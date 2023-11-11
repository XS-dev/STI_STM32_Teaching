#include "ADF4351.h"

void ADF_Output_GPIOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADF4351_CE_GPIO_Port, ADF4351_CE_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, ADF4351_LE_Pin|ADF4351_DAT_Pin|ADF4351_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADF4351_CE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADF4351_CE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = ADF4351_LE_Pin|ADF4351_DAT_Pin|ADF4351_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

void delay (int length)
{
	while (length >0)
    	length--;
}

void WriteToADF4351(uint8_t count, uint8_t *buf)
{
	uint8_t ValueToWrite = 0;
	uint8_t i = 0;
	uint8_t j = 0;
	
//	ADF_Output_GPIOInit();
	HAL_GPIO_WritePin(ADF4351_CE_GPIO_Port, ADF4351_CE_Pin	, GPIO_PIN_SET);	
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port, ADF4351_CLK_Pin	, GPIO_PIN_RESET);	
	Delay_Us(1);
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_RESET);	
	Delay_Us(1);
	
	for(i = count; i>0; i--)
	{
		ValueToWrite = *(buf+i-1);
		for(j=0; j<8; j++)
		{
			if(0x80 == (ValueToWrite & 0x80))
			{
				HAL_GPIO_WritePin(ADF4351_DAT_GPIO_Port, ADF4351_DAT_Pin	, GPIO_PIN_SET);	
			}
			else
			{
				HAL_GPIO_WritePin(ADF4351_DAT_GPIO_Port, ADF4351_DAT_Pin	, GPIO_PIN_RESET);	
			}
			Delay_Us(1);
			HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port, ADF4351_CLK_Pin	, GPIO_PIN_SET);	
			Delay_Us(1);
			ValueToWrite <<= 1;
			HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port, ADF4351_CLK_Pin	, GPIO_PIN_RESET);	
						
		}
	}
	HAL_GPIO_WritePin(ADF4351_DAT_GPIO_Port, ADF4351_DAT_Pin	, GPIO_PIN_RESET);
	Delay_Us(1);
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_SET);
	Delay_Us(1);
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_RESET);
}


void ReadToADF4351(uint8_t count, uint8_t *buf)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t iTemp = 0;
	uint8_t RotateData = 0;
	
//	ADF_Input_GPIOInit();
	HAL_GPIO_WritePin(ADF4351_CE_GPIO_Port, ADF4351_CE_Pin	, GPIO_PIN_SET);	
	Delay_Us(1);
	HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port, ADF4351_CLK_Pin	, GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_RESET);
	Delay_Us(1);
	
	for(i = count; i>0; i--)
	{
		for(j = 0; j<8; j++)
		{
			RotateData <<=1;
			Delay_Us(1);
//			iTemp = ADF4351_INPUT_DATA;
			HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port, ADF4351_CLK_Pin	, GPIO_PIN_SET);	
			if(0x01 == (iTemp&0x01))
			{
				RotateData |= 1;
			}
			Delay_Us(1);
			HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port, ADF4351_CLK_Pin	, GPIO_PIN_RESET);	
			
		}
		*(buf+i-1) = RotateData;
	}
	Delay_Us(1);
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_SET);
	Delay_Us(1);
	HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port, ADF4351_LE_Pin	, GPIO_PIN_RESET);
}


