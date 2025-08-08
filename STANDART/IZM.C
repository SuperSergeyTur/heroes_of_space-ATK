
/*--------------------------------------------------*/

/*    Программа измерения смещения нуля некоторого канала АЦП,
 *  адрес структуры данных которого передается в качестве параметра.
 */
#ifndef    _MaxOffset_ach  // для возможности внешнего переназначения смещения.
  #define  _MaxOffset_ach   (25)
  #define  _Default_offset   (512)
#endif
word  Izm_NullOffset ( struct Channel_AD *ptr )
  {
    word ix , i , dx ;

       // Сохранение первоначального смещения.
    dx = ptr->offset ;
       // Установка первоначального смещения в "идеальную" среднюю точку.
    ptr->offset = _Default_offset ;

       //  Для усреднения смещения производим измерения в течение
      // 30мсек - время не кратное периоду сети (из-за Uc у генераторов).
    for ( i = timer1 ; (u)((w)(timer1 - i)) < _MkSec(30*1000) ; )
      {
        ix = _AD_BUSY  ;
        AD_Izm( *ptr , &ix ) ;
        while ( ix == _AD_BUSY ) ;
        mIzmData_Conversion( ix , ix , *ptr ) ;
//#define  mIzmData_Conversion( src , dest , ach )
       //  dest = ( (w)(src) >> 6 ) - (ach).offset

            //  Если смещение установлено правильно, то мы должны при
           // измерении получать "нуль".
          //  В противном случае следует корректировать смещение.
        if      ( (sw)ix > 0 ) ptr->offset++ ;
        else if ( (sw)ix < 0 ) ptr->offset-- ;
      }

       //  Проверка смещения на допуски.
    if (  (sw)ptr->offset > dx+_MaxOffset_ach ||
                          (sw)ptr->offset < dx-_MaxOffset_ach )
      {   // Восстановление первоначального смещения.
        ptr->offset = dx ;
        return 1 ;
      }
    return 0 ;
  }

//----------------------------------------------
//    Контроль питающих напряжений .
//  Напряжения контролируются по очереди, а не пачкой.

