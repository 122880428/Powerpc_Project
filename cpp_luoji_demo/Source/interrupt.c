/*
#######################################
#FILE
#	$RCSfile: interrupt.c,v $
#	$Date: 2007/12/18 12:26:27 $
#	$Revision: 1.6 $
#DESCRIPTION
#	interrupt handler
#COPYRIGHT	
#	(c) 2003 Freescale Corporation
#	All rights reserved.
#HISTORY
#   $Log: interrupt.c,v $
#   Revision 1.6  2007/12/18 12:26:27  r04474
#   no message
#
#   Revision 1.5  2007/07/10 09:50:05  r04474
#   bugfix@MTWX24896: For 5xx processors we need to make sure to enable
#    	the RI bit in the  MSR in order to be able to stop at hw breakpoints for ISR debug
#
#   Revision 1.4  2004/05/27 14:42:41  milies
#   added sync after setting MSR;
#   enable block address translation in MSR if debugging on Cache Debug Version
#
#   Revision 1.3  2003/10/21 12:27:37  milies
#   remove warning message
#   
########################################
*/
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

void InterruptHandler(long cause);

#ifdef __cplusplus
}
#endif


void InterruptHandler(long cause)
{
	register long aMSR;
	#pragma unused (aMSR) /* Do not warn - aMSR used in asm code */
	
   /* Added by Kobler 2003.05.02:
	* Because we will call printf, which is part of the MSL_C library, we have to
 	* enable the FP and Altivec bit in the MSR, when the MSL_C library has been built
 	* with Hardware  floating point and Altivec enabled in the compiler
 	* otherwise this would lead to some exceptions
 	*/	
	asm{	
   	/*
	* If we are using 5xx processors we need to make sure to enable
 	* the RI bit in the  MSR in order to be able to stop at hw breakpoints
 	*/	
#if ( defined( __PPC555__ ) || defined( __PPC56X__ ) )
	mfmsr aMSR
 	ori  aMSR,aMSR,0x00000002
 	mtmsr aMSR
 	sync	
#endif

	/*
	* If we are using Hardware  floating point we need to make sure
 	* to enable the FP bit in the  MSR
 	*/	
#if __option(floatingpoint)==1 &&  __option(sfp_emulation)==0
 	mfmsr aMSR
 	ori  aMSR,aMSR,0x00002000
 	mtmsr aMSR
 	sync
#endif

   /*
	* If we have selected Altivec Programming Model we need to make sure
 	* to enable the Altivec bit in the  MSR
 	*/	

#if __VEC__
 	mfmsr aMSR
	oris aMSR,aMSR,0x0200
 	mtmsr aMSR
 	sync
#endif	
	
#ifdef CACHE_VERSION
 	mfmsr aMSR
 	ori  aMSR,aMSR,0x00000030
 	mtmsr aMSR
 	sync
#endif
	}
	
	printf("InterruptHandler: 0x%x exception.\r\n", cause);
}
