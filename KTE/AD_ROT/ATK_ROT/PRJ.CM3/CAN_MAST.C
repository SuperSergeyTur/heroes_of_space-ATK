//   Для разрешения регистровых static переменых,
// чего в TurboC нельзя, а в 196-м можно.
#define   _can_MCS_196
#define   _CAN_SHARED  //  CAN-используется и другими программами.
//--------------------------

#include "can_mast.h"
//-------------

//#include "can_drv.c"
#include "mastdrv.c"
//#include "slavedrv.c"

//   Инициализация таблиц переменных в ОЗУ из константных
// таблиц в ПЗУ.
void init_var_mtab ( void )
{
  word ax , bx ;

  for ( bx = 0 ; bx < size_tab_ab ; bx++ )
  {       //  Инициализация карточки абонента.
    *(tab_ab[bx].ab) = *(tab_ab[bx].c_ab) ;
    //  Инициализация его таблицы переменных.
    for ( ax = 0 ; ax < tab_ab[bx].ab->size_var_tab ; ax++ )
      tab_ab[bx].ab->var_tab[ax] = tab_ab[bx].c_t_ab[ax] ;

    //  Переинициализация рабочего порта.
    //if ( (sw)MASTER_PORT != ( -1 ) ) tab_ab[bx].ab->port = MASTER_PORT ;
  }

  abDev1.ab_addr = _r.AddrDevice1;

  return ;
}
//------------------------------

