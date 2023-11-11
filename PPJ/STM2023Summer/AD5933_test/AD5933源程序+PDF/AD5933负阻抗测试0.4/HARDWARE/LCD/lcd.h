
#ifndef __LCD_H
#define __LCD_H
#include "sys.h"

//#define cs1 PBout(5)
//#define reset PBout(6)
//#define rs PBout(7)
//#define sid PBout(8)
//#define sclk PBout(9)

#define cs1 PBout(5)
#define reset PBout(6)
#define rs PBout(7)
#define sclk PBout(8)
#define sid PBout(9)

//#define cs1 PAout(8)
//#define reset PAout(9)
//#define rs PAout(10)
//#define sclk PAout(11)
//#define sid PAout(12)
//#define EN_LCD PAout(13)

/*��ʼ��LCD_GPIO*/
void LCD_GPIO_Init(void);
/*дָ� LCD ģ��*/
void transfer_command(int data1);
/*д���ݵ� LCD ģ��*/
void transfer_data(int data1);
/*LCD ģ���ʼ��*/
void initial_lcd(void);
/*����LCD��ַ*/
void lcd_address(u8 page,u8 column);
/*ȫ������*/
void clear_screen(void);
/*��ָ��λ�û���*/
void LCD_draw_Point(u8 x,u8 y,u8 t);
//==================display a piture of 128*64 dots================
void full_display(void);
/*��ʾ 32x32 ����ͼ�񡢺��֡���Ƨ�ֻ� 32x32 ���������ͼ��*/
void display_graphic_32x32(u8 page,u8 column,u8 *dp);
/*��ʾ 16x16 ����ͼ�񡢺��֡���Ƨ�ֻ� 16x16 ���������ͼ��*/
void display_graphic_16x16(u8 page,u8 column,u8 *dp);
/*��ʾ 8x16 ����ͼ�񡢺��֡���Ƨ�ֻ� 8x16 ���������ͼ��*/
void display_graphic_8x16(u8 page,u8 column,u8 *dp);
/*��ʾ 8x16 �ַ���*/
void display_string_8x16(u16 page,u16 column,u8 *text);
/*��ʾ 5x7 �ַ���*/
void display_string_5x7(u16 page,u16 column,u8 *text);

void LCD_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void LCD_Move_DrawPoint(u8 x,u8 y,u8 t);
void LCD_draw_Point(u8 x,u8 y,u8 t);
void LCD_Clear(void)  ;
void LCD_Refresh_Gram(void);
void Set_Point(u8 x,u8 y);
void LCD_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void LCD_Show_chineseChar(u8 x,u8 y,char *chr, u8 mode);
void	WriteA_Chinese(u8 mode,unsigned char x, unsigned char y, const u8 *s);
void LCD_ShowString(u8 mode,u8 x,u8 y,const u8 *p);
void LCD_ShowAllString(u8 mode,u8 x,u8 y,const u8 *p);
void	Write_Chinese_String(u8 mode,unsigned char x, unsigned char y, char *s);
void LCD_draw_Square(u8 x1,u8 y1,u8 x2,u8 y2);
void LCD_Drawcircle( u16 xc, u16 yc, u16 r, u16 fill, u8 c);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 c);
void LCD_ShowString_12(u8 mode,u8 x,u8 y,const u8 *p);

void LCD_Show_CEStr(u16 x0,u16 y0, u8 *pp);
void LCD_Show_ModeCEStr(u16 x0,u16 y0, u8 *pp, u8 show_mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr);

#endif









