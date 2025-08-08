#include "mco_nmt.h"
#include "mco_dict.h"

/*
lword  Timer_NMT_LG;
lword  Timer_NMT_HBp;
TStack  Time_NMT_HB;
TStack  HeartbeatCfg;

//extern TUst _r;
extern TMCO_ust _mr;
extern byte mco_state;
*/
/*-----------------09.09.2011 14:10-----------------
 * »нициализаци€  NMT-сервисов
 * --------------------------------------------------*/
void NMT_Init( void )
{
//   StackCreate( &HeartbeatCfg );
//   StackPush( &HeartbeatCfg, _mr.TimeConsHB );
//   StackCreate( &Time_NMT_HB );
//   StackPush( &Time_NMT_HB, Timer1 );
   ArrayInit( &HeartbeatCfg );
   ArrayPush( &HeartbeatCfg, mco_ust.TimeConsHB );
   ArrayInit( &Time_NMT_HB );
   ArrayPush( &Time_NMT_HB, Timer1_fSec );
   NMT_Bootup( );
   Timer_NMT_HBp = Timer1_fSec;
}

/*-----------------09.09.2011 14:07-----------------
 * Module Control Services
 * возвращает cmd - команду перехода узла в другое
 * состо€ние
 * --------------------------------------------------*/
byte NMT_mc_service( TNMT_Service *msg )
{
   byte cmd;

if ( msg->data.d[1] == _r.can[0].addr )
{

   switch ( msg->data.d[0] )
   {
	case NMTMSG_OP :
		   cmd = MCO_CMD_START ;
		   mco_state = MCO_STS_OPER ;
		break;
	case NMTMSG_STOP :
		   cmd = MCO_CMD_STOP ;
		   mco_state = MCO_STS_STOPPED;
		break;
	case NMTMSG_PREOP :
		   cmd = MCO_CMD_PREOP ;
		   mco_state = MCO_STS_PREOP ;
		break;
	case NMTMSG_RESETAPP :
		   cmd = MCO_CMD_RESETAPP ;
		   MCO_Init(0);
		break;
	case NMTMSG_RESETCOM :
		   cmd = MCO_CMD_RESETCOM ;
		   MCO_Init(0);
		break;
	default:
		cmd = 0;
		break;
   }
}
   return cmd;
}

/*-----------------09.09.2011 14:12-----------------
 * Error Control Service - Node Guarding Protocol
 * --------------------------------------------------*/
byte NMT_lg_service( TNMT_Service *msg, byte state )
{
  static byte t = 0;
  TTimer time_lifeguard;

  msg->data._.cmd._.t  = t;
  if ( t == 1 )		t = 0;
  else              t = 1;
  msg->data._.cmd._.s  = state;

  time_lifeguard = _MkSec((lword)mco_ust.GuardTime * mco_ust.LifeTimeFactor);
  if ( time_lifeguard == 0 )
	return 2;  // не поддерживаетс€
  else
    if ( (timer1 - Timer_NMT_LG) > time_lifeguard )
    {
	   Timer_NMT_LG = timer1;
//	   EMCY_SetError(_EMCY_Monitor_hberr);
	   return 0;
    }
    else
    {
	   Timer_NMT_LG = timer1;
	   return 1;
    }
}

/*-----------------09.09.2011 14:12-----------------
 * Error Control Service - Heartbeat Protocol
 * --------------------------------------------------*/
