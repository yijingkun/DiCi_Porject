/*
 * brd_bc95.c
 *
 *  Created on: 2017-11-14
 *      Author: user
 */


#include "common.h"
#include "mcu_buffer.h"
#include "types.h"
#include "uart.h"
//#include "mcu_uart.h"
//#include "mcu_timer.h"
//#include "tool_utils.h"

/*******************************************************************
* 函数名 : Brd_Nbiot_PowerOn
* 描述   : 打开核心板电源
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 硬件复位
********************************************************************/
void Brd_Nbiot_PowerOn(void)
{
//使能BC95电源，使能MCU串口模式
	P5OUT |= BIT5;			//打开BC95电源
}

/*******************************************************************
* 函数名 : Brd_Nbiot_PowerOff
* 描述   : 关闭核心板电源
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 硬件复位
********************************************************************/
void Brd_Nbiot_PowerOff(void)
{
//关闭BC95电源，并将RX 和 TX管脚设置为GPIO输出低电平
	P5OUT &= ~BIT5;				//关闭BC95电源
	UCA1CTL1 |= UCSWRST;		//设置串口进入复位状态，否则TX管脚依然会输出3.3V电压，影响BC95供电
	P5SEL &= ~(BIT6 + BIT7);	//设置RX 和 TX管脚为GPIO模式
	P5DIR |= (BIT6 + BIT7);		//GPIO方向为 输出方向
	P5OUT &= ~(BIT6 + BIT7);    //输出 低电平
}

