	@31 // Push constant 31
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


	@32 // Push constant 32
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@ARG // Pop argument0
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


	@33 // Push constant 33
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@THIS // Pop this0
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


	@34 // Push constant 34
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@THAT // Pop that0
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


