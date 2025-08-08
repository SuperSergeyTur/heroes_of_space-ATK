// Программа индикации времени из часов-календаря.
void xClock ( struct I2C_time* ptr )
{
   _register word    ax , cx ;
   _register byte  bl;

   //_register lword  lax ;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
              Label = 100 ;
              m_index = 0 ;
              t_clock = Timer1_Ovr;

          return ;
        }

  switch ( Label )
    {
      default:
      case 100:
                Time_label = 0;
                Label = 101;
      case 101:
               /* ax = Read _i2c_time();
                if (ax != 4  )
                {
                  if ( ax != 0 )
                  {
                     mSet_ServiceMsg( _Srv_NoRead_time );
                     Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                     break;
                  }
                  else*/ Label = 102;

             //   }
            //    break;

      case 102:
              output_s ( _Clock_prompt ) ;
              output_c ( '\n' ) ;
              Label = 103 ;
      case 103:
                 // Пропуск вывода, если не завершен предыдущий вывод.
              if (  TestCompleted_Output() )
                {
                  output_c ('\r') ;
                  output_s (AWelcome) ;
                  output_s ( c_Clock[m_index] ) ;
                  Label = 105 ;
                  break ;
                }
      case 105:
                while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_index >= 2 ) m_index = 0 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( (sw)(--m_index) < 0 ) m_index = 1 ;
                      Label = 103 ;
                    }
                  else if ( m_ch == Enter )
                    {
                      output_s ( "\n\r" ) ;
                      output_s ( c_Clock[m_index] ) ;
                      output_c ( '\n' ) ;

                      Label = m_index+2 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 103;
              }

              break ;
            //-------------------

      case 2:
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
                {
                  output_c ( '\r' ) ;
                  output_s (AWelcome) ;
                  for ( ax = 2; (sw)ax >= 1; --ax  )
                  {
                      bl =ptr->b[ax];

                      cx = bl >> 4;
                      cx += 0x30;
                      output_c ( cx );
                      cx = (bl & 0x0f)+0x30;
                      output_c ( cx );
                      output_c ( ':' );

                  }

                  bl =ptr->b[0];

                  cx = bl >> 4;
                  cx += 0x30;
                  output_c ( cx );
                  cx = (bl & 0x0f)+0x30;
                  output_c ( cx );
                  output_c ( ' ' );

                  m_time = Timer1_Ovr ;
                }

              while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = 102 ;
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
      //if ( (u)((w)(Timer1_Ovr - t_clock)) > _Sec(0.1) )  Label = 4;

              break ;
            //-------------------
      case 3:
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
                {
                  output_c ( '\r' ) ;
                  output_s (AWelcome) ;
                  for ( ax = 4; ax <= 5; ++ax  )
                  {
                      bl =ptr->b[ax];

                      cx = bl >> 4;
                      cx += 0x30;
                      output_c ( cx );
                      cx = (bl & 0x0f)+0x30;
                      output_c ( cx );
                      output_c ( '.' );

                  }
                      bl =ptr->b[6];

                      cx = bl >> 4;
                      cx += 0x30;
                      output_c ( cx );
                      cx = (bl & 0x0f)+0x30;
                      output_c ( cx );

                  output_s ( Day[(ptr->b[3])-1] );

                  m_time = Timer1_Ovr ;
                }

              while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = 102 ;
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
              break ;

            //-------------------
