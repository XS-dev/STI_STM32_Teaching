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
    AD5933_Set_Freq_Add(100);//����Ƶ������Ϊ1
    AD5933_Set_Freq_Num(50);//������������Ҳ����ɨ���е�Ƶ�ʵ���

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
*������: AD5933_Set_Freq_Start
*����˵��:82��83��84������ʼƵ��
*�β�:
*����ֵ: 
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
*������: AD5933_Set_Freq_Add
*����˵��:����Ƶ������
*�β�:
*����ֵ: 
**********************************************************************************************************/
void AD5933_Set_Freq_Add( unsigned int afreq )//85,86,87����Ƶ������
{
    unsigned char buf[3];

    Fre_To_Hex( afreq, buf );
    I2C_EE_ByteWrite( 0x85, buf[0]);
    I2C_EE_ByteWrite( 0x86, buf[1]);
    I2C_EE_ByteWrite( 0x87, buf[2]);
}
/*********************************************************************************************************
*������: AD5933_Set_Freq_Num
*����˵��:����������
*�β�:
*����ֵ: 
**********************************************************************************************************/
void AD5933_Set_Freq_Num( unsigned int num )//88,89����������
{
    unsigned char buf[2];
    buf[0] = num >> 8 ;
    buf[1] = num;
    I2C_EE_ByteWrite( 0x88, buf[0]);
    I2C_EE_ByteWrite( 0x89, buf[1]);
}
/*********************************************************************************************************
*������: AD5933_Set_Mode
*����˵��:���ù���ģʽ�����������ѹ��PGA���棬ʱ��ѡ�񼰸�λ��
*�β�:
*����ֵ: 
**********************************************************************************************************/
void AD5933_Set_Mode( unsigned int ctrl, unsigned int out, unsigned int gain, unsigned int clk, unsigned int rst )//80,81���ƼĴ���
{
    iMode = ctrl | out | gain | clk | rst;
    I2C_EE_ByteWrite( 0x80, iMode >> 8 );
    I2C_EE_ByteWrite( 0x81, iMode      );
}

