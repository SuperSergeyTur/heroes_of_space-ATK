
//     ОБЪЕКТНЫЕ ПРОГРАММЫ.
//
//--------------------------------------------------------
//    Программа считывания кода текущего резерва для
//  перезагрузки уставок у многорезервных агрегатов.
word read_rezerv ( void )
  {
    register word ax ;

    // Для многорезервных агрегатов ОБЯЗАТЕЛЬНО следующее :
    //   1. На каждую область уставок ДОЛЖЕН БЫТЬ отдельный , самостоятельный дискретный вход .
    //   2. КАЖДЫЙ дискретный вход , для каждой области уставок , должен проверяться в условии .
    //   3. Дискретный вход для определения области уставок должен быть "= 1" , именно "1" ,
    // а не "0" , это важно .
    //   4. В типовых уставках установить инверсию дискретных входов "= 1" .
    //   5. Наличие "ax = 0" обязательно , для того , чтобы определять отсуствующий резерв .
    //   6. Для отсутствующего резерва применить либо "else" без проверки дискретных входов
    // (как в примере ниже) , либо проверить дискретные входы для отсуствующего резерва на "= 0" .
    //   7. В каждой области уставок необходимо будет принять и сохранить Типовые Уставки .

    //if      ( bi_KTE_rezerv1 == 1 ) ax = 1 ;
    //else if ( bi_KTE_rezerv2 == 1 ) ax = 2 ;
    //else                            ax = 0 ;

  // Для раздельной работы 12-пульсной схемы :
  #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
    if      ( bi_Vedusch == 1 && bi_Vedom == 0 && bi_Both == 0 ) ax = 2 ; // ШС1,ШС2
    else if ( bi_Vedusch == 0 && bi_Vedom == 1 && bi_Both == 0 ) ax = 3 ; //           ШС3,ШС4
    else if ( bi_Vedusch == 0 && bi_Vedom == 0 && bi_Both == 1 ) ax = 1 ; // ШС1,ШС2 + ШС3,ШС4
    else                                                         ax = 0 ;
  #else
    ax = 0 ; // если нет резерва
  #endif

    return ax ;
  }
//--------------------------------------------------------


//     ОБЪЕКТНАЯ ПРОГРАММА.