void  Control_Ucc ( void )
{
  static byte  tst ;

    switch ( N_Ucc )
      {
        default:
        case 0 :
#ifdef P24_ach
           if ( P24_Ucc != _AD_BUSY )
             {
               mIzmData_Conversion ( P24_Ucc , P24_Ucc , P24_ach ) ;
               if ( (sw)P24_Ucc < (sw)_r.P24_min || (sw)P24_Ucc > (sw)_r.P24_max )
                 {
                   if ( (tst & 0x01) != 0 ) // проверка повторности превышения.
                     {
                       Av._.P24 = 1  ;
                     }
                   else  tst |= 0x01 ;   // регистрация первого превышения.
                 }
               else
                 {
                   Av._.P24 = 0  ; // превышение было одиночное.
                   tst &= ~0x01 ;
                 }
#if defined( P12_ach )
               N_Ucc = 1 ;      // переход к следующему напряжению.
               P12_Ucc = _AD_BUSY ;
               AD_Izm ( P12_ach, &P12_Ucc ) ;
#elif defined( N12_ach )
               N_Ucc = 2 ;      // переход к следующему напряжению.
               N12_Ucc = _AD_BUSY ;
               AD_Izm ( N12_ach, &N12_Ucc ) ;
#elif defined( P5_ach )
               N_Ucc = 3 ;      // переход к следующему напряжению.
               P5_Ucc = _AD_BUSY ;
               AD_Izm ( P5_ach, &P5_Ucc ) ;
#else
               N_Ucc = 0 ;      // переход к следующему напряжению.
               P24_Ucc = _AD_BUSY ;
               AD_Izm ( P24_ach, &P24_Ucc ) ;
#endif
             }
#endif
          break ;
        case 1 :
#ifdef P12_ach
           if ( P12_Ucc != _AD_BUSY )
             {
               mIzmData_Conversion ( P12_Ucc , P12_Ucc , P12_ach ) ;
               if ( (sw)P12_Ucc < (sw)_r.P12_min || (sw)P12_Ucc > (sw)_r.P12_max )
                 {
                   if ( (tst & 0x02) != 0 ) // проверка повторности превышения.
                     {
                       Av._.P12 = 1  ;
                     }
                   else  tst |= 0x02 ;   // регистрация первого превышения.
                 }
               else
                 {
                   Av._.P12 = 0  ; // превышение было одиночное.
                   tst &= ~0x02 ;
                 }
#if defined( N12_ach )
               N_Ucc = 2 ;      // переход к следующему напряжению.
               N12_Ucc = _AD_BUSY ;
               AD_Izm ( N12_ach, &N12_Ucc ) ;
#elif defined( P5_ach )
               N_Ucc = 3 ;      // переход к следующему напряжению.
               P5_Ucc = _AD_BUSY ;
               AD_Izm ( P5_ach, &P5_Ucc ) ;
#elif defined( P24_ach )
               N_Ucc = 0 ;      // переход к следующему напряжению.
               P24_Ucc = _AD_BUSY ;
               AD_Izm ( P24_ach, &P24_Ucc ) ;
#else
               N_Ucc = 1 ;      // переход к следующему напряжению.
               P12_Ucc = _AD_BUSY ;
               AD_Izm ( P12_ach, &P12_Ucc ) ;
#endif
             }
#endif
          break ;
        case 2 :
#ifdef N12_ach
           if ( N12_Ucc != _AD_BUSY )
             {
               mIzmData_Conversion ( N12_Ucc , N12_Ucc , N12_ach ) ;
               if ( (sw)N12_Ucc < (sw)_r.N12_min || (sw)N12_Ucc > (sw)_r.N12_max )
                 {
                   if ( (tst & 0x04) != 0 ) // проверка повторности превышения.
                     {
                       Av._.N12 = 1  ;
                     }
                   else  tst |= 0x04 ;   // регистрация первого превышения.
                 }
               else
                 {
                   Av._.N12 = 0  ; // превышение было одиночное.
                   tst &= ~0x04 ;
                 }
#if defined( P5_ach )
               N_Ucc = 3 ;      // переход к следующему напряжению.
               P5_Ucc = _AD_BUSY ;
               AD_Izm ( P5_ach, &P5_Ucc ) ;
#elif defined( P24_ach )
               N_Ucc = 0 ;      // переход к следующему напряжению.
               P24_Ucc = _AD_BUSY ;
               AD_Izm ( P24_ach, &P24_Ucc ) ;
#elif defined( P12_ach )
               N_Ucc = 1 ;      // переход к следующему напряжению.
               P12_Ucc = _AD_BUSY ;
               AD_Izm ( P12_ach, &P12_Ucc ) ;
#else
               N_Ucc = 2 ;      // переход к следующему напряжению.
               N12_Ucc = _AD_BUSY ;
               AD_Izm ( N12_ach, &N12_Ucc ) ;
#endif
             }
#endif
          break ;
        case 3 :
#ifdef P5_ach
           if ( P5_Ucc != _AD_BUSY )
             {
               mIzmData_Conversion ( P5_Ucc , P5_Ucc , P5_ach ) ;
               if ( (sw)P5_Ucc < (sw)_or.P5_min || (sw)P5_Ucc > (sw)_or.P5_max )
                 {
                   if ( (tst & 0x08) != 0 ) // проверка повторности превышения.
                     {
                       Av2._.P5 = 1  ;
                     }
                   else tst |= 0x08;                           // регистрация первого превышения.
                 }
               else
                 {
                   Av2._.P5 = 0  ; // превышение было одиночное.
                   tst &= ~0x08 ;
                 }
#if defined( P24_ach )
               N_Ucc = 0 ;      // переход к следующему напряжению.
               P24_Ucc = _AD_BUSY ;
               AD_Izm ( P24_ach, &P24_Ucc ) ;
#elif defined( P12_ach )
               N_Ucc = 1 ;      // переход к следующему напряжению.
               P12_Ucc = _AD_BUSY ;
               AD_Izm ( P12_ach, &P12_Ucc ) ;
#elif defined( N12_ach )
               N_Ucc = 2 ;      // переход к следующему напряжению.
               N12_Ucc = _AD_BUSY ;
               AD_Izm ( N12_ach, &N12_Ucc ) ;
#else
               N_Ucc = 3 ;      // переход к следующему напряжению.
               P5_Ucc = _AD_BUSY ;
               AD_Izm ( P5_ach, &P5_Ucc ) ;
#endif
             }
#endif
          break ;
      }
          //  ---------------------------------------------------------

               //    Переделал, чтобы в Сб.Гот. не зависеть от поочередности измерений измерений.

#ifdef P24_ach
                   if ( Av._.P24 == 1 ) // проверка повторности превышения.
                     {
#ifdef  _Av_P24
                       mSet_AvarMsg( _Av_P24 ) ; // превышение было дважды подряд.
#else
                       mSet_PreduprMsg( _Pr_P24 ) ; // превышение было дважды подряд.
#endif
                     }
#endif

#ifdef P12_ach
                   if ( Av._.P12 == 1 ) // проверка повторности превышения.
                     {
                       mSet_PreduprMsg( _Pr_P12 ) ; // превышение было дважды подряд.
                     }
#endif

#ifdef N12_ach
                   if ( Av._.N12 == 1 ) // проверка повторности превышения.
                     {
                       mSet_PreduprMsg( _Pr_N12 ) ; // превышение было дважды подряд.
                     }
#endif
#ifdef P5_ach
                   if ( Av2._.P5 == 1 ) // проверка повторности превышения.
                     {
                       mSet_PreduprMsg( _Pr_P5 ) ; // превышение было дважды подряд.
                     }
#endif

  return ;
}
/*------------------------------------------------------------------*/

