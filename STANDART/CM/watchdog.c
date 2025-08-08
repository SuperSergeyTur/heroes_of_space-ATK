#include "lpc177x_8x_wwdt.c"
//#include "lpc177x_8x_wwdt.h"
#include "watchdog.h"

void watchdog_init(word wd_time)
{
    //Проверка причины сброса
    if (WWDT_GetStatus(WWDT_TIMEOUT_FLAG))
    {
        _SetMsg_WatchDog( _Msg_WDT ); // конкретный тип сообщения (авария, предупреждение или служебное)
                                        // задается в "include.h"
        WWDT_ClrTimeOutFlag();
    }
    //Инициализация WD таймера
    WWDT_Init(wd_time*1000);

	WWDT_Enable(ENABLE);

	WWDT_SetMode(WWDT_RESET_MODE, ENABLE);

    WWDT_Start(wd_time*1000);

}

void watchdog_reset(void)
{
	WWDT_Feed();
}
