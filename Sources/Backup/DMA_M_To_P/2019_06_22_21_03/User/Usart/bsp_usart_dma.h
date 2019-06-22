#ifndef __BSP_USART_DMA_H
#define	__BSP_USART_DMA_H

#include "stm32f4xx.h"
#include "bsp_led.h"

/* 相关宏定义，使用存储器到存储器传输必须使用DMA2 */
/* M To M */
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2 
#define DMA_FLAG_TCIF            DMA_FLAG_TCIF0

#define BUFFER_SIZE	32
#define TIMEOUT_MAX              10000 /* Maximum timeout value */

/* 相关宏定义，使用存储器到存储器传输必须使用DMA2 */
/* M To P */
#define DEBUG_USART_DR_BASE               (USART1_BASE+0x04)		
#define SENDBUFF_SIZE                     5000				//发送的数据量

#define DEBUG_USART_DMA_CLK               RCC_AHB1Periph_DMA2	
#define DEBUG_USART_DMA_CHANNEL           DMA_Channel_4
#define DEBUG_USART_DMA_STREAM            DMA2_Stream7

extern uint32_t aDST_Buffer[BUFFER_SIZE];
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint8_t SendBuff[SENDBUFF_SIZE];

uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);
void MtoM_DMA_Config(void);
void Delay(__IO uint32_t nCount);

void MtoP_DMA_Config(void);

#endif  /* __BSP_USART_DMA_H */
