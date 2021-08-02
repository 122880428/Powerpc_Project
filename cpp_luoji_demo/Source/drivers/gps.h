#ifndef __GPS__
#define __GPS__

#include "YN.h"

#define  CRC32_POLYNOMIAL 0xEDB88320L
#define  RS232    0
#define  RS422    1

#define  GPSCOM3ADDR  0x84001212
#define  GPSCOM2ADDR  0x84001412

typedef struct{
    unsigned long  year;   
    unsigned char  month;
    unsigned char  day;	
    unsigned char  hour;
    unsigned char  minute;
    unsigned char  second;	
}gpstime_t; 


extern unsigned short GPSWeek;
extern unsigned long  GPSSec;
extern unsigned long  POS_TYPE;
extern unsigned char  tag_DGPS;
extern double lat_gps;
extern double lon_gps;
extern double alt_gps;
extern float  lon_delta;
extern float  lat_delta;
extern float  alt_delta;
extern unsigned char  used_gps;

extern double Vd_gps;
extern double psi_gps;
extern double Hdot_gps;

extern gpstime_t   gpstime;

extern float baseline_length;
extern float gps_heading;
extern float gps_pitch;
extern float hdg_std_dev;
extern float ptch_std_dev;

extern  SensorStruc  gps;
    
/*---------------------------------------------------------------------------*/
void  GPS_Init(unsigned char com2_mode_422_232,unsigned char com3_mode_422_232);//gps��ʼ������
void  GPS_Msg42Rx(unsigned char tmp[]);//GPSʱ�䡢��λ״̬����γ�Ƚ���
void  GPS_Msg99Rx (unsigned char tmp[]);//GPS���ʡ��������ڽ���
void  GPS_timeRx (unsigned char tmp[]);//GPS�ꡢ�¡��ա�ʱ���֡������
void  GpsHeadingRx(unsigned char tmp[]);//GPS���ߡ����򡢸����ǡ�hdg��׼��ȡ������Ǳ�׼���
void  Task_GpsRev(void);//����GPS����
void  GPS_Monitor(void);//���GPS����״̬


#endif