#ifndef _f_zapoln_h
#define _f_zapoln_h

#define  mInit_Fzapoln() PPG_init( 0, 4, 1 ) ; \
                    PPG_set( 0, _FzapolnShort_Low, _FzapolnShort_High )

#define  mSet_Fzapoln( Low, High ) PPG_set( 0, Low, High )

#define  mFzapoln_start()  PPG_start( 0,1 )

#define  mFzapoln_stop()   PPG_stop( 0, 1 )

#endif
