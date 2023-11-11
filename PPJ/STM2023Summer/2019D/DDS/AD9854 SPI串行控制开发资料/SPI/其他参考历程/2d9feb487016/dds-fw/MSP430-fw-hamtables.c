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
//  Radio amateur band tables up to and
//  including the 6m band
//
//  !!freq allocations for Finland!!
//

#include "MSP430-fw-stdincludes.h"

#define BAND_COUNT 10
const unsigned char bandlistMetres[BAND_COUNT] =
   {  160,   80,   40,    30,    20,    17,    15,    12,    10,     6 };
const unsigned int bandlistLower_kHz[BAND_COUNT] =
   { 1810, 3500, 7000, 10100, 14000, 18068, 21000, 24890, 28000, 50000 };
const unsigned int bandlistUpper_kHz[BAND_COUNT] =
   { 2000, 3800, 7100, 10150, 14350, 18168, 21450, 24990, 29700, 52000 };

const char* STR_BU_HAM = "ham";
const char* STR_BU_CIV = "civ";

   
//-------------------------------------------------------------------
// char* getBandUse ( unsigned long )
//
// Return band use/allocation info, "ham" for amateur
// bands and "civ" for civilian, commercial, military, etc
//
const char *getBandUse(unsigned int freqkHz) 
{
   int i;
   for(i=0;i<BAND_COUNT;i++) {
      if(freqkHz>=bandlistLower_kHz[i] 
         && freqkHz<=bandlistUpper_kHz[i]) 
      {
         return STR_BU_HAM;
      }
  }
  return STR_BU_CIV;
}


//-------------------------------------------------------------------
// unsigned char getBandMetres ( unsigned long )
//
// Convert frequency to ham band "metres" notation,
// if it is an amateur band
//
unsigned char getBandMetres(unsigned int freqkHz) 
{
   int i;
   for(i=0;i<BAND_COUNT;i++) {
      if(freqkHz>=bandlistLower_kHz[i] 
         && freqkHz<=bandlistUpper_kHz[i]) 
      {
         return bandlistMetres[i];
      }
  }
  return 0;
}


//-------------------------------------------------------------------
// unsigned long getBandFreqkHz ( unsigned char )
//
// Return starting frequency i.e. lowest frequency of the 
// specified amateur band
//
unsigned int getBandFreqkHz(unsigned char band) 
{
   int i;
   for(i=0;i<BAND_COUNT;i++) {
      if(band==bandlistMetres[i]) {
         return bandlistLower_kHz[i];
      }
  }
  return 0;
}
