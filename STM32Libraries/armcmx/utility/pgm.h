#ifndef _PGM_H_
#define _PGM_H_

#define PROGMEM 
#define FLASHSTRING PGM_P
typedef const char* PGM_P;
typedef unsigned char prog_uchar;

#define pgm_read_byte(ptr)  (*(ptr))

#endif
