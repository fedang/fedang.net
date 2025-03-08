+++
title = 'Theory and implementation of tagged pointers'
date = 2025-03-09
categories = [ "langdev", "deep-dive", "low-level" ]
tags = [ "low-level", "memory", "optimization", "langdev", "interpreter" ]
+++

Let's explore **tagged pointers**, a clever optimization
that can reduce memory footprint and boost performance.

<!--more-->

Despite having widespread usage and a long history[^tagarch],
pointer tagging remains a relatively obscure topic.
That's because most of its applications are very low-level,
in operating systems and programming language interpreters.

We will look behind the scenes, analyzing and implementing this technique,
with a focus on its uses in language development.

## Preliminary theory

Let's start with the term *pointer*, which I'll use to refer to actual **memory addresses**.
Going forward, I will assume these to be represented as a word-sized integer.
All possible pointer values (2 elevated to the number of bits in a word) form the *virtual address space*.

In principle, all of these addresses are valid and potentially used.
While this could be the case for older or embedded systems, modern ones won't allocate certain ranges.
Consequently, some of the bits in a pointer will be unused[^addressing].

First, let's see the behavior of 32-bit architectures (e.g., x86, Arm32).
They use *32-bit words* (hence their name), and can address up to 4 GB (2^32 bytes) of memory[^pae].
Since these systems can use all of the 4 gigs, are the bits in the addresses fully utilized? Well, not necessarily.

This is where **alignment** comes into the picture.
Processors don't like reading from addresses not divisible by their word size.
These unaligned accesses can cause performance problems (multiple reads may be executed) or even trap.

To prevent this, compilers insert padding to align values according to their types' alignment (which can be queried with `alignof`).
These alignment requirements are specified in an *Application Binary Interface* and are thus platform-dependent.
For example, the current Linux ABI guarantees the stack to be 16-byte aligned[^abi].

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

Linux 4.14 added support for 5-level paging, which allows *57-bit virtual addresses*[^linux5page].
Everything said above applies, but for bit 56 instead of 47.
By default, addresses above 47-bit will not be allocated for user space[^page5].

An Intel extension, called *Linear Address Masking*, ignores the high bits of pointers[^lam], avoiding explicit masking.
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

Before presenting the benefits of this optimization, we need to know what tagged pointers are replacing.
For language implementations, especially interpreters, a uniform representation for all types of
values is needed, or at least preferable[^typed].

A common approach is to heap allocate everything as an object and use pointers as the representation.
This is what CPython does with `PyObject`.
The downsides are larger objects and inefficient allocations even for small values (e.g., integers, floats).

Another alternative is a **tagged union**, which stores a union of the possible value types alongside
an integer flag. Lua is currently using this approach[^lua].
Since small values are stored directly in the union, fewer allocations are needed.
But this comes at the cost of a larger value type (usually 16 bytes).

But we can have our cake and eat it too!
With pointer tagging, we can reduce heap allocations and have a single word as our value representation.

By storing some values directly in the pointer, we can avoid reading memory in those cases.
This diminishes the probability of cache misses, which are quite expensive.

Also, if the memory in the language is managed, eliminating a whole class of tiny
allocations will lessen the pressure on the garbage collector.


## A word of caution

Tagged pointers are a very powerful optimization, used by many critical systems and applications.
However, it is in no way a silver bullet and should be used with caution.

Firstly, they work only in certain environments and are intrinsically platform-dependent.
It's important to thoroughly check the architecture, ABI, and operating system of your target.

If you need to target multiple platforms, a common approach is to support a generic
value type implementation, for example, with the tagged union.
Then, with conditional compilation, you can enable the tagged pointer representation on specific targets.

```c
#if PTR_TAG_SUPPORT
#include "lowbits.h"
#else
#include "union.h"
#endif
```

The memory alignment is vital when you are using low bits tagging and must be guaranteed.
Tagging the pointers to objects on the stack should be avoided, since they could be byte-aligned (e.g., char).