word  ObjPrg ( word num )
  {
  static word ax ;
         word skor ;
         lword lax;
  //---
    if ( num != _Obj_c_Init && num != _Obj_c_Common_avar ) // Инициализация и Общие Аварии в любом случае .
     {
        // Задано ли объектное управление .
      if (  Isp.all != 0 ) return 1 ;
     }
   //----
    switch ( num )
    {    // Стартовая объектная программа для задания начальных условий.
      case _Obj_c_Init :

        canId_zad = 0 ;
        flgO.all = 0 ;
        ATK_flg.all = 0 ;
        OuRegS_ogr = 0 ; // Ограниченное задание на ток от Ведущего к Ведомому .
        Agregat = _V_REZERVE;
        Time_Reversor = Timer1_Ovr ;
        TimeDelay_Temper = Timer1_Ovr;
        Trg_Pusk = 0;
        Pusk_old = 0;
        Trg_IzmTemp = 0;
        Trg_BegTemp = 1;
        T_CAN0 = Timer1_Ovr ;
        Time_RMS_On = Timer1_Ovr;
        Time_RMS_Off = Timer1_Ovr;

        // Инициализируем Kf для определения момента :
        Kform = _sqr2_3mask ; // 0.816

        //---- ДЛя сканирования температуры
        Time_tst  = Timer1_Ovr;
        Time_tst_PIU = Timer1_Ovr;
        Time_bo_SN_On = Timer1_Ovr;
        channelTemp = Izm_seq[0];              // начальный адресс канала
        //   PDF[0].Bits._.Count_Beg = 1;  // начинаем считать температуру с 0-го (1-го) канала
        IzmTempLabel = 0;
        Av_Dat = 0;
        Avv_Dat = 0;
        bo_EndIzm = 0;


        CLR_CS_Temp();                        // Сброс адресса (4х ножек).
        for (ax = 0; ax < _MaxChannel; ++ ax)
        {
          TIzm[ax].Freq = 0 ;
          TIzm[ax].V_Out= 0 ;
          TIzm[ax].Out  = 0 ;
          TIzm[ax].I_Out= 0 ;
        }
        bo_KontrVkl = 0;
        TimeDelay = Timer1_Ovr;
        TimeBlockIzm = Timer1_Ovr;
        for (ax = 0, lax = 1;((lax & _Pr2_Tizm14)== 0)&&(ax <= 31); ++ax)
        {
          lax <<=1;
        }
        //Time_BV = Timer1_Ovr;
        Bit_PrAvar = ax;
        //------- для вентиляторов
        t_fan = 0, Id_fan = 0;
        timerVentAvar = Timer1_Ovr;
        bo_VklVent_1_2_3 = 0; // исп-ся как флаг, вкл/выкл напрямую ножкой bo_vent_otkl/bo_vent_vkl //LPC_GPIO1->SET = 0x01 << 1;
        bo_vent_otkl;
        FanSpeedMax = 1;
        // Включение контактора вентиляторов.
        controlFan(0) ;

        break;
        //-------
         // Объектная программа для задания начальных условий при переходе
        // из Работы в Сб.Готовности.
      case _Obj_c_DS1_Init :
        break;
        //-------
         // Объектная программа перед всеми защитами , например , для зарядки измерений .
      case _Obj_c_Common_avar :

        // Общие Аварии выполняются даже в наладочных режимах и при отключенном объектном управлении :

        // Централизованный сброс всех служебных сообщений :
        mClr_ServiceMsg( _Srv_ATKR_Predupr | _Srv_Err_PereclRegim ) ;
      //mClr_ServiceMsg( _Srv_Err_SA9_PU   | _Srv_ATK_ne_Vybran ) ;   // DAN 12.04.2025
        mClr_ServiceMsg( _Srv_Pusk_off     | _Srv_Link_ATK_otkl ) ;
      //mClr_ServiceMsg( _Srv_Reversor1    | _Srv_Reversor2 ) ;          DAN 12.04.2025
      //mClr_ServiceMsg( _Srv_Reversor1On  | _Srv_Reversor2On ) ;       DAN 12.04.2025
        mClr_ServiceMsg( _Srv_AP2_ne_vRabote ) ;
        mClr_ServiceMsg( _Srv_CAN_avarATK1 | _Srv_CAN_avarATK2 ) ;
        mClr_ServiceMsg( _Srv_CAN_avarATKR | _Srv_NotWorkATK1) ;
        mClr_ServiceMsg( _Srv_NotWorkATKR  | _Srv_ATK1_Predupr ) ;
        mClr_ServiceMsg2( _Srv2_NotWorkATK2| _Srv2_ATK2_Predupr ) ;
        mClr_ServiceMsg2( _Srv2_ErrNumbATK | _Srv2_ErrNumbAbon ) ;
      //mClr_ServiceMsg2( _Srv2_ST1err     | _Srv2_ST2err ) ;         // DAN 12.04.2025
      //mClr_ServiceMsg2( _Srv2_SM1err     | _Srv2_SM2err ) ;         // DAN 12.04.2025
      //mClr_ServiceMsg2( _Srv2_ST1middle  | _Srv2_ST2middle ) ;      // DAN 12.04.2025
      //mClr_ServiceMsg2( _Srv2_SM1middle  | _Srv2_SM2middle ) ;      // DAN 12.04.2025
        mClr_ServiceMsg2( _Srv2_AP2_Predupr ) ;
        if (!Prg._.Gotovn && bo_Avar)
        {
          Trg_Pusk = 0;
        }
        if (bi_Pusk_1)
        {
          if (!Pusk_old)
          {
             Trg_Pusk = 1;
          }
        }
        Pusk_old = bi_Pusk_1;
        if ( bi_VV1_stator     == 0 ) mSet_AvarMsg2( _Av2_VV1_stator ) ;   //DAN 12.04.2025
        if ( bi_VV3_trans      == 0 ) mSet_AvarMsg2( _Av2_VV3_trans ) ;    //DAN 12.04.2025


        /* DAN 12.04.2025
        if ( flgO._.V_rezerve == 1 ) // Если АТК в резерве и сеть отключена , сброс сообщений об отсутствии связи здесь :
        {
          mClr_ServiceMsg( _Srv_NoLinkCAN2_atk1 | _Srv_NoLinkCAN2_atkr ) ;
          mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
        }
        //---
        // Контроль неисправности выбора режимов :
        if ( ( bi_Ludi == 1 && (bi_Gruz == 1 || bi_Negabarit == 1) ) ||
             ( bi_Gruz == 1 && (bi_Ludi == 1 || bi_Negabarit == 1) ) ||
             ( bi_Negabarit == 1 && (bi_Ludi == 1 || bi_Gruz == 1) ) )
        {
          mSet_ServiceMsg( _Srv_Err_PereclRegim ) ;
        }

        // Контроль неисправности б/к силовых переключателей :
        if ( bi_ST1_atk1 == 1 && bi_ST1_atkR == 1 ) mSet_ServiceMsg2( _Srv2_ST1err ) ;
        if ( bi_SM1_atk1 == 1 && bi_SM1_atkR == 1 ) mSet_ServiceMsg2( _Srv2_SM1err ) ;
        if ( bi_ST2_atk2 == 1 && bi_ST2_atkR == 1 ) mSet_ServiceMsg2( _Srv2_ST2err ) ;
        if ( bi_SM2_atk2 == 1 && bi_SM2_atkR == 1 ) mSet_ServiceMsg2( _Srv2_SM2err ) ;

        // Контроль среднего положения силовых переключателей :
        if ( bi_ST1_atk1 == 0 && bi_ST1_atkR == 0 ) mSet_ServiceMsg2( _Srv2_ST1middle ) ;
        if ( bi_SM1_atk1 == 0 && bi_SM1_atkR == 0 ) mSet_ServiceMsg2( _Srv2_SM1middle ) ;
        if ( bi_ST2_atk2 == 0 && bi_ST2_atkR == 0 ) mSet_ServiceMsg2( _Srv2_ST2middle ) ;
        if ( bi_SM2_atk2 == 0 && bi_SM2_atkR == 0 ) mSet_ServiceMsg2( _Srv2_SM2middle ) ;

        // Силовые переключатели находятся внутри ШК , в котором контролируются дверные блокировки ,
        // поэтому , хотя переключатели ST1 , ST2 , SM1 и SM2 в Работе не дернут , контролируются они
        // всегда , т.к. организовать контроль правильности сборки только в Сборке Готовности ,
        // довольно сложно :

        //---
        // Контроль правильности задания номера АТК :
        ax = 0 ;
        if ( _or.CfgO._.ATK1 == 1 ) ax += 0x0001 ;
        if ( _or.CfgO._.ATK2 == 1 ) ax += 0x0010 ;
        if ( _or.CfgO._.ATKR == 1 ) ax += 0x0100 ;
        //---
        // ST1верх = 1 -> ATK1 , SM1верх = 1 -> ATK1 .
        // ST1верх = 0 -> ATKR , SM1верх = 0 -> ATKR .
        // ST2верх = 1 -> ATK2 , SM2верх = 1 -> ATK2 .
        // ST2верх = 0 -> ATKR , SM2верх = 0 -> ATKR .
        //---
        // ST1вниз = 1 -> ATKR , SM1вниз = 1 -> ATKR .
        // ST1вниз = 0 -> ATK1 , SM1вниз = 0 -> ATK1 .
        // ST2вниз = 1 -> ATKR , SM2вниз = 1 -> ATKR .
        // ST2вниз = 0 -> ATK2 , SM2вниз = 0 -> ATK2 .
        //---
        // Формирование сетевого статуса : Ведущий/Ведомый - Ведущий АТК тот , который работает на Двигатель №1 .
        // Проверяем , что силовыми переключателями ST1 , SM1 , ST2 и SM2 в ШК  выбрана та же схема ,
        // что и кулачковым переключателем SA9 на Пульте :
        //---
        switch ( ax )
        {
          //-------------------------------- АТК1 -------------------------------------------------
          case 0x0001 : // АТК1 .
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в 0 грд "Двиг1 + Двиг.2" .
              if      ( bi_Dvig1 == 1 && bi_Dvig2 == 1 )
              {
                // Режим работы "АТК1-АТК2" .
                if      ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - Ведущий , АТК2 - Ведомый , АТКR - в резерве .
                   flgO._.V_rezerve = 0 ; // АТК1 в работе .
                   bo_atkNmbrATK    = 1 ; // Пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 2 ; // AТК2 - наш Абонент .
                   //---
                   //Включаем сеть CAN0 :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если включена уставка - передача статуса Ведущего и работа одним двигателем .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // Вставить проверку того , не сброс ли это аварии , после которой второй АТК находится в работе
                      // сам в послеаварийном однодвигательном режиме .
                 //}
                   //---
                   // Рассчитанный номер Абонента не совпадает с полученным по сети ( при наличии связи ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТК1-АТКрезерв" .
                else if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - Ведущий , АТК2 - в резерве , АТКR - Ведомый .
                   flgO._.V_rezerve = 0 ; // АТК1 в работе .
                   bo_atkNmbrATK    = 1 ; // Пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 3 ; // AТКR - наш Абонент .
                   //---
                   //Включаем сеть CAN0 :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если включена уставка - передача статуса Ведущего и работа одним двигателем .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // Вставить проверку того , не сброс ли это аварии , после которой второй АТК находится в работе
                      // сам в послеаварийном однодвигательном режиме .
                 //}
                   //---
                   // Рассчитанный номер Абонента не совпадает с полученным по сети ( при наличии связи ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТК2-АТКрезерв" или Неправильное положение силовых переключателей .
                else
                {
                     if ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                     {
                       // АТК1 - в резерве , АТК2 - Ведомый , АТКR - Ведущий .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }

                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТК1 в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в -45 грд "Двиг1" .
              else if ( bi_Dvig1 == 1 && bi_Dvig2 == 0 )
              {
                // Режим работы "АТК1" .
                if      ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1                                             &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0                                             )
                          // Положение закоментированных переключателей Двигателя 2 - ST2 и SM2 не имеет значения .
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - Ведущий , АТК2 - в резерве , АТКR - в резерве .
                   flgO._.V_rezerve = 0 ; // АТК1 в работе .
                   bo_atkNmbrATK    = 1 ; // Пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 0 ; // Абонент отсуствует , однодвигательный режим .
                   //---
                   //Отключаем сеть CAN0 для Однодвигательного режима :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // Не выводим сообщение об отключенной связи в нормальном Однодвигательном режиме .
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТКрезерв" или Неправильное положение силовых переключателей .
                else
                {
                     if ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0                                             &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1   && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // Положение закоментированных переключателей Двигателя 2 - ST2 и SM2 не имеет значения ,
                          // однако проверяем , что они не в Резерве , т.к. на резерв может быть только один .
                     {
                       // АТК1 - в резерве , АТК2 - в резерве , АТКR - Ведущий .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТК1 в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в +45 грд "Двиг2" , либо неисправность переключателя SA9 на Пульте .
              else
              {
                     // Неисправность переключателя SA9 на Пульте :
                     if ( bi_Dvig1 == 0 && bi_Dvig2 == 0 )
                     {
                       mSet_ServiceMsg( _Srv_Err_SA9_PU ) ;
                     }
                     // Переключатель SA9 на Пульте в +45 грд "Двиг2" :
                     else
                     {
                       // Режим работы "АТК2" либо "АТКрезерв".
                       if ( (                                             bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1
                                                                       && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 ) ||
                            (                                             bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                                bi_ST1_atkR == 0 && bi_SM1_atkR == 0 &&   bi_ST2_atkR == 1 && bi_SM2_atkR == 1 ) )
                            // Положение закоментированных переключателей Двигателя 1 - ST1 и SM1 не имеет значения ,
                            // однако для режима "Двиг.2 на Резерв" проверяем , что они не в Резерве ,
                            // т.к. на резерв может быть только один .
                       {
                         mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                       }
                       else
                       {
                         // Неправильное положение силовых переключателей .
                         mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                       }
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТК1 в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
              }

              break ;

          //-------------------------------- АТК2 -------------------------------------------------
          case 0x0010 : // АТК2 .
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в 0 грд "Двиг1 + Двиг.2" .
              if      ( bi_Dvig1 == 1 && bi_Dvig2 == 1 )
              {
                // Режим работы "АТК1-АТК2" .
                if      ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 0 ; // АТК1 - Ведущий , АТК2 - Ведомый , АТКR - в резерве .
                   flgO._.V_rezerve = 0 ; // АТК2 в работе .
                   bo_atkNmbrATK    = 2 ; // Пишем свой номер АТК2 в свой статус .
                   flgO._.abonATK   = 1 ; // AТК1 - наш Абонент .
                   //---
                   //Включаем сеть CAN0 :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если включена уставка - передача статуса Ведущего и работа одним двигателем .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // Вставить проверку того , не сброс ли это аварии , после которой второй АТК находится в работе
                      // сам в послеаварийном однодвигательном режиме .
                 //}
                   //---
                   // Рассчитанный номер Абонента не совпадает с полученным по сети ( при наличии связи ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТК2 не управляет Реверсором1 .
                   bo_Reversor2 = 1 ;
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
                // Режим работы "АТК2-АТКрезерв" .
                else if ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 0 ; // АТК1 - в резерве , АТК2 - Ведомый , АТКR - Ведущий .
                   flgO._.V_rezerve = 0 ; // АТК2 в работе .
                   bo_atkNmbrATK    = 2 ; // Пишем свой номер АТК2 в свой статус .
                   flgO._.abonATK   = 3 ; // AТКR - наш Абонент .
                   //---
                   //Включаем сеть CAN0 :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если включена уставка - передача статуса Ведущего и работа одним двигателем .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // Вставить проверку того , не сброс ли это аварии , после которой второй АТК находится в работе
                      // сам в послеаварийном однодвигательном режиме .
                 //}
                   //---
                   // Рассчитанный номер Абонента не совпадает с полученным по сети ( при наличии связи ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТК2 не управляет Реверсором1 .
                   bo_Reversor2 = 1 ;
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТК1-АТКрезерв" или Неправильное положение силовых переключателей .
                else
                {
                     if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                     {
                       // АТК1 - Ведущий , АТК2 - в резерве , АТКR - Ведомый .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }

                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТК2 в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК2 в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТК2 не управляет Реверсором1 .
                   bo_Reversor2 = 0 ;
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в +45 грд "Двиг2" .
              else if ( bi_Dvig1 == 0 && bi_Dvig2 == 1 )
              {
                // Режим работы "АТК2" .
                if      (                                             bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                                                                      bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // Положение закоментированных переключателей Двигателя 1 - ST1 и SM1 не имеет значения /
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - в резерве , АТК2 - Ведущий , АТКR - в резерве .
                   flgO._.V_rezerve = 0 ; // АТК2 в работе .
                   bo_atkNmbrATK    = 2 ; // Пишем свой номер АТК2 в свой статус .
                   flgO._.abonATK   = 0 ; // Абонент отсуствует , однодвигательный режим .
                   //---
                   //Отключаем сеть CAN0 для Однодвигательного режима :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // Не выводим сообщение об отключенной связи в нормальном Однодвигательном режиме .
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТК2 не управляет Реверсором1 .
                   bo_Reversor2 = 1 ;
                   // Режим работы :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТКрезерв" или Неправильное положение силовых переключателей .
                else
                {
                     if (                                             bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                            bi_ST1_atkR == 0 && bi_SM1_atkR == 0 &&   bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                          // Положение закоментированных переключателей Двигателя 1 - ST1 и SM1 не имеет значения ,
                          // однако проверяем , что они не в Резерве , т.к. на резерв может быть только один .
                     {
                       // АТК1 - в резерве , АТК2 - в резерве , АТКR - Ведущий .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТК2 в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК2 в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТК2 не управляет Реверсором1 .
                   bo_Reversor2 = 0 ;
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в -45 грд "Двиг1" , либо неисправность переключателя SA9 на Пульте .
              else
              {
                     // Контроль переключателя SA9 на Пульте :
                     if ( bi_Dvig1 == 0 && bi_Dvig2 == 0 )
                     {
                       mSet_ServiceMsg( _Srv_Err_SA9_PU ) ;
                     }
                     // Переключатель SA9 на Пульте в -45 грд "Двиг1" :
                     else
                     {
                       // Режим работы "АТК1" либо "АТКрезерв" .
                       if ( ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1                                             &&
                              bi_ST1_atkR == 0 && bi_SM1_atkR == 0                                             ) ||
                            ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0                                             &&
                              bi_ST1_atkR == 1 && bi_SM1_atkR == 1   && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 ) )
                            // Положение закоментированных переключателей Двигателя 2 - ST2 и SM2 не имеет значения ,
                            // однако для режима "Двиг.1 на Резерв" проверяем , что они не в Резерве ,
                            // т.к. на резерв может быть только один .
                       {
                         mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                       }
                       else
                       {
                         // Неправильное положение силовых переключателей .
                         mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                       }
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТК2 в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК2 в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТК2 не управляет Реверсором1 .
                   bo_Reversor2 = 0 ;
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
              }
          break ;

          //-------------------------------- АТКR -------------------------------------------------
          case 0x0100 : // АТКR .
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в 0 грд "Двиг1 + Двиг.2" .
              if      ( bi_Dvig1 == 1 && bi_Dvig2 == 1 )
              {
                // Режим работы "АТКрезерв-АТК2" .
                if      ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - в резерве , АТК2 - Ведомый , АТКR - Ведущий .
                   flgO._.V_rezerve = 0 ; // АТКR в работе .
                   bo_atkNmbrATK    = 3 ; // Пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 2 ; // AТК2 - наш Абонент .
                   //---
                   //Устанавливаем Свой сетевой адрес ( АТК1 ):
                   if ( can_setting( _CAN0_Port).addr != 1 )
                   {
                      can_setting( _CAN0_Port).addr = 1 ;
                      can_stop( _CAN0_Port ) = 1; // Отключаем CAN для перезапуска .
                   }
                   //---
                   //Устанавливаем Чужой сетевой адрес :
                   if ( _r.AddrDevice2 != 2 )
                   {
                      _r.AddrDevice2 = 2 ;
                      can_stop( _CAN0_Port ) = 1; // Отключаем CAN для перезапуска .
                   }
                   //---
                   //Включаем сеть CAN0 :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если CAN-связи нет , то пересбрасываем CAN :
                   if ( flgO._.CAN0_ok == 0 && flgO._.CAN0_init == 0 )
                   {
                      flgO._.CAN0_init = 1 ;
                      T_CAN0 = Timer1_Ovr ;
                      can_stop( _CAN0_Port ) = 1;
                   }
                   else if ( flgO._.CAN0_init == 1 )
                   {
                      // Через 1 сек сбрасываем флаг инициализации CAN :
                      if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(1))        flgO._.CAN0_init = 0 ;
                      // Через 0.5 сек включаем CAN :
                      else if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(0.5)) can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если включена уставка - передача статуса Ведущего и работа одним двигателем .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // Вставить проверку того , не сброс ли это аварии , после которой второй АТК находится в работе
                      // сам в послеаварийном однодвигательном режиме .
                 //}
                   //---
                   // Рассчитанный номер Абонента не совпадает с полученным по сети ( при наличии связи ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 1 ;  // АТКR в данном режиме управляет Реверсором1 .
                   bo_Reversor2 = 0 ;  // АТКR в данном режиме не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТК1-АТКрезерв" .
                else if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                {
                   flgO._.Vedushiy  = 0 ; // АТК1 - Ведущий , АТК2 - в резерве , АТКR - Ведомый .
                   flgO._.V_rezerve = 0 ; // АТКR в работе .
                   bo_atkNmbrATK    = 3 ; // Пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 1 ; // AТК1 - наш Абонент .
                   //---
                   //Устанавливаем Свой сетевой адрес ( АТК2 ):
                   if ( can_setting( _CAN0_Port).addr != 2 )
                   {
                      can_setting( _CAN0_Port).addr = 2 ;
                      can_stop( _CAN0_Port ) = 1; // Отключаем CAN для перезапуска .
                   }
                   //---
                   //Устанавливаем Чужой сетевой адрес :
                   if ( _r.AddrDevice2 != 1 )
                   {
                      _r.AddrDevice2 = 1 ;
                      can_stop( _CAN0_Port ) = 1; // Отключаем CAN для перезапуска .
                   }
                   //---
                   //Включаем сеть CAN0 :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если CAN-связи нет , то пересбрасываем CAN :
                   if ( flgO._.CAN0_ok == 0 && flgO._.CAN0_init == 0 )
                   {
                      flgO._.CAN0_init = 1 ;
                      T_CAN0 = Timer1_Ovr ;
                      can_stop( _CAN0_Port ) = 1;
                   }
                   else if ( flgO._.CAN0_init == 1 )
                   {
                      // Через 1 сек сбрасываем флаг инициализации CAN :
                      if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(1))        flgO._.CAN0_init = 0 ;
                      // Через 0.5 сек включаем CAN :
                      else if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(0.5)) can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // Если включена уставка - передача статуса Ведущего и работа одним двигателем .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // Вставить проверку того , не сброс ли это аварии , после которой второй АТК находится в работе
                      // сам в послеаварийном однодвигательном режиме .
                 //}
                   //---
                   // Рассчитанный номер Абонента не совпадает с полученным по сети ( при наличии связи ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТКR в данном режиме не управляет Реверсором1 .
                   bo_Reversor2 = 1 ;  // АТКR в данном режиме управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
                // Режим работы "АТК1-АТК2" или Неправильное положение силовых переключателей .
                else
                {
                     if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                     {
                       // АТК1 - Ведущий , АТК2 - Ведомый , АТКR - в резерве .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }

                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТКR в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ; // АТКR в данном режиме не управляет Реверсором1 .
                   bo_Reversor2 = 0 ; // АТКR в данном режиме не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в -45 грд "Двиг1" .
              else if ( bi_Dvig1 == 1 && bi_Dvig2 == 0 )
              {
                // Режим работы "АТКрезерв" .
                if      ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0                                             &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1   && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // Положение закоментированных переключателей Двигателя 2 - ST2 и SM2 не имеет значения ,
                          // однако проверяем , что они не в Резерве , т.к. на резерв может быть только один .
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - в резерве , АТК2 - в резерве , АТКR - Ведущий .
                   flgO._.V_rezerve = 0 ; // АТКR в работе .
                   bo_atkNmbrATK    = 3 ; // Пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 0 ; // Абонент отсуствует , однодвигательный режим .
                   //---
                   //Отключаем сеть CAN0 для Однодвигательного режима :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // Не выводим сообщение об отключенной связи в нормальном Однодвигательном режиме .
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 1 ;  // АТКR в данном режиме управляет Реверсором1 .
                   bo_Reversor2 = 0 ;  // АТКR в данном режиме не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТК1" или Неправильное положение силовых переключателей .
                else
                {
                     if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1                                             &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0                                             )
                          // Положение закоментированных переключателей Двигателя 2 - ST2 и SM2 не имеет значения .
                     {
                       // АТК1 - Ведущий , АТК2 - в резерве , АТКR - в резерве .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТКR в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТКR в данном режиме не управляет Реверсором1 .
                   bo_Reversor2 = 0 ;  // АТКR в данном режиме не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Переключатель SA9 на Пульте в +45 грд "Двиг2" :
              else if ( bi_Dvig1 == 0 && bi_Dvig2 == 1 )
              {
                // Режим работы "АТКрезерв" .
                if      (                                             bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                            bi_ST1_atkR == 0 && bi_SM1_atkR == 0 &&   bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                          // Положение закоментированных переключателей Двигателя 1 - ST1 и SM1 не имеет значения ,
                          // однако проверяем , что они не в Резерве , т.к. на резерв может быть только один .
                {
                   flgO._.Vedushiy  = 1 ; // АТК1 - в резерве , АТК2 - в резерве , АТКR - Ведущий .
                   flgO._.V_rezerve = 0 ; // АТКR в работе .
                   bo_atkNmbrATK    = 3 ; // Пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 0 ; // Абонент отсуствует , однодвигательный режим .
                   //---
                   //Отключаем сеть CAN0 для Однодвигательного режима :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // Не выводим сообщение об отключенной связи в нормальном Однодвигательном режиме .
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТКR в данном режиме не управляет Реверсором1 .
                   bo_Reversor2 = 1 ;  // АТКR в данном режиме управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // Режим работы "АТК2" или Неправильное положение силовых переключателей .
                else
                {
                     if (                                             bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                                                                      bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // Положение закоментированных переключателей Двигателя 2 - ST2 и SM2 не имеет значения .
                     {
                       // АТК1 - в резерве , АТК2 - Ведущий , АТКR - в резерве .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // Неправильное положение силовых переключателей .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТКR в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТКR в данном режиме не управляет Реверсором1 .
                   bo_Reversor2 = 0 ;  // АТКR в данном режиме не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // Неисправность переключателя SA9 на Пульте :
              else
              {
                   mSet_ServiceMsg( _Srv_Err_SA9_PU ) ;
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // АТКR в резерве .
                   bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТКR в свой статус .
                   flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
                   //---
                   //Отключаем сеть CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 0 ;  // АТКR в данном режиме не управляет Реверсором1 .
                   bo_Reversor2 = 0 ;  // АТКR в данном режиме не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
              }
          break ;

          default : // Номер АТК не задан , или задано больше одного номера .
            mSet_ServiceMsg2( _Srv2_ErrNumbATK ) ;
            flgO._.Vedushiy  = 0 ;
            flgO._.V_rezerve = 1 ; // АТК в резерве до выяснения .
            bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК в свой статус .
            flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
            //---
            //Отключаем сеть CAN0 :
            Agregat = _V_REZERVE ;
            if( can_stop( _CAN0_Port ) == 0 )
            {
                can_stop( _CAN0_Port ) = 1;
            }
            //---
            mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
            //---
            // Выдача разрешений на включение Реверсоров :
            bo_Reversor1 = 0 ;
            bo_Reversor2 = 0 ;
            // Режим работы :
            flgO._.Reg1dvig = 0 ;
            flgO._.dvig_N1 = 0 ;
            flgO._.dvig_N2 = 0 ;
            //---
            bo_Vedushiy = 0 ;
          break ;
        }*/

              // DAN 12.04.2025
              // Флагами иммитируем работу АТК1 в режиме "Двиг1" .
                   flgO._.Vedushiy  = 1 ; // АТК1 - Ведущий , АТК2 - в резерве , АТКR - в резерве .
                   flgO._.V_rezerve = 0 ; // АТК1 в работе .
                   bo_atkNmbrATK    = 1 ; // Пишем свой номер АТК1 в свой статус .
                   flgO._.abonATK   = 0 ; // Абонент отсуствует , однодвигательный режим .
                   //---
                   //Отключаем сеть CAN0 для Однодвигательного режима :
                   Agregat = _ATK1 ;
                 //if( can_stop( _CAN0_Port ) == 0 )
                 //{
                 //    can_stop( _CAN0_Port ) = 1;
                 //}
                   //---
                   // Не выводим сообщение об отключенной связи в нормальном Однодвигательном режиме .
                   //---
                   // Выдача разрешений на включение Реверсоров :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // АТК1 не управляет Реверсором2 .
                   // Режим работы :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 1 ;



        //---------------------------------------------------------------------------------------------------------

        if ( Prg._.Gotovn == 0 ) // В Работе :
        {
            bo_SN_On = 1;
            
            Time_tst_PIU = Timer1_Ovr;
            Time_bo_SN_On = Timer1_Ovr;

          // При аварии одного АТК в 2х двигательном режиме , автоматически снимается Пуск у второго АТК .
          // Т.о. аварийно отключать второй АТК не нужно . не требуется сбрасывать никакие флаги и реле ,
          // реверсоры отключатся сами от пульта .
          //---
          // Если включена уставка - передача статуса Ведущего и работа одним двигателем
          // ( возможно , добавить выдержку времени ) .
        /*if ( _or.CfgO._.Change_Vedush == 1 && flgO._.Reg1dvig == 0 )
          {
            // При Аварии АТК сбрасываем флаги и реле
            // ( возможно , добавить выдержку времени ) :
            if ( bo_AvarATK == 1 )
            {
              flgO._.Vedushiy  = 0 ;
              flgO._.V_rezerve = 1 ; // АТК в резерве до выяснения .
              bo_atkNmbrATK    = 0 ; // В резерве не пишем свой номер АТК в свой статус .
              flgO._.abonATK   = 0 ; // В резерве не пишем номер своего Абонента .
              //---
              //Отключаем сеть CAN0 :
              Agregat = _V_REZERVE ;
              if( can_stop( _CAN0_Port ) == 0 )
              {
                  can_stop( _CAN0_Port ) = 1;
              }
              //---
              mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
              //---
              // Выдача разрешений на включение Реверсоров :
              bo_Reversor1 = 0 ;
              bo_Reversor2 = 0 ;
              // Режим работы :
              flgO._.Reg1dvig = 0 ;
              flgO._.dvig_N1 = 0 ;
              flgO._.dvig_N2 = 0 ;
              //---
              bo_Vedushiy = 0 ;
            }
            //----
            if ( ATK2_Avar == 1 )
            {
              //---
              flgO._.abonATK   = 0 ; // Абонент отсуствует , однодвигательный режим .
              flgO._.Reg1dvig = 1 ;  // Переход в однодвигательный режим .
              //---
              //Отключаем сеть CAN0 для Однодвигательного режима :
              Agregat = _ATK2 ;
              if( can_stop( _CAN0_Port ) == 0 )
              {
                  can_stop( _CAN0_Port ) = 1;
              }
              //---
              // Не выводим сообщение об отключенной связи в нормальном Однодвигательном режиме .
              //---
              // Сброс флага отключенного двигателя и отключение ненужного реверсора :
              if ( Agregat == _ATK2 ) flgO._.dvig_N1 = 0 , bo_Reversor1 = 0 ;
              else                    flgO._.dvig_N2 = 0 , bo_Reversor2 = 0  ;
              //---
              // Если данный АТК был Ведомым ,
              if ( flgO._.Vedushiy == 0 )
              {
                flgO._.Vedushiy = 1 ; // Оставшийся один АТК становится Ведущим .
                //---
                bo_Vedushiy = 1 ;
                //---------
                // Прописать еще инициализацию Интегратора РС .
              }
            }
          }

          // Только после того , как АТК вошел в работу , он начинает интересоваться состоянием второго АТК :
          // При аварии одного АТК в 2х двигательном режиме , автоматически снимается Пуск у второго АТК .
          if ( ATK2_Avar == 1 )
          {
            if      ( ATK2_NmbrATK == 1 ) mSet_ServiceMsg( _Srv_CAN_avarATK1 ) ;
            else if ( ATK2_NmbrATK == 2 ) mSet_ServiceMsg( _Srv_CAN_avarATK2 ) ;
            else                          mSet_ServiceMsg( _Srv_CAN_avarATKR ) ;
          }
          else // Если Аварии абонента нет :
          {
            if ( ATK2_Rabota == 0 ) // второй АТК не в работе , сообщаем о этом :
            {
                // Выводим сообщение об отсутствии готовности второго АТК только при наличии связи :
                if ( flgO._.CAN0_ok == 1 )
                {
                   // Точнее , второй АТК не в работе :
                   if      ( ATK2_NmbrATK == 1 ) mSet_ServiceMsg( _Srv_NotWorkATK1 ) ;
                   else if ( ATK2_NmbrATK == 2 ) mSet_ServiceMsg2( _Srv2_NotWorkATK2 ) ;
                   else                          mSet_ServiceMsg( _Srv_NotWorkATKR ) ;
                }
            }
            else // Второй АТК в Работе , - проверяем , нет ли у него Предупреждения :
            {
                // Если Ведомый АТК в Предупреждении , сообщаем о этом :
                if ( flgO._.Vedushiy == 1 && ATK2_Predupr == 1 )
                {
                    if      ( ATK2_NmbrATK == 1 ) mSet_ServiceMsg( _Srv_ATK1_Predupr ) ;
                    else if ( ATK2_NmbrATK == 2 ) mSet_ServiceMsg2( _Srv2_ATK2_Predupr ) ;
                    else                          mSet_ServiceMsg( _Srv_ATKR_Predupr ) ;
                }
            }
          }
*/
          //----------------------------
          // Для определения Скольжения берем скорость по ПДФ в об/мин .
          // Скорость по ПДФ может стать отрицательной ( например , при противоходе ) ,
          // поэтому берем её по модулю :
          //skor_pdf = PDF[0].out_ob ;
          //if ( (sw)skor_pdf < 0 )  skor_pdf = ~skor_pdf + 1 ;

          skor = Skor ;
          //if ( (sw)skor < 0 )  skor = ~skor + 1 ;
          //N_ob_min = (float)(w)skor / (float)(w)_Skor_Nom * (float)N_ob_minSynhr ;
          //21.12.2020 - N_ob_minSynhr используем вместо _sr.NOM.N.fe , т.к. ПДФ стоит на понижающем валу редуктора ,
          //             т.е. уставка _sr.NOM.N.fe занята под номинальную скорость редуктора .
          //------------------------------
          // Скольжение в относительных единицах :
          //
          //               nсинхр - n
          //   Sрот, % =  ------------ * 1600 дискрет ;
          //                 nсинхр
          //
        //Srot = (sw)( (float)(N_ob_minSynhr - N_ob_min              ) * (float)(w)_Ud_Nom / (float)N_ob_minSynhr ) ;
        //Srot = (sw)( (float)(N_ob_minSynhr - (float)(w)skor_pdf/10 ) * (float)(w)_Ud_Nom / (float)N_ob_minSynhr ) ;

          //---
          // Если двигатель по каким-то причинам раскрутился выше синхронной скорости ,
          // обнуляем скольжение , т.к. оно не может быть отрицательным :
          if ( (sw)Srot < 0 ) Srot = 0 ;
        }
        else // В Сборке Готовности :
        {
          Srot = _Ud_Nom ; // Скольжение , двигатель стоит .
          if ((u)((w)(Timer1_Ovr - Time_tst_PIU)) > _or.Time_ComtrolPIU)
          {
            bo_SN_On = 1;
            Time_tst_PIU = Timer1_Ovr;
          }
          if (Trg_BegTemp)
          {
           bo_SN_On = 1; 
           Trg_BegTemp = 0;
           Time_bo_SN_On = Timer1_Ovr;
          }
          if (Isp.all != 0)
          {
            bo_SN_On = 1;
            Time_bo_SN_On = Timer1_Ovr- _Sec(14);
            Time_tst_PIU = Timer1_Ovr;
          }
          if (bo_SN_On)
          {
            if ((u)((w)(Timer1_Ovr - Time_bo_SN_On)) > _Sec(15))
            {
              bo_SN_On = 0;              
            }
            
          }
          else
          {
            Time_bo_SN_On = Timer1_Ovr;
          }
        }
        //------------------------------------------------------------------------------------------

        //---
        // В Работе , при собранной Цепи ТП , проверяем :
        if ( bo_GotovATK == 1 && bi_QK1 == 1 )
        {
          // Cообщаем об отсутствии Пуска :
          if ( Isp.all == 0 )
          {
            // в Штатном режиме выставляется триггер :
            if ( ATK_flg._.trig_Pusk == 0 ) mSet_ServiceMsg( _Srv_Pusk_off ) ;
          }
          else
          {
            // В Наладочном режиме , например , СИФУ-рез , триггер не нужен , он не выставляется .
            // Контроль Пуска выполняем по самому сигналу Пуск :
            if ( bi_Pusk == 0 )             mSet_ServiceMsg( _Srv_Pusk_off ) ;
          }
          //---
          // При подаче задания проверяем включенное состояние требуемых Реверсоров .
          // Поданное задание определяем по размыканию б/к нулевого положения КЗС , т.к. сигналы "bi_Vpered" и
          // "bi_Nazad" это б/к не ручки КЗС а самих реверсоров :
        /*if ( bi_Null == 0 )  DAN 12.04.2025
          {
            // После подачи задания ждём 0.5 сек и проверяем , включились ли Реверсоры :
            if ( (u)((w)(Timer1_Ovr - Time_Reversor)) > _Sec( 0.5 ) )
            {
              if ( bi_Reversor1 == 0 && flgO._.dvig_N1 == 1 ) mSet_ServiceMsg( _Srv_Reversor1 ) ;
              if ( bi_Reversor2 == 0 && flgO._.dvig_N2 == 1 ) mSet_ServiceMsg( _Srv_Reversor2 ) ;
            }
          }*/
        }
      /*else // Реверсоры не в Работе должны быть отключены :   DAN 12.04.2025
        {
          if ( bi_Reversor1 == 1 ) mSet_ServiceMsg( _Srv_Reversor1On ) ;
          if ( bi_Reversor2 == 1 ) mSet_ServiceMsg( _Srv_Reversor2On ) ;
          //---
          Time_Reversor = Timer1_Ovr ; // Подтяжка таймера для проверки включения Реверсоров .
        }*/
        //----------------------------


        //------------------------ Выдача дискретных сигналов ---------------------------------

        // реле К8 - состояние ВВ3 вакуумного выключателя статора .
        if ( bi_VV3_trans == 1 )
        {
          bo_VV3_trans = 1 , bo_canVV1_stator = 1 ;
        }
        else
        {
          bo_VV3_trans = 0 , bo_canVV1_stator = 0 ;
        }

        //------------------------- Реле малой скорости "РМС" ---------------------------------

        // РМС пока что не используем , а при установке ручки КЗС в нуль идем по ЗИРС до самого конца ,
        // пока не получим сигнал "Положение Тормоза заклинивающего Барабан" = 1 .
        // ---
        // По включению РМС возможна шунтировка ЗИРС для быстрой остановки ...
        if      ( skor <= _or.ReleMalSkor )
        {
          if ((w)((u)(Timer1_Ovr - Time_RMS_On)) >= _Sec(1))
          {
           bo_ReleMalSkor = 0 ;
           bo_SA_canN_min = 0 ;  // DAN 12.04.2025
          }
          Time_RMS_Off = Timer1_Ovr;
        }
        else if ( skor > (_or.ReleMalSkor+_or.GistReleMalSkor ) )
        {
          if ((w)((u)(Timer1_Ovr - Time_RMS_Off)) >= _Sec(1))
          {          
           bo_ReleMalSkor = 1 ;
           bo_SA_canN_min = 1 ;  // DAN 12.04.2025
          }
          Time_RMS_On = Timer1_Ovr;
        }

        //------------------------- Реле скорости "N = 490" ---------------------------------
        if (_or.N_490 < _Skor_nom( 0.1 ))
        {
          _or.N_490 = _Skor_nom( 0.1 );
        }

        if      ( skor > _or.N_490 ) // DAN 12.04.2025
        {
           bo_N_490       = 1 ;
           bo_SA_canN_490 = 1 ;
        }
        else if ((skor < _or.N_490-_Skor_nom( 0.1 )))
        {
           bo_N_490       = 0 ;
           bo_SA_canN_490 = 0 ;
        }

        //----------------- Реле "V нулевая" для отключения Реверсоров ------------------------
        //----- на самом деле реле "Снятие ИУ" , просто на первом ШПМ оно так называлось ------

        // Это шунтирующая цепочка , не позволяющая отключить Реверсоры при установке ручки КЗС в нуль .
        // При включении Реверсоров она не работает , так что собирать ее не нужно .
        // Для отключения Реверсоров недостаточно иметь нулевую скорость , нужно , чтобы ИУ были сняты .
        // Контролируем снятие ИУ для отключения Реверсоров :
        //----
        if ( Otkl_Imp != 0 ) bo_Otkl_Imp = 1 ; // ИУ сняты , можно отключать Реверсоры.
        else                 bo_Otkl_Imp = 0 ;

        //-------------------------------------------------------------------------------------

        // Сигнал "Работа" для платы АР2 . Для другого АТК сигнал "Работа" формируется в CAN_OBJ.C :
        if ( Prg._.Gotovn == 0 && bo_Avar == 0 ) bo_canRabota = 1 /*, bo_atkRabota = 1*/ ;
        else                                     bo_canRabota = 0 /*, bo_atkRabota = 0*/ ;

        if ( KTE2_Avar == 0 )    // Если АР2 находится в работе :
        {
          if ( bo_Avar == 1 ) bo_canAvar = 1 ; // Авария из АР1 передаётся в АР2 .
          else                bo_canAvar = 0 ;
        }

        // 02.08.2017 20:43 - В Роторном Выпрямителе не используется :
        if (  Otkl_Imp != 0 /*S.flg._.ZapretImp == 1*/ ) bo_canSn_Imp = 1 /*, bo_atkSn_Imp = 1*/ ;
        else                                             bo_canSn_Imp = 0 /*, bo_atkSn_Imp = 0*/ ;

        // Инвертор должен передать Пуск своему Роторному Выпрямителю .
        // Пуск для АР2 Роторного Выпрямителя передаём и в наладочном режиме ( при включенных реверсорах , чтобы
        // правильно определить нефазность ротора ) :
        if ( bi_Pusk == 1 || ( (Isp._.SIFU_Res == 1 || Isp._.Cikl == 1) && Prg._.Gotovn == 0 && bi_Reversor == 1 ) )
        {
          bo_canPusk = 1 ; // Передача Пуска Роторному выпрямителю в АР2 .
          bo_canStart = 1;
          bo_atkPusk = 1 ; // Передача Пуска во Второй АТК .
        }
        // 13.04.2017 7:00 - DAN : Снятие ИУ ТОЛЬКО после спадания тока .
        // Снимаем Пуск Роторного только после снятия ИУ Сетевого :
        // 02.08.2017 20:43 - Новая идея Грыгорыча - снять ИУ сначала в роторе , и ток в инверторе спадет :
        else /*if ( Otkl_Imp !=0 )*/
        {
          bo_canPusk  = 0 ;
          bo_atkPusk  = 0 ;
          bo_canStart = 0 ;
        }

        //-------
        // Сигнал "bo_canVpered" пока что не используем .
        // "Вперед"/"Назад" - это б/к самих Реверсоров , а не ручки КЗС , так что разночтений быть не может :
        //if ( bi_Nazad == 1 && bi_Vpered == 0 ) bo_canNazad = 1 ;
        //else                                   bo_canNazad = 0 ;

        // 31.01.2022 - При снятии сигнала "Назад" , до подачи "Вперед" не меняем направления :
 //       if      ( bi_Nazad == 1 && bi_Vpered == 0 ) bo_canNazad = 1 ; //DAN 12.04.2025
 //       else if ( bi_Nazad == 0 && bi_Vpered == 1 ) bo_canNazad = 0 ;
        //-------

        // В наладочных режимах , кроме циклов РС , выставляем бит для Альфа-макс ротора :
        if ( Isp._.SIFU_Res == 1 || (Isp._.Cikl == 1 && Ckl._.RS == 0) )
        {
          bo_canF2_Isp = 1 ; // Альфа-ротора берем из наладочной уставки .
          //---
          bo_canZatormogen = 0 ; // Альфа-ротора отпускаем .
          bo_atkZatormogen = 0 ;
        }
        else
        {
          bo_canF2_Isp = 0 ; // Альфа-ротора в рабочем режиме .
          //---
          // Если задание скорости мизерное и угол не пошел , взводим бит , по которому Угол Ротора ставим в Альфа-макс :
          if ( (sw)ZISkor <= (sw)_or.Z_SkorNull && (sw)ZISkor >= (sw)( ~_or.Z_SkorNull + 1 ) &&
               (sw)Z_Skor <= (sw)_or.Z_SkorNull && (sw)Z_Skor >= (sw)( ~_or.Z_SkorNull + 1 ) &&
               ( S.Alfa_Old >= (_r.S_Alfa_Max - _Grad( 3.0 ))) )
          {
             bo_canZatormogen = 1 ; // Альфа-ротора в Альфа-макс .
             bo_atkZatormogen = 1 ;
          }
          else
          {
             bo_canZatormogen = 0 ; // Альфа-ротора отпускаем .
             bo_atkZatormogen = 0 ;
          }
        }

#ifdef   bo_atkOtkl_Q1
        // Только после сброса защит и перехода в Сборку Готовности .
        // Т.е. пока на АТК , который выдал аварию Отсуствия Силы от Согласующего трансформатора не сбросят аварию , он будет выдавать
        // второму АТК команду отключения Q1 :
        if ( Prg._.Gotovn == 1 ) bo_atkOtkl_Q1 = 0 ; // Сбрасывем флаг отключения Q1 для ведомого АТК .
#endif

        //----------------------------------------------
        // Кнопка "Аварийный стоп" передаётся по сети на второй АТК ( при работе в 2х двигательном режиме ) :
        if ( (Reg_AvarMsg | Reg_AvarMsgFirst) & _Av_Vnesh_Avar )
        {
          bo_atkAvarStop = 1 ;
        }
        else bo_atkAvarStop = 0 ;

        if ( ATK2_AvarStop == 1 && av_label == 0 ) mSet_AvarMsg( _Av_Vnesh_Avar ) ;
        //----------------------------------------------

        if ( Prg._.Gotovn == 0 ) // Выводим сообщение в Работе :
        {
          // Авария из платы АР2 - Роторного выпрямителя :
          if ( KTE2_Avar == 1 && av_label == 0 ) mSet_AvarMsg2 ( _Av2_KTE2 ) ;
          //---
          // Проверяем , вошла ли в работу плата АР2 :
          if ( KTE2_Rabota == 0 ) mSet_ServiceMsg( _Srv_AP2_ne_vRabote ) ;
        }

        // Передаём сброс по сети только при активном флаге Сброса - т.е. всего 1.5сек :
        // 1. Если подан Дистанционный Сброс - даём его на второй АТК :
        // 2. Если Ведомый АТК получил сигнал от Ведущего Дистанционный сброс , передаем его на свой АР2 :
        if ( (bi_DS1 == 1 || ATK2_DS1 == 1) && Av._.DistSbros == 1 )
        {
              bo_canDS1 = 1 , bo_atkDS1 = 1 ;
        }
        else  bo_canDS1 = 0 , bo_atkDS1 = 0 ;

        // Вывод действующего значения для Грыгорыча - номинал 1200 А , при этом 1000 А - действующее значение .
        // Перевод в действующее : Iдейств = Id * ы 2/3  = 0.816 * Id .  DAN 03.06.2016
        //                                                               DAN 03.06.2016
        Id_deystv = (sw)( (slw)(sw)Id_dop_kod * (slw)(sw)(( 0.816 * 256.)) >> 8 ) ;

        //---
        // Если плата АР2 Роторного выпрямителя в состоянии Предупреждения, сообщаем о этом :
        if ( KTE2_Predupr == 1 ) mSet_ServiceMsg2( _Srv2_AP2_Predupr ) ;

        //----
        if ( bi_2P24 != 1 )   //  "КОНТРОЛЬ 2P24"
        {          
          
          if ( bi_AvarUKAV       == 1 ) mSet_AvarMsg2( _Av2_AvarUKAV ) ;     //DAN 12.04.2025
         
          if ( bi_Fsil_set       == 0 ) mSet_AvarMsg2( _Av2_Fsil_set ) ;
        //if ( bi_Fsil_KZ        == 0 ) mSet_AvarMsg2( _Av2_Fsil_KZ ) ;      //DAN 12.04.2025
          if ( bi_SF2            == 0 ) mSet_PreduprMsg2( _Pr2_SF2 ) ;
#ifdef  bi_SF3x
          if ( bi_SF3x           == 0 ) mSet_PreduprMsg2( _Pr2_SF3 ) ;
#endif
        //if ( bi_SF4            == 0 ) mSet_PreduprMsg2( _Pr2_SF4 ) ;       //DAN 12.04.2025
        //if ( bi_Vnesh_AvarPult == 1 ) mSet_AvarMsg( _Av_Vnesh_AvarPult ) ; //DAN 12.04.2025
#ifdef  bi_SF5
          if ( bi_SF5            == 0 ) mSet_AvarMsg2( _Av2_SF5 ) ;
#endif
          if ( bi_KV1            == 1 ) mSet_ServiceMsg( _Srv_KV1_vid_ShI ) ;
          else
          {
            mClr_ServiceMsg2( _Srv_KV1_vid_ShI ) ;
            //---
            if      ( bi_Q1_1 == 1 ) {;}
            else if ( bi_Q1_2 == 1 ) {;}
          }

          if ( bi_Dist_Upr == 0 )       mSet_ServiceMsg( _Srv_Mestnoe ) ;
          else                          mClr_ServiceMsg( _Srv_Mestnoe ) ;
        }
        //----
        // Резервному АТК не даём собрать Готовность .
        if ( flgO._.V_rezerve == 1 )  mSet_PreduprMsg( _Pr_ATK_Rezerv ) ;
        else                          mClr_PreduprMsg( _Pr_ATK_Rezerv ) ;
        T_Izm_Dat() ; // объектная программа сканирования и контроля температуры/напряжения .
        controlFan(1) ;

        break;
        //-------
         // Объектная программа для Сборки Готовности.
      case _Obj_c_Sborka_Gotovn :
         //    Для контроля задания скорости в Сборке Готовности необходимо прием задания
         // писать ниже , в работе , а здесь , в Сборке Готовности , закоменировать "break" .

       ATK_flg._.trig_Pusk = 0 ;
       Time_Pusk =  Timer1_Ovr ;

       ATK_flg._.trig_Reg = 0 ;
       Time_Reg =  Timer1_Ovr ;

     // DAN 13.04.2017 7:00 - Обнуляем все начальные условия :
        mOtkl_Imp( _Start_imp ) ;  // снимаем ИУ
        Prg.all &=  ~(_RegTok | _RegSk ) ; // выключаем все Регуляторы .

        Set_ZI ( &zi_rs , 0 ) ;
        OuIchRS = 0 ;
        ZISkor = 0 ;
        Delta_Sk = 0 , OuIchRS_k = 0 ;
        OuRegS_dop_kod = 0 ;
        OuRegS         = 0 ;

        OIRT_drob = 0 ;     // DAN - 16.06.2016 15:24
        ZIDN = ZIDN1 = 0 ;  // выход ЗИ-РТ.
        OIRT   = _r.RTMAX ;  // интегратор регулятора тока
        OIRT1  = _r.RTMAX ;  // интегратор регулятора тока
        S.Alfa = _r.S_Alfa_Max ;

        Control_Nzad () ;  // Для контроля Задания в Сборке Готовности .

        flgO._.Shunt_Rot = 0 ; // на вскякий случай , если он сам не снялся .
        bo_canShunt_End = 0 ;  // на вскякий случай , если он сам не снялся .
        bo_atkShunt_End = 0 ;  // на вскякий случай , если он сам не снялся .

		break;
        //-------
         // Объектная программа защит, неотключаемая после срабатывания защиты.
      case _Obj_c_Rabota :
        
         mClr_ServiceMsg( _Srv_VR1 ) ;

     // И Ведущий АТК , и Ведомый АТК принимают дискретную команду "Пуск" - как б/к реверсоров .
     // Кроме того , команда "Пуск" проходит при условии , что АР2 в работе и второй АТК в работе либо однодвигательный режим :
     // При аварии одного АТК в 2х двигательном режиме , автоматически снимается Пуск у второго АТК .
     if ( bi_Pusk == 1 && KTE2_Rabota == 1 )
     {
        if (  ATK_flg._.trig_Pusk == 0 && ( (u)((w)(Timer1_Ovr - Time_Pusk)) > _or.T_zaderg_pusk )  )
           {
              //  Производим контроль текущей скорости в течении 6 пульсов перед подачей импульсов :
              // 26.05.2021 - Убрал , чтобы не портить ЗИ , т.к. при растормаживании барабана экодер почему-то
              // выдавал несколько сотен отрицательных процентов :
              /*if ( ZI_Init_Skor ( 1 ) == 0 )*/ ATK_flg._.trig_Pusk = 1 ;
              
                    //---------------------------------------------------
                    /* Если понадобится инициализация ЗИРС текущей скоростью , раскоментировать :
                    if ( _r.Cfg._.Vrasch_Dvig == 0 ) ATK_flg._.trig_Pusk = 1 ;
                    else if ( ZI_Init_Skor ( 1 ) == 0 ) ATK_flg._.trig_Pusk = 1 ; */
                    //---------------------------------------------------
              ATK_flg._.trig_Reg = 0 ;
              Time_Reg =  Timer1_Ovr ;
           }
     }
     else
     {
        // 26.05.2021 - Убрал , чтобы не портить ЗИ , т.к. при растормаживании барабана экодер почему-то
        // выдавал несколько сотен отрицательных процентов :
        //ZI_Init_Skor ( 0 ) ; // Запоминаем номер текущего пульса как первый пульс .
                    //---------------------------------------------------
                    /* Если понадобится инициализация ЗИРС текущей скоростью , раскоментировать :
                    // Запоминаем номер текущего пульса как первый пульс .
                    if ( _r.Cfg._.Vrasch_Dvig == 1 ) ZI_Init_Skor ( 0 ) ; */
                    //---------------------------------------------------
        ATK_flg._.trig_Pusk = 0 ;
        Time_Pusk =  Timer1_Ovr ;
        //---
        ATK_flg._.trig_Reg = 0 ;
        Time_Reg =  Timer1_Ovr ;
        //---
      //Control_Nzad () ;  // Контроль Задания до подачи Пуска не нужен , т.к. Пуск подается от ручки КЗС .
     }

    // пришла команда "Пуск" АТК .
    if ( bi_Pusk == 1 && ATK_flg._.trig_Pusk == 1 && KTE2_Sn_Imp == 0 )
      {
        if ( Otkl_Imp )
        {
          if ( flgO._.Shunt_Rot == 0 ) // Если Ротор Зашунтирован , то ИУ ставятся Альфа Макс и снимаются .
          {
             mVkl_Imp( _VR1_imp | _Start_imp ) ;  // включение ИУ
          }
        }
        if ( bi_V1_V3          == 0 ) mSet_AvarMsg2( _Av2_V1_V3 ) ;        //DAN 12.04.2025
        // 02.04.2019 7:39 - Пуск приходит на сетевой инвертор АР1 и сразу отдаётся на роторный выпрямитель АР2 .
        //                   Далее в каждой плате идут две независимые выдержки времени , причем на АР1 ИУ должны
        //                   податься раньше...
        //                   Задерживаю включение Регуляторов , чтобы начать двигать ИУ инвертора АР1 тогда ,
        //                   когда ИУ Ротора АР2 уже будут стоять и цепь для протекания тока будет .
        //                   -----
        //                   Т-зад.Пуска АР1 = 1.86 сек. + (Т-зад.Рег. = 0.25 сек)
        //                   Т-зад.Пуска АР2 = 1.93 сек.
        //                   -----
        if (  ATK_flg._.trig_Reg == 0 && ( (u)((w)(Timer1_Ovr - Time_Reg)) > _Sec (0.25) )  )
        {
            S.flg._.Invertor = 1 ;          // По умолчанию АР1 находится в режиме Инвертора
            Prg.all |= (_RegTok | _RegSk ); // включаем все регуляторы .
            ATK_flg._.trig_Reg = 1 ;
        }


       //-------------------------------------- Задание Скорости ---------------------------------------

       if ( bi_Dist_Upr == 0 )  ax = _or.Z_Sk_mestnoe ;
       else                     ax = canr.N_zad ;

       Z_Skor = ax ;

       //---
       // Нет разрешения включить КЗ от ШУ ШПМ .
       // Держим максимальное разрешенное задание без включения КЗ :
       if ( bo_candt_Otkl_KZ == 0 )
       {
         // Проверяем только положительное задание, т.к. отрицательного быть не может :
         if ( (sw)ax >= (sw)_or.Z_SkMax_bezKZ ) ax = _or.Z_SkMax_bezKZ ;
       }

       //-------------------------------------------------------------

        // Проверка , что Задание Скорости сравнялось с ЗИ скорости , чтобы включать КЗ только в установившемся
        // режиме и не войти в релейный режим вкл/выкл КЗ :
        ax = Z_Skor - ZISkor ;
        if ( (sw)ax >= 0 ) dZ_Sk =   ax ;
        else               dZ_Sk = - ax ;

        if ( dZ_Sk <= _Skor_nom( 0.005 ) ) bo_canZ_Sk_ZISk = 1 ;
        else                               bo_canZ_Sk_ZISk = 0 ;

       //-----------------------------------------------------------------------------------------------

       // В данный момент , если придёт сигнал "Положение тормоза заклинивающего барабан" в работе , то
       // Пуск АТК сниматься не будет , и двигатели будут "пыжыться" под тормозом . Возможно, такой режим
       // понадобится для каких-то работ ...

       //-----------------------------------------------------------------------------------------------

       //---------------------- Выход из Режима Шунтировки Ротора -------------------------
       // Возник режим шунтирования ротора в плате АР2 . Инвертор находится в Альфа Макс ,
       // РТ и РС зашунтированы .
       if ( KTE2_Shunt_Rot == 1 ) // В АР2 включен bo_Vkl_KZ - режим Шунтировки .
       {
           flgO._.Shunt_Rot = 1 ; // взводим флаг Шунтирования Ротора
           //---
           // Для расшунтировки ротора , чтобы не терять время , не проверяем ЗИС , а проверяем только задание .
           // Кроме того , проверяем , не вышел ли Второй АТК из режима шунтировки ( например , если Ведомому не
           // приходит Задание Скорости ) .
           // 18.01.2022 - либо пришел запрет на включение КЗ от ШУ ШПМ .
           // Продумать , что будет , если запрет от ШУШПМ пришел , а задание не уменьшилось ,
           // чтоб не возник релейный режим выкл/вкл КЗ ...
           if ( (sw)Z_Skor <= _or.Skor_Otkl_KZ || ATK2_Shunt_End == 1 || bi_dt_Otkl_KZ == 1 )
           {
                 bo_canShunt_End = 1 ; // Флаг для снятия ИУ выпрямителя и КЗ .
                 bo_atkShunt_End = 1 ; // Флаг для передачи во Второй АТК .
           }
           // 30.06.2022 - Флаги bo_canShunt_End и bo_atkShunt_End снимаются не здесь , а в файле UPRAVL.C .
       }

       //------------- Обработка разрешения/запрета включить КЗ от ШУ ШПМ -----------------
       // От ШУ ШПМ даётся разрешение на шунтировку ротора :
       if ( bi_dt_Otkl_KZ == 0 )
       {
            // 18.01.2022 - идею с замером тока для включения КЗ пока отставим .
            // Если скорость по модулю достигла уставки включения КЗ , нужно ограничивать ЗИ скорости на этом уровне ,
            // пока не произойдёт замер тока :
            //if ( (sw)skor >= _or.Skor_Vkl_KZ && (sw)Z_Skor >= _or.Skor_Vkl_KZ )
            //{
            //
            //}
            //----
            bo_candt_Otkl_KZ = 0 ; // Разрешение включить КЗ от ШУ ШПМ .
       }
       else bo_candt_Otkl_KZ = 1 ; // Запрет включать КЗ от ШУ ШПМ .
       //----------------------------------------------------------------------------------


            if ( bi_Vnesh_Avar == 1 )    mSet_AvarMsg( _Av_Vnesh_Avar ) ;

            // Фиксация текущего момента времени для последующего отсчета выдержки на снятие ИУ.
            Time_do_OtklImpPusk = Timer1_Ovr ;
      }
    else
      {
      //13.04.2017 7:00 - Нельзя просто взять и снять ИУ - будет опрокидывание , сказал Грыгорыч .
      //if ( !Otkl_Imp )  mOtkl_Imp( _Start_imp ) ;  // снимаем ИУ

        Z_Skor = 0 ; // 13.04.2017 7:00 - DAN . Снимаем задание , для того , чтобы ток упал и м.б снять ИУ .

        Set_ZI ( &zi_rs , 0 ) ;        // DAN - перенесено снизу , для того, чтобы ток спал быстро .
        ZISkor = 0 ;

        flgO._.Shunt_Rot = 0 ; // на вскякий случай , если он сам не снялся .
        bo_canShunt_End = 0 ;  // на вскякий случай , если он сам не снялся .
        bo_atkShunt_End = 0 ;  // на вскякий случай , если он сам не снялся .

        if ( !Otkl_Imp )
        {
           // 20.12.2020 - Задвигаем ИУ сразу , не ждём пока это сделают регуляторы :
           S.Alfa = _r.S_Alfa_Max ;
           Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.

           // - отсчет времени до отключения импульсов.
           // 20.12.2020 - добавил возможность в режиме Выпрямителя снимать ИУ без выдержки .
           if (/*S.flg._.Invertor == 0 ||*/ (u)((w)(Timer1_Ovr - Time_do_OtklImpPusk)) >= _r.Time_do_OtklImp )
           {
           //20.12.2020 - Убрал контроль тока , чтобы ИУ успевали сняться до отключения Реверсоров .
           //if ( IDV < _Id_nom ( 0.04 ) )
               {
                    mOtkl_Imp( _Start_imp ) ;  // снимаем ИУ
                    Prg.all &=  ~(_RegTok | _RegSk ) ; // выключаем все Регуляторы .

                    Av._.Sdvig_imp = 0 ;   // Задвиг отработал , снимаем команду на задвигание УИ в АльфаМакс .

                  //Set_ZI ( &zi_rs , 0 ) ;
                    OuIchRS = 0 ;
                  //ZISkor = 0 ;
                    Delta_Sk = 0 , OuIchRS_k = 0 ;
                    OuRegS_dop_kod = 0 ;
                    OuRegS         = 0 ;

                    OIRT_drob = 0 ;                // DAN - 16.06.2016 15:24

                    Prz._.int_p = 0 , Prz._.int_m = 0 ;

                    ZIDN = ZIDN1 = 0 ;  /* выход ЗИ-РТ. */
                    OIRT   = _r.RTMAX ;  /* интегратор регулятора тока */
                    OIRT1  = _r.RTMAX ;  /* интегратор регулятора тока */
                    S.Alfa = _r.S_Alfa_Max ;
               }
           }
        }
      }

        break;
        //-------
         // Объектная программа защит, отключаемая после срабатывания защиты.
      case _Obj_c_Avar_Otkl :
        break;
        //-------
    }

    return 0;
  }
