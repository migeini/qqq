/**********************************************************
* @ File name -> led.c
* @ Version   -> V1.0
* @ Date      -> 10-31-2013
* @ Brief     -> LED������غ���

 V1.*
* @ Revise    ->
**********************************************************/

#include "led.h"

/**********************************************************
* �������� ---> LED�ӿڳ�ʼ��
* ��ڲ��� ---> none
* ���ز��� ---> none 
* ����˵�� ---> none
**********************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOC, ENABLE);	//����GPIOC����ʱ��	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_SetBits(GPIOC, GPIO_Pin_1);	//����ߵ�ƽ��Ϩ���
	GPIO_SetBits(GPIOC, GPIO_Pin_0);	//����ߵ�ƽ��Ϩ���
}

