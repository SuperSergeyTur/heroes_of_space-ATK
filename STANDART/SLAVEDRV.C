
//      ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ СООБЩЕНИЙ  CAN.
//
// Время обработки прерывания "canSlaveDrive(port)" для 590-го=287-318мкс.
// Время выполнения master_full_read(write) для 1МГц и CAN-прерываниях в КТЭ
// = 987-1048мкс.

/*10.04.03 11:21#ifndef   _CAN_MASTER
//--------------------
word can_init ( byte port )
{
  can_slv_init ( port ) ;  //  инициализация переменных
  can_config ( port ) ;     //  инициализация аппаратной части

  return 0 ;
}
//--------------------
#endif  */

word  can_init ( byte port )
{
#ifdef   _CAN_MASTER
  if ( can_setting(port).config._.master== 1 )
  {
    can_mast_init ( port ) ;
  }
#endif

  can_slv_init ( port ) ;
  return  can_config ( port ) ;
}


//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
      //   Инициализация переменных для Slave.
word can_slv_init ( byte port )
{
  can_sd[port].long_io.size = 0 ;
  can_sd[port].long_io.id   = 0 ;
  can_sd[port].long_io.cmd  = 0 ;
  can_sd[port].long_io.time = 0 ;

  can_sd[port].TxBuff.in = 0 ;
  can_sd[port].TxBuff.out = 0 ;
  can_sd[port].TxBuff.num = 0 ;

  can_sd[port].canNewReceiveSlv = 0 ;
  can_sd[port].canNewSendSlv = 0 ;

//10.04.03 11:17#ifdef   _CAN_MASTER     //   Для Master.
   if ( can_setting(port).config._.master== 1 )
   {
     can_sd[port].canSlvRxBuff.new_data = 0 ;   // признак того, что буфер пуст.
   }
//10.04.03 11:17#endif

  return 0 ;
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

//  Сформировать собственный идентификатор для принятия обращений от мастера.
lword SetOwn_ID( byte port , byte address)
{
  word ax, bx ;
  register lword lax ;

//10.04.03 11:10#ifdef   _CAN_MASTER
      if ( can_setting(port).config._.master== 1 )
        {       // по количеству разрядов отведенных под сетку адреса мастера
              //  вычисляем максимальное значение адреса мастера.
          ax = (1 << can_setting(port).master_addr_size) - 1 ;
              // если заданный адрес выходит за сетку - сбрасываем его.
          if ( address > ax ) address = 0 ;

          ax = _FullAddr_Size - can_setting(port).master_addr_size ;
        }
//10.04.03 11:10#else
      else
        {       // по количеству разрядов отведенных под сетку адреса мастера
              //  вычисляем максимальное значение адреса slave.
          ax = (1 << (_FullAddr_Size-1 - can_setting(port).master_addr_size)) - 1 ;
              // если заданный адрес выходит за сетку - сбрасываем его.
          if ( address > ax ) address = 0 ;
          ax = 0 ;
        }
//10.04.03 11:10#endif
            // сдвигаем, чтобы добавить бит признака master(=1)/slave(=0).
        bx = address << 1 ;

//10.04.03 11:11#ifdef   _CAN_MASTER
      if ( can_setting(port).config._.master== 1 )  bx += 1 ;
//10.04.03 11:11#endif

        ax += 5-1 + 16 ;
        lax = (lw)bx << ax  ;

  return lax ;
}

//  Сформировать собственную маску для принятия обращений от мастера.
           /*-----------------22.11.01 11:45-------------------
            У slave маскируются только разряды адресной сетки mastera без
         бита-указателя master/slave.
            У mastera маскируются разряды адресной сетки slave и
         бит-указатель master/slave.
           --------------------------------------------------*/
lword SetOwn_Mask( byte port )
{
  word ax ;
  register lword lax ;

        ax = (1 << (_FullAddr_Size - can_setting(port).master_addr_size)) - 1 ;

//10.04.03 11:13#ifdef   _CAN_MASTER
      if ( can_setting(port).config._.master== 1 )  ax = ~ax ;
//10.04.03 11:13#endif
        lax = (lw)ax << 5 << 16 ;

  return lax ;
}
/*--------------------------------------------------------------------------*/
  //   Пример для сетки адреса мастера = 4 разряда.
  //разряды: 31 30...                           ...         ...2  1  0
       //   ЪДДВДДВДДВДДВДДВДДВДДВДДТДДВДДВДДВДДВ  ДВДДВДДВДДВДДВДДВДДї
       //ID:і10і 9і 8і 7і 6і 5і 4і 3є 2і 1і 0і xі   і xі xі xі xі xі xі
        //  АВДБДДБДДБДВБВДБВДБДДБДДРДДБДДБДВБДДБ  ДБДДБДДБДДБДДБДДБДДЩ
        //   АДДДДВДДДДЩ і  АДДДДДДДВДДДДДДДЩ
        //  адрес мастераі       адрес мастера
        //               АДДД '=0'признак обмена "мастер-slave"
        //

//  Сформировать идентификатор для обращения мастера к подчиненному.
lword SetMasterToSlave_ID( byte port, byte slave_addr )
{
  word ax, bx ;
  register lword lax ;

         // по количеству разрядов отведенных под сетку адреса мастера
        //  вычисляем максимальное значение адреса (сетку) мастера.
    ax = (1 << can_setting(port).master_addr_size) - 1 ;
        // если заданный адрес выходит за сетку - сбрасываем его.
    if ( can_setting(port).addr > ax ) can_setting(port).addr = 0 ;

          // по количеству разрядов отведенных под сетку адреса мастера
        //  вычисляем максимальное значение адреса (сетку) slave.
    bx = (1 << (_FullAddr_Size-1 - can_setting(port).master_addr_size)) - 1 ;
        // если заданный адрес выходит за сетку - сбрасываем его.
    if ( slave_addr > bx ) slave_addr = 0 ;

    lax = (w)slave_addr | ((w)can_setting(port).addr <<
                  (_FullAddr_Size - can_setting(port).master_addr_size)) ;
    lax = ( lax << 5 ) << 16 ;

//    asm_xchb( lax   ,lax+3 );
//    asm_xchb( lax+1 ,lax+2 );

  return lax ;
}

//--------------------------------------
//
//   Поиск в таблице имен заданного имени и возврат индекса позиции
// в таблице где оно найдено, либо возврат "-1" если имя не найдено.

word seek_index( byte port, char *ptr )
{
  /*register*/ char  *ptri,  *ptrj ;
               word  ax ;

  for ( ax = 0 ; ax < svar[port].size ; ax++ )
  {
    ptri = ptr,  ptrj = svar[port].tab[ax].name ;
    while ( *ptri == *ptrj )
    {   //  Проверка конца строк: закончилась одна из строк,
       //  а значит и вторая, т.к. в цикл входим по "==".
      if ( *ptri == 0 )  goto end ; //return i ; // NULL Vit-07.12.07 14:13

      ptri++, ptrj++ ;   // переход к следующей литере.
    }
  }     //  имя не найдено.
  ax = -1 ;
end:
  return ax ;    //  return -1 ;
}

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

word  canInTxBuffMsg( byte port, struct canMSG_hw *sptr )
{
  struct CAN_TxBuff  *ptr ;
  ptr = &(can_sd[port].TxBuff) ;

      /* проверить: есть ли место под новые данные в буфере вывода порта. */
  if ( ptr->num < _CanTxBuffSize )
  {
    ptr->num++ ;
                /* послать в буфер порта на вывод.  */
    ptr->msg[(w)ptr->in] = *sptr ;
    ptr->in++ ;
    if ( ptr->in >= _CanTxBuffSize ) ptr->in = 0 ;
    return 0 ;
  }
  return 1 ;
}

word  canFromTxBuffMsg( byte port )
{
  struct CAN_TxBuff  *ptr ;
  ptr = &(can_sd[port].TxBuff) ;

      /* проверить: есть ли новые данные в буфере вывода порта. */
  if ( ptr->num != 0 )
  {
                /* послать в буфер порта на вывод.  */
    if ( canSend( port , &(ptr->msg[(w)ptr->out]) ) == 0 )
    {
      ptr->num-- ;
      ptr->out++ ;
      if ( ptr->out >= _CanTxBuffSize ) ptr->out = 0 ;
      return 0 ;
    }
  }
  return 1 ;
}
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//10.04.03 11:19#ifdef   _CAN_MASTER     //   Для Master.
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

//      Буфер для сообщения типа: запрос нашему мастеру, как slave,
//  от другого мастера.
//    Занесение в slave-буфер принятого сообщения (буфер на одно сообщение).
word canInSlvBuffReceiveMsg( byte port, struct canMSG_hw *ptr )
{
         // Свободен ли буфер для новых данных?
  if ( can_sd[port].canSlvRxBuff.new_data == 1 ) return 0 ; // еще не освобожден.
    can_sd[port].canSlvRxBuff.new_data = 1 ;    // признак того, что появились новые данные.
    can_sd[port].canSlvRxBuff.msg = *ptr ; // заносим в буфер сообщение.
  return 1 ;
}

//    Извлечение из slave-буфера принятого сообщения для обработки.
word canFromSlvBuffReceiveMsg( byte port, struct canMSG_hw *ptr )
{
  if ( can_setting(port).config._.master== 1 )
  {      // Есть ли в буфере новые данные?
    if ( can_sd[port].canSlvRxBuff.new_data == 0 ) return 0 ; // еще нет.
      can_sd[port].canSlvRxBuff.new_data = 0 ;    // признак того, что буфер освобожден.
      *ptr = can_sd[port].canSlvRxBuff.msg ; // считываем из буфера сообщение.
    return 1 ;
  }
  else
    return canReceive( port , ptr )  ;
}

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//10.04.03 11:19#else
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

//10.04.03 11:20#define canFromSlvBuffReceiveMsg( port, rptr ) \
//                               canReceive( port , rptr )

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//10.04.03 11:19#endif
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

word canSlaveDrive( byte port )
{
  //static struct  canMSG_hw rmsg, smsg ;

  register word    ax, bx, cx ;
  register byte    ah , r_dlen , s_dlen ;
  static   byte    count[_Num_CAN_Ports] ;
  register void   *ptr ;
  struct  CAN_slave_data register *dptr ;
  _x_far const struct namevar  register *vptr ;

   //   Структура для преобразования отдельных байт в слово,
   // в длинное слово и наоборот.
  register union lax_ax_b  buff ;

  canFromTxBuffMsg( port ) ;
        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
  dptr = &can_sd[port] ;
  vptr = svar[port].tab ;

            // Проверка: не истекло ли время таймаута на высвобождение блока
          // длинной записи.
          //   Если кто-то занял блок и не обращается к нему более N-секунд
          // блок высвобождается для других абонентов.
        if ( dptr->long_io.size != 0 ) // занят ли блок?
        {
          if ( (u)((w)(Timer1_Ovr-dptr->long_io.time)) > _TimeOut_long_io ) dptr->long_io.size=0 ;
        }

//----------------------------------------------------------------------------

         // появились ли новые данные?
  count[port] = 0 ;
  while ( canFromSlvBuffReceiveMsg( port, &dptr->rmsg ) != 0 )
  {
         //04.11.04 15:04
     //ax = canFromSlvBuffReceiveMsg( port, &dptr->rmsg )  ;
     //if ( ax == 0 ) return 1 ;

//----------------------------------------------------------------------------

        // считываем для раскомпоновки кода команды с порядковым номером посылки.
     dptr->cmd.all = dptr->rmsg.data[0] ;
     dptr->cmd._.rqst = 0 ;// сбрасываем бит запроса, на случай ответа мастер-мастеру.
     r_dlen  = dptr->rmsg.cfg.dlen ;
             // сразу записываем 'id' в ответнон сообщение,
            // т.к. следующем проходе dptr->rmsg' может затереться.
     dptr->smsg.id = dptr->rmsg.id ;
     switch ( dptr->cmd._.cmd )
     {
       default:  dptr->smsg.data[1]  = _Err_COMMAND ; //расшифровка ОШИБКИ.
               goto err;

 //  ПРОДОЛЖЕНИЕ ЗАПИСИ/ЧТЕНИЯ ПО НЕЗАВЕРШЕННОЙ КОМАНДЕ
       case _Continue_OpCode:
                       //  если блок свободен, значит команде "продолжение
                      // чтения" не предшествовала ком. "начало чтения".
                   if ( dptr->long_io.size == 0 )
                   {
                     dptr->smsg.data[1] = _Err_CONTINUE ;
                      goto err;
                   }
                   else  // Блок длинной записи занят: занят этим же
                   {     // мастером ?
                     if ( dptr->long_io.id == dptr->rmsg.id )
                     {     // заполняем/расшифровываем сообщение очередной порции данных.
                       for ( bx = 1 ; bx < 8 && dptr->long_io.size > 0; bx++ )
                       {
                         dptr->long_io.size-- ;
                         switch ( dptr->long_io.cmd )
                         {
                           case _Read_OpCode:
                               dptr->smsg.data[bx] = *(dptr->long_io.addr++) ;
                             break;

                           case _Write_OpCode:
                               *(dptr->long_io.addr++) = dptr->rmsg.data[bx] ;
                             break;
                         }
                       }
                       if ( dptr->long_io.size == 0 )
                       {  // СОХРАНЯЯ в ответе ПОРЯДКОВЫЙ НОМЕР посылки,
                         dptr->cmd._.cmd = dptr->long_io.cmd ; // ДОБАВЛЯЕМ в него код ОПЕРАЦИИ.
                       }
                       else dptr->cmd._.cmd = _Continue_OpCode ;

                       //dptr->smsg.data[0] = dptr->cmd.all  ;
                       s_dlen = bx ;
                      //--  отсрочка отсчета time-out на высвобождение блока длинной записи.
                       dptr->long_io.time = Timer1_Ovr ;
                     }
                     else
                     {   // блок занят - мастеру следует повторить запрос.
                       dptr->smsg.data[1]  = _Err_WAIT ;
                       goto err;
                     }
                   }
         break;

 //  ЗАПРОС ДЕСКРИПТОРА МАСТЕРОМ   //------------
       case _Descript_OpCode: //Запрос дескриптора по имени.

            ax = dptr->rmsg.data[1] ;
               // не выходит ли дескриптор за размер 6-ти символов.
            if ( ax > _canName_max_size )
            {
              dptr->smsg.data[1] = _Err_NAME_SIZE ; //расшифровка ОШИБКИ.
              goto err;
            }
              dptr->canName_buff[ax] = 0 ; // оформляем конец стринга имени.
            for ( ax-- ; (sw)ax >= 0 ; ax-- )// копируем имя в буфер, чтобы его кто-то не затер.
            {
              dptr->canName_buff[ax] = dptr->rmsg.data[2+ax]  ;
            }
                  //dptr->rmsg.data[2+ax] = 0 ;// оформляем конец стринга имени.
            ax = seek_index( port, dptr->canName_buff ) ;
               // имя не найдено.
            if ( (sw)ax == -1 )
            {
              dptr->smsg.data[1] = _Err_NAME ; //расшифровка ОШИБКИ.
        err:
                 // СОХРАНЯЯ в ответе ПОРЯДКОВЫЙ НОМЕР посылки,
              dptr->cmd._.cmd = _Error_OpCode ; // ДОБАВЛЯЕМ в него код ОШИБКИ.
              //dptr->smsg.data[0] = dptr->cmd.all  ;
              s_dlen = 2 ;
            }
            else
            {
              //dptr->smsg.data[0] =dptr->rmsg.data[0] ;
              dptr->smsg.data[1] = ax;
              dptr->smsg.data[2] = vptr[ax].access;
              dptr->smsg.data[3] = vptr[ax].type;
              dptr->smsg.data[4] = vptr[ax].lon;
              dptr->smsg.data[5] = vptr[ax].lon>>8;
              dptr->smsg.data[6] = (w)vptr[ax].nom;
              dptr->smsg.data[7] = (w)vptr[ax].nom>>8;
              s_dlen = 8 ;
            }
       break;
 //  ЗАПРОС ИМЕНИ ПЕРЕМЕННОЙ МАСТЕРОМ //------------
       case _VarName_OpCode: //Запрос имени по дескриптору.

               // не выходит ли дескриптор за размер таблицы.
            if ( dptr->rmsg.data[1] >= svar[port].size )
            {
              dptr->smsg.data[1]  = _Err_DESCRIPT ; //расшифровка ОШИБКИ.
              goto err;
            }
               // Упаковываем имя переменной в объект сообщения.
            for ( ax = 2, bx = 0 ;  ; ax++, bx++ )
            {  //  влазит ли имя в сообщение - миксимум 6 символов..
              if ( ax > 8 )// " > 8 " т.к. нужен еще один оборот цикла,
              {            // чтобы проверить конец строки.
                dptr->smsg.data[1] = _Err_NAME_SIZE ; //расшифровка ОШИБКИ.
                goto err;
              }
              ah = vptr[dptr->rmsg.data[1]].name[bx] ;
              if ( ah != 0 ) dptr->smsg.data[ax] = ah ;// проверяем конец имени.
              else  break ;                            // NULL Vit-07.12.07 14:17
            }
            dptr->smsg.data[1] = bx;
            s_dlen = ax ;

       break;
 // ЗАПРОС ДАННЫХ МАСТЕРОМ   //------------
       case _Read_OpCode: //Чтение по дескриптору.

          for ( cx = 1, bx = 1 ; cx < r_dlen ; )
          {      // считывание i-того дескриптора.
            ax = dptr->rmsg.data[cx++] ;
               // не выходит ли дескриптор за размер таблицы.
            //if ( (sw)ax >= _SizeVarTable )
            if ( ax >= svar[port].size )
            {
              dptr->smsg.data[1]  = _Err_DESCRIPT ; //расшифровка ОШИБКИ.
              goto err;
         len: dptr->smsg.data[1]  = _Err_DATA_LENGHT ; //расшифровка ОШИБКИ.
              goto err;
            }
            else
            {     // используется прямая или косвенная адресация?
              if (( vptr[ax].type & _Indirect_type) != 0 )
                     ptr = *(void **)vptr[ax].addr ;// косвенная адресация.
              else   ptr =  vptr[ax].addr ;
              switch ( vptr[ax].type & ~_Indirect_type )
              {
               case _CHAR_type :
                   if ( bx+1 > 8 ) goto len ;
                   dptr->smsg.data[bx+0] = *(b*)ptr;
                   bx += 1 ;
                   break;

               case _SHORT_type:
               case _INT_type:
                   if ( bx+2 > 8 ) goto len ;
                   buff.ax = *(w*)ptr ;
                   dptr->smsg.data[bx+0] = buff.ax      ;
                   dptr->smsg.data[bx+1] = buff.ax >> 8 ;
                   bx += 2 ;
                   break;

               case _LONG_type :
                   if ( bx+4 > 8 ) goto len ;
                   buff.lax = *(lw*)ptr ;
                   dptr->smsg.data[bx+0] = buff.lax      ;
                   dptr->smsg.data[bx+1] = buff.lax >> 8 ;
                   dptr->smsg.data[bx+2] = buff.lax >>16 ;
                   dptr->smsg.data[bx+3] = buff.lax >>24 ;
                   bx += 4 ;
                   break;

            #ifdef   _CAN_FLOAT_VAR
               case _FLOAT_type :
                   if ( bx+4 > 8 ) goto len ;
                   buff.flt = *(float*)ptr ;
                   dptr->smsg.data[bx+0] = buff.lax      ;
                   dptr->smsg.data[bx+1] = buff.lax >> 8 ;
                   dptr->smsg.data[bx+2] = buff.lax >>16 ;
                   dptr->smsg.data[bx+3] = buff.lax >>24 ;
                   bx += 4 ;
                   break;
            #endif

               case _CHAR_array_type :
                      // блок длинной записи свободен.
                   if ( dptr->long_io.size == 0 )
                   {    // с командой может передаваться и смещение
                       // относительно начала массива для возможности
                       // продолжения записи с того же места при сбое передачи.
                     buff.ax = 0 ;

                     if ( r_dlen > 2 )
                     {
                       buff.ax = (w)dptr->rmsg.data[2] +
                                ((w)dptr->rmsg.data[3] << 8) ;
                         // не слишком велико ли смещение.
                       if ( vptr[ax].lon < buff.ax )
                       {
                         dptr->smsg.data[1]  = _Err_DATA_LENGHT ;
                         goto err;
                       }
                     }
                     cx = r_dlen ;// чтобы истек внешний цикл.

                      // задаем стартовые параметры блока
                      // используется прямая или косвенная адресация?
              if (( vptr[ax].type & _Indirect_type) != 0 )
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                   dptr->long_io.addr = (b*)((lw)*(void **)vptr[ax].addr+buff.ax) ;   // косвенная адресация.
              else dptr->long_io.addr = (b*)((lw)vptr[ax].addr+buff.ax) ;
#else
                   dptr->long_io.addr = (b*)((w)*(void **)vptr[ax].addr+buff.ax) ;   // косвенная адресация.
              else dptr->long_io.addr = (b*)((w)vptr[ax].addr+buff.ax) ;
#endif
                     dptr->long_io.size = vptr[ax].lon-buff.ax ;
                     dptr->long_io.id   = dptr->rmsg.id ;
                     dptr->long_io.cmd  = _Read_OpCode ;

                       // отсылаем размер передаваемого массива.
                     dptr->smsg.data[bx+0] = dptr->long_io.size;
                     dptr->smsg.data[bx+1] = dptr->long_io.size>>8;
                     bx += 2 ;

                      // СОХРАНЯЯ в ответе ПОРЯДКОВЫЙ НОМЕР посылки,
                     // ДОБАВЛЯЕМ в него код КОМАНДЫ.
                     dptr->cmd._.cmd = _Continue_OpCode ;

                     //--  отсрочка отсчета time-out на высвобождение блока длинной записи.
                     dptr->long_io.time = Timer1_Ovr ;

                   }   // Блок длинной записи занят, может этим же
                      // мастером и по этому же дескриптору.
                   else
                   {   // блок занят - мастеру следует повторить запрос.
                     dptr->smsg.data[1]  = _Err_WAIT ;
                     goto err;
                   }
                   break;
                //======================

               default:  dptr->smsg.data[1]  = _Err_TYPE ; //расшифровка ОШИБКИ.
                         goto err;
             }
           }
         }
        // dptr->smsg.data[0] = dptr->cmd.all  ;
         s_dlen = bx ;
       break;
         //------------
 // ЗАПИСЬ ДАННЫХ МАСТЕРОМ   //------------
       case _QuickWrite_OpCode: //Запись по дескриптору без подтверждающего ответа.
       case _Write_OpCode: //Запись по дескриптору.

         for ( cx = 1, bx=1 ; cx < r_dlen ; )
         {     // считывание i-того дескриптора.
           ax = dptr->rmsg.data[cx++] ;

              // не выходит ли дескриптор за размер таблицы.
           //if ( (sw)ax >= _SizeVarTable )
           if ( ax >= svar[port].size )
           {
             dptr->smsg.data[1]  = _Err_DESCRIPT ; //расшифровка ОШИБКИ.
             goto err;
       len1: dptr->smsg.data[1]  = _Err_DATA_LENGHT ; //расшифровка ОШИБКИ.
             goto err;
           }
           else
           {
               //  Разрешен ли доступ на запись для данной переменной.
             if ( vptr[ax].access != _READ_WRITE_access )
             {
               dptr->smsg.data[1]  = _Err_ACCESS ;
               goto err;
             }
                  // перекладываем содержимое переменной в сообщение.
                 // используется прямая или косвенная адресация?
             if (( vptr[ax].type & _Indirect_type) != 0 )
                    ptr = *(void **)vptr[ax].addr ;// косвенная адресация.
             else   ptr =  vptr[ax].addr ;
             switch ( vptr[ax].type & ~_Indirect_type )
             {
              case _CHAR_type :
                   if ( cx+1 > r_dlen ) goto len1 ;
                 *(b*)ptr = dptr->rmsg.data[cx+0] ;
                   cx += 1 ;
                 break;

              case _SHORT_type:
              case _INT_type:
                   if ( cx+2 > r_dlen ) goto len1 ;
                 buff.ax = (w)dptr->rmsg.data[cx+0] +
                          ((w)dptr->rmsg.data[cx+1] << 8) ;
                 *(w*)ptr = buff.ax ;
                   cx += 2 ;
                 break;

              case _LONG_type :
                   if ( cx+4 > r_dlen ) goto len1 ;
                 buff.lax = (lw)(w)dptr->rmsg.data[cx+0]       +
                           ((lw)(w)dptr->rmsg.data[cx+1] << 8) +
                           ((lw)(w)dptr->rmsg.data[cx+2] <<16) +
                           ((lw)(w)dptr->rmsg.data[cx+3] <<24) ;
                 *(lw*)ptr = buff.lax ;
                   cx += 4 ;
                 break;

          #ifdef   _CAN_FLOAT_VAR
              case _FLOAT_type :
                   if ( cx+4 > r_dlen ) goto len1 ;
                 buff.flt = (lw)(w)dptr->rmsg.data[cx+0]       +
                           ((lw)(w)dptr->rmsg.data[cx+1] << 8) +
                           ((lw)(w)dptr->rmsg.data[cx+2] <<16) +
                           ((lw)(w)dptr->rmsg.data[cx+3] <<24) ;
                 *(float*)ptr = buff.flt ;
                   cx += 4 ;
                 break;
          #endif

               case _CHAR_array_type :
                      // блок длинной записи свободен.
                   if ( dptr->long_io.size == 0 )
                   {    // с командой может передаваться и смещение
                       // относительно начала массива для возможности
                       // продолжения записи с того же места при сбое передачи.
                     buff.ax = 0 ;

                     if ( r_dlen > 2 )
                     {
                       buff.ax = (w)dptr->rmsg.data[2] +
                                ((w)dptr->rmsg.data[3] << 8) ;
                         // не слишком велико ли смещение.
                       if ( vptr[ax].lon < buff.ax )
                       {
                         dptr->smsg.data[1]  = _Err_DATA_LENGHT ;
                         goto err;
                       }
                     }
                     cx = r_dlen ;// чтобы истек внешний цикл.

                      // задаем стартовые параметры блока
                      // используется прямая или косвенная адресация?
              if (( vptr[ax].type & _Indirect_type) != 0 )
#if defined (_24_BITS_) ||  defined (_32_BITS_)
                   dptr->long_io.addr = (b*)((lw)*(void **)vptr[ax].addr+buff.ax) ;   // косвенная адресация.
              else dptr->long_io.addr = (b*)((lw)vptr[ax].addr+buff.ax) ;
#else
                   dptr->long_io.addr = (b*)((w)*(void **)vptr[ax].addr+buff.ax) ;   // косвенная адресация.
              else dptr->long_io.addr = (b*)((w)vptr[ax].addr+buff.ax) ;
#endif
                     dptr->long_io.size = vptr[ax].lon-buff.ax ;
                     dptr->long_io.id   = dptr->rmsg.id ;
                     dptr->long_io.cmd  = _Write_OpCode ;

                       // отсылаем размер передаваемого массива.
                     dptr->smsg.data[bx+0] = dptr->long_io.size;
                     dptr->smsg.data[bx+1] = dptr->long_io.size>>8;
                     bx += 2 ; // увеличиваем длину посылки.

                      // СОХРАНЯЯ в ответе ПОРЯДКОВЫЙ НОМЕР посылки,
                     // ДОБАВЛЯЕМ в него код КОМАНДЫ.
                     dptr->cmd._.cmd = _Continue_OpCode ;

                     //--  отсрочка отсчета time-out на высвобождение блока длинной записи.
                     dptr->long_io.time = Timer1_Ovr ;

                   }   // Блок длинной записи занят, может этим же
                      // мастером и по этому же дескриптору.
                   else
                   {   // блок занят - мастеру следует повторить запрос.
                     dptr->smsg.data[1]  = _Err_WAIT ;
                     goto err;
                   }
                   break;
                //======================

               default:  dptr->smsg.data[1]  = _Err_TYPE ; //расшифровка ОШИБКИ.
                         goto err;
             }
           }
         }
       //  dptr->smsg.data[0] = dptr->rmsg.data[0] ;
         s_dlen = bx ;
       break;
         //------------
       case _Version_OpCode: //Запрос возможностей абонента.

         dptr->smsg.data[1] = _Version_code;
         dptr->smsg.data[2] = svar[port].size ;
         s_dlen = 3 ;
       break;
         //------------
       case _Break_OpCode: //Прерывание операции.

         switch ( dptr->rmsg.data[1] )
         {
           default: ; //Прерывание передачи массива.
           case _Break_array :  dptr->long_io.size = 0 ;
         }
         s_dlen = 1 ;
       break;
     } //end switch

         // При записи без ответа не отсылаем ответ.
          // считываем ИСХОДНЫЙ код команды
    if ((*(union MSG_CMD*)(b*)&(dptr->rmsg.data[0]))._.cmd != _QuickWrite_OpCode)
    {
      dptr->smsg.data[0] = dptr->cmd.all  ;
    //dptr->smsg.id = dptr->rmsg.id ;   // перенесено в начало функции.
    //11.04.03 13:30dptr->smsg.cfg.dir = 1 ;
      dptr->smsg.cfg.dlen = s_dlen ;

      canInTxBuffMsg( port, &dptr->smsg ) ;
      canFromTxBuffMsg( port ) ;
    }
    //--------
        // чтобы не сидеть здесь бесконечно при большом потоке данных.
    if ( ++count[port] >= 3 ) break ;
  }        //------------

               //если NewDat вновь установлен, - возможно было
               //наложение старой и новой информации
               // if ((can_msg15con1 & 0x03) == 0x02 ) goto povtor_read_MO15;
   return 0 ;
}
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
#ifdef   _CAN_MASTER
  #ifdef _CAN_SLAVE_IRQ
    Работа Мастера и CAN-прерываний не предусматривается.09.08.06 14:20
  #endif
#endif
//---------------------------------------------------------------------------
//     Комплексная Slave-функция.
//
word can_slave ( byte port )
{
  if ( can_test( port ) != 0 ) return _Err_CAN_controller ;

#ifdef   _CAN_MASTER
  if ( can_setting(port).config._.master== 1 )  Receive_Monitor( port ) ;
 #endif

#ifndef _CAN_SLAVE_IRQ
  return  canSlaveDrive( port ) ;
#else
  return 0;
#endif
}

//----------------------------------------------------------------------------

