void Avtonastroyka_RT ( word code )
{

word c_err ;   // ��� ������
static byte vosst_ust ;

   if ( code == 0 )  // ����������/������������� ������� ��� �������� �������.
   {
     vosst_ust = 0 ;
     // 12.11.2008 11:34 : DAN - �� ����� ������������ �������� ������� ����������� ������� ,
     // ��-�� ���� ��� ��������� ������ ���� ������� �� .
     //K_perereg_AN_old = _r.K_perereg_AN ;
     return ;
   }
   else if ( code == 2 )  // ����������/������������� ������� ����� ��������������.
   {
     vosst_ust = 1 ;
     S_Alfa_IzmDoImp  = _r.S_Alfa_IzmDoImp ;
     return ;
   }
   else if ( code == 3 )  // �������������� ������� ����� �������������.
   {
      if ( vosst_ust == 1 )
      {
        _r.S_Alfa_IzmDoImp = S_Alfa_IzmDoImp ;
        vosst_ust = 0 ;
      }
     return ;
   }
   //                    ������� �����
   //------------------------------------------------------
               // 0 - ������� ��������� ������
               // 1 - ������ � ������
               // 4 - ��� ����������� ������

    switch ( AnastrRT ) // ������������ � F2_DRV.C �� ������� �� MSG_TABL.H :
    {
        case 0 :    // �����-� R����� � ��     (����� - ��� �����������)
                    c_err = ANastr_Ra_Te () ;
                    if ( c_err != 4 ) goto otkl ; // ���� ������ "1" ��� �������� ���������� "0" - ���������� .
					break;

        case 1 :    // �����-� ��  (����� - ���� ���������)
                    c_err = ANastr_Tm () ;
                    if ( c_err != 4 ) goto otkl ;
					break;
        default:    // 24.04.2009 8:50 DAN �� ��������� ��� � ������ ���������� , �� ��� ����
          // otkl:    mSet_AvarMsg( _Av_VR1 ) ; // �������� ��� ��������� ��������� �� ���������� .
          //          bo_Gotov = 0 ,  Prz._.VR1 = 1 ;
             otkl:  Isp.all = 0;  // ��������� ���������� ����� .
                    Prg._.Blok_upr = 0;
                    //20.05.2020 - ����� ���������� �� ������� � ����� ��������� .
                    Pult_Prog_Addr = _Case ( 'A' , '0' ) ,  M_FirstCall = 1 ;
                    break;
    }
    return ;
}

// ************************ ����������� Ra, Te *********************************