void AD5933_Set_Mode_Rst(void)//��λ������D4λ�Ǹ�λ����λ
{
    iMode  = ( iMode & 0xffef) | AD5933_Reset;
    I2C_EE_ByteWrite( 0x81, iMode      );
}
/*********************************************************************************************************
*������: AD5933_Set_Mode_Standby
*����˵��:���ù���ģʽ����ʼ��/����/����Ƶ��/�ظ�Ƶ��/����/ʡ��/����
*�β�:
*����ֵ: 
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
*������: AD5933_Get_DFT_ST
*����˵��:��ȡ״̬���¶Ȳ�����Ч/ʵֵ����ֵ��Ч/Ƶ��ɨ�����
*�β�:
*����ֵ: 
**********************************************************************************************************/
unsigned char  AD5933_Get_DFT_ST(void)
{
    unsigned char temp;
    temp = Rece_Byte( 0x8F );
    return temp;
}
/*********************************************************************************************************
*������: AD5933_Get_Real
*����˵��:��ȡʵ��
*�β�:
*����ֵ: 
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
*������: AD5933_Get_Img
*����˵��:��ȡ�鲿
*�β�:
*����ֵ: 
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
  SDA_IN(); // SDA����Ϊ����
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
  AD5933_SCK_L; // ʱ�����0
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

void START(void) // ������������
{
  SDA_OUT(); // sda�����
  AD5933_SDA_H;
  AD5933_SCK_H;
  Delay_Us(50); 
  AD5933_SDA_L; // START:when CLK is high,DATA change form high to low
  Delay_Us(50); 
  AD5933_SCK_L; // ǯסI2C���ߣ�׼�����ͻ��������
}

void STOP(void)
{
  SDA_OUT(); // sda�����
  AD5933_SCK_L;
  AD5933_SDA_L; // STOP:when CLK is high DATA change form low to high
  Delay_Us(50); 
  AD5933_SCK_H;
  AD5933_SDA_H; // ����I2C���߽����ź�
  Delay_Us(50); 
}

void SendByte(uint8_t txd) // ����һ���ֽ������Ӻ���
{
  uint32_t t,check;
  SDA_OUT();
//  AD5933_SCK_L; // ����ʱ�ӿ�ʼ���ݴ���
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
    Delay_Us(50); // ��TEA5767��������ʱ���Ǳ����
    AD5933_SCK_H;
    Delay_Us(50);
    AD5933_SCK_L;
    
  }
}

uint8_t ReadByte(void) // ��һ���ֽ�����
{
  unsigned char i, receive = 0;
  SDA_IN(); // SDA����Ϊ����
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


void Write_Byte(char nAddr, uint nValue) // nAddr��д���ֽ�nValue
{
  int nTemp = 0x1A; // AD5933��Ĭ�ϵ�ַ&д����λ���ͣ�
  START();
  SendByte(nTemp); // ���͵�ַ
  GetACK();

  SendByte(nAddr); // ���͵�ַ�ֽ�
  GetACK();

  SendByte(nValue); // ���������ֽ�
  GetACK();

  STOP(); // ֹͣ����
}

void SetPointer(char nAddr) //   ���õ�ַָ��
{
  int nTemp = 0x1A; // AD5933��Ĭ�ϵ�ַ&д����λ���ͣ�

  START();
  SendByte(nTemp); // ���͵�ַ
  GetACK();        // �ȴ� ACK

  SendByte(0xB0); // ����ָ������1101 0000
  GetACK();

  SendByte(nAddr); // ���͵�ַָ��
  GetACK();

  STOP(); // ֹͣ����
}

int Rece_Byte(char nAddr) // ��ȡnAddr�е��ֽڵ�����ֵ
{
  int nTemp;
  SetPointer(nAddr); // ��ַָ��ָ��nAddr
  nTemp = 0x1B;      // AD5933��Ĭ�ϵ�ַ&������λ���ߣ�
  START();

  SendByte(nTemp); // ���͵�ַ
  GetACK();

  nTemp = ReadByte(); // ��һ���ֽ�����
  SendNACK();         // ����NO_ACK

  STOP(); // ֹͣ����
  return nTemp;
}



uint16_t AD5933_Tempter(void)
{

  // unsigned char Status;  //����״̬
  unsigned int Tm; // ����ʵ�����鲿���¶�
	int Status = 0;
  //��λAD5933
  Write_Byte(0x80,0XB1);
  Write_Byte(0x81,0X00);

  // �����¶Ȳ���
  Write_Byte(0x80, 0x93);

  // �ȴ�ת�����
  do
  {
    Status=Rece_Byte(0x8F);
  }while(!(Status & 0x01));
  // �����¶ȣ�������Tm��
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
/*SValue[3]��ʼƵ�ʣ�IValue[3]Ƶ��������NValue[2]��������CValue[2]�����֣�ki����ϵ����PsɨƵΪ1�ظ�Ϊ0*/
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
  Ini_I2c(); // ��ʼ��I2C

  AddrTemp = 0X82; // ��ʼ����ʼƵ�ʼĴ���
  for (i = 0; i < 3; i++)
  {
    Write_Byte(AddrTemp, SValue[i]);
    AddrTemp++;
  }
  AddrTemp = 0X85; // ��ʼ��Ƶ�������Ĵ���
  for (i = 0; i < 3; i++)
  {
    Write_Byte(AddrTemp, IValue[i]);
    AddrTemp++;
  }
  AddrTemp = 0X88; // ��ʼ��Ƶ�ʵ����Ĵ���
  for (i = 0; i < 2; i++)
  {
    Write_Byte(AddrTemp, NValue[i]);
    AddrTemp++;
  }
  // ��ʼ�����ƼĴ�����1011 0001 0000 0000����ģʽ��2V��һ���Ŵ��ڲ�ʱ��
  AddrTemp = 0X80;
  //                for(i = 0;i <2;i++)
  {
    Write_Byte(AddrTemp, Mode | (AD5933_Standby >> 8));
    AddrTemp++;
    Write_Byte(AddrTemp, CValue[1]);
    AddrTemp++;
  }

  Write_Byte(0x80, Mode | (AD5933_SYS_Init >> 8)); // ���ƼĴ���д���ʼ��Ƶ��ɨ������
  Delay_Ms(10);
  Write_Byte(0X80, Mode | (AD5933_Begin_Fre_Scan >> 8)); // ���ƼĴ���д�뿪ʼƵ��ɨ������
  while (1)
  {
    while (1)
    {
      ReadTemp = Rece_Byte(0x8F); // ��ȡ״̬�Ĵ������DFT�Ƿ����
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

    if (realArr[2] >= 0x8000) // ����ʵ����ԭ��(������λ�⣬ȡ����һ)
    {
      realArr[2] ^= 0xFFFF;
      realArr[2] ^= 0x8000;
      realArr[2] += 1;
      realArr[2] ^= 0x8000;
    }
    if (imageArr[2] >= 0x8000) // �����鲿��ԭ��(������λ�⣬ȡ����һ)
    {
      imageArr[2] ^= 0xFFFF;
      imageArr[2] ^= 0x8000;
      imageArr[2] += 1;
      imageArr[2] ^= 0x8000;
    }
    AD5933_Dat_Re[j] = realArr[2];
    AD5933_Dat_Im[j] = imageArr[2];
    magnitude = sqrt(realArr[2] * realArr[2] + imageArr[2] * imageArr[2]); // ģֵ����
    resistance[j++] = 1 / (magnitude * Gain);                              // �迹����

    ReadTemp = Rece_Byte(0x8F); // ��ȡ״̬�Ĵ������Ƶ��ɨ���Ƿ����
    
    if (SWeep_Rep == 1)
		{
      Write_Byte(0X80, CValue[0]); // ���ƼĴ���д������Ƶ�ʣ�������һ��Ƶ�ʵ�)������
		}
    else
		{
      Write_Byte(0X80, CValue[0]); // ���ƼĴ���д���ظ���ǰƵ�ʵ�ɨ��
		}
		if (ReadTemp & 0x04)
		{
      break;
		}
  }
  Write_Byte(0X80, 0XA1); // �������ģʽ
  return magnitude;
}
/*Fre_Begin��ʼƵ�ʣ�Fre_UPƵ��������UP_Num��������OUTPUT_Vatage�����ѹ��Gain����ϵ����SWeep_RepɨƵΪ1�ظ�Ϊ0*/

/*
Fre_Begin 		��ʼƵ�� ��HZ��
Fre_UP				����Ƶ�ʣ�HZ��
UP_Num				��������
OUTPUT_Vatage	�����ѹ
                AD5933_OUTPUT_2V
                AD5933_OUTPUT_1V
                AD5933_OUTPUT_400mV
                AD5933_OUTPUT_200mV

Gain					PGA����
              AD5933_Gain_1
              AD5933_Gain_5
SWeep_Rep			ɨ��ģʽ
              AD5933_Fre_UP 	����Ƶ��
              AD5933_Fre_Rep	�ظ�Ƶ��
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

