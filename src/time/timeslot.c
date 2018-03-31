#include "types.h"
#include "timeslot.h"
#include "hal_cc2520.h"
#include "ad.h"
#include "uart.h"
#include "magentic.h"
#include "snp.h"
#include <string.h>
#include "board.h"
#include "cfg.h"
#include "rf_hal.h"
#include "flash.h"
#include "24l01.h"
#include <stdlib.h>
#include <stdlib.h>

/*************************************************************************************
//数据收发程序，需要根据NB-LOT协议更改，其中ScanRFSet（），为事件扫描函数，暂时不用更改。TimeClockUpdate（）。为记时函数，可根据需求调整。
// 其余程序可根据NB-LOT协议更改。
**********************************************************************************************************/
extern STABLE_BASELINE         StableBaseLineZ;
extern STABLE_BASELINE         StableBaseLineX;
extern BUS_EVENT_BUFF BusEvent;
extern ON_BASELINE_BUFF BaseLineBuff;
extern SNP_SEN_CFG_ACK_PACKET_t SenAckPacket;
extern SENSOR_SAMPLE_PARAMTER AxisX1Pam;
extern SENSOR_SAMPLE_PARAMTER AxisZ1Pam;
extern SENSOR_SAMPLE_PARAMTER EventOnBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER EventOnBaseLineX;
extern INIT_BASELINE InitBaseline;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineX;
//extern SET_BASELINE_UPDATA_BUFF  SetBaseBuffZ;
//extern SET_BASELINE_UPDATA_BUFF  SetBaseBuffX;
extern MAGNETIC_VALUE Magnetic;
extern SNP_EVENT_t OnTempValue;
extern SNP_UF_ACK_PACKET_t UfAckPacket;
extern SNP_SYNC_PACKET_t SyncPacket;
extern EVENT_BUFF  EventBuff;
extern u16 TempBaseFlag;
extern u8 OffTempBaseSecond;
extern u8 BaseOffNum; 
extern u8 TriggValue;
extern u8 DetectValue;
extern u8 OnBaseChangeNum;
extern u8 OnBaseUpdateNum;
extern u8 TempBaseDayCnt;
extern SNP_PHR_t CommunicateTest;
extern u16 LastBaseLineZ;
extern u16 LastBaseLineX;
extern u16 SetFlags;
extern const u16 PumpTb1[10];
extern FLASH_PARAMTER_t  FlashParamt;//
extern SENSOR_TIME_PARAMTER  SenTime;
extern RF_FCS_t g_sRfFcs;
extern SNP_EVENT_t OnSaveBuff;
extern SNP_EVENT_t OffSaveBuff;
extern STABLE_BASELINE StableBaseLine;
extern HALFBASE_NUM HalfNumZ;
extern HALFBASE_NUM HalfNumX;
extern TEMP_CHG_BASE ChangeBaseBuff[2];
extern OFF_BASELINE_BUFF OffBaseBuffZ;
extern OFF_BASELINE_BUFF OffBaseBuffX;
extern u16 ConfigFlags;
extern u16 AdMagenticFlags;
extern u16 SaveCodeAddress;
extern u16 BaseLineFlag;
extern u16 CheckNumWrite;
extern u16 CheckNumRead;
extern u16 SetBaseLineZ;
extern u16 SetBaseLineX;
extern u16 ExtraFlags;
extern u8 SystemState;
extern u8 RssiTestNum;
extern u8 DownCodeFlag;
extern u8 EventBuffFlag;
extern u8 gb_RateBuf_Addr;
extern u8 LeadCode;
extern RF_PARAMTER RfParamt;
extern CODE_SAVE_BUFFER CodeBuffer;
extern AD_TIME_CYCLE AdTime;
extern u16 pSenID;
extern u16 pTimeSlot;
extern u16 PumpHigh;
extern u16 PumpLow;
extern u16 CompFlags;
extern u8 gb_BandBuf_Addr;
extern u8 BaseLineSaveNum;
extern u8 ACK_ON;
extern u8 s_aucApBuffer[64];
extern u8 NewLineOFF;  
extern u8 SignalState;
extern u8 LastSignalState;
extern u8 InitBaseLineCount;
extern u8 ReEventNum;
extern int8 pRssi;
extern int8 pSnr;
extern LAST_EVENT LastEvent;
extern u8 gb_PowerBuf_Addr;
extern u16 AdCount;
extern u16 SysCount;
extern u16 TempBaseZ;
extern u16 TempBaseX;
extern int8 ComparRssi;
extern u8 pEventHour;
extern u8 pEventMinute;
extern u8 pEventSecond;
extern u16 SingleFlag;
extern u16 HalfBaseLineFlag;
extern u16 RefAd;
extern u32 PowerAd;
extern u32 AdPowerTemp;
extern u8 TestDemo;
extern ON_NUM_BUFF OnNumBuff;
extern u8 DownLineNum;
extern u8 SysTimeSlot;
extern u8 TimeSlotMode;
extern u8 CodeAdress;
extern u16 ChangLastID;
extern u8 testflag;
extern u8 OffNumZ;
extern u8 OffNumX;
extern u8 OldBaseDayCnt;
extern u8 OnTime;
extern u8 OnBaseMoved;
extern u8 OffBaseOpen;
extern u8 BaseBuffZPtr;
extern u8 BaseBuffXPtr;
extern u16 FlashBaseBuffZ[BASE_BUFF_NUM];
extern u16 FlashBaseBuffX[BASE_BUFF_NUM];
extern u8 OffValueCntBuffNum;
extern u8 OffTime;
extern u8 DecMaxAd;
extern u16 NewBaseFlag;
extern u8 DetectValue;
extern u16 NewBaseFlag;
extern u8 OffBaseGetTime;

u8 RfStartNum = 0;
u8 pUpLineSecond;
u8 OpenRFDelay;
CLOCK_VALUE Clock;
//SNP_EVENT_t LastSendEvent;
LAST_SEND_PACKET LastSend;
TIME_SLOT_PARMAT TimeSlot;
AD_TEST_PACKET_t AdValuePacket;
ADD_SLOT_NUM  AddSlotNum;
TACC_COUNT_VALUE TaccAdd;
SNP_SEN_MODE_PACKET_t EventPacket;
SNP_SEN_MODE_PACKET_t SenQueryPacket;
SNP_UPLINE_PACKET_t UplinePacket;
SNP_STATE_PACKET_t StatePacket;
VALUE_CHG_PACKET_t ValueChgPacket;
SNP_TIME_QUERY_PACKET  TimeQueryPacket;
SNP_RELEVANCE_BUS_REQUEST_PACKET  BusRequestPacket;
STATE_VALUE_CHANGED_PACKET StateValuePacket;
SIGNAL_RELEVANCE_PACKET  SingleRequestPacket;
DEBUG_MESSAGE_PACKET     DebugPacket;
EVENT_SAVE_SYS  SaveEventFlash;
extern u8 DetectValue;
//extern u8 OffTime;
//extern u8 EventChangTime;
//extern u8 BaseBuffTime;
// u8 MaxOffNum;
u16 TimeCommunicatFlag;
u16 ReportTime;
//u16 DownLineSecond;
u16 DebugFlag;
u8 ReSendNumE = 0;
u8 AckSendNum;
u8 UplineNum = 0;
u8 RfSendFlags;
u8 SendBusPtr;
u8 PslotNum;
u8 NotScanSyncNum;
u8 PumpTbNum = 0;
u8 LastSystem;//
u8 RestSecond = 0;
u8 ReSendCnt;
u16 pStateSecond;
u8 UplineSendNum = 0;
u8 NumRx = 0;
u8 UplineDelaySecond;
u16 ReSendNum = 0;
u8 OnSedNum = 0;
u8 OffSendNum = 0;
u8 BaseAverageNum = 0;
u32 PowerBuff[4];
u8 PowerBuffPtr = 0;
u8 AdRestSecond = 0;
u8 ReastOffSecond;
u16 SenRestSecond = 0;
u8  StateSendNum = 0;
u8  EventSendNum = 0;

void TimeParamterInit(void)
{
  u8 i;
  memset(&TimeSlot, 0 ,sizeof(TimeSlot));
  memset(&Clock,0,sizeof(Clock));
  memset(&LastSend,0,sizeof(LastSend));
  for(i=0;i<4;i++)
    { PowerBuff[i] = 0; }
  TimeCommunicatFlag=0;
  TimeSlotMode = SNP_PHR_TYPE_UP_LINE ;
  SysTimeSlot = Sen_UpLine;
  ConfigFlags = 0;
  RfSendFlags = 0;
  //NotScanSyncNum = 0;
  //SignalNum = 0;
  ReSendCnt = 0;
  DebugFlag = 0;
  LastSend.SendNum = 0;
 // ReastOffSecond = REST_AD_DELAY + 30;
  //ReSendNum = 0;
  //SignalState = 1;
   ////////////////////////test///////////////////////////////////////////////////
   P1DIR |= BIT3;
  P1OUT &= ~BIT3;
}

void TimeSlotConfig(void)
{
  u16 temp;
  temp =  TimeSlot.SenTimeSlotNum % MIN_CLCYL_SEN_NUM;
  if(temp == 0)
    { TimeSlot.MinTimeSlot = MIN_CLCYL_SEN_NUM; }
  else
    { TimeSlot.MinTimeSlot = temp; } 
  
   TaccAdd.Firm0ToFirm1 = 12800;
   TaccAdd.Firm1Event = 12800;
   TaccAdd.ToNextEvent = 12800;
   TaccAdd.ReservedWeakUp = 25504;
   TaccAdd.WeakUpDealAck = 12800;
   
   TaccAdd.AssocBusWeakUp = 12704;
   TaccAdd.ReservedSyncWeakUp = 38304;
   TaccAdd.NeighbWeakUpDealAck = 12896;
   TaccAdd.DealAckSyncWeakUp = 12704;  
   TaccAdd.WeakUpSync = 96;
}

void AdTimeClear(void)
{
  TB0CTL |= TBCLR;
  TB0CCR0 = 0x1000;
  /*if( (SystemState == INIT_BASE_LINE) && (AdRestSecond>= REST_AD_DELAY) )
     { TB0CCR0 = 0x100; }
  else
     { TB0CCR0 = 0x1000;}*/
}

