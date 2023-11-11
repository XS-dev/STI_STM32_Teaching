//===================================================================
//
//  MSP430F149 based direct digital conversion
//  software defined radio receiver
//
//  (C) 2005 Jan Florian Wagner OH2GHR, jwagner@cc.hut.fi
//  http://users.tkk.fi/~jwagner/electr/dc-rx/
//
//  Firmware Version 1.03
//
//  Licence: free as per GNU GPL
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  For further details see the included GPL.TXT 
//  or go to http://www.gnu.org/copyleft/gpl.html  
//
//===================================================================
//
// Interrupt handlers
// - keyboard (i/o pins 2.5 clock & 2.6 data)
// - serial comm (uart1)
// - tuning wheel (i/o pins 2.0 & 2.1)
//
//===================================================================

#ifndef __MSP430_FW_INTERRUPTS_H
#define __MSP430_FW_INTERRUPTS_H

#include <msp430x14x.h>

#define KBD_CLK    BIT5       // AT clock: port 2 pin 5 
#define KBD_DAT    BIT6       // AT data:  port 2 pin 6

#define XTAL_FREQ 4433619     // msp430 xtal2 port crystal
#define PCBAUDRT  9600        // baud rate to PC

#define  LED_1     BIT2       // diagnostic LED on port 6

void initInterrupts(void);

// tuning wheel counter (-32000 to +32000)
extern volatile signed int wheel_counter;

// keyboard scancode input buf
#define KBD_BUFSIZE     6

// uart i/o buffers
#define PC_RXBUF     10
#define PC_TXBUF     10

extern volatile unsigned char kbdBuf[KBD_BUFSIZE+1];
extern volatile unsigned char kbdBufPos;
extern volatile char          kbdUnreadCount;

extern volatile unsigned char pcRxBuf[PC_RXBUF+1];
extern volatile unsigned char pcRxBufPos;
extern volatile char          pcRxUnreadCount;

extern volatile unsigned char pcTxBuf[PC_TXBUF+1];
extern volatile unsigned char pcTxBufPos;
extern volatile char          pcTxUnsentCount;
extern volatile char          pcTxDone;

unsigned char  kbdGetChar (void);
void           kbdSuspend (void); 
void           kbdResume (void);

void           PC_writeChar (unsigned char out);
void           PC_writeString (char *str);
void           PC_writeLine (char *str);
unsigned char  PC_readChar (void);

void           Flash_wb (char *Data_ptr, char byte);
void           Flash_ww (int *Data_ptr, int word);
void           Flash_clr (int *Data_ptr);

#endif
