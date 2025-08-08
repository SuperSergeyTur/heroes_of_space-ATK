//Задание частоты передачи данных по i2c
void   Start_i2c_bus( void )
{
  ICCR_EN = 0; // 25.03.2015 9:02      Сначала выключается i2c, а затем настраивается скорость.
  ICCR_CS = 0x0c;  // 0x05 - 25 кГц    Иначе - нестабильность работы, проявлялась в неверном определении размера i2c,
                   // 0x1C - 31 кГц    принятии типовых уставок.
                   // 0x14 - 35 кГц
                   // 0x0C - 41 кГц
                   // 0x0B - 83 кГц
                   // 0x03 - 100 кГц
                   // 0x00 - 625 кГц
  ICCR_EN = 1;
  return ;
}

   //    Функция-переходник для совместимости xSave_into_i2c и
   //  Save_into_i2c для ранее написанных программ.

word  Save_into_i2c ( word n , byte *from , word into, byte c_addr )
{
  register word ax ;

  i2c_label = 0 ;
  do
  {
    ax = xSave_into_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );

  return ax ;
}


   //    Функция-переходник для совместимости xLoad_from_i2c и
   //  Load_from_i2c для ранее написанных программ.

word  Load_from_i2c ( word n , word from , byte *into, byte c_addr )
{
  register word ax ;

  i2c_label = 0 ;
  do
  {
    ax = xLoad_from_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );

  return ax ;
}



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
  register word dx, ax, cx ;
  enum { i0, i1, i2, i3,i35, i4, i5, i6, i7 } ;

  switch ( i2c_label )
  {
    default: i2c_label = 0 ;
    case i0 :
              from_i2c = from , into_i2c = into ;

              ax = (into_i2c+ _Page_i2c);
              cx = ax%_Page_i2c;
              i2c_Pi = ax - cx;
              ax_i2c = 1 ;
              cx_i2c = 0;
              bx_i2c = 0;
              Set_line_i2c() ; // настройка линии.
              i2c_label = i1 ;
              break;

    case i1 :

        i2c_label1 = 0 , time_i2c = Timer1_Ovr ;
        i2c_label = i2 ;
        break;

    case i2 :
              dx = 4;

              switch ( i2c_label1 )   // определение номера очередного шага.
              {

         default: i2c_label1 = 0 ;
         case i0 :
              ax = timer1;
              bx_i2c = 0;
              //Ожидание пока освободиться шина
              while(IBSR_BB == 1)
              {
                ICCR_EN = 0;
                ICCR_EN = 1;
                if( (u)((w)(timer1 - ax)) >= _MkSec(100) )
                {
                 goto stop;
                }
              }
               //загружаем адресный регистр
                   IDAR =  ( c_addr | _WR_i2c )  ;
               //старт передачи
                   IBCR = 0x10;

                   i2c_label1++ ;
                   i2c_tim = timer1;

                   //break;

           case i1:
                  //Ожидаем пока завершится передача
                  ax = timer1 - i2c_tim;
                  if (IBCR_INT == 1)
                  {
                    i2c_label1++ ;
                    if ( c_addr == _Adr_M41T56 )  i2c_label1++ ;
                  }
                  else if ( (u)ax >= _MkSec(3000) )
                  {
                     IBCR = 0;
                     i2c_label1 = i0 ;
                     if ( ++cx_i2c > 3 )
                     {
                      goto stop;
                     }
                  }
                  break;
         case i2 :

                  //Проверка наличия сигнала ACK  IBSR_LRB - последний полученный бит
                  // должен быть = 0
                   if ( IBSR_LRB == 1 )
                   {
                    stop:

                       IBCR = 0;
                       dx =  1 ;   //  код того, что произошел сбой.
                       break;
                   }
                   //передаем старший байт адреса
                   IDAR = (b)( into_i2c >> 8)  ;

                   IBCR = 0x10;

                    i2c_label1++ ;

                   cx = timer1;
                   // ждем окончания передачи
                   while (IBCR_INT == 0)
                   {
                     ax = timer1- cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }
                   //while (IBCR_INT == 0) ;

                    break;

         case i3 :
                  //Проверка наличия сигнала ACK  IBSR_LRB - последний полученный бит
                  // должен быть = 0

                   if ( IBSR_LRB == 1 )
                   {
                     goto stop ;
                   }

                   //передаем младший байт адреса

                   IDAR = (b)into_i2c   ;

                   IBCR = 0x10;

                   i2c_label1++ ;
                   cx = timer1;

                   while (IBCR_INT == 0)
                   {
                     ax = timer1- cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }

                   break;
         case i35 :

                   // ждем окончания передачи
                   i2c_label1++ ;

                   //while (IBCR_INT == 0) ;
                   if ( IBSR_LRB == 1 )
                   {
                    goto stop ;
                   }
        case i4 :
                 //загружаем байт данных
          trans:
                 IDAR = *from_i2c ;

                 IBCR = 0x10;

                 i2c_label1++ ;

                   cx = timer1;

                   // ждем окончания передачи

                   while (IBCR_INT == 0)
                   {
                     ax = timer1 - cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }
                   while ((u)((w)(timer1-cx)) < _MkSec(200)) ;
                 //break;

      case i5 :
                //Проверка наличия сигнала ACK  IBSR_LRB - последний полученный бит
                // должен быть = 0
                if ( IBSR_LRB == 1 )
                {
                 goto stop ;
                }

                 from_i2c++;
                 if ( ++ax_i2c> n )
                 {
                    dx = 0;
                    IBCR = 0;
                 }
                 else if ( ++into_i2c == i2c_Pi )
                 {
                   i2c_Pi += _Page_i2c ;
                   IBCR = 0;
                   cx_i2c = 0;
                   time_i2c = Timer1_Ovr ;
                   i2c_label1 = i0;
                 }
                 else if (++bx_i2c >= 8 )
                 {
                        i2c_label1 = i4;
                        bx_i2c = 0;
                 }
                 else goto trans;

                 break;
              }

            if ( dx != 4 )
              {
                  if ( dx == 1 )
                  {
                    ax = Timer1_Ovr - time_i2c;
                    if ( (u)ax >= 6 )
                      {
                        dx = 1 ;  // время ожидания истекло.
                      }
                      else
                      {
                        i2c_label1 = 0 ;  // повтор записи на случай, если Flash еще
                                          // не вышла из режима програмирования, и по этому
                                          // не ответила на ACK.
                        break;
                      }
                  }

                  Clr_line_i2c() ; // восстановление линии.
                  i2c_label = 0 ;
                  return dx ; // код нормального завершения или ошибки.
              }
        break;
  }

  return 4 ;   //  код продолжения записи.
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
  register word  dx, cx ;
  word ax;
  enum { i0, i1, i2, i3, i4, i5, i6,i7} ;

  switch ( i2c_label )
  {
    default: i2c_label = 0 ;
    case i0 :
              ax_i2c = 1 ;
              Set_line_i2c() ; // настройка линии.
              from_i2c = into , into_i2c = from ;
              i2c_label = i1 ;

                break;

    case i1 :

        i2c_label1 = 0 , time_i2c = Timer1_Ovr ;
        i2c_label = i2 ;
        break;

    case i2 :
              dx = 4;
              switch ( i2c_label1 )   // определение номера очередного шага.
              {
            default: i2c_label1 = 0 ;
            case i0 :
              ax = timer1;

              while(IBSR_BB == 1)
              {
                ICCR_EN = 0;
                ICCR_EN = 1;
                if( (u)((w)(timer1 - ax)) >= _MkSec(100) )
                {
                  goto stop;
                }
              }

                 IDAR =  ( c_addr | _WR_i2c )  ;

                 IBCR = 0x10;

                 i2c_label1++ ;
                  i2c_tim = timer1;

                  break;
           case i1:
                  ax = timer1- i2c_tim;
                  if (IBCR_INT == 1)
                  {
                    i2c_label1++ ;
                    if ( c_addr == _Adr_M41T56 )  i2c_label1++ ;
                  }
                  else if ( (u)ax > _MkSec(3000) )
                  {
                       goto stop;
                  }
                  break;

         case i2 :

                   if ( IBSR_LRB == 1 )
                   {

                  stop:

                     IBCR = 0;
                     dx =  1 ;   //  код того, что произошел сбой.
                     break;
                   }

                   IDAR = (b)( into_i2c >> 8)  ;

                   IBCR = 0x10;

                    i2c_label1++ ;

                   cx = timer1;
                   while (IBCR_INT == 0)
                   {
                     ax = timer1- cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }
                   //while (IBCR_INT == 0);

                    break;

         case i3 :

                   if (IBSR_LRB == 1 )
                   {
                    goto stop ;
                   }

                   IDAR = (b)into_i2c   ;

                   IBCR = 0x10;

                   i2c_label1++ ;

                   cx = timer1;
                   while (IBCR_INT == 0)
                   {
                     ax = timer1- cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }
                   //while (IBCR_INT == 0);

                   break;

            case i4 :

                   if ( IBSR_LRB == 1 )
                   {
                     goto stop ;
                   }

                   IDAR =  c_addr | _RD_i2c   ;

                   IBCR = 0x30;
                    i2c_label1++ ;
                   cx = timer1;
                   while (IBCR_INT == 0)
                   {
                     ax = timer1- cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }
                   //while (IBCR_INT == 0);

                   if ( IBSR_LRB == 1 )
                   {
                    goto stop ;
                   }
                   bx_i2c = 0;
                    //break;

         case i5 :
          load:     if (++ax_i2c > n )
                    {
                       IBCR = 0x10;

                    }
                    else IBCR = 0x18;

                    i2c_label1++ ;

                   cx = timer1;
                   while (IBCR_INT == 0)
                   {
                     ax = timer1- cx ;
                     if ( (u)ax > _MkSec(3000) )  goto stop;
                   }
                   //while (IBCR_INT == 0);


                //   break;
        case i6 :


                   *from_i2c = IDAR  ;

                    if ( ax_i2c > n )
                    {
                       IBCR = 0;
                       dx = 0;   //  код того, что работа c i2c завершена.
                    }
                    else
                    {
                      from_i2c++;
                      if ( ++bx_i2c >= 8)
                      {
                            i2c_label1 = i5 ;
                            bx_i2c = 0;
                      }
                      else goto load;
                    }
                   break;
              }
      if ( dx != 4 )
        {
           if ( dx == 1 )
            {
              ax = Timer1_Ovr - time_i2c;
              if ( (u)ax >= 2 )
                {
                  dx = 1 ;  // время ожидания истекло.
                }
                else
                {
                  i2c_label1 = 0 ;  // повтор записи на случай, если Flash еще
                                    // не вышла из режима програмирования, и по этому
                                    // не ответила на ACK.
                  break;
                }
            }

           Clr_line_i2c() ; // восстановление линии.
           i2c_label = 0 ;
           return dx ; // код нормального завершения или ошибки.
        }
        break;
  }

  return 4 ;   //  код продолжения записи.
}

