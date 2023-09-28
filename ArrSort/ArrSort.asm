// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
//resetting the counters for the inner and outter loop
@i
M=0
@j
M=0
@R2
D=M
@outter
M=D-1
@inner
M=D-1
@R5
M=0
M=M-1


(OUTERLOOP)
@i
D=M
@inner
M=M-D
@j
M=0

(INNERLOOOP)
// storing address of arr[j]
@j
D=M
@R1
A=M+D
D=A
@R11
M=D
 
// Storing Address of arr[j+1]
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
D;JGT

(RETURNPOINT)
// Checking if still in the innerLoop
@j
M=M+1
D=M
@inner
D=D-M
@INNERLOOOP
D; JLT

//Checkfor outside loop
@i
M=M+1
D=M
@outter
D=D-M
@OUTERLOOP
D;JLT

@END
0; JMP

(SWAP)
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
@RETURNPOINT
0;JMP

(END)
@R5
D=M
@R0
M=D
@END
0; JMP