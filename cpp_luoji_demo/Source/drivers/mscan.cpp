#include "yn.h"


static  unsigned long  MSCAN_BASE[4]={0x80001300,0x80001380,0x80002300,0x80002380};

/*
* 函数介绍：can初始化
* 函数实现：
* 输入参数：canChannalNum--通道号，canBaudRate--波特率
* 返回值  ：无
* 注意事项：无
*/
void InitMsCAN(unsigned char canChannalNum,unsigned char canBaudRate)
{
	volatile unsigned char judge;
	
	if(canChannalNum>3)
	   return;
	
         switch(canChannalNum)
	{
		
	    case 0: *(unsigned long *)(0x80000f58)  = 0x00130000; 
                    *(volatile unsigned char *)(0x8000A04d) = 0x00;
		    break;
		
	    case 1: *(unsigned long *)(0x80000f5c)  = 0x00130000;
                    *(volatile unsigned char *)(0x8000A04e) = 0x00;
		    break;
				
	    case 2: *(unsigned long *)(0x80000f60)  = 0x00130000; 
                    *(volatile unsigned char *)(0x8000A033) = 0x00;
	            *(volatile unsigned char *)(0x8000A034) = 0x00;
		    break;
		
            case 3: *(unsigned long *)(0x80000f64)  = 0x00130000;
                    *(volatile unsigned char *)(0x8000A03B) = 0x00;
	            *(volatile unsigned char *)(0x8000A03C) = 0x00;
		    break;
		
	    default:break;
		
	}


	do
	{
	
	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANCTL0_OFFSET) |= MSCAN_CANCTL0_INITRQ_MASK; 
	    judge = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANCTL1_OFFSET);
		
	}while(!(judge & MSCAN_CANCTL1_INITAK_MASK));
	
    switch(canBaudRate)
    {
        case CAN_100Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xD3;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

        case CAN_125Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xCF;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

        case CAN_200Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xC9;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

        case CAN_250Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xC7;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

        case CAN_400Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xC4;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

        case CAN_500Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xC3;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

        case CAN_800Kbps:   *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0x44;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x16;
                            break;

        case CAN_1Mbps:     *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xC1;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;
        
        default:            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR0_OFFSET)  = 0xC1;     /*80M*/
                            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANBTR1_OFFSET)  = 0x3E;
                            break;

    }

   



    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAC_OFFSET)  = 0x00;    
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR0_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR1_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR2_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR3_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR4_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR5_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR6_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDAR7_OFFSET) = 0x00;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR0_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR1_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR2_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR3_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR4_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR5_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR6_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANIDMR7_OFFSET) = 0xff;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANCTL1_OFFSET)  = 0x80;
    
    do
	{
	
	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANCTL0_OFFSET) &= ~MSCAN_CANCTL0_INITRQ_MASK; 
	    judge = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANCTL1_OFFSET);
		
	}while((judge & MSCAN_CANCTL1_INITAK_MASK));
	
	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANCTL0_OFFSET) = 0x8;
	
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTBSEL_OFFSET) = 0x0;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRIER_OFFSET)  = 0x0;   
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTIER_OFFSET)  = 0x0; 

	
	bCANTxBufHead0 = 0;
	bCANTxBufTail0 = 0;

	bCANTxBufHead1 = 0;
	bCANTxBufTail1 = 0;


	bCANTxBufHead2 = 0;
	bCANTxBufTail2 = 0;

	bCANTxBufHead3 = 0;
	bCANTxBufTail3 = 0;

    
}


/*
* 函数介绍：can中断初始化
* 函数实现：
* 输入参数：canChannalNum--通道号，mode--工作模式
* 返回值  ：无
* 注意事项：无
*/
void MsCANIntInit(unsigned char canChannalNum,unsigned char mode)
{	
    volatile unsigned char status;
    
    if(canChannalNum>3)
        return;
	
    status = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRFLG_OFFSET);
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRFLG_OFFSET) = status;
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRIER_OFFSET) = 0x1;   
    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTIER_OFFSET) = 0x0; 

    if(mode)
        *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR1_OFFSET) |= 0x8;
    else
        *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR1_OFFSET) &= 0xf7;
}


