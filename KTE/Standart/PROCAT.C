
// Программы для прокатных клетей :
//  1. РДН .
//  2. РРС ( лыжа ) .
//  3. Статический ток .
//  4. Контроль буксовки ( срыва тока ) .

#ifdef _RDN
/*---------------------------------------------------------------------------*/
/*--------------------- РЕГУЛЯТОР ДЕЛЕНИЯ НАГРУЗКИ --------------------------*/
/*----------------------------- ( РДН ) -------------------------------------*/
void  RDN ( void )
{
  word ax ;

  //  для фильтра.
  static word time;
  static double drob;
         word  bx, dt;
         double dax;

  //---
#ifndef _KTE_GD
  ax = Id_2v - Id_dop_kod ; // Рассчет рассогласования токов двух валков .
#else
  ax = Id_2v - Igen       ; // Рассчет рассогласования токов двух валков .
#endif

  dId = ax ;

  // Проверка на нахождение РДН в ЗОНЕ НЕЧУВСТВИТЕЛЬНОСТИ :
  if ( (sw)ax < (sw)_r.RDN_Dead_Zone && (sw)ax > (sw)(~_r.RDN_Dead_Zone + 1) )
   {
     ax = 0 ;
   }
  else
   {
     if   ( (sw)ax < 0 )  ax += _r.RDN_Dead_Zone  ;
     else                 ax -= _r.RDN_Dead_Zone  ;
   }
  // Расчет пропорциональной составляющей и выхода регулятора :
  // Усиление пропорциональным коэффициентом РДН :
  ax = (sw)( (slw)(sw)ax * (slw)(sw)_r.RDN_Kp >> 8 ) ;

  // Контроля переполнения не нужно :
  // при максимальной ошибке (2.65) , максимальном коэффициенте (30)
  // переполнения в рамках знаковых 16-ти разрядов не будет.

  // Ограничение выхода регулятора :
  if ( (sw)ax > (sw)_r.RDN_Max        )  ax =  _r.RDN_Max     ;
  if ( (sw)ax < (sw)(~_r.RDN_Max + 1) )  ax = ~_r.RDN_Max + 1 ;


  //--- КВВ 1-02-18  Фильтр выхода РДН - как нашел ОноприенкоНА было сделано в старой схеме ШР-24 Запстали до модернизации.

    if ( _r.RDN_Tfiltr != 0 )
    {
        bx = timer1 ;  dt = bx - time ;   time = bx ;  // запись момента текущей отработки фильтра.
        if ( dt >= _MkSec(10*1000) )  dt = _MkSec(10*1000) ;  // для первого входа, когда time еще не проинициализирован.

        dax  = (d)(sw)RDN_Out + drob ;
                                          //  приводим dt от "мксек" к "мсек" _r.RDN_Tfiltr: 1дискр.=1мсек
            dax += (d)(sw)( ax - RDN_Out ) * (d)(w)dt / (d)_MkSec(1000) / (d)(w)_r.RDN_Tfiltr ;

        ax   = (sw)dax ;
        drob =  dax  - (d)(sw)ax ;

        //---

        // На всякий случай - вдруг ошибся с формулой. Потом убрать.
        if ( (sw)ax > (sw)_r.RDN_Max        )  ax =  _r.RDN_Max     ;
        if ( (sw)ax < (sw)(~_r.RDN_Max + 1) )  ax = ~_r.RDN_Max + 1 ;
    }

  //---


  // Знаковый выход регулятора :
  RDN_Out = ax ; // 21.08.2009 8:35 - выход следует отнимать от задания во второй якорь .

  // В месте , где принимается выход РДН следует продумать РДН - в обе стороны или только
  // на уменьшение , и воспользоваться уставкой _r.Cfg2._.RDN_Decrease .

  return ;
}
#endif

  // РДН работает после ЗИРС . Выполнять РДН до ЗИ нет смысла ...

  // Продумать принятие выхода РДН :
  // 1. В обе стороны - обычно не применяется .
  // 2. Только на уменьшение ( _r.Cfg2._.RDN_Decrease ) - если РДН в Нижнем Валке , на котором нагрузка больше .
  // 3. Только на увеличение ( _r.CfgO._.RDN_Increase ) - если РДН в Верхнем Валке , на котором нагрузка менььше .


  /* ОБРАБОТКА Принятого Задания ( до ЗИ ) :
  // Буксовка нигде толком не проверена ...
  if ( _r.Cfg2._.Buksovka == 1 && liga._.buks == 1 )
   {
     Z_Skor = 0 ; // Снимается задание на входе ЗИРС ,
     mSet_ServiceMsg( _Srv_Buksovka ) ;
   }

     //---
  // Пример выполнения РДН ( отработано на ЗС, Слябинг , КТЕ-12к5 ) для своего якоря - выход прибавляется к заданию :
     //---
  // ОБРАБОТКА Принятого Задания ( после ЗИ ) :
  if ( _r.Cfg2._.Buksovka == 0 || liga._.buks == 0 ) // Если Буксовки нет :
   {
     // Если Регулятор Рассогласования Скорости отработал ( сформировал лыжу ) , вводится поправка от РДН после ЗИРС :
     if ( _r.Cfg2._.RDN == 1 )
     {
        if ( ( _or.CfgO._.IdStat_2v == 0 && liga._.liga_ok  == 1 ) || // Берем Статический Ток своего валка или
             ( _or.CfgO._.IdStat_2v == 1 && liga._.liga2_ok == 1 ) )  // второго валка :
        {
          if      ( _r.Cfg2._.RDN_Decrease == 1 && _or.CfgO._.RDN_Increase == 0 ) // РДН только на Уменьшение задания :
          {
             if ( (sw)RDN_Out < 0 && (sw)ZISkor > 0 ) ZISkor += RDN_Out ; // Только для НИЖНЕГО Валка .
             if ( (sw)RDN_Out > 0 && (sw)ZISkor < 0 ) ZISkor += RDN_Out ;
                //----------------------------------------------------------
                // Эта припарка толком не проверялась ,  её нужно продумать .
                // К тому же , сюда не будет входа при буксовке ...
                if ( Z_Skor == 0 )// Если задание снято по Буксовке :
                 { // При Буксовке и разности токов РДН должен вытянуть напряжения на
                   // нули ,токи должы сравняться и буксовка должна уйти .
                   // Проверяем и знак задания , и знак напряжения , на случай если
                   // оператор начнет лихорадочно педалировать в разные стороны :
                   if ( (sw)RDN_Out < 0 && ((sw)ZISkor > 0 || (sw)UdSr > 0) ) Z_Skor += RDN_Out ;
                   if ( (sw)RDN_Out > 0 && ((sw)ZISkor < 0 || (sw)UdSr < 0) ) Z_Skor += RDN_Out ;
                 }
                //----------------------------------------------------------

          }
          else if ( _r.Cfg2._.RDN_Decrease == 0 && _or.CfgO._.RDN_Increase == 1 ) // РДН только на Увеличение задания :
          {
             if ( (sw)RDN_Out > 0 && (sw)ZISkor > 0 ) ZISkor += RDN_Out ; // Только для ВЕРXНЕГО Валка .
             if ( (sw)RDN_Out < 0 && (sw)ZISkor < 0 ) ZISkor += RDN_Out ;
                //----------------------------------------------------------
                // Эта припарка толком не проверялась ,  её нужно продумать .
                // К тому же , сюда не будет входа при буксовке ...
                if ( Z_Skor == 0 )// Если задание снято по Буксовке :
                 { // При Буксовке и разности токов РДН должен вытянуть напряжения на
                   // нули ,токи должы сравняться и буксовка должна уйти .
                   // Проверяем и знак задания , и знак напряжения , на случай если
                   // оператор начнет лихорадочно педалировать в разные стороны :
                   if ( (sw)RDN_Out > 0 && ((sw)ZISkor > 0 || (sw)UdSr > 0) ) Z_Skor += RDN_Out ;
                   if ( (sw)RDN_Out < 0 && ((sw)ZISkor < 0 || (sw)UdSr < 0) ) Z_Skor += RDN_Out ;
                 }
                //----------------------------------------------------------
          }
          else // РДН и на Увеличение , и на Уменьшение :
          {
             ZISkor += RDN_Out ;                                          // Можно и для ВЕРXНЕГО , и для НИЖНЕГО Валков .
          }
        }
      }
   } */

