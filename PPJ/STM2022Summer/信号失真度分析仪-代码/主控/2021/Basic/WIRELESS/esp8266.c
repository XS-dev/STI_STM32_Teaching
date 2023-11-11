#include "esp8266.h"
#include "math.h"

static void timer_delay_ms(u32 time);

static u8 tmp_fft_data[512];

void init_esp8266(void)
{
	USART0PutString("AT+RESTORE\r\n");	//重启
	timer_delay_ms(3000);
	USART0PutString("AT+CWMODE=2\r\n");	//连接模式
	timer_delay_ms(500);
	USART0PutString("AT+CWSAP=\"asdxzcvsd\",\"12345678\",4,3\r\n");	//打开WIFI
	timer_delay_ms(500);
}

void connect_udp(int pc_id)
{
	char string[50];
	sprintf(string,"AT+CIPSTART=\"UDP\",\"192.168.4.%d\",1234\r\n",pc_id);	
	USART0PutString(string);
	timer_delay_ms(600);
}

void send_point(void)
{
	/*char string[100];
	for(int i=0;i<1024;i++)
	{
		sprintf(string,"%d ",save_data_array1[i]);
		USART1PutString(string);
	}*/
	int i=0;
	char screen_message[70];
	USART1PutString("cle 1,0\xff\xff\xff");
	int16_t max_data_point=0x0000,min_data_point=0x03fff;
	for(i=0;i<150;i++)
	{
		if(max_data_point<send_signal[i])
		{
			max_data_point=send_signal[i];
		}
		if(min_data_point>send_signal[i])
		{
			min_data_point=send_signal[i];
		}
	}
	
	float multi=1.0f;
	switch(gears)
	{
		case 1:
			multi=5.0f;
			break;
		case 2:
			multi=20.0f;
			break;
		case 3:
			multi=80.0f;
			break;
	}
	float delta_voltage=((float)(max_data_point-min_data_point)) *3.3f / 0x3fff/multi*0.384615f;
	sprintf(screen_message,"t15.txt=\"x/%0.1f mv\"\xff\xff\xff",delta_voltage*1000);
	USART1PutString(screen_message);
	
	float delta_time=1.0f/(6.0f*(1000.0f/period_point) )*1000.0f;
	sprintf(screen_message,"t14.txt=\"y/%0.1f us\"\xff\xff\xff",delta_time);
	USART1PutString(screen_message);
	
	for(i=0;i<150;i++)
	{
		int point_y=(int)( ((float)(send_signal[i]-min_data_point)) / (max_data_point-min_data_point) *130)+10 ;
		sprintf(screen_message,"add 1,0,%d\xff\xff\xff",point_y);
		USART1PutString(screen_message);
		USART1PutString(screen_message);
	}
	
	
	char message[307]={0};
	message[0]='T';
	
	
	for(i=0;i<150;i++)
	{
		message[1+2*i]=( (u8)(send_signal[i]>>7) ) | ( (u8)(0x80) );
		message[2+2*i]=( (u8)(send_signal[i]) )    | ( (u8)(0x80) );
	}
	
	message[301]=( (u8)(period_point>>7) ) | ( (u8)(0x80) );
	message[302]=( (u8)(period_point) )    | ( (u8)(0x80) );
	message[303]=gears|((u8)0x80);
	
	message[304]='\r';
	message[305]='\n';
	message[306]=0;
	
	
	USART0PutString("AT+CIPSEND=304\r\n");
	timer_delay_ms(50);
	USART0PutString(message);
	timer_delay_ms(800);
}

