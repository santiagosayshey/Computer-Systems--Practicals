	@9 // Push constant 9
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@14 // Push constant 14
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@SP
	AM=M-1
	D=M
	A=A-1
	D=M-D
	@LESS_0
	D;JLT
	@SP
	A=M-1
	M=0
	@END_LESS_1
	0;JMP
(LESS_0)
	@SP
	A=M-1
	M=-1
(END_LESS_1)

