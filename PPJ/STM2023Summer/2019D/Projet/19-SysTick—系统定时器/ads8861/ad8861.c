#include "ad8861.h"

void AD_Delay(void)
{
	SysTick_Delay_Us(1);
}
void AD_GPIO_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
}

void AD_Init(void)
{
	AD_GPIO_INIT();
	GPIOA->CRL&=0XFF0FFFFF;
	GPIOA->CRL|=(u32)8<<20;;
}


void AD_START(void)
{
	DIN = 1;
	AD_Delay();
	CONVST = 1;
	SCLK = 1;
	AD_Delay();
	DIN = 0;
	AD_Delay();

}



void AD_STOP(void)
{
	DIN = 1;
	AD_Delay();
	CONVST = 0;
	AD_Delay();
	CONVST = 1;
	AD_Delay();
	CONVST = 0;
	DIN = 0;
}



u16 AD_Read(void)
{
	unsigned char i,receive=0;
	for(i=0;i<8;i++ )
	{
		SCLK=1; 
		if(READ_DOUT)receive++;   
		AD_Delay();
		SCLK=0;
		receive<<=1;
		AD_Delay();		
  }					 
	return receive;
}

u16 AD_RESULT(void)
{
	u16 receive=0;
	AD_START();
	receive = AD_Read();
	AD_STOP();
	return receive;

}








