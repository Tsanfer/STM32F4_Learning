#ifndef __BSP_USART_DMA_H
#define	__BSP_USART_DMA_H

#include "stm32f4xx.h"
#include "bsp_led.h"

/* 相关宏定义，使用存储器到存储器传输必须使用DMA2 */
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2 
#define DMA_FLAG_TCIF            DMA_FLAG_TCIF0

#define BUFFER_SIZE	32
#define TIMEOUT_MAX              10000 /* Maximum timeout value */

extern uint32_t aDST_Buffer[BUFFER_SIZE];
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];

uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);
void MtoM_DMA_Config(void);
void Delay(__IO uint32_t nCount);

#endif  /* __BSP_USART_DMA_H */
