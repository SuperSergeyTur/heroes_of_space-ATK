
#ifndef _F16e
    #include "dzv_drv.c"
#endif

//         ПРОГРАММА УПРАВЛЕНИЯ СИФУ ВОЗБУДИТЕЛЯ.
//------------------------------------------------------------



//     ПРОГРАММА РАЗДЕЛЬНОГО УПРАВЛЕНИЯ ( РЕВЕРСИРОВАНИЯ ).
//--------------------------------------------------------

//   Для разрешения реверса необходимо, чтобы в двух сериях измерений,
// отстоящих на 10 градусов, был удовлетворительный результат "два из трех".

void  Revers_epa_init ( void )
{     //  !!! ОСОБЕННОСТЬ ЕПА В ТОМ ЧТО ОН ПОСТОЯННО СРАБАТЫВАЕТ ПРИ КАЖДОМ
     // ОБОРОТЕ ТАЙМЕРА, ДАЖЕ ЕСЛИ В EPA_TIME НИЧЕГО НЕ ЗАПИСЫВАЛИ.
    Revers_Label = 2 ; // для возможности выхода по default при
                // холостом срабатывания EPA через полный оборот таймера.
    init_sifu_epa( _revers_epa_con ) ;

    #ifndef _F16e
        init_DZV() ;
    #endif
#ifdef _SIFU2_
    #ifndef _F16e
        init_DZV2() ;
    #endif
#endif
  return ;
}

//-------  Опрос необходимости реверса и его Инициализация. ----

void  Revers_start ( void )
{   //    Для 12-ти пульсн.СИФУ реверс запускается из второго СИФУ
    //  после его отработки, чтобы не было гонок сигналов.
    if ( S.flg._.Revers == 1 )
      {
          // Срезаем длинный ИУ (для режима с ИУ=120грд.)
#ifndef _F16e
        mPort_Imp(FOR0[0]) ;
        mFzapoln1_stop() ;// снимаем оба частотных заполнения.
        mFzapoln2_stop() ;
#else
        mPort_Imp(FOR0[0][0]) ;

#endif
        S.flg._.ImpSet1 = 0 ; // для разрешения контроля ДЗВ в реверсе.
              // если импульс не был сформирован, то даем накопиться ДЗВ.
    #ifndef _F16e
        if ( S.flg._.SnImpVM == 0 ) Clr_DZV() ; // очистка ДЗВ по заднему фронту ИУ.
    #endif
          //----
#ifdef _SIFU2_
          //    Признак того, что вызов из второго СИФУ:
          //  оно отработало и сбросило TZ_Ok, сюда же зашли только,
          //  чтобы снять длинный импульс.
        if ( S.flg._.TZ_Ok == 1 )  return ;
        S.flg._.ImpSet2 = 0 ;
    #ifndef _F16e
        if ( S.flg._.SnImpVM2 == 0 ) Clr_DZV2() ; // очистка ДЗВ по заднему фронту ИУ.
    #endif
#endif
          //----

        if ( (u)TimePuls_of_Revers > _pSec(1.0) )
          {
            mSet_ServiceMsg( _Srv_AvarRevers ) ;
            TimePuls_of_Revers = 0 ;
          }
        else   TimePuls_of_Revers++ ;

      if ( _r.Cfg._.DZV == 0 )
      {
          // зарядка в АЦП первой серии измерений тока Id.
        AD_Izm (  Id_mg_ach   , &Tok_for_Revers[ 0 ] ) ;
        AD_Izm (  Id_mg_ach   , &Tok_for_Revers[ 1 ] ) ;
           //  по готовности последнего измерения будет судиться
        Tok_for_Revers[ 2 ] = _AD_BUSY ;   //  о готовности всей серии.
        AD_Izm (  Id_mg_ach   , &Tok_for_Revers[ 2 ] ) ;
      }
           // для последующего контроля, что ИУ сформировался.
        S.flg._.BegImp = 0 ;
            /* Зарядка ЕПА на ожидание Готовности измерений */
        _revers_epa_time ( timer1 + _MkSec( 5 * 55.5 ) );
        //QWEDif ( _r.Cfg._.DZV == 0 )   Revers_Label = 0 ;
        //QWED{     // не сбрасываем признак первого раза для последующ. пульсов.
          //QWEDif ( Revers_Label != 1 )
               Revers_Label = 0 ;
        //QWED}
        dn_revers = 0 ;
      }
    else
      {
        TimePuls_of_Revers = 0 ; // если нет реверса
        dt_revers = Puls_counter ; // если нет реверса
        S.flg._.ZapretImp = 0 ;
        Revers_Label = 2 ; // для возможности выхода по default при
                // холостом срабатывания EPA через полный оборот таймера.
        S.flg._.DZV_OK = 0 ; // 21.02.2008 15:15 - если признак реверса снялся.
#ifdef _SIFU2_
        S2.flg._.dzv_half = 0 ;  // 23.02.2017 - Пока только для 12-пульсной запоминаем половину пришедших ДЗВ .
        dzv_copy = 0 ;
#endif
        if ( _r.Cfg._.DZV == 1 )  S.DZV = 0 ;  //нет реверса - обнуляем S.DZV (для следа)
      }
  return ;
}
//--------------------

