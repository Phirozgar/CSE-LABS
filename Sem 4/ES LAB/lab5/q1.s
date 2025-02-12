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
	BL MEMINIT			; Function to initialize R/W mem. with array.
	LDR R0, =SRC		; Get base index of array
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
STOP
	B STOP
MEMINIT
	LDR R0, =PRG		; Load array base address in RO area
	LDR R3, =SRC		; Load array base address in RW area
	MOV R1, #0			; Loop offset
LOOP
	LDR R2, [R0, R1]
	STR R2, [R3, R1]	; Transfer from PRG to SRC
	ADD R1, #4			; Update loop offset
	CMP R1, #40
	BNE LOOP			; If R1 != 40, continue
	BX LR				; Return
	ALIGN
PRG DCD 2,1,7,6,8,0,9,5,4,3
	AREA mydata, DATA, READWRITE
SRC DCD 0		
	END
selsort.s
Displaying selsort.s.