+++
title = "Gentoo kernel upgrade"
summary = "A brief howto on updating the kernel on a Gentoo system."
categories = [ "linux", "article" ]
tags = [ "gentoo", "kernel", "linux", "sysadmin" ]
+++

## Preliminary steps

Fetch the sources of the kernel that you want to install.

```sh {class="cmd-root"}
emerge -uDUa --with-bdeps=y =sys-kernel/gentoo-sources-X.Y.Z
```
You may also need to update @world set before updating the kernel.

```sh {class="cmd-root"}
emerge -uDUa --with-bdeps=y @world
```

Using eselect, select the kernel version that you want to upgrade to.

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
cp /usr/src/linux-A.B.C-gentoo/.config /usr/src/linux
```

Then, you will have to update the configuration file. The oldconfig command will interactively prompt you to insert values for the new options.

```sh {class="cmd-root"}
make oldconfig
```

Alternatively, the olddefconfig command will automatically insert default values for the new options.

```sh {class="cmd-root"}
make olddefconfig
```

To easily change more configuration options you can use the menuconfig command, which will start an interactive ncurses interface.

```sh {class="cmd-root"}
make menuconfig
```

{{< note Warning >}}
Manually editing the `.config` file is highly discouraged.
{{< /note >}}

## Building

Once you finished setting your configuration, you can build your kernel with make.
You can speed up the build process by using multiple make jobs (determine the number with nproc).

```sh {class="cmd-root"}
make -jN
```

## Intel microcode addendum

Firstly, install the microcode firmware and the tool to manage it.

```sh {class="cmd-root"}
emerge sys-firmware/intel-microcode
```

Use the newly installed `iucode_tool` to get the processor signature and search a microcode bundle with a matching signature.

```sh {class="cmd-root"}
iucode_tool -S
iucode_tool -S -l /lib/firmware/intel-ucode/*
```

Enable in the kernel configuration the microcode loading features. Then, add in the `Firmware loading facility` the microcode
bundle found before as a named firmware blob.

After building the kernel, you can easily verify after the boot that the microcode is loaded with dmesg.

```sh {class="cmd-root"}
dmesg | grep microcode
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

Some kernel modules may be installed by packages and live outside of the kernel source tree (e.g. Nvidia drivers), and need to be rebuilt.

```sh {class="cmd-root"}
emerge @module-rebuild
```

Additionally, updating the firmware may be required by some drivers.

```sh {class="cmd-root"}
emerge sys-kernel/linux-firmware
```

## References
- https://wiki.gentoo.org/wiki/Kernel
- https://wiki.gentoo.org/wiki/Kernel/Upgrade
- https://wiki.gentoo.org/wiki/Kernel/Removal
- https://wiki.gentoo.org/wiki/Intel_microcode
