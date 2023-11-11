//******************************************************
//Copyright(C)2007,���ֵ��ӿƼ���ѧXXXXXX�Ƽ�Э��
//                    AD9854Driver
//					
//�ļ�����:	AD9854Driver
//�ļ���ʶ:(�ڲ�)(����)
//ժ    Ҫ:
//			1.XXX;
//			2.XXX
//			3.XXX 
//          
//
//��ǰ�汾:1.0
//��    ��:pdaabao
//�������:2007.05.29
//
//ȡ���汾:��
//ԭ �� ��:��
//�������:��
//******************************************************
#include<reg51.h>
#include"AD9854Driver.h"

//*******************************************
//��������:void PWriteAD9854(uchar ucAdd, uchar ucDat)
//��������:AD9854��������д����
//��ʽ����:uchar ucAdd, uchar ucDat
//�в�˵��:д��ĵ�ַ��д�������
//���ز���:��        
//ʹ��˵��:
//*******************************************
void PWriteAD9854(uchar ucAdd, uchar ucDat)
{
    
    AddIO_AD9854 = ucAdd;
    DataIO_AD9854 = ucDat;
	WR_AD9854 = 0;          //��ʼ�����ַ����д����
    WR_AD9854 = 1;          //�����أ��ߵ�ƽд��Ч
    
}
//*******************************************
//��������:uchar PReadAD9854(uchar ucAdd)
//��������:AD9854�������ж�����
//��ʽ����:uchar ucAdd
//�в�˵��:�����ݵĵ�ַ
//���ز���:���ظõ�ַ������        
//ʹ��˵��:
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
//��������:void PWriteAD9854Freq(ulong ulFreqOut)
//��������:����д��AD9854��Ƶ��
//��ʽ����:uchar ucAdd
//�в�˵��:д���ĸ���λ�Ĵ�������word 1, ���õ�Ƶ��ֵ
//���ز���:��        
//ʹ��˵��:
//*******************************************
void PWriteAD9854Freq(ulong ulFreqOut)
{
    //FTW = ulFreqOut * 2^48/��Ƶ���ʱ��			//��Ƶ���ʱ��
    //FTW = ulFreqOut * 7036874.41770;	 0x6b5fca   //40M�ڲ�ϵͳʱ��
	//FTW = ulFreqOut * 14073748.8355;	 0xd6bf94	//20M�ڲ�ϵͳʱ��
	//FTW = ulFreqOut * 3518437.12088;	 0x35afe5	//80M�ڲ�ϵͳʱ��
	//FTW = ulFreqOut * 2814749.76710;	 0x2af2cb	//100M�ڲ�ϵͳʱ��
	//FTW = ulFreqOut * 2345624.80592;   0x23ca98   //120M�ڲ�ϵͳʱ��
	//FTW = ulFreqOut * 2147483.648;     0x20c49b   //32.768*4M
	//FTW = ulFreqOut * 1759218.06444;	 0x1ad7f2	//160M�ڲ�ϵͳʱ��
	#ifdef _Freq_160M_
    uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

	Freqbuff = ulFreqOut * 0xf2;       //��160MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  (ulFreqOut * 0xd7);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

    Freqbuff = 	ulFreqOut * 0xe5;      //��80MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  ulFreqOut * 0xaf;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

    Freqbuff = 	ulFreqOut * 0x9b;      //��32.7*4MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  ulFreqOut * 0xc4;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

	Freqbuff = ulFreqOut * 0x98;       //��120MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  (ulFreqOut * 0xca);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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
//��������:void PWriteAD9854Phase(uint uiPhVal)
//��������:��������AD9854�ĳ�ʼ��λ
//��ʽ����:uint uiPhVal 
//�в�˵��:���õĳ�ʼ��λ	uiPhValΪ0~16383
//���ز���:��        
//ʹ��˵��:
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
//��������:void PWriteAD9854AmplChanI(ulong ulAmpl)
//��������:����д��AD9854��Iͨ�������
//��ʽ����:ulong ulAmpl 
//�в�˵��:���õ����ֵ	ulAmplΪ0~4096
//���ز���:��        
//ʹ��˵��:
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
//��������:void PWriteAD9854AmplChanQ(ulong ulAmpl)
//��������:����д��AD9854��Qͨ�������
//��ʽ����:ulong ulAmpl 
//�в�˵��:���õ����ֵ
//���ز���:��        
//ʹ��˵��:
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
//��������:void PSet_mv_AD9854ChanI(ulong ulAmpl)
//��������:��������AD9854��Iͨ���ĵ�ѹֵ
//��ʽ����:uint ulAmpl,�����趨�������ѹ��ֵ������һ���������迹100 
//�в�˵��:���õ����ֵ	ulAmplΪ0~492mv
//���ز���:��        
//ʹ��˵��:
//*******************************************
void PSet_mv_AD9854ChanI(uint ucAmpl)
{
      uint Vtmp;
      Vtmp = (ulong)(ucAmpl)*8325/1000;     //ÿ������Ӧ��������Ϊ8.32317
      PWriteAD9854AmplChanI( Vtmp );
}
//*******************************************
//��������:void PSet_mv_AD9854ChanQ(ulong ulAmpl)
//��������:��������AD9854��Qͨ���ĵ�ѹֵ
//��ʽ����:uint ulAmpl 
//�в�˵��:���õ����ֵ	ulAmplΪ0~492mv               //ulAmplΪ0~4920
//���ز���:��        
//ʹ��˵��:
//*******************************************
void PSet_mv_AD9854ChanQ(uint ucAmpl)
{
      uint Vtmp;
      Vtmp = (ulong)(ucAmpl)*8325/1000;     //ÿ������Ӧ��������Ϊ8.32317-----8.325203
	  //Vtmp = (ulong)(ucAmpl)*8324/10000;           //ÿ������Ӧ��������Ϊ8.32317-----8.325203  
      PWriteAD9854AmplChanQ( Vtmp );
}

//*******************************************
//��������:void InitialAD9854(void)
//��������:��ʼ��AD9854
//��ʽ����:��
//�в�˵��:��
//���ز���:��        
//ʹ��˵��:ʹ��AD9854����Ҫ��ʼ��
//*******************************************
#ifdef SINGLESTONE
void InitialAD9854(void)
{
    IO_UDClck_AD9854 = 0;//����ʱ��	�����ظ���
	RD_AD9854 = 1;       //�Ƚ�ֹ��д
	WR_AD9854 = 1;
    
	Reset_AD9854 = 1;	 //��λ	�߸�λ
	Reset_AD9854 = 0;    //     ������ 
	              
    PWriteAD9854( 0x1d, 0x10 );   //�رձȽ���
	PWriteAD9854( 0x1e, 0x04 );	  //����ϵͳʱ�ӱ�ƵΪ�ı�Ƶ
	PWriteAD9854( 0x1f, 0x00 );	  //�ⲿ����ʱ��,ģʽ0
	PWriteAD9854( 0x20, 0x60 );	  //
	IO_UDClck_AD9854 = 1;         //����ʱ��	�����ظ���
	IO_UDClck_AD9854 = 0;
}
#endif
//********************************************
//*************����ΪFSKģʽ******************
//*******************************************
//��������:void FSK_InitialAD9854(void)
//��������:��ʼ��AD9854,FSKģʽ
//��ʽ����:��
//�в�˵��:��
//���ز���:��        
//ʹ��˵��:ʹ��AD9854����Ҫ��ʼ��
//         ����Ƶ��Ӧ��1K����
//         ���Ƶ��8~10K
//         ��СƵ��0~2K
//*******************************************
#ifdef UNRAMPED_FSK
void FSK_InitialAD9854(void)
{
    IO_UDClck_AD9854 = 0;//����ʱ��	�����ظ���
	RD_AD9854 = 1;       //�Ƚ�ֹ��д
	WR_AD9854 = 1;
    
	Reset_AD9854 = 1;	 //��λ	�߸�λ
	Reset_AD9854 = 0;    //     ������ 
	              
    PWriteAD9854( 0x1d, 0x10 );   //�رձȽ���
	PWriteAD9854( 0x1e, 0x04 );	  //����ϵͳʱ�ӱ�ƵΪ�ı�Ƶ
	PWriteAD9854( 0x1f, 0x02 );	  //�ⲿ����ʱ��,ģʽ1
	PWriteAD9854( 0x20, 0x60 );	  //
	IO_UDClck_AD9854 = 1;         //����ʱ��	�����ظ���
	IO_UDClck_AD9854 = 0;
}
#endif
//*******************************************
//��������:void SET_F1_FSK_AD9854( ulong ulF1)
//��������:�趨FSKģʽF1��Ƶ��
//��ʽ����:ulong ulF1
//�в�˵��:Ƶ��1��ֵ
//���ز���:��        
//ʹ��˵��:ʹ��AD9854����Ҫ��ʼ��
//*******************************************
#if (UNRAMPED_FSK | RAMPED_FSK)
void SET_F1_FSK_AD9854( ulong ulF1)
{   
	#ifdef _Freq_160M_
    uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x04, count = 6;

	Freqbuff = ulF1 * 0xf2;       //��160MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  (ulF1 * 0xd7);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

    Freqbuff = 	ulF1 * 0xe5;      //��80MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  ulF1 * 0xaf;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

    Freqbuff = 	ulF1 * 0x9b;      //��32.7*4MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  ulF1 * 0xc4;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

	Freqbuff = ulF1 * 0x98;       //��120MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  (ulF1 * 0xca);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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
//��������:void SET_F2_FSK_AD9854( ulong ulF2)
//��������:�趨FSKģʽF2��Ƶ��
//��ʽ����:ulong ulF2
//�в�˵��:Ƶ��2��ֵ
//���ز���:��        
//ʹ��˵��:ʹ��AD9854����Ҫ��ʼ��
//*******************************************
#if (UNRAMPED_FSK | RAMPED_FSK)
void SET_F2_FSK_AD9854( ulong ulF2 )
{
    //FDATA_AD9854 = 0;
	#ifdef _Freq_160M_
    uchar FreqArray[6];
	ulong Freqbuff;
	uchar Add = 0x0A, count = 6;			 

	Freqbuff = ulF2 * 0xf2;       //��160MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100 (256)���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  (ulF2 * 0xd7);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

    Freqbuff = 	ulF2 * 0xe5;      //��80MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  ulF2 * 0xaf;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

    Freqbuff = 	ulF2 * 0x9b;           //��32.7*4MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  ulF2 * 0xc4;
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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

	Freqbuff = ulF2 * 0x98;       //��120MΪ�� ȡ��Ƶ�ʿ�����
    FreqArray[0] = Freqbuff % 0x100;   //��С��0x100���ڵ�����
	Freqbuff /= 0x100; 				   //����256������256��ֻҪ256�ı���
   
    Freqbuff +=  (ulF2 * 0xca);
	FreqArray[1] = Freqbuff % 0x100;
	Freqbuff /= 0x100;		           //Ҳ����Freqbuff <<= 8;

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
//��������:void SET_TIME_FSK_AD9854( uint uitime )
//��������:�趨FSKģʽ�л�Ƶ�ʵ�ʱ��
//��ʽ����:uint uitime
//�в�˵��:��
//���ز���:��        
//ʹ��˵��:ʹ��AD9854����Ҫ��ʼ��
//*******************************************
#ifdef UNRAMPED_FSK
void SET_TIME_FSK_AD9854( uint uitime )
{
     uchar tmp;
	 tmp = 250;
	 
	 FDATA_AD9854 = 0;   //ѡF1Ƶ��
     while (--uitime)
	     while (--tmp);
	 
	 FDATA_AD9854 = 1;   //ѡF2Ƶ��
	 while (--uitime)
	     while (--tmp);
}
#endif
//********************************************
//***********Ramp FSKģʽ*********************
//********************************************
//*******************************************
//��������:void RFSK_InitialAD9854(void)
//��������:��ʼ��AD9854,Ramp FSKģʽ
//��ʽ����:��
//�в�˵��:��
//���ز���:��        
//ʹ��˵��:ʹ��AD9854����Ҫ��ʼ��
//         Ҫ����F1,F2
//*******************************************
#ifdef RAMPED_FSK
void RFSK_InitialAD9854(void)
{
    IO_UDClck_AD9854 = 0;//����ʱ��	�����ظ���
	RD_AD9854 = 1;       //�Ƚ�ֹ��д
	WR_AD9854 = 1;
    
	Reset_AD9854 = 1;	 //��λ	�߸�λ
	Reset_AD9854 = 0;    //     ������ 
	              
    PWriteAD9854( 0x1d, 0x10 );   //�رձȽ���
	PWriteAD9854( 0x1e, 0x04 );	  //����ϵͳʱ�ӱ�ƵΪ�ı�Ƶ
	PWriteAD9854( 0x1f, 0x04 );	  //�ⲿ����ʱ��,ģʽ2       ����ɨƵд0x24
	PWriteAD9854( 0x20, 0x60 );	  //
	IO_UDClck_AD9854 = 1;         //����ʱ��	�����ظ���
	IO_UDClck_AD9854 = 0;
} 
#endif
//*******************************************
//��������:void SetRampRate(ulong ulRRC)
//��������:����ÿ��Ƶ��ͣ����ʱ��
//��ʽ����:ulong ulRRC
//�в�˵��:20λ������  ʱ��=(ulRRC + 1)*ϵͳʱ������
//���ز���:��        
//ʹ��˵��:
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
//               ������
//********************************************
void main(void)
{    
     //(ģʽ0������ʾ��)
     //***************************************
	 #ifdef SINGLESTONE
     InitialAD9854();		  //��ʼ��
	 PWriteAD9854Freq(1000);  //һǧ����
	 PWriteAD9854AmplChanI(4095);   //���3v Iͨ��
	 PWriteAD9854AmplChanQ(4095);   //���3v Qͨ��   492mv---ע������AD9854��Ҷǿ�ǿ����������ֵ
	 //PSet_mv_AD9854ChanI( 125 );      //�������

	 //�����������Ҫ��������
	 IO_UDClck_AD9854 = 1;			   //�����ظ���
	 IO_UDClck_AD9854 = 0;			   // 
	 #endif
     //����Ϊʾ������(ģʽ0������ʾ��)
	 //***************************************
     
	 //(ģʽ1��ʾ��)
	 //***************************************
	 #ifdef UNRAMPED_FSK
     FSK_InitialAD9854();
	 
	 SET_F1_FSK_AD9854 (1000 );         //F1
	 
	 SET_F2_FSK_AD9854 (10000 );       //F2
	 PSet_mv_AD9854ChanI( 200 );       //�������
	 PSet_mv_AD9854ChanQ( 200 );
     IO_UDClck_AD9854 = 1;			   //�����ظ���
	 IO_UDClck_AD9854 = 0;
	 #endif
	 //***************************************
	 while(1)
	 {   
	     //(ģʽ1��ʾ��)
	     #ifdef UNRAMPED_FSK
	     SET_TIME_FSK_AD9854(2);
		 #endif
	     
	     ;
	 }
}

