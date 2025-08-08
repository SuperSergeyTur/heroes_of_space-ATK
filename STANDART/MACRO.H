#ifndef _macro_h
#define _macro_h


/*                       М А К Р О С Ы  */

/*    ИСПОЛЬЗУЮТСЯ КАК АЛЬТЕРНАТИВА КОРОТКИМ, НО ЧАСТО ВЫЗЫВАЕМЫМ  */
/* ПОДПРОГРАММАМ ДЛЯ ПОВЫШЕНИЯ БЫСТРОДЕЙСТВИЯ ПРОГРАММЫ (в ущерб ее размеру).  */
/*--------------------------------------------------------------------  */


/*--------------------------------------------------------------------  */

    /*         Макрос перевода микросекунд ('time') в дискреты таймера.  */
    /*  Величина 'time', задаваемая ему, не должна выходить за сетку  */
    /*                   "0.0 ... 50.0"мсек.  */

  #define  _MkSec( time )  ((const w)( (d)(time)  / (d)_TimerDiscreta + (d)0.5 ))

    /*         Макрос перевода секунд ('time') в дискреты переполнений таймера.  */
    /*  Величина 'time', задаваемая ему, не должна выходить за сетку  */
    /*                   "0.1сек ... 60.0мин".  */

  #define  _Sec( time )  _MkSec( (d)(time) * (d)1000000. / (d)65536. )

    /*         Макрос перевода секунд ('time') в дискреты средних двух байт  */
    /*    полного четырехбайтного времени получаемого из "timer1 и Timer1_Ovr".  */
    /*  Величина 'time', задаваемая ему, не должна выходить за сетку  */
    /*                   "0.0005 ... 12.0"сек.  */

  #define  _fSec( time ) _MkSec( (d)(time) * (d)1000000. / (d)256. )

    /*         Макрос перевода секунд ('time') в дискреты-пульсы.  */
    /*  Величина 'time', задаваемая ему, не должна выходить за сетку  */
    /*                   "0.01 ... 215.0"сек.  */

  #define  _pSec( time ) _MkSec( (d)(time) * 1000000. / 3300. )

  #define  _Sec_kv   16 // 1 сек^2
/*--------------------------------------------------------------------  */

    /*      Макрос перевода градусов ('grd') в относительные дискреты угла.  */
    /*  Величина 'grd', задаваемая ему, не должна выходить за сетку 'double'.  */

  #define  _Grad( grd )    ((const sw)(const int) ( (d)_Ugol_180 / (d)180 * (d)(grd) ))

/*--------------------------------------------------------------------  */
#define  _r0   0

#ifdef   _Union_FR  // для FR старшее слово находится по младшему адресу

             /*  взять младшее слово от четырехбайтного  */
#define  Hw( lax )   ( *(w*)&(lax) )

             /*  взять старшее слово от четырехбайтного  */
#define  Lw( lax )   ( *( (w*)&(lax) + 1 ) )

#else
             /*  взять старшее слово от четырехбайтного  */
#define  Hw( lax )   ( *( (w*)&(lax) + 1 ) )

             /*  взять младшее слово от четырехбайтного  */
#define  Lw( lax )   ( *(w*)&(lax) )

#endif
         /*  взять старший байт от двухбайтного (через сдвиг - код оптимальней)  */
/*#define  Hb( ax )   ( *( (b*)&ax + 1 ) )  */

#define  Hb( ax )    ((b)( ax >> 8 ))

             /*  взять младший байт от двухбайтного  */
/*#define  Lb( ax )   ( *(b*)&ax )  */
#define  Lb( ax )    ((b)ax )

#define   r0    0

#define    _Case( al , ah )  ((w)( ah * 256 + al ))

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-  */

            /*   Зарегистрировать аварийное сообщение с
             * выделением самого первого сообщения.     */

// Регистров аварий развелось как собак нерезаных , поэтому первых аварий тоже может быть несколько .
// А при таком макросе выделения первой аварии зафиксируется первая авария только в вышестоящем регистре .
// Поэтому вместо этого макроса работает функция в MSG.C .
//#define   mSetF_AvarMsg( lax )   if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2 |                                \
//                                       Reg_AvarMsgFirst3| Reg_AvarMsgFirst_obj) == (lw)r0 )                  \
//                                       Reg_AvarMsgFirst = (lw)(lax) ;                                        \
//                                 else  Reg_AvarMsg |= (lw)(lax)

//#define   mSetF_AvarMsg2( lax )  if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2 |                                \
//                                       Reg_AvarMsgFirst3| Reg_AvarMsgFirst_obj) == (lw)r0 )                  \
//                                       Reg_AvarMsgFirst2 = (lw)(lax) ;                                       \
//                                else  Reg_AvarMsg2 |= (lw)(lax)

