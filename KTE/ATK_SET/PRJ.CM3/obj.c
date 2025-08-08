
//     ��������� ���������.
//
//--------------------------------------------------------
//    ��������� ���������� ���� �������� ������� ���
//  ������������ ������� � �������������� ���������.
word read_rezerv ( void )
  {
    register word ax ;

    // ��� �������������� ��������� ����������� ��������� :
    //   1. �� ������ ������� ������� ������ ���� ��������� , ��������������� ���������� ���� .
    //   2. ������ ���������� ���� , ��� ������ ������� ������� , ������ ����������� � ������� .
    //   3. ���������� ���� ��� ����������� ������� ������� ������ ���� "= 1" , ������ "1" ,
    // � �� "0" , ��� ����� .
    //   4. � ������� �������� ���������� �������� ���������� ������ "= 1" .
    //   5. ������� "ax = 0" ����������� , ��� ���� , ����� ���������� ������������ ������ .
    //   6. ��� �������������� ������� ��������� ���� "else" ��� �������� ���������� ������
    // (��� � ������� ����) , ���� ��������� ���������� ����� ��� ������������� ������� �� "= 0" .
    //   7. � ������ ������� ������� ���������� ����� ������� � ��������� ������� ������� .

    //if      ( bi_KTE_rezerv1 == 1 ) ax = 1 ;
    //else if ( bi_KTE_rezerv2 == 1 ) ax = 2 ;
    //else                            ax = 0 ;

  // ��� ���������� ������ 12-�������� ����� :
  #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
    if      ( bi_Vedusch == 1 && bi_Vedom == 0 && bi_Both == 0 ) ax = 2 ; // ��1,��2
    else if ( bi_Vedusch == 0 && bi_Vedom == 1 && bi_Both == 0 ) ax = 3 ; //           ��3,��4
    else if ( bi_Vedusch == 0 && bi_Vedom == 0 && bi_Both == 1 ) ax = 1 ; // ��1,��2 + ��3,��4
    else                                                         ax = 0 ;
  #else
    ax = 0 ; // ���� ��� �������
  #endif

    return ax ;
  }
//--------------------------------------------------------


//     ��������� ���������.

