#include"types.h"
#include"ad.h"
#include "magentic.h"
#include "timeslot.h"
#include "rf_hal.h"
#include "snp.h"
#include "cfg.h"
#include "board.h"
#include "uart.h"
#include "flash.h"
#include "24l01.h"
#include <stdlib.h>
#include <string.h>

/**********************************************************
//AD数据采集程序，暂时不用更改
*************************************************************/
extern STABLE_BASELINE         HalfStableBaseLineX;
extern SENSOR_SAMPLE_PARAMTER     NearstBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER     NearstBaseLineX;
extern SENSOR_SAMPLE_PARAMTER AxisX1Pam;
extern SENSOR_SAMPLE_PARAMTER AxisZ1Pam;
extern SNP_SEN_MODE_PACKET_t EventPacket;
extern FLASH_PARAMTER_t  FlashParamt;
extern TIME_SLOT_PARMAT TimeSlot;
extern RF_PARAMTER RfParamt;
extern ON_NUM_BUFF OnNumBuff;
extern SNP_STATE_PACKET_t StatePacket;
extern LAST_EVENT OnEvent;
extern LAST_EVENT OffEvent;
extern SENSOR_TIME_PARAMTER  SenTime;
extern STABLE_BASELINE         StableBaseLineX;
extern STABLE_BASELINE         StableBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineZ;
extern SENSOR_SAMPLE_PARAMTER OnBaseLineX;
extern BASELINE_THREE_BUFF        NearstBaseBuffZ;
extern BASELINE_THREE_BUFF        NearstBaseBuffX;
extern SENSOR_SAMPLE_PARAMTER    OffTempBaseZ;
extern BASELINE_THREE_BUFF     OffTempBaseBuffZ;

extern SENSOR_SAMPLE_PARAMTER    OffTempBaseX;
extern BASELINE_THREE_BUFF     OffTempBaseBuffX;
extern u16 TimeCommunicatFlag;
extern u16 AdMagenticFlags;
extern u16 ConfigFlags;
extern u16 BaseLineFlag;
extern u16 HalfBaseLineFlag;
extern u16 MinBaseLineZ;
extern u16 MinBaseLineX;
extern u16 ExtraFlags;
extern u16 OldBaseZTemp;
extern u16 OldBaseXTemp;
extern u16 TempBaseFlag;
extern u16 SingleFlag;
extern u16 SetBaseLineZ;
extern u16 SetBaseLineX;
extern u16 OnBaseLineFlag;
extern u16 CompFlags;
extern u32 PowerAd;
extern u8  OffNumZ;
extern u8  OffNumX;
extern u8  TempBaseDayCnt;   
extern u16 RefAd;
extern u8 MaxOffNum;
extern u8  MinBaseLineNumZ;
extern u8  MinBaseLineNumX;
extern  u8 SystemState;
extern u8 RfSendFlags;
extern u8 TriggValue;
extern u8 DetectValue;
extern u8 ApTriggValue;
extern u8 ApDetectValue;
extern u8 DecThreshZ;
extern u8 SignalState;
extern u8 SingleValue;
extern u8 cnt;
extern u8 UnDetectValue;
extern u16 SetFlags;
extern u8 RestSecondAd;
extern u8 testget;
extern u8 NewLineOFF;
extern u16 OffMinute;
extern u16 OnMinute;
extern u16  BaseZUpdateTime;
extern u16  BaseXUpdateTime;
extern u16 OffBaseLineZ;
extern u16 OffBaseLineX;
extern u16 TempBaseZ;
extern u16 TempBaseX;
extern u8 OffBaseGetTime;
extern u8 OldBaseDayCnt;
extern u8 OnTime;
extern u8 testXZ;
extern u8 BaseBuffTime;
extern u8 OnSecond;
extern u16 NewBaseFlag;
extern u16 FlashBaseBuffZ[BASE_BUFF_NUM];
extern u16 FlashBaseBuffX[BASE_BUFF_NUM];
MAGNETIC_VALUE Magnetic;
AD_TIME_CYCLE AdTime;
COMP_CNT OffBaseCnt;
COMP_CNT OldBaseCnt;
COMP_CNT NewBaseCnt;
COMP_CNT BaseBuffCnt[BASE_BUFF_NUM];

