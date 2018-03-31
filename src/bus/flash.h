#ifndef FLASH_H
#define FLASH_H

#include "cfg.h" 

#define SegmentA   0x1980  ///错误
#define SegmentB   0x1900
#define SegmentC   0x1880
#define SegmentD   0x1800

/*
#define APP_CODE_ADDRESS    0x1200     //code 存放地址
#define SAVE_CODE_ADDRESS   0x8400     //code 临时存放地址
#define INT_ERESS_PAGE      0x8200
#define INT_WRITE_ADDRESS   0x83E0
#define CODE_SAVE_COMPLETE  0x83DE
#define SEG_PAGE_NUM        56
#define CHECK_NUM_ADDRESS   0x107E
*/
/*
#define APP_CODE_ADDRESS    0x1200     //code 存放地址
#define SAVE_CODE_ADDRESS   0x8400     //code 临时存放地址
#define INT_ERESS_PAGE      0x8200
#define INT_WRITE_ADDRESS   0x83E0
#define CODE_SAVE_COMPLETE  0x83DE
#define SEG_PAGE_NUM        56
#define CHECK_NUM_ADDRESS   0x197E*/

#define SAVE_CODE_ADDRESS1     0x6000   //0xdc00//  //code 临时存放地址
#define SAVE_CODE_ADDRESS2_1   0xEC00
#define SAVE_CODE_END2_1       0xFC00
#define SAVE_CODE_ADDRESS2_2   0x10000
#define LOW_HIGH_ADD           0x8c
#define SEG_PAGE_NUM        75
#define CHECK_NUM_ADDRESS   0x197E
#define JUMP_ADRESS         0xFDFF
#define LOW_ADRESS          0x60
#define HIGH_ADRESS         0xEC
#define DAY_CNT_ADDRS       0x1892

#define EVENT_SAVE_ADRESS     0x25a00

typedef struct  _FLASH_PARAMTER_t
{
  u16                    RestNum;  //ff
  u16                    PhysicalID2;  //ff
  u16                    PhysicalID3;  //ff
  u16                    PhysicalID4;  //ff
  u16                    SenID;
  u16                    SenTimeSlotNum;
  u16                    BaseLineZ;  //FF
  u16                    BaseLineX; //FF
  u16                    BaseLineY;   //ff
  u8                     ResetFlag;   //ff
  u8                     ParamtSet;
  u8                     PumpHigh;
  u8                     PumpLow;
  u16                    SetBaseLineZ;  //FF
  u16                    SetBaseLineX;  //FF
  u8                     WatchDogRst;  //ff
  u8                     RfPower;
  u16                    TempBaseZ;
  u16                    TempBaseX;//
  u16                    BaseBuffZ[BASE_BUFF_NUM];
  u16                    BaseBuffX[BASE_BUFF_NUM];
  u8                     BaseBuffPtrZ;
  u8                     BaseBuffPtrX;
}FLASH_PARAMTER_t;

typedef struct _EVENT_SAVE_SYS
{
  u8 Hour;
  u8 Minute;
  u8 Second;
  u8 Flag;
}EVENT_SAVE_SYS;

void EraseSectorFlashB();
u16 FlashWriteB(u8 *Datain,u8 count);
void FlashReadB(u8 *Dataout,u8 count);
void EraseSectorFlash( u32 Address);
void FlashWrite(u32 Address, u8 *Datain,u16 count);
void FlashRead(u32 Address, u8 *Dataout,u16 count);
void EraseSectorFlashC( void );

#endif