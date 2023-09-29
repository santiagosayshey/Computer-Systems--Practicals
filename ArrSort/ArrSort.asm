// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initializing Pointers and addresses
@R1 // Set to the address of arr[0]
D=M-1 // Subtract 1 to account for array starting from arr[0]
@R2 // Set to the length of the array
M=M+D // Update R2 to the address of the last element

(OuterLoopStart)
    // Check Termination Condition of Outer Loop
    (CheckOuterTerminate)
    @R1
    D=M
    @R2
    D=D-M
    @ProgramEnd
    D;JGT // If D>0, jump to ProgramEnd
    
    @R1
    D=M
    @R3 // Set R3 as the index of the inner loop
    M=D+1 
    
    // Inner Loop starts here
    (InnerLoopStart)
        // Check Termination Condition of Inner Loop
        (CheckInnerTerminate)
        @R3
        D=M
        @R2
        D=D-M
        @InnerLoopEnd
        D;JGT // If D>0, jump to InnerLoopEnd
        
        // Check Element Position
        @R3 // Set to inner index to locate the element
        A=M
        D=M // D now contains the element pointed by the inner index
        @PosElementCheck
        D;JGE // If D>=0, jump to PosElementCheck
        @NegElementCheck
        0;JMP // Else, jump to NegElementCheck
        
        // Swap the values pointed by the inner and outer index pointers
        (SwapElements) 
        @R1
        A=M
        D=M
        @temp
        M=D
        @R3
        A=M
        D=M
        @R1
        A=M
        M=D
        @temp
        D=M
        @R3
        A=M
        M=D
        
        // Skip to next inner index
        (SkipInner)
        @R3
        M=M+1
        @InnerLoopStart
        0;JMP // Jump back to InnerLoopStart

    // End of Inner Loop
    (InnerLoopEnd)
    @R1
    M=M+1 // Move to the next outer index
    @OuterLoopStart
    0;JMP // Jump back to OuterLoopStart

// End of Outer Loop
(ProgramEnd)
@R0
M=-1 // Set R0 to -1

// End of program
(EndExecution)
@EndExecution
0;JMP // Jump to EndExecution to finish execution

// Reference Position Checks and Subtraction Operations
(NegRefCheck)
(PosRefCheck)
// Perform Subtraction Operation
@R3
A=M
D=M
@R1
A=M
D=D-M // Subtraction, may cause Overflow!
@SkipSubstraction
D;JGE // If D>=0, jump to SkipSubstraction
@SwapElements
0;JMP

(NegElementCheck)
@R1
A=M
D=M
@NegRefCheck
D;JLT // If D<0, jump to NegRefCheck
@SwapElements
0;JMP

(PosElementCheck)
@R1
A=M
D=M
@PosRefCheck
D;JGE // If D>=0, jump to PosRefCheck
@SkipInner
0;JMP