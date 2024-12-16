+++
title = "Gentoo kernel upgrade"
summary = "A brief howto on updating the kernel on a Gentoo system."
categories = [ "linux", "guide" ]
tags = [ "gentoo", "kernel", "linux", "sysadmin" ]
date = "2024-12-10"
+++

In this short guide I summarized the necessary steps to upgrade the
kernel in a Gentoo system.

We will update from `linux-A.B.C` to `linux-X.Y.Z`.

## Preliminary steps

Fetch the sources of the kernel that you want to install.

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
The *oldconfig* command will interactively prompt you to insert values for the new options.

```sh {class="cmd-root"}
make oldconfig
```

Alternatively, the *olddefconfig* command will automatically insert default values for the new options.

```sh {class="cmd-root"}
make olddefconfig
```

To easily change more configuration options you can use the *menuconfig* command, which will start an interactive ncurses interface.

```sh {class="cmd-root"}
make menuconfig
```

{{< note Warning >}}
Manually editing the `.config` file is highly discouraged.
{{< /note >}}

## Building

Once you finished setting your configuration, you can build your kernel with make.
The [NVIDIA drivers](#nvidia-drivers) and [Intel microcode](#intel-microcode) require you
to do extra steps before building.

You can speed up the build process by using multiple make jobs.
It is helpful to determine the number of cpu threads with `nproc`.

```sh {class="cmd-root"}
make -jN
```

## Installation

First of all, mount the boot partition, if it is not already mounted.

```sh {class="cmd-root"}
mount /dev/XXX /boot
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
It is a good habits to keep the old kernel files around (at least until you have verified the new ones).

## Addenda

### Nvidia drivers

I will not delve too much on the details here.
You can check exactly which kernel options features to enable on the wiki.

```sh {class="cmd-root"}
emerge x11-drivers/nvidia-drivers
```

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
the *Firmware loading facility* the microcode bundle found before as a named
firmware blob, then build the kernel.

Now build and install the kernel.

Verify after the rebooting that the microcode is loaded by the kernel.

```sh {class="cmd-root"}
dmesg | grep microcode
```

## References
- https://wiki.gentoo.org/wiki/Kernel
- https://wiki.gentoo.org/wiki/Kernel/Upgrade
- https://wiki.gentoo.org/wiki/Kernel/Removal
- https://wiki.gentoo.org/wiki/Intel_microcode
- https://wiki.gentoo.org/wiki/NVIDIA/nvidia-drivers
