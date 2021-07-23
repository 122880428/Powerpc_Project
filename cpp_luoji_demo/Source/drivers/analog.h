#ifndef __ANALOG__
#define __ANALOG__

#include "YN.h"


#define ANALOGINADDR     0x8400C000

#define ANALOGINCH1      0     
#define ANALOGINCH2      1    
#define ANALOGINCH3      2     
#define ANALOGINCH4      3 
#define ANALOGINCH5      4     
#define ANALOGINCH6      5    
#define ANALOGINCH7      6     
#define ANALOGINCH8      7 
#define ANALOGINCH9      8     
#define ANALOGINCH10     9    
#define ANALOGINCH11     10     
#define ANALOGINCH12     11
#define ANALOGINCH13     12     
#define ANALOGINCH14     13    
#define ANALOGINCH15     14     
#define ANALOGINCH16     15 

#if defined(_cplusplus)
extern "C"
{
#endif

void  AnalogIn(unsigned char ch,double *volts);//AD 电压采样

#ifdef _cplusplus
}
#endif

#endif