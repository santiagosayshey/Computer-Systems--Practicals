// Initialization: Set R0 to the first element in the array
@R1
A=M
D=M
@R0
M=D // R0 now holds the first element of the array

// Check if the array length is 0 or less, if so, end the program
@R2
D=M
@END
D;JLE // If array length (R2) is less than or equal to 0, Jump to END

// Loop begins
(LOOP)
@R1
M=M+1 // Move R1 to the next array element
A=M   // Load the address of the next array element
D=M   // Load the next array element to D

@R0
D=M-D // Subtract the value in R0 from the current array element
@CONTINUE
D;JGE // If the current array element is greater than or equal to R0, go to CONTINUE

// If we are here, it means we found a smaller element. Update R0
@R1
A=M
D=M
@R0
M=D // Update R0 with the new smallest value

// Continue with the next iteration
(CONTINUE)
@R2
M=M-1 // Decrement the counter (array length)
D=M  // Load the updated counter
@LOOP
D;JGT // If the counter (array length) is greater than 0, go back to LOOP

// End of program
(END)
0;JMP
