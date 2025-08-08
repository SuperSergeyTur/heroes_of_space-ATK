

//      ��������� ��������� ���������� ���������� .
//----------------------------------------------------------------

void  Init_posle_DistSbr ( void )
  {
      Reg_AvarMsgFirst = 0 ;
      Reg_AvarMsg      = 0 ;
      Reg_PreduprMsg   = 0 ;
      Reg_ServiceMsg   = 0 ;
      //mask_predupr     = 0 ; ����� �� CAN-������� "�������" �� �����������
                              // ����������.
      Reg_AvarMsgFirst2 = 0 ;
      Reg_AvarMsg2      = 0 ;
      Reg_PreduprMsg2   = 0 ;
      Reg_ServiceMsg2   = 0 ;
      //mask_predupr2     = 0 ;

#ifdef _TRETIY_REG
      Reg_AvarMsgFirst3 = 0 ;
      Reg_AvarMsg3      = 0 ;
      Reg_PreduprMsg3   = 0 ;
      Reg_ServiceMsg3   = 0 ;
      //mask_predupr3     = 0 ;
#endif

#ifdef _INTERPRETER
      Reg_AvarMsgFirst_obj = 0 ;
      Reg_AvarMsg_obj      = 0 ;
      Reg_PreduprMsg_obj   = 0 ;
      Reg_ServiceMsg_obj   = 0 ;
      //mask_predupr3     = 0 ;
#endif

      bo_Avar  = 0 ;
#ifdef bo_Avar_Yach
      bo_Avar_Yach = 0 ;
#endif
      //bo_canAvar = 0 ; // 20.09.06 16:34 ��������� � CAN_OBJ.C .
      //bo_canPredupr = 0 ;
      bo_Predupr = 0 ;
      // bo_Gotov = 0 ; // 25.05.06 16:09 ��� ����.����. �� CAN .
#ifdef _POWER
      bo_MB1_Razr = 0 ;
      bo_MB1_Otkl = 0 ;
#endif

      Prg.all = _Prg_Gotovn ;
      DWelcome = "\r\nDg>" ,  MWelcome = "\r\nMg>", AWelcome = _GWell_txt;  ;
      av_label = 0 ;
      time_VR1 = Timer1_Ovr ;//��� ������� ����.�� �� 1VR.

      Av.all = 0 , Av2.all = 0 ;
#ifdef _ATK_SET // ������������ ����� �� ��������� ������ � ������ ������ ��� ��� .
      Av._.DistSbros = 1 ;  // ������� ������������ 1.5 ��� ��� ���������� ������ ( ����������� ��� �������� ).
#endif
        mClr_Q1() ;  //   ��� ������ ������� Av.all ����� ���������� Q1,Q2,
        mClr_Q2() ;  // ����� �� �������� ���� ����� ����� �� ����� ��������.
#ifndef _ALARM_FZ
  #ifdef  _Union_FR
      Alarm_on();
  #endif
#endif
      Isp._.Oprobov = 0 ;  // �������� ��� �������� ����������� ��.

      // V.flg.all = 0 ;        // 18.10.05 08:16 �� ����� �������� ��� ,
      V.flg._.otkl_func = 0 ;  // ���������� �������� ���������� �����������
      V.Fv_zad = _Fv_nom( 1.00 ) ;
      V.flg._.Otkl_Imp  = 0 ;
      V.flg._.Sdvig_imp = 0 ;
      V.flg._.Iv_max    = 0 ;
          // ���� ��� ����� F2:�����-���, �� ������� ���, ����� �� ������
         // ����� �� ����������, �.�. ����. ����.���.
      //if ( Isp._.SIFUV_Res == 0 ) V.flg._.RT = 1 ;

    /* ���� c������������ ���� �������� - �������������� ������� */
      if( Isp._.Samonastr == 1 && zeds != 0 )
       {
         _r.Z_EDS = zeds , _r.T_ZISkorP_Razg = tzisk , _r.Z_SkMax_P = zskmax ;
         zeds = 0 ;
       }
//------------------------------------------------------
    /* ���� ������������� ���� �������� - �������������� ������� */
#ifdef   _AVTONASTR
       Avtonastroyka_RT ( 3 ) ;
#endif
//------------------------------------------------------

#ifdef  bo_DS_MT       // ��� ��������������� ������ ����� �� .
        bo_DS_MT = 1 ; // ������� , ����� 300 �� �� ��������� � Common_avar() .
#endif
//------------------------------------------------------

      Init_Regs () ; // ����������������� �����������.

/*------------ ��� CAN- � ��������� ���������. ----------*/

      can_ConfigReg ( _CAN_DS1_Init ) ;
      ObjPrg ( _Obj_c_DS1_Init )  ;
      Control_otkr_tir ( _ConOtkr_DS1_Init ) ;
      //bo_Vkl_Vent = 0;
      Trg_Pusk = 0;
      return;
  }
     //-------------------------------------------
    // ��������� ����������������� ��� CAN-��������.
void  Init_Regs ( void )
  {
      mOtkl_Imp( _VR1_imp ) ;
      mVkl_Imp( _All_imp ^ _VR1_imp ) ;

      S.NumMost = 1 ;

#ifdef _REG_POL
      ZUgol = 0 ;
      ZIUgol = 0 ;
      Integr_RP = 0 , OuRP = 0 ;
      RP_in_sqr = 0 ;
#endif

      Set_ZI ( &zi_rs , 0 ) ;
      Z_Skor = 0, ZISkor = 0, OuIchRS = 0, OuRegS_dop_kod = 0 ;
      Delta_Sk = 0 , OuIchRS_k = 0 ;
      S.Alfa = _r.S_Alfa_Start ;
      fr2 = 0xffff;

      Set_ZIRT ( &zi_rt , 0 ) ;
      OIRT_drob = 0 ;
#ifndef _KTE_GD
      ZIDN  = ZIDN1 = 0 ;  /* ����� ��-��. */
   #ifdef _ATK_SET
      OuRegS_ogr = 0 ; // ������������ ������� �� ��� �� �������� � �������� .
      //---
      OIRT  = _r.S_Alfa_Start ; // � ������� ��������� ��������� ���� - ����� �������� .
      OIRT1 = _r.S_Alfa_Start ;
   #else
      OIRT  = _r.RevU0  ;  /* ���������� ���������� ���� */
      OIRT1 = _r.RevU0  ;  /* ���������� ���������� ���� */
   #endif
   #ifdef _SIFU2_
      OIRT_drob_2_ = 0 ;
      ZIDN_2_  = ZIDN1_2_ = 0 ;  /* ����� ��-��. */
      OIRT_2_  = _r.RevU0  ;  /* ���������� ���������� ���� */
      OIRT1_2_ = _r.RevU0  ;  /* ���������� ���������� ���� */
   #endif
#else
      ORT = 0, OIRT  = 0 ;  /* ���������� ���������� ���� */
      Integr_rn = 0 ;
      Integr_rn_drob = 0 ;
      Ug_zx = 0 , Out_rn = 0 ;
#endif

      RegFlg.all = 0 ;
      Z_sk.out = 0  ;
      //S.flg._.SPI = 0 ;

      // ���������� ����� ���������� ���������� , ������� ��������� ��� ������ ��������� ������������
      // "�������� ������ ����������" , ����� ����� �������� ������������ ������������ ���������� ,
      // ���� ��� �������� ...
      flg_RaTe._.tyr_tst_av = 0 ;

    return ;
  }

/*--------------------------------------------------*/

#ifdef _ATK_SET // ������������ ����� �� ��������� ������ � ������ ������ ��� ��� .
void   DistSbros ( void )
{
  static  word  time_DS ;

           //   ���������������� ��������� �������������� ������.
    //---
    // ������� ������ ������ ( ����������� ��� ������� �� ��������� ��� ���� �� ����� ��2 ) :
  /*if ( bi_DS1 == 1 || ATK2_DS1 == 1 || KTE2_DS1 )
    {       // ��������� ������� ��� ������ ��������
      Av._.DistSbros = 1 ;
      time_DS = Timer1_Ovr ;
    }
    // ������� ������ ����� , ������ ����� 1.5 ��� :
    else if ( Av._.DistSbros == 1 )
    {       // ��������� ������� ��� ������ ��������
      if ( (u)(w)(Timer1_Ovr-time_DS) > _Sec( 1.5 ) )  Av._.DistSbros = 0 ;
    }*/

    //---
    // ������� ������ ������ ( ����������� ��� ������� �� ��������� ��� ���� �� ����� ��2 ) .
    // ������ ����� 1.5 ��� :
    if ( bi_DS1 == 1 || ATK2_DS1 == 1 || KTE2_DS1 )
    {       // ��������� ������� ��� ������ ��������
      if ( (u)(w)(Timer1_Ovr-time_DS) < _Sec( 1.5 ) )  Av._.DistSbros = 1 ;
      else                                             Av._.DistSbros = 0 ;
    }
    // ������� ������ ����� � ���� ������� ��� �� ����������� 1.5 ��� , �� ������ ��� :
    else if ( Av._.DistSbros == 1 )
    {
      if ( (u)(w)(Timer1_Ovr-time_DS) > _Sec( 1.5 ) )  Av._.DistSbros = 0 ;
    }
    else time_DS = Timer1_Ovr ;

  return ;
}
#endif

/*--------------------------------------------------*/

  // ��� ������������� ���������� ������������� USEL ���������� � OBJ_DEF.H
  // ���������� ��� _USEL_obj � � OBJ.C �������� ���� ��������� USEL_Work () .
