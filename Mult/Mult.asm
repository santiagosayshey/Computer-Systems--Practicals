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
M=0 // Clear R0 to store the result.

@R1
D=M
@R4
M=D // Store value of R1 in R4.

@R2
D=M
@R3
M=D // Store value of R2 in R3.

@R5
M=0 // Set R5 as the sign flag, 0 is positive.

// Check if either R1 or R2 is zero.
@R4
D=M
@END
D;JEQ // If R1 is zero, jump to END.

@R3
D=M
@END
D;JEQ // If R2 is zero, jump to END.

// Check if R1 is negative.
@R4
D=M
@CHECK_R2
D;JGE // If R1 is positive, jump to CHECK_R2.

@R4
M=-D // Make R1 positive.
@R5
M=!M // Flip the sign flag.

// Check if R2 is negative.
(CHECK_R2)
@R3
D=M
@MULTIPLY
D;JGE // If R2 is positive, jump to MULTIPLY.

@R3
M=-D // Make R2 positive.
@R5
M=!M // Flip the sign flag.

// Start of the multiplication loop.
(MULTIPLY)
@R3
D=M
@END
D;JEQ // If R2 is zero, jump to END.

@R4
D=M
@R0
M=D+M // Add R1 to R0.

@R3
MD=M-1 // Decrement R2.

@MULTIPLY
D;JGT // If R2 is greater than zero, jump to MULTIPLY.

// Adjust the sign of the result if needed.
@R5
D=M
@END
D;JEQ // If the sign flag is zero, jump to END.

@R0
M=-M // Negate the result in R0.

(END)

