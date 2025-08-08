
#ifndef _jrn_cnst
#define _jrn_cnst
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#ifdef _JOURNAL_INCLUDE
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

const word  _ind1_jrn   = 1 ;
const word  _ind100_jrn = 100 ;

//òàáëèöà æóðíàëà â ÝÎÇÓ
const struct TAB_JRN c_TabJrn =
{
  /* byte  version; */ _Journal_Version,   //âåðñèÿ æóðíàëà
  /* byte  num_val; */ 16,                  //÷èñëî ïåðåìåííûõ
  /* word  dt_scan; */ _fSec ( 0.10 ),     //èíòåðâàë âðåìåíè ñêàíèðîâàíèÿ
  /* struct TAB_VAL TabVal[ _MaxNumValJrn ] = */
  //Ðàáî÷èé ñïèñîê ïåðåìåííûõ, çàíîñèìûõ â æóðíàë
 {
  { "N#        ", _BRV, _Skor_nom( 1.0 ) },
  { "N#R       ", _BOL, _Skor_nom( 1.1 ) },
  { "N         ", _BOL, _Skor_nom( 1.2 ) },
  { "E         ", _BOL, _EDS_nom( 1.2 )  },
  { "Ud        ", _BRV, _Ud_nom( 1.3 )   },
  { "Id#       ", _BOL, _Id_nom( 1.5 )   },
  { "Id        ", _BRV, _Id_nom( 2.0 )   },
  { "F         ", _BOL, _Fv_nom( 1.2 )   },
  { "L         ", _MRV, _Grad(20)        },
  { "Prg.Gotovn", 0,    6                }, // Ïåðåêë. ðåæèì "Ñáîðêà Ãîòîâíîñòè"/"Ðàáîòà".
  { "Pi0f.QK1  ", 0,    1                }, // bi_QK1
  { "Pi0f.AK1  ", 0,    2                }, // bi_AK1
  { "Pi0f.DS1  ", 0,    7                }, // bi_DS1
  { "AsPi0f.VR1", 0,    0                }  // bi_VR1
 },
  0
};


