//Программ_ для работ_ с watchdog таймером
#include "watchdog.h"
static word WD_trg;

//Инициализация
void watchdog_init( word wd_time )
{
//   lword  wdK_mul;
   byte *res_cause;
   byte bh;
//   wdK_mul = (((lw)wd_time*1000000ul)/_tik_ns) ;
   //Определяем был и сброс по watchdog

  if ( wd_time != 0 )
  {
    res_cause = (b*)0x3d500; //По этому адресу лежит содержимое регистра RSRR
    bh = *res_cause;
    if ((bh & 0x20) != 0 )
    {
      _SetMsg_WatchDog( _Msg_WDT ); // конкретный тип сообщения (авария, предупреждение или служебное)
    }                                // задается в "include.h"
  // else
   //{
        //В зависимости от заданного значения времени пересброса задаем значения WT1 и WT0

        if (wd_time < 14)
        {
                RSRR = 0;
        }
        else if (wd_time < 65)
        {
                RSRR = 1;
        }
        else if (wd_time < 265)
        {
                RSRR = 2;
        }
        else
        {
                RSRR = 3;
        }

        WPR = 0xA5;
        WD_trg = 0xA5;
   //}
  }

  return ;
}

        //  Для обхода теста ОЗУ и ускорения загрузки после сброса:
        // проверяем был ли это сброс по Watchdog или это обычное включение.
word watchdog_reset_test( void )
{
//   lword  wdK_mul;
   byte *res_cause;
   byte bh;
//   wdK_mul = (((lw)wd_time*1000000ul)/_tik_ns) ;
   //Определяем был и сброс по watchdog

   if ( _r.WD_time == 0 )   return 0 ;

   res_cause = (b*)0x3d500; //По этому адресу лежит содержимое регистра RSRR
   bh = *res_cause;
   if ((bh & 0x20) != 0 )   return 1 ;
   else                     return 0 ;
}


//Попременно в течении меняем содержимое регистра WPR c А5 на 5А.
void watchdog_reset( void )
{
  //if( ( _RegMsg_WatchDog & _Msg_WDT ) == (lw)r0 )
  //{
    if ( WD_trg == 0xA5)
    {
        WD_trg = 0x5A;
    }
    else
    {
        WD_trg = 0xA5;
    }
    WPR = WD_trg;
  //}
}
