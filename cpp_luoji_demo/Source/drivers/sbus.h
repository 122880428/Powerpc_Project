/*
* 文件名称：sbus.h
* 摘 要：sbus串行通信协议驱动
*/
#ifndef _SBUS_H_
#define _SBUS_H_
#include <iostream>
#include <stdlib.h>
#include "..\libraries\AP_Param\AP_Param.h"


typedef struct{
    double pwmper;   /*周期*/ 
    double pwmhi;    /*高电平时间*/	
}ipwm_t;   /*unit = ms*/ 


class Sbus
{

private:
	friend void AP_Param_init(void);
	bool init_flag;	//皇：初始化成功标志。
	bool _calculate_flag;	//皇：进入校准程序的标志
	unsigned short RC_channels[16];		//这个还只是原始通道值。
	unsigned short _last_rc_channels[16];
	unsigned char sbus_flag;
	bool failsafe_flag;

	
	ipwm_t SBUSIN[16];
	void  Sbus_Decode(unsigned char buffer[]);	//皇：解码部分
	void  Sbus_In(void);//皇：将解码之后的数据装载到变量里面
public:
	AP_Int16  _RC_max[16];		//这里用1100~1900左右的值
	AP_Int16  _RC_min[16];
	

	Sbus(){
		printf("sbus is construct\r\n");
		init_flag = false;_calculate_flag = false;sbus_flag = 0;failsafe_flag = true;}
	void init(void);//皇：初始化串口
	bool run(void);	//皇：用于接收遥控器信号
	
	int GetChannel(int channel);//皇：获取某个通道的值，范围是1100~1900
	int GetLastChannel(int channel);//皇：获取某个通道的值，范围是1100~1900
	void debug_sbus(void);		//皇：打印一些调试信息
	void RC_calculate(void);	//皇：遥控器校准
	void RC_calc_monitor(void);		//监视遥控器数据，判断校准标志是否置true
	void RC_save_cal_val(void);		//保存记录的最大最小值
	uint16_t Get_Scaled_Channel(uint8_t channel);
	void RC_channels_reset(void);
	bool failsafe(void){return failsafe_flag;}
};


//extern Sbus _sbus;
#endif
