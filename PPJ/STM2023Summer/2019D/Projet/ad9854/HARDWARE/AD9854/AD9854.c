//=====================================================================
//                    AD9854 �����������
//Ӳ������: PC7~-PC0    ����Data;	  
//          PC13~PC8   ����Adr;    
//          RESET ����PA6;     
//          UDCLK ����PA4;   
//          WR    ����PA5;	  
//          RD    ����PA8;    
//          FDATA ����PB10;     
//          OSK   ����PA2;  
//          VDD--�߼���Դ(3.3V)
//          VSS--GND(0V)  
//AD9854.c
//�������ӹ�����
//˵�������������Ӳ������Ӿ���Ϊ20MHZ
//=====================================================================

#include <AD9854.h>      //STC��Ƭ��ͷ�ļ�	
#include "delay.h"



uchar FreqWord[6];				 //6���ֽ�Ƶ�ʿ�����

//**********************����Ϊϵͳʱ���Լ�����ر�������**************************

/* 
      �˴������Լ�����Ҫ����ϵͳʱ���Լ�������ص����ӣ�һ������ֻ�迪��һ��   
      CLK_SetΪʱ�ӱ�Ƶ���ã�������4~20����Ƶ��������ܳ���300MHZ
      Freq_mult_ulong��Freq_mult_doulle��Ϊ2��48�η�����ϵͳʱ�ӣ�һ��Ϊ�����Σ�һ��Ϊ˫������
*/

/*
#define      CLK_Set            4
const ulong  Freq_mult_ulong  = 3518437;
const double Freq_mult_doulle = 3518437.2088832;
*/

/*
#define      CLK_Set            5
const ulong  Freq_mult_ulong  = 2814750;
const double Freq_mult_doulle = 2814749.76710656;
*/

 /*
#define      CLK_Set            6
const ulong  Freq_mult_ulong  = 2345625;
const double Freq_mult_doulle = 2345624.80592213;
  */

/*
#define      CLK_Set            7
const ulong  Freq_mult_ulong  = 2010536;
const double Freq_mult_doulle = 2010535.54793326;
*/

/*
#define      CLK_Set            8
const ulong  Freq_mult_ulong  = 1759219;
const double Freq_mult_doulle = 1759218.6044416;
*/

/*
#define      CLK_Set            9
const ulong  Freq_mult_ulong  = 1563750;
const double Freq_mult_doulle = 1563749.87061476;
*/

/*
#define      CLK_Set            10
const ulong  Freq_mult_ulong  = 1407375;
const double Freq_mult_doulle = 1407374.88355328;
*/

/*
#define      CLK_Set            11
const ulong  Freq_mult_ulong  = 1279432;
const double Freq_mult_doulle = 1279431.712321164;
*/


#define      CLK_Set            12
const ulong  Freq_mult_ulong  = 1172812;
const double Freq_mult_doulle = 1172812.402961067;


/*
#define      CLK_Set            13
const ulong  Freq_mult_ulong  = 1082596;
const double Freq_mult_doulle = 1082596.064271754;
*/

/*
#define      CLK_Set            14
const ulong  Freq_mult_ulong  = 1005268;
const double Freq_mult_doulle = 1005267.773966629;
*/

/*
#define      CLK_Set            15
const ulong  Freq_mult_ulong  = 938250;
const double Freq_mult_doulle = 938249.9223688533;

 */
//**************************�޸�Ӳ��ʱҪ�޸ĵĲ���********************************



//**************************���²���Ϊ��������********************************

static void AD9854_WR_Byte(u32 addr,u32 dat);
extern void AD9854_Init(void);						  
static void Freq_convert(long Freq);	         	  
extern void AD9854_SetSine(ulong Freq,uint Shape);	  
static void Freq_double_convert(double Freq);		  
extern void AD9854_SetSine_double(double Freq,uint Shape);
extern void AD9854_InitFSK(void);				
extern void AD9854_SetFSK(ulong Freq1,ulong Freq2);					  
extern void AD9854_InitBPSK(void);					  
extern void AD9854_SetBPSK(uint Phase1,uint Phase2);					
extern void AD9854_InitOSK(void);					 
extern void AD9854_SetOSK(uchar RateShape);					  
extern void AD9854_InitAM(void);					 
extern void AD9854_SetAM(uint Shape);					
extern void AD9854_InitRFSK(void);					 
extern void AD9854_SetRFSK(ulong Freq_Low,ulong Freq_High,ulong Freq_Up_Down,ulong FreRate);				

