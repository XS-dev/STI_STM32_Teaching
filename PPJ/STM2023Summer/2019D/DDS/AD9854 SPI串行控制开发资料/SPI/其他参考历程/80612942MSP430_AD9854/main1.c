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
	BCSCTL1 &= ~XT2OFF ;            //��XT2������XT2OFF��PUC��Ϊ1��
					//��ʾ�ر�	
	do
	{
	IFG1 &= ~ OFIFG ;               //�������ʧЧ��־��OFIFG��PUC��Ϊ1��
					//��ʾ����ʧЧ
	  
	for(iq0 = 0XFF ; iq0 > 0 ; iq0 --) ;//��ʱ���ȴ�XT2����
	}

	while (( IFG1 & OFIFG ) != 0) ;           //��OFIFGΪ1����ʾ����ʧЧ��
						  // ����ѭ�����ȴ�
        BCSCTL2 =SELM_2 + SELS ;                  //ѡ��MCLK ��SMCLK ΪXT2
         _EINT() ;                                //�ز����٣����������������� 
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
