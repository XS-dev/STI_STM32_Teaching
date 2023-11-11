#include "AD9959.h"



uint8_t CSR_DATA0[1] = {0x10};     // ? CH0
uint8_t CSR_DATA1[1] = {0x20};      // ? CH1
uint8_t CSR_DATA2[1] = {0x40};      // ? CH2
uint8_t CSR_DATA3[1] = {0x80};      // ? CH3		
																	
 
uint8_t FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
uint8_t CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302	   
																	
uint8_t CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360
																	


uint8_t LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
																	
uint8_t RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
																	
uint8_t FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

//AD9959???
void Init_AD9959(void)  
{ 
		uint8_t FR1_DATA[3] = {0xD0,0x00,0x00};//20?? Charge pump control = 75uA FR1<23> -- VCO gain control =0? system clock below 160 MHz;
			 GPIO_InitTypeDef GPIO_InitStruct = {0};

		/* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
														|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);

		/*Configure GPIO pins : PD0 PD1 PD2 PD3
														 PD4 PD5 PD6 PD7 */
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
														|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/*Configure GPIO pins : PB3 PB4 PB5 PB6
														 PB7 */
		GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
														|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		Intserve();  //IO????
		IntReset();  //AD9959??
//		while(1)
		WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//??????1
		WriteData_AD9959(FR2_ADD,2,FR2_DATA,1);
//  WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
//  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
//  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
//  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
//  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
//  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);

   //??????

	Write_frequence(0,50);
	Write_frequence(1,50);
	Write_frequence(2,50);
	Write_frequence(3,50);

	//??????
	Write_Phase(0, 0);
	Write_Phase(1, 0);
	Write_Phase(2, 0);
	Write_Phase(3, 0);

	//??????
	Write_Amplitude(0, 933);
	Write_Amplitude(1, 933);
	Write_Amplitude(2, 933);
	Write_Amplitude(3, 933);
} 
//??
void delay1 (uint32_t length)
{
	Delay_Us(2);
}
//IO????
void Intserve(void)		   
{   
		HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port, AD9959_PWR_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, 	AD9959_CS_Pin	, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_UP_GPIO_Port, 	AD9959_UP_Pin	, GPIO_PIN_RESET);
	
		HAL_GPIO_WritePin(AD9959_P0_GPIO_Port, AD9959_P0_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_P1_GPIO_Port, AD9959_P1_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_P2_GPIO_Port, AD9959_P2_Pin	, GPIO_PIN_RESET);	
		HAL_GPIO_WritePin(AD9959_P3_GPIO_Port, AD9959_P3_Pin	, GPIO_PIN_RESET);	

		HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_SD1_GPIO_Port, AD9959_SD1_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_SD2_GPIO_Port, AD9959_SD2_Pin	, GPIO_PIN_RESET);	
		HAL_GPIO_WritePin(AD9959_SD3_GPIO_Port, AD9959_SD3_Pin	, GPIO_PIN_RESET);	

}
//AD9959??
void IntReset(void)	  
{
	HAL_GPIO_WritePin(AD9959_RST_GPIO_Port, AD9959_RST_Pin	, GPIO_PIN_RESET);
	delay1(1);
	
	HAL_GPIO_WritePin(AD9959_RST_GPIO_Port, AD9959_RST_Pin	, GPIO_PIN_SET);

	delay1(30);
	HAL_GPIO_WritePin(AD9959_RST_GPIO_Port, AD9959_RST_Pin	, GPIO_PIN_RESET);
}
 //AD9959????
void IO_Update(void)  
{
	HAL_GPIO_WritePin(AD9959_UP_GPIO_Port, AD9959_UP_Pin	, GPIO_PIN_RESET);
	delay1(4);
	HAL_GPIO_WritePin(AD9959_UP_GPIO_Port, AD9959_UP_Pin	, GPIO_PIN_SET);
	delay1(8);
	HAL_GPIO_WritePin(AD9959_UP_GPIO_Port, AD9959_UP_Pin	, GPIO_PIN_RESET);
}
/*--------------------------------------------
????:?????SPI?AD9959???
RegisterAddress: ?????
NumberofRegisters: ?????
*RegisterData: ??????
temp: ????IO???
----------------------------------------------*/
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp)
{
	uint8_t	ControlValue = 0;
	uint8_t	ValueToWrite = 0;
	uint8_t	RegisterIndex = 0;
	uint8_t	i = 0;

	ControlValue = RegisterAddress;
//????
	HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin	, GPIO_PIN_RESET); 
	delay1(1);
	for(i=0; i<8; i++)
	{
		HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_RESET);
		delay1(1);
		if(0x80 == (ControlValue & 0x80))
			HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin	, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin	, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_SET);
		delay1(1);
		ControlValue <<= 1;
	}
	HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_RESET);
	delay1(1);
//????
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin	, GPIO_PIN_RESET);
			delay1(1);
			if(0x80 == (ValueToWrite & 0x80))
				HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin	, GPIO_PIN_SET);
			else
			HAL_GPIO_WritePin(AD9959_SD0_GPIO_Port, AD9959_SD0_Pin	, GPIO_PIN_RESET); 
			
			HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_SET);
			delay1(1);
			ValueToWrite <<= 1;
		}
		HAL_GPIO_WritePin(AD9959_SCK_GPIO_Port, AD9959_SCK_Pin	, GPIO_PIN_RESET);	
		delay1(1);
	}	
	if(temp==1)
	IO_Update();	
  HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin	, GPIO_PIN_SET);
	delay1(10);
} 
/*---------------------------------------
????:????????
Channel:  ????
Freq:     ????
---------------------------------------*/
void Write_frequence(uint8_t Channel,uint32_t Freq)
{	 
		uint8_t CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//????
	  uint32_t Temp;            
	  Temp=(uint32_t)Freq*8.589934592;	  
	  CFTW0_DATA[3]=(uint8_t)Temp;
	  CFTW0_DATA[2]=(uint8_t)(Temp>>8);
	  CFTW0_DATA[1]=(uint8_t)(Temp>>16);
	  CFTW0_DATA[0]=(uint8_t)(Temp>>24);
	  if(Channel==0)	  
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);
		}
	  else if(Channel==1)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//???????CH1??
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.??CH1????	
	  }
	  else if(Channel==2)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//???????CH2??
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.??CH2????	
	  }
	  else if(Channel==3)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//???????CH3??
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,3);//CTW0 address 0x04.??CH3????	
	  }																																																																										 
	
} 
/*---------------------------------------

---------------------------------------*/
void Write_Amplitude(uint8_t Channel, u16 Ampli)
{ 
	u16 A_temp;//=0x23ff;
	uint8_t ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	
  A_temp=Ampli|0x1000;
	ACR_DATA[2] = (uint8_t)A_temp;  //????
  ACR_DATA[1] = (uint8_t)(A_temp>>8); //????
  if(Channel==0)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
  else if(Channel==1)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}
  else if(Channel==2)
  {
	  WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
  else if(Channel==3)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
}
/*---------------------------------------
????:????????
Channel:  ????
Phase:    ????,??:0~16383(????:0°~360°)
---------------------------------------*/
void Write_Phase(uint8_t Channel,u16 Phase)
{
	u16 P_temp=0;
  P_temp=(u16)Phase;
	CPOW0_DATA[1]=(uint8_t)P_temp;
	CPOW0_DATA[0]=(uint8_t)(P_temp>>8);
	if(Channel==0)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==1)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==2)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==3)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
}	 
