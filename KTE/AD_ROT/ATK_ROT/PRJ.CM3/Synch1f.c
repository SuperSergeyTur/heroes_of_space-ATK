//        ��������� ��������� �������� � �������������.
//------------------------------------------------------------------

//-----------------
//     ���� ��������� ��������� ��������� ������������ ��� ���������
//  � ����� ���������� �������������.
//     ��� ��������� � �� ����� ���������� �������������, ������� ���������
//  ���� ��������� ��������� �������� ����.
//-----------------
  // chtoby v setku vlazylo bolee 2-x periodov i period vlazyl v znakov. setku.
#define _Tmax_setka   ( (w)(0xFFFFu/2.3) ) // /2.3 => 35Hz

  //---
#ifndef   _Extern_Synch
  //---
word Synch_Start ( void )
  {
  //lword lax;
      // ��������� EPA - �������� ��� �������� �����.
#ifndef  _Synch_3f

  #ifndef  _DMA_Synch
    init_syn_epa( _synch_epa_con ) ;
    Syn.epa_time = (lw*)&_synch_epa_time ;
  #else
    init_syn_dma() ; //    init_syn_dma( _synch_dma_con ) ;
    Syn.epa_time  = (w*)&_synch_dma_time ;
  #endif

    Sync_start ( &Syn ) ;   // ��������� �������������.

#else

  #ifndef  _DMA_Synch

   #ifndef _CM3_
    init_syn_epa( _synch_epa_con ) ;
    init_syn_epa( _synch2_epa_con ) ;
    init_syn_epa( _synch3_epa_con ) ;

    Syn.epa_time  = (w*)&_synch_epa_time ;
    Syn2.epa_time = (w*)&_synch2_epa_time ;
    Syn3.epa_time = (w*)&_synch3_epa_time ;

   #else     //  ��� ����, � ��� �� ����� ���� �������???

    Syn.epa_time  = (w*)&_SyncTCA_time ; //(w*)&_synch_epa_time ;
    Syn2.epa_time = (w*)&_SyncTCB_time ; //(w*)&_synch2_epa_time ;
    Syn3.epa_time = (w*)&_SyncTCC_time ; //(w*)&_synch3_epa_time ;

   #endif

  #else
    init_syn_dma() ; //    init_syn_dma( _synch_dma_con ) ;

    Syn.epa_time  = (w*)&_synch_dma_time ;
    Syn2.epa_time = (w*)&_synch2_dma_time ;
    Syn3.epa_time = (w*)&_synch3_dma_time ;
  #endif

    Sync_start ( &Syn ) ;   // ��������� �������������.
    Sync_start ( &Syn2 ) ;   // ��������� �������������.
    Sync_start ( &Syn3 ) ;   // ��������� �������������.

    Tsyn = _MkSec( 20000 ) ;  //  ����� ��� 3-� ��� ������ �
    Fsyn_380 = 50*256 ;           //          �������.

#endif

    return  0 ;
  }


/*  ��������� ��������� ������������� */

void Synch_3f ( void )
{
          Synch ( &Syn ) ;

  #ifdef  _Synch_3f

          Synch ( &Syn2 ) ;
          Synch ( &Syn3 ) ;
                        //   �������� ������ ������� � ������� �� ����� �� ���.
        if ( _r.Cfg._.Sync_3f == 1 )
        {
          if      ( (u)(w)(Timer1_Ovr - Syn.T1_ovr )  <= 2  )  Tsyn = Hw( Syn.lTsyn ),  Fsyn_380 = Syn.Fsyn ;
          else if ( (u)(w)(Timer1_Ovr - Syn2.T1_ovr ) <= 2  )  Tsyn = Hw( Syn2.lTsyn ), Fsyn_380 = Syn2.Fsyn ;
          else if ( (u)(w)(Timer1_Ovr - Syn3.T1_ovr ) <= 2  )  Tsyn = Hw( Syn3.lTsyn ), Fsyn_380 = Syn3.Fsyn ;
        }
        else
        {
          Tsyn = Hw( Syn.lTsyn ),  Fsyn_380 = Syn.Fsyn ;
        }

  #endif
  return ;
}
  //---
#endif
  //---
//------------------------------------------------------

//-----------------
//   ������������� ����� ��������� �������������.
//-----------------

