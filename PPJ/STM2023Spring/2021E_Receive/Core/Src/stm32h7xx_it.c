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
int DATA_order=0;//��¼�Ѿ��յ������ݸ���
int read_state;
uint16_t DATA_Array[100]={0};//14�����ݽ��յ�����DATA_Array[13]��Ӧ���Ͷ˷������ݵ����λ�����Ͷ������λ�ȷ�
uint16_t rec_num=0;//���յ���0/1��ֵ��ת��Ϊʮ������,������ʾ�����
uint16_t find_start = 0;
uint16_t find_start_ready = 0;
uint16_t find_start_flag = 0;

uint16_t mask_window = 0;
uint16_t mask_num = 0;
uint16_t mask_num_max = 3;

uint16_t temp = 0;
//��ȡ�������͵�ƽ����������Ҫ30����Ŀǰ10K������
uint16_t wait_start = 0;

int shut_down_led4_flag=0;//�ر��������ʾ�ı�־λ������־λΪ1ʱ��Ϩ������ܣ���Ϊ0ʱ������ˢ��
uint32_t refresh_times=0;//ˢ�µĴ���
int shut_down_led4=0;//1��ʾϨ��

uint32_t overtime = 0; //��ʱ��ʱ��


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
	//�����ʱ���������ܳ�ʱ������Ϩ���ܵ��Ǹ���������10K�ļ�ʱƵ��
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
	//�ö�ʱ��������������ܵ���ʾ,������40K��Ƶ��
	if(shut_down_led4_flag==0)//����ر�����ܵı�־λΪ0�������ˢ�������
	{
		Display_Four_num();
	}
	else if(shut_down_led4_flag==1)//����־λΪ1ʱ��ѭ��160 000�Σ�3s��,Ϩ�������
	{
		refresh_times++;
		Display_Four_num();
		if(refresh_times==10000)
		{
			shut_down_led4=1;//�������벶���е�Ϩ������  
			refresh_times=0;
			shut_down_led4_flag=2;//��ʾ����ִ���κ�����ܲ���
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
	//�ö�ʱ�������ݶ�ȡ����
	//��ȡ��ƽ����
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
				//������36���͵�ƽ��������Ϊ���������ĸߵ�ƽһ��������֡
				find_start_ready = 1;
			}
		}
		if(find_start == 1)
		{
			if(find_start_ready == 1)
			{
//				find_start_flag = 1;
				find_start_ready = 0;
				
				//�������δ������δ���ʱ���ڵ����ݲ����ȡ
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
			//��ȡ��ƽ����
			DATA_Array[DATA_order]=Pinread();
			DATA_order++;//ָʾ�±�����1
			//��������
			mask_window = 1;
			if(DATA_order!=14)///�����յ���14�����ݵ�ʱ�򣬲����ٽ�rec_num����
			{
				rec_num=rec_num+Pinread();//��ȡ��������0/1
				rec_num=rec_num<<1;//16λ����������һλ
			}
			if(DATA_order==14)//��0��ʼ������Ѿ��յ���14�����ݣ�˵���ɼ������Ѿ�����
			{
				rec_num=rec_num>>1;//16λ����������һλ
				find_start_flag=0;//��find_start_flag��0����ʾ�ȴ�֡ͷ1�����صĵ�����������һ֡����
				DATA_order=0;//�����ݼ�¼�±����㣬���¿�ʼ��������
				
				//�����������ʾ
				AJcode[0]=rec_num/1000;//�������ݵĵ�1λ�����λ
				AJcode[1]=(rec_num/100)%10;//�������ݵĵ�2λ
				AJcode[2]=(rec_num/10)%10;//�������ݵĵ�3λ
				AJcode[3]=rec_num%10;//�������ݵĵ�4λ�����λ
				rec_num=0;//��ʾ������ܺ�Ž����������
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
