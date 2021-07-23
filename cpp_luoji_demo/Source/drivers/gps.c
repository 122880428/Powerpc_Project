#include "YN.h"

unsigned short GPSWeek;
unsigned long  GPSSec;
unsigned long  POS_TYPE;
unsigned char  tag_DGPS;
double lat_gps;
double lon_gps;
double alt_gps;
float  lon_delta;
float  lat_delta;
float  alt_delta;
unsigned char  used_gps;

double Vd_gps;
double psi_gps;
double Hdot_gps;
gpstime_t   gpstime;
float baseline_length;
float gps_heading;
float gps_pitch;
float hdg_std_dev;
float ptch_std_dev;

SensorStruc  gps;

static unsigned char gps_flag = 0;


    
/*---------------------------------------------------------------------------*/


/*
函数介绍：gps初始化操作
函数实现：
输入参数：com2_mode_422_232--串口2工作模式，com3_mode_422_232--串口3工作模式
返回值：无
注意事项：无
*/
void  GPS_Init(unsigned char com2_mode_422_232,unsigned char com3_mode_422_232)
{
     *(volatile unsigned short *)(GPSCOM2ADDR)  = com2_mode_422_232;
     *(volatile unsigned short *)(GPSCOM3ADDR)  = com3_mode_422_232;
}

unsigned long  CRC32Value(int i)
{	
    int j;
    unsigned long ulCRC;
	
    ulCRC=i;
    for(j=8;j>0;j--)
    {
        if(ulCRC & 1)
	    ulCRC=(ulCRC>>1)^CRC32_POLYNOMIAL;
	else
	    ulCRC>>=1;
    }
	
    return (ulCRC);
}


unsigned long CalculateBlockCRC32(unsigned long ulCount,unsigned char *ucBuffer) 
{
    unsigned long ulTemp1;
    unsigned long ulTemp2;
    unsigned long ulCRC = 0;
	
    while(ulCount-- != 0) 
    {	
        ulTemp1 = (ulCRC >> 8) & 0x00FFFFFFL;
	ulTemp2 = CRC32Value(((int)ulCRC ^*ucBuffer++) & 0xff);		
	ulCRC   = ulTemp1^ulTemp2;
     }
	
     return (ulCRC);
}

/*
函数介绍：GPS时间、定位状态、经纬度解码
函数实现：
输入参数：tmp[]--GPS接收数据包
返回值：无
注意事项：无
*/
void GPS_Msg42Rx(unsigned char tmp[])   
{
  
    dDWordStruc src;
    
    src.B[1]=tmp[14];src.B[0]=tmp[15];
    GPSWeek = src.W[0];

    src.B[3]=tmp[16];src.B[2]=tmp[17];src.B[1]=tmp[18];src.B[0]=tmp[19];
    GPSSec  = src.UDW[0];
	
    src.B[3]=tmp[32];src.B[2]=tmp[33];src.B[1]=tmp[34];src.B[0]=tmp[35];
    POS_TYPE = src.UDW[0];

    if(POS_TYPE>=48)
        tag_DGPS=1;
    else 
        tag_DGPS=0;
	
    if(gps_flag)
    {
        src.B[7]=tmp[36];src.B[6]=tmp[37];src.B[5]=tmp[38];src.B[4]=tmp[39];
	src.B[3]=tmp[40];src.B[2]=tmp[41];src.B[1]=tmp[42];src.B[0]=tmp[43];

	lat_gps = src.df;

	src.B[7]=tmp[44];src.B[6]=tmp[45];src.B[5]=tmp[46];src.B[4]=tmp[47];
	src.B[3]=tmp[48];src.B[2]=tmp[49];src.B[1]=tmp[50];src.B[0]=tmp[51];

	lon_gps = src.df;

	src.B[7]=tmp[52];src.B[6]=tmp[53];src.B[5]=tmp[54];src.B[4]=tmp[55];
	src.B[3]=tmp[56];src.B[2]=tmp[57];src.B[1]=tmp[58];src.B[0]=tmp[59];

	alt_gps = src.df;  
		
    }
	
    src.B[3]=tmp[68];src.B[2]=tmp[69];src.B[1]=tmp[70];src.B[0]=tmp[71];
    lon_delta= src.f[0];

    src.B[3]=tmp[72];src.B[2]=tmp[73];src.B[1]=tmp[74];src.B[0]=tmp[75];
    lat_delta = src.f[0];

    src.B[3]=tmp[76];src.B[2]=tmp[77];src.B[1]=tmp[78];src.B[0]=tmp[79];
    alt_delta= src.f[0];

    used_gps=tmp[93];	
	
    if(used_gps>5)
        gps_flag=1;	
    else	
        gps_flag=0;
}

