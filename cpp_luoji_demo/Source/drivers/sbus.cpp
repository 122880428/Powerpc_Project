#include "YN.h"
#include "sbus.h"

extern bool id_ok;
Sbus _sbus;

/*
* 函数介绍：调试sbus解码时的打印函数
* 注意事项：不要在这里改变sbus的值。
*/
void Sbus::debug_sbus()
{
    int i;
    //unsigned short RC_channels_copy[16];
    //RC_channels_copy[16] =  RC_channels[16];
    //printf("CHANNEL1 is :%d\r\n",GetChannel(1));
    //printf("CHANNEL2 is :%d\r\n",GetChannel(2));
    //printf("CHANNEL1 is :%d\r\n",RC_channels[0]);
    //printf("CHANNEL4 is :%f\r\n",RC_channels[3]);
    for(i=1;i<15;i++)
    {
        if(RC_channels[i] != 0)
            printf("this is channel %d:%d\r\n",i,Get_Scaled_Channel(i));
        
    }
}


void Sbus::init(void)//皇：初始化串口
{
    FComInit(FCOM9,100000,COM_PARITY_EVEN,2,8,RS232);//皇：sbus是Fcom9，波特率10K，偶校验，2位停止位，232模式
    unsigned char i;    
    if(id_ok)
    {
       
        for(i = 0;i<16;i++)
        {
            _RC_min[i].load();
        //printf("_RC_min[%d]is:%d\r\n",i,_RC_min[i].get());
            _RC_max[i].load();
        //printf("_RC_max[%d]is:%d\r\n",i,_RC_max[i].get());
        }
    }
    else
    {
        for(i = 0;i<16;i++)
            _RC_min[i].set(1100);
            _RC_max[i].set(1900);
    }
    init_flag = true;

}
/**
 * 函数作用：sbus解码任务运行
 * 作者：皇陆亚
 * 时间：2021-07-30
 * 返回值：正常解帧会反回true
 */
bool Sbus::run(void)    //皇：用于接收遥控器信号
{
//RC_save_cal_val();
    RC_calc_monitor();
    
    //皇：利用unsigned char的范围是0~255，溢出后从0开始，构成循环数组
    static unsigned char    head=0, tail=0,temp=0;      
    static unsigned char    ptr, len,idx;
    static unsigned char    buf[256];
    unsigned char tmp[256],mid;
    unsigned char FCCdata[25];
    unsigned char RxQueLen, numread;    //皇：这里的接收数据长度也要和索引的类型一致，必须是0~255

    if (!init_flag)     //皇：如果没有完成初始化，直接返回。
    {
        printf("Sbus init is not OK!\r\n");
        return false;
    }

    RxQueLen=FComRxLen(FCOM9);
    numread = RxQueLen>255?255:RxQueLen;//皇：无符号的char范围是0~256，避免超出范围，但可能会截断数据
    if (numread) 
    {
        FComIn(FCOM9,tmp,numread);
        for(idx=0;idx<numread;idx++)
        { 
            buf[head++]=tmp[idx];   //皇：所有数据装载到buf里面
        }
    }
    else return 0;  //皇：没有数据的话直接返回就可以了
    
    len=(head-tail);

    while (len>=25) //皇：字节大于25时说明至少可以存一帧数据
    {
        temp =(unsigned char)(tail+24);
        
        if((buf[tail]==0x0F) && (buf[temp]==0x00))           //皇：这里的解码还不太严谨
        {

            ptr = tail; 
            for(idx=0;idx<25;idx++)     //皇：把这一帧的数据装载到FCCdata里面
            {
                FCCdata[idx] = buf[ptr];
                buf[ptr] = 0;
                ptr++;
            }
            Sbus_Decode(FCCdata);   //皇：解码
            Sbus_In();              //皇：各个通道值转换为pwm高电平时间
            tail = tail+25;         //解码之后tail+25
        }   
        else 
        {
            tail=tail+1;        //皇：如果不是帧头，就移动到下一个
        }
        
        len=(head-tail);        //皇：更新长度
    }//end while
    return true;
}

/**
 * 函数作用：
 * 作者：皇陆亚
 * 时间：2021-07-30
 * @param buffer [需要解包的一帧遥控器原始数据]
 * 返回值：空
 */