void AD9854_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure ; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_Init(GPIOB ,&GPIO_InitStructure) ; 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_8| GPIO_Pin_2; 
	GPIO_Init(GPIOA ,&GPIO_InitStructure) ;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All^(GPIO_Pin_14| GPIO_Pin_15); 
	GPIO_Init(GPIOC ,&GPIO_InitStructure) ;
}

//====================================================================================
//��������:void AD9854_WR_Byte(uchar addr,uchar dat)
//��������:AD9854���п�д������
//��ڲ���:addr     6λ��ַ
//         dat      д�������
//���ڲ���:��
//====================================================================================
	u32 dat1,dat2;

void AD9854_WR_Byte(u32 addr,u32 dat)
{
	uint32_t wData = 0;
	
	dat1= dat|(addr<<8);
	
	wData =(dat1&0x3fff)|((dat1^0x3fff)<<16);
	AD9854_AdrBus = wData;
	AD9854_WR      = 0;
	AD9854_WR      = 1;
}

//====================================================================================
//��������:void AD9854_Init(void)
//��������:AD9854��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_Init(void)
{
	AD9854_IO_Init();
	AD9854_WR=1;//������д���ƶ˿���Ϊ��Ч
	AD9854_RD=1;
	AD9854_UDCLK=0;
	AD9854_RST=1;                 //��λAD9854
	AD9854_RST=0;

	AD9854_WR_Byte(0x1d,0x00);					//�򿪱Ƚ���
	//	AD9854_WR_Byte(0x1d,0x10);	    //�رձȽ���
	AD9854_WR_Byte(0x1e,CLK_Set);	   		//����ϵͳʱ�ӱ�Ƶ            
	AD9854_WR_Byte(0x1f,0x00);	   			//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x20,0x60);	   			//����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����

	AD9854_UDCLK=1;               			//����AD9854���
	AD9854_UDCLK=0;
}
//====================================================================================
//��������:void Freq_convert(long Freq)
//��������:�����ź�Ƶ������ת��
//��ڲ���:Freq   ��Ҫת����Ƶ�ʣ�ȡֵ��0~SYSCLK/2
//���ڲ���:��   ����Ӱ��ȫ�ֱ���FreqWord[6]��ֵ
//˵����   ���㷨λ���ֽ�����㷨���й�ʽFTW = (Desired Output Frequency �� 2N)/SYSCLK
//         �õ����㷨������N=48��Desired Output Frequency Ϊ����Ҫ��Ƶ�ʣ���Freq��SYSCLK
//         Ϊ�ɱ�̵�ϵͳʱ�ӣ�FTWΪ48Bit��Ƶ�ʿ����֣���FreqWord[6]
//====================================================================================
void Freq_convert(long Freq)   
{
	ulong FreqBuf;
	ulong Temp=Freq_mult_ulong;   	       

	uchar Array_Freq[4];			     //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�
	Array_Freq[0]=(uchar)Freq;
	Array_Freq[1]=(uchar)(Freq>>8);
	Array_Freq[2]=(uchar)(Freq>>16);
	Array_Freq[3]=(uchar)(Freq>>24);

	FreqBuf=Temp*Array_Freq[0];                  
	FreqWord[0]=FreqBuf;    
	FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[1]);
	FreqWord[1]=FreqBuf;
	FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[2]);
	FreqWord[2]=FreqBuf;
	FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[3]);
	FreqWord[3]=FreqBuf;
	FreqBuf>>=8;

	FreqWord[4]=FreqBuf;
  FreqWord[5]=FreqBuf>>8;			
}  

//====================================================================================
//��������:void AD9854_SetSine(ulong Freq,uint Shape)
//��������:AD9854���Ҳ���������
//��ڲ���:Freq   Ƶ�����ã�ȡֵ��ΧΪ0~(1/2)*SYSCLK
//         Shape  ��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095) ,ȡֵԽ��,����Խ�� 
//���ڲ���:��
//====================================================================================
void AD9854_SetSine(ulong Freq,uint Shape)
{
	uchar count;
	uchar Adress;

	Adress = 0x04;                        //ѡ��Ƶ�ʿ����ֵ�ַ�ĳ�ֵ

	Freq_convert(Freq);		           //Ƶ��ת��

	for(count=6;count>0;)	          //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
	}

	AD9854_WR_Byte(0x21,Shape>>8);	  //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	  //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK=1;                    //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void Freq_doublt_convert(double Freq)
