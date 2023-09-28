// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize counters and temporary variables
@i         // Outer loop counter
M=0
@j         // Inner loop counter
M=0
@R2        // Assume R2 holds the length of the array
D=M
@outer    // Set outer loop boundary
M=D-1
@inner     // Set inner loop boundary
M=D-1

// Set a flag value in R5
@R5
M=0
M=M-1  // Setting R5 to -1

// Start of the outer loop
(OUTERLOOP)
@i
D=M      // Load outer loop counter
@inner
M=M-D    // Update inner boundary per outer counter
@j
M=0      // Reset inner counter

// Start of the inner loop
(INNERLOOP)
@j
D=M      // Load inner loop counter
@R1      // Assume R1 holds the base address of the array
A=M+D    // Compute the address of arr[j]
D=A
@R11     // Store address of arr[j] to R11
M=D

@j
D=M+1    // Load inner loop counter and add 1
@R1
A=M+D    // Compute the address of arr[j+1]
D=A
@R12     // Store address of arr[j+1] to R12
M=D

// Compare arr[j] and arr[j+1]
@R11
A=M
D=M
@R12
A=M
D=D-M    // Compute arr[j] - arr[j+1]
@SWAP
D;JGT    // If arr[j] > arr[j+1], jump to SWAP

(RETURN)
@j
M=M+1    // Increment inner loop counter
D=M
@inner
D=D-M    // Check if we have reached the inner loop boundary
@INNERLOOP
D;JLT    // If not, continue with the inner loop

// Check for outer loop boundary
@i
M=M+1    // Increment outer loop counter
D=M
@outer
D=D-M    // Check if we have reached the outer loop boundary
@OUTERLOOP
D;JLT    // If not, continue with the outer loop

@END
0;JMP    // If both loops are complete, jump to END

// Swap arr[j] and arr[j+1] if needed
(SWAP)
@R11
A=M
D=M      // Load arr[j]
@R13     // Store arr[j] to R13
M=D

@R12
A=M
D=M      // Load arr[j+1]
@R11
A=M
M=D      // Update arr[j] to arr[j+1]

@R13
D=M      // Load arr[j] from R13
@R12
A=M
M=D      // Update arr[j+1] to arr[j]
@RETURN
0;JMP    // Return to the previous point in the inner loop

// End the program and signal completion
(END)
@R5
D=M      // Load the flag value from R5
@R0
M=D      // Update R0 to signal completion
@END
0;JMP    // End the program
