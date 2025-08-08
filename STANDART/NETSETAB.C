
//    ПРОГРАММА ИЗМЕНЕНИЯ УСТАВОК В РЕЖИМЕ МЕНЮ С ОТОБРАЖЕНИЕМ ПОСЛЕДНИХ
//  В ЕДИНИЦАХ НОМИНАЛЬНЫХ ЗНАЧЕНИЙ ДАННЫХ УСТАВОК.
//--------------------------------------------------------

/* Программа предлагает пользователю выбрать путем поочередного перебора из
 * таблицы параметр, значение которого его не устраивает и задать ему новое
 * значение.
 *   Функции:
 * - просмотр, путем перебора, таблично-заданного списка уставок и их текущих
 *   значений;
 * - изменение значения выбранной уставки.
 *   Клавиши:
 * - "+" в режиме просмотра/выбора уставок - просмотр уставок перебором вниз
 *   по списку;
 * - "-" в режиме просмотра/выбора уставок - просмотр уставок перебором вверх
 *   по списку;
 * - "Enter" в режиме просмотра/выбора уставок - выбор данной уставки, как
 *   предназначенной для изменения, и переход к режиму изменения ее значения;
 * - "Esc" в режиме просмотра/выбора уставок - возврат в диспетчер ;
 * - "+" в режиме изменения уставки - увеличение значения копии уставки,
 *   дискретно-плавно до установленного ее максимального значения ;
 * - "-" в режиме изменения уставки - уменьшение значения копии уставки,
 *   дискретно-плавно до установленного ее минимального значения ;
 * - "Enter" в режиме изменения уставки - запись полученного значения копии
 *   уставки в уставку и возврат в режим просмотра/выбора уставок;
 * - "Esc" в режиме изменения уставки - восстановление в копии уставки
 *   прежнего значения уставки и возврат в режим просмотра/выбора уставок.
 */

