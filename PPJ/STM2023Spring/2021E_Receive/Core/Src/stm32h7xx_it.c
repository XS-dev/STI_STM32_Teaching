/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32h7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
int DATA_order=0;//记录已经收到的数据个数
int read_state;
uint16_t DATA_Array[100]={0};//14个数据接收的容器DATA_Array[13]对应发送端发送数据的最高位，发送端是最高位先发
uint16_t rec_num=0;//将收到的0/1数值串转换为十进制数,用于显示数码管
uint16_t find_start = 0;
uint16_t find_start_ready = 0;
uint16_t find_start_flag = 0;

uint16_t mask_window = 0;
uint16_t mask_num = 0;
uint16_t mask_num_max = 3;

uint16_t temp = 0;
//读取到连续低电平个数，最少要30个，目前10K采样下
uint16_t wait_start = 0;

int shut_down_led4_flag=0;//关闭数码管显示的标志位，当标志位为1时，熄灭数码管，当为0时，正常刷新
uint32_t refresh_times=0;//刷新的次数
int shut_down_led4=0;//1表示熄灭

uint32_t overtime = 0; //超时的时间


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim15;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */
	//这个定时器负责主管超时，就是熄灭功能的那个，配置在10K的计时频率
	if(find_start_flag == 0)
	{
		overtime++;
		if(overtime == 200)
		{
			overtime = 0;
			if(shut_down_led4_flag == 0)
			{
				shut_down_led4_flag = 1;
			}
		}
	}
	else
	{
		overtime = 0;
	}
	
  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1_CH1 and DAC1_CH2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	//该定时器负责主管数码管的显示,配置在40K的频率
	if(shut_down_led4_flag==0)//如果关闭数码管的标志位为0，则持续刷新数码管
	{
		Display_Four_num();
	}
	else if(shut_down_led4_flag==1)//当标志位为1时，循环160 000次（3s）,熄灭数码管
	{
		refresh_times++;
		Display_Four_num();
		if(refresh_times==10000)
		{
			shut_down_led4=1;//激活输入捕获中的熄灭代码端  
			refresh_times=0;
			shut_down_led4_flag=2;//表示不再执行任何数码管操作
		}
	}
  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM15 global interrupt.
  */
void TIM15_IRQHandler(void)
{
  /* USER CODE BEGIN TIM15_IRQn 0 */
	//该定时器将数据读取出来
	//读取电平数据
	if(find_start_flag == 0)
	{
		find_start=Pinread();
		DATA_Array[temp] = find_start;
		temp++;
		if(temp == 100)
		{
			for (temp = 0; temp< 100;temp++)
			{
				printf("%d\r\n", DATA_Array[temp]);
			}
			temp = 0;
		}
		if(find_start == 0)
		{
			wait_start++;
			if(wait_start == 36)
			{
				//积累满36个低电平，我们认为即将到来的高电平一定是数据帧
				find_start_ready = 1;
			}
		}
		if(find_start == 1)
		{
			if(find_start_ready == 1)
			{
//				find_start_flag = 1;
				find_start_ready = 0;
				
				//开启屏蔽窗格，屏蔽窗格时间内的数据不会读取
				mask_window = 1;
			}
		}
	}
	else
	{
		if(mask_window == 1)
		{
			mask_num ++;
			if(mask_num == mask_num_max)
			{
				mask_window = 0;
				mask_num = 0;
			}
		}
		else
		{
			//读取电平数据
			DATA_Array[DATA_order]=Pinread();
			DATA_order++;//指示下标自增1
			//开启屏蔽
			mask_window = 1;
			if(DATA_order!=14)///当接收到第14个数据的时候，不能再将rec_num左移
			{
				rec_num=rec_num+Pinread();//读取发送来的0/1
				rec_num=rec_num<<1;//16位二进制左移一位
			}
			if(DATA_order==14)//从0开始，如果已经收到了14个数据，说明采集数据已经满了
			{
				rec_num=rec_num>>1;//16位二进制左移一位
				find_start_flag=0;//将find_start_flag归0，表示等待帧头1上升沿的到来，接收下一帧数据
				DATA_order=0;//将数据记录下标清零，重新开始接收数据
				
				//更新数码管显示
				AJcode[0]=rec_num/1000;//接收数据的第1位，最高位
				AJcode[1]=(rec_num/100)%10;//接收数据的第2位
				AJcode[2]=(rec_num/10)%10;//接收数据的第3位
				AJcode[3]=rec_num%10;//接收数据的第4位，最低位
				rec_num=0;//显示完数码管后才进行清零操作
			}
		}
	
		}


	
  /* USER CODE END TIM15_IRQn 0 */
  HAL_TIM_IRQHandler(&htim15);
  /* USER CODE BEGIN TIM15_IRQn 1 */

  /* USER CODE END TIM15_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
