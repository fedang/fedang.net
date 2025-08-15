+++
date = 2025-08-16T15:27:50+02:00
title = 'Understanding sudo by writing your own'
summary = """
In Linux, `sudo` is an essential tool for system administration.
Let's demystify how it works by writing our own small clone.
"""

categories = [ "linux", "deep-dive", "programming" ]
tags = [ "linux", "suid", "security", "pam", "c", "sysadmin" ]

no_pubinfo = false
no_rssfeed = false
+++

In the Linux world, `sudo` is an essential tool for system administration.
While most users have used it at least once, not everyone knows how it works.
Today, we'll demystify `sudo` and, along the way, write our own small clone.
After all, what better way to understand something than making it from scratch?

## What is sudo again?

Let's start by recalling what `sudo` is.
It stands for **s**uper**u**ser **do**, and as the name implies,
it allows regular users to execute commands as the administrator.
For example, running `whoami` with sudo won't return your username:

```sh {class="cmd-user"}
sudo whoami
```
```sh
root
```

On Linux, the superuser is traditionally called `root`.
But what really makes it special is that its user ID (UID) is 0.

```sh {class="cmd-user"}
sudo id
```
```sh
uid=0(root) gid=0(root) groups=0(root)
```

Of course, we can't let everyone just run privileged commands as they wish.
That's why sudo makes several checks (group membership, user password, etc.)
before allowing execution.

Actually, sudo has many more features[^man], but for the sake of simplicity,
we'll just focus on this core pipeline:
1. Authenticate the user and check permissions
2. Set up environment variables
3. Execute commands as a privileged user

As I said before, sudo is just a normal program, and there are others doing the same thing.
For example, [sudo-rs][sudors] is a recent rewrite of `sudo` in Rust.
Then there is [doas][doas0], a simpler alternative made for OpenBSD.


## A bit of kernel magic -- setuid

I said there was nothing magical about sudo and similar programs.
But actually, there is something that sets them apart from your average executable:
they have the `setuid` bit.
This is part of the file permission bits, in addition to the usual `rwx` modes.

```sh {class="cmd-user"}
ls -la $(which sudo)
```
```sh
-rwsr-xr-x 1 root root 290008 Jun 30 22:17 /usr/bin/sudo
```

Here we can see the setuid bit, indicated by a `s` -- in the place of `x`.
But, that said, what does this even do?

When a setuid program is executed, the process UID
is set to that of the file owner rather than the current user.
Sounds simple, right? Let's do some tests.

```c
#include <unistd.h>
#include <stdio.h>

int main()
{
    if (getuid() == 0)
        printf("I am root!\n");
    return 0;
}
```

This simple program just prints a message when run as root.
Let's try adding the `setuid` bit.
Note that we are compiling as root, otherwise you should use `chown root` to change file ownership.

```sh {class="cmd-root"}
cc -o example example.c
chmod u+s example
ls -la example
```
```sh
-rwsr-xr-x 1 root   root    20K Aug 14 21:09 example
```

If we run this now, we will unsurprisingly see the message:

```sh {class="cmd-root"}
./example
```
```sh
I am root!
```

But what happens if we run this as a regular user?

```sh {class="cmd-user"}
./example
```

Nothing... What is going on here?

Well, I said that `setuid` sets the UID to that of the file owner.
What I didn't say is that it sets the *effective* UID, which is different from the *real* UID.
But this is not a big problem, since we can set the real UID manually.

```c
int main()
{
    if (geteuid() == 0)
        setuid(0);
    if (getuid() == 0)
        printf("I am root!\n");
    return 0;
}
```

Now it works as we expected:

```sh {class="cmd-user"}
./example
```
```sh
I am root!
```

Here's a small figure to recap:

```
  normal executable               setuid executable
+--------------------+          +--------------------+
| owner: 0    (root) |          | owner: 0    (root) |
| ruid:  1000 (user) |          | ruid:  1000 (user) |
| euid:  1000 (user) |          | euid:  0    (root) |
+--------------------+          +--------------------+
```


## Building from scratch

Now that we know what sudo does and how, we can start making our own version.
I decided to call it `sus`. If you are wondering, it stands for **s**uper**u**ser **s**tart.

{{< note "⚠️ Important disclaimer" >}}
This is only an educational project.
It's not wise to keep untested setuid binaries around!
Use at your own risk, you have been warned...
{{< /note >}}

With the obligatory warning out of the way, it's coding time.

### 1. User authentication

Following the order of the core operations I described in the first section,
let's start with checking user permissions.

This step is crucial: if the checks are incorrect, malicious users could escalate their privileges.
In `sus` we will check if the user is in the `wheel` group[^wheel] and then prompt for their password.

