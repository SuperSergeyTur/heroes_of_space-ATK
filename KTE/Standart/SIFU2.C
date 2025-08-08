
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//
//                Принцип построения СИФУ:
// - ведущее СИФУ формирует ИУ;
// - ведомое формирует ИУ с отставание на 30грд +- дельта от РВТ;
// - ведомое СИФУ имеет свою уставку фазировочного тиристора задаваемую
//   по отношению к фазир.тир-ру ведущего СИФУ, чтобы можно было выдавать ИУ
//   на тиристоры ведомого моста со сдвигом (опережением, отставанием)
//   от ведущего в зависимости от схемы включения обмоток трансформатора.
//
//-----------------------------------

/* Второе СИФУ для 12-ти пульсной схемы. */

  word SIFU2_Start ( word num )
  {
        // Полная стартовая инициализация :
    if ( num == 0 )
    {
      mPort_Imp2(FOR0 [0]) ;

      S2.Integr = 0, S2.flg.all = 0 ;
      S2.Alfa_RVT = 0 ;
      S2.Disable  = 0; // для 12-ти пульсного СИФУ , запрет при работе только РТ1 .
      //---
      // 11.12.2018 19:05 - нициализируем все уставки фазировки , т.к. во время работы могут быть произведены
      //                    переключения режимов работы ШС - либо ШС1+ШС2 , либо отдельно ШС1 , либо отдельно ШС2 :
        s2_cx = _r.S_Alfa_Start ;
        S2.Alfa = s2_cx ;

          //  Ограничитель угла.
        if ( s2_cx > _r.S_Alfa_Max )
          {
            s2_cx = _r.S_Alfa_Max;
            S2.flg._.Fmax = 1 ;
          }
        else if ( s2_cx < _r.S_Alfa_Min )
               {
                 s2_cx = _r.S_Alfa_Min ;
                 S2.flg._.Fmin = 1 ;
               }
        S2.Alfa_Old = s2_cx ;   // раньше это делать нельзя.

        S2.FazirovVS = _r.S_FazirovVS ;
        S2.FazirovUgol = _r.S_FazirovUgol + _Grad(30);

        if ( S2.FazirovUgol > _Grad(60) )
        {
          --S2.FazirovVS;
          if ( S2.FazirovVS == 0 ) S2.FazirovVS = 6;
          S2.FazirovUgol -= _Grad(60);
        }

        for ( s2_ax = 1 ; s2_ax < _r.S2.FazirovVS ; s2_ax++ )
        {
          S2.FazirovVS-- ;
          if ( S2.FazirovVS == 0 )  S2.FazirovVS = 6 ;
        }
        S2.N = S2.FazirovVS;

           //   Расчет времени выдачи первого импульса:
          // на 30грд после ведущего, но на свой тиристор.
        pSyn->b_SIi = 0 ; // для Самостоятельного СИФУ с РТ , а не Ведомого СИФУ с РВТ .

        S2.TZ = pSyn->NS2  ; // усредненный момент прихода СИ.
        S2.TZ += (w)( (lw)( S2.FazirovUgol + S2.Alfa ) * (lw)Tsyn >> 15 )  ;
    }

        // Отсюда начинается частичная послереверсная инициализация :
   // Определение номера тиристора ведомого моста по уставке фазировки
   // ведомого моста, производится после стартовой программы СИФУ ведущего
   // моста когда S.N уже определен.

   if ( _r.Cfg2._.RT2_SIFU2 == 0 )    // РТ и РВТ :
   {
    S2.N = S.N ;
    for ( s2_ax = 1 ; s2_ax < _r.S2.FazirovVS ; s2_ax++ )
    {
      S2.N-- ;
      if ( S2.N == 0 )  S2.N = 6 ;
    }
       //   Расчет времени выдачи первого импульса:
      // на 30грд после ведущего, но на свой тиристор.
    S2.TZ = S.TZ + Tsyn/12 ;
   }

    S2.NumInt = 1 ;

   //При входе мз реверса пересчитываем S2.N, по этому обновляем NIP
   if ( Otkl_Imp == 0)
   {
      S2.NIP = FOR0 [S2.N] ;
   }
   else
   {
      S2.NIP = FOR0 [0] ;
   }

    /* Конец импульса и номер порта УИ описываются до того, как заряжать EPA */
    /* на случай, если  EPA сработает сразу же после его зарядки             */

          /* Зарядка ЕПА */

    init_sifu_epa( _sifu2_epa_con ) ;
    _sifu2_epa_time ( S2.TZ );

    return 0 ;
}

//         ПРОГРАММА УПРАВЛЕНИЯ СИФУ ВОЗБУДИТЕЛЯ.
//------------------------------------------------------------


// Программа-прерывание управления ведомым СИФУ.