/*---------------------------------------------------------------------------*/

#ifdef _DST
/*---------------------------------------------------------------------------*/
/*-------------------- Вычисление статического тока -------------------------*/
/*---------------------------------------------------------------------------*/
void  StatTok ( void ) // Старый датчик М.Головина - по производной скорости.
{
//КВВ:  Добавить потом приведение скорости к Skor_Nom, тока к Id_Nom.
    word  ax ;
   lword lax ;

    /*if ( code == 0 )
      {
        Id_Din = 0;
        Id_Stat = 0;

        return 0;
      }*/

// КВВ:  Tm - время разгона двигателя с механизмом до номинальной скорости номинальным током при номинальном потоке.
//
//     Iстат = Iполн - Iразгона
//
//      dNразгона     Tm                                     dNразгона     Tm
//     ----------- * ---- = dTразгона    =>      Iразгона = ----------- * ----  =>
//       Iразгона      F                                     dTразгона      F


   // определяем dN  -  изменение скорости за dt
   ax = Skor - Sk1 ; // Sk1 - скорость в предыдущем пульсе
#ifndef _KTE_GD
   if ((sw)ax > (sw)_Id_nom(  2.00 ) )  ax =  _Id_nom(  2.00 ) ;
   if ((sw)ax < (sw)_Id_nom( -2.00 ) )  ax =  _Id_nom( -2.00 ) ;
#else
   if ((sw)ax > (sw)_Ig_nom(  2.00 ) )  ax =  _Ig_nom(  2.00 ) ;
   if ((sw)ax < (sw)_Ig_nom( -2.00 ) )  ax =  _Ig_nom( -2.00 ) ;
#endif
   dSkor = ax ;
   // T_meh - постянная времени механизма, говорящая о том, сколько дискрет тока
   // приложить, чтобы изменить скорость на 1 дискрету  за 1 мs.
   lax = _r.T_meh ;  // постояннaя времени механизма

   //ax  = _MkSec( 1000u );
   //asm   mulu  lax , ax ;  // умножаем Tm на 1ms в дискретах timer1
   lax *= (w)_MkSec( 1000u ) ;

   ax  = (w)( timer1 - Time_stat ) ;
   Time_stat  =  timer1 ;

   //asm   divu  lax , ax ; // делим на среднее время dT в дискретах timer1
   lax /= (w)ax ;

#ifdef Iv_ach // При отсуствии канала Iv , переменная V.Fv_zad инициализируется нулем .
   //lax = (w)lax ;
   //ax  = 400 ;
   //asm   mulu  lax , ax ; // умножаем на номинальный поток
   lax *= (w)_Fv_nom( 1.00 ) ;

   //ax  = V.Fv_zad ;
   //asm   divu  lax , ax ; // делим на текуший поток
   lax /= (w)V.Fv_zad ; // делим на задание , срезаем колебания в V.Fv .
#endif

   //lax = (w)lax ;
   //asm   mul  lax , bx ; // умножаем на dN
   lax *= (sw)dSkor ;

   Id_Din = (sw)(slw)lax ;

#ifndef _KTE_GD
      ax = Id_dop_kod - Id_Din ;
      // Ограничение тока
      if ( (sw)ax > (sw)_Id_nom(  2.50 ) )  ax = _Id_nom(  2.50 ) ;
      if ( (sw)ax < (sw)_Id_nom( -2.50 ) )  ax = _Id_nom( -2.50 ) ;
#else
      ax = Igen - Id_Din ;
      // Ограничение тока
      if ( (sw)ax > (sw)_Ig_nom(  2.50 ) )  ax = _Ig_nom(  2.50 ) ;
      if ( (sw)ax < (sw)_Ig_nom( -2.50 ) )  ax = _Ig_nom( -2.50 ) ;
#endif

   Sk1 = Skor ; //  фиксация скорости

      Id_Stat = ax ;

    return ;
}

