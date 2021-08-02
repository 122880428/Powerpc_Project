#ifndef	_WDT_H
#define	_WDT_H


/****************************************************************************/
/*                     MODULE : WDT                                         */
/****************************************************************************/
 struct WDT_tag {
 	
 	union {                  /* Module Configuration Register */
            volatile unsigned long R;
            struct {
                volatile unsigned long SWTC:16;
                volatile unsigned long:13; 
                volatile unsigned long SWEN:1;
                volatile unsigned long SWRI:1;
                volatile unsigned long SWPR:1;  
            } B;
        } SWCRR;
    
       union {                /* Interrupt register */
            volatile unsigned long R;
            struct {
                volatile unsigned long :16;
                volatile unsigned long SWCN:16;
            } B;
        } SWCNR; 
        
        volatile unsigned short temp;
        
        union {                /* Interrupt register */
            volatile unsigned short R;
            struct {
                volatile unsigned short WS:16;
            } B;
        } SWSRR;
 
        
  
    };
    
#define WDT     (*( volatile struct WDT_tag *)        0x80000904) 
 

void  WDT_Lock(void);						/*看门狗配置函数*/
void  WDT_Enable(unsigned short val);		/*看门狗使能开启*/
void  WDT_Disable(void);					/*看门狗使能关闭*/

#endif
