
//   ��������� ������� ����
//
//--------------------------------------------------------

void Revers_Pola ( void )
  {
    #ifdef _Rev_Pola   // ���� ������� �������� ������� ����.

    word ax , bx ;
    //byte bx ;

    // RP_Pz.all = 0 ;

    /*
      RP_Pz._.prev_delt  = 0 ; //����� �������� ���������� ������ ����.����.
      // � ������ ���������� ����� �������� �������� ����������� �����������
      if ( ( RP_Pz._.Napravl == 0 && (sw)ZISkor >= 0 )
                                      ||
           ( RP_Pz._.Napravl == 1 && (sw)ZISkor <  0 ) )
          {
           //- �������� ���������� ������ �������� �������� � �������� --//
           //- �������� � �������� ������.                             --//
           ax = ZISkor - Skor ;

           if ( (sw)ax > (sw)_Delt_Sk || (sw)ax < (sw)(~_Delt_Sk+1) )
             { //- ��������� �������� ���������� ������ ����. ����.
               RP_Pz._.prev_delt = 1 ;
             }
          }

  RP_Pz._.need_rever = 1 ;  // ��������� ������� ������� ���� �������

  // �������� �� ������������� ������� ����
  for ( bx = 0 ; bx < 3 ; bx++ )
    {
     if ( bx == 0 )
      {
       //-- �������� �������������� ����� ������� �� ��� --//
       //-- � ����������� �����������.                   --//
        ax = OuRegS_dop_kod ;
      }
     else if ( bx == 1 )
      {
       //-- �������� ������������ ����� �������� �������� � �������� --//
       //-- �������� � ����������� �����������.                       --//
        ax = ZISkor - Skor ;
      }
     else
      {
       if ( RP_Pz._.prev_delt == 1 )  goto rp ;
       //-- �������� ������������ ����� ��������     --//
       //-- �������� � ����������� �����������.      --//
       ax = ZISkor ;
      }

        if ( (sw)ax < 0 ) // ���� �����
          {
           // � ����������� ������������� - ����� ������� � ����� �� �����
           if ( RP_Pz._.Napravl == 1 )  { RP_Pz._.need_rever = 0 ;  goto rp ; }
          }
        else              // ���� �����.
          {
           // � ����������� ������������� - ����� ������� � ����� �� �����
           if ( RP_Pz._.Napravl == 0 )  { RP_Pz._.need_rever = 0 ;  goto rp ; }
          }
    }
       rp :
                   */


    //if ( RP_Pz._.Napravl == 0 /* && */)
    //  {
    //      _r.Iv_porg_Min ;
    //  }

    //����������/������ �� ���������� ������� ���� (�������� �� ���� �����).
    if ( (w)IDV < (w)_r.RIDRR )
      {
       RP_Pz._.razr_Rev_P = 1 ;   //����������
      }
    else
      {
        RP_Pz._.razr_Rev_P = 0 ;
        if ( RP_Pz._.Not_Rev_P == 1 )  mSet_ServiceMsg ( _Srv_Not_Nul_Id ) ;
      }
   // ����������� ����� ����������� ���� �����������
    if ( (sw)V.Iv < 0 )  RP_Pz._.znak_Iv  = 1 ;
    else                 RP_Pz._.znak_Iv  = 0 ;

    RP_Pz._.znak_Fvz = 0 ;

    if ( _r.Cfg2._.Rev_Pola == 1 ) // ���� � ������-� ���., "����� ����".
      {
        if ( Prg._.RegSk == 1 )
          {
        //-------------------------------------------------------
        // �������� ������� � ������ �� �� ���� ��� ����� ������������.
              ax = (sw)( (slw)OuRegS_long * (slw)(sw)_r.Mashtab_Idz_Ivz >> 16 ) ; //

              if ( (sw)ax < 0 ) /*ax = ~ax + 1 ,*/ RP_Pz._.znak_Fvz = 1 ;
            }
          else  ax = 0 ;

          // ������������ �� ������������ ������
          if       ( (sw)ax > (sw)_Fv_nom( 1.0 ) )  ax = _Fv_nom( 1.0 ) ;
          else if  ( (sw)ax < (sw)_Fv_nom(-1.0 ) )  ax = _Fv_nom(-1.0 ) ;
          V.Fv_zad = ax ;

         RP_Pz._.Revers_Pol = 0 ;

        //�������� ���������� �������� ����
        if ( RP_Pz._.Napravl == 0 && RP_Pz._.znak_Fvz == 1 )
          {
            RP_Pz._.Revers_Pol = 1 ;
            // ���� ��� ����� ����� ������� ��� ������. �������
            if  ( RP_Pz._.razr_Rev_P == 0 )     V.Fv_zad = 0 ;
            else // ���� ����������
              {
                // ���� ��� ����� ����� ������� - ��� ����������� ������ ���. �����.
                if ( (sw)V.Iv > (sw)(~_r.Iv_porg_Min + 1 ) )
                  {
                   V.Fv_zad =  (~_r.Iv_porg_Min+1) + _Fv_nom(-0.02) ;
                   // � ����� ��� �������
                   if ( RP_Pz._.Not_Rev_P == 1 )  mSet_ServiceMsg ( _Srv_Not_Iv ) ;
                  /*P_Pz._.Revers_Pol = 1*/  // OuRegS_dop_kod  = 0 ;
                  }
                else                              RP_Pz._.Napravl = 1 ; // ����� �����������
              }
          }
        else if ( RP_Pz._.Napravl == 1 && RP_Pz._.znak_Fvz == 0 )
          {
            RP_Pz._.Revers_Pol = 1 ;
            // ���� ��� ����� ����� ������� ��� ������. �������
            if  ( RP_Pz._.razr_Rev_P == 0 )     V.Fv_zad = 0 ;
            else // ���� ����������
              {
                // ���� ��� ����� ����� ������� - ��� ����������� ������ ���. �����.
                if ( (sw)V.Iv < (sw)_r.Iv_porg_Min  )
                  {
                   V.Fv_zad =  _r.Iv_porg_Min + _Fv_nom(+0.02) ;
                   // ���� ����� ��� �������
                   if ( RP_Pz._.Not_Rev_P == 1 )  mSet_ServiceMsg ( _Srv_Not_Iv ) ;
                  /*P_Pz._.Revers_Pol = 1*/  // OuRegS_dop_kod  = 0 ;
                  }
                else                                    RP_Pz._.Napravl = 0 ;  // ����� �����������
              }
          }
       else
          {
           RP_Pz._.Malen_Iv = 0 ;
           if ( RP_Pz._.Napravl == 0 && RP_Pz._.znak_Fvz == 0 ) //���� ����� ����
             {
                // ���� ������� �� ��� ������ ���. ���, � ��� ����������� ������ ���. �����.
                if ( ((sw)V.Fv_zad > (sw)_r.Iv_porg_Min) && ((sw)V.Iv < (sw)_r.Iv_porg_Min ) )
                  {
                   V.Fv_zad =  _r.Iv_porg_Min + _Fv_nom(+0.02) ;
                   RP_Pz._.Malen_Iv = 1 ;
                  }
             }
           else if ( RP_Pz._.Napravl == 1 && RP_Pz._.znak_Fvz == 1 ) //���� ����� ����
             {
                // ���� ������� �� ��� ������ ���. ���, � ��� ����������� ������ ���. �����.
                if ( ((sw)V.Fv_zad < (sw)(~_r.Iv_porg_Min + 1 )) && ((sw)V.Iv > (sw)(~_r.Iv_porg_Min + 1 ) ) )
                  {
                   V.Fv_zad =  (~_r.Iv_porg_Min+1) + _Fv_nom(-0.02) ;
                   RP_Pz._.Malen_Iv = 1 ;
                  }
             }
          }


       if ( RP_Pz._.Revers_Pol == 1 ) // ���� ������� ������� ���������
          {
            if ( (w)(Timer1_Ovr - Time_RP ) > _Sec( 2.0 ))
              {
                mSet_ServiceMsg( _Srv_AvarRevers ) ;
                RP_Pz._.Not_Rev_P = 1 ;  // ��� �������
              }
          }
       else  Time_RP = Timer1_Ovr , RP_Pz._.Not_Rev_P = 0 ;


   /*----- ������������ � �����������/�������� ������� ����  ----*/

      //��� �������  ��� ����� ���� ����. ����������� ������ �� ����������
      if ( RP_Pz._.Revers_Pol == 1 || RP_Pz._.Malen_Iv == 1 )  ax = 0 , bx = 0 ;
      else  ax = _r.OuRSMaxMost1 , bx = _r.OuRSMaxMost2 ;

       if ( (sw)OuRegS_dop_kod >= 0 )
        {
          if ((sw)OuRegS_dop_kod > (sw)ax )  OuRegS_dop_kod = ax , Prz._.int_p = 1 ;
        }
       else
        {
          if ((sw)OuRegS_dop_kod < (sw)bx )  OuRegS_dop_kod = bx , Prz._.int_m = 1 ;
          OuRegS_dop_kod = ~OuRegS_dop_kod + 1 ;
        }
      }

 #endif

    return ;
  }

//--------------------------------------------------------

