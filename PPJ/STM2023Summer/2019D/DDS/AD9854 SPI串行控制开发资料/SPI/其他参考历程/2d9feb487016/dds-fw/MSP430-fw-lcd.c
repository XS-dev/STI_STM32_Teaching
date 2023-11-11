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
//  MSP430-fw-lcd.c: LCD driving routines, 4-bit mode
//                   Use an Hitachi 44780 based LCD module
//
//===================================================================
//
//  MSP pin-out as in the Eagle schematics:
//  P1.0 - 12   bit 0
//  P1.1 - 13   bit 1
//  P1.2 - 14   bit 2     MSP430F14x
//  P1.3 - 15   bit 3
//  P1.4 - 16   R/W
//                   EN      R/S
//                   17      18     19(unused)
//                  P1.5    P1.6   P1.7
//
//  http://www.doc.ic.ac.uk/~ih/doc/lcd/initiali.html
//
//===================================================================

#include "MSP430-fw-stdincludes.h"

//#define DEBUG_LCD  // define to debug Port1 data (will skip the waits)

// LCD time delays - critical!! 
// Probably need to adjust these if MSP430 runs at more than 4.5MHz
#define LCD_STROBEWAIT  16     // strobes
#define LCD_WRITEWAIT   256    // writes
#define LCD_EXTRAWAIT   256    // waiting after 4-bit set

//-------------------------------------------------------------------
// LCD_init ( )
// Initialize the LCD to 4 bit mode
//
void LCD_init(void) 
{
   unsigned int i;

   // output pins low and as output (except last pin)
   LCD_OUT &= BIT7;
   LCD_DIR |= ~BIT7;

   // do nothing if LCD is disabled
   if(0==FWConfig.LCD_enabled) return;

   // -- function set: 001Zxxxx    ; Z={1 eight bit mode, 0 four bit mode}
   // -- start with 8-bit init first, repeat three times
   
   LCD_OUT |= 3;  // 0011-<snip>, sets 8-bit mode
   LCD_datastrobe();
   #ifndef DEBUG_LCD
   i=sys_ticks; while((sys_ticks-i)<16) _NOP(); // wait over 4ms
   #endif
   // set 8-bit a second and third time
   LCD_datastrobe();
   #ifndef DEBUG_LCD
   i=sys_ticks; while((sys_ticks-i)<2) _NOP(); // wait ~2ms (over 100us)
   #endif
   LCD_datastrobe();
   #ifndef DEBUG_LCD
   i=sys_ticks; while((sys_ticks-i)<2) _NOP(); // wait ~2ms (over 100us)
   #endif

   // -- now switch to 4-bit mode 

   // note: command is still '8 bit bus', so don't send the lower bits
   LCD_OUT &= ~0x01;    // <0011>(xxxx) => <0010>(xxxx)
   LCD_datastrobe();
   #ifndef DEBUG_LCD
   i=sys_ticks; while((sys_ticks-i)<2) _NOP(); // short ~2ms wait
   #endif
   
   // -- 4 bit mode set - reconfigure the display
   
   //    write full 8 command bits == two 4bit writes
   //    0010 - NFXX  ; N={0 one line, 1 two line mode}
   //                   F={0 display off, 1 on}
   //    0010 - 1000
   LCD_writeCmd(0x28);     // set to two-line mode
   #ifndef DEBUG_LCD
   for(i=LCD_EXTRAWAIT;i>0;--i) _NOP(); // extra wait
   #endif

   // Display on/off control
   // 0000 - 1DCB  ; D={0 display off, 1 on} C={0 cursor off, 1 on}
   //                B={0 blink off, 1 on}
   // 0000 - 1100
   LCD_writeCmd(0x0C);   // turn ON display
   #ifndef DEBUG_LCD
   for(i=LCD_EXTRAWAIT;i>0;--i) _NOP(); // extra wait
   #endif

/*
   // Display clear  (removed, way too slow...)
   // 0000 - 0001
   LCD_writeCmd(0x01);

   // wait _really_ long... (should be >1.64ms)
   #ifndef DEBUG_LCD
   for(i=40000; i>0; --i) _NOP();
   #endif
*/

   // Entry mode set
   // 0000 - 01IS  ; I={0 cursor decrement mode, 1 increment},
   //                S={0 display shift off, 1 on}
   // 0000 - 0110
   LCD_writeCmd(0x06);  // auto-increment cursor position

   // LCD can now be written to
   LCD_clearLine(1);
   LCD_clearLine(2);
   
   return;
}


