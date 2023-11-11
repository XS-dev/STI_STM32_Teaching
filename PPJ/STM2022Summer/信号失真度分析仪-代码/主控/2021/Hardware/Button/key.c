#include "key.h"


void KeyInit(void){
	
	/* KY1�жϷ�ʽ  */
  GPIO_setAsInputPinWithPullUpResistor(KEY1_PORT,KEY1_PIN);//����
  GPIO_clearInterruptFlag(KEY1_PORT, KEY1_PIN);//����жϱ�־
	
  GPIO_enableInterrupt(KEY1_PORT, KEY1_PIN); //ʹ���ж�
  Interrupt_enableInterrupt(INT_PORT1);//ʹ��ָ���˿��ж�
  Interrupt_enableMaster(); //ʹ�����ж�
	
	/*   KY2���жϷ�ʽ   */
 GPIO_setAsInputPin(KEY2_PORT, KEY2_PIN); //ѡ��˿ڼ�������Ϊ����˿�
 GPIO_setAsInputPinWithPullUpResistor(KEY2_PORT, KEY2_PIN);//����
 GPIO_disableInterrupt(KEY2_PORT, KEY2_PIN);//��ֹ�ж�
 }


	void PORT1_IRQHandler(void){  //IO�ж�
	volatile uint32_t  state ;
  state  = GPIO_getEnabledInterruptStatus(KEY1_PORT);//��ȡ״̬
	if(state &KEY1_PIN ){ 
  delay_ms(5);  //����
	if(!(GPIO_getInputPinValue(KEY1_PORT,KEY1_PIN ))) //ȷ�ϰ���
	{
   GPIO_toggleOutputOnPin(GPIO_PORT_P2,KEY1_PIN);          //�������ִ�г���
	 while(!(GPIO_getInputPinValue(KEY1_PORT,KEY1_PIN ))); //�жϰ����Ƿ��ͷ�
   delay_ms(5);//����
   GPIO_setAsInputPinWithPullUpResistor(KEY1_PORT,KEY1_PIN);//�ͷŰ���������
	 } 
	}
	GPIO_clearInterruptFlag(KEY1_PORT,KEY1_PIN);//����жϱ�־
 }



