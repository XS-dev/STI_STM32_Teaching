#include "AD9910.h"

uint8_t CFR1[]={0x00,0x40,0x00,0x00}; // ����AD9910��Sinc�˲���      												//CFR1������
uint8_t CFR2[]={0x00,0x00,0x00,0x00}; // ���ж˿�ʹ�� ���е�CFR2[3]=0x30ʱ�����пڵ�Ƶ��λ����Ƶ��*2^0  , �� CFR2[3]=0x33ʱ�����пڵ�Ƶ��λ����Ƶ��*2^3;      												//CFR2������
uint8_t CFR3[]={0x05,0x0F,0x41,0x32};// CFR3���ƹ��ܼĴ���3   ʱ�ӱ�Ƶ25��  ����ʱ��45M  

uint8_t Assist_DAC[]={0x00,0x00,0x00,0x7F};	// ����DAC���  Ĭ��0x7f

//uint8_t Profile_All[8];			// Profile���ݴ�λ��  //01������� 23��λ���� 4567Ƶ�ʵ�г��
uint8_t Profile_All[]={0x3f,0xff,0x00,0x00,0x25,0x09,0x7b,0x42};//profile1������ 
                  


uint8_t drgparameter[20]={0x00}; //DRG����
uint8_t ramprofile0[8] = {0x00}; //ramprofile0������

uint32_t ramdata[4096];

uint8_t DRL[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};// ����б����ֵ				0x0B
uint8_t DRS[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};// ����б�²���				0x0C
uint8_t DRR[]={0x00,0x00,0x00,0x00};	// ����б������				0x0D


uint8_t FTW[]={0x00,0x00,0xa7,0xc6};
uint8_t ASF[]={0x00,0x00,0x00,0x00};





//=====================================================================
void AD9910_IO_init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CSB_Pin|DRH_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, SCK_Pin|UPDATE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SDIO_Pin|DRC_Pin|AD9910_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, PF0_Pin|PF1_Pin|PF2_Pin|RSO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = CSB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CSB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = DRH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(DRH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = UPDATE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(UPDATE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = SDIO_Pin|DRC_Pin|AD9910_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = PF0_Pin|PF1_Pin|PF2_Pin|RSO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = PLL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PLL_GPIO_Port, &GPIO_InitStruct);

}



//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_Init(void)
//��������:AD9910ʱ�ӵ����ú͸���DAC���� �Լ�AD9910��λ
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void Init_ad9910(void)
{
	AD9910_IO_init();
	PROFILE2_L;
	PROFILE1_L;
	PROFILE0_L;
	DRCTL_L;
	DRHOLD_L;
	MAS_REST_H; 
	Delay_Us(5);  
	MAS_REST_L; 


	CS_L;
	txd_8bit(0x03);
	for (int m=0;m<4;m++)
		txd_8bit(Assist_DAC[m]); 
	CS_H;

	TxCFR();
}      
//=====================================================================

//======================����8λ���ݳ���================================
void txd_8bit(uchar txdat)
{
	uchar i,sbt;
	sbt=0x80;
	SCLK_L;
	for (i=0;i<8;i++)
	{
		SCLK_L;
		Delay_Us(1);
		if((txdat & sbt)==0) 
		{AD9910_SDIO_L;}
		else 
		{AD9910_SDIO_H;}
		
		Delay_Us(1);
		SCLK_H;
		sbt=sbt>>1;
	}
}  
//=====================================================================



//======================����32λ���ݳ���================================
void txd_32bit(uint32_t dat)																							
{
	uint8_t i ;
	uint32_t com;
	com = 0x80000000;
	SCLK_L;
	
	for(i=0; i < 32; i++)
	{
		if( (dat & com) == 0)
		{
			AD9910_SDIO_L;
		}
		else
		{
			AD9910_SDIO_H;
		}
		SCLK_H;
		com = com >> 1;
		SCLK_L;
	}
}




//=====================================================================

//======================ad9910����CFRx�����ֳ���=======================
void TxCFR(void)
{
	uchar m,k;

	CS_L;
	txd_8bit(0x00);    //����CFR1�����ֵ�ַ
	for (m=0;m<4;m++)
		txd_8bit(CFR1[m]); 
	CS_H;  
	for (k=0;k<10;k++);
	
	CS_L;
	txd_8bit(0x01);    //����CFR2�����ֵ�ַ
	for (m=0;m<4;m++)
		txd_8bit(CFR2[m]); 
	CS_H;  
	for (k=0;k<10;k++);

	CS_L;
	txd_8bit(0x02);    //����CFR3�����ֵ�ַ
	for (m=0;m<4;m++)
		txd_8bit(CFR3[m]); 
	CS_H;



	for (k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//===================ad9910����profile0�����ֳ���======================
void Txprofile(void)
{
	uchar m,k;

	CS_L;
	txd_8bit(0x0e);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//===================����Ƶƫ�֡�Ƶ���ֺͷ��ͳ���======================
void Freq_convert(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	Txprofile();
}

void Freq_convert_profile0(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x0e);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}




void Freq_convert_profile1(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x0f);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}


void Freq_convert_profile2(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x10);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}



