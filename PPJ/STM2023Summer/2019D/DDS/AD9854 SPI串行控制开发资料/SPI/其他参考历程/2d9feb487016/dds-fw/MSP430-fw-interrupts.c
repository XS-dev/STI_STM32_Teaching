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
//  Interrupt handlers, with PC serial port receive and transmit.
//  Also initializes the serial port to 9600 baud.
//  Provides helper functions for AT keyboard access.
//
// - keyboard (i/o pins 2.5 clock & 2.6 data)
// - serial comm (uart1)
// - tuning wheel (i/o pins 2.0 & 2.1)
//
//===================================================================

//#define NEW_KBD_FUNCS 1
//#define WDT_SYSTICK_DEBUG 1  // define to blink the LED at system ticks

#include "MSP430-fw-stdincludes.h"

volatile unsigned char kbdBuf[KBD_BUFSIZE+1];   // keyboard scancode buf
volatile unsigned char kbdBufPos;
volatile char kbdUnreadCount;

volatile unsigned char pcRxBuf[PC_RXBUF+1];     // PC rx
volatile unsigned char pcRxBufPos;
volatile char pcRxUnreadCount;

volatile unsigned char pcTxBuf[PC_TXBUF+1];     // PC tx
volatile unsigned char pcTxBufPos;
volatile char pcTxUnsentCount;
volatile char pcTxDone;

volatile signed int wheel_counter;              // wheel rx

#define KBD_DLY 2000

#ifdef __IAR_SYSTEMS_ICC__
  // empty interrupt table, IAR EWB v3 style of declaration
  #pragma vector=UART0TX_VECTOR
     __interrupt void intUart0Tx(void) {};
  #pragma vector=UART0RX_VECTOR
     __interrupt void intUart0Rx(void) {};   
  #pragma vector=PORT1_VECTOR
     __interrupt void intPort1(void) {};
  #pragma vector=ADC_VECTOR
     __interrupt void intADC(void) {};
  #pragma vector=TIMERA1_VECTOR
     __interrupt void intTimerA1(void) {};
  #pragma vector=TIMERA0_VECTOR
     __interrupt void intTimerA0(void) {};
  #pragma vector=TIMERB1_VECTOR
     __interrupt void intTimerB1(void) {};
  #pragma vector=TIMERB0_VECTOR
     __interrupt void intTimerB0(void) {};
  #pragma vector=COMPARATORA_VECTOR
     __interrupt void intComparator(void) {};
#else
  // empty interrupt table, MSP-GCC style of declaration
  interrupt (UART0TX_VECTOR) intUart0Tx(void) {};
  interrupt (UART0RX_VECTOR) intUart0Rx(void) {};  
  interrupt (PORT1_VECTOR) intPort1(void) {};
  interrupt (ADC_VECTOR) intADC(void) {};
  interrupt (TIMERA1_VECTOR) intTimerA1(void) {};
  interrupt (TIMERA0_VECTOR) intTimerA0(void) {};
  interrupt (TIMERB1_VECTOR) intTimerB1(void) {};
  interrupt (TIMERB0_VECTOR) intTimerB0(void) {};
  interrupt (COMPARATORA_VECTOR) intComparator(void) {};
#endif
   


//===================================================================
//
//       BASIC INIT
//

