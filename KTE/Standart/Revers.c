
#ifndef _F16e
    #include "dzv_drv.c"
#endif

//         ��������� ���������� ���� �����������.
//------------------------------------------------------------



//     ��������� ����������� ���������� ( �������������� ).
//--------------------------------------------------------

//   ��� ���������� ������� ����������, ����� � ���� ������ ���������,
// ��������� �� 10 ��������, ��� ������������������ ��������� "��� �� ����".

void  Revers_epa_init ( void )
{     //  !!! ����������� ��� � ��� ��� �� ��������� ����������� ��� ������
     // ������� �������, ���� ���� � EPA_TIME ������ �� ����������.
    Revers_Label = 2 ; // ��� ����������� ������ �� default ���
                // �������� ������������ EPA ����� ������ ������ �������.
    init_sifu_epa( _revers_epa_con ) ;

    #ifndef _F16e
        init_DZV() ;
    #endif
#ifdef _SIFU2_
    #ifndef _F16e
        init_DZV2() ;
    #endif
#endif
  return ;
}

//-------  ����� ������������� ������� � ��� �������������. ----

void  Revers_start ( void )
{   //    ��� 12-�� ������.���� ������ ����������� �� ������� ����
    //  ����� ��� ���������, ����� �� ���� ����� ��������.
    if ( S.flg._.Revers == 1 )
      {
          // ������� ������� �� (��� ������ � ��=120���.)
#ifndef _F16e
        mPort_Imp(FOR0[0]) ;
        mFzapoln1_stop() ;// ������� ��� ��������� ����������.
        mFzapoln2_stop() ;
#else
        mPort_Imp(FOR0[0][0]) ;

#endif
        S.flg._.ImpSet1 = 0 ; // ��� ���������� �������� ��� � �������.
              // ���� ������� �� ��� �����������, �� ���� ���������� ���.
    #ifndef _F16e
        if ( S.flg._.SnImpVM == 0 ) Clr_DZV() ; // ������� ��� �� ������� ������ ��.
    #endif
          //----
#ifdef _SIFU2_
          //    ������� ����, ��� ����� �� ������� ����:
          //  ��� ���������� � �������� TZ_Ok, ���� �� ����� ������,
          //  ����� ����� ������� �������.
        if ( S.flg._.TZ_Ok == 1 )  return ;
        S.flg._.ImpSet2 = 0 ;
    #ifndef _F16e
        if ( S.flg._.SnImpVM2 == 0 ) Clr_DZV2() ; // ������� ��� �� ������� ������ ��.
    #endif
#endif
          //----

        if ( (u)TimePuls_of_Revers > _pSec(1.0) )
          {
            mSet_ServiceMsg( _Srv_AvarRevers ) ;
            TimePuls_of_Revers = 0 ;
          }
        else   TimePuls_of_Revers++ ;

      if ( _r.Cfg._.DZV == 0 )
      {
          // ������� � ��� ������ ����� ��������� ���� Id.
        AD_Izm (  Id_mg_ach   , &Tok_for_Revers[ 0 ] ) ;
        AD_Izm (  Id_mg_ach   , &Tok_for_Revers[ 1 ] ) ;
           //  �� ���������� ���������� ��������� ����� ��������
        Tok_for_Revers[ 2 ] = _AD_BUSY ;   //  � ���������� ���� �����.
        AD_Izm (  Id_mg_ach   , &Tok_for_Revers[ 2 ] ) ;
      }
           // ��� ������������ ��������, ��� �� �������������.
        S.flg._.BegImp = 0 ;
            /* ������� ��� �� �������� ���������� ��������� */
        _revers_epa_time ( timer1 + _MkSec( 5 * 55.5 ) );
        //QWEDif ( _r.Cfg._.DZV == 0 )   Revers_Label = 0 ;
        //QWED{     // �� ���������� ������� ������� ���� ��� ���������. �������.
          //QWEDif ( Revers_Label != 1 )
               Revers_Label = 0 ;
        //QWED}
        dn_revers = 0 ;
      }
    else
      {
        TimePuls_of_Revers = 0 ; // ���� ��� �������
        dt_revers = Puls_counter ; // ���� ��� �������
        S.flg._.ZapretImp = 0 ;
        Revers_Label = 2 ; // ��� ����������� ������ �� default ���
                // �������� ������������ EPA ����� ������ ������ �������.
        S.flg._.DZV_OK = 0 ; // 21.02.2008 15:15 - ���� ������� ������� ������.
#ifdef _SIFU2_
        S2.flg._.dzv_half = 0 ;  // 23.02.2017 - ���� ������ ��� 12-�������� ���������� �������� ��������� ��� .
        dzv_copy = 0 ;
#endif
        if ( _r.Cfg._.DZV == 1 )  S.DZV = 0 ;  //��� ������� - �������� S.DZV (��� �����)
      }
  return ;
}
//--------------------

