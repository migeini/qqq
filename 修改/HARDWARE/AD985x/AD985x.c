/***************************************************************************
                       ��������
���ܣ�stm32f103rct6����AD985xģ�飬�������AD9850��AD9851ģ��
�ӿڣ��������Žӿ������AD985x.h
ʱ�䣺2023/06/xx
�汾��0.7
���ߣ���������
������������ֻ��ѧϰʹ�ã�����ؾ���
˵��������AD9850ģ����ؾ���125Mhz����Ϊ�ο�ʱ�����롣оƬ��֧�ֱ�Ƶ
			����AD9851ģ����ؾ���30Mhz,����Ĭ������6��Ƶ����180Mhz����Ϊ�ο�ʱ�����롣

					AD985x			��Ƭ��
Ӳ������:	AD985x_rst 	PA6
					AD985x_clk 	PA4	
					AD985x_fq 	PA3	
					D0-07 			PC0-PC7
					5V					--5V 
					GND					--GND(0V)  
					
������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://kvdz.taobao.com/ 
**************************************************************************/

#include "AD985x.h"

uint8_t AD985x_FD; //��Ƶ
uint8_t AD985x;			//Ҫ������ģ���ͺ�
uint8_t LOAD_MODE;	//��or��������

/***************************************************************************
** �������� ��void AD985x_Init(uint8_t AD985x ,uint8_t Load_Mode)
** �������� ����ʼ������AD985x��Ҫ�õ���IO�ڼ�ģʽ�����м���ģʽ
** ��ڲ��� ��cm��Ҫ�������ͺţ�AD9850;AD9851
**						sp��������ʽ��PARALLEL����������SERIAL��������
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_Init(uint8_t cm ,uint8_t sp)
{
	AD985x=cm;
	LOAD_MODE=sp;
	
	AD985x_IO_Init();
	AD985x_DataBus=0xFFFF0000;

	if(AD985x==AD9850) //AD9850
		AD985x_FD = AD985x_FD_0;//����Ƶ
	else	if(AD985x==AD9851)//AD9851
		AD985x_FD = AD985x_FD_6;//ʹ��6��Ƶ
	
	if(LOAD_MODE==PARALLEL)//����
	{
		AD985x_reset_parallel();//��λΪ(����ģʽ)  
	}
	else if(LOAD_MODE==SERIAL) //����
	{
		D0=1;D1=1;D2=0;	//��ʹ�ô�������ʱ��D0��D1��D2�������루110���̶���ƽ��
		AD985x_reset_serial();//��λΪ(����ģʽ)  
	}	
}

/***************************************************************************
** �������� ��void AD985x_IO_Init(void)
** �������� ����ʼ������AD985x��Ҫ�õ���IO��
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure ; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOC ,&GPIO_InitStructure) ;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3|GPIO_Pin_4| GPIO_Pin_6; 
	GPIO_Init(GPIOA ,&GPIO_InitStructure) ;
}

/***************************************************************************
** �������� ��void AD985x_reset_parallel()
** �������� ��AD985x��λ(����ģʽ)
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_reset_parallel(void)
{
	AD985x_clk=0;
	AD985x_fq=0;
	//rest�ź�
	AD985x_rst=0;
	AD985x_rst=1;
	AD985x_rst=0;
}

/***************************************************************************
** �������� ��void AD985x_reset_parallel()
** �������� ��AD985x��λ(����ģʽ)
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_reset_serial(void)
{
	AD985x_clk=0;
	AD985x_fq=0;
	//rest�ź�
	AD985x_rst=0;
	AD985x_rst=1;
	AD985x_rst=0;
	//w_clk�ź�
	AD985x_clk=0;
	AD985x_clk=1;
	AD985x_clk=0;
	//fq_up�ź�
	AD985x_fq=0;
	AD985x_fq=1;
	AD985x_fq=0;
}

/************************************************************
** �������� ��uint32_t Convert_Freq(double Real_f)
** �������� ��Ƶ������ת��
** ��ڲ��� ��Real_f����Ҫת����Ƶ��
** ���ڲ��� ��Ƶ������ֵ
** ����˵�� ��
**************************************************************/
uint32_t Convert_Freq(double Real_f)
{
	if(AD985x==AD9850) //AD9850
	{
	return (uint32_t)(AD9850_f_Num*Real_f);
	}
	else	
		if(AD985x==AD9851)//AD9851
		{return (uint32_t)(AD9851_f_Num*Real_f);
		}
	else 
	{return 0;
	}
}

