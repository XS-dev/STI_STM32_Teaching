AD9854程序 
贴子发表于：2008/7/27 8:45:35

  欢迎参与调查  
 
     


#include<AT89X52.H>  //晶振可以用11.0592MHZ，如果用串口的话
                     //提示：在调试程序的时候晶振用12MHZ

#define HC_573_C      P2_7
#define MASTER_RESET  P2_1
#define IO_UP         P2_6
#define WRB_SCLK      P2_5
#define RDB_CSB       P2_4
#define FSK_BPSK_HOLD P2_3
#define SHAPED_LEYING P2_2

void  AD9854_F();
void  AD9854_IO_INT();
void  DLY_400MS();
void  TAB_DataWord();
void  F_DataWord();
void  V_Int();

unsigned char temp;
//unsigned char UPFLAG;
unsigned char TAB_Data[40];
unsigned char F_Data[6];
void main()
 { 
 V_Int();
 while(1){
 TAB_DataWord();
 F_DataWord();
  while(1)
    {
    if(!P1_0)
    { 
    AD9854_F();
    }  
    if(!P1_1)
    { 
    AD9854_IO_INT();
    }
 if(!P1_2)
 { 
    MASTER_RESET=1;
        }
   SHAPED_LEYING=1;
   MASTER_RESET=0;
   HC_573_C=0;
    }
                      }
   }

/***********************************************************************************************/
void TAB_DataWord()
{
 TAB_Data[0]=0X00;
 TAB_Data[1]=0X00;       //00H Phase Adjust Register #1 <13:8> (Bits 15, 14 don’t care) Phase #1 相位为0
    //01H Phase Adjust Register #1 <7:0> 01H
 TAB_Data[2]=0X00;  //02H Phase Adjust Register #2 <13:8> (Bits 15, 14 don’t care) Phase #2 相位为0
 TAB_Data[3]=0X00;       //03H Phase Adjust Register #1 <7:0> 03H
     
 TAB_Data[4]=0X00;  //Frequency Tuning Word 1 <47:40>//0000431BDE83        
 TAB_Data[5]=0X10;  //Frequency Tuning Word 1 <39:32>
 TAB_Data[6]=0X43;  //Frequency Tuning Word 1 <31:24>
 TAB_Data[7]=0X1B;  //Frequency Tuning Word 1 <23:16> 
 TAB_Data[8]=0XDE;  //Frequency Tuning Word 1 <15:8>
 TAB_Data[9]=0X83;       //Frequency Tuning Word 1 <7:0>
  
 TAB_Data[10]=0X00;  //Frequency Tuning Word 2 <47:40
 TAB_Data[11]=0X00;  //Frequency Tuning Word 2 <39:32>
 TAB_Data[12]=0X43;  //Frequency Tuning Word 2 <31:24>
 TAB_Data[13]=0X1B;  //Frequency Tuning Word 2 <23:16>
 TAB_Data[14]=0XDE;  //Frequency Tuning Word 2 <15:8>
 TAB_Data[15]=0X83;  //Frequency Tuning Word 2 <7:0> //500KHZ

 TAB_Data[16]=0X01;  //Delta Frequency Word <47:40>
 TAB_Data[17]=0X47;  //Delta Frequency Word <39:32>
 TAB_Data[18]=0XAE;  //Delta Frequency Word <31:24>
 TAB_Data[19]=0X14;  //Delta Frequency Word <23:16>
 TAB_Data[20]=0X7A;  //Delta Frequency Word <15:8>
 TAB_Data[21]=0XE1;  //Delta Frequency Word <7:0> 三角波  //频率为0

TAB_Data[22]=0X00;  //Update Clock <31:24>
TAB_Data[23]=0X00;  //Update Clock <23:16>
TAB_Data[24]=0X00;  //Update Clock <15:8>
TAB_Data[25]=0XF0;  //Update Clock <7:0>         //系统出现寄存器更新信号reg. Int Update Clk.=0;外部更新

TAB_Data[26]=0X00;  //Ramp Rate Clock <19:16> (Bits 23, 22, 21, 20 don’t care)
TAB_Data[27]=0X00;  //Ramp Rate Clock <15:8>
TAB_Data[28]=0X00;  //Ramp Rate Clock <7:0>

TAB_Data[29]=0X00;  //Don't Care(0),Don't Care(0),Don't Care(0),Comp PD(0),Reserved_Always Low(0),QDAC PD(0),DAC PD(0),DIG PD(0).
TAB_Data[30]=0X60;       //Don't Care(0),PLL Range(1),Bypass PLL(1),Ref Mult 4(0),Ref Mult 3(0),Ref Mult 2(0),Ref Mult 1(0),Ref Mult 0(0).
TAB_Data[31]=0X00;  //CLR ACC1(0),CLR ACC2(0),Triangle(0)(三角波),SRC QDAC(0),Mode 2(0),Mode 1(0),Mode 0(0),Int Update Clk(0). 注意
TAB_Data[32]=0X40;  //Don't Care(0),Bypass_Inv_Sinc(0),OSK EN(0),OSK INT(0),Don't Care(0),Don't Care(0),LSB First(0),SDO_Active(0).

TAB_Data[33]=0X00;  //Output Shape Key I Mult <11:8> (Bits 15, 14, 13, 12 don’t care)
TAB_Data[34]=0X0F;  //Output Shape Key I Mult <7:0>
                       
TAB_Data[35]=0X00;       //Output Shape Key Q Mult <11:8> (Bits 15, 14, 13, 12 don’t care)
TAB_Data[36]=0X0F;       //Output Shape Key Q Mult <7:0>

TAB_Data[37]=0X0F;       //Output Shape Key Ramp Rate <7:0>
 
TAB_Data[38]=0X00;       //QDAC <11:8> (Bits 15, 14, 13, 12 don’t care)
TAB_Data[39]=0X0F;       //QDAC <7:0> (Data is required to be in twos complement format)

}
/**********************************************************************************************/
void F_DataWord()
{
 F_Data[0]=0X00; //Frequency Tuning Word 1 <47:40>//00029F16B11C//0000A7C5AC47
 F_Data[1]=0X02; //Frequency Tuning Word 1 <39:32>
 F_Data[2]=0X9F; //Frequency Tuning Word 1 <31:24>
 F_Data[3]=0X16; //Frequency Tuning Word 1 <23:16> 
 F_Data[4]=0XB1; //Frequency Tuning Word 1 <15:8>
 F_Data[5]=0X1C;        //Frequency Tuning Word 1 <7:0> //
}

