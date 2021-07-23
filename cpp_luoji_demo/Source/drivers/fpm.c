#include "YN.h"

/*
函数介绍：转速初始化
函数实现：将 0x1 赋值存储到 FREQENADDR+2*i 指向的内存单元中
输入参数：无
返回值：无
注意事项：无
*/
void FreqInit(void)
{
    unsigned char i;
      
    for(i = 0 ; i <= FREQCH2; i++)
    {
        //将 0x1 赋值存储到 FREQENADDR+2*i 指向的内存单元中
        *(volatile unsigned short *)(FREQENADDR+2*i) = 0x1; 
    }   

    return;             
}

/*
函数介绍：转速采集入口
函数实现：将 FREQADDR+2*channel 指向的内存单元中的值取出赋值给 temp-转速
输入参数：channel-转速通道号
出口参数：无
返回值：转速
注意事项：无
*/
unsigned short FreqIn(unsigned char channel)
{
    unsigned short temp;

    if(channel > FREQCH2)
         return(0);
    
    //将 FREQADDR+2*channel 指向的内存单元中的值取出赋值给 temp-转速
    temp = *(volatile unsigned short *)(FREQADDR+2*channel);   
   
    return (temp);     
}


/*
函数介绍：FPGA计数器-1us 32bit
函数实现：将 FPGACNTADDR 指向的内存单元中的值取出赋值给 src.W[1]
         将 FPGACNTADDR+2 指向的内存单元中的值取出赋值给 src.W[0]
输入参数：无
出口参数：无
返回值：无
注意事项：无
*/
unsigned long FpgaCntGet(void)
{
    dWordStruc src;    
    
    src.W[1] =  *(volatile unsigned short *)(FPGACNTADDR); 
    src.W[0] = *(volatile unsigned short *)(FPGACNTADDR+2);      
   
    return (src.DW);     
}






