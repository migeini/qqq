#ifndef __PING_H
#define __PING_H
#include "sys.h"

#define GRAPH_PAGE_ID       0x02
#define GRAPH_CONTROL_ID    0x01

typedef enum 
{
    TEXT_TEST_PAGE_ID = 0x01,			//���ҳ��
    TEXT_SWEEP_PAGE_ID = 0x02,			//ɨƵҳ��
}TEXT_PAGE_ID;//����ID
typedef enum
{
    //���ҳ��
	TEXT_SIN_MAXFre_CONTROL_ID = 0x02,				//����,���Ƶ��
    TEXT_SWEEP_MINFre_CONTROL_ID = 0x03,			//ɨƵ,��СƵ��
    TEXT_SQUARE_STEP_CONTROL_ID = 0x04,			//����,����
    TEXT_PHASE_TIME_CONTROL_ID = 0x05,			//��λ�˵�ѹ,ʱ��
	TEXT_AMPL_CONTROL_ID = 0x06,			//��ֵ�˵�ѹ
	TEXT_MAX_CONTROL_ID = 0x07,				//���ֵ
	TEXT_MIN_CONTROL_ID = 0x08,				//��Сֵ
	TEXT_MAXF_CONTROL_ID = 0x09,			//��ֵƵ��
	TEXT_MINF_CONTROL_ID = 0x0a,			//��ֵƵ��
}TEXT_CONTROL_ID;//�ı��ؼ�ID


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








