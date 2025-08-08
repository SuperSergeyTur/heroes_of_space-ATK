#ifndef can_drv_h
#define can_drv_h

  //  Базовая структура CAN-объекта сообщения для CAN-протокола.
struct canMSG_hw {
        unsigned long int id ;
        struct
        {
           //byte dir ;
           byte dlen ;
        } cfg ;
        unsigned char data[8];
} ;

     // Блок данных для i-того CAN-порта.
struct CAN_drv_data
{
 byte Error_receive;
 byte Avar;
 byte Error_send ;
 word time_out_send14 , time_out_send13 ;
 byte Can_reInit ;
 byte Can_stop ;
};

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _MAIN_INCLUDE

word  gSegment ;
     // Блок данных для i-того CAN-порта.
struct CAN_drv_data   can_dd[ _Num_CAN_Ports] ;

#else
extern word  gSegment ;
extern struct CAN_drv_data   can_dd[ _Num_CAN_Ports] ;
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

//#########################################
#ifdef _PCL841_WIN
//#########################################

#define  Timer1_Ovr ((w)GetTickCount())

    //         Макрос перевода секунд ('time') в дискреты переполнений таймера.
    //  Величина 'time', задаваемая ему, не должна выходить за сетку
    //                   "0.1сек ... 60.0сек".

  #define  _Sec( time )  ( (d)(time) * (d)1000 )

#include "841_win.h"

//#########################################
#else
//#########################################

#define  Timer1_Ovr ((w)biostime(0,0))

    //         Макрос перевода секунд ('time') в дискреты переполнений таймера.
    //  Величина 'time', задаваемая ему, не должна выходить за сетку
    //                   "0.1сек ... 60.0мин".

  #define  _Sec( time )  ( (d)(time) * (d)18.2 )

#include "841_dos.h"


void  Sleep ( short time ) ;
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

//#########################################
#endif
//#########################################
//----------------------------------
#endif