void Freq_convert_profile3(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x11);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}



void Freq_convert_profile4(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x12);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}



void Freq_convert_profile5(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x13);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}



void Freq_convert_profile6(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x14);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}



void Freq_convert_profile7(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000 ��1G ���ڲ�ʱ���ٶȣ�
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	CS_L;
	txd_8bit(0x15);    //����profile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}

//=====================================================================

void scan8channel(void)
{
	
//		//���ո�����˳�����
//	Freq_convert_profile0(1000000);   //����Ƶ��Ϊ1M
//	Freq_convert_profile1(2000000);
//	Freq_convert_profile3(3000000);
//	Freq_convert_profile2(4000000);
//	Freq_convert_profile6(3000000);
//	Freq_convert_profile7(2000000);
//	Freq_convert_profile5(1000000);
//	Freq_convert_profile4(7000000);
	

	//000
	PROFILE2_L;
	Delay_Us(2);

	//001
	PROFILE0_H;
	Delay_Us(2);

	//011
	PROFILE1_H;
	Delay_Us(2);

	//010
	PROFILE0_L;
	Delay_Us(2);

	//110
	PROFILE2_H;
	Delay_Us(2);

	//111
	PROFILE0_H;
	Delay_Us(2);

	//101
	PROFILE1_L;
	Delay_Us(2);

	//100
	PROFILE0_L;
	Delay_Us(2);
}






//===================��������ֺͷ��ͳ���==============================
void Write_Amplitude(uint Amp)
{
	ulong Temp;
	Temp = (ulong)Amp*25.20615385;	   //������������ӷ�Ϊ�����ֽ�  25.20615385=(2^14)/650
	if(Temp > 0x3fff)
		Temp = 0x3fff;
	Temp &= 0x3fff;
	Profile_All[1]=(uchar)Temp;
	Profile_All[0]=(uchar)(Temp>>8);
	Txprofile();
}
//=====================================================================

//======================ad9910����DRG��������==========================
void Txdrg(void)
{
	uchar m,k;

	CS_L;
	txd_8bit(0x0b);    //��������б�����Ƶ�ַ0x0b
	for (m=0;m<8;m++)
		txd_8bit(drgparameter[m]); 
	CS_H;
	for(k=0;k<10;k++);
	
	CS_L;
	txd_8bit(0x0c);    //��������б�²�����ַ0x0c
	for (m=8;m<16;m++)
		txd_8bit(drgparameter[m]); 
	CS_H;
	for(k=0;k<10;k++);
	
	CS_L;
	txd_8bit(0x0d);    //��������б�����ʵ�ַ0x0d
	for (m=16;m<20;m++)
		txd_8bit(drgparameter[m]); 
	CS_H;
	for(k=0;k<10;k++);
	
	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//=====================ɨƵ���������úͷ��ͳ���========================
//���ԣ�ûɶ����
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime)
{
	ulong Temp1, Temp2, ITemp3, DTemp3, ITemp4, DTemp4;
	Temp1 = (ulong)SweepMinFre*4.294967296;
	if(SweepMaxFre > 400000000)
		SweepMaxFre = 400000000;
	Temp2 = (ulong)SweepMaxFre*4.294967296;
	if(SweepStepFre > 400000000)
		SweepStepFre = 400000000;
	ITemp3 = (ulong)SweepStepFre*4.294967296;
	DTemp3 = ITemp3;
	ITemp4 = (ulong)SweepTime/4; //1GHz/4, ��λ��ns
	if(ITemp4 > 0xffff)
		ITemp4 = 0xffff;
	DTemp4 = ITemp4;
	
	//ɨƵ������
	drgparameter[7]=(uchar)Temp1;
	drgparameter[6]=(uchar)(Temp1>>8);
	drgparameter[5]=(uchar)(Temp1>>16);
	drgparameter[4]=(uchar)(Temp1>>24);
	drgparameter[3]=(uchar)Temp2;
	drgparameter[2]=(uchar)(Temp2>>8);
	drgparameter[1]=(uchar)(Temp2>>16);
	drgparameter[0]=(uchar)(Temp2>>24);
	//Ƶ�ʲ�������λ��Hz��
	drgparameter[15]=(uchar)ITemp3;
	drgparameter[14]=(uchar)(ITemp3>>8);
	drgparameter[13]=(uchar)(ITemp3>>16);
	drgparameter[12]=(uchar)(ITemp3>>24);
	drgparameter[11]=(uchar)DTemp3;
	drgparameter[10]=(uchar)(DTemp3>>8);
	drgparameter[9]=(uchar)(DTemp3>>16);
	drgparameter[8]=(uchar)(DTemp3>>24);
	//����ʱ��������λ��us��
	drgparameter[19]=(uchar)ITemp4;
	drgparameter[18]=(uchar)(ITemp4>>8);
	drgparameter[17]=(uchar)DTemp4;
	drgparameter[16]=(uchar)(DTemp4>>8);
	//����DRG����
	Txdrg();
}
//=====================================================================

//=================ad9910����ramprofile0�����ֳ���=====================
void Txramprofile(void)
{
	uchar m,k;

	CS_L;
	txd_8bit(0x0e);    //����ramprofile0�����ֵ�ַ
	for (m=0;m<8;m++)
		txd_8bit(ramprofile0[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//=======================ad9910����ramdata����=========================
void Txramdata(void)
{
	uint m,k;

	CS_L;
	txd_8bit(0x16);    //����ram�����ֵ�ַ
	for (m=0; m<4096; m++)
		txd_8bit(ramdata[m]); 
	CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//=======================�����������úͷ��ͳ���========================
//���ã��ò��˵�
void Square_wave(uint Sample_interval)//����
{
	ulong Temp;
	Temp = Sample_interval/4; //1GHz/4, ���������Χ��4*(1~65536)ns
	if(Temp > 0xffff)
		Temp = 0xffff;
	ramprofile0[7] = 0x24;
	ramprofile0[6] = 0x00;
	ramprofile0[5] = 0x00;
	ramprofile0[4] = 0xc0;
	ramprofile0[3] = 0x0f;
	ramprofile0[2] = (uchar)Temp;
	ramprofile0[1] = (uchar)(Temp>>8);
	ramprofile0[0] = 0x00;
	Txramprofile();

	Txramdata();	
 }
//=====================================================================


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_DRG_Fre_Init(void)
//��������:AD9910������б��ģʽDRG��ʼ��------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Fre_Init(void)
{
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};	// ʹ��AD9910��Sinc�˲�                             				
	uint8_t CFR2[]={0x00,0x48,0x08,0x20};	// SYNC_CLKʹ�ܣ�����б��ʹ��	  CFR2[21:20]= 00   ѡ����Ʋ���ΪƵ��
	int j;
	
	CS_L;
	txd_8bit(0x00);				// ��CFR1д�����ַ0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	
	CS_L;
	txd_8bit(0x01);				// ��CFR2д�����ַ0x01
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;					// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate)
//��������:AD9910��DRG����------------------Ƶ��
//��ڲ���:		upper_limit				 ����Ƶ��					 1Hz---450M
//						lower_limit		����Ƶ��					1Hz---450M(����Ƶ��Ҫ��������Ƶ��)
//						dec_step		Ƶ�ʼӲ���					1Hz---450M					
//						inc_step		Ƶ�ʼ�����					1Hz---450M
//						neg_rate		Ƶ�ʼӵ�����(ʱ��)	0x0000----0xffff   250Ϊ1us�ļĴ���ֵ��250000Ϊ1ms�ļĴ���ֵ,���Ҳ����200us������			  
//						pos_rate		Ƶ�ʼ�������(ʱ��)	0x0000----0xffff   //�˴���û�м���ģ�ʵ�����Ǽ��ʱ�����ϵͳʱ��Ƶ���ٳ�����
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate)
{
	uint32_t upper_temp , lower_temp ,dec_temp, inc_temp;
	uint16_t neg_rate_temp , pos_rate_temp;
	int i;
	upper_temp		=	(uint32_t)upper_limit*4.294967296;	// Ƶ����ת��		4.294967296=(2^32)/1000000000
	lower_temp		=	(uint32_t)lower_limit*4.294967296;
	dec_temp  		=	(uint32_t)  dec_step*4.294967296;
	inc_temp  		=	(uint32_t)  inc_step*4.294967296;
	neg_rate_temp	=  	neg_rate;							// ʱ��
	pos_rate_temp	=  	pos_rate;
	
	DRL[7]=(uint8_t) lower_temp;		//����������Ƶ�ʡ�Ƶ�ʼӼ�������Ƶ�ʼӼ�����д�����飬��д����Ӧ�ļĴ���
	DRL[6]=(uint8_t)(lower_temp>>8);
	DRL[5]=(uint8_t)(lower_temp>>16);
	DRL[4]=(uint8_t)(lower_temp>>24);
	DRL[3]=(uint8_t) upper_temp;
	DRL[2]=(uint8_t)(upper_temp>>8);
	DRL[1]=(uint8_t)(upper_temp>>16);
	DRL[0]=(uint8_t)(upper_temp>>24);
	
	DRS[7]=(uint8_t) inc_temp;
	DRS[6]=(uint8_t)(inc_temp>>8);
	DRS[5]=(uint8_t)(inc_temp>>16);
	DRS[4]=(uint8_t)(inc_temp>>24);
	DRS[3]=(uint8_t) dec_temp;
	DRS[2]=(uint8_t)(dec_temp>>8);
	DRS[1]=(uint8_t)(dec_temp>>16);
	DRS[0]=(uint8_t)(dec_temp>>24);
	
	DRR[3]=(uint8_t) pos_rate_temp;
	DRR[2]=(uint8_t)(pos_rate_temp>>8);
	DRR[1]=(uint8_t) neg_rate_temp;
	DRR[0]=(uint8_t)(neg_rate_temp>>8);
	
	CS_L;												
	txd_8bit(0x0B);			// ������б����ֵ���� 0x0B
	for(i=0;i<8;i++)
	{
		txd_8bit(DRL[i]);																								
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;												
	txd_8bit(0x0C);			// ������б�²������� 0x0C
	for(i=0;i<8;i++)
	{
		txd_8bit(DRS[i]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;							
	txd_8bit(0x0D);			// ������б�����ʴ��� 0x0D
	for(i=0;i<4;i++)
	{
		txd_8bit(DRR[i]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;				// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;	
}


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_Init(void)
//��������:��CFR1��CFR2�ָ�Ĭ��ֵ
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_Init(void)
{
	int j;
	
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};
	uint8_t CFR2[]={0x01,0x40,0x08,0x20};
	uint8_t PRO[] = {0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	CS_L;
	txd_8bit(0x00);														// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x01);														// ��CFR2д����Ĵ���0x01
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x0e);														// ��RAM Profile0д����Ĵ���0x0e
	for(j=0;j<8;j++)
	{
		txd_8bit(PRO[j]);
	}
	CS_H;	
	Delay_Us(1);
	

	
	UP_DAT_L;															// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}
//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_ZB_Fre_Init(void)
//��������:����RAMģʽ�е��ز���Ƶ�ʵĳ�ʼ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Init(void)
{
	int j;
	
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};	// ����AD9910��Sinc�˲�����
	uint8_t CFR2[]={0x00,0x41,0x08,0x20};	// ��ȡ��Ч��FTW�Ĵ���������FTW��д�ز�Ƶ��ʱ�õ�
	
	CS_L;
	txd_8bit(0x00);			// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x01);			// ��CFR2д����Ĵ���0x01
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	
	UP_DAT_L;				// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_ZB_Fre_Set(uint32_t Freq)
//��������:����RAMģʽ�е��ز���Ƶ��
//��ڲ���:Freq--------------------�ز�Ƶ��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Set(uint32_t Freq)
{
		uint8_t FTW[]={0x00,0x00,0xa7,0xc6};
		int j;
		uint32_t Temp;  

	  Temp=(uint32_t)Freq*4.294967296;// ������Ƶ��ת��Ϊ��Ӧ��FTWֵ  4.294967296=(2^32)/1000000000
		
	  FTW[3]=(uint8_t)Temp;
	  FTW[2]=(uint8_t)(Temp>>8);
	  FTW[1]=(uint8_t)(Temp>>16);
	  FTW[0]=(uint8_t)(Temp>>24);
		
		CS_L;					// CSN��0			��Ƭѡ
		txd_8bit(0x07);			// ѡ��0x07��ַ           	��Ƶ��д��Ĵ���
		for(j=0;j<4;j++)
		{
			txd_8bit(FTW[j]);
		}
		CS_H;					// CSN��1			��Ƭѡ
		Delay_Us(1);
		
		
		UP_DAT_L;				// ����AD9910���
		Delay_Us(1);
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void FSK_RAM_Write(void)
//��������:������д��1024*32��RAM��---------------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void FSK_RAM_Write(void)
{
	int j;
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// ����AD9910��Sinc�˲�
	uint8_t CFR2[]={0x00,0x40,0x08,0x20};
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};// ����RAM����ʼ����ֹ��ַ����ַ������
	
	
	CS_L;
	txd_8bit(0x00);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x01);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;																										// ��RAM����ʼ����ֹ��ַ����ַ������д����Ӧ�ļĴ���  0x0e
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// ����һ��AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	CS_L;								
	txd_8bit(0x16);														
	for(j=0; j<1024; j++)
	{	
		txd_32bit(ramdata[j]);																				// ��Ƶ��RAM������д��0x16�Ĵ���
	}
		CS_H;
	
		UP_DAT_L;																									// �ڸ���һ��AD9910
		Delay_Us(1);
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void FM_RAM_Write(void)
//��������:������д��1024*32��RAM��---------------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void FM_RAM_Write(uint32_t modin,uint32_t deepth, uint32_t carrer)
{
	int j;
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// ����AD9910��Sinc�˲�
	uint8_t CFR2[]={0x00,0x40,0x08,0x20};
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xf9,0xC0,0x00,0x00,0x04};// ����RAM����ʼ����ֹ��ַ����ַ������
	uint16_t fre_temp;
	
	float ramdataraw = 0.0f;
	if(modin <= 250000)
	{
		fre_temp = (uint16_t)250000/modin;
	}
	else
	{
		fre_temp = 0;
	}
	RAM_PRO0[1] = (fre_temp>>8);
	RAM_PRO0[2] = (fre_temp);

	CS_L;
	txd_8bit(0x00);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x01);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;																										// ��RAM����ʼ����ֹ��ַ����ַ������д����Ӧ�ļĴ���  0x0e
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// ����һ��AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	CS_L;								
	txd_8bit(0x16);														
	for(j=0; j<1000; j++)
	{	
		ramdataraw = (cos(j*PI/500)*modin*deepth+carrer*2*PI)/2/PI*4.294967296;
		txd_32bit((uint32_t)ramdataraw);																				// ��Ƶ��RAM������д��0x16�Ĵ���
	}
	CS_H;
	
	UP_DAT_L;																									// �ڸ���һ��AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_ramdata_W(void)
//��������:������д��1024*32��RAM��---------------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_ramdata_W(void)
{
	int j;
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// ����AD9910��Sinc�˲�
	uint8_t CFR2[]={0x00,0x40,0x08,0x20};
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};// ����RAM����ʼ����ֹ��ַ����ַ������
	
	
	CS_L;
	txd_8bit(0x00);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x01);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;																										// ��RAM����ʼ����ֹ��ַ����ַ������д����Ӧ�ļĴ���  0x0e
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// ����һ��AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	CS_L;								
	txd_8bit(0x16);														
	for(j=0; j<1024; j++)
	{	
		txd_32bit(ramdata[j]);																				// ��Ƶ��RAM������д��0x16�Ĵ���
	}
		CS_H;
	
		UP_DAT_L;																									// �ڸ���һ��AD9910
		Delay_Us(1);
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
}


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_AMP_W(void)
//��������:������д��1024*32��RAM��-------------------------����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_AMP_W(void)
{
	int j;

	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// ����AD9910��Sinc�˲�
	uint8_t RAM_PRO0[]={0x00,0x00,0xff,0xff,0xC0,0x00,0x00,0x00};// ����RAM����ʼ����ֹ��ַ����ַ������

	CS_L;
	txd_8bit(0x00);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);																				// ��RAM����ʼ����ֹ��ַ����ַ������д����Ӧ�ļĴ���  0x0e
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x16);
	for(j=0; j<1024; j++)
	{	
		txd_32bit(ramdata[j]);																				// ������RAM������д��Ĵ���0x16	
	}
		CS_H;
	
		UP_DAT_L;
		Delay_Us(1);																									// ����AD9910
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
	 
}


//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_CON_RECIR_Fre_R(void)
//��������:����ѭ��ģʽ�Ļط�-------------------------Ƶ��
//														
//��ڲ���:��
//���ڲ���:��
//��Ҫ����ʹ�����
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																								// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��00�� �ط�Ƶ�� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�
	
	//uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x04};												//	�ӵ�ַ0�طŵ�1023					// ����˫��б��ģʽRAM_PROx[7]=0x04
	
	CS_L;
	txd_8bit(0x00);																																// ��CFR1д�����ַ0x00		
	for(j=0;j<4;j++)                                                                
	{                                                                               
		txd_8bit(CFR1[j]);                                                          
	}                                                                               
	CS_H;	                                                                
	Delay_Us(1);                                                                  
	                                                                                
//	CS_L;                                                                 
//	txd_8bit(0x0e);																                                // ��RAM_RPOxд�����ַ		
//	for(j=0;j<8;j++)                                                                
//	{                                                                               
//		txd_8bit(RAM_PRO0[j]);                                                      
//	}                                                                               
//	CS_H;	                                                                
//	Delay_Us(1);  

	
	UP_DAT_L;                                                                 
	Delay_Us(1);                                                                  // ����AD9910
	UP_DAT_H;                                                                 
	Delay_Us(1);                                                                  
	UP_DAT_L;                                                                 
	Delay_Us(1);                                                                      
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_CON_RECIR_AMP_R(void)
//��������:����ѭ��ģʽ�Ļط�-------------------------����
//														
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xE0,0x40,0x00,0x00};																								// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��10�� �طŷ��� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�
	
	uint8_t RAM_PRO0[]={0x00,0x00,0x01,0xff,0xc0,0x00,0x00,0x04};												//	�ӵ�ַ0�طŵ�1023					// ����˫��б��ģʽRAM_PROx[7]=0x04
	
	CS_L;
	txd_8bit(0x00);																																// ��CFR1д�����ַ0x00															
	for(j=0;j<4;j++)                                                                
	{                                                                               
		txd_8bit(CFR1[j]);                                                          
	}                                                                               
	CS_H;	                                                                
	Delay_Us(1);                                                                  
	                                                                                
	CS_L;                                                                 
	txd_8bit(0x0e);																                                // ��RAM_RPOxд�����ַ		
	for(j=0;j<8;j++)                                                                
	{                                                                               
		txd_8bit(RAM_PRO0[j]);                                                      
	}                                                                               
	CS_H;	                                                                
	Delay_Us(1); 
	
	UP_DAT_L;                                                                 
	Delay_Us(1);                                                                  
	UP_DAT_H;                                                                 
	Delay_Us(1);                                                                  // ����AD9910
	UP_DAT_L;
	Delay_Us(1);
}

//------------------------------------------------------------------------------------
//��������:void Freq_convert(uint32_t Freq)	
//��������:AD9910д��ʼƵ��
//��ڲ���:Freq      дƵ��   Ƶ��С��450M														
//���ڲ���:��
//------------------------------------------------------------------------------------
void Freq_convert2(uint32_t Freq)
{
	uint32_t Temp;            
	Temp=(uint32_t)Freq*4.294967296;	   //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/1000000000
		
	FTW[3]=(uint8_t)Temp;
	FTW[2]=(uint8_t)(Temp>>8);
	FTW[1]=(uint8_t)(Temp>>16);
	FTW[0]=(uint8_t)(Temp>>24);
}
//------------------------------------------------------------------------------------
//��������:void Amp_convert(uint32_t Amp)	
//��������:AD9910д��ʼ����
//��ڲ���:Amp      д����  														
//���ڲ���:��
//------------------------------------------------------------------------------------
void Amp_convert2(uint32_t Amp)
{
		
	ASF[3]=(uint8_t)Amp;
	ASF[2]=(uint8_t)(Amp>>8);

}
//------------------------------------------------------------------------------------
//��������:void AD9910_Init_Sin(void)
//��������:AD9910ʱ�ӵ����ú͸���DAC���� �Լ�AD9910�������ҳ�ʼ��
//��ڲ���:��
//���ڲ���:��
//------------------------------------------------------------------------------------
void AD9910_Init_Sin(int gain)
{
	int j;
	PROFILE0_L;														// ѡ�� Profile0
	PROFILE1_L;
	PROFILE2_L;
	DRHOLD_L;
	DRCTL_L;
	MAS_REST_H;	
	Delay_Us(1);													// ��λAD9910
	MAS_REST_L;
	
	CS_L;														// CSN��0			��Ƭѡ
	txd_8bit(0x00);													// ѡ��0x00��ַ            CFR1�Ĵ���д������
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	CS_L;														// CSN��1			��Ƭѡ
	
	CS_L;														// CSN��0			��Ƭѡ
	
	txd_8bit(0x01);													// ѡ��0x01��ַ            CFR2�Ĵ���д������
	CFR2[3] += gain;
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	CS_H;	
	Delay_Us(1);	
	CFR2[3] = 0x30;
	CS_L;														// CSN��0			��Ƭѡ
	
	txd_8bit(0x02);													// ѡ��0x02��ַ            CFR3�Ĵ���д������
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR3[j]);	
	}
	CS_H;														// CSN��1			��Ƭѡ
	Delay_Us(1);
	
	CS_L;														// CSN��0			��Ƭѡ
	txd_8bit(0x03);													// ѡ��0x03��ַ            ����DAC�Ĵ���д������
	for(j=0;j<4;j++)
	{
		txd_8bit(Assist_DAC[j]);
	}
	CS_H;														// CSN��1			��Ƭѡ
	Delay_Us(1);
	
	CS_L;														// CSN��0			��Ƭѡ
	txd_8bit(0x07);													// ѡ��0x07��ַ           	����ʼƵ��д��Ĵ���
	for(j=0;j<4;j++)
	{
		txd_8bit(FTW[j]);
	}
	CS_H;														// CSN��1			��Ƭѡ
	Delay_Us(1);
	
	UP_DAT_L;
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_WAVE_RAM_AMP_W(int mode)
//��������:������д��1024*32��RAM��-------------------------����
//��ڲ���:��
//���ڲ���:��
//�������ԭ�������������ͬ����ķ������ݵģ������Ұ�����ɾ���ˣ�����ʵ��������ĺ���������
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_WAVE_RAM_AMP_W(int mode)
{
	int j;

	uint8_t CFR1[]={0x60,0x40,0x00,0x00};		// ����AD9910��Sinc�˲�
	uint8_t RAM_PRO0[]={0x00,0x00,0x01,0xff,0xC0,0x00,0x00,0x00};	// ����RAM����ʼ����ֹ��ַ����ַ������

	CS_L;
	txd_8bit(0x00);																									// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);	// ��RAM����ʼ����ֹ��ַ����ַ������д����Ӧ�ļĴ���  0x0e
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x16);
	for(j=0; j<1024; j++)
	{	
		if(mode == 1)
		{
			txd_32bit(ramdata[j]);																				// ������RAM������д��Ĵ���0x16	
		}else if(mode == 2)
		{
			txd_32bit(ramdata[j]);		//�����ǲ�������д��ram
		}else if(mode == 3)
		{
			txd_32bit(ramdata[j]);	//������������д��ram
		}
	}
		CS_H;
	
		UP_DAT_L;
		Delay_Us(1);																									// ����AD9910
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
	 
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_DIR_Fre_R(void)
//��������:ֱ��ת��ģʽ�Ļط�-------------------------Ƶ��
//��ڲ���:��
//���ڲ���:��
//Ŀǰ��û�뵽������ܸ���ôʹ�ã����Բ�������
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																				// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��00�� �ط�Ƶ�� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�

	
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x00};								//	�ӵ�ַ0����ַ23
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x00};								//				24~273   								ֱ��ת��ģʽRAM_PROx[7]=0x00
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x00};								//      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x00};								//				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x00};								//				774~1023								��Ϥ�˿����Լ�����
//uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
	
	
	CS_L;
	txd_8bit(0x00);																												// ��CFR1д������Ӧ�ļĴ���														
	for(j=0; j<4; j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	

	
	CS_L;
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);																							// ��PRO0~PRO4д����Ӧ�ļĴ���
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x0F);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x10);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO2[j]);
	}
	CS_H;	
	Delay_Us(1);

	CS_L;
	txd_8bit(0x11);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO3[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x12);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO4[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																														// ����AD9910���
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_DIR_AMP_R(void)
//��������:ֱ��ת��ģʽ�Ļط�-------------------------����
//��ڲ���:��
//���ڲ���:��
//Ŀǰ��û�뵽������ܸ���ôʹ�ã����Բ�������
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xC0,0x40,0x00,0x00};																					// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��10�� �طŷ��� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�

	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x06,0x00,0x00,0x00,0x00};									//	�ӵ�ַ0����ַ23
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x00};                  //				24~273   									ֱ��ת��ģʽRAM_PROx[7]=0x00				
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x00};                  //      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x00};                  //				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x00};                  //				774~1023								��Ϥ�˿����Լ�����
//uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
	
	
	CS_L;	
	txd_8bit(0x00);																
	for(j=0; j<4; j++)																													// ��CFR1д������Ӧ�ļĴ���						
	{                                                                           
		txd_8bit(CFR1[j]);                                                      
	}                                                                           
	CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
		CS_L;                                                           
	txd_8bit(0x0e);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO0[j]);                                                  
	}                                                                           // ��PRO0~PRO4д����Ӧ�ļĴ���
	CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	CS_L;                                                             
	txd_8bit(0x0F);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO1[j]);                                                  
	}                                                                           
	CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	CS_L;                                                             
	txd_8bit(0x10);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO2[j]);                                                  
	}                                                                           
	CS_H;	                                                            
	Delay_Us(1);                                                              
                                                                              
	CS_L;                                                             
	txd_8bit(0x11);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO3[j]);                                                  
	}                                                                           
	CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	CS_L;                                                             
	txd_8bit(0x12);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO4[j]);                                                  
	}                                                                           
	CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	UP_DAT_L;                                                             
	Delay_Us(1);                                                              	// ����AD9910���
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}
//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_ONE_Fre_R(void)
//��������:��б��ģʽ�Ļط�-------------------------Ƶ��
//														ONE �������ⲿ����PRO2~PRO0����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																							// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��00�� �ط�Ƶ�� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�
	
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x01};											//	�ӵ�ַ0�طŵ�1023			����Ϥ����Щ�طſ����Լ����ã�
																																								//��б��ģʽRAM_PROx[7]=0x01
									
