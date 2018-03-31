#include "types.h"
#include "24l01.h"
#include "rf_hal.h"
#include "board.h"
#include "snp.h"
#include "timeslot.h"
#include "uart.h"
#include "cfg.h"
#include "ad.h"

/**********************************************************
//数据收发模块配置程序，需用NB-LOT模块程序替代
*************************************************************/
 	

extern u8  TimeSlotMode;
extern u8 SysTimeSlot;
extern u16 TimeCommunicatFlag;
extern u16 ConfigFlags;
extern u8  RfSendFlags;

const u16 PumpTb1[10] = 
{
  0x6be0,//0
  0x6c00,//1
  0x6c20,//2
  0x6c40,//3
  0x6c60,//4
  0x6c80,//5
  0x6ca0,//6
  0x6cc0,//7
  0x6ce0,//8
  0x6d00,//9
};
const u16 RFM98PowerTbl[4] =
{ 
  0x09FF,                   //20dbm  
  0x09FC,                   //17dbm
  0x09F9,                   //14dbm
  0x09F6,                   //11dbm 
};
/*
const u8 RFM98SpreadFactorTbl[7] =
{
  6,7,8,9,10,11,12
};
*/
/*
const u8 RFM98LoRaBwTbl[10] =
{
//7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
  0,1,2,3,4,5,6,7,8,9
};*/

///////////////////////////////////////////////// LoRa mode //////////////////////////////////////////////////
//Error Coding rate (CR)setting 
#define CR_4_5    
//#define CR_4_6    0
//#define CR_4_7    0
//#define CR_4_8    0 

#ifdef   CR_4_5
  #define CR    0x01                                       // 4/5
#else
  #ifdef   CR_4_6
    #define CR    0x02                                     // 4/6
  #else 
    #ifdef   CR_4_7 
      #define CR    0x03                                   // 4/7
    #else 
      #ifdef   CR_4_8
        #define CR    0x04                                 // 4/8
      #endif
    #endif
  #endif
#endif 

//CRC Enable
#define CRC_EN    

#ifdef  CRC_EN
  #define CRC   0x01                                       //CRC Enable
#else
  #define CRC   0x00
#endif

const u16 PumpBit = 0x8000;
u8  gb_FreqBuf_Addr=0;                                     //RF center frequency cache address
u8  gb_RateBuf_Addr=10; // 6,7,8,9,10,11,12////////////////////////
u8  gb_PowerBuf_Addr = POWER_RF;//2;//功率
u8  gb_FdevBuf_Addr=0;
u8  gb_BandBuf_Addr=7;// 0,1,2,3,4,5,6,7,8,9///////////////////////
u8  gb_Modem_Addr=0;
u8  gb_Modem_Addr_Backup=0;
u8  LeadCode = 12;
u8  RFM_flag = 0; 
u16 PumpHigh;
u16 PumpLow;
 ///360ms
extern u16 SetFlags;
extern u8 NewPumpH;
extern u8 NewPumpL;
void RFM98_SPI_Init(void)
{
  P3DIR |=BIT0;// CSN	
  P3SEL |= BIT1 + BIT2 + BIT3;//P3用于SPI模式
  UCB0CTL1 |= UCSWRST;
  UCB0CTL0 |= (UCMST + UCSYNC + UCCKPH + UCMSB + UCMODE_0);//8位SPI，主模式
  UCB0CTL0 &= ~UC7BIT;
  UCB0CTL1 |= UCSSEL_2;
  
  //ME1 |= USPIE0;//模块使能
  UCB0BR0=0x02;//0x02;
  UCB0BR1=0x00;
  //UCB0MCTL=0x00;
  UCB0IE &= ~UCTXIE;//禁止接受中断
  UCB0IE &= ~UCRXIE;//禁止发送中断
  UCB0CTL1 &= ~UCSWRST;//使能SPI
  
  P2DIR &=~BIT5;  //FIFOP 中断
  P2DIR |= BIT6;
  FIFOP_IE_ON();
  FIFOP_PulseSet();  
}

