///**********************************************************
//                       ��������										 
//���ܣ�stm32f103����AD985x������Σ������м�����л�ɨƵ
//			��ʾ��12864cog
//�ӿڣ����ƽӿ������AD985x.h  �����ӿ������key.h
//ʱ�䣺2023/06/xx
//�汾��0.7
//���ߣ���������
//������������ֻ��ѧϰʹ�ã�����ؾ���
//˵��������AD9850ģ����ؾ���125Mhz����Ϊ�ο�ʱ�����롣оƬ��֧�ֱ�Ƶ
//			����AD9851ģ����ؾ���30Mhz,����Ĭ������6��Ƶ����180Mhz����Ϊ�ο�ʱ�����롣

//					AD985x			��Ƭ��
//Ӳ������:	AD985x_rst 	PA6
//					AD985x_clk 	PA4	
//					AD985x_fq 	PA3	
//					D0-07 			PC0-PC7
//					5V					--5V 
//					GND					--GND(0V)  

//������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
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

//char str[30];	//��ʾ����
//extern u8 _return;
//extern u32 NowFre;
//extern u32 Sinfre;
//int main(void)
//{
//	u16 adc1, adc2;
//	u16 m = 0;
//	u16 n = 4095;
//	u16 mm, nn;
//	u32 maxFreq = 0;   // ���ֵʱ��Ƶ��
//	u32 minFreq = 0;   // ��Сֵʱ��Ƶ��
//	float temp1;
//	float temp2;
//	float temp3;
//	float temp4;	
//	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//�����жϷ��� 
//	delay_init(72);	//��ʼ����ʱ����
//	LED_Init();	//��ʼ��LED�ӿ�
//	key_init();
//	uart_init(115200);
//	adc_Init();
//	adc2 = Get_Adc2();	//��ȡADC2��ת��ֵ
//	initial_lcd();
//	LCD_Clear();
//	delay_ms(300);
//	LCD_Refresh_Gram();
//	
//	//��ʱ��
//	Timerx_Init(99, 71);
//	
//	LCD_Clear();
//	
//	// AD985x ��ʼ��
//	AD985x_Init(AD9850, SERIAL);	//��ʼ������AD9850��Ҫ�õ���IO��,����Ϊ����ͨѶ
//	
//	AD985x_SetFre_Phase(1000, 0);
//	
//	printf("DDS\r\n");

//	while(1)
//	{
//		KeyRead(); //��ȡ����ֵ ���ڲ���ע���꣬���ùܣ� 
//		Set_PointFre(Keycode, 0); //��������
//		if(_return) {
//			_return = 0;
//			LCD_Refresh_Gram(); //������ʾ
//		}
//		printf("FRE:");
//		usartstr_u(NowFre); //��ʾ��ʱƵ��
//		printf("Hz\r\n"); //����
//		printf("SINFRE:");
//		usartstr_u(Sinfre); //��ʾ��ʱƵ��
//		printf("Hz\r\n"); //����
//		
//		adc1 = Get_Adc1(); //��ȡͨ��4��ת��ֵ
//		usartstr_x(adc1); //����adc1ԭʼֵ
//		printf("\r\n"); //����
//		if(adc1 > m)
//		{
//			m = adc1; //�Ƚϴ�С�������ֵ
//			maxFreq = NowFre; // �������ֵʱ��Ƶ��
//			usartstr_u(NowFre); //��ʾ��ʱƵ��
//			printf("Hz\r\n"); //����
//		}
//		usartstr_x(m); //����mԭʼֵ
//		printf("\r\n"); //����
//		temp1 = (float)adc1 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		printf("PHASE_V:");
//		usartstr_f(temp1);
//		printf("\r\n"); //����
//		
//		//��ʾ���ֵ
//		printf("max:");
//		mm = m;
//		temp3 = (float)mm * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		usartstr_f(temp3);	
//		printf("\r\n"); //����
//		printf("MaxFreq: %uHz\r\n", maxFreq); // ��ʾ���ֵʱ��Ƶ��
//		
//		adc2 = Get_Adc2(); //��ȡͨ��5��ת��ֵ
//		usartstr_x(adc2); //����adc2ԭʼֵ
//		printf("\r\n"); //����
//		if(adc2 < n)
//		{
//			n = adc2; //�Ƚϴ�С������Сֵ
//			minFreq = NowFre; // ������Сֵʱ��Ƶ��
//		}
//		usartstr_x(n); //����nԭʼֵ
//		printf("\r\n"); //����
//		printf("AMPLITUDE_V:");
//		//��ʾADCֵ
//		temp2 = (float)adc2 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		usartstr_f(temp2);
//		printf("\r\n"); //����
//		
//		//��ʾ��Сֵ
//		printf("min:");
//		nn = n;
//		temp4 = (float)nn * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//		usartstr_f(temp4);
//		printf("\r\n"); //����
//		printf("MinFreq: %uHz\r\n", minFreq); // ��ʾ��Сֵʱ��Ƶ��
//		
//		LED1 = !LED1;
//		printf("\r\n"); //����
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

