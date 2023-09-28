// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Initialization: Set R0 to the first element in the array
@R1
A=M
D=M
@R0
M=D

// Set R3 as the counter (equivalent to a 'for loop' iterator in high-level languages)
@R2
D=M
@R3
M=D

// Check if the array length is 0, if so, skip the loop
@R3
D=M
@END
D;JEQ

// Loop begins
(LOOP)

// Compare R0 with the current array element
@R1
A=M
D=M

@R0
D=D-M
@CONTINUE
D;JGE  // If current array element is greater than or equal to R0, don't update R0

// Update R0 with the smaller value found in the array
@R1
A=M
D=M
@R0
M=D

// Labels for clarity
(CONTINUE)

// Move to the next array element
@R1
M=M+1

// Decrement our loop counter (R3)
@R3
M=M-1
@R3
D=M
@LOOP
D;JGT  // If R3 is greater than 0, continue the loop

// End of program
(END)
@END
0;JMP
