#ifndef TIMESLOT_H
#define TIMESLOT_H

#define  DEC_SYNC_TIME           537//61//123//
#define  MIN_CLCYL_SEN_NUM       5
#define  SLOT_INTERVAL_1         1//
#define  SLOT_INTERVAL_2         10
#define  POWER_AD_REF            250 
#define  STATE_RF_DELAY          8
#define  EVENT_AP_RF_DELAY       9
#define  EVENT_RF_DELAY          120    
#define  AD_REST_DELAY           43200


//DebugFlag*************************************************************
#define   RELEVANCE_BUS_REQUEST_SEND_ON      0x0001
#define   STATE_VALUE_SEND_ON                0x0002
#define   SIGNAL_REQUEST_ON                  0x0004     
#define   DEBUG_SEND_ON                      0x0008    
#define   CODE_ADRESS_MATE                   0x0010
#define   CODE_BANK_LOW                      0x0020
#define   STATE_SEND                         0x0040
#define   SEN_WEAK_UP_ON                     0x0080
#define   DOWN_LINE_RF                       0x0100
#define   RF_ALL_SYNC_ON                     0x0200
#define   RF_DEMO_SYNC                       0x0400
#define   RF_TEST_SEND                       0x0800
#define   PUMP_CHG_TEMP                      0x1000
#define   TEST_SYNC_MODE                     0x2000
#define   RE_SCAN_SYNC                       0x4000
#define   RF_POWER_SET                       0x8000
//************************************************************************

#define Sync_Frm0				0x00
#define Sync_Frm1				0x01
#define Check_Event1 			        0x02
#define Check_Event2 			        0x03
#define Check_Event3				0x04
#define Check_Event4   			        0x05
#define Check_Event5				0x06
#define Event_Reserved			        0x07
#define Ack_WeakUp				0x08
#define Sync_WeakUp				0x09
#define Neight_Ack_WeakUp                       0x0a
#define TestFirm                                0x0b
#define Deal_DebugAck                           0x0c
#define DownSysScan                             0x99
 

#define Check_Event18				0x12
#define Check_Event19				0x13
#define Check_Event20				0x14
#define Check_Event21				0x15
#define Check_Event22				0x16
#define Check_Event23				0x17
#define Check_Event24				0x18
#define Check_Event25				0x19
#define Check_Event26				0x1A
#define Check_Event27				0x1B
#define Weak_Up28				0x1C
#define Weak_Up29				0x1D
#define Ack30				        0x1E
#define Deal_Ack31				0x1F
#define Weak_Up32				0x20
#define Weak_Up33                               0x21  
#define Check_Event34                           0x22
#define Check_Event35                           0x23
#define Check_Event36				0x24
#define Check_Event37				0x25
#define Check_Event38				0x26
#define Check_Event39				0x27
#define Check_Event40				0x28
#define Check_Event41				0x29
#define Check_Event42				0x2A
#define Check_Event43				0x2B
#define Check_Event44				0x2C
#define Check_Event45				0x2D
#define Check_Event46				0x2E
#define Check_Event47				0x2F
#define Check_Event48				0x30
#define Check_Event49                           0x31  
#define Check_Event50                           0x32
#define Check_Event51                           0x33
#define Check_Event52				0x34
#define Check_Event53				0x35
#define Check_Event54				0x36
#define Check_Event55				0x37
#define Check_Event56				0x38
#define Check_Event57				0x39
#define Weak_Up58				0x3A
#define Weak_Up59				0x3B
#define Ack60				        0x3C
#define Deal_Ack61				0x3D
#define Weak_Up62				0x3E
#define Weak_Up63				0x3F

#define Sync_Frm64				0x40
#define Sync_Frm65				0x41
#define LoadCMD_FirmUPD66 			0x42
#define LoadCMD_FirmUPD67 			0x43
#define Check_Event68				0x44
#define Check_Event69   	                0x45
#define Check_Event70				0x46
#define Check_Event71				0x47
#define Check_Event72				0x48
#define Check_Event73				0x49
#define Check_Event74				0x4A
#define Check_Event75				0x4B
#define Check_Event76				0x4C
#define Check_Event77				0x4D
#define Check_Event78				0x4E
#define Check_Event79				0x4F
#define Check_Event80				0x50
#define Check_Event81				0x51
#define Check_Event82				0x52
#define Check_Event83				0x53
#define Check_Event84				0x54
#define Check_Event85				0x55
#define Check_Event86				0x56
#define Check_Event87				0x57
#define Check_Event88				0x58
#define Check_Event89				0x59
#define Check_Event90				0x5A
#define Check_Event91				0x5B
#define Weak_Up92				0x5C
#define Weak_Up93				0x5D
#define Ack94				        0x5E
#define Deal_Ack95				0x5F
#define Weak_Up96				0x60
#define Weak_Up97                               0x61  
#define Check_Event98                           0x62
#define Check_Event99                           0x63
#define Check_Event100				0x64
#define Check_Event101				0x65
#define Check_Event102				0x66
#define Check_Event103				0x67
#define Check_Event104				0x68
#define Check_Event105				0x69
#define Check_Event106				0x6A
#define Check_Event107				0x6B
#define Check_Event108				0x6C
#define Check_Event109				0x6D
#define Check_Event110				0x6E
#define Check_Event111				0x6F
#define Check_Event112				0x70
#define Check_Event113                          0x71  
#define Check_Event114                          0x72
#define Check_Event115                          0x73
#define Check_Event116				0x74
#define Check_Event117				0x75
#define Check_Event118				0x76
#define Check_Event119				0x77
#define Check_Event120				0x78
#define Check_Event121				0x79
#define Weak_Up122				0x7A
#define Weak_Up123				0x7B
#define Ack124				        0x7C
#define Deal_Ack125				0x7D
#define Weak_Up126				0x7E
#define Weak_Up127				0x7F

