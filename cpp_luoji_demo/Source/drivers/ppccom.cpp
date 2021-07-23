
#include"ppccom.h"

CommStruc            COM[2];



void PPC_ComInit(unsigned char Port,unsigned long BaudRate,unsigned char ParityMode,unsigned char StopBit,unsigned char Mode) 
{
	unsigned short cnt;
        unsigned long  status;

	if(Port>COM2)
	    return;
	 	
	switch(Port)
	{
		case COM1: COM[Port].Base = (0x80000000 + 0x11000); break;
		case COM2: COM[Port].Base = (0x80000000 + 0x11000 + 0x100); break;
		default : break;
	}	

	
        *(volatile unsigned short *)(COM[Port].Base + PSC_IMR_OFFSET) = (unsigned short)0x0;
        *(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_IMR_OFFSET) = 0x0;

	*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_TX_CMD_OFFSET) = FIFOC_PSCN_CMD_SLICE_RST;
	*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_CMD_OFFSET) = FIFOC_PSCN_CMD_SLICE_RST;


	*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_TX_SIZE_OFFSET) = ((CFG_FIFO_TX_SIZE/4) |((CFG_FIFO_TX_ADDR + Port*CFG_FIFO_RX_ADDR)<<16));
	*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_SIZE_OFFSET) = ((CFG_FIFO_RX_SIZE/4) |((CFG_FIFO_TX_SIZE + Port*CFG_FIFO_RX_ADDR)<<16));
	
	*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_TX_CMD_OFFSET) = FIFOC_PSCN_CMD_SLICE_EN;
	*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_CMD_OFFSET) = FIFOC_PSCN_CMD_SLICE_EN;
	
	
        *(volatile unsigned char *)(COM[Port].Base + PSC_CR_OFFSET)   = (unsigned char)0x0A;	/* disable TX/RX */
/* 	*(volatile unsigned short *)(COM[Port].Base + PSC_CSR_OFFSET) = (unsigned short)0xDD00; /* choose the prescaler by 16 for the Tx/Rx clock generation */
        *(volatile unsigned char *)(COM[Port].Base + PSC_CSR_OFFSET) = (unsigned char)0xFF; /* choose the prescaler by 10 for the Tx/Rx clock generation */
	*(volatile unsigned long *)(COM[Port].Base + PSC_SICR_OFFSET) = (unsigned long)0x00000000; /* select UART mode DCD input ignored */	

        switch(ParityMode)
	{
		
		case 0:
		     *(volatile unsigned char *)(COM[Port].Base + PSC_MR1_OFFSET)  = (unsigned char)0x13;	/* choose UART 8 bits, No parity */		/*无校验*/
		     break;
		case 1:
		     *(volatile unsigned char *)(COM[Port].Base + PSC_MR1_OFFSET)  = (unsigned char)0x3;		/*偶校验*/
		     break;		     
		case 2:
		     *(volatile unsigned char *)(COM[Port].Base + PSC_MR1_OFFSET)  = (unsigned char)0x7;		/*奇校验*/
		     break;
		default:
		     	*(volatile unsigned char *)(COM[Port].Base + PSC_MR1_OFFSET)  = (unsigned char)0x13;	/* choose UART 8 bits, No parity */		/*无校验*/
		     break;
		
	}

       if(StopBit == 2)
        *(volatile unsigned char *)(COM[Port].Base + PSC_MR2_OFFSET)  = (unsigned char)0x0f;	/* choose stop bit 2 */
       else
	*(volatile unsigned char *)(COM[Port].Base + PSC_MR2_OFFSET)  = (unsigned char)0x07;	/* choose stop bit 1 */
	
    switch (BaudRate) {
	    case 1200:
	    	cnt = DL_1200;   break;	/*   1200 baud */
	    case 2400:
	    	cnt = DL_2400;   break;	/*   2400 baud */
	    case 4800:
	    	cnt = DL_4800;   break;	/*   4800 baud */
	    case 9600:
	    	cnt = DL_9600;   break;	/*   9600 baud */
    	    case 19200:
    		cnt = DL_19200;  break;	/*  19200 baud */
	    case 38400:
	    	cnt = DL_38400;  break;	/*  38400 baud */
	    case 57600:
	    	cnt = DL_57600;  break;	/*  57600 baud */
	    case 115200:
	    	cnt = DL_115200; break;	/* 115.2K baud */
	    case 230400:
	    	cnt = DL_230400; break;	/* 230.4K baud */	    	
	    case 460800:
	    	cnt = DL_460800; break;	/* 460.8K baud */
	    case 921600:
	    	cnt = DL_921600; break;	/* 921.6K baud */	    	
	    default:
	        cnt = DL_9600;   break;	/*   9600 baud */
    }

    
	*(volatile unsigned char *)(COM[Port].Base + PSC_CTUR_OFFSET)=(unsigned char)((cnt >> 8) & 0xff);
	*(volatile unsigned char *)(COM[Port].Base + PSC_CTLR_OFFSET)=(unsigned char)(cnt & 0xff); 

	
	*(volatile unsigned short *)(COM[Port].Base + PSC_IMR_OFFSET) = (unsigned short)0x0;	/* disable interrupts */

     	*(volatile unsigned char *)(COM[Port].Base + PSC_CR_OFFSET) = (unsigned char)0x09;	/* enable RX */
} 


