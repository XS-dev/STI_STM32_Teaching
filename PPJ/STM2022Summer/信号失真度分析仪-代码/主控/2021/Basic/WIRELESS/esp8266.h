#ifndef ESP8266_H_
#define ESP8266_H_

#include "main.h"
#include "usart.h"
#include "measure.h"

void init_esp8266(void);
void connect_udp(int pc_id);
void send_THDx(void);
void send_point(void);


#endif
