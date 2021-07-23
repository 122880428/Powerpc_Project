#ifndef _SBUS_H_
#define _SBUS_H_

typedef struct{
    double pwmper;   /*����*/ 
    double pwmhi;    /*�ߵ�ƽʱ��*/	
}ipwm_t;   /*unit = ms*/ 


extern ipwm_t SBUSIN[16];//extern 表示变量或者函数的定义在别的文件中


void  SBUS_Rev(void);//SBUS接收函数
void  SBUS_Decode(unsigned char buffer[]);//SBUS解码函数
int   GetChannel(int channel);//获取SBUS通道号
void  SBUS_IN(void);//获取SBUS通道的高电平





#endif