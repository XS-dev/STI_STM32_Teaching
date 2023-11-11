/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/

#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "Com_Rule.h"

#include "led.h"	//����LED

/* ���Ӳ���״ָ̬ʾ */
//bit0�����ڷ������ݵ�USB��PC��
//bit1�����ڽ�������USB��PC������
uint8_t USB_COMPort_STA=0;

USART_TypeDef* USB_USART_n;	//�����л�


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
USART_InitTypeDef USART_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
uint8_t  USART_Rx_Buffer [USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;

uint8_t  USB_Tx_State = 0;
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);
/* Extern variables ----------------------------------------------------------*/

extern LINE_CODING linecoding;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**********************************************************
* �������� ---> USART2��ʼ��GPIO
* ��ڲ��� ---> none
* ������ֵ ---> none
* ����˵�� ---> ʹ�ò�ͬ�Ĵ�������������޸������ʼ����ͬ�Ĵ���
*               ����GPIO������ο���STM32���Ĳο��ֲ�_V10.pdf����110ҳ˵��
**********************************************************/
void USB_USARTn_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#if USB_USARTx==1	/* ����1 */

	USB_USART_n = USART1;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);	//������ʱ��
	
	//USART_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
	//USART_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�������������������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

#elif USB_USARTx==2	/* ����2 */

	USB_USART_n = USART2; 
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴���2ʱ��
	
	//USART_TX   PA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
	//USART_RX	  PA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�������������������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

#elif USB_USARTx==3	/* ����3 */

	USB_USART_n = USART3;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//�򿪴���3ʱ��
	
	//USART_TX   PB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
   
	//USART_RX	  PB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�������������������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

#elif USB_USARTx==4	/* ����4 */

	USB_USART_n = UART4;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴���4ʱ��
	
	//USART_TX   PC.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
   
	//USART_RX	  PC.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�������������������
	GPIO_Init(GPIOC, &GPIO_InitStructure);

#elif USB_USARTx==5	/* ����5 */

	USB_USART_n = UART5;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//�򿪴���5ʱ��
	
	//USART_TX   PC.12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
   
	//USART_RX	  PD.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�������������������
	GPIO_Init(GPIOD, &GPIO_InitStructure);

#endif
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);	//USB_CLK = PLLCLK / 1.5 = 72/1.5=48MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);	//����USBʱ��
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
  /*Enable SystemCoreClock*/
  SystemInit();
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
  
	/* 2 bit for pre-emption priority, 2 bits for subpriority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����жϷ���
	
	/* Configure the EXTI line 18 connected internally to the USB IP */
	EXTI_ClearITPendingBit(EXTI_Line18);
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//�����ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);  

	//USB�ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
	//USB�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&NVIC_InitStructure);

	//�����ж�����
#if USB_USARTx==1	/* ����1 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
#elif USB_USARTx==2	/* ����2 */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
#elif USB_USARTx==3	/* ����3 */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
#elif USB_USARTx==4	/* ����4 */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
#elif USB_USARTx==5	/* ����5 */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
#endif

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable
* Input          : None.
* Return         : Status
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
	if(NewState != DISABLE)	LED1 = 0;
	else	LED1 = 1;
}

/*******************************************************************************
* Function Name  :  USART_Config_Default.
* Description    :  configure the EVAL_COM1 with default values.
* Input          :  None.
* Return         :  None.
*******************************************************************************/
void USART_Config_Default(void)	//����ȱʡֵ
{
	USB_USARTn_GPIOInit();	//��ʼ��USART_IO��ģʽ

	USART_DeInit(USB_USART_n);  //��λ����

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USB_USART_n, &USART_InitStructure);	//��ʼ������

	USART_ITConfig(USB_USART_n, USART_IT_RXNE, ENABLE);	//�򿪷����жϱ�־
	USART_Cmd(USB_USART_n, ENABLE);	//ʹ�ܴ���
}

