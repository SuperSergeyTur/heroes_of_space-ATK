
//---------------------------------------------------------------------------
//  Инициализация программных переменных.

word  micro_master_init ( word code )
{
    word ax ;
   lword id ;
   const struct MICRO_MASTER  *ptr ;

  switch ( code )
  {
    default:
       for ( ax = 0 ; ax < _Num_Micro_Master ; ax++ )
       {
         ptr = &Micro_tab[ax] ;
         //-------
         can_md[ax].n_call = 0 ;
         can_md[ax].read_label  = 0, can_md[ax].write_label = 0 ;
         can_md[ax].err.receive = 0, can_md[ax].err.send = 0 ;

         id = SetMasterToSlave_ID( ptr->port, *(ptr->sl_addr) )  ;
         xInit_msg( 's', ptr->port, ptr->obj_w, id ) ;
         xInit_msg( 'r', ptr->port, ptr->obj_r, id ) ;
       }
    break;
 }
  return 0 ;
}
//---------------------------------------------------------------------------
        //????????  нужен ли num_call
word micro_master_read( const struct MICRO_MASTER *ptr, byte num_call )
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    register byte ah ;
    word  ret_code ;
    struct canMSG_hw rmsg;
    union MSG_CMD  rcmd ;
   //   Структура для преобразования отдельных байт в слово,
   // в длинное слово и наоборот.
    union lax_ax_b  buff ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &read_data[ptr->abonent_num] ;
    md = &can_md[ptr->abonent_num] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засориться
////// если на шине идет обмен.

          //  Если порт отключился,  включаем его снова.
// Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->read_label != 0 && md->n_call != num_call )  return _NoErr_TimeOut;
      md->n_call = num_call ; // для тайм-аута.

    switch ( md->read_label )
    {
      case 0 :// ФОРМИРУЕМ СООБЩЕНИЕ.

          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = _Read_OpCode ;
        p->scmd._.code = p->code++ ;
        p->smsg.id = SetMasterToSlave_ID( ptr->port, *(ptr->sl_addr) )  ;

      for ( p->i = 0, ah = 1, p->bh = 1 ; ptr->r_dscr1[p->i] != (char)0xff ; p->i++ )
      {
            //  Влазит ли количество заданных идентификаторов в сообщение.
        if ( ah > 7 ) return _Err_DscrNumber ;

           //  Разрешен ли доступ на запись для данной переменной.
        if (svar[ptr->port].tab[ptr->r_dscr1[p->i]].access != _READ_WRITE_access )
                                                            return  _Err_Access ;

              //  Влезут ли данные в ответное сообщение на этот запрос.
        p->bh += svar[ptr->port].tab[ptr->r_dscr1[p->i]].lon;
        if ( p->bh > 8 ) return _Err_DscrDataNumber;
        p->smsg.data[ah++] = ptr->r_dscr2[p->i];
      }

      p->smsg.data[0]  = p->scmd.all;    // записываем окончательный код команды.
      p->smsg.cfg.dlen = ah ;
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;

      p->time = timer1 ; // для "time_out"
  case 4 :
      md->read_label = 0 ;
	    // посылаем сообщение.
      if ( xSend_msg( ptr->port, ptr->obj_w, &p->smsg ) != 0 )
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        if ( (u)(w)(timer1-p->time)/_MkSec(1000) <= can_setting(ptr->port).connect )
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          md->read_label = 4 ;
          //09.04.06 00:39can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          md->err.send++ ;
          return _Err_Send ;
      } }
    // ********

	  // ожидаем ответа на запрос.
      //for ( p->tst = 0, p->time = 0 ;; )
      p->tst = 0, p->time = timer1 ;
      {   // при первом входе не проверяем наличие ответа - нет смысла.
        goto tout ;
case 1 : md->read_label = 0 ; // если надо будет - его снова взведут ниже.
        if ( xRead_msg( ptr->port, ptr->obj_r, &rmsg ) == 1)
        {
                // от своего ли абонента получили сообщение?
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
                if ( rmsg.cfg.dlen != p->bh )
                {
                  ret_code = _Err_AnswLong;
                  goto ret;
                }
                  // расшифровываем ответное сообщение.
                for ( p->i = 0, p->bh = 1 ; ptr->r_dscr1[p->i] != (char)0xff ; p->i++ )//, ah++ )
                {
                    switch ( svar[ptr->port].tab[ptr->r_dscr1[p->i]].type & ~_Indirect_type )
                    {
                      case _CHAR_type :
                          *(b*)svar[ptr->port].tab[ptr->r_dscr1[p->i]].addr = rmsg.data[p->bh++];
                          break;

                      case _SHORT_type:
                      case _INT_type:
                          buff.ax = (w)rmsg.data[p->bh++] +
                                   ((w)rmsg.data[p->bh++] << 8) ;
                          *(w*)svar[ptr->port].tab[ptr->r_dscr1[p->i]].addr = buff.ax ;
                          break;

                      case _LONG_type :
                          buff.lax = (lw)(w)rmsg.data[p->bh++] +
                                    ((lw)(w)rmsg.data[p->bh++] << 8) +
                                    ((lw)(w)rmsg.data[p->bh++] <<16) +
                                    ((lw)(w)rmsg.data[p->bh++] <<24) ;
                          *(lw*)svar[ptr->port].tab[ptr->r_dscr1[p->i]].addr = buff.lax ;
                          break;

                  #ifdef   _CAN_FLOAT_VAR
                      case _FLOAT_type :
                          buff.b[0] = rmsg.data[p->bh++] ;
                          buff.b[1] = rmsg.data[p->bh++] ;
                          buff.b[2] = rmsg.data[p->bh++] ;
                          buff.b[3] = rmsg.data[p->bh++] ;
                          *(float*)svar[ptr->port].tab[ptr->r_dscr1[p->i]].addr = buff.flt ;
                          break;
                  #endif

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
            md->err.receive++ ;
            return ret_code ; //311
          }
          else
          {
            //Sleep ( 1.0 ) ; // задержка на 1мсек.
            if ( (u)(w)(timer1-p->time)/_MkSec(1000) > can_setting(ptr->port).connect ) p->tst = 1 ;
      tout: md->read_label = 1 ;
            return _NoErr_TimeOut;
          }
    }  }
  return 0 ;
}
//#########################
//---------------------------------------------------------------------------
     // Функция записи может быть как с подтверждающим ответом, так и без:
     //   master_xwrite( _Write_OpCode, ... )      - с ответом.
     //   master_xwrite( _QuickWrite_OpCode, ... ) - без ответа.
