#include "adc.h"
#include "delay.h"		 
//////////////////////////////////////////////////////////////////////////////////	 
//ADC 驱动代码	   
//创建日期:2014/5/6
////////////////////////////////////////////////////////////////////////////////// 	


//初始化ADC1	
//PA0  通道0
void  Adc1_Init(void)
{      
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟


	//先初始化ADC1通道0 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	//PA0通道0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	ADC_DeInit(ADC1);					//ADC复位,将外设ADC1的全部寄存器重设为缺省值
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	
	//ADC初始化
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_Mode=ADC_Mode_RegSimult;	//ADC工作模式:ADC1同步规则组模式
	ADC_InitStructure.ADC_NbrOfChannel=1;			//顺序进行规则转换的ADC通道数目
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;		//模数转换工作在非扫描模式
	
	ADC_Init(ADC1,&ADC_InitStructure);		
	 
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);
	
	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE); //使能ADC1

	/* Enable ADC1 reset calibaration register  使能ADC1复位校准寄存器 */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register   ADC1复位校准寄存器检查结束*/
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibaration    启动ADC1校准 */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration  ADC1校准检查结束 */
	while(ADC_GetCalibrationStatus(ADC1));
	
}



//初始化ADC2
//PC0  通道0
void Adc2_Init(void)
{      
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC2, ENABLE); //使能ADC2时钟

	//先初始化ADC2通道10 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PC0 通道10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化  

		
	ADC_DeInit(ADC2);					//ADC复位,将外设ADC1的全部寄存器重设为缺省值
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	
	//ADC初始化
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_Mode=ADC_Mode_RegSimult;	//ADC工作模式:ADC1同步规则组模式
	ADC_InitStructure.ADC_NbrOfChannel=1;			//顺序进行规则转换的ADC通道数目
	ADC_InitStructure.ADC_ScanConvMode=DISABLE;		//模数转换工作在非扫描模式
	
	ADC_Init(ADC2,&ADC_InitStructure);		
	 
	ADC_RegularChannelConfig(ADC2,ADC_Channel_2,1,ADC_SampleTime_239Cycles5);
	
	
	/* Enable ADC1 */
	ADC_Cmd(ADC2, ENABLE); //使能ADC1

	/* Enable ADC1 reset calibaration register  使能ADC1复位校准寄存器 */   
	ADC_ResetCalibration(ADC2);
	/* Check the end of ADC1 reset calibration register   ADC1复位校准寄存器检查结束*/
	while(ADC_GetResetCalibrationStatus(ADC2));

	/* Start ADC1 calibaration    启动ADC1校准 */
	ADC_StartCalibration(ADC2);
	/* Check the end of ADC1 calibration  ADC1校准检查结束 */
	while(ADC_GetCalibrationStatus(ADC2));
}


//初始化ADC
void adc_Init(void)
{
	Adc1_Init();
	Adc2_Init();
}


//获得ADC值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
u16 Get_Adc1(void)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间			    
  
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);		//使能指定的ADC的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC规则组的转换结果
}

//获得ADC2值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
u16 Get_Adc2(void)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间   
  
	ADC_SoftwareStartConvCmd(ADC2,ENABLE);		//使能指定的ADC的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC2);	//返回最近一次ADC规则组的转换结果
}


////获取通道ch的转换值，取times次,然后平均 
////ch:通道编号
////times:获取次数
////返回值:通道ch的times次转换结果平均值
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
	 
////获取通道ch的转换值，取times次,然后平均 
////ch:通道编号
////times:获取次数
////返回值:通道ch的times次转换结果平均值
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








