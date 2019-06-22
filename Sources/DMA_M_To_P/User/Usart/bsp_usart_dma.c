#include "bsp_usart_dma.h"
#include "bsp_debug_usart.h"

/* ����aSRC_Const_Buffer������ΪDMA��������Դ
  const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ�������� */
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};

/* ����DMA����Ŀ��洢�� */
uint32_t aDST_Buffer[BUFFER_SIZE];
																		
uint8_t SendBuff[SENDBUFF_SIZE];
																		
void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

static void MtoM_DMA_Config_Init(void);
static void MtoP_DMA_Config_Init(void);

/**
  * �ж�ָ�����ȵ���������Դ�Ƿ���ȫ��ȣ�
  * �����ȫ��ȷ���1��ֻҪ����һ�����ݲ���ȷ���0
  */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--)
  {
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer != *pBuffer1)
    {
      /* ��Ӧ����Դ����������˳�������������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer++;
    pBuffer1++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;  
}

void MtoM_DMA_Config(void)
{
	uint16_t Timeout;
	DMA_InitTypeDef  DMA_InitStructure;
	/* ʹ��DMAʱ�� */
	RCC_AHB1PeriphClockCmd(DMA_STREAM_CLOCK, ENABLE);
	
	/* ��λ��ʼ��DMA������ */
  DMA_DeInit(DMA_STREAM);
	
	/* ȷ��DMA��������λ��� */
  while (DMA_GetCmdStatus(DMA_STREAM) == ENABLE)
  {
  }
	
	/* DMA������ͨ��ѡ�� */
  DMA_InitStructure.DMA_Channel = DMA_CHANNEL;  
  /* Դ���ݵ�ַ */
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
  /* Ŀ���ַ */
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aDST_Buffer;
  /* �洢�����洢��ģʽ */
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
  /* ������Ŀ */
  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
  /* ʹ���Զ��������� */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  /* ʹ���Զ��������� */
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  /* Դ�������ִ�С(32λ) */
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  /* Ŀ������Ҳ���ִ�С(32λ) */
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  /* һ�δ���ģʽ���洢�����洢��ģʽ����ʹ��ѭ������ */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  /* DMA���������ȼ�Ϊ�ܸ�*/
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	
  /* ����FIFOģʽ */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;     
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  /* ����ģʽ */
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  /* ����ģʽ */
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
  /* ���DMA�������������� */
  DMA_Init(DMA_STREAM, &DMA_InitStructure);
	
	/* ʹ��DMA����������ʼDMA���ݴ��� */
  DMA_Cmd(DMA_STREAM, ENABLE);
  /* ���DMA�������Ƿ���Ч�����г�ʱ��⹦�� */
  Timeout = TIMEOUT_MAX;
  while ((DMA_GetCmdStatus(DMA_STREAM) ==DISABLE) && (Timeout-- > 0))
  {
  }
	 /* �ж��Ƿ�ʱ */
  if (Timeout == 0)
  {
    /* ��ʱ���ó�����������ѭ����RGB��ɫ����˸ */
    while (1)
    {      
      LED_RED;
      Delay(0xFFFFFF);
      LED_RGBOFF;
      Delay(0xFFFFFF);
    }
  }
	MtoM_DMA_Config_Init();
}

void MtoP_DMA_Config(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
	/* ʹ��DMAʱ�� */
	RCC_AHB1PeriphClockCmd(DEBUG_USART_DMA_CLK, ENABLE);
	
	/* ��λ��ʼ��DMA������ */
  DMA_DeInit(DEBUG_USART_DMA_STREAM);
	
	/* ȷ��DMA��������λ��� */
  while (DMA_GetCmdStatus(DEBUG_USART_DMA_STREAM) == ENABLE)
  {
  }
	
	/*USART1 TX��ӦDMA2��ͨ��4��������7*/
  DMA_InitStructure.DMA_Channel = DEBUG_USART_DMA_CHANNEL;  
  /*����DMAԴ���������ݼĴ�����ַ*/
  DMA_InitStructure.DMA_PeripheralBaseAddr = DEBUG_USART_DR_BASE;
  /*�ڴ��ַ(Ҫ����ı�����ָ��)*/
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)SendBuff;
  /*���򣺴��ڴ浽����*/
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  /*�����СDMA_BufferSize=SENDBUFF_SIZE*/
  DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
  /*�����ַ����*/
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  /*�ڴ��ַ����*/
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  /*�������ݵ�λ*/
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  /*�ڴ����ݵ�λ 8bit*/
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  /* һ�δ���ģʽ���洢�����洢��ģʽ����ʹ��ѭ������ */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  /* DMA���������ȼ�Ϊ�� */
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
  /* ����FIFOģʽ */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;     
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  /*�洢��ͻ������ ���δ���*/
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  /*����ͻ������ ���δ���*/
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
  /*����DMA2��������7*/
  DMA_Init(DEBUG_USART_DMA_STREAM, &DMA_InitStructure);
	
	/*ʹ��DMA*/
  DMA_Cmd(DEBUG_USART_DMA_STREAM, ENABLE);
  /* ���DMA�������Ƿ���Ч�����г�ʱ��⹦�� */
  /* �ȴ�DMA��������Ч*/
  while(DMA_GetCmdStatus(DEBUG_USART_DMA_STREAM) != ENABLE)
  {
  }
	MtoP_DMA_Config_Init();
}

static void MtoM_DMA_Config_Init(void)
{
	uint8_t TransferStatus;
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
}

static void MtoP_DMA_Config_Init(void)
{
	uint16_t i;
	for(i=0;i<SENDBUFF_SIZE;i++)
  {
		if(i>(SENDBUFF_SIZE-3))
		{
			SendBuff[i]	 = '\n';
			continue;
		}
    SendBuff[i]	 = 'A';
  }
	USART_DMACmd(DEBUG_USART, USART_DMAReq_Tx, ENABLE);
}