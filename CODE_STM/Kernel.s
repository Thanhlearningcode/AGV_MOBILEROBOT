			AREA |.TEXT|,CODE,READONLY,ALIGN=2
			THUMB
			EXTERN currentPt
			EXPORT osSchedulerLaunch
			EXPORT SysTick_Handler
				
osSchedulerLaunch
	LDR R0, =currentPt  ; load value of pointer to current TCB to R0
	LDR R2, [R0]		; load value of R0 to R2
	
	LDR SP, [R2]		; load value of R2 to SP
	POP {R4-R11}
	POP {R0-R3}
	POP {R12}
	ADD SP, SP, #4
	POP {LR}
	ADD SP, SP, #4
	
	CPSIE I
	BX LR

SysTick_Handler
	CPSID I
	PUSH {R4-R11}
	LDR R0, =currentPt
	LDR R1, [R0]
	
	STR SP, [R1]
	LDR R1, [R1, #4]
	STR R1, [R0]
	
	LDR SP, [R1]
	POP {R4-R11}
	CPSIE I
	BX LR

	END