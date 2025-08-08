

/*       ПРОГРАММЫ ВВОДА/ВЫВОДА ИНФОРМАЦИИ НА ПУЛЬТ.  */

/*  Включают:  */
/* - программа диспетчер пультовых программ;  */
/* - программа - монитор;  */
/* - программа вывода на пульт строки сообщения;  */
/* - программа запрета доступа к системным программам;  */
/* - программа вывода содержимого слова в десятичном или  */
/*                   шестнадцатеричном формате.  */
/*------------------------------------------------------  */

/* #include "uart_drv.c" */

#ifndef _Monitor_start_page
  #define _Monitor_start_page  0
#endif

/*---------------------------------------------------  */

void Monitor ( void )
{
  static _register byte Regim   ;
  static _register byte B_W     ;
/*  m_addr, m_ext - Вычисленное значение введенного адреса.  */
/*  m_time     - Время последнего любого нажатия клавиши.  */
/*  m_index    - Cчетчик введенных символов в буфер m_buff[].  */
/*  m_buff[]   -  Буфер вводимых цифр значения данных или адреса (нулевой байт не используется для удобства работы с буфером).  */

         register lword  lax, lbx ;
         register word   ax ;//, w_tmp ;
         register byte   bh , bl , cl ;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;

          m_time = Timer1_Ovr - ( _TimeDoGasheniya - _MAvtoPovtor ) ;

          m_ext = _Monitor_start_page ;
          output_s ( _Monitor_prompt ) ;
          output_s ( MWelcome ) ;
          Label = 0 ;
        }

      /* Выбор и обработка данных из буфера приема до его опустошения */
