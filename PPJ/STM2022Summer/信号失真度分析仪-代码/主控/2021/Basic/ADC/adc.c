#include "adc.h"
#include "main.h"


/* Timer_A Continuous Mode Configuration Parameter */
Timer_A_UpModeConfig upModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,           // ACLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,       // ACLK/1 = 6M
				11,
        TIMER_A_TAIE_INTERRUPT_DISABLE,      // Disable Timer ISR
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE, // Disable CCR0
        TIMER_A_DO_CLEAR                     // Clear Counter
};

/* Timer_A Compare Configuration Parameter */
Timer_A_CompareModeConfig compareConfig =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_SET_RESET,               // Toggle output but
        11                                       // 16000 Period
};


void  ADC14Init(int i)
{ 
		u16 GPIO_PORT;
		u16 GPIO_PIN;
		uint32_t GPIO_INPUT;
	
	 switch(i)
	 {
		 case 1:
		 {
			  GPIO_PORT	=GPIO_PORT_P5;
				GPIO_PIN	=GPIO_PIN5;
				GPIO_INPUT=ADC_INPUT_A0;
				break;
		 }
		 case 2:
		 {
			  GPIO_PORT	=GPIO_PORT_P5;
				GPIO_PIN	=GPIO_PIN4;
				GPIO_INPUT=ADC_INPUT_A1;
				break;
		 }
		 case 3:
		 {
			  GPIO_PORT	=GPIO_PORT_P4;
				GPIO_PIN	=GPIO_PIN7;
				GPIO_INPUT=ADC_INPUT_A6;
				break;
		 }
		 default:
		 {
			  GPIO_PORT	=GPIO_PORT_P5;
				GPIO_PIN	=GPIO_PIN5;
				GPIO_INPUT=ADC_INPUT_A0;
		 }
	 }
	
	
	 MAP_ADC14_disableConversion();
	 MAP_ADC14_disableModule();
		
    /* 使能浮点运算*/
   MAP_FPU_enableModule();
   MAP_FPU_enableLazyStacking();
	
   /* 使能ADC4模块，时钟分频*/
   MAP_ADC14_enableModule();
   MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1,ADC_DIVIDER_1,0);
	
	 /* 14位分辨率  */
	 ADC14_setResolution(ADC_14BIT);//14位
	
	  /* 配置GPIO输入通道(5.5 A0),5.4(A1) */
   MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT, GPIO_PIN,GPIO_TERTIARY_MODULE_FUNCTION);

	 /* 配置ADC转换存储器 */
    MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS,
    GPIO_INPUT, false);

		
		    /* Configuring Timer_A in continuous mode and sourced from ACLK */
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upModeConfig);

    /* Configuring Timer_A0 in CCR1 to trigger at 16000 (0.5s) */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig);

    /* Configuring the sample trigger to be sourced from Timer_A0  and setting it
     * to automatic iteration after it is triggered*/
    MAP_ADC14_setSampleHoldTrigger(ADC_TRIGGER_SOURCE1, false);

    MAP_ADC14_enableConversion();
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}



void Change_Simple_Rate(uint32_t freq) //hz
{
	ROM_Timer_A_stopTimer(TIMER_A0_BASE);
	uint32_t cnt=(12000000/freq)-1;
	upModeConfig.timerPeriod=cnt;
	compareConfig.compareValue=cnt;
  MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upModeConfig);
  MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig);
	MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}

