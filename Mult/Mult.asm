// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Initialization
@R0
M=0
@R2
D=M

@R5
M=0          // This will be our flag. 0 for positive R2, and 1 for negative R2.

@NEGATIVE
D;JLT

@R3
M=D
@CHECK
0;JMP

(NEGATIVE)
@R3
M=-D
@R5
M=1          // Mark that R2 was negative.
@CHECK
0;JMP

// Begin the multiplication loop
(CHECK)
@R3
D=M
@END
D;JEQ

(ADD)
@R1
D=M
@R0
M=M+D
@R3
M=M-1
@CHECK
0;JMP

(END)
@R5
D=M
@NO_NEGATE
D;JEQ

// Negate R0
@R0
M=-M

(NO_NEGATE)
