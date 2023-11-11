
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

/*初始化LCD_GPIO*/
void LCD_GPIO_Init(void);
/*写指令到 LCD 模块*/
void transfer_command(int data1);
/*写数据到 LCD 模块*/
void transfer_data(int data1);
/*LCD 模块初始化*/
void initial_lcd(void);
/*设置LCD地址*/
void lcd_address(u8 page,u8 column);
/*全屏清屏*/
void clear_screen(void);
/*在指定位置画点*/
void LCD_draw_Point(u8 x,u8 y,u8 t);
//==================display a piture of 128*64 dots================
void full_display(void);
/*显示 32x32 点阵图像、汉字、生僻字或 32x32 点阵的其他图标*/
void display_graphic_32x32(u8 page,u8 column,u8 *dp);
/*显示 16x16 点阵图像、汉字、生僻字或 16x16 点阵的其他图标*/
void display_graphic_16x16(u8 page,u8 column,u8 *dp);
/*显示 8x16 点阵图像、汉字、生僻字或 8x16 点阵的其他图标*/
void display_graphic_8x16(u8 page,u8 column,u8 *dp);
/*显示 8x16 字符串*/
void display_string_8x16(u16 page,u16 column,u8 *text);
/*显示 5x7 字符串*/
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