```c
#define ALLOW_GROUP "wheel"
#define PWBUF_SIZE 16384

static struct passwd userpw, rootpw;
static char userbuf[PWBUF_SIZE], rootbuf[PWBUF_SIZE];

static void user_auth()
{
    uid_t uid = getuid();
    struct passwd *ptr = NULL;

    if (getpwuid_r(uid, &userpw, userbuf, sizeof(userbuf), &ptr) != 0 || ptr == NULL)
        errx(1, "Failed to get user info: entry too large or missing");

    ptr = NULL;
    if (getpwuid_r(0, &rootpw, rootbuf, sizeof(rootbuf), &ptr) != 0 || ptr == NULL)
        errx(1, "Failed to get root info: entry too large or missing");

    // User is already root
    if (uid == 0)
        return;

    if (!in_group(userpw.pw_name, userpw.pw_gid))
        errx(1, "User is not in the %s group", ALLOW_GROUP);

    if (!shadow_auth(userpw.pw_name))
        errx(1, "Authentication failed");
}
```

First of all, we read the `passwd` struct for the current user and root.
By using `getpwuid_r()` and a global buffer, the entries can be used by other functions.

Also, you can see the foolproof error-handling approach I chose: exiting at the first problem.
Since the code is so short, this seemed the best way.

Anyway, let's move on to the group membership check.

```c
#define MAX_GROUPS 128

static bool in_group(const char *user, gid_t gid)
{
    struct group *grp = getgrnam(ALLOW_GROUP);
    if (!grp)
        return false;

    gid_t allow = grp->gr_gid;
    if (gid == allow)
        return true;

    gid_t groups[MAX_GROUPS];
    int ngroups = MAX_GROUPS;

    int ret = getgrouplist(user, gid, groups, &ngroups);
    if (ret == -1)
        errx(1, "Failed to get user groups");

    if (ngroups > MAX_GROUPS)
        errx(1, "Do you really need so many groups?");

    bool ok = false;
    for (int i = 0; i < ngroups; i++) {
        if (groups[i] == allow) {
            ok = true;
            break;
        }
    }
    return ok;
}
```

This function starts by getting the `group` struct associated with `wheel`,
and saving its GID.
Then, a buffer is filled with the supplementary groups of the user.
If any of those matches the allowed GID, the function returns true.


As for `shadow_auth()`, it simply prompts the user for a password in the TTY,
then checks if the hash matches the one stored in the shadow file[^shadow].

```c
static bool shadow_auth(const char *user)
{
    char rbuf[1024], cbuf[128], host[HOST_NAME_MAX + 1];
    const char *chall = "Password: ";
    char *pass = readpassphrase(chall, rbuf, sizeof(rbuf), RPP_REQUIRE_TTY);

    if (!pass)
        err(1, "Failed to read passphrase");

    struct spwd *spw = getspnam(user);
    if (!spw)
        return false;

    char *res = crypt(pass, spw->sp_pwdp);
    return res && !strcmp(res, spw->sp_pwdp);
}
```

The `spwd` struct is analogous to `passwd`, which we have seen before.
The hashed passwords use `crypt()`, which is part of libcrypt.

You might have noticed the usage of `readpassphrase()`.
This is a very useful function that reads a password from TTY without echo[^readpass].
I discovered this little gem while diving into `doas` source code[^doas].
Unfortunately, this function is available only on BSDs.
Despite that, you can copy the original file[^readpass2] and use it on Linux easily.

Here's a copy of the files ready to be used on Linux: [readpassphrase.c]({{< fullpath "readpassphrase.c" >}})
and [readpassphrase.h]({{< fullpath "readpassphrase.h" >}}).

### 2. Environment variables

When acting as another user, it's important to sanitize the environment.
Some variables are used extensively, for example `HOME` and `USER`.
Others, like `LD_PRELOAD`, can be used to hijack programs[^ld],
so they should not be inherited for security reasons.

```c
static void env_prepare()
{
    const char *pass[4] = { "TERM", "DISPLAY", "PATH", NULL };
    char *save[4] = { NULL };

    for (int i = 0; pass[i]; i++) {
        const char *val = getenv(pass[i]);
        save[i] = val ? strdup(val) : NULL;
    }

    if (clearenv() == -1)
        err(1, "clearenv");

    if (setenv("USER", rootpw.pw_name, 1) == -1 ||
        setenv("SHELL", rootpw.pw_shell, 1) == -1 ||
        setenv("HOME", rootpw.pw_dir, 1) == -1 ||
        setenv("LOGNAME", rootpw.pw_name, 1) == -1 ||
        setenv("SUS_USER", userpw.pw_name, 1) == -1)
        err(1, "setenv");

    for (int i = 0; pass[i]; i++) {
        if (!save[i])
            continue;
        if (setenv(pass[i], save[i], 1) == -1)
            err(1, "setenv");
        free(save[i]);
    }
}
```

