#include "led.h"

u8 menu=0,i=0;
u16 t=0;

void LedInit(void){
  GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);//配置输出模式
	GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN1);
 }

void  LedSet(u8 state){ 
 if(state==1){
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN0);//P40口输出高电平
  } 
 else if(state==2){
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN1);//P41输出高电平
   }
  else if(state==3){
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);//P42输出高电平
   }
	 else if(state==4){
   GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN3);//P43输出高电平
   }
	else { 
	  GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
	 }
 }

void  LedPwm(void){ 
	if(menu ==0){      //苏醒，快呼吸模式
	 for(i=0;i<5;i++){ 
	  	LedSet(1);
			delay_us(t+5);
		 	LedSet(0);
		 	delay_us(701-t);
	 }
	 t++;
	if(t==700){ 
	 menu =1;
	  }
	 }
	if(menu ==1){ 
	 for(i=0;i<5;i++){ 
	  	LedSet(1);
			delay_us(t+5);
		 	LedSet(0);
		 	delay_us(701-t);
	 }
	 t--;
	if(t==1){ 
	 menu =0;
	  }
	 }


 


 }
 
 