//----------------------------------------------

//  Подсчет контрольной суммы блока ОЗУ размером 'n' начиная с адреса
// 'from'.
//  Контрольная сумма записывается в последний байт заданного блока -
// этот байт должен быть зарезервирован под конрольную сумму.

word Chek_sum ( word n , byte *from )
{
  _register lword ax; //, bx ;
   byte bx;
  word cx ;
  ax = (lw)from, bx = 0 , cx = 0 ;

    while ( ax < ( (lw)from + n - 1 ) )
        {
            bx -= *(b*)ax ;  // Подсчет контрольной суммы для
            ax++;            // всей таблицы кроме последнего байта.

        }
    if ( *(b*)ax != (b)bx )  cx = 1 ;
    *(b*)ax = bx ;  // Запись в последний байт таблицы уставок

   return cx ;
}


        /*   Функция чтения байта по заданному адресу
         * в пошаговом алгоритме с выходом из п/п после каждого шага.
         *   В качестве параметров ей передаются:
         *  addr   - адрес ячейки flash-памяти, которую следует
         *           прочитать;
         * *result - адрес ячейки памяти контроллера, в которую следует
         *           поместить значение считанное из flash-памяти при
         *           успешном чтении.
         *   Функция возвращает значения:
         * "4" -  в процессе чтения пока не пройдены все шаги;
         * "0" -  при успешном завершении чтения;
         * "1" -  при неуспешном чтении.
         *   При неуспешном чтении записи по адресу "result" не производится.
         * Успешным чтением является такое, при котором получены ответы от
         * flash-памяти на все "ACK" выставленные мастером. Flash-память
         * не отвечает на "ACK", если она, например, находится в фазе
         * программирования после предыдущей записи в нее. Таким образом
         * данная функция может бать использована для контроля заверешения
         * цикла программирования: если при чтении после записи функция
         * возвращает "1" - программирование не завершено => считывание
         * следует повторять до тех пор пока функция не возвратит "0".
         */
