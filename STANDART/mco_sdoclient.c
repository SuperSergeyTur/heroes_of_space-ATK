#include "mco_sdo.h"

/*-----------------10.08.2011 12:41-----------------
 *  Инициализация SDO-загрузки  -  клиент
 * --------------------------------------------------*/
//MCO_msg SDO_InitClient_Request_Download( lword mux, byte *data, byte num )
//{
//  CAN_msg  message;
//  ServiceInit  serv;
//  byte i;

//  message.mux[0] = (byte)(mux & 0x00FF0000 >> 16);
//  message.mux[1] = (byte)(mux & 0x0000FF00 >> 8);
//  message.mux[2] = (byte)(mux & 0x000000FF);
//  serv.all = 0;
//  if ( num != 0 )
//  {
//    serv._.e = 1;
//	if ( num > 4 )
//	{
//       serv._.s = 0;
//	   serv._.n = 0;
//	}
//	else
//	{
//       serv._.s = 1;
//	   serv._.n = 4-num;
//	   for ( i=0; i < num; i++ )
//	   {
//          message.data[i] = data[i];
//	   }
//	}
//  }
//  else
//  {
//	serv._.e = 0;
//	serv._.s = 1;
//    serv._.n = 0;
//  }
//  serv._.cs = 1;
//  message.service = serv.all;

//  return message;
//}

//lword






