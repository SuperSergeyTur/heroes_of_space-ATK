void RW_Prog( word flash_begin, word flash_end, byte flash_address )
{
  #define _WAIT    _fSec ( 1.0 ) // время ожидания ответа

  static byte count;  // счетчик
  static byte crs;    // контрольная сумма
  static byte size;   // размер блока данных
  union unSizeFile
  {
    word all;
    byte b[ 2 ];
  };
  static union unSizeFile SizeFile;
  static word CountByte;

  _register word ax;
  _register byte bh;

  enum{ m0 = 0, m1, m2,
        wr0,    wr1, wr2, wr3, wr4, wr5,
        rd0,    rd1, rd2, rd3, rd4, rd5, rd6, rd7, rd8, rd9, rd10,
        cl0,    cl1, cl2, cl3
      };

  if( M_FirstCall == 1 )
  {
      // перевод в режим быстрого вывода
      m_ext = Pult_Prog_Addr; // сохраняем код команды чтобы его не перебил
      if( Mon.Pult == 1 ) Speed_Pult( ); //  "Speed_Pult()"
      Pult_Prog_Addr = m_ext;
      crs = 0;
      M_FirstCall = 0;
      output_c( '@' );
      Label = m0;
      return;
  }

  switch( Label )
  {
      // Исходное состояние
      default: Label = m0;
      case m0:
             if( TestCompleted_Output( ) != 0 )
             {
                 size = sizeof( m_buff ); // размер буфера
                 output_c( size );
                 crs -= size;
                 bh = Hb( flash_begin ); // старший байт начального адреса
                 output_c( bh );
                 crs -= bh;
                 bh = Lb( flash_begin ); // младший байт начального адреса
                 output_c( bh );
                 crs -= bh;
                 bh = Hb( flash_end ); // старший байт конечого адреса
                 output_c( bh );
                 crs -= bh;
                 bh = Lb( flash_end ); // младший байт конечого адреса
                 output_c( bh );
                 crs -= bh;
                 output_c( crs ); // контрольная сумма
                 Label++;
                 m_time = Timer1_fSec; //засечь время
             }
             break;
      case m1:
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 if( bh == crs )
                 {
                     m_time = Timer1_fSec; // засечь время
                     Label++;
                 }
                 else
                 {
                     output_c( ~crs );
                     goto end;
                 }
             }
             break;
      case m2:
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 if( bh == Return )  // выход из этого режима
                 {
end:
                     Pult_Prog_Addr = _MainPultProg;
                     M_FirstCall = 1;
                     return;
                 }
                 else if( bh == 'W' ) // запись i2c
                 {
                     output_c( 'W' );
                     count = 0;
                     Label = wr0;
                 }
                 else if( bh == 'R' ) // чтение i2c
                 {
                     output_c( 'R' );
                     m_addr = flash_begin;
                     crs = 0;
                     Label = rd0;
                 }
                 else if( bh == 'C' ) // стирание i2c
                 {
                     output_c( 'C' );
                     for( CountByte = 0; CountByte < sizeof( m_buff ); CountByte++ ) m_buff[ CountByte ] = 0;
                     m_addr = flash_begin;
                     CountByte = 0;
                     crs = 0;
                     Label = cl0;
                 }
                 else goto end;
             }
             break;

      // Запись файла в i2c
      case wr0:
             // если за 0.5с ничего не поступило в приёмный буфер
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // засечь время
                 if( count < 2 ) // получение 2-х байт размера файла
                 {
                     SizeFile.b[ count ] = bh;
                     crs -= bh;
                     count++;
                 }
                 else
                 {
                     if( bh == crs ) // получена контрольная сумма пачки
                     {
                         output_c( crs );
                         m_time = Timer1_fSec; // засечь время
                         Label++;
                     }
                     else
                     {
                         output_c( ~crs );
                         goto end;
                     }
                 }
             }
             break;
      case wr1:
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина
             Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята
             m_addr = flash_begin;
             Label++;
      case wr2:
             ax = xSave_into_i2c( 2, (b*)&SizeFile.all, m_addr, flash_address ); // запись 2-х байт размера файла
             if( ax == 4 ) break;  // пока = 4 - продолжается запись
             Mon.i2c_busy = 0;  // Устанавливаем признак, что теперь шина свободна.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoWrite_i2c );
                 output_c( ~crs );
                 goto end;
             }
             else
             {
                 m_addr += 2;
                 Label++;
                 CountByte = 0;
                 count = 0;
                 m_time = Timer1_fSec; // засечь время
                 output_c( crs );
             }
             break;
      case wr3:
             //если за 0.5с ничего не поступило в приёмный буфер
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input ( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // засечь время
                 if( count < size && CountByte < SizeFile.all ) // получение очередной пачки
                 {
                     m_buff[ count ] = bh;
                     crs -= bh;
                     count++;
                     CountByte++;
                 }
                 else
                 {
                     if( bh == crs ) // получена контрольная сумма пачки
                     {
                         output_c( crs );
                         Label++;
                     }
                     else
                     {
                         output_c( ~crs );
                         goto end;
                     }
                 }
             }
             break;
      case wr4:
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина
             Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята
             Label++;
      case wr5:
             ax = xSave_into_i2c( count, (b*)&m_buff, m_addr, flash_address );
             if( ax == 4 ) break;  // пока = 4 - продолжается запись
             Mon.i2c_busy = 0;  // Устанавливаем признак, что теперь шина свободна.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoWrite_i2c );
                 output_c( ~crs );
                 goto end;
             }
             else
             {
                 output_c( crs );
                 m_addr += count;
                 if( CountByte < SizeFile.all ) // все ли байты получены?
                 {
                     m_time = Timer1_fSec; // засечь время
                     Label -= 2;
                     count = 0;
                 }
                 else goto end;
             }
             break;

      // Чтение файла из i2c
      case rd0:
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина
             Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята
             Label++;
      case rd1:
             ax = xLoad_from_i2c( 2, m_addr, (b*)&SizeFile.all, flash_address ); // считываем размер файла
             if( ax == 4 ) break;  // пока = 4 - продолжается чтение
             Mon.i2c_busy = 0;  // Устанавливаем признак, что теперь шина свободна.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoRead_i2c );
                 SizeFile.all = 0;
             }
             bh = Hb( SizeFile.all ); // старший байт размера файла
             output_c( bh );
             crs -= bh;
             bh = Lb( SizeFile.all ); // младший байт размера файла
             output_c( bh );
             crs -= bh;
             if( (w)SizeFile.all > (w)( flash_end - flash_begin ) || SizeFile.all == 0 ) // размер файла некорректный или ошибка чтения
             {
                 output_c( ~crs );
                 goto end;
             }
             output_c( crs );
             m_addr += 2;
             Label++;
             break;
      case rd2:
             // если за 0.5с ничего не поступило в приёмный буфер
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // засечь время
                 if( bh == crs ) // получена контрольная сумма пачки
                 {
                     CountByte = 0;
                     Label++;
                 }
                 else
                 {
                     output_c( ~crs );
                     goto end;
                 }
             }
             break;
      case rd3:
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина
             Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята
             Label++;
      case rd4:
             ax = xLoad_from_i2c( size, m_addr, (b*)&m_buff, flash_address ); // считываем контрольный код
             if( ax == 4 ) break;  // пока = 4 - продолжается чтение
             Mon.i2c_busy = 0;  // Устанавливаем признак, что теперь шина свободна.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoRead_i2c );
             }
             else
             {
                 for( count = 0; count < size && CountByte < SizeFile.all; count++, CountByte++ )
                 {
                     if( CountByte < 8 && m_buff[ count ] != CtrlCode[ count ] ) // проверка контрольного кода
                     {
                         ax = 1;
                     }
                     output_c( m_buff[ count ] );
                     crs -= m_buff[ count ];
                 }
                 if( ax == 1 )
                 {
                     output_c( ~crs );
                     goto end;
                 }
                 else output_c( crs );
                 m_addr += size;
                 Label++;
             }
             break;
      case rd5:
             // если за 0.5с ничего не поступило в приёмный буфер
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // засечь время
                 if( bh == crs ) // получена контрольная сумма пачки
                 {
                     if( CountByte < SizeFile.all ) Label -= 2;
                     else goto end;
                 }
                 else
                 {
                     output_c( ~crs );
                     goto end;
                 }
             }
             break;

      // очистка
      case cl0:
             SizeFile.all = flash_end - m_addr + 1;  // вычисляем сколько байт осталось до конечного адреса
             if( SizeFile.all > size ) count = size;
             else                      count = (b)SizeFile.all;
             Label++;
      case cl1:
             if( Mon.i2c_busy == 1 ) break; // Ждем, пока освободится шина
             Mon.i2c_busy = 1;  // Устанавливаем признак, что теперь шина занята
             Label++;
      case cl2:
             ax = xSave_into_i2c( count, (b*)&m_buff, m_addr, flash_address );
             if( ax == 4 ) break;  // пока = 4 - продолжается запись
             Mon.i2c_busy = 0;  // Устанавливаем признак, что теперь шина свободна.
             CountByte += count;
             m_addr += count;
             bh = Hb( CountByte ); // старший байт счетчика стертых байт
             output_c( bh );
             crs -= bh;
             bh = Lb( CountByte ); // младший байт счетчика стертых байт
             output_c( bh );
             crs -= bh;
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoWrite_i2c );
                 output_c( ~crs );
                 goto end;
             }
             else
             {
                 output_c( crs );
                 m_time = Timer1_fSec; // засечь время
                 Label++;
             }
             break;
      case cl3:
             //если за 0.5с ничего не поступило в приёмный буфер
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 if( bh == crs ) // получена контрольная сумма
                 {
                     // все ли байты очищены?
                     if( m_addr < flash_end )
                     {
                         Label -= 3;
                     }
                     else goto end;
                 }
                 else goto end;
             }
             break;
  }
  Restart_Output( );
  return;
}
