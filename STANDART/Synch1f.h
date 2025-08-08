#ifndef _synch1f_h
#define _synch1f_h

   /* ������ ����: ������� ��� ����� �� ������� �������� ������������
    * ������� ���� � ��������� �������.
    */
#ifndef  _Synch_3f
  #define    Tsyn    Hw( Syn.lTsyn )
  #define    Fsyn_380    Syn.Fsyn
#endif

#define    Tsyn2   Hw( Syn2.lTsyn )
#define    Fsyn2_380   Syn2.Fsyn


/*-----------   ���� ���������� ��� �/� ������������� --------------*/

  struct Synchr
    {
      word   NS2      ; // ����������� ������ ������� ��.
      word   NS_EPA   ; // ������ ������� �� ����������� ���.
      word   NS_OLD   ; // ������ ������� ��, ������������ �� ������, ���� ������ ����� ��� �������� �� �����.
      word   dt_old   ; // �������� �� ������� ������� �� NS_OLD �� ��������� ����� ��������.
      word   dTsyn    ; // ���������� ������� ��� ������� �� NS_OLD.
      word   NS, tsyn ; // ������ ������� "���������������" ��.
      word   T1_ovr   ; // ����������� ������� ������� ���������� �� ��� ����������� �������� �� ������������.
      lword     lTsyn ;
      word*  epa_time ;
//      word   time_out ; // ����������� ������� ������� ���������� �� ��� ����������� �������� �� ������������.
      word   Fsyn     ; // ������� ������� �����. ������������ �� �������.

      word   KSDT   : 2 ; //  ������� ������� ��
      word   b_SIv  : 1 ;
      word   b_SIu  : 1 ;
      word   b_SIi  : 1 ;
      word   b_SItst: 1 ;
      word   b_SIauto  : 1 ;
      word   b_ns_old  : 1 ;
      word   b_nsx_old : 1 ;
    }   ;

extern word   Synch_Start ( void ) ;
extern void Synch_3f ( void ) ;
extern void Sync_start ( struct Synchr *syn ) ;
extern void Synch (  struct Synchr *syn ) ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

 struct Synchr    Syn ;
 
#ifdef  _SIFU_Syn3
 struct Synchr    Syn3 ;
#endif 
 
#ifdef  _Synch_3f
 struct Synchr    Syn2, Syn3 ;
 word  Tsyn, Fsyn_380 ;
    #ifdef _CM3_
       word _SyncTCA_time, _SyncTCB_time, _SyncTCC_time ;
    #endif
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern          struct Synchr    Syn ;

#ifdef  _SIFU_Syn3
extern          struct Synchr    Syn3 ;
#endif 

  #ifdef  _Synch_3f
extern          struct Synchr    Syn2, Syn3 ;
extern          word  Tsyn, Fsyn_380 ;
    #ifdef _CM3_
extern word  _SyncTCA_time, _SyncTCB_time, _SyncTCC_time ;
    #endif
  #endif

/*------------------------------------------------*/
#endif
#endif
