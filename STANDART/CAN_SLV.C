
          //   ƒл€ разрешени€ регистровых static переменых,
          // чего в TurboC нельз€, а в 196-м можно.
//#define   _can_MCS_196
//--------------------------

#include "can_obj.c"
#include "can_drv.c"
#include "slavedrv.c"

#ifdef _Micro_Master
  #include "micrmast.c"
#endif

//ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ

/*
word canReceiveMonitor( byte port )
{
    // **************** ѕ – » ≈ ћ данных  ***********

           //  ќбработаны ли ранее считанные данные? ≈сли нет, то
           // не считываем буфер CAN: пока в CAN прийдут новые данные
           // может обработаютс€ и эти - и ничего не потер€ем.
     if ( canNewReceiveSlv == 0 )
     {
       if ( canReceive_196( 0 , &rmsg ) == 1 )
       {
         canNewReceiveSlv = 1 ; // признак того, что по€вились новые данные.
         return 1 ; // прин€ты данные дл€ 'slave'.
       }
     }
  return 0 ;
} */