Also, usually you will have to write a custom allocator (or a wrapper).
For example, this function ensures that allocations have the last 3 bits cleared (8-byte alignment).

```c
void *guarded_alloc(size_t size) {
    void *ptr = malloc(size);
    assert(((uintptr_t)ptr & 0x7) == 0);
    return ptr;
}
```

Another disadvantage is the lack of interoperability with libraries.
Tagged pointers cannot be used by code that is unaware of them, greatly limiting
the ability to interact with common libraries.
This is less problematic for language interpreters, since they frequently
require wrappers for libraries anyway.

There is the risk of using a library that has its own tags for pointers, which
could cause all kinds of unintended behavior.
In general, pointers from other sources are a security risk as they could be tagged incorrectly.

We also cannot ignore the complexity introduced by pointer tagging,
which makes debugging and tracking errors harder.

## Real world uses

Now that the obligatory warning is out of the way, let's see some tagged pointers out in the wild.

LLVM implements *PointerIntPair*, which automatically bitmangles an integer into
the low bits of a pointer. Note that this optimization is applied when possible and
only for small integer values.

A tagged representation is used by both Caml[^caml] and OCaml[^ocaml], despite being compiled
and strongly-typed languages.
This uniform value type allows them to implement generic functions in a simple way.

Lisp implementations historically have been one of the first uses of pointer tagging[^taglisp].
The type tags were even supported at the hardware level in Lisp machines[^lispmach].
Even modern implementations, such as SBCL, rely on tagged pointers[^sbcl].

While I'm treating low and high bits tagging as separate techniques, they could be combined.
The Go's runtime does just that with its *taggedPointer*[^go].
In this way it can store up to 19 bits of metadata in each pointer.


## Alternative techniques

We will see in detail three techniques: *tagged union*, *low bits tagging*, and *high bits tagging*.
But there are many ways to squeeze information into a pointer, some of which are worth mentioning.

A technique called **NaN boxing** makes use of specific bit configurations of the IEEE 754 double
to store either a number or a pointer (up to 52 bits).
This is particularly used in languages where double is the dominant number type[^nan].

The V8 JavaScript engine uses **pointer compression**[^v8].
Instead of using real addresses, all the allocations are represented by 32-bit offsets in a 4 GiB heap.
By *compressing* the pointer size, the memory footprint can be reduced by up to 40%.


## Tagged union implementation

After all this theory and considerations, we can finally move on to the implementation.
But before delving into the pointer tagging techniques we just described,
let's start from the tagged union representation.
The implementation will be fairly trivial, but it will introduce the value types and
coding style that we will use from now on.

Firstly, let's introduce the tags that we are going to use.
In our examples, they are direct translations of the types of value that we can represent.

```c
typedef enum {
    TAG_OBJECT,
    TAG_INTEGER,
    TAG_FLOAT,
    TAG_STRING,
    TAG_TINYSTR,
} value_tag_t;
```

Object refers to a generic pointer (void pointer) that could be used to store a custom type.
Integer, float (32-bit), and string (char pointer) are quite self explanatory.

What about `TINYSTR`? We'll see a bonus optimization that is very compatible with
pointer tagging: *Short String Optimization*.
This trick consists in using a pointer's bits to store directly the chars of a small string,
rather than pointing to a heap allocation containing them.

To simplify packing these tiny strings, we'll represent
them with this type.

```c
// The last byte must be zero
typedef struct {
    char data[8];
} tinystr_t;
```

We will allow only strings up to 7 chars to be optimized with SSO,
but other implementations could be specialized to ASCII chars (7 bits) and store more.

With that out of the way, let's see the union that names this implementation.

```c
typedef struct {
    value_tag_t tag;
    union {
        void *object;
        intptr_t integer;
        float float_;
        char *string;
        tinystr_t tinystr;
    } to;
} value_t;
```