/*--------------------------------------------------*/

// контроль Id_Max

#ifdef _Obj_Id_Max

void Control_Id_Max (void)
  {
    if ( IDV >= _r.Id_Max || Irot >= _r.Id_Max )
    {
        mSet_AvarMsg ( _Av_IdMax ) ;
        //----
        // Сигнал ( если он есть ) для передачи в плату АР1 АТК .
      //mOtkl_Q1 () ; // DAN 07.06.2017 15:20 - Формируем cигнал DI - сказал Грыгорыч .
        mSET_Q1() ;   // 01.08.2017 12:47 - Грыгорыч сказал , что сигнал должен держаться в нуле и не долбать .
        //----
        Av._.Id_max = 1 ; // Только для регистрации в аварийном битовом поле .
        Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
        //----
        //if ( IDV1 >= _r.Id_Max )
        //if ( IDV2 >= _r.Id_Max ) mSetF_AvarMsg ( _Av_IdMax ) ;
    }

    /* Выполняется в АР2 Роторный Выпрямитель :
    // Контроль срыва инвертора :
    // Дельта Инверторного и Роторного токов :
    dIrot = IDV - Irot ;
    if ( (sw)dIrot < 0 ) dIrot = ~dIrot + 1 ;
    //----

    // 30.12.2016 10:32 - Григорыч сказал , что если обе дельты больше уставки , то - авария .
    //                    Если одна из дельт больше - то всё в порядке .
    //                    Если обе дельты меньше уставки - тоже всё в порядке .
    if ( (sw)dIrot >= _or.dId_sryv )
    {
      // Сигнал ( если он есть ) для передачи в плату АР1 АТК .
    //mOtkl_Q1 () ;
      mSET_Q1() ;   // 01.08.2017 12:47 - Грыгорыч сказал , что сигнал должен держаться в нуле и не долбать .
      mSet_AvarMsg ( _Av_GerconDC ) ;
    } */

    return;
  }

