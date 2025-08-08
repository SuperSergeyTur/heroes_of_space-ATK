#ifndef _rev_pola_h
#define _rev_pola_h


 void  Revers_Pola ( void ) ;

/*----------- Признаки реверса поля ------*/

     //  Выходные сигналы логического блока реверса поля
 union Rev_Pola_Prz {
  word all ;
  struct  {
#ifndef _Union_FR
      word Revers_Pol  : 1 ;  // признак реверса поля.
      word Napravl     : 1 ;  // признак направления.
      word znak_Iv     : 1 ;  // признак полярности тока возб.
      word need_rever  : 1 ;  // признак необходимости реверса.

      word prev_delt   : 1 ;  // признак превышения дельта зад. и ист. скор.
      word znak_Fvz    : 1 ;  // знак выхода РС
      word razr_Rev_P  : 1 ;  // разрешение реверса поля
      word Not_Rev_P   : 1 ;  // не проходит реверс поля

      word Malen_Iv    : 1 ;  // маленький ток If

      word rezerved    : 7 ;
#else
      word rezerved    : 7 ;

      word Malen_Iv    : 1 ;  // маленький ток If

      word Not_Rev_P   : 1 ;  // не проходит реверс поля
      word razr_Rev_P  : 1 ;  // разрешение реверса поля
      word znak_Fvz    : 1 ;  // знак выхода РС
      word prev_delt   : 1 ;  // признак превышения дельта зад. и ист. скор.

      word need_rever  : 1 ;  // признак необходимости реверса.
      word znak_Iv     : 1 ;  // признак полярности тока возб.
      word Napravl     : 1 ;  // признак направления.
      word Revers_Pol  : 1 ;  // признак реверса поля.
#endif
    } _ ;
} ;

#define _Delt_Sk  _Skor_nom( 0.05 )

//#define   _Obj_c_Init              0
//#define   _Obj_c_DS1_Init          1
//#define   _Obj_c_Sborka_Gotovn     2

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/


         lword     OuRegS_long  ;

 union Rev_Pola_Prz  RP_Pz  ;

 word Time_RP ;
/*------------------------------------------------*/
#else
/*------------------------------------------------*/

  extern  lword    OuRegS_long  ;

  extern union Rev_Pola_Prz  RP_Pz ;

  extern word Time_RP ;
/*------------------------------------------------*/
#endif
#endif

