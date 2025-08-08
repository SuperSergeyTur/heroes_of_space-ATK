#ifndef ppg_497
#define ppg_497

extern void  PPG_set( byte n, word low, word high ) ;
extern void  PPG_start( byte n, byte s );

  #define  _PPG_Low      _MkSec( 10 )  // длительность нулевого импульса в мкс

  #define  _PPG_High     _MkSec( 10 )  // длительность единичного импульса в мкс

  //#define  PPG_start( n )    PPGC##n |= 0xa0
//  #define  PPG_set(n,low, high)    PRLL##n = low-1;\
//                                   PRLH##n = high-1


#endif
