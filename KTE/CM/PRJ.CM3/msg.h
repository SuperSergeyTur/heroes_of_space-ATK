
/* ������������ ����: �������� ����� ����� ������� ������ ���������  */
/*                   � ����������������� ���������.  */
/*----------------------------------------------------------------------------*/

#ifndef msg_head
#define msg_head

// ��� ��������� ������������ ������������ ���:
//#undef  _Device_Name_
//#define _Device_Name_ "    -���5-�-    "

// ������������ ��������� �������� :
#define   _PROGRAM_     "   ������ ...   "

// ����������� ����� ����� ��������:
#define   _DECIMAL_     "A.XXXXXX.XXX-XX "

//----------------------------------------
#ifdef _MAIN_INCLUDE
//----------------------------------------

//----- ������������ ��������� ��� �������� ������� ------

const char *const Tabl_name_ust[_kol_obl]  =
 {
  "1.��������� "
//"2.�������   "
 };

//-------------- �8 - ������� ������� --------------------

_x_far const struct Bits    bts[] =
  {
      _KTE_A8_Cfg1 ,
      _KTE_A8_Cfg2 ,
#ifdef _RVId
      _KTE_A8_CfgRVId ,
#endif
#ifdef  _KTE_A8_ConfigObj
    { "K�����.����." , (w*)&_or.CfgO.all,  16 ,
                               { "������0     ",
                                 "������1     ",
                                 "������2     ",
                                 "������3     ",
                                 "������4     ",
                                 "������5     ",
                                 "������6     ",
                                 "������7     ",

                                 "������8     ",
                                 "������9     ",
                                 "������10    ",
                                 "������11    ",
                                 "������12    ",
                                 "������13    ",
                                 "������14    ",
                                 "������15    " },
      { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010 , 0x0020 , 0x0040 , 0x0080 ,
        0x0100, 0x0200, 0x0400, 0x0800, 0x1000 , 0x2000 , 0x4000 , 0x8000 },
       (w*)&_Msk ,2
    },
#endif
      _KTE_A8_Prg  ,
      _KTE_A8_Isp  ,
      _KTE_A8_Sk   ,
#ifdef _Po0_INVERT      // ������� ����������� �������� �������� �������� .
    { "Po0-������. " , &_r.Po0_Normal,  6 ,
                               { "K1-������   ",
                                 "K3-�������. ",
                                 "K2-������.  ",
                                 "������3     ",
                                 "������4     ",
                                 "������5     " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 /*, 0x40 , 0x80*/ },
       (w*)&_Msk ,1
    },
#endif
#ifdef _AsPo_INVERT     // ������� ����������� �������� �������� �������� .
    { "AsPo0-���.  " , &_or.PoS_Normal[0],  8 ,
                               { "������0     ",
                                 "������1     ",
                                 "������2     ",
                                 "������3     ",
                                 "������4     ",
                                 "������5     ",
                                 "������6     ",
                                 "������7     " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
    { "Pi0-������. " , &_r.Pi0_Normal,  8 ,
                               { "2P24        ",
                                 "1QK         ",
                                 "1AK         ",
                                 "��������-1AR",
                                 "������4     ",
                                 "���-1AF     ",
                                 "1GL         ",
                                 "����.�����  " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#ifdef  _Pi1_
      _KTE_A8_Pi1 ,
#endif
#ifdef  _AsPi0_
    { "AsPi0-���.  " , &_or.PiS_Normal[0],  8 ,
                               { "1VR         ",
                                 "����.������ ",
                                 "������.���. ",
                                 "����.����.  ",
                                 "������4     ",
                                 "������5     ",
                                 "����.��     ",
                                 "������7     "
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi1_
    { "AsPi1-���.  " , &_or.PiS_Normal[1],  8 ,
                               { "���-������  ",
                                 "���-������  ",
                                 "������/����.",
                                 "������3     ",
                                 "����.������ ",
                                 "����.�����  ",
                                 "����� �����.",
                                 "�����.����  "
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi2_
    { "AsPi2-���.  " , &_or.PiS_Normal[2],  1 ,
                               {
                                 "������      ",
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi3_
    { "AsPi3-���.  " , &_or.PiS_Normal[3],  1 ,
                               {
                                 "������      ",
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
      _KTE_A8_cCfgR ,
      _KTE_A8_cStsR ,
      _KTE_A8_CAN0cfg ,
      _KTE_A8_CAN1cfg ,
      _KTE_A8_MBcfg
  };      /* ���������� ������� � ������� */
const word _MaxNumBUst  = sizeof(bts)/sizeof(const struct Bits) ;

//-------- �4 - ������� ���������� ������� ---------------
const struct Stx Nstx [ ] =  {
                                   { _ACh0_txt     , &_ar.n00_ach  },
                                   { _ACh1_txt     , &_ar.n01_ach  },
                                   { _ACh2_txt     , &_ar.n02_ach  },
                                   { _ACh3_txt     , &_ar.n03_ach  },
                                   { _ACh4_txt     , &_ar.n04_ach  },
                                   { _ACh5_txt     , &_ar.n05_ach  },
                                   { _ACh6_txt     , &_ar.n06_ach  },
                                   { _ACh7_txt     , &_ar.n07_ach  },
                                   { _ACh8_txt     , &_ar.n08_ach  },
                                   { _ACh9_txt     , &_ar.n09_ach  },
                                   { _ACh10_txt    , &_ar.n10_ach  },
                                   { _ACh11_txt    , &_ar.n11_ach  },
                                   { _ACh12_txt    , &_ar.n12_ach  },
                                   { _ACh13_txt    , &_ar.n13_ach  },
                                   { _ACh14_txt    , &_ar.n14_ach  },
                                   { _ACh15_txt    , &_ar.n15_ach  },
                                   { _ACh16_txt    , &_ar.n16_ach  },
                                   { _ACh17_txt    , &_ar.n17_ach  },
                                   { _ACh18_txt    , &_ar.n18_ach  },
                                 } ;
const word        _Nm =  sizeof(Nstx)/sizeof(const struct Stx)  ;

//----------------------------------------
#endif    // _MAIN_INCLUDE
//----------------------------------------

#define  _Av_All               ( 0xFFFFFFFFul )

#define  _Av_IdMax             ( 0x00000001ul )
#define  _Av_Gercon            ( 0x00000002ul )
#define  _Av_GerconDC          ( 0x00000004ul )
#define  _Av_CentroBegnik      ( 0x00000008ul )

#define  _Av_Stoyanka          ( 0x00000010ul )
#define  _Av_GL1               ( 0x00000020ul )
#define  _Av_Emax              ( 0x00000040ul )
#define  _Av_Nmax              ( 0x00000080ul )

#define  _Av_AK1               ( 0x00000100ul )
#define  _Av_BV1               ( 0x00000200ul )
#define  _Av_AF1               ( 0x00000400ul )
#define  _Av_VR1               ( 0x00000800ul )

#define  _Av_Teplo             ( 0x00001000ul )
#define  _Av_NoSynch           ( 0x00002000ul )
#define  _Av_Tmax              ( 0x00004000ul )
#define  _Av_Tmin              ( 0x00008000ul )

#define  _Av_QK1_SamoOtkl      ( 0x00010000ul )
#define  _Av_Iv_Min            ( 0x00020000ul )
#define  _Av_Iv_Max            ( 0x00040000ul )
#define  _Av_2P24              ( 0x00080000ul )

#define  _Av_CAN_avar          ( 0x00100000ul )
#define  _Av_Vnesh_Avar        ( 0x00200000ul )
#define  _Av_dN_Max            ( 0x00400000ul )
#define  _Av_Iv_TG             ( 0x00800000ul )

#define  _Av_PR1               ( 0x01000000ul )
#define  _Av_PR2               ( 0x02000000ul )
#define  _Av_PUM               ( 0x04000000ul )
#define  _Av_NoSynch2          ( 0x08000000ul )

#define  _Av_DC_Circuit        ( 0x10000000ul )
#define  _Av_Smazka_Podsh      ( 0x20000000ul )
#define  _Av_MasloSmazka       ( 0x40000000ul )
#define  _Av_Vent_Dvig         ( 0x80000000ul )

    //    ����� ��������������:
    //  �������� ������������� �������� "Reg_PreduprMsg" �
    //  ������� "Tabl_PreduprMsg[32]".
#define  _Pr_All               ( 0xFFFFFFFFul )

//#define  _Pr_                ( 0x00000001ul )
#define  _Pr_Podano_ZSk        ( 0x00000002ul )
#define  _Pr_Skor_NoNull       ( 0x00000004ul )
#define  _Pr_Stoyanka          ( 0x00000008ul )

#define  _Pr_Insulat           ( 0x00000010ul )
//#define  _Pr_                ( 0x00000020ul ) // _Pr_AR1
#define  _Pr_BV1               ( 0x00000040ul )
#define  _Pr_Teplo             ( 0x00000080ul )

#define  _Pr_DZVA              ( 0x00000100ul )
#define  _Pr_DZVK              ( 0x00000200ul )
//#define  _Pr_                ( 0x00000400ul )
//#define  _Pr_                ( 0x00000800ul )

#define  _Pr_P24               ( 0x00001000ul )
#define  _Pr_P12               ( 0x00002000ul )
#define  _Pr_N12               ( 0x00004000ul )
#define  _Pr_BK1               ( 0x00008000ul )

#define  _Pr_Perecl_DS         ( 0x00010000ul )
#define  _Pr_WDT               ( 0x00020000ul )
//#define  _Pr_                ( 0x00040000ul )
//#define  _Pr_                ( 0x00080000ul )

//#define  _Pr_                ( 0x00100000ul )  // _Pr_OffsetAch
#define  _Pr_ServiceProg       ( 0x00200000ul )
#define  _Pr_Rezerv_Zam        ( 0x00400000ul )
#define  _Pr_CAN_predupr       ( 0x00800000ul )

#define  _Pr_AF1P              ( 0x01000000ul )
#define  _Pr_PR1               ( 0x02000000ul )
#define  _Pr_Nzad_obryv        ( 0x04000000ul )
#define  _Pr_RazreshVkl_KTE    ( 0x08000000ul )

#define  _Pr_TipUst            ( 0x10000000ul )
#define  _Pr_Smazka_Podsh      ( 0x20000000ul )
#define  _Pr_MasloSmazka       ( 0x40000000ul )
#define  _Pr_Vent_Dvig         ( 0x80000000ul )

    //    ����� ��������� ���������:
    //  �������� ������������� �������� "Reg_ServiceMsg" �
    //  ������� "Tabl_ServiceMsg[32]".
#define  _Srv_All              ( 0xFFFFFFFFul )

#define  _Srv_No_EDS_Nom       ( 0x00000001ul )
#define  _Srv_MT               ( 0x00000002ul )
#define  _Srv_F2_regim         ( 0x00000004ul )
#define  _Srv_PultTolchki      ( 0x00000008ul )

#define  _Srv_AN_Av            ( 0x00000010ul )
#define  _Srv_AN_Ra_Te         ( 0x00000020ul )
#define  _Srv_AN_Tm            ( 0x00000040ul )
#define  _Srv_AN_Err           ( 0x00000080ul )

#define  _Srv_AN_Kreg          ( 0x00000100ul )
#define  _Srv_AN_Iv_min        ( 0x00000200ul )
#define  _Srv_ErrWrClock_i2c   ( 0x00000400ul )
#define  _Srv_ErrRdClock_i2c   ( 0x00000800ul )

#define  _Srv_Not_Nul_Id       ( 0x00001000ul )
#define  _Srv_Not_Iv           ( 0x00002000ul )
//#define  _Srv_               ( 0x00004000ul ) // _Srv_Offset_Id2_mg
//#define  _Srv_               ( 0x00008000ul ) // _Srv_Offset_Id2_sr

//#define  _Srv_               ( 0x00010000ul ) // _Srv_Offset_Id_mg
//#define  _Srv_               ( 0x00020000ul ) // _Srv_Offset_Id_sr
//#define  _Srv_               ( 0x00040000ul ) // _Srv_Offset_Ud
//#define  _Srv_               ( 0x00080000ul ) // _Srv_ErrorOZU

#define  _Srv_NoCAN_Start      ( 0x00100000ul )
#define  _Srv_AvarRevers       ( 0x00200000ul )
//#define  _Srv_               ( 0x00400000ul ) // _Srv_NoRead_time
//#define  _Srv_               ( 0x00800000ul ) // _Srv_NoWrite_time

#define  _Srv_NoRead_i2c       ( 0x01000000ul )
#define  _Srv_NoWrite_i2c      ( 0x02000000ul )
#define  _Srv_NoCheckSum_i2c   ( 0x04000000ul )
#define  _Srv_NoCAN_Connect    ( 0x08000000ul )

#define  _Srv_QKDT             ( 0x10000000ul )
#define  _Srv_ResCan           ( 0x20000000ul )
#define  _Srv_UstCnst          ( 0x40000000ul )
#define  _Srv_NoCAN_QK         ( 0x80000000ul )

/*------------------------------------------------*/

    //    ����� ������2:
    //  �������� ������������� �������� "Reg_AvarMsg2" �
    //  ������� "Tabl_AvarMsg2[32]".

//#define  _Av2_               ( 0x00000001ul ) // _Av2_Id2_Max// ��� 12-�� ��������� ���� .
//#define  _Av2_               ( 0x00000002ul )  // _Av2_1P
//#define  _Av2_               ( 0x00000004ul )  // _Av2_2P
#define  _Av2_AK2              ( 0x00000008ul )

#define  _Av2_SQ1              ( 0x00000010ul )
#define  _Av2_AM1              ( 0x00000020ul )
#define  _Av2_RV1              ( 0x00000040ul )
#define  _Av2_QKDT             ( 0x00000080ul )

#define  _Av2_Tmax2            ( 0x00000100ul )
#define  _Av2_Tmin2            ( 0x00000200ul )
//#define  _Av2_               ( 0x00000400ul ) // _Av2_AM2
#define  _Av2_SF3              ( 0x00000800ul )

#define  _Av2_BK2              ( 0x00001000ul )
#define  _Av2_MB1              ( 0x00002000ul )
#define  _Av2_AT               ( 0x00004000ul )
//#define  _Av2_               ( 0x00008000ul ) // _Av2_AF2

#define  _Av2_Id1Max           ( 0x00010000ul )  // ��� ��Id 2� ������ ����� ����������� .
#define  _Av2_Id2Max           ( 0x00020000ul )
#define  _Av2_Iv2_Min          ( 0x00040000ul )
#define  _Av2_GL2              ( 0x00080000ul )

#define  _Av2_t_Trans          ( 0x00100000ul )
#define  _Av2_KP               ( 0x00200000ul )
#define  _Av2_KP2              ( 0x00400000ul )
#define  _Av2_MT_Err           ( 0x00800000ul )

//#define  _Av2_               ( 0x01000000ul )
#define  _Av2_KFV_VKask        ( 0x02000000ul )
//#define  _Av2_               ( 0x04000000ul )
//#define  _Av2_               ( 0x08000000ul )

//#define  _Av2_               ( 0x10000000ul )
//#define  _Av2_               ( 0x20000000ul )
#define  _Av2_KF_VKask2        ( 0x40000000ul )
#define  _Av2_KF_VKask         ( 0x80000000ul )

    //    ����� ��������������2:
    //  �������� ������������� �������� "Reg_PreduprMsg2" �
    //  ������� "Tabl_PreduprMsg2[32]".

#define  _Pr2_PT               ( 0x00000001ul )
//#define  _Pr2_               ( 0x00000002ul ) // _Pr2_AF2P
//#define  _Pr2_               ( 0x00000004ul ) // _Pr2_BV2
#define  _Pr2_NoObjPrg         ( 0x00000008ul )

//#define  _Pr2_               ( 0x00000010ul )
//#define  _Pr2_               ( 0x00000020ul )
//#define  _Pr2_               ( 0x00000040ul )
//#define  _Pr2_               ( 0x00000080ul )

//#define  _Pr2_               ( 0x00000100ul )
//#define  _Pr2_               ( 0x00000200ul )
//#define  _Pr2_               ( 0x00000400ul )
//#define  _Pr2_               ( 0x00000800ul )

//#define  _Pr2_               ( 0x00001000ul )
//#define  _Pr2_               ( 0x00002000ul )
//#define  _Pr2_               ( 0x00004000ul )
//#define  _Pr2_               ( 0x00008000ul )

//#define  _Pr2_               ( 0x00010000ul )
//#define  _Pr2_               ( 0x00020000ul )
//#define  _Pr2_               ( 0x00040000ul )
//#define  _Pr2_               ( 0x00080000ul )

//#define  _Pr2_               ( 0x00100000ul )
//#define  _Pr2_               ( 0x00200000ul )
//#define  _Pr2_               ( 0x00400000ul )
//#define  _Pr2_               ( 0x00800000ul )

//#define  _Pr2_               ( 0x01000000ul )
//#define  _Pr2_               ( 0x02000000ul )
#define  _Pr2_ProbM1_VT11_24   ( 0x04000000ul )
#define  _Pr2_ProbM1_VT12_25   ( 0x08000000ul )

#define  _Pr2_ProbM1_VT13_26   ( 0x10000000ul )
#define  _Pr2_ProbM1_VT14_21   ( 0x20000000ul )
#define  _Pr2_ProbM1_VT15_22   ( 0x40000000ul )
#define  _Pr2_ProbM1_VT16_23   ( 0x80000000ul )

    //    ����� ��������� ���������2:
    //  �������� ������������� �������� "Reg_ServiceMsg2" �
    //  ������� "Tabl_ServiceMsg2[32]".

#define  _Srv2_DP_Wait_Prm     ( 0x00000001ul )
#define  _Srv2_DP_Wait_Cfg     ( 0x00000002ul )
#define  _Srv2_DP_Data_Ex      ( 0x00000004ul )
#define  _Srv2_DP_Baud_S       ( 0x00000008ul )

#define  _Srv2_DP_Baud_C       ( 0x00000010ul )
#define  _Srv2_DP_Control      ( 0x00000020ul )
#define  _Srv2_DP_Snotf        ( 0x00000040ul )
#define  _Srv2_DP_S12M         ( 0x00000080ul )

#define  _Srv2_DP_S6M          ( 0x00000100ul )
#define  _Srv2_DP_S3M          ( 0x00000200ul )
#define  _Srv2_DP_S1M          ( 0x00000400ul )
#define  _Srv2_DP_S500k        ( 0x00000800ul )

#define  _Srv2_DP_S187k        ( 0x00001000ul )
#define  _Srv2_DP_S93k         ( 0x00002000ul )
#define  _Srv2_DP_S45k         ( 0x00004000ul )
#define  _Srv2_DP_S19k         ( 0x00008000ul )

#define  _Srv2_DP_S9k          ( 0x00010000ul )
#define  _Srv2_DP_Nconf        ( 0x00020000ul )
#define  _Srv2_V1              ( 0x00040000ul )
#define  _Srv2_V2              ( 0x00080000ul )

#define  _Srv2_V3              ( 0x00100000ul )
#define  _Srv2_V4              ( 0x00200000ul )
#define  _Srv2_V5              ( 0x00400000ul )
#define  _Srv2_V6              ( 0x00800000ul )

//#define  _Srv2_              ( 0x01000000ul )
#define  _Srv2_NoReadObj_i2c   ( 0x02000000ul )
#define  _Srv2_NeisprQK1_bk    ( 0x04000000ul )
#define  _Srv2_Modbus          ( 0x08000000ul )

#define  _Srv2_Proboy_Tyr      ( 0x10000000ul )
#define  _Srv2_ZashProboy_Tyr  ( 0x20000000ul )
//#define  _Srv2_              ( 0x40000000ul )
#define  _Srv2_RTC_Err         ( 0x80000000ul )

/*------------------------------------------------*/

#ifdef _TRETIY_REG
    //    ����� ������3:
    //  �������� ������������� �������� "Reg_AvarMsg3" �
    //  ������� "Tabl_AvarMsg3[32]".

//#define  _Av3_               ( 0x00000001ul )
//#define  _Av3_               ( 0x00000002ul )
//#define  _Av3_               ( 0x00000004ul )
//#define  _Av3_               ( 0x00000008ul )

#define  _Av3_RV1_VAT          ( 0x00000010ul )
//#define  _Av3_               ( 0x00000020ul )
//#define  _Av3_               ( 0x00000040ul )
//#define  _Av3_               ( 0x00000080ul )

//#define  _Av3_               ( 0x00000100ul )
//#define  _Av3_               ( 0x00000200ul )
//#define  _Av3_               ( 0x00000400ul )
//#define  _Av3_               ( 0x00000800ul )

//#define  _Av3_               ( 0x00001000ul )
//#define  _Av3_               ( 0x00002000ul )
//#define  _Av3_               ( 0x00004000ul )
//#define  _Av3_               ( 0x00008000ul )

//#define  _Av3_               ( 0x00010000ul )
//#define  _Av3_               ( 0x00020000ul )
//#define  _Av3_               ( 0x00040000ul )
//#define  _Av3_               ( 0x00080000ul )

//#define  _Av3_               ( 0x00100000ul )
//#define  _Av3_               ( 0x00200000ul )
//#define  _Av3_               ( 0x00400000ul )
//#define  _Av3_               ( 0x00800000ul )

//#define  _Av3_               ( 0x01000000ul )
//#define  _Av3_               ( 0x02000000ul )
//#define  _Av3_               ( 0x04000000ul )
//#define  _Av3_               ( 0x08000000ul )

//#define  _Av3_               ( 0x10000000ul )
//#define  _Av3_               ( 0x20000000ul )
//#define  _Av3_               ( 0x40000000ul )
//#define  _Av3_               ( 0x80000000ul )

    //    ����� ��������������3:
    //  �������� ������������� �������� "Reg_PreduprMsg3" �
    //  ������� "Tabl_PreduprMsg3[32]".

//#define  _Pr3_               ( 0x00000001ul )
//#define  _Pr3_               ( 0x00000002ul )
//#define  _Pr3_               ( 0x00000004ul )
//#define  _Pr3_               ( 0x00000008ul )

//#define  _Pr3_               ( 0x00000010ul )
//#define  _Pr3_               ( 0x00000020ul )
//#define  _Pr3_               ( 0x00000040ul )
//#define  _Pr3_               ( 0x00000080ul )

//#define  _Pr3_               ( 0x00000100ul )
//#define  _Pr3_               ( 0x00000200ul )
//#define  _Pr3_               ( 0x00000400ul )
//#define  _Pr3_               ( 0x00000800ul )

//#define  _Pr3_               ( 0x00001000ul )
//#define  _Pr3_               ( 0x00002000ul )
//#define  _Pr3_               ( 0x00004000ul )
//#define  _Pr3_               ( 0x00008000ul )

//#define  _Pr3_               ( 0x00010000ul )
//#define  _Pr3_               ( 0x00020000ul )
//#define  _Pr3_               ( 0x00040000ul )
//#define  _Pr3_               ( 0x00080000ul )

//#define  _Pr3_               ( 0x00100000ul )
//#define  _Pr3_               ( 0x00200000ul )
//#define  _Pr3_               ( 0x00400000ul )
//#define  _Pr3_               ( 0x00800000ul )

//#define  _Pr3_               ( 0x01000000ul )
//#define  _Pr3_               ( 0x02000000ul )
//#define  _Pr3_               ( 0x04000000ul )
//#define  _Pr3_               ( 0x08000000ul )

//#define  _Pr3_               ( 0x10000000ul )
//#define  _Pr3_               ( 0x20000000ul )
//#define  _Pr3_               ( 0x40000000ul )
//#define  _Pr3_               ( 0x80000000ul )

    //    ����� ��������� ���������3:
    //  �������� ������������� �������� "Reg_ServiceMsg3" �
    //  ������� "Tabl_ServiceMsg3[32]".

//#define  _Srv3_              ( 0x00000001ul )
//#define  _Srv3_              ( 0x00000002ul )
//#define  _Srv3_              ( 0x00000004ul )
//#define  _Srv3_              ( 0x00000008ul )

//#define  _Srv3_              ( 0x00000010ul )
//#define  _Srv3_              ( 0x00000020ul )
//#define  _Srv3_              ( 0x00000040ul )
//#define  _Srv3_              ( 0x00000080ul )

//#define  _Srv3_              ( 0x00000100ul )
//#define  _Srv3_              ( 0x00000200ul )
//#define  _Srv3_              ( 0x00000400ul )
//#define  _Srv3_              ( 0x00000800ul )

//#define  _Srv3_              ( 0x00001000ul )
//#define  _Srv3_              ( 0x00002000ul )
//#define  _Srv3_              ( 0x00004000ul )
//#define  _Srv3_              ( 0x00008000ul )

//#define  _Srv3_              ( 0x00010000ul )
//#define  _Srv3_              ( 0x00020000ul )
//#define  _Srv3_              ( 0x00040000ul )
//#define  _Srv3_              ( 0x00080000ul )

//#define  _Srv3_              ( 0x00100000ul )
//#define  _Srv3_              ( 0x00200000ul )
//#define  _Srv3_              ( 0x00400000ul )
//#define  _Srv3_              ( 0x00800000ul )

//#define  _Srv3_              ( 0x01000000ul )
//#define  _Srv3_              ( 0x02000000ul )
//#define  _Srv3_              ( 0x04000000ul )
//#define  _Srv3_              ( 0x08000000ul )

//#define  _Srv3_              ( 0x10000000ul )
//#define  _Srv3_              ( 0x20000000ul )
//#define  _Srv3_              ( 0x40000000ul )
//#define  _Srv3_              ( 0x80000000ul )
#endif

//----------------------------------------
#ifdef _MSG_INCLUDE
//----------------------------------------

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_AvarMsg". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
const struct Tabl_MSG  Tabl_Msg =
{
  //const char *const Tabl_AvarMsg[32]  =
       {
         "Id-����.        ",
#ifndef  bi_2B1  //bi_GerconAC2
         "���������� ��.  ", // "������/I��-����.", //"����.�����.����.",
         "������� ��.     ", // "����.����.����. ",
#else
         "������������-��1", // "����/I��-������1", //"������ ��1,2.   ",
         "������������-��2", // "����/I��-������2",//"������ ��3,4.   ",
#endif
         "������������.   ",  //a1-03

         "������� ��� ���.",
         "�����������-1GL.",
         "E-����.         ",
         "N-����.         ",

//#ifdef bi_AK2
          "����.���.'~'���a", // "����.Q1-1AK.    ",  //a1-08
//#else
//      "������� ����-1AK",  //a1-08
//#endif
//#ifdef  bi_TK1
//       "��������-1��.   ",  //a1-09
//#else //bi_BV1
         "����������-1BV. ",  //a1-09
//#endif
         "���-1AF.        ", //a1-10
         "����������� ����", // "����.����.-1VR. ",  //a1-11

         "����������.     ",
         "��� �����. U��. ", // "��� �����.'TC1'.",
         "T����. U��-����.", // "T����'TC1'-����.",
         "T����. U��-���. ", // "T����'TC1'-���. ",

         "��������������. ",
         "If-���.         ",
         "If-����.        ",
         "������� 2P24.   ",

         "����� ����.����.",
         "������� ������. ",
         "������.���.����.",
         "����������� ��. ",

         "�������.���.-1PR",
         "�������.���.-2PR",
         "������� ��.����.",
         "��� �����. U���.", // "��� U���/����TC2",

         "��� �����.����. ",
         "������ �������. ",
         "���������.����. ",
         "���������� ����." },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_PreduprMsg". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_PreduprMsg[32]  =
       {
         "p1-00.          ",
         "������ �������. ",
         "����.�� �������.",
         "������� ��� ���.",

         "��������.       ",
         "p1-05.          ", // "��������-1AR.   ",
//#ifdef bi_PT // �������� ��������� ���������� .
//       "������.����.-1BV",
//#else
         "����������-1BV. ",
//#endif
         "����������.     ",

         "��� ����. �C��. ",
         "��� ����. �C��. ",
         "p1-10.",
         "p1-11.",

         "������� P24.    ",
         "������� P12.    ",
         "������� N12.    ",
         "��������-1��.   ",

         "�� ������.�� ��C",
         "����� WatchDog. ",
         "p1-18.          ",
         "p1-19.          ",

         "p1-20.          ", // "�������� ���.   ",
         "��������� �����.",
         "��� ����������. ",
         "����� �������.  ",

         "���-1AF.        ",
         "�������.���.-1PR",
         "����� ���.4-20��",
         "��� ������. ���.", // "������. ���.���.",

         "������� ���.���.",
         "������ �������. ",
         "���������.����. ",
         "���������� ����."
     },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_ServiceMsg". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_ServiceMsg[32]  =
       {
         "��� �������.���.",
         "������� �� ����.", // "�� �������-1GY. ",
         "���������� �����",
         "������� � �����a",

         "�� �����������! ",
         "Te ����������.  ",
         "Tm ����������.  ",
         "��� �����.Id-��.",

         "Ti,Kp �����-��. ",
         "�� ���� If!     ",
         "��� ���.�������.",
         "��� ���.�������.",

         "��� �������� Id.",
         "��� ��������. If",
         "s1-14.          ", // "��������'Id2'.  ",
         "s1-15.          ", // "��������'Id2-cp'",

         "s1-16.          ", // "��������'Id'.   ",
         "s1-17.          ", // "��������'Id-��'.",
         "s1-18.          ", // "��������'Ud'.   ",
         "s1-19.          ", // "���������� ���  ",

         "��� �����-�����.",
         "��� ���. ������a",
         "s1-22.          ", // "��� ������ ����.",
         "s1-23.          ", // "��� ������ ����.",

         "��� ������ ���. ",
         "��� ������ ���. ",
         "�����.����� ���.",
         "��� �����-�����.",

         "���.��������� �T",
         "����� CAN.      ",
         "������ � �����. ",
         "��� �����-���.�K"
     },

/*------------------------------------------------*/

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_AvarMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
  //const char *const Tabl_AvarMsg2[32]  =
       {
         "a2-00.          ", // "Id2-����.       ",//"Id-����-�������o",
         "a2-01.          ",  // "������� 1�.     ",
         "a2-02.          ",  // "������� 2�.     ",
         "����.���.'='���a", // "����.Q2-2AK.    ",

         "�����.����.-1SQ.",
         "��� U���.-1AM.  ", // "�����.����.-1AM.",
         "���-1RV.        ",
         "��� ����.����.�T",

         "T����. U���-���c", // "T����'TC2'-����.",
         "T����. U���-���.", // "T����'TC2'-���. ",
         "a2-10.          ", // "�����.����.-2AM.",
         "�����.����.-SF3.",

         "��������-2BK.   ",
         "�� ��������-1��.", // "����.����.-1MB. ",
         "��������-AT.    ",
         "a2-15.          ", // "���-2AF.        ",

         "Id1-����.       ",
         "Id2-����.       ",
         "If2-���.        ",
         "�����������-2GL.",

         "���������������c", // "������ ������-�a",
         "���.����.���-KP1",
         "���.����.���-KP2",
         "��������.������.",

         "a2-24.          ",
         "����.����������.",
         "a2-26.          ",
         "a2-27.          ",

         "a2-28.          ",
         "a2-29.          ",
         "����.�������-KF2",
#ifdef bi_KF_VKask2
         "����.�������-KF1"
#else
         "�������.�������." //"�������.�V1-AV2.",
#endif
       },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_PreduprMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_PreduprMsg2[32]  =
       {
         "��������-PT.    ",
         "p2-01.          ", // "���-2AF.        ",
//#ifdef bi_PT // �������� ��������� ���������� .
         "p2-02.          ", // "������.����.-2BV",
//#else
//         "����������-2BV. ",
//#endif
         "������ �����.   ",

         "p2-04.          ",
         "p2-05.          ",
         "p2-06.          ",
         "p2-07.          ",

         "p2-08.          ",
         "p2-09.          ",
         "p2-10.          ",
         "p2-11.          ",

         "p2-12.          ",
         "p2-13.          ",
         "p2-14.          ",
         "p2-15.          ",

         "p2-16.          ",
         "p2-17.          ",
         "p2-18.          ",
         "p2-19.          ",

         "p2-20.          ",
         "p2-21.          ",
         "p2-22.          ",
         "p2-23.          ",

         "p2-24.          ",
         "p2-25.          ",
         "����.���.V11(24)",
         "����.���.V12(25)",

         "����.���.V13(26)",
         "����.���.V14(21)",
         "����.���.V15(22)",
         "����.���.V16(23)"
     },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_ServiceMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_ServiceMsg2[32]  =
       {
         "DP: Wait Param  ",
         "DP: Wait Config ",
         "DP: Data Exchang",
         "DP: Baud Search ",

         "DP: Baud Control",
         "DP: DP Control  ",
         "DP: ����.�� ���.",
         "DP: ���� - 12�� ",

         "DP: ���� - 6��  ",
         "DP: ���� - 3��  ",
         "DP: ���� - 1,5��",
         "DP: ���� - 500��",

         "DP: ���� - 187��",
         "DP: ���� - 93�� ",
         "DP: ���� - 45�� ",
         "DP: ���� - 19�� ",

         "DP: ���� - 9,6��",
         "DP: ����.������.",
         "���. V1 �� ����.",
         "���. V2 �� ����.",

         "���. V3 �� ����.",
         "���. V4 �� ����.",
         "���. V5 �� ����.",
         "���. V6 �� ����.",

         "s2-24.          ",
         "��� ������ ���. ",
         "������.�/� QK1. ",
         "������ Modbus   ",

         "������ ���.���. ",
         "���.��� ������. ",
         "s2-30.          ",
         "��� �����.�����."
     }

#ifdef _TRETIY_REG
     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_AvarMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
  //const char *const Tabl_AvarMsg2[32]  =
      ,{
         "a3-00.          ",
         "a3-01.          ",
         "a3-02.          ",
         "a3-03.          ",

         "�����������-1RV.",
         "a3-05.          ",
         "a3-06.          ",
         "a3-07.          ",

         "a3-08.          ",
         "a3-09.          ",
         "a3-10.          ",
         "a3-11.          ",

         "a3-12.          ",
         "a3-13.          ",
         "a3-14.          ",
         "a3-15.          ",

         "a3-16.          ",
         "a3-17.          ",
         "a3-18.          ",
         "a3-19.          ",

         "a3-20.          ",
         "a3-21.          ",
         "a3-22.          ",
         "a3-23.          ",

         "a3-24.          ",
         "a3-25.          ",
         "a3-26.          ",
         "a3-27.          ",

         "a3-28.          ",
         "a3-29.          ",
         "a3-30.          ",
         "a3-31.          "
       },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_PreduprMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_PreduprMsg2[32]  =
       {
         "p3-00.          ",
         "p3-01.          ",
         "p3-02.          ",
         "p3-03.          ",

         "p3-04.          ",
         "p3-05.          ",
         "p3-06.          ",
         "p3-07.          ",

         "p3-08.          ",
         "p3-09.          ",
         "p3-10.          ",
         "p3-11.          ",

         "p3-12.          ",
         "p3-13.          ",
         "p3-14.          ",
         "p3-15.          ",

         "p3-16.          ",
         "p3-17.          ",
         "p3-18.          ",
         "p3-19.          ",

         "p3-20.          ",
         "p3-21.          ",
         "p3-22.          ",
         "p3-23.          ",

         "p3-24.          ",
         "p3-25.          ",
         "p3-26.          ",
         "p3-27.          ",

         "p3-28.          ",
         "p3-29.          ",
         "p3-30.          ",
         "p3-31.          "
     },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_ServiceMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_ServiceMsg2[32]  =
       {
         "s3-00.          ",
         "s3-01.          ",
         "s3-02.          ",
         "s3-03.          ",

         "s3-04.          ",
         "s3-05.          ",
         "s3-06.          ",
         "s3-07.          ",

         "s3-08.          ",
         "s3-09.          ",
         "s3-10.          ",
         "s3-11.          ",

         "s3-12.          ",
         "s3-13.          ",
         "s3-14.          ",
         "s3-15.          ",

         "s3-16.          ",
         "s3-17.          ",
         "s3-18.          ",
         "s3-19.          ",

         "s3-20.          ",
         "s3-21.          ",
         "s3-22.          ",
         "s3-23.          ",

         "s3-24.          ",
         "s3-25.          ",
         "s2-26.          ",
         "s2-27.          ",

         "s2-28.          ",
         "s2-29.          ",
         "s2-30.          ",
         "s2-31.          "
     }
#endif    // _TRETIY_REG
};
//----------------------------------------
#endif    // _MSG_INCLUDE
//----------------------------------------

#endif    // msg_head