while(  TestData_for_Input() )
  {
    mInput_c ( bh ) ;
    m_time = Timer1_Ovr ; /*  Для того, чтобы знать время последнего нажатия клавиши */

 /* if ( bh == _Stop )
      {                                  // 21.09.06 11:52
        mSet_AvarMsg ( _Av_UserBreak ) ; // для экономии сообщения ,
        continue ;                       // при необходимости ввести _Av_VR1 .
      } */

    switch ( Label )
      {
        default: Label = 0 ;
        case 0:
        case 1:
          if ( bh == Return )  /* Выход из монитора */
            {
              Pult_Prog_Addr = _MainPultProg  ;
              M_FirstCall = 1 ;
              return ;   /* добавить еще какую-то иниц.  */
            }
          else if (( bh == Enter ) || ( bh == Esc )) /* Приведение монитора в исходное состояние */
            {
              Label = 0 ;
              break ;
            }                          /* Режим 16-ричной побайтной адресации  */
          else if ( bh == 'c' )  Regim = 0x02u , B_W = 1 ;
                                   /* Режим 16-ричной пословной адресации  */
          else if ( bh == 'C' )  Regim = 0x04u , B_W = 2 ;
                                   /* Режим 10-ричной побайтной адресации без знака */
          else if ( bh == 'e' )  Regim = 0x3u , B_W = 1 ;
                                   /* Режим 10-ричной пословной адресации без знака */
          else if ( bh == 'E' )  Regim = 0x5u , B_W = 2 ;
                                   /* Режим 10-ричной побайтной адресации со знаком */
          else if ( bh == 'd' )  Regim = 0x14u , B_W = 1;
                                   /* Режим 10-ричной пословной адресации со знаком */
          else if ( bh == 'D' )  Regim = 0x6u , B_W = 2 ;
                                   /* Режим 10-ричной адресации длинными словами со знаком */
          else if ( bh == 'f' )  Regim = 0xBu , B_W = 4;
                                   /* Режим 10-ричной адресации длинными словами без знака */
          else if ( bh == 'F' )  Regim = 0xAu , B_W = 4;
                                   /* Режим 16-ричной адресации длинными словами */
          else if ( bh == 'G' )  Regim = 0x8u , B_W = 4;
                                   /* Режим ввода адреса запуска программы */
          //else if ( bh == '@' )  Regim = 0x1u  ;
                                   /* Режим ввода адреса сегмента памяти */
          else
            {
              Label = 1 ;
              Klav_Buff = bh ;
              break ;
            }
          output_c ( bh ) ;
          output_c ( '\'') ;
#if defined (_24_BITS_) || defined (_32_BITS_)
          output_c ( '(' ) ;
#ifndef  _32_BITS_
          m_ext &= 0x00FFu   ;   /* Срезаем мусор из расширения адреса.  */
#else
          bh = m_ext >> 12 ;
          bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
          output_c ( bh ) ;
          bh = (m_ext >> 8)&0xf ;
          bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
          output_c ( bh ) ;

#endif
          bh = (m_ext >> 4)&0xf ;
          bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
          output_c ( bh ) ;
          bh = m_ext & 0x000F ;
          bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
          output_c ( bh ) ;
      seg:
          output_c ( ')' ) ;
#endif
          Label = 10 , m_index = 0 ;
          break ;
        /*---------------  */
#if defined( _24_BITS_ ) ||  defined( _32_BITS_ )
      case 5:
              if ( bh == Esc )   /* Приведение монитора в исходное состояние */
                {
                  Label = 0 ;
                  break ;
                }
              else if ( bh == BckSp )
                {
                  if ( m_index-- != 0 )
                  {
                    output_s ("\b \b") ;
                  }
                  else
                  {
                    output_s ("\b \b\b \b\b \b") ;
                    Label = 1 ;
                  }
                  break ;
                }
              else
                {   /* Накопление вводимых цифр вводимого адреса */
                  if (( bh >= 0x30u ) && ( bh <= 0x39 ))       cl = bh - 0x30u ;
                  else if (( bh >= 0x41u ) && ( bh <= 0x46 ))  cl = bh - 0x37u ;
                       else if (( bh >= 0x61u ) && ( bh <= 0x66 ))  cl = bh - 0x57u ;
                            else
                            {
                              Klav_Buff = bh ;
                              break ;
                            }
                  output_c ( bh ) ;

                  ax = 0xf<< ((_Page_shift - m_index)*4);
                  m_ext &= ~ax;
                  m_ext  |= (w)cl << ((_Page_shift - m_index)*4) ;

                  if ( ++m_index > _Page_shift)
                  {
                    m_ext |= (w)cl ;
                    goto seg ;
                  }
                  break;
                }
#endif
           /*-----------------------------------------------------------------------*/
      case 10:
              if ( bh == Esc )   /* Приведение монитора в исходное состояние */
                {
                  Label = 0 ;
                  break ;
                }
              if ( m_index == 0 )
                {   /* Возврат к вводу команды */
                  if ( bh == BckSp )
                    {
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                        output_s ("\b \b\b \b\b \b") ;
#ifdef  _32_BITS_
                        output_s ("\b \b\b \b") ;
#endif
                        Label = 5 ;
#else
                      output_s ("\b \b\b \b") ;
                      Label = 1 ;
#endif
                      break ;
                    }
                  else if ( bh == Enter )
                         {
                           //if ( Regim == 1 ) break ;

                             /* Восстанов. предыдущего адреса.  */
                           Label = 60  ;
                           m_index = 0 ;
                             /* При пословной адресации сделать адрес четным */
                           if ( B_W == 2 ) m_addr &= 0xfffeu ;
                           else if (B_W == 4 )
                           {
                             /* При длиннословной адресации сделать адрес кратным 4 */
                              m_addr &= 0xfffcu ;
                           }
                           goto cse60 ;
                         }
                       else
                         {   /* Накопление вводимых цифр вводимого адреса */
                           if (( bh >= 0x30u ) && ( bh <= 0x39 ))       cl = bh - 0x30u ;
                           else if (( bh >= 0x41u ) && ( bh <= 0x46 ))  cl = bh - 0x37u ;
                                else if (( bh >= 0x61u ) && ( bh <= 0x66 ))  cl = bh - 0x57u ;
                                else
                                {
                                  Klav_Buff = bh ;
                                  break ;
                                }
                           m_buff [++m_index] = cl ;
                           output_c ( bh ) ;
                           break ;
                         }
                }
              else
                {   /* Затирание неверно набранной цифры */
                  if ( bh == BckSp )
                    {
                      m_index-- ;
                      output_s ("\b \b") ;
                      break ;
                    }
                  else if ( bh == Enter )
                         {
                              /* Вычисление введенного адреса по введеным цифрам */
                           for ( bl = 1 , m_addr = 0 ; bl <= m_index ; bl++ )
                             {
                               m_addr <<= 4  ;
                               m_addr &= 0xfff0u   ;
                               m_addr += (w) m_buff[bl]  ;
                             }
                           //if ( Regim == 1 )
                             //{               /* Запуск программы из монитора */
                             /*  asm_di()     ;  */
                             /*  asm_dpts()   ;  */

                                //(*(void (*) (void)) m_addr) () ;
                               //asm_rst()  ;
                             //}
                           //else /* При пословной адресации сделать адрес четным */
                                if ( B_W == 2 ) m_addr &= 0xfffeu ;
                                if ( B_W == 4 ) m_addr &= 0xfffcu ;

                           Label = 60  ;
                           m_index = 0 ;
                           goto cse60 ;
                         }
                       else if ( m_index < 4 )   /* адрес задается четырьмя 16-ричн. символами  */
                              {   /* Накопление вводимых цифр вводимого адреса ( не более 4-х) */
                                if (( bh >= 0x30u ) && ( bh <= 0x39 ))       cl = bh - 0x30u ;
                                else if (( bh >= 0x41u ) && ( bh <= 0x46 ))  cl = bh - 0x37u ;
                                     else if (( bh >= 0x61u ) && ( bh <= 0x66 ))  cl = bh - 0x57u ;
                                     else
                                      {
                                        Klav_Buff = bh ;
                                        break ;
                                      }
                                m_buff [++m_index] = cl ;
                                output_c ( bh ) ;
                                break ;
                              }
                            else break ;
                }
           /*-----------------------------------------------------------------------*/
      case 60:      /* Операция чтения/записи в память */
              if ( m_index == 0 ) /* обработка первого символа  */
                {
                  if ( bh == Esc )
                    {
                      Label = 0 ;  /* Приведение монитора в исходное состояние */
                      break ;
                    }
                      /* Повторить вывод содержимого данной ячейки */
                  else if ( bh == Enter )  ;
                      /* Перейти к выводу содержимого следующей ячейки */
                  else if ( bh == Up)     m_addr += B_W  ;
                      /* Перейти к выводу содержимого предыдущей ячейки */
                  else if ( bh == Down )  m_addr -= B_W  ;
                      /* Накопление вводимых цифр вводимого числа */
                  else
                    {
                      if (( Regim == 0x02 ) || ( Regim == 0x04 )|| ( Regim == 0x08 ))
                        {
                          if (( bh >= 0x30u ) && ( bh <= 0x39 ))       cl = bh - 0x30u ;
                          else if (( bh >= 0x41u ) && ( bh <= 0x46 ))  cl = bh - 0x37u ;
                          else if (( bh >= 0x61u ) && ( bh <= 0x66 ))  cl = bh - 0x57u ;
                          else
                          {
                            Klav_Buff = bh ;
                            break ;
                          }
                          m_buff [++m_index] = cl ;
                          output_c ( bh ) ;
                          break ;
                        }
                      else   // остальные десятичные режимы
                        {                   // десятичный режим без знака
                          if (( Regim == 3 ) || ( Regim == 5 )|| ( Regim == 10))
                            {
                              if (( bh >= 0x30u ) && ( bh <= 0x39 )) cl = bh - 0x30u ;
                              else
                              {
                                Klav_Buff = bh ;
                                break ;
                              }
                              m_buff [++m_index] = cl ;
                              output_c ( bh ) ;
                              break ;
                            }
                          else    /* десятичный режим со знаком  */
                            {
                              if ( bh == '_' ) /* <- код ввода отрицат. числа.  */
                                {
                                  m_buff [++m_index] = '-' ;
                                  output_c ( '-' ) ;
                                  break ;
                                }
                              else if (( bh >= 0x30u ) && ( bh <= 0x39 ))
                                {   /* если ввод начался с цифры - число полож.  */
                                  m_buff [++m_index] = '+' ;  /* принудительный вывод  */
                                  output_c ( '+' ) ; /*  знака.  */
                                    cl = bh - 0x30u ;
                                  m_buff [++m_index] = cl ;
                                  output_c ( bh ) ;
                                  break ;
                                }
                              else
                               {
                                  Klav_Buff = bh ;
                                  break ;
                               }
                    }   }   }
                }
              else  /* обработка последующих символов  */
                {   /* Повторить вывод содержимого данной ячейки */
                  if ( bh == Esc ) m_index = 0 ;
                  else if ( bh == BckSp ) /* Затирание неверно набранной цифры */
                    {
                      m_index-- ;
                      output_s ("\b \b") ;
                      break ;
                    }
                  else if ( bh == Enter ) /* Ввод числа окончен и подтвержден */
                    {   /* Преобразование введенного числа из набора цифр */
                      if (( Regim == 0x02 ) || ( Regim == 0x04 )|| ( Regim == 0x08 ))
                        {
                          lbx = (w) m_buff[1] ;
                          for ( bl = 2 ; bl <= m_index  ; bl++ )
                            {
                              lbx <<= 4  ;
                              lbx &= 0xfffffff0u   ;
                              lbx += (w) m_buff[bl]  ;
                            }
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                          lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                          if ( B_W == 1 )        *(fb*) lax = (b) lbx ;
                          else if ( B_W == 2 )   *(fw*) lax = (w)lbx  ;
                          else if ( B_W == 4 )   *(flw*) lax = lbx  ;
#else
                          if ( B_W == 1 ) *(b*) m_addr = (b) lbx ;
                          else if ( B_W == 2 )   *(w*)m_addr = (w)lbx  ;
                          else if ( B_W == 4 )   *(lw*)m_addr = lbx  ;
#endif
                        }
                      else if (( Regim == 3 ) || ( Regim == 5 )|| ( Regim == 10))
                        {
                          for ( lbx = 1 , lax = 0 ; m_index != 0 ; m_index-- )
                            {
                              lax +=  (lw)((w)m_buff[m_index]) * (lw) lbx ;
                               lbx *= 10u ;
                            }
                          if ( Regim == 3 )
                            {
                              if ( lax > 0x00ffu ) ax = 0x00ffu ;
                              else                 ax = (w) lax ;
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              *(fb*) lax    = (b) ax ;
#else
                              *( b*) m_addr = (b) ax ;
#endif
                            }
                          else if ( Regim == 5 )
                            {
                              if ( lax > 0xffffu ) ax = 0xffffu ;
                              else                 ax = (w) lax ;
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              *(fw*) lax    = ax ;
#else
                              *( w*) m_addr = ax ;
#endif
                            }
                            else
                            {
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lbx = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              *(flw*) lbx    = lax ;
#else
                              *( lw*) m_addr = lax ;
#endif

                            }
                        }
                      else
                        {
                          if ( m_index == 1 )  goto  cse60 ;
                          for ( lbx = 1 , lax = 0 ; m_index != 1 ; m_index-- )
                            {
                              lax +=  (lw)((w)m_buff[m_index]) * (lw) lbx ;
                               lbx *= 10u ;
                            }
                          if ( Regim == 0x14 )
                            {
                              if ( m_buff[1] == '-' )
                                {
                                  if ( lax > 0x0080u )  ax = 0x0080u ;
                                  else                  ax = ~(w)lax + 1 ;
                                }
                              else
                                {
                                  if ( lax > 0x007fu )  ax = 0x007fu ;
                                  else                  ax = (w) lax ;
                                }
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              *(fb*) lax    = (b) ax ;
#else
                              *( b*) m_addr = (b) ax ;
#endif
                            }
                          else if ( Regim == 0x6 )
                            {
                              if ( m_buff[1] == '-' )
                                {
                                  if ( lax > 0x8000u )  ax = 0x8000u ;
                                  else                  ax = ~(w)lax + 1 ;
                                }
                              else
                                {
                                  if ( lax > 0x7fffu )  ax = 0x7fffu ;
                                  else                  ax = (w) lax ;
                                }
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              *(fw*) lax    = ax ;
#else
                              *( w*) m_addr = ax ;
#endif
                            }
                            else
                            {
                              if ( m_buff[1] == '-' )
                                {
                                  lax = ~lax + 1 ;
                                }
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lbx = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              *(flw*) lbx    = lax ;
#else
                              *( lw*) m_addr = lax ;
#endif

                            }
                        }
                      m_index = 0 ;
                    }
                  else if ( bh == '^' )  /* команда наложения маски  */
                    {                   /* по "Искл.ИЛИ".  */
                      if (( Regim == 0x02 ) || ( Regim == 0x04 ) || ( Regim == 0x08 ))
                        {
                          for ( bl = 1 , lax = 0 ; bl <= m_index  ; bl++ )
                            {
                              lax <<= 4  ;
                              lax &= 0xfffffff0u   ;
                              lax += (w) m_buff[bl]  ;
                              output_c ( BckSp ) ;
                            }
                          output_c ( BckSp ) ;
                          output_c ( '^' ) ;
                          if ( B_W == 1 )
                            { bl = (b) lax ;// <- чтобы уменьшить количество команд между 'di' и 'ei'.
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              asm_di() ;
                              bl ^= *(fb*) lax ;
                              *(fb*) lax = bl ;
                              asm_ei() ;
#else
                              asm_di() ;
                              bl ^= *(b*) m_addr ;
                              *(b*) m_addr = bl ;
                              asm_ei() ;
#endif
                            }
                          else if ( B_W == 2 )
                            { ax = (w)lax;
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              asm_di() ;
                              ax ^= *(fw*) lax ;
                              *(fw*) lax = ax  ;
                              asm_ei() ;
#else
                              asm_di() ;
                              ax ^= *(w*) m_addr ;
                              *(w*) m_addr = ax  ;
                              asm_ei() ;
#endif
                            }
                            else
                            {
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                              lbx = ( (lw)m_ext << 16 ) + (lw)m_addr ;
                              asm_di() ;
                              lax ^= *(flw*) lbx ;
                              *(flw*) lbx = ax  ;
                              asm_ei() ;
#else
                              asm_di() ;
                              lax ^= *(lw*) m_addr ;
                              *(lw*) m_addr = lax  ;
                              asm_ei() ;
#endif
                            }
                        }
                      m_index = 0 ;
                    }
                      /* Накопление вводимых цифр вводимого числа */
                  else if ( m_index < ( Regim & 0x0F ) ) /* маска чтобы отсеч старшую тетераду,  */
                    {             /* так как число вводимых цифр совпадает в режимах 0x4 и 0x14.  */
                      if (( Regim == 0x02 ) || ( Regim == 0x04 )|| ( Regim == 0x08 ))
                        {
                          if (( bh >= 0x30u ) && ( bh <= 0x39 ))       cl = bh - 0x30u ;
                          else if (( bh >= 0x41u ) && ( bh <= 0x46 ))  cl = bh - 0x37u ;
                          else if (( bh >= 0x61u ) && ( bh <= 0x66 ))  cl = bh - 0x57u ;
                          else
                            {
                              Klav_Buff = bh ;
                              break ;
                            }
                          m_buff [++m_index] = cl ;
                          output_c ( bh ) ;
                          break ;
                        }
                      else   /* остальные десятичные режимы  */
                        {
                          if (( bh >= 0x30u ) && ( bh <= 0x39 )) cl = bh - 0x30u ;
                          else
                            {
                              Klav_Buff = bh ;
                              break ;
                            }
                          m_buff [++m_index] = cl ;
                          output_c ( bh ) ;
                          break ;
                        }
                    }
                    else
                    {
                      Klav_Buff = bh ;
                      break ;
                    }
                }
    cse60:
              output_c ( CR ) ;
              output_c ( LF ) ;

                /* Вывод текущего адреса сегмента */
#ifdef _32_BITS_
              bh = m_ext >> 12 ;
              bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
              output_c ( bh ) ;
              bh = (m_ext >>  8) &0x0f;
              bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
              output_c ( bh ) ;
#endif
#if defined  (_24_BITS_ )  || defined  (_32_BITS_ )
              bh = (m_ext >> 4)&0x0f ;
              bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
              output_c ( bh ) ;
              bh = m_ext & 0x000F ;
              bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
              output_c ( bh ) ;
              output_c ( '\'' ) ;
#endif
#ifdef _32_BITS_
             output_s ( "\r\n" ) ;
#endif
              /* Вывод текущего адреса и содержимого ячейки по этому адресу */
                 /* Преобразование адреса в символьный вид и вывод */
              for ( bl = 3 ; (signed char) bl  >= 0 ; bl -- )
                {
                  bh = (b)( m_addr >> 4u*bl ) & 0x0fu ;
                  bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                  output_c ( bh ) ;
                }
              output_c ( '=' ) ;

                 /* Считывание байта или слова по введеному адресу */
#if defined  (_24_BITS_ )  || defined  (_32_BITS_ )
              lax = ( (lw)m_ext << 16 ) + (lw)m_addr ;
              if ( B_W == 1 )       lbx = (lw)(*(fb*) lax)  ;
              else if ( B_W == 2 )  lbx = (lw)(*(fw*) lax)  ;
              else                  lbx =     *(flw*) lax ;
#else
              if ( B_W == 1 )      lbx = (lw)(*(b*) m_addr)  ;
              else if ( B_W == 2 ) lbx = (lw)(*(w*)m_addr)  ;
              else                 lbx =     *(lw*)m_addr ;
#endif
                 /* Преобразование считанного байта или слова данных в символьный вид и вывод */
              if (( Regim == 0x02 ) || ( Regim == 0x04 ) || ( Regim == 0x08 ))
                {
                  for ( bl = Regim - 0x1u ; (signed char) bl >= 0 ; bl -- )
                    {
                      bh = (b)( lbx >> 4u*bl ) & 0x0fu ;
                      bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                      output_c ( bh ) ;
                    }
                }
              else
              {
                if (( Regim == 10) || ( Regim == 11))
                {
                  lax = 1000000000;
                  if ( Regim == 11)
                    {
                      if ( (slw)lbx < 0 )
                        {
                          lbx = ~lbx+1 ;
                          output_c ( '-' ) ;
                        }
                      else output_c ( '+' ) ;
                    }
                }
              else if (( Regim == 5 ) || ( Regim == 6 ))
                {
                  lax = 10000;
                  if ( Regim == 6 )
                    {
                      if ( lbx > 0x7fffu )
                        {
                          lbx ^= 0xffff ;
                          lbx++ ;
                          output_c ( '-' ) ;
                        }
                      else output_c ( '+' ) ;
                    }
                  /*lax = (lw)ax ;
                   lbx=lax/10000 ;
                  output_c ( (b)((w)lbx) + 0x30 ) ;
                  lax %= 10000 ;
                  lbx=lax/1000 ;
                  output_c ( (b)((w)lbx) + 0x30 ) ;
                  ax = lax % 1000 ;
                  w_tmp = ax / 100 ;
                  output_c ( (b)w_tmp + 0x30 ) ;
                  ax %=100  ;
                  w_tmp = ax/10 ;
                  output_c ( (b)w_tmp + 0x30 ) ;
                  ax %=10 ;
                  output_c ( (b)ax + 0x30 ) ;
                  output_c ( '.' ) ;*/
                }
              else
                {
                  lax = 100;
                  if ( Regim == 0x14 )
                    {
                      if ( lbx > 0x7fu )
                        {
                          lbx ^= 0x00ffu  ;
                          lbx++ ;
                          output_c ( '-' ) ;
                        }
                      else output_c ( '+' ) ;
                    }
                /*  w_tmp = ax/100u ;
                  output_c ( (b)w_tmp + 0x30 ) ;
                  ax %= 100 ;
                  w_tmp =ax/10u ;
                  output_c ( (b)w_tmp + 0x30 ) ;
                  ax %= 10 ;
                  output_c ( (b)ax + 0x30 ) ;
                  output_c ( '.' ) ;*/
                }

                while (lax >=1)
                {
                    bh = lbx/lax ;
                    output_c ( bh + 0x30 ) ;
                    lbx %= lax ;
                    lax /=10;
                };
                output_c ( '.' ) ;
              }
              output_c ( ',' ) ;
              break ;
      }

    if ( Label == 0 )  output_s ( MWelcome ) ;
  }
     // Выдержка времени после последнего нажатия клавиши и "гашение" монитора
