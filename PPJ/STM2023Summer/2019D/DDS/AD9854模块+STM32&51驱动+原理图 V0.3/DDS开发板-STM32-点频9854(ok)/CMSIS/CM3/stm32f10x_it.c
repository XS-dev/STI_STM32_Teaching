/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

#include "delay.h"
#include "led.h"
#include "sys.h"
#include "stm32f10x_tim.h"
#include "key.h"

///* 因为USART1用来下载程序或者调试时打印信息，所以不用 */
//#if USB_USARTx==2	/* 串口2 */
//	void USART2_IRQHandler(void)
//#elif USB_USARTx==3	/* 串口3 */
//	void USART3_IRQHandler(void)
//#elif USB_USARTx==4	/* 串口3 */
//	void UART4_IRQHandler(void)
//#elif USB_USARTx==5	/* 串口3 */
//	void UART5_IRQHandler(void)
//#endif
//{
//	if(USART_GetITStatus(USB_USART_n, USART_IT_RXNE) != RESET)	//串口接收到数据
//	{
//		USART_To_USB_Send_Data();	//发送数据到USB
//	}
//}


/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
//	LCD_Clear(WHITH);	//清除屏幕
	printf("\r\nHardFault_Handler ERROR\r\n");
	while (1)
	{
//		LCD_Display_String_BK(0, 303, "HardFault_Handler ERROR", 16, RED, WHITH);
//		delay_ms(200);
//		LCD_Display_String_BK(0, 303, "                       ", 16, RED, WHITH);
//		delay_ms(200);
//		LED1 = !LED1;	//硬件出错
	}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
//  	/* Go to infinite loop when Memory Manage exception occurs */
//	LCD_Clear(WHITH);	//清除屏幕
//	printf("\r\nMemManage_Handler ERROR\r\n");
//	while (1)
//	{
//		LCD_Display_String_BK(0, 303, "MemManage_Handler ERROR", 16, RED, WHITH);
//		delay_ms(200);
//		LCD_Display_String_BK(0, 303, "                       ", 16, RED, WHITH);
//		delay_ms(200);
//		LED1 = !LED1;	//硬件出错
//	}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  	/* Go to infinite loop when Bus Fault exception occurs */
//	LCD_Clear(WHITH);	//清除屏幕
//	printf("\r\nBusFault_Handler ERROR\r\n");
//	while (1)
//	{
//		LCD_Display_String_BK(0, 303, "BusFault_Handler ERROR", 16, RED, WHITH);
//		delay_ms(200);
//		LCD_Display_String_BK(0, 303, "                      ", 16, RED, WHITH);
//		delay_ms(200);
//		LED1 = !LED1;	//硬件出错
//	}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
//	LCD_Clear(WHITH);	//清除屏幕
//	printf("\r\nUsageFault_Handler ERROR\r\n");
//	while (1)
//	{
//		LCD_Display_String_BK(0, 303, "UsageFault_Handler ERROR", 16, RED, WHITH);
//		delay_ms(200);
//		LCD_Display_String_BK(0, 303, "                        ", 16, RED, WHITH);
//		delay_ms(200);
//		LED1 = !LED1;	//硬件出错
//	}
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}
u16 sysbufer = 0;
u32 SysTimer = 0;
void TIM3_IRQHandler(void)
{
	TIM_ClearFlag(TIM3, TIM_IT_Update);

    KEY_Sys_Timer++;
    if(KEY_Cont)
      KEY_Time++;
    else
      KEY_Time = 0;
    ////////////////////////
    
    sysbufer++;
    if(sysbufer == 10)
    {
      SysTimer++;       //?10ms????
      sysbufer = 0;
    }
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
