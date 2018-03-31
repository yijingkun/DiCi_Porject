#include "types.h"
#include "magentic.h"
#include "ad.h"
#include "timeslot.h"
#include "cfg.h"
#include "flash.h"
#include <string.h>
//*****************************************************test**************
#include "board.h"
#include "uart.h"

/**********************************************************
//AD数据采集程序，暂时不用更改
*************************************************************/
extern u16 DebugFlag;
extern LAST_SEND_PACKET LastSend;
extern SNP_SEN_CFG_ACK_PACKET_t SenAckPacket;
extern SNP_STATE_PACKET_t StatePacket;
extern CLOCK_VALUE Clock;
extern FLASH_PARAMTER_t  FlashParamt;
extern TIME_SLOT_PARMAT TimeSlot;
extern MAGNETIC_VALUE Magnetic;
extern RF_PARAMTER RfParamt;
extern AD_TIME_CYCLE AdTime;
extern u16 TimeCommunicatFlag;
extern ADD_SLOT_NUM  AddSlotNum;
extern u16 ConfigFlags;
extern u16 LastBaseLineZ;
extern u16 LastBaseLineX;
extern u16 ReportTime;
extern u8 TimeSlotMode;
extern u8 RfSendFlags;
extern u8 NewLineOFF;
extern u8 SysTimeSlot;
extern u16 SetFlags ;
extern u8 Tap;
extern u8 time;
extern u8 ReSendNumE;
extern u8 OnNum;
extern u8 OffNum;
extern u8 OffSendNum;
extern u8 OffTempBaseSecond;
extern u8 BaseAverageNum;
extern u8 BaseBuffZPtr;
extern u8 BaseBuffXPtr;
extern u16 FlashBaseBuffZ[BASE_BUFF_NUM];
extern u16 FlashBaseBuffX[BASE_BUFF_NUM];
extern u16 SenRestSecond;
extern COMP_CNT OffBaseCnt;
extern COMP_CNT OldBaseCnt;
extern COMP_CNT NewBaseCnt;
extern COMP_CNT BaseBuffCnt[BASE_BUFF_NUM];


INIT_BASELINE           InitBaseline;
STABLE_BASELINE         StableBaseLineZ;
SENSOR_SAMPLE_PARAMTER  AxisZ1Pam;

STABLE_BASELINE         StableBaseLineX;
SENSOR_SAMPLE_PARAMTER  AxisX1Pam;

STABLE_BASELINE        OnStableBaseLineZ;
BASELINE_THREE_BUFF    OnBaseLineBuffZ;
SENSOR_SAMPLE_PARAMTER OnBaseLineZ;

STABLE_BASELINE        OnStableBaseLineX;
BASELINE_THREE_BUFF    OnBaseLineBuffX;
SENSOR_SAMPLE_PARAMTER OnBaseLineX;

SENSOR_SAMPLE_PARAMTER OnTempBaseZ;
BASELINE_THREE_BUFF    OnTempBaseBuffZ;

SENSOR_SAMPLE_PARAMTER OnTempBaseX;
BASELINE_THREE_BUFF    OnTempBaseBuffX;

SENSOR_TIME_PARAMTER  SenTime;

SENSOR_SAMPLE_PARAMTER    OffTempBaseZ;
BASELINE_THREE_BUFF     OffTempBaseBuffZ;

SENSOR_SAMPLE_PARAMTER    OffTempBaseX;
BASELINE_THREE_BUFF     OffTempBaseBuffX;


SENSOR_SAMPLE_PARAMTER     NearstBaseLineZ;
BASELINE_THREE_BUFF        NearstBaseBuffZ;

SENSOR_SAMPLE_PARAMTER     NearstBaseLineX;
BASELINE_THREE_BUFF        NearstBaseBuffX;

SENSOR_SAMPLE_PARAMTER     OneAdxiBaseZ;
BASELINE_THREE_BUFF        OneAdxiBaseBuffZ;

SENSOR_SAMPLE_PARAMTER     OneAdxiBaseX;
BASELINE_THREE_BUFF        OneAdxiBaseBuffX;

ON_EVENT_TIME OnEventTimeZ;
ON_EVENT_TIME OnEventTimeX;

AVERAGE_VALUE TempValueZ;
AVERAGE_VALUE TempValueX;

AVERAGE_VALUE OtherTempValueZ;
AVERAGE_VALUE OtherTempValueX;

AVERAGE_VALUE  OnTempValueZ;
AVERAGE_VALUE  OnTempValueX;

TEMP_BASE_BUFF OnTempValueBuffZ;
TEMP_BASE_BUFF OnTempValueBuffX;

OFF_AVERAGR_VALUE  OffTempValueZ;
OFF_AVERAGR_VALUE  OffTempValueX;

extern  EVENT_BUFF  EventBuff;
BUS_EVENT_BUFF BusEvent;

//ON_NUM_BUFF OnNumBuff;
TEMP_CHG_BASE ChangeBaseBuff[2];
u8 ChangBasPtr = 0;

LAST_EVENT LastEvent;
ON_BASELINE_BUFF BaseLineBuff;
OFF_BASELINE_BUFF OffBaseBuffZ;
OFF_BASELINE_BUFF OffBaseBuffX;


//u16 OnBaselineTime;
u16 OnGreatEventZ;
u16 OnSmallEventZ;
u16 OnGreatEventX;
u16 OnSmallEventX;
//u16 LastOnBaseZ;
//u16 LastOnBaseX;
u16 AdMagenticFlags;
u16 BaseLineFlag;
u16 HalfBaseLineFlag;
u16 OnBaseLineFlag;
u16 ExtraFlags;
u16 LastOnBaseLineZ;
u16 LastOnBaseLineX;
u16 SetBaseLineZ;
u16 SetBaseLineX;
//u16 BigDecectZ;
//u16 BigDecectX;
u16 HalfEventCntZ;
u16 HalfEventCntX;
u16 SingleFlag;
u16 LastCritcalZ;
u16 LastCritcalX;
u16 TempPositiveCntZ;
u16 TempNegitiveCntZ;
u16 TempPositiveCntX;
u16 TempNegitiveCntX;
u8 SystemState;
u8 DetectValue;
u8 ApDetectValue;
u8 DecValueZ;
u8 DecValueX;
u8 BasAddNumZ;
u8 BasAddNumX;
u8 BasDecNumZ;
u8 BasDecNumX;
u8 BasCountZ;
u8 BasCountX;
u16 BaseChgOnIntZ;
u16 BaseChgOnIntX;
u16 TempBaseFlag;
u16 OnMinute;
u16 OffMinute;
u16 TempBaseZ;
u16 TempBaseX;
u16 CompFlags = 0;
u8  TempBaseSecond;
u8  OnBaseUpdateNum = 0;
//u8  OnBaseChangeNum = 0;
u8  BaseOffNum = 0;

//u8  OnGetTime;
//u8  OnLowNumZ;
//u8  OnLowNumX;
u8  MaxOffNum;
u8  pEventHour;
u8  pEventMinute;
u8  pEventSecond;
u8  UnDetectValue;
u8  OffBaseNumZ = 0;
u8  OffBaseNumX = 0;
//u8  BaseAutoSet = 0;
u16  BaseZUpdateTime = 0;
u16  BaseXUpdateTime = 0;
u16  OldBaseZTemp;
u16  OldBaseXTemp;
u8   OffBaseOffedNum = 0;
//u16  OffBaseLineZ;
//u16  OffBaseLineX;
//u8   OffNumZ;
//u8   OffNumX;
//u8   TempBaseDayCnt = 0;
//u8   OldBaseDayCnt = 0;
u8   OnBaseGetNumZ;
u8   OnBaseGetNumX;
u16  pOnBaseLineZ;
u16  pBaseLineTempZ;
u16  pOnBaseLineX;
u16  pBaseLineTempX;
//u8   OffBaseOpen = ON;
u8   OneAxisCntZ;
u8   OneAxisCntX;
u8   EventOffFlag = ON;
//u8   OnBaseMoved = 0;
//u8   MinTrgge = 0;
u8   OnTime = 40;
u8   OffTime;
u8   EventChangTime;
u8   BaseBuffTime;
u8   AverageValueTime;
u16  NewBaseFlag;
u8   TempBaseOffNumZ;
u8   TempBaseOffNumX;
u8   OffBaseGetTime;
u8   DecMaxAd;
/*
u8   OffValueCntBuffZ[12];
u8   OffValueCntBuffX[12];
u8   OffValueCntBuffZPtr;
u8   OffValueCntBuffXPtr;
u8   OffValueCntZ;
u8   OffValueCntX;*/
u8   OffValueCntBuffNum;
OFF_MIN_VALUE_BUFF  MinOffBuffZ;
OFF_MIN_VALUE_BUFF  MinOffBuffX;
//u8   BigTrigBase;
//u8 Pcntz;
//u8 Pcntx;

//u8  OnBaseGetNumZ;
//u8  OnBaseGetNumX;

//u8 InitBaseLineCount;
//u8 ReEventCount;
//u8 ReEventNum;
//u8 TriggerReport = 0;
//u16 Time1;
//u16 Time2;
//AD_BUFF AdBuff;
 
//******************************************************************
//u8 ttt1=0;
//u8 ttt2=0;
//u8 DectZ;
//u8 DectX;
//u8 TrigZ;
//u8 TrigX;
//u8 tset1=0;
void InitMagenticParamter(void)
{
  u8 i;
  memset(&AxisX1Pam,0,sizeof(AxisX1Pam));
  memset(&AxisZ1Pam,0,sizeof(AxisZ1Pam));
  memset(&SenTime,0,sizeof(SenTime));
  memset(&BusEvent,0,sizeof(BusEvent));
  memset(&EventBuff,0,sizeof(EventBuff)); 
  memset(&InitBaseline,0,sizeof(InitBaseline));   
  memset(&OnStableBaseLineZ,0,sizeof(OnStableBaseLineZ));  
  memset(&OnBaseLineZ,0,sizeof(OnBaseLineZ));
  memset(&OnStableBaseLineX,0,sizeof(OnStableBaseLineX));  
  memset(&OnBaseLineX,0,sizeof(OnBaseLineX));
  memset(&NearstBaseLineZ,0,sizeof(NearstBaseLineZ));
  memset(&NearstBaseBuffZ,0,sizeof(NearstBaseBuffZ));
  memset(&NearstBaseLineX,0,sizeof(NearstBaseLineX));
  memset(&NearstBaseBuffX,0,sizeof(NearstBaseBuffX));  //
  memset(&OnTempBaseZ,0,sizeof(OnTempBaseZ));
  memset(&OnTempBaseX,0,sizeof(OnTempBaseX)); //
  memset(&OnTempBaseBuffZ,0,sizeof(OnTempBaseBuffZ)); 
  memset(&OnTempBaseBuffX,0,sizeof(OnTempBaseBuffX)); //
  memset(&OffBaseBuffZ,0,sizeof(OffBaseBuffZ));  
  memset(&OffBaseBuffX,0,sizeof(OffBaseBuffX));  
 // memset(&EventBuff,0,sizeof(EventBuff));  OffTempBaseBuffZ OffTempBaseZ
  memset(&OffTempBaseZ,0,sizeof(OffTempBaseZ)); 
  memset(&OffTempBaseBuffZ,0,sizeof(OffTempBaseBuffZ)); 
  memset(&OffTempBaseX,0,sizeof(OffTempBaseX)); 
  memset(&OffTempBaseBuffX,0,sizeof(OffTempBaseBuffX)); //
  memset(&OnTempValueBuffZ,0,sizeof(OnTempValueBuffZ));
  memset(&OnTempValueBuffX,0,sizeof(OnTempValueBuffX));
  for(i=0;i<BUFF_NUM;i++)
  { BusEvent.BusNum[i].Day |= 0x80; }

 // AdMagenticFlags = 0; 
  ExtraFlags = 0;
  BaseLineFlag = 0;
  HalfBaseLineFlag = 0;
  OnBaseLineFlag = 0;
 // SingleFlag = 0;
  TempBaseFlag = 0;
  BasAddNumZ = 0;
  BasAddNumX = 0;
  BasDecNumZ = 0;
  BasDecNumX = 0;
  BasCountZ = 0;
  BasCountX = 0;
  NewBaseFlag = 0;
  DecMaxAd = 20;
  OffBaseGetTime = 10;
  AdTime.EventPrimaryTime = 0;
  //EventErrNum = 0;
  OffTime = 64;
  OffValueCntBuffNum = 8;
  EventChangTime = OffTime + 24;
  BaseBuffTime = OffTime + 40;
  AverageValueTime = OffTime + 24;
  AdMagenticFlags &= ~EVENT_STABLE;
}


void  UpdataBasline(u16 pAdValue,SENSOR_SAMPLE_PARAMTER *AxisPam)
{
  float pValue;
  pValue=(float) pAdValue;
  if(pValue > AxisPam->pBaseLine)
    {
      pValue -= AxisPam->pBaseLine; //B(k)=B(k-1)*(1-a)+A(k)*a  a=0.05  ~~6/128
      pValue*=0.05;
      AxisPam->pBaseLine += pValue;          
    }
  else
    {
      pValue =  AxisPam->pBaseLine - pValue;
      pValue*=0.05;
      AxisPam->pBaseLine -= pValue;          
    }   
}


