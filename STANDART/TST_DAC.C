

//    ПРОГРАММА  ТЕСТИРОВАНИЯ  ЦАПов  В  РЕЖИМЕ  ДИАЛОГА  С
//  ПОЛЬЗОВАТЕЛЕМ  ПОСРЕДСТВОМ  ПУЛЬТА  ЛИБО  КОМПЬЮТЕРА .

/*------------------------------------------------------------------*/
/*   Режим доступен из "Готовности".
 *   Задание напряжения и индикация заданного напряжения для выдачи
 * на ЦАП осуществляется в вольтах.
 *   Диапазон задаваемых значений -5V ... +5V.
 *   Дискретность изменения задаваемого значения:
 * - плавно ч0.002V.
 * - грубо  ч0.100V.
 *
 *   Функции:
 * - выбор тестируемого ЦАПа из таблицы путем перебора ;
 * - задание значения для выдачи на выбранный ЦАП ;
 * - индикация номера ЦАПа и задаваемого ему на выдачу значения;
 * - выбор режима выдачи заданного значения на ЦАП: автоматический или
 *   по команде.
 *   Клавиши:
 * - "+-" - выбор номера ЦАПа ;
 * - "+" - увеличение задаваемого для выдачи на ЦАП значения ;
 * - "-" - уменьшение задаваемого для выдачи на ЦАП значения ;
 * - "Enter" - начало тестироввания ЦАПа ;
 * - "Esc"   - возврат в диспетчер.
 */


