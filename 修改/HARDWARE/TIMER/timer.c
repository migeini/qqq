#include "timer.h"
#include "led.h"
#include "AD985x.h" 
#include "ping.h"
#include "data_conversion.h"
#include "vol_collect.h"
//arr：自动重装值。
//psc：时钟预分频数
void Timerx_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能
	//定时器初始化					   //arr,psc
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim 分频因子
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断	 允许更新中断
		TIM4, //TIM4
		TIM_IT_Update  |  //TIM 更新(溢出)中断                  
		TIM_IT_Trigger,   //TIM 触发中断   （捕获中断等）					地址值	 ((uint16_t)0x0040)         
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //抢占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //响应优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx（定时器）外设 开启定时器
							 
}

u32 count=0, count1=0, NowFre=0;
extern u32 SweepMinFre;
extern u32 SweepMaxFre;
extern u32 SweepStepFre;
extern u16 SweepTime;//ms
extern u8 SweepFlag;
extern u8 chongzhi;

void TIM4_IRQHandler(void)   //TIM4中断
{
u8 cc[7]={0x35,0x30,0x30,0x30,0x30,0x30,0x30};
char ch[7];
u8 maxfre[7];
u8 minfre[7];
char vol1[7],vol2[7],vol3[7],vol4[7];
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		
		if(SweepFlag)
		{
			count++;
			if(count>=5*SweepTime)
			{
				count=0;
				count1++;
				NowFre = SweepMinFre+SweepStepFre*count1;
                if(NowFre==SweepMaxFre)
                {
                    chongzhi=1;
                }
				if(NowFre>SweepMaxFre) count1 = 0;
				//写数据 
                
				AD985x_SetFre_Phase(NowFre,0);
//                AD985x_SetFre_Phase(NowFre,0);
				u32_to_str(NowFre,ch);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_SQUARE_STEP_CONTROL_ID,7,cc);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_SWEEP_MINFre_CONTROL_ID,7,ch);
				u32_to_str(maxFreq,maxfre);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAXF_CONTROL_ID,7,maxfre);//显示此时频率
				u32_to_str(minFreq,minfre);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MINF_CONTROL_ID,7,minfre);//显示此时频率
				float_to_string(temp1,vol1);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_PHASE_TIME_CONTROL_ID,7,vol1);
				float_to_string(temp3,vol2);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAX_CONTROL_ID,7,vol2);
				float_to_string(temp2,vol3);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_AMPL_CONTROL_ID,7,vol3);
				float_to_string(temp4,vol4);
				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MIN_CONTROL_ID,7,vol4);
			}
		}
	}
}











