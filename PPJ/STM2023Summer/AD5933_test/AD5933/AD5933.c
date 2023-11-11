#include "AD5933.h"
unsigned int iMode;
float resistance[200];
float rads[200];
int AD5933_Dat_Re[200];
int AD5933_Dat_Im[200];
void I2C_EE_ByteWrite( uint8_t WriteAddr, uint8_t dat )
{
	Write_Byte(WriteAddr,dat);
}
//unsigned char  Rece_Byte(uint8_t ReadAddr )
//{
//	Rece_Byte(ReadAddr);
//}
void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  /*Configure GPIO pin : PE3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  /*Configure GPIO pins : PE2 PE3 */
  GPIO_InitStruct.Pin = 	GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}


void Init_AD5933(void)
{
    int i, j, k;
    //---this paramter is very important, it decides the collect rate. format: Freq / 1024
    AD5933_Set_Freq_Start(20000);//100Khz, 100K/1024 = 100Hz, data update rate is 100Hz!!!!!!
    AD5933_Set_Freq_Add(100);//设置频率增量为1
    AD5933_Set_Freq_Num(50);//设置增量数，也就是扫描中的频率点数

    AD5933_Set_Mode( AD5933_Standby, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_IN_MCLK, AD5933_NReset );
    AD5933_Set_Mode_Rst();
    AD5933_Set_Mode_SysInit();

    //delay for enough time
    Delay_Us(100);
}

void Fre_To_Hex(float fre, uint8_t *buf)
{
    uint32_t dat;
    dat = (536870912 / (double)(AD5933_MCLK * 1000000)) * fre;
    buf[0] = dat >> 16;
    buf[1] = dat >> 8;
    buf[2] = dat;
}
/*********************************************************************************************************
*函数名: AD5933_Set_Freq_Start
*功能说明:82、83、84设置起始频率
*形参:
*返回值: 
**********************************************************************************************************/
void AD5933_Set_Freq_Start( unsigned int freq )//
{
    unsigned char buf[3];
    Fre_To_Hex( freq, buf );
    I2C_EE_ByteWrite( 0x82, buf[0]);
    I2C_EE_ByteWrite( 0x83, buf[1]);
    I2C_EE_ByteWrite( 0x84, buf[2]);
}
/*********************************************************************************************************
*函数名: AD5933_Set_Freq_Add
*功能说明:设置频率增量
*形参:
*返回值: 
**********************************************************************************************************/
void AD5933_Set_Freq_Add( unsigned int afreq )//85,86,87设置频率增量
{
    unsigned char buf[3];

    Fre_To_Hex( afreq, buf );
    I2C_EE_ByteWrite( 0x85, buf[0]);
    I2C_EE_ByteWrite( 0x86, buf[1]);
    I2C_EE_ByteWrite( 0x87, buf[2]);
}
/*********************************************************************************************************
*函数名: AD5933_Set_Freq_Num
*功能说明:设置增量数
*形参:
*返回值: 
**********************************************************************************************************/
void AD5933_Set_Freq_Num( unsigned int num )//88,89设置增量数
{
    unsigned char buf[2];
    buf[0] = num >> 8 ;
    buf[1] = num;
    I2C_EE_ByteWrite( 0x88, buf[0]);
    I2C_EE_ByteWrite( 0x89, buf[1]);
}
/*********************************************************************************************************
*函数名: AD5933_Set_Mode
*功能说明:设置工作模式，输出激励电压，PGA增益，时钟选择及复位等
*形参:
*返回值: 
**********************************************************************************************************/
void AD5933_Set_Mode( unsigned int ctrl, unsigned int out, unsigned int gain, unsigned int clk, unsigned int rst )//80,81控制寄存器
{
    iMode = ctrl | out | gain | clk | rst;
    I2C_EE_ByteWrite( 0x80, iMode >> 8 );
    I2C_EE_ByteWrite( 0x81, iMode      );
}

