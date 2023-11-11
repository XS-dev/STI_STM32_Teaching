
#include"AD9854_SPI.h"
#include  <msp430x14x.h>
#include "general.h"

//******************************************************************************

unsigned char AD9854_Reg_PHA1[2]	={0x00,0x00};
unsigned char AD9854_Reg_PHA2[2]	={0x00,0x00};
unsigned char AD9854_Reg_FRE1[6]	={0x00,0xF0,0x00,0x00,0x00,0x00};
unsigned char AD9854_Reg_FRE2[6]	={0x50,0x00,0x00,0x00,0x00,0x00};
unsigned char AD9854_Reg_DELTA[6]	={0x00,0x00,0x00,0x01,0x00,0x00};
unsigned char AD9854_Reg_UPDATA[4]	={0x00,0x00,0x00,0x00};
unsigned char AD9854_Reg_RAMP_CLK[3]={0x00,0x00,0x01};
unsigned char AD9854_Reg_CTR_REG[4]	={	Bin(00010000),       //comp pd dowm  ctr[28]=0 //qac pd down ctr[26]=0
                           				Bin(01000110),       //no pll pass ctr[21]=0  //multi times 6 ctr[19-16]=00110  
			   							Bin(00100101),       //ext update ctr[8]=0    //Ramped FSK 
                           				Bin(01000000) };     //pass inv CR[6]=1//osk EN ctr[5]=0 //msb first ctr[1]=0 //no sdo active ctr[0]=0
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
//��������TI_CC_SPISetup(void)
//���룺��
//�������
//����������SPI���߶˿�����
//******************************************************************************
void TI_CC_SPISetup(void)
{
  ME1 |= USPIE0;                            // Enable USART0 SPI mode
  UCTL0 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
  UTCTL0 |= CKPL + SSEL1 + SSEL0 + STC;     // SMCLK, 3-pin mode
  UBR00 = 0x45;                             // UCLK/2  1F
  UBR10 = 0x00;                             // 0
  UMCTL0 = 0x4A;                            // No modulation  00
  TI_CC_SPI_USART0_PxSEL |= TI_CC_SPI_USART0_SIMO | TI_CC_SPI_USART0_SOMI | TI_CC_SPI_USART0_UCLK;
                                            // SPI option select
  TI_CC_SPI_USART0_PxDIR |= TI_CC_SPI_USART0_SIMO + TI_CC_SPI_USART0_UCLK;
                                            // SPI TXD out direction
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
}

//******************************************************************************
//��������TI_CC_SPIWriteBurstReg(Uchar addr, Uchar *buffer, Uchar count)
//���룺��ַ��д�뻺������д�����
//�������
//����������SPI����д���üĴ���
//******************************************************************************
void TI_CC_SPIWriteBurstReg(Uchar addr, Uchar *buffer, Uchar count)
{
    Uchar i;
    U0TXBUF = (addr & 0x0F); 				// Send Write address
    while (!(IFG1&UTXIFG0));                // Wait for TX to finish
    for (i = 0; i < count; i++)
    {
      U0TXBUF = buffer[i];                  // Send data
      while (!(IFG1&UTXIFG0));              // Wait for TX to finish
    }
    IFG1 &= ~URXIFG0;
    while(!(IFG1&URXIFG0));
}

//******************************************************************************
//��������void TI_CC_SPIReadBurstReg(Uchar addr, Uchar *buffer, Uchar count)
//���룺��ַ���������ݺ��ݴ�Ļ��������������ø���
//�������
//����������SPI���������üĴ���
//******************************************************************************
void TI_CC_SPIReadBurstReg(Uchar addr, Uchar *buffer, Uchar count)
{
  unsigned int i;
  IFG1 &= ~URXIFG0;                         // Clear flag
  U0TXBUF = ((addr & 0x0F) | 0x80);  		// Send Read address
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

//��������:��������
//�������:��
//******************************************************************
void Update_AD9854(void)
{
  	unsigned i=100 ;        //
	AD9854_UPDATE_OUT;
	AD9854_UPDATE_UP ;      //
	while(i--) ;
	AD9854_UPDATE_DOWN ;
}
//******************************************************************

//��������:��λ
//�������:��
//******************************************************************
void Io_Reset_AD9854(void)
{
	unsigned i=100 ;        //
	AD9854_IO_RESET_UP ;
	while(i--) ;
	AD9854_IO_RESET_DOWN ;
}
//******************************************************************

//��������:AD9854��ʼ�� д���ƼĴ���
//�������:��
//Ӳ��˵����
//******************************************************************
void Init_AD9854(void)
{
	HARDWARE_AD9854 ;       //ͨ���궨������
	TI_CC_SPISetup();		//��ʼ��SPI����
	AD9854_IO_serial;		//����ģʽ
	AD9854_OSC_ON;			//��ʱ��
	AD9854_CS_DOWN ;        //Ƭѡ	
	AD9854_RESET_UP;	
	DelayMs(10);
	AD9854_RESET_DOWN;		//����λ	
	Io_Reset_AD9854();
	AD9854_OSC_OFF;			//�ر�ʱ�ӣ���������
	TI_CC_SPIWriteBurstReg(AD9854_Addr_CTR_REG,		//д���ƼĴ���
						AD9854_Reg_CTR_REG, AD9854_Length_CTR_REG);			
	AD9854_OSC_ON;			//��ʱ�ӣ���������
	DelayMs(10);
	AD9854_UPDATE_OUT;
	AD9854_UPDATE_DOWN;		//���ø���ʱ��Ϊ���
}

//******************************************************************
//�������ܣ�д Frequency Tuning Word #1
//�������: 
//д���ַ�ֽ���:1 Byte
//д�������ֽ���:6 Bytes 
//******************************************************************
void Write_AD9854_Frq1(void)
{ 	
	TI_CC_SPIWriteBurstReg(AD9854_Addr_FRE1,		//дƵ�ʿ��ƼĴ���1
						AD9854_Reg_FRE2, AD9854_Length_FRE1);
	 Update_AD9854();

}

//******************************************************************
//�������ܣ���������ɨƵ
//�������:
//Serial Register Address :2��3��4��6
//д���ַ�ֽ���:1 Byte
//д�������ֽ���:6 Bytes 
//******************************************************************
void Write_AD9854_FrqSW(void)
{ 	
	TI_CC_SPIWriteBurstReg(AD9854_Addr_FRE1,		//дƵ�ʿ��ƼĴ���1
						AD9854_Reg_FRE1, AD9854_Length_FRE1);
		  Io_Reset_AD9854();
	TI_CC_SPIWriteBurstReg(AD9854_Addr_FRE2,		//дƵ�ʿ��ƼĴ���2
						AD9854_Reg_FRE2, AD9854_Length_FRE2);
		  Io_Reset_AD9854();
	TI_CC_SPIWriteBurstReg(AD9854_Addr_DELTA,		//дƵ�������Ĵ���
						AD9854_Reg_DELTA, AD9854_Length_DELTA);
		  Io_Reset_AD9854();
	TI_CC_SPIWriteBurstReg(AD9854_Addr_RAMP_CLK,	//дɨƵʱ�ӼĴ���
						AD9854_Reg_RAMP_CLK, AD9854_Length_RAMP_CLK);
	  	Update_AD9854();
}
