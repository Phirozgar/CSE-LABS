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
	MOV R0, #5
	MOV R1, #10
	MOV R2, #15
	MOV R3, #20
	ADD R5, R0, R1
	ADD R6, R2, R3
	ADD R10, R5, R6
STOP B STOP
	  END