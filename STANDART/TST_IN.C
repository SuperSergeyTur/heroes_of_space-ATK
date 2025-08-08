
//         ПРОГРАММА ТЕСТИРОВАНИЯ ВХОДНЫХ ДИСКРЕТНЫХ СИГНАЛОВ .
//------------------------------------------------------------------
/*   Режим доступен из "Останова".
 *   Функции:
 * - выбор порта входных сигналов из таблицы путем перебора ;
 * - индикация содержимого порта в двоичном поразрядном виде.
 *   Клавиши:
 * - "+" или "-" в режиме выбора порта - выбор индицируемого порта ;
 * - "Enter" в режиме выбора порта - переход к индикации содержимого порта;
 * - "Esc" в режиме выбора порта - возврат в диспетчер ;
 * - "Esc" в режиме индикации - переход к режиму выбора порта.
 */


void TstInputPort_Drive ( void )
{
   register byte  bh , cl ;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          Label = 100 ;
          output_s ( _Input_Tst ) ;
          return ;
        }

  switch ( Label )
    {
      default: Label = 100 ;
      case 100:
              m_index = 0 ;
      case 101:
              output_c ( '\n' ) ;
              Label = 103 ;
      case 103:  // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s ( Nstin[ m_index ].txt ) ;
                  Label = 105 ;
                  break ;
                }
      case 105:if ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Down ) /* Выбрать номер порта.*/
                    {
                      if ( ++m_index >= _Nin ) m_index = 0 ;
                      Label = 103 ;
                    }
                  else if ( bh == Up ) /* Выбрать номер порта.*/
                    {
                      if ( m_index-- == 0 ) m_index = _Nin - 1 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Enter )  Label = 20 ;
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------

      case 20:
              output_c ( '\n' ) ;
              Label = 23 ;
      case 23:
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( ( TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
                {
                  output_c ( '\r' ) ;
                  output_c ( _Input_Tst_c ) ;
                  bh = *Nstin[ m_index ].data ;

                    /*   Преобразование содержимого копии порта в двоичный
                     * символьный вид.
                     */
                  for ( cl = 0 ; cl <= 7 ; cl++ )
                    {
                      if ( (sb)bh < 0 ) output_c ( '1' ) ;
                      else              output_c ( '0' ) ;
                      bh <<= 1 ;
                    }
                  output_c ( _Input_Tst_m ) ;
                  output_c ( '\r' ) ;
                  m_time = Timer1_Ovr ;
                  Label = 23 ;
                }
              if ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )  
                    {  
                      output_s ( _Input_Tst ) ;
                      Label = 101 ;
                    }
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------
      }

  Restart_Output ()  ;

  return ;
}

