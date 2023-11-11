#include "ADS1256.h"

uint32_t CLKtim = 0;

//��ʱ����
void ADS1256_Delay(void)
{
	Delay_Us(10);
}

//-----------------------------------------------------------------//
//	�� �� ��: ADS1256_Write_8Bits
//����˵��: ��SPI���߷���8��bit���ݡ� ����CS���ơ�
//��    ��: _Data : ����
//�� �� ֵ: ��
//-----------------------------------------------------------------//

void ADS1256_Write_8Bits(uint8_t Data)
{
	
	ADS1256_Delay();	
	for(int i = 0; i < 8; i++)
	{
		if (Data & 0x80)
		{
			DIN_H ;
		}
		else
		{
			DIN_L ;
		}
		SCK_H;	
		ADS1256_Delay();
		Data <<= 1;
		SCK_L;    /* <----  ADS1256 ����SCK�½��ز���DIN����,*/
		ADS1256_Delay();				 
	}
} 

//-----------------------------------------------------------------//
//	�� �� ��: ADS1256_Read_8Bits
//	����˵��: ��SPI���߽���8��bit���ݡ� ����CS���ơ�
//	��    ��: ��
//�� �� ֵ: uint8_t����
//-----------------------------------------------------------------//

uint8_t ADS1256_Read_8Bits(void)
{
	uint8_t read = 0;
	ADS1256_Delay();
	for (int i = 0; i < 8; i++)
	{	
		SCK_H ;    /* <----  ADS1256 ����SCK�������������,*/
		ADS1256_Delay();
		read = read<<1;
		SCK_L ;
		
		if (DOUT)
		{
			read++;
		}
		ADS1256_Delay();
	}
	return read;//���ض���������
}

//-----------------------------------------------------------------//
//	�� �� ����ADS1256WREG
//	��    ��: regaddr--�Ĵ�����ַ  databyte--д�������
//	�� �� ֵ: ��
//	��    ��: ��ADS1256�е�ַΪregaddr�ļĴ���д��һ���ֽ�databyte
//-----------------------------------------------------------------//
void ADS1256WREG(uint8_t regaddr,uint8_t databyte)
{

	CS_L ;//Ƭѡ���Ϳ�ʼ
	while(DRDY);//��ADS1256_DRDYΪ��ʱ����д�Ĵ���
	ADS1256_Write_8Bits(ADS1256_CMD_WREG | (regaddr & 0x0F));//��Ĵ���д�����ݵ�ַ������λΪ�������λΪ��ַ
  ADS1256_Write_8Bits(0x00);//д�����ݵĸ���n-1,����д��1�����ݣ�����Ϊ0x00
  ADS1256_Write_8Bits(databyte);//��regaddr��ַָ��ļĴ���д������databyte
	CS_H ;//Ƭѡ���߽���


}

//-----------------------------------------------------------------//
//	�� �� ����ADS1256_Init
//	��    ��: GAIN--�ɱ�����汶��  RATE--�����ٶ�
//	�� �� ֵ: ��
//	��    ��: ��ʼ��ADS1256
//-----------------------------------------------------------------//
void ADS1256_Init(uint8_t GAIN,uint8_t RATE)//��ʼ��ADS1256
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, AD_CS_Pin|AD_SCLK_Pin|AD_DIN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AD_SYNC_GPIO_Port, AD_SYNC_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = AD_CS_Pin|AD_SCLK_Pin|AD_DIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = AD_DRDY_Pin|AD_DOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = AD_SYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(AD_SYNC_GPIO_Port, &GPIO_InitStruct);
	while(DRDY);//�ж�æµ״̬
	CS_L;//Ƭѡ����
	ADS1256_Write_8Bits(ADS1256_CMD_SELFCAL);//������У׼����
	while(DRDY);//�ж�æµ״̬
	CS_H;//Ƭѡ����

	ADS1256WREG(ADS1256_STATUS,0x06);               // ��λ��ǰ��У׼��ʹ�û���
	ADS1256WREG(ADS1256_STATUS,0x04);               // ��λ��ǰ���Զ�У׼����ʹ�û��壨�����Ƽ���

	ADS1256WREG(ADS1256_ADCON,GAIN); // PGA�Ŵ���
	ADS1256WREG(ADS1256_DRATE,RATE); // �������ʣ�����һ���˲����ã��ɲο������ֲ�
	ADS1256WREG(ADS1256_IO,0x00);    //����IO���ã����ù�û��
	
	
	while(DRDY);//�ж�æµ״̬
	CS_L;//Ƭѡ����
	ADS1256_Write_8Bits(ADS1256_CMD_SELFCAL);//������У׼����
	while(DRDY);//�ж�æµ״̬
	CS_H;//Ƭѡ����
}             