void  Stat_Tok ( void )
{
#ifdef bo_StatCurrent
  word ax ;
#endif

  if ( (b)( Puls_counter - puls_Istat ) >= _r.puls_Istat )//3  // Для отработки раз в 3 пульса .
   {
     puls_Istat = (b)Puls_counter ;
     StatTok () ;               // Датчик статического тока .
   }
  FiltrLowFreq ( &Id_Stat_flt ); //50mks // Фильтр статического тока .

#ifdef bo_StatCurrent
  if ( (sw)Id_Stat_flt.out >= 0 )  ax =  Id_Stat_flt.out     ;
  else                             ax = ~Id_Stat_flt.out + 1 ;
  //---
   // После того , как Статический Ток превысит Порог , по истечениии выдержек ,
   // выставляются Флаг Захвата и Флаг Лыжи :
  if ( ax > _r.Porog_Istat )
    {
      bo_StatCurrent = 1 ;
    }
  else
    {
      #ifndef _KTE_GD
        if ( ax < (_r.Porog_Istat - _Id_nom(  0.03 )) )
      #else
        if ( ax < (_r.Porog_Istat - _Ig_nom(  0.03 )) )
      #endif
          {
            bo_StatCurrent = 0 ;
          }
    }
#endif

  return;
}

/*  02.2018 КВВ 12500
// Новый датчик А.В.Игнатова - по интегралу динамического тока.

word  Stat_Tok_IAV50 ( word code )
{

//КВВ:  Добавить потом приведение скорости к Skor_Nom, тока к Id_Nom и деление на поток.

   static double Id_Stat_integr;
   static word time_stat, Id_old ;

   word  ax, bx, id, id_nom ;
   double dax ;

      if ( code == 0 )
      {
        Id_Stat_integr = 0;
        Id_Din2 = 0;
        Id_Stat2 = 0;
        Skor_xx = 0;
        Id_old = 0;

        return 0;
      }


// КВВ:  Tm - время разгона двигателя с механизмом до номинальной скорости номинальным током при номинальном потоке.
//
//      Iстат = (Nхх - Nфакт) * Kпривед.   ( Nфакт. = Nнагрузки, Nхх = Nрасчетная )
//
//      Nхх = Сумм( (Iполн-Iстат) * dt / Tm )
//

        id = Id_old; //  приводим в соответсвие: Текущая скорость получена за счет не текущего тока а предыдущего.

#ifndef _KTE_GD
        Id_old = Id_dop_kod;
        id_nom = _Id_nom( 1.0 );
#else
        Id_old = Igen;
        id_nom = _Ig_nom( 1.0 );
#endif

        bx  = (w)( timer1 - time_stat ) ;
        time_stat  =  timer1 ;

        dax = (slw)(sw)(id - Id_Stat2) * (slw)(w)bx ;

        dax = Id_Stat_integr + dax / (d)( (slw)(w)_or.T_meh2 * (slw)(w)_MkSec( 1000u ) ) ;
        if ((dax != NAN)&&(dax != INFINITY))
        {
          Id_Stat_integr = dax;
        }

        bx = (sw)Id_Stat_integr ;

        //---  переход от единиц тока к скорости

        Skor_xx = (slw)(sw)bx * (slw)_Skor_nom( 1.0 ) / (slw)id_nom;  //  Nхх = Nрасчетная

        //--- переход от единиц скорости к току

        ax = (slw)(sw)( Skor_xx - Skor ) * (slw)id_nom / (slw)_Skor_nom( 1.0 );

#ifndef _KTE_GD
      if ( (sw)ax > (sw)_Id_nom(  2.50 ) )  ax = _Id_nom(  2.50 ) ;
      if ( (sw)ax < (sw)_Id_nom( -2.50 ) )  ax = _Id_nom( -2.50 ) ;
#else

      if ( (sw)ax > (sw)_Ig_nom(  2.50 ) )  ax = _Ig_nom(  2.50 ) ;
      if ( (sw)ax < (sw)_Ig_nom( -2.50 ) )  ax = _Ig_nom( -2.50 ) ;
#endif

        //---

        Id_Din2 = id - ax ;

        //---

        //   lax *= (w)_Fv_nom( 1.00 ) ;
        //   lax /= (w)V.Fv_zad ; // делим на задание , срезаем колебания в V.Fv .

        //---

        Id_Stat2 = ax;

        //---

    return 0;
}


//  КВВ 02.2018
//
//  Переключение старого и нового датчиков статического тока.
//  Старый датчик М.Головина - по производной скорости.
//  Новый датчик А.В.Игнатова - по интегралу динамического тока.

void  Stat_Tok ( word code )
{

      if ( code == 0 )
      {
        Stat_Tok1 ( 0 );
        Stat_Tok_IAV50 ( 0 );
        return;
      }

      Stat_Tok1 ( 1 );
      Stat_Tok_IAV50 ( 1 );

      if( _or.CfgO._.Dat_Istat2 == 0 )  Id_Stat = Id_Stat1, Id_Din = Id_Din1;
      else                              Id_Stat = Id_Stat2, Id_Din = Id_Din2;

      return;
}*/
#endif

