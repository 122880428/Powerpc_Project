#include "YN.h"



/*
�������ܣ�AD ��ѹ����
����ʵ�֣�
���������ch-ADͨ���ţ� *volts-��ѹ��Χ����10V��
����ֵ��0-OK�� 1-ERROR
ע�������
*/
void  AnalogIn(unsigned char ch,double *volts)
{
    unsigned short temp;

    if(ch > ANALOGINCH16)
        return;
    
    temp =  *(volatile unsigned short *)(ANALOGINADDR+2*ch);

    *volts = ((short)(temp))/3276.8;
  
}
