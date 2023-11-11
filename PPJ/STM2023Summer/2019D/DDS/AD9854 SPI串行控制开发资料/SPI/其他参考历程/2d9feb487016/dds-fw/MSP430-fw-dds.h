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
// port 4: 8 bit data and 
//         5 bit address through 74hc573 latch
// port 5: 5.0 RST, 5.1 !RD, 5.2 !WR, 5.3 IOCLK, 
//         5.4 ALE, 
//         not yet used : 5.5 FSK/MOD, 5.6 KEYING 

#ifndef __MSP430_FW_DDS_H
#define __MSP430_FW_DDS_H

#include <msp430x14x.h>

// DDS data and address bus (multiplexed with DDS_ALE)
#define DDS_DATA_OUT P5OUT
#define DDS_DATA_IN  P5IN
#define DDS_DATA_DIR P5DIR

// DDS control lines
#define DDS_CTRL_OUT P4OUT
#define DDS_CTRL_DIR P4DIR
#define DDS_CTRL_IN  P4IN

// DDS control line functions (pin x = BITx)
#define DDS_ALE   BIT7
#define DDS_NWR   BIT6
#define DDS_NRD   BIT5
#define DDS_RST   BIT4
#define DDS_MOD   BIT3
#define DDS_KEY   BIT2
#define DDS_CLK   BIT1

/*
!!!final corrected PCB design!!!
// DDS control line functions (pin x = BITx)
#define DDS_ALE   BIT7
#define DDS_CLK   BIT6
#define DDS_NWR   BIT5
#define DDS_NRD   BIT4
#define DDS_MOD   BIT3
#define DDS_KEY   BIT2
#define DDS_RST   BIT1
*/

#define DDS_MODE_TONE     0   // b%000
#define DDS_MODE_FSK      1   // b%001 
#define DDS_MODE_RAMPFSK  2   // b%010
#define DDS_MODE_CHIRP    3   // b%011
#define DDS_MODE_BPSK     4   // b%100

#define DDS_MULTIPLIER    4   // PLL multiplier 
#define DDS_REFCLK_MHZ    50  // base clock, external, 50MHz
#define DDS_MAXFREQ_MHZ   50  // limit to output freq (selectable, but <1/3 multiplier*refclk)

#define DDS_1HZ_STEP (long long)(0x15798E)               // tw = 1 Hz * (2^48)/(multiplier*refclk) = 2^48/200E6 = 1407374,88 ~= 0x15798E
#define SCAN_LIM_LO  (unsigned long long)0x08637BD0      // 100 Hz low limit
#define SCAN_LIM_HI  (unsigned long long)0x466666660000  // 55 MHz high limit
#define WHEEL_DIV_RESO 1   // divider for the tuning wheel resolution (depends
                           //   on the stepper motor used)
#define DEFAULT_DELTA (long long)(0x000029F16B11)  // 500 Hz default per step
#define DEFAULT_LO_TW (long long)(0x01EB851E0000)  // 1.500 MHz default freq

extern volatile unsigned long long  dds_delta;        // freq step
extern volatile unsigned long long  dds_lo_tw;        // current frequency register
extern volatile signed int          dds_wheeldivider; // wheel de-sensitizer counter/divider

void           DDS_init (void);
unsigned char  DDS_readByte (unsigned char addr);
void           DDS_writeByte (unsigned char data, unsigned char addr);
void           DDS_writeLongTuningword (long long tw);
void           DDS_commit (void);

void           DDS_manualscan (void); // test function 1
void           DDS_autoscan1 (void); // debug func 2
void           DDS_Smeter (unsigned char s);
unsigned long DDS_Tuningword2Freq (long long tuningword);
char*          DDS_Tuningword2FreqStr (long long tuningword, char LCDformat);

#endif
