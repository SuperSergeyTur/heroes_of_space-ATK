#ifndef _epa_drv_h
#define _epa_drv_h
//---------------

/*  Для Input CAPTURE  */

        // Настройка i-того канала EPA для приема синхронизации.
word init_syn_epa( word channel )  ;

      //   Оперативное изменение приоритетов compare-EPA.
#define  mSet_sifu_epa_priority( channel, priority )                      \
{                                                                         \
  if      ( channel == _OCS0  ||  channel == _OCS1 )   ICR27 = priority ; \
  else if ( channel == _OCS2  ||  channel == _OCS3 )   ICR29 = priority ; \
}


        /*   Привязка синхронизации к ЕПА.  */
#define   _synch_epa_con     _ICS0  // синхронизация от блока питания .
#define   _synch_epa_time    IPCP0
#define   _synch2_epa_con    _ICS1  // синхронизация от блока питания .
#define   _synch2_epa_time   IPCP1
#define   _synch3_epa_con    _ICS2  // синхронизация от блока питания .
#define   _synch3_epa_time   IPCP2

#define   GUa_epa_con    _ICS1
#define   GUa_epa_time   IPCP1

#define   CUa_epa_con    _ICS2
#define   CUa_epa_time   IPCP2

        /*   Привязка сельсинов к ЕПА.  */
#define   _selsin0_epa_con     _ICS1
#define   _selsin0_epa_time    IPCP1

#define   _selsin1_epa_con     _ICS2 // в SIFU.H привязка к синхр. от силы .
#define   _selsin1_epa_time    IPCP2

    //  Перечень входных каналов EPA.
#define _ICS0 ( 0x0 )
#define _ICS1 ( 0x1 )
#define _ICS2 ( 0x2 )
#define _ICS3 ( 0x3 )

// по заднему фронту
#define _CAP0_NEG_EDGE ( 0x02 )
#define _CAP1_NEG_EDGE ( 0x08 )
#define _CAP2_NEG_EDGE ( 0x02 )
#define _CAP3_NEG_EDGE ( 0x08 )

// по переднему фронту
#define _CAP0_POS_EDGE ( 0x01 )
#define _CAP1_POS_EDGE ( 0x04 )
#define _CAP2_POS_EDGE ( 0x01 )
#define _CAP3_POS_EDGE ( 0x04 )

// по обоим фронтам
#define _CAP0_BOTH_EDGE ( 0x03 )
#define _CAP1_BOTH_EDGE ( 0x0C )
#define _CAP2_BOTH_EDGE ( 0x03 )
#define _CAP3_BOTH_EDGE ( 0x0C )

      //   Разрешение прерывания по ЕПА.
void ei_syn_epa( word channel ) ;
           // Сброс запроса прерывания.
void Syn_int_drv( word channel ) ; //, word code ) ;

        // приоритет ЕПА - минимальный возможный.
#define _ICS01_PRIORITY  _OCS01_PRIORITY
#define _ICS23_PRIORITY  _OCS23_PRIORITY

//---------------
/*  Для Output COMPARE  */

      //   Настройка заданного канала compare-EPA под CИФУ.
word init_sifu_epa( word channel ) ;
word off_sifu_epa( word channel ) ;
           // Сброс запроса прерывания.
void Sifu_int_drv( word channel ) ; //, word code ) ;

    //  Перечень выходных каналов EPA.
#define _OCS0 ( 0x0 )
#define _OCS1 ( 0x1 )
#define _OCS2 ( 0x2 )
#define _OCS3 ( 0x3 )

        // приоритет ЕПА - минимальный возможный.
#define _OCS01_PRIORITY   30 //16  // 16 - Strongest level . 06.03.07 16:22 .
#define _OCS23_PRIORITY   30 //16  // 30 - Weak .

//---------------
#endif
