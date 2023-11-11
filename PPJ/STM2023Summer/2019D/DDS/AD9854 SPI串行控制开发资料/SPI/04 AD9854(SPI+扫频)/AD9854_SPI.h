

#define  uclong   unsigned long
#define  Uchar    unsigned char
#define LongToBin(n) (((n>>21)&0x80)|((n>>18)&0x40)|((n>>15)&0x20)|((n>>12)&0x10)|((n>>9)&0x08)|((n>>6)&0x04)|((n>>3)&0x02)|((n)&0x01)) 
#define Bin(n) LongToBin(0x##n##l)
//******************************************************************
//端口操作
#define TI_CC_SPI_USART0_PxSEL  P3SEL       // interfaces, according to the pin
#define TI_CC_SPI_USART0_PxDIR  P3DIR       // assignments indicated in the
#define TI_CC_SPI_USART0_PxIN   P3IN        // chosen MSP430 device datasheet.
#define TI_CC_SPI_USART0_SIMO   0x02
#define TI_CC_SPI_USART0_SOMI   0x04
#define TI_CC_SPI_USART0_UCLK   0x08

#define AD9854_CS_UP       P6OUT |= BIT2
#define AD9854_CS_DOWN     P6OUT &=~BIT2   	//片选
#define AD9854_SCLK_UP     P3OUT |= BIT3
#define AD9854_SCLK_DOWN   P3OUT &=~BIT3	//数据时钟
#define AD9854_UPDATE_UP   P2OUT |= BIT4
#define AD9854_UPDATE_DOWN P2OUT &=~BIT4	//更新时钟
#define AD9854_UPDATE_OUT   P2DIR |= BIT4
#define AD9854_UPDATE_IN 	P2DIR &=~BIT4	//更新时钟方向
#define AD9854_SDIO_UP     P3OUT |= BIT1
#define AD9854_SDIO_DOWN   P3OUT &=~BIT1	//数据输入
#define AD9854_IO_RESET_UP    P3OUT |= BIT0
#define AD9854_IO_RESET_DOWN  P3OUT &=~BIT0	//SPI总线复位
#define AD9854_RESET_UP    P6OUT |= BIT6
#define AD9854_RESET_DOWN  P6OUT &=~BIT6   	//主复位
#define AD9854_IO_parallel P6OUT |= BIT7
#define AD9854_IO_serial   P6OUT &=~BIT7   	//串并选择
#define AD9854_OSC_ON    	P6OUT |= BIT5	
#define AD9854_OSC_OFF  	P6OUT &=~BIT5	//晶振控制
#define  HARDWARE_AD9854   P6DIR |= BIT2+BIT5+BIT6+BIT7;P3DIR |= BIT0+BIT1+BIT3;P6OUT &=~BIT5 //AD9854_OSC_OFF

////////////////////////////////////////////////////////////////////
//                                                                //
//                             INSTRUCTION BYTE                   //
//                                                                //
////////////////////////////////////////////////////////////////////

//******************************************************************
//寄存器地址 注意是串行地址
#define	  AD9854_Addr_PHA1       0        	// 2 Bytes
#define	  AD9854_Addr_PHA2       1        	// 2 Bytes 
#define	  AD9854_Addr_FRE1       2        	// 6 Bytes	
#define	  AD9854_Addr_FRE2       3        	// 6 Bytes
#define	  AD9854_Addr_DELTA      4        	// 6 Bytes
#define	  AD9854_Addr_UPDATA     5        	// 4 Bytes
#define	  AD9854_Addr_RAMP_CLK   6        	// 3 Bytes
#define	  AD9854_Addr_CTR_REG    7        	// 4 Bytes
#define	  AD9854_Addr_I_MUL      8        	// 2 Bytes
#define	  AD9854_Addr_Q_MUL      9        	// 2 Bytes
#define	  AD9854_Addr_SHAPED     10       	// 1 Bytes
#define	  AD9854_Addr_Q_DAC      11        	// 2 Bytes
//******************************************************************

//******************************************************************
//寄存器长度
#define	  AD9854_Length_PHA1       2        	// 2 Bytes
#define	  AD9854_Length_PHA2       2        	// 2 Bytes 
#define	  AD9854_Length_FRE1       6        	// 6 Bytes	
#define	  AD9854_Length_FRE2       6        	// 6 Bytes
#define	  AD9854_Length_DELTA      6        	// 6 Bytes
#define	  AD9854_Length_UPDATA     4        	// 4 Bytes
#define	  AD9854_Length_RAMP_CLK   3        	// 3 Bytes
#define	  AD9854_Length_CTR_REG    4        	// 4 Bytes
#define	  AD9854_Length_I_MUL      2        	// 2 Bytes
#define	  AD9854_Length_Q_MUL      2        	// 2 Bytes
#define	  AD9854_Length_SHAPED     1       		// 1 Bytes
#define	  AD9854_Length_Q_DAC      2        	// 2 Bytes

////////////////////////////////////////////////////////////////////
//                                                                //
//                          VARIABLES   DEFINITION                //
//                                                                //
////////////////////////////////////////////////////////////////////



void TI_CC_SPISetup(void);
void TI_CC_SPIWriteBurstReg(Uchar addr, Uchar *buffer, Uchar count);
void TI_CC_SPIReadBurstReg(Uchar addr, Uchar *buffer, Uchar count);
void Update_AD9854(void);
void Io_Reset_AD9854(void);
void Init_AD9854(void);
void Write_AD9854_Frq1(void);
void Write_AD9854_FrqSW(void);





