#include "YN.h"


void FreqInit(void)
{
    unsigned char i;
      
    for(i = 0 ; i <= FREQCH2; i++)
    {
        *(volatile unsigned short *)(FREQENADDR+2*i) = 0x1; 
    }   

    return;             
}


unsigned short FreqIn(unsigned char channel)
{
    unsigned short temp;

    if(channel > FREQCH2)
         return(0);
    
    temp = *(volatile unsigned short *)(FREQADDR+2*channel);   
   
    return (temp);     
}



unsigned long FpgaCntGet(void)
{
    dWordStruc src;    
    
    src.W[1] =  *(volatile unsigned short *)(FPGACNTADDR); 
    src.W[0] = *(volatile unsigned short *)(FPGACNTADDR+2);      
   
    return (src.DW);     
}






