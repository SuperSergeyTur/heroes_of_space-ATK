
//---------------------------------------------------------------------------
//  Инициализация аппаратной части CAN и таблицы карточек абонентов.
//  0 - хорошо,
//  1 - не хорошо.
/*10.04.03 11:23word  can_init ( byte port )
{
  can_mast_init ( port ) ;
  can_slv_init ( port ) ;
  return  can_config ( port ) ;
} */

//---------------------------------------------------------------------------
//  Инициализация программных переменных.

word  can_mast_init ( byte port )
{
   can_md[port].n_call = 0 ;
   can_md[port].read_label = 0, can_md[port].write_label = 0 ;
   can_md[port].dscr_label = 0;
   can_md[port].varn_label = 0, can_md[port].break_label = 0 ;
   can_md[port].canMsrRxBuff.new_data = 0 ;   // признак того, что буфер пуст.

  return 0 ;
}

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
  // ОТСЧЕТ ЗАДЕРЖКИ МЕТОДОМ ПО ЧАСТЯМ.
  // Для совместимости отсчета задержки BorlandC c CBuilder.
word xSleep( char num, struct Sleep_data *ptr, short Ntime )
{
        // инициализация
  if ( num == 0 )
  {
#ifndef _PCL841
    ptr->time = timer1 ;
#else
    ptr->time = 0 ;
#endif
    ptr->n_time = 0 ;
  }
  else  // отсчет.
  {      //  Отсчет одной мсек.
#ifndef _PCL841
    while( (w)(timer1-ptr->time) >= _MkSec( 1000 ) )// на случай если пока мы
    {                              // были из вне функции прошло более 1й мсек.
      ptr->time += _MkSec( 1000 ) ;
      ptr->n_time++ ;
    }
#else
    Sleep ( 1.0 ) ;
    ptr->n_time++ ;
#endif
        //  отсчет n-мсек.
    if ( ptr->n_time >= Ntime ) return 1 ;//отсчет завершен.
  }
  return 0 ;  //отсчет не завершен.
}
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

#define  canInMsrBuffSendMsg( port, sptr ) \
                       canSend( port , sptr )

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//      Буфер для сообщения типа: ответ нашему мастеру от slave или от мастера,
//  который отвечает как slave.
//    Занесение в мастер-буфер принятого сообщения (буфер на одно сообщение).
word  canInMsrBuffReceiveMsg( byte port, struct canMSG_hw *ptr )
{
         // Свободен ли буфер для новых данных?
  if ( can_md[port].canMsrRxBuff.new_data == 1 ) return 0 ; // еще не освобожден.
    can_md[port].canMsrRxBuff.new_data = 1 ;    // признак того, что появились новые данные.
    can_md[port].canMsrRxBuff.msg = *ptr ; // заносим в буфер сообщение.
  return 1 ;
}

//    Извлечение из мастер-буфера принятого сообщения для обработки.
word canFromMsrBuffReceiveMsg( byte port, struct canMSG_hw *ptr )
{
         // Есть ли в буфере новые данные?
  if ( can_md[port].canMsrRxBuff.new_data == 0 ) return 0 ; // еще нет.
    can_md[port].canMsrRxBuff.new_data = 0 ;    // признак того, что буфер освобожден.
    *ptr = can_md[port].canMsrRxBuff.msg ; // считываем из буфера сообщение.
  return 1 ;
}

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

   //   Тестируем принятое сообщение: ответ от абонента,
   //  либо запрос/ответ от мастера.
   //   Возвращает: "0" - при бите-признаке = "мастер-slave";
   //               "1" - при бите-признаке = "мастер-мастер";
   //
word  test_receive_msg( byte port, struct canMSG_hw *ptr )
{
  word ax ;
  register lword lax ;

        // разворачиваем ID.
    lax = ptr->id ;
//    asm_xchb( lax   ,lax+3 );
//    asm_xchb( lax+1 ,lax+2 );

          // по количеству разрядов отведенных под сетку адреса мастера
     //  вычисляем номер битов-признака посылки 'запрос/ответ мастер-мастер'.
    ax = _FullAddr_Size-1 - can_setting(port).master_addr_size ;
    lax >>= 16+5+ax ;
            //  выделяем эти биты.
  return (w)lax & 0x01 ;
}

/*--------------------------------------------------------------------------*/
  //   Пример для сетки ID отправляемого от мастера к мастеру.
  //разряды: 31 30...                           ...         ...2  1  0
       //   ЪДДВДДВДДВДДВДДВДДВДДВДДТДДВДДВДДВДДВ  ДВДДВДДВДДВДДВДДВДДї
       //ID:і10і 9і 8і 7і 6і 5і 4і 3є 2і 1і 0і xі   і xі xі xі xі xі xі
        //  АВДБДДБДДБДВБВДБВДБДДБДДРДДБДДБДВБДДБ  ДБДДБДДБДДБДДБДДБДДЩ
        //   АДДДДВДДДДЩ і  АДДДДДДДВДДДДДДДЩ
        //  адрес мастераі   адрес мастера отправителя
        //    приемника  АДДД '=1'признак обмена "мастер-мастер"
        //

//  Сформировать идентификатор для обращения мастера к мастера.
lword SetMasterToMaster_ID( byte port, byte master2_addr )
{
  word ax, bx ;
  register lword lax ;

         // по количеству разрядов отведенных под сетку адреса мастера
        //  вычисляем максимальное значение адреса (сетку) мастера.
    ax = (1 << can_setting(port).master_addr_size) - 1 ;
        // если заданный адрес выходит за сетку - сбрасываем его.
    if ( can_setting(port).addr > ax ) can_setting(port).addr = 0 ;
    if ( master2_addr > ax ) master2_addr = 0 ;

          // вычисляем маску бита признака "мастер-мастер".
    bx = 1 << (_FullAddr_Size-1 - can_setting(port).master_addr_size) ;

    lax =  (w)can_setting(port).addr | bx | ((w)master2_addr <<
                    (_FullAddr_Size - can_setting(port).master_addr_size)) ;
    lax = ( lax << 5 ) << 16 ;

  //  asm_xchb( lax   ,lax+3 );
  //  asm_xchb( lax+1 ,lax+2 );

  return lax ;
}
   //   Переворачивает ID принятый от мастера, чтобы прийти к его
   // отправному виду.
   //
