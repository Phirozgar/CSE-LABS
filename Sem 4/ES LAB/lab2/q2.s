    AREA    RESET, DATA, READONLY
    EXPORT __Vectors
__Vectors
		DCD 0X10001000
		DCD Reset_Handler
		ALIGN
		AREA    mycode, CODE, READONLY
		ENTRY
		EXPORT Reset_Handler
Reset_Handler

    ; Load address of source variable (into R0)
    LDR     R0, =SRC         ; Load source variable address
    ; Load address of destination variable (into R1)
    LDR     R1, =DST         ; Load destination variable address
    ; Load 32-bit value from source memory location in R0 to R2
    LDR     R2, [R0]          ; Load value from source
    ; Store 32-bit value to destination memory location R1 from R2
    STR     R2, [R1]          ; Store value to destination

STOP 
	B STOP              ; Infinite loop to halt processor

SRC DCD 8    ; Source variable with 32-bit value
DST DCD 0    ; Destination variable initialized to zero

END
