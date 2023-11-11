#include "main.h"
#include "esp8266.h"
#include "my_key.h"

volatile uint8_t dma_flag=0;

arm_rfft_fast_instance_f32  _1024_fft;

float Hanning[1024];
uint16_t data_array1[1024];


float voltage_real[1024];	
float voltage_before_fft[1024];	
float voltage_fft[1024];				

char string[20];
u8 gears=1;

int main(void)
{ 
	arm_rfft_fast_init_f32(&_1024_fft, 1024);
	clk_init();
	Usart0tInit(); 
	Usart1tInit(); 
	ADC14Init(1);
	DMA_confing();	
	key_init();
		
	calculate_hanning();
	
	init_esp8266();
	connect_udp(2);
	
	while(1)
	{ 		
		if(start_flag)
		{
			voltage_process();
			start_flag=0;
		}
	}	
}

void start_DMA(void)
{
	dma_flag=0;
	MAP_DMA_enableChannel(7);
	MAP_DMA_requestSoftwareTransfer(0);	
	MAP_ADC14_enableConversion();
	while(!dma_flag);
}

void clk_init()
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
           GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    //设置时钟频率
    CS_setExternalClockSourceFrequency(32000,48000000);
    //设置内核电压 bank延迟
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    CS_startHFXT(false);
    //连接到外部时钟
    CS_initClockSignal(CS_MCLK  , CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_ACLK  , CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);
    CS_initClockSignal(CS_SMCLK , CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);
    CS_initClockSignal(CS_BCLK  , CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    // MCLK 48M
    // ACLK =32.768KHZ
    // HSMCLK =24MHZ
    // SMCLK=12MHZ
    // BCLK =32.768KHZ
}





