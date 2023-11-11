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
//  Contains AD9854 configuration routines for parallel mode, and
//  some auxiliary user functions.
//  
//  DDS has an external 50MHz crystal oscillator connected.
//  
//  Also contains different board operational mode functions, like
//  auto scanning, manual scanning, chirp or modulation, etc.
//  (currently only the "manual scanning" over PC, tuning wheel and
//  keyboard is implemented)
//
//  Additionally contains funcs to convert the DDS tuning word
//  into a frequency and string representation.
//
// port 4: 8 bit data and
//         5 bit address through 74hc573 latch
// port 5: 5.0 RST, 5.1 !RD, 5.2 !WR, 5.3 IOCLK,
//         5.4 ALE,
//         not yet used : 5.5 FSK/MOD, 5.6 KEYING

#include "MSP430-fw-stdincludes.h"

#define DEBUG_DDS
#define POS_STEP 4
#define NEG_STEP -4

volatile unsigned long long   dds_lo_tw;        // tuning frequency (LO main freq)
volatile unsigned long long   dds_delta;        // freq step
volatile signed int           dds_wheeldivider; // wheel divider (turns vs freq steps)

char freq_str[12+10]; // filled out by call to DDS_Tuningword2FreqStr(tw), 
                      // [0..11]=LCDformat, [12..21]=PCformat, [22]=spare

//===================================================================
//
//       DDS CONFIGURATION ROUTINES
//


//-------------------------------------------------------------------
// DDS_init ( long long )
//
// Initialize the DDS : parallel data, external update clock,
//   no keying, no inverse sinc filtering, multipliers off, 
//   single tone mode
//
void DDS_init(void) 
{
   int i=0;

   // set frequency and step size (tuning wheel)
   dds_wheeldivider = 1;
//   if(RestoreSettings()==RESP_NACK) {  // get stored settings (not working 100% yet...)
      dds_delta = DEFAULT_DELTA;       // or use default settings
      dds_lo_tw = DEFAULT_LO_TW;
//   }
   
   // msp430 port setup
   DDS_DATA_DIR = 0xFF;
   DDS_CTRL_DIR = ~DDS_CLK;  // first, all outputs except AD9854 clock (input)
   DDS_DATA_OUT = 0;
   DDS_CTRL_OUT = 0xFF;

   // assert reset for a while
   DDS_CTRL_OUT |= DDS_RST;
   for(i=32000; i>0; --i) _NOP(); // wait a bit  
   DDS_CTRL_OUT &= ~DDS_RST;

   // assign to external update clock
   // addr 0x1F bits: 7=clrAcc1 6=clrAcc2 5=Triangle
   //                 4=SrcQDac (hi=no quadrature)
   //                 3=Mode[2] 2=Mode[1] 1=Mode[0]
   //                 0=Ext/IntUpdateClk (0=ext 1=int)
   DDS_writeByte( 0x00, 0x1F );
   DDS_commit();
   for(i=32000; i>0; --i) _NOP(); // wait a bit

   DDS_CTRL_DIR = 0xFF;  // now MSP430 can steer the clock signal (output)

   // DAC setup
   // addr 0x1D bits: 7=x 6=x 5=x 4=comparator power down (pd)
   //                 3=0 2=qdac pd 1=dac pw 0=dig pd
   // 0001 0001 - user-specified digital multipliers disabled, comp disabled
   DDS_writeByte( 0x10, 0x1D );

   // clock setup
   // addr 0x1E bits: 7=x
   //                 6=PLL range (0 <200MHz, 1 200..300MHz) 5=bypass PLL
   //                 4..0=ref clock multplier
   // 010 00100 - range 1, pll on, x4 (50->200 MHz)
   // DDS_writeByte( 0x40+DDS_MULTIPLIER, 0x1E );
   DDS_writeByte( 0x00+DDS_MULTIPLIER, 0x1E );

   // invsinc and other settings
   // addr 0x20 bits: 7=x 6=power down inv sinc
   //                 5=osk enable (shaped keying)
   //                 4=osk int (1 internal multipliers, 0 user specified multipliers)
   //                 3=x 2=x
   //                 1=lsb first (serial I/O) 0=sdo active (serial I/O)
   // 0101 0000 - inv sinc off, internal multipliers, keying off
   DDS_writeByte( 0x50, 0x20 );

   DDS_commit();

   return;
}


