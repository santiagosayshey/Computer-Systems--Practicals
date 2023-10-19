@10 // Push constant 10
D=A
@SP
A=M
M=D
@SP
M=M+1


@LCL // Push local 1
D=M
@1
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1


@ARG // Push argument 2
D=M
@2
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1


@THIS // Push this 3
D=M
@3
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1


@THAT // Push that 4
D=M
@4
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1


@R10 // Push temp 5
D=M
@SP
A=M
M=D
@SP
M=M+1


@R3 // Push pointer 0
D=M
@SP
A=M
M=D
@SP
M=M+1


@16 // Push static 6
D=A
@6
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1


