#include "data_conversion.h"
#include "stdio.h"
//#include "stdint.h"
#include "stm32f10x.h"

//u32ת�����ַ�����Ĭ�ϲ���ʮ����

void u32_to_str(u32 num,char *str)
{
	sprintf(str,"%u",num);		//ʹ�á�%u����ʽ��numת��Ϊ�ַ���
}

//u32ת���ַ������ڴ�ӡ
void usartstr_u(u32 u)
{
	u8 uu[10]={0};	
	sprintf(uu,"%u",u);
	printf("%s",uu);
}
//u16ת���ַ������ڴ�ӡ
void usartstr_x(u16 hx)
{
	u8 xx[10]={0};	
	sprintf(xx,"%x",hx);
	printf("%s",xx);
}

//������ת���ַ������ڴ�ӡ
void usartstr_f(float f)
{
	u8 ff[10]={0};	
	sprintf(ff,"%f",f);
	printf("%s",ff);
}

//������ת�����ַ���
void float_to_string(float num,char *str)
{
	sprintf(str,"%f",num);		////ʹ�á�%f����ʽ��numת��Ϊ�ַ���
}

