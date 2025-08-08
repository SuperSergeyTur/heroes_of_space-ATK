
/*   Программа тестирования памяти i2c.
   Тестирование производится с адреса _i2c_beg до адреса _i2c_end.
   При тестировании затирается прежнее содержимое памяти. По-этому
   тестирование производится в ОСТАНОВЕ и после тестирования следует
   записать уставки еще хранящиеся в ОЗУ в i2c.
     При тестировании в память записывается последовательно числа
   1...256,1...256, и т.д., а затем последовательно считаваются и
   проверяются.
     После тестирования выдаются соответствующие результатам сообщения.
 */

void Test_i2c ( void )
{
   byte bh , bl ;
   register word ax ;
   word bx ;

   char *ptr ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i11, i12, i2, i3, i4 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          output_s ( _Test_EOZU_txt "\r\n") ;
          M_FirstCall = 0 ;
          Label = 0 , m_index = 0 ;
          return ;
        }

    switch ( Label )
    {
      default: Label = i0;
      case i0:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 )
              {
                output_s ( _Test_i2c_txt  ) ;
                m_ext  =  _i2c_beg ;
                m_time =  _i2c_end ;
                m_addr = (w)_Adr_Flash_i2c ;
              }
#ifdef _Adr_Clock_i2c
              else
              {
                output_s ( _Test_clock_txt ) ;
                m_ext  = _clock_i2c_beg ;
                m_time = _clock_i2c_end ;
                m_addr = (w)_Adr_Clock_i2c ;
              }
#endif
              Label = i1 ;
              break ;
            }

      case i1: // Обработка символов из буфера ввода, без 'while
               // до опустошения' (т.к. при ручном вводе этого не надо)
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* Выход из этого режима */
                {
             end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  return ;   // добавить еще какую-то иниц.
                }
#ifdef _Adr_Clock_i2c
              else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                {
                  m_index = ~m_index,  Label = i0 ;
                }
#endif
              else if ( bh == Enter )
                {
                  output_s ( "\n") ;
                  m_index = 0 ;
                  Label = i11 ;
        }       }
          break ;
    //-----------------
      case i11:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _Test_No_txt  ) ;
              else                output_s ( _Test_Yes_txt ) ;
              Label = i12 ;
              break ;
            }

      case i12: // Обработка символов из буфера ввода, без 'while
               // до опустошения' (т.к. при ручном вводе этого не надо)
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* Выход из этого режима */
                {
            povt: output_s ( _Test_EOZU_txt "\r\n") ;
                  Label = 0 , m_index = 0 ;
                }
              else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                {
                  m_index = ~m_index,  Label = i11 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto povt ;
                  output_s ( _Waiting_txt "\n\r") ;
                  Label = i2 ;
        }       }
          break ;
    //-----------------

      case i2:
             // 29.11.2012 13:43 можем попасть на опрос часов, маловероятно, но может повезти
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина

            //  заранее укладываем концовку текста адреса т.к. она всегда постоянная.
          m_buff[4] = 'h', m_buff[5] = '\r', m_buff[6] = 0 ;//NULL ;
            //  Запись в память последовательно чисел 1...256,1...256, и т.д.
          for ( bx = m_ext ; bx <= m_time ; bx++ )
           {
#ifdef _WatchDog
          watchdog_reset(); // сброс сторожа
#endif
                /* Преобразование адреса в символьный вид и вывод */
             for ( bl = 3 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[3-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------
             bh = bx ;
             ax = Save_into_i2c ( 1, &bh, bx, (b)m_addr ) ;
             if ( ax != 0 )  goto end1;
           }
  
            // Считывание последовательно из памяти ранее занесенных данных.
          for ( bx = m_ext ; bx <= m_time ; bx++ )
           {
#ifdef _WatchDog
          watchdog_reset(); // сброс сторожа
#endif
                /* Преобразование адреса в символьный вид и вывод */
             for ( bl = 3 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[3-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

             ax = Load_from_i2c ( 1, bx, &bh, (b)m_addr ) ;
             if ( ax != 0 )
               {
           end1: ptr = _NoConnect_i2c_txt ;
                 goto end2;
               }
               //   Проверка после каждого считывания на соответствие ранее
               // занесенным данным.
             if ( bh != (b)bx )
               {
                 ptr = _Error_i2c_txt ;
           end2: output_s ( m_buff ) ; // вывод конечного адреса остановки.
                 m_time = Timer1_Ovr ;
                 Label = i3 ;
                 goto end3; // break; 24.11.2023 Даже при ошибке писал "Ok" из-за подмены ptr
               }
             while ( TestCompleted_Output() == 0 );
           }
         ptr = "  Ok. "  ;
   end3:
         output_s ( ptr ) ; // вывод (не)исправности.
         m_time = Timer1_Ovr ;
         Label = i4 ;
         break;

      case i3:
         if ( (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0) ) break;
         goto end3;

      case i4:
         if ( (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0) ) break;
         goto end;
    }

  return ;
}