//#define   mSetF_AvarMsg3( lax )  if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2 |                                \
//                                       Reg_AvarMsgFirst3| Reg_AvarMsgFirst_obj) == (lw)r0 )                  \
//                                       Reg_AvarMsgFirst3 = (lw)(lax) ;                                       \
//                                 else  Reg_AvarMsg3 |= (lw)(lax)

           //   Пусть пока побудут и такие макросы, т.к. в СВТГ они используются специфически.

#define   mSetF_AvarMsg( lax )   if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2 | \
                                       Reg_AvarMsgFirst3 ) == (lw)r0 )        \
                                       Reg_AvarMsgFirst = (lw)(lax) ;         \
                                 else  Reg_AvarMsg |= (lw)(lax)

#define   mSetF_AvarMsg2( lax )  if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2 | \
                                       Reg_AvarMsgFirst3 ) == (lw)r0 )        \
                                       Reg_AvarMsgFirst2 = (lw)(lax) ;        \
                                 else  Reg_AvarMsg2 |= (lw)(lax)

#define   mSetF_AvarMsg3( lax )  if ( (Reg_AvarMsgFirst | Reg_AvarMsgFirst2 | \
                                       Reg_AvarMsgFirst3 ) == (lw)r0 )        \
                                       Reg_AvarMsgFirst3 = (lw)(lax) ;        \
                                 else  Reg_AvarMsg3 |= (lw)(lax)

            /* Зарегистрировать аварийное сообщение */
#define   mSet_AvarMsg( lax )      Reg_AvarMsg  |= (lax)
#define   mSet_AvarMsg2( lax )     Reg_AvarMsg2 |= (lax)
#define   mSet_AvarMsg3( lax )     Reg_AvarMsg3 |= (lax)

            /* Снять аварийное сообщение */
#define   mClr_AvarMsg( lax )      Reg_AvarMsg  &= ~(lax), Reg_AvarMsgFirst  &= ~(lax)
#define   mClr_AvarMsg2( lax )     Reg_AvarMsg2 &= ~(lax), Reg_AvarMsgFirst2 &= ~(lax)
#define   mClr_AvarMsg3( lax )     Reg_AvarMsg3 &= ~(lax), Reg_AvarMsgFirst3 &= ~(lax)
#define   mClr_AvarMsg_obj( lax )  Reg_AvarMsg_obj &= ~(lax), Reg_AvarMsgFirst_obj &= ~(lax)

      /*ДДДДДДДДДДДДДДД  */

            /* Зарегистрировать предупредительное сообщение */
#define   mSet_PreduprMsg( lax )   Reg_PreduprMsg  |= (lax)
#define   mSet_PreduprMsg2( lax )  Reg_PreduprMsg2 |= (lax)
#define   mSet_PreduprMsg3( lax )  Reg_PreduprMsg3 |= (lax)

            /* Снять предупредительное сообщение */
#define   mClr_PreduprMsg( lax )   Reg_PreduprMsg  &= ~(lax)
#define   mClr_PreduprMsg2( lax )  Reg_PreduprMsg2 &= ~(lax)
#define   mClr_PreduprMsg3( lax )  Reg_PreduprMsg3 &= ~(lax)
#define   mClr_PreduprMsg_obj( lax )  Reg_PreduprMsg_obj &= ~(lax)

      /*ДДДДДДДДДДДДДДД  */

            /* Зарегистрировать служебное сообщение */
#define   mSet_ServiceMsg( lax )   Reg_ServiceMsg  |= (lax)
#define   mSet_ServiceMsg2( lax )  Reg_ServiceMsg2 |= (lax)
#define   mSet_ServiceMsg3( lax )  Reg_ServiceMsg3 |= (lax)

            /* Снять служебное сообщение */
#define   mClr_ServiceMsg( lax )   Reg_ServiceMsg  &= ~(lax)
#define   mClr_ServiceMsg2( lax )  Reg_ServiceMsg2 &= ~(lax)
#define   mClr_ServiceMsg3( lax )  Reg_ServiceMsg3 &= ~(lax)
#define   mClr_ServiceMsg_obj( lax )  Reg_ServiceMsg_obj &= ~(lax)

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

/*              Уставки  номиналов .  */

/* СИФУ  */

  #ifdef  P_CH

  #define   PWM_f       0x1f33

//  #ifdef  MB91362

//  #define   _dDT          ( F_Mh*_r.DT_korr)-1

