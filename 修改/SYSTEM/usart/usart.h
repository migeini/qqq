#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 


#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long
#define int16    short int
#define int32    long




#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义

//void Uart_Init(uint32 Baudrate);
void uart_init(u32 bound);
void usartSendByte(USART_TypeDef* USARTx, uint16_t Data);
void usartSendStr(USART_TypeDef* USARTx,char *str);
void usartstr_f(float f);
void usartstr_x(u16 hx);
void usartstr_u(u32 u);
void  SendChar(uchar t);
#endif