//-------------------------------------------------------------------
// unsigned char DDS_readByte ( unsigned char )
//
// Read back one byte from the DDS registers. Mainly useful for
// debugging the DDS routines.
//
unsigned char DDS_readByte(unsigned char addr)
{
   unsigned char temp=0;

   // write address
   DDS_DATA_DIR = 0xFF;
   DDS_DATA_OUT = addr;
   DDS_CTRL_OUT |= DDS_ALE;        // address into latch
   DDS_CTRL_OUT &= ~DDS_ALE; 

   // read data
   DDS_DATA_DIR = 0x00;
   DDS_CTRL_OUT &= ~DDS_NRD;       // "read"=0/lo

   temp = DDS_DATA_IN;

   DDS_CTRL_OUT |= DDS_NRD;        // return "read" to hi
   DDS_DATA_DIR = 0xFF;

   return temp;
}


//-------------------------------------------------------------------
// DDS_writeByte ( unsigned char, unsigned char )
//
// Writes one byte to the DDS but doesn't commit it yet.
//
void DDS_writeByte(unsigned char data, unsigned char addr) 
{
   DDS_DATA_DIR = 0xFF;

   // write address
   DDS_DATA_OUT = addr;
   DDS_CTRL_OUT |= DDS_ALE;      // address into latch
   DDS_CTRL_OUT &= ~DDS_ALE;

   // write data
   DDS_DATA_OUT = data;
   DDS_CTRL_OUT &= ~DDS_NWR;     // "write"=0/lo
   DDS_CTRL_OUT |= DDS_NWR;      // return write to hi

   // remember to call DDS_commit() later
   // to have the AD9854 apply the new settigns
   return;
}


//-------------------------------------------------------------------
// DDS_commit ( )
//
// Commit the transferred DDS data, pulses the IO update clock to
// move the data from the AD9854 internal buffer to its registers.
//
void DDS_commit(void) 
{
   DDS_CTRL_OUT |= DDS_CLK;
   DDS_CTRL_OUT &= ~DDS_CLK;
}


//-------------------------------------------------------------------
// DDS_writeLongTuningword ( long long )
//
// Writes the tuning word to the DDS, but doesn't commit the 
// data yet.
//
void DDS_writeLongTuningword(long long tw) 
{
   long long tmp = tw;
   unsigned char out; int i;
   
   // write last 6 bytes of tuningword (=all DDS TW registers)
   for(i=0;i<6;i++) {
      out = (unsigned char)(tmp&0xFF);
      DDS_writeByte(out, 0x09-i);
      tmp=tmp>>8;
   }
   // remember to call DDS_commit() later
   // to have the AD9854 apply the new settigns
   return;
}




//===================================================================
//
//       OPERATIONAL MODE FUNCTIONS
//


//-------------------------------------------------------------------
// DDS_autoscan1 ( )
//
// For DEBUGGING only
//
void DDS_autoscan1(void) 
{
   signed long scn = 0x04000000;
   // 0x08E00001 = 6.94 MHz
   // 0x01E00001 = 1.6 MHz
   // 0x05400000 = 4.1 MHz
   // 0x04000000 = 3.13 MHz
   signed long tmp;
   signed long dir = POS_STEP;

   DDS_DATA_DIR = 0xFF;

   // load multipliers (just to be safe)

   DDS_DATA_OUT = 0x21; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
   DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);
   DDS_DATA_OUT = 0x22; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
   DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);
   
   DDS_DATA_OUT = 0x23; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
   DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);
   DDS_DATA_OUT = 0x24; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
   DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);

   DDS_commit();


   // scan the frequency range

   while(1)
    {

      if(scn<SCAN_LIM_LO) dir=POS_STEP;
      if(scn>SCAN_LIM_HI) dir=NEG_STEP;

      scn += dir;

      // 3 x 8 bit = 24 bit

      tmp = scn;
      DDS_DATA_OUT = 0x04; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
      DDS_DATA_OUT = (tmp>>24)&0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);

      tmp = scn;
      DDS_DATA_OUT = 0x05; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
      DDS_DATA_OUT = (tmp>>16)&0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);

      tmp = scn;
      DDS_DATA_OUT = 0x06; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
      DDS_DATA_OUT = (tmp>>8)&0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);

      DDS_DATA_OUT = 0x07; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
      DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);
      DDS_DATA_OUT = 0x08; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
      DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);
      DDS_DATA_OUT = 0x09; setBit(DDS_CTRL_OUT,DDS_ALE); clrBit(DDS_CTRL_OUT,DDS_ALE);
      DDS_DATA_OUT = 0xFF; clrBit(DDS_CTRL_OUT,DDS_NWR); setBit(DDS_CTRL_OUT,DDS_NWR);

      DDS_commit();

      if(kbdUnreadCount>0)
       {
         LCD_writeHexByte(kbdGetChar());
         LCD_writeChar('/');
      }

      if(wheel_counter<0)
         { wheel_counter=0; dir=NEG_STEP; LCD_writeChar('-'); }
      if(wheel_counter>0)
         { wheel_counter=0; dir=POS_STEP; LCD_writeChar('+'); }
   }
   
   return;
}