word  ObjPrg ( word num )
  {
  static word ax ;
         word skor ;
         lword lax;
  //---
    if ( num != _Obj_c_Init && num != _Obj_c_Common_avar ) // ������������� � ����� ������ � ����� ������ .
     {
        // ������ �� ��������� ���������� .
      if (  Isp.all != 0 ) return 1 ;
     }
   //----
    switch ( num )
    {    // ��������� ��������� ��������� ��� ������� ��������� �������.
      case _Obj_c_Init :

        canId_zad = 0 ;
        flgO.all = 0 ;
        ATK_flg.all = 0 ;
        OuRegS_ogr = 0 ; // ������������ ������� �� ��� �� �������� � �������� .
        Agregat = _V_REZERVE;
        Time_Reversor = Timer1_Ovr ;
        TimeDelay_Temper = Timer1_Ovr;
        Trg_Pusk = 0;
        Pusk_old = 0;
        Trg_IzmTemp = 0;
        Trg_BegTemp = 1;
        T_CAN0 = Timer1_Ovr ;
        Time_RMS_On = Timer1_Ovr;
        Time_RMS_Off = Timer1_Ovr;

        // �������������� Kf ��� ����������� ������� :
        Kform = _sqr2_3mask ; // 0.816

        //---- ��� ������������ �����������
        Time_tst  = Timer1_Ovr;
        Time_tst_PIU = Timer1_Ovr;
        Time_bo_SN_On = Timer1_Ovr;
        channelTemp = Izm_seq[0];              // ��������� ������ ������
        //   PDF[0].Bits._.Count_Beg = 1;  // �������� ������� ����������� � 0-�� (1-��) ������
        IzmTempLabel = 0;
        Av_Dat = 0;
        Avv_Dat = 0;
        bo_EndIzm = 0;


        CLR_CS_Temp();                        // ����� ������� (4� �����).
        for (ax = 0; ax < _MaxChannel; ++ ax)
        {
          TIzm[ax].Freq = 0 ;
          TIzm[ax].V_Out= 0 ;
          TIzm[ax].Out  = 0 ;
          TIzm[ax].I_Out= 0 ;
        }
        bo_KontrVkl = 0;
        TimeDelay = Timer1_Ovr;
        TimeBlockIzm = Timer1_Ovr;
        for (ax = 0, lax = 1;((lax & _Pr2_Tizm14)== 0)&&(ax <= 31); ++ax)
        {
          lax <<=1;
        }
        //Time_BV = Timer1_Ovr;
        Bit_PrAvar = ax;
        //------- ��� ������������
        t_fan = 0, Id_fan = 0;
        timerVentAvar = Timer1_Ovr;
        bo_VklVent_1_2_3 = 0; // ���-�� ��� ����, ���/���� �������� ������ bo_vent_otkl/bo_vent_vkl //LPC_GPIO1->SET = 0x01 << 1;
        bo_vent_otkl;
        FanSpeedMax = 1;
        // ��������� ���������� ������������.
        controlFan(0) ;

        break;
        //-------
         // ��������� ��������� ��� ������� ��������� ������� ��� ��������
        // �� ������ � ��.����������.
      case _Obj_c_DS1_Init :
        break;
        //-------
         // ��������� ��������� ����� ����� �������� , �������� , ��� ������� ��������� .
      case _Obj_c_Common_avar :

        // ����� ������ ����������� ���� � ���������� ������� � ��� ����������� ��������� ���������� :

        // ���������������� ����� ���� ��������� ��������� :
        mClr_ServiceMsg( _Srv_ATKR_Predupr | _Srv_Err_PereclRegim ) ;
      //mClr_ServiceMsg( _Srv_Err_SA9_PU   | _Srv_ATK_ne_Vybran ) ;   // DAN 12.04.2025
        mClr_ServiceMsg( _Srv_Pusk_off     | _Srv_Link_ATK_otkl ) ;
      //mClr_ServiceMsg( _Srv_Reversor1    | _Srv_Reversor2 ) ;          DAN 12.04.2025
      //mClr_ServiceMsg( _Srv_Reversor1On  | _Srv_Reversor2On ) ;       DAN 12.04.2025
        mClr_ServiceMsg( _Srv_AP2_ne_vRabote ) ;
        mClr_ServiceMsg( _Srv_CAN_avarATK1 | _Srv_CAN_avarATK2 ) ;
        mClr_ServiceMsg( _Srv_CAN_avarATKR | _Srv_NotWorkATK1) ;
        mClr_ServiceMsg( _Srv_NotWorkATKR  | _Srv_ATK1_Predupr ) ;
        mClr_ServiceMsg2( _Srv2_NotWorkATK2| _Srv2_ATK2_Predupr ) ;
        mClr_ServiceMsg2( _Srv2_ErrNumbATK | _Srv2_ErrNumbAbon ) ;
      //mClr_ServiceMsg2( _Srv2_ST1err     | _Srv2_ST2err ) ;         // DAN 12.04.2025
      //mClr_ServiceMsg2( _Srv2_SM1err     | _Srv2_SM2err ) ;         // DAN 12.04.2025
      //mClr_ServiceMsg2( _Srv2_ST1middle  | _Srv2_ST2middle ) ;      // DAN 12.04.2025
      //mClr_ServiceMsg2( _Srv2_SM1middle  | _Srv2_SM2middle ) ;      // DAN 12.04.2025
        mClr_ServiceMsg2( _Srv2_AP2_Predupr ) ;
        if (!Prg._.Gotovn && bo_Avar)
        {
          Trg_Pusk = 0;
        }
        if (bi_Pusk_1)
        {
          if (!Pusk_old)
          {
             Trg_Pusk = 1;
          }
        }
        Pusk_old = bi_Pusk_1;
        if ( bi_VV1_stator     == 0 ) mSet_AvarMsg2( _Av2_VV1_stator ) ;   //DAN 12.04.2025
        if ( bi_VV3_trans      == 0 ) mSet_AvarMsg2( _Av2_VV3_trans ) ;    //DAN 12.04.2025


        /* DAN 12.04.2025
        if ( flgO._.V_rezerve == 1 ) // ���� ��� � ������� � ���� ��������� , ����� ��������� �� ���������� ����� ����� :
        {
          mClr_ServiceMsg( _Srv_NoLinkCAN2_atk1 | _Srv_NoLinkCAN2_atkr ) ;
          mClr_ServiceMsg2( _Srv2_NoLinkCAN2 ) ;
        }
        //---
        // �������� ������������� ������ ������� :
        if ( ( bi_Ludi == 1 && (bi_Gruz == 1 || bi_Negabarit == 1) ) ||
             ( bi_Gruz == 1 && (bi_Ludi == 1 || bi_Negabarit == 1) ) ||
             ( bi_Negabarit == 1 && (bi_Ludi == 1 || bi_Gruz == 1) ) )
        {
          mSet_ServiceMsg( _Srv_Err_PereclRegim ) ;
        }

        // �������� ������������� �/� ������� �������������� :
        if ( bi_ST1_atk1 == 1 && bi_ST1_atkR == 1 ) mSet_ServiceMsg2( _Srv2_ST1err ) ;
        if ( bi_SM1_atk1 == 1 && bi_SM1_atkR == 1 ) mSet_ServiceMsg2( _Srv2_SM1err ) ;
        if ( bi_ST2_atk2 == 1 && bi_ST2_atkR == 1 ) mSet_ServiceMsg2( _Srv2_ST2err ) ;
        if ( bi_SM2_atk2 == 1 && bi_SM2_atkR == 1 ) mSet_ServiceMsg2( _Srv2_SM2err ) ;

        // �������� �������� ��������� ������� �������������� :
        if ( bi_ST1_atk1 == 0 && bi_ST1_atkR == 0 ) mSet_ServiceMsg2( _Srv2_ST1middle ) ;
        if ( bi_SM1_atk1 == 0 && bi_SM1_atkR == 0 ) mSet_ServiceMsg2( _Srv2_SM1middle ) ;
        if ( bi_ST2_atk2 == 0 && bi_ST2_atkR == 0 ) mSet_ServiceMsg2( _Srv2_ST2middle ) ;
        if ( bi_SM2_atk2 == 0 && bi_SM2_atkR == 0 ) mSet_ServiceMsg2( _Srv2_SM2middle ) ;

        // ������� ������������� ��������� ������ �� , � ������� �������������� ������� ���������� ,
        // ������� , ���� ������������� ST1 , ST2 , SM1 � SM2 � ������ �� ������ , �������������� ���
        // ������ , �.�. ������������ �������� ������������ ������ ������ � ������ ���������� ,
        // �������� ������ :

        //---
        // �������� ������������ ������� ������ ��� :
        ax = 0 ;
        if ( _or.CfgO._.ATK1 == 1 ) ax += 0x0001 ;
        if ( _or.CfgO._.ATK2 == 1 ) ax += 0x0010 ;
        if ( _or.CfgO._.ATKR == 1 ) ax += 0x0100 ;
        //---
        // ST1���� = 1 -> ATK1 , SM1���� = 1 -> ATK1 .
        // ST1���� = 0 -> ATKR , SM1���� = 0 -> ATKR .
        // ST2���� = 1 -> ATK2 , SM2���� = 1 -> ATK2 .
        // ST2���� = 0 -> ATKR , SM2���� = 0 -> ATKR .
        //---
        // ST1���� = 1 -> ATKR , SM1���� = 1 -> ATKR .
        // ST1���� = 0 -> ATK1 , SM1���� = 0 -> ATK1 .
        // ST2���� = 1 -> ATKR , SM2���� = 1 -> ATKR .
        // ST2���� = 0 -> ATK2 , SM2���� = 0 -> ATK2 .
        //---
        // ������������ �������� ������� : �������/������� - ������� ��� ��� , ������� �������� �� ��������� �1 .
        // ��������� , ��� �������� ��������������� ST1 , SM1 , ST2 � SM2 � ��  ������� �� �� ����� ,
        // ��� � ���������� �������������� SA9 �� ������ :
        //---
        switch ( ax )
        {
          //-------------------------------- ���1 -------------------------------------------------
          case 0x0001 : // ���1 .
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � 0 ��� "����1 + ����.2" .
              if      ( bi_Dvig1 == 1 && bi_Dvig2 == 1 )
              {
                // ����� ������ "���1-���2" .
                if      ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - ������� , ���2 - ������� , ���R - � ������� .
                   flgO._.V_rezerve = 0 ; // ���1 � ������ .
                   bo_atkNmbrATK    = 1 ; // ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 2 ; // A��2 - ��� ������� .
                   //---
                   //�������� ���� CAN0 :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� �������� ������� - �������� ������� �������� � ������ ����� ���������� .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // �������� �������� ���� , �� ����� �� ��� ������ , ����� ������� ������ ��� ��������� � ������
                      // ��� � �������������� ���������������� ������ .
                 //}
                   //---
                   // ������������ ����� �������� �� ��������� � ���������� �� ���� ( ��� ������� ����� ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���1-���������" .
                else if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - ������� , ���2 - � ������� , ���R - ������� .
                   flgO._.V_rezerve = 0 ; // ���1 � ������ .
                   bo_atkNmbrATK    = 1 ; // ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 3 ; // A��R - ��� ������� .
                   //---
                   //�������� ���� CAN0 :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� �������� ������� - �������� ������� �������� � ������ ����� ���������� .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // �������� �������� ���� , �� ����� �� ��� ������ , ����� ������� ������ ��� ��������� � ������
                      // ��� � �������������� ���������������� ������ .
                 //}
                   //---
                   // ������������ ����� �������� �� ��������� � ���������� �� ���� ( ��� ������� ����� ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���2-���������" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                     {
                       // ���1 - � ������� , ���2 - ������� , ���R - ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }

                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���1 � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � -45 ��� "����1" .
              else if ( bi_Dvig1 == 1 && bi_Dvig2 == 0 )
              {
                // ����� ������ "���1" .
                if      ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1                                             &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0                                             )
                          // ��������� ����������������� �������������� ��������� 2 - ST2 � SM2 �� ����� �������� .
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - ������� , ���2 - � ������� , ���R - � ������� .
                   flgO._.V_rezerve = 0 ; // ���1 � ������ .
                   bo_atkNmbrATK    = 1 ; // ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 0 ; // ������� ���������� , ���������������� ����� .
                   //---
                   //��������� ���� CAN0 ��� ����������������� ������ :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // �� ������� ��������� �� ����������� ����� � ���������� ���������������� ������ .
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���������" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0                                             &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1   && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // ��������� ����������������� �������������� ��������� 2 - ST2 � SM2 �� ����� �������� ,
                          // ������ ��������� , ��� ��� �� � ������� , �.�. �� ������ ����� ���� ������ ���� .
                     {
                       // ���1 - � ������� , ���2 - � ������� , ���R - ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���1 � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � +45 ��� "����2" , ���� ������������� ������������� SA9 �� ������ .
              else
              {
                     // ������������� ������������� SA9 �� ������ :
                     if ( bi_Dvig1 == 0 && bi_Dvig2 == 0 )
                     {
                       mSet_ServiceMsg( _Srv_Err_SA9_PU ) ;
                     }
                     // ������������� SA9 �� ������ � +45 ��� "����2" :
                     else
                     {
                       // ����� ������ "���2" ���� "���������".
                       if ( (                                             bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1
                                                                       && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 ) ||
                            (                                             bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                                bi_ST1_atkR == 0 && bi_SM1_atkR == 0 &&   bi_ST2_atkR == 1 && bi_SM2_atkR == 1 ) )
                            // ��������� ����������������� �������������� ��������� 1 - ST1 � SM1 �� ����� �������� ,
                            // ������ ��� ������ "����.2 �� ������" ��������� , ��� ��� �� � ������� ,
                            // �.�. �� ������ ����� ���� ������ ���� .
                       {
                         mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                       }
                       else
                       {
                         // ������������ ��������� ������� �������������� .
                         mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                       }
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���1 � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
              }

              break ;

          //-------------------------------- ���2 -------------------------------------------------
          case 0x0010 : // ���2 .
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � 0 ��� "����1 + ����.2" .
              if      ( bi_Dvig1 == 1 && bi_Dvig2 == 1 )
              {
                // ����� ������ "���1-���2" .
                if      ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 0 ; // ���1 - ������� , ���2 - ������� , ���R - � ������� .
                   flgO._.V_rezerve = 0 ; // ���2 � ������ .
                   bo_atkNmbrATK    = 2 ; // ����� ���� ����� ���2 � ���� ������ .
                   flgO._.abonATK   = 1 ; // A��1 - ��� ������� .
                   //---
                   //�������� ���� CAN0 :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� �������� ������� - �������� ������� �������� � ������ ����� ���������� .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // �������� �������� ���� , �� ����� �� ��� ������ , ����� ������� ������ ��� ��������� � ������
                      // ��� � �������������� ���������������� ������ .
                 //}
                   //---
                   // ������������ ����� �������� �� ��������� � ���������� �� ���� ( ��� ������� ����� ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���2 �� ��������� ����������1 .
                   bo_Reversor2 = 1 ;
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
                // ����� ������ "���2-���������" .
                else if ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 0 ; // ���1 - � ������� , ���2 - ������� , ���R - ������� .
                   flgO._.V_rezerve = 0 ; // ���2 � ������ .
                   bo_atkNmbrATK    = 2 ; // ����� ���� ����� ���2 � ���� ������ .
                   flgO._.abonATK   = 3 ; // A��R - ��� ������� .
                   //---
                   //�������� ���� CAN0 :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� �������� ������� - �������� ������� �������� � ������ ����� ���������� .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // �������� �������� ���� , �� ����� �� ��� ������ , ����� ������� ������ ��� ��������� � ������
                      // ��� � �������������� ���������������� ������ .
                 //}
                   //---
                   // ������������ ����� �������� �� ��������� � ���������� �� ���� ( ��� ������� ����� ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���2 �� ��������� ����������1 .
                   bo_Reversor2 = 1 ;
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���1-���������" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                     {
                       // ���1 - ������� , ���2 - � ������� , ���R - ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }

                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���2 � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���2 � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���2 �� ��������� ����������1 .
                   bo_Reversor2 = 0 ;
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � +45 ��� "����2" .
              else if ( bi_Dvig1 == 0 && bi_Dvig2 == 1 )
              {
                // ����� ������ "���2" .
                if      (                                             bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                                                                      bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // ��������� ����������������� �������������� ��������� 1 - ST1 � SM1 �� ����� �������� /
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - � ������� , ���2 - ������� , ���R - � ������� .
                   flgO._.V_rezerve = 0 ; // ���2 � ������ .
                   bo_atkNmbrATK    = 2 ; // ����� ���� ����� ���2 � ���� ������ .
                   flgO._.abonATK   = 0 ; // ������� ���������� , ���������������� ����� .
                   //---
                   //��������� ���� CAN0 ��� ����������������� ������ :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // �� ������� ��������� �� ����������� ����� � ���������� ���������������� ������ .
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���2 �� ��������� ����������1 .
                   bo_Reversor2 = 1 ;
                   // ����� ������ :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���������" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if (                                             bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                            bi_ST1_atkR == 0 && bi_SM1_atkR == 0 &&   bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                          // ��������� ����������������� �������������� ��������� 1 - ST1 � SM1 �� ����� �������� ,
                          // ������ ��������� , ��� ��� �� � ������� , �.�. �� ������ ����� ���� ������ ���� .
                     {
                       // ���1 - � ������� , ���2 - � ������� , ���R - ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���2 � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���2 � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���2 �� ��������� ����������1 .
                   bo_Reversor2 = 0 ;
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � -45 ��� "����1" , ���� ������������� ������������� SA9 �� ������ .
              else
              {
                     // �������� ������������� SA9 �� ������ :
                     if ( bi_Dvig1 == 0 && bi_Dvig2 == 0 )
                     {
                       mSet_ServiceMsg( _Srv_Err_SA9_PU ) ;
                     }
                     // ������������� SA9 �� ������ � -45 ��� "����1" :
                     else
                     {
                       // ����� ������ "���1" ���� "���������" .
                       if ( ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1                                             &&
                              bi_ST1_atkR == 0 && bi_SM1_atkR == 0                                             ) ||
                            ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0                                             &&
                              bi_ST1_atkR == 1 && bi_SM1_atkR == 1   && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 ) )
                            // ��������� ����������������� �������������� ��������� 2 - ST2 � SM2 �� ����� �������� ,
                            // ������ ��� ������ "����.1 �� ������" ��������� , ��� ��� �� � ������� ,
                            // �.�. �� ������ ����� ���� ������ ���� .
                       {
                         mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                       }
                       else
                       {
                         // ������������ ��������� ������� �������������� .
                         mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                       }
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���2 � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���2 � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���2 �� ��������� ����������1 .
                   bo_Reversor2 = 0 ;
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
              }
          break ;

          //-------------------------------- ���R -------------------------------------------------
          case 0x0100 : // ���R .
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � 0 ��� "����1 + ����.2" .
              if      ( bi_Dvig1 == 1 && bi_Dvig2 == 1 )
              {
                // ����� ������ "���������-���2" .
                if      ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - � ������� , ���2 - ������� , ���R - ������� .
                   flgO._.V_rezerve = 0 ; // ���R � ������ .
                   bo_atkNmbrATK    = 3 ; // ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 2 ; // A��2 - ��� ������� .
                   //---
                   //������������� ���� ������� ����� ( ���1 ):
                   if ( can_setting( _CAN0_Port).addr != 1 )
                   {
                      can_setting( _CAN0_Port).addr = 1 ;
                      can_stop( _CAN0_Port ) = 1; // ��������� CAN ��� ����������� .
                   }
                   //---
                   //������������� ����� ������� ����� :
                   if ( _r.AddrDevice2 != 2 )
                   {
                      _r.AddrDevice2 = 2 ;
                      can_stop( _CAN0_Port ) = 1; // ��������� CAN ��� ����������� .
                   }
                   //---
                   //�������� ���� CAN0 :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� CAN-����� ��� , �� �������������� CAN :
                   if ( flgO._.CAN0_ok == 0 && flgO._.CAN0_init == 0 )
                   {
                      flgO._.CAN0_init = 1 ;
                      T_CAN0 = Timer1_Ovr ;
                      can_stop( _CAN0_Port ) = 1;
                   }
                   else if ( flgO._.CAN0_init == 1 )
                   {
                      // ����� 1 ��� ���������� ���� ������������� CAN :
                      if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(1))        flgO._.CAN0_init = 0 ;
                      // ����� 0.5 ��� �������� CAN :
                      else if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(0.5)) can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� �������� ������� - �������� ������� �������� � ������ ����� ���������� .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // �������� �������� ���� , �� ����� �� ��� ������ , ����� ������� ������ ��� ��������� � ������
                      // ��� � �������������� ���������������� ������ .
                 //}
                   //---
                   // ������������ ����� �������� �� ��������� � ���������� �� ���� ( ��� ������� ����� ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 1 ;  // ���R � ������ ������ ��������� ����������1 .
                   bo_Reversor2 = 0 ;  // ���R � ������ ������ �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���1-���������" .
                else if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                {
                   flgO._.Vedushiy  = 0 ; // ���1 - ������� , ���2 - � ������� , ���R - ������� .
                   flgO._.V_rezerve = 0 ; // ���R � ������ .
                   bo_atkNmbrATK    = 3 ; // ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 1 ; // A��1 - ��� ������� .
                   //---
                   //������������� ���� ������� ����� ( ���2 ):
                   if ( can_setting( _CAN0_Port).addr != 2 )
                   {
                      can_setting( _CAN0_Port).addr = 2 ;
                      can_stop( _CAN0_Port ) = 1; // ��������� CAN ��� ����������� .
                   }
                   //---
                   //������������� ����� ������� ����� :
                   if ( _r.AddrDevice2 != 1 )
                   {
                      _r.AddrDevice2 = 1 ;
                      can_stop( _CAN0_Port ) = 1; // ��������� CAN ��� ����������� .
                   }
                   //---
                   //�������� ���� CAN0 :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 1 )
                   {
                      can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� CAN-����� ��� , �� �������������� CAN :
                   if ( flgO._.CAN0_ok == 0 && flgO._.CAN0_init == 0 )
                   {
                      flgO._.CAN0_init = 1 ;
                      T_CAN0 = Timer1_Ovr ;
                      can_stop( _CAN0_Port ) = 1;
                   }
                   else if ( flgO._.CAN0_init == 1 )
                   {
                      // ����� 1 ��� ���������� ���� ������������� CAN :
                      if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(1))        flgO._.CAN0_init = 0 ;
                      // ����� 0.5 ��� �������� CAN :
                      else if ((u)((w)(Timer1_Ovr - T_CAN0)) > _Sec(0.5)) can_stop( _CAN0_Port ) = 0;
                   }
                   //---
                   // ���� �������� ������� - �������� ������� �������� � ������ ����� ���������� .
                 //if ( _or.CfgO._.Change_Vedush == 1 )
                 //{
                      // �������� �������� ���� , �� ����� �� ��� ������ , ����� ������� ������ ��� ��������� � ������
                      // ��� � �������������� ���������������� ������ .
                 //}
                   //---
                   // ������������ ����� �������� �� ��������� � ���������� �� ���� ( ��� ������� ����� ) :
                   if ( flgO._.abonATK != ATK2_NmbrATK && flgO._.CAN0_ok == 1) mSet_ServiceMsg2( _Srv2_ErrNumbAbon ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���R � ������ ������ �� ��������� ����������1 .
                   bo_Reversor2 = 1 ;  // ���R � ������ ������ ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
                // ����� ������ "���1-���2" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1 && bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0 && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                     {
                       // ���1 - ������� , ���2 - ������� , ���R - � ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }

                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���R � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ; // ���R � ������ ������ �� ��������� ����������1 .
                   bo_Reversor2 = 0 ; // ���R � ������ ������ �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � -45 ��� "����1" .
              else if ( bi_Dvig1 == 1 && bi_Dvig2 == 0 )
              {
                // ����� ������ "���������" .
                if      ( bi_ST1_atk1 == 0 && bi_SM1_atk1 == 0                                             &&
                          bi_ST1_atkR == 1 && bi_SM1_atkR == 1   && bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // ��������� ����������������� �������������� ��������� 2 - ST2 � SM2 �� ����� �������� ,
                          // ������ ��������� , ��� ��� �� � ������� , �.�. �� ������ ����� ���� ������ ���� .
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - � ������� , ���2 - � ������� , ���R - ������� .
                   flgO._.V_rezerve = 0 ; // ���R � ������ .
                   bo_atkNmbrATK    = 3 ; // ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 0 ; // ������� ���������� , ���������������� ����� .
                   //---
                   //��������� ���� CAN0 ��� ����������������� ������ :
                   Agregat = _ATK1 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // �� ������� ��������� �� ����������� ����� � ���������� ���������������� ������ .
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 1 ;  // ���R � ������ ������ ��������� ����������1 .
                   bo_Reversor2 = 0 ;  // ���R � ������ ������ �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���1" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if ( bi_ST1_atk1 == 1 && bi_SM1_atk1 == 1                                             &&
                          bi_ST1_atkR == 0 && bi_SM1_atkR == 0                                             )
                          // ��������� ����������������� �������������� ��������� 2 - ST2 � SM2 �� ����� �������� .
                     {
                       // ���1 - ������� , ���2 - � ������� , ���R - � ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���R � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���R � ������ ������ �� ��������� ����������1 .
                   bo_Reversor2 = 0 ;  // ���R � ������ ������ �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� SA9 �� ������ � +45 ��� "����2" :
              else if ( bi_Dvig1 == 0 && bi_Dvig2 == 1 )
              {
                // ����� ������ "���������" .
                if      (                                             bi_ST2_atk2 == 0 && bi_SM2_atk2 == 0 &&
                            bi_ST1_atkR == 0 && bi_SM1_atkR == 0 &&   bi_ST2_atkR == 1 && bi_SM2_atkR == 1 )
                          // ��������� ����������������� �������������� ��������� 1 - ST1 � SM1 �� ����� �������� ,
                          // ������ ��������� , ��� ��� �� � ������� , �.�. �� ������ ����� ���� ������ ���� .
                {
                   flgO._.Vedushiy  = 1 ; // ���1 - � ������� , ���2 - � ������� , ���R - ������� .
                   flgO._.V_rezerve = 0 ; // ���R � ������ .
                   bo_atkNmbrATK    = 3 ; // ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 0 ; // ������� ���������� , ���������������� ����� .
                   //---
                   //��������� ���� CAN0 ��� ����������������� ������ :
                   Agregat = _ATK2 ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   // �� ������� ��������� �� ����������� ����� � ���������� ���������������� ������ .
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���R � ������ ������ �� ��������� ����������1 .
                   bo_Reversor2 = 1 ;  // ���R � ������ ������ ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 1 ;
                   //---
                   bo_Vedushiy = 1 ;
                }
                // ����� ������ "���2" ��� ������������ ��������� ������� �������������� .
                else
                {
                     if (                                             bi_ST2_atk2 == 1 && bi_SM2_atk2 == 1 &&
                                                                      bi_ST2_atkR == 0 && bi_SM2_atkR == 0 )
                          // ��������� ����������������� �������������� ��������� 2 - ST2 � SM2 �� ����� �������� .
                     {
                       // ���1 - � ������� , ���2 - ������� , ���R - � ������� .
                       mSet_ServiceMsg( _Srv_ATK_ne_Vybran ) ;
                     }
                     else
                     {
                       // ������������ ��������� ������� �������������� .
                       mSet_PreduprMsg2( _Pr2_ShemaShK ) ;
                     }
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���R � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���R � ������ ������ �� ��������� ����������1 .
                   bo_Reversor2 = 0 ;  // ���R � ������ ������ �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
                }
              }
              //-------------------------------------------------------
              // ������������� ������������� SA9 �� ������ :
              else
              {
                   mSet_ServiceMsg( _Srv_Err_SA9_PU ) ;
                   //---
                   flgO._.Vedushiy  = 0 ;
                   flgO._.V_rezerve = 1 ; // ���R � ������� .
                   bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ���R � ���� ������ .
                   flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
                   //---
                   //��������� ���� CAN0 :
                   Agregat = _V_REZERVE ;
                   if( can_stop( _CAN0_Port ) == 0 )
                   {
                       can_stop( _CAN0_Port ) = 1;
                   }
                   //---
                   mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 0 ;  // ���R � ������ ������ �� ��������� ����������1 .
                   bo_Reversor2 = 0 ;  // ���R � ������ ������ �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 0 ;
                   flgO._.dvig_N1 = 0 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 0 ;
              }
          break ;

          default : // ����� ��� �� ����� , ��� ������ ������ ������ ������ .
            mSet_ServiceMsg2( _Srv2_ErrNumbATK ) ;
            flgO._.Vedushiy  = 0 ;
            flgO._.V_rezerve = 1 ; // ��� � ������� �� ��������� .
            bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ��� � ���� ������ .
            flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
            //---
            //��������� ���� CAN0 :
            Agregat = _V_REZERVE ;
            if( can_stop( _CAN0_Port ) == 0 )
            {
                can_stop( _CAN0_Port ) = 1;
            }
            //---
            mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
            //---
            // ������ ���������� �� ��������� ���������� :
            bo_Reversor1 = 0 ;
            bo_Reversor2 = 0 ;
            // ����� ������ :
            flgO._.Reg1dvig = 0 ;
            flgO._.dvig_N1 = 0 ;
            flgO._.dvig_N2 = 0 ;
            //---
            bo_Vedushiy = 0 ;
          break ;
        }*/

              // DAN 12.04.2025
              // ������� ���������� ������ ���1 � ������ "����1" .
                   flgO._.Vedushiy  = 1 ; // ���1 - ������� , ���2 - � ������� , ���R - � ������� .
                   flgO._.V_rezerve = 0 ; // ���1 � ������ .
                   bo_atkNmbrATK    = 1 ; // ����� ���� ����� ���1 � ���� ������ .
                   flgO._.abonATK   = 0 ; // ������� ���������� , ���������������� ����� .
                   //---
                   //��������� ���� CAN0 ��� ����������������� ������ :
                   Agregat = _ATK1 ;
                 //if( can_stop( _CAN0_Port ) == 0 )
                 //{
                 //    can_stop( _CAN0_Port ) = 1;
                 //}
                   //---
                   // �� ������� ��������� �� ����������� ����� � ���������� ���������������� ������ .
                   //---
                   // ������ ���������� �� ��������� ���������� :
                   bo_Reversor1 = 1 ;
                   bo_Reversor2 = 0 ;  // ���1 �� ��������� ����������2 .
                   // ����� ������ :
                   flgO._.Reg1dvig = 1 ;
                   flgO._.dvig_N1 = 1 ;
                   flgO._.dvig_N2 = 0 ;
                   //---
                   bo_Vedushiy = 1 ;



        //---------------------------------------------------------------------------------------------------------

        if ( Prg._.Gotovn == 0 ) // � ������ :
        {
            bo_SN_On = 1;
            
            Time_tst_PIU = Timer1_Ovr;
            Time_bo_SN_On = Timer1_Ovr;

          // ��� ������ ������ ��� � 2� ������������ ������ , ������������� ��������� ���� � ������� ��� .
          // �.�. �������� ��������� ������ ��� �� ����� . �� ��������� ���������� ������� ����� � ���� ,
          // ��������� ���������� ���� �� ������ .
          //---
          // ���� �������� ������� - �������� ������� �������� � ������ ����� ����������
          // ( �������� , �������� �������� ������� ) .
        /*if ( _or.CfgO._.Change_Vedush == 1 && flgO._.Reg1dvig == 0 )
          {
            // ��� ������ ��� ���������� ����� � ����
            // ( �������� , �������� �������� ������� ) :
            if ( bo_AvarATK == 1 )
            {
              flgO._.Vedushiy  = 0 ;
              flgO._.V_rezerve = 1 ; // ��� � ������� �� ��������� .
              bo_atkNmbrATK    = 0 ; // � ������� �� ����� ���� ����� ��� � ���� ������ .
              flgO._.abonATK   = 0 ; // � ������� �� ����� ����� ������ �������� .
              //---
              //��������� ���� CAN0 :
              Agregat = _V_REZERVE ;
              if( can_stop( _CAN0_Port ) == 0 )
              {
                  can_stop( _CAN0_Port ) = 1;
              }
              //---
              mSet_ServiceMsg( _Srv_Link_ATK_otkl ) ;
              //---
              // ������ ���������� �� ��������� ���������� :
              bo_Reversor1 = 0 ;
              bo_Reversor2 = 0 ;
              // ����� ������ :
              flgO._.Reg1dvig = 0 ;
              flgO._.dvig_N1 = 0 ;
              flgO._.dvig_N2 = 0 ;
              //---
              bo_Vedushiy = 0 ;
            }
            //----
            if ( ATK2_Avar == 1 )
            {
              //---
              flgO._.abonATK   = 0 ; // ������� ���������� , ���������������� ����� .
              flgO._.Reg1dvig = 1 ;  // ������� � ���������������� ����� .
              //---
              //��������� ���� CAN0 ��� ����������������� ������ :
              Agregat = _ATK2 ;
              if( can_stop( _CAN0_Port ) == 0 )
              {
                  can_stop( _CAN0_Port ) = 1;
              }
              //---
              // �� ������� ��������� �� ����������� ����� � ���������� ���������������� ������ .
              //---
              // ����� ����� ������������ ��������� � ���������� ��������� ��������� :
              if ( Agregat == _ATK2 ) flgO._.dvig_N1 = 0 , bo_Reversor1 = 0 ;
              else                    flgO._.dvig_N2 = 0 , bo_Reversor2 = 0  ;
              //---
              // ���� ������ ��� ��� ������� ,
              if ( flgO._.Vedushiy == 0 )
              {
                flgO._.Vedushiy = 1 ; // ���������� ���� ��� ���������� ������� .
                //---
                bo_Vedushiy = 1 ;
                //---------
                // ��������� ��� ������������� ����������� �� .
              }
            }
          }

          // ������ ����� ���� , ��� ��� ����� � ������ , �� �������� �������������� ���������� ������� ��� :
          // ��� ������ ������ ��� � 2� ������������ ������ , ������������� ��������� ���� � ������� ��� .
          if ( ATK2_Avar == 1 )
          {
            if      ( ATK2_NmbrATK == 1 ) mSet_ServiceMsg( _Srv_CAN_avarATK1 ) ;
            else if ( ATK2_NmbrATK == 2 ) mSet_ServiceMsg( _Srv_CAN_avarATK2 ) ;
            else                          mSet_ServiceMsg( _Srv_CAN_avarATKR ) ;
          }
          else // ���� ������ �������� ��� :
          {
            if ( ATK2_Rabota == 0 ) // ������ ��� �� � ������ , �������� � ���� :
            {
                // ������� ��������� �� ���������� ���������� ������� ��� ������ ��� ������� ����� :
                if ( flgO._.CAN0_ok == 1 )
                {
                   // ������ , ������ ��� �� � ������ :
                   if      ( ATK2_NmbrATK == 1 ) mSet_ServiceMsg( _Srv_NotWorkATK1 ) ;
                   else if ( ATK2_NmbrATK == 2 ) mSet_ServiceMsg2( _Srv2_NotWorkATK2 ) ;
                   else                          mSet_ServiceMsg( _Srv_NotWorkATKR ) ;
                }
            }
            else // ������ ��� � ������ , - ��������� , ��� �� � ���� �������������� :
            {
                // ���� ������� ��� � �������������� , �������� � ���� :
                if ( flgO._.Vedushiy == 1 && ATK2_Predupr == 1 )
                {
                    if      ( ATK2_NmbrATK == 1 ) mSet_ServiceMsg( _Srv_ATK1_Predupr ) ;
                    else if ( ATK2_NmbrATK == 2 ) mSet_ServiceMsg2( _Srv2_ATK2_Predupr ) ;
                    else                          mSet_ServiceMsg( _Srv_ATKR_Predupr ) ;
                }
            }
          }
*/
          //----------------------------
          // ��� ����������� ���������� ����� �������� �� ��� � ��/��� .
          // �������� �� ��� ����� ����� ������������� ( �������� , ��� ����������� ) ,
          // ������� ����� � �� ������ :
          //skor_pdf = PDF[0].out_ob ;
          //if ( (sw)skor_pdf < 0 )  skor_pdf = ~skor_pdf + 1 ;

          skor = Skor ;
          //if ( (sw)skor < 0 )  skor = ~skor + 1 ;
          //N_ob_min = (float)(w)skor / (float)(w)_Skor_Nom * (float)N_ob_minSynhr ;
          //21.12.2020 - N_ob_minSynhr ���������� ������ _sr.NOM.N.fe , �.�. ��� ����� �� ���������� ���� ��������� ,
          //             �.�. ������� _sr.NOM.N.fe ������ ��� ����������� �������� ��������� .
          //------------------------------
          // ���������� � ������������� �������� :
          //
          //               n����� - n
          //   S���, % =  ------------ * 1600 ������� ;
          //                 n�����
          //
        //Srot = (sw)( (float)(N_ob_minSynhr - N_ob_min              ) * (float)(w)_Ud_Nom / (float)N_ob_minSynhr ) ;
        //Srot = (sw)( (float)(N_ob_minSynhr - (float)(w)skor_pdf/10 ) * (float)(w)_Ud_Nom / (float)N_ob_minSynhr ) ;

          //---
          // ���� ��������� �� �����-�� �������� ����������� ���� ���������� �������� ,
          // �������� ���������� , �.�. ��� �� ����� ���� ������������� :
          if ( (sw)Srot < 0 ) Srot = 0 ;
        }
        else // � ������ ���������� :
        {
          Srot = _Ud_Nom ; // ���������� , ��������� ����� .
          if ((u)((w)(Timer1_Ovr - Time_tst_PIU)) > _or.Time_ComtrolPIU)
          {
            bo_SN_On = 1;
            Time_tst_PIU = Timer1_Ovr;
          }
          if (Trg_BegTemp)
          {
           bo_SN_On = 1; 
           Trg_BegTemp = 0;
           Time_bo_SN_On = Timer1_Ovr;
          }
          if (Isp.all != 0)
          {
            bo_SN_On = 1;
            Time_bo_SN_On = Timer1_Ovr- _Sec(14);
            Time_tst_PIU = Timer1_Ovr;
          }
          if (bo_SN_On)
          {
            if ((u)((w)(Timer1_Ovr - Time_bo_SN_On)) > _Sec(15))
            {
              bo_SN_On = 0;              
            }
            
          }
          else
          {
            Time_bo_SN_On = Timer1_Ovr;
          }
        }
        //------------------------------------------------------------------------------------------

        //---
        // � ������ , ��� ��������� ���� �� , ��������� :
        if ( bo_GotovATK == 1 && bi_QK1 == 1 )
        {
          // C������� �� ���������� ����� :
          if ( Isp.all == 0 )
          {
            // � ������� ������ ������������ ������� :
            if ( ATK_flg._.trig_Pusk == 0 ) mSet_ServiceMsg( _Srv_Pusk_off ) ;
          }
          else
          {
            // � ���������� ������ , �������� , ����-��� , ������� �� ����� , �� �� ������������ .
            // �������� ����� ��������� �� ������ ������� ���� :
            if ( bi_Pusk == 0 )             mSet_ServiceMsg( _Srv_Pusk_off ) ;
          }
          //---
          // ��� ������ ������� ��������� ���������� ��������� ��������� ���������� .
          // �������� ������� ���������� �� ���������� �/� �������� ��������� ��� , �.�. ������� "bi_Vpered" �
          // "bi_Nazad" ��� �/� �� ����� ��� � ����� ���������� :
        /*if ( bi_Null == 0 )  DAN 12.04.2025
          {
            // ����� ������ ������� ��� 0.5 ��� � ��������� , ���������� �� ��������� :
            if ( (u)((w)(Timer1_Ovr - Time_Reversor)) > _Sec( 0.5 ) )
            {
              if ( bi_Reversor1 == 0 && flgO._.dvig_N1 == 1 ) mSet_ServiceMsg( _Srv_Reversor1 ) ;
              if ( bi_Reversor2 == 0 && flgO._.dvig_N2 == 1 ) mSet_ServiceMsg( _Srv_Reversor2 ) ;
            }
          }*/
        }
      /*else // ��������� �� � ������ ������ ���� ��������� :   DAN 12.04.2025
        {
          if ( bi_Reversor1 == 1 ) mSet_ServiceMsg( _Srv_Reversor1On ) ;
          if ( bi_Reversor2 == 1 ) mSet_ServiceMsg( _Srv_Reversor2On ) ;
          //---
          Time_Reversor = Timer1_Ovr ; // �������� ������� ��� �������� ��������� ���������� .
        }*/
        //----------------------------


        //------------------------ ������ ���������� �������� ---------------------------------

        // ���� �8 - ��������� ��3 ���������� ����������� ������� .
        if ( bi_VV3_trans == 1 )
        {
          bo_VV3_trans = 1 , bo_canVV1_stator = 1 ;
        }
        else
        {
          bo_VV3_trans = 0 , bo_canVV1_stator = 0 ;
        }

        //------------------------- ���� ����� �������� "���" ---------------------------------

        // ��� ���� ��� �� ���������� , � ��� ��������� ����� ��� � ���� ���� �� ���� �� ������ ����� ,
        // ���� �� ������� ������ "��������� ������� �������������� �������" = 1 .
        // ---
        // �� ��������� ��� �������� ���������� ���� ��� ������� ��������� ...
        if      ( skor <= _or.ReleMalSkor )
        {
          if ((w)((u)(Timer1_Ovr - Time_RMS_On)) >= _Sec(1))
          {
           bo_ReleMalSkor = 0 ;
           bo_SA_canN_min = 0 ;  // DAN 12.04.2025
          }
          Time_RMS_Off = Timer1_Ovr;
        }
        else if ( skor > (_or.ReleMalSkor+_or.GistReleMalSkor ) )
        {
          if ((w)((u)(Timer1_Ovr - Time_RMS_Off)) >= _Sec(1))
          {          
           bo_ReleMalSkor = 1 ;
           bo_SA_canN_min = 1 ;  // DAN 12.04.2025
          }
          Time_RMS_On = Timer1_Ovr;
        }

        //------------------------- ���� �������� "N = 490" ---------------------------------
        if (_or.N_490 < _Skor_nom( 0.1 ))
        {
          _or.N_490 = _Skor_nom( 0.1 );
        }

        if      ( skor > _or.N_490 ) // DAN 12.04.2025
        {
           bo_N_490       = 1 ;
           bo_SA_canN_490 = 1 ;
        }
        else if ((skor < _or.N_490-_Skor_nom( 0.1 )))
        {
           bo_N_490       = 0 ;
           bo_SA_canN_490 = 0 ;
        }

        //----------------- ���� "V �������" ��� ���������� ���������� ------------------------
        //----- �� ����� ���� ���� "������ ��" , ������ �� ������ ��� ��� ��� ���������� ------

        // ��� ����������� ������� , �� ����������� ��������� ��������� ��� ��������� ����� ��� � ���� .
        // ��� ��������� ���������� ��� �� �������� , ��� ��� �������� �� �� ����� .
        // ��� ���������� ���������� ������������ ����� ������� �������� , ����� , ����� �� ���� ����� .
        // ������������ ������ �� ��� ���������� ���������� :
        //----
        if ( Otkl_Imp != 0 ) bo_Otkl_Imp = 1 ; // �� ����� , ����� ��������� ���������.
        else                 bo_Otkl_Imp = 0 ;

        //-------------------------------------------------------------------------------------

        // ������ "������" ��� ����� ��2 . ��� ������� ��� ������ "������" ����������� � CAN_OBJ.C :
        if ( Prg._.Gotovn == 0 && bo_Avar == 0 ) bo_canRabota = 1 /*, bo_atkRabota = 1*/ ;
        else                                     bo_canRabota = 0 /*, bo_atkRabota = 0*/ ;

        if ( KTE2_Avar == 0 )    // ���� ��2 ��������� � ������ :
        {
          if ( bo_Avar == 1 ) bo_canAvar = 1 ; // ������ �� ��1 ��������� � ��2 .
          else                bo_canAvar = 0 ;
        }

        // 02.08.2017 20:43 - � �������� ����������� �� ������������ :
        if (  Otkl_Imp != 0 /*S.flg._.ZapretImp == 1*/ ) bo_canSn_Imp = 1 /*, bo_atkSn_Imp = 1*/ ;
        else                                             bo_canSn_Imp = 0 /*, bo_atkSn_Imp = 0*/ ;

        // �������� ������ �������� ���� ������ ��������� ����������� .
        // ���� ��� ��2 ��������� ����������� ������� � � ���������� ������ ( ��� ���������� ���������� , �����
        // ��������� ���������� ���������� ������ ) :
        if ( bi_Pusk == 1 || ( (Isp._.SIFU_Res == 1 || Isp._.Cikl == 1) && Prg._.Gotovn == 0 && bi_Reversor == 1 ) )
        {
          bo_canPusk = 1 ; // �������� ����� ��������� ����������� � ��2 .
          bo_canStart = 1;
          bo_atkPusk = 1 ; // �������� ����� �� ������ ��� .
        }
        // 13.04.2017 7:00 - DAN : ������ �� ������ ����� �������� ���� .
        // ������� ���� ��������� ������ ����� ������ �� �������� :
        // 02.08.2017 20:43 - ����� ���� ��������� - ����� �� ������� � ������ , � ��� � ��������� ������ :
        else /*if ( Otkl_Imp !=0 )*/
        {
          bo_canPusk  = 0 ;
          bo_atkPusk  = 0 ;
          bo_canStart = 0 ;
        }

        //-------
        // ������ "bo_canVpered" ���� ��� �� ���������� .
        // "������"/"�����" - ��� �/� ����� ���������� , � �� ����� ��� , ��� ��� ����������� ���� �� ����� :
        //if ( bi_Nazad == 1 && bi_Vpered == 0 ) bo_canNazad = 1 ;
        //else                                   bo_canNazad = 0 ;

        // 31.01.2022 - ��� ������ ������� "�����" , �� ������ "������" �� ������ ����������� :
 //       if      ( bi_Nazad == 1 && bi_Vpered == 0 ) bo_canNazad = 1 ; //DAN 12.04.2025
 //       else if ( bi_Nazad == 0 && bi_Vpered == 1 ) bo_canNazad = 0 ;
        //-------

        // � ���������� ������� , ����� ������ �� , ���������� ��� ��� �����-���� ������ :
        if ( Isp._.SIFU_Res == 1 || (Isp._.Cikl == 1 && Ckl._.RS == 0) )
        {
          bo_canF2_Isp = 1 ; // �����-������ ����� �� ���������� ������� .
          //---
          bo_canZatormogen = 0 ; // �����-������ ��������� .
          bo_atkZatormogen = 0 ;
        }
        else
        {
          bo_canF2_Isp = 0 ; // �����-������ � ������� ������ .
          //---
          // ���� ������� �������� �������� � ���� �� ����� , ������� ��� , �� �������� ���� ������ ������ � �����-���� :
          if ( (sw)ZISkor <= (sw)_or.Z_SkorNull && (sw)ZISkor >= (sw)( ~_or.Z_SkorNull + 1 ) &&
               (sw)Z_Skor <= (sw)_or.Z_SkorNull && (sw)Z_Skor >= (sw)( ~_or.Z_SkorNull + 1 ) &&
               ( S.Alfa_Old >= (_r.S_Alfa_Max - _Grad( 3.0 ))) )
          {
             bo_canZatormogen = 1 ; // �����-������ � �����-���� .
             bo_atkZatormogen = 1 ;
          }
          else
          {
             bo_canZatormogen = 0 ; // �����-������ ��������� .
             bo_atkZatormogen = 0 ;
          }
        }

#ifdef   bo_atkOtkl_Q1
        // ������ ����� ������ ����� � �������� � ������ ���������� .
        // �.�. ���� �� ��� , ������� ����� ������ ��������� ���� �� ������������ �������������� �� ������� ������ , �� ����� ��������
        // ������� ��� ������� ���������� Q1 :
        if ( Prg._.Gotovn == 1 ) bo_atkOtkl_Q1 = 0 ; // ��������� ���� ���������� Q1 ��� �������� ��� .
#endif

        //----------------------------------------------
        // ������ "��������� ����" ��������� �� ���� �� ������ ��� ( ��� ������ � 2� ������������ ������ ) :
        if ( (Reg_AvarMsg | Reg_AvarMsgFirst) & _Av_Vnesh_Avar )
        {
          bo_atkAvarStop = 1 ;
        }
        else bo_atkAvarStop = 0 ;

        if ( ATK2_AvarStop == 1 && av_label == 0 ) mSet_AvarMsg( _Av_Vnesh_Avar ) ;
        //----------------------------------------------

        if ( Prg._.Gotovn == 0 ) // ������� ��������� � ������ :
        {
          // ������ �� ����� ��2 - ��������� ����������� :
          if ( KTE2_Avar == 1 && av_label == 0 ) mSet_AvarMsg2 ( _Av2_KTE2 ) ;
          //---
          // ��������� , ����� �� � ������ ����� ��2 :
          if ( KTE2_Rabota == 0 ) mSet_ServiceMsg( _Srv_AP2_ne_vRabote ) ;
        }

        // ������� ����� �� ���� ������ ��� �������� ����� ������ - �.�. ����� 1.5��� :
        // 1. ���� ����� ������������� ����� - ��� ��� �� ������ ��� :
        // 2. ���� ������� ��� ������� ������ �� �������� ������������� ����� , �������� ��� �� ���� ��2 :
        if ( (bi_DS1 == 1 || ATK2_DS1 == 1) && Av._.DistSbros == 1 )
        {
              bo_canDS1 = 1 , bo_atkDS1 = 1 ;
        }
        else  bo_canDS1 = 0 , bo_atkDS1 = 0 ;

        // ����� ������������ �������� ��� ��������� - ������� 1200 � , ��� ���� 1000 � - ����������� �������� .
        // ������� � ����������� : I������ = Id * � 2/3  = 0.816 * Id .  DAN 03.06.2016
        //                                                               DAN 03.06.2016
        Id_deystv = (sw)( (slw)(sw)Id_dop_kod * (slw)(sw)(( 0.816 * 256.)) >> 8 ) ;

        //---
        // ���� ����� ��2 ��������� ����������� � ��������� ��������������, �������� � ���� :
        if ( KTE2_Predupr == 1 ) mSet_ServiceMsg2( _Srv2_AP2_Predupr ) ;

        //----
        if ( bi_2P24 != 1 )   //  "�������� 2P24"
        {          
          
          if ( bi_AvarUKAV       == 1 ) mSet_AvarMsg2( _Av2_AvarUKAV ) ;     //DAN 12.04.2025
         
          if ( bi_Fsil_set       == 0 ) mSet_AvarMsg2( _Av2_Fsil_set ) ;
        //if ( bi_Fsil_KZ        == 0 ) mSet_AvarMsg2( _Av2_Fsil_KZ ) ;      //DAN 12.04.2025
          if ( bi_SF2            == 0 ) mSet_PreduprMsg2( _Pr2_SF2 ) ;
#ifdef  bi_SF3x
          if ( bi_SF3x           == 0 ) mSet_PreduprMsg2( _Pr2_SF3 ) ;
#endif
        //if ( bi_SF4            == 0 ) mSet_PreduprMsg2( _Pr2_SF4 ) ;       //DAN 12.04.2025
        //if ( bi_Vnesh_AvarPult == 1 ) mSet_AvarMsg( _Av_Vnesh_AvarPult ) ; //DAN 12.04.2025
#ifdef  bi_SF5
          if ( bi_SF5            == 0 ) mSet_AvarMsg2( _Av2_SF5 ) ;
#endif
          if ( bi_KV1            == 1 ) mSet_ServiceMsg( _Srv_KV1_vid_ShI ) ;
          else
          {
            mClr_ServiceMsg2( _Srv_KV1_vid_ShI ) ;
            //---
            if      ( bi_Q1_1 == 1 ) {;}
            else if ( bi_Q1_2 == 1 ) {;}
          }

          if ( bi_Dist_Upr == 0 )       mSet_ServiceMsg( _Srv_Mestnoe ) ;
          else                          mClr_ServiceMsg( _Srv_Mestnoe ) ;
        }
        //----
        // ���������� ��� �� ��� ������� ���������� .
        if ( flgO._.V_rezerve == 1 )  mSet_PreduprMsg( _Pr_ATK_Rezerv ) ;
        else                          mClr_PreduprMsg( _Pr_ATK_Rezerv ) ;
        T_Izm_Dat() ; // ��������� ��������� ������������ � �������� �����������/���������� .
        controlFan(1) ;

        break;
        //-------
         // ��������� ��������� ��� ������ ����������.
      case _Obj_c_Sborka_Gotovn :
         //    ��� �������� ������� �������� � ������ ���������� ���������� ����� �������
         // ������ ���� , � ������ , � ����� , � ������ ���������� , �������������� "break" .

       ATK_flg._.trig_Pusk = 0 ;
       Time_Pusk =  Timer1_Ovr ;

       ATK_flg._.trig_Reg = 0 ;
       Time_Reg =  Timer1_Ovr ;

     // DAN 13.04.2017 7:00 - �������� ��� ��������� ������� :
        mOtkl_Imp( _Start_imp ) ;  // ������� ��
        Prg.all &=  ~(_RegTok | _RegSk ) ; // ��������� ��� ���������� .

        Set_ZI ( &zi_rs , 0 ) ;
        OuIchRS = 0 ;
        ZISkor = 0 ;
        Delta_Sk = 0 , OuIchRS_k = 0 ;
        OuRegS_dop_kod = 0 ;
        OuRegS         = 0 ;

        OIRT_drob = 0 ;     // DAN - 16.06.2016 15:24
        ZIDN = ZIDN1 = 0 ;  // ����� ��-��.
        OIRT   = _r.RTMAX ;  // ���������� ���������� ����
        OIRT1  = _r.RTMAX ;  // ���������� ���������� ����
        S.Alfa = _r.S_Alfa_Max ;

        Control_Nzad () ;  // ��� �������� ������� � ������ ���������� .

        flgO._.Shunt_Rot = 0 ; // �� ������� ������ , ���� �� ��� �� ������ .
        bo_canShunt_End = 0 ;  // �� ������� ������ , ���� �� ��� �� ������ .
        bo_atkShunt_End = 0 ;  // �� ������� ������ , ���� �� ��� �� ������ .

		break;
        //-------
         // ��������� ��������� �����, ������������� ����� ������������ ������.
      case _Obj_c_Rabota :
        
         mClr_ServiceMsg( _Srv_VR1 ) ;

     // � ������� ��� , � ������� ��� ��������� ���������� ������� "����" - ��� �/� ���������� .
     // ����� ���� , ������� "����" �������� ��� ������� , ��� ��2 � ������ � ������ ��� � ������ ���� ���������������� ����� :
     // ��� ������ ������ ��� � 2� ������������ ������ , ������������� ��������� ���� � ������� ��� .
     if ( bi_Pusk == 1 && KTE2_Rabota == 1 )
     {
        if (  ATK_flg._.trig_Pusk == 0 && ( (u)((w)(Timer1_Ovr - Time_Pusk)) > _or.T_zaderg_pusk )  )
           {
              //  ���������� �������� ������� �������� � ������� 6 ������� ����� ������� ��������� :
              // 26.05.2021 - ����� , ����� �� ������� �� , �.�. ��� ��������������� �������� ������ ������-��
              // ������� ��������� ����� ������������� ��������� :
              /*if ( ZI_Init_Skor ( 1 ) == 0 )*/ ATK_flg._.trig_Pusk = 1 ;
              
                    //---------------------------------------------------
                    /* ���� ����������� ������������� ���� ������� ��������� , ���������������� :
                    if ( _r.Cfg._.Vrasch_Dvig == 0 ) ATK_flg._.trig_Pusk = 1 ;
                    else if ( ZI_Init_Skor ( 1 ) == 0 ) ATK_flg._.trig_Pusk = 1 ; */
                    //---------------------------------------------------
              ATK_flg._.trig_Reg = 0 ;
              Time_Reg =  Timer1_Ovr ;
           }
     }
     else
     {
        // 26.05.2021 - ����� , ����� �� ������� �� , �.�. ��� ��������������� �������� ������ ������-��
        // ������� ��������� ����� ������������� ��������� :
        //ZI_Init_Skor ( 0 ) ; // ���������� ����� �������� ������ ��� ������ ����� .
                    //---------------------------------------------------
                    /* ���� ����������� ������������� ���� ������� ��������� , ���������������� :
                    // ���������� ����� �������� ������ ��� ������ ����� .
                    if ( _r.Cfg._.Vrasch_Dvig == 1 ) ZI_Init_Skor ( 0 ) ; */
                    //---------------------------------------------------
        ATK_flg._.trig_Pusk = 0 ;
        Time_Pusk =  Timer1_Ovr ;
        //---
        ATK_flg._.trig_Reg = 0 ;
        Time_Reg =  Timer1_Ovr ;
        //---
      //Control_Nzad () ;  // �������� ������� �� ������ ����� �� ����� , �.�. ���� �������� �� ����� ��� .
     }

    // ������ ������� "����" ��� .
    if ( bi_Pusk == 1 && ATK_flg._.trig_Pusk == 1 && KTE2_Sn_Imp == 0 )
      {
        if ( Otkl_Imp )
        {
          if ( flgO._.Shunt_Rot == 0 ) // ���� ����� ������������ , �� �� �������� ����� ���� � ��������� .
          {
             mVkl_Imp( _VR1_imp | _Start_imp ) ;  // ��������� ��
          }
        }
        if ( bi_V1_V3          == 0 ) mSet_AvarMsg2( _Av2_V1_V3 ) ;        //DAN 12.04.2025
        // 02.04.2019 7:39 - ���� �������� �� ������� �������� ��1 � ����� ������� �� �������� ����������� ��2 .
        //                   ����� � ������ ����� ���� ��� ����������� �������� ������� , ������ �� ��1 �� ������
        //                   �������� ������...
        //                   ���������� ��������� ����������� , ����� ������ ������� �� ��������� ��1 ����� ,
        //                   ����� �� ������ ��2 ��� ����� ������ � ���� ��� ���������� ���� ����� .
        //                   -----
        //                   �-���.����� ��1 = 1.86 ���. + (�-���.���. = 0.25 ���)
        //                   �-���.����� ��2 = 1.93 ���.
        //                   -----
        if (  ATK_flg._.trig_Reg == 0 && ( (u)((w)(Timer1_Ovr - Time_Reg)) > _Sec (0.25) )  )
        {
            S.flg._.Invertor = 1 ;          // �� ��������� ��1 ��������� � ������ ���������
            Prg.all |= (_RegTok | _RegSk ); // �������� ��� ���������� .
            ATK_flg._.trig_Reg = 1 ;
        }


       //-------------------------------------- ������� �������� ---------------------------------------

       if ( bi_Dist_Upr == 0 )  ax = _or.Z_Sk_mestnoe ;
       else                     ax = canr.N_zad ;

       Z_Skor = ax ;

       //---
       // ��� ���������� �������� �� �� �� ��� .
       // ������ ������������ ����������� ������� ��� ��������� �� :
       if ( bo_candt_Otkl_KZ == 0 )
       {
         // ��������� ������ ������������� �������, �.�. �������������� ���� �� ����� :
         if ( (sw)ax >= (sw)_or.Z_SkMax_bezKZ ) ax = _or.Z_SkMax_bezKZ ;
       }

       //-------------------------------------------------------------

        // �������� , ��� ������� �������� ���������� � �� �������� , ����� �������� �� ������ � ��������������
        // ������ � �� ����� � �������� ����� ���/���� �� :
        ax = Z_Skor - ZISkor ;
        if ( (sw)ax >= 0 ) dZ_Sk =   ax ;
        else               dZ_Sk = - ax ;

        if ( dZ_Sk <= _Skor_nom( 0.005 ) ) bo_canZ_Sk_ZISk = 1 ;
        else                               bo_canZ_Sk_ZISk = 0 ;

       //-----------------------------------------------------------------------------------------------

       // � ������ ������ , ���� ����� ������ "��������� ������� �������������� �������" � ������ , ��
       // ���� ��� ��������� �� ����� , � ��������� ����� "��������" ��� �������� . ��������, ����� �����
       // ����������� ��� �����-�� ����� ...

       //-----------------------------------------------------------------------------------------------

       //---------------------- ����� �� ������ ���������� ������ -------------------------
       // ������ ����� ������������ ������ � ����� ��2 . �������� ��������� � ����� ���� ,
       // �� � �� ������������� .
       if ( KTE2_Shunt_Rot == 1 ) // � ��2 ������� bo_Vkl_KZ - ����� ���������� .
       {
           flgO._.Shunt_Rot = 1 ; // ������� ���� ������������ ������
           //---
           // ��� ������������� ������ , ����� �� ������ ����� , �� ��������� ��� , � ��������� ������ ������� .
           // ����� ���� , ��������� , �� ����� �� ������ ��� �� ������ ���������� ( �������� , ���� �������� ��
           // �������� ������� �������� ) .
           // 18.01.2022 - ���� ������ ������ �� ��������� �� �� �� ��� .
           // ��������� , ��� ����� , ���� ������ �� ����� ������ , � ������� �� ����������� ,
           // ���� �� ������ �������� ����� ����/��� �� ...
           if ( (sw)Z_Skor <= _or.Skor_Otkl_KZ || ATK2_Shunt_End == 1 || bi_dt_Otkl_KZ == 1 )
           {
                 bo_canShunt_End = 1 ; // ���� ��� ������ �� ����������� � �� .
                 bo_atkShunt_End = 1 ; // ���� ��� �������� �� ������ ��� .
           }
           // 30.06.2022 - ����� bo_canShunt_End � bo_atkShunt_End ��������� �� ����� , � � ����� UPRAVL.C .
       }

       //------------- ��������� ����������/������� �������� �� �� �� ��� -----------------
       // �� �� ��� ����� ���������� �� ���������� ������ :
       if ( bi_dt_Otkl_KZ == 0 )
       {
            // 18.01.2022 - ���� � ������� ���� ��� ��������� �� ���� �������� .
            // ���� �������� �� ������ �������� ������� ��������� �� , ����� ������������ �� �������� �� ���� ������ ,
            // ���� �� ��������� ����� ���� :
            //if ( (sw)skor >= _or.Skor_Vkl_KZ && (sw)Z_Skor >= _or.Skor_Vkl_KZ )
            //{
            //
            //}
            //----
            bo_candt_Otkl_KZ = 0 ; // ���������� �������� �� �� �� ��� .
       }
       else bo_candt_Otkl_KZ = 1 ; // ������ �������� �� �� �� ��� .
       //----------------------------------------------------------------------------------


            if ( bi_Vnesh_Avar == 1 )    mSet_AvarMsg( _Av_Vnesh_Avar ) ;

            // �������� �������� ������� ������� ��� ������������ ������� �������� �� ������ ��.
            Time_do_OtklImpPusk = Timer1_Ovr ;
      }
    else
      {
      //13.04.2017 7:00 - ������ ������ ����� � ����� �� - ����� ������������� , ������ �������� .
      //if ( !Otkl_Imp )  mOtkl_Imp( _Start_imp ) ;  // ������� ��

        Z_Skor = 0 ; // 13.04.2017 7:00 - DAN . ������� ������� , ��� ���� , ����� ��� ���� � �.� ����� �� .

        Set_ZI ( &zi_rs , 0 ) ;        // DAN - ���������� ����� , ��� ����, ����� ��� ���� ������ .
        ZISkor = 0 ;

        flgO._.Shunt_Rot = 0 ; // �� ������� ������ , ���� �� ��� �� ������ .
        bo_canShunt_End = 0 ;  // �� ������� ������ , ���� �� ��� �� ������ .
        bo_atkShunt_End = 0 ;  // �� ������� ������ , ���� �� ��� �� ������ .

        if ( !Otkl_Imp )
        {
           // 20.12.2020 - ��������� �� ����� , �� ��� ���� ��� ������� ���������� :
           S.Alfa = _r.S_Alfa_Max ;
           Av._.Sdvig_imp = 1 ;   // ������� �� ���������� �� � ���������.

           // - ������ ������� �� ���������� ���������.
           // 20.12.2020 - ������� ����������� � ������ ����������� ������� �� ��� �������� .
           if (/*S.flg._.Invertor == 0 ||*/ (u)((w)(Timer1_Ovr - Time_do_OtklImpPusk)) >= _r.Time_do_OtklImp )
           {
           //20.12.2020 - ����� �������� ���� , ����� �� �������� ������� �� ���������� ���������� .
           //if ( IDV < _Id_nom ( 0.04 ) )
               {
                    mOtkl_Imp( _Start_imp ) ;  // ������� ��
                    Prg.all &=  ~(_RegTok | _RegSk ) ; // ��������� ��� ���������� .

                    Av._.Sdvig_imp = 0 ;   // ������ ��������� , ������� ������� �� ���������� �� � ��������� .

                  //Set_ZI ( &zi_rs , 0 ) ;
                    OuIchRS = 0 ;
                  //ZISkor = 0 ;
                    Delta_Sk = 0 , OuIchRS_k = 0 ;
                    OuRegS_dop_kod = 0 ;
                    OuRegS         = 0 ;

                    OIRT_drob = 0 ;                // DAN - 16.06.2016 15:24

                    Prz._.int_p = 0 , Prz._.int_m = 0 ;

                    ZIDN = ZIDN1 = 0 ;  /* ����� ��-��. */
                    OIRT   = _r.RTMAX ;  /* ���������� ���������� ���� */
                    OIRT1  = _r.RTMAX ;  /* ���������� ���������� ���� */
                    S.Alfa = _r.S_Alfa_Max ;
               }
           }
        }
      }

        break;
        //-------
         // ��������� ��������� �����, ����������� ����� ������������ ������.
      case _Obj_c_Avar_Otkl :
        break;
        //-------
    }

    return 0;
  }
