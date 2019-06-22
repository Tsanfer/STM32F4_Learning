#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f4xx.h"

extern void TimingDelay_Decrement(void);
extern void SysTick_Init(void);
extern void Delay_ms(__IO u32 nTime);

#endif /* ___BSP_SYSTICK_H */
