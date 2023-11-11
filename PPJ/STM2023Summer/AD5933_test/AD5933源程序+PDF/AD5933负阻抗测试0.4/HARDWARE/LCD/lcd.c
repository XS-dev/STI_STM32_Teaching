
#include "delay.h"
#include "lcd.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "chinese.h"
u8 LCD_GRAM[128][8];
/*��ʼ��LCD_GPIO*/
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE
	GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);						 //PBE �����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;		
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOE
	GPIO_SetBits(GPIOD,GPIO_Pin_2);						 //PBE �����

}

/*дָ� LCD ģ��*/
void transfer_command(int data1)
{
	char i;
	
	cs1=0;
	rs=0;
	
	for(i=0;i<8;i++)
	{
		sclk=0;
		if(data1&0x80) sid=1;
		else sid=0;
		sclk=1;
		data1=data1<<=1;
	}
}

/*д���ݵ� LCD ģ��*/
void transfer_data(int data1)
{
	char i;
	
	cs1=0;
	rs=1;
	
	for(i=0;i<8;i++)
	{
		sclk=0;
		if(data1&0x80) sid=1;
		else sid=0;
		sclk=1;
		data1=data1<<=1;
	}
}

/*LCD ģ���ʼ��*/
void initial_lcd(void)
{
	LCD_GPIO_Init(); /*GPIO��ʼ��*/
	
	cs1=0;
	reset=0; /*�͵�ƽ��λ*/
	delay_ms(100);
	reset=1; /*��λ���*/
	delay_ms(20);
	transfer_command(0xe2); /*��λ*/
	delay_ms(5);
	transfer_command(0x2c); /*��ѹ���� 1*/
	delay_ms(5);
	transfer_command(0x2e); /*��ѹ���� 2*/
	delay_ms(5);
	transfer_command(0x2f); /*��ѹ���� 3*/
	delay_ms(5);
	transfer_command(0x23); /*�ֵ��Աȶ�,�����÷�Χ 0x20~0x27*/
	transfer_command(0x81); /*΢���Աȶ�*/
	transfer_command(0x28); /*0x1a,΢���Աȶȵ�ֵ,�����÷�Χ 0x00~0x3f*/
	transfer_command(0xa2); /*1/9 ƫѹ��(bias)*/
	transfer_command(0xc8); /*��ɨ��˳��:���ϵ���*/
	transfer_command(0xa0); /*��ɨ��˳��:������*/
//	transfer_command(0xc0); /*��ɨ��˳��:���ϵ���*/
//	transfer_command(0xa1); /*��ɨ��˳��:������*/
	transfer_command(0x40); /*��ʼ��:��һ�п�ʼ*/
	transfer_command(0xaf); /*����ʾ*/
	cs1=1;
}

/*����LCD��ַ*/
void lcd_address(u8 page,u8 column)
{
	cs1=0;
	column=column;  //����ƽ����˵�ĵ� 1 ��,�� LCD ���� IC ���ǵ� 0 ��.���������ȥ 1.
	page=page;
	//����ҳ��ַ.ÿҳ�ǵ� 8 ��.һ������� 64 �б��ֳ� 8 ��ҳ. ����ƽ����˵�ĵ� 1 ҳ,�� LCD ���� IC ���ǵ� 0 ҳ.���������ȥ 1.*/
	transfer_command(0xb0+page); 
	transfer_command(((column>>4)&0x0f)+0x10); //�����е�ַ�ĸ� 4 λ
	transfer_command(column&0x0f);  //�����е�ַ�ĵ� 4 λ
}

//�����Դ浽LCD		 
void LCD_Refresh_Gram(void)
{
	u8 i,n;		
	cs1=0;
	for(i=0;i<8;i++)  
	{
		lcd_address(i,0);
		for(n=0;n<128;n++)
		{
			transfer_data(LCD_GRAM[n][i]);
		}
	}
	cs1=1;
}
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void LCD_Clear(void)
{
	u8 i,n;  
	cs1=0;
	for(i=0;i<8;i++)for(n=0;n<128;n++)LCD_GRAM[n][i]=0x00;  
	cs1=1;
	LCD_Refresh_Gram();//������ʾ
}
void LCD_draw_Square(u8 x1,u8 y1,u8 x2,u8 y2)
{
	LCD_Fill(x1,y1,x1,y2,1);
	LCD_Fill(x1,y1,x2,y1,1);
	LCD_Fill(x1,y2,x2,y2,1);
	LCD_Fill(x2,y1,x2,y2,1);
}

