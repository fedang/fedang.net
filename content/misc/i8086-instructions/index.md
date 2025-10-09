+++
date = 2025-10-09T19:36:42+02:00
title = 'Intel 80x86 instructions'
categories = [ "low-level", "osdev" ]
tags = [ "i8086", "real-mode", "x86", "16-bit", "instruction", "opcode" ]
draft = true
+++

Complete instruction set for the 16-bit x86 processor.

<!--more-->

## Instruction table

| Name    | Description                                                      | Processor | Encodings                                 |
|:--------|:-----------------------------------------------------------------|:----------|:-----------------------------------------:|
| AAA     | ASCII Adjust After Addition                                      | 8086 *    | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| AAD     | ASCII Adjust Register AX Before Division                         | 8086 *    | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| AAM     | ASCII Adjust AX Register After Multiplication                    | 8086      | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| AAS     | ASCII Adjust AL Register After Substraction                      | 8086      | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| ADC     | Add Integers with Carry                                          | 8086      | 8 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| ADD     | Add Integers                                                     | 8086      | 8 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| AND     | Logical AND                                                      | 8086      | 8 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| ARPL    | Adjust Requester Privilege Level of Selector                     | 80286     | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| BOUND   | Check Array Index Against Bounds                                 | 80186     | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| BSF     | Bit Scan Forward                                                 | 80386     | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| BSR     | Bit Scan Reverse                                                 | 80386     | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| BSWAP   | Byte Swap                                                        | 80486     | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
| BT      | Bit Test                                                         | 80386     | 1 &nbsp;&nbsp; [see]({{< ref "#aaa" >}})  |
|         |                                                                  |           |                                           |

\*: The instruction was extended in later processors

## Instruction set

### AAA
...


## References

- https://www.ic.unicamp.br/~celio/mc404/opcodes.html
- https://www.retroparla.com/wp-content/uploads/2024/03/8086.pdf
- https://bitsavers.org/components/intel/8086/9800722-03_The_8086_Family_Users_Manual_Oct79.pdf
- https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