#ifndef  _USEL_obj
void  USEL_Work ( void )
{
  static word T_USEL ;
   // USEL ������������ ��� ��������� ��������� ������� :
   // 1."��������"           -    ����� ;
   // 2."��.���. "           - �� ����� ;
   // 3."������  "           -    ����� ;
   // 4."������ � �������. " - ������ 1.00 �;
   // 5."������  "           - ������ 0.15 �;

    // ������ ���������� :
  if ( Prg._.Gotovn == 1 )  mUSEL_set() , T_USEL = Timer1_fSec ;
    // ������  � ��������������� ��� ������� :
  else if ( bo_Predupr == 1 || bo_Avar == 1 )
   {
     if ( bo_Avar == 1 )
      {
        if ( USEL == 1 && (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(0.15) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
        else if ( (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(0.15) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
      }
     else
      {
        if ( USEL == 1 && (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(1.00) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
        else if ( (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(1.00) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
      }
   }
    // ������ :
  else      mUSEL_clr() , T_USEL = Timer1_fSec ;

 return ;
}
#endif

/*--------------------------------------------------*/

//   ��������� ��������� ����������� ���� Id

#ifndef _Obj_Id_izm

void IdIzm (void)
  {
      Id_full = _AD_BUSY;
      mAD_Izm (  Id_mg_ach  , &Id_full ) ; // ���������  "Id_Full"

#ifdef  Irot_ach
      Irot_full = _AD_BUSY;
      mAD_Izm (  Irot_ach  , &Irot_full ) ; // ���������  "Irot_Full"
#endif

#ifdef   _SIFU2_  // ��������� ���������� ���� :
    // 07.09.07 11:00 - ���� ���������� ����� �� �������� , �� �������� ���������
    // ��� Id_sum ��������� � SIFU2.C ��� �������������� ����� ���� ���������� .
    // 14.09.2017 12:40 - ���� ���������� �������� , �� �� ��������� ����������
    // ���� Id_sum ������������ ������ � ����� ���� (������ �������� ��� �������� 12500) :
  #ifdef  Id_sum_ach
      Id_sum_full = _AD_BUSY;
      mAD_Izm (  Id_sum_ach  , &Id_sum_full ) ;
  #endif
#endif

      // ��������� ����� �� ����� :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
      IdIzm_3faz () ;
#endif

#ifndef _KTE_GD
   #ifdef _RVId
      RVId.Id1_full = _AD_BUSY;
      mAD_Izm (  Id1_ach  , &RVId.Id1_full ) ; // ���������  "Id1"

      RVId.Id2_full = _AD_BUSY;
      mAD_Izm (  Id2_ach  , &RVId.Id2_full ) ; // ���������  "Id2"
   #endif
#endif

#ifdef  Itt_ach
      Itt_full = _AD_BUSY;
      mAD_Izm (  Itt_ach    , &Itt_full ) ; // ���������  "Itt_Full"
#endif

#ifdef   _SIFU2_
  #ifdef  Itt1_ach // ��� 12-�� �������� ������ ����� ��������������� ���� ��1 .
      Itt1_full = _AD_BUSY;
      mAD_Izm (  Itt1_ach    , &Itt1_full ) ; // ���������  "Itt1_Full"
  #endif
#endif

    return ;
  }

#endif

/*--------------------------------------------------*/

//   ��������� �������������� ����������� ���� Id �� ������� ��� �
// ������ ������.
//   �������� �����:
// - ���������� ���� ��� �������� ������.

#ifndef _Obj_Id_conv

void IdConv (void)
  {
    word ix ;

    while ( Id_full == _AD_BUSY ); // 04.11.2008 15:02 ���������� �� ���� .

    //mIzmData_Conversion ( Id_nn , ix ,  Id_mg_ach   ) ;
        //   ��������������� ����, ��� ���������.
    //Id_Detect =  (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;

    mIzmData_Conversion ( Id_full , ix ,  Id_mg_ach   ) ;
      ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
    //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
  #ifdef  _SIFU_1Faza
        // usrednyaem tok.
    ix = (Id_off + ix) / 3, Id_off = 0 ;
  #endif
        //   ����������� ���.
    IDV = ix ;
        //   �������� ��� �� ������ �����.
    if ( S.NumMost != 2 ) Id_dop_kod =  ix ;
    else                  Id_dop_kod = ~ix + 1 ;
   //---
        // ���������� ���� ��� �������� ������.

#ifndef _KTE_GD
 #ifdef _SIFU2_
  if ( S.Disable == 1 ) // DAN 23.05.2017 14:46 - ��� ������ ������ ��2 :
  {
    Id_teplo = ( Id_teplo + IDV2 ) / 2  ;
  }
  else
 #endif
  {
   #ifndef _ATK_SET
    Id_teplo = ( Id_teplo + IDV ) / 2  ;
   #else // � ������ �� ������ ������� �� ����� � ��� ����� ����������� �� ����� .
    Id_teplo = ( Id_teplo + Irot ) / 2  ;  // � ������ �� ��� ����� ������ � �������� ���� , Id = 0 .
   #endif
  }
#else
    Id_teplo = IDV_g ;
#endif

#ifdef  Irot_ach
    while ( Irot_full == _AD_BUSY );

    mIzmData_Conversion ( Irot_full , ix ,  Irot_ach   ) ;
      ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
    //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
        //   ����������� ���.
    Irot = ix ;
#endif

#ifdef   _SIFU2_  // ��������� ���������� ���� :
    // 07.09.07 11:00 - ���� ���������� ����� �� �������� , �� �������� ���������
    // ��� Id_sum ��������� � SIFU2.C ��� �������������� ����� ���� ���������� .
    // 14.09.2017 12:40 - ���� ���������� �������� , �� �� ��������� ����������
    // ���� Id_sum ������������ ������ � ����� ���� (������ �������� ��� �������� 12500) :
  #ifdef  Id_sum_ach
    while ( Id_sum_full == _AD_BUSY );
    mIzmData_Conversion ( Id_sum_full , ix ,  Id_sum_ach   ) ;
    //   �������� ��������� ��� :
    Id_sum = (slw)(sw)ix * (slw)(sw)_or.Mashtab_Id_sum / 256 ;
  #endif
#endif

#ifdef  Id_sr_ach
    while ( Id_sr_full == _AD_BUSY );
        //  �������������� ����������� �������� ����.
    mIzmData_Conversion ( Id_sr_full , ix ,  Id_sr_ach ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Id_sr = ix ;
#endif

#ifndef _KTE_GD
  #ifdef _RVId
    while ( RVId.Id1_full == _AD_BUSY );
        //  �������������� ����������� �������� ����.
    mIzmData_Conversion ( RVId.Id1_full , ix ,  Id1_ach ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    //   �������� ��� �� ������ ����� ���������� ������ , ��
    // ���� �� ���� ���������� ����� ���� � ������������ ������ .
    RVId.Id1 = ix ;  // �������� ��� .
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    RVId.IDV1 = ix ; // ����������� ��� .

    while ( RVId.Id2_full == _AD_BUSY );
        //  �������������� ����������� �������� ����.
    mIzmData_Conversion ( RVId.Id2_full , ix ,  Id2_ach ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    //   �������� ��� �� ������ ����� ���������� ������ , ��
    // ���� �� ���� ���������� ����� ���� � ������������ ������ .
    RVId.Id2 = ix ;  // �������� ��� .
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    RVId.IDV2 = ix ; // ����������� ��� .
  #endif
#endif

      // �������������� ����� �� ����� :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
    IdConv_3faz () ;
#endif

   //---
  #ifdef  Itt_ach
    while ( Itt_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( Itt_full , ix ,  Itt_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Idtt = ix ;
  #endif
   //---

//--------------
#ifdef   _SIFU2_
//--------------
  #ifdef  Itt1_ach // ��� 12-�� �������� ������ ����� ��������������� ���� ��1 .
    while ( Itt1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( Itt1_full , ix ,  Itt1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Idtt1 = ix ;
  #endif
//--------------
#endif //_SIFU2_
//--------------

    return;
  }

#endif

/*--------------------------------------------------*/

#ifndef _Obj_Id_Max

// 08.04.2008 11:31 - ��� ���������� �������� ������� �� ������ Id-max ����� ����� � ����
// �������� Id_Max , �.�. ��� ����� ��������� � �������������� ���� ����������� � ���� .
// ��� ���� � ����-�� ��������� �������� ������� �� ������ Id-max ��� ���������� ����� .
// � ��� ��� �������� ����� ���� .
void Control_Id_Max (void)
  {
// �������� �������� ��������� �������� ������ ���� �������� ������ � ��������������� ����
// ��� �� ��� �� � ���� Itt :
#if defined (Itt_ach) || defined (Itt1_ach) || defined (_Id_on_Itt_for_ProboyTir) //|| defined (Itt2_ach)
    static lword lax ;
  //static word xOtkl_Imp , xS_Alfa_Max , xS_Alfa ;  20.07.2017 9:45 - ���������� ��� ����������� ��������
  //static byte xS_NumMost ;                                           ��������� �� ����� ...
  //static  byte n , nn , i ;
  #ifdef   _SIFU2_
  //static  byte n2 , nn2 ;
  //static word xS2_Alfa ;
  #endif
#endif
       //  ������� �������� �� ������ ��������� ������ �� ���� �����
       // ��� ��������� ���������� �� �������� � ����� ��������.
       // 08.04.2008 11:31 - ��� ������� �������� - ��������� �������� ,
       // ����� ���� ����������� � ���� , � ������ - � ���� .
    static byte Idmax, Idmax2;
    static word time_Id_max2;
    word ax;

    if ( (IDV >= _r.Id_Max /*||  Av._.Id_max == 1*/
#ifndef _KTE_GD
    #ifdef _RVId
         || RVId.IDV1 >= _r.Id_Max || RVId.IDV2 >= _r.Id_Max
    #endif
#endif
         ) && S.flg._.VneshZp == 0 ) // 16.10.2008 16:27 - �� ����� ��������� �����.
    {
      if ( ((u)((b)(Puls_counter - time_Id_max)) >= _r.time_Id_max) || Idmax == 1 ) // �������� ������������ ����������.
      {
        Av._.Sdvig_imp = 1 ;   // ������� �� ���������� �� � ���������.
#ifndef _KTE_GD
  #ifndef _ATK_SET
        mOtkl_Q2 () ;
  #else
        mOtkl_Q1 () ;
  #endif
#else
        // DAN 08.11.2016 - � ������������ � ���������� ����������� �������� �������� �
        // ��������� , ��������� ������� �� ������ "Id-Max" ��� ����� ���� , ��� �� ������� ,
        // ��� ���� , ����� ������� ������� ...
        //mOtkl_Q1 () ; 08.11.2016 15:18
#endif
#ifdef _RVId
    #ifndef _KTE_GD
        if ( IDV  >= _r.Id_Max ) mSet_AvarMsg  ( _Av_IdMax ) ;
        if ( RVId.IDV1 >= _r.Id_Max ) mSet_AvarMsg2 ( _Av2_Id1Max ) ;
        if ( RVId.IDV2 >= _r.Id_Max ) mSet_AvarMsg2 ( _Av2_Id2Max ) ;
    #endif
#else
        mSet_AvarMsg ( _Av_IdMax ) ;
#endif
        Idmax = 1 ; // ����� ������� Puls_counter ��������� , ��������� ���������� ���� ...
        Av._.Id_max = 1 ; // ������ ��� ����������� � ��������� ������� ���� .
      }
    }
    else time_Id_max = Puls_counter , Idmax = 0 ;

#ifdef   _SIFU2_  // ������ �� ���������� ���� :
    // 14.09.2017 12:40 - ���� ���������� �������� , �� �� ��������� ����������
    // ���� Id_sum ������������ ������ � ����� ���� (������ �������� ��� �������� 12500) :
  #ifdef  Id_sum_ach
    if ( (sw)Id_sum > (sw)_or.Id_sum_max || (sw)Id_sum < (sw)(~_or.Id_sum_max +1) )
    {
        Av._.Sdvig_imp = 1 ;   // ������� �� ���������� �� � ���������.
        // ���� ��� ��� �������� ������� :
        mOtkl_Q2 () ;
        mSet_AvarMsg ( _Av_Id_sum_Max ) ;
        Av2._.Id_sum_max = 1 ; // ������ ��� ����������� � ��������� ������� ���� .
    }
  #endif
#endif

      // ������������� ����� �� ����� ���� ������ �� :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
    TokRaspr_3faz () ;
#endif

    //---------------------------------------------------------------------------------------------------------------

    // �������� ����������� ��������� ��������� .
// �������� �������� ��������� �������� ������ ���� �������� ������ � ��������������� ����
// ��� �� ��� �� � ���� Itt :
#if defined (Itt_ach) || defined (Itt1_ach) || defined (_Id_on_Itt_for_ProboyTir) //|| defined (Itt2_ach)
    //---
    // �������� :     ���� �������� ��������� �������� � �������������� ��� �� ��������� , �� �� �����
    //            ��������� ��������� ����� ��� �� ��������� , � �� ��������� �� ����� . �� ��  �����
    //            �������� � � ��� , ��� � ������ , ���� �������� ������������ , �� � ����� ����� �
    //            �������� ���������� ������� ��� � � ��������� , � � ��������� .
    //                ���� ������ ���� �������� ��� , ����� ��� ������������� ������������ ��� ��������
    //            ��� , ������������ � �������� , �� ���������� �� ��� ��������� ��������� ...
    //---
    // 12.07.2017 13:00 - DAN : ������������ ����� : 20 �� ���� �� � ����� ����� , ����� ����� ����������� �� 1��� .
    //                    ( 180 - 150 ��� ) * 20�� = 600�� .
    //---
    // �� ������ ��������� , ����������� � ������ ������ , ���������� , ����� �������� ������ .
    // ��� ������ ���������� , � ����� ����� ( ����� ��� ����� ) ������ �������� - �� ��������� .
    //---
    // ���� �������������� �� ����� "�����" , �������� ��������� ������� , ��� :
    //   S.N - ����� ��������� , �� ������� ����� �������� ��������� �� ;
    //   n   - ����� ��������� ��������� , ����� ������� ������� ��� ������� �� ;
    //   nn  - ����� ��������� , ������������ � ����� ����� � �������� , ����� ������� ������� ��� �������� ;
    //
    //                              |------------------------------|
    //                              |  ��  | ������ | ��� �������� |
    //                              |------|--------|--------------|
    //                              |  S.N |    n   |     nn       |
    //                              |------|--------|--------------|
    //                              |   1  |    5   |      2       |
    //                              |   2  |    6   |      3       |
    //                              |   3  |    1   |      4       |
    //                              |   4  |    2   |      5       |
    //                              |   5  |    3   |      6       |
    //                              |   6  |    4   |      1       |
    //                              |------------------------------|
    //
    n  = S.N - 2 ; // ����� ��������� ��������� , ����� ������� ����� ��� ������� �� .
    nn = S.N + 1 ; // ����� ��������� , ������������ � ����� ����� � �������� , ����� ������� ����� ��� �������� .
    if ( (sb)n  <= 0 ) n += 6 ;
    if ( (sb)nn >  6 ) nn = 1 ;
    //---
#ifdef   _SIFU2_
  #ifdef  Itt1_ach
    Iproboy1 = Idtt1 ;   // ��� ��������������� ���� ��1 .
  #else
   #ifdef  _Id_on_Itt_for_ProboyTir
    Iproboy1 = IDV ;     // �� ��� �� - ��� � ���� ��� � ��������������� ���� .
   #else
    Iproboy1 = Idtt*2 ;  // ����� ��� - ��� �������� ���� ��1 .
   #endif
  #endif
#else
   #ifdef  _Id_on_Itt_for_ProboyTir
    Iproboy1 = IDV ;     // �� ��� �� - ��� � ���� ��� � ��������������� ���� .
   #else
    Iproboy1 = Idtt ;    // ��� ��������������� ���� .
   #endif
#endif

    // �������� ���������� � ������ ���������� , ��� ��������� ������ � �������������� ( ��������� , ���
    // ������� ���������� ���� ) � ����������� �� .
    // ����� ������� - ����� ��������� ����� �� ���������� ( �.�. ������ ����� � ���� ) .
    //---
       // ��������� Av._.DistSbros != 1 , �.�. ����� ������ �� ������ ���� ������� [Fn+Stop] �����������
       // ������������� �� �������������� ������ � ���� � ������ ���������� . � � OBJ.H ��� ����������
       // ������ ��������� ��� ���������� ���� , � ������� � ������ ���������� ����������� ��������� ����
       // � ������������� �� �������������� ������ ( ��� �� ����� ����� �� �������� ��������� ) , ���������
       // �� � ����� ��������������� � 120 ��� ...
    if ( _r.Cfg2._.ProboyTir == 1 && Prg._.Gotovn == 1 && bo_Avar == 0 && bo_Predupr == 0 &&
#ifdef _KONTAKTOR_for_ProboyTir
         bi_QK1 == 1 && // ��������� �������������� ������� - 3� ������ ��������� , ��� ��������� �������� ��� ���� �� ����������
#endif
        flg_RaTe._.tyr_tst_ok == 0 && flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0 &&
        Av._.DistSbros != 1 && Klav_Buff != _Reset )
    {
        // ���� ����� ��������� ������ , ��� ���� , ����� �� �� �� ����� � 179 ��� :
        if ( Otkl_Imp != 0 )
        {
            S.Alfa  = _Grad( 179 ) ;        //_or.AlfaTst ;   // ����� ���� ��� ����� .
          //19.07.2017 14:52 - ��� ������ �������� ����� �� ���� , �.�. � ���� �� ����� ����� �������������� �� ...
          //S.Alfa_Old  = _Grad( 179 ) ;    //_or.AlfaTst ;   // ����� ���� ��� ����� - ����� �� ���� �� �� ���� .
  #ifdef   _SIFU2_
            S2.Alfa  = _Grad( 179 ) ;       //_or.AlfaTst ;   // ����� ���� ��� ����� .
          //19.07.2017 14:52 - ��� ������ �������� ����� �� ���� , �.�. � ���� �� ����� ����� �������������� �� ...
          //S2.Alfa_Old  = _Grad( 179 ) ;   //_or.AlfaTst ;   // ����� ���� ��� ����� - ����� �� ���� �� �� ���� .
  #endif
            S.NumMost  = 1 ;                // ����� ���� "�����" ��� ����� .
            Prg.all |= _Sled ;              // �.�. ���� ����� ����������� � ������ ���������� , �� �������� ���� .
            //---
            flg_RaTe._.tyr_tst_go = 1 ;     // �������� ����� "�������� ������ ����������" .
            //---
            // ��� ���� �� ������ � 179 ��� �� �� ���� .
            if ( S.Alfa_Old  >= _Grad( 179 )
  #ifdef   _SIFU2_
              && S2.Alfa_Old >= _Grad( 179 )
  #endif
                                             )
            {
               // ���� ������ ���� ����������� ���� :
               Otkl_Imp  = 0x0 ;            // �������� �� ��� ����� .
            }
        }
    }
    //---
    // ������� ����� �������� , �������� ������� � ����� ��������� ����� �� ���������� :
    if (  _r.Cfg2._.ProboyTir == 1 && flg_RaTe._.tyr_tst_go == 1 &&
        flg_RaTe._.tyr_tst_ok == 0 && flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0 )
    {
       // �������� ���� �� ������ - ��� � ��������������� ���� ������ ��������� ������� � ��� ���� , � ������ ,
       // ���� ������� ���� �������� , �� ���� � �������� �� ������ ���� :
       // 12.07.2017 13:00 - DAN : ��� �������� ���� ���� 30% , �� ������� ���� ��� ����������� ������ ��������� .
       //                          ���������� ������� ���� �� 20 % ��� ����������� ������ , ����������� � ���������� .
       // 30.08.2017 13:45 - DAN : �������� ������� ������� ��� �������� ������ ���������� , �.�. ��� ���������� ����
       //                          ���������� ���� �� ��� ���� 20 % ���� �� 150 ���...
       if ( Iproboy1 > _r.Id_tst_proboy // 17.09.2021 - 0.05, �.�. ��� 0.20 "���" ���� ������������ �� ��������� �������� .
   #ifndef  _Id_on_Itt_for_ProboyTir // ��� � �������� ��������� ���� �� �� - ��� �� ��� � ��������������� ���� :
                                        && IDV < _Id_nom(0.05)
   #else
     #ifdef  Id_sum_ach              // ���� ��������� ���� ���� , �� �� ������� �� �� ���� :
                                        && (sw)Id_sum < (sw)_Id_nom(0.10) && (sw)Id_sum > (sw)_Id_nom(-0.10)
     #endif
   #endif
            )
       {
        // ����������� ������ � ������ �� ���� �� � ������ ����� :
        #if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
          if      ( (sb)n == 1 || (sb)n == 4 )
          {
            if        ( IA1 > _r.Id_tst_proboy )   lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
            else /*if ( IA2 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM2_VT11_24 << (n-1) ;
          }
          else if ( (sb)n == 2 || (sb)n == 5 )
          {
            if        ( IC1 > _r.Id_tst_proboy )   lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
            else /*if ( IC2 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM2_VT11_24 << (n-1) ;
          }
          else //if ( (sb)n == 3 || (sb)n == 6 )
          {
            if        ( IB1 > _r.Id_tst_proboy )   lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
            else /*if ( IB2 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM2_VT11_24 << (n-1) ;
          }
        #else
        // ���� � ������ ����� �� ������ �� , �� ������������ �������� �������� , ���� ���� ���� ��� ��� ������ ���� ������ �� :
          lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
        #endif
          mSet_PreduprMsg2( lax ) ;             // ����������������� ��������� � �������� .
          flg_RaTe._.tyr_tst_pr = 1 ;           // ���������� ���� ��������� ����� - �������� ������ .
       }
       //---
       i++ ; // ���������� �������� ����� .
       //---
       // ����� ������� �� 6 �������� ( 1 ������ , 20 �� ) ��������� ���� �� 1 ��.���. :
       if ( i % 6 == 0 )
       {
         S.Alfa -= _Grad( 1 ) ;        // ��������� ���� ���������� .
  #ifdef   _SIFU2_
         S2.Alfa -= _Grad( 1 ) ;       // ��������� ���� ���������� .
  #endif
         //---
         // 12.07.2017 13:00 - DAN : ��� ���������� ���� �� 160 ��� �� ������� ���� ��� ����������� ������ ��������� .
         //                          ���������� ���� ����������� � ���������� .
         // ���� "��������" �� ����� :
         if ( S.Alfa < _Grad( 150 ) )  // ������������� , ��� � S2.Alfa < _Grad( 160 ) ...
         {
           flg_RaTe._.tyr_tst_ok = 1 ; // ���������� ���� ��������� ����� - ��������� � ������� .
         }
       }
       //---
       // �������� ����� ����� ��������� ��� ������ � �������������� , ��������� �� ����� ����� ...
       // ���� �������� �� ������� , ��� �� ���������� �� ������� , ��� ������ �� ��������� ������� , Id-max
       // ��� ��� - ���������� ���� ��������� ��������� ����� ��� ����� � ������ :
       if ( /*Otkl_Imp != 0x0  ||*/ Av._.Sdvig_imp != 0  || bo_Avar != 0         ||
            Av._.Gercon != 0     || Av._.GerconDC != 0   || Av2._.RV1 != 0       ||
            Av2._.GerconAC2 != 0 || Av2._.GerconAC3 != 0 || Av2._.GerconAC4 != 0 ||
            Av._.Id_max != 0     || Av._.Id2_max == 1 )
       {
           flg_RaTe._.tyr_tst_av = 1 ;           // ���������� ���� ��������� ����� - ��������� ������� ������ .
       }
    }
    else i= 0 ; // �������� ������� �������� ����� .
    //----------------

    // ���������� ��� �������� ����� �� ��������� ����� � ��������� ������� :
    // 1. ���-�� �������� ��������� ������������ "�������� ������ ����������" ����� ��� � ������ .
    // 2. ��������� ����������� , ��� ���� �� ������� �� ������� , Id-max , ��� � �.�. ...
    // 3. ��������� ����������� , ������ �� ���������� .
    // 4. ��������� ����������� , ������ ��������� .
    //---
    // �������� , ����� ��� ����� ��������� ������ ���� ��� 12-�� �������� ��� .
    //---
    // ���� ������ ���� ����������� ���� !
    if ( flg_RaTe._.tyr_tst_go == 1 && ( _r.Cfg2._.ProboyTir == 0 || flg_RaTe._.tyr_tst_av == 1 ||
                                       flg_RaTe._.tyr_tst_ok == 1 || flg_RaTe._.tyr_tst_pr == 1 ) )
    {
        mOtkl_Imp( _VR1_imp ) ;          // ��������� �� .
        S.Alfa = _r.S_Alfa_Start ;       // �������������� ����� .
      //S.Alfa_Old = _r.S_Alfa_Start ;   // 10.12.2019 - ������ ���������������� ����� �� ����� - ����� �� ����� �������� ������������ ������������� .
  #ifdef   _SIFU2_
        S2.Alfa = _r.S_Alfa_Start ;      // ���������� ���������� �������� ����� .
      //S2.Alfa_Old = _r.S_Alfa_Start ;  // 10.12.2019 - ������ ���������������� ����� �� ����� - ����� �� ����� �������� ������������ ������������� .
  #endif
        Prg.all &= ~_Sled ;              // ��������� ���� ��� ���������� �������� ����� �� �������� , ������
                                         // �� ������������� ��������� ����� 5 ����� .
        //---
        flg_RaTe._.tyr_tst_go = 0 ;      // ��� ���������� ������������ ������� ���� "������������ � ��������" .
    }
    //---
    // ��� ���������� ��������� ������������ "�������� ������ ����������" ���������� ��� ����� :
    if ( _r.Cfg2._.ProboyTir == 0 )
    {
      flg_RaTe._.tyr_tst_ok = 0 ;
      flg_RaTe._.tyr_tst_pr = 0 ;
      flg_RaTe._.tyr_tst_av = 0 ;
    }
    //---
    // ����� ���������� ���������� , ������� ��������� ��� ������ ��������� ������������ "�������� ������ ����������"
    // ������������ �� �������������� ������ , ����� ����� �������� ������������ ������������ ���������� ,
    // ���� ��� �������� ...
    //---
    // ��� ���� � ������ ����� �������� ����� �� �������� . ���������� ����� �������� ����� , ��� �����
    // ��������� � ���������� ����� ��� ��������� ��������� � ������ :
    if ( Prg._.Gotovn == 0 && flg_RaTe._.tyr_tst_ok == 1 )
    {
      flg_RaTe._.tyr_tst_ok = 0 ;
    }
#endif

    //---------------------------------------------------------------------------------------------------------------

    // 21.12.2013 12:56
    // ������ �� ������ ��������� ���� (��������, ��� � ����������), ����� �������� ������������� (����������� � ����)
    // �,��� ���������, "������" ��������, � ��, ��� �������� ���� ���� (�����, ���������� Q2 (Q1),
    // �������� ��������� ����� � �� ����, ��������� ��������� ��������� ��-�� ��������� ���� ��
    // ��������� ������� � ������) �� ��������� �������.
    if( Av._.Id_max == 0 )
    {
        Idmax2 = 0;
        time_Id_max2 = Puls_counter;
    }
    else
    {
            // ������� ������ ��������� ������� ����������, � ���� ����� �� ����������,
            // ������� ��������, ���������� � �������� ������.
            // ��������� ������� �� Timer1_Ovr � Puls_counter.
        ax = _r.Time_do_OtklImp * (_pSec( 1.0 ) / _Sec( 1.0 )) + _pSec( 0.2 );
        if( ( ( (u)((w)(Puls_counter - time_Id_max2)) > ax ) && ( Otkl_Imp != _Avar_imp ) ) )  Idmax2 = 1; // ��� �������

            //----------

        if( IDV >= _r.Id_Max
#ifndef _KTE_GD
    #ifdef _RVId
          || RVId.IDV1 >= _r.Id_Max || RVId.IDV2 >= _r.Id_Max
    #endif
#endif
          )
        {        // ���� ��� �� ������, ������ ����� ��������� �� �������� � ������ ����� ������
            if ( (u)((w)(Puls_counter - time_Id_max2)) > _pSec( 0.05 ) )    Idmax2 = 1; // ��� �������
        }

            //----------

        if ( Idmax2 == 1 )
        {
                mOtkl_Imp( _Avar_imp ) ;
                bo_Avar = 1 ;
                bo_Gotov = 0 ;
                bo_canAvar = 1 ;
                bo_canGotov = 0 ;
        #ifdef _ATK_SET
                bo_SA_canGotov = 0 ; //DAN 12.04.2025
                bo_SA_canAvar = 1 //DAN 12.04.2025
                bo_atkAvar = 1 ;
                bo_atkGotov = 0 ;
                bo_AvarATK = 1 ;
                bo_GotovATK = 0 ;
         #ifdef bo_Avar_Yach
                bo_Avar_Yach = 1 ;
                bo_AvarYacheykaATK = 1 ;
         #endif
        #endif
        #ifdef _POWER
                bo_MB1_Razr = 0 ;
        #endif

          #ifdef _KTE_GD
                bo_Vkl_LK = 0 ;
          #else
                bo_Vkl_QK1 = 0 ;
        #endif

#ifndef  _Adc_Extend_Po0 // ���� ���� 0 �� ������������ ��� ���������� ������� ��������������� ��� :
                Port_output (); // ���������������� ������ ������� ��������.
#else
                // ����� ������� � ����� ����� , � ������� ��������� ������ , ���������� , �������������� :
                S400_output ( _or.AS_CSo[_AsPo_Av_Pr_Got_] , _AsPo_Av_Pr_Got_);
#endif
        }
    }

    return;
  }

#endif
//----------------------------------------------

void Control_E_Max (void)
  {
    if ( ( EDS & 0x7fff ) > _r.E_Max )  //  �������� ������������ ���.
      {
        if ( Av._.Emax == 1 ) // �������� ����������� ����������.
          {
            mSet_AvarMsg( _Av_Emax ) ; // ���������� ���� ������ ������.
          }
        else  Av._.Emax = 1  ; // ����������� ������� ����������.
      }
    else  Av._.Emax = 0  ; // ���������� ���� ���������.

    return;
  }
//----------------------------------------------

void Control_N_Max (void)
  {
    if ( (sw)Skor > (sw)_r.N_Max || (sw)Skor < (sw)( ~_r.N_Max + 1 ))
          {
            if ( Av._.Nmax == 1 ) // �������� ����������� ����������.
              {
                mSet_AvarMsg( _Av_Nmax ) ; // ���������� ���� ������ ������.
              }
            else  Av._.Nmax = 1  ; // ����������� ������� ����������.
          }
        else  Av._.Nmax = 0  ; // ���������� ���� ���������.
    return;
  }
//----------------------------------------------
#ifdef _KTE_GD
//------
void Control_Ig_Ug_Max (void)
  {
  if ( IDV_g > _r.Ig_Max )   mSet_AvarMsg( _Av_Ig_max ) ;
#ifdef _RVId
  if ( IDV1  > _r.Ig_Max ) mSet_AvarMsg2 ( _Av2_Id1Max ) ;
  if ( IDV2  > _r.Ig_Max ) mSet_AvarMsg2 ( _Av2_Id2Max ) ;
#endif

  //    ���������� ������� �� ���������:
  //1.ax = Ugen ;                    =>  ax = Ugen
  //2.if ( (sw)ax < 0 ) ax = ~ax+1 ; =>  if ( (sw)Ugen < 0 ) ax = ~ax+1 ;
  //    ��� ���� ���� ���������� ������� ����� 1. � 2. � Ugen ���������� �
  // +1 �� -1, �� +1 � ax ��������������� � 0xFFFF � ����� ����������� ������.
  //3.if ( ax > _r.Ug_Max )
  //     ����� ���������� ����� ��� ��� ����, ����� �������� 'volatile'.
  //1.ax = (volatile)Ugen ;

  if ( (sw)Ugen > (sw)_r.Ug_Max || (sw)Ugen < (sw)( ~_r.Ug_Max + 1))
  {
    mSet_AvarMsg ( _Av_Ug_max )  ;
  }
    return;
  }
//----------------------------------------------

void Control_Ug_Min (void)
  {
    static word time ;
        //  chtoby mozshno bylo blokir. zaschitu po polyrnosty.
    if ( IDV >= _Id_nom( 0.25 ) && _r.Ug_Min != 0 )
    {
      // ���� ��� ���� ����������� ���������� ( �� ������ ) ������� ��� 25% :
      // 1. ���������� ���������� ������ ������������ � ������� 500�� -> ������ .
      // 2. ��� ����������� � ���������� ���������� ������ ������     -> ������ .
      if ( (sw)Ugen < (sw)_r.Ug_Min && (sw)Ugen > (sw)( ~_r.Ug_Min + 1))
      {
        if ((u)((w)(Timer1_Ovr - time)) > _Sec(0.5)) mSet_AvarMsg( _Av_Ug_min );
      }
      else
      {       // proverka polyarnosty Ug: ���� ��� � ���������� ������ ������...
        if ( ( (sw)Id_dop_kod > 0 && (sw)Ugen < 0 )
                                  ||
             ( (sw)Id_dop_kod < 0 && (sw)Ugen > 0 )) mSet_AvarMsg2 ( _Av2_Ug_polyarn )  ;
        else time = Timer1_Ovr ;
      }
    }
    else time = Timer1_Ovr ;
    return;
  }
//----------------------------------------------

void Control_Id_Min (void)
  {
    static word time ;

    if ( S.Alfa_Old <= _r.S_Alfa_Min && IDV < _r.Id_short_imp )
    {
      if ( (u)((w)(Timer1_Ovr - time)) > _Sec(1.0) ) mSet_AvarMsg( _Av_Id_min );
    }
    else time = Timer1_Ovr ;
    return;
  }
//----------------------------------------------

  // �������� ����������� �������������� ���������� .
  // ������� � ���� ������������ ���������� ��������� �� � ������� ���� ��
  // ��������� ��������� �� , ���� �� ��� �� ������� ���������� ���������� .
word Control_UgOstat ( void )
{
  word ah ;
  ah = 0 ;
 // chtoby mozshno bylo blokir. zaschitu .
 if ( _r.UgOstat != 0 )
 {
  if ( (sw)Ugen > (sw)(  (w)_r.UgOstat ) ||
       (sw)Ugen < (sw)( ~(w)_r.UgOstat + 1 ) )
    {
      mSet_PreduprMsg( _Pr_UgOstat ) ;
      ah = 1 ;
    }
  else mClr_PreduprMsg( _Pr_UgOstat ) ; // �����������, ����� �� ��������
 }                                      // ������ �������������� � "������" .
 return ah ;
}

//------
#endif
//----------------------------------------------

void Control_Power_Circuit (void)
  {
     // ������ , �������������� ����������� ������� ���� � ������� ���������� .
    //----
     // ��� ���������� �� , ������ ���� ������� "Id-���" �  ������ ������ �� ,
     // ������� ("Id-���"+10%Id���) , ����������� ����� �������� ������� 1.0� .
    //----
     //   � RT.C ���������� "ZIDN" ���� , � ������� ������������ ������������
     //   ������� �������� ������ ������ �� , ��� ���������� ���� � ����
     //   �������������� �������� ��������-������������ ���� , � ������ ������
     //   ���� ���������� ����� ������������ ������ ������ �� .
    static word time ;
           word ax ;

     // ������ ����������� ����������� "Id-���" �� ���� .
    ax = (volatile word)OuRegS ;  // � �� 'OuRegS' - ��������.
    if ( (sw)ax < 0 ) ax = ~ax+1 ; // (volatile) ����� ���������� �� �������������.

    if ( Prg._.RegTok == 1 &&
#ifndef _KTE_GD
     ( ( S.Disable == 0 && IDV   < _r.Id_Min && ax > (w)(_r.Id_Min + _Id_nom( 0.1 )) )
 #ifdef _SIFU2_
    // DAN 23.05.2017 14:46 - ��� ������ ������ ��2 :
    || ( S.Disable == 1 && IDV2  < _r.Id_Min && ax > (w)(_r.Id_Min + _Id_nom( 0.1 )) )
 #endif
                                                                                       ) )
#else
       IDV_g < _r.Id_Min && ax > (w)(_r.Id_Min + _Ig_nom( 0.1 )) )
#endif
     {
       if ( (u)((w)(Timer1_fSec-time)) > _r.T_Circuit )
        {
          mSet_AvarMsg( _Av_DC_Circuit ) ;
        }
     }
    else time = Timer1_fSec ;

    return;
  }
//----------------------------------------------

 // �������� ������� �������� ( �� ��� ��� ) �� ���������� �������� .
 // ���������� �������� Izm_Skor_EDS () ��������� :
 //    - ���  I-������ ��������� �� ��� ;
 //    - ��� II-������ ��������� �� ������������ ������� E=Ce�n => n=E/Ce� .
 // ������ "������������� ��" �������������� � ������ , ���� ����������
 // ���������� �������� �� ����������� ��������� ���������� � �������
 // �������� ������� .
void Control_DatSkor ( void )
{
  static word time ;
  register word ax, bx ;

#ifndef _ATK_SET
  // ���� ��� �� ��� �� �������� , ������� �� �������� ������ :
  if ( (_r.Sk_str._.TG == 0 && _r.Sk_str._.PDF == 0) || Prg._.RegSk == 0 ) return ;

  //---// ������� ������ ��� � �������� :
  ax = Skor_r ;
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "|N����|" - ������ ���������� �������� .
  bx = Skor ;
  if ( (sw)bx < 0 ) bx = ~bx + 1 ; // "|N|" - ������ �������� .

  //---  ��������� ����������� �� :
  ax -= bx ; // ���������� ���������� �������� �� ����������� .
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "| |N�|-|N| |" - ������ ���������� .
  if ( ax > _r.dN_Max )
   {
     if ( (u)((w)(Timer1_Ovr-time)) > _Sec(0.15) )
     {
#ifndef _Perecl_DS
       mSet_AvarMsg( _Av_dN_Max ) ;       // ��� ������������� �� - ��������� ���������� .
#else
       mSet_PreduprMsg( _Pr_Perecl_DS ) ; // ��� ������������� �� - ������������ �� ��� .
       _r.Sk_str._.TG = 0 , _r.Sk_str._.PDF = 0 ; // ���������� �� � ��� .
       _r.Sk_str._.EDS = 1 ;                      // ��������� ��� .
#endif
     }
   }
  else time = Timer1_Ovr ;

#else // ��� ��� :

  // ���� ��� ��� , ��� �� �������� , ��� ����� ��� , ��� ����� ������������ - ������� �� �������� ������ :
  // 29.06.2022 - ����� ����� �� �������� ������ ��� ���������� ������������ ������ , �.�. � ����
  //              ������ �������� ��� �� �������� , ��� �� ���-���������� ������ ���� ����������� :
  if ( _r.Sk_str._.PDF == 0 || Prg._.RegSk == 0 || ATK_flg._.trig_Pusk == 0 /*|| flgO._.Shunt_Rot == 1*/ )
  {
     time = Timer1_Ovr ;
     return ;
  }

  //---// ������� ������ ��� � �������� :
  ax = N_rot ;
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "|N_rot|" - ������ ���������� �������� �� ��� .
  bx = Skor ;
  if ( (sw)bx < 0 ) bx = ~bx + 1 ; // "|N|" - ������ �������� �� ��� .

  //---  ��������� ����������� �� :
  ax -= bx ; // ���������� ���������� �������� �� ����������� .
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "| |N�|-|N| |" - ������ ���������� .
  if ( ax > _r.dN_Max )
   {
     // 30.05.2021 - �������� ����� �������� ��� ������ �� ������������� �� , �.�. ��� �������� _Sec(0.15) ,
     // ��� ��������� � ������� ������� ��������� ( ��� �������� ���������� �� ������ N �� ��� = 100% ) ,
     // ������������ ������������� �� �� ���� , ��� �� ��� �� ���������� ���� ��������� ���������� ����������
     // �� ������� ( �� ���� �� ���������� �������� ) .
     if ( (u)((w)(Timer1_Ovr-time)) > _or.T_dN_Max ) //_Sec(1.5) ) // _Sec(0.15) )
     {
#ifndef _Perecl_DS
       mSet_AvarMsg( _Av_dN_Max ) ;       // ��� ������������� �� - ��������� ���������� .
#else
       mSet_PreduprMsg( _Pr_Perecl_DS ) ; // ��� ������������� �� - ������������ �� ��� .
       _r.Sk_str._.PDF = 0 ;              // ���������� ��� .
       _r.Sk_str._.EDS = 1 ;              // ��������� �������� �� ��� .
#endif
     }
   }
  else time = Timer1_Ovr ;

#endif

  return;
}
//----------------------------------------------
//
//    ��������� �������� ������� ��� ����� .

void  Control_Stoyanka ( void )
  {
    // �������� , ����� ����� �������������� �� ���� ������ , ��� ����� ������ :
    if ( (sw)_r.Stoyanka_Time_Predupr > (sw)_r.Stoyanka_Time ) _r.Stoyanka_Time_Predupr = (sw)_r.Stoyanka_Time ;
    //---
    if ( Prg._.Gotovn == 0 )
      {
   #ifndef _ATK_SET
        if ( ( EDS  & 0x7fff ) <= _r.Stoyanka_Eds  &&
#ifndef _KTE_GD
      ( (S.Disable == 0 && IDV >= _r.Stoyanka_Tok)
 #ifdef _SIFU2_                                    // DAN 23.05.2017 14:46 - ��� ������ ������ ��2 :
                                                   || (S.Disable == 1 && IDV2 >= _r.Stoyanka_Tok)
 #endif
                                                                                                  ) )
#else
                           IDV_g >= _r.Stoyanka_Tok  )
#endif
   #else
      //if ( ( Skor & 0x7fff ) <= _r.Stoyanka_Eds && Id_flt.out >= _r.Stoyanka_Tok  ) // 17.06.2021 - ����� �� ����������� ��� .
        if ( ( Skor & 0x7fff ) <= _r.Stoyanka_Eds && IDV >= _r.Stoyanka_Tok  )
   #endif
          {   //  �������� �� ���������� ��������������� "�������"
              // ��� ������ ��� ������� �������� - ��������� ����� �����
              // � ����� �������.
            if ( (u)Stoyanka_Timer <= _r.Stoyanka_Time_Predupr ) goto b1 ; // 05.04.2011 -  �� �������������� ������� ��������� ... _Sec(1.0) _Sec(0.2)
              // ����� ����� � ������� �������� - ������ �������� ������� .
            if ( (u)Stoyanka_Timer >= _r.Stoyanka_Time )
              {
                mSet_AvarMsg( _Av_Stoyanka ) ;
                mClr_PreduprMsg( _Pr_Stoyanka ) ;
              }
            else
              {
                mSet_PreduprMsg( _Pr_Stoyanka ) ;
           b1:  Stoyanka_Timer += Timer1_Ovr - Stoyanka_Time ;
              }
          }
        else if ( (u)Stoyanka_Timer <= _r.Stoyanka_Time_Predupr ) // 05.04.2011 -  �� �������������� ������� ��������� ... _Sec(1.0) _Sec(0.2)
                  Stoyanka_Timer = 0 ; // ������� ������������ ��� �
                                      // �� ������� ���� ��������� �����.
             else  goto a1 ; //  ��� ���� ����� ����� ������ �� ������ �������
      }                     // ���� ������ ��������, � �� ���� �������� ���
    else                   //  �� �����, ������ N-�������� ��������.
      {
  a1:   Stoyanka_Timer -= Timer1_Ovr - Stoyanka_Time ;
        if ( (sw)Stoyanka_Timer <= 0 ) Stoyanka_Timer = 0 ;
      }

    Stoyanka_Time = Timer1_Ovr ;

    return  ;
  }
//----------------------------------------------

  void  Control_Predohr ( void ) // �������� ��������������� .
       {
         //�������� �������������� �������� �������� :
      #ifdef  bi_KF_VKask
         //DAN 10.07.2017 10:44 - �������������� �� ����� �������� �������� ����� ����� ������� , ��� ��� �����������
         //                       ���������� ���������� ���� . ���������� ���������� , ����� ������� �������� ...
         //                       ������ ���� ���� ����� ����������� ������� � ����� ������ ����� ���� � ��� ���������
         //                       ���� ����� ��������� . ����� - ������ ������ �������������� . ����������� � ���������� ...
         if ( bi_KF_VKask == 0 )  mSet_AvarMsg2 ( _Av2_KF_VKask ) ;
       //if ( bi_KF_VKask == 0 )  mSet_PreduprMsg( _Pr_KF_VKask ) ; DAN 10.07.2017 10:44
      #endif

      // ��� ��2 � 12-�������� ���� :
      #ifdef  bi_KF_VKask2
         // �������� �������������� �������� �������� ����� �������� ����� :
         //DAN 10.07.2017 10:44 - �������������� �� ����� �������� �������� ����� ����� ������� , ��� ��� �����������
         //                       ���������� ���������� ���� . ���������� ���������� , ����� ������� �������� ...
         //                       ������ ���� ���� ����� ����������� ������� � ����� ������ ����� ���� � ��� ���������
         //                       ���� ����� ��������� . ����� - ������ ������ �������������� . ����������� � ���������� ...
         if ( bi_KF_VKask2 == 0 )  mSet_AvarMsg2 ( _Av2_KF_VKask2 ) ;
       //if ( bi_KF_VKask2 == 0 )  mSet_PreduprMsg2( _Pr2_KF_VKask2 ) ; DAN 10.07.2017 10:44
      #endif

      // ��� ��3 � 12-�������� ���� :
      #ifdef  bi_KF_VKask3
         if ( bi_KF_VKask3 == 0 )  mSet_AvarMsg3 ( _Av3_KF_VKask3 ) ;
      #endif

      // ��� ��4 � 12-�������� ���� :
      #ifdef  bi_KF_VKask4
         if ( bi_KF_VKask4 == 0 )  mSet_AvarMsg3 ( _Av3_KF_VKask4 ) ;
      #endif

          // �������� �������������� �������� �������� �����������
      #ifdef  _Vozb_KTE
         //DAN 10.07.2017 10:44 - �������������� �� ����� �������� �������� ����� ����� ������� , ��� ��� �����������
         //                       ���������� ���������� ���� . ���������� ���������� , ����� ������� �������� ...
         //                       ������ ���� ���� ����� ����������� ������� � ����� ������ ����� ���� � ��� ���������
         //                       ���� ����� ��������� . ����� - ������ ������ �������������� . ����������� � ���������� ...
         // �� ����� 407 ���� ���������� . ��� ���������� ������ �� �16 , ����� 338 ...
         if ( bi_KFV_VKask == 0 )  mSet_AvarMsg2 ( _Av2_KFV_VKask ) ;
       //if ( bi_KFV_VKask == 0 )  mSet_PreduprMsg( _Pr_KFV_VKask ) ; DAN 10.07.2017 10:44
      #endif

          // �������� ������� ���������� ��������� �������� �������� �������������� ������ ��� �������� ��������� :
      #ifdef  bi_KP
         // 12.12.2013 9:00 - � ����� � ��� � �� �������� �������������� ���� ������ �� ������������ , ��������
         // �������������� �� �������������� ���� ������ �� ����� ������� , ���� � �� ����� , ��� ���� � ���� .
         // 23.03.2016 15:19 - ������������ ����� � ���������� � ������ , �.�. ���� ������ � �� �� � ������ ,
         // �������� "�������� �������� ����������" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0
#if !(defined(_SIFU2_) && defined(bi_KP2))                                // 06.05.2019 - ���� � 6-�������� ��� ����� 2 ����� ��������
                                                      && S.NumMost == 1   //              �������� : ������ � ����� . ������������
#endif                                                                    //              ������ ���� ����� - ������� � ������ ������ .
                                                                        ) // ���� ��������� �� ,
         {
           if ( bi_KP == 0 ) // �������� �������� ������� :
           {
             // � ������ �������� :
             if ((u)((w)(Timer1_Ovr - Time_KP)) > _Sec(0.5))  mSet_AvarMsg2 ( _Av2_KP ) ;
           }
           else Time_KP = Timer1_Ovr ;
         }
         else   Time_KP = Timer1_Ovr ;
      #endif

         // ��� ��2 � 12-�������� ���� :
         // �������� ������� ���������� ��������� �������� �������� �������������� ������ ��� �������� ��������� :
      #ifdef  bi_KP2
         // 12.12.2013 9:00 - � ����� � ��� � �� �������� �������������� ���� ������ �� ������������ , ��������
         // �������������� �� �������������� ���� ������ �� ����� ������� , ���� � �� ����� , ��� ���� � ���� .
         // 23.03.2016 15:19 - ������������ ����� � ���������� � ������ , �.�. ���� ������ � �� �� � ������ ,
         // �������� "�������� �������� ����������" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0
         // 06.05.2019 - � ������ , ���� ��� ������������� � 2 ����� �������� �������� ����� � ����
         //              ������� ������ ����� ������ , ���������� ��� ���������� ���� �������� ...
#if !(defined(_SIFU2_) && defined(bi_KP))                                 // 06.05.2019 - ���� � 6-�������� ��� ����� 2 ����� ��������
                                                      && S.NumMost == 2   //              �������� : ������ � ����� . ������������
#endif                                                                    //              ������ ���� ����� - ������� � ������ ������ .
                                                                        ) // ���� ��������� �� ,
         {
           if ( bi_KP2 == 0 ) // �������� �������� ������� :
           {
             // � ������ �������� :
             if ((u)((w)(Timer1_Ovr - Time_KP2)) > _Sec(0.5)) mSet_AvarMsg2 ( _Av2_KP2 ) ;
           }
           else Time_KP2 = Timer1_Ovr ;
         }
         else   Time_KP2 = Timer1_Ovr ;
      #endif

         // ��� ��3 � 12-�������� ���� :
         // �������� ������� ���������� ��������� �������� �������� �������������� ������ ��� �������� ��������� :
      #ifdef  bi_KP3
         // 12.12.2013 9:00 - � ����� � ��� � �� �������� �������������� ���� ������ �� ������������ , ��������
         // �������������� �� �������������� ���� ������ �� ����� ������� , ���� � �� ����� , ��� ���� � ���� .
         // 23.03.2016 15:19 - ������������ ����� � ���������� � ������ , �.�. ���� ������ � �� �� � ������ ,
         // �������� "�������� �������� ����������" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0 ) // ���� ��������� �� ,
         {
           if ( bi_KP3 == 0 ) // �������� �������� ������� :
           {
             // � ������ �������� :
             if ((u)((w)(Timer1_Ovr - Time_KP3)) > _Sec(0.5)) mSet_AvarMsg3 ( _Av3_KP3 ) ;
           }
           else Time_KP3 = Timer1_Ovr ;
         }
         else   Time_KP3 = Timer1_Ovr ;
      #endif

         // ��� ��4 � 12-�������� ���� :
         // �������� ������� ���������� ��������� �������� �������� �������������� ������ ��� �������� ��������� :
      #ifdef  bi_KP4
         // 12.12.2013 9:00 - � ����� � ��� � �� �������� �������������� ���� ������ �� ������������ , ��������
         // �������������� �� �������������� ���� ������ �� ����� ������� , ���� � �� ����� , ��� ���� � ���� .
         // 23.03.2016 15:19 - ������������ ����� � ���������� � ������ , �.�. ���� ������ � �� �� � ������ ,
         // �������� "�������� �������� ����������" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0 ) // ���� ��������� �� ,
         {
           if ( bi_KP4 == 0 ) // �������� �������� ������� :
           {
             // � ������ �������� :
             if ((u)((w)(Timer1_Ovr - Time_KP4)) > _Sec(0.5)) mSet_AvarMsg3 ( _Av3_KP4 ) ;
           }
           else Time_KP4 = Timer1_Ovr ;
         }
         else   Time_KP4 = Timer1_Ovr ;
      #endif

        return ;
       }
//----------------------------------------------

#ifdef bi_PT
  void  Control_PT ( void ) // �������� ��������� ���������� .
       {
          //---
            //  "�������������� - ��������."
          if ( bi_PT == 0 )
            {
              mSet_PreduprMsg2( _Pr2_PT ) ;
  //-------
  //-------------------- ���� ���������� ���������� ������������� �� ��������� --------------------
  #ifdef bo_Vkl_Vent
              bo_Vkl_Vent = 1 ;  // ��������� ������������ .
              Time_t_tir = Timer1_Ovr ;
            }
          else if ( bo_Vkl_Vent == 1 ) // ���� ��������� ��� ��� , �� ����������� ��� �������� ,
            { // ������ �� ����������� ��� 10 ��� , ��� ���� ���-�� �� ������� �� "����.�������" :
              if ( (u)((w)(Timer1_Ovr - Time_t_tir)) > _r.Time_otkl_BV1 || Av._.DistSbros == 1 )
                {    // ����� ��������
                  bo_Vkl_Vent = 0 ; // ���������� ������������
                  mClr_PreduprMsg2( _Pr2_PT ) ;
                }
  #endif
  //-----------------------------------------------------------------------------------------------
            }
        return ;
       }
#endif

// ��� ��2 � 12-�������� ���� :
#ifdef bi_PT2
  void  Control_PT2 ( void ) // �������� ��������� ���������� .
       {
          //---
            //  "�������������� - ��������."
          if ( bi_PT2 == 0 )
            {
              mSet_PreduprMsg2( _Pr2_PT2 ) ;
  //-------
  //-------------------- ���� ���������� ���������� ������������� �� ��������� --------------------
  #ifdef bo_Vkl_Vent2
              bo_Vkl_Vent2 = 1 ;  // ��������� ������������ .
              Time_t_tir2 = Timer1_Ovr ;
            }
          else if ( bo_Vkl_Vent2 == 1 ) // ���� ��������� ��� ��� , �� ����������� ��� �������� ,
            { // ������ �� ����������� ��� 10 ��� , ��� ���� ���-�� �� ������� �� "����.�������" :
              if ( (u)((w)(Timer1_Ovr - Time_t_tir2)) > _r.Time_otkl_BV1 || Av._.DistSbros == 1 )
                {    // ����� ��������
                  bo_Vkl_Vent2 = 0 ; // ���������� ������������
                  mClr_PreduprMsg2( _Pr2_PT2 ) ;
                }
  #endif
  //-----------------------------------------------------------------------------------------------
            }
        return ;
       }
#endif

//-------------------------------------------------------------------------------------------------
//
//      ��������� ����������� ��-��.
//
//    ���� �������� ������� - 250 ���� . ������� ������� ������� 4�� =-50���� , 20�� =+200���� .
//                                                           ��� 4�� = 0����  , 20�� =+250���� .
//
//    ��� ������ ������� ( 0�� ) ������������ ����������� , ��������������� 4�� , �.�. �� ������
// ���� ������� . �� ���� ��� ������ ����������� ��������� � ���������� ����������� . ���������
// � ����� �������� - ���� .
//
//    ��������� ���� ����� :
//  |------|---------|-----------------|
//  |  ��  |  �, ��� | ���, -50...+200 |
//  |------|---------|-----------------|
//  |   0  |    0    |      -50        |
//  |   4  |   0.77  |      -50        |
//  |  12  |   2.33  |      +75        |
//  |  20  |   3.89  |      +200       |
//  ------------------------------------
//
void  Contr_Ttrans_4_20 ( word num )
{
//---
#ifndef  Ttrans_ach
//---
  num = num,  Ttrans = 0, Ttrans_4_20 = 0 ;
//---
#else
//---
  static word Ttrans_full, time_Ttr, Ttrans_4_20_drob, time_scan ;

  register word ax ;
  register lword lax ;

  switch ( num )
  {      //  ��������� �������������.
    case 0 :  Ttrans = 0, Ttrans_4_20 = 0, time_Ttr = Timer1_Ovr, Ttrans_4_20_drob = 0 ;

     start: Ttrans_full = _AD_BUSY ;  //  ������ ������� ��������� ��������
            AD_Izm ( Ttrans_ach, &Ttrans_full ) ;
      break;
         //  ������� ���������.
    case 1 :
          if ( (w)(u)(timer1-time_scan) >= _MkSec(10*1000) )
          {
            time_scan = timer1 ;
            //---

            if ( Ttrans_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Ttrans_full, ax, Ttrans_ach ) ;

                 //---   ���������, �.�. �� ����� ������ �� 4-20�� ���� ��������� 200�� � ���������� �� 15%.
                     //  ������ �� �����������, ��� ��� ��������� ���-���������� � ��������� ����� ������������ 4-20.
               lax  = (lw)Ttrans_4_20 << 16,    lax += (lw)(w)Ttrans_4_20_drob ;
                 lax += (slw)( ((lw)ax << 16) - lax ) / (sw)(_or.Filtr_Param * 2)  ;  // *2 - �.�. ������� �������� �������� �������.
               Ttrans_4_20 = (w)( lax >> 16 ),   Ttrans_4_20_drob = (w)lax ;
                 //---

               ax = Ttrans_4_20 ;

               //                              Ttr_20mA(���)-Ttr_4mA(���)
               //     Ttrans = Ttr_4mA(���) + ----------------------------  * (I-4mA)
               //                                         16mA

               ax -= _1mA_nom( 4 ) ;
               if ( (sw)ax <= 0 )  ax = 0 ;

               Ttrans = _or.Ttr_4mA + (w)( (lw)(w)(_or.Ttr_20mA - _or.Ttr_4mA ) * (lw)(sw)ax / _1mA_nom( 16 ) ) ;

            //--------------------

               goto start; //  ������ ���������� ���������.
             }
          }
      break;

    case 2 :                                          // ������ �� ������ 4-20��.
               if ( (sw)Ttrans >= (sw)_or.Ttr_predupr || (sw)Ttrans_4_20 <= (sw)_1mA_nom( 3 ) )
               {
                 if ( (u)(w)(Timer1_Ovr-time_Ttr) > _Sec( 1.0 ) )  mSet_PreduprMsg2( _Pr2_Ttr_predupr ) ;
               }
               else  time_Ttr = Timer1_Ovr ;

      break;
  }
//---
#endif
//---
  return ;
}

// ��������� ��������� ����������� , �� ��� ���������� ����������� �� ������ ������� .
void T_Izm_Dat(  word num )
{
//---
 #ifndef _Dat_Temp_Max
//---
  num = num ;
//---
#else
//---
  double ax;//float ax;
  word i;
  //---
  switch ( num )
  {
    default :
    break ;

         //  ��������� �������������.
    case 0 :
               Counter_Izm_T = 0;  // ������������� �������� .

             // ��� 2� ������� ������ :
               Izm_Temp[0].ach =  &T0_ach;
               Izm_Temp[1].ach =  &T1_ach;
               Izm_Temp[2].ach =  &T2_ach;
               Izm_Temp[3].ach =  &T3_ach;
               Izm_Temp[4].ach =  &T4_ach;
               Izm_Temp[5].ach =  &T5_ach;
               Izm_Temp[6].ach =  &T6_ach;
               Izm_Temp[7].ach =  &T7_ach;
               Izm_Temp[8].ach =  &T8_ach;
               Izm_Temp[9].ach =  &T9_ach;
               Izm_Temp[10].ach = &T10_ach;
               Izm_Temp[11].ach = &T11_ach;

             // ��� 4� ������� ������ :
#if defined _Dat_Temp_Max == 24
               Izm_Temp[12].ach = &T12_ach;
               Izm_Temp[13].ach = &T13_ach;
               Izm_Temp[14].ach = &T14_ach;
               Izm_Temp[15].ach = &T15_ach;
               Izm_Temp[16].ach = &T16_ach;
               Izm_Temp[17].ach = &T17_ach;
               Izm_Temp[18].ach = &T18_ach;
               Izm_Temp[19].ach = &T19_ach;
               Izm_Temp[20].ach = &T20_ach;
               Izm_Temp[21].ach = &T21_ach;
               Izm_Temp[22].ach = &T22_ach;
               Izm_Temp[23].ach = &T23_ach;
#endif
               for (i = 0; i < _Dat_Temp_Max; i++)
               {
                  Izm_Temp[i].full = _AD_BUSY ;  // ������������� ��� ��������� ������� .
               }

               // ��� ������ ������ - ����������� � ����� ������ �������� ���������� .
               Hotest.Temperat = -2730 ; // ���������� ���� �� �������� , ����� ��������� ���������� ������������� ����������� .
               Hotest.BKnumb   = 0 ;

               // ��������� ��������� ��� ����������� ����������� � ������ ������ �������� ���������� .
               Vrem.Temperat = -2730 ; // ���������� ���� �� �������� , ����� ��������� ���������� ������������� ����������� .
               Vrem.BKnumb   = 0 ;

      break;

         //  ������� ���������.
    case 1 :
     // ��� ����� �������� , � ��� ���� , ����� �� ������������� ��������� ��� ���� � �� �� ��������� , ��������� :
     if ( Izm_Temp[Counter_Izm_T].full != _AD_BUSY ) // ���� ��������� � ���������� ��� ��������� :
     {
       if ( Counter_Izm_T == 0 )
       {
         // ����� ������� ���������� - ���������� �� ��������� ���������  ����� �������� ���� ������� ����� ��������� :
         Hotest.Temperat = Vrem.Temperat ; // ����� ������� ����������� .
         Hotest.BKnumb   = Vrem.BKnumb   ; // ����� ���������� .
         //---
         // ���������� �� ��������� ��������� ������ ���������� , ����� ���� � ���� ������ :
         Vrem.Temperat = Temper[Counter_Izm_T] ;
         Vrem.BKnumb   = Counter_Izm_T+1 ;       // ����� ���������� , � ������ ��������� � ���� .
       }
       //---
       pru = &Izm_Temp[Counter_Izm_T] ;
       mIzmData_Conversion( Izm_Temp[Counter_Izm_T].full , ax , *pru->ach ) ;

       Izm_Temp[Counter_Izm_T].full = _AD_BUSY ; // ���������� � ���������� ��������� ����� ������ .

       ax = (double)ax/(double)_AD_VOLT_DVUPOL;//(float)ax/(float)_AD_VOLT_DVUPOL;
       // �� ����� 1 � ��� 100 ��� �������� .
       ax -= 2.73; // ������� � ��� ��������� ( 0 ��� � = 273 ��� � )
       //1000 - ������ ��� 1 � = 100 ��� , � ������ 1 ��� - 10 ������� .
       ax = ax*1000*_or.T_Scale[Counter_Izm_T];

       Temper[Counter_Izm_T] = (sw)ax ; // �6 ��������� � ��� ������������� , ������� ��������� ��������� ����� � ����� ...
     }

     // ���� ��� �������� ���������� ������� ������ , �� Name_Agr = 1 � ��������� ��� ��������� :
     // ����� ��������� � ��������� ������ � ���������� �� :
     if ( ( Name_Agr == 2 && Counter_Izm_T <  (_Dat_Temp_Max/2) /*<= 11*/ ) || // ������ ������� ���� , 6-�� �������� ����� ,
          ( Name_Agr == 3 && Counter_Izm_T >= (_Dat_Temp_Max/2) /*>= 12*/ ) || // ������ ������� ���� , 6-�� �������� ����� ,
            Name_Agr == 1 )                                                    // ��� �����, 12-�� �������� ����� :
     {
       // �������� ������ ����������� :
       if (Temper[Counter_Izm_T] >= _or.T_Av)
       {
         mSet_AvarMsg2 (_Av2_Izm_T ) ;
         mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
       }
       else if (Temper[Counter_Izm_T] >= _or.T_Pr )
       {
         mSet_PreduprMsg (_Pr_Izm_T ) ;
         mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
       }
       else
       {
         mClr_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
       }

       // ����������� ������ �������� ���������� :
       if ( (sw)Temper[Counter_Izm_T] > (sw)Vrem.Temperat )
       {
         // ������ �� ��������� ��������� :
         Vrem.Temperat = Temper[Counter_Izm_T] ; // ����� ������� ����������� , �� ���������� �� ������� ����� .
         Vrem.BKnumb   = Counter_Izm_T+1 ;       // ����� ���������� , � ������ ��������� � ���� .
       }
     }
      break;

         //  ������� ��������� .
    case 2 :
        // ������� � ���������� ...
        //---
        if ( Izm_Temp[Counter_Izm_T].full == _AD_BUSY ) // ���������� ��������� ���������� , � ������ ,
        {                                               // �������� ��������� ��������� :
          // ������ ����� �������� ���� ������ ����������� �� 24-� :
          if (++Counter_Izm_T >= _Dat_Temp_Max)
          {
            Counter_Izm_T = 0;
          }
          // _AD_BUSY ������� � ���� ����� ��������� ����������� ���������...
          pru = &Izm_Temp[Counter_Izm_T] ;
          // �������� ��������� , ��������� ������ ��� �������� � ���� :
          mAD_Izm( *pru->ach, &Izm_Temp[Counter_Izm_T].full ) ;
        }
      break;
  }
//---
#endif
//---
  return ;
}

//---------------------------------------------
//    �������� ����� � ��������� ������� : �������������� -> dt -> ������ ,
//  ���� dt ������ ������ ����, �� ����.����. ����������� .

void  Control_dt_Avar ( word code )
{
  static word time ;
  register word ax ;

  switch ( code )
  {
    case 0 :
//---
#ifdef bi_BV1 // ���� ���������� �������������� ���/���� ������������ , ��� �������� ����������
       Timer_BV1          = 0 ; // � ������� �� ���������/���������� Control_PT () .
#endif
//---
#ifdef bi_BV_2 // ��� ��2 � 12-�������� ���� :
       Timer_BV2          = 0 ;
#endif
//---
#ifdef bi_Vent_Dvig
       Timer_Vent_Dvig    = 0 ;
#endif
//---
#ifdef bi_MasloSmazka
       Timer_MasloSmazka  = 0 ;
#endif
//---
#ifdef bi_Smazka_Podsh
       Timer_Smazka_Podsh = 0 ;
#endif
//---
       time               = Timer1_Ovr ;
//---
    break;
        //--------
    case 1 :
      ax = Timer1_Ovr - time ,  time = Timer1_Ovr ;

//------------
#ifdef bi_BV1
 #ifndef bo_Vkl_Vent // ���� ���������� �������������� ���/���� ������������ , �������� �� ����� .
 if ( bi_BV1 == 0 )
  {
    mSet_PreduprMsg( _Pr_BV1 ) ;
    if ( _r.Time_otkl_BV1 != 0 ) // ��������� �� �������������� � ������ ?
     {
       if ( Prg._.Gotovn == 0 )  // � ������ :
        {
          if ( (u)Timer_BV1 >= _r.Time_otkl_BV1 ) mSet_AvarMsg( _Av_BV1 ) ;
          else    Timer_BV1 += ax ;
        }
        // � ������ ���������� , ��� ���� ����� ����� ���������� ���� ������
        // �������� � �� ���� �������� ��� �� ����� N-�������� �������� .
       else goto c1 ;
     }
  }
 else
  {
c1: Timer_BV1 -= ax ;
    if ( (sw)Timer_BV1 <= 0 ) Timer_BV1 = 0 ;
  }
 #else // ��� �������������� ���/���� ������������ �������������� "������������� ������������" :
 if ( bi_BV1 == 0 && bo_Vkl_Vent == 1 ) mSet_PreduprMsg( _Pr_BV1 ) ; // ��� ��1 .
 else                                   mClr_PreduprMsg( _Pr_BV1 ) ;
 //---
  #ifdef bi_BV2
   if ( bi_BV2 == 0 && bo_Vkl_Vent == 1 ) mSet_PreduprMsg2( _Pr2_BV2 ) ; // ��� ��2 .
   else                                   mClr_PreduprMsg2( _Pr2_BV2 ) ;
  #endif
 #endif
#endif
//------------
#ifdef bi_BV_2
 if ( bi_BV_2 == 0 ) // ��� ��2 � 12-�������� ���� :
  {
    mSet_PreduprMsg2( _Pr2_BV2 ) ;
    if ( _r.Time_otkl_BV1 != 0 ) // ��������� �� �������������� � ������ ?
     {
       if ( Prg._.Gotovn == 0 )  // � ������ :
        {
          if ( (u)Timer_BV2 >= _r.Time_otkl_BV1 ) mSet_AvarMsg2( _Av2_BV2 ) ;
          else    Timer_BV2 += ax ;
        }
        // � ������ ���������� , ��� ���� ����� ����� ���������� ���� ������
        // �������� � �� ���� �������� ��� �� ����� N-�������� �������� .
       else goto c11 ;
     }
  }
 else
  {
c11:Timer_BV2 -= ax ;
    if ( (sw)Timer_BV2 <= 0 ) Timer_BV2 = 0 ;
  }
#endif
//------------
#ifdef bi_Vent_Dvig
 if ( bi_Vent_Dvig == 0 )
  {
    mSet_PreduprMsg( _Pr_Vent_Dvig ) ;
    if ( _r.Time_otkl_VentDvig != 0 ) // ��������� �� �������������� � ������ ?
     {
       if ( Prg._.Gotovn == 0 )  // � ������ :
        {
          if ( (u)Timer_Vent_Dvig >= _r.Time_otkl_VentDvig ) mSet_AvarMsg( _Av_Vent_Dvig ) ;
          else    Timer_Vent_Dvig += ax ;
        }
        // � ������ ���������� , ��� ���� ����� ����� ���������� ���� ������
        // �������� � �� ���� �������� ��� �� ����� N-�������� �������� .
       else goto c2 ;
     }
  }
 else
  {
c2: Timer_Vent_Dvig -= ax ;
    if ( (sw)Timer_Vent_Dvig <= 0 ) Timer_Vent_Dvig = 0 ;
  }
#endif
//------------
#ifdef bi_MasloSmazka
 if ( bi_MasloSmazka == 0 )
  {
    mSet_PreduprMsg( _Pr_MasloSmazka ) ;
    if ( _r.Time_MasloSmazka != 0 ) // ��������� �� �������������� � ������ ?
     {
       if ( Prg._.Gotovn == 0 )  // � ������ :
        {
          if ( (u)Timer_MasloSmazka >= _r.Time_MasloSmazka ) mSet_AvarMsg( _Av_MasloSmazka ) ;
          else    Timer_MasloSmazka += ax ;
        }
        // � ������ ���������� , ��� ���� ����� ����� ���������� ���� ������
        // �������� � �� ���� �������� ��� �� ����� N-�������� �������� .
       else goto c3 ;
     }
  }
 else
  {
c3: Timer_MasloSmazka -= ax ;
    if ( (sw)Timer_MasloSmazka <= 0 ) Timer_MasloSmazka = 0 ;
  }
#endif
//------------
#ifdef bi_Smazka_Podsh
 if ( bi_Smazka_Podsh == 0 )
  {
    mSet_PreduprMsg( _Pr_Smazka_Podsh ) ;
    if ( _r.Time_Smazka_Podsh != 0 ) // ��������� �� �������������� � ������ ?
     {
       if ( Prg._.Gotovn == 0 )  // � ������ :
        {
          if ( (u)Timer_Smazka_Podsh >= _r.Time_Smazka_Podsh ) mSet_AvarMsg( _Av_Smazka_Podsh ) ;
          else    Timer_Smazka_Podsh += ax ;
        }
        // � ������ ���������� , ��� ���� ����� ����� ���������� ���� ������
        // �������� � �� ���� �������� ��� �� ����� N-�������� �������� .
       else goto c4 ;
     }
  }
 else
  {
c4: Timer_Smazka_Podsh -= ax ;
    if ( (sw)Timer_Smazka_Podsh <= 0 ) Timer_Smazka_Podsh = 0 ;
  }
#endif
//------------
    break;
  }
  return  ;
}

//-----------------------------

  // �������� ����������� �������� ���������.
word Control_Skor ( void )
{
  word ah ;
  ah = 0 ;
 // chtoby mozshno bylo blokir. zaschitu .
 if ( _r.Ostanov_skor != 0 )
 {
  if ( (sw)Skor > (sw)_r.Ostanov_skor  ||
       (sw)Skor < (sw)( ~_r.Ostanov_skor + 1 ) )
    {
      mSet_PreduprMsg( _Pr_Skor_NoNull  ) ;
      ah = 1 ;
    }
  else mClr_PreduprMsg( _Pr_Skor_NoNull  ) ;
 }
 return ah ;
}

//-----------------------------

word  Control_Power ( void )  //  "��������" ������� ��.
{
#ifdef  PUM_ach
 static word time ;
#endif
 //---
 switch ( N_Ucc2 )
 {
   default:
   case 0 :
  //---
#ifdef  PUM_ach
     N_Ucc2 = 1 ; // �������� ��������� :
     PUM_Ucc = _AD_BUSY ;
     AD_Izm ( PUM_ach, &PUM_Ucc ) ;
   break ;
  //---
   case 1 : // ��������� ������� ���������� �������� �������� �������� :
     if ( PUM_Ucc != _AD_BUSY )
      {
        mIzmData_Conversion ( PUM_Ucc , PUM_Ucc , PUM_ach ) ;
        if ( (sw)PUM_Ucc < (sw)_r.PUM_min || (sw)PUM_Ucc > (sw)_r.PUM_max )
         {
           // �������� ����������� ���������� :
           if ( Av2._.PUM == 1 ) // 09.03.2016 - ������� ��� ������������������� , �������� ������� .
           {           // �������� ������� - 7 ���� ( + ������ ���������� , + ���� �� ������� ... ) :
             if ( (u)((w)(timer1 - time)) > _MkSec(7u * 1000u) ) mSet_AvarMsg( _Av_PUM ) ;
           }
           else Av2._.PUM = 1 ;
         }
        else
        {
                time = timer1 ;
                Av2._.PUM = 0 ; // ���������� ���� ��������� .
        }
      }
#endif
//--------------
#ifdef   _SIFU2_
//--------------
#ifdef  _1P_ach
     N_Ucc2 = 2 ; // �������� ��������� :
     _1P_Ucc = _AD_BUSY ;
     AD_Izm ( _1P_ach, &_1P_Ucc ) ;
   break ;
  //---
   case 2 : // ��������� ������� �������������� �� :
     if ( _1P_Ucc != _AD_BUSY )
      {
        mIzmData_Conversion ( _1P_Ucc , _1P_Ucc , _1P_ach ) ;
        if ( (sw)_1P_Ucc < (sw)_r._1P_2P_min || (sw)_1P_Ucc > (sw)_r._1P_2P_max )
         {
           // �������� ����������� ����������.
           if ( Av2._._1P == 1 )  mSet_AvarMsg2( _Av2_1P ) ;
           else                   Av2._._1P = 1 ;
         }
        else    Av2._._1P = 0 ; // ���������� ���� ��������� .
      }
#endif
#ifdef  _2P_ach
     N_Ucc2 = 3 ; // �������� ��������� :
     _2P_Ucc = _AD_BUSY ;
     AD_Izm ( _2P_ach, &_2P_Ucc ) ;
   break ;
  //---
   case 3 : // ��������� ������� �������������� �� :
     if ( _2P_Ucc != _AD_BUSY )
      {
        mIzmData_Conversion ( _2P_Ucc , _2P_Ucc , _2P_ach ) ;
        if ( (sw)_2P_Ucc < (sw)_r._1P_2P_min || (sw)_2P_Ucc > (sw)_r._1P_2P_max )
         {
           // �������� ����������� ���������� :
           if ( Av2._._2P == 1 )  mSet_AvarMsg2( _Av2_2P ) ;
           else                   Av2._._2P = 1 ;
         }
        else    Av2._._2P = 0 ; // ���������� ���� ��������� .
      }
#endif
//--------------
#endif //_SIFU2_
//--------------
     N_Ucc2 = 0 ; // ������� �� ������� ��������� :
   break ;
 }
return 0 ;
}

/*-------------------------------------------------*/
//      ������������� �������� �������� ����������� ���������� �� �������
//  ���������� � �������� ��-�� �����.��������.
//
#ifdef Insul_G_ach
word  Contr_Insulat_G ( word num )
{
  static word Uinsul_full , Insul_time, Insul_timer ;
  static word Ud_insul ;
  static byte Ud_insul_drob ;
#ifdef  _Av2_InsulatG
  static word Insul_timer_av;
#endif

  register lword lax ;
  register word ax, bx ;

  switch ( num )
  {      //  ��������� �������������.
    case 0 :  UinsulG = 0, Insul_time = Timer1_Ovr, Insul_timer = 0 ;
              Ud_insul = 0 , Ud_insul_drob = 0 ;
         #ifdef  _Av2_InsulatG
              Insul_timer_av = 0 ;
         #endif
     start: Uinsul_full = _AD_BUSY ;  //  ������ ������� ��������� ��������
            AD_Izm ( Insul_G_ach,    &Uinsul_full ) ;
      break;
         //  ������� ���������.
    case 1 :
            if ( Uinsul_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Uinsul_full, ax, Insul_G_ach ) ;
                 if ( (sw)ax < 0 ) ax = ~ax+1 ;

                    //  ����������.
                    // ��������� ����� � �����.
               lax  = (slw)(sw)UinsulG << 8 ;
               lax += (lw)(w)UinsulG_drob ;   // DROB IS NOT SIGNED !

               if ( ax > UinsulG ) lax += _Insul_koef ;
               else                lax -= _Insul_koef ;

               UinsulG_drob = lax ;           // return drob.
               ax          = (slw)lax >> 8;
               if ( (sw)ax < 0 )  ax = 0 ;
               UinsulG = ax ;

               bx = _UoutG ;   //  �������� ������ Uout.
               if ( (sw)bx < 0 ) bx = ~bx+1 ;
                    //  ���������� �������� ����������, ����� ��� ���������� � ��� ��
                    //      ���������� ��� � ���������� ��������.
                    // ��������� ����� � �����.
               lax  = (slw)(sw)Ud_insul << 8 ;
               lax += (lw)(w)Ud_insul_drob ;

               if ( bx > Ud_insul ) lax += _Insul_koef ;
               else                 lax -= _Insul_koef ;

               Ud_insul_drob = lax ;           // return drob.
               bx            = (slw)lax >> 8;
               if ( (sw)bx < 0 )  bx = 0 ;
               Ud_insul = bx ;

                  //  �� �������. ����� ��� ������ ����������, �.�.�����
                  // ��������� � ���� � ����������� � ��.���.
               if( bx < _UoutG_nom( 0.25 ))  bx = _UoutG_nom( 0.25 ) ;
                   //  ��������� ������ ������������ ��������������� Uout:
                   //            porog = porog * Uout / UoutG_nom.
               lax = (lw)bx * (lw)_r.Uinsul_max ;
               UinsulG_max  = lax / _UoutG_nom( 1.0 ) ;

               ax = Timer1_Ovr-Insul_time ;
               Insul_time = Timer1_Ovr ;
                   //  �������� ������ �������� � ��������� �������.
               if ( UinsulG > UinsulG_max  && bi_Otkl_Insul == 0 )
               {     // �������� �������������� ���� 15.05.06 17:01
                 if ( (sw)Insul_timer > (sw)_Sec( 5 ) )  // 9 ) )
                 {
                   mSet_PreduprMsg2( _Pr2_InsulatG ) ;
                 }
                 else Insul_timer += ax ;
               }   //  �������� ���� �� ����������� ����� ����, � ��� � ���������...
               else if ( (sw)Insul_timer > 0 ) Insul_timer -= ax ;

                     //  �������������� � �������� ������ ���������
                    // ������ ����� ����.�����.
               if ( (Reg_PreduprMsg2 & _Pr2_InsulatG) != (lw)r0 )
                                                      bo_InsulatG = 1 ;
               else                                   bo_InsulatG = 0 ;
            //--------------------

          #ifdef  _Av2_InsulatG
               lax = (lw)bx * (lw)_or.Uinsul_max_av ;
               bx = lax / _UoutG_nom( 1.0 ) ;

                   //  �������� ������ �������� � ��������� �������.
               if ( UinsulG > bx && bi_Otkl_Insul == 0 )
               {      //  ������ ����� ���� ��������� ���� �����������������.
                 if ( (sw)_or.Tinsul != 0 )  // �������� �������������� ���� 15.05.06 17:01
                 {
                   if ( (sw)Insul_timer_av > (sw)_or.Tinsul )  // 9
                   {
                     mSet_AvarMsg2( _Av2_InsulatG ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
                 else
                 {
                   if ( (sw)Insul_timer_av > (sw)_Sec( 5 ) )
                   {
                     mSet_PreduprMsg2( _Pr2_InsulatG2 ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
               }   //  �������� ���� �� ����������� ����� ����, � ��� � ���������...
               else if ( (sw)Insul_timer_av > 0 ) Insul_timer_av -= ax ;
          #endif

               //-----
               goto start; //  ������ ���������� ���������.
             }
      break;
  }
  return 0 ;
}
#endif
/*-------------------------------------------------*/
//      ������������� �������� �������� ����������� ��������� �� �������
//  ���������� � �������� ��-�� �����.��������.
//
#ifdef Insul_D_ach
word  Contr_Insulat_D ( word num )
{
  static word Uinsul_full , Insul_time, Insul_timer ;
  static word Ud_insul ;
  static byte Ud_insul_drob ;
#ifdef  _Av2_InsulatD
  static word Insul_timer_av;
#endif

  register lword lax ;
  register word ax, bx ;

  switch ( num )
  {      //  ��������� �������������.
    case 0 :  UinsulD = 0, Insul_time = Timer1_Ovr, Insul_timer = 0 ;
              Ud_insul = 0 , Ud_insul_drob = 0 ;
         #ifdef  _Av2_InsulatD
              Insul_timer_av = 0 ;
         #endif
     start: Uinsul_full = _AD_BUSY ;  //  ������ ������� ��������� ��������
            AD_Izm ( Insul_D_ach,    &Uinsul_full ) ;
      break;
         //  ������� ���������.
    case 1 :
            if ( Uinsul_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Uinsul_full, ax, Insul_D_ach ) ;
                 if ( (sw)ax < 0 ) ax = ~ax+1 ;

                    //  ����������.
                    // ��������� ����� � �����.
               lax  = (slw)(sw)UinsulD << 8 ;
               lax += (lw)(w)UinsulD_drob ;   // DROB IS NOT SIGNED !

               if ( ax > UinsulD ) lax += _Insul_koef ;
               else                lax -= _Insul_koef ;

               UinsulD_drob = lax ;           // return drob.
               ax          = (slw)lax >> 8;
               if ( (sw)ax < 0 )  ax = 0 ;
               UinsulD = ax ;

      #ifndef  Uf_ach  // ���� ���������� ����������� �� ���������� :
                // ��� ���������� � ������. ���� :
         #ifndef _KTE_GD                                //  �������� ������ Uout.
               if ( _r.Cfg._.Iv_Econom == 1 && bi_QK1 == 0 ) bx = _or.Uf_econom ;
         #else
               if ( _r.Cfg._.Iv_Econom == 1 && bi_LK  == 0 ) bx = _or.Uf_econom ;
         #endif
               // ����� ���� ����������� , ������������� �� ������� :
               else bx = _UoutD_nom( 1.00 ) ;
               Uf = bx ;
      #else
               bx = _UoutD ;   //  �������� ������ Uout.
               if ( (sw)bx < 0 ) bx = ~bx+1 ;
      #endif
                    //  ���������� �������� ����������, ����� ��� ���������� � ��� ��
                    //      ���������� ��� � ���������� ��������.
                    // ��������� ����� � �����.
               lax  = (slw)(sw)Ud_insul << 8 ;
               lax += (lw)(w)Ud_insul_drob ;

               if ( bx > Ud_insul ) lax += _Insul_koef ;
               else                 lax -= _Insul_koef ;

               Ud_insul_drob = lax ;           // return drob.
               bx            = (slw)lax >> 8;
               if ( (sw)bx < 0 )  bx = 0 ;
               Ud_insul = bx ;

                  //  �� �������. ����� ��� ������ ����������, �.�.�����
                  // ��������� � ���� � ����������� � ��.���.
               if( bx < _UoutD_nom( 0.25 ))  bx = _UoutD_nom( 0.25 ) ;
                   //  ��������� ������ ������������ ��������������� Uout:
                   //            porog = porog * Uout / UoutD_nom.
               lax = (lw)bx * (lw)_r.Uinsul_max ;
               UinsulD_max  = lax / _UoutD_nom( 1.0 ) ;

               ax = Timer1_Ovr-Insul_time ;
               Insul_time = Timer1_Ovr ;
                   //  �������� ������ �������� � ��������� �������.
               if ( UinsulD > UinsulD_max  && bi_Otkl_Insul == 0 )
               {     // �������� �������������� ���� 15.05.06 17:01
                 if ( (sw)Insul_timer > (sw)_Sec( 5 ) )  // 9 ) )
                 {
                   mSet_PreduprMsg2( _Pr2_InsulatD ) ;
                 }
                 else Insul_timer += ax ;
               }   //  �������� ���� �� ����������� ����� ����, � ��� � ���������...
               else if ( (sw)Insul_timer > 0 ) Insul_timer -= ax ;

                     //  �������������� � �������� ������ ���������
                    // ������ ����� ����.�����.
               if ( (Reg_PreduprMsg2 & _Pr2_InsulatD) != (lw)r0 )
                                                      bo_InsulatD = 1 ;
               else                                   bo_InsulatD = 0 ;
            //--------------------

          #ifdef  _Av2_InsulatD
               lax = (lw)bx * (lw)_or.Uinsul_max_av ;
               bx = lax / _UoutD_nom( 1.0 ) ;

                   //  �������� ������ �������� � ��������� �������.
               if ( UinsulD > bx && bi_Otkl_Insul == 0 )
               {      //  ������ ����� ���� ��������� ���� �����������������.
                 if ( (sw)_or.Tinsul != 0 )  // �������� �������������� ���� 15.05.06 17:01
                 {
                   if ( (sw)Insul_timer_av > (sw)_or.Tinsul )  // 9
                   {
                     mSet_AvarMsg2( _Av2_InsulatD ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
                 else
                 {
                   if ( (sw)Insul_timer_av > (sw)_Sec( 5 ) )
                   {
                     mSet_PreduprMsg2( _Pr2_InsulatD2 ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
               }   //  �������� ���� �� ����������� ����� ����, � ��� � ���������...
               else if ( (sw)Insul_timer_av > 0 ) Insul_timer_av -= ax ;
          #endif

               //-----
               goto start; //  ������ ���������� ���������.
             }
      break;
  }
  return 0 ;
}
#endif
//-----------------------------

// "�������� ���������� ������������� ����������"
#ifdef  bi_QKDT
void Control_QKDT ( void )
{
  static word time ;

  if ( bi_QKDT == 1 ) // ���� ��������� �� ������� ,
  {
     mSet_ServiceMsg( _Srv_QKDT ) ;
     if ( bi_QK1 == 0 ) time = Timer1_fSec ;
     else if ( (u)((w)(Timer1_fSec-time)) > _fSec( 3.0 ) ) // �� ���. > 3 ���.
     {
        mSet_AvarMsg2 ( _Av2_QKDT ) ;
     }
  }
  else
  {
    time = Timer1_fSec ;
    mClr_ServiceMsg( _Srv_QKDT ) ;
  }
return ;
}
#endif
//-----------------------------

// "���������� ����������� ������������� ����������"
#ifdef  bo_QKDT
void Upr_QKDT ( void )
{
  //���� �������� � ��� �������� - �������� ��������� ���.����������,
  //�.�. ��������� ��������� ��
  #ifndef _KTE_GD
      if ( bi_QK1 == 1 && bi_AK1 == 1 )
  #else
      if ( bi_LK == 1 )
  #endif
           bo_QKDT = 1 ;
      else bo_QKDT = 0 ;

return ;
}
#endif
//-----------------------------

word MechTorm_upr ( word num )
{
  static word time2 , time3 ;
  static byte trigg , trigg2 ;
  static word time_MT ;
  static word time2_MT ;
  register word ax ;
#ifdef bi_MT
  static word time_MT_Err ;
  static byte trigg_MT_Err ;
#endif

  switch ( num )
  {
    case _MT_Init :
          trigg = 1 , trigg2 = 0 ;
          time2 = Timer1_Ovr ;
          time3 = Timer1_Ovr ;
          time_MT = Timer1_Ovr ;
          time2_MT = Timer1_Ovr ;
#ifdef bi_MT
          time_MT_Err = Timer1_Ovr ;
          trigg_MT_Err = 0 ;
#endif
    break;

      //------**************************************************---------
    case _MT_Upr :
        // ���������/������ ������������� �������.
      if ( _r.Cfg._.MT == 1 )
      {
  //******
 #ifndef  _MT_Podyom
  //******
        if ( bi_QK1 == 1 && bo_Avar == 0 && Prg._.Gotovn == 0 )
        {
          bo_MT = 1 ; // ������� �� .
          time_MT = Timer1_Ovr ;
        }
        else if ( bo_MT == 1 ) // ���� �� �� ������� , ����������� :
        {
            // �������� ����������� �������� ���������.
          if (((sw)Skor > (sw)_r.Ostanov_skor
                        ||
               (sw)Skor < (sw)( ~_r.Ostanov_skor + 1 ))) bo_MT = 1 ;
          else bo_MT = 0 ;

           // ��� ������������� ��-���������� ������������ � ��-��������� :
          if ( _r.Time_MT != 0 ) // ���� ������� ������� ������ ,
           { // �� ������������� �� �������� �� ����������� ��������� :
             if ( (u)((w)(Timer1_Ovr-time_MT)) > _r.Time_MT ) bo_MT = 0 ;
           } // ���������� �� �� ������� , ��� � �� ����������� ���� _MT_Podyom.
        }

  //******
 #else
  //******
            // ���� ��-��� ���-�� ������� ������ �������� ����.� �����.
        if ( bo_MT == 0 && trigg2 == 1 )
        {
          time_MT = Timer1_Ovr ;
          trigg2 = 0 ;
        }

            // �������� �������� ������ � ������ ���� ���������� ��.
        if ( bo_Avar == 0 && bi_QK1 == 1 && Prg._.Gotovn == 0 )
        {     // ���������������� �� ����, ��������������� �� �� ��������.
      #ifndef _KTE_GD
          if ( IDV   >= _r.Id_Otkl_MT )
      #else
          if ( IDV_g >= _r.Id_Otkl_MT )
      #endif
          {                         //'+1'-����� ����.����� � ����������
            if ( (u)((w)(Timer1_Ovr-time_MT)) > (_r.Time_MT+1) )  trigg2 = 1 ;
          }
          else time_MT = Timer1_Ovr ;
        }
        else
        {
          time_MT = Timer1_Ovr ;
          trigg2 = 0 ;
        }
        //----
        //if ( bo_MT == 1 && trigg2 == 0 ) {...} ��������� � �����. �� ������� �� ����

        if( (sw)ZISkor < (sw)_r.Ostanov_skor && (sw)ZISkor > (sw)( ~_r.Ostanov_skor + 1 )
             && Z_Skor == 0 ) // DAN 02.12.2010 15:15 - ��� ��������� ��� �� �������� ���������� ���
            //             || // ������� �������� . ��������� �� ��� ��� - 9 .
          //(sw)Skor < (sw)_r.Ostanov_skor && (sw)Skor > (sw)( ~_r.Ostanov_skor + 1 ))
        {
          if ( (u)((w)(Timer1_Ovr-time2_MT)) > _r.Time_MT )
          {
            time_MT = Timer1_Ovr ;
            trigg2 = 0 ;
          }
        }
        else time2_MT = Timer1_Ovr ;
        //---
        if ( trigg2 == 1 ) bo_MT = 1 ;
        else               bo_MT = 0 ;
  //******
 #endif
  //******
      }
      else
      {   // ��������� ���.����. �� CAN ���� ��������� ��� ���. �� ���.
        can_ConfigReg ( _CAN_MT ) ;
      }
          // ��������� ���.����. ��������.
        obj_ConfigReg ( _Obj_MT ) ;

    #ifdef bi_MT           // 02.05.2020 18:47 �� ������� �������� �.�. �������� ����������� �������.
        if ( bo_MT == 0 )  // ���������� �� ����� 35-36 ����. ��� �� ������� ���� �������� ��������,
        {                  // � � �� �� ��� �� ��������.
          time_MT_Err = Timer1_Ovr ;
          trigg_MT_Err = 0 ;
        }
        else
        {
          if ( _r.Time_MT_Err != 0 )
          {
            if ( (u)((w)(Timer1_Ovr - time_MT_Err)) > _r.Time_MT_Err )
            {
              trigg_MT_Err = 1 ;
            }
          }
        }
        if ( bi_MT == 0 && trigg_MT_Err == 1 ) mSet_AvarMsg2( _Av2_MT_Err ) ;
    #endif

    break;

      //------**************************************************---------
    case _MT_Id_Zad_Ogr: // ������ ��� ��������� ���������� :
            // ������ ����������� ���� ����� ���� ������� ������
            // � ��������� ����� ����� ������ ���������, ����� ���� �����
            // ��������� �������� �������.
 #ifdef  _MT_Podyom
      if ( _r.Cfg._.MT == 1 )
      {
        if ( bo_MT == 0 ) // �������� ������� �������� �� :
        {
          time2 = Timer1_Ovr ;
           // ������������ ��� ���������� ����� ������ , �� ������ ���������� :
          if ( (u)((w)(Timer1_Ovr - time3)) > _r.Time_MT ) trigg = 1 ;
        }
        else // �������� ������� ����� �� :
        {
          time3 = Timer1_Ovr ;
           // ����� ������� �������� �� ������ �� � ������������ ���� :
          if ( (u)((w)(Timer1_Ovr - time2)) > _r.Time_MT ) trigg = 0 ;
        }
        // ����������� ������� �� ��� :
        if ( trigg == 1 && ( (sw)ZISkor > (sw)_r.Ostanov_skor
                                        ||
                             (sw)ZISkor < (sw)( ~_r.Ostanov_skor + 1 ) ) )
        {
          ax = _r.Id_Otkl_MT + _Id_nom( 0.1 ) ;
          if ( (sw)OuRegS >= 0 )
          {
            if ((sw)OuRegS > (sw)ax ) OuRegS = ax , Prz._.int_p = 1 ;
          }
          else
          {
            ax = ~ax+1 ;
            if ((sw)OuRegS < (sw)ax ) OuRegS = ax , Prz._.int_m = 1 ;
          }
        }
      }
 #else
      ax = 0 ; // �������� ��� ����������� � ��������������� �� .
 #endif
    break;
  }
  return 0 ;
}

//-----------------------

#ifdef _ATK_SET
void Otkl_Q1_ATK ( void ) // ��������� ������� Q1 ��� ���������� ���� �� ������������ �������������� .
{
  if ( Prg._.Gotovn == 0 )
  {
       //02.08.2017 8:00 - ��������� ������� Q1 �� ������� ��� �������� � �������� :
       if ( (bi_Pusk == 1 && flgO._.Vedushiy == 1) || (ATK2_Pusk == 1 && flgO._.Vedushiy == 0) )
       {
         mOtkl_Q1 () ; // DAN 07.06.2017 17:13 - �������� � ������ ��������� Q1 .
#ifdef   bo_atkOtkl_Q1
         bo_atkOtkl_Q1 = 1 ; // ���������� ���� ���������� Q1 ��� �������� �� ������ ��� .
#endif
       }
  }
  return ;
}
#endif

//----------- �������� ��� �������������� ������/�������������� --------------
//----------------- ( ��� ����������� ����� � AVAR.H ) -----------------------
#ifndef    _Av_Iv_Max
  #define  _Av_Iv_Max        0
#endif
#ifndef    _Av2_Id1Max
  #define  _Av2_Id1Max       0
#endif
#ifndef    _Av2_Id2Max
  #define  _Av2_Id2Max       0
#endif
#ifndef    _Av2_Id2_Max
  #define  _Av2_Id2_Max      0
#endif
#ifndef    _Av_Id_sum_Max
  #define  _Av_Id_sum_Max    0
#endif
#ifndef    _Av_Gercon3
  #define  _Av_Gercon3       0      // ��� ��������� � 4-�� �� .
#endif
#ifndef    _Av_Gercon4
  #define  _Av_Gercon4       0      // ��� ��������� � 4-�� �� .
#endif
#ifndef    _Av_PUM
  #define  _Av_PUM           0
#endif
#ifndef    _Av2_1P
  #define  _Av2_1P           0
#endif
#ifndef    _Av2_2P
  #define  _Av2_2P           0
#endif
#ifndef    _Pr_AF1P
  #define  _Pr_AF1P          0
#endif
#ifndef    _Pr_WDT
  #define  _Pr_WDT           0
#endif
#ifndef    _Av2_AF2
  #define  _Av2_AF2          0
#endif
#ifndef    _Pr2_AF2P
  #define  _Pr2_AF2P         0
#endif
#ifndef    _Pr3_BK1A
  #define  _Pr3_BK1A         0
#endif
#ifndef    _Pr3_BK1B
  #define  _Pr3_BK1B         0
#endif
#ifndef    _Pr3_BK1C
  #define  _Pr3_BK1C         0
#endif
#ifndef    _Pr3_BK2A
  #define  _Pr3_BK2A         0
#endif
#ifndef    _Pr3_BK2B
  #define  _Pr3_BK2B         0
#endif
#ifndef    _Pr3_BK2C
  #define  _Pr3_BK2C         0
#endif
#ifndef    _Pr_Perecl_DS
  #define  _Pr_Perecl_DS     0
#endif
#ifndef    _Pr2_ProbM1_VT11_24
  #define  _Pr2_ProbM1_VT11_24  0
#endif
#ifndef    _Pr2_ProbM1_VT12_25
  #define  _Pr2_ProbM1_VT12_25  0
#endif
#ifndef    _Pr2_ProbM1_VT13_26
  #define  _Pr2_ProbM1_VT13_26  0
#endif
#ifndef    _Pr2_ProbM1_VT14_21
  #define  _Pr2_ProbM1_VT14_21  0
#endif
#ifndef    _Pr2_ProbM1_VT15_22
  #define  _Pr2_ProbM1_VT15_22  0
#endif
#ifndef    _Pr2_ProbM1_VT16_23
  #define  _Pr2_ProbM1_VT16_23  0
#endif
#ifndef    _Pr2_ProbM2_VT11_24
  #define  _Pr2_ProbM2_VT11_24  0
#endif
#ifndef    _Pr2_ProbM2_VT12_25
  #define  _Pr2_ProbM2_VT12_25  0
#endif
#ifndef    _Pr2_ProbM2_VT13_26
  #define  _Pr2_ProbM2_VT13_26  0
#endif
#ifndef    _Pr2_ProbM2_VT14_21
  #define  _Pr2_ProbM2_VT14_21  0
#endif
#ifndef    _Pr2_ProbM2_VT15_22
  #define  _Pr2_ProbM2_VT15_22  0
#endif
#ifndef    _Pr2_ProbM2_VT16_23
  #define  _Pr2_ProbM2_VT16_23  0
#endif
#ifndef    _Pr2_ProbM3_VT11_24
  #define  _Pr2_ProbM3_VT11_24  0   // ��� ��������� � 4-�� �� .
#endif
#ifndef    _Pr2_ProbM3_VT12_25
  #define  _Pr2_ProbM3_VT12_25  0
#endif
#ifndef    _Pr2_ProbM3_VT13_26
  #define  _Pr2_ProbM3_VT13_26  0
#endif
#ifndef    _Pr2_ProbM3_VT14_21
  #define  _Pr2_ProbM3_VT14_21  0
#endif
#ifndef    _Pr2_ProbM3_VT15_22
  #define  _Pr2_ProbM3_VT15_22  0
#endif
#ifndef    _Pr2_ProbM3_VT16_23
  #define  _Pr2_ProbM3_VT16_23  0
#endif
#ifndef    _Pr2_ProbM4_VT11_24
  #define  _Pr2_ProbM4_VT11_24  0   // ��� ��������� � 4-�� �� .
#endif
#ifndef    _Pr2_ProbM4_VT12_25
  #define  _Pr2_ProbM4_VT12_25  0
#endif
#ifndef    _Pr2_ProbM4_VT13_26
  #define  _Pr2_ProbM4_VT13_26  0
#endif
#ifndef    _Pr2_ProbM4_VT14_21
  #define  _Pr2_ProbM4_VT14_21  0
#endif
#ifndef    _Pr2_ProbM4_VT15_22
  #define  _Pr2_ProbM4_VT15_22  0
#endif
#ifndef    _Pr2_ProbM4_VT16_23
  #define  _Pr2_ProbM4_VT16_23  0
#endif
#ifndef    _Srv_NoCAN_QK
  #define  _Srv_NoCAN_QK     0
#endif
#ifndef    _Srv_Not_Nul_Id
  #define  _Srv_Not_Nul_Id   0
#endif
#ifndef    _Srv_Not_Iv
  #define  _Srv_Not_Iv       0
#endif
#ifndef    _Srv_AN_Av
  #define  _Srv_AN_Av        0
#endif
#ifndef    _Srv_AN_Ra_Te
  #define  _Srv_AN_Ra_Te     0
#endif
#ifndef    _Srv_AN_Tm
  #define  _Srv_AN_Tm        0
#endif
#ifndef    _Srv_AN_Err
  #define  _Srv_AN_Err       0
#endif
#ifndef    _Srv_AN_Kreg
  #define  _Srv_AN_Kreg      0
#endif
#ifndef    _Srv_AN_Iv_min
  #define  _Srv_AN_Iv_min    0
#endif
#ifndef    _Srv_No_EDS_Nom
  #define  _Srv_No_EDS_Nom   0
#endif
//---------------------------------------------
//-----------------------------

 word Common_avar ( void )
 {
#ifdef   Iv_ach
    static byte Ivmin ;
#endif
#ifdef   bo_DS_MT
    static word time_ds ;
#endif

      // ����� ��������� ��������� ����� ����� �������� , �������� ,
    ObjPrg ( _Obj_c_Common_avar ) ; // ��� ������� ��������� .

    Contr_Ttrans_4_20 ( 1 ) ; // ������� ��������� ������� ����������� �������������� .
    Zad_Skor_4_20 ( 1 ) ; // ������� ��������� ������� ������� ����� 4-20 �� .
    Mashtab_Dat () ;
    Control_Power_Circuit () ;
  //08.04.2008 11:31 - ��� ���������� �������� ������� �� ������ Id-max ����� ����� � ����
  //�������� Id_Max , �.�. ��� ����� ��������� � �������������� ���� ����������� � ���� .
  //Control_Id_Max () ;
#ifndef _ATK_SET // ��� �� �� ����� ( ��� ��� ���� ) .
    Control_E_Max  () ;
    Control_N_Max  () ;
#endif
    Control_DatSkor () ; // ��� ��� ���������� .
#ifdef _KTE_GD
    Control_Ig_Ug_Max () ;
    Control_Ug_Min () ;
    Control_Id_Min () ;
#endif
    Contr_Insulat( 1 ) ;
  #ifdef Insul_G_ach
    Contr_Insulat_G( 1 ) ; // �������� �������� ����������� ���������� .
  #endif
  #ifdef Insul_D_ach
    Contr_Insulat_D( 1 ) ; // �������� �������� ����������� ��������� .
  #endif

    can_ConfigReg ( _CAN_Avar ) ;  // CAN-������� ���������� ����������.

#ifndef _ALARM_FZ
  #ifdef  _Union_FR
    if ( Av._.P24 == 1 )
    {
      mSet_PreduprMsg( _Pr_P24) ;
      //��������� ����������� ���������� 1�24
      Av._.P24 = 0;
      Alarm_on();
    }
  #endif
#endif

    Control_Ucc () ;        //  �������� �������� ����������.
    Control_Power () ;      //  �������� ������� ��.
    Control_Predohr () ;    //  �������� ��������������� (���.����.).
    Control_Stoyanka () ;   //  �������� ������� �� �����.
    Control_Gercon () ;     //  �������� �������� ��������.
    Contr_Ttrans_4_20 ( 2 ) ; // ��������� � ������ �������������� ������� ����������� �������������� .
    Zad_Skor_4_20 ( 2 ) ;     // ��������� � ������ �������������� ������ ������� .
    T_Izm_Dat ( 1 ) ;         // ��������� ���������� ��������q ����������� ������� ���������� � ������ ������� ����� � ������ ��������� .

   //  Usrednitel( &Iv_usr, 2); // ���������� � REG_EDS.C
   //  V.Iv = (sw)( (slw)(sw)V.Iv_full * (slw)(sw)_r.Mashtab_Iv >> 8 ) ;


//-------------------------- ��������� ������������ --------------------------
//------------------------- �� ����� ������� ������ --------------------------
#ifdef bo_VklVent
//---
   // �������� ����������� �� ��������� ( ���� ���� ������� ����������� ) ��� � ������ �� ������������ ����
   if ( (Prg._.Gotovn == 0 && bo_Avar == 0 && (IDV >= _or.Id_Vkl_Vent
  #if defined(_SIFU2_) && !defined(bo_VklVent2) // ���� ����������� ���������� � 12-�� �������� ������������ :
                                                                     || IDV2 >= _or.Id_Vkl_Vent
  #endif
                                                                                                ) )
  #ifdef _Dat_Temp_Max
              || Hotest.Temperat >= _or.T_Pr
  #endif
                                             )
   {
      bo_VklVent = 1 ; // �������� ����������� .
      //---
      timerVent = Timer1_Ovr ;
   }
   else if ( bo_VklVent == 1 ) // ���� ���� ��� ��� , �� ����������� �������� ,
   { // ������ �� ����������� ��� ��������� ����� , ��� ���� ���-�� �� ������� �� "����.�������" :
        if ( (u)((w)(Timer1_Ovr - timerVent)) > _or.T_Otkl_Vent || Av._.DistSbros == 1 )
          {    // ����� ��������
            bo_VklVent = 0 ;  // ���������� ������������ .
          }
   }
#endif
//----------------------------------------------------------------------------
#if defined(_SIFU2_) && defined(bo_VklVent2) // ���� ����������� ���������� � 12-�� �������� �� ������������ :
   // �������� ����������� �� ��������� ( ���� ���� ������� ����������� ) ��� � ������ �� ������������ ����
   if ( (Prg._.Gotovn == 0 && bo_Avar == 0 && IDV2 >= _or.Id_Vkl_Vent )
  #ifdef _Dat_Temp_Max
                                                                        || Hotest.Temperat >= _or.T_Pr
  #endif
                                                                                                       )
   {
      bo_VklVent2 = 1 ; // �������� ����������� .
      //---
      timerVent2 = Timer1_Ovr ;
   }
   else if ( bo_VklVent2 == 1 ) // ���� ���� ��� ��� , �� ����������� �������� ,
   { // ������ �� ����������� ��� ��������� ����� , ��� ���� ���-�� �� ������� �� "����.�������" :
        if ( (u)((w)(Timer1_Ovr - timerVent2)) > _or.T_Otkl_Vent || Av._.DistSbros == 1 )
          {    // ����� ��������
            bo_VklVent2 = 0 ;  // ���������� ������������ .
          }
   }
#endif
//----------------------------------------------------------------------------


#ifdef   It_ach  // ��� ��������� � ���������� ���� ������� :
    Usrednitel( &It_usr, 2);
    It = (sw)( (slw)(sw)It_full * (slw)(sw)_r.Mashtab_It >> 8 ) ;
#endif

#ifdef   bo_DS_MT // ��� ��������������� ������ ����� �� :
        // �������� ����������� �������� ( �����  300 �� ��������� ����� ����������� ) :
    if ( bo_DS_MT == 0 ) time_ds = Timer1_Ovr ;
    else if ( (u)((w)(Timer1_Ovr-time_ds)) > _Sec( 0.3 ) ) bo_DS_MT = 0 ;
#endif

#ifdef   Iv_ach
 #ifdef   _AVTONASTR
  if ( Isp._.AvtoNastr == 1 && AnastrRT == 0 ) ; // ���������� �� ����� ���������.
  else
 #endif
   {    //  "����������� ��� �����������".
    if ( V.Iv < _r.Iv_avar_Min
   #ifdef _RVId
      || V2.Iv < _r.Iv_avar_Min
   #endif
       )
     {
        if ( ((b)(Puls_counter - time_Iv_min) > _r.time_Iv_min) || Ivmin == 1 )
         {
   #ifdef _RVId
           if ( V.Iv < _r.Iv_avar_Min ) mSet_AvarMsg( _Av_Iv_Min ) ;
           if ( V2.Iv < _r.Iv_avar_Min ) mSet_AvarMsg2( _Av2_Iv2_Min ) ;
   #else
           mSet_AvarMsg( _Av_Iv_Min ) ;
   #endif
           Ivmin = 1 ; // ����� ������� Puls_counter ��������� , ��������� ���������� ���� ...
         }
     }
    else time_Iv_min = Puls_counter , Ivmin = 0 ;
   }
#endif
      //   �������� ���������� ��������� ��������, ��� �������
      // �������� ����� "������" :
    if ( Isp._.Predupr == 1 )   mSet_PreduprMsg( _Pr_ServiceProg   ) ;


//--- ��� �����. �������� ���� �� ���� �����, � ����.�� ��380.
#ifdef  _SIFU_Syn2    // ���� �� ��������� ������������� �� ����� ��� ����.
  if ( _r.Cfg2._.SIFU_Syn2 == 1 )
  {
#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn2.T1_ovr)) >= 3 )
#else   // �� ���������� �������� 1000 ��/��� ��� �� ������ ����� 166 ��� � ��� "�����������"
      if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn2.T1_ovr)) >= 9 ) ||
          ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn2.T1_ovr)) >= 3 ) )
#endif
      {
        mSet_AvarMsg ( _Av_NoSynch2 ) ;
#ifdef _ATK_SET
        Otkl_Q1_ATK () ; // ��������� ������� Q1 ��� ���������� ���� �� ������������ �������������� .
        flgO._.Usil_ok = 0 ;
      }
      else flgO._.Usil_ok = 1 ;
#else
  }
#endif
  // ��� ���������� ������ ������������� ���������� �������� ���������� ������� - ����������
  // �� ���5-50 ���� 14.09.2018 .
  // 28.05.2020 DAN - ������ ��������������� �� ��� Syn2.b_SIauto , �.�. ����� ������
  // ������� ������������� �� ���������� ...
  // ��� ���������� ������ ������������� , ����� �� ����������� ����� ������ , �������� � �������
  // ���������������� ��� ������ ������� ������������� .
  /* �������� ������� �� ����������� �������� */
  if      ( (u)Tsyn2 < _r.TMIN )
  {
    mSet_AvarMsg2 ( _Av2_Tmin2 ) ;
#ifdef _ATK_SET
    Otkl_Q1_ATK () ; // ��������� ������� Q1 ��� ���������� ���� �� ������������ �������������� .
    flgO._.UsilTMIN_ok = 0 ;
#endif
  }
  /* �������� ������� �� ������������ �������� */
  else if ( (u)Tsyn2 > _r.TMAX )
  {
    mSet_AvarMsg2 ( _Av2_Tmax2 ) ;
#ifdef _ATK_SET
    Otkl_Q1_ATK () ; // ��������� ������� Q1 ��� ���������� ���� �� ������������ �������������� .
    flgO._.UsilTMAX_ok = 0 ;
  }
  else // ������ � ������� :
  {
    flgO._.UsilTMIN_ok = 1 ;
    flgO._.UsilTMAX_ok = 1 ;
  }
  
  //�������� ������������� ������������� ��� ������������ ������������� �� ����
  if (!flgO._.Usil_ok || !flgO._.UsilTMIN_ok || !flgO._.UsilTMAX_ok) 
  {
#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 )  mSet_AvarMsg ( _Av_NoSynch ) ;
#else   // �� ���������� �������� 1000 ��/��� ��� �� ������ ����� 166 ��� � ��� "�����������"
    if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 9 ) ||
        ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 ) )  mSet_AvarMsg ( _Av_NoSynch ) ;
#endif
    /* �������� ������� �� ����������� �������� */
    if      ( (u)Tsyn < _r.TMIN )   mSet_AvarMsg ( _Av_Tmin ) ;
    /* �������� ������� �� ������������ �������� */
    else if ( (u)Tsyn > _r.TMAX )   mSet_AvarMsg ( _Av_Tmax ) ;
  }
  
 }
  else   // ��������� ������ ������������� - ������� ��� ����� :
  {
    flgO._.Usil_ok = 0 ;
    flgO._.UsilTMIN_ok = 0 ;
    flgO._.UsilTMAX_ok = 0 ;

#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 )  mSet_AvarMsg ( _Av_NoSynch ) ;
#else   // �� ���������� �������� 1000 ��/��� ��� �� ������ ����� 166 ��� � ��� "�����������"
    if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 9 ) ||
        ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 ) )  mSet_AvarMsg ( _Av_NoSynch ) ;
#endif
    /* �������� ������� �� ����������� �������� */
    if      ( (u)Tsyn < _r.TMIN )   mSet_AvarMsg ( _Av_Tmin ) ;
    /* �������� ������� �� ������������ �������� */
    else if ( (u)Tsyn > _r.TMAX )   mSet_AvarMsg ( _Av_Tmax ) ;
    
    
  }
#else
      }
    }
  }
#endif

#else //_SIFU_Syn2

#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 )  mSet_AvarMsg ( _Av_NoSynch ) ;
#else   // �� ���������� �������� 1000 ��/��� ��� �� ������ ����� 166 ��� � ��� "�����������"
    if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 9 ) ||
        ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 ) )  mSet_AvarMsg ( _Av_NoSynch ) ;
#endif
    /* �������� ������� �� ����������� �������� */
    if      ( (u)Tsyn < _r.TMIN )   mSet_AvarMsg ( _Av_Tmin ) ;
    /* �������� ������� �� ������������ �������� */
    else if ( (u)Tsyn > _r.TMAX )   mSet_AvarMsg ( _Av_Tmax ) ;


#endif

#ifdef _ATK_SET
  #ifdef   bo_atkOtkl_Q1
    //02.08.2017 8:00 - �������� ����� , ��� ��������� Q1 ���� � ����� , ���� ���� ������� �� ����� �� ��� :
    if ( ATK2_Otkl_Q1 == 1 ) mOtkl_Q1 () ;
  #endif
#endif

        /* �������� ��������� �������� �����������. */
    if ( Id_teplo_max <= _r.Id_teplo_predupr )   mSet_PreduprMsg ( _Pr_Teplo ) ;

#ifndef _KTE_GD
 #ifdef _SIFU2_
  if ( S.Disable == 1 ) // DAN 23.05.2017 14:46 - ��� ������ ������ ��2 :
  {
    if ( IDV2 >= Id_teplo_max )   mSet_AvarMsg ( _Av_Teplo ) ;
  }
  else
 #endif
  {
   #ifndef _ATK_SET
    if ( IDV >= Id_teplo_max )   mSet_AvarMsg ( _Av_Teplo ) ;
   #else // � ������ �� ������ ������� �� ����� � ��� ����� ����������� �� ����� .
    if ( Irot >= Id_teplo_max )  mSet_AvarMsg ( _Av_Teplo ) ; // � ������ �� ��� ����� ������ � �������� ���� , Id = 0 .
   #endif
  }
#else
    if ( IDV_g >= Id_teplo_max )   mSet_AvarMsg ( _Av_Teplo ) ;
#endif

#ifdef _ATK_SET // � ��1 ������� ��������� , ��� ���������� ������� ������ :
      //----------------------------------------------- ������ ��������� ------------------------------------------------------

      //------------------------------------------- ����� ��� ������� -----------------------------------------
      // ����� ��� ������� ������� ��� ������������� ������� ������������ ���������� �������� ( 3000 ��/ ��� )
      // ��� ��������� � 1 ����� ������� � ����������� �������� ��������� .                  // �������� :
                                                                                             // 3000 ->  Z = 1
      //---                                                                                  // 1500 ->  Z = 2
      Pary_AD = (w)3000 / _or.N_nom ;                                                        // 1000 ->  Z = 3

      //-----------------------------
      // �������� ������� ���� w0 , ���/� :
      //
      //   w��� = 2 * _PI * f
      //
      OmegaNom = (float)2 * _PI * 50 ; //Syn.Fsyn/360 - �������� ������� ���� ��� ������ ...

      //-----------------------------
      // ���������� �������� , ���/� :
      //
      //         w���
      //   w0 = ------
      //          Z
      //
      OmegaNullSynhr = (float)OmegaNom / (float)(w)Pary_AD ;

      //------------------------------
      // ���������� �������� ������ � ��/��� :
      N_ob_minSynhr = _RadS_ObMin * OmegaNullSynhr ;

      // ��� ����������� �������� ��� ����������� �������� - ��� ���������� �������� :
      //if ( _sr.NOM.N.fe != N_ob_minSynhr ) _sr.NOM.N.fe = N_ob_minSynhr ; // ����� ������� ���� ��� .
      // 21.12.2020 - ��� ����� �� ���������� ���� ��������� :
      // ��� ����������� �������� ��� ����������� �������� - ��� ����������� �������� ��������� .
      // ������� �� ���������� �������� 300/11.52 = 26.04 ��/��� . �.�. _sr.NOM.N.fe = 26 ��/��� .
      //------------------------------

      // 15.10.2020 - ����� ���� ��������� ��� ������� ��� .
      //              �� ����� ���������� ������ ���� , ����� ������ �������� ���������� ��������� � ����������� ������ .
      //
      // Ud���  = U������ * 1.35 * Cos B��� ;
      //
      // Ud���� = Urot��� * S * 1.35 * Cos Lrot ;
      //
      // Ud���  = Ud���� ;
      //
      // U������ * 1.35 * Cos B��� = Urot��� * S * 1.35 * Cos Lrot ;
      //
      // U������ * Cos B��� = Urot��� * S * Cos Lrot ;
      //
      //             Urot��� * S * Cos Lrot
      // Cos B��� = ------------------------ ;
      //                   U������
      //
      //                  Urot��� * S * Cos Lrot
      // B��� = arccos ( ------------------------ ) ;
      //                        U������
      //
      // L��� = 180 ��� - B��� ;

      // ���������� , ������� � �������� ��� �������� :
      // ������������� � ���������� ������ ������� ��� 6 ��� ��2 ( ������� ��1 �� ����������� � �������� ) :
      if ( S.flg._.Invertor == 1 ) CosLrot = cosf( (float)(2 *_PI * (float)(w)_Grad( 120 ) ) / (float)(w)_Grad( 360 ) ) ; // ��.���. -> ���
      else                         CosLrot = cosf( (float)(2 *_PI * (float)(w)_Grad(   6 ) ) / (float)(w)_Grad( 360 ) ) ;

      Beta = acosf( (float)(w)_or.Urot_nom * (float)(w)Srot * CosLrot / (float)(w)_Ud_Nom / (float)(w)_or.Uset_nom ) ;

      OIRT_for_revers = (sw)(float)( (_PI - Beta) * (float)(w)_Grad( 360 ) / (2 *_PI) ) ; // ��� -> ��.���.

      //---------------------------------------- ������ ��������� -------------------------------------------------------------

      // ������ ��������� :
      // � = Kform * Irot * CosLrot_istin ,
      // ��� �form - ����������� ����� .
      //---
      // CosLrot �� ����������� ����������� ��� ������� ����� ������ , �.�. � ��� ������ �������������� CosLrot
      // ��� �������� � ������ ����� . ������� ����� ������������ �������� CosLrot_istin :
      if ( S.flg._.Invertor == 1 ) CosLrot_istin = cosf( (float)(2 *_PI * (float)(w)_Grad(   6 ) ) / (float)(w)_Grad( 360 ) ) ; // ��.���. -> ���
      else                         CosLrot_istin = cosf( (float)(2 *_PI * (float)(w)_Grad( 120 ) ) / (float)(w)_Grad( 360 ) ) ;
      //---
      // ��������� :
      // 1. �������� ��� ������ �� , � ������� �������� �� , �.�. ���� ���������� 0 ��� ( ������� ����� ) �� ������ , �.�.
      //    ������� ����� Cos 6 ��� � Cos 0 ��� ������������� .
      // 2. ��� �������������� ���������� 170 ��� ���� �� ������ ���������� �������� .

      // ����������� ������ ��������� - ������������ ������������ ������������ ���� �� Kform :

      Mom_nom = Kform * (float)(w)_sr.NOM.Id.fe * (float)_sqr2_3mask ; //0.816 ;
      Mom     = Kform * (float)(w)Irot * CosLrot_istin ;
      Moment = (sw)(float)( Mom / Mom_nom * (float)(w)_Mom_Nom ) ;

      //-----------------------------------------------------------------------------------------------------------------------
#endif

      //  �������� ������� ��������� � ����������������� ��������.
     if ( bi_2P24 != 1 )   //  "�������� 2P24"
        {
              //  "���������� ������� ����"
          if ( bi_AK1 == 0 )   mSet_AvarMsg( _Av_AK1 ) ;

     #ifdef bi_AK2
              //  "���������� ������� ����":
              //   1. Q2 .
              //   2. ��� ������ ��������� Q1 �� ������ ������� ����� ��2 .
          if ( bi_AK2 == 0 )   mSet_AvarMsg2( _Av2_AK2 ) ;
     #endif

              //  "����������� ��� - 1AF"
          if ( bi_AF1 == 1 )
            {
              mSet_AvarMsg( _Av_AF1 ) ;
     #ifdef _AF_Otkl_Q1 // 20.05.2009 - ������ ��������� � ������ � �� �� ������ �������������� .
              mOtkl_Q1 () ; // 29.02.2008 13:18 - ���������� � ������ ������ Q1 ��������� .
     #endif
            }

     #ifdef bi_AF2 // ��� ������ ��������� :
              //  "����������� ��� - 1AF �� ������ ������� ����� ��2"
          if ( bi_AF2 == 1 )
            {
              mSet_AvarMsg2( _Av2_AF2 ) ;
     #ifdef _AF_Otkl_Q1 // 20.05.2009 - ������ ��������� � ������ � �� �� ������ �������������� .
              mOtkl_Q1 () ; // 29.02.2008 13:18 - ���������� � ������ ������ Q1 ��������� .
     #endif
            }
     #endif

     #ifdef bi_AF1P
              //  "����������� ��� - 1AF"
          if ( bi_AF1P == 1 )   mSet_PreduprMsg( _Pr_AF1P ) ;
     #endif

     #ifdef bi_AF2P // ��� ������ ��������� :
              //  "����������� ��� - 1AF"
          if ( bi_AF2P == 1 )   mSet_PreduprMsg2( _Pr2_AF2P ) ;
     #endif

     #ifdef   bi_GL1
      #ifdef   _AVTONASTR
       if ( Isp._.AvtoNastr == 1 && AnastrRT == 0 ) ; // ���������� �� ����� ���������.
       else
      #endif       //  "������������� �����������"
          {
            if ( bi_GL1 == 1 )   mSet_AvarMsg( _Av_GL1 ) ;
          #ifdef _RVId
            if ( bi_GL2 == 1 )   mSet_AvarMsg2( _Av2_GL2 ) ;
          #endif
          }
     #endif

     #ifdef bi_MT // bi_GY1
              //  "������������� ��X���������� �������"
          //if ( bi_GY1 == 0 )   mSet_AvarMsg2( _Av2_GY1 ) ;

              //  "��X������������ ������ ��X���������� �������"
          if ( bi_MT  == 0 )   mSet_ServiceMsg( _Srv_MT ) ;
          else                 mClr_ServiceMsg( _Srv_MT ) ;
     #endif

     #ifdef bi_SF3
              //  "������� ��������������X ��������� - �����������, �� , �� � ��"
          if ( bi_SF3 == 0 )   mSet_AvarMsg2( _Av2_SF3 ) ;
     #endif

     #ifdef bi_SFV1
              //  "������� ����������� ��1"
         if ( bi_SFV1 == 0 ) mSet_PreduprMsg2( _Pr2_SFV1 ) ;
     #endif

     #ifdef bi_SFV2
              //  "������� ����������� ��2"
         if ( bi_SFV2 == 0 ) mSet_PreduprMsg2( _Pr2_SFV2 ) ;
     #endif

     #ifdef bi_SFV3
              //  "������� ����������� ��3"
         if ( bi_SFV3 == 0 ) mSet_PreduprMsg2( _Pr2_SFV3 ) ;
     #endif

     #ifdef bi_SFV4
              //  "������� ����������� ��4"
         if ( bi_SFV4 == 0 ) mSet_PreduprMsg2( _Pr2_SFV4 ) ;
     #endif

              //  "�������� ��������"
          if ( bi_AR1 == 1 )   mSet_PreduprMsg( _Pr_Insulat ) ;  // _Pr_AR1

     #ifdef bi_PR1
          // ����������� ������ �������� �������������� � ����� ����������� ����� .
          // ����� ���������� �� ������ �������������� � ������ ����� , ��� �����
          // ��� ���� ��������� ������ "bi_PR1"
          if ( bi_PR1 == 0 ) //  "������� �������������� 1"
            {
              mSet_PreduprMsg( _Pr_PR1 ) ;
          #ifdef bi_BV1
              if ( bi_BV1 == 0 ) mSet_AvarMsg( _Av_PR1 ) ;
          #else
//          #ifdef bi_TK1 20.05.2020 09:48
//            if ( bi_TK1 == 0 ) mSet_AvarMsg( _Av_PR1 ) ;
//          #endif
          #endif
         //---
            }
     #endif

     #ifdef bi_PR2
          // ����������� ���X ������� ��������������� � ����� ����������� ����� .
          // ����� ���������� �� ������ �������������� � ������ ����� , ��� �����
          // ��� ���� ��������� ������ "bi_PR1"
          if ( bi_PR2 == 0 ) //  "������� �������������� 2"
            {
              mSet_AvarMsg( _Av_PR2 ) ;
            }
     #endif

     //------------ ��� ��2 ------------
     #ifdef bi_2PR1
          // ����������� ������ �������� �������������� � ����� ����������� ����� ��2 .
          // ����� ���������� �� ������ �������������� � ������ ����� ��2 , ��� �����
          // ��� ���� ��������� ������ "bi_2PR1"
          if ( bi_2PR1 == 0 ) //  "������� �������������� 1"
            {
              mSet_PreduprMsg2( _Pr2_2PR1 ) ;
          #ifdef bi_BV1
              if ( bi_BV1 == 0 ) mSet_AvarMsg2( _Av2_2PR1 ) ;
          #else
//          #ifdef bi_TK1 20.05.2020 09:48
//            if ( bi_TK1 == 0 ) mSet_AvarMsg2( _Av2_2PR1 ) ;
//          #endif
          #endif
         //---
            }
     #endif
     #ifdef bi_2PR2
          // ����������� ���X ������� ��������������� � ����� ����������� ����� ��2 .
          // ����� ���������� �� ������ �������������� � ������ ����� ��2 , ��� �����
          // ��� ���� ��������� ������ "bi_PR1"
          if ( bi_2PR2 == 0 ) //  "������� �������������� 2"
            {
              mSet_AvarMsg2( _Av2_2PR2 ) ;
            }
     #endif
     //---------------------------------

     #ifdef _KTE_GD
              //  "�������� ��������� ���������� � ���� �-�"
          if ( bi_LK == 0 )    mSet_ServiceMsg( _Srv_LK ) ;
          else                 mClr_ServiceMsg( _Srv_LK ) ;
     #endif

     #ifdef bi_QKDT
          Control_QKDT () ; //  "�������� ���������� ������������� ����������"
     #endif

     #ifdef bo_QKDT
          Upr_QKDT () ; //  "���������� ����������� ������������� ����������"
     #endif

     #ifdef bi_MB1
              //  "�������� �/� ����������"
          if ( bi_MB1 == 0 )   mSet_AvarMsg2( _Av2_MB1 ) ;
     #endif

     #ifdef bi_AM1
              //  "�������� �������� ����������"
          if ( bi_AM1 == 0 )   mSet_AvarMsg2( _Av2_AM1 ) ;
     #endif

     #ifdef bi_AM2
              //  "�������� �������� ���������� - 2"
          if ( bi_AM2 == 0 )   mSet_AvarMsg2( _Av2_AM2 ) ;
     #endif

     #ifdef bi_VAT
              //  "�������� ����ר����� ���� . ��� ������ , ����� ��� - ��� �� ��������� �������������� ��������"
          if ( bi_VAT   == 0 ) mSet_AvarMsg2( _Av2_VAT ) ;
     #endif

     //#ifdef bi_RV1 - 14.10.2008 11:40 - �������� � ���������� �� ������� 2� .
     //         //  "������������ ���"
     //     if ( bi_RV1 == 1 )   mSet_AvarMsg2( _Av2_RV1 ) ;
     //#endif

     #ifdef bi_RV1_VAT
                // �/� ������������ ����������� ��� . ������ ������� ��� ��� , �.�. ��� ��� ��������� .
          if ( bi_RV1_VAT == 1 ) mSet_AvarMsg3( _Av3_RV1_VAT ) ;
     #endif

     #ifdef bi_SQ1
              //  "������� ����������"
          if ( bi_SQ1 == 0 )
            {
        #ifndef _ATK_SET
              mSet_AvarMsg2( _Av2_SQ1 ) ;
          #ifdef _POWER
              bo_MB1_Otkl = 1 ; // ���������� ��������� �����������
          #else
              mOtkl_Q1 () ; // 29.02.2008 13:18 - ������ �����, ���� �� �������� ,
          #endif            //                    �� ���� �� Q1 ��������� .
            }
        #else
              mSet_AvarMsg( _Av_SQ1 ) ;
              // ��������� Q1 ��� ������ , ������� ����� �������� ������ � �������� ��� ,
              // ���� ���� ��� ��������� �� ������� :
              bo_atkSQ1 = 1 ; // ���������� ��� ��������� ��� ���� .
              // ����� ���� , ��������� �������� � ����� ������ ������ � ������ ���������� .
            }
          else bo_atkSQ1 = 0 ; // ���������� ��� ��������� ��� ���� .

          // ����� ������ �������� , ���� ��� - ������� :
          if ( ATK2_SQ1 == 1 && flgO._.Vedushiy == 1 && av_label == 0 )
            {
              if      ( ATK2_NmbrATK == 1 ) mSet_AvarMsg( _Av_SQ1_ATK1 ) ;
              else if ( ATK2_NmbrATK == 2 ) mSet_AvarMsg( _Av_SQ1_ATK2 ) ;
              else                          mSet_AvarMsg( _Av_SQ1_ATKR ) ;
            }
        #endif
     #endif

     #ifdef bi_SQ2
          if ( bi_SQ2 == 0 ) //  "������� ���������� ��"
            {
              // ��������� Q1 ��� ������ , ������� ����� �������� ������ � �������� ��� ,
              // ���� ���� ��� ��������� �� ������� :
              mSet_AvarMsg( _Av_SQ2 ) ; // ��� ��������� �������� � ����� ������ ������ � ������ ���������� .
              //---
              // ���� � ������� ��� ��� ������������ �� � � ��������� ��� ����� ���� �� ,
              // �/� ������ � ���� �� �� �������� � ������ ��� , �� ��� ������
              // �������� � ������ �� , ���������� �� ���� �� ������� ��� ...
       #ifndef _ShK_own
            }
       #else
              bo_atkSQ2 = 1 ; // ���������� ��� ��������� ��� ���� .
            }
          else bo_atkSQ2 = 0 ; // ���������� ��� ��������� ��� ���� .

          // ����� ������ �������� , ���� ��� - ������� :
          if ( ATK2_SQ2 == 1 && flgO._.Vedushiy == 1 && av_label == 0 )
            {
              if      ( ATK2_NmbrATK == 1 ) mSet_AvarMsg( _Av_SQ2_ATK1 ) ;
              else if ( ATK2_NmbrATK == 2 ) mSet_AvarMsg( _Av_SQ2_ATK2 ) ;
              else                          mSet_AvarMsg( _Av_SQ2_ATKR ) ;
            }
       #endif
     #endif

     #ifdef _POWER
              //  "���������� ��������� ���������"
              //  ( ����� ������� , �������� � ����� , QK1 �������� , ��� ������������ ������ ) :
          if ( bi_SQ1 == 1 && bi_AR1 == 0
#ifdef bo_Insulat
                       && bo_Insulat == 0
#endif
                       && bi_QK1 == 0 && bo_Avar == 0 )    bo_MB1_Razr = 1 ;
          else                                             bo_MB1_Razr = 0 ;
     #endif

               // �������� ( ���� ���� #define bi_XXX � OBJ.H ) :
               // 1 - ���������� ;
               // 2 - ���������� ;
               // 3 - ����������� ��������� ;
               // 4 - ������ ����������� .
          Control_dt_Avar ( 1 ) ;

          if ( bi_Vnesh_Avar == 1 )    mSet_AvarMsg( _Av_Vnesh_Avar ) ;
//   #ifdef  bi_TK1 20.05.2020 09:48
//        if ( bi_TK1 == 0 )           mSet_AvarMsg( _Av_BV1 ) ;
//   #endif
     #ifdef  bi_CentroBegnik
          if ( bi_CentroBegnik == 1 )  mSet_AvarMsg( _Av_CentroBegnik ) ;
     #endif
     #ifdef  bi_Iv_TG
          if ( bi_Iv_TG == 0 )
             #ifndef _Perecl_DS // ��� ������������� �� - ��������� ���������� ;
                                       mSet_AvarMsg( _Av_Iv_TG ) ;
             #else
             {
               mSet_PreduprMsg( _Pr_Perecl_DS ) ; // ��� ������������� �� - ������������ �� ��� .
               _r.Sk_str._.TG = 0 , _r.Sk_str._.PDF = 0 ; // ���������� �� � ��� .
               _r.Sk_str._.EDS = 1 ;                      // ��������� ��� .
             }
             #endif
     #endif
     #ifdef  bi_1P
          if ( bi_1P == 0 )            mSet_AvarMsg2( _Av2_1P ) ;
     #endif
     #ifdef  bi_2P
          if ( bi_2P == 0 )            mSet_AvarMsg2( _Av2_2P ) ;
     #endif
     #ifdef  bi_PUM
          if ( bi_PUM == 0 )           mSet_AvarMsg( _Av_PUM ) ;
     #endif
     #ifdef bi_PT // �������� ��������� ���������� .
          Control_PT () ;
     #endif
     #ifdef bi_AT
             //  "������ - �������� ����������."
         if ( bi_AT == 0 )             mSet_AvarMsg2( _Av2_AT ) ;
     #endif
     #ifdef bi_PT2 // �������� ��������� ���������� ��2 .
          Control_PT2 () ;
     #endif
     #ifdef bi_AT2
             //  "������ - �������� ���������� ��2."
         if ( bi_AT2 == 0 )            mSet_AvarMsg2( _Av2_AT2 ) ;
     #endif

     // �������� ������������� �������� :
     // 1� ������� - ����� ��� ����� �������� ����� �/� ��������� :
     #ifdef bi_BK1
             //  "�������������� - ��������."
         if ( bi_BK1 == 0 )   mSet_PreduprMsg( _Pr_BK1 ) ;
     #endif
     #ifdef bi_BK2
             //  "������ - ��������."
         if ( bi_BK2 == 0 )   mSet_AvarMsg2( _Av2_BK2 ) ;
     #endif

     // 2� ������� - �������������� �� �/� ��������� � ������ ����� :
     #ifdef  bi_prBK1A
        if ( bi_prBK1A == 0 ) mSet_PreduprMsg3( _Pr3_BK1A ) ;
     #endif
     #ifdef  bi_prBK1B
        if ( bi_prBK1B == 0 ) mSet_PreduprMsg3( _Pr3_BK1B ) ;
     #endif
     #ifdef  bi_prBK1C
        if ( bi_prBK1C == 0 ) mSet_PreduprMsg3( _Pr3_BK1C ) ;
     #endif
     #ifdef  bi_prBK2A
        if ( bi_prBK2A == 0 ) mSet_PreduprMsg3( _Pr3_BK2A ) ;
     #endif
     #ifdef  bi_prBK2B
        if ( bi_prBK2B == 0 ) mSet_PreduprMsg3( _Pr3_BK2B ) ;
     #endif
     #ifdef  bi_prBK2C
        if ( bi_prBK2C == 0 ) mSet_PreduprMsg3( _Pr3_BK2C ) ;
     #endif

     // 3� ������� - ������ �� �/� ��������� � ������ ����� :
     #ifdef  bi_avBK1A
        if ( bi_avBK1A == 0 ) mSet_AvarMsg3( _Av3_BK1A ) ;
     #endif
     #ifdef  bi_avBK1B
        if ( bi_avBK1B == 0 ) mSet_AvarMsg3( _Av3_BK1B ) ;
     #endif
     #ifdef  bi_avBK1C
        if ( bi_avBK1C == 0 ) mSet_AvarMsg3( _Av3_BK1C ) ;
     #endif
     #ifdef  bi_avBK2A
        if ( bi_avBK2A == 0 ) mSet_AvarMsg3( _Av3_BK2A ) ;
     #endif
     #ifdef  bi_avBK2B
        if ( bi_avBK2B == 0 ) mSet_AvarMsg3( _Av3_BK2B ) ;
     #endif
     #ifdef  bi_avBK2C
        if ( bi_avBK2C == 0 ) mSet_AvarMsg3( _Av3_BK2C ) ;
     #endif

     // 4� ������� - �������������� � �������� �� �������� �� �/� ��������� � ������ �����
     // ( ���� �� ��������� ) .

     #ifdef bi_t_Trans
             //  "������ - �������� ��������������."
         if ( bi_t_Trans == 0 )        mSet_AvarMsg2( _Av2_t_Trans ) ;
     #endif
     #ifdef bi_tw_Trans
             //  "�������������� - �������� ��������������."
         if ( bi_tw_Trans == 0 )       mSet_PreduprMsg( _Pr_t_Trans ) ;
     #endif
     #ifdef bi_ROP
             //  "������ - ���� ������ ����."
         if ( bi_ROP == 0 )        mSet_AvarMsg2( _Av2_ROP ) ;
     #endif

     #ifdef  bi_Technol_Ostanov
      if ( bi_Technol_Ostanov == 1 )   mSet_ServiceMsg2( _Srv2_Technol_Ostanov ) ;
      else                             mClr_ServiceMsg2( _Srv2_Technol_Ostanov ) ;
     #endif

     // ��� ���������� ������ 12-�������� ����� :
     #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
          if ( Prg._.Gotovn == 1 ) // ���������/�������� ����� ����� ������ � ������ ���������� :
          {
             if ( Name_Agr == 2 ) // ������ ������� ���� , 6-�� �������� ����� :
             {
               S.Disable = 0, S2.Disable = 1; // ��������� �� ����2 .
               mSet_ServiceMsg2( _Srv2_VedomOtkl ), mClr_ServiceMsg2( _Srv2_VeduschOtkl ) ;
             }
             else if ( Name_Agr == 3 ) // ������ ������� ���� , 6-�� �������� ����� :
             {
               S.Disable = 1, S2.Disable = 0; // ��������� �� ����1 .
               mClr_ServiceMsg2( _Srv2_VedomOtkl ), mSet_ServiceMsg2( _Srv2_VeduschOtkl ) ;
             }
             else if ( Name_Agr == 1 ) // �������� ��� �����, 12-�� �������� ����� :
             {
               S.Disable = 0, S2.Disable = 0;
               mClr_ServiceMsg2( _Srv2_VeduschOtkl ) ; // �� ������ ������ .
               mClr_ServiceMsg2( _Srv2_VedomOtkl ) ;   // �� ������ ������ .
             }
             else // if ( Name_Agr == 0 ) // ������ �� ������ :
             {
               S.Disable = 1, S2.Disable = 1;
               mSet_ServiceMsg2( _Srv2_VedomOtkl ), mSet_ServiceMsg2( _Srv2_VeduschOtkl ) ;
             }
          }
          else // � ������ ������ ��������� ������������ ������ :
          {
             //---
             // if ( Name_Agr == 1 ) - �������� ��� �����, 12-�� �������� �����
             // if ( Name_Agr == 2 ) - ������� ������ ������� ����, 6-�� �������� �����
             // if ( Name_Agr == 3 ) - ������� ������ ������� ����, 6-�� �������� �����
             //---
             if      ( Name_Agr == 1 && ( bi_Vedom == 1 || bi_Vedusch == 1 || bi_Both == 0 ) ) mSet_PreduprMsg2( _Pr2_No_PereclMost ) ;
             else if ( Name_Agr == 2 && ( bi_Vedom == 1 || bi_Vedusch == 0 || bi_Both == 1 ) ) mSet_PreduprMsg2( _Pr2_No_PereclMost ) ;
             else if ( Name_Agr == 3 && ( bi_Vedom == 0 || bi_Vedusch == 1 || bi_Both == 1 ) ) mSet_PreduprMsg2( _Pr2_No_PereclMost ) ;
             else      mClr_PreduprMsg2( _Pr2_No_PereclMost ) ; // ������� ������ �������������� .
          }

          // �������� ����������� ������������� ������ :
          if    ( ( bi_Vedusch == 1 && bi_Vedom == 1 ) ||
                  ( bi_Vedusch == 1 && bi_Both  == 1 ) ||
                  ( bi_Vedom   == 1 && bi_Both  == 1 ) ||
                  ( bi_Vedusch == 0 && bi_Vedom == 0 && bi_Both == 0 ) )
          {
               mSet_ServiceMsg3( _Srv3_NeisprPerekl ) ;
          }
          else mClr_ServiceMsg3( _Srv3_NeisprPerekl ) ; // ������� ������ ��������� .
          //----
     #endif

        }
     else   mSet_AvarMsg( _Av_2P24 ) ;

