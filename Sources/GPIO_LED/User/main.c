#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_key.h"

int main(void)
{
	LED_GPIO_Config();
	key_GPIO_Config();
	while(1)
	{
		if ( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON )
		{
			LED_R_TOGGLE;
		}
		if ( Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON )
		{
			LED_G_TOGGLE;
		}
	}
}