void SystemScan(void)
{
  u16 tempZ;
  u16 tempX;
  u16 temp3;
  u16 temp4;
  u8 i;
  u16 temp;
  u8 dec;
  switch (SystemState)
  {
    case INIT_BASE_LINE:                         
      {     
          AdMagenticFlags &= ~Z_BASELINE_SUIT;
          AdMagenticFlags &= ~X_BASELINE_SUIT;
          tempZ = (u16)AxisZ1Pam.pBaseLine;
          tempX = (u16)AxisX1Pam.pBaseLine;
          if(Magnetic.AxisZ1 > tempZ)
            { tempZ = Magnetic.AxisZ1 - tempZ; }
          else
            { tempZ = tempZ - Magnetic.AxisZ1;  }  
          if( tempZ < 20) 
             { AdMagenticFlags |= Z_BASELINE_SUIT; }
          
          if(Magnetic.AxisX1 > tempX)
           { tempX = Magnetic.AxisX1 - tempX; }
          else
           { tempX = tempX - Magnetic.AxisX1; }
          if( tempX < 15)
           { AdMagenticFlags |= X_BASELINE_SUIT; }
          
          if( (AdMagenticFlags & Z_BASELINE_SUIT) && (AdMagenticFlags & X_BASELINE_SUIT) )
            {
              UpdataBasline(Magnetic.AxisZ1,&AxisZ1Pam);
              UpdataBasline(Magnetic.AxisX1,&AxisX1Pam);  
              SenTime.BaseLineTime++;
             // AdTime.OverTheraCnt = 0;
              if(SenTime.BaseLineTime >= BASE_LING_DELAY)
                {                 
                  SenTime.BaseLineTime = 0;       
                  if( !(AdMagenticFlags & BASELINE_GENERT) )
                  {
                    if( InitBaseline.Num < 3 ) 
                      {
                        InitBaseline.BaseLineZ[InitBaseline.Num] = (u16)AxisZ1Pam.pBaseLine; 
                        InitBaseline.BaseLineX[InitBaseline.Num] = (u16)AxisX1Pam.pBaseLine;   
                        InitBaseline.Num++;                       
                      }
                    else
                     {
                       if( InitBaseline.BaseLineZ[0] > InitBaseline.BaseLineZ[1] )
                           { tempZ = InitBaseline.BaseLineZ[0] - InitBaseline.BaseLineZ[1]; }
                       else
                           { tempZ = InitBaseline.BaseLineZ[1] - InitBaseline.BaseLineZ[0]; }
                       if( InitBaseline.BaseLineZ[0] > InitBaseline.BaseLineZ[2] )
                           { temp3 = InitBaseline.BaseLineZ[0] - InitBaseline.BaseLineZ[2]; }
                       else
                           { temp3 = InitBaseline.BaseLineZ[2] - InitBaseline.BaseLineZ[0]; }
                       if( InitBaseline.BaseLineX[0] > InitBaseline.BaseLineX[1] )
                           { tempX = InitBaseline.BaseLineX[0] - InitBaseline.BaseLineX[1]; }
                       else
                           { tempX = InitBaseline.BaseLineX[1] - InitBaseline.BaseLineX[0]; }
                       if( InitBaseline.BaseLineX[0] > InitBaseline.BaseLineX[2] )
                           { temp4 = InitBaseline.BaseLineX[0] - InitBaseline.BaseLineX[2]; }
                       else
                           { temp4 = InitBaseline.BaseLineX[2] - InitBaseline.BaseLineX[0]; }
                       if( (tempZ<2) && (temp3<2) && (tempX<2) && (temp4<2) )
                       {
                          AxisZ1Pam.BaseLine = InitBaseline.BaseLineZ[0];
                          AxisX1Pam.BaseLine = InitBaseline.BaseLineX[0];  
                          AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
                          AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
                          SetBaseLineZ = AxisZ1Pam.BaseLine;
                          SetBaseLineX = AxisX1Pam.BaseLine;
                          TempBaseZ = AxisZ1Pam.BaseLine;
                          TempBaseX =  AxisX1Pam.BaseLine;
                          SystemState = ON_BASE_LINE;   
                          AxisZ1Pam.OverThresCnt = 0;
                          AdMagenticFlags |= BASELINE_GENERT;  
                          //SingleFlag |= BASE_LINE_ON;
                          BaseLineFlag |= BASELINE_UPDATA;                         
                          LastBaseLineZ = AxisZ1Pam.BaseLine;
                          LastBaseLineX = AxisX1Pam.BaseLine;                                                      
                          //ConfigFlags |= RECIVE_SEN_CFG;                         
                          //ConfigFlags |= SEN_UP_LINE; 
                          BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                          BaseLineFlag &= ~BS_SMOOTH_UP_X;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_X;         
                       ConfigFlags |= RECIVE_SEN_CFG;                         
                       ConfigFlags |= SEN_UP_LINE; 
                      // DebugFlag &= ~SEN_WEAKUP_ON;
                         TimeCommunicatFlag |= STATE_SEND_ON; 
                         SenAckPacket.uiCmd = SNP_BASELINE_GET;
                          Clock.DelayUplineScan = STATE_RF_DELAY; 
                      /*    pHour = TimeSlot.Hour;
                          pMinute = TimeSlot.Minute;
                          pSecond = TimeSlot.Second;
                          TimeSlot.Hour = 0;
                          TimeSlot.Minute = 0;
                          TimeSlot.Second = 0;                       
                          SaveEvent(OFF);
                          TimeSlot.Hour = pHour;
                          TimeSlot.Minute = pMinute;
                          TimeSlot.Second = pSecond;*/
                          if(SingleFlag & LAST_EVENT_ON)
                            { SaveEvent(OFF); }
                          memset(&InitBaseline,0,sizeof(InitBaseline)); 
                          memset(&StableBaseLineZ,0,sizeof(StableBaseLineZ)); 
                          memset(&StableBaseLineX,0,sizeof(StableBaseLineX)); 
                          for(i=0;i<3;i++)
                          {
                            OffBaseBuffZ.Buff[i] = AxisZ1Pam.BaseLine;
                            OffBaseBuffX.Buff[i] = AxisX1Pam.BaseLine;
                          }
#if STRING_ON                          
 UartSendStrings("BaseLine Get"); 
  UartSendStrings("\r\n");  
#endif                         
                       }
                       else
                       {
                         memset(&InitBaseline,0,sizeof(InitBaseline));
                         SystemState = INIT_BASE_LINE;   
                       }
                     }
                    
                  }
                }
              else
               { SystemState = INIT_BASE_LINE; }
             }
          else
           {
               SystemState = INIT_BASE_LINE;                
               AxisZ1Pam.pBaseLine = (float)Magnetic.AxisZ1;
               AxisX1Pam.pBaseLine = (float)Magnetic.AxisX1;
               SenTime.BaseLineTime = 0;                   
           }
      }
    break;
    case ON_BASE_LINE:      
      {       
          if(Magnetic.AxisZ1 > AxisZ1Pam.BaseLine)
              { tempZ = Magnetic.AxisZ1 - AxisZ1Pam.BaseLine; }
          else
              { tempZ = AxisZ1Pam.BaseLine - Magnetic.AxisZ1;  }  
          if(Magnetic.AxisX1 > AxisX1Pam.BaseLine)
              { tempX = Magnetic.AxisX1 - AxisX1Pam.BaseLine; }
          else
              { tempX = AxisX1Pam.BaseLine - Magnetic.AxisX1; } 
          
          AdMagenticFlags &= ~EVENT_GENERAT;
          if( BaseLineFlag & READ_BASELINE )
          {
            if( (tempZ >= DetectValue) || (tempX >= DetectValue) )
               { 
                 AdMagenticFlags |= EVENT_GENERAT;
                 BaseLineFlag |= READ_BASELINE_ON;
               }
          }
          else
          {             
             if( (tempZ >= DetectValue) || (tempX >= DetectValue) )   
                {  AdMagenticFlags |= EVENT_GENERAT;  }  
          }
          if( (AdMagenticFlags & EVENT_GENERAT) && (!(ExtraFlags & BASELINE_CALIBRAT_Z)) && (!(ExtraFlags & BASELINE_CALIBRAT_X)) )
            {            
              AxisZ1Pam.OverThresCnt++;  
              if(AxisZ1Pam.OverThresCnt >= ON_SET_FILTER)   //1次
                 { JumpToEventON(); }   
            }
          else 
            { 
               AxisZ1Pam.OverThresCnt = 0;
               SystemState = ON_BASE_LINE;                    
               BaseLineUpdataZ();
               BaseLineUpdataX();
          if( CompFlags & OFF_BASELINE_GET_Z )  
            {
              UpdataBasline(Magnetic.AxisZ1, &OffTempBaseZ);  
              OffTempBaseBuffZ.Count++;
              if( OffTempBaseBuffZ.Count >= BASE_LING_DELAY )
                 {           
                    CompFlags &= ~OFF_BASELINE_GET_Z;
                    OffTempBaseBuffZ.Count = 0;
                    OffTempBaseBuffZ.BaseLine[OffTempBaseBuffZ.Num++]= (u16)OffTempBaseZ.pBaseLine;
                    temp3 = (u16)OffTempBaseZ.pBaseLine;                         
                    if(OffTempBaseBuffZ.Num >= 3)
                       { OffTempBaseBuffZ.Num = 0;}
             
                    temp3 = 0;
                    temp4 = DecBase( OffTempBaseBuffZ.BaseLine[0], OffTempBaseBuffZ.BaseLine[1] );
                    if( temp4 == 1 )
                     { temp3++; }
                    temp4 = DecBase( OffTempBaseBuffZ.BaseLine[0], OffTempBaseBuffZ.BaseLine[2] );
                    if( temp4 == 1 )
                      { temp3++; }
                    temp4 = DecBase( OffTempBaseBuffZ.BaseLine[1], OffTempBaseBuffZ.BaseLine[2] );
                    if( temp4 == 1 )
                      { temp3++; }
                    if(temp3 >= 3)
                    {
                      temp4 = OffTempBaseBuffZ.BaseLine[0] + OffTempBaseBuffZ.BaseLine[1] + OffTempBaseBuffZ.BaseLine[2];
                      temp4 /= 3;
                      OffTempBaseZ.BaseLine = temp4;   
                      NewBaseFlag |= OFF_BASE_GET_Z;
                      if( NewBaseFlag & OFF_BASE_GET_X )
                        { OffBaseGetTime = 60; }                
                    }
                 }
             }
          if( CompFlags & OFF_BASELINE_GET_X)
          {
            UpdataBasline(Magnetic.AxisX1, &OffTempBaseX);  
            OffTempBaseBuffX.Count++;
            if( OffTempBaseBuffX.Count >= BASE_LING_DELAY )
            {           
              CompFlags &= ~OFF_BASELINE_GET_X;
              OffTempBaseBuffX.Count = 0;
              OffTempBaseBuffX.BaseLine[OffTempBaseBuffX.Num++]= (u16)OffTempBaseX.pBaseLine;
              if(OffTempBaseBuffX.Num >= 3)
                 { OffTempBaseBuffX.Num = 0;}            
              temp3 = 0;
              temp4 = DecBase( OffTempBaseBuffX.BaseLine[0], OffTempBaseBuffX.BaseLine[1] );
              if( temp4 == 1 )
                { temp3++; }
              temp4 = DecBase( OffTempBaseBuffX.BaseLine[0], OffTempBaseBuffX.BaseLine[2] );
              if( temp4 == 1 )
                { temp3++; }
              temp4 = DecBase( OffTempBaseBuffX.BaseLine[1], OffTempBaseBuffX.BaseLine[2] );
              if( temp4 == 1 )
                { temp3++; }
              if(temp3 >= 3)
              {
                temp4 = OffTempBaseBuffX.BaseLine[0] + OffTempBaseBuffX.BaseLine[1] + OffTempBaseBuffX.BaseLine[2];
                temp4 /= 3;
                OffTempBaseX.BaseLine = temp4;   
                NewBaseFlag |= OFF_BASE_GET_X;
                if( NewBaseFlag & OFF_BASE_GET_Z )
                  { OffBaseGetTime = 60; }               
              }
            }
          }
           if(NewBaseFlag & MAX_THRES_VALUE_Z)  
             {
                tempZ = AverageAdGet( &OffTempValueZ, Magnetic.AxisZ1 );
                if( tempZ == 1 )
                {         
                   temp3 = DecBigTerg( OffTempValueZ.Value, AxisZ1Pam.BaseLine,4);
                   if( temp3 == 1 )
                    { 
                      NewBaseFlag &= ~MAX_THRES_VALUE_Z;
                      if( (!(NewBaseFlag & MAX_THRES_VALUE_X)) && ( (!(NewBaseFlag & ADD_THRES_VALUE_Z)) || (!(NewBaseFlag & ADD_THRES_VALUE_X)) ) )
                         { DetectValue = ApDetectValue; }         
                    }
                }
             }
           if( NewBaseFlag & MAX_THRES_VALUE_X )
             {
               tempX = AverageAdGet( &OffTempValueX, Magnetic.AxisX1 );
               if( tempX == 1 )
               {       
                 temp3 = DecBigTerg( OffTempValueX.Value, AxisX1Pam.BaseLine,4);
                 if( temp3 == 1 )
                   {  
                     NewBaseFlag &= ~MAX_THRES_VALUE_X;
                     if( (!(NewBaseFlag & MAX_THRES_VALUE_Z)) && ( (!(NewBaseFlag & ADD_THRES_VALUE_Z)) || (!(NewBaseFlag & ADD_THRES_VALUE_X)) ) )
                       { DetectValue = ApDetectValue; }          
                   }
               }
             }
             if( HalfBaseLineFlag & GET_NEREST_BASELINE_Z )
               {
                 temp = 0;
                 if( OffMinute > OnMinute )
                   { temp = OffMinute - OnMinute; }
                if(temp >= 2) //2**************************************************************
                {
                 tempZ = GetBaseLineAny( Magnetic.AxisZ1, &NearstBaseLineZ, &NearstBaseBuffZ); 
                 if( tempZ > 1 )
                 {       
                    HalfBaseLineFlag &= ~GET_NEREST_BASELINE_Z;
                    ExtraFlags &= ~BASELINE_CALIBRAT_Z;
                    OffBaseBuffZ.Buff[OffBaseBuffZ.SavePtr] = tempZ;
                    OffBaseBuffZ.SavePtr++;
                    if( OffBaseBuffZ.SavePtr >= OFF_BUF_NUM )
                      { OffBaseBuffZ.SavePtr = 0; }
                   // temp3 = DecBigTerg( tempZ, AxisZ1Pam.BaseLine,4);
                   // if( (temp3 == 1) && (NewBaseFlag & MAX_THRES_VALUE_Z) )
                    //  {  NewBaseFlag &= ~MAX_THRES_VALUE_Z;  }
                    temp3 = 0;
                    temp4 = DecBase( OffBaseBuffZ.Buff[0], OffBaseBuffZ.Buff[1] );
                    if( temp4 == 1 )
                     { temp3++; }
                    temp4 = DecBase( OffBaseBuffZ.Buff[0], OffBaseBuffZ.Buff[2] );
                    if( temp4 == 1 )
                      { temp3++; }
                    temp4 = DecBase( OffBaseBuffZ.Buff[1], OffBaseBuffZ.Buff[2] );
                    if( temp4 == 1 )
                      { temp3++; }                    
                    if( temp3 >= 3 )
                      { 
                        temp4 = OffBaseBuffZ.Buff[0] + OffBaseBuffZ.Buff[1] + OffBaseBuffZ.Buff[2];
                        temp4 /= 3;
                        dec = DecBase(AxisZ1Pam.BaseLine,temp4);                       
                        if(dec == 0)
                          { FlashBuffUpdateZ(); }
                        AxisZ1Pam.BaseLine = temp4;   
                        if( NewBaseFlag & MAX_THRES_VALUE_Z)
                          { 
                            NewBaseFlag &= ~MAX_THRES_VALUE_Z;
                            if( !(NewBaseFlag & MAX_THRES_VALUE_X) )
                              { DetectValue = ApDetectValue; }
                          }
                      } 
                  if(NewBaseFlag & TEMP_BASE_UPDATE_Z)
                   {
                      TempBaseOffNumZ++;      
                      if( TempBaseOffNumZ >= 2 )
                        {
                          TempBaseOffNumZ = 0;
                          FlashBuffUpdateZ();            
                         }
                   }
                 } 
                  
                }
                else
                 {
                   HalfBaseLineFlag &= ~GET_NEREST_BASELINE_Z;
                   ExtraFlags &= ~BASELINE_CALIBRAT_Z;
                 }
               }
             if( HalfBaseLineFlag & GET_NEREST_BASELINE_X )
              {      
                temp = 0;
                 if( OffMinute > OnMinute )
                   { temp = OffMinute - OnMinute; }
              if( temp >= 2)  //2*******************************************************
               {
                 tempX = GetBaseLineAny( Magnetic.AxisX1, &NearstBaseLineX, &NearstBaseBuffX); 
                 if( tempX > 1 )
                 {              
                   HalfBaseLineFlag &= ~GET_NEREST_BASELINE_X;
                   ExtraFlags &= ~BASELINE_CALIBRAT_X;
                   OffBaseBuffX.Buff[OffBaseBuffX.SavePtr] = tempX;
                   OffBaseBuffX.SavePtr++;
                   if( OffBaseBuffX.SavePtr >= OFF_BUF_NUM )
                      { OffBaseBuffX.SavePtr = 0; }
                  // temp3 = DecBigTerg( tempX, AxisX1Pam.BaseLine,4);
                  // if( (temp3 == 1) && (NewBaseFlag & MAX_THRES_VALUE_X) )
                   //  { NewBaseFlag &= ~MAX_THRES_VALUE_X;  }
                   temp3 = 0;
                   temp4 = DecBase( OffBaseBuffX.Buff[0], OffBaseBuffX.Buff[1] );
                   if( temp4 == 1 )
                     { temp3++; }
                   temp4 = DecBase( OffBaseBuffX.Buff[0], OffBaseBuffX.Buff[2] );
                   if( temp4 == 1 )
                     { temp3++; }
                   temp4 = DecBase( OffBaseBuffX.Buff[1], OffBaseBuffX.Buff[2] );
                   if( temp4 == 1 )
                     { temp3++; }
                   if( temp3 >= 3 )
                     { 
                       //OffNumX++;
                       temp4 = OffBaseBuffX.Buff[0] + OffBaseBuffX.Buff[1] + OffBaseBuffX.Buff[2];
                       temp4 /= 3;
                       dec = DecBase(AxisX1Pam.BaseLine,temp4);                       
                       if(dec == 0)
                       { FlashBuffUpdateX(); } 
                       AxisX1Pam.BaseLine = temp4;
                       NewBaseFlag &= ~MAX_THRES_VALUE_X;      
                       if( !(NewBaseFlag & MAX_THRES_VALUE_Z) )
                         { DetectValue = ApDetectValue;  }
                     }
                   if(NewBaseFlag & TEMP_BASE_UPDATE_X)
                    {
                       TempBaseOffNumX++;
                       if( TempBaseOffNumX >= 2)
                         {
                           TempBaseOffNumX = 0;
                           FlashBuffUpdateX();          
                          }
                     }
                 }                  
               }
               else
               {
                 HalfBaseLineFlag &= ~GET_NEREST_BASELINE_X;
                 ExtraFlags &= ~BASELINE_CALIBRAT_X; 
               }
              } 
            }
      }
    break;
    case  EVENT_DETECT:                    //EVENT_DETECT:
    {   
      if( AdTime.EventPrimaryTime >= PRIMARY_EVENT_TIME )
      {
        AdMagenticFlags &= ~AD_EVENT_ON_PRIMARY;
        AdTime.EventPrimaryTime = 0;
        AdMagenticFlags |= EVENT_STABLE;
        AxisZ1Pam.OverThresCnt = 0;
        AxisX1Pam.OverThresCnt = 0;
        //SensorRest();
      }    
     // if( (AdMagenticFlags & EVENT_ON_SAVED) && (OnGetTime < OffTime) )
       // {  OnGetTime++; }
      EventSave(); 
    }
    break; 
    default:
    {
       SensorRest();
       AxisZ1Pam.OverThresCnt = 0;
       SystemState = ON_BASE_LINE;     
    }
    break;
  }
}