void ADF4351Init(void)
{
	uint8_t buf[4] = {0,0,0,0};
	
	ADF_Output_GPIOInit();
	
	buf[3] = 0x00;
	buf[2] = 0x58;
	buf[1] = 0x00;				//write communication register 0x00580005 to control the progress 
 	buf[0] = 0x05;				//to write Register 5 to set digital lock detector
//	while(1)
//	{
//		WriteToADF4351(4,buf);
//		Delay_Us(10);	
//	}
	WriteToADF4351(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0xec;				//(DB23=1)The signal is taken from the VCO directly;(DB22-20:4H)the RF divider is 16;(DB19-12:50H)R is 80
	buf[1] = 0x80;				//(DB11=0)VCO powerd up;
 	buf[0] = 0x3C;				//(DB5=1)RF output is enabled;(DB4-3=3H)Output power level is 5
	WriteToADF4351(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x04;				//(DB14-3:96H)clock divider value is 150.
 	buf[0] = 0xB3;
	WriteToADF4351(4,buf);	

	buf[3] = 0x00;
	buf[2] = 0x01;				//(DB6=1)set PD polarity is positive;(DB7=1)LDP is 6nS;
	buf[1] = 0x0E;				//(DB8=0)enable fractional-N digital lock detect;
 	buf[0] = 0x42;				//(DB12-9:7H)set Icp 2.50 mA;
	WriteToADF4351(4,buf);		//(DB23-14:1H)R counter is 1

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x80;			   //(DB14-3:6H)MOD counter is 6;
 	buf[0] = 0x29;			   //(DB26-15:6H)PHASE word is 1,neither the phase resync 
	WriteToADF4351(4,buf);	   //nor the spurious optimization functions are being used
							   //(DB27=1)prescaler value is 8/9

	buf[3] = 0x00;
	buf[2] = 0x2c;
	buf[1] = 0x80;
 	buf[0] = 0x18;					//(DB14-3:0H)FRAC value is 0;
	WriteToADF4351(4,buf);	//(DB30-15:140H)INT value is 320;
}
void WriteOneRegToADF4351(uint32_t Regster)
{
	uint8_t buf[4] = {0,0,0,0};
	buf[3] = (uint8_t)((Regster>>24)&(0X000000FF));
	buf[2] = (uint8_t)((Regster>>16)&(0X000000FF));
	buf[1] = (uint8_t)((Regster>>8) &(0X000000FF));
	buf[0] = (uint8_t)((Regster)&(0X000000FF));
	WriteToADF4351(4,buf);	
}
void ADF4351_Init_some(void)
{
	WriteOneRegToADF4351(ADF4351_R2);
	WriteOneRegToADF4351(ADF4351_R3);
	WriteOneRegToADF4351(ADF4351_R5);
}

void ADF4351WriteFreq(float Fre)		//	fre单位MHz -> (xx.x) M Hz
{
	uint16_t Fre_temp, N_Mul = 1, Mul_Core = 0;
	uint16_t INT_Fre, Frac_temp, Mod_temp, i;
	uint32_t W_ADF4351_R0 = 0, W_ADF4351_R1 = 0, W_ADF4351_R4 = 0;
	float multiple;
	
	if(Fre < 35.0)
		Fre = 35.0;
	if(Fre > 4400.0)
		Fre = 4400.0;
	Mod_temp = 1000;
	Fre = ((float)((uint32_t)(Fre*10)))/10;
	
	Fre_temp = Fre;
	for(i = 0; i < 10; i++)
	{
		if(((Fre_temp*N_Mul) >= 2199.9) && ((Fre_temp*N_Mul) <= 4400.1))
			break;
		Mul_Core++;
		N_Mul = N_Mul*2;
	}
	
	multiple = (Fre*N_Mul)/25;		//25：鉴相频率，板载100M参考，经寄存器4分频得25M鉴相。若用户更改为80M参考输入，需将25改为20；10M参考输入，需将25改为2.5，以此类推。。。
	INT_Fre = (uint16_t)multiple;
	Frac_temp = ((uint32_t)(multiple*1000))%1000;
	while(((Frac_temp%5) == 0) && ((Mod_temp%5) == 0))
	{
		Frac_temp = Frac_temp/5;
		Mod_temp = Mod_temp/5;
	}
	while(((Frac_temp%2) == 0)&&((Mod_temp%2) == 0))
	{
		Frac_temp = Frac_temp/2;
		Mod_temp = Mod_temp/2;
	}
	
	Mul_Core %= 7;
	W_ADF4351_R0 = (INT_Fre<<15)+(Frac_temp<<3);
	W_ADF4351_R1 = ADF4351_R1_Base + (Mod_temp<<3);
	W_ADF4351_R4 = ADF4351_R4_ON + (Mul_Core<<20);
	
	WriteOneRegToADF4351(ADF4351_RF_OFF);
	WriteOneRegToADF4351(W_ADF4351_R0);
	WriteOneRegToADF4351(W_ADF4351_R1);
	WriteOneRegToADF4351(W_ADF4351_R4);
}

