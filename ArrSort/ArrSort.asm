// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize counters and temporary variables
@0         
D=0
@i         // Outer loop counter i = 0
M=D
@j         // Inner loop counter j = 0
M=D
@R2        
D=M
@outer     // Set outer loop boundary to (length - 1)
M=D-1
@inner     // Set inner loop boundary to (length - 1)
M=D-1

@R5        // Set a flag value in R5 to -1 (True)
M=-1  

(OUTERLOOP)
@i
D=M
@inner
M=M-D    // Update inner loop boundary
@j
M=0      // Reset inner loop counter j

(INNERLOOP)
@R1       
D=M
@j
A=D+M    // Address of arr[j]
D=A
@R11
M=D      // Store address of arr[j] to R11

@R1
D=M
@j
A=D+M+1  // Address of arr[j + 1]
D=A
@R12
M=D      // Store address of arr[j+1] to R12

@R11
A=M
D=M
@R12
A=M
D=D-M
@SWAP
D;JGT    // If arr[j] > arr[j+1], go to SWAP

(RETURN)
@j
M=M+1
D=M
@inner
D=D-M
@INNERLOOP
D;JLT

@i
M=M+1
D=M
@outer
D=D-M
@OUTERLOOP
D;JLT

@R5
D=M
@R0
M=D
@END
0;JMP    // Halt

(SWAP)
@R11
A=M
D=M
@R13
M=D      // Store arr[j] to R13
@R12
A=M
D=M
@R11
A=M
M=D      // Update arr[j] to arr[j+1]
@R13
D=M
@R12
A=M
M=D      // Update arr[j+1] to arr[j]
@RETURN
0;JMP