void JumpToEventON(void)
{
  AxisZ1Pam.OverThresCnt = 0;  
  AxisZ1Pam.LowThresCnt = 0;  
  AxisX1Pam.OverThresCnt = 0;  
  AxisX1Pam.LowThresCnt = 0;
  SenTime.BaseLineTime = 0;
  AdTime.EventOnTime = 0;
  DecValueZ = 0;
  DecValueX = 0;
 // OnGetTime = 0;
  //OnLowNumZ = 0;
 // OnLowNumX = 0;
  HalfEventCntZ = 0;
  HalfEventCntX = 0;
  TempPositiveCntZ = 0;
  TempNegitiveCntZ = 0;
  TempPositiveCntX = 0;
  TempNegitiveCntX = 0;
  AdTime.EventDetectSecond = 0;
  AdTime.EventPrimaryTime = 0;
  DetectValue = ApDetectValue;
  TempBaseFlag &= ~MAX_NUM_OFF;
  BaseLineFlag &= ~ON_BASELIN_GET;
  HalfBaseLineFlag &= ~ON_EVENT_ON_Z;
  HalfBaseLineFlag &= ~ON_EVENT_ON_X;
  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_Z;
  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_ON_Z; 
  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_X;
  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_ON_X; 
 // OnBaseLineFlag &= ~TEMP_BASE_SAVED_Z1;
 // OnBaseLineFlag &= ~TEMP_BASE_SAVED_X1;
  NewBaseFlag &= ~OFF_NUM_Z_ON;
  NewBaseFlag &= ~OFF_NUM_X_ON;
  ExtraFlags &= ~EVENT_OFF_SAVED;
  ExtraFlags &= ~ON_BASELIN_GENERT_Z;
  ExtraFlags &= ~ON_BASELIN_GENERT_X;
  ExtraFlags &= ~BIG_DECECT_Z;
  ExtraFlags &= ~BIG_DECECT_X;
  BaseLineFlag &= ~ON_EVENT_ON;
  BaseLineFlag &= ~ON_EVENT_BASELINE_RST;
  AdMagenticFlags |= AD_EVENT_ON_PRIMARY;
  //SingleFlag &= ~ON_CRITICAL_BAS_Z;
  //SingleFlag &= ~ON_CRITICAL_BAS_X;      
  SingleFlag &= ~BASELINE_NO_EFT_Z;
  SingleFlag &= ~BASELINE_NO_EFT_X;
  TempBaseFlag &= ~EVENT_EFFECT_X;
  HalfBaseLineFlag &= ~HALF_EVENT_Z;
  HalfBaseLineFlag &= ~HALF_EVENT_X;
  SingleFlag &= ~ON_CRITICAL_GENERT_Z;
  SingleFlag &= ~ON_CRITICAL_GENERT_X;
  ExtraFlags &= ~TEMP_BASE_ERR; 
  OnBaseLineFlag &= ~TEMP_ON_BASE_GET_Z;
  OnBaseLineFlag &= ~TEMP_ON_BASE_GET_X;
  AdMagenticFlags &= ~ON_EVENT_ON_SAVED;
  SingleFlag &= ~TEMP_BASE_SAVED_Z2;
  SingleFlag &= ~TEMP_BASE_SAVED_X2;
  OnBaseLineFlag &= ~TEMP_ON_TO_ON;
  SingleFlag &= ~CRITICAL_USED_Z;
  SingleFlag &= ~CRITICAL_USED_X;
  BaseLineFlag &= ~SMOOTH_UP_Z;
  BaseLineFlag &= ~SMOOTH_DOWN_Z;
  BaseLineFlag &= ~SMOOTH_UP_X;
  BaseLineFlag &= ~SMOOTH_DOWN_X;
  NewBaseFlag &= ~ON_GET_VALUE_START_Z;
  NewBaseFlag &= ~ON_GET_VALUE_START_X;
  OnBaseLineFlag &= ~DEC_VALUE_GENERATE_Z;
  OnBaseLineFlag &= ~DEC_VALUE_GENERATE_X;
  BaseLineFlag &= ~TEMP_BASE_CHANGED;
  AdMagenticFlags &= ~EVENT_STABLE;
  memset(&OnStableBaseLineZ,0,sizeof(OnStableBaseLineZ));
  memset(&OnBaseLineBuffZ,0,sizeof(OnBaseLineBuffZ));
  memset(&OnBaseLineZ,0,sizeof(OnBaseLineZ));
  memset(&OnStableBaseLineX,0,sizeof(OnStableBaseLineX));
  memset(&OnBaseLineBuffX,0,sizeof(OnBaseLineBuffX));
  memset(&OnBaseLineX,0,sizeof(OnBaseLineX));
 // memset(&OnNumBuff,0,sizeof(OnNumBuff));   
  memset(&OnTempBaseZ,0,sizeof(OnTempBaseZ));
  memset(&OnTempBaseX,0,sizeof(OnTempBaseX));
  memset(&OnTempBaseBuffZ,0,sizeof(OnTempBaseBuffZ)); 
  memset(&OnTempBaseBuffX,0,sizeof(OnTempBaseBuffX)); 
  if( BaseLineBuff.BaseNum == 0 )
     { memset(&BaseLineBuff,0,sizeof(BaseLineBuff));  }
  OnBaseLineZ.pBaseLine = Magnetic.AxisZ1;
  OnBaseLineX.pBaseLine = Magnetic.AxisX1;
  AdMagenticFlags |= ON_EVENT_SAVE;
  AdMagenticFlags &= ~EVENT_ON_SAVED;
  AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
  AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
  SingleFlag |= SINGLE_GET_ON;
  SystemState = EVENT_DETECT; 
  
#if STRING_ON
  UartSendStrings("to ON"); 
  UartSendStrings("\r\n");
#endif
}

