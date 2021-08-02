#include "YN.h"

/*
�������ܣ�ת�ٳ�ʼ��
����ʵ�֣��� 0x1 ��ֵ�洢�� FREQENADDR+2*i ָ����ڴ浥Ԫ��
�����������
����ֵ����
ע�������
*/
void FreqInit(void)
{
    unsigned char i;
      
    for(i = 0 ; i <= FREQCH2; i++)
    {
        //�� 0x1 ��ֵ�洢�� FREQENADDR+2*i ָ����ڴ浥Ԫ��
        *(volatile unsigned short *)(FREQENADDR+2*i) = 0x1; 
    }   

    return;             
}

/*
�������ܣ�ת�ٲɼ����
����ʵ�֣��� FREQADDR+2*channel ָ����ڴ浥Ԫ�е�ֵȡ����ֵ�� temp-ת��
���������channel-ת��ͨ����
���ڲ�������
����ֵ��ת��
ע�������
*/
unsigned short FreqIn(unsigned char channel)
{
    unsigned short temp;

    if(channel > FREQCH2)
         return(0);
    
    //�� FREQADDR+2*channel ָ����ڴ浥Ԫ�е�ֵȡ����ֵ�� temp-ת��
    temp = *(volatile unsigned short *)(FREQADDR+2*channel);   
   
    return (temp);     
}


/*
�������ܣ�FPGA������-1us 32bit
����ʵ�֣��� FPGACNTADDR ָ����ڴ浥Ԫ�е�ֵȡ����ֵ�� src.W[1]
         �� FPGACNTADDR+2 ָ����ڴ浥Ԫ�е�ֵȡ����ֵ�� src.W[0]
�����������
���ڲ�������
����ֵ����
ע�������
*/
unsigned long FpgaCntGet(void)
{
    dWordStruc src;    
    
    src.W[1] =  *(volatile unsigned short *)(FPGACNTADDR); 
    src.W[0] = *(volatile unsigned short *)(FPGACNTADDR+2);      
   
    return (src.DW);     
}






