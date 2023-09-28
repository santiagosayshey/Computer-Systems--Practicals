// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Initialize
@R0
M=0  // clear R0
@R4
M=0  // this will store the absolute value of R1
@R5
M=0  // this will store the absolute value of R2
@R6
M=0  // flag, 1 if result should be negative, 0 otherwise

// Check sign of R1 and store absolute value in R4
@R1
D=M
@POS1
D;JGE  // if R1 >= 0, jump to POS1
@R6
M=!M  // toggle flag if R1 is negative
@R4
M=-D  // store absolute value of R1 in R4
@R1_POSITIVE
0;JMP  // jump to R1_POSITIVE

(POS1)
@R4
M=D  // store absolute value of R1 in R4

(R1_POSITIVE)

// Check sign of R2 and store absolute value in R5
@R2
D=M
@POS2
D;JGE  // if R2 >= 0, jump to POS2
@R6
M=!M  // toggle flag if R2 is negative
@R5
M=-D  // store absolute value of R2 in R5
@MULTIPLY
0;JMP  // jump to MULTIPLY

(POS2)
@R5
M=D  // store absolute value of R2 in R5

// Multiplication Loop
(MULTIPLY)
@R5
D=M
@END
D;JEQ  // if R2 is 0, jump to END
@R4
D=M
@R0
M=M+D  // add R1 to R0
@R5
M=M-1  // decrement R2
@MULTIPLY
0;JMP  // jump to MULTIPLY

(END)
@R6
D=M
@FINISH
D;JEQ  // if result is positive, jump to FINISH
@R0
M=-M  // negate R0

(FINISH)