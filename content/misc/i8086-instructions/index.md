+++
date = 2025-10-09T19:36:42+02:00
title = 'Intel 80x86 instructions'
categories = [ "low-level", "osdev" ]
tags = [ "i8086", "real-mode", "x86", "16-bit", "instruction", "opcode" ]
+++

16-bit instruction set for the x86 architecture.

<!--more-->

| Name    | Description                                        | Introduced in | Encodings                                 |
|:--------|:---------------------------------------------------|:--------------|:-----------------------------------------:|
| AAA     | ASCII Adjust After Addition                        | 8086 *        | 1 &nbsp; [see]({{< ref "#aaa" >}}) |
| AAD     | ASCII Adjust Register AX Before Division           | 8086 *        | 1 &nbsp; [see]({{< ref "#aad" >}}) |
| AAM     | ASCII Adjust AX Register After Multiplication      | 8086          | 1 &nbsp; [see]({{< ref "#aam" >}}) |
| AAS     | ASCII Adjust AL Register After Substraction        | 8086          | 1 &nbsp; [see]({{< ref "#aas" >}}) |
| ADC     | Add Integers with Carry                            | 8086          | 8 &nbsp; [see]({{< ref "#adc" >}}) |
| ADD     | Add Integers                                       | 8086          | 8 &nbsp; [see]({{< ref "#add" >}}) |
| AND     | Logical AND                                        | 8086          | 8 &nbsp; [see]({{< ref "#and" >}}) |
| ARPL    | Adjust Requester Privilege Level of Selector       | 80286         | 1 &nbsp; [see]({{< ref "#arpl" >}}) |
| BOUND   | Check Array Index Against Bounds                   | 80186         | 1 &nbsp; [see]({{< ref "#bound" >}}) |
| BSF     | Bit Scan Forward                                   | 80386         | 1 &nbsp; [see]({{< ref "#bsf" >}}) |
| BSR     | Bit Scan Reverse                                   | 80386         | 1 &nbsp; [see]({{< ref "#bsr" >}}) |
| BSWAP   | Byte Swap                                          | 80486         | 1 &nbsp; [see]({{< ref "#bswap" >}}) |
| BT      | Bit Test                                           | 80386         | 1 &nbsp; [see]({{< ref "#bt" >}}) |
| BTC     | Bit Test and Complement                            | 80386         | 1 &nbsp; [see]({{< ref "#btc" >}}) |
| BTR     | Bit Test and Reset                                 | 80386         | 1 &nbsp; [see]({{< ref "#btr" >}}) |
| BTS     | Bit Test and Set                                   | 80386         | 1 &nbsp; [see]({{< ref "#bts" >}}) |
| CBW     | Convert Byte to Word                               | 8086          | 1 &nbsp; [see]({{< ref "#cbw" >}}) |
| CDQ     | Convert Doubleword to Quad-Word                    | 80386         | 1 &nbsp; [see]({{< ref "#cdq" >}}) |
| CLC     | Clear Carry Flag (CF)                              | 8086          | 1 &nbsp; [see]({{< ref "#clc" >}}) |
| CLD     | Clear Direction Flag (DF)                          | 8086          | 1 &nbsp; [see]({{< ref "#cld" >}}) |
| CLI     | Clear Interrupt Flag (IF)                          | 8086          | 1 &nbsp; [see]({{< ref "#cli" >}}) |
| CLTS    | Clear Task-Switched Flag in CR0                    | 80286         | 1 &nbsp; [see]({{< ref "#clts" >}}) |
| CMC     | Complementer Carry Flag (CF)                       | 8086          | 1 &nbsp; [see]({{< ref "#cmc" >}}) |
| CMOVcc  | Conditional Move                                   | Pentium Pro   | 1 &nbsp; [see]({{< ref "#cmovcc" >}}) |
| CMP     | Compare                                            | 8086          | 1 &nbsp; [see]({{< ref "#cmp" >}}) |
| CMPSB   | Compare String - Byte                              | 8086          | 1 &nbsp; [see]({{< ref "#cmpsb" >}}) |
| CMPSW   | Compare String - Word                              | 8086          | 1 &nbsp; [see]({{< ref "#cmpsw" >}}) |
| CMPSD   | Compare String - Doubleword                        | 80386         | 1 &nbsp; [see]({{< ref "#cmpsd" >}}) |
| CMPXCHG | Compare and Exchange                               | 80486         | 1 &nbsp; [see]({{< ref "#cmpxchg" >}}) |
| CPUID   | CPU Identification Code                            | Pentium       | 1 &nbsp; [see]({{< ref "#cpuid" >}}) |
| CWD     | Convert Word to Doubleword                         | 8086          | 1 &nbsp; [see]({{< ref "#cwd" >}}) |
| CWDE    | Convert Word to Extended Doubleword                | 80386         | 1 &nbsp; [see]({{< ref "#cwde" >}}) |
| DAA     | Decimal Adjust Register After Addition             | 8086          | 1 &nbsp; [see]({{< ref "#daa" >}}) |
| DAS     | Decimal Adjust AL Register After Substraction      | 8086          | 1 &nbsp; [see]({{< ref "#das" >}}) |
| DEC     | Decrement by One                                   | 8086          | 1 &nbsp; [see]({{< ref "#dec" >}}) |
| DIV     | Unsigned Integer Divide                            | 8086          | 1 &nbsp; [see]({{< ref "#div" >}}) |
| ENTER   | Make Stack Frame for Procedure Parameter           | 80186         | 1 &nbsp; [see]({{< ref "#enter" >}}) |
| HLT     | Halt Processor                                     | 8086          | 1 &nbsp; [see]({{< ref "#hlt" >}}) |
| IDIV    | Signed Integer Divide                              | 8086          | 1 &nbsp; [see]({{< ref "#idiv" >}}) |
| IMUL    | Signed Integer Multiply                            | 8086 *        | 1 &nbsp; [see]({{< ref "#imul" >}}) |
| IN      | Input from Port                                    | 8086          | 1 &nbsp; [see]({{< ref "#in" >}}) |
| INC     | Increment by One                                   | 8086          | 1 &nbsp; [see]({{< ref "#inc" >}}) |
| INSB    | Input Byte from Port                               | 80186         | 1 &nbsp; [see]({{< ref "#insb" >}}) |
| INSW    | Input Word from Port                               | 80186         | 1 &nbsp; [see]({{< ref "#insw" >}}) |
| INSD    | Input Doubleword from Port                         | 80386         | 1 &nbsp; [see]({{< ref "#insd" >}}) |
| INT     | Call to Interrupt Procedure                        | 8086          | 1 &nbsp; [see]({{< ref "#int" >}}) |
| INTO    | Interrupt on Overflow                              | 8086          | 1 &nbsp; [see]({{< ref "#into" >}}) |
| INVD    | Invalidate data cache                              | 80486         | 1 &nbsp; [see]({{< ref "#invd" >}}) |
| INVLPG  | Invalidate TBL entry                               | 80486         | 1 &nbsp; [see]({{< ref "#invlpg" >}}) |
| IRET    | Return from Interrupt                              | 8086          | 1 &nbsp; [see]({{< ref "#iret" >}}) |
| LAHF    | Load Flags into AH Register                        | 8086          | 1 &nbsp; [see]({{< ref "#lahf" >}}) |
| LAR     | Load Access Rights Byte                            | 80286         | 1 &nbsp; [see]({{< ref "#lar" >}}) |
| LDS     | Load Pointer Using DS                              | 8086 *        | 1 &nbsp; [see]({{< ref "#lds" >}}) |
| LES     | Load Pointer Using ES                              | 8086 *        | 1 &nbsp; [see]({{< ref "#les" >}}) |
| LFS     | Load Pointer Using FS                              | 80386         | 1 &nbsp; [see]({{< ref "#lfs" >}}) |
| LGS     | Load Pointer Using GS                              | 80386         | 1 &nbsp; [see]({{< ref "#lgs" >}}) |
| LSS     | Load Pointer Using SS                              | 80386         | 1 &nbsp; [see]({{< ref "#lss" >}}) |
| LSS     | Load Pointer Using SS                              | 80386         | 1 &nbsp; [see]({{< ref "#lss" >}}) |
| LEA     | Load Effective Address                             | 8086          | 1 &nbsp; [see]({{< ref "#lea" >}}) |
| LEAVE   | High Level Procedure Exit                          | 80186         | 1 &nbsp; [see]({{< ref "#leave" >}}) |
| LGDT    | Load Global Descriptor Table                       | 80286         | 1 &nbsp; [see]({{< ref "#lgdt" >}}) |
| LIDT    | Load Interrupt Descriptor Table                    | 80286         | 1 &nbsp; [see]({{< ref "#lidt" >}}) |
| LLDT    | Load Local Descriptor Table                        | 80286         | 1 &nbsp; [see]({{< ref "#lldt" >}}) |
| LMSW    | Load Machine Status Word                           | 80286         | 1 &nbsp; [see]({{< ref "#lmsw" >}}) |
| LODSB   | Load Byte String                                   | 8086          | 1 &nbsp; [see]({{< ref "#lodsb" >}}) |
| LODSW   | Load Word String                                   | 8086          | 1 &nbsp; [see]({{< ref "#lodsw" >}}) |
| LODSD   | Load Doubleword String                             | 80386         | 1 &nbsp; [see]({{< ref "#lodsd" >}}) |
| LSL     | Load Segment Limit                                 | 80286         | 1 &nbsp; [see]({{< ref "#lsl" >}}) |
| LTR     | Load Task Register                                 | 80286         | 1 &nbsp; [see]({{< ref "#ltr" >}}) |
| MOV     | Move Data                                          | 8086 *        | 1 &nbsp; [see]({{< ref "#mov" >}}) |
| MOVSB   | Move Byte String                                   | 8086          | 1 &nbsp; [see]({{< ref "#movsb" >}}) |
| MOVSW   | Move Word String                                   | 8086          | 1 &nbsp; [see]({{< ref "#movsw" >}}) |
| MOVSD   | Move Doubleword String                             | 80386         | 1 &nbsp; [see]({{< ref "#movsd" >}}) |
| MOVSX   | Move with Sign Extension                           | 80386         | 1 &nbsp; [see]({{< ref "#movsx" >}}) |
| MOVZX   | Move with Zero Extension                           | 80386         | 1 &nbsp; [see]({{< ref "#movzx" >}}) |
| MUL     | Unsigned Integer Multiply                          | 8086          | 1 &nbsp; [see]({{< ref "#mul" >}}) |
| NEG     | Negate (Two's Complement)                          | 8086          | 1 &nbsp; [see]({{< ref "#neg" >}}) |
| NOP     | Do Nothing                                         | 8086          | 1 &nbsp; [see]({{< ref "#nop" >}}) |
| NOT     | Negate (One's Complement)                          | 8086          | 1 &nbsp; [see]({{< ref "#not" >}}) |
| OR      | Logical Inclusive OR                               | 8086          | 1 &nbsp; [see]({{< ref "#or" >}}) |
| OUT     | Output To Port                                     | 8086          | 1 &nbsp; [see]({{< ref "#out" >}}) |
| OUTSB   | Output Byte from Port                              | 80186         | 1 &nbsp; [see]({{< ref "#outsb" >}}) |
| OUTSW   | Output Word from Port                              | 80186         | 1 &nbsp; [see]({{< ref "#outsw" >}}) |
| OUTSD   | Output Doubleword from Port                        | 80386         | 1 &nbsp; [see]({{< ref "#outsd" >}}) |
| POP     | Pop a Word from the Stack                          | 8086 *        | 1 &nbsp; [see]({{< ref "#pop" >}}) |
| POPA    | Pop All Registers                                  | 80386         | 1 &nbsp; [see]({{< ref "#popa" >}}) |
| POPF    | Pop FLAGS                                          | 8086          | 1 &nbsp; [see]({{< ref "#popf" >}}) |
| PUSH    | Push Operand onto Stack                            | 8086 *        | 1 &nbsp; [see]({{< ref "#push" >}}) |
| PUSHW   | Push Word                                          | 80286         | 1 &nbsp; [see]({{< ref "#pushw" >}}) |
| PUSHD   | Push Doubleword                                    | 80386         | 1 &nbsp; [see]({{< ref "#pushd" >}}) |
| PUSHA   | Push All Registers                                 | 80186         | 1 &nbsp; [see]({{< ref "#pusha" >}}) |
| PUSHF   | Push FLAGS                                         | 8086          | 1 &nbsp; [see]({{< ref "#pushf" >}}) |
| RCL     | Rotate Left through Carry - Uses CF for Extension  | 8086 *        | 1 &nbsp; [see]({{< ref "#rcl" >}}) |
| RCR     | Rotate Right through Carry - Uses CF for Extension | 8086 *        | 1 &nbsp; [see]({{< ref "#rcr" >}}) |
| RDMSR   | Read from Model Specific Register                  | Pentium       | 1 &nbsp; [see]({{< ref "#rdmsr" >}}) |
| RET     | Return from Procedure                              | 8086          | 1 &nbsp; [see]({{< ref "#ret" >}}) |
| RDPMC   | Read Performance Monitor Counter                   | Pentium Pro   | 1 &nbsp; [see]({{< ref "#rdpmc" >}}) |
| ROL     | Rotate Left through Carry - Wrap bits around       | 8086 *        | 1 &nbsp; [see]({{< ref "#rol" >}}) |
| ROR     | Rotate Right through Carry - Wrap bits around      | 8086 *        | 1 &nbsp; [see]({{< ref "#ror" >}}) |
| RSM     | Return from System Management mode                 | Pentium       | 1 &nbsp; [see]({{< ref "#rsm" >}}) |
| SALC    | Set AL on Carry                                    | Pentium Pro   | 1 &nbsp; [see]({{< ref "#salc" >}}) |
| SAHF    | Load Flags into AH Register                        | 8086          | 1 &nbsp; [see]({{< ref "#sahf" >}}) |
| SAL     | Shift Arithmetic Left                              | 8086 *        | 1 &nbsp; [see]({{< ref "#sal" >}}) |
| SAR     | Shift Arithmetic Right                             | 8086 *        | 1 &nbsp; [see]({{< ref "#sar" >}}) |
| SETcc   | Set Byte on Condition Code                         | 80386         | 1 &nbsp; [see]({{< ref "#setcc" >}}) |
| SHL     | Shift Logic Left                                   | 8086 *        | 1 &nbsp; [see]({{< ref "#shl" >}}) |
| SHR     | Shift Logic Right                                  | 8086 *        | 1 &nbsp; [see]({{< ref "#shr" >}}) |
| SBB     | Substract Integers with Borrow                     | 8086          | 1 &nbsp; [see]({{< ref "#sbb" >}}) |
| SCASB   | Compare Byte String                                | 8086          | 1 &nbsp; [see]({{< ref "#scasb" >}}) |
| SCASW   | Compare Word String                                | 8086          | 1 &nbsp; [see]({{< ref "#scasw" >}}) |
| SGDT    | Store Global Descriptor Table                      | 80286         | 1 &nbsp; [see]({{< ref "#sgdt" >}}) |
| SHLD    | Double Precision Shift Left                        | 80386         | 1 &nbsp; [see]({{< ref "#shld" >}}) |
| SHRD    | Double Precision Shift Right                       | 80386         | 1 &nbsp; [see]({{< ref "#shrd" >}}) |
| SIDT    | Store Interrupt Descriptor Table                   | 80286         | 1 &nbsp; [see]({{< ref "#sidt" >}}) |
| SLDT    | Store Local Descriptor Table                       | 80286         | 1 &nbsp; [see]({{< ref "#sldt" >}}) |
| SMSW    | Store Machine Status Word                          | 80286         | 1 &nbsp; [see]({{< ref "#smsw" >}}) |
| STC     | Set Carry Flag (CF)                                | 8086          | 1 &nbsp; [see]({{< ref "#stc" >}}) |
| STD     | Set Direction Flag (DF)                            | 8086          | 1 &nbsp; [see]({{< ref "#std" >}}) |
| STI     | Set Interrupt Flag (IF)                            | 8086          | 1 &nbsp; [see]({{< ref "#sti" >}}) |
| STOSB   | Store String Data Byte                             | 8086          | 1 &nbsp; [see]({{< ref "#stosb" >}}) |
| STOSW   | Store String Data Word                             | 8086          | 1 &nbsp; [see]({{< ref "#stosw" >}}) |
| STOSD   | Store String Data Doubleword                       | 80386         | 1 &nbsp; [see]({{< ref "#stosd" >}}) |
| SUB     | Subtract                                           | 8086          | 1 &nbsp; [see]({{< ref "#sub" >}}) |
| TEST    | Test Operands                                      | 8086          | 1 &nbsp; [see]({{< ref "#test" >}}) |
| VERR    | Verify Read                                        | 80286         | 1 &nbsp; [see]({{< ref "#verr" >}}) |
| VERW    | Verify Write                                       | 80286         | 1 &nbsp; [see]({{< ref "#verw" >}}) |
| WAIT    | Wait for FPU                                       | 8086          | 1 &nbsp; [see]({{< ref "#wait" >}}) |
| WBINVD  | Write Back and Invalidate Data Cache               | 80486         | 1 &nbsp; [see]({{< ref "#wbinvd" >}}) |
| WRMSR   | Write to Model Specific Register                   | Pentium       | 1 &nbsp; [see]({{< ref "#wrmsr" >}}) |
| XADD    | Exchange and Add                                   | 80486         | 1 &nbsp; [see]({{< ref "#xadd" >}}) |
| XCHG    | Exchange                                           | 8086          | 1 &nbsp; [see]({{< ref "#xchg" >}}) |
| XLAT    | Translate                                          | 8086          | 1 &nbsp; [see]({{< ref "#xlat" >}}) |
| XOR     | Exclusive-OR                                       | 8086          | 1 &nbsp; [see]({{< ref "#xor" >}}) |
| CALL    | Call a Procedure                                   | 8086          | 1 &nbsp; [see]({{< ref "#call" >}}) |
| Jcc     | Jump on Some Condition Code                        | 8086 *        | 1 &nbsp; [see]({{< ref "#jcc" >}}) |
| JCXZ    | Jump if CX is Zero                                 | 8086          | 1 &nbsp; [see]({{< ref "#jcxz" >}}) |
| JMP     | Jump                                               | 8086          | 1 &nbsp; [see]({{< ref "#jmp" >}}) |
| LOOP    | Loop while CX is not Zero                          | 8086          | 1 &nbsp; [see]({{< ref "#loop" >}}) |
| LOOPZ   | Loop while Zero                                    | 8086          | 1 &nbsp; [see]({{< ref "#loopz" >}}) |
| LOOPNZ  | Loop while not Zero                                | 8086          | 1 &nbsp; [see]({{< ref "#loopnz" >}}) |
|         |                                                    |               |                                       |
| LOCK    | Assert Lock Prefix                                 | 8086          | 1 &nbsp; [see]({{< ref "#lock-signal" >}}) |
| REP     | Repeat String Operation Prefix                     | 8086          | 1 &nbsp; [see]({{< ref "#repeat" >}}) |
| REPZ    | Repeat String Operation Prefix while Zero          | 8086          | 1 &nbsp; [see]({{< ref "#repeat" >}}) |
| REPNZ   | Repeat String Operation Prefix while not Zero      | 8086          | 1 &nbsp; [see]({{< ref "#repeat" >}}) |
| CS      | CS Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#segment-override" >}}) |
| DS      | DS Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#segment-override" >}}) |
| ES      | ES Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#segment-override" >}}) |
| FS      | FS Segment Override Prefix                         | 80386         | 1 &nbsp; [see]({{< ref "#segment-override" >}}) |
| GS      | GS Segment Override Prefix                         | 80386         | 1 &nbsp; [see]({{< ref "#segment-override" >}}) |
| SS      | SS Segment Override Prefix                         | 8086          | 1 &nbsp; [see]({{< ref "#segment-override" >}}) |
{.width-100}

\*: The instruction was extended in later processors


## Instructions

### AAA
### AAD
### AAM
### AAS
### ADC
### ADD
### AND
### ARPL
### BOUND
### BSF
### BSR
### BSWAP
### BT
### BTC
### BTR
### BTS
### CBW
### CDQ
### CLC
### CLD
### CLI
### CLTS
### CMC
### CMOVcc
### CMP
### CMPSB
### CMPSW
### CMPSD
### CMPXCHG
### CPUID
### CWD
### CWDE
### DAA
### DAS
### DEC
### DIV
### ENTER
### HLT
### IDIV
### IMUL
### IN
### INC
### INSB
### INSW
### INSD
### INT
### INTO
### INVD
### INVLPG
### IRET
### LAHF
### LAR
### LDS
### LES
### LFS
### LGS
### LSS
### LSS
### LEA
### LEAVE
### LGDT
### LIDT
### LLDT
### LMSW
### LODSB
### LODSW
### LODSD
### LSL
### LTR
### MOV
### MOVSB
### MOVSW
### MOVSD
### MOVSX
### MOVZX
### MUL
### NEG
### NOP
### NOT
### OR
### OUT
### OUTSB
### OUTSW
### OUTSD
### POP
### POPA
### POPF
### PUSH
### PUSHW
### PUSHD
### PUSHA
### PUSHF
### RCL
### RCR
### RDMSR
### RET
### RDPMC
### ROL
### ROR
### RSM
### SALC
### SAHF
### SAL
### SAR
### SETcc
### SHL
### SHR
### SBB
### SCASB
### SCASW
### SGDT
### SHLD
### SHRD
### SIDT
### SLDT
### SMSW
### STC
### STD
### STI
### STOSB
### STOSW
### STOSD
### SUB
### TEST
### VERR
### VERW
### WAIT
### WBINVD
### WRMSR
### XADD
### XCHG
### XLAT
### XOR
### CALL
### Jcc
### JCXZ
### JMP
### LOOP
### LOOPZ
### LOOPNZ

## Prefixes

## Lock Signal

| Prefix | Encoding       |
|--------|----------------|
| LOCK:  | F0 &nbsp;&nbsp;  (11110000) |

## Repeat

| Prefix | Encoding       |
|--------|----------------|
| REP    | F3 &nbsp;&nbsp; (11110011) |
| REPZ   | F3 &nbsp;&nbsp; (11110011) |
| REPNZ  | F2 &nbsp;&nbsp; (11110010) |

## Segment Override

| Prefix | Encoding       |
|--------|----------------|
| CS:    | 2E &nbsp;&nbsp;  (00101110) |
| DS:    | 3E &nbsp;&nbsp;  (00111110) |
| ES:    | 26 &nbsp;&nbsp;  (00100110) |
| FS:    | 64 &nbsp;&nbsp;  (01100100) |
| GS:    | 65 &nbsp;&nbsp;  (01100101) |
| SS:    | 36 &nbsp;&nbsp;  (00110110) |
{.width-100}

## References

- https://www.retroparla.com/wp-content/uploads/2024/03/8086.pdf
- https://bitsavers.org/components/intel/8086/9800722-03_The_8086_Family_Users_Manual_Oct79.pdf
- https://web.archive.org/web/20230311143236/https://www.ic.unicamp.br/~celio/mc404/opcodes.html
- https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
