#ifndef  _MB_RTU_H
  #define  _MB_RTU_H

Tmodbus_packet  request, answer;
void MBRTU_Init( void );
word MBRTU_Slave( void );
word MBRTU_Master( void );
void MBRTU_Background( void );


#endif  //  _MB_RTU_H

