

#ifndef _SNP_H_
#define _SNP_H_

#include "types.h"

//============================================================================================//

//



//============================================================================================//

//
// 包结构定义.
//
//AP指接收机， SEN指检测器
// 结构元素间不填充(PAD)任何字节用于对齐.
#pragma pack(1)
typedef struct _SNP_PHR_t   //包长6
{
	u8		ucSize;			// 包长度
	u8		uiFcf;			// FCF 本系统标志，用于解析当前包标志，区别其他可能的干扰系统，值固定为0x8a
                #define  FCF_DEF       0x8a
	u8		SlotNum;		//
	u8		uiType;			// 包类型(Packet type).
		#define	SNP_PACKET_TYPE_SYNC		( 1u )		// 同步包.  (AP-->SEN)	
                #define DOWN_CODE_SYNC	                ( 2  )
		#define	SNP_PACKET_TYPE_SEN_CFG		( 3u )		// 配置包.(AP-->SEN)
		#define	SNP_DOWN_CODE_MODE		( 7u )		// 更新程序包.(AP--SEN) 
                #define SNP_SEND_BUS_STATE               ( 5 )        //发送缓存数据test
                #define SNP_SET_ALL_PUMP                 ( 6 )         //设置频率
                #define SNP_SIGNAL_STATE                 ( 4)        // 信号强度状态包
                #define CONFIG_TO_DOWN_CODE_MODE         ( 8)           //进入下载程序配置
                #define SEND_EVENT_MANUAL                (9u)         //手动发送事件
                #define TEST_DEMO_MODE                   ( 10 )      //测试模式
                #define VALUE_CHANGED                    ( 11 )
                #define VALUE_CHANGED_ACK                ( 12 )
                #define SAME_TIME_QUERY_MODE             ( 13 )
        //******************************************************
                #define RELEVANCE_BUS_REQUEST            ( 14 ) //   连车包请求
                #define RELEVANCE_BUS_ACK                 (15)  //  连车包回传信息AP--》sen
                #define SIGNAL_RELEVANCE                  (16)  //信号质量请求
                #define SIGNAL_RELEVANCE_ACK              (17)  //信号质量请求ACK
                #define STATE_VALUE_CHANGED               (18)  //状态变化信息上传                                      
                #define DEBUG_MESSAGE                     (19)  //DEBUG 信息上传
                #define DEBUG_MESSAGE_ACK                 (20)  //DEBUG /状态变化信息 ACK
                #define STATE_ACK                         (28)  //状态包Ack(激活sen)//
                #define SNP_PACKET_QUERY                  (23)  //车位询问包
                #define SNP_PACKET_QUERY_ACK              (24)
                #define AP_COMAND                         (31)  //手持控制AP命令
        //*********************************************************************************8
                #define	SNP_PACKET_TYPE_STATE		( 0x21 )	// 状态包.(SEN-->AP) 
                #define SNP_PHR_TYPE_UP_LINE            ( 0x31 )       //正常上线包  （车位号，时间槽已配置）（SEN-->AP）
                #define SNP_TIMESLOT_UP_LINE            ( 0x3D )    //初次上线包（车位号,时间槽未配置）SEN-->AP）   
                #define SNP_DOWN_CODE_UP_LINE            ( 0x35) 
		#define SNP_PACKET_TYPE_SEN_A		(0x65 )        // 停车检测模式（即正常工作模式） (SEN-->AP)，SEN发送停车ON或OFF给AP              
		#define SNP_PACKET_TYPE_UF_DATA		( 0xD2u )	// 更新SEN程序的数据.  (AP-->SEN)
		#define	SNP_PACKET_TYPE_UF_ACK		( 0xD3u )	// 更新SEN程序 对SNP_PACKET_TYPE_UF_DATA的应答.    (SEN-->AP)    
                #define SNP_TIMESLOT_UPLINE_ACK          ( 0x81)  //    AP设置SEN时间槽包 对SNP_TIMESLOT_UP_LINE 的应答
                #define SNP_CFG_SEN_ACK                 ( 0x85 )  //   SEN对AP 配置包的应答，（SEN-->AP）,对SNP_PACKET_TYPE_SEN_CFG的应答
                #define	SNP_PACKET_TYPE_AP_ACK		( 0x6Eu )	// AP应答包.   (AP-->SEN)，对SNP_PACKET_TYPE_SEN_A发送 的应答
                #define AD_TEST_DEMO                    ( 0x91 )  //AD值发送（测试）
                #define RF_TEST_SYNC                     (0x92)
                #define RF_TEST_ACK                      ( 0x93 )
                #define RF_ALL_SYNC                       (0x94)                               //(0x90--0xA0) //手持设备与AP通讯命令

        u16		 uiDevId;		// (系统发送端ID)           
} SNP_PHR_t; 
#pragma pack()



