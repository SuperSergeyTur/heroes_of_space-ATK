
word can_ConfigReg ( word code )
{
/*register*/ word ax, dx;
#ifndef _F16e

   word  bx;

#endif
  static word time_connect, time2_connect, TimeClrMsg ;
  static byte trigg_connect ;
  dx = 0 ;

      // ����� �� ����� ���������� �� CAN.
      // ���������� ������������� � ��������� ���������� ������� :
  if ( (code != _CAN_Init) && (code != _CAN_Obmen) )
    {
      if ( _r.Cfg._.CAN_reg == 0 || Isp.all != 0 ) return dx ;
    }

  switch ( code )
  {
            // ��������� �������������.
    case _CAN_Init :

         canr.Data.all   = 0 ;          // ��� ������ ����� �������� ������� "���������" ��
         TimeClrMsg      = Timer1_Ovr ; // ������ �������� ������� ����� � ������� ������� .

           //  ������������� �������������� ����������.
         Status_KTE = 0 ;
  reinit:
         //---------------------
           // ������������� ���������� ���������� ��� �� CAN.

         canr.CfgReg.all &= _creg_Connect ;// ����� �� �������� Connect
           if ( bi_canConnect == 1 ) trigg_connect = 1 ;// ��� ���������� ����� � ��
           else                      trigg_connect = 0 ;// ��������� ��������� �� ���������.
         //---
         canr.StatReg.all= 0 ;
         bo_canConnect   = 1 ;
         canr.Data.all  &= _dreg_ClrMsg ;// 22.04.2008 - ����� �� �������� ���� ������ ��������� .
         canr.S_zad      = 0 ;
         canr.N_zad      = 0 ;

         //vmz_29012019 - ��� � ��������
         //canr.Id_zad     = 0 ;

         ax = _Id_Nom *10;
         canr.Temp_Zad = ax/_r.T_ZISkorP_Razg;
         canr.dId_zad    = 0 ;
         canr.Ug_zad     = 0 ;
#ifndef _KTE_GD
         //vmz_29012019 - ��� � ��������
         //canr.Idz_MaxP = _Id_nom(+3.0), canr.Idz_MaxM = _Id_nom(-3.0) ;
         canr.Idz_MaxP = _Id_nom(+5.0), canr.Idz_MaxM = _Id_nom(-5.0) ;
#else
         canr.Idz_MaxP = _Ig_nom(+3.0), canr.Idz_MaxM = _Ig_nom(-3.0) ;
#endif
         canr.F_zad      = _Fv_Nom ;

         //vmz_31012019 - ��� � ��������
         //canr.L_zad      = _r.S_Alfa_Max,  canr.L_min = _Grad( 0.0 ) ;//_r.S_Alfa_Min ;

         for ( ax = 0 ; ax < _Ai_max ; ax++ )  canr.Ai[ax] = 0 ;
         for ( ax = 0 ; ax < _Ao_max ; ax++ )  canr.Ao[ax] = 0 ;

       break;
         //-------------

            // ����������������� �� ����.������.
    case _CAN_DS1_Init :  // ����������������� ���� ����� ����������.
           if ( canr.Data._.Connect == 0 )  goto reinit ;
       break;
         //-------------

           //  ���������/���������� ���������� ��������������� �������� .
    case _CAN_QK :

//vmz_29012019
/*
         if    ( _r.Cfg._.CAN_QK == 0  ) dx = 0 ; // ��� CAN-���������� QK .
         else
          {
            if ( bi_canQK == 1 ) dx = 1 ; // �������� QK .
            else
             {
               dx = 2 ; // ��������� QK .
               mSet_ServiceMsg( _Srv_NoCAN_QK ) ; // ������� � AVAR.C .
             }
      #ifdef bi_QK1_Mestnoe
            if ( bi_QK1Mestnoe == 1 ) dx = 0 ; // ���������� CAN-���������� QK .
      #endif
          }
*/
            if (bi_canStart ) // ���� ������� ����� � ������ ( bo_canRabota ��������������� � bi_canStart ) :
            {
              dx = 0;
            }
            else
            {
               dx = 2;
            }

       break;
         //-------------

           //  ������� �� ���������.
    case _CAN_S_Zad :
        #ifdef _REG_POL
         if ( bi_canS_zad == 1 ) ZUgol = canr.S_zad, dx = 1 ;
        #endif
       break;
         //-------------

           //  ������� �� ��������.
    case _CAN_N_Zad :
         if ( bi_canN_zad == 1 ) Z_Skor = canr.N_zad, dx = 1 ;
       break;
         //-------------

            // ������� �� �������� ����� ��.
    case _CAN_N_Zad_R :

       // � ������ ������������� , ��������� ���������� ��������� �������
       // �������� �� ���������� ����������� ( ���������������� dx ) .
       // dx = 1 ;

       //vmz_29012019
       ZISkor = canr.N_zad;
       dx = 1 ;

       break;
         //-------------

            //  ������� �� ��� ����� � ������� � �������.
    case _CAN_Id_Zad :

//vmz_29012019 - ��� � ��������
/*
         if ( bi_canId_zad == 1 )
         {
#ifndef  _WM591
          // if ( canr.Data._.Connect == 1 )
          //{
              OuRegS_dop_kod = canr.Id_zad, dx = 1 ;
          // }
          // else
          // {    // ������� ������� ���� �����. -- �������� �� ���������
            // bi_canId_zad = 0, OuRegS_dop_kod = 0 ; "bi_canStart".
          // }
           OuIchRS = 0 ; // ���������� ���������� ������������ ����������.
#else

          if ( canr.Data._.Connect == 1 )
          {
           dx = 1 ;

           bo_Neg_curr = bi_canRecup;

           OuRegS_dop_kod = canr.Id_zad;

           time_razg =  canr.Temp_Zad;
          }
#endif
         }
         //---
              // ��������� ������� �� ���
         //OuRegS_dop_kod += canr.dId_zad ; 25.10.06 11:51 ���������� ���� ���
               // �������. ���� ���� ����� � ����� ����� ������� ���� ������ �������.
*/
       break;
         //-------------

            //  ����������� ����.
    case _CAN_Id_Zad_Ogr :

//vmz_29012019 - ��� � ��������
/*
           if ( (sw)OuRegS_dop_kod > (sw)canr.Idz_MaxP ) // ����������� ����
             {
               OuRegS_dop_kod = canr.Idz_MaxP, Prz._.int_p = 1 ;
             }
           else if ( (sw)OuRegS_dop_kod < (sw)canr.Idz_MaxM )
             {
               OuRegS_dop_kod = canr.Idz_MaxM, Prz._.int_m = 1 ;
             }
              // ��������� ������� �� ���.  - Vit 25.10.06 11:49
           OuRegS_dop_kod += canr.dId_zad ;// ���������� ���� ��� �������: ���
                      // ��� ����� ������� ���.��, � ����� � ���.������.�������.
*/

       break;
         //-------------

//vmz_29012019
/*            // ���������� ����� ��������.
    case _CAN_Revers :
       // d� = 1 ; // ����� �� ���� ����������������.
       break;
         //-------------

            //  ������� �� ��� �����������.
    case _CAN_Iv_Zad :
       break;
*/
        case _CAN_P01  :
            if ( bi_canStart && bi_canP01)
            {
                dx = 1;

            }
        break;
            //-------------

                //  ������� �� ��� �����������.
        case _CAN_P10 :
            if ( bi_canStart && bi_canP10)
            {
                dx = 1;

            }

        break;

         //-------------
            //  ����/����� �� ��������.
    case _CAN_Ostanov :
#ifndef _WM591
           //---
           // ��� ��������� ������� CAN-Connect ( ����� ��� ) :
          if (  canr.Data._.Connect == 0 )  // ����������������� �� ������ ��� �����,
          {    // � ��� Connect, �.�. �� ��������� � ����.��������, ��� ��������� �����.
            bi_canStart = 0 ;  // ������ ���������������, ��� ������,
            mClr_ServiceMsg( _Srv_NoCAN_Start ) ; // ����� ��� - � ������ ��������� .

            //vmz_29012019 - ��� � ��������
            //mSet_ServiceMsg( _Srv_NoCAN_Connect ) ;// ����� �� ���� ��������� �

            dx = 1 ;     // �������������� QK ��� ����������� �������� ������.
          }
           // ��� ������� ������� CAN-Connect ( ����� ���� ) :
          else
          {
            // � ������ ���������� ������� ������ ��������� �� ���������� ����� :
            // � ������ ���������� �� ������ �� ������ ������ �����. "��� CAN-�����".
            if ( Prg._.Gotovn == 1 )
             { // ������ ���� ��� CAN-���������� �� , ������� ������
               // ��������� �� ���������� ����� , ����� ��� ������� ����� �
               // ����������� ���������� �� ���� ����� , ��� �� ������ ��-��
               // ������ ����� :
               if ( _r.Cfg._.CAN_QK == 0 ) mClr_ServiceMsg( _Srv_NoCAN_Connect ) ;
               //---
               // �� ������ , ����� �������� ������� , "��������" �������� ������� ����� �
               // ������� ������� ������ ����������� - ������� ����� ���������� ���������
               // �� ��������� ����� . ���������� ������ ����� ��������� .
               else if ( canr.Data._.ClrMsg == 0 )
                {
                  if ( (u)((w)(Timer1_Ovr - TimeClrMsg)) > _Sec(5.0) )
                   {
                     canr.Data._.ClrMsg = 1 ;
                     mClr_ServiceMsg( _Srv_NoCAN_Connect ) ;
                   }
                }
             }
               // � ������ ������ ��������� �� ���������� ����� �� ��������� .
            else
             { // � ������ � ������ � ������� �����. "��� CAN-�����".
              if ( bi_canStart == 0 )
              {
                mSet_ServiceMsg( _Srv_NoCAN_Start ) ;
                dx = 1 ;
              }
              else mClr_ServiceMsg( _Srv_NoCAN_Start ) ;
             }
          }
#else

          if (  canr.Data._.Connect == 0 )  // ����������������� �� ������ ��� �����,
          {    // � ��� Connect, �.�. �� ��������� � ����.��������, ��� ��������� �����.
            dx = 0;
            mSet_ServiceMsg( _Srv_NoCAN_Connect ) ;// ����� �� ���� ��������� �
          }              // �������������� QK ��� ����������� �������� ������.
          else
          {
            dx = 1 ;
            if ( Prg._.Gotovn == 1 )  mClr_ServiceMsg( _Srv_NoCAN_Connect ) ;
            bo_Start = bi_canStart;
            bo_Stop  = bi_canStop ;
          }

#endif
       break;
         //-------------
         // ��������� ���.����. �� CAN ���� ��������� ��� ���. �� ���.
    case _CAN_MT :

//vmz_29012019 - ��� � ��������
/*
                // ��������� ������� CAN-������� 'MT'.
            //if ( _r.Cfg._.MT == 0 )
            //{
              // ������� �������� �� , ���������� ��� "1" :
              if ( bi_canMT == 0 ) bo_MT = 0, dx = 1 ;
              else // ������� ����� �� :
              {   // ����� ���� , ���������������� , ���������� ��� "2" :
                if ( canr.Data._.Connect == 1 )   bo_MT = 1, dx = 2 ;
                  // ����� ��� , ������� ������� ��������������� , ��� "1" :
                else  bi_canMT = 0, bo_MT = 0 , dx = 1 ;
              }
            //}
*/
       break;
         //-------------
    case _CAN_Avar :    // ��������� ������� CAN-������� '��������� ����������'.
            if ( bi_canAvar == 1 )
            {
              mSet_AvarMsg( _Av_CAN_avar ) ;
              dx = 1 ;
            }
            else if ( bi_canPredupr == 1 )
            {
              mSet_PreduprMsg( _Pr_CAN_predupr ) ;
              dx = 2 ;
            }
       break;
         //-------------
    case _CAN_Obmen :
            // ���������� �� ������ �������, ����� �� ���� �������� � �������
            // ���� ������� � �� ���� � �� ���������� ����.
            //   ��������� ������� ����� � ��������� �������� �� ������ �������
            // ���� ����� � ������ ��� �������.
            // ������� ������� ����� �������� ��� ������ 0.5���.
          if ( trigg_connect != bi_canConnect )
          {
            if ( trigg_connect == 0 )  trigg_connect = 1 ;
            else                       trigg_connect = 0 ;
            time_connect = Timer1_Ovr ;
            canr.Data._.Connect = 1 ;
          }
          if ( (u)((w)(Timer1_Ovr-time_connect)) > _r.T_Connect_cfg )
          {
            canr.Data._.Connect = 0 ;
            canr.N_zad   = 0 ;  // 23.08.06 09:56

            //vmz_29012019 - ��� � ��������
            //canr.Id_zad  = 0 ;

            ax = _Id_Nom *10;
            canr.Temp_Zad = ax/_r.T_ZISkorP_Razg;
            canr.dId_zad = 0 ;
            canr.Ug_zad  = 0 ;
            //vmz_29012019 - ��� � ��������
            //canr.L_zad   = _r.S_Alfa_Max ;
          }
          //-----------
          //     ������������ ��������� Connect.
          if ( _r.T_Connect_sts != 0 ) // ������� ������. ��������� Connect ,
          {                            // ���� ������ ������� ������� ������� .
            if ( (u)((w)(Timer1_Ovr-time2_connect)) >= _r.T_Connect_sts )
            {
              bo_canConnect = !bo_canConnect ;
              time2_connect = Timer1_Ovr ;
            }
          }
          else // ��� �������� ������� �������� ������ �������� ����� ������� :
          {
            if      ( bi_canConnect == 0 ) bo_canConnect = 0 ;
            else if ( bi_canConnect == 1 ) bo_canConnect = 1 ;
          }
          //-----------
         // ��������� �������� ���������� ������ ��� ������ � CAN.
#ifndef _F16e
          for ( ax = 0 ; ax < _Ai_max ; ax++ )
          {
            if ( _or.Ai_CS[ax] != 0xff )
            {
                // ����� � bx , ����� ���������� �� ������������ _AD_BUSY ��� ��������
              bx = _AD_BUSY;
                // ����������� ����� ������ �� ����������� ���� � ���������.
                /*    ���������  */
              AD_Izm ( *Nstx[_or.Ai_CS[ax]].ach , &bx ) ;
                /*    ��� �������, �������...
                 */
              while ( bx == _AD_BUSY );
                //�������������� ����������� ����������.
              mIzmData_Conversion ( bx, bx, *Nstx[_or.Ai_CS[ax]].ach ) ;
              canr.Ai[ax] = bx ;
            }
          }
#endif
          //----------------
          // ������������ ����� ��������� cStsR � ������� ��� ����������� :
          if ( bo_Avar == 1 )    bo_canAvar = 1 ;
          else                   bo_canAvar = 0 ;
          if ( bo_Predupr == 1 ) bo_canPredupr = 1 ;
          else                   bo_canPredupr = 0 ;

          //vmz_29012019
          //if ( bo_Gotov == 1 )   bo_canGotovQK = 1 ;
          if ( bo_Gotov == 1 && _r.Cfg._.CAN_reg == 1 && _r.Cfg._.CAN_QK == 1 )
              {
              bo_canGotovQK = 1 ;
              }

          else                   bo_canGotovQK = 0 ;
          //---
          if ( bi_QK1 == 0 )     bo_canStateQK = 0 ;
          else                   bo_canStateQK = 1 ;
          //---
//vmz_29012019 - ��� � ��������
/*
          if ( bo_MT == 0 )      bo_canMT = 0 ;
          else                   bo_canMT = 1 ;
          //---
          if      ( S.NumMost == 1 ) bo_canMost = 0 ;
          else if ( S.NumMost == 2 ) bo_canMost = 1 ;
*/
          //---
          if ( bi_KTE_rezerv != 0 ) // ������� ���������
          {
            ax = _stat_Reserve ;
            bo_canKTE_Rezerv = 1 ;
          }
          else // ������� �������
          {
            bo_canKTE_Rezerv = 0 ;
            if ( Prg._.Gotovn == 1 ) // ������� � ������ "������ ����������"
            {
              if ( bo_Gotov == 0 ) ax = _stat_NotReady ;
              else                 ax = _stat_Ready ;
            }
            else // ������� � ������ "������"
            {
              if ( bo_Avar  == 1 )     ax = _stat_Avar ;
              else
              {
                if ( bo_Predupr == 0 ) ax = _stat_Work ;
                else                   ax = _stat_Work_Predupr ;
              }
            }
          }
          Status_KTE = ax ;

         //vmz_31012019 - ���� �� Sts_KTE ��������
         if ( Prg._.Gotovn ==  0 &&  bo_Avar == 0 )  bo_canRabota = 1 ;
         else                                        bo_canRabota = 0 ;

         if ( bi_Pusk_0_1)
         {
             bo_canP01  = 1;
         }
         else bo_canP01  = 0;

         if ( bi_Pusk_1_0)
         {
             bo_canP10  = 1;
         }
         else bo_canP10  = 0;

       break;
         //-------------
            //  ����������� ������������ ���� ����������.
    case _CAN_Alfa_Min :

//vmz_29012019 - ��� � ��������
/*
         if ( S.Alfa < canr.L_min )
           {
             S.Alfa = canr.L_min ;
             S.flg._.Fmin = 1;
           }
*/
       break;
         //-------------
            //  ������� �� ���� ����������.
    case _CAN_Alfa_Zad :

//vmz_29012019 - ��� � ��������
/*
         if ( bi_canL_zad == 1 )
         {
          dx = 1 ;  // ����� ��� �������� ���������� ��.
          S.Alfa = canr.L_zad ;
          OuIchRS = 0 ; // ���������� ���������� ������������ ����������.
    #ifndef _KTE_GD
          OIRT  = _r.RevU0  ;  // ���������� ���������� ���� //
          OIRT1 = _r.RevU0  ;  // ���������� ���������� ���� //
        #ifdef _SIFU2_
           OIRT_2_  = _r.RevU0  ;  // ���������� ���������� ���� //
           OIRT1_2_ = _r.RevU0  ;  // ���������� ���������� ���� //
        #endif
    #else
          OIRT  = 0 ;  // ���������� ���������� ���� //
          Integr_rn = 0 ;
          Integr_rn_drob = 0 ;
    #endif
          // �������� ������������� ������� � ������� �� ����� , ����� ���� ����� �������
          if ( stop_pointR1 == 1 ) break; // �������� � Lmax , ������ �� ����� ����� ��������� ,
          // ������ ���� , ����� ����� ����� ����� ����� ����� � ������ ����� .

              // �������� ������������� �������.
          if ((( S.NumMost == 1 ) && ( bi_canMost  == 1 ))
                                  ||
              (( S.NumMost == 2 ) && ( bi_canMost  == 0 )))
              {
                 S.Alfa = _r.S_Alfa_Max ;
                 S.flg._.Revers = 1 ;
              }
          else
              {
                  // ������� ������� ���, �� ������.
                S.flg._.Revers = 0 ;
                S.flg._.ZapretImp = 0 ;
              }
          }
*/
       break;
         //-------------
            //  ������� �� ���������� ����������.
    case _CAN_Ug_Zad :

//vmz_29012019 - ��� � ��������
/*
        if ( bi_canUg_zad == 1 )
        {
          ORT = canr.Ug_zad, dx = 1 ;
          OuIchRS = 0 ; // ���������� ���������� ������������ ����������.
    #ifndef _KTE_GD
          OIRT  = _r.RevU0  ;  // ���������� ���������� ���� //
          OIRT1 = _r.RevU0  ;  // ���������� ���������� ���� //
    #else
          OIRT  = 0 ;  // ���������� ���������� ���� //
    #endif
        }
*/
       break;

         //-------------
//vmz_29012019 - ��� � ��������
/*
    case _CAN_DistSbros :    // ��������� ������� CAN-������� '����� �����'.
            if ( bi_canDistSbros == 1 )
              {
                 Av._.DistSbros = 1 ; // ��� ������������� �� ������������ ����������� .
                 dx = 1 ;
              }
       break;
*/
         //-------------
  }

  return dx ;
}
/*
   Status_KTE =:
  - � �������;
  - � ����������: ������� ��� �� �������, ���� ����������;
  - � ����������: ������� ��� �� �������, ��� ����������;
  - � ������: ������� �������, �������������� ���;
  - � ������: ������� �������, �������������� ����;
  - � �������������� ���������.
 */