word  correct_master_id ( byte port, struct canMSG_hw *ptr )
{
  word ax, bx ;
  register lword lax ;
/*
        // разворачиваем ID.
    lax = ptr->id ;
    //asm_xchb( lax   ,lax+3 );
    //asm_xchb( lax+1 ,lax+2 );

         // по количеству разрядов отведенных под сетку адреса мастера
        //  вычисляем максимальное значение адреса (сетку) мастера.
    ax = (1 << can_setting(port).master_addr_size) - 1 ;

       // выделяем адрес мастера от которого пришло сообщение.
    lax = ( lax >> 5 ) >> 16 ; // сдвигаем ID к нулю.
    ax = (w)lax & ax ; //  срезаем лишние биты.
            //  формируем отправной ID.
    ptr->id = SetMasterToMaster_ID( port, ax )  ;
  */

  lax = ptr->id;// полученный ID
  lax = ( lax >> 5 ) >> 16 ; //

  ax = (1 << can_setting(port).master_addr_size) - 1; // маска сетки

  bx = (w)lax & ax ; // адрес получателя, который станет адресом отправителя
  lax = lax >> (_FullAddr_Size - can_setting(port).master_addr_size);

  ax = (w)lax & ax ; // адрес отправителя, который станет адресом получателя
// укладываем в ID алрес получателя и отправителя
  lax = ( bx << (_FullAddr_Size - can_setting(port).master_addr_size)) | ax ;
// добавляем бит запроса мастер-мастер
  lax = lax | ( 1 << (_FullAddr_Size - can_setting(port).master_addr_size - 1));
  lax = ( lax << 5 ) << 16 ;
  ptr->id = lax ;

  return 0 ;
}

//---------------------------------------------------------------------------

word Receive_Monitor( byte port )
{
  word ax ;
  union MSG_CMD  rcmd ;

      //  Получено ли какое-либо сообщение.
  if ( canReceive( port , &monitor_rmsg[port] ) == 1 )
  {      // Получен запрос от мастера или ответ от slave?
         //    помещаем его в тот или иной буфер.
    ax = test_receive_msg( port, &monitor_rmsg[port] ) ;
    if ( ax == 1 )
    {    //  поскольку при обмене между мастерами ID при ответе
         // переворачивается, то приводим его к состоянию "отправка".
      correct_master_id( port, &monitor_rmsg[port] ) ; // переворачиваем id либо для ответа мастеру,
                              // либо для контроля у себя правильности ответа.
      rcmd.all = monitor_rmsg[port].data[0] ;
          //  Это запрос или ответ на запрос.
      if ( rcmd._.rqst == 1 )  // запрос нашему мастеру, как slave, от другого мастера.
      {
        canInSlvBuffReceiveMsg( port, &monitor_rmsg[port] ) ;
      }
      else   // ответ нашему мастеру от мастера, который отвечает как slave.
      {
        canInMsrBuffReceiveMsg( port, &monitor_rmsg[port] ) ;
    } }
    else
    {
      canInMsrBuffReceiveMsg( port, &monitor_rmsg[port] ) ; // ответ мастеру от slave.
    }
    return 1 ;
  }

  return 0 ;
}

//---------------------------------------------------------------------------
//ііііііііііііііііііііііііііііііііііііі
//    Функция посылает запрос на сообщение и ожидает получения ответа
// именно с тем идентификатором, что и запрос.
//    Функция имеет тайм-аут на запрос и прием.
//  dscr[] - таблица дескрипторов, должна заканчиваться кодом '0xFF'.
//
// Нельзя смешивать незавершенные вызовы master_read() и вызовы
//  master_full_read().
//
word master_full_read( char *dscr, struct Abonent_form *ptr )
{
  word ax ;
  do
  {
    
    if ( can_test( ptr->port ) != 0 ) return _Err_CAN_controller ;
    Receive_Monitor( ptr->port ) ;
    canSlaveDrive( ptr->port ) ; 
   
    ax = master_read( dscr, ptr, 0 ) ;
    
  }
  while ( ax == _NoErr_TimeOut ) ;

  return ax ;
}
//---------
word master_read(  char *dscr, struct Abonent_form *ptr, byte num_call )
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    word  ret_code ;
    struct canMSG_hw rmsg;
    union MSG_CMD  rcmd ;
   //   Структура для преобразования отдельных байт в слово,
   // в длинное слово и наоборот.
    union lax_ax_b  buff ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &read_data[ptr->port] ;
    md = &can_md[ptr->port] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засориться
////// если на шине идет обмен.

          //  Если порт отключился,  включаем его снова.
// Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->read_label != 0 && md->n_call != num_call )  
    {
      return _NoErr_TimeOut;
    }
      md->n_call = (int)num_call ; // для тайм-аута.

    switch ( md->read_label )
    {
      case 0 :

      //can_test( port ); /* Put CAN1,2 to normal mode */

          // ФОРМИРУЕМ СООБЩЕНИЕ.

          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = _Read_OpCode ;
        p->scmd._.code = p->code++ ;

                //  Задаем адрес назначения.
      if ( ptr->cfg._.master == 0 )
             p->smsg.id = SetMasterToSlave_ID( ptr->port, ptr->ab_addr )  ;
      else
      {
        p->scmd._.rqst = 1 ;
        p->smsg.id = SetMasterToMaster_ID( ptr->port, ptr->ab_addr )  ;
      }

      for ( p->i = 0, p->ax = 1, p->bx = 1 ; dscr[p->i] != (char)0xff ; p->i++ )
      {     //  не выходит ли дескриптор за рамки таблицы.
        if ( dscr[p->i] >= ptr->size_var_tab )   return _Err_DscrSize ;

             //  запрашивался ли ранее дескриптор для данной переменной.
        if ( ptr->var_tab[dscr[p->i]].tag == 0 )
        {   // дескриптор не запрашивался - следует запросить его по имени.
case 2 :  md->read_label = 0 ; // если надо - его снова установят ниже.
          p->tst = read_dscr( dscr[p->i], ptr, num_call ) ;
          if ( p->tst == _NoErr_TimeOut ) md->read_label = 2 ; // чтобы снова сюда вернуться.
          if ( p->tst != 0 )  return p->tst ;
        }
//  Влазит ли количество заданных идентификаторов в сообщение.
        if ( p->ax > 7 ) return _Err_DscrNumber ;


             //    ВЫДЕЛЯЕМ ЗАПРОС НА МАССИВ.
            //  Запрещается задавать запрос массива в сочетании с чем-то еще.
        if (( ptr->var_tab[dscr[p->i]].type & ~_Indirect_type) == _CHAR_array_type )
        {     //  были ли заданы уже какие-то идентификаторы.
          if ( p->i != 0 )            return _Err_NonCompatiblType ;
              //  остались ли в списке еще какие-то идентификаторы.
          if ( dscr[1] != (char)0xff ) return _Err_NonCompatiblType ;

          if ( ptr->long_io.size == 0 )
          {      // инициализируем блок длинной записи.
            p->smsg.data[1] = ptr->var_tab[dscr[p->i]].dscr ;
            p->ax += 1 ;
            p->bx += 2 ; // в ответ получим 2-х байтный размер массива.
          }
          else  // Блок длинной записи занят: занят этими же командой и
          {     // переменной из перечня переменных абонента?
            if ( ptr->long_io.cmd == p->scmd._.cmd &&
                              ptr->long_io.dscr == dscr[p->i] )//p->smsg.data[p->ax] )
            {     //  При продолжении записи массива код команды передается,
           // как код ПРОДОЛЖЕНИЯ записи.
              if ( ptr->long_io.repeat == 0 )// нет ли признака сбоя передачи массива.
              {
                p->scmd._.cmd  = _Continue_OpCode ;
              }
              else // Был сбой передачи массива: запрашиваем его снова, но
              {  // уже с той точки до которой он был передан.
                 // Прерываем в контроллере передачу массива,
                 // чтобы начать все снова.
      case 3 :  md->read_label = 0 ; // если надо - его снова установят ниже.
                p->tst = master_break( ptr, _Break_array, num_call );
                if ( p->tst == _NoErr_TimeOut ) md->read_label = 3 ; // чтобы снова сюда вернуться.
                if ( p->tst != 0 )  return p->tst;

                   // задаем смещение в передачу массива,
                  // вычисляем: сколько байт было передано успешно.
                p->tst = ptr->long_io.beg_size - ptr->long_io.size;
                p->smsg.data[1] = ptr->var_tab[dscr[p->i]].dscr;
                p->smsg.data[2] = p->tst;      // передаем смещение от начала
                p->smsg.data[3] = p->tst >> 8; // массива.
                p->ax += 3 ;
                p->bx += 2 ; // в ответ получим 2-х байтный размер массива.
                break ;
              }
            }
               // блок занят - мастеру следует повторить запрос.
            else  return  _Err_Wait;
               //  вычисляем длину ответного сообщения на этот запрос.
            p->bx += ptr->long_io.size;
            if ( p->bx > 8 ) p->bx = 8;
          }
          break;
        }
        else
        {        //  Влезут ли данные в ответное сообщение на этот запрос.
          p->bx += ptr->var_tab[dscr[p->i]].lon;
          if ( p->bx > 8 ) return _Err_DscrDataNumber;
          p->smsg.data[p->ax++] = ptr->var_tab[dscr[p->i]].dscr;
      } }

      p->smsg.data[0] = p->scmd.all;    // записываем окончательный код команды.
      p->smsg.cfg.dlen    = p->ax ;
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;

      p->time = 0 ; // для "time_out"
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
  case 4 :
      md->read_label = 0 ;
      
	    // посылаем сообщение.
      if ( canInMsrBuffSendMsg( ptr->port, &p->smsg ) != 0 )
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        //if ( p->time <= mTime_out( ptr->port ))
        if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 0 )  // отсчет задержки.
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          md->read_label = 4 ;
          //09.04.06 00:39can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          if ( (ptr->var_tab[dscr[0]].type & ~_Indirect_type) == _CHAR_array_type )
          {    // если обрыв передачи произошел при передаче массива,
            ptr->long_io.repeat = 1 ;  // взводим признак.
          }
          ptr->err.send++ ;
          return _Err_Send ;
      } }
    // ********

	  // ожидаем ответа на запрос.
      //for ( p->tst = 0, p->time = 0 ;; )
      p->tst = 0, p->time = 0 ;
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
      {   // при первом входе не проверяем наличие ответа - нет смысла.
        goto tout ;
case 1 : md->read_label = 0 ; // если надо будет - его снова взведут ниже.
        if ( canFromMsrBuffReceiveMsg( ptr->port, &rmsg) == 1)
          {      // от своего ли абонента получили сообщение?
            if ( rmsg.id == p->smsg.id )
            {     // считываем код команды.
              rcmd.all = rmsg.data[0] ;
             // со своим ли порядковым номером получили ответ.
            if ( rcmd._.code == p->scmd._.code )
            {    // не ошибкой ли ответил абонент, если ошибкой, то
                 // возвращаем ее в старшем байте кода.
              if ( rcmd._.cmd == _Error_OpCode )
              {
                ret_code = rmsg.data[1]*(w)256;
                goto ret;
              }
                 // код своей ли команды получили,
              if ( rcmd._.cmd == _Read_OpCode  ||
                     // или код продолжения команды.
                   rcmd._.cmd == _Continue_OpCode ) // надо конкретизир.
              // что этот код можно присылать только в ответ на длинное сооб.
              {    // такой ли длины мы ожидали получить сообщение.
                if ( rmsg.cfg.dlen != p->bx )
                {
                  ret_code = _Err_AnswLong;
                  goto ret;
                }
                  // расшифровываем ответное сообщение.
                for ( p->i = 0, p->bx = 1 ; dscr[p->i] != (char)0xff ; p->i++ )//, p->ax++ )
                {
                    switch ( ptr->var_tab[dscr[p->i]].type & ~_Indirect_type )
                    {
                      case _CHAR_type :
                          *(b*)ptr->var_tab[dscr[p->i]].addr = rmsg.data[p->bx++];
                          break;

                      case _SHORT_type:
                      case _INT_type:
                          buff.ax  = (w)rmsg.data[p->bx++];
                          buff.ax += (w)rmsg.data[p->bx++] << 8 ;
                          *(w*)ptr->var_tab[dscr[p->i]].addr = buff.ax ;
                          break;

                      case _LONG_type :
                          buff.lax  = (lw)(w)rmsg.data[p->bx++] ;
                          buff.lax += (lw)(w)rmsg.data[p->bx++] << 8 ;
                          buff.lax += (lw)(w)rmsg.data[p->bx++] << 16 ;
                          buff.lax += (lw)(w)rmsg.data[p->bx++] << 24 ;
                          *(lw*)ptr->var_tab[dscr[p->i]].addr = buff.lax ;
                          break;

                  #ifdef   _CAN_FLOAT_VAR
                      case _FLOAT_type :
                          buff.b[0] = rmsg.data[p->bx++] ;
                          buff.b[1] = rmsg.data[p->bx++] ;
                          buff.b[2] = rmsg.data[p->bx++] ;
                          buff.b[3] = rmsg.data[p->bx++] ;
                          *(float*)ptr->var_tab[dscr[p->i]].addr = buff.flt ;
                          break;
                  #endif

                      case _CHAR_array_type :
                              // проинициализирован ли блок передачи.
                          if ( ptr->long_io.size == 0 )
                          {      // инициализируем блок длинной записи.
                            ptr->long_io.addr = (char*)ptr->var_tab[dscr[p->i]].addr ;
                            ptr->long_io.size = (w)rmsg.data[1]+(w)rmsg.data[2]*256;
                            ptr->long_io.cmd  = p->scmd._.cmd ;
                            ptr->long_io.dscr = dscr[0] ;
                            ptr->long_io.beg_size = ptr->long_io.size ;
                            ptr->long_io.repeat = 0 ;
                          }     // нет ли признака сбоя передачи массива.
                          else if ( ptr->long_io.repeat != 0 )
                          {    // проверяем - сохранилось ли равенство массивов.
                           // if ( ptr->long_io.size !=
                             //  (w)rmsg.data[1]+(w)rmsg.data[2]*256 ) return _Err_ArraySize ;
                            ptr->long_io.repeat = 0 ;
                          }
                          else
                          {
                            for ( ; rmsg.cfg.dlen > 1 ; rmsg.cfg.dlen-- )
                            {    // данные должны закончиться синхронно с длиной сообщения.
                              if ( ptr->long_io.size <= 0 )
                              {
                                ret_code = _Err_ArraySize;
                                goto ret;
                              }
                              ptr->long_io.size-- ;
                              *(ptr->long_io.addr++) = rmsg.data[p->bx++] ;
                            }
                          }       // Получили код продолжения команды:
                          if ( rcmd._.cmd == _Continue_OpCode )
                          {
                          // и данные еще не истекли - нормально.
                            if ( ptr->long_io.size != 0 )  return _NoErr_Continue ;
                          // а данные уже истекли - не нормально.
                            else
                              {
                                ret_code = _Err_ArraySize;
                                goto ret;
                              }
                          }
                               // Получили код своей команды - признак завершения записи.
                          if ( rcmd._.cmd == _Read_OpCode )
                          {
                          // а данные еще не истекли - не нормально.
                            if ( ptr->long_io.size != 0 )
                            {   //"=0"- устанавливаем признак завершения длинной записи.
                              ptr->long_io.size = 0 ;
                              ret_code = _Err_ArraySize;
                              goto ret;
                          } }

                          break;

                      default:  ret_code = _Err_Type ; // неизвестный тип данных.
                                goto ret;
                    }
                  }
                  return 0 ;
              } }
            } }
               //   отсчет time_out. - с еще одним заходом проверки
              //  приема по истечении времени.
          if ( p->tst == 1 )
          {
            ret_code = _Err_Receive ; //311
        ret:
            if ( (ptr->var_tab[dscr[0]].type & ~_Indirect_type) == _CHAR_array_type )
            {    // если обрыв передачи произошел при передаче массива,
              ptr->long_io.repeat = 1 ;  // взводим признак.
            }
            ptr->err.receive++ ;
            //ptr->var_tab[dscr[p->i]].tag = 0;
            return ret_code ; //311
          }
          else
          {
            //Sleep ( 1.0 ) ; // задержка на 1мсек.
            //if ( p->time > mTime_out( ptr->port ) ) p->tst = 1 ;
            //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
            if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 1 ) p->tst = 1 ; // отсчет задержки.
      tout: md->read_label = 1 ;
            return _NoErr_TimeOut;
          }
    }  }
  return 0 ;
}
//#########################