//---
#ifndef _KTE_GD
  #define  _Srv_Oprobovanie  0
#endif
//---     // ������� �����.� �����.������, ���� ����� �����-���� �� ���
          // ����� �����������, �.�. ��� ����������� ���� ���� ���������.
      mClr_ServiceMsg( _Srv_F2_regim | _Srv_Oprobovanie ) ;
      if ( Isp.all != 0 )
      {
         if ( Isp._.Oprobov == 1 ) mSet_ServiceMsg( _Srv_Oprobovanie ) ;
         else                      mSet_ServiceMsg( _Srv_F2_regim ) ;
      }

      //---
      // � ���������� ������� ����������� ����������� �� ����� �������� � ������ .
      // ������� ���� ��������� , � �� ��� Isp._.Predupr , �.�. ��� ��� ��������
      // ��������� �������� , ����� �� �� ����� � ������ ��������� :
      if ( Isp._.SIFUV_Res == 1 || Ckl._.RTV == 1 || Ckl._.SIFUV == 1 ) mSet_PreduprMsg( _Pr_ServiceProg ) ;

#ifdef _KTE_GD
          // ���� ������� ����������� , �� �� ������ ������� ������������� :
      if ( bi_Oprobov == 1 && bi_Blokir == 0 ) mSet_ServiceMsg( _Srv_Blokir ) ;
      else                                     mClr_ServiceMsg( _Srv_Blokir ) ;
