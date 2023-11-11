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

#include "AD9854.h"     



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
//  GPIO_InitTypeDef GPIO_InitStruct = {0};

//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//  __HAL_RCC_GPIOC_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//  __HAL_RCC_GPIOD_CLK_ENABLE();
//  __HAL_RCC_GPIOG_CLK_ENABLE();
//  __HAL_RCC_GPIOA_CLK_ENABLE();

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, RST_Pin|A5_Pin|D7_Pin|A4_Pin, GPIO_PIN_RESET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOD, D6_Pin|A3_Pin|D5_Pin|A2_Pin
//                          |D4_Pin|A1_Pin|D3_Pin|A0_Pin, GPIO_PIN_RESET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOG, D2_Pin|UDCLK_Pin|D1_Pin|D0_Pin, GPIO_PIN_RESET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOG, WD_Pin|RD_Pin, GPIO_PIN_SET);

//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOC, OSK_Pin|FSK_Pin, GPIO_PIN_RESET);

//  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
//  GPIO_InitStruct.Pin = RST_Pin|A5_Pin|D7_Pin|A4_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
//                           PDPin PDPin PDPin PDPin */
//  GPIO_InitStruct.Pin = D6_Pin|A3_Pin|D5_Pin|A2_Pin
//                          |D4_Pin|A1_Pin|D3_Pin|A0_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

//  /*Configure GPIO pins : PGPin PGPin PGPin */
//  GPIO_InitStruct.Pin = D2_Pin|D1_Pin|D0_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = UDCLK_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(UDCLK_GPIO_Port, &GPIO_InitStruct);

//  /*Configure GPIO pins : PGPin PGPin */
//  GPIO_InitStruct.Pin = WD_Pin|RD_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

//  /*Configure GPIO pins : PCPin PCPin */
//  GPIO_InitStruct.Pin = OSK_Pin|FSK_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
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
	if((dat &0x01)>>0){DDS_D0_H;}else {DDS_D0_L;}
	if((dat &0x02)>>1){DDS_D1_H;}else {DDS_D1_L;}
	if((dat &0x04)>>2){DDS_D2_H;}else {DDS_D2_L;}
	if((dat &0x08)>>3){DDS_D3_H;}else {DDS_D3_L;}
	if((dat &0x10)>>4){DDS_D4_H;}else {DDS_D4_L;}
	if((dat &0x20)>>5){DDS_D5_H;}else {DDS_D5_L;}
	if((dat &0x40)>>6){DDS_D6_H;}else {DDS_D6_L;}
	if((dat &0x80)>>7){DDS_D7_H;}else {DDS_D7_L;}
		 
	if(( addr&0x20)>>5) {DDS_A5_H;}else {DDS_A5_L;}
	if(( addr&0x10)>>4) {DDS_A4_H;}else {DDS_A4_L;}
	if(( addr&0x08)>>3) {DDS_A3_H;}else {DDS_A3_L;}
	if(( addr&0x04)>>2) {DDS_A2_H;}else {DDS_A2_L;}
	if(( addr&0x02)>>1) {DDS_A1_H;}else {DDS_A1_L;}
	if(( addr&0x01)>>0) {DDS_A0_H;}else {DDS_A0_L;}
	
	AD9854_WR_L;
	AD9854_WR_H;
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
	AD9854_WR_H;//������д���ƶ˿���Ϊ��Ч
	AD9854_RD_H;
	AD9854_UDCLK_L;
	AD9854_RST_H;                 //��λAD9854
	AD9854_RST_L;

	AD9854_WR_Byte(0x1d,0x00);					//�򿪱Ƚ���
	//	AD9854_WR_Byte(0x1d,0x10);	    //�رձȽ���
	AD9854_WR_Byte(0x1e,CLK_Set);	   		//����ϵͳʱ�ӱ�Ƶ            
	AD9854_WR_Byte(0x1f,0x00);	   			//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x20,0x60);	   			//����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����

	AD9854_UDCLK_H;               			//����AD9854���
	AD9854_UDCLK_L;
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

	AD9854_UDCLK_H;                    //����AD9854���
	AD9854_UDCLK_L;
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

	AD9854_UDCLK_H;                    //����AD9854���
	AD9854_UDCLK_L;
}