/***************************************************************************
** �������� ��void AD985x_wr_parrel(double fre,uint8_t phase,uint8_t mul)
** �������� �� ��AD985x��д����������(����)
** ��ڲ��� ��fre: Ƶ��
							phase:��λ 0-31 ��һ�������ִ���11.25��
							mul:��Ƶ AD9850оƬ��֧�ֱ�Ƶ
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_wr_parrel(double fre,uint8_t phase,uint8_t mul)
{
	uint32_t w,y;
	
	y=Convert_Freq(fre);
	
	w=(phase<<3)|mul;   
	AD985x_DataBus=w|(w^0xff)<<16;     //дw0����
	AD985x_clk=1;
	AD985x_clk=0;

	w=(uint8_t)(y>>24);
	AD985x_DataBus=w|(w^0xff)<<16;     //w1
	AD985x_clk=1;
	AD985x_clk=0;

	w=(uint8_t)(y>>16);
	AD985x_DataBus=w|(w^0xff)<<16;     //w2
	AD985x_clk=1;
	AD985x_clk=0;

	w=(uint8_t)(y>>8);
	AD985x_DataBus=w|(w^0xff)<<16;     //w3
	AD985x_clk=1;
	AD985x_clk=0;

	w=(uint8_t)(y);
	AD985x_DataBus=w|(w^0xff)<<16;     //w4
	AD985x_clk=1;
	AD985x_clk=0;
	
	//����ʼ��
	AD985x_fq=1;
	AD985x_fq=0;
}

/***************************************************************************
** �������� ��void AD985x_wr_serial(double fre,uint8_t phase,uint8_t mul)
** �������� �� ��AD985x��д����������(����)
** ��ڲ��� ��fre: Ƶ��
							phase:��λ 0-31 ��һ�������ִ���11.25��
							mul:��Ƶ AD9850оƬ��֧�ֱ�Ƶ
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_wr_serial(double fre,uint8_t phase,uint8_t mul)
{
	uint8_t i,w;
	uint32_t y;
	
	y=Convert_Freq(fre);
	//дw4����
	w=(y>>=0);
	for(i=0;i<8;i++)
	{
		AD985x_bit_data=(w>>i)&0x01;
		AD985x_clk=1;
		AD985x_clk=0;
	}
	//дw3����
	w=(y>>8);
	for(i=0;i<8;i++)
	{
		AD985x_bit_data=(w>>i)&0x01;
		AD985x_clk=1;
		AD985x_clk=0;
	}
	//дw2����
	w=(y>>16);
	for(i=0;i<8;i++)
	{
		AD985x_bit_data=(w>>i)&0x01;
		AD985x_clk=1;
		AD985x_clk=0;
	}
	//дw1����
	w=(y>>24);
	for(i=0;i<8;i++)
	{
		AD985x_bit_data=(w>>i)&0x01;
		AD985x_clk=1;
		AD985x_clk=0;
	}
	//дw0����
	w=(phase<<3)|mul;  
	for(i=0;i<8;i++)
	{
		AD985x_bit_data=(w>>i)&0x01;
		AD985x_clk=1;
		AD985x_clk=0;
	}
	//����ʼ��
	AD985x_fq=1;
	AD985x_fq=0;
}

/***************************************************************************
** �������� ��void AD985x_Setfq(double fre,uint8_t phase)
** �������� ������AD985xƵ�ʼ���λ
** ��ڲ��� ��fre: Ƶ��
							phase:��λ 0-31 ��һ�������ִ���11.25��
** ���ڲ��� ����
** ����˵�� ����
*****************************************************************************/
void AD985x_SetFre_Phase(double fre,uint8_t phase)
{	
	if(LOAD_MODE==PARALLEL)
		AD985x_wr_parrel(fre,phase,AD985x_FD);
	else if(LOAD_MODE==SERIAL)
		AD985x_wr_serial(fre,phase,AD985x_FD);
}










































