#include "Measure.h"
void QuickSort(uint16_t arr[], int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }
 
            if(i < j)
            {
                arr[i++] = arr[j];
            }
 
            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }
 
            if(i < j)
            {
                arr[j--] = arr[i];
            }
        }
 
        arr[i] = k;
 
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }

}

void Mea_Input(int mode)
{
	for (u16 temp = 0; temp< 1000;temp++)
	{
		comp[temp] = adc3_data[temp+500];
	}

	QuickSort(comp,0,999);

	InputAC = (comp[950]-comp[50])*3300/65536;
	if(mode == 1)
	{InputAC_kailu = InputAC;}
	if(mode == 2)
	{
		InputRes = InputAC_kailu/(InputAC-InputAC_kailu)*6.73;
	}
}


void Mea_Output(int mode)
{
		OutputAC = 0;
		for(u16 outtemp = 0;outtemp < 10;outtemp++)
		{
			for (u16 temp = 0; temp< 1000;temp++)
			{
				comp[temp] = adc1_data[temp+outtemp*1000];
			}
			QuickSort(comp,0,999);	
			OutputAC = (comp[970]-comp[60])*3300/65536+OutputAC;	
		}
		OutputAC = OutputAC/10;

	if(mode == 1)
	{OutputResAC = OutputAC;}
	
	if(mode == 2)
	{OutputRes = (OutputAC/OutputResAC-1)*1.55;}	
	
}



float Mea_Scan_Output(void)
{
		OutputAC = 0;
		for (u16 temp = 0; temp< 1000;temp++)
		{
			comp[temp] = adc1_data[temp];
		}
		QuickSort(comp,0,999);
		OutputAC = (comp[970]-comp[30])*3300/65536;
		
		return OutputAC;
}

void Mea_Scan(void)
{
	u16 saopin = 0;
	u16 order = 0;
	float data0 = 0;
	float data1 = 0;
	frequency = 100;
	Freq_convert(frequency);

	TIM15->PSC = 300-1;	
//	printf("%d\r\n", frequency);
	adc_saopin();
	
	data1 = data0;
	data0 = Mea_Scan_Output();
	
	scan_data[order] = (data0-data1)/1*1+data1;
	order+=1;
	
	for(saopin = 0;saopin<50;saopin++)
	{		
		if(frequency<1000)
		{
			frequency = 400+frequency;
			Freq_convert(frequency);

//			printf("%d\r\n", frequency);
			TIM15->PSC = 300-1;	
			adc_saopin();
			data1 = data0;
			data0 = Mea_Scan_Output();
			
			for(u16 ordertemp=1;ordertemp<2;ordertemp++)
			{				
				scan_data[order] = (data0-data1)/1*ordertemp+data1;
				order+=1;		
			}

		}
		else if(frequency<10000)
		{
			frequency = 400*8+frequency;
			Freq_convert(frequency);
			
//			printf("%d\r\n", frequency);
			TIM15->PSC = 75-1;	
			adc_saopin();
			data1 = data0;
			data0 = Mea_Scan_Output();
			
			for(u16 ordertemp=1;ordertemp<9;ordertemp++)
			{				
				scan_data[order] = (data0-data1)/8*ordertemp+data1;
				order+=1;		
			}

		}
		else if(frequency<50000)
		{
			frequency = 400*40+frequency;
			Freq_convert(frequency);			
//			printf("%d\r\n", frequency);
			TIM15->PSC = 30-1;	
			adc_saopin();
			data1 = data0;
			data0 = Mea_Scan_Output();
			
			for(u16 ordertemp=1;ordertemp<40;ordertemp++)
			{				
				scan_data[order] = (data0-data1)/40*ordertemp+data1;
				order+=1;		
			}
		}		

		else if(frequency<100000)
		{
			frequency = 400*10+frequency;
			Freq_convert(frequency);			
//			printf("%d\r\n", frequency);
			TIM15->PSC = 15-1;	
			adc_saopin();
			data1 = data0;
			data0 = Mea_Scan_Output();
			
			for(u16 ordertemp=1;ordertemp<10;ordertemp++)
			{				
				scan_data[order] = (data0-data1)/10*ordertemp+data1;
				order+=1;		
			}
		}	
		else if(frequency<150000)
		{
			frequency = 400*25+frequency;
			Freq_convert(frequency);			
//			printf("%d\r\n", frequency);
			TIM15->PSC = 10-1;	
			adc_saopin();
			data1 = data0;
			data0 = Mea_Scan_Output();
			
			for(u16 ordertemp=1;ordertemp<25;ordertemp++)
			{				
				scan_data[order] = (data0-data1)/25*ordertemp+data1;
				order+=1;		
			}
		}			
		else if(frequency<200000)
		{
			frequency = 400*10+frequency;
			Freq_convert(frequency);			
//			printf("%d\r\n", frequency);			
			TIM15->PSC = 5-1;	
			adc_saopin();
			data1 = data0;
			data0 = Mea_Scan_Output();
			
			for(u16 ordertemp=1;ordertemp<10;ordertemp++)
			{				
				scan_data[order] = (data0-data1)/10*ordertemp+data1;
				order+=1;		
			}

		}
		else
		{
			order-=1;
			break;
		}

	}
	for (u16 temp = 0; temp< 473;temp++)
	{
		scan_data[temp] = scan_data[temp]*255/700;
//		printf("%f\r\n", scan_data[temp]);
	}	
	Freq_convert(1000);	
	sendwave();
}

void Upper_K_Find(void)
{
	u16 findtmp = 0;
	float biggest = scan_data[100]/1.414;
	for(findtmp = 100;findtmp < 472;findtmp++)
	{
		if(scan_data[findtmp]<biggest)
		{
			Upper_K = findtmp*0.4;
			break;
		}
		
	}
	show_Upper_K(Upper_K);
}


void Start_Input_Resistor_Measure(void)
{
	OPenRelay(GPIOD,GPIO_PIN_2);
	CloseRelay(GPIOD,GPIO_PIN_4);
}


void Stop_Input_Resistor_Measure(void)
{
	OPenRelay(GPIOD,GPIO_PIN_4);
	CloseRelay(GPIOD,GPIO_PIN_2);	
}

void Open_DC(void)
{
	CloseRelay(GPIOB,GPIO_PIN_9);
	CloseRelay(GPIOD,GPIO_PIN_6);
	
	CloseRelay(GPIOE,GPIO_PIN_1);
	OPenRelay(GPIOB,GPIO_PIN_5);
}	

void Open_AC(void)
{
	CloseRelay(GPIOB,GPIO_PIN_9);
	OPenRelay(GPIOD,GPIO_PIN_6);
	
	OPenRelay(GPIOE,GPIO_PIN_1);
	CloseRelay(GPIOB,GPIO_PIN_5);
}

void Start_Output_Resistor_Measure(void)
{
	OPenRelay(GPIOB,GPIO_PIN_9);
//	OPenRelay(GPIOD,GPIO_PIN_6);
//	
//	OPenRelay(GPIOE,GPIO_PIN_1);
//	CloseRelay(GPIOB,GPIO_PIN_5);
//	
	CloseRelay(GPIOD,GPIO_PIN_6);
	
	CloseRelay(GPIOE,GPIO_PIN_1);
	OPenRelay(GPIOB,GPIO_PIN_5);	
	
	
	
}
void Close_All(void)
{
	CloseRelay(GPIOB,GPIO_PIN_9);
	CloseRelay(GPIOD,GPIO_PIN_6);
	
	CloseRelay(GPIOE,GPIO_PIN_1);
	CloseRelay(GPIOB,GPIO_PIN_5);
}



