#include "msp.h"
#include "AD9854.h"

void delay_us(uint32_t i)
{
      while(i--);
}

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    AD9854_Init();//初始化AD9854
    delay_us(10000);
    AD9854_SetSine_double(1000,2000);//设置频率和幅值

}

//测试正弦波，采用120MHZ SYSCLK时,出来10MHZ波形，波形很好，测试成功
//当采用300MHZ SYSCLK时,测试50MHZ波形时,DDS发热厉害,且波形衰减严重,幅度在35mV左右
//
//int main()
//{
//  AD9854_Init();
//  AD9854_SetSine(80000000,4095);
//  while(1);
//}


//测试正弦波，采用120MHZ SYSCLK时,出来87.697HZ波形，波形很好，测试成功
//
//int main()
//{
//  AD9854_Init();
//  AD9854_SetSine_double(87.697,4000);
//  while(1);
//}


//测试FSK，采用120MHZ SYSCLK,1K和6K,测试成功,结果对应"FSK波形.bmp"

//int main()
//{
//  AD9854_InitFSK();
//  AD9854_SetFSK(1000,6000);
//  while(1)
//  {
//      AD9854_FDATA = 1;
//      delay_us(30000);          //延时时间长，便于观察
//      AD9854_FDATA = 0;
//      delay_us(30000);
//  }
//}


//测试BPSK，采用120MHZ SYSCLK,测试成功

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



//测试OSK，采用120MHZ SYSCLK,测试成功

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


//测试AM，采用120MHZ SYSCLK,测试成功

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

//测试RFSK，采用120MHZ SYSCLK,测试成功

//int main()
//{
//  AD9854_InitRFSK();
//  AD9854_SetRFSK(1000,60000,100,30);
//  while(1)
//  {
//      AD9854_FDATA = 1;
//      delay_us(30000);          //延时时间长，便于观察
//      AD9854_FDATA = 0;
//      delay_us(30000);
//  }
//}

