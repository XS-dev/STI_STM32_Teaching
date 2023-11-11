#include "lcd.h"

int wave_result[480] = {0};

void bar(double process)
{
//	char screen_message[70];
//	sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(process));
//	USART1PutString(screen_message);	
}

void sendresult(int number)
{
//	char screen_message[70];
//	sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(number));
//	USART1PutString(screen_message);
//	
//	sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(number));
//	USART1PutString(screen_message);
}

void sendwave(int wave)
{
	char screen_message[70];
//	for(int i = 0; i < 480; i++)
//	{
//		sprintf(screen_message,"add 10,0,%d\xff\xff\xff",(int)(wave));
//		USART1PutString(screen_message);
//	}
 
	
}


void display_guzhang(void)
{
//	switch(guzhang_flag)
//	{
//		case 0 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"电路正常\"\xff\xff\xff");
//			}
//			break;
//			
//		case 1 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R1断路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 2 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R2断路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 3 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R3断路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 4 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R4断路\"\xff\xff\xff");
//			}
//		break;
//		
//		case 5 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R1短路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 6 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R2短路\"\xff\xff\xff");
//			}
//		break;
//			
//		
//			
//		case 7 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R3短路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 8 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"R4短路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 9 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"C1断路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 10 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"C2断路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 11 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"C3断路\"\xff\xff\xff");
//			}
//		break;
//			
//		case 12 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"C1两倍\"\xff\xff\xff");
//			}
//		break;
//			
//		case 13 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"C2两倍\"\xff\xff\xff");
//			}
//		break;
//			
//		case 14 :
//			for(int i = 0;i<5;i++)
//			{
//				USART1PutString("t6.txt=\"C3两倍\"\xff\xff\xff");
//			}
//		break;
//	}

}

void show_delta(void)
{
//	char screen_message[70];
//	sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(INResistor*100));
//	USART1PutString(screen_message);
//	
//	sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(OUResistor*100));
//	USART1PutString(screen_message);
//	
//	sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(K1ZE*100));
//	USART1PutString(screen_message);	

//	sprintf(screen_message,"x3.val=%d\xff\xff\xff",(int)(UPFre*100));
//	USART1PutString(screen_message);
//	
//	sprintf(screen_message,"x4.val=%d\xff\xff\xff",(int)(x_pic*100));
//	USART1PutString(screen_message);

//	sprintf(screen_message,"x5.val=%d\xff\xff\xff",(int)(y_pic*100));
//	USART1PutString(screen_message);
//	
//	display_guzhang();
}

void clean_wave(void)
{
//	USART1PutString("cle 10,0\xff\xff\xff");
}





