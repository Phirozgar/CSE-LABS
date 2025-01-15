    AREA    RESET, DATA, READONLY
    EXPORT __Vectors
__Vectors
		DCD 0X10001000
		DCD Reset_Handler
		ALIGN 4
		AREA    mycode, CODE, READONLY
		ENTRY
		EXPORT Reset_Handler
Reset_Handler
		LDR R0, =SRC
		LDR R1, =DST
		MOV R2, #0
LOOP	LDR R3, [R0, R2]
		STR R3, [R1, R2]
		ADD R2, #4
		CMP R2, #40
		BNE LOOP
STOP 
	B STOP              ; Infinite loop to halt processor



END