//---------------------------------------------------------------------------
//
// Нельзя смешивать незавершенные вызовы master_write() и вызовы
//  master_full_write().
//

word master_full_write( char *dscr, struct Abonent_form *ptr )
{
  word ax ;
  do
  {
    if ( can_test( ptr->port ) != 0 ) return _Err_CAN_controller ;
    Receive_Monitor( ptr->port ) ;
    canSlaveDrive( ptr->port ) ;
    ax = master_write( dscr, ptr, 0 ) ;
  }
  while ( ax == _NoErr_TimeOut ) ;

  return ax ;
}
//----------
     // Функция записи может быть как с подтверждающим ответом, так и без:
     //   master_xwrite( _Write_OpCode, ... )      - с ответом.
     //   master_xwrite( _QuickWrite_OpCode, ... ) - без ответа.
word master_xwrite( char OpCode, char *dscr, struct Abonent_form *ptr, byte num_call)
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    word  ret_code ;
    struct canMSG_hw rmsg;
    union MSG_CMD  rcmd ;
   //   Структура для преобразования отдельных байт в слово,
   // в длинное слово и наоборот.
    union lax_ax_b  buff ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &write_data[ptr->port] ;
    md = &can_md[ptr->port] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засоритьс
////// если на шине идет обмен.

// Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->write_label != 0 && md->n_call != num_call )  return _NoErr_TimeOut;
      md->n_call = num_call ; // для тайм-аута.

    switch ( md->write_label )
    {
      case 3 : goto case3 ;
      case 0 :
//  Если порт отключился,  включаем его снова.
      //can_test( port ); /* Put CAN1,2 to normal mode */

            // ФОРМИРУЕМ СООБЩЕНИЕ.

          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = OpCode ; //_Write_OpCode ;
        p->scmd._.code = p->code++ ;

                //  Задаем адрес назначения.
      if ( ptr->cfg._.master == 0 )
             p->smsg.id = SetMasterToSlave_ID( ptr->port, ptr->ab_addr )  ;
      else
      {
        p->scmd._.rqst = 1 ;
        p->smsg.id = SetMasterToMaster_ID( ptr->port, ptr->ab_addr )  ;
      }

      for ( p->i = 0, p->ax = 1 ; dscr[p->i] != (char)0xff ; p->i++ )
      {     //  не выходит ли дескриптор за рамки таблицы.
        if ( dscr[p->i] >= ptr->size_var_tab )   return _Err_DscrSize ;

             //  запрашивался ли ранее дескриптор для данной переменной.
        if ( ptr->var_tab[dscr[p->i]].tag == 0 )
        {   // дескриптор не запрашивался - следует запросить его по имени.
  case 2 :  md->write_label = 0 ; // ?б<Ё - эR - ??R б-Rч  гбв -Rчпв -Ёі?.
          p->tst = read_dscr( dscr[p->i], ptr, num_call ) ;
          if ( p->tst == _NoErr_TimeOut ) md->write_label = 2 ; // звRцл б-Rч  боэ  ч?а-гвмбп.
          if ( p->tst != 0 )  return p->tst ;
        }
           //  Разрешен ли доступ на запись для данной переменной.
       if (ptr->var_tab[dscr[p->i]].access != _READ_WRITE_access )
                                                            return  _Err_Access ;

           //  Влазит ли заданный идентификатор и его данные в сообщение.
       if ( (ptr->var_tab[dscr[p->i]].type & ~_Indirect_type) != _CHAR_array_type )
       {
         if ( p->ax+1+ptr->var_tab[dscr[p->i]].lon > 8 ) return _Err_DscrDataNumber ;
         p->smsg.data[p->ax++] = ptr->var_tab[dscr[p->i]].dscr ;
       }


       switch ( ptr->var_tab[dscr[p->i]].type & ~_Indirect_type )
       {
        case _CHAR_type :
            p->smsg.data[p->ax++] = *(b*)(ptr->var_tab[dscr[p->i]].addr) ;
            break;

        case _SHORT_type:
        case _INT_type:
            buff.ax = *(w*)(ptr->var_tab[dscr[p->i]].addr) ;
            p->smsg.data[p->ax++] = buff.ax      ;
            p->smsg.data[p->ax++] = buff.ax >> 8 ;
            break;

        case _LONG_type :
            buff.lax = *(lw*)(ptr->var_tab[dscr[p->i]].addr) ;
            p->smsg.data[p->ax++] = buff.lax      ;
            p->smsg.data[p->ax++] = buff.lax >> 8 ;
            p->smsg.data[p->ax++] = buff.lax >>16 ;
            p->smsg.data[p->ax++] = buff.lax >>24 ;
            break;

      #ifdef   _CAN_FLOAT_VAR
        case _FLOAT_type :
            buff.flt = *(float*)(ptr->var_tab[dscr[p->i]].addr) ;
            p->smsg.data[p->ax++] = buff.b[0];
            p->smsg.data[p->ax++] = buff.b[1];
            p->smsg.data[p->ax++] = buff.b[2];
            p->smsg.data[p->ax++] = buff.b[3];
            break;
      #endif

        case _CHAR_array_type :
                //  были ли заданы уже какие-то идентификаторы.
            if ( p->i != 0 )            return _Err_NonCompatiblType ;
                //  остались ли в списке еще какие-то идентификаторы.
            if ( dscr[1] != (char)0xff ) return _Err_NonCompatiblType ;

            if ( ptr->long_io.size == 0 )
            {     // дескриптор посылаем однократно с первой посылкой.
              p->smsg.data[p->ax++] = ptr->var_tab[dscr[p->i]].dscr ;
                  // инициализируем блок длинной записи.
             // ptr->long_io.addr = (char*)ptr->var_tab[dscr[i]].addr ;
             // ptr->long_io.size = ptr->var_tab[dscr[i]].lon ;
             // ptr->long_io.cmd  = p->scmd._.cmd ;
             // ptr->long_io.dscr = dscr[i] ;
            }
            else  // Блок длинной записи занят: занят этой же
            {     // переменной из перечня переменных абонента?
            if ( ptr->long_io.cmd == p->scmd._.cmd &&
                              ptr->long_io.dscr == dscr[p->i] )
            {     //  При продолжении записи массива код команды передается,
           // как код ПРОДОЛЖЕНИЯ записи.
              if ( ptr->long_io.repeat == 0 )// нет ли признака сбоя передачи массива.
              {     //  При продолжении записи массива код команды передается,
                   // как код ПРОДОЛЖЕНИЯ записи.
                p->scmd._.cmd  = _Continue_OpCode ;

                for ( ; p->ax < 8 && ptr->long_io.size > 0; p->ax++ )
                {
                  ptr->long_io.size-- ;
                  p->smsg.data[p->ax] = *(ptr->long_io.addr++) ;
                }
              }
              else // Был сбой передачи массива: запрашиваем его снова, но
              {  // уже с той точки до которой он был передан.
                 // Прерываем в контроллере передачу массива,
                 // чтобы начать все снова.
         case3: md->write_label = 0 ; // ?б<Ё - эR - ??R б-Rч  гбв -Rчпв -Ёі?.
                p->tst = master_break( ptr, _Break_array, num_call );
                if ( p->tst == _NoErr_TimeOut ) md->write_label = 3 ; // звRцл б-Rч  боэ  ч?а-гвмбп.
                if ( p->tst != 0 )  return p->tst;

                   // задаем смещение в передачу массива,
                  // вычисляем: сколько байт было передано успешно.
                p->tst = ptr->long_io.beg_size - ptr->long_io.size;
                p->smsg.data[1] = ptr->var_tab[dscr[p->i]].dscr;
                p->smsg.data[2] = p->tst;      // передаем смещение от начала
                p->smsg.data[3] = p->tst >> 8; // массива.
                p->ax += 3 ;
              //  p->bx += 2 ; // в ответ получим 2-х байтный размер массива.
              }
            }
                 // блок занят - мастеру следует повторить запрос.
              else  return  _Err_Wait ;
            }
            break;
          //==============
        default:  return _Err_Type ; //расшифровка ОШИБКИ.
       }
      }

      p->smsg.data[0] = p->scmd.all  ;

      p->smsg.cfg.dlen    = p->ax ;
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;
    // ********
      p->time = 0 ; // для "time_out"
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
  case 4 :
      md->write_label = 0 ;
	    // посылаем сообщение.
      if ( canInMsrBuffSendMsg( ptr->port, &p->smsg ) != 0 )//   return _Err_Send ;
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        //if ( p->time <= mTime_out( ptr->port ))
        if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 0 )  // отсчет задержки.
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          md->write_label = 4 ;
          //09.04.06 00:40can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          if ( (ptr->var_tab[dscr[0]].type & ~_Indirect_type) == _CHAR_array_type )
          {    // если обрыв передачи произошел при передаче массива,
            ptr->long_io.repeat = 1 ;  // взводим признак.
          }
          ptr->err.send++ ;
          return _Err_Send ;
        }
      }    // при записи без ответа не ожидаем ответа.
      else if ( OpCode == _QuickWrite_OpCode )  return 0 ;
    // ********

	  // ожидаем ответа на запрос.
      //for ( p->tst = 0, p->time = 0 ;; )
      p->tst = 0, p->time = 0 ;
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
      {   // при первом входе не проверяем наличие ответа - нет смысла.
        goto tout ;
  case 1 : md->write_label = 0 ; // если надо будет - его снова взведут ниже.
        if ( canFromMsrBuffReceiveMsg( ptr->port, &rmsg) == 1)
          {      // от своего ли абонента получили сообщение?
            if ( rmsg.id == p->smsg.id )
            {     // считываем код команды.
              rcmd.all = rmsg.data[0] ;
                   // со своим ли порядковым номером получили ответ.
              if ( rcmd._.code == p->scmd._.code )
              {      // не ошибкой ли ответил абонент, если ошибкой, то
                    // возвращаем ее в старшем байте кода.
                if ( rcmd._.cmd == _Error_OpCode )
                {
                  ret_code = rmsg.data[1]*(w)256 ;
                  goto ret;
                }
                    // ждем ответа на обычную или длинную запись.
                if ( (ptr->var_tab[dscr[0]].type & ~_Indirect_type) == _CHAR_array_type )
                {     // если это ответ на первый запрос, то:
                  if ( ptr->long_io.size == 0 && p->scmd._.cmd == _Write_OpCode )
                  {   // инициализируем блок длинной записи.
                    ptr->long_io.addr = (char*)ptr->var_tab[dscr[0]].addr ;
                    ptr->long_io.size = (w)rmsg.data[1]+(w)rmsg.data[2]*256;
                    ptr->long_io.cmd  = p->scmd._.cmd ;
                    ptr->long_io.dscr = dscr[0] ;
                    ptr->long_io.beg_size = ptr->long_io.size ;
                    ptr->long_io.repeat = 0 ;
                  }     // нет ли признака сбоя передачи массива.
                  else if ( ptr->long_io.repeat != 0 )
                  {    // проверяем - сохранилось ли равенство массивов.
                    ptr->long_io.repeat = 0 ;
                  }
                       // Получили код продолжения команды:
                  if ( rcmd._.cmd == _Continue_OpCode )
                  {     // и данные еще не истекли - нормально.
                    if ( ptr->long_io.size != 0 )  return _NoErr_Continue ;
                        // а данные уже истекли - не нормально.
                    else
                    {
                      ret_code = _Err_ArraySize ;
                      goto ret;
                    }
                  }
                       // Получили код своей команды - признак завершения записи.
                  if ( rcmd._.cmd == _Write_OpCode )
                  {     // а данные еще не истекли - не нормально.
                    if ( ptr->long_io.size != 0 )
                    {   //"=0"- устанавливаем признак завершения длинной записи.
                      ptr->long_io.size = 0 ;
                      ret_code = _Err_ArraySize ;
                      goto ret;
                    }
                    else return 0 ;
                  }
                }
                else   // код своей ли команды получили,
                    if ( rcmd._.cmd == _Write_OpCode )  return 0 ;
        } } }
               //   отсчет time_out. - с еще одним заходом проверки
              //  приема по истечении времени.
        if ( p->tst == 1 )
        {
          ret_code = _Err_Receive ;
      ret:
          if ( (ptr->var_tab[dscr[0]].type & ~_Indirect_type) == _CHAR_array_type )
          {    // если обрыв передачи произошел при передаче массива,
            ptr->long_io.repeat = 1 ;  // взводим признак.
          }
          ptr->err.receive++ ;
          return ret_code ; //311
        }
        else
        {
            //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if ( p->time > mTime_out( ptr->port )) p->tst = 1 ;
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 1 ) p->tst = 1 ; // отсчет задержки.
    tout: md->write_label = 1 ;
          return _NoErr_TimeOut;
        }
    } }
  return 0 ;
}
//#########################

