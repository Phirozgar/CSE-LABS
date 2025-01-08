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
	MOV R7, #15
	MOV R8, #10
	SUB R10, R7, R8
STOP B STOP
	  END