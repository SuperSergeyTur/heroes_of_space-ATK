#ifndef _cikl_h
#define _cikl_h

  #define   _CiklLong  ( (b) 0x06u )

/*-----------   Структура для Циклов. --------------*/

 union Zad_Cikl_str {
              word  all ;
              struct {
                        word  SIFU       : 1;
                        word  RT         : 1;
                        word  RS         : 1;
                        word  RN         : 1;

                        word  RTV        : 1;
                        word  rezerv     : 1; // Reg_EDS 09.06.2020 15:35
                        word  SIFUV      : 1;
                        word  RP         : 1;

                        word  RT1        : 1;
                        word  RT2        : 1;

                      } _ ;
            } ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

 union Zad_Cikl_str   Ckl, Ckl1 ;

        word     TCIKL ;

        word     CiklTab[ _CiklLong ] ;

        word      OCIKL ;

        word     YKST, YKSTc ;// Счет и контроль циклов CIKL.c word*    YKST ;

        word     SCHCIKL ;

/*------------------------------------------------*/
  #else
/*------------------------------------------------*/

  extern  union Zad_Cikl_str   Ckl, Ckl1 ;

  extern  word     TCIKL ;

  extern  word     CiklTab[] ;

  extern  word     YKST, YKSTc;// Счет и контроль циклов CIKL.c  extern  word    *YKST ;

  extern  word     OCIKL ;

  extern  word     SCHCIKL ;

/*------------------------------------------------*/
#endif
#endif

