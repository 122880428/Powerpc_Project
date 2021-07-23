#ifndef __NVRAM__
#define __NVRAM__

#define MAX_OFFSET        0x80000

#define NVRAM_ADDR        0x83000000

long   NvramRead(unsigned long offset,unsigned short * val);
long   NvramWrite(unsigned long offset,unsigned short val);


#endif