//-------------------------------------------------------------------
// LCD_datastrobe()
// Strobe the LCD EN pin and wait for >40us
//
void LCD_datastrobe(void) 
{
   register int i;

   // strobe EN high
   LCD_OUT |= LCD_EN_BIT;
   #ifndef DEBUG_LCD
   for(i=LCD_STROBEWAIT; i>0; --i) _NOP();
   #endif

   // return EN to low
   LCD_OUT &= ~LCD_EN_BIT;
   #ifndef DEBUG_LCD
   for(i=LCD_STROBEWAIT; i>0; --i) _NOP();
   #endif

   // some more waiting... very efficient coding...
   #ifndef DEBUG_LCD
   for(i=LCD_WRITEWAIT; i>0; --i) _NOP();
   #endif
   return;
}


//-------------------------------------------------------------------
// LCD_home ( unsigned char )
// Moves the cursor to the start of the specified line
// 1 = first line, 2 = second line
//
void LCD_home(unsigned char line) 
{
   if(2==line) LCD_writeCmd(0x80 + 41); // 1aaa aaaa - set DDRAM address to 41 (line 2)
   else LCD_writeCmd(0x02);              // 0000 001x - move cursor home
   return;
}

//-------------------------------------------------------------------
// LCD_moveTo ( unsigned char )
// Moves the cursor to the given position
//
void LCD_moveTo(unsigned char pos) 
{
   LCD_writeCmd(0x80 + pos);     // move char to position 'pos'
   return;
}

//-------------------------------------------------------------------
// LCD_clearLine ( unsigned char )
// Clears the specified line on the LCD.
// 1 = first line, 2 = second line
//
void LCD_clearLine(unsigned char line)
{
   int i;
   // go to start of line
   if(2==line) LCD_writeCmd(0x80 + 41); // 1aaa aaaa - set DDRAM address to 41 (line 2)
   else LCD_writeCmd(0x02);             // 0000 001x - move cursor home
   // blank the line
   for(i=0;i<LCD_CHARS_PER_LINE;++i) {
      LCD_writeChar(' ');
   }
   // go back to start of line
   if(2==line) LCD_writeCmd(0x80 + 41); // 1aaa aaaa - set DDRAM address to 41 (line 2)
   else LCD_writeCmd(0x02);             // 0000 001x - move cursor home      
   return;
}

//-------------------------------------------------------------------
// LCD_write[Cmd/Char] ( unsigned char )
// Writes a command or a character byte to the LCD using 4-bit mode
// The LCD 'busy' flag is not polled.
//
void LCD_writeCmd(unsigned char byte) 
{
   // do nothing if LCD is disabled
   if(0==FWConfig.LCD_enabled) return;

   LCD_DIR |= ~BIT7;          // make sure all LCD pins are outputs
   LCD_OUT &= BIT7;           // clear all except 7th (unused) bit
                              // RW=0 RS=0 EN=0
   LCD_write(byte);
   return;
}
void LCD_writeChar(unsigned char byte) 
{
   // do nothing if LCD is disabled
   if(0==FWConfig.LCD_enabled) return;

   LCD_DIR |= ~BIT7;            // make sure the LCD pins are outputs
   LCD_OUT &= BIT7;             // clear all except 7th (unused) bit
   LCD_OUT |= LCD_RS_BIT;       // RW=0 RS=1 EN=0
   LCD_write(byte);
   return;
}

void LCD_write(unsigned char byte) 
{
   unsigned char hi, lo;
   
   // write hi bits
   hi = byte>>4;
   lo = byte&0x0F;
   LCD_OUT |= hi;
   LCD_datastrobe();

   // write lo bits
   LCD_OUT = (LCD_OUT&0xF0) | lo;
   LCD_datastrobe();

   return;
}


//-------------------------------------------------------------------
// LCD_writeString ( char[] )
// Write a zero-terminated string to the LCD. The maximum string
// length is 40 characters.
//
void LCD_writeString(char *s) 
{
   unsigned int pos = 0;
   while((pos<40) && *(s+pos)!=0) {
      LCD_writeChar(*(s+pos));
      pos++;
   }
   return;
}


//-------------------------------------------------------------------
// LCD_writeHexByte ( unsigned char )
// Displays an 8-bit number in hex format on the LCD
//
void LCD_writeHexByte(unsigned char num) {
   unsigned char lo, hi;

   lo=(num&0x0F); 
   hi=(num&0xF0)>>4;

   if(lo>9) { lo='A'+(lo-10); } 
   else { lo='0'+lo; }
   
   if(hi>9) { hi='A'+(hi-10); } 
   else { hi='0'+hi; }

   LCD_writeChar(hi);
   LCD_writeChar(lo);
   return;
}
