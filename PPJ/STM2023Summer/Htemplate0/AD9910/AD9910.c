#include "AD9910.h"

uint8_t CFR1[]={0x00,0x40,0x00,0x00}; // 开启AD9910反Sinc滤波器      												//CFR1控制字
uint8_t CFR2[]={0x00,0x00,0x00,0x00}; // 并行端口使能 其中当CFR2[3]=0x30时，并行口的频率位设置频率*2^0  , 当 CFR2[3]=0x33时，并行口的频率位设置频率*2^3;      												//CFR2控制字
uint8_t CFR3[]={0x05,0x0F,0x41,0x32};// CFR3控制功能寄存器3   时钟倍频25倍  基础时钟45M  

uint8_t Assist_DAC[]={0x00,0x00,0x00,0x7F};	// 辅助DAC输出  默认0x7f

//uint8_t Profile_All[8];			// Profile的暂存位置  //01振幅控制 23相位控制 4567频率调谐字
uint8_t Profile_All[]={0x3f,0xff,0x00,0x00,0x25,0x09,0x7b,0x42};//profile1控制字 
                  


uint8_t drgparameter[20]={0x00}; //DRG参数
uint8_t ramprofile0[8] = {0x00}; //ramprofile0控制字

uint32_t ramdata[4096];

uint8_t DRL[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};// 数字斜坡限值				0x0B
uint8_t DRS[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};// 数字斜坡步长				0x0C
uint8_t DRR[]={0x00,0x00,0x00,0x00};	// 数字斜坡速率				0x0D


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
//函数名称:void AD9910_Init(void)
//函数功能:AD9910时钟的设置和辅助DAC设置 以及AD9910复位
//入口参数:无
//出口参数:无
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


	AD9910_CS_L;
	txd_8bit(0x03);
	for (int m=0;m<4;m++)
		txd_8bit(Assist_DAC[m]); 
	AD9910_CS_H;

	TxCFR();
}      
//=====================================================================

//======================发送8位数据程序================================
void txd_8bit(uchar txdat)
{
	uchar i,sbt;
	sbt=0x80;
	AD9910_SCLK_L;
	for (i=0;i<8;i++)
	{
		AD9910_SCLK_L;
		Delay_Us(1);
		if((txdat & sbt)==0) 
		{AD9910_SDIO_L;}
		else 
		{AD9910_SDIO_H;}
		
		Delay_Us(1);
		AD9910_SCLK_H;
		sbt=sbt>>1;
	}
}  
//=====================================================================



//======================发送32位数据程序================================
void txd_32bit(uint32_t dat)																							
{
	uint8_t i ;
	uint32_t com;
	com = 0x80000000;
	AD9910_SCLK_L;
	
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
		AD9910_SCLK_H;
		com = com >> 1;
		AD9910_SCLK_L;
	}
}




//=====================================================================