#ifdef _RRS
/*---------------------------------------------------------------------------*/
/*---------------- РЕГУЛЯТОР РАССОГЛАСОВАНИЯ СКОРОСТИ -----------------------*/
/*------------------------( РРС "Лыжа" ) ------------------------------------*/

void  RRS ( void )
{
  word ax ;
  //---
  if ( (sw)Id_Stat_flt.out >= 0 )  ax =  Id_Stat_flt.out     ;
  else                             ax = ~Id_Stat_flt.out + 1 ;
  //---
   // После того , как Статический Ток превысит Порог , по истечениии выдержек ,
   // выставляются Флаг Захвата и Флаг Лыжи :
  if ( ax > _r.Porog_Istat )
    {
      if ( (u)((w)(Timer1_fSec - Time_Ist)) >= _r.T_zahv ) liga._.zahv_ok = 1 ; // Захват произошел .
      if ( (u)((w)(Timer1_fSec - Time_Ist)) >= _r.T_liga ) liga._.liga_ok = 1 ; // Лыжеобразование завершено ( убрать рассогласование скоростей ) .
    }
  else
    {
        Time_Ist = Timer1_fSec ;
        //---
      #ifndef _KTE_GD
        if ( ax < (_r.Porog_Istat - _Id_nom(  0.03 )) )
      #else
        if ( ax < (_r.Porog_Istat - _Ig_nom(  0.03 )) )
      #endif
          {
            // Снятие флагов с гистерезисом 3% :
            liga._.zahv_ok = 0 , liga._.liga_ok = 0 ; // Разрешение формирования Лыжи перед очередным Захватом .
          }
    }

   // Если есть статический ток другого валка , выполняется аналогично :
#ifdef Id_stat_2v_ach
  //---
  if ( (sw)Id_Stat2_flt.out >= 0 )  ax =  Id_Stat2_flt.out     ;
  else                              ax = ~Id_Stat2_flt.out + 1 ;
  //---
#else // Статический ток второго валка передан по сети :
  if ( (sw)Id_stat_2v >= 0 )        ax =  Id_stat_2v     ;
  else                              ax = ~Id_stat_2v + 1 ;
#endif
  if ( ax > _r.Porog_Istat )
    {
      if ( (u)((w)(Timer1_fSec - Time_Ist2)) >= _r.T_zahv ) liga._.zahv2_ok = 1 ; // Захват произошел .
      if ( (u)((w)(Timer1_fSec - Time_Ist2)) >= _r.T_liga ) liga._.liga2_ok = 1 ; // Лыжеобразование завершено ( убрать рассогласование скоростей ) .
#ifdef bo_StatCurrent2
      bo_StatCurrent2 = 1 ;
#endif
    }
  else
    {
        Time_Ist2 = Timer1_fSec ;
        //---
      #ifndef _KTE_GD
        if ( ax < (_r.Porog_Istat - _Id_nom(  0.03 )) )
      #else
        if ( ax < (_r.Porog_Istat - _Ig_nom(  0.03 )) )
      #endif
          {
            // Снятие флагов с гистерезисом 3% :
           liga._.zahv2_ok = 0 , liga._.liga2_ok = 0 ; // Разрешение формирования Лыжи перед очередным Захватом .
           #ifdef bo_StatCurrent2
            bo_StatCurrent2 = 0 ;
           #endif
          }
    }

  return ;
}
#endif


  /* Пример выполнения Лыжи Предварительной .
  // До появления статического тока , начиная с нулевой скорости вводится рассогласование скоростей путем умножения
  // на коэффициент , меньший "1" . Таким образом Лыжа получается динамической , зависимой от величины задания скорости
  // ( отработано на ЗС, Слябинг , КТЕ-12к5 ) :
     //---
  // Раньше ( у Макса Головина ) Лыжа формировалась через добавку/вычитание дельты скорости по достижении скорости разрешения
  // формирования лыжи . Но это было неудобно , громоздкие контроли знаков задания и запрета перехода задания из-за лыжи
  // в другую полярность ... Кроме того , ввод добавки давал "пичек" тока притормаживания - а это просто не эстетично ...
     //---
  // Так же бессмысленно давать лыжу при появлении статическесго тока ( liga._.zahv_ok  == 1 && liga._.liga_ok  == 0 ) ,
  // в результате получим опять "пичек" тока притормаживания ...
     //---
  // ОБРАБОТКА Принятого Задания :
  // Если при включеннном контроле Буксовки сработала Буксовка :
  if ( _r.Cfg2._.Buksovka == 1 && liga._.buks == 1 )
  {
     Z_Skor = 0 ; // Снимается задание на входе ЗИРС ,
     mSet_ServiceMsg( _Srv_Buksovka ) ;
  }
  else // Если Буксовки нет :
  {
     // Формирование лыжи у "ВедомогоВерхнего" , если включен РРС .
     // Вычитаем Дельту Лыжи ( "ВедущийНижний" должен крутится быстрее ) :
     if ( _r.Cfg2._.RRS == 1 )
     {
       if ( ( _or.CfgO._.IdStat_2v == 0 && liga._.liga_ok  == 0 ) || // Берем Статический Ток своего валка или
            ( _or.CfgO._.IdStat_2v == 1 && liga._.liga2_ok == 0 ) )  // второго валка :
       {
         if ( _r.K_liga != 0 && _r.K_liga != 1*256 )  // сделали 256 чтобы не проходить весь диапазон для ее отключения.
         {
             Z_Skor = (slw)(sw)Z_Skor * (slw)(sw)_r.K_liga / 256;
         }
       }
     }
  } */


