
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

void SetabDrive (char *numb, word kol)
{
  register  word    ax , bx , cx , ex , t_ax = 0 ;
  byte  all_sig;
  static word Nu; //Пременная для определения номера элемента масива numb
  static byte tst_output ;
  register lword  lax, lbx ;
  double   dax, dbx ;

  enum { k0, k01, k3, k10, k101, k12, k18, k20, k201, k21, k22, k30, k31, k32, k33, k34 } ;


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;

          if ( Mon.Password_Ok == 0 )  Label = k32 ;  // Вход с предупреждением о пароле.
          else                         Label = k34 ;  // Обычный вход.

          return ;
        }
        //--------------------

  switch ( Label )
    {
      default:
      case k32:  //  Контроль пароля: ограничение.
              output_s ( _PasswordLtd_txt ) ;
              m_time = Timer1_Ovr ;
              Label = k33 ;
      case k33:
              if ( (u)(w)(Timer1_Ovr - m_time) < _Time_Password_txt )  break   ;
               //---

      case k34:  //  Обычный вход.

          output_s ( _Setab_prompt ) ;
          output_c ( '\n' ) ;

          m_index = 0;
          Label = k0 ;

          if ((kol ==1)||(_MaxNumUstav ==1) )
          {
            if ( kol ==1 )
            {
              m_index = numb[0] ;   // установка номера блока уставок на требуемый
              if ( Ustav[m_index].kol_vo == 1 )
              {
                mSymbol_in_Buff_RXD( Enter ) ;
              }
            }
            output_c ( '\r' ) ;
            output_s ( Ustav[m_index].gruppa ) ;

            mSymbol_in_Buff_RXD( Enter ) ;
          }
          else if (kol > 1  )
          {
              Nu = 0;
              m_index = numb[Nu] ;   // установка номера блока уставок на первый
          }
          if ( m_index > _MaxNumUstav ) goto out;

          return ;
          //-------


      case k0:  //   Выбор группы.
            if( TestCompleted_Output() )
               {
      case k01:

                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( Ustav[m_index].gruppa ) ;
                  tst_output = 0 ;     //если, при нажатии, не успеваем вывести последнее значение, то
               }                       // взводим тригер, чтобы повторить вывод после отпускаения клавиши изменения
               else  tst_output = 1 ;

                  Label = k3 ;
              break ;
                 //---
                 //  Изменение  группы
      case k3:
              while (  TestData_for_Input() )
                {
          #ifdef _INTERPRETER
                if    ( Str_quant.SetPoint == 0 ) t_ax=_MaxNumUstav-1 ;
                else                              t_ax=_MaxNumUstav ;
          #else
                t_ax = _MaxNumUstav;
          #endif

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
                        if ( m_index > t_ax ) goto out;
                      }
                      else if ( ++m_index >= t_ax ) m_index = 0 ;

                      Label = k0 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {

                      if ( kol > 1 )
                      {
                        if (Nu-- == 0 ) Nu = kol-1;
                        m_index = numb[Nu] ;
                        if ( m_index > t_ax ) goto out;
                      }
                      else if ( m_index-- == 0 ) m_index = t_ax - 1  ;
                      Label = k0 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      for(m_addr = 0; (Ustav[m_index].adr_Gruop[m_addr].mask & _N_prog) == 0; m_addr++)
                      {
                        if ( m_addr == Ustav[m_index].kol_vo-1 )
                        {
                          Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                          return ;
                        }

                      }
                      output_c ( '\n' ) ;
                      Label = k101 ;
                      return ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }

              if ( tst_output == 1 )  Label = k0 ;

              if ( AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = k0;
              }

              break ;


      case k10:  //   Выбор уставки в группе.
            if( TestCompleted_Output() )
            {
      case k101:

              output_c ( '\r' ) ;
              output_s( AWelcome );
              output_s ( Ustav[m_index].adr_Gruop[m_addr].text ) ;
                tst_output = 0 ;     //если, при нажатии, не успеваем вывести последнее значение, то
             }                       // взводим тригер, чтобы повторить вывод после отпускаения клавиши изменения
             else  tst_output = 1 ;

              Label = k12 ;
              break;

     case k12:while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
      case k18:       if ( (kol == 1) || (t_ax == 1) ) goto out;
                      output_s ( _Setab_prompt ) ;
                      output_c ( '\n' ) ;
                      Label = k0;
                      m_addr = 0;
                      break ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      do
                      {
                        if ( ++m_addr >= Ustav[m_index].kol_vo ) m_addr = 0 ;
                      }
                      while ((Ustav[m_index].adr_Gruop[m_addr].mask & _N_prog) == 0 );
                      Label = k10 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      do
                      {
                        if ( m_addr-- == 0 ) m_addr = Ustav[m_index].kol_vo - 1 ;
                      }
                      while ((Ustav[m_index].adr_Gruop[m_addr].mask & _N_prog) == 0 );
                      Label = k10 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      // Запоминание первоначального значения уставки.
                  ax = Ustav[m_index].adr_Gruop[m_addr].code._.type  ;
 // неправильно считает
//            #ifdef  _INTERPRETER
                  if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 || ax == 0 )
                  {
                    if      ( ax == 1 ) m_dbx =      (d)*( sb*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 2 ) m_dbx =      (d)*( sw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 3 ) m_dbx =      (d)*(  f*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 4 ) m_dbx =      (d)*(slw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 0 ) m_dbx =          *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  }
                  else
                  {
                    if      ( ax == 1 ) m_dbx =      (d)*(  b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 2 ) m_dbx =      (d)*(  w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 3 ) m_dbx =      (d)*(  f*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 4 ) m_dbx =      (d)*( lw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 0 ) m_dbx =          *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  }
