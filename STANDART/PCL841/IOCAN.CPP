//---------------------------------------------------------------------------
#include <vcl.h>
#include <io.h>
#include <fcntl.h>

#pragma hdrstop

#include "IOserv.h"
#include "Can_win.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#define _Num_Klient 10

TCANIO *CANIO;
CAN_SETTING *CAN_params;

struct Abonent_form ab841[_Num_Klient];
struct namevar t_ab[_Num_Klient] ;

//---------------------------------------------------------------------------
__fastcall CAN_SETTING::CAN_SETTING()
{
 addr = 1;
 addr_p = 1;
 master_addr_size = 4;
 btime0 = 0x43;
 btime1 = 0x2f;
 config = 0x00;

 timeout = 1;
 connect = 5;

 //message("Constructor called");
}

__fastcall CAN_SETTING::~CAN_SETTING()
{
 //message("Destructor called");
}
//---------------------------------------------------------------------------
__fastcall TCANIO::TCANIO(ULONG DevNum)
{
 int n;

 Port_active = false;
 DReady = false;

 PCL841Lib = LoadLibrary("ADS841.DLL");

 if (PCL841Lib != NULL)
 {
  /* Подключение экспортируемых функций */

  pCANPortOpen = (LRESULT __stdcall (*)(WORD, WORD*, WORD*, WORD*))
                  GetProcAddress(PCL841Lib, "CANPortOpen");
  pCANPortClose = (LRESULT __stdcall (*)(WORD))
                  GetProcAddress(PCL841Lib, "CANPortClose");
  pCANInit = (LRESULT __stdcall (*)(WORD,WORD,WORD,UCHAR))
                  GetProcAddress(PCL841Lib, "CANInit");
  pCANReset = (LRESULT __stdcall (*)(WORD))
                  GetProcAddress(PCL841Lib, "CANReset");
  pCANSetNormal = (LRESULT __stdcall (*)(WORD))
                  GetProcAddress(PCL841Lib, "CANSetNormal");
  pCANInpb = (LRESULT __stdcall (*)(WORD,WORD,UCHAR *))
                  GetProcAddress(PCL841Lib, "CANInpb");
  pCANOutpb = (LRESULT __stdcall (*)(WORD,WORD,UCHAR))
                  GetProcAddress(PCL841Lib, "CANOutpb");
  pCANSendMsg = (LRESULT __stdcall (*)(WORD,UCHAR *,BOOL))
                  GetProcAddress(PCL841Lib, "CANSendMsg");
  pCANQueryMsg = (LRESULT __stdcall (*)(WORD,BOOL *,UCHAR *))
                  GetProcAddress(PCL841Lib, "CANQueryMsg");
  pCANSetAcp = (LRESULT __stdcall (*) (WORD, WORD, WORD))
                  GetProcAddress(PCL841Lib, "CANSetAcp");
  pCANWaitForMsg = (LRESULT __stdcall (*)(WORD,UCHAR FAR *,
                      ULONG uTimeValue))
                  GetProcAddress(PCL841Lib, "CANWaitForMsg");
  portnum = DevNum;
 }
 else
  message("Can't load library");
}
//---------------------------------------------------------------------------
__fastcall TCANIO::~TCANIO()
{
 FreeLibrary(PCL841Lib);
}
//---------------------------------------------------------------------------
int TCANIO::CAN_Init(char work_port)
{
 AnsiString TestData;
 int Result;

 if(Port_active)
  return 0;

  /* Инициализация CAN */

 if(pCANPortOpen(port_param.addr_p - 1, &CPort, &CHostID, &CBaudRate))
 {
  message("Can port open failed");
   return -1;
 }

 Result = pCANReset(CPort);
 CANIO = Mainclass->RootVars[work_port].Canport;

 if(can_init(CPort ))//, &port_param))
  return -1;
 else
  Port_active = true;

 return 0;
}
//---------------------------------------------------------------------------
int TCANIO::CAN_Close()
{
 if(Port_active)
 {
  pCANReset(CPort);
  pCANPortClose(port_param.addr_p - 1);

  Port_active = false;
 }
 return 0;
}
//---------------------------------------------------------------------------
int __fastcall TCANIO::PORT_WRITE_param(int numhandle)
{
 try
 {
  /* Запись адреса порта */
  if(_rtl_write(numhandle, &port_param.addr_p, sizeof(char)) == -1)
   throw -1;

  /* Запись адреса мастера */
  if(_rtl_write(numhandle, &port_param.addr, sizeof(char)) == -1)
   throw -1;

  /* Запись количества разрядов сервера */
  if(_rtl_write(numhandle, &port_param.master_addr_size, sizeof(char)) == -1)
   throw -1;

  /* Запись параметров тайминга соединения */
  if(_rtl_write(numhandle, &port_param.btime0, sizeof(char)) == -1)
   throw -1;
  if(_rtl_write(numhandle, &port_param.btime1, sizeof(char)) == -1)
   throw -1;

  /* Запись параметров конфигурации */
  if(_rtl_write(numhandle, &port_param.config, sizeof(char)) == -1)
   throw -1;

  /* Запись временной дискреты */
  if(_rtl_write(numhandle, &port_param.timeout, sizeof(int)) == -1)
   throw -1;

  /* Запись времени time-out */
  if(_rtl_write(numhandle, &port_param.connect, sizeof(int)) == -1)
   throw -1;

  return 0;
 }

 catch(int)
 {
  return -1;
 }
}
//---------------------------------------------------------------------------
int __fastcall TCANIO::PORT_READ_param(int numhandle)
{
 try
 {
  /* Чтение адреса порта */
  if(_rtl_read(numhandle, &port_param.addr_p, sizeof(char)) == -1)
   throw -1;

  /* Чтение адреса мастера */
  if(_rtl_read(numhandle, &port_param.addr, sizeof(char)) == -1)
   throw -1;

  /* Чтение количества разрядов сервера */
  if(_rtl_read(numhandle, &port_param.master_addr_size, sizeof(char)) == -1)
   throw -1;

  /* Чтение параметров тайминга соединения */
  if(_rtl_read(numhandle, &port_param.btime0, sizeof(char)) == -1)
   throw -1;
  if(_rtl_read(numhandle, &port_param.btime1, sizeof(char)) == -1)
   throw -1;

  /* Чтение параметров конфигурации */
  if(_rtl_read(numhandle, &port_param.config, sizeof(char)) == -1)
   throw -1;

  /* Чтение временной дискреты */
  if(_rtl_read(numhandle, &port_param.timeout, sizeof(int)) == -1)
   throw -1;

  /* Чтение времени time-out */
  if(_rtl_read(numhandle, &port_param.connect, sizeof(int)) == -1)
   throw -1;

  return 0;
 }

 catch(int)
 {
  return -1;
 }
}
//---------------------------------------------------------------------------
int __fastcall TCANIO::PORT_UPDATE_param(struct CAN_SETTING *param)
{
 port_param = *param;

 return 1;
}
//---------------------------------------------------------------------------

