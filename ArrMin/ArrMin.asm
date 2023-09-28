// Initialization: Set R0 to the first element in the array
@R1
A=M
D=M
@R0
M=D

// Initialize R3 as the counter
@R2
D=M
@R3
M=D

// Check if the array length is <= 0, if so, skip the loop
@R3
D=M
@END
D;JLE  // Jump if the length is less than or equal to 0

// Loop begins
(LOOP)

// Decrement our loop counter (R3) first
@R3
M=M-1
D=M
@END
D;JLE // If R3 is less than or equal to 0, end the loop

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

// Jump to the beginning of the loop
@LOOP
0;JMP

// End of program
(END)
@END
0;JMP