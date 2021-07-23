//////////////////////////
//	Project Stationery  //
//////////////////////////
#include "YN.H"
#include "test.h"
static  canbuff_t canTestA;

/*
* 函数介绍：主函数入口处
* 函数实现：无
* 输入参数：无
* 返回值  ：无
* 注意事项：变量的声明一定要放到函数的最前面，这个编译器要求比较严格
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
    
    
    
/*测试代码*/    
    /*mybox.a=2;
    mybox.b=3;
    printf("suqare:%d\n",mybox.square());
    */
    
    
    
    Sys_Init();    //系统初始化 
    
    //开始任务
	while (1) 
	{
	

      	//皇：这一段代码还未搞明白它的作用，条件编译把它暂时屏蔽了
       #if 0  
         
        if(PPC_ComRxLen(COM1))                          //串口
        {
    	    cnt =  PPC_ComRxLen(COM1);
    	    PPC_ComIn(COM1, buf,cnt);
    	    PPC_ComOut(COM1, buf,cnt);
        } 
       #endif 
        
		//皇：轮询各个串口
        if(FComRxLen(FCOM1))                          //串口
        {
    	    cnt =  FComRxLen(FCOM1);
    	    FComIn(FCOM1, buf,cnt);
    	    FComOut(FCOM1, buf,cnt);
       
        }
        
        if(FComRxLen(FCOM2))                          //串口
        {
    	    cnt =  FComRxLen(FCOM2);
    	    FComIn(FCOM2, buf,cnt);
    	    FComOut(FCOM2, buf,cnt);       

        }
        
        if(FComRxLen(FCOM3))                          //串口
        {
    	    cnt =  FComRxLen(FCOM3);
    	    FComIn(FCOM3, buf,cnt);
    	    FComOut(FCOM3, buf,cnt);       

        }
        
        if(FComRxLen(FCOM4))                          //串口
        {
    	    cnt =  FComRxLen(FCOM4);
    	    FComIn(FCOM4, buf,cnt);
    	    FComOut(FCOM4, buf,cnt);
       

        }
        
        if(FComRxLen(FCOM5))                          //串口
        {
    	    cnt =  FComRxLen(FCOM5);
    	    FComIn(FCOM5, buf,cnt);
    	    FComOut(FCOM5, buf,cnt);       

        }
        
        if(FComRxLen(FCOM6))                          //串口
        {
    	    cnt =  FComRxLen(FCOM6);
    	    FComIn(FCOM6, buf,cnt);
    	    FComOut(FCOM6, buf,cnt);       

        }
        
        if(FComRxLen(FCOM7))                          //串口
        {
    	    cnt =  FComRxLen(FCOM7);
    	    FComIn(FCOM7, buf,cnt);
    	    FComOut(FCOM7, buf,cnt);
       

        }
        
        if(FComRxLen(FCOM8))                          //串口
        {
    	    cnt =  FComRxLen(FCOM8);
    	    FComIn(FCOM8, buf,cnt);
    	    FComOut(FCOM8, buf,cnt);       

        }
        
        if(FComRxLen(FCOM9))                          //串口
        {
    	    cnt =  FComRxLen(FCOM9);
    	    FComIn(FCOM9, buf,cnt);
    	    FComOut(FCOM9, buf,cnt);       

        }
        
        //皇：通过计时器实现定时调用
         if (tag_1ms) 		//1000Hz任务
        {   
            
            tag_1ms = 0;	//结束处一定要记得把tag置0，它会在定时器中断里面进行赋值
        }
                  
        if (tag_5ms)		//200Hz任务
        {

           tag_5ms = 0;
              			  
        }    
	
        
        if (tag_10ms) 		//100Hz任务
        {   
            
            tag_10ms = 0; 
		        
        }
                  
        if (tag_20ms)		//50Hz任务
        {
        
           tag_20ms = 0;
                 			  
        }    
	
	    if(tag_50ms)		//20Hz任务
	    {
  
	        tag_50ms = 0;
	    }
	    
	    if (tag_100ms) 		//10Hz任务
        {   
            
            printf("hello! world3!\n"); 
            tag_100ms = 0;     
        }
                  
        if (tag_500ms)		//2Hz任务
        {

           tag_500ms = 0;           			  
        } 
	
	    if(tag_1s == 1)		//1Hz任务
	    {
  

	      tag_1s = 0;
	    }
	    
	    if (tag_2s)			//0.5Hz任务
        {

           tag_2s = 0;       			  
        } 	  

	}
}