#define Check_Events                            0x81
#define Sen_UpLine                              0x82
#define UpLineAck                               0x83
#define Events_WeakUp                           0x84
//#define Ack_WeakUp                              0x85
#define Deal_Ack                                0x86
#define Events_WeakUp_1                         0x87
#define Events_WeakUp_2                         0x88
#define Ack_WeakUp_1                            0x89
#define Ack_WeakUp_2                            0x8A
#define Weak_Up63_1                             0x8B
#define Weak_Up63_2                             0x8C
#define WeakUp_Sync                             0x8D
//#define Ack_WeakUp_0                            0x8E
//#define Weak_Up63_0                             0x8F
#define DownCode_Firm1                          0x90
#define DownCode_Firm1_Ack                      0x91
#define DownCode_Firm2                          0x92
#define DownCode_Firm2_Ack                      0x93
#define DownCode_Firm3                          0x94
#define DownCode_Firm3_Ack                      0x95
#define DownCode_Firm4                          0x96
#define DownCode_Firm4_Ack                      0x97
#define DownCode_WeakUp                         0x98

typedef struct _CLOCK_VALUE
{
 // u16 RandomNUM;
  u16  DownLineDelay;
  u16 DelayUplineScan;
  u16 UplineSecond;
  u8  msnum;
  u8 UpLineSecond;  
  u8 TestSecond;
  u8 StateSecond;
}CLOCK_VALUE;

typedef struct _TACC_COUNT_VALUE
{
  u16 Firm1Event;
  u16 WeakUpDealAck;
  u16 Firm0ToFirm1;
  u16 ToNextEvent;
  u16 ReservedWeakUp;
  u16 WeakUpSync;
  u16 AssocBusWeakUp;
  u16 ReservedSyncWeakUp;
 // u16 NeighbSyncWeakUp;
  u16 NeighbWeakUpDealAck;
  u16 DealAckSyncWeakUp;
}TACC_COUNT_VALUE;

typedef struct _LAST_SEND_PACKET
{
  u16 SendNum;
 // u16 ReSendNum;
  u8 Hour;
  u8 Minute;
  u8 Second;
  u8 ucSerNr;
}LAST_SEND_PACKET;

typedef struct _TIME_SLOT_PARMAT
{
  u16 RcvSyncNum;
  u16  SenTimeSlotNum; //SEN Ê±¼ä²Û ±àºÅ
  u16 ReportMinute;
  u8  ReciveSyncRepeat;
  u8  MinTimeSlot;
  u8  Second;
  u8  Minute;
  u8  Hour;
  u8  LastHour;
  u8  TimeSlotNum;
  u8  AllTimeSlotNum;
  u8  StartWorkTime;
  u8  StopWorkTime;
  u8  ReportSecond;
  u8 UplineTime;
}TIME_SLOT_PARMAT;


typedef struct _ADD_SLOT_NUM
{
  u8 SenID;
  u8 Second;
  u8 MsTime;
  u8 SendNum;
}ADD_SLOT_NUM;
//**********************************************************
// u16 TimeCommunicatFlag
#define  SYS_WEAKE_UP              0x0001  
#define  DOWN_CODE                 0x0002
#define  DOWN_CODE_DOWN_LINE       0x0004
#define  SEN_ON_LINE               0x0008   
#define  RECIVE_SYNC               0x0010
#define  REPORTR_SWITCH            0x0020
#define  SEN_CONFIG_DOWN_CODE      0x0040
#define  DEMO_SYNC                 0x0080
#define  EVENT_SEND                0x0100 
#define  RECIVE_ACK                0x0200   
#define  VALUE_CHG_SEND            0x0400    
#define  STATE_SEND_ON             0x0800
#define  VALUE_ACK                 0x1000
#define  SAME_TIME_QUERY           0x2000
#define  CFG_SYNC_ON               0x4000
#define  EVENT_SEND_ON             0x8000
//***********************************************************
//u8 RfSendFlags
#define  RF_ON                     0x01
#define  EVENT_SEND_NEED           0x02
#define  UP_LINE_MODE              0x04
#define  POWER_AD_REF_ON           0x08
#define  BASE_LINE_FILP_SEND_ON    0x10
#define  RF_SEND_ON                0x20
#define  CONNECTED_AP              0x40
#define  TIME_SLOT_SET             0x80


//******************************************************88***

//*************************************************************

void TimerAInit(void);
void TimerA_RestCount(u16 CountNum);         
void TimerAStart(void);
void TimerAStop(void);
void ClockInit(void);
void TimeParamterInit(void);
void SendEventData(void);
void ModeB_EventSlot(void);
void ModeK_Slot(void);
void ModeB_EventHighSlot(void);
void TimeSlotConfig(void);
u8 SendBuffUpdata();
u8 CreatTimeSlot(void);
void ModeUpLineSlot(void);
void StateSend(void);
void ModeTest_Slot(void);
void ReciveUpLineAck(void);
//void SyncLosedConnect(void);
//void SyncInitConnect(void);
void EventNoCareSend(void);
void EventJump(void);
void ModeDownCode_Slot(void);
void DownLineConfig(void);    
u16 CreatRandomNum(void);
void UplineConfig(void);
void  TimeClockUpdate(void);
void SaveCode(void);
void ScanRFSet(void);
//void SetBaseBuffUpdate(void);
void SetBaseBuffUpdateZ(void);
void SetBaseBuffUpdateX(void);
void TimeSlotUpdate(void);
void DownLineEvent(void);
void AdTimeClear(void);
#endif