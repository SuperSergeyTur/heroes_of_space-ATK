
//const char *c_Programm[2] = { "\rПеревiрка ОЗП   ", "\rПеревiрка запису"};

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
 //register word ax ;
   static slword ret;
 //lword bx ;

 //char *ptr ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i11, i12, i2 , i21 , i22 , i23 , i24 , i3 };


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задани
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
             end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  //Last_Av = 0;
                }
              else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                {
                  m_index = ~m_index,  Label = i0 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto end ;
                  output_s ("\r\n");
                  m_index = 0;
                  Label = i2 ;
        }       }
          break ;
    //-----------------

      case i2:
          if ( TestCompleted_Output() )
            {
              if (m_index == 0)
              {
                output_s ( c_Programm[0] ) ;
              }
              else
              {
                output_s ( c_Programm[1] ) ;
              }
              Label = i21 ;
              break ;
            }
    case i21:

      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* Выход из этого режима */
                {
                  goto end;
                }
              else if ( bh == Up || bh == Down ) /* Изменить выбор. */
                {
                  m_index = ~m_index,  Label = i2 ;
                }
              else if ( bh == Enter )
                {
                  output_s ( _Waiting_txt "\n\r") ;
                    Label = i22 ;
                }
        }
          break ;
    case i22:
             // 29.11.2012 13:43 можем попасть на опрос часов, маловероятно, но может повезти
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина

            //  заранее укладываем концовку текста адреса т.к. она всегда постоянная.
                 m_buff[5] = 'h', m_buff[6] = '\r', m_buff[7] = 0 ;//NULL ;
/*          //  Запись в память последовательно чисел 1...256,1...256, и т.д.
          for ( bx = 0 ; bx < (_flash_end - _flash_beg); bx = bx + 8192 )
           {
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 4 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[4-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------
             bh = bx ;
             ax = Save_into_i2c(8192,buff,bx,(b)m_addr) ;
             if ( ax != 0 )
             {
               goto end1;
             }
             //Flash_Store();
           }
*/
          if (m_index == 0)
          {
            ret = EMC_Check( _EMC_CS1,1 );
          }
          else
          {
            ret = EMC_Check( _EMC_CS1,0 );
          }
          m_time = Timer1_Ovr ;
          Label = i23 ;
          break ;

    case i23:
          if ( (u)((w)(Timer1_Ovr-m_time)) < _Sec(0.7) ) break;
          if ( ret == -1 )
          {
            output_s ( " Ok." ) ;
            m_time = Timer1_Ovr ;
            Label = i24 ;
            break ;
          }
          else  // Вывод адреса , на котором произошла ошибка :
          {
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 4 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( ret >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[4-bl] = bh ; //output_c ( bh ) ;
               }
             //---
             if( TestCompleted_Output() )  output_s ( _Error_i2c_txt "\n\r") ;
             output_s ( m_buff ) ;
             Label = i3 ;
          }
          break ;
    case i24:
          if ( (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0) ) break;
          goto end;
    //-----------------
      case i3:
      //---
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return || bh == Enter )  /* Выход из этого режима */
              {
                goto end;
              }
        }
/*
            // Считывание последовательно из памяти ранее занесенных данных.
          for ( bx = 0; bx < (_flash_end - _flash_beg) ; bx++ )
           {
                // Преобразование адреса в символьный вид и вывод
             for ( bl = 4 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[4-bl] = bh ; //output_c ( bh ) ;
               }
             if( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

             ax = Load_from_i2c(1,bx,&bh,(b)m_addr) ;
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
                 for ( m_time = Timer1_Ovr ; (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0); ) ;
                 goto end3;
               }
           }
         ptr = "  Ok. "  ;
   end3:
         output_s ( ptr ) ; // вывод (не)исправности.
         for ( m_time = Timer1_Ovr ; (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0); ) ;
         goto end; */
    }

  return ;
}