As you can see, the value tag is stored together the union of the value types.
Due to padding, the size of `value_t` will be two words (16 bytes on a 64-bit machine).

To keep all of the implementations we'll see today compatible,
the operations on the values will be hidden behind macros.

```c
#define VALUE_IS_OBJECT(val) ((val).tag == TAG_OBJECT)
#define VALUE_FROM_OBJECT(obj) ((value_t){ .tag = TAG_OBJECT, \
                                .to.object = (void *)(obj) })
#define VALUE_TO_OBJECT(val) ((val).to.object)
```

The operation `VALUE_IS_OBJECT` checks if the value has the object tag.
Similarly, `VALUE_FROM_OBJECT` and `VALUE_TO_OBJECT` are respectively
used to incapsulate or extract an object from a `value_t`.

```c
#define VALUE_IS_INTEGER(val) ((val).tag == TAG_INTEGER)
#define VALUE_FROM_INTEGER(num) ((value_t){ .tag = TAG_INTEGER, \
                                 .to.integer = (num) })
#define VALUE_TO_INTEGER(val) ((val).to.integer)
```

Integers have analogous operations.
Let's define the maximum and minimum values for our integers.

```c
#define INTEGER_MAX INTPTR_MAX
#define INTEGER_MIN INTPTR_MIN
```

Right now these limits coincide with the system ones, as we use the `intptr_t` fully.
But later on we'll have to give up some bits in our representation.

Since you have got the hang of it, these are the operations for the remaining values.

```c
#define VALUE_IS_FLOAT(val) ((val).tag == TAG_FLOAT)
#define VALUE_FROM_FLOAT(num) ((value_t){ .tag = TAG_FLOAT, \
                               .to.float_ = (num) })
#define VALUE_TO_FLOAT(val) ((val).to.float_)
```

```c
#define VALUE_IS_STRING(val) ((val).tag == TAG_STRING)
#define VALUE_FROM_STRING(str) ((value_t){ .tag = TAG_STRING, \
                                .to.string = (char *)(str) })
#define VALUE_TO_STRING(val) ((val).to.string)
```

```c
#define VALUE_IS_TINYSTR(val) ((val).tag == TAG_TINYSTR)
#define VALUE_FROM_TINYSTR(str) ((value_t){ .tag = TAG_TINYSTR, \
                                 .to.tinystr = (str) })
#define VALUE_TO_TINYSTR(val) ((val).to.tinystr)
```

In this implementation, the tag can be accessed very fast
without any further operation (shift/masking).
However, the size overhead is quite detrimental.
Usually, a tagged union made from two words is passed around using two registers.
This effectively halves the number of available processor registers and makes
life harder for optimizing compilers.


## Low bits tagging implementation

It's finally time to implement our tagged pointers.
We'll start with the low bits technique, as it is slightly superior in both
performance and compatibility.
On the other hand, only very few tag bits are usable with this technique.

We need to redefine the tags as specific bit patterns.

```c
// Only the integer tag sets the lowest bit
typedef enum {
    TAG_OBJECT  = 0,        // 0b000
    TAG_INTEGER = 1,        // 0b001
    TAG_FLOAT   = 2,        // 0b010
    TAG_STRING  = 4,        // 0b100
    TAG_TINYSTR = 6,        // 0b110
} value_tag_t;

typedef uintptr_t value_t;
```

Now our `value_t` is simply a `uintptr_t`. Our tags will use at most 3 bits, so
the pointers need to be aligned to at least 8 bytes.
Note that the first bit is dedicated to integers (more about that later).

For good measure, let's add some constants that will come in handy later on.

```c
#define VALUE_BITS 64
#define VALUE_TAG_BITS 3
#define VALUE_TAG_MASK 7    // 0b111
```

The first two values are self-explanatory and `VALUE_TAG_MASK` is simply
a 3-bit mask that we can use to retrieve the tags.

We'll incapsulate the bit operations in these macros to make our life easier.