/*word   xRead_i2c_flash ( word addr , byte* result , byte c_addr)
{
  enum { i0, i1, i2, i3, i4, i5, i6, i7 } ;
  word ax;
  switch ( i2c_label1 )   // определение номера очередного шага.
  {
    default: i2c_label1 = 0 ;
    case i0 :

    ax = timer1;
 	while(IBSR_BB == 1)
 	{
 	  ICCR_EN = 0;
 	  ICCR_EN = 1;
    if( (u)((w)(timer1 - ax)) >= _MkSec(100) ) goto stop;
 	}

     IDAR =  ( c_addr | _WR_i2c )  ;

     IBCR = 0x10;

     i2c_label1++ ;

     if ( c_addr == _Adr_M41T56 )  i2c_label1++ ;

       while (IBCR_INT == 0);
        break;

    case i1 :

       if ( IBSR_LRB == 1 )
       {

         //Vit 14.05.07 15:48 mSet_ServiceMsg( _Srv_2 );
         goto stop ;
       }

       IDAR = (b)( addr >> 8)  ;

       IBCR = 0x10;

        i2c_label1++ ;

       while (IBCR_INT == 0);

        break;

    case i2 :

       if (IBSR_LRB == 1 ) goto stop ;

       IDAR = (b)addr   ;

       IBCR = 0x10;

       i2c_label1++ ;

       while (IBCR_INT == 0);

       break;

    case i3 :

       if ( IBSR_LRB == 1 )
       {
         //Vit 14.05.07 15:48 mSet_ServiceMsg( _Srv_1);
         goto stop ;
       }

       IDAR =  c_addr | _RD_i2c   ;

       IBCR = 0x30;
        i2c_label1++ ;
       while (IBCR_INT == 0);
        break;

    case i4 :

       if ( IBSR_LRB == 1 ) goto stop ;

       IBCR = 0x10;
       i2c_label1++ ;
       while (IBCR_INT == 0);

    case i5 :


       *result = IDAR  ;

       IBCR = 0;
       return 0 ;   //  код того, что работа c i2c завершена.
  }
     return 4 ;   //  код того, что работа c i2c не завершена.

  stop:

     IBCR = 0;
     return 1 ;   //  код того, что произошел сбой.
}
*/

        /*   Функция записи заданного байта данных по заданному адресу
         * в пошаговом алгоритме с выходом из п/п после каждого шага.
         *   В качестве параметров ей передаются:
         *  addr   - адрес ячейки flash-памяти, в которую следует
         *           записать заданный байт данных;
         *  data   - байт данных, который следует записать по заданному
         *           адресу.
         *   Функция возвращает значения:
         * "4" -  в процессе записи пока не пройдены все шаги;
         * "0" -  при успешном завершении записи;
         * "1" -  при неуспешной записи.
         * Успешной записью является такая, при которой получены ответы от
         * flash-памяти на все "ACK" выставленные мастером. Flash-память
         * не отвечает на "ACK", если она, например, находится в фазе
         * программирования после предыдущей записи в нее.
         */