void AD5933_Set_Mode_Rst(void)//复位操作，D4位是复位控制位
{
    iMode  = ( iMode & 0xffef) | AD5933_Reset;
    I2C_EE_ByteWrite( 0x81, iMode      );
}
/*********************************************************************************************************
*函数名: AD5933_Set_Mode_Standby
*功能说明:设置工作模式，初始化/启动/递增频率/重复频率/测温/省电/待机
*形参:
*返回值: 
**********************************************************************************************************/
void AD5933_Set_Mode_Standby(void)
{
    iMode  = ( iMode & 0x0fff) | AD5933_Standby;
    I2C_EE_ByteWrite( 0x80, iMode >> 8  );
}

void AD5933_Set_Mode_SysInit(void)
{
    iMode  = ( iMode & 0x0fff) | AD5933_SYS_Init;
    I2C_EE_ByteWrite( 0x80, iMode >> 8  );
}

void AD5933_Set_Mode_Freq_Start(void)
{
    iMode  = ( iMode & 0x0fff) | AD5933_Begin_Fre_Scan;
    I2C_EE_ByteWrite( 0x80, iMode >> 8  );
}

void AD5933_Set_Mode_Freq_UP(void)
{
    iMode  = ( iMode & 0x0fff) | AD5933_Fre_UP;
    I2C_EE_ByteWrite( 0x80, iMode >> 8  );
}

void AD5933_Set_Mode_Freq_Repeat(void)
{
    iMode  = ( iMode & 0x0fff) | AD5933_Fre_Rep;
    I2C_EE_ByteWrite( 0x80, iMode >> 8  );
}

void AD5933_Set_Mode_Freq_Temp(void)
{
    iMode  = ( iMode & 0x0fff) | AD5933_Get_Temp;
    I2C_EE_ByteWrite( 0x80, iMode >> 8  );
}
/*********************************************************************************************************
*函数名: AD5933_Get_DFT_ST
*功能说明:读取状态，温度测量有效/实值和虚值有效/频率扫描完成
*形参:
*返回值: 
**********************************************************************************************************/
unsigned char  AD5933_Get_DFT_ST(void)
{
    unsigned char temp;
    temp = Rece_Byte( 0x8F );
    return temp;
}
/*********************************************************************************************************
*函数名: AD5933_Get_Real
*功能说明:读取实部
*形参:
*返回值: 
**********************************************************************************************************/
unsigned int AD5933_Get_Real(void)
{
    unsigned char high, low;
    unsigned int real;

    high = Rece_Byte( 0x94 );
    low = Rece_Byte( 0x95 );
    real = (high << 8) | low;
    return real;
}
/*********************************************************************************************************
*函数名: AD5933_Get_Img
*功能说明:读取虚部
*形参:
*返回值: 
**********************************************************************************************************/
unsigned int AD5933_Get_Img(void)
{
    unsigned char high, low;
    unsigned int img;

    high = Rece_Byte( 0x96 );
    low = Rece_Byte( 0x97 );
    img = (high << 8) | low;
    return img;
}






void Ini_I2c(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, AD5933_SCK_Pin|AD5933_SDA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = AD5933_SCK_Pin|AD5933_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}


void GetACK(void)
{
  uint8_t ucErrTime = 0;
  SDA_IN(); // SDA设置为输入
  AD5933_SDA_H;
  Delay_Us(50);
  AD5933_SCK_H;
  Delay_Us(50);
  while (READ_SDA)
  {
		ucErrTime = READ_SDA;
		if(ucErrTime)
		{
//			printf("failed");
			break;
		}
//    ucErrTime++;
		Delay_Us(50);
//    if (ucErrTime > 250)
//    {
//      STOP();
//			printf("failed");
//      return;
//    }
  }
//	printf("failed");
  AD5933_SCK_L; // 时钟输出0
}

void SendNACK(void)
{
  AD5933_SCK_L;
  SDA_OUT();
  AD5933_SDA_H;
  Delay_Us(50);
  AD5933_SCK_H;
  Delay_Us(50);
  AD5933_SCK_L;
}

void START(void) // 启动数据总线
{
  SDA_OUT(); // sda线输出
  AD5933_SDA_H;
  AD5933_SCK_H;
  Delay_Us(50); 
  AD5933_SDA_L; // START:when CLK is high,DATA change form high to low
  Delay_Us(50); 
  AD5933_SCK_L; // 钳住I2C总线，准备发送或接收数据
}

