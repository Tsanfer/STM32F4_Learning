#include "stm32f4xx.h"
#include "./led/bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_exti.h"
#include "bsp_usart_dma.h"

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	LED_GPIO_Config();
	EXTI_Key_Config();
	Debug_USART_Config();
	MtoM_DMA_Config();
	MtoP_DMA_Config();
	Usart_SendByte( DEBUG_USART, 'A');
	Usart_SendHalfWord( DEBUG_USART, 65535);
	Usart_SendString( DEBUG_USART, "Ұ��STM32F429����ͨ������\n");
	printf("����ͨ��printf��������\n");
	printf("\n");
	Show_Message();
	while(1)
	{	
		;
	}
}
