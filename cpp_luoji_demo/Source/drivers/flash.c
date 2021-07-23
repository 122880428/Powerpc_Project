#include "flash.h"

/*
函数介绍：擦除扇区
函数实现：
输入参数：flashAdrs-地址
返回值：无
注意事项：无
*/
short EraseFlashSector(unsigned long flashAdrs)
 {
     short retVal = 0;
     volatile unsigned short data1, data2;
     
     if(flashAdrs>FLASH_END_ADDR)
     {
     	 retVal = -1;
     	 return(retVal);
     }
     
     flashAdrs = (flashAdrs/FLASH_SECTOR_SIZE)*FLASH_SECTOR_SIZE;
 
              
     *(volatile unsigned short *)(FLASH_CMD_1)  = 0xaaaa;
     *(volatile unsigned short *)(FLASH_CMD_2)  = 0x5555;
     *(volatile unsigned short *)(FLASH_CMD_1)  = 0x8080;
     *(volatile unsigned short *)(FLASH_CMD_1)  = 0xaaaa;
     *(volatile unsigned short *)(FLASH_CMD_2)  = 0x5555;          
     *(volatile unsigned short *)(flashAdrs)    = 0x3030;

     do
     {
        data1 = *(volatile unsigned short *)(flashAdrs);	
     	
     }
     while((data1&0x0808)==0);
     
     data1 = *(volatile unsigned short *)(flashAdrs);
     
     do
     {
      	data2 = data1;
        data1 = *(volatile unsigned short *)(flashAdrs);	
  
     } while ((data1&0x4444)!=(data2&0x4444));   
                 
     
     *(volatile unsigned short *) (FLASH_CMD_1)  = 0xaaaa;
     *(volatile unsigned short *) (FLASH_CMD_2)  = 0x5555;
     *(volatile unsigned short *) (FLASH_CMD_1)  = 0xf0f0;   
     
     return(retVal);
                
 }
 

/*
函数介绍：写数据
函数实现：
输入参数：pFB-地址指针，size-数据大小，offset-偏移地址
返回值：无
注意事项：无
*/
short ProgFlash(volatile unsigned short * pFB,unsigned long size,unsigned long offset)
{
    short retVal = 0;
    volatile unsigned short * pFA;       /* flash address */ 
    volatile unsigned short data1, data2;   
  
    for (pFA = (volatile unsigned short *) (offset); pFA < (volatile unsigned short *)
        (size + offset) ; pFA++)
        {
              if((unsigned long)(pFA)>FLASH_END_ADDR)
              {
     	          retVal = -1;
     	          return(retVal);
              }
             
             *(volatile unsigned short *)(FLASH_CMD_1)  = 0xaaaa;
             *(volatile unsigned short *)(FLASH_CMD_2)  = 0x5555;
             *(volatile unsigned short *)(FLASH_CMD_1)  = 0xa0a0;
                
             *pFA = *pFB;                      /* data to write */
           
             data1 = *pFA;
     
             do
             {
      	          data2 = data1;
                  data1 = *pFA;	
  
             } while ((data1&0x4040)!=(data2&0x4040));      
             
             data1 = *pFA;
             
             do
             {   
                  data2 = data1;            	   
                  data1 = *pFA;
             } while ((data1 !=  *pFB) || (data2 !=  *pFB)); 
              
              pFB++;
              
         *(volatile unsigned short *) (FLASH_CMD_1)  = 0xaaaa;
         *(volatile unsigned short *) (FLASH_CMD_2)  = 0x5555;
         *(volatile unsigned short *) (FLASH_CMD_1)  = 0xf0f0; 
         }

         
         return(retVal);
 } 
 

/*
函数介绍：读数据
函数实现：
输入参数：offset-偏移地址
返回值：无
注意事项：无
*/
unsigned short ReadFlash(unsigned long offset)
{
    return (*(volatile unsigned short *)(offset));
}



