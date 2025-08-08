/*------------------------------------------------------------------*/
/*   Программа ввода и изменеия пароля:
 * - пароль накладывается на вход в:
                                   { "AE-Зап.Устав. ", _Case ( 'A' , 'E' ) },
                                   { "F2-Наладка.   ", _Case ( 'F' , '2' ) },
                                   { "A2-Фазир.Us   ", _Case ( 'A' , '3' ) },
                                   { "A5-Фазир.Мостa", _Case ( 'A' , '5' ) },
                                   //{ "FA-ОСТАНОВ.   ", _Case ( 'F' , 'A' ) },
                                   { "A9-Тест ЦАП.  ", _Case ( 'A' , '9' ) },
                                   { "AB-Тест Двых. ", _Case ( 'A' , 'B' ) },
                                   { "AD-Вывод ЦАП. ", _Case ( 'A' , 'D' ) },
                                   { "F-Монитор.    ", _Case ( 'F' ,  0  ), 9 },
                                   { "F1-След.      ", _Case ( 'F' , '1' ) },
                                   { "F3-Тест ОЗУ.  ", _Case ( 'F' , '3' ) },
                                   { "F4-Тест ЭОЗУ  ", _Case ( 'F' , '4' ) },
                                   { "F7-Наст.Часов.", _Case ( 'F' , '7')  },
                                   { "FD-Тест DP.   ", _Case ( 'F' , 'D' ) },
                                   { "F9-Тип.Устав. ", _Case ( 'F' , '9' ) },
                                   { "F0-Табл.След. ", _Case ( 'F' , '0' ) },
                                   { "FC-Услов.След.", _Case ( 'F' , 'C')  },
                                   { "F1-След.      ", _Case ( 'F' , '1' ) },
                                   { "AC-Настр.Журн.", _Case ( 'A' , 'C' ) },
 * - пароль накладывается на изменение уставок в: -- для тех программ, которые, например, могут понадобиться
 *                                                                       при выяснении проблем в разговоре по телефону.
                                   { "A7-Ред.Устав. ", _Case ( 'A' , '7' ) },
                                   { "A8-Ред.БитУст.", _Case ( 'A' , '8' ) },
                                   { "A3-Фазир.Is   ", _Case ( 'A' , '3' ) },
                                   { "A4-Тест АЦП.  ", _Case ( 'A' , '4' ) },
 * - в каждой из указаных программ вставляется опрос признака "пароль введен";
 * - при загрузке в "system.c"по ветке инициализации ПО проверяет:
 *       - если задан нулевой пароль значит пароль не используется и включает признак
 *         "пароль введен";
 *       - иначе сбрасывает признак "пароль введен";
 * - при вызове с пультового терминала ПО выполняет:
 *       - если пароль не введен ранее - предлагает ввести   или восстановить пароль;
 *       - если пароль    введен ранее - предлагает изменить или активировать пароль;
 * - при вводе пароля:
 *       - размер пароля "word";
 *       - имя переменной пароля "_r.Password";
 *       - пароль состоит из 3-х цифр;
 *       - каждая тетрада word содержит одну цифру, четвертая тетрада запасная;
 *       - на терминал выводится три нуля и курсор устанавливается на крайнем левом нуле;
 *       - цифра вводится увеличением/уменьшением клавишами ввех/вниз в диапазоне "0...9", но на экране не
 *         показывается - после первого нажатия нуль заменяется на символы "*".
 *         Высвечивается нуль, только если перебором дошли снова до нуля.
 *         При каждом нажатии клавиш вверх/вниз на всех позициях выводятся знаки "-" для контроля того,
 *         что клавиша нажалась.
 *       - завершение ввода каждой цифры и переход к следующей осуществляется через "Enter";
 *       - возврат к предыдущей цифре осуществляется через "Esc", при этом текущая цифра обнуляется;
 *       - по завершении ввода всех цифр введеный пароль сравнивается с уставкой пароля и либо принимается, либо отвергается
 *         с сответствующим сообщением;
 *       - ПО возвращается к меню диспетчера;
 * - при восстановлении пароля:
 *       - входим в меню восстановления пароля;
 *       - на экран выводится пароль, преобразованный по формуле: "Xi=9-Ni",
 *         при этом 1-я цифра пароля оказывается на 3-й позиции, 2-я - на 1-й и 3-я - на 2-й;
 *       - искомый пароль вычисляется по формуле: "Ni=9-Xi",
 *         при этом следует учитывать, что 1-я цифра выводимой комбинации соответствует 2-й цифре пароля,
 *         2-я - 3-й и 3-я - 1-й;
 * - при изменении пароля повторяется то же, что и при вводе пароля, но с выводом значенией цифр и по завершении ввода
 *   введеный пароль заносится в уставку с соответствующим сообщением;
 * - для отключения пароля вообще, пароль изменяется на нулевой.
 */


