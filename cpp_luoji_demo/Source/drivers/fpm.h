#ifndef _FPM_H
#define _FPM_H

#define  FREQADDR     0x8400E000
#define  FREQENADDR   0x8400E100
#define  FPGACNTADDR  0x84010100
#define  IRQENADDR    0x84010000 
#define  IRQCNT       0x84010002

#define  FREQCH1      0
#define  FREQCH2      1


void FreqInit(void);//转速初始化
unsigned short FreqIn(unsigned char channel); //转速采集入口
unsigned long  FpgaCntGet(void);//FPGA计数器-1us 32bit


#endif

