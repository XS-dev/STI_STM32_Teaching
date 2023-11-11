#ifndef _MEASURE_H_
#define _MEASURE_H_


#include "main.h"
#include "math.h"
#include <arm_math.h>

void calculate_hanning(void);
void voltage_process(void);
void peek_measure(float multi);

extern uint16_t send_signal[150];
extern float base_ele;
extern float two_ele;
extern float three_ele;
extern float four_ele;
extern float five_ele;
extern float THDx;
extern uint16_t period_point;
extern float voltage_peek;
extern int fre_index2;
extern uint32_t final_index;



#endif