```c
#define VALUE_GET_TAG(val, mask) \
    (value_tag_t)((value_t)(val) & mask)

#define VALUE_HAS_TAG(val, tag) \
    (VALUE_GET_TAG(val, VALUE_TAG_MASK) == (value_tag_t)(tag))

#define VALUE_SET_TAG(val, tag) ((value_t)(val) | tag)

#define VALUE_UNSET_TAG(val) ((val) & ~VALUE_TAG_MASK)
```

To get the tag we apply a mask to the value in `VALUE_GET_TAG`,
while in `VALUE_HAS_TAG` the given tag is compared with the retrieved one.
`VALUE_SET_TAG` simply ORs the tag and the value.
Lastly, `VALUE_UNSET_TAG` clears the bits of the mask.

Like before, operations on values with `TAG_OBJECT` is quite straightforward.

```c
#define VALUE_IS_OBJECT(val) VALUE_HAS_TAG(val, TAG_OBJECT)
#define VALUE_FROM_OBJECT(obj) VALUE_SET_TAG(obj, TAG_OBJECT)
#define VALUE_TO_OBJECT(val) (void *)VALUE_UNSET_TAG(val)
```

Let's move onto integers, which this time are a bit more complex :wink:.
As I mentioned before, we dedicated the lowest bit to integers.
This means that we can tell apart integer values just by checking
if the first bit is set.

To do this, we need to define a different mask for the first bit.

```c
#define INTEGER_SHIFT 1
#define INTEGER_MASK 1
#define INTEGER_SIGN_BIT ((value_t)1 << (VALUE_BITS - 1))
```

`INTEGER_SHIFT` is the amount of bits the integer values are shifted when tagged.
`INTEGER_SIGN_BIT` is the most significant bit, which is used to store the sign
of integers.

By using the first bit for the tagging, we reduce the range of values representable
by our integers.

```c
#define INTEGER_MAX \
    (((value_t)1 << (VALUE_BITS - 1 - INTEGER_SHIFT)) - 1)

#define INTEGER_MIN \
    -((value_t)1 << (VALUE_BITS - 1 - INTEGER_SHIFT))
```

Concretely, our  63-bit integers can represent numbers from `4611686018427387903`
to `-4611686018427387904`.
Many languages offer some kind of bignum[^bignum] to address the lack of the full 64-bit range.

For the tagging and untagging of integers things get a little complicated,
so let's make two small helper functions.
In a real situation these should be inlined.

```c
#define VALUE_IS_INTEGER(val) \
    (VALUE_GET_TAG(val, INTEGER_MASK) == TAG_INTEGER)

#define VALUE_FROM_INTEGER(num) value_tag_integer(num)
#define VALUE_TO_INTEGER(val) value_untag_integer(val)

value_t value_tag_integer(intptr_t num) {
    assert(num < INTEGER_MIN || num > INTEGER_MAX);
    return (value_t)num << INTEGER_SHIFT
         | (num & INTEGER_SIGN_BIT) | TAG_INTEGER;
}

intptr_t value_untag_integer(value_t val) {
    assert(VALUE_IS_INTEGER(val));
    return (intptr_t)val >> INTEGER_SHIFT
         | (val & INTEGER_SIGN_BIT);
}
```

`VALUE_IS_INTEGER` simply masks the lowest bit and tests if we have a `TAG_INTEGER`.
It's very important to check if a value is an integer, **before** testing for other tags!
Since integers use a shorter mask, applying `VALUE_TAG_MASK` to an integer will yield
extraneous bits in the tag.

In `value_tag_integer` the number is shifted to the left by 1 and ORed with the tag.
Then, if the sign bit was set, it gets ORed back again.
This last step preserves the sign of the number.

Correspondingly, `value_untag_integer` shifts the value to the right by 1.
If the highest bit of the value was set, the resulting integer is ORed with `INTEGER_SIGN_BIT`.

