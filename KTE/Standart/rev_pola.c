
//   ПРОГРАММА РЕВЕРСА ПОЛЯ
//
//--------------------------------------------------------

void Revers_Pola ( void )
  {
    #ifdef _Rev_Pola   // если включен алгоритм реверса поля.

    word ax , bx ;
    //byte bx ;

    // RP_Pz.all = 0 ;

    /*
      RP_Pz._.prev_delt  = 0 ; //сброс признака превышения модуля разн.скор.
      // В случае совпадения знака заданной скорости включенного направления
      if ( ( RP_Pz._.Napravl == 0 && (sw)ZISkor >= 0 )
                                      ||
           ( RP_Pz._.Napravl == 1 && (sw)ZISkor <  0 ) )
          {
           //- Контроль превышения модуля разности заданной и истинной --//
           //- скорости с уставкой порога.                             --//
           ax = ZISkor - Skor ;

           if ( (sw)ax > (sw)_Delt_Sk || (sw)ax < (sw)(~_Delt_Sk+1) )
             { //- установка признака превышения модуля разн. скор.
               RP_Pz._.prev_delt = 1 ;
             }
          }

  RP_Pz._.need_rever = 1 ;  // установка запроса реверса поля вначале

  // Проверка на необходимость реверса поля
  for ( bx = 0 ; bx < 3 ; bx++ )
    {
     if ( bx == 0 )
      {
       //-- Проверка несоответствия знака задания на ток --//
       //-- и включенного направления.                   --//
        ax = OuRegS_dop_kod ;
      }
     else if ( bx == 1 )
      {
       //-- Проверка несовпадения знака разности заданной и истинной --//
       //-- скорости и включенного направления.                       --//
        ax = ZISkor - Skor ;
      }
     else
      {
       if ( RP_Pz._.prev_delt == 1 )  goto rp ;
       //-- Проверка несовпадения знака заданной     --//
       //-- скорости и включенного направления.      --//
       ax = ZISkor ;
      }

        if ( (sw)ax < 0 ) // если отриц
          {
           // и направление отрицательное - сброс запроса и выход из цикла
           if ( RP_Pz._.Napravl == 1 )  { RP_Pz._.need_rever = 0 ;  goto rp ; }
          }
        else              // если полож.
          {
           // и направление положительное - сброс запроса и выход из цикла
           if ( RP_Pz._.Napravl == 0 )  { RP_Pz._.need_rever = 0 ;  goto rp ; }
          }
    }
       rp :
                   */


    //if ( RP_Pz._.Napravl == 0 /* && */)
    //  {
    //      _r.Iv_porg_Min ;
    //  }

    //Разрешение/запрет на выполнение реверса поля (контроль по току якоря).
    if ( (w)IDV < (w)_r.RIDRR )
      {
       RP_Pz._.razr_Rev_P = 1 ;   //разрешение
      }
    else
      {
        RP_Pz._.razr_Rev_P = 0 ;
        if ( RP_Pz._.Not_Rev_P == 1 )  mSet_ServiceMsg ( _Srv_Not_Nul_Id ) ;
      }
   // Определение знака измеренного тока возбуждения
    if ( (sw)V.Iv < 0 )  RP_Pz._.znak_Iv  = 1 ;
    else                 RP_Pz._.znak_Iv  = 0 ;

    RP_Pz._.znak_Fvz = 0 ;

    if ( _r.Cfg2._.Rev_Pola == 1 ) // если в конфиг-и вкл., "Ревес поля".
      {
        if ( Prg._.RegSk == 1 )
          {
        //-------------------------------------------------------
        // принятие задания с выхода РС на вход РТВ через нормирование.
              ax = (sw)( (slw)OuRegS_long * (slw)(sw)_r.Mashtab_Idz_Ivz >> 16 ) ; //

              if ( (sw)ax < 0 ) /*ax = ~ax + 1 ,*/ RP_Pz._.znak_Fvz = 1 ;
            }
          else  ax = 0 ;

          // Ограниечение до номинального потока
          if       ( (sw)ax > (sw)_Fv_nom( 1.0 ) )  ax = _Fv_nom( 1.0 ) ;
          else if  ( (sw)ax < (sw)_Fv_nom(-1.0 ) )  ax = _Fv_nom(-1.0 ) ;
          V.Fv_zad = ax ;

         RP_Pz._.Revers_Pol = 0 ;

        //Контроль управления реверсом поля
        if ( RP_Pz._.Napravl == 0 && RP_Pz._.znak_Fvz == 1 )
          {
            RP_Pz._.Revers_Pol = 1 ;
            // если при смене знака задания нет разреш. реверса
            if  ( RP_Pz._.razr_Rev_P == 0 )     V.Fv_zad = 0 ;
            else // есть разрешение
              {
                // если при смене знака задания - ток возбуждения меньше мин. порог.
                if ( (sw)V.Iv > (sw)(~_r.Iv_porg_Min + 1 ) )
                  {
                   V.Fv_zad =  (~_r.Iv_porg_Min+1) + _Fv_nom(-0.02) ;
                   // и долго нет реверса
                   if ( RP_Pz._.Not_Rev_P == 1 )  mSet_ServiceMsg ( _Srv_Not_Iv ) ;
                  /*P_Pz._.Revers_Pol = 1*/  // OuRegS_dop_kod  = 0 ;
                  }
                else                              RP_Pz._.Napravl = 1 ; // смена направления
              }
          }
        else if ( RP_Pz._.Napravl == 1 && RP_Pz._.znak_Fvz == 0 )
          {
            RP_Pz._.Revers_Pol = 1 ;
            // если при смене знака задания нет разреш. реверса
            if  ( RP_Pz._.razr_Rev_P == 0 )     V.Fv_zad = 0 ;
            else // есть разрешение
              {
                // если при смене знака задания - ток возбуждения меньше мин. порог.
                if ( (sw)V.Iv < (sw)_r.Iv_porg_Min  )
                  {
                   V.Fv_zad =  _r.Iv_porg_Min + _Fv_nom(+0.02) ;
                   // если долго нет реверса
                   if ( RP_Pz._.Not_Rev_P == 1 )  mSet_ServiceMsg ( _Srv_Not_Iv ) ;
                  /*P_Pz._.Revers_Pol = 1*/  // OuRegS_dop_kod  = 0 ;
                  }
                else                                    RP_Pz._.Napravl = 0 ;  // смена направления
              }
          }
       else
          {
           RP_Pz._.Malen_Iv = 0 ;
           if ( RP_Pz._.Napravl == 0 && RP_Pz._.znak_Fvz == 0 ) //если полож напр
             {
                // если задание на ток больше мин. пор, а ток возбуждения меньше мин. порог.
                if ( ((sw)V.Fv_zad > (sw)_r.Iv_porg_Min) && ((sw)V.Iv < (sw)_r.Iv_porg_Min ) )
                  {
                   V.Fv_zad =  _r.Iv_porg_Min + _Fv_nom(+0.02) ;
                   RP_Pz._.Malen_Iv = 1 ;
                  }
             }
           else if ( RP_Pz._.Napravl == 1 && RP_Pz._.znak_Fvz == 1 ) //если отриц напр
             {
                // если задание на ток больше мин. пор, а ток возбуждения меньше мин. порог.
                if ( ((sw)V.Fv_zad < (sw)(~_r.Iv_porg_Min + 1 )) && ((sw)V.Iv > (sw)(~_r.Iv_porg_Min + 1 ) ) )
                  {
                   V.Fv_zad =  (~_r.Iv_porg_Min+1) + _Fv_nom(-0.02) ;
                   RP_Pz._.Malen_Iv = 1 ;
                  }
             }
          }


       if ( RP_Pz._.Revers_Pol == 1 ) // если процесс реверса затянулся
          {
            if ( (w)(Timer1_Ovr - Time_RP ) > _Sec( 2.0 ))
              {
                mSet_ServiceMsg( _Srv_AvarRevers ) ;
                RP_Pz._.Not_Rev_P = 1 ;  // нет реверса
              }
          }
       else  Time_RP = Timer1_Ovr , RP_Pz._.Not_Rev_P = 0 ;


   /*----- Ограничитель и повторитель/инвертор задания тока  ----*/

      //при реверсе  или малом токе возб. ограничение выхода РС обнуляется
      if ( RP_Pz._.Revers_Pol == 1 || RP_Pz._.Malen_Iv == 1 )  ax = 0 , bx = 0 ;
      else  ax = _r.OuRSMaxMost1 , bx = _r.OuRSMaxMost2 ;

       if ( (sw)OuRegS_dop_kod >= 0 )
        {
          if ((sw)OuRegS_dop_kod > (sw)ax )  OuRegS_dop_kod = ax , Prz._.int_p = 1 ;
        }
       else
        {
          if ((sw)OuRegS_dop_kod < (sw)bx )  OuRegS_dop_kod = bx , Prz._.int_m = 1 ;
          OuRegS_dop_kod = ~OuRegS_dop_kod + 1 ;
        }
      }

 #endif

    return ;
  }

//--------------------------------------------------------

