#include "mco_task.h"
#include "mco_pdo.h"

/*
TMCO_ust _mr;
byte mco_state;
byte flag_initmap;

extern TMCO_ust _mco;
extern byte can_irq_flag;
extern TCAN_Transfer cantransfer;
extern void SDO_Server( TMCO_msg *msg );
extern TPDO_Parameter	TPDO[];
extern TPDO_Parameter	RPDO[];
*/

void MCO_Init( byte port )
{   

   mco_ust.DeviceType     = _OD_DEVICE_TYPE;
   mco_ust.VendorID       = _OD_VENDOR_ID;
   mco_ust.ProductCode    = _OD_PRODUCT_CODE;
   mco_ust.SyncObj.all    = 0x00000080;
   mco_ust.TimeCom        = 0;
   mco_ust.GuardTime      = 0;
   mco_ust.LifeTimeFactor = 0;
   mco_ust.TimeConsHB     = (0x7F<<16)+0; // адрес мастера NMT = 0x7F
   mco_ust.TimeProdHB     = 0;
   mco_ust.EmcyID.all     = can_setting(port).addr;
   mco_ust.InhibitTime    = 0;

   mco_vkl = can_setting(port).config._.mcovkl;
   mco_state = MCO_STS_BOOTUP ;
   flag_sdo.all = 0;
   flag_initmap = 0;
   flag_set_rpdo = 0;
   can_irq_flag = 0;
//   SetDefaultSettings( &_mr, &_mc );
   MCO_Dictionary_init();
   if ( CAN_Init(port) == 1 )
   {
	// широковещательные сообщения с Node-ID=0
   	  SetRxMailbox( port, 0, MB_BROADCAST );
	// сообщения NMT сервиса
      SetRxMailbox( port, ((word)_COBID_NMTERR << 7), MB_NMT_RX );
      SetTxMailbox( port, (word)_r.can[0].addr, MB_NMT_TX );
	// SDO-сообщения
      SetRxMailbox( port, (word)_r.can[0].addr, MB_SDO_RX );
      SetTxMailbox( port, (word)_r.can[0].addr, MB_SDO_TX );
	// PDO-сообщения
//      SetRxMailbox( port, (word)_r.can[0].addr, MB_PDO_RX );
//      SetRxMailbox( port, ((word)_COBID_PDO << 7), MB_PDO21_RX );
//      SetRxMailbox( port, ((word)_COBID_PDO << 7), MB_PDO22_RX );
//      SetRxMailbox( port, ((word)_COBID_PDO << 7), MB_PDO23_RX );
      SetTxMailbox( port, (word)_r.can[0].addr, MB_PDO_TX );
      SetTxMailbox( port, (word)_r.can[0].addr, MB_PDO21_TX );
      SetTxMailbox( port, (word)_r.can[0].addr, MB_PDO22_TX );
      SetTxMailbox( port, (word)_r.can[0].addr, MB_PDO23_TX );

      NMT_Init();
	  mco_state = MCO_STS_PREOP ;
	  PDO_Init();
//	  if () SYNC_Init();
   }
		Timer_mco_send = Timer1_fSec;
}

//void MCO_Client( TCAN_Transfer *pTransfer )
//{



//}


