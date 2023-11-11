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
	Delay_Us(10);
	
}
// ------------------------------------------------ Software SPI Function

// ------------------------------------------------ Initializing AD9833
void AD9833_Init(void)
{
	AD9833_SetWave(0);
	AD9833_SetWaveData(0,0);
} 



void writeSPI(uint16_t word) 
{
	uint8_t i = 0;
	DSDATA_LOW;
	dds_delay();
	
	DCLK_HIGH;
	dds_delay();
	
	DSYNC_LOW;
	dds_delay();
	
	for (i = 0; i < 16 ; i++) 
	{
    if(word & 0x8000)
		{
			DSDATA_HIGH;  //bit=1, Set High
		}			
		else
		{
			DSDATA_LOW;   //bit=0, Set Low
		}
		
		dds_delay();
		DCLK_LOW;             //Data is valid on falling edge
		dds_delay();
		DCLK_HIGH;  
		word = word<<1; //Shift left by 1 bit
  }
	dds_delay();
	DSYNC_HIGH;
	DSDATA_HIGH;
	dds_delay();
	DCLK_LOW;
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


