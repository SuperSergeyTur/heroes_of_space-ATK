

   //    Функция-переходник для совместимости xSave_into_i2c и
   //  Save_into_i2c для ранее написанных программ.

word  Save_into_i2c ( word n , byte *from , word into, byte c_addr )
{
  register word ax ;

  size_block_rw = 8 ;  // чтобы ускорить запись и, Главное, для инициализации этой переменной
  i2c_label = 0 ;
  do
  {
    ax = xSave_into_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );
  size_block_rw = 1 ; // чтобы не раздувать фоновый цикл и, Главное, для инициализации этой переменной

  return ax ;
}


   //    Функция-переходник для совместимости xLoad_from_i2c и
   //  Load_from_i2c для ранее написанных программ.

word  Load_from_i2c ( word n , word from , byte *into, byte c_addr )
{
  register word ax ;

  size_block_rw = 8 ;  // чтобы ускорить запись и, Главное, для инициализации этой переменной
  i2c_label = 0 ;
  do
  {
    ax = xLoad_from_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );
  size_block_rw = 1 ; // чтобы не раздувать фоновый цикл и, Главное, для инициализации этой переменной

  return ax ;
}


/*    При времени периода SCL равном 35 мксек:
   - время успешного чтения байта   - 1.5 мсек;
   - время неуспешного чтения байта после предыдущей записи - 0.5 мсек;
   - время успешной записи байта    - 1.0 мсек;
   - время программирования байта   - 1.0 мсек;
   - время побайтной записи с проверкой чтением всей flash-памяти 7сек.
 */

//  Запись блока данных размером 'n' из ОЗУ по адресу 'from' в i2c-flash
// по адресу 'into'.
//  Программа возвращает:
// - 4 - в процессе записи пока не записаны все байты блока;
// - 0 - при успешном завершении записи всех байт;
// - 1 - при неуспешной записи.
//   Используется алгоритм побайтной записи блока с использованием п/п
// с алгоритмами пошагового обращения к i2c. После каждого шага осуществляется
// выход из п/п. Таким образом запись в i2c можно применять в процессе
// работы с записью в i2c от пульса к пульсу.
//

word  xSave_into_i2c ( word n , byte *from , word into, byte c_addr )
{
  register word  ax, dx ;
  enum { i0, i1 } ;
  enum { j0, j1, j2, j3 } ;

  dx = 4 ;   //  код того, что работа c i2c не завершена.

  switch ( i2c_label )
  {
    default: i2c_label = 0 ;
    case i0 :  // если не задано ничего, то не ничего и не начинаем.
        if ( n == 0 ) return 0 ; // код нормального завершения или ошибки.

        Set_line_i2c () ; // настройка линии.
        ax_i2c = 1 ;
        from_i2c = from , into_i2c = (w)into ;
        i2c_label1 = 0 , time_i2c = Timer1_Ovr ;

        i2c_label = i1 ;
        break;
//Vit Ajax  break;

    case i1 :
      switch ( i2c_label1 )   // определение номера очередного шага.
      {
        default: i2c_label1 = 0 ;
        case j0 :   // выводим старт условие и адрес микросхемы
            Start_i2c()  ;
            Wr_byte_i2c ( c_addr | _WR_i2c )  ;
            ACK_set()   ;
            if ( mACK() == 1 )   goto stop2 ;
//            time_i2c = Timer1_Ovr ; // сбрасываем выдержку после удачной
                                   //  записи очередного фрейма.
            i2c_label1++ ;
         if ( c_addr == _Adr_M41T56 )
         {
            i2c_label1++ ;
            break;
         }
            break;
//Vit Ajax  break;
        case j1 :     // выводим старший байт адреса памяти внутри микросхемы
            Wr_byte_i2c ((b)( into_i2c >> 8 ))  ;
            ACK_set()   ;
            if ( mACK() == 1 )   goto stop ;

            i2c_label1++ ;
            break;
//Vit Ajax  break;

        case j2 :     // выводим младший байт адреса памяти внутри микросхемы
            Wr_byte_i2c ( (b)into_i2c )  ;
            ACK_set()   ;
            if ( mACK() == 1 )   goto stop ;

            i2c_label1++ ;
            break;
//Vit Ajax  break;

        case j3 :
           ax = 0 ;
      xxx: Wr_byte_i2c ( *from_i2c )  ;  // непрерывно пишем байт за байтом.
           ACK_set()   ;
           if ( mACK() == 1 )   goto stop ;

           from_i2c++ , into_i2c++ , ax_i2c++ ;
           if ( ax_i2c <= n )
           {    // Не началась ли новая страница?
             if( (into_i2c % _Page_i2c) == 0 )
             {    // Если началась, то ставим Stop-условие, и начинаем с начала.
               time_i2c = Timer1_Ovr ; // сбрасываем выдержку после удачной
                                   //  записи очередного фрейма.
               Stop_i2c() ;
               i2c_label1 = j0 ; // взводим метку в исходное состояние.
             }
             //else  if ( ++ax <= 8 ) goto xxx ;
             else
             {
               ax++ ;
               if ( ax < size_block_rw ) goto xxx ;
             }
           }
           else         //  После прочтения всего, что надо
           {            // выводим стоп условие.
             dx = 0 ;   //  код того, что работа c i2c завершена.
         end:
             Stop_i2c() ;
             Clr_line_i2c () ; // восстановление линии.
             i2c_label = 0 ; // взводим метку в исходное состояние.
           }
           break;
           //------------
      stop:
           dx = 1 ;   //  код того, что произошел сбой.
           goto end ;
      stop2:
           ax = Timer1_Ovr - time_i2c;
           if ( (u)ax >= _Sec( 0.25 ))
           {
             dx = 1 ;  // время ожидания истекло. - бывает когда не запаяны
             goto end ;                // часы реального времени.
           }
              // повтор записи на случай, если Flash еще
              // не вышла из режима програмирования, и по этому
              // не ответила на первый ACK.
           else   i2c_label1 = j0 ;
           break;
      }
    //----------
  }

  return dx ;   //  код продолжения записи.
}



