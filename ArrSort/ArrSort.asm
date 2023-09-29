// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@R1 
D=M-1 
@R2
M=M+D 

(OUTER)

    (EARLY_TERMINATE)
    @R1
    D=M
    @R2
    D=D-M
    @SORTED
    D;JGT
    @R1
    D=M
    @R3
    M=D+1 


(INNER)

    (CHECK_INNER_END)
    @R3
    D=M
    @R2
    D=D-M
    @NEXT_INNER
    D;JGT
    @R3 
    A=M
    D=M 
    @ELEM_POS
    D;JGE
    @ELEM_NEG
    0;JMP

    (SWAP) // swap if smaller
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

    (SKIP)
    @R3
    M=M+1
    @INNER

0;JMP

    (NEXT_INNER)
    @R1
    M=M+1
    @OUTER
    0;JMP

(SORTED)
@R0
M=-1
(END)
@END
0;JMP

(REF_NEG)

(REF_POS)
// subs
@R3
A=M
D=M
@R1
A=M
D=D-M
@SKIP
D;JGE
@SWAP
0;JMP

(ELEM_NEG)
@R1
A=M
D=M
@REF_NEG
D;JLT
@SWAP
0;JMP

(ELEM_POS)
@R1
A=M
D=M
@REF_POS
D;JGE
@SKIP
0;JMP