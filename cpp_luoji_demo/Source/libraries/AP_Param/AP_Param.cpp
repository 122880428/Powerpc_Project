#include "AP_Param.h"
#include "..\..\drivers\sbus.h"
const unsigned long Param_RC_Min=0;
const unsigned long Param_RC_Max=0;
const unsigned char RC_param_addr=0; //这是遥控器相关参数的组，分配256个字节



extern Sbus _sbus;


void AP_Param_init(void)
{
	//NVram从0x02处开始存储。
unsigned char i = 0;
for (i = 0; i<16;i++)
    {	//每个数占了两个字节。
    _sbus._RC_max[i].setaddr(2*i+2);	//最小值存储在2~32处

    _sbus._RC_min[i].setaddr(2*i+36);	//最小值存储在34~66+1处
    }
}