//��������:�����ź�Ƶ������ת��
//��ڲ���:Freq   ��Ҫת����Ƶ�ʣ�ȡֵ��0~SYSCLK/2
//���ڲ���:��   ����Ӱ��ȫ�ֱ���FreqWord[6]��ֵ
//˵����   �й�ʽFTW = (Desired Output Frequency �� 2N)/SYSCLK�õ��ú�����
//         ����N=48��Desired Output Frequency Ϊ����Ҫ��Ƶ�ʣ���Freq��SYSCLK
//         Ϊ�ɱ�̵�ϵͳʱ�ӣ�FTWΪ48Bit��Ƶ�ʿ����֣���FreqWord[6]
//ע�⣺   �ú��������溯��������Ϊ�ú�������ڲ���Ϊdouble����ʹ�źŵ�Ƶ�ʸ���ȷ
//         ������100HZ�����ñ��������ڸ���100HZ��������ú���void Freq_convert(long Freq)
//====================================================================================
void Freq_double_convert(double Freq)   
{
	ulong Low32;
	uint  High16;
	double Temp=Freq_mult_doulle;   	            //23ca99Ϊ2��48�η�����120M
	Freq*=(double)(Temp);
	//	1 0000 0000 0000 0000 0000 0000 0000 0000 = 4294967295
	High16 =(int)(Freq/4294967295);                  //2^32 = 4294967295
	Freq -= (double)High16*4294967295;
	Low32 = (ulong)Freq;

	FreqWord[0]=Low32;	     
	FreqWord[1]=Low32>>8;
	FreqWord[2]=Low32>>16;
	FreqWord[3]=Low32>>24;
	FreqWord[4]=High16;
	FreqWord[5]=High16>>8;			
} 
//====================================================================================
//��������:void AD9854_SetSine_double(double Freq,uint Shape)
//��������:AD9854���Ҳ���������
//��ڲ���:Freq   Ƶ�����ã�ȡֵ��ΧΪ0~1/2*SYSCLK
//         Shape  ��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095) 
//���ڲ���:��
//====================================================================================
void AD9854_SetSine_double(double Freq,uint Shape)
{
	uchar count=0;
	uchar Adress;

	Adress=0x04;						     //ѡ��Ƶ�ʿ�����1��ַ�ĳ�ֵ

	Freq_double_convert(Freq);		           //Ƶ��ת��

	for(count=6;count>0;)	                    //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
	}

	AD9854_WR_Byte(0x21,Shape>>8);	  //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	  //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK=1;                    //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void AD9854_InitFSK(void)
//��������:AD9854��FSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitFSK(void)
{
	AD9854_WR=1;                        //������д���ƶ˿���Ϊ��Ч
	AD9854_RD=1;
	AD9854_UDCLK=0;
	AD9854_RST=1;                        //��λAD9854
	AD9854_RST=0;	

	AD9854_WR_Byte(0x1d,0x00);	       //�򿪱Ƚ���
	AD9854_WR_Byte(0x1e,CLK_Set);	   //����ϵͳʱ�ӱ�Ƶ
	AD9854_WR_Byte(0x1f,0x02);	       //����ϵͳΪģʽ1�����ⲿ����
	AD9854_WR_Byte(0x20,0x60);	      //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����

	AD9854_UDCLK=1;                  //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void AD9854_SetFSK(ulong Freq1,ulong Freq2)
//��������:AD9854��FSK����
//��ڲ���:Freq1   FSKƵ��1
//         Freq2   FSKƵ��2
//���ڲ���:��
//====================================================================================
void AD9854_SetFSK(ulong Freq1,ulong Freq2)
{
	uchar count=6;
	uchar Adress1,Adress2;

	const uint Shape=4000;	      //��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095)

	Adress1=0x04;				 //ѡ��Ƶ�ʿ�����1��ַ�ĳ�ֵ
	Adress2=0x0a;				 //ѡ��Ƶ�ʿ�����2��ַ�ĳ�ֵ

	Freq_convert(Freq1);               //Ƶ��ת��1

	for(count=6;count>0;)	          //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress1++,FreqWord[--count]);
	}

	Freq_convert(Freq2);               //Ƶ��ת��2

	for(count=6;count>0;)	          //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress2++,FreqWord[--count]);
	}

	AD9854_WR_Byte(0x21,Shape>>8);	      //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	     //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK=1;                    //����AD9854���
	AD9854_UDCLK=0;		
}

