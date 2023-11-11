/**********************************************************
                       ��������
										 
���ܣ�stm32f103rct6����
			��ʾ��12864
�ӿڣ������ӿ������key.h
ʱ�䣺2015/11/3
�汾��1.0
���ߣ���������
������

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://shop110336474.taobao.com/?spm=a230r.7195193.1997079397.2.Ic3MRJ

**********************************************************/


#include "AD9910.h"


const uchar cfr1[]={0x00,0x40,0x00,0x00};       //cfr1������
const uchar cfr2[]={0x01,0x00,0x00,0x00};       //cfr2������
const uchar cfr3[]={0x05,0x0F,0x41,0x32};       //cfr3������  40M����  25��Ƶ  VC0=101   ICP=001;
uchar profile11[]={0x3f,0xff,0x00,0x00,0x25,0x09,0x7b,0x42};       //profile1������ 0x25,0x09,0x7b,0x42
                  //01������� 23��λ���� 4567Ƶ�ʵ�г��
void AD9110_IOInit(void)
{
//	GPIO_InitTypeDef GPIO_InitStructure ; 
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; 
//	GPIO_Init(GPIOB ,&GPIO_InitStructure) ; 

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_8| GPIO_Pin_2; 
//	GPIO_Init(GPIOA ,&GPIO_InitStructure) ;

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All^(GPIO_Pin_14| GPIO_Pin_15); 
//	GPIO_Init(GPIOC ,&GPIO_InitStructure) ;
}

//=====================================================================


//======================����8λ���ݳ���===================================
void txd_8bit(uchar txdat)
{uchar i,sbt;
  sbt=0x80;
  AD9910_SCLK_L;
  for (i=0;i<8;i++)
   {
		 if ((txdat & sbt)==0) 
		 {
			 AD9910_SDIO_L; 
		 }
			 
		 else
		 {
			 AD9910_SDIO_H;
		 }			 	 
    AD9910_SCLK_H;
		sbt=sbt>>1;
		AD9910_SCLK_L;
   }
 }

 
/************************************************************
** �������� ��void Init_ad9910(void))
** �������� ����ʼ��AD9910�Ĺܽź���򵥵��ڲ��Ĵ��������ã�
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
**************************************************************/
void Init_ad9910(void)
{
	uchar k,m;
	
	AD9110_IOInit();//IO��ʼ��
	AD9910_PWR_L;//��������
	
	AD9910_PF0_L;
	AD9910_PF1_L;
	AD9910_PF2_L;

	AD9910_DRC_L;
	AD9910_DRH_L;                                                                                        
	AD9910_RST_H; 
//delay_ms(5); 
	Delay_Ms(5);	
	AD9910_RST_L; 
	
	AD9910_CS_L;
	txd_8bit(0x00);    //����CFR1�����ֵ�ַ
	for (m=0;m<4;m++)
		txd_8bit(cfr1[m]); 
	AD9910_CS_H;  
	for (k=0;k<10;k++);
	AD9910_CS_L;
	txd_8bit(0x01);    //����CFR2�����ֵ�ַ
	for (m=0;m<4;m++)
	txd_8bit(cfr2[m]); 
	AD9910_CS_H;  
	for (k=0;k<10;k++);

	AD9910_CS_L;
  txd_8bit(0x02);    //����CFR3�����ֵ�ַ
	for (m=0;m<4;m++)
	txd_8bit(cfr3[m]); 
  AD9910_CS_H;
	for (k=0;k<10;k++);

	AD9910_UP_H;
	for(k=0;k<10;k++);
	AD9910_UP_L;
	//delay_ms(1);
	Delay_Ms(1);

}      
/************************************************************
** �������� ��void Txfrc(void))
** �������� ����AD9910оƬ����Ƶ�ʣ����ȵ���ؿ�������
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
**************************************************************/
void Txfrc(void)
{
	uchar m;

	AD9910_CS_L;
	txd_8bit(0x0e);    //����profile1�����ֵ�ַ
	for (m=0;m<8;m++)
	txd_8bit(profile11[m]); 
	AD9910_CS_H;

	AD9910_UP_H;
	AD9910_UP_L;
}         
/************************************************************
** �������� ��void Freq_convert(void))
** �������� ������Ҫ��Ƶ��ת��Ϊ��Ӧ�Ŀ������ݣ������profile11�����͵�оƬ
** ��ڲ��� ��Ŀ��Ƶ�ʣ���λHz
** ���ڲ��� ����
** ����˵�� ����
**************************************************************/
void Freq_convert(ulong Freq)
{
	  ulong Temp;            
	  Temp=(ulong)Freq*4.294967296;	   //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  ��Ƶ1GHz��32λ��λ�ۼ�������ÿHz�ڵĿ��������� delta =  4.294967296 = (2^32)/1000000000
	  profile11[7]=(uchar)Temp;
	  profile11[6]=(uchar)(Temp>>8);
	  profile11[5]=(uchar)(Temp>>16);
	  profile11[4]=(uchar)(Temp>>24);
	  Txfrc();
}

/************************************************************
** �������� ��void AD9910_AmpWrite(void))
** �������� �������ȿ������ݱ��浽profile11��д��оƬ
** ��ڲ��� �����ȿ����֣���Χ0~16383
** ���ڲ��� ����
** ����˵�� ��14λ���ȿ����֣���������0~16383��Ӧ�������0~800mV����
**************************************************************/
void AD9910_AmpWrite(uint16_t Amp)
{
		profile11[0] = (Amp%16384)>>8;
		profile11[1] = (Amp%16384)&0xff;
	  Txfrc();
}