u32 SumAdValue;
u16 LastAdAverage;
u16 AdAverage;
u16 AdCount;

u32 SumAdValueX;
u16 LastAdAverageX;
u16 AdAverageX;

u16 LastBaseLineZ;
u16 LastBaseLineX;
u8 WeakUpSecond;
u8 OffTempBaseSecond;
u8 BaseBuffZPtr;
u8 BaseBuffXPtr;
extern u8 AdRestSecond;
extern u8 DectZ;
extern u8 DectX;
extern u8 TrigZ;
extern u8 TrigX;
extern u8 Tap;
//u8 time=0;
void AdInit(void)
{
  P8DIR |= BIT1;  //AD_AVCC
  P8DIR |= BIT4; //AD_POWER
  P2DIR |= BIT0; //POWER_GET
   
   P8DIR|=BIT2;   //reset
   P8DIR|=BIT3;  //set

  
  P4DIR |= BIT1; //GNDX
  P4DIR |= BIT4;   //GNDZ
  P4DIR |= BIT0;   //GNDY
  P4DIR |= BIT3+BIT2;   //ADDA,ADDB
  P6SEL |= BIT0 + BIT5 + BIT6;//OPEN AD0,AD1,AD2
  
  P8OUT|= BIT1;   // AVCC OFF
  P8OUT|= BIT4;  //AD POWER OFF
  P4OUT &=~ BIT1; //M_GNDX
  P4OUT &=~ BIT4; //M_GNDZ
  P4OUT &=~ BIT0; //M_GNDY
  
  AD_POWER_GET_OFF();
  AdParamterInit();
  ADC12CTL0 &= ~(ADC12ENC); 
  ADC12CTL0 = ADC12ON + ADC12SHT0_0; // 开ADC12模块+采集定时器分频系数n=1
  ADC12CTL1 = ADC12SHP + ADC12SSEL_3 + ADC12DIV_7 + ADC12CSTARTADD_0;//+ CONSEQ_3; // 使用采样定时器输出作采集/转换信号SAMPCON, 转换时钟 SMCLK-ADC12SSEL_3   8分频=1M
  ADC12MCTL0 = ADC12SREF_2 + ADC12INCH_0; //Vr+=VeREF
  ADC12MCTL5 = ADC12SREF_0 + ADC12INCH_5;// + EOS; 
  ADC12MCTL6 = ADC12SREF_0 + ADC12INCH_6; 
}

void AdParamterInit(void)
{ 
  memset(&Magnetic,0,sizeof(Magnetic));
  memset(&AdTime,0,sizeof(AdTime));
  //memset(&OffBaseCnt,0,sizeof(OffBaseCnt));
 // memset(&OldBaseCnt,0,sizeof(OldBaseCnt));
  //memset(&NewBaseCnt,0,sizeof(NewBaseCnt));
}
void M_ADX_OPEN(void)
{
  AD_POWER_ON();
  M_SENX_ON(); 
  M_SENZ_OFF();
  M_SENY_OFF(); 
  M_KEYX_OPEN();
  delay_us(50);
}

void M_ADZ_OPEN(void)
{
  AD_POWER_ON();  
  M_SENX_OFF();
  M_SENZ_ON();  
  M_SENY_OFF();
  M_KEYZ_OPEN();
  delay_us(50);
}

void SensorRest(void)
{
  M_SENZ_ON();  
  M_SENX_ON();
  M_SENY_ON();
  MSenRst();
  MSenSet();
  M_SENZ_OFF();  
  M_SENX_OFF(); 
  M_SENY_OFF();
  
}