void send_fft(void)
{
	float max_fft=0;
	int i=0;
	
	char message[520];
	message[0]='F';
	
	message[513]=(u8)((final_index>>21)|0x80);
	message[514]=(u8)((final_index>>14)|0x80);
	message[515]=(u8)((final_index>>7)|0x80);
	message[516]=(u8)((final_index)|0x80);
	message[517]='\r';
	message[518]='\n';
	message[519]=0;
	
	/*for(i=7;i<512;i++)
	{
		if(voltage_fft[i]<=1.0f)
		{
			log_fft[i]=0;
		}
		else 
		{
			log_fft[i]=logf(voltage_fft[i]);
		}
		log_fft[i]=logf(voltage_fft[i]);
	}
	
	for(i=7;i<512;i++)
	{
		if(log_fft[i]>max_fft)
		{
			max_fft=log_fft[i];
		}
		if(log_fft[i]<min_fft)
		{
			min_fft=log_fft[i];
		}
	}
	if(max_fft-min_fft<=0.001f)
	{
		return;
	}
	
	for(i=0;i<7;i++)
	{
		log_fft[i]=min_fft;
	}
	
	for(i=7;i<512;i++)
	{
		tmp_fft_data[i]=(u8) (( (log_fft[i]-min_fft) / (max_fft-min_fft))*127);
		message[1+i]=(u8)(tmp_fft_data[i]|0x80);
	}*/
	
	for(i=10;i<512;i++)
	{
		if(voltage_fft[i]>max_fft)
		{
			max_fft=voltage_fft[i];
		}
	}
	if(max_fft<0.0001f)
	{
		return;
	}
	
	for(i=10;i<512;i++)
	{
		tmp_fft_data[i]=(u8)((voltage_fft[i]/max_fft)*127);
		message[1+i]=(u8)(tmp_fft_data[i]|0x80);
	}
	for(i=0;i<10;i++)
	{
		message[1+i]=0x80;
	}
	
	USART0PutString("AT+CIPSEND=517\r\n");
	timer_delay_ms(50);
	USART0PutString(message);
	timer_delay_ms(1000);
}

void send_THDx(void)
{
	char screen_message[70];
	sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(THDx*10000.0f));
	USART1PutString(screen_message);
	sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(base_ele*10000.0f));
	USART1PutString(screen_message);
	sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(two_ele*10000.0f));
	USART1PutString(screen_message);
	sprintf(screen_message,"x3.val=%d\xff\xff\xff",(int)(three_ele*10000.0f));
	USART1PutString(screen_message);
	sprintf(screen_message,"x4.val=%d\xff\xff\xff",(int)(four_ele*10000.0f));
	USART1PutString(screen_message);
	sprintf(screen_message,"x5.val=%d\xff\xff\xff",(int)(five_ele*10000.0f));
	USART1PutString(screen_message);
	
	char message[16];
	message[0]='D';
	
	u16 tmp_data=(u16)(THDx*0x2000);
	message[1]=( (u8)(tmp_data>>7) ) | ( (u8)(0x80) );
	message[2]=( (u8)(tmp_data) )    | ( (u8)(0x80) );
	
	tmp_data=(u16)(base_ele*0x2000);
	message[3]=( (u8)(tmp_data>>7) ) | ( (u8)(0x80) );
	message[4]=( (u8)(tmp_data) )    | ( (u8)(0x80) );
	
	tmp_data=(u16)(two_ele*0x2000);
	message[5]=( (u8)(tmp_data>>7) ) | ( (u8)(0x80) );
	message[6]=( (u8)(tmp_data) )    | ( (u8)(0x80) );
	
	tmp_data=(u16)(three_ele*0x2000);
	message[7]=( (u8)(tmp_data>>7) ) | ( (u8)(0x80) );
	message[8]=( (u8)(tmp_data) )    | ( (u8)(0x80) );
	
	tmp_data=(u16)(four_ele*0x2000);
	message[9]=( (u8)(tmp_data>>7) ) | ( (u8)(0x80) );
	message[10]=( (u8)(tmp_data) )    | ( (u8)(0x80) );
	
	tmp_data=(u16)(five_ele*0x2000);
	message[11]=( (u8)(tmp_data>>7) ) | ( (u8)(0x80) );
	message[12]=( (u8)(tmp_data) )    | ( (u8)(0x80) );
	
	message[13]='\r';
	message[14]='\n';
	message[15]=0;
	
	USART0PutString("AT+CIPSEND=13\r\n");
	timer_delay_ms(50);
	USART0PutString(message);
	timer_delay_ms(200);
}



void timer_delay_ms(u32 time)
{
    for(int i=0;i<time*3500;i++);
}