//char str[30];  //��ʾ����
//extern u8 _return;
//extern u32 NowFre;
//extern u32 Sinfre;

//u8 displayFlag = 0;  // ��ʾ�����Сֵʱ��Ƶ�ʱ�־λ
//u8 isStarted = 0;    // �Ƿ�ʼ��־λ

//void StartSweep();

//int main(void)
//{
//    u16 adc1, adc2;
//    u16 m = 0;
//    u16 n = 4095;
//    u16 mm, nn;
//    u32 maxFreq = 0;   // ���ֵʱ��Ƶ��
//    u32 minFreq = 0;   // ��Сֵʱ��Ƶ��
//    float temp1;
//    float temp2;
//    float temp3;
//    float temp4; 
//    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //�����жϷ��� 
//    delay_init(72); //��ʼ����ʱ����
//    LED_Init(); //��ʼ��LED�ӿ�
//    key_init();
//    uart_init(115200);
//    adc_Init();
//    adc2 = Get_Adc2(); //��ȡADC2��ת��ֵ
//    initial_lcd();
//    LCD_Clear();
//    delay_ms(300);
//    LCD_Refresh_Gram();
//    
//    //��ʱ��
//    Timerx_Init(99, 71);
//    
//    LCD_Clear();
//    
//    // AD985x ��ʼ��
//    AD985x_Init(AD9850, SERIAL); //��ʼ������AD9850��Ҫ�õ���IO��,����Ϊ����ͨѶ
//    
//    AD985x_SetFre_Phase(1000, 0);
//    
//    printf("DDS\r\n");

//    while(1)
//    {
//        KeyRead(); //��ȡ����ֵ ���ڲ���ע���꣬���ùܣ� 
//        Set_PointFre(Keycode, 0); //��������
//        if (_return) {
//            _return = 0;
//            LCD_Refresh_Gram(); //������ʾ
//        }
//        printf("FRE:");
//        usartstr_u(NowFre); //��ʾ��ʱƵ��
//        printf("Hz\r\n"); //����
//        printf("SINFRE:");
//        usartstr_u(Sinfre); //��ʾ��ʱƵ��
//        printf("Hz\r\n"); //����
//        
//        if (NowFre != 0) {  // �� NowFre ��Ϊ��ʱ��������ʾ��־����ǿ�ʼ
//            displayFlag = 1;
//            isStarted = 1;
//        }

//        adc1 = Get_Adc1(); //��ȡͨ��4��ת��ֵ
//        usartstr_x(adc1); //����adc1ԭʼֵ
//        printf("\r\n"); //����

//        if (isStarted && adc1 > m)  // ֻ���ڿ�ʼ֮��Ŵ洢���ֵʱ�̵�Ƶ��
//        {
//            m = adc1; //�Ƚϴ�С�������ֵ
//            maxFreq = NowFre; // �������ֵʱ��Ƶ��
//            usartstr_u(NowFre); //��ʾ��ʱƵ��
//            printf("Hz\r\n"); //����
//        }
//        usartstr_x(m); //����mԭʼֵ
//        printf("\r\n"); //����
//        temp1 = (float)adc1 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        printf("PHASE_V:");
//        usartstr_f(temp1);
//        printf("\r\n"); //����
//        
//        //��ʾ���ֵ
//        printf("max:");
//        mm = m;
//        temp3 = (float)mm * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp3); 
//        printf("\r\n"); //����
//        if (displayFlag) {
//            printf("MaxFreq: %uHz\r\n", maxFreq); // ��ʾ���ֵʱ��Ƶ��
//        }
//        
//        adc2 = Get_Adc2(); //��ȡͨ��5��ת��ֵ
//        usartstr_x(adc2); //����adc2ԭʼֵ
//        printf("\r\n"); //����

