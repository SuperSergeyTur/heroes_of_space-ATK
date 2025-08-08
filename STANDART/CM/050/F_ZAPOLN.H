#ifndef _f_zapoln_h
#define _f_zapoln_h

#define mInit_Fzapoln()   PPG_init( 2, 2, 0 );                                \
                          PPG_set( 2, _FzapolnShort_Low, _FzapolnShort_High );\
                          PPG_init( 3, 2, 0 );                                \
                          PPG_set( 3, _FzapolnShort_Low, _FzapolnShort_High )

#define mFzapoln1_start() PPG_start( 2, 1 )
#define mFzapoln1_stop()  PPG_stop( 2, 0 )
#endif
