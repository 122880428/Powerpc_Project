#include "time.h"

//皇：用于实现任务调度而定义的一些变量
unsigned long    timetick=1;    
unsigned char    tag_200us;
unsigned char    tag_1ms;
unsigned char    tag_5ms;
unsigned char    tag_10ms;
unsigned char    tag_20ms;
unsigned char    tag_40ms;
unsigned char    tag_50ms;
unsigned char    tag_80ms;
unsigned char    tag_100ms;
unsigned char    tag_125ms;
unsigned char    tag_200ms;
unsigned char    tag_500ms;
unsigned char    tag_600ms;
unsigned char    tag_1s;
unsigned char    tag_2s;
unsigned short   CPULoad;
unsigned short   IdleCount=1L;




/****************************************************************************
* 名称：time_init
* 功能：定时器初始化
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：在系统初始化的时候被调用
****************************************************************************/ 
asm void time_init(void) {
  lis		r4, 0x0000		/* Load initial DEC value of 49500  1ms*/
  ori		r4, r4, 0xC15B
  mtdec		r4

}

/*
* 函数介绍：清除定时器中断标志
* 函数实现：无
* 输入参数：无
* 返回值  ：无
* 注意事项：进入到定时器中断之后要及时重置中断标志位
*/
asm void clr_time_flag(void) {
  lis		r4, 0x0000		/* Load initial DEC value of 49500  1ms*/
  ori		r4, r4, 0xC15B
  mtdec		r4
}



/****************************************************************************
* 名称：time_isr
* 功能：定时器中断函数
* 入口参数：无
* 出口参数：无
* 返回值：无
* 备注：触发定时器中断之后会进入到这个函数中
****************************************************************************/ 
	
void time_isr (void)
{

   clr_time_flag();			//清除中断标志位
   timetick=(timetick+1)%(5000*60); 
   tag_1ms   = 1;
   
                           
    if ((timetick % 5 ) == 0)   tag_5ms  = 1;                          
	if ((timetick % 10 ) == 0)	tag_10ms  = 1;
	if ((timetick % 20 ) == 0)	tag_20ms  = 1;
	if ((timetick % 40  ) == 0)	tag_40ms  = 1;
	if ((timetick % 50 ) == 0)	tag_50ms  = 1;
	if ((timetick % 80 ) == 0)	tag_80ms  = 1;
	if ((timetick % 100 ) == 0)	tag_100ms = 1;
	if ((timetick % 125 ) == 0)	tag_125ms = 1;
	if ((timetick % 200 ) == 0)	tag_200ms = 1;
	if ((timetick % 500) == 0) 
	{ 
	tag_500ms = 1; 
	CPULoad=(unsigned short)(50000L/IdleCount); 	//皇：这里不清楚为什么要多加了这样两句。
	IdleCount=1; 
	} 
    if ((timetick % 600) == 0)   tag_600ms = 1;
	if ((timetick % 1000) == 0){ tag_1s    = 1;}
	if ((timetick % 2000) == 0)	tag_2s    = 1;      
	
    
}
