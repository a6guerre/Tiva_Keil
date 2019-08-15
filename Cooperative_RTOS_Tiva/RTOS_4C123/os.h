#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H
#include "tm4c123gh6pm.h"

#include <stdint.h>
void osKernelLaunch(uint32_t quanta);

void osKernelInit(void);
void osThreadYield(void);

uint8_t osKernelAddThreads(void(*task0)(void),
	                         void(*task1)(void),
													 void(*task2)(void));
													 
#endif