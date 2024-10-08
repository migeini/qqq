#include "data_conversion.h"
#include "stdio.h"
//#include "stdint.h"
#include "stm32f10x.h"

//u32转换成字符串，默认采用十进制

void u32_to_str(u32 num,char *str)
{
	sprintf(str,"%u",num);		//使用“%u”格式将num转换为字符串
}

//u32转换字符串串口打印
void usartstr_u(u32 u)
{
	u8 uu[10]={0};	
	sprintf(uu,"%u",u);
	printf("%s",uu);
}
//u16转换字符串串口打印
void usartstr_x(u16 hx)
{
	u8 xx[10]={0};	
	sprintf(xx,"%x",hx);
	printf("%s",xx);
}

//浮点型转换字符串串口打印
void usartstr_f(float f)
{
	u8 ff[10]={0};	
	sprintf(ff,"%f",f);
	printf("%s",ff);
}

//浮点型转换成字符串
void float_to_string(float num,char *str)
{
	sprintf(str,"%f",num);		////使用“%f”格式将num转换为字符串
}

