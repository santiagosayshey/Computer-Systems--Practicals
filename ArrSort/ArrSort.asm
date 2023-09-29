// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize counters and temporary variables
@i
M=0
@j
M=0
@R2
D=M
@outer
M=D
@inner
M=D-1

@R5
M=0    // Initialize the swap flag to 0

(OUTERLOOP)
@R5
M=0
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
A=M+D
D=A
@R11
M=D
@j
D=M+1
@R1
A=M+D
D=A
@R12
M=D

@R11
A=M
D=M
@R12
A=M
D=D-M
@SWAP
D;JGT    // If arr[j] > arr[j+1], jump to SWAP

(RETURN)
@j
M=M+1
D=M
@inner
D=D-M
@INNERLOOP
D;JLT    // If inner boundary is not reached, jump to INNERLOOP

@R5
D=M
@END
D;JEQ    // If no swap happened, array is sorted. Jump to END

@i
M=M+1
D=M
@outer
D=D-M
@OUTERLOOP
D;JLT    // If outer boundary is not reached, jump to OUTERLOOP

(END)
@R0
M=-1    // Signalling the array is sorted
@END
0;JMP    // End the program

(SWAP)
@R5
M=-1   // Set swap flag to true
@R11
A=M
D=M
@R13
M=D    // Store arr[j] to R13
@R12
A=M
D=M
@R11
A=M
M=D    // Swap arr[j] and arr[j+1]
@R13
D=M
@R12
A=M
M=D    // Swap arr[j+1] and arr[j]
@RETURN
0;JMP    // Return to INNERLOOP