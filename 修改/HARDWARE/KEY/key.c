#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "key.h"
#include "stdio.h"
//////////////////////
u32 KEY_Sys_Timer;
u32 Keycode;
//////////////////////
u32 SystemTime;
u32 KEY_Time;
u32 key_Trgtime;
u32 KEY_Trg;
u32 KEY_Cont=0;
u32 Trg_state = NO;
void key_init(void)
{
	GPIO_InitTypeDef GPIOStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
	GPIOStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStructure.GPIO_Pin =GPIO_Pin_11 + GPIO_Pin_12 + GPIO_Pin_13 + GPIO_Pin_14 + GPIO_Pin_15;
	GPIOStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIOStructure);						//��ʼ��PB11,PB12,PB13,PB14,PB15

	TIM_DeInit(TIM3);					//Timer����ΪĬ��ȱʡֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 71;//��ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ:71
	TIM_TimeBaseInitStruct.TIM_Period = 999;//����һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ:999
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);//����ָ���Ĳ�����ʼ��TIM3��ʱ�������λ
	
	TIM_ITConfig(TIM3, TIM_IT_Update|TIM_IT_Trigger, ENABLE);//ʹ��ָ����TIM3�ж�,��������жϺʹ����ж�
	TIM_Cmd(TIM3, ENABLE);					//ʹ��TIM3
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;	//TIM3�ж�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//IQRͨ����ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;			//��Ӧ���ȼ�1
	NVIC_Init(&NVIC_InitStruct);			//��ʼ��NVIC�Ĵ���
}

//���ݰ����ı�Ĵ������ض�λ��ֵ
u32 Change_GPIOCode(void)
{
	u32 GPIO_Data;
	GPIO_Data=(((GPIOB->IDR)>>11)&0xffff)|(~(KEY1BIT+KEY2BIT +KEY3BIT +KEY4BIT+KEY5BIT));
	return GPIO_Data;
}

//���ܣ���ȡ����״̬
u32 KeyRead(void)
{
    u32 ReadData = Change_GPIOCode()^0XFFFFFFFF;   //��ȡ����״̬
    KEY_Trg = ReadData & (ReadData ^ KEY_Cont);      //��ⰴ������
    KEY_Cont = ReadData;	//���°����ĳ���״̬

	if(!Trg_state) 
		key_Trgtime = KEY_Sys_Timer + T_10mS;	//���Trg_stateΪ�٣�key_Trgtime��10s
	if(KEY_Trg)
		Trg_state = YES;
	if(Trg_state)
	{
		if((KEY_Sys_Timer > key_Trgtime)&&(KEY_Sys_Timer<(((u32)0-T_10mS))))  //�̰�
		{
			switch(KEY_Cont)
			{
				case K_1:{Keycode = K_1_S; break;}
				case K_2:{Keycode = K_2_S; break;} 	
				case K_3:{Keycode = K_3_S; break;}
				case K_4:{Keycode = K_4_S; break;}
				case K_5:{Keycode = K_5_S; break;}
				default:{Keycode = K_NO; break;}
			}	
			
		}
	}
	if(KEY_Time >= T_1S)	  	//����1s����
	{ 
		KEY_Time = T_1S-T_330mS;
		switch(KEY_Cont)
		{
			case K_1:{Keycode = K_1_L; break;}
			case K_2:{Keycode = K_2_L; break;} 	
			case K_3:{Keycode = K_3_L; break;}
			case K_4:{Keycode = K_4_L; break;}
			case K_5:{Keycode = K_5_L; break;}
			default:{Keycode = K_NO; break;} 
		}
	}
	return Keycode;
}
//�������״̬
void KEY_EXIT(void)
{
	if(Keycode != K_NO)
	{
		Trg_state = NO;
		Keycode = K_NO;
	}	
}

