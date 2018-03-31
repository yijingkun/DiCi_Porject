#ifndef AD_H
#define AD_H

#include "snp.h"

#define M_SENX_ON()       (P4OUT &=~ BIT1)
#define M_SENX_OFF()       (P4OUT |= BIT1)
#define M_SENZ_ON()       (P4OUT &=~ BIT4)
#define M_SENZ_OFF()       (P4OUT |= BIT4)
#define M_SENY_ON()        (P4OUT &=~ BIT0)
#define M_SENY_OFF()       (P4OUT |= BIT0)
#define M_KEYX_OPEN()    st(P4OUT &= ~BIT2; P4OUT |= BIT3;)  //B A
#define M_KEYZ_OPEN()    st(P4OUT |= BIT2; P4OUT |= BIT3;)

#define AD_POWER_ON()     (P8OUT&=~ BIT4)
#define AD_POWER_OFF()    (P8OUT|= BIT4)
#define AVCC_POWER_ON()   (P8OUT&=~BIT1) 
#define AVCC_POWER_OFF()   (P8OUT|=BIT1) 
#define AD_POWER_GET_ON()   (P2OUT &= ~BIT0)
#define AD_POWER_GET_OFF()   (P2OUT |= BIT0)


//#define AD_INTERRUPT_ON()   (TA1CCTL1 |= CCIE)
//#define AD_INTERRUPT_OFF()   (TA1CCTL1 &= ~CCIE)

//#define TIME_INTERRUPT_ON()   (TACCTL2 |= CCIE)
//#define TIME_INTERRUPT_OFF()   (TACCTL2 &= ~CCIE)

#define ADC12CTL1_CSTARTADD_MASK  0xF000
#define BASELINE_SAVE_TIME   1800  //30∑÷÷”
#define WEAKUP_TIME     10

typedef struct _MAGNETIC_VALUE
{
  u16 AxisZ1;
  u16 AxisX1;
  //u16 OldZ1;
  //u16 OldX1;
} MAGNETIC_VALUE;

typedef struct _COMP_CNT
{
  u8 CntZ;
  u8 CntX;
}COMP_CNT;

typedef struct  _AD_TIME_CYCLE
{ 
  u16 BaseLineSaveSecond;
  u16 EventOnTime;
  u16 EventPrimaryTime;
 // u16 RestSecond;
  u16 BaseInitMinute;
 // u16 PowerSecond;
  u16 WeakUpSecond;
  u16 AdDelayTime;
  u8  uiRemainSlot;
  //u8  OverTheraCnt;
  u8  EventBaselineSecondZ;
  u8  EventBaselineSecondX;
  u8  ReadBaseLineTime;
  u8  BusOffSecond;
 // u8  SlotTime;
 // u8  SlotSecond;
//  u8  NearBaseTimeX;
  u8  CriticalOffSecond;
  u8  TempBaseSecondZ;
  u8  TempBaseSecondX;
  u8  BaseInitSecond;
  u8  EventDetectSecond;
  u8  OffBaseSecond;
}AD_TIME_CYCLE;

void AdInit(void);
void AdParamterInit(void);
void ADX1_OPEN(void);
void ADY1_OPEN(void);
void ADZ1_OPEN(void);
void AD_ALL_OFF(void);
u16 GetAdValue(void);
void TimerBStart(void);
void TimerBInit(void);
void TimerAStop(void);
void SendSenData(void);
void adSendData(void);
void M_ADZ_OPEN(void);
void P_ADZ_OPEN(void);
void M_ADX_OPEN(void);
void P_ADX_OPEN(void);
void adSaveData(u16 *mCurrentData, u16 *mOldData, u16 *pCurrentData, u16 *pOlddata, u16 TimeMs);
void adSendDataTest(void);
void SensorRest(void);
u16 GetPowerAD(void);
u16 GetRefAD(void);
void AdIntrruptInit(void);
void AdIntrruptOn(void);
void AdIntrruptOff(void);
void  OnBaseComparZ(u16 pBaseZ, u16 pBaseX, COMP_CNT *BaseCnt, u8 Update);
void  OnBaseComparX(u16 pBaseZ, u16 pBaseX, COMP_CNT *BaseCnt, u8 Update);
#endif