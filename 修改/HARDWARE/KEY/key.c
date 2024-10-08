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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	//使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM3时钟
	GPIOStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIOStructure.GPIO_Pin =GPIO_Pin_11 + GPIO_Pin_12 + GPIO_Pin_13 + GPIO_Pin_14 + GPIO_Pin_15;
	GPIOStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIOStructure);						//初始化PB11,PB12,PB13,PB14,PB15

	TIM_DeInit(TIM3);					//Timer设置为默认缺省值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 71;//作为TIMx时钟频率除数的预分频值:71
	TIM_TimeBaseInitStruct.TIM_Period = 999;//在下一个更新事件装入活动的自动重装载寄存器周期的值:999
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);//根据指定的参数初始化TIM3的时间基数单位
	
	TIM_ITConfig(TIM3, TIM_IT_Update|TIM_IT_Trigger, ENABLE);//使能指定的TIM3中断,允许更新中断和触发中断
	TIM_Cmd(TIM3, ENABLE);					//使能TIM3
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;	//TIM3中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//IQR通道被使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;			//响应优先级1
	NVIC_Init(&NVIC_InitStruct);			//初始化NVIC寄存器
}

//根据按键改变寄存器中特定位的值
u32 Change_GPIOCode(void)
{
	u32 GPIO_Data;
	GPIO_Data=(((GPIOB->IDR)>>11)&0xffff)|(~(KEY1BIT+KEY2BIT +KEY3BIT +KEY4BIT+KEY5BIT));
	return GPIO_Data;
}

//功能：读取按键状态
u32 KeyRead(void)
{
    u32 ReadData = Change_GPIOCode()^0XFFFFFFFF;   //读取按键状态
    KEY_Trg = ReadData & (ReadData ^ KEY_Cont);      //检测按键触发
    KEY_Cont = ReadData;	//更新按键的持续状态

	if(!Trg_state) 
		key_Trgtime = KEY_Sys_Timer + T_10mS;	//如果Trg_state为假，key_Trgtime加10s
	if(KEY_Trg)
		Trg_state = YES;
	if(Trg_state)
	{
		if((KEY_Sys_Timer > key_Trgtime)&&(KEY_Sys_Timer<(((u32)0-T_10mS))))  //短按
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
	if(KEY_Time >= T_1S)	  	//超过1s长按
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
//清除按键状态
void KEY_EXIT(void)
{
	if(Keycode != K_NO)
	{
		Trg_state = NO;
		Keycode = K_NO;
	}	
}