/*    case 4:
                Time_label = 0;
                Label = 5;
      case 5:
                ax = Read _i2c_time();
                if (ax != 4  )
                {
                  if ( ax != 0 )
                  {
                     mSet_ServiceMsg( _Srv_NoRead_time );
                     Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                     break;
                  }
                  else
                  {
                   Label = 2;
                   t_clock = Timer1_Ovr;
                  }

                }
                break;   */
      }

  Restart_Output ()  ;

  return ;
}
// Программа индикации времени из часов-календаря.
/*void Clock ( void )
{
   _register word    ax , cx ;
   _register byte  bl;

   //_register lword  lax ;

      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          M_FirstCall = 0 ;
              Label = 100 ;
              m_index = 0 ;
              t_clock = Timer1_Ovr;

          return ;
        }

  switch ( Label )
    {
      default:
      case 100:
                Time_label = 0;
                Label = 101;
      case 101:
                ax = Read _i2c_time();
                if (ax != 4  )
                {
                  if ( ax != 0 )
                  {
                     mSet_ServiceMsg( _Srv_NoRead_time );
                     Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                     break;
                  }
                  else Label = 102;

                }
                break;

      case 102:
              output_s ( _Clock_prompt ) ;
              output_c ( '\n' ) ;
              Label = 103 ;
      case 103:
                 // Пропуск вывода, если не завершен предыдущий вывод.
              if (  TestCompleted_Output() )
                {
                  output_c ('\r') ;
                  output_s (AWelcome) ;
                  output_s ( c_Clock[m_index] ) ;
                  Label = 105 ;
                  break ;
                }
      case 105:
                while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Up ) // Изменить номер индицируемой переменной.
                    {
                      if ( ++m_index >= 2 ) m_index = 0 ;
                      Label = 103 ;
                    }    // переход к следующей настройке
                  else if ( m_ch == Down ) // Изменить номер индицируемой переменной.
                    {
                      if ( (sw)(--m_index) < 0 ) m_index = 1 ;
                      Label = 103 ;
                    }
                  else if ( m_ch == Enter )
                    {
                      output_s ( "\n\r" ) ;
                      output_s ( c_Clock[m_index] ) ;
                      output_c ( '\n' ) ;

                      Label = m_index+2 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 103;
              }

              break ;
            //-------------------

      case 2:
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
                {
                  output_c ( '\r' ) ;
                  output_s (AWelcome) ;
                  for ( ax = 2; (sw)ax >= 1; --ax  )
                  {
                      bl =c_time.b[ax];

                      cx = bl >> 4;
                      cx += 0x30;
                      output_c ( cx );
                      cx = (bl & 0x0f)+0x30;
                      output_c ( cx );
                      output_c ( ':' );

                  }

                  bl =c_time.b[0];

                  cx = bl >> 4;
                  cx += 0x30;
                  output_c ( cx );
                  cx = (bl & 0x0f)+0x30;
                  output_c ( cx );
                  output_c ( ' ' );

                  m_time = Timer1_Ovr ;
                }

              while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = 102 ;
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
      if ( (u)((w)(Timer1_Ovr - t_clock)) > _Sec(0.1) ) Label = 4;

              break ;
            //-------------------
      case 3:
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > 2 ) )
                {
                  output_c ( '\r' ) ;
                  output_s (AWelcome) ;
                  for ( ax = 4; ax <= 5; ++ax  )
                  {
                      bl =c_time.b[ax];

                      cx = bl >> 4;
                      cx += 0x30;
                      output_c ( cx );
                      cx = (bl & 0x0f)+0x30;
                      output_c ( cx );
                      output_c ( '.' );

                  }
                      bl =c_time.b[6];

                      cx = bl >> 4;
                      cx += 0x30;
                      output_c ( cx );
                      cx = (bl & 0x0f)+0x30;
                      output_c ( cx );

                  output_s ( Day[(c_time.b[3])-1] );

                  m_time = Timer1_Ovr ;
                }

              while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  Label = 102 ;
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
              break ;

            //-------------------
      case 4:
                Time_label = 0;
                Label = 5;
      case 5:
                ax = Read _i2c_time();
                if (ax != 4  )
                {
                  if ( ax != 0 )
                  {
                     mSet_ServiceMsg( _Srv_NoRead_time );
                     Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                     break;
                  }
                  else
                  {
                   Label = 2;
                   t_clock = Timer1_Ovr;
                  }

                }
                break;
      }

  Restart_Output ()  ;

  return ;
}
*/

