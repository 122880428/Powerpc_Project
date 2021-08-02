#include"gpt.h"


/*
函数介绍：通用定时器使能开启
函数实现：
输入参数：val--定时器响应时间
返回值：无
注意事项：无
*/
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
/*
函数介绍：通用定时器使能关闭
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void  GPT_Disable(void)
{
      GPT.MODE.B.STOP_CONT = 0x0;
      GPT.MODE.B.CE  = 0x0; 

}

/*
函数介绍：通用定时器中断
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void  GPT_InterruptHandler(void)
{
      volatile unsigned long int_temp;

      int_temp = GPT.STATUS.R;      
      GPT.STATUS.R = int_temp;

     /* logMsg("interrupt!\n\r",0,0,0,0,0,0);*/

}

/*
函数介绍：外部中断设置
函数实现：
输入参数：val-中断响应时间
返回值：无
注意事项：无
*/
void    IRQ0_SetDiv(unsigned short val)
{
      unsigned short divider;


      divider = (unsigned short)(((1.0*IRQ0FREQ/val)*2+1)/2);
      *(volatile unsigned short *)(IRQ0DIVADDR) = (divider-1);

}

/*
函数介绍：外部中断使能开启
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void    IRQ0_Enable(void)
{
       *(volatile unsigned short *)(IRQ0ENADDR) = 0x1;
 
}

/*
函数介绍：外部中断使能关闭
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void    IRQ0_Disable(void)
{
       *(volatile unsigned short *)(IRQ0ENADDR) = 0x0;
 
}
/*
函数介绍：外部中断函数
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void  IRQ0_InterruptHandler(void)
{
    /*
      logMsg("interrupt!\n\r",0,0,0,0,0,0); */

}