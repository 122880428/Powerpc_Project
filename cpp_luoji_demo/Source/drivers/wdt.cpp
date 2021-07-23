#include "wdt.h"

#define  IPS_CLOCK_FREQ  66666666

void  WDT_Enable(unsigned short val)  /*time =1ms*val  val>1*/
{
   unsigned short swtc;
   unsigned long  value;
      
   swtc=(unsigned short)(1.0*IPS_CLOCK_FREQ/65535/2000*val+0.5);
   value=(unsigned long)((swtc<<16)+0x7);
   WDT.SWCRR.R = value;
   WDT_Lock();
}

void  WDT_Disable(void)
{

    WDT.SWCRR.B.SWEN = 0;
}



void  WDT_Lock(void)
{
   
    WDT.SWSRR.B.WS= 0x556C;
    WDT.SWSRR.B.WS= 0xAA39;           
    
}






