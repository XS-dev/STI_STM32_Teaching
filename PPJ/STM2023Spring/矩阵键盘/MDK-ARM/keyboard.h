#ifndef __keyboard_h
#define __keyboard_h
 
 
#include "main.h"
 
//#define R4_Pin GPIO_PIN_9
//#define R4_GPIO_Port GPIOD
//#define R4_EXTI_IRQn EXTI9_5_IRQn
//#define R3_Pin GPIO_PIN_11
//#define R3_GPIO_Port GPIOD
//#define R3_EXTI_IRQn EXTI15_10_IRQn
//#define R2_Pin GPIO_PIN_13
//#define R2_GPIO_Port GPIOD
//#define R2_EXTI_IRQn EXTI15_10_IRQn
//#define R1_Pin GPIO_PIN_15
//#define R1_GPIO_Port GPIOD
//#define R1_EXTI_IRQn EXTI15_10_IRQn
//#define C1_Pin GPIO_PIN_7
//#define C1_GPIO_Port GPIOC
//#define C2_Pin GPIO_PIN_9
//#define C2_GPIO_Port GPIOC
//#define C3_Pin GPIO_PIN_9
//#define C3_GPIO_Port GPIOA
//#define C4_Pin GPIO_PIN_11
//#define C4_GPIO_Port GPIOA
 
void Keyboard_Row_Output(void);
void Keyboard_Column_Input(void);
void Keyboard_Column_Output(void);
void Keyboard_Row_Input(void);
void delay_keyboard(void);
void Keyboard_Row_Ext(void);

uint16_t scan_key(void);
uint16_t scan_key_Column(void);
uint16_t scan_key_row(void);


#endif