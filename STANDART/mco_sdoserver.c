#include "mco_sdo.h"


//*********************   SDO-загрузка (Запись данных)   ********************************
/*-----------------11.08.2011 12:48-----------------
 * Обработка запроса на инициализацию SDO-загрузки
 * --------------------------------------------------*/
lword  SDO_InitServer_Download( TSDO_msg *msg, lword *num )
{
  byte  i;
  lword err;
  TServInit	srv;
  TSegmentData seg;
  byte data[8];

  if ( flag_sdo._.init_dl == 1 ) // Если уже идет обмен SDO, то выставляем запрет на еще один SDO
  {
	 return _ERR_SDO_data_state;
  }

  flag_sdo._.init_dl = 0;
  // Индекс и подиндекс перекладываем
//  smsg->data.seg.mux.index = rmsg->data.seg.mux.index ;
//  smsg->data.seg.mux.subindex = rmsg->data.seg.mux.subindex ;
//  index = ReversByte( msg->data.seg.mux.index );

  srv.all = msg->all[0];
  if ( srv._.e == 1 ) // укороченый
  {
	 if ( srv._.s == 1 ) // Количество байт = 4-n
		*num = 4 - srv._.n ;
	 else // Неопределенное количество байт -> считаем что 4 байта
		*num = 4 ;
  }
  else                       // обычный
  {
	 if ( srv._.s == 1 ) // Количество байт - в поле data
	 {
		*num = (lword)msg->all[4]         +
		      ((lword)msg->all[5] << 8  ) +
		      ((lword)msg->all[6] << 16 ) +
			  ((lword)msg->all[7] << 24 ) ;
        flag_sdo._.init_dl = 1;  // Взводим флаг инициализации SDO-download
	 }
	 else   // зарезервировано
		*num = 0;
  }
  seg.index = msg->all[1] + ((word)msg->all[2] << 8);
  seg.subindex = msg->all[3];
  data[0] = msg->all[4];
  data[1] = msg->all[5];
  data[2] = msg->all[6];
  data[3] = msg->all[7];
  err = Write_ObjDict( seg.index, seg.subindex, _SDO_type,
					   &data[0], num );
  // Если без ошибок, то отправляем подтверждение инициализации
  srv.all = 0;
  if ( err == 0 )
  {
     srv._.cs = 3 ;
	 msg->all[0] = srv.all;
     for ( i = 4; i < 8; i++ )
        msg->all[i] = 0 ;
  }
  else
  {
	return err ;
  }
  return 0;
}

/*-----------------15.08.2011 16:07-----------------
 * Обработка запроса на загрузку SDO-сегмента
 * --------------------------------------------------*/
lword SDO_LoadServer_Download( TSDO_msg *msg, lword *num, word index, byte subindex )
{
  lword n;
  byte i;
  lword err;
  TServLoad srv;
  byte data[8];

  if ( flag_sdo._.init_dl == 0 ) // Если не было инициализации
  {
	 return _ERR_SDO_data_local;
  }

  srv.all = msg->all[0];

  if ( flag_sdo._.t_bit == srv._.t ) // t-бит не изменился
  {
	 return _ERR_SDO_t_state;
  }

  flag_sdo._.t_bit = srv._.t ;

  n = 7 - srv._.n;

  if ( srv._.c == 1 ) // Последний сегмент
  {
	 if ( *num != n )
	 {
		if ( *num > (n + 7) )
		{
		   return _ERR_SDO_type_data_min;
		}
		return _ERR_SDO_type_data_length;
	 }
	 flag_sdo._.init_dl = 0;
  }
  else                      // Есть еще сегменты
  {
      if ( ( *num < n ) || ( *num < 7 ))
      {
	     return _ERR_SDO_type_data_max;
      }
	  *num = *num - 7 ;
  }
  data[0] = msg->all[4];
  data[1] = msg->all[5];
  data[2] = msg->all[6];
  data[3] = msg->all[7];
  err = Write_ObjDict( index, subindex, _SDO_type, &data[0], num );
  if ( err == 0 )
  {
//     smsg->srv.sl.t = rmsg->srv.sl.t ;
     srv._.cs = 1 ;
	 msg->all[0] = srv.all;
     for ( i = 1; i < 8; i++ )
       msg->all[i] = 0 ;
  }
  else
  {
	return err ;
  }

  return 0;
}
//***************************************************************************************

