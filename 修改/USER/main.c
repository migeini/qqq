///**********************************************************
//                       康威电子										 
//功能：stm32f103驱动AD985x输出波形，长按中间键可切换扫频
//			显示：12864cog
//接口：控制接口请参照AD985x.h  按键接口请参照key.h
//时间：2023/06/xx
//版本：0.7
//作者：康威电子
//其他：本程序只供学习使用，盗版必究。
//说明：本店AD9850模块板载晶振125Mhz，作为参考时钟输入。芯片不支持倍频
//			本店AD9851模块板载晶振30Mhz,程序默认配置6倍频，即180Mhz，作为参考时钟输入。

//					AD985x			单片机
//硬件连接:	AD985x_rst 	PA6
//					AD985x_clk 	PA4	
//					AD985x_fq 	PA3	
//					D0-07 			PC0-PC7
//					5V					--5V 
//					GND					--GND(0V)  

//更多电子需求，请到淘宝店，康威电子竭诚为您服务 ^_^
//https://kvdz.taobao.com/ 
//**********************************************************/
//#include "stm32_config.h"
//#include "stdio.h"
//#include "led.h"
//#include "lcd.h"
//#include "AD985x.h" 
//#include "key.h"
//#include "timer.h"
//#include "task_manage.h"
//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "adc.h"

//char str[30];	//显示缓存
//extern u8 _return;
//extern u32 NowFre;
//extern u32 Sinfre;
//int main(void)
//{
//	u16 adc1, adc2;
//	u16 m = 0;
//	u16 n = 4095;
//	u16 mm, nn;
//	u32 maxFreq = 0;   // 最大值时的频率
//	u32 minFreq = 0;   // 最小值时的频率
//	float temp1;
//	float temp2;
//	float temp3;
//	float temp4;	
//	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组 
//	delay_init(72);	//初始化延时函数
//	LED_Init();	//初始化LED接口
//	key_init();
//	uart_init(115200);
//	adc_Init();
//	adc2 = Get_Adc2();	//获取ADC2的转换值
//	initial_lcd();
//	LCD_Clear();
//	delay_ms(300);
//	LCD_Refresh_Gram();
//	
//	//定时器
//	Timerx_Init(99, 71);
//	
//	LCD_Clear();
//	
//	// AD985x 初始化
//	AD985x_Init(AD9850, SERIAL);	//初始化控制AD9850需要用到的IO口,设置为串行通讯
//	
//	AD985x_SetFre_Phase(1000, 0);
//	
//	printf("DDS\r\n");

//	while(1)
//	{
//		KeyRead(); //读取按键值 （内部备注不详，不用管） 
//		Set_PointFre(Keycode, 0); //按键处理
//		if(_return) {
//			_return = 0;
//			LCD_Refresh_Gram(); //更新显示
//		}
//		printf("FRE:");
//		usartstr_u(NowFre); //显示此时频率
//		printf("Hz\r\n"); //换行
//		printf("SINFRE:");
//		usartstr_u(Sinfre); //显示此时频率
//		printf("Hz\r\n"); //换行
//		
//		adc1 = Get_Adc1(); //获取通道4的转换值
//		usartstr_x(adc1); //发送adc1原始值
//		printf("\r\n"); //换行
//		if(adc1 > m)
//		{
//			m = adc1; //比较大小，找最大值
//			maxFreq = NowFre; // 保存最大值时的频率
//			usartstr_u(NowFre); //显示此时频率
//			printf("Hz\r\n"); //换行
//		}
//		usartstr_x(m); //发送m原始值
//		printf("\r\n"); //换行
//		temp1 = (float)adc1 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//		printf("PHASE_V:");
//		usartstr_f(temp1);
//		printf("\r\n"); //换行
//		
//		//显示最大值
//		printf("max:");
//		mm = m;
//		temp3 = (float)mm * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//		usartstr_f(temp3);	
//		printf("\r\n"); //换行
//		printf("MaxFreq: %uHz\r\n", maxFreq); // 显示最大值时的频率
//		
//		adc2 = Get_Adc2(); //获取通道5的转换值
//		usartstr_x(adc2); //发送adc2原始值
//		printf("\r\n"); //换行
//		if(adc2 < n)
//		{
//			n = adc2; //比较大小，找最小值
//			minFreq = NowFre; // 保存最小值时的频率
//		}
//		usartstr_x(n); //发送n原始值
//		printf("\r\n"); //换行
//		printf("AMPLITUDE_V:");
//		//显示ADC值
//		temp2 = (float)adc2 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//		usartstr_f(temp2);
//		printf("\r\n"); //换行
//		
//		//显示最小值
//		printf("min:");
//		nn = n;
//		temp4 = (float)nn * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//		usartstr_f(temp4);
//		printf("\r\n"); //换行
//		printf("MinFreq: %uHz\r\n", minFreq); // 显示最小值时的频率
//		
//		LED1 = !LED1;
//		printf("\r\n"); //换行
//		delay_ms(250);	
//		KEY_EXIT();
//	}	
//}

