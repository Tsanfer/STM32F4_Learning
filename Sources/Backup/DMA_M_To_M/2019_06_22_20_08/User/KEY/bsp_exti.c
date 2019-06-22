#include "bsp_exti.h"

static void EXTI_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
/*--------------------KEY1--------------------------*/	
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
/*-----------------------KEY2--------------------------*/		
	/* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStruct;

	/*开启GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/*打开外部中断时钟(APB2外设，使能)*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	/*配置NVIC*/
	EXTI_NVIC_Config();

	
/*--------------KEY1----------------------*/	
	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin =  KEY1_GPIO_PIN;	
	/*设置引脚模式为输入模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	/*设置引脚为浮空模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	/*配置外部中断(KEY1口，KEY1管脚)*/
	SYSCFG_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE);
	
	/*选择中断EXTI的PIN = 键盘的PIN*/
	EXTI_InitStruct.EXTI_Line = KEY1_INT_EXTI_LINE; 
	/*选择外部中断模式 = 中断模式*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*选择中断触发模式 = 上升沿*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	/*选择是否使能 = 使能*/
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
/*--------------KEY2----------------------*/	
	/*选择要控制的GPIO引脚*/															   
	GPIO_InitStructure.GPIO_Pin =  KEY2_GPIO_PIN;	
	/*设置引脚模式为输入模式*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	/*设置引脚为浮空模式*/
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/*调用库函数，使用上面配置的GPIO_InitStructure初始化GPIO*/
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);
	
	/*配置外部中断(KEY1口，KEY1管脚)*/
	SYSCFG_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE);
	
	/*选择中断EXTI的PIN = 键盘的PIN*/
	EXTI_InitStruct.EXTI_Line = KEY2_INT_EXTI_LINE; 
	/*选择外部中断模式 = 中断模式*/
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/*选择中断触发模式 = 上升沿*/
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	/*选择是否使能 = 使能*/
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
}
