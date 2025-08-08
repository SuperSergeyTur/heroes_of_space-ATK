
/* ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ КРОМЕ ВСЕГО ПРОЧЕГО ТЕКСТЫ АВАРИЙНЫХ  */
/*                   И ПРЕДУПРЕДИТЕЛЬНЫХ СООБЩЕНИЙ.  */
/*----------------------------------------------------------------------------*/

#ifndef msg_head
#define msg_head

// Для изменения стандартного наименования КТЭ:
//#undef  _Device_Name_
//#define _Device_Name_ "     -ATK5-     "

// Наименование программы агрегата :
#define   _PROGRAM_     "  Випрямляч     "

// Децимальный номер схемы агрегата:
#define   _DECIMAL_     "  A.656457.749  "

//----------------------------------------
#ifdef _MAIN_INCLUDE
//----------------------------------------

//----- Наименования агрегатов для областей уставок ------

const char *const Tabl_name_ust[_kol_obl]  =
 {
  "Ротор.Випр."
//"2.Балласт  "
 };

//-------------- А8 - Уставки битовые --------------------

_x_far const struct Bits    bts[] =
  {
      _KTE_A8_Cfg1 ,
    //_KTE_A8_Cfg2 ,
#ifdef  _KTE_A8_ConfigObj
    { "Kонфіг.обкт." , (w*)&_or.CfgO.all,  5  ,
                               { "След у ШІМ  ",
                                 "Увімк.КЗ рот",
                                 "F рот за ДП ",
                                 "Увімкн.СімДП",
                                 "Увім.Філ.ДП ",
                                 "Старт РС    ",
                                 "резерв6     ",
                                 "резерв7     ",

                                 "резерв8     ",
                                 "резерв9     ",
                                 "резерв10    ",
                                 "резерв11    ",
                                 "резерв12    ",
                                 "резерв13    ",
                                 "резерв14    ",
                                 "резерв15    " },
      { 0x0001, 0x0002, 0x0004, 0x0008, 0x0010 , 0x0020 , 0x0040 , 0x0080 ,
        0x0100, 0x0200, 0x0400, 0x0800, 0x1000 , 0x2000 , 0x4000 , 0x8000 },
       (w*)&_Msk ,2
    },
#endif
      _KTE_A8_Prg  ,
    //_KTE_A8_Isp  ,
      _KTE_A8_Sk   ,
#ifdef _Po0_INVERT      // Имеется возможность инверсии выходных сигналов .
    { "Po0-інверт. " , &_r.Po0_Normal,  6 ,
                               { "резерв0     ",
                                 "K9-Стан ВВ1 ",
                                 "резерв2     ",
                                 "резерв3     ",
                                 "резерв4     ",
                                 "резерв5     " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 /*, 0x40 , 0x80*/ },
       (w*)&_Msk ,1
    },
#endif
#ifdef _AsPo_INVERT     // Имеется возможность инверсии выходных сигналов .
    { "AsPo0-інв.  " , &_or.PoS_Normal[0],  8 ,
                               { "резерв0     ",
                                 "резерв1     ",
                                 "резерв2     ",
                                 "резерв3     ",
                                 "резерв4     ",
                                 "резерв5     ",
                                 "резерв6     ",
                                 "резерв7     " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
    { "Pi0-інверт. " , &_r.Pi0_Normal,  8 ,
                               { "2P24        ",
                                 "резерв1     ",
                                 "FF1-варис.РВ",
                                 "F-запоб.РВ  ",
                                 "1SQ-ДверіШРВ",
                                 "резерв5     ",
                                 "резерв6     ",
                                 "Дист.Скидан." },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#ifdef  _Pi1_
    { "Pi1-інверт. " , &_r.Pi1_Normal,  8 ,     /* CM3 */
                               {
                                 "резерв0/INT7", //"KP3-КЗ /INT7",
                                 "net    /INT2",
                                 "резерв2/INT5", //"KF2-вып/INT5",
                                 "резерв3/INT6", //"KP2-вып/INT6",
                                 "резерв4/INT4",
                                 "резерв5/INT3", //"KF3-КЗ /INT3",
                                 "Iсі-max/INT0",
                                 "Iрв-max/INT1"
                               },
        { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
         (w*)&_Msk ,1
      },
#endif
#ifdef  _AsPi0_
    { "AsPi0-інв.  " , &_or.PiS_Normal[0],  1 ,
                               {
                                 "резерв      ",
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi1_
    { "AsPi1-інв.  " , &_or.PiS_Normal[1],  1 ,
                               {
                                 "резерв      ",
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi2_
    { "AsPi2-інв.  " , &_or.PiS_Normal[2],  1 ,
                               {
                                 "резерв      ",
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi3_
    { "AsPi3-інв.  " , &_or.PiS_Normal[3],  1 ,
                               {
                                 "резерв      ",
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
  };      /* Количество уставок в таблице */
const word _MaxNumBUst  = sizeof(bts)/sizeof(const struct Bits) ;

//-------- А4 - Таблица аналоговых каналов ---------------
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
#define  _Av_GerconSN          ( 0x00000008ul ) // _Av_CentroBegnik

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

    //    Маски предупреждений:
    //  побитово соответствуют регистру "Reg_PreduprMsg" и
    //  таблице "Tabl_PreduprMsg[32]".
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

#define  _Pr_t_Trans           ( 0x00100000ul )  // _Pr_OffsetAch
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

    //    Маски служебных сообщений:
    //  побитово соответствуют регистру "Reg_ServiceMsg" и
    //  таблице "Tabl_ServiceMsg[32]".
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

    //    Маски аварий2:
    //  побитово соответствуют регистру "Reg_AvarMsg2" и
    //  таблице "Tabl_AvarMsg2[32]".

//#define  _Av2_               ( 0x00000001ul ) // _Av2_Id2_Max// Для 12-ти пульсного СИФУ .
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

#define  _Av2_Id1Max           ( 0x00010000ul )  // Для РВId 2х якорей через возбуждение .
#define  _Av2_Id2Max           ( 0x00020000ul )
#define  _Av2_Iv2_Min          ( 0x00040000ul )
#define  _Av2_GL2              ( 0x00080000ul )

#define  _Av2_t_Trans          ( 0x00100000ul )
#define  _Av2_KP               ( 0x00200000ul )
#define  _Av2_KP_KZ            ( 0x00400000ul ) // _Av2_KP2
#define  _Av2_KTE2             ( 0x00800000ul ) // _Av2_MT_Err

#define  _Av2_Fsil_rot         ( 0x01000000ul )
#define  _Av2_KFV_VKask        ( 0x02000000ul )
//#define  _Av2_               ( 0x04000000ul )
//#define  _Av2_               ( 0x08000000ul )

//#define  _Av2_               ( 0x10000000ul )
//#define  _Av2_               ( 0x20000000ul )
#define  _Av2_KF_VKask2        ( 0x40000000ul )
#define  _Av2_KF_VKask         ( 0x80000000ul )

    //    Маски предупреждений2:
    //  побитово соответствуют регистру "Reg_PreduprMsg2" и
    //  таблице "Tabl_PreduprMsg2[32]".

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

    //    Маски служебных сообщений2:
    //  побитово соответствуют регистру "Reg_ServiceMsg2" и
    //  таблице "Tabl_ServiceMsg2[32]".

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
    //    Маски аварий3:
    //  побитово соответствуют регистру "Reg_AvarMsg3" и
    //  таблице "Tabl_AvarMsg3[32]".

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

    //    Маски предупреждений3:
    //  побитово соответствуют регистру "Reg_PreduprMsg3" и
    //  таблице "Tabl_PreduprMsg3[32]".

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

    //    Маски служебных сообщений3:
    //  побитово соответствуют регистру "Reg_ServiceMsg3" и
    //  таблице "Tabl_ServiceMsg3[32]".

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

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_AvarMsg". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
const struct Tabl_MSG  Tabl_Msg =
{
  //const char *const Tabl_AvarMsg[32]  =
       {
         "Id-макс.        ", //"Id-макс-рот.выпр", - 13.06.2021 одно сообщение на оба тока Id и Irot .
#ifndef  bi_2B1  //bi_GerconAC2
         "Iтт-макс-Інвер. ", //"Внутрен.КЗ-Инвер", // "Внутреннее КЗ.  ", // "Геркон/Iтт-макс.", //"Герк.перем.тока.",
         "Iтт-макс-Випр.  ", //"Внутрен.КЗ-Выпр.", // "Внешнее КЗ.     ", // "Герк.пост.тока. ",
#else
         "ВнутрішнєКЗ-ШВ1 ", // "Герк/Iтт-максШВ1", //"Геркон ШС1,2.   ",
         "ВнутрішнєКЗ-ШВ2 ", // "Герк/Iтт-максШВ2",//"Геркон ШС3,4.   ",
#endif
         "Зрив Інвертора. ", // "Центробежник.   ", //a1-03

         "Стоянка під стр.",
         "Збудник-1GL.    ",
         "E-макс.         ",
         "N-макс.         ",

//#ifdef bi_AK2
          "Від.авт.'~'струм", // "Откл.Q1-1AK.    ",  //a1-08
//#else
//      "Силовая цепь-1AK",  //a1-08
//#endif
//#ifdef  bi_TK1
//       "Перегрев-1ТК.   ",  //a1-09
//#else //bi_BV1
         "Охоложден-1BV.  ",  //a1-09
//#endif
         "ПЗП-1AF.        ", //a1-10
         "Оперативне відкл", // "Опер.откл.-1VR. ",  //a1-11

         "Перенавантаж.   ",
         "Немає синх. Uсн.", // "Нет синхр.'TC1'.",
         "Tсинх. Uсн-макс.", // "Tсинх'TC1'-макс.",
         "Tсинх. Uсн-мін. ", // "Tсинх'TC1'-мин. ",

         "Самовідключення ",
         "If-мін.         ",
         "If-макс.        ",
         "Живлення 2P24.  ",

         "АСУТП авар.відкл",
         "Аварійний Стоп. ",  //"Внешняя авария. ",
         "Неспр.дат.швид. ",
         "Збудження ТГ.   ",

         "Запобіж.сил.-1PR",
         "Запобіж.сил.-2PR",
         "Живл.підс.потужн",
         "Немє синхр.Uсил.", // "Нет Uсил/СинхTC2",

         "Немає сил. кола ",
         "Мастило підшипн.",
         "Мастило.двиг.   ",
         "Вентиляція двиг." },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_PreduprMsg". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_PreduprMsg[32]  =
       {
         "p1-00.          ",
         "Подано завдан.  ",
         "Швид.не нулева. ",
         "Стоянка під стр.",

         "Ізоляція.       ",
         "p1-05.          ", // "Изоляция-1AR.   ",
//#ifdef bi_PT // Контроль перегрева тиристоров .
//       "Неиспр.вент.-1BV",
//#else
         "Охолодження-1BV.",
//#endif
         "Перевантаження. ",

         "Немає сигн. ДCВА",
         "Немає сигн. ДCВК",
         "p1-10.",
         "p1-11.",

         "Живлення P24.   ",
         "Живлення P12.   ",
         "Живлення N12.   ",
         "Перегрів выпрям.",  //"Перегрев-1ВК.   ",

         "ДШ перекл.на ЕРC",
         "Скидан.WatchDog.",
         "p1-18.          ",
         "p1-19.          ",

         "ПерегрівСилТранc", // "Смещение АЦП.   ",
         "Службова прогр. ",
         "КТЄ переключен. ",
         "АСУТП поперед.  ",

         "Варистор выпрям.",  //"Варисторы-1AF.  ",
         "Запобіж.сил.-1PR",
         "Обрив зав.4-20мА",
         "Немае дозв.увімк", // "Разреш. Вкл.КТЭ.",

         "Прийняті тип.уст",
         "Мастило підшипн.",
         "Мастило двиг.   ",
         "Вентиляція двиг."
     },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_ServiceMsg". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_ServiceMsg[32]  =
       {
         "Немає ном. ЕРС  ",
         "Наклад. ЕМ гальм", // "МТ наложен-1GY. ",
         "Налагоджув.режим",
         "Завдан. з пульту",

         "АН зупинено     ",
         "Te визначено    ",
         "Tm визначено    ",
         "Немає вим.Id-гр.",

         "Ti,Kp визначено ",
         "Не знято If!    ",
         "Немає зап.напрац",
         "Немає чіт.напрац",

         "Немає зниж Id.  ",
         "Немає нараст. If",
         "s1-14.          ", // "Смещение'Id2'.  ",
         "s1-15.          ", // "Смещение'Id2-cp'",

         "s1-16.          ", // "Смещение'Id'.   ",
         "s1-17.          ", // "Смещение'Id-ср'.",
         "s1-18.          ", // "Смещение'Ud'.   ",
         "s1-19.          ", // "Неисправно ОЗУ  ",

         "Немає АСУТП-Стрт",
         "Немає ум.реверсу",
         "s1-22.          ", // "Нет чтения врем.",
         "s1-23.          ", // "Нет записи врем.",

         "Немає читан. уст",
         "Немає запису уст",
         "Контр.сума уст. ",
         "Немає АСУТП-зв. ",

         "Увім. контакт ДГ",
         "Скидання CAN.   ",
         "Помилка в устав.",
         "Нема АСУТПвкл.ЛK"
     },

/*------------------------------------------------*/

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_AvarMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
  //const char *const Tabl_AvarMsg2[32]  =
       {
         "a2-00.          ", // "Id2-макс.       ",//"Id-макс-ведомогo",
         "a2-01.          ",  // "Питание 1Р.     ",
         "a2-02.          ",  // "Питание 2Р.     ",
         "Відк.авт.'='стр ", // "Откл.Q2-2AK.    ",

         "Дверн.блок.-1SQ.",
         "Немає Uсил.-1AM.", // "Силов.напр.-1AM.",
         "РДШ-1RV.        ",
         "Нема від.конт.ДГ",

         "Tсінх. Uсил-макc", // "Tсинх'TC2'-макс.",
         "Tсінх. Uсил-мин.", // "Tсинх'TC2'-мин. ",
         "a2-10.          ", // "Силов.напр.-2AM.",
         "Допом.прис.-SF3.",

         "Перегрів-2BK.   ",
         "МВ вимкнено-1МВ.", // "Масл.выкл.-1MB. ",
         "Перегрів-AT.    ",
         "a2-15.          ", // "ПЗП-2AF.        ",

         "Id1-макс.       ",
         "Id2-макс.       ",
         "If2-мін.        ",
         "Збудник-2GL.    ",

         "ПерегрівСилТранc", // "Защита трансф-рa",
         "Жив.імп.вип-KP2.",  //"Пит.усил.имп-KP1",
         "Жив.імп.КЗ-KP3. ",  //"Пит.усил.имп-KP2",
         "Авар-Мереж.інвеp",  //"Неисправ.тормоз.",

         "Запобіж.Випрям. ",
         "Зап.Вих Каск Зб.",
         "a2-26.          ",
         "a2-27.          ",

         "a2-28.          ",
         "a2-29.          ",
         "Запоб.імп.КЗ-KF3",  //"Пред.ВыхКаск-KF2",
#ifdef bi_KF_VKask2
         "Зап.імп.вип-KF2 "   //"Пред.ВыхКаск-KF1"
#else
         "Запобіж.ВихКаск." //"Предохр.АV1-AV2.",
#endif
       },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_PreduprMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_PreduprMsg2[32]  =
       {
         "Перегрів-PT.    ",
         "p2-01.          ", // "ПЗП-2AF.        ",
//#ifdef bi_PT // Контроль перегрева тиристоров .
         "p2-02.          ", // "Неиспр.вент.-2BV",
//#else
//         "Охлаждение-2BV. ",
//#endif
         "Помилка.прогр.  ",

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
         "Проб.тир.V11(24)",
         "Проб.тир.V12(25)",

         "Проб.тир.V13(26)",
         "Проб.тир.V14(21)",
         "Проб.тир.V15(22)",
         "Проб.тир.V16(23)"
     },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_ServiceMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_ServiceMsg2[32]  =
       {
         "DP: Wait Param  ",
         "DP: Wait Config ",
         "DP: Data Exchang",
         "DP: Baud Search ",

         "DP: Baud Control",
         "DP: DP Control  ",
         "DP: Швид.не визн",
         "DP: Швид - 12Мб ",

         "DP: Швид - 6Мб  ",
         "DP: Швид - 3Мб  ",
         "DP: Швид - 1,5Мб",
         "DP: Швид - 500Кб",

         "DP: Швид - 187Кб",
         "DP: Швид - 93Кб ",
         "DP: Швид - 45Кб ",
         "DP: Швид - 19Кб ",

         "DP: Швид - 9,6Кб",
         "DP: Пом.конфіг. ",
         "Тир. V1 не відк.",
         "Тир. V2 не відк.",

         "Тир. V3 не відк.",
         "Тир. V4 не відк.",
         "Тир. V5 не відк.",
         "Тир. V6 не відк.",

         "Немає зв. з АР1.",
         "Немає читан. прг",
         "Неспр.б/к QK1.  ",
         "Помилка Modbus  ",

         "Пробій сил.тир. ",
         "Зах.при тестув. ",
         "Немає зв. з ДП. ",
         "Немає налаг. год"
     }

#ifdef _TRETIY_REG
     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_AvarMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
  //const char *const Tabl_AvarMsg2[32]  =
      ,{
         "a3-00.          ",
         "a3-01.          ",
         "a3-02.          ",
         "a3-03.          ",

         "Розчеп ВАТ-1RV. ",
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

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_PreduprMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
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

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_ServiceMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
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
