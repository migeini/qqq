#ifndef _DATA_CONVERSION_H
#define _DATA_CONVERSION_H

#include "stm32f10x.h"

			
void u32_to_str(u32 num,char *str);	//u32ת�����ַ���
void usartstr_u(u32 u);//u32ת���ַ������ڴ�ӡ
void usartstr_x(u16 hx);//u16ת���ַ������ڴ�ӡ
void usartstr_f(float f);//������ת���ַ������ڴ�ӡ
void float_to_string(float num,char *str);//������ת�����ַ���

#endif