/*--------------------------------------------------*/

// �������� Id_Max

#ifdef _Obj_Id_Max

void Control_Id_Max (void)
  {
    if ( IDV >= _r.Id_Max || Irot >= _r.Id_Max )
    {
        mSet_AvarMsg ( _Av_IdMax ) ;
        //----
        // ������ ( ���� �� ���� ) ��� �������� � ����� ��1 ��� .
      //mOtkl_Q1 () ; // DAN 07.06.2017 15:20 - ��������� c����� DI - ������ �������� .
        mSET_Q1() ;   // 01.08.2017 12:47 - �������� ������ , ��� ������ ������ ��������� � ���� � �� ������� .
        //----
        Av._.Id_max = 1 ; // ������ ��� ����������� � ��������� ������� ���� .
        Av._.Sdvig_imp = 1 ;   // ������� �� ���������� �� � ���������.
        //----
        //if ( IDV1 >= _r.Id_Max )
        //if ( IDV2 >= _r.Id_Max ) mSetF_AvarMsg ( _Av_IdMax ) ;
    }

    /* ����������� � ��2 �������� ����������� :
    // �������� ����� ��������� :
    // ������ ������������ � ��������� ����� :
    dIrot = IDV - Irot ;
    if ( (sw)dIrot < 0 ) dIrot = ~dIrot + 1 ;
    //----

    // 30.12.2016 10:32 - �������� ������ , ��� ���� ��� ������ ������ ������� , �� - ������ .
    //                    ���� ���� �� ����� ������ - �� �� � ������� .
    //                    ���� ��� ������ ������ ������� - ���� �� � ������� .
    if ( (sw)dIrot >= _or.dId_sryv )
    {
      // ������ ( ���� �� ���� ) ��� �������� � ����� ��1 ��� .
    //mOtkl_Q1 () ;
      mSET_Q1() ;   // 01.08.2017 12:47 - �������� ������ , ��� ������ ������ ��������� � ���� � �� ������� .
      mSet_AvarMsg ( _Av_GerconDC ) ;
    } */

    return;
  }

