(START)

	@1 // Push constant 1
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@SKIP
	0;JMP

(SKIP)

	@3 // Push constant 3
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


