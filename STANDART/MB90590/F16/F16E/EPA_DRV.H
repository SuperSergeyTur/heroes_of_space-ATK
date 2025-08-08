#ifndef _epa_drv_h
#define _epa_drv_h
//---------------

/*  Для Input CAPTURE  */

        // Настройка i-того канала EPA для приема синхронизации.
word init_syn_epa( word channel )  ;

      //   Оперативное изменение приоритетов compare-EPA.
#define  mSet_sifu_epa_priority( channel, priority )                      \
{                                                                         \
  if(       channel == _OCS0  ||  channel == _OCS1 )   ICR07 = priority ; \
  else if ( channel == _OCS2  ||  channel == _OCS3 )   ICR08 = priority ; \
  else if ( channel == _OCS4  ||  channel == _OCS5 )   ICR09 = priority ; \
}


        /*   Привязка синхронизации к ЕПА.  */
#define   _synch_epa_con     _ICS5
#define   _synch_epa_time    IPCP5
#define   _synch2_epa_con    _ICS0
#define   _synch2_epa_time   IPCP0
#define   _synch3_epa_con    _ICS1
#define   _synch3_epa_time   IPCP1

#define   GUa_epa_con    _ICS0
#define   GUa_epa_time   IPCP0

#define   CUa_epa_con    _ICS1
#define   CUa_epa_time   IPCP1

        /*   Привязка сельсинов к ЕПА.  */
#define   _selsin0_epa_con     _ICS2
#define   _selsin0_epa_time    IPCP2

#define   _selsin1_epa_con     _ICS1
#define   _selsin1_epa_time    IPCP1

    //  Перечень входных каналов EPA.
#define _ICS0 ( 0x0 )
#define _ICS1 ( 0x1 )
#define _ICS2 ( 0x2 )
#define _ICS3 ( 0x3 )
#define _ICS4 ( 0x4 )
#define _ICS5 ( 0x5 )

// по заднему фронту
#define _CAP0_NEG_EDGE ( 0x02 )
#define _CAP1_NEG_EDGE ( 0x08 )
#define _CAP2_NEG_EDGE ( 0x02 )
#define _CAP3_NEG_EDGE ( 0x08 )
#define _CAP4_NEG_EDGE ( 0x02 )
#define _CAP5_NEG_EDGE ( 0x08 )

// по переднему фронту
#define _CAP0_POS_EDGE ( 0x01 )
#define _CAP1_POS_EDGE ( 0x04 )
#define _CAP2_POS_EDGE ( 0x01 )
#define _CAP3_POS_EDGE ( 0x04 )
#define _CAP4_POS_EDGE ( 0x01 )
#define _CAP5_POS_EDGE ( 0x04 )

// по обоим фронтам
#define _CAP0_BOTH_EDGE ( 0x03 )
#define _CAP1_BOTH_EDGE ( 0x0C )
#define _CAP2_BOTH_EDGE ( 0x03 )
#define _CAP3_BOTH_EDGE ( 0x0C )
#define _CAP4_BOTH_EDGE ( 0x03 )
#define _CAP5_BOTH_EDGE ( 0x0C )

      //   Разрешение прерывания по ЕПА.
void ei_syn_epa( word channel ) ;
           // Сброс запроса прерывания.
void Syn_int_drv( word channel ) ; //, word code ) ;

        // приоритет ЕПА - минимальный возможный.
#define _ICS01_PRIORITY   6
#define _ICS23_PRIORITY   6
#define _ICS45_PRIORITY   6

//---------------
/*  Для Output COMPARE  */

      //   Настройка заданного канала compare-EPA под CИФУ.
word init_sifu_epa( word channel ) ;
           // Сброс запроса прерывания.
void Sifu_int_drv( word channel ) ; //, word code ) ;

    //  Перечень выходных каналов EPA.
#define _OCS0 ( 0x0 )
#define _OCS1 ( 0x1 )
#define _OCS2 ( 0x2 )
#define _OCS3 ( 0x3 )
#define _OCS4 ( 0x4 )
#define _OCS5 ( 0x5 )

        // приоритет ЕПА - минимальный возможный.
#define _OCS01_PRIORITY   6
#define _OCS23_PRIORITY   6
#define _OCS45_PRIORITY   6

//---------------
#endif
