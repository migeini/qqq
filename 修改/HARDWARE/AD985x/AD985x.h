#ifndef __AD985x_H
#define __AD985x_H	 
#include "sys.h"

#define AD9851 			1
#define AD9850			0
 
#define PARALLEL		0 //����
#define SERIAL			1 //����

#define AD985x_FD_0    			0 //����Ƶ
#define AD985x_FD_6   			1 //ʹ��6��Ƶ

#define AD9850_CLK	125000000				//�ο�ʱ��
#define AD9851_CLK	180000000				//�ο�ʱ��

#define AD9850_f_Num  34.359738368	//Ƶ��ת��ϵ����2^32/ϵͳʱ��Ƶ��
#define AD9851_f_Num  23.860929422	//Ƶ��ת��ϵ����2^32/ϵͳʱ��Ƶ��

#define AD985x_rst    	PAout(6)  //��λ
#define AD985x_clk    	PAout(4)  //����ʱ����������
#define AD985x_fq    		PAout(3)  //���ݸ���
#define AD985x_bit_data PCout(7)  //����������������

#define AD985x_DataBus	GPIOC->BSRR//���п��ƽ�PC0-7

#define D0   		PCout(0)
#define D1   		PCout(1)
#define D2   		PCout(2)

extern uint8_t AD985x_FD; //��Ƶ
extern uint8_t AD985x;			//Ҫ������ģ���ͺ�
extern uint8_t LOAD_MODE;	//��or��������

void AD985x_IO_Init(void);//��ʼ������AD985x��Ҫ�õ���IO��
void AD985x_Init(uint8_t cm ,uint8_t sp);//��ʼ������AD985x��Ҫ�õ���IO�ڼ�ģʽ�����м���ģʽ

void AD985x_reset_parallel(void);//AD985x��λ(����ģʽ)
void AD985x_reset_serial(void);	//AD985x��λ(����ģʽ)

uint32_t Convert_Freq(double Real_f);//Ƶ������ת��

void AD985x_wr_parrel(double fre,uint8_t phase,uint8_t mul);//��AD985x��д����������(����)
void AD985x_wr_serial(double fre,uint8_t phase,uint8_t mul);//��AD985x��д����������(����)
void AD985x_SetFre_Phase(double fre,uint8_t phase);//����Ƶ�ʣ���λ

#endif

