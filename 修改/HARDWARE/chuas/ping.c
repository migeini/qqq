#include "ping.h " 
#include "delay.h"
#include "sys.h"
#include "usart.h"

const u8 text_get_data_frame_head[3] = {0xEE,0xB1,0x11};	
const u8 text_frame_head[3] = {0xEE,0xB1,0x10};	
const u8 text_float_frame_head[3] = {0xEE,0xB1,0x07};
const u8 com_frame_end[4] = {0xFF,0xFC,0xFF,0xFF};


//发送帧头
static void screen_send_sel_framehead(const u8 * framehead)		
{
    for(int i=0;i < 3;i++)		
    {
        USART_SendData( USART1,framehead[i] );
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}

//发送画面ID 
static void screen_send_page_id(const u8* pageid)			
{
    for(int j = 0;j < 2;j++)	
    {
        USART_SendData( USART1,pageid[j]);			
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}

//发送控件ID
static void screen_send_control_id(const u8* controlid)	
{	
    for(int j = 0;j < 2;j++)		
    {
        USART_SendData( USART1,controlid[j]);			
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}	

//发送数据
static void screen_send_data(u8 datalen,u8* data)		
{
    for(int a = 0;a < datalen;a++)			
    {
        USART_SendData( USART1,data[a] );				
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    } 
}		

//发送帧尾
static void screen_send_com_frametail(void)					
{
    for(int k=0;k<4;k++)
    {
        USART_SendData( USART1,com_frame_end[k] );				
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}


//定义函数，通过变量输入，给串口屏相应空间发送指令//
/**
 * 原函数:void Ping_SendValue(u8 x,u8 y, u8 *value )
 * 现函数:void screen_text_sendvalue(u8 pageid,u8 controlid, u8 *data)
 * 作用:给屏幕的文本框发送数据;
 * 帧头:0xEE
 * 命令:0xB1,0x10
 * 数据:两字节画面ID+两字节控件ID+不定长数据
 * 帧尾:0xFF,0xFC,0xFF,0xFF
 * 一帧数据:0xEE 0xB1 0x10 0x00 0x01 0x00 0x01 0x.. 0x.. 0x.. 0x.. 0xFF 0xFC 0xFF 0xFF
*/
void screen_text_sendvalue(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,u8 datalen, u8 *data)
{
    u8 pageidtmp[2]={0x00,0x00};
    u8 controlidtmp[2]={0x00,0x00};

	switch(pageid)//画面ID选择
	{
		case TEXT_TEST_PAGE_ID:
			pageidtmp[1]=0x01;
		break;
		
		case TEXT_SWEEP_PAGE_ID:
			pageidtmp[1]=0x02;
		break;
		
	}
	switch(controlid)//控件ID选择
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
	//发送数据帧
	screen_send_sel_framehead(text_frame_head);//帧头
    screen_send_page_id(pageidtmp);//画面id
	screen_send_control_id(controlidtmp);//控件id
	screen_send_data(datalen,data);//不定长数据
    screen_send_com_frametail();//帧尾
}

//定义函数，通过变量输入，给串口屏相应空间发送指令//
/**
 * 现函数:void screen_text_getvalue(u8 pageid,u8 controlid)
 * 作用:获取文本的内容
 * 帧头:0xEE
 * 命令:0xB1,0x11
 * 数据:两字节画面ID+两字节控件ID+不定长数据
 * 帧尾:0xFF,0xFC,0xFF,0xFF
 * 一帧数据:0xEE 0xB1 0x11 0x00 0x01 0x00 0x01 0x.. 0x.. 0x.. 0x.. 0xFF 0xFC 0xFF 0xFF
*/
void screen_text_getvalue(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid)
{
    u8 pageidtmp[2]={0x00,0x00};
    u8 controlidtmp[2]={0x00,0x00};

	switch(pageid)//画面ID选择
	{
		case TEXT_TEST_PAGE_ID:
			pageidtmp[1]=0x01;
		break;
		
		case TEXT_SWEEP_PAGE_ID:
			pageidtmp[1]=0x02;
		break;
		
	}
	switch(controlid)//控件ID选择
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
	//发送数据帧
	screen_send_sel_framehead(text_get_data_frame_head);//帧头
    screen_send_page_id(pageidtmp);//画面id
	screen_send_control_id(controlidtmp);//控件id
    screen_send_com_frametail();//帧尾
}



//定义函数，通过变量输入，给串口屏相应空间发送指令//
/**
 * 函数名:void screenShowDataFromFloat(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,float value,int mode)
 * 作用:给屏幕的文本框发送浮点型数据;
 * 帧头:0xEE
 * 命令:0xB1,0x10
 * 数据:两字节画面ID+两字节控件ID+不定长数据
 * 命令:0x02,0x86       02表示浮点型数据
 * 帧尾:0xFF,0xFC,0xFF,0xFF
 * 一帧数据:0xEE 0xB1 0x07 0x00 0x01 0x00 0x01 0x02 0x80 0x.. 0x.. 0x.. 0xFF 0xFC 0xFF 0xFF
*/

unsigned char screenShowfloatSetBuf[2] = {0x02,0x80};
void screenShowDataFromFloat(TEXT_PAGE_ID pageid,TEXT_CONTROL_ID controlid,float value,int mode)
{
	unsigned char i = 0;
    unsigned char val = 0;
	u8 pageidtmp[2]={0x00,0x00};
    u8 controlidtmp[2]={0x00,0x00};

	switch(pageid)//画面ID选择
	{
		case TEXT_TEST_PAGE_ID:
			pageidtmp[1]=0x01;
		break;
		
		case TEXT_SWEEP_PAGE_ID:
			pageidtmp[1]=0x02;
		break;
		
	}
	switch(controlid)//控件ID选择
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
	//发送数据帧

	screen_send_sel_framehead(text_float_frame_head);//帧头
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

