//    ПРОГРАММА  ЗАПИСИ  ПОСЛЕДНЕЙ  АВАРИИ  В  FLASH-ПЗУ.

/*------------------------------------------------------------------*/

/*   Программа занесения в память i2c данных текущей аварии.
 *   Заносятся аварийные регистры сообщений и фрагмент следа из N-пульсов.
 *   Данные аварий регистрируются в памяти по замкнутому циклу в
 * пределах адресов '_i2c_av_beg+2' и '_i2c_av_end'.
 * По адресу '_i2c_av_beg' находится двухбайтный указатель конца данных
 * последней зарегистрированной аварии. Он всегда указывает на следующую,
 * после последнего занесенного байта данных аварии, свободную ячейку
 * памяти.
 *   Программа работает "методом по частям" и запускается после отработки
 * аварии и отключения следа, до Дист.Сброса.
 *   Программа возвращает:
 * - 0 - по заверешении записи;
 * - 4 - в процессе записи;
 * - 1 - при нарушении связи с i2c.
 */
word   Save_avar ( void )
{
//#ifndef _SD_Card_   
   register word    ax;//, cx ;
   lword lax, lbx, lcx;
   static lword size_i2c ;
#ifdef _SD_Card_ 
   Avar_reg_index = _Av_index_addr;
#endif   
      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i1, i2, i2_1, i2_2, i2_3, i2_4,
                 i3, i3_1, i3_2, i3_3, i3_4,
                 i4, i4_1, i4_2, i4_3, i4_4,
                     i5_1, i5_2, i5_3, i5_4,
                     i5_5, i5_6, i5_7, i5_8, i6, i7 };


    switch ( i2c_av_label )
     {
      default: i2c_av_label = i0;
      case i0:
               if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
               Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
#ifdef _SD_Card_ 
              _Adr_Flash_i2c = _SD_Addr;
#endif
                  //  Взводим перед чтением в исходное состояние
                 // указатель метки для функции xLoad_from_i2c.
               i2c_label = 0 , i2c_av_label++ ;
      case i1:
                 //   Считывание указателя адреса конца данных последней
                // зафиксированной в i2c аварии.
                 //_SizeAddr_i2c_ определяется в obj_def.h 
               ax = xLoad_from_i2c ( _SizeAddr_i2c_ , _Av_index_addr, (b*)&i2c_av_addr, _Adr_Flash_i2c ) ;
               goto read;
               
               //-----------------
      case i2 :   //  Проверка указателя: не было ли там какого-то мусора.
               if ( i2c_av_addr < _i2c_av_beg+_SizeAddr_i2c_  ||
                    i2c_av_addr > _i2c_av_end) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
               //-----------------
                 //   Запуск записи 16-ти байт регистров аварий записываемой
                 // в i2c аварии.
               av_adr_data = (b*) &msg_av ;//Reg_AvarMsgFirst ;
                 // вычисляем сколько осталось до конца i2c.
               //bx = _i2c_av_end - i2c_av_addr + 1 ;
               lax = _i2c_av_end - i2c_av_addr + 1 ;
               size_i2c = sizeof(struct MSG_reg) ;
               i2c_label = 0 , i2c_av_label = i2_3 ;
                      // переход через верхнюю границу i2c.
                 //if ( size_i2c > bx )
                 if ( size_i2c > lax )
                 {   // разбиваем запись блока на две части.
                   //size_i2c = bx ;
                   size_i2c = lax; 
                   i2c_av_label = i2_1 ;
                    // записываем одну часть блока:
    case i2_1 :    goto save ;
    case i2_2 :      // записываем вторую часть блока:
                   i2c_av_addr += size_i2c ; // подгоняем указатель i2c.
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sizeof(struct MSG_reg) - size_i2c ;
                   i2c_label = 0 , i2c_av_label = i2_3 ;
                 }
    case i2_3 :  goto save ;
    case i2_4 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                i2c_av_label = i3 ;
                break;
               //-----------------
    case i3 :
                 //   Запуск записи текущей таблицы адресов следа.
               av_adr_data = (b*) &sled ;
                 // вычисляем сколько осталось до конца i2c.
               //bx = _i2c_av_end - i2c_av_addr + 1 ;
               lax = _i2c_av_end - i2c_av_addr + 1 ;
               size_i2c = sizeof(struct SLED) ;
               i2c_label = 0 , i2c_av_label = i3_3 ;
                 if ( size_i2c > lax )
                 {
                   //size_i2c = bx ; // а в i2c будут на 2-х.
                   size_i2c = lax ; // а в i2c будут на 2-х.
                   i2c_av_label = i3_1 ;
                    // записываем одну часть блока:
    case i3_1 :    goto save ;
    case i3_2 :      // записываем вторую часть блока:
                   i2c_av_addr += size_i2c ;
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sizeof(struct SLED) - size_i2c ;
                   i2c_label = 0 , i2c_av_label = i3_3 ;
                 }
    case i3_3 :  goto save ;
    case i3_4 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                i2c_av_label = i4 ;
               break;
               //-----------------
      case i4 :
                 // Записываем фрагмент следа исходя из заданного объема
                 // записываемого фрагмента следа, независимо от того
                 // сколько колонок следа регистрировалось реально,
                 // для удобства последующего учета границ различных
                 // фрагментов следа, т.к. их размер будет одинаковым.

                   // влазит ли заданный размер страницы в i2c.
               //ax = _i2c_av_end - _i2c_av_beg + 1 - 2 ;
               lax = _i2c_av_end - _i2c_av_beg + 1 - _SizeAddr_i2c_ ;
               lbx = _i2c_av_page  ;
               if ( lbx > lax )
               {
                 sled.save_mem -= lbx-lax ;
               }

               lax = sled.save_mem ;
                   // Не больше ли заданный размер фрагмента, чем сам след?
               if( lax > _SizeSledPole )
               {
                 lax = _SizeSledPole ;
                 sled.save_mem = lax ;
               }
                 /*  Отступаем от конца следа в ОЗУ на
                  * заданное количество пульсов N к началу следа.
                  * Проверяем возможность перехода при этом через нижнюю
                  * границу области следа к ее верхней границе.
                  * Запускаем запись фрагмента следа в i2c.
                  */
               lcx = sl_d.index - lax ;
               if ( sl_d.index < lax )  lcx += _SizeSledPole ;
               av_adr_data = &SledPole[lcx] ;

                 // вычисляем сколько осталось до конца i2c.
               //bx = _i2c_av_end - i2c_av_addr + 1 ;
               lbx = _i2c_av_end - i2c_av_addr + 1 ;
                  // не переваливает ли след через свою верхнюю границу?
               if ( sl_d.index >= lax )
               {         // нет не переваливает:
                 size_i2c = sled.save_mem ; // данные следа лежат на одном отрезке,
                 i2c_label = 0 , i2c_av_label = i4_3 ;
                 //if ( size_i2c > bx )
                 if ( size_i2c > lbx )
                 {
                   size_i2c = lbx ; // а в i2c будут на 2-х.
                   i2c_av_label = i4_1 ;
                    // записываем одну часть блока:
    case i4_1 :    goto save ;
    case i4_2 :      // записываем вторую часть блока:
                   i2c_av_addr += size_i2c ;
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sled.save_mem - size_i2c ;
                   i2c_label = 0 , i2c_av_label = i4_3 ;
                 }
    case i4_3 :  goto save ;
    case i4_4 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                i2c_av_label = i6 ;
               }
               else    //  След переваливает через свою верхнюю границу:
               {      // данные следа лежат в ОЗУ  на двух отрезках.
                      // Пишем отрезок до верхней границы:
                 size_i2c = sled.save_mem - sl_d.index ;
                 i2c_label = 0 , i2c_av_label = i5_3 ;
                 //if ( size_i2c > bx )
                 if ( size_i2c > lbx )
                 {
                   //size_i2c = bx ; // и в i2c будут на 2-х.
                   size_i2c = lbx ; // и в i2c будут на 2-х.
                   i2c_av_label = i5_1 ;
                     // записываем одну часть блока:
    case i5_1 :    goto save ;
    case i5_2 :      // записываем другую часть блока:
                   i2c_av_addr += size_i2c ;
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sled.save_mem - sl_d.index - size_i2c ;
                   i2c_label = 0 , i2c_av_label = i5_3 ;
                 }
    case i5_3 :    goto save ;
    case i5_4 :
                 i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                 if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                //-----------
                   // вычисляем сколько осталось до конца i2c.
                // bx = _i2c_av_end - i2c_av_addr + 1 ;
                  lax = _i2c_av_end - i2c_av_addr + 1 ;
                     //   Пишем отрезок после верней границы, т.е. от нуля.
                 av_adr_data = &SledPole[0] ;
                 size_i2c = sl_d.index ;
                 i2c_label = 0 , i2c_av_label = i5_7 ;
                 //if ( size_i2c > bx )
                 if ( size_i2c > lax )
                 {
                   //size_i2c = bx ; //
                   size_i2c = lax ; //
                   i2c_av_label = i5_5 ;
                     // записываем одну часть блока:
    case i5_5 :    goto save ;
    case i5_6 :      // записываем другую часть блока:
                   i2c_av_addr += size_i2c ;
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sl_d.index - size_i2c ;
                   i2c_label = 0 , i2c_av_label = i5_7 ;
                 }
    case i5_7 :    goto save ;

    case i5_8 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                i2c_av_label = i6 ;
               }
               break;

               //-----------------
      case i6 :  //   Запись указателя адреса конца данных последней
                // зафиксированной в i2c аварии.
               ax = xSave_into_i2c ( _SizeAddr_i2c_ , (b*) &i2c_av_addr , _Av_index_addr , _Adr_Flash_i2c ) ;
               goto read;
      case i7 :
#ifdef _SD_Card_ 
                _Adr_Flash_i2c = _EEPROM_Addr;
#endif                   
               Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
               return 0;
               //-----------------

      //---------------------------------------------

          read:   //  Проверка кода возвращаемого п/п xLoad_from_i2c.
               if ( ax == 4 ) ;  // пока = 4 - продолжаем чтение.
               else if ( ax == 1 )
                 {
                   mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
#ifdef _SD_Card_ 
                   _Adr_Flash_i2c = _EEPROM_Addr;
#endif                   
                   Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                   return 1;
                 }
               else  i2c_av_label++ ;
               break;

          save:   //   Ожидание записи.
#ifdef _SD_Card_ 
               Avar_reg_index.addr = i2c_av_addr;
               ax = xSave_into_i2c ( size_i2c , av_adr_data , Avar_reg_index, _Adr_Flash_i2c ) ;
#else
               ax = xSave_into_i2c ( size_i2c , av_adr_data , i2c_av_addr, _Adr_Flash_i2c ) ;
#endif          
               if ( ax == 4 ) ;   // пока = 4 - запись не завершена.
               else if ( ax == 1 )
               {
                   // нарушен алгоритм связи по i2c.
                   mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
#ifdef _SD_Card_ 
                   _Adr_Flash_i2c = _EEPROM_Addr;
#endif                   
                   Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                   return 1;
               }
               else  i2c_av_label++ ;
               break;
    }
    
  return 4;
}