//-------------------------------------------------------------------
// DDS_manualscan ( )
//
// Manual frequency scanning loop, function does NOT return but
// checks the serial and keyboard data, and tuning wheel state.
// 
void DDS_manualscan(void) 
{
   long long oldTW;
   unsigned char metres; 
   char *out;
   
   DDS_DATA_DIR = 0xFF;

   // load DDS multipliers (just to be safe)
   DDS_writeByte(0xFF, 0x21);
   DDS_writeByte(0xFF, 0x22);
   DDS_writeByte(0xFF, 0x23);
   DDS_writeByte(0xFF, 0x24);
   
   // set startup frequency
   DDS_writeLongTuningword(dds_lo_tw);
   DDS_commit();
   out = DDS_Tuningword2FreqStr(dds_lo_tw,1);
   if(1==FWConfig.LCD_enabled) { 
      LCD_home(2);
      LCD_writeString(out);
   }
   PC_writeString("FREQ ");
   PC_writeString(&freq_str[12]);
   PC_writeString((char*)STR_CRLF);
   
   // -- user tuning
   //kbdResume();

   while(1) {

      oldTW=dds_lo_tw;

      // handle remote commands from PC and local keyboard entry
      processCmdPC();
      processCmdKeyboard();

      // tuning wheel turned?
      if((wheel_counter/dds_wheeldivider)<0 ) { //&& (dds_lo_tw>=SCAN_LIM_LO)) {
         wheel_counter+=WHEEL_DIV_RESO; dds_lo_tw -= dds_delta;
         //if((dds_lo_tw<SCAN_LIM_LO) || (dds_lo_tw>SCAN_LIM_HI)) dds_lo_tw=SCAN_LIM_LO;
      }
      if((wheel_counter/dds_wheeldivider)>0 ) { // && (dds_lo_tw<=SCAN_LIM_HI)) {
         wheel_counter-=WHEEL_DIV_RESO; dds_lo_tw += dds_delta;
         //if((dds_lo_tw<SCAN_LIM_LO) || (dds_lo_tw>SCAN_LIM_HI)) dds_lo_tw=SCAN_LIM_HI;
      }

//>>DEBUG
      if(dds_lo_tw>SCAN_LIM_HI) { PC_writeChar('#'); }
      //if((dds_lo_tw<SCAN_LIM_LO) || (dds_lo_tw>SCAN_LIM_HI)) dds_lo_tw=DEFAULT_LO_TW;
//>>
      
      // update the DDS freq and user display?
      if(oldTW!=dds_lo_tw) {
   
         DDS_writeLongTuningword(dds_lo_tw);
         DDS_commit();

         out = DDS_Tuningword2FreqStr(dds_lo_tw,1);

         // write to PC 
         PC_writeString("FREQ ");
         PC_writeString(&freq_str[12]);
         PC_writeString((char*)STR_CRLF);
         // write to LCD if enabled
         if(1==FWConfig.LCD_enabled) {
            LCD_home(2);
            out = DDS_Tuningword2FreqStr(dds_lo_tw,1);
            LCD_writeString(out);
         
            metres = getBandMetres((dds_lo_tw/1000)/DDS_1HZ_STEP);
            if(metres!=0) {
               LCD_writeChar(' ');
               if(metres>99) { 
                  LCD_writeChar('1');
                  metres%=100; 
               }
               if(metres>9) { 
                  LCD_writeChar('0'+metres/10);
                  metres%=10;
               }
               LCD_writeChar('0'+metres);
               LCD_writeChar('m');
               LCD_writeChar(' ');
               LCD_writeChar(' ');
            } else {
               LCD_writeString("      \0");
            }
            
            //DDS_Smeter(5); // todo: use msp430 internal ADC
            
         }
      }

  }//(infinite loop)

}




