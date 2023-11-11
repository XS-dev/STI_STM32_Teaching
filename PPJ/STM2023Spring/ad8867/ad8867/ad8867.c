#include "ad8867.h"

void AD_Delay(void)
{
	Delay_Us(10);
}
void AD_GPIO_INIT(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADSTART_GPIO_Port, ADSTART_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADSCLK_GPIO_Port, ADSCLK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADCS_GPIO_Port, ADCS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADSTART_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADSTART_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ADOUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADSCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADSCLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADCS_GPIO_Port, &GPIO_InitStruct);
	
}

void AD_Init(void)
{
	AD_GPIO_INIT();
}


void AD_START(void)
{
	DIN_H;
	AD_Delay();
	CONVST_H;
	SCLK_H;
	AD_Delay();
	SCLK_L;
	AD_Delay();
	DIN_L;
}



void AD_STOP(void)
{
	DIN_H;
	AD_Delay();
	CONVST_L;
	AD_Delay();
	CONVST_H;
	AD_Delay();
	CONVST_L;
	DIN_L;
}



uint16_t AD_Read(void)
{
	unsigned char i,receive=0;
	for(i=0;i<16;i++ )
	{
		SCLK_H; 
		if(READ_DOUT)receive++;   
		AD_Delay();
		SCLK_L;
		receive<<=1;
		AD_Delay();		
  }					 
	return receive;
}

uint16_t AD_RESULT(void)
{
	uint16_t receive=0;
	AD_START();
	receive = AD_Read();
	AD_STOP();
	return receive;

}








