#ifndef  _NET_H
  #define  _NET_H
#include <types.h>
//------------------------------------------------------------------------------
#ifdef  _CM3_
#pragma pack(1)
#endif

typedef union 
{
    uint8 all;
    struct
    {
    uint8 On      : 1 ;
    uint8 Mco_On  : 1 ;
    uint8 Master  : 1 ;
    uint8 bt_125k : 1 ;
    uint8 bt_250k : 1 ;
    uint8 bt_1M   : 1 ;
    }_;
}TCanConfig;
//------------------------------------------------------------------------------
typedef struct 
   {
       uint8   Address ;             // CAN-адрес порта в сети к которой он подкл.
       uint8   MasterAddrSize ; // разрядная сетка адреса мастера - фиксированная.
       TCanConfig Config ;// не использ-ся
       uint8   btime0  ;          // 1-я настройка скорости порта
       uint8   btime1  ;          // 2-я настройка скорости порта
       uint8   __reserv0;
       uint16  Timeout ;  // дискрета timeout = 1мсек - фиксированна.
       uint8   connect ;  // количество отсчитываемых дискрет тайм-аута.
       uint8   AddressP ;   // адрес платы - не используется.
       uint16  __rezerv1  ;
}TCanSettings;
//------------------------------------------------------------------------------
typedef struct
{
  union
  {
	uint8 All;
	struct
  	{
    uint8	On       : 1;
    uint8	Master   : 1;
		uint8	b19200	 : 1;
		uint8	b38400	 : 1;
		uint8	b57600	 : 1;
    uint8	ParityOn : 1;
    uint8	Parity   : 1;
    uint8	StopBit  : 1;
    }_;
  }Settings;
  uint8      Address;
} TUartConfigCM3;
//------------------------------------------------------------------------------
typedef struct
{
  uint8	  On;
  uint8		IpAddress[4];
  uint8		IpMask[4];
  uint8		IpGate[4];
  uint8		MacAddress[6];
} TEthConfig;


//-----   Регистры платы  общая память -----
typedef struct
{
  uint8	TcpRequestF;	      // 00h
  uint8	TcpReadyF;            // 01h
  uint8   _Reserved0;          // 02h

  uint8	 RtuRequestF;         // 03h
  uint8   RtuReadyF;           // 04h
  uint8   BoardID;             // 05h идентификатор платы!

  uint8	 CanRequestF;          // 06h
  uint8	 CanReadyF;            // 07h
  uint8	 _Reserved1;           // 08h

  uint8   ModeRegH;             // 09h
  uint8	 TimerWD;              // 0Ah
  uint8   reg1[5];              // 0Bh

  TEthConfig EthConfig;
//  union config ;             // 10h
//  uint8 IP[4];	       // 11h - 14h
//  uint8 MaskIP[4];	       // 15h - 18h
//  uint8 GateIP[4];           // 19h - 1Ch
//  uint8 MAC[6];	       // 1Dh - 22h

  TCanSettings CanSettings;
//  uint8   addr ;             // 23h
//  uint8   master_addr_size ; // 24h
//  union  CAN_CONFIG config ; // 25h
//  uint8   btime0  ;          // 26h
//  uint8   btime1  ;          // 27h
//  uint16   timeout ;         // 28h - 29h
//  uint8   connect ;          // 30h
//  uint8   addr_p ;           // 31h
//  uint16   rezerv  ;         // 32h - 33h


//----- RS485 -----
  TUartConfigCM3 UartConfigCM3;
//  union config;              // 34h
//  uint8      addr;           // 35h

  uint8      TCPcount;          // 36h
  uint8      TCPErr;            // 37h

  uint8      CANErrBus;         // 38h
  uint8      CANErrRec;         // 39h
  uint8      CANErrSnd;         // 3Ah

  uint8      RTUcount;          // 3Bh
  uint8      RTUErr;            // 3Ch

  uint8      reg2[8];	       // 3Dh - 3Fh

  uint16      eth_length;        // 40h - 41h
  uint8      eth_data[0x600];   // 42h - 641h

  uint8      reg3[0xBE];        // 642h - 6FFh

  uint16      can_length;        // 700h - 701h
  uint8      can_data[0x10];    // 702h - 711h

  uint8      reg4[0xEE];        // 712h - 7FFh

  uint16      rtu_length;        // 800h - 801h
  uint8      rtu_data[0x100];   // 802h - 901h

  uint8      reg5[0x6FE];       // 902h - FFFh
  uint8      rez[1];            //для согласования
} TECRRegs;

