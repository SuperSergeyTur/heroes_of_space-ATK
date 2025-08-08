
//  ПРОГРАММА ОБРАБОТКИ СЕЛЬСИНА.

//------------------------------------------------------------------
//
//   Программа имеет функции:
// - смещение нуля ;
// - масштабирование ;
//   Интервал от сельсина до синхроимп. допускается в пределах
// (+-)180градусов.
//    Если сельсин опережает синхроимп. - задание положительное,
//  иначе - отрицательное.
//

      //  Настройки для Сельсинов.

void Selsin_init ( void )
{
  word ax ;
  Sels_tr.all = 0 ;
  for ( ax = 0 ; ax < _Sels_Num ; ax++ )   Selsin ( 0 , ax ) ;

  return ;
}

void Selsin_input ( void )
{
  word ax ;
  for ( ax = 0 ; ax < _Sels_Num ; ax++ )   Selsin ( 1 , ax ) ;

  return ;
}

word Selsin ( word code , word num )
{
  register slword lax ;
  register sword ax ;
  register struct SELSIN * p ;

  switch ( code )
  {
    case 0 :    // настройка EPA - передаем его условный номер.
      if ( num == 0 )
      {
        init_syn_epa( _selsin0_epa_con ) ;
        Sels[0].epa_addr  = (w*)&_selsin0_epa_time ;
        Sels[0].epa_time  =  _selsin0_epa_time ;
        Sels[0].out_g = 0 ;
        Sels[0].out_m = 0 ;
        Sels[0].drob = 0 ;

       // 13.08.2014 - Порог в градусах лучше не делать , т.к. в этом случае
       // сигнал сельсина может "сбиваться"

      //-----
      #ifndef   _Sels_mashtP0
        SelsDU[0].mashtP = (w*)&_Sels_mashtP ;
      #else
        SelsDU[0].mashtP = &_or.Sels_mashtP0 ;
      #endif
      //-----
      #ifndef   _Sels_mashtM0
        SelsDU[0].mashtM = (w*)&_Sels_mashtM ;
      #else
        SelsDU[0].mashtM = &_or.Sels_mashtM0 ;
      #endif
      //-----
      #ifndef   _Sels_shift0
        SelsDU[0].shift  = (b*)&_Sels_shift ;
      #else
        SelsDU[0].shift  = &_or.Sels_shift0 ;
      #endif
      //-----
      }
      else if ( num == 1 )
      {
        init_syn_epa( _selsin1_epa_con ) ;
        Sels[1].epa_addr  = (w*)&_selsin1_epa_time ;
        Sels[1].epa_time  =  _selsin1_epa_time ;
        Sels[1].out_g = 0 ;
        Sels[1].out_m = 0 ;
        Sels[1].drob = 0 ;

       // 13.08.2014 - Порог в градусах лучше не делать , т.к. в этом случае
       // сигнал сельсина может "сбиваться"

      //-----
      #ifndef   _Sels_mashtP1
        SelsDU[1].mashtP = (w*)&_Sels_mashtP ;
      #else
        SelsDU[1].mashtP = &_or.Sels_mashtP1 ;
      #endif
      //-----
      #ifndef   _Sels_mashtM1
        SelsDU[1].mashtM = (w*)&_Sels_mashtM ;
      #else
        SelsDU[1].mashtM = &_or.Sels_mashtM1 ;
      #endif
      //-----
      #ifndef   _Sels_shift1
        SelsDU[1].shift  = (b*)&_Sels_shift ;
      #else
        SelsDU[1].shift  = &_or.Sels_shift1 ;
      #endif
      //-----
      }
    break;

    default:;

      p = &Sels[num] ;
        /*  ЗАЩИТЫ от СБОЕВ и ИСЧЕЗНОВЕНИЙ/ПОЯВЛЕНИЙ СИНХРОНИЗАЦИЙ. */

          /* Пришел-ли новый синхроимпульс?  */
      if ( p->NS2_time == Syn.NS2 )  return 0 ;

        /*   По изменению содержимого ЕПА по сравнению с предыдущим вызовом
         * судится о том, что пришел синхроимпульс (ну или помеха) */
      if ( p->epa_time == *p->epa_addr )  return 0 ;

      ax = *p->epa_addr - p->epa_time ; /* Расчет интервала между соседними импульсами сельсина.    */
      p->epa_time = *p->epa_addr  ; /* Запоминается текущее содержимое ЕПА. */
      p->NS2_time = Syn.NS2  ;

      if ( (w)ax < _r.TMIN || (w)ax > _r.TMAX )  return 0 ;  /* Отсеивание ложных замеров. */

          // Вычисление интервала от сельсина до синхроимп..
      ax = p->epa_time - Syn.NS2 ; // NS2 - отфильтрованный момент синхроимпульса.
      //Перевод в градусы
      lax = (slw)ax << 15 ;
      ax = Tsyn ;
      //asm  div  lax, ax ;
      //ax = (sw)lax ;
      ax = (slw)lax / (sw)ax ;
         // Введение смещения нуля.
      ax -= _r.Selsin[num].null ;
        //--------
#ifdef _SELS_NULL
      // Подана команда "Выставить нуль сельсина 0 или сельсина 1"
      if ( (Sels_tr._.null0 == 1 && num == 0) || (Sels_tr._.null1 == 1 && num == 1) )
      {
        // Если сигнал сельсина с текущим смещением больше 1грд , тогда выполняем установку нуля :
        if ( (sw)ax > (sw)_Grad(1) || (sw)ax < (sw)(~_Grad(1) + 1) )
        {
          _r.Selsin[num].null = _r.Selsin[num].null + ax ;
          //--- 14.04.2011 11:09 - добавлено, чтобы не заходить за 180 грд .
          if ( (sw)_r.Selsin[num].null < 0 )
          {
            if ( (w)(~_r.Selsin[num].null+1) > _Grad(180)) _r.Selsin[num].null += _Grad( 360 ) ;
          }
          else
          {
            if ( (w)_r.Selsin[num].null > _Grad(180))      _r.Selsin[num].null -= _Grad( 360 ) ;
          }
          //---
          // Введение смещения нуля.
          ax -= _r.Selsin[num].null ;
        }
      }
#endif

      //--------
      // Масштабирование сигнала в градусах для компенсации разбаланса поворота сельсина
      // приводит к тому , что сигнал в градусах буквально "сходит с ума" - т.е. сам себя изменяет .
      // Поэтому выполняем разнополярное масштабирование не здесь , а в конце - после масштабирование :

      // Введение порога в сигнал сельсина также приводит к неадекватному изменению сигнала
      // в градусах , поэтому делаем это после масштабирования в ZAD_SKOR.C :
      //--------

#ifndef  _AZIMUT
         //   Если интервал от сельсина до синхроимп. больше 180грд. то:
         if ( (sw)ax < 0 )
           {
             if ( (w)(~ax + 1) > _Grad( 180 ))  ax +=  _Grad( 360 ) ;
           }
         else
           {
             if ( (w)ax > _Grad( 180 ))         ax -=  _Grad( 360 ) ;
           }
#else    // Сельсин работает в режиме азимута : от 0 до 360 грд , а не как обычно от 0 до +-180 грд .
         // 21.11.07 22:08 - Для индикации азимута требуется от 0 до 360 грд :
         if ( (sw)ax < 0 )
          {
            //ax = ~ax + 1 ; // выпрямление .
            ax +=  _Grad( 360 ) ;
          }
#endif

      //--------
      //   Фильтрация: вычисление отклонения текущего измеренного задания
      lax = ((lw)p->out_g << 16) + (lw)p->drob ;

      ax  -= p->out_g ;
      lax += (slw)ax << ( 16 - *SelsDU[num].shift )  ;
      ax = (w)( lax >> 16 ) ;
      p->drob = (w)lax ;
        //--------
      p->out_g = ax ; // вывод в градусах после фильтрация и порога.

      ax = (slw)(sw)ax * (slw)(sw)_r.Selsin[num].masht >> 8  ;

      // Выполняем разнополярное масштабирование для компенсации разбаланса поворота сельсина :
      if      ( (sw)ax < 0 ) ax = (sw)( (slw)(sw)ax * (slw)(sw)*SelsDU[num].mashtM >> 8 ) ;
      else if ( (sw)ax > 0 ) ax = (sw)( (slw)(sw)ax * (slw)(sw)*SelsDU[num].mashtP >> 8 ) ;
      //------
      p->out_m = ax ;

    break;
  }
    //------
  return 1 ;
}