//-------------------------------------------------------------------
// initInterrupts ( )
// Set up the serial port, and wheel/keyboard port interrupts.
//
void initInterrupts(void) {

   _DINT();
   
   // -- reconfig watch dog timer as interval mode interrupt
   
   WDTCTL = WDTPW + WDTCNTCL + 
            WDTTMSEL + WDTIS0;   // clear counter, interval mode
                                 // WDTIS0: 470..540Hz (SMCLK/8192)
                                 // - : 122..135Hz (SMCLK/32768)
   sys_ticks = 0;
   
   // -- port 2 pin interrupts
    
   // enable tuning wheel interrupt on pin 2.0 and
   // AT keyboard clock int on 2.5   (users guide page 195 / 9-3)
   P2SEL &= ~(BIT0+BIT1+KBD_CLK+KBD_DAT);    // don't use modules, just i/o
   P2DIR &= ~(BIT0+BIT1+KBD_CLK+KBD_DAT);    // set 2.0 .1 .5 .6 as inputs
   P2IES |= BIT0+KBD_CLK;                    // P2.0 or P2.5 high->low generates interrupt
   P2IFG = 0x00;                             // clear interrupt flags
   P2IE  |= BIT0+KBD_CLK;                    // pin int enable
   wheel_counter = 0; 
   kbdBufPos = 0; 
   kbdUnreadCount = 0;
   
   // -- serial comm port config
    
   P3DIR = 0xFF;                      // all pins as outputs (utxd0, utxd1)
   P3DIR &= ~(BIT1+BIT3+BIT5+BIT7);   // simo0, uclk0, urxd0 and urxd1 as inputs
   P3SEL |= BIT1+BIT3+BIT5+BIT6+BIT7; // port 3 pins multiplexed to simo0, uclk0,
                                      // urxd0, urxd1, utxd1
   // PC serial comm : uart1 "9600,n,8,1"
   // (page 244, 12.5.2)
   U1CTL = SWRST;                     // reset, as in users guide
   U1CTL |= CHAR;
   U1TCTL |= SSEL0+SSEL1+TXEPT;
   U1RCTL = 0;
   U1MCTL = 0x0;
   U1BR0 = (XTAL_FREQ/PCBAUDRT)&0x00FF;
   U1BR1 = ((XTAL_FREQ/PCBAUDRT)&0xFF00)>>8;

   pcRxBufPos = 0; 
   pcTxBufPos = 0;
   pcRxUnreadCount = 0; 
   pcTxUnsentCount = 0;
   pcTxDone = 1;

   // enable uart modules (page 53, table 3-13)
   // (unused:ME1 |= USPIE0;  // uart 0 SPI enable
   ME2 |= URXE1+UTXE1;        // uart 1 rx tx enable

   //U0CTL &= ~(SWRST);   // USART init sequence last stage, as recommended
   U1CTL &= ~(SWRST);     // on page 242

   // -- enable interrupts (page 47, table 3-5)
   //IE1 |= URXIE0;      // uart 0 rx int enable
   IE2 |= URXIE1+UTXIE1;    // enable UART 1 rx&tx interrupt
   IE1 |= NMIIE+OFIE+WDTIE; // enable NMI, oscillator fault, watchdog/interval interrupt

   _EINT();
   
   return;
}



//===================================================================
//
//       INTERRUPT HANDLERS
//


//-------------------------------------------------------------------
// intWDT ( )
// Watchdog interrupt handler, with watchdog in interval counter mode.
// Advances the system tick counter. 1 tick = 8192/crystalfreq seconds.
// If using 4.433Mhz xtal clock: 1 tick = ~1.8ms
// 
#ifdef __IAR_SYSTEMS_ICC__
  #pragma vector=WDT_VECTOR
    __interrupt void intWDT(void)
#else
  interrupt (WDT_VECTOR) intWDT(void)
#endif
{
   ++sys_ticks;
   #ifdef WDT_SYSTICK_DEBUG
   if(sys_ticks%128==0) { P6OUT^=LED_1; } // blink the LED
   #endif
}

//-------------------------------------------------------------------
// intNMI ( )
// NMI handler, usually called when the crystal oscillator fails
//
#ifdef __IAR_SYSTEMS_ICC__
  #pragma vector=NMI_VECTOR
    __interrupt void intNMI(void)
#else
  interrupt (NMI_VECTOR) intNMI(void)
#endif
{
   int i;

   // osc fault?
   if((IFG1&OFIFG)!=0) {
      do {
         IFG1 &= ~OFIFG;           // clear osc fault flag
         for(i=0;i<256;i++) { _NOP(); }
         //if((IFG1)&OFIFG!=0) P6OUT=0xFF; else P6OUT=0;
      } while((IFG1&OFIFG)!=0);   // try restarting the xtal2
      IE1 |= OFIE;
   }
}