/*    Сервисная программа извлечения из i2c аварийных регистров сообщений
 * и фрагмента следа по заданному номеру следования аварии во времени.
 * Номер -1- состветствует последней зафиксированной аварии,
 * номер -2- состветствует предпоследней зафиксированной аварии и т.д.
 *    Данные аварий регистрируются в памяти по замкнутому циклу в
 * пределах адресов '_i2c_av_beg+2' и '_i2c_av_end'.
 * По адресу '_i2c_av_beg' находится двухбайтный указатель конца данных
 * последней зарегистрированной аварии. Он всегда указывает на на следующую,
 * после последнего занесенного байта данных аварии, свободную ячейку
 * памяти.
 */

void ReLoad_sled ( void )
{

  static   byte tst_msg ;
  register word ax;//, bx ;
  lword lax, lbx;
  static lword size_i2c ;
#ifdef _SD_Card_ 
   Avar_reg_index = _Av_index_addr;
#endif   
  
      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
      enum { i0, i1, i1_1, i1_2, i1_3, i1_4,
                 i2, i2_1, i2_2, i2_3, i2_4,
                 i3, i3_1, i3_2, i3_3, i3_4,
                 i4, i4_1, i4_2, i4_3, i4_4,
                 i5, i6 };

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
              m_index = 1 , Label = 0; // , m_ext = 0 ;
              output_s ( _ReLoadAvar_txt "\n") ;
          tst_msg = 0 ;
            // Останавливаем След.
          bo_SledStart = 0 ;
          //return ; 20.10.04 15:27
        }
       //  пока находимся в распечатке следа, острочиваем автозапуск следа.
      sl_d.time_out = Timer1_Ovr ;  //20.10.04 15:27

          //  Закончено ли восстановление данных и вкл.вывод сообщений.
      if ( tst_msg != 0 )
      {     //  Однократная установка "M_FirstCall" для "print_message".
        if ( tst_msg == 1 )  tst_msg = 2 , M_FirstCall = 1 ;
          //  Вывод восстановленных аварийных сообщений.
        print_message ( &msg_av ) ;
        return ;
      }

  switch ( Label )
    {
      default: Label = 0 ;
      case i0:     // Ожидание завершения предыдущего вывода.
              if (  TestCompleted_Output() )
                {   // вывод номера аварии предлагаемой к выборке из i2c.
                  output_s ( _ReLoad_prm ) ;
                  output_c ( m_index/10 + 0x30 ) ;// десятки.
                  output_c ( m_index%10 + 0x30 ) ;// единицы.
                  Label++ ;
                  break ;
                }
      case i1: if (  TestData_for_Input() )
                {   // вычисляем кол-во страниц в следе.
                  //ax = _i2c_av_end - _i2c_av_beg + 1 - 2 ;
                  lax = _i2c_av_end - _i2c_av_beg + 1 - _SizeAddr_i2c_ ;
                  lbx = _i2c_av_page  ;
                  if ( lbx > lax ) // влазит ли заданный размер страницы в i2c.
                  {
                    sled.save_mem -= lbx-lax ;
                    ax = 1 ;
                  }
                  else ax= lax / lbx  ;

                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
               end:   Pult_Prog_Addr = _MainPultProg ,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                    // выбор номера аварии подлежащей выборке из i2c.
                  else if ( m_ch == Up )
                    {
                      if ( ++m_index > ax ) m_index = 1 ;
                      Label-- ;
                    }
                  else if ( m_ch == Down )
                    {
                      if ( --m_index == 0 ) m_index = ax ;
                      Label-- ;
                    }    /* переход к выборке данных по выбранному номеру аварии. */
                  else if ( m_ch == Enter )
                    {
                      Label++ ;
                      output_s ( _Waiting_txt ) ;
                }   }
              break ;
            //-------------------

      case i1_1:  Prg._.Sled = 0 ;  //  ожидаем остановки следа.
                  if ( bo_SledActiv == 0 ) Label++ ;
              break ;
            //-------------------

      case i1_2:
               if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
               Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
#ifdef _SD_Card_ 
              _Adr_Flash_i2c = _SD_Addr;
#endif
              
                                               //   Запуск считывания указателя
               av_adr_data = (b*) &m_lext ;     // адреса конца данных
               i2c_av_addr =  _i2c_av_beg ;    // последней зафиксированной
               i2c_label = 0 , Label++ ;       // в i2c аварии.
               size_i2c = _SizeAddr_i2c_ ;
               break;
      case i1_3 : goto load ;  // Ожидание считывания.
               //-----------------
      case i1_4 :    //  Проверка указателя: не было ли там какого-то мусора.
               if ( m_lext < _i2c_av_beg+_SizeAddr_i2c_  ||
                    m_lext > _i2c_av_end) m_lext = _i2c_av_beg+_SizeAddr_i2c_ ;
               //-----------------

                 /*  Отступаем от конца последней аварии на
                  * заданное количество страниц к началу заданной к
                  * выборке аварии. Страница включает в себя регистры аварий
                  * и фрагмент следа заносимые при каждой регистрации аварии.
                  */
               lax = _i2c_av_page * m_index ;
               lbx =  m_lext - (_i2c_av_beg + _SizeAddr_i2c_) ;

                   //   Отступить пришлось настолько, что дошли до начала
                   // области следа и перепрыгнули на ее конец.
               if ( lax > lbx )
               {
 #ifndef _CM3_                 
                 i2c_av_addr = ((w)_i2c_av_end+1) - ( lax - lbx ) ; 
#else
                 i2c_av_addr = (_i2c_av_end+1) - ( lax - lbx ) ; 
#endif                 
               }
                   //   Отступить пришлось настолько, что не дошли до начала     
                   // области следа.
               else            i2c_av_addr = m_lext - lax ;

               //   Запуск считывания регистров аварий извлекаемой
               // из i2c аварии.
               av_adr_data = (b*) &msg_av ;//Reg_AvarMsgFirst ;
                 // вычисляем сколько осталось до конца i2c.
               lbx = _i2c_av_end - i2c_av_addr + 1 ;
               size_i2c = sizeof(struct MSG_reg) ;
               i2c_label = 0 , Label = i2_3 ;
                      // переход через верхнюю границу i2c.
                 if ( size_i2c > lbx )
                 {   // разбиваем запись блока на две части.
                   size_i2c = lbx ;
                   Label = i2_1 ;
                    // считываем одну часть блока:
    case i2_1 :    goto load ;
    case i2_2 :      // считываем вторую часть блока:
                   i2c_av_addr += size_i2c ; // подгоняем указатель i2c.
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sizeof(struct MSG_reg) - size_i2c ;
                   i2c_label = 0 , Label = i2_3 ;
                 }
    case i2_3 :  goto load ;
    case i2_4 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                Label = i3 ;
                break;
               //-----------------
    case i3 :
                 //   Запуск записи текущей таблицы адресов следа:
                //  временно считываем таблицу следа в поле следа, чтобы
                // не затереть, если там мусор, рабочую таблицу.
               //av_adr_data = (b*) &sled ;
               av_adr_data = (fb*)&SledPole[0] ;
                 // вычисляем сколько осталось до конца i2c.
               lbx = _i2c_av_end - i2c_av_addr + 1 ;
               size_i2c = sizeof(struct SLED) ;
               i2c_label = 0 , Label = i3_3 ;
                 if ( size_i2c > lbx )
                 {
                   size_i2c = lbx ; // а в i2c будут на 2-х.
                   Label = i3_1 ;
                    // считываем одну часть блока:
    case i3_1 :    goto load ;
    case i3_2 :      // считываем вторую часть блока:
                   i2c_av_addr += size_i2c ;
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+ _SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sizeof(struct SLED) - size_i2c ;
                   i2c_label = 0 , Label = i3_3 ;
                 }
    case i3_3 :  goto load ;
    case i3_4 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                    // не было-ли там какого-то мусора?
                if ( ((struct SLED*)&SledPole[0])->type == sled.type )
                {   // таблица как-будто исправна - можно переписывать.
                  sled = *(struct SLED*)&SledPole[0] ;
                }
                Label = i4 ;
               break;
      case i4 :
                 // Считываем фрагмент следа исходя из заданного объема
                 // считываемого фрагмента следа, независимо от того
                 // сколько колонок следа регистрировалось реально,
                 // для удобства последующего учета границ различных
                 // фрагментов следа, т.к. их размер будет одинаковым.

               av_adr_data = (fb*)&SledPole[0] ;
               lax = sled.save_mem ;
                   // Не больше ли заданный размер фрагмента, чем сам след?
               if( lax > _SizeSledPole )
               {
                 lax = _SizeSledPole ;
                 sled.save_mem = lax ;
               }
               sl_d.index = lax ;

                 size_i2c = sled.save_mem ; // данные следа лежат на одном отрезке,
                 i2c_label = 0 , Label = i4_3 ;
                   // вычисляем сколько осталось до конца i2c.
                 lbx = _i2c_av_end - i2c_av_addr + 1 ;
                 if ( size_i2c > lbx )
                 {
                   size_i2c = lbx ; // а в i2c будут на 2-х.
                   Label = i4_1 ;
                    // считываем одну часть блока:
    case i4_1 :    goto load ;
    case i4_2 :      // считываем вторую часть блока:
                   i2c_av_addr += size_i2c ;
                   if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
                      // Инкрементируем указатель занесения в i2c
                   av_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sled.save_mem - size_i2c ;
                   i2c_label = 0 , Label = i4_3 ;
                 }
    case i4_3 :  goto load ;
    case i4_4 :
                i2c_av_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_av_addr > _i2c_av_end ) i2c_av_addr = _i2c_av_beg+_SizeAddr_i2c_ ;
