#ifndef  _RS_H
  #define  _RS_H

void Init_RS( void ) ;
word Work_RS( byte flag ) ;

#ifdef _NET_INCLUDE
   word In_RS485, Out_RS485;
//   byte num_rs485_in, num_rs485_out;
   word Timer_Rec1, Timer_Send1, Timer_Rec;
#else
   extern word In_RS485, Out_RS485;
//   extern byte num_rs485_in, num_rs485_out;
   extern word Timer_Rec1, Timer_Send1, Timer_Rec;
#endif

#endif  // _RS_H
