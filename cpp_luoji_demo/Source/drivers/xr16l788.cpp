#include "YN.h"

/*
*********************************************************************************************************
*                                       GLOBAL  VARIABLES
*********************************************************************************************************
*/
XFCommStruc            XFCOM[9]; 

/*
*********************************************************************************************************
*                                            Set Port's I/O Base
*********************************************************************************************************
*/

/*
* 函数介绍：设置串口基地址初始化
* 函数实现：
* 输入参数：无
* 返回值  ：无
* 注意事项：无
*/
void FComSetIOBase(void)
{
    unsigned char i;
    
    for(i = 0; i < 9; i++)
    { 
       XFCOM[i].Base= FCOM_IOBASE + i*0x200;  
       
    }
}


/*
*********************************************************************************************************
*                                            Configure the Port
*********************************************************************************************************
*/

/*
* 函数介绍：串口初始化
* 函数实现：
* 输入参数：Port--通道号，BaudRate--波特率  Parity--奇偶校验位，StopBit--停止位，RxFifoNum--接收缓存大小，Mode_422_232-串口模式
* 返回值  ：无
* 注意事项：无
*/    		
void FComInit(unsigned char port, long baudrate,unsigned char parity,unsigned char StopBit,unsigned short rxfifonum,unsigned char mode_422_232)
{
    unsigned short divider;
    
     divider = (unsigned short)(((1.0*UARTFREQ/baudrate)*2+1)/2);
 
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_RX_EN)  = 0x0;

    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_TX_EN)  = 0x0;

    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_BT)     = divider;

    if(StopBit == 0x2)
       *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_PARITY) = (parity+4);
    else
       *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_PARITY) = parity;

    if(rxfifonum > XFComFifoRxLen)
        rxfifonum = XFComFifoRxLen;    
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_FCR) =  rxfifonum;      /*2??ü3?1y350*/
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_422_232) = mode_422_232;
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_RX_EN)  = 0x1;
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_TX_EN)  = 0x1;
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_TIME_OUT) = 80;   
    *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_INT_ENABLE)  = 0x1;
 
    XFCOM[port].Rxhead=XFCOM[port].Txhead=XFCOM[port].Rxtail=XFCOM[port].Txtail=0;
  
}
		

/*
*********************************************************************************************************
*                                            Uart Interrupt Handler
*********************************************************************************************************
*/


/*
* 函数介绍：串口接收中断处理函数
* 函数实现：
* 输入参数：port--通道号
* 返回值  ：无
* 注意事项：无
*/
void FComRxInterruptHandler(unsigned char port)
{ 
    unsigned short    i,cnt;

    
    cnt = *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_RXCNT);
    
    if(cnt > XFComFifoRxLen)
       cnt = XFComFifoRxLen;
    
    for(i = 0; i < cnt; i++)
    {
    
        XFCOM[port].RxBuf[XFCOM[port].Rxhead++]=((*(volatile unsigned short *)(XFCOM[port].Base+FCOM_UART_RX_REG))&0xff);
        if(XFCOM[port].Rxhead >= XFComRxBuffSize)        
            XFCOM[port].Rxhead = 0;       
    
    } 
              			        
} 


/*
* 函数介绍：串口中断处理函数
* 函数实现：
* 输入参数：无
* 返回值  ：无
* 注意事项：无
*/
void  FComInterruptHandler(void)
{
    unsigned short     int_temp;
    unsigned long  status;
    
     if(((*(volatile unsigned short *)FCOM_UART_STATUS)&0x1ff)!=0x0)
     {
         int_temp = (*(volatile unsigned short *)FCOM_UART_STATUS)&0x1ff;
         
         if(int_temp&0x1)
         {
         	 FComRxInterruptHandler(FCOM1);                
                /*  semGive(semFCom1); */
         }
         
         if(int_temp&0x2)
         {
         	 FComRxInterruptHandler(FCOM2);
                 /* semGive(semFCom2); */
         }

         if(int_temp&0x4)
         {
         	 FComRxInterruptHandler(FCOM3);                
                /*  semGive(semFCom3); */
         }
         
         if(int_temp&0x8)
         {
         	 FComRxInterruptHandler(FCOM4);
                 /* semGive(semFCom4); */
         }

          if(int_temp&0x10)
         {
         	 FComRxInterruptHandler(FCOM5);                
                /*  semGive(semFCom5); */
         }
         
         if(int_temp&0x20)
         {
         	 FComRxInterruptHandler(FCOM6);
                 /* semGive(semFCom6); */
         }

         if(int_temp&0x40)
         {
         	 FComRxInterruptHandler(FCOM7);                
                /*  semGive(semFCom7); */
         }
         
         if(int_temp&0x80)
         {
         	 FComRxInterruptHandler(FCOM8);
                 /* semGive(semFCom8); */
         }
  
         if(int_temp&0x100)
         {
         	 FComRxInterruptHandler(FCOM9);
                 /* semGive(semFCom9); */
         }
     }     	

	
}


/*
*********************************************************************************************************
*                                            Get Rx Len
*********************************************************************************************************
*/

/*
* 函数介绍：串口接收缓冲区数据长度查询
* 函数实现：
* 输入参数：port--通道号
* 返回值  ：len--数据长度
* 注意事项：无
*/
unsigned short  FComRxLen (unsigned char port)
{
    unsigned short len;
    
    len = (XFComRxBuffSize + XFCOM[port].Rxhead - XFCOM[port].Rxtail)%XFComRxBuffSize;
    
    return (len);
}
 

