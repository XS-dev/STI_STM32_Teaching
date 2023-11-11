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
//  Flash memory related functions, for storing or retreiving
//  a setup (frequency, freq step size, etc).
//
//  The MSP430F149 has 2x128 bytes of "Information Memory" in the
//  address range 01000h - 010FFh, and this area is used to store
//  DC-RX configurations.
//  Note: the compiler and linker should already know without any 
//  extra settings that they shoud not generate code into this 
//  memory area...
//
//===================================================================

#include "MSP430-fw-stdincludes.h"

// Allocation of 0x1000-0x1007F:
//    1 byte   magic word
//    1 byte   (filler, for integer addressing of longlong's)
//    8 bytes  tuning word
//    8 bytes  frequency step/tuning word step
//  110 bytes  (unused data)

#define SYSCFG_TW_START    SYSCONFIG_BASE_A+2 
#define SYSCFG_TW_END      SYSCFG_TW_START+sizeof(unsigned long long)
#define SYSCFG_FS_START    SYSCFG_TW_END
#define SYSCFG_FS_END      SYSCFG_FS_START+sizeof(unsigned long long)

//-------------------------------------------------------------------
// SaveSettings ( )
//
// Store the current user settings like frequency and
// frequency step size, etc.
// 
void SaveSettings(void)
{
   char *cptr;
   unsigned int i;
   
   // disable all interrupts while programming
   _DINT();
   IE1 &= ~(NMIIE+OFIE+WDTIE); // (see MSP430-fw-interrupts.c)
   
   // erase the segment
   Flash_clr((int *)SYSCONFIG_BASE_A);

   // store the currently active tuning word 
   cptr = (char*) &dds_lo_tw;
   i = SYSCFG_TW_START;
   while(i<SYSCFG_TW_END) {
      Flash_wb((char*)i, *cptr);
      ++cptr;
      ++i;
   }
   
   // store the currently active frequency step
   cptr = (char*) &dds_delta;
   i = SYSCFG_FS_START;
   while(i<SYSCFG_FS_END) {
      Flash_wb((char*)i, *cptr);
      ++cptr;
      ++i;
   }
   
   // write magic word
   Flash_wb((char*)SYSCONFIG_BASE_A, SYSCONFIG_MAGIC);
   
   // re-enable interrupts
   IE1 |= NMIIE+OFIE+WDTIE;
   _EINT();
   
   return;
}

//-------------------------------------------------------------------
// unsigned char RestoreSettings ( )
//
// Restore previously saved user settings from the flash memory.
// Returns RESP_OK if restore was successful.
// 
unsigned char RestoreSettings(void)
{
   int i;
   
   // check the magic word
   if(*((char*)SYSCONFIG_BASE_A)!=SYSCONFIG_MAGIC) {
      i = RESP_NACK;
   } else {
      // restore values (copy from Flash to RAM)
      dds_lo_tw = *((unsigned long long *)SYSCFG_TW_START);
      dds_delta = *((unsigned long long *)SYSCFG_FS_START);
      // TODO: add bounds checks for TW and Delta...
      i = RESP_OK;
   }
   return i;
}


//===================================================================
//
//       FLASH MEMORY REPROGRAMMING (MSP430F149 only)
//
// Functions were copied from TI's application report SLAA103
// http://www.gaw.ru/pdf/TI/app/msp430/slaa103.pdf

/************************************************************************/
/* Flash_wb                                                             */
/* programs 1 byte (8 bit) into the flash memory                        */
/************************************************************************/
void Flash_wb( char *Data_ptr, char byte )
{
   FCTL3 = 0x0A500;  /* Lock = 0 */
   FCTL1 = 0x0A540;  /* WRT = 1 */
   *Data_ptr=byte;   /* program Flash word */
   FCTL1 = 0x0A500;  /* WRT = 0 */
   FCTL3 = 0x0A510;  /* Lock = 1 */
}
/************************************************************************/
/* Flash_ww                                                             */
/* programs 1 word (16 bits) into the flash memory                      */
/************************************************************************/
void Flash_ww( int *Data_ptr, int word )
{
   FCTL3 = 0x0A500;  /* Lock = 0 */
   FCTL1 = 0x0A540;  /* WRT = 1 */
   *Data_ptr=word;   /* program Flash word */
   FCTL1 = 0x0A500;  /* WRT = 0 */
   FCTL3 = 0x0A510;  /* Lock = 1 */
}
/************************************************************************/
/* Flash_clr                                                            */
/* erases 1 Segment of flash memory                                     */
/************************************************************************/
void Flash_clr( int *Data_ptr )
{
   FCTL3 = 0x0A500;  /* Lock = 0 */
   FCTL1 = 0x0A502;  /* ERASE = 1 */
   *Data_ptr=0;      /* erase Flash segment */
   FCTL1 = 0x0A500;  /* ERASE = 0 */
   FCTL3 = 0x0A510;  /* Lock = 1 */
}