byte NMT_hb_service( byte id, byte *state )
{
  TTimer time_heartbeat, timer;
  TConsHbT  conf;
  lword num;

  *state = 0; // заглушка
//≈сли тактирование не поддерживаетс€
  if ( HeartbeatCfg.count == 0 )
    	return 2;
  num = ArrayFindNumMask( &HeartbeatCfg , id, 0x0F00 );
  if ( num == 0 )
	   return 1;

// надо как-то обработать состо€ние генератора...

  ArrayReadValue( &HeartbeatCfg, num, &conf.all );
  ArrayReadValue( &Time_NMT_HB, num, &timer );

  time_heartbeat = _fSec(0.001) * conf._.heartbeat ;
  if ( time_heartbeat == 0 )
	return 1;        // тактирование не поддерживаетс€
  else
    if ( (Timer1_fSec - timer) > time_heartbeat )
    {
	   ArrayWriteValue( &Time_NMT_HB, num, Timer1_fSec ); // превышено врем€ ожидани€ тактировани€
//	   EMCY_SetError(_EMCY_Monitor_hberr);
	   return 0;
    }
    else
    {
       ArrayWriteValue( &Time_NMT_HB, num, Timer1_fSec );
	   return 1;
    }
}

/*-----------------09.09.2011 14:44-----------------
 * ѕроверка времени дл€ Heartbeat Protocol
 * --------------------------------------------------*/
byte NMT_check_heartbeat( void )
{
  TConsHbT  conf;
  TTimer timer, time_heartbeat;
  byte i, ret;

// ≈сли тактирование не поддерживаетс€
   if ( HeartbeatCfg.count == 0 )
    	return 0;
   ret = 0;

   for ( i = 1; i <= HeartbeatCfg.count; i++ )
   {
     ArrayReadValue( &HeartbeatCfg, i, &conf.all );
     ArrayReadValue( &Time_NMT_HB, i, &timer );

     time_heartbeat = _fSec( 0.001) *conf._.heartbeat ;
     if ( time_heartbeat != 0 )
       if ( (Timer1_fSec - timer) > time_heartbeat )
       {
	      ArrayWriteValue( &Time_NMT_HB, i, Timer1_fSec ); // превышено врем€ ожидани€ тактировани€
//	   EMCY_SetError(_EMCY_Monitor_hberr);
	      ret++;
       }
       else
       {
           ArrayWriteValue( &Time_NMT_HB, i, Timer1_fSec );
       }
   }
   return ret;
}

/*-----------------09.09.2011 14:44-----------------
 * ѕроверка времени дл€ Node Guarding Protocol
 * --------------------------------------------------*/
byte NMT_check_lifeguard( void )
{
  TTimer time_lifeguard;

  time_lifeguard = _MkSec((lword)mco_ust.GuardTime * mco_ust.LifeTimeFactor);
  if ( time_lifeguard == 0 )
	return 2;  // не поддерживаетс€
  if ( (timer1 - Timer_NMT_LG) > time_lifeguard )
  {
	  Timer_NMT_LG = timer1;
	  return 0;
  }
  Timer_NMT_LG = timer1;
  return 1;
}

void NMT_HB_Producer( byte state )
{
   TNMT_Service nmt_msg;
   TCAN_Transfer Transfer;
   TTimer temp_timer;

   if ( mco_ust.TimeProdHB != 0 )
   {
	  temp_timer = (_fSec( 0.001) * (mco_ust.TimeProdHB - 10));
      if ( ((w)(Timer1_fSec - Timer_NMT_HBp)) >= temp_timer )
      {
		 Transfer.can_number = 0;
         Transfer.mailbox_number = MB_NMT_TX;
	     nmt_msg.data.d[0] = state;
#ifdef _Union_FR
	     Transfer.data_low_reg = ((lword)nmt_msg.data.d[0]) << 24;
#else
	     Transfer.data_low_reg = (lword)nmt_msg.data.d[0];
#endif
	     Transfer.size = 1 ;
	     Transfer.identifier = can_setting(0).addr + 0x700;
	     CAN_SendMsg( &Transfer );
		 Timer_NMT_HBp = Timer1_fSec;
      }
   }
}


void NMT_Bootup( void )
{
   TCAN_Transfer Transfer;

   Transfer.data_low_reg  = 0;
   Transfer.data_high_reg = 0;
   Transfer.size = 1 ;
   Transfer.mailbox_number = MB_NMT_TX;
   Transfer.identifier = (_COBID_NMTERR << 7) + can_setting(0).addr;
   Transfer.can_number = 0;

   CAN_SendMsg(&Transfer);
}

