@R1
A=M
D=M
@R0
M=D

@R2
D=M
@R3
M=D  // Initialize R3 as the counter

@R3
D=M
@END
D;JEQ  // If array length is 0, end the program

(LOOP)
@R1
A=M
D=M   // Load the current element

@R0
D=M-D // Subtract from the current minimum value

@NOT_UPDATE
D;JGE // If the result is >=0, do not update R0

@R1
A=M
D=M   // Update R0 with the new smaller value
@R0
M=D

(NOT_UPDATE)
@R1
M=M+1 // Move to the next element in the array

@R3
M=M-1
D=M   // Decrement counter
@LOOP
D;JGT // If more elements are there, repeat the loop

(END)
0;JMP  // End of the program