#endif

/*--------------------------------------------------*/

void Control_Nzad (void)
  {
    word ax ;
            // �������� ����������� ������� �� ��������.
          if ( _r.Cfg._.Control_ZSk == 1 )
            {
              ax = Nzad ;
              if ( (sw)ax < 0 )  ax = ~ax + 1 ;

              if ( ax > _r.Ostanov_skor )
                {
                  mSet_PreduprMsg( _Pr_Podano_ZSk   ) ;
            }   }
    return;
  }

void bo_ATK (void)
  {
  static word T_Lamp ;
        // ������������ �������� �������� �������������� ��� , ������ ��� , ���������� ��� , ����� �� ���� �����������
        // �� "��������" , ����������� ����� ������������ ����������� ������� ( bo_Avar , bo_Predupr � bo_Gotov ).

        //-------- ���� "������ ���" --------
        // ����� ��2 ��������� ����������� �� ����� ���� �� ����� ��� , ������� ����� ��� ��1 � ��2 "������" .
        // ���� "������" ������������ � ������ ��� ���������� "�� �������" � "�� ������" .
        // � �� ��� ������ ���1 , ���2 � ���R ������� ��������������� , ������ ������ �������� � ���������� ����������� ������� .
        // ATK2_Avar �������� � ���� ������ � ��1 � ��2 ������� ��� .
        // ���� ������ ��� - ������� , ������� ����� ��� ��1 � ��2 �������� ��� "������" :
        if ( ( bo_Avar == 1 || KTE2_Avar == 1 || (flgO._.Vedushiy == 1 && ATK2_Avar == 1)
        // ������� ����� ������ �� ��� ��������� ��� ������ :
               ) && flgO._.V_rezerve == 0 ) bo_AvarATK = 1  ;
        else                                bo_AvarATK = 0 ;
#ifdef bo_Avar_Yach
        //---- ���� "������ ������ ���" -----
          // 13.06.2021 - ����� ������ ��� ���������� ������ ������������ �������������� .
          // ������ ��� ������ �� ������� � ������ ������������ �������� ��� ������
          // ��� ���������� ������ ������������ �������������� :
        if ( ( bo_Avar_Yach == 1 || (flgO._.Vedushiy == 1 && ATK2_Avar_Yach == 1)
        // ������� ����� ������ �� ��� ��������� ��� ������ :
               ) && flgO._.V_rezerve == 0 ) bo_AvarYacheykaATK = 1 ;
        else                                bo_AvarYacheykaATK = 0 ;
#endif
        //---- ���� "�������������� ���" ----
        // ����� ��2 ��������� ����������� �� ����� ���� �� ����� ��� , ������� ����� ��� ��1 � ��2 "��������������" .
        if ( ( bo_Predupr == 1 || KTE2_Predupr == 1
#ifndef _ShK_Rele_Vedom // ���� � �� ����������� �� �������� �������������� �������� ��� .
        // ATK2_Predupr �������� � ���� �������������� � ��1 � ��2 ������� ��� .
        // ���� ������ ��� - ������� , ������� ����� ��� ��1 � ��2 �������� ��� "��������������" :
               || (flgO._.Vedushiy == 1 && ATK2_Predupr == 1)
#endif
        // ������� ����� ������ �� ��� ��������� ��� ������ :
               ) && flgO._.V_rezerve == 0 ) bo_PreduprATK = 1 ;
        else                                bo_PreduprATK = 0 ;
        //------ ���� "���������� ���" ------
        // ����� ��2 ��������� ����������� �� ����� ���� �� ����� ��� , ������� ����� ��� ��1 � ��2 "����������" .
        // ���� "����������" ������������ � ������ ��� ���������� "�� �������" � "�� ������" .
        if ( ( bo_Gotov == 1 && KTE2_GotovQK == 1
#ifndef _ShK_Rele_Vedom // ���� � �� ����������� �� �������� ���������� �������� ��� .
        // ATK2_GotovQK �������� � ���� ���������� � ��1 � ��2 ������� ��� .
        // ���� ������ ��� - ������� , ������� ����� ��� ��1 � ��2 �������� ��� "����������" :
               && ((flgO._.Vedushiy == 1 && ATK2_GotovQK == 1) || flgO._.Vedushiy == 0)
#endif
        // ��� ������ � ������ "��� ���������" ����������� ������� ����� ����� ��� � ������������ ������ ���������� ��� :
               && ((flgO._.CAN0_ok == 1 && flgO._.abonATK == ATK2_NmbrATK) || flgO._.Reg1dvig == 1)
        // ������� ����� ������ �� ��� ��������� ��� ������ :
               ) && flgO._.V_rezerve == 0 ) bo_GotovATK = 1 ;
        else                                bo_GotovATK = 0 ;
        //----
        // �� ������ ���� ������ "���. �� �������" � "���. �� ������" ( �.�. , ������������ ��-�� ) ,
        // ������� �������� ����� �/� ���� "���������� ���" � "������ ���" - ��������� ������ ���
        // ������� ���������� . ��������� ������������ ��-�� ( ������ ���� �� �������� ) - ��� ����
        // � ������ ��� �� .
        //----
        // �� ���������� �� ������ . � "���� ��" ���� �/� ���������� , ������ , "�� �������" � "�� ������" .
        // ����� ����� ����� ���������� "���������" . "���������" ���������� ��� ������ ������� ������
        // ��������� , ����� ������� ��������� "����������" ( �.�. ������ "�����" ) � ����� �����������
        // "�����/�����" - ������������� ������� .
        //----
        //-------- ���� "������ ���" --------
        // ��������� ����� "����������" ��� "����" - ������ �� .
        // ����� ����� "������ ���" ���� ��� ����������������� ������� ����������� :
        // 1. ��� � ������ ( � ��1 , � ��2 ) .
        // 2. ���� "������ ���" ��������� � ���� "���������� ���" �������� .
        // 3. ���� ����� "���� ���������" , ���� � ������ "��� ���������" �������������� ��������� :
        //    3.1. ������ � ���������� ������ ������� ��� .
        //    3.2. ����������� ������� ����� ����� ��� � ������������ ������ ���������� ��� ����������� .
        // 4. ����� ������ "�����" ������� �������� � ������ �� .
        // 5. ����������� ������ �� ��� ��������� ��� ������ .
        if ( Prg._.Gotovn == 0 && KTE2_Rabota == 1 && bo_AvarATK == 0 && bo_GotovATK == 1 &&
              ( (ATK2_Rabota == 1 && ATK2_Avar == 0 && flgO._.CAN0_ok == 1 && flgO._.abonATK == ATK2_NmbrATK) ||
              flgO._.Reg1dvig == 1 ) && ATK_flg._.trig_Pusk == 1 && flgO._.V_rezerve == 0 )
        {
#ifdef _Rabota_Mig // ���� ����� "������ ���" �� ������������ ��� ������ "�����" � ���������� ��� � "��������������" :
             if ( bo_PreduprLamp == 0 ) bo_RabotaATK = 1 , T_Lamp = Timer1_fSec ;
             else
             {
                  // ������ � ��������������� , ������ ������ :
                  //---
                  if ( bo_RabotaATK == 1 )
                    {
                      if ( (u)((w)(Timer1_fSec - T_Lamp)) >= _fSec(1.00) )
                      {
                        bo_RabotaATK = 0 , T_Lamp = Timer1_fSec ;
                      }
                    }
                  else
                    {
                      if ( (u)((w)(Timer1_fSec - T_Lamp)) >= _fSec(1.00) )
                      {
                        bo_RabotaATK = 1 , T_Lamp = Timer1_fSec ;
                      }
                    }
             }
#else
             bo_RabotaATK = 1 ;
#endif
        }
        else bo_RabotaATK = 0 , T_Lamp = Timer1_fSec ;

    return;
  }