word  can_obj ( word code )
{
  code = code ;// ����� �� ���� �������. � ��������������� "code"

  //if ( tst_can_stop(_WorkSlaveCANPort) == 1 )  return 1 ;

  //----------------------------------------------

  return 0 ;
}

/*
//vmz_31012019
void  Sts_KTE ( void )
  {

    if ( Prg._.Gotovn ==  0 &&  bo_Avar == 0 )  bo_canRabota = 1 ;
    else                                        bo_canRabota = 0 ;

    if ( bi_Pusk_0_1)
    {
        bo_canP01  = 1;
    }
    else bo_canP01  = 0;

    if ( bi_Pusk_1_0)
    {
        bo_canP10  = 1;
    }
    else bo_canP10  = 0;

//vmz_31012019 - ���� ��� ���������� ����� ?
//
//    if ( KTE2_Avar == 0 )    // �������� � ��1 ������ ������ ���� ��1 ��������� ��� � ������
//    {
//     if ( bo_Avar == 1 )    bo_canAvar = 1 ;
//     else                   bo_canAvar = 0 ;
//    }
//
    //if ( bi_KF1 == 0 || bi_KF2 == 0 )  bo_canAvar = 1 ;  //  � ������ ���������� ���� �������� � ��1
    //vmz_31012019 - � ����� ��� ? : - ��� ��� ���� � Obmen
    // if ( bo_Avar == 1 )    bo_canAvar = 1 ;
    // else                   bo_canAvar = 0 ;

    return ;
  }
*/


