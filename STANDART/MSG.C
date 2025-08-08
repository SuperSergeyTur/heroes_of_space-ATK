
// ПРОГРАММА ВЫВОДА НА ПУЛЬТ АВАРИЙНЫХ, ПРЕДУПРЕДИТЕЛЬНЫХ И СЛУЖЕБНЫХ СООБЩЕНИЙ.
//--------------------------------------------------------------

/*------------------------------------------------------------------*/
/*   Программа циклической выдачи сообщений соответствующих побитово
 * регистрам регистрации сообщений. Эти регистры приняты 32-разрядными,
 * что вызвано удобством использования при этом команды ассемблера
 * "norml" (см.ниже).
 *   Добавлено еще по одному 32-разрядному регистру сообщений. Проверяется
 * в начале оба одноименных регистра на наличие сообщений, и в случае наличия
 * просматриваются по очереди .
 *
 * "Reg_AvarMsgFirst"  -  признак аварии появившийся первым ;
 * "Reg_AvarMsg"       -  признаки аварий ;
 * "Reg_PreduprMsg"    -  признаки предупреждений ;
 * "Reg_ServiceMsg"    -  признаки служебных сообщений ;
 *
 * "Reg_AvarMsgFirst2" -  2-й регистр признака аварии появившейся первой ;
 * "Reg_AvarMsg2"      -  2-й регистр признаков аварий ;
 * "Reg_PreduprMsg2"   -  2-й регистр признаков предупреждений ;
 * "Reg_ServiceMsg2"   -  2-й регистр признаков служебных сообщений .
 *
 * "avar_first_obj"    -  3-й регистр признака аварии появившейся первой - перекрасный язык программирования ;
 * "avar_obj"          -  3-й регистр признаков аварий - перекрасный язык программирования ;
 * "predupr_obj"       -  3-й регистр признаков предупреждений - перекрасный язык программирования ;
 * "service_obj"       -  3-й регистр признаков служебных сообщений - перекрасный язык программирования .
 */
      //  Для совместимости с прежними программами.
void PrintMessage ( void )
{
   print_message ( &msg_reg ) ;
   return ;
}

void print_message ( struct MSG_reg *ptr )
{
  #define  bit_pointer  m_buff[0]  /* указатель номера последнего обработанного бита */
          register byte  bh , tst ;
          register lword lax ;
          //register word ax ;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          Label = 0 ,  bit_pointer = 0xFF ;
          m_time = Timer1_Ovr ;

#ifdef _JOURNAL
          //если вывод сообщений из журнала
          if ( BitJrn._.tst_msg_jrn != 0 ) output_s ( _Jrn_Message_prompt );
          else
#endif

          output_s ( _Message_prompt ) ;
          goto obhod ;
        }

        /* Обработка символов из буфера ввода, до его опустошения. */
      while (  TestData_for_Input() )
        {
          mInput_c ( bh ) ;
          if ( bh == Return )  /* Выход из этого режима */
            {

#ifdef _JOURNAL
              if ( BitJrn._.tst_msg_jrn != 0 ) //если вывод сообщений из журнала
              {
                Pult_Prog_Addr = _Case ( 'F' , 'B' ); //принудительный возврат в программу просмотра журнала
                BitJrn._.tst_msg_jrn = 0; //отключаем вывод сообщений журнала
                Label = (b)m_ext;    //восстанавливаем метку
                return;
              }
#endif

              Pult_Prog_Addr = _MainPultProg ,  M_FirstCall = 1 ;
              return ;   // добавить еще какую-то иниц.
            }
          else
            {

#ifdef _JOURNAL
              if ( BitJrn._.tst_msg_jrn == 0 ) //если вывод сообщений из журнала, то всё, что в switch'е не нужно
              {
#endif

                switch ( bh )     // после того как появился 'msg_buf' использование
                {              // 'ptr' не работает, и кроме того не хорошо было для msg_av.
                  case Down : msg_buf.predupr.lw_reg  = 0 ;  /* Сброс предупреждений */
                              msg_buf.service.lw_reg  = 0 ;
                              msg_buf.predupr2.lw_reg = 0 ;
                              msg_buf.service2.lw_reg = 0 ;
#ifdef _TRETIY_REG
                              msg_buf.predupr3.lw_reg = 0 ;
                              msg_buf.service3.lw_reg = 0 ;
#endif
#ifdef _INTERPRETER
                              msg_buf.service_obj.lw_reg = 0 ;
                              msg_buf.predupr_obj.lw_reg = 0 ;
#endif
                              //msg_buf..lw_reg = 0 ;
                  case Up :   mask_predupr   = msg_buf.predupr.lw_reg ;  /* Маскирование предупреждений */
                              mask_service   = msg_buf.service.lw_reg ;  /* Маскирование служебных сооб.*/
#ifndef _ONE_REG
                              mask_predupr2  = msg_buf.predupr2.lw_reg ;  /* Маскирование предупреждений */
                              mask_service2  = msg_buf.service2.lw_reg ;  /* Маскирование служебных сооб.*/
#endif
#ifdef _TRETIY_REG
                              mask_predupr3  = msg_buf.predupr3.lw_reg ;  /* Маскирование предупреждений */
                              mask_service3  = msg_buf.service3.lw_reg ;  /* Маскирование служебных сооб.*/
#endif
#ifdef _INTERPRETER
                              mask_predupr_obj  = msg_buf.predupr_obj.lw_reg ;  /* Маскирование предупреждений */
                              mask_service_obj  = msg_buf.service_obj.lw_reg ;  /* Маскирование служебных сооб.*/
#endif
                              output_s("\r\nOk.\r\n") ;
                              break ;

#ifndef _NO_RTC
                  case Enter:    /* Распечатка времени остановки следа. */
                              output_s ("\r\n") ;
                              PrintTime ( &(ptr->time) ) ;
                              Label = 0 ,  bit_pointer = 0xFF ;
                              break ;
#endif                              
                  default  :  Klav_Buff = bh ;
                              break ;
                }

#ifdef _JOURNAL
              }
              else Klav_Buff = bh;
#endif

            }
        }


       /* Ожидание окончания вывода имеющихся в буфере сообщений */
    if ( !TestCompleted_Output() )
      {                      /* оператор "Op2" */
        m_time = Timer1_Ovr ; /*   Для того, чтобы знать время окончания */
        return ;             /* вывода сообщения и иметь точку отсчета  */
      }                      /* для оператора "Op1".                    */

       /* Выдержка времени после окончания предыдущего сообщения */
  //ax = Timer1_Ovr - m_time;
    if ( (u)(w)(Timer1_Ovr - m_time) <= (w)_SoobPauza ) return ;  /* оператор "Op1" */
