/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   控制多彩流水灯
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "bsp_debug_usart.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
//	char ch;
	LED_GPIO_Config();
	Debug_USART_Config();
	Usart_SendByte( DEBUG_USART, 'A');
	Usart_SendHalfWord( DEBUG_USART, 65535);
	Usart_SendString( DEBUG_USART, "野火STM32F429串口通信例程\n");
	printf("串口通信printf函数测试\n");
	printf("\n");
//	ch = getchar();
//	printf("\r\n %c \r\n",ch);
	Show_Message();
while(1)
	{	
		;
	}
}


// 作业

// 用串口2实现这两个例程


/*********************************************END OF FILE**********************/

