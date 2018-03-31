#include "types.h"
#include "hal_cc2520.h"
//#include "cc2420_rf.h"
#include "rf_hal.h"
#include "timeslot.h"
#include "snp.h"
#include "ad.h"
#include "board.h"
#include "uart.h"
#include "cfg.h"
#include "flash.h"
#include "magentic.h"
#include "24l01.h"
#include <string.h>

/**********************************************************************
 数据收发程序，需用NB-LOT程序替代
**************************************************************************/
extern u8 SysTimeSlot;
extern u16 TempBaseFlag;
extern u16 ReportTime;
extern u8 DownLineNum;
extern AD_TEST_PACKET_t AdValuePacket;
extern u8 NotScanSyncNum;
extern AD_TIME_CYCLE AdTime;
extern SNP_EVENT_t OnSaveBuff;
extern SNP_EVENT_t OffSaveBuff;
extern u8 EventBuffFlag;
extern SNP_SEN_MODE_PACKET_t EventPacket;
extern SNP_UPLINE_PACKET_t UplinePacket;
extern SNP_SEN_MODE_PACKET_t SenQueryPacket;
extern TIME_SLOT_PARMAT TimeSlot;
extern FLASH_PARAMTER_t  FlashParamt;//
extern SNP_EVENT_t EventA;
extern SNP_EVENT_t EventB;
extern u16 ConfigFlags;
extern u16 TimeCommunicatFlag;
extern u16 SingleFlag;
extern u16 AdMagenticFlags;
extern u16 TestRfDelay;
extern u16 PumpHigh;
extern u16 PumpLow;
extern u16 SetFlags;
extern u8 AdRestSecond;
extern u8 TimeSlotMode;
extern RF_PARAMTER RfParamt;
extern u8 RfSendFlags;
extern u8 PumpTbNum;
extern u8 NewLineOFF;
extern u8 TestDemo;
extern u16 DebugFlag;
extern u8 PumpTbNum;
extern u16 ReSendNum;
extern u8 OnNum;
extern u8 OffNum;
extern u8 BaseAverageNum;
extern u8 OnBaseChangeNum;
extern u8 RestSecond;
extern SNP_SEN_CFG_ACK_PACKET_t SenAckPacket;

SNP_UF_ACK_PACKET_t UfAckPacket;



u8 s_aucApBuffer[50];
u16 pTimeSlot;
u16 pSenID;
//int8 pRssi;
//int8 pSnr;
u8 DemoCnt=0;//
//u8 DemoSyncCnt = 0;



void RFDataPreprocess(void)
{
  u16	  uiRxSize=0; 
  memset(s_aucApBuffer,0,sizeof(s_aucApBuffer));
  uiRxSize = RFM98_LoRaRxPacket((u8 *)&s_aucApBuffer[0]);
  if( ((u16)uiRxSize > 1) && 
      ((u16)uiRxSize<0x40) &&
      (s_aucApBuffer[1]==FCF_DEF) )   
  { 
   ComandPro(); 
  }
/*  else if(uiRxSize == 0xff)
  {
    UartSendStrings("CRC error");  
    UartSendStrings("\r\n");   
  }*/
    
}

