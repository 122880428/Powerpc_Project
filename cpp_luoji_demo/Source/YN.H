#ifndef _YN_H_
#define _YN_H_


#include <stdio.h>

typedef union {
    unsigned char     B[4];
    short             D[2];
    unsigned short    W[2];
    long              DW;
    unsigned long     UDW;
    float             f;
} dWordStruc;

typedef union {
    unsigned char    B[4];
    float            val;    
} FloatStruc;

typedef union {
    unsigned char    B[4];
    unsigned long    val;    
} LongStruc;

typedef union {
    unsigned char    B[2];
    unsigned short   val;    
} ShortStruc;


typedef union {
    unsigned char     B[8];
    short             D[4];
    unsigned short    W[4];
    long              DW[2];
    unsigned long     UDW[2];
    float             f[2];
    double            df;
} dDWordStruc;


typedef		struct
{
    unsigned char	bSFF;
    unsigned long       wID;
    unsigned char	bData[8];
}CAN_Msg;


typedef struct  {
    unsigned short        invalid;
    unsigned short        counter;
    char                  fail;       
    unsigned short        freq;
} SensorStruc;

#include "drivers\ppc5125Intr.h"
#include "drivers\ppccom.h"
#include "drivers\xr16l788.h"
#include "drivers\wdt.h"
#include "drivers\nvram.h"
#include "drivers\mscan.h"
#include "drivers\flash.h"
#include "drivers\fpm.h"
#include "drivers\gpt.h"
#include "drivers\pwm.h"
#include "drivers\io.h"
#include "drivers\analog.h"
#include "drivers\mpxv.h"
#include "drivers\sbus.h"
#include "drivers\gps.h"
#include "drivers\time.h"
#include "startup\init.h"
#include "math.h"
#include <cmath>
#include "stdlib.h"
//#include "iostream.h"

/*void OSTimeDly(int a)
{
	
}*/

#endif