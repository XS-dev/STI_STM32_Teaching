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

#ifndef __MSP430_FW_LCD_H
#define __MSP430_FW_LCD_H

#include <msp430x14x.h>

// P1.0 - 12   bit 1
// P1.1 - 13   bit 2
// P1.2 - 14   bit 3
// P1.3 - 15   bit 4
// P1.4 - 16   R/W
//                  EN      R/S
//                  17      18     19(unused)
//                 P1.5    P1.6   P1.7

#include <msp430x14x.h>

#define LCD_OUT      P1OUT     // LCD port, 4-bit mode
#define LCD_DIR      P1DIR
#define LCD_RW_BIT   BIT4
#define LCD_EN_BIT   BIT5
#define LCD_RS_BIT   BIT6

#define LCD_CHARS_PER_LINE    24
#define LCD_LINES             2

void           LCD_datastrobe (void);
void           LCD_init (void);
void           LCD_writeCmd (unsigned char byte);
void           LCD_writeChar (unsigned char byte);
void    LCD_write (unsigned char byte);
void           LCD_writeString (char *s);
void           LCD_home (unsigned char line);
void           LCD_moveTo (unsigned char pos);
void           LCD_clearLine(unsigned char line);
void           LCD_writeHexByte (unsigned char num);

#endif