//    Программа принятия аналогового значения.
//
//   Программа имеет функции:
// - порог нуля ;
// - фильтрация.

  void  Izm_Analog ( void )
  {
    register word ax ;
             word  bx ;
    register lword lax ;

       // Измерение аналогового задания .
    bx = _AD_BUSY  ;
    AD_Izm( *pr->ach, &bx ) ;
    while ( bx == _AD_BUSY ) ;

      // Преобразование в знаковый дополнительный код.
    mIzmData_Conversion( bx , ax , *pr->ach ) ;

        //  Введение порога в задание, чтобы можно было выставить
        // устойчивый нуль задания при неустойчивом нуле АЦП (смещение,
        // биение и т.д.). Перевалив через порог задание начинает расти
        // с нуля, а не скачком, т.е. порог - это постоянная составляющая
        // и в минус и в плюс.
    if ( (sw)ax < 0 )
      {
        if ( (u)(w)(~ax + 1) <= (w)pr->porog ) ax = 0x0  ;
        else                               ax += (w)pr->porog ;
      }
    else
      {
        if ( (u)(w)ax <= (w)pr->porog    ) ax = 0x0  ;
        else                           ax -= (w)pr->porog  ;
      }
      //   Фильтрация: вычисление отклонения текущего измеренного задания
      // от предыдущего отфильтрованного, деление этого отклонения
      // на 'N' и прибавление его, вместе с получившейся после деления дробной
      // частью, к предыдущему значению задания, которое тоже имеет свою
      // дробную часть.
      //   Для задания будет взята только целая часть.
          // склеивание целой и дробной частей в "long".
      lax  = (lw)pr->out << 16 ;
      lax += (lw)(w)pr->drob ;
      lax += (slw)( ((lw)ax << 16) - lax ) / (sw)pr->shift   ;

      pr->out = (w)( lax >> 16 ) ;
      pr->drob = (w)lax ;

    return  ;
  }



