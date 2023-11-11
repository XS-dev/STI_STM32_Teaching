#include "ad7946.h"


void ad79_delay(void)
{
	SysTick_Delay_Us(1);
	
}


void AD79_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure1;
	
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_9|GPIO_Pin_10);
										
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure1);

}


u16 AD79_Read(void) 
{
	unsigned char i,receive=0;
	ADCLK = 1;
	ad79_delay();
	ADCLK  =0;
	ad79_delay();
	CS = 0;
	
	for(i=0;i<14;i++ )
	{
		ADCLK=1; 
		if(SDO_READ)receive++;   
		ad79_delay();
		ADCLK=0;
		receive<<=1;
		ad79_delay();		
  	}
	ADCLK=1; 
	ad79_delay();
	ADCLK =0;
	ad79_delay();
	
	ADCLK=1; 
	ad79_delay();
	ADCLK =0;
	ad79_delay();
	
	CS = 1;
	ad79_delay();
	ad79_delay();
	ad79_delay();
	ad79_delay();
	CS = 0;
	ad79_delay();	
	ADCLK =1;
	ad79_delay();

	return receive;
}