//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���
void LCD_draw_Point(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
//	cs1=0;
	pos=y/8;
	bx=y%8;
	temp=1<<bx;
	if(t)LCD_GRAM[x][pos]|=temp;
	else LCD_GRAM[x][pos]&=~temp;
//	cs1=1;
}
void LCD_Move_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127)	x -= 127;
	if(y>63)	y -= 63;
	pos=y/8;
	bx=y%8;
	temp=1<<(bx);
	if(t)LCD_GRAM[x][pos]|=temp;
	else LCD_GRAM[x][pos]&=~temp;	    
}
void LCD_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)LCD_draw_Point(x,y,dot);
	}
//	LCD_Refresh_Gram();//������ʾ
}

//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  

void Set_Point(u8 x,u8 y)
{
	static u8 time=0,set=5,xbuf=0,ybuf=0;
	
	time++;
	if(xbuf!=x || ybuf!=y)	LCD_Fill(xbuf,ybuf,xbuf,ybuf+16,0);
	if(time < set)
	{
		LCD_Fill(x,y,x,y+16,1);
	}else if(time < set*2)
	{
		LCD_Fill(x,y,x,y+16,0);
	}else time=0;
	xbuf=x;
	ybuf=y;
}

//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void LCD_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{
	u8 temp,t,t1;
	u8 y0=y;
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
			if(size==12)temp=asc2_1206[chr][t];  //����1206����
			else temp=asc2_1608[chr][t];		 //����1608���� 	                          
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)LCD_draw_Point(x,y,mode);
				else LCD_draw_Point(x,y,!mode);
				temp<<=1;
				y++;
				if((y-y0)==size)
				{
					y=y0;
					x++;
					break;
				}
			}  	 
    }
}
void LCD_Show_chineseChar(u8 x,u8 y,char *chr, u8 mode)
{
	u8 temp,t,t1;
	u8 y0=y;		
	
	for(t=0;t<32;t++)
	{
		temp = *chr;
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)
				LCD_Move_DrawPoint(x,y,mode);
			else
			LCD_Move_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
			}
		} 
		chr++;
	}  
}
void	WriteA_Chinese(u8 mode,unsigned char x, unsigned char y, const u8 *s)
{
	unsigned char j;

	if (x > 127) return;
	if (y > 63) return;

	for (j = 0; j < sizeof(GB_16)/34;j++)
	{
		if(s[0] == (char)GB_16[j].Index[0] && s[1] == (char)GB_16[j].Index[1])
		{
			LCD_Show_chineseChar(x, y, &GB_16[j].Msk[0], mode);
			x+=16;
			break;
		}
	}
}
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void LCD_Show_CEStr(u16 x0,u16 y0, u8 *pp)
{
	LCD_ShowAllString(1,x0,y0*8,pp);
}
void LCD_Show_ModeCEStr(u16 x0,u16 y0, u8 *pp, u8 show_mode)
{
	LCD_ShowAllString(show_mode,x0,y0*8,pp);

}
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	LCD_ShowAllString(1,x,y*8,chr);

}


void LCD_ShowString(u8 mode,u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;LCD_Clear();}
        LCD_ShowChar(x,y,*p,16,mode);	 
        x+=8;
        p++;
    }  
}
void LCD_ShowString_12(u8 mode,u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;LCD_Clear();}
        LCD_ShowChar(x,y,*p,12,mode);	 
        x+=8;
        p++;
    }  
}
void LCD_ShowAllString(u8 mode,u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
			if(x>MAX_CHAR_POSX)return;
			if(y>MAX_CHAR_POSY)return;
			if(*p>127)
			{
				WriteA_Chinese(mode,x,y,p);
				p+=2;
				x+=16;
			}else
			{
				LCD_ShowChar(x,y,*p,16,mode);
				x+=8;
				p++;				
			}
    }  
}	 

void	Write_Chinese_String(u8 mode,unsigned char x, unsigned char y, char *s)
{
	unsigned char i, j;

	if (x > 127) return;
	if (y > 63) return;
	for (i = 0; s[i] != '\0'; i+=2)
	{
		for (j = 0; j < sizeof(GB_16)/34;j++)
		{
			if(s[i] == (char)GB_16[j].Index[0] && s[i + 1] == (char)GB_16[j].Index[1])
			{
				LCD_Show_chineseChar(x, y, &GB_16[j].Msk[0], mode);
				x+=16;
				break;
			}
		}
	}
}




/***********************************************************
* �������ƣ�LCD_DrawLine
* �������ܣ�LCD���ߺ���
*           ��ڲ���: x1,y1��������꣩x2,y2���յ����꣩c(��ɫ)   
*			���ڲ������� 
***********************************************************/

// �������� a ��b ��ֵ    
__inline void swap_int(u16 *a, u16 *b)   
{    
    *a ^= *b;    
    *b ^= *a;    
    *a ^= *b;    
}    
  
