#include "bsp_ads1115.h"

/* ���� */
adsGain_t m_gain;
/* ����ͨ�� */
uint8_t m_channel = 0;


 
/**
  * @brief  �������üĴ���
  * @param  None
  * @retval None:
  */
void ads1115_Init(void)
{
  ads1115_I2C_INIT();  // ads1115_I2C init

  /* ���� */
  m_gain = GAIN_ONE;

  /* config the config reg */
  if (ConfigeRegister(m_channel))
  {
    // deal error 
    printf("init configreg error\r\n");
  }
  
}

/**
  * @brief  �������üĴ���
  * @param  channel : ͨ��X(0..3)
  * @retval None:
  */
 uint8_t  ConfigeRegister(unsigned char channel)
{

      /* Set config reg valus */
  uint16_t config = ADS1015_REG_CONFIG_CQUE_NONE    | // ���ñȽ���              (default val)
                    ADS1015_REG_CONFIG_CLAT_NONLAT  | // ������Ƚ���            (default val)
                    ADS1015_REG_CONFIG_CPOL_ACTVLOW | // ALERT/RDY �͵�ƽ��Ч    (default val)
                    ADS1015_REG_CONFIG_CMODE_TRAD   | // ���г��͵Ĵ�ͳ�Ƚ���     (default val)
                    ADS1015_REG_CONFIG_DR_1600SPS   | // 1600 samples per second (default val)
                    ADS1015_REG_CONFIG_MODE_CONTIN;   // Single-shot mode       
  
  /* Set PGA/voltage range */
  config |= m_gain;
  
  /* Set 'start single-conversion' bit */
  config |= ADS1015_REG_CONFIG_OS_SINGLE;

  /* Set single-ended input channel */
  switch (channel)
  {
    case (0):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
      break;
    case (1):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
      break;
    case (2):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
      break;
    case (3):
      config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
      break;
  }
  

   /* Write config register to the ADC */
   if (writeRegister(CMD_ADS1115_Write_REG, ADS1015_REG_POINTER_CONFIG, config))
   {
     
     // deal no ack error
     return 1;
   }
   
   /* normal return */
   return 0;

}

  

/**
  * @brief  ָ��Ĵ���
  * @param  ads1115_I2CAddress : ADS115��ַ�Ͷ�дλ 0bit���ƶ�д
  * @param  reg        :  Ҫ�����ļĴ���
  * @retval None:
  */
 uint8_t  PointRegister (uint8_t ads1115_I2CAddress, uint8_t reg)
{  
    
  /* ads1115_I2C start */
    ads1115_I2C_Start(); 
  
  /* sent addr and write reg */
    ads1115_I2C_Send_Byte(ads1115_I2CAddress);
  /* ack */
   if (ads1115_I2C_Wait_Ack())
   {
      return 1;
   }
   
   /* Point reg is seted convert reg */
   ads1115_I2C_Send_Byte(reg);
   /* ack */
    if (ads1115_I2C_Wait_Ack())
   {
       return 1;
   }
   
   /* ads1115_I2C stop */
  ads1115_I2C_Stop();
   
  /* normal rerturn */
  return 0;
 }

/**
  * @brief  ��������
  * @param  gain : ���� 
  * @retval None:
  */
 void  SetGain(adsGain_t gain)
 {
   m_gain = gain;
 }
 
/**
  * @brief  ȡ������
  * @param  None
  * @retval None
  */
 adsGain_t GetGain(void)
 {
   return m_gain;
 }
 
 
