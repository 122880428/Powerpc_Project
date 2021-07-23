#include "yn.h"


pwm_t   PWMOUT[18];

void PwmInit(void)
{
    unsigned char i;
    dWordStruc src;
    unsigned short divider;
   
    for(i = 0 ; i <= PWMOUTCH18; i++)
    {
        PWMOUT[i].pwmhi = 10.0;
   	PWMOUT[i].pwmper = 20.0; 
    }

    *(volatile unsigned short *)(PWMOUTCLKENADDR) = 0x0;
    divider = (unsigned short)(((1.0*PWMFREQ/PWMDIVFREQ)*2+1)/2);
    *(volatile unsigned short *)(PWMOUTFREQADDR) = (divider-1);
    *(volatile unsigned short *)(PWMOUTCLKENADDR) = 0x1;

     
    for(i = 0 ; i <= PWMOUTCH18; i++)
    {
        src.DW = (unsigned long)(PWMOUT[i].pwmper/1000.0*PWMDIVFREQ+0.5);  
        *(volatile unsigned short *)(PWMOUTPERADDR+4*i) = src.W[1];  
        *(volatile unsigned short *)(PWMOUTPERADDR+4*i+2) = src.W[0];

        src.DW = (unsigned long)(PWMOUT[i].pwmhi/1000.0*PWMDIVFREQ+0.5);
       
        *(volatile unsigned short *)(PWMOUTHIGHADDR+4*i) = src.W[1];   
        *(volatile unsigned short *)(PWMOUTHIGHADDR+4*i+2) = src.W[0]; 
      
        *(volatile unsigned short *)(PWMOUTENADDR+2*i) = 0x1; 
    } 

    return;             
}

void PwmHighOut(unsigned char channel)
{
     dWordStruc src;
    
    if(channel > PWMOUTCH18)
	    return;
    
    if(PWMOUT[channel].pwmper<0.01)
        return;  

     src.DW = (unsigned long)(PWMOUT[channel].pwmhi/1000.0*PWMDIVFREQ+0.5);
     *(volatile unsigned short *)(PWMOUTHIGHADDR+4*channel) = src.W[1]; 
     *(volatile unsigned short *)(PWMOUTHIGHADDR+4*channel+2) = src.W[0];    

     return;
	
}

void PwmPerOut(unsigned char channel)
{
     dWordStruc src;
    
    if(channel > PWMOUTCH18)
	    return;
    
    if(PWMOUT[channel].pwmper<0.01)
        return;  

     src.DW = (unsigned long)(PWMOUT[channel].pwmper/1000.0*PWMDIVFREQ+0.5);
     *(volatile unsigned short *)(PWMOUTPERADDR+4*channel) = src.W[1]; 
     *(volatile unsigned short *)(PWMOUTPERADDR+4*channel+2) = src.W[0];   
 
     return;
	
}



