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
	MOV R1, #2
	MOV R2, #0
LOOP
	MOV R3, R0
	SUBS R0, R0, R1
	BMI STOP
	ADD R2, R2, #1
	B LOOP
STOP 
	B STOP
N1 DCD 0x11111001
N2 DCD 0x11111101
END