void STOP(void)
{
  SDA_OUT(); // sda线输出
  AD5933_SCK_L;
  AD5933_SDA_L; // STOP:when CLK is high DATA change form low to high
  Delay_Us(50); 
  AD5933_SCK_H;
  AD5933_SDA_H; // 发送I2C总线结束信号
  Delay_Us(50); 
}

void SendByte(uint8_t txd) // 发送一个字节数据子函数
{
  uint32_t t,check;
  SDA_OUT();
//  AD5933_SCK_L; // 拉低时钟开始数据传输
  for (t = 0; t < 8; t++)
  { 
		check = txd & 0x80;
		if(check)
		{
			AD5933_SDA_H;
		}
		else
		{
			AD5933_SDA_L;
		}
		Delay_Us(50);
    txd <<= 1;
    Delay_Us(50); // 对TEA5767这三个延时都是必须的
    AD5933_SCK_H;
    Delay_Us(50);
    AD5933_SCK_L;
    
  }
}

uint8_t ReadByte(void) // 读一个字节数据
{
  unsigned char i, receive = 0;
  SDA_IN(); // SDA设置为输入
  for (i = 0; i < 8; i++)
  {
    AD5933_SCK_L;
    Delay_Us(50);
    AD5933_SCK_H;
    receive <<= 1;
    if (READ_SDA)
		{
      receive++;
		}
    Delay_Us(50);
  }
  SendNACK();
  return receive;
}


void Write_Byte(char nAddr, uint nValue) // nAddr中写入字节nValue
{
  int nTemp = 0x1A; // AD5933的默认地址&写控制位（低）
  START();
  SendByte(nTemp); // 发送地址
  GetACK();

  SendByte(nAddr); // 发送地址字节
  GetACK();

  SendByte(nValue); // 发送数据字节
  GetACK();

  STOP(); // 停止总线
}

void SetPointer(char nAddr) //   设置地址指针
{
  int nTemp = 0x1A; // AD5933的默认地址&写控制位（低）

  START();
  SendByte(nTemp); // 发送地址
  GetACK();        // 等待 ACK

  SendByte(0xB0); // 发送指针命令1101 0000
  GetACK();

  SendByte(nAddr); // 发送地址指针
  GetACK();

  STOP(); // 停止总线
}

int Rece_Byte(char nAddr) // 读取nAddr中的字节到返回值
{
  int nTemp;
  SetPointer(nAddr); // 地址指针指向nAddr
  nTemp = 0x1B;      // AD5933的默认地址&读控制位（高）
  START();

  SendByte(nTemp); // 发送地址
  GetACK();

  nTemp = ReadByte(); // 读一个字节数据
  SendNACK();         // 发送NO_ACK

  STOP(); // 停止总线
  return nTemp;
}



uint16_t AD5933_Tempter(void)
{

  // unsigned char Status;  //保存状态
  unsigned int Tm; // 保存实部，虚部，温度
	int Status = 0;
  //复位AD5933
  Write_Byte(0x80,0XB1);
  Write_Byte(0x81,0X00);

  // 启动温度测量
  Write_Byte(0x80, 0x93);

  // 等待转换完成
  do
  {
    Status=Rece_Byte(0x8F);
  }while(!(Status & 0x01));
  // 读出温度，保存在Tm中
  Tm = Rece_Byte(0x92);
  Tm <<= 8;
  Tm += Rece_Byte(0x93);
  Tm <<= 2;

  return Tm;
}

void Maopao_Paixu(float *dat, uint16_t leng)
{
  uint16_t i, j;
  float buf;
  for (j = 0; j < leng - 1; j++)
    for (i = 0; i < leng - j - 1; i++)
      if (dat[i] > dat[i + 1])
      {
        buf = dat[i];
        dat[i] = dat[i + 1];
        dat[i + 1] = buf;
      }
}

float Get_resistance(uint16_t num)
{
  uint16_t i;
  float navle;
  Maopao_Paixu(resistance, num);
  navle = resistance[0];
  for (i = num / 2 - num / 4; i < num / 2 + num / 4; i++)
  {
    navle = (navle + resistance[i]) / 2;
  };
  ;
  return navle * AD5933_Correction;
}


