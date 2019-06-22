#include "bsp_key.h"

void key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//打开GPIO时钟
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
	//选择GPIO_PIN
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	//选择模式为输入模式
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	//输出没有推挽和开漏模式
	//GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	//选择电阻下拉
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	//输出没有速度
	//GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
	
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStruct);
}

uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if ( GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )
	{
		while( GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON );
		//做相应动作
		return KEY_ON;
	}
	else
		return KEY_OFF;
}
