#ifndef TYPES_H
#define TYPES_H
#include <msp430x54x.h>
/***********************************************************************************
 * TYPEDEFS
 */
typedef signed   char   int8;
typedef unsigned char   u8;


typedef signed   short  int16;
typedef unsigned short  u16;


typedef signed   long   int32;
typedef unsigned long   u32;



/***********************************************************************************
* CONSTANTS AND DEFINES
*/
#define CPU_F ( (double) 8000000)

#define delay_us(x) __delay_cycles( (long)(CPU_F*(double)(x) / 1000000.0))
#define delay_ms(x) __delay_cycles( (long)(CPU_F*(double)(x) / 1000.0))

#define Sys_Soft_Reset()  WDTCTL=0x0000

#define AP_FORMAL   1   // 1 正式AP  0 模拟测试AP
#define UART_TEST_MODE   0  //不用
//#define STRING_TEST    1//打印数据
//#define SCAN_NARROW   0     //1 实际扫描4ms，0 测试扫描125ms
#define RP_ON      0
#define NEW_BOARD     1   //板本
#define SMOOTH_ON     0  //ON时等待熄火再发送数据  1:等待  0：不等待
//烧写程序
//***********************************************
#define LED_TEST_ON          1  //测试模式
#define FIXED_ID             1 //固定ID，时间槽，通道    
#define STRING_ON            1
#define ON_START_GEY_BASELINE_TIME   120//2分钟
#define REST_AD_DELAY        70
#define REST_OFF_DELAY       100


#define STATE_ON              0 // 车位状态 1 / 实时事件 0 (复位事件是否上报   1:上报，        0:不上报)
#define DEFAULT_ID    0xa502
#define DEFAULT_NUM   1
#define HIGH_PUMP     0x066d
#define LOW_PUMP      0x0700
#define POWER_RF      2    //433 功率  0 :20DB     1: 17DB       2: 14DB     3: 11DB
#define VERSION_HIGH       6
#define VERSION_LOW        10
//************************************************
#define  DIRECT_Z   1
#define  DIRECT_X   0

#define  HALF_ON    1
#define  EVENT_ON   0

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0   
#endif

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILED
#define FAILED  1
#endif

#ifndef OUTPUT
#define OUTPUT	1
#endif

#ifndef INPUT
#define INPUT	0
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW	0
#endif

#ifndef ON
#define ON	1
#endif

#ifndef OFF
#define OFF	0
#endif

#ifndef DOING
#define DOING	0
#endif

#ifndef DONE
#define DONE   1
#endif

#ifndef ERR
#define ERR 0xFF
#endif
/***********************************************************************************
* MACROS
*/

#ifndef BV
#define BV(n)      (1 << (n))
#endif

#ifndef BM
#define BM(n)      (1 << (n))
#endif

#ifndef BF
#define BF(x,b,s)  (((x) & (b)) >> (s))
#endif

#ifndef MIN
#define MIN(n,m)   (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n,m)   (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
#define ABS(n)     (((n) < 0) ? -(n) : (n))
#endif


/* uint32 processing */
#define BREAK_UINT32( var, ByteNum ) \
    (uint8)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
    ((uint32)((uint32)((Byte0) & 0x00FF) \
        + ((uint32)((Byte1) & 0x00FF) << 8) \
            + ((uint32)((Byte2) & 0x00FF) << 16) \
                + ((uint32)((Byte3) & 0x00FF) << 24)))

#define HI_UINT32(a) ((uint16) (((uint32)(a)) >> 16))
#define LO_UINT32(a) ((uint16) ((uint32)(a)))


/* uint16 processing */
#define BUILD_UINT16(loByte, hiByte) \
    ((uint16)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define HI_UINT16(a) (((uint16)(a) >> 8) & 0xFF)
#define LO_UINT16(a) ((uint16)(a) & 0xFF)


/* uint16 processing */
#define BUILD_UINT8(hiByte, loByte) \
    ((uint8)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT8(a) (((uint8)(a) >> 4) & 0x0F)
#define LO_UINT8(a) ((uint8)(a) & 0x0F)

/***********************************************************************************
 * Host to network byte order macros
 */
#define BIG_ENDIAN
#ifdef BIG_ENDIAN
#define UINT16_HTON(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint16)); )
#define UINT16_NTOH(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint16)); )

#define UINT32_HTON(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint32)); )
#define UINT32_NTOH(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint32)); )
#else
#define UINT16_HTON(x)
#define UINT16_NTOH(x)

#define UINT32_HTON(x)
#define UINT32_NTOH(x)
#endif


/*
*  This macro is for use by other macros to form a fully valid C statement.
*  Without this, the if/else conditionals could show unexpected behavior.
*
*  For example, use...
*    #define SET_REGS()  st( ioreg1 = 0; ioreg2 = 0; )
*  instead of ...
*    #define SET_REGS()  { ioreg1 = 0; ioreg2 = 0; }
*  or
*    #define  SET_REGS()    ioreg1 = 0; ioreg2 = 0;
*  The last macro would not behave as expected in the if/else construct.
*  The second to last macro will cause a compiler error in certain uses
*  of if/else construct
*
*  It is not necessary, or recommended, to use this macro where there is
*  already a valid C statement.  For example, the following is redundant...
*    #define CALL_FUNC()   st(  func();  )
*  This should simply be...
*    #define CALL_FUNC()   func()
*
* (The while condition below evaluates false without generating a
*  constant-controlling-loop type of warning on most compilers.)
*/
#define st(x)      do { x } while (__LINE__ == -1)

#endif