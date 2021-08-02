//////////////////////////
//	Project Stationery  //
//////////////////////////
#include "YN.H"
#include "..\drivers\gcs.h"
#include "test.h"
#include <iostream.h>
#include "..\dynamics\quadrotor.h"
#include <vector>
#include "drivers\sbus.h"
#include "sbus.h"
/*
* 函数介绍：主函数入口处
* 函数实现：无
* 输入参数：无
* 返回值  ：无
* 注意事项：变量的声明一定要放到函数的最前面，这个编译器要求比较严格
*/


void main()
{
    extern Gcs _gcs;

    unsigned char i = 0;
    unsigned long kk = 0,tt =0;
    unsigned long  cnt = 50; 

    unsigned short val = 10000;
    extern Sbus _sbus;
    Quadrotor _quadrotor;

    
	//皇：内存对齐测试
   /* __declspec(align(8)) double d1=300;
	printf("dl is %f\r\n",d1);
	__attribute__((aligned(16))) double jet=25;
	printf("jet is %f\r\n",jet);*/

    Sys_Init();     //系统初始化 
    _sbus.init();   //sbus初始化
    _gcs.init();    //gcs初始化

    //皇：测试Eigen数学库是否可用。
    //test_Eigen();
    
//开始任务
while (1) 
{

//皇：通过计时器实现定时调用
 if (tag_1ms) 		//1000Hz任务
{   
    tag_1ms = 0;	//结束处一定要记得把tag置0，它会在定时器中断里面进行赋值
}

if (tag_5ms)		//200Hz任务
{
 tag_5ms = 0;
}    


if (tag_10ms) 		//100Hz任务
{   
    
	 //皇：串口功能测试
	//test_com(); 
    tag_10ms = 0; 
}

if (tag_14ms) 		//Hz任务
{   
    _sbus.run(); 
    tag_14ms = 0; 
}

if (tag_20ms)		//50Hz任务
{
    tag_20ms = 0;
}    

if(tag_50ms)		//20Hz任务
{

    _gcs.run();
    tag_50ms = 0;
}

if (tag_100ms) 		//10Hz任务
{   

    tag_100ms = 0;     
}

if (tag_500ms)		//2Hz任务
{
    _quadrotor.test_quadrotor_dynamics();
 tag_500ms = 0;           			  
} 

if(tag_1s == 1)		//1Hz任务
{
 tag_1s = 0;
}

if (tag_2s)			//0.5Hz任务
{
//皇：用来检测c++编译器的版本，结果是c++98的标准
//printf("_cplusplus:%d\r\n",__cplusplus);

_quadrotor.debug_printf();
_sbus.debug_sbus();

printf("program is running...!\r\n");
tag_2s = 0;       			  
}//endif	  
}//end while
}//end main
