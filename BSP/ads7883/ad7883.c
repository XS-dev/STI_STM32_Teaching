#include "ad7883.h"


void ad78_delay(void)
{
	SysTick_Delay_Us(10);
	
}



void AD78_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure1;
	
	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC, GPIO_Pin_11);
										
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure1);

}


u16 AD78_Read(void)
{
	u16 i,receive=0;
	AD78_CS = 1;
	ad78_delay();

	AD78_CS = 0;//开始信号 第1个0
	ad78_delay();

	for(i=0;i<16;i++ )
	{
		AD78_SCLK=0; 
		
		ad78_delay();
		if(AD78_SDO_READ)receive++; 
	  receive<<=1;
		AD78_SCLK=1;
		ad78_delay();		
  }

	receive >>=4;
	AD78_CS = 1;
	ad78_delay();
	ad78_delay();

	return receive;
}

