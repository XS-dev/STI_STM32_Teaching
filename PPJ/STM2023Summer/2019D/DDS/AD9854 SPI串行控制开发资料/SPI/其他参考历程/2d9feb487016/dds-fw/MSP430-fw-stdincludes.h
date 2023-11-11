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

#ifndef __MSP430_FW_STDINCLUDES_H_
#define __MSP430_FW_STDINCLUDES_H_

   #include <msp430x14x.h>
   #ifndef __IAR_SYSTEMS_ICC__
      #include <signal.h>
   #endif

   #ifndef setBit
   #define setBit(ucByte, ucBit) (ucByte |= ucBit)
   #define clrBit(ucByte, ucBit) (ucByte &= ~ucBit)
   #endif

   #include "MSP430-fw-dds.h"
   #include "MSP430-fw-interrupts.h"
   #include "MSP430-fw-lcd.h"
   #include "MSP430-fw-console.h"
   #include "MSP430-fw-hamtables.h"
   #include "MSP430-fw-main.h"
   #include "MSP430-fw-memory.h"

   #define FW_VERSION_PC   "Firmware v1.03"
   #define FW_VERSION_LCD  "Mini DDS RX v1.03  "
   #define FW_COPYRIGHT    "(C) 2005 Jan Wagner"

#endif
