#ifndef _reg_eds_h
#define _reg_eds_h

void  Reg_Eds ( void ) ;
word  Fvz_to_Ivz ( void ) ;
void  Zadanie_Iv ( void ) ;
void  MomentDvig ( void ) ;

     //  Количество точек кривой намагничивания.
  #define   _Nf      20

  struct tab_Ivz
  {
    word   t[ _Nf+2 ]  ;
  } ;

            // Для программ записи уставок.
#define   TabFunc      Ivz
#define   c_TabFunc    c_Ivz


  struct Vozb
  {
    word  Fv_zad ;
    word  Iv_zad ;
    word  Fv , Iv , Iv_full ;
    union
    {
      word all ;
      struct
      {
        word  ltd_z_max : 1 ;
        word  ltd_z_min : 1 ;
        word  Fmax      : 1 ;
        word  Fmin      : 1 ;

        word  Fdmax     : 1 ;
        word  Fdmin     : 1 ;
        word  fazir     : 1 ; //RT        : 1 ;
        word  most2     : 1 ; //DAN 07.08.2018 13:15 : для будущего реверсивного возб-ля , 0-вперёд , 1-назад .

        word  otkl_func : 1 ;
        word  Iv_econom : 1 ;
        word  Iv_gashen : 1 ;
        word  Sdvig_imp : 1 ;

        word  Otkl_Imp  : 3 ;
        word  Iv_max    : 1 ; //: 2 ; DAN 07.08.2018 13:15 - ещё в 2008 году вместо двойной проверки сделана выдержка времени .
      } _ ;
    } flg ;
    //------
      word  Alfa_Old   ;
      word  Integr_rt  ; // Для индикации в стандартном MSG_TABL.H .
#ifdef _Vozb_KTE
      word  Alfa       ;
      word  TZ         ;
      word  TZ_real    ;
      word  Iv_off     ;
      byte  time_Iv_max;
      byte  N          ;
      byte  NumInt     ;
      byte  NIP        ;
#endif
    //------
  };

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

        // Кривая намагничивания.
struct tab_Ivz Ivz ;

struct Vozb  V ;
#ifdef _RVId
  struct Vozb  V2 ;
#endif
word Integr_REDS  ;
word OutRSMaxM1 , OutRSMaxM2 ;
word Skor_II_Z ;
word Moment ;
word Zad_EDS ;
byte puls ;

#ifndef _Vozb_KTE
 Usrednit_Str   Iv_usr;
#endif
#ifdef _RVId
 Usrednit_Str   Iv2_usr;
    #ifdef _KTEV
        Usrednit_Str   Udv_usr;
        word UdvSr_full, UdvSr;
    #endif
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern struct tab_Ivz Ivz ;

extern struct Vozb  V ;
#ifdef _RVId
  extern struct Vozb  V2 ;
#endif
extern word Integr_REDS ;
extern word OutRSMaxM1 , OutRSMaxM2 ;
extern word Skor_II_Z ;
extern word Moment ;
extern word Zad_EDS ;
extern byte puls ;

#ifndef _Vozb_KTE
 extern Usrednit_Str   Iv_usr;
#endif
#ifdef _RVId
 extern Usrednit_Str   Iv2_usr;
    #ifdef _KTEV
        extern Usrednit_Str   Udv_usr;
        extern word UdvSr_full, UdvSr;
    #endif
#endif

/*------------------------------------------------*/
#endif
#endif


