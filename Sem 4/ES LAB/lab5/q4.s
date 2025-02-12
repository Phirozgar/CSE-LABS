	AREA	RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
		DCD 0X10001000
		DCD Reset_Handler
		ALIGN 4
		AREA	mycode, CODE, READONLY
		ENTRY
		EXPORT Reset_Handler
Reset_Handler
	BL REGLOADER
	LDR R0, =SRC
	MOV SP, R0
	ADD SP, SP, #40
	STMDB SP!, {R1-R10}
	MOV R1, #0			; Outer loop offset
OUTER
	MOV R2, R1			; Minimum element index
	ADD R3, R1, #4		; Inner loop offset
INNER
	LDR R4, [R0, R2]	; Get min. ele.
	LDR R5, [R0, R3]	; Get current ele.
	CMP R5, R4
	MOVLO R2, R3		; If current ele. < min. ele., rewrite min. index
	ADD R3, #4			; Update inner loop offset
	CMP R3, #40
	BNE INNER			; if R3 != 40, continue INNER
	LDR R6, [R0, R2]
	LDR R7, [R0, R1]
	STR R6, [R0, R1]
	STR R7, [R0, R2]	; Swap current outer loop ele. and discovered min. ele.
	ADD R1, #4			; Update outer loop offset
	CMP R1, #36			
	BNE OUTER			; if R1 != 36, continue
	LDM SP!, {R1-R10}
STOP
	B STOP
REGLOADER
	MOV R1, #2
	MOV R2, #4
	MOV R3, #7
	MOV R4, #1
	MOV R5, #3
	MOV R6, #9
	MOV R7, #0
	MOV R8, #6
	MOV R9, #5
	MOV R10, #8
	BX LR
	ALIGN
	AREA mydata, DATA, READWRITE
SRC DCD 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	END