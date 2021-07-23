
#######################################################################
#   INCLUDES
#######################################################################  

   .include "cpu.h"
   
   .extern time_isr
   .extern ppc5125IntrDemux


###################################################
#    Globally accessible symbols
###################################################

   .global ExtIntr  
   .global decIsr   

###################################################
#    Definitions 
###################################################

   .text

decIsr:
   
   prologue
   
   bl   time_isr                      # call decrement handler

   epilogue                           # Restore context
 
   rfi                                # run task 

  
ExtIntr:

   prologue               

   bl           ppc5125IntrDemux       # call handler given by macro parameter

   epilogue                            # Restore context

   rfi                                 # run task 

  .end