// Программа-прерывание отсчета выдержек времени измерений реверса.
//
//   Это прерывание, по своему алгоритму, не должно перебивать
// прерывание по СИФУ.
//
void Revers_Interrupt ( void )
{
     enum {i0,i10,i20,i30};
//---------------------
  /*register*/ word cx0, cx1, cx2, tst ;
//---------------------
     pR( 1 ) ;

       // Объектное (под процессор) дополнение для прерываний:
  Sifu_int_drv(_revers_epa_con) ;  // сброс запроса прерывания.

//-----------
#ifdef  mVObj_mask    // Объектное дополнение для прерываний:
    mVObj_mask() ;  // разрешения pts-EPA0 для частотного заполнения.
#endif
//---------------------
     //  разрешить  прерывания для АЦП, гашения ИУ .
  asm_ei() ;
//-----------

  dn_revers++ ;
  //---
  switch ( Revers_Label )
    {
         // на случай холостого срабатывания EPA через полный оборот таймера.
      default:  break ;
              //----------------
      case  i0 :
      case i10 :

      if ( _r.Cfg._.DZV == 0 )
      {
           // готова ли первая серия измерений для реверса?
        while ( Tok_for_Revers[ 2 ] == _AD_BUSY ) ;

          // преобразование данных серии измерений.
        mIzmData_Conversion ( Tok_for_Revers[ 0 ] , cx0 ,  Id_mg_ach   ) ;
        if ( (sw)cx0 < 0 ) cx0 = ~cx0 + 1 ;
        mIzmData_Conversion ( Tok_for_Revers[ 1 ] , cx1 ,  Id_mg_ach   ) ;
        if ( (sw)cx1 < 0 ) cx1 = ~cx1 + 1 ;
        mIzmData_Conversion ( Tok_for_Revers[ 2 ] , cx2 ,  Id_mg_ach   ) ;
        if ( (sw)cx2 < 0 ) cx2 = ~cx2 + 1 ;

          // проверка данных серии измерений на удовлетворительность.
        tst = 0 ;
        if ( cx0 < _r.RIDRR )  tst++ ;
        if ( cx1 < _r.RIDRR )  tst++ ;
        if ( cx2 < _r.RIDRR )  tst++ ;
           //  Если два из трех замеров тока в серии
          // удовлетворительны, то хорошо.
        if ( tst >= 2  )
        {         // Прошли две серии или одна?
          if ( Revers_Label == i10 )
          {     // для КТЭВ выдержка времени на спад тока,
               // т.к. даже ниже уставки реверсирования при номинале 50А и более
               // ток продолжает тянуться индуктивностью выше тока удержания
               // тиристоров и снятие подтверждающих не помогает.
            Revers_Label = i20 ; // для возможности выхода по default при
                                // холостом срабатывания EPA через полный оборот таймера.
            if ( (u)((w)(Puls_counter - dt_revers)) >= _r.dt_revers )
            {    // больше запускать серию измерений не надо - уходим на реверс.
              //Revers_Label = i20 ; // для возможности выхода по default при
              goto revx ; // холостом срабатывания EPA через полный оборот таймера.
            }  // больше запускать серию измерений не надо - уходим до следующего пульса.
            else break ; // для этой ветки тоже надо Revers_Label = i20 ; т.к. если за время выдержки
          }  //  снимется запрос на рев., то по переполнению таймера снова войдем на эту ветвь и среверсир. под током.
          else Revers_Label  = i10 ;
        }   // все с начала: запуск "первой" серии измерений.
        else
        {
          Revers_Label = i0 ;
          dt_revers = Puls_counter ; // сбрасываем выдержку если ток не в норме.
        }
          //---
      }
      else
      {
#ifdef _F16e
        // Ожидание прихода через порт 3  сигналов от ДЗВ
        Port_input ( 3 ) ;
#endif
        cx0  = 0 ;  // блокируем опрос ДЗВ, пока идет ИУ.
        if ( S.flg._.ImpSet1 == 0 )
        {
#ifdef _F16e
          cx0 |= bi_DZVA * 1 ;
          cx0 |= bi_DZVK * 2 ;
#else
          cx0 |= DZVA_Ok() * 1 ;
          cx0 |= DZVK_Ok() * 2 ;
#endif
        }
        if ( S.flg._.VneshZp == 1 || S.Disable == 1 ) // 16.10.2008 16:27 - ИУ Ведущего моста отключены извне.
        {
          cx0 |= 1 ; // Маскируем ДЗВ отключенного моста.
          cx0 |= 2 ;
        }
      #ifdef _SIFU2_
        if ( S.flg._.ImpSet2 == 0 )
        {
#ifdef _F16e
          cx0 |= bi_DZVA2 * 4 ;
          cx0 |= bi_DZVK2 * 8 ;
#else
          cx0 |= DZVA2_Ok() * 4 ;
          cx0 |= DZVK2_Ok() * 8 ;
#endif
        }
        if ( S2.flg._.VneshZp == 1 || S2.Disable == 1 ) // 16.10.2008 16:27 - ИУ Ведомого моста отключены извне.
        {
          cx0 |= 4 ; // Маскируем ДЗВ отключенного моста.
          cx0 |= 8 ;
        }
      #else
        cx0 |= 4 ;
        cx0 |= 8 ;
      #endif
        S.DZV = cx0 ;// для индикации.

#ifdef _SIFU2_  // 23.02.2017 - Пока только для 12-пульсной запоминаем половину пришедших ДЗВ .
        if ( S2.flg._.dzv_half == 1 )  cx0 |= dzv_copy ;
#endif

             //  Оба пришли.
        if ( cx0 == 0x0F )
        {
          S.flg._.DZV_OK = 1 ; // 21.02.2008 15:15 - выдержку на безток.паузу больше не обнулять !
          if ( (u)((w)(Puls_counter - dt_revers)) >= _r.dt_revers ) goto revx ;
        }
        else if ( ((cx0 & 0x05) | ((cx0 & 0x0A) >> 1)) == 0x05 )
        {     // Если  пришeл хотя бы один сигнал от какого-либо ДЗВ в
             // каждом из мостов фиксируем время для ожидания второго сигнала.
        //  if ( S.flg._.ZapretImp == 0 ) dt_revers = Puls_counter ;
        //  S.flg._.ZapretImp = 1 ; // запрет может сохран. на неск.пульсов.
        //---
#ifdef _SIFU2_  // 23.02.2017 - Пока только для 12-пульсной запоминаем половину пришедших ДЗВ .
          if ( S2.flg._.dzv_half == 0 ) // первый вход .
          {
            dzv_copy = cx0 ;
            S2.flg._.dzv_half = 1 ;
          }
#endif
          //---
          S.flg._.DZV_OK = 1 ; // 21.02.2008 15:15 - выдержку на безток.паузу больше не обнулять !
          if ( (u)((w)(Puls_counter - dt_revers)) >= (u)((w)(_pSec(0.015) + _r.dt_revers)) )
          {
            if ( _r.Cfg2._.DZV_Predupr == 1 ) // 05.09.2019 - вывод сообщений об отсуствии сигнала ДЗВ при реверсе .
            {
              if ( (cx0 & 0x01) == 0 )  mSet_PreduprMsg( _Pr_DZVA ) ;
              if ( (cx0 & 0x02) == 0 )  mSet_PreduprMsg( _Pr_DZVK ) ;
      #ifdef _SIFU2_
              if ( (cx0 & 0x04) == 0 )  mSet_PreduprMsg( _Pr_DZVA2 ) ;
              if ( (cx0 & 0x08) == 0 )  mSet_PreduprMsg( _Pr_DZVK2 ) ;
      #endif
            }
            goto revx ; // холостом срабатывания EPA через полный оборот таймера.
          }
        }    // Нет ни одного - все с начала
        else if ( S.flg._.DZV_OK == 0 ) //if ( cx0 == 0 )
        {
          // 21.02.2008 15:15 - выдержку на безтоковую паузу нужно обнулять только до
          // первого прихода ДЗВ , иначе во время безтоковой паузы при переходах
          // синусоиды через нуль сигналы ДЗВ дребезжат . Если при этом сбрасывать
          // выдержку "dt_revers" , то реальная безтоковая пауза увеличивается на
          // несколько порядков .
          Revers_Label = i0 ;
          dt_revers = Puls_counter ; // сбрасываем выдержку если ДЗВ не в норме.
        }
      }
          //---
      tst = S.TZ - _MkSec((5)*55.5) , tst = tst - timer1 ; // 23.02.2017 - Уменьшено на 6 грд по итогам ЗЖРК , 12-пульс .
      if ( (u)tst >= (w)Tsyn )
    //if (( (w)((S.TZ-_MkSec((5+5+1)*55.5)) - timer1) >= (w)Tsyn ))
      {
        if ( _r.Cfg._.DZV == 0 )   Revers_Label = i20 ;
        else
        {     // не сбрасываем признак первого раза для последующ. пульсов.
          if ( Revers_Label != i10 ) Revers_Label = i20 ;
        }
      }
      else
      {
        if ( _r.Cfg._.DZV == 0 )
        {
                  // Повтор серии измерений.
          mAD_Izm (  Id_mg_ach  , &Tok_for_Revers[ 0 ] ) ;
          mAD_Izm (  Id_mg_ach  , &Tok_for_Revers[ 1 ] ) ;
          Tok_for_Revers[ 2 ] = _AD_BUSY ;
          mAD_Izm (  Id_mg_ach  , &Tok_for_Revers[ 2 ] ) ;
        }
           //  Зарядка ЕПА на выдержку времени 5грд после серии измерений.
        _revers_epa_time ( timer1 + _MkSec( 5 * 55.5 ) );
      }

        break;
            //-----------------------

  revx:
        // Чтобы не дать среверсироваться , выставить "1" :
        if ( can_ConfigReg ( _CAN_Revers ) == 1 ) break ;
        if ( obj_ConfigReg ( _Obj_Revers ) == 1 ) break ;

        Revers_Label = i20 ; // <- на всякий случай для "return" по "default"
        TimePuls_of_Revers = 0 ;

    //***** Условие - дважды "два из трех" пройдено. *****

           // Запрещаем формирование ИУ.
        S.flg._.ZapretImp = 1 ;
        if ( S.flg._.BegImp == 1 )// все! поздно! импульс сформирован! ну и ничего,
          {                   //  начнем все с начала после этого импульса.
             // для последующего контроля, что ИУ сформировался.
            S.flg._.BegImp = 0 ;
            S.flg._.ZapretImp = 0 ;
            //Revers_Label = i20 ; // <- на всякий случай для "return" по "default"
            break ;
          }
            //  Отодвигаем ЕПА, чтобы оно не сработало
           // пока мы будем здесь возиться.
        _sifu_epa_time ( timer1 - 1u ) ;
           // сброс запроса прерывания СИФУ,если он сформ. пока мы сидели
          // в этом прерыв.
        Sifu_int_drv(_sifu_epa_con) ;
      #ifdef _SIFU2_
        _sifu2_epa_time ( timer1 - 1u ) ;
        Sifu_int_drv(_sifu2_epa_con) ;
      #endif
           //QWED  Зарядка ЕПА на выдержку времени.
        _revers_epa_time ( timer1 + _MkSec( 250 ) ); //1000 , 23.02.2017 - Уменьшено в 4 раза по итогам ЗЖРК , 12-пульс .
        Revers_Label = i30 ; // <- на всякий случай для "return" по "default"
        break;

      case i30 : //QWED
        Revers_Label = i20 ; // <- на всякий случай для "return" по "default"
        S.flg._.ZapretImp = 0 ;

     //---  Перерасчет интегральной части регулятора тока  ---

#ifndef _KTE_GD
        if ( S.flg._.Invertor == 1 )
          {
            OIRT = _r.RevU0 - (w)_r.KeV * (w)ED1 ;
            if ( OIRT < _r.RTMIN )  OIRT = _r.RTMIN ;
          }
        else
          {
            OIRT = _r.RevU0 + (w)_r.KeI * (w)ED1 ;
            if ( OIRT > 0x3FFFu )   OIRT = 0x3FFFu ;
          }
        IDV = IDN = 0x02u*_K_diskr ; // IDV - до конца "Reversa" не изменять
        ZIDN = OuRegS = 0x02*_K_diskr ;
        Set_ZIRT ( &zi_rt , 0x02*_K_diskr ) ;

#ifdef  _SIFU2_

        Set_ZIRT ( &zi_rt2 , 0x02*_K_diskr ) ;
        IDN_2_  = IDN ;
        ZIDN_2_ = ZIDN;
        IDV2    = IDV;
        OIRT_2_ = OIRT;

#endif
     //-------------    РТ    -----------

            //---  Расчет РТ или Формирование задания на угол управления.
        if ( Prg._.RegTok == 1 && can_ConfigReg ( _CAN_Alfa_Zad ) == 0 &&
                                  obj_ConfigReg ( _Obj_Alfa_Zad ) == 0 )
        {
          RegTok () ;
          Linear () ;
#ifdef  _SIFU2_
          // DAN 23.05.2017 14:46 - При работе обоих СИФУ самостоятельно, либо при работе только ШС2 .
          if ( _r.Cfg2._.RT2_SIFU2 == 1 || S.Disable == 1 ) // 2-й РТ ( самостоятельный ) для второго моста :
          {
            RegTok2 () ; // 2-й РТ для второго моста .
            Linear2 () ;
            if      ( S2.Alfa > _r.S_Alfa_Max )  S2.Alfa = _r.S_Alfa_Max, S2.flg._.Fmax = 1 ;
            else if ( S2.Alfa < _r.S_Alfa_Min )  S2.Alfa = _r.S_Alfa_Min, S2.flg._.Fmin = 1 ;
          }
#endif
        }
#else      // переворачиваем под формат РН.
        cx0 = _Grad( 180 ) - _r.RevU0 ;
                          // номер моста еще не изменили...
        if       ( S.NumMost == 1 ) Integr_rn = ~cx0+1 ;
        else if  ( S.NumMost == 2 ) Integr_rn =  cx0 ;
        //OuIchRS = 0 ; 27.06.06 11:41
        //OIRT  = 0 ; 27.06.06 11:41 /* интегратор регулятора тока */
        //---
        can_ConfigReg ( _CAN_Alfa_Zad ) ;
        obj_ConfigReg ( _Obj_Alfa_Zad ) ;
#endif

        if       ( S.NumMost == 1 ) S.NumMost = 2 ;
        else if  ( S.NumMost == 2 ) S.NumMost = 1 ;

        S.flg._.Revers = 0 ;
        dt_revers = Puls_counter ; // сбрасываем выдержку если мы среверсировались.
        S.flg._.DZV_OK = 0 ; // 21.02.2008 15:15 - выдержку на безток.паузу обнулять.
#ifdef _SIFU2_
        S2.flg._.dzv_half = 0 ;
        dzv_copy = 0 ;
#endif

     //-------------   СИФУ   -----------

        S.flg._.Fmax = 0,   S.flg._.Fmin = 0 ;
        S.flg._.Fdmin = 0,  S.flg._.Fdmax = 0 ;

            //---- Ограничение минимального угла управления.
        can_ConfigReg ( _CAN_Alfa_Min ) ;
             //-----

        /* Расчет S.TZ для текущего угла для текущего тиристора */
        cx0 = S.Alfa ;
        if      ( cx0 > _r.S_Alfa_Max )  cx0 = _r.S_Alfa_Max, S.flg._.Fmax = 1 ;
        else if ( cx0 < _r.S_Alfa_Min )  cx0 = _r.S_Alfa_Min, S.flg._.Fmin = 1 ;

        if ( cx0 > S.Alfa_Old )
        {
          S.TZ = S.TZ + (w)( (lw)(cx0-S.Alfa_Old) * (lw)Tsyn >> 15 ) ;
        }
        else
        {
          S.TZ = S.TZ - (w)( (lw)(S.Alfa_Old-cx0) * (lw)Tsyn >> 15 ) ;
        }
        S.Alfa_Old = cx0;

         /* Подбор такого N, чтобы S.TZ попал в область (timer1+10грд)...(timer1+10грд+60грд)
          * 10грд - необходимо для того, чтобы успеть выполнить п/п Ugol_Pol() и тем самым
          * зарядить EPA для следующего УИ */

        cx0 = S.TZ - (w)( (lw)_r.S_Alfa_IzmDoImp * (lw)Tsyn >> 15 ) - timer1 ;
        cx1 = _Grad( 60.0 ) * (lw)Tsyn >> 15  ;  // 1000 , 23.02.2017 - Уменьшено в 2 раза по итогам ЗЖРК , 12-пульс :
        while ( ( (u)cx0 < _MkSec( 500 ) ) || ( (u)cx0 > (u)((w)(cx1 + _MkSec( 500 ))) ) )
          {
            if ( ((u)cx0 > Tsyn) || ((u)cx0 < Tsyn/32) )
              {
                S.TZ += cx1 ,  S.N++ ;
                if ( S.N > 6 ) S.N = 1 ;
              }
            else
              {
                S.TZ -= cx1 ,  S.N-- ;
                if ( S.N < 1 ) S.N = 6 ;
              }
            cx0 = S.TZ - (w)( (lw)_r.S_Alfa_IzmDoImp * (lw)Tsyn >> 15 ) - timer1 ;
          }
#ifndef _F16e
        S.NIP = FOR0 [S.N] ;  // импульсы с подтверждающими

        if ( Otkl_Imp != 0x0 ) S.NIP = FOR0[0] ;
#else

        S.NIP = FOR0[S.NumMost] [S.N] ;  // импульсы с подтверждающими

        if ( Otkl_Imp != 0x0 ) S.NIP = FOR0[0][0] ;

#endif
        /* Зарядка ЕПА на угол измерения. */

        S.NumInt = 1 ;

       _sifu_epa_time ( S.TZ - (w)( (lw)_r.S_Alfa_IzmDoImp * (lw)Tsyn >> 15 ) );

  #ifdef  _SIFU2_
      // DAN 23.05.2017 14:46 - При работе обоих СИФУ самостоятельно, либо при работе только ШС2 .
      if ( _r.Cfg2._.RT2_SIFU2 == 1 || S.Disable == 1 ) // 2-й РТ ( самостоятельный ) для второго моста :
      {
        /* Расчет S2.TZ для текущего угла для текущего тиристора */
        cx0 = S2.Alfa ;
        if      ( cx0 > _r.S_Alfa_Max )  cx0 = _r.S_Alfa_Max, S.flg._.Fmax = 1 ;
        else if ( cx0 < _r.S_Alfa_Min )  cx0 = _r.S_Alfa_Min, S.flg._.Fmin = 1 ;

        if ( cx0 > S2.Alfa_Old )
        {
          S2.TZ = S2.TZ + (w)( (lw)(cx0-S2.Alfa_Old) * (lw)Tsyn >> 15 ) ;
        }
        else
        {
          S2.TZ = S2.TZ - (w)( (lw)(S2.Alfa_Old-cx0) * (lw)Tsyn >> 15 ) ;
        }
        S2.Alfa_Old = cx0;

         /* Подбор такого N, чтобы S.TZ попал в область (timer1+10грд)...(timer1+10грд+60грд)
          * 10грд - необходимо для того, чтобы успеть выполнить п/п Ugol_Pol() и тем самым
          * зарядить EPA для следующего УИ */

        cx0 = S2.TZ - timer1 ;
        cx1 = _Grad( 60.0 ) * (lw)Tsyn >> 15  ;
        while ( ( (u)cx0 < _MkSec( 500 ) ) || ( (u)cx0 > (u)((w)(cx1 + _MkSec( 500 ))) ) )
          {
            if ( ((u)cx0 > Tsyn) || ((u)cx0 < Tsyn/32) )
              {
                S2.TZ += cx1 ,  S2.N++ ;
                if ( S2.N > 6 ) S2.N = 1 ;
              }
            else
              {
                S2.TZ -= cx1 ,  S2.N-- ;
                if ( S2.N < 1 ) S2.N = 6 ;
              }
            cx0 = S2.TZ  - timer1 ;
          }
#ifndef _F16e
        S2.NIP = FOR0 [S2.N] ;  // импульсы с подтверждающими

        if ( Otkl_Imp != 0x0 ) S2.NIP = FOR0[0] ;
#else

        S2.NIP = FOR0[S.NumMost] [S2.N] ;  // импульсы с подтверждающими

        if ( Otkl_Imp != 0x0 ) S2.NIP = FOR0[0][0] ;

#endif

        /*S2.N = S.N ;
        for ( s2_ax = 1 ; s2_ax < _r.S2.FazirovVS ; s2_ax++ )
        {
          S2.N-- ;
          if ( S2.N == 0 )  S2.N = 6 ;
        }

        S2.TZ = S.TZ + Tsyn/12 ; // 30 грд для Ведомого СИФУ .

        S2.NumInt = 1 ;

        //При входе мз реверса пересчитываем S2.N, по этому обновляем NIP
        if ( Otkl_Imp == 0)
        {
           S2.NIP = FOR0 [S2.N] ;
        }
        else
        {
           S2.NIP = FOR0 [0] ;
        }*/

        // Конец импульса и номер порта УИ описываются до того, как заряжать EPA
        // на случай, если  EPA сработает сразу же после его зарядки

              //Зарядка ЕПА
        asm_di();
          S2.NumInt = 1 ;
         _sifu2_epa_time ( S2.TZ );
        asm_ei();
      }
      else // Для СИФУ2 с РВТ :
      {
        SIFU2_Start (1) ;
      }
  #endif

    // Для следа, чтобы в байтовой ячейке содержались номера моста и тиристора :
    S.Most_Tir  = S.N ;
    S.Most_Tir |= S.NumMost << 4  ;
    if ( _r.Cfg._.DZV == 1 && (S.DZV & 0x03) != 0 ) S.Most_Tir |= 0x08 ; // Если пришло хотя бы одно ДЗВ .
    if ( S.flg._.Revers  == 1 )
    {   // 03.08.2021 - Если реверс окончился , то флаг снятия ИУ писать не нужно , иначе в следе будет несоответствие :
                                   S.Most_Tir |= 0x40 ; // 6й - SPI .
      if ( S.flg._.SnImpVM == 1 )  S.Most_Tir |= 0x80 ; // 7й - снятие импульсов .
    }

  #ifdef  _SIFU2_
    // Для следа, чтобы в байтовой ячейке содержались номера моста и тиристора :
    S2.Most_Tir =  S2.N ; // Ведомое СИФУ выдает импульсы на "свой" тиристор ,
    S2.Most_Tir |=  S.NumMost << 4  ; // но на такой же мост , как у Ведущего.
    if ( _r.Cfg._.DZV == 1 && (S.DZV & 0x0C) != 0 ) S2.Most_Tir |= 0x08 ; // Если пришло хотя бы одно ДЗВ .
    if ( S.flg._.Revers   == 1 )
    {   // 03.08.2021 - Если реверс окончился , то флаг снятия ИУ писать не нужно , иначе в следе будет несоответствие :
                                   S2.Most_Tir |= 0x40 ; // 6й - SPI ведущего моста .
      if ( S.flg._.SnImpVM2 == 1 ) S2.Most_Tir |= 0x80 ; // 7й - снятие импульсов .
    }
  #endif

        break;
    }
//-----------

     pR( 0 ) ;

    return;
}

