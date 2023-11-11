#include  <msp430x16x.h>
#include "AD9854.h"

//control function register  32bitS;


      unsigned char ctr[]={0,0,0,1,0,1,0,0,       //comp pd dowm  ctr[3]=0 //qac pd down ctr[5]=0
                           0,1,0,0,0,1,0,1,       //no pll pass ctr[10]=0  //multi times 5 ctr[11-15]=00101  
			   0,0,0,0,0,0,0,0,       //ext update ctr[23]=0
                           0,0,1,0,0,0,0,0  };    //osk defoult ctr[26]=1  //msb first ctr[30]=0 //no sdo active ctr[31]=0
void Initsys()
{ 
        unsigned int iq0 ;
	BCSCTL1 &= ~XT2OFF ;            //打开XT2振荡器，XT2OFF在PUC后为1，
					//表示关闭	
	do
	{
	IFG1 &= ~ OFIFG ;               //清除振荡器失效标志，OFIFG在PUC后为1，
					//表示振荡器失效
	  
	for(iq0 = 0XFF ; iq0 > 0 ; iq0 --) ;//延时，等待XT2起振
	}

	while (( IFG1 & OFIFG ) != 0) ;           //若OFIFG为1，表示振荡器失效，
						  // 继续循环，等待
        BCSCTL2 =SELM_2 + SELS ;                  //选择MCLK ，SMCLK 为XT2
         _EINT() ;                                //必不可少！！！！！！！！！ 
}


void main( void )
{
     unsigned char a[48]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
     WDTCTL = WDTPW + WDTHOLD ; 
     Initsys() ;   
     Init_AD9854() ;
     Write_AD9854_Frq1(a) ;
     while(1) ;

}
