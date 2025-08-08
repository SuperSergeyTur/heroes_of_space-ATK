/*    Программа  "Задатчик Интенсивности Универсальный".
 *
 *   Программа использующая ЗИ должна при вызове ЗИ передать ему в качестве
 * параметра адрес своего блока данных для обработки ЗИ.
 *
 */

void Zad_Intens ( struct ZI *zip )
{
//    Т.к. эта функция вызывается как из фона так и
//  из прерываний то, по-скольку компилятор не позволяет описать функцию
//  как реентерабельную, для сохранения временных переменных в стеке их
//  следует описать как автоматические, а не как регистровые (т.к.
//  автоматические переменные компилятор распологает в стеке).
  /*register*/  lword lax ;
  /*register*/   word ax;

//  asm_push( lax   );  //  Сохраняем 'lax', чтобы эта функция могла вызываться
//  asm_push( lax+2 );  // из прерывания, прерывая себя же вызванную в фоне.

  ax = (w)( timer1 - zip->time ) / (w)_Sec( 1.0 ) ;
  zip->time = timer1 ;  // запись момента текущей отработки ЗИ.

  if ( (sw)zip->in != (sw)zip->out )
    {
      lax = (lw)zip->drob ;
      lax += (lw)zip->out << 16 ;
  //    ax = (w)( timer1 - zip->time ) / (w)_Sec( 1.0 ) ;

      if ( (sw)zip->in > (sw)zip->out )
        {
          lax += (lw)*zip->temp_p * (lw)ax ;
          zip->drob = (w) lax;
          zip->out  = (w) ( lax >> 16 ) ;
          if ( (sw)zip->out > (sw)zip->in ) zip->out = zip->in ;
        }
      else
       {
          lax -= (lw)*zip->temp_m * (lw)ax ;
          zip->drob = (w) lax;
          zip->out  = (w) ( lax >> 16 ) ;
          if ( (sw)zip->out < (sw)zip->in ) zip->out = zip->in ;
    }  }

  //zip->time = timer1 ;  // запись момента текущей отработки ЗИ.


//  asm_pop( lax+2 );
//  asm_pop( lax   );
  return ;
}

void Set_ZI ( struct ZI *zip , word ax )
{
  zip->in = ax ;
  zip->out = ax ;
  zip->drob = 0 ;
  zip->time = timer1 ;

  return ;
}