void S2_Interrupt ( void )
  {
     enum {i0,i1,i2,i3,i4};
//---------------------
    pV( 1 ) ;
beg_imp:
       // Объектное (под процессор) дополнение для прерываний:
    Sifu_int_drv(_sifu2_epa_con) ;  // сброс запроса прерывания.

//---------------------
#ifdef  mVObj_mask    // Объектное дополнение для прерываний:
    mVObj_mask() ;  // разрешения pts-EPA0 для частотного заполнения.
#endif
//---------------------

         //  разрешить  прерывания для АЦП.
    asm_ei() ;

  switch( S2.NumInt )
  {
  case i1 :

    /*19.10.2016 13:47 - Формирование ИУ сделано , наконец , по образу и подобию СИФУ1 ...
          // Переключаем частотное заполнение, как разрешение.
      if ( Otkl_Imp == 0 && S2.flg._.VneshZp == 0 && S2.Disable == 0) // 16.10.2008 16:27 - ИУ моста отключены извне.
      {                                                               // 28.09.2016 10:38 - ИУ отключены при работе только РТ1.
        if      ( S.NumMost == 1 ) {  mFzapoln3_start() ; }
        else if ( S.NumMost == 2 ) {  mFzapoln4_start() ; }
      }*/

      //Теперь ожидаем время начала импульса
    asm_di();//Чтобы не влезло левое прерывание

      do  s2_ax = S2.TZ - timer1 ;
      while ( (u)s2_ax < (w)Tsyn  );
            // Запрет из реверса или запрет при работе только РТ1 или ИУ моста отключены извне .
      if( S.flg._.ZapretImp == 0 && S2.Disable == 0 && S2.flg._.VneshZp == 0 ) // В СИФУ2 реверс возможен ТОЛЬКО с ДЗВ !!!
      {      //считывание ДЗВ до формирования импульса.
        if ( S.flg._.Revers == 1 ) // если в ведущем СИФУ сняты подтверждающие,
        {   // то в ведомом снимаем ИУ совсем, как только появился один из ДЗВ.
          if ( DZVA2_Ok() || DZVK2_Ok() ) S.flg._.SnImpVM2 = 1 ;
        }
        else  S.flg._.SnImpVM2 = 0 ;
        //---
        if ( S.flg._.SnImpVM2 == 0 )
        {
          S.flg._.ImpSet2 = 1 ; // для запрета контроля ДЗВ в реверсе.

            if ( Otkl_Imp == 0 )
            {
                if      ( S.NumMost == 1 ) {
                                              mFzapoln3_stop() ;// снимаем оба частотных заполнения.
                                              mFzapoln3_start() ;
                                            }
                else if ( S.NumMost == 2 ) {
                                              mFzapoln4_stop() ;// снимаем оба частотных заполнения.
                                              mFzapoln4_start() ;
                                            }
            }
            else goto xxx ; // При срабатывании геркона Otkl_Imp без выдержек и S.NIP не пишется.
            mPort_Imp2(S2.NIP) ;
        }
      }
      else // 25.02.2008 19:17 - при запрете нужно снять частотные заполнения :
      {
  xxx:  mFzapoln3_stop() ;// снимаем оба частотных заполнения.
        mFzapoln4_stop() ;// снимаем оба частотных заполнения.
        mPort_Imp2( FOR0 [0] ) ;
      }
      //Clr_DZV2() ; // очистка ДЗВ по переднему фронту ИУ.
    asm_ei();
   //-----
         //  Расчет времени гашения ИУ: не даем заступить точке гашения за
         // точку измерения.
      s2_ax = _r.S_Alfa_IzmId - _Grad( 5.0 );
      if ( _r_S_ImpLong < s2_ax )  s2_ax = _r_S_ImpLong ;

      s2_ax = S2.TZ + ( (lw)s2_ax * (lw)Tsyn >> 15 ) ;
                 // перезарядка ЕПА
      //_sifu2_epa_time (s2_ax); // зарядка конца импульса

      S2.NumInt = 2 ;

  asm_di() ;
      //---   Проверка на опоздание ИУ. Если опоздал, то переход тут же к началу ИУ.

    s2_cx = s2_ax - timer1 ;
    if ( (u)s2_cx < (w)Tsyn*2  &&  s2_cx >= _MkSec( 50 ) )
    {
                 // перезарядка ЕПА
      _sifu2_epa_time( s2_ax ) ; // зарядка начала импульса

  asm_ei() ;
    }
    else
    {
  asm_ei() ;

      do  s2_cx = s2_ax - timer1 ;
      while ( (u)s2_cx < (w)Tsyn*2  );

      goto end_imp ;
    }
    break;
     //-------------

  case i2 :
end_imp: ;
          // Формируем задний фронт .
        mPort_Imp2(FOR0[0]) ;
        mFzapoln3_stop() ;// снимаем оба частотных заполнения.
        mFzapoln4_stop() ;
        S.flg._.ImpSet2 = 0 ; // для разрешения контроля ДЗВ в реверсе.
              // если импульс не был сформирован, то даем накопиться ДЗВ.
        if ( S.flg._.SnImpVM2 == 0 ) Clr_DZV2() ; // очистка ДЗВ по заднему фронту ИУ.
     //-------------

                // зарядка точки измерения Id.
      s2_ax = S2.TZ + (w)( (lw)_r.S_Alfa_IzmId * (lw)Tsyn >> 15 )  ;
      _sifu2_epa_time( s2_ax) ;
      S2.NumInt = 3 ;
    break;
     //-------------

  case i3 :   //--------

      Id2_Izm () ;
      //---  Расчет РТ :
      //---
      if ( S.flg._.VneshZp == 0 ) // У Ведущего моста нет запрета ИУ , Ведомый работает со 2-м РТ или с РВТ :
      {
        if ( Prg._.RegTok == 1 )
        {
             if ( _r.Cfg2._.RT2_SIFU2 == 0 ) // Структура РТ+РВТ :
             {
               if ( S.Disable == 0 ) // ШС1 работает вместе с ШС2 .
               {
                 RVT () ;            // РВТ для второго моста .
                 ZIDN_2_ = 0 ;       // Инициализация при невыполнении .
               }
               else // DAN 23.05.2017 14:46 - При работе только ШС2 :
               {
                 RegTok2 () ;        // 2-й РТ для второго моста .
                 Linear2 () ;
                 S2.Out_rvt = 0 ;    // Инициализация при невыполнении .
               }
             }
             else // Структура РТ1 + РТ2 :
             {
                 RegTok2 () ;        // 2-й РТ для второго моста .
                 Linear2 () ;
                 S2.Out_rvt = 0 ;    // Инициализация при невыполнении .
             }
        }       // Если не режим Проверки Пробоя Тиристора . В этом режиме угол задаётся самим режимом ...
        else if ( flg_RaTe._.tyr_tst_go == 0 ) S2.Alfa_RVT = 0 , S2.Alfa = S.Alfa ; // Для режима СИФУ .
      }
      //---

  case i4 :  S2.NumInt = 4 ;

//---------  СИФУ  -------------
    // DAN 23.05.2017 14:46 - В это условие есть смысл заходить только при работе ШС1 .
    //                        Если ШС1 отключен , либо оба СИФУ самостоятельные , то ждать формирования ИУ СИФУ1 не нужно ...
    if ( S.flg._.TZ_Ok == 0 && _r.Cfg2._.RT2_SIFU2 == 0 && S.Disable == 0 ) // если в ведущем СИФУ TZ еще не расчитано,
    {                        // то зайдем сюда через 5грд.
      s2_ax = timer1 + _MkSec( 3u * 55u ) ;
      _sifu2_epa_time ( s2_ax ) ;
      return ;
    }

    S.flg._.TZ_Ok = 0 ;
    S2.NumInt = 1 ;
    //---
    //---------------------------------------------------------------------------------
    // DAN 23.05.2017 14:46 - При работе обоих СИФУ самостоятельно, либо при работе только ШС2 .
    if ( _r.Cfg2._.RT2_SIFU2 == 1 || S.Disable == 1 ) // 2-й РТ ( самостоятельный ) для второго моста :
    {
        S2.flg._.Fmax = 0 ;
        S2.flg._.Fmin = 0 ;
        S2.flg._.Fdmin  = 0 ;
        S2.flg._.Fdmax  = 0 ;

            //---- Ограничение минимального угла управления.
      //can_ConfigReg ( _CAN_Alfa_Min ) ; - это здесь не требуется ...
             //-----

        if ( Av._.Sdvig_imp == 1 ) goto sdv ; // сдвиг импульсов в Альфа_Макс.
        else         s2_cx = S2.Alfa ;


          //   Наступление ограничений по ЗИ и ограничителю угла друг друга
          // взаимоисключают;  по-этому поводу будет ссылка ниже ...
          //  Ограничитель угла.
      if ( flg_RaTe._.tyr_tst_go == 1 ) // DAN 20.07.2017 9:45 - При тесте тиристоров диапазон угла принимается
      {                                 //                       от 150 до 179 грд :
        if ( s2_cx > _Grad( 179 ) )
          {
              s2_cx = _Grad( 179 ) ;
            S2.flg._.Fmax = 1;
          }
        else if ( s2_cx < _Grad( 150 ) )
               {
                 s2_cx = _Grad( 150 ) ;
                 S2.flg._.Fmin = 1;
               }
      }
      else
      {
        if ( s2_cx > _r.S_Alfa_Max) // Рабочий Ограничитель угла :
          {
         sdv: s2_cx = _r.S_Alfa_Max;
            S2.flg._.Fmax = 1;
          }
        else if ( s2_cx < _r.S_Alfa_Min )
               {
                 s2_cx = _r.S_Alfa_Min ;
                 S2.flg._.Fmin = 1;
               }
      }
           // ЗИ.
        if ( s2_cx < S2.Alfa_Old  )
          {
            s2_ax = S2.Alfa_Old - s2_cx ;
            if ( s2_ax > _r.S_DeltaAlfa_Max)
              {
                s2_ax = _r.S_DeltaAlfa_Max;      //   если после ограничителя угол сел на ЗИ,
                s2_cx = S2.Alfa_Old - s2_ax ;    //   то, следовательно, ограничение по _r.Alfa_Min если
                S2.flg._.Fdmin = 1 ;   //   и было то отпало само собой и по-этому здесь
                S2.flg._.Fmin  = 0 ; // <- признак ограничения _r.Alfa_Min сбрасывается.
              }
            S2.TZ -= (w)( (lw)s2_ax * (lw)Tsyn >> 15 ) ;
          }
        else
          {
            s2_ax = s2_cx - S2.Alfa_Old ;
                // из-за перекрытия ИУ нельзя обходить ЗИ
            if ( Av._.Sdvig_imp == 1 ) goto s2 ; // Обход ЗИ при сдвиге импульсов в Альфа_Макс.
            if ( s2_ax > _r.S_DeltaAlfa_Max )
              {
                s2_ax = _r.S_DeltaAlfa_Max ;    // если после ограничителя угол сел на ЗИ,
                s2_cx = S2.Alfa_Old + s2_ax ; // то, следовательно, ограничение по AlfaMax если
                S2.flg._.Fdmax = 1 ;                // и было то отпало само собой и по-этому здесь
                S2.flg._.Fmax = 0;                  // <- признак ограничения Fmax сбрасывается.
              }
        s2: S2.TZ += (w)( (lw)s2_ax * (lw)Tsyn >> 15 ) ;
          }

        S2.Alfa_Old = s2_cx;      // раньше это делать нельзя.

        // TZ += (w)( (lw)_Grad( 60.0 ) * (lw)Tsyn >> 15 ) ;
        S2.TZ += Tsyn/6 ;

        //Расчет номера тиристора Второго Моста для выдачи.
        ++S2.N;// = S.N ;
        if ( S2.N == 7 )  S2.N = 1 ;
    }
    //---------------------------------------------------------------------------------
    //---
    else // РВТ для второго моста :
    {
        s2_cx = S2.Alfa_RVT ;
        S2.Alfa_Old = S.Alfa_Old + S2.Alfa_RVT ; // 14.10.2008 16:59 - для переменной с полным углом СИФУ2 .

        S2.TZ  = S.TZ ;
        S2.TZ += (w)( (slw)(sw)s2_cx * (slw)Tsyn >> 15 ) ;
        S2.TZ += Tsyn / 12 ; // 30 эл. гр

        //Расчет номера тиристора ведомого М для выдачи.
        S2.N = S.N ;
        for ( s2_ax = 1 ; s2_ax < _r.S2.FazirovVS ; s2_ax++ )
        {
          S2.N-- ;
          if ( S2.N == 0 )  S2.N = 6 ;
        }
    }

    //--------
     // нормальная работа , не реверс и не контроль пробития :
    if ( S.flg._.Revers == 0 && flg_RaTe._.tyr_tst_go == 0 ) S2.NIP = FOR0 [S2.N] ;  // импульсы с подтверждающими
    // реверс или контроль пробития :
    else                                                     S2.NIP = FOR1 [S2.N] ;  // импульсы без подтверждающих
                         // 16.10.2008 16:27 - ИУ моста отключены извне.
    if ( Otkl_Imp != 0x0 || S2.flg._.VneshZp == 1 )          S2.NIP = FOR0 [0] ;

    // DAN 23.05.2017 14:46 - При работе обоих СИФУ самостоятельно, либо при работе только ШС2 .
    if ( _r.Cfg2._.RT2_SIFU2 == 1 || S.Disable == 1 ) // 2-й РТ ( самостоятельный ) для второго моста :
    {
      if ( pSyn->b_SIi == 1 )
      {
        pSyn->b_SIi = 0 ;
        s2_ax = S2.TZ ;
        S2.TZ = pSyn->NS2  ;
        if ( S2.N >= S2.FazirovVS ) S2.TZ += Tsyn/6 * (w)(S2.N - S2.FazirovVS)  ;
        else                        S2.TZ += Tsyn/6 * (w)(6u + S2.N - S2.FazirovVS)  ;
        S2.TZ += (w)( (lw)( S2.FazirovUgol + s2_cx ) * (lw)Tsyn >> 15 )  ;

          // После перепривязки проверка отклонения момента выдачи УИ от момента расчитанного
        if (( (u)((w)(S2.TZ - s2_ax)) >= (w)Tsyn/8 ) && ( (u)((w)(s2_ax - S2.TZ)) >= (w)Tsyn/8 )) // без перепривязки и в случае его большого отклонения
          {
                          /*  Нижеследующая Последовательность проверки обязательна:
                             * сначала "-Tsyn", потом "+Tsyn" - т.е. проверка завершается
                             * прибавлением периода. Это на тот случай если отклонение "TZ"
                             * вызвано не ошибкой перепривязки на "Tsyn", а тем что уплыли
                             * импульсы из-за временного отсутствия синхронизации и прибавив
                             * лишний период в направлении роста таймера мы в худшем случае
                             * просидим период без импульсов, но не собьемся со шкалы таймера
                             * и через период снова подадутся импульсы.
                             */
            S2.TZ -= Tsyn ;  // <- Когда мы при большом 'alfa' залезли старой шестеркой за новый СИ.
            if (( (u)((w)(S2.TZ - s2_ax)) >= (w)Tsyn/8 ) && ( (u)((w)(s2_ax - S2.TZ)) >= (w)Tsyn/8 ))  // <- Когда мы при маленьком 'alfa'
                      S2.TZ += 2*Tsyn ;   //  и задержке обработки очередного СИ получили его после начала новой шестерки.
          }
      }
    }

    /* Зарядка ЕПА */

    //  КВВ 10-11-16 - добавил защиту от опоздания, пришлось перенести ниже реверса
    // _sifu2_epa_time ( S2.TZ );

    // Для следа, чтобы в байтовой ячейке содержались номера моста и тиристора :
    S2.Most_Tir =  S2.N ; // Ведомое СИФУ выдает импульсы на "свой" тиристор ,
    S2.Most_Tir |=  S.NumMost << 4  ; // но на такой же мост , как у Ведущего.
    if ( _r.Cfg._.DZV == 1 && (S.DZV & 0x0C) != 0 ) S2.Most_Tir |= 0x08 ; // Если пришло хотя бы одно ДЗВ .
    if ( S.flg._.Revers   == 1 ) S2.Most_Tir |= 0x40 ; // 6й - SPI ведущего моста .
    if ( S.flg._.SnImpVM2 == 1 ) S2.Most_Tir |= 0x80 ; // 7й - снятие импульсов .

      //-------  Опрос необходимости реверса и его Инициализация. ----
    Revers_start () ;

    /* Зарядка ЕПА на угол измерения тока */

  asm_di() ;
    s2_ax = S2.TZ;
    s2_cx = s2_ax - timer1 ;

    if ( (u)s2_cx < (w)Tsyn*2  &&  s2_cx >= _MkSec( 50 ) )
    {
      _sifu2_epa_time ( s2_ax );
  asm_ei() ;
    }
    else
    {
  asm_ei() ;
      do  s2_cx = s2_ax - timer1 ;
      while ( (u)s2_cx < (w)Tsyn*2  );
      goto beg_imp ;
    }

    break;
  }
  pV( 0 ) ;

  return;
}
//---------------------------------------------------