// Программа настройки времени в часах-календаре.
void xClock_ust ( struct I2C_time* ptr)
{
   _register word    ax , bx , cx ;
   //_register byte  bl;
   _register lword  lax ;
   static struct I2C_time s_time;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          M_FirstCall = 0 ;
              Label = 100 ;
              m_index = 5 ; // 0
              Time_label = 0;
          return ;
        }

  switch ( Label )
    {
      case 100:
             /* ax = Read _i2c_time();
              if ( ax == 1 )
              {
                  mSet_ServiceMsg( _Srv_NoRead_time );
                  Label = 107;
                  break;
              }
              else if ( ax == 0 )
              {*/
                s_time = *ptr;
                Label = 101;
             // }

      case 101:
                  bx = s_time.b[0]|| 0x80;
                  if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                  Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
                  i2c_label = 0;
                  ax = Save_into_i2c  ( 1 , (b*)&bx , _Adr_sec  ,_Adr_Clock_i2c) ;
                  Mon.i2c_busy = 0 ;
                  t_clock = Timer1_Ovr;
                  Label = 102;
                  break;

      default:
      case 102:
              output_s ( _Clock1_prompt ) ;
              output_c ( '\n' ) ;
              Label = 103 ;
              break;

      case 103:
                 // Пропуск вывода, если не завершен предыдущий вывод.
              if (  TestCompleted_Output() )
                {
                  output_c ('\r') ;
                  output_s (AWelcome) ;
                  output_s ( u_Clock[m_index] ) ;
                  Label = 105 ;
                  break ;
                }
      case 105:
                while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Label = 106;
                      break;
                    }
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_index >= 7 ) m_index = 0 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( (sw)(--m_index) < 0 ) m_index = 6 ;
                      Label = 103 ;
                    }
                  else if ( m_ch == Enter )
                    {
                      output_s ( "\n\r " ) ;
                      output_s ( u_Clock[m_index] ) ;
                      output_s ( ":\n" ) ;
                      Label = m_index ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
                Label = 103;
              }

              break ;
            //-------------------
    case 106:
              if ( (u)((w)(Timer1_Ovr - t_clock)) > _Sec(0.25) )
              {
                if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
                    i2c_label = 0;
                    ax = Save_into_i2c  ( 7 , (b*)&s_time.b[1] , _Adr_min  ,_Adr_Clock_i2c) ;

                Mon.i2c_busy = 0 ;
                if ( ax != 0 )   mSet_ServiceMsg( _Srv_NoWrite_time ) ;
                else output_s ( _Saved_txt );
                *ptr = s_time;
                Label = 107;
                t_clock =  Timer1_Ovr;
              }
              break;
    case 107:
              Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
              return ;   // добавить еще какую-то иниц.

    case 0:
              clock_max = 0x59;
              n_clock = 1;
              Label = 70;
              break;
    case 1:
              clock_max = 0x23;
              n_clock = 2;
              Label =70 ;
              break;
    case 2:
              Label = 80;
              break;
    case 3:
              clock_max = 0x31;
              n_clock = 4;
              Label = 70;
              break;
    case 4:
              clock_max = 0x12;
              n_clock = 5;
              Label = 70;
              break;
    case 5:
              clock_max = 0x99;
              n_clock = 6;
              Label = 70;
              break;
    case 70:

              clock_ed  =s_time.b[n_clock];
              if ( (u)clock_ed> clock_max) clock_ed = clock_max;
              Label = 60;

    case 60:
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) )
              {
                  output_c ( '\r');
                  output_s (AWelcome) ;
                  cx = clock_ed >> 4;
                  cx += 0x30;
                  output_c ( cx );
                  cx = (clock_ed & 0x0f)+0x30;
                  output_c ( cx );
                  output_c ( '\r');
                  m_time = Timer1_Ovr ;
              }

              while ( TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  {
                    output_c ('\n');
                    Label = 102 ;
                  }
                  else if ( m_ch == Up )
                    {
                      if ( clock_ed == clock_max )
                      {
                          if ( (n_clock == 6) || (n_clock == 1)
                                              ||(n_clock == 2))
                          {
                            clock_ed = 0;
                          }
                          else clock_ed = 1;
                      }
                      else
                      if ( (clock_ed&0x0f) == 9 )
                      {
                        clock_ed+=7;
                      }
                      else clock_ed++ ;
                    }
                  else if ( m_ch == Down )
                    {
                      if ( (n_clock == 6) || (n_clock == 1)
                                          ||(n_clock == 2))
                      {
                        ax = 0;
                      }
                      else ax = 1;

                      if ( clock_ed != ax )
                        {
                          if ( (clock_ed&0x0f) != 0 )
                          {
                            clock_ed--;
                          }
                          else clock_ed -= 7;
                        }
                        else clock_ed = clock_max;
                    }
                    else if (m_ch == Enter)
                    {
                     s_time.b[n_clock] = clock_ed;
                     output_c ('\n');
                     Label = 102 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              break ;

    case 6:
                if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                Mon.i2c_busy = 1 ;
                i2c_label = 0;
                Label = 71 ;
    case 71:

             /* if ( (u)((w)(Timer1_Ovr - t_clock)) > _Sec(0.25) )
              {*/
                ax = xLoad_from_i2c ( 1 , _Adr_Contr , (b*)&s_time.b[7]  ,_Adr_Clock_i2c) ;
                if ( ax != 4 )
                {
                 Mon.i2c_busy = 0 ;
                 if (ax == 0)
                 {
                   n_clock = s_time.b[7]&0x1f ;
                   if (((s_time.b[7]>>5)&0x01) == 0 ) n_clock = ~n_clock+1;
                   Label = 72 ;
                 }
                 else
                 {
                    mSet_ServiceMsg( _Srv_NoRead_time );
                    Label = 107;
                 }

                }
             /*   t_clock =  Timer1_Ovr;
              }*/
            break;

    case 72:
              if  (   TestCompleted_Output() )    // чтобы не мельтешило.
              {
                output_c ( '\r');
                output_s (AWelcome) ;

                 if ((sw)n_clock < 0 )
                 {
                    output_c ('-') ;
                    ax = ~n_clock+1;
                    lax = ax*1370;//5.35*256 = 1370 - дискрета изменения
                                  //5.35 секунд в месяц для минуса
                 }
                 else
                 {
                    output_c ('+') ;
                    ax = n_clock;
                    lax = ax*2739;//10.7*256 = 2739 - дискрета изменения
                                  //10.7 секунд в месяц  для плюса
                 }

                 m_time = lax%256;
                 lax /=256;

                  for ( ax = 100 ; ax != 1 ; ax /= 10 )
                  {
                    bx = lax / ax ;
                    lax %= ax;
                    output_c ( (b)bx + 0x30 ) ;
                  }   // распечатываем последнюю цифру.
                  output_c ( (b)(w)lax + 0x30 ) ;

                  Label = 73;
                  break;
    case 73:
                  output_c ( '.' ) ;
                  lax = m_time ; // восстанавливаем остаток.
                  lax*=10  ;
                  ax = lax/256 ;
                  output_c ( (b)ax + 0x30 ) ;

                  output_s (" сек/меc"  ) ;

                  Label = 74;
                  break;
              }
    case 74:
              while ( TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  {
                    output_c ('\n');
                    Label = 102 ;
                  }
                  else if ( m_ch == Up )
                    {
                      if ( (sw)(++n_clock) >= (sw)0x1f ) n_clock = 0x1f;
                      Label = 72;
                    }
                  else if ( m_ch == Down )
                    {
                      if ( (sw)(--n_clock)<= (sw)0xffe1 ) n_clock = 0xffe1;
                      Label = 72;

                    }
                    else if (m_ch == Enter)
                    {
                      Label = 75;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              break ;
    case 75:
              if ( (sw)n_clock < 0 )
              {
              n_clock = ~n_clock+1;
              n_clock &= 0xdf;
              }
              else
              {
              n_clock |= 0x20;
              }
              s_time.b[7] = n_clock;
              output_c ('\n');
              Label = 76;
    case 76:
              if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
              Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
                  i2c_label = 0;
                  ax = Save_into_i2c  ( 1 , (b*)&s_time.b[7] , _Adr_Contr  ,_Adr_Clock_i2c) ;

              Mon.i2c_busy = 0 ;
              if ( ax != 0 )   mSet_ServiceMsg( _Srv_NoWrite_time ) ;
              Label = 102 ;
              break;
    case 80:
              clock_ed =s_time.b[3];
              if ( (u)clock_ed > 7) clock_ed = 7;
              else if (clock_ed == 0 ) clock_ed = 1;
              Label = 8;
    case 8:
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) )
              {

                  output_c ( '\r');
                  output_s (AWelcome) ;
                  output_s ( Day[clock_ed-1] );
                  m_time = Timer1_Ovr ;
              }

              while ( TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                  {
                    output_c ('\n');
                    Label = 102 ;
                  }
                  else if ( m_ch == Up )
                    {
                      if ( clock_ed == 7 )
                      {
                         clock_ed = 1;
                      }
                      else ++clock_ed;
                    }
                  else if ( m_ch == Down )
                    {
                      if ( clock_ed != 1 )
                        {
                            --clock_ed;
                        }
                        else clock_ed = 7;
                    }
                    else if (m_ch == Enter)
                    {
                     s_time.b[3] = clock_ed;
                     output_c ('\n');
                     Label = 102 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              break ;

    }
  Restart_Output ()  ;

  return ;
}