//	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x01};
//	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};																									
//	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};
//	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};
//	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};
//	uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};
//	uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};
//	uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};
	
	CS_L;
	txd_8bit(0x00);																															// ��CFR1д����Ĵ���0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x0e);																															// ��RAM_PRO0д����Ĵ���0x0e														
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	CS_H;	
	Delay_Us(1);
	
//	CS_L;																															
//	txd_8bit(0x0f);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO1[j]);
//	}
//	CS_H;	
//	Delay_Us(1);
//	
//	CS_L;
//	txd_8bit(0x10);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO2[j]);
//	}
//	CS_H;	
//	Delay_Us(1);

//	CS_L;
//	txd_8bit(0x11);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO3[j]);
//	}
//	CS_H;	
//	Delay_Us(1);
//	
//	CS_L;
//	txd_8bit(0x12);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO4[j]);
//	}
//	CS_H;	
//	Delay_Us(1);
	
	UP_DAT_L;																																// ʹ��AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_ONE_AMP_R(void)
//��������:��б��ģʽ�Ļط�-------------------------����
//ONE �������ⲿ����PRO2~PRO0����
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xC0,0x40,0x00,0x00};																							// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��10�� �طŷ��� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�
	
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x01};											//	�ӵ�ַ0�طŵ�1023			����Ϥ����Щ�طſ����Լ����ã�
																																								//��б��ģʽRAM_PROx[7]=0x01
