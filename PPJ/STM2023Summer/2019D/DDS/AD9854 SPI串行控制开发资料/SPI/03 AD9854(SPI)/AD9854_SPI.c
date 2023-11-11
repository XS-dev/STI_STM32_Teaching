
#include"AD9854_SPI.h"
#include  <msp430x14x.h>
#include "general.h"

//******************************************************************

unsigned char AD9854_Reg_PHA1[2]	={0x00,0x00};
unsigned char AD9854_Reg_PHA2[2]	={0x00,0x00};
unsigned char AD9854_Reg_FRE1[6]	={0x30,0x00,0x00,0x00,0x00,0x00};
unsigned char AD9854_Reg_FRE2[6]	={0x00,0x00,0x00,0x00,0x80,0x00};
unsigned char AD9854_Reg_DELTA[6]	={0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char AD9854_Reg_UPDATA[4]	={0x00,0x00,0x00,0x00};
unsigned char AD9854_Reg_RAMP_CLK[3]={0x00,0x00,0x00};
unsigned char AD9854_Reg_CTR_REG[4]	={	Bin(00010100),       //comp pd dowm  ctr[3]=0 //qac pd down ctr[5]=0
                           				Bin(01000110),       //no pll pass ctr[10]=0  //multi times 6 ctr[11-15]=00110  
			   							Bin(00000000),       //ext update ctr[23]=0
                           				Bin(01000000) };    //osk defoult ctr[26]=1  //msb first ctr[30]=0 //no sdo active ctr[31]=0
unsigned char AD9854_Reg_I_MUL[2]	={0x00,0x00};
unsigned char AD9854_Reg_Q_MUL[2]	={0x00,0x00};
unsigned char AD9854_Reg_SHAPED[1]	={0x00};
unsigned char AD9854_Reg_Q_DAC[2]	={0x00,0x00};

////////////////////////////////////////////////////////////////////
//                                                                //
//                             BASIC FUNCTION                     //
//                                                                //
////////////////////////////////////////////////////////////////////

//******************************************************************************
//函数名：TI_CC_SPISetup(void)
//输入：无
//输出：无
//功能描述：SPI总线端口设置
//******************************************************************************
void TI_CC_SPISetup(void)
{
	
  ME1 |= USPIE0;                            // Enable USART0 SPI mode
  UCTL0 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
  UTCTL0 |= CKPL + SSEL1 + SSEL0 + STC;     // SMCLK, 3-pin mode
  UBR00 = 0x1F;                             // UCLK/2
  UBR10 = 0x00;                             // 0
  UMCTL0 = 0x00;                            // No modulation
  TI_CC_SPI_USART0_PxSEL |= TI_CC_SPI_USART0_SIMO | TI_CC_SPI_USART0_SOMI | TI_CC_SPI_USART0_UCLK;
                                            // SPI option select
  TI_CC_SPI_USART0_PxDIR |= TI_CC_SPI_USART0_SIMO + TI_CC_SPI_USART0_UCLK;
                                            // SPI TXD out direction
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
}

//******************************************************************************
//函数名：TI_CC_SPIWriteBurstReg(Uchar addr, Uchar *buffer, Uchar count)
//输入：地址，写入缓冲区，写入个数
//输出：无
//功能描述：SPI连续写配置寄存器
//******************************************************************************
void TI_CC_SPIWriteBurstReg(Uchar addr, Uchar *buffer, Uchar count)
{
    Uchar i;
    U0TXBUF = addr ; // Send address
    while (!(IFG1&UTXIFG0));                // Wait for TX to finish
    for (i = 0; i < count; i++)
    {
      U0TXBUF = buffer[i];                  // Send data
      while (!(IFG1&UTXIFG0));              // Wait for TX to finish
    }
    IFG1 &= ~URXIFG0;
    while(!(IFG1&URXIFG0));
}

//***************************************************************************
//函数名：void TI_CC_SPIReadBurstReg(Uchar addr, Uchar *buffer, Uchar count)
//输入：地址，读出数据后暂存的缓冲区，读出配置个数
//输出：无
//功能描述：SPI连续读配置寄存器
//******************************************************************************
void TI_CC_SPIReadBurstReg(Uchar addr, Uchar *buffer, Uchar count)
{
  unsigned int i;
  IFG1 &= ~URXIFG0;                         // Clear flag
  U0TXBUF = (addr | 0x80);  				// Send address
  while (!(IFG1&UTXIFG0));                  // Wait for TXBUF ready
  U0TXBUF = 0;                              // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  while (!(IFG1&URXIFG0));                  // Wait for end of addr byte TX
  IFG1 &= ~URXIFG0;                         // Clear flag
  while (!(IFG1&URXIFG0));                  // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    U0TXBUF = 0;                            //Initiate next data RX, meanwhile..
    buffer[i] = U0RXBUF;                    // Store data from last data RX
    while (!(IFG1&URXIFG0));                // Wait for end of data RX
  }
  buffer[count-1] = U0RXBUF;                // Store last RX byte in buffer
}

//函数功能:更新设置
//输入参数:无
//******************************************************************
void Update_AD9854(void)
{
	AD9854_UPDATE_UP ;      //原来肯定是低电平,所以我觉得先置高好
	_NOP() ;
	_NOP() ;
	_NOP() ;
	AD9854_UPDATE_DOWN ;
}
//******************************************************************

//函数功能:复位
//输入参数:无
//******************************************************************
void Io_Reset_AD9854(void)
{
	unsigned i=100 ;        //这个数据取决于实际效果
	AD9854_IO_RESET_UP ;
	while(i--) ;
	AD9854_IO_RESET_DOWN ;
}
//******************************************************************

//函数功能:AD9854初始化 写控制寄存器
//输入参数:无
//硬件说明：
//******************************************************************
void Init_AD9854(void)
{
	HARDWARE_AD9854 ;   //通过宏定义就可以改动了
	TI_CC_SPISetup();		//初始化SPI总线
	AD9854_IO_serial;		//串行模式
	AD9854_OSC_ON;			//打开时钟
	AD9854_CS_DOWN ;    //片选	
	AD9854_RESET_UP;	
	DelayMs(10);
	AD9854_RESET_DOWN;		//主复位	
	Io_Reset_AD9854();
	AD9854_OSC_OFF;			//关闭时钟，更新配置
	TI_CC_SPIWriteBurstReg(AD9854_Addr_CTR_REG,		//写控制寄存器
						AD9854_Reg_CTR_REG, AD9854_Length_CTR_REG);
						
    //Update_AD9854() ;
	AD9854_OSC_ON;			//打开时钟，更新配置
	DelayMs(10);
	AD9854_UPDATE_OUT;
	AD9854_UPDATE_DOWN;		//配置更新时钟
}

//******************************************************************

//函数功能：写 Frequency Tuning Word #1
//输入参数: frq1(指针,指向unsigned char型数组的首地址,数组长度为48,6个字节)
//Serial Register Address :2
//写入地址字节数:1 Byte
//写入数据字节数:6 Bytes 
//******************************************************************
void Write_AD9854_Frq1(void)
{ 	
	TI_CC_SPIWriteBurstReg(AD9854_Addr_FRE1,		//写频率控制寄存器1
						AD9854_Reg_FRE1, AD9854_Length_FRE1);
	  Update_AD9854();
}