/*
        //  Введение порога в задание, чтобы можно было выставить
        // устойчивый нуль задания при неустойчивом нуле АЦП (смещение,
        // биение и т.д.). Перевалив через порог задание начинает расти
        // с нуля, а не скачком, т.е. порог - это постоянная составляющая
        // и в минус и в плюс.
    if ( (sw)ax < 0 )
      {
        if ( (w)(~ax + 1) <= _Sels_porog ) ax = 0x0  ;
        else                               ax += _Sels_porog  ;
      }
    else
      {
        if ( (w)ax <= _Sels_porog ) ax = 0x0  ;
        else                        ax -= _Sels_porog  ;
      }
      //   Фильтрация: вычисление отклонения текущего измеренного задания
      // от предыдущего отфильтрованного, деление этого отклонения сдвигом
      // на 'N' и прибавление его, вместе с получившейся после деления дробной
      // частью, к предыдущему значению задания, которое тоже имеет свою
      // дробную часть.
      //   Для задания на скорость будет взята только целая часть.
      // склеивание целой и дробной частей в "long".

      lax = ((lw)p->out << 16) + (lw)p->drob ;

      ax  -= p->out ;
      lax += (slw)ax << ( 16 - _Sels_shift )  ;

    p->out = (w)( lax >> 16 ) ;

       //   Периодическое обнуление дробной части отфильтрованного задания,
       // чтобы в ней не происходило накопления при малых и редких биениях АЦП.
       //   Если АЦП бьет на одну дискрету в 3-х случаях из 4-х и чаще, то до
       // обнуления дробной части единичка успеет переползти в целую часть, а
       // если бьет реже, то не успеет и обнулится. В результате только
       // "устойчивая" единица пройдет в целую часть.
    if ( ++p->time >= ( (w)1 << _Sels_shift ) * 3u/4u ) p->drob = 0x8000u , p->time = 0 ;
    else                                             p->drob = (w)lax ;
  */
