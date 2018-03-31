#include"types.h"
#include "cfg.h"
#include "snp.h"
#include "timeslot.h"
#include "board.h"
#include "magentic.h"
#include "ad.h"
#include "uart.h"
#include "flash.h"
//#include <malloc.h> 
#include <stdlib.h>
#include <string.h>


/*******************************************************************************
 //初始化配置程序，可暂时不管
**********************************************************************************/

extern u8 gb_PowerBuf_Addr;
extern u8 testget;
extern u8 OffBaseOpen;
extern AD_TIME_CYCLE AdTime;
extern SENSOR_TIME_PARAMTER  SenTime;
extern SENSOR_SAMPLE_PARAMTER EventOnBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER EventOnBaseLineX;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineX;
extern STABLE_BASELINE         StableBaseLineZ;
extern STABLE_BASELINE         StableBaseLineX;
extern EVENT_BUFF  EventBuff;
extern ON_NUM_BUFF OnNumBuff;
extern OFF_BASELINE_BUFF OffBaseBuffZ;
extern OFF_BASELINE_BUFF OffBaseBuffX;
extern SNP_UF_ACK_PACKET_t UfAckPacket;
extern TIME_SLOT_PARMAT TimeSlot; 
extern SENSOR_SAMPLE_PARAMTER AxisX1Pam;
extern SENSOR_SAMPLE_PARAMTER AxisZ1Pam;
extern INIT_BASELINE InitBaseline;
extern BUS_EVENT_BUFF BusEvent;
extern CLOCK_VALUE Clock;
extern MAGNETIC_VALUE Magnetic;
extern u16 ExtraFlags;
extern u16 TimeCommunicatFlag;
extern u16 SetBaseLineZ;
extern u16 SetBaseLineX;
extern u16 AdMagenticFlags;
extern u16 CheckNumRead;
extern u16 CheckNumWrite;
extern u16 PumpHigh;
extern u16 PumpLow;
extern u16 ReportTime;
extern u16 BaseLineFlag;
extern u16 CompFlags;
extern u16 TempBaseZ;
extern u16 TempBaseX;
extern u8 SysTimeSlot;
extern u8 TimeSlotMode;
extern u8 RfSendFlags;
extern u8 NumRx;
extern u8 Day;
extern u8 BaseAutoSet;
extern u8 SendBusPtr;
extern u8 TriggValue;
extern u8 ApTriggValue;
extern u8 ApDetectValue;
extern u8 DetectValue;
extern u8 SystemState;
extern u8 NotScanSyncNum;
extern u8 DownLineNum;
extern u8 SingleValue;
extern u16 SetOnTime;
extern u16 HalfBaseLineFlag;
extern u16 TempBaseFlag;
extern u16 DebugFlag;
extern u16 SingleFlag;
extern u16 LastBaseLineZ;
extern u16 LastBaseLineX;
extern u8 NewLineOFF;
extern u8 PumpTbNum;
extern u8 MaxOffNum;
extern u8 UnDetectValue;
extern u8 TempBaseDayCnt;
extern u8 OldBaseDayCnt;
extern u8 OneAxisOffMode;
extern u8 OnBaseMoved;
extern u8 MinTrgge;
extern u8 OnTime;
extern u8 EventOffFlag;
extern u8 BaseBuffZPtr;
extern u8 BaseBuffXPtr;
extern u8 BigTrigBase;
extern u8 OffTime;
extern u8 EventChangTime;
extern u8 BaseBuffTime;
extern u8 AverageValueTime;
extern u8 OffValueCntBuffNum;
extern u8 DecMaxAd;
extern u16 NewBaseFlag;

extern ON_BASELINE_BUFF BaseLineBuff;
extern EVENT_SAVE_SYS  SaveEventFlash;
SET_SEN_PARAMTER_1 ReportCfg;
SET_SEN_PARAMTER_2 DetectValueCfg;
SNP_SEN_CFG_ACK_PACKET_t SenAckPacket;
RF_PARAMTER RfParamt;
FLASH_PARAMTER_t  FlashParamt;
CODE_SAVE_BUFFER CodeBuffer;

u8 IntVecBuff[66];
u8 DownCodeFlag;
u16 ConfigFlags;
u16 SetFlags = 0;
u16 ChangLastID;
u32 SaveCodeAddress ;
u8 NewPumpH;
u8 NewPumpL;
u16 ReportTimeTab[8];
u8  OffBaseOpenTab[2];
u8  EventOffTab[2];
//u8  MinTriggTab[2];
u8  OnTimeTab[4];
u8  TriggValueTab[8];
u8 CodeAdress;
u8  UnDetectValueTab[4];
u8  SingleValueTab[8];
extern u8 DatCnt1[2];
extern u8 testflag;