/*
*********************************************************************************************************
*                                            Get Tx Len
*********************************************************************************************************
*/

/*
* 函数介绍：串口发送缓冲区数据长度查询
* 函数实现：
* 输入参数：port--通道号
* 返回值  ：len--数据长度
* 注意事项：无
*/
unsigned short  FComTxLen (unsigned char port)
{
    unsigned short len;
    
    len = (XFComTxBuffSize + XFCOM[port].Txhead - XFCOM[port].Txtail)%XFComTxBuffSize;
    
    return (len);
 
}


/*
*********************************************************************************************************
*                                          User Get Chars
*********************************************************************************************************
*/

/*
* 函数介绍：串口读取缓冲区数据
* 函数实现：
* 输入参数：port--通道号，buf[]--数据存储地址，len--读取的长度
* 返回值  ：NumIn--实际读取数据长度
* 注意事项：无
*/
unsigned short  FComIn (unsigned char port,  unsigned char buf[], unsigned short len)
{
    unsigned short RxLen,NumIn,idx;

    RxLen=FComRxLen(port);
    if (RxLen>=len) NumIn=len;
    else            NumIn=RxLen;

	for (idx=0;idx<NumIn;idx++) 
	{
	    
	    buf[idx]=XFCOM[port].RxBuf[XFCOM[port].Rxtail++];
	    
	    if(XFCOM[port].Rxtail >= XFComRxBuffSize)
	        XFCOM[port].Rxtail = 0; 
	  	
	}
	return (NumIn);
}


/*
*********************************************************************************************************
*                                          User Send Chars
*********************************************************************************************************
*/

/*
* 函数介绍：串口发送缓冲区数据
* 函数实现：
* 输入参数：port--通道号，buf[]--数据存储地址，len--读取的长度
* 返回值  ：cnt--发送数据长度
* 注意事项：无
*/
unsigned short  FComOut(unsigned char port, unsigned char buf[], unsigned short len)
{
    unsigned short  idx;
    unsigned short cnttt,cnt;
    
  
    for (idx=0;idx<len;idx++) 
    {
    	XFCOM[port].TxBuf[XFCOM[port].Txhead++]=buf[idx];
    	if(XFCOM[port].Txhead >= XFComTxBuffSize)        
           XFCOM[port].Txhead = 0;
    }
    
    
    if (FComTxLen(port)) 
    { 
 
         cnttt = *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_TXCNT);
          
         if(FComTxLen(port) < (XFComFifoTxLen-cnttt))
        	 cnt = FComTxLen(port);
         else
             cnt = (XFComFifoTxLen- cnttt);
                     
         for(idx = 0; idx < cnt; idx++)
         {
         	*(volatile unsigned short *)(XFCOM[port].Base+FCOM_UART_TX_REG) = XFCOM[port].TxBuf[XFCOM[port].Txtail++];
         	if(XFCOM[port].Txtail >= XFComTxBuffSize)        
                XFCOM[port].Txtail = 0; 
         }     
              
	  }
	 return(cnt);	 
}

unsigned short  FComOut_mavlink(unsigned char port, const uint8_t *buf, int len)
{
    unsigned short  idx;
    unsigned short cnttt,cnt;
    
  
    for (idx=0;idx<len;idx++) 
    {
        XFCOM[port].TxBuf[XFCOM[port].Txhead++]=buf[idx];
        if(XFCOM[port].Txhead >= XFComTxBuffSize)        
           XFCOM[port].Txhead = 0;
    }
    
    
    if (FComTxLen(port)) 
    { 
 
         cnttt = *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_TXCNT);
          
         if(FComTxLen(port) < (XFComFifoTxLen-cnttt))
             cnt = FComTxLen(port);
         else
             cnt = (XFComFifoTxLen- cnttt);
                     
         for(idx = 0; idx < cnt; idx++)
         {
            *(volatile unsigned short *)(XFCOM[port].Base+FCOM_UART_TX_REG) = XFCOM[port].TxBuf[XFCOM[port].Txtail++];
            if(XFCOM[port].Txtail >= XFComTxBuffSize)        
                XFCOM[port].Txtail = 0; 
         }     
              
      }
     return(cnt);
}


/*
*********************************************************************************************************
*                                          User Get Chars  poll
*********************************************************************************************************
*/

/*
* 函数介绍：
* 函数实现：
* 输入参数：port--通道号
* 返回值  ：NumIn--
* 注意事项：无
*/
unsigned short  FComInPoll (unsigned char port)
{
    unsigned short NumIn,i;

    NumIn = *(volatile unsigned short *)(XFCOM[port].Base + FCOM_UART_RXCNT);
    
    if(NumIn > XFComFifoRxLen)
       NumIn = XFComFifoRxLen;
    
    for(i = 0; i < NumIn; i++)
    {
        XFCOM[port].RxBuf[XFCOM[port].Rxhead++]=((*(volatile unsigned short *)(XFCOM[port].Base+FCOM_UART_RX_REG))&0xff);  
        if(XFCOM[port].Rxtail >= XFComRxBuffSize)
	        XFCOM[port].Rxtail = 0;   
    }
    
	return (NumIn);
}