/*
//void Fre_To_Hex(float fre, uint8_t *buf)
//{
//  uint32_t dat;
//  dat = (536870912 / (double)(AD5933_MCLK * 1000000)) * fre;
//  buf[0] = dat >> 16;
//  buf[1] = dat >> 8;
//  buf[2] = dat;
//}

*/
/*SValue[3]起始频率，IValue[3]频率增量，NValue[2]增量数，CValue[2]控制字，ki增益系数，Ps扫频为1重复为0*/
float Scale_imp(uint8_t *SValue, uint8_t *IValue, uint8_t *NValue, uint8_t *CValue)
{
  int i, j, AddrTemp;
  uint8_t Gain = ((~CValue[0]) & 0x01) ? 5 : 1;
  uint8_t SWeep_Rep = ((CValue[0] & 0xF0) == (AD5933_Fre_UP >> 8)) ? 1 : 0;
  uint8_t Mode = CValue[0] & 0x0f;
  long ReadTemp, realArr[3], imageArr[3];
  float magnitude;
  //                uint start_f[3]={0X33,0X26,0X17};
  //                uint inc_f[3]={0,0,0X21};
  //                uint num_f[2]={0,0XC8};
  //                uint control[2]={0XB1,0X00};
  //								CValue[0]=Mode|AD5933_Standby;
  j = 0;
  Ini_I2c(); // 初始化I2C

  AddrTemp = 0X82; // 初始化起始频率寄存器
  for (i = 0; i < 3; i++)
  {
    Write_Byte(AddrTemp, SValue[i]);
    AddrTemp++;
  }
  AddrTemp = 0X85; // 初始化频率增量寄存器
  for (i = 0; i < 3; i++)
  {
    Write_Byte(AddrTemp, IValue[i]);
    AddrTemp++;
  }
  AddrTemp = 0X88; // 初始化频率点数寄存器
  for (i = 0; i < 2; i++)
  {
    Write_Byte(AddrTemp, NValue[i]);
    AddrTemp++;
  }
  // 初始化控制寄存器，1011 0001 0000 0000待机模式，2V，一倍放大，内部时钟
  AddrTemp = 0X80;
  //                for(i = 0;i <2;i++)
  {
    Write_Byte(AddrTemp, Mode | (AD5933_Standby >> 8));
    AddrTemp++;
    Write_Byte(AddrTemp, CValue[1]);
    AddrTemp++;
  }

  Write_Byte(0x80, Mode | (AD5933_SYS_Init >> 8)); // 控制寄存器写入初始化频率扫描命令
  Delay_Ms(10);
  Write_Byte(0X80, Mode | (AD5933_Begin_Fre_Scan >> 8)); // 控制寄存器写入开始频率扫描命令
  while (1)
  {
    while (1)
    {
      ReadTemp = Rece_Byte(0x8F); // 读取状态寄存器检查DFT是否完成
      //							ReadTemp=ReadTemp&0x07;
      if (ReadTemp & 0x02)
        break;
    }
    realArr[0] = Rece_Byte(0x94);
    realArr[1] = Rece_Byte(0x95);
    realArr[2] = realArr[0] * 0x100 + realArr[1];

    imageArr[0] = Rece_Byte(0x96);
    imageArr[1] = Rece_Byte(0x97);
    imageArr[2] = imageArr[0] * 0x100 + imageArr[1];

    rads[j] = atan2(imageArr[2], realArr[2]) - 0.00143485062;

    if (realArr[2] >= 0x8000) // 计算实部的原码(除符号位外，取反加一)
    {
      realArr[2] ^= 0xFFFF;
      realArr[2] ^= 0x8000;
      realArr[2] += 1;
      realArr[2] ^= 0x8000;
    }
    if (imageArr[2] >= 0x8000) // 计算虚部的原码(除符号位外，取反加一)
    {
      imageArr[2] ^= 0xFFFF;
      imageArr[2] ^= 0x8000;
      imageArr[2] += 1;
      imageArr[2] ^= 0x8000;
    }
    AD5933_Dat_Re[j] = realArr[2];
    AD5933_Dat_Im[j] = imageArr[2];
    magnitude = sqrt(realArr[2] * realArr[2] + imageArr[2] * imageArr[2]); // 模值计算
    resistance[j++] = 1 / (magnitude * Gain);                              // 阻抗计算

    ReadTemp = Rece_Byte(0x8F); // 读取状态寄存器检查频率扫描是否完成
    
    if (SWeep_Rep == 1)
		{
      Write_Byte(0X80, CValue[0]); // 控制寄存器写入增加频率（跳到下一个频率点)的命令
		}
    else
		{
      Write_Byte(0X80, CValue[0]); // 控制寄存器写入重复当前频率点扫描
		}
		if (ReadTemp & 0x04)
		{
      break;
		}
  }
  Write_Byte(0X80, 0XA1); // 进入掉电模式
  return magnitude;
}
/*Fre_Begin起始频率，Fre_UP频率增量，UP_Num增量数，OUTPUT_Vatage输出电压，Gain增益系数，SWeep_Rep扫频为1重复为0*/