/*  ax = Timer1_Ovr- m_time;
  if ( (u)ax >= (u)_TimeDoGasheniya )
    {
      Label = 0 ;
         //  Для того, чтобы периодически выводить приглашение
      m_time +=_MAvtoPovtor ;
          //  Если буфер вывода занят, то нечего туда напихивать приглашений.
    if (  TestCompleted_Output() )  output_s ( MWelcome ) ;
    }
*/
 Restart_Output ()  ;

  return ;
}

  void  output_ch ( void )
{
    mOutput_c ( m_ch ) ;
  return ;
}

  void  Restart_Output ( void )
{
   mRestart_Output ()  ;
   return ;
}

  word  TestData_for_Input ( void )
{
   return mTestData_for_Input() ;
}

  word  TestCompleted_Output ( void )
{
   return  mTestCompleted_Output() ;
}

/*---------------------------------------------------------*/
/*    В прерываниях лучше этой функцией не пользоваться.  */
/* Программа вывода на последовательный порт строки.  */
/* В качестве параметра программе передается адрес начала строки.  */
/* Строка должна завершаться нулем.  */
/*   Программа заносит строку в буфер и не ожидая завершения вывода  */
/* выходит из себя.  */

  void  output_str ( void )
{
  while( mTestFreeSpace_for_Output() && (*str_addr != 0) ) // NULL 07.12.07 14:09
    {
      mOutput_c ( *(str_addr++) ) ;
    }

  Restart_Output ()  ;

  return ;
}
// KVV_backup
  void  output_whex ( word value )
{
    byte ah;

    ah = (value>>12) & 0x000f;     mOutput_c ( ah < 10 ? '0'+ ah : 'A'+(ah-10) ) ;
    ah = (value>> 8) & 0x000f;     mOutput_c ( ah < 10 ? '0'+ ah : 'A'+(ah-10) ) ;
    ah = (value>> 4) & 0x000f;     mOutput_c ( ah < 10 ? '0'+ ah : 'A'+(ah-10) ) ;
    ah = (value>> 0) & 0x000f;     mOutput_c ( ah < 10 ? '0'+ ah : 'A'+(ah-10) ) ;

  Restart_Output ()  ;

  return ;
}


