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
	
  	//�ʣ����ڵĳ�ʼ������
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


    /*IRQ0_Disable();
    IRQ0_SetDiv(IRQ0DIVFREQ);
    
    FreqInit();
    PwmInit();
    intInit();
    IRQ0_Enable(); */
    /* GPT_Enable(1000); */
   
    time_init();  		//��ʱ����ʼ��
    time_enable();
    printf("time_enable...!\n\r");
    int_enable();
    printf("init ok!!\n\r");
}
    
#endif    