void NetSetab_Drive (char *numb, word kol)
{
  register  word    ax , bx , cx , ex ;
  byte  sig_old;
  static word Nu; //Пременная для определения номера элемента масива numb
  register  lword  lax ;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          output_s ( _NetSetab_prompt ) ;
          output_c ( '\n' ) ;

          m_index = 0;
          Label = 0 ;

          if ((kol ==1)||(NetNumUstav ==1) )
          {
            if ( kol ==1 )
            {
              m_index = numb[0] ;   // установка номера блока уставок на требуемый
              if ( NetUstav[m_index].kol_vo == 1 )
              {
                mSymbol_in_Buff_RXD( Enter ) ;
              }
            }
            output_c ( '\r' ) ;
            output_s ( NetUstav[m_index].gruppa ) ;

            mSymbol_in_Buff_RXD( Enter ) ;
          }
          else if (kol > 1  )
          {
              Nu = 0;
              m_index = numb[Nu] ;   // установка номера блока уставок на первый
          }
          if ( m_index > NetNumUstav ) goto out;

          return ;
        }
        //--------------------

  switch ( Label )
    {
      default:
      case 5:  //   Если вывод не поспевает за нажатиями клавиш
               // "больше/меньше", то производится обработка нескольких
               // нажатий за время одного вывода.
           //  Пропуск вывода, если не завершен предыдущий вывод, и
           // переход к обработке нажатий клавиш.
          if (  TestCompleted_Output() )
            {    /*  Вывод заданной строки меню. */
              if ( Label != 5 )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( NetUstav[m_index].gruppa ) ;
                  Label = 10 ;
                }
              else
                {
                  // Вывод значения ячейки соответствующей данной строке меню.
                  output_c ( '\r' ) ;
                  output_s( AWelcome );

                        // для 'word' все равно: со знаком или без.
                  if ( NetUstav[m_index].adr_Gruop[m_addr].code._.type == 2 )  ax = *(w*)NetUstav[m_index].adr_Gruop[m_addr].addr ;
                  else
                  {     // для 'byte' не все равно: со знаком или без.
                    ax = *(sb*)NetUstav[m_index].adr_Gruop[m_addr].addr ;
                    if ( NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение.
                  }
                  cx = *(w*)NetUstav[m_index].adr_Gruop[m_addr].abs_nom;
                  bx = NetUstav[m_index].adr_Gruop[m_addr].nom ;
                  if ( NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
                  {    // Если распечатка со знаком - выделяем знак и модуль.
                    if ( (sw)ax >= 0 )    sig_old = '+' ;
                    else   ax = ~ax + 1 , sig_old = '-' ;
                  }
                  /*if ( Ustav[m_index].adr_Gruop[m_addr].code._.type == 2 )  ax = *(w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  else                          ax = *(b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  cx = *(w*)Ustav[m_index].adr_Gruop[m_addr].abs_nom;
                  bx = Ustav[m_index].adr_Gruop[m_addr].nom ;
                  if ( (sw)ax >= 0 )    sig_old = '+' ;
                  else   ax = ~ax + 1 , sig_old = '-' ;*/

                    // приводим содержимое ячейки к его номиналам.
                       /* для отображения уставок типа '1/x' */
                   if (NetUstav[m_index].adr_Gruop[m_addr].code._.invert == 1 )
                   {  // меняем местами ax и bx для инверсного деления.
                     ex = ax , ax = bx, bx = ex ;
                   }
                   lax =  (lw)ax*(lw)cx;
                   m_time = lax%bx;
                   *(w*)&m_buff[0] = bx;
                   lax /=bx;
                   if(lax > 0xffffu) lax = 0xffff;
                   //lax &= 0xffff ;   // очищаем остаток.

                             // распечатка целой части - максимум 5 символов.
                      ex = 5 - NetUstav[m_index].adr_Gruop[m_addr].code._.celoe ; //сколько первых символов пропустить
                      if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                      else if ( (sw)ex < 0 ) ex = 0 ;
                      for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                      {
                        bx = lax / ax ;
                        lax %= ax;
                            // пока идут первые нули - не выводим их:
                        if ( bx == 0 && cx == 0 )
                        {     // а пропускаем лишние нулевые символы,
                          if ( ex != 0 ) ex-- ;
                             // или заменяем пробелами.
                          else  output_c (' ') ;
                        }
                        else
                        {
                          if(cx == 0)
                          {
                            if ((NetUstav[m_index].adr_Gruop[m_addr].code._.zapr == 1)&& (_Ne_Rabota == 0) ) output_c ( '#' ) ;
                            if ( (NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 0) ) output_c ( sig_old ) ;
                            cx = 1 ;
                          }
                           // первые нули закончились.
                          output_c ( (b)bx + 0x30 ) ;
                        }
                      }   // распечатываем последнюю цифру.
                      if(cx == 0)
                      {
                        if ((NetUstav[m_index].adr_Gruop[m_addr].code._.zapr == 1)&& (_Ne_Rabota == 0) ) output_c ( '#' ) ;
                        if ( (NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 0) ) output_c ( sig_old ) ;
                      }
                      //if ( (Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0) && (cx == 0) ) output_c ( sig_old ) ;
                      output_c ( (b)(w)lax + 0x30 ) ;
                     Label = 15 ;
                     break;

            case 15:    // распечатка дробной части
                      if ( NetUstav[m_index].adr_Gruop[m_addr].code._.celoe == 0 ) ex = 2 ;// по умолчанию.
                      else ex = NetUstav[m_index].adr_Gruop[m_addr].code._.drob ;
                      if ( ex != 0 )
                      {
                        output_c ( '.' ) ;
                        bx = *(w*)&m_buff[0] ;
                        lax = m_time ; // восстанавливаем остаток.
                        for ( ; ex != 0 ; ex-- )
                        {
                          lax*=10  ;
                          ax = lax/bx ;
                          lax %= bx;
                            output_c ( (b)ax + 0x30 ) ;
                        }
                      }
                      output_s ( NetUstav[m_index].adr_Gruop[m_addr].ch ) ;
                      if ((NetUstav[m_index].adr_Gruop[m_addr].code._.zapr == 1) && (_Ne_Rabota == 0) ) output_c ( '#' ) ;

                  Label = 20 ;// для режима изменения выбранной уставки
                }
              break ;
            }
          if ( Label != 5 ) // Режим выбора уставок.
            {
     case 10: while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
               out:   Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      if (  kol > 1  )
                      {
                        if (++Nu>= kol ) Nu = 0;
                        m_index = numb[Nu] ;
                        if ( m_index > NetNumUstav ) goto out;
                      }
                      else if ( ++m_index >= NetNumUstav ) m_index = 0 ;

                      Label = 0 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {

                      if ( kol > 1 )
                      {
                        if (Nu-- == 0 ) Nu = kol-1;
                        m_index = numb[Nu] ;
                        if ( m_index > NetNumUstav ) goto out;
                      }
                      else if ( m_index-- == 0 ) m_index = NetNumUstav - 1  ;
                      Label = 0 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      for(m_addr = 0; (NetUstav[m_index].adr_Gruop[m_addr].mask & _N_prog) == 0; m_addr++)
                      {
                        if ( m_addr == NetUstav[m_index].kol_vo-1 )
                        {
                          Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                          return ;
                        }

                      }
                      output_c ( '\n' ) ;
                      Label = 16 ;
                      return ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 0;
              }

              break ;
            //-------------------

     case 16: //output_c ( '\n' ) ;
              output_c ( '\r' ) ;
              output_s( AWelcome );
              output_s ( NetUstav[m_index].adr_Gruop[m_addr].text ) ;
              Label = 17 ;
              break;

     case 17:while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
      case 18:        if ( (kol == 1) || (NetNumUstav == 1) ) goto out;
                      output_s ( _NetSetab_prompt ) ;
                      output_c ( '\n' ) ;
                      Label = 0;
                      m_addr = 0;
                      break ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      do
                      {
                        if ( ++m_addr >= NetUstav[m_index].kol_vo ) m_addr = 0 ;
                      }
                      while ((NetUstav[m_index].adr_Gruop[m_addr].mask & _N_prog) == 0 );
                      Label = 16 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      do
                      {
                        if ( m_addr-- == 0 ) m_addr = NetUstav[m_index].kol_vo - 1 ;
                      }
                      while ((NetUstav[m_index].adr_Gruop[m_addr].mask & _N_prog) == 0 );
                      Label = 16 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      // Запоминание первоначального значения уставки.
                  if ( NetUstav[m_index].adr_Gruop[m_addr].code._.type == 2 )  m_ext = *(w*)NetUstav[m_index].adr_Gruop[m_addr].addr ;
                      else                          m_ext = *(b*)NetUstav[m_index].adr_Gruop[m_addr].addr ;
                      output_c ( '\n' ) ;
                      Label = 5 ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 16;
              }

              break ;
          }
        else   // Режим изменения выбранной уставки.
          {
     case 20: while (  TestData_for_Input() )
                {     // Считывание уставки для ее последующего изменения.
                        // для 'word' все равно: со знаком или без.
                  if ( NetUstav[m_index].adr_Gruop[m_addr].code._.type == 2 )  ax = *(w*)NetUstav[m_index].adr_Gruop[m_addr].addr ;
                  else                        //  ax = *(b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  {     // для 'byte' не все равно: со знаком или без.
                    ax = *(sb*)NetUstav[m_index].adr_Gruop[m_addr].addr ;
                    if ( NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение.
                  }
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      ax = m_ext ;  // Восстановление прежнего значения уставки.
                      output_s ( "\n\r" ) ;
                      output_s ( NetUstav[m_index].gruppa ) ;
                      output_c ( '\n' ) ;
                      if ( NetUstav[m_index].kol_vo == 1 )
                      {
                        Label  = 18;
                      }
                      else Label = 16 ;

                    }
                  else if ( m_ch == Enter ) // Записать копию уставки в память в уставку.
                    {
                      output_s ( "\n\r" ) ;
                      output_s ( NetUstav[m_index].gruppa ) ;
                      output_c ( '\n' ) ;
                      if ( NetUstav[m_index].kol_vo == 1 )
                      {
                        Label  = 18;
                      }
                      else Label = 16 ;       // Вернуться к перебору уставок.
                    }
                  else if ((NetUstav[m_index].adr_Gruop[m_addr].code._.zapr == 0)|| (_Ne_Rabota == 1) )
                  {
                    if ( m_ch == Up )   /* Увеличить грубо копию уставки.*/
                    {
                      if (NetUstav[m_index].adr_Gruop[m_addr].code._.invert == 1 ) goto down ;
                 up:  cx = ax ; // сохраняем предыдущее значение.
                      ax += NetUstav[m_index].adr_Gruop[m_addr].dX ;
                      bx  = NetUstav[m_index].adr_Gruop[m_addr].max ;
                       //  Если распечатка без знака то число рассматриваем
                      //  как беззнаковое в диапазоне 0...65535.
                      if ( NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
                      {    //  со знаком.
                           //  Защита на случай переваливания через max, если
                           // max задан 0xFFFF (для беззнаковых) или 0x7FFF
                           // (для знаковых), т.к. в этих случаях ограничение
                           // по обычному алгоритму не может работать.
                        if ( (sw)ax < (sw)cx ) ax = bx ; // если после сложения число
                           // стало меньше чем до, значит произошло переваливание.
                        if ( (sw)ax > (sw)bx ) ax = bx ;
                      }
                      else
                      {    // без знака.
                        if ( (w)ax < (w)cx ) ax = bx ; // если после сложения число
                           // стало меньше чем до, значит произошло переваливание.
                        if ( (w)ax > (w)bx ) ax = bx ;
                      }
                      Label = 5 ;
                    }
                    else if ( m_ch == Down ) /* Уменьшить грубо копию уставки.*/
                    {
                      if (NetUstav[m_index].adr_Gruop[m_addr].code._.invert == 1 ) goto up ;
                 down:cx = ax ; // сохраняем предыдущее значение.
                      ax -= NetUstav[m_index].adr_Gruop[m_addr].dX ;
                      bx  = NetUstav[m_index].adr_Gruop[m_addr].min ;
                      //if ( (sw)(ax -= Ustav[m_index].adr_Gruop[m_addr].dX ) < (sw)Ustav[m_index].adr_Gruop[m_addr].min ) ax = Ustav[m_index].adr_Gruop[m_addr].min ;
                      if ( NetUstav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
                      {    //  со знаком.
                           //  Защита на случай переваливания через min, если
                           // min задан 0x0000 (для беззнаковых) или 0x8000
                           // (для знаковых), т.к. в этих случаях ограничение
                           // по обычному алгоритму не может работать.
                        if ( (sw)ax > (sw)cx ) ax = bx ; // если после вычитания число
                           // стало больше чем до, значит произошло переваливание.
                        if ( (sw)ax < (sw)bx ) ax = bx ;
                      }
                      else
                      {    // без знака.
                        if ( (w)ax > (w)cx ) ax = bx ; // если после вычитания число
                           // стало больше чем до, значит произошло переваливание.
                        if ( (w)ax < (w)bx ) ax = bx ;
                      }
                      Label = 5 ;
                    }
                    else
                    {
                      Klav_Buff = m_ch;
                    }

                  }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                    // Выдача в уставку ее измененного или неизмененного значения.
                  if ( NetUstav[m_index].adr_Gruop[m_addr].code._.type == 2 )  *(w*)NetUstav[m_index].adr_Gruop[m_addr].addr = ax ;
                  else                          *(b*)NetUstav[m_index].adr_Gruop[m_addr].addr = ax ;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 5;
              }

              break ;
            //-------------------
          }
    }

 Restart_Output ()  ;

  return ;
}
/*---------------------------------*/



