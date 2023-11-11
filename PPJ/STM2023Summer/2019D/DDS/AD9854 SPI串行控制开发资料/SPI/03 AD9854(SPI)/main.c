#include  <msp430x14x.h>
#include"AD9854_SPI.h"
#include "general.h"
//control function register  32bitS;


void Initsys()
{
   unsigned int iq0;
   _DINT();
   BCSCTL1 &=~XT2OFF;
   do
   {
      IFG1 &= ~OFIFG;		         // 清除振荡器失效标志
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// 延时，等待XT2起振
   }
   while ((IFG1 & OFIFG) != 0);		// 判断XT2是否起振		
   BCSCTL2 |=SELM1+SELS;		//MCLK为8MHz，SMCLK为8MHz ;                
}

void main( void )
{
     WDTCTL = WDTPW + WDTHOLD ; 
     Initsys();   
     Init_AD9854();
 	 Write_AD9854_Frq1();
     while(1) ;

}
