#ifndef __PING_H
#define __PING_H
#include "sys.h"

#define GRAPH_PAGE_ID       0x02
#define GRAPH_CONTROL_ID    0x01

typedef enum 
{
    TEXT_TEST_PAGE_ID = 0x01,			//检测页面
    TEXT_SWEEP_PAGE_ID = 0x02,			//扫频页面
}TEXT_PAGE_ID;//画面ID
typedef enum
{
    //检测页面
	TEXT_SIN_MAXFre_CONTROL_ID = 0x02,				//正弦,最大频率
    TEXT_SWEEP_MINFre_CONTROL_ID = 0x03,			//扫频,最小频率
    TEXT_SQUARE_STEP_CONTROL_ID = 0x04,			//方波,步长
    TEXT_PHASE_TIME_CONTROL_ID = 0x05,			//相位端电压,时间
	TEXT_AMPL_CONTROL_ID = 0x06,			//幅值端电压
	TEXT_MAX_CONTROL_ID = 0x07,				//最大值
	TEXT_MIN_CONTROL_ID = 0x08,				//最小值
	TEXT_MAXF_CONTROL_ID = 0x09,			//最值频率
	TEXT_MINF_CONTROL_ID = 0x0a,			//最值频率
}TEXT_CONTROL_ID;//文本控件ID


extern unsigned char chart_1_data[4];
extern unsigned char chart_2_data[20];
extern unsigned char chart_3_data[4];
extern unsigned char chart_4_data[4];
extern unsigned char chart_5_data[4];
extern unsigned char chart_6_data[20];

void screen_text_sendvalue(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,u8 datalen, u8 *data);
void screen_text_getvalue(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid);
void screenShowDataFromFloat(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,float value,int mode);


#endif








