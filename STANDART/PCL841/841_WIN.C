
#include <vcl.h>
#include <io.h>
#include <fcntl.h>

#include <process.h>
#include "resource.h"

//---------------------------------------------------------------------------
   //   Программы совмещения функций посылки/приема сообщения дл
   //                      DOS и Windows.
   // Несовместимость проявляется в различном построении передаваемых
   // им структур данных MSG_STRUCTx (иначе можно было бы обойтись условной
   // компиляцией, подставляя вызов той или иной функции с теми же данными).
   //  Программа производит только лишь перевалку данных из структуры
   // одного типа в другой.

//---------------------------------------------------------------------------
/* reset can controller */
int  canReset( byte port )
{
  return CANIO->pCANReset( port );
}
//---------------------------------------------------------------------------
/* initiallize and configure can controller */
int  canConfig( byte port, CAN_STRUCT can)
{
  word ax ;

  CANIO->pCANInit (port, can.bt0, can.bt1, 0);
  ax = CANIO->pCANSetAcp(port, can.acc_code, can.acc_mask);
         // Задаем в догонку собственный сетевой CAN-адрес порта в его сети.
         // его можно задавать только при установленном бите 'reset'.
  return ax ;
}
//---------------------------------------------------------------------------
/* change can controller to normal run mode */
int  canNormalRun( byte port )
{
  return !CANIO->pCANSetNormal(port);
}
//---------------------------------------------------------------------------

word canSend( byte  port, struct canMSG_hw *send_msg)
{
  MSG_STRUCT_WIN  msg_win ;
  word i ;

         //  Приведение ID от общего вида к виду PCL841.
  msg_win.IDhigh = (send_msg->id >> (5+16)) >> 3 ;
  msg_win.IDlow  = send_msg->id  >> (5+16) ;
  msg_win.RTR    = 0 ; //22.04.03 11:39send_msg->cfg.dir ^ 1 ;
  msg_win.dlc    = send_msg->cfg.dlen;
  for (i=0; i<8; i++) msg_win.Data[i] = send_msg->data[i];

  i = CANIO->pCANSendMsg( port, (unsigned char *)(&msg_win), TRUE);

      //  Передаю Максиму ожидаемый в ответ ID, чтобы он мог отсеять
      // ответ на мою посылку из посылок WAGO.
#ifdef _CAN_WAGO
  CANIO->SetCAN_ID( 0, (send_msg->id >> (5+16)) ) ;
#endif

  return i;
}

//---------------------------------------------------------------------------
word canReceive( byte  port, struct canMSG_hw *rec_msg)
{
  MSG_STRUCT_WIN  msg_win;
  word i, ax;
  unsigned char buff[100];

  BOOL DReady;
  AnsiString TestInfo;

  CANIO->pCANQueryMsg(port, (int *)&DReady, (unsigned char *)(&msg_win));

         //  Приведение ID от вида PCL841 к общему виду.
  rec_msg->id = msg_win.IDhigh << 3 | msg_win.IDlow;
  rec_msg->id <<= 5+16 ;
  rec_msg->cfg.dlen =  msg_win.dlc & 0x0f;
  //22.04.03 11:39rec_msg->cfg.dir  =  ((msg_win.RTR & 0x10) >> 4) ^ 0x01;
  for ( i = 0 ; i < 8 ; i++ ) rec_msg->data[i] = msg_win.Data[i];

  return (int)DReady;
}