//	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};                    
//	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};                    
//	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};                    
//	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};                    
//	uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//	uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//	uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
	                                                                              
	CS_L;                                                               
	txd_8bit(0x00);																									            // ��CFR1д����Ĵ���0x00 
	for(j=0;j<4;j++)                                                              
	{                                                                             
		txd_8bit(CFR1[j]);                                                        
	}                                                                             
	CS_H;	                                                              
	Delay_Us(1);                                                                
	                                                                              
	CS_L;                                                               
	txd_8bit(0x0e);																                              // ��RAM_PRO0д����Ĵ���0x0e														
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	CS_H;	
	Delay_Us(1);
	
//	CS_L;
//	txd_8bit(0x0f);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO1[j]);
//	}
//	CS_H;	
//	Delay_Us(1);
//	
//	CS_L;
//	txd_8bit(0x10);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO2[j]);
//	}
//	CS_H;	
//	Delay_Us(1);

//	CS_L;
//	txd_8bit(0x11);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO3[j]);
//	}
//	CS_H;	
//	Delay_Us(1);
//	
//	CS_L;
//	txd_8bit(0x12);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO4[j]);
//	}
//	CS_H;	
//	Delay_Us(1);
	
	UP_DAT_L;																																// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_TWO_Fre_R(void)
//��������:��б��ģʽ�Ļط�-------------------------Ƶ��
//TWO �������ڲ�����							����λΪ��CFR1[20:17]�� �ο������ֲ�
//��ڲ���:��
//���ڲ���:��
//�������Ŀǰ����Ϊ��ȫû��Ҫʹ�ã����Բ��ù�
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																						// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��00�� �ط�Ƶ�� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�
																																							// ѡ����Ӧ�Ŀ���λ����ѡ�����0100   ͻ�� ִ��Profile 0��Profile 4��Ȼ����ֹ 
																																							// ����λΪ��CFR1[20:17]�� �ο������ֲ�
																			
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x01};										//	�ӵ�ַ0����ַ23
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};                    //				24~273   												//��б��ģʽRAM_PROx[7]=0x01
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};                    //      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};                    //				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};                    //				774~1023								��Ϥ�˿����Լ�����
//uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
	                                                                            
	                                                                            
	CS_L;                                                             
	txd_8bit(0x00);																                            
	for(j=0;j<4;j++)                                                            	// ��CFR1д������Ӧ�ļĴ���						
	{                                                                             
		txd_8bit(CFR1[j]);                                                        
	}                                                                             
	CS_H;	                                                              
	Delay_Us(1);                                                                
	                                                                              
	CS_L;                                                               
	txd_8bit(0x0e);																                              
	for(j=0;j<8;j++)                                                              
	{                                                                             
		txd_8bit(RAM_PRO0[j]);                                                    
	}                                                                             // ��PRO0~PRO4д����Ӧ�ļĴ���
	CS_H;	                                                              
	Delay_Us(1);                                                                
	                                                                              
	CS_L;                                                               
	txd_8bit(0x0f);																                              
	for(j=0;j<8;j++)                                                              
	{                                                                             
		txd_8bit(RAM_PRO1[j]);                                                    
	}                                                                             
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x10);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO2[j]);
	}
	CS_H;	
	Delay_Us(1);

	CS_L;
	txd_8bit(0x11);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO3[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x12);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO4[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																																// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//��������:void AD9910_RAM_RAMP_UP_TWO_AMP_R(void)
//��������:��б��ģʽ�Ļط�-------------------------����
//�������Ŀǰ����Ϊ��ȫû��Ҫʹ�ã����Բ��ù�												TWO �������ڲ�����							����λΪ��CFR1[20:17]�� �ο������ֲ�
//��ڲ���:��
//���ڲ���:��
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xC0,0x40,0x00,0x00};																							// ʹ��RAMģʽ  ���ط�Ŀ��λ��Ϊ��10�� �طŷ��� ��ע��ʹ�ܺ�ͱ����RAM�Ĵ����ˣ�

	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x01};											//	�ӵ�ַ0����ַ23				
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};                      //				24~273   												//��б��ģʽRAM_PROx[7]=0x01
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};                      //      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};                      //				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};                      //				774~1023								��Ϥ�˿����Լ�����
	uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                      
	uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                      
	uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                      
	                                                                              
	CS_L;                                                               
	txd_8bit(0x00);																                              
	for(j=0;j<4;j++)                                                              
	{                                                                             	// ��CFR1д������Ӧ�ļĴ���						
		txd_8bit(CFR1[j]);                                                          
	}                                                                               
	CS_H;	                                                                
	Delay_Us(1);                                                                  
	                                                                                
	CS_L;                                                                 
	txd_8bit(0x0e);																                                
	for(j=0;j<8;j++)                                                                
	{                                                                               
		txd_8bit(RAM_PRO0[j]);                                                      
	}                                                                               
	CS_H;	                                                                // ��PRO0~PRO4д����Ӧ�ļĴ���
	Delay_Us(1);                                                                  
	                                                                                
	CS_L;                                                                 
	txd_8bit(0x0f);																                                
	for(j=0;j<8;j++)                                                                
	{
		txd_8bit(RAM_PRO1[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x10);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO2[j]);
	}
	CS_H;	
	Delay_Us(1);

	CS_L;
	txd_8bit(0x11);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO3[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	CS_L;
	txd_8bit(0x12);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO4[j]);
	}
	CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																																	// ����AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

