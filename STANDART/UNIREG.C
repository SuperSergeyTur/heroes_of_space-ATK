
//   Регулятор.

void  UniReg ( Reg_Str *rptr  )
  {
    register word ax, bx ;
    register lword lax ;

    if (rptr->cfg._.enable == 0 )
    {
      rptr->integr = 0;
      rptr->integr_drob = 0;
      //rptr->out = 0;
      return ;
    }

//-------------------

           // Проверка заданий на ограничения и установка флагов
          //       для внешнего регулятора.
    rptr->b._.ltd_z_max = 0,  rptr->b._.ltd_z_min = 0 ;
    ax = *rptr->zad ;
    if      ( (sw)ax > (sw)(*rptr->zad_max))
      {
        ax = (*rptr->zad_max) ;
        rptr->b._.ltd_z_max = 1 ;
      }
    else if ( (sw)ax < (sw)(*rptr->zad_min))
      {
        ax = (*rptr->zad_min) ;
        rptr->b._.ltd_z_min = 1 ;
      }
//-------------------

        // Задатчик Интенсивности

    rptr->zi.in = ax ;
    Zad_Intens ( &(rptr->zi) ) ;
    ax = rptr->zi.out + rptr->add_zi ;
           // проверка ограничений по ЗИ (для внешнего регулятора).
    rptr->b._.ltd_zi_max = 0,  rptr->b._.ltd_zi_min = 0 ;
    bx = rptr->zi.in ;
    if ( bx != ax )  // если есть торможение задания по ЗИ:
    {
      if ( (sw)bx >= 0 )  // торможение в положительной зоне:
      {
        if ( (sw)bx > (sw)ax ) rptr->b._.ltd_zi_max = 1 ;  // на возрастание.
        else                   rptr->b._.ltd_zi_min = 1 ;  // на уменьшение.
      }
      else                // торможение в отрицательной зоне:
      {
        if ( (sw)bx < (sw)ax ) rptr->b._.ltd_zi_max = 1 ;// на возрастание по модулю.
        else                   rptr->b._.ltd_zi_min = 1 ;// на уменьшение по модулю.
      }
    }
//-------------------
    if      ( (sw)ax > (sw)(*rptr->zad_max))
      {
        ax = (*rptr->zad_max) ;
        rptr->b._.ltd_z_max = 1 ;
      }
    else if (rptr->cfg._.positiv_in == 1)
    {
      if ( (sw)ax < 0)
      {
        ax = 0 ;
        rptr->b._.ltd_z_min = 1 ;
      }
    }
    else  if( (sw)ax < (sw)(*rptr->zad_min))
      {
        ax = (*rptr->zad_min) ;
        rptr->b._.ltd_z_min = 1 ;
      }
        //  Вычисление отклонения от задания в каждой из фаз.
       // Определяем заданный тип вычисления ошибки:
       // 0 - отрицательная обратная связь;
       // 1 - положительная обратная связь.
    if ( rptr->cfg._.positiv_oc == 0 )  ax = ax - *rptr->oc ;
    else                                ax = *rptr->oc - ax ;
//ДДДДДДДДДДД Расчет интегратора.  ДДДДДДДДДДДДДД

//   Проверка ограничений на возрастание или снижение интегратора.

      if ( (sw)ax >= 0 )
      {
        //if ( rptr->b._.ltd_z_max == 1 )  goto v4 ;
        if ( rptr->b._.ltd_int_p == 1 )  goto v4 ;
      }
    else
      {
        //if ( rptr->b._.ltd_z_min == 1 )  goto v4 ;
        if ( rptr->b._.ltd_int_m == 1 )  goto v4 ;
      }

    bx = (*rptr->ki) & 0x7fff;  //защита от "-" коэфф.

    lax = (slw)(sw)bx * (slw)(sw)ax ;

        //  Подготовка к контролю переполнения (без использ.'asm'):
       // если до сложения/вычитания операнды были одного знака, а результат
       // получился другого знака - значит произошло переполнения.
    bx = 2 ;
    if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
    {
         if( (sw)rptr->integr >= 0 ) bx = 0 ; // +/+
    }
    else if( (sw)rptr->integr <  0 ) bx = 1 ; // -/-

    lax += (slw)(sw)rptr->integr << 8 ;
    lax += (lw)(w)rptr->integr_drob ;   // DROB IS'NT SIGNED !
              /* Проверка переполнений. */
                  //  переполнение в плюс?
          if     ( bx == 0 && (slw)lax <  0 ) goto v3 ;
                  //  переполнение в минус?
          else if( bx == 1 && (slw)lax >= 0 ) goto v2 ;
                  //  нет переполнения.

              /* Проверка ограничений. */

          if ( (slw)lax < (slw)(sw)rptr->lim_min<<8  )
            {
    v2:       lax = (slw)(sw)rptr->lim_min<<8 ;
            }
          else if ( (slw)lax >= (slw)(sw)rptr->lim_max<<8 )
            {
    v3:       lax = (slw)(sw)rptr->lim_max<<8 ;
            }

          rptr->integr = (slw)lax >> 8;
          rptr->integr_drob = lax;
    v4:   rptr->b._.ltd_int_p = 0 , rptr->b._.ltd_int_m = 0 ;

//ДДДДДД  Расчет пропорциональной составляющей и выхода регулятора. ДДДДДД

    bx = (*rptr->kp) & 0x7fff;  //защита от "-" коэфф.

    lax = (slw)(sw)bx * (slw)(sw)ax ;

    if ( (rptr->cfg._.pos_out == 1) && ((slw)lax < 0) ) lax = 0;

        //  Подготовка к контролю переполнения (без использ.'asm'):
       // если до сложения/вычитания операнды были одного знака, а результат
       // получился другого знака - значит произошло переполнения.
    bx = 2 ;
    if ( (slw)lax >= 0 ) // запоминаем сочетание знаков операндов.
    {
         if( (sw)rptr->integr >= 0 ) bx = 0 ; // +/+
    }
    else if( (sw)rptr->integr <  0 ) bx = 1 ; // -/-

    lax += (slw)(sw)rptr->integr<<8 ;

              /* Проверка переполнений. */
                  //  переполнение в плюс?
          if     ( bx == 0 && (slw)lax <  0 ) goto p3 ;
                  //  переполнение в минус?
          else if( bx == 1 && (slw)lax >= 0 ) goto p2 ;
                  //  нет переполнения.

              /* Проверка ограничений. */
          if ( (slw)lax < (slw)rptr->lim_min<<8 )
            {
    p2:       rptr->out = (sw)rptr->lim_min , rptr->b._.ltd_int_m = 1 ;
            }
          else if ( (slw)lax >= (slw)rptr->lim_max<<8 )
            {
    p3:       rptr->out = (sw)rptr->lim_max , rptr->b._.ltd_int_p = 1 ;
            }
          else rptr->out = (w)((slw)lax>>8) ;

    //   Выходная часть: т.к. регулятор универсальный, то перекладывать
    //  задание в нужное место должен какой-то внешний согласователь.

  return ;
}

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
