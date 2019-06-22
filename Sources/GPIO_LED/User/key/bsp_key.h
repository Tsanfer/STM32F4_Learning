#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define KEY_ON 1
#define KEY_OFF 0

#define KEY1_PIN GPIO_Pin_0
#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_CLK RCC_AHB1Periph_GPIOA

#define KEY2_PIN GPIO_Pin_13
#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_CLK RCC_AHB1Periph_GPIOC

extern void key_GPIO_Config(void);
extern uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif
