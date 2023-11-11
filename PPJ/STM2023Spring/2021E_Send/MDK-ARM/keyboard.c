#include "keyboard.h"

uint16_t keyall[5][5] = {
	{0, 0, 0  , 0, 0},
	{0,16, 12 , 8, 4},
	{0,15, 11 , 7, 3},
	{0,14, 10 , 6, 2},
	{0,13, 9	, 5, 1},
};




void delay_keyboard(void)
{
	Delay_Ms(20);
}

void Keyboard_Column_Output(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, C1_Pin|C2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, C3_Pin|C4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = C1_Pin|C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin */
  GPIO_InitStruct.Pin = C3_Pin|C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void Keyboard_Column_Input(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	
  GPIO_InitStruct.Pin = C1_Pin|C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = C3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void Keyboard_Row_Output(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);

	
  GPIO_InitStruct.Pin = R1_Pin|R2_Pin|R3_Pin|R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

	

void Keyboard_Row_Input(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

  GPIO_InitStruct.Pin = R1_Pin|R2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = R3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(R3_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(R4_GPIO_Port, &GPIO_InitStruct);
}

void Keyboard_Row_Ext(void)
{
	
	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pins : PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = R4_Pin|R3_Pin|R2_Pin|R1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}






uint16_t scan_key(void)
{
	uint16_t Column = 0;
	uint16_t row = 0;
	uint16_t key = 255;

	Column = scan_key_Column();
	row = scan_key_row();
//	printf("%d,%d\n",Column,row);

	key = keyall[Column][row];
	return key;
}

uint16_t scan_key_Column(void)
{
	Keyboard_Row_Output();
	Keyboard_Column_Input();
	delay_keyboard();

	
	if(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin))
	{
		return 1;
	}
	if(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin))
	{
		return 2;
	}
	if(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin))
	{
		return 3;
	}
	if(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin))
	{
		return 4;
	}
	return 0;
}

uint16_t scan_key_row(void)
{
	Keyboard_Column_Output();
	Keyboard_Row_Input();
	delay_keyboard();
	
	if(HAL_GPIO_ReadPin(R1_GPIO_Port, R1_Pin))
	{
		return 1;
	}
	if(HAL_GPIO_ReadPin(R2_GPIO_Port, R2_Pin))
	{
		return 2;
	}
	if(HAL_GPIO_ReadPin(R3_GPIO_Port, R3_Pin))
	{
		return 3;
	}
	if(HAL_GPIO_ReadPin(R4_GPIO_Port, R4_Pin))
	{
		return 4;
	}
	return 0;
}