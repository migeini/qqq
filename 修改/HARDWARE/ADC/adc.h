#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 							   
void Adc1_Init(void); 				//ADC1ͨ����ʼ��
void Adc2_Init(void);				//ADC2ͨ����ʼ��
void adc_Init(void);				//ADC��ʼ��
u16 Get_Adc1(void); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc2(void);
//u16 Get_Adc1_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
#endif 















