#ifndef __keyboard_h
#define __keyboard_h
 
 
#include "main.h"
 
 
 
 
void Keyboard_GPIO_Config(void);		//��ʼ�� ���󰴼���I/O��
 
void keyboard_scan(uint16_t *key_val);		//���󰴼�ɨ�躯��
 
uint16_t fetch_key_value(void);				//�����Զ��尴����ֵ
 
 
#endif