//        if (isStarted && adc2 < n)  // ֻ���ڿ�ʼ֮��Ŵ洢��Сֵʱ�̵�Ƶ��
//        {
//            n = adc2; //�Ƚϴ�С������Сֵ
//            minFreq = NowFre; // ������Сֵʱ��Ƶ��
//        }
//        usartstr_x(n); //����nԭʼֵ
//        printf("\r\n"); //����
//        printf("AMPLITUDE_V:");
//        //��ʾADCֵ
//        temp2 = (float)adc2 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp2);
//        printf("\r\n"); //����
//        
//        //��ʾ��Сֵ
//        printf("min:");
//        nn = n;
//        temp4 = (float)nn * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp4);
//        printf("\r\n"); //����
//        if (displayFlag) {
//            printf("MinFreq: %uHz\r\n", minFreq); // ��ʾ��Сֵʱ��Ƶ��
//        }
//        
//        LED1 = !LED1;
//        printf("\r\n"); //����
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

char str[30];  //��ʾ����
extern u8 _return;
extern u32 NowFre;
extern u32 Sinfre;

u8 displayFlag = 0;  // ��ʾ�����Сֵʱ��Ƶ�ʱ�־λ
u8 isStarted = 0;    // �Ƿ�ʼ��־λ

u32 lastNowFre = 0;  // �洢��һ�ε�Ƶ��ֵ

//void StartSweep();

