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
#define  mFzapoln1_start()  if (_r.Cfg._.Fzapoln) { if ( S.flg._.VneshZp == 0 ) PPG_start( 0,1 );        else PPG_start( 2,1 );} \
                                             else { if ( S.flg._.VneshZp == 0 ) LPC_GPIO1->SET = (1<<3); else LPC_GPIO1->SET = (1<<25);}
#define  mFzapoln2_start()  if (_r.Cfg._.Fzapoln) { if ( S.flg._.VneshZp == 0 ) PPG_start( 1,1 );        else PPG_start( 3,1 );} \
                                             else { if ( S.flg._.VneshZp == 0 ) LPC_GPIO1->SET = (1<<5); else LPC_GPIO1->SET = (1<<28);}
//---
// Если Ведущий мост не отключен , отключаем Заполнение Ведущего , а если отключен - отключаем Ведомого :
#define  mFzapoln1_stop()   if ( S.flg._.VneshZp == 0 ) PPG_stop( 0, 0 ) ; else PPG_stop( 2, 0 )
#define  mFzapoln2_stop()   if ( S.flg._.VneshZp == 0 ) PPG_stop( 1, 0 ) ; else PPG_stop( 3, 0 )
//---
#define  mSet_Fzapoln3( Low, High ) PPG_set( 2, Low, High )
#define  mSet_Fzapoln4( Low, High ) PPG_set( 3, Low, High )
//---
#define  mFzapoln3_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 2,1 );} else { LPC_GPIO1->SET = (1<<25);}
#define  mFzapoln4_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 3,1 );} else { LPC_GPIO1->SET = (1<<28);}
//---
#define  mFzapoln3_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 2, 0 )//;}else { LPC_GPIO1->CLR = (1<<25);}
#define  mFzapoln4_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 3, 0 )//;}else { LPC_GPIO1->CLR = (1<<28);}
//---------------
#else
//---------------
#define  mInit_Fzapoln()  PPG_init( 0, 2, 0 ) ; \
                    PPG_set( 0, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 1, 2, 0 ) ; \
                    PPG_set( 1, _FzapolnShort_Low, _FzapolnShort_High )
//---
#define  mFzapoln1_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 0,1 );} else { LPC_GPIO1->SET = (1<<3);}
#define  mFzapoln2_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 1,1 );} else { LPC_GPIO1->SET = (1<<5);}
//---
#define  mFzapoln1_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 0, 0 )//;}else { LPC_GPIO1->CLR = (1<<3);}
#define  mFzapoln2_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 1, 0 )//;}else { LPC_GPIO1->CLR = (1<<5);}
//---------------
#endif
//---------------

#define  mSet_Fzapoln1( Low, High ) PPG_set( 0, Low, High )
#define  mSet_Fzapoln2( Low, High ) PPG_set( 1, Low, High )

#define  mFzapoln_trg()  //   PCNH0_STGR = 1; \  TDS как здесь нужно сделать - не знаю, будем проверять
                         //   PCNH1_STGR = 1
                         /*  PPG_trg( 0 );\
                           PPG_trg( 1 )*/
#ifndef _BTE_ForceGroup //!defined(_BTE_ForceGroup) && defined(_Force_IU_)
   #define  mSet_Fzapoln( Low, High )  mSet_Fzapoln1( Low, High )
#else
   #define  mSet_Fzapoln( Low, High )  mSet_Fzapoln1( Low, High ); \
                                       mSet_Fzapoln2( Low, High )
#endif

#define  mFzapoln_start()           mFzapoln1_start()
#define  mFzapoln_stop()            mFzapoln1_stop()

#define  mFzapoln_strob_set( data )  if (data == 0) { LPC_GPIO1->CLR = (1<<5);} else { LPC_GPIO1->SET = (1<<5);}

//---------------
#ifdef   _Vozb_KTE
//---------------
  #ifdef _VOZB_SHIM_  // ШИМ Возбудитель
        #define  mInit_Fzapoln4()
        #define  mSet_Fzapoln4( Low, High )
        #define  mFzapoln4_start()
        #define  mFzapoln4_stop()
  #else
    #ifdef  _SIFUV_1Faza  // Частотное заполнение для встроенного однофазного возб.КТЭ - PPG5 FG
        #define  mInit_Fzapoln4()  PPG_init( 5, 2, 0 ) ; \
                 PPG_set( 5, _V_FzapolnShort_Low, _V_FzapolnShort_High )
        #define  mSet_Fzapoln4( Low, High ) PPG_set( 5, Low, High )
        #define  mFzapoln4_start()     if (_r.Cfg2._.FzapolnV) {   PPG_start(5, 0 );  } else { _PPG5_IOPORT->SET = _PPG5_Msk; }
        #define  mFzapoln4_stop()    /*if (_r.Cfg2._.FzapolnV) {*/ PPG_stop( 5, 0 )//;} else { _PPG5_IOPORT->CLR = _PPG5_Msk; }
    #else                 // Частотное заполнение для встроенного трехфазного возб.КТЭ - PPG2 FG
        #define  mInit_Fzapoln4()  PPG_init( 2, 2, 0 ) ; \
                 PPG_set( 2, _V_FzapolnShort_Low, _V_FzapolnShort_High )
        #define  mSet_Fzapoln4( Low, High ) PPG_set( 2, Low, High )
        #define  mFzapoln4_start()     if (_r.Cfg2._.FzapolnV) {   PPG_start(2, 1 );  } else { _PPG5_IOPORT->SET = _PPG2_Msk; }
        #define  mFzapoln4_stop()    /*if (_r.Cfg2._.FzapolnV) {*/ PPG_stop( 2, 0 )//;} else { _PPG5_IOPORT->CLR = _PPG2_Msk; }
    #endif // _SIFUV_1Faza
  #endif
#define  mFzapoln_trgv()    // PCNH5_STGR = 1;  TDS как здесь нужно сделать - не знаю, будем проверять
//---------------
#endif // _Vozb_KTE
//---------------
#if defined(_CM3_) && ( defined(_SUBV_) || defined(_VOZB_SHIM_) )
   #define  mInit_PPG_SUBV()            PPG_init( 2, 2, 0 )		// PPG_init( 2, 4, 0 )
   #define  mSet_PPG_SUBV( Low, High )  PPG_set( 2, Low, High )
   #define  mPPG_SUBV_start()           PPG_start( 2, 3 )
   #define  mPPG_SUBV_stop( lev )       PPG_stop( 2, lev )
#endif

#endif
