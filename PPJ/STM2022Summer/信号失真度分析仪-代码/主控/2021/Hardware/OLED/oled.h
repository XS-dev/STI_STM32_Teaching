#ifndef __OLED_H
#define __OLED_H	

#include "main.h"
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ

#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    


                         // GND //   ��Դ��
                         // VCC // ��5V��3.3v��Դ
 #define  SCL_PORT  GPIO_PORT_P2   // �ӣ�SCL��
 #define  SCL_PIN   GPIO_PIN7      // �ӣ�SCL��
 #define  SDA_PORT  GPIO_PORT_P2   // �ӣ�SDA��
 #define  SDA_PIN   GPIO_PIN6      // �ӣ�SDA��
 #define  RES_PORT  GPIO_PORT_P2   // ��
 #define  RES_PIN   GPIO_PIN4      // ��
 #define  DC_PORT   GPIO_PORT_P5   // ��
 #define  DC_PIN    GPIO_PIN6      // ��
 #define  CS_PORT   GPIO_PORT_P6   // ��    
 #define  CS_PIN    GPIO_PIN6      // ��  
//-----------------OLED�˿ڶ���----------------  					   

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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//��ʾ����
void OLED_ShowString(u8 x,u8 y, u8 *p);	     //��ʾ�ַ��� 
void OLED_Set_Pos(unsigned char x, unsigned char y);  //��ʾ���λ��
void OLED_ShowCHinese(u8 x,u8 y,u8 no); //��ʾ����
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);//��ʾͼƬ
#endif  
	 



