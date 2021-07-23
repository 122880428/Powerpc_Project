/*
* 文件名称：init.h
* 摘 要：完成各个外设和板载资源的初始化
* 
* 当前版本：1.0
* 作 者：皇陆亚18439432431
* 完成日期：2021 年 7 月 14 日
* 修改内容：增加了函数注释，规范了一些代码，刚移植到c++，把用不到的函数先删除了。 
*
*/



#ifndef INIT_H
#define INIT_H

#include "YN.h"

/*
* 函数介绍：系统初始化
* 函数实现：完成各个外设和板载资源的初始化
* 输入参数：无
* 返回值  ：无
* 注意事项：无
*/
void  Sys_Init(void)
{
 	printf("initing...!\n\r");
    mmu_cache_init(); 			//memory management unit内存管理单元初始化
    int_disable(); 				//打开中断总开关   
    WDT_Disable();      		//打开看门狗
	
  	//皇：串口的初始化设置
    FComSetIOBase();
    FComInit(FCOM1,921600,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM2,921600,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM3,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM4,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM5,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM6,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM7,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM8,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM9,115200,COM_PARITY_NONE,1,64,RS422);


    /*IRQ0_Disable();
    IRQ0_SetDiv(IRQ0DIVFREQ);
    
    FreqInit();
    PwmInit();
    intInit();
    IRQ0_Enable(); */
    /* GPT_Enable(1000); */
   
    time_init();  		//定时器初始化
    time_enable();
    printf("time_enable...!\n\r");
    int_enable();
    printf("init ok!!\n\r");
}
    
#endif    