/*
* 文件名称：sbus.h
* 摘 要：sbus串行通信协议驱动
*/
#ifndef _SBUS_H_
#define _SBUS_H_
#include <iostream>
#include <stdlib.h>



typedef struct{
    double pwmper;   /*周期*/ 
    double pwmhi;    /*高电平时间*/	
}ipwm_t;   /*unit = ms*/ 


class Sbus
{
private:
	bool init_flag;	//皇：初始化成功标志。
	unsigned short RC_channels[16];		//这个还只是原始通道值。

	ipwm_t SBUSIN[16];
	void  Sbus_Decode(unsigned char buffer[]);	//皇：解码部分
	void  Sbus_In(void);//皇：将解码之后的数据装载到变量里面
public:
	Sbus(){init_flag = false;}
	void init(void);//皇：初始化串口
	bool run(void);	//皇：用于接收遥控器信号
	
	int GetChannel(int channel);//皇：获取某个通道的值，范围是1100~1900
	void debug_sbus(void);		//皇：打印一些调试信息
};


//extern Sbus _sbus;
#endif