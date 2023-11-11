#ifndef _USART_H
#define _USART_H

#include "main.h"

/* ´®¿Ú0 */
void Usart0tInit(void);											//For esp8266   9.6 rx   9.7 tx
void USART0PutChar(char ch);
void USART0PutString(char str[]);

/* ´®¿Ú1*/

void Usart1tInit(void);											//For srceen   3.2 rx   3.3 tx
void USART1PutChar(char ch);
void USART1PutString(char str[]);

#endif	