//---------------------------------------------------------------------------

word read_dscr( byte dscr, struct Abonent_form *ptr, byte num_call )
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    struct canMSG_hw rmsg;
    word i ;
    union MSG_CMD  rcmd ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &dscr_data[ptr->port] ;
    md = &can_md[ptr->port] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засоритьс
////// если на шине идет обмен.

        // Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->dscr_label != 0 && md->n_call != num_call )  return _NoErr_TimeOut;
      md->n_call = num_call ; // для тайм-аута.

    switch ( md->dscr_label )
    {
      case 0 :
           //  Если порт отключился,  включаем его снова.
      //can_test( port ); /* Put CAN1,2 to normal mode */

             // Формируем сообщение.

            //  не выходит ли дескриптор за рамки таблицы.
        if ( dscr >= ptr->size_var_tab )   return _Err_DscrSize ;

             //  сбрасываем признак наличия дескриптора для данной переменной.
        ptr->var_tab[dscr].tag = 0 ;
            //   Копируем имя из таблицы в посылаемый объект сообщения.
        for ( i = 0 ; ptr->var_tab[dscr].name[i] != 0 ; i++ )
        {
          p->smsg.data[i+2] = ptr->var_tab[dscr].name[i] ;
           //  Влазит ли длина имени в одно сообщение.
          if ( i+2 > 7 ) return _Err_NameSize ;
        }

          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = _Descript_OpCode ;
        p->scmd._.code = p->code++ ;

      p->smsg.data[1] = i ;    // длина имени.
      p->smsg.cfg.dlen    = i+2 ;  // общая длина посылки.
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;
                //  Задаем адрес назначения.
      if ( ptr->cfg._.master == 0 )
             p->smsg.id = SetMasterToSlave_ID( ptr->port, ptr->ab_addr )  ;
      else
      {
        p->scmd._.rqst = 1 ;
        p->smsg.id = SetMasterToMaster_ID( ptr->port, ptr->ab_addr )  ;
      }

      p->smsg.data[0] = p->scmd.all  ;

    // ********
      p->time = 0 ; // для "time_out"
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
  case 4 :
      md->dscr_label = 0 ;
	    // посылаем сообщение.
      if ( canInMsrBuffSendMsg( ptr->port, &p->smsg ) != 0 ) //  return _Err_Send ;
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        //if ( p->time <= mTime_out( ptr->port ))
        if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 0 )  // отсчет задержки.
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          md->dscr_label = 4 ;
          //09.04.06 00:40can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          ptr->err.send++ ;
          return _Err_Send ;
      } }
    // ********

          // ожидаем ответа на запрос.
        //for ( p->tst = 0, p->time = 0 ;; )
        p->tst = 0, p->time = 0 ;
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
        {   // при первом входе не проверяем наличие ответа - нет смысла.
          goto tout ;
  case 1 : md->dscr_label = 0 ; // ?б<Ё - эR цгэ?в - ??R б-Rч  чч?эгв -Ёі?.
          if ( canFromMsrBuffReceiveMsg( ptr->port, &rmsg) == 1)
            {      // от своего ли абонента получили сообщение?
              if ( rmsg.id == p->smsg.id )
              {     // считываем код команды.
                rcmd.all = rmsg.data[0] ;
                     // со своим ли порядковым номером получили ответ.
              if ( rcmd._.code == p->scmd._.code )
              {     // не ошибкой ли ответил абонент, если ошибкой, то
                   // возвращаем ее в старшем байте кода.
                if ( rcmd._.cmd == _Error_OpCode ) return rmsg.data[1]*(w)256  ;
                   // код своей ли команды получили.
                if ( rcmd._.cmd == p->scmd._.cmd )
                {    // такой ли длины мы ожидали получить сообщение.
                  if ( rmsg.cfg.dlen != 8 ) return _Err_AnswLong ;

                     //  устанавливаем признак наличия дескриптора для данной переменной.
                  ptr->var_tab[dscr].tag = _Descript_tag ;
                    // расшифровываем сообщение.
                         //  дескриптор
                  ptr->var_tab[dscr].dscr   = rmsg.data[1] ;
                         //  код доступа
                  ptr->var_tab[dscr].access = rmsg.data[2] ;
                         //  код типа
                  ptr->var_tab[dscr].type   = rmsg.data[3] ;
                         //  код длины данных
                  ptr->var_tab[dscr].lon = (w)rmsg.data[4]+(w)rmsg.data[5]*256;
                    /*  адрес переменной в его адресном пространстве абонента */
                  ptr->var_tab[dscr].nom = (w)rmsg.data[6]+(w)rmsg.data[7]*256;

                  break ;
              } }
            } }
               //   отсчет time_out. - с еще одним заходом проверки
              //  приема по истечении времени.
        if ( p->tst == 1 )
        {
          ptr->err.receive++ ;
          return _Err_Receive ; //311
        }
        else
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if ( p->time > mTime_out( ptr->port )) p->tst = 1 ;
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 1 ) p->tst = 1 ; // отсчет задержки.
    tout: md->dscr_label = 1 ;
          return _NoErr_TimeOut;
        }
    } }

  return 0;
}
//---------------------------------------------------------------------------
//----------------------------------------------
//  Прочитать имя переменной контроллера с заданным дескриптором.
//  адрес "*ptr" - должен указывать на заранее зарезервированную память
// размером не менее чем для шести символов и завершающего строку нуля.

