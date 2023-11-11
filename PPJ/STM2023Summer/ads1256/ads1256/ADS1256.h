#ifndef __ADS1256_H_
#define	__ADS1256_H_

#include "main.h"
/*端口定义----需要编辑*/ 
#define AD_CS_Pin GPIO_PIN_8
#define AD_CS_GPIO_Port GPIOD
#define AD_SCLK_Pin GPIO_PIN_10
#define AD_SCLK_GPIO_Port GPIOD
#define AD_DIN_Pin GPIO_PIN_14
#define AD_DIN_GPIO_Port GPIOD
#define AD_DRDY_Pin GPIO_PIN_6
#define AD_DRDY_GPIO_Port GPIOC
#define AD_DOUT_Pin GPIO_PIN_8
#define AD_DOUT_GPIO_Port GPIOC
#define AD_SYNC_Pin GPIO_PIN_8
#define AD_SYNC_GPIO_Port GPIOA


//模拟SPI时钟引脚---输出
#define SCK_H  HAL_GPIO_WritePin(AD_SCLK_GPIO_Port ,AD_SCLK_Pin,1)
#define SCK_L  HAL_GPIO_WritePin(AD_SCLK_GPIO_Port ,AD_SCLK_Pin,0)

//模拟SPI数据输入引脚---输入
#define DOUT HAL_GPIO_ReadPin(AD_DOUT_GPIO_Port,AD_DOUT_Pin)

//模拟SPI数据输出引脚---输出
#define DIN_H  HAL_GPIO_WritePin(AD_DIN_GPIO_Port ,AD_DIN_Pin,1)
#define DIN_L  HAL_GPIO_WritePin(AD_DIN_GPIO_Port ,AD_DIN_Pin,0)

//模拟SPI片选引脚---输出
#define CS_H  HAL_GPIO_WritePin(AD_SYNC_GPIO_Port ,AD_SYNC_Pin,1)
#define CS_L  HAL_GPIO_WritePin(AD_SYNC_GPIO_Port ,AD_SYNC_Pin,0)

//ADS1256状态引脚---输入
#define DRDY	HAL_GPIO_ReadPin(AD_DRDY_GPIO_Port,AD_DRDY_Pin)


//ADS1256控制命令
#define ADS1256_CMD_WAKEUP   0x00 //启动
#define ADS1256_CMD_RDATA    0x01 //读数据
#define ADS1256_CMD_RDATAC   0x03 
#define ADS1256_CMD_SDATAC   0x0f 
#define ADS1256_CMD_RREG     0x10 //读寄存器
#define ADS1256_CMD_WREG     0x50 //写寄存器
#define ADS1256_CMD_SELFCAL  0xf0 //自动校准
#define ADS1256_CMD_SELFOCAL 0xf1 
#define ADS1256_CMD_SELFGCAL 0xf2 
#define ADS1256_CMD_SYSOCAL  0xf3 
#define ADS1256_CMD_SYSGCAL  0xf4 
#define ADS1256_CMD_SYNC     0xfc //片选
#define ADS1256_CMD_STANDBY  0xfd //待机
#define ADS1256_CMD_REST     0xfe //复位
 
// ADS1256寄存器地址表
#define ADS1256_STATUS       0x00   
#define ADS1256_MUX          0x01   
#define ADS1256_ADCON        0x02   
#define ADS1256_DRATE        0x03   
#define ADS1256_IO           0x04   
#define ADS1256_OFC0         0x05   
#define ADS1256_OFC1         0x06   
#define ADS1256_OFC2         0x07   
#define ADS1256_FSC0         0x08   
#define ADS1256_FSC1         0x09   
#define ADS1256_FSC2         0x0A 
 
 
// ADS1256正输入采样通道前四位
#define ADS1256_MUXP_AIN0   0x00 
#define ADS1256_MUXP_AIN1   0x10 
#define ADS1256_MUXP_AIN2   0x20 
#define ADS1256_MUXP_AIN3   0x30 
#define ADS1256_MUXP_AIN4   0x40 
#define ADS1256_MUXP_AIN5   0x50 
#define ADS1256_MUXP_AIN6   0x60 
#define ADS1256_MUXP_AIN7   0x70 
#define ADS1256_MUXP_AINCOM 0x80 

// ADS1256负输入采样通道后四位
#define ADS1256_MUXN_AIN0   0x00 
#define ADS1256_MUXN_AIN1   0x01 
#define ADS1256_MUXN_AIN2   0x02 
#define ADS1256_MUXN_AIN3   0x03 
#define ADS1256_MUXN_AIN4   0x04 
#define ADS1256_MUXN_AIN5   0x05 
#define ADS1256_MUXN_AIN6   0x06 
#define ADS1256_MUXN_AIN7   0x07 
#define ADS1256_MUXN_AINCOM 0x08   
 
 
//ADS1256增益设置
#define ADS1256_GAIN_1      0x00 //1倍
#define ADS1256_GAIN_2      0x01 //2倍
#define ADS1256_GAIN_4      0x02 //4倍
#define ADS1256_GAIN_8      0x03 //8倍
#define ADS1256_GAIN_16     0x04 //16倍
#define ADS1256_GAIN_32     0x05 //32倍
#define ADS1256_GAIN_64     0x06 //64倍

 
//ADS1256采样速率
#define ADS1256_DRATE_30000SPS  0xF0 
#define ADS1256_DRATE_15000SPS  0xE0 
#define ADS1256_DRATE_7500SPS   0xD0 
#define ADS1256_DRATE_3750SPS   0xC0 
#define ADS1256_DRATE_2000SPS   0xB0 
#define ADS1256_DRATE_1000SPS   0xA1 
#define ADS1256_DRATE_500SPS    0x92 
#define ADS1256_DRATE_100SPS    0x82 
#define ADS1256_DRATE_60SPS     0x72 
#define ADS1256_DRATE_50SPS     0x63 
#define ADS1256_DRATE_30SPS     0x53 
#define ADS1256_DRATE_25SPS     0x43 
#define ADS1256_DRATE_15SPS     0x33 
#define ADS1256_DRATE_10SPS     0x23 
#define ADS1256_DRATE_5SPS      0x13 
#define ADS1256_DRATE_2_5SPS    0x03


/*函数定义*/ 
void ADS1256_Write_8Bits(uint8_t Data);//模拟SPI写数据
uint8_t ADS1256_Read_8Bits(void);//模拟SPI读数据
void ADS1256WREG(uint8_t regaddr,uint8_t databyte);//写寄存器
void ADS1256_Init(uint8_t GAIN,uint8_t RATE); //初始化ADS1256
uint32_t ADS1256ReadData(uint8_t AINP,uint8_t AINN);//单次读24位原始数据
double ADS1256GetVolt(uint8_t AINP_,uint8_t AINN_,int GAIN);//单次读24位电压数据

#endif



