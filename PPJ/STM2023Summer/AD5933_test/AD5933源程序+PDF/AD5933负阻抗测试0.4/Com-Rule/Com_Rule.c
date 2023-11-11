#include "Com_Rule.h"
#include "hw_config.h"


#define Data_Begin 			0xfe
#define Data_agreement 	0x0001
#define Data_KEEP 			0x0000
#define Data_device 			0x0001
#define Data_CMD 				0x01
#define Data_Dat 				0x02
#define Data_END_LENG 				3


#define ERROR_agreement 				3
#define ERROR_keep 				3
#define ERROR_device 				3
#define ERROR_UpDown 				3
#define ERROR_check 				3




#define Data_UPLOAD 				0x0F
#define Data_DOWNLOAD 			0xF0

extern u8 DDS_model;
u8 DDS_ASK[]={0xff,0xf0,0x01,0x0f,0xff};
u8 Com_Buf[30];
u8 *Com_dat;
u8 Command;
u8	Get_Msg_mark=ERROR;
u32 frequence[4];

u8 Data_END[]={0xf1,0x1f,0xf2};
u8 First_Data=SUCCESS;
/**********************************************************
* 函数功能 ---> 判断接收起始标志
* 入口参数 ---> dat：第一次接收到的数据
* 返回数值 ---> SUCCESS：成功判断起始标志
								ERROR：不是起始标志
* 功能说明 ---> none
**********************************************************/
u8 If_Receive_Begin(u8 dat)
{
	if(dat==Data_Begin) return SUCCESS;
	return ERROR;
}
/**********************************************************
* 函数功能 ---> 判断协议类型
* 入口参数 ---> agr：协议类型
* 返回数值 ---> SUCCESS：协议正常
								ERROR：非本协议
* 功能说明 ---> none
**********************************************************/
u8 If_agreement_right(u8 *agr)
{
	if((((u16)agr[0]<<8)+agr[1])==Data_agreement)return SUCCESS;
	return ERROR;
}
/**********************************************************
* 函数功能 ---> 保留
* 入口参数 ---> dat：保留
* 返回数值 ---> SUCCESS：保留
								ERROR：保留
* 功能说明 ---> none
**********************************************************/
u8 If_keep_right(u8 *dat)
{
	if((((u16)dat[2]<<8)+dat[3])==Data_KEEP)return SUCCESS;
	return ERROR;
}
/**********************************************************
* 函数功能 ---> 判断设备型号
* 入口参数 ---> dat：设备型号
* 返回数值 ---> SUCCESS：型号正确
								ERROR：型号错误
* 功能说明 ---> none
**********************************************************/
u8 If_device_description(u8 *dat)
{
	if((((u16)dat[4]<<8)+dat[5])==Data_device)return SUCCESS;
	return ERROR;
}
/**********************************************************
* 函数功能 ---> 判断数据方向
* 入口参数 ---> *mode：接收到的数组
* 返回数值 ---> Data_UPLOAD：上传
								Data_DOWNLOAD：下载
								ERROR：通信错误
* 功能说明 ---> none
**********************************************************/
u8 If_UpDown_Load(u8 *mode)
{
	if(mode[6]==Data_UPLOAD)return ERROR;
	else if(mode[6]==Data_DOWNLOAD)return SUCCESS;
//	return ERROR;
}
/**********************************************************
* 函数功能 ---> 判断数据命令
* 入口参数 ---> *type：接收到的数组
* 返回数值 ---> Data_CMD：命令
								Data_Dat：数据
								ERROR：通信错误
* 功能说明 ---> none
**********************************************************/
u8 Data_type(u8 *type)
{
//	switch(type[7])
//	{
//		case Data_CMD:return Data_CMD;
//		case Data_Dat:return Data_Dat;
//		default: return ERROR;
//	}
	return type[7];
}
/**********************************************************
* 函数功能 ---> 判断命令
* 入口参数 ---> *type：接收到的数组
* 返回数值 --->接收到的命令
* 功能说明 ---> none
**********************************************************/
u8 Get_Data_CMD(u8 *dat)
{
	return dat[7];
}
u8 Get_Data_Func(u8 *dat)
{
	return dat[8];
}
/**********************************************************
* 函数功能 ---> 得到数据串
* 入口参数 ---> *dat：接收到的数组
* 返回数值 --->	*Com_dat 数据起始地址
* 功能说明 ---> none
**********************************************************/
u8 Get_Data_dat(u8 *dat)
{
	Com_dat=dat+9;
	return SUCCESS;
}
/**********************************************************
* 函数功能 ---> 检验校验位
* 入口参数 ---> *dat：接收到的数组 
								leng：数组长度
* 返回数值 --->	SUCCESS：校验成功
* 功能说明 ---> none
**********************************************************/
u8 Data_check(u8 *dat,u8 leng)
{
	u8 i,check=0;
	
	for(i=0;i<leng;i++)check+=dat[i];
	if(check==dat[leng])return SUCCESS;
	return ERROR;
}
/**********************************************************
* 函数功能 ---> 接受结束判断
* 入口参数 ---> dat：接收到的数据
* 返回数值 --->	SUCCESS：数据结束
* 功能说明 ---> none
**********************************************************/
u8 If_Receive_Over(u8 dat)
{
	static u8 i=0;
	
	if(dat==Data_END[i])i++;
	if(i>=Data_END_LENG){i=0;return SUCCESS;}
	return ERROR;
}
/**********************************************************
* 函数功能 ---> 接收数组
* 入口参数 ---> dat：接收到的数据
* 返回数值 --->	i-4：数据长度
							ERROR：没有数据
* 功能说明 ---> none
**********************************************************/
u8 Get_Receive_Data(u8 dat)
{
	static u8 i;
	u8 leng;
	
	if(If_Receive_Begin(dat)&&First_Data){First_Data=ERROR;return ERROR;}
	if(First_Data==ERROR)
	{
		Com_Buf[i++]=dat;
		if(i>30)
		{
			First_Data=SUCCESS;
			i=0;
		}
		if(If_Receive_Over(dat)==SUCCESS)
		{
			First_Data=SUCCESS;
			leng=i-4;
			i=0;
			return leng;
		}
	}
	return ERROR;
}
void Return_ASK(void)
{
	USB_Send_String(DDS_ASK,5);
}
/**********************************************************
* 函数功能 ---> 判断接收数据是否正常
* 入口参数 ---> leng：接收到的数据长度
* 返回数值 --->	SUCCESS：数据正常
* 功能说明 ---> none
**********************************************************/
u8 If_Data_Right(u8 leng)
{
	if(If_agreement_right(Com_Buf)==ERROR)return ERROR_agreement;
	if(If_keep_right(Com_Buf)==ERROR)return ERROR_keep;
	if(If_device_description(Com_Buf)==ERROR)return ERROR_device;
	if(If_UpDown_Load(Com_Buf)==ERROR)return ERROR_UpDown;
	if(Data_check(Com_Buf,leng)==ERROR)return ERROR_check;
	return SUCCESS;
}
u8 Data_Deal(u8 dat)
{
	u8 leng;

	leng=Get_Receive_Data(dat);
	if(leng==ERROR)return ERROR;
	if(If_Data_Right(leng)==SUCCESS)
	{
//		if(Data_type(Com_Buf)==Data_CMD)
		{
			DDS_model=Get_Data_CMD(Com_Buf);
			Command=Get_Data_Func(Com_Buf);
			Get_Data_dat(Com_Buf);
			Get_Msg_mark=1;
			Return_ASK();
			return SUCCESS;
		}
	}
	return ERROR;
}
