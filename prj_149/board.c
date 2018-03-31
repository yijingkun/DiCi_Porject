#include "types.h"
#include "board.h"
#include "ad.h"
#include "uart.h"
#include "timeslot.h"
#include "magentic.h"
//#include "cc2420_rf.h"
#include "rf_hal.h"
#include "cfg.h"
#include "24l01.h"

/*******************************************************************
//初始化程序，可以更改
*****************************************************************/
//u8 StartMode;
//u8 RfTestMode;
void OscInit(void)
{
  P7SEL |= BIT0 + BIT1;
  P5SEL |= BIT2 + BIT3;   
 // UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
  UCSCTL4 &= ~0x0700;                        // Set ACLK = XT1CLK
  UCSCTL6 &= ~XT1OFF; 
  UCSCTL6 &= ~0x000c;
  do
  {
    UCSCTL7 &= ~XT1LFOFFG;                  // Clear XT1 fault flags
  }while (UCSCTL7&XT1LFOFFG);   
  
 __bis_SR_register(SCG0);                  // Disable the FLL control loop
  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
  UCSCTL2 = FLLD_1 + 244;                 
  __bic_SR_register(SCG0);                  // Enable the FLL control loop
  
  __delay_cycles(250000);
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG );//XT1HFOFFG  DCOFFG
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);    
}


void BoardInit(void)
{
#if LED_TEST_ON 
   WDTCTL = WDTPW + WDTHOLD;
   OscInit();  
#endif
   WDTCTL=  WDT_ARST_1000 ; 
   delay_ms(200);
   WDTCTL = WDT_ARST_1000 ; 
   LedInit();
   UartInit();   
   RFM98_SPI_Init();
   RFM98_REST_DOWN();
   delay_us(200);
   RFM98_REST_UP();
   delay_ms(6);      
   _EINT();
/***********由yjk注释掉 2018.03.26
   TimerAInit();  //时间槽定时器
   TimeParamterInit();
*/   
   AdParamterInit();
   InitMagenticParamter();
   SystemParamterInit();
   AdInit();  
   AdIntrruptInit();
   IoInit();
   //IoInitIn();
   //IoDown();
  // IoUp();
}
void LedInit(void)
{
  P1DIR |= BIT5; 
  P1DIR |= BIT4;
  LED1_OFF();
  LED2_OFF();
}

void IoInit(void)
{
  P1DIR |= BIT0 + BIT1 + BIT2 + BIT3 + BIT6 + BIT7;
  //P1DIR |= BIT1;
  //P1DIR |= BIT2;
  //P1DIR |= BIT3;
  //P1DIR |= BIT6;
 // P1DIR |= BIT7;
  
  P2DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT7;
 // P2DIR |= BIT2;
 // P2DIR |= BIT3;
  //P2DIR |= BIT4;
 // P2DIR |= BIT7;
  
  P3DIR |= BIT4 + BIT5 + BIT6 + BIT7;
 // P3DIR |= BIT5;
 // P3DIR |= BIT6;
  //P3DIR |= BIT7;
  
  P4DIR |= BIT5 + BIT6 + BIT7;
  //P4DIR |= BIT6;
 // P4DIR |= BIT7;
  
  P5DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
 // P5DIR |= BIT2;
  //P5DIR |= BIT3;
 // P5DIR |= BIT4;
  //P5DIR |= BIT5;
  
  P6DIR |= BIT1 + BIT2 + BIT3 + BIT4 + BIT7;
  //P6DIR |= BIT2;
  //P6DIR |= BIT3;
  //P6DIR |= BIT4;
 // P6DIR |= BIT7;
  
  P7DIR |= BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7;
 // P7DIR |= BIT3;
 // P7DIR |= BIT4;
 // P7DIR |= BIT5;
 // P7DIR |= BIT6;
 // P7DIR |= BIT7;
  
  P8DIR |= BIT0 + BIT5 + BIT6;
//  P8DIR |= BIT5;
  //P8DIR |= BIT6;
}

