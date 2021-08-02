#include "YN.h"

/* local */

static INTR_HANDLER	intrVecTable[NUM_VEC_MAX];	/*  Intr vector table */


void intInit(void)
{

    ppc5125IntDisable(COM1_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)COM1_INT_SOURCE, (VOIDFUNCPTR)PPC_ComTxInterruptHandler,COM1);
    ppc5125IntEnable(COM1_INT_SOURCE); 
    
    ppc5125IntDisable(COM2_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)COM2_INT_SOURCE, (VOIDFUNCPTR)PPC_ComTxInterruptHandler,COM2);
    ppc5125IntEnable(COM2_INT_SOURCE); 
    
    
    ppc5125IntDisable(COM_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)COM_INT_SOURCE, (VOIDFUNCPTR)PPC_ComFifoInterruptHandler,0);
    ppc5125IntEnable(COM_INT_SOURCE);  
    
    
    ppc5125IntDisable(IRQ1_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)IRQ1_INT_SOURCE, (VOIDFUNCPTR)FComInterruptHandler,0);
    ppc5125IntEnable(IRQ1_INT_SOURCE);
    
    ppc5125IntDisable(GPT0_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)GPT0_INT_SOURCE, (VOIDFUNCPTR)GPT_InterruptHandler,0);
    ppc5125IntEnable(GPT0_INT_SOURCE);
    
    ppc5125IntDisable(CAN1_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)CAN1_INT_SOURCE, (VOIDFUNCPTR)MsCANInterruptHandler,CAN_CHANNAL1);
    ppc5125IntEnable(CAN1_INT_SOURCE);
    
    ppc5125IntDisable(CAN2_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)CAN2_INT_SOURCE, (VOIDFUNCPTR)MsCANInterruptHandler,CAN_CHANNAL2);
    ppc5125IntEnable(CAN2_INT_SOURCE);
    
    ppc5125IntDisable(CAN3_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)CAN3_INT_SOURCE, (VOIDFUNCPTR)MsCANInterruptHandler,CAN_CHANNAL3);
    ppc5125IntEnable(CAN3_INT_SOURCE);
    
    ppc5125IntDisable(CAN4_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)CAN4_INT_SOURCE, (VOIDFUNCPTR)MsCANInterruptHandler,CAN_CHANNAL4);
    ppc5125IntEnable(CAN4_INT_SOURCE);   
    
    ppc5125IntDisable(IRQ0_INT_SOURCE);
    ppc5125IntConnect ((VOIDFUNCPTR *)IRQ0_INT_SOURCE, (VOIDFUNCPTR)IRQ0_InterruptHandler,0);
    ppc5125IntEnable(IRQ0_INT_SOURCE); 


    
    
}
/*******************************************************************************
*
* ppc5125IntConnect - connect a routine to an interrupt 
*
* This routine connects any C or assembly routine to one of the multiple 
* sources of interrupts.
*
* The connected routine can be any normal C code, except that it must not 
* invoke certain operating system functions that may block or perform I/O
* operations.
*
* <vector> types are defined in h/drv/intrClt/ppc5125Intr.h.
*
* RETURNS: OK, or ERROR if <vector> is unknown.
*
* SEE ALSO: ppc5125Intr.h
*/

int ppc5125IntConnect
    (
    VOIDFUNCPTR *	vector,		/* interrupt vector to attach to */
    VOIDFUNCPTR		routine,	/* routine to be called */
    int 		parameter	/* parameter to be passed to routine */
    )
    {

    /* test the vector */

    if ((int)(vector) >= NUM_VEC_MAX)
	return (-1);

    intrVecTable[(int)(vector)].vec = routine;
    intrVecTable[(int)(vector)].arg = parameter;

    return (0);
    }

/*******************************************************************************
*
* ppc5125IntrDemux - SIU interrupt demultiplexer 
*
* This routine must be bound to external interrupt exception (vector 0x500). 
* It is used to call the appropriate handler with its argument when an
* interrupt occurs. 
*
* NOTE: when this function is called the interrupts are still locked. It's
* this function responsability to unlock the interrupt.
*
* RETURNS: N/A
*/

