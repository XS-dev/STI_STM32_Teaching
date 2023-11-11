#include "AD9834.h"

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
    data <<= 1 ; 
    AD9834_SCLK_H; 
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