//-------------
word SetMaxNumChan(word *Cnt)
{
  word Out = 0;
  if ( ++*Cnt >= Izm_Seq_max )
  {
    *Cnt = 0; // ������ � 0-�� ���������� ��� �������

    //if (++*Cnt == 2)
    // {
    //bo_canEndIzm = 1;
    TimeDelay = Timer1_Ovr;
    Out = 1;

    Time_Cikl = (float)(Timer1_Ovr - Time_Cikl1)/(float)_Sec(1);
    //Time_Cikl1 = Timer1_Ovr;

  }

  channelTemp = Izm_seq[*Cnt];
  if ( channelTemp >= _MaxChannel)
  {
    channelTemp = 0;
  }

  return Out;
}

//--------------��������� ����� ������� ����������� � ����������------------
void T_Izm_Dat(void)
{
  word ax, bx;//, cx;
  static word int_Counter = 0;

  switch (IzmTempLabel)
  {
  case 0:
    if ( bo_SN_On )
    {
      if ((w)((u)(Timer1_Ovr - TimeDelay_Temper))> _Sec(4))
      {
        Trg_IzmTemp = 1;
      }
      
      if (Trg_IzmTemp)
      {
        
        ax = 1;
        
        if ((bo_EndIzm)&&(Prg._.Gotovn))
        {
          ax = 0;
          bo_EndIzm = 0;
          TimeDelay = Timer1_Ovr;
        }
        else
        {
          if (Prg._.Gotovn)
          {
            if((u)((w)(Timer1_Ovr - TimeDelay))< _Sec(3))
            {
              ax = 0;
              Time_Cikl1 = Timer1_Ovr;
            }
          }
          
        }
        
        //��� ���������� ������ ��������� ��� ��������� �������
        if((u)((w)(Timer1_Ovr - TimeBlockIzm))> _Sec(1))
        {
          bo_KontrVkl = 1;
        }
        //�� ������ ������
        if ((!PDF[0].Bits._.Count_Beg)&&(ax != 0))
        {
          Set_CS_Temp(Addr_izmChanell[(0xfU & channelTemp)]);          // ������ ������ ������
          PDF[0].Bits._.Count_Beg = 1;
          ++IzmTempLabel;
          //Time_Cikl1 = Timer1_Ovr;
        }
      }
      
    }
    else
    {
      channelTemp = 0;
      int_Counter  = 0;
      Trg_IzmTemp = 0;
      TimeDelay_Temper = Timer1_Ovr;
      PDF[0].Bits._.Count_Beg = 0;
      Av_Dat = 0;
      bo_EndIzm = 0;
      //Time_Cikl1 = Timer1_Ovr;
    }
    break;
  case 1:
    //�������� ��������� � ��������� ��������� ����� ��������� ������

    Time_tst = Timer1_Ovr;
    ++IzmTempLabel;
  //  break;
  case 2:

    if (!PDF[0].Bits._.Count_Beg)
    {
      ++IzmTempLabel;
      if (PDF[0].Freq != 0)
      {
        TIzm[channelTemp].Freq =  PDF[0].Freq ;
        TIzm[channelTemp].V_Out=  PDF[0].V_Out;
        TIzm[channelTemp].Out  =  PDF[0].Out  ;
        TIzm[channelTemp].I_Out=  PDF[0].I_Out;

        Av_Dat &= ~AvTemp[channelTemp];  // ��� ����������� ����� ���� ����� � ������ ������
      }
      else
      {
        TIzm[channelTemp].Freq =  0;
        TIzm[channelTemp].V_Out=  0;
        TIzm[channelTemp].Out  =  _or.T0Volt;
        TIzm[channelTemp].I_Out=  (sw)(_or.T0Volt*10);
        PDF[0].Bits._.Count_Beg = 0;
        //CLR_CS_Temp();
        //++IzmTempLabel;
        Av_Dat |= AvTemp[channelTemp];//(0x1<<(_MaxChannel - channelTemp-1));  ���������� ������� � ����� �� ������� ������ � ���� �� ��������� �� ��� ������������ �����
      }
      //if (   ( Invert_v_rabote !=  _stat_Avar))
      //      if( )
      //      {
      //        mClr_PreduprMsg(_Pr_Tizm1>>channelTemp );
      //      }
    }
    else
    {
      if ((u)((w)(Timer1_Ovr - Time_tst)) > _Sec(1))
      {
        TIzm[channelTemp].Freq =  0;
        TIzm[channelTemp].V_Out=  0;
        TIzm[channelTemp].Out  =  _or.T0Volt;
        TIzm[channelTemp].I_Out=  (sw)(_or.T0Volt*10);
        PDF[0].Bits._.Count_Beg = 0;
        //CLR_CS_Temp();
        ++IzmTempLabel;
        Av_Dat |= AvTemp[channelTemp];//(0x1<<(_MaxChannel - channelTemp-1));
        // mSet_AvarMsg(_Av_Tizm1>>channelTemp);
      }
    }
    break;
  case 3:
    //    if ((u)((w)(Timer1_Ovr - Time_tst)) > _or.Time_opros )
    //    {
    CLR_CS_Temp();
    //����  ����� ��� ���������, �� ��������� � ��������� �����
    if (SetMaxNumChan(&int_Counter)== 1)
    {
      IzmTempLabel = 4;
      
    }
    else
    {
      IzmTempLabel = 0;
      
    }
    break;
  case 4:
    Avv_Dat = Av_Dat;
    Trg_BegTemp = 0;
    //� ������ ���������� ���������� �� ���� ��� ��� � 2 ���.
    if(((u)((w)(Timer1_Ovr - TimeDelay))> _Sec(2))||(!Prg._.Gotovn))
    {
      bo_EndIzm = 1;
      IzmTempLabel = 0;
      TimeDelay = Timer1_Ovr;
      
    }
    break;
  }

/*if (Prg._.Gotovn)
  {
    mClr_PreduprMsg2(_Msk_Temp_Msg );
    mClr_AvarMsg2(_Av2_Tizm1|_Av2_Tizm2| _Av2_Ishs1|  _Av2_Ishs2 );
  }
*/
  FanSpeedMax  = 0;
  ax = 0;
  bx = 0;
  if (_r.Cfg2._.ContrTShI)
  {
    if ((Avv_Dat & _Ch_Ishs1msk)!= 0)
    {
      mSet_AvarMsg2( _Av2_Ishs1);
    }
  }
  if (_r.Cfg2._.ContrTShV)
  {
    
    if ((Avv_Dat & _Ch_Ishs2msk)!= 0)
    {
      mSet_AvarMsg2( _Av2_Ishs2);
    }
  }
  
  Avv_Dat &= (~(_Ch_Ishs1msk | _Ch_Ishs2msk));
  //mSet_PreduprMsg( (lw)(Avv_Dat & (_Ch_Ishs1msk | _Ch_Ishs2msk) )<< Bit_PrAvar );

  if (Avv_Dat  != 0)
  {
    FanSpeedMax  = 1;
    if (_r.Cfg2._.ContrTShI)
    {
      
      if ((Avv_Dat & _Ch_BK1_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK2_S1msk) != 0)
      {
        ++ax;
      }
      
      if ((Avv_Dat & _Ch_BK3_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK4_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK5_S1msk) != 0)
      {
        ++ax;
      }
      if ((Avv_Dat & _Ch_BK6_S1msk) != 0)
      {
        ++ax;
      }
    }
    else
    {
      Avv_Dat &= (~(_Ch_BK1_S1msk | _Ch_BK2_S1msk| _Ch_BK3_S1msk| _Ch_BK4_S1msk| _Ch_BK5_S1msk| _Ch_BK6_S1msk));
    }
    if (_r.Cfg2._.ContrTShV)
    {
      
      if ((Avv_Dat & _Ch_BK1_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK2_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK3_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK4_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK5_S2msk) != 0)
      {
        ++bx;
      }
      if ((Avv_Dat & _Ch_BK6_S2msk) != 0)
      {
        ++bx;
      }
    }
    else
    {
      Avv_Dat &= (~(_Ch_BK1_S2msk | _Ch_BK2_S2msk| _Ch_BK3_S2msk| _Ch_BK4_S2msk| _Ch_BK5_S2msk| _Ch_BK6_S2msk));
    }
    
    if ((ax <= _Dat_Temp_All/4 )&&(bx <= _Dat_Temp_All/4))
    {
      mSet_PreduprMsg2( (lw)Avv_Dat  << Bit_PrAvar );
    }
    else
    {
      if ((ax > _Dat_Temp_All/4)&&(!bi_BV1))
      {

        mSet_AvarMsg2( _Av2_Tizm1 );
      }
      if ((bx > _Dat_Temp_All/4)&&(!bi_BV2))
      {
        mSet_AvarMsg2( _Av2_Tizm2 );
      }
    }
  }


       Volt[0] = TIzm[_Ch_Ishs1].V_Out; // ������������� �������� ������� �� ����������
       Volt[1] = TIzm[_Ch_Ishs2].V_Out;//
       Amper[0] =  (Volt[0]*_or.mV_A) /1000;
       Amper[1] =  (Volt[1]*_or.mV_A)/1000;
       if (isnan(Amper[0])|| isinf(Amper[0]))
       {
         Amper[0] = 0;
       }

       if (isnan(Amper[1])|| isinf(Amper[1]))
       {
         Amper[1] = 0;
       }

       // ------ �������� ���������� �������� ����� ------------
       //if ( Invert_v_rabote ==  _stat_Work || Invert_v_rabote ==  _stat_Work_Predupr )
       //if ( (Invert_v_rabote &  _stat_Work) || (Invert_v_rabote & _stat_Work_Predupr) )  {
       // for ( int i = 0; i < 2; i++){
       //if ( (sw)Volt[i] < (sw)_or.Pimp_min || (sw)Volt[i] > (sw)_or.Pimp_max ) mSet_AvarMsg(_Av_Pimp), mSet_PreduprMsg(_Pr_Pimp);
       //if ( (sw)Amper[i] < (sw)_or.Pimp_min || (sw)Amper[i] > (sw)_or.Pimp_max ) /*mSet_AvarMsg(_Av_Pimp),*/ mSet_PreduprMsg(_Pr_Pimp);
       //else                                                                      /*mClr_AvarMsg(_Av_Pimp),*/ mClr_PreduprMsg(_Pr_Pimp);
       // if ( (canr.Data._.Connect == 0)||(can_ConfigReg ( _CAN_IznmVkl) != 0))
       // {

       if ( Otkl_Imp == 0)
       {
         ax = 1;
       }
       else
       {
         ax = 0;
       }
       if (_r.Cfg2._.ContrTShI)
       {         
         
         if ( (Amper[0] < _or.Pimp_min[ax] || Amper[0] > _or.Pimp_max[ax])&&((Avv_Dat & _Ch_Ishs1msk ) == 0) )
         {
           if (!Prg._.Gotovn)
           {
             mSet_AvarMsg2(_Av2_Pimp1);
           }
           else
           {
             mSet_PreduprMsg2(_Pr2_Pimp1);
           }
           
         }
         else
         {
           mClr_PreduprMsg2(_Pr2_Pimp1);
         }
         
       }
       if (_r.Cfg2._.ContrTShV)
       {
         
         if ( (Amper[1] < _or.Pimp_min[ax] || Amper[1] > _or.Pimp_max[ax]) &&((Avv_Dat & _Ch_Ishs2msk ) == 0))
         {
           if (!Prg._.Gotovn)
           {
             mSet_AvarMsg2(_Av2_Pimp2);
           }
           else
           {
             mSet_PreduprMsg2(_Pr2_Pimp2);
           }
         }
         else
         {
           mClr_PreduprMsg2(_Pr2_Pimp2);
         }
       }
       
       //}
       //---------------
       
       
       // ------------------------- ������������� �����������
       //Temper[Counter_Izm_T] = (sw)Temperature[Counter_Izm_T];
       for (ax = 0; ax < _Dat_Temp_All/2; ++ax)
       {
         Temper[ax] = TIzm[DT_Chanells[0][ax]].I_Out;
         Temper[ax+_Dat_Temp_All/2] = TIzm[DT_Chanells[1][ax]].I_Out;
         fTemper[0][ax] = TIzm[DT_Chanells[0][ax]].Out;
         fTemper[1][ax] = TIzm[DT_Chanells[1][ax]].Out;
       }
       DTMonitor.checkSensors(fTemper[0]);
       DT_Cond[0] = DTMonitor.getAllFaultFlags();
       if (_r.Cfg2._.ContrTShI)
       {
         
         if (DTMonitor.hasAnyFaults()&&((Avv_Dat & (_Ch_BK1_S1msk | _Ch_BK2_S1msk)) == 0))
         {
           if (DTMonitor.getFaultyCount() > _Dat_Temp_All/4)
           {
             mSet_AvarMsg2(_Av2_dT_ShS1);
           }
           else
           {
             mSet_PreduprMsg(_Pr_dT_ShS1);
           }
           FanSpeedMax  = 1;
         }
       }
       //-------------     �������� ������ �����������
       DTMonitor.checkSensors(fTemper[1]);
       if (_r.Cfg2._.ContrTShV)
       {
         
         DT_Cond[1] = DTMonitor.getAllFaultFlags();
         if (DTMonitor.hasAnyFaults()&&((Avv_Dat & (_Ch_BK1_S1msk | _Ch_BK2_S1msk)) == 0))
         {
           if (DTMonitor.getFaultyCount() > _Dat_Temp_All/4)
           {
             mSet_AvarMsg2(_Av2_dT_ShS2);
           }
           else
           {
             mSet_PreduprMsg(_Pr_dT_ShS2);
           }
           FanSpeedMax  = 1;
         }
       }
       
       if ((sw)Temper[Counter_Izm_T] >= _or.T_Av)
       {
         if ((u)((w)(Timer1_fSec - Time_Av_Dat_temp[Counter_Izm_T])) > _fSec(2))
         {
           // mSet_AvarMsg (_Av_Izm_T ) ;
           // mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
           Av_DT_Str.all |= (1UL<< Counter_Izm_T);
           Pr_DT_Str.all &= ~(1UL<< Counter_Izm_T);
         }
         Time_Pr_Dat_temp[Counter_Izm_T] = Timer1_fSec;
       }
       else if ((sw)Temper[Counter_Izm_T] >= _or.T_Pr )
       {
         //mSet_PreduprMsg2 (_Pr2_Izm_T ) ;
         //mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
         if ((u)((w)(Timer1_fSec - Time_Pr_Dat_temp[Counter_Izm_T])) > _fSec(2))
         {
           Av_DT_Str.all &= ~(1UL<< Counter_Izm_T);
           Pr_DT_Str.all |= (1UL<< Counter_Izm_T);
         }
         Time_Av_Dat_temp[Counter_Izm_T] = Timer1_fSec;
       }
       else
       {
         Av_DT_Str.all &= ~(1UL<< Counter_Izm_T);
         Pr_DT_Str.all &= ~(1UL<< Counter_Izm_T);
         Time_Av_Dat_temp[Counter_Izm_T] = Timer1_fSec;
         Time_Pr_Dat_temp[Counter_Izm_T] = Timer1_fSec;
       }
       if (Prg._.Gotovn)
       {
         mClr_PreduprMsg ( _Pr_CTC_Temper ) ;
         mClr_AvarMsg ( _Av_CTC_Temper ) ;
       }

       mClr_ServiceMsg3 ( _SrvDT_Mask ) ; // ����� 4-� ��������
       if ( Pr_DT_Str.all != 0 )
       {
         mSet_PreduprMsg ( _Pr_CTC_Temper ) ; //
         FanSpeedMax  = 1;
         //bo_canPrTemp = 0;
         for (ax = 0; ax < _Dat_Temp_All /*6*/; ++ax)
         {
           if ((Pr_DT_Str.all&(1Ul<<ax)) != 0)
           {
             mSet_ServiceMsg3 ((_Srv3_BK1>> ax)) ;
           }
         }
       }

       // ------------  ����������� ������ �������� ���������� ��� ����������
       if (++Counter_Izm_T /*������� �������. �������*/ >= _Dat_Temp_All /*���-�� �������*/ ) // ���� �� ����������� ��� ��������� � ���������� ������ �����������
       {
         t_fan = 0 ;
         for ( int i = 0; i < _Dat_Temp_All; i++)
         {
           if ( (sw)Temper[i] > (sw)t_fan ) t_fan = Temper[i] ;
         }
         Counter_Izm_T = 0 ;
       }
       //---------
       if ( Av_DT_Str.all != 0)
       {
         mSet_AvarMsg (_Av_CTC_Temper ) ;
         FanSpeedMax  = 1;
         //bo_canAvTemp = 0;
         for (ax = 0; ax < _Dat_Temp_All /*6*/; ++ax)
         {
           if ((Av_DT_Str.all&(1Ul<<ax)) != 0)
           {
             mSet_ServiceMsg3 ((_Srv3_BK1>> ax)) ;
           }
         }
       }
       if (!bo_KontrVkl)
       {
         //mClr_AvarMsg( );
         mClr_PreduprMsg2(_Pr2_Pimp1 | _Pr2_Pimp2 |_Pr_dT_ShS1 |_Pr_dT_ShS2);
         mClr_PreduprMsg (_Pr_dT_ShS1 |_Pr_dT_ShS2);
       }

       //  }
       //  else
       //  {
       //    bo_canAvTemp = 1;
       //    bo_canAvPimp =1;
       //    bo_canPrTemp = 1;
       //    for (ax = 0; ax < _Dat_Temp_All; ++ax)
       //    {
       //      Time_Av_Dat_temp[ax] = Timer1_fSec;
       //      Time_Pr_Dat_temp[ax] = Timer1_fSec;
       //    }
       //    mClr_AvarMsg(_Av_dT_ShS1|_Av_dT_ShS1 | _Av_CTC_Temper);
       //    mClr_PreduprMsg ( _Pr_CTC_Temper ) ;
       //    mClr_ServiceMsg2(_Srv2_BK1|_Srv2_BK2|_Srv2_BK3|_Srv2_BK4);
       //
       //
       //  }
       // Timer_T_NoLink = Timer1_Ovr;
}

