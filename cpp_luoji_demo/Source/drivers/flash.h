#ifndef _FLASH_H
#define _FLASH_H


#define FLASH_BASE_ADDR  0xFE000000   /*0xFE000000--0xFF000000*/
#define FLASH_END_ADDR   0xFEFFFFFF
#define FLASH_CMD_ADDRESS_1  0x555  
#define FLASH_CMD_ADDRESS_2  0x2aa  
#define FLASH_CMD_1    (FLASH_BASE_ADDR + FLASH_CMD_ADDRESS_1*2)
#define FLASH_CMD_2    (FLASH_BASE_ADDR + FLASH_CMD_ADDRESS_2*2)


#define FLASH_SECTOR_SIZE         (0x20000)

short  EraseFlashSector(unsigned long flashAdrs);//��������
short ProgFlash(volatile unsigned short * pFB,unsigned long size,unsigned long offset);//д����
unsigned short ReadFlash(unsigned long offset);//������



#endif