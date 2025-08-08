#ifndef _f_zapoln_h
#define _f_zapoln_h

#define mInit_Fzapoln()   PPG_init( 2, 2, 0 );                                \
                          PPG_set( 2, _FzapolnShort_Low, _FzapolnShort_High );\
                          PPG_init( 3, 2, 0 );                                \
                          PPG_set( 3, _FzapolnShort_Low, _FzapolnShort_High )

#define mFzapoln1_start() PPG_start( 2, 1 )
#define mFzapoln1_stop()  PPG_stop( 2, 0 )

#define mFzapoln2_start() PPG_start( 3, 1 )
#define mFzapoln2_stop()  PPG_stop( 3, 0 )

#define  mSet_Fzapoln1( Low, High ) PPG_set( 2, Low, High )
#define  mSet_Fzapoln2( Low, High ) PPG_set( 3, Low, High )

#define  mSet_Fzapoln( Low, High )  mSet_Fzapoln1( Low, High )

#endif
