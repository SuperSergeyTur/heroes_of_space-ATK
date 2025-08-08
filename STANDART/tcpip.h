#ifndef  _TCPIP_H
  #define  _TCPIP_H

#define  MB_BUFFER		64


 /*
struct  Mb_net
{
  byte In_Func;
  byte In_b[MB_BUFFER];
  byte Out_Func;
  byte Out_b[MB_BUFFER];
} ;
 */

void Init_TCPIP( void ) ;
void Work_TCPIP( void ) ;
//void TCPIP_driver( void ) ;
typedef union 
{
  struct{    
  word n[2];
  }w;
  struct{
    byte n[4];
  }b;
  
} Word_Byte;

#ifdef  _NET_INCLUDE

   word flag_newdata ;
   Tmodbus_packet rmb, smb ;
   word buf_in, buf_out ;   //   После отладки удалить
   word inet ;
   word tcpip1, tcpip2, tcpip3 ;
#else

  extern word flag_newdata ;
  extern modbus_packet, rmb, smb ;
  extern word buf_in, buf_out ;   //   После отладки удалить
  extern word tcpip1, tcpip2, tcpip3 ;
  extern word inet ;

#endif

#endif //  _TCPIP_H