void TimerAInit(void)
{
  TA1CTL  = TASSEL_1 + TACLR; //ACLK,， 
  TA1CCR0 =  64;    
  TA1CCR1 = 0x100;
}

void TimerA_RestCount(u16 CountNum)
{
  TA1CTL  |=   TACLR;   
  TA1CCR0 = CountNum;  
  TB0CTL |= TBCLR;
  TB0CCR0 = 0x100;
  //TA1CCR1 = 0xC0 + CountNum;  
}
void TimerAStart(void)
{
TA1CCTL0 |= CCIE;
 TA1CTL &= ~0x30;  
// TA1CTL |= 0x10;
 TA1CTL |= MC1;
}

void TimerAStop(void)
{
  TA1CCTL0 &= ~CCIE;
  TA1CTL &= ~(MC1 + MC0);
}

//u8 testt1 = 0;
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TimerSlot  (void) 
{ 
  //LPM3_EXIT;
  //AdIntrruptOff();
  WDTCTL =  WDT_ARST_1000 ; 
 // LastSystem = SysTimeSlot;
  if(TimeSlotMode == SNP_PHR_TYPE_UP_LINE )
      { 
        ModeUpLineSlot();
      }
   else if( TimeSlotMode == SNP_DOWN_CODE_MODE )
      { ModeDownCode_Slot(); }
   else
    {  
      TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
      SysTimeSlot = Sen_UpLine;
      DownLineConfig();      
    } 
//  AdIntrruptOn();
}

//*****************************************************************************************************
//*****************************************************************************************************8
 //******************************************************************************************************************

//低区间时间槽
 //******************************************************************************************************************


void DownLineConfig(void)
{
  TA1CCR0 += 4000;//7930;   
  AdTimeClear();
  TimeCommunicatFlag &= ~RECIVE_SYNC;
 // TempBaseFlag |= EVENT_GET_ON;
  Clock.DownLineDelay = 0; 
  UplineSendNum = 0;
  Clock.UpLineSecond = 0;
  Clock.DelayUplineScan = STATE_RF_DELAY;
  Clock.msnum = 0;
  OpenRFDelay = 0;
  TimeCommunicatFlag &= ~SEN_ON_LINE;
  TimeCommunicatFlag &= ~STATE_SEND_ON;
  TimeCommunicatFlag &= ~EVENT_SEND_ON;
  TimeCommunicatFlag &= ~CFG_SYNC_ON;
  //CompFlags &= ~WEAK_UP_CFG_SEND;
  SetFlags &= ~TEST_DEMO_ON;
  DebugFlag |= DOWN_LINE_RF;
          ConfigFlags &= ~BUS_SEND_ON;
          ConfigFlags &= ~RECIVE_SEN_CFG;
          DebugFlag &= ~RELEVANCE_BUS_REQUEST_SEND_ON;
          DebugFlag &= ~STATE_VALUE_SEND_ON;
          DebugFlag &= ~SIGNAL_REQUEST_ON;
          DebugFlag &= ~DEBUG_SEND_ON;
         // DebugFlag &= ~SEN_QUERY_ON;
          SetFlags &= ~STATE_TIME_SAVED;
        //  SetFlags &= ~AD_WEAKUP;
        //  SetFlags &= ~DOWN_CODE_CFG;
  ConfigFlags &= ~SEN_UP_LINE;
  NumRx = 0;
  ConfigFlags &= ~DATE_SEND;
  RfParamt.ApID = 0;
  TimeCommunicatFlag &= ~EVENT_SEND;    
 // DebugFlag |= DOWN_LINE_RF;

  SysTimeSlot = Sen_UpLine;
  TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
  //DownLineSecond = 0;
  Clock.msnum = 0;
  RfDisable();  //SaveEventFlash  ;
  if( (SetFlags & EVENT_GENERT) && (!(SetFlags & DOWNLINE_NORM)) )
  {
    SaveEventFlash.Hour = LastEvent.Hour;
    SaveEventFlash.Minute = LastEvent.Minute;
    SaveEventFlash.Second = LastEvent.Second;
    SaveEventFlash.Flag = 0xaa;
    FlashWrite(EVENT_SAVE_ADRESS,(u8 *)&SaveEventFlash,sizeof(SaveEventFlash));
    SetFlags |= EVENT_FLASH_SAVED;   
  }
  if(!(AdMagenticFlags & DOWNLINE_INIT))
  {
    AdMagenticFlags |= DOWNLINE_INIT;
    DownLineNum = 0;
  }
  else
  {
    DownLineNum++;
    if( DownLineNum >= 200 )
       {            
         FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
         FlashParamt.WatchDogRst++;   
         EraseSectorFlashB();                                   
         FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) ); 
         Sys_Soft_Reset();
       }
  }
 RFM98_REST_DOWN();
 delay_us(200);  
 RFM98_REST_UP();
 //RFM98_Config();
// RfDisable();
#if STRING_ON
 UartSendStrings("down line");  
 UartSendStrings("\r\n"); 
#endif
}



void DownLineEvent(void)
{
  TA1CCR0 += 4000;//7930;   
  TimeCommunicatFlag &= ~RECIVE_SYNC; 
  Clock.DownLineDelay = 0;
  Clock.UpLineSecond = 0;
  Clock.DelayUplineScan = STATE_RF_DELAY;
  //Clock.StateSecond = 0;
  //OpenRFDelay = 0;
  TimeCommunicatFlag &= ~SEN_ON_LINE;
  TimeCommunicatFlag &= ~STATE_SEND_ON;
  TimeCommunicatFlag &= ~EVENT_SEND_ON;
  SetFlags &= ~TEST_DEMO_ON;
  //TimeCommunicatFlag &= ~STATE_SEND_ON;
          ConfigFlags &= ~BUS_SEND_ON;
          ConfigFlags &= ~RECIVE_SEN_CFG;
          DebugFlag &= ~RELEVANCE_BUS_REQUEST_SEND_ON;
          DebugFlag &= ~STATE_VALUE_SEND_ON;
          DebugFlag &= ~SIGNAL_REQUEST_ON;
          DebugFlag &= ~DEBUG_SEND_ON;
        //  DebugFlag &= ~SEN_QUERY_ON;
          SetFlags &= ~STATE_TIME_SAVED;
        //  SetFlags &= ~AD_WEAKUP;
        //  SetFlags &= ~DOWN_CODE_CFG;
  ConfigFlags &= ~SEN_UP_LINE;
  NumRx = 0;
  ConfigFlags &= ~DATE_SEND;
  RfParamt.ApID = 0;
  TimeCommunicatFlag &= ~EVENT_SEND;    
  //DebugFlag |= DOWN_LINE_RF;

  SysTimeSlot = Sen_UpLine;
  TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
  //DownLineSecond = 0;
  Clock.msnum = 0;
  RfDisable();  
}
//******************************************************************************************************************

//*****************************************************************************************************

void ReciveUpLineAck(void)
{   
 // u8 i;
         if(TimeCommunicatFlag & RECIVE_ACK)
         { 
             TimeCommunicatFlag &= ~RECIVE_ACK;
             TimeCommunicatFlag &= ~STATE_SEND_ON;
             LED2_OFF();
             if( !(ConfigFlags & TIMESLOT_SAVED) )
             {
               if( pSenID == RfParamt.SenID )
               {
                 // if( ConfigFlags & FLASH_WRITE_ERROR )
                  //  { FlshParamtCfg(); }
                //  else
                  FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
                  FlashParamt.SenTimeSlotNum = pTimeSlot;
                  FlashParamt.ParamtSet = 0xa5;
                  EraseSectorFlashB();
                  CheckNumWrite = FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );  
                  FlashRead(CHECK_NUM_ADDRESS, (u8 *)&CheckNumRead,2);
                  if(CheckNumWrite == CheckNumRead)
                    {
                      ConfigFlags &= ~FLASH_WRITE_ERROR;
                      TimeSlot.SenTimeSlotNum = FlashParamt.SenTimeSlotNum;   
                      TimeSlotConfig();    
                      ConfigFlags |= TIMESLOT_SAVED;      
                    } 
                  else
                    {
                      ConfigFlags |= FLASH_WRITE_ERROR;
                    } 
                  TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
                  DownLineConfig();                      //设置时间槽后掉线（未用） （收到SYNC）
                  TA1CCR0 += 128;  
                 // UartSendStrings("Save Timeslot");  
                 // UartSendStrings("\r\n"); 
                 }             
             }
            else
             {      
                 TimeCommunicatFlag |= SEN_ON_LINE;
                 RfParamt.ApID = RfParamt.pApID;
                 TimeSlot.UplineTime = 0;
                 UplineNum = 0;
                 ConfigFlags &= ~SET_PUMP;                       
                 TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
                RfSendFlags |= UP_LINE_MODE;
#if STRING_ON                
                UartSendStrings("Up line OK");  
                UartSendStrings("\r\n"); 
#endif                
           } 
         }
         else           
         {   
            TimeSlotUpdate();
#if STRING_ON          
            UartSendStrings("no ack");  
            UartSendStrings("\r\n");  
#endif                     
         }
}

//******************************************************************************************************************************
 //*************************************************************************************************8