#endif

     // ��� ���������� ������ 12-�������� ����� :
     #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
          // ����� ������ ���� ��������� , �������� �������� , � ����������� �� ������� ������� :
          if ( Name_Agr == 3 ) // ������ ������� ���� , 6-�� �������� ����� :
           {
              // �� ��� (����� ������� � Id-Max) �������������� � ������ �������� ����� �� ��������� :
              //----- ��� 12-�� �������� ����� � ����� �� � ������ ����� :
              if ( ( Reg_AvarMsg     & _Av_AK1        ) != (lw)r0 ) mClr_AvarMsg(  _Av_AK1  ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AM1       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AM1 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AT        ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AT   ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_PT        ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_PT) ;
              if ( ( Reg_AvarMsg     & _Av_AF1        ) != (lw)r0 ) mClr_AvarMsg( _Av_AF1) ;
              if ( ( Reg_PreduprMsg  & _Pr_AF1P       ) != (lw)r0 ) mClr_PreduprMsg( _Pr_AF1P) ;
              if ( ( Reg_PreduprMsg  & _Pr_BV1        ) != (lw)r0 ) mClr_PreduprMsg( _Pr_BV1 ) ;
              if ( ( Reg_AvarMsg     & _Av_BV1        ) != (lw)r0 ) mClr_AvarMsg( _Av_BV1 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KP        ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KF_VKask  ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask  ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_SFV1      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV1 ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK1A      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK1A ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK1B      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK1B ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK1C      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK1C ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK1A      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK1A ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK1B      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK1B ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK1C      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK1C ) ;

              //----- ��� 12-�� �������� ����� � ����� �� � ������ ����� :
              //----- ( ������� �� ������� �������� ���������� - ���������� �� � ����� )
            //if ( ( Reg_AvarMsg2    & _Av2_KP2       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP2 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KF_VKask2 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask2 ) ;
            //if ( ( Reg_PreduprMsg2 & _Pr2_SFV2      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV2 ) ;
           }
         //---
          if ( Name_Agr == 2 ) // ������ ������� ���� , 6-�� �������� ����� :
           {
              // �� ��� (����� ������� � Id-Max) �������������� � ������ �������� ����� �� ��������� :
              //----- ��� 12-�� �������� ����� � ����� �� � ������ ����� :
              if ( ( Reg_AvarMsg2    & _Av2_AK2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AK2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AM2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AM2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AT2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AT2   ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_PT2       ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_PT2) ;
              if ( ( Reg_AvarMsg2    & _Av2_AF2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AF2) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_AF2P      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_AF2P ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_BV2       ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_BV2  ) ;
              if ( ( Reg_AvarMsg2    & _Av2_BV2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_BV2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KP2       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KF_VKask2 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask2 ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_SFV2      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV2 ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK2A      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK2A ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK2B      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK2B ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK2C      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK2C ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK2A      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK2A ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK2B      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK2B ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK2C      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK2C ) ;

              //----- ��� 12-�� �������� ����� � ����� �� � ������ ����� :
              //----- ( ������� �� ������� �������� ���������� - ���������� �� � ����� )
            //if ( ( Reg_AvarMsg2    & _Av2_KP3       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP3 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KP4       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP4 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KF_VKask3 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask3 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KF_VKask4 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask4 ) ;
            //if ( ( Reg_PreduprMsg2 & _Pr2_SFV3      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV3 ) ;
            //if ( ( Reg_PreduprMsg2 & _Pr2_SFV4      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV4 ) ;
           }
     #endif

      // ��������� ������������ "�������� ������ ����������" ���������� �������� ��������� .
      if ( flg_RaTe._.tyr_tst_pr == 1 ) mSet_ServiceMsg2( _Srv2_Proboy_Tyr ) ;
      else                              mClr_ServiceMsg2( _Srv2_Proboy_Tyr ) ;

       // ��� ������ ��������� ������������ "�������� ������ ����������" ��������� ������� ������ .
      if ( flg_RaTe._.tyr_tst_av == 1 ) mSet_ServiceMsg2( _Srv2_ZashProboy_Tyr ) ;
      else                              mClr_ServiceMsg2( _Srv2_ZashProboy_Tyr ) ;

#ifdef _INTERPRETER
    if (ObjSrv_bit._.Avar)    mSet_PreduprMsg2( _Pr2_NoObjPrg ) ;
#endif

   return 0 ;
 }

//-----------------------------

void  Sborka_Gotovn ( void )
{
   #ifndef _KTE_GD
    static   word time_QK ;
    register lword lax ;
   #endif
    register word ax ;

      //   ����� ���� ��������� ��������� (� �.�. � �������)
      // ����� ��������� �� �������� � ��������������� (������������ � �����) :
    mClr_AvarMsg ( _Av_All & ~_Mask_AvarSbr  ) ;
    mClr_AvarMsg2( _Av_All & ~_Mask_AvarSbr2 ) ;
#ifdef _TRETIY_REG
    mClr_AvarMsg3( _Av_All ) ;
#endif
#ifdef _INTERPRETER
    mClr_AvarMsg_obj( _Av_All ) ;
#endif

      //   ����� ���� ����������������� ��������� , ����� ������������ � ����� :
    mClr_PreduprMsg  ( _Pr_All & ~_Mask_PreduprSbr  ) ;
    mClr_PreduprMsg2 ( _Pr_All & ~_Mask_PreduprSbr2 ) ;
#ifdef _TRETIY_REG
    mClr_PreduprMsg3( _Pr_All ) ;
#endif
#ifdef _INTERPRETER
    mClr_PreduprMsg_obj( _Pr_All ) ;
#endif

      //   ����� (����������) ��������� ��������� , ������������ � ����� :
    mClr_ServiceMsg ( _Mask_ServiceSbr  ) ;
    mClr_ServiceMsg2( _Mask_ServiceSbr2 ) ;
#ifdef _TRETIY_REG
    mClr_ServiceMsg3( _Srv_All & ~_Mask_ServiceSbr3 ) ;
#endif
#ifdef _INTERPRETER
    mClr_ServiceMsg_obj( _Srv_All ) ;
#endif


              //  "������������� �����"
#ifndef _ATK_SET
    if ( can_ConfigReg ( _CAN_DistSbros ) == 1 )   goto sbr ;
    if ( bi_DS1 == 1 )   Av._.DistSbros = 1 ;
    else  if ( Av._.DistSbros == 1 )
    {
  sbr:Init_posle_DistSbr () ;
    }
#else // ������������ ����� �� ��������� ������ � ������ ������ ��� ��� .
    DistSbros () ;  //  ��������.��������� ����.������.
        //---
    if ( Av._.DistSbros == 1 )   Init_posle_DistSbr () ;
#endif

    Perekl_rezerv( 1, read_rezerv()) ;// ������������ ������� �������� �������.

    MechTorm_upr ( _MT_Upr ) ;

    Common_avar() ;

    can_ConfigReg ( _CAN_Ostanov ) ;// ��� �������� ������� ����� �� CAN.

      // ���� ��� ��������� ���������� ��������� .
    //if ( Sch_Byte |= 0 )   mSet_ServiceMsg( _Srv_OZU_Isporch ) ;

      //  �������� ������� ��������� � ����������������� ��������.
     if ( bi_2P24 != 1 )   //  "�������� 2P24"
        {
    #ifdef _KTE_GD    //  "��������� �������������� �������"
          if ( bi_QK1 == 0 )  mSet_PreduprMsg( _Pr_Q1 ) ;
              // ���� ��� ���������� ���. ����-��  � ����������
          if ( bi_Razresh_Vkl == 0 )  mSet_PreduprMsg( _Pr_RazreshVkl_KTE ) ;
        }
    #else
       if( _r.Cfg2._.VR1 == 1 )
       {
       //#ifndef _1VR_GOTOVN // ���� ������ ���������� ��� ������� VR1 - �� ��������� "����������� ����������" �� ������� .
          //  "������� ������������ ����������"
          if ( bi_VR1 == 1 || Prz._.VR1 == 1 )    mSet_ServiceMsg( _Srv_VR1 ) ;
       //#else
       }
       else
       {
          // ������� - �� �������� ��������� 1VR , � ��������� ������ , ���� ���� bi_VR1 ���� , �� ��������� �� ����� ,
          // ���������� ����� , � ��� � ������ ������� �� ����� , ���� ���� bi_VR1 �� ������� ...
          if ( Prz._.VR1 == 1 )    mSet_ServiceMsg( _Srv_VR1 ) ;
       //#endif
       }
              //   ����. QK ��� ������ �� ������ �� 1VR: ������ 2��� �������
          if ( Prz._.VR1 == 1 )// Prz._.VR1, ������� ��������� bo_Gotov, �����
          {                   // ����� ������� ���������.
            if ( bi_QK1 == 0 )  Prz._.VR1 = 0 ;
            else if ( (u)((b)(Timer1_Ovr-time_VR1)) > _Sec(2.0)) 
            {
              Prz._.VR1 = 0 ;
              mClr_ServiceMsg( _Srv_VR1 ) ;
            }
          }
        }
        // 26.01.07 18:28 - ����������� �������� ��� �� ����������� ��������� :
     // �������� �������� ��������� ( � ��� �� � ������ ) :
     if ( _r.Cfg._.Vrasch_Dvig == 0 ) Control_Skor () ;
    #endif
            // �������� ����������� ������� �� ��������.
          if ( _r.Cfg._.Control_ZSk == 1 )
            {
              ax = Z_Skor ;
              if ( (sw)ax < 0 )  ax = ~ax + 1 ;

              if ( ax > _r.Ostanov_skor )
                {
                  mSet_PreduprMsg( _Pr_Podano_ZSk   ) ;
            }   }
                                                    //0 DAN 20.05.2016 - ��� ��������� ������ �� ������ ��� .
    if ( Isp._.SIFU_Res == 1 && (sw)zad_res.out > (sw)5 )  mSet_PreduprMsg( _Pr_Podano_ZSk ) ;
    if ( Isp._.RT_Res   == 1 && (sw)zad_res.out > (sw)5 )  mSet_PreduprMsg( _Pr_Podano_ZSk ) ;

      // ����� ��������� ��������� ����� �������� ���� �����
    ObjPrg ( _Obj_c_Sborka_Gotovn ) ; // ����� ���� ������ �������.

      //   �������� ������� ��������� � ����������������� ��������  �
      // �� ������ � ����.
          // ������ ��� ������ �� ������� ������������ �������� ��� ������ :
    if ( ((Reg_AvarMsg | Reg_AvarMsgFirst) & (_Mask_Avar) )
                                        != (lw)r0 )  bo_Avar = 1 ;
#ifdef bo_Avar_Yach
          // 13.06.2021 - ����� ������ ��� ���������� ������ ������������ �������������� .
          // ������ ��� ������ �� ������� � ������ ������������ �������� ��� ������
          // ��� ���������� ������ ������������ �������������� :
    if ( ((Reg_AvarMsg | Reg_AvarMsgFirst) & (_Mask_Avar) )
                                        != (lw)r0 )  bo_Avar_Yach = 1 ;
#endif
          // ��������� ������� � �������������� , �.�. ��� ���������� � ������ :
#ifndef _KTE_GD
    if( _r.Cfg2._.VR1 == 1 ) lax = _Mask_AvarPreduprGotovn;
    else                     lax = _Mask_AvarPreduprGotovn | _Av_VR1;
    if ( ( ((Reg_AvarMsgFirst | Reg_AvarMsg) & ~lax )
#else
    if ( ( ((Reg_AvarMsgFirst | Reg_AvarMsg) & ~( _Mask_AvarPreduprGotovn ))
#endif
       | (Reg_PreduprMsg & ~(mask_predupr
          #ifdef _KTE_GD // ��������� �������������� �� ��������� ������.���-� :
              | _Pr_RazreshVkl_KTE
          #endif
                            ))
       | (Reg_AvarMsgFirst2 | Reg_AvarMsg2)|(Reg_PreduprMsg2 & ~(mask_predupr2))
#ifdef _TRETIY_REG
       | (Reg_AvarMsgFirst3 | Reg_AvarMsg3)|(Reg_PreduprMsg3 & ~(mask_predupr3))
#endif
#ifdef _INTERPRETER
       | (Reg_AvarMsgFirst_obj | Reg_AvarMsg_obj)|(Reg_PreduprMsg_obj & ~(mask_predupr_obj))
#endif
                              ) != (lw)r0 )  bo_Predupr = 1 ;
    else                                     bo_Predupr = 0 ;

      //  ����������� �������� ���������� ��� .
  //bo_Gotov = 0 ; 03.02.2011 11:07 ���������� ���� , ����� � CAN-���������� "Po0" �� ������������ ���������� ,
                  // �.�. Po0_c.all ( ������� ������ � VAR_TAB.H ), ���������� � ����� ����� ��������� .
    bo_canGotov = 0 ;     // ����� �� ������������ �� ��� �������� � ��.�. �� CAN
 #ifdef _ATK_SET
    bo_SA_canGotov = 0 ; //DAN 12.04.2025
    bo_atkGotov = 0 ;
    bo_ATK () ; // ������������ ���������� ������� ��� � ����� , ����� ���� ������ ������� .
 #endif
 #ifdef _KTE_GD
    bo_Vkl_LK = 0 ;
      //---
         // ���� ����������� � ��������� � �����������.
    Isp._.Oprobov = 0 ;
    if ( bi_Oprobov == 1 && bi_Blokir == 0 ) Isp.all = 0 , Isp._.Oprobov = 1 ;
 #endif
    //---

    // ��� ������ , ��� �������������� :
    if ( bo_Avar == 0 && bo_Predupr == 0 )
    {
      // 05.03.2018 13:15 DAN - ���������� �������� �� �������� �������� ������ ���������� , ����� � ��������� ,
      //                        ��������� �������������� ��������� ������� �������� 3� ������ ��������� ,
      //                        �� ��������� �� ���������� � ���� ������ ������ ��� ������� �������� ���������� .
      //
      //                        ��� ����� ��� ��������� � OBJ_DEF.H ������ ������ _KONTAKTOR_for_ProboyTir ...
      bo_Gotov = 1 ;
      bo_canGotov = 1 ;  
      bo_SA_canGotov = 1 ; //DAN 12.04.2025
      bo_atkGotov = 1 ;
 
      
      //---
#if defined (Itt_ach) || defined (Itt1_ach) || defined (_Id_on_Itt_for_ProboyTir) //|| defined (Itt2_ach)
    // ��� ������ , ��� �������������� � ���� �� ������ ��������� ������� ( ��� ������������ ��������� ) :
      if ( (_r.Cfg2._.ProboyTir == 1 && flg_RaTe._.tyr_tst_ok == 1 &&
            flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0) || _r.Cfg2._.ProboyTir == 0 )
#endif
      {
             //  "�����������"
    #ifdef _KTE_GD
             //  ��������� � ������ �� �������. ���� ����� �����.�����.
        if ( bi_Oprobov == 1 && Isp.all != 0 ) goto  xx ; // � ����� ����������

        if ( bi_Razresh_Vkl == 1 )  // ���������e ���. ��� - �����.
        {
    #else   // ��� ��������������� ������� ����, ������ ������� �� ���. �� ��
        if ( bo_Vkl_QK1 == 1 ) // ����� 4���. � ���� �� �� ���������, �� ������� ��.
        {
          if ((u)((w)(Timer1_Ovr-time_QK)) > _Sec( 4.0 )) bo_Vkl_QK1 = 0 ;
        }
        else  time_QK = Timer1_Ovr ;
        
        if ( bi_Razresh_Vkl == 0 )  mSet_PreduprMsg( _Pr_RazreshVkl_KTE ) ;
        else  mClr_PreduprMsg( _Pr_RazreshVkl_KTE ) ;

          //----
    //  #ifdef _KTE_5
        // � "F2-�������" � ��� ����."CAN-���.��" - ���������e ���. ��� - �����.
        if ( (can_ConfigReg ( _CAN_QK ) == 0 && (bi_Razresh_Vkl == 1 || bo_Vkl_QK1 == 1))
                                             || // ��� ��� ���."CAN-���.��" ���
              can_ConfigReg ( _CAN_QK ) == 1 )  // ������� �����. �AN-������� .
     // #endif
        {
          bo_Vkl_QK1 = 1 ; // ���� ���� ���. ���� ������ ���.�� ���.��.
          // 15.03.2021 DAN - ������� �������� �������� ������������ ���������� .
          if ( bi_QK1 == 1 && ( (_r.Cfg2._.VR1 == 1 && bi_VR1 == 0) || _r.Cfg2._.VR1 == 0 ) && Prz._.VR1 == 0 ) // "��������� �������������� �������"
    #endif // 14.08.2012 - �������� bi_VR1 �������� ��� ��������� � ������� ���������� ��� ������� 1VR .
          {   //mVkl_Imp( _VR1_imp | _Start_imp ) ;
              goto xx ; // ��������, ����� �� ���������� ������. �� ������ 'xx:'.
          xx: Prg.all = _Sled | _Blok_upr ;
              DWelcome = "\r\nDr>" ,  MWelcome = "\r\nMr>", AWelcome = _RWell_txt;  ;
              //bo_Vkl_Vent = 1;
              upr_label = 0 ;
          }
        }
      }
    }
    else // ���� "����������" ��� ( ���� "��������������" � "������" ) :
    {
        bo_Gotov = 0 ; // 03.02.2011 11:07 ���������� ������ , ����� ���������� � ����� ����� .
 #ifndef _KTE_GD
        bo_Vkl_QK1 = 0 ;
 #endif
    }
      //    �������� ������� ��������� ���������� ��������� ���
      //  ���������� ��� �� "Enter" � ������ "A1".
    //check_msg_time ()  ; //��� ��� ���� � system.c  24.02.09 15:50
    // ���������������� "check_msg_time()" 11.04.2014 11:49 �.�. �� ���� �� ������ ���������� 1 ��� � "System_prg()"
  return ;
}
//------------------------------------------------


void  Rabota ( void )
{
      //   04.10.05 10:46
      //   ����� ����������������� ��������� .
  //  mClr_PreduprMsg  ( _Pr_All & ~( _Pr_P24 | _Pr_P12 | _Pr_N12 | _Pr_DZVA | _Pr_DZVK) ) ;
  //  mClr_PreduprMsg2 ( _Pr_All & ~( _Pr2_ | _Pr2_ )
//-------

#ifdef _ATK_SET // ������������ ����� �� ��������� ������ � ������ ������ ��� ��� .
    DistSbros () ;  //  ��������.��������� ����.������.

          //  "������������� �����" �������������� �� ���� ������.
    if ( Av._.DistSbros == 1 ) // ������������ ����� �� ��������� ������ � ������ ������ ��� ��� .
      {
        Reg_PreduprMsg  = 0 , Reg_ServiceMsg  = 0 , mask_predupr  = 0 ;
        Reg_PreduprMsg2 = 0 , Reg_ServiceMsg2 = 0 , mask_predupr2 = 0 ;
#ifdef _TRETIY_REG
        Reg_PreduprMsg3 = 0 , Reg_ServiceMsg3 = 0 , mask_predupr3 = 0 ;
#endif
#ifdef _INTERPRETER
        Reg_PreduprMsg_obj = 0 , Reg_ServiceMsg_obj = 0 , mask_predupr_obj = 0 ;
#endif
#ifdef  bo_DS_MT       // ��� ��������������� ������ ����� �� .
        bo_DS_MT = 1 ; // ������� , ����� 300 �� �� ��������� � Common_avar() .
#endif
      }
#endif

    MechTorm_upr ( _MT_Upr ) ;

    Common_avar() ;

//-------

    if ( bi_2P24 != 1 )   //  "�������� 2P24"
      {
    //-------   �������� ������������� "���������� ��������������� ��������" .

    //---
    #ifdef _KTE_GD   // ��� �� � ���������� ������� ��������� �������� ���������,
    //---
          if ( bi_QK1 == 0 )
          {
            mSet_PreduprMsg( _Pr_Q1 ) ;
            mSet_AvarMsg( _Av_VR1 ) ;
          }

          // ��������� �� ����� ����������� : ������.���.�� , ��������
          // �������� ��������� � ����������� �������������� ���������� :

          // ���������� ����������� ������ ����� �������� ������� ����������� . � ����� �������� ������ ����������
          // �� ������ �������� ������� �� ����������� � UPRAVL.C :
          if ( Isp._.Oprobov == 1 && (/*bi_Blokir == 1 ||*/ bi_Oprobov == 0)) mSet_AvarMsg( _Av_VR1 ) ;

        //if ( bi_Razresh_Vkl == 0 && bi_Oprobov == 0 )  // ���� ��� ���������� ���. ���
        //20.03.2009 11:32 - DAN . ����� ��������������� �� ����� ����������� , � �� �� ���� :
          if ( bi_Razresh_Vkl == 0 && Isp._.Oprobov == 0 )  // ���� ��� ���������� ���. ���
          {
            mSet_PreduprMsg( _Pr_RazreshVkl_KTE ) ; // ���������� ����������������� ���������
            mSet_AvarMsg( _Av_VR1 ) ;
          }
            //---
          //if ( bi_LK == 0 && bo_Gotov == 1 ) // ���� �� ��� �� ������� ,
          if ( bi_LK == 0 && bo_Avar == 0 ) // ���� �� ��� �� ������� , i net avarii :
          {
            // �������� �������� ��������� � ����������� �������������� ���. :
            if ( Control_Skor() == 0 && Control_UgOstat() == 0 ) bo_Vkl_LK = 1 ; // ���������� ��������� �� .
            else                                                 bo_Vkl_LK = 0 ;
          }
    //---
    #else    // ��� ���.
    //---
        if ( bi_QK1 == 0 )   //  ���� ������ ����-������� �� :
          {
            if ( bo_Avar == 0 && // �� ���� �� ������ , �� �������� ��� �������� ������������ ���������� =>
                 ( ( can_ConfigReg ( _CAN_QK ) == 0 && ( _r.Cfg2._.VR1 == 1 && bi_VR1 == 0 ) ) ||
                     can_ConfigReg ( _CAN_QK ) == 1 ) )
              { //��������� ����� �������� ��� �������� ( 2% ��������� �� ������, ���� _r.Id_Min=0 � ���� ��� ���� ) :
                if ( ( S.Disable == 0 && IDV <= (_r.Id_Min + _Id_nom (0.02)) )
            #ifdef _SIFU2_ // DAN 23.05.2017 14:46 - ��� ������ ������ ��2 :
                  || ( S.Disable == 1 && IDV2 <= (_r.Id_Min + _Id_nom (0.02)) )
            #endif
                                                                                )
                {
                     mSet_AvarMsg( _Av_QK1_SamoOtkl ) ; // ��������������.
                }
                else mSet_ServiceMsg2(_Srv2_NeisprQK1_bk ) ; // ���� ���� ��� .
          }   }

          //  "������� ������������ ����������" - ������� ��� �������:
        if ( ( can_ConfigReg ( _CAN_QK ) == 0 && (( _r.Cfg2._.VR1 == 1 && bi_VR1 == 1 ) || ( _r.Cfg2._.VR1 == 0 && bi_QK1 == 0 ))) ||
               can_ConfigReg ( _CAN_QK ) == 2 )
          {
            mSet_AvarMsg( _Av_VR1 ) ;
            Prz._.VR1 = 1 ;
          }
    //---
    #endif
    //---
      }

      // ����� ��������� ��������� ����� �������� ���� �����
    ObjPrg ( _Obj_c_Rabota ) ; // ����� ���� ������ �������.

//------- �������� ������� ����������������� �������� � ������ �� � ����.

    if ( ( (Reg_PreduprMsg  & ~mask_predupr ) |
           (Reg_PreduprMsg2 & ~mask_predupr2)
#ifdef _TRETIY_REG
         | (Reg_PreduprMsg3 & ~mask_predupr3)
#endif
#ifdef _INTERPRETER
         | (Reg_PreduprMsg_obj & ~mask_predupr_obj)
#endif
                                              ) != (lw)r0 ) bo_Predupr = 1 ;
    else                                                    bo_Predupr = 0 ;

 #ifdef _ATK_SET
    bo_ATK () ; // ������������ ���������� ������� ��� � ����� , ����� ���� ������ ������� .
 #endif

//------- �������� ������� ��������� �������� � ������ �� � ����.

switch( av_label )
{
  default :
  case 0  :

    ObjPrg ( _Obj_c_Avar_Otkl )  ; // ������ ����������� ����� ������������ ������.

#ifndef _ATK_SET
          //  "������������� �����" �������������� �� ���� ������.
    if ( can_ConfigReg ( _CAN_DistSbros ) == 1 )   goto sbr1 ;
    if ( bi_DS1 == 1 )    Av._.DistSbros = 1 ;
    else  if ( Av._.DistSbros == 1 )
      {
  sbr1: Av._.DistSbros = 0 ;
        Reg_PreduprMsg  = 0 , Reg_ServiceMsg  = 0 , mask_predupr  = 0 ;
        Reg_PreduprMsg2 = 0 , Reg_ServiceMsg2 = 0 , mask_predupr2 = 0 ;
#ifdef _TRETIY_REG
        Reg_PreduprMsg3 = 0 , Reg_ServiceMsg3 = 0 , mask_predupr3 = 0 ;
#endif
#ifdef _INTERPRETER
        Reg_PreduprMsg_obj = 0 , Reg_ServiceMsg_obj = 0 , mask_predupr_obj = 0 ;
#endif
#ifdef  bo_DS_MT       // ��� ��������������� ������ ����� �� .
        bo_DS_MT = 1 ; // ������� , ����� 300 �� �� ��������� � Common_avar() .
#endif
      }
#endif
//------- ����������� ������ ������. -------------------

    // 04.11.2011 9:25 - ���������� ���� ������ ��� ���� , ����� ��������� ��������������
    // ������ ������ ��� ����� � ��������� ��������� �� ����� _Obj_c_Avar_Otkl .
    // ���� ������ ������������� ��� ���� ����� , �� ��� �� ���������� � �������
    // ������ ������ � ����������� �� ��������� ���������� �������� , � ����������� .

    //mSetF_AvarMsg  ( Reg_AvarMsg  ) ; // ����� ������������� ������ ������
    //mSetF_AvarMsg2 ( Reg_AvarMsg2 ) ; // ������ �� ������ �������� �� ����.
    // 26.07.2013 10:45 - ����� ������������� ������ ������ �� ���X ��������� ��������� ,
    // �� ��� ������� , ��� ��� ��� �������� �� ���� ����� :
    SetF_AvarMsg () ;

    if ( ( Reg_AvarMsgFirst | Reg_AvarMsgFirst2
#ifdef _TRETIY_REG
                            | Reg_AvarMsgFirst3
#endif
#ifdef _INTERPRETER
                            | Reg_AvarMsgFirst_obj
#endif
                                                  ) != (lw)r0 ) // ���� ���� ������.
      {
        mSdvig_Imp()  ;   // ������� �� ���������� �� � ���������.
        Prg.all = 0 ;//21.02.06 15:50 _Sled ;
        SCHCIKL = 0, YKST = 0 ; // 21.01.2021 ����� ������� ������ �������� � ������.
        // ���� � ������� �������� ������ ��-�� ����� ��� ���������� ,
        // ����������� bo_canGotov = 0 � ���������� �� ������ ���� ...
        bo_canGotov = 0 ; // ��� ���������� ����������� �� ������� �������.
     #ifdef _ATK_SET
        bo_SA_canGotov = 0 ; //DAN 12.04.2025
        bo_atkGotov = 0 ;
     #endif
     #ifdef _KTE_GD
        bo_Gotov = 0 ;  // �������� ����������� ��� �� ����� ����. ��������� ����. ��� ������� ����.
        bo_Vkl_LK = 0 ;
     #else
        bo_Vkl_QK1 = 0 ;
     #endif
      #ifdef bo_Avar_Yach
          // 13.06.2021 - ����� ������ ��� ���������� ������ ������������ �������������� .
          // ������ ��� ������ �� ������� � ������ ������������ �������� ��� ������
          // ��� ���������� ������ ������������ �������������� :
        if ( ((Reg_AvarMsg | Reg_AvarMsgFirst) & (_Mask_Avar) )
                                        != (lw)r0 )  bo_Avar_Yach = 1 ;
      #endif
          // �������� ������������ - "������������ ����.":
          // ���� ����� ����.����. ���� � ������ ������ �� ���������. ������.
      #ifdef _ATK_SET  // ���������� ���� - ���� ����������� ���������� :
        if ( ((Reg_AvarMsgFirst & ~(_Av_VR1 | _Av_NoSynch2) ) | Reg_AvarMsgFirst2
      #else
        if ( ((Reg_AvarMsgFirst & ~_Av_VR1 ) | Reg_AvarMsgFirst2
      #endif
#ifdef _TRETIY_REG
                                             | Reg_AvarMsgFirst3
#endif
#ifdef _INTERPRETER
                                             | Reg_AvarMsgFirst_obj
#endif
                                                                    ) != (lw)r0 )
          {    // ���������� �� ������.
            DWelcome = "\r\nDa>" ,  MWelcome = "\r\nMa>", AWelcome = _AvWell_txt;
            bo_Avar = 1 ;
            //bo_canAvar = 1 ; // 20.09.06 16:34 ��������� � CAN_OBJ.C .
            bo_Gotov = 0 ;
          #ifdef _POWER
            bo_MB1_Razr = 0 ;
          #endif
        #ifndef _ATK_SET
            if ( _r.Cfg._.Kontaktor == 1 )
              {  // ������� ������� ������ ��� ������ _Av_IdMax ( � ����� ) :
                if ((( Reg_AvarMsg | Reg_AvarMsgFirst ) & ~_Otkl_Q2_Mask ) != (lw)r0 ) goto q ;
                if ((( Reg_AvarMsg2 | Reg_AvarMsgFirst2 ) & ~_Otkl_Q2_Mask2 ) != (lw)r0 ) goto q ;
                // ���� ������������ , ��������� ����� ��� ���������� Q2 ��� �������� � ����������� ��������� :
                //#ifdef _TRETIY_REG
                //#endif
                //#ifdef _INTERPRETER
                //#endif
             #ifdef _SIFU2_
               if ( S.Disable == 1 ) // DAN 23.05.2017 14:46 - ��� ������ ������ ��2 :
               {
                if ( IDV2 > _r.Tok_Otkl_Kontaktor ) goto q ;
               }
               else
             #endif
               {
                if ( IDV > _r.Tok_Otkl_Kontaktor ) goto q ;
               }
              }
            else
              {
          q:    mOtkl_Q2 () ;
              }
        #else
                if ((( Reg_AvarMsg | Reg_AvarMsgFirst ) & ~_Otkl_Q2_Mask ) != (lw)r0 )    mOtkl_Q1 ()  ;
                if ((( Reg_AvarMsg2 | Reg_AvarMsgFirst2 ) & ~_Otkl_Q2_Mask2 ) != (lw)r0 ) mOtkl_Q1 ()  ;
        #endif
                // �������� �������� ������� ������� ��� ����������� ��������.
            Time_do_OtklImp  = Timer1_Ovr ;
            av_label = 10 ;
            bo_SledActiv = 1 ;
            break;// ������� ���� ����� ������ �����, ���� ��� �������������
                 // �� ������ ����� ��������� �������� ������� ��������� � �������.
             //---------------
  case 10 :   // - �������� ��������� �����, ����� ������� ���������.
            //21.02.06 15:50 Prg._.Sled = 0 ;
            if ( bo_SledActiv == 0 )
              {
                av_label = 15 ;
              }
  case 15 :   // - ������ ������� �� ���������� ���������.
            if ( (u)((w)(Timer1_Ovr - Time_do_OtklImp)) >= _r.Time_do_OtklImp )
              {
                mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
     #ifdef _KTE_GD
                // DAN 08.11.2016 - � ������������ � ���������� ����������� �������� �������� �
                // ��������� , ��������� ������� �� ������ "Id-Max" ��� ����� ���� , ��� �� ������� ,
                // ��� ���� , ����� ������� ������� ...
                if ( ( (Reg_AvarMsg | Reg_AvarMsgFirst) & _Av_IdMax ) != (lw)r0 ) mOtkl_Q1 () ;
     #endif
                //---
                   //  ���� ������� ��� �������� ��������� � ���������� ����.
                  // (�������� ����� ���� ������ ��������.)
                if ( av_label == 15 )
                {
                  av_label = 18 ;
                  i2c_av_label = 0 ;
                }
              }
        break; //--------------------
  case 18 :
            if ( Save_avar() != 4 )   av_label = 20 ;

        break; //--------------------
  case 20 :
               //  ����������� ���������� �����.
            sl_d.time_out = Timer1_Ovr ;
              //  "������������� �����"
#ifndef _ATK_SET
                // ����� ����� ���� �������� � ������ ������ � Id_Max
            if ( can_ConfigReg ( _CAN_DistSbros ) == 1 )  goto sbr ;
            if ( Klav_Buff == _Reset )        goto sbr ;
            if ( bi_DS1 == 1 )   Av._.DistSbros = 1 ;
            else  if ( Av._.DistSbros == 1 )
              {      // �������� �� ������������� ����� ��� ������ �������?
                if ( ( (Reg_AvarMsg | Reg_AvarMsgFirst)
                                      & _Mask_DistSbr ) != 0 )  break ;
           sbr: Init_posle_DistSbr () ;
          }   }
#else // ������������ ����� �� ��������� ������ � ������ ������ ��� ��� .
            if ( Av._.DistSbros == 1 )
            {
               Init_posle_DistSbr () ;
          } }
#endif
        else  // ���������� �� ������� 1VR - "����������� ����������".
          {
            Time_do_OtklImp  = Timer1_Ovr ;
            av_label = 30 ;
  case 30 :
            if ( (u)((w)(Timer1_Ovr - Time_do_OtklImp)) >= _r.Time_do_OtklImp )
              {
                Init_posle_DistSbr () ;
              }
          }
      }
}
      //    �������� ������� ��������� ���������� ��������� ���
      //  ���������� ��� �� "Enter" � ������ "A1".
    //check_msg_time ()  ; //��� ��� ���� � system.c  24.02.09 15:50
    // ���������������� "check_msg_time()" 11.04.2014 11:49 �.�. �� ���� �� ������ ���������� 1 ��� � "System_prg()"
  return ;
}
//---------------------

void Clr_Q1_Q2 ( void )
{
  static word timeout_Q1, timeout_Q2  ;

  // ������ �� ���������� ��������� ������ _Time_otkl_QX . �� ����� ���������� ���������
  // ���� ������������� ���������� �������� Av._.OneQX . ���� ���� ���� �� ���� ,
  // ����������� ���������� ��������� �� ���������� . ���� ������������� ��������� ��
  // �������� ������� , ��� ������� , ��� ���� ������� �������� ������� .

         /* ������, ����� ��������, ������� �� ���������� "Q1". */
      if ( Av._.OtklQ1 == 1 )
      {
        if ( (u)((w)(timer1 - TimeOtklQ1)) >= _Time_otkl_Q1 )
        {
          mClr_Q1() ;
          timeout_Q1 = Timer1_Ovr ;
        }
      }
      else if ( Av._.OneQ1 == 1 ) // ���� ���� ������������� ���������� Q1 ������ , ���������� Q1 �� ���������� .
        { // ������ ������������� ���������� �������� ����� �������� ������� , ���� ��� ����� �������� .
          if ( (u)((w)(Timer1_Ovr-timeout_Q1)) >= _TimeOut_otkl_Q1)
            {                                         // ������� ������������� , ������ ���� ������� Q1 ������� ,
              if ( bi_xQ1 == 1 || Av._.Ostanov == 1 ) Av._.OneQ1 = 0 ; // ��� � ������ ������� .
            }
        }

         /* ������, ����� ��������, ������� �� ���������� "Q2". */
      if ( Av._.OtklQ2 == 1 )
      {
        if ( (u)((w)(timer1 - TimeOtklQ2)) >= _Time_otkl_Q2 )
        {
          mClr_Q2() ;
          timeout_Q2 = Timer1_Ovr ;
        }
      }
      else if ( Av._.OneQ2 == 1 ) // ���� ���� ������������� ���������� Q2 ������ , ���������� Q2 �� ���������� .
        { // ������ ������������� ���������� �������� ����� �������� ������� , ���� ��� ����� �������� .
          if ( (u)((w)(Timer1_Ovr-timeout_Q2)) >= _TimeOut_otkl_Q2)
            {                                         // ������� ������������� , ������ ���� ������� Q1 ������� ,
              if ( bi_xQ2 == 1 || Av._.Ostanov == 1 ) Av._.OneQ2 = 0 ; // ��� � ������ ������� .
            }
        }

return ;
}
//-------------

void GerconAC_Interrupt (void)
  {
      if ( mTest_Gercon() )
      {
     #ifdef  _Gercon_APV  // ���� ����-��� �� ��������� ���.
        if ( Av2._.APV_Gercon != 0 )
     #endif
        {
          mOtkl_Q1 () ;
      #ifdef _POWER
          bo_MB1_Otkl = 1 ;
      #endif
          // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
          //            �������� ��� �������� , ����� �� ������ ������� ��������� :
          // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
          //            ��� , ��� ����� ������� � ��� :
          //              1. � ������ ����������� ����� ������� �� ��������� ,
          //            �� �������� �� � �����-���� .
          //              2. � ������ ��������� ������� ������� �� � �����-����
          //             �������� ������� ����� �� ������� , ����� �������� ��� .
          //              3. ��� �� �������� ��������� �� ������� .
      #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 � ��� �� ������� �� ��� �������� , ����� �� ���������� ���/���� .
          if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
      #endif
        }
        Av._.Sdvig_imp = 1 ;
        Av._.Gercon = 1 ;
      #ifdef bi_2B1 // ������� � ��1 � � ��2 �������� �� ���� 1� .
        if ( mTest_Gercon2B1() ) Av2._.GerconAC2 = 1 ;
      #endif
      #ifdef bi_3B1 // ������� � ��1 , ��2 � ��3 �������� �� ���� 1� .
             if ( mTest_Gercon3B1() ) Av2._.GerconAC3 = 1 ;
      #endif
      #ifdef bi_4B1 // ������� � ��1 , ��2 , ��3 � ��4 �������� �� ���� 1� .
             if ( mTest_Gercon4B1() ) Av2._.GerconAC4 = 1 ;
      #endif
      }
    return   ;
  }

//-------------

void GerconDC_Interrupt (void)
  {
      if ( mTest_GerconDC() )
      {
      //-------------------
    #ifdef bi_GerconDC
        mOtkl_Q2 () ;
          // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
          //            �������� ��� �������� , ����� �� ������ ������� ��������� :
          // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
          //            ��� , ��� ����� ������� � ��� :
          //              1. � ������ ����������� ����� ������� �� ��������� ,
          //            �� �������� �� � �����-���� .
          //              2. � ������ ��������� ������� ������� �� � �����-����
          //             �������� ������� ����� �� ������� , ����� �������� ��� .
          //              3. ��� �� �������� ��������� �� ������� .
      #ifndef _KTE_GD
          if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
      #endif
        Av._.Sdvig_imp = 1 ;
        Av._.GerconDC = 1 ;
    #else  // 14.10.2008 11:40
     #ifdef bi_RV1
              //  "������������ ���"
        Av._.Sdvig_imp = 1 ;   // ������� �� ���������� �� � ���������.
        Av2._.RV1 = 1 ;
     #endif
    #endif
      //-------------------
    #ifdef bi_GerconAC2
      #ifdef  _Gercon_APV  // ���� ����-��� �� ��������� ���.
        if ( Av2._.APV_Gercon != 0 )
      #endif
        {
          mOtkl_Q1 () ;
          // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
          //            �������� ��� �������� , ����� �� ������ ������� ��������� :
          // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
          //            ��� , ��� ����� ������� � ��� :
          //              1. � ������ ����������� ����� ������� �� ��������� ,
          //            �� �������� �� � �����-���� .
          //              2. � ������ ��������� ������� ������� �� � �����-����
          //             �������� ������� ����� �� ������� , ����� �������� ��� .
          //              3. ��� �� �������� ��������� �� ������� .
      #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 � ��� �� ������� �� ��� �������� , ����� �� ���������� ���/���� .
          if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
      #endif
        }
        Av._.Sdvig_imp = 1 ;
        Av2._.GerconAC2 = 1 ;
    #endif
      //-------------------
      }
    return   ;
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
          /* �������� ������� ��������.  */
void Control_Gercon ( void )
{
        /* �������� ������� ������� ����������� ����.  */
  #ifdef bi_GerconDC
    if ( bi_GerconDC == 1 )  Av._.GerconDC = 1 ;
    if ( Av._.GerconDC == 1 )
     {
        mSet_AvarMsg ( _Av_GerconDC ) ;
        mOtkl_Q2 () ;
     }
  #else // 14.10.2008 11:40
     #ifdef bi_RV1
              //  "������������ ���"
       if ( bi_RV1 == 1 ) Av2._.RV1 = 1 ;
       if ( Av2._.RV1 == 1 )
        {
          Av._.Sdvig_imp = 1 ;   // ������� �� ���������� �� � ���������.
          mSet_AvarMsg2( _Av2_RV1 ) ;
        }
     #endif
  #endif
     //-------
    if ( bi_Gercon == 1 )  Av._.Gercon = 1 ;
  #ifdef bi_GerconAC2
    if ( bi_GerconAC2 == 1 ) Av2._.GerconAC2 = 1 ;
  #endif
     //-------

//---***************************************
#ifndef  _Gercon_APV
//---***************************************
    if ( Av._.Gercon == 1 ) // <- ������� ������������ �  ���������� �� �������.
      {
        mSet_AvarMsg ( _Av_Gercon ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
        //            �������� ��� �������� , ����� �� ������ ������� ��������� :
        // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
        //            ��� , ��� ����� ������� � ��� :
        //              1. � ������ ����������� ����� ������� �� ��������� ,
        //            �� �������� �� � �����-���� .
        //              2. � ������ ��������� ������� ������� �� � �����-����
        //             �������� ������� ����� �� ������� , ����� �������� ��� .
        //              3. ��� �� �������� ��������� �� ������� .
    #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 � ��� �� ������� �� ��� �������� , ����� �� ���������� ���/���� .
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
      }
      //----
    if ( Av2._.GerconAC2 == 1 )
     {
      #ifdef bi_2B1 // ������� � ��1 � � ��2 �������� �� ���� 1� .
        if ( Av._.Gercon == 1 ) // ���� ��������� ������� � � ��1 � � ��2 ,
         {                      // ������� , ��� �������� ������ � ��2 ,
           if ( (Reg_AvarMsgFirst & _Av_Gercon) != (lw)r0 ) // ���� ��1 ��� � ������ ����� ,
            {                            // ������� � ������ ������ ��2 .
              mSet_AvarMsg ( _Av_GerconDC ) ;
            }
           mClr_AvarMsg ( _Av_Gercon ) ; // ������� ��������� � ������� � ��1 .
         }
      #endif
        mSet_AvarMsg ( _Av_GerconDC ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
        //            �������� ��� �������� , ����� �� ������ ������� ��������� :
        // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
        //            ��� , ��� ����� ������� � ��� :
        //              1. � ������ ����������� ����� ������� �� ��������� ,
        //            �� �������� �� � �����-���� .
        //              2. � ������ ��������� ������� ������� �� � �����-����
        //             �������� ������� ����� �� ������� , ����� �������� ��� .
        //              3. ��� �� �������� ��������� �� ������� .
    #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 � ��� �� ������� �� ��� �������� , ����� �� ���������� ���/���� .
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
     }
      //----
  #ifdef bi_3B1 // ������� � ��1 , ��2 � ��3 �������� �� ���� 1� .
    if ( Av2._.GerconAC3 == 1 )
     {
        if ( Av._.Gercon == 1 ) // ���� ��������� ������� � � ��1 � � ��3 ,
         {                      // ������� , ��� �������� ������ � ��3 ,
           if ( (Reg_AvarMsgFirst & _Av_Gercon) != (lw)r0 ) // ���� ��1 ��� � ������ ����� ,
            {                            // ������� � ������ ������ ��3 .
              mSet_AvarMsg ( _Av_Gercon3 ) ;
            }
           mClr_AvarMsg ( _Av_Gercon ) ; // ������� ��������� � ������� � ��1 .
         }
        mSet_AvarMsg ( _Av_Gercon3 ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
        //            �������� ��� �������� , ����� �� ������ ������� ��������� :
        // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
        //            ��� , ��� ����� ������� � ��� :
        //              1. � ������ ����������� ����� ������� �� ��������� ,
        //            �� �������� �� � �����-���� .
        //              2. � ������ ��������� ������� ������� �� � �����-����
        //             �������� ������� ����� �� ������� , ����� �������� ��� .
        //              3. ��� �� �������� ��������� �� ������� .
    #ifndef _KTE_GD
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
     }
  #endif
  #ifdef bi_4B1 // ������� � ��1 , ��2 , ��3 � ��4 �������� �� ���� 1� .
    if ( Av2._.GerconAC4 == 1 )
     {
        if ( Av._.Gercon == 1 ) // ���� ��������� ������� � � ��1 � � ��4 ,
         {                      // ������� , ��� �������� ������ � ��4 ,
           if ( (Reg_AvarMsgFirst & _Av_Gercon) != (lw)r0 ) // ���� ��1 ��� � ������ ����� ,
            {                            // ������� � ������ ������ ��4 .
              mSet_AvarMsg ( _Av_Gercon4 ) ;
            }
           mClr_AvarMsg ( _Av_Gercon ) ; // ������� ��������� � ������� � ��1 .
         }
        mSet_AvarMsg ( _Av_Gercon4 ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
        //            �������� ��� �������� , ����� �� ������ ������� ��������� :
        // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
        //            ��� , ��� ����� ������� � ��� :
        //              1. � ������ ����������� ����� ������� �� ��������� ,
        //            �� �������� �� � �����-���� .
        //              2. � ������ ��������� ������� ������� �� � �����-����
        //             �������� ������� ����� �� ������� , ����� �������� ��� .
        //              3. ��� �� �������� ��������� �� ������� .
    #ifndef _KTE_GD
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
     }
  #endif
//---***************************************
#else
//---***************************************
    if ( Av._.Gercon == 1 || Av2._.GerconAC2 == 1 )
    {
      Av._.Sdvig_imp = 1 ;
          //  ������ �������� �������� ����� ���������� ����� 10 � 30 ����.
      if ( Av2._.APV_Gercon != 0 )  goto Avar  ;
      else      // ������ �������� ������� �� 30 ����.
      {
         if ( RT_trigg == 0 )// ����������, ��� �� ������� ���
         {                  // ������������ ������� ��.
           if ( Prg._.RegTok == 1 ) RT_trigg  = 0x81 ;
           else                     RT_trigg  = 0x80 ;
         }
         Prg._.RegTok = 0 ; // ���������� ���. ����.
         if ( (u)((w)(timer1 - gercon_time)) > _MkSec( 10u * 1000u ) )   // ���� ������ 10 ms .
         {
           if (   mTest_Gercon()
                #ifdef bi_GerconAC2
                       || mTest_GerconDC()
                #endif
              )
           {       // ������ ����������� ���� ��1
         Avar: if ( Av._.Gercon   == 1 )  mSet_AvarMsg ( _Av_Gercon ) ;
                   // ������ ����������� ���� ��2
               if ( Av2._.GerconAC2 == 1 )mSet_AvarMsg ( _Av_GerconDC ) ;
               mOtkl_Q1 () ;
               // 05.12.07 - �� ���������� �� ������������ , �� �������� ����� �������
               //            �������� ��� �������� , ����� �� ������ ������� ��������� :
               // 28.09.15 - �������� � ������� ������ , ����� ������� ����� �� X����������
               //            ��� , ��� ����� ������� � ��� :
               //              1. � ������ ����������� ����� ������� �� ��������� ,
               //            �� �������� �� � �����-���� .
               //              2. � ������ ��������� ������� ������� �� � �����-����
               //             �������� ������� ����� �� ������� , ����� �������� ��� .
               //              3. ��� �� �������� ��������� �� ������� .
           #ifndef _KTE_GD
               if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* ���������� ��������� ����� */
           #endif
          #ifdef _POWER
              bo_MB1_Otkl = 1 ;
          #endif
           }
           else  // ���� ������ ����������� ����� 10 ms
           {
              if ( bo_Avar == 0  ) // �������, ����� �� ����� ����� ��.
              {
                Av._.Sdvig_imp = 0 ;
                if ( RT_trigg == 0x81 )  Prg._.RegTok = 1 ;
              }
              RT_trigg = 0  ;
              Av._.Gercon = 0 ;
              Av2._.GerconAC2 = 0 ;
              Av2._.APV_Gercon = 1 ; // ������� ���������� ����. ��� �����. ��� �������. ������.
           }
         }
      }
    }
    else
    {
      RT_trigg = 0  ;
      if ( Av2._.APV_Gercon != 0 )
      {     //  ���� � ������� 30 ms ����� ������� ��� ������ �������� ��
            // ��������  -  tst_ ������������.
        if ( (u)((w)(timer1 - gercon_time)) > _MkSec( 30u * 1000u ) )  Av2._.APV_Gercon = 0 ;
      }
      else gercon_time = timer1 ;
    }
//---***************************************
#endif
//---***************************************
  return ;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// ��������� ����� �� ����� :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )

 void IdIzm_3faz (void)
 {
   // 100��� - ��� 6 ��������� ������ ����� ��������������������� �������� .
   // ������� �������� �� 4 ������� ���� ������ ����� :
   //---
   // ����������� ��� , �� ������� ������ ������ ���� ��� .
     // � ������ ����������� ��������� ��������� :          // � ������� ������ :
     // Tir1 - ������ ���� I� ( Ia - ������������� )        // Tir1 - ������ ���� Ia � Ib
     // Tir2 - ������ ���� Ib ( Ic - ������������� )        // Tir2 - ������ ���� Ia � I�
     // Tir3 - ������ ���� Ia ( Ib - ������������� )        // Tir3 - ������ ���� Ib � Ic
     // Tir4 - ������ ���� Ic ( Ia - ������������� )        // Tir4 - ������ ���� Ib � Ia
     // Tir5 - ������ ���� Ib ( Ic - ������������� )        // Tir5 - ������ ���� Ic � Ia
     // Tir6 - ������ ���� Ia ( Ib - ������������� )        // Tir6 - ������ ���� Ic � Ib
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 2 && S.N != 5 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S.N != 3 && S.N != 6 ) )
    {
      IA1_full = _AD_BUSY; // ��1
      mAD_Izm (  IA1_ach    , &IA1_full ) ; // ���������  "IA1_Full"
      //---
 #ifdef IA2_ach
      IA2_full = _AD_BUSY; // ��2
      mAD_Izm (  IA2_ach    , &IA2_full ) ; // ���������  "IA2_Full"
 #endif
    }
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 1 && S.N != 4 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S.N != 2 && S.N != 5 ) )
    {
      IB1_full = _AD_BUSY; // ��1
      mAD_Izm (  IB1_ach    , &IB1_full ) ; // ���������  "IB1_Full"
      //---
 #ifdef IB2_ach
      IB2_full = _AD_BUSY; // ��2
      mAD_Izm (  IB2_ach    , &IB2_full ) ; // ���������  "IB2_Full"
 #endif
    }
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 3 && S.N != 6 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S.N != 1 && S.N != 4 ) )
    {
      IC1_full = _AD_BUSY; // ��1
      mAD_Izm (  IC1_ach    , &IC1_full ) ; // ���������  "IC1_Full"
      //---
 #ifdef IC2_ach
      IC2_full = _AD_BUSY; // ��2
      mAD_Izm (  IC2_ach    , &IC2_full ) ; // ���������  "IC2_Full"
 #endif
    }

  return ;
 }

//   ��������� �������������� ���������� ����� �� ����� :
 void IdConv_3faz (void)
 {
    register word ix ;
    //---
   // ����������� ��� , �� ������� ������ ������ ���� ��� .
     // � ������ ����������� ��������� ��������� :          // � ������� ������ :
     // Tir1 - ������ ���� I� ( Ia - ������������� )        // Tir1 - ������ ���� Ia � Ib
     // Tir2 - ������ ���� Ib ( Ic - ������������� )        // Tir2 - ������ ���� Ia � I�
     // Tir3 - ������ ���� Ia ( Ib - ������������� )        // Tir3 - ������ ���� Ib � Ic
     // Tir4 - ������ ���� Ic ( Ia - ������������� )        // Tir4 - ������ ���� Ib � Ia
     // Tir5 - ������ ���� Ib ( Ic - ������������� )        // Tir5 - ������ ���� Ic � Ia
     // Tir6 - ������ ���� Ia ( Ib - ������������� )        // Tir6 - ������ ���� Ic � Ib
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 2 && S.N != 5 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S.N != 3 && S.N != 6 ) )
  {
    while ( IA1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IA1_full , ix ,  IA1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IA1 = ix ;
      //---
 #ifdef IA2_ach
    while ( IA2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IA2_full , ix ,  IA2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IA2 = ix ;
 #endif
  }
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 1 && S.N != 4 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S.N != 2 && S.N != 5 ) )
  {
    while ( IB1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IB1_full , ix ,  IB1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IB1 = ix ;
      //---
 #ifdef IB2_ach
    while ( IB2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IB2_full , ix ,  IB2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IB2 = ix ;
 #endif
  }
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 3 && S.N != 6 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S.N != 1 && S.N != 4 ) )
  {
    while ( IC1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IC1_full , ix ,  IC1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IC1 = ix ;
      //---
 #ifdef IC2_ach
    while ( IC2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IC2_full , ix ,  IC2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IC2 = ix ;
 #endif
  }

  return ;
 }

#endif

//---------------------------------------------------------------------------------------------------------------

      // ������������� ����� �� ����� ���� ������ �� :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )

 void TokRaspr_3faz (void)
 {
    word ax ;
    //---
    // ����������� ��� , �� ������� ������ ������ ���� ��� :
    // Tir1 - ������ ���� Ia � Ib
    // Tir2 - ������ ���� Ia � I�
    // Tir3 - ������ ���� Ib � Ic
    // Tir4 - ������ ���� Ib � Ia
    // Tir5 - ������ ���� Ic � Ia
    // Tir6 - ������ ���� Ic � Ib

    if ( Prg._.Gotovn == 0 ) // �������� ������ � ������ :
    {
      if ( S.N == 1 ) // Tir1 - ������ ���� Ia � Ib .
      {
         //--- ���� A ������ ��1 � ��2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
         //---
         //--- ���� B ������ ��1 � ��2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
      }
      else if ( S.N == 2 ) // Tir2 - ������ ���� Ia � I� .
      {
         //--- ���� A ������ ��1 � ��2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
         //---
         //--- ���� C ������ ��1 � ��2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
      }
      else if ( S.N == 3 ) // Tir3 - ������ ���� Ib � Ic .
      {
         //--- ���� B ������ ��1 � ��2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
         //---
         //--- ���� C ������ ��1 � ��2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
      }
      else if ( S.N == 4 ) // Tir4 - ������ ���� Ib � Ia .
      {
         //--- ���� B ������ ��1 � ��2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
         //---
         //--- ���� A ������ ��1 � ��2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
      }
      else if ( S.N == 5 ) // Tir5 - ������ ���� Ic � Ia .
      {
         //--- ���� C ������ ��1 � ��2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
         //---
         //--- ���� A ������ ��1 � ��2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
      }
      else // Tir6 - ������ ���� Ic � Ib .
      {
         //--- ���� C ������ ��1 � ��2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
         //---
         //--- ���� B ������ ��1 � ��2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // ���� � ���������� ����� ������ ���������� :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
      }
    }

  return ;
 }

#endif
