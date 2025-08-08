/*-------------------------------------------------*/
//      Однопороговый контроль изоляции ротора по датчику
//  напряжения с делителя ус-ва контр.изоляции.
//
word  Contr_Insulat ( word num )
{
//---
#ifndef  Insulation_ach
//---
  num = num ;
//---
#else
//---
  static word Uinsul_full , Insul_time, Insul_timer ;
  static word Ud_insul ;
  static byte Ud_insul_drob ;
#ifdef  _Av_Insulat
  static word Insul_timer_av;
#endif

  register lword lax ;
  register word ax, bx ;

  switch ( num )
  {      //  Стартовая инициализация.
    case 0 :  Uinsul = 0 , Insul_time = Timer1_Ovr, Insul_timer = 0 ;
              Ud_insul = 0 , Ud_insul_drob = 0 ;
         #ifdef  _Av_Insulat
              Insul_timer_av = 0 ;
         #endif
     start: Uinsul_full = _AD_BUSY ;  //  запуск первого измерения изоляции
            AD_Izm ( Insulation_ach, &Uinsul_full ) ;
      break;
         //  Рабочая программа.
    case 1 :
            if ( Uinsul_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Uinsul_full, ax, Insulation_ach ) ;
                 if ( (sw)ax < 0 ) ax = ~ax+1 ;

                    //  Фильтрация.
                    // склеиваем целое и дробь.
               lax  = (slw)(sw)Uinsul << 8 ;
               lax += (lw)(w)Uinsul_drob ;   // DROB IS NOT SIGNED !

               if ( ax > Uinsul ) lax += _Insul_koef ;
               else               lax -= _Insul_koef ;

               Uinsul_drob = lax ;           // return drob.
               ax          = (slw)lax >> 8;
               if ( (sw)ax < 0 )  ax = 0 ;
               Uinsul = ax ;

               bx = _Uout ;   //  выделяем модуль Uout.
               if ( (sw)bx < 0 ) bx = ~bx+1 ;
                    //  Фильтрация опорного напряжения, чтобы оно изменялось с той же
                    //      постоянной что и напряжение изоляции.
                    // склеиваем целое и дробь.
               lax  = (slw)(sw)Ud_insul << 8 ;
               lax += (lw)(w)Ud_insul_drob ;

               if ( bx > Ud_insul ) lax += _Insul_koef ;
               else                 lax -= _Insul_koef ;

               Ud_insul_drob = lax ;           // return drob.
               bx            = (slw)lax >> 8;
               if ( (sw)bx < 0 )  bx = 0 ;
               Ud_insul = bx ;

                  //  Не коррект. порог при низком напряжении, т.к.порог
                  // стремится к нулю и срабатывает в Сб.Гот.
               if( bx < _Uout_nom( 0.25 ))  bx = _Uout_nom( 0.25 ) ;
                   //  Коррекция порога срабатывания пропорционально Uout:
                   //            porog = porog * Uout / Uout_nom.
               lax = (lw)bx * (lw)_r.Uinsul_max ;
               Uinsul_max  = lax / _Uout_nom( 1.0 ) ;

               ax = Timer1_Ovr-Insul_time ;
               Insul_time = Timer1_Ovr ;
                   //  Контроль порога изоляции с выдержкой времени.
               if ( Uinsul > Uinsul_max  && bi_Otkl_Insul == 0 )
               {     // задержка накопительного типа 15.05.06 17:01
                 if ( (sw)Insul_timer > (sw)_Sec( 5 ) )  // 9 ) )
                 {
                   mSet_PreduprMsg( _Pr_Insulat ) ;
                 }
                 else Insul_timer += ax ;
               }   //  вычитаем пока не переступили через нуль, и так и оставляем...
               else if ( (sw)Insul_timer > 0 ) Insul_timer -= ax ;

                     //  Предупреждение и выходной сигнал очищаются
                    // только через Дист.Сброс.
               if ( (Reg_PreduprMsg & _Pr_Insulat) != (lw)r0 )
                                                      bo_Insulat = 1 ;
               else                                   bo_Insulat = 0 ;
            //--------------------

          #ifdef  _Av_Insulat
               lax = (lw)bx * (lw)_r.Uinsul_max_av ;
               bx = lax / _Uout_nom( 1.0 ) ;

                   //  Контроль порога изоляции с выдержкой времени.
               if ( Uinsul > bx && bi_Otkl_Insul == 0 )
               {      //  Второй порог либо аварийный либо предупредительный.
                 if ( (sw)_r.Tinsul != 0 )  // задержка накопительного типа 15.05.06 17:01
                 {
                   if ( (sw)Insul_timer_av > (sw)_r.Tinsul )  // 9
                   {
                     mSet_AvarMsg( _Av_Insulat ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
                 else
                 {
                   if ( (sw)Insul_timer_av > (sw)_Sec( 5 ) )
                   {
                     mSet_PreduprMsg2( _Pr2_Insulat2 ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
               }   //  вычитаем пока не переступили через нуль, и так и оставляем...
               else if ( (sw)Insul_timer_av > 0 ) Insul_timer_av -= ax ;
          #endif

               //-----
               goto start; //  запуск очередного измерения.
             }
      break;
  }
//---
#endif
//---
  return 0 ;
}
