#ifndef _TIME_H
#define _TIME_H


extern   unsigned long    timetick;    
extern   unsigned char    tag_200us;
extern   unsigned char    tag_1ms;
extern   unsigned char    tag_5ms;
extern   unsigned char    tag_10ms;
extern   unsigned char    tag_20ms;
extern   unsigned char    tag_40ms;
extern   unsigned char    tag_50ms;
extern   unsigned char    tag_80ms;
extern   unsigned char    tag_100ms;
extern   unsigned char    tag_125ms;
extern   unsigned char    tag_200ms;
extern   unsigned char    tag_500ms;
extern   unsigned char    tag_600ms;
extern   unsigned char    tag_1s;
extern   unsigned char    tag_2s;
extern   unsigned short   CPULoad;
extern   unsigned short   IdleCount;
#ifdef __cplusplus
extern "C" {
#endif

void time_init(void);
void time_isr(void);

#ifdef __cplusplus
}
#endif
#endif

