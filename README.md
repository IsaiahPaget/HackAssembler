# HackAssembler

This is an assembler for the Hack assembly language from the course Nand2Tetris part one.

This assembler feautures case insensitivity and comments

### Assembly Code:

```c
// takes the value in register 1 and the value in register 2 and puts the larger one in register 3

@0
D=M
@1
D=D-M
@10
D;JGT
@1
D=M
@12
0;JMP
@0
D=M
@2
M=D
@14
0;JMP
```

### Output:

```
0000000000000000
1111110000010000
0000000000000001
1111010011010000
0000000000001010
1110001100000001
0000000000000001
1111110000010000
0000000000001100
1110101010000111
0000000000000000
1111110000010000
0000000000000010
1110001100001000
0000000000001110
1110101010000111
```
