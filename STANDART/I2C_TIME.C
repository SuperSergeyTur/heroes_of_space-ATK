//Программма для считывания времени из М41Т56
//Считывает 7 байт (секунды, минуты, часы, день недели,
// день месяца, месяц, год) в структуру с_time в двоично-десятичной системе и
// в d_time в обычной.
//Возвращает: 4 - в ходе работы, 1- при аварии, 0 - по окончании работы
word  Read_i2c_time( void )
{
  word ax, i;
  switch ( Time_label )
  {
    default:
    case 0:
            if ( Mon.i2c_busy == 1 ) return 4; //  Ждем пока освободится шина.
            Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.
            Time_label = 1;
            i2c_label = 0;

    case 1:
            //Считываем весь массив времени в с_time.b
            ax = xLoad_from_i2c ( 8 , _Adr_sec , (b*)&c_time.b[0]  ,_Adr_Clock_i2c) ;
            if ( ax != 4 )
            {
             Mon.i2c_busy = 0 ;
             if (ax == 0)
             {
              ax = 4; // показываем занятость программы.
              Time_label = 2;
             }
             else
             {
             Time_label = 0;
             }

            }
            break;
    case 2:
            //Преобразовываем - откидываем служебные биты
            c_time.b[0] &= 0x7f;
            c_time.b[1] &= 0x7f;
            c_time.b[2] &= 0x3f;
            c_time.b[3] &= 0x07;
            c_time.b[4] &= 0x3f;
            c_time.b[5] &= 0x1f;
            c_time.b[7] &= 0x3f;
            ax = 4;
            Time_label = 3;

            break;
    case 3:
            //Преобразовываем из двоично-десятичной системы
            //в обычную и складываем в d_time.
            for ( i=0; i < 7; ++i )
            {
              ax = c_time.b[i]>>4;
              ax*=10;
              d_time.b[i] = ax+(c_time.b[i]&0x0f);
            }
            ax = 0;
            Time_label = 0;
            break;
  }
  return ax ;
}

/*------------------------------------------------------------------*/
/*   Программа распечатки времени считанного из часов реального времени.
 */

void PrintTime ( struct I2C_time* ptr )
{
  register word  ax ;

           // распечатка дня, месяца, года.
  for ( ax = 4 ; ax != 7 ; ax++ )
  {       // десятки.
    m_ch = ptr->b[ax] >> 4 ;
    output_c( m_ch + 0x30 ) ;
          // единицы.
    m_ch = ptr->b[ax] & 0x0f ;
    output_c( m_ch + 0x30 ) ;
    output_c( '.' ) ;
  }
    // распечатка дня недели.
  output_s( Day[ptr->b[3]-1] ) ;

  output_s( "\r\n" ) ;

           // распечатка часов, минут, секунд.
  for ( ax = 2 ; (sw)ax >= 0 ; ax-- )
  {       // десятки.
    m_ch = ptr->b[ax] >> 4 ;
    output_c( m_ch + 0x30 ) ;
          // единицы.
    m_ch = ptr->b[ax] & 0x0f ;
    output_c( m_ch + 0x30 ) ;
    if( ax != 0 ) output_c( ':' ) ;
  }

  return ;
}
//--------------

void xOvr_Time_Schet(struct I2C_time* ptr)
{
  word ax;
  static byte read ;

    // раз в минуту обновляем время.
if ( read == 1 )
{
  ax = Read_i2c_time() ;
  if ( ax != 4 )
  {
    read = 0 ;
    if ( ax == 0 )  *ptr = c_time ;
  }
}
else  // пока считываем - блокируем наращивание времени.
{
  ax = Timer1_fSec/*Timer1_Ovr*/ - I2C_Time_Ovr; // 05.06.2012 12:59 заменил на fSec, чтобы синхронизация с часами
  if ( (u)ax >= _fSec(1) /*_Sec(1)*/)            // (т.е. выход на шину i2c) была действительно раз в минуту,
  {                                              // а не раз в минуту плюс через секунду после синхронизации
    //mUSEL_not() ;
    //I2C_Time_Ovr = Timer1_Ovr;
    I2C_Time_Ovr += _fSec(1) /*_Sec(1)*/; // выбираем накопившееся из-за блокировки запоздание.

    ++ptr->b[0];            // секунды
    ax =ptr->b[0] & 0x0f;
    if (ax >= 10  )         // десятки секунд
    {
      ptr->b[0] += 6; //  сразу обнуляем младшую тетраду и добавляем 1 к старшей
      if ((ptr->b[0] >>4) >= 6 )
      {
        ptr->b[0] = 0;
        ++ptr->b[1];             // минуты
        ax =ptr->b[1] & 0x0f;
        if ( ax >= 10 )
        {
            ptr->b[1] += 6;      // десятки минут
            if ((ptr->b[1] >>4) >= 6 )
            {
              ptr->b[1] = 0;
              ++ptr->b[2];       // часы
              ax =ptr->b[2] & 0x0f;
              if ( ax >= 10 )
              {
                ptr->b[2] += 6;  // десятки часов
                ax = (ptr->b[2] & 0x3f)>>4;
                if ( ax > 2 )
                {
                  ptr->b[2] = 0;
                }
                else ptr->b[2] &= 0xf0;
              }
            }
            else ptr->b[1] &= 0xf0;
        }        //  раз в минуту обновляем данные из часов I2C.
        Time_label = 0;
        read = 1 ;
        //while ( Read_i2c_time() == 4 )  ;
        //*ptr = c_time ;
      }
      else ptr->b[0] &= 0xf0;
    }
  }
}
  return ;

}