void ppc5125IntrDemux (void)
    {
    unsigned char 	intVec;			/* interrupt vector */
    unsigned long	intMask2;		/* current interrupt mask */
    unsigned long	intMask3;		/* current interrupt mask */
    unsigned long	intMask4;		/* current interrupt mask */

    /* read the interrupt vector register */

    intVec =(*(volatile unsigned long *)(PPC5125IPICSIVCR))&0x7f;
    
    if(intVec == 0) return;


    /* save the current interrupt mask */ 

    intMask2 = (*(volatile unsigned long *)(PPC5125IPICSIMSRL));
    intMask3 = (*(volatile unsigned long *)(PPC5125IPICSIMSRH));
    intMask4 = (*(volatile unsigned long *)(PPC5125IPICSEMSR));
    
 //   (*(volatile unsigned long *)(PPC5125IPICSIPNRH)) = (*(volatile unsigned long *)(PPC5125IPICSIPNRH));
 //   (*(volatile unsigned long *)(PPC5125IPICSIPNRL)) = (*(volatile unsigned long *)(PPC5125IPICSIPNRL));

    /* lock all levels inferior to the interrupt detected */

    if ((intVec >= 1) && (intVec < 17))
    {
    	(*(volatile unsigned long *)(PPC5125IPICSIMSRH)) &= ~(1 << (16 - intVec));
    	(*(volatile unsigned long *)(PPC5125IPICSIMSRL)) =0x0;
    	(*(volatile unsigned long *)(PPC5125IPICSEMSR))  =0x0;
    }
    
    if ((intVec >= 32) && (intVec < 48))
    {
    	(*(volatile unsigned long *)(PPC5125IPICSIMSRH)) &= ~(1 << (63 - intVec));
    	(*(volatile unsigned long *)(PPC5125IPICSIMSRL)) =0x0;
    	(*(volatile unsigned long *)(PPC5125IPICSEMSR))  =0x0;
    }
    
    if((intVec >= 64) && (intVec < 96))
    {
    	(*(volatile unsigned long *)(PPC5125IPICSIMSRL)) &= ~(1 << (95 - intVec));
    	(*(volatile unsigned long *)(PPC5125IPICSIMSRH)) =0x0;
    	(*(volatile unsigned long *)(PPC5125IPICSEMSR))  =0x0;
    }
    
    
     
	if (intVec == 17)
	{
	    (*(volatile unsigned long *)(PPC5125IPICSEMSR))  &= 0xbfffffff;
	    (*(volatile unsigned long *)(PPC5125IPICSIMSRH)) =0x0;
	    (*(volatile unsigned long *)(PPC5125IPICSIMSRL)) =0x0;
	} 
	
	if (intVec == 48)
	{
		(*(volatile unsigned long *)(PPC5125IPICSEMSR))  &= 0x7fffffff;
		(*(volatile unsigned long *)(PPC5125IPICSIMSRH)) =0x0;
	    (*(volatile unsigned long *)(PPC5125IPICSIMSRL)) =0x0;
	} 

    /* call the Interrupt Handler */
    
//这里的C++语法不兼容C语言的，还得想办法改写一下
    intrVecTable[intVec].vec (intrVecTable[intVec].arg);

    
    if (intVec == 17)
	{
	    (*(volatile unsigned long *)(PPC5125IPICSEPNR)) = 0x40000000 ;
	} 
	
	if (intVec == 48)
	{
		(*(volatile unsigned long *)(PPC5125IPICSEPNR)) = 0x80000000 ;
	} 

    
    /* restore the interrupt mask */

    (*(volatile unsigned long *)(PPC5125IPICSIMSRL)) = intMask2;
    (*(volatile unsigned long *)(PPC5125IPICSIMSRH)) = intMask3;
    (*(volatile unsigned long *)(PPC5125IPICSEMSR))  = intMask4;

    return;
    }


/*******************************************************************************
*
* ppc5125IntEnable - enable one of the Level or IRQ interrupts into the SIU
*
* This routine will unmask the bit in the SIMASK register corresponding to
* the requested interrupt level.  The interrupt level must be in the range
* of 0 - 31.
* 
* RETURNS: 0, always.
*/

int ppc5125IntEnable
    (
    int intNum		/* interrupt level to enable (0 - 31) */
    )
    {

    if ((intNum >= 1) && (intNum < 17))
	   (*(volatile unsigned long *)(PPC5125IPICSIMSRH)) |= (1 << (16 - intNum));
    
    if ((intNum >= 32) && (intNum < 48))
	   (*(volatile unsigned long *)(PPC5125IPICSIMSRH)) |= (1 << (63 - intNum));
    
    if((intNum >= 64) && (intNum < 96))
       (*(volatile unsigned long *)(PPC5125IPICSIMSRL)) |= (1 << (95 - intNum)); 
    
    if(intNum == 17)
       (*(volatile unsigned long *)(PPC5125IPICSEMSR)) |= 0x40000000;
    
    if(intNum == 48)
       (*(volatile unsigned long *)(PPC5125IPICSEMSR)) |= 0x80000000;
       
     return 0;
    }

/*******************************************************************************
*
* ppc5125IntDisable - Disable one of the Level or IRQ interrupts into the SIU
*
* This routine will mask the bit in the SIMASK register corresponding to
* the requested interrupt level.  The interrupt level must be in the range
* of 0 - 31.
* 
* RETURNS: 0, always.
*/

int ppc5125IntDisable
    (
    int intNum          /* interrupt level to disable (0 - 31) */
    )
    {
    
    if ((intNum >= 1) && (intNum < 17))
	   (*(volatile unsigned long *)(PPC5125IPICSIMSRH)) &= ~(1 << (16 - intNum));
    
    if ((intNum >= 32) && (intNum < 48))
	   (*(volatile unsigned long *)(PPC5125IPICSIMSRH)) &= ~(1 << (63 - intNum));
    
    if((intNum >= 64) && (intNum < 96))
       (*(volatile unsigned long *)(PPC5125IPICSIMSRL)) &= ~(1 << (95 - intNum));
  
    if(intNum == 17)
       (*(volatile unsigned long *)(PPC5125IPICSEMSR)) &= ~(0x40000000);
    
    if(intNum == 48)
       (*(volatile unsigned long *)(PPC5125IPICSEMSR)) &= ~(0x80000000);
       
    return 0;
    }

void time_enable(void) {
   *(volatile unsigned long *)(0x80000104) = 0x00400010;
}


asm void int_enable(void) {
  lis		r3, 0x0000
  ori		r3, r3, 0xB030
  mtmsr	r3
  isync  
}

asm void int_disable(void) {
  lis		r3, 0x0000
  ori		r3, r3, 0x3030
  mtmsr	r3
  isync  
}

