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
//  User keyboard and PC serial control commands.
//  The keyboard scan codes are decoded for Finnish/Swedish keyboards,
//  other keyboards may or may not decode correctly.
//
//  Command syntax:
//  HELP              list of commands (without the debug commands)
//  INFO              progam version info
//  FREQ mmkkkhhh     set the frequency
//  STEP n[nn][k]     set frequency step size, e.g. STEP 15k
//  WHEEL {+|-}nn     turn the wheel, e.g. WHEEL +15
//  BAND n[n][m]      switch to start of freq band, e.g. BAND 20m
//  ...
//  Debug commands: DUMP DDS
//

#define ECHO_PCCONS     // define to send result of command over serial port
#define ECHO_PC_TO_LCD  // define to show PC commands on the LCD

// debug flags, comment out when not needed
//#define DEBUG_KBDCONS             // (currently unused)
//#define DEBUG_KBDCONS_SCANCODES   // define to dump keyboard scancodes to PC

#include "MSP430-fw-stdincludes.h"

// local funcs
unsigned char  parseCmdString (unsigned char cmdBuf[]);
unsigned char  strSemiComp (char *str1, char *str2);

// buffers
volatile unsigned char  pcCmdBuf[MAX_CMD_LEN+1];
volatile unsigned char  pcCmdBufPos;
volatile char           pcCmdEOL;

volatile unsigned char  kbdCmdBuf[MAX_CMD_LEN+1];
volatile unsigned char  kbdCmdBufPos;
volatile char           kbdFlags;
#define  FLAG_X   BIT0     // 1=special char follows
#define  FLAG_KR  BIT1     // 1=key release event/char follows
#define  FLAG_EOL BIT2     // 1=got full cmd line (after ENTER)

// ACK/NACK responses send back over the serial port
const char* PC_OK    = "OK";
const char* PC_NACK  = "NACK";

// -- scan code to ascii and internal keydef tables
//
// extended chars, internal codes used in this prog
//  0x00 none    0x01 left alt  0x02 left shift  0x03 left ctrl  0x04 enter
//  0x05 backspc 0x06 esc       0x07 num lock    0x08 scoll lock 0x09 end
//  0x0a arr lft 0x0b home      0x0c insert      0x0d arr down   0x0e arr right
//  0x0f arr up  0x10 num '0'   ... 0x19 num'9'  0x1a down       0x1b up
#define ScancodeLUT_START 0x15
const unsigned char ScancodeLUT[] = {  // table starts at 0x15 !! and the keyboard is FINNISH/SWEDISH...
   'q', '1',  0, 0, 0, 'z', 's', 'a', 'w', '2', 0,  // 0x15 - 0x1F
   0, 'c', 'x', 'd', 'e', '4', '3', 0, 0, ' ', 'v', 'f', 't', 'r', '5', 0, // 0x20-0x2F
   0, 'n', 'b', 'h', 'g', 'y', '6', 0, 0, 0, 'm', 'j', 'u', '7', '8', 0, // 0x30-0x3F
   0, ',', 'k', 'i', 'o', '0', '9', 0, 0, '.', '-', 'l', 'ö', 'p', '+', 0, // 0x40-0x4F
   0, 0, 'ä', 0, 'å', '´', 0, 0, 0, 0, SC_ENTER,
   '¨', 0, '*', 0, 0, // 0x50-0x5F
   0, 0, 0, 0, 0, 0, SC_BACKSPC,
   0, 0, SC_NUM0+1, 0, SC_NUM0+4, SC_NUM0+7, 0, 0, 0, // 0x60-0x6F
   SC_NUM0, SC_BACKSPC, SC_NUM0+2, SC_NUM0+5, SC_NUM0+6, SC_NUM0+8, SC_ESC,
   SC_NUMLOCK, 0, 0, SC_NUM0+3, 0, 0, SC_NUM0+9, SC_SCOLLLOCK, 0 // 0x70-0x7F
};
#define ScancodeXLUT_START 0x5A
const unsigned char ScancodeXLUT[] = { // special chars, 0xE0 xx style, table starts at 0x5A !!!
   SC_ENTER, 0, 0, 0, 0, 0,   // 0x5A - 0x5F
   0, 0, 0, 0, 0, 0, 0, 0, 0, SC_END, // 0x60 - 0x69
   0, SC_ARRLEFT, SC_HOME, 0, 0, 0, // 0x6A - 0x6F
   SC_INSERT, SC_BACKSPC, SC_ARRDOWN, 0, SC_ARRRIGHT, SC_ARRUP, // 0x70 - 0x75
   0, 0, 0, SC_PAGEDOWN, // 0x76 - 0x79
   SC_PAGEUP, 0, 0, SC_PAGEDOWN, 0, 0 // 0x7A - 0x7F
   // (code set 1 vs set 2 seem to have mixed PgUp/PgDown scancodes, thus...)
};