//u8 testflag;
void EventSave(void)
{
   u16 ThresData;
   u16 tempZ;
   u16 tempX; 
   u16 temp3;
   u16 temp4;
   u8  TempDec1;
   u8  TempDec2;
 //  u8  BigDec1;
 //  u8  BigDec2;
   //u8  DatCnt[2];
   u8 i;

       if(Magnetic.AxisZ1 > AxisZ1Pam.BaseLine)
         { ThresData = Magnetic.AxisZ1 - AxisZ1Pam.BaseLine; }
       else
         { ThresData = AxisZ1Pam.BaseLine - Magnetic.AxisZ1; } 
       if( (ThresData >= HALF_EVENT_VALUE) && ( ThresData <= (ApDetectValue+2)) )
          { HalfEventCntZ++; }
       else
          { HalfEventCntZ = 0; }
       if( AdMagenticFlags & EVENT_ON_SAVED )
          { DetectValue = UnDetectValue; }
       else
          { DetectValue = ApDetectValue;  }

   if( HalfBaseLineFlag & HALF_EVENT_Z )
      { DetectValue = HALF_EVENT_VALUE; }
   if( (NewBaseFlag & MAX_THRES_VALUE_Z) || (NewBaseFlag & MAX_THRES_VALUE_X) )
      { DetectValue = 8; }
   if( (NewBaseFlag & ADD_THRES_VALUE_Z) && (NewBaseFlag & ADD_THRES_VALUE_X) )
      { DetectValue += 3; }
   if( ThresData < DetectValue )
      { 
        AxisZ1Pam.LowThresCnt++; 
        AxisZ1Pam.OverThresCnt = 0;
        if( AdMagenticFlags & EVENT_ON_SAVED )
          {  MinOffBuffZ.MinNum++;  }
      }
    else
      { 
        AxisZ1Pam.LowThresCnt = 0;  
        if( AdMagenticFlags & EVENT_STABLE )
         {  AxisZ1Pam.OverThresCnt++; } 
        if( ThresData > DecValueZ )
          { DecValueZ = ThresData; }
      }  
  if( AdMagenticFlags & EVENT_ON_SAVED )
  {
    MinOffBuffZ.MinCnt++;
      if( MinOffBuffZ.MinCnt >= 8 ) 
      {
        MinOffBuffZ.MinCnt = 0;
        MinOffBuffZ.CntBuff[MinOffBuffZ.BuffPtr++] = MinOffBuffZ.MinNum;
        if(MinOffBuffZ.BuffPtr >= OffValueCntBuffNum)
          { MinOffBuffZ.BuffPtr = 0; }
        MinOffBuffZ.AllCnt++;
        if( MinOffBuffZ.AllCnt >= OffValueCntBuffNum)
          {      
            MinOffBuffZ.AllOffNum = 0; 
            for(i=0;i<OffValueCntBuffNum;i++)
               { MinOffBuffZ.AllOffNum += MinOffBuffZ.CntBuff[i]; }
            if( MinOffBuffZ.AllOffNum >= MaxOffNum )
               { NewBaseFlag |= OFF_NUM_Z_ON; }
            else
               { NewBaseFlag &= ~OFF_NUM_Z_ON; }
            MinOffBuffZ.AllCnt -= 1;          
          }
      }
  }  
       if(Magnetic.AxisX1 > AxisX1Pam.BaseLine)
         { ThresData = Magnetic.AxisX1 - AxisX1Pam.BaseLine; }
       else
         { ThresData = AxisX1Pam.BaseLine - Magnetic.AxisX1; } 
      
       if( (ThresData >= HALF_EVENT_VALUE) && ( ThresData <= (ApDetectValue+2)) )
          { HalfEventCntX++; }
       else 
          { HalfEventCntX = 0; }
       if( AdMagenticFlags & EVENT_ON_SAVED )
          { DetectValue = UnDetectValue; }
       else
          {  DetectValue = ApDetectValue;  }
    if( HalfBaseLineFlag & HALF_EVENT_X )
       {  DetectValue = HALF_EVENT_VALUE; }
    if( (NewBaseFlag & MAX_THRES_VALUE_Z) || (NewBaseFlag & MAX_THRES_VALUE_X) )
      { DetectValue = 8; }
    if( (NewBaseFlag & ADD_THRES_VALUE_Z) && (NewBaseFlag & ADD_THRES_VALUE_X) )
      { DetectValue += 3; }
    if( ThresData < DetectValue )
      { 
        AxisX1Pam.LowThresCnt++;   
        AxisX1Pam.OverThresCnt = 0;   
        if( AdMagenticFlags & EVENT_ON_SAVED )
          {  MinOffBuffX.MinNum++;  }
      }
     else 
      {  
        AxisX1Pam.LowThresCnt = 0; 
        if( AdMagenticFlags & EVENT_STABLE )
          {  AxisX1Pam.OverThresCnt++;}
        if( ThresData > DecValueX )
          { DecValueX = ThresData; }
      }
  if( AdMagenticFlags & EVENT_ON_SAVED )
  {    
      MinOffBuffX.MinCnt++;
      if( MinOffBuffX.MinCnt >= 8 ) 
      {
        MinOffBuffX.MinCnt = 0;
        MinOffBuffX.CntBuff[MinOffBuffX.BuffPtr++] = MinOffBuffX.MinNum;
        if(MinOffBuffX.BuffPtr >= OffValueCntBuffNum)
          { MinOffBuffX.BuffPtr = 0; }
        MinOffBuffX.AllCnt++;
        if( MinOffBuffX.AllCnt >= OffValueCntBuffNum)
          {      
            MinOffBuffX.AllOffNum = 0; 
            for(i=0;i<OffValueCntBuffNum;i++)
               { MinOffBuffX.AllOffNum += MinOffBuffX.CntBuff[i]; }
            if( MinOffBuffX.AllOffNum >= MaxOffNum )
               { NewBaseFlag |= OFF_NUM_X_ON; }
            else
               { NewBaseFlag &= ~OFF_NUM_X_ON; }
            MinOffBuffX.AllCnt -= 1;           
          }
      }
  }
     if( AdMagenticFlags & EVENT_STABLE )
     {
       if( HalfEventCntZ >= OnTime )
         {  HalfBaseLineFlag |= HALF_EVENT_Z; }
       if( HalfEventCntX >= OnTime )
         { HalfBaseLineFlag |= HALF_EVENT_X;  }
       
       if( (AxisZ1Pam.OverThresCnt >= OnTime)      ||    //HOLDER_OVER_TIME
           (AxisX1Pam.OverThresCnt >= OnTime)  )        
       {
         //SensorRest(); 
         AdMagenticFlags &= ~EVENT_STABLE;
         TempBaseFlag &= ~MAX_NUM_OFF;
         AxisZ1Pam.OverThresCnt = 0;
         AxisX1Pam.OverThresCnt = 0;
        // OnGetTime = 0;
         //OnLowNumZ = 0;
         //OnLowNumX = 0;
         if( !(BaseLineFlag & READ_BASELINE_ON) )
           { 
            // SaveEvent(ON);
              if( TimeSlot.Hour >= 24 )
                  { TimeSlot.Hour = 0; }
              EventBuff.Event[EventBuff.SavePtr].Hour = TimeSlot.Hour;
              EventBuff.Event[EventBuff.SavePtr].Hour |= 0x80;
              EventBuff.Event[EventBuff.SavePtr].Minute = TimeSlot.Minute;
              EventBuff.Event[EventBuff.SavePtr].Second = TimeSlot.Second;
              EventBuff.Event[EventBuff.SavePtr].Second |= 0x80;            
              LastEvent.Hour = EventBuff.Event[EventBuff.SavePtr].Hour;
              LastEvent.Minute = EventBuff.Event[EventBuff.SavePtr].Minute;
              LastEvent.Second = EventBuff.Event[EventBuff.SavePtr].Second;
              EventBuff.EventNum++;
              EventBuff.SavePtr++;
              if( EventBuff.SavePtr >= SAVE_BUFF_NUM )
                 { EventBuff.SavePtr = 0; }  
              SaveEventMain();
              TempBaseFlag |= EVENT_ON_GENERT;
              //OffBaseLineZ = AxisZ1Pam.BaseLine;
              //OffBaseLineX = AxisX1Pam.BaseLine;
              OnBaseLineFlag &= ~ON_BASE_GET;
              ExtraFlags &= ~OFFBASE_SAVED_Z;
              ExtraFlags &= ~OFFBASE_SAVED_X;              
             // CompFlags &= ~ONE_ADXI_BASE_GET;
              pEventHour = TimeSlot.Hour;
              pEventMinute = TimeSlot.Minute;
              pEventSecond = TimeSlot.Second;
              pEventSecond |= 0x80;
              TempBaseFlag |= P_EVENT_GENERT;
              
              OnMinute = TimeSlot.Hour*60;
              OnMinute += TimeSlot.Minute;       
           } 
         else
           {  BaseLineFlag &= ~READ_BASELINE_ON; }         
         AdMagenticFlags |= EVENT_ON_SAVED;   
         OnBaseLineFlag &= ~SENSOR_ON_REST;
         //CompFlags &= ~ONE_ADXI_JUDG_END;      
        // CompFlags &= ~NEED_GET_BASE_LINE_Z;
       //  CompFlags &= ~NEED_GET_BASE_LINE_X;    
         CompFlags &= ~OFF_BASE_EFFECT_Z;
         CompFlags &= ~OFF_BASE_EFFECT_X;     
        // NewBaseFlag &= ~OTHER_TEMP_X_ON;
      //   NewBaseFlag &= ~OTHER_TEMP_Z_ON;
         NewBaseFlag |= ON_GET_VALUE_START_Z;
         NewBaseFlag |= ON_GET_VALUE_START_X;
         memset(&OffBaseCnt,0,sizeof(OffBaseCnt));
         memset(&OldBaseCnt,0,sizeof(OldBaseCnt));
         memset(&NewBaseCnt,0,sizeof(NewBaseCnt));
         memset(&BaseBuffCnt,0,sizeof(BaseBuffCnt));//TempValueZ
         memset(&TempValueZ,0,sizeof(TempValueZ));
         memset(&TempValueX,0,sizeof(TempValueX));//
         memset(&MinOffBuffZ,0,sizeof(MinOffBuffZ));
         memset(&MinOffBuffX,0,sizeof(MinOffBuffX));
         memset(&OnTempValueZ,0,sizeof(OnTempValueZ));
         memset(&OnTempValueX,0,sizeof(OnTempValueX));
         OnTempValueZ.Base = Magnetic.AxisZ1;
         OnTempValueX.Base = Magnetic.AxisX1;
         TempBaseSecond = TEMP_BASE_TIME;
         SenRestSecond = 0;
         OneAxisCntZ = 0;
         OneAxisCntX = 0;
         OnBaseGetNumZ = 0;
         OnBaseGetNumX = 0;
        // OffValueCntBuffZPtr = 0;
        // OffValueCntBuffXPtr = 0;
        // OffValueCntZ = 0;
         //OffValueCntX = 0;
         OnGreatEventZ = Magnetic.AxisZ1;
         OnSmallEventZ = Magnetic.AxisZ1;
         OnGreatEventX = Magnetic.AxisX1;
         OnSmallEventX = Magnetic.AxisX1;
         AdMagenticFlags &= ~BUS_OFF_GENERT;
         HalfBaseLineFlag &= ~OFF_BASE_CNT_ON;
         AdTime.TempBaseSecondZ = TempBaseSecond;
         AdTime.TempBaseSecondX = TempBaseSecond;
         AdTime.BusOffSecond = 0;
#if STRING_ON
         UartSendStrings("ON"); 
         UartSendStrings("\r\n");
#endif
#if LED_TEST_ON
LED1_ON();
#endif
       }
     }
 
    if( (AdMagenticFlags & EVENT_ON_SAVED) && (!(OnBaseLineFlag & DEC_VALUE_GENERATE_Z)) && (HalfBaseLineFlag & ON_EVENT_BASELINE_GET_Z) )  //ON_BASELIN_GENERT_Z
    {    
       if( AdTime.TempBaseSecondZ >= TEMP_BASE_TIME )
         { tempZ = GetBaseLineAny( Magnetic.AxisZ1, &OnTempBaseZ, &OnTempBaseBuffZ); }
       else
         { tempZ = 0;}
       if( tempZ > 1 )
       {
         AdTime.TempBaseSecondZ = 0;
         OnBaseLineFlag |= DEC_VALUE_GENERATE_Z;
         OnBaseLineFlag |= TEMP_ON_BASE_GET_Z;
         OnBaseLineFlag &= ~ON_EVENT_SCAND;
         OnTempBaseZ.BaseLine = tempZ;
         //OnBaseGetNumZ++;
         TempPositiveCntZ = 0;
         TempNegitiveCntZ = 0;
         TempValueZ.Base = Magnetic.AxisZ1;
         OnBaseLineFlag &= ~TEMP_BASE_CHANGED_Z;
               
        if( (!(OnBaseLineFlag & TEMP_BASE_CHANGED_X)) && (OnBaseLineFlag & TEMP_ON_BASE_GET_X) && (!(ExtraFlags & TEMP_BASE_ERR)) )
        { 
            BaseLineFlag  &= ~TEMP_BASE_CHANGED;
            ExtraFlags &= ~TEMP_BASE_ERR;
            OnBaseInitChg();
            if( !(HalfBaseLineFlag & BASE_INIT_OFF) ) 
            {         
              temp4 = 0;
              temp3 = DecBase( BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ , OnTempBaseZ.BaseLine );
              if( temp3 == 1 )    //<4
                { temp4++; }
              temp3 = DecBase( BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX , OnTempBaseX.BaseLine );
              if( temp3 == 1 )   //<4
                { temp4++; }
              if( temp4 < 2 )
              { 
                //if( EventOffFlag == ON )
                  // {  TimeCommunicatFlag |= STATE_SEND_ON;  }
                 BaseLineBuff.BasePtr++;
                 if( BaseLineBuff.BasePtr >= BASE_NUM )
                   { BaseLineBuff.BasePtr = 0; }
                  BaseLineBuff.BaseNum++;                      
              }          
              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ = OnTempBaseZ.BaseLine;
              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX = OnTempBaseX.BaseLine;  
              if(BaseLineBuff.BaseNum >= 2)
                { FlashWrite(SegmentC, (u8 *)&BaseLineBuff,sizeof(BaseLineBuff)); }  
              
              if( BaseLineBuff.BaseNum >= BASE_NUM )
              {
                ThresData = ScanOnBaseBuff();
                if( (ThresData > 0) && ( ThresData < 3 ) )
                {                        
                          BaseChgOnIntZ = AxisZ1Pam.BaseLine;
                          BaseChgOnIntX = AxisX1Pam.BaseLine;                         
                          ExtraFlags |= ON_GET_BASELINE;
                          OnBaseLineFlag |= ON_BASE_GET;
                         // OnBaseLineFlag |= GET_ON_BASELINE;
                          AdTime.BaseInitSecond = 0;
                          AdTime.BaseInitMinute = 0;                          
                          FlashBuffUpdateZ();
                          FlashBuffUpdateX();                          
                          AxisZ1Pam.BaseLine = BaseLineBuff.BaseBuff[ThresData].BaseZ;
                          AxisX1Pam.BaseLine = BaseLineBuff.BaseBuff[ThresData].BaseX; 
                          AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
                          AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
                         // SetBaseLineZ = AxisZ1Pam.BaseLine;
                        //  SetBaseLineX = AxisX1Pam.BaseLine;
                          TempBaseZ = AxisZ1Pam.BaseLine;
                          TempBaseX = AxisX1Pam.BaseLine;                         
                          //OffNumZ = 0;
                         // OffNumX = 0;
                          //TempBaseDayCnt = 0;
                          //OldBaseDayCnt = 0;
                          for(i=0;i<3;i++)
                            {
                              OffBaseBuffZ.Buff[i] = AxisZ1Pam.BaseLine;
                              OffBaseBuffX.Buff[i] = AxisX1Pam.BaseLine;
                            }
                          ChangeBaseBuff[ChangBasPtr].OldBaseZ = BaseChgOnIntZ;
                          ChangeBaseBuff[ChangBasPtr].OldBaseX = BaseChgOnIntX;
                          ChangeBaseBuff[ChangBasPtr].NewBaseZ = AxisZ1Pam.BaseLine;
                          ChangeBaseBuff[ChangBasPtr].NewBaseX = AxisX1Pam.BaseLine;
                          ChangBasPtr++;
                          if(ChangBasPtr >= 2)
                           { ChangBasPtr = 0; }                         
                          BaseLineFlag |= BASELINE_UPDATA;                         
                          LastBaseLineZ = AxisZ1Pam.BaseLine;
                          LastBaseLineX = AxisX1Pam.BaseLine;                            
                          BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                          BaseLineFlag &= ~BS_SMOOTH_UP_X;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_X;                                                           
                          Clock.DelayUplineScan = STATE_RF_DELAY; 
                          EraseSectorFlashC(); 
                          //SetBaseBuffUpdateZ();
                          //SetBaseBuffUpdateX();
                          //OnBaseChangeNum++;
                          temp3 = DecBase( OnTempBaseZ.BaseLine, AxisZ1Pam.BaseLine );
                          temp4 = DecBase( OnTempBaseX.BaseLine, AxisX1Pam.BaseLine );
                          if( (temp3 == 2) || (temp4 == 2) )
                          {                           
                              memset(&BaseLineBuff,0,sizeof(BaseLineBuff));
                              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ = OnTempBaseZ.BaseLine;
                              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX = OnTempBaseX.BaseLine;  
                              BaseLineBuff.BaseNum = 1;
                          }

   //UartSendStrings("ON base changedZ"); 
 // UartSendStrings("\r\n");                   
                }
              }
             
            }
          }
 //UartSendStrings("temp base getZ"); 
 //UartSendStrings("\r\n");          
       }
       else if( tempZ == 1 )
       {
         AdTime.TempBaseSecondZ = 0;
         OnTempBaseZ.pBaseLine = Magnetic.AxisZ1;
 //UartSendStrings("temp z num"); 
//UartSendStrings("\r\n");         
       }
    }
    if( (AdMagenticFlags & EVENT_ON_SAVED)  && (!(OnBaseLineFlag & DEC_VALUE_GENERATE_X)) && (HalfBaseLineFlag & ON_EVENT_BASELINE_GET_X) )
    {     
      if( AdTime.TempBaseSecondX >= TEMP_BASE_TIME )
         { tempX = GetBaseLineAny( Magnetic.AxisX1, &OnTempBaseX, &OnTempBaseBuffX); }
      else
         { tempX = 0; }
      if( tempX > 1 )
      {
        AdTime.TempBaseSecondX = 0;
        OnBaseLineFlag |= DEC_VALUE_GENERATE_X;
        OnBaseLineFlag |= TEMP_ON_BASE_GET_X;
        OnBaseLineFlag &= ~ON_EVENT_SCAND;
        OnTempBaseX.BaseLine = tempX;
        TempPositiveCntX = 0;
        TempNegitiveCntX = 0;
        TempValueX.Base = Magnetic.AxisX1;
        OnBaseLineFlag &= ~TEMP_BASE_CHANGED_X;
       
        if( (!(OnBaseLineFlag & TEMP_BASE_CHANGED_Z)) && (OnBaseLineFlag & TEMP_ON_BASE_GET_Z) && (!(ExtraFlags & TEMP_BASE_ERR)) )
          { 
            BaseLineFlag  &= ~TEMP_BASE_CHANGED; 
            ExtraFlags &= ~TEMP_BASE_ERR;
            OnBaseInitChg();
           if( !(HalfBaseLineFlag & BASE_INIT_OFF) )
           {                
              temp4 = 0;
              temp3 = DecBase( BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ , OnTempBaseZ.BaseLine );
              if( temp3 == 1 )
                { temp4++; }
              temp3 = DecBase( BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX , OnTempBaseX.BaseLine );
              if( temp3 == 1 )
                { temp4++; }
              if( temp4 < 2 )
              {               
                //if( EventOffFlag == ON )
                  // {  TimeCommunicatFlag |= STATE_SEND_ON;  }
                 BaseLineBuff.BasePtr++;
                 if( BaseLineBuff.BasePtr >= BASE_NUM )
                   { BaseLineBuff.BasePtr = 0; }
                  BaseLineBuff.BaseNum++;           
              }  
              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ = OnTempBaseZ.BaseLine;
              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX = OnTempBaseX.BaseLine;  
              if(BaseLineBuff.BaseNum >= 2)
                {  FlashWrite(SegmentC, (u8 *)&BaseLineBuff,sizeof(BaseLineBuff)); }     
              if( BaseLineBuff.BaseNum >= BASE_NUM )
              {
                ThresData = ScanOnBaseBuff();
                if( (ThresData > 0) && ( ThresData < 3 ) )
                {
                          BaseChgOnIntZ = AxisZ1Pam.BaseLine;
                          BaseChgOnIntX = AxisX1Pam.BaseLine;                         
                          ExtraFlags |= ON_GET_BASELINE;
                          OnBaseLineFlag |= ON_BASE_GET;
                         // OnBaseLineFlag |= GET_ON_BASELINE;
                          AdTime.BaseInitSecond = 0;
                          AdTime.BaseInitMinute = 0;
                          FlashBuffUpdateZ();
                          FlashBuffUpdateX();
                          AxisZ1Pam.BaseLine = BaseLineBuff.BaseBuff[ThresData].BaseZ;
                          AxisX1Pam.BaseLine = BaseLineBuff.BaseBuff[ThresData].BaseX;
                          AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
                          AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
                          //SetBaseLineZ = AxisZ1Pam.BaseLine;
                         // SetBaseLineX = AxisX1Pam.BaseLine;
                          TempBaseZ = AxisZ1Pam.BaseLine;
                          TempBaseX = AxisX1Pam.BaseLine;                        
                          //OffNumZ = 0;
                         // OffNumX = 0;
                          //TempBaseDayCnt = 0;
                          //OldBaseDayCnt = 0;
                          for(i=0;i<3;i++)
                            {
                              OffBaseBuffZ.Buff[i] = AxisZ1Pam.BaseLine;
                              OffBaseBuffX.Buff[i] = AxisX1Pam.BaseLine;
                            }
                          ChangeBaseBuff[ChangBasPtr].OldBaseZ = BaseChgOnIntZ;
                          ChangeBaseBuff[ChangBasPtr].OldBaseX = BaseChgOnIntX;
                          ChangeBaseBuff[ChangBasPtr].NewBaseZ = AxisZ1Pam.BaseLine;
                          ChangeBaseBuff[ChangBasPtr].NewBaseX = AxisX1Pam.BaseLine;
                          ChangBasPtr++;
                          if(ChangBasPtr >= 2)
                           { ChangBasPtr = 0; }                            
                          BaseLineFlag |= BASELINE_UPDATA;                         
                          LastBaseLineZ = AxisZ1Pam.BaseLine;
                          LastBaseLineX = AxisX1Pam.BaseLine;                            
                          BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                          BaseLineFlag &= ~BS_SMOOTH_UP_X;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_X;                                                 
                          Clock.DelayUplineScan = STATE_RF_DELAY; 
                           EraseSectorFlashC();
                          //OnBaseChangeNum++;
                          temp3 = DecBase( OnTempBaseZ.BaseLine, AxisZ1Pam.BaseLine );
                          temp4 = DecBase( OnTempBaseX.BaseLine, AxisX1Pam.BaseLine );
                          if( (temp3 == 2) || (temp4 == 2) )
                          {
                            //SaveEvent(ON);
                              memset(&BaseLineBuff,0,sizeof(BaseLineBuff));
                              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseZ = OnTempBaseZ.BaseLine;
                              BaseLineBuff.BaseBuff[BaseLineBuff.BasePtr].BaseX = OnTempBaseX.BaseLine;  
                              BaseLineBuff.BaseNum = 1;
                          }
    //UartSendStrings("ON base changedX"); 
//UartSendStrings("\r\n");
                }
              }
            }
          }
//UartSendStrings("temp base getX"); 
//UartSendStrings("\r\n");  
      }
     if( tempX == 1 )
      {
        AdTime.TempBaseSecondX = 0;
        OnTempBaseX.pBaseLine = Magnetic.AxisX1;  
 //  UartSendStrings("temp X num"); 
 //UartSendStrings("\r\n");      
      }
    }
   if( (ExtraFlags & ON_BASELIN_GENERT_Z) && (ExtraFlags & ON_BASELIN_GENERT_X) )
   {
      AverageValueGet( &TempValueZ, Magnetic.AxisZ1 );
      AverageValueGet( &TempValueX, Magnetic.AxisX1 );      
      temp3 = DecBigTerg( TempValueZ.Value, TempValueZ.LastValue,4);  
      if(temp3 == 0)
      {     
        TempDec1 = DecBigTerg( OnBaseLineZ.BaseLine, AxisZ1Pam.BaseLine,DecMaxAd);
        TempDec2 = DecBigTerg( TempValueZ.Value, AxisZ1Pam.BaseLine,9);  
        if( (TempDec1 == 0) && (TempDec2 == 1)  )
         {          
            TempValueZ.LastValue = TempValueZ.Value;
            NewBaseFlag |= TEMP_BASE_UPDATE_Z;
            NewBaseFlag |= OTHER_TEMP_X_ON;
            AxisZ1Pam.BaseLine = TempValueZ.Value;   
            TempBaseOffNumZ = 0;
            memset(&OtherTempValueX,0,sizeof(OtherTempValueX));
            OtherTempValueX.Base = Magnetic.AxisX1;
            if(SingleFlag & LAST_EVENT_ON)
              {  
                OffSendNum = 0;
                SaveEvent(OFF);                
              }
         }     
      }
      if( NewBaseFlag & OTHER_TEMP_X_ON )
      {
        tempX = AverageValueGet( &OtherTempValueX, Magnetic.AxisX1 );   
        if( tempX == 1 )
        {
          NewBaseFlag &= ~OTHER_TEMP_X_ON;
          TempDec1 = DecBigTerg( OtherTempValueX.Value, AxisX1Pam.BaseLine,9);
          if( TempDec1 == 1 )
          {
            NewBaseFlag |= TEMP_BASE_UPDATE_X;
            AxisX1Pam.BaseLine = OtherTempValueX.Value;   
            TempBaseOffNumX = 0;                 
          }        
        }
      }
      
      temp3 = DecBigTerg( TempValueX.Value, TempValueX.LastValue, 4);
      if( temp3 == 0)
      {             
         TempDec1 = DecBigTerg( OnBaseLineX.BaseLine, AxisX1Pam.BaseLine,DecMaxAd);
         TempDec2 = DecBigTerg( TempValueX.Value, AxisX1Pam.BaseLine,9);   
         if( (TempDec1 == 0) && (TempDec2 == 1)  )
          {         
            TempValueX.LastValue = TempValueX.Value;
            NewBaseFlag |= TEMP_BASE_UPDATE_X;
            NewBaseFlag |= OTHER_TEMP_Z_ON;
            AxisX1Pam.BaseLine = TempValueX.Value;
            TempBaseOffNumX = 0;
            memset(&OtherTempValueZ,0,sizeof(OtherTempValueZ));
            OtherTempValueZ.Base = Magnetic.AxisZ1;
            if(SingleFlag & LAST_EVENT_ON)
              {  
                 OffSendNum = 0;
                 SaveEvent(OFF);               
              }
          }
      }
      if( NewBaseFlag & OTHER_TEMP_Z_ON )
      {
        tempZ = AverageValueGet( &OtherTempValueZ, Magnetic.AxisZ1 );  
        if( tempZ == 1 )
        {         
          NewBaseFlag &= ~OTHER_TEMP_Z_ON;
          TempDec1 = DecBigTerg( OtherTempValueZ.Value, AxisZ1Pam.BaseLine,9);
          if( TempDec1 == 1 )
          {
            NewBaseFlag |= TEMP_BASE_UPDATE_Z;
            AxisZ1Pam.BaseLine = OtherTempValueZ.Value;   
            TempBaseOffNumZ = 0;           
          }
        }
      }     
   }
       if( NewBaseFlag & ON_GET_VALUE_START_Z )
        {
          tempZ = AverageValueGet( &OnTempValueZ, Magnetic.AxisZ1 );  
          if( tempZ == 1 )
          {
            NewBaseFlag &= ~ON_GET_VALUE_START_Z;
            OnTempValueBuffZ.BaseLine[OnTempValueBuffZ.SavePtr++] = OnTempValueZ.Value;
            if( OnTempValueBuffZ.SavePtr >= 3 )
              { OnTempValueBuffZ.SavePtr = 0; }
            temp3 = ComperTempBuff(&OnTempValueBuffZ);
            if( temp3 == 1 )
              { NewBaseFlag |= ADD_THRES_VALUE_Z; }
            else
              { NewBaseFlag &= ~ADD_THRES_VALUE_Z; }
          }
        }
       if( NewBaseFlag & ON_GET_VALUE_START_X )
       {        
         tempX = AverageValueGet( &OnTempValueX, Magnetic.AxisX1 ); 
         if( tempX == 1 )
         {
           NewBaseFlag &= ~ON_GET_VALUE_START_X;
           OnTempValueBuffX.BaseLine[OnTempValueBuffX.SavePtr++] = OnTempValueX.Value;
           if( OnTempValueBuffX.SavePtr >= 3)
             { OnTempValueBuffX.SavePtr = 0; }    
           temp3 = ComperTempBuff(&OnTempValueBuffX);
           if( temp3 == 1 )
             {  NewBaseFlag |= ADD_THRES_VALUE_X;  }
           else
             {  NewBaseFlag &= ~ADD_THRES_VALUE_X; }
         }
       }
       if( AdTime.EventOnTime >= ON_START_GEY_BASELINE_TIME )// && (时间大于2分钟)) 
       {  
 // UartSendStrings("2 minute on"); 
  //UartSendStrings("\r\n");      
         if( (!(OnBaseLineFlag & SENSOR_ON_REST)) && (EventOffFlag == ON) )
         {
           OnBaseLineFlag |= SENSOR_ON_REST;
           SensorRest();       
         }
         if( !(HalfBaseLineFlag & ON_EVENT_BASELINE_GET_Z) )
            { OnEventGetBaseLineZ();  }
         else
            {  AnyBaseLineUpdateZ( &OnStableBaseLineZ, &OnBaseLineZ); }
         if( !(HalfBaseLineFlag & ON_EVENT_BASELINE_GET_X) )
            {  OnEventGetBaseLineX(); }
         else 
            { AnyBaseLineUpdateX( &OnStableBaseLineX, &OnBaseLineX); }
       }
      /*if( (AdMagenticFlags & EVENT_ON_SAVED) && (OnGetTime >= OffTime)  )
        { 
          OnGetTime = 0;
          if( (ExtraFlags & ON_BASELIN_GENERT_Z) && (ExtraFlags & ON_BASELIN_GENERT_X) ) 
          {
            if( (CompFlags & EFFECT_ON_Z) && (CompFlags & EFFECT_ON_X) && (!(CompFlags & ONE_ADXI_JUDG_END)) )
            {
              if( (OnLowNumZ >= MaxOffNum) && (OnLowNumX < MaxOffNum) )
                 {
                   OneAxisCntX++;
                   OneAxisCntZ = 0;                          
                 }
              else if( (OnLowNumZ < MaxOffNum) && (OnLowNumX >= MaxOffNum) )  //CompFlags |= NEED_GET_BASE_LINE_Z;
                 { 
                   OneAxisCntZ++;
                   OneAxisCntX = 0;                          
                 }
              else
                {
                  OneAxisCntZ = 0;
                  OneAxisCntX = 0;
                }
              if(OneAxisCntZ >= 3)
                {
                  CompFlags |= NEED_GET_BASE_LINE_Z;
                  CompFlags |= ONE_ADXI_JUDG_END;
                  CompFlags &= ~ONE_BASE_Z_GENERT;
                  OneAxisCntZ = 0;
                   memset(&OneAdxiBaseZ,0,sizeof(OneAdxiBaseZ)); 
                   memset(&OneAdxiBaseBuffZ,0,sizeof(OneAdxiBaseBuffZ));                    
                }
               if(OneAxisCntX >= 3)
               {
                 CompFlags |= NEED_GET_BASE_LINE_X;
                 CompFlags |= ONE_ADXI_JUDG_END;
                 CompFlags &= ~ONE_BASE_X_GENERT;
                 OneAxisCntX = 0;
                 memset(&OneAdxiBaseX,0,sizeof(OneAdxiBaseX)); 
                 memset(&OneAdxiBaseBuffX,0,sizeof(OneAdxiBaseBuffX));                  
               }              
            }
          }
        //  if( (OnLowNumZ >= MaxOffNum) && (OnLowNumX >= MaxOffNum) )
            // { TempBaseFlag |= MAX_NUM_OFF; }
          OnLowNumZ = 0;
          OnLowNumX = 0;        
        }*/
     /*  if( (CompFlags & NEED_GET_BASE_LINE_Z) && (!(CompFlags & ONE_BASE_Z_GENERT))  )
       {
         tempZ = GetBaseLineAny( Magnetic.AxisZ1, &OneAdxiBaseZ, &OneAdxiBaseBuffZ); 
         if( tempZ > 1 )
         {
           if( AxisX1Pam.LowThresCnt >= OffTime )
           {
              FlashBuffUpdateZ();
              AxisZ1Pam.BaseLine = tempZ;
              CompFlags |= ONE_BASE_Z_GENERT;
              TempBaseFlag |= MAX_NUM_OFF;           
           }
           else
           {
             CompFlags &= ~NEED_GET_BASE_LINE_Z;
             CompFlags &= ~ONE_BASE_Z_GENERT;
           }
         }
       }*/
     /*  if((CompFlags & NEED_GET_BASE_LINE_X) && (!(CompFlags & ONE_BASE_X_GENERT))  )
       {
         tempX = GetBaseLineAny( Magnetic.AxisX1, &OneAdxiBaseX, &OneAdxiBaseBuffX); 
         if( tempX > 1)
         {
            if( AxisZ1Pam.LowThresCnt >= OffTime )
            {
               FlashBuffUpdateX();
               AxisX1Pam.BaseLine = tempX;
               CompFlags |= ONE_BASE_X_GENERT;
               TempBaseFlag |= MAX_NUM_OFF;                   
            }
            else
            {
              CompFlags &= ~NEED_GET_BASE_LINE_X;
              CompFlags &= ~ONE_BASE_X_GENERT;
            }
         }
       }*/
       if( (CompFlags & OFF_BASE_EFFECT_Z) && (CompFlags & OFF_BASE_EFFECT_X) )
         {  TempBaseFlag |= MAX_NUM_OFF; }
       if( (NewBaseFlag & OFF_NUM_Z_ON) && (NewBaseFlag & OFF_NUM_X_ON) )
         { TempBaseFlag |= MAX_NUM_OFF; }
      if( ((AxisZ1Pam.LowThresCnt >= OffTime) && (AxisX1Pam.LowThresCnt >= OffTime)) || (TempBaseFlag & MAX_NUM_OFF) )
       {       
            TempBaseFlag &= ~MAX_NUM_OFF;
             EventOff();    
       }
       else
      {            
         SystemState = EVENT_DETECT;
      } 
    if( (OnBaseLineFlag & TEMP_ON_BASE_GET_Z)   &&
        (OnBaseLineFlag & TEMP_ON_BASE_GET_X)   &&
        (!(BaseLineFlag & TEMP_BASE_CHANGED))  )       
     {  
       if(Magnetic.AxisZ1 > OnTempBaseZ.BaseLine)
         { 
           tempZ = Magnetic.AxisZ1 - OnTempBaseZ.BaseLine;
           HalfBaseLineFlag |= POSITIVE_CNT_Z;
         }
       else
         { 
           tempZ = OnTempBaseZ.BaseLine - Magnetic.AxisZ1;
           HalfBaseLineFlag &= ~POSITIVE_CNT_Z;
         } 
       if(Magnetic.AxisX1 > OnTempBaseX.BaseLine)
         { 
           tempX = Magnetic.AxisX1 - OnTempBaseX.BaseLine;
           HalfBaseLineFlag |= POSITIVE_CNT_X;
         }
       else
         { 
           tempX = OnTempBaseX.BaseLine - Magnetic.AxisX1; 
           HalfBaseLineFlag &= ~POSITIVE_CNT_X;
         } 
         if( tempZ >= HALF_EVENT_VALUE )
          { 
            if(HalfBaseLineFlag & POSITIVE_CNT_Z)
               { 
                 TempPositiveCntZ++; 
                 TempNegitiveCntZ = 0;
               }
            else
              {
                TempNegitiveCntZ++;
                TempPositiveCntZ = 0;
              }
          }
         else
          { 
            TempPositiveCntZ = 0;
            TempNegitiveCntZ = 0;
          }  
         if( tempX >= HALF_EVENT_VALUE )
          { 
            if(HalfBaseLineFlag & POSITIVE_CNT_X)
               { 
                 TempPositiveCntX++; 
                 TempNegitiveCntX = 0;
               }
            else
              {
                TempNegitiveCntX++;
                TempPositiveCntX = 0;
              }
          }
         else
          { 
            TempPositiveCntX = 0; 
            TempNegitiveCntX = 0;
          }  

       if( (TempPositiveCntZ >= EventChangTime) ||
           (TempNegitiveCntZ >= EventChangTime) ||
           (TempPositiveCntX >= EventChangTime) ||
           (TempNegitiveCntX >= EventChangTime)  )
          {   
             if( (OnTempBaseZ.BaseLine < MIN_BASE) ||
                 (OnTempBaseZ.BaseLine > MAX_BASE) ||
                 (OnTempBaseX.BaseLine < MIN_BASE) ||
                 (OnTempBaseX.BaseLine > MAX_BASE) )
               { ExtraFlags |= TEMP_BASE_ERR; }
             else
               { ExtraFlags &= ~TEMP_BASE_ERR; }
             TempBaseSecond = TEMP_BASE_TIME; 
             OnBaseLineFlag |= TEMP_BASE_CHANGED_Z;
             OnBaseLineFlag |= TEMP_BASE_CHANGED_X;
             BaseLineFlag  |= TEMP_BASE_CHANGED;
             OnBaseLineFlag &= ~DEC_VALUE_GENERATE_Z;
             OnBaseLineFlag &= ~DEC_VALUE_GENERATE_X;
             AdTime.TempBaseSecondZ = TempBaseSecond;
             AdTime.TempBaseSecondX = TempBaseSecond;
             TempPositiveCntZ = 0;
             TempNegitiveCntZ = 0;
             TempPositiveCntX = 0;
             TempNegitiveCntX = 0;
             SenRestSecond = 0;
             SensorRest(); 
            if( (ExtraFlags & ON_BASELIN_GENERT_Z) && (ExtraFlags & ON_BASELIN_GENERT_X) )
             {
                  OnGreatEventZ = Magnetic.AxisZ1;
                  OnSmallEventZ = Magnetic.AxisZ1;
                  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_Z;
                  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_ON_Z;
                   OnGreatEventX = Magnetic.AxisX1;
                   OnSmallEventX = Magnetic.AxisX1;
                   HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_X;
                   HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_ON_X;
                   OnEventTimeZ.Hour = TimeSlot.Hour;
                   OnEventTimeZ.Minute = TimeSlot.Minute;
                   OnEventTimeZ.Second = TimeSlot.Second;              
             }   
    //UartSendStrings("Temp Bas chg"); 
 //UartSendStrings("\r\n");            
          }   
     }  
}
void CommdOffBaseLine(void)
{
                          AxisZ1Pam.BaseLine = OnBaseLineZ.BaseLine ;
                          AxisX1Pam.BaseLine = OnBaseLineX.BaseLine ;   
                          AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
                          AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
                          BaseLineFlag |= BASELINE_UPDATA;                         
                          LastBaseLineZ = AxisZ1Pam.BaseLine;
                          LastBaseLineX = AxisX1Pam.BaseLine;                            
                          BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                          BaseLineFlag &= ~BS_SMOOTH_UP_X;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_X;                                                             
                          Clock.DelayUplineScan = STATE_RF_DELAY;                       
}