word  Password_control ( word code )
{
    register word  ax  ;
    register byte  bh  ;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
enum { i0, i10, i20, i30, i40, i50, i60, i70, i160 };


            //  Инициализация.
    if ( code == 0 )
    {
      if ( _r.Password == 0 )  Mon.Password_Ok = 1 ;
      else                     Mon.Password_Ok = 0 ;

      return  0 ;
    }
    else if ( code == 2 )  //  Вставка для сервисных программ: Контроль пароля - Полный запрет входа.
    {
        if ( Mon.Password_Ok == 0 )
        {
          if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
          {
            output_s ( _NoPassword_txt ) ;
            m_time = Timer1_Ovr ;
            M_FirstCall = 0 ;
          }
          else    //---
          {
            if ( (u)(w)(Timer1_Ovr - m_time) > _Time_Password_txt )
            {
              Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
            }
          }
          return  0 ;
        }
        else  return  1 ;
    }
          //----------------------
     //------------------------



      if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
        {                      // начального условия ...
          M_FirstCall = 0 ;
             //-------------
          m_time = Timer1_Ovr ;
          Label = i0 ;
          m_index = 0 ;
          return  0 ;
        }


     switch ( Label )
     {
      default:
      case i0:    output_s ( _MenuPassword_txt ) ;
                  m_index = 0 ;
                  Label = i10 ;
      case i10:
            if ( TestCompleted_Output() )
            {
              if ( Mon.Password_Ok == 0 )
              {
                if ( m_index == 0 ) output_s ( _EnterPassword_txt ) ;  // определение
                else                output_s ( _RecovPassword_txt ) ;  // структуры меню
              }                                                        // в зависимости
              else                                                     // от наложения
              {                                                        // пароля
                if ( m_index == 0 ) output_s ( _ChangePassword_txt ) ;
                else                output_s ( _ActivatePassword_txt ) ;
              }
              Label = i20 ;
              break ;
            }

      case  i20:
          if ( TestData_for_Input() )
           {
              mInput_c ( bh ) ;
              if ( bh == Return )  // Выход из этого режима
                {
             end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                  return  0 ;
                }                                 // для блокировки активации при отсутствии пароля
              else if (( bh == Up  ||  bh == Down ) && _r.Password != 0 ) // Изменить выбор.
                {
                  //aa = m_index ;
                  m_index = ~m_index ;
                  Label = i10 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 )                Label = i30 ;
                  else  if ( Mon.Password_Ok == 0 )  Label = i60 ;
                  else
                  {
                    Mon.Password_Ok = 0 ;                  // активация пароля
                    output_s ( _ActivatedPassword_txt ) ;
                    m_time = Timer1_Ovr ;
                    Label = i160 ;
                  }
                }
              else    Klav_Buff = bh;
           }
          break ;

      case i30:   output_s ( "\n" ) ;
                  m_index = 0 ;
                  m_buff[0] = 0, m_buff[1] = 0, m_buff[2] = 0 ;
                  //output_s ( "\n\r     0 0 0  \b\b\b\b\b" ) ;
                  Label = i40 ;

      case i40:
                if ( (u)(w)(Timer1_Ovr - m_time) > _Sec( 0.15 ) )
                {
                  if ( TestCompleted_Output() )            // вывод меню ввода пароля
                  {
                      output_s ( "\r    -" ) ;
                    if ( Mon.Password_Ok == 1 )   output_c ( m_buff[0]+0x30 ) ;
                    else
                    {
                      if ( m_buff[0] == 0 )  output_c ( '0' ) ;    // если вводимый символ не 0 -
                      else                   output_c ( '*' ) ;    // замена его на '*'
                    }
                      output_s ( "-" ) ;
                    if ( Mon.Password_Ok == 1 )   output_c ( m_buff[1]+0x30 ) ;
                    else
                    {
                      if ( m_buff[1] == 0 )  output_c ( '0' ) ;
                      else                   output_c ( '*' ) ;
                    }
                      output_s ( "-" ) ;
                    if ( Mon.Password_Ok == 1 )   output_c ( m_buff[2]+0x30 ) ;
                    else
                    {
                      if ( m_buff[2] == 0 )  output_c ( '0' ) ;
                      else                   output_c ( '*' ) ;
                    }
                      output_s ( "-" ) ;
                     // вычисление месторасположения курсора в зависимости от выбранной позиции
                    for ( ax = 0 ; ax < (( _PasswordSize-1 - m_index ) * 2 + 2 ) ; ax++ )
                    {
                      output_s ( "\b" ) ;
                    }

                    Label = i50 ;
                    break ;
                } }

      case i50:   if ( TestData_for_Input() )                        // ввод пароля
                  {
                    mInput_c ( bh ) ;
                        if ( bh == Return )         // по нажатию Esc - обнуление текущей позиции
                        {                           // если уже 0 - переход на предыдущую
                          Label = i40 ;
                          if ( m_buff[m_index] != 0 )  m_buff[m_index] = 0 ;
                          else
                          {
                            if ( m_index != 0 )  m_index-- ;
                            else                 Label = i0 ;
                          }
                        }
                        else if ( bh == Up )
                        {
                          if ( m_buff[m_index] < 9 )  m_buff[m_index]++ ;
                          else m_buff[m_index] = 0 ;
                         //---  при изменении символа - кратковременный вывод тире на всех позициях
                          if ( Mon.Password_Ok == 0 )   output_s ( _ProbelPassword_txt ) ;
                          m_time = Timer1_Ovr ;
                            //---
                          Label = i40 ;
                        }
                        else if ( bh == Down )
                        {
                          if ( m_buff[m_index] > 0 )  m_buff[m_index]-- ;
                          else m_buff[m_index] = 9 ;
                            //---
                          if ( Mon.Password_Ok == 0 )   output_s ( _ProbelPassword_txt ) ;
                          m_time = Timer1_Ovr ;
                            //---
                          Label = i40 ;
                        }
                        else if ( bh == Enter )   // по нажатию Enter - переход
                        {                         // на следующую позицию
                          if ( m_index < 2 )
                          {
                            m_index++ ;
                            Label = i40 ;
                          }
                          else
                          {
                            if ( Mon.Password_Ok == 1 )           // если пароль был предварительно
                            {                                     // введен - запоминание
                              _r.Password =  (w)m_buff[0] +       // изменённого пароля
                                            ((w)m_buff[1] << 4) +
                                            ((w)m_buff[2] << 8) ;
                              output_s ( _OkNewPassword_txt ) ;
                            }
                            else
                            {
                              ax = _r.Password ;
                              if ( m_buff[0] == (ax & 0x000F))           // проверка правильности
                              {                                          // введённого пароля
                                if ( m_buff[1] == ((ax >> 4) & 0x000F))
                                 {
                                   if ( m_buff[2] == ((ax >> 8) & 0x000F))
                                    {
                                      output_s ( _RightPassword_txt ) ;
                                      Mon.Password_Ok = 1 ;
                                    }
                                   else goto end1 ;
                                 }
                                else goto end1 ;
                              }
                              else
                              {
                        end1:   output_s ( _WrongPassword_txt ) ;
                              }
                            }
                            m_time = Timer1_Ovr ;
                            m_index = 0 ;
                            Label = i160 ;
                          }
                        }
                        else    Klav_Buff = bh;
                  }

                  break;


      case i60:   ax = _r.Password ;                      // вывод меню восстановления пароля
                  m_buff[2] = 9 - ( ax       & 0x000F) ;
                  m_buff[0] = 9 - ((ax >> 4) & 0x000F) ;
                  m_buff[1] = 9 - ((ax >> 8) & 0x000F) ;

                  output_s ( _RecoveCodePassword_txt ) ;
                  output_s ( "\r\n    -" ) ;
                  output_c ( m_buff[0]+0x30 ) ;
                  output_s ( "-" ) ;
                  output_c ( m_buff[1]+0x30 ) ;
                  output_s ( "-" ) ;
                  output_c ( m_buff[2]+0x30 ) ;
                  output_s ( "-" ) ;
                  Label = i70 ;

      case i70:   if ( TestData_for_Input() )
                  {
                    mInput_c ( bh ) ;
                        if ( bh == Return || bh == Enter )  // Выход из этого режима
                        {
                          goto end ;
                        }
                        else    Klav_Buff = bh;
                  }
                  break ;

      case i160 :
                  if ( (u)(w)(Timer1_Ovr - m_time) > _Time_Password_txt ) goto end ;
          break ;

    }

  return  0 ;
}

