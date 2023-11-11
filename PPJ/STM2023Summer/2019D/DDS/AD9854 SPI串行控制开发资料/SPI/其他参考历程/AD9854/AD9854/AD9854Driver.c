//******************************************************
//Copyright(C)2007,桂林电子科技大学XXXXXX科技协会
//                    AD9854Driver
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
#include<reg51.h>
#include"AD9854Driver.h"

//*******************************************
//函数名称:void PWriteAD9854(uchar ucAdd, uchar ucDat)
//函数功能:AD9854基本并行写操作
//形式参数:uchar ucAdd, uchar ucDat
//行参说明:写入的地址，写入的数据
//返回参数:无        
//使用说明:
//*******************************************
void PWriteAD9854(uchar ucAdd, uchar ucDat)
{
    
    AddIO_AD9854 = ucAdd;
    DataIO_AD9854 = ucDat;
	WR_AD9854 = 0;          //开始导入地址，且写数据
    WR_AD9854 = 1;          //上升沿，高电平写无效
    
}
//*******************************************
//函数名称:uchar PReadAD9854(uchar ucAdd)
//函数功能:AD9854基本并行读操作
//形式参数:uchar ucAdd
//行参说明:读数据的地址
//返回参数:返回该地址的数据        
//使用说明:
//*******************************************
/*uchar PReadAD9854(uchar ucAdd)
{
    uchar tmp;
    RD_AD9854 = 0;
    AddIO_AD9854 = ucAdd;
    RD_AD9854 = 1;
    tmp = DataIO_AD9854;
    return tmp & 0x3f;
} */
//*******************************************
//函数名称:void PWriteAD9854Freq(ulong ulFreqOut)
//函数功能:并行写入AD9854的频率
//形式参数:uchar ucAdd
//行参说明:写到哪个相位寄存器常用word 1, 设置的频率值
//返回参数:无        
//使用说明:
//*******************************************
void PWriteAD9854Freq(ulong ulFreqOut)
{
    //FTW = ulFreqOut * 2^48/倍频后的时钟			//倍频后的时钟
    //FTW = ulFreqOut * 7036874.41770;	 0x6b5fca   //40M内部系统时钟
	//FTW = ulFreqOut * 14073748.8355;	 0xd6bf94	//20M内部系统时钟
	//FTW = ulFreqOut * 3518437.12088;	 0x35afe5	//80M内部系统时钟
	//FTW = ulFreqOut * 2814749.76710;	 0x2af2cb	//100M内部系统时钟
	//FTW = ulFreqOut * 2345624.80592;   0x23ca98   //120M内部系统时钟
	//FTW = ulFreqOut * 2147483.648;     0x20c49b   //32.768*4M
	//FTW = ulFreqOut * 1759218.06444;	 0x1ad7f2	//160M内部系统时钟
	#ifdef _Freq_160M_
    uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

	Freqbuff = ulFreqOut * 0xf2;       //以160M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  (ulFreqOut * 0xd7);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  (ulFreqOut * 0x1a);
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] =  Freqbuff % 0x100;
	//Freqbuff /= 0x100;
	FreqArray[5] = Freqbuff / 0x100; 
    #endif
	
    //80M
    #ifdef _Freq_80M_
	uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

    Freqbuff = 	ulFreqOut * 0xe5;      //以80M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  ulFreqOut * 0xaf;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  ulFreqOut * 0x35;
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] = Freqbuff % 0x100;
	//Freqbuff /= 0x100;

	FreqArray[5] = Freqbuff / 0x100;
	//Freqbuff /= 0x100; 
    #endif
    
    #ifdef _Freq_131M_
	uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

    Freqbuff = 	ulFreqOut * 0x9b;      //以32.7*4M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  ulFreqOut * 0xc4;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  ulFreqOut * 0x20;
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] = Freqbuff % 0x100;
	//Freqbuff /= 0x100;

	FreqArray[5] = Freqbuff / 0x100;
	//Freqbuff /= 0x100;
    #endif

	//120M
    #ifdef _Freq_120M_
	 uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

	Freqbuff = ulFreqOut * 0x98;       //以120M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  (ulFreqOut * 0xca);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  (ulFreqOut * 0x23);
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] =  Freqbuff % 0x100;
	//Freqbuff /= 0x100;
	FreqArray[5] = Freqbuff / 0x100;
	#endif

	for (count=6; count; )
	{
	    PWriteAD9854( Add++, FreqArray[--count]);
	}
}
//*******************************************
//函数名称:void PWriteAD9854Phase(uint uiPhVal)
//函数功能:并行设置AD9854的初始相位
//形式参数:uint uiPhVal 
//行参说明:设置的初始相位	uiPhVal为0~16383
//返回参数:无        
//使用说明:
//         360-----------16383
//         0-------------0
//*******************************************
#ifdef PHASE_EN
void PWriteAD9854Phase(uint uiPhVal)
{
    	
    PWriteAD9854( 0x00, uiPhVal/0x100);
    PWriteAD9854( 0x01, uiPhVal%0x100);
}
#endif
//*******************************************
//函数名称:void PWriteAD9854AmplChanI(ulong ulAmpl)
//函数功能:并行写入AD9854的I通道的振幅
//形式参数:ulong ulAmpl 
//行参说明:设置的振幅值	ulAmpl为0~4096
//返回参数:无        
//使用说明:
//         0.5v-----------1111 1111 1111
//         0.0v-----------0000 0000 0000
//*******************************************
void PWriteAD9854AmplChanI(uint ulAmpl)
{
    
	//uchar Htmp, Ltmp;

	//Ltmp = (uint)(ulAmpl / 805) & 0x00ff;
	//Htmp = (uint)((ulAmpl / 805) >> 8) & 0x00ff;

    PWriteAD9854( 0x21, ulAmpl/0x100);
    PWriteAD9854( 0x22, ulAmpl%0x100);
}
//*******************************************
//函数名称:void PWriteAD9854AmplChanQ(ulong ulAmpl)
//函数功能:并行写入AD9854的Q通道的振幅
//形式参数:ulong ulAmpl 
//行参说明:设置的振幅值
//返回参数:无        
//使用说明:
//         0.5v-----------1111 1111 1111
//         0.0v-----------0000 0000 0000
//*******************************************
void PWriteAD9854AmplChanQ(uint ulAmpl)
{
    
	//uchar Htmp, Ltmp;

	//Ltmp = (ulAmpl / 805) & 0x00ff;
	//Htmp = ((ulAmpl / 805) >> 8) & 0x00ff;

    PWriteAD9854( 0x23, ulAmpl/0x100);
    PWriteAD9854( 0x24, ulAmpl%0x100);
}
//*******************************************
//函数名称:void PSet_mv_AD9854ChanI(ulong ulAmpl)
//函数功能:并行设置AD9854的I通道的电压值
//形式参数:uint ulAmpl,欲将设定的输出电压幅值，这里一般假设输出阻抗100 
//行参说明:设置的振幅值	ulAmpl为0~492mv
//返回参数:无        
//使用说明:
//*******************************************
void PSet_mv_AD9854ChanI(uint ucAmpl)
{
      uint Vtmp;
      Vtmp = (ulong)(ucAmpl)*8325/1000;     //每毫伏对应的数字量为8.32317
      PWriteAD9854AmplChanI( Vtmp );
}
//*******************************************
//函数名称:void PSet_mv_AD9854ChanQ(ulong ulAmpl)
//函数功能:并行设置AD9854的Q通道的电压值
//形式参数:uint ulAmpl 
//行参说明:设置的振幅值	ulAmpl为0~492mv               //ulAmpl为0~4920
//返回参数:无        
//使用说明:
//*******************************************
void PSet_mv_AD9854ChanQ(uint ucAmpl)
{
      uint Vtmp;
      Vtmp = (ulong)(ucAmpl)*8325/1000;     //每毫伏对应的数字量为8.32317-----8.325203
	  //Vtmp = (ulong)(ucAmpl)*8324/10000;           //每毫伏对应的数字量为8.32317-----8.325203  
      PWriteAD9854AmplChanQ( Vtmp );
}

