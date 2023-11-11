/**************************************************
RX = C10
TX = C11
**************************************************/

#ifndef _LCD_H
#define _LCD_H




#include "main.h"


extern int guzhang_flag;
extern int wave_result[480];
extern float INResistor  ;
extern float OUResistor  ;
extern float K1ZE 			 ;
extern float UPFre 		   ;


extern float x_pic ;
extern float y_pic ;



void bar(double process);

void sendresult(int number);


void sendwave(int wave);

void display_guzhang(void);
void show_delta(void);
void clean_wave(void);

#endif

