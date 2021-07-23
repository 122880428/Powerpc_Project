#include "YN.h"

void  Sys_Init(void)
{
 	printf("initing...!\n\r");
    //mmu_cache_init(); 
    int_disable();    
    WDT_Disable();      

    // PPC_ComInit(COM1,115200,COM_PARITY_NONE,1,RS232);
    PPC_ComInit(COM2,115200,COM_PARITY_NONE,1,RS232);
    
    //PPC_ComEnableInterrupt(COM1);
    PPC_ComEnableInterrupt(COM2);
    
    FComSetIOBase();
    FComInit(FCOM1,921600,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM2,921600,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM3,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM4,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM5,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM6,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM7,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM8,115200,COM_PARITY_NONE,1,64,RS422);
    FComInit(FCOM9,115200,COM_PARITY_NONE,1,64,RS422);
    InitMsCAN(CAN_CHANNAL1,CAN_1Mbps);
    InitMsCAN(CAN_CHANNAL2,CAN_1Mbps);
    InitMsCAN(CAN_CHANNAL3,CAN_1Mbps);
    InitMsCAN(CAN_CHANNAL4,CAN_1Mbps); 
    
    MsCANIntInit(CAN_CHANNAL1,CAN_BASE_FRAME);
    MsCANIntInit(CAN_CHANNAL2,CAN_BASE_FRAME);
    MsCANIntInit(CAN_CHANNAL3,CAN_BASE_FRAME);
    MsCANIntInit(CAN_CHANNAL4,CAN_BASE_FRAME);  
    
    IRQ0_Disable();
    IRQ0_SetDiv(IRQ0DIVFREQ);
    
    FreqInit();
    PwmInit();
    intInit();
    IRQ0_Enable(); 
    /* GPT_Enable(1000); */
   
    time_init();  
    time_enable();
    
    int_enable();
    printf("init ok!!\n\r");
}
    