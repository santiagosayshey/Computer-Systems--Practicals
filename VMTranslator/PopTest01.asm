	@31 // Push constant 31
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@32 // Push constant 32
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@33 // Push constant 33
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@34 // Push constant 34
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@LCL // Pop local0
	D=M
	@0
	D=D+A
	@R13
	M=D
	@SP
	AM=M-1
	D=M
	@R13
	A=M
	M=D


	@ARG // Pop argument1
	D=M
	@1
	D=D+A
	@R13
	M=D
	@SP
	AM=M-1
	D=M
	@R13
	A=M
	M=D


	@THIS // Pop this2
	D=M
	@2
	D=D+A
	@R13
	M=D
	@SP
	AM=M-1
	D=M
	@R13
	A=M
	M=D


	@THAT // Pop that3
	D=M
	@3
	D=D+A
	@R13
	M=D
	@SP
	AM=M-1
	D=M
	@R13
	A=M
	M=D