/**
  * @brief  д�Ĵ���
  * @param  ads1115_I2CAddress : ADS115��ַ�Ͷ�дλ 0bit���ƶ�д
  * @param  reg        :  Ҫ�����ļĴ���
  * @param  value      :  д��Ĵ�����ֵ
  * @retval None
  */
  uint8_t writeRegister(uint8_t ads1115_I2CAddress, uint8_t reg, uint16_t value) 
 {
   
  ads1115_I2C_Start(); 
   /* ��ַ�Ͷ�д��ַ */
  ads1115_I2C_Send_Byte(ads1115_I2CAddress);
   /* ACK */
  if (ads1115_I2C_Wait_Ack())
   {
     return 1;
   }
   
   /* �Ĵ�����ַ */
  ads1115_I2C_Send_Byte(reg);
    /* ACK */
   if (ads1115_I2C_Wait_Ack())
   {
     return 1;
   }
   
   /* Lo_thresh�Ĵ��� */
  ads1115_I2C_Send_Byte((uint8_t)(value>>8));
   /* ACK */
   if (ads1115_I2C_Wait_Ack())
   {
     return 1;
   }
   
   /* Hi_thresh�Ĵ��� */
  ads1115_I2C_Send_Byte((uint8_t)(value & 0xFF));
   /* ACK */
   if (ads1115_I2C_Wait_Ack())
   {
     return 1;
   }
  ads1115_I2C_Stop();
   
   /* normal return */
   return 0;
}
 


/**
  * @brief  ��ȡconvert�Ĵ���
  * @param  None
  * @retval None
  */
 uint16_t readConvertRegister(void) 
{ 
  uint8_t high = 0;
  uint8_t low = 0;
  /* ads1115_I2C start */
  ads1115_I2C_Start(); 
  /* addr and read reg */
  ads1115_I2C_Send_Byte((uint8_t)CMD_ADS1115_Read_REG);
   /* ACK */
   if (ads1115_I2C_Wait_Ack())
   {
     return 1;
   }
   
   high = ads1115_I2C_Read_Byte(1);
   low = ads1115_I2C_Read_Byte(1);
   
   /* ads1115_I2C stop */
  ads1115_I2C_Stop();

  return (high<<8 | low);
}

/**
  * @brief  ���adc��ֵ
  * @param  None
  * @retval None
  */
uint16_t GetAds1115Values(void)
{
	  /* point to convert reg .ready to read adc values */
  if (PointRegister(CMD_ADS1115_Write_REG,ADS1015_REG_POINTER_CONVERT))
  {
    // deal error 
    printf("init PointRegister error\r\n");
  }
  
   return readConvertRegister();
}


/* ------------- ads1115_I2C drive ---------- */


/**
  * @brief  IIC��ʼ��IO
  * @param  None
  * @retval None
  */
void ads1115_I2C_INIT()
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SCL_Pin|SDA_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADDR_GPIO_Port, ADDR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = SCL_Pin|SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = ADDR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ADDR_GPIO_Port, &GPIO_InitStruct);

  ads1115_I2C_SCL_H;
  ads1115_I2C_SDA_H;
}

/**
  * @brief  SDA�������
  * @param  None
  * @retval None
  */
void SDA_Pin_OUT()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  /*Configure GPIO pin : PE3 */
  GPIO_InitStruct.Pin = SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief  SDA��������
  * @param  None
  * @retval None
  */
void SDA_Pin_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOE_CLK_ENABLE();
  /*Configure GPIO pins : PE2 PE3 */
  GPIO_InitStruct.Pin = 	SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief  ������ʼ�ź��ź�
  * @param  None
  * @retval None

SCL   -------|_____


SDA    ---|________

*/
void ads1115_I2C_Start(void)
{
  SDA_Pin_OUT();
  
  ads1115_I2C_SDA_H;
  ads1115_I2C_SCL_H;
  ads1115_delay_us(2);
  ads1115_I2C_SDA_L;
  ads1115_delay_us(2);
  ads1115_I2C_SCL_L;
}

/**
  * @brief  ����ֹͣ�ź�
  * @param  None
  * @retval None

SCL   ------------

SDA   ____|-------
  
*/
void ads1115_I2C_Stop(void)
{
   SDA_Pin_OUT();

   ads1115_I2C_SCL_L;
   ads1115_I2C_SDA_L;
   ads1115_I2C_SCL_H;
   ads1115_delay_us(2);
   ads1115_I2C_SDA_H;
   ads1115_delay_us(2);
}

