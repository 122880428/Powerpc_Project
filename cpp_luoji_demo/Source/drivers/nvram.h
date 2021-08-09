#ifndef __NVRAM__
#define __NVRAM__
//#include <iostream>
//using namespace std;
/*
皇：使用的NVram型号是MR2A16ACYS35，有4Mbit的存储
换算成bit是4*1024*1024=4194304
也就是字节：4194304/8 = 524288
写成十六进制就是0x80000
 */
#define MAX_OFFSET        0x80000 			//皇：地址最大偏移量

#define NVRAM_ADDR        0x83000000		//皇：NVRAM的首地址

//unsigned short   NvramRead(unsigned long offset,unsigned short * val);	/*nvram读*/
unsigned short 	 NvramRead(unsigned long offset);
//皇：现在还只能存储正数，那负数呢？
long   NvramWrite(unsigned long offset,unsigned short val);/*nvram写*/
bool NvramWriteChar(unsigned long offset,unsigned char val);
unsigned char NvramReadChar(unsigned long offset);
#endif