//*************************************************************************************************8
void ModeDownCode_Slot(void)
{
  switch (SysTimeSlot)
  {
    case Sync_Frm0:                 //0 时间槽 0
      {          
        TA1CCR0 += 576;//TaccAdd.Firm0ToFirm1;  
        SysTimeSlot =  Sync_Frm1;   
        
      }
    break;  
    case Sync_Frm1:   
        {
#if STRING_ON
          UartSendStrings("CFirm1:");  
          UartSendNumber(TimeSlot.RcvSyncNum);
#endif
          TimeSlot.RcvSyncNum++;
          if( TimeSlot.RcvSyncNum >= 384)
          {
            TimeSlot.RcvSyncNum = 0; 
            memset(&CodeBuffer, 0 ,sizeof(CodeBuffer));
              delay_ms(500);
             delay_ms(500);
             delay_ms(500);  
            Sys_Soft_Reset();
          }        
          else
          {
            TA1CCR0 += 448;//TaccAdd.Firm1Event;
            SysTimeSlot = DownCode_Firm1;
            RFM98_LoRaEntryRx(sizeof(SNP_UF_DOWN_CODE_PACKET_t));    
          }
        }
      break;  
      case DownCode_Firm1:
       {
         TA1CCR0 += 2048;
         SysTimeSlot = DownCode_Firm2; 
       }
      break;
      case DownCode_Firm2:
       {
         TA1CCR0 += 512;
         SysTimeSlot = DownCode_Firm3;
       }
      break;
      case DownCode_Firm3:
       {
         P1OUT &= ~BIT3;
           TA1CCR0 += 1024;//1536;
           SysTimeSlot = DownCode_Firm4; 
           SaveCode();
       }
      break;
      case DownCode_Firm4:
       {
          TA1CCR0 += 512;//1024;
          SysTimeSlot = Sync_Frm0; 
          RFM98_LoRaEntryRx(21);  
       }
      break;
      case DownSysScan:
        {
          TA1CCR0 += 14420; //500ms
          SysTimeSlot = DownSysScan;
          TimeCommunicatFlag |= DOWN_CODE_DOWN_LINE;
          RFM98_LoRaEntryRx(21); 
          TimeSlot.RcvSyncNum++;
          if( TimeSlot.RcvSyncNum >= 120)
            {
              TimeSlot.RcvSyncNum = 0;  
                delay_ms(500);
             delay_ms(500);
             delay_ms(500);  
              Sys_Soft_Reset();
            }
          // UartSendStrings("downScan sync");  
         //  UartSendStrings("\r\n");  
        }
      break;
      default:
        {
//  UartSendStrings("downSan err rest");  
//UartSendStrings("\r\n");           
          Sys_Soft_Reset();
        }
      break;
  }
}

 //*************************************************************************************************8
//*************************************************************************************************8
void SaveCode(void)
{
         if( TimeCommunicatFlag & DOWN_CODE_DOWN_LINE )
          {
               RFM98_LoRaEntryTx(sizeof(UplinePacket));
               UplinePacket.sPhr.uiFcf = FCF_DEF;
               UplinePacket.sPhr.uiDevId = RfParamt.SenID; 
               //UplinePacket.TimeSlot = TimeSlot.SenTimeSlotNum;
              // UplinePacket.sPhr.ucSerNr++;             
               UplinePacket.sPhr.uiType = SNP_DOWN_CODE_UP_LINE; 
             //  UartSendStrings("SaveCode up line send");  
            //   UartSendStrings("\r\n"); 
               RfTxPacket((u8 *)&UplinePacket, sizeof(UplinePacket));
           }
         else if(DownCodeFlag == 3)
         {
           RFM98_LoRaEntryTx(sizeof(UfAckPacket));
           UfAckPacket.SavedBuffNum = CodeBuffer.LastReciveNum;
           UfAckPacket.Type = 0xAA;
           UfAckPacket.sPhr.uiFcf = FCF_DEF;
           UfAckPacket.sPhr.uiDevId = RfParamt.SenID;
           UfAckPacket.sPhr.uiType = SNP_PACKET_TYPE_UF_ACK;
           RfTxPacket((u8 *)&UfAckPacket, sizeof(UfAckPacket));  
           DownCodeFlag = 0;
             FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
             FlashParamt.RestNum = 0xff;   
             EraseSectorFlashB();                                   
             FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) ); 
    // UartSendStrings("recive end");  
 //UartSendStrings("\r\n");        
            delay_ms(500);
             delay_ms(500);
             delay_ms(500);  
             
           Sys_Soft_Reset(); 
         }
         else if( (DownCodeFlag == 1) || (DownCodeFlag == 2) )
         {
            RFM98_LoRaEntryTx(sizeof(UfAckPacket));
           UfAckPacket.Type = 0x55;
           UfAckPacket.SavedBuffNum = CodeBuffer.LastReciveNum;
           UfAckPacket.sPhr.uiFcf = FCF_DEF;
           UfAckPacket.sPhr.uiDevId = RfParamt.SenID;
           UfAckPacket.sPhr.uiType = SNP_PACKET_TYPE_UF_ACK;
           RfTxPacket((u8 *)&UfAckPacket, sizeof(UfAckPacket));   
           DownCodeFlag = 0xff;
        //   UartSendStrings("send ack:");  
          // UartSendNumber(UfAckPacket.SavedBuffNum);
// UartSendStrings("\r\n");
         }
        
}