int main(void)
{
    u16 adc1, adc2;
    u16 m = 0;
    u16 n = 4095;
    u16 mm, nn;
//    u32 maxFreq = 0;   // ���ֵʱ��Ƶ��
//    u32 minFreq = 0;   // ��Сֵʱ��Ƶ��
//    float temp1;
//    float temp2;
//    float temp3;
//    float temp4; 
    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //�����жϷ��� 
    delay_init(72); //��ʼ����ʱ����
    LED_Init(); //��ʼ��LED�ӿ�
    key_init();
    uart_init(115200);
    adc_Init();
    adc2 = Get_Adc2(); //��ȡADC2��ת��ֵ
    initial_lcd();
    LCD_Clear();
    delay_ms(300);
    LCD_Refresh_Gram();
    
    //��ʱ��
    Timerx_Init(99, 71);
    
    LCD_Clear();
    
    // AD985x ��ʼ��
    AD985x_Init(AD9850, SERIAL); //��ʼ������AD9850��Ҫ�õ���IO��,����Ϊ����ͨѶ
    
    AD985x_SetFre_Phase(1000, 0);
    
    printf("DDS\r\n");

    while(1)
    {
        KeyRead(); //��ȡ����ֵ ���ڲ���ע���꣬���ùܣ� 
        Set_PointFre(Keycode, 0); //��������
        if (_return) {
            _return = 0;
            LCD_Refresh_Gram(); //������ʾ
        }
//        printf("FRE:");
//        usartstr_u(NowFre); //��ʾ��ʱƵ��
//        printf("Hz\r\n"); //����
//        printf("SINFRE:");
//        usartstr_u(Sinfre); //��ʾ��ʱƵ��
//        printf("Hz\r\n"); //����
        
        if (NowFre != 0 && NowFre != lastNowFre) {  // �� NowFre ��Ϊ��ʱ��������ʾ��־����ǿ�ʼ
            displayFlag = 1;
            isStarted = 1;
        }

        // �ж�NowFre�Ƿ����仯
//        if (NowFre == lastNowFre) {
//            // ���Ƶ�ʲ��䣬maxFreq �� minFreq ��Ϊ��
//            maxFreq = 0;
//            minFreq = 0;
//            displayFlag = 0;
//            isStarted = 0;
//            m=0;
//            n=4095;
//        }
        // �ж�NowFre�Ƿ����仯
        if (chongzhi==1) {
            // ���Ƶ�ʲ��䣬maxFreq �� minFreq ��Ϊ��
            maxFreq = 0;
            minFreq = 0;
            displayFlag = 0;
            isStarted = 0;
            m=0;
            n=4095;
            chongzhi=0;
        }
        

        adc1 = Get_Adc1(); //��ȡͨ��4��ת��ֵ
//        usartstr_x(adc1); //����adc1ԭʼֵ
//        printf("\r\n"); //����

        if (isStarted && adc1 > m)  // ֻ���ڿ�ʼ֮��Ŵ洢���ֵʱ�̵�Ƶ��
        {
            m = adc1; //�Ƚϴ�С�������ֵ
            maxFreq = NowFre; // �������ֵʱ��Ƶ��
//            usartstr_u(NowFre); //��ʾ��ʱƵ��
//            printf("Hz\r\n"); //����
        }
//        usartstr_x(m); //����mԭʼֵ
//        printf("\r\n"); //����
        temp1 = (float)adc1 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        printf("PHASE_V:");
//        usartstr_f(temp1);
//        printf("\r\n"); //����
        
        //��ʾ���ֵ
//        printf("max:");
        mm = m;
        temp3 = (float)mm * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp3); 
//        printf("\r\n"); //����
        if (displayFlag) {
            printf("MaxFreq: %uHz\r\n", maxFreq); // ��ʾ���ֵʱ��Ƶ��
        }
        
        adc2 = Get_Adc2(); //��ȡͨ��5��ת��ֵ
//        usartstr_x(adc2); //����adc2ԭʼֵ
//        printf("\r\n"); //����

        if (isStarted && adc2 < n)  // ֻ���ڿ�ʼ֮��Ŵ洢��Сֵʱ�̵�Ƶ��
        {
            n = adc2; //�Ƚϴ�С������Сֵ
            minFreq = NowFre; // ������Сֵʱ��Ƶ��
        }
//        usartstr_x(n); //����nԭʼֵ
//        printf("\r\n"); //����
//        printf("AMPLITUDE_V:");
        //��ʾADCֵ
        temp2 = (float)adc2 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp2);
//        printf("\r\n"); //����
        
        //��ʾ��Сֵ
//        printf("min:");
        nn = n;
        temp4 = (float)nn * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp4);
//        printf("\r\n"); //����
        if (displayFlag) {
            printf("MinFreq: %uHz\r\n", minFreq); // ��ʾ��Сֵʱ��Ƶ��
        }
        
        LED1 = !LED1;
//        printf("\r\n"); //����
        delay_ms(250); 
        
        // ���� lastNowFre Ϊ��ǰ�� NowFre
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

//char str[30];  //��ʾ����
//extern u8 _return;
//extern u32 NowFre;
//extern u32 Sinfre;

//u8 displayFlag = 0;  // ��ʾ�����Сֵʱ��Ƶ�ʱ�־λ
//u8 isStarted = 0;    // �Ƿ�ʼ��־λ

//u32 lastNowFre = 0;  // �洢��һ�ε�Ƶ��ֵ

//void StartSweep();

//int main(void)
//{
//    u16 adc1, adc2;
//    u16 m = 0;
//    u16 n = 4095;
//    u16 mm, nn;
//    u32 maxFreq = 0;   // ���ֵʱ��Ƶ��
//    u32 minFreq = 0;   // ��Сֵʱ��Ƶ��
//    float temp1;
//    float temp2;
//    float temp3;
//    float temp4;
//    
//    u16 execution_count = 0; // �������������ڼ���ִ�д���

//    MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2); //�����жϷ��� 
//    delay_init(72); //��ʼ����ʱ����
//    LED_Init(); //��ʼ��LED�ӿ�
//    key_init();
//    uart_init(115200);
//    adc_Init();
//    adc2 = Get_Adc2(); //��ȡADC2��ת��ֵ
//    initial_lcd();
//    LCD_Clear();
//    delay_ms(300);
//    LCD_Refresh_Gram();