//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-

         // Очистка кодов из буфера с выдержкой времени.
void  Test_Klav_buff( void )
{
  static word time_klav ;

  if ( Klav_Buff != 0 )
  {         // Иммитируем нажатую кнопку: с выдержкой времени снимаем код.
    if ( (u)((w)(Timer1_Ovr - time_klav)) > _Sec(0.25) ) Klav_Buff = 0 ;
  }
  else time_klav = Timer1_Ovr ;

  return ;
}

/*-----------------------------------------------------  */
/*    Управляющий воспринимает и одно- и двух-символьные команды  */
/*  завершенные  нажатием клавиши "Enter".  */
/*    Текст введенной команды помещается в двухбайтную ячейку  */
/*  "Pult_Prog_Addr" для обработки этой команды какой-либо другой  */
/*  программой вне управляющего.  */
/*    При при двухсимвольной команде в младший байт помещается первый  */
/*  введенный символ, а в старший - второй.  */
/*    При односимвольной - в младший байт - введенный символ, а в  */
/*  старший - нуль.  */
/*    По коду в этой ячейке где-то наруже вызывается нужная программа,  */
/*  которая подменяет собой диспетчера. При необходимости снова вернуть  */
/*  управление диспетчеру эта активная программа должна записать в ячейку  */
/*  "Pult_Prog_Addr" нули.  */

