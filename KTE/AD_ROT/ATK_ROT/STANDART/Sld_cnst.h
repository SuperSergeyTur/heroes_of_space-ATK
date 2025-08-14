
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
    /*  dt_scan ;         */  _MkSec(3333), //нужно задавать не в дискр.,а уже в мкс. //_MkSec(250),- шкала для короткого следа
    /*  dt_stop ;         */  6,
    /*  kratn ;           */  0, //1, - Кратность короткого следа - 0, каждый такт по 250 мкс .
    /*  t_start;          */  _Sec( 60 * 5 ),
    /*  n_kanal ;         */  16,//_SledTabSizeMax ,
    /*  page_size ;       */  16,
  {
 //----  Рабочий список переменных заносимых в след.
                     //  _sl_form(type,off_sign,print_type,celoe,drob)
    {"L        " },
    {"Idsi     " },
    {"Idrv     " },
    {"N_rot    " },
    {"N_pdf    " },
    {"Otkl_Imp " },
    {"Po0      " },
    {"IA       " },
    {"IB       " },
    {"IC       " },
    {"Uac      " },
    {"Uba      " },
    {"Lr       " },
    {"Psi_mX   " },
    {"Psi_mY   " },
    {"flgO_all " }
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
    {"Time-ovr ", (w*)&Timer1_Ovr  ,_sl_form(2,1,2,2,3), _Sec(1.0)   ,(w*)&_ind1_sld,"s "  },
    {"Time-fsec", (w*)&Timer1_fSec        , _sl_form(2,1,2,2,3), _fSec(1.0) , (w*)&_ind1_sld  , "s " },
    {"Prz_flg  ", &Prz.all     ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Idrv     ", &Irot        ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"dId      ", &dIrot       ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Idsi     ", &Id_dop_kod  ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Id-flt   ", &Id_flt.out  ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#ifdef _ATK_ROT
  //{"Id-deystv", &Id_deystv   ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
    {"OutRT    ", &OIRT        ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"RegFlg   ", &RegFlg.all  ,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld  ,"h " },
    {"flgDopIzm", &flg_RaTe.all,_sl_form(2,1,1,0,0), 1       ,(w*)&_ind1_sld  ,"h " },
#ifdef   Itt_ach
    {"Idtt     ", &Idtt        ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
#ifdef  Id_sr_ach
    {"Idsr     ", &Id_sr       ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
#endif
    {"L#       ", &S.Alfa        ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld  ,"g " },
    {"L        ", &S.Alfa_Old    ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld  ,"g " },
//---------------------------- Измерения и вычисления  в ШИМ ----------------------------------
    {"Time-int ", &TimeAD_Skor   , _sl_form(2,1,2,2,1), _MkSec(1),(w*)&_ind1_sld,"mks " },
    {"Time-zar ", &time_zar      , _sl_form(2,1,2,2,1), _MkSec(1),(w*)&_ind1_sld,"mks " },
    {"Time-izm ", &time_izm      , _sl_form(2,1,2,2,1), _MkSec(1),(w*)&_ind1_sld,"mks " },
    {"Time-math", &time_math     , _sl_form(2,1,2,2,1), _MkSec(1),(w*)&_ind1_sld,"mks " },
    {"IA       ", &IA            , _sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"IB       ", &IB            , _sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"IC       ", &IC            , _sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"Uac      ", &Uac           , _sl_form(2,0,2,3,1), _Ud_Nom ,(w*)&_ind100_sld,"% " },
    {"Uba      ", &Uba           , _sl_form(2,0,2,3,1), _Ud_Nom ,(w*)&_ind100_sld,"% " },
    {"Ix       ", &Ix            , _sl_form(0,0,2,3,1), _ADf_Nom,(w*)&_ind100_sld,"% " },
    {"Iy       ", &Iy            , _sl_form(0,0,2,3,1), _ADf_Nom,(w*)&_ind100_sld,"% " },
    {"Ux       ", &Ux            , _sl_form(0,0,2,3,1), _ADf_Nom,(w*)&_ind100_sld,"% " },
    {"Uy       ", &Uy            , _sl_form(0,0,2,3,1), _ADf_Nom,(w*)&_ind100_sld,"% " },
    {"Psi_X    ", &Psi_X[1]      , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_Y    ", &Psi_Y[1]      , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_X_n-1", &Psi_X[0]      , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_Y_n-1", &Psi_Y[0]      , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_mX   ", &Psi_m_X[1]    , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_mY   ", &Psi_m_Y[1]    , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_mXn-1", &Psi_m_X[0]    , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"Psi_mYn-1", &Psi_m_Y[0]    , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"absPsi_mX", &Psi_m_X[2]    , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"absPsi_mY", &Psi_m_Y[2]    , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld,  "ед" },
    {"errPhi_e ", &errPhi_e      , _sl_form(1,1,1,0,0), 1       ,(w*)&_ind1_sld,  "h " },
    {"Slip     ", &Slip          , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld, "rad" },
    {"Slip_F   ", &Slip_f[1]     , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld, "rad" },
    {"w_rot    ", &OmegaRot      , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld, "rad" },
    {"N_rot    ", &SkorRot       , _sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N_pusk`  ", &Skor_Pusk      , _sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N     `  ", &Skor       , _sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"N_pdf    ", &SkorPDF       , _sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
    {"Phi_e    ", &Phi_e         , _sl_form(0,0,2,4,1), 1       ,(w*)&_ind1_sld, "rad" },
//--------------------------------------- СИФУ в ШИМ ------------------------------------------
    {"VT       ", &VT                     , _sl_form(1,1,1,0,0), 1          , (w*)&_ind1_sld, "h "   },
    {"VTn      ", &VTn                    , _sl_form(1,1,1,0,0), 1          , (w*)&_ind1_sld, "h "   },
    {"LL0      ", &L_L[0]                    , _sl_form(1,1,1,0,0), 1          , (w*)&_ind1_sld, "h "   },
    {"LL1      ", &L_L[1]                   , _sl_form(1,1,1,0,0), 1          , (w*)&_ind1_sld, "h "   },
    {"Lr1      ", &L[0]          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lr2      ", &L[1]          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lr3      ", &L[2]          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lr4      ", &L[3]          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lr5      ", &L[4]          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"Lr6      ", &L[5]          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_IU1    ", &L_IU[0]       , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_IU2    ", &L_IU[1]       , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_IU3    ", &L_IU[2]       , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_IU4    ", &L_IU[3]       , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_IU5    ", &L_IU[4]       , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_IU6    ", &L_IU[5]       , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"L_iu     ", &L_iu          , _sl_form(2,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"dL_dp    ", &delta_L       , _sl_form(0,0,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"dLdT     ", &dLdT          , _sl_form(0,0,2,3,1),1     ,(w*)&_ind1_sld ," " },
//---------------------------------------------------------------------------------------------
    {"cCfgR    ", &canr.CfgReg.all ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"cStsR    ", &canr.StatReg.all,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
#ifdef _ATK_ROT
    {"cStsR_AP1", &canr.StatReg2.all,_sl_form(2,1,1,0,0),1         , (w*)&_ind1_sld ,"h " },
#endif
    {"cN#      ", &canr.N_zad      ,_sl_form(2,0,2,3,1),_Skor_Nom,(w*)&_ind100_sld,"% " },
  /*{"cId#     ", &canr.Id_zad     ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"cId#P    ", &canr.Idz_MaxP   ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"cId#M    ", &canr.Idz_MaxM   ,_sl_form(2,0,2,3,1), _Id_Nom ,(w*)&_ind100_sld,"% " },
    {"cF#      ", &canr.F_zad      ,_sl_form(2,0,2,3,1), _Fv_Nom ,(w*)&_ind100_sld,"% " },
    {"cL#      ", &canr.L_zad      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },
    {"cL#min   ", &canr.L_min      ,_sl_form(2,1,2,3,1),_Grad(1.0),(w*)&_ind1_sld ,"g " },*/
    {"Po0      ", &Po0_c.all       ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
    {"Po_null  ", &Prt_NULL.all    ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld  ,"h " },
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
  //{"S_NumInt ", &S.NumInt        ,_sl_form(1,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
  //{"S_flg    ", &S.flg.all       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
  //{"S_TZ     ", &S.TZ            ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Prg_all  ", &Prg.all         ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Otkl_Imp ", &Otkl_Imp        ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"flgO_all ", &flgO.all        ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Av_all   ", &Av.all          ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Av2_all  ", &Av2.all         ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
  //{"upr_label", &upr_label       ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
//  {"Syn_apEPA", (w*)&LPC_TIM3->CR0,_sl_form(2,1,1,0,0), 1        ,(w*)&_ind1_sld,"h " },
//  {"Syn_EPA  ", (w*)&Syn.NS_EPA  ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
//  {"Syn_NS2  ", (w*)&Syn.NS2     ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
//  {"Tsyn     ", &Tsyn            ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
#ifdef   _SIFU_Syn2
    {"Syn2apEPA", (w*)&LPC_TIM1->CR0,_sl_form(2,1,1,0,0), 1        ,(w*)&_ind1_sld,"h " },
    {"Syn2_EPA ", (w*)&Syn2.NS_EPA ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Syn2_NS2 ", (w*)&Syn2.NS2    ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
    {"Tsyn2    ", &Tsyn2           ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h " },
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
    {"z_res_out", (w*)&zad_res.out ,_sl_form(2,1,1,0,0), 1         ,(w*)&_ind1_sld,"h "   }
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