obhod:// dlya bystrogo zapolneniya ekrana pri pervom vhode
    tst = 0x00 ;  // каждый из регистров должен установить свой признак отсутствия сообщений
    switch ( Label )
      {
                /*---- Первое аварийное сообщение ----*/
        default :
        case 0 :
              // проверка обоих (троих или четверых) регистров первой аварии :
             if ( ( ptr->_.avar_first.lw_reg | ptr->_.avar_first2.lw_reg
#ifdef _TRETIY_REG
                                             | ptr->_.avar_first3.lw_reg
#endif
#ifdef _INTERPRETER
                                                                         | ptr->_.avar_first_obj.lw_reg
#endif
                                                                                                        ) != (lw)0 ) // Op1
              {
                output_s ("\r\n") ;
                output_s (AWelcome) ;
                output_s ( _FirstAvMsg_txt ) ;
                Label = 1 ;
                m_time = Timer1_Ovr ;
                return ;

              case 1 : // проверка первого регистра первой аварии :
                if ( ptr->_.avar_first.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.avar_first.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_1 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto  as_1 ;                         //  Проверка на случай, если после проверки в операторе
                 aq_1:   Label = 11 ,  bit_pointer = 0xFF ; // Op1 кто-то, за время вывода сообщения, обнулил регистр.
                         return ; //  'return' потому-что уже проделано изрядно операций,

                 as_1:
                  // время потеряно и пора уже выходить, хотя логично перейти к следующему регистру.
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;
                       //   Преобразование " 31 - " надо чтобы нулевому(!) биту
                       // регистра соответствовало нулевое(!) сооб. таблицы и так далее.
                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Avar[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // первый регистр чист , переходим на второй
                 {
                    Label = 11 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 11 : // проверка второго регистра первой аварии :
                if ( ptr->_.avar_first2.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.avar_first2.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_11 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto  as_11 ; //  Проверка на случай, если после проверки в операторе
#ifdef _TRETIY_REG                             // Op1 кто-то, за время вывода сообщения, обнулил регистр.
                 aq_11:   Label = 12 ,  bit_pointer = 0xFF ; // проверка третьего регистра первой аварии .
#else
 #ifdef _INTERPRETER
                 aq_11:   Label = 13 ,  bit_pointer = 0xFF ; // проверка регистра прекрасного языка .
 #else
                 aq_11:   Label = 2  ,  bit_pointer = 0xFF ; // проверка регистров вторых аварий .
 #endif
#endif
                          return ; //  'return' потому-что уже проделано изрядно операций,

                 as_11:
                  // время потеряно и пора уже выходить, хотя логично перейти к следующему регистру.
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;
                       //   Преобразование " 31 - " надо чтобы нулевому(!) биту
                       // регистра соответствовало нулевое(!) сооб. таблицы и так далее.
                    output_c ('\r') ;
#ifndef _ONE_REG
                    output_s ( Tabl_Msg.Avar2[ 31 - bit_pointer ] ) ;
#else
                    Msg_notSupport ( (b)(31 - bit_pointer) ) ;
#endif
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                    else // второй регистр первой аварии чист , переходим на третий регистр
                 {       // или на регистр прекрасного языка или на вторые аварийные сообщения .
#ifdef _TRETIY_REG
                    Label = 12 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 12 : // проверка третьего регистра первой аварии :
                if ( ptr->_.avar_first3.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.avar_first3.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_12 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto  as_12 ; //  Проверка на случай, если после проверки в операторе
 #ifdef _INTERPRETER                            // Op1 кто-то, за время вывода сообщения, обнулил регистр.
                 aq_12:   Label = 13,  bit_pointer = 0xFF ; // проверка регистра прекрасного языка .
 #else
                 aq_12:   Label = 2 ,  bit_pointer = 0xFF ; // проверка регистров вторых аварий .
 #endif
                          return ; //  'return' потому-что уже проделано изрядно операций,

                 as_12:
                  // время потеряно и пора уже выходить, хотя логично перейти к следующему регистру.
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;
                       //   Преобразование " 31 - " надо чтобы нулевому(!) биту
                       // регистра соответствовало нулевое(!) сооб. таблицы и так далее.
                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Avar3[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // третий регистр чист , переходим на регистры прекрасного языка или на регистры вторых аварий :
                 {
#endif
#ifdef _INTERPRETER
                    Label = 13 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 13 : // проверка регистра первой аварии прекрасного языка :
                if ( ptr->_.avar_first_obj.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.avar_first_obj.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_13 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto  as_13 ;                         //  Проверка на случай, если после проверки в операторе
                 aq_13:   Label = 2 ,  bit_pointer = 0xFF ; // Op1 кто-то, за время вывода сообщения, обнулил регистр.
                          return ; //  'return' потому-что уже проделано изрядно операций,

                 as_13:
                  // время потеряно и пора уже выходить, хотя логично перейти к следующему регистру.
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;
                       //   Преобразование " 31 - " надо чтобы нулевому(!) биту
                       // регистра соответствовало нулевое(!) сооб. таблицы и так далее.
                    output_c ('\r') ;
                    output_s ( Tabl_Msg_obj.Avar[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // регистр первой аварии прекрасного языка чист , переходим на регистры вторых аварий :
                 {
#endif
                    Label = 2 , bit_pointer = 0xFF ;
                    return ;
                 }
              }
              // сообщений о первых авариях нет :
             else  Label = 2 ,  bit_pointer = 0xFF ,  tst |= 0x01 ;

                /*---- Вторичные аварийные сообщения ----*/
        case 2:
             /* Исключаем дублирование сообщений о первых и вторичных авариях .*/

              // проверка обоих (троих или четверых) регистров аварий :
             if ( ( ( ptr->_.avar.lw_reg  & ~ptr->_.avar_first.lw_reg  ) |
                    ( ptr->_.avar2.lw_reg & ~ptr->_.avar_first2.lw_reg )
#ifdef _TRETIY_REG
                  | ( ptr->_.avar3.lw_reg & ~ptr->_.avar_first3.lw_reg )
#endif
#ifdef _INTERPRETER
                  | ( ptr->_.avar_obj.lw_reg & ~ptr->_.avar_first_obj.lw_reg )
#endif
                                                                               ) != (lw)0 )
              {
                output_s ("\r\n") ;
                output_s (AWelcome) ;
                output_s ( _AvMsg_txt ) ;
                Label = 21 ;
                m_time = Timer1_Ovr ;
                return ;

              case 21 : // проверка первого регистра аварий :
                if ( ( ptr->_.avar.lw_reg & ~ptr->_.avar_first.lw_reg ) != (lw)0 )
                 {
                    lax = ptr->_.avar.lw_reg & ~ptr->_.avar_first.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_21 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if (lax != 0) goto as_21  ;            /*   Если в оставшемся кадре, единичных битов     */
                 aq_21: Label = 22 ,  bit_pointer = 0xFF ; /* не осталось, то возврат указателя обработанных */
                        return ;                           /* битов к началу регистра.                       */
                 as_21:
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;

                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Avar[ 31 - bit_pointer ] ) ;

                    m_time = Timer1_Ovr ;
                    return ;
                     /*  Для того, чтобы знать время начала вывода сообщения, т.е. иметь
                      * хотя бы такую точку отсчета для оператора "Op1", на тот случай,
                      * если сообщение короткое и к следующему входу в эту п/п будет уже
                      * выведено и мы не пройдем через оператор "Op2" и таким образом не
                      * будем иметь точки отсчета для оператора "Op1".
                      */
                 }
                else // первый регистр чист , переходим на второй
                 {
                    Label = 22 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 22 : // проверка второго регистра аварий :
                if ( ( ptr->_.avar2.lw_reg & ~ptr->_.avar_first2.lw_reg ) != (lw)0 )
                 {
                    lax = ptr->_.avar2.lw_reg & ~ptr->_.avar_first2.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_22 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if (lax != 0) goto as_22  ; // Если в оставшемся кадре, единичных битов не осталось,
#ifdef _TRETIY_REG                              //то возврат указателя обработанных битов к началу регистра.
                 aq_22: Label = 23 ,  bit_pointer = 0xFF ; // проверка третьего регистра вторых аварий .
#else
 #ifdef _INTERPRETER
                 aq_22: Label = 24 ,  bit_pointer = 0xFF ;
 #else
                 aq_22: Label = 3  ,  bit_pointer = 0xFF ;
 #endif
#endif
                        return ;
                 as_22:
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;

                    output_c ('\r') ;
#ifndef _ONE_REG
                    output_s ( Tabl_Msg.Avar2[ 31 - bit_pointer ] ) ;
#else
                    Msg_notSupport ( (b)(31 - bit_pointer) ) ;
#endif
                    m_time = Timer1_Ovr ;
                    return ;
                     /*  Для того, чтобы знать время начала вывода сообщения, т.е. иметь
                      * хотя бы такую точку отсчета для оператора "Op1", на тот случай,
                      * если сообщение короткое и к следующему входу в эту п/п будет уже
                      * выведено и мы не пройдем через оператор "Op2" и таким образом не
                      * будем иметь точки отсчета для оператора "Op1".
                      */
                 }
                else // второй регистр чист , переходим на регистр прекрасного языка или на предупредительные сообщения .
                 {
#ifdef _TRETIY_REG
                    Label = 23 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 23 : // проверка третьего регистра аварий :
                if ( ( ptr->_.avar3.lw_reg & ~ptr->_.avar_first3.lw_reg ) != (lw)0 )
                 {
                    lax = ptr->_.avar3.lw_reg & ~ptr->_.avar_first3.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_23 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if (lax != 0) goto as_23  ;  // Если в оставшемся кадре, единичных битов не осталось,
 #ifdef _INTERPRETER                              //то возврат указателя обработанных битов к началу регистра.
                 aq_23: Label = 24,  bit_pointer = 0xFF ;
 #else
                 aq_23: Label = 3 ,  bit_pointer = 0xFF ;
 #endif
                        return ;
                 as_23:
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;

                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Avar3[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                     /*  Для того, чтобы знать время начала вывода сообщения, т.е. иметь
                      * хотя бы такую точку отсчета для оператора "Op1", на тот случай,
                      * если сообщение короткое и к следующему входу в эту п/п будет уже
                      * выведено и мы не пройдем через оператор "Op2" и таким образом не
                      * будем иметь точки отсчета для оператора "Op1".
                      */
                 }
                else // третий регистр вторых аварий чист , переходим на регистр перекрасного языка
                 {   // или на регистры предупреждений :
#endif
#ifdef _INTERPRETER
                    Label = 24 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 24 : // проверка третьего регистра аварий :
                if ( ( ptr->_.avar_obj.lw_reg & ~ptr->_.avar_first_obj.lw_reg ) != (lw)0 )
                 {
                    lax = ptr->_.avar_obj.lw_reg & ~ptr->_.avar_first_obj.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_24 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                      /*   Отыскание среди оставшихся "в кадре" необработанных битов
                       *  ближайшего к старшему краю единичного бита и его номера "bh"
                       *  в масштабе этого "кадра".
                       */
                    asm_norml( lax , bh ) ;
                    if (lax != 0) goto as_24  ;           /*   Если в оставшемся кадре, единичных битов     */
                 aq_24: Label = 3 ,  bit_pointer = 0xFF ; /* не осталось, то возврат указателя обработанных */
                        return ;                           /* битов к началу регистра.                       */
                 as_24:
                      /*   Перевод номера найденного очередного единичного бита
                       *  из масштаба "кадра" в масштаб регистра, и тем самым
                       *  перерасчет указателя обработанных битов.
                       */
                    bit_pointer += bh ;

                    output_c ('\r') ;
                    output_s ( Tabl_Msg_obj.Avar[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                     /*  Для того, чтобы знать время начала вывода сообщения, т.е. иметь
                      * хотя бы такую точку отсчета для оператора "Op1", на тот случай,
                      * если сообщение короткое и к следующему входу в эту п/п будет уже
                      * выведено и мы не пройдем через оператор "Op2" и таким образом не
                      * будем иметь точки отсчета для оператора "Op1".
                      */
                 }
                else // регистр вторых аварий прекрасного языка чист , переходим на регистры предупреждений :
                 {
#endif
                    Label = 3 , bit_pointer = 0xFF ;
                    return ;
                 }
              }
              // аварийных сообщений нет :
             else  Label = 3 ,  bit_pointer = 0xFF ,  tst |= 0x02 ;

                 /*---- Все предупредительные сообщения ----*/
        case 3:
              // проверка обоих (троих или четверых) регистров предупреждений :
             if ( ( ptr->_.predupr.lw_reg | ptr->_.predupr2.lw_reg
#ifdef _TRETIY_REG
                                          | ptr->_.predupr3.lw_reg
#endif
#ifdef _INTERPRETER
                                                                   | ptr->_.predupr_obj.lw_reg
#endif
                                                                                               ) != (lw)0 )
              {
                output_s ("\r\n") ;
                output_s (AWelcome) ;
                output_s ( _PrMsg_txt ) ;
                Label = 31 ;
                m_time = Timer1_Ovr ;
                return ;

              case 31 : // проверка первого регистра предупреждений :
                if ( ptr->_.predupr.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.predupr.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_31 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto as_31 ;
                 aq_31:   Label = 32 ,  bit_pointer = 0xFF ;
                          return ;
                 as_31:
                    bit_pointer += bh ;
                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Predupr[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // первый регистр чист , переходим на второй
                 {
                    Label = 32 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 32 : // проверка второго регистра предупреждений :
                if ( ptr->_.predupr2.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.predupr2.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_32 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto as_32 ;
#ifdef _TRETIY_REG
                 aq_32:   Label = 33 ,  bit_pointer = 0xFF ;
#else
 #ifdef _INTERPRETER
                 aq_32:   Label = 34 ,  bit_pointer = 0xFF ;
 #else
                 aq_32:   Label = 4  ,  bit_pointer = 0xFF ;
 #endif
#endif
                          return ;
                 as_32:
                    bit_pointer += bh ;
                    output_c ('\r') ;
#ifndef _ONE_REG
                    output_s ( Tabl_Msg.Predupr2[ 31 - bit_pointer ] ) ;
#else
                    Msg_notSupport ( (b)(31 - bit_pointer) ) ;
#endif
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // второй регистр чист , переходим на регистр прекрасного языка или на служебные сообщения .
                 {
#ifdef _TRETIY_REG
                    Label = 33 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 33 : // проверка третего регистра предупреждений :
                if ( ptr->_.predupr3.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.predupr3.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_33 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto as_33 ;
 #ifdef _INTERPRETER
                 aq_33:   Label = 34,  bit_pointer = 0xFF ;
 #else
                 aq_33:   Label = 4 ,  bit_pointer = 0xFF ;
 #endif
                          return ;
                 as_33:
                    bit_pointer += bh ;
                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Predupr3[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // второй(третий)  регистр чист , переходим на регистры сервисные
                 {
#endif
#ifdef _INTERPRETER
                    Label = 34 , bit_pointer = 0xFF ;
                    return ;
                 }

              case 34 : // проверка третего регистра предупреждений :
                if ( ptr->_.predupr_obj.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.predupr_obj.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_34 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                    asm_norml( lax , bh ) ;
                    if(lax != 0) goto as_34 ;
                 aq_34:   Label = 4 ,  bit_pointer = 0xFF ;
                          return ;
                 as_34:
                    bit_pointer += bh ;
                    output_c ('\r') ;
                    output_s ( Tabl_Msg_obj.Predupr[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                    return ;
                 }
                else // второй(третий)  регистр чист , переходим на регистры сервисные
                 {
#endif
                    Label = 4 , bit_pointer = 0xFF ;
                    return ;
                 }
              }
              // предупредительных сообщений нет :
             else  Label = 4 ,  bit_pointer = 0xFF ,  tst |= 0x04 ;

                /*---- Служебные сообщения ----*/
        case 4:
                  //   В "_r.Begin_Code" старший бит - признак того,
                 //  что приняты типовые уставки.
             // перенесено в #ust_i2c.c: читай там.
             //if ( (_r.Begin_Code & 0x8000) != 0 )
             //      {  mSet_ServiceMsg( _Srv_TipUst ) ; }
             //else  {  mClr_ServiceMsg( _Srv_TipUst ) ; }
              //-----
              // проверка обоих(троих) регистров сервисных сообщений :
             if ( ( ptr->_.service.lw_reg | ptr->_.service2.lw_reg
#ifdef _TRETIY_REG
                                          | ptr->_.service3.lw_reg
#endif
#ifdef _INTERPRETER
                                                                   | ptr->_.service_obj.lw_reg
#endif
                                                                                               ) != (lw)0 )
              {
                if ( Mon.EnableSrvMsg == 0 )
                 {
                    output_s ( _Srv1Msg_txt ) ;
                    Label = 0 ;
                    Mon.NewCiklMsg = 1 ; // Признак перехода к новому циклу вывода сообщений
                                     // для защит - если они хотят очистить регистры.
                 }
                else
                 {
                    output_s ("\r\n") ;
                    output_s (AWelcome) ;
                    output_s ( _Srv2Msg_txt ) ;
                    Label = 41 ;
                 }
                m_time = Timer1_Ovr ;
                return ;

              case 41 : // проверка первого регистра сервисных сообщений :
                if ( ptr->_.service.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.service.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_41 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                   asm_norml( lax , bh  );
                   if(lax != 0) goto as_41  ;
                 aq_41:   Label = 42 ,  bit_pointer = 0xFF ;
                          //Mon.NewCiklMsg = 1 ; // Здесь признак не нужен , т.к. нужно еще проверить второй регистр .
                          return ;
                 as_41:
                    bit_pointer += bh ;
                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Service[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                 //   return ;
                 }
                else // первый регистр чист , переходим на второй
                 {
                    Label = 42 , bit_pointer = 0xFF ;
                 //   return ;
                 }
                return ;

              case 42 : // проверка второго регистра сервисных сообщений :
                if ( ptr->_.service2.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.service2.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_42 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                   asm_norml( lax , bh  );
                   if(lax != 0) goto as_42  ;
#ifdef _TRETIY_REG
                 aq_42:   Label = 43 ,  bit_pointer = 0xFF ;
#else
 #ifdef _INTERPRETER
                 aq_42:   Label = 44 ,  bit_pointer = 0xFF ;
 #else
                 aq_42:   Label =  0 ,  bit_pointer = 0xFF ;
                          Mon.NewCiklMsg = 1 ; // Признак перехода к новому циклу вывода сообщений
                          // для защит - если они хотят очистить регистры - выставляется , т.к. все регистры проверены .
 #endif
#endif
                          return ;
                 as_42:
                    bit_pointer += bh ;
                    output_c ('\r') ;
#ifndef _ONE_REG
                    output_s ( Tabl_Msg.Service2[ 31 - bit_pointer ] ) ;
#else
                    Msg_notSupport ( (b)(31 - bit_pointer) ) ;
#endif
                    m_time = Timer1_Ovr ;
                 //   return ;
                 }
                else // второй регистр чист , переходим на регистр прекрасного языка или на начало .
                 {
#ifdef _TRETIY_REG
                    Label = 43 , bit_pointer = 0xFF ;
                 //   return ;
                 }
                return ;

              case 43 : // проверка третьего регистра сервисных сообщений :
                if ( ptr->_.service3.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.service3.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_43 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                   asm_norml( lax , bh  );
                   if(lax != 0) goto as_43  ;
 #ifdef _INTERPRETER
                 aq_43:   Label = 44,  bit_pointer = 0xFF ;
 #else
                 aq_43:   Label = 0 ,  bit_pointer = 0xFF ;
                          Mon.NewCiklMsg = 1 ; // Признак перехода к новому циклу вывода сообщений
                          // для защит - если они хотят очистить регистры - выставляется , т.к. все регистры проверены .
 #endif
                          return ;
                 as_43:
                    bit_pointer += bh ;
                    output_c ('\r') ;
                    output_s ( Tabl_Msg.Service3[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                  //  return ;
                 }
                else // второй регистр чист , метка на начало :
                 {
#endif
#ifdef _INTERPRETER
                    Label = 44 , bit_pointer = 0xFF ;
                 //   return ;
                 }
                return ;

              case 44 : // проверка второго регистра сервисных сообщений :
                if ( ptr->_.service_obj.lw_reg != (lw)0 )
                 {
                    lax = ptr->_.service_obj.lw_reg ;
                    bit_pointer += 1 ;
                    if ( bit_pointer >= 32 ) goto aq_44 ;// FR-при сдвиге на 32 не выполняет сдвига вообще.
                    lax <<= bit_pointer ; /* Сдвиг "за кадр" уже обработанных битов. */

                   asm_norml( lax , bh  );
                   if(lax != 0) goto as_44  ;
                 aq_44:   Label = 0 ,  bit_pointer = 0xFF ;
                          Mon.NewCiklMsg = 1 ; // Признак перехода к новому циклу вывода сообщений
                          // для защит - если они хотят очистить регистры - выставляется , т.к. все регистры проверены .
                          return ;
                 as_44:
                    bit_pointer += bh ;
                    output_c ('\r') ;
                    output_s ( Tabl_Msg_obj.Service[ 31 - bit_pointer ] ) ;
                    m_time = Timer1_Ovr ;
                  //  return ;
                 }
                else // второй регистр чист , метка на начало :
                 {
#endif
                    Label = 0 , bit_pointer = 0xFF ;
                    Mon.NewCiklMsg = 1 ; // Признак перехода к новому циклу вывода сообщений
                                        // для защит - если они хотят очистить регистры.
                  //  return ;
                 }
                return ;
              }
             else // сервисных сообщений нет :
              {
                 bit_pointer = 0xFF ,  tst |= 0x08 ;
                    /*---- Сообщений нет ----*/
                      //   Признаки отсутствия сообщений во всех регистрах будут установлены
                      // только если программа прочесала их за один заход, если же какой то
                      // регистр был пропущен по "case", то значит в нем были сообщения на
                      // предыдущем цикле, и он косвенно, таким образом, не выставил свой
                      // признак отсутствия сообщений.
                  if ( tst == 0x0f )
                  {
                    output_s ("\r\n") ;
                    output_s (AWelcome) ;
                    output_s ( _NoMsg_txt ) ;
                    m_time = Timer1_Ovr ;
                    Label  = 8 ;
                  }
                  else
                  {
        case 8:     Label = 0,  Mon.NewCiklMsg = 1 ; // Все регистры проверены , выставляем признак .
                  }
              }

      }

      // Если сообщений нет, то выводим поочередно "Сообщения:" ("Сооб.журнала") и "Сообщений нет",
      // чтобы не было эффекта 'замирания' при быстром выводе.
      if ( tst == 0 )
      {
#ifdef _JOURNAL
        //если вывод сообщений из журнала
        if ( BitJrn._.tst_msg_jrn != 0 ) output_s ( _Jrn_Message_prompt );
        else
#endif
              output_s ( _Message_prompt ) ;
        m_time = Timer1_Ovr ;
      }

    //   Сделать общий 'return' из-за принципа работы 'tst' не получается,
    // а сделать 'tst' по другому - приводит к неприятным побочным эффектам.
  return ;
}
//--------------

  //    Фиксация времени изменения количества сообщений для
  //  распечатки его по "Enter" в режиме "A1".
word check_msg_time ( void )
{
  register word ax ;
  //static byte tst ;

         //   Проверяем через подсчет контрольной суммы сообщений
        //  не изменилось ли количество сообщений.
    //if ( ++tst > 10 ) // чтобы не подсчитывать постоянно контрольную сумму.
    //{
  //  tst = 1 ;
         //   КОНТРОЛЬ СУММЫ МОЖЕТ НЕ СРАБОТАТЬ ЕСЛИ ОДНО СООБЩЕНИЕ ВЗВЕЛОСЬ,
         // А ДРУГОЕ (С ТЕМ ЖЕ КОДОМ В ДРУГОМ БАЙТЕ) ОДНОВРЕМЕННО СБРОСИЛОСЬ.
      //if ( Chek_sum ( sizeof(struct MSG_regs), (b*)&msg_reg._ ) != 0 )
         // сравниваем сразу по 4 байта для быстроты.
    for ( ax = 0 ; ax < ( sizeof(struct MSG_regs)/4 ) ; ax++ )
    {
      if ( ((lw*)&msg_reg._)[ax] != ((lw*)&msg_buf)[ax] )
      {
      //  tst = 0 ; // копируем сообщения из рабочего буфера в буфер
        msg_reg._ = msg_buf ; // вывода на пульт и в CAN.
          // Для вывода времени в режиме "A1".
        msg_reg.time = c_time ;
          // очищаем при появлении нового сообщ., чтобы оно не попало под
          // чужую маску, т.к. в маску входят и служебные и предупреждения.
      //  mask_predupr = 0 ;   больше не надо т.к. ввели
//#ifndef _ONE_REG          отдельные маски на служебные сообщения.  21.02.08
      //  mask_predupr2 = 0 ;
//#endif
        //подсветку пультика включаем, если изменилось кол-во сообщений и
        //вывод находится либо в А1 или А0, чтобы своей командой
        //включения подсветки не сбивать с толку Link и CodeReadWriter.
        if ( ( Lb( Pult_Prog_Addr) == 'A' || Lb( Pult_Prog_Addr) == 'a' ) &&
             ( Hb( Pult_Prog_Addr) == '0' || Hb( Pult_Prog_Addr) == '1' )
           )
        Mon.RXBuffOverflow = 1; //

#ifdef _JOURNAL
        if ( BitJrn._.first == 1 ) BitJrn._.tst_new_msg = 1; //установка признака изменения количества сообщений
#endif

        break;
      }
    }
    if ( Mon.RXBuffOverflow == 1  &&  Mon.Pult == 0 ) //   При медленном выводе вешается в А1 на ожидании выдержки
    {                                                  //     2сек между сообщениями - вывод символов сбивает ее.
      Mon.RXBuffOverflow = 0;
      if ((Timer1_Ovr - time_Svet) > _Sec(0.5) )
      {
        output_c ( _PultikSwet ); //включаем подсветку пультика
        Restart_Output ()  ;
        time_Svet = Timer1_Ovr;
      }
    }
    //}

  return 1 ; //(w)tst ;
}

  // Подпрограмма вывода номера сообщения из отключенного второго регистра
  // сообщений в случае , если его всё-таки кто-то взвёл .
void Msg_notSupport ( byte num )
 {
   output_s ( _Msg_notSupport_txt ) ;
   m_ch = num / 10 + 0x30 ;
   output_c ( m_ch ) ;      // вывод первой цифры - десятков .
   num %= 10 ;
   output_c ( num + 0x30 ) ; // вывод второй цифры - единиц .
   output_s ( "." ) ;

   return ;
 }

/*-------------------------------------------------  */

/*  ПРОГРАММА ЦИКЛИЧЕСКОГО ПЕРЕКЛЮЧЕНИЯ МЕЖДУ 'A1' И 'A6':
   для агрегатов где нет на двери приборов.
 */

void A1_A6_Switching ( void )
 {
   static byte screen_mode, time_perekl ;

    if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
      {                      /* начального условия ...                    */
        M_FirstCall = 0 ;
        screen_mode = 1 ;
      }
 //-------------

    switch ( screen_mode )
    {
      case 1 :
          Mon.NewCiklMsg = 0,  M_FirstCall = 1 ;
          screen_mode = 2 ;

      case 2 :
          Mon.EnableSrvMsg = 1 ;
          PrintMessage () ;
          //---
          if ( Mon.NewCiklMsg == 1 )
          {
            screen_mode = 3 ;
            m_time = Timer1_Ovr ;
          }
          //---
          break;

              /* Выдержка времени после окончания предыдущего сообщения */
      case 3 :
          //if ( (u)(w)(Timer1_Ovr - m_time) <= (w)(_SoobPauza/2) ) break ;

            M_FirstCall = 1, S_break = 107 ;
            time_perekl = Timer1_Ovr ;
            screen_mode = 4 ;

      case 4 :
        
#if  defined (_A6_group_obj) && defined (_BTE)
     //   #if  !(defined (Zad_RM_ach) || defined (Zad_RT_ach))
          if ( ((Klav_Buff == Shift_Up) || (Klav_Buff == Shift_Down)) == 1) time_perekl = Timer1_Ovr ;
          SelectParamA0( 1 ) ;                  // Вывод переменных из группы IndA0 в подменю "А0 индикации"     
     //   #endif  
#endif        
          Indicator_Drive () ;
          //---
          if ( (b)(Timer1_Ovr-time_perekl) >= _Sec(5.0) ) //7.0
          {
            S_break = 0 ;
            screen_mode = 1 ;
          }
          
        break;
    }

  return ;
}

//------------------------------

// Функция выделения первой аварии . Регистров аварий развелось как собак нерезаных , поэтому первых аварий тоже может
// быть несколько . Пока все регистры первых аварий чисты - записываем в них содержимое регистров аварий . Т.е. если
// аварии в разных регистрах сработали одновременно - мы их не потеряем .
void SetF_AvarMsg ( void )
{
  if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2
#ifdef _TRETIY_REG
                                             | Reg_AvarMsgFirst3
#endif
#ifdef _INTERPRETER
                                                                 | Reg_AvarMsgFirst_obj
#endif
                                                                                        ) == (lw)r0 )
  {
    Reg_AvarMsgFirst  = Reg_AvarMsg  ;
    Reg_AvarMsgFirst2 = Reg_AvarMsg2 ;
#ifdef _TRETIY_REG
    Reg_AvarMsgFirst3 = Reg_AvarMsg3 ;
#endif
#ifdef _INTERPRETER
    Reg_AvarMsgFirst_obj = Reg_AvarMsg_obj ;
#endif
  }
  return ;
}
