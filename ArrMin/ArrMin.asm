// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize Pointers and addresses
@R1 // Address of arr[0]
D=M-1 // Adjust for array starting from arr[0]
@R2 // Address of the length
M=M+D // Set R2 to the address of the last element

// Set R0 with the maximum value 32767
@32767
D=A
@R0
M=D

(MainLoop)
    // Check Termination Condition
    (CheckTerminate)
    @R1
    D=M
    @R2
    D=D-M
    @EndLoop
    D;JGT // If D>0, jump to EndLoop
    
    // Check Element Position
    @R1
    A=M
    D=M
    @PosCheck
    D;JGE // If D>=0, jump to PosCheck
    @NegCheck
    0;JMP // Else, jump to NegCheck
    
    // Update R0
    (UpdateR0)
    @R1
    A=M
    D=M
    @R0
    M=D
    
    // Skip to next element
    (SkipElement)
    @R1
    M=M+1
    @MainLoop
    0;JMP // Jump back to MainLoop

// End of Loop
(EndLoop)
@EndLoop
0;JMP // End the execution

// Substraction and Checks
(NegR0)
(PosR0)

// Perform Subtraction
@R1
A=M
D=M
@R0
D=D-M // Subtraction, may cause Overflow!
@SkipUpdate
D;JGE // If D>=0, jump to SkipUpdate
@UpdateR0
0;JMP

// Check for Negative Element
(NegCheck)
@R0
D=M
@NegR0
D;JLT // If D<0, jump to NegR0
@UpdateR0
0;JMP

// Check for Positive Element
(PosCheck)
@R0
D=M
@PosR0
D;JGE // If D>=0, jump to PosR0
@SkipElement
0;JMP