We start by saving a list of whitelisted variables.
Then, we clear the environment and only add common values from root's passwd entry.
Finally, the saved values are restored.

### 3. Command execution

At this point, we trust the user and we have prepared the environment for running our command.
But there is still something that has to be done before we can use the `exec` system call.

As we saw before in the small test, `setuid` changes only the effective UID.
Thus, we must set the real UID and GID to get the privileges that we want.

```c
static void cmd_execute(int argc, char **argv)
{
    // Escalate privileges
    umask(022);

    if (initgroups(rootpw.pw_name, rootpw.pw_gid) == -1)
        err(1, "initgroups");

    if (setgid(0) == -1)
        err(1, "setgid");

    if (setuid(0) == -1)
        err(1, "setuid");

    // Execute given program (or shell)
    char *binsh[2] = { NULL };
    if (argc <= 1) {
        binsh[0] = rootpw.pw_shell ? rootpw.pw_shell : "/bin/sh";
        argv = binsh;
    } else {
        // Skip argv0
        argv++;
    }

    execvp(*argv, argv);
    err(1, "Command execution failed");
}
```

The `umask()` call sets the default permission file mask,
while `initgroups()` sets the supplementary groups for root.

Finally, `execvp` is a variant of the `exec` family that
searches the executable in the `PATH` (similar to the shell).
We will execute the arguments received from the CLI,
and if none are provided fall back to the shell.

### Tying them all together

Each phase is handled by the functions we saw earlier,
so all that's left is some C glue.

```c
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <err.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>
#include <shadow.h>
#include <crypt.h>

#include "readpassphrase.h"

// ... previous functions ...

int main(int argc, char **argv)
{
    user_auth();

    env_prepare();

    cmd_execute(argc, argv);
}
```

Before continuing, remember to add yourself to the `wheel` group:
```sh {class="cmd-root"}
sudo usermod -aG wheel user
```

Finally, let's compile...

```sh {class="cmd-root"}
cc -o sus sus.c -lcrypt
chmod u+s sus
```
...and try it out.

```sh {class="cmd-user"}
./sus
```
```sh
Password:
bash-5.2# id
uid=0(root) gid=0(root) groups=0(root)
bash-5.2# env
SHELL=/bin/bash
PWD=/home/fedang/code/sus
LOGNAME=root
SUS_USER=fedang
HOME=/root
TERM=alacritty
USER=root
DISPLAY=:0
SHLVL=1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin
_=/bin/env
bash-5.2#
```

Works to a tee!
The UID, GID, groups and environment are set up correctly for the `root` user.

## Some security hardening

While `sus` is technically complete, we can still make some improvements.

For example, what happens if a malicious user renames
or symlinks `sus` to make unsuspecting users think they are running something else?

```sh {class="cmd-user"}
not_sus something bad
```
```sh
Pwned 😈
```

The real `sudo` has a whitelist for `argv[0]` (the executable name).

```c
initprogname2(argc > 0 ? argv[0] : "sudo", allowed_prognames);
```

We can add a small check to block invocations with a name other than `sus`.

```c
static void integrity_check(const char *argv0)
{
    const char *name = strrchr(argv0, '/');
    name = name ? &name[1] : argv0;
    if (strcmp(name, "sus"))
        errx(1, "Invoked with wrong filename: %s", name);

    if (geteuid() != 0)
        errx(1, "Not running with EUID 0, is this root-owned and setuid?");
}
```

I also added a check for the effective UID.
Let's plug this into `main()`.

```c {hl_lines=3}
int main(int argc, char **argv)
{
    integrity_check(argc > 0 ? argv[0] : "sus");

    user_auth();

    env_prepare();

    cmd_execute(argc, argv);
}
```

Now it's much better:

```sh {class="cmd-user"}
not_sus something bad
```
```
Invoked with wrong filename: not_sus
```

Another thing that could be made stricter is the handling of `PATH`.
Currently, the value is passed through due to the whitelist.
To increase security, we can replace it with a known safe `PATH` instead.

```c {hl_lines=[6,7,17]}
#define SAFE_PATH \
    "/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin"

static void env_prepare()
{
    const char *pass[3] = { "TERM", "DISPLAY", NULL };
    char *save[3] = { NULL };

    for (int i = 0; pass[i]; i++) {
        const char *val = getenv(pass[i]);
        save[i] = val ? strdup(val) : NULL;
    }

    if (clearenv() == -1)
        err(1, "clearenv");

    if (setenv("PATH", SAFE_PATH, 1) == -1 ||
        setenv("USER", rootpw.pw_name, 1) == -1 ||
        setenv("SHELL", rootpw.pw_shell, 1) == -1 ||
        setenv("HOME", rootpw.pw_dir, 1) == -1 ||
        setenv("LOGNAME", rootpw.pw_name, 1) == -1 ||
        setenv("SUS_USER", userpw.pw_name, 1) == -1)
        err(1, "setenv");

    // ...
}
```