//#include "stm32_config.h"
//#include "stdio.h"
//#include "led.h"
//#include "lcd.h"
//#include "AD985x.h" 
//#include "key.h"
//#include "timer.h"
//#include "task_manage.h"
//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "adc.h"

//char str[30];  //显示缓存
//extern u8 _return;
//extern u32 NowFre;
//extern u32 Sinfre;

//u8 displayFlag = 0;  // 显示最大最小值时的频率标志位
//u8 isStarted = 0;    // 是否开始标志位

//void StartSweep();

//int main(void)
//{
//    u16 adc1, adc2;
//    u16 m = 0;
//    u16 n = 4095;
//    u16 mm, nn;
//    u32 maxFreq = 0;   // 最大值时的频率
//    u32 minFreq = 0;   // 最小值时的频率
//    float temp1;
//    float temp2;
//    float temp3;
//    float temp4; 
//    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //设置中断分组 
//    delay_init(72); //初始化延时函数
//    LED_Init(); //初始化LED接口
//    key_init();
//    uart_init(115200);
//    adc_Init();
//    adc2 = Get_Adc2(); //获取ADC2的转换值
//    initial_lcd();
//    LCD_Clear();
//    delay_ms(300);
//    LCD_Refresh_Gram();
//    
//    //定时器
//    Timerx_Init(99, 71);
//    
//    LCD_Clear();
//    
//    // AD985x 初始化
//    AD985x_Init(AD9850, SERIAL); //初始化控制AD9850需要用到的IO口,设置为串行通讯
//    
//    AD985x_SetFre_Phase(1000, 0);
//    
//    printf("DDS\r\n");

//    while(1)
//    {
//        KeyRead(); //读取按键值 （内部备注不详，不用管） 
//        Set_PointFre(Keycode, 0); //按键处理
//        if (_return) {
//            _return = 0;
//            LCD_Refresh_Gram(); //更新显示
//        }
//        printf("FRE:");
//        usartstr_u(NowFre); //显示此时频率
//        printf("Hz\r\n"); //换行
//        printf("SINFRE:");
//        usartstr_u(Sinfre); //显示此时频率
//        printf("Hz\r\n"); //换行
//        
//        if (NowFre != 0) {  // 当 NowFre 不为零时，设置显示标志并标记开始
//            displayFlag = 1;
//            isStarted = 1;
//        }

//        adc1 = Get_Adc1(); //获取通道4的转换值
//        usartstr_x(adc1); //发送adc1原始值
//        printf("\r\n"); //换行

