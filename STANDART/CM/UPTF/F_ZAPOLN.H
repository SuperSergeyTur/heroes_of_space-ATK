#ifndef _f_zapoln_h
#define _f_zapoln_h

  // Формируем частотные заполнения в зависимости от количества СИФУ :
#define  mInit_Fzapoln()  PPG_init( 0, 2, 0 ) ; \
                    PPG_set( 0, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 1, 2, 0 ) ; \
                    PPG_set( 1, _FzapolnShort_Low, _FzapolnShort_High ) ;\
                          PPG_init( 5, 2, 0 ) ; \
                    PPG_set( 5, _FzapolnShort_Low, _FzapolnShort_High )
//---
#define  mFzapoln1_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 0,1 );} else { LPC_GPIO1->SET = (1<<3);}
#define  mFzapoln2_start()  if (_r.Cfg._.Fzapoln) { PPG_start( 1,1 );} else { LPC_GPIO1->SET = (1<<5);}
//---
#define  mFzapoln1_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 0, 0 )//;}else { LPC_GPIO1->CLR = (1<<3);}
#define  mFzapoln2_stop()  /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 1, 0 )//;}else { LPC_GPIO1->CLR = (1<<5);}

#define  mSet_Fzapoln1( Low, High ) PPG_set( 0, Low, High )
#define  mSet_Fzapoln2( Low, High ) PPG_set( 1, Low, High )

#define  mFzapoln_trg()  //   PCNH0_STGR = 1; \  TDS как здесь нужно сделать - не знаю, будем проверять
                         //   PCNH1_STGR = 1
                         /*  PPG_trg( 0 );\
                           PPG_trg( 1 )*/

#define  mSet_Fzapoln( Low, High )  mSet_Fzapoln1( Low, High )
#define  mFzapoln_start()           mFzapoln1_start()
#define  mFzapoln_stop()            mFzapoln1_stop()

#define  mFzapoln_strob_set( data )  if (data == 0) { LPC_GPIO1->CLR = (1<<5);} else { LPC_GPIO1->SET = (1<<5);}

//---------------
// Частотное заполнение для шунтирующих тиристоров - PPG5 FG
#define  mInit_Fzapoln5()  PPG_init( 5, 2, 0 ) ; \
                  PPG_set( 5, _FzapolnShort_Low, _FzapolnShort_High )
#define  mSet_Fzapoln5( Low, High ) PPG_set( 5, Low, High )
#define  mFzapoln5_start()     if (_r.Cfg._.Fzapoln) {   PPG_start(5, 0 )  ;} else { _PPG5_IOPORT->SET = _PPG5_Msk; }
#define  mFzapoln5_stop()    /*if (_r.Cfg._.Fzapoln) {*/ PPG_stop( 5, 0 )//;} else { _PPG5_IOPORT->CLR = _PPG5_Msk; }
//---------------

// PPG1 - Сигнал форсировки ИУ роторного выпрямителя :
  #ifndef _LABOR_STEND
#define  mPPG1_forsir_set( data )    if ( data ) { LPC_GPIO1->SET = (1<<5);} else { PPG_stop( 1, 0 ) ;}
  #else // на стенде АТК на выходных каскадах форсировка ИУ наоборот :
#define  mPPG1_forsir_set( data )    if ( data ) { PPG_stop( 1, 0 ) ;} else { LPC_GPIO1->SET = (1<<5);}
  #endif

// PPG4 - Сигнал, передаваемый из АР2 в АР1, используемый для принудительной коммутации :
// Логическая "1" соответствует "1" , общая точка соответствует логическому "0" :
#define  mPPG4_set( data )           if ( data ) { LPC_GPIO2->SET = (1<<0);} else { PPG_stop( 4, 0 ) ;}

#endif