/*
void IoUp(void)
{
  P1OUT |= BIT0;
  P1OUT |= BIT1;
  P1OUT |= BIT2;
  P1OUT |= BIT3;
  P1OUT |= BIT6;
  P1OUT |= BIT7;
  
  P2OUT |= BIT1;
  P2OUT |= BIT2;
  P2OUT |= BIT3;
  P2OUT |= BIT4;
  P2OUT |= BIT7;
  
  P3OUT |= BIT4;
  P3OUT |= BIT5;
  P3OUT |= BIT6;
  P3OUT |= BIT7;
  
  P4OUT |= BIT5;
  P4OUT |= BIT6;
  P4OUT |= BIT7;
  
  P5OUT |= BIT1;
  P5OUT |= BIT2;
  P5OUT |= BIT3;
  P5OUT |= BIT4;
  P5OUT |= BIT5;
  
  P6OUT |= BIT1;
  P6OUT |= BIT2;
  P6OUT |= BIT3;
  P6OUT |= BIT4;
  P6OUT |= BIT7;
  
  P7OUT |= BIT2;
  P7OUT |= BIT3;
  P7OUT |= BIT4;
  P7OUT |= BIT5;
  P7OUT |= BIT6;
  P7OUT |= BIT7;
  
  P8OUT |= BIT0;
  P8OUT |= BIT5;
  P8OUT |= BIT6;
}
*/
/*
void IoDown(void)
{
  P1OUT &= ~BIT0;
  P1OUT &= ~BIT1;
  P1OUT &= ~BIT2;
  P1OUT &= ~BIT3;
  P1OUT &= ~BIT6;
  P1OUT &= ~BIT7;
  
  P2OUT &= ~BIT1;
  P2OUT &= ~BIT2;
  P2OUT &= ~BIT3;
  P2OUT &= ~BIT4;
  P2OUT &= ~BIT7;
  
  P3OUT &= ~BIT4;
  P3OUT &= ~BIT5;
  P3OUT &= ~BIT6;
  P3OUT &= ~BIT7;
  
  P4OUT &= ~BIT5;
  P4OUT &= ~BIT6;
  P4OUT &= ~BIT7;
  
  P5OUT &= ~BIT1;
  P5OUT &= ~BIT2;
  P5OUT &= ~BIT3;
  P5OUT &= ~BIT4;
  P5OUT &= ~BIT5;
  
  P6OUT &= ~BIT1;
  P6OUT &= ~BIT2;
  P6OUT &= ~BIT3;
  P6OUT &= ~BIT4;
  P6OUT &= ~BIT7;
  
  P7OUT &= ~BIT2;
  P7OUT &= ~BIT3;
  P7OUT &= ~BIT4;
  P7OUT &= ~BIT5;
  P7OUT &= ~BIT6;
  P7OUT &= ~BIT7;
  
  P8OUT &= ~BIT0;
  P8OUT &= ~BIT5;
  P8OUT &= ~BIT6;
}
*/
/*
void IoInitIn(void)
{
  P1DIR &= ~BIT0;
  P1DIR &= ~BIT1;
  P1DIR &= ~BIT2;
  P1DIR &= ~BIT3;
  P1DIR &= ~BIT6;
  P1DIR &= ~BIT7;
  
  P2DIR &= ~BIT1;
  P2DIR &= ~BIT2;
  P2DIR &= ~BIT3;
  P2DIR &= ~BIT4;
  P2DIR &= ~BIT7;
  
  P3DIR &= ~BIT4;
  P3DIR &= ~BIT5;
  P3DIR &= ~BIT6;
  P3DIR &= ~BIT7;
  
  P4DIR &= ~BIT5;
  P4DIR &= ~BIT6;
  P4DIR &= ~BIT7;
  
  P5DIR &= ~BIT1;
  P5DIR &= ~BIT2;
  P5DIR &= ~BIT3;
  P5DIR &= ~BIT4;
  P5DIR &= ~BIT5;
  
  P6DIR &= ~BIT1;
  P6DIR &= ~BIT2;
  P6DIR &= ~BIT3;
  P6DIR &= ~BIT4;
  P6DIR &= ~BIT7;
  
  P7DIR &= ~BIT2;
  P7DIR &= ~BIT3;
  P7DIR &= ~BIT4;
  P7DIR &= ~BIT5;
  P7DIR &= ~BIT6;
  P7DIR &= ~BIT7;
  
  P8DIR &= ~BIT0;
  P8DIR &= ~BIT5;
  P8DIR &= ~BIT6;
}*/