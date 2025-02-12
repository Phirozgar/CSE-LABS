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
	MOV R0, #5			; Input value
	BL FACTORIAL		; Function call
STOP
	B STOP
FACTORIAL
	CMP R0, #0			; Base case R0 = 0
	MOVEQ R0, #1		; 0! = 1
	BXEQ LR				; Return from base case
	STMDB SP!, {R0, LR}	; Push current input and link register value onto stack
	SUB R0, R0, #1		; Update input for next function call to R0 - 1
	BL FACTORIAL		; Recursive function call
	LDMIA SP!, {R1, LR}	; Pop previous input and link register values from stack
	MUL R0, R1, R0		; Calculate factorial with stack values
	BX LR				; Return
	END