//====================================================================================
//��������:void AD9854_InitBPSK(void)
//��������:AD9854��BPSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitBPSK(void)
{
	AD9854_WR=1;                    //������д���ƶ˿���Ϊ��Ч
	AD9854_RD=1;
	AD9854_UDCLK=0;
	AD9854_RST=1;                   //��λAD9854
	AD9854_RST=0;

	AD9854_WR_Byte(0x1d,0x00);	       //�򿪱Ƚ������������
	AD9854_WR_Byte(0x1e,CLK_Set);	   //����ϵͳʱ�ӱ�Ƶ
	AD9854_WR_Byte(0x1f,0x08);	      //����ϵͳΪģʽ4�����ⲿ����
	AD9854_WR_Byte(0x20,0x60);	      //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����

	AD9854_UDCLK=1;                //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void AD9854_SetBPSK(uint Phase1,uint Phase2)
//��������:AD9854��BPSK����
//��ڲ���:Phase1   ������λ1
//         Phase2	������λ2
//���ڲ���:��
//˵����   ��λΪ14Bit��ȡֵ��0~16383���������ñ�������ʱ��Phase1����Ϊ0��
//         ��Phase1����Ϊ8192��180����λ
//====================================================================================
void AD9854_SetBPSK(uint Phase1,uint Phase2)
{
	uchar count;

	const ulong Freq=60000;
	const uint Shape=4000;

	uchar Adress;
	Adress=0x04;                           //ѡ��Ƶ�ʿ�����1��ַ�ĳ�ֵ

	AD9854_WR_Byte(0x00,Phase1>>8);	           //������λ1
	AD9854_WR_Byte(0x01,(uchar)(Phase1&0xff));

	AD9854_WR_Byte(0x02,Phase2>>8);	          //������λ2
	AD9854_WR_Byte(0x03,(uchar)(Phase2&0xff));

	Freq_convert(Freq);                            //Ƶ��ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
	}

	AD9854_WR_Byte(0x21,Shape>>8);	                  //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	               //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK=1;                                //����AD9854���
	AD9854_UDCLK=0;	
}

//====================================================================================
//��������:void AD9854_InitOSK(void)
//��������:AD9854��OSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitOSK(void)
{
	AD9854_WR=1;                           //������д���ƶ˿���Ϊ��Ч
	AD9854_RD=1;
	AD9854_UDCLK=0;
	AD9854_RST=1;                          //��λAD9854
	AD9854_RST=0;

	AD9854_WR_Byte(0x1d,0x00);	           //�򿪱Ƚ���
	AD9854_WR_Byte(0x1e,CLK_Set);	       //����ϵͳʱ�ӱ�Ƶ
	AD9854_WR_Byte(0x1f,0x00);	           //����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x20,0x70);	           //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����,ͨ�������ڲ�����

	AD9854_UDCLK=1;                        //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void AD9854_SetOSK(uchar RateShape)
//��������:AD9854��OSK����
//��ڲ���: RateShape    OSKб��,ȡֵΪ4~255��С��4����Ч
//���ڲ���:��
//====================================================================================
void AD9854_SetOSK(uchar RateShape)
{
	uchar count;

	const ulong Freq=60000;			 //������Ƶ
	const uint  Shape=4000;			//��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095)

	uchar Adress;
	Adress=0x04;               //ѡ��Ƶ�ʿ����ֵ�ַ�ĳ�ֵ

	Freq_convert(Freq);                       //Ƶ��ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
	}

	AD9854_WR_Byte(0x21,Shape>>8);	                  //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	                  //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));  	 


	AD9854_WR_Byte(0x25,RateShape);				       //����OSKб��

	AD9854_UDCLK=1;                                //����AD9854���
	AD9854_UDCLK=0;	
}