/*  #else

  #define   _dDT          ( F_Mh*23) -1

  #endif*/

  #define   _dt_Teplo     _Sec(1)

  #define   _dQ_min       25

  #define   _dQ_max       75

  #define   PWM_fl      ( (lw)PWM_f<<16 )+0xffff

  #define   _Id_Nom      ( 200u * _K_diskr)

  #define  _Is_Nom       ( 200u * _K_diskr)

  #define  _Is2_Nom       _Is_Nom*_Is_Nom

  #define  _Fwg_Nom      ( 4000 )

  #define  _dF_Nom       ( 82u )

  #define  _Umz_Nom      ( 400u* _K_diskr)

  #define  _Us_Nom       ( 307u* _K_diskr)

  #define  _Ud_Nom       ( 307u* _K_diskr)

  #define  _Kf_i_mg       _MkSec(5000)

  #define  _Ku_Nom_m      16u

  #define  _Ku_Nom_p      25u

  #define  _Ku_Nom_v      13u

  #define  _Rs_Nom        128
#ifndef _400Hz

  #define  _HzSin_Nom     0x80u

  #define  _HzSin_NomSq   0x4000u

  #define  _Hz_ind_max    200
#else

  #define  _HzSin_Nom     0x40u

  #define  _HzSin_NomSq   0x1000u

  #define  _Hz_ind_max    400

#endif

  #define  _Volt_Nom     1

  #define  _DAC_Max      390 //Выход DAC при котором у нас на выходе 10 В

  #define  _DAC_4mA      _DAC_Max/5 //Выход DAC при котором у нас на выходе 4 mA

  #define  _Grad_Cel     1
  #define  _Grad_Cel_k   0x2710u

  #define  _Reg_Nom       6400


  #else


#ifndef _ADC_12_
  #define  _K_diskr       1  // 10-ти разрядный АЦП - старый вариант Idnom = 200d Udnom = 400d .
#else
  #define  _K_diskr       4  // 12-ти разрядный АЦП - новый вариант Idnom = 800d Udnom = 1600d .
#endif

  #ifndef    _Id_Nom
    #define  _Id_Nom      ( 200u * _K_diskr )  // 10-ти разрядный АЦП - 200d , 12-ти разрядный АЦП - 800d .
  #endif

  #ifndef    _Id_Nom200
    #define  _Id_Nom200   ( 200u )  // Для нового ЗИРТ - 200 дискрет номинал , чтобы можно было задать 300 ном/с .
  #endif

  #ifndef    _Ig_Nom
    #define  _Ig_Nom      ( 200u * _K_diskr )  // 10-ти разрядный АЦП - 200d , 12-ти разрядный АЦП - 800d .
  #endif

#if defined(_BTE) || defined(_CCT)
  #ifndef    _Ud_Nom
    #define  _Ud_Nom      ( 200u * _K_diskr )  // 10-ти разрядный АЦП - 200d , 12-ти разрядный АЦП - 800d .
  #endif
#else
  #ifndef    _Ud_Nom
    #define  _Ud_Nom      ( 400u * _K_diskr )  // 10-ти разрядный АЦП - 400d , 12-ти разрядный АЦП - 1600d .
  #endif
#endif
  // Привязываем номинал ЭДС к номиналу исходной величины - напряжения :
  #define  _EDS_Nom     ( _Ud_Nom << _Skor_Shift )

  // Привязываем номинал скорости к номиналам исходных величин - напряжения и , соответственно , задания :
  #define  _Skor_Nom    ( _Ud_Nom << _Skor_Shift )

  #define  _1mA_Nom     ( 400u * _K_diskr / 20u )
  #define  _20mA_Nom    ( 400u * _K_diskr )

  // ВОЗБУДИТЕЛЬ - КТЭ.

  #ifndef    _Iv_Nom
    #define  _Iv_Nom    ( 200u * _K_diskr )  // 10-ти разрядный АЦП - 200d , 12-ти разрядный АЦП - 800d .
  #endif

  #define  _Fv_Nom    _Iv_Nom

  #define  _Mom_Nom     ( _Fv_Nom ) // Номинал момента привязан к потоку .

  #define  _Uf_Nom      ( 400u * _K_diskr )  // 10-ти разрядный АЦП - 400d , 12-ти разрядный АЦП - 1600d .

  // ВОЗБУДИТЕЛЬ - КТЭС, СВНТ.

  #ifndef    _Us_Nom
    #define  _Us_Nom      ( 400u * _K_diskr )
  #endif

  #ifndef    _Is_Nom

    #define  _Is_Nom      ( 200u * _K_diskr )
  #endif

  #ifndef    _Q_Nom
    #define  _Q_Nom       ( 400u )
  #endif

  #define  _Cos_Nom       ( 200u ) // * _K_diskr )  // 10-ти разрядный АЦП - 200d , 12-ти разрядный АЦП - 800d .

  #define  _Itr_Nom       ( 100u * _K_diskr )  // 10-ти разрядный АЦП - 100d , 12-ти разрядный АЦП - 400d .  // 200 12.05.06 09:38

  #define  _R_Nom         ( 100u ) // * _K_diskr )  // 10-ти разрядный АЦП - 100d , 12-ти разрядный АЦП - 400d .

