
//         ПРОГРАММА ТЕСТИРОВАНИЯ ВЫХОДНЫХ ДИСКРЕТНЫХ СИГНАЛОВ .
//------------------------------------------------------------------
/*   Режим доступен из "Останова".
 *   Функции:
 * - выбор порта выходных сигналов из таблицы путем перебора ;
 * - индикация последнего записанного в порт значения в двоичном
 *  поразрядном виде;
 * - модификация посредством клавиатуры поразрядно в двоичном виде значения
 *  перед записью его в порт;
 * - запись в порт модифицированного значения.
 *   Клавиши:
 * - "+" или "-" в режиме выбора порта - выбор порта ;
 * - "Enter" в режиме выбора порта - переход к индикации и модификации
 *  содержимого порта;
 * - "+" или "-" в режиме индикации - перевод курсора к очередному старшему
 *  либо младшему разряду порта соответсвенно ;
 * - "F" или "f" в режиме индикации - инвертирование разряда, на котором
 * установлен курсор, без его записи в порт;
 * - "Enter" в режиме индикации - запись модифицированного значения
 *  содержимого порта в порт;
 * - "Esc" в режиме выбора порта - возврат в диспетчер ;
 * - "Esc" в режиме индикации - переход к режиму выбора порта.
 */


void TstOutputPort_Drive ( void )
{
   register byte  bh , cl ;
   word ax;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          Label = 100 ;
          m_index = 0 ;
          return ;
        }

  switch ( Label )
    {
      default:
      case 100:
              output_s ( _Output_Tst "\n" ) ;
              Label = 101 ;
      case 101:   // Ожидание завершения предыдущего вывода.
              if ( TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s ( Nstout[ m_index ].txt ) ;
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
                      if ( ++m_index >= _Nout ) m_index = 0 ;
                      Label = 101 ;
                    }
                  else if ( bh == Up ) /* Выбрать номер порта.*/
                    {
                      if ( m_index-- == 0 ) m_index = _Nout - 1 ;
                      Label = 101 ;
                    }    /* переход к следующей настройке */
                  else if ( bh == Enter )
                  {

                    Label = Nstout[ m_index ].label ;

                  }
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------

      case 20:
              output_c ( '\n' ) ;
              output_c ( '\r' ) ;
              output_c ( _Output_Tst_c ) ;
              bh = m_buff[0] = *Nstout[ m_index ].Px ;

                /*   Преобразование содержимого копии порта в двоичный
                 * символьный вид.
                 */
              for ( cl = 0 ; cl <= 7 ; cl++ )
                {
                  if ( (sb)bh < 0 ) output_c ( '1' ) ;
                  else              output_c ( '0' ) ;
                  bh <<= 1 ;
                }
              output_c ( _Output_Tst_m ) ;
              output_c ( BckSp ) ;
              output_c ( BckSp ) ;
              m_ext = 0 ;
              Label = 30 ;
              break ;
            //-------------------

      case 30:
              if ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )  Label = 100 ;
                  else if ( bh == Up ) /* Выбрать номер бита.*/
                    {
                      if ( m_ext < 7 )
                        {
                          m_ext++ ;
                          output_c ( BckSp ) ; // сместиться на позицию влево.
                        }
                        else
                        {
                          Label = 20;
                          break;
                        }
                    }
                  else if ( bh == Down ) /* Выбрать номер бита.*/
                    {
                      if ( m_ext != 0 )
                        {
                          m_ext-- ;
                          output_c ( FrvdSp ) ; // сместиться на позицию вправо.
                        }
                    }      /* Проинвертировать выбранный бит.*/
                  else if ( bh == Enter )
                    {
                      bh = 0x01 << m_ext ;
                      m_buff[0] ^= bh ;
                      if ( ( m_buff[0] & bh ) == 0 )  output_c ( '0' ) ;
                      else                            output_c ( '1' ) ;
                      output_c ( BckSp ) ;
                          /* Вывод в порт скорректированной копии данных. */
                      *Nstout[ m_index ].Px  = m_buff[0] ;
                    }
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------

      case 40:
              output_c ( '\n' ) ;
              m_time = Timer1_Ovr - _Sec( 1.0 ) ;
              Label = 41 ;
      case 41:
              ax = Timer1_Ovr - m_time;
              if ( (u)ax >= _Sec( 0.2 ) )
                {
                  output_c ( '\r' ) ;
                  output_s ( _Output_Tst_Q1 ) ;
                  mClr_Q1();
                  Label = 50 ;
                }
              break ;
            //-------------------

      case 50:
              if ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )  Label = 100 ;
                  else if ( bh == Enter ) /*     */
                    {
                      mOtkl_Q1 () ;
                      output_c ( '\r' ) ;
                      output_s ( _Output_Tst_q1 ) ;
                      m_time = Timer1_Ovr ;
                      Label = 41 ;
                    }
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------

      case 60:
              output_c ( '\n' ) ;
              m_time = Timer1_Ovr - _Sec( 1.0 ) ;
              Label = 61 ;
      case 61:
              ax = Timer1_Ovr - m_time;
              if ( (u)ax >= _Sec( 0.3 ) )
                {
                  output_c ( '\r' ) ;
                  output_s ( _Output_Tst_Q2 ) ;
                  mClr_Q2();
                  Label = 70 ;
                }
              break ;
            //-------------------

      case 70:
              if ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )  Label = 100 ;
                  else if ( bh == Enter )
                    {
                      mOtkl_Q2 () ;
                      output_c ( '\r' ) ;
                      output_s ( _Output_Tst_q2 ) ;
                      m_time = Timer1_Ovr ;
                      Label = 61 ;
                    }
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------
#ifdef   _ATK_ROT
      case 80:
              output_c ( '\n' ) ;
              m_time = Timer1_Ovr - _Sec( 1.0 ) ;
              Label = 81 ;
      case 81:
              ax = Timer1_Ovr - m_time;
              if ( (u)ax >= _Sec( 0.2 ) )
                {
                  output_c ( '\r' ) ;
                  output_s ( _Output_Tst_PPG4 ) ;
                  mPPG4_set( 1 ) ;
                  Label = 90 ;
                }
              break ;
            //-------------------

      case 90:
              if ( TestData_for_Input() )
                {
                  mInput_c ( bh ) ;
                  if ( bh == Return )  Label = 100 ;
                  else if ( bh == Enter ) /*     */
                    {
                      mPPG4_set( 0 ) ;
                      output_c ( '\r' ) ;
                      output_s ( _Output_Tst_ppg4 ) ;
                      m_time = Timer1_Ovr ;
                      Label = 81 ;
                    }
                  else
                    {
                      Klav_Buff = bh;
                    }
                }
              break ;
            //-------------------

#endif
      }

  Restart_Output ()  ;

  return ;
}