// Bresenham's line algorithm    
  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u8 c)   
{        
    u16 dx =abs( x2 - x1), // ˮƽ����   
        dy =abs( y2 - y1), // ��ֱ����   
        yy = 0;    		   // �Ƕ��Ƿ����45���־
  
	int ix ,    
        iy,    
        cx ,    
        cy ,    
        n2dy,    
        n2dydx ,    
        d ; 
    if(dx < dy)  // ��б�ʴ��� 1 ʱ��dx��dy ����, ���Ƕȴ���45�� 
    {    
        yy = 1;              // ���ñ�־λ  
        swap_int(&x1, &y1);  // ��������  
        swap_int(&x2, &y2);    
        swap_int(&dx, &dy);    
    }        
    ix = (x2 - x1) > 0 ? 1 : -1; // �ж��Ƿ��1���Ǽ�һ    
    iy = (y2 - y1) > 0 ? 1 : -1;    
    cx = x1;  //  x��ֵ  
    cy = y1;  //  y��ֵ  
    n2dy = dy * 2;    		 // ��Ҫ�Ƚϵĸ�����ֵ
    n2dydx = (dy - dx) * 2;    
    d = dy * 2 - dx;     

// ���ֱ���� x ��ļнǴ���45��    
    if(yy)  
    {   
        while(cx != x2) // �����Ƿ�ﵽ�յ�  
        {    
            if(d < 0)  
            {    
                d += n2dy;    
            }   
            else   
            {    
                cy += iy;    
                d += n2dydx;    
            }    
            LCD_draw_Point( cy, cx, c); // ����   
            cx += ix;    
        }    
    }
  
// ���ֱ���� x ��ļн�С��45��    
    else   
    {   
        while(cx != x2)   
        {    
            if(d < 0)  
            {    
                d += n2dy;    
            }  
            else   
            {    
                cy += iy;    
                d += n2dydx;    
            }    
            LCD_draw_Point( cx, cy, c);    
            cx += ix;    
        }    
    }    
}   

/**********************************************************
* �������ƣ�LCD_DrawRectangle
* �������ܣ�LCD�����κ���
*           ��ڲ���: x1,y1���Խ���������꣩x2,y2���Խ����յ����꣩color(��ɫ)   
*			���ڲ������� 
***********************************************************/

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u8 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}

/**********************************************************
* �������ƣ�LCD_Drawcircle
* �������ܣ���ָ��λ�û�һ��ָ����С��Բ
*           ��ڲ���: (x,y)-(���ĵ����꣩r(�뾶)
*                     fill(Ϊ�Ƿ����)   c(��ɫ)   
*			���ڲ������� 
***********************************************************/
	  
__inline void draw_circle_8( u16 xc, u16 yc, u16 x, u16 y, u8 c)   
	{    
	    // ���� c Ϊ��ɫֵ    
	    LCD_draw_Point( xc + x, yc + y, c);    
	    LCD_draw_Point( xc - x, yc + y, c);    
	    LCD_draw_Point( xc + x, yc - y, c);   
	    LCD_draw_Point( xc - x, yc - y, c);
	    LCD_draw_Point( xc + y, yc + x, c);   
	    LCD_draw_Point( xc - y, yc + x, c);
	    LCD_draw_Point( xc + y, yc - x, c);
	    LCD_draw_Point( xc - y, yc - x, c);
	}       
//Bresenham's circle algorithm    
void LCD_Drawcircle( u16 xc, u16 yc, u16 r, u16 fill, u8 c)  
	{    
	    // (xc, yc) ΪԲ�ģ�r Ϊ�뾶    
	    // fill Ϊ�Ƿ����    
	    // c Ϊ��ɫֵ       
	    // ���Բ��ͼƬ�ɼ������⣬ֱ���˳�    
	  
	   int x = 0, y = r, yi, d;    
	       d = 3 - 2 * r; 

//	    if(xc + r < 0 || xc - r >= 128 || yc + r < 0 || yc - r >= 64)   
//	    {
//	        return;  
//	    }     
	    if(fill)  
	    {    
	        // �����䣨��ʵ��Բ��    
	        while(x <= y)   
	        {    
	            for(yi = x; yi <= y; yi ++)    
	            {  
	                draw_circle_8(xc, yc, x, yi, c);    
	            }  
	            if(d < 0)   
	            {    
	                d = d + 4 * x + 6;    
	            }   
	            else   
	            {    
	                d = d + 4 * (x - y);    
	                y --;    
	            }    
	  
	            x++;    
	        }    
	    }   
	    else   
	    {    
	        // �������䣨������Բ��    
	        while (x <= y)   
	        {    
	            draw_circle_8(xc, yc, x, y, c);    
	            if(d < 0)   
	            {    
	                d = d + 4 * x + 6;    
	            }   
	            else   
	            {    
	                d = d + 4 * (x - y);    
	                y --;    
	            }    
	            x ++;    
	        }    
	    }    
	}   