/*******************************************************************************
* Function Name  :  USART_Config.
* Description    :  Configure the EVAL_COM1 according to the line coding structure.
* Input          :  None.
* Return         :  Configuration status
                    TRUE : configuration done with success
                    FALSE : configuration aborted.
*******************************************************************************/
bool USART_Config(void)
{
  USART_DeInit(USB_USART_n);  //��λ����

  /* set the Stop bit*/
  switch (linecoding.format)
  {
    case 0:
      USART_InitStructure.USART_StopBits = USART_StopBits_1;
      break;
    case 1:
      USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
      break;
    case 2:
      USART_InitStructure.USART_StopBits = USART_StopBits_2;
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  /* set the parity bit*/
  switch (linecoding.paritytype)
  {
    case 0:
      USART_InitStructure.USART_Parity = USART_Parity_No;
      break;
    case 1:
      USART_InitStructure.USART_Parity = USART_Parity_Even;
      break;
    case 2:
      USART_InitStructure.USART_Parity = USART_Parity_Odd;
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  /*set the data type : only 8bits and 9bits is supported */
  switch (linecoding.datatype)
  {
    case 0x07:
      /* With this configuration a parity (Even or Odd) should be set */
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      break;
    case 0x08:
      if (USART_InitStructure.USART_Parity == USART_Parity_No)	//��У��λʱ����8λ���ݷ�ʽ���������9λ
      {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      }
      else 
      {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
      }
      
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  USART_InitStructure.USART_BaudRate = linecoding.bitrate;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
  /* Configure and enable the USART */
	USART_Init(USB_USART_n, &USART_InitStructure);	//��ʼ��USART
	USART_ITConfig(USB_USART_n, USART_IT_RXNE, ENABLE);	//�򿪽����жϱ�־
	USART_Cmd(USB_USART_n, ENABLE);	//ʹ�ܴ���

  return (TRUE);
}

/*******************************************************************************
* Function Name  : USB_To_USART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
* Return         : none.
*******************************************************************************/
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes)	//��USB���յ����� -> ����
{
  
  uint32_t i;

	USB_COMPort_STA |= 0x02;	//��������USB�����ݷ��͵�����
  
  for (i = 0; i < Nb_bytes; i++)
  {
//	while(USART_GetFlagStatus(USB_USART_n, USART_FLAG_TC) == RESET);	//�ȴ����ڷ����������
//	USART_SendData(USB_USART_n, *(data_buffer + i));	//�������ݵ�����
		Data_Deal(*(data_buffer + i));
  }
}

/*******************************************************************************
* Function Name  : Handle_USBAsynchXfer.
* Description    : send data to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void Handle_USBAsynchXfer (void)	//USB�������ݸ���λ��
{
  
  uint16_t USB_Tx_ptr;
  uint16_t USB_Tx_length;
  
  if(USB_Tx_State != 1)
  {
    if (USART_Rx_ptr_out == USART_RX_DATA_SIZE)
    {
      USART_Rx_ptr_out = 0;
    }
    
    if(USART_Rx_ptr_out == USART_Rx_ptr_in) 
    {
      USB_Tx_State = 0; 
      return;
    }
    
    if(USART_Rx_ptr_out > USART_Rx_ptr_in) /* rollback */
    { 
      USART_Rx_length = USART_RX_DATA_SIZE - USART_Rx_ptr_out;
    }
    else 
    {
      USART_Rx_length = USART_Rx_ptr_in - USART_Rx_ptr_out;
    }
    
    if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE)
    {
      USB_Tx_ptr = USART_Rx_ptr_out;
      USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
      
      USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;	
      USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;	
    }
    else
    {
      USB_Tx_ptr = USART_Rx_ptr_out;
      USB_Tx_length = USART_Rx_length;
      
      USART_Rx_ptr_out += USART_Rx_length;
      USART_Rx_length = 0;
    }
    USB_Tx_State = 1; 
    UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
    SetEPTxCount(ENDP1, USB_Tx_length);
    SetEPTxValid(ENDP1); 
  }  
  
}
/*******************************************************************************
* Function Name  : UART_To_USB_Send_Data.
* Description    : send the received data from UART 0 to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void USART_To_USB_Send_Data(void)	//�Ӵ��ڽ��յ����� -> USB
{
	USB_COMPort_STA |= 0x01;	//���ڷ������ݵ�USB

  
  if (linecoding.datatype == 7)	//7λ����ʱ
  {
	USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(USB_USART_n) & 0x7f;	//7λ���� 
  }
  else if (linecoding.datatype == 8)	//8λ����ʱ
  {
	USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(USB_USART_n);	//8λ����
  }
  
  USART_Rx_ptr_in++;
  
  /* To avoid buffer overflow */
  if(USART_Rx_ptr_in == USART_RX_DATA_SIZE)
  {
    USART_Rx_ptr_in = 0;
  }
}

void USB_Send_Data(u8 dat)	//�Ӵ��ڽ��յ����� -> USB
{
	USB_COMPort_STA |= 0x01;	//���ڷ������ݵ�USB
	USART_Rx_Buffer[USART_Rx_ptr_in] = dat;	//8λ����
  USART_Rx_ptr_in++;
  
  /* To avoid buffer overflow */
  if(USART_Rx_ptr_in == USART_RX_DATA_SIZE)
  {
    USART_Rx_ptr_in = 0;
  }
}
void USB_Send_String(u8 *dat,u8 leng)
{
	u8 i;
	
	for(i=0;i<leng;i++)
	{
			USB_Send_Data(dat[i]);
	}
}
/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(uint32_t*)ID1;
  Device_Serial1 = *(uint32_t*)ID2;
  Device_Serial2 = *(uint32_t*)ID3;  

  Device_Serial0 += Device_Serial2;

  if (Device_Serial0 != 0)
  {
    IntToUnicode (Device_Serial0, &Virtual_Com_Port_StringSerial[2] , 8);
    IntToUnicode (Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
  }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;
  
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    }
    
    value = value << 4;
    
    pbuf[ 2* idx + 1] = 0;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
