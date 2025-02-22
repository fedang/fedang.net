+++
title = 'Theory and implementation of tagged pointers'
date = 2025-02-14T13:58:39+01:00
categories = [ "langdev", "guide", "low-level" ]
tags = [ "low-level", "memory", "optimization", "langdev", "interpreter" ]
draft = true
+++

Curious about the tricks that make some interpreted languages so fast?
Let's analyze and implement **tagged pointers**, a clever optimization
that can reduce memory footprint and boost performance in interpreters.

<!--more-->

## Some theory

Let's start with the term *pointer*, which I'll use to refer to actual **memory addresses**.
Going forward, I will assume these to be represented as a word-sized integer.
All possible pointer values (2 to the power of the bits in a word) form the *virtual address space*.

In principle, all of these addresses are valid and potentially used.
While this could be the case for older or embedded systems, modern ones won't allocate certain ranges.
Consequently, some of the bits in a pointer will be unused (for addressing at least).

First, let's see the behaviour of 32-bit architectures (e.g., x86, Arm32).
They use *32-bit words* (hence their name), and can address up to 4 GB (4 × 1024&sup3; bytes) of memory[^pae].
Since these systems can use all of the 4 gigs, are the bits in the addresses fully utilized? Well, not necessarily.

This is where **alignment** comes into the picture.
Processors don't like reading from addresses not divisible by their word size.
These unaligned accesses can cause performance problems (multiple reads may be executed) or even trap.

To prevent this, compilers insert padding to align values according to their types' alignment (which can be queried with `alignof`).
These alignment requirements are specified in an *Application Binary Interface* and are thus platform-dependent.
For example, the current Linux ABI guarantees the stack to be 16 bytes aligned[^abi].

Similar conventions are also adopted by system libraries.
Memory allocated with `malloc` is aligned to 8 bytes (16 on 64-bit systems) by both glibc[^malloc] and MSVCRT[^msalloc].

On a system where these assumptions hold, our pointers will always have their bottom 3 bits set to zero.

```
Top                       Bottom
▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮000
```

We can use those bits to store some metadata, masking them when the raw pointer is needed.
This technique, let's call it **low bits tagging**, can be used just as well on
64-bit architectures (x86_64, Aarch64, etc.).

But another opportunity opens up for us on these systems thanks to their
massive (theoretical) address space of 16 EB (16 million terabytes!).
This range is so ludicrously big that processors don't physically support all of it.
Today, the most common configuration is using *48-bit virtual addresses*, leaving the top 16 bits unused.

Let's see how these bits are handled in common architectures (technical content ahead).

### x86_64

Canonical addresses on x86_64 must have bits 63 through 48 set to zeros or ones (depending on whether bit 47 is a zero or one)[^intel].
The Linux kernel uses the bit 47 to distinguish between user and kernel address space[^mmap].
This means that in user space, bits 63:47 will always be zero.

Linux 4.14 added support for 5-level paging, which allows *57-bit virtual addresses*.
Everything said above applies, but for bit 56 instead of 47.
By default, addresses above 47-bit will not be allocated for user space[^page5].

An Intel extension called *Linear Address Masking*, ignores the high bits of pointers[^lam], avoiding explicit masking.
The most significant bit is reserved for kernel use, allowing metadata in bits 62:57 (or 62:48 in `LAM_U48` mode).

A similar feature from AMD called *Upper Address Ignore* has not been added to the kernel due to
security concerns[^uai].
It allows the uppermost 7 bits to be ignored, including the most significant bit, which is
usually reserved for kernel addresses.

### ARM64

The Aarch64 architecture adopts a slightly different approach.
For 48-bit virtual addresses, bits 63:48 must be either all 0s or all 1s.
Address space partitioning is independent of bit 47, allowing for a range of 256 TB (instead of the 128 TB on x86_64).
Kernel addresses have the high bits set to 1s, while user space addresses must have them set to zero[^armptr].

Linux also supports 52-bit addressing[^armmap], which not all processors implement.
For compatibility, all user space addresses will be by default in the 48-bit range.

Arm-v8 introduced the *Top Byte Ignore* feature, which has similarities to Intel's LAM.
It was added to allow for virtual address tagging[^tbi] and works by ignoring bits 63:56.
Linux supports TBI alongside the *Memory Tagging Extension*[^mtelinux].

### RISC-V

RISC-V supports three addressing modes: 39-bit (SV39), 48-bit (SV48) and 57-bit (SV57) virtual addresses.
Like x86_64, the high bits of the address must match (sign extend) the last addressable bit[^riscv].
For example, when using SV48 addressing, bits 63:48 must be equal to bit 47.

The virtual memory layout[^rvmap] is similar to x86_64, where bit 47 is set for kernel addresses
and the top bits are zero for user space.

The recently ratified *RISC-V Pointer Masking* proposal[^rvext] adds the `Smmpm`, `Smnpm` and `Ssnpm` extensions.
These can be used to configure the processor to ignore `PMLEN` bits in addresses, starting from the most significant bit.

