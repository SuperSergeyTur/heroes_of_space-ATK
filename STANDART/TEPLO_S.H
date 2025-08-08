#ifndef _teplo_s_h
#define _teplo_s_h

extern void Teplo_s_Programm ( word num ) ;

#define    Is_TeploIntegr  tpls.Integr

#define    Is_teplo_max    tpls.I_max

#define    Is_teplo        tpls.I

//------------------------------
#ifdef  _MAIN_INCLUDE

  struct Teplo_un  tpls ;

#else

  extern struct Teplo_un  tpls ;

/*------------------------------------------------*/
#endif
#endif

