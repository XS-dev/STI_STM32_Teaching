#include "display.h"

void show_Input_res(float InputRes)
{
	for(int i = 0; i < 480; i++)
	{
		sprintf(screen_message,"add 10,0,%d\xff\xff\xff",(int)(0));
		USART7PutString(screen_message);
	}
	sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(InputRes*100));
//	printf("%f\r\n",InputRes);
	USART7PutString(screen_message);
}


void show_Output_res(float OutputRes)
{
	sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(OutputRes*100));
	USART7PutString(screen_message);
}

void show_Gain(float Gain)
{
	sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(Gain*100));
	USART7PutString(screen_message);
}

void show_x_ray(void)
{
	sprintf(screen_message,"x4.val=%d\xff\xff\xff",(int)(1600));
	USART7PutString(screen_message);
}

void show_Upper_K(float Upper_K)
{
	sprintf(screen_message,"x3.val=%d\xff\xff\xff",(int)(Upper_K*100));
	USART7PutString(screen_message);
}



void sendwave(void)
{
//	char screen_message[70];
	for(int i = 0; i < 473; i++)
	{
		sprintf(screen_message,"add 10,0,%d\xff\xff\xff",(int)(scan_data[472-i]));
		USART7PutString(screen_message);
	}
}

void display_Error(void)
{
	switch(Error_flag)
	{
		case 0 :
			for(int i = 0;i<5;i++)
			{
//				USART7PutString("t6.txt=\"电路正常\"\xff\xff\xff");
			}
			break;
			
		case 1 :
			for(int i = 0;i<5;i++)
			{
//				USART7PutString("t6.txt=\"R1断路\"\xff\xff\xff");
			}
		break;
	}

}


