
	_asm{
	.include "cpu.h"
   
   .extern time_isr
   .extern ppc5125IntrDemux



   .global ExtIntr  
   .global decIsr   


   .text

decIsr:
   
   prologue
   
   bl   time_isr                      

   epilogue                         
 
   rfi                                

  
ExtIntr:

   prologue               

   bl           ppc5125IntrDemux       

   epilogue                            

   rfi                                

  .end
}