void NetSetabBit_Drive (char *numb, word kol)
{
  #define   index2   m_addr
  register word ax;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          index2 = 0;
            m_ext = 0;

            if ((kol == 0 ) || (kol > 1))
            {
              output_s ( _NetSetabBit_prompt ) ;
              output_c ( '\n' ) ;
              Label = 0 ;
              if ( kol > 1 )
              {
                m_index = numb[m_ext] ;   // установка номера блока уставок на первый
                if ( m_index > NetNumBUst ) goto bout;
              }
              else m_index = 0 ;   // установка номера блока уставок на первый
            }
            else
            {
              m_index = numb[0] ;   // установка номера блока уставок на требуемый
              output_c ( '\n' ) ;
              output_c ( '\r' ) ;
              if ( m_index >= NetNumBUst )
              {
                Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
              }
              output_s( AWelcome );
              output_s ( Netbts[m_index].text ) ;

              for(index2 = 0; (*Netbts[m_index].mask1 & Netbts[m_index].msk[index2]) == 0; ++index2)
              {
                  if ( index2 >= (w)Netbts[m_index].n )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      break;
                    }

              }

              Label = 5 ;
            }

          return ;
        }
        //--------------------

  switch ( Label )
    {
      default:
      case 0:
      case 5:  //   Если вывод не поспевает за нажатиями клавиш
               // "больше/меньше", то производится обработка нескольких
               // нажатий за время одного вывода.
           //  Пропуск вывода, если не завершен предыдущий вывод, и
           // переход к обработке нажатий клавиш.
          if (  TestCompleted_Output() )
            {    /*  Вывод заданной строки меню. */
              if ( Label != 5 )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( Netbts[m_index].text ) ;
                  Label = 10 ;
                }
              else
                {   // Вывод значения ячейки соответствующей данной строке меню.

                  if ( Netbts[m_index].code._.type == 1 )  ax = *(b*)Netbts[m_index].addr ;
                  else  ax = *(w*)Netbts[m_index].addr ;

                  //output_c ( '\n' ) ;
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( Netbts[m_index].bit[index2] ) ;
                  output_c ( '=' ) ;
                  if ( ( ax  & Netbts[m_index].msk[index2]) == 0 )
                           output_c ( '0' ) ;
                  else     output_c ( '1' ) ;

                  Label = 20 ;// для режима изменения выбранной уставки
                }
              break ;
            }
          if ( Label != 5 ) // Режим выбора уставок.
            {
     case 10: while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
               bout:  Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      if (  kol > 1  )
                      {
                        if (++m_ext>= kol ) m_ext = 0;
                        m_index = numb[m_ext] ;
                        if ( m_index > NetNumBUst ) goto bout;
                      }
                      else if ( ++m_index >= NetNumBUst ) m_index = 0 ;
                      Label = 0 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      if ( kol > 1 )
                      {
                        if (m_ext-- == 0 ) m_ext = kol-1;
                        m_index = numb[m_ext] ;
                        if ( m_index > NetNumBUst ) goto bout;
                      }
                      else if ( m_index-- == 0 ) m_index = NetNumBUst - 1  ;
                      Label = 0 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      for(index2 = 0; (*Netbts[m_index].mask1 & Netbts[m_index].msk[index2]) == 0; ++index2)
                      {
                          if ( index2 >= (w)Netbts[m_index].n )
                            {
                              Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                              return;
                            }

                      }
                      output_c ( '\n' ) ;
                      Label = 5 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 0;
              }

              break ;
            //-------------------
          }
        else   // Режим изменения выбранной уставки.
          {
     case 20: while (  TestData_for_Input() )
                {
                  if ( Netbts[m_index].code._.type == 1 )  ax = *(b*)Netbts[m_index].addr ;
                  else  ax = *(w*)Netbts[m_index].addr ;

                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  {
                     if ( kol == 1 ) goto bout;
                     else
                     {
                        output_s ( _NetSetabBit_prompt ) ;
                        output_c ( '\n' ) ;
                        Label = 0 ;
                     }

                  }
                  else if ( m_ch == Down ) /* Уменьшить грубо копию уставки.*/
                    {
                      do
                      {
                        if ( ++index2 >= (w)Netbts[m_index].n ) index2 = 0 ;
                      }
                      while ((*Netbts[m_index].mask1 & Netbts[m_index].msk[index2]) == 0 );

                      Label = 5 ;
                    }
                  else if ( m_ch == Up )   /* Увеличить грубо копию уставки.*/
                    {
                      do
                      {
                        if ( index2-- == 0 ) index2 = (w)Netbts[m_index].n-1 ;
                      }
                      while ((*Netbts[m_index].mask1 & Netbts[m_index].msk[index2]) == 0 );
                      Label = 5 ;
                    }
                  else if ( m_ch == Enter ) // Записать копию уставки в память в уставку.
                    {
                      ax ^= Netbts[m_index].msk[index2]  ;  // Инвертирование разряда уставки.
                      Label = 5 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                  if ( Netbts[m_index].code._.type == 1 ) *(b*)Netbts[m_index].addr = ax ;
                  else                                    *(w*)Netbts[m_index].addr = ax ;

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 5;
              }

              break ;
            //-------------------
          }
    }

 Restart_Output ()  ;

  return ;
}