//===================================================================
//
//       HELPER FUNCS
//


//-------------------------------------------------------------------
// byte2hex ( unsigned char, unsigned char[] )
//
// Converts the specified byte value into a null-terminated hex string.
//
void byte2Hex(unsigned char num, unsigned char out[]) 
{
   out[1]=(num&0x0F); 
   out[0]=((num&0xF0)>>4)&0x0F;
   if(out[1]>9) { out[1]='A'+(out[1]-10); } else { out[1]='0'+out[1]; }
   if(out[0]>9) { out[0]='A'+(out[0]-10); } else { out[0]='0'+out[0]; }
   out[2] = '\0';
   return;
}

//-------------------------------------------------------------------
// uchar strSemiComp ( char *, char * )
//
// Returns 1 if the beginning of string1 is the same as string2,
// and 0 otherwise
//
unsigned char strSemiComp(char *str1, char *str2)
{
   unsigned char a, b; int x;

   if(*str1=='\0' || *str2=='\0') return 0;

   for(x=0; x<MAX_CMD_LEN; x++) {
      a=*(str1+x);
      b=*(str2+x);
      if(b=='\0') return 1; // || b==' ') return 1;
      if(a!=b) return 0;
      //if(a==b) continue;
   }
   return 0;
}


//-------------------------------------------------------------------
// processCmdPC ( )
//
// Reads the PC serial input buffer and checks if there is a 
// full new command line i.e. a string terminated with CR & LF
//
void processCmdPC(void)
{
   unsigned char tmp;

   _DINT();
   // assemble command line
   do {
      tmp=PC_readChar();
      if(tmp==0) break;          // no chars

      // end of line?
      if(tmp=='\r' || tmp==10 || tmp==13) { 
         pcCmdEOL=1; 
         pcCmdBufPos=0; 
         break; 
      }

      // overflow?
      if(pcCmdBufPos>=MAX_CMD_LEN) break;

      // to lower case
      if(tmp>='A' && tmp<='Z') { tmp='a'+(tmp-'A'); }

      // add only proper chars to the buffer
      if(tmp>='a' && tmp<='z') { pcCmdBuf[pcCmdBufPos++]=tmp; }
      else if(tmp>='0' && tmp<='9') { pcCmdBuf[pcCmdBufPos++]=tmp; }
      else if(tmp==' ' || tmp=='.' || tmp=='-' || tmp=='+') { pcCmdBuf[pcCmdBufPos++]=tmp; }

      pcCmdBuf[pcCmdBufPos]='\0';

   } while(tmp!=0);

   // got a full command line
   if(pcCmdEOL==1) {

      #ifdef ECHO_PCCONS
         #ifdef ECHO_PC_TO_LCD
         LCD_clearLine(1);
         LCD_moveTo(0);
         LCD_writeString("PC: ");
         LCD_writeString((char *)pcCmdBuf);
         #endif
      PC_writeString("rx<"); PC_writeString((char *)&pcCmdBuf[0]); PC_writeString(">\r\n");
      #endif

      // check and execute the command
      parseCmdString((unsigned char *)pcCmdBuf);

      // purge rest of the command line
      pcCmdEOL=0;
      pcCmdBufPos=0;
      pcCmdBuf[0]=0;
      pcCmdBuf[1]=0;
   }

   _EINT();

}


//-------------------------------------------------------------------
// processCmdKeyboard ( )
//
// Reads the keyboard input buffer and convert scan codes into 
// ASCII characters. It displays a command line on the first row
// of the LCD, and checks for a new full command line (str+<enter>)
//
// To allow fast typing, ASCII characters are added to the buffer
// after a key release events (instead immediately on a keypress event).
//