//-----------------------------------------------------------------//
//	�� �� ����ADS1256ReadData
//	��    ��: AINP--������  AINN������ //������ΪAINN-CIOM��Ϊ�������룬ANNXΪ���
//	�� �� ֵ: ������24λ����
//	��    ��: ���ζ�ȡ����
//-----------------------------------------------------------------//
uint32_t ADS1256ReadData(uint8_t AINP,uint8_t AINN) //��ȡ����
{
	uint32_t sum=0;
  while(DRDY);//��ADS1256_DRDYΪ��ʱ����д�Ĵ��� 
	ADS1256WREG(ADS1256_MUX,(AINP|AINN));		//����ͨ��	
	CS_L;//Ƭѡ���Ϳ�ʼ����
 	ADS1256_Write_8Bits(ADS1256_CMD_SYNC);
 	ADS1256_Write_8Bits(ADS1256_CMD_WAKEUP);
  while(DRDY);//��ADS1256_DRDYΪ��ʱ����д�Ĵ��� 	
	ADS1256_Write_8Bits(ADS1256_CMD_RDATA);//������ʼ��ȡ��������
	ADS1256_Delay();
  sum |= (ADS1256_Read_8Bits() << 16);
	sum |= (ADS1256_Read_8Bits() << 8);
	sum |= ADS1256_Read_8Bits();
	CS_L;
	if (sum>0x7FFFFF)           // if MSB=1, 
	{
		sum -= 0x1000000;       // do 2's complement
	}
    return sum;
}


//-----------------------------------------------------------------//
//	�� �� ����ADS1256ReadData
//	��    ��: AINP--������  AINN������ //������ΪAINN-CIOM��Ϊ�������룬ANNXΪ���  GAINΪ���õ�����
//	�� �� ֵ: ��ѹ����
//	��    ��: ���ζ�ȡ��ѹ����*0.000000598/(GAIN+1)
//-----------------------------------------------------------------//
double ADS1256GetVolt(uint8_t AINP_,uint8_t AINN_,int GAIN) //��ȡ����
{
	double data=0;
  data=ADS1256ReadData(AINP_, AINN_);
	if(data < 15000)
	{	
		data = 0.010;
	}
	else if(data < 35000)
	{
		data = 0.020;
	}
	else if(data < 50000)
	{
		data = 0.030;
	}
	else if(data < 70000)
	{
		data = 0.040;
	}
	else if(data < 85000)
	{
		data = 0.050;
	}
	else if(data < 105000)
	{
		data = 0.060;
	}
	else if(data < 120000)
	{
		data = 0.070;
	}
	else if(data < 135000)
	{
		data = 0.080;
	}
	else if(data < 150000)
	{
		data = 0.090;
	}
	else if(data < 165000)
	{
		data = 0.100;
	}
	else if(data < 838000)
	{
		data = data*0.0000006055;
	}			
	else if(data < 1680000)
	{
		data = data*0.0000005975;
	}	
	else if(data < 2480000)
	{
		data = data*0.0000005964;
	}	
	else if(data < 3280000)
	{
		data = data*0.0000005954;
	}		
	else
	{
		data = data*0.0000005940;
	}	
	float rounded_num = roundf(data * 1000) / 1000.0f;
  return (uint32_t)(rounded_num*100);	
}