/*            #else
                  if ( ax == 2 )        m_ext =            *(w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  else                  m_ext =            *(b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
            #endif*/
                      output_c ( '\n' ) ;
                      Label = k201 ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
              if ( tst_output == 1 )  Label = k10 ;

              if ( AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = k10;
              }

              break ;
                 //---

      case k20:  //   Отображение значения уставки.
            if( TestCompleted_Output() )
               {
      case k201:  //   Отображение значения уставки.
                  // Вывод значения ячейки соответствующей данной строке меню.
                  output_c ( '\r' ) ;
                  output_s( AWelcome );

                        // для 'word' все равно: со знаком или без.
               /* if ( Ustav[m_index].adr_Gruop[m_addr].code._.type == 2 )  ax = *(w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  else
                  {     // для 'byte' не все равно: со знаком или без.
                    ax = *(sb*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение.
                  }
               */
                  ax = Ustav[m_index].adr_Gruop[m_addr].code._.type  ;
                  if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 || ax == 0 )
                  {
                    if      ( ax == 1 ) lbx = (slw)(sw)*( sb*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 2 ) lbx = (slw)    *( sw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 3 ) dax =      ( d)*(  f*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 4 ) lbx =          *(slw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 0 ) dax =          *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  }
                  else
                  {
                    if      ( ax == 1 ) lbx = ( lw)( w)*(  b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 2 ) lbx = ( lw)    *(  w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 3 ) dax =      ( d)*(  f*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 4 ) lbx =          *( lw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 0 ) dax =          *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  }

                         // распечатка в <double> виде.
                if ( (ax == 0)||(ax == 3) )
                {
                      bx = Ustav[m_index].adr_Gruop[m_addr].nom  ;
                      cx = *(w*)Ustav[m_index].adr_Gruop[m_addr].abs_nom  ;
                      //if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
                      {
                        if (  dax >= 0 )  all_sig = '+' ;
                        else  dax *= -1., all_sig = '-' ;
                      }
                       dbx = dax * (d)cx ;
                       dax = dbx / (d)bx ;
                       if ( dax > (d)(lw)0xffffffff )  dax = (lw)0xffffffff ;    // В отличие от алгоритма для целочисленных переменных
                       lax = (lw)dax ;                                               //  здесь сохраняем не остаток, а уже готовую `double`-дробную часть.
                       m_dax  = dax - (d)lax  ;  //сохраняем дробную часть.

                                  // распечатка целой части - максимум  10 символов.
                            //  4-х байтных начинаем с разных делителей, чтобы сократить итерации.
                      lbx = 1000000000ul, ax = 10 ;
                      ex = ax - Ustav[m_index].adr_Gruop[m_addr].code._.celoe ; //сколько первых символов пропустить
                      if ( (sw)ex < 0 ) ex = 0 ;


                      for ( cx = 0 ; lbx != 1 ; lbx /= 10 )
                          {

                            bx   = lax/lbx  ;
                            lax %= lbx ;
                                // пока идут первые нули - не выводим их:
                            if ( bx == 0 && cx == 0 )
                            {     //   пропускаем лишние нулевые символы,
                              if ( ex != 0 ) ex-- ;
                                  // или заменяем пробелами.
                              else  output_c (' ') ;
                            }
                            else
                            {
                              if ((cx == 0) && ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )  ) output_c ( all_sig ) ;
                              cx = 1 ; // первые нули закончились.
                              output_c ( (b)bx + 0x30 ) ;
                            }
                          }

                          if ((cx == 0) && ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )  ) output_c ( all_sig ) ;
                          // распечатываем последнюю цифру.
                          output_c ( (b)(w)lax + 0x30 ) ;
                          Label = k21 ;
                          return;

      case k21:    // распечатка дробной части  для double

                       ex = Ustav[m_index].adr_Gruop[m_addr].code._.drob ;
                          if ( ex != 0 )
                            {
                              output_c ( '.' ) ;

                              for ( ; ex != 0 ; ex-- )
                              {
                                m_dax *= 10 ;
                                ax = (w)m_dax  ;     //выделение целой части дроби
                                output_c ( (b)(w)ax + 0x30 ) ;
                                m_dax -= (d)ax ;    //сдвиг дроби

                              }
                            }

                }
                         // распечатка в <lword, word и byte> виде.
                else
                {

                  bx = Ustav[m_index].adr_Gruop[m_addr].nom ;
                  cx = *(w*)Ustav[m_index].adr_Gruop[m_addr].abs_nom;
                  if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
                  {    // Если распечатка со знаком - выделяем знак и модуль.
                    if ( (slw)lbx >= 0)     all_sig = '+' ;
                    else   lbx = ~lbx + 1 , all_sig = '-' ;
                  }

                  // приводим содержимое ячейки к его номиналам.
                  /* для отображения уставок типа '1/x' */
                  if (Ustav[m_index].adr_Gruop[m_addr].code._.invert == 1 )
                   {  // меняем местами ax и bx для инверсного деления.
                     ex = ax , ax = bx, bx = ex ;
                   }

                  if ( ax != 4 )  // для word byte: преобразование целочисленное
                     {
                       lax =  (lw)lbx * (lw)cx ;
                       m_time = lax%bx ;     //сохраняем остаток.
                       *(w*)&m_buff[0] = bx;
                       lax /= bx;
                       if(lax > 0xffffu) lax = 0xffff;
                       //lax &= 0xffff ;   // очищаем остаток.
                     }
                  else   // для lword: преобразование double чтобы избежать переполнения при первом умножении
                     {
                       dax = (d)lbx * (d)cx ;

                       dbx = dax / (d)bx ;     //   Контроль переполнения.
                       if ( dbx > (d)(lw)0xffffffff )  dbx = (lw)0xffffffff,  dax = (d)bx * dbx ;

                       lax = dbx ;
                       m_time  = dax - (d)lax * (d)bx ;    //сохраняем остаток.
                       *(w*)&m_buff[0] = bx ;
                     }
                                  // распечатка целой части - максимум 5 или 10 символов.
                            //  для 2-х и 4-х байтных начинаем с разных делителей, чтобы сократить итерации.
                      if ( ax != 4 )  lbx =      10000ul, ax =  5 ;
                      else            lbx = 1000000000ul, ax = 10 ;
                      ex = ax - Ustav[m_index].adr_Gruop[m_addr].code._.celoe ; //сколько первых символов пропустить
                      if ( ex == ax ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                      else if ( (sw)ex < 0 ) ex = 0 ;

                      for ( cx = 0 ; lbx != 1 ; lbx /= 10 )
                      {
                      bx = lax / lbx ;
                      lax %= lbx;
                      // пока идут первые нули - не выводим их:
                      if ( bx == 0 && cx == 0 )
                        {     // а пропускаем лишние нулевые символы,
                        if ( ex != 0 ) ex-- ;
                        // или заменяем пробелами.
                        else  output_c (' ') ;
                        }
                      else
                        {
                        if((cx == 0) && (Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0)  ) output_c ( all_sig ) ;
                        cx = 1 ; // первые нули закончились.
                        output_c ( (b)bx + 0x30 ) ;
                        }
                      }   // распечатываем последнюю цифру.
                      if ((cx == 0) && (Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0)  ) output_c ( all_sig ) ;
                        // распечатываем последнюю цифру.

                       output_c ( (b)(w)lax + 0x30 ) ;


                     Label = k22 ;
                     break;

      case k22:    // распечатка дробной части
                      if ( Ustav[m_index].adr_Gruop[m_addr].code._.celoe == 0 ) ex = 2 ;// по умолчанию.
                      else ex = Ustav[m_index].adr_Gruop[m_addr].code._.drob ;
                      if ( ex != 0 )
                      {
                        output_c ( '.' ) ;
                        bx = *(w*)&m_buff[0] ;
                        lax = m_time ; // восстанавливаем остаток.
                        for ( ; ex != 0 ; ex-- )
                              {
                                 lbx = lax*10  ;
                                   lax = lbx % bx ;
                                   ax  = lbx / bx ;
                                output_c ( (b)(w)ax + 0x30 ) ;
                               }
                      }
                 }
                      output_s ( Ustav[m_index].adr_Gruop[m_addr].ch ) ;
                      if ((Ustav[m_index].adr_Gruop[m_addr].code._.zapr == 1) && (_Ne_Rabota == 0) ) output_c ( '#' ) ;

                tst_output = 0 ;     //если, при нажатии, не успеваем вывести последнее значение, то
               }                     // взводим тригер, чтобы повторить вывод после отпускаения клавиши изменения
             else  tst_output = 1 ;


             Label = k30 ;// для режима изменения выбранной уставки

              break;
           //    Режим изменения выбранной уставки
      case k30: if (  TestData_for_Input() ) // while (  TestData_for_Input() ) 30.08.2019. На F16K с PU-162M в работе (R>) при
                {     // Считывание уставки для ее последующего изменения.      изменении уставок (А7) и зажатой клавише
                        // для 'word' все равно: со знаком или без.             больше/меньше через 15 сек срабатывала авария
                  ax = Ustav[m_index].adr_Gruop[m_addr].code._.type  ;       // по отсутствию синхронизации ТС1. Обнаружил
 //           #ifdef  _INTERPRETER                                           // Омельяненко Е. на ТПЕ-100.
                  if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 || ax == 0 )
                  {
                    if      ( ax == 1 ) dax =      (d)(sw)*( sb*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 2 ) dax =      (d)    *( sw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 3 ) dax =      (d)    *(  f*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 4 ) dax =      (d)    *(slw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 0 ) dax =             *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  }
                  else
                  {
                    if      ( ax == 1 ) dax =      (d)( w)*(  b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 2 ) dax =      (d)    *(  w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 3 ) dax =      (d)    *(  f*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 4 ) dax =      (d)    *( lw*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    else if ( ax == 0 ) dax =             *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  }
 /*           #else
                  if ( ax == 2 )         ax =            *(w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  else
                  {     // для 'byte' не все равно: со знаком или без.
                                         ax =           *(sb*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                    if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение.
                  }
            #endif*/

                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      //lax = m_lax ;  // Восстановление прежнего значения уставки.
//            #ifdef _INTERPRETER
                      dax = m_dbx ;  // Восстановление прежнего значения уставки.
/*            #else
                      ax  = m_ext ;  // Восстановление прежнего значения уставки.
            #endif*/
                      output_s ( "\n\r" ) ;
                      output_s ( Ustav[m_index].gruppa ) ;
                      output_c ( '\n' ) ;
                      if ( Ustav[m_index].kol_vo == 1 )
                      {
                        Label  = k18;
                      }
                      else Label = k10 ;

                    }
                  else if ( m_ch == Enter ) // Записать копию уставки в память в уставку.
                    {
                      output_s ( "\n\r" ) ;
                      output_s ( Ustav[m_index].gruppa ) ;
                      output_c ( '\n' ) ;
                      if ( Ustav[m_index].kol_vo == 1 )
                      {
                        Label  = k18;
                      }
                      else Label = k10 ;       // Вернуться к перебору уставок.
                    }
                  else if ((Ustav[m_index].adr_Gruop[m_addr].code._.zapr == 0)|| (_Ne_Rabota == 1) )
                  {
                    if ( m_ch == Up && Mon.Password_Ok == 1 )   /* Увеличить грубо копию уставки.*/
                    {
                      //if (Ustav[m_index].adr_Gruop[m_addr].code._.invert == 1 ) goto down ;
  //          #ifdef _INTERPRETER
               //up:  //dbx = dax ; // сохраняем предыдущее значение - ПРИ РАБОТЕ С DOUBLE КОНТРОЛЬ ПЕРЕПОЛНЕНИЯ НЕ НУЖЕН.
                      dax += Ustav[m_index].adr_Gruop[m_addr].dX ;
                      dbx  = Ustav[m_index].adr_Gruop[m_addr].max ;
                      if ( ax == 1 || ax == 2 )   //  В поле макс/мин типа double число по-старому ложится макросами
                      {  //  размерностью (w), и для отрицательных чисел старшие биты заполняются нулями, чтобы это исправить:
                        bx = (w)dbx ;  //  очищаем от старших нулевых битов в double.
                                      //  возвращаем в double с растяжкой знакового бита.
                        if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )  dbx = (sw)bx ;
                        else                                                          dbx = ( w)bx ;
                      }

                      if ( dax > dbx ) dax = dbx ;
                                                             //if ( dax < dbx ) lax = (lw)(w)bx ; // С DOUBLE КОНТРОЛЬ ПЕРЕПОЛНЕНИЯ НЕ НУЖЕН
 /*           #else
                      //if (Ustav[m_index].adr_Gruop[m_addr].code._.invert == 1 ) goto down ;
                 //up:
                      cx = ax ; // сохраняем предыдущее значение.
                      ax += Ustav[m_index].adr_Gruop[m_addr].dX ;
                      bx  = Ustav[m_index].adr_Gruop[m_addr].max ;
                       //  Если распечатка без знака то число рассматриваем
                      //  как беззнаковое в диапазоне 0...65535.
                      if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
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
            #endif*/
                      Label = k20 ;
                    }
                    else if ( m_ch == Down && Mon.Password_Ok == 1 ) /* Уменьшить грубо копию уставки.*/
                    {
                      //if (Ustav[m_index].adr_Gruop[m_addr].code._.invert == 1 ) goto up ;
 //           #ifdef _INTERPRETER
              //down:
                      dax -= Ustav[m_index].adr_Gruop[m_addr].dX ;
                      dbx  = Ustav[m_index].adr_Gruop[m_addr].min ;
                      if ( ax == 1 || ax == 2 )
                      {
                        bx = (w)dbx ;  //  очищаем от старших нулевых битов в double.
                                      //  возвращаем в double с растяжкой знакового бита.
                        if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )  dbx = (sw)bx ;
                        else                                                          dbx = ( w)bx ;
                      }

                      //if (( dax < dbx ) || ( dax>Ustav[m_index].adr_Gruop[m_addr].max)) dax = dbx ;
                      if ( dax < dbx ) dax = dbx ;
   /*         #else
                      //if (Ustav[m_index].adr_Gruop[m_addr].code._.invert == 1 ) goto up ;
                 //down:
                      cx = ax ; // сохраняем предыдущее значение.
                      ax -= Ustav[m_index].adr_Gruop[m_addr].dX ;
                      bx  = Ustav[m_index].adr_Gruop[m_addr].min ;
                      //if ( (sw)(ax -= Ustav[m_index].adr_Gruop[m_addr].dX ) < (sw)Ustav[m_index].adr_Gruop[m_addr].min ) ax = Ustav[m_index].adr_Gruop[m_addr].min ;
                      if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 )
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
          #endif*/
                       Label = k20 ;
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
         //   #ifdef _INTERPRETER
                  //ax = Ustav[m_index].adr_Gruop[m_addr].code._.type  ;
                  if ( Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0 || ax == 0 )
                  {
                    if      ( ax == 1 )   *( sb*)Ustav[m_index].adr_Gruop[m_addr].addr = (sb)dax ;
                    else if ( ax == 2 )   *( sw*)Ustav[m_index].adr_Gruop[m_addr].addr = (sw)dax ;
                    else if ( ax == 3 )   *(  f*)Ustav[m_index].adr_Gruop[m_addr].addr = (f)dax ;
                    else if ( ax == 4 )   *(slw*)Ustav[m_index].adr_Gruop[m_addr].addr = (slw)dax ;
                    else if ( ax == 0 )   *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr = dax ;
                  }
                  else
                  {
                    if      ( ax == 1 )   *(  b*)Ustav[m_index].adr_Gruop[m_addr].addr = (b)dax ;
                    else if ( ax == 2 )   *(  w*)Ustav[m_index].adr_Gruop[m_addr].addr = (w)dax ;
                    else if ( ax == 3 )   *(  f*)Ustav[m_index].adr_Gruop[m_addr].addr = (f)dax ;
                    else if ( ax == 4 )   *( lw*)Ustav[m_index].adr_Gruop[m_addr].addr = (lw)dax ;
                    else if ( ax == 0 )   *(  d*)Ustav[m_index].adr_Gruop[m_addr].addr = dax ;
                  }
        /*    #else
                  if ( Ustav[m_index].adr_Gruop[m_addr].code._.type == 2 )  *(w*)Ustav[m_index].adr_Gruop[m_addr].addr = ax ;
                  else                                                      *(b*)Ustav[m_index].adr_Gruop[m_addr].addr = ax ;
            #endif*/
                }
              if ( tst_output == 1 )  Label = k20 ;
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = k20;
              }
              break;
    }
     Restart_Output ()  ;

     return ;
}
/*---------------------------------*/



