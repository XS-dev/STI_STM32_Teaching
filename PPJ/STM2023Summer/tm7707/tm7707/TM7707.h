/*======================================================================*/
/*= TM7707 Driver library.												*/
/*======================================================================*/
#ifndef _TM7707_H_
#define _TM7707_H_
#include "main.h"

#define AD7_CS_Pin GPIO_PIN_2
#define AD7_CS_GPIO_Port GPIOD
#define AD7_DIN_Pin GPIO_PIN_6
#define AD7_DIN_GPIO_Port GPIOD
#define AD7_DRTY_Pin GPIO_PIN_5
#define AD7_DRTY_GPIO_Port GPIOB
#define AD7_RST_Pin GPIO_PIN_7
#define AD7_RST_GPIO_Port GPIOB
#define AD7_DOUT_Pin GPIO_PIN_9
#define AD7_DOUT_GPIO_Port GPIOB
#define AD7_SCLK_Pin GPIO_PIN_1
#define AD7_SCLK_GPIO_Port GPIOE

//ģ��SPIʱ������---���
#define AD7_SCK_H  HAL_GPIO_WritePin(AD7_SCLK_GPIO_Port ,AD7_SCLK_Pin,1)
#define AD7_SCK_L  HAL_GPIO_WritePin(AD7_SCLK_GPIO_Port ,AD7_SCLK_Pin,0)

//ģ��SPI������������---����
#define AD7_DOUT HAL_GPIO_ReadPin(AD7_DOUT_GPIO_Port,AD7_DOUT_Pin)

//ģ��SPI�����������---���
#define AD7_DIN_H  HAL_GPIO_WritePin(AD7_DIN_GPIO_Port ,AD7_DIN_Pin,1)
#define AD7_DIN_L  HAL_GPIO_WritePin(AD7_DIN_GPIO_Port ,AD7_DIN_Pin,0)
//ģ��SPIƬѡ����---���
#define AD7_CS_H  HAL_GPIO_WritePin(AD7_CS_GPIO_Port ,AD7_CS_Pin,1)
#define AD7_CS_L  HAL_GPIO_WritePin(AD7_CS_GPIO_Port ,AD7_CS_Pin,0)
//״̬����---����
#define AD7_DRDY	HAL_GPIO_ReadPin(AD7_DRTY_GPIO_Port,AD7_DRTY_Pin)
//��λ����
#define AD7_RST_H  HAL_GPIO_WritePin(AD7_RST_GPIO_Port ,AD7_RST_Pin,1)
#define AD7_RST_L  HAL_GPIO_WritePin(AD7_RST_GPIO_Port ,AD7_RST_Pin,0)




// Communication register
enum
{
	// Destination register
	REG_COMM		= 0x00,	// Communication register.
	REG_SETUP		= 0x10,	// Setting register.
	REG_CLOCK		= 0x20,	// Clock register.
	REG_DATA		= 0x30,	// Data register.
	REG_ZERO_CH1	= 0x60,	/* ƫ�ƼĴ���	*/
	REG_FULL_CH1	= 0x70,	/* �����̼Ĵ���	*/
	// Register 
	WRITE			= 0x00,	// Write register
	READ			= 0x08,	// Read register
	// Channel index
	CH_1			= 0x00,	/* AIN1+  AIN1-		*/
	CH_2			= 0x01,	/* AIN2+  AIN2-		*/
	CH_3			= 0x02,	/* AIN1-  AIN1-		*/
	CH_4			= 0x03,	/* AIN1-  AIN2-		*/
	CH_MAX			= 0x04,	// Cannot write to device register.
};

// Setting register
enum
{
	MD_NORMAL		= (0 << 6),	/* ����ģʽ		*/
	MD_CAL_SELF		= (1 << 6),	/* ��У׼ģʽ	*/
	MD_CAL_ZERO		= (2 << 6),	/* У׼0�̶�ģʽ	*/
	MD_CAL_FULL		= (3 << 6),	/* У׼���̶�ģʽ*/

	GAIN_1			= (0 << 3),	/* ����			*/
	GAIN_2			= (1 << 3),	/* ����			*/
	GAIN_4			= (2 << 3),	/* ����			*/
	GAIN_8			= (3 << 3),	/* ����			*/
	GAIN_16			= (4 << 3),	/* ����			*/
	GAIN_32			= (5 << 3),	/* ����			*/
	GAIN_64			= (6 << 3),	/* ����			*/
	GAIN_128		= (7 << 3),	/* ����			*/

	/* ����˫���Ի��ǵ����Զ����ı��κ������źŵ�״̬����ֻ�ı�������ݵĴ����ת�������ϵ�У׼�� */
	BIPOLAR			= (0 << 2),	/* ˫�������� */
	UNIPOLAR		= (1 << 2),	/* ���������� */

	BUF_NO			= (0 << 1),	/* �����޻��壨�ڲ�������������) */
	BUF_EN			= (1 << 1),	/* �����л��� (�����ڲ�������) */

	FSYNC_0			= 0,
	FSYNC_1			= 1			/* ������ */
};

// Clock register define.
enum
{
	CLKDIS_0	= 0x00,		/* ʱ�����ʹ�� ������Ӿ���ʱ������ʹ�ܲ����񵴣� */
	CLKDIS_1	= 0x10,		/* ʱ�ӽ�ֹ �����ⲿ�ṩʱ��ʱ�����ø�λ���Խ�ֹMCK_OUT�������ʱ����ʡ�� */

	/*
		2.4576MHz��CLKDIV=0 ����Ϊ 4.9152MHz ��CLKDIV=1 ����CLK Ӧ�� ��0����
		1MHz ��CLKDIV=0 ���� 2MHz   ��CLKDIV=1 ����CLK ��λӦ��  ��1��
	*/
	CLK_4_9152M = 0x08,
	CLK_2_4576M = 0x00,
	CLK_1M 		= 0x04,
	CLK_2M 		= 0x0C,

	FS_50HZ		= 0x00,
	FS_60HZ		= 0x01,
	FS_250HZ	= 0x02,
	FS_500HZ	= 0x04,

	ZERO_0		= 0x00,
	ZERO_1		= 0x80
};



// Function declare
void TM7707_Delay(void);

void TM7707_Write_8Bits(uint8_t Data);
uint8_t TM7707_Read_8Bits(void);
void TM7707_InitializeGPIO(void);

void		TM7707_WaitForDRDY	(void);
uint8_t		TM7707_TransferByte	(uint8_t uiTxData);
void		TM7707_SynchronizeDeviceClock(void);
void		TM7707_SelfCalibration(uint8_t	uiChannelIndex, uint8_t uiGain);
void		TM7707_Initialize	(void);
uint32_t	TM7707_ReadADCValue(uint8_t uiChannelIndex);

#endif
