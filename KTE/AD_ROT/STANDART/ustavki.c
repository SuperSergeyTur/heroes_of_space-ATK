
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

void  Init_Prog ( void )
  {
//#if ( !defined (_WM591) && !defined (_F16e) ) || defined (Id_sr_ach)
    register word ax ;
//#endif
//ДДДДДДДДДДДДД  Для ЦАПа  ДДДДДДДДДДДДДД

      DAC_start () ;
 #ifndef _AD_ROT
      Selsin_init () ;
 #endif
//ДДДДДДДДДДДДД Для Входных\Выходных Портов ДДДДДДДДДДДДДДДДДД

#ifndef  _Adc_Extend_Po0 // Если Порт 0 не используется для управления внешним мультиплексором АЦП :
           // инициализация портов выходных дискретных сигналов.
      Port_output_clr ();
#endif

           // инициализация портов входных дискретных сигналов.
      Port_input (0);
#ifndef _WM591
#ifndef _F16e
      //Inputs_Programming (0) ;

      // Первичное обнуление линий CS0 и CS1 для правильного ПЕРВОГО считывания порта AsPi0.
      // Актуально для F16K, а для СМ3, как оказалось, нужно еще и CS2, CS3 и CS4 установить в 1 (это для S500),
      // хотя правильно бы было изначально настроить ножки процессора на всех процессорных платах
      // при инициализации в зависимости от S500 или S400.
      // Проявилось на КТЕ-1600 нажимном (Зап.сталь слябинг), когда при неправильном ПЕРВОМ чтении порта,
      // на который бал заведен сигнал SQ1, отключался Q1 после перезапуска процессора.
#ifdef _S500
       Clr_cs_sio( 0 );
#else
    #ifdef _CM3_
        #ifdef  _CS0
            _Set_CS(CS_IO[0]);
        #endif
        #ifdef  _CS1
            _Set_CS(CS_IO[1]);
        #endif
        #ifdef  _CS2
            _Set_CS(CS_IO[2]);
        #endif
        #ifdef  _CS3
            _Set_CS(CS_IO[3]);
        #endif
        #ifdef  _CS4
            _Set_CS(CS_IO[4]);
        #endif
        #ifdef  _CS5
            _Set_CS(CS_IO[5]);
        #endif
        #ifdef  _CS6
            _Set_CS(CS_IO[6]);
        #endif
        #ifdef  _CS7
            _Set_CS(CS_IO[7]);
        #endif
        #ifdef  _CS8
            _Set_CS(CS_IO[8]);
        #endif
        #ifdef  _CS9
            _Set_CS(CS_IO[9]);
        #endif
    #endif
#endif

     //инициализация портов на дополнительной плате
    //Входные порты
      for ( ax = 0 ; ax < _SInp_max ; ax++ )
      {
        if ( _or.AS_CSi[ax] != 0xff )
        {
          S400_input ( _or.AS_CSi[ax], ax, 0 );
        }
      }

    //Выходные порты

    for ( ax = 0 ; ax < _SOut_max ; ax++ )
    {
      PoS_c[ax].all = 0;
      if ( _or.AS_CSo[ax] != 0xff )
      {
        S400_output ( _or.AS_CSo[ax] , ax);
      }
    }
#else
    #ifdef _DI8
          Port_DI8 (0);
    #endif
    //---
    #ifdef _PORTE2_
          Port2_Filtr (0);
    #endif
#endif
#endif

//ДДДДДДДДДДДДД  Для CAN  ДДДДДДДДДДДДДД

      // Инициализация слова управления необходима здесь , до инициализации в CAN_OBJ.C :
      canr.CfgReg.all = 0 ;

//ДДДДДДДДДДДДД  Для Пульта  ДДДДДДДДДДДДДД

//#ifdef  _CM3_
//  strcpy (__DATETIME__ , __DATE__);
//  strcat (__DATETIME__ , " \n\r");
//  strcat (__DATETIME__ , __TIME__);
  //strcat (__DATETIME__ , "\n\r");
  /*InitDateTimeCompile(&TDa, &TTi, __DATETIME__);
  DateCompile(&TDa) ;
  TimeCompile(&TTi) ;
  memcpy( __DATETIME__, TDa.Str, sizeof(TDa.Str));
  strcat( __DATETIME__, "\n\r   - ") ;
  strcat( __DATETIME__, TTi.Str);
  strcat( __DATETIME__, " -") ;*/
//#endif

      DWelcome = "\r\nDg>" ,  MWelcome = "\r\nMg>", AWelcome = _GWell_txt;
      DWell_old = DWelcome ;
      AWell_old = AWelcome ;

      output_s ( "\r\n" _Device_Name_ ) ;
      while ( !TestCompleted_Output() )  ;

      output_s ( "\r\n" ) ; // Для CM3 нельзя эти символы записать в одной строке ...
      output_s ( __DATETIME__ ) ;
      output_s ( "\r\n" ) ;
      while ( !TestCompleted_Output() )  ;

#ifdef _PROGRAM_
      output_s ( "\r\n" _PROGRAM_ ) ;
      while ( !TestCompleted_Output() )  ;
#endif

             // Загрузка рабочей области.
      while ( Perekl_rezerv ( 2, read_rezerv() ) != 0 ) ;

      while ( !TestCompleted_Output() )  ;

      _N_prog = 1 ;// для "A7".
      Speed_Pult () ;
    #ifdef _UPTF       // Стартовая программа - "A0-Сообщ/Индиk" .
      Pult_Prog_Addr = _Case ( 'A' , '0' ) ,   M_FirstCall = 1, M_FirstCallFazir = 1 ;
    #else
      Pult_Prog_Addr = _Case ( 'A' , '1' ) ,   M_FirstCall = 1, M_FirstCallFazir = 1 ;
    #endif

//ДДДДД  Для Структуры Программы ДДДДДД

      Prg.all = _Prg_Gotovn ;
      upr_label = 0 ;

//ДДДДДДДДДДДДД  Для аварий  ДДДДДДДДДДДДДД

    Reg_AvarMsgFirst = 0 ;
    Reg_AvarMsg      = 0 ;
    Reg_PreduprMsg   = 0 ;
//  Reg_ServiceMsg   = 0 ;  обнуляется в cstart()
    mask_predupr     = 0 ;
//------
    Reg_AvarMsgFirst2 = 0 ;
    Reg_AvarMsg2      = 0 ;
    Reg_PreduprMsg2   = 0 ;
    Reg_ServiceMsg2   = 0 ;
    mask_predupr2     = 0 ;
//------
#ifdef _TRETIY_REG
    Reg_AvarMsgFirst3 = 0 ;
    Reg_AvarMsg3      = 0 ;
    Reg_PreduprMsg3   = 0 ;
    Reg_ServiceMsg3   = 0 ;
    mask_predupr3     = 0 ;
#endif

#ifdef _INTERPRETER
    Reg_AvarMsgFirst_obj = 0 ;
    Reg_AvarMsg_obj      = 0 ;
    Reg_PreduprMsg_obj   = 0 ;
    Reg_ServiceMsg_obj   = 0 ;
    mask_predupr_obj     = 0 ;
    mask_service_obj     = 0 ;
#endif

    F2regim = 0 ;
    av_label = 0  ;

    N_Ucc = 0 , N_Ucc2 = 0 ;
    P24_Ucc = _AD_BUSY ;
    AD_Izm ( P24_ach, &P24_Ucc ) ;  //  запуск первого измерения питания
#ifdef  _Union_FR
    Alarm_start();
#endif

    Av.all = 0 , Av2.all = 0 ;
        mClr_Q1() ;  //   При каждой очистке Av.all нужно сбрасывать Q1,Q2,
        mClr_Q2() ;  // иначе он залипнет если сброс попал на время импульса.

    Isp.all = 0x0  ;  // структура для программ испытаний
    Prz.all = 0 ;

#ifndef _WM591
    Control_dt_Avar ( 0 ) ; // инициализация выдержек перехода предупреждений в аварии.

    Contr_Ttrans_4_20 ( 0 ) ; // инициализация контоля датчика температуры трансформатора .

    Stoyanka_Time  = Timer1_Ovr ;
    Stoyanka_Timer = 0 ;

    MechTorm_upr ( _MT_Init ) ;  // инициализация мех.торм.

    RT_trigg = 0 ;//, APV_Gercon = 0 ;

     //- Инициализация Для Контроля изоляции -

    Uinsul = 0 , Uinsul_max = 0 ; // Для случаев , когда контроль изоляции не определен .
    Contr_Insulat( 0 )  ;

  #ifdef Insul_G_ach
    Contr_Insulat_G( 0 ) ; // Инициализация Для Контроля изоляции Возбуждения Генератора .
  #endif
  #ifdef Insul_D_ach
    Contr_Insulat_D( 0 ) ; // Инициализация Для Контроля изоляции Возбуждения Двигателя .
  #endif
#endif

              //  Измерения смещений по каналам АЦП:
/* 20.11.2016 - Шестаков рекомендует убрать автоматическое смещение , т.к. оно может измениться при подаче силы .
    if ( Izm_NullOffset ( & Id_mg_ach   ) != 0 )  // Id мгновенный
      {
        mSet_PreduprMsg( _Pr_OffsetAch ) ;
        mSet_ServiceMsg( _Srv_Offset_Id_mg ) ;
      }*/   // убрано чтобы не меряло ложное смещ. при вращ.двиг. 13.07.06 10:42
   // if ( Izm_NullOffset ( & Ud_ach   ) != 0 )     //      Ud
   //   {
   //     mSet_PreduprMsg( _Pr_OffsetAch ) ;
   //     mSet_ServiceMsg( _Srv_Offset_Ud ) ;
   //   }
#if defined( Id_sr_ach ) || ( defined( _CM3_ ) && defined( _KTEV ) && defined( _RVId ) )
     set_strob_usredn() ;// строб, чтобы разрядить усреднит.
       for ( ax = timer1 ; (u)((w)(timer1-ax)) <= _MkSec(20000) ; ) ;
     clr_strob_usredn() ;

  /*if ( Izm_NullOffset ( & Id_sr_ach ) != 0 )
      {
        mSet_PreduprMsg( _Pr_OffsetAch ) ;
        mSet_ServiceMsg( _Srv_Offset_Id_sr ) ;
      }*/
#endif
/*  //        Для второго моста 12-ти пульсных схем.
#ifdef  Id2_mg_ach                                 //  Id2 мгновенн.
    if ( Izm_NullOffset ( & Id2_mg_ach ) != 0 )
      {
        mSet_PreduprMsg( _Pr_OffsetAch ) ;
        mSet_ServiceMsg( _Srv_Offset_Id2_mg ) ;
      }
#endif
#ifdef  Id2_sr_ach                                 //  Id2 средний
    if ( Izm_NullOffset ( & Id2_sr_ach ) != 0 )
      {
        mSet_PreduprMsg( _Pr_OffsetAch ) ;
        mSet_ServiceMsg( _Srv_Offset_Id2_sr ) ;
      }
#endif
#ifdef  _RVId
    if ( Izm_NullOffset ( & Id1_ach ) != 0 )
      {
        mSet_PreduprMsg( _Pr_OffsetAch ) ;
//        mSet_ServiceMsg( _Srv_Offset_Id2_sr ) ;
      }
    if ( Izm_NullOffset ( & Id2_ach ) != 0 )
      {
        mSet_PreduprMsg( _Pr_OffsetAch ) ;
//        mSet_ServiceMsg( _Srv_Offset_Id2_sr ) ;
      }
#endif
//        Для тока якоря/генератора систем ГД.
#ifdef _KTE_GD
  //if ( Izm_NullOffset ( & Ug_ach   ) != 0 )     //  Ug генератора
  //  {                                       не измеряем т.к. при вкл.системы
  //    mSet_PreduprMsg( _Pr_OffsetAch ) ;    может уже быть наведенное напряжение.
  //    mSet_ServiceMsg( _Srv_Offset_Ug ) ;
  //  }  // убрано чтобы не меряло ложное смещ. при работе резервн.сист. 13.07.06 10:42
  //  if ( Izm_NullOffset ( & Ig_ach ) != 0 )  //  Ig генератора
  //    {
  //      mSet_PreduprMsg( _Pr_OffsetAch ) ;
  //      mSet_ServiceMsg( _Srv_Offset_Ig ) ;
  //    }
#endif
*/
 //-----------Для усреднения тока возбуждения

//#ifndef _KTEV  //13.09.07 14:00 - Для всех агрегатов , у которых есть Iv_ach :
#ifdef   Iv_ach
    time_Iv_min = Puls_counter ;
        #ifndef _Vozb_KTE
            Iv_usr.n = 0;
            Iv_usr.out = &V.Iv_full;
            Iv_usr.time = timer1;
            Iv_usr.time1 = timer1;         // 25.04.2008 - Для формы Iv с ярко выраженными пульсами
            Iv_usr.ach = &Iv_ach;          // увеличено с 10мс до 20мс :
                #ifndef _CM3_
                    Iv_usr.dT = _MkSec(20u*1000u); //_MkSec(10u*1000u);  // _MkSec(40u*1000u);
                #else
                                              // Измерения Iv происходят в фоне , в СМ3 успевает за пульс несколько раз ...
                    Iv_usr.dT = _MkSec(3333); // 11.04.2019 По результатам 10К Азовсталь с запаздыванием измерения возбудителя .
                #endif
            Iv_usr.label = 0;
            Iv_usr.sum = 0;
            Iv_usr.mod = 1;
                #ifdef _Rev_Pola   // если включен алгоритм реверса поля.
                    Iv_usr.mod = 0;  // усреднение со знаком.
                #endif
            Usrednitel( &Iv_usr, 0);
        #else
            V.Iv = 0 ;
            time_Iv_max = Puls_counter ;
        #endif
#else
    V.Iv = 0 ; // Для агрегатов , у которых нет Iv_ach .
#endif

#ifdef _RVId
    #ifdef Iv2_ach
        Iv2_usr.n = 0;
        Iv2_usr.out = &V2.Iv_full;
        Iv2_usr.time = timer1;
        Iv2_usr.time1 = timer1;         // 25.04.2008 - Для формы Iv с ярко выраженными пульсами
        Iv2_usr.ach = &Iv2_ach;          // увеличено с 10мс до 20мс :
            #ifndef _CM3_
                Iv2_usr.dT = _MkSec(20u*1000u); //_MkSec(10u*1000u);  // _MkSec(40u*1000u);
            #else
                                           // Измерения Iv происходят в фоне , в СМ3 успевает за пульс несколько раз ...
                Iv2_usr.dT = _MkSec(3333); // 11.04.2019 По результатам 10К Азовсталь с запаздыванием измерения возбудителя .
            #endif
        Iv2_usr.label = 0;
        Iv2_usr.sum = 0;
        Iv2_usr.mod = 1;
        //Iv2_usr.mod = 0;  // усреднение со знаком.
        Usrednitel( &Iv2_usr, 0);
    #endif
    #ifdef _KTEV
        Udv_usr.n = 0;
        Udv_usr.out = &UdvSr_full;
        Udv_usr.time = timer1;
        Udv_usr.time1 = timer1;         // 25.04.2008 - Для формы Iv с ярко выраженными пульсами
        Udv_usr.ach = &UdvSr_ach;        // увеличено с 10мс до 20мс :
            #ifndef _CM3_
                Udv_usr.dT = _MkSec(20u*1000u); //_MkSec(10u*1000u);  // _MkSec(40u*1000u);
            #else
                                           // Измерения Iv происходят в фоне , в СМ3 успевает за пульс несколько раз ...
                Udv_usr.dT = _MkSec(3333); // 11.04.2019 По результатам 10К Азовсталь с запаздыванием измерения возбудителя .
            #endif
        Udv_usr.label = 0;
        Udv_usr.sum = 0;
        Udv_usr.mod = 1;
        //Udv_usr.mod = 0;  // усреднение со знаком.
        Usrednitel( &Udv_usr, 0);
        UdvSr = 0;
    #endif
#endif

#ifdef   It_ach // Для агрегатов , у которых есть ток тормоза .
    It = 0 ;
    //---
    It_usr.n = 0;
    It_usr.out = &It_full;
    It_usr.time = timer1;
    It_usr.time1 = timer1;         // 25.04.2008 - Для формы Iv с ярко выраженными пульсами
    It_usr.ach = &It_ach;          // увеличено с 10мс до 20мс :
    It_usr.dT = _MkSec(20u*1000u); //_MkSec(10u*1000u);  // _MkSec(40u*1000u);
    It_usr.label = 0;
    It_usr.sum = 0;
    It_usr.mod = 1;
    Usrednitel( &It_usr, 0);
#endif

        // Для считывания часов реального времени i2c.
    Time_label = 0;
    I2C_Time_Ovr = Timer1_Ovr;
        //  Фиксируем время запуска программы.
    while ( Read_i2c_time() == 4 )  ;
        // Для вывода времени в режиме "A1".
    msg_reg.time = c_time ;

   Mashtab_Dat () ;

//------------- Для Регулятора Положения --------------

#ifdef _REG_POL
      Ugol = 0 , ZUgol = 0 ;
      ZIUgol = 0 ;
      Integr_RP = 0 , OuRP = 0 ;
      RP_in_sqr = 0 ;
       //  для  ЗИ-РП
      //Set_ZI ( &zi_rp , 0 ) ;
      //zi_rp.time = timer1 ;
      //zi_rp.temp_p_razg = &_r.T_ZIP_Razg ;
      //zi_rp.temp_p_torm = &_r.T_ZIP_Torm ;
      //zi_rp.temp_m_razg = &_r.T_ZIP_Razg ;
      //zi_rp.temp_m_torm = &_r.T_ZIP_Torm ;
      //zi_rp.temp_parabola = 0 ;
#endif

//--------------- Для Регулятора Скорости -------------

       //  для  ЗИ-РC
      Set_ZI ( &zi_rs , 0 ) ;
      zi_rs.time = timer1 ;
      // Триггера для замены темпов ЗИС .
      Shtat_temp = 1 ;
      Fors_temp  = 0 ;
      Reviz_temp = 0 ;
#ifndef _WM591
      zi_rs.temp_p_razg = &_r.T_ZISkorP_Razg ;
      zi_rs.temp_p_torm = &_r.T_ZISkorP_Torm ;
    #ifndef _ZI_4TEMPA
      zi_rs.temp_m_razg = &_r.T_ZISkorP_Razg ;
      zi_rs.temp_m_torm = &_r.T_ZISkorP_Torm ;
    #else
      zi_rs.temp_m_razg = &_r.T_ZISkorM_Razg ;
      zi_rs.temp_m_torm = &_r.T_ZISkorM_Torm ;
    #endif
#else
      zi_rs.temp_p_razg = &TempRazg ;
      zi_rs.temp_p_torm = &TempRazg ;
      zi_rs.temp_m_razg = &TempRazg ;
      zi_rs.temp_m_torm = &TempRazg ;
#endif
    #ifndef _KTEV
      zi_rs.temp_parabola = &_r.T_ZISkor_Parab ;
      zi_rs.temp_parabola_delta = &_r.T_ZISkor_Parab_delta ;
    #else
      zi_rs.temp_parabola = 0 ; // адрес = 0, сама уставка
    #endif                      // в UST_CNST.H игнорируется .

        RegFlg.all = 0 , OuIchRS = 0 ;
        Delta_Sk = 0 , OuIchRS_k = 0 ;
        Z_Skor = 0x0 , OuRegS = 0 , OuRegS_dop_kod = 0 ;
        ZISkor = 0x0 ;
        Skor = 0x0   ;
        S.flg.all = 0 ;
        TG = 0 ;
#ifndef _WM591
        Filtr_Sk ( 0 ) ;

   #ifdef bi_RS_P // для адаптивного РС ( П и ПИ по команде ) :
        _r_KRSP = _r.KRSP_for_P & 0x7fff; // защита от "-" коэфф.
   #endif

#endif //  _WM591

//------------------- Для РТ ----------------------
      UdSr = 0;
      EDS = 0, EDS_shest_kod = 0, ZNEDS = 0 ,  EDS_P = 0 ;
      IDV = 0 ;
#ifdef  _SIFU2_
      IDV2 = 0 ;
#endif
      ZnEDS_P = 0 ;
      time_Id_max = Puls_counter ;

      // Инициализация флагов дополнительных измерений тока для Автонастройки и Контроля открытия тиристоров .
      // В дальнейшем каждый процесс будет по мере надобности инициализировать свой флаг .
      flg_RaTe.all = 0;
      //---
#ifdef   _AVTONASTR  // Для автонастройки.
     // 12.11.2008 11:34 : DAN - Во время переключения областей уставок принимались типовые ,
     // из-за того что программа меняла сами уставки РТ .
     // K_perereg_AN_old = _r.K_perereg_AN ;
    kn_Label = 0 , kp_Label = 0 , kpr_Label = 0 ;
    Id_AN_imp = 0 ;
#endif
#ifdef  Id_sr_ach
      Id_sr = 0 ;
#endif
#ifdef  Id2_sr_ach
      Id2_sr = 0 ;
#endif

       //  для  ЗИ-РТ
      //Set_ZIRT ( &zi_rt , 0 ) ;
      //zi_rt.time = timer1 ;
      //zi_rt.temp_p = &_r.Temp_RT_P ;
      //zi_rt.temp_m = &_r.Temp_RT_M ;

      OIRT_drob = 0 ;
      Id_dop_kod = 0;
#ifndef _KTE_GD
      ZIDN  = ZIDN1 = 0 ;  // выход ЗИ-РТ.
      OIRT  = _r.RevU0  ;  // интегратор регулятора тока
      OIRT1 = _r.RevU0  ;  // интегратор регулятора тока
      ORT   = 0x2000;      // выход регулятора тока
      IDN = 0 , IDN1 = 0 ;
   #ifdef _SIFU2_
       OIRT_drob_2_ = 0 ;
       ZIDN_2_  = ZIDN1_2_ = 0 ;  // выход ЗИ-РТ.
       OIRT_2_  = _r.RevU0  ;  // интегратор регулятора тока
       OIRT1_2_ = _r.RevU0  ;  // интегратор регулятора тока
       ORT_2_   = 0x2000;      // выход регулятора тока
       IDN_2_ = 0 , IDN1_2_ = 0 ;
       //---
       // Для одновременного изменения коэффициентов РТ :
       ust_rINN0   = _r.INN0 ;
       ust_rKRTP   = _r.KRTP ;
       ust_rKRTPRI = _r.KRTPRI ;
       ust_rKRTNI  = _r.KRTNI  ;
   #endif
#else
      Ig_full = _AD_BUSY ;
      AD_Izm (  Ig_ach   , &Ig_full  ) ; // зарядка первого ИЗМЕРЕНИЯ "Ig"
      Ug_full = _AD_BUSY ;
      AD_Izm (  Ug_ach   , &Ug_full  ) ; // зарядка первого ИЗМЕРЕНИЯ "Ug"
      Ugx_full = _AD_BUSY ;
      AD_Izm (  Ugx_ach   , &Ugx_full  ) ; // зарядка первого ИЗМЕРЕНИЯ "Ugx"
 #ifdef Udv_ach  // Измерение напряжения на двигателе
      Udv_full = _AD_BUSY ;
      AD_Izm (  Udv_ach   , &Udv_full  ) ; // зарядка первого ИЗМЕРЕНИЯ "Udv"
 #endif
         // для  ЗИ-РTg
      Set_ZI ( &zi_rtg , 0 ) ;
      zi_rtg.time = timer1 ;
      zi_rtg.temp_p_razg = &_or.T_ZIRTg_P ;
      zi_rtg.temp_p_torm = &_or.T_ZIRTg_M ;
      zi_rtg.temp_m_razg = &_or.T_ZIRTg_P ;
      zi_rtg.temp_m_torm = &_or.T_ZIRTg_M ;
      zi_rtg.temp_parabola = 0 ; // адрес = 0, сама уставка в OBJ.H игнорируется .

      Igen  = 0 , Ugen = 0 , Udv = 0 ;
      IDV_g = 0 ;
      IDN_g = 0 ;
      OIRT  = 0 ;  // интегратор регулятора тока
      Integr_rn = 0 ;
      Integr_rn_drob = 0 ;
      ORT = 0 ;
      Ug_zx = 0 , Out_rn = 0 ;
      Ig_forUgz_Out = 0 , Ig_forUgzR_Out = 0 ; // Для структуры с одним РНг
#endif

#ifdef _RVId
      RVId.Id1_full = _AD_BUSY;
      mAD_Izm( Id1_ach, &RVId.Id1_full ); // ИЗМЕРЕНИЕ  "Id1"
      RVId.Id2_full = _AD_BUSY;
      mAD_Izm( Id2_ach, &RVId.Id2_full ); // ИЗМЕРЕНИЕ  "Id2"
      RVId.dId = RVId.dIf = RVId.Integr = RVId.Drob = RVId.Out = RVId.dIfz = 0;
      RVId.Time = Puls_counter;
      RVId.Iv1_z = RVId.Iv1_zad = RVId.Iv1_dlt = RVId.Iv1_korr = 0;
      RVId.Iv2_z = RVId.Iv2_zad = RVId.Iv2_dlt = RVId.Iv2_korr = 0;
      RVId.Id1 = RVId.Id2 = RVId.IDV1 = RVId.IDV2 = 0;
      RVId.flg.all = 0;
#endif

//-------------  Для автонастройки  ---------------------------------
#ifdef   _AVTONASTR
       Avtonastroyka_RT ( 0 ) ;
#endif

//-------------------------- Для Реверса Поля --------------------------------

 #ifdef _Rev_Pola   // если включен алгоритм реверса поля.
      RP_Pz.all = 0 ;  // переменная признаков для реверса поля.
      Time_RP = Timer1_Ovr ;
#endif

//------------------ Для Регулятора Деления Нагрузки -------------------------

#ifdef  _RDN
 #ifdef Id_2v_ach  // Измерение канала Id-2вал :
    Id_2v_full = _AD_BUSY ;
    AD_Izm (  Id_2v_ach   , &Id_2v_full  ) ; // зарядка первого ИЗМЕРЕНИЯ "Id-2вал"
 #endif
    RDN_Out = 0 , dId = 0 ;
#endif

//----------- Для Фильтра Статического Тока -----------
#ifdef  _DST
    puls_Istat = 0 ;
    Id_Din  = 0 ;
    Id_Stat = 0 ;
    Sk1 = dSkor = 0;
    Time_stat  =  timer1 ;
    Id_Stat_flt.in    = &Id_Stat ;
    Id_Stat_flt.tau   = &_r.T_flt_Stat ;
    Id_Stat_flt.first =  0 ;
#endif

//--------------- Для Регулятора Рассогласования Скорости (ЛЫЖА) -------------
#ifdef  _RRS
    liga.all  = 0 ;
   #ifdef Id_stat_2v_ach
    Id_Stat2_flt.in    = &Id_Stat2 ;
    Id_Stat2_flt.tau   = &_r.T_flt_Stat ;
    Id_Stat2_flt.first =  0 ;
   #endif
    Id_stat_2v = 0 ;
#endif

//-------------------------- Для Контроля Буксовки ---------------------------

#ifdef  _BUKSOVKA
 #ifdef N_2v_ach  // Измерение канала N-2вал :
    N_2v_full = _AD_BUSY ;
    AD_Izm (  N_2v_ach   , &N_2v_full  ) ; // зарядка первого ИЗМЕРЕНИЯ "N-2вал"
 #endif
#endif

//----------------------- Для Включения Вентиляторов -------------------------
//--------------------- по синалам перегрева тиристоров ----------------------

#ifdef bi_PT
  #ifdef bo_Vkl_Vent
    bo_Vkl_Vent = 1 ;  // включение охлаждения при запуске контроллера.
    Time_t_tir = Timer1_Ovr ;
  #endif
#endif

#ifdef bi_PT2
  #ifdef bo_Vkl_Vent2
    bo_Vkl_Vent2 = 1 ;  // включение охлаждения при запуске контроллера.
    Time_t_tir2 = Timer1_Ovr ;
  #endif
#endif

//----------------------- Для Включения Вентиляторов -------------------------
//------------------------- по токам силовых мостов --------------------------

#ifdef bo_VklVent
    bo_VklVent = 1 ;  // включение охлаждения при запуске контроллера.
    timerVent = Timer1_Ovr ;
#endif

#ifdef bo_VklVent2
    bo_VklVent2 = 1 ;  // включение охлаждения при запуске контроллера.
    timerVent2 = Timer1_Ovr ;
#endif

//---------------- Для Контроля питания Усилителей импульсов Выходных Каскадов  -------------------
#ifdef  bi_KP
    Time_KP = Timer1_Ovr ;
#endif

// Для ШС2 в 12-пульсном СИФУ :
#ifdef  bi_KP2
    Time_KP2 = Timer1_Ovr ;
#endif

// Для ШС3 в 12-пульсном СИФУ :
#ifdef  bi_KP3
    Time_KP3 = Timer1_Ovr ;
#endif

// Для ШС4 в 12-пульсном СИФУ :
#ifdef  bi_KP4
    Time_KP4 = Timer1_Ovr ;
#endif

// Для тиристоров КЗ в АТК Роторном выпрямителе :
#ifdef  bi_KP_KZ
    Time_KP_KZ = Timer1_Ovr ;
#endif
//-------------------------------------------------------------------------------------------------

//-------- Для аналоговых измерений температуры каждого охладителя в каждом силовом шкафу ---------

    T_Izm_Dat ( 0 ) ; // Инициализация измерений и количества каналов .

//-------------------------------------------------------------------------------------------------

#ifndef _WM591
//--------------- Для Регулятора ЭДС -------------

      V.flg.all  = 0 ;
      V.Fv_zad   = _Fv_nom( 1.00 ) ;
      V.Iv_zad   = _Iv_nom( 1.00 ) ;
      V.Fv       = _Fv_nom( 1.00 ) ;
      V.Alfa_Old = _Grad( 180 ) ;
//#ifdef _Vozb_KTE
      V.Integr_rt= _Grad( 180 ) ; // Для индикации в стандартном MSG_TABL.H .
//#endif
      Zad_EDS = _r.Z_EDS ;
      Integr_REDS = _Fv_nom( 1.00 ) ;
      OutRSMaxM1 = _r.OuRSMaxMost1 ;
      OutRSMaxM2 = _r.OuRSMaxMost2 ;
      //S_Reg.all = 0   ;
      //Ki_RS =  _r.KRSI ;
      //Kp_RS =  _r.KRSP ;
      //Ki_reds = _r.Ki_REDS ;
      //Kp_reds = _r.Kp_REDS ;
      KFE = 0x02u ;
      pFE = 1 ;

//---------------- Для Задания ---------------

    zad_res.out = 0 , zad_res.shift = 2 , zad_res.porog = 10 , zad_res.ach = &Zad_res_ach ;
    trig.all = 0 ;

    Zad_Skor_4_20 ( 0 ) ; // инициализация Задания токовой петлёй 4-20 мА .

#endif //_WM591

//ДДДДДДДДДДДДДД Для Тепла ДДДДДДДДДДДДДДДД

  Teplo_Programm ( 0 )  ;

//------------------- Для Циклов ------------------

  Ckl.all = 0 , YKST = 0/*CiklTab*/ ,   SCHCIKL = 0x0u, c_index = 0xff, YKSTc = 1;

  TCIKL  = 0x0006 ;
  //CiklTab[ 0 ] = 0 ; //0x0020 - Т.к. в циклах задаются свои начальные условия, то элемент обнуляем.
  //CiklTab[ 1 ] = 0 ;
  //CiklTab[ 2 ] = 0 ;
  for ( ax = 0 ; ax < _CiklLong ; ax++ ) CiklTab[ax] = 0 ;
  //---------------------Для Геркона----------------------------

#ifdef  _CM3_
    Init_Gercon () ;
#else
    Set_Gercon_Level( Falling );
    Set_Gercon_Level1( Falling );
#endif
    Set_Gercon_Priority();
    Gercon_Int_Enable();
    Gercon_Int_Enable1();

  //------------------------------------------------------------
  #ifdef _WM591

  PPG_Prt_out0.num = 2;
  PPG_Prt_out1.num = 3;
  PPG_Prt_out2.num = 4;

  PPG_Prt_out0.max = _Id_nom(3.33);
  PPG_Prt_out1.max = _Ud_nom(1.66);
  PPG_Prt_out2.max = 2000;

  PPG_Prt_out0.val = &Id_dop_kod;
  PPG_Prt_out1.val = &UdSr;
  PPG_Prt_out2.val = &PPG_strob;

  PPG_Prt_out0.low = 0;
  PPG_Prt_out1.low = 0;
  PPG_Prt_out2.low = 0;

  PPG_Prt_out0.high = 0;
  PPG_Prt_out1.high = 0;
  PPG_Prt_out2.high = 0;

  out_go = 0;

  PPG_Prt_in0.max = _Id_nom(3.33);
  PPG_Prt_in1.max = 250;

  PPG_Prt_in0.mask = 0x7f;
  PPG_Prt_in1.mask = 0xbf;

  PPG_Prt_in0.ICS_reg = &ICS01;
  PPG_Prt_in1.ICS_reg = &ICS23;

  PPG_Prt_in0.time_reg = &IPCP1;
  PPG_Prt_in1.time_reg = &IPCP2;

  PPG_Prt_in0.val = &INN;
  PPG_Prt_in1.val = &OIRT1;

  TempRazg = _r.T_ZISkorP_Razg;
  Id_z_old = 0 ;

  INN = 0;
  OIRT1 = 0;

  #endif
  //------------------------------------------------------------
    return ;
  }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void  Mashtab_Dat ( void )
{
 //-------------
 #ifndef _AD_ROT
 //-------------
        // Вычисление коэфф. масштабирования по номиналам Id, Ud и Iv.

      Mashtab.Id = (slw)(sw)_mc.Mashtab_Id * (slw)(sw)_sr.Dat.Id  /  (sw)_sr.NOM.Id.fe ;
      Mashtab.Id_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Id / (sw)256 ;

      Mashtab.Ud = (slw)(sw)_mc.Mashtab_Ud * (slw)(sw)_sr.Dat.Ud  /  (sw)_sr.NOM.Ud.fe ;
      Mashtab.Ud_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Ud / (sw)256 ;

      Mashtab.Iv = (slw)(sw)_mc.Mashtab_Iv * (slw)(sw)_sr.Dat.Iv  /  (sw)_sr.NOM.Iv.fe ;
      Mashtab.Iv_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Iv / (sw)256 ;

#ifdef _KTE_GD
      Mashtab.Ig = (slw)(sw)_mc.Mashtab_Ig * (slw)(sw)_sr.Dat.Ig  /  (sw)_sr.NOM.Ig.fe ;
      Mashtab.Ig_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Ig / (sw)256 ;

      Mashtab.Ug = (slw)(sw)_mc.Mashtab_Ug * (slw)(sw)_sr.Dat.Ug  /  (sw)_sr.NOM.Ug.fe ;
      Mashtab.Ug_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Ug / (sw)256 ;
#endif

    //---------------------------------------------------------------------------------------

#ifdef _KTE
  #ifdef _AVTONASTR
      AN_Kreg () ; // Вычисление коэффициентов РТ с помощью АН .
  #endif
    //---------------
    //01.03.2017 - Коэффициенты РТ берутся из двух мест :
      if ( _r.Cfg._.RT_Anastr == 1 )
      {
            // Коэффициенты , полученные с помощью АН , рассчитываемые , но не доступные к изменению с пульта :
            _r_KRTPRI = an_KRTPRI;
            _r_KRTNI  = an_KRTNI ;
            _r_KRTP   = an_KRTP ;
            // ---
  #ifdef  _SIFU2_ // Для 12ти пульсной системы с РТ2 или отдельной работы вторым мостом :
            _or_KRTPRI_2_ = an_KRTPRI_2_;
            _or_KRTNI_2_  = an_KRTNI_2_ ;
            _or_KRTP_2_   = an_KRTP_2_ ;
  #endif
      }
      else
      {
            // Коэффициенты из уставок , доступные к изменению с пульта .
            _r_KRTPRI = _r.KRTPRI;
            _r_KRTNI  = _r.KRTNI ;
            _r_KRTP   = _r.KRTP ;
            // ---
  #ifdef  _SIFU2_ // Для 12ти пульсной системы с РТ2 или отдельной работы вторым мостом :
            _or_KRTPRI_2_ = _or.KRTPRI_2_;
            _or_KRTNI_2_  = _or.KRTNI_2_ ;
            _or_KRTP_2_   = _or.KRTP_2_ ;
  #endif
      }
    //---------------
#endif

#ifdef  _SIFU2_  // Для номинала в абсолютных единицах для ШС1 и ШС2 в 12-пульсной схеме :
      Id_divBy2_abs = (sw)_sr.NOM.Id.fe/2 ;
      //-----------------------------------

       // Для одновременного изменения коэффициентов РТ :
       if ( ust_rINN0 != _r.INN0 ) // момент изменения уставки :
       {
            ust_rINN0  = _r.INN0 ;
            if ( _r.Cfg2._.RT1_RT2sovm == 1 ) _or.INN0_2_ = _r.INN0 ; // Изменение уставки РТ2 синхронно с РТ1 .
       }
       //---
       if ( ust_rKRTP != _r.KRTP ) // момент изменения уставки :
       {
            ust_rKRTP  = _r.KRTP ;
            if ( _r.Cfg2._.RT1_RT2sovm == 1 ) _or.KRTP_2_ = _r.KRTP ; // Изменение уставки РТ2 синхронно с РТ1 .
       }
       //---
       if ( ust_rKRTPRI != _r.KRTPRI ) // момент изменения уставки :
       {
            ust_rKRTPRI  = _r.KRTPRI ;
            if ( _r.Cfg2._.RT1_RT2sovm == 1 ) _or.KRTPRI_2_ = _r.KRTPRI ; // Изменение уставки РТ2 синхронно с РТ1 .
       }
       //---
       if ( ust_rKRTNI != _r.KRTNI ) // момент изменения уставки :
       {
            ust_rKRTNI  = _r.KRTNI ;
            if ( _r.Cfg2._.RT1_RT2sovm == 1 ) _or.KRTNI_2_ = _r.KRTNI ; // Изменение уставки РТ2 синхронно с РТ1 .
       }

#endif

 //-------------
 #else
 //-------------
  //  для фильтра.
  static word time;
  static double drob;
         word bx, dt;
         double dax;
         float fax, fbx;

        // Вычисление коэффициентов масштабирования по номиналам Id, Ud . А также расчет Z, R и L .
        // ----
        // В паспортных данных АД приведены действующие значения . Вычисляем масштаб Id
        // для действующего значения тока :
        // Максимальное измеренное значение с датчика также вычисляется действующее , т.к. максимальное среднее
        // всё равно будет больше ...
               //---------------------------------------------------------------
               // Для перевода действующего в среднее значение используем формулу :
               //        ___
               //       ы 3
               //  Id = ----- * Iдействующее = 1.22474 * Iдействующее .
               //       ы 2
               //
               // 05.11.2019 - Перевод в действующее пока не делаем , т.к. при этом возникает
               // большая путаница - как считать "Id-макс" и Геркон ...
               // Mashtab.Id = 1.22474 * 1.151*256 * Iном-ДТ / Iном-Двиг .
               //---------------------------------------------------------------
        // ----
        // 25.04.2019 - Номиналы согласованы с Грыгорычем :
        // ДТ настраиваем на 1.7 В - амплитудное значение при номинале .
        // ДН настраиваем на 4.0 В - амплитудное значение при номинале .
        // ----
        // Mashtab.Id = 1.151*256 * Idном-ДТ / Idном-АТК .
      Mashtab.Id = (slw)(sw)_mc.Mashtab_Id * (slw)(sw)_sr.Dat.Id / (sw)_sr.NOM.Id.fe ;
      Mashtab.Id_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Id / (sw)256 ;

        // ----
        // Mashtab.Ud = 0.978*256 * Uном-ДТ / Uном-АТК .
      Mashtab.Ud = (slw)(sw)_mc.Mashtab_Iv * (slw)(sw)_sr.Dat.Ud  /  (sw)_sr.NOM.Ud.fe ;
      Mashtab.Ud_max = (slw)(sw)_AD_MAX * (slw)(sw)Mashtab.Ud / (sw)256 ;

        // 13.01.2022 - Масштаб тока ротора вычисляем исходя из той величины , на которую настроет датчик тока Id АТК :
        // Mashtab.Irot = Mashtab.Id * Idном-АТК / Id-двиг .
        // Mashtab.Irot = Mashtab.Id * Idном-АТК / (I-ном-rot/0.816) .
      Mashtab.Irot = (sw)((float)(sw)Mashtab.Id * (float)(sw)_sr.NOM.Id.fe /((float)_or.I_rot_nom/(float)_sqr2_3mask)) ;

      //------------------------------
      // Фильтр частоты сети ротора :
      //if ( _or.Frot_Tfiltr != 0 ) // 50мсек , 1 дискр. = 1 мсек .
      if ( _or.CfgO._.Vedushiy == 0 )       
      {
        bx = timer1 ;  dt = bx - time ;   time = bx ;  // запись момента текущей отработки фильтра.
        if ( dt >= _MkSec(10*1000) )  dt = _MkSec(10*1000) ;  // для первого входа, когда time еще не проинициализирован.
        
        dax  = (d)Frot + drob ;
        //  приводим dt от "мксек" к "мсек" _or.Frot_Tfiltr: 1дискр.=1мсек
        dax += (d)( nFrot - Frot ) * (d)(w)dt / (d)_MkSec(1000) / (d)(w)/*_r.Frot_Tfiltr*/50 ;
        
        Frot = (float)dax ;
        drob =  dax  - (d)Frot ;
      }
      
      //----------------------------------------------- Скрипт Грыгорыча ------------------------------------------------------

      //------------------------------------------- Число пар полюсов -----------------------------------------
      // Число пар полюсов находим как целочисленное частное Максимальной Синхронной скорости ( 3000 об/ мин )
      // для двигателя с 1 парой полюсов к Номинальной скорости двигателя .                  // Например :
                                                                                             // 3000 ->  Z = 1
      //---                                                                                  // 1500 ->  Z = 2
      Pary_AD = (w)3000 / _sr.NOM.N.fe ;                                                     // 1000 ->  Z = 3

      //-----------------------------
      // Круговая частота сети w0 , рад/с :
      //
      //   wном = 2 * _PI * f
      //
      OmegaNom = (float)2 * _PI * 50 ; //Syn.Fsyn/360 - измерять частоту сети нет смысла ...

      //-----------------------------
      // Синхронная скорость , рад/с :
      //
      //         wном
      //   w0 = ------
      //          Z
      //
      OmegaNullSynhr = (float)OmegaNom / (float)(w)Pary_AD ;

      //------------------------------
      // Скорость ротора в относительных единицах ( от синхронной ) :
      //
      //               wрот * 100%
      //   wрот, % =  -------------
      //                    w0
      //
       
      if ( !_or.CfgO._.Vedushiy )
      {
        SkorRot = (sw)( (float)OmegaRot * (float)(w)_Skor_Nom / (float)OmegaNullSynhr ) ;
        // Скорость ротора в Об/мин :
        N_ob_min = _RadS_ObMin * OmegaRot ;
        // Максимальное приращение пилы за такт :
        drad0 = OmegaNom * _Ts ;
      }
      else
      {
        SkorRot =  Ndpr;
        N_ob_min = (float)_sr.NOM.N.fe *((float)Ndpr/(float)_Skor_Nom);
      }
      fax = ((float)_sr.NOM.N.fe* 0.9)/60.0;
      fbx = ((float)_Enc_base_time/(float)_MkSec(1))*1e-6;
      dN_max = fax*fbx*0x1fff;
      //------------------------------

      //------------------------------

      //----------------------------------- Перегрузочная способность -----------------------------------------
      // Перегрузочная способность - отношение Критического Момента к Номинальному
      //
      //                   Ммакс
      // _or.Km  ->  Км = ------- = 1.8...2.5 ед.
      //                   Мном


      //--------------------------------- Коэффициент трансформации двигателя ---------------------------------
      //
      //       0.95 * Uстат.ном
      // Кt = ------------------
      //              Uрот.ном
      //
      Kt = (float)0.95 * (float)(w)_sr.NOM.Iv.fe / (float)(w)_sr.NOM.Ud.fe ;

      //------------------------------- Номинальный Момент двигателя , Н*м -------------------------------------
      //
      //           9.55 * Pном
      //   Mном = -------------
      //               Nном
      //
      // Перевод об/мин в рад/c и Мощности из кВт в Вт -> 9.55*1000
      Mnom = (w)( (lw)(w)_or.Pnom * 1000 * _RadS_ObMin / (lw)(w)_sr.NOM.N.fe ) ;

      //--------------------------------- Номинальное Скольжение двигателя ------------------------------------
      //
      //          3000
      //          -----  - Nном
      //            Z
      //  Sном = ---------------
      //              3000
      //              -----
      //                Z
      //
      // Для рассчета Скольжения Синхронную скорость ротора в радианах переводим в Об/мин :
      SlipNom = ((float)_RadS_ObMin * OmegaNullSynhr - (float)(w)_sr.NOM.N.fe) / (float) (_RadS_ObMin * OmegaNullSynhr) ;

      //--------------------------------------------------------------------------------------------------------
      // Активное сопротивление фазы статора :
      //
      //       Uстат.ном * Sном
      // r1 = ------------------
      //        ы3 * Iстат.ном
      //
      r1 = (float)(w)_sr.NOM.Iv.fe * (float)SlipNom / (float)( _sqr3_mask * (float)(w)_or.Istat/10 ) ;
      // 10 - основание для дробной части тока статора .

      //--------------------------------------------------------------------------------------------------------
      // Активное сопротивление фазы ротора :
      //
      //       wном * Mном * Sном
      // r2 = --------------------
      //       3 * Iрот.ном^2 * Z
      //
      r2 = (float)(OmegaNom * (float)(w)Mnom * SlipNom) / (float)( 3 * (float)(w)_or.I_rot_nom * (float)(w)_or.I_rot_nom * (float)(w)Pary_AD ) ;

      //--------------------------------------------------------------------------------------------------------
      // Относительное активное сопротивление , приведенное к ротору :
      //
      //
      //               r1             Iрот.ном
      //  Rsigma = ( ------ + r2 ) * ----------
      //              Kt^2            Uрот.ном
      //
      //
      Rsigma_raschet = (float)(w)_or.I_rot_nom * (float)( r1 / ( Kt * Kt ) + r2 ) / (float)(w)_sr.NOM.Ud.fe ;
      if ((Rsigma_raschet == INFINITY) || (Rsigma_raschet == NAN)) Rsigma_raschet = 0 ;

      //--------------------------------------------------------------------------------------------------------
      // Приведенное к ротору сопротивление индуктивности рассеяния фазы двигателя , в относительных единицах :
      //
      //               Uрот.ном^2 * Z        Iрот.ном     Uрот.ном * Iрот.ном
      //   Xsigma = --------------------- * ---------- = ------------------------
      //            2 * wном * Кm * Mном     Uрот.ном     2 * w0 * Кm * Mном
      //
      //
      Xsigma_raschet = (float)(w)_sr.NOM.Ud.fe * (float)(w)_or.I_rot_nom / (float)( 2 * OmegaNullSynhr * _or.Km * (float)(w)Mnom ) ;
      if ((Xsigma_raschet == INFINITY) || (Xsigma_raschet == NAN)) Xsigma_raschet = 0 ;

      //--------------------------------------------------------------------------------------------------------
      // Первый вход в рассчет Rsigma и Xsigma :
      if ( Rsigma == 0 && Rsigma_korr == 0 && Xsigma == 0 && Xsigma_korr == 0 && trig_first_raschet == 0 )
      {
          if ( _or.Rsigma == 0 ) // В ЭОЗУ нет откорректированного значения Rsigma :
          {
            // Задаем в работу рассчетное значение Rsigma :
            Rsigma = Rsigma_raschet ;
            Rsigma_korr = Rsigma_raschet ;
          }
          else // В ЭОЗУ есть откорректированное значение Rsigma :
          {
            // Задаем в работу запомненное значение Rsigma :
            Rsigma = _or.Rsigma ;
            Rsigma_korr = _or.Rsigma ;
          }
          //----
          if ( _or.Xsigma == 0 ) // В ЭОЗУ нет откорректированного значения Xsigma :
          {
            // Задаем в работу рассчетное значение Xsigma :
            Xsigma = Xsigma_raschet ;
            Xsigma_korr = Xsigma_raschet ;
          }
          else // В ЭОЗУ есть откорректированное значение Xsigma :
          {
            // Задаем в работу запомненное значение Xsigma :
            Xsigma = _or.Xsigma ;
            Xsigma_korr = _or.Xsigma ;
          }
          trig_first_raschet = 1 ; // флаг проведенного первого рассчета .
      }

      //--------------------------------------------------------------------------------------------------------
      //Возможность коррекции рассчетного Rsigma :
      if ( Rsigma_korr != Rsigma ) // Изменили с пульта - принимаем в работу :
      {
           Rsigma = Rsigma_korr ;
           if ( Rsigma_korr != 0 ) _or.Rsigma = Rsigma_korr ;
           else // При обнулении значения возвращаем рассчетное
           {
                 // Задаем в работу рассчетное значение Rsigma :
                 Rsigma = Rsigma_raschet ;
                 Rsigma_korr = Rsigma_raschet ;
                 _or.Rsigma = 0 ;  // и обнуляем уставку коррекции .
           }
      }

      //--------------------------------------------------------------------------------------------------------
      //Возможность коррекции рассчетного Xsigma
      if ( Xsigma_korr != Xsigma ) // Изменили с пульта - принимаем в работу :
      {
           Xsigma = Xsigma_korr ;
           if ( Xsigma_korr != 0 ) _or.Xsigma = Xsigma_korr ;
           else // При обнулении значения возвращаем рассчетное
           {
                 // Задаем в работу рассчетное значение Rsigma :
                 Xsigma = Xsigma_raschet ;
                 Xsigma_korr = Xsigma_raschet ;
                 _or.Xsigma = 0 ;  // и обнуляем уставку коррекции .
           }
      }
      //--------------------------------------------------------------------------------------------------------

 //-------------
 #endif
 //-------------

  return ;
}
