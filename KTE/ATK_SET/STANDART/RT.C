
//         ПРОГРАММА  РЕГУЛЯТОРА ТОКА ЯКОРЯ .
//----------------------------------------------------------

void RegTok (void)
 {
     byte  tst1 , tst2 , tst3 ;
     word  ax, bx, cx ;
     lword lax ;

   if ( Ckl._.RT2 == 1 || Isp._.RT2_Res == 1 || S.Disable == 1 )
   {
     // Инициализация РТ1 в наладочных режимах , в которых он не используется :
      OIRT_drob = 0 ;
      ZIDN  = ZIDN1 = 0 ;  /* выход ЗИ-РТ. */
      Set_ZIRT ( &zi_rt , 0 ) ;
      OIRT  = _r.RevU0  ;  /* интегратор регулятора тока */
      OIRT1 = _r.RevU0  ;  /* интегратор регулятора тока */
     //---
     return ;
   }
      tst1 = 0 , tst3 = 0 ;

     //----  Фрагмент вынесен из концов регуляторов скорости и ЭДС
     //   для того чтобы регулятору тока задавать ток, а он уже
     //   разбирался с реверсом и ограничениями. -------

      OuRegS = OuRegS_dop_kod ;

        /*----- Изменение ограничения тока во II зоне ----*/
      ax = Skor ;
      if ( (sw)ax < 0 )  ax = ~ax + 1 ;
         // определяется по изменению скорости двигателя.
      ax -= Skor_II_Z ;
      if ( _r.Cfg._.Dve_Zony == 1  &&  (sw)ax > 0 )
      {
       // Для Моста 1
        if ( (sw)OuRegS >= 0 ) //RegFlg._.OuRS == 0 )
        {
          lax = _r.OuRSMaxMost1 - _r.OuRSMax2Most1 ;
          if ( (slw)lax < 0 ) lax = 0 ;

          //ax = skor - Skor_II_Z ;
          //asm   mulu lax , ax ;
          lax *= (w)ax ;
          ax = _r.Z_SkMax_P - Skor_II_Z ;
          if ( (sw)ax <= 0 ) ax = 1 ;
          //asm   divu lax , ax ;
          //asm   bnv   as      ;          /* не вылез ли результат деления за 2 байта    */
          //asm   ld    lax , #0xffffu ;
      //as:
          lax /= (w)ax ;
          OutRSMaxM1 = _r.OuRSMaxMost1 - (w)lax  ;
          if ( (sw)OutRSMaxM1 < (sw)_r.OuRSMax2Most1 ) OutRSMaxM1 = _r.OuRSMax2Most1 ;

          if ( (sw)OuRegS > (sw)OutRSMaxM1 )  OuRegS = OutRSMaxM1 , Prz._.int_p = 1 ; // до 15.04.2008 флаг не выставлялся .
        }
      // Для Моста 2
        else
        {    // Отрицательная зона.
          lax = _r.OuRSMax2Most2 - _r.OuRSMaxMost2 ;
          if ( (slw)lax < 0 ) lax = 0 ;
          //ax = skor - Skor_II_Z ;
          //asm   mulu lax , ax ;
          lax *= (w)ax ;
          ax = ~_r.Z_SkMax_M + 1 ;
          ax -= Skor_II_Z ;
          //ax = _r.Z_SkMax_M - Skor_II_Z ;
          if ( (sw)ax <= 0 ) ax = 1 ;
          //asm   divu lax , ax ;
          //asm   bnv   an      ;    /* не вылез ли результат деления за 2 байта    */
          //asm   ld    lax , #0xffffu ;
      //an:
          lax /= (w)ax ;
          OutRSMaxM2 = _r.OuRSMaxMost2 + (w)lax  ;
          if ( (sw)OutRSMaxM2 > (sw)_r.OuRSMax2Most2 ) OutRSMaxM2 = _r.OuRSMax2Most2 ;

          if ( (sw)OuRegS < (sw)OutRSMaxM2 )  OuRegS = OutRSMaxM2 , Prz._.int_m = 1 ; // до 15.04.2008 флаг не выставлялся .
        }
      }
      else
      {   /*----- Ограничение тока в I зоне ----*/
        if ( (sw)OuRegS >= 0 ) //RegFlg._.OuRS == 0 )
        {
          if ((sw)OuRegS > (sw)_r.OuRSMaxMost1 ) OuRegS = _r.OuRSMaxMost1 , Prz._.int_p = 1 ;
#ifdef _KTEV
           // Нереверсивный КТЭ (только мост "Вперед" ) . При "Гашении" не ограничиваем .
          else if ( _r.Cfg._.Ne_Revers == 1 && bo_GashenPolya == 0 )
           { // Моста "Назад" нет . Ограничиваем задание на минимуме , чтобы не было "If-мин."
             if ((sw)OuRegS < (sw)_r.OuRSMax2Most1 ) OuRegS = _r.OuRSMax2Most1 , Prz._.int_m = 1 ;
           }
#endif
        }
        else
        {
          if ((sw)OuRegS < (sw)_r.OuRSMaxMost2 ) OuRegS = _r.OuRSMaxMost2 , Prz._.int_m = 1 ;
        }
      }
      //-----------
      MechTorm_upr ( _MT_Id_Zad_Ogr ) ; // Ограничение тока при наложенном МТ .
      //-----------

       //---------------  Ограничение задания на ток.
       // Объектные ограничения после штатного :
      can_ConfigReg ( _CAN_Id_Zad_Ogr ) ; // CAN-ограничение задания на ток
      obj_ConfigReg ( _Obj_Id_Zad_Ogr ) ; // Объектное задание перебивает CAN-задание
       //---------------

      if ( (sw)OuRegS < 0 )  // ВыхРС (вхРТ) отриц. - режим торм-я или реверса .
        {
          //bo_atkOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
          //bo_canOuRS = 1 ;
          if ( _r.Cfg._.Ne_Revers == 1 ) // Нереверсивный КТЭ (только мост
           {                             // "Вперед" ) . Моста "Назад" нет .
             RegFlg._.OuRS = 0 ;         // Флаг положительного Выхода РС .
              //  16.11.06: убрали везде ограничение задания тока на 2-х дискр.
              // при нулевом задании, т.к. при нереверс.КТЭ-500 при испытаниях
              // на 17А двиг. он разгонялся 2-мя дискретами до разноса даже при отриц. задании от РС.
              // а у Вайнблата из-за этого двигатель останавливался при N#=0 20сек,
              // вместо 5сек при полном снятии ИУ.
             OuRegS = 0 ; // 16.11.06 '= 2' ;   // Нулевое задание на мост "Вперед" .
           }
          else  // Реверсивный КТЭ :
           {
             RegFlg._.OuRS = 1 ;       // Флаг отриц. ВыхРС (вкл. моста "Назад")
             OuRegS = ~OuRegS + 1 ;    // Модуль задания .
           }
        }
      else
      {
        RegFlg._.OuRS = 0 ;
        //bo_atkOuRS = 0 ; 
        //bo_canOuRS = 0 ;
      }
      // 1% задания тока , чтобы в канале не появилось отрицательное смещение :
      //16.11.06 if ( OuRegS == 0 )  OuRegS = 0x0002 ;
      //-----------

         // Проверка необходимости реверса.
   #ifndef _ATK_SET
      if ((( S.NumMost == 1 ) && ( RegFlg._.OuRS == 1 ))
                              ||
          (( S.NumMost == 2 ) && ( RegFlg._.OuRS == 0 )))
          {
            OuRegS = 0x0u ;
          //if ( ZIDN <= _r.Temp_RT_M )  S.flg._.Revers = 1 ;
            if ( ZIDN <= _r.Temp_RT_M/300 + 150 )  S.flg._.Revers = 1 ; // приведение ном/сек к плс/сек .
          }
   #else
      if ((( S.flg._.Invertor == 1 ) && ( RegFlg._.OuRS == 1 ))
                              ||
          (( S.flg._.Invertor == 0 ) && ( RegFlg._.OuRS == 0 )))
          {
            OuRegS = 0x0u ;
              // Реверс без сброса тока , с подстановкой нужного интегратора :
              // Процедуру реверса начинаем без сброса тока :
              if       ( S.flg._.Invertor == 1 ) // Переход на отрицательный выход РС :
              {
                  // Подставлять интегратор при этом переходе не нужно , иначе будет удар тока .
                  S.flg._.Invertor = 0 ;
                  bo_canOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
                  bo_atkOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
              }
              else if  ( S.flg._.Invertor == 0 )
              {
                  OIRT = OIRT_for_revers ; // Подставляем рассчитанный ранее интегратор .
                  S.flg._.Invertor = 1 ;
                  bo_canOuRS = 0 ; // Флаг положит. ВыхРС .
                  bo_atkOuRS = 0 ; // Флаг положит. ВыхРС .
              }
          }
   #endif
      else
         {
        // признак реверса был, но снялся регулятором - давать небольшое задание
           if ( S.flg._.Revers == 1 )
             {
              OuRegS = (0x03u*_K_diskr) ;
              Prz._.Revers1 = 1 ;
              Prz._.Revers2 = 1 ; // для РТ2 СИФУ2 , чтоб работал пересчет интегратора при реверсе .
             }
   #ifdef _ATK_SET
           // 14.10.2020 - Почему-то иногда бывало , что после классического реверса , КТЭ-шного ,
           //              который в АТК уже не используется , режим Инвертор/Выпрямитель
           //              перекидывался , а bo_canOuRS не изменялся , что приводило к аварии .
           //              Во избежание данной ситуации , приводим эти два бита в соответствие .
           // 25.08.2021 - Все равно оставляем эту припарку , она не помешает , если выполнится лишний раз :
           else
             {
               if ( S.flg._.Invertor == 0 )
               {
                 bo_canOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
                 bo_atkOuRS = 1 ; // Флаг отриц. ВыхРС - режим торможения .
               }
               else
               {
                 bo_canOuRS = 0 ; // Флаг положит. ВыхРС .
                 bo_atkOuRS = 0 ; // Флаг положит. ВыхРС .
               }

             }
   #endif
           S.flg._.Revers = 0 ;
           S.flg._.ZapretImp = 0 ;

         }

     //-----------------
      IDN1 = IDN;
      ZIDN1 = ZIDN;

      ZIDN =  OuRegS; // Задание тока однополярное - взят модуль .

      if ( ED1 > 126 )  ED1 = 126 ;

      bx = (w) TABLINN[ ED1 ] ;
      lax = (lw)_r.INN0 * (lw)bx  ;
    //DRINN = (b) lax ;
      INN = (w) ( lax >> 8 ) ; // Гранично-непрерывный ток , пересчитанный с учётом ЭДС .

#ifdef  _SIFU2_
      // DAN 24.11.2016 - гранично-непрерывный ток для двигателя - наступает раньше , чем гранично-непрерывный в мосту .
      lax = (lw)_or.INN0_dvig * (lw)bx  ;
      INN_dvig = (w) ( lax >> 8 ) ;
#endif

      //if ( ZIDN > _r.IZMAX )  ZIDN = _r.IZMAX ; 07.07.05 13:57

if ( Isp._.ZIRT_shunt == 0 ) // Если есть ЗИРТ :
{
    /*if ( ZIDN >= ZIDN1 )
        {
          bx = ZIDN - ZIDN1  ;
          if ( bx > _r.Temp_RT_P )  ZIDN = ZIDN1 + _r.Temp_RT_P ;
        }
      else
       {
          bx = ZIDN1 - ZIDN  ;
          if ( bx > _r.Temp_RT_M )  ZIDN = ZIDN1 - _r.Temp_RT_M ;
       }*/

      // Задатчик Интенсивности
#ifdef _ATK_SET
    if ( KTE2_Prinud_com == 0 ) // Обычный режим :
    {
      zi_rt.temp_p = &_r.Temp_RT_P ;
      zi_rt.temp_m = &_r.Temp_RT_M ;
    }
    else // Режим Принудительной коммутации , быстрый ЗИТ :
    {
      zi_rt.temp_p = &_or.Temp_RT_P ;
      zi_rt.temp_m = &_or.Temp_RT_M ;
    }
#endif
      zi_rt.in = (d)ZIDN ;
      Zad_IntensRT ( &zi_rt ) ;
      ZIDN = (w)zi_rt.out ;
}
else
{
      Set_ZIRT ( &zi_rt , ZIDN ) ; // Инициализация всего ЗИРТ .
}

      ax = IDV ;

#ifndef _KTEV
 #ifndef _ATK_SET
      if  ( IDN < (INN - INN/6 )) IDN = ax ;
      else if  ( ax < IDN )       IDN = ax ;
      else                        IDN = ax + (w)( (lw)( ax - IDN ) * (w)_r.KRTDI >> 8 ) ;
      //if ( FSIFU.DIO == 0 ) OIRT1 = OIRT ;
 #else
      if ( flgO._.Id_neprer == 0 ) IDN = ax ; // прерывистый ток .
      else                                    // непрерывный ток ,
      {    // Корректируем ОС только если есть динамика на наростание :
           if  ( ax < IDN )        IDN = ax ;
           else                    IDN = ax + (w)( (lw)( ax - IDN ) * (w)_r.KRTDI >> 8 ) ;
      }
 #endif
#else
      IDN = ax ; // 22.02.2008 8:37 - Для КТЭВа не нужен динамический коэффициент .
#endif

      if ( S.flg._.Fdmin == 0 ) OIRT1 = OIRT ;
      else
          {
            if ( ZIDN1 > IDN )   // и если на прошлом пульсе был Fdmin==1 производим перерасчет интегратора
              {
                 bx = ( ZIDN1 - IDN ) / 2 ;
                 if ( bx > (10*_K_diskr) ) bx = 10*_K_diskr ;

                 tst1 = 1 ;
                 goto ri  ;  // идет на перерасчет интегратора

                // lax = (lw) bx * (lw)KRTI ;
                // if ( lax > 0x0f00u )  lax = 0x0f00u  ;
                // OIRT = OIRT + (w) lax  ;
                // if ( ( OIRT > 0x4000u) || (OIRT > _r.RTMAX ) )  OIRT = _r.RTMAX ;

         ri_ok:              // перерасчет интегратора окончен
                 tst1 = 0 ;
                 OIRT1 = OIRT ;
              }

          }

#ifndef _KTEV
 #ifndef _ATK_SET
  #ifdef  _SIFU2_
      // 13.06.2018 13:15 - Шестаков сказал , что для 12-ти пульсных сделать возможность изменения :
      if ( ( ZIDN1 >= INN ) && ( IDN > (sw)((slw)(sw)INN * (slw)(sw)_or.KINN >> 8)) ) //_or.KINN = 0.8
  #else
      if ( ( ZIDN1 >= INN ) && ( IDN > ( INN - INN / 5 )) )
  #endif
        {
          tst2 = 0 ;
          if (ZIDN < INN )
            {
              if  ( INN <= (3*_K_diskr) )  // 16.11.06  ZIDN = 1 ;
              {      // 16.11.06 пока ZIDN не нуль, делаем кк и делали "ZIDN=1",
                if  ( ZIDN != 0 )  ZIDN = 1*_K_diskr ; // а в остальном пропускаем "0".
              }
              else              ZIDN = INN - (3*_K_diskr) ;
            }

        }
      else
        {
          tst2 = 1 ;
          if ( ZIDN >= INN )
            {
                 ZIDN = INN + INN / 15 + (1*_K_diskr) ;
            }
        }
 #else // Для АТК не делается порог задания тока на уровне гранично непрерывного .
       // Прерывистый или непрерывный режим определяется по измерениям тока перед ИУ .
      if ( flgO._.Id_neprer == 1 ) tst2 = 0 ;
      else                         tst2 = 1 ;
 #endif
      //01.03.2017 - Коэффициенты РТ берутся из двух мест - из уставки или рассчитываются АН :
      if  ( tst2 == 0 )  KRTI = _r_KRTNI;  //_r.KRTNI;    - Ти для непрерыного тока .
      else               KRTI = _r_KRTPRI; //_r.KRTPRI;   - Ти для прерывистого тока .

#else
      tst2 = 0 ; // Заглушка для компилятора .
      KRTI = _r.KRTNI; // 22.02.2008 8:37 - для КТЭВа не нужно хитрое обрезание задания и
                       //                   прерывистый коэффициент .
#endif


  //  bx = ZIDN - IDN ;
      bx = IDN - ZIDN ;

      if ( (sw)bx >= 0 )
        {
          if ( S.flg._.Fmax == 1 )  goto r ;
        }
      else
        {
          if ( S.flg._.Fmin == 1 )  goto r ;
        }

   ri:

   lax = KRTI ;

   if ( lax == 0 )
     {             // инициализация интегратора при Ки = 0 :
       OIRT = _r.RevU0 ;
       OIRT_drob = 0 ;
       goto r ;
     }

    //-------------- 01.04.09 -------------------------------------

    // 3.3 мс - такт счёта , раз в пульс .
    // 65535  - основание интегратора и выхода РТ (дробная часть) , в конце происходит сдвиг на 16 разрядов влево .
    // 64     - основание уставки Ти (дробная часть) для возможности задать доли миллисекунды .
    lax = (lw)( (d)_Grad( 1 ) / (d)_Id_nom ( 0.01 ) *  3.3 * 65535. * 64. ) / lax ;
    lax &= 0x7ffffffful ;  //защита от "-" коэфф.

    //--------------------------------------------------
    cx = bx ;                     // ошибка .
    if ( (sw)cx < 0 )  cx = -cx ; // выпрямленная ошибка .
    // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
    // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
    if ( ((lw)cx >= (lw)0x7fffffff / lax) && (lax != 0) )    // sravnivaem modul oshibki
     {                                       // s maksimalno dopustimoy
       if ( (sw)bx >= 0 ) lax = 0x7fffffff ; // pri vychislennom 'Ki',
       else               lax = 0x80000000 ; // dlya 32-bit setki oshibkoy.
     }
    else  lax = (slw)lax * (slw)(sw)bx ;     // умножение интегр. коэффициента на ошибку
    //--------------------------------------------------

    // lax = (lw) bx * (lw) KRTI ;
    // if ( lax > 0x4000u ) lax = 0x4000u ;
    if ( (slw)lax >= ((slw)0x4000u << 16) )   lax = (lw)0x4000u << 16 ;  //оставшееся ограничение Шестакова

    if ( tst1 == 1 && (slw)lax >= ((slw)0x0f00u << 16) )   lax = (lw)0x0f00u << 16 ;  // ограничение при tst1==1

    // 08.10.2013 - Эти две проверки почему-то были однополярные , хотя lax м.б. отрицательным при отрицательной ошибке :
    // 22.10.2013 - В таком виде эти проверки , однако не работают. РТ блокируется вообще :
    // оставшееся ограничение Шестакова :
  /*lbx   =  (lw)(0x4000 * _K_diskr) ;
    lbx <<= 16 ;
    if ( (slw)lax >= (slw)lbx ) lax = lbx ;

    lbx   = (slw)((sw)0xC000 * _K_diskr) ;
    lbx <<= 16 ;
    if ( (slw)lax <  (slw)lbx ) lax = lbx ;

    // ограничение при tst1==1 :
    if ( tst1 == 1 && (slw)lax >= ((slw)0x0f00u*_K_diskr << 16) ) lax = (lw)0x0f00u*_K_diskr << 16 ;

    lbx   = (slw)((sw)0xf100 *_K_diskr) ;
    lbx <<= 16 ;
    if ( tst1 == 1 && (slw)lax <  (slw)lbx ) lax = lbx ;*/

       //  Подготовка к контролю переполнения (без использ.'asm'):
       // если до сложения/вычитания операнды были одного знака, а результат
       // получился другого знака - значит произошло переполнение.
     cx = 2 ;
     if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
      {
          if( (sw)OIRT >= 0 ) cx = 0 ; // +/+
      }
     else if( (sw)OIRT <  0 ) cx = 1 ; // -/-

     lax += (slw)(sw)OIRT << 16 ;
     lax += (lw)(w)OIRT_drob ;   // DROB ISN'T SIGNED !

              /* Проверка переполнений. */
                  //  переполнение в плюс?
          if     ( cx == 0 && (slw)lax <  0 ) goto v1 ;
                  //  переполнение в минус?
          else if( cx == 1 && (slw)lax >= 0 ) goto v2 ;
    //--------------------------------------------------

              /* Проверка ограничений. */
          if ( (slw)lax < ((slw)_r.RTMIN << 16) )
            {
    v2:       lax = (lw)_r.RTMIN << 16 ;
            }
          else if ( (slw)lax >= ((slw)_r.RTMAX << 16) )
            {
    v1:       lax = (lw)_r.RTMAX << 16 ;
            }

     OIRT = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .
     OIRT_drob = lax ;       // запись дробной части .


    if ( tst1 == 1 )  goto ri_ok  ;
    if ( tst3 == 1 )  goto ri_ok1 ;
  //-----------------------------------------------------------------------

  r:

    if ( tst2 == 1 )
      {
        ORT = OIRT;
      }
    else    //ДДДДДД  Расчет пропорциональной составляющей и выхода регулятора. ДДДДДД
      {
        //lax = (lw)bx * (lw)_r.KRTP ;
        //if ( lax > 0x4000u ) lax = 0x4000u ;

#ifndef _KTEV
        //01.03.2017 - Коэффициенты РТ берутся из двух мест - из уставки или рассчитываются АН :
        lax = _r_KRTP ; //_r.KRTP ;
#else
        lax = _r.KRTP ;
#endif
                                            // "<< 8"-догоняем "Kp*256" до формата
        lax = lax * _Grad( 1 ) / _Id_nom ( 0.01 ) << 8 ;
        lax &= 0x7ffffffful ;  //защита от "-" коэфф.

        //---------- preventive overflow control -----------
        cx = bx ;                     // ошибка .
        if ( (sw)cx < 0 )  cx = -cx ; // выпрямленная ошибка .
        // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
        // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
        if ( ((lw)cx >= (lw)0x7fffffff / lax) && (lax != 0) )    // sravnivaem modul oshibki
          {                                       // s maksimalno dopustimoy
            if ( (sw)bx >= 0 ) lax = 0x7fffffff ; // pri vychislennom 'Kp',
            else               lax = 0x80000000 ; // dlya 32-bit setki oshibkoy.
          }
        else  lax = (slw)lax * (slw)(sw)bx ;


        //  Подготовка к контролю переполнения (без использ.'asm'):
        // если до сложения/вычитания операнды были одного знака, а результат
        // получился другого знака - значит произошло переполнение.
        cx = 2 ;
        if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
          {
             if( (sw)OIRT >= 0 ) cx = 0 ; // +/+
          }
        else if( (sw)OIRT <  0 ) cx = 1 ; // -/-

        lax += (slw)(sw)OIRT << 16 ;
        lax += (lw)(w)OIRT_drob ;   // DROB ISN'T SIGNED !

                  /* Проверка переполнений. */
                      //  переполнение в плюс?
              if     ( cx == 0 && (slw)lax <  0 ) goto p3 ;
                      //  переполнение в минус?
              else if( cx == 1 && (slw)lax >= 0 ) goto p2 ;
                      //  нет переполнения.

                  /* Проверка ограничений. */
              if ( (slw)lax < ((slw)_r.RTMIN << 16) )
                {
       p2:          ORT = (lw)_r.RTMIN ;
                }
              else if ( (slw)lax >= ((slw)_r.RTMAX << 16) )
                {
       p3:          ORT = (lw)_r.RTMAX  ;
                }
              else  ORT = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .

      }


   //----------------------------------------

        //Если РТ вызван не программой 'Реверс', и был реверс на прошлом пульсе -
            //   перерасчет инт.части, если сняты подтверждающие ИУ
            // чтобы она не застревала в угле начально-непрерывного тока
            // и при включении подтверждающих ИУ не было броска тока.

        if ( ( stop_pointR1 == 0 ) &&  (( S.flg._.Revers == 1 ) || ( Prz._.Revers1 == 1 )))
          {
            Prz._.Revers1 = 0 ;

          //-----
             if ( ( ZIDN1 > IDN ) && ( IDN < (5*_K_diskr) ) )
               {
                 bx =  ZIDN1 - IDN ;
                 if ( bx > (3*_K_diskr) )
                   {
                    tst3 = 1 ;
                    goto ri  ;  // идет на перерасчет интегратора

                //   s_lax = (lw)s_ax * (lw)KRTI ;
                //   s_lax = (lw)OIRT + s_lax ;
                //   if ( (u)(w) s_lax >  _r.RTMAX ) OIRT = _r.RTMAX ;
                //   else                         OIRT = (w) s_lax  ;

            ri_ok1:            // перерасчет интегратора окончен
                    tst3 = 0 ;
                   }
               }
          }


    return;
 }

