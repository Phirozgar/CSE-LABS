	AREA	RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
		DCD 0X10001000
		DCD Reset_Handler
		ALIGN
		AREA	mycode, CODE, READONLY
		ENTRY
		EXPORT Reset_Handler
Reset_Handler
	LDR R10, =OP1
	LDR R1, [R10]
	LDR R11, =OP2
	LDR R2, [R11]
GCD
	CMP R1, R2
	BMI R2G
	SUB R1, R1, R2	; Subtract smaller no. from larger no.
RETA
	CMP R1, #0
	BEQ BRKA
	CMP R2, #0
	BEQ BRKB		; if either are 0, GCD is the other, exit loop
	B GCD
RETB
	LDR R1, [R10]
	LDR R2, [R11]
	MOV R4, #0
	MUL R5, R1, R2	; Find largest possible LCM (R1 * R2)
DIVIDE				; And then divide it with calulated GCD
	SUB R5, R5, R3
	ADD R4, #1
	CMP R5, R3
	BPL DIVIDE
STOP
	B STOP
R2G
	SUB R2, R2, R1
	B RETA
BRKA
	MOV R3, R2
	B RETB
BRKB
	MOV R3, R1
	B RETB
	ALIGN 4
OP1	DCD 24
OP2 DCD 16
END