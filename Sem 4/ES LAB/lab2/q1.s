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
	MOV R0, #10		; Store immediate value decimal 10 into R0
	LDR R3, =VALUE1	; Load address of VALUE1 into R3
	LDR R4, [R3]	; Load contents of R3 from memory into R4
	MOV R5, R0		; Copy value from R0 to R5
STOP B STOP
;defining a memory location
VALUE1 DCD 8
END
