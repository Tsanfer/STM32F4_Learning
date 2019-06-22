#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_systick.h"
// bsp : board support package

int main(void)
{
	LED_GPIO_Config();
	EXTI_Key_Config();
	SysTick_Init();
	while(1)
	{
//		LED_RED;
//		Delay_ms(1000);
//		LED_GREEN
//		Delay_ms(1000);
//		LED_BLUE
//		Delay_ms(1000);
	}
}

// 课后作业

// 1- 让红灯以大概500ms的时间闪烁

// 2- 把绿灯跟蓝灯也点亮，实现一个流水灯
