#include "vol_collect.h"
#include "adc.h"
#include "usart.h"
#include "ping.h"
#include "data_conversion.h"
#include "timer.h"

extern u32 NowFre;
extern u8 isStarted;   
u32 maxFreq = 0;   // ���ֵʱ��Ƶ��
u32 minFreq = 0; 
u32 maxnowfre=0;
u32 resonantFreq;
u8 chongzhi=0;
float temp1,temp2,temp3,temp4;
//void phase_vol(void)
//{
//	u16 adc1,mm;
//	u16 m=0;
//    
//	adc1=Get_Adc1();	//��ȡͨ��4��ת��ֵ
//	
//			if(isStarted && adc1 > m)
//			{
//				m = adc1; //�Ƚϴ�С�������ֵ
//				maxFreq = NowFre; // �������ֵʱ��Ƶ��
////				u32_to_str(maxFreq,maxfre);
////				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAXF_CONTROL_ID,7,maxfre);//��ʾ��ʱƵ��
//			}
//		
//		temp1=(float)adc1*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
////		screenShowDataFromFloat(TEXT_TEST_PAGE_ID,TEXT_PHASE_TIME_CONTROL_ID,temp1,0);
//		//��ʾ��ֵ
//		mm=m;
//		temp3=(float)mm*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
////		screenShowDataFromFloat(TEXT_TEST_PAGE_ID,TEXT_MAX_CONTROL_ID,temp3,0);
//}


//void ampl_vol(void)
//{
//	u16 adc2,nn;
//	u16 n=4095;
//	adc2=Get_Adc2();	//��ȡADC2��ת��ֵ
//	
//			if(isStarted && adc2 < n)
//			{
//				n=adc2;			//�Ƚϴ�С������Сֵ
//				minFreq = NowFre; // �������ֵʱ��Ƶ��
////				u32_to_str(minFreq,minfre);
////				screen_text_sendvalue(TEXT_TEST_PAGE_ID,TEXT_MAXF_CONTROL_ID,7,minfre);//��ʾ��ʱƵ��
//			}
//		
//	//��ʾADC2ֵ
//	temp2=(float)adc2*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//	//screenShowDataFromFloat(TEXT_TEST_PAGE_ID,TEXT_AMPL_CONTROL_ID,temp2,0);
//	//��ʾ��ֵ
//	nn=n;
//	temp4=(float)nn*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
////	screenShowDataFromFloat(TEXT_TEST_PAGE_ID,TEXT_MIN_CONTROL_ID,temp4,0);	
//}