//        if (isStarted && adc1 > m)  // 只有在开始之后才存储最大值时刻的频率
//        {
//            m = adc1; //比较大小，找最大值
//            maxFreq = NowFre; // 保存最大值时的频率
//            usartstr_u(NowFre); //显示此时频率
//            printf("Hz\r\n"); //换行
//        }
//        usartstr_x(m); //发送m原始值
//        printf("\r\n"); //换行
//        temp1 = (float)adc1 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        printf("PHASE_V:");
//        usartstr_f(temp1);
//        printf("\r\n"); //换行
//        
//        //显示最大值
//        printf("max:");
//        mm = m;
//        temp3 = (float)mm * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp3); 
//        printf("\r\n"); //换行
//        if (displayFlag) {
//            printf("MaxFreq: %uHz\r\n", maxFreq); // 显示最大值时的频率
//        }
//        
//        adc2 = Get_Adc2(); //获取通道5的转换值
//        usartstr_x(adc2); //发送adc2原始值
//        printf("\r\n"); //换行

//        if (isStarted && adc2 < n)  // 只有在开始之后才存储最小值时刻的频率
//        {
//            n = adc2; //比较大小，找最小值
//            minFreq = NowFre; // 保存最小值时的频率
//        }
//        usartstr_x(n); //发送n原始值
//        printf("\r\n"); //换行
//        printf("AMPLITUDE_V:");
//        //显示ADC值
//        temp2 = (float)adc2 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp2);
//        printf("\r\n"); //换行
//        
//        //显示最小值
//        printf("min:");
//        nn = n;
//        temp4 = (float)nn * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp4);
//        printf("\r\n"); //换行
//        if (displayFlag) {
//            printf("MinFreq: %uHz\r\n", minFreq); // 显示最小值时的频率
//        }
//        
//        LED1 = !LED1;
//        printf("\r\n"); //换行
//        delay_ms(250); 
//        KEY_EXIT();
//    }   
//}
#include "stm32_config.h"
#include "stdio.h"
#include "led.h"
#include "lcd.h"
#include "AD985x.h" 
#include "key.h"
#include "timer.h"
#include "task_manage.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "vol_collect.h"

char str[30];  //显示缓存
extern u8 _return;
extern u32 NowFre;
extern u32 Sinfre;

u8 displayFlag = 0;  // 显示最大最小值时的频率标志位
u8 isStarted = 0;    // 是否开始标志位

u32 lastNowFre = 0;  // 存储上一次的频率值

//void StartSweep();

