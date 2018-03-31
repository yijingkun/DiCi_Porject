#ifndef BOARD_H
#define BOARD_H


#define LED1_ON()         (P1OUT &= ~BIT5)   
#define LED1_OFF()         (P1OUT |= BIT5) 
#define LED2_ON()         (P1OUT &= ~BIT4) 
#define LED2_OFF()         (P1OUT |= BIT4) 


void LedInit(void);
void OscInit(void);
void BoardInit(void);
void SystemParamterInit(void);
void Delay5S(void);
void IoInit(void);
void IoUp(void);
void IoDown(void);
void IoInitIn(void);
#endif