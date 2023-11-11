#include "measure.h"


static void amplitude(void);
static int find_max_index(int begin);
static void calculate_THDx(void);
static void find_muti(void);
static void get_signal(void);
static void inter_data(int length,int dst_length,uint16_t source_data[],uint16_t dst_data[]);

extern void send_THDx(void);
extern void send_point(void);
extern void send_fft(void);

uint32_t final_index;

float signal_fre;
float base_ele,two_ele,three_ele,four_ele,five_ele,THDx;
int fre_index2;
float voltage_peek;
uint16_t send_signal[150];
uint16_t period_point;

void calculate_hanning(void)
{
	int i=0;
	for(i=0;i<1024;i++)
	{
			Hanning[i]=0.5f*(1-cosf(6.283185307f*i/1023));
	}
}


void voltage_process(void)
{
	//char string[40];
	
	#define MUL_find 12.5663704f
	
	find_muti();
	
	uint32_t i=0;
	
	uint32_t max_index1=1,fre_index1=0,max_index2=1;fre_index2=0;
	
	final_index=1;
	
	signal_fre=0;
	
	Change_Simple_Rate(1000000);
	start_DMA();	
	for(i=0;i<1024;i++)
	{
		voltage_before_fft[i]=((float)data_array1[i]);
	}
	arm_rfft_fast_f32(&_1024_fft,voltage_before_fft, voltage_fft, 0);
	amplitude();

	max_index1=find_max_index(1);
	
	
	if(((float)max_index1)*MUL_find*1000<1000000)
	{
		fre_index1=(uint32_t) ( ((float)max_index1)*MUL_find*1000 );
		if(fre_index1==0)
		{
			fre_index1=1;
		}
	}
	else
	{
		fre_index1=1000000;
	}
	
	Change_Simple_Rate(fre_index1); 
	
	start_DMA();
	for(i=0;i<1024;i++)
	{
		voltage_before_fft[i]=((float)data_array1[i]);
	}
	arm_rfft_fast_f32(&_1024_fft,voltage_before_fft, voltage_fft, 0);
	amplitude();
		
	max_index2=find_max_index(1);
	signal_fre=(12000000.0f/(12000000/fre_index1))/1024.0f*max_index2;

	period_point=(uint16_t) ((signal_fre/200000.0f)*0x3fff+0.5f);
	
	/*sprintf(string,"frequency=%f  ",signal_fre);
	USART1PutString(string);*/											//--------------------------------------
	
	
//-----------------------------------------------------------------------------------------------------	
	
	
	
	if(signal_fre<10.0f)
	{
		return;
	}
	else if(signal_fre<1064.0f)											//-------------------------------- low fre
	{
		final_index=16500;
	}
	else
	{
		if(signal_fre<48000.0f)
		{
			if( (uint32_t)(signal_fre*18.5132437f) <2000000)
			{
				final_index=(uint32_t) (signal_fre*18.5132437f);
				if(final_index==0)
				{
					final_index=1;
				}
			}
			else
			{
				final_index=2000000;
			}
		}
		else if(signal_fre<63000.0f)
		{
			final_index=1090900;
		}
		else if(signal_fre<73000.0f)
		{
			final_index=1333000;
		}
		else
		{
			final_index=1714000;
		}
		
		/**/
	}
	
	/*sprintf(string,"sample=%d\n",final_index);
	USART1PutString(string);*/

	Change_Simple_Rate(final_index);
	start_DMA();

	for(i=0;i<1024;i++)
	{
		voltage_before_fft[i]=((float)data_array1[i])*Hanning[i];				///-----------------shi fou jia chuang------------
		/*sprintf(string,"%d ",data_array1[i]);
		USART1PutString(string);*/
	}
	arm_rfft_fast_f32(&_1024_fft,voltage_before_fft, voltage_fft, 0);
	amplitude();
	/*for(i=0;i<512;i++)
	{
		sprintf(string,"%e ",voltage_fft[i]);
		USART1PutString(string);
	}*/
	
	calculate_THDx();

	get_signal();

	send_fft();
	send_point();
	send_THDx();
}

void find_muti(void)
{
	if(gears==1)
	{
		peek_measure(5.0f);
		if(voltage_peek<0.14f)
		{
			gears=2;
			ADC14Init(2);
			peek_measure(20.0f);
			if(voltage_peek<0.030f)
			{
				gears=3;
				ADC14Init(3);
			}
			return;
		}
	}
	else if(gears==2)
	{
		peek_measure(20.0f);
		if(voltage_peek<0.030f)
		{
			gears=3;
			ADC14Init(3);
		}
		else if(voltage_peek>0.150f)
		{
			gears=1;
			ADC14Init(1);
		}
	}
	else 
	{
		peek_measure(80.0f);
		if(voltage_peek>0.034f)
		{
			gears=2;
			ADC14Init(2);
			peek_measure(20.0f);
			if(voltage_peek>0.160f)
			{
				gears=1;
				ADC14Init(1);
			}
		}
	}
}