//======================ad9910发送CFRx控制字程序=======================
void TxCFR(void)
{
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x00);    //发送CFR1控制字地址
	for (m=0;m<4;m++)
		txd_8bit(CFR1[m]); 
	AD9910_CS_H;  
	for (k=0;k<10;k++);
	
	AD9910_CS_L;
	txd_8bit(0x01);    //发送CFR2控制字地址
	for (m=0;m<4;m++)
		txd_8bit(CFR2[m]); 
	AD9910_CS_H;  
	for (k=0;k<10;k++);

	AD9910_CS_L;
	txd_8bit(0x02);    //发送CFR3控制字地址
	for (m=0;m<4;m++)
		txd_8bit(CFR3[m]); 
	AD9910_CS_H;



	for (k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//===================ad9910发送profile0控制字程序======================
void Txprofile(void)
{
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x0e);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//===================计算频偏字、频率字和发送程序======================
void Freq_convert(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x0e);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x0f);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x10);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x11);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x12);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x13);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x14);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
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
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	Profile_All[7]=(uchar)Temp;
	Profile_All[6]=(uchar)(Temp>>8);
	Profile_All[5]=(uchar)(Temp>>16);
	Profile_All[4]=(uchar)(Temp>>24);
	
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x15);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(Profile_All[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
	
}

//=====================================================================

void scan8channel(void)
{
	
//		//按照格雷码顺序编码
//	Freq_convert_profile0(1000000);   //设置频率为1M
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






//===================计算幅度字和发送程序==============================
void Write_Amplitude(uint Amp)
{
	ulong Temp;
	Temp = (ulong)Amp*25.20615385;	   //将输入幅度因子分为两个字节  25.20615385=(2^14)/650
	if(Temp > 0x3fff)
		Temp = 0x3fff;
	Temp &= 0x3fff;
	Profile_All[1]=(uchar)Temp;
	Profile_All[0]=(uchar)(Temp>>8);
	Txprofile();
}
//=====================================================================

//======================ad9910发送DRG参数程序==========================
void Txdrg(void)
{
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x0b);    //发送数字斜坡限制地址0x0b
	for (m=0;m<8;m++)
		txd_8bit(drgparameter[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);
	
	AD9910_CS_L;
	txd_8bit(0x0c);    //发送数字斜坡步长地址0x0c
	for (m=8;m<16;m++)
		txd_8bit(drgparameter[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);
	
	AD9910_CS_L;
	txd_8bit(0x0d);    //发送数字斜坡速率地址0x0d
	for (m=16;m<20;m++)
		txd_8bit(drgparameter[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);
	
	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//=====================扫频波参数设置和发送程序========================
//可以，没啥问题
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
	ITemp4 = (ulong)SweepTime/4; //1GHz/4, 单位：ns
	if(ITemp4 > 0xffff)
		ITemp4 = 0xffff;
	DTemp4 = ITemp4;
	
	//扫频上下限
	drgparameter[7]=(uchar)Temp1;
	drgparameter[6]=(uchar)(Temp1>>8);
	drgparameter[5]=(uchar)(Temp1>>16);
	drgparameter[4]=(uchar)(Temp1>>24);
	drgparameter[3]=(uchar)Temp2;
	drgparameter[2]=(uchar)(Temp2>>8);
	drgparameter[1]=(uchar)(Temp2>>16);
	drgparameter[0]=(uchar)(Temp2>>24);
	//频率步进（单位：Hz）
	drgparameter[15]=(uchar)ITemp3;
	drgparameter[14]=(uchar)(ITemp3>>8);
	drgparameter[13]=(uchar)(ITemp3>>16);
	drgparameter[12]=(uchar)(ITemp3>>24);
	drgparameter[11]=(uchar)DTemp3;
	drgparameter[10]=(uchar)(DTemp3>>8);
	drgparameter[9]=(uchar)(DTemp3>>16);
	drgparameter[8]=(uchar)(DTemp3>>24);
	//步进时间间隔（单位：us）
	drgparameter[19]=(uchar)ITemp4;
	drgparameter[18]=(uchar)(ITemp4>>8);
	drgparameter[17]=(uchar)DTemp4;
	drgparameter[16]=(uchar)(DTemp4>>8);
	//发送DRG参数
	Txdrg();
}
//=====================================================================

//=================ad9910发送ramprofile0控制字程序=====================
void Txramprofile(void)
{
	uchar m,k;

	AD9910_CS_L;
	txd_8bit(0x0e);    //发送ramprofile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(ramprofile0[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//=======================ad9910发送ramdata程序=========================
void Txramdata(void)
{
	uint m,k;

	AD9910_CS_L;
	txd_8bit(0x16);    //发送ram控制字地址
	for (m=0; m<4096; m++)
		txd_8bit(ramdata[m]); 
	AD9910_CS_H;
	for(k=0;k<10;k++);

	UP_DAT_H;
	for(k=0;k<10;k++);
	UP_DAT_L;
	HAL_Delay(1);
}         
//=====================================================================

//=======================方波参数设置和发送程序========================
//别用，用不了的
void Square_wave(uint Sample_interval)//方波
{
	ulong Temp;
	Temp = Sample_interval/4; //1GHz/4, 采样间隔范围：4*(1~65536)ns
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
//函数名称:void AD9910_DRG_Fre_Init(void)
//函数功能:AD9910的数字斜坡模式DRG初始化------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Fre_Init(void)
{
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};	// 使能AD9910反Sinc滤波                             				
	uint8_t CFR2[]={0x00,0x48,0x08,0x20};	// SYNC_CLK使能，数字斜坡使能	  CFR2[21:20]= 00   选择控制参数为频率
	int j;
	
	AD9910_CS_L;
	txd_8bit(0x00);				// 将CFR1写入其地址0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	
	AD9910_CS_L;
	txd_8bit(0x01);				// 将CFR2写入其地址0x01
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;					// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate)
//函数功能:AD9910的DRG设置------------------频率
//入口参数:		upper_limit				 上限频率					 1Hz---450M
//						lower_limit		下限频率					1Hz---450M(上限频率要大于下限频率)
//						dec_step		频率加步进					1Hz---450M					
//						inc_step		频率减步进					1Hz---450M
//						neg_rate		频率加的速率(时间)	0x0000----0xffff   250为1us的寄存器值，250000为1ms的寄存器值,最大也就是200us的样子			  
//						pos_rate		频率减的速率(时间)	0x0000----0xffff   //此处是没有计算的，实际上是间隔时间乘以系统时钟频率再除以四
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_DRG_Freq_set(uint32_t upper_limit , uint32_t lower_limit ,uint32_t dec_step , uint32_t inc_step , uint16_t neg_rate ,uint16_t pos_rate)
{
	uint32_t upper_temp , lower_temp ,dec_temp, inc_temp;
	uint16_t neg_rate_temp , pos_rate_temp;
	int i;
	upper_temp		=	(uint32_t)upper_limit*4.294967296;	// 频率字转换		4.294967296=(2^32)/1000000000
	lower_temp		=	(uint32_t)lower_limit*4.294967296;
	dec_temp  		=	(uint32_t)  dec_step*4.294967296;
	inc_temp  		=	(uint32_t)  inc_step*4.294967296;
	neg_rate_temp	=  	neg_rate;							// 时间
	pos_rate_temp	=  	pos_rate;
	
	DRL[7]=(uint8_t) lower_temp;		//将上限下限频率、频率加减步进、频率加减速率写入数组，后写入相应的寄存器
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
	
	AD9910_CS_L;												
	txd_8bit(0x0B);			// 将数字斜坡限值存入 0x0B
	for(i=0;i<8;i++)
	{
		txd_8bit(DRL[i]);																								
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;												
	txd_8bit(0x0C);			// 将数字斜坡步长存入 0x0C
	for(i=0;i<8;i++)
	{
		txd_8bit(DRS[i]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;							
	txd_8bit(0x0D);			// 将数字斜坡速率存入 0x0D
	for(i=0;i<4;i++)
	{
		txd_8bit(DRR[i]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;				// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;	
}


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_Init(void)
//函数功能:将CFR1和CFR2恢复默认值
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_Init(void)
{
	int j;
	
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};
	uint8_t CFR2[]={0x01,0x40,0x08,0x20};
	uint8_t PRO[] = {0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	AD9910_CS_L;
	txd_8bit(0x00);														// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x01);														// 将CFR2写入其寄存器0x01
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x0e);														// 将RAM Profile0写入其寄存器0x0e
	for(j=0;j<8;j++)
	{
		txd_8bit(PRO[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	

	
	UP_DAT_L;															// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}
//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_ZB_Fre_Init(void)
//函数功能:设置RAM模式中的载波的频率的初始化
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Init(void)
{
	int j;
	
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};	// 开启AD9910反Sinc滤波功能
	uint8_t CFR2[]={0x00,0x41,0x08,0x20};	// 读取有效的FTW寄存器开启，FTW是写载波频率时用的
	
	AD9910_CS_L;
	txd_8bit(0x00);			// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x01);			// 将CFR2写入其寄存器0x01
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	
	UP_DAT_L;				// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_ZB_Fre_Set(uint32_t Freq)
//函数功能:设置RAM模式中的载波的频率
//入口参数:Freq--------------------载波频率
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_ZB_Fre_Set(uint32_t Freq)
{
		uint8_t FTW[]={0x00,0x00,0xa7,0xc6};
		int j;
		uint32_t Temp;  

	  Temp=(uint32_t)Freq*4.294967296;// 将输入频率转化为相应的FTW值  4.294967296=(2^32)/1000000000
		
	  FTW[3]=(uint8_t)Temp;
	  FTW[2]=(uint8_t)(Temp>>8);
	  FTW[1]=(uint8_t)(Temp>>16);
	  FTW[0]=(uint8_t)(Temp>>24);
		
		AD9910_CS_L;					// CSN置0			开片选
		txd_8bit(0x07);			// 选择0x07地址           	将频率写入寄存器
		for(j=0;j<4;j++)
		{
			txd_8bit(FTW[j]);
		}
		AD9910_CS_H;					// CSN置1			关片选
		Delay_Us(1);
		
		
		UP_DAT_L;				// 更新AD9910输出
		Delay_Us(1);
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void FSK_RAM_Write(void)
//函数功能:将数据写入1024*32的RAM中---------------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void FSK_RAM_Write(void)
{
	int j;
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// 开启AD9910反Sinc滤波
	uint8_t CFR2[]={0x00,0x40,0x08,0x20};
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};// 设置RAM的起始和终止地址、地址步进率
	
	
	AD9910_CS_L;
	txd_8bit(0x00);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x01);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;																										// 将RAM的起始和终止地址、地址步进率写入相应的寄存器  0x0e
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// 更新一下AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	AD9910_CS_L;								
	txd_8bit(0x16);														
	for(j=0; j<1024; j++)
	{	
		txd_32bit(ramdata[j]);																				// 将频率RAM的内容写入0x16寄存器
	}
		AD9910_CS_H;
	
		UP_DAT_L;																									// 在更新一下AD9910
		Delay_Us(1);
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void FM_RAM_Write(void)
//函数功能:将数据写入1024*32的RAM中---------------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void FM_RAM_Write(uint32_t modin,uint32_t deepth, uint32_t carrer)
{
	int j;
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// 开启AD9910反Sinc滤波
	uint8_t CFR2[]={0x00,0x40,0x08,0x20};
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xf9,0xC0,0x00,0x00,0x04};// 设置RAM的起始和终止地址、地址步进率
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

	AD9910_CS_L;
	txd_8bit(0x00);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x01);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;																										// 将RAM的起始和终止地址、地址步进率写入相应的寄存器  0x0e
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// 更新一下AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	AD9910_CS_L;								
	txd_8bit(0x16);														
	for(j=0; j<1000; j++)
	{	
		ramdataraw = (cos(j*PI/500)*modin*deepth+carrer*2*PI)/2/PI*4.294967296;
		txd_32bit((uint32_t)ramdataraw);																				// 将频率RAM的内容写入0x16寄存器
	}
	AD9910_CS_H;
	
	UP_DAT_L;																									// 在更新一下AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_ramdata_W(void)
//函数功能:将数据写入1024*32的RAM中---------------------------频率
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_ramdata_W(void)
{
	int j;
	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// 开启AD9910反Sinc滤波
	uint8_t CFR2[]={0x00,0x40,0x08,0x20};
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};// 设置RAM的起始和终止地址、地址步进率
	
	
	AD9910_CS_L;
	txd_8bit(0x00);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x01);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;																										// 将RAM的起始和终止地址、地址步进率写入相应的寄存器  0x0e
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// 更新一下AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	AD9910_CS_L;								
	txd_8bit(0x16);														
	for(j=0; j<1024; j++)
	{	
		txd_32bit(ramdata[j]);																				// 将频率RAM的内容写入0x16寄存器
	}
		AD9910_CS_H;
	
		UP_DAT_L;																									// 在更新一下AD9910
		Delay_Us(1);
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
}


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_AMP_W(void)
//函数功能:将数据写入1024*32的RAM中-------------------------幅度
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_AMP_W(void)
{
	int j;

	uint8_t CFR1[]={0x00,0x40,0x00,0x00};																	// 开启AD9910反Sinc滤波
	uint8_t RAM_PRO0[]={0x00,0x00,0xff,0xff,0xC0,0x00,0x00,0x00};// 设置RAM的起始和终止地址、地址步进率

	AD9910_CS_L;
	txd_8bit(0x00);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);																				// 将RAM的起始和终止地址、地址步进率写入相应的寄存器  0x0e
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x16);
	for(j=0; j<1024; j++)
	{	
		txd_32bit(ramdata[j]);																				// 将幅度RAM的内容写入寄存器0x16	
	}
		AD9910_CS_H;
	
		UP_DAT_L;
		Delay_Us(1);																									// 更新AD9910
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
	 
}


//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_CON_RECIR_Fre_R(void)
//函数功能:连续循环模式的回放-------------------------频率
//														
//入口参数:无
//出口参数:无
//主要就是使用这个
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																								// 使能RAM模式  将回放目的位设为“00” 回放频率 （注：使能后就变成了RAM寄存器了）
	
	//uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x04};												//	从地址0回放到1023					// 连续双向斜坡模式RAM_PROx[7]=0x04
	
	AD9910_CS_L;
	txd_8bit(0x00);																																// 将CFR1写入其地址0x00		
	for(j=0;j<4;j++)                                                                
	{                                                                               
		txd_8bit(CFR1[j]);                                                          
	}                                                                               
	AD9910_CS_H;	                                                                
	Delay_Us(1);                                                                  
	                                                                                
//	AD9910_CS_L;                                                                 
//	txd_8bit(0x0e);																                                // 将RAM_RPOx写入其地址		
//	for(j=0;j<8;j++)                                                                
//	{                                                                               
//		txd_8bit(RAM_PRO0[j]);                                                      
//	}                                                                               
//	AD9910_CS_H;	                                                                
//	Delay_Us(1);  

	
	UP_DAT_L;                                                                 
	Delay_Us(1);                                                                  // 更新AD9910
	UP_DAT_H;                                                                 
	Delay_Us(1);                                                                  
	UP_DAT_L;                                                                 
	Delay_Us(1);                                                                      
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_CON_RECIR_AMP_R(void)
//函数功能:连续循环模式的回放-------------------------幅度
//														
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_CON_RECIR_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xE0,0x40,0x00,0x00};																								// 使能RAM模式  将回放目的位设为“10” 回放幅度 （注：使能后就变成了RAM寄存器了）
	
	uint8_t RAM_PRO0[]={0x00,0x00,0x01,0xff,0xc0,0x00,0x00,0x04};												//	从地址0回放到1023					// 连续双向斜坡模式RAM_PROx[7]=0x04
	
	AD9910_CS_L;
	txd_8bit(0x00);																																// 将CFR1写入其地址0x00															
	for(j=0;j<4;j++)                                                                
	{                                                                               
		txd_8bit(CFR1[j]);                                                          
	}                                                                               
	AD9910_CS_H;	                                                                
	Delay_Us(1);                                                                  
	                                                                                
	AD9910_CS_L;                                                                 
	txd_8bit(0x0e);																                                // 将RAM_RPOx写入其地址		
	for(j=0;j<8;j++)                                                                
	{                                                                               
		txd_8bit(RAM_PRO0[j]);                                                      
	}                                                                               
	AD9910_CS_H;	                                                                
	Delay_Us(1); 
	
	UP_DAT_L;                                                                 
	Delay_Us(1);                                                                  
	UP_DAT_H;                                                                 
	Delay_Us(1);                                                                  // 更新AD9910
	UP_DAT_L;
	Delay_Us(1);
}

//------------------------------------------------------------------------------------
//函数名称:void Freq_convert(uint32_t Freq)	
//函数功能:AD9910写初始频率
//入口参数:Freq      写频率   频率小于450M														
//出口参数:无
//------------------------------------------------------------------------------------
void Freq_convert2(uint32_t Freq)
{
	uint32_t Temp;            
	Temp=(uint32_t)Freq*4.294967296;	   //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000
		
	FTW[3]=(uint8_t)Temp;
	FTW[2]=(uint8_t)(Temp>>8);
	FTW[1]=(uint8_t)(Temp>>16);
	FTW[0]=(uint8_t)(Temp>>24);
}
//------------------------------------------------------------------------------------
//函数名称:void Amp_convert(uint32_t Amp)	
//函数功能:AD9910写初始幅度
//入口参数:Amp      写幅度  														
//出口参数:无
//------------------------------------------------------------------------------------
void Amp_convert2(uint32_t Amp)
{
		
	ASF[3]=(uint8_t)Amp;
	ASF[2]=(uint8_t)(Amp>>8);

}
//------------------------------------------------------------------------------------
//函数名称:void AD9910_Init_Sin(void)
//函数功能:AD9910时钟的设置和辅助DAC设置 以及AD9910并行正弦初始化
//入口参数:无
//出口参数:无
//------------------------------------------------------------------------------------
void AD9910_Init_Sin(int gain)
{
	int j;
	PROFILE0_L;														// 选择 Profile0
	PROFILE1_L;
	PROFILE2_L;
	DRHOLD_L;
	DRCTL_L;
	MAS_REST_H;	
	Delay_Us(1);													// 复位AD9910
	MAS_REST_L;
	
	AD9910_CS_L;														// CSN置0			开片选
	txd_8bit(0x00);													// 选择0x00地址            CFR1寄存器写入数据
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	AD9910_CS_L;														// CSN置1			关片选
	
	AD9910_CS_L;														// CSN置0			开片选
	
	txd_8bit(0x01);													// 选择0x01地址            CFR2寄存器写入数据
	CFR2[3] += gain;
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);	
	CFR2[3] = 0x30;
	AD9910_CS_L;														// CSN置0			开片选
	
	txd_8bit(0x02);													// 选择0x02地址            CFR3寄存器写入数据
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR3[j]);	
	}
	AD9910_CS_H;														// CSN置1			关片选
	Delay_Us(1);
	
	AD9910_CS_L;														// CSN置0			开片选
	txd_8bit(0x03);													// 选择0x03地址            辅助DAC寄存器写入数据
	for(j=0;j<4;j++)
	{
		txd_8bit(Assist_DAC[j]);
	}
	AD9910_CS_H;														// CSN置1			关片选
	Delay_Us(1);
	
	AD9910_CS_L;														// CSN置0			开片选
	txd_8bit(0x07);													// 选择0x07地址           	将初始频率写入寄存器
	for(j=0;j<4;j++)
	{
		txd_8bit(FTW[j]);
	}
	AD9910_CS_H;														// CSN置1			关片选
	Delay_Us(1);
	
	UP_DAT_L;
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_WAVE_RAM_AMP_W(int mode)
//函数功能:将数据写入1024*32的RAM中-------------------------幅度
//入口参数:无
//出口参数:无
//这个函数原本是用来输出不同种类的幅度数据的，不过我把它给删掉了，所以实际用上面的函数就行了
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_WAVE_RAM_AMP_W(int mode)
{
	int j;

	uint8_t CFR1[]={0x60,0x40,0x00,0x00};		// 开启AD9910反Sinc滤波
	uint8_t RAM_PRO0[]={0x00,0x00,0x01,0xff,0xC0,0x00,0x00,0x00};	// 设置RAM的起始和终止地址、地址步进率

	AD9910_CS_L;
	txd_8bit(0x00);																									// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);	// 将RAM的起始和终止地址、地址步进率写入相应的寄存器  0x0e
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																										// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x16);
	for(j=0; j<1024; j++)
	{	
		if(mode == 1)
		{
			txd_32bit(ramdata[j]);																				// 将幅度RAM的内容写入寄存器0x16	
		}else if(mode == 2)
		{
			txd_32bit(ramdata[j]);		//将三角波的数据写入ram
		}else if(mode == 3)
		{
			txd_32bit(ramdata[j]);	//将方波的数据写入ram
		}
	}
		AD9910_CS_H;
	
		UP_DAT_L;
		Delay_Us(1);																									// 更新AD9910
		UP_DAT_H;
		Delay_Us(1);
		UP_DAT_L;
		Delay_Us(1);
	 
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_DIR_Fre_R(void)
//函数功能:直接转换模式的回放-------------------------频率
//入口参数:无
//出口参数:无
//目前还没想到这个功能该怎么使用，所以不做考虑
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																				// 使能RAM模式  将回放目的位设为“00” 回放频率 （注：使能后就变成了RAM寄存器了）

	
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x00};								//	从地址0到地址23
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x00};								//				24~273   								直接转换模式RAM_PROx[7]=0x00
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x00};								//      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x00};								//				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x00};								//				774~1023								熟悉了可以自己设置
//uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
	
	
	AD9910_CS_L;
	txd_8bit(0x00);																												// 将CFR1写入其相应的寄存器														
	for(j=0; j<4; j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	

	
	AD9910_CS_L;
	txd_8bit(0x0e);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);																							// 将PRO0~PRO4写入相应的寄存器
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x0F);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x10);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);

	AD9910_CS_L;
	txd_8bit(0x11);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO3[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x12);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO4[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																														// 更新AD9910输出
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_DIR_AMP_R(void)
//函数功能:直接转换模式的回放-------------------------幅度
//入口参数:无
//出口参数:无
//目前还没想到这个功能该怎么使用，所以不做考虑
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_DIR_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xC0,0x40,0x00,0x00};																					// 使能RAM模式  将回放目的位设为“10” 回放幅度 （注：使能后就变成了RAM寄存器了）

	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x06,0x00,0x00,0x00,0x00};									//	从地址0到地址23
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x00};                  //				24~273   									直接转换模式RAM_PROx[7]=0x00				
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x00};                  //      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x00};                  //				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x00};                  //				774~1023								熟悉了可以自己设置
//uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
//uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x00};
	
	
	AD9910_CS_L;	
	txd_8bit(0x00);																
	for(j=0; j<4; j++)																													// 将CFR1写入其相应的寄存器						
	{                                                                           
		txd_8bit(CFR1[j]);                                                      
	}                                                                           
	AD9910_CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
		AD9910_CS_L;                                                           
	txd_8bit(0x0e);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO0[j]);                                                  
	}                                                                           // 将PRO0~PRO4写入相应的寄存器
	AD9910_CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	AD9910_CS_L;                                                             
	txd_8bit(0x0F);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO1[j]);                                                  
	}                                                                           
	AD9910_CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	AD9910_CS_L;                                                             
	txd_8bit(0x10);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO2[j]);                                                  
	}                                                                           
	AD9910_CS_H;	                                                            
	Delay_Us(1);                                                              
                                                                              
	AD9910_CS_L;                                                             
	txd_8bit(0x11);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO3[j]);                                                  
	}                                                                           
	AD9910_CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	AD9910_CS_L;                                                             
	txd_8bit(0x12);																                            
	for(j=0;j<8;j++)                                                            
	{                                                                           
		txd_8bit(RAM_PRO4[j]);                                                  
	}                                                                           
	AD9910_CS_H;	                                                            
	Delay_Us(1);                                                              
	                                                                            
	UP_DAT_L;                                                             
	Delay_Us(1);                                                              	// 更新AD9910输出
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}
//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_ONE_Fre_R(void)
//函数功能:上斜坡模式的回放-------------------------频率
//														ONE 代表由外部引脚PRO2~PRO0控制
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																							// 使能RAM模式  将回放目的位设为“00” 回放频率 （注：使能后就变成了RAM寄存器了）
	
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x01};											//	从地址0回放到1023			（熟悉了这些回放可以自己设置）
																																								//上斜坡模式RAM_PROx[7]=0x01
									
