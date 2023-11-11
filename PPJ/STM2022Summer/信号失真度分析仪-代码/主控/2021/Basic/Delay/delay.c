//#include "delay.h"
//#include "main.c"
//#define clock_source 48    //时钟频率填写到这里（单位MHz）    

////void delay_us(u32 us){ //uS微秒级延时程序
////} 
////	SysTick_disableInterrupt();   //禁用时钟中断
////	SysTick_setPeriod(us*clock_source);	//加载计数值
////	SysTick->VAL=0x00;           //清空计数器
////	SysTick_enableModule();   //使能系统时钟
////	while(SysTick_getValue()&(us*clock_source));
////	SysTick->VAL=0x00;        //清空计数器
////	SysTick_disableModule();//关闭计数
////}

//void delay_ms(u16 ms){ //mS毫秒级延时程序 		  	  
//	while( ms-- != 0){
//		delay_us(1000);	
//	}
//}

//void delay_s(u16 s){ //S秒级延时程序 		  	  
//	while( s-- != 0){
//		delay_ms(1000);	
//	}
//}





