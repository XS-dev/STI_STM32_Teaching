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
//  MSP430-fw-main.c: the main() startup routine and struct FWConfig
//
//===================================================================
//
//  Components connected to the MSP430:
//
//    Quarz crystal:    4.433MHz (or some close to 4MHz) 
//    AT keyboard:      I/O pins P2.6 (clock), P2.7 (data)
//    PC RS-232:        UART1 UTXD1 (P3.6), URXD1 (P3.7)
//    LCD (4-bit mode): port P1
//    AD9854 DDS:       ports P4 and P5
//    Tuning wheel:     I/O pins P2.0 and P2.1
//
//  This project won't compile on the IAR EWB /free/
//  version since during compiling the 4k limit is exceeded.
//  It should compile on the commercial version, though.
//
//  It won't compile on the TI's CCE, mainly because
//  that compiler does not support "long long"'s nor quad's
//  that are required for the AD9854 tuning word calculations.
//
//===================================================================

#include "MSP430-fw-stdincludes.h"

struct _FWConfig FWConfig;          // firmware configuration
volatile unsigned int sys_ticks;    // counter, 1 tick = 8192/crystalfreq seconds

const char STR_CRLF[3]="\r\n\0";

int main(void)
{
   unsigned int i;

   // -- init user command buffers
   pcCmdBufPos = 0; pcCmdBuf[0]='\0';
   pcCmdEOL = 0;
   kbdCmdBufPos = 0; kbdCmdBuf[0]='\0';
   kbdFlags = 0;
   
   // -- MSP430 controller setup
   P6DIR = 0xFF; // debugging leds
   P6OUT = 0;

   // -- peripherals and interrupt init
   initInterrupts();
   // suspend AT keyboard transmissions for later
   //   kbdSuspend();
   
   // -- system startup delay
   // give other devices time to start up, LCD needs 15ms
   // (as the 6us start-up time of the MSP430 might be too fast)
   i=sys_ticks; while((sys_ticks-i)<15) _NOP();
   //for(i=10000; i>0; --i) _NOP();

   // xt2 crystal clock (users guide ch 7.5)
   BCSCTL1 &= ~XT2OFF;   // 64 + 4;  // 01 000 100 = XT2 not off, XTS=hf xtal, rsel=4
   do {
      IFG1 &= ~OFIFG;    // clear osc fault flag
      for(i=0;i<256;i++) _NOP();
   } while((IFG1&OFIFG)!=0);
   BCSCTL2 |= (SELM1 + SELS);  // mclk = xt2, smclk = xt2

   // -- peripherals init

   FWConfig.LCD_enabled = 1;
   FWConfig.LCD_present = 1;
   LCD_init();

   // -- status display

   LCD_home(1);
   LCD_writeString(FW_VERSION_LCD);
   PC_writeLine("Cheddar54 DDS RX");
   PC_writeLine(FW_VERSION_PC);
   PC_writeLine(FW_COPYRIGHT);

   DDS_init();

   DDS_manualscan();
   
   return 0;
}

