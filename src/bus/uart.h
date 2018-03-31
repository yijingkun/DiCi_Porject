#ifndef UART_H
#define UART_H

#define RECNUM 4

void UartInit();
void UartSendByte(u8 data);
void UartSendStrings(char *str);
void UartSendWByte(u16 data);
void UartSendNumber(u16 data);
void SplitNum(u16 temp,char *pbuf);
void UartSendNumberH(u16 data);
void SplitNumH(u16 temp,char *pbuf);
void UartSendNumberH8(u8 data);
void SplitNumH8(u8 temp,char *pbuf);
void Mcu_UartSendLR(void);
void Mcu_UartSendAtCommand(char *cmd);
void Mcu_UartSendDataWithLength(char *data, unsigned short len);


/*******************************************************************************
* 函数名 : strnicmp
* 描述   : 字符比较
* 输入   :
* 输出   :
* 返回   :
* 注意   :
*******************************************************************************/
int strnicmp(const char *dst, const char *src, int count);

/*******************************************************************************
* 函数名 : itoi
* 描述   : 数字转化为字符串
* 输入   :
* 输出   :
* 返回   :
* 注意   :
*******************************************************************************/
void itoi(char *str, unsigned long num);

/*******************************************************************************
* 函数名 : itoc
* 描述   : 单个数字转化为字符
* 输入   : ichar数字
* 输出   :
* 返回   : 字符
* 注意   :
*******************************************************************************/
char itoc(unsigned char ichar);

/*******************************************************************************
* 函数名 : Hex2Str
* 描述   : 16进制数转化成字符串，用于AT+NSOST命令
* 输入   : 输入: pSrc - 源数据指针
* 输出   : 输出: pDst - 目标字符串指针
* 返回   :
* 注意   : 如：{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01"
*******************************************************************************/
void Hex2Str(char* pSrc, char* pDst, unsigned int nSrcLength);

/*******************************************************************************
* 函数名 : AsciiToHex
* 描述   : ASCALL码转换成字符
* 输入   : unsigned char cNum  ASC-II字符码
* 输出   : unsigned char HEX码
* 返回   :
* 注意   : 如：{'A'} --> 0xA
*******************************************************************************/
unsigned char AsciiToHex(unsigned char cNum);

/*******************************************************************************
* 函数名 : StrToHex
* 描述   : 字符串转换hex
* 输入   : char *ptr字符存储区，unsigned short len数据长度
* 输出   :
* 返回   :
* 注意   : 如："C8329BFD0E01" -->  {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
*******************************************************************************/
void StrToHex(char *ptr, unsigned short len);


/***********************************************************************
 *
 * 用于存储设备信息，设备本身的参数不可修改
 *
 ***********************************************************************/
typedef struct _DeviceStruct
{
  char mftID[2];		//厂商ID号，mftID[0]=‘K’=0x4B mftID[1]=‘X’=0x58
  char devID[2];		//厂商ID号，devID[0]=‘0’=0x30 devID[1]=‘1’=0x31
  char hwdVer[2];		//电路板硬件版本号，hwdVer[0]=‘0’=0x31 hwdVer[1]=‘1’=0x34
  char sftVer[2];		//程序软件版本号，sftVer[0]=‘0’=0x31 sftVer[1]=‘1’=0x34
}DeviceStruct;

/***********************************************************************
 *
 * 用于存储NBIOT通信模块参数信息，比如网络制式、信号强度等
 *
 ***********************************************************************/
typedef struct _ModuleStruct
{
  char cgmr[18];		//NBIOT模块固件版本号：比如V100R100C10B657SP2
  char nband;			//NBIOT运营商：nband=‘5’=中国电信， nband=‘8’=中国移动、中国联通， nband=‘0’=其他
  char nccid[20];		//SIM卡卡号：比如89860316482018310474
}ModuleStruct;

/***********************************************************************
 *
 * 用于存储传感器参数信息，比如温度、湿度等 //后续增加，湿度、经纬度位置信息、等其他传感器
 *
 ***********************************************************************/
typedef struct _SensorStruct
{
	struct
	{
		char csq[2];		//NBIOT网络信号强度，比如csq=‘14’,分解为csq[0]='1',csq[1]='4'
	}nbiot;

	struct
	{
		char charge;			//USB连接状态，charge=‘0’没有连接USB线，charge=‘1’已经连接USB线
		char battery_rate[3];	//电池电量，battery[0]=‘百位’ ，battery[1]=‘十位’，，battery[3]=‘个位’
	}battery;

    struct
    {
		char mark;				//温度符号，'+' 或者 '-'
    	char data[4];			//存储温度：[0]-[3]存储温度，比如"23.5"、"10.5",精度为0.1度
    }temp;

    struct
    {
    	char data[4];			//存储温度：[0]-[3]湿度百分比，精度为1%度,比如40.5%
    }humidity;



}SensorStruct;

/***********************************************************************
 *
 * 用于存储设备参数信息，设备和上位机控制软件直接的交换协议
 *
 ***********************************************************************/
typedef struct _ParameterStruct
{
    struct
    {
    	char temperature_up[5];		//温度上限阈值：比如"+50.0"
    	char temperature_down[5];	//温度下限阈值：比如"-20.0"
    	char cycle_up[5];			//超出温度上限阈值时，温度上传周期：比如"00010"，10分钟上传一次
    	char cycle_middle[5];		//在温度控制范围之内，温度上传周期：比如"00020"，20分钟上传一次
    	char cycle_down[5];			//超出温度下限阈值时，温度上传周期：比如"00010"，10分钟上传一次
    }temp;
}ParameterStruct;



/***********************************************************************
 *
 * 用于存储NBIOT收发信息，设备和IoT平台的交换协议
 *
 ***********************************************************************/
typedef struct _MessageStruct
{
	char	index[4];		//记录发送消息的数量，计满清零“0000”-“9999”

	DeviceStruct	device_info;

	ModuleStruct	module_info;

	ParameterStruct	param_info;

	SensorStruct	sensor_info;

}MessageStruct;


extern MessageStruct 	msg_buffer;
extern MessageStruct 	*msg;


#endif