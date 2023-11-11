#ifndef __OLED_H
#define __OLED_H	

#include "main.h"
//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    


                         // GND //   电源地
                         // VCC // 接5V或3.3v电源
 #define  SCL_PORT  GPIO_PORT_P2   // 接（SCL）
 #define  SCL_PIN   GPIO_PIN7      // 接（SCL）
 #define  SDA_PORT  GPIO_PORT_P2   // 接（SDA）
 #define  SDA_PIN   GPIO_PIN6      // 接（SDA）
 #define  RES_PORT  GPIO_PORT_P2   // 接
 #define  RES_PIN   GPIO_PIN4      // 接
 #define  DC_PORT   GPIO_PORT_P5   // 接
 #define  DC_PIN    GPIO_PIN6      // 接
 #define  CS_PORT   GPIO_PORT_P6   // 接    
 #define  CS_PIN    GPIO_PIN6      // 接  
//-----------------OLED端口定义----------------  					   

#define OLED_SCLK_Clr() GPIO_setOutputLowOnPin(SCL_PORT,SCL_PIN )//CLK
#define OLED_SCLK_Set() GPIO_setOutputHighOnPin(SCL_PORT,SCL_PIN )                  

#define OLED_SDIN_Clr() GPIO_setOutputLowOnPin(SDA_PORT,SDA_PIN)//DIN
#define OLED_SDIN_Set() GPIO_setOutputHighOnPin(SDA_PORT,SDA_PIN)                

#define OLED_RST_Clr()  GPIO_setOutputLowOnPin(RES_PORT,RES_PIN)//RES
#define OLED_RST_Set()  GPIO_setOutputHighOnPin(RES_PORT,RES_PIN)                 

#define OLED_DC_Clr()   GPIO_setOutputLowOnPin(DC_PORT,DC_PIN)//DC
#define OLED_DC_Set()   GPIO_setOutputHighOnPin(DC_PORT,DC_PIN)                 
 		     
#define OLED_CS_Clr()   GPIO_setOutputLowOnPin(CS_PORT,CS_PIN )//CS
#define OLED_CS_Set()   GPIO_setOutputHighOnPin(CS_PORT,CS_PIN )                 

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//显示数字
void OLED_ShowString(u8 x,u8 y, u8 *p);	     //显示字符串 
void OLED_Set_Pos(unsigned char x, unsigned char y);  //显示光标位置
void OLED_ShowCHinese(u8 x,u8 y,u8 no); //显示汉字
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);//显示图片
#endif  
	 



