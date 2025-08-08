#ifndef _sifu2_h
#define _sifu2_h


word SIFU2_Start ( word num ) ;
void S2_Interrupt ( void );
void Id2_Izm (void) ;
void RVT ( void ) ;


  struct SIFU2
    {
      word  Integr     ;
      word  Out_rvt    ;
      word  Alfa       ;
      word  TZ         ;

      byte  N          ;
      byte  NumInt     ;
      byte  NIP        ;
      byte  Most_Tir   ;

      word  Alfa_Old   ;

      union
      {
        byte  all ;
        struct
        {
          word   int_p : 1;
          word   int_m : 1;
          word   VneshZp : 1;  // Внешний запрет импульсов .
          //word   SnImpVM : 1;
        } _ ;
      } flg ;
    }   ;


    struct _r_SIFU2
    {
      byte     FazirovVS ;
      word     Kp_rvt ;
      word     Ki_rvt ;
      word     RVTmax ;
    } ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

_register struct SIFU2      S2 ;

_register   word  s2_ax ;
_register   word  s2_cx ;
_register  lword  s2_lax ;//, s2_lbx  ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

  extern _register  struct SIFU2   S2 ;

  extern _register   word  s2_ax ;
  extern _register   word  s2_cx    ;
  extern _register  lword  s2_lax ;//, s_lbx  ;

/*------------------------------------------------*/
#endif
#endif
