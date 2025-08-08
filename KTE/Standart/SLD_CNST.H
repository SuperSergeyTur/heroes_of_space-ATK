
/* ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ ИНИЦИАЛИЗАЦИЮ БЛОКА УСТАВОК КОНСТАНТАМИ.  */
/*-------------------------------------------------  */

#ifndef _sld_cnst_h
#define _sld_cnst_h

#ifdef  _FLASH_INCLUDE

const word  _ind1_sld   = 1 ;
const word  _ind100_sld = 100 ;
const struct SLED   c_sled =
{
    /*  type   ;          */  _Sled_Vresion,
    /*  save_mem ;        */  _MaxSaveSled,
    /*  dt_scan ;         */  _MkSec(3333), //нужно задавать не в дискр.,а уже в мкс.
    /*  dt_stop ;         */  6,
    /*  kratn ;           */  1,
    /*  t_start;          */  _Sec( 60 * 5 ),
    /*  n_kanal ;         */  18,//_SledTabSizeMax ,
    /*  page_size ;       */  16,
  {
 //----  Рабочий список переменных заносимых в след.
                     //  _sl_form(type,off_sign,print_type,celoe,drob)
    {"Time-sec " },
    {"E        " },
    {"Ud       " },
    {"N#       " },
    {"N#R      " },
    {"N        " },
    {"Id#      " },
#ifndef _SIFU2_
    {"Id#R     " },
    {"Id       " },
    {"L        " },
    {"M_Nvs    " },
#else
    {"Id#R_RT1 " },
    {"Id1      " },
    {"L1       " },
    {"M_Nvs1   " },
#endif
#ifdef   Itt_ach
    {"Idtt     " },
#else
    {"Tckl     " },
#endif
    {"If       " },
#ifndef _SIFU2_
    {"cCfgR    " },
    {"cN#      " },
    {"Pi0f     " },
    {"IntRT    " },
#else
    {"Id#R_RT2 " },
    {"Id2      " },
    {"M_Nvs2   " },
    {"L2       " },
#endif
    {"Po0      " }
  },
  0
};

//--------  Полный список доступных переменных.