void PPC_ComEnableInterrupt(unsigned char Port)
{
     *(volatile unsigned short *)(COM[Port].Base + PSC_IMR_OFFSET) = (unsigned short)0x800;	/* enable interrupts */
     *(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_IMR_OFFSET) = 0x20;	/* enable interrupts */

}

unsigned char  PPC_ComRxLen (unsigned char Port)
{
    unsigned char len;

    len = (unsigned char)(COM[Port].Rxhead - COM[Port].Rxtail);  
    return (len);
}

unsigned char  PPC_ComTxLen (unsigned char Port)
{
    unsigned char len;
    
    len = (unsigned char)(COM[Port].Txhead - COM[Port].Txtail);
    return (len);
}

unsigned char  PPC_ComIn (unsigned char Port,unsigned char buf[], unsigned char len)
{
    unsigned char RxLen,NumIn,idx;

    RxLen=PPC_ComRxLen(Port);
    if (RxLen>=len) NumIn=len;
    else            NumIn=RxLen;
    
	  for (idx=0;idx<NumIn;idx++) buf[idx]=COM[Port].RxBuf[COM[Port].Rxtail++];
	  return (NumIn);
}

unsigned char  PPC_ComOut(unsigned char Port, unsigned char buf[], unsigned char len)
{
    unsigned char TxLen,NumOut,idx;

    TxLen=PPC_ComTxLen(Port);
    if ((TxLen+len)<=PPC_ComTxBuffSize) NumOut=len;
    else            NumOut=(unsigned char)(PPC_ComTxBuffSize-TxLen);

    for (idx=0;idx<NumOut;idx++) {
      COM[Port].TxBuf[COM[Port].Txhead++]=buf[idx];
    }
    
    if (PPC_ComTxLen(Port)) {

         *(volatile unsigned char *)(COM[Port].Base + PSC_CR_OFFSET) = (unsigned char)0x05;     /* enable TX/RX */
                                                                    
	  }	
	  return(NumOut);
}


void PPC_ComRxInterruptHandler(unsigned char Port)
{ 
    unsigned short temp_int;
    unsigned long  status, cnt,j;

    switch(Port)
	{
		case COM1: COM[Port].Base = (0x80000000 + 0x11000); break;
		case COM2: COM[Port].Base = (0x80000000 + 0x11000 + 0x100); break;
		default : break;
	}
    
    if((*(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_SR_OFFSET)&0x20) == 0x20) 
    {
        cnt = *(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_COUNT_OFFSET);
        for(j = 0;j < cnt; j++)  
        {
            COM[Port].RxBuf[COM[Port].Rxhead++]= *(volatile unsigned char *)(COM[Port].Base + FIFOC_PSCN_RX_DATA_OFFSET);

        }  
    } 	 
    
    status = *(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_ISR_OFFSET);
    *(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_RX_ISR_OFFSET) = status; 
              			        
} 


void  PPC_ComFifoInterruptHandler(void)
{
    unsigned short     int_temp;
    unsigned long  status;

   /* logMsg("0x%x\n\r",(*(volatile unsigned short *)MPC512X_FIFOC_ISR_OFFSET)&0x3ff); */
    
     if(((*(volatile unsigned short *)MPC512X_FIFOC_ISR_OFFSET)&0x3ff)!=0x0)
     {
         int_temp = (*(volatile unsigned short *)MPC512X_FIFOC_ISR_OFFSET)&0x3ff;
         
         if(int_temp&0x1)
         {
         	 PPC_ComRxInterruptHandler(COM1);
         }
         
         if(int_temp&0x2)
         {
         	 PPC_ComRxInterruptHandler(COM2);
                
         }
         
     }     	

	
}


void    PPC_ComTxInterruptHandler(unsigned char Port)
{
	unsigned char i,cnt;
	  
	  
	if((*(volatile unsigned short *)(COM[Port].Base + PSC_ISR_OFFSET) &0x800)== 0x800)
	{
        if(!PPC_ComTxLen(Port))
	    { 
	       
		    *(volatile unsigned char *)(COM[Port].Base + PSC_CR_OFFSET) = (unsigned char)0x09; /* Disable Tx interrupts*/
		    *(volatile unsigned long *)(COM[Port].Base + FIFOC_PSCN_TX_CMD_OFFSET) |=FIFOC_PSCN_CMD_SLICE_RST;
		} 
		else 
		{
		    if(PPC_ComTxLen(Port) < CFG_FIFO_TX_SIZE)
                cnt = PPC_ComTxLen(Port);
            else
                cnt = CFG_FIFO_TX_SIZE;
                     
            for(i = 0; i < cnt; i++ )
            {
                *(volatile unsigned char *)(COM[Port].Base + FIFOC_PSCN_TX_DATA_OFFSET) = COM[Port].TxBuf[COM[Port].Txtail++];
            }
 	    } 
	  
    }
	
}



