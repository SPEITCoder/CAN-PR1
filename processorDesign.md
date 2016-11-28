# 3 Processor Design
## 3.1 Instruction Set Structure
### Instruction Definition
<code>[00][01][02][03][04][05][06][07][08][09][10][11][12][13][14][15]</code>

<code>▃▃▃▃▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃ : type 1</code>

<code>▃▃▃▃▁▁▁▁▃▃▃▃▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ : type 2</code>

<code>▃▃▃▃▁▁▁▁▃▃▃▃▃▃▃▃▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ : type 3</code>

<code>▃▃▃▃▁▁▁▁▃▃▃▃▃▃▃▃▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃ : type 4</code>

#### Type 1 for <code>conditional branch (bne in assembly)</code>

<code>▃▃0▃▁▁register▁addr▁▃▃▃▃immediate▃number▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃▃</code>

<code>[00][01][02][03][04][05][06][07][08][09][10][11][12][13][14][15]</code>

#### Type 2 for <code>load</code> and <code>store</code>

<code>▃▃1▃▁▁0▁▃▃▃▃▁reg▁read▁add▁1▁▃reg▃read▃add▃2▃▁immediate▁operand▁▁</code>

<code>[00][01][02][03][04][05][06][07][08][09][10][11][12][13][14][15]</code>

[02] could be 0 or 1 to indicate load or store respectively.

#### Type 3 for 3 arithmetic/logic instruction operating on 3 register operands.

<code>▃▃1▃▁▁1▁▃ope▃n.▃▁reg▁read▁add▁1▁▃reg▃read▃add▃2▃▁reg▁write▁add▁▁</code>

<code>[00][01][02][03][04][05][06][07][08][09][10][11][12][13][14][15]</code>

[02][03] could be 0 0, 0 1, 1 0 to indicate 3 a/l instruction.
+ 0 0 for addition, 
+ 0 1 for left shifting (shifting reg_read_1 to the left by reg_read_2 bits, store in reg_write), 
+ and 1 0 for logic XOR.

Example: Addition : 1 1 0 0 0 0 0 1 0 0 1 0 0 0 1 1 

is equivalent to write in assembly format Add $1, $2, $3.

Say $1 is +10(decimal), $2 is -4, $3 is whatever number, after the operation, $3 should contain +6.

Example: Left shifting : 1 1 0 1 0 0 0 1 0 0 1 0 0 0 1 1 

is equivalent to write in assembly format Sll $1, $2, $3

Say $1 is +10(decimal), 0 [...] 1 0 1 0 (binary), $2 is -2, $3 is whatever number, after the operation, $3 should contain +2(decimal).

#### Type 4 for copy instruction containing 1 register address and a 8-bit immediate number.

<code>▃▃1▃▁▁1▁▃▃1▃▃▃1▃reg▁write▁add▁▁▃▃▃▃immediate▃number▃▃▃▃▃▃▃▃▃▃▃▃▃</code>

<code>[00][01][02][03][04][05][06][07][08][09][10][11][12][13][14][15]</code>

[02][03] set to 1 1 to indicate that it is a copy (Cpy in assembly).

Note that type 3 and type 4 are variations of type 3, while varying [02][03] to allocate the following bit space differently.

Also, all the immediate numbers are signed, to economize the function space bits.
### Instruction format

+ I-format : type 2
+ J-format : type 1
+ R-format : type 3 and 4

### Loading 65535 into a register

Suppose initially all the registers are null.

1. Cpy $0, +127 ($0 = +127)

<code>1 1 1 1 0 0 0 0 0 1 1 1 1 1 1 1</code>
2. Cpy $1, +7  ($1 = +7)

<code>1 1 1 1 0 0 0 1 0 0 0 0 0 1 1 1</code>
3. Sll $0, $1, $2 ($2 = 16256)

<code>1 1 0 1 0 0 0 0 0 0 0 1 0 0 1 0</code>
4. Add $2, $0, $3 ($3 = 16383)

<code>1 1 0 0 0 0 1 0 0 0 0 0 0 0 1 1</code>

5. Cpy $1, +2 ($1 = +2)

<code>1 1 1 1 0 0 0 1 0 0 0 0 0 0 1 0</code>
6. Sll $3, $1, $4 ($4 = 65532)

<code>1 1 0 1 0 0 1 1 0 0 0 1 0 1 0 0</code>

7. Cpy $0, +3 ($0 = +3)

<code>1 1 1 1 0 0 0 0 0 0 0 0 0 0 1 1</code>

8. Add $4, $0, $15 ($15 = 65535)

<code>1 1 0 0 0 1 0 0 0 0 0 0 1 1 1 1</code>

9. Since the instructions are all executed, PC now points to nothing, CPU can return the result on reading $15, which is predefined as the return value register.

### Translating the code.

<code>Cpy $0, +32</code>  --- <code>int *a = 0x20</code> 

<code>Cpy $1, +0</code> --- <code>int s = 0</code> (to ensure that the register value is 0)

<code>Cpy $2, +0</code> --- <code>int i = 0</code> (to ensure that the register value is 0)

<code>Cpy $3, +9</code> --- ($3 = +9, +9 = 10 - 1, given the special position of the conditional branch in the instruction)

<code>Cpy $12, +4</code> --- ($12 = +4)

<code>Cpy $11, +1</code> --- ($13 = +1)

<code>XOR $2, $3, $14</code> --- (compare i and 9, storing the result in $14)

<code>Load $0, $13, +0</code> --- ($13 = *a)

<code>Add $1, $13, $1</code> --- <code> s += *a </code> (since $13 = *a)

<code>Add $0, $12, $0</code> --- <code> a += 4 </code>

<code>Add $2, $11, $2</code> --- <code> i++ </code>

<code>Bne $14, -20</code> (jump back to XOR $2, $3, $14)


