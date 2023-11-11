#include "HC595.h"
/*
 *PB4...........DIO
 *PB5...........RCLK
 *PB6...........SCLK

 */

uint16_t LED_table[18]={
//01234567
0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
//89ABCDEF
0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,
//Ϩ��-
0xFF,0xBF};
//��������ܶ��롰0123456789AbCdEFϨ��-��

uint16_t wei_table[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//��һλ���ڰ�λλ��




void HC595_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, HC595_SCLK_Pin|HC595_RCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HC595_DIO_GPIO_Port, HC595_DIO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = HC595_SCLK_Pin|HC595_RCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = HC595_DIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HC595_DIO_GPIO_Port, &GPIO_InitStruct);
}


/****************************************************************/
//���붯̬��ʾ����LED8_Display()�����β�x��y���޷���ֵ
//x��ʾλѡ��y��ʾ����ʾ������
/****************************************************************/
void LED8_Display(uint16_t x,uint16_t y)
{
  LED_OUT(LED_table[y]);//�ͳ�����
  LED_OUT(wei_table[x]);//�ͳ�λ��		
  RCLK_L;
  RCLK_H;//RCLK����������
  Delay_Ms(1);
}
/****************************************************************/
//���ֽ����ݴ�����λ����LED_OUT()�����β�outdata���ڴ���ʵ������
//�޷���ֵ
/****************************************************************/
void LED_OUT(uint16_t outdata)
{
  uint16_t i;
  for(i=0;i<8;i++)//ѭ��8��
  {
    if (outdata & 0x80)//��һȡ�����λ 1000 0000 b 
		{
			DIO_H;//�ͳ���1��
		}
    else {
      DIO_L;//�ͳ���0��
		}
    outdata<<=1;//ִ������һλ����
    SCLK_L;
    SCLK_H;//SCLK����������
  }
}
