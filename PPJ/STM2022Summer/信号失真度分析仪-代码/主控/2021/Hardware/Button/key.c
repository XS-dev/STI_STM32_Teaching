#include "key.h"


void KeyInit(void){
	
	/* KY1中断方式  */
  GPIO_setAsInputPinWithPullUpResistor(KEY1_PORT,KEY1_PIN);//上拉
  GPIO_clearInterruptFlag(KEY1_PORT, KEY1_PIN);//清除中断标志
	
  GPIO_enableInterrupt(KEY1_PORT, KEY1_PIN); //使能中断
  Interrupt_enableInterrupt(INT_PORT1);//使能指定端口中断
  Interrupt_enableMaster(); //使能主中断
	
	/*   KY2非中断方式   */
 GPIO_setAsInputPin(KEY2_PORT, KEY2_PIN); //选择端口及引脚作为输入端口
 GPIO_setAsInputPinWithPullUpResistor(KEY2_PORT, KEY2_PIN);//上拉
 GPIO_disableInterrupt(KEY2_PORT, KEY2_PIN);//禁止中断
 }


	void PORT1_IRQHandler(void){  //IO中断
	volatile uint32_t  state ;
  state  = GPIO_getEnabledInterruptStatus(KEY1_PORT);//获取状态
	if(state &KEY1_PIN ){ 
  delay_ms(5);  //消抖
	if(!(GPIO_getInputPinValue(KEY1_PORT,KEY1_PIN ))) //确认按下
	{
   GPIO_toggleOutputOnPin(GPIO_PORT_P2,KEY1_PIN);          //这里放需执行程序
	 while(!(GPIO_getInputPinValue(KEY1_PORT,KEY1_PIN ))); //判断按键是否释放
   delay_ms(5);//消抖
   GPIO_setAsInputPinWithPullUpResistor(KEY1_PORT,KEY1_PIN);//释放按键后拉高
	 } 
	}
	GPIO_clearInterruptFlag(KEY1_PORT,KEY1_PIN);//清除中断标志
 }



