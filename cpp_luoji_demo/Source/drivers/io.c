#include"yn.h"

/*
�������ܣ����������
����ʵ�֣�
���������channel-IO���ͨ���ţ� level-�����ƽֵ����1����0����
����ֵ����
ע�������
*/
void DigitalOut(unsigned char channel,unsigned short level)
{
    
     if(channel > DO8)
         return;
     
     *(volatile unsigned short *)(DOADDR+2*channel) = level;

}

/*
�������ܣ�����������
����ʵ�֣�
���������channel--IO����ͨ����
����ֵ��temp-���
ע�������
*/
unsigned short DigitalIn(unsigned char channel)
{
    unsigned short temp;

    if(channel > DI8)
         return(0);
    
    temp = *(volatile unsigned short *)(DIADDR+2*channel);   
   
    return (temp);     
}








