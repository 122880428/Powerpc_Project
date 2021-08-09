#ifndef _MPXV_H_
#define _MPXV_H_

#include "math.h"

#define MPXV5004   1

typedef struct{
    double altitude;        /*m*/
    double speed;           /*km/h*/
    double highPressure;    /*pa*/
    double speedPressure;   /*pa*/
    double qc;              /*pa*/
    double vc;	            /*km/h*/
}mpxv_t;  

extern  mpxv_t  MPXV;

void  Gravity(double altitude,double lat,double lon,double *g_);
void  CaculMpxvRu(double altitude, double *ru_temp);
void  CaculMpxvHigh(double high_vol);
void  CaculMpxvSpeed(double speed_vol);
void  CaculMpxvVC(void);
void  Mpxv_Receive(void);   

#endif