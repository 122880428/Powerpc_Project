#include"yn.h"

/*
函数介绍：开关量输出
函数实现：
输入参数：channel-IO输出通道号， level-输出电平值（“1”或”0”）
返回值：无
注意事项：无
*/
void DigitalOut(unsigned char channel,unsigned short level)
{
    
     if(channel > DO8)
         return;
     
     *(volatile unsigned short *)(DOADDR+2*channel) = level;

}

/*
函数介绍：开关量输入
函数实现：
输入参数：channel--IO输入通道号
返回值：temp-输出
注意事项：无
*/
unsigned short DigitalIn(unsigned char channel)
{
    unsigned short temp;

    if(channel > DI8)
         return(0);
    
    temp = *(volatile unsigned short *)(DIADDR+2*channel);   
   
    return (temp);     
}