//===================================================================
//
//       UI HELPERS
//


//-------------------------------------------------------------------
// long DDS_Tuningword2Freq ( long long )
//
// Converts the tuning word into Hertz.
// 
unsigned long DDS_Tuningword2Freq(long long tuningword)
{
   // f_dds = (ref*multipl) * tuningword / 2^48
   //          200 MHz * tuningword / 2^48 = tw / (2^48/200E6)
   //       = tw / 1407374.884 [Hz]
   return (unsigned long) ( ((unsigned long long)tuningword / (unsigned long long)DDS_1HZ_STEP) );
}


//-------------------------------------------------------------------
// char* DDS_Tuningword2FreqStr ( long long, char )
//
// Creates a string representation in Hz of the specified DDS 
// tuning word. Formatting is in both LCD style, which is 
// with dots and no leading 0 in the 10MHz's, and PC style,
// which is just the plain Hz display.
// The string is placed into global 'freq_str'.
// freq_str[0..11] = LCD formatted, freq_str[12..23] = PC formatted
// Returns pointer to the actual start of the string.
//
char* DDS_Tuningword2FreqStr(long long tuningword, char LCDformat)
{
   unsigned char tmp;
   register unsigned char c;
   unsigned long freqhz;
   int i, j;
   
   // f_dds = (ref*multipl) * tuningword / 2^48
   //          200 MHz * tuningword / 2^48 = tw / (2^48/200E6)
   //       = tw / 1407374.884 [Hz]
   freqhz = (long) ( ((long long)tuningword / (long long)DDS_1HZ_STEP) );

   i=0;  // starting idx for LCD format
   j=12; // starting idx for PC format
   
   //
   // LCD format : freq_str[0..11, or 0..10]
   //   format as "12.345.678"(MHz) when freq>=10MHz 
   //   or "1.234.567"(Mhz) when freq<10MHz
   //
   // PC format :  freq_str[12..23]
   //   format as "12345678"(Hz) always
   //

   tmp=(freqhz/10000000); 
   freqhz = freqhz%10000000; //  10*1E6
   c='0'+tmp;
   freq_str[i++]=c; 
   freq_str[j++]=c;
   tmp=(freqhz/1000000); 
   freqhz = freqhz%1000000;   //   1*1E6
   c='0'+tmp;
   freq_str[i++]=c; 
   freq_str[j++]=c;
   freq_str[i++]='.';                               //     '.'
   tmp=(freqhz/100000);  
   freqhz = freqhz%100000;    // 100*1E3
   c='0'+tmp;
   freq_str[i++]=c;
    freq_str[j++]=c;
   tmp=(freqhz/10000); 
   freqhz = freqhz%10000;     //  10*1E3
   c='0'+tmp;
   freq_str[i++]=c;
    freq_str[j++]=c;
   tmp=(freqhz/1000);  
   freqhz = freqhz%1000;      //   1*1E3
   c='0'+tmp;
   freq_str[i++]=c;
    freq_str[j++]=c;
   freq_str[i++]='.';                               //     '.'
   tmp=(freqhz/100);     
   freqhz = freqhz%100;       //     100
   c='0'+tmp;
   freq_str[i++]=c;
    freq_str[j++]=c;
   tmp=(freqhz/10);    
     freqhz = freqhz%10;        //      10
   c='0'+tmp;
   freq_str[i++]=c; 
   freq_str[j++]=c;
   c='0'+freqhz;
   freq_str[i++]=c;
    freq_str[j++]=c;                //       1
   
   freq_str[i++]='\0'; 
   //freq_str[j++]='\0';

   // Return pointer to LCD formatting 
   if(1==LCDformat) {
      // return without a leading zero
      if('0'==freq_str[0]) { return (char*)&freq_str[1]; }
      else { return (char*)&freq_str[0]; }
   }
   // PC formatting, simply return pointer to second part of string
   return (char*)&freq_str[12];
}


//-------------------------------------------------------------------
// DDS_Smeter ( )
//
// Display s-meter on the second LCD line.
//
void DDS_Smeter(unsigned char s) 
{
   if(s<=9) 
   {
      LCD_moveTo(55);
      LCD_writeChar('S');
      LCD_writeChar(s+'0');
   }
}