void processCmdKeyboard(void)
{
   unsigned char xchar;
   #ifdef DEBUG_KBDCONS_SCANCODES
   unsigned char cTmp[4];
   #endif
   
   //kbdSuspend(); // no interference from keyboard

   // -- assemble command line
   
   do {
      
      // get next scancode
      
      xchar=kbdGetChar();
      if(xchar==0) {
         break;  // 0, no new chars
      }
      
      #ifdef DEBUG_KBDCONS_SCANCODES
      PC_writeString(" 0x"); byte2Hex(xchar, cTmp); PC_writeString((char*)cTmp);
      #endif
   
      if(xchar==0xE0) 
      { kbdFlags |= FLAG_X; continue; }    // special char follows
      
      if(xchar==0xF0)
      { kbdFlags |= FLAG_KR; continue; }   // key release event, remember for next char
      
      if(xchar>0xF0 || xchar<ScancodeLUT_START) 
      { continue; }                  // unhandled codes, assume some kind of "mess"
   
      // look up scan code => key
      
      if((kbdFlags&FLAG_X)!=0) {   
         // extended key code
         kbdFlags &= ~FLAG_X;   // clear flag
         if(xchar>=ScancodeXLUT_START && xchar<(ScancodeXLUT_START+sizeof(ScancodeXLUT))) { 
            xchar = ScancodeXLUT[xchar-ScancodeXLUT_START]; 
         } else {
            xchar = 0;
         }
      } else {
         // simple key
         if(xchar>=ScancodeLUT_START && xchar<(ScancodeLUT_START+sizeof(ScancodeLUT)))
         { xchar = ScancodeLUT[xchar-ScancodeLUT_START]; }
      }     

      // process new char and command line string
      
      // a key PRESS event
      if((kbdFlags&FLAG_KR)==0) {
         
         // pressing Enter completes the line
         if(xchar==SC_ENTER) {
            kbdFlags |= FLAG_EOL;  // got full cmd
            kbdCmdBufPos = 0; 
            break;            
         }
         
         // (ignore other key press events)
         
      // a key RELEASE event   
      } else {            
         
         kbdFlags &= ~FLAG_KR; // clear flag
         
         // first process keys with special meanings
         
         if((xchar==0) || (xchar==SC_ENTER)) {
            continue;
         } 
         
         if(xchar==SC_BACKSPC) {              // backspace, delete char
            if(kbdCmdBufPos>0) kbdCmdBufPos--;
            //kbdCmdBuf[kbdCmdBufPos]='\0'; - done below!
            //break;
         } else if(xchar==SC_PAGEUP) { 
            wheel_counter++; 
            break; 
         } else if(xchar==SC_PAGEDOWN) { 
            wheel_counter--; 
            break;
         }
   
         if(kbdCmdBufPos>=MAX_CMD_LEN) { continue; }     // buf overflow

         // add proper chars (released keys) to cmdline str
         if(xchar>='a' && xchar<='z') 
            { kbdCmdBuf[kbdCmdBufPos++]=xchar; }
         else if(xchar>='0' && xchar<='9') 
            { kbdCmdBuf[kbdCmdBufPos++]=xchar; }
         else if(xchar==' ' || xchar=='.' || xchar=='-' || xchar=='+') 
            { kbdCmdBuf[kbdCmdBufPos++]=xchar; }
      
         kbdCmdBuf[kbdCmdBufPos]='\0';
                  
         // show the current command line on the LCD
         LCD_clearLine(1);
         LCD_moveTo(0); 
         LCD_writeString((char *)kbdCmdBuf);
      }
            
   } while(xchar!=0);

   //kbdResume();   // enable keyboard xmit

   // got a full command line?
   if((kbdFlags&FLAG_EOL)!=0) {

      PC_writeString("# KEYB<"); PC_writeString((char *)&kbdCmdBuf[0]); PC_writeString(">\r\n");

      // check and execute the command
      xchar = parseCmdString((unsigned char *)kbdCmdBuf);
      // if(xchar==RESP_NACK) { LCD_write("ERR",1,40-3); }

      // purge rest of the command line
      kbdFlags &= ~FLAG_EOL;
      kbdCmdBufPos=0;
      kbdCmdBuf[0]=0;
      kbdCmdBuf[1]=0;
      LCD_home(1);
      LCD_writeString(FW_VERSION_LCD);      
   }
   
   return;
}



