#ifndef __PWM__
#define __PWM__


#define PWMOUTENADDR     0x8400A000
#define PWMOUTCLKENADDR  0x8400A100
#define PWMOUTFREQADDR   0x8400A102
#define PWMOUTPERADDR    0x8400A200
#define PWMOUTHIGHADDR   0x8400A400

#define PWMFREQ         66666666    /*Hz*/
#define PWMDIVFREQ      22222222    /*Hz*/

#define PWMOUTCH1    0      
#define PWMOUTCH2    1      
#define PWMOUTCH3    2     
#define PWMOUTCH4    3  
#define PWMOUTCH5    4     
#define PWMOUTCH6    5 
#define PWMOUTCH7    6      
#define PWMOUTCH8    7      
#define PWMOUTCH9    8     
#define PWMOUTCH10   9  
#define PWMOUTCH11   10     
#define PWMOUTCH12   11  
#define PWMOUTCH13   12     
#define PWMOUTCH14   13     
#define PWMOUTCH15   14    
#define PWMOUTCH16   15 
#define PWMOUTCH17   16    
#define PWMOUTCH18   17


typedef struct{
    double pwmper;   /*周期*/ 
    double pwmhi;    /*高电平时间*/	
}pwm_t;   /*unit = ms*/ 


extern pwm_t   PWMOUT[18];

void PwmInit(void);							/*PWM初始化*/
void PwmHighOut(unsigned char channel);		/*PWM高电平时间*/
void PwmPerOut(unsigned char channel);		/*PWM周期*/

#endif
