#include "AD9834.h"
void AD9834_Init(void)
{
	AD9834_Gpio_Init();
  AD9834_Write_16Bits(0x2100);
  AD9834_Write_16Bits(0x2038);
  AD9834_Write_16Bits(0XC000);
  AD9834_Write_16Bits(0x2100);
  AD9834_Select_Wave(0x2028);
  AD9834_Set_Freq(0,12000); //Set the output frequency of 15MHz
}

void AD9834_Gpio_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SDATA_GPIO_Port, SDATA_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FSYNC_GPIO_Port, FSYNC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PDPin PDPin */
  GPIO_InitStruct.Pin = SCLK_Pin|RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SCLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = SDATA_Pin|FSYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SDATA_GPIO_Port, &GPIO_InitStruct);

}

void AD9834_Write_16Bits(uint16_t data) 
{ 
  uint8_t i = 0 ; 
  AD9834_SCLK_H; 
  AD9834_FSYNC_L; 
  for(i=0 ;i<16 ;i++)      
  { 
    if(data & 0x8000) 
    AD9834_SDATA_H; 
    else 
    AD9834_SDATA_L; 
    AD9834_SCLK_L; 
		Delay_Ms(1);
    data <<= 1 ; 
    AD9834_SCLK_H; 
		Delay_Ms(1);

  } 
  AD9834_SDATA_H; 
  AD9834_FSYNC_H; 
} 

void AD9834_Select_Wave(uint16_t initdata) 
{ 
  AD9834_FSYNC_H; 
  AD9834_SCLK_H; 
  AD9834_RESET_H; 
  AD9834_RESET_L;
  AD9834_Write_16Bits(initdata); 
} 


void AD9834_Set_Freq(uint8_t freq_number, uint32_t freq) 
{
    uint32_t FREQREG = (uint32_t)(268435456.0/75000000*freq); 
    uint16_t FREQREG_LSB_14BIT = (uint16_t)FREQREG; 
    uint16_t FREQREG_MSB_14BIT = (uint16_t)(FREQREG>>14); 
    if(freq_number == 0) 
    { 
        FREQREG_LSB_14BIT &= ~(1U<<15); 
        FREQREG_LSB_14BIT |= 1<<14; 
        FREQREG_MSB_14BIT &= ~(1U<<15); 
        FREQREG_MSB_14BIT |= 1<<14; 
    }
    else
    {
        FREQREG_LSB_14BIT &= ~(1<<14); 
        FREQREG_LSB_14BIT |= 1U<<15; 
        FREQREG_MSB_14BIT &= ~(1<<14); 
        FREQREG_MSB_14BIT |= 1U<<15; 
    } 
    AD9834_Write_16Bits(FREQREG_LSB_14BIT); 
    AD9834_Write_16Bits(FREQREG_MSB_14BIT);      
} 