void TstDAC_Drive ( void )
{
   register word ax ;
   static   word buff ;

// #ifdef _DAC_OFFSET
   register word cx ;
// #endif


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
              m_index = 0 , Label = 0 ;

          #ifdef _DAC_OFFSET
              m_ext = 0 ;
          #endif

          return ;
        }

  switch ( Label )
    {
      default: Label = 0 ;
      case 0:
                  output_s ( _DAC_Tst ) ;
                  output_c ( '\n' ) ;
                  Label = 4;
      case 4:
             // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( DAC_tab1[m_index].txt ) ;
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
                      if ( ++m_index >= _DAC_Ntab1 ) m_index = 0 ;
                      Label = 4 ;
                    }
                  else if ( m_ch == Up )
                    {
                      if ( m_index == 0 ) m_index = _DAC_Ntab1 ;
                      m_index-- ;
                      Label = 4 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Enter )
                    {
                      T_DAC  = 0, buff = 0 ;  // обнуляем тестовую переменную.
                      m_addr = DAC_tab1[m_index].p->var_num ;  // сохраняем прежний адрес.
                      DAC_tab1[m_index].p->var_num = _DAC_Ntab2-1 ; // задаем новый адрес.

#if defined (_DAC_OFFSET) || defined (_CM3_)
                      // Для "чистого" DAC возможно смещение нулевой точки , для
                      // его компенсации предназначен режим "Смещение нуля" .
                      // Поэтому для DAC0 и DAC1 переходим к выбору режимов :
                      // "Смещение нуля" или "Тест диапазона" .

                      //  В одноплатном ВТЕ DACи аппаратно связаны со схемами без подстроечных резисторов "0"
                      //  поэтому пришлось опять вернуть смещение DACов
  #if    defined _BTE_NEW   //#ifndef  _CM3_
                      if ( m_index <= 2 ) Label = 20 ; // Выбор режима .
                      else                Label = 25 ; // "Тест диапазона" .
  #else // #elif !defined _CM3_  10.07.2017 8:21 DAC1 - задание на If
                     // if ( m_index <= 1 )
                      Label = 20 ; // Выбор режима .
//#else    // у платы CM3 только один "чистый" DAC :
//                    if ( m_index == 0 ) Label = 20 ; // Выбор режима .
  #endif

#else
                      Label = 25 ;                     // "Тест диапазона" .
#endif

                      output_s ( "\n\r  " ) ;
                      output_s ( DAC_tab1[m_index].txt ) ;
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

#if defined (_DAC_OFFSET) || defined (_CM3_)

      case 20:  // Ожидание завершения предыдущего вывода.
                if ( TestCompleted_Output() )
                 {
                   output_c ( '\r' ) ;
                   output_s( AWelcome );
                   if ( m_ext == 0 )    output_s ( _DAC_Shift_Null ) ;
                   else                 output_s ( _DAC_Test ) ;
                   Label = 21 ;
                   break ;
                 }

      case 21:  // Выбор режима : "Смещение нуля" или "Тест диапазона" .
                if ( TestData_for_Input() )
                  {
                    mInput_c ( m_ch ) ;
                    if ( m_ch == Return )  // Выход из этого режима
                      {
                           // восстанавливаем прежний адрес :
                        DAC_tab1[m_index].p->var_num = m_addr ;
                        output_c ( '\n' ) ;
                        Label = 0 ;
                      }
                    else if ( m_ch == Up || m_ch == Down ) // Изменить выбор
                      {
                        m_ext = ~m_ext , Label = 20 ;
                      }
                    else if ( m_ch == Enter )
                      {
                          // Переход в режим "Смещение нуля" :
                        if ( m_ext == 0 )  Label = 22 ;
                          // Переход в режим "Тест диапазона":
                        else               Label = 25 ;
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

      case 22:    // Для задания смещения необходимо задать нуль на DAC :
                T_DAC = 0, buff = 0 ;  // обнуляем тестовую переменную.

                  // сохраняем прежнее смещение :
                m_time = DAC_tab1[m_index].p->offset ;

      case 23:  // Вывод смещения .
                if ( TestCompleted_Output() )
                 {
                      // знаковое смещение в дискретах :
                   ax = DAC_tab1[m_index].p->offset ;
                   output_c ( '\r' ) ;
                   output_s( AWelcome );

                      // Определение знака :
                   if ( (sw)ax >= 0 )  output_s ( " См= +" ) ;
                   else
                    {
                      output_s ( " См= -" ) ;
                      ax = ~ax + 1 ;
                    }

                   cx = (lw)(w)ax * 100 % _DAC_setka_max ; // остаток от деления уставки в дискретах
                   ax = (lw)(w)ax * 100 / _DAC_setka_max ; // на 1 единицу ( дискрет/процент ) .

                   m_ch = ax / 100 + 0x30  ;
                   ax %= 100 ;
                   output_c ( m_ch ) ;

                   m_ch = ax / 10 + 0x30  ;
                   ax %= 10 ;
                   output_c ( m_ch ) ;

                   output_c ( ax + 0x30 ) ;

                    output_c ( '.' ) ;  // вывод дробной части .

                   cx *= 10 ;
                   m_ch = cx / _DAC_setka_max + 0x30 ;
                   cx %= _DAC_setka_max ;
                   output_c ( m_ch ) ;

                   cx *= 10 ;
                   m_ch = cx / _DAC_setka_max + 0x30 ;
                   output_c ( m_ch ) ;

                   output_s ( "% " ) ;

                   Label = 24 ;
                 }
              break ;

      case 24:  // Режим "Смещение нуля"
                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  /* Выход из этого режима */
                    {
                        // восстанавливаем прежнее смещение :
                      DAC_tab1[m_index].p->offset = m_time ;
                        // Переход к выбору режима
                      Label = 20 ; // "Смещение нуля" или "Тест диапазона" .
                    }
                   else if ( m_ch == Up )   // Изменить смещение
                     {
                       if ( (sw)DAC_tab1[m_index].p->offset < _DAC_setka_max )
                        {
                            // знаковое смещение в дискретах увеличиваем на 0.25% .
                           DAC_tab1[m_index].p->offset += 1 ; //_DAC_setka_max/400 ;
                           Label = 23 ;
                        }
                     }
                   else if ( m_ch == Down ) // Изменить смещение
                     {
                       if ( (sw)DAC_tab1[m_index].p->offset > (sw)_DAC_setka_min )
                        {
                            // знаковое смещение в дискретах уменьшаем на 0.25% .
                           DAC_tab1[m_index].p->offset -= 1 ; //_DAC_setka_max/400 ;
                           Label = 23 ;
                        }
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
                   Label = 23 ;
                 }

              break ;
            //-------------------
#endif

      case 25:  // сохраняем прежний масштаб :
              m_time = DAC_tab1[m_index].p->mashtab ;
                // задаем новый масштаб :
              DAC_tab1[m_index].p->mashtab = 1.0*256;
              Label = 2 ;  // переставляем метку, чтобы сюда больше не войти
                         // и не затереть сохраненный масштаб.
      case 2:   // Режим "Тест диапвзона"
                    // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );

                  ax = T_DAC ;

                    /*  Вывод знака. */
                  if ( (sw)ax >= 0 )  output_s ( " U = +" ) ;
                  else
                    {
                      output_s ( " U = -" ) ;
                      ax = ~ax + 1 ;
                    }

                  cx = (lw)(w)ax * 100 % _DAC_setka_max ; // остаток от деления уставки в дискретах
                  ax = (lw)(w)ax * 100 / _DAC_setka_max ; // на 1 единицу ( дискрет/процент ) .

                  m_ch = ax / 100 + 0x30  ;
                  ax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = ax / 10 + 0x30  ;
                  ax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( ax + 0x30 ) ;

                   output_c ( '.' ) ;   // вывод дробной части .

                   cx *= 10 ;
                   m_ch = cx / _DAC_setka_max + 0x30 ;
                   cx %= _DAC_setka_max ;
                   output_c ( m_ch ) ;

                   cx *= 10 ;
                   m_ch = cx / _DAC_setka_max + 0x30 ;
                   output_c ( m_ch ) ;

                  output_s ( "% " ) ;

                  Label = 3 ;
                  break ;
                }

      case 3:  /* Обработка символов из буфера ввода, без 'while
                * до опустошения' (т.к. при ручном вводе этого не надо) */
              if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                      if ( m_ch == Return )  /* Выход из этого режима */
                        {
                            // восстанавливаем прежний масштаб
                          DAC_tab1[m_index].p->mashtab = m_time ;

                    #if defined ( _DAC_OFFSET ) || defined ( _CM3_)
                      #ifndef _CM3_
                          if ( m_index <= 1 ) Label = 20 ; // Выбор режима .
                          else
                           {
                             DAC_tab1[m_index].p->var_num = m_addr ;  // восстанавливаем прежний адрес.
                             Label = 0 ;  // "Тест диапазона" .
                           }
                      #else  // у платы CM3 только один "чистый" DAC :
                          Label = 20 ; // Выбор режима .
                      #endif

                          T_DAC = 0, buff = 0 ;  // обнуляем тестовую переменную.
                    #else
                          output_c ( '\n' ) ;
                          DAC_tab1[m_index].p->var_num = m_addr ;  // восстанавливаем прежний адрес.
                          Label = 0 ;
                    #endif

                        }
                      else
                      {
#if defined (_DAC_OFFSET) || defined (_CM3_)

                        ax = (sw)(((slw)DAC_tab1[m_index].p->offset*100)/ _DAC_setka_max);
#else
                        ax = 0;
#endif
                        if ( m_ch == Up )
                          {
                            if ( (sw)buff < (sw)+100-(sw)ax )  buff++ ;  //  инкрементируем в процентах 1д=1%.
                            Label = 2 ;
                          }
                        else if ( m_ch == Down )
                          {
                            if ( (sw)buff > (sw)-100-(sw)ax )  buff-- ;
                            Label = 2 ;
                          }
                        else
                        {
                          Klav_Buff = m_ch;
                        }
                        T_DAC = (slw)(sw)_DAC_setka_max * (sw)buff / (sw)100 ;  //  переводим проценты в дискреты.
                      }
                }
              if (AWelcome != AWell_old )
                {
                  AWell_old = AWelcome;
                  Label = 2;
                }

    }

 Restart_Output ()  ;

  return ;
}