/**
  * @brief  ��������Ӧ���ź�ACK
  * @param  None
  * @retval None
  */
void ads1115_I2C_Ack(void)
{
   ads1115_I2C_SCL_L;
   SDA_Pin_OUT();
   ads1115_I2C_SDA_L;
   ads1115_delay_us(2);
   ads1115_I2C_SCL_H;
   ads1115_delay_us(2);
   ads1115_I2C_SCL_L;
}

/**
  * @brief  ����������Ӧ���ź�ACK
  * @param  None
  * @retval None
  */
void ads1115_I2C_NAck(void)
{
   ads1115_I2C_SCL_L;
   SDA_Pin_OUT();
   ads1115_I2C_SDA_H;
   ads1115_delay_us(2);
   ads1115_I2C_SCL_H;
   ads1115_delay_us(2);
   ads1115_I2C_SCL_L;
}

/**
  * @brief  �ȴ��ӻ�Ӧ���ź�
  * @param  txd Ҫ���͵��ַ�
  * @retval ����ֵ��1 ����Ӧ��ʧ�� 0 ����Ӧ��ɹ�
��ACK:
SCL   -------

SDA   ---|____

û��ACK;

SCL   -------

SDA   -------
*/
uint8_t ads1115_I2C_Wait_Ack(void)
{
  uint8_t tempTime=0;

  SDA_Pin_IN();

  ads1115_I2C_SDA_H;
  ads1115_delay_us(2);
  ads1115_I2C_SCL_H;
  ads1115_delay_us(2);

  while(HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin))
  {
    tempTime=HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin);
    if(tempTime == 0)
    {
      // ads1115_I2C_Stop();
      break;
    }  
  }

  ads1115_I2C_SCL_L;
  return 0;
}
//ads1115_I2C ����һ���ֽ�

/**
  * @brief  ads1115_I2C ����һ���ֽ�
  * @param  txd Ҫ���͵��ַ�
  * @retval None:
  *
 SCL __|----|___|-----|___

 SDA __|--------|_________

����:  |-- 1----| ----0---|

*/
void ads1115_I2C_Send_Byte(uint8_t txd)
{
  uint8_t i=0;

  SDA_Pin_OUT();
  ads1115_I2C_SCL_L;//����ʱ�ӿ�ʼ���ݴ���

  for(i=0;i<8;i++)
  {
    if((txd&0x80)>0) //0x80  1000 0000
		{
      ads1115_I2C_SDA_H;
		}
    else
		{
      ads1115_I2C_SDA_L;
		}

    txd<<=1;
    ads1115_I2C_SCL_H;
    ads1115_delay_us(2); //��������
    ads1115_I2C_SCL_L;
    ads1115_delay_us(2);
  }
}


/**
  * @brief  ads1115_I2C ��ȡһ���ֽ�
  * @param  ask: 1 ��ȡ��Ӧ��,0 û��Ӧ��
  * @retval None:
  */
uint8_t ads1115_I2C_Read_Byte(uint8_t ack)
{
   uint8_t i=0,receive=0;

   SDA_Pin_IN();
   for(i=0;i<8;i++)
   {
    ads1115_I2C_SCL_L;
    ads1115_delay_us(2);
    ads1115_I2C_SCL_H;
    receive<<=1;
    if(HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin))
       receive++;
    ads1115_delay_us(1);  
   }
   
   if(ack==0)
      ads1115_I2C_NAck();
   else
      ads1115_I2C_Ack();
   
  return receive;
}



/* -------------- delay --------------*/



/**
  * @brief  ��ʱ��������ʱus
  * @param  i(0..255)
  * @retval None:
  */
void ads1115_delay_us(uint32_t i)
{
	Delay_Us(i);
}

/**
  * @brief  ��ʱ��������ʱms
  * @param  i(0..255)
  * @retval None:
  */
void ads1115_delay_ms(uint32_t i)
{
	Delay_Ms(i);
}