For floats, we will use a similar, albeit much simpler, strategy.
The reason we are not using `double` is because it's non-trivial to truncate bits from it.
On the other hand, a `float` is just 32 bits and fits nicely in our 64-bit pointers.

```c
#define FLOAT_SHIFT 31

#define VALUE_IS_FLOAT(val) VALUE_HAS_TAG(val, TAG_FLOAT)
#define VALUE_FROM_FLOAT(num) value_tag_float(num)
#define VALUE_TO_FLOAT(val) value_untag_float(val)

value_t value_tag_float(float num) {
    union {
        uint32_t raw;
        float num;
    } pun;
    pun.num = num;
    return VALUE_SET_TAG((value_t)pun.raw << FLOAT_SHIFT, TAG_FLOAT);
}

float value_untag_float(value_t val) {
    assert(VALUE_IS_FLOAT(val));
    union {
        uint32_t raw;
        float num;
    } pun;
    pun.raw = (val >> FLOAT_SHIFT) & 0xffffffff;
    return pun.num;
}
```

In `value_tag_float` we make use of a union to type-pun[^punning] the `float` into a `uint32_t`.
Then, the punned integer is shifted to the left by 31 and is tagged.

Conversely, in `value_untag_float` the value gets shifted to the right and masked to get the bottom 32 bits.
The type punning is repeated to get the float back.

Values with `TAG_STRING` behave just like the objects we have seen before.

```c
#define VALUE_IS_STRING(val) VALUE_HAS_TAG(val, TAG_STRING)
#define VALUE_FROM_STRING(str) VALUE_SET_TAG(str, TAG_STRING)
#define VALUE_TO_STRING(val) (char *)VALUE_UNSET_TAG(val)
```

Tiny strings are more interesting.
We use a helper function to tag them by left shifting and ORing together the chars.
The inverse operation consists of right shifting and masking.

```c
#define VALUE_IS_TINYSTR(val) VALUE_HAS_TAG(val, TAG_TINYSTR)
#define VALUE_FROM_TINYSTR(num) value_tag_tinystr(num)
#define VALUE_TO_TINYSTR(val) value_untag_tinystr(val)

value_t value_tag_tinystr(tinystr_t str) {
    assert(str.data[7] == '\0');
    return ((value_t)str.data[0] <<  8)
         | ((value_t)str.data[1] << 16)
         | ((value_t)str.data[2] << 24)
         | ((value_t)str.data[3] << 32)
         | ((value_t)str.data[4] << 40)
         | ((value_t)str.data[5] << 48)
         | ((value_t)str.data[6] << 56)
         | TAG_TINYSTR;
}

tinystr_t value_untag_tinystr(value_t val) {
    assert(VALUE_IS_TINYSTR(val));
    tinystr_t str = {
        (val >>  8) & 0xff,
        (val >> 16) & 0xff,
        (val >> 24) & 0xff,
        (val >> 32) & 0xff,
        (val >> 40) & 0xff,
        (val >> 48) & 0xff,
        (val >> 56) & 0xff,
    };
    return str;
}
```

What are the characteristics of this implementation?
Since accessing the tag and value requires bitwise operations, a tagged union
is slightly more performant.
However, the difference is negligible in practice.
A valid concern is that the number of bits we can use for tags is very limited.

But as we have seen previously, there are many benefits to using a single tagged pointer.


## High bits tagging implementation

The implementation using high bits is really similar to the one we just saw.
As such, lines that didn't change won't be included.

Like before, let's start from adjusting our `value_tag_t` bits.
Integers will have the highest 7th bit dedicated, while
all other values will be within 6 bits.
This trick will allow us to have 63-bit integers.

```c
// Only the integer tag sets the highest bit
typedef enum {
    TAG_OBJECT  = 0,    // 0b_000000
    TAG_INTEGER = 0x40, // 0b1000000
    TAG_FLOAT   = 2,    // 0b_000010
    TAG_STRING  = 3,    // 0b_000011
    TAG_TINYSTR = 4,    // 0b_000100
} value_tag_t;
```

