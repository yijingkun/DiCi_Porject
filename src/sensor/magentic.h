#ifndef MAGENTIC_H
#define MAGENTIC_H

#include "snp.h"

#define BUFF_NUM           5
#define ON_NUM             2

#define BASE_LING_DELAY    24  //384  //3s
#define PRIMARY_EVENT_TIME   24  //384  //3秒
#define STABLE_BASELINE_UPDATE_NUM   40   //基准基线值更新次数  40次为不间断2分钟次数
#define SAVE_BUFF_NUM     6
#define ON_SET_FILTER     1
#define ON_GET_VALUE_TIME   48
//#define HOLDER_OVER_TIME  40  //640
//#define ON_EVENT_ON_TIME   88//64  //1024 
//#define EVENT_OFF_TIME    64//40 //640
//#define HALF_ON_TIME      480  //7680
//#define HALF_OFF_TIME     80 //1280   

#define TEMP_BASE_TIME    30
#define MIN_BASE          50
#define MAX_BASE          1023
#define OFF_BUF_NUM       3

    

#define BASELINE_BUFF_NUM   8
#define VIB_NUM             3
#define BASE_NUM            4

//与最小阈值相关参数***************************************************************************
#define MIN_EVENT_VALUE     3
#define HALF_EVENT_VALUE    4
#define OVER_BASE_ERR       8 
#define LOW_BASE_RIGHT      5
#define EFFECT_VALUE        8
//********************************************************************************************


//////state///////////// 
#define  INIT_BASE_LINE    0
#define  ON_BASE_LINE      1
#define  ON_HALF_EVENT     2
#define  COUNTING_BLOW     3
#define  EVENT_DETECT      4




#define  SetVccON()  (P8OUT&=~BIT3)
#define  SetGndON()  (P8OUT|=BIT3) 
#define  RstGndON()  (P8OUT|=BIT2) 
#define  RstVccON()  (P8OUT&=~BIT2)

#define  MSenSet()   st(RstGndON(); SetVccON(); delay_us(35);  )//30
#define  MSenRst()   st( SetGndON(); RstVccON(); delay_us(35); )//30

//**************************************************************************
//u16 AdMagenticFlags
#define AD_EVENT_ON_PRIMARY        0x0001
#define EVENT_STABLE               0x0002
#define EVENT_GENERAT              0x0004
#define DOWNLINE_INIT              0x0008
#define ON_HALF_BASELINE_Z         0x0010
#define EVENT_ON_SAVED             0x0020
#define ON_HALF_BASELINE_X         0x0040
#define ON_DEC_SAVED               0x0080
#define ON_EVENT_SAVE              0x0100
#define AD_SEND_NEED               0x0200
#define Z_BASELINE_SUIT            0x0400
#define X_BASELINE_SUIT            0x0800
#define ON_EVENT_ON_SAVED          0x1000
#define AD_COUNT_ON                0x2000
#define BASELINE_GENERT            0x4000   
#define BUS_OFF_GENERT             0x8000
//***************************************************************************
///*******************************************************************************8
//u16 BaseLineFlag
#define SMOOTH_UP_Z                0x0001
#define SMOOTH_DOWN_Z              0x0002
#define SMOOTH_UP_X                0x0004
#define SMOOTH_DOWN_X              0x0008
#define ON_BASELIN_GET             0x0010
#define ON_EVENT_ON                0x0020
#define BS_SMOOTH_UP_Z             0x0040
#define BS_SMOOTH_DOWN_Z           0x0080 
#define ON_EVENT_BASELINE_RST      0x0100
#define BASELINE_UPDATA            0x0200
#define READ_BASELINE              0x0400
#define READ_BASELINE_ON           0x0800
#define BS_SMOOTH_UP_X             0x1000
#define BS_SMOOTH_DOWN_X           0x2000
#define EVENT2_CHANGED             0x4000
#define TEMP_BASE_CHANGED          0x8000

///*******************************************************************************8
//HalfBaseLineFlag
#define BASE_INIT_OFF                0x0001   
#define SEND_OFF_COMMD               0x0002
#define ON_EVENT_ON_Z                0x0004
#define ON_EVENT_ON_X                0x0008
#define COMMD_OFF_BASE               0x0010
#define OFF_BASE_CNT_ON              0x0020
#define POSITIVE_CNT_Z               0x0040
#define POSITIVE_CNT_X               0x0080
#define ON_EVENT_BASELINE_GET_Z      0x0100
#define ON_EVENT_BASELINE_GET_ON_Z   0x0200
#define ON_EVENT_BASELINE_GET_X      0x0400
#define ON_EVENT_BASELINE_GET_ON_X   0x0800
#define GET_NEREST_BASELINE_Z        0x1000
#define GET_NEREST_BASELINE_X        0x2000
#define HALF_EVENT_Z                 0x4000
#define HALF_EVENT_X                 0x8000