word ANastr_Ra_Te (void)
{
  static word an_time, time_anOvr , k_komp ;
  static word p_count_AN0, p_count_AN1, p_count_Res ;
  static double d_ax ;
  byte iTmo , cx ;

  lword lax ;
  word ax, c_err, ax_ud, ax_id ;

  enum {k00, k0, k1, k2, k21, k22, k3, k32, k34, k4, k40, k5, k6, k7, k8, k9, k10, k11, k110, k111, k112,
        k12, k13, k14} ;

  ax_id = IDV ; // ����������� ��� .
  ax_ud = UdSr ;
  if ( (sw)ax_ud < (sw)0 )  ax_ud = ~ax_ud + 1 ;

// ������ �� ������ �����������.
    if ( AN_Label >= k2 )
    {
      if ( V.Iv > _Iv_nom(0.07) // 31.07.2014 12:00 - ���� _Iv_nom(0.03)
//#ifdef bi_GL1 // ���� ��������� ������������� ����������������� , �� ������������ 1GL , �.�. �� �������� ��� ����������� ...
//                                || bi_GL1 == 0
//#endif
                                               )
      {
        mSet_ServiceMsg ( _Srv_AN_Iv_min ); // "�� ���� Iv !"
        //output_s ( _AN_Iv_min ) ;
        S.Alfa = _r.S_Alfa_Start ; // 31.07.2014 12:00 - ������� ������� ��� .

  // �� ������ ���� ��� ����������� �� L2 ��������� L1 , �� �� ������ ������ �������������� :
  #ifdef  _SIFU2_
        S2.Alfa_RVT = 0 ;
        S2.Alfa = _r.S_Alfa_Start ;
  #endif
        return 1;
    } }

    switch ( AN_Label)
    {
        case k00 :
           S.Alfa = _r.S_Alfa_Max ;
           an_time = Timer1_Ovr ;
           AN_Label = k0 ;
           iTei = 0;
           flg_RaTe._.Id_anastr = 0;
           IN0n = 0;
        case k0 :
           if ( _r.Cfg._.Ne_Revers == 0 ) // ���� ������� ����������� ,
		   {
              S.flg._.Revers = 1 ; // ������������� ���� ������� �� ������
              Revers_start();      // � �������� ��������� ��������������� ������� .
		   }
           AN_Label = k1 ;

        case k1 :
           // � ������������� ��������� ���� ������� �� p����� �� ��������� ,
           // � � ����������� ���� , ���� ���������� ������ � ���� ��������� :
           if ( S.flg._.Revers != 0 ) break;
           //---
           if ( _r.INN_def_AN == 1 ) // ���� INN ���������� � 90��� :
           {
              if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec(2.0) )
              {
                 S.Alfa = _Grad(90) ;
                 an_time = Timer1_Ovr ;
                 AN_Label = k2 ;
              }
           }
           else  // ���� INN ������������� �� ���������� Ud, Id :
           {
              // ���������� ���� �������������� ��������� Id ����� ����� ��������� Ud :
              if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec(2.0) )
              {
                 S.Alfa = _Grad(120) ;
                 _r.S_Alfa_IzmDoImp = _Grad( 2 ) ;  // �������� ��������� �����
                 flg_RaTe._.Id_anastr = 1;       // ���� ��� sifu.c �������� ������ ���� ����� ����� Ud ,
                 AN_Label = k2 ;     // ��� ���������� ��� ����������� �������� ������������ ���� .
              }
           }
           break;

        case k2 :
    if ( _r.INN_def_AN == 1 ) // ���� INN ���������� � 90��� :
    {
              if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec( 0.4 ) )
              {
                 IN0i[iTei] = ax_id ;  // �������� ����������� ���
                 //--------------------- 17.05.2018 10:00 ------------------------
                 // ��� �������� "�-����-Ud" � ������ ����������� ��������-������������ ���� � 90 ��� :
                 ax = (volatile word)UdSr ;
                 if ( S.NumMost == 1 ) // ��� ���������� � "������" ������������� ���������� ��������
                   {
                      if ( (sw)ax >= 0 )  ax = 0    ;
                      else                ax = ~ax + 1 ;
                   }
                 else  if ( S.NumMost == 2 ) // ��� ���������� � "�����" ������������� ���������� ��������
                   {
                      if ( (sw)ax < 0 )   ax = 0 ;
                    //else                ax = ax ;
                   }
                 else ax = 0 ;
                 Ud_AN[iTei] = ax ;
                 //---------------------------------------------------------------
                 AN_Label = k3 ;
              }
    }
    else  // ���� INN ������������� �� ���������� Id :
    { // ���� INN ���������� �� Id � ������. ���������� Id, ������� ���� ����� ����� Ud
           if ( IN0n == 0 ) S.Alfa -= 1 ; // ��������� ���� �� 1 ����. ������ ���� �� ����� �������� "��������������" ����� .

           if ( S.Alfa < _r.S_Alfa_Min)
                {
                AN_Label = k0;
                S.Alfa = _r.S_Alfa_Max ;
                flg_RaTe._.Id_anastr = 0;
                mSet_ServiceMsg ( _Srv_AN_Av ) ;// "�� o���������� !"
                //output_s ( _AN_Av ) ;
                return 1;
                }

                /* 15.11.2011 15:41 - DAN ���� ��� ������������ �� ��������������� ����, �� �� ������ ������������� ,
                 * ������� ������ �������� ������������� ��� �� ����� "�����" :
                   if ( S.NumMost == 1 ) // ��� ���������� � "������" ������������� ��� ��������
                     {
                        if ( (sw)Id_AN_imp < 0 )  ax = 0 ;
                        else                      ax = Id_AN_imp ;
                     }
                   else  if ( S.NumMost == 2 ) // ��� ���������� � "�����" ������������� ��� ��������
                     {
                        if ( (sw)Id_AN_imp > 0 )  ax = 0 ;
                        else                      ax = ~Id_AN_imp + 1 ;
                     } */

                // 15.11.2011 15:41 - DAN ������ ���������� ��� :
                   if ( (sw)Id_AN_imp < 0 )    ax = ~Id_AN_imp + 1 ;
                   else                        ax =  Id_AN_imp ;

           if ( ( ax_id > _Id_nom(0.02) ) // ���, ���������� � 13 ���., ������ 2%
                           &&
                ( ax > _Id_nom(0.015) )  // � ���, ���������� � ������ ������ ��������,
                        /* &&                  // ����� � �������� 1..3% �� ���.
                ( ax <= _Id_nom(0.03) )*/ ) // ���������� ���� �� ������� ������������ .
                {
                  if ( IN0n >= 6 ) // ����� ��������� 6 ������� , ����� ��������� ������ � ��� :
                  {
                   IN0i[iTei] = ax_id /*- _Id_nom(0.01)*/;  // �������� ����������� ��� (� ���������� 1% ����)

                   Id_AN_imp1  = ax ;  // ���������� ���, ���������� � ������ ������ ��������
                   Id_AN[iTei] = ax ;  // ����������� ��� � 2 ��� �� �� .
                  _r.S_Alfa_IzmDoImp = _Grad( 10 ) ;  // �������� ��������� �����
                   an_time = Timer1_Ovr ;
                   IN0n = 0 ;
                   AN_Label = k21 ;       // ������� �� �������� ���������� ��������� ��������-������������ ����
                  }
                  else IN0n++ ; // ���� ����� �������� ������� .
                }
           else if ( IN0n != 0 ) IN0n = 0 ; // ��� ���� �����....
           break;

        case k21 :

              if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec( 0.8 ) )
                 {
                /* 15.11.2011 15:41 - DAN ���� ��� ������������ �� ��������������� ����, �� �� ������ ������������� ,
                 * ������� ������ �������� ������������� ��� �� ����� "�����" :
                   if ( S.NumMost == 1 ) // ��� ���������� � "������" ������������� ��� ��������
                     {
                        if ( (sw)Id_AN_imp < 0 )  ax = 0 ;
                        else                      ax = Id_AN_imp ;
                     }
                   else  if ( S.NumMost == 2 ) // ��� ���������� � "�����" ������������� ��� ��������
                     {
                        if ( (sw)Id_AN_imp > 0 )  ax = 0 ;
                        else                      ax = ~Id_AN_imp + 1 ;
                     } */

                // 15.11.2011 15:41 - DAN ������ ���������� ��� :
                   if ( (sw)Id_AN_imp < 0 )    ax = ~Id_AN_imp + 1 ;
                   else                        ax =  Id_AN_imp ;
                            // ���� ��� � 10 ��.���. �� ���� ������, ��� ��� � ������ ������ ��������
                   if ( ax <= Id_AN_imp1 )  // ������ ���� ������ ��� "�����".
                     {
                       IN0i[iTei] = 0x1fff ;  // ���������� ������� �����
                     }

                   Id_AN1[iTei] = Id_AN_imp ;    // �������� ��� � 10 ��� �� �� .
                   Id_AN2[iTei] = ax ;        // ����������� ��� � 10 ��� �� �� .
                   flg_RaTe._.Id_anastr = 0;         // ��������� �������������� ������ ����
                   k_komp = 0 ; // ������������� ��� �������� ������� "_r.K_Kompen_Ud" .
                   _r.S_Alfa_IzmDoImp = S_Alfa_IzmDoImp ;
                   an_time = Timer1_Ovr ;
                   AN_Label = k22 ;
                 }
           break;

        case k22 :    //������  ������� "_r.K_Kompen_Ud"
                      // 22.10.2013 - �������� , ��� ������������� �������� , ������� ����� 200 �� ����� ������
                      // ��������� . ��� ����� ���������������� ������ "an_time = Timer1_Ovr" ���� .
            if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec( 0.2 ) )
              {
                ax = (volatile word)UdSr ;
                if ( S.NumMost == 1 ) // ��� ���������� � "������" ������������� ���������� ��������
                  {
                     if ( (sw)ax >= 0 )  ax = 0    ;
                     else                ax = ~ax + 1 ;
                  }
                else  if ( S.NumMost == 2 ) // ��� ���������� � "�����" ������������� ���������� ��������
                  {
                     if ( (sw)ax < 0 )   ax = 0 ;
                   //else                ax = ax ;
                  }
                else ax = 0 ;

                k_komp += ax ;
                IN0n++ ;
                // an_time = Timer1_Ovr ; // ���������������� , ��� �������� 200 �� ����� ������ ���������� .
                if ( IN0n >= 5 ) // ����� ��������� 6 ������� , ����� ��������� ������ � ��� :
                 {
                    ax = k_komp / 6 ;
                    // ���� �� 6 ������� 3 ������ - �������, �� "_r.K_Kompen_Ud" �� ���� :
                    if ( k_komp > 2 && ax == 0 ) ax = 1 ;
                    Ud_AN[iTei] = ax ;
                    IN0n = 0 ;
                    AN_Label = k3 ;
                 }
              }
    } // ��������� ��������� �������� ��������-������������ �� Id � ������. ���������� Id, ������� ���� ����� ����� Ud .
           break;

        case k3 :

               S.Alfa = _r.S_Alfa_Max ;
               if ( S.Alfa_Old == S.Alfa )
               {
                   an_time = Timer1_Ovr ;
                   AN_Label = k32 ;
               }

           break;

        case k32 :
        case k34 :

               S.Alfa -= 1 ;  // ��������� ���� �� 1 ����.
               //---
               if ( S.Alfa < _r.S_Alfa_Min)
               {
                  AN_Label = k0;
                  S.Alfa = _r.S_Alfa_Max ;
                  mSet_ServiceMsg ( _Srv_AN_Av ) ;// "�� o���������� !"
                  //output_s ( _AN_Av ) ;
                  return 1;
               }
               //---

               if ( ax_id >= ( IN0i[iTei] * 4 / 10 ) && AN_Label == k32 )
               {
                  AN_Alfa_04Inn = S.Alfa_Old ;
                  AN_Id_04Inn = ax_id ;
                  AN_Label = k34 ;
               }

               if ( ax_id >= ( IN0i[iTei] * 7 / 10 ) && AN_Label == k34 )
               {
                  an_time = Timer1_Ovr ;
                  AN_Alfa_07Inn = S.Alfa_Old ;
                  AN_Id_07Inn = ax_id ;

                  //KtpRa_pr[iTei] = 91. * (AN_Id_07Inn - AN_Id_04Inn) * 64. / (AN_Alfa_04Inn - AN_Alfa_07Inn)/8. ; // 91 - convert to deg; 8=800d/100%

                    d_ax = (d) _Grad(1) * (AN_Id_07Inn - AN_Id_04Inn) * _sr.NOM.Id.fe / (AN_Alfa_04Inn - AN_Alfa_07Inn) / _Id_Nom ;
                    // ��������� �� double � ������� ���������� :
                    KtpRa_pr[iTei] = d_ax * 64. ; // 64 - ��������� ��� �������� ����� .

                  AN_Label = k40 ;
               }

           break;


        case k40 :
        case k4 :
           S.Alfa -= 1 ;  // ��������� ���� �� 1 ����.
           //---
           if ( S.Alfa < _r.S_Alfa_Min)
           {
              AN_Label = k0;
              S.Alfa = _r.S_Alfa_Max ;
              mSet_ServiceMsg ( _Srv_AN_Av ) ;// "�� o���������� !"
              //output_s ( _AN_Av ) ;
              return 1;
           }
           //---
           if ( ax_id >= _Id_nom(0.5) && AN_Label == k40 )
           {
              AN_Alfa_05Inom = S.Alfa_Old ;
              AN_Id_05Inom = ax_id ;
              AN_Label = k4 ;
           }

           if ( ax_id >= _Id_nom(0.95) && AN_Label == k4 )
           {
              an_time = Timer1_Ovr ;
              AN_Alfa_Inom = S.Alfa_Old ;
              AN_Id_95Inom = ax_id ;

                  //KtpRa_nepr[iTei] = 91. * (AN_Id_95Inom - AN_Id_05Inom) * 64. / (AN_Alfa_05Inom - AN_Alfa_Inom) /8. ; // 91 - Convert to deg; 8=800d/100%

                    d_ax = (d) _Grad(1) * (AN_Id_95Inom - AN_Id_05Inom) * _sr.NOM.Id.fe / (AN_Alfa_05Inom - AN_Alfa_Inom) / _Id_Nom ;
                    // ��������� �� double � ������� ���������� :
                    KtpRa_nepr[iTei] = d_ax * 64. ; // 64 - ��������� ��� �������� ����� .

              AN_Label = k5 ;
           }
           break;

        case k5 :
           if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec( 0.4 ) )
           {

           /* ����������� Ra �� ������ ���,
            * ���������� ��� ����������� ���������� ��� Fujitsu
            *
            *
            *       ax_ud * _sr.NOM.Ud.fe
            *       --------------------
            *             _Ud_Nom
            * Ra = ---------------------------- * _Ra_Nom
            *       ax_id * _sr.NOM.Id.fe
            *       --------------------------
            *             _Id_Nom
            *
            *
            *
            *         ax_ud * _sr.NOM.Ud.fe * _Id_Nom
            * Ra = ------------------------------------- * _Ra_Nom    (1)
            *      ax_id * _sr.NOM.Id.fe * _Ud_Nom
            *
			*
            *      _Id_Nom  = 200u
            *      _Ud_Nom  = 400u
			*
			* 				   _Ud_Nom
			* 	   _Ra_Nom	= --------- * _R0                         (2)
			*                  _Id_Nom
			*
			*
            *         ax_ud * _sr.NOM.Ud.fe
            * Ra = --------------------------- * _R0                  (3)
            *      ax_id * _sr.NOM.Id.fe
            *
			*
			* � (3) - ��� ����������� � _Ra_Nom ������������� �����.
            * ��� ��������� ������������� � ���� , ���� ���������� �� (3) Ra
            * ��������� �� _Ra_Nom �� (2).
			*
			* ������� ������� Ra : ������� �� - ������� ���
			*
              12.10.2018 13:30 - �������� ����� ��������� ������� Rai , ��������� ��� ���������� ���
                                 �� ���������� � ��������� . � ���� �� , � ���������� ����������� ����������
                                 ����, ��� ��� ���� ������� � 90 ��� ���������� ��������� � ���� , ��
                                 �������� ����� ���������� ��������������� � ���� ��������� �� ��������������
                                 ��������� � �������� Rai ������� .

              // ���� �� ���������� ��������� �������� , �� Ud ����� �������� � ���� , ������ :
              if ( ax_ud == 0 ) mSet_ServiceMsg2 ( _Srv2_AN_Ud_Null ) ;

              // ������ ��������� 64 , �� Ud � ������� ���������� � ���������� ���� ��� �������� :
              lax  = (lw)ax_ud * (lw)_sr.NOM.Ud.fe ;
              lax *= (lw)64 ;
              lax /= (lw)Id_AN_high;

              lax *= (lw)_R0 ;
              lax /= (lw)_sr.NOM.Id.fe;
              lax /= (lw)64 ;          // ������� ��������� .
              Rai[iTei] = (w)lax ; // ���, ���� _R0=1000 ; */

              Id_AN_high = ax_id ; // ~95% Id
              AN_Label = k6 ;
           }
           break;

        case k6 :
           S.Alfa = _r.S_Alfa_Max ;
           an_time = Timer1_Ovr ;
           AN_Label = k7 ;
           break;

        case k7 :
           if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec( 0.4 ) )   AN_Label = k8 ;
           break;

        case k8 :
           S.Alfa = AN_Alfa_05Inom ; // ����� ���-�������� ���� .
		   an_time = Timer1_Ovr ;
           AN_Label = k9 ;
           break;

        case k9 :
		   if ( (u)((w)(Timer1_Ovr - an_time)) > _Sec( 0.5 ) )
		   {
              Id_AN_low = ax_id ;
              p_count_AN0 = Puls_counter ;  // ������ ������� ���� ����������� � �������
                              //���������� ���������� � ������ ����� ����������, �.�. � ������ ��.

              ax = Id_AN_high - Id_AN_low ;
              ax *= 63 ;
              ax /= 100;
              Id_AN_t1 = ax + Id_AN_low ; // ������ ����� ��� �������� �� .
              AN_Label = k10 ;
		   }
           break;

        case k10 :
            S.Alfa = AN_Alfa_Inom ;  // ����� ������� ���� .
            if ( ax_id >= Id_AN_t1)
            {
                p_count_AN1 = Puls_counter ;
                AN_Label = k11 ;
            }
		   break ;

        case k11 :  // ������
            S.Alfa = _r.S_Alfa_Max ;

            // ==== ������ �� ���������� ������� - ��� ������, �.�. ������������� ���� � ����,
            // � ����� ����� �������� �.�. ������ ��� ������ 1 ������.
            // ������ ��� ����� ��� � �����.
            p_count_Res = p_count_AN1 - p_count_AN0 ;
            if ( p_count_AN0 > p_count_AN1 )
            {
              p_count_Res = ~p_count_Res + 1 ;
            }
            Tei[iTei] = p_count_Res * 33 * 64 ;  // *3,3 �� *10 , ��������� 64 .
            Tei[iTei] /= 10 ;                    // [ms]

            time_anOvr = Timer1_Ovr;
            if ( iTei >= 5)
            {
              mOtkl_Imp( _VR1_imp );
              _r.Te_AN = (w)( ( (lw)Tei[0]+(lw)Tei[1]+(lw)Tei[2]+(lw)Tei[3]+(lw)Tei[4]+(lw)Tei[5] ) / (lw)6 ) ;
            //_r.Ra_AN = ( Rai[0]+Rai[1]+Rai[2]+Rai[3]+Rai[4]+Rai[5] )/6; // ������ ��������� 12.10.2018 13:30 .


              _r.KtpRa_AN_pr   = (w) ( ( (lw)KtpRa_pr  [0] + (lw)KtpRa_pr  [1] + (lw)KtpRa_pr  [2] +
                                         (lw)KtpRa_pr  [3] + (lw)KtpRa_pr  [4] + (lw)KtpRa_pr  [5]  ) / (lw)6 );
              _r.KtpRa_AN_nepr = (w) ( ( (lw)KtpRa_nepr[0] + (lw)KtpRa_nepr[1] + (lw)KtpRa_nepr[2] +
                                         (lw)KtpRa_nepr[3] + (lw)KtpRa_nepr[4] + (lw)KtpRa_nepr[5]  ) / (lw)6 );



             if ( _r.INN_def_AN )
             { // ���� INN ���������� � 90���
               _r.INN0 = ( IN0i[0]+IN0i[1]+IN0i[2]+IN0i[3]+IN0i[4]+IN0i[5] )/6;
             }
             else
             {
               cx = 0 ;
               _r.INN0 = 0 ; // ������������� ������� .
               for ( iTmo = 0; iTmo <= 5; iTmo++ )
                {
                  ax = IN0i[iTmo] ;

                  if ( ax == 0x1fff ) cx++ , ax = _Id_nom(0.10) ; //"Id_nom(0.10)" - ������������ ������� �������� ����.����.

                  _r.INN0 += ax ;

                  if ( iTmo == 5 )
                  {
                    if ( cx >= 2 ) /*_r.INN0 = 0 ,*/ mSet_ServiceMsg ( _Srv_AN_Err );
                    _r.INN0 /= 6 ;
                  }
                }
             }

          #ifdef _SIFU2_
              _or.INN0_2_ = _r.INN0 ;
          #endif

              _r.K_Kompen_Ud = ( Ud_AN[0]+Ud_AN[1]+Ud_AN[2]+Ud_AN[3]+Ud_AN[4]+Ud_AN[5] ) / 6 ;

              if ( _r.Te_AN != 0 /*&& _r.Ra_AN != 0*/ )
               {
                mSet_ServiceMsg ( _Srv_AN_Ra_Te );             // "R�,Te ����������"
                //output_s ( _AN_Ra_Te ) ;
               }
               kn_Label = 0 , kp_Label = 0 , kpr_Label = 0 ;
               AN_Label = k110 ;
            }
            else

         case k14 :
            {
                AN_Label = k14 ;
                if ( ax_ud < _Ud_nom(0.02) )
                {
                  iTei++ ; // ��������� �� ��������� ����� ������� ��� �������� ���������. �������� .
                  an_time = Timer1_Ovr ;
                  AN_Label = k0;
                }
// ���� ����� �������� Ud ���������, ������������� �� � ����������
                if ( (u)((w)(Timer1_Ovr-time_anOvr)) > _Sec(5.0) )
                {
                   mSet_ServiceMsg ( _Srv_AN_Av ) ; // "�� o���������� !"
                   //output_s ( _AN_Av ) ;
                   return 1;
                }
            }
            break;

         case k110 :
              c_err = AN_Kreg () ; // ������� ������������� �� .
              //if ( c_err == 1) mSet_ServiceMsg ( _Srv_AN_Err ) ; // "������ ������� !"
              //if ( c_err == 1) output_s ( _AN_Err ) ;
              if ( c_err == 0 )  // ������� ������������� �� ������ ���������� "0" :
               {
                mSet_ServiceMsg ( _Srv_AN_Kreg );              // "�i,Kp ����������"
                //output_s ( _AN_Kreg ) ;
                AN_Label = k111 ;
               }
              else
               {
                 return 1 ; // ����� ������ .
               }
            break;

         case k111 :
              S.Alfa = _r.S_Alfa_Start ;
              mVkl_Imp( _VR1_imp );
              Prg.all |= _RegTok ; /* ���. ��������� ����. */
              OuRegS_dop_kod = _Id_nom( 0.01 ); // ������� ���� 1% ��� ���������� "U0-������".
              iTei = 0;
              an_time = Timer1_Ovr ;
              AN_Label = k112 ;
            break;

         case k112 :
              if ( iTei > 5 ) //������  ������� "_r.RevU0"
              {
                lax = (slw)OIRT_AN[0]+(slw)OIRT_AN[1]+(slw)OIRT_AN[2]+
                      (slw)OIRT_AN[3]+(slw)OIRT_AN[4]+(slw)OIRT_AN[5] ;
                lax /= (slw)(sw)6 ;
                _r.RevU0 = (u)(sw)(slw)lax ;
                OuRegS_dop_kod = 0;
                Prg.all = _Sled | _Blok_upr ; /* ����. ����������. */
                AN_Label = k12 ;
              }
              else if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec( 0.5 ) )
              {
                an_time = Timer1_Ovr ;
                OIRT_AN[iTei] = OIRT ;
                iTei++ ;
              }
            break;

  default:
        case k12 :
                 an_time = Timer1_Ovr ;
                 AN_Label = k13 ;
        case k13 :
            S.Alfa = _r.S_Alfa_Max ;
            if ( (u)((w)(Timer1_Ovr-an_time)) > _Sec ( 0.5 ) )
            {
              AN_Label = k00 ;
              return 0 ;
            }
            break;
    }
    return 4;
}