void Sync_start ( struct Synchr *syn )
  {
    syn->NS_EPA = *syn->epa_time ;
    syn->NS     = syn->NS_EPA ; // timer1 ;18.02.07 22:07
    syn->tsyn   = _MkSec( 20000 ) ;

    syn->Fsyn   = 50.0 ;
    Hw( syn->lTsyn ) = _MkSec( 20000 ) ; // ��� ������ ����.
    syn->KSDT   = 3 ;// 1 ;
    syn->NS2    = timer1 ; // chtoby zapustilos SIFU.
    syn->b_SIv  = 1 , syn->b_SIu = 1 , syn->b_SIi = 1 , syn->b_SIauto = 1 ;
    syn->T1_ovr = Timer1_Ovr-_Sec(60) ; /* ��� ����, ����� ����� ����� ���������� �� */
    //syn->time_out = Timer1_fSec - _Tmax_setka ;
    syn->NS_OLD = 0 ;
    syn->dt_old = 0 ;
    syn->b_ns_old = 0 ;
    syn->b_nsx_old = 0 ;

    return ;
  }
//------------------------------------------------------

/*  ��������� ��������� ������������� */

void Synch ( struct Synchr *syn )
{
  register word  ax , bx , cx ;
  register lword lcx ;
  float fax;

            // ����������� �������� �� ���������� �����.
    if ( (*Timer3-syn->T1_ovr) > 0x7fff ) syn->T1_ovr = *Timer3-0x7fff ;
        //---
        /*   �� ��������� ����������� ��� �� ��������� � ���������� �������
          * ������� � ���, ��� ������ ������������� (�� ��� ������) */
    if ( syn->NS_EPA == *syn->epa_time )
    { //--- ���� ����� ���������� ��������� ��� ��� ��� "��������������" �� , �
      // ������ (������ + _r.dTsyn_max) , � ��� ������ �� �������� ...
      if ( syn->KSDT == 0 )
      {
        ax = (w)(*Timer3 - (syn->NS2 + (syn->lTsyn>>16)) ) ;
             //  ��������� ��� ��������, ����� ����� �� ����������� �����,
            // ��� ������ ������� ����� NS2.
        if ( (sw)ax >= (sw)_MkSec( 20 * 55 ))  // _r.dTsyn_max )
        {     //--- ������� �� �������� "syn->b_ns_old" ������� ���� �� ���������
              // "���������������" �� :
                // ��� �� ������ ��?
          if ( syn->b_ns_old != 0 ) goto sover ;
                // ��� �� ������������� ��?
          else  if ( syn->b_nsx_old != 0 ) syn->KSDT = 1 ;
                // �� ���� �������� ��.
          else                             syn->KSDT = 3 ;
        }
      }    // �������� ���������� �����.������.
      else if ( syn->KSDT != 3 )
      {      // control otsutstv.sync. ili perioda nige 30Hz.
        if ( (*Timer3 - syn->NS_EPA) >= _Tmax_setka ) syn->KSDT = 3 ;
      }
      return ;
    }
    else
    {
      syn->NS_EPA = *syn->epa_time ;   /* ������������ ������� ���������� ��� */
        //---
      if ( syn->KSDT == 0 )
      {   /* ������������ �������� ������� ��, � ������
            * �������� ������� ����� ������� � ������� ���������������.
            */
        ax = syn->NS_EPA - syn->NS2 ;
          /*   ������ ����������� �� ���������� ������� pri lozhnom srabat.
            * comparatora, na perehode 180grd, i �����
            * ��������� ������� � ������������ � ����������� ���������.
            */                                      // ���� �� ����������� NS.
        if ( ax < (w)((syn->lTsyn>>16)-_r.dTsyn_max) )  syn->b_nsx_old = 1 ;
        else
        {
        //--- �������� ����� ����������� �������� ������� �� � "��������":
        ax -= (syn->lTsyn>>16) ;
        cx = ax ;
        if ( (sw)ax < 0 ) ax = -ax ;

        //--- ������� �� �������� "syn->b_ns_old" ������� ���� �� ���������
        // "���������������" �� . ���� ����� �������� ����� �����������
        // �������� ������� �� � "��������" ������ ������� :
        if ( syn->b_ns_old == 0 || ax < syn->dt_old )
          {     //   �������� ���������� ������� �� ���������� ������,
            if ( (sw)ax <= (sw)_r.dTsyn_max )
            {
              //--- ���������� ��� ��������� ���� ����� ������� �� ��
              // ������ , ���� ����� ��� �������� ����� "����������" :
              syn->b_ns_old = 1 ; // ������� ������� ������� ������������� .
              syn->NS_OLD = syn->NS_EPA ; // ������ ������� �� .
              syn->dt_old = ax ; // �������� �� "���������" ����� �������� .
              syn->dTsyn  = cx ; // ���������� ������� .
              return ;
            }
            else  syn->KSDT = 1 ;
          }
        //--- ����� ������ ������� �� ����� ������ �������� �� "���������"
        // ����� �������� , - ������ ����� ����� ������ ����� ������� �� :
        else if ( ax > syn->dt_old )
          {
           /*  ���������� ������������ ������� (2-� ��������) ��, ������������ ���
            * ���������� �� ������� (4-� ��������) ������� �� ���������� (�������-
            * ���� ������� �� ������������) ����������� �� "N" ������� ������
            * ������������ ����� ����� ������� �� �� n-��� ("K_synchr") ���, ���
            * ���� �����, ������� ����� ������������ ������� ����� �� (16-n)-���.
            *   �������, ����� �������, � ������� ��� �����, ������������ � ����-
            * ������ ��� ����������� �������� �������, ���� ����� ����� ����������
            * ������� ����������, � � ������� ��� ����� - �������.
            *   ���������� ������� � ������� ���� ������ ������������ '�������'
            * ������������ �������. ��� ������������ �� ������� ��������� ����������,
            * �.�. ����� ����������� ������ ��������� �� 1�����. �������� ������
            * ������ ��� ���������� �� �������� ������� �������� �������� ������������
            * (�.�. �� �������, ����� ��� ��������� �� ����� � �������)
            */
    sover: lcx = syn->lTsyn + ((slw)(sw)syn->dTsyn << ( 16 - _r.K_synchr )) ;

                    // zaschita ot shuma - ���� ��������� �������:
            if ( (w)(lcx >> 16) < _MkSec(12500) || (w)(lcx >> 16) > _MkSec(30*1000) )   // predel 80Hz //100Hz .
            {
              syn->KSDT = 3 ;
              return ;
            }

            syn->lTsyn = lcx ; // ���������� ����� ������ .

              /*  ���������� ��������, ���������������� ������� ��. */
            ax = syn->NS2 + (syn->lTsyn>>16) , cx = syn->NS_OLD - ax ;
            Syn_NS2_old = syn->NS2;
            syn->NS2 = ax + ((sw)cx >> _r.Kf_synch ) ;
            //---
            // ���������� ��������� ��� ���������� ��������� ��� :
            syn->NS = syn->NS_OLD ;
        sx:
            //---------------
            // ������� ������� � �������.
            fax = (float)(Hw( syn->lTsyn )) ;
            syn->Fsyn = (float)_MkSecl(1000000)  / fax ;
            //---
            syn->b_SIv = 1, syn->b_SIu = 1, syn->b_SIi = 1, syn->b_SIauto = 1 ;
            syn->T1_ovr = Timer1_Ovr ; /* ��� ����, ����� ����� ����� ���������� �� */
            //---------------
            syn->NS_OLD = 0 ; // ������������� ��� ���������� ����������� .
            syn->dt_old = 0 ;
            syn->b_ns_old = 0 ;
            syn->b_nsx_old = 0 ;
            //--- ����� ��� ������ syn->NS , ����� �� �������
            // ���� �������� � �� ���������� �� ����� KSDT != 0 :
            return ;
          }
        }
      }
      else
      {     // ��������� - �� ������ �� ��� ��� ����� ������ �����?
        if ( syn->KSDT != 3 )
        {
          // ������������ ���������� �������� ������� ��, � ������
          // �������� ������� ����� ������� � ������� ����������� ���.
          ax = syn->NS_EPA - syn->NS ;
          cx = ax - (syn->lTsyn>>16) ;  // ���������� �������.

            /* ������� ������������ � ������ ����� ����� �� ��� ��� ����
              * ��� ����� ����� �� ������ � ���������� " TC +- dx ".
              */
          if ( ax >= _MkSec(12500)  &&  ax <= _MkSec(30000) ) // zaschita ot shuma: predel 80Hz //100Hz, .
          {
            if ( syn->KSDT == 1 )  syn->tsyn = ax,  syn->KSDT = 2 ;
            else  // lovim sredi musora dva podryad stabilnyh perioda:
            {    // raznica mezhdu mgnovennym tekushim i proshlym periodami.
              bx = ax - syn->tsyn ;
              if ( (sw)bx < 0 ) bx = -bx ;
              lcx = ((lw)syn->tsyn + (lw)ax ) << (16-1) ; // usredn '(a+b)/2'
              syn->tsyn = ax ;
                //---  esli otklonenie menshe chem 1/50 perioda(2%), to Ok.
              if ( bx <= (ax/50) )
              {    /*   ������� ����� �������-�� ������������� ���� �����������
                    * � ��-����� �����������, ��� ����� ����������� ����� �������� */
                syn->lTsyn = lcx ;
                Syn_NS2_old = syn->NS2 ;
                syn->NS2 = syn->NS_EPA ;
                syn->NS = syn->NS_EPA ;
                syn->KSDT = 0 ;   /* ����� �������� ����� �� �� */
                goto sx ;
              }
          } }
          else  syn->KSDT = 1 ;
        }
        else  syn->KSDT = 1 ;
      }
      syn->NS = syn->NS_EPA ;
    }

 return;
}
//-----------------------------------------------