//********************************************************************
//ExtraFlags*********************************************************
#define BIG_DECECT_Z                 0x0001
#define BIG_DECECT_X                 0x0002
#define ON_BASELIN_GENERT_Z          0x0004
#define ON_BASELIN_GENERT_X          0x0008
#define BASELINE_CALIBRAT_Z          0x0010
#define BASELINE_CALIBRAT_X          0x0020
#define BASELINE_UPDATE_NUM_Z        0x0040
#define BASELINE_UPDATE_NUM_X        0x0080
#define CRITICAL_OFF                 0x0100
#define OFFBASE_SAVED_Z              0x0200
#define OFFBASE_SAVED_X              0x0400
#define BASELINE_RSSI_GET            0x0800
#define TEMP_BASE_ERR                0x1000
#define OFF_SAVED                    0x2000
#define ON_GET_BASELINE              0x4000
#define EVENT_OFF_SAVED              0x8000


//SingleFlag******************************************************
#define LAST_EVENT_ON                0x0001
#define BASELINE_INITED              0x0002
#define SINGLE_GET_ON                0x0004
#define TEMP_BASE_SAVED_Z2           0x0008  
#define TEMP_BASE_SAVED_X2           0x0010
#define SET_BASE_COMD                0x0020
#define REST_OFF_SEND                0x0040
#define BASELINE_NO_EFT_Z            0x0080
#define BASELINE_NO_EFT_X            0x0100
#define ON_CRITICAL_BAS_Z            0x0200
#define ON_CRITICAL_BAS_X            0x0400
#define ON_CRITICAL_GENERT_Z         0x0800
#define ON_CRITICAL_GENERT_X         0x1000
#define CRITICAL_USED_Z              0x2000
#define CRITICAL_USED_X              0x4000
#define LOST_EVENT_SCANED            0x8000

//OnBaseLineFlag**********************************************************
#define TEMP_ON_BASE_GET_Z           0x0001
#define TEMP_ON_BASE_GET_X           0x0002
#define DEC_VALUE_GENERATE_Z         0x0004
#define DEC_VALUE_GENERATE_X         0x0008
#define ON_EVENT_SCAND               0x0010
#define TEMP_ON_TO_ON                0x0020
#define BASEZ_TIME_START             0x0040
#define BASEX_TIME_START             0x0080
#define TEMP_BASE_CHANGED_Z          0x0100
#define TEMP_BASE_CHANGED_X          0x0200
#define ODD_BASE_EFFECT_Z            0x0400  //奇数
#define EVEN_BASE_EFFECT_Z           0x0800  //偶数
#define ODD_BASE_EFFECT_X            0x1000
#define EVEN_BASE_EFFECT_X           0x2000
#define ON_BASE_GET                  0x4000
#define SENSOR_ON_REST               0x8000
//************************************************************************
//TempBaseFlag*************************************************************
#define BASE_CHANGE_OVER_Z1           0x0001
#define BASE_CHANGE_OVER_X1           0x0002
#define BASE_CHANGE_OVER_Z2           0x0004
#define BASE_CHANGE_OVER_X2           0x0008
#define BASE_EFFECT_OVER_1            0x0010
#define BASE_EFFECT_OVER_2            0x0020
#define EVENT_GET_ON                  0x0040
#define EVENT_EFFECT_X                0x0080
#define BASE_UPDATE_ON_Z              0x0100
#define BASE_UPDATE_ON_X              0x0200
#define EVENT_ON_GENERT               0x0400
#define HALF_EVENT_VALUE_OFF          0x0800
#define P_EVENT_GENERT                0x1000
#define UPLINE_AP_STATE               0x2000
#define MAX_NUM_OFF                   0x4000
#define TIME_ERR_SET                  0x8000


//CompFlags****************************************************************
#define TEMP_BASE_SAVE_FLASH          0x0001
#define DAY_UPDATE                    0x0002
#define EVENT_TIME_ERROR              0x0004
//#define NEED_GET_BASE_LINE_Z          0x0008
//#define NEED_GET_BASE_LINE_X          0x0010
//#define ONE_ADXI_BASE_GET             0x0020
//#define ONE_ADXI_JUDG_END             0x0040
//#define ONE_BASE_Z_GENERT             0x0080
//#define ONE_BASE_X_GENERT             0x0100
#define UP_SECOND_ADD                 0x0200
#define WEAK_UP_CFG_SEND              0x0400
#define OFF_BASELINE_GET_Z            0x0800
#define OFF_BASELINE_GET_X            0x1000
#define OFF_BASE_EFFECT_Z             0x2000
#define OFF_BASE_EFFECT_X             0x4000
#define FLASH_BASE_UPDATE             0x8000
//***************************************************************************

