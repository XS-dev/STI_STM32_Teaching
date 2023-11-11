#include "FM.h"

uint32_t fm_scan0[200] 	= {0};//存放采集值


uint32_t fsm_max = 0;
uint32_t fsm_min = 0;


float 	fm_fs 				= 0		;//fm的最大频偏
float		 fm_mf				= 0		;//fm的调频范围
uint32_t fm_st[20] = {0};	//直方统计，做20组
void scanfre(void)//获取扫描数据
{
	for(int usehere = 0;usehere < 200;usehere++)
	{
		fm_temp = 0;
		while(fm_temp<=0)
		{
				switch (capture_Cnt)
				{
					case 0:
						capture_Cnt++;
						__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING);
						HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_3);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);
						break;
					case 3:
						fm_value[fm_temp] = capture_Buf[1]- capture_Buf[0];    //高电平时间
						fm_temp++;
						capture_Cnt = 0;  //清空标志位
						break;
				}
		}
		fm_scan0[usehere] = fm_value[0];
	}
	QuickSort(fm_scan0,0,199);
	fsm_max = fm_scan0[190];
	fsm_min = fm_scan0[10];
	fm_fs = ((float)240000000*count_flag/(float)(fsm_min)-(float)240000000*count_flag/(float)(fsm_max))/2;
	fm_mf = fm_fs/FM_fre;
}