u8 SPI1_ReadWriteByte(u8 data)
{
  u8 rx;
  u8 SpiCount;
  WDTCTL = WDT_ARST_1000 ; 
  UCB0IFG &= ~UCRXIFG;
  SpiCount = 0;
  while( !(UCB0IFG & UCTXIFG))
  { 
    SpiCount++;
    if( SpiCount > 200 )
    {
      ConfigFlags |= SPI_ERROR;
    //  UartSendStrings("Spi err"); 
 // UartSendStrings("\r\n");  
      break; 
    }
  }
  UCB0TXBUF=data;
  SpiCount = 0;
  while(!(UCB0IFG & UCRXIFG))
  {  
    SpiCount++; 
    if( SpiCount > 200 )
    { 
      ConfigFlags |= SPI_ERROR;
    //  UartSendStrings("Spi err"); 
 // UartSendStrings("\r\n");  
      break; 
    }
  }
  rx = UCB0RXBUF;
  return rx;
}

//SPI写寄存器
//reg:指定寄存器地址+value:写入的值
u8 RFM98_Write_Reg(u16 TxData)
{
  u8 status;	
  TxData|=0x8000;
  RFM98_SPI_BEGIN();              //使能SPI传输
  status =SPI1_ReadWriteByte((TxData>>8));//发送寄存器号 
  SPI1_ReadWriteByte(TxData);      //写入寄存器的值
  RFM98_SPI_END();             //禁止SPI传输	   
  return(status);       			//返回状态值
}
//读取SPI寄存器值
//reg:要读的寄存器
u8 RFM98_Read_Reg(u16 addr)
{
  u8 reg_val;	    
  RFM98_SPI_BEGIN();           //使能SPI传输		
  SPI1_ReadWriteByte((addr>>8));   //发送寄存器号
  reg_val=SPI1_ReadWriteByte(0x00);//读取寄存器内容
  RFM98_SPI_END();           //禁止SPI传输		    
  return(reg_val);           //返回状态值
}	
//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值 
u8 RFM98_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
  u8 status,i;	       
  RFM98_SPI_BEGIN();           //使能SPI传输
  status=SPI1_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值   	   
  for(i=0;i<len;i++)
     {  
       *pBuf = SPI1_ReadWriteByte(0x00); 
       pBuf++;
     }//读出数据
  RFM98_SPI_END();       //关闭SPI传输
  return status;        //返回读到的状态值
}
//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
u8 RFM98_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
  u8 status,i;	   
  reg |= 0x80;
  RFM98_SPI_BEGIN();          //使能SPI传输
  status = SPI1_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值
  for(i=0; i<len; i++)
   {
     SPI1_ReadWriteByte(*pBuf); 
     pBuf++;
   }//写入数据	 
  RFM98_SPI_END();        //关闭SPI传输
  return status;          //返回读到的状态值
}				   


//RFM98参数配置

void RFM98_Config(void)
{
     RFM98_Write_Reg(LR_RegOpMode+0x80+0x08);		//进入Lora模式
     RFM98_Write_Reg(PumpHigh); 
     RFM98_Write_Reg(PumpLow); 
     RFM98_Write_Reg(PumpBit); 
    //setting base parameter 
    RFM98_Write_Reg(RFM98PowerTbl[gb_PowerBuf_Addr]);             //Setting output power parameter  
    
    RFM98_Write_Reg(LR_RegOcp+0x0B);                              //RegOcp,Close Ocp
    RFM98_Write_Reg(LR_RegLna+0x23);                              //RegLNA,High & LNA Enable
    
   /* if(RFM98SpreadFactorTbl[gb_RateBuf_Addr]==6)           //SFactor=6
    {
      u8 tmp;
      RFM98_Write_Reg(LR_RegModemConfig1+(RFM98LoRaBwTbl[gb_BandBuf_Addr]<<4)+(CR<<1)+0x01);//Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
      RFM98_Write_Reg(LR_RegModemConfig2+(RFM98SpreadFactorTbl[gb_RateBuf_Addr]<<4)+(CRC<<2)+0x03);
      
      tmp = RFM98_Read_Reg(0x31);
      tmp &= 0xF8;
      tmp |= 0x05;
      RFM98_Write_Reg(0x3100+tmp);
      RFM98_Write_Reg(0x3700+0x0C);
    } 
    else*/
    {
      RFM98_Write_Reg(LR_RegModemConfig1+(gb_BandBuf_Addr<<4)+(CR<<1)+0x00);//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
      RFM98_Write_Reg(LR_RegModemConfig2+(gb_RateBuf_Addr<<4)+(CRC<<2)+0x03);  //SFactor &  LNA gain set by the internal AGC loop 
    }
    RFM98_Write_Reg(LR_RegSymbTimeoutLsb+0xFF);                   //RegSymbTimeoutLsb Timeout = 0x3FF(Max) 
    
    RFM98_Write_Reg(LR_RegPreambleMsb + 0);                       //RegPreambleMsb 
    RFM98_Write_Reg(LR_RegPreambleLsb + LeadCode); //8                     //RegPreambleLsb 8+4=12byte Preamble
    
    RFM98_Write_Reg(REG_LR_DIOMAPPING2+0x01);                     //RegDioMapping2 DIO5=00, DIO4=01
    RFM98_Write_Reg(LR_RegPacketConfig1 + 0x10);   //CRC_ON, Not Clear CRC
  
   RFM98_Write_Reg(LR_RegOpMode+0x01+0x08);                  //Entry standby mode  
}



