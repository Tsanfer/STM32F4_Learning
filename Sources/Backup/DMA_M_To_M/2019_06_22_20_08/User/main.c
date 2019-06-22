/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ƶ����ˮ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
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
	uint8_t TransferStatus;
	LED_GPIO_Config();
	EXTI_Key_Config();
	Debug_USART_Config();
	MtoM_DMA_Config();
	/* �ȴ�DMA������� */
  while(DMA_GetFlagStatus(DMA_STREAM,DMA_FLAG_TCIF)==DISABLE)
  {
  }
	/* �Ƚ�Դ�����봫������� */
  TransferStatus=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	/* �ж�Դ�����봫������ݱȽϽ��*/
  if(TransferStatus==0)  
  {
		/* Դ�����봫������ݲ����ʱRGB��ɫ����ʾ��ɫ */
    LED_RED;
  }
  else
  { 
    /* Դ�����봫����������ʱRGB��ɫ����ʾ��ɫ */
    LED_BLUE;
  }
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

// ��ҵ

// �ô���2ʵ������������


/*********************************************END OF FILE**********************/

