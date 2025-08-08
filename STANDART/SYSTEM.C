
#include <led_control.c>
#include <password.c>

#ifdef _WatchDog
    #include <watchdog.c>
#endif

//----------------------------------------------
//
//   Программа сборник системных программ.
//
void System_prg ( byte code )
{

  Timer1_fS() ;    // счет младшего и старшего таймерных полуслов.

  if ( code == 0 )  // стартовая инициализация.
  {
    //------ обнуление для агрегатов с единичным набором регистров --------
    Reg_AvarMsgFirst2 = 0 ;
    Reg_AvarMsg2      = 0 ;
    Reg_PreduprMsg2   = 0 ;
    Reg_ServiceMsg2   = 0 ;
    mask_predupr      = 0 , mask_predupr2 = 0 ;
    mask_service      = 0 , mask_service2 = 0 ;
#ifdef _TRETIY_REG
    Reg_AvarMsgFirst3 = 0 ;
    Reg_AvarMsg3      = 0 ;
    Reg_PreduprMsg3   = 0 ;
    Reg_ServiceMsg3   = 0 ;
    mask_predupr3     = 0 ;
    mask_service3     = 0 ;
#endif
#ifdef _INTERPRETER
    Reg_AvarMsgFirst_obj = 0 ;
    Reg_AvarMsg_obj      = 0 ;
    Reg_PreduprMsg_obj   = 0 ;
    Reg_ServiceMsg_obj   = 0 ;
    mask_predupr_obj     = 0 ;
    mask_service_obj     = 0 ;
#endif

    time_Svet = Timer1_Ovr;
    //----------------------------------------------------------------------

    //xSave_Ust( code ) ;      // запись уставок по команде.
#ifndef _NO_LINK
    Link_start() ;
#endif
    S_break = 200 , Nort_Password = 0 ;

    RemoteTerminal ( 0 )  ;

#ifdef _INTERPRETER
    if ( Interpreter (0) != 0 ) ObjSrv_bit._.Avar = 1 ;
#endif

    LED_control ( 0 ) ;
    Password_control ( 0 ) ;
#if defined( _CM3_) && !defined (_NO_RTC)
      //Считываем значение переменной WinTime из ЭОЗУ
#ifndef _free_Space_Reg
     необходимо определить _free_Space_Reg чтобы не затирались уставки
       при записи параметров зимнего времени.
         если кроме этой ошибок по _free_Space_Reg нет, то необходимо обновить
           monitor.h, определение макроса _ust_beg_adr_i2c
#endif
      word ax = Load_from_i2c(2,WinTime_addr , (b*)&WinTime,_Adr_Flash_i2c );
      if (ax == 0)
      {
        if ( mTst_autostart() )
        {
          //проверка на значение переменной WinTime в ЭОЗУ, если там мусор,
          //то записываем в ЭОЗУ 1
           if (WinTime > 1)
           {
             WinTime = 1;
             Save_into_i2c(2 ,(b*)&WinTime, WinTime_addr,_Adr_Flash_i2c );
           }

           if (_WinTimeOn > 1)
           {
             _WinTimeOn = 1;
           }
        }
      }
#endif
//#ifdef _WatchDog  // 26.03.2015 - Нельзя перенесить из _MAIN.C, т.к. он успевает сработать за время вывода стартовых сообщений (даты и названии программы) .
//    watchdog_init(_r.WD_time);
//#endif
  }
  else
  {
    Ovr_Time_Schet();  // часы реального времени.
#ifndef _NO_LINK
    Link_txrx();
#endif

//#ifdef _WatchDog  // 26.03.2015 - Нельзя перенесить из _MAIN.C, т.к. он успевает сработать за время вывода стартовых сообщений (даты и названии программы) .
//    watchdog_reset(); // сброс сторожа
//#endif
#ifdef _Sld_cond
    Cond_Sled_Stop ();
    Cond_Sled_Start ();
#endif
          //    Фиксация времени изменения количества сообщений дл
      //  распечатки его по "Enter" в режиме "A1".
    check_msg_time ()  ;

#ifdef _JOURNAL                            // 11.04.2014 11:45 перенесено из "_main()". Д.б. после "check_msg_time()"
    if( Av._.Ostanov == 0 ) Journal ( 1 ); // журнал выполняется только в "Работе"
#endif
  }

  xSave_Ust( code ) ;      // запись уставок по команде.
  //xF9_LoadUst( code );
#if defined(_BTE) && defined(Zad_RT_ach)
  if ( code != 0 ) RW_i2c_data (code);     // в ВТЕ чтение i2c уже выполненно в ustavki.c (это необх. для входа в осн.цикл с известн. значен.задания )
#else
  RW_i2c_data (code);     // запись переменной по команде
#endif

#ifndef _NO_LINK
  PrepareTab();
  Load_Sled_Tab();
  LanOscl();
#endif

#ifdef _INTERPRETER
    if (ObjSrv_bit._.InWork)
    {
        if ( Interpreter (1) != 0) ObjSrv_bit._.Avar = 1;
    }
#endif

  RemoteTerminal ( 1 )  ;

  LED_control ( 1 ) ;


  //----  XML-Reading  -----
    //  Interpreter and executer of host-xmlCommands
    //  Linked to vartab.h - exports his arrays into vartab with fixed numbers
  //xmlCommandExecuter.executeCommand();

  return ;
}
//------------------------------