#endif

/*--------------------------------------------------*/

void Control_Nzad (void)
  {
    word ax ;
            // Проверка присутствия задания на скорость.
          if ( _r.Cfg._.Control_ZSk == 1 )
            {
              ax = Nzad ;
              if ( (sw)ax < 0 )  ax = ~ax + 1 ;

              if ( ax > _r.Ostanov_skor )
                {
                  mSet_PreduprMsg( _Pr_Podano_ZSk   ) ;
            }   }
    return;
  }

void bo_ATK (void)
  {
  static word T_Lamp ;
        // Формирование выходных сигналов Предупреждения АТК , Аварии АТК , Готовности АТК , чтобы не было возможности
        // их "моргания" , выполняется после формирования стандартных выходов ( bo_Avar , bo_Predupr и bo_Gotov ).

        //-------- Реле "Авария АТК" --------
        // Плата АР2 Роторного выпрямителя не имеет Ламп на двери АТК , выводим общую для АР1 и АР2 "Аварию" .
        // Реле "Авария" используется в Пульте для управления "ВВ Статора" и "ВВ Ротора" .
        // В ШК все Аварии АТК1 , АТК2 и АТКR собраны последовательно , однако аварии Ведомого и Резервного шунтируются Ведущим .
        // ATK2_Avar содержит в себе Аварию и АР1 и АР2 другого АТК .
        // Если данный АТК - Ведущий , выводим общую для АР1 и АР2 Ведомого АТК "Аварию" :
        if ( ( bo_Avar == 1 || KTE2_Avar == 1 || (flgO._.Vedushiy == 1 && ATK2_Avar == 1)
        // Выводим лампу только на АТК выбранном для работы :
               ) && flgO._.V_rezerve == 0 ) bo_AvarATK = 1  ;
        else                                bo_AvarATK = 0 ;
#ifdef bo_Avar_Yach
        //---- Реле "Авария Ячейки АТК" -----
          // 13.06.2021 - Выдаём Аварию для отключения ячейки Согласующего Трансформатора .
          // Только при аварии по геркону и дверях отрабатывает выходной бит Авария
          // для отключения ячейки Согласующего трансформатора :
        if ( ( bo_Avar_Yach == 1 || (flgO._.Vedushiy == 1 && ATK2_Avar_Yach == 1)
        // Выводим лампу только на АТК выбранном для работы :
               ) && flgO._.V_rezerve == 0 ) bo_AvarYacheykaATK = 1 ;
        else                                bo_AvarYacheykaATK = 0 ;
#endif
        //---- Реле "Предупреждение АТК" ----
        // Плата АР2 Роторного выпрямителя не имеет Ламп на двери АТК , выводим общее для АР1 и АР2 "Предупреждение" .
        if ( ( bo_Predupr == 1 || KTE2_Predupr == 1
#ifndef _ShK_Rele_Vedom // Если в ШК параллельно НЕ приходит предупреждение Ведомого АТК .
        // ATK2_Predupr содержит в себе Предупреждение и АР1 и АР2 другого АТК .
        // Если данный АТК - Ведущий , выводим общее для АР1 и АР2 Ведомого АТК "Предупреждение" :
               || (flgO._.Vedushiy == 1 && ATK2_Predupr == 1)
#endif
        // Выводим лампу только на АТК выбранном для работы :
               ) && flgO._.V_rezerve == 0 ) bo_PreduprATK = 1 ;
        else                                bo_PreduprATK = 0 ;
        //------ Реле "Готовность АТК" ------
        // Плата АР2 Роторного выпрямителя не имеет Ламп на двери АТК , выводим общую для АР1 и АР2 "Готовность" .
        // Реле "Готовность" используется в Пульте для управления "ВВ Статора" и "ВВ Ротора" .
        if ( ( bo_Gotov == 1 && KTE2_GotovQK == 1
#ifndef _ShK_Rele_Vedom // Если в ШК параллельно НЕ приходит Готовность Ведомого АТК .
        // ATK2_GotovQK содержит в себе Готовность и АР1 и АР2 другого АТК .
        // Если данный АТК - Ведущий , выводим общую для АР1 и АР2 Ведомого АТК "Готовность" :
               && ((flgO._.Vedushiy == 1 && ATK2_GotovQK == 1) || flgO._.Vedushiy == 0)
#endif
        // При работе в режиме "Два двигателя" проверяется наличие связи между АТК и соответствие номера выбранного АТК :
               && ((flgO._.CAN0_ok == 1 && flgO._.abonATK == ATK2_NmbrATK) || flgO._.Reg1dvig == 1)
        // Выводим лампу только на АТК выбранном для работы :
               ) && flgO._.V_rezerve == 0 ) bo_GotovATK = 1 ;
        else                                bo_GotovATK = 0 ;
        //----
        // На Пульте есть кнопки "Вкл. ВВ статора" и "Вкл. ВВ ротора" ( т.е. , согласующего тр-ра ) ,
        // которые работают через б/к реле "Готовность АТК" и "Авария АТК" - включатся только при
        // наличии Готовности . Включение Согласующего тр-ра ( подача силы на инвертор ) - это вход
        // в Работу без ИУ .
        //----
        // ТП заряжается на Пульте . В "Цепи ТП" есть б/к Готовности , Аварии , "ВВ статора" и "ВВ ротора" .
        // После этого могут включиться "Реверсоры" . "Реверсоры" включаются при подаче Задания ручкой
        // Оператора , таким образом включение "Реверсоров" ( т.е. подача "Пуска" ) и выбор направления
        // "Вперёд/Назад" - одновременный процесс .
        //----
        //-------- Реле "Работа АТК" --------
        // Включение обоих "Реверсоров" это "Пуск" - подача ИУ .
        // Выдаём лампу "Работа АТК" если все нижеперечисленные условия выполняются :
        // 1. АТК в работе ( и АР1 , и АР2 ) .
        // 2. Реле "Авария АТК" отключено и реле "Готовность АТК" включено .
        // 3. Либо режим "Один двигатель" , либо в режиме "Два двигателя" контролируется следующее :
        //    3.1. Работа и отсутствие Аварии Второго АТК .
        //    3.2. Проверяется наличие связи между АТК и соответствие номера выбранного АТК рассчетному .
        // 4. После подачи "Пуска" истекла выдержка и поданы ИУ .
        // 5. Выполняется только на АТК выбранном для работы .
        if ( Prg._.Gotovn == 0 && KTE2_Rabota == 1 && bo_AvarATK == 0 && bo_GotovATK == 1 &&
              ( (ATK2_Rabota == 1 && ATK2_Avar == 0 && flgO._.CAN0_ok == 1 && flgO._.abonATK == ATK2_NmbrATK) ||
              flgO._.Reg1dvig == 1 ) && ATK_flg._.trig_Pusk == 1 && flgO._.V_rezerve == 0 )
        {
#ifdef _Rabota_Mig // Если лампа "Работа АТК" не используется для подачи "Пуска" и показывает еще и "Предупреждение" :
             if ( bo_PreduprLamp == 0 ) bo_RabotaATK = 1 , T_Lamp = Timer1_fSec ;
             else
             {
                  // Работа с Предупреждением , мигаем лампой :
                  //---
                  if ( bo_RabotaATK == 1 )
                    {
                      if ( (u)((w)(Timer1_fSec - T_Lamp)) >= _fSec(1.00) )
                      {
                        bo_RabotaATK = 0 , T_Lamp = Timer1_fSec ;
                      }
                    }
                  else
                    {
                      if ( (u)((w)(Timer1_fSec - T_Lamp)) >= _fSec(1.00) )
                      {
                        bo_RabotaATK = 1 , T_Lamp = Timer1_fSec ;
                      }
                    }
             }
#else
             bo_RabotaATK = 1 ;
#endif
        }
        else bo_RabotaATK = 0 , T_Lamp = Timer1_fSec ;

    return;
  }