void OnBaseInitChg(void)
{
  u8 temp3;
  u8 ThresData;
 // u8 pHour;
 // u8 pMiute;
 // u8 pSecond;
  u8 i;
              HalfBaseLineFlag &= ~BASE_INIT_OFF;
              if( (ExtraFlags & ON_GET_BASELINE ) && (LastEvent.Second & 0x80) )// && (OnBaseGetNumZ == 1) && (OnBaseGetNumX == 1) )
              {
                OnBaseLineFlag &= ~ODD_BASE_EFFECT_Z;
                OnBaseLineFlag &= ~ODD_BASE_EFFECT_X;
                temp3 = 0;
                ThresData = DecBase( BaseChgOnIntZ, OnTempBaseZ.BaseLine );
                if( ThresData == 1)
                 { temp3++; }
                ThresData = DecBase( BaseChgOnIntX, OnTempBaseX.BaseLine );
                if( ThresData == 1)
                 { temp3++; }
                if( temp3 >= 2)
                {
                          ExtraFlags &= ~ON_GET_BASELINE;
                         // OnBaseLineFlag |= GET_ON_BASELINE;
                          FlashBuffUpdateZ();
                          FlashBuffUpdateX();
                          AxisZ1Pam.BaseLine = BaseChgOnIntZ;
                          AxisX1Pam.BaseLine = BaseChgOnIntX;
                          AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine; 
                          AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
                         // SetBaseLineZ = AxisZ1Pam.BaseLine;
                        //  SetBaseLineX = AxisX1Pam.BaseLine;
                          TempBaseZ = AxisZ1Pam.BaseLine;
                          TempBaseX = AxisX1Pam.BaseLine;                      
                          //OffNumZ = 0;
                          //OffNumX = 0;
                          //TempBaseDayCnt = 0;
                          //OldBaseDayCnt = 0;
                          for(i=0;i<3;i++)
                           {
                             OffBaseBuffZ.Buff[i] = AxisZ1Pam.BaseLine;
                             OffBaseBuffX.Buff[i] = AxisX1Pam.BaseLine;
                           }
                          BaseLineFlag |= BASELINE_UPDATA;                         
                          LastBaseLineZ = AxisZ1Pam.BaseLine;
                          LastBaseLineX = AxisX1Pam.BaseLine;                            
                          BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                          BaseLineFlag &= ~BS_SMOOTH_UP_X;
                          BaseLineFlag &= ~BS_SMOOTH_DOWN_X;                                                   
                          Clock.DelayUplineScan = STATE_RF_DELAY; 
                          HalfBaseLineFlag |= BASE_INIT_OFF; //**********************************************************************************   
                          AdMagenticFlags &= ~ON_EVENT_ON_SAVED;
                          OnBaseLineFlag |= ON_BASE_GET;
                          OnBaseUpdateNum++; 
                           EraseSectorFlashC();
//  UartSendStrings("Init Base Back"); 
  //UartSendStrings("\r\n");  
                          
                }
              }
}

u8 ScanOnBaseBuff(void)
{
  u8 temp;
  u8 temp1;
  u8 ret = 0;
  OnBaseLineFlag &= ~ODD_BASE_EFFECT_Z; //奇数
  OnBaseLineFlag &= ~EVEN_BASE_EFFECT_Z; //偶数
  OnBaseLineFlag &= ~ODD_BASE_EFFECT_X;
  OnBaseLineFlag &= ~EVEN_BASE_EFFECT_X;
  TempBaseFlag &= ~BASE_CHANGE_OVER_Z1;
  TempBaseFlag &= ~BASE_CHANGE_OVER_X1;
  TempBaseFlag &= ~BASE_CHANGE_OVER_Z2;
  TempBaseFlag &= ~BASE_CHANGE_OVER_X2;
  TempBaseFlag &= ~BASE_EFFECT_OVER_1;
  TempBaseFlag &= ~BASE_EFFECT_OVER_2;
  temp1 = 0;
  temp = DecBase( BaseLineBuff.BaseBuff[0].BaseZ, BaseLineBuff.BaseBuff[2].BaseZ );
  if( temp == 1 )
    { temp1++; }
 /* temp = DecBase( BaseLineBuff.BaseBuff[0].BaseZ, BaseLineBuff.BaseBuff[4].BaseZ );
  if( temp == 1 )
    { temp1++; }
  temp = DecBase( BaseLineBuff.BaseBuff[2].BaseZ, BaseLineBuff.BaseBuff[4].BaseZ );
  if( temp == 1 )
    { temp1++; }*/
  if( temp1 >= 1 )
  { OnBaseLineFlag |= EVEN_BASE_EFFECT_Z; }
  temp1 = 0;
  temp = DecBase( BaseLineBuff.BaseBuff[0].BaseX, BaseLineBuff.BaseBuff[2].BaseX );
  if( temp == 1 )
    { temp1++; }
 /* temp = DecBase( BaseLineBuff.BaseBuff[0].BaseX, BaseLineBuff.BaseBuff[4].BaseX );
  if( temp == 1 )
    { temp1++; }
  temp = DecBase( BaseLineBuff.BaseBuff[2].BaseX, BaseLineBuff.BaseBuff[4].BaseX );
  if( temp == 1 )
    { temp1++; }*/
  if( temp1 >= 1 )
    { OnBaseLineFlag |= EVEN_BASE_EFFECT_X; }
  
    temp1 = 0;
    temp = DecBase( BaseLineBuff.BaseBuff[1].BaseZ, BaseLineBuff.BaseBuff[3].BaseZ );
    if( temp == 1 )
     { temp1++; }
   /* temp = DecBase( BaseLineBuff.BaseBuff[1].BaseZ, BaseLineBuff.BaseBuff[5].BaseZ );
    if( temp == 1 )
     { temp1++; }
    temp = DecBase( BaseLineBuff.BaseBuff[3].BaseZ, BaseLineBuff.BaseBuff[5].BaseZ );
    if( temp == 1 )
     { temp1++; }*/
    if( temp1 >= 1)
      { OnBaseLineFlag |= ODD_BASE_EFFECT_Z; }
    temp1 = 0;
    temp = DecBase( BaseLineBuff.BaseBuff[1].BaseX, BaseLineBuff.BaseBuff[3].BaseX );
    if( temp == 1 )
     { temp1++; }
  /*  temp = DecBase( BaseLineBuff.BaseBuff[1].BaseX, BaseLineBuff.BaseBuff[5].BaseX );
    if( temp == 1 )
     { temp1++; }
    temp = DecBase( BaseLineBuff.BaseBuff[3].BaseX, BaseLineBuff.BaseBuff[5].BaseX );
    if( temp == 1 )
     { temp1++; }*/
    if( temp1 >= 1)
      { OnBaseLineFlag |= ODD_BASE_EFFECT_X; }
    
    if( (!(OnBaseLineFlag & ODD_BASE_EFFECT_Z)) || (!(OnBaseLineFlag & ODD_BASE_EFFECT_X)) )//1,3 差大于4
      { 
        if( (OnBaseLineFlag & EVEN_BASE_EFFECT_Z) && (OnBaseLineFlag & EVEN_BASE_EFFECT_X)  )  //0 ，2相等，1,3 与2差大于7
          {
            temp = DecBase( BaseLineBuff.BaseBuff[1].BaseZ, BaseLineBuff.BaseBuff[2].BaseZ );
            if( temp == 2 )
              { TempBaseFlag |= BASE_CHANGE_OVER_Z1; }
            temp = DecBase( BaseLineBuff.BaseBuff[1].BaseX, BaseLineBuff.BaseBuff[2].BaseX );
            if( temp == 2 )
              { TempBaseFlag |= BASE_CHANGE_OVER_X1; }
            if( (TempBaseFlag & BASE_CHANGE_OVER_Z1) || (TempBaseFlag & BASE_CHANGE_OVER_X1) )
             { TempBaseFlag |= BASE_EFFECT_OVER_1;}
            
            temp = DecBase( BaseLineBuff.BaseBuff[3].BaseZ, BaseLineBuff.BaseBuff[2].BaseZ );
            if( temp == 2 )
              { TempBaseFlag |= BASE_CHANGE_OVER_Z2; }
            temp = DecBase( BaseLineBuff.BaseBuff[3].BaseX, BaseLineBuff.BaseBuff[2].BaseX );
            if( temp == 2 )
              { TempBaseFlag |= BASE_CHANGE_OVER_X2; }
            if( (TempBaseFlag & BASE_CHANGE_OVER_Z2) || (TempBaseFlag & BASE_CHANGE_OVER_X2) )
               { TempBaseFlag |= BASE_EFFECT_OVER_2; }
            
            if( (TempBaseFlag & BASE_EFFECT_OVER_1) && (TempBaseFlag & BASE_EFFECT_OVER_2) )
               { ret = 2; }
          }
      }
    else if( (!(OnBaseLineFlag & EVEN_BASE_EFFECT_Z)) || (!(OnBaseLineFlag & EVEN_BASE_EFFECT_X)) )
    {
      if( (OnBaseLineFlag & ODD_BASE_EFFECT_Z) && (OnBaseLineFlag & ODD_BASE_EFFECT_X) )    //1,3相等，0,2差>4
        {
          temp = DecBase( BaseLineBuff.BaseBuff[0].BaseZ, BaseLineBuff.BaseBuff[1].BaseZ );
          if( temp == 2 )
              { TempBaseFlag |= BASE_CHANGE_OVER_Z1; }
          temp = DecBase( BaseLineBuff.BaseBuff[0].BaseX, BaseLineBuff.BaseBuff[1].BaseX );
          if( temp == 2 )
              { TempBaseFlag |= BASE_CHANGE_OVER_X1; }
          if( (TempBaseFlag & BASE_CHANGE_OVER_Z1) || (TempBaseFlag & BASE_CHANGE_OVER_X1) )
              { TempBaseFlag |= BASE_EFFECT_OVER_1;}
          
          temp = DecBase( BaseLineBuff.BaseBuff[2].BaseZ, BaseLineBuff.BaseBuff[1].BaseZ );
          if( temp == 2 )
             { TempBaseFlag |= BASE_CHANGE_OVER_Z2; }
          temp = DecBase( BaseLineBuff.BaseBuff[2].BaseX, BaseLineBuff.BaseBuff[1].BaseX );
          if( temp == 2 )
             { TempBaseFlag |= BASE_CHANGE_OVER_X2; }
          if( (TempBaseFlag & BASE_CHANGE_OVER_Z2) || (TempBaseFlag & BASE_CHANGE_OVER_X2) )
             { TempBaseFlag |= BASE_EFFECT_OVER_2; }
          
          if( (TempBaseFlag & BASE_EFFECT_OVER_1) && (TempBaseFlag & BASE_EFFECT_OVER_2) )
            { ret = 1; }
        }
    }
  return ret;
}

