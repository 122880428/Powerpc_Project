//#include "YN.h"

#include "nvram.h"
/*unsigned short NvramRead(unsigned long offset,unsigned short * val)
{
    if(offset>MAX_OFFSET)
         return(-1);
    *val = *(volatile unsigned short *)(NVRAM_ADDR+offset);
    return(0);	
}*/

unsigned short NvramRead(unsigned long offset)
{
    if(offset>MAX_OFFSET)
         return(-1);
    return(*(volatile unsigned short *)(NVRAM_ADDR+offset)); 	
}

//unsigned short是占用两个字节，这里需要确认一下它是不是一次写入两个字节
long NvramWrite(unsigned long offset,unsigned short val)
{
   if(offset>MAX_OFFSET)
         return(-1);
    *(volatile unsigned short *)(NVRAM_ADDR+offset) = val;
    
    return(0);
}

bool NvramWriteChar(unsigned long offset,unsigned char val)
{
   if(offset>MAX_OFFSET)
         return false;
    *(volatile unsigned char *)(NVRAM_ADDR+offset) = val;
    
    return true;
}
unsigned char NvramReadChar(unsigned long offset)
{
    if(offset>MAX_OFFSET)
         return(-1);
    return(*(volatile unsigned char *)(NVRAM_ADDR+offset));    
}