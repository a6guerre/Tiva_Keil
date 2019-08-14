#include "os.h"
#include "tm4c123gh6pm.h"

#define NUM_OF_THREADS 3
#define STACK          100
void osSchedulerLaunch(void);

struct tcb{
   int32_t *stackPt;
	 struct tcb *nextPt;
};
typedef struct tcb tcbType;
tcbType tcbs[NUM_OF_THREADS];
tcbType *currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACK];

void osKernelStackInit(int i){
   tcbs[i].stackPt = &TCB_STACK[i][STACK-16];
	 TCB_STACK[i][STACK-1] = 0x01000000;
	
}

uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void))
{
   tcbs[0].nextPt = &tcbs[1];
   tcbs[1].nextPt = &tcbs[2];
   tcbs[2].nextPt = &tcbs[0];
   
   osKernelStackInit(0);
   TCB_STACK[0][STACK-2] = (int32_t)(task0);
	 osKernelStackInit(1);
	 TCB_STACK[1][STACK-2] = (int32_t)(task1);
	 osKernelStackInit(2);
	 TCB_STACK[2][STACK-2] = (int32_t)(task2);
	 currentPt = &tcbs[0];
	
   return 1;
}

void OS_Init(void)
{
	 PLL_Init();
   //SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_6MHZ|SYSCTL_OSC_MAIN);
	 NVIC_ST_CTRL_R = 0;
	 NVIC_ST_CURRENT_R = 0;
	 NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R& 0x00FFFFFF)|0xE0000000;
}

void osKernelLaunch(uint32_t quanta)
{
	 NVIC_ST_RELOAD_R = quanta - 1;
	 NVIC_ST_CTRL_R = 0x00000007;
   osSchedulerLaunch();
}
// scheduler
// thread control block
// stack to hold the context