void  Pult_Dispetcher ( void )
{
/*  m_timer  - Время последнего любого нажатия клавиши.  */
/*  m_index  - Cчетчик введенных символов в буфер x.Buff[] .  */

  register byte bh ;
  register word ax;
  static  union {
                  byte Buff[2] ; /*  Буфер вводимых символов  */
                  word Code    ;
                }  x ;


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          m_time = Timer1_Ovr - ( _TimeDoGasheniya - _MAvtoPovtor ) ;
          output_s ( _Dispet_prompt ) ;
          output_s ( DWelcome ) ;
          m_index = 0 ;
          x.Code = 0 ;
        }

      /* Выбор и обработка данных из буфера приема до его опустошения */
    while(  TestData_for_Input() )
      {
        mInput_c ( bh ) ;
        m_time = Timer1_Ovr ; /*  Для того, чтобы знать время последнего нажатия клавиши */

              if ( ( bh >= 'A'  &&  bh <= 'J' )
                                ||
                   ( bh >= '0'  &&  bh <= '9' )
                                ||
                   ( bh >= 'a'  &&  bh <= 'j' ) )
                {
                  if ( m_index < 2 )
                    {
                      x.Buff[m_index++] =  bh ;
                      output_c ( bh ) ;
                    }
                }
              else if ( m_index == 0 )
                {
                  if ( bh == Enter ) //|| ( bh == Esc ))  // Вызов меню.
                    {
                      Pult_Prog_Addr = _NortonPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Esc )  /* Повторное приведение диспетчера в исходное состояние */
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      //output_s ( DWelcome ) ;
                    }
                  else Klav_Buff = bh ;
                }
              else
                {     /* Возврат к вводу команды и */
                  if ( bh == Esc )  /* приведение диспетчера в исходное состояние */
                    {
                      m_index = 0 ;
                      x.Code = 0 ;
                      output_s ( DWelcome ) ;
                    }
                  else if ( bh == BckSp )
                    {         /* Затирание неверно набранной цифры */
                      x.Buff[--m_index] =  0 ;
                      output_s ("\b \b") ;
                    }
                  else if ( bh == Enter )
                    {     // Склеиваем младший байт со старшим, чтобы не зависить
                         // от толкования компилятором "union".
                      Pult_Prog_Addr = (w)x.Buff[0] + ((w)x.Buff[1] << 8) ;
                      M_FirstCall = 1 ;
                      return ;
                    }
                  else Klav_Buff = bh ;
                }
      }
   if ( DWell_old != DWelcome)
   {
       DWell_old = DWelcome;
       goto prm ; //output_s ( DWelcome );
   }
     /* Выдержка времени после последнего нажатия клавиши и "гашение" диспетчера */

  ax = Timer1_Ovr- m_time;

  if ( (u)ax >= (u)_TimeDoGasheniya )
    {
           /*  Для того, чтобы периодически выводить приглашение */
      m_time += _MAvtoPovtor ;
 prm: m_index = 0 ;
      x.Code = 0 ;
          /*  Если буфер вывода занят, то нечего туда напихивать приглашений.  */
      if (  TestCompleted_Output() )  output_s ( DWelcome ) ;
    }

 Restart_Output ()  ;

  return ;
}
/*----------------------------------------  */