//NewBaseFlag***************************************************************************
#define TEMP_BASE_UPDATE_Z            0x0001
#define TEMP_BASE_UPDATE_X            0x0002
#define OFF_NUM_Z_ON                  0x0004
#define OFF_NUM_X_ON                  0x0008
#define ON_GET_VALUE_START_Z          0x0010
#define ON_GET_VALUE_START_X          0x0020
#define ADD_THRES_VALUE_Z             0x0040
#define ADD_THRES_VALUE_X             0x0080 
#define OTHER_TEMP_X_ON               0x0100
#define OTHER_TEMP_Z_ON               0x0200
#define MAX_THRES_VALUE_Z             0x0400
#define MAX_THRES_VALUE_X             0x0800
#define STATE_SYNC_ON                 0x1000
#define TEMP_X_GENERT                 0x2000
#define OFF_BASE_GET_Z                0x4000
#define OFF_BASE_GET_X                0x8000
//***************************************************************************
typedef struct _SENSOR_SAMPLE_PARAMTER
{ 
  u16 BaseLine;        //基线值;
  u16 OverThresCnt;  //状态3 过阀值计数(Z轴）
  u16 LowThresCnt;   //状态4 低于阀值计数  (Z轴）  
  float pBaseLine;
} SENSOR_SAMPLE_PARAMTER;

typedef struct _SENSOR_TIME_PARAMTER
{
  u16 BaseLineTime;    //状态1校准基线计时值
  u16 BaseLineTimeZ; 
  u16 BaseLineTimeX;
  u16 EventTimeout;
}SENSOR_TIME_PARAMTER;

typedef struct _SNP_EVENT_t
{
  u8 Hour;
  u8 Minute;
  u8 Second;
}SNP_EVENT_t;

typedef struct _EVENT_BUFF
{
  SNP_EVENT_t   Event[SAVE_BUFF_NUM];
  u8            SavePtr;
  u8            SendPtr;
  u8            EventNum;
  u8            LastNum;
}EVENT_BUFF;

typedef struct _BUS_EVENT
{
  u8 Day;
  u8 Hour;
  u8 Minute;
  u8 Second;
  //u8 MaxDecZ;
 // u8 MaxDecX;
}BUS_EVENT;

typedef struct _BUS_EVENT_BUFF
{
  BUS_EVENT  BusNum[BUFF_NUM];
  u16        SavePtr;
}BUS_EVENT_BUFF;

typedef struct _AD_BUFF
{
  u16 Buff[2];
  u8  BuffPtr;
  u8  Num;
  u8  Count;
}AD_BUFF;

typedef struct _AVERAGE_VALUE
{
  u16 Base;
  u16 Value;
  u16 LastValue;
  u8  Num;
}AVERAGE_VALUE;

typedef struct _OFF_AVERAGR_VALUE
{
  u16 Value;
  u16 LastValue;
  u16 Sum;
  u8  Num;
}OFF_AVERAGR_VALUE;
typedef struct  _STABLE_BASELINE
{
  u16 BaseLineTime;
  u16 pBaseLine;
  u8  GenerateNum;
  u8  PositiveNum;
  u8  NegativeNum;
}STABLE_BASELINE;

typedef struct _INIT_BASELINE
{
  u16 BaseLineZ[3];
  u16 BaseLineX[3];
  u8  Num;
}INIT_BASELINE;

typedef struct _BASELINE_THREE_BUFF
{
  u16 BaseLine[3];
  u16 Count;
  u8  Num;
}BASELINE_THREE_BUFF;

typedef struct _TEMP_BASE_BUFF
{
  u16 BaseLine[3];
  u8  SavePtr;
}TEMP_BASE_BUFF;

typedef struct _MIN_DEC_BASELINE
{
  u16  BaseLineZ;
  u16  BaseLineX;
  u16  DecZ;
  u16  DecX;
  u16  LastDecZ;
  u16  LastDecX;
}MIN_DEC_BASELINE;

typedef struct  _SET_BASELINE_DATA
{
 u16  Value;
 u16  Num;
}SET_BASELINE_DATA;
/*
typedef struct _SET_BASELINE_UPDATA_BUFF
{
  SET_BASELINE_DATA    BaseLine[SET_BASE_NUM];
  u16                  LowBaseLine;
  u16                  HighBaseLine;
}SET_BASELINE_UPDATA_BUFF;
*/
typedef struct _HALFBASE_NUM
{
  u16 BaseNum;
  u16 HalfNum;
  u16 PositiveNum;
  u16 NegativeNum;
}HALFBASE_NUM;

typedef struct _ON_EVENT_TIME
{
  u16 OnBase;
  u8 Hour;
  u8 Minute;
  u8 Second;
}ON_EVENT_TIME;