void Setab_Bit_Drive (char *numb, word kol)
{
  #define   index2   m_addr
  register word ax, bx;
  register char const *ptr;


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;

          if ( Mon.Password_Ok == 0 )  Label = 200 ;  // Вход с предупреждением о пароле.
          else                         Label = 210 ;  // Обычный вход.

          return ;
        }
        //--------------------

  switch ( Label )
    {
      default:
      case 200:  //  Контроль пароля: ограничение.
              output_s ( _PasswordLtd_txt ) ;
              m_time = Timer1_Ovr ;
              Label = 201 ;
      case 201:
              if ( (u)(w)(Timer1_Ovr - m_time) < _Time_Password_txt )  break ;
               //---

      case 210:  //  Обычный вход.

          index2 = 0;
            m_ext = 0;

            if ((kol == 0 ) || (kol > 1))
            {
              output_s ( _SetabBit_prompt ) ;
              output_c ( '\n' ) ;
              Label = 0 ;
              if ( kol > 1 )
              {
                m_index = numb[m_ext] ;   // установка номера блока уставок на первый
                if ( m_index > _MaxNumBUst ) goto bout;
              }
              else m_index = 0 ;   // установка номера блока уставок на первый
            }
            else
            {
              m_index = numb[0] ;   // установка номера блока уставок на требуемый
              output_c ( '\n' ) ;
              output_c ( '\r' ) ;
              if ( m_index >= _MaxNumBUst )
              {
                Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
              }
              output_s( AWelcome );
              output_s ( bts[m_index].text ) ;

              for(index2 = 0; (*bts[m_index].mask1 & bts[m_index].msk[index2]) == 0; ++index2)
              {
                  if ( index2 >= (w)bts[m_index].n )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      break;
                    }

              }

              Label = 5 ;
            }

          return ;
          //-------

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
                  output_s ( bts[m_index].text ) ;
                  Label = 10 ;
                }
              else
                {   // Вывод значения ячейки соответствующей данной строке меню.

                  if ( bts[m_index].code._.type == 1 )  ax = *(b*)bts[m_index].addr ;
                  else  ax = *(w*)bts[m_index].addr ;

                  //output_c ( '\n' ) ;
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                       //  03-02-14 КВВ
                       //    Ограничиваем вывод имени бита на 14-ти символах для возможности
                       //  указания в таблице А8 адресов строк сообщений из "А1-Сообщения" и чтобы
                       //  символы не выезжали за экран, т.к. сообщения 16-ти символьные -
                       //  понадобилось для СВТГ для масок переходов между СВ1 и СВ2 по авариям.
                  // output_s ( bts[m_index].bit[index2] ) ;
                  ptr = bts[m_index].bit[index2] ;
                  for ( bx = 0 ; ptr[ bx ] != NULL && bx < _A8_bit_txt_size  ; bx++ ) {  output_c ( ptr[ bx ] ) ; }
                  output_c ( '=' ) ;
                  if ( ( ax  & bts[m_index].msk[index2]) == 0 )
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
                        if ( m_index > _MaxNumBUst ) goto bout;
                      }
                      else if ( ++m_index >= _MaxNumBUst ) m_index = 0 ;
                      Label = 0 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      if ( kol > 1 )
                      {
                        if (m_ext-- == 0 ) m_ext = kol-1;
                        m_index = numb[m_ext] ;
                        if ( m_index > _MaxNumBUst ) goto bout;
                      }
                      else if ( m_index-- == 0 ) m_index = _MaxNumBUst - 1  ;
                      Label = 0 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
                      for(index2 = 0; (*bts[m_index].mask1 & bts[m_index].msk[index2]) == 0; ++index2)
                      {
                          if ( index2 >= (w)bts[m_index].n )
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
                  if ( bts[m_index].code._.type == 1 )  ax = *(b*)bts[m_index].addr ;
                  else  ax = *(w*)bts[m_index].addr ;

                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  {
                     if ( kol == 1 ) goto bout;
                     else
                     {
                        output_s ( _SetabBit_prompt ) ;
                        output_c ( '\n' ) ;
                        Label = 0 ;
                     }

                  }
                  else if ( m_ch == Down ) /* Уменьшить грубо копию уставки.*/
                    {
                      do
                      {
                        if ( ++index2 >= (w)bts[m_index].n ) index2 = 0 ;
                      }
                      while ((*bts[m_index].mask1 & bts[m_index].msk[index2]) == 0 );

                      Label = 5 ;
                    }
                  else if ( m_ch == Up )   /* Увеличить грубо копию уставки.*/
                    {
                      do
                      {
                        if ( index2-- == 0 ) index2 = (w)bts[m_index].n-1 ;
                      }
                      while ((*bts[m_index].mask1 & bts[m_index].msk[index2]) == 0 );
                      Label = 5 ;
                    }
                  else if ( m_ch == Enter && Mon.Password_Ok == 1 ) // Записать копию уставки в память в уставку.
                    {
                      ax ^= bts[m_index].msk[index2]  ;  // Инвертирование разряда уставки.
                      Label = 5 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                  if ( bts[m_index].code._.type == 1 ) *(b*)bts[m_index].addr = ax ;
                  else                                 *(w*)bts[m_index].addr = ax ;

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

