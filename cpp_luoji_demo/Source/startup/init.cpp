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
	
	
	// PPC_ComInit(COM1,115200,COM_PARITY_NONE,1,RS232);
    PPC_ComInit(COM2,115200,COM_PARITY_NONE,1,RS232);
    
    //PPC_ComEnableInterrupt(COM1);
    PPC_ComEnableInterrupt(COM2);
	
  	//皇：串口的初始化设置
    FComSetIOBase();
    //皇：串口的初始化可以选择是232模式还是422模式。
    FComInit(FCOM1,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM2,115200,COM_PARITY_NONE,1,64,RS232);	//gcs
    FComInit(FCOM3,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM4,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM5,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM6,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM7,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM8,115200,COM_PARITY_NONE,1,64,RS232);
    //FComInit(FCOM9,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM9,100000,COM_PARITY_EVEN,2,8,RS232);
	
	
	//皇：can总线相关内容
	
	InitMsCAN(CAN_CHANNAL1,CAN_1Mbps);
    InitMsCAN(CAN_CHANNAL2,CAN_1Mbps);
    InitMsCAN(CAN_CHANNAL3,CAN_1Mbps);
    InitMsCAN(CAN_CHANNAL4,CAN_1Mbps); 
    
    MsCANIntInit(CAN_CHANNAL1,CAN_BASE_FRAME);
    MsCANIntInit(CAN_CHANNAL2,CAN_BASE_FRAME);
    MsCANIntInit(CAN_CHANNAL3,CAN_BASE_FRAME);
    MsCANIntInit(CAN_CHANNAL4,CAN_BASE_FRAME);  
	
	
    
    IRQ0_Disable();
    IRQ0_SetDiv(IRQ0DIVFREQ);
    
    FreqInit();
    PwmInit();
    
    intInit();
    IRQ0_Enable(); 
    /* GPT_Enable(1000); */
   
    time_init();  		//定时器初始化
    time_enable();		//打开定时器中断，这个中断打开之后才能使用任务调度
    
    int_enable();		//打开中断总开关
    printf("init OK!\n\r");
}
    
#endif    