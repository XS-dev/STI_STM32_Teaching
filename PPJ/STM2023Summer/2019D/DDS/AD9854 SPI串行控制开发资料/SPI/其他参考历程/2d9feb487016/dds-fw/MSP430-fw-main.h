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

#ifndef __MSP430_FW_CONFIG_H_
#define __MSP430_FW_CONFIG_H_

struct _FWConfig
{
   unsigned short LCD_present : 1;
   unsigned short LCD_enabled : 1;
   unsigned short KBD_present : 1;
   unsigned short KBD_failure : 1;
};

extern struct _FWConfig FWConfig;         // firmware configuration
extern volatile unsigned int sys_ticks;   // system tick counter (see main.c or interrupts.c)

extern const char STR_CRLF[3];            // carriage-return and linefeed

#endif