u16 FlashBaseBuffZ[BASE_BUFF_NUM];
u16 FlashBaseBuffX[BASE_BUFF_NUM];
/*
void FlshParamtCfg(void)
{
  FlashParamt.SenID = RfParamt.SenID;
  FlashParamt.SenTimeSlotNum = TimeSlot.SenTimeSlotNum;
  FlashParamt.ResetFlag = 0;
  FlashParamt.ParamtSet = 0xa5;
  FlashParamt.PumpHigh = (u8)PumpHigh;
  FlashParamt.PumpLow = (u8)PumpLow;
}*/

void FlashParamterInit(void)
{
  u8 i;
  AdMagenticFlags = 0; 
  SingleFlag = 0;
  //FlashRead(CHECK_NUM_ADDRESS,(u8 *)&CheckNumRead,2);
  FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); 
  FlashParamt.RestNum++;                           //****************************************test****************
  if( (FlashParamt.ParamtSet != 0xa5)    || 
      (FlashParamt.SenID == 0xffff)      ||
      (FlashParamt.SenTimeSlotNum == 0XFFFF) ||
      (FlashParamt.PumpHigh == 0XFF)         ||
      (FlashParamt.PumpLow == 0xff)          ||
      (FlashParamt.BaseLineZ == 0xffff)      ||
      (FlashParamt.BaseLineX == 0xffff)      ||
      (FlashParamt.SetBaseLineZ == 0xffff)   ||
      (FlashParamt.SetBaseLineX == 0xffff))
    { FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); }
  /*if( (FlashParamt.ParamtSet != 0xa5)    || 
      (FlashParamt.SenID == 0xffff)      ||
      (FlashParamt.SenTimeSlotNum == 0XFFFF) ||
      (FlashParamt.PumpHigh == 0XFF)         ||
      (FlashParamt.PumpLow == 0xff)          ||
      (FlashParamt.BaseLineZ == 0xffff)      ||
      (FlashParamt.BaseLineX == 0xffff)      ||
      (FlashParamt.SetBaseLineZ == 0xffff)   ||
      (FlashParamt.SetBaseLineX == 0xffff)   ) 
    { FlashReadB( (u8 *)&FlashParamt,sizeof(FlashParamt)); }*/
 /* if( (FlashParamt.ParamtSet != 0xa5)    || 
      (FlashParamt.SenID == 0xffff)      ||
      (FlashParamt.SenTimeSlotNum == 0XFFFF) ||
      (FlashParamt.PumpHigh == 0XFF)         ||
      (FlashParamt.PumpLow == 0xff)          ||
      (FlashParamt.BaseLineZ == 0xffff)      ||
      (FlashParamt.BaseLineX == 0xffff)      ||
      (FlashParamt.SetBaseLineZ == 0xffff)   ||
      (FlashParamt.SetBaseLineX == 0xffff)  )  
   { ConfigFlags |= FLASH_READ_ERR; }
  else 
   { ConfigFlags &= ~FLASH_READ_ERR;}*/
  if( FlashParamt.ParamtSet == 0xa5 )//&& (ConfigFlags & FLASH_CHECK_OK) )
  {
    RfParamt.SenID = FlashParamt.SenID;
    TimeSlot.SenTimeSlotNum = FlashParamt.SenTimeSlotNum;
    AxisZ1Pam.BaseLine = FlashParamt.BaseLineZ;
    AxisX1Pam.BaseLine = FlashParamt.BaseLineX;
    AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
    AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
   // SetBaseLineZ = FlashParamt.SetBaseLineZ;
   // SetBaseLineX = FlashParamt.SetBaseLineX;
    TempBaseZ = FlashParamt.TempBaseZ;
    TempBaseX = FlashParamt.TempBaseX;
    for(i=0;i<BASE_BUFF_NUM;i++)
      { 
        FlashBaseBuffZ[i] = FlashParamt.BaseBuffZ[i];
        FlashBaseBuffX[i] = FlashParamt.BaseBuffX[i];
      }
    BaseBuffZPtr = FlashParamt.BaseBuffPtrZ;
    if( BaseBuffZPtr >= BASE_BUFF_NUM )
      { BaseBuffZPtr = 0; }
    BaseBuffXPtr = FlashParamt.BaseBuffPtrX;
    if( BaseBuffXPtr >= BASE_BUFF_NUM )
      { BaseBuffXPtr = 0; }
    
    if( FlashParamt.RfPower >= 4 )
      { FlashParamt.RfPower = POWER_RF; }
    gb_PowerBuf_Addr = FlashParamt.RfPower; 
    PumpHigh = FlashParamt.PumpHigh;
    PumpHigh |= 0x0600;
    PumpLow = FlashParamt.PumpLow;
    PumpLow |= 0x0700;
    TimeSlotConfig();
    ConfigFlags |= TIMESLOT_SAVED; 
    EraseSectorFlashB();                                    //*****************************test*************************
    FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );  //*****************************test*复位次数存储************************
    FlashRead(EVENT_SAVE_ADRESS,(u8 *)&SaveEventFlash,sizeof(SaveEventFlash));
    if( SaveEventFlash.Flag == 0xaa )
    {
      SetFlags |= EVENT_FLASH_SAVED;
      TimeSlot.Hour = SaveEventFlash.Hour & 0x7f;
      TimeSlot.Minute = SaveEventFlash.Minute & 0x7f;
      TimeSlot.Second = SaveEventFlash.Second & 0x7f;
      if( SaveEventFlash.Second & 0x80 )
        { SaveEvent(ON); }
      else
        { SaveEvent(OFF);} 
    }
  }
  else
  {
#if FIXED_ID   
    FlashParamt.ParamtSet = 0xa5; 
    FlashParamt.SenID = DEFAULT_ID;      
#endif 
    FlashParamt.SenTimeSlotNum = DEFAULT_NUM;
    RfParamt.SenID = FlashParamt.SenID;
    FlashParamt.RfPower = POWER_RF;
    gb_PowerBuf_Addr = FlashParamt.RfPower;
    FlashParamt.PumpHigh = (u8)HIGH_PUMP;  
    FlashParamt.PumpLow = (u8)LOW_PUMP;
    PumpHigh = HIGH_PUMP;
    PumpLow = LOW_PUMP;
    AxisZ1Pam.BaseLine = 0xFFFF;
    AxisX1Pam.BaseLine = 0xFFFF;
    FlashParamt.BaseLineZ = AxisZ1Pam.BaseLine;
    FlashParamt.BaseLineX = AxisX1Pam.BaseLine;
    for(i=0;i<BASE_BUFF_NUM;i++)
      { FlashBaseBuffZ[i] = 0; }
    for(i=0;i<BASE_BUFF_NUM;i++)
      { FlashBaseBuffX[i] = 0; }
    BaseBuffZPtr = 0;
    BaseBuffXPtr = 0;
    EraseSectorFlashB();
    CheckNumWrite = FlashWriteB( (u8 *)&FlashParamt,sizeof(FlashParamt) );  
    FlashRead(CHECK_NUM_ADDRESS, (u8 *)&CheckNumRead,2);
   // TimeSlot.SenTimeSlotNum = CreatTimeSlot();
#if FIXED_ID     
      ConfigFlags |= TIMESLOT_SAVED;
#endif
    TimeSlot.SenTimeSlotNum = FlashParamt.SenTimeSlotNum;
    TimeSlotConfig();
    FlashParamt.ResetFlag = 0;
  }
  FlashRead(JUMP_ADRESS, &CodeAdress,1);
  
  FlashRead(SegmentC, (u8 *)&BaseLineBuff,sizeof(BaseLineBuff));  
  if( (BaseLineBuff.BaseNum<2) || (BaseLineBuff.BaseNum==0xff) )
     { memset(&BaseLineBuff,0,sizeof(BaseLineBuff)); } 
                    
                         if( (FlashParamt.BaseLineZ < MIN_BASE) || ( FlashParamt.BaseLineZ > MAX_BASE) )
                         {
                           if( (FlashParamt.SetBaseLineZ > MIN_BASE) && (FlashParamt.SetBaseLineZ < MAX_BASE) )
                               { 
                                 AxisZ1Pam.BaseLine = FlashParamt.SetBaseLineZ; 
                                 BaseLineFlag |= BASELINE_UPDATA;
                               }
                         }
                       
                         if( (FlashParamt.BaseLineX < MIN_BASE) || ( FlashParamt.BaseLineX > MAX_BASE) )
                         {
                           if( (FlashParamt.SetBaseLineX > MIN_BASE) && (FlashParamt.SetBaseLineX < MAX_BASE) )
                              { 
                                AxisX1Pam.BaseLine = FlashParamt.SetBaseLineX;
                                BaseLineFlag |= BASELINE_UPDATA;
                              }
                         }
                         
                        /* if( (FlashParamt.SetBaseLineZ < MIN_BASE) || (FlashParamt.SetBaseLineZ > MAX_BASE) )
                         {
                           if( (FlashParamt.BaseLineZ > MIN_BASE) && (FlashParamt.BaseLineZ < MAX_BASE) )
                             { 
                               SetBaseLineZ = FlashParamt.BaseLineZ;
                               BaseLineFlag |= BASELINE_UPDATA;
                             }
                         }*/
                         
                       /*  if( (FlashParamt.SetBaseLineX < MIN_BASE) || (FlashParamt.SetBaseLineX > MAX_BASE) )
                         {
                           if( (FlashParamt.BaseLineX > MIN_BASE) && (FlashParamt.BaseLineX < MAX_BASE) )
                             { 
                               SetBaseLineX = FlashParamt.BaseLineX; 
                               BaseLineFlag |= BASELINE_UPDATA;
                             }
                         }*/
                         AxisZ1Pam.OverThresCnt = 0;
                         SystemState = ON_BASE_LINE;
                         BaseLineFlag |= READ_BASELINE;
                       //  SingleFlag |= BASE_LINE_ON;
                         SenTime.BaseLineTime = 0;                                                 
                         LastBaseLineZ = AxisZ1Pam.BaseLine;
                         LastBaseLineX = AxisX1Pam.BaseLine;  
                         SetBaseLineZ = FlashParamt.SetBaseLineZ;
                         SetBaseLineX = FlashParamt.SetBaseLineX;
                         TempBaseZ = FlashParamt.TempBaseZ;
                         TempBaseX = FlashParamt.TempBaseX;
                         AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
                         AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
                         for(i=0;i<3;i++)
                         {
                           OffBaseBuffZ.Buff[i] = AxisZ1Pam.BaseLine;
                           OffBaseBuffX.Buff[i] = AxisX1Pam.BaseLine;
                         }
                      