For the tag, we'll use the bits that we discussed during theory (62:57).
We'll shift the value `0x3f` (`0b111111`) and use it as the mask.

```c
#define VALUE_TAG_BITS 6
#define VALUE_TAG_SHIFT (VALUE_BITS - 1 - VALUE_TAG_BITS)
#define VALUE_TAG_MASK ((value_t)0x3f << VALUE_TAG_SHIFT)
```

The helper macros to get and set the tag are tweaked a bit
to account for the shifted tags.

```c
#define VALUE_GET_TAG(val, mask) \
    (value_tag_t)(((value_t)(val) & mask) >> VALUE_TAG_SHIFT)

#define VALUE_SET_TAG(val, tag) \
    ((value_t)(val) | (value_t)tag << VALUE_TAG_SHIFT)
```

Object and string values are the same as before.

For integers, we'll use the highest bit to mark them.
The sign bit will be moved down to bit 62.

```c
#define INTEGER_MASK ((value_t)1 << (VALUE_BITS - 1))
#define INTEGER_SIGN_BIT ((value_t)1 << (VALUE_BITS - 2))

#define INTEGER_MAX (INTEGER_SIGN_BIT - 1)
#define INTEGER_MIN (-INTEGER_SIGN_BIT)
```

As for the range, we still have 63-bit integers like the previous implementation.


```c
value_t value_tag_integer(intptr_t num) {
	assert(num < INTEGER_MIN || num > INTEGER_MAX);
	// Clear the top bits
    value_t val = num & ~(INTEGER_MASK | INTEGER_SIGN_BIT);
    // Move the sign bit
    if (num < 0) val |= INTEGER_SIGN_BIT;
    return VALUE_SET_TAG(val, TAG_INTEGER);
}

intptr_t value_untag_integer(value_t val) {
	assert(VALUE_IS_INTEGER(val));
    intptr_t num = val;
    // If the number is negative, leave the top 1's for the two's complement
    if (!(val & INTEGER_SIGN_BIT)) num &= ~INTEGER_MASK;
    return num;
}
```

In this version of `value_tag_integer` the number gets cleared of its top 2 bits.
If the sign is negative, the value gets ORed with the sign bit.
Then, the value is tagged and returned.

To preserve the two's complement, `value_untag_integer` clears the tag bit
only if the number is positive (thus `INTEGER_SIGN_BIT` is not set).

This time, tagging floats is slightly easier since we don't any shift.

```c
value_t value_tag_float(float num) {
    union {
        uint32_t raw;
        float num;
    } pun;
    pun.num = num;
    return VALUE_SET_TAG(pun.raw, TAG_FLOAT);
}

float value_untag_float(value_t val) {
    assert(VALUE_IS_FLOAT(val));
    union {
        uint32_t raw;
        float num;
    } pun;
    pun.raw = val & 0xffffffff;
    return pun.num;
}
```

For tiny string there is a slight difference in the shifting order.
We are packing the chars from the 1st to the 7th byte,
while before it was from the 2nd byte to the 8th.

```c
value_t value_tag_tinystr(tinystr_t str) {
    assert(str.data[7] == '\0');
    return ((value_t)str.data[0] <<  0)
         | ((value_t)str.data[1] <<  8)
         | ((value_t)str.data[2] << 16)
         | ((value_t)str.data[3] << 24)
         | ((value_t)str.data[4] << 32)
         | ((value_t)str.data[5] << 40)
         | ((value_t)str.data[6] << 48)
         | (value_t)TAG_TINYSTR << VALUE_TAG_SHIFT;
}

tinystr_t value_untag_tinystr(value_t val) {
    assert(VALUE_IS_TINYSTR(val));
    tinystr_t str = {
        (val >>  0) & 0xff,
        (val >>  8) & 0xff,
        (val >> 16) & 0xff,
        (val >> 24) & 0xff,
        (val >> 32) & 0xff,
        (val >> 40) & 0xff,
        (val >> 48) & 0xff,
    };
    return str;
}
```

