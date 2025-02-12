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
	LDR R0, =NUM		; Numbers to push/pop
	LDR R1, =FAS		; Full Ascending stack top pointer
	LDR R2, =EDS+20		; Empty descending stack top pointer
	MOV R3, #0			; Offset variable
PUSHLOOP
	LDR R4, [R0, R3]	; Fetch number
	ADD R1, #4			; Increment FA stack pointer
	STR R4, [R1]		; Store to FA stack
	STR R4, [R2]		; Store to ED stack
	SUB R2, R2, #4		; Decrement ED stack pointer
	ADD R3, #4			; Update offset
	CMP R3, #20
	BNE PUSHLOOP		; If offset != 20, continue
	LDR R5, =OFA		; Pop storage for FA stack
	LDR R6, =OED		; Pop storage for ED stack
	MOV R3, #0			; Reset offset variable
POPLOOP
	LDR R0, [R1]		; Load top element from FA stack
	SUB R1, R1, #4		; Decrement FA stack pointer
	STR R0, [R5, R3]	; Store FA top
	ADD R2, #4			; Increment ED stack pointer
	LDR R0, [R2]		; Load top element from ED stack
	STR R0, [R6, R3]	; Store ED top
	ADD R3, #4			; Update offset
	CMP R3, #20			
	BNE POPLOOP			; If offset != 20, continue
STOP
	B STOP
	ALIGN
NUM DCD 1, 2, 3, 4, 5
	AREA mydata, DATA, READWRITE
FAS DCD 0, 0, 0, 0, 0, 0
EDS DCD 0, 0, 0, 0, 0, 0
OFA DCD 0, 0, 0, 0, 0
OED DCD 0, 0, 0, 0, 0
	END