#if LED_TEST_ON
                     if( ( (FlashParamt.BaseLineZ < MIN_BASE) || ( FlashParamt.BaseLineZ > MAX_BASE) ) && 
                         ( (FlashParamt.SetBaseLineZ < MIN_BASE) || ( FlashParamt.SetBaseLineZ > MAX_BASE) )  )
                       {
                           SystemState = INIT_BASE_LINE;
                           AdMagenticFlags &= ~BASELINE_GENERT;
                           //BaseAutoSet = ON;
                           memset(&InitBaseline,0,sizeof(InitBaseline));    
                       }
                     else if( ( (FlashParamt.BaseLineX < MIN_BASE) || ( FlashParamt.BaseLineX > MAX_BASE) )   &&
                              ( (FlashParamt.SetBaseLineX < MIN_BASE) || ( FlashParamt.SetBaseLineX > MAX_BASE) )  )
                       {
                            SystemState = INIT_BASE_LINE;
                            AdMagenticFlags &= ~BASELINE_GENERT;
                            //BaseAutoSet = ON;
                            memset(&InitBaseline,0,sizeof(InitBaseline));
                       }
#endif
}

void SystemParamterInit(void)
{
  memset(&CodeBuffer, 0 ,sizeof(CodeBuffer));
 // memset(&CodeBuffer.Buff[0], 0xff, 512);
  
  ReportTimeTab[0] = REPORT_SEND_TIME_0;
  ReportTimeTab[1] = REPORT_SEND_TIME_1;
  ReportTimeTab[2] = REPORT_SEND_TIME_2;
  ReportTimeTab[3] = REPORT_SEND_TIME_3;
  ReportTimeTab[4] = REPORT_SEND_TIME_4;
  ReportTimeTab[5] = REPORT_SEND_TIME_5;
  ReportTimeTab[6] = REPORT_SEND_TIME_6;
  ReportTimeTab[7] = REPORT_SEND_TIME_7;
  
  OffBaseOpenTab[0] = OFF_BASE_OPEN_0;
  OffBaseOpenTab[1] = OFF_BASE_OPEN_1;
  
 EventOffTab[0] = EVENT_OFF_0;
 EventOffTab[1] = EVENT_OFF_1;
  
 // MinTriggTab[0] = MIN_TRIGG_0;
 // MinTriggTab[1] = MIN_TRIGG_1;
  
  OnTimeTab[0] = ON_TIME_0;
  OnTimeTab[1] = ON_TIME_1;
  OnTimeTab[2] = ON_TIME_2;
  OnTimeTab[3] = ON_TIME_3;
  
  TriggValueTab[0] = TRIGG_VALUE_0;
  TriggValueTab[1] = TRIGG_VALUE_1;
  TriggValueTab[2] = TRIGG_VALUE_2;
  TriggValueTab[3] = TRIGG_VALUE_3;
  TriggValueTab[4] = TRIGG_VALUE_4;
  TriggValueTab[5] = TRIGG_VALUE_5;
  TriggValueTab[6] = TRIGG_VALUE_6;
  TriggValueTab[7] = TRIGG_VALUE_7;
  
  UnDetectValueTab[0] = DETECT_VALUE_0;
  UnDetectValueTab[1] = DETECT_VALUE_1;
  UnDetectValueTab[2] = DETECT_VALUE_2;
  UnDetectValueTab[3] = DETECT_VALUE_3;
  
  SingleValueTab[0] = SINGLE_VALUE_0;
  SingleValueTab[1] = SINGLE_VALUE_1;
  SingleValueTab[2] = SINGLE_VALUE_2;
  SingleValueTab[3] = SINGLE_VALUE_3;
  SingleValueTab[4] = SINGLE_VALUE_4;
  SingleValueTab[5] = SINGLE_VALUE_5;
  SingleValueTab[6] = SINGLE_VALUE_6;
  SingleValueTab[7] = SINGLE_VALUE_7;
}