#ifdef _BUKSOVKA
/*---------------------------------------------------------------------------*/
/*----------------- Контроль буксовки ( срыва тока ) ------------------------*/
/*---------------------------------------------------------------------------*/

//   Контроль буксовки осуществляем по мгновенным токам , а также скоростям
// первого и второго валков .

void  Control_Buksovka ( void )
{
  //   К захвату и к статическому току не привязываемся , чтобы не пропустить
  // факт наличия буксовки при контроле ее в одном из 2х КТЭ .
  //----------------
  // Если разность токов больше порога выключения РДН :
  if ( (sw)dId > (sw)_r.Id_RDN_off || (sw)dId < (sw)(~_r.Id_RDN_off+1) )
    {
      liga._.did = 1 ;
    }
  // Если разность токов меньше порога включения РДН :
  else if ( liga._.did == 1 )
    {
       if ( (sw)dId < (sw)_r.Id_RDN_on && (sw)dId > (sw)(~_r.Id_RDN_on+1) )
        {
            liga._.did = 0 ;
        }
    }
  //----------------
#ifdef N_2v_ach
  dN = N_2v - Skor ; // разность скоростей .
  // Если разность скоростей больше порога выключения РДН :
  if ( (sw)dN > (sw)_r.N_RDN_off || (sw)dN < (sw)(~_r.N_RDN_off+1) )
    {
      liga._.dn = 1 ;
    }
  // Если разность скоростей меньше порога включения РДН :
  else if ( liga._.dn == 1 )
    {
       if ( (sw)dN < (sw)_r.N_RDN_on && (sw)dN > (sw)(~_r.N_RDN_on+1) )
         {
            liga._.dn = 0 ;
         }
    }
#endif

  //----------------
  // Алгоритм обработки сигналов буксовки .
  //----------------
  // 1. Если Буксовка еще не определена , но условия есть :
  if ( liga._.buks == 0 && (liga._.did == 1 || liga._.dn == 1) )
    {
      if ( liga._.b_trig == 0 )
        {
          liga._.b_trig = 1 ;  // триггер буксовки .
          Time_buks = Timer1_Ovr ;
        }
      // Триггер буксовки взведён , - контролируем время :
      else if ( (u)( (w)(Timer1_fSec - Time_buks) ) > _r.Time_Buksov )
        {
          // Счетчик пульсов с буксовкой ( битовое поле из 4-х битов ) :
          if ( liga._.buk_count < 0xF ) liga._.buk_count++ ;
          //---
          if ( (b)(liga._.buk_count) >= (b)_r.count_Buk_f )
            {
              // Выдача сигнала "Буксовка" , для обработки в объектных программах :
              liga._.buks = 1 ;
              liga._.b_trig = 0 ;    // для ожидания следующей буксовки .
            }
        }
      //   Если за время контроля буксовки "_r.Time_Buksov" не набралось
      // требуемого количества дельт "_r.count_Buk_f" , снимаем триггер ,
      else liga._.b_trig = 0 ;       // для ожидания следующей буксовки .
    }
  //----------------
  // 2. Условия Буксовки сняты , ожиданием следующую Буксовку .
  else if ( liga._.did == 0 && liga._.dn == 0 )
    {
      liga._.b_trig = 0 ;
      if ( liga._.buk_count != 0 ) liga._.buk_count-- ; // уменьшаем счетчик с буксовкой .
      else  liga._.buks = 0 ; // счетсчик на нуле - снятие сигнала Буксовка .
    }

  //-----------------------------------------------------

  return ;
}
#endif