#ifndef _Obj_Id2_izm

void Id2_Izm (void)
  {
// Контроль пробития тиристора работает только если определён сигнал с трансформаторов тока
// или ОС для РТ и есть Itt :
#if defined (Itt_ach) /*|| defined (Itt1_ach)*/ || defined (Itt2_ach) || defined (_Id_on_Itt_for_ProboyTir)
    static lword lax ;
#endif
    static byte Idmax2 , Id2_max ;
    static word time_Id_max2 , time_Id_max_2 ;
    word ax;
    register word ix ;

            /*    Измерение мгновенного тока */
      Id2_full = _AD_BUSY;
      mAD_Izm (  Id2_mg_ach  , &Id2_full ) ; // ИЗМЕРЕНИЕ  "Id_Full"

            // Измерение суммарного тока :
    // 07.09.07 11:00 - Если аналоговый канал не определён , то знаковый суммарный
    // ток Id_sum находится в SIFU2.C как алгебраическая сумма двух мгновенных .
    // 14.09.2017 12:40 - Если аналоговый определён , то по знаковому суммарному
    // току Id_sum отрабатываем аварию в обоих СИФУ (Сказал Соломаха для Слябинга 12500) :
  #ifdef  Id_sum_ach
      Id_sum_full = _AD_BUSY;
      mAD_Izm (  Id_sum_ach  , &Id_sum_full ) ;
  #endif

      // Измерение токов по фазам :
  #if defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach )
      Id2_Izm_3faz () ;
  #endif

            /*    Измерение среднего тока */
#ifdef  Id2_sr_ach
      Id2_sr_full = _AD_BUSY;
      mAD_Izm (  Id2_sr_ach  , &Id2_sr_full ) ;
#endif
#ifdef  Itt2_ach
      Itt2_full = _AD_BUSY;
      mAD_Izm (  Itt2_ach    , &Itt2_full ) ; // ИЗМЕРЕНИЕ  "Itt1_Full"
#else             // Для определения пробитого тиристора необходимо мерять фазный ток здесь ,
  #ifdef Itt_ach  // т.к. длительность пульса - 1 мс и если мерять в СИФУ1 , то тока не будет видно ...
      Itt_full = _AD_BUSY;
      mAD_Izm (  Itt_ach    , &Itt_full ) ; // ИЗМЕРЕНИЕ  "Itt_Full"
  #endif
#endif
       while ( Id2_full == _AD_BUSY );

    mIzmData_Conversion ( Id2_full , ix ,  Id2_mg_ach   ) ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
        //   беззнаковый ток.
    IDV2 = ix ;
        //   знаковый ток по номеру моста.
    if ( S.NumMost != 2 ) Id2_dop_kod =  ix ;
    else                  Id2_dop_kod = ~ix + 1 ;

            // Измерение суммарного тока :
    // 07.09.07 11:00 - Если аналоговый канал не определён , то знаковый суммарный
    // ток Id_sum находится в SIFU2.C как алгебраическая сумма двух мгновенных .
    // 14.09.2017 12:40 - Если аналоговый определён , то по знаковому суммарному
    // току Id_sum отрабатываем аварию в обоих СИФУ (Сказал Соломаха для Слябинга 12500) :
  #ifdef  Id_sum_ach
    while ( Id_sum_full == _AD_BUSY );
    mIzmData_Conversion ( Id_sum_full , ix ,  Id_sum_ach   ) ;
    //   знаковый суммарный ток :
    Id_sum = (slw)(sw)ix * (slw)(sw)_or.Mashtab_Id_sum / 256 ;

            // Защита по суммарному току :
    // 14.09.2017 12:40 - Если аналоговый определён , то по знаковому суммарному
    // току Id_sum отрабатываем аварию в обоих СИФУ (Сказал Соломаха для Слябинга 12500) :
    if ( (sw)Id_sum > (sw)_or.Id_sum_max || (sw)Id_sum < (sw)(~_or.Id_sum_max +1) )
    {
        Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
        // Пока что без выдержки времени :
        mOtkl_Q2 () ;
        mSet_AvarMsg ( _Av_Id_sum_Max ) ;
        Av2._.Id_sum_max = 1 ; // Только для регистрации в аварийном битовом поле .
    }
  #else //   знаковый суммарный ток как алгебраическая сумма двух мгновенных :
    Id_sum = (sw)( Id_dop_kod + Id2_dop_kod ) / (sw)2 ;
  #endif

        //  Двойная проверка на случай затирания одного из двух битов
       // при наложении прерывания на операции с этими ячейками.
       // 15.02.2016 9:22 - Эта двойная проверка - пережиток прошлого ,
       // когда флаг выставлялся в СИФУ , а авария - в фоне .
                                                     // 16.10.2008 16:27 - ИУ моста отключены извне.
    if ( (IDV2 >= _r.Id_Max /*|| Av._.Id2_max == 1*/) && S2.flg._.VneshZp == 0 )
    {
      if ( ((u)((b)(Puls_counter - time_Id_max_2)) >= _r.time_Id_max) || Id2_max == 1 ) // проверка длительности превышения.
      { // 16.10.2008 16:27 - При отключенном Ведомом мосту , если , например , питание ДТ
        mSet_AvarMsg2( _Av2_Id2_Max ) ;             // отключили , аварию не отрабатываем .
        Av._.Id2_max = 1 ;
        mOtkl_Q2 () ;
        Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
        Id2_max = 1 ; // когда счетчик Puls_counter обнулится , останется взведенным флаг ...
      }
    }
    else time_Id_max_2 = Puls_counter , Id2_max = 0 ;

    // 21.12.2013 12:56
    // Защита на случай зависания фона (например, как в Березниках), когда теряется синхронизация (выполняется в фоне)
    // и,как следствие, "плывут" импульсы, а всё, что делается чуть выше (сдвиг, отключение Q2 (Q1),
    // которого физически может и не быть, установка аварийных сообщений из-за зависшего фона не
    // переводит систему в аварию) не отключает агрегат.
    if( Av._.Id2_max == 0 )
    {
        Idmax2 = 0;
        time_Id_max2 = Puls_counter;
    }
    else
    {
            // Ожидаем снятие импульсов фоновой программой, и если этого не происходит,
            // снимаем импульсы, готовность и включаем аварию.
            // Переводим уставку из Timer1_Ovr в Puls_counter.
        ax = _r.Time_do_OtklImp * (_pSec( 1.0 ) / _Sec( 1.0 )) + _pSec( 0.2 );
        if( ( ( (u)((w)(Puls_counter - time_Id_max2)) > ax ) && ( Otkl_Imp != _Avar_imp ) ) )  Idmax2 = 1; // для защёлки

            //----------

        if( IDV2 >= _r.Id_Max )
        {        // Если ток не падает, значит сдвиг импульсов не помогает и дальше ждать нечего
            if ( (u)((w)(Puls_counter - time_Id_max2)) > _pSec( 0.05 ) )    Idmax2 = 1; // для защёлки
        }

            //----------

        if ( Idmax2 == 1 )
        {
                mOtkl_Imp( _Avar_imp ) ;
                bo_Avar = 1 ;
                bo_Gotov = 0 ;
                bo_canAvar = 1 ;
                bo_canGotov = 0 ;
        #ifdef _POWER
                bo_MB1_Razr = 0 ;
        #endif

                bo_Vkl_QK1 = 0 ;

#ifndef  _Adc_Extend_Po0 // Если Порт 0 не используется для управления внешним мультиплексором АЦП :
                Port_output (); // Централизованная выдача внешних сигналов.
#else
                // Номер выборки и номер порта , в котором находятся Авария , Готовность , Предупреждение :
                S400_output ( _or.AS_CSo[_AsPo_Av_Pr_Got_] , _AsPo_Av_Pr_Got_);
#endif
        }
    }

#ifdef  Id2_sr_ach
    while ( Id2_sr_full == _AD_BUSY );
        //  Преобразование измеренного среднего тока.
    mIzmData_Conversion ( Id2_sr_full , ix ,  Id2_sr_ach ) ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Id2_sr = ix ;
#endif

      // Преобразование токов по фазам :
#if defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach )
    Id2Conv_3faz () ;
#endif

      // Распределение токов по фазам двух секций ШС :
#if defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach ) && defined( IA4_ach ) && defined( IB4_ach ) && defined( IC4_ach )
    Tok2Raspr_3faz () ;
#endif

    //---------------------------------------------------------------------------------------------------------------

// Контроль пробития тиристора работает только если определён сигнал с трансформаторов тока
// или ОС для РТ и есть Itt :
#if defined (Itt_ach) /*|| defined (Itt1_ach)*/ || defined (Itt2_ach) || defined (_Id_on_Itt_for_ProboyTir)
   //---
  #ifdef  Itt2_ach
    while ( Itt2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( Itt2_full , ix ,  Itt2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Idtt2 = ix ;
  #else             // Для определения пробитого тиристора необходимо мерять фазный ток здесь ,
    #ifdef Itt_ach  // т.к. длительность пульса - 1 мс и если мерять в СИФУ1 , то тока не будет видно ...
    while ( Itt_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( Itt_full , ix ,  Itt_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Idtt2 = ix*2 ; // Общий ток - это половина тока ШС2 .
    #endif
  #endif
   //---
    n2  = S2.N - 2 ; // Номер пробитого тиристора , через который течёт ток фазного КЗ .
    nn2 = S2.N + 1 ; // Номер тиристора , находящегося в одном плече с пробитым , через который течёт ток нагрузки .
    if ( (sb)n2  <= 0 ) n2 += 6 ;
    if ( (sb)nn2 >  6 ) nn2 = 1 ;
    //---
    // Ток , для определения пробитого тиристора :
   #ifdef  _Id_on_Itt_for_ProboyTir
    Iproboy2 = IDV2 ;     // ОС для РТ - это и есть ток с Трансформаторов Тока .
   #else
    Iproboy2 = Idtt2 ;   // Ток трансформаторов тока ШС2 ( Если Itt2 не определён , то рассчитывается в СИФУ2 ).
   #endif

    //-------------------------------------------------------------------------------------------------------------

    // Включен режим контроля , контроль запущен и флаги окончания теста не выставлены :
    if (  _r.Cfg2._.ProboyTir == 1 && flg_RaTe._.tyr_tst_go == 1 &&
        flg_RaTe._.tyr_tst_ok == 0 && flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0 )
    {
       // Измеряем токи по модулю - ток с трансформаторов тока должен превышать Уставку и при этом , в случае ,
       // если собрана цепь нагрузки , то тока в нагрузке не должно быть :
       // 12.07.2017 13:00 - DAN : При контроле тока выше 30% , не хватало тока для определения пробоя тиристора .
       //                          Уменьшение уставки тока до 20 % для определения пробоя , согласовано с Шестаковым .
       // 30.08.2017 13:45 - DAN : Шестаков заказал уставку для контроля пробоя тиристоров , т.к. при испытаниях наша
       //                          маломощная сеть не даёт даже 20 % тока на 150 грд...
       if ( Iproboy2 > _r.Id_tst_proboy // 17.09.2021 - 0.05, т.к. при 0.20 "пик" тока затягивается на следующий тиристор .
   #ifndef  _Id_on_Itt_for_ProboyTir // Ток в нагрузке проверяем если ОС РТ - это НЕ ток с Трансформаторов Тока :
                                        && IDV2 < _Id_nom(0.05)
   #else
     #ifdef  Id_sum_ach              // Если суммарный шунт есть , но РТ замкнут не по нему :
                                        && (sw)Id_sum < (sw)_Id_nom(0.10) && (sw)Id_sum > (sw)_Id_nom(-0.10)
     #endif
   #endif
            )
       {
        // Определение пробоя в каждом из двух ШС в каждом мосту :
        #if defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach ) && defined( IA4_ach ) && defined( IB4_ach ) && defined( IC4_ach )
          if      ( (sb)n2 == 1 || (sb)n2 == 4 )
          {
            if        ( IA3 > _r.Id_tst_proboy )   lax = _Pr2_ProbM3_VT11_24 << (n2-1) ;
            else /*if ( IA4 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM4_VT11_24 << (n2-1) ;
          }
          else if ( (sb)n2 == 2 || (sb)n2 == 5 )
          {
            if        ( IC3 > _r.Id_tst_proboy )   lax = _Pr2_ProbM3_VT11_24 << (n2-1) ;
            else /*if ( IC4 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM4_VT11_24 << (n2-1) ;
          }
          else //if ( (sb)n2 == 3 || (sb)n2 == 6 )
          {
            if        ( IB3 > _r.Id_tst_proboy )   lax = _Pr2_ProbM3_VT11_24 << (n2-1) ;
            else /*if ( IB4 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM4_VT11_24 << (n2-1) ;
          }
        #else
        // Если в каждом мосту по одному ШС , то рассчитываем пробитый тиристор , даже если есть все три фазных тока одного ШС :
          lax = _Pr2_ProbM2_VT11_24 << (n2-1) ;
        #endif
          mSet_PreduprMsg2( lax ) ;             // Предупредительное сообщение о пробитом .
          flg_RaTe._.tyr_tst_pr = 1 ;           // Выставляем флаг окончания теста - тиристор пробит .
       }
    }
#endif

    return;
  }

#endif
//---------------------------------------------------

// Измерение токов по фазам :
#if defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach )

 void Id2_Izm_3faz (void)
 {
   // 100мкс - все 6 измерений фазных токов мультиплексированными каналами .
   // Поэтому измеряем по 4 рабочих тока каждый пульс :
   //---
   // Определение фаз , по которым сейчас должен течь ток .
     // В режиме определения пробитого тиристора :          // В рабочем режиме :
     // Tir1 - фазные токи Iс ( Ia - необязательно )        // Tir1 - фазные токи Ia и Ib
     // Tir2 - фазные токи Ib ( Ic - необязательно )        // Tir2 - фазные токи Ia и Iс
     // Tir3 - фазные токи Ia ( Ib - необязательно )        // Tir3 - фазные токи Ib и Ic
     // Tir4 - фазные токи Ic ( Ia - необязательно )        // Tir4 - фазные токи Ib и Ia
     // Tir5 - фазные токи Ib ( Ic - необязательно )        // Tir5 - фазные токи Ic и Ia
     // Tir6 - фазные токи Ia ( Ib - необязательно )        // Tir6 - фазные токи Ic и Ib
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S2.N != 2 && S2.N != 5 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S2.N != 3 && S2.N != 6 ) )
    {
      IA3_full = _AD_BUSY; // ШС3
      mAD_Izm (  IA3_ach    , &IA3_full ) ; // ИЗМЕРЕНИЕ  "IA3_Full"
      //---
 #ifdef IA4_ach
      IA4_full = _AD_BUSY; // ШС4
      mAD_Izm (  IA4_ach    , &IA4_full ) ; // ИЗМЕРЕНИЕ  "IA4_Full"
 #endif
    }
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S2.N != 1 && S2.N != 4 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S2.N != 2 && S2.N != 5 ) )
    {
      IB3_full = _AD_BUSY; // ШС3
      mAD_Izm (  IB3_ach    , &IB3_full ) ; // ИЗМЕРЕНИЕ  "IB3_Full"
      //---
 #ifdef IB4_ach
      IB4_full = _AD_BUSY; // ШС4
      mAD_Izm (  IB4_ach    , &IB4_full ) ; // ИЗМЕРЕНИЕ  "IB4_Full"
 #endif
    }
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S2.N != 3 && S2.N != 6 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S2.N != 1 && S2.N != 4 ) )
    {
      IC3_full = _AD_BUSY; // ШС3
      mAD_Izm (  IC3_ach    , &IC3_full ) ; // ИЗМЕРЕНИЕ  "IC3_Full"
      //---
 #ifdef IC4_ach
      IC4_full = _AD_BUSY; // ШС4
      mAD_Izm (  IC4_ach    , &IC4_full ) ; // ИЗМЕРЕНИЕ  "IC4_Full"
 #endif
    }

  return ;
 }

//   Программа преобразования измеренных токов по фазам :
 void Id2Conv_3faz (void)
 {
    register word ix ;
    //---
   // Определение фаз , по которым сейчас должен течь ток .
     // В режиме определения пробитого тиристора :          // В рабочем режиме :
     // Tir1 - фазные токи Iс ( Ia - необязательно )        // Tir1 - фазные токи Ia и Ib
     // Tir2 - фазные токи Ib ( Ic - необязательно )        // Tir2 - фазные токи Ia и Iс
     // Tir3 - фазные токи Ia ( Ib - необязательно )        // Tir3 - фазные токи Ib и Ic
     // Tir4 - фазные токи Ic ( Ia - необязательно )        // Tir4 - фазные токи Ib и Ia
     // Tir5 - фазные токи Ib ( Ic - необязательно )        // Tir5 - фазные токи Ic и Ia
     // Tir6 - фазные токи Ia ( Ib - необязательно )        // Tir6 - фазные токи Ic и Ib
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S2.N != 2 && S2.N != 5 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S2.N != 3 && S2.N != 6 ) )
  {
    while ( IA3_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IA3_full , ix ,  IA3_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IA3 = ix ;
      //---
 #ifdef IA4_ach
    while ( IA4_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IA4_full , ix ,  IA4_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IA4 = ix ;
 #endif
  }
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S2.N != 1 && S2.N != 4 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S2.N != 2 && S2.N != 5 ) )
  {
    while ( IB3_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IB3_full , ix ,  IB3_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IB3 = ix ;
      //---
 #ifdef IB4_ach
    while ( IB4_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IB4_full , ix ,  IB4_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IB4 = ix ;
 #endif
  }
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S2.N != 3 && S2.N != 6 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S2.N != 1 && S2.N != 4 ) )
  {
    while ( IC3_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IC3_full , ix ,  IC3_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IC3 = ix ;
      //---
 #ifdef IC4_ach
    while ( IC4_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IC4_full , ix ,  IC4_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IC4 = ix ;
 #endif
  }

  return ;
 }

#endif

//---------------------------------------------------------------------------------------------------------------

      // Распределение токов по фазам двух секций ШС :
#if defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach ) && defined( IA4_ach ) && defined( IB4_ach ) && defined( IC4_ach )

 void Tok2Raspr_3faz (void)
 {
    word ax ;
    //---
    // Определение фаз , по которым сейчас должен течь ток :
    // Tir1 - фазные токи Ia и Ib
    // Tir2 - фазные токи Ia и Iс
    // Tir3 - фазные токи Ib и Ic
    // Tir4 - фазные токи Ib и Ia
    // Tir5 - фазные токи Ic и Ia
    // Tir6 - фазные токи Ic и Ib

    if ( Prg._.Gotovn == 0 ) // Контроль только в работе :
    {
      if ( S2.N == 1 ) // Tir1 - фазные токи Ia и Ib .
      {
         //--- Фаза A шкафов ШС3 и ШС4 :
         ax = IA3 - IA4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA3 + IA4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_A ) ;
           }
         }
         //---
         //--- Фаза B шкафов ШС3 и ШС4 :
         ax = IB3 - IB4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB3 + IB4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_B ) ;
           }
         }
      }
      else if ( S2.N == 2 ) // Tir2 - фазные токи Ia и Iс .
      {
         //--- Фаза A шкафов ШС3 и ШС4 :
         ax = IA3 - IA4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA3 + IA4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_A ) ;
           }
         }
         //---
         //--- Фаза C шкафов ШС3 и ШС4 :
         ax = IC3 - IC4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC3 + IC4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_C ) ;
           }
         }
      }
      else if ( S2.N == 3 ) // Tir3 - фазные токи Ib и Ic .
      {
         //--- Фаза B шкафов ШС3 и ШС4 :
         ax = IB3 - IB4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB3 + IB4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_B ) ;
           }
         }
         //---
         //--- Фаза C шкафов ШС3 и ШС4 :
         ax = IC3 - IC4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC3 + IC4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_C ) ;
           }
         }
      }
      else if ( S2.N == 4 ) // Tir4 - фазные токи Ib и Ia .
      {
         //--- Фаза B шкафов ШС3 и ШС4 :
         ax = IB3 - IB4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB3 + IB4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_B ) ;
           }
         }
         //---
         //--- Фаза A шкафов ШС3 и ШС4 :
         ax = IA3 - IA4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA3 + IA4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_A ) ;
           }
         }
      }
      else if ( S2.N == 5 ) // Tir5 - фазные токи Ic и Ia .
      {
         //--- Фаза C шкафов ШС3 и ШС4 :
         ax = IC3 - IC4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC3 + IC4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_C ) ;
           }
         }
         //---
         //--- Фаза A шкафов ШС3 и ШС4 :
         ax = IA3 - IA4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA3 + IA4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_A ) ;
           }
         }
      }
      else // Tir6 - фазные токи Ic и Ib .
      {
         //--- Фаза C шкафов ШС3 и ШС4 :
         ax = IC3 - IC4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC3 + IC4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_C ) ;
           }
         }
         //---
         //--- Фаза B шкафов ШС3 и ШС4 :
         ax = IB3 - IB4 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB3 + IB4)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr2S_B ) ;
           }
         }
      }
    }

  return ;
 }

#endif

//---------------------------------------------------------------------------------------------------------------

        //   Регулятор Выравнивающего Тока

void RVT ( void )
{    // не регистровые, чтобы сохранялись в стеке.
  word  ax, bx, cx ;
  lword lax ;

  // РВТ выполняем если есть хотя бы одно условие :
  // 1. Ток больше гранично-непрерывного .
  // 2. Задана уставка инициализации РВТ ( чтобы можно было её подобрать при включённом РВТ ) :
  if ( IDN >= INN || _or.RVT_INN0 == 0 )
  {
//ДДДДДДДДДДД Расчет ошибки.  ДДДДДДДДДДДДДД

    ax = Id2_sr - Id_sr ;

 //ДДДДДДДДДДД Расчет интегратора.  ДДДДДДДДДДДДДД

//   Проверка ограничений на возрастание или снижение интегратора.

    if ( (sw)ax >= 0 )
      {
        if ( S2.flg._.int_p == 1 )  goto d4 ;
      }
    else
      {
        if ( S2.flg._.int_m == 1 )  goto d4 ;
      }

    lax = _r.S2.Ki_rvt ;
    if ( lax != 0 )  //  при нулевом Ки обнуляем интегратор.
    {
      lax = (slw)(sw)lax * (slw)(sw)ax ;
      lax += (slw)(sw)S2.Integr  ;
      //    контроля переполнения не нужно: ?
      //-------------------------------------------------------------------------------------
      // 15.10.2008 15:12 - Интегратор сейчас word , без дробной части , поэтому максимальный
      //                    выход РДН нельзя делать более 5 грд ( 5*91*64= 29120 ) , чтобы не
      //                    переполнилось знаковое слово S2.Integr .
      //                    Для того , чтобы выход РДН был более 5 грд , необходимо сделать
      //                    дробную часть , контроль переполнения и т.д...
      //-------------------------------------------------------------------------------------
            /* Проверка ограничений. */
      //if ((slw)lax >= (slw)(sw)_Grad( +3 * 64 )) lax = _Grad( +3 * 64 ) ; 15.10.2008 15:12
      if ((slw)lax >= (slw)(sw)_Grad(_r.S2.RVTmax)) lax = _Grad(_r.S2.RVTmax) ;
      //else if ((slw)lax <  (slw)(sw)_Grad( -3 * 64 )) lax = _Grad( -3 * 64 ) ; 15.10.2008 15:12
      else if ((slw)lax <  (slw)(sw)_Grad(-_r.S2.RVTmax)) lax = _Grad(-_r.S2.RVTmax) ;
    }
    S2.Integr = (w)lax ;

    d4:  S2.flg._.int_p = 0 ,  S2.flg._.int_m = 0 ;

    //ДДДДДД  Расчет пропорциональной составляющей и выхода регулятора. ДДДДДД

      // 13.06.2018 13:15 - Шестаков сказал , что РВТ П-часть по мгновенному току .
      //ДДДДДДДДДДД Расчет ошибки.  ДДДДДДДДДДДДДД
      ax = IDV2 - IDV ;

      lax = _r.S2.Kp_rvt ;
      lax = (slw)(sw)lax * (slw)(sw)ax ;
      lax += (slw)(sw)S2.Integr ;

      //if ((slw)lax >= (slw)(sw)_Grad( +3 * 64 )) 15.10.2008 15:12
      if ((slw)lax >= (slw)(sw)_Grad(_r.S2.RVTmax))
      {
        //lax = _Grad( +3 * 64 ) , S2.flg._.int_p = 1 ; 15.10.2008 15:12
        lax = _Grad(_r.S2.RVTmax) , S2.flg._.int_p = 1 ;
      }
      //else if ((slw)lax <  (slw)(sw)_Grad( -3 * 64 )) 15.10.2008 15:12
      else if ((slw)lax <  (slw)(sw)_Grad( -_r.S2.RVTmax))
      {
        //lax = _Grad( -3 * 64 ) , S2.flg._.int_m = 1 ; 15.10.2008 15:12
        lax = _Grad(-_r.S2.RVTmax) , S2.flg._.int_m = 1 ;
      }
      S2.Out_rvt = (sw)lax >> 6 ;
  }
  // 12.12.2016 - Инициализация выхода и интегратора РВТ при Id-гр-непр . Интегратор
  // инициализируем нулём , т.к. он может пойти в любую сторону :
  else S2.Integr = (sw)_or.RVT_INN0 * 64 , S2.Out_rvt = _or.RVT_INN0 ;

        //  Линеаризация выхода Регулятора Тока
    //---------------------------------------------------

    ax = S.Alfa ;
    if ( ax > _Grad( 90 )) ax = _Grad( 180 ) - ax ;

    bx = ax >> 8 ;
    if ( ax  > _Grad( 45 ) )
      {
        bx -= 15 ;   // 15 -> 45 эл.гр.
        bx *=  6 ;   // 6 - коэффициент наклона прямой
                                      // в пределах 45 - 90 эл.гр.
        cx = 358 - bx ;  // 358(1,4) - коэффициент линеаризации при
                        // угле 45 эл. градусов.
        cx -= (w)( (lw)6u * (lw)(ax & 0x00FFu) >> 8 ) ;
        if ( cx < 0x100u )  cx = 0x100u ;
      }
    else
      {
        bx -=  7 ;  // 7 -> 20 эл.гр.
        bx *= 31 ;  // 31 - коэффициент наклона прямой
                                   // в пределах 20 - 45 эл.гр
        cx = 614 - bx ; // 514(2,4) - коэффициент линеаризации при
                                // угле 20 эл. градусов.
        cx -= (w)( (lw)31u * (lw)(ax & 0x00FFu) >> 8 ) ;
        if ( cx < 358u )  cx = 358u ;
      }
     //K_L = v_cx  ;

    S2.Alfa_RVT = (slw)(sw)S2.Out_rvt * (slw)(w)cx >> 8 ;

    //---------------------------------------------------
/*
    ax = S2.Alfa_RVT ;
      //  Ограничитель угла и интегральной части РВТ .
    if ( v_ax > _r.V_Alfa_Max )
      {
       Vm.Alfa_Old = _r.V_Alfa_Max ;
       v_lax = (lw)Vm.Alfa_Old << 8 ;

       asm  divu  v_lax , v_cx  ; //Релинеаризация  V_Alfa_Max
       v_cx = (w)v_lax << 6 ;

       if ( Vm.Zn == 0 )
        {
         Vm.int_p = 1 ;
         if ( Vm.Integr > v_cx ) Vm.Integr = v_cx ;
        }
       else
        {
         Vm.int_m = 1 ;
         v_cx = ~v_cx + 1 ;
         if ( (sw)Vm.Integr < (sw)v_cx ) Vm.Integr = v_cx ;
        }
      }
    else Vm.Alfa_Old = v_ax ;
  */
  return ;
}

//         ПРОГРАММА  РЕГУЛЯТОРА ТОКА ЯКОРЯ ВТОРОГО МОСТА для 12-пульсной схемы .
//-------------------------------------------------------------------------------

void RegTok2 (void)
 {
     byte  tst1 , tst2 , tst3 ;
     word  ax, bx, cx ;
     lword lax ;

   if ( Ckl._.RT1 == 1 || Isp._.RT1_Res == 1 )
   {
     // Инициализация РТ2 в наладочных режимах , в которых он не используется :
      OIRT_drob_2_ = 0 ;
      ZIDN_2_  = ZIDN1_2_ = 0 ;  /* выход ЗИ-РТ. */
      Set_ZIRT ( &zi_rt2 , 0 ) ;
      OIRT_2_  = _r.RevU0  ;  /* интегратор регулятора тока */
      OIRT1_2_ = _r.RevU0  ;  /* интегратор регулятора тока */
     //---
     return ;
   }
      tst1 = 0 , tst3 = 0 ;

   //----------------------------- ОГРАНИЧЕНИЕ ЗАДАНИЯ НА ТОК --------------------------------
   //------------- достаточно выполнить в основном РТ первого моста --------------------------
   //-----------------------------------------------------------------------------------------
   // У Ведущего моста отключены ИУ или наладочные режимы РТ2 , основной РТ не выполняется ,
   // поэтому вполняем принятие задания :
   if ( S.flg._.VneshZp == 1 || S.Disable == 1 || Ckl._.RT2 == 1 || Isp._.RT2_Res == 1 )
   {
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
      else  RegFlg._.OuRS = 0 ;

      // 1% задания тока , чтобы в канале не появилось отрицательное смещение :
      //16.11.06 if ( OuRegS == 0 )  OuRegS = 0x0002 ;
      //-----------

         // Проверка необходимости реверса.
      if ((( S.NumMost == 1 ) && ( RegFlg._.OuRS == 1 ))
                              ||
          (( S.NumMost == 2 ) && ( RegFlg._.OuRS == 0 )))
          {
            OuRegS = 0x0u ;
          //if ( ZIDN_2_ <= _r.Temp_RT_M )  S.flg._.Revers = 1 ;
            if ( ZIDN_2_ <= _r.Temp_RT_M/300 + 150 )  S.flg._.Revers = 1 ; // приведение ном/сек к плс/сек .
          }
      else
         {
        // признак реверса был, но снялся регулятором - давать небольшое задание
           if ( S.flg._.Revers == 1 )
             {
              OuRegS = (0x03u*_K_diskr) ;
              Prz._.Revers1 = 1 ;
              Prz._.Revers2 = 1 ; // для РТ2 СИФУ2 , чтоб работал пересчет интегратора при реверсе .
             }
           S.flg._.Revers = 0 ;
           S.flg._.ZapretImp = 0 ;

         }
     //-----------------
   }
   //-----------------------------------------------------------------------------------------
   //-----------------------------------------------------------------------------------------
   //-----------------------------------------------------------------------------------------
      IDN1_2_ =  IDN_2_;
      ZIDN1_2_ = ZIDN_2_;

      ZIDN_2_ =  OuRegS; // Задание тока однополярное - взят модуль .

      if ( ED1 > 126 )  ED1 = 126 ;

      bx = (w) TABLINN[ ED1 ] ;
      lax = (lw)_or.INN0_2_ * (lw)bx  ;
    //DRINN = (b) lax ;
      INN_2_ = (w) ( lax >> 8 ) ; // Гранично-непрерывный ток , пересчитанный с учётом ЭДС .

      //if ( ZIDN > _r.IZMAX )  ZIDN = _r.IZMAX ; 07.07.05 13:57

if ( Isp._.ZIRT_shunt == 0 ) // Если есть ЗИРТ :
{
    /*if ( ZIDN_2_ >= ZIDN1_2_ )
        {
          bx = ZIDN_2_ - ZIDN1_2_  ;
          if ( bx > _r.Temp_RT_P )  ZIDN_2_ = ZIDN1_2_ + _r.Temp_RT_P ;
        }
      else
       {
          bx = ZIDN1_2_ - ZIDN_2_  ;
          if ( bx > _r.Temp_RT_M )  ZIDN_2_ = ZIDN1_2_ - _r.Temp_RT_M ;
       }*/

      // Задатчик Интенсивности
      zi_rt2.in = (d)ZIDN_2_ ;
      Zad_IntensRT ( &zi_rt2 ) ;
      ZIDN_2_ = (w)zi_rt2.out ;
}
else
{
      Set_ZIRT ( &zi_rt2 , ZIDN_2_ ) ; // Инициализация всего ЗИРТ .
}

      ax = IDV2 ; // ОС только по току второго моста в 12-пульсной схеме .

#ifndef _KTEV
      if  ( IDN_2_ < (INN_2_ - INN_2_/6 )) IDN_2_ = ax ;
      else if  ( ax < IDN_2_ )             IDN_2_ = ax ;
      else                                 IDN_2_ = ax + (w)( (lw)( ax - IDN_2_ ) * (w)_r.KRTDI >> 8 ) ;
      //if ( FSIFU.DIO == 0 ) OIRT1 = OIRT ;
#else
      IDN = ax ; // 22.02.2008 8:37 - Для КТЭВа не нужен динамический коэффициент .
#endif

      if ( S2.flg._.Fdmin == 0 ) OIRT1_2_ = OIRT_2_ ;
      else
          {
            if ( ZIDN1_2_ > IDN_2_ )   // и если на прошлом пульсе был Fdmin==1 производим перерасчет интегратора
              {
                 bx = ( ZIDN1_2_ - IDN_2_ ) / 2 ;
                 if ( bx > (10*_K_diskr) ) bx = 10*_K_diskr ;

                 tst1 = 1 ;
                 goto ri  ;  // идет на перерасчет интегратора

                // lax = (lw) bx * (lw)KRTI ;
                // if ( lax > 0x0f00u )  lax = 0x0f00u  ;
                // OIRT = OIRT + (w) lax  ;
                // if ( ( OIRT > 0x4000u) || (OIRT > _r.RTMAX ) )  OIRT = _r.RTMAX ;

         ri_ok:              // перерасчет интегратора окончен
                 tst1 = 0 ;
                 OIRT1_2_ = OIRT_2_ ;
              }

          }

#ifndef _KTEV
      // 13.06.2018 13:15 - Шестаков сказал , что для 12-ти пульсных сделать возможность изменения :
      if ( ( ZIDN1_2_ >= INN_2_ ) && ( IDN_2_ > (sw)((slw)(sw)INN_2_ * (slw)(sw)_or.KINN >> 8)) ) //_or.KINN = 0.8
    //if ( ( ZIDN1_2_ >= INN_2_ ) && ( IDN_2_ > ( INN_2_ - INN_2_ / 5 )) )
        {
          tst2 = 0 ;
          if (ZIDN_2_ < INN_2_ )
            {
              if  ( INN_2_ <= (3*_K_diskr) )  // 16.11.06  ZIDN = 1 ;
              {      // 16.11.06 пока ZIDN не нуль, делаем кк и делали "ZIDN=1",
                if  ( ZIDN_2_ != 0 )  ZIDN_2_ = 1*_K_diskr ; // а в остальном пропускаем "0".
              }
              else              ZIDN_2_ = INN_2_ - (3*_K_diskr) ;
            }

        }
      else
        {
          tst2 = 1 ;
          if ( ZIDN_2_ >= INN_2_ )
            {
                 ZIDN_2_ = INN_2_ + INN_2_ / 15 + (1*_K_diskr) ;
            }
        }
      //01.03.2017 - Коэффициенты РТ берутся из двух мест - из уставки или рассчитываются АН :
      if  ( tst2 == 0 )  KRTI_2_ = _or_KRTNI_2_;  //_or.KRTNI_2_;   - Ти для непрерыного тока .
      else               KRTI_2_ = _or_KRTPRI_2_; //_or.KRTPRI_2_;  - Ти для прерывистого тока .

#else
      tst2 = 0 ; // Заглушка для компилятора .
      KRTI = _r.KRTNI; // 22.02.2008 8:37 - для КТЭВа не нужно хитрое обрезание задания и
                       //                   прерывистый коэффициент .
#endif


  //  bx = ZIDN - IDN ;
      bx = IDN_2_ - ZIDN_2_ ;

      if ( (sw)bx >= 0 )
        {
          if ( S2.flg._.Fmax == 1 )  goto r ;
        }
      else
        {
          if ( S2.flg._.Fmin == 1 )  goto r ;
        }

   ri:

   lax = KRTI_2_ ;

   if ( lax == 0 )
     {             // инициализация интегратора при Ки = 0 :
       OIRT_2_ = _r.RevU0 ;
       OIRT_drob_2_ = 0 ;
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
          if( (sw)OIRT_2_ >= 0 ) cx = 0 ; // +/+
      }
     else if( (sw)OIRT_2_ <  0 ) cx = 1 ; // -/-

     lax += (slw)(sw)OIRT_2_ << 16 ;
     lax += (lw)(w)OIRT_drob_2_ ;   // DROB ISN'T SIGNED !

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

     OIRT_2_ = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .
     OIRT_drob_2_ = lax ;       // запись дробной части .


    if ( tst1 == 1 )  goto ri_ok  ;
    if ( tst3 == 1 )  goto ri_ok1 ;
  //-----------------------------------------------------------------------

  r:

    if ( tst2 == 1 )
      {
        ORT_2_ = OIRT_2_;
      }
    else    //ДДДДДД  Расчет пропорциональной составляющей и выхода регулятора. ДДДДДД
      {
        //lax = (lw)bx * (lw)_r.KRTP ;
        //if ( lax > 0x4000u ) lax = 0x4000u ;

#ifndef _KTEV
        //01.03.2017 - Коэффициенты РТ берутся из двух мест - из уставки или рассчитываются АН :
        lax = _or_KRTP_2_ ; //_or.KRTP_2_ ;
#else
        lax = _or.KRTP_2_ ;
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
             if( (sw)OIRT_2_ >= 0 ) cx = 0 ; // +/+
          }
        else if( (sw)OIRT_2_ <  0 ) cx = 1 ; // -/-

        lax += (slw)(sw)OIRT_2_ << 16 ;
        lax += (lw)(w)OIRT_drob_2_ ;   // DROB ISN'T SIGNED !

                  /* Проверка переполнений. */
                      //  переполнение в плюс?
              if     ( cx == 0 && (slw)lax <  0 ) goto p3 ;
                      //  переполнение в минус?
              else if( cx == 1 && (slw)lax >= 0 ) goto p2 ;
                      //  нет переполнения.

                  /* Проверка ограничений. */
              if ( (slw)lax < ((slw)_r.RTMIN << 16) )
                {
       p2:          ORT_2_ = (lw)_r.RTMIN ;
                }
              else if ( (slw)lax >= ((slw)_r.RTMAX << 16) )
                {
       p3:          ORT_2_ = (lw)_r.RTMAX  ;
                }
              else  ORT_2_ = (slw)lax >> 16 ; // дробная часть уходит, целая записывается .

      }


   //----------------------------------------

        //Если РТ вызван не программой 'Реверс', и был реверс на прошлом пульсе -
            //   перерасчет инт.части, если сняты подтверждающие ИУ
            // чтобы она не застревала в угле начально-непрерывного тока
            // и при включении подтверждающих ИУ не было броска тока.

        if ( ( stop_pointR1 == 0 ) &&  (( S.flg._.Revers == 1 ) || ( Prz._.Revers2 == 1 )))
          {
            Prz._.Revers2 = 0 ;

          //-----
             if ( ( ZIDN1_2_ > IDN_2_ ) && ( IDN_2_ < (5*_K_diskr) ) )
               {
                 bx =  ZIDN1_2_ - IDN_2_ ;
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
   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   // !!!!!!!!!!!!!!! 28.12.2015 - Сделать в дальнейшем РТ и Линеаризацию !!!!!!!!!!!!!!!!!!
   // !!!!!!!!!!!!! ф-ями и передавать в них папраметры для 1-го и 2-го РТ !!!!!!!!!!!!!!!!!
   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//------------------------------------

        /*Программа линеаризации */

void Linear2 (void)
{
   register word  ax , bx , cx ;

  if ( ORT_2_ <= _Ugol_90 )  ax = ORT_2_ ;
  else                       ax = _Ugol_180 - ORT_2_ ;
    bx  = LIN [ ax >> 8 ] ;
    cx  = LIN [(ax >> 8) + 1 ] ;
    cx -= bx ;
    bx += (w)( (lw)cx * (lw)(ax & 0x00FFu) / 0x0100ul ) ;
  if ( ORT_2_ <= _Ugol_90 ) S2.Alfa = bx;
  else                      S2.Alfa = _Ugol_180 - bx ;
return;

}
//------------------------------------
