//////////////////////////
//	Project Stationery  //
//////////////////////////
#include "YN.H"
#include "test.h"
static  canbuff_t canTestA;

/*
* �������ܣ���������ڴ�
* ����ʵ�֣���
* �����������
* ����ֵ  ����
* ע���������������һ��Ҫ�ŵ���������ǰ�棬���������Ҫ��Ƚ��ϸ�
*/
void main()
{

   
    unsigned char  counter;
    unsigned char  buff0[256];
    unsigned char  buff1[256];
    unsigned char  buf[256];
    unsigned char i = 0;
    unsigned long kk = 0,tt =0;
    unsigned long  cnt = 50; 
    double volt;
    unsigned short val = 10000;
    box mybox;
    
    
    
/*���Դ���*/    
    /*mybox.a=2;
    mybox.b=3;
    printf("suqare:%d\n",mybox.square());
    */
    
    
    
    Sys_Init();    //ϵͳ��ʼ�� 
    
    //��ʼ����
	while (1) 
	{
	

      	//�ʣ���һ�δ��뻹δ�������������ã��������������ʱ������
       #if 0  
         
        if(PPC_ComRxLen(COM1))                          //����
        {
    	    cnt =  PPC_ComRxLen(COM1);
    	    PPC_ComIn(COM1, buf,cnt);
    	    PPC_ComOut(COM1, buf,cnt);
        } 
       #endif 
        
		//�ʣ���ѯ��������
        if(FComRxLen(FCOM1))                          //����
        {
    	    cnt =  FComRxLen(FCOM1);
    	    FComIn(FCOM1, buf,cnt);
    	    FComOut(FCOM1, buf,cnt);
       
        }
        
        if(FComRxLen(FCOM2))                          //����
        {
    	    cnt =  FComRxLen(FCOM2);
    	    FComIn(FCOM2, buf,cnt);
    	    FComOut(FCOM2, buf,cnt);       

        }
        
        if(FComRxLen(FCOM3))                          //����
        {
    	    cnt =  FComRxLen(FCOM3);
    	    FComIn(FCOM3, buf,cnt);
    	    FComOut(FCOM3, buf,cnt);       

        }
        
        if(FComRxLen(FCOM4))                          //����
        {
    	    cnt =  FComRxLen(FCOM4);
    	    FComIn(FCOM4, buf,cnt);
    	    FComOut(FCOM4, buf,cnt);
       

        }
        
        if(FComRxLen(FCOM5))                          //����
        {
    	    cnt =  FComRxLen(FCOM5);
    	    FComIn(FCOM5, buf,cnt);
    	    FComOut(FCOM5, buf,cnt);       

        }
        
        if(FComRxLen(FCOM6))                          //����
        {
    	    cnt =  FComRxLen(FCOM6);
    	    FComIn(FCOM6, buf,cnt);
    	    FComOut(FCOM6, buf,cnt);       

        }
        
        if(FComRxLen(FCOM7))                          //����
        {
    	    cnt =  FComRxLen(FCOM7);
    	    FComIn(FCOM7, buf,cnt);
    	    FComOut(FCOM7, buf,cnt);
       

        }
        
        if(FComRxLen(FCOM8))                          //����
        {
    	    cnt =  FComRxLen(FCOM8);
    	    FComIn(FCOM8, buf,cnt);
    	    FComOut(FCOM8, buf,cnt);       

        }
        
        if(FComRxLen(FCOM9))                          //����
        {
    	    cnt =  FComRxLen(FCOM9);
    	    FComIn(FCOM9, buf,cnt);
    	    FComOut(FCOM9, buf,cnt);       

        }
        
        //�ʣ�ͨ����ʱ��ʵ�ֶ�ʱ����
         if (tag_1ms) 		//1000Hz����
        {   
            
            tag_1ms = 0;	//������һ��Ҫ�ǵð�tag��0�������ڶ�ʱ���ж�������и�ֵ
        }
                  
        if (tag_5ms)		//200Hz����
        {

           tag_5ms = 0;
              			  
        }    
	
        
        if (tag_10ms) 		//100Hz����
        {   
            
            tag_10ms = 0; 
		        
        }
                  
        if (tag_20ms)		//50Hz����
        {
        
           tag_20ms = 0;
                 			  
        }    
	
	    if(tag_50ms)		//20Hz����
	    {
  
	        tag_50ms = 0;
	    }
	    
	    if (tag_100ms) 		//10Hz����
        {   
            
            printf("hello! world3!\n"); 
            tag_100ms = 0;     
        }
                  
        if (tag_500ms)		//2Hz����
        {

           tag_500ms = 0;           			  
        } 
	
	    if(tag_1s == 1)		//1Hz����
	    {
  

	      tag_1s = 0;
	    }
	    
	    if (tag_2s)			//0.5Hz����
        {

           tag_2s = 0;       			  
        } 	  

	}
}
