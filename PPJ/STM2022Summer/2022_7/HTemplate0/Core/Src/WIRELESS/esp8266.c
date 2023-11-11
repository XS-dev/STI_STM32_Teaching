#include "esp8266.h"

int wave_type=3;
uint32_t 	mf=0;

void init_esp8266(void)
{
	USART0PutString("AT+RESTORE\r\n");	//    
	Delay_Ms(3000);
	USART0PutString("AT+CWMODE=2\r\n");	//    ??
	Delay_Ms(500);
	USART0PutString("AT+CWSAP=\"asdxzcvsd\",\"12345678\",4,3\r\n");	//  WIFI
	Delay_Ms(500);
}

void connect_udp(int pc_id)
{
	char string[50];
	sprintf(string,"AT+CIPSTART=\"UDP\",\"192.168.4.%d\",1234\r\n",pc_id);	
	USART0PutString(string);
	Delay_Ms(600);
}

void send_fft(void)
{
	float max_fft=0;
	int i=0;
	
	char message[520] = {0};
	message[0]='T';
	message[1]=( (u8)(wave_type)) | ( (u8)(0x80) );	//WAVE_TYPE：波的类型 1，2，3
	message[2]=( (u8)((uint16_t)AMDMF>>7) ) | ( (u8)(0x80) );	//mf：调制度 
	message[3]=( (u8)((uint16_t)AMDMF) )    | ( (u8)(0x80) );

	message[517]='\r';
	message[518]='\n';
	message[519]=0;
//	for(i=10;i<512;i++)
//	{
//		if(voltage_fft[i]>max_fft)
//		{
//			max_fft=voltage_fft[i];
//		}
//	}
//	if(max_fft<0.0001f)
//	{
//		return;
//	}
//	


//	for(i=10;i<512;i++)
//	{
//		//tmp_fft_data[i]=(u8)((voltage_fft[i]/max_fft)*127);		//归一化处理后乘2^14，放入数组
//		//message[1+i]=(u8)(tmp_fft_data[i]|0x80);
//	}
//	for(i=4;i<10;i++)
//	{
//		message[1+i]=0x80;
//	}
	
	USART0PutString("AT+CIPSEND=517\r\n");
	Delay_Ms(50);
	USART0PutString(message);
	Delay_Ms(1000);
}




