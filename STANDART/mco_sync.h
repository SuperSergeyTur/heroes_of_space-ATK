#ifndef  _MCO_SYNC_H
   #define  _MCO_SYNC_H

void SYNC_Init( void );
byte SYNC_check_msg( void );
byte SYNC_msg( void );

#ifdef _CANOPEN_INCLUDE

TTimer Timer_SYNC_msg;
byte  mco_sync_flag;

#else

extern TTimer Timer_SYNC_msg;
extern byte  mco_sync_flag;

#endif

#endif