As compared to the low bits technique, this one has more available bits and
similar (un)tagging performance.
Also, no allocation alignment guarantees are needed.

However, there is a problem with this approach: it's not completely future-proof.
We are still a long way from using the full 64 bits for addressing,
but it's not the first time that something similar happened[^mac24].


## Conclusion

We are finally done with the implementations!

I hope you found this deep dive interesting and insightful.
I went into as many details as I could and the article ended up being lengthy.
Despite that, there is still much more to say.
If you like this topic, you can start with the references.

Now, you should have a good understanding of how addresses are handled,
and how we can take advantage of that in an interpreter.
Nevertheless, heed my warning and don't sprinkle tagged pointers everywhere.

All the implementations were tested on x86_64 and Aarch64 systems.
Here you can find the full code listing: [union.c]({{< fullpath "union.c" >}}), [lowbits.c]({{< fullpath "lowbits.c" >}}),
[highbits.c]({{< fullpath "highbits.c" >}}), and [test.c]({{< fullpath "test.c" >}}).

If you have any questions or would like to report a mistake,
get in touch with me at *{{< email "main@fedang.net" >}}*.

## References
- https://muxup.com/2023q4/storing-data-in-pointers
- https://coredumped.dev/2024/09/09/what-is-the-best-pointer-tagging-method
- https://bernsteinbear.com/blog/small-objects
- https://en.wikichip.org/wiki/arm/tbi
- https://mikeash.com/pyblog/friday-qa-2012-07-27-lets-build-tagged-pointers.html
- https://alwaysprocessing.blog/2023/03/19/objc-tagged-ptr
- https://piotrduperas.com/posts/nan-boxing
- https://www.linaro.org/blog/type-tracking-using-arm-memory-tagging
- https://simonsafar.com/2020/sbcl
- *Representing Type Information in Dinamically Typed Languages* \
    https://www.cs.arizona.edu/sites/default/files/TR93-27.pdf
- https://squoze.org
- https://clementbera.wordpress.com/2018/11/09/64-bits-immediate-floats/


[^taglisp]: https://www.snellman.net/blog/archive/2017-09-04-lisp-numbers
[^lispmach]: https://en.wikipedia.org/wiki/Lisp_machine

[^nan]: https://wingolog.org/archives/2011/05/18/value-representation-in-javascript-implementations

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

[^sbcl]: https://web.archive.org/web/20121014233601/http://sbcl-internals.cliki.net/tag%20bit
[^caml]: https://web.archive.org/web/20090810001400/https://caml.inria.fr/pub/ml-archives/caml-list/2004/07/e86a25aa6c6a6a7d08dd7eb50cfd5d52.fr.html
[^ocaml]: https://dev.realworldocaml.org/runtime-memory-layout.html

[^tagarch]: https://en.wikipedia.org/wiki/Tagged_architecture

[^typed]: Even strongly typed languages like OCaml make use of tagged pointers, \
    https://blog.janestreet.com/what-is-gained-and-lost-with-63-bit-integers

[^go]: https://github.com/golang/go/blob/master/src/runtime/tagptr_64bit.go

[^addressing]: They might still be used in certain circumstances. For example, Linux *usually* marks kernel addresses with a 1 in the MSB.

[^llvm]: https://github.com/llvm/llvm-project/blob/3bd3e06f3fe418e24af65457877f40cee0544f9d/llvm/include/llvm/ADT/PointerIntPair.h#L64

[^linux5page]: https://lwn.net/Articles/717293

[^bignum]: https://en.wikipedia.org/wiki/Arbitrary-precision_arithmetic
[^punning]: https://en.wikipedia.org/wiki/Type_punning#Use_of_union

[^mac24]: *Transitioning from 24-bit to 32-bit Addressing*, \
    https://macgui.com/news/article.php?t=527
