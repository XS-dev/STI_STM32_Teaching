#ifndef _AD9959_H_
#define _AD9959_H_
#include "main.h"

#define kHz 1000*0.9987013790118112670830499041494

#define CSR_ADD   0x00   //CSR 
#define FR1_ADD   0x01   //FR1 
#define FR2_ADD   0x02   //FR2 
#define CFR_ADD   0x03   //CFR 
#define CFTW0_ADD 0x04   //CTW0
#define CPOW0_ADD 0x05   //CPW0
#define ACR_ADD   0x06   //ACR 
#define LSRR_ADD  0x07   //LSR 
#define RDW_ADD   0x08   //RDW 
#define FDW_ADD   0x09   //FDW 


#define Mhz 1000000
#define step500K 500000


//#define AD9959_P0_Pin GPIO_PIN_0
//#define AD9959_P0_GPIO_Port GPIOD
//#define AD9959_P1_Pin GPIO_PIN_1
//#define AD9959_P1_GPIO_Port GPIOD
//#define AD9959_P2_Pin GPIO_PIN_2
//#define AD9959_P2_GPIO_Port GPIOD
//#define AD9959_P3_Pin GPIO_PIN_3
//#define AD9959_P3_GPIO_Port GPIOD
//#define AD9959_SD0_Pin GPIO_PIN_4
//#define AD9959_SD0_GPIO_Port GPIOD
//#define AD9959_SD1_Pin GPIO_PIN_5
//#define AD9959_SD1_GPIO_Port GPIOD
//#define AD9959_SD2_Pin GPIO_PIN_6
//#define AD9959_SD2_GPIO_Port GPIOD
//#define AD9959_SD3_Pin GPIO_PIN_7
//#define AD9959_SD3_GPIO_Port GPIOD
//#define AD9959_SCK_Pin GPIO_PIN_3
//#define AD9959_SCK_GPIO_Port GPIOB
//#define AD9959_CS_Pin GPIO_PIN_4
//#define AD9959_CS_GPIO_Port GPIOB
//#define AD9959_UP_Pin GPIO_PIN_5
//#define AD9959_UP_GPIO_Port GPIOB
//#define AD9959_RST_Pin GPIO_PIN_6
//#define AD9959_RST_GPIO_Port GPIOB
//#define AD9959_PWR_Pin GPIO_PIN_7
//#define AD9959_PWR_GPIO_Port GPIOB


//AD9959?????
//#define AD9959_PWR	PBout(12)
//#define Reset				PBout(10)
//#define UPDATE			PEout(14)
//#define CS					PEout(12)
//#define SCLK				PEout(10)
//#define SDIO3				PEout(8)

//#define SDIO2				PBout(13)
//#define SDIO1				PBout(11)
//#define SDIO0				PEout(15)
//#define PS3					PEout(13)
//#define PS2					PEout(11)
//#define PS1					PEout(9)
//#define PS0					PEout(7)
#define AD9959_Amv 	1.8907
#define AD9959_Khz 	1000


void delay1 (uint32_t length);
void IntReset(void);	 
void IO_Update(void);  
void Intserve(void);		
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp);
void Init_AD9959(void);
void Write_frequence(uint8_t Channel,uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampli);
void Write_Phase(uint8_t Channel,uint16_t Phase);



#endif
