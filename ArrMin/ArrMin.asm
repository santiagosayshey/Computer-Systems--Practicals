// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Initialization: Set R0 to the first element in the array
@R1
A=M
D=M
@R0
M=D  // R0 = first element of the array

// Set R3 as the counter
@R2
D=M
@R3
M=D  // R3 = R2 (length of the array)

// Check if the array length is 0, if so, skip the loop
@R3
D=M
@END
D;JEQ  // if array length is 0, jump to END

(LOOP)
// Load the next element from the array
@R1
A=M
D=M   // D = *R1 (current array element)

@R0
D=D-M // D = current array element - R0

// Check for Overflow, when one number is positive and another is negative
@CHECK_OVERFLOW
D;JLT  // If D<0 (signs were different), jump to CHECK_OVERFLOW

// Here, D>=0, no overflow occurred, now we can safely compare
@CONTINUE
D;JGE  // If D >= 0 (R0 >= current array element), jump to CONTINUE

// Update R0 with the new smaller value
@R1
A=M
D=M
@R0
M=D

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

(CHECK_OVERFLOW)
@R0
D=M    // Load R0

@R1
A=M
D=D-M // D = R0 - *R1

@CONTINUE
D;JLT  // If D < 0 (R0 < *R1), jump to CONTINUE

// If we are here, *R1 < R0, so update R0
@R1
A=M
D=M
@R0
M=D

@CONTINUE
0;JMP  // Jump to CONTINUE unconditionally