#ifdef _RVId
/*---------------------------------------------------------------------------*/
/*----- РЕГУЛЯТОР ВЫРАВНИВАНИЯ ТОКОВ ЯКОРЯ ЧЕРЕЗ ТОКИ ВОЗБУЖДЕНИЯ -----------*/
/*----------------------------- ( РВId ) ------------------------------------*/
void RVId_Reg( void )
{
    word ax, bx, cx;
    lword lax;

    if( Prg._.Gotovn == 1                          // В Сборке Готовности
#if defined( _KTEV )
       || ( Prg._.Gotovn == 0 && bi_LK_KTE == 0 )  // или в Работе, но ЛК КТЭ отключен
#elif defined( _KTE_GD )
       || ( Prg._.Gotovn == 0 && bi_LK == 0 )      // или в Работе, но ЛК отключен
#endif
      )
    {
        RVId.Integr = 0;
        RVId.Drob = 0;
        RVId.Out = 0;
        RVId.dId = 0;
        RVId.dIfz = 0;
        RVId.flg._.int_p = 0, RVId.flg._.int_m = 0;
        RVId.flg._.Work = 0;
        RVId.Time = Puls_counter;
        return;
    }

    if( Puls_counter != RVId.Time ); // Т.к. функция RVId вызывается в фоне (в main), а якорные токи измеряются
    else return;                      // в СИФУ перед РТ, то синхронизируемся с СИФУ.
    RVId.Time = Puls_counter;

#if defined( _KTE_GD )
         if( (sw)Ugen  >= (sw)_Ug_nom(  0.01 ) ) ax = RVId.Id2 - RVId.Id1; // Разница между токами двух двигателей (Id1 -> If, Id2 -> If2)
    else if( (sw)Ugen  <= (sw)_Ug_nom( -0.01 ) ) ax = RVId.Id1 - RVId.Id2; // Разница между токами двух двигателей (Id1 -> If, Id2 -> If2)
#elif defined( _KTEV )
         if( (sw)UdvSr >= (sw)_Ud_nom(  0.01 ) ) ax = RVId.Id2 - RVId.Id1; // Разница между токами двух двигателей (Id1 -> If, Id2 -> If2)
    else if( (sw)UdvSr <= (sw)_Ud_nom( -0.01 ) ) ax = RVId.Id1 - RVId.Id2; // Разница между токами двух двигателей (Id1 -> If, Id2 -> If2)
#else
         if( (sw)UdSr  >= (sw)_Ud_nom(  0.01 ) ) ax = RVId.Id2 - RVId.Id1; // Разница между токами двух двигателей (Id1 -> If, Id2 -> If2)
    else if( (sw)UdSr  <= (sw)_Ud_nom( -0.01 ) ) ax = RVId.Id1 - RVId.Id2; // Разница между токами двух двигателей (Id1 -> If, Id2 -> If2)
#endif
    else                                         ax = 0;

    RVId.dId = ax;

    bx = ax;
    if( (sw)bx < 0 ) bx = ~bx + 1;

    if( _r.RVId_Dead_Zone != 0 )
    {
             if( bx >=   _r.RVId_Dead_Zone       ) RVId.flg._.Work = 1;
        else if( bx <= ( _r.RVId_Dead_Zone / 2 ) ) RVId.flg._.Work = 0;
        if( RVId.flg._.Work == 0 ) return;
    }

    if( (sw)ax >= 0 )
    {
        if( RVId.flg._.int_p == 1 ) goto v4;
    }
    else
    {
        if( RVId.flg._.int_m == 1 ) goto v4;
    }

    //----------- Расчет интегратора --------------
    lax = _r.RVId_Ti & 0x7ffful; // защита от "-" коэфф.
    if( lax == 0 )
    {
        RVId.Integr = 0;
        RVId.Drob = 0;
        goto v4;
    }
    else
    {
#ifndef _KTE_GD
        lax = (lw)( (d)_Iv_nom( 0.01 ) / (d)_Id_nom( 0.01 ) * 3.3 * 65536. ) / lax;
#else
        lax = (lw)( (d)_Iv_nom( 0.01 ) / (d)_Ig_nom( 0.01 ) * 3.3 * 65536. ) / lax;
#endif
    }

    cx = ax;                   // ошибка .
    if( (sw)cx < 0 ) cx = -cx; // выпрямленная ошибка .
    // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
    // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
    if( ((lw)cx >= (lw)0x7fffffff / lax) && ( lax != 0 ) )    // sravnivaem modul oshibki
    {                                       // s maksimalno dopustimoy
        if( (sw)ax >= 0 ) lax = 0x7fffffff; // pri vychislennom 'Ki',
        else              lax = 0x80000000; // dlya 32-bit setki oshibkoy.
    }
    else lax = (slw)lax * (slw)(sw)ax;

    //  Подготовка к контролю переполнения (без использ.'asm'):
    // если до сложения/вычитания операнды были одного знака, а результат
    // получился другого знака - значит произошло переполнения.
    cx = 2;
    if( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
    {
         if( (sw)RVId.Integr >= 0 ) cx = 0; // +/+
    }
    else if( (sw)RVId.Integr <  0 ) cx = 1; // -/-

    lax += (slw)(sw)RVId.Integr << 16;
    lax += (lw)(w)RVId.Drob;   // DROB NOT IS SIGNED !
    RVId.Drob = lax;           // return drob.

    // Проверка переполнений.
    // переполнение в плюс?
         if( cx == 0 && (slw)lax <  0 ) goto v3;
    // переполнение в минус?
    else if( cx == 1 && (slw)lax >= 0 ) goto v2;
    // нет переполнения.

    // Проверка ограничений.
    if( (slw)lax < ( (slw)(sw)( ~_r.RVId_Max + 1 ) << 16 ) )
    {
v2:     RVId.Integr = ~_r.RVId_Max + 1;
    }
    else if( (slw)lax >= ( (slw)(sw)_r.RVId_Max << 16 ) )
    {
v3:     RVId.Integr = _r.RVId_Max;
    }
    else RVId.Integr = (w)( lax >> 16 );

v4:
    RVId.flg._.int_p = 0, RVId.flg._.int_m = 0;


    lax = _r.RVId_Kp & 0x7ffful;  // защита от "-" коэфф.
#ifndef _KTE_GD
    lax = lax * _Iv_nom( 0.01 ) / _Id_nom( 0.01 ) << 8;
#else
    lax = lax * _Iv_nom( 0.01 ) / _Ig_nom( 0.01 ) << 8;
#endif
    lax &= 0x7ffffffful;  //защита от "-" коэфф.

    //--- preventive overflow control.
    cx = ax;
    if( (sw)cx < 0 ) cx = -cx;
    // Если lax = 0 , то процессор _CM3_ при делении на нуль получает нуль , входит в условие
    // и выдаёт максимальный выход , что есть неправильно . Поэтому проверяем , что lax != 0 :
    if( ( (lw)cx >= (lw)0x7fffffff / lax ) && ( lax != 0 ) ) // sravnivaem modul oshibki
    {                                       // s maksimalno dopustimoy
        if( (sw)ax >= 0 ) lax = 0x7fffffff; // pri vychislennom 'Ki',
        else              lax = 0x80000000; // dlya 32-bit setki oshibkoy.
    }
    else lax = (slw)lax * (slw)(sw)ax;

    //  Подготовка к контролю переполнения (без использ.'asm'):
    // если до сложения/вычитания операнды были одного знака, а результат
    // получился другого знака - значит произошло переполнения.
    cx = 2;
    if( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
    {
         if( (sw)RVId.Integr >= 0 ) cx = 0; // +/+
    }
    else if( (sw)RVId.Integr <  0 ) cx = 1; // -/-

    lax += (slw)(sw)RVId.Integr << 16;

    // Проверка переполнений.
    //  переполнение в плюс?
         if( cx == 0 && (slw)lax <  0 ) goto p3;
    //  переполнение в минус?
    else if( cx == 1 && (slw)lax >= 0 ) goto p2;
    //  нет переполнения.

    if( (slw)lax < (slw)(sw)( ~_r.RVId_Max + 1 ) << 16 )
    {
p2:     ax = ~_r.RVId_Max + 1, RVId.flg._.int_m = 1;
    }
    else if( (slw)lax >= ( (slw)(sw)_r.RVId_Max << 16 ) )
    {
p3:     ax = _r.RVId_Max, RVId.flg._.int_p = 1;
    }
    else ax = (w)( lax >> 16 );

    RVId.Out = ax;
    if( _r.CfgRVId._.RVId_Vkl == 1 ) RVId.dIfz = RVId.Out;
    else                             RVId.dIfz = 0;

    return;
}

#endif
/*---------------------------------------------------------------------------*/

