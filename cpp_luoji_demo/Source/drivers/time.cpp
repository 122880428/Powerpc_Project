#include "time.h"

//�ʣ�����ʵ��������ȶ������һЩ����
unsigned long    timetick=1;    
unsigned char    tag_200us;
unsigned char    tag_1ms;
unsigned char    tag_5ms;
unsigned char    tag_10ms;
unsigned char    tag_20ms;
unsigned char    tag_40ms;
unsigned char    tag_50ms;
unsigned char    tag_80ms;
unsigned char    tag_100ms;
unsigned char    tag_125ms;
unsigned char    tag_200ms;
unsigned char    tag_500ms;
unsigned char    tag_600ms;
unsigned char    tag_1s;
unsigned char    tag_2s;
unsigned short   CPULoad;
unsigned short   IdleCount=1L;




/****************************************************************************
* ���ƣ�time_init
* ���ܣ���ʱ����ʼ��
* ��ڲ�������
* ���ڲ�������
* ����ֵ����
* ��ע����ϵͳ��ʼ����ʱ�򱻵���
****************************************************************************/ 
asm void time_init(void) {
  lis		r4, 0x0000		/* Load initial DEC value of 49500  1ms*/
  ori		r4, r4, 0xC15B
  mtdec		r4

}

/*
* �������ܣ������ʱ���жϱ�־
* ����ʵ�֣���
* �����������
* ����ֵ  ����
* ע��������뵽��ʱ���ж�֮��Ҫ��ʱ�����жϱ�־λ
*/
asm void clr_time_flag(void) {
  lis		r4, 0x0000		/* Load initial DEC value of 49500  1ms*/
  ori		r4, r4, 0xC15B
  mtdec		r4
}



/****************************************************************************
* ���ƣ�time_isr
* ���ܣ���ʱ���жϺ���
* ��ڲ�������
* ���ڲ�������
* ����ֵ����
* ��ע��������ʱ���ж�֮�����뵽���������
****************************************************************************/ 
	
void time_isr (void)
{

   clr_time_flag();			//����жϱ�־λ
   timetick=(timetick+1)%(5000*60); 
   tag_1ms   = 1;
   
                           
    if ((timetick % 5 ) == 0)   tag_5ms  = 1;                          
	if ((timetick % 10 ) == 0)	tag_10ms  = 1;
	if ((timetick % 20 ) == 0)	tag_20ms  = 1;
	if ((timetick % 40  ) == 0)	tag_40ms  = 1;
	if ((timetick % 50 ) == 0)	tag_50ms  = 1;
	if ((timetick % 80 ) == 0)	tag_80ms  = 1;
	if ((timetick % 100 ) == 0)	tag_100ms = 1;
	if ((timetick % 125 ) == 0)	tag_125ms = 1;
	if ((timetick % 200 ) == 0)	tag_200ms = 1;
	if ((timetick % 500) == 0) 
	{ 
	tag_500ms = 1; 
	CPULoad=(unsigned short)(50000L/IdleCount); 	//�ʣ����ﲻ���ΪʲôҪ������������䡣
	IdleCount=1; 
	} 
    if ((timetick % 600) == 0)   tag_600ms = 1;
	if ((timetick % 1000) == 0){ tag_1s    = 1;}
	if ((timetick % 2000) == 0)	tag_2s    = 1;      
	
    
}
