          //   Для разрешения регистровых static переменых,
          // чего в TurboC нельзя, а в 196-м можно.
#define   _can_MCS_196
//#define   _CAN_SHARED  //  CAN-используется и другими программами.
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

  abDev21.ab_addr  = _r.AddrDevice2;

  return ;
}
//------------------------------

word can_master ( byte port , byte code )
{
  static byte tst_scan, trig_scan;
  static word time_scan ;
  static byte mark ;

  //vmz 122014
  static byte tst_scan2, trig_scan2;
  //static word time_scan2 ;
  static byte mark2 ;

  register word ax, bx ;

  static word Mtime_connect , Mtime_connect2 ;
  static byte Mtrigg_connect , Mtrigg_connect2 ;

  do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
      // Склеиваем два средних байта из 4 байт полного времени в
    // одно слово.
  ax = ( ax << 8 ) | ( bx >> 8 ) ;

      //  Стартовая инициализация.
  if ( code == 0 )
  {

    init_var_mtab();        // При тесте порта не переинициализируем :
    canr.StatReg4.all = 0 ; // инициализация своего статуса АР1 для передачи в другой ШУ: ШУ1-ШУ2 .

reinit:
    if  (port == 1)
     {
       for (bx = 0; bx < 7; ++bx)
       {
         Tst_Read_Dev[bx] = 0;
       }
      
      Tst_Write_Dev[0] = 0 ;
      Tst_Write_Dev[1] = 0 ;
      
      tst_scan = 0 , time_scan = ax, trig_scan = 0 ;
      Opros_time = 0 ;
      N_rot = 0 ;
      canr.StatReg2.all = 0 ;
      Mbi_canConnect = 1 ;
      if ( Mbi_canConnect == 1 ) Mtrigg_connect = 1 ;// при отсутствии связи и не
      else                       Mtrigg_connect = 0 ;// создавать видимость ее появления.
     }
    else if (port==0)
     {                                   // При тесте порта не переинициализируем всю таблицу , достаточно только адреса :
      abDev21.ab_addr  = _r.AddrDevice2; // Для переключения между Резервом и Рабочим инициализируем Адрес Чужого .
      //---

      Tst_Read_Dev21 = 0, Tst_Write_Dev21 = 0 ;
      tst_scan2 = 0 , time_scan2 = ax, trig_scan2 = 0 ;

      canId_zad = 0 ;
      canr.StatReg3.all = 0 ;
      Mbi_canConnect2 = 1 ;
      if ( Mbi_canConnect2 == 1 ) Mtrigg_connect2 = 1 ;// при отсутствии связи и не
      else                        Mtrigg_connect2 = 0 ;// создавать видимость ее появления.
     }

    return 0 ;
  }

  // Проверяем наличие связи c АР2
  // Признак наличия связи приходит как меандр 0.5сек.
  if ( Mtrigg_connect != Mbi_canConnect )
  {
    if ( Mbi_canConnect == 0 ) Mtrigg_connect = 0 ;
    else                       Mtrigg_connect = 1 ;
    Mtime_connect = Timer1_Ovr ;
    mClr_ServiceMsg2( _Srv2_NoLinkCAN ) ;
    flgO._.CAN1_ok = 1 ;
  }
  if ( (u)((w)(Timer1_Ovr-Mtime_connect)) > _r.T_Connect_cfg )
  {
    N_rot = 0 ;
    canr.StatReg2.all = 0 ;
    //Mbi_canConnect = 1 ;
    if ( Mbi_canConnect == 1 ) Mtrigg_connect = 1 ;// при отсутствии связи и не
    else                       Mtrigg_connect = 0 ;// создавать видимость ее появления.
    mSet_ServiceMsg2( _Srv2_NoLinkCAN ) ;
    flgO._.CAN1_ok = 0 ;
  }

  // Проверяем наличие связи со вторым ШУ: АТК1-АТК2
  if (_r.can[0].config._.master)
  {
    if ( Mtrigg_connect2 != Mbi_canConnect2 )
    {
      if ( Mtrigg_connect2 == 0 ) Mtrigg_connect2 = 1 ;
      else                        Mtrigg_connect2 = 0 ;
      Mtime_connect2 = Timer1_Ovr ;
      //mClr_ServiceMsg( _Srv_NoLinkCAN2_atk1 ) ; // DAN 12.04.2025
      mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
      //mClr_ServiceMsg( _Srv_NoLinkCAN2_atkr ) ; // DAN 12.04.2025
      flgO._.CAN0_ok = 1 ;
    }
    if ( (u)((w)(Timer1_Ovr-Mtime_connect2)) > _r.T_Connect_cfg )
    {
      canId_zad = 0 ;
      canr.StatReg3.all = 0 ;
      Mbi_canConnect2 = 1 ;
      if ( Mbi_canConnect2 == 1 ) Mtrigg_connect2 = 1 ;// при отсутствии связи и не
      else                       Mtrigg_connect2 = 0 ;// создавать видимость ее появления.
      mSet_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;    // DAN 12.04.2025
      /* Проверяем наличие связи по рассчитанному номеру абонента :
      if      ( flgO._.abonATK == 1 )
      {
      mSet_ServiceMsg( _Srv_NoLinkCAN2_atk1 ) ; // Нет связи с АТК1 .
      mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
      mClr_ServiceMsg( _Srv_NoLinkCAN2_atkr ) ;
    }
    else if ( flgO._.abonATK == 2 )
      {
      mClr_ServiceMsg( _Srv_NoLinkCAN2_atk1 ) ;
      mSet_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;    // Нет связи с АТК2 .
      mClr_ServiceMsg( _Srv_NoLinkCAN2_atkr ) ;
    }
    else if ( flgO._.abonATK == 3 )
      {
      mClr_ServiceMsg( _Srv_NoLinkCAN2_atk1 ) ;
      mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
      mSet_ServiceMsg( _Srv_NoLinkCAN2_atkr ) ; // Нет связи с АТКR .
    }
    else // Чтобы сообщение об обрыве связи не появлялось у АТК , находящегося в Резерве ( с нулевым адресом Абонента )
      {
      mClr_ServiceMsg( _Srv_NoLinkCAN2_atk1 ) ;
      mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
      mClr_ServiceMsg( _Srv_NoLinkCAN2_atkr ) ;
    }*/
      //---
      flgO._.CAN0_ok = 0 ;
    }
  }
  else
  {
    mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
  }
  


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
        case _CAN1_Port : // Связь с AP2

          //  Тактирование опроса: если завершился опрос последнего абонента,
         // повторяем опрос с выдержкой времени.
            if ( tst_scan == 0 || (u)((w)(ax-time_scan)) > _r.time_scan )
             {
          // первый вход после такта - фиксируем время выхода на шину.
      if ( tst_scan != 0 ) time_scan = ax ;
      tst_scan = 0 ;  //14.03.05 14:04

              // обнулять в начале каждого оборота, а не один раз при входе в функцию.
              mark = 0 ;
/*********************************
 Первое устройство
*********************************/
              Tst_Read_Dev[0] = master_read("\x0\xff",&abDev1 , mark++ );
              Tst_Read_Dev[1] = master_read("\x1\xff",&abDev1 , mark++ );
              Tst_Read_Dev[2] = master_read("\x2\xff",&abDev1 , mark++ );
              Tst_Read_Dev[3] = master_read("\x3\xff",&abDev1 , mark++ );
              Tst_Read_Dev[4] = master_read("\x4\xff",&abDev1 , mark++ );
              Tst_Read_Dev[5] = master_read("\x5\xff",&abDev1 , mark++ );
              Tst_Read_Dev[6] = master_read("\x6\xff",&abDev1 , mark++ );
              Tst_Read_Dev[7] = master_read("\x7\xff",&abDev1 , mark++ );
              Tst_Write_Dev[0]  = master_write(  "\x8\x9\xff" , &abDev1 , mark++ ) ; 
              Tst_Write_Dev[1]  = master_write(  "\xa\b\xff"  , &abDev1 , mark++ ) ;  

        // опрос этой пачки завершен - взводим триггер.
        if ( Tst_Write_Dev2 != _NoErr_TimeOut && Tst_Write_Dev2 != _NoErr_Continue )
         {
          tst_scan = 1;
         }

             }

            break;

        case _CAN0_Port : // Связь с ША

            if ( (tst_scan2 == 0) || ((u)((w)(ax-time_scan2)) > _r.time_scan) )
             {
             // первый вход после такта - фиксируем время выхода на шину.
                if ( tst_scan2 != 0 ) time_scan2 = ax ;
                tst_scan2 = 0 ;  //14.03.05 14:04

              // обнулять в начале каждого оборота, а не один раз при входе в функцию.
              mark2 = 0 ;

                Tst_Write_Dev21  = master_qwrite( "\x0\x1\xff" , &abDev21 , mark2++ ) ; // DAN 31.05.2016
                Tst_Write_Dev21  = master_qwrite( "\x2\x3\xff" , &abDev21 , mark2++ ) ; // DAN 12.04.2025
                Tst_Write_Dev21  = master_qwrite( "\x4\x5\xff" , &abDev21 , mark2++ ) ; // DAN 12.04.2025
                Tst_Write_Dev21  = master_qwrite( "\x6\x7\xff" , &abDev21 , mark2++ ) ; // DAN 12.04.2025

                if ( Tst_Read_Dev21 != _NoErr_TimeOut && Tst_Read_Dev21 != _NoErr_Continue )
                {
                     tst_scan2 = 1;
                }

             }

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
  return 0 ;
}