#ifdef  _CM3_
#pragma pack()
#endif

#define AddrNet        (lw)0x00300000

// при чтении или записи переменных в сетевую плату, если читается или записывается
// несколько переменных подряд, то надо вставлять какую-то другую операцию (например, net_ptr++).
// Т.к. FR при чтении/записи нескольких переменных на внешней шине выставляет CS только один раз.
// А в сетевых платах сделано прерывание по CS...

//#define  READ_NET(dst, src)  { dst = *(w*)((lw)src); net_ptr=0; while (net_ptr<5) {net_ptr++;} }
#define  READ_NET(dst, src)  { dst = *(w*)((lw)src); net_ptr++; }

//#define  WRITE_NET(dst, src) { *((w*)(lw)dst) = (w)src; net_ptr++; }
#define  WRITE_NET(dst, src) { *((w*)(lw)dst) = (w)src; net_ptr=0; while (net_ptr<5) {net_ptr++;} }


#define   mSetNetReset()   PDR0_PD05 = 1
#define   mClrNetReset()   PDR0_PD05 = 0

#define   _NotDefined_              0x00
#define   _ProfibusDP_              0x01
#define   _ModbusTCPIP_             0x02
#define   _ModbusRTU_               0x03
#define   _CANopen_                 0x04
#define   _RS485FD_                 0x05


#ifdef _Union_FR

union  net_set
{
  byte all ;
  struct
   {
     byte  rezerved   : 4 ;

     byte  stop       : 1 ;
     byte  par2       : 1 ;
     byte  par1       : 1 ;
     byte  vkl        : 1 ;
   } _ ;
} ;

union  net_speed
{
  byte all ;
  struct
   {
     byte  sp115      : 1 ;
     byte  sp56       : 1 ;
     byte  sp38       : 1 ;
     byte  sp19       : 1 ;

     byte  sp9        : 1 ;
     byte  sp4        : 1 ;
     byte  sp2        : 1 ;
     byte  sp1        : 1 ;
   } _ ;
} ;

#else // _Union_FR

union  net_set
{
  byte all ;
  struct
   {
     byte  vkl        : 1 ;
     byte  par1       : 1 ;
     byte  par2       : 1 ;
     byte  stop       : 1 ;

     byte  rezerved   : 4 ;
   } _ ;
} ;

union  net_speed
{
  byte all ;
  struct
   {
     byte  sp1        : 1 ;
     byte  sp2        : 1 ;
     byte  sp4        : 1 ;
     byte  sp9        : 1 ;

     byte  sp19       : 1 ;
     byte  sp38       : 1 ;
     byte  sp56       : 1 ;
     byte  sp115      : 1 ;
   } _ ;
} ;

#endif // _Uniopn_FR

#define   _net_cfg_vkl         0x01
#define   _net_cfg_par1        0x02
#define   _net_cfg_par2        0x04
#define   _net_cfg_stop        0x08

#define   _net_spd_1           0x01
#define   _net_spd_2           0x02
#define   _net_spd_4           0x04
#define   _net_spd_9           0x08
#define   _net_spd_19          0x10
#define   _net_spd_38          0x20
#define   _net_spd_56          0x40
#define   _net_spd_115         0x80