/**********************************************************
**Name:     RFM98_LoRaReadRSSI
**Function: Read the RSSI value
**Input:    none
**Output:   temp, RSSI value
**********************************************************/
u8 RFM98_LoRaReadRSSI(void)
{
  u16 temp=10;
  temp=RFM98_Read_Reg(LR_RegRssiValue);                  //Read RegRssiValue,Rssi value
  temp=temp+127-137;                                       //127:Max RSSI, 137:RSSI offset
  return (u8)temp;
}

/**********************************************************
**Name:     RFM98_LoRaEntryRx
**Function: Entry Rx mode
**Input:    None
**Output:   None
**********************************************************/
void RFM98_LoRaEntryRx(u8 length)
{
  u8 addr; 
        
  RFM98_Config();                                         //setting base parameter
  
  RFM98_Write_Reg(0x4D00+0x84);                                   //Normal and Rx
  RFM98_Write_Reg(LR_RegHopPeriod+0xFF);                          //RegHopPeriod NO FHSS
  RFM98_Write_Reg(REG_LR_DIOMAPPING1+0x01);                       //DIO0=00, DIO1=00, DIO2=00, DIO3=01
      
  RFM98_Write_Reg(LR_RegIrqFlagsMask+0x3F);                       //Open RxDone interrupt & Timeout
  RFM98_Write_Reg(LR_RegIrqFlags+0xFF);   									//Clear IRQ
  
  RFM98_Write_Reg(LR_RegPayloadLength+ length);                       //RegPayloadLength  21byte(this register must difine when the data long of one byte in SF is 6)
    
  addr = RFM98_Read_Reg(LR_RegFifoRxBaseAddr);           //Read RxBaseAddr
  RFM98_Write_Reg(LR_RegFifoAddrPtr+addr);                        //RxBaseAddr -> FiFoAddrPtr  
  RFM98_Write_Reg(LR_RegOpMode+0x05+0x08);                        //Continuous Rx Mode 
}

/**********************************************************
**Name:     RFM98_LoRaRxPacket
**Function: Receive data in LoRa mode
**Input:    None
**Output:   1- Success
            0- Fail
**********************************************************/

u8 RFM98_LoRaRxPacket(u8 *rxbuf)
{ 
  u8 addr;
  u8 packet_size;
  u8 crc;
  u8 i;
  u8 *ptr;
  u8 len;
  u16 Sum;
  u16 RcvSum; 
    addr = RFM98_Read_Reg(LR_RegFifoRxCurrentaddr);      //last packet addr
    RFM98_Write_Reg(LR_RegFifoAddrPtr+addr);                      //RxBaseAddr -> FiFoAddrPtr    
  /*  if(RFM98SpreadFactorTbl[gb_RateBuf_Addr]==6)           //When SpreadFactor is six,will used Implicit Header mode(Excluding internal packet length)
      packet_size=21;
    else*/
      packet_size = RFM98_Read_Reg(LR_RegRxNbBytes);    //Number for received bytes    
    RFM98_Read_Buf(0x00, rxbuf, packet_size);
    crc = RFM98_Read_Reg(LR_RegIrqFlags);
    RFM98_Write_Reg(LR_RegIrqFlags+0xFF); //clear irq
    if( (TimeSlotMode != SNP_DOWN_CODE_MODE) && ( SysTimeSlot != Sen_UpLine ) )
    {  RfDisable();  } 
    if( (crc & 0x20) || (*rxbuf <= 2) )
     { return 0xff; }
    len = *rxbuf - 2;
    ptr = rxbuf;
    Sum = 0;
    for(i=0;i<len;i++)
     { Sum += *ptr++; }
    RcvSum = *ptr++;
    RcvSum |= *ptr<<8;
  //  if( TimeSlotMode != SNP_DOWN_CODE_MODE )
     // { RfDisable(); } 
    if( RcvSum == Sum )
      {  return *rxbuf; }
    else
      { return 0xff; }
    
}

