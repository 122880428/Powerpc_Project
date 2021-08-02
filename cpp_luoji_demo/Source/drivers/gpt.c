#include"gpt.h"


void    GPT_Enable(unsigned short val)
{
       
      unsigned short  counter;
      unsigned short  frescale;
      
      frescale = 0x1a09;  

      GPT.COUNTER.B.PRESCALE = frescale;
      
      counter = (unsigned short)(1.0*IPS_CLOCK_FREQ/frescale/1000*val);

      GPT.COUNTER.B.COUNT = counter;

      GPT.MODE.B.TIMER_MS = 0x4;

      GPT.MODE.B.INTEN =0x1;

      GPT.MODE.B.CE = 0x1;
      GPT.MODE.B.STOP_CONT = 0x1;
      
}

void  GPT_Disable(void)
{
      GPT.MODE.B.STOP_CONT = 0x0;
      GPT.MODE.B.CE  = 0x0; 

}


void  GPT_InterruptHandler(void)
{
      volatile unsigned long int_temp;

      int_temp = GPT.STATUS.R;      
      GPT.STATUS.R = int_temp;

     /* logMsg("interrupt!\n\r",0,0,0,0,0,0);*/

}


void    IRQ0_SetDiv(unsigned short val)
{
      unsigned short divider;


      divider = (unsigned short)(((1.0*IRQ0FREQ/val)*2+1)/2);
      *(volatile unsigned short *)(IRQ0DIVADDR) = (divider-1);

}

void    IRQ0_Enable(void)
{
       *(volatile unsigned short *)(IRQ0ENADDR) = 0x1;
 
}


void    IRQ0_Disable(void)
{
       *(volatile unsigned short *)(IRQ0ENADDR) = 0x0;
 
}

void  IRQ0_InterruptHandler(void)
{
    /*
      logMsg("interrupt!\n\r",0,0,0,0,0,0); */

}