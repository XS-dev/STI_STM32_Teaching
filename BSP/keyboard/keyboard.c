#include "keyboard.h"

uint8_t KEYPAD_INT_Buttons[4][4] = {
	{0x01, 0x02, 0x03, 0x0C},
	{0x04, 0x05, 0x06, 0x0D},
	{0x07, 0x08, 0x09, 0x0E},
	{0x0A, 0x00, 0x0B, 0x0F},
};

// initialize keypad
void KEYPAD_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, KEYPAD_ROW_4_Pin|KEYPAD_ROW_3_Pin|KEYPAD_ROW_2_Pin|KEYPAD_ROW_1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = KEYPAD_COLUMN_4_Pin|KEYPAD_COLUMN_3_Pin|KEYPAD_COLUMN_2_Pin|KEYPAD_COLUMN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = KEYPAD_ROW_4_Pin|KEYPAD_ROW_3_Pin|KEYPAD_ROW_2_Pin|KEYPAD_ROW_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// private function for "PULL DOWN SPECIFIC ROW"
void KEYPAD_INT_PullDownRow(uint8_t row)
{
	switch(row)
	{
	case 1:
		KEYPAD_ROW_HIGH_BUT_1;					// pull down row 1
		break;
	case 2:
		KEYPAD_ROW_HIGH_BUT_2;					// pull down row 2
		break;
	case 3:
		KEYPAD_ROW_HIGH_BUT_3;					// pull down row 3
		break;
	case 4:
		KEYPAD_ROW_HIGH_BUT_4;					// pull down row 4
		break;
	default:
		break;
	}
}

// private function for "check each column after pulling down row"
uint8_t KEYPAD_INT_CheckColumn(uint8_t row)
{
	if(KEYPAD_COLUMN_1_CHECK)
	{
		KEYPAD_Debounce_Delay(KEYPAD_DEBOUNCE_DELAYTIME);
		if(KEYPAD_COLUMN_1_CHECK)
		{
			return KEYPAD_INT_Buttons[row - 1][0];
		}
	}
	if(KEYPAD_COLUMN_2_CHECK)
	{
		KEYPAD_Debounce_Delay(KEYPAD_DEBOUNCE_DELAYTIME);
		if(KEYPAD_COLUMN_2_CHECK)
		{
			return KEYPAD_INT_Buttons[row - 1][1];
		}
	}
	if(KEYPAD_COLUMN_3_CHECK)
	{
		KEYPAD_Debounce_Delay(KEYPAD_DEBOUNCE_DELAYTIME);
		if(KEYPAD_COLUMN_3_CHECK)
		{
			return KEYPAD_INT_Buttons[row - 1][2];
		}
	}
	if(KEYPAD_COLUMN_4_CHECK)
	{
		KEYPAD_Debounce_Delay(KEYPAD_DEBOUNCE_DELAYTIME);
		if(KEYPAD_COLUMN_4_CHECK)
		{
			return KEYPAD_INT_Buttons[row - 1][3];
		}
	}
	return KEYPAD_NO_PRESSED;
}


uint8_t KEYPAD_READ(void)
{
	uint8_t row, check;
	for(uint8_t i = 0; i < 4; i++)
	{
		row = i + 1;
		KEYPAD_INT_PullDownRow(row);
		check = KEYPAD_INT_CheckColumn(row);
		if(check != KEYPAD_NO_PRESSED)
		{
			return check;
		}
	}
	return KEYPAD_NO_PRESSED;
}

__attribute__((weak)) void KEYPAD_Debounce_Delay(uint32_t debounceDelay)
{
	HAL_Delay(debounceDelay);
}
//