//-------------------------------------------------------------------
// intUart1Rx ( )
// Received data on UART1 RX line, from the PC
//
#ifdef __IAR_SYSTEMS_ICC__
  #pragma vector=UART1RX_VECTOR
    __interrupt void intUart1Rx(void)
#else
  interrupt (UART1RX_VECTOR) intUart1Rx(void)
#endif
{
   int tmp = RXBUF1;
   if(!(pcRxUnreadCount>=PC_RXBUF)) { pcRxUnreadCount++; }

   ++pcRxBufPos; 
   pcRxBufPos%=PC_RXBUF;
   pcRxBuf[pcRxBufPos] = tmp;
}


//-------------------------------------------------------------------
// intUart1Tx ( )
// One data byte has been sent, check transmitter buffer to send more
//
#ifdef __IAR_SYSTEMS_ICC__
  #pragma vector=UART1TX_VECTOR
    __interrupt void intUart1Tx(void)
#else
  interrupt (UART1TX_VECTOR) intUart1Tx(void)
#endif
{
   signed char tmpPos;

   if(pcTxUnsentCount==0) {
   
      pcTxDone = 1;
   
   } else {
   
      pcTxDone = 0;

      // pcTxUnsentCount = 1 : pcTxBuf[pcTxBufPos] newest
      // pcTxUnsentCount = 2 : pcTxBuf[pcTxBufPos-1] newest
      // ...

      tmpPos=1+((signed char)pcTxBufPos)-((signed char)pcTxUnsentCount);
      if(tmpPos<0) { tmpPos+=PC_TXBUF; }
      pcTxUnsentCount--;
      TXBUF1=pcTxBuf[tmpPos];
   }
}


//-------------------------------------------------------------------
// intPort2 ( )
// I/O pin interrupt, caused by the tuning wheel or AT keyboard clock
//
#ifdef __IAR_SYSTEMS_ICC__
  #pragma vector=PORT2_VECTOR
    __interrupt void intPort2(void)
#else
  interrupt (PORT2_VECTOR) intPort2(void)
