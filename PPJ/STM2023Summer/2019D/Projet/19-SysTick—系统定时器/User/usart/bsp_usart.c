#include "bsp_usart.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure1;
//	NVIC_InitTypeDef NVIC_InitStructure2;
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
	
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	

//  
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure1.NVIC_IRQChannel = UART4_IRQn;
//	
//  /* �������ȼ�*/
//  NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ� */
//  NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure1);
//	

//  
//  /* ����USARTΪ�ж�Դ */
//  NVIC_InitStructure2.NVIC_IRQChannel = USART3_IRQn;
//	
//  /* �������ȼ�*/
//  NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ� */
//  NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
//  /* ��ʼ������NVIC */
//  NVIC_Init(&NVIC_InitStructure2);
	
	
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure0;
	USART_InitTypeDef USART_InitStructure0;
	

//GPIO_InitTypeDef GPIO_InitStructure1;
//USART_InitTypeDef USART_InitStructure1;
	
//	GPIO_InitTypeDef GPIO_InitStructure2;
	
	
	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD), ENABLE);

	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure0.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure0.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure0.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure0);

//	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_10;
//	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure1);
	
//	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_12;
//	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure2);
	
  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure0.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure0.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure0);
	
//	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_11;
//	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOC, &GPIO_InitStructure1);
	
//	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOD, &GPIO_InitStructure2);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure0.USART_BaudRate = DEBUG_USART_BAUDRATE;
//	USART_InitStructure1.USART_BaudRate = DEBUG_USART_BAUDRATE;

	// ���� �������ֳ�
	USART_InitStructure0.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure1.USART_WordLength = USART_WordLength_8b;

	// ����ֹͣλ
	USART_InitStructure0.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure1.USART_StopBits = USART_StopBits_1;

	// ����У��λ
	USART_InitStructure0.USART_Parity = USART_Parity_No ;
//	USART_InitStructure1.USART_Parity = USART_Parity_No ;

	// ����Ӳ��������
	USART_InitStructure0.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	
//	USART_InitStructure1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure0.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_InitStructure1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure0);
//	USART_Init(UART4, &USART_InitStructure1);
//	USART_Init(UART5, &USART_InitStructure1);
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
//	USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);
//	USART_Cmd(UART4, ENABLE);
//	USART_Cmd(UART5, ENABLE);


}

/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

void USART1PutString(char str[])
{ 
//	Usart_SendString(UART4,str);
}
void USART0PutString(char str[])
{ 
//	Usart_SendString(UART5,str);
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
	
//		USART_SendData(UART4, (uint8_t) ch);
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
		//while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);		

		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}



