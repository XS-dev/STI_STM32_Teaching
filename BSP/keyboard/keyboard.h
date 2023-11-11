#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


#include "main.h"

#define KEYPAD_DEBOUNCE_DELAYTIME			20u

#define KEYPAD_COLUMN_4_Pin 				GPIO_PIN_15
#define KEYPAD_COLUMN_4_GPIO_Port 			GPIOB
#define KEYPAD_COLUMN_3_Pin 				GPIO_PIN_14
#define KEYPAD_COLUMN_3_GPIO_Port 			GPIOB
#define KEYPAD_COLUMN_2_Pin 				GPIO_PIN_13
#define KEYPAD_COLUMN_2_GPIO_Port 			GPIOB
#define KEYPAD_COLUMN_1_Pin 				GPIO_PIN_12
#define KEYPAD_COLUMN_1_GPIO_Port 			GPIOB

#define KEYPAD_ROW_4_Pin 					GPIO_PIN_4
#define KEYPAD_ROW_4_GPIO_Port 				GPIOA
#define KEYPAD_ROW_3_Pin 					GPIO_PIN_5
#define KEYPAD_ROW_3_GPIO_Port 				GPIOA
#define KEYPAD_ROW_2_Pin 					GPIO_PIN_6
#define KEYPAD_ROW_2_GPIO_Port 				GPIOA
#define KEYPAD_ROW_1_Pin 					GPIO_PIN_7
#define KEYPAD_ROW_1_GPIO_Port 				GPIOA

#define KEYPAD_ROW_1_LOW					XY_GPIO_SetPinLow(KEYPAD_ROW_1_GPIO_Port, KEYPAD_ROW_1_Pin)
#define KEYPAD_ROW_1_HIGH					XY_GPIO_SetPinHigh(KEYPAD_ROW_1_GPIO_Port, KEYPAD_ROW_1_Pin)

#define KEYPAD_ROW_2_LOW					XY_GPIO_SetPinLow(KEYPAD_ROW_2_GPIO_Port, KEYPAD_ROW_2_Pin)
#define KEYPAD_ROW_2_HIGH					XY_GPIO_SetPinHigh(KEYPAD_ROW_2_GPIO_Port, KEYPAD_ROW_2_Pin)

#define KEYPAD_ROW_3_LOW					XY_GPIO_SetPinLow(KEYPAD_ROW_3_GPIO_Port, KEYPAD_ROW_3_Pin)
#define KEYPAD_ROW_3_HIGH					XY_GPIO_SetPinHigh(KEYPAD_ROW_3_GPIO_Port, KEYPAD_ROW_3_Pin)

#define KEYPAD_ROW_4_LOW					XY_GPIO_SetPinLow(KEYPAD_ROW_4_GPIO_Port, KEYPAD_ROW_4_Pin)
#define KEYPAD_ROW_4_HIGH					XY_GPIO_SetPinHigh(KEYPAD_ROW_4_GPIO_Port, KEYPAD_ROW_4_Pin)


#define KEYPAD_ROW_HIGH_BUT_1 \
{\
	KEYPAD_ROW_1_LOW;\
	KEYPAD_ROW_2_HIGH;\
	KEYPAD_ROW_3_HIGH;\
	KEYPAD_ROW_4_HIGH;\
}

#define KEYPAD_ROW_HIGH_BUT_2 \
{\
	KEYPAD_ROW_1_HIGH;\
	KEYPAD_ROW_2_LOW;\
	KEYPAD_ROW_3_HIGH;\
	KEYPAD_ROW_4_HIGH;\
}

#define KEYPAD_ROW_HIGH_BUT_3 \
{\
	KEYPAD_ROW_1_HIGH;\
	KEYPAD_ROW_2_HIGH;\
	KEYPAD_ROW_3_LOW;\
	KEYPAD_ROW_4_HIGH;\
}

#define KEYPAD_ROW_HIGH_BUT_4 \
{\
	KEYPAD_ROW_1_HIGH;\
	KEYPAD_ROW_2_HIGH;\
	KEYPAD_ROW_3_HIGH;\
	KEYPAD_ROW_4_LOW;\
}


#define KEYPAD_COLUMN_1_CHECK			!XY_GPIO_GetInputPinValue(KEYPAD_COLUMN_1_GPIO_Port, KEYPAD_COLUMN_1_Pin)
#define KEYPAD_COLUMN_2_CHECK			!XY_GPIO_GetInputPinValue(KEYPAD_COLUMN_2_GPIO_Port, KEYPAD_COLUMN_2_Pin)
#define KEYPAD_COLUMN_3_CHECK			!XY_GPIO_GetInputPinValue(KEYPAD_COLUMN_3_GPIO_Port, KEYPAD_COLUMN_3_Pin)
#define KEYPAD_COLUMN_4_CHECK			!XY_GPIO_GetInputPinValue(KEYPAD_COLUMN_4_GPIO_Port, KEYPAD_COLUMN_4_Pin)

#define KEYPAD_NO_PRESSED					(uint8_t)0xFF

typedef enum {
	KEYPAD_Button_0 = 0x00,                     /*!< Button 0 code */
	KEYPAD_Button_1 = 0x01,                     /*!< Button 1 code */
	KEYPAD_Button_2 = 0x02,                     /*!< Button 2 code */
	KEYPAD_Button_3 = 0x03,                     /*!< Button 3 code */
	KEYPAD_Button_4 = 0x04,                     /*!< Button 4 code */
	KEYPAD_Button_5 = 0x05,                     /*!< Button 5 code */
	KEYPAD_Button_6 = 0x06,                     /*!< Button 6 code */
	KEYPAD_Button_7 = 0x07,                     /*!< Button 7 code */
	KEYPAD_Button_8 = 0x08,                     /*!< Button 8 code */
	KEYPAD_Button_9 = 0x09,                     /*!< Button 9 code */
	KEYPAD_Button_STAR = 0x0A,                  /*!< Button START code */
	KEYPAD_Button_HASH = 0x0B,                  /*!< Button HASH code */
	KEYPAD_Button_A = 0x0C,	                   /*!< Button A code. Only on large size */
	KEYPAD_Button_B = 0x0D,	                   /*!< Button B code. Only on large size */
	KEYPAD_Button_C = 0x0E,	                   /*!< Button C code. Only on large size */
	KEYPAD_Button_D = 0x0F,	                   /*!< Button D code. Only on large size */
	KEYPAD_Button_NOPRESS = KEYPAD_NO_PRESSED
} KEYPAD_Button_t;


static inline char *stringFromKeypadButton(KEYPAD_Button_t key)
{
    static char *strings[] = { 	"		KEYPAD_Button_0", "KEYPAD_Button_1", "KEYPAD_Button_2", "KEYPAD_Button_3",
										"KEYPAD_Button_4", "KEYPAD_Button_5", "KEYPAD_Button_6", "KEYPAD_Button_7",
										"KEYPAD_Button_8", "KEYPAD_Button_9", "KEYPAD_Button_STAR", "KEYPAD_Button_HASH",
										"KEYPAD_Button_A", "KEYPAD_Button_B", "KEYPAD_Button_C", "KEYPAD_Button_D"
    						};

    return strings[key];
}

uint8_t KEYPAD_READ(void);

void KEYPAD_Init(void);

void KEYPAD_Debounce_Delay(uint32_t debounceDelay);


#endif
