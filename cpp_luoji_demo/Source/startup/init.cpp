/*
* �ļ����ƣ�init.h
* ժ Ҫ����ɸ�������Ͱ�����Դ�ĳ�ʼ��
* 
* ��ǰ�汾��1.0
* �� �ߣ���½��18439432431
* ������ڣ�2021 �� 7 �� 14 ��
* �޸����ݣ������˺���ע�ͣ��淶��һЩ���룬����ֲ��c++�����ò����ĺ�����ɾ���ˡ� 
*
*/



#ifndef INIT_H
#define INIT_H

#include "YN.h"

/*
* �������ܣ�ϵͳ��ʼ��
* ����ʵ�֣���ɸ�������Ͱ�����Դ�ĳ�ʼ��
* �����������
* ����ֵ  ����
* ע�������
*/
void  Sys_Init(void)
{
 	printf("initing...!\n\r");
    mmu_cache_init(); 			//memory management unit�ڴ����Ԫ��ʼ��
    int_disable(); 				//���ж��ܿ���   
    WDT_Disable();      		//�򿪿��Ź�
	
	
	// PPC_ComInit(COM1,115200,COM_PARITY_NONE,1,RS232);
    PPC_ComInit(COM2,115200,COM_PARITY_NONE,1,RS232);
    
    //PPC_ComEnableInterrupt(COM1);
    PPC_ComEnableInterrupt(COM2);
	
  	//�ʣ����ڵĳ�ʼ������
    FComSetIOBase();
    //�ʣ����ڵĳ�ʼ������ѡ����232ģʽ����422ģʽ��
    FComInit(FCOM1,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM2,115200,COM_PARITY_NONE,1,64,RS232);	//gcs
    FComInit(FCOM3,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM4,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM5,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM6,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM7,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM8,115200,COM_PARITY_NONE,1,64,RS232);
    //FComInit(FCOM9,115200,COM_PARITY_NONE,1,64,RS232);
    FComInit(FCOM9,100000,COM_PARITY_EVEN,2,8,RS232);
	
	
	//�ʣ�can�����������
	
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
   
    time_init();  		//��ʱ����ʼ��
    time_enable();		//�򿪶�ʱ���жϣ�����жϴ�֮�����ʹ���������
    
    int_enable();		//���ж��ܿ���
    printf("init OK!\n\r");
}
    
#endif    