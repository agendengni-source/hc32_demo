#include "main.h"
void user_systickinit(void)
{
	SystemCoreClockUpdate();
	SysTick_Init(1000);
	
}
volatile uint32_t led_slowtime[2]={0,500};
void SysTick_Handler()
{
	
	SysTick_IncTick();
	led_slowtime[0]++;
}