/*
* 函数介绍：can发送函数
* 函数实现：
* 输入参数：canChannalNum--通道号
* 返回值  ：无
* 注意事项：无
*/
unsigned short MsCANSendOneMsg(unsigned char canChannalNum)
{
        canbuff_t       *ps_Buffer;
	unsigned short 	*pw_Head,*pw_Tail;
	volatile unsigned char status,statusTemp;
	
	if(canChannalNum>3)
	   return;

        switch(canChannalNum)
	{
		
	    case 0: pw_Head = &bCANTxBufHead0;
		    pw_Tail = &bCANTxBufTail0; 
		    ps_Buffer = &CANTxBuf0[bCANTxBufHead0];
		    break;
		
	    case 1: pw_Head = &bCANTxBufHead1;
		    pw_Tail = &bCANTxBufTail1;
		    ps_Buffer = &CANTxBuf1[bCANTxBufHead1];
		    break;
				
	    case 2: pw_Head = &bCANTxBufHead2;
		    pw_Tail = &bCANTxBufTail2;
		    ps_Buffer = &CANTxBuf2[bCANTxBufHead2];
		    break;
		
            case 3: pw_Head = &bCANTxBufHead3;
		    pw_Tail = &bCANTxBufTail3;
		    ps_Buffer = &CANTxBuf3[bCANTxBufHead3];
		    break;
		
	    default:break;
		
	}
	
	status = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTFLG_OFFSET);	
     
	if(status&0x1)
	{
            if(*pw_Head == *pw_Tail)
            { 
                 *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTIER_OFFSET) = 0;

            }
            else
            {  
                  
                *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTBSEL_OFFSET) = status;    
            	
                if(ps_Buffer->mode)
                {
                    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR0_OFFSET)   = (ps_Buffer->id>>21)&0xff; 
        	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR1_OFFSET)   = (((ps_Buffer->id>>13)&0xe0) + 0x8 + ((ps_Buffer->id>>15)&0x7));
                    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR2_OFFSET)   = (ps_Buffer->id>>7)&0xff; 
        	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR3_OFFSET)   = (ps_Buffer->id<<1)&0xfe; 
        	}                
                else
                {	   
	    	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR0_OFFSET)   = (ps_Buffer->id>>3)&0xff; 
        	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR1_OFFSET)   = (ps_Buffer->id<<5)&0xe0;
        	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR2_OFFSET)   = 0;
        	    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXIDR3_OFFSET)   = 0;
        	}
    

        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR0_OFFSET)   = ps_Buffer->data[0];
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR1_OFFSET)   = ps_Buffer->data[1]; 
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR2_OFFSET)   = ps_Buffer->data[2]; 
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR3_OFFSET)   = ps_Buffer->data[3]; 
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR4_OFFSET)   = ps_Buffer->data[4]; 
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR5_OFFSET)   = ps_Buffer->data[5]; 
       		*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR6_OFFSET)   = ps_Buffer->data[6]; 
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDSR7_OFFSET)   = ps_Buffer->data[7]; 
        	*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_TXDLR_OFFSET)    = ps_Buffer->length;

                statusTemp = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTBSEL_OFFSET); 
                *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTFLG_OFFSET) = statusTemp; 
  	        *pw_Head= (*pw_Head + 1)%CAN_SEND_BUF_LEN;
             }	  	  
		
	} 

}



