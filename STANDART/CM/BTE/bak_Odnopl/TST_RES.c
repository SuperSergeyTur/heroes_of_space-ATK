// Программа насторойки электронного резистора в режиме диалога с пользователем посредством пульта или компьютера
// Структура меню:
//   1. Настр.Рез. (Настройка резистора)
//      1.1 RES0-(1-ый из 2-ух подстр. параметров) , где 1-ый параметр значение подстраиваемой переменной (например Ud) 
//      1.2 RES0-(2-ой из 2-ух подстр. параметров) , где 2-ой параметр значение подстраиваемой переменной (например Id)
//      1.3 RES1-(1-ый из 2-ух подстр. параметров) , где 1-ый параметр значение подстраиваемой переменной (например Is)
//      ...
//      1.n
//           1.1.1  Настр. диапаз. (настройка диапазона резистора) 
//                  по нажатию "Enter" в верхней стороке индицируется 2-а параметра ( Ом  ,  подстаиваемая переменная(%)  )
//                                     в нижней значения, которые соответствуют указанным в верхней строке 

//              1.1.1.1 нажатие "+" инкримент одной дискреты резистора 
//              1.1.1.2 нажатие "-" декримент одной дискреты резистора
//              1.1.1.3 нажатие "Esc" возвращаем в RAM то что запомнили при первом входе
//              1.1.1.4 нажатие "Enter" отдельную функцию (функция возвращает ошибку или ее отсутствие при выполнении след операций):

//                  1.1.1.4.1 оставляем в RAM заданное значение
//                  1.1.1.4.2 считуем с ROM текущее значение и записуем его в EEPROM в адрес "Предыдущая настройка" проверяем что записали
//                  1.1.1.4.3 записуем в ROM выставленное значение в RAM
//                  1.1.1.4.4 перепроверяем что значения в RAM и ROM одинаковые
//                  1.1.1.4.5 считаем значение из счетчика если оно >= 0xff записываем в него 0x01 иначе просто инкримент
//                  1.1.1.4.6 запишем и сверим, что записано в счетчике с тем, что хотели записать

//Примечание к  1.1.1:  при возникновении ошибки выводится сообщение на 4-е сек ( "НетЧт/Зап.Рез." )
//                      при отсутствии ошибки ничего не выводится

//           1.1.2  Счетчик изм. (счетчик количества внесенных изменений посредствам меню "Настр. диапаз." и с ВЫХОДОМ ПО "Enter") 
//              1.1.2.1 по нажатие "+" или "-"  происходит переопрос данной ячейки памяти резистора (для проверки I2C)
//              1.1.2.2 по нажатие "Esc" или "Enter"  происходит выход из данного подменю
//Примечание к  1.1.2:  при возникновении ошибки выводится сообщение на 4-е сек ( "НетЧтения Рез." )
//                      при отсутствии ошибки ничего не выводится

//           1.1.3  Пред. настр. (предыдущее значение настройки резистора в Ом, которое соответствует значению (Счетчик изм. - 1) т.е. предпоследней настройке) 
//              1.1.3.1 по нажатие "+" или "-"  происходит переопрос данной ячейки памяти резистора (для проверки I2C)
//              1.1.3.2 по нажатие "Esc" или "Enter"  происходит выход из данного подменю
//Примечание к  1.1.3:  при возникновении ошибки выводится сообщение на 4-е сек ( "НетЧтения Рез." )
//                      при отсутствии ошибки ничего не выводится





