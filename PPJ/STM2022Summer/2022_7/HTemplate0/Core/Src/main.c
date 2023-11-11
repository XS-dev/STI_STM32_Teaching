/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


ALIGN_32BYTES (uint16_t adc1_data[FFT_LENGTH]) 	__attribute__((section(".ARM.__at_0x30020000")));
__IO uint8_t fre_flag0 = 0;//表示载波频率测量结束

extern uint32_t 	flag;  // 输出频率标志位


__IO uint8_t AdcConvEnd = 0;//表示adc采集完成
__IO uint16_t fre_count = 0;//fm扫描标志位，在第101个上升沿

u16 			None_flag 				= 0;
u16 			AM_flag 					= 0;
u16 			FM_flag 					= 0;
uint32_t 	fm_value[10]  	= {0};//fm扫频临时存放值


uint32_t 	cnt 						= 0;  // 计数值，库函数为unit32_t 
uint32_t 	cnt_value[201] 	= {0};
uint32_t 	capture_Buf[3] 	= {0};   //存放计数值
uint8_t 		capture_Cnt 			= 0;    //状态标志位
uint32_t 	high_time 				= 0;   //高电平时间
u16 			fm_temp 					= 0;
float	count_flag = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void adc_init(void)
{
    MX_ADC1_Init();	//初始化调用放这里, 确保在MX_DMA_Init()初始化后面    
    HAL_Delay(100);	//有地方说这里可以等等电压稳定后再校准

    if (HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
    {
        printf("hadc1 error with HAL_ADCEx_Calibration_Start\r\n");
        Error_Handler();
    }

    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_data, ADC1_BUFFER_SIZE) != HAL_OK)
    {
        printf("hadc1 error with HAL_ADC_Start_DMA\r\n");
        Error_Handler();
    }

		HAL_TIM_Base_Start(&htim6);
		while (!AdcConvEnd);
		AdcConvEnd = 0;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_UART5_Init();
  /* USER CODE BEGIN 2 */
	AD9833_Init();
	init_esp8266();
	connect_udp(3);
	AD9854_Init();
	for(int mino = 0;mino<5; mino++)
		AD9854_SetSine_double((1000 + 50000),4095);
	char screen_message[70];
	for(int i = 0;i<5;i++)
	USART1PutString("t6.txt=\"None\"\xff\xff\xff");
	sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(0));
	USART1PutString(screen_message);
	sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(0));
	USART1PutString(screen_message);
	sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(0));
	USART1PutString(screen_message);
	sprintf(screen_message,"x3.val=%d\xff\xff\xff",(int)(0));
	USART1PutString(screen_message);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		if(None_flag)
		{

				None_flag = 0;
				HAL_TIM_Base_Start_IT(&htim4);
				HAL_TIM_Base_Start(&htim2);
				while(1){
				if(fre_flag0)
				break;
				};
				fre_flag0 = 0;	
				fre_get();
				for(int mino = 0;mino<5; mino++)
				AD9854_SetSine_double((frequency + 50000),4095);
				printf("%d \r\n", frequency);
				TIM6->PSC = 30-1;
				adc_init();
//				Raw_Wave();
				FFT_Init();
				FFT_DIS();
				JUDGE();
				if(FM_flag == 1)
				{
					for(int i = 0;i<5;i++)
					USART1PutString("t6.txt=\"FM\"\xff\xff\xff");
					wave_type = 2;
					for(int mino = 0;mino<5; mino++)
					AD9854_SetSine_double((10000000 + 50000),4095);
					TIM6->PSC = 30-1;
					adc_init();
					FFT_Init();
					FM_peak();
					char screen_message[70];
					sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(FM_fre/10));
					USART1PutString(screen_message);
					AD9854_SetSine_double((10000000 + 500000),4095);
					count_flag = (uint32_t)((float)50000/FM_fre);
					scanfre();
					sprintf(screen_message,"x3.val=%d\xff\xff\xff",(int)(fm_mf*100));
					USART1PutString(screen_message);
					AD9833_SetWaveData(FM_fre,0);	
					AMDMF = fm_mf;
					send_fft();			
					FM_flag = 0;
				}
				if(AM_flag == 1)
				{
					wave_type=1;
					AM_flag = 0;
					AM_peak2();
					AM_MF0();
					for(int i = 0;i<5;i++)
					USART1PutString("t6.txt=\"AM\"\xff\xff\xff");
					char screen_message[70];
					sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(AM_fre/10));
					USART1PutString(screen_message);
					sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(AMDMF*100));
					USART1PutString(screen_message);	
					AD9833_SetWaveData(AM_fre,0);
					AMDMF = AMDMF;
					send_fft();
				}
				if(None_flag == 1)
				{
					for(int i = 0;i<5;i++)
					USART1PutString("t6.txt=\"None\"\xff\xff\xff");
					wave_type=0;
					AD9833_SetWaveData(0,0);			
					None_flag = 0;
				}
		}
		if(AM_flag)
		{
			printf("Fl\r\n");
			wave_type=1;
			for(int mino = 0;mino<5; mino++)
			AD9854_SetSine_double((10000000 + 50000),4095);
			TIM6->PSC = 30-1;
			adc_init();
			FFT_Init();
			FFT_DIS();
			AM_peak();
			AM_MF0();
			for(int i = 0;i<50;i++)
			USART1PutString("t6.txt=\"AM\"\xff\xff\xff");
			char screen_message[70];
			sprintf(screen_message,"x1.val=%d\xff\xff\xff",(int)(AM_fre/10));
			USART1PutString(screen_message);
			sprintf(screen_message,"x2.val=%d\xff\xff\xff",(int)(AMDMF*100));
			USART1PutString(screen_message);	
			AD9833_SetWaveData(AM_fre,0);
			AMDMF = AMDMF;
			send_fft();
			AM_flag = 0;
		}
		if(FM_flag)
		{
				for(int i = 0;i<50;i++)
				USART1PutString("t6.txt=\"FM\"\xff\xff\xff");
				wave_type = 2;
				for(int mino = 0;mino<5; mino++)
				AD9854_SetSine_double((10000000 + 50000),4095);
				TIM6->PSC = 30-1;
				adc_init();
				FFT_Init();
				FM_peak();
				char screen_message[70];
				sprintf(screen_message,"x0.val=%d\xff\xff\xff",(int)(FM_fre/10));
				USART1PutString(screen_message);
				AD9854_SetSine_double((10000000 + 500000),4095);
				count_flag = (uint32_t)((float)50000/FM_fre);
				scanfre();
				sprintf(screen_message,"x3.val=%d\xff\xff\xff",(int)(fm_mf*100));
				USART1PutString(screen_message);
				AD9833_SetWaveData(FM_fre,0);	
				AMDMF = fm_mf;
				send_fft();			
				FM_flag = 0;
		}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == htim5.Instance)
	{
		switch(capture_Cnt)
		{

			case 1:
				capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_3);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_3,TIM_ICPOLARITY_RISING);  //设置为下降沿捕获
				capture_Cnt++;
				break;
			case 2:
				fre_count++;
				if(fre_count >= count_flag)
				{
					capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_3);//获取当前的捕获值.
					HAL_TIM_IC_Stop_IT(&htim5,TIM_CHANNEL_3); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
					capture_Cnt++;  
					fre_count = 0;
				}


		}
	
	}
	
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
   if(hadc->Instance == ADC1) {
       SCB_InvalidateDCache_by_Addr((uint32_t *) &adc1_data[0], ADC1_BUFFER_SIZE);}
	 AdcConvEnd = 1;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim4.Instance)
	{
			cnt_value[flag]= __HAL_TIM_GetCounter(&htim2);//读取外部计数器的值
			__HAL_TIM_SetCounter(&htim2,0);
			flag++;
			if(flag == 201)
			{
				flag = 0;
				QuickSort(cnt_value,1,200);
				frequency = (cnt_value[99]+cnt_value[100]+cnt_value[101])/3*16000;
				HAL_TIM_Base_Stop_IT(&htim4);
				fre_flag0 = 1;
			}
	}
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