/*
* 函数介绍：
* 函数实现：
* 输入参数：canChannalNum--通道号
* 返回值  ：无
* 注意事项：无
*/
unsigned short MsCANSend(unsigned char canChannalNum, canbuff_t  *ps_Buffer)
{
	
	unsigned short 	*pw_Head,*pw_Tail;
	canbuff_t 	*pw_Buffer;
	volatile unsigned char status,statusTemp;
 		
	if(canChannalNum>3)
	   return;

	
	switch(canChannalNum)
	{
		
	    case 0: pw_Head = &bCANTxBufHead0;
	            pw_Tail = &bCANTxBufTail0; 
		    pw_Buffer = &CANTxBuf0[bCANTxBufTail0];
		    break;
		
	    case 1: pw_Head = &bCANTxBufHead1;
	            pw_Tail = &bCANTxBufTail1;
		    pw_Buffer = &CANTxBuf1[bCANTxBufTail1];
		    break;
				
	    case 2: pw_Head = &bCANTxBufHead2;
		    pw_Tail = &bCANTxBufTail2;
		    pw_Buffer = &CANTxBuf2[bCANTxBufTail2];
	            break;
		
	    case 3: pw_Head = &bCANTxBufHead3;
		    pw_Tail = &bCANTxBufTail3;
		    pw_Buffer = &CANTxBuf3[bCANTxBufTail3];
		    break;
		
	    default:break;
		
	}

        pw_Buffer->id      = ps_Buffer->id;			
	pw_Buffer->length  = ps_Buffer->length;	
        pw_Buffer->mode    = ps_Buffer->mode;			
	pw_Buffer->data[0] = ps_Buffer->data[0];
	pw_Buffer->data[1] = ps_Buffer->data[1];
	pw_Buffer->data[2] = ps_Buffer->data[2];
	pw_Buffer->data[3] = ps_Buffer->data[3];
	pw_Buffer->data[4] = ps_Buffer->data[4];
	pw_Buffer->data[5] = ps_Buffer->data[5];
	pw_Buffer->data[6] = ps_Buffer->data[6];
	pw_Buffer->data[7] = ps_Buffer->data[7];		
        
	*pw_Tail= (*pw_Tail+1)%CAN_SEND_BUF_LEN;

        if(*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTIER_OFFSET) == 0)
        {
            *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTIER_OFFSET) = 0x1;

        }
   
}


/*
* 函数介绍：can读取数据
* 函数实现：
* 输入参数：canChannalNum--通道号
* 返回值  ：无
* 注意事项：无
*/
void MsCANRevOneMsg(unsigned char canChannalNum) 
{
	canbuff_t           *ps_Temp; 	
	
	if(canChannalNum>3)
	   return;
	
	switch(canChannalNum)
	{
		
		case 0: ps_Temp = &CANRxBuf0;
				break;
		
		case 1: ps_Temp = &CANRxBuf1;
				break;
				
		case 2: ps_Temp = &CANRxBuf2;
				break;
		
		case 3: ps_Temp = &CANRxBuf3;
				break;
		
		default:break;
		
	}


   
        if((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR1_OFFSET))&0x8)
            ps_Temp->id      = ((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR0_OFFSET)<<21) + ((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR1_OFFSET)&0xe0)<<13) + ((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR1_OFFSET)&0x7)<<15) + (*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR2_OFFSET)<<7) + ((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR3_OFFSET)&0xfe)>>1))&0x1fffffff;       
        else
	    ps_Temp->id      = ((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR0_OFFSET)<<3) + ((*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXIDR1_OFFSET)&0xe0)>>5))&0x7ff;       

 
        ps_Temp->length  = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDLR_OFFSET); 
	ps_Temp->data[0] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR0_OFFSET);		
        ps_Temp->data[1] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR1_OFFSET);
	ps_Temp->data[2] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR2_OFFSET);
	ps_Temp->data[3] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR3_OFFSET);
	ps_Temp->data[4] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR4_OFFSET);
	ps_Temp->data[5] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR5_OFFSET);
	ps_Temp->data[6] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR6_OFFSET);
	ps_Temp->data[7] = *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_RXDSR7_OFFSET); 
	
        *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRFLG_OFFSET) = 0x1;
	


}


/*
* 函数介绍：can中断处理函数
* 函数实现：
* 输入参数：canChannalNum--通道号
* 返回值  ：无
* 注意事项：无
*/
void MsCANInterruptHandler(unsigned char canChannalNum)
{
    volatile unsigned char   status;
  
   
    status = (*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRFLG_OFFSET));
    while(status & 0x1)
    {            
        MsCANRevOneMsg(canChannalNum);            	
        status = (*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRFLG_OFFSET));
    } 
  
    if(*(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANTIER_OFFSET))
    {
        MsCANSendOneMsg(canChannalNum); 
    } 

    *(volatile unsigned char *)(MSCAN_BASE[canChannalNum] + MSCAN_CANRFLG_OFFSET) = status;
}   


