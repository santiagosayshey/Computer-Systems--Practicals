// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Bubble sort implementation for Hack assembly

@R1
D=M     // Start address of the array
@START
M=D     // START stores the start address of the array

@R2
D=M-1   // D = Length of the array - 1 (since we count from 0)
@SIZE
M=D     // SIZE stores the length of the array - 1

(LOOP)
@SIZE
D=M     // Load SIZE into D
@ENDLOOP
D;JLE   // Jump to ENDLOOP if D <= 0

@START
A=M     // Point to the start of the array
D=M     // Load first element into D

@I
M=0     // Reset I to 0

(SWAPLOOP)
@I
D=M     // Load I into D
@SIZE
D=D-M   // Subtract SIZE from I
@ENDSWAPLOOP
D;JLE   // Jump to ENDSWAPLOOP if D <= 0

@START
A=M+A   // Point to the current element
D=M     // Load current element into D

@START
A=M+A+1   // Point to the next element
D=D-M     // Subtract next element from current
@NOSWAP
D;JGE     // Jump to NOSWAP if no swap is needed

// Swap the two numbers
@START
A=M+A
M=M+D     // Add the difference to the current number (making it the larger number)

@START
A=M+A+1
M=M-D     // Subtract the difference from the next number (making it the smaller number)

(NOSWAP)
@I
M=M+1   // Increment I
@SWAPLOOP
0;JMP

(ENDSWAPLOOP)
@SIZE
M=M-1   // Decrement SIZE
@LOOP
0;JMP

(ENDLOOP)
@R0
M=-1   // Set R0 to True (-1) to indicate completion
(END)
@END
0;JMP
