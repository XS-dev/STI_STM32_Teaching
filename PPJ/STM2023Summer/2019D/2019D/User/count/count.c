#include "count.h"

//冒泡法
//void QuickSort(uint16_t a[],int q,int n)
//{
//    int i,j,temp;
//    for(i=q;i<n-1;i++)
//    {
//        for(j=q;j<n-1-i;j++)
//        {
//            if(a[j]>a[j+1])
//            {
//                temp=a[j];
//                a[j]=a[j+1];
//                a[j+1]=temp;
//            }
//        }
//    }
//}

// 快排函数
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

float singlesaopin(uint8_t channel,uint8_t readfre,int maga, int mod)
{
		float result = 0;
		ADCx_Init(channel,readfre,maga);
		SysTick_Delay_Us(500*mod);
//		QuickSort(ADC_ConvertedValue,0,maga-1);
		for(int i = 0; i<(maga);i++)
		{
				ADC_ConvertedValueLocal[i] =(float) ADC_ConvertedValue[i]/4096*3.3;	
				wave_show[i] = (ADC_ConvertedValueLocal[i]/3.3)*255;
				printf("%f\r\n",ADC_ConvertedValueLocal[i]);
				sendwave(wave_show[i]);				
		}
//		for(int i = 0;i < 30;i++)
//		printf("%f\r\n",ADC_ConvertedValueLocal[i+10]);
//		for(int i = 0;i < 30;i++)
//		printf("%f\r\n",ADC_ConvertedValueLocal[maga-i-100]);
		result = ADC_ConvertedValue[maga-35]-ADC_ConvertedValue[25];
		result = (float) result/4096*3.3;
		return result;
}

void zhendesaop(void)
{
	int djcsaopin = 0;
	int fre = 0;
	for(fre = 0; fre < 481;fre++)//0-1.5K
	{
		AD9833_SetWaveData(500*fre,0);
		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000,4);
		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000,4);
		djcsaopin++;
	}
//	for(fre = 4; fre <9;fre++)//2-4K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000);
//		djcsaopin++;		
//	}
//	for(fre = 9;fre < 13;fre++)//4.5-6K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000);
//		djcsaopin++;
//	}
//	for(fre = 13;fre < 21;fre++)//6.5-10K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000);
//		djcsaopin++;
//	}
//	for(fre = 21;fre < 31;fre++)//10.5-15K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000);
//		djcsaopin++;
//	}
//	for(fre = 31;fre < 41;fre++)//15.5-20K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000);
//		djcsaopin++;
//	}
//	for(fre = 41;fre < 81;fre++)//20.5-40K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,500);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,500);
//		djcsaopin++;
//	}
//	
//	for(fre = 81;fre < 121;fre++)//40.5-60K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,500);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,500);
//		djcsaopin++;
//	}
//	
//	for(fre = 121;fre < 201;fre++)//60.5-100K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,400);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,400);
//		djcsaopin++;
//	}
//	
//	for(fre = 201;fre < 481;fre++)//100.5-240K
//	{
//		AD9833_SetWaveData(500*fre,0);
//		Input[djcsaopin] 	= singlesaopin(ADC_CHANNEL1,0x00,1000);
//		Output[djcsaopin] =	singlesaopin(ADC_CHANNEL2,0x00,1000);
//		djcsaopin++;
//	}
	
	
}



