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

#ifndef __MSP430_FW_CONSOLE_H
#define __MSP430_FW_CONSOLE_H

#define MAX_CMD_LEN 20

extern volatile unsigned char pcCmdBuf[MAX_CMD_LEN+1];   // serial command buffer
extern volatile unsigned char pcCmdBufPos;
extern volatile char          pcCmdEOL;

extern volatile unsigned char kbdCmdBuf[MAX_CMD_LEN+1];  // keyboard command buffer
extern volatile unsigned char kbdCmdBufPos;
extern volatile char          kbdFlags;

void  processCmdPC (void);
void  processCmdKeyboard (void);
void  byte2Hex (unsigned char num, unsigned char out[]);

// -- ACK/NACK responses send back over the serial port
#define RESP_NONE    0
#define RESP_OK      1
#define RESP_NACK    2
extern const char*   PC_OK;
extern const char*   PC_NACK;


// -- scan code to ascii and internal keydef tables
//
// extended chars, internal codes used in this prog
//  0x00 none    0x01 left alt  0x02 left shift  0x03 left ctrl  0x04 enter
//  0x05 backspc 0x06 esc       0x07 num lock    0x08 scoll lock 0x09 end
//  0x0a arr lft 0x0b home      0x0c insert      0x0d arr down   0x0e arr right
//  0x0f arr up  0x10 num '0'   ... 0x19 num'9'  0x1a down       0x1b up
#define SC_ENTER        0x04
#define SC_BACKSPC      0x05
#define SC_ESC          0x06
#define SC_PAGEUP       0x1B
#define SC_PAGEDOWN     0x1A
#define SC_ARRLEFT      0x0A
#define SC_ARRRIGHT     0x0E
#define SC_ARRUP        0x0F
#define SC_ARRDOWN      0x0D
#define SC_NUM0         0x10
#define SC_NUMLOCK      0x07
#define SC_SCOLLLOCK    0x08
#define SC_HOME         0x0B
#define SC_INSERT       0x0C
#define SC_END          0x09


#endif
