#include "types.h"
#include "ad.h"
//#include "cc2420_rf.h"
#include "uart.h"
#include "board.h"
#include "timeslot.h"
#include "rf_hal.h"
#include "snp.h"
#include "cfg.h"
#include "flash.h"
#include "ad.h"
#include "24l01.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magentic.h"
#include "..\bc95\brd_bc95.h"

MessageStruct 	 msg_buffer;
MessageStruct 	*msg;

extern CLOCK_VALUE Clock;
extern FLASH_PARAMTER_t  FlashParamt;
extern RF_PARAMTER RfParamt;
extern TIME_SLOT_PARMAT TimeSlot;
extern u16 PumpHigh;
extern u16 PumpLow;
extern u16 ReportTime;
extern u16 TimeCommunicatFlag;
extern u16 TempBaseFlag;
extern int8 BaseLineSnr;
extern u32 AdPowerTemp;
extern u8 RfSendFlags;
extern SNP_STATE_PACKET_t StatePacket;
extern u16 ConfigFlags;
extern u16 DebugFlag;
extern u8 MaxOffNum;
extern u8 OffTime;
extern u8 DetectValue;
u8 SysTimeSlot;
u8 TimeSlotMode;
u8 DownLineNum = 0;
EVENT_BUFF  EventBuff;

u32 AdPowerTemp;
u32 PowerAd;
u16 RefAd;
//u8  TestDemo = 0;

//u8 test[300];
//u8 *ptr;
void delay_1s(void)
{
  u8 i;
  for(i=0;i<5;i++)
  {
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
  }
}

void delay_8S(void)
{
   u8 i;
 for(i=0;i<14;i++)
  {
     LED1_ON();
     LED2_ON();
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     LED1_OFF();
     LED2_OFF();
      delay_ms(200);
     WDTCTL = WDT_ARST_1000 ;
  }
}

void main(void)
{  
  unsigned char *i=0;
  u16 temp;
  BoardInit();
  LED1_ON();
  LED2_ON();
  delay_8S();
 UartSendStrings("hello word");  
 UartSendStrings("\r\n");
  LED1_OFF();
  LED2_OFF();
  FlashParamterInit(); 
//  UartSendStrings("ID:");  
//  UartSendNumberH(RfParamt.SenID);   
//  UartSendStrings("TimeSlot:"); 
//  UartSendNumber(TimeSlot.SenTimeSlotNum);
//  UartSendStrings("PUMP:");
//  UartSendStrings("\r\n");  
//  UartSendNumberH(PumpHigh);   
//  UartSendNumberH(PumpLow);   
  TimerAStart(); 
   AVCC_POWER_ON();
   AD_ALL_OFF();
   delay_ms(2);
   SensorRest();
   AdIntrruptOn();
temp = RfParamt.SenID;
temp &= 0x0007;
temp <<= 3;
TimeSlot.ReportSecond = temp;
TimeCommunicatFlag |= STATE_SEND_ON;

ReportTime = REPORT_SEND_TIME_3;  
MaxOffNum = OffTime - 8;
DetectValue = 5;
#if !LED_TEST_ON 
   if( FlashParamt.SenID != 0xffff)
    { LPM3; }
#endif
   Brd_Nbiot_AT_Reset();
   Brd_Nbiot_Snd_AT();
   Brd_Nbiot_Get_Cgmr();
   Brd_Nbiot_Get_Cgsn();
   Brd_Nbiot_Get_Nconfig(0);
   Brd_Nbiot_Get_Nband(i);
   Brd_Nbiot_Get_Cfun();
   Brd_Nbiot_Get_Cimi();
   Brd_Nbiot_Get_Nccid();
   Nbiot_Api_Open_Network();
 while(1)
  {  
    /*  WDTCTL = WDT_ARST_1000 ;   //测试程序 每隔1秒发送一次ON/OFF事件
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     SaveEvent(ON);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     WDTCTL = WDT_ARST_1000 ; 
     delay_ms(200);
     SaveEvent(OFF);*/
  }
}

/*
UartSendStrings("BX:"); 
  UartSendNumber(AxisX1Pam.BaseLine);
   UartSendStrings("hello word");  
 UartSendStrings("\r\n");
memset(&AxisX1Pam,0,sizeof(AxisX1Pam));  SaveEventOff
delay_ms(200);
       WDTCTL = WDT_ARST_1000 ; 
BasAddNumZ = 0;
  BasAddNumX = 0;
  BasDecNumZ = 0;
  BasDecNumX = 0;
BasCountZ  DownLineConfig();
*/  

/***********ip地址120.26.200.64端口号6900********/