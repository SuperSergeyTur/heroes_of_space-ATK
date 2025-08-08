
/* ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ КРОМЕ ВСЕГО ПРОЧЕГО ТЕКСТЫ АВАРИЙНЫХ  */
/*                   И ПРЕДУПРЕДИТЕЛЬНЫХ СООБЩЕНИЙ.  */
/*----------------------------------------------------------------------------*/

#ifndef msg_head
#define msg_head

// Для изменения стандартного наименования КТЭ:
//#undef  _Device_Name_
//#define _Device_Name_ "    -КТЕ5-А-    "

// Наименование программы агрегата :
#define   _PROGRAM_     "   Привод ...   "

// Децимальный номер схемы агрегата:
#define   _DECIMAL_     "A.XXXXXX.XXX-XX "

//----------------------------------------
#ifdef _MAIN_INCLUDE
//----------------------------------------

//----- Наименования агрегатов для областей уставок ------

const char *const Tabl_name_ust[_kol_obl]  =
 {
  "1.Двигатель "
//"2.Балласт   "
//"1.12-пульс.  ",
//"2.6-п.ШС1,ШС2",
//"3.6-п.ШС3,ШС4"
 };

//-------------- А8 - Уставки битовые --------------------

_x_far const struct Bits    bts[] =
  {
      _KTE_A8_Cfg1 ,
      _KTE_A8_Cfg2 ,
#ifdef _RVId
      _KTE_A8_CfgRVId ,
#endif
#ifdef  _KTE_A8_ConfigObj
    { "Kонфиг.обкт." , (w*)&_or.CfgO.all,  16 ,
                               { "резерв0     ",
                                 "резерв1     ",
                                 "резерв2     ",
                                 "резерв3     ",
                                 "резерв4     ",
                                 "резерв5     ",
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
      _KTE_A8_Isp  ,
      _KTE_A8_Sk   ,
#ifdef _Po0_INVERT      // Имеется возможность инверсии выходных сигналов .
    { "Po0-инверт  " , &_r.Po0_Normal,  6 ,
                               { "K1-Авария   ",
                                 "K3-Предупр. ",
                                 "K2-Готовн.  ",
                                 "резерв3     ",
                                 "резерв4     ",
                                 "резерв5     " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 /*, 0x40 , 0x80*/ },
       (w*)&_Msk ,1
    },
#endif
#ifdef _AsPo_INVERT     // Имеется возможность инверсии выходных сигналов .
    { "AsPo0-инв.  " , &_or.PoS_Normal[0],  8 ,
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
    { "Pi0-инверт  " , &_r.Pi0_Normal,  8 ,
                               { "2P24        ",
                                 "1QK         ",
                                 "1B1         ",
                                 "2B1         ",
                                 "3B1         ",
                                 "4B1         ",
                                 "1GL         ",
                                 "Дист.Сброс  " },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#ifdef  _Pi1_
      _KTE_A8_Pi1 ,
#endif
#ifdef  _AsPi0_
    { "AsPi0-инв.  " , &_or.PiS_Normal[0],  8 ,
                               { "1VR         ",
                                 "Внеш.авария ",
                                 "Разреш.вкл. ",
                                 "Вент.двиг.  ",
                                 "1SQ         ",
                                 "резерв5     ",
                                 "Возб.ТГ     ",
                                 "резерв7     "
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi1_
    { "AsPi1-инв.  " , &_or.PiS_Normal[1],  8 ,
                               { "ИЗУ-Больше  ",
                                 "ИЗУ-Меньше  ",
                                 "Работа/Толч.",
                                 "резерв3     ",
                                 "Толч.Вперед ",
                                 "Толч.Назад  ",
                                 "Снять Задан.",
                                 "Гашен.поля  "
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi2_
    { "AsPi2-инв.  " , &_or.PiS_Normal[2],  1 ,
                               {
                                 "резерв      ",
                                 },
      { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },
       (w*)&_Msk ,1
    },
#endif
#ifdef  _AsPi3_
    { "AsPi3-инв.  " , &_or.PiS_Normal[3],  1 ,
                               {
                                 "резерв      ",
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
                                 #ifdef  _Ch13_Mux
                                   _A4_ADC_Ch13_Mux_list,
                                 #endif
                                   { _ACh14_txt    , &_ar.n14_ach  },
                                 #ifdef  _Ch14_Mux
                                   _A4_ADC_Ch14_Mux_list,
                                 #endif
                                   { _ACh15_txt    , &_ar.n15_ach  },
                                 #ifdef  _Ch15_Mux
                                   _A4_ADC_Ch15_Mux_list,
                                 #endif
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
#define  _Av_Id_sum_Max        ( 0x04000000ul )  //_Av_PUM
#define  _Av_NoSynch2          ( 0x08000000ul )

#define  _Av_DC_Circuit        ( 0x10000000ul )
#define  _Av_Smazka_Podsh      ( 0x20000000ul )
#define  _Av_MasloSmazka       ( 0x40000000ul )
#define  _Av_Vent_Dvig         ( 0x80000000ul )

    //    Маски предупреждений:
    //  побитово соответствуют регистру "Reg_PreduprMsg" и
    //  таблице "Tabl_PreduprMsg[32]".
#define  _Pr_All               ( 0xFFFFFFFFul )

#define  _Pr_Izm_T             ( 0x00000001ul )
#define  _Pr_Podano_ZSk        ( 0x00000002ul )
#define  _Pr_Skor_NoNull       ( 0x00000004ul )
#define  _Pr_Stoyanka          ( 0x00000008ul )

#define  _Pr_Insulat           ( 0x00000010ul )
//#define  _Pr_                ( 0x00000020ul ) // _Pr_AR1
#define  _Pr_BV1               ( 0x00000040ul )
#define  _Pr_Teplo             ( 0x00000080ul )

#define  _Pr_DZVA              ( 0x00000100ul )
#define  _Pr_DZVK              ( 0x00000200ul )
#define  _Pr_DZVA2             ( 0x00000400ul )
#define  _Pr_DZVK2             ( 0x00000800ul )

#define  _Pr_P24               ( 0x00001000ul )
#define  _Pr_P12               ( 0x00002000ul )
#define  _Pr_N12               ( 0x00004000ul )
#define  _Pr_BK1               ( 0x00008000ul )

#define  _Pr_Perecl_DS         ( 0x00010000ul )
#define  _Pr_WDT               ( 0x00020000ul )
//#define  _Pr_                ( 0x00040000ul )
//#define  _Pr_                ( 0x00080000ul )

//#define  _Pr_                ( 0x00100000ul ) // _Pr_OffsetAch
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

#define  _Av2_Id2_Max          ( 0x00000001ul )  // Для 12-ти пульсного СИФУ .
#define  _Av2_1P               ( 0x00000002ul )
#define  _Av2_2P               ( 0x00000004ul )
#define  _Av2_AK2              ( 0x00000008ul )

#define  _Av2_SQ1              ( 0x00000010ul )
#define  _Av2_AM1              ( 0x00000020ul )
#define  _Av2_RV1              ( 0x00000040ul )
#define  _Av2_QKDT             ( 0x00000080ul )

#define  _Av2_Tmax2            ( 0x00000100ul )
#define  _Av2_Tmin2            ( 0x00000200ul )
#define  _Av2_AM2              ( 0x00000400ul )
#define  _Av2_SF3              ( 0x00000800ul )

#define  _Av2_BK2              ( 0x00001000ul )
#define  _Av2_MB1              ( 0x00002000ul )
#define  _Av2_AT               ( 0x00004000ul )
#define  _Av2_AF2              ( 0x00008000ul )

#define  _Av2_Id1Max           ( 0x00010000ul )  // Для РВId 2х якорей через возбуждение .
#define  _Av2_Id2Max           ( 0x00020000ul )
#define  _Av2_Iv2_Min          ( 0x00040000ul )
#define  _Av2_GL2              ( 0x00080000ul )

#define  _Av2_t_Trans          ( 0x00100000ul )
#define  _Av2_KP               ( 0x00200000ul )
#define  _Av2_KP2              ( 0x00400000ul )
#define  _Av2_AT2              ( 0x00800000ul )

#define  _Av2_BV2              ( 0x01000000ul )
#define  _Av2_KFV_VKask        ( 0x02000000ul )
#define  _Av2_2PR1             ( 0x04000000ul )
#define  _Av2_2PR2             ( 0x08000000ul )

#define  _Av2_Izm_T            ( 0x10000000ul )
#define  _Av2_VAT              ( 0x20000000ul )
#define  _Av2_KF_VKask2        ( 0x40000000ul )
#define  _Av2_KF_VKask         ( 0x80000000ul )

    //    Маски предупреждений2:
    //  побитово соответствуют регистру "Reg_PreduprMsg2" и
    //  таблице "Tabl_PreduprMsg2[32]".

#define  _Pr2_PT               ( 0x00000001ul )
#define  _Pr2_AF2P             ( 0x00000002ul )
#define  _Pr2_BV2              ( 0x00000004ul )
#define  _Pr2_NoObjPrg         ( 0x00000008ul )

#define  _Pr2_No_PereclMost    ( 0x00000010ul )
#define  _Pr2_PT2              ( 0x00000020ul )
#define  _Pr2_2PR1             ( 0x00000040ul )
#define  _Pr2_Ttr_predupr      ( 0x00000080ul )

#define  _Pr2_ProbM4_VT11_24   ( 0x00000100ul )  //_Pr2_SFV1
#define  _Pr2_ProbM4_VT12_25   ( 0x00000200ul )  //_Pr2_SFV2
#define  _Pr2_ProbM4_VT13_26   ( 0x00000400ul )
#define  _Pr2_ProbM4_VT14_21   ( 0x00000800ul )

#define  _Pr2_ProbM4_VT15_22   ( 0x00001000ul )
#define  _Pr2_ProbM4_VT16_23   ( 0x00002000ul )
#define  _Pr2_ProbM3_VT11_24   ( 0x00004000ul )
#define  _Pr2_ProbM3_VT12_25   ( 0x00008000ul )

#define  _Pr2_ProbM3_VT13_26   ( 0x00010000ul )
#define  _Pr2_ProbM3_VT14_21   ( 0x00020000ul )
#define  _Pr2_ProbM3_VT15_22   ( 0x00040000ul )
#define  _Pr2_ProbM3_VT16_23   ( 0x00080000ul )

#define  _Pr2_ProbM2_VT11_24   ( 0x00100000ul )
#define  _Pr2_ProbM2_VT12_25   ( 0x00200000ul )
#define  _Pr2_ProbM2_VT13_26   ( 0x00400000ul )
#define  _Pr2_ProbM2_VT14_21   ( 0x00800000ul )

#define  _Pr2_ProbM2_VT15_22   ( 0x01000000ul )
#define  _Pr2_ProbM2_VT16_23   ( 0x02000000ul )
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

#define  _Srv2_VedomOtkl       ( 0x01000000ul )
#define  _Srv2_NoReadObj_i2c   ( 0x02000000ul )
#define  _Srv2_NeisprQK1_bk    ( 0x04000000ul )
#define  _Srv2_Modbus          ( 0x08000000ul )

#define  _Srv2_Proboy_Tyr      ( 0x10000000ul )
#define  _Srv2_ZashProboy_Tyr  ( 0x20000000ul )
#define  _Srv2_VeduschOtkl     ( 0x40000000ul )
#define  _Srv2_RTC_Err         ( 0x80000000ul )

/*------------------------------------------------*/

#ifdef _TRETIY_REG
    //    Маски аварий3:
    //  побитово соответствуют регистру "Reg_AvarMsg3" и
    //  таблице "Tabl_AvarMsg3[32]".

#define  _Av3_KF_VKask3        ( 0x00000001ul )
#define  _Av3_KF_VKask4        ( 0x00000002ul )
#define  _Av3_KP3              ( 0x00000004ul )
#define  _Av3_KP4              ( 0x00000008ul )

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

#define    _Pr3_TokRaspr1S_A   ( 0x00000001ul )
#define    _Pr3_TokRaspr1S_B   ( 0x00000002ul )
#define    _Pr3_TokRaspr1S_C   ( 0x00000004ul )
//#define  _Pr3_               ( 0x00000008ul )

#define    _Pr3_TokRaspr2S_A   ( 0x00000010ul )
#define    _Pr3_TokRaspr2S_B   ( 0x00000020ul )
#define    _Pr3_TokRaspr2S_C   ( 0x00000040ul )
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

#define  _Srv3_BK1             ( 0x00000001ul )
#define  _Srv3_BK2             ( 0x00000002ul )
#define  _Srv3_BK3             ( 0x00000004ul )
#define  _Srv3_BK4             ( 0x00000008ul )

#define  _Srv3_BK5             ( 0x00000010ul )
#define  _Srv3_BK6             ( 0x00000020ul )
#define  _Srv3_BK7             ( 0x00000040ul )
#define  _Srv3_BK8             ( 0x00000080ul )

#define  _Srv3_BK9             ( 0x00000100ul )
#define  _Srv3_BK10            ( 0x00000200ul )
#define  _Srv3_BK11            ( 0x00000400ul )
#define  _Srv3_BK12            ( 0x00000800ul )

#define  _Srv3_BK13            ( 0x00001000ul )
#define  _Srv3_BK14            ( 0x00002000ul )
#define  _Srv3_BK15            ( 0x00004000ul )
#define  _Srv3_BK16            ( 0x00008000ul )

#define  _Srv3_BK17            ( 0x00010000ul )
#define  _Srv3_BK18            ( 0x00020000ul )
#define  _Srv3_BK19            ( 0x00040000ul )
#define  _Srv3_BK20            ( 0x00080000ul )

#define  _Srv3_BK21            ( 0x00100000ul )
#define  _Srv3_BK22            ( 0x00200000ul )
#define  _Srv3_BK23            ( 0x00400000ul )
#define  _Srv3_BK24            ( 0x00800000ul )

#define  _Srv3_NeisprPerekl    ( 0x01000000ul )
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
#ifdef  _SIFU2_
         "Id1-макс.       ",  //"Id-макс-ведущегo",  //"Id-макс.        ",
#else
         "Id-макс.        ",
#endif
#ifndef  bi_2B1  //bi_GerconAC2
         "Внутреннее КЗ.  ", // "Геркон/Iтт-макс.", //"Герк.перем.тока.",
         "Внешнее КЗ.     ", // "Герк.пост.тока. ",
#else
         "ВнутреннееКЗ-ШВ1", // "Герк/Iтт-максШВ1", //"Геркон ШС1,2.   ",
         "ВнутреннееКЗ-ШВ2", // "Герк/Iтт-максШВ2",//"Геркон ШС3,4.   ",
#endif
         "Центробежник.   ",  //a1-03

         "Стоянка под ток.",
         "Возбудитель-1GL.",
         "E-макс.         ",
         "N-макс.         ",

//#ifdef bi_AK2
         "Откл.Q1-1AK.    ",  //a1-08
//#else
//       "Силовая цепь-1AK",  //a1-08
//#endif
//#ifdef  bi_TK1
//       "Перегрев-1ТК.   ",  //a1-09
//#else //bi_BV1
         "Охлаждение-1BV. ",  //a1-09
//#endif
         "ПЗП-1AF.        ", //a1-10
         "Оперативное откл", // "Опер.откл.-1VR. ",  //a1-11

         "Перегрузка.     ",
         "Нет синхр. Uсн. ", // "Нет синхр.'TC1'.",
         "Tсинх. Uсн-макс.", // "Tсинх'TC1'-макс.",
         "Tсинх. Uсн-мин. ", // "Tсинх'TC1'-мин. ",

         "Самоотключение. ",
         "If-мин.         ",
         "If-макс.        ",
         "Питание 2P24.   ",

         "АСУТП авар.откл.",
         "Внешняя авария. ",
         "Неиспр.дат.скор.",
         "Возбуждение ТГ. ",

         "Предохр.сил.-1PR",
         "Предохр.сил.-2PR",
         "Id-сум-макс.    ",  //"Питание ус.мощн.",
         "Нет синхр. Uсил.", // "Нет Uсил/СинхTC2",

         "Нет силов.цепи. ",
         "Смазка подшипн. ",
         "Маслосмаз.двиг. ",
         "Вентиляция двиг." },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_PreduprMsg". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_PreduprMsg[32]  =
       { "BK-нагрев.      ",
         "Подано задание. ",
         "Скор.не нулевая.",
         "Стоянка под ток.",

         "Изоляция.       ",
         "p1-05.          ", // "Изоляция-1AR.   ",
#ifdef bi_PT // Контроль перегрева тиристоров .
         "Неиспр.вент.-1BV",
#else
         "Охлаждение-1BV. ",
#endif
         "Перегрузка.     ",

         "Нет ДCВА-ведущ. ",
         "Нет ДCВК-ведущ. ",
         "Нет ДCВА-ведом. ",
         "Нет ДCВК-ведом. ",

         "Питание P24.    ",
         "Питание P12.    ",
         "Питание N12.    ",
         "Перегрев-1ВК.   ",

         "ДС перекл.на ЭДC",
         "Сброс WatchDog. ",
         "p1-18.          ",
         "p1-19.          ",

         "p1-20.          ", // "Смещение АЦП.   ",
         "Сервисная прогр.",
         "КТЭ переключен. ",
         "АСУТП предупр.  ",

         "ПЗП-1AF.        ",
         "Предохр.сил.-1PR",
         "Обрыв зад.4-20мА",
         "Нет Разреш. Вкл.", // "Разреш. Вкл.КТЭ.",

         "Приняты тип.уст.",
         "Смазка подшипн. ",
         "Маслосмаз.двиг. ",
         "Вентиляция двиг."
     },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_ServiceMsg". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_ServiceMsg[32]  =
       { "Нет номинал.ЭДС.",
         "Наложен ЭМ торм.", // "МТ наложен-1GY. ",
         "Наладочный режим",
         "Задание с пультa",

         "АН остановлена! ",
         "Te определена.  ",
         "Tm определена.  ",
         "Нет измер.Id-гр.",

         "Ti,Kp опред-ны. ",
         "Не снят If!     ",
         "Нет зап.наработ.",
         "Нет чтн.наработ.",

         "Нет снижения Id.",
         "Нет нарастан. If",
         "s1-14.          ", // "Смещение'Id2'.  ",
         "s1-15.          ", // "Смещение'Id2-cp'",

         "s1-16.          ", // "Смещение'Id'.   ",
         "s1-17.          ", // "Смещение'Id-ср'.",
         "s1-18.          ", // "Смещение'Ud'.   ",
         "s1-19.          ", // "Неисправно ОЗУ  ",

         "Нет АСУТП-Старт.",
         "Нет усл. реверсa",
         "s1-22.          ", // "Нет чтения врем.",
         "s1-23.          ", // "Нет записи врем.",

         "Нет чтения уст. ",
         "Нет записи уст. ",
         "Контр.сумма уст.",
         "Нет АСУТП-Связи.",

         "Вкл.контактор ДT",
         "Сброс CAN.      ",
         "Ошибка в устав. ",
         "Нет АСУТП-вкл.ЛK"
     },

/*------------------------------------------------*/

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_AvarMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
  //const char *const Tabl_AvarMsg2[32]  =
       {
         "Id2-макс.       ",  //"Id-макс-ведомогo",
         "Питание 1Р.     ",
         "Питание 2Р.     ",
//#ifndef  _SIFU2_
//       "Откл.Q2-2AK.    ",
//#else
         "Откл.Q1-2AK.    ",
//#endif

         "Дверн.блок.-1SQ.",
         "Нет Uсил.-1AM.  ", // "Силов.напр.-1AM.",
         "РДШ-1RV.        ",
         "Нет откл.конт.ДT",

         "Tсинх. Uсил-макc", // "Tсинх'TC2'-макс.",
         "Tсинх. Uсил-мин.", // "Tсинх'TC2'-мин. ",
         "Нет Uсил.-2AM.  ", // "Силов.напр.-2AM.",
         "Вспом.устр.-SF3.",

         "Перегрев-2BK.   ",
         "МВ отключен-1МВ.", // "Масл.выкл.-1MB. ",
         "Перегрев ШС1-AT1",  //"Перегрев тир.-AT",
         "ПЗП-2AF.        ",

         "Id1-макс.       ",
         "Id2-макс.       ",
         "If2-мин.        ",
         "Возбудитель-2GL.",

         "ПерегревСилТранc", // "Защита трансф-рa",
         "Пит.усил.имп-KP1",
         "Пит.усил.имп-KP2",
         "Перегрев ШС2-AT2",

         "Неиспр.вент.-2BV",
         "Пред.ВыхКаскВзб.",
         "Пред.силШС2-1PR2",
         "Пред.силШС2-2PR2",

         "BK-перегрев.    ",
         "Q2-ВАТ отключён.",
         "Пред.ВыхКаск-KF2",
#ifdef bi_KF_VKask2
         "Пред.ВыхКаск-KF1"
#else
         "Предохр.ВыхКаск." //"Предохр.АV1-AV2.",
#endif
       },

     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_PreduprMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
   //const char *const Tabl_PreduprMsg2[32]  =
       {
         "Перегрев ШС1-PT1", //"Перегрев тир.-PT",
         "ПЗП-2AF.        ",
#ifdef bi_PT // Контроль перегрева тиристоров .
         "Неиспр.вент.-2BV",
#else
         "Охлаждение-2BV. ",
#endif
         "Ошибка прогр.   ",

         "Запрет перекл.ШC",
         "Перегрев ШС2-PT2",
         "Пред.силШС2-1PR2",
         "Повыш.темп.тр-рa",

         "Проб.ШС4-V11(24)", //"Откл.авт.-SFV1. ",
         "Проб.ШС4-V12(25)", //"Откл.авт.-SFV2. ",
         "Проб.ШС4-V13(26)",
         "Проб.ШС4-V14(21)",

         "Проб.ШС4-V15(22)",
         "Проб.ШС4-V16(23)",
         "Проб.ШС3-V11(24)",
         "Проб.ШС3-V12(25)",

         "Проб.ШС3-V13(26)",
         "Проб.ШС3-V14(21)",
         "Проб.ШС3-V15(22)",
         "Проб.ШС3-V16(23)",

         "Проб.тM2-V11(24)",                          //"Проб.ШС2-V11(24)",
         "Проб.тM2-V12(25)",                          //"Проб.ШС2-V12(25)",
         "Проб.тM2-V13(26)",                          //"Проб.ШС2-V13(26)",
         "Проб.тM2-V14(21)",                          //"Проб.ШС2-V14(21)",

         "Проб.тM2-V15(22)",                          //"Проб.ШС2-V15(22)",
         "Проб.тM2-V16(23)",                          //"Проб.ШС2-V16(23)",
         "Проб.тM1-V11(24)",  //"Проб.тир.V11(24)",   //"Проб.ШС1-V11(24)",
         "Проб.тM1-V12(25)",  //"Проб.тир.V12(25)",   //"Проб.ШС1-V12(25)",

         "Проб.тM1-V13(26)",  //"Проб.тир.V13(26)",   //"Проб.ШС1-V13(26)",
         "Проб.тM1-V14(21)",  //"Проб.тир.V14(21)",   //"Проб.ШС1-V14(21)",
         "Проб.тM1-V15(22)",  //"Проб.тир.V15(22)",   //"Проб.ШС1-V15(22)",
         "Проб.тM1-V16(23)"   //"Проб.тир.V16(23)"    //"Проб.ШС1-V16(23)"
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
         "DP: Скор.не опр.",
         "DP: Скор - 12Мб ",

         "DP: Скор - 6Мб  ",
         "DP: Скор - 3Мб  ",
         "DP: Скор - 1,5Мб",
         "DP: Скор - 500Кб",

         "DP: Скор - 187Кб",
         "DP: Скор - 93Кб ",
         "DP: Скор - 45Кб ",
         "DP: Скор - 19Кб ",

         "DP: Скор - 9,6Кб",
         "DP: Ошиб.конфиг.",
         "Тир. V1 не откр.",
         "Тир. V2 не откр.",

         "Тир. V3 не откр.",
         "Тир. V4 не откр.",
         "Тир. V5 не откр.",
         "Тир. V6 не откр.",

         "ШС2-отключен.   ",  //"ШС3, ШС4-отключ."
         "Нет чтения прг. ",
         "Неиспр.б/к QK1. ",
         "Ошибка Modbus   ",

         "Пробой сил.тир. ",
         "Защ.при тестир. ",
         "ШС1-отключен.   ",  //"ШС1, ШС2-отключ.",
         "Нет настр.часов."
     }

#ifdef _TRETIY_REG
     /*   Матрица из 32-х сообщений соответствующих побитово битам регистра
      * "Reg_AvarMsg2". Нулевое сообщение в матрице соответствует самому
      * младшему, 0-му биту регистра, а последнее, 31-е сообщение в матрице
      * соответствует самому старшему, 31-му биту регистра.
      */
  //const char *const Tabl_AvarMsg2[32]  =
      ,{
         "Пред.ВыхКаск-KF3",
         "Пред.ВыхКаск-KF4",
         "Пит.усил.имп-KP3",
         "Пит.усил.имп-KP4",

         "РасцепитВАТ-1RV.",
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
         "Токорспр.ШС1,2фA",
         "Токорспр.ШС1,2фB",
         "Токорспр.ШС1,2фC",
         "p3-03.",

         "Токорспр.ШС3,4фA",
         "Токорспр.ШС3,4фB",
         "Токорспр.ШС3,4фC",
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
         "ВК1             ",
         "ВК2             ",
         "ВК3             ",
         "ВК4             ",

         "ВК5             ",
         "ВК6             ",
         "ВК7             ",
         "ВК8             ",

         "ВК9             ",
         "ВК10            ",
         "ВК11            ",
         "ВК12            ",

         "ВК13            ",
         "ВК14            ",
         "ВК15            ",
         "ВК16            ",

         "ВК17            ",
         "ВК18            ",
         "ВК19            ",
         "ВК20            ",

         "ВК21            ",
         "ВК22            ",
         "ВК23            ",
         "ВК24            ",

         "Неиспр.перекл.  ",
         "s3-25.          ",
         "s3-26.          ",
         "s3-27.          ",

         "s3-28.          ",
         "s3-29.          ",
         "s3-30.          ",
         "s3-31.          "
     }
#endif    // _TRETIY_REG
};
//----------------------------------------
#endif    // _MSG_INCLUDE
//----------------------------------------

#endif    // msg_head
