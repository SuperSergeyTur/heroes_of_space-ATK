
#ifdef _CM3_
word Time_Usel_Err_RAM @ "RAM_region"; // для проверки внешнего ОЗУ кладём во внутреннее .
#endif

//       ГЛАВНАЯ ПРОГРАММА - ДИСПЕТЧЕР ВСЕХ ОСТАЛЬНЫХ ПРОГРАММ.
//--------------------------------------------------


void    main (void) 
{
    word ax;
#if defined(MB91362) || defined(_CM3_)
    word bx;
#endif
#ifdef  _CM3_
    double bd;
#endif

    Init_CPU_Ports ();
#ifdef  MB91362
    bx = Init_RAM();
#endif

#ifdef  _CM3_
    //Настройка приоритетов прерываний:4 группы, 8 подгрупп
    // Выше приоритет у группы с меньшим номером . Внутри группы выше приоритет у прерывания с меньшим номером .
  NVIC_SetPriorityGrouping(5);
  RTC_Init();
  EMC_Init();

  if ((slw)emcx == -1 ) // Тест ОЗУ выдал "-1" - всё ОК , если какое-то число - это адрес неисправности .
  {
    bx = 0;
  }
  else
  {
    bx = 1;
  }
#endif
    Init_timer ();
//--------------------------------------
#ifdef _CM3_
      if ( bx != 0 )
      {
        Time_Usel_Err_RAM = Timer1_Ovr;

        for ( ;; )
        {
          mUSEL_not();
          if ((slw)emcx % 2 == 0) while((Timer1_Ovr-Time_Usel_Err_RAM) < _Sec(0.5));  // младший байт - микросхема DD3 .
          else                    while((Timer1_Ovr-Time_Usel_Err_RAM) < _Sec(1.0));  // старший байт - микросхема DD4 .
          Time_Usel_Err_RAM = Timer1_Ovr;
        }
      }
#endif
//--------------------------------------
    Init_Stop_Point () ;
#ifdef _CM3_
    GPDMA_Init_Start ();
#endif
    Start_RXD_TXD ();
    sio_start();
    Start_AD ();

#ifdef  _Union_FR
    Start_i2c_bus();
#endif

    Detect_i2c ( ); // Определение объёма i2c.

#ifdef  _CM3_
    PPG_total_init( LPC_PWM0,  2,_FzapolnShort_Low+_FzapolnShort_High); //SUM
    PPG_total_init( LPC_PWM1,  0,_DAC_setka_max); //DAC
    bd = 0;
#endif

    Perekl_rezerv ( 0, 0 ) ; // Инициализация прогр. перезагрузки блоков уст.
          // Поочередная загрузка всех блоков уставок, проверка, инициализация
         //типовыми уставками, с завершающей загрузкой первого блока.
    for ( ax = _kol_obl ; ax >= 1 ; ax-- ) load_obl_ust ( ax ) ;

    if (_r.Cfg._.Fzapoln) { mInit_Fzapoln() ; } // надо ставить после загрузки уставок.

    Init_Prog ();
#ifndef _KTEV
    pdf_init () ;
#endif
    System_prg ( 0 ) ;

    Start_Sled () ;

#ifdef  _CM3_
  CAN_aflut_Init();
#endif

    can_init( _CAN1_Port );                              // Инициализация CAN1
#ifdef _CANOPEN
    if (can_setting(_CAN0_Port).config._.mcovkl == 1)
       MCO_Init( _CAN0_Port );                          // Инициализация CAN0-CANOPEN , если он включен
    else
#endif
    can_init( _CAN0_Port );                           // Инициализация CAN0

#ifdef _CAN2_Port
    can_init( _CAN2_Port );                                  // Инициализация CAN2
#endif

#ifdef _CAN_MASTER
  #ifdef _CANOPEN
    if (can_setting(_CAN_MASTER_PORT).config._.mcovkl == 0)  // Если CANOPEN на этом порту выключен ,
  #endif
#ifdef _CAN_MASTER_PORT      
    can_master( _CAN_MASTER_PORT, 0);                        // инициализация CAN-MASTER на этом порту    
#endif    
#endif
    can_master( _CAN0_Port, 0); 
#ifdef  _CM3_
    MBRTU_Init();
#endif
#ifdef   _NET_IRQ
    Init_Net(); // 19.03.2014 13:47 д.б. до входа в ОСТАНОВ
#endif

    Shtat_ConfigReg ( _Shtat_Init ) ;
    can_ConfigReg ( _CAN_Init ) ;
    obj_ConfigReg ( _Obj_Init ) ;
#ifdef _NARABOTKA
    Narabotka ( 0 ) ;
#endif

#ifdef _JOURNAL
    Journal ( 0 ); // Должно быть до перехода в останов.
#endif

#ifdef  MB91362
      if (  bx != 0 )
      {
        Speed_Pult () ; // переход на медленный вывод .
       // output_s( _Autostart_txt ) ; // 14.01.2014 9:39 - сообщение убрано , чтобы не запутывать фразой про PIN1 .
        while ( !TestCompleted_Output() )  ;
        mSet_ServiceMsg( _Srv_ErrorOZU ) ;
        goto no_auto_start;
      }
#endif

          // Правильно ли проинициализирован константный блок уставок.
      if (  (b)_c.Ctrl_Code != 0x21u )
        {
          Speed_Pult () ; // переход на медленный вывод .
         // output_s( _Autostart_txt ) ;
          while ( !TestCompleted_Output() )  ;
          mSet_ServiceMsg( _Srv_UstCnst ) ;
          goto no_auto_start;
        }


      if ( !mTst_autostart() )
        {
          Speed_Pult () ; // переход на медленный вывод .
          output_s( _Autostart_txt ) ;
          while ( !TestCompleted_Output() )  ;
          goto no_auto_start ;
        }

#ifndef  _CM3_
      if ( (w)_i2c_end < (w)_i2c_end_32k ) // i2c должна быть не менее 32кб
        {
          Speed_Pult () ; // переход на медленный вывод .
          output_s( _MinSize_i2c_txt ) ;
          while ( !TestCompleted_Output() )  ;
          goto no_auto_start ;
        }
#endif

      ObjPrg ( _Obj_c_Init ) ;  // код "0" - стартовая инициализация.
 p(20) ;

      Control_otkr_tir ( _ConOtkr_Init ) ;

      Synch_Start () ;
  #ifndef _AD_ROT
    #ifdef  _SIFU_Syn2    // ЕСТЬ ЛИ ОТДЕЛЬНАЯ СИНХРОНИЗАЦИЯ ОТ МОСТА ДЛЯ СИФУ.
      Synch2_Start () ;
      Correct_Fazir (0) ;
    #endif
  #endif

      SIFU_Start () ;

    #ifdef _Vozb_KTE
      Vozb_Start () ;
    #endif

    #ifndef _AD_ROT
      Revers_epa_init () ;
    #else
      SkorAD_epa_init () ;
    #endif

p(10) ;

#ifdef _WatchDog  // 26.03.2015 - Нельзя перенесить в SYSTEM.C , т.к. он успевает сработать за время вывода стартовых сообщений (даты и названии программы) .
if (_r.Cfg2._.WatchdogEn) //Инициализация Watchdog по уставке
{
  watchdog_init( _r.WD_time ); // настройка и старт сторожа д.б. перед рабочим циклом
}
#endif

//НННННННННННННННННННННННННННННННННННННННННННННННННННННН

      while ( Av._.Ostanov == 0 )         // Основной цикл программ
      {
        //Av._.Ostanov = 0; // Рабочий режим.
        //  Для индикации времени цикла программы.
        Tckl = timer1 - Tckl_time , Tckl_time = timer1 ;
         //mUSEL_not() ;
p(11) ;
#ifndef  _USEL_obj
         USEL_Work () ;
p(12) ;
#endif
          System_prg ( 1 ) ;

#ifdef _WatchDog  // 26.03.2015 - Нельзя перенесить в SYSTEM.C , т.к. он успевает сработать за время вывода стартовых сообщений (даты и названии программы) .
          watchdog_reset(); // сброс сторожа
#endif

p(13) ;
          Port_input (1);
p(14) ;

#ifndef _F16e
          //Inputs_Programming (1) ;
          for ( ax = 0 ; ax < _SInp_max ; ax++ )
          {
            if ( _or.AS_CSi[ax] != 0xff )
            {
              S400_input ( _or.AS_CSi[ax], ax, 1 );
            }
          }
#else
    #ifdef _DI8
          Port_DI8 (1);
    #endif
    //---
    #ifdef _PORTE2_
          Port2_Filtr (1);
    #endif
#endif

p(15) ;
#ifndef _KTEV
          pdf_input() ;   // опрос ПДФ(ов).
p(16) ;
#endif
           //---- Считывание заданных аналоговых каналов.
          can_ConfigReg ( _CAN_Obmen ) ;
p(17) ; 
Synch ( &Syn ) ;
#ifndef _AD_ROT
       
      #ifdef  _SIFU_Syn2    // ЕСТЬ ЛИ ОТДЕЛЬНАЯ СИНХРОНИЗАЦИЯ ОТ МОСТА ДЛЯ СИФУ.
p(18) ;
        Synch ( &Syn2 ) ;
p(19) ;
        Correct_Fazir (1) ;
      #endif
p(49) ;
        Selsin_input() ;
#endif
//#ifndef _KTE  25.02.08 15:46 перенесено в СИФУ для синхронности.
  //      Short_ImpLong () ;
//#endif
#ifdef _DST
 p(70) ;
  Stat_Tok () ; // Датчик статического тока .
#endif
#ifdef _RRS
  RRS () ; // формирование флагов лыжи .
#endif
#ifdef _RDN
 p(71) ;
 #ifdef Id_2v_ach  // Измерение канала Id-2вал :
  while  ( Id_2v_full == _AD_BUSY );
  mIzmData_Conversion ( Id_2v_full , ax ,  Id_2v_ach ) ;
  Id_2v = (sw)( (slw)(sw)ax * (slw)(sw)_r.Mashtab_Id_2v >> 8 ) ;
  Id_2v_full = _AD_BUSY ;
  AD_Izm (  Id_2v_ach  , &Id_2v_full ) ; // ИЗМЕРЕНИЕ  "Id-2вал"
 #endif
 p(72) ;
  RDN () ; // Регулятор деления нагрузки .
#endif
 p(73) ;
#ifdef _BUKSOVKA
 #ifdef N_2v_ach  // Измерение канала N-2вал :
  while  ( N_2v_full == _AD_BUSY );
  mIzmData_Conversion ( N_2v_full , ax ,  N_2v_ach ) ;
  N_2v = (sw)( (slw)(sw)ax * (slw)(sw)_r.Mashtab_N_2v >> 8 ) ;
  N_2v_full = _AD_BUSY ;
  AD_Izm (  N_2v_ach  , &N_2v_full ) ; // ИЗМЕРЕНИЕ  "N-2вал"
 #endif
  Control_Buksovka () ; // Обнаружение буксовки .
#endif

#ifdef _RVId
//#ifdef _KTEV          // 15.12.2020 15:20 Измерение якорных токов для КТЭВ перенесено в IdIzm() и IdConv(),
//RVId_Izm_Conv ( ) ;   // а сами якорные токи д.б. заведены на усреднители (для ТПД,
//#endif                // для ГД - не обязательно).
  RVId_Reg ( ) ; //Включение Регулятора выравнивания токов якоря
#endif

 p(50) ;
        Shtat_ConfigReg ( _Shtat_Reg ) ;
 p(51) ;
        if ( Prg._.Gotovn == 1 )  Sborka_Gotovn () ;
        else                      Rabota () ;

 p(60) ;

//----
#ifdef _CAN_MASTER
#ifdef _CAN_MASTER_PORT
//----
    #if _CAN_MASTER_PORT == _CAN1_Port      // CAN1
        can_master( _CAN1_Port, 1 ) ;
 p(61) ;
  #ifdef _CANOPEN
    if ( mco_vkl == 1)
       MCO_Background( _CAN0_Port );
    else
  #endif
        //can_slave( _CAN0_Port ) ;
        #ifdef _CAN2_Port
            can_slave( _CAN2_Port ) ;
        #endif

    #elif _CAN_MASTER_PORT == _CAN0_Port // CAN0
  #ifdef _CANOPEN
    if ( mco_vkl == 1)
       MCO_Background( _CAN0_Port );
    else
  #endif
        can_master( _CAN0_Port, 1 ) ;
 p(61) ;
        can_slave( _CAN1_Port ) ;
        #ifdef _CAN2_Port
            can_slave( _CAN2_Port ) ;
        #endif

    #elif _CAN_MASTER_PORT == _CAN2_Port        // CAN2 - 24.07.2014 - д.б. ниже , чем CAN0 , т.к. если Мастером задан
        can_master( _CAN2_Port, 1 ) ;           //        CAN0 , а CAN2 не определён , то компилятор "проваливается" в
 p(61) ;                                        //        строчки по CAN2 ...
        can_slave( _CAN1_Port ) ;
  #ifdef _CANOPEN
    if ( mco_vkl == 1)
       MCO_Background( _CAN0_Port );
    else
  #endif
        can_slave( _CAN0_Port ) ;

    #endif
#else //_CAN_MASTER_PORT
  can_slave( _CAN1_Port ) ;  
#endif
//----
#else //_CAN_MASTER
//----
// p(613) ;
        can_slave( _CAN1_Port ) ;
  #ifdef _CANOPEN
    if ( mco_vkl == 1)
       MCO_Background( _CAN0_Port );
    else
  #endif
        //can_slave( _CAN0_Port ) ;
    #ifdef _CAN2_Port
        can_slave( _CAN2_Port ) ;
    #endif
//----
#endif //_CAN_MASTER
//----
 p(62) ;
        can_obj(0) ;
 p(63) ;

#ifdef _CM3_
     MBRTU_Background();
#endif
#ifdef _NET_IRQ
   Work_Net( _FLAGNET_SEND );
#endif
 p(64) ;
        Blok_upr () ;
        //if ( Prg._.Blok_upr == 1 )  Blok_upr () ;
//#ifdef _KTE_GD   27.06.2008 10:00 - перенесено из MAIN в СИФУ .
//        Izm_GD () ; //  Измерение Ug и Ig.
//#endif
 p(74) ;
#if !defined(_KTEV) && !defined(_AD_ROT)
           // Формирование задания на ток возбуждения + регулятор ЭДС 2-й зоны.
        Zadanie_Iv () ;
#endif
 p(80) ;

#ifdef _NARABOTKA
    Narabotka ( 1 ) ;
#endif

          Pult_Rabota () ; // вынесено из switch для уменьшения времени считывания i2c

          switch ( Zapas_Pointer++ )
            {
              default :  Zapas_Pointer = 1 ;
              case  0 :
  #ifndef _ATK_ROT // Для АТК выполняется только в сетевом АР1 ( но по току ротора , т.к. при включении КЗ Id = 0 ) :
                         Teplo_Programm(1) ;  // 50 - 550
  #endif
                         break ;
              case  1 :
 p(160) ;
                         pr = &zad_res ,  Izm_Analog () ;
                         break ;
            }


 p(190) ;
    // Sled () ;  перенесено в прерывание СИФУ.

//#ifdef _JOURNAL
//    Journal ( 1 ); 11.04.2014 11:44 Перенесено в "System_prg()"
//#endif

 p(200) ;

#ifndef  _Adc_Extend_Po0 // Если Порт 0 не используется для управления внешним мультиплексором АЦП :
              // Централизованная выдача внешних сигналов.
          Port_output ();
#endif

 #ifndef _F16e
 p(201) ;
          for ( ax = 0 ; ax < _SOut_max ; ax++ )
          {
            if ( _or.AS_CSo[ax] != 0xff )
            {
              S400_output ( _or.AS_CSo[ax] , ax);
            }
          }
#endif
 p(202) ;
          //DAC_Output () ;
          DAC_pOutput ();
 p(203) ;
          Clr_Q1_Q2 ()  ;
 p(204) ;
        }
    //Speed_Pult () ; // переход на медленный вывод .

no_auto_start:

          // Запретить прерывания по имп. и изм. ЕПА.

    mOtkl_Imp( _Avar_imp ) ;  // отключение импульсов
    mClr_ImpVozb ()  ;
  //---
    //output_s( _Ostanov_prompt ) ;
    //while ( !TestCompleted_Output() );
    if ( Mon.Pult == 1 ) Speed_Pult ( ) ; // переход на быстрый вывод .

  //---
    Av._.Ostanov = 1 ; // Тестовый режим.
      // Накладываем мех.тормоз.
#ifdef bo_MT
    bo_MT = 0 ;
#endif

    DWelcome = "\r\nDo>" ,  MWelcome = "\r\nMo>", AWelcome = _OWell_txt ;
    Pult_Prog_Addr = _Case ( 'A' , '1' ) ,   M_FirstCall = 1 ;

    while ( 1 )
    {    //  Для индикации времени цикла программы.
      Tckl = timer1 - Tckl_time , Tckl_time = timer1 ;

          System_prg ( 1 ) ;

#ifdef _WatchDog
          watchdog_reset(); // сброс сторожа
#endif

          Port_input (1);
#ifndef _F16e
          for ( ax = 0 ; ax < _SInp_max ; ax++ )
          {
            if ( _or.AS_CSi[ax] != 0xff )
            {
              S400_input ( _or.AS_CSi[ax], ax, 1 );
            }
          }
#else
    #ifdef _DI8
          Port_DI8 (1);
    #endif
    //---
    #ifdef _PORTE2_
          Port2_Filtr (1);
    #endif
#endif
#ifndef _KTEV
          pdf_input() ;   // опрос ПДФ(ов).
#endif
           //---- Считывание заданных аналоговых каналов.
          can_ConfigReg ( _CAN_Obmen ) ;

          Pult_Rabota () ;

#ifndef  _Adc_Extend_Po0 // Если Порт 0 не используется для управления внешним мультиплексором АЦП :
              // Централизованная выдача внешних сигналов.
          Port_output ();
#endif
#ifndef _F16e
          for ( ax = 0 ; ax < _SOut_max ; ax++ )
          {
            if ( _or.AS_CSo[ax] != 0xff )
            {
              S400_output ( _or.AS_CSo[ax] , ax);
            }
          }
#endif
          DAC_Output () ;

#ifdef _CAN_MASTER
    #if _CAN_MASTER_PORT == _CAN1_Port      // CAN1
        can_master( _CAN1_Port, 1 ) ;
        can_slave( _CAN0_Port ) ;
        #ifdef _CAN2_Port
            can_slave( _CAN2_Port ) ;
        #endif
    #elif _CAN_MASTER_PORT == _CAN0_Port // CAN0
        can_master( _CAN0_Port, 1 ) ;
        can_slave( _CAN1_Port ) ;
        #ifdef _CAN2_Port
            can_slave( _CAN2_Port ) ;
        #endif
    #elif _CAN_MASTER_PORT == _CAN2_Port        // CAN2 - 24.07.2014 - д.б. ниже , чем CAN0 , т.к. если Мастером задан
        can_master( _CAN2_Port, 1 ) ;           //        CAN0 , а CAN2 не определён , то компилятор "проваливается" в
        can_slave( _CAN1_Port ) ;           //        строчки по CAN2 ...
        can_slave( _CAN0_Port ) ;
    #endif
#else
        can_slave( _CAN1_Port ) ;
        can_slave( _CAN0_Port ) ;
    #ifdef _CAN2_Port
        can_slave( _CAN2_Port ) ;
    #endif
#endif
          can_obj(0) ;

#ifdef _CM3_
     MBRTU_Background();
#endif

#ifdef _NET_IRQ
   Work_Net( _FLAGNET_SEND );
#endif

                // Проверка сигнала Геркона Переменного Тока.
                   // <- признак выставляется в  прерывании по геркону.
          if ( bi_Gercon == 1 )    mSet_AvarMsg ( _Av_Gercon ) ;
          // Если определён "bi_2B1" , то авария срабатывает всё равно по входу bi_Gercon.
#ifdef  bi_GerconAC2
          if ( bi_GerconAC2 == 1 ) mSet_AvarMsg ( _Av_GerconDC ) ;
#endif
#ifdef  bi_GerconDC
          if ( bi_GerconDC == 1 )  mSet_AvarMsg ( _Av_GerconDC ) ;
#endif

          Clr_Q1_Q2 ()  ;
        mUSEL_clr() ;
          Sled () ;   //150-200mcs
        mUSEL_set() ;
      }
}
//-------------
