#ifndef CFG_H
#define CFG_H
#include "snp.h"
#include "types.h"


#define BASE_BUFF_NUM     5
//***************************************************************************
// u16 ConfigFlags
#define  RECIVE_SEN_CFG            0x0001
#define  BUS_SEND_ON               0x0002
#define  SET_PUMP                  0x0004
#define  FLASH_WRITE_ERROR         0x0008
#define  SAVE_PUMP_COMD            0x0010
#define  SEN_UP_LINE               0x0020
#define  FLASH_READ_ERR            0x0040
#define  TIMESLOT_SAVED            0x0080
#define  SYS_REST_COMMEND          0x0100
#define  RECIVE_TEST_SYNC          0x0200
#define  DATE_SEND                 0x0400
#define  FLASH_CHECK_OK            0x0800
#define  CFG_BOX_SYNC              0x1000
#define  INIT_AD_START             0x2000
#define  SPI_ERROR                 0x4000
#define  SEND_BAS_BUFF             0x8000


//***************************************************************8
//u16 SetFlags
#define SET_TIMESLOT_FLAG          0x0001
#define SET_ID_FLAG                0x0002
#define UPLINE_SEND                0x0004
#define AD_WEAKUP                  0x0008
#define STATE_TIME_SAVED           0x0010
#define AD_GET_ON                  0x0020
#define DOWN_CODE_CFG              0x0040
#define POWER_GET_END              0x0080
#define SER_REST_COMD              0x0100
#define TEST_DEMO_ON               0x0200
#define DOWNLINE_NORM              0x0400
#define EVENT_GENERT               0x0800
#define EVENT_FLASH_SAVED          0x1000
#define NEW_PUMP_SAVED             0x2000
#define NEW_PUMP_GET               0x4000
#define PUMP_CFG_SEND              0x8000
//*****************************************************************************************************************************************

//**************状态报发送时间
#define REPORT_SEND_TIME_0         1440   //24小时   
#define REPORT_SEND_TIME_1         720  //12小时 
#define REPORT_SEND_TIME_2         480 // 8小时  
#define REPORT_SEND_TIME_3         240  //4小时
#define REPORT_SEND_TIME_4         30  //30分钟
#define REPORT_SEND_TIME_5         15  //15分钟     
#define REPORT_SEND_TIME_6         10  //10分钟 
#define REPORT_SEND_TIME_7         5  //5分钟

//***********************车辆信息发送
#define OFF_BASE_OPEN_0            18     //5.5--Off3分钟基值更新 5.6--复位后发OFF
#define OFF_BASE_OPEN_1            12

//****************************
#define EVENT_OFF_0            OFF      //  
#define EVENT_OFF_1            ON    //旧版--ON基值漂移，     5.6--值<阈值+3  基值更新  5.9--发送事件状态包

//*****************************
#define MIN_TRIGG_0               OFF 
#define MIN_TRIGG_1               ON   

//*******************************
#define ON_TIME_0                 40
#define ON_TIME_1                 80
#define ON_TIME_2                 120
#define ON_TIME_3                 160

//***********************触发探测阈值TriggValueTab
#define TRIGG_VALUE_0              4
#define TRIGG_VALUE_1              5   
#define TRIGG_VALUE_2              6         //AP须初始化值
#define TRIGG_VALUE_3              7
#define TRIGG_VALUE_4              8
#define TRIGG_VALUE_5              9
#define TRIGG_VALUE_6              10
#define TRIGG_VALUE_7              11

//************************XZ轴阈值
#define DETECT_VALUE_0             3     //
#define DETECT_VALUE_1             4
#define DETECT_VALUE_2             5
#define DETECT_VALUE_3             6

//**********************************信号强度阈值
#define SINGLE_VALUE_0            40// 5
#define SINGLE_VALUE_1            48// 6
#define SINGLE_VALUE_2            56//  7
#define SINGLE_VALUE_3            64// 8
#define SINGLE_VALUE_4            72// 9
#define SINGLE_VALUE_5            80// 10
#define SINGLE_VALUE_6            88// 11
#define SINGLE_VALUE_7            96// 12
//****************************************************************************************************************************************************


//***************************************************************************
typedef struct  _AP_SET_PARAMTER_1
{						
  u8   ReportTime	: 3,		// 状态报发送时间间隔
       OffBase  	: 1,		// 报告间隔固定, 参考'Page 173: Enabling Synchronized Reporting'.(检测器s事件数据是否发送)
       EventOff  	: 1,		// 备用
       MinTrigg         : 1,
       OnTime           : 2;
}AP_SET_PARAMTER_1;

typedef union _SET_SEN_PARAMTER_1
{
  u8                  Paramter;
  AP_SET_PARAMTER_1   PamSet;
}SET_SEN_PARAMTER_1;

typedef struct  _AP_SET_PARAMTER_2
{
  u8 TriggValue       :3,    //触发阈值
     UnDetectValue    :2,    // 阈值
     SignalValue      :3;    //备用    
}AP_SET_PARAMTER_2;

typedef union _SET_SEN_PARAMTER_2
{
  u8                  Paramter;
  AP_SET_PARAMTER_2   PamSet;
}SET_SEN_PARAMTER_2;

typedef struct _RF_PARAMTER
{
  u16 ApID;
  u16 pApID;
  u16 SenID;
}RF_PARAMTER;

typedef struct _CODE_SAVE_BUFFER
{
  u8 Buff[512];
  //u8 *BuffPtr;
 // u8 *BasePtr;
  u16 BuffPtr;
  u16 LastReciveNum;
  u16 Page512Num;
  u16 Rum32Num;
  u16 AllNum;
}CODE_SAVE_BUFFER;


void SyncProcess(SNP_SYNC_PACKET_t *SyncPtr);
void CfgParmatInit(void);
void SenCfgProcess(SNP_CFG_PACKET_t *SenCfgPtr);
void SystemParamterDefault(void);
void TotalCfgSet(u8 *pbuff);
void SenUfCfg(SNP_UF_DOWN_CODE_PACKET_t *SaveCodePtr);
void FlshParamtCfg(void);
void FlashParamterInit(void);
#endif