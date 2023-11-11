#ifndef __task_manage_H
#define __task_manage_H
#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"

#define Interface 2//��������
#define StrMax    10//�������ݴ�С

extern u32 SysTimer;


void Main_Menu(u32 Key_Value, u8* Task_ID);
void LCD_Show_ModeCEInfo(u16 x0, u8 start_info, u8 current_deal_info);
void Copybuf2dis(u8 *source, u8 dis[StrMax], u8 dispoint, u8 FloatNum, u8 CursorEn);
void Set_PointFre(u32 Key_Value, u8* Task_ID);
void Sweep_Fre(u32 Key_Value, u8* Task_ID);
void Move_Pha(u32 Key_Value, u8* Task_ID);
void Jump_Fre(u32 Key_Value, u8* Task_ID);

void Task0_PointFre(u32 Key_Value);
void Task1_Square(u32 Key_Value);
void Task2_Triangular(u32 Key_Value);
void Task3_SweepFre(u32 Key_Value);
void fre_buf_change(u8 *strbuf);

#endif
