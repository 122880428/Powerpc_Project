#include "YN.h"

ipwm_t SBUSIN[16];

static unsigned short RC_channels[16];

/*
函数描述：SBUS 解码函数
函数实现：
输入参数：buffer[] 源码数据
输出参数：
注意事项：
*/
void SBUS_Decode(unsigned char buffer[])
{
    /*
    移位操作优先级高于按位操作
    buffer[1]=0110 1110 buffer[2]=0111 1110 0x07FF=0000 0111 1111 1111;
    buffer[2]<<8=0111 1110 0000 0000;
    buffer[1] | buffer[2]<<8= 0000 0000 0110 1110 | 0111 1110 0000 0000 = 0111 1110 0110 1110;
    buffer[1] | buffer[2]<<8 & 0x07FF = 0111 1110 0110 1110 & 0000 0111 1111 1111 = 0000 0110 0110 1110
    */
    RC_channels[0]  = ((buffer[1]    |buffer[2]<<8)                 & 0x07FF);
    RC_channels[1]  = ((buffer[6]>>4 |buffer[7]<<4)                 & 0x07FF);
    RC_channels[2]  = ((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
    RC_channels[3]  = ((buffer[2]>>3 |buffer[3]<<5)                 & 0x07FF);
    RC_channels[4]  = ((buffer[5]>>1 |buffer[6]<<7)                 & 0x07FF);
    RC_channels[5]  = ((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
    RC_channels[6]  = ((buffer[9]>>2 |buffer[10]<<6)                & 0x07FF);
    RC_channels[7]  = ((buffer[10]>>5|buffer[11]<<3)                & 0x07FF);
    RC_channels[8]  = ((buffer[12]   |buffer[13]<<8)                & 0x07FF);
    RC_channels[9]  = ((buffer[13]>>3|buffer[14]<<5)                & 0x07FF);
    RC_channels[10] = ((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
    RC_channels[11] = ((buffer[16]>>1|buffer[17]<<7)                & 0x07FF);
    RC_channels[12] = ((buffer[17]>>4|buffer[18]<<4)                & 0x07FF);
    RC_channels[13] = ((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
    RC_channels[14] = ((buffer[20]>>2|buffer[21]<<6)                & 0x07FF);
    RC_channels[15] = ((buffer[21]>>5|buffer[22]<<3)                & 0x07FF); 

  


        SBUS_IN();

}


/*
函数描述：获取通道号
函数实现：
输入参数：channel 通道号
输出参数：temp--sbus 各通道数据值
注意事项：
*/
int GetChannel(int channel)
{
	int temp;
	if((channel>=1)&&(channel<=18))
	{
		temp = ((int)((RC_channels[channel - 1] -1000)*0.625 + 1505)); 
		return temp;
	}
	else return 0;
}

/*
函数描述：SBUS 接收函数
函数实现：
输入参数：
输出参数：
注意事项：
*/
void  SBUS_Rev(void)
{
    unsigned char     buf[256],tmp[25],FCCdata[25];
    unsigned char     head=0, tail=0,temp=0;
    unsigned char     ptr, len,idx;
    unsigned short    RxQueLen, numread;

    while(1)
    {
    	//OSTimeDly(5);
		
        RxQueLen=FComRxLen(FCOM9);

        numread=RxQueLen>25?25:RxQueLen;

        if (numread) 
            FComIn(FCOM9,tmp,numread);

        for(idx=0;idx<numread;idx++)
        { 
            buf[head++]=tmp[idx]; 
   
        }

        len=(head-tail);

        while (len>=sizeof(FCCdata)) 
        {
	    temp =(unsigned char)(tail+24);
            
            if((buf[tail]==0x0F) && ((buf[temp]==0x04)||(buf[temp]==0x14)||(buf[temp]==0x24)||(buf[temp]==0x34)))
            {
                ptr=tail; 
                for(idx=0;idx<sizeof(FCCdata);idx++)
                {
                     FCCdata[idx]=buf[ptr++];
                     buf[ptr] = 0;
                }
                SBUS_Decode(FCCdata);
                tail += sizeof(FCCdata); 
            }	
            else tail ++;
            
            len=(head-tail);			
        }
        
    }
  
}


/*
函数描述：获取 SBUS 通道的高电平
函数实现：
输入参数：
输出参数：
注意事项：
*/
void SBUS_IN(void)
{
    unsigned char  idx;    
    
    
    for(idx=0;idx<16;idx++)
    {
       SBUSIN[idx].pwmhi=(double)GetChannel(idx+1)/1000.0;	     	
    }

        
}

