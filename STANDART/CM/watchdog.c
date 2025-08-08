#include "lpc177x_8x_wwdt.c"
//#include "lpc177x_8x_wwdt.h"
#include "watchdog.h"

void watchdog_init(word wd_time)
{
    //�������� ������� ������
    if (WWDT_GetStatus(WWDT_TIMEOUT_FLAG))
    {
        _SetMsg_WatchDog( _Msg_WDT ); // ���������� ��� ��������� (������, �������������� ��� ���������)
                                        // �������� � "include.h"
        WWDT_ClrTimeOutFlag();
    }
    //������������� WD �������
    WWDT_Init(wd_time*1000);

	WWDT_Enable(ENABLE);

	WWDT_SetMode(WWDT_RESET_MODE, ENABLE);

    WWDT_Start(wd_time*1000);

}

void watchdog_reset(void)
{
	WWDT_Feed();
}
