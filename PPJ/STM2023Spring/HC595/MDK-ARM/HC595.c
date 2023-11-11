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
//熄灭-
0xFF,0xBF};
//共阳数码管段码“0123456789AbCdEF熄灭-”

uint16_t wei_table[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//第一位至第八位位码




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
//数码动态显示函数LED8_Display()，有形参x和y，无返回值
//x表示位选择，y表示欲显示的数码
/****************************************************************/
void LED8_Display(uint16_t x,uint16_t y)
{
  LED_OUT(LED_table[y]);//送出段码
  LED_OUT(wei_table[x]);//送出位码		
  RCLK_L;
  RCLK_H;//RCLK产生上升沿
  Delay_Ms(1);
}
/****************************************************************/
//单字节数据串行移位函数LED_OUT()，有形参outdata用于传入实际数据
//无返回值
/****************************************************************/
void LED_OUT(uint16_t outdata)
{
  uint16_t i;
  for(i=0;i<8;i++)//循环8次
  {
    if (outdata & 0x80)//逐一取出最高位 1000 0000 b 
		{
			DIO_H;//送出“1”
		}
    else {
      DIO_L;//送出“0”
		}
    outdata<<=1;//执行左移一位操作
    SCLK_L;
    SCLK_H;//SCLK产生上升沿
  }
}