// ************************ ������ ��� Tm *********************************

word ANastr_Tm (void)
{

//  lword lax ;
    word ax, ax_ud, ax_id ;
    static byte pulse, flg_max ;
    static word an_time, Timer_AN;

    ax_id = Id_dop_kod ;
    if ( (sw)ax_id < (sw)0 )  ax_id = ~ax_id + 1 ;
    ax_ud = UdSr ;
    if ( (sw)ax_ud < (sw)0 )  ax_ud = ~ax_ud + 1 ;

    do { Timer_AN = Timer1_Ovr , ax = timer1 ; } while ( Timer_AN != Timer1_Ovr ) ;
    Timer_AN <<= 8 ;      //  �� ��������������� ������� �������� �������
    Timer_AN  += (ax>>8); // ��� ������ ������� ������� ��� ����� �����-
                    // ������ �������� � ��������� 0.25����-16.7���.

    switch ( AN_Label)
    {
        case 0 :
		   Id_for_Imax[0] = 0 ;
		   Id_for_Imax[1] = 0 ;
		   Id_for_Imax[2] = 0 ;
		   T_for_Imax[2]  = 0 ;
		   T_for_Imax[1]  = 0 ;
		   T_for_Imax[0]  = 0 ;
		   k_AN = 0;
           iTmi = 0;
           flag_Tm = 0;
		   AN_Label++ ;
           break;

		case 1 :
		   Id_max_AN = 0;
           Id_max_tmp_AN = 0;
           n_izm_AN = 0;           // �-�� ��������� (�������) ����� ���������
           flg_max = 0;
           S.Alfa = _Grad(90) ;
           an_time = Timer_AN ;
           AN_Label++ ;
           break;

        case 2 :
           if ( (u)((w)(Timer_AN-an_time)) > _fSec( 2.0 ) )
		   		{
                     if ( flag_Tm == 1)  S.Alfa = Last_Angle_Tm;
                     else
                     {
                     S.Alfa = _r.Alfa0_forTm_AN - (_r.Kratn_5_AN / 5) * _Grad(5) * k_AN ;
                     Last_Angle_Tm = S.Alfa;
                     }
                     an_time = Timer_AN ;
					 AN_Label++ ;
                }
           break;

		case 3 :

// �������� �� ������
           if ( (ax_id > _Id_nom( 2.1 )) || (S.Alfa <= _r.S_Alfa_Min) )
		   		{
                    S.Alfa = _r.S_Alfa_Max;
                    return 1;
                }

//           Id_for_Imax[2] = Id_for_Imax[1];
           Id_for_Imax[1] = Id_for_Imax[0];
           Id_for_Imax[0] = ax_id;
/*
		   T_for_Imax[2] = T_for_Imax[1];
		   T_for_Imax[1] = T_for_Imax[0];
		   T_for_Imax[0] = Timer_AN ;
*/
 // ����� ����������� ��� � 3,3 ��
    if ( pulse != (b)Puls_counter )
    {
        pulse = (b)Puls_counter ;

    // ���� � ������� ������� T_AN_ust �� ��� ��������� �������� ����,
    // �� ���� �� ��������� ���� (������)
           if ( ((u)((w)(Timer_AN-an_time)) > _r.T_AN_ust)  && (Id_max_AN == 0) )
           {
                k_AN++ ;
                AN_Label++ ;
           }

// ������ ������� (�������) ����������� ���������
           if ( (Id_max_tmp_AN != 0) && (ax_id < Id_max_tmp_AN ) ) flg_max = 1 ;

    // ����������� ��������� ����
           if ( (ax_id > _Id_nom( 0.4 )) && (ax_id > Id_max_tmp_AN) && ( flg_max == 0 ) )
           { Id_max_tmp_AN = ax_id;
             tmax_tmp_AN = Timer_AN;
           }

           if ( (ax_id > _Id_nom( 0.4 )) && (ax_id < Id_max_tmp_AN) )
                n_izm_AN++;

           if ( n_izm_AN > 10 )
           {
                Id_max_AN = Id_max_tmp_AN ;
                tmax_AN = (tmax_tmp_AN - an_time); // �� 90 ���.
           }

/*
           if ( (ax_id > _Id_nom( 0.5 )) && (ax_id <= Id_for_Imax[1]) && (ax_id <= Id_for_Imax[2]) )// && (u)((w)(Timer_AN-an_time)) > _fSec( 2.1 ) )
		   {
                Id_max_AN = Id_for_Imax[2] ;
                tmax_AN = (T_for_Imax[2] - an_time); // �� 90 ���.
           }
*/


// ���� ��c����� �������
           if ( (Id_max_AN >= _Id_nom( 1.0 )) && (Id_max_AN <= _Id_nom( 2.1 )) )
                {
                AN_Label = 5; // �� �����
                }
           else if ( Id_max_AN != 0 )
				{
					k_AN++ ;
					AN_Label++ ;
				}
    }

		   break;

	    case 4 :
		   S.Alfa = _r.S_Alfa_Max ;
           if ( ax_ud <= _Ud_nom( 0.03 ) )
                { AN_Label = 1;   // �� ��������� ����
                }
		   break;

		case 5 :
		   S.Alfa = _r.S_Alfa_Max ;
           if ( ax_ud <= _Ud_nom( 0.03 ) )  AN_Label++ ;
		   break;

        case 6 :
		   Tm_def_AN() ;
           Tmi[iTmi] = _r.Tm_AN;

           AN_Label = 1;
           flag_Tm = 1;


           if ( iTmi++ == 9)
           {
                _r.Tm_AN = (Tmi[0]+Tmi[1]+Tmi[2]+Tmi[3]+Tmi[4]+Tmi[5]+Tmi[6]+Tmi[7]+Tmi[8]+Tmi[9])/10; //��. ��������������
                AN_Label = 0 ;
                return 0 ;
           }
          // iTmi++;
           break;
            //---------
/*        default:
        case 50 :
       //     time...
        S.Alfa = _r.S_Alfa_Max ;
                    if ( c_err == 1) mSet_ServiceMsg ( _Srv_AN_Av ) ;// "�� o���������� !"
                    //if ( c_err == 1) output_s ( _AN_Av ) ;
                    else if ( c_err == 4 ) break;
                    else mSet_ServiceMsg ( _Srv_AN_Tm ); // "Tm ����������."
                    //else output_s ( _AN_Tm ) ;
  */
     }
	return 4;
}


