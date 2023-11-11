//******************************************************
//Copyright(C)2007,���ֵ��ӿƼ���ѧXXXX�Ƽ�Э��
//                     AD9854Driver
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
#ifndef _AD9854DRIVER_H
#define _AD9854DRIVER_H

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long
//�Ƿ��õ�����λ
//#define PHASE_EN

//ѡ��ʹ�õ�ģʽ
#define SINGLESTONE    1      //��Ƶ��ģʽ
//#define UNRAMPED_FSK 1            
//#define RAMPED_FSK   1
//#define CHIRP        1
//#define BPSK         1

//���ݾ����Ƶ��ѡ��
#define _Freq_131M_
//#define _Freq_120M_
//#define _Freq_160M_
//#define _Freq_80M_

//����Ԥ����
#define AddIO_AD9854   P2  //��ַ��
#define DataIO_AD9854  P0  //���ݿ�
//����λ����
sbit RD_AD9854 = P3^4;	   //дʹ�ܣ�����Ч
sbit WR_AD9854 = P3^5;

//��ʱ����
sbit OSK_AD9854 = P3^2;	   //SHAPED KEYING
sbit FDATA_AD9854 = P3^3;  //FSK/BPSK/HOLD

sbit Reset_AD9854 = P3^7;  	   //��λ �߸�λ��������
sbit IO_UDClck_AD9854 = P3^6;  //����ʱ��

//��������
//*********************����Ϊ��Ƶģʽ**********************
//����˵����д���ݵ�AD9854
extern void PWriteAD9854(uchar ucAdd, uchar ucDat);  

//����˵��������Ƶ��ֵ 
extern void PWriteAD9854Freq(ulong ulFreqOut);

//����˵��������Iͨ���ķ���
extern void PWriteAD9854AmplChanI(uint ulAmpl);

//����˵��������Qͨ���ķ���
extern void PWriteAD9854AmplChanQ(uint ulAmpl);

//����˵��������Iͨ���ķ��ȣ�����������Ǻ���
extern void PSet_mv_AD9854ChanI(uint ucAmpl);

//����˵��������Qͨ���ķ��ȣ�����������Ǻ���
extern void PSet_mv_AD9854ChanQ(uint ucAmpl);

//����˵������ʼ��AD9854��ģʽ0
extern void InitialAD9854(void);
//***********************************************************

#endif