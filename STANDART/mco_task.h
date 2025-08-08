#ifndef  _MCO_TASK_H
   #define  _MCO_TASK_H


#include "array.h"
#include "mco_can.h"
#include "mco_sdo.h"
#include "mco_nmt.h"
#include "mco_dict.h"
#include "mco_emcy.h"
#include "mco_sync.h"


#define NUM_MAILBOX_MAX		13
#define MB_BROADCAST		0
#define MB_NMT_RX			1
#define MB_NMT_TX			2
#define MB_SDO_RX			3
#define MB_SDO_TX			4
#define MB_PDO_RX			5
#define MB_PDO_TX			6
#define MB_PDO21_TX			7
#define MB_PDO22_TX			8
#define MB_PDO23_TX			9
#define MB_PDO21_RX			10
#define MB_PDO22_RX			11
#define MB_PDO23_RX			12



#define  CAN_INTERRUPT(x)		MCO_Server( TCAN_Transfer *pTransfer)

#define CAN_BAUD_1M     		0x1C00
#define CAN_BAUD_500K   		0x1C01
#define CAN_BAUD_250K   		0x1C03
#define CAN_BAUD_125K   		0x3A07
#define CAN_BAUD_100K   		0x4D07
#define CAN_BAUD_50K    		0x4D0f
#define CAN_BAUD_20K    		0x4D27
#define CAN_BAUD_10K    		0x7FFF
#define CAN_BAUD_83K3			0x1417
#define CAN_BAUD_47K6			0x1429
#define CAN_BAUD_95K2			0x1414
#define CAN_BAUD_33K3			0x581D

#define MCO_CMD_START		1
#define MCO_CMD_STOP		2
#define MCO_CMD_PREOP		128
#define MCO_CMD_RESETAPP	129
#define MCO_CMD_RESETCOM	130

#define MCO_STS_BOOTUP		0
#define MCO_STS_STOPPED		4
#define MCO_STS_OPER		5
#define MCO_STS_PREOP		127

// Broadcast COB-ID
#define _COBID_NMT			0x0	// 0000
#define _COBID_SYNC			0x1	// 0001
#define _COBID_TIMESTAMP    0x2	// 0010
// COB-ID abonent
#define _COBID_EMCY			0x1	// 0001
#define _COBID_NMTERR		0xE	// 1110
// COB_ID own
#define _COBID_PDO1TX		0x3	// 0011
#define _COBID_PDO2TX		0x5	// 0101
#define _COBID_PDO3TX		0x7	// 0111
#define _COBID_PDO4TX		0x9	// 1001
#define _COBID_PDO1RX		0x4	// 0100
#define _COBID_PDO2RX		0x6	// 0110
#define _COBID_PDO3RX		0x8	// 1000
#define _COBID_PDO4RX		0xA	// 1010
#define _COBID_SDOTX		0xB	// 1011
#define _COBID_SDORX		0xC	// 1100
#define _COBID_PDO			0xD	// 1101


#ifndef _Union_FR
//#pragma pack(1)
typedef union
{
	struct
	{
	   lword	lo;
	   lword	hi;
	}_;
	byte		data[8];
	TSDO_msg	sdo;
}TMCO_msg;

//#pragma pack()

typedef union
{
  word slovo;
  struct
  {
     byte b1;
	 byte b2;
  }_;
}TWord;

typedef union
{
  lword slovo;
  struct
  {
     TWord w1;
	 TWord w2;
  }_;
}TLword;

typedef union
{
	lword   lw;
	struct
	{
	  word	w1;
	  word	w2;
	}w;
	struct
	{
	  byte	b1;
	  byte	b2;
	  byte	b3;
	  byte	b4;
	}b;
}TLWord;

#else

typedef union
{
	struct
	{
	   lword	lo;
	   lword	hi;
	}_;
	byte		data[8];
//	TSDO_msg	sdo;
}TMCO_msg;

//#pragma pack()

typedef union
{
  word slovo;
  struct
  {
	 byte b2;
     byte b1;
  }_;
}TWord;

typedef union
{
  lword slovo;
  struct
  {
	 TWord w2;
     TWord w1;
  }_;
}TLword;

typedef union
{
	lword   lw;
	struct
	{
	  word	w2;
	  word	w1;
	}w;
	struct
	{
	  byte	b4;
	  byte	b3;
	  byte	b2;
	  byte	b1;
	}b;
}TLWord;


#endif


#include "mco_pdo.h"


void MCO_Init( byte port );
void MCO_Server( TCAN_Transfer *pTransfer );
void MCO_Background( byte port );

//#define mReversByte(x) { byte bb;  bb = x._.b1; x._.b1 = x._.b2; x._.b2 = bb; }
#ifdef _CANOPEN_INCLUDE

//TMCO_ust _mr;
byte mco_state;
byte flag_initmap, flag_set_rpdo;
byte mco_vkl;
TMCO_msg		mco;
TMCO_ust	mco_ust;
TTimer Timer_mco_send;

#else

//extern TMCO_ust _mr;
extern byte mco_state;
extern byte flag_initmap, flag_set_rpdo;
extern byte mco_vkl;
extern TMCO_msg		mco;
extern TMCO_ust	mco_ust;
extern TTimer Timer_mco_send;;

#endif

#endif  // _MCO_H