// ************************ ����������� Tm *********************************

void Tm_def_AN(void)
{
        word iTeo, iTmo, Min_AN ;
        sword ax ;
        lword lax ;

        Min_AN = 0xffff ;

    // ���������� ���������� � ������, ������� 5.
        if ( (_r.Te_AN - (_r.Te_AN/5)*5 ) > ( ((2*_r.Te_AN+5)/10)*5 - _r.Te_AN)  )
            _r.Te_AN = ((2*_r.Te_AN+5)/10)*5;
        else  _r.Te_AN = (_r.Te_AN/5)*5;

    iTeo = _r.Te_AN / 5 - 1; // Begin from 0

        for ( iTmo = 0; iTmo <= 79; iTmo++ )
        {
            lax = tmax_AN * 256 ;    // tmax_AN[�����]*0,256 = [��]
            ax = (sw)((w)(lax/100) - To_x10[iTmo][iTeo]) ; // "/100" = 1/1000*10, �.�. T_x10.

            if ( ax < 0 ) ax = ~ax + 1 ;       // ax = [ms*10]

            if ( (To_x10[iTmo][iTeo] != 0) && (Min_AN > (w)ax) )
            {
                Min_AN = ax ;
                _r.Tm_AN = iTmo;
            }
        }
        _r.Tm_AN = (_r.Tm_AN + 1)*5; // [ms]
    }


    // ************************ ����������� Ki, Kp *****************************

