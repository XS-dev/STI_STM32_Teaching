#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "AD9854.h"

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    AD9854_Init();//��ʼ��AD9854
    delay_us(10000);
    AD9854_SetSine_double(14992,2000);//����Ƶ�ʺͷ�ֵ
    while(1);
}