#define      DR_IER            (AddrNet   )
#define      DR_IDR            (AddrNet+2 )
#define      DR_ISR            (AddrNet+4 )
#define      DR_IMR            (AddrNet+6 )  // Маска прерывний        RO
#define      DR_IAR            (AddrNet+8 )  // Резерв                 RO
#define      DR_CHIPID         (AddrNet+10)  // Идентификатор платы    RO
#define      DR_SR             (AddrNet+12)  // Статус                 RO
#define      DR_CR             (AddrNet+14)  // Упраление              WR
#define      DR_TLIFE          (AddrNet+16)  // Время жизни, мс        RW
#define      DR_IPADDR0        (AddrNet+18)  // IP адрес               RW
#define      DR_IPADDR1        (AddrNet+20)  //
#define      DR_IPADDR2        (AddrNet+22)  //
#define      DR_IPADDR3        (AddrNet+24)  //
#define      DR_NETMASK0       (AddrNet+26)  // Маска подсети          RW
#define      DR_NETMASK1       (AddrNet+28)  //
#define      DR_NETMASK2       (AddrNet+30)  //
#define      DR_NETMASK3       (AddrNet+32)  //
#define      DR_DRIPADDR0      (AddrNet+34)  // Шлюз                   RW
#define      DR_DRIPADDR1      (AddrNet+36)  //
#define      DR_DRIPADDR2      (AddrNet+38)  //
#define      DR_DRIPADDR3      (AddrNet+40)  //
#define      DR_ETHADDR0       (AddrNet+42)  // EMAC адрес             RW
#define      DR_ETHADDR1       (AddrNet+44)  //
#define      DR_ETHADDR2       (AddrNet+46)  //
#define      DR_ETHADDR3       (AddrNet+48)  //
#define      DR_ETHADDR4       (AddrNet+50)  //
#define      DR_ETHADDR5       (AddrNet+52)  //
#define      DR_ADDR           (AddrNet+54)  // Адрес в сети Модбас    RW
#define      DR_SPEED          (AddrNet+56)  // Скорость в сети Модбас RW
#define      DR_MODE           (AddrNet+58)  // Скорость в сети Модбас RW
#define      DR_ERROR          (AddrNet+60)  // Скорость в сети Модбас RW
#define      DR_NDI            (AddrNet+64)  // Номер входного буфера   RO
#define      DR_NDO            (AddrNet+66)  // Номер выходного буфера  RO
#define      DR_DLI           (AddrNet+512)  // Длина входного буфера 1        RW
#define      DR_DI            (AddrNet+514)  // Входной буфер 1        RW
#define      DR_DLO           (AddrNet+1024) // Длина выходного буфера 1       RW
#define      DR_DO            (AddrNet+1026) // Выходной буфер 1       RW


 /*-----------------21.04.2010 15:27-----------------
 * -----   DR_IER, DR_IDR, DR_ISR   -----
 * Bit  0 - Line find/searh
 * Bit  1 - Life-Time
 * Bit  2 - New Data In
 * -----   DR_CR   -----
 * Bit  0 - START
 * Bit  1 - STOP
 * Bit  2 - EOI
 * Bit  3 - Master
 * Bit  4 - Slave
 * Bit  5 - Change Buffer In
 * Bit  6 - Change Buffer Out
 * -----   DR_SR   -----
 * Bit  0 - START/STOP  = 1/0
 * Bit  1 - Master/Slave = 1/0
 * Bit  2 - Search/Find = 0/1
 * --------------------------------------------------*/

 #define  DR_ISR_SF         0x0001
 #define  DR_ISR_LT         0x0002
 #define  DR_ISR_ND         0x0004

 #define  DR_CR_START       0x0001
 #define  DR_CR_STOP        0x0002
 #define  DR_CR_EOI         0x0004
 #define  DR_CR_MASTER      0x0008
 #define  DR_CR_SLAVE       0x0010
 #define  DR_CR_CBI         0x0020
 #define  DR_CR_CBO         0x0040
 #define  DR_CR_LOAD	    0x0080

 #define  DR_SR_SS          0x0001
 #define  DR_SR_MS          0x0002
 #define  DR_SR_SF          0x0004



 #define  _FLAGNET_NO		0x00
 #define  _FLAGNET_SEND		0x01


void Init_Net( void ) ;
void Init_Net_Msg( void ) ;
word Work_Net( byte flag ) ;

#ifdef _NET_INCLUDE
   byte net_ptr ;
   byte TypeNet ;
   byte flag_net ;
   word ErrorNet;
#else
   extern byte net_ptr ;
   extern byte TypeNet ;
   extern byte flag_net ;
   extern word ErrorNet;
#endif


//---------   Определения для СМ3   -------------------

void NET_Reset( void );

extern TECRRegs *NetRam;

#endif  //  _NET_H