int main(void)
{
    u16 adc1, adc2;
    u16 m = 0;
    u16 n = 4095;
    u16 mm, nn;
//    u32 maxFreq = 0;   // 最大值时的频率
//    u32 minFreq = 0;   // 最小值时的频率
//    float temp1;
//    float temp2;
//    float temp3;
//    float temp4; 
    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //设置中断分组 
    delay_init(72); //初始化延时函数
    LED_Init(); //初始化LED接口
    key_init();
    uart_init(115200);
    adc_Init();
    adc2 = Get_Adc2(); //获取ADC2的转换值
    initial_lcd();
    LCD_Clear();
    delay_ms(300);
    LCD_Refresh_Gram();
    
    //定时器
    Timerx_Init(99, 71);
    
    LCD_Clear();
    
    // AD985x 初始化
    AD985x_Init(AD9850, SERIAL); //初始化控制AD9850需要用到的IO口,设置为串行通讯
    
    AD985x_SetFre_Phase(1000, 0);
    
    printf("DDS\r\n");

    while(1)
    {
        KeyRead(); //读取按键值 （内部备注不详，不用管） 
        Set_PointFre(Keycode, 0); //按键处理
        if (_return) {
            _return = 0;
            LCD_Refresh_Gram(); //更新显示
        }
//        printf("FRE:");
//        usartstr_u(NowFre); //显示此时频率
//        printf("Hz\r\n"); //换行
//        printf("SINFRE:");
//        usartstr_u(Sinfre); //显示此时频率
//        printf("Hz\r\n"); //换行
        
        if (NowFre != 0 && NowFre != lastNowFre) {  // 当 NowFre 不为零时，设置显示标志并标记开始
            displayFlag = 1;
            isStarted = 1;
        }

        // 判断NowFre是否发生变化
//        if (NowFre == lastNowFre) {
//            // 如果频率不变，maxFreq 和 minFreq 设为零
//            maxFreq = 0;
//            minFreq = 0;
//            displayFlag = 0;
//            isStarted = 0;
//            m=0;
//            n=4095;
//        }
        // 判断NowFre是否发生变化
        if (chongzhi==1) {
            // 如果频率不变，maxFreq 和 minFreq 设为零
            maxFreq = 0;
            minFreq = 0;
            displayFlag = 0;
            isStarted = 0;
            m=0;
            n=4095;
            chongzhi=0;
        }
        

        adc1 = Get_Adc1(); //获取通道4的转换值
//        usartstr_x(adc1); //发送adc1原始值
//        printf("\r\n"); //换行

        if (isStarted && adc1 > m)  // 只有在开始之后才存储最大值时刻的频率
        {
            m = adc1; //比较大小，找最大值
            maxFreq = NowFre; // 保存最大值时的频率
//            usartstr_u(NowFre); //显示此时频率
//            printf("Hz\r\n"); //换行
        }
//        usartstr_x(m); //发送m原始值
//        printf("\r\n"); //换行
        temp1 = (float)adc1 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        printf("PHASE_V:");
//        usartstr_f(temp1);
//        printf("\r\n"); //换行
        
        //显示最大值
//        printf("max:");
        mm = m;
        temp3 = (float)mm * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp3); 
//        printf("\r\n"); //换行
        if (displayFlag) {
            printf("MaxFreq: %uHz\r\n", maxFreq); // 显示最大值时的频率
        }
        
        adc2 = Get_Adc2(); //获取通道5的转换值
//        usartstr_x(adc2); //发送adc2原始值
//        printf("\r\n"); //换行

        if (isStarted && adc2 < n)  // 只有在开始之后才存储最小值时刻的频率
        {
            n = adc2; //比较大小，找最小值
            minFreq = NowFre; // 保存最小值时的频率
        }
//        usartstr_x(n); //发送n原始值
//        printf("\r\n"); //换行
//        printf("AMPLITUDE_V:");
        //显示ADC值
        temp2 = (float)adc2 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp2);
//        printf("\r\n"); //换行
        
        //显示最小值
//        printf("min:");
        nn = n;
        temp4 = (float)nn * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp4);
//        printf("\r\n"); //换行
        if (displayFlag) {
            printf("MinFreq: %uHz\r\n", minFreq); // 显示最小值时的频率
        }
        
        LED1 = !LED1;
//        printf("\r\n"); //换行
        delay_ms(250); 
        
        // 更新 lastNowFre 为当前的 NowFre
        lastNowFre = NowFre;

        KEY_EXIT();
    }   
}

//#include "stm32_config.h"
//#include "stdio.h"
//#include "led.h"
//#include "lcd.h"
//#include "AD985x.h" 
//#include "key.h"
//#include "timer.h"
//#include "task_manage.h"
//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "adc.h"

//char str[30];  //显示缓存
//extern u8 _return;
//extern u32 NowFre;
//extern u32 Sinfre;

//u8 displayFlag = 0;  // 显示最大最小值时的频率标志位
//u8 isStarted = 0;    // 是否开始标志位

//u32 lastNowFre = 0;  // 存储上一次的频率值

//void StartSweep();

//int main(void)
//{
//    u16 adc1, adc2;
//    u16 m = 0;
//    u16 n = 4095;
//    u16 mm, nn;
//    u32 maxFreq = 0;   // 最大值时的频率
//    u32 minFreq = 0;   // 最小值时的频率
//    float temp1;
//    float temp2;
//    float temp3;
//    float temp4;
//    
//    u16 execution_count = 0; // 计数变量，用于计数执行次数