//***************************************************************************************************
void SyncProcess(SNP_SYNC_PACKET_t *SyncPtr)
{ 
  u16 TempID;
  u8 i;
 // u8 AdDecNum;
    TimeSlot.Second = SyncPtr->Second;
    TimeSlot.Minute = SyncPtr->Minute;
    TimeSlot.Hour = SyncPtr->Hour;   

    TimeSlot.TimeSlotNum = SyncPtr->TimeSlotNum;
    TimeSlot.AllTimeSlotNum = SyncPtr->AllTimeSlotNum;
    
  if( (TimeSlot.Hour == 0) && (TimeSlot.Minute < 5) && (!(CompFlags & DAY_UPDATE)) )
    { CompFlags |= DAY_UPDATE; }
  DownLineNum = 0;
  NumRx = 0;
  DebugFlag &= ~RE_SCAN_SYNC;
  AdTimeClear();
  if( TimeSlotMode == SNP_DOWN_CODE_MODE )
     {  TimerA_RestCount(61); }
  else
    { TimerA_RestCount(DEC_SYNC_TIME);  }
   if( (SysTimeSlot == Sen_UpLine) && (!(RfSendFlags & CONNECTED_AP)) )
   {
     for(i=0;i<BUFF_NUM;i++)
       { BusEvent.BusNum[i].Day |= 0x80; }
   }
  

  if( SysTimeSlot == Sen_UpLine )
  {
    if( (SyncPtr->CfgBox == 0xaa)              || 
        (ConfigFlags & RECIVE_SEN_CFG)         || 
        (TimeCommunicatFlag & EVENT_SEND_ON)   ||
        (TimeCommunicatFlag & STATE_SEND_ON)   ||
        (TimeSlotMode == SNP_DOWN_CODE_MODE)  )
      { 
        SysTimeSlot = Sync_Frm1; 
        if(SyncPtr->CfgBox == 0xaa)
          { TimeCommunicatFlag |= STATE_SEND_ON; }
      }
    else 
      { SysTimeSlot = Sen_UpLine; }
  }
  else
  {
    SysTimeSlot = Sync_Frm1;     
  }
  if(SyncPtr->CfgBox == 0xaa)
    { ConfigFlags |= CFG_BOX_SYNC; }
  else
    { 
      ConfigFlags &= ~CFG_BOX_SYNC; 
      if(SetFlags & AD_WEAKUP)
        { SetFlags &= ~AD_WEAKUP; }
    }
  if( SyncPtr->sPhr.uiType == SNP_PACKET_TYPE_SYNC )
    { 
      TimeCommunicatFlag |= RECIVE_SYNC;
      NewBaseFlag |= STATE_SYNC_ON;
    }
  else if(SyncPtr->sPhr.uiType == DOWN_CODE_SYNC)//************************************有待完善
    { 
      TempID = SyncPtr->StartWorkTime;
      TempID |= SyncPtr->StopWorkTime<<8;
      if( TempID == RfParamt.SenID )
        { TimeCommunicatFlag |= RECIVE_SYNC; }
      else
        { TimeCommunicatFlag &= ~RECIVE_SYNC;}
    }
  if(!(CompFlags & UP_SECOND_ADD))
    { Clock.UpLineSecond += 4; }
  ReportCfg.Paramter = SyncPtr->SystemParameter[0];
  DetectValueCfg.Paramter = SyncPtr->SystemParameter[1];
  ReportTime = ReportTimeTab[ReportCfg.PamSet.ReportTime];
  DecMaxAd = OffBaseOpenTab[ReportCfg.PamSet.OffBase];
  EventOffFlag = EventOffTab[ReportCfg.PamSet.EventOff];
  //MinTrgge = MinTriggTab[ReportCfg.PamSet.MinTrigg];
  OnTime = OnTimeTab[ReportCfg.PamSet.OnTime];
  ApDetectValue = TriggValueTab[DetectValueCfg.PamSet.TriggValue];
  UnDetectValue = UnDetectValueTab[DetectValueCfg.PamSet.UnDetectValue];
  OffTime = SingleValueTab[DetectValueCfg.PamSet.SignalValue];
  SetFlags &= ~STATE_TIME_SAVED;
  EventChangTime = OffTime + 24;
  BaseBuffTime = OffTime + 40;
  MaxOffNum = OffTime - 8;
  AverageValueTime = OffTime + 24;
  OffValueCntBuffNum = OffTime>>3;
//UartSendStrings("ReportParamter:"); 
//UartSendNumber(ReportCfg.Paramter  );
  
  //TempBaseFlag |= EVENT_GET_ON;
 // DebugFlag &= ~SYS_REST_ON;
  //AdIntrruptOff();
  //UartSendStrings("SYNC:"); 
//UartSendNumber(TimeSlot.TimeSlotNum );
// UartSendStrings("\r\n");  
 //P5OUT &= ~BIT4; 
}

 
void SenCfgProcess(SNP_CFG_PACKET_t *SenCfgPtr)
{
  u8 command;
  u8 i;
  u8 tempBank;
  u8 Bank;
  u16 mytemp;
  u8 *ptr;
//  u8 *CodePtr;
 // CodePtr = (u8 *)malloc(sizeof(512));
    TimeSlot.Second = SenCfgPtr->Second;
    TimeSlot.Minute = SenCfgPtr->Minute;
    TimeSlot.Hour = SenCfgPtr->Hour;
    TimeSlot.TimeSlotNum = SenCfgPtr->TimeSlotNum;
    TimeSlot.AllTimeSlotNum = SenCfgPtr->AllTimeSlotNum;
    SetFlags &= ~STATE_TIME_SAVED;
 // DebugFlag &= ~SYS_REST_ON;
  DownLineNum = 0;
  NumRx = 0;
  AdTimeClear();
  TimerA_RestCount(DEC_SYNC_TIME);  
//UartSendStrings("Cfg SYNC:"); 
//UartSendStrings("\r\n");   
  SysTimeSlot = Sync_Frm1;
  ptr = (u8 *)&SenCfgPtr->uiDestId;
  mytemp = *ptr++;
  mytemp |= *ptr<<8;
//  ptr = (u8 *)&SenCfgPtr->uiCmd;
 // *ptr &= 0x0f;
 //TempBaseFlag |= EVENT_GET_ON;
  if(mytemp == RfParamt.SenID)
    { 
      TimeCommunicatFlag |= RECIVE_SYNC; 
      TimeCommunicatFlag |= CFG_SYNC_ON;
      CompFlags |= WEAK_UP_CFG_SEND;
      if( SetFlags & AD_WEAKUP )
        { TimeCommunicatFlag |= STATE_SEND_ON; }
 //UartSendStrings("Cfg SYNC:"); 
//UartSendStrings("\r\n");     
    }
  else if( (*ptr == SET_ID) && (mytemp == ChangLastID))
    { TimeCommunicatFlag |= RECIVE_SYNC; }
  if( (mytemp == RfParamt.SenID)  && (!(ConfigFlags & RECIVE_SEN_CFG)) )// && (TimeSlotMode == SNP_PACKET_TYPE_SEN_A)
  {    
    ptr = (u8 *)&SenCfgPtr->uiCmd;
    mytemp = *ptr++;
    mytemp |= *ptr<<8;
    command = (u8)mytemp & 0x0F;  
    switch (command)
    {
      case SNP_CMD_SEN_RECAL:
        {
          //TimeSlotMode = SNP_PACKET_TYPE_SEN_A;
            SenAckPacket.uiCmd = mytemp;
            ConfigFlags |= RECIVE_SEN_CFG; 
            ConfigFlags |= SYS_REST_COMMEND;
           // TimeCommunicatFlag &= ~STATE_SEND_ON;
        }
      break;
      case SNP_CMD_ENTER_UF:
        {       
          //if(!(SetFlags & CFG_RESEND))
          
            TimeSlotMode = SNP_PHR_TYPE_UP_LINE;
            SenAckPacket.uiCmd = mytemp;
            ConfigFlags |= RECIVE_SEN_CFG; 
          //  TimeCommunicatFlag &= ~STATE_SEND_ON;
            DownCodeFlag = 0;         
            TimeSlot.RcvSyncNum = 0;
            DebugFlag &= ~CODE_ADRESS_MATE;
            tempBank = mytemp>>8;
            FlashRead(JUMP_ADRESS, &Bank,1); 
// Bank = 0x60;        //***********************************************************bank*********************  
            if( (Bank == LOW_ADRESS) && (tempBank == HIGH_ADRESS) )
              {
                DebugFlag |= CODE_ADRESS_MATE;
                SaveCodeAddress = SAVE_CODE_ADDRESS2_1;
                DebugFlag |= CODE_BANK_LOW;
                //Clock.UpLineSecond = 0;
              }
            else if( (Bank == HIGH_ADRESS) && (tempBank ==LOW_ADRESS) )
              {
                DebugFlag |= CODE_ADRESS_MATE;
                SaveCodeAddress = SAVE_CODE_ADDRESS1;
                DebugFlag &= ~CODE_BANK_LOW;
                //Clock.UpLineSecond = 0;
              }
            SenAckPacket.uiCmd = SNP_CMD_ENTER_UF;
            SenAckPacket.uiCmd |= Bank<<8;
          
        }
      break;    
      case SNP_CMD_SET_BASELINE:
      {
        if( SystemState == EVENT_DETECT )
        {         
            AdTime.EventOnTime = 0;
            BaseLineFlag &= ~READ_BASELINE_ON;
            BaseLineFlag &= ~READ_BASELINE;
            SenTime.BaseLineTime = 0;  
            memset(&StableBaseLineZ,0,sizeof(StableBaseLineZ)); 
            memset(&StableBaseLineX,0,sizeof(StableBaseLineX)); ;          
            memset(&OnBaseLineZ,0,sizeof(OnBaseLineZ));
            memset(&OnBaseLineX,0,sizeof(OnBaseLineX));                   
            AxisZ1Pam.OverThresCnt = 0;
            AxisX1Pam.OverThresCnt = 0;
        }
        SensorRest();      
        TimeSlotMode = SNP_PHR_TYPE_UP_LINE;  
        SenAckPacket.uiCmd = mytemp;
        ConfigFlags |= RECIVE_SEN_CFG;
        //SingleFlag |= SET_BASE_COMD;
        SystemState = INIT_BASE_LINE;
        ExtraFlags &= ~ON_GET_BASELINE;
        AdMagenticFlags &= ~BASELINE_GENERT;
        memset(&InitBaseline,0,sizeof(InitBaseline));
        memset(&EventBuff,0,sizeof(EventBuff)); 
        memset(&BaseLineBuff,0,sizeof(BaseLineBuff));
        AxisZ1Pam.pBaseLine = (float)Magnetic.AxisZ1;
        AxisX1Pam.pBaseLine = (float)Magnetic.AxisX1;       
        for(i=0;i<BUFF_NUM;i++)
           { BusEvent.BusNum[i].Day |= 0x80; }      
      }
      break;
    /*  case SNP_SET_TIMESLOT:
      {
       // TimeSlotMode = SNP_PACKET_TYPE_SEN_A;  
        TimeSlot.SenTimeSlotNum = mytemp>>8;
        SenAckPacket.uiCmd = mytemp;
        SetFlags |= SET_TIMESLOT_FLAG;
      //  TimeCommunicatFlag &= ~STATE_SEND_ON;
        DownLineConfig();
      }
      break;*/
      case SET_ID:
      {
        //TimeSlotMode = SNP_PACKET_TYPE_SEN_A;  
        ChangLastID = RfParamt.SenID;
        RfParamt.SenID = mytemp>>8;
        RfParamt.SenID |= SenCfgPtr->Parmet<<8;
        SenAckPacket.uiCmd = mytemp;      
        SetFlags |= SET_ID_FLAG;
        ConfigFlags |= RECIVE_SEN_CFG; 
       // DownLineConfig();
      }
      break;
      /*case SER_SETBASE_Z:
      {
        //SetBaseLineZ = mytemp>>4;
        AxisZ1Pam.BaseLine =  mytemp>>4;
        SetBaseLineZ = AxisZ1Pam.BaseLine;
        TempBaseZ = AxisZ1Pam.BaseLine;
        BaseLineFlag |= BASELINE_UPDATA;
        ConfigFlags |= RECIVE_SEN_CFG; 
       // TimeCommunicatFlag &= ~STATE_SEND_ON;
        SenAckPacket.uiCmd = mytemp;
        for(i=0;i<3;i++)
          { OffBaseBuffZ.Buff[i] = AxisZ1Pam.BaseLine; }           
      }
      break;*/
     /* case SET_SETBASE_X:
      {
       // SetBaseLineX = mytemp>>4;
        AxisX1Pam.BaseLine = mytemp>>4;
        SetBaseLineX = AxisX1Pam.BaseLine;
        TempBaseX = AxisX1Pam.BaseLine;
        BaseLineFlag |= BASELINE_UPDATA;
        ConfigFlags |= RECIVE_SEN_CFG; 
       // TimeCommunicatFlag &= ~STATE_SEND_ON;
        SenAckPacket.uiCmd = mytemp;
        for(i=0;i<3;i++)
          { OffBaseBuffX.Buff[i] = AxisX1Pam.BaseLine; }                
      }
      break;*/
      case SET_NEW_PUMP:
      {
        NewPumpL = mytemp>>8;
        NewPumpH = SenCfgPtr->Parmet;
        SenAckPacket.uiCmd = mytemp;
        ConfigFlags |= RECIVE_SEN_CFG; 
        SetFlags |= NEW_PUMP_GET;
       // TimeCommunicatFlag &= ~STATE_SEND_ON;
      }
      break;
    case SET_RF_POWER:
      {
        gb_PowerBuf_Addr = mytemp>>8;
        SenAckPacket.uiCmd = mytemp;
        DebugFlag |= RF_POWER_SET;
        ConfigFlags |= RECIVE_SEN_CFG; 
       // DownLineConfig();
      }
      break;
      default:        
      break;
    }
  }
}

