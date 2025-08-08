
// ������������ ����: �������� ��������� ������� .
//------------------------------------------------------------------------------

#ifndef msg_tabl_h
#define msg_tabl_h

// � MSG.H _Device_Name_ ����� ������������� :
#define _Device_Name_ "    -���5-�-    "

//----------- �8 - ������� ������� ������� ---------------

#define _KTE_A8_Cfg1 \
    { "K�����.1    " , (w*)&_r.Cfg.all, 15 ,                                   \
                               { "������� ���.",                               \
                                 "�������.���.",                               \
                                 "�����-���.  ",                               \
                                 "�����-���.�K",                               \
                                 "����.��-��  ",                               \
                                 "��������.��p",                               \
                                 "���.����.��p",                               \
                                 "���         ",                               \
                                 "N#-�������� ",                               \
                                 "�������.����",                               \
                                 "��-�������  ",                               \
                                 "If-������.  ",                               \
                                 "���������   ",                               \
                                 "�������.��  ",                               \
                                 "�� ��������." },                             \
      { _cfg_Shtat_reg  , _cfg_Obj_prg    , _cfg_CAN_reg  , _cfg_CAN_QK   ,    \
        _cfg_RT_Anastr  , _cfg_Dve_Zony   , _cfg_MT       , _cfg_DZV      ,    \
        _cfg_Control_ZSk, _cfg_Vrasch_Dvig, _cfg_Ostanov  , _cfg_Iv_Econom,    \
        _cfg_Kontaktor  , _cfg_Fzapoln    , _cfg_Ne_Revers },                  \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Cfg2 \
    { "K�����.2    " , (w*)&_r.Cfg2.all, 13 ,                                      \
                               { "���         ",                                   \
                                 "��� ������. ",                                   \
                                 "��� (����)  ",                                   \
                                 "If-������.N#",                                   \
                                 "������ ���� ",                                   \
                                 "�������.��� ",                                   \
                                 "���.�������.",                                   \
                                 "2�� � 12���.",                                   \
                                 "���.�.��1-2 ",                                   \
                                 "��-������   ",                                   \
                                 "���-�������.",                                   \
                                 "�����.��.��p",                                   \
                                 "1VR         " },                                 \
      { _cfg2_RDN        , _cfg2_RDN_Decrease, _cfg2_RRS        , _cfg2_Iv_Econom2,\
        _cfg2_Rev_Pola   , _cfg2_FzapolnV    , _cfg2_SIFU_Syn2  , _cfg2_RT2_SIFU2, \
        _cfg2_RT1_RT2sovm, _cfg2_MT_Podyom   , _cfg2_DZV_Predupr, _cfg2_ProboyTir, \
        _cfg2_1VR },                                                               \
       (w*)&_Msk ,2                                                                \
    }

//-----
#define _KTE_A8_CfgRVId \
    { "K�����.PB-Id" , (w*)&_r.CfgRVId.all, 3 ,                                \
                               { "��-�������  ",                               \
                                 "GL1-��-��   ",                               \
                                 "GL2-��-��   " },                             \
      { _cfgRVId_Vkl, _cfgRVId_GL1, _cfgRVId_GL2 },                            \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Prg \
    { "���������   " , (w*)&Prg.all,  7 ,                                      \
                               { "������e     ",                               \
                                 "��          ",                               \
                                 "��          ",                               \
                                 "��          ",                               \
                                 "����� �����.",                               \
                                 "���� ������.",                               \
                                 "����        " },                             \
      { _ZadSkor, _RP, _RegSk, _RegTok, _Cikl, _Blok_upr, _Sled },             \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Isp \
    { "������.��   " , (w*)&Isp.all,  2 ,                                      \
                               { "������.���� ",                               \
                                 "������.���� "},                              \
      { 0x0400 , 0x0800 },                                                     \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Sk \
    { "������ ����." , (w*)&_r.Sk_str.all,  8 ,                                \
                               { "N:���       ",                               \
                                 "N:��        ",                               \
                                 "N:���       ",                               \
                                 "N:������    ",                               \
                                 "N:��C 2 ���a",                               \
                                 "���:���/����",                               \
                                 "��C����:���.",                               \
                                 "��C����:12�."},                              \
      { _sk_EDS       ,  _sk_TG       , _sk_PDF      , _sk_filtr ,             \
        _sk_EdsIIzona ,  _sk_EDS_Appar, _sk_FiltrEds , _sk_KompUd_12p },       \
       (w*)&_Msk ,2                                                            \
    }

//-----
#ifdef _CM3_
   #ifdef  _SIFU2_
     #define _KTE_A8_Pi1 \
      { "Pi1-������. " , &_r.Pi1_Normal,  8 ,     /* CM3 */                    \
                               {                                               \
                                 "������0/INT7",                               \
                                 "net    /INT2",                               \
                                 "����1  /INT5",                               \
                                 "����1  /INT6",                               \
                                 "����2  /INT4",                               \
                                 "����2  /INT3",                               \
                                 "1�/Ittm/INT0",                               \
                                 "2�/1RV /INT1"                                \
                               },                                              \
        { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },                 \
         (w*)&_Msk ,1                                                          \
      }
   #else
     #define _KTE_A8_Pi1 \
      { "Pi1-������. " , &_r.Pi1_Normal,  8 ,     /* CM3 */                    \
                               {                                               \
                                 "������0/INT7",                               \
                                 "net    /INT2",                               \
                                 "����   /INT5",                               \
                                 "����   /INT6",                               \
                                 "KF     /INT4",                               \
                                 "KFT    /INT3",                               \
                                 "1�/Ittm/INT0",                               \
                                 "2�/1RV /INT1"                                \
                               },                                              \
        { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },                 \
         (w*)&_Msk ,1                                                          \
      }
   #endif
#else //_CM3_
     #define _KTE_A8_Pi1 \
      { "Pi1-������. " , &_r.Pi1_Normal,  8 ,     /* F16 , F16K */             \
                               {                                               \
                                 "������0-P22 ", /*P22*/                       \
                                 "������1-P23 ", /*P23*/                       \
                                 "KFV         ", /*P24*/                       \
                                 "��DC-2B/1RV ", /*P25*/                       \
                                 "����        ", /*P26*/                       \
                                 "����        ", /*P27*/                       \
                                 "KF          ", /*P86*/                       \
                                 "��AC-1B/Ittm"  /*P92*/                       \
                               },                                              \
      { 0x01 , 0x02 , 0x04, 0x08, 0x10 , 0x20 , 0x40, 0x80 },                  \
      {(w*)&_Msk},1                                                            \
    }
#endif //_CM3_

//-----
#ifdef _Pi2_
 #define _KTE_A8_Pi2 \
    { "Pi2-������. " , &_r.Pi2_Normal,  8 ,                                    \
                               {                                               \
                                 "KF          ", /*PDRR_PR6 */                 \
                                 "KFT         ", /*PDRS_PDS6*/                 \
                                 "BK2         ", /*PDRQ_PDQ2*/                 \
                                 "BK1         ", /*PDRQ_PDQ3*/                 \
                                 "������4     ",                               \
                                 "������5     ",                               \
                                 "������6     ",                               \
                                 "������7     "                                \
                               },                                              \
      { 0x01 , 0x02 , 0x04, 0x08, 0x10 , 0x20 , 0x40, 0x80 },                  \
      {(w*)&_Msk},1                                                            \
    }
#endif

//-----
#define _KTE_A8_cCfgR \
    { "�����:cCfgR " , &canr.CfgReg.all  , 16 ,                                \
                               { "N#          ",                               \
                                 "Id#         ",                               \
                                 "reserved2   ",                               \
                                 "L#          ",                               \
                                 "Most        ",                               \
                                 "��          ",                               \
                                 "F#          ",                               \
                                 "MT          ",                               \
                                                                               \
                                 "Start       ",                               \
                                 "Predupr     ",                               \
                                 "Avar        ",                               \
                                 "DistSbros   ",                               \
                                 "S#          ",                               \
                                 "reserved13  ",                               \
                                 "reserved14  ",                               \
                                 "Connect     "                                \
                                 },                                            \
      { _A8_creg_mask },                                                       \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_cStsR \
    { "�����:cStsR " , &canr.StatReg.all  , 16 ,                               \
                               { "Gotovn      ",                               \
                                 "Predupr     ",                               \
                                 "Avar        ",                               \
                                 "KTE_Rezerv  ",                               \
                                 "StateQK     ",                               \
                                 "GotovQK     ",                               \
                                 "Most        ",                               \
                                 "Connect     ",                               \
                                                                               \
                                 "MT          ",                               \
                                 "rezerv9     ",                               \
                                 "rezerv10    ",                               \
                                 "rezerv11    ",                               \
                                 "rezerv12    ",                               \
                                 "rezerv13    ",                               \
                                 "rezerv14    ",                               \
                                 "rezerv15    "                                \
                                 },                                            \
      { _A8_sreg_mask },                                                       \
       (w*)&_Msk ,2                                                            \
    }

//---------------------------------------- ���� CAN 0 ----------------------------------------
// ��� ���������� ������ �������� CAN (��� �������� == 0) �������� ����������� ������ 100 ��� .
#ifdef _CANOPEN                            // CAN0-open :
#define _KTE_A8_CAN0cfg \
    { "CAN0-config   " , &can_setting( _CAN0_Port ).config.all, 5 ,                          \
                               {                                                             \
                                 "���.CAN     " ,                                            \
                                 "���.CANopen " ,                                            \
                                 "125���-500� " ,                                            \
                                 "250���-250� " ,                                            \
                                 "1���  - 25� " },                                           \
      { _can_cfg_vkl,_can_cfg_mcovkl, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M },  \
       (w*)&_Msk ,1                                                                          \
    }
#else
#define _KTE_A8_CAN0cfg \
    { "CAN0-config   " , &can_setting( _CAN0_Port ).config.all, 5 ,                          \
                               { "���.CAN     " ,                                            \
                                 "CAN-������  " ,                                            \
                                 "125���-500� " ,                                            \
                                 "250���-250� " ,                                            \
                                 "1���  - 25� " },                                           \
      { _can_cfg_vkl, _can_cfg_master, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M }, \
       (w*)&_Msk ,1                                                                          \
    }
#endif

//---------------------------------------- ���� CAN 1 ----------------------------------------
// ��� ���������� ������ �������� CAN (��� �������� == 0) �������� ����������� ������ 100 ��� .
#define _KTE_A8_CAN1cfg \
    { "CAN1-config   " , &can_setting( _CAN1_Port ).config.all, 5 ,                          \
                               { "���.CAN     " ,                                            \
                                 "CAN-������  " ,                                            \
                                 "125���-500� " ,                                            \
                                 "250���-250� " ,                                            \
                                 "1���  - 25� " },                                           \
      { _can_cfg_vkl, _can_cfg_master, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M }, \
       (w*)&_Msk ,1                                                                          \
    }

//---------------------------------------- ���� CAN 2 ----------------------------------------
// ��� ���������� ������ �������� CAN (��� �������� == 0) �������� ����������� ������ 100 ��� .
#ifdef _CAN2_Port
#define _KTE_A8_CAN2cfg \
    { "CAN2-config   " , &can_setting( _CAN2_Port ).config.all, 5 ,                          \
                               { "���.CAN     " ,                                            \
                                 "CAN-������  " ,                                            \
                                 "125���-500� " ,                                            \
                                 "250���-250� " ,                                            \
                                 "1���  - 25� " },                                           \
      { _can_cfg_vkl, _can_cfg_master, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M }, \
       (w*)&_Msk ,1                                                                          \
    }
#endif
//---------------------------------------- Modbus RTU ----------------------------------------
#ifdef _CM3_
#define _KTE_A8_MBcfg \
    { "MBRTU-config  " , &_r.rs485.config.all, 7,                                            \
                               { "���.Modbus  " ,                                            \
                                 "19200 ���/� " ,                                            \
                                 "38400 ���/� " ,                                            \
                                 "57600 ���/� " ,                                            \
                                 "���.����.   " ,                                            \
                                 "��������    " ,                                            \
                                 "1 ����-���  " },                                           \
      { _cfg_rs_vkl, _cfg_rs_b19200, _cfg_rs_b38400, _cfg_rs_b57600,                         \
        _cfg_rs_parityon,  _cfg_rs_parity, _cfg_rs_stopbit },                                \
       (w*)&_Msk ,1                                                                          \
    }
#endif
//--------------------------------------------------------------------------------------------


//----------------------------------------
#ifdef _MAIN_INCLUDE
//----------------------------------------

const word  _ind_Nom  = 1 ;
const word  _ind_100  = 100 ;
const word  _ind_1000 = 1000 ;
const word  _Msk  = 0xffff;

//----------- �7 - ������� ������ ������� ----------------

_x_far const struct STB       stb_avar[ ] =
  {
    { "N-����        ", &_r.N_Max             ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "dN-���.����.  ", &_r.dN_Max            ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "E-����        ", &_r.E_Max             ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom(0.01) , 0xff, "��� " , _form(1,2,2,2) },
    { "T-���.���.����", &_r.T_Circuit         ,_fSec( 0.0 )     ,_fSec( 12.0 )     ,_fSec(1.0)    ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "��� " , _form(1,3,2,2) },
    { "Id-���        ", &_r.Id_Min            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
    { "Id-����       ", &_r.Id_Max            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
#ifdef   Id_sum_ach
    { "Id-���-����   ", &_or.Id_sum_max       ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
#endif
    { "dt-Id-����    ", &_r.time_Id_max       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "�c"   , _form(1,3,1,1) }, // !!! ��� �� "word" , � "byte" , �� 255 ������� .
    { "Id-���-������ ", &_r.Id_tst_proboy     ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
    { "If-���        ", &_r.Iv_avar_Min       ,_Iv_nom( 0.0 )   ,_Iv_nom( 2.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
    { "dt-If-���     ", &_r.time_Iv_min       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "�c"   , _form(1,3,1,1) },
#ifdef _Vozb_KTE
    { "If-����       ", &_r.Iv_avar_Max       ,_Iv_nom( 0.0 )   ,_Iv_nom( 3.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
    { "dt-If-����    ", &_r.time_Iv_max       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "�c"   , _form(1,3,1,1) },
#endif
#if   defined( bi_BV1 ) || defined( bo_Vkl_Vent )
  #ifndef  _STOLB_1TIR
   #ifdef bi_PT   // ��� ��������� ��������� ������������ �� ��������� :
    { "T-����.����.  ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(3000.0 )     ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "��� " , _form(1,2,2,2) },
   #else
    { "T-����������  ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(600.0 )      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "��� " , _form(1,2,2,2) },
   #endif
  #else
    { "T-����������  ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(3.0 )        ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,2,2,2) },
  #endif
#endif
#ifdef bo_VklVent // ��� ��������� ��������� ������������ �� ���� ����� :
    { "Id-���-������.", &_or.Id_Vkl_Vent      ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
    { "T-����-������.", &_or.T_Otkl_Vent      ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "��� " , _form(1,3,1,2) },
#endif
#ifdef _Dat_Temp_Max // ��� ��������� ����������� ��������� ����������� ������� ���������� � ������ ������� ����� :
    { "T-��������-��.", &_or.T_Pr             , 0.*10           , 300*10           , 10           ,(w*)&_ind_Nom, 10             , 0xff, "��"   , _form(0,3,1,2) },
    { "T-��������-��.", &_or.T_Av             , 0.*10           , 300*10           , 10           ,(w*)&_ind_Nom, 10             , 0xff, "��"   , _form(0,3,1,2) },
#endif
    { "T-����.���.   ", &_r.Time_do_OtklImp   ,_Sec( 0.1 )      ,_Sec( 9.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.1)      , 0xff, "��� " , _form(1,2,2,2) },
#ifdef bi_Vent_Dvig
    { "T-������.����.", &_r.Time_otkl_VentDvig,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "��� " , _form(1,3,1,2) },
#endif
#ifdef bi_MasloSmazka
    { "T-����.����.  ", &_r.Time_MasloSmazka  ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "��� " , _form(1,3,1,2) },
#endif
#ifdef bi_Smazka_Podsh
    { "T-����.����.  ", &_r.Time_Smazka_Podsh ,_Sec( 0.0 )      , (sw)0xFFFF       ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "��� " , _form(1,3,1,2) },
#endif
    { "E-�������     ", &_r.Stoyanka_Eds      ,_EDS_nom( +0.0 ) ,_EDS_nom( +5.0 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom(0.01) , 0xff, "��� " , _form(1,2,2,2) },
    { "Id-������a    ", &_r.Stoyanka_Tok      ,_Id_nom( 0.0 )   ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.10 ) , 0xff, "��� " , _form(1,2,1,2) },
    { "T-����.������a", &_r.Stoyanka_Time     ,_Sec( 0.0 )      ,_Sec( 120.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "��� " , _form(1,2,0,2) },
    { "T-����.������a", &_r.Stoyanka_Time_Predupr ,_Sec( 0.0 )  ,_Sec( 120.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "��� " , _form(1,2,0,2) },
    { "Id-����-����  ", &_r.Tok_Otkl_Kontaktor,_Id_nom( 0.0 )   ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.10 ), 0xff, "��� " , _form(1,2,2,2) },
    { "U����-����    ", &_r.Uinsul_max        , 0               , (w)(9.9*(_AD_MAX/5.0))  ,(w)(1.0*(_AD_MAX/5.0)),(w*)&_ind_Nom,(w)(0.01*(_AD_MAX/5.0)),0xff," B"  , _form(1,2,2,2) },
#ifdef Insul_D_ach
  #ifndef  Uf_ach
    { "Uf-������.���.", &_or.Uf_econom        ,_Uf_nom( 0.00 )  ,_Uf_nom( +2.00 )  , _Uf_Nom      ,(w*)&_ind_Nom, _Uf_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
  #endif
#endif
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
    { "dIs-���.�����.", &_or.dIs_ControlBegin ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
    { "Is-���������. ", &_or.Is_tokoraspred   ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,2,2,2) },
#endif
//------------
 #ifndef _CM3_
//------------
#ifdef _SIFU2_
  #if   defined( _1P_ach ) || defined( _2P_ach )
    { "1�_2P-����    ", &_r._1P_2P_max        ,(sw)(-9.9*(_AD_MAX/5.0)), 9.9*(_AD_MAX/5.0)  ,1.0*(_AD_MAX/5.0),(w*)&_ind_Nom, 0.1*(_AD_MAX/5.0),0xff," B"  , _form(0,2,2,2) },
    { "1�_2P-���     ", &_r._1P_2P_min        ,(sw)(-9.9*(_AD_MAX/5.0)), 9.9*(_AD_MAX/5.0)  ,1.0*(_AD_MAX/5.0),(w*)&_ind_Nom, 0.1*(_AD_MAX/5.0),0xff," B"  , _form(0,2,2,2) },
  #endif
#endif
#ifdef PUM_ach
    { "���������-����", &_r.PUM_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "���������-��� ", &_r.PUM_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef P12_ach
    { "P12-����      ", &_r.P12_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "P12-���       ", &_r.P12_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef N12_ach
    { "N12-����      ", &_r.N12_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "N12-���       ", &_r.N12_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
    { "1P24-����     ", &_r.P24_max           ,-102*9.99        , 102*9.99         , 102          ,(w*)&_ind_Nom,  1              ,0xff, " B" , _form(0,2,2,2) },
    { "1P24-���      ", &_r.P24_min           ,-102*9.99        , 102*9.99         , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) }
//------------
 #else
//------------
#ifdef _SIFU2_
  #if   defined( _1P_ach ) || defined( _2P_ach )
    { "1�_2P-����    ", &_r._1P_2P_max,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4           , 0xff, " B" , _form(0,2,2,2) },
    { "1�_2P-���     ", &_r._1P_2P_min,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4           , 0xff, " B" , _form(0,2,2,2) },
  #endif
#endif
#ifdef PUM_ach
    { "���������-����", &_r.PUM_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "���������-��� ", &_r.PUM_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef P12_ach
    { "P12-����      ", &_r.P12_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "P12-���       ", &_r.P12_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef N12_ach
    { "N12-����      ", &_r.N12_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "N12-���       ", &_r.N12_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
    { "1P24-����     ", &_r.P24_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "1P24-���      ", &_r.P24_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) }
//------------
 #endif
//------------
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_RS[ ] =
  {
#ifdef  _REG_POL
    { "�����-dS-��   ", &_r.DeltaDeadZone     , 0               ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.5 )   , 0xff, "�� "  , _form(1,3,2,2) },
    { "K�-dS-��      ", &_r.Kp_dP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  64            , 0xff, "��"   , _form(1,3,2,2) },
    { "K�-��         ", &_r.Kp_RP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  16            , 0xff, "��"   , _form(1,3,2,2) },
    { "T�-��         ", &_r.Ki_RP             , 0               , 999              , 1            ,(w*)&_ind_Nom,  2             , 0xff, "�c"   , _form(1,3,0,2) },
#endif
    { "N#-����'+'    ", &_r.Z_SkMax_P         ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "N#-����'-'    ", &_r.Z_SkMax_M         ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "N-�������     ", &_r.Ostanov_skor      ,_Skor_nom( +0.0 ),_Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1<<_Skor_Shift , 0xff, "%"    , _form(1,3,2,2) },
    { "T-�������     ", &_r.Ostanov_time      ,_Sec( 0.1 )      ,_Sec( 9.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, 1              , 0xff, "��� " , _form(1,1,2,2) },
#ifndef  _ZI_30min
  #ifdef _ZI_4TEMPA
    { "������-����'+'", &_r.T_ZISkorP_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"    , _form(1,3,2,2) },
    { "������-����'-'", &_r.T_ZISkorP_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"    , _form(1,3,2,2) },
    { "������-����'+'", &_r.T_ZISkorM_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"    , _form(1,3,2,2) },
    { "������-����'-'", &_r.T_ZISkorM_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"    , _form(1,3,2,2) },
   #ifdef bi_Reviz
    { "������-��'���'", &_or.T_ZISkor_Reviz   ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"    , _form(1,3,2,2) },
   #endif
   #ifdef bi_Fors_Temp
    { "������-��'���'", &_r.T_ZISkorP_Fors    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"    , _form(1,3,2,2) },
   #endif
  #else
    { "������-��'+'  ", &_r.T_ZISkorP_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,3,2,2) },
    { "������-��'-'  ", &_r.T_ZISkorP_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,3,2,2) },
   #ifdef bi_Reviz
    { "������-��'���'", &_or.T_ZISkor_Reviz   ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,3,2,2) },
   #endif
   #ifdef bi_Fors_Temp
    { "������-��'���'", &_r.T_ZISkorP_Fors    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,3,2,2) },
   #endif
  #endif
#else
    { "������-��'+'  ", &_r.T_ZISkorP_Razg    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,2,1,2) },
    { "������-��'-'  ", &_r.T_ZISkorP_Torm    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,2,1,2) },
 #ifdef bi_Fors_Temp
    { "������-��'���'", &_r.T_ZISkorP_Fors    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,2,1,2) },
 #endif
#endif
    { "�e����-��'s'  ", &_r.T_ZISkor_Parab,       _Sec( 0.0 ),       _Sec( 20.0 ),     _Sec( 1.0 ),(w*)&_ind_Nom, _Sec( 0.1 )    , 0xff, "��� " , _form(1,3,2,2) },
    { "�e����-��-dN  ", &_r.T_ZISkor_Parab_delta, _Skor_nom( 0.0 ),  _Skor_nom( 1.0 ), _Skor_Nom  ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,3,2,2) },
#ifdef  TGx_ach
    { "��x8-�����    ", &_r.TGx8_porog        ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_nom(0.01),(w*)&_ind_Nom, 4             , 0xff, "%"    , _form(1,3,2,2) },
#endif
    { "�����-��      ", &_r.porog_fil         ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,3,2,2) },
    { "K-��          ", &_r.K_fil_sk          , 2               , 1000             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,2) },
    { "�����-����    ", &_r.Porog_FE          , 0               , 1600             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,2) },
    { "K-����        ", &_r.K_FE              , 2               , 1000             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,2) },
#ifdef bi_RS_P
    { "K�-�C (��-���)", &_r.KRSP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
#else
    { "K�-�C         ", &_r.KRSP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
#endif
    { "T�-�C         ", &_r.KRSI              , 0               , 2000             , 1            ,(w*)&_ind_Nom,  2             , 0xff, "�c"   , _form(1,4,0,2) },
#ifdef bi_RS_P
    { "K�-�C (�-���) ", &_r.KRSP_for_P        , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
    { "���� �/�� ����", &_r.Adapt_temp        ,_Id_nom( 0.0 )   ,_Id_nom( 20.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.05 ), 0xff, "��� " , _form(1,2,2,2) },
#endif
    { "K���-�C       ", &_r.KRSPIP            , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
    { "K�-�C-2�.     ", &_r.KRSP_II_Z         , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
    { "T�-�C-2�.     ", &_r.KRSI_II_Z         , 0               , 999              , 1            ,(w*)&_ind_Nom,  2             , 0xff, "�c"   , _form(1,3,0,2) },
  //{ "K���-�C-2�.   ", &_r.KRSPIP_II_Z       , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��" , _form(1,3,2,2) },
#ifdef bi_Reviz
    { "K�-�C-������� ", &_or.KRSP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
    { "T�-�C-������� ", &_or.KRSI             , 0               , 2000             , 1            ,(w*)&_ind_Nom,  2             , 0xff, "�c"   , _form(1,4,0,2) },
    { "K���-�C-����� ", &_or.KRSPIP           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "��"   , _form(1,3,2,2) },
#endif
    { "N#-�������    ", &Z_Skor               ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_RT[ ] =
  {
  //{ "Id#-����      ", &_r.IZMAX             ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "���", 2 },
    { "Id#-����1'+'  ", &_r.OuRSMaxMost1      ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(0,2,2,2) },
    { "Id#-����1'-'  ", &_r.OuRSMaxMost2      ,_Id_nom(-3.5 )   ,_Id_nom( 0.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(0,2,2,2) },
    { "Id#-����2'+'  ", &_r.OuRSMax2Most1     ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(0,2,2,2) },
    { "Id#-����2'-'  ", &_r.OuRSMax2Most2     ,_Id_nom(-3.5 )   ,_Id_nom( 0.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(0,2,2,2) },
    { "Id-��-���p    ", &_r.INN0              ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
#ifdef  _SIFU2_
    { "Id-��-���p-�� ", &_or.INN0_dvig        ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom,  1*_K_diskr    , 0xff, "��� " , _form(1,2,3,2) },
    { "�����-INN     ", &_or.KINN             , 0x0050          , 0x0125           , 0x0100       ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,2,3,2) },
#endif
    { "������-��'+'  ", &_r.Temp_RT_P         ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "��� " , _form(1,4,1,2) },
    { "������-��'-'  ", &_r.Temp_RT_M         ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "��� " , _form(1,4,1,2) },
    { "'K�-��        ", &_r_KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "��"   , _form(1,3,2,2) },
    { "'K�-��-AH     ", &an_KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "��"   , _form(1,3,2,2) },
    { "K�-��-���     ", &_r.KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  4             , 0xff, "��"   , _form(1,3,2,2) },
    { "'��-�����p    ", &_r_KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "'��-�����p-AH ", &an_KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "��-�����p-��� ", &_r.KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  1             , 0xff, "�c"   , _form(1,3,2,2) },
    { "'��-�����p    ", &_r_KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "'��-�����p-AH ", &an_KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "��-�����p-��� ", &_r.KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "�c"   , _form(1,3,2,2) },
    { "K-��-���      ", &_r.KRTDI             , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,2) },
#ifdef  _SIFU2_
    { "Id-��-���p-��2", &_or.INN0_2_          ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "'K�-��2       ", &_or_KRTP_2_          , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "��"   , _form(1,3,2,2) },
    { "'K�-��2-AH    ", &an_KRTP_2_           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "��"   , _form(1,3,2,2) },
    { "K�-��2-���    ", &_or.KRTP_2_          , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  4             , 0xff, "��"   , _form(1,3,2,2) },
    { "'��-��2���p   ", &_or_KRTPRI_2_        , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "'��-��2���p-AH", &an_KRTPRI_2_         , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "��-��2���p-���", &_or.KRTPRI_2_        , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  1             , 0xff, "�c"   , _form(1,3,2,2) },
    { "'��-��2���p   ", &_or_KRTNI_2_         , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "'��-��2���p-AH", &an_KRTNI_2_          , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "�c"   , _form(1,3,2,2) },
    { "��-��2���p-���", &_or.KRTNI_2_         , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "�c"   , _form(1,3,2,2) },
#endif
    { "��-���-����   ", &_r.RTMAX             ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,3,0,2) },
    { "��-���-���    ", &_r.RTMIN             ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,3,0,2) },
#ifdef _DST
    { "T-���������   ", &_r.T_meh             ,_Id_nom( 0.0 )   , _Id_nom( 30.0 )  ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "�-�-����.���� ", &_r.T_flt_Stat        ,_fSec( 0.0)      , _fSec( 10 )      ,_fSec(1)      ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "��� " , _form(1,2,2,2) },
    { "����.����.���a", &_r.puls_Istat        , 0               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
#endif
    { "Id#-�������   ", &OuRegS_dop_kod       ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(0,2,2,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_Tormoz[ ] =
  {
    { "Id-����.��    ", &_r.Id_Otkl_MT        ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "T-������.��   ", &_r.Time_MT           ,_Sec( 0.0 )      ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,2,2,2) },
    { "T���-�����.�� ", &_r.Time_MT_Err       ,_Sec( 0.0 )      ,_Sec( 10.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,2,2,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

#if defined( _RDN ) || defined( _RRS ) || defined( _BUKSOVKA )
_x_far const struct STB       stb_Procat[ ] =
  {
#ifdef _RDN
    { "�����-���     ", &_r.RDN_Dead_Zone     ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "K-���         ", &_r.RDN_Kp            , 0               , (sw)0xA000u      , 0x0100*(_Skor_Nom/_Id_Nom) ,(w*)&_ind_Nom,40, 0xff, "��"   , _form(1,2,2,2) },
    { "dN#-���-����  ", &_r.RDN_Max           ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "T������-���   ", &_r.RDN_Tfiltr        , 0               , 999              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "�c"   , _form(1,3,0,2) }
#endif
#ifdef _RRS
  #ifdef _RDN
    ,
  #endif
    { "N#-�������1   ", &_r.Sk_zahv1          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "N#-�������2   ", &_r.Sk_zahv2          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "I����-������� ", &_r.Porog_Istat       ,_Id_nom( 0.0 )   , _Id_nom( 3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "T-�������     ", &_r.T_zahv            ,_fSec( 0.0 )     , _fSec(2.0 )      ,_fSec(1.0)    ,(w*)&_ind_Nom,  _fSec(0.01)   , 0xff, "��� " , _form(1,2,2,2) },
    { "T-����        ", &_r.T_liga            ,_fSec( 0.0 )     , _fSec(2.0 )      ,_fSec(1.0)    ,(w*)&_ind_Nom,  _fSec(0.01)   , 0xff, "��� " , _form(1,2,2,2) },
    { "K-����        ", &_r.K_liga            , 0               , 1*256            , 256          ,(w*)&_ind_Nom,  3             , 0xff, "��"   , _form(1,3,2,2) }
#endif
#ifdef _BUKSOVKA
  #if defined( _RDN ) || defined( _RRS )
    ,
  #endif
    { "����-Id-�����.", &_r.Id_RDN_off        ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "����-Id-�����.", &_r.Id_RDN_on         ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "����-N-�����. ", &_r.N_RDN_off         ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "����-N-�����. ", &_r.N_RDN_on          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "T-�����.����. ", &_r.Time_Buksov       ,_fSec( 0.0 )     ,_fSec( 12.0 )     ,_fSec(1.0)    ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "��� " , _form(1,3,2,2) },
    { "������� ����. ", &_r.count_Buk_f       , 0               , 15               , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) }
#endif
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

#ifdef _RVId
_x_far const struct STB       stb_RVId[ ] =
  {
    { "�����-��      ", &_r.RVId_Dead_Zone    ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� ", _form(1,2,2,2) },
    { "K�-PB         ", &_r.RVId_Kp           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  1             , 0xff, "��"  , _form(1,3,3,2) },
    { "T�-PB         ", &_r.RVId_Ti           , 0               , 30000            , 1            ,(w*)&_ind_Nom,  1             , 0xff, "�c"  , _form(1,5,0,2) },
    { "��-����       ", &_r.RVId_Max          ,_Iv_nom( +0.0 )  ,_Iv_nom( +2.0 )   ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "��� ", _form(1,2,2,2) },
    { "If#-GL1       ", &_r.Iv_zad_GL1        ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� ", _form(1,3,2,2) },
    { "If#-GL2       ", &_r.Iv_zad_GL2        ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� ", _form(1,3,2,2) }
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_SIFU[ ] =
  {
    { "L#-����       ", &_r.S_Alfa_Max        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,3,0,2) },
    { "L#-���        ", &_r.S_Alfa_Min        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,3,0,2) },
    { "������-L#     ", &_r.S_DeltaAlfa_Max   ,_Grad( 0.0 )     ,_Grad(  25.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,3,0,2) },
    { "L-���������-Id", &_r.S_Alfa_IzmId      ,_Grad( 11.5 )    ,_Grad(  20.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.1 )   , 0xff, "��"   , _form(1,3,2,2) },
    { "L-���������-Ud", &_r.S_Alfa_IzmDoImp   ,_Grad( 1.0 )     ,_Grad(  3.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.1 )   , 0xff, "��"   , _form(1,3,2,2) },
#ifndef  _SIFU2_
    { "'�����.�����:N", &_r.S_FazirovVS       , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ��K"  , _form(1,2,0,1) },
    { "'�����.�����:F", &_r.S_FazirovUgol     ,_Grad( 0.0 )     ,_Grad( 60.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom,  0             , 0xff," ��"   , _form(1,3,0,2) },
#else
    { "'�����.�����:N", &_r.S_FazirovVS       , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ��K"  , _form(1,2,0,1) },
    { "'�����.�����:F", &_r.S_FazirovUgol     ,_Grad( 0.0 )     ,_Grad( 60.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom,  0             , 0xff," ��"   , _form(1,3,0,2) },
    { "'�����.�����:N", &_r.S2.FazirovVS      , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ��K"  , _form(1,2,0,1) },
    { "K�-���-�����. ", &_r.S2.Kp_rvt         , 0               , 3000             , 64           ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,2,2) },
    { "K�-���-�����. ", &_r.S2.Ki_rvt         , 0               , 3000             , 64           ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,2,2) },
    { "���-���-����  ", &_r.S2.RVTmax         , 0               , 5*64             , 64           ,(w*)&_ind_Nom,  16            , 0xff, "��"   , _form(1,2,2,2) },
    { "���-���-Id-�� ", &_or.RVT_INN0         ,_Grad( -5.0 )    ,_Grad( 5.0 )      ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.05 )  , 0xff, "��"   , _form(0,1,3,2) },
#endif
    { "U0-������     ", &_r.RevU0             ,_Grad( 000.0 )   ,_Grad( 180.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,0,2) },
    { "Id-������     ", &_r.RIDRR             ,_Id_nom( 0.0 )   ,_Id_nom( 0.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "��� " , _form(1,2,2,2) },
    { "dt-������     ", &_r.dt_revers         , 0               ,_pSec( 10.0 )     ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "�c"   , _form(1,3,1,2) },
    { "K-K���-Ud     ", &_r.K_Kompen_Ud       , 0               , 100              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,2) },
    { "L#-�������    ", &S.Alfa               ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,2,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_EDS[ ] =
  {
    { "K-���-�       ", &_r.KEDS_R            , 0               , 255              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,1) },
    { "K-���-�       ", &_r.KEDS_P            , 0               , 255              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,1) },
//  24.06.2020 ���������������� �� �������� ��� � ������ ����������� �. ��� ���������� ������ ��.
//  ��� ��������� ���� ������� �� ���� ��������� ������� �� ���� �� ��������.
//  { "K-���-�       ", &_r.KEDS_T            , 0               , 255              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,3,0,1) },
    { "E#���-2�-���� ", &_r.Z_EDS             ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom( 0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "N���-2�-����  ", &_r.Skor2Z            ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "E#-2�-����    ", &_r.Z_II_EDS          ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom( 0.01), 0xff, "��� " , _form(1,2,2,2) },
    { "'N-2�-����    ", &Skor_II_Z            ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom,  0             , 0xff, "��� " , _form(1,2,2,2) },
    { "K�-������     ", &_r.Kp_REDS           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  3             , 0xff, "��"   , _form(1,4,2,2) },
    { "T�-������     ", &_r.Ki_REDS           , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "�c"   , _form(1,3,0,2) },
    { "K�-������-2�. ", &_r.DT_ZISk           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  3             , 0xff, "��"   , _form(1,4,2,2) },
    { "T�-������-2�. ", &_r.Ki_REDS_II_Z      , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "�c"   , _form(1,3,0,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_Vozb[ ] =
  {
    { "If#-����      ", &_r.Iv_zad_Max        ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(1,3,2,2) },
    { "If#-1-������  ", &_r.Iv_zad            ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(1,3,2,2) },
    { "If#-���       ", &_r.Iv_zad_Min        ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(1,3,2,2) },
    { "If#-������.   ", &_r.Iv_econom         ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(1,3,2,2) },
    { "T-������.���� ", &_r.T_econom          ,_Sec( 0.0 )      ,_Sec( 600.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.5)      , 0xff, "��� " , _form(1,3,2,2) },
#ifdef _Rev_Pola
    { "If-���������� ", &_r.Iv_porg_Min       ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(1,3,2,2) },
#endif
#ifdef _Vozb_KTE
    { "If-���������  ", &_r.Iv_null           ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(1,3,2,2) },
    { "K�-���        ", &_r.V_Kp_rt           , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,4,0,2) },
    { "K�-�T�        ", &_r.V_Ki_rt           , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��"   , _form(1,4,0,2) },
    { "'�����.����.:N", &_r.V_FazirovVS       , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ��K"  , _form(1,2,0,1) },
    { "'�����.����.:F", &_r.V_FazirovUgol     ,_Grad( 0.0 )     ,_Grad( 60.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom,  0             , 0xff," ��"   , _form(1,3,0,2) },
    { "T-���.���.���.", &_r.V_Time_do_OtklImp ,_Sec( 0.1 )      ,_Sec( 6.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.1)      , 0xff, "��� " , _form(1,2,2,1) },
    { "Lf#-���       ", &_r.V_Alfa_Min        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,0,2) },
    { "Lf#-����      ", &_r.V_Alfa_Max        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,0,2) },
#endif
    { "If#-�������   ", &_r.Iv_gashen         ,_Iv_nom( -0.1 )  ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(0,3,2,2) },
    { "T-������� ����", &_r.T_gashenie        ,_Sec( 0.0 )      ,_Sec( 600.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.5)      , 0xff, "��� " , _form(1,3,2,2) },
    { "If#-�������   ", &V.Iv_zad             ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "��� " , _form(0,3,2,2) }
#ifdef _Vozb_KTE
   ,{ "Lf#-�������   ", &V.Alfa               ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,2,2) }
#endif
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       peregr[ ] =
  {
    { "Id_I1         ", &_r.I2Tr.I[0]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,3,2,2) },
    { "Id_T1         ", &_r.I2Tr.T[0]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  100           , 0xff, "��� " , _form(1,5,0,2) },
    { "Id_I2         ", &_r.I2Tr.I[1]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,3,2,2) },
    { "Id_T2         ", &_r.I2Tr.T[1]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  10            , 0xff, "��� " , _form(1,5,0,2) },
    { "Id_I3         ", &_r.I2Tr.I[2]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,3,2,2) },
    { "Id_T3         ", &_r.I2Tr.T[2]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,5,0,2) },
    { "Id_I4         ", &_r.I2Tr.I[3]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,3,2,2) },
    { "Id_T4         ", &_r.I2Tr.T[3]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,5,0,2) },
    { "Id_I5         ", &_r.I2Tr.I[4]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,3,2,2) },
    { "Id_T5         ", &_r.I2Tr.T[4]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "��� " , _form(1,5,0,2) },
    { "Id-������.    ", &Id_TeploIntegr       ,_Id_nom( 0.99 )  ,_Id_nom( 1.00 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "��� " , _form(1,3,2,2) },
    { "Id_To         ", &_r.I2Tr.Tohl         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  10            , 0xff, "��� " , _form(1,5,0,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_masht[ ] =
  {
  //{ "Id-�������    ", &_r.Mashtab_Id        , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��" , 2 },
    { "Id-���-����.  ", &_sr.NOM.Id.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A"   , _form(1,5,0,2) },
    { "Id-���-��     ", &_sr.Dat.Id           , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A"   , _form(1,5,0,2) },
    { "'Id-����-��   ", &Mashtab.Id_max       , 0               , _Id_nom( 7.0 )   , _Id_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "��� " , _form(1,2,2,2) },
    { "'Id-�������   ", &Mashtab.Id           , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "��"   , _form(1,3,2,2) },
  //{ "Ud-�������    ", &_r.Mashtab_Ud        , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��" , 2 },
    { "Ud-���-����.  ", &_sr.NOM.Ud.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B"   , _form(1,5,0,2) },
    { "Ud-���-��     ", &_sr.Dat.Ud           , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B"   , _form(1,5,0,2) },
    { "'Ud-����-��   ", &Mashtab.Ud_max       , 0               , _Ud_nom( 7.0 )   , _Ud_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "��� " , _form(1,2,2,2) },
    { "'Ud-�������   ", &Mashtab.Ud           , (sw)0xF700      , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "��"   , _form(1,3,2,2) },
  //{ "If-�������    ", &_r.Mashtab_Iv        , 0               , 0x0EFF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��" , 2 },
    { "If-���-����.  ", &_sr.NOM.Iv.fe        , 0               , 0x7fff           , 10           ,(w*)&_ind_Nom, 1              , 0xff, " A"   , _form(1,5,1,2) },
    { "If-���-��     ", &_sr.Dat.Iv           , 0               , 0x7fff           , 10           ,(w*)&_ind_Nom, 1              , 0xff, " A"   , _form(1,5,1,2) },
    { "'If-����-��   ", &Mashtab.Iv_max       , 0               , _Iv_nom( 7.0 )   , _Iv_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "��� " , _form(1,2,2,2) },
    { "'If-�������   ", &Mashtab.Iv           , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "��"   , _form(1,3,2,2) },
    { "��-�������    ", &_r.Mashtab_OS_TG     , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#ifdef  TGx_ach
    { "��x8-�������  ", &_r.Mashtab_OS_TGx    , (sw)0xF600      , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) },
#endif
#ifdef  EDS_ach
    { "E�����-�������", &_r.Mashtab_EDS       , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
#ifdef   Itt_ach
    { "Idtt-�������  ", &_r.Mashtab_Idtt      , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
    { "Is-�������    ", &_r.Mashtab_Idtt      , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
#ifdef   Id_sum_ach
    { "Id-���-�������", &_or.Mashtab_Id_sum   , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
#ifdef   It_ach
    { "It-�������    ", &_r.Mashtab_It        , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
    { "N#-�������    ", &_r.Mashtab_ZSkA      , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
  //{ "N(E��)-�������", &_or.Mashtab_N_po_EDS , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
  //{ "N(E��)-�������", &_or.Mashtab_Npr_po_EDS,0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#ifdef Id_2v_ach  // ��������� ������ Id-2��� :
    { "Id-2d-������� ", &_r.Mashtab_Id_2v     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
#ifdef N_2v_ach  // ��������� ������ N-2��� :
    { "N-2d-�������  ", &_r.Mashtab_N_2v      , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,3,2) },
#endif
  //{ "K-��������    ", &_r.Koef_Id_teplo     , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��"   , _form(1,3,2,2) },
    { "���0-���/��.  ", &_r.PDF[0].imp        , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 2              , 0xff, "��"   , _form(1,5,0,2) },
  //{ "���-����      ", &_r.PDF[0].null       ,_Grad(-179.0 )   ,_Grad(+179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(0,3,1,2) },
  //{ "���0-�������  ", &_r.PDF[0].masht      , (sw)0xF000      , 0x3000           ,_PDF_delitel  ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,1,3,2) },
  //{ "���0-�������  ", &_r.PDF[0].masht      , 0               , (sw)0xFFFFu      ,_PDF_delitel  ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,2,3,2) },
    { "N-���-����.   ", &_sr.NOM.N.fe         , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 2              , 0xff, "��/��� ", _form(1,5,0,2) },
#ifdef _Sels_shift0
    { "�����0g-K-���.", &_or.Sels_shift0      , 0               , 7                , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
#endif
    { "�����0g-����  ", &_r.Selsin[0].null    ,_Grad(-179.0 )   ,_Grad(+179.0)     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.25 )  , 0xff, "��"   , _form(0,3,1,2) },
#ifdef _Sels_mashtP0
    { "�����0m-���'+'", &_or.Sels_mashtP0     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��"   , _form(1,3,2,2) },
#endif
#ifdef _Sels_mashtM0
    { "�����0m-���'-'", &_or.Sels_mashtM0     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��"   , _form(1,3,2,2) },
#endif
    { "�����0m-�����.", &_r.Selsin[0].masht   , (sw)0xF000      , 0x0F00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,1,3,2) },
#ifdef _Sels_shift1
    { "�����1g-K-���.", &_or.Sels_shift1      , 0               , 7                , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
#endif
    { "�����1g-����  ", &_r.Selsin[1].null    ,_Grad(-179.0 )   ,_Grad(+179.0)     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.25 )  , 0xff, "��"   , _form(0,3,1,2) },
#ifdef _Sels_mashtP1
    { "�����1m-���'+'", &_or.Sels_mashtP1     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��"   , _form(1,3,2,2) },
#endif
#ifdef _Sels_mashtM1
    { "�����1m-���'-'", &_or.Sels_mashtM1     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "��"   , _form(1,3,2,2) },
#endif
    { "�����1m-�����.", &_r.Selsin[1].masht   , (sw)0xF000      , 0x0F00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,1,3,2) },
#ifdef _Rev_Pola
    { "Id#/F#-�������", &_r.Mashtab_Idz_Ivz   , (sw)0xF000      , 0x7fff           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,1,3,2) },
#endif
#ifdef  Ttrans_ach
    { "��-�����.     ", &_or.Filtr_Param      , 1               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "�� "  , _form(1,4,1,2) },
    { "Ttr-�������.  ", &_or.Ttr_predupr      , 0               ,  300*10          , 10           ,(w*)&_ind_Nom, 10             , 0xff, "��"   , _form(0,3,0,2) },
    { "Ttr-4��       ", &_or.Ttr_4mA          , -50.*10         ,  300*10          , 10           ,(w*)&_ind_Nom, 10             , 0xff, "��"   , _form(0,3,0,2) },
    { "Ttr-20��      ", &_or.Ttr_20mA         , 0               ,  300*10          , 10           ,(w*)&_ind_Nom, 10             , 0xff, "��"   , _form(0,3,0,2) }
#endif
#ifdef _DAC_OFFSET
    { "'DAC0-����.0  ", &_or.dac_numb[0].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  "  , _form(0,3,1,2) },
// #ifndef _CM3_  10.07.2017 8:21 DAC1 - ������� �� If
    { "'DAC1-����.0  ", &_or.dac_numb[1].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  "  , _form(0,3,1,2) },
// #endif
#endif
    { "DAC0-�������  ", &_or.dac_numb[0].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) },
    { "DAC1-�������  ", &_or.dac_numb[1].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#if defined(_PPG_for_DAC2) || !(defined(_CM3_) || defined(_FR50N_)) // ��� F16K DAC2 ���������
   ,{ "DAC2-�������  ", &_or.dac_numb[2].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#endif
#ifdef  _PPG_for_DAC3
   ,{ "DAC3-�������  ", &_or.dac_numb[3].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#endif
#ifdef  _PPG_for_DAC4
   ,{ "DAC4-�������  ", &_or.dac_numb[4].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#endif
#ifdef  _PPG_for_DAC5
   ,{ "DAC5-�������  ", &_or.dac_numb[5].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#endif
#ifdef  _PPG_for_DAC6
   ,{ "DAC6-�������  ", &_or.dac_numb[6].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#endif
#ifdef  _PPG_for_DAC7
   ,{ "DAC7-�������  ", &_or.dac_numb[7].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,3,3,2) }
#endif
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_serv[ ] =
  {
    { "����-����.    ", &sled.kratn           , 0               , 31               , 1000         ,(w*)&sled.dt_scan, 1          , 0xff, "��"   , _form(1,3,2,2) },
#ifdef _JOURNAL
    { "������-����.  ", &TabJrn.dt_scan       , _fSec(0)        , _fSec(5.0)       , _fSec(1.0)   ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "��� " , _form(1,1,2,2) },
#endif
#ifdef _WatchDog
    { "����� WatchDog", &_r.WD_time           , 0               ,1100              , 1            ,(w*)&_ind_Nom, 50             , 0xff, "��"   , _form(1,4,0,2) },
#endif
  //{ "����-����.    ", &sled.dt_scan         , 0               ,_MkSec(50u*1000u) ,_MkSec(1000)  ,(w*)&_ind_Nom, _MkSec(100)    , 0xff, "��"   , _form(1,2,2,2) },
    { "cS#           ", &canr.S_zad           ,_Grad( 0.0 )     ,_Grad( 359.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(0,4,0,2) },
    { "cN#           ", &canr.N_zad           ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "cId#          ", &canr.Id_zad          ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "��� " , _form(0,2,2,2) },
    { "cdId#         ", &canr.dId_zad         ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "��� " , _form(0,2,2,2) },
    { "cId#P         ", &canr.Idz_MaxP        ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "��� " , _form(0,2,2,2) },
    { "cId#M         ", &canr.Idz_MaxM        ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "��� " , _form(0,2,2,2) },
    { "cL#           ", &canr.L_zad           ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,0,2) },
    { "cL#min        ", &canr.L_min           ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "��"   , _form(1,4,0,2) },
    { "cF#           ", &canr.F_zad           ,_Fv_nom( -1.3 )  ,_Fv_nom( 1.3 )    ,_Fv_Nom       ,(w*)&_ind_Nom, _Fv_nom( 0.01 ), 0xff, "��� " , _form(0,3,2,2) },
#ifndef _F16e
    { "CS:cAi0       ", &_or.Ai_CS[0]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
    { "CS:cAi1       ", &_or.Ai_CS[1]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
    { "CS:cAi2       ", &_or.Ai_CS[2]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
    { "CS:cAi3       ", &_or.Ai_CS[3]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
    { "CS:cAi4       ", &_or.Ai_CS[4]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#ifdef _AsPo0_
    { "CS:AsPo0      ", &_or.AS_CSo[0]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo1_
    { "CS:AsPo1      ", &_or.AS_CSo[1]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo2_
    { "CS:AsPo2      ", &_or.AS_CSo[2]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo3_
    { "CS:AsPo3      ", &_or.AS_CSo[3]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo4_
    { "CS:AsPo4      ", &_or.AS_CSo[4]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo5_
    { "CS:AsPo5      ", &_or.AS_CSo[5]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo6_
    { "CS:AsPo6      ", &_or.AS_CSo[6]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPo7_
    { "CS:AsPo7      ", &_or.AS_CSo[7]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi0_
    { "CS:AsPi0      ", &_or.AS_CSi[0]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi1_
    { "CS:AsPi1      ", &_or.AS_CSi[1]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi2_
    { "CS:AsPi2      ", &_or.AS_CSi[2]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi3_
    { "CS:AsPi3      ", &_or.AS_CSi[3]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi4_
    { "CS:AsPi4      ", &_or.AS_CSi[4]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi5_
    { "CS:AsPi5      ", &_or.AS_CSi[5]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi6_
    { "CS:AsPi6      ", &_or.AS_CSi[6]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi7_
    { "CS:AsPi7      ", &_or.AS_CSi[7]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi8_
    { "CS:AsPi8      ", &_or.AS_CSi[8]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi9_
    { "CS:AsPi9      ", &_or.AS_CSi[9]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi10_
    { "CS:AsPi10     ", &_or.AS_CSi[10]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi11_
    { "CS:AsPi11     ", &_or.AS_CSi[11]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi12_
    { "CS:AsPi12     ", &_or.AS_CSi[12]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi13_
    { "CS:AsPi13     ", &_or.AS_CSi[13]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi14_
    { "CS:AsPi14     ", &_or.AS_CSi[14]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#ifdef _AsPi15_
    { "CS:AsPi15     ", &_or.AS_CSi[15]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(0,2,0,1) },
#endif
#endif //_F16e
    { "T-connectCfg  ", &_r.T_Connect_cfg     ,_Sec( 0.0 )      ,_Sec( 5.0 )       ,_Sec( 1.0 )   ,(w*)&_ind_Nom, 1              , 0xff, "��� " , _form(1,2,2,2) },
    { "T-connectSts  ", &_r.T_Connect_sts     ,_Sec( 0.0 )      ,_Sec( 5.0 )       ,_Sec( 1.0 )   ,(w*)&_ind_Nom, 1              , 0xff, "��� " , _form(1,2,2,2) },
    { "T������ CAN0  ", &_r.can[0].connect    , 0               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
    { "CAN0-����c 1  ", &can_setting( _CAN0_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   ,  _form(1,3,0,1) },
    { "CAN0-����c 2  ", &can_setting( _CAN0_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   ,  _form(1,3,0,1) },
    { "CAN0-����a    ", &can_setting( _CAN0_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   ,  _form(1,3,0,1) },
    { "T������ CAN1  ", &_r.can[1].connect                         , 0    , 100    , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
    { "CAN1-����c 1  ", &can_setting( _CAN1_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   ,  _form(1,3,0,1) },
    { "CAN1-����c 2  ", &can_setting( _CAN1_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   ,  _form(1,3,0,1) },
    { "CAN1-����a    ", &can_setting( _CAN1_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   ,  _form(1,3,0,1) }
#ifdef _CAN2_Port
   ,{ "T������ CAN2  ", &_r.can[2].connect                         , 0    , 100    , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
    { "CAN2-����c 1  ", &can_setting( _CAN2_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
    { "CAN2-����c 2  ", &can_setting( _CAN2_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) },
    { "CAN2-����a    ", &can_setting( _CAN2_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) }
#endif
#ifdef _CAN_MASTER
    #ifdef _A7_CAN_MASTER_Ust
          ,_A7_CAN_MASTER_Ust
    #endif
   ,{ "T-MconnectCfg ", &_r.T_mConnect_cfg    ,_Sec( 0.0 )      ,_Sec( 5.0 )       , _Sec(1.0)    ,(w*)&_ind_Nom, 1              , 0xff, "��� " , _form(1,2,2,2) },
    { "T-MconnectSts ", &_r.T_mConnect_sts    ,_Sec( 0.0 )      ,_Sec( 5.0 )       , _Sec(1.0)    ,(w*)&_ind_Nom, 1              , 0xff, "��� " , _form(1,2,2,2) },
    { "CAN-����      ", &_r.time_scan         ,_fSec( 0.0 )     ,_fSec( 1.0 )      , _fSec( 1.0)  ,(w*)&_ind_Nom,_fSec(0.001)    , 0xff, "c�� " , _form(1,1,3,2) }
#endif
#ifdef _CM3_
   ,{ "Modbus-����c  ", &_r.rs485.addr        , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,1) }
#endif
  };

//---------------------------------------------------------------------------------------------------------------------

#ifdef _CM3_
const _x_far struct STB       stb_ADC_masht[ ] =
  {
    { "������� n0    ", &_ar.ADC_Scale[0]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n1    ", &_ar.ADC_Scale[1]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n2    ", &_ar.ADC_Scale[2]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n3    ", &_ar.ADC_Scale[3]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n4    ", &_ar.ADC_Scale[4]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n5    ", &_ar.ADC_Scale[5]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n6    ", &_ar.ADC_Scale[6]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n7    ", &_ar.ADC_Scale[7]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n8    ", &_ar.ADC_Scale[8]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n9    ", &_ar.ADC_Scale[9]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n10   ", &_ar.ADC_Scale[10] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n11   ", &_ar.ADC_Scale[11] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n12   ", &_ar.ADC_Scale[12] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n13   ", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n14   ", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) },
    { "������� n15   ", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "��" , _form(1,1,4,2) }
 };
#endif

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_shtat[ ] =
  {
    { "���'>'-����   ", &_r.ZSkBM_MaxB        ,_Skor_nom(  0.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "���'<'-���    ", &_r.ZSkBM_MaxM        ,_Skor_nom( -2.00),_Skor_nom(  0.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "����-���      ", &_r.Temp_ZSkBM        ,                0,_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom,               8, 0xff, "��� " , _form(1,2,3,2) },
    { "N#-�����.����.", &_r.Z_SkRab           ,_Skor_nom( -2.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "N#-���.������ ", &_r.ZSk_TB            ,_Skor_nom( -2.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "N#-���.�����  ", &_r.ZSk_TH            ,_Skor_nom( -2.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "��� " , _form(0,2,2,2) },
    { "N#-�����      ", &_r.Z_SkMin           ,_Skor_nom( +0.00),_Skor_nom( +0.50 ), _Skor_nom( +0.01 ) ,(w*)&_ind_Nom, 8        , 0xff, "%"    , _form(1,2,2,2) }
#ifdef  Nzad_4_20_ach
   ,{ "��-�����-N#.  ", &_or.Filtr_Param_Nzad , 1               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "�� "  , _form(1,4,1,2) },
    { "N#-4��        ", &_or.Nzad_4mA         ,_Skor_nom( +0.00),_Skor_nom( +2.00 ), _Skor_nom( +0.01 ) ,(w*)&_ind_Nom, 8        , 0xff, "%"    , _form(1,2,2,2) },
    { "N#-20��       ", &_or.Nzad_20mA        ,_Skor_nom( +0.00),_Skor_nom( +2.00 ), _Skor_nom( +0.01 ) ,(w*)&_ind_Nom, 8        , 0xff, "%"    , _form(1,2,2,2) }
#endif
  };

//---------------------------------------------------------------------------------------------------------------------

#ifdef _A7_Obj_Ust
_x_far const struct STB       stb_obj[ ] =
  {
      _A7_Obj_Ust
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct STB       stb_Ivz[ ] =
  {
    { "F#100%->If#   ", &Ivz.t [ 20 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#95%->If#    ", &Ivz.t [ 19 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#90%->If#    ", &Ivz.t [ 18 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#85%->If#    ", &Ivz.t [ 17 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#80%->If#    ", &Ivz.t [ 16 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#75%->If#    ", &Ivz.t [ 15 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#70%->If#    ", &Ivz.t [ 14 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#65%->If#    ", &Ivz.t [ 13 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#60%->If#    ", &Ivz.t [ 12 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#55%->If#    ", &Ivz.t [ 11 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#50%->If#    ", &Ivz.t [ 10 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#45%->If#    ", &Ivz.t [  9 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#40%->If#    ", &Ivz.t [  8 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#35%->If#    ", &Ivz.t [  7 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#30%->If#    ", &Ivz.t [  6 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#25%->If#    ", &Ivz.t [  5 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#20%->If#    ", &Ivz.t [  4 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#15%->If#    ", &Ivz.t [  3 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#10%->If#    ", &Ivz.t [  2 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#5% ->If#    ", &Ivz.t [  1 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) },
    { "F#0% ->If#    ", &Ivz.t [  0 ]         , 0               , _Iv_nom( 1.5 )   ,_Iv_nom(0.01) ,(w*)&_ind_Nom, 1              , 0xff, "%"  , _form(1,3,2,2) }
  };

//---------------------------------------------------------------------------------------------------------------------

#ifdef   _AVTONASTR
_x_far const struct STB       stb_anastr[ ] =
  {
  //{ "T�� ��-������.", &_r.Tpp_AN_nepr       , 3               , 2000             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,2) },
    { "T�� ��-������.", &_r.Tpp_AN_pr         , 3               , 2000             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,2) },
    { "����.�����.�� ", &_r.KoefDempfirRT     , (w)(0.25*256.)  , 2 * 256          , 256          ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(0,2,3,2) },
    { "Id-��-���p-90g", &_r.INN_def_AN        , 0               , 1                , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "    , _form(1,1,0,2) },
    { "Te            ", &_r.Te_AN             , 0               , 120 * 64         , 64           ,(w*)&_ind_Nom, 64             , 0xff, "��"   , _form(1,3,0,2) },
  //------ 11.01.2022 - DAN �����, ��� ��������� ����� ���� ��� ��������, ����� ���� � ��� ����� �� ����������...
  //{ "'���/Ra_����. ", &_r.KtpRa_AN_nepr     , 0               , 120 * 64         , 64           ,(w*)&_ind_Nom, 0              , 0xff, "��"   , _form(1,3,2,2) },
  //{ "'���/Ra_����. ", &_r.KtpRa_AN_pr       , 0               , 120 * 64         , 64           ,(w*)&_ind_Nom, 0              , 0xff, "��"   , _form(1,3,2,2) }
  //------
  //{ "Tm            ", &_r.Tm_AN             , 0               , 1000             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "��"   , _form(1,3,0,2) },
  //{ "T�������-Tm   ", &_r.T_AN_ust          , _fSec( 0.0 )    , _fSec( 16.0 )    , _fSec(1)     ,(w*)&_ind_Nom, _fSec(1)       , 0xff, "��� " , _form(1,2,1,2) },
  //{ "L0 (Tm ��)    ", &_r.Alfa0_forTm_AN    , _Grad(60)       , _Grad(85)        , _Grad(1)     ,(w*)&_ind_Nom, _Grad(5)       , 0xff, "��"   , _form(1,2,0,2) },
  //{ "����-�� L#-Tm ", &_r.Kratn_5_AN        , 5               , 10               , 1            ,(w*)&_ind_Nom, 5              , 0xff, "��"   , _form(1,2,0,2) },
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

const struct UstUzm   Ustav[] =
  {
//  { "������������� " ,sizeof(stb_reg   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_reg   [0] },
    { "���. �������� " ,sizeof(stb_RS    )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_RS    [0] },
    { "��������� ���a" ,sizeof(stb_RT    )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_RT    [0] },
    { "����          " ,sizeof(stb_SIFU  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_SIFU  [0] },
    { "���           " ,sizeof(stb_EDS   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_EDS   [0] },
    { "�����������   " ,sizeof(stb_Vozb  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_Vozb  [0] },
    { "������        " ,sizeof(stb_Tormoz)/sizeof(struct STB) ,(_x_far const struct STB*)&stb_Tormoz[0] },
#if defined( _RDN ) || defined( _RRS ) || defined( _BUKSOVKA )
    { "������        " ,sizeof(stb_Procat)/sizeof(struct STB) ,(_x_far const struct STB*)&stb_Procat[0] },
#endif
#ifdef _RVId
    { "PB-Id         " ,sizeof(stb_RVId  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_RVId  [0] },
#endif
    { "������        " ,sizeof(stb_avar  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_avar  [0] },
    { "����������    " ,sizeof(peregr    )/sizeof(struct STB) ,(_x_far const struct STB*)&peregr    [0] },
    { "��������      " ,sizeof(stb_masht )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_masht [0] },
#ifdef _CM3_
    { "�������� ���  " ,sizeof(stb_ADC_masht)/sizeof(struct STB) ,&stb_ADC_masht[0] },
#endif
    { "������� �����." ,sizeof(stb_shtat )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_shtat [0] },
#ifdef _AVTONASTR
    { "������������� " ,sizeof(stb_anastr)/sizeof(struct STB) ,(_x_far const struct STB*)&stb_anastr[0] },
#endif
    { "F#->If#       " ,sizeof(stb_Ivz   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_Ivz   [0] },
    { "��������e     " ,sizeof(stb_serv  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_serv  [0] }
#ifdef _A7_Obj_Ust
   ,{ "������. �����." ,sizeof(stb_obj   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_obj   [0] }
#endif
#ifdef  _INTERPRETER
   ,{ "������. �����." ,sizeof(Ust_Obj_Prg)/sizeof(struct Obj_STB) ,(_x_far const struct STB*)&Ust_Obj_Prg[0] }
#endif
  }; /* ���������� ������� � ������� */
const word _MaxNumUstav = sizeof(Ustav)/sizeof(const struct UstUzm) ;


//------------- �6 - ������� ��������� -------------------

_x_far const struct Ind  ind_reg[] =
  {
#ifndef  _SIFU2_
         { "L    , Id     ", { &S.Alfa_Old     , &Id_dop_kod    },{_Grad( 1 )     ,_Id_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L    , Ud     ", { &S.Alfa_Old     , &UdSr          },{_Grad( 1 )     ,_Ud_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L    , ����   ", { &S.Alfa_Old     , &S.NumMost     },{_Grad( 1 )     ,  1             },{ "�p, ", "" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,1,0,1)} },
         { "Id   , Ud     ", { &Id_dop_kod     , &UdSr          },{_Id_Nom        ,_Ud_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
#else
         { "L    , Id1    ", { &S.Alfa_Old     , &Id_dop_kod    },{_Grad( 1 )     ,_Id_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L2   , Id2    ", { &S2.Alfa_Old    , &Id2_dop_kod   },{_Grad( 1 )     ,_Id_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L    , Idsum  ", { &S.Alfa_Old     , &Id_sum        },{_Grad( 1 )     ,_Id_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L2   , Idsum  ", { &S2.Alfa_Old    , &Id_sum        },{_Grad( 1 )     ,_Id_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L    , Ud     ", { &S.Alfa_Old     , &UdSr          },{_Grad( 1 )     ,_Ud_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L2   , Ud     ", { &S2.Alfa_Old    , &UdSr          },{_Grad( 1 )     ,_Ud_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L    , ����   ", { &S.Alfa_Old     , &S.NumMost     },{_Grad( 1 )     ,  1             },{ "�p, ", "" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,1,0,1)} },
         { "L2   , ����   ", { &S2.Alfa_Old    , &S.NumMost     },{_Grad( 1 )     ,  1             },{ "�p, ", "" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,1,0,1)} },
         { "Idsum, Ud     ", { &Id_sum         , &UdSr          },{_Id_Nom        ,_Ud_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "Id1  , Id2    ", { &Id_dop_kod     , &Id2_dop_kod   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
       //{ "|Id1|, |Id2|  ", { &IDV            , &IDV2          },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "Id1s , Id2s   ", { &Id_sr          , &Id2_sr        },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "|Id1|, Id1s   ", { &IDV            , &Id_sr         },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "|Id2|, Id2s   ", { &IDV2           , &Id2_sr        },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
#endif
#ifdef _REG_POL
         { "S#   , S      ", { &ZUgol          , &Ugol          },{_Grad( 1 )     ,_Grad( 1 )      },{ "�, " ,"�" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "S#   , RPout  ", { &ZUgol          , &OuRP          },{_Grad( 1 )     ,_Skor_nom(1)    },{ "�, " ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
#endif
         { "N#   , N#R    ", { &Z_Skor         , &ZISkor        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N#R  , N      ", { &ZISkor         , &Skor          },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N    , E      ", { &Skor           , &EDS_dop_kod   },{_Skor_nom(1)   ,_EDS_nom(1)     },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N    , Nx     ", { &Skor           , &Skor_r        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Nnf  , Nf     ", { &Skor_ind       , &Skor_f        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#ifdef   TGx_ach
         { "Nx1  , Nx8    ", { &TGx1           , &TGx8          },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%,"  , "%"}, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,2,2),_form(0,2,2,2)} },
#endif
#ifdef  Nzad_4_20_ach
         { "N#(4-20)      ", { &Nzad_4_20      , &Nzad          },{_1mA_Nom       ,_Skor_nom(1)    }, {"��," ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,2,1,2),_form(0,3,0,2)} },
#endif
       //{ "dN   , �����-p", { &Delta_Sk       , &OuIchRS_k     },{_Skor_nom(1)   ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#ifndef  _SIFU2_
         { "Id#  , Id     ", { &OuRegS_dop_kod , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Id   , M      ", { &Id_dop_kod     , &Moment        },{_Id_Nom        ,_Mom_Nom        },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#else
         { "Id#  , Id1    ", { &OuRegS_dop_kod , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Id#  , Id2    ", { &OuRegS_dop_kod , &Id2_dop_kod   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Idsum, M      ", { &Id_sum         , &Moment        },{_Id_Nom        ,_Mom_Nom        },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef _DST
         { "Id   , IstF   ", { &Id_dop_kod     , &Id_Stat_flt.out},{_Id_Nom    , _Id_Nom      }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
#endif
         { "E#   , E      ", { &Zad_EDS        , &EDS_dop_kod   },{_EDS_nom(1)    ,_EDS_nom(1)     },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(0,3,1,2)} },
#ifdef   EDS_ach
         { "E�����, E����p", { &iEDS           , &prEDS         },{_EDS_nom(1)>>_Skor_Shift ,_EDS_nom(1)>>_Skor_Shift },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
         { "F#   , If#    ", { &V.Fv_zad       , &V.Iv_zad      },{_Fv_nom(1)     ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If#  , If     ", { &V.Iv_zad       , &V.Iv          },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If   , F      ", { &V.Iv           , &V.Fv          },{_Iv_Nom        ,_Fv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#ifdef  _Vozb_KTE
         { "Lf   , If     ", { &V.Alfa_Old     , &V.Iv          },{_Grad( 1 )     ,_Iv_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
         { "����-�,If     ", { &V.Integr_rt    , &V.Iv          },{_Grad( 1 )     ,_Iv_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
#endif
         { "Id  ,Id-�����p", { &Id_dop_kod     , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(1,3,0,2)} },
         { "Id-���,Id-���.", { &Id_TeploIntegr , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,2,2),_form(1,3,0,2)} },
         { "KompUd,Ud-komp", { &Kompen_Ud      , &UdSr_Komp     },{ 1             ,_Ud_Nom         },{ "d,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
#ifndef _SIFU2_
         { "|Id#R|, |Id|  ", { &ZIDN           , &IDV           },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(1,3,0,2)} },
         { "���-p, Id-p   ", { &OIRT           , &IDN           },{_Grad( 1 )     ,_Id_Nom         },{ "�,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
#else
         { "INN  , INN-�� ", { &INN            , &INN_dvig      },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
         { "RVTout, dL2   ", { &S2.Out_rvt     , &S2.Alfa_RVT   },{_Grad(1)       ,_Grad(1)        },{ "�,"  ,"�" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,2,1,2),_form(0,2,1,2)} },
         { "|Id1#R|,|Id1| ", { &ZIDN           , &IDV           },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(1,3,0,2)} },
         { "|Id2#R|,|Id2| ", { &ZIDN_2_        , &IDV2          },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(1,3,0,2)} },
         { "��1�-p,Id1-p  ", { &OIRT           , &IDN           },{_Grad( 1 )     ,_Id_Nom         },{ "�,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
         { "��2�-p,Id2-p  ", { &OIRT_2_        , &IDN_2_        },{_Grad( 1 )     ,_Id_Nom         },{ "�,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
#endif
#ifdef Itt_ach
         { "Idtt , Id     ", { &Idtt           , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef Itt1_ach
         { "Idtt1, Id1    ", { &Idtt1          , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef Itt2_ach
         { "Idtt2, Id2    ", { &Idtt2          , &Id2_dop_kod   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef It_ach
         { "It   , Id     ", { &It             , &Id_dop_kod    },{_Iv_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
         { "Ud-oe         ", { &UdSr                            },{ 1                                     },{ "��"       }, {(w*)&_ind_Nom              },{_form(0,4,0,2)               } },
         { "Ud   , U����  ", { &UdSr           , &Uinsul        },{_Ud_Nom        , (w)(1.0*(_AD_MAX/5.0))},{ "%,"  ,"B" }, {(w*)&_ind_100,(w*)&_ind_Nom},{_form(0,3,1,2),_form(0,1,2,2)} },
         { "U����,U��.���c", { &Uinsul         , &Uinsul_max    },{(w)(1.0*(_AD_MAX/5.0)), (w)(1.0*(_AD_MAX/5.0))},{ "�,"  ,"B" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,1,2,2),_form(0,1,2,2)} },
#ifdef Insul_D_ach
         { "Uf   ,  U���� ", { &Uf             , &UinsulD      }, {_Ud_Nom     ,(w)(1.0*(_AD_MAX/5.0))    }, {"%,","B"}, {(w*)&_ind_100,(w*)&_ind_Nom}, {_form(0,3,1,2),_form(0,1,2,2)} },
         { "U����,U��.���c", { &UinsulD        , &UinsulD_max  }, {(w)(1.0*(_AD_MAX/5.0)), (w)(1.0*(_AD_MAX/5.0))},{"�, ","B"}, {(w*)&_ind_Nom,(w*)&_ind_Nom}, {_form(0,1,2,2),_form(0,1,2,2)} },
#endif
#ifdef  _T_PDF
         { "���0_T, ���0_F", { &PDF[0].N_Tpdf  , &PDF[0].N_Fpdf},{ _Skor_Nom     ,_Skor_Nom       },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef _CM3_
         { "���0:��/���, %", { &PDF[0].out_ob  , &PDF[0].out_m  },{ 10            ,_Skor_Nom       },{ ", "  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,4,1,2),_form(0,3,0,2)} },
#else
         { "���0:��/���, %", { &PDF[0].out_ob  , &PDF[0].out_m  },{ 1             ,_Skor_Nom       },{ ", "  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,4,0,2),_form(0,3,0,2)} },
#endif
#ifdef TG_ach
         { "��   , E      ", { &TG             , &EDS_dop_kod   },{_Skor_nom(1)   ,_EDS_nom(1)     },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
#endif
         { "�����0:����, %", { &Sels[0].out_g  , &Sels[0].out_m}, {_Grad( 1 )  ,_Skor_Nom     }, {", " , ""    }, {(w*)&_ind_Nom,(w*)&_ind_100}, {_form(0,3,1,2),_form(0,3,1,2)} },
         { "�����1:����, %", { &Sels[1].out_g  , &Sels[1].out_m}, {_Grad( 1 )  ,_Skor_Nom     }, {", " , ""    }, {(w*)&_ind_Nom,(w*)&_ind_100}, {_form(0,3,1,2),_form(0,3,1,2)} },
#ifdef  Ttrans_ach
         { "Ttr(4-20),Ttr ", { &Ttrans_4_20    , &Ttrans        },{_1mA_Nom    , 10           }, {"��,","�p"   }, {(w*)&_ind_Nom,(w*)&_ind_Nom}, {_form(0,2,1,2),_form(0,3,0,2)} },
#endif
#ifndef  _SIFU2_
         { "  Id (%, �)   ", { &Id_dop_kod     , &Id_dop_kod   }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Id.fe},{_form(0,3,1,2),_form(0,5,0,2)} },
#else
         { "  Id1 (%, �)  ", { &Id_dop_kod     , &Id_dop_kod   }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&Id_divBy2_abs},{_form(0,3,1,2),_form(0,5,0,2)} },
         { "  Id2 (%, �)  ", { &Id2_dop_kod    , &Id2_dop_kod  }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&Id_divBy2_abs},{_form(0,3,1,2),_form(0,5,0,2)} },
         { "  Idsum (%, �)", { &Id_sum         , &Id_sum       }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Id.fe},{_form(0,3,1,2),_form(0,5,0,2)} },
#endif
         { "  Ud (%, �)   ", { &UdSr           , &UdSr         }, { _Ud_Nom , _Ud_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Ud.fe},{_form(0,3,1,2),_form(0,5,0,2)} },
         { "  If (%, �)   ", { &V.Iv           , &V.Iv         }, { _Iv_Nom , _Iv_Nom*10 },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Iv.fe},{_form(0,3,0,2),_form(0,2,1,2)} }
  };

//---------------------------------------------------------------------------------------------------------------------

_x_far const struct Ind  ind_serv[] =
  {
    // 12-�� �������� ����� , �� ��� �� � ������ ����� - ��������� ������ ������ :
#if   defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
         { "IA1   , IB1   ", { &IA1            , &IB1             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC1   , IA2   ", { &IC1            , &IA2             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IB2   , IC2   ", { &IB2            , &IC2             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
    // 12-�� �������� ����� , �� ������ �� � ������ ����� :
#elif defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && !defined( IA2_ach ) && !defined( IB2_ach ) && !defined( IC2_ach ) && \
      defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach )
         { "IA1   , IB1   ", { &IA1            , &IB1             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC1   , IA2   ", { &IC1            , &IA3             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IB2   , IC2   ", { &IB3            , &IC3             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
    // 6-�� �������� ����� :
#elif defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
         { "IA1   , IB1   ", { &IA1            , &IB1             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC1           ", { &IC1                               },{_Id_Nom                         },{ "%  "      }, {(w*)&_ind_100              },{_form(1,3,0,2)               } },
#endif
    // 12-�� �������� ����� , �� ��� �� � ������ ����� - ��������� ������ ������ :
#if   defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach ) && defined( IA4_ach ) && defined( IB4_ach ) && defined( IC4_ach )
         { "IA3   , IB3   ", { &IA3            , &IB3             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC3   , IA4   ", { &IC3            , &IA4             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IB4   , IC4   ", { &IB4            , &IC4             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
#endif
#ifdef _Dat_Temp_Max
       _A6_ADC_multiplex_temp,
#endif
         { "cCfgR,  cStsR ", { &canr.CfgReg.all, &canr.StatReg.all},{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },
         { "cS#  ,  cN#   ", { &canr.S_zad     , &canr.N_zad      },{_Grad( 1 )     ,_Skor_Nom       },{ "��, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cId# ,  cdId# ", { &canr.Id_zad    , &canr.dId_zad    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cId#P,  cId#M ", { &canr.Idz_MaxP  , &canr.Idz_MaxM   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cL#  ,  cF#   ", { &canr.L_zad     , &canr.F_zad      },{_Grad( 1 )     ,_Fv_Nom         },{ "�p, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
         { "cAo0 ,  cAo1  ", { &canr.Ao[0]     , &canr.Ao[1]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi0 ,  cAi1  ", { &canr.Ai[0]     , &canr.Ai[1]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi2 ,  cAi3  ", { &canr.Ai[2]     , &canr.Ai[3]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi4          ", { &canr.Ai[4]                        },{ 1                              },{ " "        }, {(w*)&_ind_Nom              },{_form(0,5,0,2)               } },
         { "CAN0Err:Bus   ", { &can_dd[_CAN0_Port].Avar           },{ 1                                },{"�� "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN0Err:Rec,Tx", { &can_dd[_CAN0_Port].Error_receive,&can_dd[_CAN0_Port].Error_send},{1,1},{"��, ","�� "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CAN1Err:Bus   ", { &can_dd[_CAN1_Port].Avar                                        },{1  },{"�� "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN1Err:Rec,Tx", { &can_dd[_CAN1_Port].Error_receive,&can_dd[_CAN1_Port].Error_send},{1,1},{"��, ","�� "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
#ifdef _CAN2_Port
         { "CAN2Err:Bus   ", { &can_dd[_CAN2_Port].Avar                                        },{1  },{"�� "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN2Err:Rec,Tx", { &can_dd[_CAN2_Port].Error_receive,&can_dd[_CAN2_Port].Error_send},{1,1},{"��, ","�� "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
#endif
#ifdef _CAN_MASTER
    #ifdef _A6_CAN_MASTER_Ind
           _A6_CAN_MASTER_Ind,
    #endif
#endif
#ifdef _NARABOTKA
         { "���������-�,� ", { &NARAB.hou     , &NARAB.min  },{ 1             , 1              },{ "�, " ,"m"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,2,0,1)} },
         { "���������-�,c ", { &NARAB.min     , &NARAB.sec  },{ 1             , 1              },{ "m, " ,"c"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)} },
         { "���������-�,� ", { &NARAB.hou     , &NARAB.ovr  },{ 1             , 1              },{ "�, " ,"��" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,3,0,1)} },
#endif
         { "Tckl  , StopP ", { &Tckl, &stop_point       }, { _MkSec(1000), 1          },{ "��, ",""  }, {(w*)&_ind_Nom, (w*)&_ind_Nom } ,{_form(1,2,1,2),_form(1,3,0,1)} },
         { "StpS  , StpS2 ", { &stop_pointS, &stop_pointV }, { 1         , 1          },{ ", "  ,""  }, {(w*)&_ind_Nom, (w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} },
         { "StpPDF, StpDP ", { &stop_pointP, &stop_pointD }, { 1         , 1          },{ ", "  ,""  }, {(w*)&_ind_Nom, (w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} }
  };

//---------------------------------------------------------------------------------------------------------------------

#ifdef _A6_Obj_Ind
_x_far const struct Ind  ind_obj[] =
  {
        _A6_Obj_Ind
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

#if defined( _RDN ) || defined( _RRS ) || defined( _BUKSOVKA )
_x_far const struct Ind  ind_Procat[] =
  {
#ifdef _RDN
         { "Id   , Id-2d  ", { &Id_dop_kod     , &Id_2v        }, {_Id_Nom     , _Id_Nom      }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "dId  , RDNout ", { &dId            , &RDN_Out      }, {_Id_Nom     , _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "N#   , RDNout ", { &Z_Skor         , &RDN_Out      }, {_Skor_nom(1), _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} }
#endif
#ifdef _BUKSOVKA
  #ifdef _RDN
    ,
  #endif
         { "N    , N-2d   ", { &Skor           , &N_2v         }, {_Skor_nom(1), _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "N    , dN     ", { &Skor           , &dN           }, {_Skor_nom(1), _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} }
#endif
#if defined( _RRS ) && defined( _DST )
  #if defined( _RDN ) || defined( _BUKSOVKA )
    ,
  #endif
         { "IstF , Ist-2d ", { &Id_Stat_flt.out, &Id_stat_2v     },{_Id_Nom    , _Id_Nom      }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} }
#endif
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

#ifdef _RVId
_x_far const struct Ind  ind_RVId[] =
  {
         { "Id1  , Id2    ", { &RVId.Id1      , &RVId.Id2     },{_Id_Nom        ,_Id_Nom         },{ "%,  ","%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If   , If2    ", { &V.Iv          , &V2.Iv        },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If#  , If#2   ", { &V.Iv_zad      , &V2.Iv_zad    },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "dId  , dIf    ", { &RVId.dId      , &RVId.dIf     },{_Id_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Out  , dIf#   ", { &RVId.Out      , &RVId.dIfz    },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If#1 , If2#1  ", { &RVId.Iv1_z    , &RVId.Iv2_z   },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If#2 , If2#2  ", { &RVId.Iv1_zad  , &RVId.Iv2_zad },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If#k , If2#k  ", { &RVId.Iv1_korr , &RVId.Iv2_korr},{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Id1  , Id2 (�)", { &RVId.Id1      , &RVId.Id2     },{_Id_Nom        ,_Id_Nom         },{ ", "  ," " }, {(w*)&_sr.NOM.Id.fe,(w*)&_sr.NOM.Id.fe},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "If   , If2 (�)", { &V.Iv          , &V2.Iv        },{_Iv_Nom*10     ,_Iv_Nom*10      },{ ", "  ," " }, {(w*)&_sr.NOM.Iv.fe,(w*)&_sr.NOM.Iv.fe},{_form(0,2,1,2),_form(0,2,1,2)} }
  };
#endif

//---------------------------------------------------------------------------------------------------------------------

const struct IndUzm Indicat[]=
{
    { "������������� " ,sizeof(ind_reg )/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_reg [0] },
#ifdef _A6_Obj_Ind
    { "������. �����." ,sizeof(ind_obj )/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_obj [0] },
#endif
#if defined( _RDN ) || defined( _RRS ) || defined( _BUKSOVKA )
    { "������        " ,sizeof(ind_Procat)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_Procat[0] },
#endif
#ifdef _RVId
    { "PB-Id         " ,sizeof(ind_RVId)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_RVId[0] },
#endif
    { "��������e     " ,sizeof(ind_serv)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_serv[0] }
#ifdef  _INTERPRETER
   ,{ "������. �����." ,sizeof(Ind_Obj_Prg)/sizeof(struct Ind_obj ) ,(_x_far const struct Ind*)(&Ind_Obj_Prg[0]) }
#endif
};

const word _NumInd = sizeof( Indicat )/sizeof(struct IndUzm) ;

//--------------------------------------------------------

#ifdef _CombRedact
/*
��� �� �������� ����� ������� � �������: �������� ������ �� ������� ������� � �������� �� �� ����� (0xff ������), ������� �������� �� ���������.
�������� ������ � ���������� � ��������� � ��� ������ �� ������ ��� �������� ������ ���������.
*/
_x_far const struct COMB_MENU comb_menu[] =
{
#ifdef _OBJ_COMB_REDACT
     _OBJ_COMB_REDACT,
#endif
    { "N#-������� - N#a", &_r.Mashtab_ZSkA,  0, 0x1400, 0x0100, (w*)&_ind_Nom, 1, "��", _form(1,3,3,2),
                  /*ind*/ &ZSkA, _Skor_Nom , "%",               (w*)&_ind_100,          _form(0,3,0,2)},
    { "��-������� - �� ", &_r.Mashtab_OS_TG, 0, 0x1400, 0x0100, (w*)&_ind_Nom, 1, "��", _form(1,3,3,2),
                  /*ind*/ &TG,   _Skor_Nom , "%",               (w*)&_ind_100,          _form(0,3,0,2)},
    { "�����0: ����.-% ", &_r.Selsin[0].masht, (sw)0xF000, 0x0F00, 0x0100, (w*)&_ind_Nom, 1, "��", _form(0,1,3,2),
                  /*ind*/ &Sels[0].out_m, _Skor_Nom,  "%",      (w*)&_ind_100,          _form(0,3,0,2)},
    { "If#-1-������ - N", &_r.Iv_zad, _Iv_nom(0.0), _Iv_nom(1.3), _Iv_Nom, (w*)&_ind_Nom, _Iv_nom(0.01), "��� ", _form(1,1,2,2),
                  /*ind*/ &Skor, _Skor_nom(1), "%",             (w*)&_ind_100,          _form(0,3,1,2)}
};

_x_far const word len_comb_menu = sizeof(comb_menu) / sizeof(const struct COMB_MENU); //����������� ������� ��������� ��������������� ����
#endif

//--------------------------------------------------------

//-------- ������� ���������� ��� ������ �� ���� ---------
//---- � ��3 ��� 10-��������� , � ��� - 12-��������� -----
                                                                   //_Vozb_KTE |    |  _Vozb_KTE |
_x_far const struct DAC_output_tab2 DAC_tab2  [ ] =                //          |    |  _SIFU2_   | _SIFU2_
  {                                                                //          |    |            |
    { "E         ",  &EDS_dop_kod  , (w)(0.12 * 256.)          },  // 0        | 0  |  0         |  0
    { "F#        ",  &V.Fv_zad     , (  1.00 * 256./_K_diskr ) },  // 1        | 1  |  1         |  1
    { "F         ",  &V.Fv         , (  1.00 * 256./_K_diskr ) },  // 2        | 2  |  2         |  2
    { "If#       ",  &V.Iv_zad     , (  1.00 * 256./_K_diskr ) },  // 3        | 3  |  3         |  3
    { "If        ",  &V.Iv         , (  1.00 * 256./_K_diskr ) },  // 4        | 4  |  4         |  4
   #ifdef _Vozb_KTE                                                //          |    |            |
    { "Lf        ",  &V.Alfa_Old   , (w)(0.12 * 256.)          },  // 5        | -  |  5         |  -
   #endif                                                          //          |    |            |
    { "N#        ",  &Z_Skor       , (w)(0.12 * 256.)          },  // 6        | 5  |  6         |  5
    { "N#R       ",  &ZISkor       , (w)(0.12 * 256.)          },  // 7        | 6  |  7         |  6
    { "N         ",  &Skor         , (w)(0.12 * 256.)          },  // 8        | 7  |  8         |  7
    { "Id#       ",  &OuRegS_dop_kod,(  1.00 * 256./_K_diskr ) },  // 9        | 8  |  9         |  8
    { "|Id#R|    ",  &ZIDN         , (  1.00 * 256./_K_diskr ) },  //10        | 9  | 10         |  9
   #ifndef _SIFU2_                                                 //          |    |            |
    { "Id        ",  &Id_dop_kod   , (  1.00 * 256./_K_diskr ) },  //11        | 10 |  -         | -
   #else                                                           //          |    |            |
    { "Id1       ",  &Id_dop_kod   , (  1.00 * 256./_K_diskr ) },  //-         | -  | 11         | 10
    { "Id1-�����.",  &Id_sr        , (  1.00 * 256./_K_diskr ) },  //-         | -  | 12         | 11
    { "Id2       ",  &Id2_dop_kod  , (  1.00 * 256./_K_diskr ) },  //-         | -  | 13         | 12
    { "Id2-�����.",  &Id2_sr       , (  1.00 * 256./_K_diskr ) },  //-         | -  | 14         | 13
    { "Idsum     ",  &Id_sum       , (  1.00 * 256./_K_diskr ) },  //-         | -  | 15         | 14
   #endif                                                          //          |    |            |
    { "Ud        ",  &UdSr         , (  1.00 * 256./_K_diskr ) },  //12        | 11 | 16         | 15
    { "L         ",  &S.Alfa_Old   , (w)(0.12 * 256.)          },  //13        | 12 | 17         | 16
   #ifdef _SIFU2_                                                  //          |    |            |
    { "dL2       ",  &S2.Alfa_RVT  , (w)(0.12 * 256.)          },  //-         | -  | 18         | 17
    { "L2        ",  &S2.Alfa_Old  , (w)(0.12 * 256.)          },  //-         | -  | 19         | 18
   #endif                                                          //          |    |            |
    { "PDF0m     ",  &PDF[0].out_m , (w)(0.12 * 256.)          },  //14        | 13 | 20         | 19
    { "PDF0g     ",  &PDF[0].out_g , (w)(0.12 * 256.)          },  //15        | 14 | 21         | 20
    { "Sels0g    ",  &Sels[0].out_g, (w)(0.12 * 256.)          },  //16        | 15 | 22         | 21
    { "Sels1g    ",  &Sels[1].out_g, (w)(0.12 * 256.)          },  //17        | 16 | 23         | 22
    { "Sels0m    ",  &Sels[0].out_m, (w)(0.12 * 256.)          },  //18        | 17 | 24         | 23
    { "Sels1m    ",  &Sels[1].out_m, (w)(0.12 * 256.)          },  //19        | 18 | 25         | 24
    { "cAo0      ",  &canr.Ao[0]   , (  1.00 * 256./_K_diskr ) },  //20        | 19 | 26         | 25
    { "cAo1      ",  &canr.Ao[1]   , (  1.00 * 256./_K_diskr ) },  //21        | 20 | 27         | 26
    { "cAi0      ",  &canr.Ai[0]   , (  1.00 * 256./_K_diskr ) },  //22        | 21 | 28         | 27
    { "cAi1      ",  &canr.Ai[1]   , (  1.00 * 256./_K_diskr ) },  //23        | 22 | 29         | 28
    { "cAi2      ",  &canr.Ai[2]   , (  1.00 * 256./_K_diskr ) },  //24        | 23 | 30         | 29
    { "cAi3      ",  &canr.Ai[3]   , (  1.00 * 256./_K_diskr ) },  //25        | 24 | 31         | 30
    { "cAi4      ",  &canr.Ai[4]   , (  1.00 * 256./_K_diskr ) },  //26        | 25 | 32         | 31
#ifdef _DST
    { "Idin      ",  &Id_Din       , (  1.00 * 256./_K_diskr ) },
    { "Ist       ",  &Id_Stat      , (  1.00 * 256./_K_diskr ) },
    { "IstF      ",  &Id_Stat_flt.out, ( 1.00 * 256./_K_diskr) },
#endif
#ifdef _RVId
    { "If#2      ",  &V2.Iv_zad    , (  1.00 * 256./_K_diskr ) },
#endif
#ifdef _Dat_Temp_Max
       _AD_ADC_multiplex_temp,
#endif
    #ifdef _AD_Obj_DAC
      _AD_Obj_DAC ,
    #endif
       //  ���������� "����" ������� ������� ������ � ����� ������,
       // �.�. ��� ������������ ��� ����� ����� � �� ������ ����������.
    { "Test      ",  &T_DAC       , (  1.0*256     ) }
  } ;
const word  _DAC_Ntab2 = sizeof(DAC_tab2) / sizeof(struct DAC_output_tab2) ;

//-------------------------------------------------

const struct Stout Nstout [] = {
                                 #ifdef  _Po0_
                                   { "Po0   ", &Po0_c.all   ,  20 },
                                 #endif
                                 #ifdef  _AsPo0_
                                   { "AsPo0 ", &PoS_c[0].all,  20 },
                                 #endif
                                 #ifdef  _AsPo1_
                                   { "AsPo1 ", &PoS_c[1].all,  20 },
                                 #endif
                                 #ifdef  _AsPo2_
                                   { "AsPo2 ", &PoS_c[2].all,  20 },
                                 #endif
                                 #ifdef  _AsPo3_
                                   { "AsPo3 ", &PoS_c[3].all,  20 },
                                 #endif
                                 #ifdef  _AsPo4_
                                   { "AsPo4 ", &PoS_c[4].all,  20 },
                                 #endif
                                 #ifdef  _AsPo5_
                                   { "AsPo5 ", &PoS_c[5].all,  20 },
                                 #endif
                                 #ifdef  _AsPo6_
                                   { "AsPo6 ", &PoS_c[6].all,  20 },
                                 #endif
                                 #ifdef  _AsPo7_
                                   { "AsPo7 ", &PoS_c[7].all,  20 },
                                 #endif
                                   { "Q1V   ", (b*)0        ,  40 },
                                   { "Q2V   ", (b*)0        ,  60 }
                                } ;
const word _Nout  = sizeof(Nstout)/sizeof(const struct Stout) ;

//-------------------------------------------------

const struct Stin Nstin [] =   {
                                   { "Pi0   ", &Pi0_c.all }
                                 #ifdef  _Pi1_
                                  ,{ "Pi1   ", &Pi1_c.all }
                                 #endif
                                 #ifdef  _Pi2_
                                  ,{ "Pi2   ", &Pi2_c.all }
                                 #endif
                                 #ifdef  _Pi3_
                                  ,{ "Pi3   ", &Pi3_c.all }
                                 #endif
                                 #ifdef  _Pi4_
                                  ,{ "Pi4   ", &Pi4_c.all }
                                 #endif
                                 #ifdef  _AsPi0_
                                  ,{ "AsPi0 ", &PiS_c[0].all }
                                 #endif
                                 #ifdef  _AsPi1_
                                  ,{ "AsPi1 ", &PiS_c[1].all }
                                 #endif
                                 #ifdef  _AsPi2_
                                  ,{ "AsPi2 ", &PiS_c[2].all }
                                 #endif
                                 #ifdef  _AsPi3_
                                  ,{ "AsPi3 ", &PiS_c[3].all }
                                 #endif
                                 #ifdef  _AsPi4_
                                  ,{ "AsPi4 ", &PiS_c[4].all }
                                 #endif
                                 #ifdef  _AsPi5_
                                  ,{ "AsPi5 ", &PiS_c[5].all }
                                 #endif
                                 #ifdef  _AsPi6_
                                  ,{ "AsPi6 ", &PiS_c[6].all }
                                 #endif
                                 #ifdef  _AsPi7_
                                  ,{ "AsPi7 ", &PiS_c[7].all }
                                 #endif
                                 #ifdef  _AsPi8_
                                  ,{ "AsPi8 ", &PiS_c[8].all }
                                 #endif
                                 #ifdef  _AsPi9_
                                  ,{ "AsPi9 ", &PiS_c[9].all }
                                 #endif
                                 #ifdef  _AsPi10_
                                  ,{ "AsPi10", &PiS_c[10].all }
                                 #endif
                                 #ifdef  _AsPi11_
                                  ,{ "AsPi11", &PiS_c[11].all }
                                 #endif
                                 #ifdef  _AsPi12_
                                  ,{ "AsPi12", &PiS_c[12].all }
                                 #endif
                                 #ifdef  _AsPi13_
                                  ,{ "AsPi13", &PiS_c[13].all }
                                 #endif
                                 #ifdef  _AsPi14_
                                  ,{ "AsPi14", &PiS_c[14].all }
                                 #endif
                                 #ifdef  _AsPi15_
                                  ,{ "AsPi15", &PiS_c[15].all }
                                 #endif
                                } ;
const word _Nin  = sizeof(Nstin)/sizeof(const struct Stin) ;

//-------------------------------------------------

const struct DAC_output_tab1 DAC_tab1  [] =                  // F16K | //FR
       {                                                     //------|-------
         { "DAC0-sys ", &_or.dac_numb[0], _DAC_setka_max  }, // PPG4 | //DA0
         { "DAC1     ", &_or.dac_numb[1], _DAC_setka_max  }, // PPG0 | //DA1
         { "DAC2     ", &_or.dac_numb[2], _DAC_setka_max  }  // PPG5 | //PPG4
       #ifdef  _PPG_for_DAC3
        ,{ "DAC3     ", &_or.dac_numb[3], _DAC_setka_max  }
       #endif
       #ifdef  _PPG_for_DAC4
        ,{ "DAC4     ", &_or.dac_numb[4], _DAC_setka_max  }
       #endif
       #ifdef  _PPG_for_DAC5
        ,{ "DAC5     ", &_or.dac_numb[5], _DAC_setka_max  }
       #endif
       #ifdef  _PPG_for_DAC6
        ,{ "DAC6     ", &_or.dac_numb[6], _DAC_setka_max  }
       #endif
       #ifdef  _PPG_for_DAC7
        ,{ "DAC7     ", &_or.dac_numb[7], _DAC_setka_max  }
       #endif
       } ;
const word _DAC_Ntab1  = sizeof(DAC_tab1)/sizeof(const struct DAC_output_tab1) ;

//-------------------------------------------------

_x_far const struct Ck  Nckl [ ] =
  {
   { "�C         \r", _Skor_nom(-1.1), _Skor_nom(+1.1), _Skor_Nom  , _Skor_nom(0.01) },
   { "�T         \r", _Id_nom( -2.0) , _Id_nom(+2.0)  , _Id_Nom    , _Id_nom(0.01)   },
#ifdef _Rev_Pola
   { "���-����.  \r", _Iv_nom(-2.0)  , _Iv_nom(2.0)   , _Iv_Nom    , _Iv_nom(0.01)   },
#else
   { "���-����.  \r", _Iv_nom(0.0)   , _Iv_nom(2.0)   , _Iv_Nom    , _Iv_nom(0.01)   },
#endif
   { "�����      \r", _Grad(0.0)     , _Grad(179.0)   , _Grad(1.0) , _Grad(0.05)     },
// 09.06.2020 15:35 ��.���. � "F2_drv.c", "Upravl.c", "Reg_eds.c", "Cikl.h".
// { "����       \r", _EDS_nom(0.0)  , _EDS_nom(+1.0) , _EDS_Nom   , _EDS_nom(0.01)  },
   { "����       \r", _Grad(0.0)     , _Grad(179.0)   , _Grad(1.0) , _Grad(0.05)     },
   { "��         \r", _Grad(-179.0)  , _Grad(179.0)   , _Grad(1.0) , _Grad(0.05)     }
#ifdef _SIFU2_
  ,{ "�T1        \r", _Id_nom( -2.0) , _Id_nom(+2.0)  , _Id_Nom    , _Id_nom(0.01)   },
   { "�T2        \r", _Id_nom( -2.0) , _Id_nom(+2.0)  , _Id_Nom    , _Id_nom(0.01)   }
#endif
  } ;
const word _Nck  = sizeof(Nckl)/sizeof(const struct Ck) ;

//-------------------------------------------------

#ifdef _AVTONASTR
// ��� ������������� ��
_x_far const struct Vybor AN_RT [] =
  {
   { "\r�����-� ����.�T", 0 }
 //{ "\r�����-� ��     ", 1 }
  } ;
const word _Nanastr  = sizeof(AN_RT)/sizeof(const struct Vybor) ;
#endif

//-------------------------------------------------

_x_far const struct Vybor Vyb [] = { // ������� � ���-�� ����� � F2_DRV.C :
                                 { "\r����-���-�1    ",  3 },//k10 },
                                 { "\r����-���-�2    ",  4 },//k11 },

                                 { "\r��-���-�1      ",  5 },//k12 },
                                 { "\r��-���-�2      ",  6 },//k13 },
#ifdef _SIFU2_
                                 { "\r��1-���-�1     ", 44 },//k80 },
                                 { "\r��1-���-�2     ", 45 },//k85 },
                                 { "\r��2-���-�1     ", 46 },//k90 },
                                 { "\r��2-���-�2     ", 47 },//k95 },
#endif

                              // { "\r���-���        ",  8 },//k15 },
#ifdef _Vozb_KTE
                                 { "\r�����-���      ",  9 },//k16 },
#endif
#ifdef   _AVTONASTR
                                 { "\r�������������  ",  25},//k60a},
#endif
#ifdef   _NARABOTKA
                                 { "\r�����.���������",  33},//k67 },
#endif
#ifdef _SELS_NULL
                                 { "\r���.���� �����.", 37 },//k71 },
#endif
                                 { "\r�����.'F#->If#'",  7 },//k14 },
                                 { "\r����� �������  ", 11 },//k30 },

                                 { "\r������� �����  ", 10 },//k17 }
                                 { "\r��������� �����", 48 } //k96 ��� ��������� ����� � "�������" 18.05.2020
                               } ;
const word _Nvyb =  sizeof(Vyb)/sizeof(const struct Vybor) ;
//----------------------------------------

_x_far const struct NCx NC [] = {
                                   { "A1-���������. ", _Case ( 'A' , '1' ) },
                                   { "A7-���.�����. ", _Case ( 'A' , '7' ) },
                                   { "A8-���.������.", _Case ( 'A' , '8' ) },
                                   { "AE-����.�����.", _Case ( 'A' , 'E' ) },
                                   { "A6-���������. ", _Case ( 'A' , '6' ) },
#ifdef _CombRedact
                                   { "F1-����.�����.", _Case ( 'F' , '1' ) },
#endif
                                   { "F2-�������.   ", _Case ( 'F' , '2' ) },
                                 //{ "A5-�����.����a", _Case ( 'A' , '5' ) }, // 18.05.2020
                                   { "FA-�������.   ", _Case ( 'F' , 'A' ) },
                                   { "A4-���� ���.  ", _Case ( 'A' , '4' ) },
                                   { "A9-���� ���.  ", _Case ( 'A' , '9' ) },
                                   { "AA-���� ���.  ", _Case ( 'A' , 'A' ) },
                                   { "AB-���� ����. ", _Case ( 'A' , 'B' ) },
                                   { "F-�������.    ", _Case ( 'F' ,  0  ), 9 },
                                   { "F0-����������p", _Case ( 'F' , '0' ) },
#ifdef _Sld_cond
                                   { "FC-���.������p", _Case ( 'F' , 'C')  },
#endif
                                 //{ "F1-����.      ", _Case ( 'F' , '1' ) },
#ifdef _JOURNAL
                                   { "AC-�����.����.", _Case ( 'A' , 'C' ) },
                                   { "FB-������.    ", _Case ( 'F' , 'B' ) },
#endif
#ifdef  _TEST_RAM_INCLUDE
                                   { "F3-���� ���.  ", _Case ( 'F' , '3' ) },
#endif
                                   { "F4-���� ����. ", _Case ( 'F' , '4' ), 9 },// ��� �����������.
                                   { "F5-�����.����.", _Case ( 'F' , '5' ) },
                                   { "F6-����.      ", _Case ( 'F' , '6')  },
                                   { "F7-����.�����.", _Case ( 'F' , '7')  },
                                   { "AD-����� ���. ", _Case ( 'A' , 'D' ) },
                                   { "F8-� �������. ", _Case ( 'F' , '8' ) },
                                   { "F9-�����.�����", _Case ( 'F' , '9' ) },
                                   { "Link          ", _Case ( 'I' ,  0  ), 9 },// ��� �����������.
#ifndef _CM3_
                                   { "J-RW_I2C      ", _Case ( 'J' ,  0  ), 9 },// ��� �����������.
#endif
                                   { "AF-������     ", _Case ( 'A' , 'F' ) },
#ifdef _NET_IRQ
//09.06.2020 13:17                 { "FD-���� DP.   ", _Case ( 'F' , 'D' ) },
                                   { "B6-����:�����.", _Case ( 'B' , '6' ) },
                                   { "B7-����:�����.", _Case ( 'B' , '7' ) },
                                   { "B8-����:�����.", _Case ( 'B' , '8' ) },
#endif
                                   { "FE-����.�����a", _Case ( 'F' , 'E' ) }
                           } ;
const word _Nc = sizeof(NC)/sizeof(const struct NCx) ;

//----------------------------------------
#else //_MAIN_INCLUDE
//----------------------------------------

extern const word  _ind_Nom;
extern const word  _ind_100;
extern const word  _ind_1000;
extern const word  _Msk;

extern _x_far const struct STB       stb_avar[];
extern _x_far const struct STB       stb_reg[];
extern _x_far const struct STB       peregr[];
extern _x_far const struct STB       stb_masht[];
extern _x_far const struct STB       stb_serv[];
extern _x_far const struct STB       stb_shtat[];
    #ifdef _A7_Obj_Ust
extern _x_far const struct STB       stb_obj[];
    #endif
extern _x_far const struct STB       stb_Ivz[];
    #ifdef   _AVTONASTR
extern _x_far const struct STB       stb_anastr[];
    #endif

extern const struct UstUzm   Ustav[];
extern const word _MaxNumUstav;

extern _x_far const struct Ind  ind_reg[];
extern _x_far const struct Ind  ind_serv[];
    #ifdef _A6_Obj_Ind
extern _x_far const struct Ind  ind_obj[];
    #endif

extern const struct IndUzm Indicat[];
extern const word _NumInd;

extern _x_far const struct DAC_output_tab2 DAC_tab2[];
extern const word  _DAC_Ntab2;

#ifdef _CombRedact
extern _x_far const struct COMB_MENU comb_menu[];
extern _x_far const word len_comb_menu;
#endif

extern const struct Stout Nstout[];
extern const word _Nout;

extern const struct Stin Nstin[];
extern const word _Nin;

extern const struct DAC_output_tab1 DAC_tab1[];
extern const word _DAC_Ntab1;

extern _x_far const struct Ck  Nckl[];
extern const word _Nck;

    #ifdef   _AVTONASTR
extern _x_far const struct Vybor AN_RT[];
extern const word _Nanastr;
    #endif

extern _x_far const struct Vybor Vyb[];
extern const word _Nvyb;

extern _x_far const struct NCx NC[];
extern const word _Nc;

//----------------------------------------
#endif   //MAIN_INCLUDE
//----------------------------------------

#endif   //msg_tabl_h