//-------------
word SetMaxNumChan(word *Cnt)
{
  word Out = 0;
  if ( ++*Cnt >= Izm_Seq_max )
  {
    *Cnt = 0; // Чтение с 0-го начинается при инициал

    //if (++*Cnt == 2)
    // {
    //bo_canEndIzm = 1;
    TimeDelay = Timer1_Ovr;
    Out = 1;

    Time_Cikl = (float)(Timer1_Ovr - Time_Cikl1)/(float)_Sec(1);
    //Time_Cikl1 = Timer1_Ovr;

  }

  channelTemp = Izm_seq[*Cnt];
  if ( channelTemp >= _MaxChannel)
  {
    channelTemp = 0;
  }

  return Out;
}

//--------------Программа опрос каналов температуры и напряжения------------
void T_Izm_Dat(void)
{
  word ax, bx;//, cx;
  static word int_Counter = 0;

  switch (IzmTempLabel)
  {
  case 0:
    if ( bo_SN_On )
    {
      if ((w)((u)(Timer1_Ovr - TimeDelay_Temper))> _Sec(4))
      {
        Trg_IzmTemp = 1;
      }
      
      if (Trg_IzmTemp)
      {
        
        ax = 1;
        
        if ((bo_EndIzm)&&(Prg._.Gotovn))
        {
          ax = 0;
          bo_EndIzm = 0;
          TimeDelay = Timer1_Ovr;
        }
        else
        {
          if (Prg._.Gotovn)
          {
            if((u)((w)(Timer1_Ovr - TimeDelay))< _Sec(3))
            {
              ax = 0;
              Time_Cikl1 = Timer1_Ovr;
            }
          }
          
        }
        
        //Для блокировки вывода сообщений при включении питания
        if((u)((w)(Timer1_Ovr - TimeBlockIzm))> _Sec(1))
        {
          bo_KontrVkl = 1;
        }
        //На всякий случай
        if ((!PDF[0].Bits._.Count_Beg)&&(ax != 0))
        {
          Set_CS_Temp(Addr_izmChanell[(0xfU & channelTemp)]);          // Задаем адресс канала
          PDF[0].Bits._.Count_Beg = 1;
          ++IzmTempLabel;
          //Time_Cikl1 = Timer1_Ovr;
        }
      }
      
    }
    else
    {
      channelTemp = 0;
      int_Counter  = 0;
      Trg_IzmTemp = 0;
      TimeDelay_Temper = Timer1_Ovr;
      PDF[0].Bits._.Count_Beg = 0;
      Av_Dat = 0;
      bo_EndIzm = 0;
      //Time_Cikl1 = Timer1_Ovr;
    }
    break;
  case 1:
    //Начинаем измерения с небольшой выдержкой после установки адреса

    Time_tst = Timer1_Ovr;
    ++IzmTempLabel;
  //  break;
  case 2:

    if (!PDF[0].Bits._.Count_Beg)
    {
      ++IzmTempLabel;
      if (PDF[0].Freq != 0)
      {
        TIzm[channelTemp].Freq =  PDF[0].Freq ;
        TIzm[channelTemp].V_Out=  PDF[0].V_Out;
        TIzm[channelTemp].Out  =  PDF[0].Out  ;
        TIzm[channelTemp].I_Out=  PDF[0].I_Out;

        Av_Dat &= ~AvTemp[channelTemp];  // Тут обнуляється масив якщо канал і датчик справні
      }
      else
      {
        TIzm[channelTemp].Freq =  0;
        TIzm[channelTemp].V_Out=  0;
        TIzm[channelTemp].Out  =  _or.T0Volt;
        TIzm[channelTemp].I_Out=  (sw)(_or.T0Volt*10);
        PDF[0].Bits._.Count_Beg = 0;
        //CLR_CS_Temp();
        //++IzmTempLabel;
        Av_Dat |= AvTemp[channelTemp];//(0x1<<(_MaxChannel - channelTemp-1));  Зберігається одиниця в масиві по індексу каналу і якщо не скидається то далі висталяється аварія
      }
      //if (   ( Invert_v_rabote !=  _stat_Avar))
      //      if( )
      //      {
      //        mClr_PreduprMsg(_Pr_Tizm1>>channelTemp );
      //      }
    }
    else
    {
      if ((u)((w)(Timer1_Ovr - Time_tst)) > _Sec(1))
      {
        TIzm[channelTemp].Freq =  0;
        TIzm[channelTemp].V_Out=  0;
        TIzm[channelTemp].Out  =  _or.T0Volt;
        TIzm[channelTemp].I_Out=  (sw)(_or.T0Volt*10);
        PDF[0].Bits._.Count_Beg = 0;
        //CLR_CS_Temp();
        ++IzmTempLabel;
        Av_Dat |= AvTemp[channelTemp];//(0x1<<(_MaxChannel - channelTemp-1));
        // mSet_AvarMsg(_Av_Tizm1>>channelTemp);
      }
    }
    break;
  case 3:
    //    if ((u)((w)(Timer1_Ovr - Time_tst)) > _or.Time_opros )
    //    {
    CLR_CS_Temp();
    //Если  сдели все измерения, то переходим к окончанию серии
    if (SetMaxNumChan(&int_Counter)== 1)
    {
      IzmTempLabel = 4;
      
    }
    else
    {
      IzmTempLabel = 0;
      
    }
    break;
  case 4:
    Avv_Dat = Av_Dat;
    Trg_BegTemp = 0;
    //В сборке готовности измеренияя не чаще чем раз в 2 сек.
    if(((u)((w)(Timer1_Ovr - TimeDelay))> _Sec(2))||(!Prg._.Gotovn))
    {
      bo_EndIzm = 1;
      IzmTempLabel = 0;
      TimeDelay = Timer1_Ovr;
      
    }
    break;
  }

/*if (Prg._.Gotovn)
  {
    mClr_PreduprMsg2(_Msk_Temp_Msg );
    mClr_AvarMsg2(_Av2_Tizm1|_Av2_Tizm2| _Av2_Ishs1|  _Av2_Ishs2 );
  }
*/
  FanSpeedMax  = 0;
  ax = 0;
  bx = 0;
  if (_r.Cfg2._.ContrTShI)
  {
    if ((Avv_Dat & _Ch_Ishs1msk)!= 0)
    {
      mSet_AvarMsg2( _Av2_Ishs1);
    }
  }
  if (_r.Cfg2._.ContrTShV)
  {
    
    if ((Avv_Dat & _Ch_Ishs2msk)!= 0)
    {
      mSet_AvarMsg2( _Av2_Ishs2);
    }
  }
  
  Avv_Dat &= (~(_Ch_Ishs1msk | _Ch_Ishs2msk));
  //mSet_PreduprMsg( (lw)(Avv_Dat & (_Ch_Ishs1msk | _Ch_Ishs2msk) )<< Bit_PrAvar );

  if (Avv_Dat  != 0)
  {
    FanSpeedMax  = 1;
    if (_r.Cfg2._.ContrTShI)
    {
      
      if ((Avv_Dat & _Ch_BK1_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK2_S1msk) != 0)
      {
        ++ax;
      }
      
      if ((Avv_Dat & _Ch_BK3_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK4_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK5_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK6_S1msk) != 0)
      {
        ++ax;
      }
    }
    else
    {
      Avv_Dat &= (~(_Ch_BK1_S1msk | _Ch_BK2_S1msk| _Ch_BK3_S1msk| _Ch_BK4_S1msk| _Ch_BK5_S1msk| _Ch_BK6_S1msk));
    }
    if (_r.Cfg2._.ContrTShV)
    {
      
      if ((Avv_Dat & _Ch_BK1_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK2_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK3_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK4_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK5_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK6_S2msk) != 0)
      {
        ++bx;
      }
    }
    else
    {
      Avv_Dat &= (~(_Ch_BK1_S2msk | _Ch_BK2_S2msk| _Ch_BK3_S2msk| _Ch_BK4_S2msk| _Ch_BK5_S2msk| _Ch_BK6_S2msk));
    }
    
    if ((ax <= _Dat_Temp_All/4 )&&(bx <= _Dat_Temp_All/4))
    {
      mSet_PreduprMsg2( (lw)Avv_Dat  << Bit_PrAvar );
    }
    else
    {
      if ((ax > _Dat_Temp_All/4)&&(!bi_BV1))
      {

        mSet_AvarMsg2( _Av2_Tizm1 );
      }
      if ((bx > _Dat_Temp_All/4)&&(!bi_BV2))
      {
        mSet_AvarMsg2( _Av2_Tizm2 );
      }
    }
  }


       Volt[0] = TIzm[_Ch_Ishs1].V_Out; // Перекладываем значения каналов по напряжению
       Volt[1] = TIzm[_Ch_Ishs2].V_Out;//
       Amper[0] =  (Volt[0]*_or.mV_A) /1000;
       Amper[1] =  (Volt[1]*_or.mV_A)/1000;
       if (isnan(Amper[0])|| isinf(Amper[0]))
       {
         Amper[0] = 0;
       }

       if (isnan(Amper[1])|| isinf(Amper[1]))
       {
         Amper[1] = 0;
       }

       // ------ Контроль напряжения питающих узлов ------------
       //if ( Invert_v_rabote ==  _stat_Work || Invert_v_rabote ==  _stat_Work_Predupr )
       //if ( (Invert_v_rabote &  _stat_Work) || (Invert_v_rabote & _stat_Work_Predupr) )  {
       // for ( int i = 0; i < 2; i++){
       //if ( (sw)Volt[i] < (sw)_or.Pimp_min || (sw)Volt[i] > (sw)_or.Pimp_max ) mSet_AvarMsg(_Av_Pimp), mSet_PreduprMsg(_Pr_Pimp);
       //if ( (sw)Amper[i] < (sw)_or.Pimp_min || (sw)Amper[i] > (sw)_or.Pimp_max ) /*mSet_AvarMsg(_Av_Pimp),*/ mSet_PreduprMsg(_Pr_Pimp);
       //else                                                                      /*mClr_AvarMsg(_Av_Pimp),*/ mClr_PreduprMsg(_Pr_Pimp);
       // if ( (canr.Data._.Connect == 0)||(can_ConfigReg ( _CAN_IznmVkl) != 0))
       // {

       if ( Otkl_Imp == 0)
       {
         ax = 1;
       }
       else
       {
         ax = 0;
       }
       if (_r.Cfg2._.ContrTShI)
       {         
         
         if ( (Amper[0] < _or.Pimp_min[ax] || Amper[0] > _or.Pimp_max[ax])&&((Avv_Dat & _Ch_Ishs1msk ) == 0) )
         {
           if (!Prg._.Gotovn)
           {
             mSet_AvarMsg2(_Av2_Pimp1);
           }
           else
           {
             mSet_PreduprMsg2(_Pr2_Pimp1);
           }
           
         }
         else
         {
           mClr_PreduprMsg2(_Pr2_Pimp1);
         }
         
       }
       if (_r.Cfg2._.ContrTShV)
       {
         
         if ( (Amper[1] < _or.Pimp_min[ax] || Amper[1] > _or.Pimp_max[ax]) &&((Avv_Dat & _Ch_Ishs2msk ) == 0))
         {
           if (!Prg._.Gotovn)
           {
             mSet_AvarMsg2(_Av2_Pimp2);
           }
           else
           {
             mSet_PreduprMsg2(_Pr2_Pimp2);
           }
         }
         else
         {
           mClr_PreduprMsg2(_Pr2_Pimp2);
         }
       }
       
       //}
       //---------------
       
       
       // ------------------------- перекладываем температуру
       //Temper[Counter_Izm_T] = (sw)Temperature[Counter_Izm_T];
       for (ax = 0; ax < _Dat_Temp_All/2; ++ax)
       {
         Temper[ax] = TIzm[DT_Chanells[0][ax]].I_Out;
         Temper[ax+_Dat_Temp_All/2] = TIzm[DT_Chanells[1][ax]].I_Out;
         fTemper[0][ax] = TIzm[DT_Chanells[0][ax]].Out;
         fTemper[1][ax] = TIzm[DT_Chanells[1][ax]].Out;
       }
       DTMonitor.checkSensors(fTemper[0]);
       DT_Cond[0] = DTMonitor.getAllFaultFlags();
       if (_r.Cfg2._.ContrTShI)
       {
         
         if (DTMonitor.hasAnyFaults()&&((Avv_Dat & (_Ch_BK1_S1msk | _Ch_BK2_S1msk)) == 0))
         {
           if (DTMonitor.getFaultyCount() > _Dat_Temp_All/4)
           {
             mSet_AvarMsg2(_Av2_dT_ShS1);
           }
           else
           {
             mSet_PreduprMsg(_Pr_dT_ShS1);
           }
           FanSpeedMax  = 1;
         }
       }
       //-------------     Проверка уровня температуры
       DTMonitor.checkSensors(fTemper[1]);
       if (_r.Cfg2._.ContrTShV)
       {
         
         DT_Cond[1] = DTMonitor.getAllFaultFlags();
         if (DTMonitor.hasAnyFaults()&&((Avv_Dat & (_Ch_BK1_S1msk | _Ch_BK2_S1msk)) == 0))
         {
           if (DTMonitor.getFaultyCount() > _Dat_Temp_All/4)
           {
             mSet_AvarMsg2(_Av2_dT_ShS2);
           }
           else
           {
             mSet_PreduprMsg(_Pr_dT_ShS2);
           }
           FanSpeedMax  = 1;
         }
       }
       
       if ((sw)Temper[Counter_Izm_T] >= _or.T_Av)
       {
         if ((u)((w)(Timer1_fSec - Time_Av_Dat_temp[Counter_Izm_T])) > _fSec(2))
         {
           // mSet_AvarMsg (_Av_Izm_T ) ;
           // mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
           Av_DT_Str.all |= (1UL<< Counter_Izm_T);
           Pr_DT_Str.all &= ~(1UL<< Counter_Izm_T);
         }
         Time_Pr_Dat_temp[Counter_Izm_T] = Timer1_fSec;
       }
       else if ((sw)Temper[Counter_Izm_T] >= _or.T_Pr )
       {
         //mSet_PreduprMsg2 (_Pr2_Izm_T ) ;
         //mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
         if ((u)((w)(Timer1_fSec - Time_Pr_Dat_temp[Counter_Izm_T])) > _fSec(2))
         {
           Av_DT_Str.all &= ~(1UL<< Counter_Izm_T);
           Pr_DT_Str.all |= (1UL<< Counter_Izm_T);
         }
         Time_Av_Dat_temp[Counter_Izm_T] = Timer1_fSec;
       }
       else
       {
         Av_DT_Str.all &= ~(1UL<< Counter_Izm_T);
         Pr_DT_Str.all &= ~(1UL<< Counter_Izm_T);
         Time_Av_Dat_temp[Counter_Izm_T] = Timer1_fSec;
         Time_Pr_Dat_temp[Counter_Izm_T] = Timer1_fSec;
       }
       if (Prg._.Gotovn)
       {
         mClr_PreduprMsg ( _Pr_CTC_Temper ) ;
         mClr_AvarMsg ( _Av_CTC_Temper ) ;
       }

       mClr_ServiceMsg3 ( _SrvDT_Mask ) ; // сброс 4-х датчиков
       if ( Pr_DT_Str.all != 0 )
       {
         mSet_PreduprMsg ( _Pr_CTC_Temper ) ; //
         FanSpeedMax  = 1;
         //bo_canPrTemp = 0;
         for (ax = 0; ax < _Dat_Temp_All /*6*/; ++ax)
         {
           if ((Pr_DT_Str.all&(1Ul<<ax)) != 0)
           {
             mSet_ServiceMsg3 ((_Srv3_BK1>> ax)) ;
           }
         }
       }

       // ------------  Определение самого Горячего Охладителя для вентиляции
       if (++Counter_Izm_T /*счетчик измерен. каналов*/ >= _Dat_Temp_All /*кол-во каналов*/ ) // пока не определится как принимать и передавать данные температуры
       {
         t_fan = 0 ;
         for ( int i = 0; i < _Dat_Temp_All; i++)
         {
           if ( (sw)Temper[i] > (sw)t_fan ) t_fan = Temper[i] ;
         }
         Counter_Izm_T = 0 ;
       }
       //---------
       if ( Av_DT_Str.all != 0)
       {
         mSet_AvarMsg (_Av_CTC_Temper ) ;
         FanSpeedMax  = 1;
         //bo_canAvTemp = 0;
         for (ax = 0; ax < _Dat_Temp_All /*6*/; ++ax)
         {
           if ((Av_DT_Str.all&(1Ul<<ax)) != 0)
           {
             mSet_ServiceMsg3 ((_Srv3_BK1>> ax)) ;
           }
         }
       }
       if (!bo_KontrVkl)
       {
         //mClr_AvarMsg( );
         mClr_PreduprMsg2(_Pr2_Pimp1 | _Pr2_Pimp2 |_Pr_dT_ShS1 |_Pr_dT_ShS2);
         mClr_PreduprMsg (_Pr_dT_ShS1 |_Pr_dT_ShS2);
       }

       //  }
       //  else
       //  {
       //    bo_canAvTemp = 1;
       //    bo_canAvPimp =1;
       //    bo_canPrTemp = 1;
       //    for (ax = 0; ax < _Dat_Temp_All; ++ax)
       //    {
       //      Time_Av_Dat_temp[ax] = Timer1_fSec;
       //      Time_Pr_Dat_temp[ax] = Timer1_fSec;
       //    }
       //    mClr_AvarMsg(_Av_dT_ShS1|_Av_dT_ShS1 | _Av_CTC_Temper);
       //    mClr_PreduprMsg ( _Pr_CTC_Temper ) ;
       //    mClr_ServiceMsg2(_Srv2_BK1|_Srv2_BK2|_Srv2_BK3|_Srv2_BK4);
       //
       //
       //  }
       // Timer_T_NoLink = Timer1_Ovr;
}