u8 DecBigTerg( u16 Base1, u16 Base2 ,u8 Value)
{
  u16 temp;
  u8 ret;
  if( Base1 > Base2 )
    { temp = Base1 - Base2; }
  else
    { temp = Base2 - Base1; }
  if( temp < Value )
     { ret = 1;}
  else
     {ret = 0;}
  return ret;///
}

u8 DecDect( u16 Base1, u16 Base2)
{
   u8 ret;
  u16 temp;
  if( Base1 > Base2 )
    { temp = Base1 - Base2; }
  else
    { temp = Base2 - Base1; }
   if( temp < ApDetectValue )
     { ret = 1;}
  else
     {ret = 0;}
  return ret;///
}

u8 DecBase( u16 Base1, u16 Base2 )
{
  u8 ret;
  u16 temp;
  if( Base1 > Base2 )
    { temp = Base1 - Base2; }
  else
    { temp = Base2 - Base1; }
  if( temp < 4 )
    { ret = 1; }
  else if(temp > 8)
    { ret = 2; }
  else
    { ret = 0; }
  
  return ret;
}

u8 DecBaseEvent( u16 Base1, u16 Base2 )
{
  u8 ret;
  u16 temp;
  if( Base1 > Base2 )
    { temp = Base1 - Base2; }
  else
    { temp = Base2 - Base1; }
  if( temp < UnDetectValue )
    { ret = 1; }
  else
    { ret = 0; }
  
  return ret;
}

u8 DecBaseOn( u16 Base1, u16 Base2 )
{
   u8 ret;
  u16 temp;
  if( Base1 > Base2 )
    { temp = Base1 - Base2; }
  else
    { temp = Base2 - Base1; }
  if( temp < 3 )
    { ret = 1; }
  else
    { ret = 0; }
  return ret;
}

void EventOff(void)
{
  //u8 pSecond;
 // u8 pMinute;
 // u8 pHour;
           if( AdMagenticFlags & EVENT_ON_SAVED )
             {
                AxisZ1Pam.LowThresCnt = 0; 
                AxisX1Pam.LowThresCnt = 0;          
                //SaveEvent(OFF); 
                if( TimeSlot.Hour >= 24 )
                  { TimeSlot.Hour = 0; } 
                EventBuff.Event[EventBuff.SavePtr].Hour = TimeSlot.Hour;
                EventBuff.Event[EventBuff.SavePtr].Hour |= 0x80;
                EventBuff.Event[EventBuff.SavePtr].Minute = TimeSlot.Minute;
                EventBuff.Event[EventBuff.SavePtr].Second = TimeSlot.Second;
                EventBuff.Event[EventBuff.SavePtr].Second &= 0x7f;
                LastEvent.Hour = EventBuff.Event[EventBuff.SavePtr].Hour;
                LastEvent.Minute = EventBuff.Event[EventBuff.SavePtr].Minute;
                LastEvent.Second = EventBuff.Event[EventBuff.SavePtr].Second;
                EventBuff.EventNum++;
                EventBuff.SavePtr++;
                if( EventBuff.SavePtr >= SAVE_BUFF_NUM )
                 { EventBuff.SavePtr = 0; }  
                SaveEventMain();
                TempBaseFlag &= ~EVENT_ON_GENERT;
              
                pEventHour = TimeSlot.Hour;
                pEventMinute = TimeSlot.Minute;
                pEventSecond = TimeSlot.Second;
                pEventSecond &= ~0x80;
                TempBaseFlag |= P_EVENT_GENERT;
                OnBaseLineFlag &= ~ON_BASE_GET;
                ExtraFlags &= ~OFFBASE_SAVED_Z;
                ExtraFlags &= ~OFFBASE_SAVED_X;
                OffMinute = TimeSlot.Hour*60;
                OffMinute += TimeSlot.Minute;  
                ExtraFlags |= EVENT_OFF_SAVED;
                //CompFlags &= ~ONE_ADXI_JUDG_END; 
               // CompFlags &= ~ONE_BASE_Z_GENERT;
              //  CompFlags &= ~ONE_BASE_X_GENERT;
                memset(&OnBaseLineZ,0,sizeof(OnBaseLineZ));
                memset(&OnBaseLineX,0,sizeof(OnBaseLineX));  //
                memset(&OffTempValueZ,0,sizeof(OffTempValueZ));
                memset(&OffTempValueX,0,sizeof(OffTempValueX));
                AdMagenticFlags &= ~ON_EVENT_ON_SAVED;
                HalfBaseLineFlag &= ~OFF_BASE_CNT_ON;
                ExtraFlags |= BASELINE_CALIBRAT_Z;
                ExtraFlags |= BASELINE_CALIBRAT_X;
                NewBaseFlag &= ~OFF_BASE_GET_Z;
                NewBaseFlag &= ~OFF_BASE_GET_X;
                AdMagenticFlags |= BUS_OFF_GENERT;
                TempBaseFlag &= ~BASE_UPDATE_ON_Z;
                TempBaseFlag &= ~BASE_UPDATE_ON_X;//OffBaseOffedNum
                if( (CompFlags & OFF_BASE_EFFECT_Z) && (CompFlags & OFF_BASE_EFFECT_X) )
                   { 
                     OffBaseOffedNum++;
                     if( OffBaseOffedNum >= 3 )
                        {
                          OffBaseOffedNum = 0;
                          FlashBuffUpdateZ();
                          FlashBuffUpdateX();
                          AxisZ1Pam.BaseLine = OffTempBaseZ.BaseLine;
                          AxisX1Pam.BaseLine = OffTempBaseX.BaseLine;          
                        }          
                   }
                else
                   { OffBaseOffedNum = 0;}
                CompFlags &= ~OFF_BASE_EFFECT_Z;
                CompFlags &= ~OFF_BASE_EFFECT_X;
                if(BaseLineBuff.BaseNum >= 2)
                  {  EraseSectorFlashC(); }
                memset(&BaseLineBuff,0,sizeof(BaseLineBuff));
                OffBaseGetTime = 10;
                BasAddNumZ = 0;
                BasAddNumX = 0;
                BasDecNumZ = 0;
                BasDecNumX = 0;
                BasCountZ = 0;
                BasCountX = 0;
                OffTempBaseSecond = 0;
                SenRestSecond = 0;
             }  
            AdTime.EventOnTime = 0;
            BaseLineFlag &= ~READ_BASELINE_ON;
            BaseLineFlag &= ~READ_BASELINE;          
            //AdTime.BusOffSecond = 0;
            SenTime.BaseLineTime = 0;  
            AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine;
            AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;  
            BaseLineFlag &= ~SMOOTH_UP_Z;
            BaseLineFlag &= ~SMOOTH_DOWN_Z;
            BaseLineFlag &= ~SMOOTH_UP_X;
            BaseLineFlag &= ~SMOOTH_DOWN_X;   
           // HalfBaseLineFlag &= ~COMMD_OFF_BASE;      
            if( ExtraFlags & ON_BASELIN_GENERT_Z )                                                  
            {
               AdMagenticFlags &= ~ON_HALF_BASELINE_Z;                                                                       
               memset(&StableBaseLineZ,0,sizeof(StableBaseLineZ)); 
               AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine;    
            }
           if( ExtraFlags & ON_BASELIN_GENERT_X )    
            {
               AdMagenticFlags &= ~ON_HALF_BASELINE_X;
               memset(&StableBaseLineX,0,sizeof(StableBaseLineX)); 
               AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;   
            }
            if(DetectValue < ApDetectValue)
            { DetectValue = ApDetectValue; }
            AdMagenticFlags &= ~EVENT_ON_SAVED;
            AxisZ1Pam.OverThresCnt = 0;
            AxisX1Pam.OverThresCnt = 0;
            HalfBaseLineFlag &= ~ON_EVENT_ON_Z;
            HalfBaseLineFlag &= ~ON_EVENT_ON_X;
            SingleFlag &= ~SINGLE_GET_ON;
            SystemState = ON_BASE_LINE;
#if STRING_ON
            UartSendStrings("OFF"); 
            UartSendStrings("\r\n");
#endif
#if LED_TEST_ON                    
LED1_OFF();
#endif                 
}
void SaveEventMain(void)
{
  u8 flag;
  
  AddSlotNum.SenID = RfParamt.SenID;
  AddSlotNum.Second = TimeSlot.Second;
  AddSlotNum.MsTime = AdTime.uiRemainSlot;
  AddSlotNum.SendNum = 0;
  ReSendNumE = 0;
  SetFlags |= EVENT_GENERT;
  if( (SysTimeSlot != Sen_UpLine) && (TimeSlotMode == SNP_PHR_TYPE_UP_LINE) && (!(SetFlags & DOWN_CODE_CFG)) )
    { 
      flag = 0;
      if(ConfigFlags & RECIVE_SEN_CFG)
         { flag |= 0x01;}
      if( TimeCommunicatFlag & STATE_SEND_ON )
         { flag |= 0x02; }
       DownLineEvent();// DownLineConfig(); 
      if( flag & 0x01 )
       { ConfigFlags |= RECIVE_SEN_CFG; }
      if( flag & 0x02 )
       { TimeCommunicatFlag |= STATE_SEND_ON; }
    }
  //   UartSendStrings("evevt save");  
// UartSendStrings("\r\n");
}