/*******************************************************************
* 函数名 : delay_nms
* 描述   : 使用delay_ms函数可以用来赋值变量
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 
********************************************************************/
void delay_nms(int n)
{
  for(int i=0;i<n;i++)
  {
    delay_ms(1);
  }
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Hdw_Reset
* 描述   : 通过Reset管脚复位NBIOT模块
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 硬件复位
********************************************************************/
unsigned char Brd_Nbiot_Hdw_Reset(void)
{
	P4DIR |= BIT5;
	P4OUT |= BIT5;									//拉低Reset管脚电平，复位nbiot模块
	delay_nms(NBIOT_RESET_DELAYTIME);				//延时
	P4DIR |= BIT5;
	P4OUT &= ~BIT5;									//拉高Reset管脚电平，退出复位

    return 1;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_AT_Reset
* 描述   : 通过NRB命令复位模块
* 输入   : 无
* 输出   :
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_AT_Reset(void)
{
	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
//	Mcu_UartSendAtCommand("AT+NRB");				//通过UART0串口输出log信息
	Mcu_UartSendAtCommand("AT+NRB");				//发送AT指令

    return 1;
}

/*******************************************************************
* 函数名 : Mcu_BC95_AT_OK
* 描述   : 发送AT，返回OK，测试uart0串口和BC95模块之间通信是否正常
* 输入   : 无
* 输出   :
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 发送AT，返回OK
********************************************************************/
unsigned char Brd_Nbiot_Snd_AT(void)
{
	unsigned short try_num = AT_AT_REPEAT_NUMBER;

    do
    {
    	Buffer_Uart0RecvClear();					//清除uart1接收缓存区
//    	Mcu_UartSendAtCommand("AT");				//通过UART0串口输出log信息
    	Mcu_UartSendAtCommand("AT");				//发送AT指令
//    	Mcu_TimerAStart();							//开启定时，等待指令回复
//    	__bis_SR_register(LPM3_bits + GIE);			//MCU进入低功耗睡眠模式
        delay_nms(2000);                                  //延时500毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)			//检测到OK代表NBIOT模块已经正常启动，可以发送其他AT指令
    	{
//    		Mcu_TimerAStop();
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cgmr
* 描述   : 获取NBIOT模块固件版本号
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cgmr(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
//    	Mcu_Uart1SendAtCommand("AT+CGMR");				//通过UART0串口输出log信息
    	Mcu_UartSendAtCommand("AT+CGMR");				//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "SECURITY,") != NULL)		//比如：SECURITY,V100R100C10B657SP2
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cgsn
* 描述   : 获取NBIOT模块的IMEI信息
* 输入   : 无
* 输出   :
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cgsn(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

    do
    {
    	Buffer_Uart0RecvClear();				//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CGSN=1");	//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CGSN:") != NULL)	//搜索"+CGSN:"关键字的位置 +CGSN:863703034512546
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Nconfig
* 描述   : 获取是否模块自动联网
* 输入   : 无
* 输出   : autocnt=0 : 没有自动联网   1 ：上点自动联网
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Nconfig(unsigned char *autocnt)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();				//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+NCONFIG?");	//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+NCONFIG:AUTOCONNECT,FALSE") != NULL)
    	{
    		*autocnt = 0;
    		break;
    	}
    	else if(strstr(recv0_buf, "+NCONFIG:AUTOCONNECT,TRUE") != NULL)
    	{
    		*autocnt = 1;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Nband
* 描述   : 获取模块的频段
* 输入   : 无
* 输出   : nband=0 : 850MHZ   1 ：900MHZ  2 ：800MHZ
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Nband(unsigned char *nband)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

    do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+NBAND?");			//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+NBAND:5") != NULL)
    	{
    		*nband = '5';									//中国电信
    		break;
    	}
    	else if(strstr(recv0_buf, "+NBAND:8") != NULL)
    	{
    		*nband = '8';									//中国移动、中国联通
    		break;
    	}
    	else if(strstr(recv0_buf, "+NBAND:20") != NULL)
    	{
    		*nband = '0';								//欧美制式
    		break;
    	}

    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cfun
* 描述   : 确定是否识别SIM卡，以及射频是否打开
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cfun(void)
{
	unsigned short try_num = AT_CFUN_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CFUN?");				//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CFUN:1") != NULL)		//射频模块已经正常启动，并且成功识别SIM卡
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cimi
* 描述   : 获取SIM卡的IMSI
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cimi(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CIMI");				//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "460") != NULL)			//比如：460111108971472，中国的IMSI以460开头
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Nccid
* 描述   : 获取SIM卡的ICCID号码
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Nccid(void)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+NCCID");				//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+NCCID:") != NULL)		//成功获取iccid号码，比如+NCCID:89860317492039393960
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Csq
* 描述   : 获取本地网络信号
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 在API层提取信号强度值
********************************************************************/
unsigned char Brd_Nbiot_Get_Csq(void)
{
	unsigned short try_num = AT_CSQ_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();					//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CSQ");			//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CSQ:99,99") != NULL)	//没有搜索到信号
    	{

    	}
    	else if(strstr(recv0_buf, "+CSQ:") != NULL)	//搜索到信号
    	{
			break;
    	}
    }while(--try_num);

    return try_num;
}


/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cgatt
* 描述   : 判断是否附着到网络
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cgatt(void)
{
	unsigned short try_num = AT_CGATT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CGATT?");			//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CGATT:1") != NULL)
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cereg
* 描述   : 判断是否注册到网络
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cereg(void)
{
	unsigned short try_num = AT_CEREG_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CEREG?");			//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CEREG:0,1") != NULL)
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cscon
* 描述   : 判断是当前设备的连接状态
* 输入   : 无
* 输出   : cscon=0 : idle   1 ：connect
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cscon(unsigned char *cscon)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CSCON?");			//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CSCON:0,1") != NULL)
    	{
    		*cscon = 1;									//进入connect状态
    		break;
    	}
    	else if(strstr(recv0_buf, "+CSCON:0,0") != NULL)
    	{
    		*cscon = 0;									//进入idle状态或者还没有登网成功
    		break;
    	}
    }while(--try_num);

    return try_num;
}


