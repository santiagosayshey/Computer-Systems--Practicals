	@0 // Push constant 0
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


	@SP
	AM=M-1
	D=M
	@TRUE
	D;JNE

	@END
	0;JMP

(TRUE)

	@3 // Push constant 3
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


(END)

	@0 // Push constant 0
	D=A
	@SP
	A=M
	M=D
	@SP
	M=M+1