/*
函数介绍：GPS速率、航向、日期解码
函数实现：
输入参数：tmp[]-GPS接收数据包
返回值：无
注意事项：无
*/
void  GPS_Msg99Rx (unsigned char tmp[])
{
    dDWordStruc src;
    
    if(gps_flag)
    {
        src.B[7]=tmp[44];src.B[6]=tmp[45];
	src.B[5]=tmp[46];src.B[4]=tmp[47];
	src.B[3]=tmp[48];src.B[2]=tmp[49];
	src.B[1]=tmp[50];src.B[0]=tmp[51];     
		
        Vd_gps = src.df;

	src.B[7]=tmp[52];src.B[6]=tmp[53];
	src.B[5]=tmp[54];src.B[4]=tmp[55];
	src.B[3]=tmp[56];src.B[2]=tmp[57];
	src.B[1]=tmp[58];src.B[0]=tmp[59];   
		
        psi_gps = src.df;

	src.B[7]=tmp[60];src.B[6]=tmp[61];
	src.B[5]=tmp[62];src.B[4]=tmp[63];
	src.B[3]=tmp[64];src.B[2]=tmp[65];
	src.B[1]=tmp[66];src.B[0]=tmp[67];   
		
        Hdot_gps = src.df;
	
    }
    

}

/*
函数介绍：GPS年、月、日、时、分、秒解码
函数实现：
输入参数：tmp[]-GPS接收数据包
返回值：无
注意事项：无
*/
void  GPS_timeRx (unsigned char tmp[])
{

    dWordStruc src;
    
    src.B[3]=tmp[56];src.B[2]=tmp[57];src.B[1]=tmp[58];src.B[0]=tmp[59];
    gpstime.year   = src.UDW;

    gpstime.month  = tmp[60];
    gpstime.day    = tmp[61];
    gpstime.hour   = tmp[62];
    gpstime.minute = tmp[63];
    src.B[3]=tmp[64];
    src.B[2]=tmp[65];
    src.B[1]=tmp[66];
    src.B[0]=tmp[67];
    gpstime.second = src.UDW/1000;

    printf(" gpstime.second = %d\n\r", gpstime.second);  
	

}

/*
函数介绍：GPS航线、航向、俯仰角、hdg标准差度、俯仰角标准差度
函数实现：
输入参数：tmp[]-GPS接收数据包
返回值：无
注意事项：无
*/
void GpsHeadingRx(unsigned char tmp[])   
{
    dWordStruc src;

    src.B[0]=tmp[39];src.B[1]=tmp[38];src.B[2]=tmp[37];src.B[3]=tmp[36];
    baseline_length = src.f;      /*[baseline] */
			
    src.B[0]=tmp[43];src.B[1]=tmp[42];src.B[2]=tmp[41];src.B[3]=tmp[40];
    gps_heading = src.f;          /* [heading0~360��˳ʱ��] */

			
    src.B[0]=tmp[47];src.B[1]=tmp[46];src.B[2]=tmp[45];src.B[3]=tmp[44];
    gps_pitch = src.f;           /* [pitch-90~90��] */
	
    src.B[0]=tmp[55];src.B[1]=tmp[54];src.B[2]=tmp[53];src.B[3]=tmp[52];
    hdg_std_dev =  src.f;        /* [hdg��׼�� ��] */
	
    src.B[0]=tmp[59];src.B[1]=tmp[58];src.B[2]=tmp[57];src.B[3]=tmp[56];
    ptch_std_dev =  src.f;       /* [pitch��׼���] */

 /*   printf("gps_heading = %f\n\r",gps_heading);  */

}

