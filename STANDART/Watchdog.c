//��������� ��� �����_ � watchdog ��������
#include "watchdog.h"

//�������������
void watchdog_init( word wd_time )
{
    byte bx;

  if ( wd_time != 0 )
  {
    bx = WDTC;
    if ( ((bx & 0xd0) == 0) && ((bx & 0x20) != 0) )
    {
      _SetMsg_WatchDog( _Msg_WDT ); // ���������� ��� ��������� (������, �������������� ��� ���������)
    }                               // �������� � "include.h"
    //else
    //{
        //� ����������� �� ��������� �������� ������� ���������� ������ �������� WT1 � WT0
      /*  if (wd_time <= 2) ������ �.�. � ��� ��� ������
        {
                WDTC = 0x00; //����� ������������ ����� 2 ����
        }
        else*/ if ( wd_time <= 11 )
        {
                WDTC = 0x01; //����� ������������ ����� 11 ����
        }
        else if ( wd_time <= 54 )
        {
                WDTC = 0x02; //����� ������������ ����� 54 ����
        }
        else
        {
                WDTC = 0x03; //����� ������������ ����� 458 ����
        }
    //}
  }

  return ;
}

        //  ��� ������ ����� ��� � ��������� �������� ����� ������:
        // ��������� ��� �� ��� ����� �� Watchdog ��� ��� ������� ���������.
word watchdog_reset_test( void )
{
    byte bx;

    if ( _r.WD_time == 0 )  return 0 ;

    bx = WDTC;
    if ( ((bx & 0xd0) == 0) && ((bx & 0x20) != 0) )   return 1 ;
    else                                              return 0 ;
}

//���������� ������ ���������� ������
void watchdog_reset( void )
{
   //if( ( _RegMsg_WatchDog & _Msg_WDT ) == (lw)r0 )
   //{
     WDTC_WTE = 0;
   //}
}