//*********************   SDO-выгрузка (Чтение данных)   ********************************
/*-----------------16.08.2011 10:11-----------------
 * Обработка запроса на инициализацию SDO-выгрузки
 * --------------------------------------------------*/
lword SDO_InitServer_Upload( TSDO_msg *msg, lword *num )
{
  byte *pByte;
  byte i;
  lword err;
  word index;
  byte subindex;
  TServInit	srv;
  byte data[8];

  if ( flag_sdo._.init_ul == 1 ) // Если уже идет обмен SDO, то выставляем запрет на еще один SDO
  {
	 return _ERR_SDO_data_state;
  }
  flag_sdo._.init_ul = 0;
  // Индекс и подиндекс перекладываем
//  smsg->data.seg.mux.index = rmsg->data.seg.mux.index ;
//  smsg->data.seg.mux.subindex = rmsg->data.seg.mux.subindex ;

  srv.all = 0;
//  index = ReversByte( msg->data.seg.mux.index );
  index = msg->all[1]  + ((msg->all[2]) << 8);
  subindex = msg->all[3];
  err = Read_ObjDict( index, subindex, _SDO_type, &(data[0]), num );

  msg->all[4] = data[3];
  msg->all[5] = data[2];
  msg->all[6] = data[1];
  msg->all[7] = data[0];

  if ( err == 0 )
  {
     srv._.cs = 2 ;
	 if ( *num > 4 ) // если ответ не укладывается в укороченную посылку
	 {
        flag_sdo._.init_ul = 1;
		pByte = (byte*)num ;
		for ( i = 0; i < 4; i++ )
		   msg->all[i+4] = pByte[i] ;
        *num = 0;
		srv._.e = 0;
		srv._.s = 1;
	 }
	 else 			// укороченная посылка
	 {
		srv._.n = 4-(*num);
		srv._.e = 1;
		if ( *num == 4 ) srv._.s = 0;
		else             srv._.s = 1;
	 }
	 msg->all[0] = srv.all;
  }
  else
	return err;

  return 0;
}

/*-----------------16.08.2011 10:11-----------------
 * Обработка запроса на выгрузку SDO-сегмента
 * --------------------------------------------------*/
lword SDO_LoadServer_Upload( TSDO_msg *msg, lword *num, word index, byte subindex )
{
  lword n;
  byte i;
  lword err;
  TServLoad	srv;
  byte data[8];

  if ( flag_sdo._.init_ul == 0 ) // Если не было инициализации
  {
	 return _ERR_SDO_data_local;
  }

  srv.all = msg->all[0];
  if ( flag_sdo._.t_bit == srv._.t ) // t-бит не изменился
  {
	 return _ERR_SDO_t_state;
  }

  flag_sdo._.t_bit = srv._.t ;

  n = 7 - srv._.n;

  if ( srv._.c == 1 ) // Последний сегмент
  {
	 if ( *num != n )
	 {
		if ( *num > (n + 7) )
		{
		   return _ERR_SDO_type_data_min;
		}
		return _ERR_SDO_type_data_length;
	 }
	 flag_sdo._.init_dl = 0;
  }
  else                      // Есть еще сегменты
  {
      if ( ( *num < n ) || ( *num < 7 ))
      {
	     return _ERR_SDO_type_data_max;
      }
	  *num = *num - 7 ;
  }
  err = Read_ObjDict( index, subindex, _SDO_type, &data[0], num );
  if ( err == 0 )
  {
//     smsg->srv.sl.t = rmsg->srv.sl.t ;
     srv._.cs = 1 ;
	 msg->all[0] = srv.all;
     for ( i = 1; i < 7; i++ )
        msg->all[i] = 0 ;
  }
  else
  {
	return err ;
  }

  return 0;
}

//***************************************************************************************

//**************************   Аварийное завершение SDO   *******************************
/*-----------------16.08.2011 12:54-----------------
 * Обработка запроса на аварийное завершение SDO от клиента
 * --------------------------------------------------*/