//	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x01};
//	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};																									
//	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};
//	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};
//	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};
//	uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};
//	uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};
//	uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};
	
	AD9910_CS_L;
	txd_8bit(0x00);																															// 将CFR1写入其寄存器0x00
	for(j=0;j<4;j++)
	{
		txd_8bit(CFR1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x0e);																															// 将RAM_PRO0写入其寄存器0x0e														
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
//	AD9910_CS_L;																															
//	txd_8bit(0x0f);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO1[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);
//	
//	AD9910_CS_L;
//	txd_8bit(0x10);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO2[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);

//	AD9910_CS_L;
//	txd_8bit(0x11);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO3[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);
//	
//	AD9910_CS_L;
//	txd_8bit(0x12);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO4[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);
	
	UP_DAT_L;																																// 使能AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_ONE_AMP_R(void)
//函数功能:上斜坡模式的回放-------------------------幅度
//ONE 代表由外部引脚PRO2~PRO0控制
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_ONE_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xC0,0x40,0x00,0x00};																							// 使能RAM模式  将回放目的位设为“10” 回放幅度 （注：使能后就变成了RAM寄存器了）
	
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0xff,0xc0,0x00,0x00,0x01};											//	从地址0回放到1023			（熟悉了这些回放可以自己设置）
																																								//上斜坡模式RAM_PROx[7]=0x01