word AN_Kreg (void)
{

  static double  d_ax, d_kp, d_ti, d_ti_pr, d_Tpp_AN_pr, d_Tpp_AN_nepr, d_Te_AN, d_Kt, d_KtpRa_AN_pr, d_KtpRa_AN_nepr, d_KoefDempfirRT ;


// -------------   ��������� �� ������������� ��������� � double.


  //d_Kt = (d)_Id_Nom / (d)_sr.NOM.Id.fe ;  // ���������  NOM.Id.fe = 1�����/1A

   d_Kt = 100. / (d)_sr.NOM.Id.fe ;  // ���������  NOM.Id.fe = 1�����/1A

   d_KoefDempfirRT = (d)_r.KoefDempfirRT / 256. ;

   d_Te_AN = (d)_r.Te_AN / 64. / 1000. ;  //  ��������� �� ��������� "64" � "1.0" � �� "����" � "���".

   d_KtpRa_AN_pr   = (d) _r.KtpRa_AN_pr   / 64. ;

   d_KtpRa_AN_nepr = (d) _r.KtpRa_AN_nepr / 64. ;

 //d_Tpp_AN_nepr   = (d)_r.Tpp_AN_nepr / 1000. ; // 16.06.2020 - �� ���������� �������� "T�� ��-������." = "Te" .
   d_Tpp_AN_nepr   = d_Te_AN ;

   d_Tpp_AN_pr     = (d)_r.Tpp_AN_pr  / 1000. ;


// --------------          ������.

// --------------     ����� ������������ ����.

                // => ��������  ��.���������  d_K_RT: "�����.�������� / ( ��� * �����.���� )"

        d_ax = ( d_KtpRa_AN_nepr * d_Kt );



// �� �������
//   d_kp = ( 8.5 * d_KoefDempfirRT * d_Te_AN / d_Tpp_AN_nepr - 1.) / d_ax ;

//   d_ti = d_ax * d_Tpp_AN_nepr*d_Tpp_AN_nepr / ( 18. * d_Te_AN );


// �� ������
   d_kp = ( 6.0 * d_Te_AN / d_Tpp_AN_nepr - 1.) / d_ax ;

   d_ti = d_ax * d_KoefDempfirRT * d_KoefDempfirRT * d_Tpp_AN_nepr*d_Tpp_AN_nepr / ( 9. * d_Te_AN );








// --------------     ����� ������������ ����.

   d_ti_pr = d_Tpp_AN_pr * ( d_KtpRa_AN_pr * d_Kt ) / 4.24 ;


// --------------  ��������� �� double � ������� ����������.

//              ��������� �� "1 / ���"   �  => "���_�����(����)*64" =>


   an_KRTP   =  d_kp * 256.;

   an_KRTNI  =  d_ti * 1000. * 64.;

   an_KRTPRI =  d_ti_pr * 1000. * 64.;



#ifdef _SIFU2_
   // ---
   // ��� 12�� �������� ������� � ��2 �������������� ���������� , �� �� ���������� ...
   an_KRTNI_2_   = an_KRTNI ;
   an_KRTP_2_   = an_KRTP ;
   an_KRTPRI_2_ = an_KRTPRI ;
#endif


//-------------------------------------------------------------------------------------------------

    return 0 ;
}