//  Запись блока данных размером 'n' из i2c-flash по адресу 'from' в ОЗу
// по адресу 'into'.
//  Программа возвращает:
// - 4 - в процессе записи пока не записаны все байты блока;
// - 0 - при успешном завершении записи всех байт;
// - 1 - при неуспешной записи.
//   Используется алгоритм побайтной записи блока с использованием п/п
// с алгоритмами пошагового обращения к i2c. После каждого шага осуществляется
// выход из п/п. Таким образом запись в i2c можно применять в процессе
// работы с записью в i2c от пульса к пульсу.
//

word  xLoad_from_i2c ( word n , word from , byte *into , byte c_addr)
{
  register word  ax, dx ;
  enum { i0, i1 } ;
  enum { j0, j1, j2, j3, j4 } ;

  dx = 4 ;   //  код того, что работа c i2c не завершена.

  switch ( i2c_label )
  {
    default: i2c_label = 0 ;
    case i0 :  // если не задано ничего, то не ничего и не начинаем.
        if ( n == 0 ) return 0 ; // код нормального завершения или ошибки.

        Set_line_i2c () ; // настройка линии.
        ax_i2c = 1 ;
        from_i2c = into , into_i2c = (w)from ;
        i2c_label1 = 0 , time_i2c = Timer1_Ovr ;

        i2c_label = i1 ;
        break;
//Vit Ajax  break;

    case i1 :
      switch ( i2c_label1 )   // определение номера очередного шага.
      {
        default: i2c_label1 = 0 ;
        case j0 :  // выводим старт условие и адрес микросхемы
           Start_i2c()  ;
           Wr_byte_i2c ( c_addr | _WR_i2c )  ;
           ACK_set()   ;
           if ( mACK() == 1 )   goto stop2 ;

            i2c_label1++ ;

          if ( c_addr == _Adr_M41T56 )
          {
            i2c_label1++ ; //  для часов перепрыгиваем одну метку
            break;
          }
            break;
//Vit Ajax  break;
        case j1 :  // выводим старший байт адреса памяти внутри микросхемы
           Wr_byte_i2c ((b)( into_i2c >> 8 ))  ;
           ACK_set()   ;
           if ( mACK() == 1 )   goto stop ;

            i2c_label1++ ;
            break;
//Vit Ajax  break;

        case j2 :  // выводим младший байт адреса памяти внутри микросхемы
           Wr_byte_i2c ( (b)into_i2c )  ;
           ACK_set()   ;
           if ( mACK() == 1 )   goto stop ;

            i2c_label1++ ;
            break;
//Vit Ajax  break;

        case j3 :  // повторяем старт условие и адрес микросхемы с битом чтения.
           Start_i2c()  ;
           Wr_byte_i2c ( c_addr | _RD_i2c )  ;
           ACK_set()   ;
           if ( mACK() == 1 )   goto stop ;

            i2c_label1++ ;
            break;
//Vit Ajax  break;

        case j4 :  // непрерывно читаем байт за байтом.
           ax = 0 ;
     xxx: *from_i2c = Rd_byte_i2c ()  ;

           from_i2c++ , ax_i2c++ ;
           if ( ax_i2c > n )   //  После прочтения всего, что надо
           {                  // выводим стоп условие.
             dx = 0 ;   //  код того, что работа c i2c завершена.
         end:
             ACK_set()   ;
             Stop_i2c() ;
             Clr_line_i2c () ; // восстановление линии.
             i2c_label = 0 ; // взводим метку в исходное состояние.
           }
           else  // Квитируем "ACK" как признак продолжения чтения.
           {
             ACK_clr()   ;
             //if ( ++ax <= 8 ) goto xxx ;
             ax++ ;
             if ( ax < size_block_rw ) goto xxx ;
           }
           break;
           //------------
      stop:
           dx = 1 ;   //  код того, что произошел сбой.
           goto end ;
      stop2:
           ax = Timer1_Ovr - time_i2c;
           if ( (u)ax >= _Sec( 0.25 ))
           {
             dx = 1 ;  // время ожидания истекло. - бывает когда не запаяны
             goto end ;                // часы реального времени.
           }
              // повтор записи на случай, если перед считыванием была
              // запись и Flash еще не вышла из режима програмирования,
              // и по этому не ответила на первый ACK.
           else   i2c_label1 = j0 ;
           break;
      }
//----------------
  }

  return dx ;   //  код продолжения записи.
}

//----------------------------------------------

//  Подсчет контрольной суммы блока ОЗУ размером 'n' начиная с адреса
// 'from'.
//  Контрольная сумма записывается в последний байт заданного блока -
// этот байт должен быть зарезервирован под конрольную сумму.

word Chek_sum ( word n , byte *from )
{
  register byte *ptr ;
  register word bx , cx ;

  ptr = from, bx = 0 , cx = 0 ;
  while ( ptr < ( from + n - 1 ) )
    {
      bx -= *ptr ;  // Подсчет контрольной суммы для
      ptr++;           // всей таблицы кроме последнего байта.
    }
  if ( *ptr != (b)bx )  cx = 1 ;

  *ptr = bx ;  // Запись в последний байт таблицы уставок

   return cx ;
}

//----------------------------------------------

