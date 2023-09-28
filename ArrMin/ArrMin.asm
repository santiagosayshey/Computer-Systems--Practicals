// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Initialization: Set R0 to the first element in the array
@R1
A=M
D=M
@R0
M=D  // R0 = first element of the array

// Set R3 as the counter (equivalent to a 'for loop' iterator in high-level languages)
@R2
D=M
@R3
M=D  // R3 = R2 (length of the array)

// Check if the array length is 0, if so, skip the loopa
@R3
D=M
@END
D;JEQ  // if array length is 0, jump to END

// Loop begins
(LOOP)

// Load the next element from the array
@R1
A=M
D=M   // D = *R1 (current array element)

@R0
D=M-D // D = R0 - current array element

@CONTINUE
D;JGE  // If D >= 0 (R0 >= current array element), jump to CONTINUE

// If we are here, the current array element is smaller than R0
@R1
A=M
D=M
@R0
M=D  // Update R0 with the new smaller value

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
D;JGT  // If R3 > 0, continue the loop

// End of program
(END)
@END
0;JMP
