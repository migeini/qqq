#ifndef _VOL_COLLECT_H
#define _VOL_COLLECT_H
#include <stm32f10x.h>
extern u32 maxFreq;   // 最大值时的频率
extern u32 minFreq;   // 最小值时的频率
extern u8 chongzhi;
extern u32 resonantFreq;
extern float temp1,temp2,temp3,temp4;

void phase_vol(void);
void ampl_vol(void);


#endif

