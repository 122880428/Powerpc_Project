
#include "init_mmu_cache.h"

//----------------------------------------------------------------------------
//                                                                       
//  DESCRIPTION: 
//                                                                       
//  This file contains the initialization software for:
//
//   - Dcache (Data Cache) and Icache (Instruction Cache).
//
//   - MMU (Memory Management Unit)
//
//
//----------------------------------------------------------------------------

asm void mmu_cache_init()
{
	nofralloc
	
   mfspr    r7,LR        // Save the Link Register value. The link register's
                          // value will be restored so that this function 
                          // can return to the calling address.
   // Disable Caches
   bl		DisableInstCache
   bl		DisableDataCache
   
   // Initialize MMU
   bl       init_bat_mmu

   // Initialize Instruction and Caches
   bl       init_caches
   
//   bl       AddrTranslationOn

   mtspr    LR,r7      // restore original Link Register value 

   bclr     20,0        // jump unconditionally to effective address in Link
                        // register
};

asm void init_caches()
{
   nofralloc

   mfspr    r8,LR        // Save the Link Register value

   // Enable the Instruction Cache 
   bl    EnableAndInvalidateInstCache

   // Enable the Data Cache 
   bl    EnableAndInvalidateDataCache

   mtspr    LR,r8      // restore original Link Register value 

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}



//###########################################################################
// Function: EnableAndInvalidateDataCache
//
// Description: This function is used to initialize the Data cache to a start
//              state. This is done by ensuring that data cache is enabled by
//              explicitly enabling it and invalidating all cache lines or 
//              blocks. Note that by executing this function, all modified
//              blocks will be destoyed.
//########################################################################        

asm void EnableAndInvalidateDataCache()
{
   nofralloc

#if DATA_CACHE_ON
//	invalidate_enable_L1_dcache
            
   mfspr r5,HID0         
   ori   r5,r5,0x4400   // Set DCE and DCFI bit
   sync
   mtspr hid0, r5
   lis r4, 0xffff
   ori r4,r4,0xfbff
   and r5, r5, r4      // Clear the DCFI bit
   sync
   mtspr hid0, r5

#endif

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}


//###########################################################################
// Function: EnableAndInvalidateInstCache
//
// Description: This function first enables the instruction cache and then
//              sets the instruction cache flash invalidate (ICFI) bit in 
//              the HID0 register. This establishes a start state for the 
//              cache.
//
//########################################################################        

asm void EnableAndInvalidateInstCache()
{
   nofralloc

#if INSTRUCTION_CACHE_ON

   //	invalidate_enable_L1_icache
   mfspr r5,HID0        
   ori   r5,r5,0x8800   // Set the ICE and ICFI bit
   sync
   mtspr hid0, r5
   lis   r4, 0xffff
   ori   r4,r4,0xf7ff
   and   r5, r5, r4      // Clear the ICFI bit
   sync
   mtspr hid0, r5

#endif

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}