/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Cclk
* 描述   : 获取当前网络时间
* 输入   : 无
* 输出   :
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Cclk(void)
{
	unsigned short try_num = AT_CCLK_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+CCLK?");				//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "+CCLK:") != NULL)			//时间信息"yy/MM/dd,hh:mm:ss"比如 +CCLK:17/11/15,07:10:04+32
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Get_Ncdp
* 描述   : 获取当前NCDP信息，IoT平台信息
* 输入   : 无
* 输出   : <ip_addr>,<port>
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Get_Ncdp(char *ncdp)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();						//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+NCDP?");				//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	ncdp = strstr(recv0_buf, "+NCDP:");				//比如+NCDP:114.115.144.122,5683
    	if(ncdp != NULL)
    	{
    		ncdp = ncdp + 6;							//跳过“+NCDP:”关键字
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Set_Nconfig
* 描述   : 设置模块上电自动联网
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Nconfig(void)
{
	unsigned short try_num = AT_NCONFIG_REPEAT_NUMBER;

	do
    {
    	Buffer_Uart0RecvClear();								//清除uart1接收缓存区
    	Mcu_UartSendAtCommand("AT+NCONFIG=AUTOCONNECT,TRUE");	//发送AT指令
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Set_Cgatt
* 描述   : 手动附网 去网操作
* 输入   : cgatt=0： 去网  1 ：附网
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Cgatt(unsigned char cgatt)
{
	unsigned short try_num = AT_CGATT_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	if(cgatt == 0)
	{
		Mcu_UartSendAtCommand("AT+CGATT=0");			//发送AT指令
	}
	else
	{
		Mcu_UartSendAtCommand("AT+CGATT=1");			//发送AT指令
	}

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Set_Cfun
* 描述   : 手动打开 或者 关闭 射频电路
* 输入   : cfun=0： 关闭射频  1 ：打开射频
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Cfun(unsigned char cfun)
{
	unsigned short try_num = AT_CFUN_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	if(cfun == 0)
	{
		Mcu_UartSendAtCommand("AT+CFUN=0");			//发送AT指令
	}
	else
	{
		Mcu_UartSendAtCommand("AT+CFUN=1");			//发送AT指令
	}

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Set_Ncdp
* 描述   : 设置
* 输入   : ipaddr平台的IP地址  ipport平台的端口号
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Set_Ncdp(char *ip_port)
{
	unsigned short try_num = AT_DEFAULT_REPEAT_NUMBER;
	char cmd[64] = {0};

	strcpy(cmd, "AT+NCDP=");		    				//创建命令，比如AT+NCDP=119.23.233.222,5683
	strcat(cmd, ip_port);

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	Mcu_UartSendAtCommand(cmd);						//发送AT指令

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//操作失败返回ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Crt_Nsocr
* 描述   : 创建UDP信道
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Crt_Nsocr(void)
{
	unsigned short try_num = AT_NSOCR_REPEAT_NUMBER;
	char cmd[64] = {0};

	strcpy(cmd, "AT+NSOCR=DGRAM,17,");		    		//创建命令
	strcat(cmd, UDP_LOCAL_PORT);
	strcat(cmd, ",1");

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	Mcu_UartSendAtCommand(cmd);						//发送AT指令

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//操作失败返回ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Cls_Nsocl
* 描述   : 关闭UDP信道
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   :
********************************************************************/
unsigned char Brd_Nbiot_Cls_Nsocl(void)
{
	unsigned short try_num = AT_NSOCR_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	Mcu_UartSendAtCommand("AT+NSOCL=0");				//发送AT指令

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//返回ERROR,说明udp信道已经关闭了
    	{
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Snd_Nsost
* 描述   : 通过UDP信道发送数据
* 输入   : data数据指针，len 用户数据长度
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 发送前 需要构建发送指令
********************************************************************/
unsigned char Brd_Nbiot_Snd_Nsost(char *ip_port, char * data, unsigned short len)
{
	char cmd[64] = {0};
	char str[6]	 = {0};
	unsigned short try_num = AT_NSOST_REPEAT_NUMBER;

	itoi(str, len);										//数字转化成字符串
	strcpy(cmd, "AT+NSOST=0,");		    				//创建命令 AT+NSOST=0,114.115.144.122,4567,3,303132
	strcat(cmd, ip_port);					//加入服务端IP地址和端口号
	strcat(cmd, ",");
	strcat(cmd, str);									//加入数据长度
	strcat(cmd, ",");

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	UartSendStrings(cmd);							//发送AT指令
	Mcu_UartSendDataWithLength(data, len*2);		//发送数据
	Mcu_UartSendLR();									//发送回车

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//操作失败返回ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Rcv_Nsorf
* 描述   : 通过UDP信道读取数据
* 输入   : 无
* 输出   : newdata=1 读取到新数据， newdata=0已经没有数据了
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 数据仍然存放在recv0_buf，没有对数据做解析
********************************************************************/
unsigned char Brd_Nbiot_Rcv_Nsorf(unsigned char *newdata)
{
	unsigned short try_num = AT_NSORF_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();									//清除uart1接收缓存区
	Mcu_UartSendAtCommand("AT+NSORF=0,512");					//发送AT+NSORF指令,读取数据

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if( (recv0_buf[2] == '0') && (recv0_buf[3] == ',') )		//如果返回 回车+“0，” 代表接收到新数据，解释：‘0’=信道编号固定为0，‘，’固定符号
    	{
    		*newdata = 1;
    		break;
    	}
    	else if( (recv0_buf[2] == 'O') && (recv0_buf[3] == 'K') )	//如果返回 回车+OK代表没有数据了
    	{
    		*newdata = 0;
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)					//操作失败返回ERROR
    	{
    		*newdata = 0;
    		try_num  = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Snd_Nmgs
* 描述   : 通过coap信道发送数据
* 输入   : data数据指针，len 用户数据长度
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 发送前 需要构建发送指令
********************************************************************/
unsigned char Brd_Nbiot_Snd_Nmgs(char * data, unsigned short len)
{
	char cmd[64] = {0};
	char str[6]	 = {0};
	unsigned short try_num = AT_NMGS_REPEAT_NUMBER;

	itoi(str, len);										//数字转化成字符串
	strcpy(cmd, "AT+NMGS=");		    				//创建命令，比如AT+NMGS=11,48454C4C4F2C574F524C44
	strcat(cmd, str);									//加入数据长度
	strcat(cmd, ",");

	Buffer_Uart0RecvClear();							//清除uart1接收缓存区
	UartSendStrings(cmd);							//发送AT指令
	Mcu_UartSendDataWithLength(data, len*2);			//发送数据
	Mcu_UartSendLR();									//发送回车，发送AT+NMGS指令,通过coap信道发送数据

//	Buffer_Uart0RecvClear();										//清除uart1接收缓存区
//	Mcu_Uart1SendAtCommand("AT+NMGS=11,48454C4C4F2C574F524C44");	//通过UART0串口输出回显命令
//	Mcu_Uart0SendAtCommand("AT+NMGS=11,48454C4C4F2C574F524C44");	//发送AT+NSORF指令,读取数据

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if(strstr(recv0_buf, "OK") != NULL)				//操作成功返回OK
    	{
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)		//操作失败返回ERROR
    	{
    		try_num = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Brd_Nbiot_Rcv_Nmgr
* 描述   : 通过COAP信道读取数据
* 输入   : 无
* 输出   : newdata=1 读取到新数据， newdata=0已经没有数据了
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 数据仍然存放在recv0_buf，没有对数据做解析
********************************************************************/
unsigned char Brd_Nbiot_Rcv_Nmgr(unsigned char *newdata)
{
	unsigned short try_num = AT_NMGR_REPEAT_NUMBER;

	Buffer_Uart0RecvClear();										//清除uart1接收缓存区
	Mcu_UartSendAtCommand("AT+NMGR");								//发送AT+NSORF指令,读取数据

	do
    {
        delay_nms(2000);                                  //延时50毫秒，期间接到返回的'OK',则返回剩余的try_num
    	if( ('0' < recv0_buf[2]) && (recv0_buf[3] < '9') )			//如果返回 第一个有效数据位 0-9的长度信息，那么代表接收到数据
    	{
    		*newdata = 1;
    		break;
    	}
    	else if( (recv0_buf[2] == 'O') && (recv0_buf[3] == 'K') )	//如果返回 回车+OK代表没有数据了
    	{
    		*newdata = 0;
    		break;
    	}
    	else if(strstr(recv0_buf, "ERROR") != NULL)					//操作失败返回ERROR
    	{
    		*newdata = 0;
    		try_num  = 0;
    		break;
    	}
    }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Nbiot_Api_Open_Network
* 描述   : 打开射频，确保NBIOT模块注册到网络
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 确保模块注册到网络上
********************************************************************/
unsigned char Nbiot_Api_Open_Network(void)
{
  unsigned short try_num = API_OPEN_REPEAT_NUMBER; 	//默认尝试3次
  unsigned char  status    = 0;
  unsigned char  autocnt   = 0;
  unsigned char  nband     = 0;
  unsigned char  i         = 0;

  do
  {
    //硬件复位NBIOT模块-通过AT+NRB复位
    status = Brd_Nbiot_AT_Reset();
    if(status == 0)
      goto OPEN_ERROR;
    //使用AT-OK测试NBIOT模块的串口是否通信正常
    status = Brd_Nbiot_Snd_AT();
    if(status == 0)
      goto OPEN_ERROR;
    //查询是否自动注册网络，if-yes=下一步，if-no=设置为true + 重启模块
    status = Brd_Nbiot_Get_Nconfig(&autocnt);
    if(status == 0)
      goto OPEN_ERROR;
    else
    {
      if(autocnt == 0)						//if-no=设置为true
      {
        status = Brd_Nbiot_Set_Nconfig();	//设置为上电自动登网
        if(status == 0)
          goto OPEN_ERROR;

          continue;							//重启模块
      }
    }

    //查询当前的NCDP信息，if=设置参数=下一步，if!=设置的参数= 设置新的NCDP + 重启模块
    status = Brd_Nbiot_Set_Ncdp(CDP_SERVER_IP_PORT);
    if(status == 0)
      goto OPEN_ERROR;
    //查询-等待NBIOT模块完成读取SIM和打开射频操作-通过AT+CFUN?指令获取，if-fail=进入下次do-while，if-OK=下一步
    status = Brd_Nbiot_Get_Cfun();
    if(status == 0)								//SIM卡没有识别，或者没有安装SIM卡
      goto OPEN_ERROR;
    //获取NBIOT模块运营商类型
    status = Brd_Nbiot_Get_Nband(&nband);
    if(status == 0)
      goto OPEN_ERROR;
    else
      msg->module_info.nband = nband;
    //获取NBIOT模块的固件版本号
    status = Brd_Nbiot_Get_Cgmr();
    if(status == 0)
      goto OPEN_ERROR;
    else	//从recv0_buf中提取固件版本号
    {
      for(i=0; i<18; i++)
        msg->module_info.cgmr[i] = recv0_buf[i+11];	//跳过“回车+SECURITY,”关键字，得到V100R100C10B657SP2
    }
    //获取模块的IMEI串码-通过AT+CGSN=1指令获得
    status = Brd_Nbiot_Get_Cgsn();
    if(status == 0)
      goto OPEN_ERROR;

    //获取SIM卡的ICCID卡号-通过AT+NCCID指令获得
    status = Brd_Nbiot_Get_Nccid();
    if(status == 0)
      goto OPEN_ERROR;
    else	//从recv0_buf中提取SIM卡的ICCID号
    {
      for(i=0; i<20; i++)
        msg->module_info.nccid[i] = recv0_buf[i+9];	//跳过“回车+NCCID:”关键字，得到89860317492039393960
    }

    //获取当前NBIOT网络的信号强度-通过AT+CSQ指令获得
    status = Brd_Nbiot_Get_Csq();
    if(status == 0)
      goto OPEN_ERROR;
    else	//从recv0_buf中提取信号强度
    {
      if(recv0_buf[8] != ',')		//信号强度有可能是个位数,+CSQ:14,99
      {
        msg->sensor_info.nbiot.csq[0] = recv0_buf[7];
        msg->sensor_info.nbiot.csq[1] = recv0_buf[8];
      }
      else
      {
        msg->sensor_info.nbiot.csq[0] = '0';
        msg->sensor_info.nbiot.csq[1] = recv0_buf[7];
      }
    }
    //查询-等待附着到网络-通过AT+CGATT?指令获取，if-fail=进入下次do-while，if-OK=下一步
    status = Brd_Nbiot_Get_Cgatt();
    if(status == 0)
      goto OPEN_ERROR;

    //查询-等待注册到网络-通过AT+CEGER?指令获取，if-fail=进入下次do-while，if-OK=下一步
    status = Brd_Nbiot_Get_Cereg();
    if(status == 0)
      goto OPEN_ERROR;

    break;		//成功完成所有配置，并打开UDP信道

OPEN_ERROR:
    try_num--;
    
  }while(try_num);

  return try_num;  
}

/*******************************************************************
* 函数名 : Nbiot_Api_Close_Network
* 描述   : 注销NBIOT网络，并关闭射频功能
* 输入   : 无
* 输出   : 无
* 返回   : 0 : 失败   非零 ：成功
* 注意   : 确保模块进入最低功耗
********************************************************************/
unsigned char Nbiot_Api_Close_Network(void)
{
  unsigned char  status    = 0;
  unsigned short try_num = API_CLOSE_REPEAT_NUMBER; 	//默认尝试5次

  do
  {
    //关闭射频功能-通过AT+CFUN=0操作，节省电量
    status = Brd_Nbiot_Set_Cfun(0);
    if(status != 0)
      break;

  }while(--try_num);

    return try_num;
}

/*******************************************************************
* 函数名 : Nbiot_Api_Send_Message
* 描述   : 通过NBIOT模块发送数据
* 输入   : 无
* 输出   : 无
* 返回   : 无
* 注意   : 无
********************************************************************/
unsigned char Nbiot_Api_Send_Message()
{
  unsigned char  status    = 0;
  unsigned short try_num = API_SEND_REPEAT_NUMBER; 	//默认尝试5次

  char * chptr = (char *)(&msg_buffer);

  Hex2Str(chptr, send0_buf, sizeof(MessageStruct));	//hex 转化成 string

  do
  {
    status = Brd_Nbiot_Snd_Nmgs(send0_buf, sizeof(MessageStruct));		//具体的数据长度，需要coap发送数据=调用AT+NMGS指令发送数据
    if(status != 0)
      break;
  }while(--try_num);

  return try_num;
}

/*******************************************************************
* 函数名 : Nbiot_Api_Recv_Message
* 描述   : 通过NBIOT模块接收数据
* 输入   : 无
* 输出   : new=1，接收到新数据，new=0没有接收到数据
* 返回   : 无
* 注意   : 无
********************************************************************/
unsigned char Nbiot_Api_Recv_Message(unsigned char *new)
{
	unsigned char status  = 0;

	status = Brd_Nbiot_Rcv_Nmgr(new);	//if-需要coap接收数据=调用AT+NMGR指令接收数据

    return status;
}

/*******************************************************************
* 函数名 : Nbiot_Api_Get_Csq
* 描述   : 通过NBIOT模块获取当前信号强度
* 输入   : 无
* 输出   : 无
* 返回   : 无
* 注意   : 无
********************************************************************/
unsigned char Nbiot_Api_Get_Csq(void)
{
	unsigned char status  = 0;

	status = Brd_Nbiot_Get_Csq();	//获取当前NBIOT网络的信号强度-通过AT+CSQ指令获得
	if(status != 0)					//从recv0_buf中提取当前时间
	{
		if(recv0_buf[8] != ',')		//信号强度有可能是个位数,+CSQ:14,99
		{
			msg->sensor_info.nbiot.csq[0] = recv0_buf[7];
			msg->sensor_info.nbiot.csq[1] = recv0_buf[8];
		}
		else
		{
			msg->sensor_info.nbiot.csq[0] = '0';
			msg->sensor_info.nbiot.csq[1] = recv0_buf[7];
		}
	}

    return status;
}

/*******************************************************************************
* 函数名 : strnicmp
* 描述   : 字符比较
* 输入   :
* 输出   :
* 返回   :
* 注意   :
*******************************************************************************/
int strnicmp(const char *dst, const char *src, int count)
{
   char ch1, ch2;

   if(count != strlen(src))
	   return -1;

   do
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( --count && ch1 && (ch1 == ch2) );

   return (ch1 - ch2);
}

/*******************************************************************************
* 函数名 : itoi
* 描述   : 数字转化为字符串
* 输入   :
* 输出   :
* 返回   :
* 注意   :
*******************************************************************************/
void itoi(char *str, unsigned long num)
{
	char index[]="0123456789";
	char i = 0, j = 0;
    char temp;

    do
    {
        str[i++] = index[num%10];
        num /= 10;
    }while(num);

    str[i]='\0';

    for(j=0; j<=(i-1)/2; j++)
    {
        temp=str[j];
        str[j]=str[i-j-1];
        str[i-j-1]=temp;
    }
}

/*******************************************************************************
* 函数名 : itoc
* 描述   : 单个数字转化为字符
* 输入   : ichar数字
* 输出   :
* 返回   : 字符
* 注意   :
*******************************************************************************/
char itoc(unsigned char ichar)
{
	char index[]="0123456789";

    return index[ichar%10];
}

/*******************************************************************************
* 函数名 : Hex2Str
* 描述   : 16进制数转化成字符串，用于AT+NSOST命令
* 输入   : 输入: pSrc - 源数据指针
* 输出   : 输出: pDst - 目标字符串指针
* 返回   :
* 注意   : 如：{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01"
*******************************************************************************/
void Hex2Str(char* pSrc, char* pDst, unsigned int nSrcLength)
{
	int i = 0;
	const char tab[]="0123456789ABCDEF";	// 0x0-0xf的字符查找表

	for (i = 0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];		// 输出高4位
		*pDst++ = tab[*pSrc & 0x0f];	// 输出低4位
		pSrc++;
	}

	// 输出字符串加个结束符
	*pDst = '\0';
}

/*******************************************************************************
* 函数名 : AsciiToHex
* 描述   : ASCALL码转换成字符
* 输入   : unsigned char cNum  ASC-II字符码
* 输出   : unsigned char HEX码
* 返回   :
* 注意   : 如：{'A'} --> 0xA
*******************************************************************************/
unsigned char AsciiToHex(unsigned char cNum)
{
	if(cNum>='0'&&cNum<='9')
	{
		cNum -= '0';
	}
	else if(cNum>='A'&&cNum<='F')
	{
		cNum -= 'A';
		cNum += 10;
	}
	else if(cNum>='a'&&cNum<='f')
	{
		cNum -= 'a';
		cNum += 10;
	}
	return cNum;
}

/*******************************************************************************
* 函数名 : StrToHex
* 描述   : 字符串转换hex
* 输入   : char *ptr字符存储区，unsigned short len数据长度
* 输出   :
* 返回   :
* 注意   : 如："C8329BFD0E01" -->  {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
*******************************************************************************/
void StrToHex(char *ptr, unsigned short len)
{
	unsigned char n1  = 0;
	unsigned char n2  = 0;
	unsigned char num = 0;
	unsigned short i = 0;
	unsigned short index = 0;

	for(i=0; i<len; i++)
	{
		index = i << 1;				//index=i*2
		n1 = AsciiToHex(ptr[index]);
		n2 = AsciiToHex(ptr[index+1]);
		num = (n1<<4) + n2;
		ptr[i] = num;
	}
}
