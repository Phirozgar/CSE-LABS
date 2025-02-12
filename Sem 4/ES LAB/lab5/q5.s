	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC
	LDR R1, =A
	SUB R1, R1, #4
	LDR R2, =B
	ADD R2, R2, #24
LOOP	ADD R4, R0, R3;load the address of new element
	LDR R5, [R4]; load the new element
	ADD R1, R1, #4;push into full ascending stack
	STR R5, [R1]
	STR R5, [R2];push into empty descending stack
	SUB R2, R2, #4
	ADD R3, R3, #4; increment the index
	SUBS R6, R3, #24; check for out bounds
	BNE LOOP
	MOV R3, #0;initialize counter
LOOP1 LDR R4, [R1];pop from full ascending stack
	SUB R1, R1, #4
	ADD R2, R2, #4;pop from empty descending stack
	LDR R5, [R2]
	ADD R3, R3, #1; increment counter
	SUBS R6, R3, #6; check for out bounds
	BNE LOOP1
STOP
	B STOP
SRC DCD 1, 3, 5, 6, 2, 12
	AREA mydata, DATA, READWRITE
A DCD 0, 0, 0, 0, 0, 0;fully ascending stack
B DCD 0, 0, 0, 0, 0, 0; empty descending stack
	END