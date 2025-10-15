+++
date = 2025-10-09T19:36:42+02:00
title = 'Intel x86 16-bit instructions'
categories = [ "low-level", "osdev" ]
tags = [ "x86", "real-mode", "i8086", "16-bit", "instruction", "opcode" ]
+++

16-bit instruction set for the x86 architecture.

<!--more-->

<details open>
<summary>Instruction list</summary>

| Name                             | Description                                        | Introduced    |
|:---------------------------------|:---------------------------------------------------|:--------------|
| [AAA]({{< ref "#aaa" >}})        | ASCII Adjust After Addition                        | 8086          |
| [AAD]({{< ref "#aad" >}})        | ASCII Adjust Register AX Before Division           | 8086 *        |
| [AAM]({{< ref "#aam" >}})        | ASCII Adjust AX Register After Multiplication      | 8086 *        |
| [AAS]({{< ref "#aas" >}})        | ASCII Adjust AL Register After Substraction        | 8086          |
| [ADC]({{< ref "#adc" >}})        | Add Integers with Carry                            | 8086          |
| [ADD]({{< ref "#add" >}})        | Add Integers                                       | 8086          |
| [AND]({{< ref "#and" >}})        | Logical AND                                        | 8086          |
| [ARPL]({{< ref "#arpl" >}})      | Adjust Requester Privilege Level of Selector       | 80286         |
| [BOUND]({{< ref "#bound" >}})    | Check Array Index Against Bounds                   | 80186         |
| [BSF]({{< ref "#bsf" >}})        | Bit Scan Forward                                   | 80386         |
| [BSR]({{< ref "#bsr" >}})        | Bit Scan Reverse                                   | 80386         |
| [BSWAP]({{< ref "#bswap" >}})    | Byte Swap                                          | 80486         |
| [BT]({{< ref "#bt" >}})          | Bit Test                                           | 80386         |
| [BTC]({{< ref "#btc" >}})        | Bit Test and Complement                            | 80386         |
| [BTR]({{< ref "#btr" >}})        | Bit Test and Reset                                 | 80386         |
| [BTS]({{< ref "#bts" >}})        | Bit Test and Set                                   | 80386         |
| [CALL]({{< ref "#call" >}})      | Call a Procedure                                   | 8086          |
| [CBW]({{< ref "#cbw" >}})        | Convert Byte to Word                               | 8086          |
| [CDQ]({{< ref "#cdq" >}})        | Convert Doubleword to Quad-Word                    | 80386         |
| [CLC]({{< ref "#clc" >}})        | Clear Carry Flag (CF)                              | 8086          |
| [CLD]({{< ref "#cld" >}})        | Clear Direction Flag (DF)                          | 8086          |
| [CLI]({{< ref "#cli" >}})        | Clear Interrupt Flag (IF)                          | 8086          |
| [CLTS]({{< ref "#clts" >}})      | Clear Task-Switched Flag in CR0                    | 80286         |
| [CMC]({{< ref "#cmc" >}})        | Complementer Carry Flag (CF)                       | 8086          |
| [CMOVcc]({{< ref "#cmovcc" >}})  | Conditional Move                                   | Pentium Pro   |
| [CMP]({{< ref "#cmp" >}})        | Compare Operands                                   | 8086          |
| [CMPSB]({{< ref "#cmpsb" >}})    | Compare String - Byte                              | 8086          |
| [CMPSW]({{< ref "#cmpsw" >}})    | Compare String - Word                              | 8086          |
| [CMPSD]({{< ref "#cmpsd" >}})    | Compare String - Doubleword                        | 80386         |
| [CMPXCHG]({{< ref "#cmpxchg" >}})| Compare and Exchange                               | 80486         |
| [CPUID]({{< ref "#cpuid" >}})    | CPU Identification Code                            | Pentium       |
| [CWD]({{< ref "#cwd" >}})        | Convert Word to Doubleword                         | 8086          |
| [CWDE]({{< ref "#cwde" >}})      | Convert Word to Extended Doubleword                | 80386         |
| [DAA]({{< ref "#daa" >}})        | Decimal Adjust Register After Addition             | 8086          |
| [DAS]({{< ref "#das" >}})        | Decimal Adjust AL Register After Substraction      | 8086          |
| [DEC]({{< ref "#dec" >}})        | Decrement by One                                   | 8086          |
| [DIV]({{< ref "#div" >}})        | Unsigned Integer Divide                            | 8086          |
| [ENTER]({{< ref "#enter" >}})    | Make Stack Frame for Procedure Parameter           | 80186         |
| [HLT]({{< ref "#hlt" >}})        | Halt Processor                                     | 8086          |
| [IDIV]({{< ref "#idiv" >}})      | Signed Integer Divide                              | 8086          |
| [IMUL]({{< ref "#imul" >}})      | Signed Integer Multiply                            | 8086 *        |
| [IN]({{< ref "#in" >}})          | Input from Port                                    | 8086          |
| [INC]({{< ref "#inc" >}})        | Increment by One                                   | 8086          |
| [INSB]({{< ref "#insb" >}})      | Input Byte from Port                               | 80186         |
| [INSW]({{< ref "#insw" >}})      | Input Word from Port                               | 80186         |
| [INSD]({{< ref "#insd" >}})      | Input Doubleword from Port                         | 80386         |
| [INT]({{< ref "#int" >}})        | Call to Interrupt Procedure                        | 8086          |
| [INTO]({{< ref "#into" >}})      | Interrupt on Overflow                              | 8086          |
| [INVD]({{< ref "#invd" >}})      | Invalidate data cache                              | 80486         |
| [INVLPG]({{< ref "#invlpg" >}})  | Invalidate TBL entry                               | 80486         |
| [IRET]({{< ref "#iret" >}})      | Return from Interrupt                              | 8086          |
| [Jcc]({{< ref "#jcc" >}})        | Jump on Some Condition Code                        | 8086 *        |
| [JCXZ]({{< ref "#jcxz" >}})      | Jump if CX is Zero                                 | 8086          |
| [JMP]({{< ref "#jmp" >}})        | Jump                                               | 8086          |
| [LAHF]({{< ref "#lahf" >}})      | Load Flags into AH Register                        | 8086          |
| [LAR]({{< ref "#lar" >}})        | Load Access Rights Byte                            | 80286         |
| [LDS]({{< ref "#lds" >}})        | Load Far Pointer Using DS                          | 8086 *        |
| [LES]({{< ref "#les" >}})        | Load Far Pointer Using ES                          | 8086 *        |
| [LFS]({{< ref "#lfs" >}})        | Load Far Pointer Using FS                          | 80386         |
| [LGS]({{< ref "#lgs" >}})        | Load Far Pointer Using GS                          | 80386         |
| [LSS]({{< ref "#lss" >}})        | Load Far Pointer Using SS                          | 80386         |
| [LSS]({{< ref "#lss" >}})        | Load Far Pointer Using SS                          | 80386         |
| [LEA]({{< ref "#lea" >}})        | Load Effective Address                             | 8086          |
| [LEAVE]({{< ref "#leave" >}})    | High Level Procedure Exit                          | 80186         |
| [LGDT]({{< ref "#lgdt" >}})      | Load Global Descriptor Table                       | 80286         |
| [LIDT]({{< ref "#lidt" >}})      | Load Interrupt Descriptor Table                    | 80286         |
| [LLDT]({{< ref "#lldt" >}})      | Load Local Descriptor Table                        | 80286         |
| [LMSW]({{< ref "#lmsw" >}})      | Load Machine Status Word                           | 80286         |
| [LODSB]({{< ref "#lodsb" >}})    | Load Byte String                                   | 8086          |
| [LODSW]({{< ref "#lodsw" >}})    | Load Word String                                   | 8086          |
| [LODSD]({{< ref "#lodsd" >}})    | Load Doubleword String                             | 80386         |
| [LOOP]({{< ref "#loop" >}})      | Loop while CX is not Zero                          | 8086          |
| [LOOPZ]({{< ref "#loopz" >}})    | Loop while Zero                                    | 8086          |
| [LOOPNZ]({{< ref "#loopnz" >}})  | Loop while not Zero                                | 8086          |
| [LSL]({{< ref "#lsl" >}})        | Load Segment Limit                                 | 80286         |
| [LTR]({{< ref "#ltr" >}})        | Load Task Register                                 | 80286         |
| [MOV]({{< ref "#mov" >}})        | Move Data                                          | 8086 *        |
| [MOVSB]({{< ref "#movsb" >}})    | Move Byte String                                   | 8086          |
| [MOVSW]({{< ref "#movsw" >}})    | Move Word String                                   | 8086          |
| [MOVSD]({{< ref "#movsd" >}})    | Move Doubleword String                             | 80386         |
| [MOVSX]({{< ref "#movsx" >}})    | Move with Sign Extension                           | 80386         |
| [MOVZX]({{< ref "#movzx" >}})    | Move with Zero Extension                           | 80386         |
| [MUL]({{< ref "#mul" >}})        | Unsigned Integer Multiply                          | 8086          |
| [NEG]({{< ref "#neg" >}})        | Negate (Two's Complement)                          | 8086          |
| [NOP]({{< ref "#nop" >}})        | Do Nothing                                         | 8086          |
| [NOT]({{< ref "#not" >}})        | Negate (One's Complement)                          | 8086          |
| [OR]({{< ref "#or" >}})          | Logical Inclusive OR                               | 8086          |
| [OUT]({{< ref "#out" >}})        | Output To Port                                     | 8086          |
| [OUTSB]({{< ref "#outsb" >}})    | Output Byte from Port                              | 80186         |
| [OUTSW]({{< ref "#outsw" >}})    | Output Word from Port                              | 80186         |
| [OUTSD]({{< ref "#outsd" >}})    | Output Doubleword from Port                        | 80386         |
| [POP]({{< ref "#pop" >}})        | Pop a Word from the Stack                          | 8086 *        |
| [POPA]({{< ref "#popa" >}})      | Pop All Registers                                  | 80386         |
| [POPF]({{< ref "#popf" >}})      | Pop FLAGS                                          | 8086          |
| [PUSH]({{< ref "#push" >}})      | Push Operand onto Stack                            | 8086 *        |
| [PUSHW]({{< ref "#pushw" >}})    | Push Word                                          | 80286         |
| [PUSHD]({{< ref "#pushd" >}})    | Push Doubleword                                    | 80386         |
| [PUSHA]({{< ref "#pusha" >}})    | Push All Registers                                 | 80186         |
| [PUSHF]({{< ref "#pushf" >}})    | Push FLAGS                                         | 8086          |
| [RCL]({{< ref "#rcl" >}})        | Rotate Left through Carry - Uses CF for Extension  | 8086 *        |
| [RCR]({{< ref "#rcr" >}})        | Rotate Right through Carry - Uses CF for Extension | 8086 *        |
| [RDMSR]({{< ref "#rdmsr" >}})    | Read from Model Specific Register                  | Pentium       |
| [RET]({{< ref "#ret" >}})        | Return from Procedure                              | 8086          |
| [RDPMC]({{< ref "#rdpmc" >}})    | Read Performance Monitor Counter                   | Pentium Pro   |
| [ROL]({{< ref "#rol" >}})        | Rotate Left through Carry - Wrap bits around       | 8086 *        |
| [ROR]({{< ref "#ror" >}})        | Rotate Right through Carry - Wrap bits around      | 8086 *        |
| [RSM]({{< ref "#rsm" >}})        | Return from System Management mode                 | Pentium       |
| [SALC]({{< ref "#salc" >}})      | Set AL on Carry                                    | Pentium Pro   |
| [SAHF]({{< ref "#sahf" >}})      | Load Flags into AH Register                        | 8086          |
| [SAL]({{< ref "#sal" >}})        | Shift Arithmetic Left                              | 8086 *        |
| [SAR]({{< ref "#sar" >}})        | Shift Arithmetic Right                             | 8086 *        |
| [SETcc]({{< ref "#setcc" >}})    | Set Byte on Condition Code                         | 80386         |
| [SHL]({{< ref "#shl" >}})        | Shift Logic Left                                   | 8086 *        |
| [SHR]({{< ref "#shr" >}})        | Shift Logic Right                                  | 8086 *        |
| [SBB]({{< ref "#sbb" >}})        | Substract Integers with Borrow                     | 8086          |
| [SCASB]({{< ref "#scasb" >}})    | Compare Byte String                                | 8086          |
| [SCASW]({{< ref "#scasw" >}})    | Compare Word String                                | 8086          |
| [SGDT]({{< ref "#sgdt" >}})      | Store Global Descriptor Table                      | 80286         |
| [SHLD]({{< ref "#shld" >}})      | Double Precision Shift Left                        | 80386         |
| [SHRD]({{< ref "#shrd" >}})      | Double Precision Shift Right                       | 80386         |
| [SIDT]({{< ref "#sidt" >}})      | Store Interrupt Descriptor Table                   | 80286         |
| [SLDT]({{< ref "#sldt" >}})      | Store Local Descriptor Table                       | 80286         |
| [SMSW]({{< ref "#smsw" >}})      | Store Machine Status Word                          | 80286         |
| [STC]({{< ref "#stc" >}})        | Set Carry Flag (CF)                                | 8086          |
| [STD]({{< ref "#std" >}})        | Set Direction Flag (DF)                            | 8086          |
| [STI]({{< ref "#sti" >}})        | Set Interrupt Flag (IF)                            | 8086          |
| [STOSB]({{< ref "#stosb" >}})    | Store String Data Byte                             | 8086          |
| [STOSW]({{< ref "#stosw" >}})    | Store String Data Word                             | 8086          |
| [STOSD]({{< ref "#stosd" >}})    | Store String Data Doubleword                       | 80386         |
| [SUB]({{< ref "#sub" >}})        | Subtract                                           | 8086          |
| [TEST]({{< ref "#test" >}})      | Test Operands                                      | 8086          |
| [VERR]({{< ref "#verr" >}})      | Verify Read                                        | 80286         |
| [VERW]({{< ref "#verw" >}})      | Verify Write                                       | 80286         |
| [WAIT]({{< ref "#wait" >}})      | Wait for FPU                                       | 8086          |
| [WBINVD]({{< ref "#wbinvd" >}})  | Write Back and Invalidate Data Cache               | 80486         |
| [WRMSR]({{< ref "#wrmsr" >}})    | Write to Model Specific Register                   | Pentium       |
| [XADD]({{< ref "#xadd" >}})      | Exchange and Add                                   | 80486         |
| [XCHG]({{< ref "#xchg" >}})      | Exchange                                           | 8086          |
| [XLAT]({{< ref "#xlat" >}})      | Translate                                          | 8086          |
| [XOR]({{< ref "#xor" >}})        | Exclusive-OR                                       | 8086          |
|                                  |                                                    |               |
| [LOCK]({{< ref "#lock-signal" >}})| Assert Lock Prefix                                | 8086          |
| [REP]({{< ref "#repeat" >}})     | Repeat String Operation Prefix                     | 8086          |
| [REPZ]({{< ref "#repeat" >}})    | Repeat String Operation Prefix while Zero          | 8086          |
| [REPE]({{< ref "#repeat" >}})    | Repeat String Operation Prefix while Equal         | 8086          |
| [REPNZ]({{< ref "#repeat" >}})   | Repeat String Operation Prefix while not Zero      | 8086          |
| [REPNE]({{< ref "#repeat" >}})   | Repeat String Operation Prefix while not Equal     | 8086          |
| [CS]({{< ref "#segment-override" >}})| CS Segment Override Prefix                     | 8086          |
| [DS]({{< ref "#segment-override" >}})| DS Segment Override Prefix                     | 8086          |
| [ES]({{< ref "#segment-override" >}})| ES Segment Override Prefix                     | 8086          |
| [FS]({{< ref "#segment-override" >}})| FS Segment Override Prefix                     | 80386         |
| [GS]({{< ref "#segment-override" >}})| GS Segment Override Prefix                     | 80386         |
| [SS]({{< ref "#segment-override" >}})| SS Segment Override Prefix                     | 8086          |
| [o32]({{< ref "#size-override" >}})| Operand-size Override Prefix                     | 80386         |
| [a32]({{< ref "#size-override" >}})| Address-size Override Prefix                     | 80386         |
{.width-100}

\*: The instruction was extended in later processors.

</details>

## Encoding

### ModR/M Byte

| Bits | Field | Meaning                                    |
|:-----|:------|:-------------------------------------------|
| 7-6  | mod   | Encodes the addressing mode                |
| 5-3  | reg   | Encodes the register number                |
| 2-0  | r/m   | Specifies register or memory addressing    |
{.width-100}

### Addressing mode -- mod

| Value (oo) | Meaning                                   |
|:-----------|:------------------------------------------|
| 0b00       | No displacement is present                |
| 0b01       | 8-bits displacement (sign-extended to 16) |
| 0b10       | 16-bits displacement (high : low)         |
| 0b11       | r/m is treated as a reg field             |
{.width-100}

### Register index -- reg

| Value (rrr) | Meaning (w=0) | Meaning (w=1) | Meaning (32bit) |
|:------------|:--------------|:--------------|:--------------|
| 0b000       | AL            | AX            | EAX           |
| 0b001       | CL            | CX            | ECX           |
| 0b010       | DL            | DX            | EDX           |
| 0b011       | BL            | BX            | EBX           |
| 0b100       | AH            | SP            | ESP           |
| 0b101       | CH            | BP            | EBP           |
| 0b110       | DH            | SI            | ESI           |
| 0b111       | BH            | DI            | EDI           |
{.width-100}

### Register or memory -- r/m

| Value (mmm) | Meaning             |
|:------------|:--------------------|
| 0b000       | DS:[BX+SI] + DISP   |
| 0b001       | DS:[BX+DI] + DISP   |
| 0b010       | SS:[BP+SI] + DISP   |
| 0b011       | SS:[BP+DI] + DISP   |
| 0b100       | DS:[SI] + DISP      |
| 0b101       | DS:[DI] + DISP      |
| 0b110       | SS:[BP] + DISP *    |
| 0b111       | DS:[BX] + DISP      |
{.width-100}

\*: If mod=0b00 and r/m=0b110, a 2-byte displacement is required.

### Segment register

| Value (sss) | Meaning       |
|:------------|:--------------|
| 0b000       | ES            |
| 0b001       | CS            |
| 0b010       | SS            |
| 0b011       | DS            |
| 0b100       | FS *          |
| 0b101       | GS *          |
{.width-100}

\*: Available on 80386 and later machines.

### Condition codes

| Value (ccc) | Name        |  Meaning       |
|:------------|:------------|:---------------|
| 0b0000      | O           | Overflow |
| 0b0001      | NO          | Not overflow |
| 0b0010      | C/B/NAE     | Carry, below, not above nor equal|
| 0b0011      | NC/AE/NB    | Not carry, above or equal, not below|
| 0b0100      | E/Z         | Equal, zero|
| 0b0101      | NE/NZ       | Not equal, not zero|
| 0b0110      | BE/NA       | Below or equal, not above|
| 0b0111      | A/NBE       | Above, not below nor equal|
| 0b1000      | S           | Sign|
| 0b1001      | NS          | Not sign|
| 0b1010      | P/PE        | Parity, parity even|
| 0b1011      | NP/PO       | Not parity, parity odd|
| 0b1100      | L/NGE       | Less, not greater nor equal|
| 0b1101      | GE/NL       | Greater or egual, not less|
| 0b1110      | LE/NG       | Less or equal, not greater|
| 0b1111      | G/NLE       | Greater, not less nor equal|
{.width-100}


## Instructions

For each instruction, there could be several opcodes and encodings.\
We will specify in both hex and binary the opcode and the values of the ModR/M byte.

| Notation  | Meaning                          |
|-----------|:---------------------------------|
| 00 ... FF | Literal opcode in base 16        |
| /r        | ModR/M byte with variable reg value|
| /0 ... /7 | ModR/M byte with fixed reg value |
| ib        | Immediate byte (8 bits)          |
| iw        | Immediate word (16 bits)         |
| id        | Immediate doubleword (32 bits)   |
| relN      | Relative displacement (N bits, signed)   |
| ptrN      | Absolute offset (N bits)         |
| mN        | Memory operand (N bits)          |
| immN      | Immediate value (N bits)         |
{.width-100}


### AAA

| Instruction        | Opcode                      |
|:-------------------|:----------------------------|
| AAA                | 37 <br> 00110111            |
{.width-100}

### AAD

| Instruction        | Opcode                      |
|:-------------------|:----------------------------|
| AAD                | D5 0A <br> 1101010100001010 |
| AAD imm8           | D5 ib <br> 11010101iiiiiiii |
{.width-100}

### AAM

| Instruction        | Opcode                      |
|:-------------------|:----------------------------|
| AAM                | D4 0A <br> 1101010000001010 |
| AAM imm8           | D4 ib <br> 11010100iiiiiiii |
{.width-100}

### AAS

| Instruction        | Opcode                      |
|:-------------------|:----------------------------|
| AAS                | 3F <br> 00111111            |
{.width-100}

### ADC

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| ADC AL, imm8       | 14 ib <br> 00010100iiiiiiii           |
| ADC AX, imm16      | 15 iw <br> 00010101iiiiiiiiiiiiiiii   |
| ADC r/m8, r8       | 10 /r <br> 00010000oorrrmmm           |
| ADC r/m16, r16     | 11 /r <br> 00010001oorrrmmm           |
| ADC r8, r/m8       | 12 /r <br> 00010010oorrrmmm           |
| ADC r16, r/m16     | 13 /r <br> 00010011oorrrmmm           |
| ADC r/m8, imm8     | 80 /2 ib <br> 10000000oo010mmmiiiiiiii         |
| ADC r/m16, imm16   | 81 /2 iw <br> 10000001oo010mmmiiiiiiiiiiiiiiii |
| ADC r/m16, imm8    | 83 /2 ib <br> 10000011oo010mmmiiiiiiii         |
{.width-100}

### ADD

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| ADD AL, imm8       | 04 ib <br> 00000100iiiiiiii           |
| ADD AX, imm16      | 05 iw <br> 00000101iiiiiiiiiiiiiiii   |
| ADD r/m8, r8       | 00 /r <br> 00000000oorrrmmm           |
| ADD r/m16, r16     | 01 /r <br> 00000001oorrrmmm           |
| ADD r8, r/m8       | 02 /r <br> 00000010oorrrmmm           |
| ADD r16, r/m16     | 03 /r <br> 00000011oorrrmmm           |
| ADD r/m8, imm8     | 80 /0 ib <br> 10000000oo000mmmiiiiiiii         |
| ADD r/m16, imm16   | 81 /0 iw <br> 10000001oo000mmmiiiiiiiiiiiiiiii |
| ADD r/m16, imm8    | 83 /0 ib <br> 10000011oo000mmmiiiiiiii         |
{.width-100}

### AND

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| AND AL, imm8       | 24 ib <br> 00100100iiiiiiii           |
| AND AX, imm16      | 25 iw <br> 00100101iiiiiiiiiiiiiiii   |
| AND r/m8, r8       | 20 /r <br> 00100000oorrrmmm           |
| AND r/m16, r16     | 21 /r <br> 00100001oorrrmmm           |
| AND r8, r/m8       | 22 /r <br> 00100010oorrrmmm           |
| AND r16, r/m16     | 23 /r <br> 00100011oorrrmmm           |
| AND r/m8, imm8     | 80 /4 ib <br> 10000000oo100mmmiiiiiiii         |
| AND r/m16, imm16   | 81 /4 iw <br> 10000001oo100mmmiiiiiiiiiiiiiiii |
| AND r/m16, imm8    | 83 /4 ib <br> 10000011oo100mmmiiiiiiii         |
{.width-100}

### ARPL

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| ARPL r/m16, r16    | 63 /r <br> 01100011oorrrmmm           |
{.width-100}

### BOUND

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BOUND r16, r/m32   | 62 /r <br> 01100010oorrrmmm           |
| BOUND r32, r/m64   | 62 /r <br> 01100010oorrrmmm           |
{.width-100}

### BSF

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BSF r16, r/m16     | 0F BC /r <br> 0000111110111100oorrrmmm |
{.width-100}

### BSR

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BSR r16, r/m16     | 0F BD /r <br> 0000111110111101oorrrmmm |
{.width-100}

### BSWAP

*Reverses the byte order of a 32-bit or 64-bit (destination) register. This instruction is provided for converting little-
endian values to big-endian format and vice versa. To swap bytes in a word value (16-bit register), use the XCHG
instruction. When the BSWAP instruction references a 16-bit register, the result is undefined.*[^bswap]

[^bswap]: *BSWAP—Byte Swap*, Vol. 2A 3-129

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BSWAP r32          | 0F C8+rrr <br> 0000111111001rrr |
{.width-100}

### BT

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BT r/m16, r16      | 0F A3 /r <br> 0000111110100011oorrrmmm |
| BT r/m16, imm8     | 0F BA /4 ib <br> 0000111110111010oo100mmmiiiiiiii |
{.width-100}

### BTC

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BTC r/m16, r16     | 0F BB /r <br> 0000111110111011oorrrmmm |
| BTC r/m16, imm8    | 0F BA /7 ib <br> 0000111110111010oo111mmmiiiiiiii |
{.width-100}

### BTR

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BTR r/m16, r16     | 0F B3 /r <br> 0000111110110011oorrrmmm |
| BTR r/m16, imm8    | 0F BA /6 ib <br> 0000111110111010oo110mmmiiiiiiii |
{.width-100}

### BTS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| BTS r/m16, r16     | 0F AB /r <br> 0000111110101011oorrrmmm |
| BTS r/m16, imm8    | 0F BA /5 ib <br> 0000111110111010oo101mmmiiiiiiii |
{.width-100}

### CALL

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CALL rel16 \*      | E8 iw <br> 11101000iiiiiiiiiiiiiiii   |
| CALL r/m16 \*      | FF /2 <br> 11111111oo010mmm           |
| CALL ptr16:16 \*\* | 9A id <br> 10011010iiiiiiiiiiiiiiiissssssssssssssss |
| CALL mem16:16 \*\* | FF /3 <br> 11111111oo011mmm           |
{.width-100}

\*: Near calls (inside the same CS segment). \
\*\*: Far calls (changes the CS segment).

### CBW

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CBW                | 98 <br> 10011000                      |
{.width-100}

### CDQ

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CDQ                | 99 <br> 10011001                      |
{.width-100}

### CLC

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CLC                | F8 <br> 11111000                      |
{.width-100}

### CLD

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CLD                | FC <br> 11111100                      |
{.width-100}

### CLI

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CLI                | FA <br> 11111010                      |
{.width-100}

### CLTS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CLTS               | 0F 06 <br> 0000111100000110           |
{.width-100}

### CMC

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CMC                | F5 <br> 11110101                      |
{.width-100}

### CMOVcc

| Instruction        | Opcode                                 |
|:-------------------|:---------------------------------------|
| CMOVO r16, r/m16   | 0F 40 /r <br> 0000111110000000oorrrmmm |
| CMOVNO r16, r/m16  | 0F 41 /r <br> 0000111101000001oorrrmmm |
| CMOVB r16, r/m16   | 0F 42 /r <br> 0000111101000010oorrrmmm |
| CMOVC r16, r/m16   | 0F 42 /r <br> 0000111101000010oorrrmmm |
| CMOVNAE r16, r/m16 | 0F 42 /r <br> 0000111101000010oorrrmmm |
| CMOVAE r16, r/m16  | 0F 43 /r <br> 0000111101000011oorrrmmm |
| CMOVNB r16, r/m16  | 0F 43 /r <br> 0000111101000011oorrrmmm |
| CMOVNC r16, r/m16  | 0F 43 /r <br> 0000111101000011oorrrmmm |
| CMOVE r16, r/m16   | 0F 44 /r <br> 0000111101000100oorrrmmm |
| CMOVZ r16, r/m16   | 0F 44 /r <br> 0000111101000100oorrrmmm |
| CMOVNE r16, r/m16  | 0F 45 /r <br> 0000111101000101oorrrmmm |
| CMOVNZ r16, r/m16  | 0F 45 /r <br> 0000111101000101oorrrmmm |
| CMOVBE r16, r/m16  | 0F 46 /r <br> 0000111101000110oorrrmmm |
| CMOVNA r16, r/m16  | 0F 46 /r <br> 0000111101000110oorrrmmm |
| CMOVA r16, r/m16   | 0F 47 /r <br> 0000111101000111oorrrmmm |
| CMOVNBE r16, r/m16 | 0F 47 /r <br> 0000111101000111oorrrmmm |
| CMOVS r16, r/m16   | 0F 48 /r <br> 0000111101001000oorrrmmm |
| CMOVNS r16, r/m16  | 0F 49 /r <br> 0000111101001001oorrrmmm |
| CMOVP r16, r/m16   | 0F 4A /r <br> 0000111101001010oorrrmmm |
| CMOVPE r16, r/m16  | 0F 4A /r <br> 0000111101001010oorrrmmm |
| CMOVNP r16, r/m16  | 0F 4B /r <br> 0000111101001011oorrrmmm |
| CMOVPO r16, r/m16  | 0F 4B /r <br> 0000111101001011oorrrmmm |
| CMOVL r16, r/m16   | 0F 4C /r <br> 0000111101001100oorrrmmm |
| CMOVNGE r16, r/m16 | 0F 4C /r <br> 0000111101001100oorrrmmm |
| CMOVGE r16, r/m16  | 0F 4D /r <br> 0000111101001101oorrrmmm |
| CMOVNL r16, r/m16  | 0F 4D /r <br> 0000111101001101oorrrmmm |
| CMOVLE r16, r/m16  | 0F 4E /r <br> 0000111101001110oorrrmmm |
| CMOVNG r16, r/m16  | 0F 4E /r <br> 0000111101001110oorrrmmm |
| CMOVG r16, r/m16   | 0F 4F /r <br> 0000111101001111oorrrmmm |
| CMOVNLE r16, r/m16 | 0F 4F /r <br> 0000111101001111oorrrmmm |
{.width-100}

### CMP

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CMP AL, imm8       | 3C ib <br> 00111100iiiiiiii           |
| CMP AX, imm16      | 3D iw <br> 00111101iiiiiiiiiiiiiiii   |
| CMP r/m8, imm8     | 80 /7 ib <br> 10000000oo111mmmiiiiiiii|
| CMP r/m16, imm16   | 81 /7 iw <br> 10000001oo111mmmiiiiiiiiiiiiiiii|
| CMP r/m16, imm8    | 83 /7 iw <br> 10000011oo111mmmiiiiiiii|
| CMP r/m8, r8       | 38 /r <br> 00111000oorrrmmm           |
| CMP r/m16, r16     | 39 /r <br> 00111001oorrrmmm           |
| CMP r8, r/m8       | 3A /r <br> 00111010oorrrmmm           |
| CMP r16, r/m16     | 3B /r <br> 00111011oorrrmmm           |
{.width-100}

### CMPSB

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CMPSB              | A6 <br> 10100110                      |
{.width-100}

### CMPSW

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CMPSW              | A7 <br> 10100111                      |
{.width-100}

### CMPSD

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CMPSD *            | A7 <br> 10100111                      |
{.width-100}

\*: Requires 32-bit operand size.

### CMPXCHG

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CMPXCHG r/m8, r8   | 0F B0 /r <br> 0000111110110000oorrrmmm|
| CMPXCHG r/m16, r16 | 0F B1 /r <br> 0000111110110001oorrrmmm|
{.width-100}

### CPUID

*Returns processor identification and feature
information to the EAX, EBX, ECX, and EDX
registers, as determined by input entered in
EAX (in some cases, ECX as well).*

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CPUID              | 0F A2 <br> 0000111110100010           |
{.width-100}

### CWD

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CWD                | 99 <br> 10011001                      |
{.width-100}

### CWDE

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| CWDE               | 98 <br> 10011000                      |
{.width-100}

### DAA

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| DAA                | 27 <br> 00100111                      |
{.width-100}

### DAS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| DAS                | 2F <br> 00101111                      |
{.width-100}

### DEC

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| DEC r/m8           | FE /1 <br> 11111110oo001mmm           |
| DEC r/m16          | FF /1 <br> 11111111oo001mmm           |
| DEC r16            | 48+rw <br> 01001rrr                   |
{.width-100}

### DIV

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| DIV r/m8           | F6 /6 <br> 11110110oo110mmm           |
| DIV r/m16          | F7 /6 <br> 11110111oo110mmm           |
{.width-100}

### ENTER

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| ENTER imm16, imm8  | C8 iw ib <br> 11001000iiiiiiiiiiiiiiiiiiiiiiii|
{.width-100}

### HLT

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| HLT                | F4 <br> 11110100                      |
{.width-100}

### IDIV

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| IDIV r/m8          | F6 /7 <br> 11110110oo111mmm           |
| IDIV r/m16         | F7 /7 <br> 11110111oo111mmm           |
{.width-100}

### IMUL

| Instruction            | Opcode                                |
|:-----------------------|:--------------------------------------|
| IMUL r/m8              | F6 /5 <br> 11110110oo101mmm           |
| IMUL r/m16             | F7 /5 <br> 11110111oo101mmm           |
| IMUL r16, r/m16        | 0F AF /r <br> 0000111110101111oorrrmmm|
| IMUL r16, r/m16, imm8  | 6B /r ib <br> 01101011oorrrmmmiiiiiiii        |
| IMUL r16, r/m16, imm16 | 69 /r iw <br> 01101001oorrrmmmiiiiiiiiiiiiiiii |
{.width-100}

### IN

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| IN AL, DX          | EC <br> 11101100                      |
| IN AX, DX          | ED <br> 11101101                      |
| IN AL, imm8        | E4 ib <br> 11100100iiiiiiii           |
| IN AX, imm8        | E5 ib <br> 11100101iiiiiiii           |
{.width-100}

### INC

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INC r/m8           | FE /0 <br> 11111110oo000mmm           |
| INC r/m16          | FF /0 <br> 11111111oo000mmm           |
| INC r16            | 40+rw \* <br> 01000rrr                |
{.width-100}

\*: 40H through 47H are REX prefixes in 64-bit mode

### INSB

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INSB               | 6C <br> 01101100                      |
{.width-100}

### INSW

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INSW               | 6D <br> 01101101                      |
{.width-100}

### INSD

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INSD \*            | 6D <br> 01101101                      |
{.width-100}

\*: Requires 32-bit operand size.

### INT

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INT1               | F1 <br> 11110001                      |
| INT3               | CC <br> 11001100                      |
| INT imm8           | CD ib <br> 11001101iiiiiiii           |
{.width-100}

### INTO

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INTO               | CE <br> 11001110                      |
{.width-100}

### INVD

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INVD               | 0F 08 <br> 0000111100001000           |
{.width-100}

### INVLPG

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| INVLPG m           | 0F 01 /7 <br> 0000111100000001oo111mmm|
{.width-100}

### IRET

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| IRET               | CF <br> 11001111                      |
{.width-100}

### Jcc

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| JO rel8 \*         | 70 ib <br> 01110000iiiiiiii           |
| JNO rel8 \*        | 71 ib <br> 01110001iiiiiiii           |
| JB rel8 \*         | 72 ib <br> 01110010iiiiiiii           |
| JC rel8 \*         | 72 ib <br> 01110010iiiiiiii           |
| JNAE rel8 \*       | 72 ib <br> 01110010iiiiiiii           |
| JAE rel8 \*        | 73 ib <br> 01110011iiiiiiii           |
| JNB rel8 \*        | 73 ib <br> 01110011iiiiiiii           |
| JNC rel8 \*        | 73 ib <br> 01110011iiiiiiii           |
| JE rel8 \*         | 74 ib <br> 01110100iiiiiiii           |
| JZ rel8 \*         | 74 ib <br> 01110100iiiiiiii           |
| JNE rel8 \*        | 75 ib <br> 01110101iiiiiiii           |
| JNZ rel8 \*        | 75 ib <br> 01110101iiiiiiii           |
| JBE rel8 \*        | 76 ib <br> 01110110iiiiiiii           |
| JNA rel8 \*        | 76 ib <br> 01110110iiiiiiii           |
| JNBE rel8 \*       | 77 ib <br> 01110111iiiiiiii           |
| JA rel8 \*         | 77 ib <br> 01110111iiiiiiii           |
| JS rel8 \*         | 78 ib <br> 01111000iiiiiiii           |
| JNS rel8 \*        | 79 ib <br> 01111001iiiiiiii           |
| JP rel8 \*         | 7A ib <br> 01111010iiiiiiii           |
| JPE rel8 \*        | 7A ib <br> 01111010iiiiiiii           |
| JNP rel8 \*        | 7B ib <br> 01111011iiiiiiii           |
| JPO rel8 \*        | 7B ib <br> 01111011iiiiiiii           |
| JL rel8 \*         | 7C ib <br> 01111100iiiiiiii           |
| JNGE rel8 \*       | 7C ib <br> 01111100iiiiiiii           |
| JLE rel8 \*        | 7E ib <br> 01111101iiiiiiii           |
| JNG rel8 \*        | 7E ib <br> 01111101iiiiiiii           |
| JNL rel8 \*        | 7D ib <br> 01111110iiiiiiii           |
| JGE rel8 \*        | 7D ib <br> 01111110iiiiiiii           |
| JNLE rel8 \*       | 7F ib <br> 01111111iiiiiiii           |
| JG rel8 \*         | 7F ib <br> 01111111iiiiiiii           |
| JO rel16 \*\*      | 0F 80 iw <br> 00001111100010000iiiiiiiiiiiiiiii |
| JNO rel16 \*\*     | 0F 81 iw <br> 00001111100010001iiiiiiiiiiiiiiii |
| JB rel16 \*\*      | 0F 82 iw <br> 00001111100010010iiiiiiiiiiiiiiii |
| JC rel16 \*\*      | 0F 82 iw <br> 00001111100010010iiiiiiiiiiiiiiii |
| JNAE rel16 \*\*    | 0F 82 iw <br> 00001111100010010iiiiiiiiiiiiiiii |
| JAE rel16 \*\*     | 0F 83 iw <br> 00001111100010011iiiiiiiiiiiiiiii |
| JNB rel16 \*\*     | 0F 83 iw <br> 00001111100010011iiiiiiiiiiiiiiii |
| JNC rel16 \*\*     | 0F 83 iw <br> 00001111100010011iiiiiiiiiiiiiiii |
| JE rel16 \*\*      | 0F 84 iw <br> 00001111100010100iiiiiiiiiiiiiiii |
| JZ rel16 \*\*      | 0F 84 iw <br> 00001111100010100iiiiiiiiiiiiiiii |
| JNE rel16 \*\*     | 0F 85 iw <br> 00001111100010101iiiiiiiiiiiiiiii |
| JNZ rel16 \*\*     | 0F 85 iw <br> 00001111100010101iiiiiiiiiiiiiiii |
| JBE rel16 \*\*     | 0F 86 iw <br> 00001111100010110iiiiiiiiiiiiiiii |
| JNA rel16 \*\*     | 0F 86 iw <br> 00001111100010110iiiiiiiiiiiiiiii |
| JNBE rel16 \*\*    | 0F 87 iw <br> 00001111100010111iiiiiiiiiiiiiiii |
| JA rel16 \*\*      | 0F 87 iw <br> 00001111100010111iiiiiiiiiiiiiiii |
| JS rel16 \*\*      | 0F 88 iw <br> 00001111100011000iiiiiiiiiiiiiiii |
| JNS rel16 \*\*     | 0F 89 iw <br> 00001111100011001iiiiiiiiiiiiiiii |
| JP rel16 \*\*      | 0F 8A iw <br> 00001111100011010iiiiiiiiiiiiiiii |
| JPE rel16 \*\*     | 0F 8A iw <br> 00001111100011010iiiiiiiiiiiiiiii |
| JNP rel16 \*\*     | 0F 8B iw <br> 00001111100011011iiiiiiiiiiiiiiii |
| JPO rel16 \*\*     | 0F 8B iw <br> 00001111100011011iiiiiiiiiiiiiiii |
| JL rel16 \*\*      | 0F 8C iw <br> 00001111100011100iiiiiiiiiiiiiiii |
| JNGE rel16 \*\*    | 0F 8C iw <br> 00001111100011100iiiiiiiiiiiiiiii |
| JLE rel16 \*\*     | 0F 8E iw <br> 00001111100011101iiiiiiiiiiiiiiii |
| JNG rel16 \*\*     | 0F 8E iw <br> 00001111100011101iiiiiiiiiiiiiiii |
| JNL rel16 \*\*     | 0F 8D iw <br> 00001111100011110iiiiiiiiiiiiiiii |
| JGE rel16 \*\*     | 0F 8D iw <br> 00001111100011110iiiiiiiiiiiiiiii |
| JNLE rel16 \*\*    | 0F 8F iw <br> 00001111100011111iiiiiiiiiiiiiiii |
| JG rel16 \*\*      | 0F 8F iw <br> 00001111100011111iiiiiiiiiiiiiiii |
{.width-100}

\*: Short jump. \
\*\*: Near jump. \

### JCXZ

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| JCXZ rel8          | E3 ib <br> 11100011iiiiiiii           |
| JCXE rel8          | E3 ib <br> 11100011iiiiiiii           |
{.width-100}

### JMP

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| JMP rel8 \*        | EB ib <br> 11101011iiiiiiii           |
| JMP rel16 \*\*     | E9 iw <br> 11101001iiiiiiiiiiiiiiii   |
| JMP r/m16 \*\*     | FF /4 <br> 11111111oo100mmm           |
| JMP ptr16:16 \*\*\*| EA id <br> 11101010iiiiiiiiiiiiiiiissssssssssssssss|
| JMP m16:16 \*\*\*  | FF /5 <br> 11111111oo101mmm           |
{.width-100}

\*: Short jump. \
\*\*: Near jump. \
\*\*\*: Far jump.

### LAHF

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LAHF               | 9F <br> 10011111                      |
{.width-100}

### LAR

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LAR r16, r/m16     | 0F 02 /r <br> 0000111100000010oorrrmmm|
{.width-100}

### LDS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LDS r16, m16:16    | C5 /r <br> 11000101oorrrmmm |
{.width-100}

### LES

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LES r16, m16:16    | C4 /r <br> 11000100oorrrmmm |
{.width-100}

### LFS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LFS r16, m16:16    | 0F B4 /r <br> 0000111110110100oorrrmmm |
{.width-100}

### LGS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LGS r16, m16:16    | 0F B5 /r <br> 0000111110110101oorrrmmm |
{.width-100}

### LSS

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LSS r16, m16:16    | 0F B2 /r <br> 0000111110110010oorrrmmm |
{.width-100}

### LEA

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LEA r16, m         | 8D /r <br> 10001101oorrrmmm           |
{.width-100}

### LEAVE

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LEAVE              | C9 <br> 11001001                      |
{.width-100}

### LGDT

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LGDT m16&32        | 0F 01 /2 <br> 0000111100000001oo010mmm|
{.width-100}

### LIDT

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LIDT m16&32        | 0F 01 /3 <br> 0000111100000001oo011mmm|
{.width-100}

### LLDT

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LLDT m16&32        | 0F 00 /2 <br> 0000111100000000oo010mmm|
{.width-100}

### LMSW

| Instruction        | Opcode                                |
|:-------------------|:--------------------------------------|
| LMSW r/m16         | 0F 01 /6 <br> 0000111100000001oo110mmm|
{.width-100}

### LODSB
### LODSW
### LODSD
### LOOP
### LOOPZ
### LOOPNZ
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

## Prefixes

For more information, see Section 2.1.1 "Instruction Prefixes"
of the _Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 2_.

### Lock Signal

_The LOCK prefix can be prepended only to the following instructions and only to those forms of the instructions
where the destination operand is a memory operand: ADD, ADC, AND, BTC, BTR, BTS, CMPXCHG, CMPXCH8B,
CMPXCHG16B, DEC, INC, NEG, NOT, OR, SBB, SUB, XOR, XADD, and XCHG. \
If the LOCK prefix is used with one of these instructions and the source operand is a memory operand, an undefined opcode exception (#UD) may be
generated. An undefined opcode exception will also be generated if the LOCK prefix is used with any instruction not
in the above list._[^lock]

[^lock]: *LOCK—Assert LOCK# Signal Prefix*, Vol. 2A 3-613

| Prefix | Opcode           |
|--------|------------------|
| LOCK   | F0 <br> 11110000 |
{.width-100}

### Repeat

_The REP prefix can be added to the INS, OUTS, MOVS, LODS, and STOS instructions, and the
REPE, REPNE, REPZ, and REPNZ prefixes can be added to the CMPS and SCAS instructions._[^rep]

[^rep]: *REP/REPE/REPZ/REPNE/REPNZ—Repeat String Operation Prefix*, Vol. 2B 4-555

| Prefix | Opcode           |
|--------|------------------|
| REP    | F3 <br> 11110011 |
| REPZ   | F3 <br> 11110011 |
| REPE   | F3 <br> 11110011 |
| REPNZ  | F2 <br> 11110010 |
| REPNE  | F2 <br> 11110010 |
{.width-100}

### Segment Override

Use of segment override with any branch instruction was later reserved and
repurposed for branch-prediction hints.[^branchhint]\
In real-address mode, they retain the original meaning.

[^branchhint]: *2.1.1 Instruction Prefixes*, 2-2 Vol. 2A

| Prefix | Opcode           |
|--------|------------------|
| CS:    | 2E <br> 00101110 |
| DS:    | 3E <br> 00111110 |
| ES:    | 26 <br> 00100110 |
| FS:    | 64 <br> 01100100 |
| GS:    | 65 <br> 01100101 |
| SS:    | 36 <br> 00110110 |
{.width-100}

### Size Override

_When operating in real-address mode, the default addressing and operand size is 16 bits. An address-size override
can be used in real-address mode to enable 32-bit addressing. However, the maximum allowable 32-bit linear
address is still 0x000FFFFF (2<sup>20</sup> - 1)._[^32bits]

[^32bits]: *3.3.5 32-Bit and 16-Bit Address and Operand Sizes*, Vol. 1 3-9

| Prefix        | Opcode           |
|---------------|------------------|
| Operand-size  | 66 <br> 01100110 |
| Address-size  | 67 <br> 01100111 |
{.width-100}

## References

- https://bitsavers.org/components/intel/8086/9800722-03_The_8086_Family_Users_Manual_Oct79.pdf
- https://web.archive.org/web/20230311143236/https://www.ic.unicamp.br/~celio/mc404/opcodes.html
- Note: Last revision available at the time of writing was of June 2024, \
    https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
