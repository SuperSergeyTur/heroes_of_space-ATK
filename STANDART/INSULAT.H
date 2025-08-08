#ifndef  _insulat_h
#define  _insulat_h

extern word  Contr_Insulat ( word num ) ;

#ifndef    _Insul_koef
  #define  _Insul_koef  (0.7 * 256)
#endif

#ifndef    bi_Otkl_Insul
  #define  bi_Otkl_Insul  ( Prg._.Gotovn == 1 )
#endif

#ifndef    _Uout
  #define  _Uout   Ud
  #define  _Uout_nom( data )  _Ud_nom( data )
#endif

//------------------------------
#ifdef  _MAIN_INCLUDE
//------------------------------
       // Äëÿ êîíòğîëÿ èçîëÿöèè.
word Uinsul , Uinsul_max  ;
byte Uinsul_drob ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern word Uinsul , Uinsul_max  ;
extern byte Uinsul_drob ;

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#endif
#endif
