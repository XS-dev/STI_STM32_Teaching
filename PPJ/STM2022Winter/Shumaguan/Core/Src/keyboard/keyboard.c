#include "keyboard.h"
 
 
 
/*
* @Description: 初始化 矩阵按键的I/O口
* @param 1 – 参数 1：无
* @return – 返回值：无
*/
void Keyboard_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
        
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, R3_Pin|R2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(R4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = R3_Pin|R2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = R1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(R1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = C1_Pin|C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = C3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(C3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(C4_GPIO_Port, &GPIO_InitStruct);

}
 
 
 
 
/*
* @Description: 矩阵按键扫描函数
* @param 1 – *key_val：存储 当前按键的数值
* @return – 返回值：无
*/
void keyboard_scan(uint16_t *key_val)
{
	uint16_t temp=0;
 
	GPIOA->ODR=0X00;
	GPIOA->ODR=0XF7;
	if((GPIOA->IDR&0XF0)!=0XF0){
		Delay_Ms(10);
		
		if((GPIOA->IDR & 0XF0)!=0XF0){
			temp=(GPIOA->IDR&0XF7);
			
			switch(temp){
				case 0xE7:  *key_val = 13;   break;
			
				case 0xD7:  *key_val = 14;   break;
			
				case 0xB7:  *key_val = 15;   break;
				
				case 0x77:  *key_val = 16;   break;
				
				default:    *key_val = 0;   break;
			}
		}while((GPIOA->IDR&0XF7) != 0XF7);
	}
    
	
	GPIOA->ODR=0X00;
	GPIOA->ODR=0XFB;
	if((GPIOA->IDR&0XF0)!=0XF0){
		Delay_Ms(10);
		
		if((GPIOA->IDR & 0XF0)!=0XF0){
			temp=(GPIOA->IDR&0XFB);
			
			switch(temp){
				case 0xEB:  *key_val = 9;  break;
 
				case 0xDB:  *key_val = 10;  break;
 
				case 0xBB:  *key_val = 11;  break;
 
				case 0x7B:  *key_val = 12 ;  break;
 
				default:    *key_val = 0;  break;
			}
		}while((GPIOA->IDR&0XFB) != 0XFB);
	}
 
	
	GPIOA->ODR=0X00;
	GPIOA->ODR=0XFD;
	if((GPIOA->IDR&0XF0)!=0XF0){						//GPIOA->IDR：读取置1的IO口，这里就是读取 PA7-PA4管脚的电平
		Delay_Ms(10);
		
		if((GPIOA->IDR & 0XF0)!=0XF0){
			temp=(GPIOA->IDR&0XFD);
			
			switch(temp){
				case 0xED:  *key_val = 5;   break;
 
				case 0xDD:  *key_val = 6;  break;
 
				case 0xBD:  *key_val = 7;  break;
 
				case 0x7D:  *key_val = 8;  break;
 
				default:    *key_val = 0;   break;
			}
		}while((GPIOA->IDR&0XFD) != 0XFD);
	}
 
 
	GPIOA->ODR=0X00;
	GPIOA->ODR=0XFE;
	if((GPIOA->IDR&0XF0)!=0XF0){
		Delay_Ms(10);
			
		if((GPIOA->IDR & 0XF0)!=0XF0){
			temp=(GPIOA->IDR&0XFE);
			
			switch(temp){
				case 0xEE:  *key_val = 1;  break;
 
				case 0xDE:  *key_val = 2;  break;
 
				case 0xBE:  *key_val = 3;  break;
 
				case 0x7E:  *key_val = 4;  break;
 
				default:    *key_val = 0;   break;
			}
		}while((GPIOA->IDR&0XFE) != 0XFE);
	}
}
 
 
 
/*
* @Description: 返回自定义按键数值
* @param 1 – 参数 1：无
* @return – count：按键数值
*/
uint16_t fetch_key_value(void){
	uint16_t key = 0,count = 22;
	keyboard_scan(&key);
	
	switch(key){
	case 0:										// 没有按键按下时
		count = 22;		break;		
	case 1:										// S1
		count = 1;		break;
	case 2:										// S2
		count = 2;		break;
	case 3:										// S3
		count = 3;		break;
	case 4:										// S4
		count = 17;		break;
	case 5:										// S5
		count = 4;		break;
	case 6:										// S6
		count = 5;		break;
	case 7:										// S7
		count = 6;		break;
	case 8:										// S8
		count = 18;		break;	
	case 9:										// S9
		count = 7;		break;
	case 10:									// S10
		count = 8;		break;
	case 11:									// S11
		count = 9;		break;
	case 12:									// S12
		count = 12;		break;
	case 13:									// S13
		count = 13;		break;
	case 14:									// S14
		count = 0;		break;
	case 15:									// S15
		count = 15;		break;
	case 16:									// S16
		count = 16;		break;
	}return count;
}