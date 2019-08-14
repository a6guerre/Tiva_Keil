            AREA |.text|, CODE, READONLY,ALIGN=2
			THUMB
			REQUIRE8
			PRESERVE8
				
			IMPORT currentPt
			EXPORT SysTick_Handler
			EXPORT osSchedulerLaunch
				
OS_DisableInterrupts
	CPSID 		I
	BX 			LR
	
OS_EnableInterrupts
	CPSIE 		I
	BX			LR
	
SysTick_Handler             ; saves r0,r1,r2,r3,r12,lr,pc,psr
	CPSID		I
	PUSH        {R4-R11}    ; saves r4-r11
	LDR         R0, =currentPt
	LDR         R1, [R0]
    STR         SP, [R1]
	LDR         R1, [R1,#4] ; r1 = currentPt->next
	STR         R1, [R0]    ; currentPt = r1
	LDR         SP, [R1]    ; SP = currentPt->stackPt
	POP         {R4-R11}
	CPSIE       I
	BX          LR          ; Automatically restored by processor
	
osSchedulerLaunch
	LDR			R0, =currentPt
	LDR         R2, [R0] 
	LDR         SP, [R2] ;SP = currentPt->stackPt
	POP         {R4-R11}
	POP         {R0-R3}
	POP 		{R12}
	POP         {LR};SP,SP,#4
	POP         {LR}
	POP         {R1};SP,SP,#4
	CPSIE       I
	BX          LR
	
    ALIGN
    END