//====================================================================================
//��������:void AD9854_InitAM(void)
//��������:AD9854��AM��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitAM(void)
{
	uchar count;

	const ulong Freq=60000;			 //������Ƶ

	uchar  Adress;
	Adress=0x04;      //ѡ��Ƶ�ʿ����ֵ�ַ�ĳ�ֵ

	AD9854_WR=1;    //������д���ƶ˿���Ϊ��Ч
	AD9854_RD=1;
	AD9854_UDCLK=0;
	AD9854_RST=1;     //��λAD9854
	AD9854_RST=0;

	AD9854_WR_Byte(0x1d,0x00);	                  //�򿪱Ƚ���
	AD9854_WR_Byte(0x1e,CLK_Set);	             //����ϵͳʱ�ӱ�Ƶ
	AD9854_WR_Byte(0x1f,0x00);	                 //����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x20,0x60);	                  //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����

	Freq_convert(Freq);                            //Ƶ��ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
	}

	AD9854_UDCLK=1;                             //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void AD9854_SetAM(uchar Shape)
//��������:AD9854��AM����
//��ڲ���:Shape   12Bit����,ȡֵ��0~4095   
//���ڲ���:��
//====================================================================================
void AD9854_SetAM(uint Shape)
{
	AD9854_WR_Byte(0x21,Shape>>8);	                  //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	                  //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK=1;                                   //����AD9854���
	AD9854_UDCLK=0;			
}

//====================================================================================
//��������:void AD9854_InitRFSK(void)
//��������:AD9854��RFSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitRFSK(void)
{
	AD9854_WR=1;                      //������д���ƶ˿���Ϊ��Ч
	AD9854_RD=1;
	AD9854_UDCLK=0;
	AD9854_RST=1;                     //��λAD9854
	AD9854_RST=0;

	AD9854_WR_Byte(0x1d,0x00);	       //�򿪱Ƚ���
	AD9854_WR_Byte(0x1e,CLK_Set);	   //����ϵͳʱ�ӱ�Ƶ
	AD9854_WR_Byte(0x1f,0x24);	        //����ϵͳΪģʽ2�����ⲿ����,ʹ�����ǲ�ɨƵ����
	AD9854_WR_Byte(0x20,0x60);	        //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����	

	AD9854_UDCLK=1;                   //����AD9854���
	AD9854_UDCLK=0;
}

//====================================================================================
//��������:void AD9854_SetRFSK(void)
//��������:AD9854��RFSK����
//��ڲ���:Freq_Low          RFSK��Ƶ��	   48Bit
//         Freq_High         RFSK��Ƶ��	   48Bit
//         Freq_Up_Down		 ����Ƶ��	   48Bit
//		   FreRate           б��ʱ�ӿ���  20Bit
//���ڲ���:��
//ע��     ÿ��������֮���ʱ����������ʽ��ʾ��FreRate +1��*��System Clock ����һ������,
//         Ƶ�� ���������½� һ������Ƶ��
//====================================================================================
void AD9854_SetRFSK(ulong Freq_Low,ulong Freq_High,ulong Freq_Up_Down,ulong FreRate)
{
	uchar count=6;
	uchar Adress1,Adress2,Adress3;
	const uint  Shape=4000;			   //��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095)

	Adress1=0x04;		     //ѡ��Ƶ�ʿ����ֵ�ַ�ĳ�ֵ 
	Adress2=0x0a;
	Adress3=0x10;

	Freq_convert(Freq_Low);                             //Ƶ��1ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress1++,FreqWord[--count]);
	}

	Freq_convert(Freq_High);                             //Ƶ��2ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress2++,FreqWord[--count]);
	}

	Freq_convert(Freq_Up_Down);                             //����Ƶ��ת��

	for(count=6;count>0;)	                               //д��6�ֽڵ�Ƶ�ʿ�����  
	{
		AD9854_WR_Byte(Adress3++,FreqWord[--count]);
	}

	AD9854_WR_Byte(0x1a,(uchar)((FreRate>>16)&0x0f));				   //����б������
	AD9854_WR_Byte(0x1b,(uchar)(FreRate>>8));
	AD9854_WR_Byte(0x1c,(uchar)FreRate);				    

	AD9854_WR_Byte(0x21,Shape>>8);	                  //����Iͨ������
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));

	AD9854_WR_Byte(0x23,Shape>>8);	                  //����Qͨ������
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK=1;                                //����AD9854���
	AD9854_UDCLK=0;	
}