//*************************************************************************************************
//u8 TestSecond;
//u8 testget = 0;
void ModeUpLineSlot(void)
{
 // u16 AdTemp1;
  u8 i;
  u8 temp1;
  u8 temp2;
  TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
  switch(SysTimeSlot)
  {
    case  Sync_Frm0:
    {        
          //Clock.Mesc = 0;
          AdTimeClear();
          Clock.UpLineSecond += 4;   
          CompFlags |= UP_SECOND_ADD;
          if(SetFlags & DOWN_CODE_CFG)
            { AckSendNum++;  }
          if(RestSecond < 120)
            { RestSecond += 4; }
         if( (SetFlags & DOWN_CODE_CFG) && (AckSendNum > 3) )
         {
           SetFlags &= ~DOWN_CODE_CFG;
           AckSendNum = 0;
           TA1CCR0 += 256;
           gb_RateBuf_Addr=7;
           gb_BandBuf_Addr=9;
           SysTimeSlot = DownSysScan;
           TimeSlotMode = SNP_DOWN_CODE_MODE;   
           FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
           FlashParamt.BaseLineZ = AxisZ1Pam.BaseLine;
           FlashParamt.BaseLineX = AxisX1Pam.BaseLine;
           FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );
           memset(&CodeBuffer, 0 ,sizeof(CodeBuffer));
           memset(&CodeBuffer.Buff[0],0xff,512);           
         }
        else if( (Clock.UpLineSecond >= 60) || (SingleFlag & SET_BASE_COMD) )
         { 
           if(SingleFlag & SET_BASE_COMD)
              { SingleFlag &= ~SET_BASE_COMD; }
           Clock.UpLineSecond = 0;
           TA1CCR0 += 524;    //16ms
           memset(&Clock,0,sizeof(Clock));   
           SetFlags &= ~AD_WEAKUP;   
           TimeSlot.Second += 3;
           TimeClockUpdate();
           DownLineConfig();
         }        
         else
         {
           TA1CCR0 += TaccAdd.Firm0ToFirm1;
           SysTimeSlot =  Sync_Frm1; 
         }
     }
    break;
    case Sync_Frm1:
    {
      P1OUT &= ~BIT3;
#if STRING_ON
      UartSendStrings("F1:"); 
       UartSendNumber(Clock.UpLineSecond);
#endif
       RfDisable();     
       CompFlags &= ~UP_SECOND_ADD;
       TA1CCR0 += TaccAdd.Firm1Event;  
       SysTimeSlot = Check_Event1;
       if( (TimeSlot.SenTimeSlotNum<1) || (TimeSlot.SenTimeSlotNum>10) )
         { 
           TimeSlot.SenTimeSlotNum = 1;
           TimeSlotConfig();
         }
       if( (TimeCommunicatFlag & RECIVE_SYNC) || (TimeCommunicatFlag & DEMO_SYNC) || (DebugFlag & RF_DEMO_SYNC) )
           {          
             TimeSlot.ReciveSyncRepeat = 0;    
           }      
       else
          {
             TimeSlot.Second += 3;
             TimeClockUpdate();
             TimeSlot.ReciveSyncRepeat++;  
             if(TimeSlot.ReciveSyncRepeat >= 8)    //5秒  
               {
                 TimeSlot.ReciveSyncRepeat = 0;
                 DownLineConfig();                  //上线10次掉线（排除）  （上线无SYNC 排除）
               }     
          }
       if( (DebugFlag & RF_DEMO_SYNC) || (DebugFlag & RF_ALL_SYNC_ON) )
       {
         if(Clock.UpLineSecond >= 16)
         {
           Clock.UpLineSecond = 0;
           TA1CCR0 += 524;    //16ms
           memset(&Clock,0,sizeof(Clock));   
           SetFlags &= ~AD_WEAKUP;         
           DownLineConfig();
         }
       }
       if( (Clock.UpLineSecond >= 60) || (SingleFlag & SET_BASE_COMD) )
       {
           if(SingleFlag & SET_BASE_COMD)
              { SingleFlag &= ~SET_BASE_COMD; }
           Clock.UpLineSecond = 0;
           TA1CCR0 += 524;    //16ms
           memset(&Clock,0,sizeof(Clock));   
           SetFlags &= ~AD_WEAKUP;   
           TimeSlot.Second += 3;
           TimeClockUpdate();
           DownLineConfig();
       }
    }
    break;
    case Check_Event1:
    case Check_Event2:
    case Check_Event3:
    case Check_Event4:
    case Check_Event5:
      {          
        AdTimeClear();
       // UartSendStrings("RunSlot:"); 
 //UartSendNumber(TimeSlot.TimeSlotNum );
 //UartSendNumber(TimeSlot.SenTimeSlotNum );
        ConfigFlags &= ~DATE_SEND;
        if( (TimeSlot.TimeSlotNum == TimeSlot.SenTimeSlotNum) && (TimeCommunicatFlag & RECIVE_SYNC) )
        {        
               TimeCommunicatFlag &=~ RECIVE_SYNC;
               //Clock.RandomNUM++; 
               if(ConfigFlags & RECIVE_SEN_CFG)// || (SetFlags & CFG_RESEND) )
                 {
                   RFM98_LoRaEntryTx(sizeof(SenAckPacket));
                   ConfigFlags &= ~RECIVE_SEN_CFG;
                   SenAckPacket.sPhr.uiFcf = FCF_DEF;
                   SenAckPacket.sPhr.uiDevId = RfParamt.SenID;
                   SenAckPacket.sPhr.uiType = SNP_CFG_SEN_ACK;
                   RfTxPacket((u8 *)&SenAckPacket, sizeof(SenAckPacket));
                   if(SenAckPacket.uiCmd == SNP_CMD_SET_BASELINE)
                     { SingleFlag |= SET_BASE_COMD; }
                   SenAckPacket.uiCmd &= 0x00ff;
                   ChangLastID = 0;
                   if(SetFlags & NEW_PUMP_GET)
                   {
                     SetFlags &= ~NEW_PUMP_GET;
                     SetFlags |= PUMP_CFG_SEND;
                   }
               if( (SenAckPacket.uiCmd == SNP_CMD_ENTER_UF) && (DebugFlag & CODE_ADRESS_MATE) )
                {  
                  SetFlags |= DOWN_CODE_CFG; 
                  AckSendNum = 0;
                  Clock.UpLineSecond = 0;
                }
              // UartSendStrings("Cfg ACK send"); 
          //  UartSendStrings("\r\n");
                  }  
             else if( (TimeCommunicatFlag & EVENT_SEND_ON))  //发送事件包                        
                  {    
#if LED_TEST_ON
     LED2_ON();
#endif
                    RFM98_LoRaEntryTx(sizeof(EventPacket)); 
                    CompFlags &= ~EVENT_TIME_ERROR;
                    if( !(CompFlags & DAY_UPDATE) )
                    {
                       temp1 = EventBuff.Event[EventBuff.SendPtr].Hour & 0x7f;
                       temp2 = LastSend.Hour & 0x7f;                  
                       if( temp1 < temp2 )
                        {   CompFlags |= EVENT_TIME_ERROR;   }
                       else if(temp1 == temp2)
                        {
                          temp1 = EventBuff.Event[EventBuff.SendPtr].Minute;
                          temp2 = LastSend.Minute;
                          if( temp1 < temp2 )
                           {  CompFlags |= EVENT_TIME_ERROR;  }
                          else if( temp1 == temp2 )
                          {
                            temp1 = EventBuff.Event[EventBuff.SendPtr].Second & 0x7f;
                            temp2 = LastSend.Second & 0x7f;
                            if( temp1 < temp2 )
                              {   CompFlags |= EVENT_TIME_ERROR;   }
                          }
                        }
                    }
                    temp1 = EventBuff.Event[EventBuff.SendPtr].Hour & 0x7f;
                    temp2 = EventBuff.Event[EventBuff.SendPtr].Minute;
                    if( ((temp1==0) && (temp2 < 3)) || (CompFlags & EVENT_TIME_ERROR) )
                    {
                       EventBuff.SavePtr = EventBuff.SendPtr;
                       EventBuff.Event[EventBuff.SavePtr].Hour = TimeSlot.Hour | 0x80;
                       EventBuff.Event[EventBuff.SavePtr].Minute = TimeSlot.Minute;
                       EventBuff.Event[EventBuff.SavePtr].Second &= 0x80;
                       EventBuff.Event[EventBuff.SavePtr].Second |= TimeSlot.Second;
                       LastEvent.Hour = EventBuff.Event[EventBuff.SavePtr].Hour;
                       LastEvent.Minute = EventBuff.Event[EventBuff.SavePtr].Minute;
                       LastEvent.Second = EventBuff.Event[EventBuff.SavePtr].Second;
                       EventBuff.SavePtr++;
                       if( EventBuff.SavePtr >= SAVE_BUFF_NUM )
                         { EventBuff.SavePtr = 0; }           
                    }
                    EventPacket.Hour = EventBuff.Event[EventBuff.SendPtr].Hour & 0x7f;  //事件由缓存取出赋予发送包发送
                    EventPacket.Minute = EventBuff.Event[EventBuff.SendPtr].Minute;
                    EventPacket.Second = EventBuff.Event[EventBuff.SendPtr].Second;
                    if( (!(EventPacket.Second & 0x80)) && (TempBaseFlag & EVENT_ON_GENERT) )
                    {
                      temp1 = LastEvent.Hour & 0x7f;
                      temp2 = LastEvent.Second & 0x7f;
                      if( (temp1 == EventPacket.Hour)               &&
                          (LastEvent.Minute == EventPacket.Minute)  &&
                          (temp2 == EventPacket.Second)   )
                      {
                        EventPacket.Second |= 0x80;
                        EventBuff.Event[EventBuff.SendPtr].Second |= 0x80;   
                        LastEvent.Second |= 0x80;
                      }
                    }
                    EventPacket.sPhr.uiFcf = FCF_DEF;
                    EventPacket.sPhr.uiDevId = RfParamt.SenID;  
                    EventPacket.sPhr.SlotNum = TimeSlot.SenTimeSlotNum;
                    EventPacket.sPhr.uiType = SNP_PACKET_TYPE_SEN_A;                     
                    RfTxPacket((u8 *)&EventPacket, sizeof(EventPacket));    ////事件包发送
                    if( (LastSend.Hour == EventPacket.Hour) && (LastSend.Minute == EventPacket.Minute) && (LastSend.Second == EventPacket.Second) )
                       {                                             
                           if( ReSendNumE < 40 )
                              { ReSendNumE++;  }
                           else                        
                              { 
                                RfSendFlags &= ~CONNECTED_AP; 
                                ReportTime = REPORT_SEND_TIME_3;
                                PumpTbNum = 0;
                              }                            
                       }
                    if( (LastSend.Hour != EventPacket.Hour)     || 
                        (LastSend.Minute != EventPacket.Minute) ||
                        (LastSend.Second != EventPacket.Second)  )
                    {
                      if( (LastSend.Second & 0x80) && (EventPacket.Second & 0x80) )
                         { 
                           OnSedNum++;
                           OffSendNum = 0;
                         }
                      else if( (!(LastSend.Second & 0x80)) && (!(EventPacket.Second & 0x80)) )
                        {
                          OffSendNum++;
                          OnSedNum = 0; 
                        }
                      else
                        {
                          OnSedNum = 0;
                          OffSendNum = 0;       
                        }
                      if( (OnSedNum>=3) || (OffSendNum>=4) )
                       {  Sys_Soft_Reset();  }     
                    }
                    LastSend.Hour = EventPacket.Hour;
                    LastSend.Minute = EventPacket.Minute;
                    LastSend.Second = EventPacket.Second;
                    if( (PslotNum != TimeSlot.SenTimeSlotNum) && (RfSendFlags & CONNECTED_AP) )
                      { ReSendNum++; }
                    PslotNum = TimeSlot.SenTimeSlotNum;
                    TimeCommunicatFlag |= EVENT_SEND;
                    CompFlags &= ~DAY_UPDATE;
                    SetFlags &= ~UPLINE_SEND;
                    RfSendFlags &= ~EVENT_SEND_NEED; 
                    ConfigFlags &= ~BUS_SEND_ON;
                    EventSendNum++;                   

#if STRING_ON                    
                    UartSendStrings("E_Send:"); 
                    UartSendStrings("\r\n");
               
             if(LastSend.Second & 0x80)
               {
                 UartSendStrings("ON:"); 
                 NewLineOFF = 1;
                 UartSendNumber(LastSend.Hour & 0x7f);
                 UartSendStrings(":");
                 NewLineOFF = 1;
                 UartSendNumber(LastSend.Minute );
                 UartSendStrings(":");
                 // NewLineOFF = 1;
                  UartSendNumber(LastSend.Second & 0x7f );
               }
               else
               {
                 UartSendStrings("OFF:"); 
                 NewLineOFF = 1;
                 UartSendNumber(LastSend.Hour & 0x7f);
                 UartSendStrings(":");
                 NewLineOFF = 1;
                 UartSendNumber(LastSend.Minute );
                 UartSendStrings(":");
                  //NewLineOFF = 1;
                  UartSendNumber(LastSend.Second & 0x7f );
               }
#endif             
                  } 
             else if( TimeCommunicatFlag & STATE_SEND_ON )  //发送心跳包
                 {
                   RFM98_LoRaEntryTx(sizeof(UplinePacket));
                   UplinePacket.sPhr.uiFcf = FCF_DEF;
                   UplinePacket.sPhr.uiDevId = RfParamt.SenID; 
                   //UplinePacket.TimeSlot = TimeSlot.SenTimeSlotNum;
                   UplinePacket.PowerInt &= 0x0f;
                   UplinePacket.PowerInt |= gb_PowerBuf_Addr<<4;
                   if( RfSendFlags & CONNECTED_AP )
                     {  UplinePacket.PowerInt |= 0x80;  }
                   else
                     {  UplinePacket.PowerInt &= ~0x80; }
                   UplinePacket.VersionLow = VERSION_LOW;
                   UplinePacket.VersionHigh = VERSION_HIGH;
                   UplinePacket.CodeAdress = CodeAdress;
                   UplinePacket.AdValueZ = BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ;
                   UplinePacket.AdValueX = BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX;
                   UplinePacket.BaseZ =  AxisZ1Pam.BaseLine;
                   UplinePacket.BaseX = AxisX1Pam.BaseLine;
                   UplinePacket.ResendNum = ReSendNum;
                   UplinePacket.BaseAverageNum = FlashParamt.RestNum;//BaseAverageNum;
                   UplinePacket.BaseChgNum = DetectValue;
                   UplinePacket.OnEventChgNum = BaseLineBuff.BaseNum;                  
                   UplinePacket.sPhr.SlotNum = TimeSlot.SenTimeSlotNum;                        
                   UplinePacket.sPhr.uiType =  SNP_PHR_TYPE_UP_LINE;
                   StateSendNum++;                
                   
#if STRING_ON                   
                   UartSendStrings("Up line send");  
                   UartSendStrings("\r\n");    
#endif                   
                    if(FlashParamt.ResetFlag == 1)    
                       {   UplinePacket.sPhr.uiType |= 0x08;  }
               
                   RfTxPacket((u8 *)&UplinePacket, sizeof(UplinePacket));  //心跳包发送
                   TimeCommunicatFlag &= ~RECIVE_ACK; 
                   TimeCommunicatFlag |= EVENT_SEND;
                   SetFlags |= UPLINE_SEND;
                   if( (PslotNum != TimeSlot.SenTimeSlotNum) && (RfSendFlags & CONNECTED_AP) )
                      { ReSendNum++; }
                   PslotNum = TimeSlot.SenTimeSlotNum;
                   if( !(RfSendFlags & CONNECTED_AP) )
                   {
                     UplineSendNum++;
                     if( UplineSendNum >= 4 )
                        { 
                          UplineSendNum = 0;
                          DebugFlag |= PUMP_CHG_TEMP;
                          Clock.UpLineSecond = 60;
                          RestSecond = 115;                                                                                      
                        }
                   }
#if LED_TEST_ON  
    LED2_ON();
#endif                   
                }
        }
        else if((CompFlags & WEAK_UP_CFG_SEND) && (SetFlags & AD_WEAKUP) )
        {
                   CompFlags &= ~WEAK_UP_CFG_SEND;
                   RFM98_LoRaEntryTx(sizeof(UplinePacket));
                   UplinePacket.sPhr.uiFcf = FCF_DEF;
                   UplinePacket.sPhr.uiDevId = RfParamt.SenID; 
                   //UplinePacket.TimeSlot = TimeSlot.SenTimeSlotNum;
                   UplinePacket.PowerInt &= 0x0f;
                   UplinePacket.PowerInt |= gb_PowerBuf_Addr<<4;
                   if( RfSendFlags & CONNECTED_AP )
                     {  UplinePacket.PowerInt |= 0x80;  }
                   else
                     {  UplinePacket.PowerInt &= ~0x80; }
                   UplinePacket.VersionLow = VERSION_LOW;
                   UplinePacket.VersionHigh = VERSION_HIGH;
                   UplinePacket.CodeAdress = CodeAdress;
                   UplinePacket.AdValueZ = BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ;
                   UplinePacket.AdValueX = BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX;
                   UplinePacket.BaseZ =  AxisZ1Pam.BaseLine;
                   UplinePacket.BaseX = AxisX1Pam.BaseLine;
                   UplinePacket.ResendNum = ReSendNum;
                   UplinePacket.BaseAverageNum = FlashParamt.RestNum;
                   UplinePacket.BaseChgNum = DetectValue;
                   UplinePacket.OnEventChgNum = BaseLineBuff.BaseNum;                  
                   UplinePacket.sPhr.SlotNum = TimeSlot.SenTimeSlotNum;                        
                   UplinePacket.sPhr.uiType =  SNP_PHR_TYPE_UP_LINE;
                   RfTxPacket((u8 *)&UplinePacket, sizeof(UplinePacket));                   
        }
        else if( TimeCommunicatFlag & DEMO_SYNC  )
        {
          TimeCommunicatFlag &= ~DEMO_SYNC;;
          if( SetFlags & SER_REST_COMD )
          {
            SetFlags &= ~SER_REST_COMD;
            SensorRest();
            AdValuePacket.Rest = 0xaa;
          }
          else
          { AdValuePacket.Rest = 0; }
          RFM98_LoRaEntryTx(sizeof(AdValuePacket));
          AdValuePacket.sPhr.uiFcf = FCF_DEF;
          AdValuePacket.sPhr.SlotNum = TimeSlot.SenTimeSlotNum;
          AdValuePacket.sPhr.uiType = AD_TEST_DEMO;
          AdValuePacket.sPhr.uiDevId = RfParamt.SenID; 
          AdValuePacket.AdValueZ = Magnetic.AxisZ1;
          AdValuePacket.AdValueX = Magnetic.AxisX1;
          RfTxPacket((u8 *)&AdValuePacket, sizeof(AdValuePacket));   
     // UartSendStrings("AD value send");  
// UartSendStrings("\r\n");    
        }
        else if( (DebugFlag & RF_DEMO_SYNC) || (DebugFlag & RF_ALL_SYNC_ON) )//
        {
               DebugFlag &= ~RF_DEMO_SYNC;  
               DebugFlag &= ~RF_ALL_SYNC_ON;
               DebugFlag |= TEST_SYNC_MODE;
               RFM98_LoRaEntryTx(sizeof(UplinePacket));
               UplinePacket.sPhr.uiFcf = FCF_DEF;
               UplinePacket.sPhr.uiDevId = RfParamt.SenID; 
               //UplinePacket.TimeSlot = TimeSlot.SenTimeSlotNum;
               UplinePacket.VersionLow = VERSION_LOW;
               UplinePacket.VersionHigh = VERSION_HIGH;
               UplinePacket.CodeAdress = CodeAdress;
               UplinePacket.sPhr.SlotNum = TimeSlot.SenTimeSlotNum;    
               UplinePacket.sPhr.uiType =  SNP_PHR_TYPE_UP_LINE;
               RfTxPacket((u8 *)&UplinePacket, sizeof(UplinePacket));
             //  UartSendStrings("Rf upline send"); 
  //UartSendStrings("\r\n");        
        }
        TA1CCR0 += TaccAdd.ToNextEvent;
        SysTimeSlot++; 
        TimeSlot.TimeSlotNum++;
        if( TimeSlot.TimeSlotNum > TimeSlot.AllTimeSlotNum )
         { TimeSlot.TimeSlotNum = 1; }
        if( ( (StateSendNum >= 5) && (NewBaseFlag & STATE_SYNC_ON) ) || (EventSendNum >= 50) )
           {                    
              StateSendNum = 0;
              EventSendNum = 0;
              memset(&Clock,0,sizeof(Clock));   
              SetFlags &= ~AD_WEAKUP;   
              DownLineConfig();
           } 
        NewBaseFlag &= ~STATE_SYNC_ON;
      }
    break;
    case Event_Reserved:
      {       
          AdTimeClear();
          ConfigFlags &= ~DATE_SEND;     
          TA1CCR0 += TaccAdd.ReservedWeakUp;     
          SysTimeSlot = Ack_WeakUp;         
      }
    break;  
    case Ack_WeakUp:
      {
        AdTimeClear();
        TA1CCR0 += TaccAdd.WeakUpDealAck;
        SysTimeSlot = Sync_WeakUp;
        if( TimeCommunicatFlag & EVENT_SEND )// || (DebugFlag & RF_TEST_SEND))
         {
           RFM98_LoRaEntryRx(sizeof(SNP_AP_ACK_PACKET_t)); 
         }
      }
    break;
    case Sync_WeakUp:
      {
        //ED1_OFF();
        AdTimeClear();
        TA1CCR0 += TaccAdd.WeakUpSync;  
        SysTimeSlot = Sync_Frm0; 
       // CompFlags &= ~WEAK_UP_CFG_SEND;
        if( TimeCommunicatFlag & EVENT_SEND )//(SetFlags & UPLINE_SEND)//
          { 
            TimeCommunicatFlag &= ~EVENT_SEND;
            if( !(SetFlags & UPLINE_SEND) )
            {
              if(TimeCommunicatFlag & RECIVE_ACK )
               {
                   LED2_OFF();
                  TimeCommunicatFlag &= ~RECIVE_ACK;  
                  TimeCommunicatFlag &= ~EVENT_SEND_ON;
                  SetFlags &= ~EVENT_GENERT;
                  TempBaseFlag &= ~EVENT_ON_GENERT;
                  LastSend.SendNum++;
                  EventBuff.Event[EventBuff.SendPtr].Hour &= ~0x80;
                 /* if( LastSend.Second & 0x80 )
                  {
                    OnSedNum++;
                    OffSendNum = 0;
                  }
                  else
                  {
                    OffSendNum++;
                    OnSedNum = 0;
                  }*/
                  if(SetFlags & EVENT_FLASH_SAVED)
                  {
                    SaveEventFlash.Hour = 0;
                    SaveEventFlash.Minute = 0;
                    SaveEventFlash.Second = 0;
                    SaveEventFlash.Flag = 0;
                    FlashWrite(EVENT_SAVE_ADRESS,(u8 *)&SaveEventFlash,sizeof(SaveEventFlash));
                    SetFlags &= ~EVENT_FLASH_SAVED; 
                    if( OnSedNum > 0)
                      { OnSedNum--; }
                    if( OffSendNum > 0 )
                      { OffSendNum--; }                   
                  }
                              
                  for(i=0;i<BUFF_NUM;i++)
                  {
                    if( (LastSend.Hour == BusEvent.BusNum[i].Hour)     &&
                        (LastSend.Minute == BusEvent.BusNum[i].Minute) &&
                        (LastSend.Second == BusEvent.BusNum[i].Second)  )
                       { BusEvent.BusNum[i].Day |= 0x80; }
                  }
                  if( EventPacket.Second & 0x80 )
                    { SingleFlag |= LAST_EVENT_ON; }
                  else
                    { SingleFlag &= ~LAST_EVENT_ON; }
#if STRING_ON                  
                   UartSendStrings(" ack");  
                       UartSendStrings("\r\n"); 
#endif                       
               }
               else
               {
                 //LastSend.ReSendNum++;
                 TimeSlotUpdate();   
#if STRING_ON                 
                  UartSendStrings("no ack");  
                  UartSendStrings("\r\n"); 
#endif                    
               }
            }
            else
            {
              SetFlags &= ~UPLINE_SEND;
              ReciveUpLineAck(); 
            }
          }
        RFM98_LoRaEntryRx(sizeof(SNP_SYNC_PACKET_t)); 
        if( ((TimeCommunicatFlag & EVENT_SEND_ON) == 0)   &&
            ((TimeCommunicatFlag & STATE_SEND_ON) == 0)   &&
            ((ConfigFlags & CFG_BOX_SYNC) == 0)           &&
            ((SetFlags & DOWN_CODE_CFG) == 0)             &&
            ((DebugFlag & TEST_SYNC_MODE) == 0)           &&
            ((TimeCommunicatFlag & CFG_SYNC_ON) == 0)    )                      
        {  
          SetFlags |= DOWNLINE_NORM;
          TimeSlot.Second += 3;
          TimeClockUpdate();
          DownLineConfig();   
          SetFlags &= ~DOWNLINE_NORM;
          DebugFlag &= ~TEST_SYNC_MODE;
        }
      }
    break;  
    case  Sen_UpLine:
      {        
        TA1CCR0 += 16384;//500ms      
        SysTimeSlot = Sen_UpLine;
        Clock.msnum++;
        DownLineNum = 0;
        ConfigFlags &= ~DATE_SEND;
        if(Clock.msnum >= 2)   //1080ms
        {
          Clock.msnum = 0;
          Clock.StateSecond++;
          TimeClockUpdate();
          SenRestSecond++;
          if( SenRestSecond >= AD_REST_DELAY )
          {
            SenRestSecond = 0;
            SensorRest();
          }
          if(ReastOffSecond < REST_OFF_DELAY)
          {
            ReastOffSecond++;
            if( (ReastOffSecond >= REST_OFF_DELAY) && (SystemState == ON_BASE_LINE) )
               { SingleFlag |= REST_OFF_SEND; }
          }
          if(AdRestSecond < REST_AD_DELAY)
             { AdRestSecond++; }
          if( SetFlags & NEW_PUMP_SAVED )
          {
            SetFlags &= ~NEW_PUMP_SAVED;
            TimeCommunicatFlag |= STATE_SEND_ON;
            ConfigFlags |= SEN_UP_LINE;   
            Clock.DelayUplineScan = STATE_RF_DELAY;   
            // UartSendStrings("pump upline"); 
 // UartSendStrings("\r\n"); 
          }  
          if(RestSecond < 120)  // 120
            {
               RestSecond++;
               if(DebugFlag & PUMP_CHG_TEMP)
                 { RestSecond = 120; }
               TimeSlot.ReportMinute = ReportTime -1 ; 
               if(TimeSlot.ReportSecond < 50)
                 { TimeSlot.ReportSecond = 50; }     
       //    UartSendStrings("RestSecond:"); 
  //UartSendNumber(RestSecond);    
            }
        }
       
#if UPLINE_TEST 
 TimeSlot.ReportMinute = ReportTime -1 ; 
 if(TimeSlot.ReportSecond < 50)
 { TimeSlot.ReportSecond = 50; } 
#endif 
        if( (TimeSlot.Hour == 0) && (TimeSlot.Minute == 0) && (AdRestSecond >= REST_AD_DELAY) )
           {
             TimeSlot.ReportMinute = ReportTime -1 ; 
             if(TimeSlot.ReportSecond < 50)
                { TimeSlot.ReportSecond = 50; }         
           }

          ScanRFSet(); 
        if( ConfigFlags & SEN_UP_LINE )// && (SingleFlag & BASE_LINE_ON) )//&& (TimeCommunicatFlag & SYS_WEAKE_UP) )
        {
           //testget = 1;
            WDTCTL =  WDT_ARST_1000 ; 
            AdMagenticFlags &= ~DOWNLINE_INIT;
            TempBaseFlag &= ~EVENT_GET_ON;
            Clock.UpLineSecond = 0;
            UplineSendNum = 0;           
            RFM98_SPI_Init(); 
            NumRx++;
            if(NumRx < 2)
              { 
                RFM98_LoRaEntryRx(19);
                StateSendNum = 0;
                EventSendNum = 0;
                NewBaseFlag &= ~STATE_SYNC_ON;
              }
            else if(NumRx>STATE_RF_DELAY)
             { NumRx = 0; }
            if( !(SetFlags & POWER_GET_END) )
            {
              if( !(RfSendFlags & POWER_AD_REF_ON) )
                 {              
                   AD_POWER_GET_ON(); 
                   PowerAd = GetPowerAD();                 
                   RfSendFlags |= POWER_AD_REF_ON; 
                 }
               else 
                {
                  RefAd = GetRefAD(); 
                  RfSendFlags &= ~POWER_AD_REF_ON;
                  SetFlags |= POWER_GET_END;
                  AD_POWER_GET_OFF();
                  AdPowerTemp = POWER_AD_REF * PowerAd;
                  AdPowerTemp /= RefAd;
                  if( AdPowerTemp > 0 )
                  {
                    if(PowerBuff[0] == 0)
                     {
                       for(i=0;i<4;i++)
                         { PowerBuff[i] = AdPowerTemp; }
                     }
                     PowerBuff[PowerBuffPtr++] = AdPowerTemp;
                     if(PowerBuffPtr >= 4)
                       { PowerBuffPtr = 0; }  
                     AdPowerTemp = 0;
                     for(i=0;i<4;i++)
                      { AdPowerTemp += PowerBuff[i]; }                  
                     AdPowerTemp >>= 2;
                    UplinePacket.PowerInt = AdPowerTemp / 100;
                    UplinePacket.PowerFloat = AdPowerTemp % 100;  
                  }
                }
            }
            if( (Clock.DownLineDelay >= Clock.DelayUplineScan) || (ConfigFlags & SPI_ERROR) || (DebugFlag & PUMP_CHG_TEMP) ) 
            {        
              ConfigFlags &= ~SEN_UP_LINE;
              SetFlags &= ~AD_WEAKUP;
              NumRx = 0;
              RfSendFlags &= ~UP_LINE_MODE;
              TimeCommunicatFlag &= ~STATE_SEND_ON;  
              SetFlags &= ~STATE_TIME_SAVED;
              
              if( Clock.DelayUplineScan == EVENT_RF_DELAY)  //1分钟
                { 
                  RfSendFlags &= ~CONNECTED_AP;   
                  ReSendNum = 0;
                  BaseAverageNum = 0;
                  //OnBaseChangeNum = 0;
                  TimeCommunicatFlag &= ~EVENT_SEND_ON;
                  DebugFlag &= ~RELEVANCE_BUS_REQUEST_SEND_ON;
                  DebugFlag &= ~STATE_VALUE_SEND_ON;
                  DebugFlag &= ~SIGNAL_REQUEST_ON;
                  DebugFlag &= ~DEBUG_SEND_ON;
                  //DebugFlag &= ~SEN_QUERY_ON;
                  DebugFlag &= ~RE_SCAN_SYNC;
                  ReportTime = REPORT_SEND_TIME_3;
                  PumpTbNum = 0;
                  //BaseAutoSet = ON;
                  for(i=0;i<BUFF_NUM;i++)
                    { BusEvent.BusNum[i].Day |= 0x80; }
                }
              else if( ((Clock.DelayUplineScan == STATE_RF_DELAY) || (DebugFlag & PUMP_CHG_TEMP)) && (RestSecond >= 120) )               
               {     
                 DebugFlag &= ~PUMP_CHG_TEMP;
                 if( RfSendFlags & CONNECTED_AP )
                 {
                   DebugFlag |= RE_SCAN_SYNC;
                   TimeSlot.ReportMinute = ReportTime -1 ; 
                   if(TimeSlot.ReportSecond < 50)
                      { TimeSlot.ReportSecond = 50; }    
                 }
                 else
                 {
                   if( PumpTbNum < 10 )
                   {
                     PumpHigh = PumpTb1[PumpTbNum]>>8;
                     PumpHigh |= 0x0600;
                     PumpLow = PumpTb1[PumpTbNum];
                     PumpLow &= 0x00ff;
                     PumpLow |= 0x0700;
                     PumpTbNum++;
                    // ConfigFlags |= SEN_UP_LINE;
                    // TimeCommunicatFlag |= STATE_SEND_ON;  
                     Clock.DelayUplineScan = STATE_RF_DELAY;
                     Clock.DownLineDelay = 0;
                     TimeSlot.ReportMinute = ReportTime -1 ; 
                     if(TimeSlot.ReportSecond < 50)
                        { TimeSlot.ReportSecond = 50; } 
#if STRING_ON                       
  UartSendStrings("New PUMP:");
  UartSendStrings("\r\n");  
  UartSendNumberH(PumpHigh);   
  UartSendNumberH(PumpLow);  
#endif   
                   }
                   else
                   {
                     PumpTbNum = 0;
                     PumpHigh = FlashParamt.PumpHigh;
                     PumpHigh |= 0x0600;
                     PumpLow = FlashParamt.PumpLow;
                     PumpLow |= 0x0700;
                   }
                 }
               }
              if( Clock.DelayUplineScan == EVENT_AP_RF_DELAY )
                 { TimeCommunicatFlag &= ~EVENT_SEND_ON; }
           //  TempBaseFlag |= EVENT_GET_ON;
              
              RFM98_REST_DOWN();
              delay_us(200);
              RFM98_REST_UP();
              delay_ms(6);
              //RFM98_Config();
             // RfDisable();
              //testget = 0;
#if STRING_ON              
              UartSendStrings("down to sleep");  
              UartSendStrings("\r\n");   
#endif              
            }
            else
            {
#if STRING_ON             
            UartSendStrings("weakup 500ms");  
            UartSendStrings("\r\n"); 
#endif              
            }
            Clock.DownLineDelay++;
        }
        else  
        { 
          WDTCTL =  WDT_ARST_1000 ; 
          RfDisable(); 
           Clock.DownLineDelay = 0;
           SetFlags &= ~POWER_GET_END;
           TempBaseFlag |= EVENT_GET_ON;
           if( ConfigFlags & SYS_REST_COMMEND )
           {
             ConfigFlags &= ~SYS_REST_COMMEND;
             FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
             FlashParamt.RestNum = 0xff;   
             EraseSectorFlashB();                                   
             FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) ); 
             Sys_Soft_Reset();
           }
           else if( BaseLineFlag & BASELINE_UPDATA )
           {
             BaseLineFlag &= ~BASELINE_UPDATA;
             FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));        
             FlashParamt.BaseLineZ = AxisZ1Pam.BaseLine;
             FlashParamt.BaseLineX = AxisX1Pam.BaseLine;    
             FlashParamt.SetBaseLineZ = SetBaseLineZ;
             FlashParamt.SetBaseLineX = SetBaseLineX;
             FlashParamt.TempBaseZ = TempBaseZ;
             FlashParamt.TempBaseX = TempBaseX;
             FlashParamt.ParamtSet = 0xa5;
             EraseSectorFlashB();   
             FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );
             ConfigFlags &= ~FLASH_WRITE_ERROR; 
             FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));    
             if( (FlashParamt.BaseLineZ != AxisZ1Pam.BaseLine) ||
                 (FlashParamt.BaseLineX != AxisX1Pam.BaseLine) ||  
                 (FlashParamt.SetBaseLineZ != SetBaseLineZ)    ||
                 (FlashParamt.SetBaseLineX != SetBaseLineX)    ||
                 (FlashParamt.TempBaseZ != TempBaseZ)          ||
                 (FlashParamt.TempBaseX != TempBaseX)          ||
                 (FlashParamt.ParamtSet != 0xa5)  )
                { BaseLineFlag |= BASELINE_UPDATA;  }
   //  UartSendStrings("Base saved");  
 //UartSendStrings("\r\n");         
           }
           else if(CompFlags & FLASH_BASE_UPDATE)
           {
             CompFlags &= ~FLASH_BASE_UPDATE;
             FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));               
             for(i=0;i<BASE_BUFF_NUM;i++)
             {
               FlashParamt.BaseBuffZ[i] = FlashBaseBuffZ[i];
               FlashParamt.BaseBuffX[i] = FlashBaseBuffX[i];
             }
             FlashParamt.BaseLineZ = AxisZ1Pam.BaseLine;
             FlashParamt.BaseLineX = AxisX1Pam.BaseLine;    
             FlashParamt.BaseBuffPtrZ = BaseBuffZPtr;
             FlashParamt.BaseBuffPtrX = BaseBuffXPtr;
             FlashParamt.ParamtSet = 0xa5;
             EraseSectorFlashB();
             FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );  
           }
           else if( ConfigFlags & SAVE_PUMP_COMD )
           {           
             ConfigFlags &= ~SAVE_PUMP_COMD;
             SetFlags |= NEW_PUMP_SAVED;
             FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
             FlashParamt.PumpHigh = (u8)PumpHigh;
             FlashParamt.PumpLow = (u8)PumpLow;
             //FlashParamt.BaseLineZ = AxisZ1Pam.BaseLine;
            // FlashParamt.BaseLineX = AxisX1Pam.BaseLine;    
            // FlashParamt.SetBaseLineZ = SetBaseLineZ;
             //FlashParamt.SetBaseLineX = SetBaseLineX;   
            // FlashParamt.TempBaseZ = TempBaseZ;
            // FlashParamt.TempBaseX = TempBaseX;
             FlashParamt.ParamtSet = 0xa5;
             EraseSectorFlashB(); 
             FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );
           /*  FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));    
             if( (FlashParamt.BaseLineZ != AxisZ1Pam.BaseLine) ||
                 (FlashParamt.BaseLineX != AxisX1Pam.BaseLine) || 
                  (FlashParamt.SetBaseLineZ != SetBaseLineZ)   ||
                 (FlashParamt.SetBaseLineX != SetBaseLineX)    ||
                 (FlashParamt.TempBaseZ != TempBaseZ)          ||
                 (FlashParamt.TempBaseX != TempBaseX)          || 
                 (FlashParamt.ParamtSet != 0xa5)  )
               { BaseLineFlag |= BASELINE_UPDATA;  }  */
     // UartSendStrings("PuMP Flashed"); 
  //UartSendStrings("\r\n"); 
           } 
       /*  else if(SetFlags & SET_TIMESLOT_FLAG)
         {
           SetFlags &= ~SET_TIMESLOT_FLAG;
           FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));
           FlashParamt.SenTimeSlotNum = TimeSlot.SenTimeSlotNum;
           FlashParamt.ParamtSet = 0xa5;
           EraseSectorFlashB();
           FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );
           ConfigFlags |= RECIVE_SEN_CFG; 
           TimeSlotConfig();
         }*/
         else if(SetFlags & SET_ID_FLAG)
         {
           SetFlags &= ~SET_ID_FLAG;
           FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));
           FlashParamt.SenID = RfParamt.SenID;
           FlashParamt.ParamtSet = 0xa5;
           EraseSectorFlashB();
           FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );  
           ConfigFlags |= SEN_UP_LINE; 
           //ConfigFlags |= RECIVE_SEN_CFG; 
           TimeCommunicatFlag |= STATE_SEND_ON; 
         }
         else if(DebugFlag & RF_POWER_SET)
         {
           DebugFlag &= ~RF_POWER_SET;
           FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));
           FlashParamt.RfPower = gb_PowerBuf_Addr;
           FlashParamt.ParamtSet = 0xa5;
           EraseSectorFlashB();
           FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );  
          // ConfigFlags |= RECIVE_SEN_CFG; 
           ConfigFlags |= SEN_UP_LINE; 
           TimeCommunicatFlag |= STATE_SEND_ON; 
         }
         SetGndON();
        RstGndON();
        if(SetFlags & POWER_GET_END)
           { AD_POWER_GET_OFF(); }
       //  IoDown();
        //IoUp();
         /*if( ConfigFlags & FLASH_READ_ERR )
           {
             UartSendStrings("flash err");  
             UartSendStrings("\r\n");
           }
           else*/
           {  
#if STRING_ON             
             if( Clock.StateSecond !=  pStateSecond )
             {
              /* UartSendStrings("ID:");  
               UartSendNumberH(RfParamt.SenID);   
                UartSendStrings("PUMP:");
               UartSendStrings("\r\n");  
               UartSendNumberH(PumpHigh);   
               UartSendNumberH(PumpLow);   
               UartSendStrings("Z:"); 
               UartSendNumber(Magnetic.AxisZ1); 
               UartSendStrings("X:"); 
               UartSendNumber(Magnetic.AxisX1); 
               */
               UartSendStrings("Report:");
               UartSendNumber(ReportTime); 
               UartSendStrings("ReportTime:"); 
               UartSendNumber(TimeSlot.ReportMinute); 
               UartSendNumber(TimeSlot.ReportSecond); 
                         
               
               UartSendStrings("Z:"); 
               UartSendNumber(Magnetic.AxisZ1); 
               UartSendStrings("X:"); 
               UartSendNumber(Magnetic.AxisX1); 
               UartSendStrings("BaseZ:"); 
               UartSendNumber(AxisZ1Pam.BaseLine); 
               UartSendStrings("BaseX:");
               UartSendNumber(AxisX1Pam.BaseLine); 
   
          // UartSendStrings("RestNum:"); 
           //  UartSendNumber(FlashParamt.RestNum);
//UartSendStrings("OffBaseGetTime:"); 
 //UartSendNumber(OffBaseGetTime);
              NewLineOFF = 1;
              UartSendNumber(TimeSlot.Hour); 
              UartSendStrings(":");
              NewLineOFF = 1;
              UartSendNumber(TimeSlot.Minute); 
              UartSendStrings(":");
              UartSendNumber(TimeSlot.Second); 
               UartSendStrings("\r\n");
             //  UartSendStrings("RF Power:"); 
            //  UartSendNumber(gb_PowerBuf_Addr); 
             //  UartSendStrings("\r\n");
              // if(AdRestSecond >= REST_AD_DELAY)
              // {  UartSendStrings("RestSecond ON");  
              // UartSendStrings("\r\n");}
             }
#endif            
             pStateSecond = Clock.StateSecond;            
           }
        }
      }
    break;
    default:
      {        
        DownLineConfig();
        Sys_Soft_Reset();
      }
    break;
  }
}


