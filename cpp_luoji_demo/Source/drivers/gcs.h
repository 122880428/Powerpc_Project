#ifndef __GCS_H
#define __GCS_H
#include <iostream>
#include <stdint.h>
#include <string>
using namespace std;
class Gcs
{
private:
	bool init_flag;//皇：初始化标志
	//皇：最终发送的数据包
	unsigned char datalinksenddata[32];
	//struct DATALINK datalink;


/*一些临时数据，最终是要存在datalinksenddata[32]里面的*/
	float roll;
	float pitch;
	float yaw;
	float Acc[3];
	float Gyro[3];
	float Vel[3];
	float Pos[3];
	uint8_t star_num ; /*卫星数量*/
	float hdop;       /*mti 水平位置精度因子*/
	uint8_t gps_type;/*GPS定位状态 0- No Fix;1-Dead Reckoning only;2- 2D-Fix;3-3D-Fix;4- GNSS + dead reckoning combined*/

struct DATALINK
{
	/*uint8_t 	isready;*/
	/*uint8_t 	recvdatasubframeid;*/
	uint8_t	senddatasubframeid;
/*	uint16_t 	upsignaltotalcount;
	uint16_t 	upsignalgoodcount;
	uint16_t 	upsignalquality;
	uint32_t 	nosignalcount;
	struct	HEADER	header;*/
}datalink;

/****************************************/


	void Sfloat32Toint82(float in,volatile uint8_t* pout,float mul);
	void DataLinkSendDataPreProc(void);
	void DataLinkDownLoadDataProc(void);

public:
	Gcs()//皇：c++98的标准不支持成员变量设置缺省值，需要在构造函数处初始化。
	{
		init_flag = false;
		roll= 0;
		pitch = 0;
		yaw = 0;
		Acc[0] = 0;
		Acc[1] = 0;
		Acc[2] = 0;
		Gyro[0] = 0;
		Gyro[1] = 0;
		Gyro[2] = 0;
		Vel[0] = 0;
		Vel[1] = 0;
		Vel[2] = 0;
		Pos[0] = 0;
		Pos[1] = 0;
		Pos[2] = 0;
		star_num = 0; /*卫星数量*/
		hdop = 0;       /*mti 水平位置精度因子*/
		gps_type = 0;/*GPS定位状态 0- No Fix;1-Dead Reckoning only;2- 2D-Fix;3-3D-Fix;4- GNSS + dead reckoning combined*/
	}

	~Gcs(){};
	void init();
	bool run();
	bool set(string name,float data);

};
#endif 