/*************************************************************************************
 Title	:   Analog Devices AD9833 DDS Wave Generator Library for STM32 Using HAL Libraries
 Author:    Bardia Alikhan Afshar <bardia.a.afshar@gmail.com>  
 Software:  IAR Embedded Workbench for ARM
 Hardware:  Any STM32 device
*************************************************************************************/
#include "9833.h"
// ------------------- Variables ----------------
uint16_t FRQLW = 0;    // MSB of Frequency Tuning Word
uint16_t FRQHW = 0;    // LSB of Frequency Tuning Word
uint32_t  phaseVal=0;  // Phase Tuning Value
uint8_t 	WKNOWN=0;      // Flag Variable
// -------------------------------- Functions --------------------------------
void dds_delay(void)
{
	SysTick_Delay_Us(1);
	
}
// ------------------------------------------------ Software SPI Function

// ------------------------------------------------ Initializing AD9833
void AD9833_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
	DCLK = 0;
} 



void writeSPI(uint16_t word) 
{
	u8 i = 0;
	DCLK = 0;
	dds_delay();
	
	DCLK = 1;
	dds_delay();
	
	SYNC = 0;
	dds_delay();
	
	for (i = 0; i < 16 ; i++) 
	{
    if(word & 0x8000) 
			SDATA = 1;  //bit=1, Set High
		else 
			SDATA = 0;   //bit=0, Set Low
		dds_delay();
		DCLK = 0;             //Data is valid on falling edge
		dds_delay();
		DCLK = 1;  
		word = word<<1; //Shift left by 1 bit
  }
	dds_delay();
	SYNC = 1;
	SDATA = 1;
	dds_delay();
	DCLK = 0;
	dds_delay();
}

// ------------------------------------------------ Sets Output Wave Type
void AD9833_SetWave(uint16_t Wave)
{
  switch(Wave)
	{
		case 0:
			
			writeSPI(0x2000); // Value for Sinusoidal Wave
			WKNOWN=0;
			break;
		case 1:
			writeSPI(0x2028); // Value for Square Wave
			WKNOWN=1;
			break;
		case 2:
			writeSPI(0x2002); // Value for Triangle Wave
			WKNOWN=2;
			break;
		default:
			break;
  }
}

// ------------------------------------------------ Sets Wave Frequency & Phase (In Degree) In PHASE0 & FREQ0 Registers
void AD9833_SetWaveData(float Frequency,float Phase)
{
		long freq=0;
		dds_delay();
	 // ---------- Tuning Word for Phase ( 0 - 360 Degree )
	 if(Phase<0)Phase=0; // Changing Phase Value to Positive
	 if(Phase>360)Phase=360; // Maximum value For Phase (In Degree)
			phaseVal  = ((int)(Phase*(4096/360)))|0XC000;  // 4096/360 = 11.37 change per Degree for Register And using 0xC000 which is Phase 0 Register Address
	 
 // ---------- Tuning word for Frequency      

	freq=(int)(((Frequency*pow(2,28))/FMCLK)+1); // Tuning Word
	FRQHW=(int)((freq & 0xFFFC000) >> 14); // FREQ MSB
	FRQLW=(int)(freq & 0x3FFF);  // FREQ LSB 
	FRQLW |= 0x4000;
	FRQHW |= 0x4000; 
 // ------------------------------------------------ Writing DATA
	writeSPI(0x2100); // enable 16bit words and set reset bit
	writeSPI(FRQLW);
	writeSPI(FRQHW);
  writeSPI(phaseVal);
	writeSPI(0x2000); // clear reset bit 
	dds_delay();
	AD9833_SetWave(WKNOWN);
	dds_delay();
}