//-------------------------------------------------------------------
// parseCmdString ( unsigned char[] )
//
// Parses and executes the specified command string.
//
unsigned char parseCmdString(unsigned char cmdBuf[])
{
   unsigned char tmp, i, cTmp[3], resp;
   unsigned long ltmp; long long lltmp;
   signed int itmp;

   resp = RESP_NONE;
   
   // commands are pre-converted to lower case
   if(strSemiComp((char *)&cmdBuf[0], "freq ")==1) {

      // ==> FREQ mmkkkhhh
   
      lltmp = 0;
      for(i=5;i<13;i++) {
         lltmp *= 10;
         if(cmdBuf[i]>='0' && cmdBuf[i]<='9') lltmp += (long long)(cmdBuf[i]-'0');
      }
      lltmp *= DDS_1HZ_STEP;

      #ifdef ECHO_PCCONS
      PC_writeLine("Freq Set");
      #endif 
      //if(lltmp>=SCAN_LIM_LO && lltmp<=SCAN_LIM_HI) {
      dds_lo_tw = lltmp;
      resp = RESP_OK;
      //} else {
      // #ifdef ECHO_PCCONS
      // PC_writeLine("Freq Limit ERR");
      // #endif      
      //}

   } else if(strSemiComp((char *)&cmdBuf[0], "band ")==1) {
   
      // BAND n[n][m]
      ltmp=0;
      for(i=5;i<9 && cmdBuf[i]!='\0';++i) {
         if(cmdBuf[i]>='0' && cmdBuf[i]<='9') { 
            ltmp = 10*ltmp + (cmdBuf[i]-'0'); 
         } else break;
      }
      lltmp = (long long)getBandFreqkHz((unsigned char)ltmp);

      #ifdef ECHO_PCCONS
      PC_writeLine("Band Set");
      #endif      
      if(lltmp!=0) {
         lltmp *= 1000;
         dds_lo_tw = lltmp*DDS_1HZ_STEP;
         resp = RESP_OK;
      } else {
         resp = RESP_NACK;
      }
      
   } else if(strSemiComp((char *)&cmdBuf[0], "step ")==1) {

      // ==> STEP n[nn][K]
      //     t.ex. STEP 10K, STEP 100

      ltmp = 0; tmp=0;

      for(i=5;i<9;i++) {
         tmp = cmdBuf[i];
         if(tmp>='0' && tmp<='9') {            // number
            ltmp = 10*ltmp + (tmp-'0');
         } else {                              // '\0', K or M
            if(tmp=='k') ltmp *= 1000;
            if(tmp=='m') ltmp *= 1000000;
            break;
         }
      }

      #ifdef ECHO_PCCONS
      PC_writeLine("Step Set");
      #endif 
      if(ltmp!=0) {
         dds_delta = (long long)ltmp * (long long)DDS_1HZ_STEP;
         resp = RESP_OK;
      } else {
         resp = RESP_NACK;
      }

   } else if(strSemiComp((char *)&cmdBuf[0], "info")==1) {

      // ==> INFO
      
      PC_writeLine("Cheddar54 DDS RX");
      PC_writeLine(FW_VERSION_PC);
      PC_writeLine(FW_COPYRIGHT);

   } else if(strSemiComp((char *)&cmdBuf[0], "wheel ")==1) {

      // ==> WHEEL [+/-]nn
      // t.ex. WHEEL -25, WHEEL +05

      if(cmdBuf[6]=='-') 
         { itmp=-1; } 
      else 
         { itmp=1; }
      itmp *= ((cmdBuf[7]-'0')*10 + (cmdBuf[8]-'0'));

      #ifdef ECHO_PCCONS
      PC_writeLine("Wheel Toggle");
      #endif
      if(itmp>=-99 && itmp<=99) { 
         wheel_counter = itmp; 
         resp = RESP_OK;
      } else {
         resp = RESP_NACK;
      }

   } else if(strSemiComp((char *)&cmdBuf[0], "help")==1) {

      // ==> HELP

      PC_writeLine("HELP, INFO    general infos");
      PC_writeLine("FINE n        set wheel divisor");
      PC_writeLine("FREQ mmkkkhhh set LO frequency");
      PC_writeLine("STEP n[nn][k] set tuning step size");
      PC_writeLine("WHEEL {+|-}nn 'rotate' tuning wheel");

   } else if(strSemiComp((char *)&cmdBuf[0], "fine ")==1) {

      #ifdef ECHO_PCCONS
      PC_writeLine("Wheel Divider");
      #endif
      tmp=cmdBuf[5];
      if(tmp>='1' && tmp<='9') {
         dds_wheeldivider = tmp-'0';
         resp = RESP_OK;
      } else {
         resp = RESP_NACK;
      }
      
   } else if(strSemiComp((char*)cmdBuf, "dump dds")==1) {
      
      PC_writeLine("DDS register dump:");
      for(i=0x00;i<0x28;i++) {
         byte2Hex(i, cTmp);
         PC_writeString((char*)cTmp);
         PC_writeString("->");
         tmp=DDS_readByte(i);
         byte2Hex(tmp, cTmp);
         PC_writeString((char*)cTmp);
         PC_writeString((char*)STR_CRLF);
      }
      
   } else if(strSemiComp((char*)cmdBuf, "save")==1) {

         #ifdef ECHO_PCCONS
         PC_writeLine("Save State");
         #endif
         SaveSettings();
         resp = RESP_OK;
      
   } else if(strSemiComp((char*)cmdBuf, "load")==1) {

         #ifdef ECHO_PCCONS
         PC_writeLine("Load State");
         #endif
         resp = RestoreSettings();

   }

   #ifdef ECHO_PCCONS
   if(resp==RESP_OK) {
      PC_writeLine((char*)PC_OK);
   } else if(resp==RESP_NACK) {
      PC_writeLine((char*)PC_NACK);
   }
   #endif
   
   return resp;
}