//AP配置SEN包（占用同步包时间）  AP-->SEN  对应 SNP_PACKET_TYPE_SEN_CFG包
typedef struct _SNP_CFG_PACKET_t //包长16
{
	SNP_PHR_t	sPhr;
        u8		AllTimeSlotNum;	// 1个大周期包含小周期个数（1个小周期为250ms）
        u8              Hour;      //时
        u8              Minute;    //分
        u8              Second;     //秒，
        u8              Msec;   //不用
        u8              TimeSlotNum;  //小周期计数值
	u16		uiDestId;		// 	SEN解析与本机ID匹配时, 执行'uiCmd'定义的命令.
	u16		uiCmd;			// 命令类型, 低4位为命令，高12位为参数
		#define SNP_CMD_PUMP_bm			        ( 1u )		// 设置通道号（频率）
		#define SNP_CMD_SEN_RECAL			( 2u )		// /复位	
                #define SNP_CMD_ENTER_UF                        (3u )          // 下载程序                
                #define  SNP_CMD_SEND_BUS                        ( 5 )
                #define  SNP_CMD_SET_BASELINE                    (6) //设置基值
                #define REST_COMMEND                              7
                #define SNP_SET_TIMESLOT                         (8) //设置频率
                #define  SNP_BASELINE_GET                         (9)
                #define SET_SETBASE_X                             (10)  //设置基值X
                #define SER_SETBASE_Z                           (4u)   //设置基值Z
                #define SET_RF_POWER                             (11)
                #define SET_OFF_BASELINE                         (12)    
                #define SET_ID                                   (13)
                #define SET_NEW_PUMP                              (14) //检测器激活
        u8              Parmet;
        u8              CheckNumLow; 
        u8              CheckNumHigh;
        
} SNP_CFG_PACKET_t;


typedef struct  _SNP_SET_PUMP_CFG_t
{
  SNP_PHR_t	  sPhr;
  u16             Pump;
  u16             SenID[8];
  u8              Reserved1;
  u8              CheckNumLow;
  u8              CheckNumHigh;
}SNP_SET_PUMP_CFG_t;
//AP同步包  AP-->SEN  //用于SEN校准时间，公共参数配置  对应SNP_PACKET_TYPE_SYNC包
typedef struct _SNP_SYNC_PACKET_t   //包长21
{
	SNP_PHR_t	sPhr;
        u8		AllTimeSlotNum;	// 总时间槽个数（带检测器的数量），12的倍数
        u8              Hour;      //时
        u8              Minute;    //分
        u8              Second;     //秒，
        u8              Msec;   //毫秒定义值， 值为0,1,2,3，  0 代表0ms，1代表250ms，2代表 500ms，3代表750ms  
        u8              TimeSlotNum;  //当前时间槽
        u8              StartWorkTime;  //  SEN开始工作的时间(单位 小时)
        u8              StopWorkTime;   //  SEN结束工作的时间（单位 小时）
        u8              CfgBox;
        u8              SystemParameter[2];	//15 16位
        u8              CheckNumLow;
        u8              CheckNumHigh;
} SNP_SYNC_PACKET_t;

//SEN 应答包，对应SNP_CFG_SEN_ACK命令
typedef struct _SNP_SEN_CFG_ACK_PACKET_t  //包长8
{
  SNP_PHR_t	sPhr;
   u16		uiCmd;	  //AP配置包的命令回传
   u8           CheckNumLow;
   u8           CheckNumHigh;
}SNP_SEN_CFG_ACK_PACKET_t;


// AP应答包结构. 对应 SNP_PACKET_TYPE_AP_ACK
typedef struct _SNP_AP_ACK_PACKET_t   //包长14
{
        SNP_PHR_t	sPhr;  
	u16		SenID[5];		
        u8              CheckNumLow;
        u8              CheckNumHigh;
												
} SNP_AP_ACK_PACKET_t;

