#ifndef INIT_MMU_CACHE_H
#define INIT_MMU_CACHE_H




#define DATA_CACHE_ON			1  // 1: on, 0: off
#define INSTRUCTION_CACHE_ON	1  // 1: on, 0: off

/*** BAT flags definition ***/
#define BAT_BL_128K 0x00000000
#define BAT_BL_256K 0x00000004
#define BAT_BL_512K 0x0000000C
#define BAT_BL_1M 0x0000001C
#define BAT_BL_2M 0x0000003C
#define BAT_BL_4M 0x0000007C
#define BAT_BL_8M 0x000000FC
#define BAT_BL_16M 0x000001FC
#define BAT_BL_32M 0x000003FC
#define BAT_BL_64M 0x000007FC
#define BAT_BL_128M 0x00000FFC
#define BAT_BL_256M 0x00001FFC
/* supervisor/user valid mode definitions - Upper BAT*/
#define BAT_VALID_SUPERVISOR 0x00000002
#define BAT_VALID_USER 0x00000001
#define BAT_INVALID 0x00000000
/* WIMG bit settings - Lower BAT */
#define BAT_WRITE_THROUGH 0x00000040
#define BAT_CACHE_INHIBITED 0x00000020
#define BAT_COHERENT 0x00000010
#define BAT_GUARDED 0x00000008
/* Protection bits - Lower BAT */
#define BAT_NO_ACCESS 0x00000000
#define BAT_READ_ONLY 0x00000001
#define BAT_READ_WRITE 0x00000002


/*** memory map 5121ADS ***/
#define NOR_FLASH_BASE 0xfe000000
#define NOR_FLASH_BAT_BL BAT_BL_32M
#define DDR_BASE 0x00000000
#define DDR_BAT_BL BAT_BL_256M 
#define IMMR_BASE  0x80000000
#define IMMR_BAT_BL  BAT_BL_128M

/*** BAT definition ***/

#define IBAT0L_VAL (NOR_FLASH_BASE|BAT_CACHE_INHIBITED|BAT_READ_WRITE)
#define IBAT0U_VAL (NOR_FLASH_BASE|BAT_VALID_SUPERVISOR|BAT_VALID_USER|NOR_FLASH_BAT_BL)
#define DBAT0L_VAL IBAT0L_VAL
#define DBAT0U_VAL IBAT0U_VAL

#define IBAT1L_VAL (DDR_BASE|BAT_READ_WRITE|BAT_WRITE_THROUGH)
#define IBAT1U_VAL (DDR_BASE|BAT_VALID_SUPERVISOR|BAT_VALID_USER|DDR_BAT_BL)
#define DBAT1L_VAL IBAT1L_VAL
#define DBAT1U_VAL IBAT1U_VAL

#define IBAT2L_VAL (IMMR_BASE|BAT_CACHE_INHIBITED|BAT_READ_WRITE)
#define IBAT2U_VAL (IMMR_BASE|BAT_VALID_SUPERVISOR|BAT_VALID_USER|IMMR_BAT_BL)
#define DBAT2L_VAL IBAT2L_VAL
#define DBAT2U_VAL IBAT2U_VAL

#define IBAT3L_VAL 0
#define IBAT3U_VAL 0
#define DBAT3L_VAL IBAT3L_VAL
#define DBAT3U_VAL IBAT3U_VAL




asm void mmu_cache_init();
asm void init_caches();
asm void EnableAndInvalidateDataCache();
asm void EnableAndInvalidateInstCache();
asm void init_bat_mmu();
asm void InvalidateBATs();
asm void InvalidateTLBs();
asm void AddrTranslationOff();
asm void FlushDataCache();
asm void DisableDataCache();
asm void DisableInstCache(); 

#endif

