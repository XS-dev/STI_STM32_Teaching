/* macro for input binary */ 
#define LongToBin(n) ( ((n >> 21) & 0x80) | ((n >> 18) & 0x40) | ((n >> 15) & 0x20) | ((n >> 12) & 0x10) | ((n >> 9) & 0x08) | ((n >> 6) & 0x04) | ((n >> 3) & 0x02) | ((n ) & 0x01) ) 
#define Bin(n) LongToBin(0x##n##l)