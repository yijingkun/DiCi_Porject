#ifndef RF_HAL_H
#define RF_HAL_H

#define RF_RX_PACKET_CRC_ERROR	0xFFFC
#define RF_RX_PACKET_TIMEOUT	0xFFFD

typedef struct _RF_FCS_t
{
  u8	uiRssi;
  u8	uiCrc;
} RF_FCS_t;



void CommunictionInit(void);
void SendTest(void);
void RFDataPreprocess(void);
void rfDataHandle(void);
void RfInit(void);
void UINT_16_HTON(u8 *ptr);
void ComandPro(void);
void RfTest(void);
void delay400ms(void);
#endif