//#include "timer.h"
//#include "led.h"
//#include "AD985x.h"
//#include "ping.h"
//#include "data_conversion.h"

////arr���Զ���װֵ��
////psc��ʱ��Ԥ��Ƶ��
//void Timerx_Init(u16 arr,u16 psc)
//{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
//	//��ʱ����ʼ��					   //arr,psc
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
//	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim ��Ƶ����
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�	 ��������ж�
//		TIM4, //TIM4
//		TIM_IT_Update  |  //TIM ����(���)�ж�                  
//		TIM_IT_Trigger,   //TIM �����ж�   �������жϵȣ�					��ֵַ	 ((uint16_t)0x0040)         
//		ENABLE  //ʹ��
//		);
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //��Ӧ���ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����ʱ�������� ������ʱ��
//							 
//}

//u32 count=0, count1=0, NowFre=0;
//extern u32 SweepMinFre;
//extern u32 SweepMaxFre;
//extern u32 SweepStepFre;
//extern u16 SweepTime;//ms
//extern u8 SweepFlag;
//extern u32 maxFreq;   // ���ֵʱ��Ƶ��
//extern u32 minFreq;   // ��Сֵʱ��Ƶ��
//extern float temp1,temp2,temp3,temp4;

//void TIM4_IRQHandler(void)   //TIM4�ж�
//{
//	u8 cc[7]={0x35,0x30,0x30,0x30,0x30,0x30,0x30};
//	char ch[7];
//	u8 maxfre[7];
//	u8 minfre[7];
//	char vol1[7],vol2[7],vol3[7],vol4[7];
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		
//		if(SweepFlag)
//		{
//			count++;
//			if(count>=10*SweepTime)
//			{
//				count=0;
//				count1++;
//				NowFre = SweepMinFre+SweepStepFre*count1;
//				if(NowFre>SweepMaxFre) count1 = 0;
//				//д���� 
//				AD985x_SetFre_Phase(NowFre,0);
//				u32_to_str(NowFre,ch);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_SQUARE_STEP_CONTROL_ID,7,cc);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_SWEEP_MINFre_CONTROL_ID,7,ch);
//				u32_to_str(maxFreq,maxfre);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAXF_CONTROL_ID,7,maxfre);//��ʾ��ʱƵ��
//				u32_to_str(minFreq,minfre);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAXF_CONTROL_ID,7,minfre);//��ʾ��ʱƵ��
//				float_to_string(temp1,vol1);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_PHASE_TIME_CONTROL_ID,7,vol1);
//				float_to_string(temp3,vol2);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAX_CONTROL_ID,7,vol2);
//				float_to_string(temp2,vol3);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_AMPL_CONTROL_ID,7,vol3);
//				float_to_string(temp4,vol4);
//				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MIN_CONTROL_ID,7,vol4);
//				
//			}
//		}
//	}
//}

//void TIM4_IRQHandler(void)   //TIM4�ж�
//{
////    u8 cc[7] = {0x35, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};  // ����ɨƵ��ʾ
////    char ch[7];
////    u8 maxfre[7];
////    u8 minfre[7];
////    char vol1[7], vol2[7], vol3[7], vol4[7];
//    
//    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  // ��� TIM4 �����ж�
//    {
//        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  // ����жϱ�־λ
//        
//        if (SweepFlag)
//        {
//            count++;
//            if (count >= 10 * SweepTime)  // �����趨��ʱ��������Ƶ�ʸ���
//            {
//                count = 0;
//                count1++;
//                NowFre = SweepMinFre + SweepStepFre * count1;
//                
//                if (NowFre > SweepMaxFre) 
//                {
//                    count1 = 0;
//                }
//                
//                // �����µ�Ƶ��
//                AD985x_SetFre_Phase(NowFre, 0);
//                
////                // ��ʾ��ǰɨƵƵ��
////                u32_to_str(NowFre, ch);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_SQUARE_STEP_CONTROL_ID, 7, cc);  // ��ʾɨƵ����
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_SWEEP_MINFre_CONTROL_ID, 7, ch); // ��ʾ��ǰƵ��
////                
////                // ��ʾ������СƵ��
////                u32_to_str(maxFreq, maxfre);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_MAXF_CONTROL_ID, 7, maxfre);  // ��ʾ���Ƶ��
////                
////                u32_to_str(minFreq, minfre);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_MINF_CONTROL_ID, 7, minfre);  // ��ʾ��СƵ��
////                
////                // ��ʾ�����ѹֵ
////                float_to_string(temp1, vol1);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_PHASE_TIME_CONTROL_ID, 7, vol1);  // ��λ��ѹ
////                
////                float_to_string(temp3, vol2);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_MAX_CONTROL_ID, 7, vol2);  // ����ѹ
////                
////                float_to_string(temp2, vol3);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_AMPL_CONTROL_ID, 7, vol3);  // ��ֵ��ѹ
////                
////                float_to_string(temp4, vol4);
////                screen_text_sendvalue(TEXT_TEST_PAGE_ID, TEXT_MIN_CONTROL_ID, 7, vol4);  // ��С��ѹ
//            }
//        }
//    }
//}
#include "timer.h"
#include "led.h"
#include "AD985x.h" 

//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void Timerx_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	//��ʱ����ʼ��					   //arr,psc
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim ��Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�	 ��������ж�
		TIM4, //TIM4
		TIM_IT_Update  |  //TIM ����(���)�ж�                  
		TIM_IT_Trigger,   //TIM �����ж�   �������жϵȣ�					��ֵַ	 ((uint16_t)0x0040)         
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //��Ӧ���ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����ʱ�������� ������ʱ��
							 
}

u32 count=0, count1=0, NowFre=0;
extern u32 SweepMinFre;
extern u32 SweepMaxFre;
extern u32 SweepStepFre;
extern u16 SweepTime;//ms
extern u8 SweepFlag;

void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		
		if(SweepFlag)
		{
			count++;
			if(count>=10*SweepTime)
			{
				count=0;
				count1++;
				NowFre = SweepMinFre+SweepStepFre*count1;
				if(NowFre>SweepMaxFre) count1 = 0;
				//д���� 
				AD985x_SetFre_Phase(NowFre,0);
			}
		}
	}
}





