lword SDO_Alarm_Request( TSDO_msg *rmsg )
{
  lword err;

  err = (lword)rmsg->all[4]        + ((lword)rmsg->all[5] << 8) +
       ((lword)rmsg->all[6] << 16) + ((lword)rmsg->all[7] << 24);
  flag_sdo._.init_dl = 0;
  flag_sdo._.init_ul = 0;
  return err;
}

/*-----------------16.08.2011 12:54-----------------
 * Запрос на аварийное завершение SDO от сервера
 * --------------------------------------------------*/
void SDO_Alarm_Response( lword err, word index, byte subindex, TSDO_msg *smsg )
{

   TServInit	srv;

   srv.all = 0;
   srv._.cs = 4;

   smsg->all[0] = srv.all;
   smsg->all[1] = (byte)(index & 0x00FF );
   smsg->all[2] = (byte)((index & 0xFF00 ) >> 8);
   smsg->all[3] = subindex ;
   smsg->all[4] = (byte)(err & 0x000000FF);
   smsg->all[5] = (byte)((err & 0x0000FF00) >> 8);
   smsg->all[6] = (byte)((err & 0x00FF0000) >> 16);
   smsg->all[7] = (byte)((err & 0xFF000000) >> 24);

   flag_sdo._.init_dl = 0;
   flag_sdo._.init_ul = 0;
   return ;
}
//***************************************************************************************

//**************************   SDO-загрузка (запись) блока  *****************************
//lword SDO_InitServer_Request_BlockDownload( TSDO_msg *msg, lword *mux )
//{
//	return 0;
//}


//***************************************************************************************

/*-----------------11.08.2011 13:33-----------------
 * SDO-сервер
 * Обработка данных приходящих с COB-ID: 581h...67Fh
 * --------------------------------------------------*/
void SDO_Server( TMCO_msg *msg )
{
  static word index;
  static byte subindex;
  TSDO_msg	smsg;
//  TSDO_msg* pSmsg;
  TServInit	srv;
  lword num;
  byte  cs, i;
  lword err;

  for ( i = 0; i < 8; i++ )
  {
     smsg.all[i] = msg->data[i];
  }
  srv.all = smsg.all[0];
  cs = srv._.cs  ;

//  pSmsg = &smsg;
  switch ( cs )
  {
	case 0 :
		err = SDO_LoadServer_Download( &smsg, &num, index, subindex);
		if ( err != 0 )
		{
		   // Обработка ошибки
		   index = smsg.all[1] + ((word)smsg.all[2] << 8 );
		   subindex = smsg.all[3];
		   SDO_Alarm_Response(err, index, subindex, &smsg);
		}
		break;
	case 1 :
		err = SDO_InitServer_Download ( &smsg, &num);
		if ( err != 0 )
		{
		   // Обработка ошибки
		   index = smsg.all[1] + ((word)smsg.all[2] << 8 );
		   subindex = smsg.all[3];
		   SDO_Alarm_Response(err, index, subindex, &smsg);
		}
		break;
	case 2 :
		err = SDO_InitServer_Upload( &smsg, &num );
		if ( err != 0 )
		{
		   // Обработка ошибки
		   index = smsg.all[1] + ((word)smsg.all[2] << 8 );
		   subindex = smsg.all[3];
		   SDO_Alarm_Response(err, index, subindex, &smsg);
		}
		break;
	case 3 :
		err = SDO_LoadServer_Upload( &smsg, &num, index, subindex );
		if ( err != 0 )
		{
		   // Обработка ошибки
		   index = smsg.all[1] + ((word)smsg.all[2] << 8 );
		   subindex = smsg.all[3];
		   SDO_Alarm_Response(err, index, subindex, &smsg);
		}
		break;
	case 4 :
		SDO_Alarm_Request( &smsg );
		break;
	case 5 :
		break;
	case 6 :
		break;
	default:
		SDO_Alarm_Response( err, index, subindex, &smsg);
		break;

  }
  for ( i = 0; i < 8; i++ )
  {
     msg->data[i] = smsg.all[i];
  }

}