//########################################################################
// Function: init_bat_mmu
//
// Description: In the process of determining the physical address from the
//              effective address, there are 3 paths/modes that can be 
//              taken. 
//
//              The first is the Real Address mode where the effective
//              address is equal to the physical address. In this mode, the
//              MMU is turned off and as a default, instruction and data
//              cacheing are enabled for all physical addresses as part of
//              the default WIMG value. The IMMR address space as well as 
//              some I/O space must be data cache inhibited. Data cache must
//              be turned completely off by ensuring that HID0[DCE] is 
//              cleared. HID0[ICE] still needs to be set during instruction
//              cache initializtion.
//
//              The second is Block Address Translation. This MMU mode offers
//              memory characterization and control on blocks of memory from
//              128 Kbyte to 256 Mbytes in size. The drawback to this mode
//              is the limited number of blocks that can be considered in 
//              the translation process. The MPC8260 only offers 4 different
//              blocks of memory that can be managed. That is, 4 blocks for
//              data and 4 for instructions.
//
//              The last mode is Page Address Translation. This mode is the
//              most complicated and offers the finest granularity in terms
//              memory management. Pages are 4 Kbytes in size and can be 
//              managed with the ability to operate in a virtual memory space
//              as far as the application/operating system software is 
//              conserned. This virtual space is expanded from 2^32 bytes to 
//              2^52 bytes. Page Address Translation is useful for operating 
//              systems that need to swap out tasks or programs from disk 
//              storage which need to run in the same physical memory space. 
//              This swapping requires searching tables and developing soft-
//              ware for interrupt routines to insert new Page Table entries 
//              when the effective address is not found in the on-chip Page 
//              Translation table. Software is also required to do the 
//              task/program swapping as well.
//
//              This example does not require the complexity of page 
//              translation yet we still want to take advantage of memory
//              management. Block Address Translation is our choice. 
//
//              The Block Address Translation (BAT) registers will be 
//              allocated in the following manner:
//
//                 -> IBAT0 and DBAT0 - 60x SDRAM 
//
//                       - Read/Write capability
//                       - Write-Through is disabled.
//                       - Cacheing enabled
//                       - No requirements to enforce memory coherency.
//                       - Address space is unguarded
//
//                 -> DBAT1 - PCI
//
//                       - Read/Write capability
//                       - Write-Through is disabled. 
//                       - Cacheing disabled
//                       - No requirements to enforce memory coherency.
//                       - Address space is unguarded
//
//                 -> DBAT2 - Board Status and Control Registers 0-2
//                          - Internal Memory Map Registers (IMMR) space
//
//                       - Read/Write capability
//                       - Write-Through is enabled. 
//                       - Cacheing disabled
//                       - No requirements to enforce memory coherency.
//                       - Address space is unguarded
//
//                 -> IBAT3 and DBAT3- Flash ROM memory (8 Mbyte)
//
//                       - Read/Write capability. The ability to write has
//                         been added for flash reprogramming.
//                       - Write-Through is enabled
//                       - Instruction Cacheing enabled. Data Cacheing 
//                         disabled.
//                       - No requirements to enforce memory coherency.
//                       - Address space is unguarded
//
//########################################################################        

asm void init_bat_mmu()
{
   nofralloc

   mfspr    r9,LR        // Save the Link Register value. The link register's
                          // value will be restored so that this function 
                          // can return to the calling address.

   // Turn off the address translation
   bl	AddrTranslationOff
   
   // The 603e BAT registers are not initialized by the hardware after the 
   // power-up or reset sequence. Consequently, all valid bits in both 
   // instruction and data BAT areas must be cleared before setting any BAT 
   // area for the first time. This is true regardless of whether address 
   // translation is enabled. 
   bl    InvalidateBATs    // clear the valid bits on all 8   

   // Invalidate all TLB entries: This needs to be done because Translation
   // Lookaside Buffers valid bits are undefined at reset. The MMU comes out 
   // of reset disabled but if the MMU were enabled and TLB's were not 
   // invalidated first, erratic behavior would result.
   bl InvalidateTLBs      // Invalidate all TLBs

   //	setup_ibats
		addis  r0, r0, 0x0000
		addis  r4, r0, IBAT0L_VAL@h
		ori    r4, r4, IBAT0L_VAL@l
		addis  r3, r0, IBAT0U_VAL@h
		ori    r3, r3, IBAT0U_VAL@l
		mtspr  ibat0l, r4
		mtspr  ibat0u, r3
		isync

		addis  r4, r0, IBAT1L_VAL@h
		ori    r4, r4, IBAT1L_VAL@l
		addis  r3, r0, IBAT1U_VAL@h
		ori    r3, r3, IBAT1U_VAL@l
		mtspr  ibat1l, r4
		mtspr  ibat1u, r3
		isync

		addis  r4, r0, IBAT2L_VAL@h
		ori    r4, r4, IBAT2L_VAL@l
		addis  r3, r0, IBAT2U_VAL@h
		ori    r3, r3, IBAT2U_VAL@l
		mtspr  ibat2l, r4
		mtspr  ibat2u, r3
		isync

		addis  r4, r0, IBAT3L_VAL@h
		ori    r4, r4, IBAT3L_VAL@l
		addis  r3, r0, IBAT3U_VAL@h
		ori    r3, r3, IBAT3U_VAL@l
		mtspr  ibat3l, r4
		mtspr  ibat3u, r3
		isync


   // 	setup_dbats
		addis  r0, r0, 0x0000
		addis  r4, r0, DBAT0L_VAL@h
		ori    r4, r4, DBAT0L_VAL@l
		addis  r3, r0, DBAT0U_VAL@h
		ori    r3, r3, DBAT0U_VAL@l
		mtspr  dbat0l, r4
		mtspr  dbat0u, r3
		isync
		
		addis  r4, r0, DBAT1L_VAL@h
		ori    r4, r4, DBAT1L_VAL@l
		addis  r3, r0, DBAT1U_VAL@h
		ori    r3, r3, DBAT1U_VAL@l
		mtspr  dbat1l, r4
		mtspr  dbat1u, r3
		isync
		
		addis  r4, r0, DBAT2L_VAL@h
		ori    r4, r4, DBAT2L_VAL@l
		addis  r3, r0, DBAT2U_VAL@h
		ori    r3, r3, DBAT2U_VAL@l
		mtspr  dbat2l, r4
		mtspr  dbat2u, r3
		isync

		addis  r4, r0, DBAT3L_VAL@h
		ori    r4, r4, DBAT3L_VAL@l
		addis  r3, r0, DBAT3U_VAL@h
		ori    r3, r3, DBAT3U_VAL@l
		mtspr  dbat3l, r4
		mtspr  dbat3u, r3
		isync

 //	instruction_address_translation_on
		mfmsr  r5
		ori    r5, r5, 0x0020
		mtmsr  r5
		isync

//	data_address_translation_on
		mfmsr  r5
		ori    r5, r5, 0x0010
		mtmsr  r5
		isync

   

   mtspr    LR,r9      // restore original Link Register value 

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}