word can_read_var_name( struct Abonent_form *ptr, byte dscr, char *cptr, byte num_call )
{
  if ( can_test( ptr->port ) != 0 ) return _Err_CAN_controller ;
  Receive_Monitor( ptr->port ) ;
    canSlaveDrive( ptr->port ) ;
  return  read_var_name( ptr, dscr, cptr, num_call ) ;
}
//----------
word read_var_name( struct Abonent_form *ptr, byte dscr, char *cptr, byte num_call )
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    struct canMSG_hw rmsg;
    word i ;
    union MSG_CMD  rcmd ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &read_var_data[ptr->port] ;
    md = &can_md[ptr->port] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засоритьс
////// если на шине идет обмен.
// Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->varn_label != 0 && md->n_call != num_call )  return _NoErr_TimeOut;
      md->n_call = num_call ; // для тайм-аута.

    switch ( md->varn_label )
    {
      case 0 :
//  Если порт отключился,  включаем его снова.
      //can_test( port ); /* Put CAN1,2 to normal mode */

             // Формируем сообщение.

          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = _VarName_OpCode ;
        p->scmd._.code = p->code++ ;

      p->smsg.data[1] = dscr ;    // номер переменной.
      p->smsg.cfg.dlen    = 2 ;  // общая длина посылки.
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;
                //  Задаем адрес назначения.
      if ( ptr->cfg._.master == 0 )
             p->smsg.id = SetMasterToSlave_ID( ptr->port, ptr->ab_addr )  ;
      else
      {
        p->scmd._.rqst = 1 ;
        p->smsg.id = SetMasterToMaster_ID( ptr->port, ptr->ab_addr )  ;
      }

      p->smsg.data[0] = p->scmd.all  ;

    // ********
      p->time = 0 ; // для "time_out"
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
  case 4 :
      md->varn_label = 0 ;
	    // посылаем сообщение.
      if ( canInMsrBuffSendMsg( ptr->port, &p->smsg ) != 0 )
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        //if ( p->time <= mTime_out( ptr->port ))
        if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 0 )  // отсчет задержки.
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          md->varn_label = 4 ;
          //09.04.06 00:40can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          ptr->err.send++ ;
          return _Err_Send ;
      } }
    // ********

          // ожидаем ответа на запрос.
        //for ( p->tst = 0, p->time = 0 ;; )
        p->tst = 0, p->time = 0 ;
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
        {   // при первом входе не проверяем наличие ответа - нет смысла.
          goto tout ;
  case 1 : md->varn_label = 0 ; // ?б<Ё - эR цгэ?в - ??R б-Rч  чч?эгв -Ёі?.
          if ( canFromMsrBuffReceiveMsg( ptr->port, &rmsg) == 1)
            {      // от своего ли абонента получили сообщение?
              if ( rmsg.id == p->smsg.id )
              {     // считываем код команды.
                rcmd.all = rmsg.data[0] ;
                     // со своим ли порядковым номером получили ответ.
              if ( rcmd._.code == p->scmd._.code )
              {     // не ошибкой ли ответил абонент, если ошибкой, то
                   // возвращаем ее в старшем байте кода.
                if ( rcmd._.cmd == _Error_OpCode ) return rmsg.data[1]*(w)256  ;
                   // код своей ли команды получили.
                if ( rcmd._.cmd == p->scmd._.cmd )
                {    // Не выходит ли длина имени за размер 6-ти символов.
                  if ( rmsg.data[1] > 6 ) return _Err_NameSize  ;

                      //   Копируем имя из принятого объекта сообщения в указатель.
                  for (i = 0 ; i < rmsg.data[1] ; i++) cptr[i] = rmsg.data[i+2] ;
                  cptr[i] = 0 ;//NULL ;
                  break ;
              } }
            } }
               //   отсчет time_out. - с еще одним заходом проверки
              //  приема по истечении времени.
        if ( p->tst == 1 )
        {
          ptr->err.receive++ ;
          return _Err_Receive ; //311
        }
        else
        {
            //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if ( p->time > mTime_out( ptr->port )) p->tst = 1 ;
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 1 ) p->tst = 1 ; // отсчет задержки.
    tout: md->varn_label = 1 ;
          return _NoErr_TimeOut;
        }
    } }

  return 0;
}

