#ifndef _GENERAL	
#define _GENERAL


#define  FREQUENCY  8000     // MCLK的频率为8000KHz ,即1秒钟执行8M个时钟周期
#define  LOOPBODY  8         //MSP430中一个for循环体耗费8个周期

#define  LOOPCNT ( unsigned int )  (( FREQUENCY/LOOPBODY ))
                             //1秒执行8M/8=1M个for循环
                             //即1毫秒执行1000个for循环
                             //即要延时1毫秒需1000个for循环

void DelayMs ( unsigned int ) ;

#endif
