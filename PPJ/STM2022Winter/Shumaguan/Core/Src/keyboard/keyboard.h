#ifndef __keyboard_h
#define __keyboard_h
 
 
#include "main.h"
 
 
 
 
void Keyboard_GPIO_Config(void);		//初始化 矩阵按键的I/O口
 
void keyboard_scan(uint16_t *key_val);		//矩阵按键扫描函数
 
uint16_t fetch_key_value(void);				//返回自定义按键数值
 
 
#endif