void MCO_Server( TCAN_Transfer *pTransfer )
{
word id_cmd, id_node;
byte res, state, i;
TNMT_Service nmt_msg;
TMCO_msg   mco_msg;

	if ( can_irq_flag != 0 )
	{

      id_cmd   = ( pTransfer->identifier & 0x780) >> 7 ;
      id_node  = ( pTransfer->identifier & 0x07F) ;
      switch ( id_cmd )
      {
      	 case _COBID_NMT :
			if ( pTransfer->size == 2 )
			{
#ifdef _Union_FR
			   nmt_msg.data.d[0] = (byte)((pTransfer->data_low_reg & 0xFF000000 ) >> 24);
			   nmt_msg.data.d[1] = (byte)((pTransfer->data_low_reg & 0x00FF0000 ) >> 16);
#else
			   nmt_msg.data.d[0] = (byte)(pTransfer->data_low_reg & 0x000000FF );
			   nmt_msg.data.d[1] = (byte)((pTransfer->data_low_reg & 0x0000FF00 ) >> 8);
#endif
			   res = NMT_mc_service( &nmt_msg );
			}
			break;
		case _COBID_SYNC :
			SYNC_msg();
			break;
		case _COBID_TIMESTAMP :
//          Сейчас никак не обрабатываем
			break;
//		case _COBID_EMCY :
//          Сейчас никак не обрабатываем
//			break;
		case _COBID_PDO1TX :
		case _COBID_PDO2TX :
		case _COBID_PDO3TX :
		case _COBID_PDO4TX :
			if ( mco_state == MCO_STS_OPER )
			{
      			id_node  =  pTransfer->identifier ;
				for ( i = 0; i < 4; i++ )
				{
				   if ( id_node == (TPDO[i].COBID & 0x000007FF) )
				   {
			   			if ( ( TPDO[i].COBID & 0x80000000 ) == 0 )
						{
							pTransfer->size = PDO_Read( 0, &mco_msg);
							pTransfer->data_low_reg  = mco_msg._.lo;
							pTransfer->data_high_reg = mco_msg._.hi;
							pTransfer->identifier = id_node;
							pTransfer->mailbox_number = MB_PDO_TX;
		    				CAN_SendMsg( pTransfer );
							return ;
						}
				   }
				}
			}
			break;
		case _COBID_PDO1RX :
		case _COBID_PDO2RX :
		case _COBID_PDO3RX :
		case _COBID_PDO4RX :
			if ( mco_state == MCO_STS_OPER )
			{
			   	mco_msg._.lo = pTransfer->data_low_reg;
			   	mco_msg._.hi = pTransfer->data_high_reg;
      			id_node  =  pTransfer->identifier;
				for ( i = 0; i < 4; i++ )
				{
				   if ( id_node == (RPDO[i].COBID & 0x000007FF) )
				   {
			   			if ( ( RPDO[i].COBID & 0x80000000 ) == 0 ) PDO_Write( i, &mco_msg);
						return;
				   }
				}
			}
			break;
		case _COBID_SDOTX :
		case _COBID_SDORX :
			if ( mco_state != MCO_STS_STOPPED )
			{
				mco_msg._.lo = pTransfer->data_low_reg;
				mco_msg._.hi = pTransfer->data_high_reg;
				SDO_Server( &mco_msg );
				pTransfer->data_low_reg  = mco_msg._.lo;
				pTransfer->data_high_reg = mco_msg._.hi;
				pTransfer->identifier = 0x580 + can_setting(pTransfer->can_number).addr;
				pTransfer->size = 8 ;
		    	pTransfer->mailbox_number = MB_SDO_TX;
				pTransfer->can_number = 0;
		    	CAN_SendMsg( pTransfer );
			}
			break;
		case _COBID_PDO :
			if ( mco_state == MCO_STS_OPER )
			{
			   	mco_msg._.lo = pTransfer->data_low_reg;
			   	mco_msg._.hi = pTransfer->data_high_reg;
      			id_node  =  pTransfer->identifier;
				for ( i = 0; i < 4; i++ )
				{
					if ( id_node == ( RPDO[i].COBID & 0x000007FF ) )
					{

			   			if ( ( RPDO[i].COBID & 0x80000000 ) == 0 )
						{
							PDO_Write( i, &mco_msg);
						}
						return;
					}
					if ( id_node == ( TPDO[i].COBID & 0x000007FF ) )
					{
			   			if ( ( TPDO[i].COBID & 0x80000000 ) == 0 )
						{
							pTransfer->size = PDO_Read( i, &mco_msg);
							pTransfer->data_low_reg  = mco_msg._.lo;
							pTransfer->data_high_reg = mco_msg._.hi;
							pTransfer->identifier = id_node;
							pTransfer->mailbox_number = MB_PDO_TX;
		    				CAN_SendMsg( pTransfer );
							return;
						}
					}
				}
			}
			break;
		case _COBID_NMTERR :
			res = NMT_hb_service( id_node, &state );
            if ( res == 0 ) // Время ожидания HB посылки просрочено
			{
	            EMCY_Send( _EMCY_Monitor_hberr );
			}
			else
			  if ( res == 2 ) // Режим Heartbeat не поддерживается
			  {
			     res = NMT_lg_service( &nmt_msg, mco_state ) ;
				 if ( res == 0 ) // Время ожидания LG посылки просрочено
				 {
	                 EMCY_Send( _EMCY_Monitor_hberr );
				 }
				 else
				   if ( res == 1 ) // Отвечаем на посылку
				   {
					  pTransfer->mailbox_number = MB_NMT_TX;
				   	  pTransfer->data_low_reg = (lword)nmt_msg.data.d[0] + ((lword)nmt_msg.data.d[1] << 8 );
					  pTransfer->size = 2;
//					  Идентификатор оставляем тот же
					  CAN_SendMsg( pTransfer );
				   }

			  }
			break;
      }
   }
}


