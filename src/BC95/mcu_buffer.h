/*
 * buffer.h
 *
 *  Created on: 2016-8-15
 *      Author: user
 */

#ifndef MCU_BUFFER_H_
#define MCU_BUFFER_H_

#include "common.h"

//uart0 接收缓存区
extern char   recv0_buf[UART0_BUFFER_SIZE];
extern char * recv0_ptr;
extern short  recv0_num;

//uart0 发送缓存区
extern char   send0_buf[UART0_BUFFER_SIZE];
extern char * send0_ptr;
extern short  send0_num;


/*******************************************************************
* 函数名 : Buffer_Uart0RecvClear
* 描述   : 清零UART0接收缓存区
* 输入   : 无
* 输出   : 无
* 返回   : 无
* 注意   : 缓存区大小为UART0_BUFFER_SIZE字节，客户可修改扩大
********************************************************************/
void Buffer_Uart0RecvClear(void);

/*******************************************************************
* 函数名 : Buffer_Uart0SendClear
* 描述   : 清零UART0发送缓存区
* 输入   : 无
* 输出   : 无
* 返回   : 无
* 注意   : 缓存区大小为UART0_BUFFER_SIZE字节，客户可修改扩大
********************************************************************/
void Buffer_Uart0SendClear(void);

#endif /* BUFFER_H_ */