/*
//扫描事件缓存，缓存不空发送事件。
//扫描结果：TimeCommunicatFlag |= EVENT_SEND_ON ：缓存不空，需要发送事件包。  
            TimeCommunicatFlag & STATE_SEND_ON  ： 心跳时间到，需要发送心跳包
*/
void ScanRFSet(void)   //
{
    u8 i;
    u8 SendPtr;
    SendPtr = 0xff;
    for(i=EventBuff.SavePtr;i<SAVE_BUFF_NUM;i++)
    {
      if( EventBuff.Event[i].Hour & 0x80 )
        { 
          SendPtr = i;
          TempBaseFlag &= ~P_EVENT_GENERT;
          break; 
        }
    }//EventBuff.SendPtr
    if( SendPtr == 0xff )
    {
      for( i=0;i<EventBuff.SavePtr;i++)
       {
         if( EventBuff.Event[i].Hour & 0x80 )
         { 
           SendPtr = i;
           TempBaseFlag &= ~P_EVENT_GENERT;
           break; 
         }
       }
    }
    if( (SendPtr == 0xff) && (TempBaseFlag & P_EVENT_GENERT) )
    {   
       TempBaseFlag &= ~P_EVENT_GENERT;
       EventBuff.Event[EventBuff.SavePtr].Hour = pEventHour;
       EventBuff.Event[EventBuff.SavePtr].Minute = pEventMinute;
       EventBuff.Event[EventBuff.SavePtr].Second = pEventSecond;
       SendPtr = EventBuff.SavePtr;
       EventBuff.SavePtr++;
       if( EventBuff.SavePtr >= SAVE_BUFF_NUM )
         { EventBuff.SavePtr = 0; }    
 //UartSendStrings("****Penent saved");  
 //UartSendStrings("\r\n");      
    }
    if( (SendPtr != 0xff) )//&& (!(ExtraFlags & CRITICAL_OFF)) )
        {         
           TempBaseFlag &= ~P_EVENT_GENERT;
           if( RfSendFlags & CONNECTED_AP )
           {
               EventBuff.LastNum = EventBuff.EventNum;
               EventBuff.SendPtr = SendPtr;
               TimeCommunicatFlag |= EVENT_SEND_ON;
               ConfigFlags |= SEN_UP_LINE; 
               SingleFlag &= ~LOST_EVENT_SCANED;
               Clock.DelayUplineScan = EVENT_RF_DELAY;
               
               TimeCommunicatFlag |= SEN_ON_LINE;
                 RfParamt.ApID = RfParamt.pApID;
                 TimeSlot.UplineTime = 0;
                 //TestDemo = 0;
                 UplineNum = 0;
                 ConfigFlags &= ~SET_PUMP;   
  //UartSendStrings("evevt scan");  
 //UartSendStrings("\r\n");                
                 
           }
          else if( EventBuff.EventNum != EventBuff.LastNum )
           {
               EventBuff.LastNum = EventBuff.EventNum;
               EventBuff.SendPtr = SendPtr;
               TimeCommunicatFlag |= EVENT_SEND_ON;
               ConfigFlags |= SEN_UP_LINE; 
               SingleFlag &= ~LOST_EVENT_SCANED;
               Clock.DelayUplineScan = EVENT_AP_RF_DELAY;
               ReSendNumE = 0;
               TimeCommunicatFlag |= SEN_ON_LINE;
                 RfParamt.ApID = RfParamt.pApID;
                 TimeSlot.UplineTime = 0;
                 //TestDemo = 0;
                 UplineNum = 0;
                 ConfigFlags &= ~SET_PUMP;       
           }
           else if( (SystemState == ON_BASE_LINE)      && 
                    (LastSend.SendNum > 1)             && 
                    (SingleFlag & LAST_EVENT_ON)       &&
                    (!(SingleFlag & LOST_EVENT_SCANED)) )
           {
             SaveEvent(OFF);
             SingleFlag |= LOST_EVENT_SCANED;
           }
          /* else if( (SystemState == EVENT_DETECT)        && 
                    (LastSend.SendNum > 1)               &&
                    (!(SingleFlag & LAST_EVENT_ON))      &&
                    (!(SingleFlag & LOST_EVENT_SCANED))  &&
                    (ExtraFlags & ON_BASELIN_GENERT_Z)   &&
                    (ExtraFlags & ON_BASELIN_GENERT_X)  )
           {
             SaveEvent(ON);
             SingleFlag |= LOST_EVENT_SCANED;
           }*/
           else if( (TimeCommunicatFlag & STATE_SEND_ON) || (SetFlags & AD_WEAKUP) || (TempBaseFlag & UPLINE_AP_STATE) ) 
           {
                if(TempBaseFlag & UPLINE_AP_STATE)
                   { TempBaseFlag &= ~UPLINE_AP_STATE;  }
               ConfigFlags |= SEN_UP_LINE; 
               if(DebugFlag & RE_SCAN_SYNC)
                 { Clock.DelayUplineScan = EVENT_RF_DELAY; }
               else
                 { Clock.DelayUplineScan = STATE_RF_DELAY; }
                if( !(SetFlags & STATE_TIME_SAVED) )
                {
                   AddSlotNum.SenID = RfParamt.SenID;
                   AddSlotNum.Second = TimeSlot.Second;
                   AddSlotNum.MsTime = AdTime.uiRemainSlot;
                   AddSlotNum.SendNum = 0;
                   SetFlags |= STATE_TIME_SAVED;
                 }
           }       
        } 
        else if( (SystemState == ON_BASE_LINE)      && 
                 (LastSend.SendNum > 1)             && 
                 (SingleFlag & LAST_EVENT_ON)       &&
                 (!(SingleFlag & LOST_EVENT_SCANED)) )
           {
             SaveEvent(OFF);                     
             SingleFlag |= LOST_EVENT_SCANED;
           }
        /* else if( (SystemState == EVENT_DETECT)        && 
                 (LastSend.SendNum > 1)                &&
                 (!(SingleFlag & LAST_EVENT_ON))       &&
                 (!(SingleFlag & LOST_EVENT_SCANED))   &&
                 (ExtraFlags & ON_BASELIN_GENERT_Z)    &&
                 (ExtraFlags & ON_BASELIN_GENERT_X)  )
           {
             SaveEvent(ON);
             SingleFlag |= LOST_EVENT_SCANED;
           }*/
       else if( (TimeCommunicatFlag & STATE_SEND_ON) || (SetFlags & AD_WEAKUP) || (TempBaseFlag & UPLINE_AP_STATE) )// && (!(TimeCommunicatFlag & SIGNAL_SEND_ON)) )
        {     
           if(TempBaseFlag & UPLINE_AP_STATE)
             {  TempBaseFlag &= ~UPLINE_AP_STATE;  }
           ConfigFlags |= SEN_UP_LINE;  
           if(DebugFlag & RE_SCAN_SYNC)
             { Clock.DelayUplineScan = EVENT_RF_DELAY; }
           else
             { Clock.DelayUplineScan = STATE_RF_DELAY; }
           if( !(SetFlags & STATE_TIME_SAVED) )
           {
              AddSlotNum.SenID = RfParamt.SenID;
              AddSlotNum.Second = TimeSlot.Second;
              AddSlotNum.MsTime = AdTime.uiRemainSlot;
              AddSlotNum.SendNum = 0;
              SetFlags |= STATE_TIME_SAVED;
            }
        } 
      else if((SingleFlag & REST_OFF_SEND) && (RfSendFlags & CONNECTED_AP) )
        {
          SingleFlag &= ~REST_OFF_SEND;
          SaveEvent(OFF);          
        }
}