int __fastcall TCANIO::IO_data(char port, char ab_addr, char var_num,
                               namevar **Var_buff,
                               char cmd, char n_kl, char counter)
{
      //  Создаем временную перевалочную структуру описывающую одного абонента.
 word ax, i ;
 byte  dscr[9] ;

 // Сейчас порт определяется как номер ветви
 CANIO = Mainclass->RootVars[port].Canport;

 // А сейчас как физический номер порта
 port = Mainclass->RootVars[port].Canport->CPort;

 //  Заполняем созданную структуру.
 ab841[n_kl].port = port ;
 ab841[n_kl].ab_addr = ab_addr ;
 ab841[n_kl].size_var_tab = var_num ;
 ab841[n_kl].var_tab = &t_ab[n_kl] ;

 //ab841[n_kl].long_io.size = 0 ;

 for ( i = 0 ; i < var_num ; i++ )
 {   // копируем данные описывающие i-тую переменную.
  ab841[n_kl].var_tab[i] = *Var_buff[i];
  dscr[i] = i ;
 }

 dscr[i] = 0xff ;// оформляем конец строки перечня дескрипторов.

 //  Выбор команды.
  //if ( can_test( port ) != 0 ) return ?;

  can_test( port ) ;

  Receive_Monitor( port ) ;
    //canSlaveDrive( port ) ;

 switch (cmd)
 {
  case 1:
    //ax = master_read(port, dscr , &ab841[n_kl], counter);
    ax = master_read( dscr , &ab841[n_kl], counter);
  break;      //   WRITE

  case 2:
    //ax = master_write(port, dscr, &ab841[n_kl], counter);
    ax = master_write( dscr, &ab841[n_kl], counter);
  break;

  default:;      //   READ
 }

 for ( i = 0; i < var_num; i++)
 {   // копируем обратно обработанные данные описывающие i-тую переменную.
  Var_buff[i]->tag      = ab841[n_kl].var_tab[i].tag;
  Var_buff[i]->dscr     = ab841[n_kl].var_tab[i].dscr;
  Var_buff[i]->addr_var = ab841[n_kl].var_tab[i].addr_var;
  Var_buff[i]->type     = ab841[n_kl].var_tab[i].type;
  Var_buff[i]->lon      = ab841[n_kl].var_tab[i].lon;
  Var_buff[i]->access   = ab841[n_kl].var_tab[i].access;
 }

 return ax ;
}
//---------------------------------------------------------------------------