//   Вход в Останов с переспрашиванием.

void   FA_Ostanov ( void )
{
  register byte bh ;
      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2, i3 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          output_s ( _Ostanov_Prompt ) ;
          M_FirstCall = 0 ;
          Label = 0 ;
          m_index = 0;
            //---
          if ( Prg._.Gotovn == 0 )
          {
            output_s ( _Dostup_Gotovn_txt ) ;
            m_time = Timer1_Ovr,  Label = i3 ;
          }
        }

    switch ( Label )
     {
      default:
      case i0: output_s ( "\n" ) ;
               Label = i1 ;
      case i1:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _OstanovNo_txt  ) ;
              else                output_s ( _OstanovYes_txt ) ;
              Label = i2 ;
              break ;
            }

      case i2:

          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  // Выход из этого режима
                    {
                 end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( bh == Up || bh == Down ) // Изменить выбор.
                    {
                      m_index = ~m_index,  Label = i1 ;
                    }
                  else if ( bh == Enter )
                    {
                      if ( m_index == 0 ) goto end ;
                      Av._.Ostanov = 1 ;
                      goto end ;
                    }
                  else    Klav_Buff = bh;
            }
          break ;

      case i3:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) )  goto end;
          break ;
     }
  return ;
}

/*----------------------------------------  */

//----------------------------------------------------------
const struct AboutMenu TxtAbout[ ] =
{
  { _Type_Agregat_txt, _Device_Name_, 0 },
  { _DateTime_txt,     __DATETIME__,  0 },
#ifdef _PROGRAM_
  { _Type_Program_txt, _PROGRAM_,     0 },
#endif
#ifdef _DECIMAL_
  { _Decimal_txt,      _DECIMAL_,     0 },
#endif
  {  _Size_i2c_txt,    "",            1 },
  {  _ObjectOblUst,    "",            2 }
};

const word TxtAbout_size = sizeof( TxtAbout )/sizeof( struct AboutMenu );
//----------------------------------------------------------