///**************************************************************************************************************////
void SenUfCfg(SNP_UF_DOWN_CODE_PACKET_t *SaveCodePtr)
{
  u16 temp;
  u16 i;
//  u8 tempBuffer[34];
  u8 *ptr;
  u16 pNum;
  u16 SumCheckNum;
  u16 RcvCheckNum;
  /* ptr = (u8 *)&SaveCodePtr->SenID;
 temp = *ptr++;
  temp |= *ptr<<8;
  if(temp != RfParamt.SenID)
  { 
    if( temp == 0xffff )      
        return;
  }*/
  ptr = (u8 *)&SaveCodePtr->CurrentNum;
  pNum = *ptr++;
  pNum |= *ptr<<8;
  if( pNum != (CodeBuffer.LastReciveNum+1) )     //返回错误信息
  {                       
    DownCodeFlag = 1;
    return;
  }
  if( pNum == 1)
  {
    ptr = (u8 *)&SaveCodePtr->AllNum;
    CodeBuffer.AllNum = *ptr++;
    CodeBuffer.AllNum |= *ptr<<8;
    
    CodeBuffer.Page512Num = (CodeBuffer.AllNum - 2)<<5;
    temp = CodeBuffer.Page512Num & 0x01FF;
    CodeBuffer.Page512Num = CodeBuffer.Page512Num>>9;  
    if(temp > 0)
    {
      CodeBuffer.Page512Num += 1;
      CodeBuffer.Rum32Num = temp;
    }
    else
    {
      CodeBuffer.Rum32Num = 512;
    }
  } 
  temp = CodeBuffer.AllNum - pNum;
  if( temp > 1 )
  {
    for(i=0;i<32;i++)
      { 
        CodeBuffer.Buff[CodeBuffer.BuffPtr] =  SaveCodePtr->CodeData[i];
        UfAckPacket.Data[i] = SaveCodePtr->CodeData[i];
        CodeBuffer.BuffPtr++;
      }
    if( CodeBuffer.Page512Num > 1 )
    { 
       if( CodeBuffer.BuffPtr == 512 )
        {
          SumCheckNum = 0;
          ptr = &CodeBuffer.Buff[0];
          for(i=0;i<512;i++)
            { SumCheckNum += *ptr++; }
         EraseSectorFlash( SaveCodeAddress);
          FlashWrite(SaveCodeAddress, &CodeBuffer.Buff[0], 512);        
          FlashRead(SaveCodeAddress, &CodeBuffer.Buff[0], 512);
          RcvCheckNum = 0;
          ptr = &CodeBuffer.Buff[0];
          for(i=0;i<512;i++)
            { RcvCheckNum += *ptr++; }
          if( RcvCheckNum == SumCheckNum )
            {
               SaveCodeAddress += 512;
               if( (DebugFlag & CODE_BANK_LOW) && (SaveCodeAddress == SAVE_CODE_END2_1) )
                 { SaveCodeAddress = SAVE_CODE_ADDRESS2_2; }
               CodeBuffer.Page512Num--;
               memset(&CodeBuffer.Buff[0], 0xff, 512);
               CodeBuffer.BuffPtr = 0;
            }
          else
            {
              delay_ms(500);
              delay_ms(500);
              delay_ms(500);              
              Sys_Soft_Reset(); 
            }
        }
    }
    else
    {    
      if(CodeBuffer.BuffPtr == CodeBuffer.Rum32Num)
        {
          SumCheckNum = 0;
          ptr = &CodeBuffer.Buff[0];
          for(i=0;i<512;i++)
            { SumCheckNum += *ptr++; }
          EraseSectorFlash( SaveCodeAddress);
          FlashWrite(SaveCodeAddress, &CodeBuffer.Buff[0], 512);
          FlashRead(SaveCodeAddress, &CodeBuffer.Buff[0], 512);              
          RcvCheckNum = 0;
          ptr = &CodeBuffer.Buff[0];
          for(i=0;i<512;i++)
            { RcvCheckNum += *ptr++; }
          if( RcvCheckNum == SumCheckNum )
            {
              SaveCodeAddress += 512;
              CodeBuffer.Page512Num--;
              memset(&CodeBuffer.Buff[0], 0xff, 512);
              CodeBuffer.BuffPtr = 0;
            }
          else
           {       
              delay_ms(500);
              delay_ms(500);
              delay_ms(500);              
              Sys_Soft_Reset(); 
           }
        }
    }
    DownCodeFlag = 2;
    CodeBuffer.LastReciveNum = pNum;
  }
  else if( temp == 1 )
   {
      for(i=0;i<32;i++)
        { IntVecBuff[i] = SaveCodePtr->CodeData[i]; }  
      DownCodeFlag = 2;
      CodeBuffer.LastReciveNum = pNum;
   }
  else //  实际中断向量存储
  {
    for(i=0;i<32;i++)
      { IntVecBuff[i+32] = SaveCodePtr->CodeData[i]; }   
    IntVecBuff[64] = 0xAA;
    IntVecBuff[65] = 0xAA;
    SumCheckNum = 0;
    ptr = &IntVecBuff[0];
    for(i=0;i<66;i++)
      { SumCheckNum += *ptr++; }
    FlashWrite(SegmentD, (u8 *)&IntVecBuff[0],66);
    FlashRead(SegmentD, (u8 *)&IntVecBuff[0],66);
    RcvCheckNum = 0;
    ptr = &IntVecBuff[0];
    for(i=0;i<66;i++)
      { RcvCheckNum += *ptr++; }
    if( RcvCheckNum == SumCheckNum )
    {
       DownCodeFlag = 3;
       CodeBuffer.LastReciveNum = pNum; 
       memset(&CodeBuffer, 0 ,sizeof(CodeBuffer));
       memset(&CodeBuffer.Buff[0], 0xff, 512);
      //SaveCodeAddress = SAVE_CODE_ADDRESS;
    }
    else
       {       
           delay_ms(500);
           delay_ms(500);
           delay_ms(500);              
           Sys_Soft_Reset(); 
       }
   
  }
}