## PAM -- Pluggable Authentication Modules

Now, our small program not only works but is also secure (hopefully 🤞).
Despite that, we can still improve in one aspect: ecosystem integration.

A lot of Linux software relies on [PAM][pam] for authentication.
This framework was developed to remove the burden of authentication
from the end applications.
Instead, modules are loaded at runtime to provide flexible authentication schemes.

Thankfully, integrating PAM into our application is not difficult.
This function does a very basic authentication pipeline.

```c
#include <security/pam_appl.h>
#include <security/pam_misc.h>

static int pam_auth(const char *user)
{
    pam_handle_t *pamh = NULL;
    struct pam_conv conv = { misc_conv, NULL };

    int ret = pam_start("sus", user, &conv, &pamh);
    if (ret != PAM_SUCCESS)
        return ret;

    ret = pam_authenticate(pamh, 0);
    if (ret != PAM_SUCCESS)
        goto end;

    ret = pam_acct_mgmt(pamh, 0);
    if (ret != PAM_SUCCESS)
        goto end;

    ret = pam_setcred(pamh, PAM_ESTABLISH_CRED);
end:
    pam_end(pamh, ret);
    return ret;
}
```

Now we can replace `shadow_auth()` with `pam_auth()`.

```c {hl_lines=["8-10"]}
static void user_auth()
{
    // ...

    if (!in_group(userpw.pw_name, userpw.pw_gid))
        errx(1, "User is not in the %s group", ALLOW_GROUP);

    int ret = pam_auth(userpw.pw_name);
    if (ret != PAM_SUCCESS)
        errx(1, "PAM authentication failed: %s", pam_strerror(NULL, ret));
}
```

Remember to link the PAM libraries when compiling:

```sh {class="cmd-root"}
cc -o sus sus.c -lpam -lpam_misc
chmod u+s sus
```

### PAM configuration

Now that we have delegated our authentication to PAM,
it's crucial that we configure it correctly.
Otherwise, our program could stop working or become
a security hole!

PAM configuration files are stored in `/etc/pam.d/`.
But since they differ depending on your distribution,
the best bet is to copy and adapt the content of `/etc/pam.d/sudo`.

For example, on my machine I ended up with this `/etc/pam.d/sus`:
```
#%PAM-1.0
auth 		include 	system-auth
account 	include 	system-auth
session 	include 	system-auth
```

## Conclusion

We are finally done with this project.
Though, I would refrain from using it in the real world.

When comparing `sus` to `sudo` (and alternatives),
it's clear that many features are missing.
To name a few: no logging, no locales, and no target user selection (just root).
Furthermore, we don't read a config file (like `sudoers`) for fine-grained permissions,
but just bake constant values into the code.

If you liked this post, I recommend reading doas's source code[^doas-src].
It's pretty concise and easy to follow. I found it quite helpful when writing this article and `sus`.

Here you can find the source code for [sus.c]({{< fullpath "sus.c" >}}) (~160 LOC)
and a bonus [Makefile]({{< fullpath "Makefile" >}}).

## References
- https://www.sudo.ws/about/intro/
- https://github.com/trifectatechfoundation/sudo-rs
- https://github.com/Duncaen/OpenDoas
- https://flak.tedunangst.com/post/doas
- https://wiki.archlinux.org/title/PAM
- https://www.redhat.com/en/blog/pluggable-authentication-modules-pam
- https://github.com/linux-pam/linux-pam

[pam]: https://github.com/linux-pam/linux-pam

[^man]: https://www.sudo.ws/docs/man/1.8.10/sudo.man/
[^doas]: https://github.com/multiplexd/doas/blob/master/doas.c

[^readpass2]: https://cvsweb.openbsd.org/src/lib/libc/gen/readpassphrase.c?rev=1.27

[doas0]: https://flak.tedunangst.com/post/doas

[sudors]: https://github.com/trifectatechfoundation/sudo-rs

[^readpass]: https://man.freebsd.org/cgi/man.cgi?query=readpassphrase&sektion=3

[^wheel]: The group for accessing sudo/doas has been traditionally called `wheel`, \
          https://en.wikipedia.org/wiki/Wheel_(computing)

[^shadow]: Password hashes are stored in `/etc/shadow`, \
            https://man7.org/linux/man-pages/man5/shadow.5.html

[^ld]: https://man7.org/linux/man-pages/man8/ld.so.8.html

[^doas-src]: https://cvsweb.openbsd.org/src/usr.bin/doas/doas.c?rev=1.98