//    //��ʱ��
//    Timerx_Init(99, 71);

//    LCD_Clear();

//    // AD985x ��ʼ��
//    AD985x_Init(AD9850, SERIAL); //��ʼ������AD9850��Ҫ�õ���IO��,����Ϊ����ͨѶ

//    AD985x_SetFre_Phase(1000, 0);

//    printf("DDS\r\n");

//    while (1)
//    {
//        KeyRead(); //��ȡ����ֵ ���ڲ���ע���꣬���ùܣ� 
//        Set_PointFre(Keycode, 0); //��������
//        if (_return) {
//            _return = 0;
//            LCD_Refresh_Gram(); //������ʾ
//        }
//        printf("FRE:");
//        usartstr_u(NowFre); //��ʾ��ʱƵ��
//        printf("Hz\r\n"); //����
//        printf("SINFRE:");
//        usartstr_u(Sinfre); //��ʾ��ʱƵ��
//        printf("Hz\r\n"); //����

//        if (NowFre != 0) {  // �� NowFre ��Ϊ��ʱ��������ʾ��־����ǿ�ʼ
//            displayFlag = 1;
//            isStarted = 1;
//        }

//        adc1 = Get_Adc1(); //��ȡͨ��4��ת��ֵ
//        usartstr_x(adc1); //����adc1ԭʼֵ
//        printf("\r\n"); //����

//        if (isStarted && adc1 > m)  // ֻ���ڿ�ʼ֮��Ŵ洢���ֵʱ�̵�Ƶ��
//        {
//            m = adc1; //�Ƚϴ�С�������ֵ
//            maxFreq = NowFre; // �������ֵʱ��Ƶ��
//            usartstr_u(NowFre); //��ʾ��ʱƵ��
//            printf("Hz\r\n"); //����
//        }
//        usartstr_x(m); //����mԭʼֵ
//        printf("\r\n"); //����
//        temp1 = (float)adc1 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        printf("PHASE_V:");
//        usartstr_f(temp1);
//        printf("\r\n"); //����

//        //��ʾ���ֵ
//        printf("max:");
//        mm = m;
//        temp3 = (float)mm * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp3);
//        printf("\r\n"); //����
//        if (displayFlag) {
//            printf("MaxFreq: %uHz\r\n", maxFreq); // ��ʾ���ֵʱ��Ƶ��
//        }

//        adc2 = Get_Adc2(); //��ȡͨ��5��ת��ֵ
//        usartstr_x(adc2); //����adc2ԭʼֵ
//        printf("\r\n"); //����

//        if (isStarted && adc2 < n)  // ֻ���ڿ�ʼ֮��Ŵ洢��Сֵʱ�̵�Ƶ��
//        {
//            n = adc2; //�Ƚϴ�С������Сֵ
//            minFreq = NowFre; // ������Сֵʱ��Ƶ��
//        }
//        usartstr_x(n); //����nԭʼֵ
//        printf("\r\n"); //����
//        printf("AMPLITUDE_V:");
//        //��ʾADCֵ
//        temp2 = (float)adc2 * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp2);
//        printf("\r\n"); //����

//        //��ʾ��Сֵ
//        printf("min:");
//        nn = n;
//        temp4 = (float)nn * (3.3 / 4096); //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
//        usartstr_f(temp4);
//        printf("\r\n"); //����
//        if (displayFlag) {
//            printf("MinFreq: %uHz\r\n", minFreq); // ��ʾ��Сֵʱ��Ƶ��
//        }

//        LED1 = !LED1;
//        printf("%uhz\r\n",execution_count);
//        printf("\r\n"); //����
//        delay_ms(250); 
//        KEY_EXIT();
//        
//        // ����ִ�д���
//        execution_count++;
//        if (execution_count >= 100) {
//            // ÿִ��100��ʱ���ñ���
//            maxFreq = 0;
//            minFreq = 0;
//            displayFlag = 0;
//            isStarted = 0;
//            m = 0;
//            n = 4095;
//            execution_count = 0;  // ����������
//        }
//        
//    }
//}