word micro_master_xwrite( char OpCode, const struct MICRO_MASTER *ptr, byte num_call)
{
    struct  Data_mast register  *p ;
    struct CAN_master_data  register *md ;

    register byte ah ;
    word  ret_code ;
    struct canMSG_hw rmsg;
    union MSG_CMD  rcmd ;
   //   Структура для преобразования отдельных байт в слово,
   // в длинное слово и наоборот.
    union lax_ax_b  buff ;

        //   для сокращения объема операций заранее вычисляем
        // адрес блока данных.
    p = &read_data[ptr->abonent_num] ;  //p = &write_data[ptr->port] ;
    md = &can_md[ptr->abonent_num] ;

//////  Очищать буфер приема нет смысла т.к. он тут же может снова засоритьс
////// если на шине идет обмен.

// Если п/п в тайм-ауте, то пропускаем только свой вызов.
    if ( md->write_label != 0 && md->n_call != num_call )  return _NoErr_TimeOut;
      md->n_call = num_call ; // для тайм-аута.

    switch ( md->write_label )
    {
      case 0 :
            // ФОРМИРУЕМ СООБЩЕНИЕ.
          // Компонуем код команды с порядковым номером посылки.
        p->scmd.all    = 0 ;
        p->scmd._.cmd  = OpCode ; //_Write_OpCode ;
        p->scmd._.code = p->code++ ;

                //  Задаем адрес назначения.
        p->smsg.id = SetMasterToSlave_ID( ptr->port, *(ptr->sl_addr) )  ;

      for ( p->i = 0, ah = 1 ; ptr->w_dscr1[p->i] != (char)0xff ; p->i++ )
      {
           //  Влазит ли заданный идентификатор и его данные в сообщение.
       if ( (svar[ptr->port].tab[ptr->w_dscr1[p->i]].type & ~_Indirect_type) != _CHAR_array_type )
       {
         if ( ah+1+svar[ptr->port].tab[ptr->w_dscr1[p->i]].lon > 8 ) return _Err_DscrDataNumber ;
         p->smsg.data[ah++] = ptr->w_dscr2[p->i] ;
       }


       switch ( svar[ptr->port].tab[ptr->w_dscr1[p->i]].type & ~_Indirect_type )
       {
        case _CHAR_type :
            p->smsg.data[ah++] = *(b*)(svar[ptr->port].tab[ptr->w_dscr1[p->i]].addr) ;
            break;

        case _SHORT_type:
        case _INT_type:
            buff.ax = *(w*)(svar[ptr->port].tab[ptr->w_dscr1[p->i]].addr) ;
            p->smsg.data[ah++] = buff.ax      ;
            p->smsg.data[ah++] = buff.ax >> 8 ;
            break;

        case _LONG_type :
            buff.lax = *(lw*)(svar[ptr->port].tab[ptr->w_dscr1[p->i]].addr) ;
            p->smsg.data[ah++] = buff.lax      ;
            p->smsg.data[ah++] = buff.lax >> 8 ;
            p->smsg.data[ah++] = buff.lax >>16 ;
            p->smsg.data[ah++] = buff.lax >>24 ;
            break;

      #ifdef   _CAN_FLOAT_VAR
        case _FLOAT_type :
            buff.flt = *(float*)(svar[ptr->port].tab[ptr->w_dscr1[p->i]].addr) ;
            p->smsg.data[ah++] = buff.b[0];
            p->smsg.data[ah++] = buff.b[1];
            p->smsg.data[ah++] = buff.b[2];
            p->smsg.data[ah++] = buff.b[3];
            break;
      #endif
          //==============
        default:  return _Err_Type ; //расшифровка ОШИБКИ.
       }
      }

      p->smsg.data[0] = p->scmd.all  ;

      p->smsg.cfg.dlen    = ah ;
      //11.04.03 13:29p->smsg.cfg.dir     = 1 ;
    // ********
      p->time = timer1 ; // для "time_out"
  case 4 :
      md->write_label = 0 ;
	    // посылаем сообщение.
      if ( xSend_msg( ptr->port, ptr->obj_w, &p->smsg ) != 0 )//   return _Err_Send ;
      {    // ожидание освобождения буфера для записи без подтверждающего ответа.
        if ( (u)(w)(timer1-p->time)/_MkSec(1000) <= can_setting(ptr->port).connect )
        {
          //Sleep ( 1.0 ) ; // задержка на 1мсек.
          md->write_label = 4 ;
          //09.04.06 00:39can_dd[ptr->port].Error_send-- ; // компенсируем счетчик ошибки записи если
          return _NoErr_TimeOut;   // будем производить повторную попытку записи
        }
        else
        {
          md->err.send++ ;
          return _Err_Send ;
        }
      }    // при записи без ответа не ожидаем ответа.
      else if ( OpCode == _QuickWrite_OpCode )  return 0 ;
    // ********

	  // ожидаем ответа на запрос.
      //for ( p->tst = 0, p->time = 0 ;; )
      p->tst = 0, p->time = timer1 ;
      {   // при первом входе не проверяем наличие ответа - нет смысла.
        goto tout ;
  case 1 : md->write_label = 0 ; // если надо будет - его снова взведут ниже.
        if ( xRead_msg( ptr->port, ptr->obj_r, &rmsg ) == 1 )
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
                    // код своей ли команды получили,
                if ( rcmd._.cmd == _Write_OpCode )  return 0 ;
        } } }
               //   отсчет time_out. - с еще одним заходом проверки
              //  приема по истечении времени.
        if ( p->tst == 1 )
        {
          ret_code = _Err_Receive ;
      ret:
          md->err.receive++ ;
          return ret_code ; //311
        }
        else
        {
            //Sleep ( 1.0 ) ; // задержка на 1мсек.
          if ( (u)(w)(timer1-p->time)/_MkSec(1000) > can_setting(ptr->port).connect ) p->tst = 1 ;
    tout: md->write_label = 1 ;
          return _NoErr_TimeOut;
        }
    } }
  return 0 ;
}
//#########################