/***********************************************************************************************/
void  AD9854_F() 
 {   
  unsigned char i;           
  unsigned char tempf;  //   HC_573_C=0 ;选通
  MASTER_RESET=0;
  RDB_CSB=1;
  WRB_SCLK=0;
  IO_UP=0;
  tempf="4";
  for(i=0;i<6;i++)
 {     
  HC_573_C=1;          //选通地址
  P0=tempf;
  HC_573_C=0;          //关闭HC573
  ACC="F"_Data[i];    
  P0=ACC;     
  WRB_SCLK=0;
  WRB_SCLK=1;
  tempf++;
          }     
 
  WRB_SCLK=1;
  
  IO_UP=0;
  IO_UP=1;             
  }    
/************************************************************************************************/
void AD9854_IO_INT()
{ 
  unsigned char i;
  DLY_400MS();
  MASTER_RESET=0;
  MASTER_RESET=0;
  FSK_BPSK_HOLD =1; //多功能管脚
  SHAPED_LEYING =1;     //Must First Be Selected in the Programming Control Register
          //to Function. A logic high will cause the I and Q DAC outputs 
   //to ramp-up from zero-scale to full-scale amplitude at a preprogrammed
   //rate.Logic low causes the full-scale output to ramp-down 
          //to zero-scale at the preprogrammed rate.
  RDB_CSB=1;            //Active LOW. This pin is shared with RDB when
  WRB_SCLK=0;           //并行写数据时钟.低电平有效
  IO_UP=0;              //数据写入准备
  temp="0";         //表格首数据地址
          //AD9854 寄存器首地址
  for(i=0;i<40;i++)
 {  
  HC_573_C=1;
  P0=temp;  //送地址 
  HC_573_C=0;
                //取对应地址的数据
  ACC="TAB"_Data[i];
  P0=ACC;
  WRB_SCLK=0;
  WRB_SCLK=1;
  temp++;
  }
  WRB_SCLK=1;         //关闭数据接收
  IO_UP=0;
  IO_UP=1;
   }

/**********************************************************************/
void V_Int()
 {          
  unsigned char tempf;  //   HC_573_C=0 ;选通
  MASTER_RESET=0;
  RDB_CSB=1;
  WRB_SCLK=0;
  tempf="0X1F";    
  HC_573_C=1;          //选通地址
  P0=tempf;
  HC_573_C=0;          //关闭HC573
  ACC="0X00";    
  P0=ACC;     
  WRB_SCLK=0;
  WRB_SCLK=1;
  DLY_400MS();
  WRB_SCLK=1;
  DLY_400MS();             
  }    

  
/**************************************************************************/

void DLY_400MS()
{ 
 unsigned char i,j;
 for(i=0;i<90;i++)
 {
 for(j=0;j<60;j++);
 } 
 }  