//########################################################################
// Function: AddrTranslationOff
//
// Description: This function will clear the instruction address translation
//				bit in MSR and the data address translation bit in MSR
//
//########################################################################        

asm void AddrTranslationOff()
{
   nofralloc

   //	instruction_address_translation_off
   mfmsr  r5
   li	  r4, 0xFFDF	
   and    r5, r5, r4 // clear address data translation bit in MSR
   mtmsr  r5
   isync

   //	data_address_translation_off
   mfmsr  r5
   li	  r4, 0xFFEF
   and    r5, r5, r4 // clear instruction data translation bit in MSR
   mtmsr  r5
   isync

   bclr     20,0        // jump unconditionally to effective address in Link
                        // register
}


//########################################################################
// Function: InvalidateBATs
//
// Description: This function will clear the Vp and Vs bits. These bits are
//              both valid bits and the one that is checked during the 
//              translation process depends on the state of the MSR[PR]
//              bit. Here's the rule:
//
//                 MSR[PR] = 0 corresponds to supervisor mode; in this mode,
//                 Vs is checked.
//
//                 MSR[PR] = 1 corresponds to user mode; in this mode, Vp
//                 is checked.
//
//              Both bits will be cleared in all 4 IBAT and all 4 DBAT
//              registers because the state of these bits are not
//              guaranteed upon power-up reset.
//
//########################################################################        

asm void InvalidateBATs()
{
   nofralloc


   addis    r0,0,0      // load 0 into R0

   isync
   mtspr    DBAT0U,r0   // Data bat register 0 upper
   isync
   mtspr    DBAT1U,r0   // Data bat register 1 upper
   isync
   mtspr    DBAT2U,r0   // Data bat register 2 upper
   isync
   mtspr    DBAT3U,r0   // Data bat register 3 upper
   isync

   mtspr    IBAT0U,r0   // Instruction bat register 0 upper
   isync
   mtspr    IBAT1U,r0   // Instruction bat register 1 upper
   isync
   mtspr    IBAT2U,r0   // Instruction bat register 2 upper
   isync
   mtspr    IBAT3U,r0   // Instruction bat register 3 upper
   isync

   bclr     20,0        // jump unconditionally to effective address in Link
                        // register
}