void AD_ALL_OFF(void)
{
  P4OUT |= 0x13;  // GNDX ,GNDY, GNDZ 拉高
  P4OUT &= ~BIT2;
  P4OUT &= ~BIT3;  
  AD_POWER_OFF();
  //P8OUT|=BIT3;
 // P8OUT|=BIT2;
}

u16 GetAdValue(void)
{
  u16 Value;
  ADC12CTL0 |= ADC12ENC;
  ADC12CTL0 |= ADC12SC; // 开始转换
  while ((ADC12IFG & BIT0)==0); //等待转换结束
  ADC12CTL0 &= ~ADC12ENC;
  Value=ADC12MEM0>>2;   //精度为10位AD
  return Value;
}

u16 GetPowerAD(void)
{
  u16 Value;
  ADC12CTL1 &= ~ADC12CTL1_CSTARTADD_MASK;
  ADC12CTL1 |= ADC12CSTARTADD_5;
  ADC12CTL0 |= ADC12ENC;
  ADC12CTL0 |= ADC12SC; // 开始转换
  while ((ADC12IFG & BIT5)==0); //等待转换结束
  ADC12CTL0 &= ~ADC12ENC;
  Value=ADC12MEM5>>2;   //精度为10位AD
  ADC12CTL1 &= ~ADC12CTL1_CSTARTADD_MASK;
  ADC12CTL1 |= ADC12CSTARTADD_0;
  return Value;
}

u16 GetRefAD(void)
{
  u16 Value;
  ADC12CTL1 &= ~ADC12CTL1_CSTARTADD_MASK;
  ADC12CTL1 |= ADC12CSTARTADD_6;
  ADC12CTL0 |= ADC12ENC;
  ADC12CTL0 |= ADC12SC; // 开始转换
  while ((ADC12IFG & BIT6)==0); //等待转换结束
  ADC12CTL0 &= ~ADC12ENC;
  Value=ADC12MEM6>>2;   //精度为10位AD
  ADC12CTL1 &= ~ADC12CTL1_CSTARTADD_MASK;
  ADC12CTL1 |= ADC12CSTARTADD_0;
  return Value; 
}

void AdIntrruptInit(void)
{
  TB0CTL  = TBSSEL_1 + TBCLR; //ACLK,，
  TB0CCR0 =  0x400;;  
}

void AdIntrruptOn(void)
{
   TB0CCTL0 |= CCIE;
   TB0CTL &= ~0x30;  
   TB0CTL |= MC1;
}

void AdIntrruptOff(void)
{
   TB0CCTL0 &= ~CCIE;
   TB0CTL &= ~(MC1 + MC0);
}

//u8 time = 0;