//	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};                    
//	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};                    
//	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};                    
//	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};                    
//	uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//	uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//	uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
	                                                                              
	AD9910_CS_L;                                                               
	txd_8bit(0x00);																									            // 将CFR1写入其寄存器0x00 
	for(j=0;j<4;j++)                                                              
	{                                                                             
		txd_8bit(CFR1[j]);                                                        
	}                                                                             
	AD9910_CS_H;	                                                              
	Delay_Us(1);                                                                
	                                                                              
	AD9910_CS_L;                                                               
	txd_8bit(0x0e);																                              // 将RAM_PRO0写入其寄存器0x0e														
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO0[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
//	AD9910_CS_L;
//	txd_8bit(0x0f);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO1[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);
//	
//	AD9910_CS_L;
//	txd_8bit(0x10);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO2[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);

//	AD9910_CS_L;
//	txd_8bit(0x11);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO3[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);
//	
//	AD9910_CS_L;
//	txd_8bit(0x12);																
//	for(j=0;j<8;j++)
//	{
//		txd_8bit(RAM_PRO4[j]);
//	}
//	AD9910_CS_H;	
//	Delay_Us(1);
	
	UP_DAT_L;																																// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
	
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_TWO_Fre_R(void)
//函数功能:上斜坡模式的回放-------------------------频率
//TWO 代表由内部控制							控制位为（CFR1[20:17]） 参考数据手册
//入口参数:无
//出口参数:无
//这个功能目前我认为完全没必要使用，所以不用管
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_Fre_R(void)
{
	int j;
	uint8_t CFR1[]={0x80,0x40,0x00,0x00};																						// 使能RAM模式  将回放目的位设为“00” 回放频率 （注：使能后就变成了RAM寄存器了）
																																							// 选择相应的控制位，我选择的是0100   突发 执行Profile 0至Profile 4，然后中止 
																																							// 控制位为（CFR1[20:17]） 参考数据手册
																			
	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x01};										//	从地址0到地址23
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};                    //				24~273   												//上斜坡模式RAM_PROx[7]=0x01
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};                    //      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};                    //				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};                    //				774~1023								熟悉了可以自己设置
//uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
//uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                    
	                                                                            
	                                                                            
	AD9910_CS_L;                                                             
	txd_8bit(0x00);																                            
	for(j=0;j<4;j++)                                                            	// 将CFR1写入其相应的寄存器						
	{                                                                             
		txd_8bit(CFR1[j]);                                                        
	}                                                                             
	AD9910_CS_H;	                                                              
	Delay_Us(1);                                                                
	                                                                              
	AD9910_CS_L;                                                               
	txd_8bit(0x0e);																                              
	for(j=0;j<8;j++)                                                              
	{                                                                             
		txd_8bit(RAM_PRO0[j]);                                                    
	}                                                                             // 将PRO0~PRO4写入相应的寄存器
	AD9910_CS_H;	                                                              
	Delay_Us(1);                                                                
	                                                                              
	AD9910_CS_L;                                                               
	txd_8bit(0x0f);																                              
	for(j=0;j<8;j++)                                                              
	{                                                                             
		txd_8bit(RAM_PRO1[j]);                                                    
	}                                                                             
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x10);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);

	AD9910_CS_L;
	txd_8bit(0x11);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO3[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x12);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO4[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																																// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

//---------------------------------------------------------------------------------------------------------------------------------
//函数名称:void AD9910_RAM_RAMP_UP_TWO_AMP_R(void)
//函数功能:上斜坡模式的回放-------------------------幅度
//这个功能目前我认为完全没必要使用，所以不用管												TWO 代表由内部控制							控制位为（CFR1[20:17]） 参考数据手册
//入口参数:无
//出口参数:无
//---------------------------------------------------------------------------------------------------------------------------------
void AD9910_RAM_RAMP_UP_TWO_AMP_R(void)
{
	int j;
	uint8_t CFR1[]={0xC0,0x40,0x00,0x00};																							// 使能RAM模式  将回放目的位设为“10” 回放幅度 （注：使能后就变成了RAM寄存器了）

	uint8_t RAM_PRO0[]={0x00,0xff,0xff,0x05,0x00,0x00,0x00,0x01};											//	从地址0到地址23				
	uint8_t RAM_PRO1[]={0x00,0xff,0xff,0x44,0x40,0x06,0x00,0x01};                      //				24~273   												//上斜坡模式RAM_PROx[7]=0x01
	uint8_t RAM_PRO2[]={0x00,0xff,0xff,0x82,0xC0,0x44,0x80,0x01};                      //      	274~523
	uint8_t RAM_PRO3[]={0x00,0xff,0xff,0xC1,0x40,0x83,0x00,0x01};                      //				524~773
	uint8_t RAM_PRO4[]={0x00,0xff,0xff,0xff,0xC0,0xC1,0x80,0x01};                      //				774~1023								熟悉了可以自己设置
	uint8_t RAM_PRO5[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                      
	uint8_t RAM_PRO6[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                      
	uint8_t RAM_PRO7[]={0x00,0xff,0xff,0xff,0xC0,0x00,0x00,0x01};                      
	                                                                              
	AD9910_CS_L;                                                               
	txd_8bit(0x00);																                              
	for(j=0;j<4;j++)                                                              
	{                                                                             	// 将CFR1写入其相应的寄存器						
		txd_8bit(CFR1[j]);                                                          
	}                                                                               
	AD9910_CS_H;	                                                                
	Delay_Us(1);                                                                  
	                                                                                
	AD9910_CS_L;                                                                 
	txd_8bit(0x0e);																                                
	for(j=0;j<8;j++)                                                                
	{                                                                               
		txd_8bit(RAM_PRO0[j]);                                                      
	}                                                                               
	AD9910_CS_H;	                                                                // 将PRO0~PRO4写入相应的寄存器
	Delay_Us(1);                                                                  
	                                                                                
	AD9910_CS_L;                                                                 
	txd_8bit(0x0f);																                                
	for(j=0;j<8;j++)                                                                
	{
		txd_8bit(RAM_PRO1[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x10);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO2[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);

	AD9910_CS_L;
	txd_8bit(0x11);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO3[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	AD9910_CS_L;
	txd_8bit(0x12);																
	for(j=0;j<8;j++)
	{
		txd_8bit(RAM_PRO4[j]);
	}
	AD9910_CS_H;	
	Delay_Us(1);
	
	UP_DAT_L;																																	// 更新AD9910
	Delay_Us(1);
	UP_DAT_H;
	Delay_Us(1);
	UP_DAT_L;
	Delay_Us(1);
}

