#ifndef __Measure_H__
#define __Measure_H__

#include "main.h"

void Mea_Input(int mode);

void Mea_Output(int mode);

float Mea_Scan_Output(void);
void Mea_Scan(void);
void Upper_K_Find(void);
float Mea_Scan_Low(void);
void Mea_Input_Low(void);

void QuickSort(uint16_t arr[], int low, int high);

void Start_Input_Resistor_Measure(void);

void Stop_Input_Resistor_Measure(void);

void Open_DC(void);
	
void Open_AC(void);

void Start_Output_Resistor_Measure(void);
void Close_All(void);

#endif