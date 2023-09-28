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

@R1
D=M
@R4
M=D // R4 will hold the shifting R1

@R2
D=M
@R3
M=D // R3 will be used to iterate over the bits of R2

// Handling the sign of the result and making R1 and R2 positive for the multiplication loop
@R5
M=0 // Initialize the sign flag to positive

@R1
D=M
@POSITIVE1
D;JGE

@R1
M=-D // If R1 is negative, make it positive and update the sign flag
@R5
M=!M
(POSITIVE1)

@R2
D=M
@POSITIVE2
D;JGE

@R2
M=-D // If R2 is negative, make it positive and update the sign flag
@R5
M=!M
(POSITIVE2)

// Loop for each bit in R2
(LOOP)
@R3
D=M
@END
D;JEQ // If R3 is zero, end the loop

@R3
D=M
D=D-1
@R3
M=D // Decrement R3

@R4
D=M
@TEMP
M=D // Store the current value of R4 in TEMP

@R2
D=M
@NEXT
D;JLE // If R2 is less than or equal to 0, go to the next iteration

// If the LSB of R2 is 1, add the value of R4 to R0
@R0
M=M+D
@TEMP
D=M
@R0
M=M+D

(NEXT)
@R4
M=M+M // Shift R4 left by 1

@R2
M=M>>1 // Shift R2 right by 1 (divide by 2)

@LOOP
0;JMP // Jump back to the loop

(END)

// Adjusting the sign of the result
@R5
D=M
@NO_NEGATE
D;JEQ

@R0
M=-M // If the sign flag is set, negate R0

(NO_NEGATE)