/*
// 时间更新：时分秒
*/
void  TimeClockUpdate(void)
{
  u8 temp;
  TimeSlot.Second++;
  TimeSlot.ReportSecond++;
  if( ExtraFlags & ON_GET_BASELINE )
    { AdTime.BaseInitSecond++;}
  if( TimeSlot.Second >= 60 )
  {     
     TimeSlot.Second = 0;
     TimeSlot.Minute++;     
     if( TimeSlot.Minute >= 60 )
     {
       TimeSlot.Minute = 0;
       TimeSlot.Hour++;
       if( TimeSlot.Hour>= 24 )
         {  
           TimeSlot.Hour = 0;
           AdRestSecond = 0;  
           CompFlags |= DAY_UPDATE;
           FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt));  
           temp = DecBaseOn(FlashParamt.BaseLineZ, AxisZ1Pam.BaseLine);
           if(temp == 1 )
             { BaseLineFlag |= BASELINE_UPDATA; }
           temp = DecBaseOn(FlashParamt.BaseLineX, AxisX1Pam.BaseLine);
            if(temp == 1 )
             { BaseLineFlag |= BASELINE_UPDATA; }
          /* if( (OffNumZ>=3) && (OffNumX>=3) )
             {
               TempBaseDayCnt++;
               OldBaseDayCnt++;
               FlashRead(SegmentC, (u8 *)&BaseLineBuff,sizeof(BaseLineBuff));
               BaseLineBuff.TempBasDay = TempBaseDayCnt;
               BaseLineBuff.OldBasDay = OldBaseDayCnt;
               FlashWrite(SegmentC, (u8 *)&BaseLineBuff,sizeof(BaseLineBuff));
               if( TempBaseDayCnt >= 7 )
               {           
                 TempBaseDayCnt = 0;   
                 if(OldBaseDayCnt >= 30)
                 {
                   OldBaseDayCnt = 0;
                   if( (FlashParamt.TempBaseZ > MIN_BASE) && 
                       (FlashParamt.TempBaseZ < MAX_BASE) && 
                       (FlashParamt.TempBaseX > MIN_BASE) &&
                       (FlashParamt.TempBaseX < MAX_BASE)  )
                     {
                        SetBaseLineZ = FlashParamt.TempBaseZ;
                        SetBaseLineX = FlashParamt.TempBaseX;              
                     }
                 }
                 TempBaseZ = AxisZ1Pam.BaseLine;
                 TempBaseX = AxisX1Pam.BaseLine;
                 BaseLineFlag |= BASELINE_UPDATA;                  
               }
             }*/
         // OffNumZ = 0;
           //OffNumX = 0;
         }
     }
  }
  if( (ReportTime != REPORT_SEND_TIME_0) &&
      (ReportTime != REPORT_SEND_TIME_1) &&
      (ReportTime != REPORT_SEND_TIME_2) &&
      (ReportTime != REPORT_SEND_TIME_3) &&
      (ReportTime != REPORT_SEND_TIME_4) &&
      (ReportTime != REPORT_SEND_TIME_5) &&
      (ReportTime != REPORT_SEND_TIME_6) && 
      (ReportTime != REPORT_SEND_TIME_7)  )
    {           
       ReportTime = REPORT_SEND_TIME_3;
    }
  if( !(RfSendFlags & CONNECTED_AP) )
    { ReportTime = REPORT_SEND_TIME_3; }
  if( TimeSlot.ReportSecond >= 60 )
    { 
      TimeSlot.ReportSecond = 0;
      TimeSlot.ReportMinute++;
    }
  if( TimeSlot.ReportMinute >= ReportTime )
  {
    TimeSlot.ReportMinute = 0;
    TimeCommunicatFlag |= STATE_SEND_ON;        
  }
  if( AdTime.BaseInitSecond >= 60 )
  {
    AdTime.BaseInitSecond = 0;
    AdTime.BaseInitMinute++;
    if( AdTime.BaseInitMinute >= 2880 )
    {
      AdTime.BaseInitMinute = 0;
      ExtraFlags &= ~ON_GET_BASELINE;
    }
  }
}