void SaveEvent( u8 Type)
{
  u8 SecondType;
  u8 flag;
  if( TimeSlot.Hour >= 24 )
   { TimeSlot.Hour = 0; }
  if( Type == ON )
    {  
      SecondType =  TimeSlot.Second | 0x80;           
    }
  else
    { 
      SecondType =  TimeSlot.Second & 0x7F;
      TempBaseFlag &= ~EVENT_ON_GENERT;     
    }

  EventBuff.Event[EventBuff.SavePtr].Hour = TimeSlot.Hour;
  EventBuff.Event[EventBuff.SavePtr].Hour |= 0x80;
  EventBuff.Event[EventBuff.SavePtr].Minute = TimeSlot.Minute;
  EventBuff.Event[EventBuff.SavePtr].Second = SecondType;
  LastEvent.Hour = EventBuff.Event[EventBuff.SavePtr].Hour;
  LastEvent.Minute = EventBuff.Event[EventBuff.SavePtr].Minute;
  LastEvent.Second = EventBuff.Event[EventBuff.SavePtr].Second;
  EventBuff.EventNum++;
  EventBuff.SavePtr++;
  if( EventBuff.SavePtr >= SAVE_BUFF_NUM )
    { EventBuff.SavePtr = 0; }
  AddSlotNum.SenID = RfParamt.SenID;
  AddSlotNum.Second = TimeSlot.Second;
  AddSlotNum.MsTime = AdTime.uiRemainSlot;
  AddSlotNum.SendNum = 0;
  ReSendNumE = 0;
  SetFlags |= EVENT_GENERT;
  if( (SysTimeSlot != Sen_UpLine) && (TimeSlotMode == SNP_PHR_TYPE_UP_LINE) && (!(SetFlags & DOWN_CODE_CFG)) )
    { 
      flag = 0;
      if(ConfigFlags & RECIVE_SEN_CFG)
         { flag |= 0x01;}
      if( TimeCommunicatFlag & STATE_SEND_ON )
         { flag |= 0x02; }
       DownLineEvent();// DownLineConfig(); 
      if( flag & 0x01 )
       { ConfigFlags |= RECIVE_SEN_CFG; }
      if( flag & 0x02 )
       { TimeCommunicatFlag |= STATE_SEND_ON; }
    }
    // UartSendStrings("evevt save");  
// UartSendStrings("\r\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseLineUpdataZ(void)
{
 // u8 i;
  u16 temp;
  UpdataBasline(Magnetic.AxisZ1,&AxisZ1Pam); 
  StableBaseLineZ.BaseLineTime++;
  if(StableBaseLineZ.BaseLineTime >= BASE_LING_DELAY)
    {    
          StableBaseLineZ.BaseLineTime = 0;                        
          StableBaseLineZ.pBaseLine = (u16)AxisZ1Pam.pBaseLine;
          if( StableBaseLineZ.pBaseLine > AxisZ1Pam.BaseLine )
            {  
              temp = StableBaseLineZ.pBaseLine - AxisZ1Pam.BaseLine;
             if( temp < MIN_EVENT_VALUE )
                { StableBaseLineZ.PositiveNum++; }
            }
          else if( StableBaseLineZ.pBaseLine < AxisZ1Pam.BaseLine )
            { 
              temp = AxisZ1Pam.BaseLine - StableBaseLineZ.pBaseLine; 
             if( temp < MIN_EVENT_VALUE )
                { StableBaseLineZ.NegativeNum++; }
            }               
// UartSendStrings("**********Z:"); 
 // UartSendNumber(StableBaseLineZ.pBaseLine);   
  //UartSendStrings("X:"); 
  //UartSendNumber(StableBaseLine.pBaseLineX);  
 // UartSendStrings("**********NUm:"); 
 //UartSendNumber(StableBaseLineZ.GenerateNum);  
          StableBaseLineZ.GenerateNum++;
          if( StableBaseLineZ.GenerateNum >= STABLE_BASELINE_UPDATE_NUM)
          {
            StableBaseLineZ.GenerateNum = 0;
            if( StableBaseLineZ.PositiveNum > 35 ) 
               { 
                 AxisZ1Pam.BaseLine++;
               //  BaseTimeStartZ();
                // SetBaseLineZ++;
                 BasAddNumZ++;
                 BasDecNumZ = 0;
                 BaseLineFlag |= BS_SMOOTH_UP_Z;
                 BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                 if( BasAddNumZ >= 1 )
                 { TempBaseFlag |= BASE_UPDATE_ON_Z; }
               }
            else if( StableBaseLineZ.NegativeNum > 35 )
               { 
                 AxisZ1Pam.BaseLine--; 
               //  BaseTimeStartZ();
                // SetBaseLineZ--;
                 BasDecNumZ++;
                 BasAddNumZ = 0;
                 BaseLineFlag |= BS_SMOOTH_DOWN_Z;
                 BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                 if( BasDecNumZ >= 1 )
                   { TempBaseFlag |= BASE_UPDATE_ON_Z; }
               }
            else if( (BaseLineFlag & BS_SMOOTH_UP_Z) && (StableBaseLineZ.NegativeNum > 4) )
              {
                AxisZ1Pam.BaseLine--;    
              //  BaseTimeStartZ();
               // SetBaseLineZ--;
                BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                if( BasAddNumZ > 0 )
                 { BasAddNumZ--;}
              }
            else if( (BaseLineFlag & BS_SMOOTH_DOWN_Z) && (StableBaseLineZ.PositiveNum > 4) )
              {
                AxisZ1Pam.BaseLine++; 
              //  BaseTimeStartZ();
               // SetBaseLineZ++;
                BaseLineFlag &= ~BS_SMOOTH_DOWN_Z;
                BaseLineFlag &= ~BS_SMOOTH_UP_Z;
                if( BasDecNumZ > 0 )
                  { BasDecNumZ--; }
              }           
            AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine;
            StableBaseLineZ.PositiveNum = 0;
            StableBaseLineZ.NegativeNum = 0;  
            if( TempBaseFlag & BASE_UPDATE_ON_Z )
            {
              BasCountZ++;             
              if( BasCountZ >= 3 )
              {
                TempBaseFlag &= ~BASE_UPDATE_ON_Z;
                BasCountZ = 0;               
                if(BasAddNumZ >= 2)
                  { 
                    AxisZ1Pam.BaseLine -= BasAddNumZ;
                  }
                else if( BasDecNumZ >= 2 )
                  { 
                    AxisZ1Pam.BaseLine += BasDecNumZ; 
                  }
                BasAddNumZ = 0;
                BasDecNumZ = 0;
              }
            }
 // UartSendStrings("******UpBZ:"); 
 // UartSendNumber(AxisZ1Pam.BaseLine);   
          }  
    }               
}

void BaseLineUpdataX(void)
{
//  u8 i;
  u16 temp;
  UpdataBasline(Magnetic.AxisX1,&AxisX1Pam);    
  StableBaseLineX.BaseLineTime++;
  if(StableBaseLineX.BaseLineTime >= BASE_LING_DELAY)
    {    
          StableBaseLineX.BaseLineTime = 0;                        
          StableBaseLineX.pBaseLine = (u16)AxisX1Pam.pBaseLine;   
          if( StableBaseLineX.pBaseLine > AxisX1Pam.BaseLine )
            {  
              temp = StableBaseLineX.pBaseLine - AxisX1Pam.BaseLine;
              if( temp < MIN_EVENT_VALUE )
                { StableBaseLineX.PositiveNum++; }
            }
          else if( StableBaseLineX.pBaseLine < AxisX1Pam.BaseLine )
            { 
              temp = AxisX1Pam.BaseLine - StableBaseLineX.pBaseLine;
              if( temp < MIN_EVENT_VALUE )
               { StableBaseLineX.NegativeNum++; }
            }
                  
 //UartSendStrings("Z:"); 
 // UartSendNumber(StableBaseLine.pBaseLineZ);   
 // UartSendStrings("X:"); 
  //UartSendNumber(StableBaseLineX.pBaseLine);        
          StableBaseLineX.GenerateNum++;
          if( StableBaseLineX.GenerateNum >= STABLE_BASELINE_UPDATE_NUM)
          {
            StableBaseLineX.GenerateNum = 0;
            if( StableBaseLineX.PositiveNum > 35 ) 
               { 
                 AxisX1Pam.BaseLine++;
                // BaseTimeStartX();
               //  SetBaseLineX++;
                 BasAddNumX++;
                 BasDecNumX = 0;
                 BaseLineFlag |= BS_SMOOTH_UP_X;
                 BaseLineFlag &= ~BS_SMOOTH_DOWN_X;
                 if( BasAddNumX >= 1 )
                   { TempBaseFlag |= BASE_UPDATE_ON_X;}                
               }
            else if( StableBaseLineX.NegativeNum > 35 )
               { 
                 AxisX1Pam.BaseLine--; 
                // BaseTimeStartX();
              //   SetBaseLineX--;
                 BasDecNumX++;
                 BasAddNumX = 0;
                 BaseLineFlag |= BS_SMOOTH_DOWN_X;
                 BaseLineFlag &= ~BS_SMOOTH_UP_X;
                 if( BasDecNumX >= 1 )
                   { TempBaseFlag |= BASE_UPDATE_ON_X; }
               }
            else if( (BaseLineFlag & BS_SMOOTH_UP_X) && (StableBaseLineX.NegativeNum > 4) )
              {
                AxisX1Pam.BaseLine--; 
              //  BaseTimeStartX();
              //  SetBaseLineX--;
                BaseLineFlag &= ~BS_SMOOTH_DOWN_X;
                BaseLineFlag &= ~BS_SMOOTH_UP_X;
                if( BasAddNumX > 0 ) 
                  { BasAddNumX--; }
              }
            else if( (BaseLineFlag & BS_SMOOTH_DOWN_X) && (StableBaseLineX.PositiveNum > 4) )
              {
                AxisX1Pam.BaseLine++; 
              //  BaseTimeStartX();
               // SetBaseLineX++;
                BaseLineFlag &= ~BS_SMOOTH_DOWN_X;
                BaseLineFlag &= ~BS_SMOOTH_UP_X;
                if( BasDecNumX > 0 )
                  { BasDecNumX--; }
              }
            
  
            AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;
            StableBaseLineX.PositiveNum = 0;
            StableBaseLineX.NegativeNum = 0;  
            if( TempBaseFlag & BASE_UPDATE_ON_X )
            {
              BasCountX++;             
              if( BasCountX >= 3 )
              {
                TempBaseFlag &= ~BASE_UPDATE_ON_X;
                BasCountX = 0;               
                if(BasAddNumX >= 2)
                  { 
                    AxisX1Pam.BaseLine -= BasAddNumX;
                  }
                else if( BasDecNumX >= 2 )
                  { 
                    AxisX1Pam.BaseLine += BasDecNumX; 
                  }
                BasAddNumX = 0;
                BasDecNumX = 0;
              }
            }
   
 // UartSendStrings("*******UBX:"); 
 //UartSendNumber(AxisX1Pam.BaseLine);
          }  
    }               
}




void OnEventGetBaseLineZ(void)
{
  u16 temp;
  u16 temp2;
  //u8 temp3;
  //u8 temp4;
  if(  Magnetic.AxisZ1 > OnGreatEventZ )
    { OnGreatEventZ = Magnetic.AxisZ1; }
  else if( Magnetic.AxisZ1 < OnSmallEventZ )
    { OnSmallEventZ = Magnetic.AxisZ1; }
  
  if( AdTime.EventBaselineSecondZ >= 30 ) //////////////////////////////////////////////////////////////////////////
    { 
      AdTime.EventBaselineSecondZ = 0;
      HalfBaseLineFlag |= ON_EVENT_BASELINE_GET_ON_Z; 
      OnBaseLineZ.pBaseLine = Magnetic.AxisZ1;
    } 

  if( HalfBaseLineFlag & ON_EVENT_BASELINE_GET_ON_Z )
  {
     UpdataBasline(Magnetic.AxisZ1,&OnBaseLineZ);  
     OnStableBaseLineZ.BaseLineTime++;
     if( OnStableBaseLineZ.BaseLineTime >= BASE_LING_DELAY )
     {
       OnStableBaseLineZ.BaseLineTime = 0;
       HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_ON_Z;
     //  SensorRest();
       temp = OnGreatEventZ - OnSmallEventZ;
       if( temp >= 8 )
          {
            OnGreatEventZ = Magnetic.AxisZ1;
            OnSmallEventZ = Magnetic.AxisZ1;  
            memset(&OnBaseLineBuffZ,0,sizeof(OnBaseLineBuffZ));
            return;
          }
       OnGreatEventZ = Magnetic.AxisZ1;
       OnSmallEventZ = Magnetic.AxisZ1;
       if( OnBaseLineBuffZ.Num < 3 )
        {
          OnBaseLineBuffZ.BaseLine[OnBaseLineBuffZ.Num] = (u16)OnBaseLineZ.pBaseLine;
          OnBaseLineBuffZ.Num++;
 // UartSendStrings("On get Num:"); 
//UartSendNumber(OnBaseLineBuffZ.Num);      
        }
       if( OnBaseLineBuffZ.Num >= 3 )
        {
          if( OnBaseLineBuffZ.BaseLine[0] > OnBaseLineBuffZ.BaseLine[1] )
             { temp = OnBaseLineBuffZ.BaseLine[0] - OnBaseLineBuffZ.BaseLine[1]; }
          else
             { temp = OnBaseLineBuffZ.BaseLine[1] - OnBaseLineBuffZ.BaseLine[0]; }
          if( OnBaseLineBuffZ.BaseLine[0] > OnBaseLineBuffZ.BaseLine[2] )
             { temp2 = OnBaseLineBuffZ.BaseLine[0] - OnBaseLineBuffZ.BaseLine[2]; }
          else
             { temp2 = OnBaseLineBuffZ.BaseLine[2] - OnBaseLineBuffZ.BaseLine[0]; }
          if( (temp < 2) && (temp2 < 2) && (OnBaseLineBuffZ.BaseLine[0] > MIN_BASE) && (OnBaseLineBuffZ.BaseLine[0] < MAX_BASE) )
            {
               LastOnBaseLineZ = OnBaseLineZ.BaseLine;
               OnBaseLineZ.BaseLine = OnBaseLineBuffZ.BaseLine[0];
               OnTempBaseZ.pBaseLine = (float)OnBaseLineZ.BaseLine;              
               TempPositiveCntZ = 0;
               TempNegitiveCntZ = 0;
               BasAddNumZ = 0;
               BasDecNumZ = 0; 
               BasCountZ = 0;     
              // pOnBaseLineZ = OnBaseLineZ.BaseLine;
               pBaseLineTempZ = AxisZ1Pam.BaseLine;
               AdTime.TempBaseSecondZ = 0;
               TempBaseFlag &= ~BASE_UPDATE_ON_Z;
               HalfBaseLineFlag |= ON_EVENT_BASELINE_GET_Z;
               NewBaseFlag &= ~OTHER_TEMP_X_ON;
               AdTime.TempBaseSecondZ = TEMP_BASE_TIME;  
               if( (ExtraFlags & ON_BASELIN_GENERT_Z) && (LastSend.Second & 0x80) && (HalfBaseLineFlag & ON_EVENT_BASELINE_GET_X) )
                 { OnAddOff(); }
               ExtraFlags |= ON_BASELIN_GENERT_Z;
               OnStableBaseLineZ.PositiveNum = 0;
               OnStableBaseLineZ.NegativeNum = 0;
               OnBaseLineZ.pBaseLine = (float)OnBaseLineZ.BaseLine;
               memset(&OnBaseLineBuffZ,0,sizeof(OnBaseLineBuffZ)); 
               temp = DecBigTerg( OnBaseLineZ.BaseLine, AxisZ1Pam.BaseLine,10);  
               if( temp == 0)
                 {  NewBaseFlag |= MAX_THRES_VALUE_Z;  }
             /*  temp = DecDect(OnBaseLineZ.BaseLine, AxisZ1Pam.BaseLine );
               if( temp == 0)
                 {  CompFlags |= EFFECT_ON_Z; }
               else
                 {  CompFlags &= ~EFFECT_ON_Z; }*/
               if(OnBaseGetNumZ<10)
                 { OnBaseGetNumZ++; }

 //UartSendStrings("OnBZ:"); 
//UartSendNumber(OnBaseLineZ.BaseLine);                 
            }
          else
            { memset(&OnBaseLineBuffZ,0,sizeof(OnBaseLineBuffZ)); }
        }
     }
  }
}

void OnEventGetBaseLineX(void)
{
  u16 temp;
  u16 temp2;
 // u8 temp3;
  //u8 temp4;
  if(  Magnetic.AxisX1 > OnGreatEventX )
    { OnGreatEventX = Magnetic.AxisX1; }
  else if( Magnetic.AxisX1 < OnSmallEventX )
    { OnSmallEventX = Magnetic.AxisX1; }
  if( AdTime.EventBaselineSecondX >= 30 )
    { 
      AdTime.EventBaselineSecondX = 0;
      HalfBaseLineFlag |= ON_EVENT_BASELINE_GET_ON_X; 
      OnBaseLineX.pBaseLine = Magnetic.AxisX1;
    } 
  if( HalfBaseLineFlag & ON_EVENT_BASELINE_GET_ON_X )
  {
     UpdataBasline(Magnetic.AxisX1,&OnBaseLineX);  
     OnStableBaseLineX.BaseLineTime++;
     if( OnStableBaseLineX.BaseLineTime >= BASE_LING_DELAY )
     {
       OnStableBaseLineX.BaseLineTime = 0;
       HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_ON_X;
     //  SensorRest();
       temp = OnGreatEventX - OnSmallEventX;
       if( temp >= 8 )
          {
            OnGreatEventX = Magnetic.AxisX1;
            OnSmallEventX = Magnetic.AxisX1;  
            memset(&OnBaseLineBuffX,0,sizeof(OnBaseLineBuffX));
            return;
          }
       OnGreatEventX = Magnetic.AxisX1;
       OnSmallEventX = Magnetic.AxisX1;
       if( OnBaseLineBuffX.Num < 3 )
        {
          OnBaseLineBuffX.BaseLine[OnBaseLineBuffX.Num] = (u16)OnBaseLineX.pBaseLine;
          OnBaseLineBuffX.Num++;
   //  UartSendStrings("On get NumX:"); 
   //  UartSendNumber(OnBaseLineBuffX.Num);      
        }
       if( OnBaseLineBuffX.Num >= 3 )
       {
          if( OnBaseLineBuffX.BaseLine[0] > OnBaseLineBuffX.BaseLine[1] )
             { temp = OnBaseLineBuffX.BaseLine[0] - OnBaseLineBuffX.BaseLine[1]; }
          else
             { temp = OnBaseLineBuffX.BaseLine[1] - OnBaseLineBuffX.BaseLine[0]; }
          if( OnBaseLineBuffX.BaseLine[0] > OnBaseLineBuffX.BaseLine[2] )
             { temp2 = OnBaseLineBuffX.BaseLine[0] - OnBaseLineBuffX.BaseLine[2]; }
          else
             { temp2 = OnBaseLineBuffX.BaseLine[2] - OnBaseLineBuffX.BaseLine[0]; }
          if( (temp < 2) && (temp2 < 2) && (OnBaseLineBuffX.BaseLine[0] > MIN_BASE) && (OnBaseLineBuffX.BaseLine[0] < MAX_BASE) )
          {
             LastOnBaseLineX = OnBaseLineX.BaseLine;
             OnBaseLineX.BaseLine = OnBaseLineBuffX.BaseLine[0];
             OnTempBaseX.pBaseLine = (u16)OnBaseLineX.BaseLine;
             TempPositiveCntX = 0;
             TempNegitiveCntX = 0;
             BasAddNumX = 0;
             BasDecNumX = 0;
             BasCountX = 0;       
            // pOnBaseLineX = OnBaseLineX.BaseLine;
             pBaseLineTempX = AxisX1Pam.BaseLine; 
             TempBaseFlag &= ~BASE_UPDATE_ON_X;              
             AdTime.TempBaseSecondX = 0;
             HalfBaseLineFlag |= ON_EVENT_BASELINE_GET_X;
             AdTime.TempBaseSecondX = TEMP_BASE_TIME;
             if( (ExtraFlags & ON_BASELIN_GENERT_X) && (LastSend.Second & 0x80) && (HalfBaseLineFlag & ON_EVENT_BASELINE_GET_Z) )
               {  OnAddOff(); }
             ExtraFlags |= ON_BASELIN_GENERT_X;
             NewBaseFlag &= ~OTHER_TEMP_Z_ON;
             OnStableBaseLineX.PositiveNum = 0;
             OnStableBaseLineX.NegativeNum = 0;
            // ExtraFlags &= ~MIN_OFF_SEND_X;
             OnBaseLineX.pBaseLine = (float)OnBaseLineX.BaseLine;
             memset(&OnBaseLineBuffX,0,sizeof(OnBaseLineBuffX)); 
             temp = DecBigTerg( OnBaseLineX.BaseLine, AxisX1Pam.BaseLine,10);  
             if( temp == 0)
               {  NewBaseFlag |= MAX_THRES_VALUE_X;  }
           /*  temp = DecDect(OnBaseLineX.BaseLine,AxisX1Pam.BaseLine);
             if(temp == 0)
                {  CompFlags |= EFFECT_ON_X;  }
             else
                {  CompFlags &= ~EFFECT_ON_X;  }*/
             if(OnBaseGetNumX < 10)
               { OnBaseGetNumX++; }
//UartSendStrings("OnBX:"); 
// UartSendNumber(OnBaseLineX.BaseLine);         
          }
        else
           { memset(&OnBaseLineBuffX,0,sizeof(OnBaseLineBuffX)); }               
       }    
    }   
  }
}

void OnAddOff(void)
{
   u16 temp1,temp2;
   temp1 =  DecBigTerg( OnBaseLineZ.BaseLine, LastOnBaseLineZ,9);  
   temp2 =  DecBigTerg( OnBaseLineX.BaseLine, LastOnBaseLineX,9);  
   if( (temp1 == 0) || (temp2 == 0) )
    { SaveEvent(OFF); }
}

void AnyBaseLineUpdateZ( STABLE_BASELINE *StableBaseZ, SENSOR_SAMPLE_PARAMTER *EventZ)
{
  u16 temp3;
  u8 i;
  UpdataBasline(Magnetic.AxisZ1,EventZ);  
  StableBaseZ->BaseLineTime++;
  if( StableBaseZ->BaseLineTime >= BASE_LING_DELAY )
  {
    StableBaseZ->BaseLineTime = 0;
    StableBaseZ->pBaseLine = (u16)EventZ->pBaseLine;
    if( StableBaseZ->pBaseLine > EventZ->BaseLine )
       { 
         temp3 = StableBaseZ->pBaseLine - EventZ->BaseLine;
         if( temp3 < MIN_EVENT_VALUE )
            { StableBaseZ->PositiveNum++; }
       }
    else if( StableBaseZ->pBaseLine < EventZ->BaseLine )
       { 
         temp3 = EventZ->BaseLine - StableBaseZ->pBaseLine;
         if( temp3 < MIN_EVENT_VALUE )
           { StableBaseZ->NegativeNum++; }
       }
    
    StableBaseZ->GenerateNum++;
    if( StableBaseZ->GenerateNum >= STABLE_BASELINE_UPDATE_NUM )
    {
      StableBaseZ->GenerateNum = 0;
      if( StableBaseZ->PositiveNum > 35 )
      {
        EventZ->BaseLine++;
       // SetBaseLineZ++;
        BaseLineFlag |= SMOOTH_UP_Z;
        BaseLineFlag &= ~SMOOTH_DOWN_Z;
        AxisZ1Pam.BaseLine++; 
      //  BaseTimeStartZ();
        OnTempBaseZ.BaseLine++;
        TempPositiveCntZ = 0;
        TempNegitiveCntZ = 0;                                
        if(ExtraFlags & ON_GET_BASELINE)
        {
          BaseChgOnIntZ++;
          for(i=0;i<BASE_NUM;i++)
          {
            if(BaseLineBuff.BaseBuff[i].BaseZ > 0)
            { BaseLineBuff.BaseBuff[i].BaseZ++; }
          }
        }
        BasAddNumZ++;
        BasDecNumZ = 0;
        if( BasAddNumZ >= 1 )
          { TempBaseFlag |= BASE_UPDATE_ON_Z; }
      }
      else if( StableBaseZ->NegativeNum > 35 )
      {
        EventZ->BaseLine--;
      //  SetBaseLineZ--;
        BaseLineFlag |= SMOOTH_DOWN_Z;
        BaseLineFlag &= ~SMOOTH_UP_Z;
        AxisZ1Pam.BaseLine--; 
      //  BaseTimeStartZ();
        OnTempBaseZ.BaseLine--;
        TempPositiveCntZ = 0;
        TempNegitiveCntZ = 0;
        if(ExtraFlags & ON_GET_BASELINE)
        {
          BaseChgOnIntZ--;
          for(i=0;i<BASE_NUM;i++)
          {
            if(BaseLineBuff.BaseBuff[i].BaseZ > 0)
            { BaseLineBuff.BaseBuff[i].BaseZ--; }
          }
        }
        BasDecNumZ++;
        BasAddNumZ = 0;       
        if( BasDecNumZ >= 1 )
          { TempBaseFlag |= BASE_UPDATE_ON_Z; }
      }
      else if( (BaseLineFlag & SMOOTH_UP_Z) && (StableBaseZ->NegativeNum > 4) )
      {
        EventZ->BaseLine--;
       // SetBaseLineZ--;
        BaseLineFlag &= ~SMOOTH_DOWN_Z;
        BaseLineFlag &= ~SMOOTH_UP_Z;
        AxisZ1Pam.BaseLine--; 
      //  BaseTimeStartZ();
        OnTempBaseZ.BaseLine--;
        TempPositiveCntZ = 0;
        TempNegitiveCntZ = 0;
        if(ExtraFlags & ON_GET_BASELINE)
        {
          BaseChgOnIntZ--;
          for(i=0;i<BASE_NUM;i++)
          {
            if(BaseLineBuff.BaseBuff[i].BaseZ > 0)
            { BaseLineBuff.BaseBuff[i].BaseZ--; }
          }
        }
        if( BasAddNumZ > 0 )
          { BasAddNumZ--;}
      }
      else if( (BaseLineFlag & SMOOTH_DOWN_Z) && (StableBaseZ->PositiveNum > 4) )
      {
        EventZ->BaseLine++;
       // SetBaseLineZ++;
        BaseLineFlag &= ~SMOOTH_DOWN_Z;
        BaseLineFlag &= ~SMOOTH_UP_Z;
        AxisZ1Pam.BaseLine++; 
     //  BaseTimeStartZ();
        OnTempBaseZ.BaseLine++;
        TempPositiveCntZ = 0;
        TempNegitiveCntZ = 0;
        if(ExtraFlags & ON_GET_BASELINE)
        {
          BaseChgOnIntZ++;
          for(i=0;i<BASE_NUM;i++)
          {
            if(BaseLineBuff.BaseBuff[i].BaseZ > 0)
            { BaseLineBuff.BaseBuff[i].BaseZ++; }
          }
        }
        if( BasDecNumZ > 0 )
           { BasDecNumZ--;}
      }
      EventZ->pBaseLine = (float)EventZ->BaseLine;
      StableBaseZ->PositiveNum = 0;
      StableBaseZ->NegativeNum = 0;
      if( TempBaseFlag & BASE_UPDATE_ON_Z )
            {
              BasCountZ++;             
              if( BasCountZ >= 3 )
              {
                TempBaseFlag &= ~BASE_UPDATE_ON_Z;
                BasCountZ = 0;               
                if(BasAddNumZ >= 2)
                  { 
                    AxisZ1Pam.BaseLine -= BasAddNumZ; 
                  //  SetBaseLineZ -= BasAddNumZ;
                  }
                else if( BasDecNumZ >= 2 )
                  { 
                    AxisZ1Pam.BaseLine += BasDecNumZ; 
                   // BasAddNumZ += BasDecNumZ;
                  }
                BasAddNumZ = 0;
                BasDecNumZ = 0;
                if((OnBaseGetNumZ == 1) && (pBaseLineTempZ != AxisZ1Pam.BaseLine))
                {
                  AxisZ1Pam.BaseLine = pBaseLineTempZ;
                  OnBaseGetNumZ = 0;
                  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_Z;    
                }
                else
                {  OnBaseGetNumZ = 2; }
              }
            }     
   //  UartSendStrings("UpdataHZ:"); 
 // UartSendNumber(EventZ->BaseLine);   
    }
  }
}

void AnyBaseLineUpdateX( STABLE_BASELINE *StableBaseX, SENSOR_SAMPLE_PARAMTER *EventX )
{
  u16 temp3;
  u8 i;
  UpdataBasline(Magnetic.AxisX1,EventX);  
  StableBaseX->BaseLineTime++;
  if( StableBaseX->BaseLineTime >= BASE_LING_DELAY )
  {
     StableBaseX->BaseLineTime = 0;
     StableBaseX->pBaseLine = (u16)EventX->pBaseLine;
     if( StableBaseX->pBaseLine > EventX->BaseLine )
        {  
          temp3 = StableBaseX->pBaseLine - EventX->BaseLine;
          if( temp3 < MIN_EVENT_VALUE )
            { StableBaseX->PositiveNum++; }
        }
     else if( StableBaseX->pBaseLine < EventX->BaseLine )
        { 
          temp3 = EventX->BaseLine - StableBaseX->pBaseLine;
          if( temp3 < MIN_EVENT_VALUE )
           { StableBaseX->NegativeNum++; }
        }
     StableBaseX->GenerateNum++;
     if( StableBaseX->GenerateNum >= STABLE_BASELINE_UPDATE_NUM )
     {
        StableBaseX->GenerateNum = 0;
        if( StableBaseX->PositiveNum > 35 )
         {
           EventX->BaseLine++;
          // SetBaseLineX++;
           BaseLineFlag |= SMOOTH_UP_X;
           BaseLineFlag &= ~SMOOTH_DOWN_X;
           AxisX1Pam.BaseLine++; 
          // BaseTimeStartX();
           OnTempBaseX.BaseLine++;
           TempPositiveCntX = 0;
           TempNegitiveCntX = 0;
           if(ExtraFlags & ON_GET_BASELINE)
           {
             BaseChgOnIntX++;
             for(i=0;i<BASE_NUM;i++)
             {
               if(BaseLineBuff.BaseBuff[i].BaseX > 0)
                 { BaseLineBuff.BaseBuff[i].BaseX++; }
              }
            }
           BasAddNumX++;
           BasDecNumX = 0;
           if( BasAddNumX >= 1 )
             { TempBaseFlag |= BASE_UPDATE_ON_X;}        
         }
        else if( StableBaseX->NegativeNum > 35 )
         {
           EventX->BaseLine--;
          // SetBaseLineX--;
           BaseLineFlag |= SMOOTH_DOWN_X;
           BaseLineFlag &= ~SMOOTH_UP_X;
           AxisX1Pam.BaseLine--; 
          // BaseTimeStartX();
           OnTempBaseX.BaseLine--;
           TempPositiveCntX = 0;
           TempNegitiveCntX = 0;
           if(ExtraFlags & ON_GET_BASELINE)
           {
             BaseChgOnIntX--;
             for(i=0;i<BASE_NUM;i++)
             {
               if(BaseLineBuff.BaseBuff[i].BaseX > 0)
                 { BaseLineBuff.BaseBuff[i].BaseX--; }
              }
            }
            BasDecNumX++;
            BasAddNumX = 0;       
            if( BasDecNumX >= 1 )
             { TempBaseFlag |= BASE_UPDATE_ON_X;}    
         }
        else if( (BaseLineFlag & SMOOTH_UP_X) && (StableBaseX->NegativeNum > 4) )
         {
           EventX->BaseLine--;
          // SetBaseLineX--;
           BaseLineFlag &= ~SMOOTH_DOWN_X;
           BaseLineFlag &= ~SMOOTH_UP_X;
           AxisX1Pam.BaseLine--;
         //  BaseTimeStartX();
           OnTempBaseX.BaseLine--;
           TempPositiveCntX = 0;
           TempNegitiveCntX = 0;
           if(ExtraFlags & ON_GET_BASELINE)
           {
             BaseChgOnIntX--;
             for(i=0;i<BASE_NUM;i++)
             {
               if(BaseLineBuff.BaseBuff[i].BaseX > 0)
                 { BaseLineBuff.BaseBuff[i].BaseX--; }
              }
            }
            if( BasAddNumX > 0 )
               { BasAddNumX--;}
         }
        else if( (BaseLineFlag & SMOOTH_DOWN_X) && (StableBaseX->PositiveNum > 4) )
         {
           EventX->BaseLine++;
          // SetBaseLineX++;
           BaseLineFlag &= ~SMOOTH_DOWN_X;
           BaseLineFlag &= ~SMOOTH_UP_X;
           AxisX1Pam.BaseLine++; 
          // BaseTimeStartX();
           OnTempBaseX.BaseLine++;
           TempPositiveCntX = 0;
           TempNegitiveCntX = 0;
           if(ExtraFlags & ON_GET_BASELINE)
           {
             BaseChgOnIntX++;
             for(i=0;i<BASE_NUM;i++)
             {
               if(BaseLineBuff.BaseBuff[i].BaseX > 0)
                 { BaseLineBuff.BaseBuff[i].BaseX++; }
              }
            }
           if( BasDecNumX > 0 )
           { BasDecNumX--;}
        }
        EventX->pBaseLine = (float)EventX->BaseLine;
        StableBaseX->PositiveNum = 0;
        StableBaseX->NegativeNum = 0;
        if( TempBaseFlag & BASE_UPDATE_ON_X )
            {
              BasCountX++;             
              if( BasCountX >= 3 )
              {
                TempBaseFlag &= ~BASE_UPDATE_ON_X;
                BasCountX = 0;               
                if(BasAddNumX >= 2)
                  { 
                    AxisX1Pam.BaseLine -= BasAddNumX;
                  //  SetBaseLineX -= BasAddNumX;
                  }
                else if( BasDecNumX >= 2 )
                  { 
                    AxisX1Pam.BaseLine += BasDecNumX; 
                   // SetBaseLineX += BasDecNumX;
                  }
                BasAddNumX = 0;
                BasDecNumX = 0;
                if((OnBaseGetNumX == 1) && (pBaseLineTempX != AxisX1Pam.BaseLine))
                {
                  AxisX1Pam.BaseLine = pBaseLineTempX;
                  OnBaseGetNumX = 0;
                  HalfBaseLineFlag &= ~ON_EVENT_BASELINE_GET_X;
                }
                else
                {  OnBaseGetNumX = 2;  }
              }
            }         
   //  UartSendStrings("UpdataHX:"); 
  //UartSendNumber(EventX->BaseLine);   
     }
  }
}



u16 GetBaseLineAny(u16 AdValue, SENSOR_SAMPLE_PARAMTER  *TempBaseLine, BASELINE_THREE_BUFF *BaseBuff )
{
  u16 temp1;
  u16 temp2;
  u16 Base;
  UpdataBasline(AdValue, TempBaseLine);  
  BaseBuff->Count++;
  Base = 0;
  if( BaseBuff->Count >= BASE_LING_DELAY )
  {
    BaseBuff->Count = 0;
    if( BaseBuff->Num < 3 )
    {   
      Base = 1;
      BaseBuff->BaseLine[BaseBuff->Num]= (u16)TempBaseLine->pBaseLine;
//UartSendStrings("ValueNum:"); 
 //UartSendNumber(BaseBuff->Num);         
//UartSendStrings("Value:"); 
 // UartSendNumber(BaseBuff->BaseLine[BaseBuff->Num]);          
      BaseBuff->Num++;         
    }
    if( BaseBuff->Num >= 3 )
    {
      if( BaseBuff->BaseLine[0] > BaseBuff->BaseLine[1] )
         { temp1 = BaseBuff->BaseLine[0] - BaseBuff->BaseLine[1]; }
      else
         { temp1 = BaseBuff->BaseLine[1] - BaseBuff->BaseLine[0]; }
      if( BaseBuff->BaseLine[0] > BaseBuff->BaseLine[2] )
        { temp2 = BaseBuff->BaseLine[0] - BaseBuff->BaseLine[2]; }
      else
        { temp2 = BaseBuff->BaseLine[2] - BaseBuff->BaseLine[0]; }
      if( (temp1 < 2) && (temp2 < 2 ) )
        { Base = BaseBuff->BaseLine[0];}
      else
        { Base = 0;  }
      memset(BaseBuff,0,sizeof(BASELINE_THREE_BUFF));
    }
  }
  return Base;
}

void FlashBuffUpdateZ(void)
{
  FlashBaseBuffZ[BaseBuffZPtr++] = AxisZ1Pam.BaseLine;
  if( BaseBuffZPtr >= BASE_BUFF_NUM)
    { BaseBuffZPtr = 0; }
  FlashBaseBuffX[BaseBuffXPtr++] = AxisX1Pam.BaseLine;
  if(BaseBuffXPtr>=BASE_BUFF_NUM)
    { BaseBuffXPtr = 0; }
  CompFlags |= FLASH_BASE_UPDATE;
  NewBaseFlag &= ~TEMP_BASE_UPDATE_Z;
}

void FlashBuffUpdateX(void)
{
  FlashBaseBuffX[BaseBuffXPtr++] = AxisX1Pam.BaseLine;
  if(BaseBuffXPtr>=BASE_BUFF_NUM)
    { BaseBuffXPtr = 0; }
  FlashBaseBuffZ[BaseBuffZPtr++] = AxisZ1Pam.BaseLine;
  if( BaseBuffZPtr >= BASE_BUFF_NUM)
    { BaseBuffZPtr = 0; }
  CompFlags |= FLASH_BASE_UPDATE;
  NewBaseFlag &= ~TEMP_BASE_UPDATE_X;
}

u8  AverageValueGet( AVERAGE_VALUE *TempValue, u16 AdValue )
{
    u8 temp;
    u8 ret;
    ret = 0;
    if( TempValue->Num < AverageValueTime )
      {
        temp = DecBigTerg( TempValue->Base , AdValue, 4 );
        if( temp == 1 )
          { 
            TempValue->Num++;
            if( TempValue->Num >= AverageValueTime )
            {
              TempValue->Num = 0;
              TempValue->LastValue = TempValue->Value;
              TempValue->Value = TempValue->Base;             
              TempValue->Base = AdValue; 
              ret = 1;
            }
          }
        else
          { 
            TempValue->Num = 0;
            TempValue->Base = AdValue;         
          }
      }
    return ret;
}

u8 ComperTempBuff( TEMP_BASE_BUFF *TempBuff )
{
  u8 temp1;
  u8 temp2;
  temp2 = 0;
  temp1 = DecBigTerg( TempBuff->BaseLine[0], TempBuff->BaseLine[1], 4);
  if(temp1 == 1)
    { temp2++; }
  temp1 = DecBigTerg( TempBuff->BaseLine[0], TempBuff->BaseLine[2], 4);
  if(temp1 == 1)
    { temp2++; }
  temp1 = DecBigTerg( TempBuff->BaseLine[1], TempBuff->BaseLine[2], 4);
  if(temp1 == 1)
    { temp2++; }
  if( temp2 >= 3 )
    { temp1 = 1; }
  else
    { temp1 = 0; }
  
  return temp1;
}

u8 AverageAdGet( OFF_AVERAGR_VALUE *TempValue, u16 AdValue )
{
  u8 temp;
  u8 ret;
  ret = 0;
  temp = DecBigTerg( TempValue->LastValue , AdValue, 4 );
  TempValue->LastValue = AdValue;
  if( temp == 1 )
  {
    TempValue->Sum += AdValue;
    TempValue->Num++;
    if( TempValue->Num >= 32 )
    {      
      TempValue->Value = TempValue->Sum>>5;
      TempValue->Num = 0;  
      TempValue->Sum = 0;
      ret = 1;       
    }
  }
  else
  {
    TempValue->Num = 0;  
    TempValue->Sum = 0;
  }
  return ret;
}