//--------------------Fan-----------------------------------------------------
void controlFan(word num)
{  // Ctrl_Vent
  word IDV_Vrem;
  static word  Time_t_tir, Time_temper_min ;
  double Id_fan1;
  /* ��������� ������������ ���������� ����������� ��� �� ���� ��� � �� �����������. ������ � ������� � ������ ��� ���������� ���� ����� �� �������, ���� � ������� �
  � ����������  �� ���������� ������� �����������, � ���� ��� �� ���������� �����������, �� ��������� �� �������. ���� �� �� ����, �� ������ ����� ��������������� ����������� ����
  ����� 0,1 ������� �� ����������. ���������� ����������.  ����� �������� ��� ����� �� ������� ����� ����������� ��������� = 0 + ������� �� ��������������������� ���� �� ���������� ����*/

  if ( num == 0 )
  {
    bo_VklVent_1_2_3 = 1;
    bo_vent_vkl;//mSET_Q2() ;  // ��������� ���������� �� 10 ��� ��� ������� �����������.
    //#define   mSET_Q2()    LPC_GPIO1->CLR = _Q2_Msk
    //#define   mCLR_Q2()    LPC_GPIO1->SET = _Q2_Msk
    Time_t_tir = Timer1_Ovr ;//- _r.Time_otkl_BV1 + _Sec( 15.0 ) ;     // ���� ������� ������ 10���
    //Id_fan =_or.Id_max_vent ;
    Time_temper_min = Timer1_Ovr ;
  }
  else
  {
    //if ( bi_SFV == 1 )
    //{
    // �������� ����������� �� ����������� ��������� (������ ��������)( ������/���������� ) ��� � ������ �� ������������ ����
    //if ( (Prg._.Gotovn == 0 && Otkl_Imp == 0 /*bo_Avar == 0 && (IDV >= _or.Id_Vkl_VentShs1 )*/ ) || t_fan >= _or.t_VklFanShs1 )
    // ������� �� ��������� ��������� ��� �����������
    if ( t_fan >= _or.T_Pr )
    {
      //Id_fan = _or.Id_zad_average/*, bo_VklVent_1_2_3 = 1*/;   // ������� � ���������� ���� ����������� ����������
      FanSpeedMax = 1;
      //Time_t_tir  = Timer1_Ovr;
    }
    if (!Prg._.Gotovn)// || t_fan >= _or.T_Pr )
      //if ( (Invert_v_rabote & _stat_Work) || (Invert_v_rabote & _stat_Work_Predupr) || t_fan >= _or.t_VklFanShs1 )
    {
      // ���� Id ����������. �������� ������� ���. � ����� ������ ����� �������� ����.
      if      ( Irot >= IDV ) IDV_Vrem = Irot;
      else                IDV_Vrem = IDV ;

      bo_VklVent_1_2_3 = 1;
      bo_vent_vkl;// mSET_Q2();
      //IDV_Vrem = IDV;
      // if ( (sw)IDV_Vrem < 0 )  IDV_Vrem = ~IDV_Vrem + 1 ;

      if (IDV_Vrem >= _or.Id_Vkl_VentShs1)
      {
        //Id_fan = ((w)(IDV_Vrem/_Id_nom(0.1))*_Id_nom(0.1));// -_or.Id_min_vent;//* (w)((_or.Id_max_vent - _or.Id_min_vent )/_or.Id_max_vent);// + _or.ShiftCurrentVent, bo_VklVent_1_2_3 = 1;
        //Id_fan1 = ((w)(((_or.Id_max_vent - _or.Id_min_vent ))/((_Id_nom(1.0) - _or.Id_Vkl_VentShs1)))*((bx - _or.Id_Vkl_VentShs1))) + _or.Id_min_vent;
        Id_fan1 = (double)((double)(_or.Id_max_vent - _or.Id_min_vent )/(double)(_Id_nom(1.0) - _or.Id_Vkl_VentShs1));
        Id_fan = (w)(Id_fan1 *(double)(IDV_Vrem - _or.Id_Vkl_VentShs1)) +  _or.Id_min_vent;
        if( Id_fan < _or.Id_min_vent )  Id_fan =_or.Id_min_vent ;
        if( Id_fan > _Id_Nom )  Id_fan = _Id_Nom ;

        Time_temper_min = Timer1_Ovr ;
        //Id_fan = ((w)((_or.Id_max_vent - _or.Id_min_vent )*(IDV_Vrem/100))) /*+ _or.ShiftCurrentVent, bo_VklVent_1_2_3 = 1*/;
      }
      // else
      // {
      // ���� ��� ������� ��� ��������� �����������, �� Time_temper_min �� �����������
      if ( (u)((w)(Timer1_Ovr - Time_temper_min)) > _or.Time_otkl_BV1 ) Id_fan = 0 ;
      // }
      //---
      Time_t_tir  = Timer1_Ovr;
    }// ���� ��� ����������� ����� �� ���������
    else /*if ( bi_SFV == 1 ) */// ���� ���� ��� ��� , �� ����������� �������� ,  ??????????????????????????????????????????????????????????????????????
    { // ������ �� ����������� ��� ��������� ����� , ��� ���� ���-�� �� ������� �� "����.�������" :
      if ( bo_VklVent_1_2_3 == 1 )     // ���� ��������� ��� ���, �� ����������� ��������,
      {                           // ������ �� ����������� �� ��������, ��� ���� ���-�� �� ������� �� "����.�������" :
        if (( Av._.DistSbros == 1 )||( (u)((w)(Timer1_Ovr - Time_t_tir)) > _or.Time_otkl_BV1 )) //_Sec( 10.0 * 60.0 ) )
        {                               // ����� ��������
          Id_fan = 0;
          FanSpeedMax = 0;
          bo_VklVent_1_2_3 = 0;
          bo_vent_otkl; // mCLR_Q2() ;     // ���������� ������������
        }
      }

    }
  }
  if (bo_VklVent_1_2_3 == 1)
  {
    if (FanSpeedMax == 1)
    {
      Id_fan =_or.Id_zad_fors ;
    }
  }
  else
  {
    Id_fan = 0;
  }

  if (bo_VklVent_1_2_3)
  {
    if ((!bi_BV1) ||(!bi_BV2) )
    {
      if ((u)((w)(Timer1_Ovr - timerVentAvar)) > _or.TimeAvarNoVent)
      {
        if (!bi_BV1)
        {
          mSet_PreduprMsg2( _Pr2_Vent_Shs1 ) ;
        }

        if (!bi_BV2)
        {
          mSet_PreduprMsg2( _Pr2_Vent_Shs2 ) ;
        }
      }
    }
    else
    {
      if (Prg._.Gotovn)
      {
        mClr_PreduprMsg2( _Pr2_Vent_Shs2 | _Pr2_Vent_Shs1 ) ;
      }
      timerVentAvar = Timer1_Ovr;
    }

  }
  else
  {
    timerVentAvar = Timer1_Ovr;
  }
  //  else mSet_AvarMsg2( _Av2_Power_Vent_Shs1 );  //���������� ��������
}
//---------------------End Fan------------------------------------------------