//u8 testZ;
//u8 testX;
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B0(void)
{
   u16 AdTemp1;
   u16 AdTemp2;
   u8 i;
   WDTCTL = WDT_ARST_1000; 
   _EINT();
       TB0CCR0+= 0x1000; 
     if( (TempBaseFlag & EVENT_GET_ON) || (SetFlags & TEST_DEMO_ON) )
     {  
       if( !(ConfigFlags & DATE_SEND) )
            {              
               M_ADZ_OPEN();
               AdTemp1=GetAdValue();
               AdTemp1&=0x03ff;    //10位AD精度   
               Magnetic.AxisZ1 = AdTemp1;
               M_ADX_OPEN();                 
               AdTemp2=GetAdValue();
               AdTemp2&=0x03ff;
               Magnetic.AxisX1 = AdTemp2;
               AD_ALL_OFF(); 
            }
     //  u32 SumAdValueX;
//u16 LastAdAverageX;
//u16 AdAverageX;
        if( SetFlags & AD_GET_ON)
        {
           SumAdValue += Magnetic.AxisZ1;
          // SumAdValueX += Magnetic.AxisX1;
           AdCount++;
           if( AdCount >= 16 )
           {
              SetFlags &= ~AD_GET_ON;
             AdCount = 0;
             AdTime.AdDelayTime = 0;
             
             AdAverage = SumAdValue>>4;       
             SumAdValue = 0;
             if( AdAverage > LastAdAverage)
                { AdTemp1 = AdAverage - LastAdAverage; }
             else
                { AdTemp1 = LastAdAverage - AdAverage; }
             LastAdAverage = AdAverage;
             
          /*   AdAverageX = SumAdValueX>>4;
             SumAdValueX = 0;
             if( AdAverageX > LastAdAverageX )
               { AdTemp2 = AdAverageX - LastAdAverageX; }
             else
               { AdTemp2 = LastAdAverageX - AdAverageX; }
             LastAdAverageX = AdAverageX; */
             
             if( AdTemp1 >= 50 )
             {
                SensorRest();
                SetFlags |= AD_WEAKUP; 
               // CompFlags &= ~AD_WEAKUP_X;
                WeakUpSecond = 0;
 #if STRING_ON                
  UartSendStrings("Ad weak up!!!!!!!!"); 
 UartSendStrings("\r\n");  
#endif
             }
            /* else if( (AdTemp2 >= 50) && (!(RfSendFlags & CONNECTED_AP)) )
             {
                SensorRest();
                SetFlags |= AD_WEAKUP; 
                CompFlags |= AD_WEAKUP_X;
                WeakUpSecond = 0;
             }*/
           }           
        }
        else
        {
          AdTime.AdDelayTime++;
          if( AdTime.AdDelayTime >= 16 )
            { 
              SetFlags |= AD_GET_ON;
              AdTime.AdDelayTime = 0;
              SumAdValue = 0;
              SumAdValueX = 0;
              AdCount = 0;
    //  UartSendStrings("Ad get on"); 
 // UartSendStrings("\r\n");                  
            }
        }
     }
            AdTime.uiRemainSlot++;
            if( (BaseLineFlag & READ_BASELINE) && ((AdRestSecond>= REST_AD_DELAY)) )
              { 
                AdTime.ReadBaseLineTime++; 
                if( AdTime.ReadBaseLineTime >= 80 )
                  { 
                    AdTime.ReadBaseLineTime = 0;
                    BaseLineFlag &= ~READ_BASELINE;
                  }
              }
            if( AdMagenticFlags & AD_EVENT_ON_PRIMARY )
              {  AdTime.EventPrimaryTime++;  }
            if(AdTime.uiRemainSlot >= 8)
              { 
             /* time++;
                if( time >= 3)
                {
                  //cnt = 0;
                  time = 0;
                  UartSendStrings("Z:"); 
                  UartSendNumber(Magnetic.AxisZ1);
                  UartSendStrings("X:"); 
                  UartSendNumber(Magnetic.AxisX1);
                   UartSendStrings("BZ:"); 
                  UartSendNumber(AxisZ1Pam.BaseLine ); 
                  UartSendStrings("BX:"); 
                  UartSendNumber(AxisX1Pam.BaseLine ); 
   if( SystemState == EVENT_DETECT)
    {
       UartSendStrings("IN ON"); 
  UartSendStrings("\r\n");  
    }
   else
    {
       UartSendStrings("IN OFF"); 
  UartSendStrings("\r\n");  
    }
     UartSendStrings("\r\n");        
                }*/
                
                AdTime.uiRemainSlot =0;  
                AdTime.BaseLineSaveSecond++;  
                if(SystemState == ON_BASE_LINE)
                {
                   OffTempBaseSecond++;
                   if(OffTempBaseSecond >= OffBaseGetTime )
                   {
                     OffTempBaseSecond = 0;
                     CompFlags |= OFF_BASELINE_GET_Z;
                     CompFlags |= OFF_BASELINE_GET_X;
                     OffTempBaseZ.pBaseLine = (float)AxisZ1Pam.BaseLine;
                     OffTempBaseX.pBaseLine = (float)AxisX1Pam.BaseLine;
                     OffTempBaseBuffZ.Count = 0;
                     OffTempBaseBuffX.Count = 0;              
                   }
                }
               /* if( (AdMagenticFlags & EVENT_ON_SAVED) && (NewBaseFlag & ON_TIME_START) )
                {
                  OnSecond++;
                  if( OnSecond >= 60 )
                    {
                      OnSecond = 0;
                      NewBaseFlag &= ~ON_TIME_START;
                      NewBaseFlag |= ON_EVENT_REIGHT;           
                    }
                }*/
                /*if( (OnBaseLineFlag & BASEZ_TIME_START) && (BaseZUpdateTime < 1800))//1800
                {
                    BaseZUpdateTime++;
                    if( BaseZUpdateTime >= 1800 )
                    {
                      OnBaseLineFlag &= ~BASEZ_TIME_START;
                      if(AxisZ1Pam.BaseLine > OldBaseZTemp)
                        { AdTemp2 = AxisZ1Pam.BaseLine - OldBaseZTemp; }
                      else
                        { AdTemp2 = OldBaseZTemp - AxisZ1Pam.BaseLine; }
                      if( AdTemp2 >= 3)
                        {  AxisZ1Pam.BaseLine = OldBaseZTemp;  }
                    }                
                }*/
                if( (OnBaseLineFlag & BASEX_TIME_START) && (BaseXUpdateTime < 1800))
                {
                  BaseXUpdateTime++;
                  if( BaseXUpdateTime >= 1800)
                  {
                    OnBaseLineFlag &= ~BASEX_TIME_START;
                    if(AxisX1Pam.BaseLine > OldBaseXTemp)
                        { AdTemp2 = AxisX1Pam.BaseLine - OldBaseXTemp; }
                    else
                        { AdTemp2 = OldBaseXTemp - AxisX1Pam.BaseLine; }
                    if( AdTemp2 >= 3)
                        {   AxisX1Pam.BaseLine = OldBaseXTemp;   }
                  }
                }
                if( WeakUpSecond <= WEAKUP_TIME )
                   { WeakUpSecond++; }
                if( (AdMagenticFlags & EVENT_ON_SAVED) && (!(OnBaseLineFlag & DEC_VALUE_GENERATE_Z)) )
                   { AdTime.TempBaseSecondZ++; }
                if( (AdMagenticFlags & EVENT_ON_SAVED) && (!(OnBaseLineFlag & DEC_VALUE_GENERATE_X)) )
                   { AdTime.TempBaseSecondX++; }              
                if( (AdMagenticFlags & EVENT_ON_SAVED) && (AdTime.EventOnTime < ON_START_GEY_BASELINE_TIME) )
                   {  AdTime.EventOnTime++;  }
                if( (!(HalfBaseLineFlag & ON_EVENT_BASELINE_GET_Z))     && 
                     (AdTime.EventOnTime >= ON_START_GEY_BASELINE_TIME) &&
                     (AdMagenticFlags & EVENT_ON_SAVED) )
                 { AdTime.EventBaselineSecondZ++; } 
                if( (!(HalfBaseLineFlag & ON_EVENT_BASELINE_GET_X))  &&
                    (AdTime.EventOnTime >= ON_START_GEY_BASELINE_TIME) &&
                    (AdMagenticFlags & EVENT_ON_SAVED) )
                  { AdTime.EventBaselineSecondX++; }
                if( (SystemState == EVENT_DETECT) && (!(AdMagenticFlags & EVENT_ON_SAVED)) )
                {
                  AdTime.EventDetectSecond++;
                  if( AdTime.EventDetectSecond > 80 )
                  {
                    AdTime.EventOnTime = 0;
                    BaseLineFlag &= ~READ_BASELINE_ON;
                    BaseLineFlag &= ~READ_BASELINE;
                    SenTime.BaseLineTime = 0;  
                    memset(&StableBaseLineZ,0,sizeof(StableBaseLineZ)); 
                    memset(&StableBaseLineX,0,sizeof(StableBaseLineX)); ;          
                    memset(&OnBaseLineZ,0,sizeof(OnBaseLineZ));
                    memset(&OnBaseLineX,0,sizeof(OnBaseLineX));  
                    AxisZ1Pam.pBaseLine = (float)AxisZ1Pam.BaseLine;
                    AxisX1Pam.pBaseLine = (float)AxisX1Pam.BaseLine;             
                    AxisZ1Pam.OverThresCnt = 0;
                    AxisX1Pam.OverThresCnt = 0;
                    AdTime.EventDetectSecond = 0;
                    AdMagenticFlags &= ~EVENT_ON_SAVED;
                    SystemState = ON_BASE_LINE;                     
                  }
                }
                if( AdMagenticFlags & BUS_OFF_GENERT )
                    { 
                      AdTime.BusOffSecond++;
                      if( AdTime.BusOffSecond >= 8 )
                       {    
                         AdTime.BusOffSecond = 0;
                         AdTime.OffBaseSecond = 0;
                         AdMagenticFlags &= ~BUS_OFF_GENERT;
                         HalfBaseLineFlag |= OFF_BASE_CNT_ON;
                         HalfBaseLineFlag |= GET_NEREST_BASELINE_Z;
                         HalfBaseLineFlag |= GET_NEREST_BASELINE_X;                                                                                 
                         NearstBaseLineZ.pBaseLine = Magnetic.AxisZ1;
                         NearstBaseLineX.pBaseLine = Magnetic.AxisX1;                        
                       }
                    }
                if(HalfBaseLineFlag & OFF_BASE_CNT_ON)
                    {
                      if( AdTime.OffBaseSecond < 30 )
                         { AdTime.OffBaseSecond++; }
                      if( AdTime.OffBaseSecond >= 30 )
                      {
                        ExtraFlags &= ~BASELINE_CALIBRAT_Z;
                        ExtraFlags &= ~BASELINE_CALIBRAT_X; 
                      }
                    }
               /* if( ExtraFlags & CRITICAL_OFF )
                {
                  AdTime.CriticalOffSecond++;
                  if( AdTime.CriticalOffSecond >= 120 )
                  {
                    AdTime.CriticalOffSecond = 0;
                    ExtraFlags &= ~CRITICAL_OFF;
                  }      
                }*/
                if( AdTime.BaseLineSaveSecond >= BASELINE_SAVE_TIME )
                  {
                    AdTime.BaseLineSaveSecond = 0;                    
                    if( LastBaseLineZ > AxisZ1Pam.BaseLine )
                      { AdTemp1 = LastBaseLineZ - AxisZ1Pam.BaseLine; }
                    else 
                      { AdTemp1 = AxisZ1Pam.BaseLine - LastBaseLineZ; }
                    if( LastBaseLineX > AxisX1Pam.BaseLine )
                      { AdTemp2 = LastBaseLineX - AxisX1Pam.BaseLine; }
                    else
                      { AdTemp2 = AxisX1Pam.BaseLine - LastBaseLineX; }
                    if( (AdTemp1 >= 2) || (AdTemp2 >= 2) )
                     {
                       LastBaseLineZ = AxisZ1Pam.BaseLine;
                       LastBaseLineX = AxisX1Pam.BaseLine;
                       BaseLineFlag |= BASELINE_UPDATA;                      
                       //BaseLineSaveNum++;
                     }
                  }                            
              }
           // AdTime.PowerSecond =10;
            if( (!(ConfigFlags & DATE_SEND)) && (AdRestSecond>= REST_AD_DELAY) && (TempBaseFlag & EVENT_GET_ON) )
            {              
               if( ApDetectValue < DETECT_VALUE_0 )
                  { ApDetectValue = DETECT_VALUE_0; } 
               if(UnDetectValue < DETECT_VALUE_0)
                 { UnDetectValue = DETECT_VALUE_0; }
               if(OnTime < 40)
                  { OnTime = 40; }
               if( MaxOffNum < 20)
                 { MaxOffNum = 40; }    
               if(  (SystemState == EVENT_DETECT) && (AdMagenticFlags & EVENT_ON_SAVED) )
                  {  
                    OnBaseComparZ(OffTempBaseZ.BaseLine, OffTempBaseX.BaseLine, &OffBaseCnt, 0);
                    OnBaseComparX(OffTempBaseZ.BaseLine, OffTempBaseX.BaseLine, &OffBaseCnt, 0);
                    OnBaseComparZ(SetBaseLineZ, SetBaseLineX, &OldBaseCnt, 1);
                    OnBaseComparX(SetBaseLineZ, SetBaseLineX, &OldBaseCnt, 1);
                    OnBaseComparZ(TempBaseZ, TempBaseX, &NewBaseCnt, 1);
                    OnBaseComparX(TempBaseZ, TempBaseX, &NewBaseCnt, 1);
                    for(i=0;i<BASE_BUFF_NUM;i++)
                    {
                      OnBaseComparZ(FlashBaseBuffZ[i], FlashBaseBuffX[i], &BaseBuffCnt[i], 1);
                      OnBaseComparX(FlashBaseBuffZ[i], FlashBaseBuffX[i], &BaseBuffCnt[i], 1);
                    }
                  }
               SystemScan(); 
            } 
}

