#include "ping.h " 
#include "delay.h"
#include "sys.h"
#include "usart.h"

const u8 text_get_data_frame_head[3] = {0xEE,0xB1,0x11};	
const u8 text_frame_head[3] = {0xEE,0xB1,0x10};	
const u8 text_float_frame_head[3] = {0xEE,0xB1,0x07};
const u8 com_frame_end[4] = {0xFF,0xFC,0xFF,0xFF};


//����֡ͷ
static void screen_send_sel_framehead(const u8 * framehead)		
{
    for(int i=0;i < 3;i++)		
    {
        USART_SendData( USART1,framehead[i] );
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}

//���ͻ���ID 
static void screen_send_page_id(const u8* pageid)			
{
    for(int j = 0;j < 2;j++)	
    {
        USART_SendData( USART1,pageid[j]);			
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}

//���Ϳؼ�ID
static void screen_send_control_id(const u8* controlid)	
{	
    for(int j = 0;j < 2;j++)		
    {
        USART_SendData( USART1,controlid[j]);			
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}	

//��������
static void screen_send_data(u8 datalen,u8* data)		
{
    for(int a = 0;a < datalen;a++)			
    {
        USART_SendData( USART1,data[a] );				
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
}		

//����֡β
static void screen_send_com_frametail(void)					
{
    for(int k=0;k<4;k++)
    {
        USART_SendData( USART1,com_frame_end[k] );				
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}


//���庯����ͨ���������룬����������Ӧ�ռ䷢��ָ��//
/**
 * ԭ����:void Ping_SendValue(u8 x,u8 y, u8 *value )
 * �ֺ���:void screen_text_sendvalue(u8 pageid,u8 controlid, u8 *data)
 * ����:����Ļ���ı���������;
 * ֡ͷ:0xEE
 * ����:0xB1,0x10
 * ����:���ֽڻ���ID+���ֽڿؼ�ID+����������
 * ֡β:0xFF,0xFC,0xFF,0xFF
 * һ֡����:0xEE 0xB1 0x10 0x00 0x01 0x00 0x01 0x.. 0x.. 0x.. 0x.. 0xFF 0xFC 0xFF 0xFF
*/
void screen_text_sendvalue(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,u8 datalen, u8 *data)
{
    u8 pageidtmp[2]={0x00,0x00};
    u8 controlidtmp[2]={0x00,0x00};

	switch(pageid)//����IDѡ��
	{
		case TEXT_TEST_PAGE_ID:
			pageidtmp[1]=0x01;
		break;
		
		case TEXT_SWEEP_PAGE_ID:
			pageidtmp[1]=0x02;
		break;
		
	}
	switch(controlid)//�ؼ�IDѡ��
	{
		case TEXT_SIN_MAXFre_CONTROL_ID:
			controlidtmp[1] = 0x02;
		break;
			
		case TEXT_SWEEP_MINFre_CONTROL_ID:
			controlidtmp[1] = 0x03;
		break;
		
		case TEXT_SQUARE_STEP_CONTROL_ID:
			controlidtmp[1] = 0x04;
		break;		

		case TEXT_PHASE_TIME_CONTROL_ID:
			controlidtmp[1] = 0x05;
		break;	
		
		case TEXT_AMPL_CONTROL_ID:
			controlidtmp[1] = 0x06;
		break;
		
		case TEXT_MAX_CONTROL_ID:
			controlidtmp[1] = 0x07;
		break;
		
		case TEXT_MIN_CONTROL_ID:
			controlidtmp[1] = 0x08;
		break;
			
		case TEXT_MAXF_CONTROL_ID:
			controlidtmp[1] = 0x09;
		break;
		
		case TEXT_MINF_CONTROL_ID:
			controlidtmp[1] = 0x0a;
		break;
	}
	//��������֡
	screen_send_sel_framehead(text_frame_head);//֡ͷ
    screen_send_page_id(pageidtmp);//����id
	screen_send_control_id(controlidtmp);//�ؼ�id
	screen_send_data(datalen,data);//����������
    screen_send_com_frametail();//֡β
}

//���庯����ͨ���������룬����������Ӧ�ռ䷢��ָ��//
/**
 * �ֺ���:void screen_text_getvalue(u8 pageid,u8 controlid)
 * ����:��ȡ�ı�������
 * ֡ͷ:0xEE
 * ����:0xB1,0x11
 * ����:���ֽڻ���ID+���ֽڿؼ�ID+����������
 * ֡β:0xFF,0xFC,0xFF,0xFF
 * һ֡����:0xEE 0xB1 0x11 0x00 0x01 0x00 0x01 0x.. 0x.. 0x.. 0x.. 0xFF 0xFC 0xFF 0xFF
*/
void screen_text_getvalue(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid)
{
    u8 pageidtmp[2]={0x00,0x00};
    u8 controlidtmp[2]={0x00,0x00};

	switch(pageid)//����IDѡ��
	{
		case TEXT_TEST_PAGE_ID:
			pageidtmp[1]=0x01;
		break;
		
		case TEXT_SWEEP_PAGE_ID:
			pageidtmp[1]=0x02;
		break;
		
	}
	switch(controlid)//�ؼ�IDѡ��
	{
		case TEXT_SIN_MAXFre_CONTROL_ID:
			controlidtmp[1] = 0x02;
		break;
			
		case TEXT_SWEEP_MINFre_CONTROL_ID:
			controlidtmp[1] = 0x03;
		break;
		
		case TEXT_SQUARE_STEP_CONTROL_ID:
			controlidtmp[1] = 0x04;
		break;		

		case TEXT_PHASE_TIME_CONTROL_ID:
			controlidtmp[1] = 0x05;
		break;	
		
		case TEXT_AMPL_CONTROL_ID:
			controlidtmp[1] = 0x06;
		break;
		
		case TEXT_MAX_CONTROL_ID:
			controlidtmp[1] = 0x07;
		break;
		
		case TEXT_MIN_CONTROL_ID:
			controlidtmp[1] = 0x08;
		break;
			
		case TEXT_MAXF_CONTROL_ID:
			controlidtmp[1] = 0x09;
		break;
		
		case TEXT_MINF_CONTROL_ID:
			controlidtmp[1] = 0x0a;
		break;
	}
	//��������֡
	screen_send_sel_framehead(text_get_data_frame_head);//֡ͷ
    screen_send_page_id(pageidtmp);//����id
	screen_send_control_id(controlidtmp);//�ؼ�id
    screen_send_com_frametail();//֡β
}



//���庯����ͨ���������룬����������Ӧ�ռ䷢��ָ��//
/**
 * ������:void screenShowDataFromFloat(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,float value,int mode)
 * ����:����Ļ���ı����͸���������;
 * ֡ͷ:0xEE
 * ����:0xB1,0x10
 * ����:���ֽڻ���ID+���ֽڿؼ�ID+����������
 * ����:0x02,0x86       02��ʾ����������
 * ֡β:0xFF,0xFC,0xFF,0xFF
 * һ֡����:0xEE 0xB1 0x07 0x00 0x01 0x00 0x01 0x02 0x80 0x.. 0x.. 0x.. 0xFF 0xFC 0xFF 0xFF
*/

unsigned char screenShowfloatSetBuf[2] = {0x02,0x80};
void screenShowDataFromFloat(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,float value,int mode)
{
	unsigned char i = 0;
    unsigned char val = 0;
	u8 pageidtmp[2]={0x00,0x00};
    u8 controlidtmp[2]={0x00,0x00};

	switch(pageid)//����IDѡ��
	{
		case TEXT_TEST_PAGE_ID:
			pageidtmp[1]=0x01;
		break;
		
		case TEXT_SWEEP_PAGE_ID:
			pageidtmp[1]=0x02;
		break;
		
	}
	switch(controlid)//�ؼ�IDѡ��
	{
		case TEXT_SIN_MAXFre_CONTROL_ID:
			controlidtmp[1] = 0x02;
		break;
			
		case TEXT_SWEEP_MINFre_CONTROL_ID:
			controlidtmp[1] = 0x03;
		break;
		
		case TEXT_SQUARE_STEP_CONTROL_ID:
			controlidtmp[1] = 0x04;
		break;		

		case TEXT_PHASE_TIME_CONTROL_ID:
			controlidtmp[1] = 0x05;
		break;	
		
		case TEXT_AMPL_CONTROL_ID:
			controlidtmp[1] = 0x06;
		break;
		
		case TEXT_MAX_CONTROL_ID:
			controlidtmp[1] = 0x07;
		break;
		
		case TEXT_MIN_CONTROL_ID:
			controlidtmp[1] = 0x08;
		break;
			
		case TEXT_MAXF_CONTROL_ID:
			controlidtmp[1] = 0x09;
		break;
		
		case TEXT_MINF_CONTROL_ID:
			controlidtmp[1] = 0x0a;
		break;
	}
	//��������֡

	screen_send_sel_framehead(text_float_frame_head);//֡ͷ
	screen_send_page_id(pageidtmp);
	screen_send_control_id(controlidtmp);
	USART_SendData(USART1,screenShowfloatSetBuf[0]);
	USART_SendData(USART1,screenShowfloatSetBuf[1]);
	
	for (i=0;i<4;++i)
	{
        if(mode)
        {
            val = ((unsigned char*)&value)[i];
			USART_SendData(USART1,val);
        }
        else
        {
            val = ((unsigned char*)&value)[3-i];
			USART_SendData(USART1,val);			
		}
	}
	screen_send_com_frametail();
}

