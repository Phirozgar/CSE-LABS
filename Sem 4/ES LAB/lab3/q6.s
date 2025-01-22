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
	LDR R0, =SRC
	MOV R1, #0
	MOV R2, #1
	STR R1, [R0]
	ADD R0, R0, #4
	STR R2, [R0]
	ADD R0, R0, #4
	MOV R10, #5
LOOP
	ADD R4, R1, R2
	STR R4, [R0]
	ADD R0, R0, #4
	MOV R1, R2
	MOV R2, R4
	SUBS R10, R10, #1
	BNE LOOP
STOP 
	B STOP
SRC DCD 
END