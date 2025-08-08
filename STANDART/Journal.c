
void Journal ( byte num )
{
  register byte ax, bx, cx, dx;
  register word PlusGist, MinusGist;
  _x_far const struct VAR_JRN register *ptr;
  static byte index;

  // инициализация
  if ( num == 0 )
  {
    for ( ax = 0; ax < _MaxNumVarJrn; ax++ ) JrnData.flag[ ax ] = 0;
    JrnData.time = Timer1_fSec;
    JrnData.label = 0; // метка для программы TestJrnTab()
    InJrnPtr = 1; // указатель на первую запись
    OutJrnPtr = 0;
    BitJrn.all = 0;
    JrnData.Stop = 0;
    JrnData.activ = 0;
    i2c_jrn_label = 0;
    index = 0;

    // обнуляем буфер журнала
    for ( ax = 0; ax < _MaxJrnCount; ax++ )
    {
       //MsgJrn[ ax ].number = 0;
       for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ ax ].name[ bx ] = 0;
       MsgJrn[ ax ].uslovie = 0;
       MsgJrn[ ax ].value = 0;
       MsgJrn[ ax ].time_msg._.avar_first.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.avar.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.predupr.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.service.lw_reg = 0;
#ifndef _ONE_REG
       MsgJrn[ ax ].time_msg._.avar_first2.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.avar2.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.predupr2.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.service2.lw_reg = 0;
#endif
       for ( bx = 0; bx < 8; bx++ ) MsgJrn[ ax ].time_msg.time.b[ bx ] = 0;
    }

      // Находим соответствие именам из рабочей таблицы имен
      // в const-таблице и списываем ее свежий адрес (номер),
      // поскольку при перезашивке адрес (номер) переменной мог измениться
      // по-сравнению с устаревшим адресом (номером) данной переменной, хранящимся в i2c.
    while ( TestJrnTab ( 0 ) != 0 );

    //Фиксируем время запуска программы
    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = _TimeStartProg[ bx ];
    MsgJrn[ InJrnPtr ].uslovie = -2; // устанавливаем признак, что запись в журнале произведена по запуску программы
    MsgJrn[ InJrnPtr ].value = 0;
    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode; // запись контрольного кода
    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;

    // Для дискретных переменных устанавливаем флаг в зависимости от состояния дискр.входа,
    // чтобы при входе в рабочий цикл буфер не забивался начальными состояниями.
    for ( ax = 0; ax < TabJrn.n_kanal; ax++ )  // перебираем все заданные переменные
    {
      // для уменьшения последующего времени вычислений однократно вычисляем адрес переменной в таблице
      ptr = &FullJrnTab[ JrnData.tab[ ax ] ];

      if ( ptr->code._.ad == 1 ) // дискретная переменная
      {
        switch ( ptr->code._.type )
        {
          default:
                    break;
          case 1:   // однобайтная
                    // Если заданный бит в байте равен 0
                    if ( ( *(b*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ ax ].etalon ) ) == 0 ) JrnData.flag[ ax ] = 1;
                    break;

          case 2:   // двухбайтная
                    // Если заданный бит в слове равен 0
                    if ( ( *(w*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ ax ].etalon ) ) == 0 ) JrnData.flag[ ax ] = 1;
                    break;
        }
      }
    }

    return;
  }

  // Измерение времени работы журнала.
  // При 16-ти переменных FR - 0.2...0.5ms
  //                      590 - 0.6...1.4ms
  Tckl_jrn = timer1 ;

  // Задержка на запуск журнала, пока всё не устаканится, так как без задержки пишутся все события при инициализации,
  // начиная с отсутствия синхронизации.
  if ( BitJrn._.first == 0 )
  {
    if ( (u)( (w)( Timer1_fSec - JrnData.time ) ) <= _fSec( 3.0 ) ) return;
    JrnData.time = Timer1_fSec;
    BitJrn._.first = 1;
  }

  // пока журнал активен - сохраняем буфер журнала в i2c
  if ( JrnData.activ == 1 ) Save_jrn ();

  // есть команда на остановку журнала
  if ( bi_JrnStop == 1 )
  {
    if ( JrnData.activ == 1 )
    {
      // Проверка - есть ли ещё что-то в буфере для записи в i2c?
      // Если из буфера всё выбрано - останавливаем запись в i2c.
      if ( ( ( OutJrnPtr + 1 ) & _MaxJrnCount ) == InJrnPtr  ) JrnData.activ = 0;
    }
    Tjrn = 0;
    return; // есть команда на остановку журнала - возврат, чтобы в буфере не фиксировались новые записи.
  }
  else JrnData.activ = 1;

  // есть ли в буфере место под новые данные
  if ( ( ( InJrnPtr + 1 ) & _MaxJrnCount ) == OutJrnPtr ) return; // буфер заполнен, запись в i2c не успевает
                                                                  // за новыми данными

  // Регистры сообщений проверяем каждый цикл
  if ( BitJrn._.tst_new_msg == 1 ) // проверка признака изменения количества сообщений
  {
    BitJrn._.tst_new_msg = 0; // сброс признака
    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = _JrnMsg[ bx ];  // запоминаем имя переменной из общей таблицы
    MsgJrn[ InJrnPtr ].uslovie = -1; // устанавливаем признак, что запись в журнале произведена по изменению количества сообщений
    MsgJrn[ InJrnPtr ].value = 0;
    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode; // запись контрольного кода
    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;
  }

  // Рабочий цикл журнала отрабатывается раз в "TabJrn.dt_scan" сек.
  if ( (u)( (w)( Timer1_fSec - JrnData.time ) ) < TabJrn.dt_scan ) return; // время еще не вышло
  JrnData.time = Timer1_fSec; // вновь засекаем время


  //---------------- Рабочий цикл ------------------------------------------

  // за 1 проход просматриваем столько переменных, сколько может поместиться в буфере
  dx = _MaxJrnCount;
  if( (sb)dx > (sb)TabJrn.n_kanal ) dx = TabJrn.n_kanal;

  for ( ax = dx; ax != 0; ax-- )  // перебираем все заданные переменные
  {
    // есть ли в буфере место под новые данные
    if ( ( ( InJrnPtr + 1 ) & _MaxJrnCount ) == OutJrnPtr ) return; // буфер заполнен, запись в i2c не успевает
                                                                    // за новыми данными

    if( TabJrn.TabVar[ index ].name[ 0 ] == '?' ) goto next; // такой переменной в общей таблице нет

    // для уменьшения последующего времени вычислений однократно вычисляем адрес переменной в таблице
    ptr = &FullJrnTab[ JrnData.tab[ index ] ];

    if ( ptr->code._.ad == 1 ) // дискретная переменная
    {
      // Для дискретных переменных ловим все изменения заданных битов и сохраняем в буфер
      switch ( ptr->code._.type )
      {
        default:
                  break;
        case 1:   // однобайтная
                  // Если заданный бит в байте стал равным 0
                  if ( ( *(b*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) == 0 && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1; // установка флага
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx ] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _RVN;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // запоминаем номер бита
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  // Если заданный бит в байте стал равным 1
                  else if ( ( *(b*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) != 0 && JrnData.flag[ index ] != 0 )
                  {
                    JrnData.flag[ index ] = 0; // сброс флага
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _NRV;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // запоминаем номер бита
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  break;

        case 2:   // двухбайтная
                  // Если заданный бит в слове стал равным 0
                  if ( ( *(w*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) == 0 && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1; // установка флага
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _RVN;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // запоминаем номер бита
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  // Если заданный бит в слове стал равным 1
                  else if ( ( *(w*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) != 0 && JrnData.flag[ index ] != 0 )
                  {
                    JrnData.flag[ index ] = 0; // сброс флага
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _NRV;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // запоминаем номер бита
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  break;
      }
    }
    else if ( ptr->code._.ad == 0 ) // аналоговая переменная
    {
      // Сразу вычисляем пороги с учетом гистерезиса
      PlusGist  = TabJrn.TabVar[ index ].etalon + ptr->nom * _Gisterezis / 100;
      MinusGist = TabJrn.TabVar[ index ].etalon - ptr->nom * _Gisterezis / 100;

      switch ( TabJrn.TabVar[ index ].uslovie )
      {
        default:
                  break;
        case _RVN: // ==
                  if ( ptr->code._.off_sign == 0 ) // переменная двуполярная
                  {
                    if ( *(sw*)ptr->addr == (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _RVN;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    // Нужен ли здесь гистерезис? - НУЖЕН ОБЯЗАТЕЛЬНО, иначе будет писаться весь дребезг возле эталона
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist || *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // переменная однополярная
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //если переменная однополярная - то отрицательный порог не имеет смысла
                    if ( *(w*)ptr->addr == (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _RVN;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(w*)ptr->addr >= (w)PlusGist || *(w*)ptr->addr <= (w)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _NRV: // !=
                  if ( ptr->code._.off_sign == 0 ) // переменная двуполярная
                  {
                    if ( *(sw*)ptr->addr != (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _NRV;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist || *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // переменная однополярная
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //если переменная однополярная - то отрицательный порог не имеет смысла
                    if ( *(w*)ptr->addr != (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _NRV;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist || *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _BRV: // >=
                  if ( ptr->code._.off_sign == 0 ) // переменная двуполярная
                  {
                    if ( *(sw*)ptr->addr >= (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BRV;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // переменная однополярная
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //если переменная однополярная - то отрицательный порог не имеет смысла
                    if ( *(w*)ptr->addr >= (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BRV;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(w*)ptr->addr <= (w)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _BOL: // >
                  if ( ptr->code._.off_sign == 0 ) // переменная двуполярная
                  {
                    if ( *(sw*)ptr->addr > (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BOL;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // переменная однополярная
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //если переменная однополярная - то отрицательный порог не имеет смысла
                    if ( *(w*)ptr->addr > (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BOL;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(w*)ptr->addr <= (w)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _MRV: // <=
                  if ( ptr->code._.off_sign == 0 ) // переменная двуполярная
                  {
                    if ( *(sw*)ptr->addr <= (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MRV;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // переменная однополярная
                  {
                    if ( *(w*)ptr->addr <= (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MRV;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(w*)ptr->addr >= (w)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _MEN: // <
                  if ( ptr->code._.off_sign == 0 ) // переменная двуполярная
                  {
                    if ( *(sw*)ptr->addr < (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MEN;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // переменная однополярная
                  {
                    if ( *(w*)ptr->addr < (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // запоминаем имя переменной из общей таблицы
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MEN;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                      // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                    }
                    else if ( *(w*)ptr->addr >= (w)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;
      }
    }
    else if ( ptr->code._.ad == 2 ) // аналоговая переменная, сформированная битовыми полями
    {
      if ( ptr->code._.type == 1 ) bx =  7; // байт
      else                         bx = 15; // слово

      for ( cx = 0; cx <= bx; cx++) //поиск первой значащей позиции в маске, результат в cx
         if ( ( ptr->nom >> cx ) & 1 != 0 ) break;

      MinusGist = TabJrn.TabVar[ index ].etalon << cx; // эталон сдвигаем к маске

      // байт
      if ( ptr->code._.type == 1 ) PlusGist = (w)( *(b*)ptr->addr & ptr->nom ) & 0x00FF;
      // слово
      else PlusGist = *(w*)ptr->addr & ptr->nom;

      switch ( TabJrn.TabVar[ index ].uslovie )
      {
        default:
                  break;

        case _RVN: // ==
                  if ( PlusGist == MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _RVN;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  else if ( PlusGist != MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _NRV: // !=
                  if ( PlusGist != MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _NRV;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  else if ( PlusGist == MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _BRV: // >=
                  if ( PlusGist >= MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _BRV;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  else if ( PlusGist < MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _BOL: // >
                  if ( PlusGist > MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _BOL;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  else if ( PlusGist <= MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _MRV: // <=
                  if ( PlusGist <= MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _MRV;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  else if ( PlusGist > MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _MEN: // <
                  if ( PlusGist < MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // запоминаем имя переменной из общей таблицы
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _MEN;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // засекаем время события
                    // Т.к. год и 'Control Byte' не используется - пишем сюда контрольный код
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // пишем все регистры сообщений
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // увеличиваем указатель
                  }
                  else if ( PlusGist >= MinusGist ) JrnData.flag[ index ] = 0;
                  break;
      }
    }
next:
    if( ++index >= TabJrn.n_kanal ) index = 0; // просмотрели все переменные - начинаем с начала
  }
  //------------------------------------------------------------------------
  Tjrn = timer1 - Tckl_jrn; // в Tjrn время работы журнала

  return;
}

// m_index - пункт "Меню1"
// m_time  - порядковый номер переменной
// m_ext   - пункт "Меню2"
// m_addr  - номер новой переменной

// Настройка журнала
void SetJrnTab ( void )
{

  register word ax, bx, cx, ex;
  byte  sig_old;
  register lword lax;


              //  Контроль пароля: Полный запрет входа.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


  if ( M_FirstCall == 1 )  // Идентификация первого входа для задания
  {                        // начального условия ...
    M_FirstCall = 0;
    Label = 0;
    m_index = 0;
    m_ext = 0;
    m_addr = 0;
    JrnData.Stop = 1; // остановка журнала
  }

  //--------------------

  switch ( Label )
  {
    default:
    case 0:
          output_s ( _SetJrn_prompt ); // "\n\rНастр. журнала: \n" на верхней строке
          Label = 1;

    case 1:
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu1[ m_index ].txt ); //Кратность, переменных, список
            Label = 2;
          }
          break ;

          //Работаем с "Меню1": кратность, число переменных, список переменных
    case 2:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // Выход из этого режима
            {
              JrnData.Stop = 0; //запуск журнала
              Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1;
              return;   // добавить еще какую-то иниц.
            }
            else if ( m_ch == Down ) //увеличить пункт "Меню1"
            {
              m_index++;
              if ( m_index >= Menu1_size ) m_index = 0;
              Label = 1;
            }
            else if ( m_ch == Up )  //уменьшить пункт "Меню1"
            {
              m_index--;
              if ( (sw)m_index < 0 ) m_index = Menu1_size - 1;
              Label = 1;
            }
            else if ( m_ch == Enter ) Label = 3;
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 1;
          }
          break;

    case 3:
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" ); //выводим на верхнюю строку пункт "Меню1"
            output_s ( Menu1[ m_index ].txt );
            output_c ( '\n' );
            Label = Menu1[ m_index ].label;
          }
          break;

    //-------------------------------------------------------------------------------
    case 10: //"Кратность"
          m_time = TabJrn.dt_scan; //сохраняем прежнюю кратность
          Label = 11;
    case 11: //Вывод кратности журнала
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );

            ax = TabJrn.dt_scan;
            m_ch  = ax / _fSec(10);
            ax = ax % _fSec(10) ; // остаток от деления кратности на делитель

            if ( m_ch != 0 )  m_ch += 0x30;
            else              m_ch = ' ';

            output_c ( m_ch ); //десятки

            m_ch = ax / _fSec(1);
            ax %= _fSec(1) ;

            output_c ( m_ch+0x30 ); //единицы
            output_c ( '.' );

            ax *= 10;
            m_ch = ax / _fSec(1);
            ax %= _fSec(1);
            output_c ( m_ch + 0x30 ); //десятые

            ax *= 10;
            m_ch = ax / _fSec(1);
            ax %= _fSec(1);
            output_c ( m_ch + 0x30 ); //сотые

            ax *= 10;
            m_ch = ax / _fSec(1);
            output_c ( m_ch + 0x30 ); //тысячные
            output_s ( " сек " );
            Label = 12;
          }
          break ;

    case 12: //Режим изменения кратности журнала
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // Выход из этого режима
            {
              TabJrn.dt_scan = m_time; // Восстанавливаем прежнюю кратность
              Label = 0;
            }
            else if ( m_ch == Up )   // Увеличить кратность
            {
              TabJrn.dt_scan += _fSec(0.01) ; // увеличиваем кратность
              if ( TabJrn.dt_scan >= _fSec(5.0) ) TabJrn.dt_scan = _fSec(5.0);
              Label = 11; // возврат на вывод кратности
            }
            else if ( m_ch == Down ) // Уменьшить кратность
            {
              TabJrn.dt_scan -= _fSec(0.01); // уменьшаем кратность
              if ( (sw)TabJrn.dt_scan <= 0 ) TabJrn.dt_scan = _fSec(0.00);
              Label = 11; // возврат на вывод кратности
            }
            else if ( m_ch == Enter ) Label = 0; // Кратность принята
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 11;
          }
          break;

    //-------------------------------------------------------------------------------
    case 20:  //"Переменныx"
          m_time = (w)TabJrn.n_kanal; //сохраняем текущее кол-во переменных
          Label = 21;
    case 21:  //Вывод количества переменных
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( "N = " );

            ax = (w)TabJrn.n_kanal;
            output_c ( ax / 10 + 0x30 ); //десятки
            output_c ( ax % 10 + 0x30 ); //единицы
            Label = 22;
          }
          break;

    case 22: //Режим изменения количества переменных
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )
            {
              TabJrn.n_kanal = (b)m_time; //восстанавливаем прежнее кол-во переменных
              Label = 0;
            }
            else if ( m_ch == Up ) //увеличить кол-во переменных
            {
              TabJrn.n_kanal++;
              if ( TabJrn.n_kanal > _MaxNumVarJrn ) TabJrn.n_kanal = _MaxNumVarJrn; //25.06.2012 10:10 1;
              Label = 21;
            }
            else if ( m_ch == Down ) //уменьшить кол-во переменных
            {
              TabJrn.n_kanal--;
              if ( (sb)TabJrn.n_kanal < 0/*1*/ ) TabJrn.n_kanal = 0; //25.06.2012 10:10 _MaxNumVarJrn; для возможности задать
              Label = 21;                         // 0 переменных и работать только по изменениям количества сообщений
            }
            else if ( m_ch == Enter ) Label = 0; //принять число переменных
            else  Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 21;
          }
          break;

    //-------------------------------------------------------------------------------
    case 29:
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" ); //выводим на верхнюю строку пункт "Меню1"
            output_s ( Menu1[ m_index ].txt );
            output_c ( '\n' );
            Label = 31;
          }
          break;
    case 30:  //"Список    "
          if( TabJrn.n_kanal == 0 )
          {
            m_index = 1;
            output_s ( "\r" ); //выводим на верхнюю строку пункт "Меню1"
            output_s ( Menu1[ m_index ].txt );
            output_c ( '\n' );
            Label = Menu1[ m_index ].label;
            break;
          }
          m_time = 0;
          Label = 31;
    case 31:  //Просмотр уже заданных переменных
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_c ( 'n' );
            //распечатка номера переменной
            ax = m_time + 1;
            output_c ( ax / 10 + 0x30 ); //единицы
            output_c ( ax % 10 + 0x30 ); //десятки
            output_c ( '-' );

            //распечатка наименования переменной
            output_s ( TabJrn.TabVar[ m_time ].name );
            Label = 32;
          }
          break;

    case 32:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = 0;
            else if ( m_ch == Down ) //увеличить номер переменной
            {
              m_time++;
              if ( m_time >= TabJrn.n_kanal ) m_time = 0;
              Label = 31;
            }
            else if ( m_ch == Up ) //уменьшить номер переменной
            {
              m_time--;
              if ( (sw)m_time < 0 ) m_time = TabJrn.n_kanal - 1;
              Label = 31;
            }
            else if ( m_ch == Enter ) //перейти в режим выбора новой переменной,
            {                         //условия и задания эталона
              Label = 33;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 31;
          }
          break;

    case 33:  //выводим на верхнюю строку имя текущей переменной
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            output_c ( 'n' );
            //распечатка номера переменной
            ax = m_time + 1;
            output_c ( ax / 10 + 0x30 ); //десятки
            output_c ( ax % 10 + 0x30 ); //единицы
            output_c ( '-' );
            //распечатка наименования переменной
            output_s ( TabJrn.TabVar[ m_time ].name );
            output_c ( '\n' );
            Label = 34;
          }
          break;

    case 34: //Работаем с "Меню2" - новая переменная, условие, эталон/номер бита
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu2[ m_ext ].txt );
            Label = 35;
          }
          break;

    case 35:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = 29;
            else if ( m_ch == Down ) //увеличить пункт меню2
            {
              m_ext++;
              //если выбрана дискретная переменная, то меню "Условие" пропускаем
              if ( FullJrnTab[ JrnData.tab[ m_time ] ].code._.ad == 1 && Menu2[ m_ext ].label == 50 ) m_ext++;
              if ( m_ext >= Menu2_size ) m_ext = 0;
              Label = 34;
            }
            else if ( m_ch == Up ) //уменьшить пункт меню2
            {
              m_ext--;
              if ( (sw)m_ext < 0 ) m_ext = Menu2_size - 1;
              //если выбрана дискретная переменная, то меню "Условие" пропускаем
              if ( FullJrnTab[ JrnData.tab[ m_time ] ].code._.ad == 1 && Menu2[ m_ext ].label == 50 )
              {
                m_ext--;
                if ( (sw)m_ext < 0 ) m_ext = Menu2_size - 1;
              }
              Label = 34;
            }
            else if ( m_ch == Enter ) Label = 36;
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 34;
          }
          break;

    case 36: //вывод на верхнюю строку выбранного пункта "Меню2"
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            output_s ( Menu2[ m_ext ].txt );
            output_c ( '\n' );
            Label = Menu2[ m_ext ].label;
            m_addr = 0;
          }
          break;

    //-------------------------------------------------------------------------------
    case 40:  // "Новая перемен."
          m_addr = 0;
          Label = 41;
    case 41:  //  Выбор новой переменной в список заданных переменных.
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_c ( '#' );
            //распечатка номера переменной
            ax = m_addr + 1;
            output_c ( ax / 10  + 0x30 ); //десятки
            output_c ( ax % 10  + 0x30 ); //единицы
            output_c ( '-' );
            //распечатка наименования переменной
            //output_s ( FullJrnTab[ m_addr ].name );
            //вывод посимвольно, т.к. output_s не переносит far.
            for ( ax = 0; ax < _VarNameSize; ax++ )
                output_c ( FullJrnTab[ m_addr ].name[ ax ] );
            Label = 42;
          }
          break;

    case 42:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = 33;
            else if ( m_ch == Down ) //увеличить номер новой переменной
            {
              m_addr++;
              if ( m_addr >= FullJrnTab_size ) m_addr = 0;
              Label = 41;
            }
            else if ( m_ch == Up ) //уменшить номер новой переменной
            {
              m_addr--;
              if ( (sw)m_addr < 0 ) m_addr = FullJrnTab_size - 1;
              Label = 41;
            }
            else if ( m_ch == Enter ) //принять новую переменную
            {
              if ( JrnData.tab[ m_time ] != m_addr ) //если действительно новая переменная
              {
                //Запоминаем номер новый переменной
                JrnData.tab[ m_time ] = m_addr;
                //Если номер новый переменной не совпадает со старым номером,
                //то обнуляем флаг и для аналоговой переменной эталон, т.к. могут оказаться разные номиналы.
                //Для дискретной переменной эталон (номер бита) сразу переписывается из const-таблицы.
                //После изменения аналоговой переменной надо задать новый эталон.
                JrnData.flag[ m_time ] = 0;
                if ( FullJrnTab[ JrnData.tab[ m_time ] ].code._.ad == 1 )
                     TabJrn.TabVar[ m_time ].etalon = FullJrnTab[ JrnData.tab[ m_time ] ].nom;
                else TabJrn.TabVar[ m_time ].etalon = 0;
                // Перезаписываем имя переменной в рабочую таблицу
                for ( ax = 0; ax < _VarNameSize; ax++ ) TabJrn.TabVar[ m_time ].name[ ax ] = FullJrnTab[ m_addr ].name[ ax ];
              }
              Label = 33;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 41;
          }
          break;

    //-------------------------------------------------------------------------------
    case 50: //"Условие       "
          //Запоминаем текущее условие
          m_buff[ 2 ] = TabJrn.TabVar[ m_time ].uslovie;
          //вывод начинаем с текущего условия
          m_addr = TabJrn.TabVar[ m_time ].uslovie;
          Label = 51;
    case 51: //Выбор условия - работаем с "Меню3"
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu3[ m_addr ].txt );
            Label = 52;
          }
          break;

    case 52:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )
            {
              TabJrn.TabVar[ m_time ].uslovie = m_buff[ 2 ]; //восстанавливаем условие
              Label = 33;
            }
            else if ( m_ch == Down )
            {
              m_addr++;
              if ( m_addr >= Menu3_size ) m_addr = 0;
              Label = 51;
            }
            else if ( m_ch == Up )
            {
              m_addr--;
              if ( (sw)m_addr < 0 ) m_addr = Menu3_size - 1;
              Label = 51;
            }
            else if ( m_ch == Enter )
            {
              //Запоминаем новое условие и сбрасываем флаг
              TabJrn.TabVar[ m_time ].uslovie = Menu3[ m_addr ].label;
              JrnData.flag[ m_time ] = 0;
              Label = 33;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 51;
          }
          break;

    //-------------------------------------------------------------------------------
    case 60:  //"Эталон/Бит    "
          *(w*)&m_buff[ 0 ] = TabJrn.TabVar[ m_time ].etalon; //запоминаем значение эталона
          //для уменьшения последующего времени вычислений однократно вычисляем адрес переменной в таблице
          dptr = &FullJrnTab[ JrnData.tab[ m_time ] ];
          Label = 61;
    case 61: //Вывод эталона
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );

            ax = TabJrn.TabVar[ m_time ].etalon;

            // Распечатка в 10-тичном виде

            // аналоговая переменная, сформированная битовыми полями или дисретная переменная
            if ( dptr->code._.ad == 2 || dptr->code._.ad == 1 ) bx = 1;
            else bx = dptr->nom;
            cx = *(w*)dptr->abs_nom;
            if ( dptr->code._.off_sign == 0 )
            {    //Если распечатка со знаком - выделяем знак и модуль
              if ( (sw)ax >= 0 )   sig_old = '+';
              else   ax = ~ax + 1, sig_old = '-';
            }

            //приводим содержимое ячейки к его номиналам
            lax = (lw)ax * (lw)cx;
            m_addr = lax % bx;
            lax /= bx;
            if ( lax > 0xffffu) lax = 0xffff;

            //распечатка целой части - максимум 5 символов
            ex = 5 - dptr->code._.celoe; //сколько первых символов пропустить
            if ( ex == 5 ) ex = 2; //для совместимости - если заданы были нули то принимаем формат "3.2".
            else if ( (sw)ex < 0 ) ex = 0;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;
              //пока идут первые нули - не выводим их:
              if ( bx == 0 && cx == 0 )
              {     //а пропускаем лишние нулевые символы,
                if ( ex != 0 ) ex--;
                //или заменяем пробелами
                else output_c (' ');
              }
              else
              {
                if ( cx == 0 )
                {
                  if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
                  cx = 1;
                }
                //первые нули закончились
                output_c ( (b)bx + 0x30 );
              }
            }   //распечатываем последнюю цифру
            if ( cx == 0 )
            {
              if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
            }
            output_c ( (b)(w)lax + 0x30 );
            Label = 62;
          }
          break;

    case 62:    //распечатка дробной части
          if ( TestCompleted_Output() )
          {
            if ( dptr->code._.celoe == 0 ) ex = 2;// по умолчанию.
            else ex = dptr->code._.drob;
            if ( ex != 0 )
            {
              output_c ( '.' );
              bx = dptr->nom;
              lax = m_addr; //восстанавливаем остаток
              for ( ; ex != 0 ; ex-- )
              {
                lax *= 10;
                ax = lax / bx;
                lax %= bx;
                output_c ( (b)ax + 0x30 );
              }
            }
            output_s ( dptr->ch );
            Label = 63; // для режима изменения эталона
          }
          break;

    case 63: //Изменение эталона
          if ( TestData_for_Input() )
          {
            ax = TabJrn.TabVar[ m_time ].etalon; //запоминаем эталон
            cx = ax; // сохраняем предыдущее значение
            mInput_c ( m_ch );
            if ( m_ch == Return )
            {
              TabJrn.TabVar[ m_time ].etalon = *(w*)&m_buff[ 0 ]; //восстанавливаем значение эталона
              Label = 33;
              break;
            }
            else if ( m_ch == Up ) //увеличить эталон
            {
              ax += dptr->dX;
              bx  = dptr->max;
              //  Если распечатка без знака то число рассматриваем
              //  как беззнаковое в диапазоне 0...65535.
              if ( dptr->code._.off_sign == 0 ) //со знаком
              {
                //  Защита на случай переваливания через max, если
                // max задан 0xFFFF (для беззнаковых) или 0x7FFF
                // (для знаковых), т.к. в этих случаях ограничение
                // по обычному алгоритму не может работать.
                if ( (sw)ax < (sw)cx ) ax = bx; // если после сложения число
                // стало меньше чем до, значит произошло переваливание.
                if ( (sw)ax > (sw)bx ) ax = bx;
              }
              else //без знака
              {
                if ( (w)ax < (w)cx ) ax = bx; // если после сложения число
                // стало меньше чем до, значит произошло переваливание.
                if ( (w)ax > (w)bx ) ax = bx;
              }
              Label = 61;
            }
            else if ( m_ch == Down ) //уменьшить эталон
            {
              ax -= dptr->dX;
              bx = dptr->min;
              if ( dptr->code._.off_sign == 0 ) //со знаком
              {
                //  Защита на случай переваливания через min, если
                // min задан 0x0000 (для беззнаковых) или 0x8000
                // (для знаковых), т.к. в этих случаях ограничение
                // по обычному алгоритму не может работать.
                if ( (sw)ax > (sw)cx ) ax = bx; // если после вычитания число
                // стало больше чем до, значит произошло переваливание.
                if ( (sw)ax < (sw)bx ) ax = bx;
              }
              else //без знака
              {
                if ( (w)ax > (w)cx ) ax = bx; // если после вычитания число
                // стало больше чем до, значит произошло переваливание.
                if ( (w)ax < (w)bx ) ax = bx;
              }
              Label = 61;
            }
            else if ( m_ch == Enter ) //Запоминаем новый эталон
            {
              Label = 33;
            }
            else  Klav_Buff = m_ch;
            TabJrn.TabVar[ m_time ].etalon = ax; //возвращаем эталон
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 61;
          }
          break;
  }
  Restart_Output ( );
  return;
}

  //   Находим соответствие всем именам из рабочей таблицы имен
  // в const-таблице и списываем ее свежие параметры (адрес),
  // поскольку при перезашивке адрес переменной мог измениться
  // по-сравнению с устаревшим адресом данной переменной хранящимся в i2c.

word TestJrnTab ( byte num )
{
  enum { k0, k10 };

  static byte index1; //  индекс поиска внутри рабочей таблицы.
  static byte index2; //  индекс поиска внутри const-таблицы.
  char *ptr1;
  _x_far const char *ptr2;
  byte ah, bh;

  if ( num == 0 )
  {
    switch ( JrnData.label )
    {
      default:;     // начало поиска.
      case k0 : index1 = 0, index2 = 0 ;
                JrnData.label = k10 ;
         break;
          //-----------------
      case k10:      // перебираем порциями не более 3-х переменных.
                for ( ah = 3 ; ah != 0 ; ah-- )
                {     //  Если задан прямой адрес, то пропускаем.
                  //if ( JrnData.tab[index1].name[0] == '@' ) goto next ;

                  ptr1 = &TabJrn.TabVar[ index1 ].name[ 0 ];
                  ptr2 = &FullJrnTab[ index2 ].name[ 0 ];
                       //  сравниваем имена.
                  for ( bh = 0 ; ; bh++ )
                  {
                        // имя не равно.
                    if ( ptr1[bh] != ptr2[bh] )  break ;

                        // имя закончилось?... значит имя найдено.
                    if ( ptr1[bh] == 0 || ptr1[bh] == ' ' )  // NULL Vit-07.12.07 14:13
                    {      // задаем соответствующий имени указатель на
                          //     переменную в базовой таблице.
                      JrnData.tab[index1] = index2 ;

                 next:  // начинаем поиск следующей переменной.
                      if ( ++index1 >= _MaxNumVarJrn )
                      {     // вся таблица проверена.
                        JrnData.label = k0 ; // взводим метку на начало.
                        return 0 ;
                      }
                      index2 = -1 ; // сбрасываем указатель.
                      break ;
                    }
                  }
                      // переходим к следующей переменной в константной таблице.
                  if ( ++index2 >= FullJrnTab_size ) // переменные в списке закончились.
                  {    // имя не найдено:
                    ptr1[0] = '?' ; // помечаем его '?' и пропускаем.
                    goto next ;
                  }
                }
         break;
          //-----------------
    }
  }
  else
  {
    // Если была запись старта программы или по изменению количества сообщений - то сравнивать имена переменных не нужно
    if ( (sb)MsgJrnPrint.uslovie < 0 && *(w*)&MsgJrnPrint.time_msg.time.b[ 6 ] == _CntrCode ) return 0;

    switch ( JrnData.label )
    {
      default:;     // начало поиска.
      case k0 : index1 = 0, index2 = 0 ;
                JrnData.label = k10 ;
         break;
          //-----------------
      case k10:      // перебираем порциями не более 3-х переменных.
                for ( ah = 3 ; ah != 0 ; ah-- )
                {     //  Если задан прямой адрес, то пропускаем.
                  //if ( JrnData.tab[index1].name[0] == '@' ) goto next ;

                  ptr1 = &MsgJrnPrint.name[ 0 ];
                  ptr2 = &FullJrnTab[ index2 ].name[ 0 ];
                       //  сравниваем имена.
                  for ( bh = 0 ; ; bh++ )
                  {
                        // имя не равно.
                    if ( ptr1[bh] != ptr2[bh] )  break ;

                        // имя закончилось?... значит имя найдено.
                    if ( ptr1[bh] == 0 || ptr1[bh] == ' ' )  // NULL Vit-07.12.07 14:13
                    {      // задаем соответствующий имени указатель на
                          //     переменную в базовой таблице.
                      JrnData.number = index2 ;
                      JrnData.label = k0 ; // взводим метку на начало.
                      return 0 ;
                    }
                  }
                      // переходим к следующей переменной в константной таблице.
                  if ( ++index2 >= FullJrnTab_size ) // переменные в списке закончились.
                  {    // имя не найдено:
                    MsgJrnPrint.time_msg.time.b[ 7 ] = 0;
                    JrnData.label = k0 ; // взводим метку на начало.
                    return 0;
                  }
                }
         break;
          //-----------------
    }
  }
  return 4 ;  // проверка продолжается.
}


//---------------------------------------------------

//вывод журнала на пультик
void JrnPrint ( void )
{
  register word ax, bx, cx, ex;
  register lword lax;
#ifdef _CM3_

  lword lbx;
  static lword size_i2c ;
#else

  static word size_i2c ;

#endif
  byte  sig_old;
  register byte ab, bb, cb;

  enum { k0, k1, k310, k311, k312, k313, k314, k315, k316, k317,
         k2, k3, k4, k7, k8, k9, k10, k11, k12, k20, k21 };

  if ( M_FirstCall == 1 )  //  Идентификация первого входа для задания
  {                        // начального условия ...
    M_FirstCall = 0;
    Label = k0;
    m_index = 1;
#ifndef _CM3_

    // вычисляем количество страниц в журнале
    m_addr = (w)(_i2c_jrn_end - _i2c_jrn_beg + 1 - _AdrSize);
    m_ext = _i2c_jrn_page;
    if ( m_ext > m_addr ) m_addr = 1; // влазит ли заданный размер страницы в i2c.
    else m_addr /= m_ext;
#else

    j_ext = (_i2c_jrn_end - _i2c_jrn_beg + 1 - _AdrSize);

    if ( j_ext < _i2c_jrn_page ) m_addr = 1; // влазит ли заданный размер страницы в i2c.
    else m_addr = j_ext /_i2c_jrn_page;

#endif
    output_s ( _Waiting_txt ) ;
  }

  if ( BitJrn._.tst_msg_jrn != 0 ) //Включен вывод сообщений журнала
  {
    //Однократная установка "M_FirstCall" для "print_message"
    if ( BitJrn._.tst_msg_jrn == 1 ) BitJrn._.tst_msg_jrn = 2, M_FirstCall = 1;
    print_message ( &MsgJrnPrint.time_msg ); //Вывод сообщений из журнала
    return;
  }

  //--------------------

  switch ( Label )
  {
    default:
    case k0:

          JrnData.Stop = 1; // останавливаем журнал
          if ( JrnData.activ == 0 ) Label++;  // ожидаем остановку журнала на случай, если при подаче команды остановки
          break;                              // в i2c производилась запись последней строки журнала

    case k1:
          if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
          Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята.
#ifndef _CM3_
          jrn_adr_data = (b*)&m_ext;    // Запуск считывания указателя адреса конца данных
#else
          jrn_adr_data = (b*)&j_ext;    // Запуск считывания указателя адреса конца данных
#endif
          i2c_jrn_addr = _i2c_jrn_beg;  // последней зафиксированной
          i2c_label = 0;                // в i2c записи.
          size_i2c = _AdrSize; // 2;
          Label = k310;
          break;

    case k310:
          goto load;  // Ожидание считывания.

    case k311:
#ifndef _CM3_
          // Проверка указателя: не было ли там какого-то мусора.
          if ( m_ext < _i2c_jrn_beg + _AdrSize || m_ext > _i2c_jrn_end ) m_ext = _i2c_jrn_beg + _AdrSize;

          // Отступаем от конца последней записи на
          // заданное количество страниц к началу заданной к
          // выборке записи.

          ax = _i2c_jrn_page * m_index;
          bx = m_ext - ( _i2c_jrn_beg + _AdrSize );

          // Отступить пришлось настолько, что дошли до начала
          // области журнала и перепрыгнули на ее конец.
          if ( ax > bx )  i2c_jrn_addr = ( (w)_i2c_jrn_end + 1 ) - ( ax - bx );  // (w) - добавлено, чтобы не было
                                                                                 // предупреждения при i2c на 32К
          // Отступить пришлось настолько, что не дошли до начала области журнала.
          else            i2c_jrn_addr = m_ext - ax;

          // Запуск считывания извлекаемой из i2c записи
          jrn_adr_data = (b*)&MsgJrnPrint;
          // вычисляем сколько осталось до конца i2c.
          bx = _i2c_jrn_end - i2c_jrn_addr + 1;
          size_i2c = sizeof( struct MSG_JRN );
          i2c_label = 0;
          Label = k314;
          // переход через верхнюю границу i2c.
          if ( size_i2c > bx )
          {   // разбиваем запись блока на две части.
            size_i2c = bx;

#else   //_CM3_
          if ( j_ext < _i2c_jrn_beg + _AdrSize || j_ext > _i2c_jrn_end ) j_ext = _i2c_jrn_beg + _AdrSize;

          // Отступаем от конца последней записи на
          // заданное количество страниц к началу заданной к
          // выборке записи.

          lax = _i2c_jrn_page * m_index;
          lbx = j_ext - ( _i2c_jrn_beg + _AdrSize );

          // Отступить пришлось настолько, что дошли до начала
          // области журнала и перепрыгнули на ее конец.
          if ( lax > lbx )  i2c_jrn_addr = ( _i2c_jrn_end + 1 ) - ( lax - lbx );  // (w) - добавлено, чтобы не было
                                                                                 // предупреждения при i2c на 32К
          // Отступить пришлось настолько, что не дошли до начала области журнала.
          else            i2c_jrn_addr = j_ext - lax;

          // Запуск считывания извлекаемой из i2c записи
          jrn_adr_data = (b*)&MsgJrnPrint;
          // вычисляем сколько осталось до конца i2c.
          lbx = _i2c_jrn_end - i2c_jrn_addr + 1;
          size_i2c = sizeof( struct MSG_JRN );
          i2c_label = 0;
          Label = k314;
          // переход через верхнюю границу i2c.
          if ( size_i2c > lbx )
          {   // разбиваем запись блока на две части.
            size_i2c = lbx;

#endif //_CM3_
            Label = k312;
            // считываем одну часть блока:
    case k312:
            goto load;

    case k313:
            // считываем вторую часть блока:
            i2c_jrn_addr += size_i2c; // подгоняем указатель i2c.
            if ( i2c_jrn_addr > _i2c_jrn_end ) i2c_jrn_addr = _i2c_jrn_beg + _AdrSize;
            // Инкрементируем указатель занесения в i2c
            jrn_adr_data += size_i2c;   // данных считанных из ОЗУ.
            size_i2c = sizeof( struct MSG_JRN ) - size_i2c;
            i2c_label = 0;
            Label = k314;
          }

    case k314:
          goto load;

    case k315:
          Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
          Label++;

    case k316:
          // Находим соответствие имени из "MsgJrnPrint.name" с именем в const-таблице.
          // Если имени переменной не нашлось, то в "MsgJrnPrint.time_msg.time.b[ 7 ]" пишем 0.
          if ( TestJrnTab ( 1 ) == 0 )
                Label++;
          break;

    case k317:
          if ( *(w*)&MsgJrnPrint.time_msg.time.b[ 6 ] == _CntrCode ) //Запись обнаружена.
          {
            output_s ( "  Ok." ) ;
            Label = k2;
          }
          else
          {
            output_s ( _Jrn_no_Wrt ) ;
            Label = k20;
          }
          break;

    case k2: // выводим на верхнюю строку
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            bb = MsgJrnPrint.time_msg.time.b[ 4 ];  // дата
            cb = bb >> 4;
            cb += 0x30;
            output_c ( cb );
            cb = ( bb & 0x0F ) + 0x30;
            output_c ( cb );
            output_c ( '.' );

            bb = MsgJrnPrint.time_msg.time.b[ 5 ];  // месяц
            cb = bb >> 4;
            cb += 0x30;
            output_c ( cb );
            cb = ( bb & 0x0F ) + 0x30;
            output_c ( cb );

            output_s ( DayJrn[ ( MsgJrnPrint.time_msg.time.b[ 3 ] ) - 1 ] ); // день недели

            for ( ab = 2; (sw)ab >= 1; --ab  )  // часы, минуты
            {
              bb = MsgJrnPrint.time_msg.time.b[ ab ];
              cb = bb >> 4;
              cb += 0x30;
              output_c ( cb );
              cb = ( bb & 0x0F ) + 0x30;
              output_c ( cb );
              output_c ( ':' );
            }
            bb = MsgJrnPrint.time_msg.time.b[ 0 ];  // секунды

            cb = bb >> 4;
            cb += 0x30;
            output_c ( cb );
            cb = ( bb & 0x0F ) + 0x30;
            output_c ( cb );

            output_c ( '\n' );

            Label++;
          }
          break;

    case k3: //вывод на нижнюю строку имени переменной
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            for ( ab = 0; ab < _VarNameSize; ab++ ) output_c ( MsgJrnPrint.name[ ab ] );
            Label++;
          }
          break;

    case k4:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // Выход из этого режима
            {
end:          Pult_Prog_Addr = _MainPultProg, M_FirstCall = 1;
              JrnData.Stop = 0;   // запуск журнала
              return;   // добавить еще какую-то иниц.
            }
            else if ( m_ch == Up ) //уменьшить номер записи
            {
              if ( --m_index == 0 ) m_index = m_addr;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else if ( m_ch == Down ) //увеличить номер записи
            {
              if ( ++m_index > m_addr ) m_index = 1;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else if ( m_ch == Enter )
            {
              //в выбранной записи журнала зафиксировано изменение какой-то переменной
              if ( (sb)MsgJrnPrint.uslovie >= 0 ) Label = k7;
              //в выбранной записи журнала зафиксировано изменение количества сообщений -
              //поэтому переходим сразу на вывод сообщений
              else if ( (sb)MsgJrnPrint.uslovie == -1 )
              {
                BitJrn._.tst_msg_jrn = 1; //запускаем распечатку сообщений
                m_ext = (w)k2; //сохраняем точку входа при возврате в программу после отмены вывода сообщений
              }
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = k3;
          }
          break;

    case k7: //вывод на верхнюю строку имени переменной
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            output_c ( ' ' );
            for ( ab = 0; ab < _VarNameSize; ab++ ) output_c ( MsgJrnPrint.name[ ab ] );
            output_c ( '\n' );
            dptr = &FullJrnTab[ JrnData.number ];
            Label++;
          }
          break;

    case k8: //на нижней строке - условие и значение
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            // переменная аналоговая или сформиравана битовыми полями
            if ( dptr->code._.ad == 0 || dptr->code._.ad == 2 ) Label = k9;  //аналоговая переменная
            else Label = k11; //дискретная переменная
          }
          break;

    case k9: //значение аналоговой переменной
          if ( TestCompleted_Output() )
          {
            for ( ax = 0; ax < Menu3_size; ax++) //поиск текста условия
            {
              if ( MsgJrnPrint.uslovie == Menu3[ ax ].label )
              {
                output_s ( Menu3[ ax ].txt ); //распечатка условия
                break;
              }
            }

            ax = MsgJrnPrint.value; //берем значение переменной

            // Распечатка в 10-тичном виде

            // аналоговая переменная, сформированная битовыми полями или дисретная переменная
            if ( dptr->code._.ad == 2 || dptr->code._.ad == 1 ) bx = 1;
            else bx = dptr->nom;
            cx = *(w*)dptr->abs_nom;
            if ( dptr->code._.off_sign == 0 )
            {    //Если распечатка со знаком - выделяем знак и модуль
              if ( (sw)ax >= 0 )   sig_old = '+';
              else   ax = ~ax + 1, sig_old = '-';
            }

            //приводим содержимое ячейки к его номиналам
            lax = (lw)ax * (lw)cx;
            m_ext = lax % bx;
            lax /= bx;
            if ( lax > 0xffffu) lax = 0xffff;

            //распечатка целой части - максимум 5 символов
            ex = 5 - dptr->code._.celoe; //сколько первых символов пропустить
            if ( ex == 5 ) ex = 2; //для совместимости - если заданы были нули то принимаем формат "3.2".
            else if ( (sw)ex < 0 ) ex = 0;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;
              //пока идут первые нули - не выводим их:
              if ( bx == 0 && cx == 0 )
              {     //а пропускаем лишние нулевые символы,
                if ( ex != 0 ) ex--;
                //или заменяем пробелами
                else output_c (' ');
              }
              else
              {
                if ( cx == 0 )
                {
                  if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
                  cx = 1;
                }
                //первые нули закончились
                output_c ( (b)bx + 0x30 );
              }
            }   //распечатываем последнюю цифру
            if ( cx == 0 )
            {
              if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
            }
            output_c ( (b)(w)lax + 0x30 );
            Label = k10;
          }
          break;

    case k10:    //распечатка дробной части
          if ( TestCompleted_Output() )
          {
            if ( dptr->code._.celoe == 0 ) ex = 2;// по умолчанию.
            else ex = dptr->code._.drob;
            if ( ex != 0 )
            {
              output_c ( '.' );
              bx = dptr->nom;
              lax = m_ext; //восстанавливаем остаток
              for ( ; ex != 0 ; ex-- )
              {
                lax *= 10;
                ax = lax / bx;
                lax %= bx;
                output_c ( (b)ax + 0x30 );
              }
            }
            output_s ( dptr->ch );
            Label = k12;
          }
          break;

    case k11: //значение дискретной переменной
          if ( TestCompleted_Output() )
          {
            ab = MsgJrnPrint.value; //номер бита

            output_s ( "n." );
            output_c ( ab / 10  + 0x30 );
            output_c ( ab % 10  + 0x30 );
            for ( ax = 0; ax < Menu3_size; ax++ ) //поиск текста условия
            {
              if ( MsgJrnPrint.uslovie == Menu3[ ax ].label )
              {
                output_s ( Menu3[ ax ].txt ); //распечатка условия
                break;
              }
            }
            output_c ( '0' );
            Label = k12;
          }
          break;

    case k12:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = k2;
            else if ( m_ch == Enter )
            {
              BitJrn._.tst_msg_jrn = 1; //запускаем распечатку сообщений
              m_ext = (w)k2; //сохраняем точку входа при возврате в программу после отмены вывода сообщений
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = k8;
          }
          break;

          //---------------------------------------------

          load:   //   Ожидание чтения
               ax = xLoad_from_i2c ( size_i2c , i2c_jrn_addr, jrn_adr_data, _Adr_Flash_i2c ) ;
               if ( ax == 4 );   // пока = 4 - чтение не завершено.
               else if ( ax == 1 )
               { // нарушен алгоритм связи по i2c.
                 output_s ( _NoConnect_i2c_txt );
                 Mon.i2c_busy = 0;  // Устанавливаем признак, что теперь шина свободна.
                 goto end;
               }
               else  Label++;
               break;

    case k20: // Вывод номера записи
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( "N = " );

            lax = (lw)m_index;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;

              if ( bx == 0 && cx == 0 ) output_c (' '); //пока идут первые нули - не выводим их
              else
              {
                cx = 1;
                output_c ( (b)bx + 0x30 );
              }
            }
            output_c ( (b)(w)lax + 0x30 ); //распечатываем последнюю цифру
            Label = k21;
          }
          break ;

    case k21:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) goto end; // Выход из этого режима
            else if ( m_ch == Up ) //уменьшить номер записи
            {
              if ( --m_index == 0 ) m_index = m_addr;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else if ( m_ch == Down ) //увеличить номер записи
            {
              if ( ++m_index > m_addr ) m_index = 1;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = k20;
          }
          break;

  }

  Restart_Output ( );

  return;
}


//Запись буфера журнала в i2c
word Save_jrn ( void )
{
   register word    ax;
#ifndef _CM3_
   register word   bx;
   static word size_i2c ;
#else
   lword lbx;
   static lword size_i2c ;

#endif

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
  enum { i0, i00, i1, i2, i2_1, i2_2, i2_3, i2_4, i3, i7 };


    switch ( i2c_jrn_label )
     {
      default: i2c_jrn_label = i0;
      case i0:
               if ( ( ( OutJrnPtr + 1 ) & _MaxJrnCount ) != InJrnPtr ) i2c_jrn_label++; // в буфере есть новые данные
               break;

      case i00:
               if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
               Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята.
                  //  Взводим перед чтением в исходное состояние
                 // указатель метки для функции xLoad_from_i2c.
               i2c_label = 0, i2c_jrn_label++;
      case i1:
                 //   Считывание указателя адреса конца данных последней
                // зафиксированной в i2c записи.
               ax = xLoad_from_i2c ( _AdrSize , _i2c_jrn_beg , (b*)&i2c_jrn_addr, _Adr_Flash_i2c ) ;
               goto read;
               //-----------------
      case i2 :   //  Проверка указателя: не было ли там какого-то мусора.
               if ( i2c_jrn_addr < _i2c_jrn_beg+_AdrSize  ||
                    i2c_jrn_addr > _i2c_jrn_end) i2c_jrn_addr = _i2c_jrn_beg+_AdrSize ;
               //-----------------
                 // Берём адрес последней записи из буфера
               jrn_adr_data = (b*)&MsgJrn[ ( OutJrnPtr + 1 ) & _MaxJrnCount ];
#ifndef _CM3_
                 // вычисляем сколько осталось до конца i2c.
               bx = _i2c_jrn_end - i2c_jrn_addr + 1 ;
               size_i2c = sizeof(struct MSG_JRN) ;
               i2c_label = 0 , i2c_jrn_label = i2_3 ;
                      // переход через верхнюю границу i2c.
                 if ( size_i2c > bx )
                 {   // разбиваем запись блока на две части.
                   size_i2c = bx ;
#else  //_CM3_
                 // вычисляем сколько осталось до конца i2c.
               lbx = _i2c_jrn_end - i2c_jrn_addr + 1 ;
               size_i2c = sizeof(struct MSG_JRN) ;
               i2c_label = 0 , i2c_jrn_label = i2_3 ;
                      // переход через верхнюю границу i2c.
                 if ( size_i2c > lbx )
                 {   // разбиваем запись блока на две части.
                   size_i2c = lbx ;
#endif        //_CM3_
                   i2c_jrn_label = i2_1 ;
                    // записываем одну часть блока:
    case i2_1 :    goto save ;
    case i2_2 :      // записываем вторую часть блока:
                   i2c_jrn_addr += size_i2c ; // подгоняем указатель i2c.
                   if ( i2c_jrn_addr > _i2c_jrn_end ) i2c_jrn_addr = _i2c_jrn_beg+_AdrSize ;
                      // Инкрементируем указатель занесения в i2c
                   jrn_adr_data += size_i2c ;   // данных считанных из ОЗУ.
                   size_i2c = sizeof(struct MSG_JRN) - size_i2c ;
                   i2c_label = 0 , i2c_jrn_label = i2_3 ;
                 }
    case i2_3 :  goto save ;
    case i2_4 :
                i2c_jrn_addr += size_i2c ;    // подгоняем указатель i2c.
                if ( i2c_jrn_addr > _i2c_jrn_end ) i2c_jrn_addr = _i2c_jrn_beg+_AdrSize ;
                i2c_jrn_label = i3 ;
                break;

               //-----------------
      case i3 :  //   Запись указателя адреса конца данных последней
                // зафиксированной в i2c записи.
               ax = xSave_into_i2c ( _AdrSize , (b*) &i2c_jrn_addr , _i2c_jrn_beg, _Adr_Flash_i2c ) ;
               goto read;
      case i7 :
               Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
               OutJrnPtr = ( OutJrnPtr + 1 ) & _MaxJrnCount; //увеличиваем указатель отработанной записи
               i2c_jrn_label = i0;
               return 0;
               //-----------------

      //---------------------------------------------

          read:   //  Проверка кода возвращаемого п/п xLoad_from_i2c.
               if ( ax == 4 ) ;  // пока = 4 - продолжаем чтение.
               else if ( ax == 1 )
                 {
                   mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
                   Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                   i2c_jrn_label = i0;
                   return 1;
                 }
               else  i2c_jrn_label++ ;
               break;

          save:   //   Ожидание записи.
               ax = xSave_into_i2c ( size_i2c , jrn_adr_data , i2c_jrn_addr, _Adr_Flash_i2c ) ;
               if ( ax == 4 ) ;   // пока = 4 - запись не завершена.
               else if ( ax == 1 )
               {
                   // нарушен алгоритм связи по i2c.
                   mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
                   Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                   i2c_jrn_label = i0;
                   return 1;
               }
               else  i2c_jrn_label++ ;
               break;
    }
  return 4;
}