//*******************************************
//函数名称:void InitialAD9854(void)
//函数功能:初始化AD9854
//形式参数:无
//行参说明:无
//返回参数:无        
//使用说明:使用AD9854必须要初始化
//*******************************************
#ifdef SINGLESTONE
void InitialAD9854(void)
{
    IO_UDClck_AD9854 = 0;//更新时钟	上升沿更新
	RD_AD9854 = 1;       //先禁止读写
	WR_AD9854 = 1;
    
	Reset_AD9854 = 1;	 //复位	高复位
	Reset_AD9854 = 0;    //     低正常 
	              
    PWriteAD9854( 0x1d, 0x10 );   //关闭比较器
	PWriteAD9854( 0x1e, 0x04 );	  //设置系统时钟倍频为四倍频
	PWriteAD9854( 0x1f, 0x00 );	  //外部更新时钟,模式0
	PWriteAD9854( 0x20, 0x60 );	  //
	IO_UDClck_AD9854 = 1;         //更新时钟	上升沿更新
	IO_UDClck_AD9854 = 0;
}
#endif
//********************************************
//*************以下为FSK模式******************
//*******************************************
//函数名称:void FSK_InitialAD9854(void)
//函数功能:初始化AD9854,FSK模式
//形式参数:无
//行参说明:无
//返回参数:无        
//使用说明:使用AD9854必须要初始化
//         基带频率应设1K左右
//         最高频率8~10K
//         最小频率0~2K
//*******************************************
#ifdef UNRAMPED_FSK
void FSK_InitialAD9854(void)
{
    IO_UDClck_AD9854 = 0;//更新时钟	上升沿更新
	RD_AD9854 = 1;       //先禁止读写
	WR_AD9854 = 1;
    
	Reset_AD9854 = 1;	 //复位	高复位
	Reset_AD9854 = 0;    //     低正常 
	              
    PWriteAD9854( 0x1d, 0x10 );   //关闭比较器
	PWriteAD9854( 0x1e, 0x04 );	  //设置系统时钟倍频为四倍频
	PWriteAD9854( 0x1f, 0x02 );	  //外部更新时钟,模式1
	PWriteAD9854( 0x20, 0x60 );	  //
	IO_UDClck_AD9854 = 1;         //更新时钟	上升沿更新
	IO_UDClck_AD9854 = 0;
}
#endif
//*******************************************
//函数名称:void SET_F1_FSK_AD9854( ulong ulF1)
//函数功能:设定FSK模式F1的频率
//形式参数:ulong ulF1
//行参说明:频率1的值
//返回参数:无        
//使用说明:使用AD9854必须要初始化
//*******************************************
#if (UNRAMPED_FSK | RAMPED_FSK)
void SET_F1_FSK_AD9854( ulong ulF1)
{   
	#ifdef _Freq_160M_
    uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

	Freqbuff = ulF1 * 0xf2;       //以160M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  (ulF1 * 0xd7);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  (ulF1 * 0x1a);
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] =  Freqbuff % 0x100;
	//Freqbuff /= 0x100;
	FreqArray[5] = Freqbuff / 0x100; 
    #endif
	
    //80M
    #ifdef _Freq_80M_
	uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

    Freqbuff = 	ulF1 * 0xe5;      //以80M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  ulF1 * 0xaf;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  ulF1 * 0x35;
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] = Freqbuff % 0x100;
	//Freqbuff /= 0x100;

	FreqArray[5] = Freqbuff / 0x100;
	//Freqbuff /= 0x100; 
    #endif
    
    #ifdef _Freq_131M_
	uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

    Freqbuff = 	ulF1 * 0x9b;      //以32.7*4M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  ulF1 * 0xc4;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  ulF1 * 0x20;
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] = Freqbuff % 0x100;
	//Freqbuff /= 0x100;

	FreqArray[5] = Freqbuff / 0x100;
	//Freqbuff /= 0x100;
    #endif

	//120M
    #ifdef _Freq_120M_
	 uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

	Freqbuff = ulF1 * 0x98;       //以120M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  (ulF1 * 0xca);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  (ulF1 * 0x23);
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] =  Freqbuff % 0x100;
	//Freqbuff /= 0x100;
	FreqArray[5] = Freqbuff / 0x100;
	#endif

	for (count=6; count; )
	{
	    PWriteAD9854( Add++, FreqArray[--count]);
	}
}
#endif
//*******************************************
//函数名称:void SET_F2_FSK_AD9854( ulong ulF2)
//函数功能:设定FSK模式F2的频率
//形式参数:ulong ulF2
//行参说明:频率2的值
//返回参数:无        
//使用说明:使用AD9854必须要初始化
//*******************************************
#if (UNRAMPED_FSK | RAMPED_FSK)
void SET_F2_FSK_AD9854( ulong ulF2 )
{
    //FDATA_AD9854 = 0;
	#ifdef _Freq_160M_
    uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x0A, count = 6;			 

	Freqbuff = ulF2 * 0xf2;       //以160M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100 (256)以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  (ulF2 * 0xd7);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  (ulF2 * 0x1a);
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] =  Freqbuff % 0x100;
	//Freqbuff /= 0x100;
	FreqArray[5] = Freqbuff / 0x100; 
    #endif
	
    //80M
    #ifdef _Freq_80M_
	uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x0A, count = 6;

    Freqbuff = 	ulF2 * 0xe5;      //以80M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  ulF2 * 0xaf;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  ulF2 * 0x35;
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] = Freqbuff % 0x100;
	//Freqbuff /= 0x100;

	FreqArray[5] = Freqbuff / 0x100;
	//Freqbuff /= 0x100; 
    #endif
    
    #ifdef _Freq_131M_
	uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x0A, count = 6;

    Freqbuff = 	ulF2 * 0x9b;           //以32.7*4M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  ulF2 * 0xc4;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  ulF2 * 0x20;
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] = Freqbuff % 0x100;
	//Freqbuff /= 0x100;

	FreqArray[5] = Freqbuff / 0x100;
	//Freqbuff /= 0x100;
    #endif

	//120M
    #ifdef _Freq_120M_
	 uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x0A, count = 6;

	Freqbuff = ulF2 * 0x98;       //以120M为例 取得频率控制字
    FreqArray[0] = Freqbuff % 0x100;   //最小的0x100以内的数据
	Freqbuff /= 0x100; 				   //除于256，高于256的只要256的倍数
   
    Freqbuff +=  (ulF2 * 0xca);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //也可以Freqbuff <<= 8;

	Freqbuff +=  (ulF2 * 0x23);
	FreqArray[2] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[3] = Freqbuff % 0x100;
	Freqbuff /= 0x100;

	FreqArray[4] =  Freqbuff % 0x100;
	//Freqbuff /= 0x100;
	FreqArray[5] = Freqbuff / 0x100;
	#endif

	for (count=6; count; )
	{
	    PWriteAD9854( Add++, FreqArray[--count]);
	}
}
#endif
//*******************************************
//函数名称:void SET_TIME_FSK_AD9854( uint uitime )
//函数功能:设定FSK模式切换频率的时间
//形式参数:uint uitime
//行参说明:无
//返回参数:无        
//使用说明:使用AD9854必须要初始化
//*******************************************
#ifdef UNRAMPED_FSK
void SET_TIME_FSK_AD9854( uint uitime )
{
     uchar tmp;
	 tmp = 250;
	 
	 FDATA_AD9854 = 0;   //选F1频率
     while (--uitime)
	     while (--tmp);
	 
	 FDATA_AD9854 = 1;   //选F2频率
	 while (--uitime)
	     while (--tmp);
}
#endif
//********************************************
//***********Ramp FSK模式*********************
//********************************************
//*******************************************
//函数名称:void RFSK_InitialAD9854(void)
//函数功能:初始化AD9854,Ramp FSK模式
//形式参数:无
//行参说明:无
//返回参数:无        
//使用说明:使用AD9854必须要初始化
//         要设置F1,F2
//*******************************************
#ifdef RAMPED_FSK
void RFSK_InitialAD9854(void)
{
    IO_UDClck_AD9854 = 0;//更新时钟	上升沿更新
	RD_AD9854 = 1;       //先禁止读写
	WR_AD9854 = 1;
    
	Reset_AD9854 = 1;	 //复位	高复位
	Reset_AD9854 = 0;    //     低正常 
	              
    PWriteAD9854( 0x1d, 0x10 );   //关闭比较器
	PWriteAD9854( 0x1e, 0x04 );	  //设置系统时钟倍频为四倍频
	PWriteAD9854( 0x1f, 0x04 );	  //外部更新时钟,模式2       三角扫频写0x24
	PWriteAD9854( 0x20, 0x60 );	  //
	IO_UDClck_AD9854 = 1;         //更新时钟	上升沿更新
	IO_UDClck_AD9854 = 0;
} 
#endif
//*******************************************
//函数名称:void SetRampRate(ulong ulRRC)
//函数功能:设置每个频段停留的时间
//形式参数:ulong ulRRC
//行参说明:20位的数据  时间=(ulRRC + 1)*系统时钟周期
//返回参数:无        
//使用说明:
//*******************************************
#ifdef RAMPED_FSK
void SetRampRate(ulong ulRRC)
{
    uchar DataBuff[3]={0};
    DataBuff[0] = 0x00ff & ulRRC;
    ulRRC >>= 8;
    DataBuff[1] = 0x00ff & ulRRC;
    ulRRC >>= 8;
    DataBuff[2] = 0x00ff & ulRRC;
    PWriteAD9854( 0x1c, DataBuff[0] ); 
	PWriteAD9854( 0x1b, DataBuff[1] ); 
	PWriteAD9854( 0x1a, DataBuff[2] ); 
}
#endif
//********************************************
//               主函数
//********************************************
void main(void)
{    
     //(模式0的完整示例)
     //***************************************
	 #ifdef SINGLESTONE
     InitialAD9854();		  //初始化
	 PWriteAD9854Freq(1000);  //一千赫兹
	 PWriteAD9854AmplChanI(4095);   //振幅3v I通道
	 PWriteAD9854AmplChanQ(4095);   //振幅3v Q通道   492mv---注意这是AD9854凌叶强那块输出的最大峰值
	 //PSet_mv_AD9854ChanI( 125 );      //量化振幅

	 //以下两句很重要，必须有
	 IO_UDClck_AD9854 = 1;			   //上升沿更新
	 IO_UDClck_AD9854 = 0;			   // 
	 #endif
     //以上为示例函数(模式0的完整示例)
	 //***************************************
     
	 //(模式1的示例)
	 //***************************************
	 #ifdef UNRAMPED_FSK
     FSK_InitialAD9854();
	 
	 SET_F1_FSK_AD9854 (1000 );         //F1
	 
	 SET_F2_FSK_AD9854 (10000 );       //F2
	 PSet_mv_AD9854ChanI( 200 );       //量化振幅
	 PSet_mv_AD9854ChanQ( 200 );
     IO_UDClck_AD9854 = 1;			   //上升沿更新
	 IO_UDClck_AD9854 = 0;
	 #endif
	 //***************************************
	 while(1)
	 {   
	     //(模式1的示例)
	     #ifdef UNRAMPED_FSK
	     SET_TIME_FSK_AD9854(2);
		 #endif
	     
	     ;
	 }
}