const struct Sled_var  FullSledTab[] =
  {
                     //  _sl_form(type,off_sign,print_type,celoe,drob)
    {"Time-sec ", (w*)&Puls_counter, _sl_form(2,1,2,2,3), _pSec(1.0),(w*)&_ind1_sld,"s " },
#ifndef _CM3_
    {"Time-msec", (w*)&timer1    ,_sl_form(2,1,2,2,1), _MkSec(1000),(w*)&_ind1_sld,"ms " },
#else
    {"Time-msec", (w*)&LPC_TIM0->TC,_sl_form(2,1,2,2,1), _MkSec(1000),(w*)&_ind1_sld,"ms " },
#endif
    {"Tckl     ", (w*)&Tckl      ,_sl_form(2,1,2,2,1), _MkSec(1000),(w*)&_ind1_sld,"ms " },
    {"Time-ovr ", (w*)&Timer1_Ovr,_sl_form(2,1,2,2,3), _Sec(1.0)   ,(w*)&_ind1_sld,"s "  },
    {"E        ", &EDS_dop_kod   ,_sl_form(2,0,2,3,1), _EDS_Nom    ,(w*)&_ind100_sld,"% "},
    {"Enf      ", &EDS_dop_kod_nf,_sl_form(2,0,2,3,1), _EDS_Nom    ,(w*)&_ind100_sld,"% "},
#ifdef   EDS_ach
    {"Eap      ", &iEDS ,_sl_form(2,0,2,3,1),_EDS_Nom>>_Skor_Shift ,(w*)&_ind100_sld,"% "},
    {"Epr      ", &prEDS,_sl_form(2,0,2,3,1),_EDS_Nom>>_Skor_Shift ,(w*)&_ind100_sld,"% "},
#endif
    {"Ud       ", &UdSr        ,_sl_form(2,0,2,3,1), _Ud_Nom ,(w*)&_ind100_sld,"% " },
#ifdef _REG_POL
    {"S#       ", &ZUgol       ,_sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"RPINsqr  ", &RP_in_sqr   ,_sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"S        ", &Ugol        ,_sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"IntRP    ", &Integr_RP   ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"RPOut    ", &OuRP        ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
#endif
    {"N#       ", &Z_Skor      ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N#R      ", &ZISkor      ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N#a      ", &ZSkA        ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
#ifdef Nzad_4_20_ach
    {"N#(4-20) ", &Nzad        ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
#endif
    {"N#_IZU_BM", &ZSkBM       ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N#_Tolch ", &ZSkT        ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N#_Shtat ", &ZSk_Shtat   ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N        ", &Skor        ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"Nnf      ", &Skor_ind    ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"Nf       ", &Skor_f      ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"Nx       ", &Skor_r      ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"TG       ", &TG          ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
#ifdef   TGx_ach
    {"TGx1     ", &TGx1        ,_sl_form(2,0,2,3,2),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"TGx8     ", &TGx8        ,_sl_form(2,0,2,3,2),_Skor_Nom,(w*)&_ind100_sld,"% " },
#endif
    {"IntRS    ", &OuIchRS     ,_sl_form(2,0,2,3,1),_Id_Nom  ,(w*)&_ind100_sld,"% " },
    {"Prz_flg  ", &Prz.all     ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef bi_RS_P
    {"KpRS     ", &_r_KRSP ,_sl_form(2,0,2,3,1), 256        ,(w*)&_ind1_sld  ,"ед" },
#endif
    {"Kp-RS    ", &KRSP_ind    ,_sl_form(2,0,2,3,1), 256    ,(w*)&_ind1_sld  ,"ед" },
    {"Ti-RS    ", &KRSI_ind    ,_sl_form(2,0,2,3,1), 1      ,(w*)&_ind1_sld  ,"ms "},
    {"Kp-REDS  ", &Kp_REDS_ind ,_sl_form(2,0,2,3,1), 256    ,(w*)&_ind1_sld  ,"ед" },
    {"Ti-REDS  ", &Ki_REDS_ind ,_sl_form(2,0,2,3,1), 1      ,(w*)&_ind1_sld  ,"ms "},
    {"Id#      ", &OuRegS_dop_kod,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#ifndef _SIFU2_
    {"Id#R     ", &ZIDN        ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Id       ", &Id_dop_kod  ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"IntRT    ", &OIRT        ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"IDN      ", &IDN         ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"INN      ", &INN         ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#else
    {"Id#R_RT1 ", &ZIDN        ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Id#R_RT2 ", &ZIDN_2_     ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Id1      ", &Id_dop_kod  ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Id2      ", &Id2_dop_kod ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"IntRT1   ", &OIRT        ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"IntRT2   ", &OIRT_2_     ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"IDN_RT1  ", &IDN         ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"IDN_RT2  ", &IDN_2_      ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"INN-dv   ", &INN_dvig    ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"INN_RT1  ", &INN         ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"INN_RT2  ", &INN_2_      ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Idsum    ", &Id_sum      ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
    {"RTout    ", &ORT         ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"RegFlg   ", &RegFlg.all  ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld  ,"h " },
    {"flgDopIzm", &flg_RaTe.all,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld  ,"h " },
#ifdef   Itt_ach
    {"Idtt     ", &Idtt        ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef   Itt1_ach
    {"Idtt1    ", &Idtt1       ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef   Itt2_ach
    {"Idtt2    ", &Idtt2       ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef _RDN
    {"Id-2d    ", &Id_2v           ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    {"dId      ", &dId             ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    {"RDNout   ", &RDN_Out         ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef _BUKSOVKA
    {"N-2d     ", &N_2v            ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"dN       ", &dN              ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef _DST
    {"Idin     ", &Id_Din          ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    {"dSkor    ", &dSkor           ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"Ist      ", &Id_Stat         ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    {"IstF     ", &Id_Stat_flt.out ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
#endif
#ifdef _RRS
    {"Ist-2d   ", &Id_stat_2v      ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    {"flgLiga  ", &liga.all        ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
    {"M        ", &Moment      ,_sl_form(2,0,2,3,1),_Mom_Nom ,(w*)&_ind100_sld,"% " },
#ifdef  _RVId
    { "PB.Id1  ", &RVId.Id1        ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    { "PB.Id2  ", &RVId.Id2        ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    { "PB.If2  ", &V2.Iv           ,_sl_form(2,0,2,3,1), _Iv_Nom   ,(w*)&_ind100_sld,"% " },
    { "PB.If#2 ", &V2.Iv_zad       ,_sl_form(2,0,2,3,1), _Iv_Nom   ,(w*)&_ind100_sld,"% " },
    { "PB.dId  ", &RVId.dId        ,_sl_form(2,0,2,3,1), _Id_Nom   ,(w*)&_ind100_sld,"% " },
    { "PB.dIf  ", &RVId.dIf        ,_sl_form(2,0,2,3,1), _Iv_Nom   ,(w*)&_ind100_sld,"% " },
    { "PB.Out  ", &RVId.Out        ,_sl_form(2,0,2,3,1), _Iv_Nom   ,(w*)&_ind100_sld,"% " },
#endif
#ifdef  Id_sr_ach
    {"Idsr     ", &Id_sr       ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef  Id2_sr_ach
    {"Id2sr    ", &Id2_sr      ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifndef _SIFU2_
    {"L#       ", &S.Alfa      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L        ", &S.Alfa_Old  ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"M_Nvs    ", &S.Most_Tir  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#else
    {"L1#      ", &S.Alfa      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L1       ", &S.Alfa_Old  ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"M_Nvs1   ", &S.Most_Tir  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"L2#      ", &S2.Alfa     ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L2       ", &S2.Alfa_Old ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"M_Nvs2   ", &S2.Most_Tir ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"IntRVT   ", &S2.Integr   ,_sl_form(2,0,2,3,1),_Grad(1.0)*64,(w*)&_ind1_sld ,"g " },
    {"RVTout   ", &S2.Out_rvt  ,_sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"dL2      ", &S2.Alfa_RVT ,_sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
#endif
    {"Id_TplInt", &Id_TeploIntegr,_sl_form(2,0,2,3,1), _Id_Nom,(w*)&_ind100_sld,"% "},
    {"F#       ", &V.Fv_zad    ,_sl_form(2,0,2,3,1), _Fv_Nom ,(w*)&_ind100_sld,"% " },
    {"F        ", &V.Fv        ,_sl_form(2,0,2,3,1), _Fv_Nom ,(w*)&_ind100_sld,"% " },
    {"IntREDS  ", &Integr_REDS ,_sl_form(2,0,2,3,1), _Fv_Nom ,(w*)&_ind100_sld,"% " },
    {"If#      ", &V.Iv_zad    ,_sl_form(2,0,2,3,1), _Iv_Nom ,(w*)&_ind100_sld,"% " },
    {"If       ", &V.Iv        ,_sl_form(2,0,2,3,1), _Iv_Nom ,(w*)&_ind100_sld,"% " },
#ifdef _Vozb_KTE
    {"IntRTf   ", &V.Integr_rt ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lf#      ", &V.Alfa      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lf       ", &V.Alfa_Old  ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"V_Nvs    ", &V.N         ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"V_NumInt ", &V.NumInt    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"V_TZ     ", &V.TZ        ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"V_TZreal ", &V.TZ_real   ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
    {"V_flg    ", &V.flg.all   ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef   It_ach
    {"It       ", &It          ,_sl_form(2,0,2,3,1), _Iv_Nom ,(w*)&_ind100_sld,"% " },
#endif
    // 6-ти пульсная схема :
#if   defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
    {"IA1      ", &IA1         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IB1      ", &IB1         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IC1      ", &IC1         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
#endif
    // 12-ти пульсная схема , по два ШС в каждом мосту - индикация первой секции :
#if   defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
    {"IA2      ", &IA2         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IB2      ", &IB2         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IC2      ", &IC2         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    // 12-ти пульсная схема , по одному ШС в каждом мосту :
#elif !defined( IA2_ach ) && !defined( IB2_ach ) && !defined( IC2_ach ) && defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach )
    {"IA2      ", &IA3         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IB2      ", &IB3         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IC2      ", &IC3         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
#endif
    // 12-ти пульсная схема , по два ШС в каждом мосту - индикация второй секции :
#if   defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach ) && defined( IA4_ach ) && defined( IB4_ach ) && defined( IC4_ach )
    {"IA3      ", &IA3         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IB3      ", &IB3         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IC3      ", &IC3         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IA4      ", &IA4         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IB4      ", &IB4         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
    {"IC4      ", &IC4         ,_sl_form(2,1,2,3,1), _Id_Nom  ,(w*)&_ind100_sld,"% "},
#endif
#ifdef _Dat_Temp_Max
       _F0_ADC_multiplex_temp,
#endif
    {"cCfgR    ", &canr.CfgReg.all ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"cStsR    ", &canr.StatReg.all,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
    {"cN#      ", &canr.N_zad      ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"cId#     ", &canr.Id_zad     ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"cId#P    ", &canr.Idz_MaxP   ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"cId#M    ", &canr.Idz_MaxM   ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"cF#      ", &canr.F_zad      ,_sl_form(2,0,2,3,1), _Fv_Nom ,(w*)&_ind100_sld,"% " },
    {"cL#      ", &canr.L_zad      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"cL#min   ", &canr.L_min      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"PDF0m    ", &PDF[0].out_m    ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"PDF0g    ", &PDF[0].out_g    ,_sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
#ifdef _CM3_
    {"PDF0o    ", &PDF[0].out_ob   ,_sl_form(2,0,2,3,1),10,        (w*)&_ind1_sld ,"o/m " },
#else
    {"PDF0o    ", &PDF[0].out_ob   ,_sl_form(2,0,2,3,1),1,         (w*)&_ind1_sld ,"o/m " },
#endif
#ifdef _T_PDF
    {"flg_PDF0 ", &PDF[0].flg.all          , _sl_form(1,1,1,0,0), 1         , (w*)&_ind1_sld  , "h " },
    {"N_F_PDF0 ", &PDF[0].N_Fpdf           , _sl_form(2,0,2,3,0), _Skor_Nom , (w*)&_ind100_sld, "% " },
    {"N_T_PDF0 ", &PDF[0].N_Tpdf           , _sl_form(2,0,2,3,0), _Skor_Nom , (w*)&_ind100_sld, "% " },
  //{"T_PDF0   ", (w*)&pdf_drv_data[0].Tpdf, _sl_form(2,1,1,0,0), 1         , (w*)&_ind1_sld  , "h " },
    {"F_PDF0   ", (w*)&PDF[0].Fpdf         , _sl_form(2,1,1,0,0), 1         , (w*)&_ind1_sld  , "h " },
    {"Счетч_T  ", (w*)&pdf_drv_data[0].Scht_T    , _sl_form(2,1,1,0,0), 1   , (w*)&_ind1_sld  , "h " },
    {"Tpdf_time", (w*)&pdf_drv_data[0].Tpdf_time , _sl_form(2,1,1,0,0), 1   , (w*)&_ind1_sld  , "h " },
#endif
    {"Sels0g   ", &Sels[0].out_g   ,_sl_form(2,0,2,3,1), _Grad(1.0),(w*)&_ind1_sld  ,"g " },
    {"Sels0m   ", &Sels[0].out_m   ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"Sels1g   ", &Sels[1].out_g   ,_sl_form(2,0,2,3,1), _Grad(1.0),(w*)&_ind1_sld  ,"g " },
    {"Sels1m   ", &Sels[1].out_m   ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"Po0      ", &Po0_c.all       ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#ifdef  _AsPo0_
    {"AsPo0    ", &PoS_c[0].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPo1_
    {"AsPo1    ", &PoS_c[1].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPo2_
    {"AsPo2    ", &PoS_c[2].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPo3_
    {"AsPo3    ", &PoS_c[3].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPo4_
    {"AsPo4    ", &PoS_c[4].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPo5_
    {"AsPo5    ", &PoS_c[5].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPo6_
    {"AsPo6    ", &PoS_c[6].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPo7_
    {"AsPo7    ", &PoS_c[7].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
    {"Pi0      ", &Pi0_c.all       ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef  _Pi1_
    {"Pi1      ", &Pi1_c.all       ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _Pi2_
    {"Pi2      ", &Pi2_c.all       ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
    {"Pi0f     ", &Pi0_cf.all      ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef  _Pi1_
    {"Pi1f     ", &Pi1_cf.all      ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _Pi2_
    {"Pi2f     ", &Pi2_cf.all      ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi0_
    {"AsPi0    ", &PiS_c[0].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi1_
    {"AsPi1    ", &PiS_c[1].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi2_
    {"AsPi2    ", &PiS_c[2].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi3_
    {"AsPi3    ", &PiS_c[3].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi4_
    {"AsPi4    ", &PiS_c[4].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi5_
    {"AsPi5    ", &PiS_c[5].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi6_
    {"AsPi6    ", &PiS_c[6].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi7_
    {"AsPi7    ", &PiS_c[7].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi8_
    {"AsPi8    ", &PiS_c[8].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi9_
    {"AsPi9    ", &PiS_c[9].all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi10_
    {"AsPi10   ", &PiS_c[10].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi11_
    {"AsPi11   ", &PiS_c[11].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi12_
    {"AsPi12   ", &PiS_c[12].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi13_
    {"AsPi13   ", &PiS_c[13].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi14_
    {"AsPi14   ", &PiS_c[14].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi15_
    {"AsPi15   ", &PiS_c[15].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef  _AsPi0_
    {"AsPi0f   ", &PiS_cf[0].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi1_
    {"AsPi1f   ", &PiS_cf[1].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi2_
    {"AsPi2f   ", &PiS_cf[2].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi3_
    {"AsPi3f   ", &PiS_cf[3].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi4_
    {"AsPi4f   ", &PiS_cf[4].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi5_
    {"AsPi5f   ", &PiS_cf[5].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi6_
    {"AsPi6f   ", &PiS_cf[6].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi7_
    {"AsPi7f   ", &PiS_cf[7].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi8_
    {"AsPi8f   ", &PiS_cf[8].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi9_
    {"AsPi9f   ", &PiS_cf[9].all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi10_
    {"AsPi10f  ", &PiS_cf[10].all  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi11_
    {"AsPi11f  ", &PiS_cf[11].all  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi12_
    {"AsPi12f  ", &PiS_cf[12].all  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi13_
    {"AsPi13f  ", &PiS_cf[13].all  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi14_
    {"AsPi14f  ", &PiS_cf[14].all  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifdef  _AsPi15_
    {"AsPi15f  ", &PiS_cf[15].all  ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#endif
#ifndef  Num_obl
    {"NumRez   ", &Num_obl         ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
#endif
    {"S_NumInt ", &S.NumInt        ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"S_flg    ", &S.flg.all       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"S_TZ     ", &S.TZ            ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef _SIFU2_
    {"S2_NumInt", &S2.NumInt       ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"S2_flg   ", &S2.flg.all      ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"S2_TZ    ", &S2.TZ           ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
    {"Prg_all  ", &Prg.all         ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Otkl_Imp ", &Otkl_Imp        ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"S_DZV    ", &S.DZV           ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"dt_revers", &dt_revers       ,_sl_form(2,1,2,2,3), _pSec(1.0),(w*)&_ind1_sld,"s " },
    {"dn_revers", &dn_revers       ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
    {"Av_all   ", &Av.all          ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Av2_all  ", &Av2.all         ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Rev_label", &Revers_Label    ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
#ifdef   _Union_FR
    {"Syn_apEPA", (w*)&IPCP0       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#else
  #ifdef _CM3_
    {"Syn_apEPA", (w*)&LPC_TIM3->CR0,_sl_form(2,1,1,0,0), 1        ,(w*)&_ind1_sld,"h " },
  #else  // 590-й процессор :
    {"Syn_apEPA", (w*)&IPCP3       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
  #endif
#endif
    {"Syn_EPA  ", (w*)&Syn.NS_EPA  ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Syn_NS2  ", (w*)&Syn.NS2     ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Tsyn     ", &Tsyn            ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef   _SIFU_Syn2
 #ifdef  _Union_FR
    {"Syn2apEPA", (w*)&IPCP2       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
 #else
   #ifdef _CM3_
    {"Syn2apEPA", (w*)&LPC_TIM1->CR0,_sl_form(2,1,1,0,0), 1        ,(w*)&_ind1_sld,"h " },
   #else // 590-й процессор :
    {"Syn2apEPA", (w*)&IPCP5       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
   #endif
 #endif
    {"Syn2_EPA ", (w*)&Syn2.NS_EPA ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Syn2_NS2 ", (w*)&Syn2.NS2    ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Tsyn2    ", &Tsyn2           ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifdef _Rev_Pola   // если включен алгоритм реверса поля.
    {"RevPo_flg", (w*)&RP_Pz.all   ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
#ifndef _CM3_
    {"timer1   ", (w*)&timer1      ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#else
    {"timer1   ", (w*)&LPC_TIM0->TC,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#endif
    {"Timer1Ovr", (w*)&Timer1_Ovr  ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
  //{"zi_prz   ", &zi_rs.prz.all   ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
  //{"zi_in2   ", &zi_rs.in_2      ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"zi_out   ", &zi_rs.out       ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
  //{"zi_out2  ", &zi_rs.out_2     ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"zi_outlin", &zi_rs.out_lin   ,_sl_form(2,0,2,3,1), _Skor_Nom ,(w*)&_ind100_sld,"% " },
    {"z_res_out", (w*)&zad_res.out ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h "   },
    {"I1pr-tir ", &Iproboy1    ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },  // для помощи в определении пробитого тиристора
    {"i-tyr    ", &i           ,_sl_form(1,1,2,3,0), 1         ,(w*)&_ind1_sld," "  },
    {"n-tyr    ", &n           ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
    {"nn-tyr   ", &nn          ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
#ifdef _SIFU2_
    {"I2pr-tir ", &Iproboy2    ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"n2-tyr   ", &n2          ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
    {"nn2-tyr  ", &nn2         ,_sl_form(1,1,2,1,0), 1         ,(w*)&_ind1_sld," "  },
#endif
    {"Kompen_Ud", &Kompen_Ud       ,_sl_form(2,1,2,3,0), 1         ,(w*)&_ind1_sld,  "d " },
    {"Ud_Komp  ", &UdSr_Komp       ,_sl_form(2,0,2,3,1), _Ud_Nom   ,(w*)&_ind100_sld,"% " },
    {"EDS_P    ", &EDS_P           ,_sl_form(2,0,2,3,1), _EDS_Nom  ,(w*)&_ind100_sld,"% " }, // добавлено Головиным
    {"ZnEDS_P  ", &ZnEDS_P         ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " }   // для помощи в настр. ДЭДС
#ifdef _Sld_cnst_Obj
  ,_Sld_cnst_Obj
#endif
           // зарезервированная строка для задания прямого адреса пременной.
    //{"@addr    ", 0                ,_sl_form(1,1,1,3,0), 1         ,(w*)&_ind1_sld,"  " }
  };
const word FullSledTab_size = sizeof(FullSledTab) / sizeof(struct Sled_var) ;

   // {"RegAv1   ", &Reg_AvarMsgFirst,_sl_form(4,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
   // {"RegAv    ", &Reg_AvarMsg     ,_sl_form(4,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
   // {"RegPr    ", &Reg_PreduprMsg  ,_sl_form(4,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
   // {"RegSrv   ", &Reg_ServiceMsg  ,_sl_form(4,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

 extern const word  _ind1_sld   ;
 extern const word  _ind100_sld ;
 extern const struct SLED  c_sled ;
 extern const struct Sled_var  FullSledTab[] ;
 extern const word FullSledTab_size ;

/*------------------------------------------------*/
#endif
#endif


