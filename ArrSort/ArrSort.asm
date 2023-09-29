// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize loop counters and temporary variables
@i         // Outer loop counter
M=0
@j         // Inner loop counter
M=0
@R2        // Assume R2 holds the length of the array
D=M
@outer     // Set outer loop boundary
M=D
@inner     // Set inner loop boundary
M=D-1

// Set a flag value in R5 to track if any swaps are made
@R5
M=0    // Initialize as 0 (no swaps)

(OUTERLOOP)
@R5
M=0    // Reset swap flag at the start of each outer loop iteration
@i
D=M
@inner
M=M-D    // Update inner boundary per outer counter
@j
M=0    // Reset inner counter j

(INNERLOOP)
@j
D=M
@R1
A=M+D    // Compute the address of arr[j]
D=A
@R11
M=D    // Store address of arr[j] to R11
@j
D=M+1
@R1
A=M+D    // Compute the address of arr[j+1]
D=A
@R12
M=D    // Store address of arr[j+1] to R12

// Compare and possibly swap arr[j] and arr[j+1]
@R11
A=M
D=M
@R12
A=M
D=D-M
@SWAP
D;JGT

(RETURN)
@j
M=M+1
D=M
@inner
D=D-M
@INNERLOOP
D;JLT

// No swap means array is sorted. End the program
@R5
D=M
@END
D;JEQ

@i
M=M+1
D=M
@outer
D=D-M
@OUTERLOOP
D;JLT

(END)
@R0
M=-1    // Signalling the array is sorted
@END
0;JMP  // End the program

(SWAP)
@R5
M=-1   // Set swap flag to true
@R11
A=M
D=M
@R13
M=D
@R12
A=M
D=M
@R11
A=M
M=D
@R13
D=M
@R12
A=M
M=D
@RETURN
0;JMP
