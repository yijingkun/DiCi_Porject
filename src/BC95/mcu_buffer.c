/*
 * buffer.c
 *
 *  Created on: 2016-8-15
 *      Author: user
 */

#include "common.h"

//uart0 接收缓存区
char   recv0_buf[UART0_BUFFER_SIZE];
char * recv0_ptr=recv0_buf;
short  recv0_num;

//uart0 发送缓存区
char   send0_buf[UART0_BUFFER_SIZE];
char * send0_ptr;
short  send0_num;


/*******************************************************************
* 函数名 : Buffer_Uart0RecvClear
* 描述   : 清零UART0接收缓存区
* 输入   : 无
* 输出   : 无
* 返回   : 无
* 注意   : 缓存区大小为UART0_BUFFER_SIZE字节，客户可修改扩大
********************************************************************/
void Buffer_Uart0RecvClear(void)
{
	unsigned short i = 0;

	for(i=0; i<UART0_BUFFER_SIZE; i++)
	{
		recv0_buf[i] = 0x00;
	}

	recv0_ptr = recv0_buf;
	recv0_num = 0;
}

/*******************************************************************
* 函数名 : Buffer_Uart0SendClear
* 描述   : 清零UART0发送缓存区
* 输入   : 无
* 输出   : 无
* 返回   : 无
* 注意   : 缓存区大小为UART0_BUFFER_SIZE字节，客户可修改扩大
********************************************************************/
void Buffer_Uart0SendClear(void)
{
	unsigned short i = 0;

	for(i=0; i<UART0_BUFFER_SIZE; i++)
	{
		send0_buf[i] = 0x00;
	}

	send0_ptr = send0_buf;
	send0_num = 0;
}