void ComandPro(void)
{
  //u8 i;
  u8 *ptr;
 // u16  ulSlotBm = 0;
  u8  SenSlotBm = 0; 
  u8 TempHigh;
  u8 TempLow;
//  int16 TestRssi;
  u16  temp;
  SNP_PHR_t	*psPhr	=(SNP_PHR_t * )&s_aucApBuffer[0];          //程序处理   
         switch (psPhr->uiType)
           {
             case RF_TEST_SYNC:
               {
                 temp = s_aucApBuffer[12];
                 temp |= s_aucApBuffer[13]<<8;
                 if( temp == RfParamt.SenID )
                 {
                  DebugFlag |= RF_DEMO_SYNC;
                  TimerA_RestCount(DEC_SYNC_TIME);  
                  SysTimeSlot = Sync_Frm1;
                  TimeSlot.TimeSlotNum = s_aucApBuffer[11];
                  TimeSlot.AllTimeSlotNum = s_aucApBuffer[6];
                  DownLineNum = 0;      
                 }
               }
             break;
             case RF_ALL_SYNC:
             {
               DebugFlag |= RF_ALL_SYNC_ON;
               TimerA_RestCount(DEC_SYNC_TIME);  
               SysTimeSlot = Sync_Frm1;
               TimeSlot.TimeSlotNum = s_aucApBuffer[11];
               TimeSlot.AllTimeSlotNum = s_aucApBuffer[6];
               DownLineNum = 0;  
             }
             break;
           /*  case RF_TEST_ACK:
             {
               DebugFlag &= ~RF_TEST_SEND;
               TestSnr = s_aucApBuffer[6];
               TestSnr |= s_aucApBuffer[7]<<8;
               NewLineOFF = 1;
                TestRssi = s_aucApBuffer[8];
                TestRssi |= s_aucApBuffer[9]<<8;
                 if( TestRssi < 0 )
                  {
                    UartSendStrings("RSSI:-"); 
                    UartSendNumber(0-TestRssi);                   
                  }
                  else
                  {
                    UartSendStrings("RSSI:"); 
                    UartSendNumber(TestRssi);  
                  }
                  UartSendStrings("  "); 
               if( TestSnr < 0)
                  {
                    UartSendStrings("SNR:-"); 
                    UartSendNumber(0-TestSnr);     
                  }
                  else
                  {
                    UartSendStrings("SNR:"); 
                    UartSendNumber(TestSnr);   
                  }                            
             }
             break;*/
             case SNP_PACKET_TYPE_SYNC:                //同步.
             case DOWN_CODE_SYNC:
               {        
                  DebugFlag &= ~RF_DEMO_SYNC;
                  TimeCommunicatFlag &= ~DEMO_SYNC; 
                  DebugFlag &= ~RF_ALL_SYNC_ON;
                  DebugFlag &= ~RF_DEMO_SYNC;
                  SetFlags &= ~TEST_DEMO_ON;
                 SyncProcess((SNP_SYNC_PACKET_t *)&s_aucApBuffer[0]);      
               }
             break;
             case SNP_PACKET_TYPE_SEN_CFG:           //SEN(Sensor)配置
              {     
                TimeCommunicatFlag &= ~DEMO_SYNC; 
                SetFlags &= ~TEST_DEMO_ON;
                DebugFlag &= ~RF_ALL_SYNC_ON;
                DebugFlag &= ~RF_DEMO_SYNC;
                SenCfgProcess((SNP_CFG_PACKET_t *)&s_aucApBuffer[0]);
              }
             break;
             case SNP_PACKET_TYPE_UF_DATA:         // 更新固件数据.
              {
                temp = s_aucApBuffer[6];
                temp |= s_aucApBuffer[7]<<8;
                if( (TimeSlotMode == SNP_DOWN_CODE_MODE) && (temp == RfParamt.SenID) )
                {
                  TimeSlot.RcvSyncNum = 0;
                  TimeCommunicatFlag &= ~DOWN_CODE_DOWN_LINE;
                  SenUfCfg((SNP_UF_DOWN_CODE_PACKET_t *)&s_aucApBuffer[0]);   
                  //P1OUT |= BIT3;
                }
              }
             break;
             case SNP_SET_ALL_PUMP:
             {
               DownLineNum = 0;
               temp = s_aucApBuffer[8];
               temp |= s_aucApBuffer[9]<<8;
                 if( temp == RfParamt.SenID )
                 {
                   PumpHigh = s_aucApBuffer[7];
                   PumpHigh |= 0x0600;
                   PumpLow = s_aucApBuffer[6] & 0x00FF;
                   PumpLow |= 0x0700;
                   ConfigFlags |= SAVE_PUMP_COMD;                 
                   ConfigFlags |= SET_PUMP;
                   SetFlags &= ~AD_WEAKUP;
                   DownLineConfig();   //配置通道(线下)
                   RFM98_REST_DOWN();
                   delay_us(200);
                   RFM98_REST_UP();
                   delay_ms(6);      
                 }
             }
             break;
             case SNP_TIMESLOT_UPLINE_ACK:
             {
                pSenID = 0;
                pSenID = s_aucApBuffer[6];
                pSenID |= s_aucApBuffer[7]<<8;                                 
                pTimeSlot = 0;
                pTimeSlot = s_aucApBuffer[8];
                pTimeSlot|= s_aucApBuffer[9]<<8;
                ptr = &s_aucApBuffer[10];
                TimeCommunicatFlag |= RECIVE_ACK;                                             
             }
             break;
             case SNP_PACKET_TYPE_AP_ACK:
             {                                     
                SenSlotBm = TimeSlot.MinTimeSlot - 1; 
                SenSlotBm <<= 1;
                ptr = &s_aucApBuffer[6+SenSlotBm];
                temp = *ptr++;
                temp |= *ptr<<8;
                if( (temp == RfParamt.SenID) && (TimeCommunicatFlag & EVENT_SEND) )
                   {  
                     TimeCommunicatFlag |= RECIVE_ACK; 
                     if( !(RfSendFlags & CONNECTED_AP) )
                       {
                         PumpTbNum = 0;
                         ReSendNum = 0;
                         BaseAverageNum = 0;
                         //OnBaseChangeNum = 0;
                         RfSendFlags |= CONNECTED_AP;   
                         TempBaseFlag |= UPLINE_AP_STATE;
                         TempHigh = PumpHigh;
                         TempLow = PumpLow;
                        // ReportTime = REPORT_SEND_TIME_7; 
                         if( (TempHigh != FlashParamt.PumpHigh) || (TempLow != FlashParamt.PumpLow) )
                           { ConfigFlags |= SAVE_PUMP_COMD; }
                         if( !(DebugFlag & PUMP_CHG_TEMP) )
                           { RestSecond = 120; }
                       }
                   }   
             }
            break;
            case TEST_DEMO_MODE:
             {
               temp = s_aucApBuffer[12];
               temp |= s_aucApBuffer[13]<<8;
               if( temp == RfParamt.SenID )
               {
                  TimerA_RestCount(DEC_SYNC_TIME);  
                  SysTimeSlot = Sync_Frm1;
                  TimeSlot.TimeSlotNum = s_aucApBuffer[11];
                  TimeSlot.AllTimeSlotNum = s_aucApBuffer[6];
                  DownLineNum = 0;
                  TimeCommunicatFlag |= DEMO_SYNC; 
                  SetFlags |= TEST_DEMO_ON;
                  AdRestSecond = REST_AD_DELAY;
                  if( s_aucApBuffer[15] == 0xaa)
                     { SetFlags |= SER_REST_COMD; }
               }
             }
            break;
            default:
            break;
          } 
  /* if((psPhr->uiType != 1)  )
    {
      UartSendStrings("type:"); 
  UartSendNumber(psPhr->uiType);
    }*/
}
//*************************************************test***********************************