//###########################################################################
// Function: InvalidateTLBs
//
// Description:
//
//  All 32 TLBs are invalidated. The tlbie instruction will clear the valid
//  bit for each TLB entry. Each TLB entry is indexed by effective address
//  A15 through A19. This example is not using the PowerPC instruction
//  tlbia because the 603 core does not support it. So traversing through all
//  32 entries is the only method.
//
//########################################################################        

asm void InvalidateTLBs()
{
   nofralloc


   //-----------------------------------------------------------------------
   // Loop 32 times, incrementing effective address A15-A19 using the tlbie
   // mnemonic. 
   //-----------------------------------------------------------------------

   addi     r5,0,32
   mtspr    CTR,r5            // Load CTR with 32. 

   addi     r3,0,0            // Use r3 as the tlb index
      
tlb_write_loop:

   tlbie    r3                // invalidate the tlb entry
   sync
   addi     r3,r3,0x1000      // increment the index
    
   bc       16,0,tlb_write_loop   // Decrement CTR, then branch if the 
                                  // decremented CTR is not equal to 0      


   bclr  20,0    // jump unconditionally to effective address in Link
                 // register
}


//###########################################################################
// Function:  FlushDataCache
//
// Description: This function flushes the data cache. For the 603ev, there is 
//              no direct way to do this. The blocks/cache lines cannot be 
//              flushed incrementally in a direct fashion unless all effective
//              addresses cached are known in the data cache. Since this is  
//              too difficult to know, this function will traverse through all 
//              possible effective addresses in the user data space in 
//              external memory with a dcbf (data cache block flush) mnemonic.
//              In this way, no data location will be missed.
//
// History:
//
// 1/9/99    Initial    jay  
//
//########################################################################        

asm void FlushDataCache()
{
   nofralloc


	addis    r3,0,0         // Load the start address of 0x00000000

   //--------------------------------------------------------------------
   // I chose a RAM address of 0x00013000 because I figure that my data 
   // requirements won't exceed this memory limit.
   //--------------------------------------------------------------------

	addis    r5,0,0x0001      
   addi     r5,r5,0x3000   // Load the end address of 0x00013000

FlushAgain:

	cmp	   cr0,0,r3,r5         // Compare 2 unsigned words
	bge	   FlushDone         // go to done

   //--------------------------------------------------------------------
   // flush the next effective address if it exists in the cache. If it 
   // doesn't, the flush command will be ignored. If it does, the block 
   // value will be copied back to RAM and the block will be invalidated.
   //---------------------------------------------------------------------

   dcbf     0,r3              

	addi	   r3,r3,0x4         // increment by a word
	b	      FlushAgain        // repeat

FlushDone:

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}


//###########################################################################
// Function: DisableDataCache
//
// Description: This function disables the data cache only by clearing the 
//              DCE bit in the HID0 register and setting DCFI bit. Note that
//				by executing this function, all modified blocks will be destroyed.
//
//########################################################################        

asm void DisableDataCache()
{
   nofralloc

   mfspr  r5,hid0
   ori    r5,r5,0x0400		// set hid0 DCFI bits
   sync
   mtspr  hid0,r5
   lis	  r4, 0xffff
   ori	  r4, r4, 0xbfff
   and    r5, r5, r4    	// clear hid0 DCE bit
   sync
   mtspr  hid0,r5

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}


//###########################################################################
// Function:  DisableInstCache
//
// Description: This function disables the instruction cache by clearing the
//              ICE bit in the HID0 register and sets ICFI bit in HID0
//
//########################################################################        

asm void DisableInstCache()
{
   nofralloc

   mfspr  r5, hid0
   ori    r5, r5, 0x0800   // set hid0 ICFI bit
   isync
   mtspr  hid0, r5
   lis	  r4, 0xffff
   ori	  r4, r4, 0x7fff
   and    r5, r5, r4	// clear hid0 ICE bit
   isync
   mtspr  hid0, r5

   bclr  20,0           // jump unconditionally to effective address in Link
                        // register
}