By setting `PMLEN` to 7, the addresses are masked similarly to AMD's UAI.
The security concerns were addressed in a note, specifying that an appropriate system ABI
can prevent the usage of the MSB without changes to the masking mechanism.

### To sum up

As we have seen, each architecture leaves some parts of the address unused.
Let's call the technique that stores metadata in those bits **high bits tagging**.

For the sake of simplicity, let's select a single layout to act as a common denominator between the
various platforms.
To accommodate x86_64 5-level paging and LAM, we can choose to use only bits 62:57 for tagging.
These bits are allowed on RISC-V and also fall inside the range of Arm's TBI feature.
I'm also assuming that our addresses are aligned to 16 bytes.

Thus, we end up with the following pointer layout (`T` for tag bits).

```
Top                                                       Bottom
▮TTTTTT▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮▮0000
```

## Why is this useful?

Now that we have a good grasp of the principles of pointer tagging,
we can move on to address :wink: their practical uses and advantages.

The metadata stored in the tags could be utilized in many ways.
For example, Android uses it to improve memory safety through MTE[^mte2].
From now on, I will focus on its applications in language development and interpreters.

But before delving into the benefits of this optimization, let's first see what they are replacing.
A common approach is to heap allocate everything as an object and use
pointers as a uniform value representation. This is what CPython does with `PyObject`.

The usual alternative is a *tagged union*, which stores a union of the possible value types alongside
an integer flag. This results in fewer heap allocations, but comes at the cost of a larger value type (usually 16 bytes).
Lua is currently using this approach[^lua].

By tagging our pointers, we can reduce heap allocations and have a single word as our value representation.
We can have our cake and eat it too!










## Technique comparison


There are other clever ways to stuff extra information in a pointer.
A technique called NaN boxing makes use specific bit configurations of the IEEE 754 double precision float
to store pointers (up to 52 bits).

## A word of caution

This does not work on funky architectures. FPGA, Xeon Phi


While there are no standard guarantees about memory alignment, common architectures like x86 are very consistent.




## Implementation


### Union


## Tagged implementation

### Low bit

### High bit






## References
- https://muxup.com/2023q4/storing-data-in-pointers
- https://coredumped.dev/2024/09/09/what-is-the-best-pointer-tagging-method
- https://bernsteinbear.com/blog/small-objects
- https://wingolog.org/archives/2011/05/18/value-representation-in-javascript-implementations
- https://en.wikichip.org/wiki/arm/tbi
- https://mikeash.com/pyblog/friday-qa-2012-07-27-lets-build-tagged-pointers.html
- https://www.snellman.net/blog/archive/2017-09-04-lisp-numbers
- https://alwaysprocessing.blog/2023/03/19/objc-tagged-ptr

[^mmap]: https://docs.kernel.org/arch/x86/x86_64/mm.html
[^rvmap]: https://docs.kernel.org/arch/riscv/vm-layout.html
[^armmap]: https://docs.kernel.org/arch/arm64/memory.html

[^uai]: *Pointer tagging for x86 systems*, \
    https://lwn.net/Articles/888914/

[^lam]: *Support for Intel's Linear Address Masking*, \
    https://lwn.net/Articles/902094

[^armptr]: https://www.kernel.org/doc/Documentation/arm64/tagged-pointers.txt

[^tbi]: https://source.android.com/docs/security/test/tagged-pointers#top-byte-ignore

[^mte]: *Armv8.5-A Memory Tagging Extension*, \
    https://developer.arm.com/-/media/Arm%20Developer%20Community/PDF/Arm_Memory_Tagging_Extension_Whitepaper.pdf

[^mtelinux]: https://docs.kernel.org/arch/arm64/memory-tagging-extension.html

[^page5]: https://docs.kernel.org/arch/x86/x86_64/5level-paging.html

[^rvext]: *RISC-V Pointer Masking*, \
    https://drive.google.com/file/d/159QffOTbi3EEbdkKndYRZ2c46D25ZLmO/view

[^riscv]: *The RISC-V Instruction Set Manual: Volume II*, \
    https://drive.google.com/file/d/17GeetSnT5wW3xNuAHI95-SI1gPGd5sJ_/view

[^malloc]: https://www.gnu.org/software/libc/manual/html_node/Aligned-Memory-Blocks.html

[^pae]: I purposefully didn't mention PAE, see \
    https://www.realworldtech.com/forum/?threadid=76912&curpostid=76973

[^intel]: *Intel 64 and IA-32 Architectures Software Developer’s Manual*, \
    https://cdrdv2.intel.com/v1/dl/getContent/671200

[^rvnote]: https://github.com/riscv/riscv-j-extension/blob/master/zjpm/background.adoc#pointer-masking-and-privilege-modes

[^msalloc]: https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/malloc

[^abi]: *Linux x86 ABI changed; compiler update required*, \
    https://sourceforge.net/p/fbc/bugs/659

[^mte2]: *How does MTE work?*, \
    https://developer.arm.com/documentation/108035/0100/How-does-MTE-work-?

[^v8]: https://v8.dev/blog/pointer-compression#value-tagging-in-v8

[^lua]: https://github.com/lua/lua/blob/master/lobject.h