void TimeSlotUpdate(void)
{
  u8 temp;
  temp = TimeSlot.SenTimeSlotNum;
  switch( AddSlotNum.SendNum )
  {
    case 0:
    {
      temp += AddSlotNum.SenID ;
    }
    break;
    case 1:
    {
      temp += AddSlotNum.Second;
    }
    break;
    case 2:
    {
      temp += AddSlotNum.MsTime;
    }
    break;
  case 3:
    {
      temp += AddSlotNum.Second;
    }
    break;
    case 4:
    {
      temp += AddSlotNum.MsTime; 
    }
    break;
    case 5:
    {
      temp += AddSlotNum.SenID ;
    }
    break;
    case 6:
    {
      temp += AddSlotNum.MsTime;
    }
    break;
    case 7:
    {
      temp += AddSlotNum.SenID ; 
    }
    break;
    case 8:
    {
      temp += AddSlotNum.Second;
    }
    break;
  default:
    break;
  }

  temp = temp % 10;
  if(temp == 0)
    { TimeSlot.SenTimeSlotNum = 10; }
  else
    { TimeSlot.SenTimeSlotNum = temp;}
  
  temp =  TimeSlot.SenTimeSlotNum % MIN_CLCYL_SEN_NUM;
  if(temp == 0)
    { TimeSlot.MinTimeSlot = MIN_CLCYL_SEN_NUM; }
  else
    { TimeSlot.MinTimeSlot = temp; } 
  
  AddSlotNum.SendNum++;
  if(AddSlotNum.SendNum > 8 )
    { AddSlotNum.SendNum = 0; }
}

