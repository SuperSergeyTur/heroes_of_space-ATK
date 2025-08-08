word SIFU_Start ( void )
{
  word ax, bx;

  mVkl_Imp ( _All_imp ) ;  // Otkl_Imp &= ~( 0xFFFFu) очистка регистра снятия импульсов
  mOtkl_Imp ( _Start_imp ) ;  // Otkl_Imp |= ( 0x8000u )программа стартует со снятыми импульсами
  S.flg._.ImpSet1 = 0;
  //S.flg._.ImpSet2 = 1;

   PPG_sifu_init();

    //Формируем задание на частоту ШИМ из уставки и задаем минимальное время импульса 3 мкс

    bx = 1000000ul/_r.Fwg;

    ax = bx - _r.t_off_min;

    PPG_sifu_set( ax, _r.t_off_min );

#ifdef _SIFU_Obj
//Импульс на тиристор

    Sifu_Obj_set();

#endif

   S.Alfa = _Grad(180);

   S.NumMost = 1;
#ifdef _F497
     //В 497 дискрета таймера 2 мкс, а не 1 мкс
    bx/=2;

#endif

   S.TZ = timer1+bx;

   init_sifu_epa( _sifu_epa_con ) ;

   _sifu_epa_time ( S.TZ );

   return 0;
}

void S_Interrupt ( void )
{
  //mUSEL_clr() ;

    Sifu_int_drv(_sifu_epa_con) ;  // сброс запроса прерывания.
    //При использовании Puls_counter необходимо помнить, что он зависит от Fwg
    Puls_counter++ ;

    Id_full = _AD_BUSY;

    mAD_Izm (  Id_mg_ach  , &Id_full ) ; // ИЗМЕРЕНИЕ  "Id_Full"
    //Перенесен в main
    //if ( Prg._.Cikl == 1 )    Cikl () ;

    Gercon_control();

    while ( Id_full == _AD_BUSY );

    IdConv ();



    Control_Id_Max ();

    if ( Prg._.RT == 1 )   RegTok ();

    Sled () ;   //150-200mcs

    if ( Av._.Sdvig_imp == 1 ) goto sdv ; // сдвиг импульсов в Альфа_Макс.
    else         s_ax = S.Alfa ;

    if ( s_ax > _r.S_Alfa_Max)
    {
sdv:
        s_ax =  _r.S_Alfa_Max ;
    }
    else if (s_ax < _r.S_Alfa_Min )  s_ax = _r.S_Alfa_Min;

    //ЗИ СИФУ - для ограничения изменения угла за пульс

    if ( s_ax > S.Alfa_Old )
    {
        s_cx = s_ax - S.Alfa_Old;
        if ( s_cx > _r.S_DeltaAlfa_Max) s_ax =  S.Alfa_Old + _r.S_DeltaAlfa_Max;
    }
    else
    {
        s_cx = S.Alfa_Old - s_ax;
        if ( s_cx > _r.S_DeltaAlfa_Max) s_ax =  S.Alfa_Old - _r.S_DeltaAlfa_Max;

    }

    S.Alfa_Old = s_ax;

    //Период ограничивается минимальной величиной импульса 3 мкс и минимальной паузой
    //между импульсами в 5 мкс, 180 гр = (1/Fwg)-8

    s_cx = 1000000l/_r.Fwg;

#ifdef _F497
     //В 497 дискрета таймера 2 мкс, а не 1 мкс
    S.TZ += (s_cx/2);
#else

    S.TZ += s_cx;

#endif




    s_lax = s_cx - _r.t_off_min -_r.t_on_min;

    s_lax *= s_ax;

    s_ax = (s_lax /_Grad(180))+_r.t_on_min;


    s_cx -= s_ax;

    PPG_sifu_set( s_ax, s_cx );

    if ( Otkl_Imp == 0 )
    {

      if (S.flg._.ImpSet1 == 0)
      {
        S.flg._.ImpSet1 = 1;

        if ( S.NumMost == 1 )
        {
           PPG_sifu_start1();
        }
        else if (S.NumMost == 2 )
        {
           PPG_sifu_start2();
        }
      }

    }
    else
    {
      if (S.flg._.ImpSet1 == 1)
      {
        PPG_sifu_stop();
        S.flg._.ImpSet1 = 0;
      }
    }


    _sifu_epa_time ( S.TZ );
    //mUSEL_set() ;
    return ;
}

