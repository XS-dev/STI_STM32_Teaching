#ifndef _GENERAL	
#define _GENERAL


#define  FREQUENCY  8000     // MCLK��Ƶ��Ϊ8000KHz ,��1����ִ��8M��ʱ������
#define  LOOPBODY  8         //MSP430��һ��forѭ����ķ�8������

#define  LOOPCNT ( unsigned int )  (( FREQUENCY/LOOPBODY ))
                             //1��ִ��8M/8=1M��forѭ��
                             //��1����ִ��1000��forѭ��
                             //��Ҫ��ʱ1������1000��forѭ��

void DelayMs ( unsigned int ) ;

#endif