#endif

  #define  _Ugol_180           ( (w) 0x3fffu )

  #define  _Ugol_90            ( (w) 0x1fffu )

  #define  _Ne_Rabota   Prg._.Gotovn

  #define  _N_StypF()   (Pi0_f.all & 0x38)>>3


    /*         Макросы перевода величин скорости, тока и ЭДС из  */
    /* относительных единиц в номиналах в относительные единицы в дискретах.  */
    /*  Величина 'nom', задаваемая ему, не должна выходить за сетку 'double'.  */

#define   _Id_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Id_Nom ))

#define   _Id_nom200( nom )  ((w)(int)( (const d)(nom) * (const d)_Id_Nom200 ))

#define   _Ig_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Ig_Nom ))

#define   _Ud_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Ud_Nom ))

#define   _Mom_nom( nom )    ((w)(int)( (const d)(nom) * (const d)_Mom_Nom ))

#define   _Iv_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Iv_Nom ))

#define   _Fv_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Fv_Nom ))

#define   _Uf_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Uf_Nom ))

#define   _Is_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Is_Nom ))

#define   _Us_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Us_Nom ))

#define   _Cos_nom( nom )    ((w)(int)( (const d)(nom) * (const d)_Cos_Nom ))

#define   _Itr_nom( nom )    ((w)(int)( (const d)(nom) * (const d)_Itr_Nom ))

#define   _R_nom( nom )      ((w)(int)( (const d)(nom) * (const d)_R_Nom ))

#define   _AD_offset( nom )  ((w)(int)( (const d)(nom) * ((const d)_AD_VOLT/2+0.5) ))

#define   _1mA_nom( nom )    ((w)(int)( (const d)(nom) * (const d)_1mA_Nom ))

//-------
#ifdef   P_CH
//-------
#define   _i_nom( nom )      ((w)(int)( (const d)(nom) * (const d)_i_Nom ))

#define   _dF_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_dF_Nom ))

#define   _Umz_nom( nom )    ((w)(int)( (const d)(nom) * (const d)_Umz_Nom ))

#define   _HzSin_nom( nom )  ((w)(int)( (const d)(nom) * (const d)_HzSin_Nom ))

#define   _Ku_nom_m( nom )   ((w)(int)( (const d)(nom) * (const d)_Ku_Nom_m ))

#define   _Ku_nom_p( nom )   ((w)(int)( (const d)(nom) * (const d)_Ku_Nom_p ))

#define   _Ku_nom_v( nom )   ((w)(int)( (const d)(nom) * (const d)_Ku_Nom_v ))

#define  _Volt_nom( nom )    ((w)(int)( (const d)(nom) * (const d)_Volt_Nom ))

#define  _Grad_cel( nom )    ((w)(int)( (const d)(nom) * (const d)_Grad_Cel ))

#define  _Grad_cel_k( nom )  ((w)(int)( (const d)(nom) * (const d)_Grad_Cel_k ))

#define  _Rs_nom( nom )      ((w)(int)( (const d)(nom) * (const d)_Rs_Nom ))

#define  _Reg_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_Reg_Nom ))

#define   mSin( L_in , L_out)  sin_ax = L_in & _wgL180_mask ;   \
          if ( sin_ax > _wgL90_mask ) sin_ax  = _wgL180_mask - sin_ax ;\
          sin_ax <<= 1;                                         \
          sin_cx = sin_ax >> 8 ;                               \
          if(Prg._.Trap == 0)                                          \
          {                                                            \
            sin_ax = _sin_tab[sin_cx] ;                                \
          }                                                            \
          else sin_ax = _sin_tab0[sin_cx] ;                            \
          L_out= sin_ax

//-------
#else
//-------

#define   _EDS_nom( nom )     ((w)(int)( (const d)(nom) * (const d)_EDS_Nom ))

#define   _Skor_nom( nom )    ((sw)(int)( (const d)(nom) * (const d)_Skor_Nom ))  // sw - для компилятора IAR

#define  d_Skor_nom( nom )    ((d)( (const d)(nom) * (const d)_Skor_Nom ))

#define   _Q_nom( nom )       ((w)(int)( (const d)(nom) * (const d)_Q_Nom ))

#endif

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#endif