void calculate_THDx(void)			// fang bo  0.38873   sanjiaobo 0.118
{
	static u8 range=4;
	int i=0,index1=0,index2=0,index3=0,index4=0,index5=0;
	base_ele=0;two_ele=0;three_ele=0;four_ele=0;five_ele=0,THDx=0;
	

	int max_index=find_max_index(7);
	
	//period_point=(uint16_t) ((uint16_t)(1024/max_index+0.5)) * ( 1000000.0f/12000000.0f*(12000000/final_index) );  //-------------------------------------later 
	
	
	/*char string[120];
	for(int i=0;i<512;i++)
	{
		sprintf(string,"%e ",voltage_fft[i]);
		USART1PutString(string);
	}*/
	
	for(i=-range;i<=range;i++)
	{
		index1=max_index+i;
		if(index1>0&&index1<512)
		{
			base_ele+=voltage_fft[index1];
		}	
		
		index2=2*max_index+i;
		if(index2>0&&index2<512)
		{
			two_ele+=voltage_fft[index2];
		}	
		
		index3=3*max_index+i;
		if(index3>0&&index3<512)
		{
			three_ele+=voltage_fft[index3];
		}		
		
		index4=4*max_index+i;
		if(index4>0&&index4<512)
		{
			four_ele+=voltage_fft[index4];
		}		
		
		index5=5*max_index+i;
		if(index5>0&&index5<512)
		{
			five_ele+=voltage_fft[index5];
		}	
	}
	
	if(signal_fre>51000.0f)
	{
		two_ele*=0.94322944f;
	}
	if(signal_fre>34000.0f)
	{
		three_ele*=0.94770225f;
	}
	if(signal_fre>51000.0f)
	{
		four_ele*=0.95101504f;
	}
	if(signal_fre>51000.0f)
	{
		five_ele*=0.962361f;
	}
	
	THDx=sqrtf(two_ele+three_ele+four_ele+five_ele)/sqrt(base_ele);
	
	base_ele=sqrtf(base_ele);
	two_ele=sqrtf(two_ele);
	three_ele=sqrtf(three_ele);
	four_ele=sqrtf(four_ele);
	five_ele=sqrtf(five_ele);
	
	//float total=base_ele+two_ele+three_ele+four_ele+five_ele;
	if(base_ele!=0)
	{
		two_ele/=base_ele;
		three_ele/=base_ele;
		four_ele/=base_ele;
		five_ele/=base_ele;
		base_ele=1.0f;
	}
		

	/*sprintf(string,"thdx=%f 1=%f 2=%f 3=%f 4=%f 5=%f\n",THDx,base_ele,two_ele,three_ele,four_ele,five_ele);
	USART1PutString(string);*/
}

int find_max_index(int begin)
{
	int i=0;
	float max_fft=-1;
	int max_index=1;
	for(i=begin;i<512;i++)
	{
		if(voltage_fft[i]>max_fft)
		{
			max_fft=voltage_fft[i];
			max_index=i;
		}
	}
	return max_index;
}

void amplitude(void)
{
	int i=0;
	for(i=0;i<512;i++)
	{
		voltage_fft[i]=pow(voltage_fft[2*i],2)+pow(voltage_fft[2*i+1],2);
	}
}

void peek_measure(float multi)
{
	uint16_t tmp_max=0x0000,tmp_min=0xffff;
	
	Change_Simple_Rate(2000000);
	start_DMA();
	for(int i=0;i<1024;i++)
	{
		if(data_array1[i]>tmp_max)
		{
			tmp_max=data_array1[i];
		}
		if(data_array1[i]<tmp_min)
		{
			tmp_min=data_array1[i];
		}
	}
	
	Change_Simple_Rate(1000);
	start_DMA();
	for(int i=0;i<1024;i++)
	{
		if(data_array1[i]>tmp_max)
		{
			tmp_max=data_array1[i];
		}
		if(data_array1[i]<tmp_min)
		{
			tmp_min=data_array1[i];
		}
	}
	
	voltage_peek=((float)(tmp_max-tmp_min))*3.3f/0x3fff/multi;
}

void get_signal(void)
{
	
	if(signal_fre<10.0f)
	{
		for(int i=0;i<150;i++)
		{
			send_signal[i]=0;
		}
	}
	else
	{
		int fre_index_3;
		if((uint32_t)(signal_fre*100)<1)
		{
			fre_index_3=1;
		}
		else if((uint32_t)(signal_fre*100)<2000000)
		{
			fre_index_3=(uint32_t)(signal_fre*100);
		}
		else
		{
			fre_index_3=2000000;
		}
		Change_Simple_Rate(fre_index_3);
		start_DMA();
		
		uint32_t period_point=(uint32_t)(12000000.f/(12000000/fre_index_3)/signal_fre+0.5f);
		if(period_point>=1023)
		{
			period_point=1023;
		}
		
		inter_data(period_point,150,data_array1,send_signal);
	}	
}

void inter_data(int length,int dst_length,uint16_t source_data[],uint16_t dst_data[])
{
	if(length>=1024||length<=2)
	{
		return;
	}
	
	
	int i=0;int left_index;float position;
	float div=((float)length)/((float)dst_length);
	
	for(i=0;i<dst_length;i++)
	{
		position=div*i;
		left_index=(int)position;
		if(length>=600)
		{
			dst_data[i]=(uint16_t) (((float)(source_data[left_index+1]-source_data[left_index]))*(position-left_index)+source_data[left_index]);	
		}
		else
		{
			dst_data[i]=(uint16_t) (((float)(source_data[left_index+301]-source_data[left_index+300]))*(position-left_index)+source_data[left_index+300]);	
		}
	}
}
