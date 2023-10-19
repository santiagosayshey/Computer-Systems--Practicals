	@10 // Push constant 10
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@10 // Push constant 10
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
	@EQUAL_0
	D;JEQ
	@SP
	A=M-1
	M=0
	@END_EQUAL_1
	0;JMP
(EQUAL_0)
	@SP
	A=M-1
	M=-1
(END_EQUAL_1)

