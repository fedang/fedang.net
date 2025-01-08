+++
title = 'Setting up Ly on Gentoo'
date = 2025-01-08T01:00:52+01:00
summary = "My experience with installing the `ly` display manager."
categories = [ "linux", "guide" ]
tags = [ "linux", "gentoo", "display-manager", "ly", "tty" ]
+++

> Ly is a lightweight TUI (ncurses-like) display manager for Linux and BSD.

## Premise

A few months ago, my Gentoo install came to be in a rather annoying predicament.
Instead of the usual login tty, I was greeted by a black screen after booting from GRUB.
I inserted my credentials nonetheless, and to my relief, I could successfully launch X.

I was confident that the culprit was some kernel option or driver.
Yet I did not have quite enough time or motivation to investigate,
so I eventually ended up getting used to logging in from a blank tty.

In the meantime, I began looking into display managers, hoping that they would prevent similar situations.
While searching, I stumbled upon [ly](https://github.com/fairyglade/ly) and was intrigued.

Yesterday I had some free time and decided finally to try `ly` out.

## Installing Ly

Ly doesn't have an ebuild in the official Gentoo repository yet,
but there is one in the GURU overlay[^guru].

The project README also has a section about installing on Gentoo[^gentoo].

However, I decided to install it directly from git and compile it myself.
I had already all the dependencies installed, except for Zig.

```sh {class="cmd-root"}
emerge --ask dev-lang/zig-bin
```

After cloning the repository I installed `ly` following the instructions.

```sh {class="cmd-root"}
zig build installopenrc
rc-update del display-manager
rc-update add ly
```

## Fixing the blank TTY

After rebooting, my screen was once again a blank slate. :frowning:

I did some digging and found a very helpful discussion on the Gentoo forum[^forum].
Apparently newer nvidia drivers conflict with some kernel options (`FB_SIMPLE`, `SYSFB_SIMPLEFB`, `DRM_SIMPLEDRM`).
I disabled them and recompiled my kernel (see [here]({{< ref "/posts/gentoo-kernel-upgrade" >}}) for details).

Now my TTYs can be seen once again, hooray!

## Moving to Openrc-init

Unfortunately `ly` does not support `sysvinit`, Gentoo's default init system.
Since my system is based around OpenRC, I decided to enable OpenRC's own init.

For an easier transition I added the `sysv-utils` use flags to `sys-apps/openrc` and reemerged.

```sh {class="cmd-root"}
echo "sys-apps/openrc sysv-utils" >> /etc/portage/package.use
emerge --ask --oneshot --newuse sys-apps/openrc
```

To start using `openrc-init` you just need to pass the parameter `init=/sbin/openrc-init` to the kernel.

Also, remember to disable `agetty` in the tty used by `ly` (the default is `tty2`).
```sh {class="cmd-root"}
rc-update del agetty.tty2
```

## Fixing the xinitrc

At this point, `ly` is being displayed in the second tty.
The input works correctly and I can log into a shell session.

But the same can't be said for the xinitrc environment.
Despite having made the `.xinitrc` an executable shell script, I am
instantly logged out every time I try it.

After some debugging, I discovered that the root of the problem was my home layout.
To adopt the XDG specification, I had moved the xinitrc and most of my configuration files to the `.config`
directory.

The environmental variables (`PATH`, `XINITRC`, etc.) were being assigned in my `.zshrc` file,
which is sourced only by interactive shells.
This is the reason running `startx` from a shell worked, while the same scripts failed
when run by `ly`.

I moved the environment initialization to the `.zprofile` file, which is always sourced.
After this last change, I could finally start a X session from `ly`. :partying_face:

## Configuring Ly

These are my initial modifications to the `/etc/ly/config.ini` file.

```diff
36c36
< animation = none
---
> animation = doom
88c88
< clock = null
---
> clock = %c
114c114
< hide_key_hints = false
---
> hide_key_hints = true
118c118
< initial_info_text = null
---
> initial_info_text = core login
174c174
< session_log = ly-session.log
---
> session_log = .cache/ly-session.log
192c192
< text_in_center = false
---
> text_in_center = true
216c216
< xinitrc = ~/.xinitrc
---
> xinitrc = ~/.config/X11/xinitrc
```

## References

- https://github.com/fairyglade/ly
- https://wiki.gentoo.org/wiki/OpenRC/openrc-init


[^gentoo]: https://github.com/fairyglade/ly#gentoo-installation
[^forum]: https://forums.gentoo.org/viewtopic-t-1157629-start-25.html
[^guru]: https://github.com/gentoo-mirror/guru/tree/master/x11-misc/ly