#endif
{
   int inBit;
   
   #ifdef NEW_KBD_FUNCS
   static unsigned char kbdBitcount=0, kbdData=0, risingedge=0;
   static unsigned int  old_sys_ticks = 0;
   #else
   unsigned int  timeout=0;
   unsigned char kbdChar=0, fail=0, i=0;   
   #endif
   
   // which pin caused int?
   if((P2IFG&BIT0)!=0) {
   
      // -- Wheel
   
      // pin 2.0 is already low (generated int)
      // so the 2.1 pin determines which way
      // the wheel was turned:
      //   0=up, 1=down
      inBit = P2IN & BIT1;
      if(inBit!=0 && wheel_counter<32000)
         { wheel_counter += 1; }
      else if(inBit==0 && wheel_counter>-32000)
         { wheel_counter -= 1; }
         
      // reset interrupt flag
      P2IFG &= ~BIT0;
   }

   if ((P2IFG&KBD_CLK)!=0) {

      // -- AT keyboard
      
      // keyboard serial stream:
      //  falling clock edge data in
      //  start bit 0, 8 bit LSB ... MSB, odd parity, stop bit 1
      // 
      //  from scope traces and 
      //  http://www.beyondlogic.org/keyboard/keybrd.htm
      //
      //    (A)      B      C      D      E
      // ----+       +------+      +------+
      // CLK | <int  |      |      |      |         5..25 kHz
      //     +-------+      +------+      +-----...
      //
      // -+ DATA    +----------+
      //  |  0      |       1  |           0
      //  +---------+          +---------------...
      
      // timeout loop: xtal 4MHz/16000=250 Hz (plenty for 5..25kHz AT kbd clock)

      #ifdef NEW_KBD_FUNCS
      if(risingedge==1) {
         // trigged on rising edge (data done), switch back to falling edge trig
         P2IES |= KBD_CLK;
         risingedge=0;
      } else {
         // trigged on falling edge (data in), change to rising edge trig
         P2IES &= ~KBD_CLK;
         risingedge=1;         
            
         // read the bit
         inBit = P2IN & KBD_DAT;
      
   intPort2_kbdRetry:
         // start of new sequence?
         if(kbdBitcount==0) {
         
            // start bit 0
            if(inBit==0) { 
               ++kbdBitcount; 
               kbdData=0; 
            } else { 
               // out of sync, wait for next bit 
               P6OUT |= LED_1;
            }
            
            // continue current sequence: databits, parity, stopbit
            } else {

            // if previous bit over 3 ticks ago, reset sequence
            if((sys_ticks-old_sys_ticks)>20) { 
               kbdBitcount=0;
               kbdData=0;
         //   P6OUT ^= LED_1; // toggle diagnostic LED            
               goto intPort2_kbdRetry; // reinterpret as start bit
            }
            
            // data bits
            if(kbdBitcount<=(1+8)) {
               // LSB comes first, so shift bits in from left side
               kbdData /= 2;
            if(inBit!=0) 
               { kbdData |= 0x80; }
            ++kbdBitcount;
            // parity - ignored
            } else if (kbdBitcount==(1+8+1)) {
               ++kbdBitcount;
            // stop bit 1
            } else {
               if(inBit==0) {
                  // out of sync
                   P6OUT ^= LED_1; // toggle diagnostic LED
                  FWConfig.KBD_failure = 1; 
               } else {
                  if(!(kbdUnreadCount>=(KBD_BUFSIZE-1)))
                     { kbdUnreadCount++; }
                  kbdBufPos=(kbdBufPos+1)%KBD_BUFSIZE;
                  kbdBuf[kbdBufPos] = kbdData;
                  P6OUT &= ~LED_1;
               }
               kbdBitcount = 0;
            }
         }
      }
      old_sys_ticks = sys_ticks;
      #else
      // check start bit 0, cont B (wait for rising edge)
      if((P2IN&KBD_DAT)!=0) fail=1;
      timeout=0; 
      while((P2IN&KBD_CLK)==0 && (timeout++)<KBD_DLY && fail==0) { _NOP(); }
      if(timeout>KBD_DLY-1) fail=1;
   
      // cont C, wait for falling edges, read in 8 bits
      for(i=0;i<8 && fail==0;++i) { // &&fail==0

         // falling edge
         timeout=0; 
         while((P2IN&KBD_CLK)!=0 && (timeout++)<KBD_DLY) { _NOP(); }
         if(timeout>KBD_DLY-1) fail=1;
         
         // data, LSB first MSB last
         kbdChar /= 2;
         if((P2IN&KBD_DAT)!=0) kbdChar+=0x80;
      
         // rising edge
         timeout=0; while((P2IN&KBD_CLK)==0 && (timeout++)<KBD_DLY && fail==0) _NOP(); if(timeout>KBD_DLY-1) fail=1;
      }
   
      // skip parity bit, falling + rising edge
      timeout=0; while((P2IN&KBD_CLK)!=0 && (timeout++)<KBD_DLY && fail==0) _NOP(); if(timeout>KBD_DLY-1) fail=1;
      timeout=0; while((P2IN&KBD_CLK)==0 && (timeout++)<KBD_DLY && fail==0) _NOP(); if(timeout>KBD_DLY-1) fail=1;
   
      // check stop bit 1, falling + rising edge
      timeout=0; while((P2IN&KBD_CLK)!=0 && (timeout++)<KBD_DLY && fail==0) _NOP(); if(timeout>KBD_DLY-1) fail=1;
      if((P2IN&KBD_DAT)==0) fail=1;
      timeout=0; while((P2IN&KBD_CLK)==0 && (timeout++)<KBD_DLY && fail==0) _NOP(); // last rising edge
      
      if(fail==0) {
         if(!(kbdUnreadCount>=(KBD_BUFSIZE-1)))
         { kbdUnreadCount++; }

         kbdBufPos=(kbdBufPos+1)%KBD_BUFSIZE;
         kbdBuf[kbdBufPos] = kbdChar;
      } else {
         // P6OUT |= LED_1; // kbd error led on
         FWConfig.KBD_failure = 1; 
      }
      #endif
      
      // reset interrupt flag
      P2IFG &= ~KBD_CLK;
   }

}


