#include "YN.h"


long NvramRead(unsigned long offset,unsigned short * val)
{
    if(offset>MAX_OFFSET)
         return(-1);
    *val = *(volatile unsigned short *)(NVRAM_ADDR+offset);
    return(0);	
}



long NvramWrite(unsigned long offset,unsigned short val)
{
   if(offset>MAX_OFFSET)
         return(-1);
    *(volatile unsigned short *)(NVRAM_ADDR+offset) = val;
    
    return(0);
	
}

