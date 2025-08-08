//Программа для работ_ с watchdog таймером
#include "watchdog.h"

//Инициализация
void watchdog_init( word wd_time )
{
    byte bx;

  if ( wd_time != 0 )
  {
    bx = WDTC;
    if ( ((bx & 0xd0) == 0) && ((bx & 0x20) != 0) )
    {
      _SetMsg_WatchDog( _Msg_WDT ); // конкретный тип сообщения (авария, предупреждение или служебное)
    }                               // задается в "include.h"
    //else
    //{
        //В зависимости от заданного значения времени пересброса задаем значения WT1 и WT0
      /*  if (wd_time <= 2) Убрали т.к. в нем нет смысла
        {
                WDTC = 0x00; //время срабатывания около 2 мсек
        }
        else*/ if ( wd_time <= 11 )
        {
                WDTC = 0x01; //время срабатывания около 11 мсек
        }
        else if ( wd_time <= 54 )
        {
                WDTC = 0x02; //время срабатывания около 54 мсек
        }
        else
        {
                WDTC = 0x03; //время срабатывания около 458 мсек
        }
    //}
  }

  return ;
}

        //  Для обхода теста ОЗУ и ускорения загрузки после сброса:
        // проверяем был ли это сброс по Watchdog или это обычное включение.
word watchdog_reset_test( void )
{
    byte bx;

    if ( _r.WD_time == 0 )  return 0 ;

    bx = WDTC;
    if ( ((bx & 0xd0) == 0) && ((bx & 0x20) != 0) )   return 1 ;
    else                                              return 0 ;
}

//Сбрасываем таймер сторожевой собаки
void watchdog_reset( void )
{
   //if( ( _RegMsg_WatchDog & _Msg_WDT ) == (lw)r0 )
   //{
     WDTC_WTE = 0;
   //}
}
