

////////////////////////////////////////////////////////////////////
//                                                                //
//                             INSTRUCTION BYTE                   //
//                                                                //
////////////////////////////////////////////////////////////////////


//******************************************************************
//Ð´
#define	  AD9854_PHA1       {0,0,0,0,0,0,0,0}        // 2 Bytes
#define	  AD9854_PHA2       {0,0,0,0,0,0,0,1}        // 2 Bytes 
#define	  AD9854_FRE1       {0,0,0,0,0,0,1,0}        // 6 Bytes	
#define	  AD9854_FRE2       {0,0,0,0,0,0,1,1}        // 6 Bytes
#define	  AD9854_DELTA      {0,0,0,0,0,1,0,0}        // 6 Bytes
#define	  AD9854_UPDATA     {0,0,0,0,0,1,0,1}        // 4 Bytes
#define	  AD9854_RAMP_CLK   {0,0,0,0,0,1,1,0}        // 3 Bytes
#define	  AD9854_CTR_REG    {0,0,0,0,0,1,1,1}        // 4 Bytes
#define	  AD9854_I_MUL      {0,0,0,0,1,0,0,0}        // 2 Bytes
#define	  AD9854_Q_MUL      {0,0,0,0,1,0,0,1}        // 2 Bytes
#define	  AD9854_SHAPED     {0,0,0,0,1,0,1,0}        // 1 Bytes
#define	  AD9854_Q_DAC      {0,0,0,0,1,0,1,1}        // 2 Bytes
//******************************************************************
//¶Á
//******************************************************************

    
#define AD9854_CS_UP       P6OUT |= BIT0
#define AD9854_CS_DOWN     P6OUT &= ~BIT0   //Æ¬Ñ¡
#define AD9854_SCLK_UP     P6OUT |= BIT1
#define AD9854_SCLK_DOWN   P6OUT &= ~BIT1
#define AD9854_UPDATE_UP   P6OUT |= BIT2
#define AD9854_UPDATE_DOWN P6OUT &= ~BIT2
#define AD9854_SDIO_UP     P6OUT |= BIT3
#define AD9854_SDIO_DOWN   P6OUT &= ~BIT3
#define AD9854_IO_RESET_UP    P6OUT |= BIT4
#define AD9854_IO_RESET_DOWN  P6OUT &= ~BIT4
#define  HARDWARE_AD9854   P6DIR |= 0XFF 
////////////////////////////////////////////////////////////////////
//                                                                //
//                          VARIABLES   DEFINITION                //
//                                                                //
////////////////////////////////////////////////////////////////////


extern unsigned char ctr[48] ;


void Write_AD9854_C(unsigned char *command)  ;
void Write_AD9854_D(unsigned char *data) ;
void Write_AD9854_Frq1(unsigned char * frq1) ;
void Update_AD9854(void) ;
void Io_Reset_AD9854(void) ;
void Ctr_AD9854(unsigned char *ctr) ;
void Init_AD9854(void) ;




