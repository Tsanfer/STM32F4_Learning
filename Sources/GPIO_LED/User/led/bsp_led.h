#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

extern void LED_GPIO_Config(void);

//R 红色灯
#define LED_R_PIN GPIO_Pin_10
#define LED_R_GPIO_PORT GPIOH
#define LED_R_GPIO_CLK RCC_AHB1Periph_GPIOH

#define LED_R_TOGGLE { LED_R_GPIO_PORT->ODR ^= LED_R_PIN; }

//G 绿色灯
#define LED_G_PIN GPIO_Pin_11
#define LED_G_GPIO_PORT GPIOH
#define LED_G_GPIO_CLK RCC_AHB1Periph_GPIOH

#define LED_G_TOGGLE { LED_G_GPIO_PORT->ODR ^= LED_G_PIN; }

#endif