#ifdef _SD_Card_ 
                   _Adr_Flash_i2c = _EEPROM_Addr;
#endif                   
                Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                Label++ ;
               break;
      case i5 :
                   //   Находим соответствие именам из рабочей таблицы имен
                   // в const-таблице и списываем ее свежие параметры (адрес),
                   // поскольку при перезашивке адрес переменной мог измениться
                   // по-сравнению с устаревшим адресом данной переменной хранящимся в i2c.
               if ( TestSledTab () == 0 )  Label++ ;
               break;
               //-----------------
      case i6 :
               output_s ( "\n\r  Ok. \n\r" ) ;
               sl_d.print_size = sled.save_mem ;   /* Распечатываемый размер следа. */
               tst_msg = 1 ; // вкл.распечатку сообщений.
               break;
      //---------------------------------------------

          load:   //   Ожидание записи.
#ifdef _SD_Card_ 
               Avar_reg_index.addr = i2c_av_addr;               
               ax = xLoad_from_i2c ( size_i2c , Avar_reg_index , av_adr_data, _Adr_Flash_i2c ) ;
#else
               ax = xLoad_from_i2c ( size_i2c , i2c_av_addr, av_adr_data, _Adr_Flash_i2c ) ;
#endif               
               
               if ( ax == 4 ) ;   // пока = 4 - запись не завершена.
               else if ( ax == 1 )
               {      // нарушен алгоритм связи по i2c.
                   output_s ( _NoConnect_i2c_txt ) ;
#ifdef _SD_Card_ 
                   _Adr_Flash_i2c = _EEPROM_Addr;
#endif                   
                   Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                   goto end ;
               }
               else  Label++ ;
               break;
    }

 Restart_Output ()  ;

  return ;
}
