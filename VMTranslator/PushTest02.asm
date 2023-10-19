	@LCL // Push local 0
	D=M
	@0
	A=D+A
	D=M
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@ARG // Push argument 1
	D=M
	@1
	A=D+A
	D=M
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@THIS // Push this 2
	D=M
	@2
	A=D+A
	D=M
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@THAT // Push that 3
	D=M
	@3
	A=D+A
	D=M
	@SP
	A=M
	M=D
	@SP
	M=M+1


