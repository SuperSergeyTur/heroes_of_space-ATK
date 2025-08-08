#ifndef _epa_drv_h
#define _epa_drv_h
//---------------

/*  Для Input CAPTURE  */

        // Настройка i-того канала EPA для приема синхронизации.
word init_syn_epa( word channel )  ;

        /*   Привязка синхронизации к ЕПА.  */
#define   _synch_epa_con     _ICS0
#define   _synch_epa_time    IPCP0

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
//---------------
#endif
