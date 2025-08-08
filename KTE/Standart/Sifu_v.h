#ifndef _sifuv_h
#define _sifuv_h


extern word   Vozb_Start ( void ) ;
extern void   Vozb_Interrupt ( void ) ;
extern word   Short_V_ImpLong ( void ) ;

#define   _r_V_Alfa_Izm       _MkSec( 12*55 ) //_Grad( 12 ) 11.04.2019 13:28 надо будет всё перевести в _Grad()
#define   _r_V_DeltaAlfa_Max  _Grad( 15 )
//---
#ifdef  _SIFUV_1Faza
    #define   _ShortImp_Long      _MkSec( 12*55 ) //_Grad(  12 )
#else // 25.01.2019 Уссурийск 5к. Во встроенном 3-х фазном возбудителе короткие ИУ д.б. 6 град (указание Шестакова и Швеня).
    #define   _ShortImp_Long      _MkSec( 6*55 ) //_Grad(  6 )
#endif
//---

//DAN 07.08.2018 14:00 - Три бита для трёх масок :
#define   _V_Av_otkl_imp      1
#define   _V_VR1_otkl_imp     2
#define   _V_Revers_otkl_imp  4 // DAN 07.08.2018 13:15 : для будущего реверсивного возб-ля .

/*------------------------------------------------*/
#ifdef _VOZB_INCLUDE
/*------------------------------------------------*/

_register   word  v_ax ;
_register   word  v_cx ;
_register  lword  v_lax , v_lbx  ;

      // Для возможности задать из-вне переменную длину ИУ.
            word V_ImpLong ;

            word   time_Iv_max ;

#ifndef  _ExternTabImpV

#define   SetImpCode( num )  ImpTabVozb [ num ]
             //   Таблица с подтверждающими ИУ.
//---
#ifndef  _SIFUV_1Faza
//---                 // для 590 только 4 импульса возбудителя,
     // для FR - все 6 импульсов :
                      // рабочие тиристоры:  1/6, 2/1, 3/2, 4/3, 5/4, 6/5.
    const byte ImpTabVozb [ 7 ] = { 0x3f,0x5e,0x7c,0x79,0x73,0x67,0x4f };

//---
#else
//---
    // тир-ры двоятся чтобы можно было реализовать 120-грд ИУ для 1-фазн.
  #if defined(_Union_FR) || defined (_CM3_)  // Для этой системы беруться V1 , V3 , V4 , V6 :
                      // рабочие тиристоры:    1/6, 1/6,откл.,3/4, 3/4,откл.
    const byte ImpTabVozb [ 7 ] = { 0x3f,0x5e,0x5e,0x3f,0x73,0x73,0x3f };
  #else  // У 590 процессора 4 импульса на возбудитель - V1 , V2 , V3 , V4 :
                      // рабочие тиристоры:    1/2, 1/2,откл.,3/4, 3/4,откл.
    const byte ImpTabVozb [ 7 ] = { 0x3f,0x7c,0x7c,0x3f,0x73,0x73,0x3f };
/*             A  C
            V4 і  і  V1
         ЪДДДДБДДЕДДДДї
         і        і     і
         і  V2(6) і  V3 і
         ГДДДДДДДБДДДДґ
         і '-'          і'+'
*/
  #endif
//---
#endif
//---
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

  extern _register   word  v_ax ;
  extern _register   word  v_cx    ;
  extern _register  lword  v_lax, v_lbx  ;

  extern             word V_ImpLong ;

  extern             word time_Iv_max ;

  extern      const byte  ImpTabVozb []   ;

/*------------------------------------------------*/
#endif
#endif
