#ifndef _rev_pola_h
#define _rev_pola_h


 void  Revers_Pola ( void ) ;

/*----------- �������� ������� ���� ------*/

     //  �������� ������� ����������� ����� ������� ����
 union Rev_Pola_Prz {
  word all ;
  struct  {
#ifndef _Union_FR
      word Revers_Pol  : 1 ;  // ������� ������� ����.
      word Napravl     : 1 ;  // ������� �����������.
      word znak_Iv     : 1 ;  // ������� ���������� ���� ����.
      word need_rever  : 1 ;  // ������� ������������� �������.

      word prev_delt   : 1 ;  // ������� ���������� ������ ���. � ���. ����.
      word znak_Fvz    : 1 ;  // ���� ������ ��
      word razr_Rev_P  : 1 ;  // ���������� ������� ����
      word Not_Rev_P   : 1 ;  // �� �������� ������ ����

      word Malen_Iv    : 1 ;  // ��������� ��� If

      word rezerved    : 7 ;
#else
      word rezerved    : 7 ;

      word Malen_Iv    : 1 ;  // ��������� ��� If

      word Not_Rev_P   : 1 ;  // �� �������� ������ ����
      word razr_Rev_P  : 1 ;  // ���������� ������� ����
      word znak_Fvz    : 1 ;  // ���� ������ ��
      word prev_delt   : 1 ;  // ������� ���������� ������ ���. � ���. ����.

      word need_rever  : 1 ;  // ������� ������������� �������.
      word znak_Iv     : 1 ;  // ������� ���������� ���� ����.
      word Napravl     : 1 ;  // ������� �����������.
      word Revers_Pol  : 1 ;  // ������� ������� ����.
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