/**********************************************************
**Name:     RFM98_LoRaEntryTx
**Function: Entry Tx mode
**Input:    None
**Output:   None
**********************************************************/
void RFM98_LoRaEntryTx(u8 length)
{
  u8 addr;
    
  RFM98_Config();                                         //setting base parameter
    
  RFM98_Write_Reg(0x4D00+0x87);                                   //Tx for 20dBm
  RFM98_Write_Reg(LR_RegHopPeriod);                               //RegHopPeriod NO FHSS
  RFM98_Write_Reg(REG_LR_DIOMAPPING1+0x41);                       //DIO0=01, DIO1=00, DIO2=00, DIO3=01
  
  RFM98_Write_Reg(LR_RegIrqFlags+0xFF);             //Clear irq
  RFM98_Write_Reg(LR_RegIrqFlagsMask+0xF7);                       //Open TxDone interrupt
  RFM98_Write_Reg(LR_RegPayloadLength+ length);                       //RegPayloadLength  21byte
  addr = RFM98_Read_Reg(LR_RegPayloadLength);
  addr = RFM98_Read_Reg(LR_RegFifoTxBaseAddr);           //RegFiFoTxBaseAddr
  RFM98_Write_Reg(LR_RegFifoAddrPtr+addr);                        //RegFifoAddrPtr
    
}
/**********************************************************
**Name:     RFM98_LoRaTxPacket
**Function: Send data in LoRa mode
**Input:    BUF ADDR
**Output:   1- Send over
**********************************************************/
void RfTxPacket(u8 *txbuf, u8 len)
{ 
  u8 addr;
  u8 i;
  u8 *ptr;
  u16 Sum;
  ConfigFlags |= DATE_SEND;
  *txbuf = len;  
  Sum = 0;
  ptr = txbuf;
  for(i=0;i<(len-2);i++)
     { Sum += *ptr++; }
  *ptr++ = Sum;
  *ptr = Sum>>8;
  addr = RFM98_Read_Reg(LR_RegFifoTxBaseAddr);       //RegFiFoTxBaseAddr
  RFM98_Write_Reg(LR_RegFifoAddrPtr+addr);                    //RegFifoAddrPtr
  RFM98_Write_Buf(0x00, txbuf, len);
  RFM98_Write_Reg(LR_RegOpMode+0x03+0x08);                    //Tx Mode 	
  RFM_flag |= IRQ_SEND_DATA;
}


void RfDisable(void)
{
  RFM98_Write_Reg(LR_RegOpMode+0x00+0x08);      //Entry Standby mode 
}
void CC2520_cfg(void)  
{
}
void RfEnable(u8 RxState)
{
}
void comm(u8 data)
{
}
void SetChannel(u8 data)
{
}
u8 GetSysVolt(void)       
{ 
   return 0;
}
#pragma vector = PORT2_VECTOR
__interrupt void FIFOP()
{ 
 // LPM3_EXIT;
  //AdIntrruptOff();
  WDTCTL = WDT_ARST_1000 ; 
  if(P2IFG & BIT5) //FIFOP 为高
  {
    P2IFG&=~BIT5;
    if( RFM_flag & IRQ_SEND_DATA )
    {
      RFM_flag &= ~IRQ_SEND_DATA;
      RFM98_Read_Reg(LR_RegIrqFlags);
      RFM98_Write_Reg(LR_RegIrqFlags+0xFF);             //Clear ir   
      ConfigFlags &= ~DATE_SEND;
      if((TimeSlotMode == SNP_DOWN_CODE_MODE))
      {
        RFM98_LoRaEntryRx(sizeof(SNP_UF_DOWN_CODE_PACKET_t));
      }
      else
      {
        RfDisable();
      }
      if(SetFlags & PUMP_CFG_SEND)
      {
        SetFlags &= ~PUMP_CFG_SEND;
        PumpHigh = NewPumpH;
        PumpHigh |= 0x0600;
        PumpLow = NewPumpL;
        PumpLow |= 0x0700;
        ConfigFlags |= SAVE_PUMP_COMD;                 
        DownLineConfig();   //配置通道(线下)
        RFM98_REST_DOWN();
        delay_us(200);
        RFM98_REST_UP();
      }
    }
    else
    {
      //P5OUT |= BIT4;
      RFDataPreprocess();
    }
  }
 // AdIntrruptOff();
}
