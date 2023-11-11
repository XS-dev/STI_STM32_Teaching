#include "AD9959.H"

uint8_t CSR_DATA0[1] = {0x10};     // �� CH0
uint8_t CSR_DATA1[1] = {0x20};      // �� CH1
uint8_t CSR_DATA2[1] = {0x40};      // �� CH2
uint8_t CSR_DATA3[1] = {0x80};      // �� CH3		
																	
 
uint8_t 	FR2_DATA[2] = {0x20,0x00};//default Value = 0x0000
uint8_t 	CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302	   
																	
uint8_t 	CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360
			


uint32_t SinFre[4] = {1000000, 1000000, 1000000, 1000000};
uint32_t SinAmp[4] = {1023, 1023, 1023, 1023};
uint32_t SinPhr[4] = {0, 4095, 4095*3, 4095*2};
//ɨƵ����
uint32_t SweepMinFre = 1000;
uint32_t SweepMaxFre = 10000;
uint32_t SweepStepFre = 100;
uint16_t SweepTime = 1;//ms
uint8_t SweepFlag = 0;



uint8_t 	FR1_DATA[3] = {0xD0,0x00,0x00};//20��Ƶ Charge pump control = 75uA FR1<23> -- VCO gain control =0ʱ system clock below 160 MHz;
uint8_t 	LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
																	
uint8_t 	RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
																	
uint8_t 	FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

//AD9959��ʼ��
void Init_AD9959(void)  
{ 		
	Intserve();  //IO�ڳ�ʼ��
	IntReset();  //AD9959��λ  
	
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//д���ܼĴ���1
	WriteData_AD9959(FR2_ADD,2,FR2_DATA,1);
	//д���ʼƵ��
	Write_frequence(3,SinFre[3]);
	Write_frequence(0,SinFre[0]); 
	Write_frequence(1,SinFre[1]);
	Write_frequence(2,SinFre[2]);

	Write_Phase(3, SinPhr[3]);
	Write_Phase(0, SinPhr[0]);
	Write_Phase(1, SinPhr[1]);
	Write_Phase(2, SinPhr[2]);
	
	Write_Amplitude(3, SinAmp[3]);
	Write_Amplitude(0, SinAmp[0]);
	Write_Amplitude(1, SinAmp[1]);
	Write_Amplitude(2, SinAmp[2]);
} 
//��ʱ
void delay1 (uint32_t length)
{
//	length = length*12;
//	while(length--);
	Delay_Us(length);
}
//IO�ڳ�ʼ��
void Intserve(void)		   
{   
	AD9959_PWR_L;
    CS_H;
    SCLK_L;
    UPDATE_L;
    PS0_L;
//    PS1_L;
//    PS2_L;
//    PS3_L;
    SDIO0_L;
    SDIO1_L;
//    SDIO2_L;
//    SDIO3_L;
}
//AD9959��λ
void IntReset(void)	  
{
	Reset_L;
	delay1(1);
	Reset_H;
	delay1(30);
	Reset_L;
}
 //AD9959��������
void IO_Update(void)  
{
	UPDATE_L;
	delay1(2);
	UPDATE_H;
	delay1(4);
	UPDATE_L;
}
/*--------------------------------------------
�������ܣ�������ͨ��SPI��AD9959д����
RegisterAddress: �Ĵ�����ַ
NumberofRegisters: �����ֽ���
*RegisterData: ������ʼ��ַ
temp: �Ƿ����IO�Ĵ���
----------------------------------------------*/
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp)
{
	uint8_t	ControlValue = 0;
	uint8_t	ValueToWrite = 0;
	uint8_t	RegisterIndex = 0;
	uint8_t	i = 0;

	ControlValue = RegisterAddress;
//д���ַ
	SCLK_L;
                                                                                                                                                             	CS_L;	
	delay1(1);	
	for(i=0; i<8; i++)
	{
		SCLK_L; 
		
		if(0x80 == (ControlValue & 0x80))
		{SDIO0_H;	}  
		else
		{SDIO0_L;	}  
		
		delay1(1);
		
		
		SCLK_H;
		delay1(1);
		
		
		ControlValue <<= 1;
	}
	SCLK_L;
	delay1(10);
	
	//д������
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			SCLK_L;
			if(0x80 == (ValueToWrite & 0x80))
			{
				SDIO0_H;	
			}				
			else
			{
				SDIO0_L;
			}
			
			delay1(1);
			
			SCLK_H;
			delay1(1);
			
			ValueToWrite <<= 1;
		}
		SCLK_L;	
		delay1(5);
	}	
	if(temp != 0)
	IO_Update();	
	CS_H;
	delay1(25);
} 
/*---------------------------------------
�������ܣ�����ͨ�����Ƶ��
Channel:  ���ͨ��
Freq:     ���Ƶ�ʣ���Χ0~200 000 000 Hz
---------------------------------------*/
void Write_frequence(uint8_t Channel,uint32_t Freq)
{	 
	  uint8_t 	CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//�м����
	  
	  uint32_t 	Temp;            
	  Temp=(uint32_t)Freq*8.589934592;	   //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  8.589934592=(2^32)/500000000 ����500M=25M*20(��Ƶ���ɱ��)
	  
	  CFTW0_DATA[3]=(uint8_t)Temp;
	  CFTW0_DATA[2]=(uint8_t)(Temp>>8);
	  CFTW0_DATA[1]=(uint8_t)(Temp>>16);
	  CFTW0_DATA[0]=(uint8_t)(Temp>>24);
	  
	  if(Channel==0)	  
	  {
		  WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ��
		  WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
		}
	  else if(Channel==1)	
	  {
		  WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH1ͨ��
		  WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH1�趨Ƶ��	
	  }
	  else if(Channel==2)	
	  {
		  WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH2ͨ��
	      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH2�趨Ƶ��	
	  }
	  else if(Channel==3)	
	  {
		  WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH3ͨ��
          WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH3�趨Ƶ��	
	  }																																																																										 
	
} 
/*---------------------------------------
�������ܣ�����ͨ���������
Channel:  ���ͨ��
Ampli:    �������,��Χ0~1023������ֵ0~1023��Ӧ�������0~530mV����
---------------------------------------*/
void Write_Amplitude(uint8_t Channel, uint16_t Ampli)
{ 
	uint16_t A_temp;//=0x23ff;
	uint8_t ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	
	A_temp=Ampli|0x1000;
	ACR_DATA[2] = (uint8_t)A_temp;  //��λ����
	ACR_DATA[1] = (uint8_t)(A_temp>>8); //��λ����
	if(Channel==0)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
	else if(Channel==1)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1); 
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}
	else if(Channel==2)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1); 
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
	else if(Channel==3)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1); 
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
}
/*---------------------------------------
�������ܣ�����ͨ�������λ
Channel:  ���ͨ��
Phase:    �����λ,��Χ��0~16383(��Ӧ�Ƕȣ�0��~360��)
---------------------------------------*/
void Write_Phase(uint8_t Channel,uint16_t Phase)
{
	uint16_t P_temp=0;
	P_temp=(uint16_t)Phase;
	CPOW0_DATA[1]=(uint8_t)P_temp;
	CPOW0_DATA[0]=(uint8_t)(P_temp>>8);
	if(Channel==0)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}
	else if(Channel==1)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1); 
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}
	else if(Channel==2)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1); 
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}
	else if(Channel==3)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1); 
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}
}









