#include "error_detect.h"

float Mea_Scan_DC(void)
{
		OutputDC = 0;
		for (u16 temp = 0; temp< 1000;temp++)
		{
			comp[temp] = adc1_data[temp];
		}
		QuickSort(comp,0,999);
		OutputDC = (comp[500])*3300/65536;
		
		return OutputDC;
}
