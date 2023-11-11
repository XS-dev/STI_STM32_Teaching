#include "FM.h"

uint32_t fm_scan0[200] 	= {0};//��Ųɼ�ֵ


uint32_t fsm_max = 0;
uint32_t fsm_min = 0;


float 	fm_fs 				= 0		;//fm�����Ƶƫ
float		 fm_mf				= 0		;//fm�ĵ�Ƶ��Χ
uint32_t fm_st[20] = {0};	//ֱ��ͳ�ƣ���20��
void scanfre(void)//��ȡɨ������
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
						HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_3);	//�������벶��       ����: __HAL_TIM_ENABLE(&htim5);
						break;
					case 3:
						fm_value[fm_temp] = capture_Buf[1]- capture_Buf[0];    //�ߵ�ƽʱ��
						fm_temp++;
						capture_Cnt = 0;  //��ձ�־λ
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








