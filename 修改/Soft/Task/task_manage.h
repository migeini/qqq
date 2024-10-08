#ifndef __task_manage_H
#define __task_manage_H
#include "stm32f10x.h"
#include "lcd.h"
#include "key.h"

#define Interface 2//��������
#define StrMax    10//�������ݴ�С

extern u32 SysTimer;


void Copybuf2dis(u8 *source, u8 dis[StrMax], u8 dispoint, u8 FloatNum, u8 CursorEn);
void Set_PointFre(u32 Key_Value, u8* Task_ID);
void Sweep_Fre(u32 Key_Value, u8* Task_ID);

//
void Task0_PointFre(u32 Key_Value);		//���Ҳ�
void Task1_Square(u32 Key_Value);		//���� 300k
void Task2_Triangular(u32 Key_Value);	//���ǲ� 1M
void Task3_SweepFre(u32 Key_Value);		//ɨƵ
void fre_buf_change(u8 *strbuf);


#endif
