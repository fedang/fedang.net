+++
date = 2025-08-13T15:27:50+02:00
title = 'Understanding sudo by writing your own'
summary = """
In Linux, `sudo` is an essential tool for system administration.
Let's demystify how it works by writing our own small clone.
"""

categories = [ "linux", "deep-dive" ]
tags = [ "linux", "suid", "security", "pam", "c", "sysadmin" ]

no_pubinfo = false
no_rssfeed = false
draft = true
+++

In the Linux world, `sudo` is an essential tool for system administration.
While most users have used it at least once, not everyone knows how it works.
Today, we'll demystify `sudo` and, along the way, write our own small clone.
Because what better way to understand something than making it from scratch?

## What is sudo again?

Let's start by recalling what `sudo` is.
It stands for **s**uper **u**ser **do**, and as the name implies,
it allows regular users to execute commands as the administrator.
For example, running `whoami` with sudo won't return your username:

```sh {class="cmd-user"}
sudo whoami
```
```sh
root
```

On Linux, the super user is traditionally called `root`.
But what really makes it special is that its user id (UID) is `0`.

```sh {class="cmd-user"}
sudo id
```
```sh
uid=0(root) gid=0(root) groups=0(root)
```

Of course, we can't let everyone just run privileged commands as they wish.
That's why sudo makes several checks (group membership, user password, etc)
before allowing execution.

Actually, sudo has many more features[^man], but for the sake of simplicity,
we'll just focus on this core pipeline:
1. Authenticate the user and check permissions
2. Set up environment variables
3. Execute commands as a privileged user

As I said before, sudo is just a normal program, and there are others doing the same thing.
For example, [sudo-rs](sudors) is a recent rewrite of `sudo` in Rust.
Then there is `doas`[^doasname], a simpler alternative written for OpenBSD.


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

Here we can see the setuid bit, indicated by the `s` -- in the place of `x`.
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

This very simple program just prints a message when we are root.
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

If we run this now, we will, not very surprisingly, see the message:

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

Well, I said that `setuid` sets the UID to the one of the file owner.
What I didn't say is that it sets the *effective* UID, which is different than the *real* UID.
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

Now it works like we expected:

```sh {class="cmd-user"}
./example
```
```sh
I am root!
```

## Building from scratch

## References
- https://www.sudo.ws/about/intro/
- https://github.com/trifectatechfoundation/sudo-rs
- https://cvsweb.openbsd.org/src/usr.bin/doas/doas.c?rev=1.98
- https://github.com/Duncaen/OpenDoas


[^man]: https://www.sudo.ws/docs/man/1.8.10/sudo.man/
[^doas]: https://github.com/multiplexd/doas/blob/master/doas.c
[^sudocode]: https://github.com/sudo-project/sudo/blob/main/src/sudo.c

[^doasname]: *Dedicated Openbsd Application Subexecutor*,\
             https://flak.tedunangst.com/post/doas
[sudors]: https://github.com/trifectatechfoundation/sudo-rs