typedef struct _ON_DEC_VALUE
{
  u16 DecZ;
  u16 DecX;
 // u8 State;
}ON_DEC_VALUE;

typedef struct _ON_NUM_BUFF
{
  ON_DEC_VALUE  DecValue[ON_NUM];
  u16            Num;
}ON_NUM_BUFF;


typedef struct _LAST_EVENT
{
  u8 Hour;
  u8 Minute;
  u8 Second;
}LAST_EVENT;

typedef struct _BASELIN_EVEVT
{
  u16 BaseZ;
  u16 BaseX;
}BASELIN_EVEVT;

typedef struct _ON_BASELINE_BUFF
{
  BASELIN_EVEVT  BaseBuff[BASE_NUM];
  u8   BasePtr;
  u8   BaseNum;  
 // u8   TempBasDay;
  //u8   OldBasDay;
}ON_BASELINE_BUFF;

typedef struct _OFF_BASELINE_BUFF
{
  u16  Buff[OFF_BUF_NUM];
  u8   SavePtr;
}OFF_BASELINE_BUFF;

typedef struct _TEMP_CHG_BASE
{
  u16 OldBaseZ;
  u16 OldBaseX;
  u16 NewBaseZ;
  u16 NewBaseX;
}TEMP_CHG_BASE;

typedef struct _OFF_MIN_VALUE_BUFF
{
  u8 CntBuff[12];
  u8 BuffPtr;
  u8 MinNum;
  u8 MinCnt;
  u8 AllCnt;
  u8 AllOffNum;
}OFF_MIN_VALUE_BUFF;
//************************test****************************



//*************************test***************************
void InitMagenticParamter(void);
void  UpdataBasline(u16 pAdValue,SENSOR_SAMPLE_PARAMTER *AxisPam);
void SystemScan(void);
u16 SnpEventConver(u16 pTime);
void RestBaseLine(void);
void ParamterChange(u8 *pBuff);
void linetest(void);
void SendState(void);
void SendAd();
void EventSave(void);
void GetBaseLine(void);
void SaveEventBuff(SNP_EVENT_t *SaveData);
void JumpToEventON(void);
void OnEventGetBaseLine(void); 
void OnEventBaseLineUpdate(void);
void SmoothUpdata(void);
void SaveEvent( u8 Type);
void GetBigValue(void);
void GetBaseLineZ(void);
void GetBaseLineX(void);
void HalfBaseLineZ(u16 tempZ);
void HalfBaseLineUpdateZ(void);
void OnEventGetBaseLineZ(void);
void OnBaseLineUpdateZ(void);
void BaseLineUpdataZ(void);
void BaseLineUpdataX(void);
void AnyBaseLineUpdateZ( STABLE_BASELINE *StableBaseZ, SENSOR_SAMPLE_PARAMTER *EventZ);
void AnyBaseLineUpdateX( STABLE_BASELINE *StableBaseX, SENSOR_SAMPLE_PARAMTER *EventX);
u16 GetBaseLineAny(u16 AdValue, SENSOR_SAMPLE_PARAMTER  *TempBaseLine, BASELINE_THREE_BUFF *BaseBuff );
void GetNearestBaseLine( u8 Direct, u16 Value );
void DectectZ( u16 tempZ );
void DectectX(u16 tempX);
void HalfBaseLineX( u16 tempX );
void OnEventGetBaseLineX(void);
void HalfDecZ(void);
void HalfDecX(void);
void EventOff(void);
void OnSaveEvent(u8 Type, ON_EVENT_TIME *Time);
void OnTempEvent(void);
void SaveEventOff(void);
void BaseChangEvent(void);
u8 DecCompZ( u8 num );
u8 DecCompX( u8 num );
u8 ScanOnBaseBuff(void);
u8 DecBase( u16 Base1, u16 Base2 );
void OnBaseInitChg(void);
void EventChgSave( LAST_EVENT *SaveData );
void CommdOffBaseLine(void);
u8 DecBaseOn( u16 Base1, u16 Base2 );
void  SaveEventMain(void);
void BaseTimeStartX(void);
void BaseTimeStartZ(void);
u8 DecDect( u16 Base1, u16 Base2);
u8 DecBaseEvent( u16 Base1, u16 Base2 );
u8 DecBigDetect( u16 Base1, u16 Base2);
void FlashBuffUpdateZ(void);//FlashBuffUpdateZ();
void FlashBuffUpdateX(void);//FlashBuffUpdateX();
u8 DecBigTerg( u16 Base1, u16 Base2 , u8 Value);
u8  AverageValueGet( AVERAGE_VALUE *TempValue, u16 AdValue);
u8 ComperTempBuff( TEMP_BASE_BUFF *TempBuff );
u8 AverageAdGet( OFF_AVERAGR_VALUE *TempValue, u16 AdValue );
void OnAddOff(void);
#endif