/*    Программа  "Задатчик Интенсивности Универсальный".
 *
 *   Программа, использующая ЗИ должна при вызове ЗИ передать ему в качестве
 * параметра адрес своего блока данных для обработки ЗИ.
 * Задатчик Интенсивности содержит пять темпов :
 *      - темп разгона двигателя вперед ( в "+" )    ;
 *      - темп торможения двигателя вперед ( в "+" ) ;
 *      - темп разгона двигателя назад ( в "-" )     ;
 *      - темп торможения двигателя назад ( в "-" )  ;
 *      - темп параболической (s-образной) характеристики .
 */

//   ВСТАВКИ в других файлах.


//  msg_tabl.h
//    { "ТeмпЗИs-РС-1  ", &_r.T_ZISkor_Parab      , 0             , _Sec( 20 )       , _Sec( 1 )    ,(w*)&_ind_Nom,  _Sec( 0.2 )     , 0xff, "сек", _form(1,3,2,2) },
//    { "ТeмпЗИs-РС-dN ", &_r.T_ZISkor_Parab_delta,_Skor_nom(0.0) ,_Skor_nom( 1.0 )  ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },

//  ustavki.c
//    #ifndef _KTEV
//      zi_rs.temp_parabola       = &_r.T_ZISkor_Parab ;
//      zi_rs.temp_parabola_delta = &_r.T_ZISkor_Parab_delta ;
//    #else
//      zi_rs.temp_parabola = 0 ; // адрес = 0, сама уставка
//    #endif                      // в UST_CNST.H игнорируется .

// ust_cnst.h
//   /* word     T_ZISkor_Parab  ;        */  0 ,  // 5 // sec
//   /* word     T_ZISkor_Parab_delta ;   */  _Skor_nom( 0.05 ),



