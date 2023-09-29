// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Initialize R3 to hold the result
@R3
M=0

// Copy R2 to R4 and check if it's negative
@R2
D=M
@R4
M=D  // Store a copy of R2 in R4

// Check if R2 is negative.
// If so, make it positive, and at the end flip the sign of the result.
@LOOP
D;JGE  // If R2 >= 0, jump to LOOP
@R2
D=!M  // Make R2 positive if it's negative
M=D+1

// Main Multiplication Loop
(LOOP)
@R1
D=M      // Load R1
@R3
M=D+M    // Add R1 to R3, R3 accumulates the result

@R2
D=M-1    // Decrement R2
M=D

@LOOP
D;JNE    // If R2 is not zero, jump to LOOP

// Check the sign of the original R2 stored in R4
@R4
D=M
@NEGATIVE
D;JLT  // If R4 < 0, jump to NEGATIVE
@POSITIVE
0;JMP  // Else, jump to POSITIVE

// If the result is negative, flip all the bits
(NEGATIVE)
@R3
D=!M    // Flip all the bits of R3
@R0
M=D+1   // Store the result in R0 and increment to get two's complement
@END
0;JMP  // Jump to END

// If the result is positive, store it as it is
(POSITIVE)
@R3
D=M
@R0
M=D    // Store the positive result in R0

// End the program
(END)
@END
0;JMP  // Halt