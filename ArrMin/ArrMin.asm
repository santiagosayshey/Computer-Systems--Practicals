// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize
@i      // Counter i
M=0

@R1     // Assume R1 holds the base address of the array
D=M
@i      // Compute address of the first element, i.e., base + 0
AM=D+M  // Update i and set A register
D=M     // Load the value of the first element of the array
@R0     // Assume R0 will hold the minimum value found
M=D
@R3     // R3 will also hold the minimum value found for comparison
M=D
@R2     // Assume R2 holds the length of the array
M=M-1   // Decrement length as we already processed one element

// Start Loop
@LOOP
0;JMP

// Find Minimum
(MINIMUM)
@i
AM=M    // Increment address to the next element and set A register
D=M     // Load the value of the next element
@R0     // Update R0 to hold the new minimum if found
M=D
D=M     // Load minimum value to D for comparison
@R3
M=D     // Update R3 to hold the minimum for comparison
@R2
M=M-1   // Decrement the length counter as another element is processed
D=M
@END
D;JEQ   // If the length counter reaches 0, jump to END

// Continue Loop
(LOOP)
@R0
D=M     // Load current minimum to D
@R3
M=D     // Update R3 for comparison
@i
AM=M+1  // Increment address to the next element and set A register
D=M     // Load the value of the next element
@R3
D=M-D   // Compare the value with current minimum
M=D     // Store the result of comparison in R3
@MINIMUM
D;JGT   // If the next element is greater, jump to MINIMUM to update minimum
@R2
M=M-1   // Decrement the length counter as another element is processed
D=M
@END
D;JEQ   // If the length counter reaches 0, jump to END
@LOOP
0;JMP   // Continue with the next element

// End the program
(END)
@END
0;JMP   // Halt
