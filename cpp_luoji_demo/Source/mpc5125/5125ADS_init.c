/*
* 文件名称：5125ADS_init.c
* 摘 要：定义了一些与系统初始化相关的内容
* 
* 当前版本：1.0
* 作 者：皇陆亚18439432431
* 完成日期：2021 年 7 月 14 日
* 修改内容：增加了函数注释，添加了cpp的条件编译，移植到了c++工程中 
*
*/

//皇：不太清楚这一段代码的作用
#pragma section code_type ".init"

//皇：使用c的语法来编译这几个函数。
#ifdef __cplusplus
extern "C" {
#endif

asm void __reset(void);		//复位
asm void usr_init();		//初始化
extern void __start();		//函数在mpc5125\_start.c文件里面
//皇：这两个变量没有找到在哪里定义的。
extern unsigned long gInterruptVectorTable;
extern unsigned long gInterruptVectorTableEnd;

#ifdef __cplusplus
}
#endif


/*
* 函数介绍：复位
* 函数实现：看着像是开机启动的时候先进行各项复位
* 输入参数：无
* 返回值  ：无
* 注意事项：无
*/
asm void __reset(void)
{
	//
	//   Enable machine check exceptions & floating point
	//
	lis		r3, 0x0000
	ori		r3, r3, 0x3000
	mtmsr	r3
		
	b		__start
} 

/*
* 函数介绍：用户初始化
* 函数实现：函数现在还为空
* 输入参数：无
* 返回值  ：无
* 注意事项：在_ppc_eabi_init.c的__init_hardware函数里面调用了
*/
asm void usr_init()
{

}