//******************************************************************************************************
//检测器ID :a5 56   频率：6d 00

typedef struct _SNP_RELEVANCE_BUS_REQUEST_PACKET  //检测器发送连车请求包  对应命令 RELEVANCE_BUS_REQUEST    已调通  检测器串口命令 77 a5 56 02 ff
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SNP_RELEVANCE_BUS_REQUEST_PACKET;

typedef struct _SNP_RELEVANCE_BUS_REQUEST_ACK_PACKET  //ap回传“检测器发送连车请求包” ACK， 对应命令 RELEVANCE_BUS_ACK
{
  SNP_PHR_t	sPhr;  
  u16           SenID;
  u8            Front; 
  u8            Behind;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SNP_RELEVANCE_BUS_REQUEST_ACK_PACKET;

typedef struct _SIGNAL_RELEVANCE_PACKET  // 信号质量请求包，对应命令 SIGNAL_RELEVANCE
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SIGNAL_RELEVANCE_PACKET;

typedef struct _SIGNAL_RELEVANCE_ACK_PACKET  //信号质量ACK，AP回传，对应命令 SIGNAL_RELEVANCE_ACK
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  int8          Rssi;
  int8          Snr;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SIGNAL_RELEVANCE_ACK_PACKET;

typedef struct  _STATE_VALUE_CHANGED_PACKET  // 状态值改变上传包， 对应命令 STATE_VALUE_CHANGED   已调通 捡测器串口命令 66 a5 56 02 ff
{
   SNP_PHR_t	sPhr;  
   u16          AdValue;   //BIT15： ON/OFF 事件   0--14: AD值
   u8           Hour;      //时
   u8           Minute;    //分
   u8           Second;     //秒
   u8           Recived;
   u8           CheckNumLow;
   u8           CheckNumHigh;
}STATE_VALUE_CHANGED_PACKET;

typedef struct _DEBUG_MESSAGE_PACKET  //Debug 包上传， 对应命令  DEBUG_MESSAGE 
{
  SNP_PHR_t	sPhr;   
  u16           Value1;
  u16           Value2;
  u16           Value3;
  u16           Value4;
  u16           Value5; 
  u8           CheckNumLow;
  u8           CheckNumHigh;
}DEBUG_MESSAGE_PACKET;

typedef struct _DEBUG_MESSAGE_ACK_PACKET  // 状态值改变 和Debug 包Ack,  对应命令 DEBUG_MESSAGE_ACK
{
  SNP_PHR_t	sPhr;  
  u16           SenID; 
  u8            Type;  // 为检测器发送的相应标志位，STATE_VALUE_CHANGED 或 DEBUG_MESSAGE
  u8            Recive;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}DEBUG_MESSAGE_ACK_PACKET;

typedef struct  _STATE_ACK_PACKET //STATE_ACK   状态报ACK（激活SEN）
{
  SNP_PHR_t	sPhr;
  u16           SenID; 
  u8            Recive1;
  u8            Recive2;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}STATE_ACK_PACKET;
//*********************************************************************************


typedef struct _SNP_TIME_QUERY_PACKET
{
  SNP_PHR_t	sPhr;  
  u16           SenID;    
  u8            CheckNumLow;
  u8            CheckNumHigh;
}SNP_TIME_QUERY_PACKET;

typedef struct _SNP_AP_VALUE_ACK_PACKET  //16
{
  SNP_PHR_t	  sPhr;  
  u16             SenID;   
  u8              HourA;
  u8              MinuteA;
  u8              SecondA;
  u8              HourB;
  u8              MinuteB;
  u8              SecondB;
  u8              CheckNumLow;
  u8              CheckNumHigh;
}SNP_AP_VALUE_ACK_PACKET;


typedef struct _SNP_SIGNAL_STATE_PACKET_t
{
   SNP_PHR_t	sPhr;        //sPhr.uiType = 7  包类型
   u16          BaselineZ;   //Z轴基值
   u16          BaselineX;   //X轴基值
   u8           DecZX;     //当前值与基值差 高4位Z轴差，低4位X轴差
   u8           State;    // 状态值，AP收到的状态值相同才能运算
   u8           CheckNumLow;
   u8           CheckNumHigh;
}SNP_SIGNAL_STATE_PACKET_t;

// 状态包， 上线包 结构.  对应 SNP_PHR_TYPE_UP_LINE，SNP_TIMESLOT_UP_LINE，SNP_PACKET_TYPE_STATE包
typedef struct _SNP_UPLINE_PACKET_t  //包长17
{
	SNP_PHR_t	sPhr;//同步头
        u8              PowerInt;    //低4位电池电压，高4位RF功率
        u8              PowerFloat;
        u8              BaseChgNum;    //    
        u8              VersionLow;
        u8              VersionHigh;
        u8              CodeAdress;
        u16             AdValueZ;
        u16             AdValueX;
        u16             BaseZ;
        u16             BaseX;
        u16             ResendNum;
        u8              BaseAverageNum;
        u8              OnEventChgNum;
        u8              CheckNumLow;
        u8              CheckNumHigh;
} SNP_UPLINE_PACKET_t;

//事件包 SEN-->AP 对应 SNP_PACKET_TYPE_SEN_A ，车位ON或OFF时，SEN发送状态时间给AP
typedef struct _SNP_SEN_MODE_PACKET_t           //包长16
{
	SNP_PHR_t	sPhr;   //6
        u8              Hour;      //时
        u8              Minute;    //分
        u8              Second;     //秒， 此BIT0--BIT6 为秒值，BIT7为车位ON，OFF标志位，BIT7=1 为ON，BIT7=0 为OFF  
        u8              Day; //不用
        u8              CheckNumLow;
        u8              CheckNumHigh;
} SNP_SEN_MODE_PACKET_t;

typedef struct _BUS_SEND_PACKET_t
{
  SNP_PHR_t	sPhr;
  u8            Day;
  u8            Hour;
  u8            Minute;
  u8            Second;
  u8            MaxDecZ;
  u8            MaxDecX;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}BUS_SEND_PACKET_t;


typedef struct _VALUE_CHG_PACKET_t
{
  SNP_PHR_t	sPhr;
  u8            Hour;
  u8            Minute;
  u8            Second;
  u8            temp;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}VALUE_CHG_PACKET_t;

typedef struct  _SNP_STATE_PACKET_t
{
  SNP_PHR_t	sPhr;  //包头标示位为：0x21
  u8       VersionLow;
  u8       VersionHigh;
  u8       PowerInt;//  电池电压
  u8       PowerFloat;
  u16      BaseLineZ;  //Z轴基值
  u16      BaseLineX;  //X轴基值
  u16      AdValueZ;  //Z轴当前值
  u16      AdValueX;  //X轴当前值
  u16      OnBaseLineZ; //Z轴ON时临时基值
  u16      OnBaseLineX;//X轴ON时临时基值
  u16      SendNum;   // 事件发送次数
  u16      ReSendNum;  //事件重传次数
  u8       BaseLineSaveNum;  //基值存储次数
  u8       ReEventNum;   //备用
  u8       CheckNumLow;
  u8       CheckNumHigh;
}SNP_STATE_PACKET_t;


typedef struct _SNP_UF_DOWN_CODE_PACKET_t  //程序下载
{
  SNP_PHR_t	sPhr;
  u16           SenID;
  u16           AllNum;
  u16           CurrentNum;
  u8            CodeData[32];
  u8       CheckNumLow;
  u8       CheckNumHigh;
}SNP_UF_DOWN_CODE_PACKET_t;


typedef struct _SNP_UF_ACK_PACKET_t  //检测器ACK
{
	SNP_PHR_t	sPhr;
        u16      SavedBuffNum;
        u8       Type;
        u8       temp;
        u8       Data[32];
        u8       CheckNumLow;
        u8       CheckNumHigh;
} SNP_UF_ACK_PACKET_t;

typedef struct _AD_TEST_PACKET_t
{
  SNP_PHR_t	sPhr;
  u16           AdValueZ;
  u16           AdValueX;
  u8            PowerInt;
  u8            PowerFloat;
  u8            Rest;
  u8            recived;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}AD_TEST_PACKET_t;

typedef struct _RF_TEST_ACK_PACKET_t
{
  SNP_PHR_t	sPhr;
  int16         Snr;
  int16         Rssi;
  u8            CheckNumLow;
  u8            CheckNumHigh;
}RF_TEST_ACK_PACKET_t;

#endif