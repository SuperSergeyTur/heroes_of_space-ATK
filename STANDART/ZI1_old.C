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

void Zad_Intens ( struct ZI *zip )
{
//    Т.к. эта функция вызывается как из фона так и
//  из прерываний то, по-скольку компилятор не позволяет описать функцию
//  как реентерабельную, для сохранения временных переменных в стеке их
//  следует описать как автоматические, а не как регистровые (т.к.
//  автоматические переменные компилятор распологает в стеке).
  /*register*/  lword lax ;
  /*register*/   word ax ;
  /*register*/   word bx;//26.01.06 13:59, cx ;
  /*register*/   byte lbl ;
  /*register*/   byte sign_lin ;

   //do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
   //tim <<= 8 ;       //  Из четырехбайтного полного значения времени
   //tim  += (bx>>8);  // для работы берутся средние два байта прини-
                     // мающие значения в диапазоне 0.25мсек-12.0сек.


//  asm_push( lax   );  //  Сохраняем 'lax', чтобы эта функция могла вызываться
//  asm_push( lax+2 );  // из прерывания, прерывая себя же вызванную в фоне.
  bx = timer1 ;               //_Sec(1.0)/2 для округления.
  ax = (w)( bx - zip->time + (w)_Sec( 1.0 )/2) / (w)_Sec( 1.0 ) ; // Вычисление dT.
  zip->time = bx ;  // запись момента текущей отработки ЗИ.

  if ( (sw)zip->in != (sw)zip->out_lin )
    {
     sign_lin = 0 ;
     // если вход и выход ЗИ положительны
     if ( (sw)zip->in >= 0 && (sw)zip->out_lin >= 0 )
       {

        // если вход больше выхода ЗИ используется темп разгона в "+".
        if ( (sw)zip->in > (sw)zip->out_lin )
          {
            bx = *zip->temp_p_razg ;
            lbl = 1 ;
          }

        // если вход меньше выхода ЗИ используется темп торможения в "+".
        else
          {
            bx = *zip->temp_p_torm ;
            lbl = 2 , sign_lin = 1 ;
          }
       }

     // иначе если вход и выход ЗИ отрицательны
     else if ( (sw)zip->in < 0 && (sw)zip->out_lin <= 0 )
       {

        // если вход меньше выхода ЗИ (по знаку) используется темп разгона в "-".
        if ( (sw)zip->in < (sw)zip->out_lin )
          {
            bx = *zip->temp_m_razg ;
            lbl = 2 , sign_lin = 1 ;
          }

       // если вход болше выхода ЗИ (по знаку) используется темп торможения в "-".
        else
          {
            bx = *zip->temp_m_torm ;
            lbl = 1 ;
           }
       }

     // если вход отрицательный а выход положительный
                          //  используется темп торможения в "+".
     else if ( (sw)zip->in < 0 && (sw)zip->out_lin > 0 )
          {
            bx = *zip->temp_p_torm ;
            lbl = 3 , sign_lin = 1 ;
          }

     // если вход положительный а выход отрицательный
                          //  используется темп торможения в "-".
     else if ( (sw)zip->in >= 0 && (sw)zip->out_lin < 0 )
          {
            bx = *zip->temp_m_torm ;
            lbl = 4 ;
          }

  //------- Рассчет интегратора N1 ( линейная часть ЗИ ) ---------------
     lax = zip->drob_lin ;
     lax += (lw)zip->out_lin << 16 ;
     if ( sign_lin == 1 ) lax -= (lw)bx * (lw)ax ;
     else                 lax += (lw)bx * (lw)ax ;
     zip->drob_lin = (w) lax ;
     zip->out_lin  = (w) ( lax >> 16 ) ;
  //--------------------------------------------------------------------

  //------------- Проверка конечных условий интегратора N1 -------------
     switch ( lbl )    //    out <?> in
       {
         case 1:       //   + < +,  - < -
                 if ( (sw)zip->out_lin > (sw)zip->in ) zip->out_lin = zip->in, zip->drob_lin = 0 ;
                  //26.01.06 13:59cx = zip->in - zip->out_lin ; // вычисляем дельту межде соседними загибами.
         break ;

         case 2:       //   + > +,  - > -
                 if ( (sw)zip->out_lin < (sw)zip->in ) zip->out_lin = zip->in, zip->drob_lin = 0 ;
                  //26.01.06 13:59cx = zip->in - zip->out_lin ;
         break ;

         case 3:       //   + != -
                       // если адрес уставки и ее значение не равны нулю ,
                      // выполняется параболический ЗИ .
                //26.01.06 14:00if ( *zip->temp_parabola == 0 || zip->temp_parabola == 0 )
                //26.01.06 14:00 {                              // выполняется параболический ЗИ .
                 if ( (sw)zip->out_lin < 0 ) zip->out_lin = 0, zip->drob_lin = 0 ;
                //26.01.06 14:00}
                /*26.01.06 14:03 else // оформляем парабол. переход через нуль.
                 {
                   if ( (sw)zip->out_lin <= 0 )
                   {
                     bx = 0 ;// даем ком."закругление" - спад интегр. N2 до нуля.
                         // держим разные знаки In и Out пока интегр. N2 не дошел до нуля.
                     if ( (sw)zip->out_2 != 0 ) zip->out_lin = +1 ;
                     else                      zip->out_lin =  0 ;
                   }
                 }
                  cx = zip->out_lin ;*/
         break ;

         case 4:       //   - != +
                //26.01.06 14:05if ( *zip->temp_parabola == 0 || zip->temp_parabola == 0 )
                //26.01.06 14:05 {                              // выполняется параболический ЗИ .
                 if ( (sw)zip->out_lin > 0 ) zip->out_lin = 0, zip->drob_lin = 0 ;
                //26.01.06 14:05 }
                 /*26.01.06 14:05 else // оформляем парабол. переход через нуль.
                 {
                   if ( (sw)zip->out_lin >= 0 )
                   {
                     bx = 0 ;// даем ком."закругление" - спад интегр. N2 до нуля.
                         // держим разные знаки In и Out пока интегр. N2 не дошел до нуля.
                     if ( (sw)zip->out_2 != 0 ) zip->out_lin = -1 ;
                     else                      zip->out_lin =  0 ;
                   }
                 }
                  cx = zip->out_lin ;*/
         break ;
       }
  //--------------------------------------------------------------------
    }



  //--------------------------------------------------------------------

    // В случае равенства задания (in) и линейного выхода (out_lin) на вход
    // второго интегратора должен подаваться нуль :
  else bx = 0 ;//26.01.06 14:07, cx = 0 ;

  //---               // сохраняем знак 'bx'
  if ( sign_lin == 1 )  zip->in_2 = ~bx + 1 ;  // если знак "-" , инвертируем bx .
  else                  zip->in_2 = bx ; // знаковый вход второго интегратора .

  //--------------------------------------------------------------------

         // если адрес уставки и ее значение не равны нулю ,
        // выполняется параболический ЗИ .
  if ( *zip->temp_parabola != 0 && zip->temp_parabola != 0 )
   {
  //------- Рассчет интегратора N2 -------------------------------------

     if ( (sw)zip->in_2 != (sw)zip->out_2 || zip->prz.all != 0 )
       {
        //---    Вычисл. мин.ограничения темпа при маленьких приращениях за входе
        //  'zi_in' , т.к. 'zi_out2' не успевает выйти на установившееся значение
        //  и 'zi_out' сильно не дотягивает: за время нарастания 'zi1', 'zi2'
        //  должен выйти на 'bx'.
        // cx = bx * |zip->in_2 - zip->out_2| / |zip->in - zip->lin| ;

        /*26.01.06 14:10 lax = (w)(zip->in_2 - zip->out_2) ;
        if ( (sw)lax < 0 ) lax = ~(w)lax+1 ;
          lax = (lw)(w)lax * (lw)bx ;
        //cx = zip->in - zip->out_lin ;
        if ( cx == 0 ) cx = 1 ;
        else if ( (sw)cx < 0 ) cx = ~cx+1 ;
          lax /= cx ;
        if ( lax > 0x7fffu ) zip->out_2 = zip->in_2 ;
        else
        {*/
        bx = *zip->temp_parabola ;
        bx = (w)( (lw)*zip->temp_p_razg * (lw)_fSec(1.00) / (lw)( bx * 2 ) ) ;  //2 - коэффициент закругленности параболы, при увеличении - закругленность увелич-ся.


        //----------------------------
        lax = zip->drob_2 ;
        lax += (lw)zip->out_2 << 16 ;

        //----- если в интервале линейного уч. изменится задание "zip->in_2" в противоположную сторону
        if ( ( zip->prz._.trg_pl  == 1 ) && (sw)zip->in_2 < 0 && (sw)zip->in < (sw)zip->out )  zip->prz._.trg_pl  = 0 , zip->prz._.trg_lin  = 0 ;
        if ( ( zip->prz._.trg_min == 1 ) && (sw)zip->in_2 > 0 && (sw)zip->in > (sw)zip->out )  zip->prz._.trg_min = 0 , zip->prz._.trg_lin  = 0 ;

        //if ( ( zip->prz._.trg_pl  == 1 || zip->prz._.trg_pl_end  == 1 ) && (sw)zip->in_2 < 0 && (sw)zip->in < (sw)zip->out )  zip->prz._.trg_pl  = 0 , zip->prz._.trg_lin  = 0 ; // если в интервале линейного уч. изменится задание "zip->in_2" в противоположную сторону
        //if ( ( zip->prz._.trg_min == 1 || zip->prz._.trg_min_end == 1 ) && (sw)zip->in_2 > 0 && (sw)zip->in > (sw)zip->out )  zip->prz._.trg_min = 0 , zip->prz._.trg_lin  = 0 ;

        //------ если в интервале параболы2 изменится полярность задания "zip->in_2" в противоположную сторону
        if ( ( zip->prz._.trg_min_end == 1 ) && (sw)zip->in_2 < 0 && (sw)zip->in < (sw)zip->out )   zip->prz._.trg_min_end = 0 ;
        if ( ( zip->prz._.trg_pl_end  == 1 ) && (sw)zip->in_2 > 0 && (sw)zip->in > (sw)zip->out )   zip->prz._.trg_pl_end  = 0 ;


       //------- если в интервале параболы2 возрастет задание "zip->in" выше  "zip->out_lin"
        if ( ( zip->prz._.trg_min_end == 1 ) && (sw)zip->in_2 > 0 && (sw)zip->in > (sw)(zip->out_lin + _Skor_nom( 0.01 )) )   zip->prz._.trg_min_end = 0  ;
        if ( ( zip->prz._.trg_pl_end  == 1 ) && (sw)zip->in_2 < 0 && (sw)zip->in < (sw)(zip->out_lin - _Skor_nom( 0.01 )) )   zip->prz._.trg_pl_end  = 0  ;


         // если вход больше выхода :
        if ( (sw)zip->in_2 > (sw)zip->out_2 || zip->prz._.trg_pl == 1 || zip->prz._.trg_pl_end == 1 )
         {
          if ( zip->prz._.trg_min == 1 || zip->prz._.trg_min_end == 1 ) goto _min ;

          if (zip->prz._.trg_pl_end == 0 )  // если нет цикла второй парболы
           {

            if ( ( zip->prz._.trg_pl == 0 ) ) // если триггер в "плюс" не установлен
              {
                if ( zip->in_2 != 0 )   // и "zi.in_2 != 0"
                  {
                    zip->time_s = Timer1_fSec ; // фиксация времени для интервала параболы
                    zip->prz._.trg_pl = 1 ;
                    zip->in2_copy =  zip->in_2 ; // сохранение копии "zip->in_2"
                    zip->outl_copy = zip->out ; // zip->outl_copy = zip->out_lin ;
                  }
              }
            else
              {
                zip->in_2 = zip->in2_copy ;
                    // если на участке параболы осталось всего лишь половина пройденного пути (если дали малое задание)
                  if ( (sw)( zip->out - zip->outl_copy ) > (sw)( zip->in - zip->out ) && zip->prz._.trg_lin == 0 )
                    {
                      goto _n1 ;  // минуем линейный участок
                    }
              }



            if ( (u)((w)(Timer1_fSec - zip->time_s)) > (w)*zip->temp_parabola  &&  zip->prz._.trg_lin == 0 )  // интервал параболы завешен
              {
                zip->prz._.trg_lin = 1 ; // начался линейный участок
                zip->out2_copy  = zip->out_2 ;  // копия "out_2" для интегрирования в минус

                zip->out_2 = zip->in2_copy  ;   // в "out_2" заносится копия "in2" для интервала линейного интегрирования
                lax = zip->drob_2 ;
                lax += (lw)zip->out_2 << 16 ;

                zip->outl_copy -= zip->out  ;  // в переменную "outl_copy" добавляем текущее значение "zip->out"
              }


            if (  zip->prz._.trg_lin == 1  ) // линейный участок
              {          // расчет точки для старта интервала парболы в "минус"
                zip->start_m = zip->in + zip->outl_copy ; // (перерасчет производится во время всего линейного участка т.к. "zip->in" может меняться)

                if ( (sw)zip->out >= (sw)zip->start_m )  // закончился интервал линейного интегрирования
                  {
                    zip->out_2 = zip->out2_copy ;  // в "out_2" заносится копия "in2" для интервала линейного интегрирования
                    lax = zip->drob_2 ;
                    lax += (lw)zip->out_2 << 16 ;
                _n1:
                    zip->prz._.trg_lin  = 0 ;
                    zip->prz._.trg_pl   = 0 ;
                    zip->prz._.trg_min_end  = 1 ;

                    zip->start_m = zip->in ; // сохраняем копию "zip->in" для определения изменения "zip->in" на интервале парболы в "минус"

                    goto _min ;
                  }
              }
           }
         else
           {
              // если уменьшилось задание "zip->in" то сбрасаваем "prz._.trg_pl_end"
              if ( zip->in != zip->start_p && (sw)zip->in_2 < 0 )
                {

                  if ( (sw)( zip->out_lin - zip->in ) > (sw)( zip->out - zip->out_lin ) )
                    {
                      zip->prz._.trg_pl_end = 0 ;
                      zip->out_2 = 0 ;
                    }
                }
              zip->in_2 = 0 ;

              // если итегратор out_2 дошел до "0", а триггер "trg_pl_end == 1" то принудительно сбрасываем trg_pl_end, иначе zi_out зависало
              if ( zip->out_2 == 0 )   zip->prz._.trg_pl_end = 0 /*, zip->out_lin = 0 */;
           }

           //------------------------------------

           lax +=  (lw)bx * (lw)ax ; // * (lw)zip->K / (lw)256 ;
           zip->drob_2 = (w) lax ;
           zip->out_2  = (w) ( lax >> 16 ) ;
           if ( (sw)zip->out_2 > (sw)zip->in_2 ) zip->out_2 = zip->in_2, zip->drob_2 = 0 ;
         }
        else // если вход меньше выхода :
         {
           _min:

          if ( zip->prz._.trg_min_end == 0 )
           {
            if ( ( zip->prz._.trg_min == 0 ) ) // если триггер в "минус" не установлен
              {
               if ( zip->in_2 != 0 )    // и "zi.in_2 != 0"
                 {
                    zip->time_s = Timer1_fSec ; // фиксация времени для интервала параболы
                    zip->prz._.trg_min = 1 ;
                    zip->in2_copy  =  zip->in_2 ; //
                    zip->outl_copy = zip->out ; // zip->outl_copy = zip->out_lin ;
                 }
              }
            else
              {
                zip->in_2 = zip->in2_copy ;

                  if ( (sw)( zip->out - zip->outl_copy ) < (sw)( zip->in - zip->out ) && zip->prz._.trg_lin == 0 )
                    {
                      goto _n2 ;
                    }
              }

           //------------------------------------

            if ( (u)((w)(Timer1_fSec - zip->time_s)) > (w)*zip->temp_parabola && zip->prz._.trg_lin == 0 )  // интервал параболы завешен
              {
                zip->prz._.trg_lin = 1 ; // начался линейный участок
                zip->out2_copy  = zip->out_2 ;  // копия "out_2" для интегрирования в минус

                zip->out_2 = zip->in2_copy  ;   // в "out_2" заносится копия "in2" для интервала линейного интегрирования
                lax = zip->drob_2 ;
                lax += (lw)zip->out_2 << 16 ;

                zip->outl_copy -= zip->out  ;
                //zip->start_p = zip->in -  zip->out + zip->outl_copy ; // расчет точки для старта интервала парболы в "плюс"
              }

           //------------------------------------


            if ( ( zip->prz._.trg_lin == 1 )  )      //  интервал линейного интегрирования
              {
               zip->start_p = zip->in + zip->outl_copy ; // расчет точки для старта интервала парболы в "плюс"

               if ( (sw)zip->out <= (sw)zip->start_p )   // закончился интервал линейного интегрирования
                 {
                   zip->out_2 = zip->out2_copy ;
                   lax = zip->drob_2 ;
                   lax += (lw)zip->out_2 << 16 ;
               _n2:
                   zip->prz._.trg_lin  = 0 ;
                   zip->prz._.trg_min  = 0 ;
                   zip->prz._.trg_pl_end = 1 ;

                   zip->start_p = zip->in ; // сохраняем копию "zip->in" для определения изменения "zip->in" на интервале парболы в "плюс"
                 }
              }
           }
         else
           {
              // если увеличилось задание "zip->in" то сбрасаваем "prz._.trg_min_end"
              if ( zip->in != zip->start_m && (sw)zip->in_2 > 0 )
                {
                  if ( (sw)( zip->in - zip->out_lin ) > (sw)( zip->out_lin - zip->out ) )
                    {
                      zip->prz._.trg_min_end = 0 ;
                      zip->out_2 = 0 ;
                    }
                }
              zip->in_2 = 0 ;

              // если итегратор out_2 дошел до "0", а триггер "trg_pl_end == 1" то принудительно сбрасываем trg_pl_end
              if ( zip->out_2 == 0 )   zip->prz._.trg_min_end = 0 /*, zip->out_lin = 0*/  ;
           }


           lax -=  (lw)bx * (lw)ax ; // * (lw)zip->K / (lw)256 ;
           //lax -= ( (lw)bx * (lw)ax * zip->K >> 8 );
           zip->drob_2 = (w) lax ;
           zip->out_2  = (w) ( lax >> 16 ) ;
           if ( (sw)zip->out_2 < (sw)zip->in_2 ) zip->out_2 = zip->in_2, zip->drob_2 = 0 ;
         }
       }//26.01.06 14:11}

    // когда вход ЗИ равен выходу - почему-то in2 = out2 = +-temp;
    if ( zip->in == zip->out ) zip->prz.all = 0 , zip->in_2 = zip->out_2 = 0 ;


  //--------------------------------------------------------------------

       //   Если команда (т.е. смена знака zip->in2) на отработку нового
       // задания (zip->in) пришла до того, как отработалось старое задание
       // и выход второго интегратора (zip->out_2) все еще выполняет старое
       // задание --> принудительно обнуляем (zip->out_2) , чтоб он интегрил
       // новое задание .

     if ( (sw)zip->in_2 < 0 && (sw)zip->out_2 > 0 )
       {
         if ( (sw)zip->in < (sw)zip->out )    zip->out_2 = 0 ;
       }
     if ( (sw)zip->in_2 > 0 && (sw)zip->out_2 < 0 )
       {
         if ( (sw)zip->in > (sw)zip->out )    zip->out_2 = 0 ;
       }
  //--------------------------------------------------------------------


     lax = zip->drob ;
     lax += (lw)zip->out << 16 ;

     bx = zip->out_2 ;

     if ( (sw)zip->in < (sw)zip->out && (sw)bx > 0 )   bx = 0 ;
     if ( (sw)zip->in > (sw)zip->out && (sw)bx < 0 )   bx = 0 ;

     if ( bx == 0 )
     {    // дотяжка.
        if ( (sw)zip->out > (sw)zip->in ) bx = -1 ;
        else if ( (sw)zip->out < (sw)zip->in ) bx = +1 ;
     }
       // Если задание на интегратор bx = 0 (zip->out_2), интегратор не работает
     if ( (sw)bx > 0 ) // Если задание положительное :
      {
        lax += (lw)bx * (lw)ax ;
        zip->drob = (w) lax ;
        zip->out  = (w) ( lax >> 16 ) ;
          // Срезаем выход ЗИ , если он наинтегрировался больше входа:
        if ( (sw)zip->out > (sw)zip->in ) zip->out = zip->in, zip->drob = 0 ;
      }
     if ( (sw)bx < 0 ) // Если задание отрицательное :
      {
        bx = ~bx + 1 ;
        lax -= (lw)bx * (lw)ax ;
        zip->drob = (w) lax ;
        zip->out  = (w) ( lax >> 16 ) ;
          // Срезаем макс.отриц. выход ЗИ, если он наинтегрировался больше входа:
        if ( (sw)zip->out < (sw)zip->in ) zip->out = zip->in, zip->drob = 0 ;
      }
  //--------------------------------------------------------------------
   }
    // если адрес уставки равен нулю , выполняется только линейный ЗИ :
  else zip->out = zip->out_lin ; // Выходу ЗИ присваеваем выход линейного ЗИ .

  //--------------------------------------------------------------------

//  asm_pop( lax+2 );
//  asm_pop( lax   );
  return ;
}
  //--------------------------------------------------------------------


  // ---------- Программа записи в переменные ЗИ значения ах -----------
  // ------ ( запись КОНЕЧНЫХ ЗНАЧЕНИЙ без переходных процессов ) ------

void Set_ZI ( struct ZI *zip , word ax )
{
  zip->in = ax ;
  zip->in_2 = 0 ;

  zip->out_lin = ax ;
  zip->out_2 = 0 ;
  zip->out = ax ;

  zip->drob_lin = 0 ;
  zip->drob_2 = 0 ;
  zip->drob = 0 ;

  zip->prz.all = 0 ;

  zip->time = timer1 ;

  return ;
}

  //--------------------------------------------------------------------

