#include "gcs.h"
#include "yn.h"
#include <string.h>
Gcs _gcs;

/**
 * 函数作用：处理下行数据  飞控向地面站发数据
 * 作者：皇陆亚
 * 时间：2021-07-31
 */
void Gcs::DataLinkDownLoadDataProc(void)
{
   /*static uint16_t sendindex=0;*/
    uint8_t i = 0;
    uint16_t crc=0; 
    //roll++;
	/*发送缓冲区赋值*/
	memset((void*)datalinksenddata,0,sizeof(datalinksenddata));/*/初始化为0*/
	datalinksenddata[0]=31;
	datalinksenddata[1]=0xAB;
	datalinksenddata[2]=0xCD;
	Sfloat32Toint82(roll,datalinksenddata+3,1e2);
	Sfloat32Toint82(pitch,datalinksenddata+5,1e2);
	Sfloat32Toint82(yaw,datalinksenddata+7,1e2);
 	Sfloat32Toint82(Pos[2],datalinksenddata+9,1e0);  /*/高度数据*/
 	Sfloat32Toint82(Vel[2],datalinksenddata+11,1e2); /*/z轴速度*/

	datalinksenddata[13]=datalink.senddatasubframeid;
	switch(datalinksenddata[13])
	{
		case 211:
		{	
			Sfloat32Toint82(Gyro[0],datalinksenddata+14,1e2);	        /*/滚转角速度*/
			Sfloat32Toint82(Gyro[1],datalinksenddata+16,1e2);			/*/俯仰角速度*/
			Sfloat32Toint82(Gyro[2],datalinksenddata+18,1e2);			/*/航向角速度*/
			Sfloat32Toint82(Acc[0],datalinksenddata+20,1e2);			/*/acc_X*/
			Sfloat32Toint82(Acc[1],datalinksenddata+22,1e2);			/*/acc_Y*/
			Sfloat32Toint82(Acc[2],datalinksenddata+24,1e2);			/*/acc_Z*/
			Sfloat32Toint82(Vel[0],datalinksenddata+26,1e2);			/*/x轴速度*/
			Sfloat32Toint82(Vel[1],datalinksenddata+28,1e2);			/*/y轴速度*/
		}
		break;
		
		case 212:
		{	
			Sfloat32Toint82(Pos[0],datalinksenddata+14,1e2);  /*/x轴位移*/
           	Sfloat32Toint82(Pos[1],datalinksenddata+16,1e2);  /*/y轴位移*/
		}
		break ;
		case 214:
		{
			Sfloat32Toint82(star_num,datalinksenddata+14,1e0); /*卫星数量*/
			datalinksenddata[14]=star_num;
			datalinksenddata[15]=0;
           	Sfloat32Toint82(gps_type,datalinksenddata+16,1e0);  /*卫星数量*/
			Sfloat32Toint82(hdop,datalinksenddata+18,1e0);      /*水平精度因子*/
		}
		break;

	}
	
	for( i = 3;i < 30; i++)
	{
		crc += datalinksenddata[i];
	}
	datalinksenddata[30]=crc&0xFF;
	datalinksenddata[31]=(crc>>8)&0xFF;
}
/**
 * 函数作用：处理数据id
 * 作者：皇陆亚
 * 时间：2021-07-31
 */
void Gcs::DataLinkSendDataPreProc(void)
{
 static uint16_t sendindex=0;
 switch(sendindex)
	{
		case 0:datalink.senddatasubframeid=211;sendindex++;break;
		case 1:datalink.senddatasubframeid=212;sendindex++;break;
		case 2:datalink.senddatasubframeid=214;sendindex++;break;
		default :datalink.senddatasubframeid=215;sendindex=0;break;
	}	
}


/**
 * 函数作用：初始化Fcom2
 * 作者：皇陆亚
 * 时间：2021-07-30
 * 返回值：NULL
 */
void Gcs::init()
{
	FComInit(FCOM2,115200,COM_PARITY_NONE,1,64,RS232);	//gcs
	init_flag = true;
}

/**
 * 函数作用：连接地面站通信
 * 作者：皇陆亚
 * 时间：2021-07-30
 * 返回值：如果运行出错会返回false
 */
bool Gcs::run()
{

	if(!init_flag)
	{
		printf("Gcs is not OK!\r\n");
		return false;
	}

	DataLinkSendDataPreProc();
    DataLinkDownLoadDataProc();
    FComOut(FCOM2,datalinksenddata,sizeof(datalinksenddata));/*通过串口向上位机发数据*/


	return true;
}

/**
 * 函数作用：将一个float数转化成两个int数并且存入到数组中
 * 作者：皇陆亚
 * 时间：2021-07-31
 * @param in   [要拆分的float数]
 * @param pout [要存入的数组]
 * @param mul  [放大倍数，如果不放大就是1]
 */
void Gcs::Sfloat32Toint82(float in,volatile uint8_t* pout,float mul) 
{
	int16_t temp;
	if(in>=0) temp=(int16_t)(in*mul+0.5f);
	else	  temp=(int16_t)(in*mul-0.5f);

	(*(pout+0))=(temp)&0xFF;
	(*(pout+1))=(temp>>8)&0xFF;
}

/**
 * 函数作用：
 * 作者：皇陆亚
 * 时间：2021-07-31
 * @param name 需要填入的数据含义
 * @param data 填入的数据值
 * 返回值：
 */
bool Gcs::set(string name,float data)
{
	/*************************/
	//皇：根据字符号去匹配，这样写起来确实不太高级的亚子。不过简单易懂


	if(!name.compare("roll"))
		{roll = data;return true;}
	if(!name.compare("pitch"))
		{pitch = data;return true;}
	if(!name.compare("yaw"))
		{yaw = data;return true;}
	if(!name.compare("accx"))
		{Acc[0] = data;return true;}
	if(!name.compare("accy"))
		{Acc[1] = data;return true;}
	if(!name.compare("accz"))
		{Acc[2] = data;return true;}
	if(!name.compare("gyrox"))
		{Gyro[0] = data;return true;}
	if(!name.compare("gyroy"))
		{Gyro[1] = data;return true;}
	if(!name.compare("gyroz"))
		{Gyro[2] = data;return true;}
	if(!name.compare("velx"))
		{Vel[0] = data;return true;}
	if(!name.compare("vely"))
		{Vel[1] = data;return true;}
	if(!name.compare("velz"))
		{Vel[2] = data;return true;}
	if(!name.compare("posx"))
		{Pos[0] = data;return true;}
	if(!name.compare("posy"))
		{Pos[1] = data;return true;}
	if(!name.compare("posz"))
		{Pos[2] = data;return true;}

	/*********************************/

	return false;

}