void  Timer1_fS( void )
{
  word ax, bx ;

    do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
    ax <<= 8 ;      //  Из четырехбайтного полного значения времени
    ax  += (bx>>8); // для работы берутся средние два байта прини-
                    // мающие значения в диапазоне 0.25мсек-12.0сек.
  Timer1_fSec = ax ;

  return ;
}
//---------------------------------

void  RemoteTerminal ( word code )
{
  static word  UartCAN_time_connect ;
  union UART_CANtx tx_buff ;
  word j, i = 0;
  if ( code == 0 )
  {
reinit:
    if ( Mon.UartCAN_Connect == 1 )
    {    // чтобы не замирал вывод после обрыва связи.
      Mon.UartCAN_Connect = 0 ; // сначала обнулить, а затем вызвать
      Restart_Output ()  ;     // Restart...
    }
    Mon.RX_Data_ok = 0 ;
    UartCAN_Rx.all = 0 ;
    UartCAN_Tx.all = UartCAN_Rx.all ;
    UartCAN_time_connect = Timer1_Ovr - _Sec(2.1) ;
    //time_rxd = Timer1_Ovr ;

    return ;
  }
    //-----------
          //  все операции ведем в буфере, а позавершении выгружаем в рабочую переменную,
          // чтобы если CAN или DP на прерываниях, они не схватили недоделанный мусор.
    tx_buff.all = UartCAN_Tx.all ;

        //  проверяем наличие связи, и одновремено отвечаем тем же уровнем, что и приняли.
    if ( tx_buff._.Connect != UartCAN_Rx._.Connect )
    {
      if ( tx_buff._.Connect == 0 ) tx_buff._.Connect = 1 ;
      else                          tx_buff._.Connect = 0 ;
      UartCAN_time_connect = Timer1_Ovr ;
      Mon.UartCAN_Connect = 1 ;
    }
    else if ( (u)((w)( Timer1_Ovr - UartCAN_time_connect )) >= _Sec(2.0) )  goto reinit ;
      //---

    //  если изменился  rx_num - значит прислали символ в буфер клавиатуры
    if ( UartCAN_Rx._.rx_num == 0 )  tx_buff._.rx_num = 0 ;
    else if ( UartCAN_Rx._.rx_num != tx_buff._.rx_num )
    {
      mSymbol_in_Buff_RXD( UartCAN_Rx._.Symbol ) ;
      tx_buff._.rx_num = UartCAN_Rx._.rx_num ;
    }
      //---

    //  если изменился  tx_num - значит прислали запрос на символ из буфера экрана

    if ( UartCAN_Rx._.tx_num == 0 )  tx_buff._.tx_num = 0 ;
    else if ( UartCAN_Rx._.tx_num != tx_buff._.tx_num )
    {
      //  поле Symbol является счетчиком запрошиваемых символов
      //  для совместимости с прежними версиями:
      //  -  0 или 1 означает - один символ и результат положить в UartCAN_Tx.all
      //  -  более 1 означает - все имеющиеся но не более заданого количества и результат положить в UartCAN2_Tx.all
      if ( UartCAN_Rx._.tx_array == 0 )
      {
        if ( mTestYesData_in_Buff_TXD() )
        {
            mSymbol_from_Buff_TXD( tx_buff._.Symbol ) ;
            mSymbol_in_TXD_port( tx_buff._.Symbol ) ;
            tx_buff._.tx_num = UartCAN_Rx._.tx_num ;
        }
      }
      else
      {
        
        //  первые два байта массива tx_buff.buff[] заняты полем tx_buff.all
        while ( mTestYesData_in_Buff_TXD() && i < ( _UartCAN_Tx_Size - 2))
        {
            mSymbol_from_Buff_TXD( tx_buff.symbols[2+i] ) ;
            i++;
            // вывод при передаче пачками не делаем, т.к. порт не успеет все проглотить
            //mSymbol_in_TXD_port( tx_buff._.Symbol ) ;
            //  при передаче масивом используем  tx_buff._.Symbol как счетчик передаваемых символов
            tx_buff._.tx_num = UartCAN_Rx._.tx_num ;
        }
        //  стоит здесь чтобы не перезатирать данные на холостых проходах
        for( j = 0 ; j < i ; j++)  UartCAN_Tx.symbols[2+j] = tx_buff.symbols[2+j];
        tx_buff._.Symbol = i;
      }
    }
      //---

    UartCAN_Tx.all = tx_buff.all ;

  return ;
}