//===================================================================
//
//       KEYBOARD HELPER FUNCTIONS
//

//-------------------------------------------------------------------
// kdbSuspend ( )
// Tell the AT keyboard to momentarily pause sending of any data.
//
void kbdSuspend(void) 
{
  /*
   _DINT();
   P2IES &= ~KBD_CLK;   // int off
   P2DIR |= KBD_CLK;    // clock line as output
   P2OUT &= ~KBD_CLK;   // set line low = keyboard doesn't transmit
   P2IFG &= ~KBD_CLK;   // clear int flag
   _EINT();
  */
   return;
} 

//-------------------------------------------------------------------
// kbdResume ( )
// Allow the AT keyboard to send data. If the keyboard was previously
// suspended and new button press data accumulated in the keyboards
// own memory buffer, it will start sending that data soon.
//
void kbdResume(void) 
{
  /*
   _DINT();
   P2DIR &= ~KBD_CLK;   // clock line as input
   P2IES |= KBD_CLK;    // int on
   P2IFG &= ~KBD_CLK;   // clear int flag
   _EINT();
  */
   return;
}

//-------------------------------------------------------------------
// unsigned char kbdGetChar ( )
// Returns the next character from our keyboard buffer, or 0 if
// the buffer was empty.
//
unsigned char kbdGetChar(void) 
{
   unsigned char tmp;

   if(kbdUnreadCount<=0) return '\0';

   _DINT();

   if(kbdBufPos>KBD_BUFSIZE)
   { kbdBufPos = 0; kbdUnreadCount=1; }

   kbdUnreadCount--;
   tmp = (kbdBufPos-kbdUnreadCount)%KBD_BUFSIZE;
   tmp = kbdBuf[tmp]; 

   _EINT();

   return tmp;
}



//===================================================================
//
//       PC SERIAL COMM HELPER FUNCTIONS
//

//-------------------------------------------------------------------
// PC_writeChar ( unsigned char )
// Queue a new data byte to transmit to the PC.
//
void PC_writeChar(unsigned char out) 
{

   // currently not sending?
   if(pcTxDone==1) {
      // just place the new char into the hardware buffer
      TXBUF1 = out; pcTxUnsentCount=0;
      pcTxDone = 0;
      return;
   }

   // already sending, add to software buffer for sending later
   while(pcTxUnsentCount>=PC_TXBUF) // buffer overflow
      { _NOP(); } // wait for tx interrupt driver to 'free' 1 byte

   _DINT();
   ++pcTxBufPos;              // append byte to the buffer
   pcTxBufPos%=PC_TXBUF;    
   pcTxUnsentCount++;
   pcTxBuf[pcTxBufPos] = out;
   _EINT();

   return;
}

//-------------------------------------------------------------------
// PC_writeString ( char * )
// Write a null-terminated string to the serial port 
//
void PC_writeString(char *str) 
{
   int i;
   for(i=0;i<100 && *(str+i)!='\0';i++)
      { PC_writeChar(*(str+i)); }
   return;
}

//-------------------------------------------------------------------
// PC_writeLine ( char * )
// Write a null-terminated string to the serial port.
// Precedes the string with a # and adds a newline.
//
void PC_writeLine(char *str)
{
   PC_writeString("# ");
   PC_writeString(str);
   PC_writeString((char*)STR_CRLF);
}

//-------------------------------------------------------------------
// unsigned char PC_readChar ( )
// Returns the next character from our serial input buffer, or 0 if
// the buffer was empty.
//
unsigned char PC_readChar(void) 
{
   unsigned char tmp;

   if(pcRxUnreadCount<1) { return 0; }

   _DINT();
   if(pcRxBufPos>PC_RXBUF) { 
      pcRxBufPos = 0; 
      pcRxUnreadCount = 1; 
   }

   do {
      tmp = pcRxBuf[pcRxBufPos];
      --pcRxBufPos; 
      pcRxBufPos%=PC_RXBUF;
      pcRxUnreadCount--;
   } while((tmp==0) && (pcRxUnreadCount>0));
   _EINT();

   return tmp;
}
