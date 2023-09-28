// Initialization: Set R0 to 32767 (maximum possible value)
@32767
D=A
@R0
M=D

// Check if the array length is 0 or less; if so, end the program
@R2
D=M
@END
D;JLE

(LOOP)
@R1
A=M+1 // Point to the next element in array
D=M   // Get the next element value

@R0
D=M-D // Compare with the minimum found till now

@CONTINUE
D;JGE // If the current element is greater or equal, continue to the next element

@R1
A=M
D=M   // Else, update R0 with the new minimum value
@R0
M=D

(CONTINUE)
@R2
M=M-1
D=M   // Decrement the array length (counter)
@LOOP
D;JGT // If more elements are there, continue the loop

(END)
0;JMP // End the program