//   Программа вывода сведений о версии ПО .
void  About ( void )
{
      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2, i3, i4, i5, i6, i7, i8 };

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          Label = i0 ;
          m_index = 0 ;
        }

    switch ( Label )
     {
      default:
      case i0:
               output_s ( _About_Prompt ) ;
               output_s ( "\n" ) ;
               Label = i1 ;
      case i1:
               if ( TestCompleted_Output() )
                {
                  output_c( '\r');
                  output_s( AWelcome );
                  Label = i2 ;
                  break ;
                }
      case i2:
               if ( TestCompleted_Output() )
                {
                  output_s( TxtAbout[ m_index ].txt1 ) ;
                  Label = i3 ;
                  break ;
                }
      case i3:
               while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      output_s( "\n\r");
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_index >= TxtAbout_size ) m_index = 0 ;
                      Label = i0 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( m_index-- == 0 ) m_index = TxtAbout_size - 1 ;
                      Label = i0 ;
                    }
                  else if ( m_ch == Enter )
                    {
                      Label = i5 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
               break ;

      case i4:
               output_c( '\r');
               output_s( AWelcome );
               Label = i2 ;
               break ;

      case i5:
               if ( TestCompleted_Output() )
                 {
                   //output_c( 0x08 ); // Забой символа .
                   output_s( ":\n\r");

                   switch ( TxtAbout[ m_index ].label )
                    {
                     default:
                        output_s( TxtAbout[ m_index ].txt2 ) ;
                        break ;

                     case 1:

                        switch ( _i2c_end )
                        {
                            case 0x1fff:
                                 output_s( _Size_i2c_8kb_txt ) ;
                                 break ;
                            case 0x7fff:
                                 output_s( _Size_i2c_32kb_txt ) ;
                                 break ;
                            case 0xffff:
                                 output_s( _Size_i2c_64kb_txt ) ;
                                 break ;
#ifdef _CM3_ // у Fujitsu эта переменная типа "word" :
                            case 0x7ffff:
                                 output_s( _Size_i2c_512kb_txt ) ;
                                 break ;
#endif
                            default:
                                 output_s( _Size_i2c_No_txt ) ;
                                 break ;
                        }

                        break ;

                     case 2:
                        if( _kol_obl > 1 )
                        {
                            if ( copy_code_rezerv == 0 ) output_s( _AgregatOut_txt ) ;
                            else                         output_s( Tabl_name_ust[ copy_code_rezerv - 1 ] ) ;
                        }
                        else                             output_s( Tabl_name_ust[ 0 ] ) ;
                        break ;
                    }

                   Label = i6 ;
                   break ;
                 }

      case i6:
               while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return || m_ch == Enter )
                    {
                      output_c ( '\n' ) ;
                      Label = i0 ;
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

/*----------------------------------------  */

//   Программа инициализации стоповых точек процессора и записи точек
// возможного зависания .

void Init_Stop_Point ( void )
{
  stop_point  = stop_point1  ; // запись стоповой точки фоновой программы .
  stop_pointS = stop_pointS1 ; // запись стоповой точки прерывания СИФУ .
  stop_pointV = stop_pointV1 ; // запись стоповой точки прерывания СИФУВ/СИФУ2 .
  stop_pointP = stop_pointP1 ; // запись стоповой точки прерывания ПДФ .
  stop_pointD = stop_pointD1 ; // запись стоповой точки прерывания DP .
  stop_pointR = stop_pointR1 ; // запись стоповой точки прерывания Реверс .

  return ;
}

/*----------------------------------------  */

//   Программа подсчета времени работы агрегата и чтения/записи
// часов работы в энергонезависимую память ЭОЗУ часов .

//   Программа использует для подсчета времени наработки секунды из часов реального времени в I2C .
//   Счетчик считает до 60 000 часов , потом переполняется , количество переполнений запоминается .
//   Всего 1369 лет непрерывной работы... Должно хватить...

//   Из-за того, что секунды часов реального времени в конце каждой минуты на секунду "зависают" ,
// счетчик "накалывается" каждую минуту на одну секунду в сторону увеличения... Серега говорит ,
// что так и должно быть, что это синхронизируется время...

#ifdef _NARABOTKA
void Narabotka ( word code )
{
  enum  { k0, k1, k2, k3, k4 } ;

  static word  time ;
// #ifndef _CM3_  // 17.10.19 FAA вернульсь на сохранение по станд. с i2c
  if ( code == 0 )
   {
     //---
      // Для записи во флэш-память часов переменной счетчика отключений :

#ifndef _CM3_
      RAB.addr_i2c =  _clock_i2c_beg ;  // 8 // 9 ; // адрес начала массива в i2с .
      RAB.chip_addr=  _Adr_Clock_i2c ;  // адрес микросхемы на шине i2c, в которую будет производится запись .
#else
      RAB.addr_i2c =  NarabSpaceBeg ; //_clock_i2c_beg ;  // 8 // 9 ; // адрес начала массива в i2с .
      RAB.chip_addr=  _Adr_Flash_i2c; //_Adr_Clock_i2c ;  // адрес микросхемы на шине i2c, в которую будет производится запись .
#endif
      RAB.addr_mem = (b*)&NARAB_buff ;  // адрес начала массива в оперативной памяти .
      RAB.size     =  sizeof(NARAB) ;//5 ;   // размер массива  - 5 байт .
      RAB.code     =  0 ;               // код операции - 1 - запись в i2c .
                                        // все остальное -   чтение из i2c .
      i2c_str = &RAB ;                  // Структура для работы с данными по i2c .
      i2c_lab = k0 ;                    // Для свича чтения записи слова кол-ва срабатываний .
     //---
      narab.all = 0 ;                   // Обнуляем рабочую структуру .
      time = Timer1_Ovr ;
     //---
#ifdef _OBJ_Narabotka
      Obj_Narabotka ( 0 ) ;
#endif
   }
  else
   {
      switch ( i2c_lab )
        {
          default :
          case k0 :
           narab._.rab_rd = 1 ; // выставляем флаг требования чтения .
           i2c_lab = k1 ;
          break;
           //---
          case k1 :
           if      ( narab._.rab_rd == 1 ) i2c_lab = k2 ;  // переход на ветку чтения .
           else if ( narab._.rab_wr == 1 ) i2c_lab = k3 ;  // переход на ветку записи .
          break;
           //---
          case k2 :
            // чтение переменной из ЭОЗУ при загрузке :
           if      ( narab._.rab_rd == 1 && Write_dat_i2c == 0 )
            {
              // Чтение количества часов работы из ЭОЗУ .
              Write_dat_i2c  = 1 ; // Переменная для работы программы : 0 - не работает , 1 - работает .
              narab._.rab_rd = 0 ; // снимаем флаг требования записи .
              RAB.code = 0 ;       // код операции - 0 - чтение из i2c .
              narab._.load_ok = 0 ; // на всякий случай.
            }
           else if ( Write_dat_i2c == _Error_Wr_ust )
            {
              mSet_ServiceMsg( _Srv_ErrRdClock_i2c ) ;
              narab._.load_ok = 1 ; // все равно разрешаем счет наработки.
              Write_dat_i2c  = 0 ; // Переменная для работы программы : 0 - не работает , 1 - работает .
              i2c_lab = k1 ;       // переход на метку ожидания чтения/записи .
            }
           else if ( Write_dat_i2c == 0 )  // чтение произошло :
            {

    #ifndef _BTE
              NARAB = NARAB_buff ;
    #else
                // берем данные из NARAB_buff если там не хлам т.к. в 590 - NARAB_buff считывается из часов
              if( NARAB_buff.Start_z.Contrl_sum == _CONTR_CODE_TIP_UST )   NARAB = NARAB_buff ;
    #endif
              narab._.load_ok = 1 ; // разрешаем счет наработки.

              i2c_lab = k1 ; // переход на метку ожидания чтения/записи .
              //output_s ( "\r\n Чтение-Ok." ) ;
            }
          break;
           //---
          case k3 :
            // запись переменной в ЭОЗУ :
           if ( narab._.rab_wr == 1 && Write_dat_i2c == 0 )
            {
              // Запись количества срабатываний предварительной защиты в ПЗУ .
              Write_dat_i2c  = 1 ; // Переменная для работы программы : 0 - не работает , 1 - работает .
              narab._.rab_wr = 0 ; // снимаем флаг требования записи .
              RAB.code = 1 ;       // код операции - 1 - запись в i2c .
                //---
              NARAB_buff = NARAB ;
            }
           else if ( Write_dat_i2c == _Error_Wr_ust )
            {
              mSet_ServiceMsg( _Srv_ErrWrClock_i2c ) ;
              Write_dat_i2c  = 0 ; // Переменная для работы программы : 0 - не работает , 1 - работает .
              i2c_lab = k1 ;       // переход на метку ожидания чтения/записи .
            }
           else if ( Write_dat_i2c == 0 )  // запись произошла :
            {
              i2c_lab = k1 ;       // переход на метку ожидания чтения/записи .
              RAB.code = 0 ;       // код операции - 0 - чтение из i2c .
              //output_s ( "\r\n Запись-Ok." ) ;
            }
          break;
           //---
        }
/*
#else  // #ifndef _CM3_
  if ( code == 0 )
   {
      narab.all = 0 ;                   // Обнуляем рабочую структуру .
      time = Timer1_Ovr ;
      narab._.rab_rd = 1 ; // выставляем флаг требования чтения .
#ifdef _OBJ_Narabotka
      Obj_Narabotka ( 0 ) ;
#endif
   }
  else
   {
	   if ( narab._.rab_rd == 1 )
	   {
		  NARAB = NARAB_buff ;
		  narab._.rab_rd = 0;
		  narab._.load_ok = 1;
	   }
	   if ( narab._.rab_wr == 1 )
	   {
		  NARAB_buff = NARAB;
		  narab._.rab_wr = 0;
	   }


#endif // #ifndef _CM3_
*/
        //------------------------------------------------------------------------

         // Собственно подсчет времени наработки в часах :
        if ( Prg._.Gotovn == 0 && bo_Avar == 0 )
         {
            // Используем секунды из часов реального времени в I2C :
            // Перевод из двоично-десятичного кода в десятичный .
            Nsec = (b)(c_time.b[0]>>4)*10+(c_time.b[0]&0x0f) ; // Новая секунда .
            //---
            if ( narab._.rab_beg == 0 ) // Начинаем считать время .
             {
                 narab._.rab_beg = 1 ;  // Взводим флаг начала работы ,
                 old_sec = Nsec ;       // зарядка детектора новой секунды .
             }
            if ( Nsec != old_sec ) // детектируем новую секунду :
             {
                 narab._.new_sec = 1 ;  // Взводим флаг новой секунды .
                 old_sec = Nsec ;       // Зарядка детектора новой секунды .
             }
            //-----------------------------------
            if ( narab._.new_sec == 1 ) // Появилась новая секунда - прибавляем ее к наработке .
             {
               if ( (b)NARAB.sec < (b)59 ) NARAB.sec++ ;
               else
                {
                  NARAB.sec = 0 ;
                  //---
                  if ( (b)NARAB.min < (b)59 ) NARAB.min++ ;
                  else
                   {
                     NARAB.min = 0 ;
                     //---
                     if ( (u)(w)NARAB.hou < (w)60000 ) NARAB.hou++ ;
                     else
                      {
                        NARAB.hou = 0 ;
                        //---
                        if ( (u)(w)NARAB.ovr < (w)200 ) NARAB.ovr++ ;
                      }
                   }
                }
               //narab._.new_sec = 0 ; // сброс флага новой секунды - перенесено ниже .
             }
         }
        else if ( narab._.rab_beg == 1 ) // Если вышли из работы :
         {
           narab._.rab_beg = 0 ;  // Обнуляем флаг работы .
           //narab._.rab_wr  = 1 ;  // Выставляем флаг требования записи .
         }

         //-----------------

#ifdef _OBJ_Narabotka
        Obj_Narabotka ( 1 ) ; //  Другие счетчики из объектных программ.
#endif
        //Чтобы использовать флаг секунды в объектных программах обнуляем его
        if ( narab._.new_sec == 1 ) narab._.new_sec = 0 ; // сброс флага новой секунды .
         //-----------------

            //  Блокировать пока не загружены прежние значения счетчиков из I2C.
        if (  narab._.load_ok == 0 ) return  ;

            //  Раз в минуту записываем счетчики в ЭОЗУ часов.
        if ( (u)(w)(Timer1_Ovr - time) >= _Sec ( 60 ) )
        {
          time = Timer1_Ovr ;
            //---
          narab._.rab_wr  = 1 ;  // Выставляем флаг требования записи .
        }

   }
  return ;
}
#endif

/*!
* @brief  Функция отправляет команду на пультовый терминал
* @param  Comand - код команды, описывается в @file monitor.h
* @param  Params - массив параметров
* @param  NumbParams количество параметров в массиве
* @date   14.06.2023
* @authors Sergey Tur
*/

void SendCommandToPult(byte Comand, byte *Params, byte NumbParams)
{
  word i;
  //Переводим пульт в режим команды
  output_c ( _ComPref ) ;
  output_c ( Comand ) ;
  if (Params != NULL)
  {
    for (i=0; i <  NumbParams; ++i)
    {
      output_c ( Params[i] ) ;
    }
  }
  Restart_Output ()  ;

}


/*!
* @brief  Функция отправляет команду без параметров на пультовый терминал
* @param  Comand - код команды, описывается в @file monitor.h
* @date   14.06.2023
* @authors Sergey Tur
*/

void SendEasyCommandToPult(byte Comand)
{
  SendCommandToPult(Comand, NULL , 0) ;
}


