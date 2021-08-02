#ifndef _GPT_H_
#define _GPT_H_

#define  IPS_CLOCK_FREQ  66666666 

#define  GPT0_INT_SOURCE  INT_GPT0

struct GPT_tag {
 	
 	union {                 
            volatile unsigned long R;
            struct {
                volatile unsigned long OCPW:8;
                volatile unsigned long :2; 
                volatile unsigned long OCT:2;  
                volatile unsigned long ICM:2;
                volatile unsigned long ICT:2;
                volatile unsigned long :3;
                volatile unsigned long CE:1; 
                volatile unsigned long :1;
                volatile unsigned long STOP_CONT:1;
                volatile unsigned long OPEN_DRN:1;
                volatile unsigned long INTEN:1;
                volatile unsigned long :2;
                volatile unsigned long GPIO:2;
                volatile unsigned long :1;
                volatile unsigned long TIMER_MS:3; 
            } B;
        } MODE;
    
       union {                
            volatile unsigned long R;
            struct {
                volatile unsigned long PRESCALE:16;
                volatile unsigned long COUNT:16;
            } B;
        } COUNTER; 
        
        
        union {                
            volatile unsigned long R;
            struct {
                volatile unsigned long CAPTURE:16;
                volatile unsigned long :1;  
                volatile unsigned long OVF:3; 
                volatile unsigned long :3; 
                volatile unsigned long PIN:1; 
                volatile unsigned long :3; 
                volatile unsigned long UDOV:1;
                volatile unsigned long TEXP:1; 
                volatile unsigned long PWMP:1; 
                volatile unsigned long COMP:1; 
                volatile unsigned long CAFT:1;  
            } B;
        } STATUS;
  
    };
 

#define GPT     (*( volatile struct GPT_tag *)        0x80000B00) 

#define IRQ0ENADDR    0x84010000
#define IRQ0DIVADDR   0x84010002
#define IRQ0FREQ       2000000   /*hz*/
#define IRQ0DIVFREQ    50        /*hz*/   

void GPT_Enable(unsigned short val);//ͨ�ö�ʱ��ʹ�ܿ���
void GPT_Disable(void);//ͨ�ö�ʱ��ʹ�ܹر�
void GPT_InterruptHandler(void);//ͨ�ö�ʱ���ж�

void IRQ0_SetDiv(unsigned short val);//�ⲿ�ж�����
void IRQ0_Enable(void);//�ⲿ�ж�ʹ�ܿ���
void IRQ0_Disable(void);//�ⲿ�ж�ʹ�ܹر�
void IRQ0_InterruptHandler(void);//�ⲿ�жϺ���

#endif