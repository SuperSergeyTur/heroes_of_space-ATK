//---------------------------------------------------------------------------
#ifndef IOcanH
#define IOcanH

#include "Netdefs.h"
#include "Resource.h"
#include "Driver.h"

class CAN_SETTING
{
 public:
  unsigned char addr;              // Адрес мастера
  unsigned char master_addr_size;  // Количество разрядов X мастера в XXXX000000
  unsigned char btime0;            // Регистры задания таймингов
  unsigned char btime1;
  unsigned char config;            // Пока не исползуется
  unsigned int addr_p;             // адрес платы (или ее номер в WIN32)

  int timeout;                     // Дискрета соединения
  int connect;                     // Тайм-аут

  __fastcall CAN_SETTING();
  __fastcall ~CAN_SETTING();
};

//---------------------------------------------------------------------------

class TCANIO
{
 private:

  long DriverHandle;
  WORD CPort;
  WORD CHostID;
  WORD CBaudRate;
  LRESULT result;
  ULONG portnum;
  USHORT far EventType;
  USHORT far MacID;

  HINSTANCE DriverLib;
  HINSTANCE PCL841Lib;

  BOOL DReady;
  bool Port_active;


 public:

  LRESULT __stdcall (*pDeviceConfig)(ULONG DeviceNum,DWORD BoardID,HWND owner);
  LRESULT __stdcall (*pDeviceOpen)(ULONG DeviceNum, LONG far * DeviceHandle);
  LRESULT __stdcall (*pCANPortOpen)(WORD DevNum, WORD *wPort,
                           WORD *wHostID, WORD *wBaudRate);
  LRESULT __stdcall (*pCANPortClose)(WORD wPort);
  LRESULT __stdcall (*pCANInit)(WORD Port,WORD BTR0,WORD BTR1,UCHAR usMask);
  LRESULT __stdcall (*pCANReset)(WORD Port);
  LRESULT __stdcall (*pCANSetNormal)(WORD Port);
  LRESULT __stdcall (*pCANInpb)(WORD Port,WORD Offset,UCHAR *Data);
  LRESULT __stdcall (*pCANOutpb)(WORD Port,WORD Offset,UCHAR Value);
  LRESULT __stdcall (*pCANSendMsg)(WORD Port,UCHAR *TxBuf,BOOL Wait);
  LRESULT __stdcall (*pCANQueryMsg)(WORD Port,BOOL *Ready,UCHAR *RcvBuf);
  LRESULT __stdcall (*pCANWaitForMsg)(WORD Port,UCHAR FAR *RcvBuf,
                      ULONG uTimeValue);
  LRESULT __stdcall (*pCANSetAcp)(WORD Port,WORD Acp,WORD Mask);

  #pragma pack (push)
  #pragma pack (1)
  struct MSG_STRUCT{
    unsigned int IDhigh:8;
    unsigned int dlc:4;
    unsigned int RTR:1;
    unsigned int IDlow:3;
    unsigned char Data[8];
  };
  #pragma pack (pop)

  CAN_SETTING port_param;
  MSG_STRUCT TxData;

  __fastcall TCANIO(ULONG DevNum);
  __fastcall ~TCANIO();

  int CAN_Init(char work_port);
  int CAN_Close(void);
  int __fastcall IO_data(char port, char ab_addr, char var_num,
                         namevar **Var_buff,
                         char cmd, char n_kl,
                         char counter);
  int __fastcall PORT_WRITE_param(int numhandle);
  int __fastcall PORT_READ_param(int numhandle);
  int __fastcall PORT_UPDATE_param(struct CAN_SETTING *param);
};

//---------------------------------------------------------------------------

extern TCANIO *CANIO;
extern struct CAN_SETTING *CAN_params;
#endif

