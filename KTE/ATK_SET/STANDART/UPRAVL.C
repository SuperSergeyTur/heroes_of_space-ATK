

/* Блок управления задающий алгоритм работы начиная с опробования. */

void Blok_upr ( void )
{
   enum  { k0, k10, k20, k30, k35, k140, k145, k150, k153,
                 k160, k163, k170, k173, k180, k183,
                       k190, k193, k199, k200x, k200,
                       k210, k220                     // Автонастройка .
         };
#ifdef _KTE_GD
  static byte tst ;
#endif

static w dn_max_copy=0; //для автонастройки функционала
static w otkl_func_copy=0;
static w dve_zony_copy=0;

//--------------
                                                       // 20.12.2008 19:36 DAN Подумать , нужно
   if ( Prg._.Blok_upr == 0 && Isp._.SIFUV_Res == 0 )  // ли добавить контроль циклов РТВ и СИФУВ .
     {                                                 //---------------------------------------
       upr_label = 0 ;                                 // 22.11.2013 9:02 DAN А контроль циклов
       return ;                                        // РТВ и СИФУВ уже выполнен в F2_DRV.C .
     }
   //---
   switch ( upr_label )
     { default :
       case k0 :
                 if      ( Isp._.SIFUV_Res == 1 ) upr_label = k140 ;      //   S.Disable и S2.Disable должны включаться
                 else if ( Isp._.Samonastr == 1 ) upr_label = k10  ;      // в штатной/объектной программе .
                 else if ( Isp._.RT_Res    == 1 ) upr_label = k150 ;      // ------------------------------------------
                 else if ( Isp._.RT1_Res   == 1 )                         //   Принудительно здесь они включаются
                 {                                upr_label = k150 ;      // только при выборе РТ1 или РТ2 .
       #ifdef  _SIFU2_
                    S2.Disable = 1;
       #endif
                    S.Disable  = 0;

                 }
                 else if ( Isp._.RT2_Res   == 1 )
                 {                               upr_label = k150 ;
       #ifdef  _SIFU2_
                    S2.Disable = 0;
       #endif
                    S.Disable  = 1;

                 }
                 else if ( Isp._.SIFU_Res  == 1 ) upr_label = k160 ;
                 else if ( Isp._.Cikl      == 1 ) upr_label = k170 ;
                 else if ( Isp._.Oprobov   == 1 ) upr_label = k180 ;
                 else if ( Isp._.RN_Res    == 1 ) upr_label = k190 ;
#ifdef _AVTONASTR
                 else if ( Isp._.AvtoNastr == 1 ) upr_label = k210 ;  // Aвтонастройка
#endif
                 else
                   {        // для внешней системы регулирования -
                           // признак того, что КТЭ готов к принятию задания.

                         // Проверяем отсутствие CAN-команды 'Останов'.
                     if ( can_ConfigReg ( _CAN_Ostanov ) == 0
                   #ifdef  bi_Technol_Ostanov
                          && bi_Technol_Ostanov == 0
                   #endif
                   #ifdef  bi_QKDT
                          && bi_QKDT == 0 // Если контактор ДТ разомкнулся ,
                   #endif
                                                              )
                     {
                        /* Запоминаем номер текущего пульса как первый пульс */
                       ZI_Init_Skor ( 0 ) ;
                       upr_label = k199 ;
                     }
                   }
                 upr_ax = 0 , upr_time = Timer1_Ovr ;

                 break;


               /*---------  Самонастройка. -----------*/
       case k10:
              #ifdef  bi_QKDT
                 if ( bi_QKDT == 1 ) break ; // Если контактор ДТ не разомкнулся , выход .
              #endif
                 mVkl_Imp( _VR1_imp | _Start_imp ) ;
                    //---------
              #ifdef _KTE_GD   // 10.08.05 16:03
                  if ( bi_LK == 0 )
                  {
                    Prg.all = (Prg.all & _Sled) | _RN | _Blok_upr ;
                    ORT = 0 ;
                    break;
                  }
              #endif

                 zeds = _r.Z_EDS ; //копия текущего  значения уставки
                 tzisk = _r.T_ZISkorP_Razg ; //копия текущего  значения уставки
                 zskmax = _r.Z_SkMax_P ; //копия текущего  значения уставки
                 dn_max_copy = _r.dN_Max;
                 _r.dN_Max = _Skor_nom ( 1.0 ); //на время автонастройки отключаем контроля неисправности ДС.

                   //  Задается повышенное задание ЭДС, чтобы регулятор ЭДС
                 // надежно сидел в насыщении и держал номинальный ток
                 // возбуждения, когда регулятор скорости поднимет скорость
                 // до ЭДС = zeds .
                 _r.Z_EDS  +=  100 ;

                 // Начальные условия
                 _r.Iv_zad_Max  = _Iv_nom( 1.0 ) ;
                 dve_zony_copy = _r.Cfg._.Dve_Zony; //
                 otkl_func_copy = V.flg._.otkl_func; //
                 _r.Cfg._.Dve_Zony = 1 ;
                 V.flg._.otkl_func = 1 ; // Включен только РТВ (функционал на время
                                // самонастройки отключен)
                   // Задаем регулятору скорости повышенное задание, чтобы
                 // он с медленным темпом поднял ЭДС до значения zeds.
                 Z_Skor = _Skor_nom( 1.4 ) ;
              #ifndef   _ZI_30min
                 _r.T_ZISkorP_Razg = _Skor_nom( 0.10 ) ;  // темп - 1.0 ном за 10сек.
              #else                     // ЗИ до 30 минут .
                 _r.T_ZISkorP_Razg = 150 ;                // темп - 1.0 ном за 10мин.
              #endif
                 _r.Z_SkMax_P = _Skor_nom( 1.4 )  ;
                    //-----
                 Prg.all = (Prg.all & _Sled) | _RegSk | _RegTok | _Blok_upr  ;
                    //---------
                 upr_ax = 0 , upr_label = k20 , upr_time = Timer1_Ovr ;
                 break;
                   /*   Ожидание такой скорости, при которой ЕДС
                    * двигателя станет равной заданной ЭДС - zeds.
                    */
       case k20: upr_ax = ( upr_ax + ( EDS & 0x7FFFu )) / 2 ; // Усреднение ЭДС.
                 if ( upr_ax < zeds )
                   {
              #ifndef   _ZI_30min
                     if ( (u)((w)(Timer1_Ovr - upr_time)) > _Sec( 18.0 ) )
                                            mSet_ServiceMsg( _Srv_No_EDS_Nom ) ;
              #else                     // ЗИ до 30 минут .
                     if ( (u)((w)(Timer1_Ovr - upr_time)) > _Sec( 12.0 * 60.0 ) )
                                            mSet_ServiceMsg( _Srv_No_EDS_Nom ) ;
              #endif
                     break ;
                   }
                   //  Задаем для РС поддерживать, далее, текущую скорость.
                 Z_Skor = ZISkor ;  // Полученный выход ЗИ скорости принимаем, как заданную скорость,
                 if ( (sw)Skor > 0 ) _r.Skor2Z = Skor  ;  // ???(надо подумать) и скорость, как скорость перехода во вторую зону.

                   /*   Таблицу начинаем заполнять с конца и ее самый
                    * старший член принимаем равным номинальному значению
                    * потока, выше которого задание не имеет права подниматься.
                    */
                 upr_bx = _Nf ;
                 Ivz.t [ upr_bx-- ] = _Iv_nom ( 1.0 ) ;
                   // Снижаем задание ЭДС на одну ступень ( 1/20 ) от zeds.
                 _r.Z_EDS  = zeds * upr_bx / _Nf ;
                 upr_ax = V.Fv_zad , upr_time = Timer1_Ovr , upr_label = k30 ;
                 break;

       case k30:  upr_ax = ( upr_ax + V.Fv_zad ) / 2 ; // Усреднение заданий на поток.
                     /*   Выдержка времени на успокоение переходнго процесса
                      * очередной ступени.
                      */
                  if ( (u)((w)(Timer1_Ovr - upr_time)) < _Sec( 3.0 )) break ;

                     /*   Самонастройка завершается по достижении заданием
                      * на поток уставки минимально доп. потока.
                      */
                  if ( upr_ax > _r.Iv_zad_Min && upr_bx > 0  )
                    {
                      Ivz.t [ upr_bx-- ] = upr_ax ;
                   // Снижаем задание ЭДС на одну ступень ( 1/20 ).
                      _r.Z_EDS  = zeds * upr_bx / _Nf ;
                      upr_time = Timer1_Ovr ;
                    }
                  else
                    {   // равномерно делим оставшуюся часть кривой.
                      upr_ax = Ivz.t [ upr_bx+1 ] / (upr_bx+1) ;
                        // равномерно заполняем оставшуюся часть таблицы.
                      while ( upr_bx != 0 )
                        {
                          Ivz.t [ upr_bx ] = upr_ax * upr_bx ;
                          upr_bx-- ;
                        }
                        /*   Самый младший член принимаем равным нулевому
                         * значению потока.
                         */
                      Ivz.t [ 0 ] = 0 ;

                       /*  Самонастройка завершена - сбрасываем скорость.  */
                      _r.Z_EDS   =  zeds , zeds = 0 ;
                      _r.T_ZISkorP_Razg = tzisk  ;
                      _r.Z_SkMax_P = zskmax  ;
                      Z_Skor = _Skor_nom( 0.0 ) ;
                      _r.dN_Max = dn_max_copy ;
                      //V.flg._.otkl_func = 0 ; //заменил на восстановление прежнего значения
                      _r.Cfg._.Dve_Zony = dve_zony_copy;
                      V.flg._.otkl_func = otkl_func_copy;

                      // Инициализируем рабочую уставку Задания ЭДС рассчетной :
                      _r.Z_II_EDS = _r.Z_EDS ;

                      output_s ( "\r\n ЕРС-Ok." ) ;
                      upr_label = k35 ;
                    }
                 break;
                   /*   Ожидание остановки двигателя.
                    */
       case k35:      if ( (sw)Skor < _r.Ostanov_skor )
                      {   // переводим КТЭ в сборку готовности.
                        Isp._.Samonastr = 0;
                        mSet_AvarMsg( _Av_VR1 ) ;
                        bo_Gotov = 0 ,  Prz._.VR1 = 1 ;
                        upr_label=k0;
                      }
                 break ;

             //-------------------
                    /*            ИСПЫТАТЕЛЬНЫЕ РЕЖИМЫ:
                     * ЗАДАНИЕ ОТ РЕЗИСТОРА НА СИФУ-Возб.
                     */
       case k140:
                #ifdef _Vozb_KTE
                    //---
                    // DAN 22.11.2013 - В файле SIFU_V.C при включенных наладочных режимах
                    // РТВ не выполняется , соответственно задание не перебивается .
                    //V.flg._.RT = 0 ; /* откл. РТВ. */
                    //---
                    // Т.к. этот наладочный режим выполняется в Сборке Готовности , то включаем След :
                    Prg.all |= _Sled ;
                    upr_label = k145 ;
                    // DAN 27.07.2020 - Сделана отдельная ветка , чтобы не взводить постоянно след .
                    // При испытаниях ТЕП для бурового станка выявлено , что если войти в работу в режиме
                    // "СИФУВ-рез" и произойдет Авария ( например , "If-макс" ) , то ее невозможно
                    // будет сбросить , т.к. аварийный свитч залипнет в ожидании отключения следа ...
       case k145:
                    // 04.10.2018 - При полном диапазоне АЦП в одной полярности (512*_K_diskr) из-за смещений
                    //              можно не выдавить Alfa_min , поэтому берем меньший диапазон :
                    upr_ax = (sw)( (slw)(sw)zad_res.out *
                                   (slw)(sw)((_r.V_Alfa_Max-_r.V_Alfa_Min)/(400*_K_diskr) ) ) ;
                    if ( (sw)upr_ax < 0 )             V.Alfa = _r.V_Alfa_Max ;
                    else if ( upr_ax > _r.V_Alfa_Max) V.Alfa = 0 ;
                    else                              V.Alfa = _r.V_Alfa_Max - upr_ax ;
                #endif
                  break;
             //-------------------
                    /*            ИСПЫТАТЕЛЬНЫЕ РЕЖИМЫ:
                     * ЗАДАНИЕ ОТ РЕЗИСТОРА НА РЕГУЛЯТОР ТОКА.
                     */
       case k150:
                  // Если даже в Сборке готовности это сообщение было замаскировано , то здесь ,
                  // пока резистор не поставлен в крайнее левое положение , ни импульсы не подадутся ,
                  // ни регуляторы не включатся :
                  if ( (sw)zad_res.out > (sw)5 )  //0 - DAN 20.05.2016 - Дал маленький допуск на сбитый АЦП .
                  {
                    mSet_PreduprMsg( _Pr_Podano_ZSk   ) ;
                    break ;
                  }
                    mClr_PreduprMsg( _Pr_Podano_ZSk   ) ;

              #ifdef  bi_QKDT
                 if ( bi_QKDT == 1 ) break ; // Если контактор ДТ не разомкнулся , выход .
              #endif
                  if ( Isp._.NumMost == 0 ) S.NumMost = 1 ;
                  else                      S.NumMost = 2 ;
                  //-------
                  if ( (u)((w)(Timer1_Ovr-upr_time)) > _Sec(0.5) )
                  {
                    mVkl_Imp( _All_imp ) ;
                    //---
              #ifdef _KTE_GD // при отключённом ЛК включаем РН с нулевым заданием :
                    if ( bi_LK == 0 )
                    {
                      RN_null () ;
                      break;
                    }
              #endif         // при вкл. ЛК включаем полную систему регулирования :
                    //---
                    Prg.all = (Prg.all & _Sled) | _RegTok | _Blok_upr ; /* вкл. РТ. */
                    upr_label = k153 ;
                  }
                  break;
       case k153:

                      upr_ax = zad_res.out ;
             #ifndef _KTE_GD
                          // Не пускаем резистор в другую полярность.
                      if ( (sw)upr_ax < 0 ) upr_ax = 0 ;

                        // для моста назад даем отрицательное задание на ток.
                      if ( Isp._.NumMost != 0 ) upr_ax = ~upr_ax + 1 ;
                      // 12.09.2008 11:01 - Масштабируем так , чтобы выдавить 3 номинала тока :
                      // 04.10.2018 - При полном диапазоне АЦП в одной полярности (512*_K_diskr) из-за смещений
                      //              не выйдет ровно 3 номинала , будет меньше , ну и ладно ...
                      upr_ax = (sw)( (slw)(sw)upr_ax * (slw)(sw)_Id_nom(3.00) / (slw)(sw)(_AD_MAX) ) ;
             #else  // при отключённом ЛК включаем РН с нулевым заданием :
                    if ( bi_LK == 0 )
                    {
                      RN_null () ;
                      upr_label = k150 ; // возврат на ветку выше .
                      break;
                    }
                      // 12.09.2008 11:01 - Масштабируем так , чтобы выдавить 3 номинала тока :
                      // 04.10.2018 - При полном диапазоне АЦП в одной полярности (512*_K_diskr) из-за смещений
                      //              не выйдет ровно 3 номинала , будет меньше , ну и ладно ...
                      upr_ax = (sw)( (slw)(sw)upr_ax * (slw)(sw)_Ig_nom(3.00) / (slw)(sw)(_AD_MAX) ) ;
             #endif
                      OuRegS_dop_kod = upr_ax ;

                  break;
             //-------------------
                    /* ЗАДАНИЕ ОТ РЕЗИСТОРА НА СИФУ.
                     */
       case k160:
                  // Если даже в Сборке готовности это сообщение было замаскировано , то здесь ,
                  // пока резистор не поставлен в крайнее левое положение , импульсы не подадутся :
                  if ( (sw)zad_res.out > (sw)5 ) //0 DAN 20.05.2016 - Дал маленький допуск на сбитый АЦП .
                  {
                    mSet_PreduprMsg( _Pr_Podano_ZSk   ) ;
                    break ;
                  }
                    mClr_PreduprMsg( _Pr_Podano_ZSk   ) ;

              #ifdef  bi_QKDT
               #ifndef _KTE_GD
                 if ( bi_QKDT == 1 ) break ; // Если контактор ДТ не разомкнулся , выход .
               #endif
              #endif
                  if ( Isp._.NumMost == 0 ) S.NumMost = 1 ;
                  else                      S.NumMost = 2 ;
                  //-------
                  if ( (u)((w)(Timer1_Ovr-upr_time)) > _Sec(0.5) )
                  {
                    mVkl_Imp( _All_imp ) ;
                    Prg.all = (Prg.all & _Sled) | _Blok_upr ; /* откл. регуляторы. */
                    upr_label = k163 ;
                  }
       case k163:

                    // 04.10.2018 - При полном диапазоне АЦП в одной полярности (512*_K_diskr) из-за смещений
                    //              можно не выдавить Alfa_min , поэтому берем меньший диапазон :
                    upr_ax = (sw)( (slw)(sw)zad_res.out *
                                   (slw)(sw)((_r.S_Alfa_Max-_r.S_Alfa_Min)/(400*_K_diskr) ) ) ;
                    if ( (sw)upr_ax < 0 )             S.Alfa = _r.S_Alfa_Max ;
                    else if ( upr_ax > _r.S_Alfa_Max) S.Alfa = 0 ;
                    else                              S.Alfa = _r.S_Alfa_Max - upr_ax ;

                  break;
             //-------------------
                    /* ШТАТНЫЙ РЕЖИМ.
                     */
       case k200x:      // Отработка команды CAN-останов.
                    S.Alfa  = _r.S_Alfa_Max ; // Команда на задвигание УИ в АльфаМакс.
                    Prg.all = _Sled | _Blok_upr ; // если истекла выдержка или
                    if ( (u)((w)(Timer1_Ovr - upr_time)) >= _r.Time_do_OtklImp
                                       ||  // если снялась команда CAN-останов ,
                         can_ConfigReg ( _CAN_Ostanov ) == 0
                   #ifdef  bi_Technol_Ostanov  // или если снялась дискретная команда -
                          || bi_Technol_Ostanov == 0
                   #endif
                         )// возвращяемся в рабочий режим.
                    {
                      Init_Regs () ; // переинициализация регуляторов.
                      upr_label = k0 ;
                    }
                  break;

       case k199:       /*  Производим контроль текущей скорости
                            в течении 6 пульсов перед подачей импульсов . */
                   #ifndef _KTE_GD // Для ГД вход в работу с РНг без РС и РТг , контроль не здесь .
                    if ( ZI_Init_Skor ( 1 ) == 0 )
                      {
                         /*  Производим штатный пуск. */
                       Prg.all = _Prg_Rabota | _Blok_upr ;
                   #else
                      {
                   #endif
                   #ifndef _ATK_SET  // ИУ включаются не здесь , а после пуска в OBJ.C ...
                        mVkl_Imp( _VR1_imp | _Start_imp ) ;
                   #else
                        // В АР2 отключен bo_Vkl_KZ ( фактическая скорость меньше "N-вкл.КЗ") - выход из режима Шунтировки .
                        if ( flgO._.Shunt_Rot == 1 ) // Выход из режима Шунтировки Ротора :
                        {
                          Prg.all |= (_RegTok | _RegSk );     // Включаем Регуляторы после Режима Шунтировки Ротора .
                          mVkl_Imp( _VR1_imp | _Start_imp ) ; // Включаем ИУ после Режима Шунтировки Ротора .
                          flgO._.Shunt_Rot = 0 ;              // Отключаем режим Шунтировки Ротора .
                          bo_canShunt_End = 0 ;
                          bo_atkShunt_End = 0 ;
                        }
                   #endif
                        upr_label = k200 ;
                      }
                  break;

       case k200:       // Контроль команды CAN-останов.
                    if ( can_ConfigReg ( _CAN_Ostanov ) == 1
                   #ifdef  bi_Technol_Ostanov
                          || bi_Technol_Ostanov == 1
                   #endif
                            )
                    {              // 23.08.06 09:56
                  #ifdef _KTE_GD  // проверки, чтобы не погасить генератор,
                      if (  bi_LK == 0     ||   // когда  ЛК включен и на
                          ((sw)EDS_dop_kod <= (sw)_r.Ostanov_skor // двигателе
                                           &&   // есть ЭДС, чтобы не сжечь ген.
                           (sw)EDS_dop_kod >= (sw)( ~_r.Ostanov_skor + 1 )))
                  #endif
                      {
                        upr_label = k200x,  upr_time = Timer1_Ovr ;
                        break;
                    } }
                  //---     для КТЭ это и весь блок управления, а для ГД
            #ifndef _KTE_GD  // он продолжается дальше.
                  break;
            #else
                 // В одноконтурной структуре это не делаем :
                 if ( _r.Cfg2._.One_RNg == 0 )
                  {     // при вкл. ЛК включаем полную систему регулирования.
                    if ( bi_LK == 1 )
                    {
                            //if ( Prg._.RegTok == 0 )
                       // однократная - теперя проверяется отключенность РС, а не РТ. Чтобы в режиме "РС-Останов"
                      if ( Prg._.RegSk == 0 ) // отключался РТ, и здеся не устанавливался, однако.
                      {    // переинициализация вышестоящих регуляторов.
                        if ( _r.Cfg._.Vrasch_Dvig == 0 )
                         {
                           Set_ZI ( &zi_rs , 0 ) ;
                           Z_Skor = 0, ZISkor = 0;
                         }
                        else  // Возможность включить КТЭ-ГД на ВРАЩАЮЩИЙСЯ ДВИГАТЕЛЬ :
                         {    // 19.12.2008 13:23 - До конца не проработано , сделано для КАСКАДА .
                           if ( ZI_Init_Skor ( 1 ) == 1 ) goto end ;  // ЗИ не инициализировано .
                         }
                        OuIchRS = 0, OuRegS_dop_kod = 0 ; // интегратор и выход рег-ра скорости .
                        OIRT  = 0 ;  /* интегратор регулятора тока */
                        Prg.all &= _Sled | _Blok_upr ;
                        Prg.all |= _ZadSkor | _RegSk | _RegTok | _RN ;
                        end: ; // Не включаем РС и РТг пока ЗИ РС не инициализировано .
                      }
                    }
                    else // при откл. ЛК включаем РН с нулевым заданием.
                    {
                      if ( Prg._.RegTok == 1 || Prg._.RN == 0 )
                      {
                        Prg.all &= _Sled | _Blok_upr ;
                        Prg.all |= _ZadSkor | _RN ;
                        // 05.12.2013 - Если ЛК отключается при работающем под скоростью двигателе ,
                        // необходимо обнулить все ЗИ и переменные , иначе они залипнут :
                        Set_ZI ( &zi_rtg , 0 ) ;
                        OIRT  = 0 ;  /* интегратор регулятора тока */
                        Set_ZI ( &zi_rs , 0 ) ;
                        Z_Skor = 0x0 , OuRegS = 0 , OuRegS_dop_kod = 0 ;
                        ZISkor = 0x0 ; OuIchRS = 0 ;
                      }
                      //---
                      if ( _r.Cfg._.Vrasch_Dvig == 0 )
                      {
                        ORT = 0 ; // Задание РНг обнуляем .
                      }
                      else  // Возможность включить КТЭ-ГД на ВРАЩАЮЩИЙСЯ ДВИГАТЕЛЬ :
                      {    // 19.12.2008 13:23 - До конца не проработано , сделано для КАСКАДА .
                        /* Запоминаем номер текущего пульса как первый пульс */
                        ZI_Init_Skor ( 0 ) ;
                        // Задание РНг здесь не обнуляем .
                      }
                    }
                  }
                 else // Для Одноконтурной системы с одним РНг :
                  {
                    if ( bi_LK == 1 )
                    {
                       // однократная переинициализация вышестоящих регуляторов.
                      if ( tst != 0 )
                      {
                        OuIchRS = 0, OuRegS_dop_kod = 0 ; // интегратор и выход рег-ра скорости .
                        OIRT  = 0 ;  /* интегратор регулятора тока */
                        Prg.all &= _Sled | _Blok_upr ;
                        Prg.all |= _ZadSkor | _RN ;
                        // для однократности :
                        tst = 0 ;
                      }

                    }
                    else // при откл. ЛК включаем РН с нулевым заданием ( обнуление в RT.C ).
                    {
                      if ( Prg._.RegTok == 1 || Prg._.RN == 0 )
                      {
                        Prg.all &= _Sled | _Blok_upr ;
                        Prg.all |= _ZadSkor | _RN ;
                      }
                      //---
                      // для однократности :
                      tst = 1 ;
                    }
                  }
                  break;
             //-------------------
                    /* ЗАДАНИЕ ОТ РЕЗИСТОРА НА РЕГУЛЯТОР НАПРЯЖЕНИЯ.
                     */
       case k190:
                    mVkl_Imp( _All_imp ) ;
                    Prg.all = (Prg.all & _Sled) | _RN | _Blok_upr ; /* вкл. РТ. */
                    upr_label = k193 ;
                  //break;
       case k193:
                    ORT = zad_res.out << _Ug_Shift ;
                  break;
             //-------------------
                    // Опробование в режиме РН командами Больше-Меньше.
       case k180:   //-------
                    //zi_oprob.out         = _Ud_nom( 0.0 ) ;//_r.S_Alfa_Max ;
                    Set_ZI ( &zi_oprob , 0 ) ;
                    zi_oprob.temp_p_razg = &_or.ZI_oprob ;
                    zi_oprob.temp_p_torm = &_or.ZI_oprob ;
                    zi_oprob.temp_m_razg = &_or.ZI_oprob ;
                    zi_oprob.temp_m_torm = &_or.ZI_oprob ;
                    zi_oprob.temp_parabola = 0 ; // адрес = 0 , сама уставка
                                                 // в UST_CNST.H игнорируется .
                    mVkl_Imp( _All_imp ) ;
                    Prg.all = (Prg.all & _Sled) | _RN | _Blok_upr ; /* вкл. РТ. */
                    upr_label = k183 ;
                  //break ;
       case k183:
                  #ifndef _Obj_Oprob
                    if ((bi_Menshe == 1 && bi_Bolshe == 1)
                                        ||
                        (bi_Menshe == 0 && bi_Bolshe == 0))
                                               zi_oprob.in = zi_oprob.out ;
                    else if ( bi_Bolshe == 1 ) zi_oprob.in =  _r.Ug_zad_max ;
                    else                       zi_oprob.in = ~_r.Ug_zad_max+1 ;
                  #else
                    Obj_Oprob () ;
                  #endif

                        // Ug# изменяем по ЗИ.
                    Zad_Intens ( &zi_oprob ) ;
                    ORT = zi_oprob.out ;
                  //-------

                    // По отпусканию кнопки "Блокировка" просто снимаются команды "Больше-Меньше" .
                    // А отключение происходит при отключении тумблера "Опробование" :
                    if ( bi_Blokir == 0 )
                      {
                        ORT = 0 ;
                        //zi_oprob.out = 0 ;    // 28.07.2017 9:03 Нужно обнулять всю структуру zi_oprob, иначе
                        //zi_oprob.in  = 0 ;    // при отпускании кнопки "Блокировка" выход в структуре медленно падает и
                        Set_ZI( &zi_oprob, 0 ); // при последующем нажатии кнопки "Блокировка" на выходе сразу есть сигнал.
                        //mSet_AvarMsg( _Av_VR1 ) ; // переводим КТЭ в сборку готовности.
                        //bo_Gotov = 0 ;//,  Prz._.VR1 = 1 ;
                      }
                  break;
            #endif
             //-------------------
                    /* ЦИКЛЫ
                     */
       case k170:
              #ifdef  bi_QKDT
                 if ( bi_QKDT == 1 && Ckl._.RTV != 1
               #ifdef _KTE_GD
                       && Ckl._.RN != 1 && Ckl._.SIFU != 1
               #endif
                                           ) break ; // Если контактор ДТ не разомкнулся , выход .
              #endif
                      if ( (u)((w)(Timer1_Ovr-upr_time)) > _Sec(0.5) )
                      {
                        mVkl_Imp( _All_imp ) ;
                        upr_label = k173 ;
                      }
                  break;
       case k173:
                    #ifdef _KTE_GD // при отключённом ЛК включаем РН с нулевым заданием :
                       if ( bi_LK == 0 && Ckl._.RN != 1 && Ckl._.RTV != 1 && Ckl._.SIFUV != 1 && Ckl._.SIFU != 1 )
                       {
                         // только для тех циклов , в которых необходимо погасить остаточное намагничивание
                         // генератора , для последующего включения ЛК :
                         RN_null () ;
                         break;
                       }
                    #endif
                      //---
                      // 13.11.2013 - DAN добавил блок управления , т.к. иначе выходит из этой функции .
                      // Но теперь все выбранные регуляторы будут постоянно включены и выключить их будет нельзя :
                      if ( Ckl._.RP == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RegTok | _RegSk | _RP ;
                        }
                      else if ( Ckl._.RS == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RegTok | _RegSk ;
                        }
// 09.06.2020 15:35     else if ( Ckl._.Reg_EDS == 1 )
//                      {
//                        Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RegTok | _RegSk | _RP ;
//                      }
                      else if ( Ckl._.RT == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RegTok ;
                        }
                      else if ( Ckl._.RT1 == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RegTok ;
       #ifdef  _SIFU2_
                          S2.Disable = 1;
       #endif
                          S.Disable  = 0;
                        }
                      else if ( Ckl._.RT2 == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RegTok ;
       #ifdef  _SIFU2_
                          S2.Disable = 0;
       #endif
                          S.Disable  = 1;
                        }
                      else if ( Ckl._.RN == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl | _RN ;
                        }
                      else if ( Ckl._.RTV == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl ;
                        }
                      else if ( Ckl._.SIFUV == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl ;
                        }
                      else if ( Ckl._.SIFU == 1 )
                        {
                          Prg.all = (Prg.all & _Sled) | _Blok_upr | _Cikl ;
                        }
                 break;

#ifdef   _AVTONASTR
       case k210 :  //-----   Автонастройка.   ------
                   S.NumMost = 1 ;
                  //-------
                  if ( (u)((w)(Timer1_Ovr-upr_time)) > _Sec(0.5) )
                  {
                    mVkl_Imp( _All_imp ) ;
                    Prg.all = _Sled | _Blok_upr ; /* откл. регуляторы. */
                    Avtonastroyka_RT ( 2 ) ;  // Инициализация
                    upr_label = k220 ;
                  }
                  break;
      case k220 :
                Avtonastroyka_RT ( 1 ) ;  // Работа АН
               // Prg._.Blok_upr = 0;
                break;
#endif

     }
  return ;
}

//------------------------------------------------------------------------------------------------

// Программа инициализации ЗИРС текущей скоростью для включения на вращающийся двигатель .
word ZI_Init_Skor ( word num )
{
 static byte  first_puls , count_puls;
 static word  skor_sum ;
 word   ax ;
 ax = 1 ;

 switch ( num )
  {
    default :
    case 0 :
          /* Запоминаем номер текущего пульса как первый пульс */
      first_puls = (b)Puls_counter ;
      count_puls = 0 , skor_sum = 0 ;
      //---
    break;

    case 1 :
          /*  Производим контроль текущей скорости
              в течении 6 пульсов перед подачей импульсов . */
    if ( (b)Puls_counter != first_puls )
    {
      first_puls = (b)Puls_counter ;
        //---
      count_puls++ ;
      skor_sum += Skor ;
      // Ориентируемся по Puls_counter , тк фон может разростись :
      if ( count_puls >= 5 ) // ПЕРЕПОЛНЕНИЯ НЕ БУДЕТ ДО 2х НОМИНАЛОВ СКОРОСТИ !
        {
        //resulSk = (sw)skor_sum / (sw)(w)count_puls ;
          Set_ZI ( &zi_rs , (sw)skor_sum / (sw)(w)count_puls ) ;
          //Z_Skor = zi_rs.in ; //30.11.2011 15:31 не нужно . Задание также инициализируем , чтобы оно не испортило ЗИ в РС .
          //ZISkor = zi_rs.in ; //30.11.2011 15:31 не нужно .
          ax = 0 ;
        }
    }
      //---
    break;

  }
 return ax ;
}

//------------------------------------------------------------------------------------------------

// Программа для входа в испытательные режимы ГД с первоначальным гашением напряжения генератора
// для последующего включения ЛК .
#ifdef _KTE_GD
 void RN_null ( void )
 {
   // при отключенном ЛК включаем РН с нулевым заданием :
   if ( Prg._.RegTok == 1 || Prg._.RN == 0 )
   {
     // однократная переинициализация вышестоящих регуляторов :
     Prg.all &= _Sled | _Blok_upr ; // побитовое "или" , чтобы не "мигнуть" Следом или Блоком Управления .
     Prg.all |= _ZadSkor | _RN ;
    // DAN 22.11.2016 13:42 - Добавлена инициализация интеграторов :
    // 05.12.2013 - Если ЛК отключается при работающем под скоростью двигателе ,
    // необходимо обнулить все ЗИ и переменные , иначе они залипнут :
    Set_ZI ( &zi_rtg , 0 ) ;
    OIRT  = 0 ;  /* интегратор регулятора тока */
    Set_ZI ( &zi_rs , 0 ) ;
    Z_Skor = 0x0 , OuRegS = 0 , OuRegS_dop_kod = 0 ;
    ZISkor = 0x0 ; OuIchRS = 0 ;
   }
   //---
   ORT = 0 ; // Задание РНг обнуляем .

   return ;
 }
#endif
