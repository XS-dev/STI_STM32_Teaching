//******************************************************
//Copyright(C)2007,桂林电子科技大学XXXX科技协会
//                     AD9854Driver
//					
//文件名称:	AD9854Driver
//文件标识:(内参)(公开)
//摘    要:
//			1.XXX;
//			2.XXX
//			3.XXX 
//          
//
//当前版本:1.0
//作    者:pdaabao
//完成日期:2007.05.29
//
//取代版本:无
//原 作 者:无
//完成日期:无
//******************************************************
#ifndef _AD9854DRIVER_H
#define _AD9854DRIVER_H

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
//是否用调整相位
//#define PHASE_EN

//选择使用的模式
#define SINGLESTONE    1      //单频率模式
//#define UNRAMPED_FSK 1            
//#define RAMPED_FSK   1
//#define CHIRP        1
//#define BPSK         1

//根据晶振的频率选择
#define _Freq_131M_
//#define _Freq_120M_
//#define _Freq_160M_
//#define _Freq_80M_

//并行预定义
#define AddIO_AD9854   P2  //地址口
#define DataIO_AD9854  P0  //数据口
//并行位定义
sbit RD_AD9854 = P3^4;	   //写使能，低有效
sbit WR_AD9854 = P3^5;

//暂时不用
sbit OSK_AD9854 = P3^2;	   //SHAPED KEYING
sbit FDATA_AD9854 = P3^3;  //FSK/BPSK/HOLD

sbit Reset_AD9854 = P3^7;  	   //复位 高复位，低正常
sbit IO_UDClck_AD9854 = P3^6;  //更新时钟

//函数声明
//*********************以下为单频模式**********************
//函数说明：写数据到AD9854
extern void PWriteAD9854(uchar ucAdd, uchar ucDat);  

//函数说明：设置频率值 
extern void PWriteAD9854Freq(ulong ulFreqOut);

//函数说明：设置I通道的幅度
extern void PWriteAD9854AmplChanI(uint ulAmpl);

//函数说明：设置Q通道的幅度
extern void PWriteAD9854AmplChanQ(uint ulAmpl);

//函数说明：设置I通道的幅度，送入的数据是毫伏
extern void PSet_mv_AD9854ChanI(uint ucAmpl);

//函数说明：设置Q通道的幅度，送入的数据是毫伏
extern void PSet_mv_AD9854ChanQ(uint ucAmpl);

//函数说明：初始化AD9854，模式0
extern void InitialAD9854(void);
//***********************************************************

#endif