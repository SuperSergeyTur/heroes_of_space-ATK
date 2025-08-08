
#ifndef _var_tab_h
#define _var_tab_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _MAIN_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

//   СТРАНИЦЫ ДОЛЖНЫ БЫТЬ ПО 32 СТРОКИ.

const word crezerv = 0 ;
_x_far const struct namevar  var_tab1[] =
{
#ifdef _CANOPEN
// Группа 1  - ТЕКУЩИЕ ПАРАМЕТРЫ ПРИВОДА - 14 - контрольная строка
  { "r0_00",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2000, _VAR },
  { "E",       &EDS_dop_kod,        2, _SHORT_type,  _Ud_Nom,   _READ_access,       0x2001, _VAR },
  { "r0_01",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2002, _VAR },
  { "T-fSec",  &Timer1_fSec,        2, _SHORT_type,  0,         _READ_access,       0x2003, _VAR },
  { "r0_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2004, _VAR },
  { "r0_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2005, _VAR },
  { "N#",      &Z_Skor,             2, _SHORT_type,  _Skor_Nom, _READ_access,       0x2006, _VAR },
  { "N#R",     &ZISkor,             2, _SHORT_type,  _Skor_Nom, _READ_access,       0x2007, _VAR },
  { "N",       &Skor,               2, _SHORT_type,  _Skor_Nom, _READ_access,       0x2008, _VAR },
  { "Id_flt",  &Id_flt.out,         2, _SHORT_type,  _Id_Nom,   _READ_access,       0x2009, _VAR },
  { "r0_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x200a, _VAR },
  { "r0_05",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x200b, _VAR },
  { "Stup",    &SP_stup,            2, _SHORT_type,  0,         _READ_access,       0x200c, _VAR },
  { "Id#",     &OuRegS_dop_kod,     2, _SHORT_type,  _Id_Nom,   _READ_access,       0x200d, _VAR },
  { "Id#R",    &ZIDN,               2, _SHORT_type,  _Id_Nom,   _READ_access,       0x200e, _VAR },
  { "Id",      &Id_dop_kod,         2, _SHORT_type,  _Id_Nom,   _READ_access,       0x200f, _VAR },
  { "Ud",      &UdSr,               2, _SHORT_type,  _Skor_Nom, _READ_access,       0x2010, _VAR },
  { "L#"    ,  &S.Alfa,             2, _SHORT_type,  _Grad(1),  _READ_access,       0x2011, _VAR },
  { "L"     ,  &S.Alfa_Old,         2, _SHORT_type,  _Grad(1),  _READ_access,       0x2012, _VAR },
  { "r0_05",   (w*)&crezerv,        2, _SHORT_type,  _Fv_Nom,   _READ_access,       0x2013, _VAR },
  { "r0_06",   (w*)&crezerv,        2, _SHORT_type,  _Fv_Nom,   _READ_access,       0x2014, _VAR },
  { "r0_07",   (w*)&crezerv,        2, _SHORT_type,  _Iv_Nom,   _READ_access,       0x2015, _VAR },
  { "r0_08",   (w*)&crezerv,        2, _SHORT_type,  _Iv_Nom,   _READ_access,       0x2016, _VAR },
  { "M_Nvs" ,  &S.Most_Tir,         1,_CHAR_type,    0,         _READ_access,       0x2017, _VAR },
  { "RVTout",  (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2018, _VAR },
  { "dL2",     (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2019, _VAR },
  { "M_Nvs2",  (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x201a, _VAR },
  { "Lf#",     (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x201b, _VAR },
  { "Lf",      (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x201c, _VAR },
  { "r0_09",   (w*)&crezerv,        2, _SHORT_type,  _Mom_Nom,  _READ_access,       0x201d, _VAR },
  { "Istat",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x201e, _VAR },
  { "Idsum",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x201f, _VAR },
// Группа 2  - УПРАВЛЕНИЕ ПРИВОДОМ - 57 - контрольная строка
  { "UnitSt",  &Status_KTE,         1, _CHAR_type,   0,         _READ_access,       0x2020, _VAR },
  { "cStsR",   &canr.StatReg.all,   2, _SHORT_type,  0,         _READ_access,       0x2021, _VAR },
  { "cCfgR",   &canr.CfgReg.all,    2, _SHORT_type,  0,         _READ_WRITE_access, 0x2022, _VAR },
  { "r1_00",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2023, _VAR },
  { "Id#_t",   &canr.Temp_Zad,      1, _CHAR_type ,  0,         _READ_WRITE_access, 0x2024, _VAR },
  { "cN#",     &canr.N_zad,         2, _SHORT_type,  _Skor_Nom, _READ_WRITE_access, 0x2025, _VAR },
  { "cdId#",   &canr.dId_zad,       2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access, 0x2026, _VAR },
  { "cId#",    &canr.Id_zad,        2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access, 0x2027, _VAR },
  { "cId#P",   &canr.Idz_MaxP,      2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access, 0x2028, _VAR },
  { "cId#M",   &canr.Idz_MaxM,      2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access, 0x2029, _VAR },
  { "r1_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x202a, _VAR },
  { "r1_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x202b, _VAR },
  { "r1_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x202c, _VAR },
  { "cL#",     &canr.L_zad,         2, _SHORT_type,  _Grad(1),  _READ_WRITE_access, 0x202d, _VAR },
  { "cL#min",  &canr.L_min,         2, _SHORT_type,  _Grad(1),  _READ_WRITE_access, 0x202e, _VAR },
  { "cS#",     &canr.S_zad,         2, _SHORT_type,  _Grad(1),  _READ_WRITE_access, 0x202f, _VAR },
  { "cF#",     &canr.F_zad,         2, _SHORT_type,  _Fv_Nom,   _READ_WRITE_access, 0x2030, _VAR },
  { "r1_06",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2031, _VAR },
  { "r1_07",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2032, _VAR },
  { "r1_08",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2033, _VAR },
  { "r1_09",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2034, _VAR },
  { "r1_10",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2035, _VAR },
  { "r1_11",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2036, _VAR },
  { "r1_12",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2037, _VAR },
  { "r1_13",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2038, _VAR },
  { "r1_14",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2039, _VAR },
  { "r1_15",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x203a, _VAR },
  { "r1_16",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x203b, _VAR },
  { "r1_17",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x203c, _VAR },
  { "r1_18",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x203d, _VAR },
  { "UartRx",  &UartCAN_Rx.all,     2, _SHORT_type,  0,         _READ_WRITE_access, 0x203e, _VAR },
  { "UartTx",  &UartCAN_Tx.all,     2, _SHORT_type,  0,         _READ_access,       0x203f, _VAR },
// Группа 3  - АНАЛОГОВЫЙ ВВОД-ВЫВОД - 90 - контрольная строка
  { "Ai0",     &canr.Ai[0],         2, _SHORT_type,  0,         _READ_access,       0x2040, _VAR },
  { "Ai1",     &canr.Ai[1],         2, _SHORT_type,  0,         _READ_access,       0x2041, _VAR },
  { "Ai2",     &canr.Ai[2],         2, _SHORT_type,  0,         _READ_access,       0x2042, _VAR },
  { "Ai3",     &canr.Ai[3],         2, _SHORT_type,  0,         _READ_access,       0x2043, _VAR },
  { "Ai4",     &canr.Ai[4],         2, _SHORT_type,  0,         _READ_access,       0x2044, _VAR },
  { "r2_00",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2045, _VAR },
  { "r2_01",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2046, _VAR },
  { "Ao0",     &canr.Ao[0],         2, _SHORT_type,  0,         _READ_WRITE_access, 0x2047, _VAR },
  { "Ao1",     &canr.Ao[1],         2, _SHORT_type,  0,         _READ_WRITE_access, 0x2048, _VAR },
  { "r2_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2049, _VAR },
  { "r2_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x204a, _VAR },
#ifndef _WM591
  { "Sels0g",  &Sels[0].out_g,      2, _SHORT_type, _Grad(1),   _READ_access,       0x204b, _VAR },
  { "Sels0m",  &Sels[0].out_m,      2, _SHORT_type, _Skor_Nom,  _READ_access,       0x204c, _VAR },
  { "Sels1g",  &Sels[1].out_g,      2, _SHORT_type, _Grad(1),   _READ_access,       0x204d, _VAR },
  { "Sels1m",  &Sels[1].out_m,      2, _SHORT_type, _Skor_Nom,  _READ_access,       0x204e, _VAR },
  { "PDF0m" ,  &PDF[0].out_m,       2, _SHORT_type, _Skor_Nom,  _READ_access,       0x204f, _VAR },
  { "PDF0g" ,  &PDF[0].out_g ,      2, _SHORT_type, _Grad(1),   _READ_access,       0x2050, _VAR },
  { "PDF0o" ,  &PDF[0].out_ob,      2, _SHORT_type,  10,        _READ_access,       0x2051, _VAR },
#else
  { "Sels0g",  (w*)&crezerv,        2, _SHORT_type, _Grad(1),   _READ_access,       0x204b, _VAR },
  { "Sels0m",  (w*)&crezerv,        2, _SHORT_type, _Skor_Nom,  _READ_access,       0x204c, _VAR },
  { "Sels1g",  (w*)&crezerv,        2, _SHORT_type, _Grad(1),   _READ_access,       0x204d, _VAR },
  { "Sels1m",  (w*)&crezerv,        2, _SHORT_type, _Skor_Nom,  _READ_access,       0x204e, _VAR },
  { "PDF0m" ,  (w*)&crezerv,        2, _SHORT_type, _Skor_Nom,  _READ_access,       0x204f, _VAR },
  { "PDF0g" ,  (w*)&crezerv,        2, _SHORT_type, _Grad(1),   _READ_access,       0x2050, _VAR },
  { "PDF0o" ,  (w*)&crezerv,        2, _SHORT_type,  1,         _READ_access,       0x2051, _VAR },
#endif
  { "r2_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2052, _VAR },
  { "r2_05",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2053, _VAR },
  { "r2_06",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2054, _VAR },
  { "r2_07",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2055, _VAR },
  { "r2_08",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2056, _VAR },
  { "r2_09",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2057, _VAR },
  { "r2_10",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2058, _VAR },
  { "r2_11",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2059, _VAR },
  { "r2_12",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x205a, _VAR },
  { "r2_13",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x205b, _VAR },
  { "r2_14",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x205c, _VAR },
  { "r2_15",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x205d, _VAR },
  { "r2_16",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x205e, _VAR },
  { "r2_17",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x205f, _VAR },
// Группа 4  - ДИСКРЕТНЫЙ ВВОД-ВЫВОД - 123 - контрольная строка
  { "Pi0",     &Pi0_f.all,          1, _CHAR_type,   0,         _READ_access,       0x2060, _VAR },
  { "Pi1",     &Pi1_f.all,          1, _CHAR_type,   0,         _READ_access,       0x2061, _VAR },
#ifdef _Pi2_
  { "Pi2",     &Pi2_f.all,          1, _CHAR_type,   0,         _READ_access,       0x2062, _VAR },
#else
  { "Pi2",     (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2062, _VAR },
#endif
  { "Pi0f",    &Pi0_cf.all,         1, _CHAR_type,   0,         _READ_access,       0x2063, _VAR },
  { "Pi1f",    &Pi1_cf.all,         1, _CHAR_type,   0,         _READ_access,       0x2064, _VAR },
#ifdef _Pi2_
  { "Pi2f",    &Pi2_cf.all,         1, _CHAR_type,   0,         _READ_access,       0x2065, _VAR },
#else
  { "Pi2f",    (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2065, _VAR },
#endif
  { "AsPi0",   &PiS_f[0].all,       1, _CHAR_type,   0,         _READ_access,       0x2066, _VAR },
  { "AsPi1",   &PiS_f[1].all,       1, _CHAR_type,   0,         _READ_access,       0x2067, _VAR },
  { "AsPi2",   &PiS_f[2].all,       1, _CHAR_type,   0,         _READ_access,       0x2068, _VAR },
  { "AsPi3",   &PiS_f[3].all,       1, _CHAR_type,   0,         _READ_access,       0x2069, _VAR },
  { "r3_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x206a, _VAR },
  { "r3_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x206b, _VAR },
  { "AsPi0f",  &PiS_cf[0].all,      1, _CHAR_type,   0,         _READ_access,       0x206c, _VAR },
  { "AsPi1f",  &PiS_cf[1].all,      1, _CHAR_type,   0,         _READ_access,       0x206d, _VAR },
  { "AsPi2f",  &PiS_cf[2].all,      1, _CHAR_type,   0,         _READ_access,       0x206e, _VAR },
  { "AsPi3f",  &PiS_cf[3].all,      1, _CHAR_type,   0,         _READ_access,       0x206f, _VAR },
  { "r3_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2070, _VAR },
  { "r3_05",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2071, _VAR },
  { "Po0",     &Po0_c.all,          1, _CHAR_type,   0,         _READ_access,       0x2072, _VAR }, // Po0_c.all изменяется в любой части программы . Po0_nm.all - не изменяется .
  { "r3_06",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access,       0x2073, _VAR },
  { "AsPo0",   &PoS_c[0].all,       1, _CHAR_type,   0,         _READ_WRITE_access, 0x2074, _VAR },
  { "AsPo1",   &PoS_c[1].all,       1, _CHAR_type,   0,         _READ_WRITE_access, 0x2075, _VAR },
#else //_CANOPEN
// Группа 1  - ТЕКУЩИЕ ПАРАМЕТРЫ ПРИВОДА - 14 - контрольная строка
  { "r0_00",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "E",       &EDS_dop_kod,        2, _SHORT_type,  _Ud_Nom,   _READ_access       },
  { "r0_01",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "T-fSec",  &Timer1_fSec,        2, _SHORT_type,  0,         _READ_access       },
  { "r0_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r0_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "N#",      &Z_Skor,             2, _SHORT_type,  _Skor_Nom, _READ_access       },
  { "N#R",     &ZISkor,             2, _SHORT_type,  _Skor_Nom, _READ_access       },
  { "N",       &Skor,               2, _SHORT_type,  _Skor_Nom, _READ_access       },
  { "Id_flt",  &Id_flt.out,         2, _SHORT_type,  _Id_Nom,   _READ_access       },
  { "r0_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r0_05",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Stup",    &SP_stup,            2, _SHORT_type,  0,         _READ_access       },
  { "Id#",     &OuRegS_dop_kod,     2, _SHORT_type,  _Id_Nom,   _READ_access       },
  { "Id#R",    &ZIDN,               2, _SHORT_type,  _Id_Nom,   _READ_access       },
  { "Id",      &Id_dop_kod,         2, _SHORT_type,  _Id_Nom,   _READ_access       },
  { "Ud",      &UdSr,               2, _SHORT_type,  _Skor_Nom, _READ_access       },
  { "L#"    ,  &S.Alfa,             2, _SHORT_type,  _Grad(1),  _READ_access       },
  { "L"     ,  &S.Alfa_Old,         2, _SHORT_type,  _Grad(1),  _READ_access       },
  { "r0_05",   (w*)&crezerv,        2, _SHORT_type,  _Fv_Nom,   _READ_access       },
  { "r0_06",   (w*)&crezerv,        2, _SHORT_type,  _Fv_Nom,   _READ_access       },
  { "r0_07",   (w*)&crezerv,        2, _SHORT_type,  _Iv_Nom,   _READ_access       },
  { "r0_08",   (w*)&crezerv,        2, _SHORT_type,  _Iv_Nom,   _READ_access       },
  { "M_Nvs" ,  &S.Most_Tir,         1,_CHAR_type,    0,         _READ_access       },
  { "RVTout",  (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "dL2",     (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "M_Nvs2",  (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Lf#",     (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Lf",      (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r0_09",   (w*)&crezerv,        2, _SHORT_type,  _Mom_Nom,  _READ_access       },
  { "Istat",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Idsum",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
// Группа 2  - УПРАВЛЕНИЕ ПРИВОДОМ - 57 - контрольная строка
  { "UnitSt",  &Status_KTE,         1, _CHAR_type,   0,         _READ_access       },
  { "cStsR",   &canr.StatReg.all,   2, _SHORT_type,  0,         _READ_access       },
  { "cCfgR",   &canr.CfgReg.all,    2, _SHORT_type,  0,         _READ_WRITE_access },
  { "r1_00",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Id#_t",   &canr.Temp_Zad,      1, _CHAR_type ,  0,         _READ_WRITE_access },
  { "cN#",     &canr.N_zad,         2, _SHORT_type,  _Skor_Nom, _READ_WRITE_access },
  { "cdId#",   &canr.dId_zad,       2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access },
  { "cId#",    &canr.Id_zad,        2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access },
  { "cId#P",   &canr.Idz_MaxP,      2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access },
  { "cId#M",   &canr.Idz_MaxM,      2, _SHORT_type,  _Id_Nom,   _READ_WRITE_access },
  { "r1_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "cL#",     &canr.L_zad,         2, _SHORT_type,  _Grad(1),  _READ_WRITE_access },
  { "cL#min",  &canr.L_min,         2, _SHORT_type,  _Grad(1),  _READ_WRITE_access },
  { "cS#",     &canr.S_zad,         2, _SHORT_type,  _Grad(1),  _READ_WRITE_access },
  { "cF#",     &canr.F_zad,         2, _SHORT_type,  _Fv_Nom,   _READ_WRITE_access },
  { "r1_06",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_07",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_08",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_09",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_10",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_11",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_12",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_13",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_14",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_15",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_16",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_17",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r1_18",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "UartRx",  &UartCAN_Rx.all,     2, _SHORT_type,  0,         _READ_WRITE_access },
  { "UartTx",  &UartCAN_Tx.all,     2, _SHORT_type,  0,         _READ_access       },
// Группа 3  - АНАЛОГОВЫЙ ВВОД-ВЫВОД - 90 - контрольная строка
  { "Ai0",     &canr.Ai[0],         2, _SHORT_type,  0,         _READ_access       },
  { "Ai1",     &canr.Ai[1],         2, _SHORT_type,  0,         _READ_access       },
  { "Ai2",     &canr.Ai[2],         2, _SHORT_type,  0,         _READ_access       },
  { "Ai3",     &canr.Ai[3],         2, _SHORT_type,  0,         _READ_access       },
  { "Ai4",     &canr.Ai[4],         2, _SHORT_type,  0,         _READ_access       },
  { "r2_00",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_01",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Ao0",     &canr.Ao[0],         2, _SHORT_type,  0,         _READ_WRITE_access },
  { "Ao1",     &canr.Ao[1],         2, _SHORT_type,  0,         _READ_WRITE_access },
  { "r2_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
#ifndef _WM591
  { "Sels0g",  &Sels[0].out_g,      2, _SHORT_type, _Grad(1),   _READ_access       },
  { "Sels0m",  &Sels[0].out_m,      2, _SHORT_type, _Skor_Nom,  _READ_access       },
  { "Sels1g",  &Sels[1].out_g,      2, _SHORT_type, _Grad(1),   _READ_access       },
  { "Sels1m",  &Sels[1].out_m,      2, _SHORT_type, _Skor_Nom,  _READ_access       },
  { "PDF0m" ,  &PDF[0].out_m,       2, _SHORT_type, _Skor_Nom,  _READ_access       },
  { "PDF0g" ,  &PDF[0].out_g ,      2, _SHORT_type, _Grad(1),   _READ_access       },
  { "PDF0o" ,  &PDF[0].out_ob,      2, _SHORT_type,  10,        _READ_access       },
#else
  { "Sels0g",  (w*)&crezerv,        2, _SHORT_type, _Grad(1),   _READ_access       },
  { "Sels0m",  (w*)&crezerv,        2, _SHORT_type, _Skor_Nom,  _READ_access       },
  { "Sels1g",  (w*)&crezerv,        2, _SHORT_type, _Grad(1),   _READ_access       },
  { "Sels1m",  (w*)&crezerv,        2, _SHORT_type, _Skor_Nom,  _READ_access       },
  { "PDF0m" ,  (w*)&crezerv,        2, _SHORT_type, _Skor_Nom,  _READ_access       },
  { "PDF0g" ,  (w*)&crezerv,        2, _SHORT_type, _Grad(1),   _READ_access       },
  { "PDF0o" ,  (w*)&crezerv,        2, _SHORT_type,  1,         _READ_access       },
#endif
  { "r2_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_05",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_06",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_07",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_08",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_09",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_10",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_11",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_12",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_13",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_14",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_15",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_16",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r2_17",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
// Группа 4  - ДИСКРЕТНЫЙ ВВОД-ВЫВОД - 123 - контрольная строка
  { "Pi0",     &Pi0_f.all,          1, _CHAR_type,   0,         _READ_access       },
  { "Pi1",     &Pi1_f.all,          1, _CHAR_type,   0,         _READ_access       },
#ifdef _Pi2_
  { "Pi2",     &Pi2_f.all,          1, _CHAR_type,   0,         _READ_access       },
#else
  { "Pi2",     (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
#endif
  { "Pi0f",    &Pi0_cf.all,         1, _CHAR_type,   0,         _READ_access       },
  { "Pi1f",    &Pi1_cf.all,         1, _CHAR_type,   0,         _READ_access       },
#ifdef _Pi2_
  { "Pi2f",    &Pi2_cf.all,         1, _CHAR_type,   0,         _READ_access       },
#else
  { "Pi2f",    (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
#endif
  { "AsPi0",   &PiS_f[0].all,       1, _CHAR_type,   0,         _READ_access       },
  { "AsPi1",   &PiS_f[1].all,       1, _CHAR_type,   0,         _READ_access       },
  { "AsPi2",   &PiS_f[2].all,       1, _CHAR_type,   0,         _READ_access       },
  { "AsPi3",   &PiS_f[3].all,       1, _CHAR_type,   0,         _READ_access       },
  { "r3_02",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r3_03",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "AsPi0f",  &PiS_cf[0].all,      1, _CHAR_type,   0,         _READ_access       },
  { "AsPi1f",  &PiS_cf[1].all,      1, _CHAR_type,   0,         _READ_access       },
  { "AsPi2f",  &PiS_cf[2].all,      1, _CHAR_type,   0,         _READ_access       },
  { "AsPi3f",  &PiS_cf[3].all,      1, _CHAR_type,   0,         _READ_access       },
  { "r3_04",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "r3_05",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "Po0",     &Po0_c.all,          1, _CHAR_type,   0,         _READ_access       }, // Po0_c.all изменяется в любой части программы . Po0_nm.all - не изменяется .
  { "r3_06",   (w*)&crezerv,        2, _SHORT_type,  0,         _READ_access       },
  { "AsPo0",   &PoS_c[0].all,       1, _CHAR_type,   0,         _READ_WRITE_access },
  { "AsPo1",   &PoS_c[1].all,       1, _CHAR_type,   0,         _READ_WRITE_access },
#endif //_CANOPEN
  _Var_tab_InsertSled ,
  _Var_tab_InsertSled2
} ;

//  { "StrPrg",  &Prg.all,  2, _SHORT_type, 0,  _READ_WRITE_access },
//  { "NOMs"  ,  &_or.NOM, sizeof(_or.NOM), _CHAR_array_type,  0, _READ_access },
//  { "MsgAv" ,(void*) &Tabl_AvarMsg[0],  32*3*30, _CHAR_array_type | _Indirect_type ,  0,  _READ_access }

_x_far const struct SlaveVars  svar[_Num_CAN_Ports] = // _x_far - нужно , чтоб работал LINK .
{
  {
    sizeof(var_tab1)/sizeof(struct namevar), // кол-во перем. в табл.
    &var_tab1[0]                               // адр. табл.
  },
  {
    sizeof(var_tab1)/sizeof(struct namevar), // кол-во перем. в табл.
    &var_tab1[0]                               // адр. табл.
  }
#ifdef _CAN2_Port
 ,{
    sizeof(var_tab1)/sizeof(struct namevar), // кол-во перем. в табл.
    &var_tab1[0]                               // адр. табл.
  }
#endif
} ;

const lword size_vartab1 = sizeof(var_tab1);

#ifdef _INTERPRETER
 word   Std_Vars[sizeof(var_tab1)/sizeof(struct namevar)] ;
 byte  tmp_std_var[sizeof(var_tab1)/sizeof(struct namevar)][8];
#endif

const word  kol_var = sizeof(var_tab1)/sizeof(struct namevar) ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
 extern _x_far const struct namevar  var_tab1[];               // _x_far - нужно , чтоб работал LINK .
 extern _x_far const struct SlaveVars  svar[_Num_CAN_Ports];   // _x_far - нужно , чтоб работал LINK .
 extern _x_far const lword size_vartab1;                       // _x_far - нужно , чтоб работал LINK .
 extern _x_far const word crezerv ;                            // _x_far - нужно , чтоб работал LINK .

#ifdef _INTERPRETER
 extern word   Std_Vars[] ;
 extern byte  tmp_std_var[][8];
#endif

 extern const word kol_var;

#endif
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