//------------------------------------
		/*Программа линеаризации */

void Linear (void)
{
   register word  ax , bx , cx ;

  if ( ORT <= _Ugol_90 )  ax = ORT ;
  else                    ax = _Ugol_180 - ORT ;
    bx  = LIN [ ax >> 8 ] ;
    cx  = LIN [(ax >> 8) + 1 ] ;
    cx -= bx ;
    bx += (w)( (lw)cx * (lw)(ax & 0x00FFu) / 0x0100ul ) ;
  if ( ORT <= _Ugol_90 ) S.Alfa = bx;
  else                   S.Alfa = _Ugol_180 - bx ;
return;

}

//------------------------------------
        /*Программа ЗИРТ */

 void Zad_IntensRT ( struct ZIRT *zip )
{
//    Т.к. эта функция вызывается как из фона так и
//  из прерываний то, по-скольку компилятор не позволяет описать функцию
//  как реентерабельную, для сохранения временных переменных в стеке их
//  следует описать как автоматические, а не как регистровые (т.к.
//  автоматические переменные компилятор распологает в стеке).

//  Однополярный ЗИРТ , для однополярного РТ .

#if _K_diskr == 1 // 10-ти разрядный АЦП - 200d .
  lword lax ;
   word ax;

//ax = (w)( timer1 - zip->time ) / (w)_Sec( 1.0 ) ;
// FAA  _Sec( 4.0 ) - dla povisheniya tocnosti v preobrazov. makrosa (esli brat _Sec( 1.0 ) to pri tempe 70 za 10 sek poluchaem ~810, a pri _Sec( 4.0 ) oshibka ne vidna
  ax = (w)((lw)(4ul * (lw)(w)( timer1 - zip->time ) ) / (lw)_Sec( 4.0 )) ;
  zip->time = timer1 ;  // запись момента текущей отработки ЗИ.

  if ( (w)zip->in != (w)zip->out )
    {
      lax = (lw)zip->drob ;
      lax += (lw)zip->out << 16 ;

      if ( (w)zip->in > (w)zip->out )
        {
          lax += (lw)*zip->temp_p * (lw)ax ;
          zip->drob = (w) lax;
          zip->out  = (w) ( lax >> 16 ) ;
          if ( (w)zip->out > (w)zip->in ) zip->out = zip->in ;
        }
      else
       {
          lax -= (lw)*zip->temp_m * (lw)ax ;
          zip->drob = (w) lax;
          zip->out  = (w) ( lax >> 16 ) ;
          if ( (w)zip->out < (w)zip->in ) zip->out = zip->in ;
    }  }
#else // 12-ти разрядный АЦП - 800d .

   double ax;

// FAA  _Sec( 4.0 ) - dla povisheniya tocnosti v preobrazov. makrosa (esli brat _Sec( 1.0 ) to pri tempe 70 za 10 sek poluchaem ~810, a pri _Sec( 4.0 ) oshibka ne vidna
//ax = (d)(w)( timer1 - zip->time ) / (d)((lw)_Sec( 1.0 ) << 16);
  ax = (d)((lw)(4ul * (lw)(w)( timer1 - zip->time )))/ (d)((lw)_Sec( 4.0 ) << 16);
  zip->time = timer1 ;  // запись момента текущей отработки ЗИ.

  // Темпы берутся с номиналом 200 дискрет , поэтому приводим в соответствие с номиналом .

  if ( zip->in != zip->out )
    {
      if ( zip->in > zip->out )
        {
          zip->out += (d)*zip->temp_p * (d)_K_diskr * ax ;
          if ( zip->out > zip->in ) zip->out = zip->in ;
        }
      else
       {
          zip->out -= (d)*zip->temp_m * (d)_K_diskr * ax ;
          if ( zip->out < zip->in ) zip->out = zip->in ;
    }  }
#endif

  return ;
}

void Set_ZIRT ( struct ZIRT *zip , word ax )
{
#if _K_diskr == 1 // 10-ти разрядный АЦП - 200d .
  zip->in = ax ;
  zip->out = ax ;
#else // 12-ти разрядный АЦП - 800d .
  zip->in = (d)ax ;
  zip->out = (d)ax ;
#endif
  zip->drob = 0 ;
  zip->time = timer1 ;

  return ;
}