word can_master ( byte port , byte code )
{
  static byte tst_scan, trig_scan;
  static byte tst_scan2, trig_scan2;
  static word time_scan ;
  static word time_scan2 ;
  //static byte mark ;
  static byte mark2 ;
  register word ax, bx ;

 // static word Mtime_connect;
  static byte Mtrigg_connect;

  do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
  // Склеиваем два средних байта из 4 байт полного времени в
  // одно слово.
  ax = ( ax << 8 ) | ( bx >> 8 ) ;

  //  Стартовая инициализация.
  if ( code == 0 )
  {

    init_var_mtab();
    //    can_logic( _INIT_CAN_OBJ );

  reinit:
    if  (port == 1)
    {
      //tst1 = 2;
      //Err_Dev1  = 0;
      //Time_Dev1 = Timer1_Ovr;

      Tst_Read_Dev1 = 0, Tst_Write_Dev1 = 0 ;
      tst_scan = 0 , time_scan = ax, trig_scan = 0 ;
      Opros_time = 0 ;
      SkorPDF = 0 ;
      canr.StatReg2.all = 0 ;
      Mbi_canConnect = 1 ;
      if ( Mbi_canConnect == 1 ) Mtrigg_connect = 1 ;// при отсутствии связи и не
      else                       Mtrigg_connect = 0 ;// создавать видимость ее появления.
    }
    else if (port==0)
    {                                   // При тесте порта не переинициализируем всю таблицу , достаточно только адреса :
      //vmz 122014
      Tst_Read_Dev21 = 0;//, Tst_Write_Dev21 = 0 ;
      //vmz 122014
      tst_scan2 = 0 , time_scan2 = ax, trig_scan2 = 0 ;
      /*
      //vmz 09122014
      Mbi_canConnect2 = 1 ;
      if ( Mbi_canConnect2 == 1 ) Mtrigg_connect2 = 1 ;// при отсутствии связи и не
      else                        Mtrigg_connect2 = 0 ;// создавать видимость ее появления.
      */
      count_CAN2_no = 0;//счетчик "неответов" CAN-платы
    }

    return 0 ;
  }

  // Проверяем наличие связи со вторым КТЭ
  // Признак наличия связи приходит как меандр 0.5сек.
 /* if ( Mtrigg_connect != Mbi_canConnect )
  {
    if ( Mtrigg_connect == 0 ) Mtrigg_connect = 1 ;
    else                       Mtrigg_connect = 0 ;
    Mtime_connect = Timer1_Ovr ;
    mClr_ServiceMsg2( _Srv2_NoLinkCAN ) ;
    flgO._.CAN1_ok = 1 ;
  }
  if ( (u)((w)(Timer1_Ovr-Mtime_connect)) > _r.T_Connect_cfg )
  {
    canr.StatReg2.all = 0 ;
    Mbi_canConnect = 1 ;
    if ( Mbi_canConnect == 1 ) Mtrigg_connect = 1 ;// при отсутствии связи и не
    else                       Mtrigg_connect = 0 ;// создавать видимость ее появления.
    mSet_ServiceMsg2( _Srv2_NoLinkCAN ) ;
    flgO._.CAN1_ok = 0 ;
  }
 */
  //-----------

  // Тест порта.
  if ( can_test( port ) != 0 )  goto reinit ;//vmz 17122014 см. reinit - разделил по портам,
  //иначе вместо одного переинициализировались оба
  else
  {      //  Рассортировка принятых фреймов:
    // ответы мастеру от абонентов/запросы мастеру от других мастеров.
    Receive_Monitor( port ) ;// не вносить внутрь do{...}while();
    do
    {
      canSlaveDrive( port ) ;
      //-----------
      switch ( port )
      {
      case _CAN1_Port : // Связь с AP1

         break;
      case _CAN0_Port :

      /*  if ( (tst_scan2 == 0) || ((u)((w)(ax-time_scan2)) > _r.time_scan) )
        {*/
          // первый вход после такта - фиксируем время выхода на шину.
          if( tst_scan2 != 0 ) time_scan2 = ax;  //14.03.05 14:04
          tst_scan2 = 0;  //14.03.05 14:04

          // обнулять в начале каждого оборота, а не один раз при входе в функцию.
          mark2 = 0;

          Tst_Read_Dev21  = master_read( "\x0\xff", &abDev21 , mark2++ ) ;

          //vmz 12122014
          if (Tst_Read_Dev21 == 0)
          {
            mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
            priznak_CAN2_no = 0 ;
          }
          else
          {
            if ( Tst_Read_Dev21 != _NoErr_TimeOut && Tst_Read_Dev21 != _NoErr_Continue )
            {
              mSet_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
              if (priznak_CAN2_no==0) count_CAN2_no++;
              priznak_CAN2_no = 1 ;
            }
          }


          // опрос этой пачки завершен - взводим триггер.
          if ( Tst_Read_Dev21 != _NoErr_TimeOut && Tst_Read_Dev21 != _NoErr_Continue )
          {
            tst_scan2 = 1;
          }

        //}

        break;

      }
        //--------------
      } while ( Receive_Monitor ( port ) == 1 ) ; //  чтобы выбрать все из буфера приема, если там 'запарка'.
      //-------------------
      /*
      //  Вычисление времени цикла опроса: если завершился опрос
      // последнего абонента, ...  ловим перепад 'tst_scan'
      if ( tst_scan == 1 )
      {      // цикл закончился.
      if ( trig_scan == 0 )
      {
      Opros_time = (u)((w)(ax - time_scan)) ;
      trig_scan = 1 ;
    }
    }
    else trig_scan = 0 ;  */
      //-------
    }
    //can_logic( _WORK_CAN_OBJ );
    return 0 ;
  }


  /***********************************************************
  Функция - обработчик CAN-состояния:
  вставляется в main после can_master(port, 1);
  ***********************************************************/
  /*
  void can_logic( byte oper )
  {
  static word time_master, time_slave;
  static word time_sts_connect, trigg_sts_connect;

  //mClr_ServiceMsg ( _Srv_CAN_Slave  ) ; //12.09.2008 14:41
  //mClr_ServiceMsg ( _Srv_CAN_Master ) ; //12.09.2008 14:41
  //mClr_ServiceMsg ( _Srv_CAN_Master_QK1 ) ;
  if ( (w)(Timer1_Ovr-time_master) >= _r.T_mConnect_cfg )
  {
  //  if ( CfgM[1]._.Connect == 1 ) CfgM[1]._.Connect = 0;
  // else                          CfgM[1]._.Connect = 1;
  time_master = Timer1_Ovr ;
}

  if ( trigg_sts_connect != StsM[1]._.Connect )
  {
  if ( trigg_sts_connect == 0 )  trigg_sts_connect = 1 ;
  else                           trigg_sts_connect = 0 ;
  time_sts_connect = Timer1_Ovr ;
  DataM[1]._.connect = 1 ;
}
  if ( (w)(Timer1_Ovr-time_sts_connect) > _r.T_mConnect_sts )
  DataM[1]._.connect = 0 ;
  if ( (DataM[1]._.connect == 0) || (StsM[1]._.Ready == 0) )
  DataM[1]._.link = 0;
  else
  DataM[1]._.link = 1;

  switch ( oper )
  {
case _INIT_CAN_OBJ:
  time_master = Timer1_Ovr ;
  time_slave = Timer1_Ovr ;
  time_sts_connect = Timer1_Ovr ;
  trigg_sts_connect = 0 ;
  //    CfgM[0].all = 0 ;
  //    CfgM[1].all = 0 ;
  StsM[0].all = 0 ;
  StsM[1].all = 0 ;
  DataM[0].all = 0 ;
  DataM[1].all = 0 ;
  sMaster.all = 0 ;
  sMaster._.bit_master = 1 ;
  break;
case _WORK_CAN_OBJ:
  if ( (sMaster._.bit_master == 0) && (canr.Data._.Connect == 0) )
  {
  //canr.Id_zad = 0 ; //12.09.2008 14:41
  // Для сброса задания на РТ при переходе с Мастера на Ведомого,
  // при отсутствии Мастера вообще.
  // иначе в OuRegS_dop_kod остается последнее значение записанное
  // при работе Мастером
  //if ( canr.CfgReg._.Id_zad == 0 )  OuRegS_dop_kod = 0 ; //12.09.2008 14:41
}
  //          sMaster._.bit_master = 0 ;
  if ( canr.Data._.Connect == 1 )
  {
  sMaster._.bit_master = 0 ;
  //mSet_ServiceMsg(_Srv_CAN_Slave) ; //12.09.2008 14:41
  time_slave = Timer1_Ovr ;
}
  else
  {
  if ( sMaster._.bit_master == 0 )
  {
  if ( (Timer1_Ovr - time_slave) >= _Sec(0.4) )
  {
  sMaster._.bit_master = 1 ;
  //mSet_ServiceMsg(_Srv_CAN_Master); //12.09.2008 14:41
  time_slave = Timer1_Ovr ;
}
  else
  {
  sMaster._.bit_master = 0 ;
  //mSet_ServiceMsg(_Srv_CAN_Slave) ; //12.09.2008 14:41
}
}
  else
  {
  sMaster._.bit_master = 1 ;
  //mSet_ServiceMsg(_Srv_CAN_Master); //12.09.2008 14:41
  time_slave = Timer1_Ovr ;
  if ( DataM[1]._.link == 1 )
  sMaster._.free_master = 1 ;
  else
  sMaster._.free_master = 0 ;
}
}

  // 2-х Двигательный режим (точнее 4-ре без Сети )
  /*if ( trig_Regim == 3 )
  {
  if ((( can_setting( _CAN0_Port).addr == 0x01 ) && bi_canP1rab == 1 ) ||
  (( can_setting( _CAN0_Port).addr == 0x02 ) && bi_canP2rab == 1 ))
  {
  sMaster._.bit_master = 1 ;
  //mSet_ServiceMsg(_Srv_CAN_Master); //12.09.2008 14:41
  //mClr_ServiceMsg(_Srv_CAN_Slave);  //12.09.2008 14:41
}
  else
  {
  sMaster._.bit_master = 0 ;
  //mSet_ServiceMsg(_Srv_CAN_Slave);  //12.09.2008 14:41
  //mClr_ServiceMsg(_Srv_CAN_Master); //12.09.2008 14:41
}
}
  if ( sMaster._.bit_master == 0 ) StsM[1]._.StateQK = 0 ; */

  //      break;
  //}
  //return ;
  //}