/*word   xWrite_i2c_flash ( word addr , byte data , byte c_addr)
{
  enum { i0, i1, i2, i3, i4, i5, i6, i7 } ;
  word ax;

  switch ( i2c_label1 )   // определение номера очередного шага.
  {

    default: i2c_label1 = 0 ;
    case i0 :
 	ax = timer1;
 	while(IBSR_BB == 1)
 	{
 	  ICCR_EN = 0;
 	  ICCR_EN = 1;
    if( (u)((w)(timer1 - ax)) >= _MkSec(100) ) goto stop;
  }

       IDAR =  ( c_addr | _WR_i2c )  ;

       IBCR = 0x10;

       i2c_label1++ ;
      if ( c_addr == _Adr_M41T56 )  i2c_label1++ ;

       while (IBCR_INT == 0) ;

       break;

    case i1 :


       if ( IBSR_LRB == 1 )
       {
         goto stop ;
       }

       IDAR = (b)( addr >> 8)  ;

       IBCR = 0x10;

        i2c_label1++ ;

       while (IBCR_INT == 0) ;

        break;

    case i2 :

       if ( IBSR_LRB == 1 ) goto stop ;

       IDAR = (b)addr   ;

       IBCR = 0x10;

       i2c_label1++ ;
       while (IBCR_INT == 0) ;
      break;

    case i3 :
     if ( IBSR_LRB == 1 ) goto stop ;

     IDAR = data ;

     IBCR = 0x10;

     i2c_label1++ ;

     while (IBCR_INT == 0) ;
     break;

    case i4 :

     IBCR = 0;

     return 0 ;   //  код того, что работа c i2c завершена.
  }
     return 4 ;   //  код того, что работа c i2c не завершена.

  stop:

     IBCR = 0;
     return 1 ;   //  код того, что произошел сбой.
}
*/