/*
函数介绍：接收GPS数据
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void  Task_GpsRev(void)
{
    unsigned char  rxBufferLen,numread;
    unsigned char  buff[256],temp[256];
    unsigned char  DGPS42[104], DGPS99[76];
    unsigned char  head=0,tail=0,prt=0,len,idx;
    unsigned long  crc32;
    unsigned char  tmp,tmp1,tmp2,tmp3,tmp4,tmp5;
    dWordStruc src;

    while(1)
    {
        //OSTimeDly(5);
        rxBufferLen=PPC_ComRxLen(COM2);
        numread=rxBufferLen>180 ? 180:rxBufferLen;
        
        if(numread)
            PPC_ComIn(COM2,temp,numread);
        for (idx=0; idx<numread; idx++) 
            buff[head++]=temp[idx];	            
  	 
        len = head-tail; 
		
        while (len>= sizeof(DGPS99))
        { 
	    tmp=tail;tmp1=tail+1;tmp2=tail+2;tmp3=tail+3;tmp4=tail+4;tmp5=tail+5;
            if((buff[tmp]==0xAA) && (buff[tmp1]==0x44) && (buff[tmp2]==0x12) && (buff[tmp3]==0x1C) && (buff[tmp4]==0x2A) && (buff[tmp5]==0x00))
            {             
		if(len>=sizeof(DGPS42))
		{
	            prt=tail;                        
		    for (idx=0;idx<sizeof(DGPS42);idx++) 
                        DGPS42[idx]=buff[prt++];
		    crc32=CalculateBlockCRC32(sizeof(DGPS42)-4,DGPS42);
		    src.B[3]=DGPS42[100];src.B[2]=DGPS42[101];src.B[1]=DGPS42[102];src.B[0]=DGPS42[103];

           	    if (crc32==src.DW)
           	    {          	        
           	        GPS_Msg42Rx(DGPS42); 	   	
           	   	tail=tail+sizeof(DGPS42);  
                                           
           	    }
           	    else tail++;		
	      }
	      else break;
         } 
	 else if((buff[tmp]==0xAA) && (buff[tmp1]==0x44) && (buff[tmp2]==0x12) && (buff[tmp3]==0x1C) && (buff[tmp4]==0x63) && (buff[tmp5]==0x00))
	 {
             prt=tail;                        
             for (idx=0;idx<sizeof(DGPS99);idx++) 
                 DGPS99[idx]=buff[prt++];
	     crc32=CalculateBlockCRC32(sizeof(DGPS99)-4,DGPS99);
	     src.B[3]=DGPS99[72];src.B[2]=DGPS99[73];src.B[1]=DGPS99[74];src.B[0]=DGPS99[75];
             if (crc32==src.DW)
             {  	
                 GPS_Msg99Rx(DGPS99); 	   	
           	 tail=tail+sizeof(DGPS99);
                 
             }
             else tail++;
	
	 }
         else if((buff[tmp]==0xAA) && (buff[tmp1]==0x44) && (buff[tmp2]==0x12) && (buff[tmp3]==0x1C) && (buff[tmp4]==0x65) && (buff[tmp5]==0x00))
         {    
             prt=tail;                        
	     for (idx=0;idx<sizeof(DGPS99);idx++) 
                 DGPS99[idx]=buff[prt++];
             crc32=CalculateBlockCRC32(sizeof(DGPS99)-4,DGPS99);
	     src.B[3]=DGPS99[72];src.B[2]=DGPS99[73];src.B[1]=DGPS99[74];src.B[0]=DGPS99[75];
             if (crc32==src.DW)
             {           	    	
                 GPS_timeRx(DGPS99); 	   	
           	 tail=tail+sizeof(DGPS99);                 
           	   	     
             }
             else tail++;
         }
         
         else if((buff[tmp]==0xAA) && (buff[tmp1]==0x44) && (buff[tmp2]==0x12) && (buff[tmp3]==0x1C) && (buff[tmp4]==0xFA)) 
         {
             prt=tail;
             for (idx=0;idx<sizeof(DGPS99);idx++) 
                 DGPS99[idx]=buff[prt++];
		 crc32=CalculateBlockCRC32(sizeof(DGPS99)-4,DGPS99);
		 src.B[3]=DGPS99[72];src.B[2]=DGPS99[73];src.B[1]=DGPS99[74];src.B[0]=DGPS99[75];
             if (crc32==src.DW)
             {  
            	 GpsHeadingRx(DGPS99); 
           	 tail=tail+sizeof(DGPS99);
                 gps.counter++;  
             }
             else tail++;
         	
         }

         else    tail++;         
         len = head-tail;
     }    
   }
        
}

/*
函数介绍：监控GPS数据状态
函数实现：
输入参数：无
返回值：无
注意事项：无
*/
void    GPS_Monitor(void)
{
    static unsigned short    flag=0, cnt=0, old=0;

    while(1)
    {

    //OSTimeDly(100);

    gps.invalid +=1;    if (gps.invalid>=20) gps.fail=1;

    cnt=(cnt+1)%100;    if ((cnt%10)==0) flag=1;
    if (flag) {  
        flag=0;
        gps.freq = gps.counter-old;  old=gps.counter;
    }

    }
}







