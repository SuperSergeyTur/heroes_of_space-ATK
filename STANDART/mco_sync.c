#include "mco_dict.h"
/*
TTimer Timer_SYNC_msg;
byte  mco_sync_flag = 0;

extern TMCO_ust  _mr;
  */
void SYNC_Init( void )
{
// Взводим таймер для генератора синхросообщений
   Timer_SYNC_msg = Timer1;
   mco_sync_flag = 0;
}

byte SYNC_check_msg( void )
{
   if ( mco_ust.SyncObj._.bit30 == 1 )
   {
	   if ( (Timer1 - Timer_SYNC_msg) > _MkSec( mco_ust.TimeCom ) )
	   {
		  return 1;
	   }
   }
   return 0;
}

byte SYNC_msg( void )
{
   Timer_SYNC_msg = Timer1;
   mco_sync_flag = 1;
   return 0;
}