//ïîëíûé ñïèñîê äîñòóïíûõ ïåðåìåííûõ
_x_far const struct VAR_JRN FullJrnTab[] =
{                                                                      // _jrn_form( ad, off_sign, celoe, drob, type )
  { "E         ", &EDS_dop_kod,     _EDS_nom(-2.0), _EDS_nom(2.0), _EDS_Nom, (w*)&_ind100_jrn, _EDS_nom(0.01), "%", _jrn_form( 0,0,3,1,2 ) },

#ifdef   EDS_ach
  { "Eap       ", &iEDS,            _EDS_nom(-2.0)>>_Skor_Shift, _EDS_nom(2.0)>>_Skor_Shift, _EDS_Nom>>_Skor_Shift, (w*)&_ind100_jrn, _EDS_nom(0.01)>>_Skor_Shift, "%", _jrn_form( 0,0,3,1,2 ) },
  { "Epr       ", &prEDS,           _EDS_nom(-2.0)>>_Skor_Shift, _EDS_nom(2.0)>>_Skor_Shift, _EDS_Nom>>_Skor_Shift, (w*)&_ind100_jrn, _EDS_nom(0.01)>>_Skor_Shift, "%", _jrn_form( 0,0,3,1,2 ) },
#endif

  { "Ud        ", &UdSr,            _Ud_nom(-2.0),   _Ud_nom(2.0),   _Ud_Nom,    (w*)&_ind100_jrn, _Ud_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },

#ifdef _REG_POL
  { "S#        ", &ZUgol,           _Grad(0.0),      _Grad(359.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "RPINsqr   ", &RP_in_sqr,       _Grad(0.0),      _Grad(359.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "S         ", &Ugol,            _Grad(0.0),      _Grad(359.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "IntRP     ", &Integr_RP,       _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "RPOut     ", &OuRP,            _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
#endif

  { "N#        ", &Z_Skor,          _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "N#R       ", &ZISkor,          _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "N         ", &Skor,            _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "Nnf       ", &Skor_ind,        _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "Nf        ", &Skor_f,          _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "Nx        ", &Skor_r,          _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "IntRS     ", &OuIchRS,         _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "Id#       ", &OuRegS_dop_kod,  _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },

#ifndef _SIFU2_
  { "Id#R      ", &ZIDN,            _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "Id        ", &Id_dop_kod,      _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "IntRT     ", &OIRT,            _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
#else
  { "Id#R_RT1  ", &ZIDN,            _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "Id#R_RT2  ", &ZIDN_2_,         _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "Id1       ", &Id_dop_kod,      _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "Id2       ", &Id2_dop_kod,     _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "IntRT1    ", &OIRT,            _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "IntRT2    ", &OIRT_2_,         _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "Idsum     ", &Id_sum,          _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
#endif

#ifdef _RDN
  { "Id-2d     ", &Id_2v,           _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "dId       ", &dId,             _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "RDNout    ", &RDN_Out,         _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
#endif

#ifdef _BUKSOVKA
  { "N-2d      ", &N_2v,            _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "dN        ", &dN,              _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
#endif

#ifdef _RRS
  { "IdDin     ", &Id_Din,          _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "dSkor     ", &dSkor,           _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "IdStat    ", &Id_Stat,         _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "IdStatFlt ", &Id_Stat_flt.out, _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "IdSt-2d   ", &Id_stat_2v,      _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "flgLiga   ", &liga.all,        0,               7,              1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _RVId
  { "Id-1      ", &Id1,             _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "Id-2      ", &Id2,             _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "If2       ", &V2.Iv,           _Iv_nom(-3.0),   _Iv_nom(3.0),   _Iv_Nom,    (w*)&_ind100_jrn, _Iv_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "If#2      ", &V2.Iv_zad,       _Iv_nom(-3.0),   _Iv_nom(3.0),   _Iv_Nom,    (w*)&_ind100_jrn, _Iv_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "dId       ", &dRVId,           _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "dIf       ", &dIv,             _Iv_nom(-3.0),   _Iv_nom(3.0),   _Iv_Nom,    (w*)&_ind100_jrn, _Iv_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
#endif

#ifdef  Id_sr_ach
  { "Idsr      ", &Id_sr,           _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
#endif

#ifdef  Id2_sr_ach
  { "Id2sr     ", &Id2_sr,          _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
#endif

  { "L#        ", &S.Alfa,          _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "L         ", &S.Alfa_Old,      _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "M_Nvs     ", &S.Most_Tir,      0,               7,              1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },

#ifdef _SIFU2_
  { "M_Nvs2    ", &S2.Most_Tir,     0,               7,              1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
  { "RVTout    ", &S2.Out_rvt,      _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "IntRVT    ", &S2.Integr,       _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "dL2       ", &S2.Alfa_RVT,     _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "L2#       ", &S2.Alfa,         _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "L2        ", &S2.Alfa_Old,     _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
#endif

  { "cCfgR     ", &canr.CfgReg.all, 0,               15,             1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },
  { "cStsR     ", &canr.StatReg.all,0,               15,             1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },
  { "cN#       ", &canr.N_zad,      _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "cId#      ", &canr.Id_zad,     _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "cId#P     ", &canr.Idz_MaxP,   _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "cId#M     ", &canr.Idz_MaxM,   _Id_nom(-3.0),   _Id_nom(3.0),   _Id_Nom,    (w*)&_ind100_jrn, _Id_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "cF#       ", &canr.F_zad,      _Fv_nom(-2.0),   _Fv_nom(2.0),   _Fv_Nom,    (w*)&_ind100_jrn, _Fv_nom(0.01),    "%", _jrn_form( 0,0,3,1,2 ) },
  { "cL#       ", &canr.L_zad,      _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "cL#min    ", &canr.L_min,      _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },
  { "PDF0m     ", &PDF[0].out_m,    _Skor_nom(-2.0), _Skor_nom(2.0), _Skor_Nom,  (w*)&_ind100_jrn, _Skor_nom(0.001), "%", _jrn_form( 0,0,3,1,2 ) },
  { "PDF0g     ", &PDF[0].out_g,    _Grad(0.0),      _Grad(179.0),   _Grad(1.0), (w*)&_ind1_jrn,   _Grad(1.0),       "g", _jrn_form( 0,1,3,0,2 ) },

  { "Po0       ", &Po0_c.all,       0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },

#ifdef  _AsPo0_
  { "AsPo0     ", &PoS_c[0].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo1_
  { "AsPo1     ", &PoS_c[1].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo2_
  { "AsPo2     ", &PoS_c[2].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo3_
  { "AsPo3     ", &PoS_c[3].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo4_
  { "AsPo4     ", &PoS_c[4].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo5_
  { "AsPo5     ", &PoS_c[5].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo6_
  { "AsPo6     ", &PoS_c[6].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPo7_
  { "AsPo7     ", &PoS_c[7].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

  { "Pi0f      ", &Pi0_f.all,       0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },

  { "Pi0f.QK1  ", &Pi0_f.all,       0,               7,              1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
  { "Pi0f.AK1  ", &Pi0_f.all,       0,               7,              2,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
  { "Pi0f.DS1  ", &Pi0_f.all,       0,               7,              7,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },

#ifdef  _Pi1_
  { "Pi1f      ", &Pi1_f.all,       0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _Pi2_
  { "Pi2f      ", &Pi2_f.all,       0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi0_
  { "AsPi0f    ", &PiS_f[0].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
  { "AsPi0f.VR1", &PiS_f[0].all,    0,               7,              1,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi1_
  { "AsPi1f    ", &PiS_f[1].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi2_
  { "AsPi2f    ", &PiS_f[2].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi3_
  { "AsPi3f    ", &PiS_f[3].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi4_
  { "AsPi4f    ", &PiS_f[4].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi5_
  { "AsPi5f    ", &PiS_f[5].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi6_
  { "AsPi6f    ", &PiS_f[6].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi7_
  { "AsPi7f    ", &PiS_f[7].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi8_
  { "AsPi8f    ", &PiS_f[8].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi9_
  { "AsPi9f    ", &PiS_f[9].all,    0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi10_
  { "AsPi10f   ", &PiS_f[10].all,   0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi11_
  { "AsPi11f   ", &PiS_f[11].all,   0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi12_
  { "AsPi12f   ", &PiS_f[12].all,   0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi13_
  { "AsPi13f   ", &PiS_f[13].all,   0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi14_
  { "AsPi14f   ", &PiS_f[14].all,   0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

#ifdef  _AsPi15_
  { "AsPi15f   ", &PiS_f[15].all,   0,               7,              0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,1,0,1 ) },
#endif

  { "Av_all    ", &Av.all,          0,               15,             0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },
  { "Av2_all   ", &Av2.all,         0,               15,             0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },
  { "Prg       ", &Prg.all,         0,               15,             0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },
  { "Prg.Gotovn", &Prg.all,         0,               15,             6,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },

#ifdef _Rev_Pola   // åñëè âêëþ÷åí àëãîðèòì ðåâåðñà ïîëÿ.
  { "RevPo_flg ", (w*)&RP_Pz.all,   0,               15,             0,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 1,1,2,0,2 ) },
#endif

  { "cCfgRn13x2", &canr.CfgReg.all, 0,                3,        0x6000,          (w*)&_ind1_jrn,   1,                "",  _jrn_form( 2,1,1,0,2 ) }

#ifdef _Jrn_cnst_Obj
  ,_Jrn_cnst_Obj
#endif
};

const word FullJrnTab_size = sizeof( FullJrnTab )/sizeof( struct VAR_JRN );

/*
//ïîëíûé ñïèñîê äîñòóïíûõ äèñêðåòíûõ ïîðòîâ
const struct BIT_PORT FullBitPort[] =
{
  { "Po0       ", &Po0_c.all     },
#ifdef  _AsPo0_
  { "AsPo0     ", &PoS_c[0].all  },
#endif
#ifdef  _AsPo1_
  { "AsPo1     ", &PoS_c[1].all  },
#endif
#ifdef  _AsPo2_
  { "AsPo2     ", &PoS_c[2].all  },
#endif
#ifdef  _AsPo3_
  { "AsPo3     ", &PoS_c[3].all  },
#endif
#ifdef  _AsPo4_
  { "AsPo4     ", &PoS_c[4].all  },
#endif
#ifdef  _AsPo5_
  { "AsPo5     ", &PoS_c[5].all  },
#endif
#ifdef  _AsPo6_
  { "AsPo6     ", &PoS_c[6].all  },
#endif
#ifdef  _AsPo7_
  { "AsPo7     ", &PoS_c[7].all  },
#endif
  { "Pi0f      ", &Pi0_f.all     },
#ifdef  _Pi1_
  { "Pi1f      ", &Pi1_f.all     },
#endif
#ifdef  _Pi2_
  { "Pi2f      ", &Pi2_f.all     },
#endif
#ifdef  _AsPi0_
  { "AsPi0f    ", &PiS_f[0].all  },
#endif
#ifdef  _AsPi1_
  { "AsPi1f    ", &PiS_f[1].all  },
#endif
#ifdef  _AsPi2_
  { "AsPi2f    ", &PiS_f[2].all  },
#endif
#ifdef  _AsPi3_
  { "AsPi3f    ", &PiS_f[3].all  },
#endif
#ifdef  _AsPi4_
  { "AsPi4f    ", &PiS_f[4].all  },
#endif
#ifdef  _AsPi5_
  { "AsPi5f    ", &PiS_f[5].all  },
#endif
#ifdef  _AsPi6_
  { "AsPi6f    ", &PiS_f[6].all  },
#endif
#ifdef  _AsPi7_
  { "AsPi7f    ", &PiS_f[7].all  },
#endif
#ifdef  _AsPi8_
  { "AsPi8f    ", &PiS_f[8].all  },
#endif
#ifdef  _AsPi9_
  { "AsPi9f    ", &PiS_f[9].all  },
#endif
#ifdef  _AsPi10_
  { "AsPi10f   ", &PiS_f[10].all },
#endif
#ifdef  _AsPi11_
  { "AsPi11f   ", &PiS_f[11].all },
#endif
#ifdef  _AsPi12_
  { "AsPi12f   ", &PiS_f[12].all },
#endif
#ifdef  _AsPi13_
  { "AsPi13f   ", &PiS_f[13].all },
#endif
#ifdef  _AsPi14_
  { "AsPi14f   ", &PiS_f[14].all },
#endif
#ifdef  _AsPi15_
  { "AsPi15f   ", &PiS_f[15].all },
#endif
};

const word FullBitPort_size = sizeof( FullBitPort )/sizeof( struct BIT_PORT );
  */
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#else
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

extern const struct TAB_JRN c_TabJrn;
extern _x_far const struct VAR_JRN FullJrnTab[];
extern const word FullJrnTab_size;
//extern const struct BIT_PORT FullBitPort[];
//extern const word FullBitPort_size;

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#endif
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#endif

