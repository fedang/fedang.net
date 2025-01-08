+++
title = "Gentoo kernel upgrade"
subtitle = ""
categories = [ "linux", "guide" ]
tags = [ "linux", "gentoo", "kernel", "sysadmin" ]
date = "2024-12-10"
#summary = "A brief howto on updating the kernel on a Gentoo system."
summary = """I wrote this short guide to keep track of the upgrade procedure for the kernel on a Gentoo system. \
The main steps are summarized, with additional sections about the Nvidia drivers and Intel microcode."""
+++

I wrote this short guide to keep track of the upgrade procedure for the kernel on a Gentoo system.
The main steps are summarized, with additional sections about the Nvidia drivers and Intel microcode.

This guide should be used as a checklist and assumes an already working installation.
If you need more exhaustive documentation, refer to the Gentoo wiki.

## Preliminary steps

We will update from `linux-A.B.C` to `linux-X.Y.Z`.

Let's start by fetching the source of the new kernel.

```sh {class="cmd-root"}
emerge -uDUa --with-bdeps=y =sys-kernel/gentoo-sources-X.Y.Z
```
You may also need to update `@world` set before updating the kernel.

```sh {class="cmd-root"}
emerge -uDUa --with-bdeps=y @world
```

Using eselect, select the kernel version that you want to upgrade to.
This will adjust the `/usr/src/linux` symlink.

```sh {class="cmd-root"}
eselect kernel list
eselect kernel set X
```

Go to the directory containing kernel sources.

```sh {class="cmd-root"}
cd /usr/src/linux
```

## Configuration

Start by copying your `.config` from the old kernel sources.

```sh {class="cmd-root"}
# from the old folder
cp /usr/src/linux-A.B.C-gentoo/.config /usr/src/linux
# from the running kernel
zcat /proc/config.gz > /usr/src/linux/.config
```

Then, you will have to update the configuration file.
The **oldconfig** target will interactively prompt you to insert values for the new options.

```sh {class="cmd-root"}
make oldconfig
```

Alternatively, **olddefconfig** will automatically insert default values for the new options.

```sh {class="cmd-root"}
make olddefconfig
```

To easily change more configuration options you can use **menuconfig**, which will start an interactive ncurses interface.

```sh {class="cmd-root"}
make menuconfig
```

{{< note Warning >}}
Manually editing the `.config` file is highly discouraged
since configuration options have dependencies.
{{< /note >}}

## Building

Once you are done changing your configuration, you can build your kernel with make.
The [NVIDIA drivers](#nvidia-drivers) and [Intel microcode](#intel-microcode) require you
to do extra steps before building.

You can speed up the build process by using multiple make jobs.
It is helpful to determine the number of cpu threads with `nproc`.

```sh {class="cmd-root"}
make -j$(nproc)
```

## Installation

Firstly, mount the boot partition if it is not already mounted.

```sh {class="cmd-root"}
mount /boot
```

Then, you can install the new kernel and modules.

```sh {class="cmd-root"}
make install
make modules_install
```

Update your bootloader configuration. If you are using GRUB, you can use grub-mkconfig.

```sh {class="cmd-root"}
grub-mkconfig -o /boot/grub/grub.cfg
```

Some kernel modules may be installed by packages and live outside of the kernel source tree (e.g. Nvidia drivers).
They need to be rebuilt every time you change the kernel.
Luckily portage provides this handy shorthand.

```sh {class="cmd-root"}
emerge @module-rebuild
```

Additionally, some drivers may require firmware updates.

```sh {class="cmd-root"}
emerge sys-kernel/linux-firmware
```

Now you can reboot your machine and everything should hopefully work as intended.

## Clean up

It is a good habit to keep the old kernel files around (at least until you have verified the new ones).

If you have a few old kernels in your boot partition, you may want to remove some of them.

```sh {class="cmd-root"}
rm /boot/System.map-A.B.C-gentoo
rm /boot/config-A.B.C-gentoo
rm /boot/vmlinuz-A.B.C-gentoo
```

Then, remember to update GRUB (or your bootloader of choice).

```sh {class="cmd-root"}
grub-mkconfig -o /boot/grub/grub.cfg
```

## Addenda

### Nvidia drivers

I will not delve too much on the details here.
You can check exactly which kernel options features to enable on the wiki[^nvidia].

However, I recently found the solution to a problem that caused my TTYs to be blank.
I had accidentally activated `FB_SIMPLE`, `SYSFB_SIMPLEFB` and `DRM_SIMPLEDRM`.
These options cause problems with newer nvidia drivers and should be disabled[^fb-nvidia].

```sh {class="cmd-root"}
emerge x11-drivers/nvidia-drivers
```

If you already installed the drivers, `@module-rebuild` should automatically rebuild them.

### Intel microcode

Install Intel's `iucode_tool` for managing microcodes.

```sh {class="cmd-root"}
emerge sys-firmware/intel-microcode
```

Use the tool to get the processor signature and search a microcode bundle with
a matching signature.

```sh {class="cmd-root"}
iucode_tool -S
iucode_tool -S -l /lib/firmware/intel-ucode/*
```

Enable in the kernel configuration the microcode loading features and add in
the **Firmware loading facility** the microcode bundle found before as a named
firmware blob, then build the kernel.

Now build and install the kernel.

Verify after rebooting that the microcode is loaded by the kernel.

```sh {class="cmd-root"}
dmesg | grep microcode
```

For more details, see the wiki[^intel].

## References

- https://wiki.gentoo.org/wiki/Kernel
- https://wiki.gentoo.org/wiki/Kernel/Upgrade
- https://wiki.gentoo.org/wiki/Kernel/Removal

[^nvidia]: https://wiki.gentoo.org/wiki/NVIDIA/nvidia-drivers
[^fb-nvidia]: https://forums.gentoo.org/viewtopic-t-1157629-start-25.html
[^intel]: https://wiki.gentoo.org/wiki/Intel_microcode
