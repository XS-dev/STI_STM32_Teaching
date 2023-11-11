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
//  a setup (frequency, freq step size, etc)
//
//===================================================================

#ifndef __MSP430_FW_MEMORY_H
#define  __MSP430_FW_MEMORY_H

#include "MSP430-fw-stdincludes.h"

void           Flash_wb (char *Data_ptr, char byte);
void           Flash_ww (int *Data_ptr, int word);
void           Flash_clr (int *Data_ptr);

void           SaveSettings (void);
unsigned char  RestoreSettings (void);

#define SYSCONFIG_MAGIC    0x7C     // magic word, to check if memory 
                                    // does hold a valid config
#define SYSCONFIG_BASE_A   0x1000   // starting address in Flash, segment A
#define SYSCONFIG_BASE_B   0x1080   // -"- B

#endif
