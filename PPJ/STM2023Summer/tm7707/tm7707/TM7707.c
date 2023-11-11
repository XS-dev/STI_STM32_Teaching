#include "TM7707.h"

//Simple delay function
void TM7707_Delay(void)
{
	Delay_Us(100);
}

void TM7707_Write_8Bits(uint8_t Data)
{
	
	TM7707_Delay();	
	for(int i = 0; i < 8; i++)
	{
		if (Data & 0x80)
		{
			AD7_DIN_H ;
		}
		else
		{
			AD7_DIN_L ;
		}
		AD7_SCK_H;	
		TM7707_Delay();
		Data <<= 1;
		AD7_SCK_L;    /* <----  ADS1256 是在SCK下降沿采样DIN数据,*/
		TM7707_Delay();				 
	}
} 
uint8_t TM7707_Read_8Bits(void)
{
	uint8_t read = 0;
	TM7707_Delay();
	for (int i = 0; i < 8; i++)
	{	
		AD7_SCK_H ;    /* <----  ADS1256 是在SCK上升沿输出数据,*/
		TM7707_Delay();
		read = read<<1;
		AD7_SCK_L ;		
		if (AD7_DOUT)
		{
			read++;
		}
		TM7707_Delay();
	}
	return read;//返回读到的数据
}



/************************************************************************/
/* Function Name:	TM7707_InitializeGPIO.								*/
/* Purpose:			Initializes all GPIOs used by the device.			*/
/* Resources:		GPIO control and GPIO device RCC.					*/
/* Params:			None.												*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_InitializeGPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, AD7_CS_Pin|AD7_DIN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AD7_RST_GPIO_Port, AD7_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AD7_SCLK_GPIO_Port, AD7_SCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = AD7_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(AD7_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = AD7_DIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(AD7_DIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = AD7_DRTY_Pin|AD7_DOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = AD7_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(AD7_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = AD7_SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(AD7_SCLK_GPIO_Port, &GPIO_InitStruct);

  // Default disables the device.
  AD7_CS_H;
}

uint32_t TM7707_ReadADCValue(uint8_t uiChannelIndex)
{
	uint32_t rtnADValue = 0;
	// Write channel index.
	TM7707_TransferByte(REG_DATA | READ | uiChannelIndex);
	// Wait for the conversion to complete
	TM7707_WaitForDRDY();
	// Read ADC value.
	rtnADValue |= TM7707_TransferByte(0xFF);
	rtnADValue <<= 8;
	rtnADValue |= TM7707_TransferByte(0xFF);
	rtnADValue <<= 8;
	rtnADValue |= TM7707_TransferByte(0xFF);
	
	return rtnADValue;
}

/************************************************************************/
/* Function Name:	TM7707_TransferByte.								*/
/* Purpose:			Send of recive a byte.								*/
/* Resources:		SPI controler.										*/
/* Params:																*/
/*	@uiTxData:			The byte data will be sent.						*/
/* Return:			The byte data recived.								*/
/* Limitation:		None.												*/
/************************************************************************/
uint8_t TM7707_TransferByte(uint8_t uiTxData)
{
	uint8_t uiRxData;
	AD7_CS_L;		// CS = 0;
	TM7707_Write_8Bits(uiTxData);
	AD7_CS_H;	// CS = 0;
	TM7707_Delay();	
	AD7_CS_L;
	uiRxData = TM7707_Read_8Bits();
	AD7_CS_H;
	return uiRxData;
}

/************************************************************************/
/* Function Name:	TM7707_SynchronizeDeviceClock.						*/
/* Purpose:			Synchronize TM7707 device clock, keep SCLK pin high	*/
/*					at least 32 cycles.									*/
/* Resources:		SPI controler and GPIOs.							*/
/* Params:			None.												*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_SynchronizeDeviceClock(void)
{
	uint8_t i;
	// Keep SCLK pin high at 40 cycles.
	for(i=0; i<5; i++)
	{
		TM7707_TransferByte(0xFF);
	}
}

/************************************************************************/
/* Function Name:	TM7707_WaitForDRDY.									*/
/* Purpose:			Wait for device DRDY signal.						*/
/* Resources:		DRDY GPIO pin.										*/
/* Params:			None.												*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_WaitForDRDY(void)
{
	while((AD7_DRDY) != 0);
}

/************************************************************************/
/* Function Name:	TM7707_SelfCalibration.								*/
/* Purpose:			Internal channel self-calibration.					*/
/* Resources:		SPI controler and GPIOs.							*/
/* Params:																*/
/*	@uiChannelIndex:	Channel index.									*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_SelfCalibration(uint8_t	uiChannelIndex, uint8_t uiGain)
{
	uiChannelIndex = uiChannelIndex % CH_MAX;
	//Write communication register to set setup register.
	TM7707_TransferByte(REG_SETUP | WRITE | uiChannelIndex);
	//Write configuration register, start self-calibration.
	TM7707_TransferByte(MD_CAL_SELF | uiGain | UNIPOLAR | BUF_EN | FSYNC_0);
	// Wait for operation to complete(ablut 180ms).
	TM7707_WaitForDRDY();
}

/************************************************************************/
/* Function Name:	TM7707_Initialize.									*/
/* Purpose:			Initialize TM7707 device.							*/
/* Resources:		SPI controler and GPIO pins.						*/
/* Params:			None.												*/
/* Return:			None.												*/
/* Limitation:		None.												*/
/************************************************************************/
void TM7707_Initialize(void)
{
	// Initialize GPIO for TM7707 device.
	TM7707_InitializeGPIO();
	// Synchronize device clock.
	TM7707_SynchronizeDeviceClock();
	// Configure the clock registers
	TM7707_TransferByte(REG_CLOCK | WRITE | CH_1); // Write communication register to set clook register.
	TM7707_TransferByte(CLKDIS_0 | CLK_4_9152M | FS_500HZ); // External clock, frequency is 4.9152 MHz and the sampling frequency is 500Hz.
	TM7707_TransferByte(REG_CLOCK | WRITE | CH_2); // Write communication register to set clook register.
	TM7707_TransferByte(CLKDIS_0 | CLK_4_9152M | FS_500HZ); // External clock, frequency is 4.9152 MHz and the sampling frequency is 500Hz.
}

