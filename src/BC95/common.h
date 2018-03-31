/*
 * common.h
 *
 *  Created on: 2016-8-29
 *      Author: user
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//#include <msp430.h>


//NBIOT数据发送方式
#define  UDP_LOCAL_PORT "4567"
#define  UDP_SERVER_IP_PORT  	"114.115.144.122,4567"			//UDP:远程服务器IP地址和端口号
//#define  CDP_SERVER_IP_PORT  	"114.115.144.122,5683"			//COAP:远程服务器IP地址和端口号,私有的iot
//#define  CDP_SERVER_IP_PORT  	"180.101.147.115,5683"			//COAP:远程服务器IP地址和端口号，电信iot
#define  CDP_SERVER_IP_PORT  	"120.26.200.64"			//COAP:远程服务器IP地址和端口号，电信iot

//uart串口buffer大小
#define  UART0_BUFFER_SIZE	512 	//定义处理NBIOT模块AT指令接收缓存区和发送缓存区的长度
#define  UART1_BUFFER_SIZE	512  	//定义处理参数设置等接收缓存区和发送缓存区的长度

//电池电压采集信息
#define  BATTERY_WAIT_TIME  		500000			//在采集电压之前需要提前打开分压电路，默认时间单位为uS
#define  BATTERY_THRESHOLD_UP  		2293			// (4.2v/3) / 2.5v * 4095 = 2293，相当于4.2V对应的AD值为2293
#define  BATTERY_THRESHOLD_DOWN  	1692			// (3.1v/3) / 2.5v * 4095 = 1692，相当于3.1V对应的AD值为1692；具体电压值按实际情况调整
#define  BATTERY_STEP_RANGE  	    (BATTERY_THRESHOLD_UP - BATTERY_THRESHOLD_DOWN)	// AD有效值范围

//NBIOT相关操作
#define  API_OPEN_REPEAT_NUMBER  	3		//操作多次，失败之后 停留N长时间之后在做尝试，不能总是在尝试-费电，也不能仅尝试一次
#define  API_CLOSE_REPEAT_NUMBER  	3		//操作多次，失败之后 停留N长时间之后在做尝试，不能总是在尝试-费电，也不能仅尝试一次
#define  API_SEND_REPEAT_NUMBER  	3		//操作多次，失败之后 停留N长时间之后在做尝试，不能总是在尝试-费电，也不能仅尝试一次
#define  API_RECV_REPEAT_NUMBER  	3		//操作多次，失败之后 停留N长时间之后在做尝试，不能总是在尝试-费电，也不能仅尝试一次

//时间参数
#define  TIMER_REPEAT_NBIOT_REGISTER	3600 	//单位秒：1小时=60分钟x60秒
#define  TIMER_REPEAT_NBIOT_RECV		3		//单位秒：3
#define  COUNT_REPEAT_NBIOT_RECV		10		//尝试读取10次，间隔时间为TIMER_REPEAT_RECV
#define  TIMER_KEY_PUSH_DELAY			10		//单位秒：10,按键按下10秒

//AT指令尝试重复操作的次数(固定)
#define  NBIOT_RESET_DELAYTIME  	1000	//在操作AT指令出现错误，重复操作的次数，默认时间 = (0.3S * N)S
#define  AT_DEFAULT_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NRB_REPEAT_NUMBER  		3		//在操作AT指令出现错误，重复操作的次数
#define  AT_AT_REPEAT_NUMBER  		3		//在操作AT指令出现错误，重复操作的次数
#define  AT_CCLK_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NCONFIG_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_CFUN_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_CSQ_REPEAT_NUMBER  		3		//在操作AT指令出现错误，重复操作的次数
#define  AT_CGATT_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_CEREG_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NSOCR_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NSOST_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NSORF_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NMGS_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数
#define  AT_NMGR_REPEAT_NUMBER  	3		//在操作AT指令出现错误，重复操作的次数

#endif /* COMMON_H_ */