// ���������-���������� ������� �������� ������� ��������� �������.
//
//   ��� ����������, �� ������ ���������, �� ������ ����������
// ���������� �� ����.
//
void Revers_Interrupt ( void )
{
     enum {i0,i10,i20,i30};
//---------------------
  /*register*/ word cx0, cx1, cx2, tst ;
//---------------------
     pR( 1 ) ;

       // ��������� (��� ���������) ���������� ��� ����������:
  Sifu_int_drv(_revers_epa_con) ;  // ����� ������� ����������.

//-----------
#ifdef  mVObj_mask    // ��������� ���������� ��� ����������:
    mVObj_mask() ;  // ���������� pts-EPA0 ��� ���������� ����������.
#endif
//---------------------
     //  ���������  ���������� ��� ���, ������� �� .
  asm_ei() ;
//-----------

  dn_revers++ ;
  //---
  switch ( Revers_Label )
    {
         // �� ������ ��������� ������������ EPA ����� ������ ������ �������.
      default:  break ;
              //----------------
      case  i0 :
      case i10 :

      if ( _r.Cfg._.DZV == 0 )
      {
           // ������ �� ������ ����� ��������� ��� �������?
        while ( Tok_for_Revers[ 2 ] == _AD_BUSY ) ;

          // �������������� ������ ����� ���������.
        mIzmData_Conversion ( Tok_for_Revers[ 0 ] , cx0 ,  Id_mg_ach   ) ;
        if ( (sw)cx0 < 0 ) cx0 = ~cx0 + 1 ;
        mIzmData_Conversion ( Tok_for_Revers[ 1 ] , cx1 ,  Id_mg_ach   ) ;
        if ( (sw)cx1 < 0 ) cx1 = ~cx1 + 1 ;
        mIzmData_Conversion ( Tok_for_Revers[ 2 ] , cx2 ,  Id_mg_ach   ) ;
        if ( (sw)cx2 < 0 ) cx2 = ~cx2 + 1 ;

          // �������� ������ ����� ��������� �� ��������������������.
        tst = 0 ;
        if ( cx0 < _r.RIDRR )  tst++ ;
        if ( cx1 < _r.RIDRR )  tst++ ;
        if ( cx2 < _r.RIDRR )  tst++ ;
           //  ���� ��� �� ���� ������� ���� � �����
          // �����������������, �� ������.
        if ( tst >= 2  )
        {         // ������ ��� ����� ��� ����?
          if ( Revers_Label == i10 )
          {     // ��� ���� �������� ������� �� ���� ����,
               // �.�. ���� ���� ������� �������������� ��� �������� 50� � �����
               // ��� ���������� �������� �������������� ���� ���� ���������
               // ���������� � ������ �������������� �� ��������.
            Revers_Label = i20 ; // ��� ����������� ������ �� default ���
                                // �������� ������������ EPA ����� ������ ������ �������.
            if ( (u)((w)(Puls_counter - dt_revers)) >= _r.dt_revers )
            {    // ������ ��������� ����� ��������� �� ���� - ������ �� ������.
              //Revers_Label = i20 ; // ��� ����������� ������ �� default ���
              goto revx ; // �������� ������������ EPA ����� ������ ������ �������.
            }  // ������ ��������� ����� ��������� �� ���� - ������ �� ���������� ������.
            else break ; // ��� ���� ����� ���� ���� Revers_Label = i20 ; �.�. ���� �� ����� ��������
          }  //  �������� ������ �� ���., �� �� ������������ ������� ����� ������ �� ��� ����� � ���������. ��� �����.
          else Revers_Label  = i10 ;
        }   // ��� � ������: ������ "������" ����� ���������.
        else
        {
          Revers_Label = i0 ;
          dt_revers = Puls_counter ; // ���������� �������� ���� ��� �� � �����.
        }
          //---
      }
      else
      {
#ifdef _F16e
        // �������� ������� ����� ���� 3  �������� �� ���
        Port_input ( 3 ) ;
#endif
        cx0  = 0 ;  // ��������� ����� ���, ���� ���� ��.
        if ( S.flg._.ImpSet1 == 0 )
        {
#ifdef _F16e
          cx0 |= bi_DZVA * 1 ;
          cx0 |= bi_DZVK * 2 ;
#else
          cx0 |= DZVA_Ok() * 1 ;
          cx0 |= DZVK_Ok() * 2 ;
#endif
        }
        if ( S.flg._.VneshZp == 1 || S.Disable == 1 ) // 16.10.2008 16:27 - �� �������� ����� ��������� �����.
        {
          cx0 |= 1 ; // ��������� ��� ������������ �����.
          cx0 |= 2 ;
        }
      #ifdef _SIFU2_
        if ( S.flg._.ImpSet2 == 0 )
        {
#ifdef _F16e
          cx0 |= bi_DZVA2 * 4 ;
          cx0 |= bi_DZVK2 * 8 ;
#else
          cx0 |= DZVA2_Ok() * 4 ;
          cx0 |= DZVK2_Ok() * 8 ;
#endif
        }
        if ( S2.flg._.VneshZp == 1 || S2.Disable == 1 ) // 16.10.2008 16:27 - �� �������� ����� ��������� �����.
        {
          cx0 |= 4 ; // ��������� ��� ������������ �����.
          cx0 |= 8 ;
        }
      #else
        cx0 |= 4 ;
        cx0 |= 8 ;
      #endif
        S.DZV = cx0 ;// ��� ���������.

#ifdef _SIFU2_  // 23.02.2017 - ���� ������ ��� 12-�������� ���������� �������� ��������� ��� .
        if ( S2.flg._.dzv_half == 1 )  cx0 |= dzv_copy ;
#endif

             //  ��� ������.
        if ( cx0 == 0x0F )
        {
          S.flg._.DZV_OK = 1 ; // 21.02.2008 15:15 - �������� �� ������.����� ������ �� �������� !
          if ( (u)((w)(Puls_counter - dt_revers)) >= _r.dt_revers ) goto revx ;
        }
        else if ( ((cx0 & 0x05) | ((cx0 & 0x0A) >> 1)) == 0x05 )
        {     // ����  ����e� ���� �� ���� ������ �� ������-���� ��� �
             // ������ �� ������ ��������� ����� ��� �������� ������� �������.
        //  if ( S.flg._.ZapretImp == 0 ) dt_revers = Puls_counter ;
        //  S.flg._.ZapretImp = 1 ; // ������ ����� ������. �� ����.�������.
        //---
#ifdef _SIFU2_  // 23.02.2017 - ���� ������ ��� 12-�������� ���������� �������� ��������� ��� .
          if ( S2.flg._.dzv_half == 0 ) // ������ ���� .
          {
            dzv_copy = cx0 ;
            S2.flg._.dzv_half = 1 ;
          }
#endif
          //---
          S.flg._.DZV_OK = 1 ; // 21.02.2008 15:15 - �������� �� ������.����� ������ �� �������� !
          if ( (u)((w)(Puls_counter - dt_revers)) >= (u)((w)(_pSec(0.015) + _r.dt_revers)) )
          {
            if ( _r.Cfg2._.DZV_Predupr == 1 ) // 05.09.2019 - ����� ��������� �� ��������� ������� ��� ��� ������� .
            {
              if ( (cx0 & 0x01) == 0 )  mSet_PreduprMsg( _Pr_DZVA ) ;
              if ( (cx0 & 0x02) == 0 )  mSet_PreduprMsg( _Pr_DZVK ) ;
      #ifdef _SIFU2_
              if ( (cx0 & 0x04) == 0 )  mSet_PreduprMsg( _Pr_DZVA2 ) ;
              if ( (cx0 & 0x08) == 0 )  mSet_PreduprMsg( _Pr_DZVK2 ) ;
      #endif
            }
            goto revx ; // �������� ������������ EPA ����� ������ ������ �������.
          }
        }    // ��� �� ������ - ��� � ������
        else if ( S.flg._.DZV_OK == 0 ) //if ( cx0 == 0 )
        {
          // 21.02.2008 15:15 - �������� �� ���������� ����� ����� �������� ������ ��
          // ������� ������� ��� , ����� �� ����� ���������� ����� ��� ���������
          // ��������� ����� ���� ������� ��� ��������� . ���� ��� ���� ����������
          // �������� "dt_revers" , �� �������� ���������� ����� ������������� ��
          // ��������� �������� .
          Revers_Label = i0 ;
          dt_revers = Puls_counter ; // ���������� �������� ���� ��� �� � �����.
        }
      }
          //---
      tst = S.TZ - _MkSec((5)*55.5) , tst = tst - timer1 ; // 23.02.2017 - ��������� �� 6 ��� �� ������ ���� , 12-����� .
      if ( (u)tst >= (w)Tsyn )
    //if (( (w)((S.TZ-_MkSec((5+5+1)*55.5)) - timer1) >= (w)Tsyn ))
      {
        if ( _r.Cfg._.DZV == 0 )   Revers_Label = i20 ;
        else
        {     // �� ���������� ������� ������� ���� ��� ���������. �������.
          if ( Revers_Label != i10 ) Revers_Label = i20 ;
        }
      }
      else
      {
        if ( _r.Cfg._.DZV == 0 )
        {
                  // ������ ����� ���������.
          mAD_Izm (  Id_mg_ach  , &Tok_for_Revers[ 0 ] ) ;
          mAD_Izm (  Id_mg_ach  , &Tok_for_Revers[ 1 ] ) ;
          Tok_for_Revers[ 2 ] = _AD_BUSY ;
          mAD_Izm (  Id_mg_ach  , &Tok_for_Revers[ 2 ] ) ;
        }
           //  ������� ��� �� �������� ������� 5��� ����� ����� ���������.
        _revers_epa_time ( timer1 + _MkSec( 5 * 55.5 ) );
      }

        break;
            //-----------------------

  revx:
        // ����� �� ���� ���������������� , ��������� "1" :
        if ( can_ConfigReg ( _CAN_Revers ) == 1 ) break ;
        if ( obj_ConfigReg ( _Obj_Revers ) == 1 ) break ;

        Revers_Label = i20 ; // <- �� ������ ������ ��� "return" �� "default"
        TimePuls_of_Revers = 0 ;

    //***** ������� - ������ "��� �� ����" ��������. *****

           // ��������� ������������ ��.
        S.flg._.ZapretImp = 1 ;
        if ( S.flg._.BegImp == 1 )// ���! ������! ������� �����������! �� � ������,
          {                   //  ������ ��� � ������ ����� ����� ��������.
             // ��� ������������ ��������, ��� �� �������������.
            S.flg._.BegImp = 0 ;
            S.flg._.ZapretImp = 0 ;
            //Revers_Label = i20 ; // <- �� ������ ������ ��� "return" �� "default"
            break ;
          }
            //  ���������� ���, ����� ��� �� ���������
           // ���� �� ����� ����� ��������.
        _sifu_epa_time ( timer1 - 1u ) ;
           // ����� ������� ���������� ����,���� �� �����. ���� �� ������
          // � ���� ������.
        Sifu_int_drv(_sifu_epa_con) ;
      #ifdef _SIFU2_
        _sifu2_epa_time ( timer1 - 1u ) ;
        Sifu_int_drv(_sifu2_epa_con) ;
      #endif
           //QWED  ������� ��� �� �������� �������.
        _revers_epa_time ( timer1 + _MkSec( 250 ) ); //1000 , 23.02.2017 - ��������� � 4 ���� �� ������ ���� , 12-����� .
        Revers_Label = i30 ; // <- �� ������ ������ ��� "return" �� "default"
        break;

      case i30 : //QWED
        Revers_Label = i20 ; // <- �� ������ ������ ��� "return" �� "default"
        S.flg._.ZapretImp = 0 ;

     //---  ���������� ������������ ����� ���������� ����  ---

#ifndef _KTE_GD
        if ( S.flg._.Invertor == 1 )
          {
            OIRT = _r.RevU0 - (w)_r.KeV * (w)ED1 ;
            if ( OIRT < _r.RTMIN )  OIRT = _r.RTMIN ;
          }
        else
          {
            OIRT = _r.RevU0 + (w)_r.KeI * (w)ED1 ;
            if ( OIRT > 0x3FFFu )   OIRT = 0x3FFFu ;
          }
        IDV = IDN = 0x02u*_K_diskr ; // IDV - �� ����� "Reversa" �� ��������
        ZIDN = OuRegS = 0x02*_K_diskr ;
        Set_ZIRT ( &zi_rt , 0x02*_K_diskr ) ;

#ifdef  _SIFU2_

        Set_ZIRT ( &zi_rt2 , 0x02*_K_diskr ) ;
        IDN_2_  = IDN ;
        ZIDN_2_ = ZIDN;
        IDV2    = IDV;
        OIRT_2_ = OIRT;

#endif
     //-------------    ��    -----------

            //---  ������ �� ��� ������������ ������� �� ���� ����������.
        if ( Prg._.RegTok == 1 && can_ConfigReg ( _CAN_Alfa_Zad ) == 0 &&
                                  obj_ConfigReg ( _Obj_Alfa_Zad ) == 0 )
        {
          RegTok () ;
          Linear () ;
#ifdef  _SIFU2_
          // DAN 23.05.2017 14:46 - ��� ������ ����� ���� ��������������, ���� ��� ������ ������ ��2 .
          if ( _r.Cfg2._.RT2_SIFU2 == 1 || S.Disable == 1 ) // 2-� �� ( ��������������� ) ��� ������� ����� :
          {
            RegTok2 () ; // 2-� �� ��� ������� ����� .
            Linear2 () ;
            if      ( S2.Alfa > _r.S_Alfa_Max )  S2.Alfa = _r.S_Alfa_Max, S2.flg._.Fmax = 1 ;
            else if ( S2.Alfa < _r.S_Alfa_Min )  S2.Alfa = _r.S_Alfa_Min, S2.flg._.Fmin = 1 ;
          }
#endif
        }
#else      // �������������� ��� ������ ��.
        cx0 = _Grad( 180 ) - _r.RevU0 ;
                          // ����� ����� ��� �� ��������...
        if       ( S.NumMost == 1 ) Integr_rn = ~cx0+1 ;
        else if  ( S.NumMost == 2 ) Integr_rn =  cx0 ;
        //OuIchRS = 0 ; 27.06.06 11:41
        //OIRT  = 0 ; 27.06.06 11:41 /* ���������� ���������� ���� */
        //---
        can_ConfigReg ( _CAN_Alfa_Zad ) ;
        obj_ConfigReg ( _Obj_Alfa_Zad ) ;
#endif

        if       ( S.NumMost == 1 ) S.NumMost = 2 ;
        else if  ( S.NumMost == 2 ) S.NumMost = 1 ;

        S.flg._.Revers = 0 ;
        dt_revers = Puls_counter ; // ���������� �������� ���� �� ����������������.
        S.flg._.DZV_OK = 0 ; // 21.02.2008 15:15 - �������� �� ������.����� ��������.
#ifdef _SIFU2_
        S2.flg._.dzv_half = 0 ;
        dzv_copy = 0 ;
#endif

     //-------------   ����   -----------

        S.flg._.Fmax = 0,   S.flg._.Fmin = 0 ;
        S.flg._.Fdmin = 0,  S.flg._.Fdmax = 0 ;

            //---- ����������� ������������ ���� ����������.
        can_ConfigReg ( _CAN_Alfa_Min ) ;
             //-----

        /* ������ S.TZ ��� �������� ���� ��� �������� ��������� */
        cx0 = S.Alfa ;
        if      ( cx0 > _r.S_Alfa_Max )  cx0 = _r.S_Alfa_Max, S.flg._.Fmax = 1 ;
        else if ( cx0 < _r.S_Alfa_Min )  cx0 = _r.S_Alfa_Min, S.flg._.Fmin = 1 ;

        if ( cx0 > S.Alfa_Old )
        {
          S.TZ = S.TZ + (w)( (lw)(cx0-S.Alfa_Old) * (lw)Tsyn >> 15 ) ;
        }
        else
        {
          S.TZ = S.TZ - (w)( (lw)(S.Alfa_Old-cx0) * (lw)Tsyn >> 15 ) ;
        }
        S.Alfa_Old = cx0;

         /* ������ ������ N, ����� S.TZ ����� � ������� (timer1+10���)...(timer1+10���+60���)
          * 10��� - ���������� ��� ����, ����� ������ ��������� �/� Ugol_Pol() � ��� �����
          * �������� EPA ��� ���������� �� */

        cx0 = S.TZ - (w)( (lw)_r.S_Alfa_IzmDoImp * (lw)Tsyn >> 15 ) - timer1 ;
        cx1 = _Grad( 60.0 ) * (lw)Tsyn >> 15  ;  // 1000 , 23.02.2017 - ��������� � 2 ���� �� ������ ���� , 12-����� :
        while ( ( (u)cx0 < _MkSec( 500 ) ) || ( (u)cx0 > (u)((w)(cx1 + _MkSec( 500 ))) ) )
          {
            if ( ((u)cx0 > Tsyn) || ((u)cx0 < Tsyn/32) )
              {
                S.TZ += cx1 ,  S.N++ ;
                if ( S.N > 6 ) S.N = 1 ;
              }
            else
              {
                S.TZ -= cx1 ,  S.N-- ;
                if ( S.N < 1 ) S.N = 6 ;
              }
            cx0 = S.TZ - (w)( (lw)_r.S_Alfa_IzmDoImp * (lw)Tsyn >> 15 ) - timer1 ;
          }
#ifndef _F16e
        S.NIP = FOR0 [S.N] ;  // �������� � ���������������

        if ( Otkl_Imp != 0x0 ) S.NIP = FOR0[0] ;
#else

        S.NIP = FOR0[S.NumMost] [S.N] ;  // �������� � ���������������

        if ( Otkl_Imp != 0x0 ) S.NIP = FOR0[0][0] ;

#endif
        /* ������� ��� �� ���� ���������. */

        S.NumInt = 1 ;

       _sifu_epa_time ( S.TZ - (w)( (lw)_r.S_Alfa_IzmDoImp * (lw)Tsyn >> 15 ) );

  #ifdef  _SIFU2_
      // DAN 23.05.2017 14:46 - ��� ������ ����� ���� ��������������, ���� ��� ������ ������ ��2 .
      if ( _r.Cfg2._.RT2_SIFU2 == 1 || S.Disable == 1 ) // 2-� �� ( ��������������� ) ��� ������� ����� :
      {
        /* ������ S2.TZ ��� �������� ���� ��� �������� ��������� */
        cx0 = S2.Alfa ;
        if      ( cx0 > _r.S_Alfa_Max )  cx0 = _r.S_Alfa_Max, S.flg._.Fmax = 1 ;
        else if ( cx0 < _r.S_Alfa_Min )  cx0 = _r.S_Alfa_Min, S.flg._.Fmin = 1 ;

        if ( cx0 > S2.Alfa_Old )
        {
          S2.TZ = S2.TZ + (w)( (lw)(cx0-S2.Alfa_Old) * (lw)Tsyn >> 15 ) ;
        }
        else
        {
          S2.TZ = S2.TZ - (w)( (lw)(S2.Alfa_Old-cx0) * (lw)Tsyn >> 15 ) ;
        }
        S2.Alfa_Old = cx0;

         /* ������ ������ N, ����� S.TZ ����� � ������� (timer1+10���)...(timer1+10���+60���)
          * 10��� - ���������� ��� ����, ����� ������ ��������� �/� Ugol_Pol() � ��� �����
          * �������� EPA ��� ���������� �� */

        cx0 = S2.TZ - timer1 ;
        cx1 = _Grad( 60.0 ) * (lw)Tsyn >> 15  ;
        while ( ( (u)cx0 < _MkSec( 500 ) ) || ( (u)cx0 > (u)((w)(cx1 + _MkSec( 500 ))) ) )
          {
            if ( ((u)cx0 > Tsyn) || ((u)cx0 < Tsyn/32) )
              {
                S2.TZ += cx1 ,  S2.N++ ;
                if ( S2.N > 6 ) S2.N = 1 ;
              }
            else
              {
                S2.TZ -= cx1 ,  S2.N-- ;
                if ( S2.N < 1 ) S2.N = 6 ;
              }
            cx0 = S2.TZ  - timer1 ;
          }
#ifndef _F16e
        S2.NIP = FOR0 [S2.N] ;  // �������� � ���������������

        if ( Otkl_Imp != 0x0 ) S2.NIP = FOR0[0] ;
#else

        S2.NIP = FOR0[S.NumMost] [S2.N] ;  // �������� � ���������������

        if ( Otkl_Imp != 0x0 ) S2.NIP = FOR0[0][0] ;

#endif

        /*S2.N = S.N ;
        for ( s2_ax = 1 ; s2_ax < _r.S2.FazirovVS ; s2_ax++ )
        {
          S2.N-- ;
          if ( S2.N == 0 )  S2.N = 6 ;
        }

        S2.TZ = S.TZ + Tsyn/12 ; // 30 ��� ��� �������� ���� .

        S2.NumInt = 1 ;

        //��� ����� �� ������� ������������� S2.N, �� ����� ��������� NIP
        if ( Otkl_Imp == 0)
        {
           S2.NIP = FOR0 [S2.N] ;
        }
        else
        {
           S2.NIP = FOR0 [0] ;
        }*/

        // ����� �������� � ����� ����� �� ����������� �� ����, ��� �������� EPA
        // �� ������, ����  EPA ��������� ����� �� ����� ��� �������

              //������� ���
        asm_di();
          S2.NumInt = 1 ;
         _sifu2_epa_time ( S2.TZ );
        asm_ei();
      }
      else // ��� ����2 � ��� :
      {
        SIFU2_Start (1) ;
      }
  #endif

    // ��� �����, ����� � �������� ������ ����������� ������ ����� � ��������� :
    S.Most_Tir  = S.N ;
    S.Most_Tir |= S.NumMost << 4  ;
    if ( _r.Cfg._.DZV == 1 && (S.DZV & 0x03) != 0 ) S.Most_Tir |= 0x08 ; // ���� ������ ���� �� ���� ��� .
    if ( S.flg._.Revers  == 1 )
    {   // 03.08.2021 - ���� ������ ��������� , �� ���� ������ �� ������ �� ����� , ����� � ����� ����� �������������� :
                                   S.Most_Tir |= 0x40 ; // 6� - SPI .
      if ( S.flg._.SnImpVM == 1 )  S.Most_Tir |= 0x80 ; // 7� - ������ ��������� .
    }

  #ifdef  _SIFU2_
    // ��� �����, ����� � �������� ������ ����������� ������ ����� � ��������� :
    S2.Most_Tir =  S2.N ; // ������� ���� ������ �������� �� "����" �������� ,
    S2.Most_Tir |=  S.NumMost << 4  ; // �� �� ����� �� ���� , ��� � ��������.
    if ( _r.Cfg._.DZV == 1 && (S.DZV & 0x0C) != 0 ) S2.Most_Tir |= 0x08 ; // ���� ������ ���� �� ���� ��� .
    if ( S.flg._.Revers   == 1 )
    {   // 03.08.2021 - ���� ������ ��������� , �� ���� ������ �� ������ �� ����� , ����� � ����� ����� �������������� :
                                   S2.Most_Tir |= 0x40 ; // 6� - SPI �������� ����� .
      if ( S.flg._.SnImpVM2 == 1 ) S2.Most_Tir |= 0x80 ; // 7� - ������ ��������� .
    }
  #endif

        break;
    }
//-----------

     pR( 0 ) ;

    return;
}

