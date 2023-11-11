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
      IFG1 &= ~OFIFG;		         // �������ʧЧ��־
  for (iq0 = 0xFF; iq0 > 0; iq0--);	// ��ʱ���ȴ�XT2����
   }
   while ((IFG1 & OFIFG) != 0);		// �ж�XT2�Ƿ�����		
   BCSCTL2 |=SELM1+SELS;		//MCLKΪ8MHz��SMCLKΪ8MHz ;                
}

void main( void )
{
     WDTCTL = WDTPW + WDTHOLD ; 
     Initsys();   
     Init_AD9854();
 	 Write_AD9854_Frq1();
     while(1) ;

}
