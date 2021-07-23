#include "YN.h"

mpxv_t  MPXV;
static  double ru;


void  Gravity(double altitude,double lat,double lon,double *g)
{
      double wgs_a,wgs_inv_f,wgs_omega_default,wgs_gm_default,wgs_gamma_e,wgs_k,wgs_e2,wgs_b;
      double sinlam,sin2lam,gamma_ts,m;

      wgs_a = 6378137.0;
      wgs_inv_f = 298.257223563;
      wgs_omega_default = (7.292115/100000.0);
      wgs_gm_default = (3986004.418*100000000.0);
      wgs_gamma_e = 9.7803253359;
      wgs_k = 0.00193185265241;
      wgs_e2 = (6.69437999014/1000.0); 
      wgs_b = 6356752.3142;

      if(altitude < 0)
         altitude = 0;
      if(altitude > 200000.0)
         altitude = 200000.0;
 
      sinlam = sin(lat/180.0*3.1415926);
      sin2lam =  sinlam*sinlam;

      gamma_ts = wgs_gamma_e*(1.0 + wgs_k*sin2lam)/(sqrt(1.0 - wgs_e2*sin2lam));
      m = wgs_a*wgs_a*wgs_b*wgs_omega_default*wgs_omega_default/wgs_gm_default;      
      *g = gamma_ts*(1.0-2.0*(1.0 + 1.0/wgs_inv_f + m - 2.0*sin2lam/wgs_inv_f)*altitude/wgs_a + 3.0*altitude*altitude/wgs_a/wgs_a);
} 


void  CaculMpxvRu(double altitude, double *ru_temp)
{
    double temp;     
    
  /*  if(altitude<11000.0) 
    {
        temp=1-0.0225569*altitude/1000;
	*ru_temp = 0.12492*9.8*exp(4.255277*log(temp));
    }
    else 
    {
	temp=11-altitude/1000.0;
	*ru_temp = 0.03718*9.8*exp(temp/6.318);
    } */

    if(altitude<11000.0) 
    {
        temp=1.0-2.25577*altitude/100000.0;
	*ru_temp = 1.225*pow(temp, 4.25588);
    }
    else if(altitude<20000.0) 
    {
	temp=0.5208046-1.576855*altitude/10000.0;
	*ru_temp = 1.225*exp(temp);
    }
    else if(altitude<32000.0) 
    {
	temp=1.0+4.61574*(altitude-20000.0)/1000000.0;
	*ru_temp = 1.225*0.0718655037*pow(temp,-35.1632);
    } 
    else if(altitude<47000.0) 
    {
	temp=1.0+1.22458*(altitude-32000.0)/100000.0;
	*ru_temp = 1.225*0.010795897*pow(temp,-13.20115);
    } 
    else if(altitude<51000.0) 
    {
	temp=-0.822103547-1.262266*altitude/1000.0;
	*ru_temp = 1.225*exp(temp);
    } 
    else
    {
        temp=1.0-1.03455*(altitude-51000.0)/100000.0;
	*ru_temp = 1.225*0.000703347*pow(temp,11.20115);
    }

}

void  CaculMpxvHigh(double high_vol)
{
    MPXV.highPressure  = ((high_vol+0.060)/5.05 + 0.095)/0.009*1000.0;  
   
    /*大气压力（Pa A) =101325.0*(1-0.02257*海拔)^5.256*/
    MPXV.altitude = 1000.0/0.02257 * (1.0 - pow(MPXV.highPressure/101325.0, (1.0 / 5.256)));
}


void  CaculMpxvSpeed(double speed_vol) 
{ 

    CaculMpxvRu(MPXV.altitude,&ru);
   

    if(MPXV5004)
       MPXV.speedPressure =((speed_vol-0.095)/5.05 - 0.2)/0.2*1000.0;
    else
       MPXV.speedPressure =(speed_vol-2.5)*5.05/5.0*249.0889;  /*+-*/

    if(MPXV.speedPressure < 0.0)
        MPXV.speedPressure = 0.0;

    MPXV.speed = sqrt(2*MPXV.speedPressure/ru)*3.6;
    
    CaculMpxvVC();
		
}

void CaculMpxvVC(void)
{
   double p0,a0,fm,pp0,q1,q2,gg,em2,vc0,vc1,vc2;
   unsigned char k = 0;

   p0 = 101359.5687;
   a0 = 340.43;
   fm = MPXV.speed/3.6/a0;
   pp0 = MPXV.highPressure/p0;

   if(fm < 0.001)
   {
       MPXV.qc = 0;
       MPXV.vc = 0;
   } 
   else
   {
       if(fm > 1.0)
           q1 = (166.921* pow(fm,7.0)/pow((7.0*fm*fm-1.0),2.5)-1.0)*pp0; 
       else
           q1 = (pow((1.0+0.2*fm*fm),3.5)-1.0)*pp0;  
  
       if(q1 < 0.892929)
           vc2 = a0*sqrt(5.0*(pow((q1+1.0),2.0/7.0) -1.0));
       else
       {
           q2 = q1;
           gg = (q2 + 1.0)/166.921;
           vc0 = fm*MPXV.speed/3.6/a0;
           em2 = 7.0*vc0*vc0 -1.0;
           vc1 = vc0-em2*(pow(vc0,7.0)- gg*pow(em2,2.5)/(7.0*pow(vc0,6.0)*(2.0*vc0*vc0-1.0)));
           k = 0;
           while((abs(vc1-vc0)<0.00001) && ( k < 5))  
           {
               vc0= vc1;
               em2 = 7.0*vc0*vc0 -1.0;
               vc1 = vc0-em2*(pow(vc0,7.0)- gg*pow(em2,2.5)/(7.0*pow(vc0,6.0)*(2.0*vc0*vc0-1.0)));
               k++;
           }
           vc2 = vc0*a0;
       }      
         
       MPXV.qc = q1*p0;
       MPXV.vc = vc2*3.6;
 
   }

  		
}  		
/****************************************************************************
* 名称：Mpxv_Receive(void)
* 功能：压力传感器数据采集任务
* 入口参数：无
* 出口参数：无
****************************************************************************/
void   Mpxv_Receive(void)   
{
  double   vol1 = 0,vol2 = 0;
  double   H_height;
  double   H_speed; 
  
  
  AnalogIn (ANALOGINCH16, &vol1);    /* 通道16－－高度计 */
  AnalogIn (ANALOGINCH15, &vol2);    /* 通道15－－空速计 */
  	    
  CaculMpxvHigh(vol1);
  	
  CaculMpxvSpeed(vol2);
     
  printf(" height = %f,speed = %f,qc = %f, vc = %f\n\r",MPXV.altitude,MPXV.speed,MPXV.qc,MPXV.vc);    /*  打印高度和空速  */
    

}