//    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //设置中断分组 
//    delay_init(72); //初始化延时函数
//    LED_Init(); //初始化LED接口
//    key_init();
//    uart_init(115200);
//    adc_Init();
//    adc2 = Get_Adc2(); //获取ADC2的转换值
//    initial_lcd();
//    LCD_Clear();
//    delay_ms(300);
//    LCD_Refresh_Gram();

//    //定时器
//    Timerx_Init(99, 71);

//    LCD_Clear();

//    // AD985x 初始化
//    AD985x_Init(AD9850, SERIAL); //初始化控制AD9850需要用到的IO口,设置为串行通讯

//    AD985x_SetFre_Phase(1000, 0);

//    printf("DDS\r\n");

//    while (1)
//    {
//        KeyRead(); //读取按键值 （内部备注不详，不用管） 
//        Set_PointFre(Keycode, 0); //按键处理
//        if (_return) {
//            _return = 0;
//            LCD_Refresh_Gram(); //更新显示
//        }
//        printf("FRE:");
//        usartstr_u(NowFre); //显示此时频率
//        printf("Hz\r\n"); //换行
//        printf("SINFRE:");
//        usartstr_u(Sinfre); //显示此时频率
//        printf("Hz\r\n"); //换行

//        if (NowFre != 0) {  // 当 NowFre 不为零时，设置显示标志并标记开始
//            displayFlag = 1;
//            isStarted = 1;
//        }

//        adc1 = Get_Adc1(); //获取通道4的转换值
//        usartstr_x(adc1); //发送adc1原始值
//        printf("\r\n"); //换行

//        if (isStarted && adc1 > m)  // 只有在开始之后才存储最大值时刻的频率
//        {
//            m = adc1; //比较大小，找最大值
//            maxFreq = NowFre; // 保存最大值时的频率
//            usartstr_u(NowFre); //显示此时频率
//            printf("Hz\r\n"); //换行
//        }
//        usartstr_x(m); //发送m原始值
//        printf("\r\n"); //换行
//        temp1 = (float)adc1 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        printf("PHASE_V:");
//        usartstr_f(temp1);
//        printf("\r\n"); //换行

//        //显示最大值
//        printf("max:");
//        mm = m;
//        temp3 = (float)mm * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp3);
//        printf("\r\n"); //换行
//        if (displayFlag) {
//            printf("MaxFreq: %uHz\r\n", maxFreq); // 显示最大值时的频率
//        }

//        adc2 = Get_Adc2(); //获取通道5的转换值
//        usartstr_x(adc2); //发送adc2原始值
//        printf("\r\n"); //换行

//        if (isStarted && adc2 < n)  // 只有在开始之后才存储最小值时刻的频率
//        {
//            n = adc2; //比较大小，找最小值
//            minFreq = NowFre; // 保存最小值时的频率
//        }
//        usartstr_x(n); //发送n原始值
//        printf("\r\n"); //换行
//        printf("AMPLITUDE_V:");
//        //显示ADC值
//        temp2 = (float)adc2 * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp2);
//        printf("\r\n"); //换行

//        //显示最小值
//        printf("min:");
//        nn = n;
//        temp4 = (float)nn * (3.3 / 4096); //获取计算后的带小数的实际电压值，比如3.1111
//        usartstr_f(temp4);
//        printf("\r\n"); //换行
//        if (displayFlag) {
//            printf("MinFreq: %uHz\r\n", minFreq); // 显示最小值时的频率
//        }

//        LED1 = !LED1;
//        printf("%uhz\r\n",execution_count);
//        printf("\r\n"); //换行
//        delay_ms(250); 
//        KEY_EXIT();
//        
//        // 计数执行次数
//        execution_count++;
//        if (execution_count >= 100) {
//            // 每执行100次时重置变量
//            maxFreq = 0;
//            minFreq = 0;
//            displayFlag = 0;
//            isStarted = 0;
//            m = 0;
//            n = 4095;
//            execution_count = 0;  // 计数器清零
//        }
//        
//    }
//}

