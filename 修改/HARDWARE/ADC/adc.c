#include "adc.h"
#include "delay.h"		 
//////////////////////////////////////////////////////////////////////////////////	 
//ADC ��������	   
//��������:2014/5/6
////////////////////////////////////////////////////////////////////////////////// 	


//��ʼ��ADC1	
//PA0  ͨ��0
void  Adc1_Init(void)
{      
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��


	//�ȳ�ʼ��ADC1ͨ��0 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	//PA0ͨ��0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	ADC_DeInit(ADC1);					//ADC��λ,������ADC1��ȫ���Ĵ�������Ϊȱʡֵ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
	//ADC��ʼ��
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC�����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//ת��������������ⲿ��������
	ADC_InitStructure.ADC_Mode=ADC_Mode_RegSimult;	//ADC����ģʽ:ADC1ͬ��������ģʽ
	ADC_InitStructure.ADC_NbrOfChannel=1;			//˳����й���ת����ADCͨ����Ŀ
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;		//ģ��ת�������ڷ�ɨ��ģʽ
	
	ADC_Init(ADC1,&ADC_InitStructure);		
	 
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
	
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE); //ʹ��ADC1

	/* Enable ADC1 reset calibaration register  ʹ��ADC1��λУ׼�Ĵ��� */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register   ADC1��λУ׼�Ĵ���������*/
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibaration    ����ADC1У׼ */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration  ADC1У׼������ */
	while(ADC_GetCalibrationStatus(ADC1));
	
}



//��ʼ��ADC2
//PC0  ͨ��0
void Adc2_Init(void)
{      
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC2, ENABLE); //ʹ��ADC2ʱ��

	//�ȳ�ʼ��ADC2ͨ��10 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PC0 ͨ��10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  

		
	ADC_DeInit(ADC2);					//ADC��λ,������ADC1��ȫ���Ĵ�������Ϊȱʡֵ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
	//ADC��ʼ��
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC�����Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//ת��������������ⲿ��������
	ADC_InitStructure.ADC_Mode=ADC_Mode_RegSimult;	//ADC����ģʽ:ADC1ͬ��������ģʽ
	ADC_InitStructure.ADC_NbrOfChannel=1;			//˳����й���ת����ADCͨ����Ŀ
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;		//ģ��ת�������ڷ�ɨ��ģʽ
	
	ADC_Init(ADC2,&ADC_InitStructure);		
	 
	ADC_RegularChannelConfig(ADC2,ADC_Channel_2,1,ADC_SampleTime_239Cycles5);
	
	
	/* Enable ADC1 */
	ADC_Cmd(ADC2, ENABLE); //ʹ��ADC1

	/* Enable ADC1 reset calibaration register  ʹ��ADC1��λУ׼�Ĵ��� */   
	ADC_ResetCalibration(ADC2);
	/* Check the end of ADC1 reset calibration register   ADC1��λУ׼�Ĵ���������*/
	while(ADC_GetResetCalibrationStatus(ADC2));

	/* Start ADC1 calibaration    ����ADC1У׼ */
	ADC_StartCalibration(ADC2);
	/* Check the end of ADC1 calibration  ADC1У׼������ */
	while(ADC_GetCalibrationStatus(ADC2));
}


//��ʼ��ADC
void adc_Init(void)
{
	Adc1_Init();
	Adc2_Init();
}


//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc1(void)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��			    
  
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);		//ʹ��ָ����ADC�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC�������ת�����
}

//���ADC2ֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc2(void)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��   
  
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);		//ʹ��ָ����ADC�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC2);	//�������һ��ADC�������ת�����
}


////��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
////ch:ͨ�����
////times:��ȡ����
////����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
//u16 Get_Adc1_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc1(ADC1,ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 
	 
////��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
////ch:ͨ�����
////times:��ȡ����
////����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
//u16 Get_Adc2_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc2(ADC2,ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 