void  Sbus::Sbus_Decode(unsigned char buffer[]) //皇：解码部分
{
    unsigned char i = 0;

    for(i=0;i<15;i++)
        _last_rc_channels[i] = RC_channels[i];

    RC_channels[0]  = ((buffer[1]    |buffer[2]<<8)                 & 0x07FF);
    RC_channels[1]  = ((buffer[2]>>3 |buffer[3]<<5)                 & 0x07FF);
    RC_channels[2]  = ((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
    RC_channels[3]  = ((buffer[5]>>1 |buffer[6]<<7)                 & 0x07FF);
    RC_channels[4]  = ((buffer[6]>>4 |buffer[7]<<4)                 & 0x07FF);
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
    sbus_flag = buffer[23];
    if(sbus_flag & 0x10)        //失控了
    {
        //RC_channels_reset();
        failsafe_flag = true;
        printf("RC is failsafe!\r\n");
    }
    else if(sbus_flag & 0x20)   //丢包了
    {
       
    }
        failsafe_flag = false;

}

/**
 * 函数作用：各个通道值转换为pwm高电平时间
 * 作者：皇陆亚
 * 时间：2021-07-30
 * 返回值：NULL
 */
void  Sbus::Sbus_In(void)
{
    unsigned char  idx;    

    for(idx=0;idx<16;idx++)
    {
        SBUSIN[idx].pwmhi=(double)GetChannel(idx+1)/1000.0; 
    }
}

/*
* 函数介绍：获取SBUS某个通道值
* 函数实现：
* 输入参数：channel--通道号
* 返回值  ：temp--SBUS各通道数据值
* 注意事项：无
*/
int Sbus::GetChannel(int channel)
{
    int temp;
    if((channel>=1)&&(channel<=16))
    {
        temp = ((int)((RC_channels[channel - 1] -1024)*0.6 + 1500));    //皇：各个通道的值缩放到1100~1900
        return temp;
    }
    else return 0;
}
/*
* 函数介绍：获取SBUS某个通道上一次的值
* 函数实现：
* 输入参数：channel--通道号
* 返回值  ：temp--SBUS各通道数据值
* 注意事项：无
*/
int Sbus::GetLastChannel(int channel)
{
    int temp;
    if((channel>=1)&&(channel<=16))
    {
        temp = ((int)((_last_rc_channels[channel - 1] -1024)*0.6 + 1500));    //皇：各个通道的值缩放到1100~1900
        return temp;
    }
    else return 0;
}

/**
 * 函数作用：记录这一段时间遥控器的最大最小值
 * 作者：皇陆亚
 * 时间：2021-08-06
 */
void Sbus::RC_calculate(void)
{
    
if(_calculate_flag)
    {
        unsigned char i = 0;
        for (i = 0; i<16;i++)
        {
            if((_RC_min[i].get() > GetChannel(i+1) || _RC_min[i].get()<500))
                _RC_min[i].set(GetChannel(i+1));
            
            if(_RC_max[i].get()< GetChannel(i+1))
                _RC_max[i].set(GetChannel(i+1));
            
        }
        printf("RC_calculating......\r");
    }
}

/**
 * 函数作用：监控遥控器校准的命令
 * 作者：皇陆亚
 * 时间：2021-08-06
 */
void Sbus::RC_calc_monitor(void)
{
//这里用处理过的数据会出现一些小问题。后面不能通过遥控器来控制是否进入校准程序
//应该用原始数据的，但是原始数据我又记不得是多少了，也懒的回算了
    if((GetChannel(6)>1800)&& (GetChannel(6)<2000))     //六通道处于高位时启动校准         
        _calculate_flag = true;
    if((GetChannel(6)<1700)&& (GetLastChannel(6)>1800))  //六通道高位拨回中位时保存数据           
        RC_save_cal_val();
    RC_calculate();
}

void Sbus::RC_save_cal_val(void)
{
    unsigned char i = 0;
    for (i = 0; i<16;i++)
        {
            _RC_min[i].save();   
            _RC_max[i].save();
        }
    _calculate_flag = false;
}

/**
 * 函数作用：遥控器数值缩放到严格的1100~1900
 * 作者：皇陆亚
 * 时间：2021-08-07
 */
uint16_t Sbus::Get_Scaled_Channel(uint8_t channel)
{
    float temp;
    if((channel>=1)&&(channel<=16))
    {
        temp = (((RC_channels[channel - 1] -1024)*0.6 + 1500));    //皇：各个通道的值缩放到1100~1900
        temp = (temp-_RC_min[channel - 1].get())*800/(_RC_max[channel - 1].get()-_RC_min[channel - 1].get())+1100;
        return (uint16_t)temp;
    }
    else return 0;
}

/**
 * 函数作用：遥控器数据放到中位
 * 作者：皇陆亚
 * 时间：2021-08-07
 */
void Sbus::RC_channels_reset(void)
{
    unsigned char i = 0;
    for (i = 0; i<16;i++)
        {
            RC_channels[i] = 1024;
        }
    RC_channels[3-1] = 0;
}