//--------------------Fan-----------------------------------------------------
void controlFan(word num)
{  // Ctrl_Vent
  word IDV_Vrem;
  static word  Time_t_tir, Time_temper_min ;
  double Id_fan1;
  /* Программа предполагает управление вентиляцией как по току так и по температуре. Входим в условие в работе при превышении тока какой то уставки, либо и вработе и
  в готовности  по превышению какойто температуры, и если это по превышению температуры, то работатем от уставки. Если же по току, то задаем прямо пропорционально возростанию тока
  шагом 0,1 номинал на вентилятор. Необходимо опробовать.  Можно работать все время от уставки задав температуру включения = 0 + переход на прямопропорциональную сать по превышению тока*/

  if ( num == 0 )
  {
    bo_VklVent_1_2_3 = 1;
    bo_vent_vkl;//mSET_Q2() ;  // включение охлаждения на 10 сек при запуске контроллера.
    //#define   mSET_Q2()    LPC_GPIO1->CLR = _Q2_Msk
    //#define   mCLR_Q2()    LPC_GPIO1->SET = _Q2_Msk
    Time_t_tir = Timer1_Ovr ;//- _r.Time_otkl_BV1 + _Sec( 15.0 ) ;     // если уставка меньше 10сек
    //Id_fan =_or.Id_max_vent ;
    Time_temper_min = Timer1_Ovr ;
  }
  else
  {
    //if ( bi_SFV == 1 )
    //{
    // Включаем вентиляторы по температуре включения (самого горячего)( работа/готовность ) или в работе по беззнаковому току
    //if ( (Prg._.Gotovn == 0 && Otkl_Imp == 0 /*bo_Avar == 0 && (IDV >= _or.Id_Vkl_VentShs1 )*/ ) || t_fan >= _or.t_VklFanShs1 )
    // Смотрим на состояние инвертора или температуру
    if ( t_fan >= _or.T_Pr )
    {
      //Id_fan = _or.Id_zad_average/*, bo_VklVent_1_2_3 = 1*/;   // задание в готовности если температура повышенная
      FanSpeedMax = 1;
      //Time_t_tir  = Timer1_Ovr;
    }
    if (!Prg._.Gotovn)// || t_fan >= _or.T_Pr )
      //if ( (Invert_v_rabote & _stat_Work) || (Invert_v_rabote & _stat_Work_Predupr) || t_fan >= _or.t_VklFanShs1 )
    {
      // Токи Id безнаковые. Выбираем больший ток. В любом случае будет значение тока.
      if      ( Irot >= IDV ) IDV_Vrem = Irot;
      else                IDV_Vrem = IDV ;

      bo_VklVent_1_2_3 = 1;
      bo_vent_vkl;// mSET_Q2();
      //IDV_Vrem = IDV;
      // if ( (sw)IDV_Vrem < 0 )  IDV_Vrem = ~IDV_Vrem + 1 ;

      if (IDV_Vrem >= _or.Id_Vkl_VentShs1)
      {
        //Id_fan = ((w)(IDV_Vrem/_Id_nom(0.1))*_Id_nom(0.1));// -_or.Id_min_vent;//* (w)((_or.Id_max_vent - _or.Id_min_vent )/_or.Id_max_vent);// + _or.ShiftCurrentVent, bo_VklVent_1_2_3 = 1;
        //Id_fan1 = ((w)(((_or.Id_max_vent - _or.Id_min_vent ))/((_Id_nom(1.0) - _or.Id_Vkl_VentShs1)))*((bx - _or.Id_Vkl_VentShs1))) + _or.Id_min_vent;
        Id_fan1 = (double)((double)(_or.Id_max_vent - _or.Id_min_vent )/(double)(_Id_nom(1.0) - _or.Id_Vkl_VentShs1));
        Id_fan = (w)(Id_fan1 *(double)(IDV_Vrem - _or.Id_Vkl_VentShs1)) +  _or.Id_min_vent;
        if( Id_fan < _or.Id_min_vent )  Id_fan =_or.Id_min_vent ;
        if( Id_fan > _Id_Nom )  Id_fan = _Id_Nom ;

        Time_temper_min = Timer1_Ovr ;
        //Id_fan = ((w)((_or.Id_max_vent - _or.Id_min_vent )*(IDV_Vrem/100))) /*+ _or.ShiftCurrentVent, bo_VklVent_1_2_3 = 1*/;
      }
      // else
      // {
      // Если нет условий для включения вентилятора, то Time_temper_min не обновляется
      if ( (u)((w)(Timer1_Ovr - Time_temper_min)) > _or.Time_otkl_BV1 ) Id_fan = 0 ;
      // }
      //---
      Time_t_tir  = Timer1_Ovr;
    }// ниже как инерционное звено на понижение
    else /*if ( bi_SFV == 1 ) */// Если тока уже нет , но вентиляторы включены ,  ??????????????????????????????????????????????????????????????????????
    { // держим их включенными еще некоторое время , или пока кто-то не сбросит их "дист.сбросом" :
      if ( bo_VklVent_1_2_3 == 1 )     // Если перегрева уже нет, но вентиляторы включены,
      {                           // держим их включенными по выдержке, или пока кто-то не сбросит их "дист.сбросом" :
        if (( Av._.DistSbros == 1 )||( (u)((w)(Timer1_Ovr - Time_t_tir)) > _or.Time_otkl_BV1 )) //_Sec( 10.0 * 60.0 ) )
        {                               // через выдержку
          Id_fan = 0;
          FanSpeedMax = 0;
          bo_VklVent_1_2_3 = 0;
          bo_vent_otkl; // mCLR_Q2() ;     // отключение вентиляторов
        }
      }

    }
  }
  if (bo_VklVent_1_2_3 == 1)
  {
    if (FanSpeedMax == 1)
    {
      Id_fan =_or.Id_zad_fors ;
    }
  }
  else
  {
    Id_fan = 0;
  }

  if (bo_VklVent_1_2_3)
  {
    if ((!bi_BV1) ||(!bi_BV2) )
    {
      if ((u)((w)(Timer1_Ovr - timerVentAvar)) > _or.TimeAvarNoVent)
      {
        if (!bi_BV1)
        {
          mSet_PreduprMsg2( _Pr2_Vent_Shs1 ) ;
        }

        if (!bi_BV2)
        {
          mSet_PreduprMsg2( _Pr2_Vent_Shs2 ) ;
        }
      }
    }
    else
    {
      if (Prg._.Gotovn)
      {
        mClr_PreduprMsg2( _Pr2_Vent_Shs2 | _Pr2_Vent_Shs1 ) ;
      }
      timerVentAvar = Timer1_Ovr;
    }

  }
  else
  {
    timerVentAvar = Timer1_Ovr;
  }
  //  else mSet_AvarMsg2( _Av2_Power_Vent_Shs1 );  //Вентилятор выключен
}
//---------------------End Fan------------------------------------------------
