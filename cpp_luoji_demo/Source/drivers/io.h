#ifndef __IO__
#define __IO__

#define  DOADDR  0x84008000
#define  DIADDR  0x84008000

#define  DO1      0
#define  DO2      1
#define  DO3      2 
#define  DO4      3  
#define  DO5      4 
#define  DO6      5  
#define  DO7      6
#define  DO8      7


#define  DI1      0    /*5~30V*/
#define  DI2      1    /*5~30V*/
#define  DI3      2    /*5~30V*/
#define  DI4      3    /*5~30V*/
#define  DI5      4    /*5~30V*/
#define  DI6      5    /*5~30V*/
#define  DI7      6    /*5~30V*/
#define  DI8      7    /*5~30V*/


#define  HIGHLEVEL   0x1
#define  LOWEVEL     0x0

void DigitalOut(unsigned char channel,unsigned short level); //开关量输出
unsigned short DigitalIn(unsigned char channel);//开关量输入

#endif