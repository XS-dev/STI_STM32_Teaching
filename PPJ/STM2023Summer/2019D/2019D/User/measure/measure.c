#include "measure.h"

void general_measure(bool i1,bool i2, bool i4)
{
	JD1=i1;
	JD2=i2;
	JD4=i4;
}

void oneKgain(void)
{
	float IN,OUT;
	general_measure(0,1,0);
	IN=singlesaopin(ADC_CHANNEL1,0x07,1000,60);
	OUT=singlesaopin(ADC_CHANNEL2,0x07,1000,60);
	K1ZE=OUT/IN*100;
//	printf("%f\r\n",K1ZE);
}

void InputResistor(void)
{
	float US,UI	;
	general_measure(0,1,1);
	SysTick_Delay_Ms(50);
	US=singlesaopin(ADC_CHANNEL1,0x07,1000,60);
//	US = (ADC_ConvertedValueLocal[990]+ADC_ConvertedValueLocal[10])/2;
	general_measure(1,1,1);
	SysTick_Delay_Ms(50);
	UI=singlesaopin(ADC_CHANNEL1,0x07,1000,60);
//	UI = (ADC_ConvertedValueLocal[990]+ADC_ConvertedValueLocal[10])/2;
	INResistor=6.8*UI/(US-UI);
	printf("%f ",UI);
	printf("%f ",US);
	printf("%f\r\n",INResistor);
	
}

void outputResistor(void)
{
	float US,UI	;
	general_measure(0,1,0);
	SysTick_Delay_Ms(50);
	US=singlesaopin(ADC_CHANNEL1,0x07,1000,60);
//	US = (ADC_ConvertedValueLocal[990]+ADC_ConvertedValueLocal[10])/2;
	general_measure(0,0,0);
	SysTick_Delay_Ms(50);
	UI=singlesaopin(ADC_CHANNEL2,0x07,1000,60);
//	UI = (ADC_ConvertedValueLocal[990]+ADC_ConvertedValueLocal[10])/2;
	OUResistor=1.5*(US-UI)/UI;
//	printf("%f ",UI);
//	printf("%f ",US);
//	printf("%f\r\n",OUResistor);
	
}