void Zad_Intens ( struct ZI *zip )
{
//    Т.к. эта функция вызывается как из фона так и
//  из прерываний то, по-скольку компилятор не позволяет описать функцию
//  как реентерабельную, для сохранения временных переменных в стеке их
//  следует описать как автоматические, а не как регистровые (т.к.
//  автоматические переменные компилятор распологает в стеке).
  /*register*/  lword lax ;
  /*register*/   word ax ;
  /*register*/   word bx , cx , ds_abs, proizv ;
  /*register*/   byte lbl ;
  /*register*/   byte sign_lin ;

   //do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
   //tim <<= 8 ;       //  Из четырехбайтного полного значения времени
   //tim  += (bx>>8);  // для работы берутся средние два байта прини-
                     // мающие значения в диапазоне 0.25мсек-12.0сек.

  bx = timer1 ;               //_Sec(1.0)/2 для округления.
//ax = (w)( bx - zip->time + (w)_Sec( 1.0 )/2) / (w)_Sec( 1.0 ) ; // Вычисление dT в масштабе "dT,sec << 16".
// FAA  _Sec( 4.0 ) - dla povisheniya tocnosti v preobrazov. makrosa (esli brat _Sec( 1.0 ) to pri tempe 70 za 10 sek poluchaem ~810, a pri _Sec( 4.0 ) oshibka ne vidna
  ax = (w)((lw)(4ul * (lw)(w)( bx - zip->time + (w)_Sec( 1.0 )/2 ) ) / (lw)_Sec( 4.0 )) ;
  zip->time = bx ;  // запись момента текущей отработки ЗИ.

  if ( (sw)zip->in != (sw)zip->out_lin )
  {

     sign_lin = 0 ;
     // если вход и выход ЗИ положительны
     if ( (sw)zip->in >= 0 && (sw)zip->out_lin >= 0 )
     {
            // если вход больше выхода ЗИ используется темп разгона в "+".
        if ( (sw)zip->in > (sw)zip->out_lin )             bx = *zip->temp_p_razg, lbl = 1 ;
            // если вход меньше выхода ЗИ используется темп торможения в "+".
        else                                              bx = *zip->temp_p_torm, lbl = 2 , sign_lin = 1 ;
     }
     // иначе если вход и выход ЗИ отрицательны
     else if ( (sw)zip->in < 0 && (sw)zip->out_lin <= 0 )
     {
        // если вход меньше выхода ЗИ (по знаку) используется темп разгона в "-".
        if ( (sw)zip->in < (sw)zip->out_lin )             bx = *zip->temp_m_razg, lbl = 2 , sign_lin = 1 ;
       // если вход больше выхода ЗИ (по знаку) используется темп торможения в "-".
        else                                              bx = *zip->temp_m_torm, lbl = 1 ;
     }
        // если вход отрицательный, а выход положительный
     else if ( (sw)zip->in < 0 && (sw)zip->out_lin > 0 )  bx = *zip->temp_p_torm, lbl = 3 , sign_lin = 1 ;
        // если вход положительный, а выход отрицательный
     else if ( (sw)zip->in >= 0 && (sw)zip->out_lin < 0 ) bx = *zip->temp_m_torm, lbl = 4 ;


  //------- Рассчет интегратора N1 ( линейная часть ЗИ ) ---------------

     lax = zip->drob_lin ;
     lax += (lw)zip->out_lin << 16 ;
     if ( sign_lin == 1 ) lax -= (lw)bx * (lw)ax ;
     else                 lax += (lw)bx * (lw)ax ;
     zip->drob_lin = (w) lax ;
     zip->out_lin  = (w) ( lax >> 16 ) ;

  //------------- Проверка конечных условий интегратора N1 -------------

     switch ( lbl )    //    out <?> in
       {
         case 1:       //   + < +,  - < -
                 if ( (sw)zip->out_lin > (sw)zip->in ) zip->out_lin = zip->in, zip->drob_lin = 0 ;
         break ;

         case 2:       //   + > +,  - > -
                 if ( (sw)zip->out_lin < (sw)zip->in ) zip->out_lin = zip->in, zip->drob_lin = 0 ;
         break ;

         case 3:       //   + != -
                 if ( (sw)zip->out_lin < 0 ) zip->out_lin = 0, zip->drob_lin = 0 ;
         break ;

         case 4:       //   - != +
                 if ( (sw)zip->out_lin > 0 ) zip->out_lin = 0, zip->drob_lin = 0 ;
         break ;
       }
    }
  //--------------------------------------------------------------------

                  //   S-ЗИ.
    //    output = output_s + ( input - output ) * dt_ckl(sec) / Ts(sec) ;
    //  где Ts - уставка-постоянная времени S-закругления: либо задается фиксированная либо домножается для
    //         ускорения процесса на прямом участке и при дотяжке на завершающем участке.

         // если адрес уставки и ее значение не равны нулю ,
        // выполняется параболический ЗИ .
  if ( *zip->temp_parabola != 0 && zip->temp_parabola != 0 )
   {
/*           Проверенный вариант на C#. 2-02-18
 *
                    dt1 = time - time_old; time_old = time;
                    if (dt1 == 0) dt1 = dt;

                    dn = zi_rs1.output - s_out;

                    dn_old = dn_abs;
                    dn_abs = Math.Abs(dn);
                    dn_proizv = (dn_abs-dn_old) / dt1;

                    if (dn_proizv < 0) {}
                    else if (dn_abs > dN_temp) s_tau = s_Tau / (dn_abs / dN_temp);
                    else s_tau = s_Tau;

                    s_out += (zi_rs1.output - s_out) * dt1 / s_tau;

 */

                    //          КОРРЕКТИРОВКА УСТАВОЧНОГО ТЕМПА S-ЗИ

              //        ЗДЕСЬ "zip->temp_parabola" задает не темп, а постоянную времени
              //  и измеряется не в "ном/сек", а в "сек" аналогично постоянной времени регулятора.

              //   При подходе к установившемуся значению ( отрицательная производная отставания S_ZI от Lin_ZI)
              // сохраняем набранный ускоренный темп для сокращения времени дотяжки.

                 //  Вычисляем производную отставания S_ZI от Lin_ZI)

             bx = timer1 ;
             cx =  bx - zip->time_szi ;
             zip->time_szi = bx ;

                   // ДЛЯ ПОДДЕРЖАНИЯ ЗАДАННОГО ОТСТАВАНИЯ S-ЗИ ОТ ВХОДНОГО ЗИ.
                  //   чем больше отставание тем меньше постоянная времени S-ЗИ.

                 ds_abs = zip->out_lin - zip->out;
                 if ( (sw)ds_abs < (sw)0)  ds_abs *= -1 ;
                 // т.к. от производной нужен только знак, то упрощаем формулу
                 // zip->proizv = (d)(sw)(ds - zip->ds_old) / ( (d)cx / _MkSec(1) / 1000000.);//перевод в сек: делим на 1000000.
                 proizv = ds_abs - zip->ds_old;
                 zip->ds_old = ds_abs;

             if ((sw)proizv < (sw)0) {}
             else if (ds_abs > *zip->temp_parabola_delta)
             {
                 if ( ds_abs == 0 ) ds_abs = 1;
                 zip->temp_parabola_old = (lw)(*zip->temp_parabola) * (lw)(*zip->temp_parabola_delta) / ds_abs;
             }
             else   zip->temp_parabola_old = *zip->temp_parabola;

                 //          НЕПОСРЕДСТВЕННО  S-ЗИ  ФИЛЬТР.

             if( (sw)zip->temp_parabola_old <= (sw)0 ) zip->temp_parabola_old = 1;
             zip->s_out += (d)(sw)(zip->out_lin - zip->out) * (d)(w)cx / (d)zip->temp_parabola_old / 65536.;

             zip->out = (w)zip->s_out ;

   }
    // если адрес уставки равен нулю , выполняется только линейный ЗИ :
  else zip->out = zip->out_lin ; // Выходу ЗИ присваеваем выход линейного ЗИ .

  return ;

}
  //--------------------------------------------------------------------


  // ---------- Программа записи в переменные ЗИ значения ах -----------
  // ------ ( запись КОНЕЧНЫХ ЗНАЧЕНИЙ без переходных процессов ) ------

void Set_ZI ( struct ZI *zip , word ax )
{
  zip->in = ax ;

  zip->out_lin = ax ;
  //zip->out1    = ax ;
  zip->out     = ax ;

  zip->drob_lin = 0 ;

  zip->time = timer1 ;

  zip->s_out = ax ;
  zip->time_szi = timer1 ;
  //zip->proizv   = 0 ;
  zip->temp_parabola_old = *zip->temp_parabola ;

  return ;
}

  //--------------------------------------------------------------------

