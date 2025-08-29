
/* ������������ ����: �������� ����� ����� ������� ������ ���������  */
/*                   � ����������������� ���������.  */
/*----------------------------------------------------------------------------*/

#ifndef msg_head
#define msg_head

// ��� ��������� ������������ ������������ ���:
//#undef  _Device_Name_
//#define _Device_Name_ "     -��K5-     "

// ������������ ��������� �������� :
#define   _PROGRAM_     "��������"

// ����������� ����� ����� ��������:
#define   _DECIMAL_     "  A.656457.749  "

//----------------------------------------
#ifdef _MAIN_INCLUDE
//----------------------------------------

//----- ������������ ��������� ��� �������� ������� ------

const char *const Tabl_name_ust[_kol_obl]  =
 {
  "�����.�����."
//"2.�������   "
 };

//-------------- �8 - ������� ������� --------------------

_x_far const struct Bits    bts[] =
  {
      _KTE_A8_Cfg1 ,
      _KTE_A8_Cfg2 ,
#ifdef  _KTE_A8_ConfigObj
    { "K�����.����." , (w*)&_or.CfgO.all,  4  ,
                               { 
                                 "������0     ", //"���1        ",
                                 "������1     ", //"���2        ",
                                 "������2     ", //"���R        ",
                                 "OnOIRTRevers",
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
                               { "K8-���� ��� ",
                                 "KG10-������.",
                                 "KG11-������.",
                                 "������3     ",
                                 "������4     ",
                                 "������5     " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 /*, 0x40 , 0x80*/ },
       (w*)&_Msk ,1
    },
#endif
#ifdef _AsPo_INVERT     // ������� ����������� �������� �������� �������� .
    { "AsPo0-���.  " , &_or.PoS_Normal[0],  8 ,
                               { "�1-�����   ",
                                 "K2-������.  ",
                                 "K3-��������.",
                                 "K4-������   ",
                                 "K5-n=490    ",
                                 "K6-n min    ",
                                 "������6     ",
                                 "�7-������   " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
    { "AsPo1-���.  " , &_or.PoS_Normal[1],  8 ,
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
    { "AsPo2-���.  " , &_or.PoS_Normal[2],  8 ,
                               { "������0     ",
                                 "������1     ",
                                 "������2     ",
                                 "������3     ",
                                 "�13-������  ",
                                 "�14-������  ",
                                 "�15-������  ",
                                 "�16-������  " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },

#endif
    { "Pi0-������. " , &_r.Pi0_Normal,  8 ,
                               { "2P24        ",
                                 "������1     ",
                                 "FF1-�����.Ѳ",
                                 "F-�����.Ѳ  ",
                                 "1SQ-�����Ѳ",
                                 "������5     ",
                                 "������6     ",
                                 "����.������." },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#ifdef  _Pi1_
    { "Pi1-������. " , &_r.Pi1_Normal,  8 ,     /* CM3 */
                               {
                                 "������0/INT7",
                                 "net    /INT2",
                                 "������2/INT5",
                                 "������3/INT6",
                                 "PPG4   /INT4",
                                 "������5/INT3",
                                 "I�-max/INT0",
                                 "I��-max/INT1"
                               },
        { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
         (w*)&_Msk ,1
      },
#endif
#ifdef  _AsPi0_
    { "AsPi0-���.  " , &_or.PiS_Normal[0],  8 ,
                               { "������0     ",
                                 "������.����",
                                 "Q1-1        ",
                                 "Q1-2        ",
                                 "SF2         ",
                                 "SFV1        ",
                                 "KV1         ",
                                 "�������.���."
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi1_
    { "AsPi1-���.  " , &_or.PiS_Normal[1],  8 ,
                               { "1BV1        ",
                                 "2BV1        ",
                                 "������2     ",
                                 "������3     ",
                                 "������4     ",
                                 "������5     ",
                                 "������6     ",
                                 "������7     "
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi2_
    { "AsPi2-���.  " , &_or.PiS_Normal[2],  8 ,
                               {
                                 "�� �����.  ",
                                 "��1 ������  ",
                                 "��3 ������. ",
                                 "����        ",
                                 "����        ",
                                 "����� ���� ",
                                 "������ �����",
                                 "�1/�3 ����."
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi3_
    { "AsPi3-���.  " , &_or.PiS_Normal[3],  1 ,
                               { "������      "
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
    /*_KTE_A8_cCfgR ,
      _KTE_A8_cStsR ,*/
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
#define  _Av_SQ1_ATK1          ( 0x00020000ul )  //_Av_Iv_Min
#define  _Av_SQ1_ATKR          ( 0x00040000ul )  //_Av_Iv_Max
#define  _Av_2P24              ( 0x00080000ul )

#define  _Av_CAN_avar          ( 0x00100000ul )
#define  _Av_Vnesh_Avar        ( 0x00200000ul )
#define  _Av_dN_Max            ( 0x00400000ul )
#define  _Av_Iv_TG             ( 0x00800000ul )

//#define  _Av_Vnesh_AvarPult    ( 0x01000000ul )  //_Av_PR1  //DAN 12.04.2025
#define  _Av_SQ1_ATK2          ( 0x02000000ul )  //_Av_PR2
#define  _Av_CTC_Temper        ( 0x04000000ul )  //_Av_PUM
#define  _Av_NoSynch2          ( 0x08000000ul )

#define  _Av_DC_Circuit        ( 0x10000000ul )
//#define  _Av_TP                ( 0x20000000ul )  //_Av_Smazka_Podsh      // DAN 12.04.2025
#define  _Av_SQ1               ( 0x40000000ul )  //_Av_MasloSmazka
#define  _Av_SQ2               ( 0x80000000ul )  //_Av_Vent_Dvig

    //    ����� ��������������:
    //  �������� ������������� �������� "Reg_PreduprMsg" �
    //  ������� "Tabl_PreduprMsg[32]".
#define  _Pr_All               ( 0xFFFFFFFFul )

#define  _Pr_ATK_Rezerv        ( 0x00000001ul )
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
#define  _Pr_dT_ShS2           ( 0x00040000ul )
#define  _Pr_dT_ShS1           ( 0x00080000ul )

#define  _Pr_CTC_Temper        ( 0x00100000ul )  // _Pr_OffsetAch
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

#define  _Srv_No_EDS_Nom         0
#define  _Srv_MT                 0
#define  _Srv_PultTolchki        0
#define  _Srv_NoCAN_QK           0

#define  _Srv_CAN_avarATK1     ( 0x00000001ul ) // _Srv_No_EDS_Nom
#define  _Srv_CAN_avarATK2     ( 0x00000002ul ) // _Srv_MT
#define  _Srv_F2_regim         ( 0x00000004ul )
#define  _Srv_CAN_avarATKR     ( 0x00000008ul ) // _Srv_PultTolchki

#define  _Srv_Link_ATK_otkl    ( 0x00000010ul ) // _Srv_AN_Av
#define  _Srv_Pusk_off         ( 0x00000020ul ) // _Srv_AN_Ra_Te
#define  _Srv_Mestnoe          ( 0x00000040ul ) // _Srv_NzadSmeshMax   // _Srv_AN_Tm        // DAN 12.04.2025
#define  _Srv_VR1              ( 0x00000080ul ) // _Srv_AN_Err                            // DAN 12.04.2025

//#define  _Srv_Reversor1On      ( 0x00000100ul ) // _Srv_AN_Kreg         DAN 12.04.2025
//#define  _Srv_Reversor2On      ( 0x00000200ul ) // _Srv_AN_Iv_min       DAN 12.04.2025
#define  _Srv_ErrWrClock_i2c   ( 0x00000400ul )
#define  _Srv_ErrRdClock_i2c   ( 0x00000800ul )

#define  _Srv_ATK1_Predupr     ( 0x00001000ul ) // _Srv_Not_Nul_Id
#define  _Srv_ATKR_Predupr     ( 0x00002000ul ) // _Srv_Not_Iv
//#define  _Srv_Reversor1        ( 0x00004000ul ) // _Srv_Offset_Id2_mg    DAN 12.04.2025
//#define  _Srv_Reversor2        ( 0x00008000ul ) // _Srv_Offset_Id2_sr    DAN 12.04.2025

#define  _Srv_AP2_ne_vRabote   ( 0x00010000ul ) // _Srv_Offset_Id_mg
//#define  _Srv_NoLinkCAN2_atk1  ( 0x00020000ul ) // _Srv_Offset_Id_sr
//#define  _Srv_NoLinkCAN2_atkr  ( 0x00040000ul ) // _Srv_Offset_Ud
#define  _Srv_KV1_vid_ShI      ( 0x00080000ul ) // _Srv_ATK_ne_Vybran  // _Srv_ErrorOZU     // DAN 12.04.2025

#define  _Srv_NoCAN_Start      ( 0x00100000ul )
#define  _Srv_AvarRevers       ( 0x00200000ul )
#define  _Srv_NotWorkATK1      ( 0x00400000ul ) // _Srv_NoRead_time
#define  _Srv_NotWorkATKR      ( 0x00800000ul ) // _Srv_NoWrite_time

#define  _Srv_NoRead_i2c       ( 0x01000000ul )
#define  _Srv_NoWrite_i2c      ( 0x02000000ul )
#define  _Srv_NoCheckSum_i2c   ( 0x04000000ul )
#define  _Srv_NoCAN_Connect    ( 0x08000000ul )

//#define  _Srv_Err_SA9_PU       ( 0x10000000ul ) // _Srv_QKDT         // DAN 12.04.2025
#define  _Srv_ResCan           ( 0x20000000ul )
#define  _Srv_UstCnst          ( 0x40000000ul )
#define  _Srv_Err_PereclRegim  ( 0x80000000ul ) // _Srv_NoCAN_QK

/*------------------------------------------------*/

    //    ����� ������2:
    //  �������� ������������� �������� "Reg_AvarMsg2" �
    //  ������� "Tabl_AvarMsg2[32]".

//#define  _Av2_               ( 0x00000001ul ) // _Av2_Id2_Max// ��� 12-�� ��������� ���� .
#define  _Av2_Ishs2            ( 0x00000002ul )  // _Av2_1P
#define  _Av2_Ishs1            ( 0x00000004ul )  // _Av2_2P
#define  _Av2_AK2              ( 0x00000008ul )

#define  _Av2_SQ1              ( 0x00000010ul )
#define  _Av2_AM1              ( 0x00000020ul )
#define  _Av2_RV1              ( 0x00000040ul )
#define  _Av2_QKDT             ( 0x00000080ul )

#define  _Av2_Tmax2            ( 0x00000100ul )
#define  _Av2_Tmin2            ( 0x00000200ul )
#define  _Av2_Pimp2            ( 0x00000400ul ) // _Av2_AM2
#define  _Av2_Pimp1            ( 0x00000800ul )

#define  _Av2_BK2              ( 0x00001000ul )
#define  _Av2_dT_ShS2          ( 0x00002000ul )
#define  _Av2_dT_ShS1          ( 0x00004000ul )
#define  _Av2_SF3              ( 0x00008000ul ) // _Av2_AF2

#define  _Av2_Id1Max           ( 0x00010000ul )  // ��� ��Id 2� ������ ����� ����������� .
#define  _Av2_Id2Max           ( 0x00020000ul )
#define  _Av2_AvarUKAV         ( 0x00040000ul ) // _Av2_Iv2_Min                        //DAN 12.04.2025
#define  _Av2_V1_V3            ( 0x00080000ul ) // _Av2_GL2                            //DAN 12.04.2025

#define  _Av2_t_Trans          ( 0x00100000ul )
#define  _Av2_KP               ( 0x00200000ul )
#define  _Av2_KP2              ( 0x00400000ul )
#define  _Av2_KTE2             ( 0x00800000ul ) // _Av2_MT_Err

#define  _Av2_Fsil_set         ( 0x01000000ul )
#define  _Av2_KFV_VKask        ( 0x02000000ul )
#define  _Av2_VV1_stator       ( 0x04000000ul ) // _Av2_Fsil_KZ // _Av2_CAN_avarATK1   //DAN 12.04.2025
#define  _Av2_VV3_trans        ( 0x08000000ul ) // _Av2_SF5 // _Av2_CAN_avarATKR       //DAN 12.04.2025

#define  _Av2_Tizm2            ( 0x10000000ul )
#define  _Av2_Tizm1            ( 0x20000000ul )
#define  _Av2_KF_VKask2        ( 0x40000000ul )
#define  _Av2_KF_VKask         ( 0x80000000ul )

    //    ����� ��������������2:
    //  �������� ������������� �������� "Reg_PreduprMsg2" �
    //  ������� "Tabl_PreduprMsg2[32]".

#define  _Pr2_PT               ( 0x00000001ul )
#define  _Pr2_Vent_Shs2        ( 0x00000002ul ) // _Pr2_AF2P
#define  _Pr2_Vent_Shs1        ( 0x00000004ul ) // _Pr2_BV2
//#define  _Pr2_NoObjPrg         ( 0x00000008ul )

#define  _Pr2_SF2              ( 0x00000010ul )
#define  _Pr2_SF3              ( 0x00000020ul )
#define  _Pr2_BV2              ( 0x00000040ul ) // DAN 12.04.2025
#define  _Pr2_ShemaShK         ( 0x00000080ul )

#define  _Pr2_Pimp2            ( 0x00000100ul )
#define  _Pr2_Pimp1            ( 0x00000200ul )
#define  _Pr2_Tizm14           ( 0x00000400ul )
#define  _Pr2_Tizm13           ( 0x00000800ul )

#define  _Pr2_Tizm12           ( 0x00001000ul )
#define  _Pr2_Tizm11           ( 0x00002000ul )
#define  _Pr2_Tizm10           ( 0x00004000ul )
#define  _Pr2_Tizm9            ( 0x00008000ul )

#define  _Pr2_Tizm8            ( 0x00010000ul )
#define  _Pr2_Tizm7            ( 0x00020000ul )
#define  _Pr2_Tizm6            ( 0x00040000ul )
#define  _Pr2_Tizm5            ( 0x00080000ul )

#define  _Pr2_Tizm4            ( 0x00100000ul )
#define  _Pr2_Tizm3            ( 0x00200000ul )
#define  _Pr2_Tizm2            ( 0x00400000ul )
#define  _Pr2_Tizm1            ( 0x00800000ul )

#define  _Pr2_SFV1             ( 0x01000000ul )  // DAN 12.04.2025
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

#define  _Srv2_V1                0
#define  _Srv2_V2                0
#define  _Srv2_V3                0
#define  _Srv2_V4                0
#define  _Srv2_V5                0
#define  _Srv2_V6                0
#define  _Srv2_DP_Wait_Prm       0
#define  _Srv2_DP_Wait_Cfg       0
#define  _Srv2_DP_Data_Ex        0
#define  _Srv2_DP_Baud_S         0
#define  _Srv2_DP_Baud_C         0
#define  _Srv2_DP_Control        0
#define  _Srv2_DP_Snotf          0
#define  _Srv2_DP_S12M           0

//#define  _Srv2_ST1err          ( 0x00000001ul )  //_Srv2_DP_Wait_Prm       // DAN 12.04.2025
//#define  _Srv2_SM1err          ( 0x00000002ul )  //_Srv2_DP_Wait_Cfg       // DAN 12.04.2025
//#define  _Srv2_ST2err          ( 0x00000004ul )  //_Srv2_DP_Data_Ex        // DAN 12.04.2025
//#define  _Srv2_SM2err          ( 0x00000008ul )  //_Srv2_DP_Baud_S         // DAN 12.04.2025

//#define  _Srv2_ST1middle       ( 0x00000010ul )  //_Srv2_DP_Baud_C         // DAN 12.04.2025
//#define  _Srv2_SM1middle       ( 0x00000020ul )  //_Srv2_DP_Control        // DAN 12.04.2025
//#define  _Srv2_ST2middle       ( 0x00000040ul )  //_Srv2_DP_Snotf          // DAN 12.04.2025
//#define  _Srv2_SM2middle       ( 0x00000080ul )  //_Srv2_DP_S12M           // DAN 12.04.2025

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
#define  _Srv2_NotWorkATK2     ( 0x00040000ul )  //_Srv2_V1
#define  _Srv2_AP2_Predupr     ( 0x00080000ul )  //_Srv2_V2

#define  _Srv2_ATK2_Predupr    ( 0x00100000ul )  //_Srv2_V3
#define  _Srv2_ErrNumbATK      ( 0x00200000ul )  //_Srv2_V4
#define  _Srv2_ErrNumbAbon     ( 0x00400000ul )  //_Srv2_V5
#define  _Srv2_Technol_Ostanov ( 0x00800000ul )  //_Srv2_V6

#define  _Srv2_NoLinkCAN       ( 0x01000000ul )
#define  _Srv2_NoReadObj_i2c   ( 0x02000000ul )
#define  _Srv2_NeisprQK1_bk    ( 0x04000000ul )
#define  _Srv2_Modbus          ( 0x08000000ul )

#define  _Srv2_Proboy_Tyr      ( 0x10000000ul )
#define  _Srv2_ZashProboy_Tyr  ( 0x20000000ul )
#define  _Srv2_NoLinkCAN2      ( 0x40000000ul )
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

#define  _Srv3_BK12            ( 0x00000001ul )
#define  _Srv3_BK11            ( 0x00000002ul )
#define  _Srv3_BK10            ( 0x00000004ul )
#define  _Srv3_BK9             ( 0x00000008ul )

#define  _Srv3_BK8             ( 0x00000010ul )
#define  _Srv3_BK7             ( 0x00000020ul )
#define  _Srv3_BK6             ( 0x00000040ul )
#define  _Srv3_BK5             ( 0x00000080ul )

#define  _Srv3_BK4             ( 0x00000100ul )
#define  _Srv3_BK3             ( 0x00000200ul )
#define  _Srv3_BK2             ( 0x00000400ul )
#define  _Srv3_BK1             ( 0x00000800ul )

//#define  _Srv3_             ( 0x00001000ul )
//#define  _Srv3_             ( 0x00002000ul )
//#define  _Srv3_             ( 0x00004000ul )
//#define  _Srv3_             ( 0x00008000ul )

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
         "Id-����.        ", //"Id-����-���.���.", - 13.06.2021 ���� ��������� �� ��� ���� Id � Irot .
#ifndef  bi_2B1  //bi_GerconAC2
         "I��-����-�����. ", //"�������.��-�����", // "���������� ��.  ", // "������/I��-����.", //"����.�����.����.",
         "I��-����-����.  ", //"�������.��-����.", // "������� ��.     ", // "����.����.����. ",
#else
         "������� ��-��1", // "����/I��-������1", //"������ ��1,2.   ",
         "������� ��-��2", // "����/I��-������2",//"������ ��3,4.   ",
#endif
         "�����������.   ",  //a1-03

         "�����. �� �����",
         "���������-1GL.  ",
         "E-����.         ",
         "N-����.         ",

//#ifdef bi_AK2
          "³��.���.'~'����", // "����.Q1-1AK.    ",  //a1-08
//#else
//      "������� ����-1AK",  //a1-08
//#endif
//#ifdef  bi_TK1
//       "��������-1��.   ",  //a1-09
//#else //bi_BV1
         "�����������-1BV.",  //a1-09
//#endif
         "���-1AF.        ", //a1-10
         "������� ����    ", // "����.����.-1VR. ",  //a1-11

         "��������������  ",
         "���� ����. U��", // "��� �����.'TC1'.",
         "T���. U��-����.", // "T����'TC1'-����.",
         "T���. U��-��. ", // "T����'TC1'-���. ",

         "�������������� ",
         "���� ��/��-���1",  //"If-���.         ",
         "���� ��/��-���R",  //"If-����.        ",
         "�������� 2P24.  ",

         "����� ����.����",
         "�������� ����. ",  //"������� ������. ",
         "�����.���.����� ",
         "��������� ��.   ",

         "a1-24.          ",  //"����.����.�� ���",  //"�������.���.-1PR",        //DAN 12.04.2025
         "���� ��/��-���2",  //"�������.���.-2PR",
         "������.���.����.", // "����� ��-���2.  ",  //"������� ��.����.",
         "���� ����.U���", // "��� U���/����TC2",

         "���� �����.����",
         "a1-29.          ",  //"�� ��������.    ",  //"������ �������. ",       // DAN 12.04.2025
         "���� ��/��.    ",  //"���������.����. ",
         "���� ��.       " },//"���������� ����." },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_PreduprMsg". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_PreduprMsg[32]  =
       {
         "���  � ������  ",
         "������ �������� ",
         "�����.�� �������",
         "�����. �� �����",

         "��������.       ",
         "p1-05.          ", // "��������-1AR.   ",
//#ifdef bi_PT // �������� ��������� ���������� .
//       "������.����.-1BV",
//#else
         "���������.-1BV  ",
//#endif
         "��������������  ",

         "���� ����. �C��",
         "���� ����. �C��",
         "p1-10.",
         "p1-11.",

         "�������� P24.   ",
         "�������� P12.   ",
         "�������� N12.   ",
         "������� ������.",  //"��������-1��.   ",

         "�� �����.�� ��C ",
         "������ WatchDog.",
         "�������� ��  �� ",
         "�������� ��  ز ",

         "����� ���.����.", // _Pr_CTC_Temper
         "�������� �����. ",
         "��� ����������. ",
         "����� ��������. ",

         "�������� ������.",  //"���-1AF.        ",
         "������.���.-1PR",
         "����� ���.4-20��",
         "���� ���. ����", // "������. ���.���.",

         "������� ���.���",
         "������� ������.",
         "�������.����.   ",
         "���������� ����."
     },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_ServiceMsg". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_ServiceMsg[32]  =
       {
         "����.����.���1.", // "��� �������.���.",
         "����.����.���2.", // "������� �� ����.", // "�� �������-1GY. ",
         "��������.�����  ",
         "����.����.���R.", // "������� � �����a",

         "��'��. ��� ���� ", //"�� �����������! ",
         "���� ���. ���� ", //"Te ����������.  ",
         "̳����� �������.", //"�������� �������", //"Tm ����������.  ",                                 // DAN 12.04.2025
         "������� ����    ", //"�� ��������.    ", //"��� �����.Id-��.",                                 // DAN 12.04.2025

         "s1-08.          ", //"��������1 ���.  ", // "Ti,Kp �����-��. ",        //DAN 12.04.2025
         "s1-09.          ", //"��������2 ���.  ", // "�� ���� If!     ",        //DAN 12.04.2025
         "���� ���.������",
         "���� ���.������",

         "�������.���1.   ", // "��� �������� Id.",
         "�������.���R.   ", // "��� ��������. If",
         "s1-14.          ", //"��������1 ����. ", // "��������'Id2'.  ",        //DAN 12.04.2025
         "s1-15.          ", //"��������2 ����. ", // "��������'Id2-cp'",        //DAN 12.04.2025

         "������.�� � ���.", // "��������'Id'.   ",
         "s1-17.          ", //"��� c���� c ���1", // "��������'Id-��'.",        //DAN 12.04.2025
         "s1-18.          ", //"��� c���� c ���R", // "��������'Ud'.   ",        //DAN 12.04.2025
         "KV1-��.���� � ز", //"��� �� ������.  ", // "���������� ���  ",        //DAN 12.04.2025

         "���� �����-�����",
         "���� ��.������� ",
         "���1 �� � �����", // "��� ������.���1.", // "��� ������ ����.",
         "���R �� � �����", // "��� ������.���R.", // "��� ������ ����.",

         "���� ���. ���  ",
         "���� ���. ���. ",
         "�����.���� ���. ",
         "���� �����-��  ",

         "��������.����.��", // "���.��������� �T",
         "�������� CAN.   ",
         "������� � �����.",
         "s1-31.          ",  //"��������.���.��.", //"��� �����-���.�K"                                 // DAN 12.04.2025
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
         "��.����.��� ��.", // ����� �������
         "��.����.��� ز.", // ����� �������
         "����.���.'='��� ", // "����.Q2-2AK.    ",

         "�����.��.ز-1SQ.", //"�����.����.-1SQ.",
         "���� U���.-1AM.", // "�����.����.-1AM.",
         "���-1RV.        ",
         "���� ���.���.��",

         "T���. U���-���c", // "T����'TC2'-����.",
         "T���. U���-��.", // "T����'TC2'-���. ",
         "���.���.���� �� ", //"I��C-����-��3.  ",
         "���.���.���� ز ", //"I����-����      ",

         "�������-2BK.   ",
         "�������� ��  �� ",
         "�������� ��  ز ",
         "�����.����.-SF3.",


         "Id1-����.       ",
         "Id2-����.       ",
         "����� ����     ", //"If2-���.        ",                         //DAN 12.04.2025
         "�1 ��� �3 ����  ", //"�����������-2GL.",                         //DAN 12.04.2025

         "��������������c", // "������ ������-�a",
         "���.���.���-KP1.",  //"���.����.���-KP1",
         "���.���.���-KP2",
         "����� ���������",  //"��������.������.",

         "�������.������.",
         "���.������� ��. ",
         "�1 �������      ",  //"�������.��.     ",  //"����.����.���1. ", //DAN 12.04.2025
         "�3 ������.      ",  //"SF5-�����.������",  //"����.����.���R. ", //DAN 12.04.2025

         "����.����. ��  ",
         "����.����. ز  ", //"����� ����.����.",
         "���.�������-KF2 ",
#ifdef bi_KF_VKask2
         "���.�������-KF1 "
#else
         "���.���.���-KF1 "   //"�������.�������." //"�������.�V1-AV2.",
#endif
       },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_PreduprMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_PreduprMsg2[32]  =
       {
         "�������-PT.    ",
         "����������  ��  ",
         "����������  ز  ",
         "������� �����.  ",

         "SF2-������ ز,��", //"SF2-������.��.  ",  //DAN 12.04.2025
         "SF3-�����������.",
         "���������.-2BV  ", //"SF4-������.��.  ",  //DAN 12.04.2025
         "����� ��.       ",

         "���.���.���� �� ", //"I��C-����-��3.  ",
         "���.���.���� ز ", //"I����-����      ",
         "��.���.BK6 ��   ",
         "��.���.BK5 ��   ",

         "��.���.��4 ��   ",
         "��.���.BK3 ��   ",
         "��.���.BK2 ��   ",
         "��.���.BK1 ��   ",

         "��.����.���. ��", // ����������� � ����. �� ����������.
         "��.���.BK6 ز   ",
         "��.���.BK5 ز   ",
         "��.���.��4 ز   ",

         "��.���.BK3 ز   ",
         "��.���.BK2 ز   ",
         "��.���.BK1 ز   ",
         "��.����.���. ز", // -//-

         "SFV1-����.ز, ��",  //DAN 12.04.2025
         "p2-25.          ",
         "����.���.���.V11", //"����.���.V11(24)",
         "����.���.���.V12", //"����.���.V12(25)",

         "����.���.���.V13", //"����.���.V13(26)",
         "����.���.���.V14", //"����.���.V14(21)",
         "����.���.���.V15", //"����.���.V15(22)",
         "����.���.���.V16"  //"����.���.V16(23)"
     },

     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_ServiceMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
   //const char *const Tabl_ServiceMsg2[32]  =
       {
         "s2-00.          ",  //"ST1-������.�/�. ",  //"DP: Wait Param  ",                      // DAN 12.04.2025
         "s2-01.          ",  //"SM1-������.�/�. ",  //"DP: Wait Config ",                      // DAN 12.04.2025
         "s2-02.          ",  //"ST2-������.�/�. ",  //"DP: Data Exchang",                      // DAN 12.04.2025
         "s2-03.          ",  //"SM2-������.�/�. ",  //"DP: Baud Search ",                      // DAN 12.04.2025

         "s2-04.          ",  //"ST1-������� ���.",  //"DP: Baud Control",                      // DAN 12.04.2025
         "s2-05.          ",  //"SM1-������� ���.",  //"DP: DP Control  ",                      // DAN 12.04.2025
         "s2-06.          ",  //"ST2-������� ���.",  //"DP: ����.�� ���.",                      // DAN 12.04.2025
         "s2-07.          ",  //"SM2-������� ���.",  //"DP: ���� - 12�� ",                      // DAN 12.04.2025

         "DP: ���� - 6��  ",
         "DP: ���� - 3��  ",
         "DP: ���� - 1,5��",
         "DP: ���� - 500��",

         "DP: ���� - 187��",
         "DP: ���� - 93�� ",
         "DP: ���� - 45�� ",
         "DP: ���� - 19�� ",

         "DP: ���� - 9,6��",
         "DP: ���.������. ",
         "���2 �� � �����",  //"��� ������.���2.", //"���. V1 �� ����.",
         "�����.����������",  //"���. V2 �� ����.",

         "��������.���2.  ",  //"���. V3 �� ����.",
         "�����-����� ��� ",  //"���. V4 �� ����.",
         "�����-��������� ",  //"���. V5 �� ����.",
         "����� ��������  ",  //"���. V6 �� ����.",

         "���� ��. � ��2.",
         "���� ��� ���.  ",
         "�����.�/� QK1.  ",
         "������� Modbus  ",

         "����� ���.���. ",
         "���.��� ������. ",
         "���� ��'���� ���",  //"��� c���� c ���2",  // 12.04.2025
         "���� �����. ���"
     }

#ifdef _TRETIY_REG
     /*   ������� �� 32-� ��������� ��������������� �������� ����� ��������
      * "Reg_AvarMsg2". ������� ��������� � ������� ������������� ������
      * ��������, 0-�� ���� ��������, � ���������, 31-� ��������� � �������
      * ������������� ������ ��������, 31-�� ���� ��������.
      */
  //const char *const Tabl_AvarMsg2[32]  =
      ,{
         "��6 ��          ", // ������.
         "��5 ��          ", // ������.
         "��4 ��          ", // ������.
         "��3 ��          ", // ������.

         "��2 ��          ", // ������.
         "��1 ��          ", // ������.
         "��6 ز          ", // ������.
         "��5 ز          ", // ������.

         "��4 ز          ", // ������.
         "��3 ز          ", // ������.
         "��2 ز          ", // ������.
         "��1 ز          ", // ������.

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
         "��6 ��          ", // ������.
         "��5 ��          ", // ������.
         "��4 ��          ", // ������.
         "��3 ��          ", // ������.

         "��2 ��          ", // ������.
         "��1 ��          ", // ������.
         "��6 ز          ", // ������.
         "��5 ز          ", // ������.

         "��4 ز          ", // ������.
         "��3 ز          ", // ������.
         "��2 ز          ", // ������.
         "��1 ز          ", // ������.

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