void MCO_Background( byte port )
{
  byte res;
  byte i;
  TCAN_Transfer Transfer;
  TMCO_msg   mco_msg;

   Transfer.can_number = port;
 #ifndef _MCO_CAN_IRQ
   if ( can_irq_flag != 0 )
   {
	  for ( i = 0 ; i < 8; i++ )
	  {
	     if ( (can_irq_flag & (1 << i)) == (1 << i))
	     {
		    pCANTransfer = &cantransfer[i];
		    MCO_Server( pCANTransfer );
	  	    can_irq_flag &= ~(1<< i);
	     }
	  }
   }
#endif
   if ( flag_set_rpdo != 0 )
   {
	  if (( flag_set_rpdo == 1 ) && (( RPDO[0].COBID & 0x80000000 ) == 0 ))  SetRxMailbox( port, (word)(RPDO[0].COBID & 0x000007FF), MB_PDO_RX );
	  if (( flag_set_rpdo == 2 ) && (( RPDO[1].COBID & 0x80000000 ) == 0 ))  SetRxMailbox( port, (word)(RPDO[1].COBID & 0x000007FF), MB_PDO21_RX );
	  if (( flag_set_rpdo == 3 ) && (( RPDO[2].COBID & 0x80000000 ) == 0 ))  SetRxMailbox( port, (word)(RPDO[2].COBID & 0x000007FF), MB_PDO22_RX );
	  if (( flag_set_rpdo == 4 ) && (( RPDO[3].COBID & 0x80000000 ) == 0 ))  SetRxMailbox( port, (word)(RPDO[3].COBID & 0x000007FF), MB_PDO23_RX );

	  flag_set_rpdo = 0;
   }


   while ( flag_initmap != 0 )
   {
	  switch ( flag_initmap )
	  {
	  	case 0x01 :
                  PDO_InitMapping( 1, 0);
                  flag_initmap &= 0xFE;
                  break;
	  	case 0x02 :
                  PDO_InitMapping( 1, 1);
                  flag_initmap &= 0xFD;
                  break;
	  	case 0x04 :
                  PDO_InitMapping( 1, 2);
                  flag_initmap &= 0xFB;
                  break;
	  	case 0x08 :
                  PDO_InitMapping( 1, 3);
                  flag_initmap &= 0xF7;
                  break;
	  	case 0x10 :
                  PDO_InitMapping( 0, 0);
                  flag_initmap &= 0xEF;
                  break;
	  	case 0x20 :
                  PDO_InitMapping( 0, 1);
                  flag_initmap &= 0xDF;
                  break;
	  	case 0x40 :
                  PDO_InitMapping( 0, 2);
                  flag_initmap &= 0xBF;
                  break;
	  	case 0x80 :
                  PDO_InitMapping( 0, 3);
                  flag_initmap &= 0x7F;
                  break;
	  }
   }
// PDO TX посылки
   if ( mco_state == MCO_STS_OPER )
   {
	 if ((w)(Timer1_fSec - Timer_mco_send) >= _r.time_scan  )
	 {
		Timer_mco_send = Timer1_fSec;
		for ( i = 0; i < 4; i++ )
   		{
   			if ( ( TPDO[i].COBID & 0x80000000 ) == 0 )
   			{
   				Transfer.size = PDO_Read( i, &mco_msg);
   				Transfer.data_low_reg  = mco_msg._.lo;
   				Transfer.data_high_reg = mco_msg._.hi;
   				Transfer.identifier = TPDO[i].COBID & 0x000007FF;
   				switch (i)
				{
				  case 0:	Transfer.mailbox_number = MB_PDO_TX; break;
				  case 1:	Transfer.mailbox_number = MB_PDO21_TX; break;
				  case 2:	Transfer.mailbox_number = MB_PDO22_TX; break;
				  case 3:	Transfer.mailbox_number = MB_PDO23_TX; break;
				}
   				CAN_SendMsg( &Transfer );
   			}
   		}
	 }
   }

// Генератор NMT-сервиса
   NMT_HB_Producer( mco_state );

// Проверка NMT сервиса (таймеров)
   res = NMT_check_heartbeat();
   if ( res == 0 )
   {
      EMCY_Send( _EMCY_Monitor_hberr );
   }
   else
   {
	  if ( res == 2 )
		  if ( !NMT_check_lifeguard() )
		  {
              EMCY_Send( _EMCY_Monitor_hberr );
		  }
   }
   mco_test(port);
}


