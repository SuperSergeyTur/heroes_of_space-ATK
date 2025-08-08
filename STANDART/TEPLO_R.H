#ifndef _teplo_h
#define _teplo_h

extern void Teplo_Programm ( word num ) ;

#define    Id_TeploIntegr   tpl.Integr

#define    Id_teplo_max     tpl.I_max

#define    Id_teplo         tpl.I

//------------------------------
#ifdef  _MAIN_INCLUDE

  struct Teplo_un  tpl ;

#else

  extern struct Teplo_un  tpl ;

/*------------------------------------------------*/
#endif
#endif

