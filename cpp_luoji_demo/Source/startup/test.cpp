#include "test.h"
#include <Eigen\Dense>
using Eigen::Matrix2d;
using Eigen::VectorXd;


int box::square(void)
{
	return this->a*this->b;
	return 0;
}


 	unsigned char  counter;
    unsigned char  buff0[256];
    unsigned char  buff1[256];
    unsigned char  buf[256];
    unsigned short  cnt = 50; 

void test_com(void)
{
   
      	//皇：这一段代码还未搞明白它的作用，条件编译把它暂时屏蔽了
       #if 0  
        if(PPC_ComRxLen(COM1))                          //串口
        {
        	//板载串口接收缓冲区数据长度查询
    	    cnt =  PPC_ComRxLen(COM1);
    	    //板载串口读取缓冲区数据，buf[]--数据存储地址，len--读取的长度	
    	    PPC_ComIn(COM1, buf,cnt);
    	    //板载串口发送数据		
    	    PPC_ComOut(COM1, buf,cnt);	
        } 
       #endif 
        
		//皇：轮询各个串口
        if(FComRxLen(FCOM1))                          //串口
        {
    	    cnt =  FComRxLen(FCOM1);
    	    FComIn(FCOM1, buf,cnt);
    	    printf("FCOM1 is receving...\r\n");
    	    FComOut(FCOM1, buf,cnt);
       
        }
        
        if(FComRxLen(FCOM2))                          //串口
        {
    	    cnt =  FComRxLen(FCOM2);
    	    FComIn(FCOM2, buf,cnt);
    	    printf("FCOM2 is receving...\r\n");
    	    FComOut(FCOM2, buf,cnt);       

        }
        
        if(FComRxLen(FCOM3))                          //串口
        {
    	    cnt =  FComRxLen(FCOM3);
    	    FComIn(FCOM3, buf,cnt);
    	    printf("FCOM3 is receving...\r\n");
    	    FComOut(FCOM3, buf,cnt);       
        }
        
        if(FComRxLen(FCOM4))                          //串口
        {
    	    cnt =  FComRxLen(FCOM4);
    	    FComIn(FCOM4, buf,cnt);
    	    printf("FCOM4 is receving...\r\n");
    	    FComOut(FCOM4, buf,cnt);
        }
        
        if(FComRxLen(FCOM5))                          //串口
        {
    	    cnt =  FComRxLen(FCOM5);
    	    FComIn(FCOM5, buf,cnt);
    	    printf("FCOM5 is receving...\r\n");
    	    FComOut(FCOM5, buf,cnt);       

        }
        
        if(FComRxLen(FCOM6))                          //串口
        {
    	    cnt =  FComRxLen(FCOM6);
    	    FComIn(FCOM6, buf,cnt);
    	    printf("FCOM6 is receving...\r\n");
    	    FComOut(FCOM6, buf,cnt);       
        }
        
        if(FComRxLen(FCOM7))                          //串口
        {
    	    cnt =  FComRxLen(FCOM7);
    	    FComIn(FCOM7, buf,cnt);
    	    printf("FCOM7 is receving...\r\n");
    	    FComOut(FCOM7, buf,cnt);      
        }
        
        if(FComRxLen(FCOM8))                          //串口
        {
    	    cnt =  FComRxLen(FCOM8);
    	    FComIn(FCOM8, buf,cnt);
    	    printf("FCOM8 is receving...\r\n");
    	    FComOut(FCOM8, buf,cnt);       
        }

}

double nn=200;

void test_Eigen(void)
{
	static 	Matrix2d mm;

	//VectorXd state(12);
  	mm(0,0) = 3;
  	mm(1,0) = 2.5;
  	mm(0,1) = -1;
  	mm(1,1) = mm(1,0) + mm(0,1);
  	mm = mm.inverse();
  	 //printf("m:%d",m);
    printf("m0:%f\r\n",mm(0,0));
    printf("m1:%f\r\n",mm(0,1));
    printf("m2:%f\r\n",mm(1,0));
    printf("m3:%f\r\n",mm(1,1));
    //printf("nn is %f\r\n",nn);
    
    
    
    __declspec(align(32)) double input1[4] = {1, 1, 1, 1};
  	//__attribute__ ((aligned (32))) double input2[4] = {1, 2, 3, 4};
   double input2[4] = {1, 2, 3, 4};
  // double ans=_d_add(input1[1],input2[2]);
   
  	 printf("address of input1: %X\r\n",&input1); 
  	 printf("input1 is %f,%f,%f,%f\r\n",input1[0],input1[1],input1[2],input1[3]);
  	 printf("address of input2: %X\r\n",&input2); 
  	 printf("input2 is %f,%f,%f,%f\r\n",input2[0],input2[1],input2[2],input2[3]);
}
