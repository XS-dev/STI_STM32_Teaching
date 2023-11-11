#ifndef ESP8266_H_
#define ESP8266_H_

#include "main.h"

extern int wave_type;

void init_esp8266(void);
void connect_udp(int pc_id);
void send_fft(void);

#endif