void TstRES_Drive ( void )
{
   register word  ax ;
           lword  lax ;   
   static   word  time, time_Ind ;
   static   word  count_con, count_Fault_Comp ;
   static   word  Res_RAM_copy ;
   static   word  ResFirst_con ;

           //  Контроль пароля: Полный запрет входа.
   if ( Password_control ( 2 ) == 0 )  return   ;

              

   if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
     {                      /* начального условия ...                    */
       M_FirstCall = 0 ;
       m_index = 0 , Label = 0 ;
       m_ext = 0 ;
       count_con = 0 ;

   //    if ( Mon.Password_Ok == 0 )  Label = 200 ;  // Вход с предупреждением о пароле.
   //    else                         Label = 210 ;  // Обычный вход.

       return ;
     }

  switch ( Label )
    {
      default: Label = 0 ;
      case 0:
                  output_s ( _RES_Tst ) ;
                  output_c ( '\n' ) ;
                  Label = 4;
      case 4:
             // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( RES_com_tab[m_index].RES_tab.txt ) ;
                  Label = 1 ;
                  break ;
                }
      case 1:  if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down )
                    {
                      if ( ++m_index >= _RES_Ntab ) m_index = 0 ;
                      Label = 4 ;
                    }
                  else if ( m_ch == Up )
                    {
                      if ( m_index == 0 ) m_index = _RES_Ntab ;
                      m_index-- ;
                      Label = 4 ;
                    }    // переход к следующей настройке 
                  else if ( m_ch == Enter )
                    {
                      Label = 20 ;
                        // начинаем с подменю настройки диапазона
                      m_ext = 0;

                      output_s ( "\n\r  " ) ;
                      output_s ( RES_com_tab[m_index].RES_tab.txt ) ;
                      output_s ( ":\n" ) ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
               if (AWelcome != AWell_old )
                {
                  AWell_old = AWelcome;
                  Label = 4;
                }

              break ;
            //-------------------

      case 20:  // Ожидание завершения предыдущего вывода.
                if ( TestCompleted_Output() )
                 {
                   output_c ( '\r' ) ;
                   output_s( AWelcome );
                   if      ( m_ext == 0 )    output_s ( _RES_NASTR_DIAP ) ;
                   else if ( m_ext == 1 )    output_s ( _RES_COUNT_NASTR ) ;
                   else                      output_s ( _RES_PAST_NASTR ) ;
                   Label = 21 ;
                   break ;
                 }

      case 21:  // Выбор режима : 
                if ( TestData_for_Input() )
                  {
                    mInput_c ( m_ch ) ;
                    if ( m_ch == Return )  // Выход из этого подменю
                      {
                        output_c ( '\n' ) ;
                        Label = 0 ;
                      }
                    else if ( m_ch == Down )
                      {
                        if ( ++m_ext >= _RES_Ntab2 ) m_ext = 0 ;
                        Label = 20 ;
                      }
                    else if ( m_ch == Up )
                      {
                        if ( m_ext == 0 ) m_ext = _RES_Ntab2 ;
                        m_ext-- ;
                        Label = 20 ;
                      }
                    else if ( m_ch == Enter )
                      {
                          // Сбросим счетчик неуспешных обращений к резистору
                        count_con = 0 ;
                          // Сбросим тригер записи буферного значения RAM для возврата знач при выдоде по Esc
                        ResFirst_con = 0 ;

                          // Переход в режим "Настройка Диапазона":
                        if      ( m_ext == 0 )
                         {

                           Label = 22, time = timer1 ;
                           output_s ( "\n\r  " ) ;
                             // на верхн. строку вывед. Ом и физич. параметр., который подверг. настройке
                           output_s ( RES_com_tab[m_index].RES_DataAch.txt ) ;
                           output_s ( ":\n" ) ;



                         }
                          // Переход в режим индикации "Счетчик изменений":
                        else if ( m_ext == 1 )  Label = 40, time = timer1 ;
                          // Переход в режим индикации "Предыдущая настройка":
                        else if ( m_ext == 2 )  Label = 50, time = timer1  ;

                      }
                    else
                      {
                        Klav_Buff = m_ch;
                      }
                  }
                if (AWelcome != AWell_old )
                  {
                    AWell_old = AWelcome;
                    Label = 20 ;
                  }

              break ;

 //--------------------------------------------------------------------------------------------------------------------//
        
              
              
      case 22:     //  Режим "Настройка Диапазона":
                   //  Если надо зададим начальные условия


                  // считаем текущее значение резистора и сохраним его в буфер для возврата по Esc
               if ( TestCompleted_Output() )
                 {

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM ) ;

                   if ( ax == MCP4661_RETFUNC_FAILED )
                    {
                         // Если при опросе возникли проблемы с чтением данных резистора
                         // попробуем переопросить резистор на следующем цикле
                      if ( ++count_con > 3 )
                       {
                        count_con = 0 ;
                        Label = 38 ;
                        break ;
                       }

                    }
                   else
                    {
                       // При чтении данных ошибок не возникло
                       
                       // При отладке несколько раз показалось, что при удержании кнопки "+", "-" ( прокрутки сопротивления ) значение резистора
                       // принималополовинное значение. (из 100 раз такое заметил 2-а раза)
                       // Поэтому если прочитанное не совпадает с желаемым проделаем цикл записи еще раз
                     if ( ResFirst_con != 0 )          
                      { 
                        if ( ResCommon[ m_index ].Res_data_write != ResCommon[ m_index ].ResMemory.Res_RAM )
                         {
                          if ( ++count_Fault_Comp > 3 ) Label = 38 ;  
                          else                          Label = 24 ;
                          break ;
                         } 
                        
                      } 
                     
                       // Если зашли в подменю первый раз сохраняем считаное значение сопротивления
                       // и запомним его для выхода по "Esc" :
                     if ( ResFirst_con == 0 )
                      {
                         Res_RAM_copy = ResCommon[ m_index ].ResMemory.Res_RAM ;
                         ResFirst_con = 1;
                      }
                     Label = 26 ;
                    }

                   break ;
                 }
                 // вне  TestCompleted_Output   break не ставим чтоб можно было нажать Esc


                 // Зададим новое значение
      case 24:
                if (  TestCompleted_Output() )
                 {
                   ax = SetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM );

                   if ( ax == MCP4661_RETFUNC_FAILED )
                    {
                         // Если при записи  возникли проблемы с чтением данных резистора
                         // попробуем записать их на следующем цикле
                      if ( ++count_con > 3 )
                       {
                        count_con = 0 ;
                        Label = 38 ;
                        break ;
                       }

                    }
                   else
                    {
                      count_con = 0 ;
                        // на следующем проходе считаем что там записано
                      Label = 22 ;
                      break ;
                    }
                 }
              
                break ;


      case 25:




      case 26:

                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                     // Вывод сопротивления в Ом 
                     
                  // Если надо вывести значение резистора через ЖОПУ (привести цифровой рез. к подобию переменного рез. то его крутить не 
                  //   с лева на право, а с права на лево)
               #ifdef _RES_IND_INVERT 
                  lax = ResCommon[ m_index ].ResConst.mashtab - 
                        (lw)(( (lw)ResCommon[ m_index ].ResMemory.Res_RAM * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
               #else
                  lax = (lw)(( (lw)ResCommon[ m_index ].ResMemory.Res_RAM * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;                  
               #endif


                  //output_s ( " R = " ) ;

                  m_ch = lax / 100000 + 0x30  ;
                  lax %= 100000 ;
                  output_c ( m_ch ) ;                  
                  
                  m_ch = lax / 10000 + 0x30  ;
                  lax %= 10000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 1000 + 0x30  ;
                  lax %= 1000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 100 + 0x30  ;
                  lax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 10 + 0x30  ;
                  lax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( lax + 0x30 ) ;

                  //output_s ( " Ом " ) ;
                  output_s ( ", " ) ;

                     //  Вывод физических ежениц
                    // Если масштаб == 0  (для резисторов, которые установленны не для аналоговах переменных таких как Id_max, ...)
                  if ( RES_com_tab[m_index].RES_DataAch.nom == 0 )
                    {
                     ax = 0 ;  
                     output_s ( "НеИзм." ) ;                      
                    }
                  else
                    {
                       // Вывод знака физаческой переменной
                     ax = *(  w*)RES_com_tab[m_index].RES_DataAch.adr ;
                     
                     if ( (sw)ax >= 0 )  output_c ( '+' );
                     else
                       {
                         output_c ( '-' ); ;
                         ax = ~ax + 1 ;
                       }                     
                      
                     ax =  (w)( (slw) ax * (slw)100 * (slw)100 / (slw)RES_com_tab[m_index].RES_DataAch.nom ) ;

                  
                     
                     m_ch = ax / 10000 + 0x30  ;
                     ax %= 10000 ;
                     output_c ( m_ch ) ;

                     m_ch = ax / 1000 + 0x30  ;
                     ax %= 1000 ;
                     output_c ( m_ch ) ;

                     m_ch = ax / 100 + 0x30  ;
                     ax %= 100 ;
                     output_c ( m_ch ) ;

                     output_c ( '.' ) ;  // вывод дробной части .


                     m_ch = ax / 10 + 0x30  ;
                     ax %= 10 ;
                     output_c ( m_ch ) ;


           //        m_ch = ax / 1 + 0x30  ;  17-тый символ
           //        output_c ( m_ch ) ;
                    }
           //       output_s ( "% " ) ;

                  Label = 30 ;

                  time_Ind = Timer1_Ovr ;

                  break ;

                }



      case 30:


                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  // Выход из этого режима
                     {
                       Label = 32 ;
                     }
               #ifndef _RES_IND_INVERT 
                   else if ( m_ch == Up )
                     {
                         // Проверим на выход из сетки для данного резистора в max
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM < ResCommon[ m_index ].ResConst.Wiper_Data_max )
                        {
                           // Подготовим данные для записи
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM + 1 ;
                         count_Fault_Comp = 0;
                         Label = 24 ;
                        }
                     }
                   else if ( m_ch == Down ) // Изменить смещение
                     {
                         // Проверим на знач. меньше 0
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM > 0  )
                        {
                           // Подготовим данные для записи
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM - 1 ;
                         count_Fault_Comp = 0 ;
                         Label = 24 ;
                        }
                     }
               #else
                   else if ( m_ch == Down  )
                     {
                         // Проверим на выход из сетки для данного резистора в max
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM < ResCommon[ m_index ].ResConst.Wiper_Data_max )
                        {
                           // Подготовим данные для записи
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM + 1 ;
                         count_Fault_Comp = 0 ;
                         Label = 24 ;
                        }
                     }
                   else if ( m_ch == Up ) // Изменить смещение
                     {
                         // Проверим на знач. меньше 0
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM > 0  )
                        {
                           // Подготовим данные для записи
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM - 1 ;
                         count_Fault_Comp = 0 ;                         
                         Label = 24 ;
                        }
                     }                   
               #endif
                   
                   else if ( m_ch == Enter ) Label = 35 ; // Смещение принято .
                   else
                     {
                       Klav_Buff = m_ch;
                     }
                 }
                if (AWelcome != AWell_old )
                 {
                   AWell_old = AWelcome;
                   Label = 26 ;
                 }
                
                  // если ничего не нажали все равно вернемся и обновим индицируемые параметры
              if ( (u)(w)( Timer1_Ovr - time_Ind ) >= _Sec(0.20) && Label == 30 )  Label = 26 ;

              break ;


               // Нажали Esc
        case 32:

              if (  TestCompleted_Output() )
                {
                    // Если текущее значение не равно буферу записуем в резистор буфер
                  if ( ResCommon[ m_index ].ResMemory.Res_RAM != Res_RAM_copy )
                   {
                      // Подготовим данные для записи
                    ResCommon[ m_index ].Res_data_write = Res_RAM_copy ;
                    ax = SetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM );

                    if ( ax == MCP4661_RETFUNC_FAILED )
                     {
                          // Если при записи  возникли проблемы с чтением данных резистора.
                          // Попробуем записать их на следующем цикле
                       if ( ++count_con > 3 )
                        {
                         count_con = 0 ;
                         Label = 38 ;
                         break ;
                        }

                     }
                    else
                     {
                       count_con = 0 ;
                         // на следующем проходе считаем корректно ли записано наше значение
                       Label = 33 ;
                       break ;
                     }
                   }

                }

        case 33:



                  // считаем текущее значение резистора
               if ( TestCompleted_Output() )
                 {

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM ) ;

                   if ( ax == MCP4661_RETFUNC_FAILED )
                    {
                         // Если при опросе возникли проблемы с чтением данных резистора
                         // попробуем переопросить резистор на следующем цикле
                      if ( ++count_con > 3 )
                       {
                        count_con = 0 ;
                        Label = 38 ;
                        break ;
                       }

                    }
                   else
                    {
                       // При чтении данных ошибок не возникло проверим что буферное значение соответствует записанному
                     if ( ResCommon[ m_index ].ResMemory.Res_RAM == Res_RAM_copy )
                      {
                        // Работу завершили корректно перейдем в меню уровнем выше
                       Label = 20 ;
                      }
                     else
                      {
                        // Данные имеют разное значение работу завершили некорректно выйдем из меню с сообщением
                       Label = 38 ;
                      }

                    }

                   break ;
                 }

 //---------------------------------------------------------------------//
                 // Выход по Enter
        case 35:
              if (  TestCompleted_Output() )
                {
                 ResCommon[ m_index ].Res_Err_Ret = SetResVal_Enter( &ResCommon[ m_index ] ) ;
                 ax = (w)ResCommon[ m_index ].Res_Err_Ret ;

                   // запись данных в процессе (запись данных не закончена)
                 if        ( ax == MCP4661_RET_RECORD_NO_FINISH || ax == MCP4661_RET_EEPROM_BUSY ) break ;
                   // данные записались корректно
                 else if   ( ax == MCP4661_RET_DATA_OK )                 Label = 20 ;
                   // ошибка при записи данных
                 else if ( ( ax == MCP4661_RETFUNC_FAILED  )      ||
                           ( ax == MCP4661_RET_CONNECT_OVERFLOW ) ||
                           ( ax == MCP4661_RET_DATA_FAILED )
                         )                                               Label = 38 ;

                 break ;
                }


        case 38:

              if (  TestCompleted_Output() )
                {

                 time = Timer1_Ovr ;
                 Label = 39 ;
                 break ;
                }


        case 39:

                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( "НетЧт/Зап.Рез." ) ;  //( "НетЧт/Зап.Рез." ) ;
                    // Выведем сообщение на время чтоб его успели/смогли прочитать
                  if ( (u)(w)(Timer1_Ovr - time) > _Sec( 4.0 ) )  Label = 20 ;
                  break ;
                }
                  break ;




 //--------------------------------------------------------------------------------------------------------------------//
                 //  режим индикации "Счетчик изменений":

      case 40:



               if ( TestCompleted_Output() )
                 {

                      // По даташиту после записи обращаться к EEPROM разрешается через 5 мс (до этошо момента запись и чтение не имеют смысла)
                      // ограничим цикличность опроса если обращение к даннай ячейке не проходит
                   if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) ) break ;

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_EEP_COUNT_SAVE ) ;

                   if ( ( ax == MCP4661_RET_EEPROM_BUSY ) || ( ax == MCP4661_RETFUNC_FAILED ) )
                    {
                         // Если при опросе возникли проблемы с чтением данных резистора
                         // попробуем переопросить резистор на следующем цикле
                      time = timer1 ;
                         // Сбросим счетчик неуспешных обращений к резистору
                      if ( ++count_con > 3 ) count_con = 0, Label = 44 ;
                    }
                   else  Label = 42 ;

                   break ;
                 }

      case 42:

                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );

                    // переложим считанное выше значение
                  ax = ResCommon[ m_index ].ResMemory.Count_Save ;
                  output_s ( " Изм= " ) ;  //( " Изм= " ) ;

                    /*  Вывод количества изменений сопротивления. */

                  m_ch = ax / 100 + 0x30  ;
                  ax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = ax / 10 + 0x30  ;
                  ax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( ax + 0x30 ) ;

                  output_s ( " раз." ) ;  //( " раз." ) ;

                  Label = 46 ;

                  break ;
                }


      case 44:

                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( "НетЧтения Рез." ) ;  //( "НетЧтения Рез." ) ;

                  Label = 46 ;
                  break ;
                }

      case 46:

                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  // Выход из этого режима
                     {
                         // Переход к выбору режима
                       Label = 20 ;
                     }
                   else if ( m_ch == Up )
                     {
                         // Переопросим ячейку памяти резистора где хранится "Предыдущая настройка"
                         // Переопрос актуален для проверки I2C запроса к данному резистору
                       Label = 40 ;
                     }
                   else if ( m_ch == Down ) // Изменить смещение
                     {
                         // Переопросим ячейку памяти резистора где хранится "Предыдущая настройка"
                         // Переопрос актуален для проверки I2C запроса к данному резистору
                       Label = 40 ;
                     }
                   else if ( m_ch == Enter ) Label = 20 ; // Смещение принято .
                   else
                     {
                       Klav_Buff = m_ch;
                     }
                 }
                if (AWelcome != AWell_old )
                 {
                   AWell_old = AWelcome;
                   Label = 42 ;
                 }

              break ;
            //-------------------


 //--------------------------------------------------------------------------------------------------------------------//
                 //  Режим индикации "Предыдущая настройка":

      case 50:

                if ( TestCompleted_Output() )
                 {

                      // По даташиту после записи обращаться к EEPROM разрешается через 5 мс (до этошо момента запись и чтение не имеют смысла)
                      // ограничим цикличность опроса если обращение к даннай ячейке не проходит
                   if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) ) break ;

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_EEP_PAST_SAVE ) ;

                   if ( ( ax == MCP4661_RET_EEPROM_BUSY ) || ( ax == MCP4661_RETFUNC_FAILED ) )
                    {
                         // Если при опросе возникли проблемы с чтением данных резистора
                         // попробуем переопросить резистор на следующем цикле
                      time = timer1 ;
                         // Сбросим счетчик неуспешных обращений к резистору
                      if ( ++count_con > 3 ) count_con = 0, Label = 54 ;
                    }
                   else  Label = 52 ;

                   break ;
                 }

      case 52:

                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                 
                     // переложим считанное выше значение
                     // Вывод сопротивления в Ом 
                     
                  // Если надо вывести значение резистора через ЖОПУ (привести цифровой рез. к подобию переменного рез. то его крутить не 
                  //   с лева на право, а с права на лево)
               #ifdef _RES_IND_INVERT 
                  lax = ResCommon[ m_index ].ResConst.mashtab - 
                        (lw)(( (lw)ResCommon[ m_index ].ResMemory.Past_Save * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
               #else
                  lax = (lw)(( (lw)ResCommon[ m_index ].ResMemory.Past_Save * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;                  
               #endif
                  
                  output_s ( " R = " ) ;
                  m_ch = lax / 100000 + 0x30  ;
                  lax %= 100000 ;
                  output_c ( m_ch ) ;                  
                  
                  m_ch = lax / 10000 + 0x30  ;
                  lax %= 10000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 1000 + 0x30  ;
                  lax %= 1000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 100 + 0x30  ;
                  lax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 10 + 0x30  ;
                  lax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( lax + 0x30 ) ;
                  
                  output_s ( " Ом " ) ;  //( " Ом " ) ;

                  Label = 56 ;

                  break ;

                }



      case 54:

                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( "НетЧтения Рез." ) ;  //( "НетЧтения Рез." ) ;

                  Label = 56 ;
                  break ;
                }


      case 56:

                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  // Выход из этого режима
                     {
                         // Переход к выбору режима
                       Label = 20 ;
                     }
                   else if ( m_ch == Up )
                     {
                         // Переопросим ячейку памяти резистора где хранится "Предыдущая настройка"
                         // Переопрос актуален для проверки I2C запроса к данному резистору
                       Label = 50 ;
                     }
                   else if ( m_ch == Down ) // Изменить смещение
                     {
                         // Переопросим ячейку памяти резистора где хранится "Предыдущая настройка"
                         // Переопрос актуален для проверки I2C запроса к данному резистору
                       Label = 50 ;
                     }
                   else if ( m_ch == Enter ) Label = 20 ; // Смещение принято .
                   else
                     {
                       Klav_Buff = m_ch;
                     }
                 }
                if (AWelcome != AWell_old )
                 {
                   AWell_old = AWelcome;
                   Label = 52 ;
                 }

              break ;

 //--------------------------------------------------------------------------------------------------------------------//


    }

 Restart_Output ()  ;

  return ;
}

