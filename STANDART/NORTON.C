
//         ПРОГРАММА АКТИВИЗАЦИИ ПУЛЬТОВЫХ ПРОГРАММ ПУТЕМ ВЫБОРА
//             ЖЕЛАЕМОЙ ДЛЯ ЗАПУСКА ПРОГРАММЫ В РЕЖИМЕ МЕНЮ.
//         ИСПОЛЬЗУЕТСЯ КАК АЛЬТЕРНАТИВА К ЗАПУСКУ ТОЙЖЕ ПРОГРАММЫ
//              ВВОДОМ СИМВОЛЬНОЙ КОМАНДЫ ИЗ СТРОКИ КОМАНД.
//------------------------------------------------------------------
/*   Функции:
 * - выбор в режиме меню желаемой для запуска программы и ее запуск ;
 *   Клавиши:
 * - "+", "-" смена пункта меню ;
 * - "Enter" - запуск выбранной в меню программы ;
 * - "Esc"   - возврат в диспетчер.
 */


void Norton_Drive ( void )
{
//   static word  index ;
   _register byte    bh;
   _register word    ax, bx, cx;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          m_index = m_old ;
          m_addr = 0;
          m_ext =  NC[ m_index ].cmd;
          output_s ( _Norton_prompt ) ;
          if (  TestCompleted_Output() )
            {
            //  output_s ( "\r\n" ) ;
              if (NC[ m_index ].Password != 0 )
              {
                while (NC[ m_index ].Password != Nort_Password )
                {
                  if ( ++m_index >= _Nc ) m_index = 0 ;
                  if (NC[ m_index ].Password == 0 ) break;

                }
              }
              output_s ( NC[ m_index ].txt ) ;
            }
          Label = 100 ;
          return ;
        }

  switch ( Label )
    {
      default: Label = 100 ;
      case 100:
                 // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ('\r') ;
                  output_s (AWelcome) ;
                  output_s ( NC[ m_index ].txt ) ;
                  Label = 105 ;
                  break ;
                }
      case 105:while (  TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      m_old = m_index= 0;
                      m_addr = 0;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Down ) /* Выбрать пункт меню. */
                    {
                        do
                        {
                          if ( ++m_index >= _Nc ) m_index = 0 ;
                          if (NC[ m_index ].Password == 0) break;
                        } while (NC[ m_index ].Password != Nort_Password);
                      m_addr = 0;
                      m_ext =  NC[ m_index ].cmd;

                      Label = 100 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Up )
                    {
                        do
                        {
                          if ( m_index-- == 0 ) m_index = _Nc - 1 ;
                          if (NC[ m_index ].Password == 0) break;
                        } while (NC[ m_index ].Password != Nort_Password);
                      m_addr = 0;
                      m_ext =  NC[ m_index ].cmd;
                      Label = 100 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Enter )
                    {
                      Pult_Prog_Addr = m_ext,  M_FirstCall = 1 ;
                      m_old = m_index;
                    }
                  //Вставка для выбора программы из меню с помощью клавиатуры
                  //при нажатии буквенной клавиши меню переходит на строку меню,
                  //вызов которой начинается с данной буквы(первая сверху в структуре),
                  //если таковая имеется.При нажатии второй клавиши осущесвляется переход
                  //на строку, код вызова которой был набран(опять же при наличии таковой)
                  else if ( ( bh >= 'A'  &&  bh <= 'M' )
                                    ||
                       ( bh >= '0'  &&  bh <= '9' )
                                    ||
                       ( bh >= 'a'  &&  bh <= 'm' ) )
                    {

                          Label = 100 ;//изменение стороки необходмо отобразить

                          //Вводится первый символ
                          if (m_addr  == 0 )
                          {
                            //Если первый символ 0, то переходим к диспетчеру
                            if ( bh == '0' )
                            {
                              m_index = 0;
                              m_ext = 0;
                            }
                            else
                            {
                              //Если введен символ, которого нет в меню, то
                              //он рассматривается как код команды(для скрытых
                              //программ, таких, как программа считывания уставок)
                              m_ext =  bh;
                            }

                           cx = _Nc;
                           //Проходим по меню в поисках нужной строки
                           //for( bx = 0; bx < _Nc; ++bx)
                           for( bx = _Nc-1 ; (sw)bx >= 0 ; --bx)
                            {
                              ax = NC[ bx ].cmd & 0xff;//Смотрим по первому символу
                              //На случай, если вводили маленькими буквами проверяем также и на
                              //равенство ax+0x20. Также проверяем не запаролена ли данная строчка
                              if ( (ax == bh)||((ax+0x20) == bh) )
                              {
                                m_index = bx;//изменяем номер строки
                                //Если второго символа нет, то запоминаем его номер, чтобы вывести
                                //эту строчку первой.
                                if ((NC[ bx ].cmd>>8) == 0  )
                                {
                                  cx = bx;
                                }
                                m_addr = 1; //переходим ко второму символу
                                m_ext =  NC[ m_index ].cmd;

                                //break;
                              }

                            }

                            if ( cx != _Nc )
                            {
                                m_ext =  NC[ cx ].cmd;
                                m_index = cx;//изменяем номер строки
                            }
                          }
                          else
                          {
                             //второй символ
                             m_addr = 0;//Чтобы не надо было каждый раз нажимать ESC
                             ax = NC[ m_index ].cmd & 0xff;//Т.к. это второй символ, то первый - это
                                                           // первая бува команды в текущей строчке
                             ax += (w)bh<<8;//Теперь надо проверять оба символа
                             //При набирании несуществующей комбинации переходим на строчку
                             //диспетчера
                             m_index = 0;
                             m_ext = bh;
                             for( bx = 0; bx < _Nc; ++bx)
                              {
                                if ( (ax == NC[ bx ].cmd)||(ax == (NC[ bx ].cmd+0x2000)) )
                                {
                                  m_index = bx;
                                  m_ext =  NC[ m_index ].cmd;
                                  //Label = 100 ;
                                  break;
                                }

                              }

                          }

                    }

/*                  else if (( bh == 'q' )||( bh == 'Q'))
                  {
                    Pult_Prog_Addr = 'Q',  M_FirstCall = 1 ;
                    m_old = m_index;

                  }*/
                  else
                    {
                      Klav_Buff = bh;
                    }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 100;
              }
              break ;
      }

  Restart_Output ()  ;

  return ;
}

