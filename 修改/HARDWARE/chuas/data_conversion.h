#ifndef _DATA_CONVERSION_H
#define _DATA_CONVERSION_H

#include "stm32f10x.h"

			
void u32_to_str(u32 num,char *str);	//u32转换成字符串
void usartstr_u(u32 u);//u32转换字符串串口打印
void usartstr_x(u16 hx);//u16转换字符串串口打印
void usartstr_f(float f);//浮点型转换字符串串口打印
void float_to_string(float num,char *str);//浮点型转换成字符串

#endif


