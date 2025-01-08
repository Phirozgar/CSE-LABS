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
	MOV R0, #2_1010
	MOV R1, #2_0110
	ADD R2, R0, R1
STOP B STOP
	  END