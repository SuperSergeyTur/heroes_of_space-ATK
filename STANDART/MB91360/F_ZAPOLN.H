#ifndef _f_zapoln_h
#define _f_zapoln_h

  // Формируем частотные заполнения в зависимости от количества СИФУ :
//---------------
#ifdef    _SIFU2_
//---------------
#define  mInit_Fzapoln()  PPG_init( 0, 2, 0 ) ; \
                    PPG_set( 0, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 1, 2, 0 ) ; \
                    PPG_set( 1, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 2, 2, 0 ) ; \
                    PPG_set( 2, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 3, 2, 0 ) ; \
                    PPG_set( 3, _FzapolnShort_Low, _FzapolnShort_High )
//---
// 01.04.2016 - В 12-пульсных КТЭ , при отключении Ведущего моста и самостоятельной работе Ведомого моста
//              всё равно работает СИФУ1 с переинициализированным Заполнением Ведущего , подающее ИУ на Ведомый мост .
// Если Ведущий мост не отключен , запускаем Заполнение Ведущего , а если отключен - запускаем Ведомого :
#define  mFzapoln1_start()  if (_r.Cfg._.Fzapoln) { if ( S.flg._.VneshZp == 0 ) PPG_start( 0,1 ); else PPG_start( 2,1 );} \
                                             else { if ( S.flg._.VneshZp == 0 ) PDRO_PDO0 = 1   ; else PDRO_PDO2 = 1; }
#define  mFzapoln2_start()  if (_r.Cfg._.Fzapoln) { if ( S.flg._.VneshZp == 0 ) PPG_start( 1,1 ); else PPG_start( 3,1 );} \
                                             else { if ( S.flg._.VneshZp == 0 ) PDRO_PDO1 = 1   ; else PDRO_PDO3 = 1; }
//---
// Если Ведущий мост не отключен , отключаем Заполнение Ведущего , а если отключен - отключаем Ведомого :
#define  mFzapoln1_stop()   if ( S.flg._.VneshZp == 0 ) PPG_stop( 0, 0 ) ; else PPG_stop( 2, 0 )
#define  mFzapoln2_stop()   if ( S.flg._.VneshZp == 0 ) PPG_stop( 1, 0 ) ; else PPG_stop( 3, 0 )
//---
#define  mSet_Fzapoln3( Low, High ) PPG_set( 2, Low, High )
#define  mSet_Fzapoln4( Low, High ) PPG_set( 3, Low, High )
//---
#define  mFzapoln3_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 2,1 );} else { PDRO_PDO2 = 1;}
#define  mFzapoln4_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 3,1 );} else { PDRO_PDO3 = 1;}
//---
#define  mFzapoln3_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 2, 0 )//;}else { PDRO_PDO2 = 0;}
#define  mFzapoln4_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 3, 0 )//;}else { PDRO_PDO3 = 0;}
//---------------
#else
//---------------
#define  mInit_Fzapoln()  PPG_init( 0, 2, 0 ) ; \
                    PPG_set( 0, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 1, 2, 0 ) ; \
                    PPG_set( 1, _FzapolnShort_Low, _FzapolnShort_High )
//---
#define  mFzapoln1_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 0,1 );} else { PDRO_PDO0 = 1;}
#define  mFzapoln2_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 1,1 );} else { PDRO_PDO1 = 1;}
//---
#define  mFzapoln1_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 0, 0 )//;}else { PDRO_PDO0 = 0;}
#define  mFzapoln2_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 1, 0 )//;}else { PDRO_PDO1 = 0;}
//---------------
#endif
//---------------

#define  mSet_Fzapoln1( Low, High ) PPG_set( 0, Low, High )
#define  mSet_Fzapoln2( Low, High ) PPG_set( 1, Low, High )

#define  mFzapoln_trg()     PCNH0_STGR = 1; \
                            PCNH1_STGR = 1
                         /*  PPG_trg( 0 );\
                           PPG_trg( 1 )*/

#define  mSet_Fzapoln( Low, High )  mSet_Fzapoln1( Low, High )
#define  mFzapoln_start()           mFzapoln1_start()
#define  mFzapoln_stop()            mFzapoln1_stop()

#define  mFzapoln_strob_set( data ) PDRO_PDO1 = data

//---------------
// Частотное заполнение для встроенного возб.КТЭ - PPG5 FG
#ifdef   _Vozb_KTE
#define  mInit_Fzapoln4()  PPG_init( 5, 2, 0 ) ; \
                  PPG_set( 5, _V_FzapolnShort_Low, _V_FzapolnShort_High )
#define  mSet_Fzapoln4( Low, High ) PPG_set( 5, Low, High )
#define  mFzapoln4_start()     if (_r.Cfg2._.FzapolnV) {   PPG_start(5, 0 )  ;} else { PDRO_PDO5 = 1;}
#define  mFzapoln4_stop()   /* if (_r.Cfg2._.FzapolnV) {*/ PPG_stop( 5, 0 )//;} else { PDRO_PDO5 = 0;}

#define  mFzapoln_trgv()     PCNH5_STGR = 1; \

#endif
//---------------

#define  mInit_PPG_SUBV()            PPG_init( 2, 2, 0 )		// PPG_init( 2, 4, 0 )
#define  mSet_PPG_SUBV( Low, High )  PPG_set( 2, Low, High )
#define  mPPG_SUBV_start()           PPG_start( 2, 3 )
#define  mPPG_SUBV_stop( lev )       PPG_stop( 2, lev )

#endif
