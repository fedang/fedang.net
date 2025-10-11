+++
date = 2025-10-09T19:36:42+02:00
title = 'Intel 80x86 instructions'
categories = [ "low-level", "osdev" ]
tags = [ "i8086", "real-mode", "x86", "16-bit", "instruction", "opcode" ]
draft = true
+++

Complete instruction set for the 16-bit x86 processor.

<!--more-->

| Name    | Description                                        | Introduced in | Encodings                                 |
|:--------|:---------------------------------------------------|:--------------|:-----------------------------------------:|
| AAA     | ASCII Adjust After Addition                        | 8086 *        | 1 &nbsp; [{{< icon jump-to smaller >}}]({{< ref "#aaa" >}}) |
| AAD     | ASCII Adjust Register AX Before Division           | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| AAM     | ASCII Adjust AX Register After Multiplication      | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| AAS     | ASCII Adjust AL Register After Substraction        | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| ADC     | Add Integers with Carry                            | 8086          | 8 &nbsp; [see]({{< ref "#aaa" >}}) |
| ADD     | Add Integers                                       | 8086          | 8 &nbsp; [see]({{< ref "#aaa" >}}) |
| AND     | Logical AND                                        | 8086          | 8 &nbsp; [see]({{< ref "#aaa" >}}) |
| ARPL    | Adjust Requester Privilege Level of Selector       | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BOUND   | Check Array Index Against Bounds                   | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BSF     | Bit Scan Forward                                   | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BSR     | Bit Scan Reverse                                   | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BSWAP   | Byte Swap                                          | 80486         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BT      | Bit Test                                           | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BTC     | Bit Test and Complement                            | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BTR     | Bit Test and Reset                                 | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| BTS     | Bit Test and Set                                   | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CBW     | Convert Byte to Word                               | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CDQ     | Convert Doubleword to Quad-Word                    | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CLC     | Clear Carry Flag (CF)                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CLD     | Clear Direction Flag (DF)                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CLI     | Clear Interrupt Flag (IF)                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CLTS    | Clear Task-Switched Flag in CR0                    | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMC     | Complementer Carry Flag (CF)                       | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMOVcc  | Conditional Move                                   | Pentium Pro   | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMP     | Compare                                            | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMPSB   | Compare String - Byte                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMPSW   | Compare String - Word                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMPSD   | Compare String - Doubleword                        | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CMPXCHG | Compare and Exchange                               | 80486         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CPUID   | CPU Identification Code                            | Pentium       | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CWD     | Convert Word to Doubleword                         | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CWDE    | Convert Word to Extended Doubleword                | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| DAA     | Decimal Adjust Register After Addition             | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| DAS     | Decimal Adjust AL Register After Substraction      | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| DEC     | Decrement by One                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| DIV     | Unsigned Integer Divide                            | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| ENTER   | Make Stack Frame for Procedure Parameter           | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| HLT     | Halt Processor                                     | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| IDIV    | Signed Integer Divide                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| IMUL    | Signed Integer Multiply                            | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| IN      | Input from Port                                    | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INC     | Increment by One                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INSB    | Input Byte from Port                               | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INSW    | Input Word from Port                               | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INSD    | Input Doubleword from Port                         | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INT     | Call to Interrupt Procedure                        | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INTO    | Interrupt on Overflow                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INVD    | Invalidate data cache                              | 80486         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| INVLPG  | Invalidate TBL entry                               | 80486         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| IRET    | Return from Interrupt                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LAHF    | Load Flags into AH Register                        | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LAR     | Load Access Rights Byte                            | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LDS     | Load Pointer Using DS                              | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LES     | Load Pointer Using ES                              | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LFS     | Load Pointer Using FS                              | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LGS     | Load Pointer Using GS                              | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LSS     | Load Pointer Using SS                              | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LSS     | Load Pointer Using SS                              | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LEA     | Load Effective Address                             | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LEAVE   | High Level Procedure Exit                          | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LGDT    | Load Global Descriptor Table                       | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LIDT    | Load Interrupt Descriptor Table                    | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LLDT    | Load Local Descriptor Table                        | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LMSW    | Load Machine Status Word                           | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LODSB   | Load Byte String                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LODSW   | Load Word String                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LODSD   | Load Doubleword String                             | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LSL     | Load Segment Limit                                 | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LTR     | Load Task Register                                 | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MOV     | Move Data                                          | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MOVSB   | Move Byte String                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MOVSW   | Move Word String                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MOVSD   | Move Doubleword String                             | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MOVSX   | Move with Sign Extension                           | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MOVZX   | Move with Zero Extension                           | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| MUL     | Unsigned Integer Multiply                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| NEG     | Negate (Two's Complement)                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| NOP     | Do Nothing                                         | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| NOT     | Negate (One's Complement)                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| OR      | Logical Inclusive OR                               | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| OUT     | Output To Port                                     | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| OUTSB   | Output Byte from Port                              | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| OUTSW   | Output Word from Port                              | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| OUTSD   | Output Doubleword from Port                        | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| POP     | Pop a Word from the Stack                          | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| POPA    | Pop All Registers                                  | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| POPF    | Pop FLAGS                                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| PUSH    | Push Operand onto Stack                            | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| PUSHW   | Push Word                                          | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| PUSHD   | Push Doubleword                                    | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| PUSHA   | Push All Registers                                 | 80186         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| PUSHF   | Push FLAGS                                         | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| RCL     | Rotate Left through Carry - Uses CF for Extension  | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| RCR     | Rotate Right through Carry - Uses CF for Extension | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| RDMSR   | Read from Model Specific Register                  | Pentium       | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| RET     | Return from Procedure                              | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| RDPMC   | Read Performance Monitor Counter                   | Pentium Pro   | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| ROL     | Rotate Left through Carry - Wrap bits around       | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| ROR     | Rotate Right through Carry - Wrap bits around      | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| RSM     | Return from System Management mode                 | Pentium       | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SALC    | Set AL on Carry                                    | Pentium Pro   | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SAHF    | Load Flags into AH Register                        | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SAL     | Shift Arithmetic Left                              | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SAR     | Shift Arithmetic Right                             | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SETcc   | Set Byte on Condition Code                         | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SHL     | Shift Logic Left                                   | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SHR     | Shift Logic Right                                  | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SBB     | Substract Integers with Borrow                     | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SCASB   | Compare Byte String                                | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SCASW   | Compare Word String                                | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SGDT    | Store Global Descriptor Table                      | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SHLD    | Double Precision Shift Left                        | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SHRD    | Double Precision Shift Right                       | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SIDT    | Store Interrupt Descriptor Table                   | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SLDT    | Store Local Descriptor Table                       | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SMSW    | Store Machine Status Word                          | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| STC     | Set Carry Flag (CF)                                | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| STD     | Set Direction Flag (DF)                            | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| STI     | Set Interrupt Flag (IF)                            | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| STOSB   | Store String Data Byte                             | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| STOSW   | Store String Data Word                             | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| STOSD   | Store String Data Doubleword                       | 80386         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| SUB     | Subtract                                           | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| TEST    | Test Operands                                      | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| VERR    | Verify Read                                        | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| VERW    | Verify Write                                       | 80286         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| WAIT    | Wait for FPU                                       | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| WBINVD  | Write Back and Invalidate Data Cache               | 80486         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| WRMSR   | Write to Model Specific Register                   | Pentium       | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| XADD    | Exchange and Add                                   | 80486         | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| XCHG    | Exchange                                           | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| XLAT    | Translate                                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| XOR     | Exclusive-OR                                       | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| CALL    | Call a Procedure                                   | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| Jcc     | Jump on Some Condition Code                        | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| JCXZ    | Jump if CX is Zero                                 | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| JMP     | Jump                                               | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LOOP    | Loop while CX is not Zero                          | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LOOPZ   | Loop while Zero                                    | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LOOPNZ  | Loop while not Zero                                | 8086          | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| LOCK    | Assert Lock Prefix                                 | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| REP     | Repeat String Operation Prefix                     | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| REPZ    | Repeat String Operation Prefix while Zero          | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| REPNZ   | Repeat String Operation Prefix while not Zero      | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| CS      | CS Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| DS      | DS Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| ES      | ES Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| FS      | FS Segment Override Prefix                         | 80386         | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| GS      | GS Segment Override Prefix                         | 80386         | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
| SS      | SS Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#prefixes" >}}) |
{.width-100}

\*: The instruction was extended in later processors


## Instructions

### AAA
...


### Prefixes


## References

- https://www.retroparla.com/wp-content/uploads/2024/03/8086.pdf
- https://bitsavers.org/components/intel/8086/9800722-03_The_8086_Family_Users_Manual_Oct79.pdf
- https://web.archive.org/web/20230311143236/https://www.ic.unicamp.br/~celio/mc404/opcodes.html
- https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