void  OnBaseComparZ(u16 pBaseZ, u16 pBaseX, COMP_CNT *BaseCnt, u8 Update)
{
  u8 temp;
    temp = DecBaseEvent(pBaseZ ,Magnetic.AxisZ1 );
    if( temp == 1 )
      {                      
         BaseCnt->CntZ++;
         if( (BaseCnt->CntZ >= BaseBuffTime) && (BaseCnt->CntX >= BaseBuffTime) )
           {
              if( Update == 1 )
                {   
                    AxisZ1Pam.BaseLine = pBaseZ;
                    AxisX1Pam.BaseLine = pBaseX;   
                }
              else
                { CompFlags |= OFF_BASE_EFFECT_Z;}
              BaseCnt->CntZ = 0;
              //OffNumZ = 0;
             // OffNumX = 0;
              //TempBaseDayCnt = 0;  
             // OldBaseDayCnt = 0;
              if( !(ExtraFlags & OFFBASE_SAVED_Z) )
                 {
                    ExtraFlags |= OFFBASE_SAVED_Z;
                    BaseLineFlag |= BASELINE_UPDATA;
                 }              
          }          
      }
     else
     { 
       BaseCnt->CntZ = 0;        
     } 
}

void  OnBaseComparX(u16 pBaseZ, u16 pBaseX, COMP_CNT *BaseCnt, u8 Update)
{
  u8 temp;
    temp = DecBaseEvent(pBaseX ,Magnetic.AxisX1 );
    if( temp == 1 )
      {                      
         BaseCnt->CntX++;
         if( (BaseCnt->CntX >= BaseBuffTime) && (BaseCnt->CntZ >= BaseBuffTime) )
           {
              if( Update == 1)
                 { 
                   AxisZ1Pam.BaseLine = pBaseZ;
                   AxisX1Pam.BaseLine = pBaseX;
                 }
              else
                 { CompFlags |= OFF_BASE_EFFECT_X; }
              BaseCnt->CntX = 0;
              //OffNumZ = 0;
              //OffNumX = 0;
              //TempBaseDayCnt = 0;   
             // OldBaseDayCnt = 0;
              if( !(ExtraFlags & OFFBASE_SAVED_X) )
                 {
                    ExtraFlags |= OFFBASE_SAVED_X;
                    BaseLineFlag |= BASELINE_UPDATA;
                 } 
          }
      }
     else
     { 
       BaseCnt->CntX = 0; 
     } 
}
