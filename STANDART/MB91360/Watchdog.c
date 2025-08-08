//��������_ ��� �����_ � watchdog ��������
#include "watchdog.h"
static word WD_trg;

//�������������
void watchdog_init( word wd_time )
{
//   lword  wdK_mul;
   byte *res_cause;
   byte bh;
//   wdK_mul = (((lw)wd_time*1000000ul)/_tik_ns) ;
   //���������� ��� � ����� �� watchdog

  if ( wd_time != 0 )
  {
    res_cause = (b*)0x3d500; //�� ����� ������ ����� ���������� �������� RSRR
    bh = *res_cause;
    if ((bh & 0x20) != 0 )
    {
      _SetMsg_WatchDog( _Msg_WDT ); // ���������� ��� ��������� (������, �������������� ��� ���������)
    }                                // �������� � "include.h"
  // else
   //{
        //� ����������� �� ��������� �������� ������� ���������� ������ �������� WT1 � WT0

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

        //  ��� ������ ����� ��� � ��������� �������� ����� ������:
        // ��������� ��� �� ��� ����� �� Watchdog ��� ��� ������� ���������.
word watchdog_reset_test( void )
{
//   lword  wdK_mul;
   byte *res_cause;
   byte bh;
//   wdK_mul = (((lw)wd_time*1000000ul)/_tik_ns) ;
   //���������� ��� � ����� �� watchdog

   if ( _r.WD_time == 0 )   return 0 ;

   res_cause = (b*)0x3d500; //�� ����� ������ ����� ���������� �������� RSRR
   bh = *res_cause;
   if ((bh & 0x20) != 0 )   return 1 ;
   else                     return 0 ;
}


//���������� � ������� ������ ���������� �������� WPR c �5 �� 5�.
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
