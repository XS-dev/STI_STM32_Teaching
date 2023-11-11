#include "msp.h"
#include "AD9854.h"

void delay_us(uint32_t i)
{
      while(i--);
}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    AD9854_Init();//��ʼ��AD9854
    delay_us(10000);
    AD9854_SetSine_double(1000,2000);//����Ƶ�ʺͷ�ֵ

}

//�������Ҳ�������120MHZ SYSCLKʱ,����10MHZ���Σ����κܺã����Գɹ�
//������300MHZ SYSCLKʱ,����50MHZ����ʱ,DDS��������,�Ҳ���˥������,������35mV����
//
//int main()
//{
//  AD9854_Init();
//  AD9854_SetSine(80000000,4095);
//  while(1);
//}


//�������Ҳ�������120MHZ SYSCLKʱ,����87.697HZ���Σ����κܺã����Գɹ�
//
//int main()
//{
//  AD9854_Init();
//  AD9854_SetSine_double(87.697,4000);
//  while(1);
//}


//����FSK������120MHZ SYSCLK,1K��6K,���Գɹ�,�����Ӧ"FSK����.bmp"

//int main()
//{
//  AD9854_InitFSK();
//  AD9854_SetFSK(1000,6000);
//  while(1)
//  {
//      AD9854_FDATA = 1;
//      delay_us(30000);          //��ʱʱ�䳤�����ڹ۲�
//      AD9854_FDATA = 0;
//      delay_us(30000);
//  }
//}


//����BPSK������120MHZ SYSCLK,���Գɹ�

//int main()
//{
//  AD9854_InitBPSK();
//  AD9854_SetBPSK(0,8192);
//  while(1)
//  {
//      AD9854_FDATA = 1;
//      delay_us(10);
//      AD9854_FDATA = 0;
//      delay_us(10);
//  }
//}



//����OSK������120MHZ SYSCLK,���Գɹ�

//int main()
//{
//  AD9854_InitOSK();
//  AD9854_SetOSK(10);
//  while(1)
//  {
//      AD9854_OSK=1;
//      delay_us(30);
//      AD9854_OSK=0;
//      delay_us(30);
//  }
//}


//����AM������120MHZ SYSCLK,���Գɹ�

//int main()
//{
//  AD9854_InitAM();
//  while(1)
//  {
//      AD9854_SetAM(2000);
//      delay_us(10);
//      AD9854_SetAM(4000);
//      delay_us(10);
//  }
//}
//

//����RFSK������120MHZ SYSCLK,���Գɹ�

//int main()
//{
//  AD9854_InitRFSK();
//  AD9854_SetRFSK(1000,60000,100,30);
//  while(1)
//  {
//      AD9854_FDATA = 1;
//      delay_us(30000);          //��ʱʱ�䳤�����ڹ۲�
//      AD9854_FDATA = 0;
//      delay_us(30000);
//  }
//}

