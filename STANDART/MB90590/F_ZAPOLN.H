#ifndef _f_zapoln_h
#define _f_zapoln_h

#define  mInit_Fzapoln()  PPG_init( 2, 4, 0 );  \
                    PPG_set( 2, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 3, 4, 0 ); \
                    PPG_set( 3, _FzapolnShort_Low, _FzapolnShort_High )

#define  mSet_Fzapoln1( Low, High ) PPG_set( 2, Low, High )
#define  mSet_Fzapoln2( Low, High ) PPG_set( 3, Low, High )

#define  mFzapoln1_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 2, 3 );} else { PDR5_P52 = 1;}
#define  mFzapoln2_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 3, 3 );} else { PDR5_P53 = 1;}


#define  mFzapoln1_stop()  if (_r.Cfg._.Fzapoln) { PPG_stop( 2, 0 );} else { PDR5_P52 = 0;}
#define  mFzapoln2_stop()  if (_r.Cfg._.Fzapoln) { PPG_stop( 3, 0 );} else { PDR5_P53 = 0;}

#define  mSet_Fzapoln( Low, High )  mSet_Fzapoln1( Low, High )
#define  mFzapoln_start()           mFzapoln1_start()
#define  mFzapoln_stop()            mFzapoln1_stop()

           // частотное заполн. для встроенного тормоза КТУ
#define  mInit_Fzapoln3()  PPG_init( 5, 4, 0 ) ; \
                    PPG_set( 5, _FzapolnShort_Low, _FzapolnShort_High )
#define  mSet_Fzapoln3( Low, High ) PPG_set( 5, Low, High )
#define  mFzapoln3_start()   PPG_start( 5, 0 )
#define  mFzapoln3_stop()    PPG_stop( 5, 0 )

           // частотное заполн. для встроенного возб.КТЭ
          // оно использует тот же выход, что и Po0_c._.n4, но
          // при инициализации PPG он преключается на PPG, но при
          // остановке PPG он будет опять слушаться Po0_c._.n4.
#define  mInit_Fzapoln4()  PPG_init( 1, 4, 0 ) ; \
                    PPG_set( 1, _V_FzapolnShort_Low, _V_FzapolnShort_High )
#define  mSet_Fzapoln4( Low, High ) PPG_set( 1, Low, High )
#define  mFzapoln4_start()   if (_r.Cfg2._.FzapolnV) { PPG_start( 1, 3 );}   else { PDR5_P51 = 1;}
#define  mFzapoln4_stop()    if (_r.Cfg2._.FzapolnV) { PPG_stop( 1, 0 );} else { PDR5_P51 = 0;}

#define  mFzapoln_strob_set( data ) PDR5_P53 = data



#define  mInit_PPG_SUBV()            PPG_init( 3, 4, 0 )
#define  mSet_PPG_SUBV( Low, High )  PPG_set( 3, Low, High )
#define  mPPG_SUBV_start()           PPG_start( 3, 3 )
#define  mPPG_SUBV_stop( lev )       PPG_stop( 3, lev )

#endif