//---------------------------------------------------------------------------
//----------------------------------------------
//   Послать в контроллер команду с расшифровкой команды, например,
// прервать передачу массива.

word master_break( struct Abonent_form *ptr, byte cmd, byte num_call )
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    struct canMSG_hw rmsg ;
    union MSG_CMD  rcmd ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &break_data[ptr->port] ;
    md = &can_md[ptr->port] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засоритьс
////// если на шине идет обмен.

        // Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->break_label != 0 && md->n_call != num_call )  return _NoErr_TimeOut;
      md->n_call = num_call ; // для тайм-аута.

    switch ( md->break_label )
    {
      case 0 :
           //  Если порт отключился,  включаем его снова.
      //can_test( port ); /* Put CAN1,2 to normal mode */

             // Формируем сообщение.

          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = _Break_OpCode ;
        p->scmd._.code = p->code++ ;

      p->smsg.data[1] = cmd ;    // номер переменной.
      p->smsg.cfg.dlen    = 2 ;  // общая длина посылки.
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;
                //  Задаем адрес назначения.
      if ( ptr->cfg._.master == 0 )
             p->smsg.id = SetMasterToSlave_ID( ptr->port, ptr->ab_addr )  ;
      else
      {
        p->scmd._.rqst = 1 ;
        p->smsg.id = SetMasterToMaster_ID( ptr->port, ptr->ab_addr )  ;
      }

      p->smsg.data[0] = p->scmd.all  ;

    // ********
      p->time = 0 ; // для "time_out"
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
  case 4 :
      md->break_label = 0 ;
	    // посылаем сообщение.
      if ( canInMsrBuffSendMsg( ptr->port, &p->smsg ) != 0 ) //  return _Err_Send ;
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        //if ( p->time <= mTime_out( ptr->port ))
        if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 0 )  // отсчет задержки.
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          md->break_label = 4 ;
          //09.04.06 00:40can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          ptr->err.send++ ;
          return _Err_Send ;
      } }
    // ********

          // ожидаем ответа на запрос.
        //for ( p->tst = 0, p->time = 0 ;; )
        p->tst = 0, p->time = 0 ;
      xSleep ( 0, &(md->slpd),  0 ) ; // инициализация отсчета задержки.
        {   // при первом входе не проверяем наличие ответа - нет смысла.
          goto tout ;
  case 1 : md->break_label = 0 ; // ?б<Ё - эR цгэ?в - ??R б-Rч  чч?эгв -Ёі?.
          if ( canFromMsrBuffReceiveMsg( ptr->port, &rmsg) == 1)
            {      // от своего ли абонента получили сообщение?
              if ( rmsg.id == p->smsg.id )
              {     // считываем код команды.
                rcmd.all = rmsg.data[0] ;
                     // со своим ли порядковым номером получили ответ.
                if ( rcmd._.code == p->scmd._.code )
                {     // не ошибкой ли ответил абонент, если ошибкой, то
                     // возвращаем ее в старшем байте кода.
                  if ( rcmd._.cmd == _Error_OpCode ) return rmsg.data[1]*(w)256  ;
                     // код своей ли команды получили.
                  if ( rcmd._.cmd == p->scmd._.cmd )  break ;
                }
            } }
               //   отсчет time_out. - с еще одним заходом проверки
              //  приема по истечении времени.
        if ( p->tst == 1 )// return _Err_Receive ; //311
        {
          ptr->err.receive++ ;
          return _Err_Receive ; //311
        }
        else
        {
            //Sleep ( 1.0 ) ; // задержка на 1мсек.
          //if ( p->time > mTime_out( ptr->port )) p->tst = 1 ;
          //if(xSleep ( 1, &(md->slpd),  1 )) p->time++; // отсчет задержки.
          if(xSleep ( 1, &(md->slpd),  mTime_out( ptr->port )) == 1 ) p->tst = 1 ; // отсчет задержки.
    tout: md->break_label = 1 ;
          return _NoErr_TimeOut;
        }
    } }

  return 0;
}
