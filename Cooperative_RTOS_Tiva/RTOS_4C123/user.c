#include "os.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
int Count1, Count2, Count3;
int nvicRegVal, stCtrl;
void Task1(void) 
{
	 
	 NVIC_ST_CTRL_R = 0; // Disable counter and interrupts
	 Count1 = 0;
	 int iter, delay;
	 for(;;){
      for(iter = 0; iter < 10; ++iter){
	       ++Count1;
		     GPIO_PORTF_DATA_R &= ~0x04;
		     GPIO_PORTF_DATA_R &= ~0x08;
		     GPIO_PORTF_DATA_R ^= 0x02;
			   delay = 0;
		     for(delay = 0; delay < 500000; delay++){
				    ++Count1;					 
			   }
				 ++Count1;
	    }
			osThreadYield();
			NVIC_ST_CTRL_R = 0; // Disable counter and interrupts
	 }
}

void Task2(void) 
{
	 Count2 = 0;
	 NVIC_ST_CTRL_R = 0x00000007; // Re-enable counter and interrupts
	 stCtrl = NVIC_ST_CTRL_R;
	 nvicRegVal = NVIC_ST_CURRENT_R;
   for(;;){
		  NVIC_ST_CTRL_R = 0x00000007;
	    ++Count2;
		  GPIO_PORTF_DATA_R &= ~0x02;
		  GPIO_PORTF_DATA_R &= ~0x08;
		  GPIO_PORTF_DATA_R |= 0x04;
	 }
}

void Task3(void) 
{
	 Count3 = 0;
   for(;;){
	    ++Count3;
		  GPIO_PORTF_DATA_R &= ~0x02;
		  GPIO_PORTF_DATA_R &= ~0x04;
		  GPIO_PORTF_DATA_R |= 0x08;
	 }
}
int main(void)
{
   OS_Init();
	 SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; //activate port F
	 GPIO_PORTF_DIR_R |= 0x0E;
	 GPIO_PORTF_DEN_R |= 0x0E;
	 osKernelAddThreads(&Task1,&Task2, &Task3);
	 GPIO_PORTF_DATA_R |= 0x08;
	 osKernelLaunch(12500000);
	 return 0;
}