/*
Fre_Begin 		开始频率 （HZ）
Fre_UP				步进频率（HZ）
UP_Num				步进次数
OUTPUT_Vatage	输出电压
                AD5933_OUTPUT_2V
                AD5933_OUTPUT_1V
                AD5933_OUTPUT_400mV
                AD5933_OUTPUT_200mV

Gain					PGA增益
              AD5933_Gain_1
              AD5933_Gain_5
SWeep_Rep			扫描模式
              AD5933_Fre_UP 	递增频率
              AD5933_Fre_Rep	重复频率
*/
///*
// AD5933_Sweep(30000,200,200,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
float AD5933_Sweep(float Fre_Begin, float Fre_UP, uint16_t UP_Num, uint16_t OUTPUT_Vatage, uint16_t Gain, uint16_t SWeep_Rep)
{
  uint8_t SValue[3], IValue[3], NValue[2], CValue[2];
  uint16_t buf = 0;
  Fre_To_Hex(Fre_Begin, SValue);
  Fre_To_Hex(Fre_UP, IValue);
  NValue[0] = UP_Num >> 8;
  NValue[1] = UP_Num;
#ifdef AD5933_MCLK_USE_OUT
  buf = OUTPUT_Vatage | Gain | SWeep_Rep | AD5933_OUT_MCLK;
#else
  buf = OUTPUT_Vatage | Gain | SWeep_Rep | AD5933_IN_MCLK;
#endif
  CValue[0] = buf >> 8;
  CValue[1] = buf;

  Scale_imp(SValue, IValue, NValue, CValue);
  return 0;
}

float DA5933_Get_Rs(void)
{
  float Rs, re, im;

  //	AD5933_Sweep(30000,200,2,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_Rep);
  AD5933_Sweep(10000, 1, 40, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP);
  Rs = Get_resistance(40);
  re = Rs * cos(rads[0]);
  im = Rs * sin(rads[0]);
  return Rs;
}

float DA5933_Dat_Cap(float Fre)
{
  float pp;
  //	float dat=3.1415926*2*Fre;
  float dat = 1;
  pp = 1000000 * 23.9999992 / (AD5933_Dat_Re[0] * dat);
  return pp;
}

float DA5933_Get_Cap(float Fre)
{
  //	float Cap,dat;
  //
  //	AD5933_Sweep(30000,1,40,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_UP);
  //	Cap=DA5933_Get_Rs();
  //	dat=1/(Cap*30000*2*3.1415926/100000000000000);
  //	DA5933_Dat_Cap(30000);
  //
  //	return Cap;

  float Rs, re, im, cap;

  //	AD5933_Sweep(30000,200,2,AD5933_OUTPUT_2V,AD5933_Gain_1,AD5933_Fre_Rep);
  AD5933_Sweep(100000, 1, 20, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP);
  Rs = Get_resistance(20);
  //	re=Rs*cos(rads[0]);
  im = Rs * sin(rads[0]);
  cap = 0.9442 / (2 * 3.1415926 * im / 10000000);
  return cap;
}
float DA5933_Get_L(float Fre)
{
  float L;
  float Rs, re, im;

  AD5933_Sweep(100000, 1, 20, AD5933_OUTPUT_2V, AD5933_Gain_1, AD5933_Fre_UP);
  Rs = Get_resistance(20);
  //	re=Rs*cos(rads[0]);
  im = Rs * sin(rads[0]);
  L = im * 1000 / (2 * 3.1415926);
  return L;
}


//*/

