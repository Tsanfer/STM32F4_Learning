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
#include "bsp_exti.h"
#include "bsp_usart_dma.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	uint8_t TransferStatus;
	LED_GPIO_Config();
	EXTI_Key_Config();
	Debug_USART_Config();
	MtoM_DMA_Config();
	/* 等待DMA传输完成 */
  while(DMA_GetFlagStatus(DMA_STREAM,DMA_FLAG_TCIF)==DISABLE)
  {
  }
	/* 比较源数据与传输后数据 */
  TransferStatus=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	/* 判断源数据与传输后数据比较结果*/
  if(TransferStatus==0)  
  {
		/* 源数据与传输后数据不相等时RGB彩色灯显示红色 */
    LED_RED;
  }
  else
  { 
    /* 源数据与传输后数据相等时RGB彩色灯显示蓝色 */
    LED_BLUE;
  }
	Usart_SendByte( DEBUG_USART, 'A');
	Usart_SendHalfWord( DEBUG_USART, 65535);
	Usart_SendString( DEBUG_USART, "野火STM32F429串口通信例程\n");
	printf("串口通信printf函数测试\n");
	printf("\n");
	Show_Message();
	while(1)
	{	
		;
	}
}

// 作业

// 用串口2实现这两个例程


/*********************************************END OF FILE**********************/

