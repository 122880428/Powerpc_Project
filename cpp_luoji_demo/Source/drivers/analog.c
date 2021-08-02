#include "YN.h"



/*
函数介绍：AD 电压采样
函数实现：
输入参数：ch-AD通道号， *volts-电压范围（±10V）
返回值：0-OK， 1-ERROR
注意事项：无
*/
void  AnalogIn(unsigned char ch,double *volts)
{
    unsigned short temp;

    if(ch > ANALOGINCH16)
        return;
    
    temp =  *(volatile unsigned short *)(ANALOGINADDR+2*ch);

    *volts = ((short)(temp))/3276.8;
  
}
