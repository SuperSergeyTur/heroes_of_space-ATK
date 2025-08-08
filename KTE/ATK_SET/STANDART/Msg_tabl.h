
// ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ РАЗЛИЧНЫЕ ТАБЛИЦЫ .
//------------------------------------------------------------------------------

#ifndef msg_tabl_h
#define msg_tabl_h

// В MSG.H _Device_Name_ можно переименовать :
#define _Device_Name_ "     -АТК5-     "

//----------- А8 - Таблицы битовых уставок ---------------

#define _KTE_A8_Cfg1 \
    { "Kонфіг.1    " , (w*)&_r.Cfg.all,7 ,                                    \
                               { "ШтатнеУправ.",                               \
                                 "Об'єктУправ.", \
                                  "Не реверс   ",\
                                 "АСУТП-упр.  ",                               \
                                 "N#-контроль ",                               \
                                 "ВклОбер.двиг",                                \
                                 "Частотн.IУ  "},                             \
      { _cfg_Shtat_reg  , _cfg_Obj_prg ,_cfg_Ne_Revers, _cfg_CAN_reg , _cfg_Control_ZSk ,     \
        _cfg_Vrasch_Dvig, _cfg_Fzapoln },                                      \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Cfg2 \
    { "Kонфіг.2    " , (w*)&_r.Cfg2.all,  5 ,                                  \
                               { "Увім.автофаз",                              \
                                 "УвімWatchdog",                               \
                                 "КонтрТемпШІ ",                               \
                                 "КонтрТемпШВ "   ,                               \
                                 "1VR         " },                             \
      { _cfg2_SIFU_Syn2,_cfg2_WatchdogEn,_cfg2_ContrTShI,_cfg2_ContrTShV, _cfg2_1VR },                         \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Prg \
    { "Структура   " , (w*)&Prg.all,  6 ,                                      \
                               { "Сбірка гот. ",                               \
                                 "РШ          ",                                   \
                                 "РС          ",                               \
                                 "Цикли Завдан",                               \
                                 "Блок Управл.",                               \
                                 "Слід        " },                             \
      { _Gotovn, _RegSk, _RegTok, _Cikl, _Blok_upr, _Sled },                   \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Isp \
    { "Шунтув.ЗІ   " , (w*)&Isp.all,  2 ,                                      \
                               { "Шунтув.ЗІРС ",                               \
                                 "Шунтув.ЗІРШ "},                              \
      { 0x0400 , 0x0800 },                                                     \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Sk \
    {  "Датчик швид." , (w*)&_r.Sk_str.all,  3 ,                                \
                               { "N:ПДФ       ",                               \
                                 "N:w         ",                               \
                                 "N:фільтр    "},                              \
      { _sk_PDF , _sk_EDS , _sk_filtr },                                       \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_cCfgR \
    { "АСУТП:cCfgR " , &canr.CfgReg.all  , 16 ,                                \
                               { "N#          ",                               \
                                 "Id#         ",                               \
                                 "reserved2   ",                               \
                                 "L#          ",                               \
                                 "Most        ",                               \
                                 "ЛК          ",                               \
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
    { "АСУТП:cStsR " , &canr.StatReg.all  , 16 ,                               \
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

//---------------------------------------- Порт CAN 0 ----------------------------------------
// При отсутствии выбора скорости CAN (все скорости == 0) скорость принимается равной 100 кГц .
#define _KTE_A8_CAN0cfg \
    { "CAN0-config   " , &can_setting( _CAN0_Port ).config.all, 5 ,                          \
                               { "Увімк.CAN   " ,                                            \
                                 "Увім.CANopen" ,                                            \
                                 "125кГц-500м " ,                                            \
                                 "250кГц-250м " ,                                            \
                                 "1МГц  - 25м " ,                                            \
                                  },                                           \
      { _can_cfg_vkl, _can_cfg_mcovkl, _can_cfg_bt_125k, \
      _can_cfg_bt_250k, _can_cfg_bt_1M },                                \
       (w*)&_Msk ,1                                                                          \
    }

//---------------------------------------- Порт CAN 1 ----------------------------------------
// При отсутствии выбора скорости CAN (все скорости == 0) скорость принимается равной 100 кГц .
#define _KTE_A8_CAN1cfg \
    { "CAN1-config   " , &can_setting( _CAN1_Port ).config.all, 5 ,                          \
                               { "Увімк.CAN   " ,                                            \
                                 "CAN-майстер " ,                                            \
                                 "125кГц-500м " ,                                            \
                                 "250кГц-250м " ,                                            \
                                 "1МГц  - 25м " },                                           \
      { _can_cfg_vkl, _can_cfg_master, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M }, \
       (w*)&_Msk ,1                                                                          \
    }

//---------------------------------------- Порт CAN 2 ----------------------------------------
// При отсутствии выбора скорости CAN (все скорости == 0) скорость принимается равной 100 кГц .
#ifdef _CAN2_Port
#define _KTE_A8_CAN2cfg \
    { "CAN2-config   " , &can_setting( _CAN2_Port ).config.all, 5 ,                          \
                               { "Увімк.CAN   " ,                                            \
                                 "CAN-майстер " ,                                            \
                                 "125кГц-500м " ,                                            \
                                 "250кГц-250м " ,                                            \
                                 "1МГц  - 25м " },                                           \
      { _can_cfg_vkl, _can_cfg_master, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M }, \
       (w*)&_Msk ,1                                                                          \
    }
#endif
//---------------------------------------- Modbus RTU ----------------------------------------
#ifdef _CM3_
#define _KTE_A8_MBcfg \
    { "MBRTU-config  " , &_r.rs485.config.all, 7,                                            \
                               { "Увiмк.Modbus" ,                                            \
                                 "19200 Біт/с " ,                                            \
                                 "38400 Біт/с " ,                                            \
                                 "57600 Біт/с " ,                                            \
                                 "Увім.парн.  " ,                                            \
                                 "Парність    " ,                                           \
                                 "1 стоп-біт  "},\
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

//----------- А7 - Таблицы блоков уставок ----------------

_x_far const struct STB       stb_avar[ ] =
  {
  //{ "N-макс        ", &_r.N_Max             ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "dN-дат.швид.  ", &_r.dN_Max            ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "T-dN-дат.швид.", &_or.T_dN_Max         ,_Sec( 0.0 )      ,_Sec( 20.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,3,2,2) },
  //{ "E-макс        ", &_r.E_Max             ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom(0.01) , 0xff, "ном", _form(1,2,2,2) },
    { "T-обр.сил.кола", &_r.T_Circuit         ,_fSec( 0.0 )     ,_fSec( 12.0 )     ,_fSec(1.0)    ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек", _form(1,3,2,2) },
    { "Id-мін        ", &_r.Id_Min            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "Id-макс       ", &_r.Id_Max            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#ifdef   Id_sum_ach
    { "Id-сум-макс   ", &_or.Id_sum_max       ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#endif
    { "dt-Id-макс    ", &_r.time_Id_max       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "мceк",_form(1,3,1,1) }, // !!! Это не "word" , а "byte" , до 255 пульсов .
  //{ "Id-тст-пробой ", &_r.Id_tst_proboy     ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
  //{ "If-мин        ", &_r.Iv_avar_Min       ,_Iv_nom( 0.0 )   ,_Iv_nom( 2.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
  //{ "dt-If-мин     ", &_r.time_Iv_min       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "мceк",_form(1,3,1,1) },
#ifdef _Vozb_KTE
    { "If-макс       ", &_r.Iv_avar_Max       ,_Iv_nom( 0.0 )   ,_Iv_nom( 3.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "dt-If-макс    ", &_r.time_Iv_max       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "мceк",_form(1,3,1,1) },
#endif
#ifdef bi_BV1
  #ifndef  _STOLB_1TIR
   #ifdef bi_PT   // для алгоритма включения вентиляторов по перегреву :
    { "T-відк.вент.  ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(3000.0 )     ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "хвл", _form(1,2,2,2) },
   #else
    { "T-охолодження ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(600.0 )      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "хвл", _form(1,2,2,2) },
   #endif
  #else
    { "T-охолодження ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(3.0 )        ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },
  #endif
#endif
#ifdef bo_VklVent // для алгоритма включения вентиляторов по току якоря :
    { "Id-увімк-вент.", &_or.Id_Vkl_Vent      ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "T-вимк-вентил.", &_or.T_Otkl_Vent      ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "хвл", _form(1,3,1,2) },
#endif
#ifdef _Dat_Temp_Max // для алгоритма аналогового измерения температуры каждого охладителя в каждом силовом шкафу :
    { "T-перегрiв-поп", &_or.T_Pr             , 0.*10           , 300*10           , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,1,2) },
    { "T-перегрів-ав.", &_or.T_Av             , 0.*10           , 300*10           , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,1,2) },
#endif
    { "T-відк.Імп.   ", &_r.Time_do_OtklImp   ,_Sec( 0.1 )      ,_Sec( 9.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.1)      , 0xff, "сек", _form(1,2,2,2) },
#ifdef bi_Vent_Dvig
    { "T-вент.двиг.  ", &_r.Time_otkl_VentDvig,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "хвл", _form(1,3,1,2) },
#endif
#ifdef bi_MasloSmazka
    { "T-маст.двигуна", &_r.Time_MasloSmazka  ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "хвл", _form(1,3,1,2) },
#endif
#ifdef bi_Smazka_Podsh
    { "T-маст.підшип.", &_r.Time_Smazka_Podsh ,_Sec( 0.0 )      , (sw)0xFFFF       ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "хвл", _form(1,3,1,2) },
#endif
    { "N-стоянка     ", &_r.Stoyanka_Eds      ,_Skor_nom( +0.0 ),_Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1<<_Skor_Shift , 0xff, "%"  , _form(1,3,2,2) },
    { "Id-стоянкa    ", &_r.Stoyanka_Tok      ,_Id_nom( 0.0 )   ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.10 ) , 0xff, "ном", _form(1,2,1,2) },
    { "T-авар.стоянкa", &_r.Stoyanka_Time     ,_Sec( 0.0 )      ,_Sec( 120.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "сек", _form(1,2,0,2) },
    { "T-поп. cтоянкa", &_r.Stoyanka_Time_Predupr ,_Sec( 0.0 )  ,_Sec( 120.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "сек", _form(1,2,0,2) },
  //{ "Id-конт-макс  ", &_r.Tok_Otkl_Kontaktor,_Id_nom( 0.0 )   ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.10 ), 0xff, "ном", _form(1,2,2,2) },
  //{ "Id-откл.МТ    ", &_r.Id_Otkl_MT        ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
  //{ "T-отпуск.МТ   ", &_r.Time_MT           ,_Sec( 0.0 )      ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },
    { "Uізол-макс    ", &_r.Uinsul_max        , 0               , (w)(9.9*(_AD_MAX/5.0))  ,(w)(1.0*(_AD_MAX/5.0)),(w*)&_ind_Nom,(w)(0.01*(_AD_MAX/5.0)),0xff," B"  , _form(1,2,2,2) },
    { "Id-вкл-вент.  ", &_or.Id_Vkl_VentShs1 , _Id_nom( 0.0 )  , _Id_nom( 3.5 )    , _Id_Nom          ,(w*)&_ind_Nom, _Id_nom(0.01)   , 0xff, "ном " , _form(1,2,2,2) },
    { "T-відк-вент.  ", &_or.Time_otkl_BV1   , _Sec( 0.0 )     , _Sec(3000.0 )     , _Sec(60.0)       ,(w*)&_ind_Nom, _Sec(1.0)       , 0xff, "хвл " , _form(1,2,2,2) },
    { "МінШвидВентШС.", &_or.Id_min_vent     , _Id_nom( 0.0 )  , _Id_nom( 3.5 )    , _Id_Nom          ,(w*)&_ind_Nom, _Id_nom(0.01)   , 0xff, "ном " , _form(1,2,2,2) },
    { "МаксШвидВентШС", &_or.Id_max_vent     , _Id_nom( 0.0 )  , _Id_nom( 3.5 )    , _Id_Nom          ,(w*)&_ind_Nom, _Id_nom(0.01)   , 0xff, "ном " , _form(1,2,2,2) },
    { "Затримка BV   ", &_or.TimeAvarNoVent  , 0               , _Sec(360)         , _Sec(1)          ,(w*)&_ind_Nom, _Sec(1)         , 0xff, "сек"  , _form(1,3,0,2) },
    { "ШвидВентФорс  ", &_or.Id_zad_fors  , _Id_nom( 0.0 )  , _Id_nom( 3.5 )    , _Id_Nom          ,(w*)&_ind_Nom, _Id_nom(0.01)   , 0xff, "ном " , _form(1,2,2,2) },
    { "T-перегрів-поп", &_or.T_Pr            , 0.*10           , 300*10            , 10               ,(w*)&_ind_Nom, 10             , 0xff, "гр"   , _form(0,3,1,2) },
    { "T-перегрів-ав.", &_or.T_Av            , 0.*10           , 300*10            , 10               ,(w*)&_ind_Nom, 10             , 0xff, "гр"   , _form(0,3,1,2) },
    { "dT-дат-ав.    ", &_or.dt_Av           , 0               , 100               , 1                ,(w*)&_ind_Nom, 1              , 0xff, "гр"   , _form(1,3,0,3) },
    { "Т 0 Вольт     ", &_or.T0Volt          ,-200            , 200              , 1         ,(w*)&_ind_Nom, 1             ,0xff,"Грд" ,_form(0,3,0,3) },
    { "Темп зрос.темп", &_or. TempT          ,0               , 1000             , 1         ,(w*)&_ind_Nom, 1             ,0xff,"мВ/Гр",_form(1,3,0,3) },
    { "T-опитув-плата", &_or.Time_opros      , _Sec( 0.1 )    , _Sec(2.0 )     , _Sec(1.0)       ,(w*)&_ind_Nom, _Sec(0.1)       , 0xff, "сек " , _form(1,2,2,2) },

#ifdef Insul_D_ach
  #ifndef  Uf_ach
    { "Uf-економ.реж.", &_or.Uf_econom        ,_Uf_nom( 0.00 )  ,_Uf_nom( +2.00 )  , _Uf_Nom      ,(w*)&_ind_Nom, _Uf_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
  #endif
#endif
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
    { "dIs-нач.контр.", &_or.dIs_ControlBegin ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "Is-струморозп.", &_or.Is_tokoraspred   ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#endif
//------------
 #ifndef _CM3_
//------------
#ifdef _SIFU2_
  #if   defined( _1P_ach ) || defined( _2P_ach )
    { "1Р_2P-макс    ", &_r._1P_2P_max        ,(sw)(-9.9*(_AD_MAX/5.0)), 9.9*(_AD_MAX/5.0)  ,1.0*(_AD_MAX/5.0),(w*)&_ind_Nom, 0.1*(_AD_MAX/5.0),0xff," B"  , _form(0,2,2,2) },
    { "1Р_2P-мін     ", &_r._1P_2P_min        ,(sw)(-9.9*(_AD_MAX/5.0)), 9.9*(_AD_MAX/5.0)  ,1.0*(_AD_MAX/5.0),(w*)&_ind_Nom, 0.1*(_AD_MAX/5.0),0xff," B"  , _form(0,2,2,2) },
  #endif
#endif
#ifdef PUM_ach
    { "Живлен.ПП-макс", &_r.PUM_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "Живлен.ПП-мін ", &_r.PUM_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef P12_ach
    { "P12-макс      ", &_r.P12_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "P12-мін       ", &_r.P12_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef N12_ach
    { "N12-макс      ", &_r.N12_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "N12-мін       ", &_r.N12_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
    { "1P24-макс     ", &_r.P24_max           ,-102*9.99        , 102*9.99         , 102          ,(w*)&_ind_Nom,  1              ,0xff, " B" , _form(0,2,2,2) },
    { "1P24-мін      ", &_r.P24_min           ,-102*9.99        , 102*9.99         , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) }
//------------
 #else
//------------
#ifdef _SIFU2_
  #if   defined( _1P_ach ) || defined( _2P_ach )
    { "1Р_2P-макс    ", &_r._1P_2P_max,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4           , 0xff, " B" , _form(0,2,2,2) },
    { "1Р_2P-мін     ", &_r._1P_2P_min,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4           , 0xff, " B" , _form(0,2,2,2) },
  #endif
#endif
#ifdef PUM_ach
    { "ЖивУМ-макс    ", &_r.PUM_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "ЖивУМ-мін     ", &_r.PUM_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef P12_ach
    { "P12-макс      ", &_r.P12_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "P12-мін       ", &_r.P12_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef N12_ach
    { "N12-макс      ", &_r.N12_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "N12-мін       ", &_r.N12_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
    { "1P24-макс     ", &_r.P24_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "1P24-мін      ", &_r.P24_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) }
//------------
 #endif
//------------
   ,{ "Pimp-макс інв ", &_or.Pimp_max[0]      ,0                , 999              , 1            ,(w*)&_ind_Nom,  0.1            ,0xff, " B" , _form(1,3,1,3) },
    { "Pimp-мін  інв ", &_or.Pimp_min[0]      ,0                , 999              , 1            ,(w*)&_ind_Nom,  0.1           , 0xff, " B" , _form(1,3,1,3) },
    { "Pimp-макс вип ", &_or.Pimp_max[1]      ,0                , 999              , 1            ,(w*)&_ind_Nom,  0.1            ,0xff, " B" , _form(1,3,1,3) },
    { "Pimp-мін вип  ", &_or.Pimp_min[1]      ,0                , 999              , 1            ,(w*)&_ind_Nom,  0.1           , 0xff, " B" , _form(1,3,1,3) },
    { "K Pimp        ", &_or.mV_A             ,0                , 999              , 1            ,(w*)&_ind_Nom,  0.1           , 0xff, "од" , _form(1,3,1,3) }
  };

_x_far const struct STB       stb_reg[ ] =
  {
#ifdef  _REG_POL
    { "Порог-dS-РП   ", &_r.DeltaDeadZone     , 0               ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.5 )   , 0xff, "грд", _form(1,3,2,2) },
    { "Kп-dS-РП      ", &_r.Kp_dP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  64            , 0xff, "од" , _form(1,3,2,2) },
    { "Kп-РП         ", &_r.Kp_RP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  16            , 0xff, "од" , _form(1,3,2,2) },
    { "Tи-РП         ", &_r.Ki_RP             , 0               , 999              , 1            ,(w*)&_ind_Nom,  2             , 0xff, "мceк",_form(1,3,0,2) },
#endif
    { "N#-макс       ", &_r.Z_SkMax_P         ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
  //{ "N#-мин        ", &_r.Z_SkMax_M         ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "N#-нулеве     ", &_or.Z_SkorNull       ,_Skor_nom( +0.0 ),_Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1<<_Skor_Shift , 0xff, "%"  , _form(1,3,2,2) },
    { "N-зупинка     ", &_r.Ostanov_skor      ,_Skor_nom( +0.0 ),_Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1<<_Skor_Shift , 0xff, "%"  , _form(1,3,2,2) },
  //{ "T-зупинка     ", &_r.Ostanov_time      ,_Sec( 0.1 )      ,_Sec( 9.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,1,2,2) },
#ifndef  _ZI_30min
  #ifdef _ZI_4TEMPA
    { "ТемпЗІ-РШВп'+'", &_r.T_ZISkorP_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗІ-РШВп'-'", &_r.T_ZISkorP_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗІ-РШНз'+'", &_r.T_ZISkorM_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗІ-РШНз'-'", &_r.T_ZISkorM_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #ifdef bi_Reviz
    { "ТемпЗІ-РШ'рвз'", &_or.T_ZISkor_Reviz   ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #endif
   #ifdef bi_Fors_Temp
    { "ТемпЗІ-РШ'фрс'", &_r.T_ZISkorP_Fors    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #endif
  #else
    { "ТемпЗІ-РШ'+'  ", &_r.T_ZISkorP_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
    { "ТемпЗІ-РШ'-'  ", &_r.T_ZISkorP_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
   #ifdef bi_Reviz
    { "ТемпЗІ-РШ'рвз'", &_or.T_ZISkor_Reviz   ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
   #endif
   #ifdef bi_Fors_Temp
    { "ТемпЗІ-РШ'фрс'", &_r.T_ZISkorP_Fors    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
   #endif
  #endif
#else
    { "ТемпЗІ-РШ'+'  ", &_r.T_ZISkorP_Razg    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "хвл", _form(1,2,1,2) },
    { "ТемпЗІ-РШ'-'  ", &_r.T_ZISkorP_Torm    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "хвл", _form(1,2,1,2) },
 #ifdef bi_Fors_Temp
    { "ТемпЗІ-РШ'фрс'", &_r.T_ZISkorP_Fors    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "хвл", _form(1,2,1,2) },
 #endif
#endif
    { "ТeмпЗІ-РШ's'  ", &_r.T_ZISkor_Parab,       _Sec( 0.0 ),       _Sec( 20.0 ),     _Sec( 1.0 ),(w*)&_ind_Nom, _Sec( 0.1 )    , 0xff, "сек", _form(1,3,2,2) },
    { "ТeмпЗІ-РШ-dN  ", &_r.T_ZISkor_Parab_delta, _Skor_nom( 0.0 ),  _Skor_nom( 1.0 ), _Skor_Nom  ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
#ifdef  TGx_ach
    { "ТГx8-поріг    ", &_r.TGx8_porog        ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_nom(0.01),(w*)&_ind_Nom, 4             , 0xff, "%"  , _form(1,3,2,2) },
#endif
    { "Поріг-ФШ      ", &_r.porog_fil         ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
    { "K-ФШ          ", &_r.K_fil_sk          , 2               , 1000             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "од" , _form(1,3,0,2) },
//  { "Порог-ФЭДС    ", &_r.Porog_FE          , 0               , 1600             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,2) },
//  { "K-ФЭДС        ", &_r.K_FE              , 2               , 1000             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,2) },
#ifdef bi_RS_P
    { "Kп-РШ (ПІ-рег)", &_r.KRSP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "од" , _form(1,3,2,2) },
#else
    { "Kп-РШ         ", &_r.KRSP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "од" , _form(1,3,2,2) },
#endif
    { "Tі-РШ         ", &_r.KRSI              , 0               , 2000             , 1            ,(w*)&_ind_Nom,  2             , 0xff, "мceк",_form(1,4,0,2) },
#ifdef bi_RS_P
    { "Kп-РШ (П-рег) ", &_r.KRSP_for_P        , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "од" , _form(1,3,2,2) },
    { "Темп П/ПІ адап", &_r.Adapt_temp        ,_Id_nom( 0.0 )   ,_Id_nom( 20.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.05 ), 0xff, "ном", _form(1,2,2,2) },
#endif
    { "Kпіп-РШ       ", &_r.KRSPIP            , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "од" , _form(1,3,2,2) },
#ifdef bi_Reviz
    { "Kп-РШ-Ревізія ", &_or.KRSP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "од" , _form(1,3,2,2) },
    { "Tі-РШ-Ревізія ", &_or.KRSI             , 0               , 2000             , 1            ,(w*)&_ind_Nom,  2             , 0xff, "мceк",_form(1,4,0,2) },
    { "Kпіп-РШ-Ревіз ", &_or.KRSPIP           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "од" , _form(1,3,2,2) },
#endif
#ifdef _RDN
    { "Поріг-РДН     ", &_r.RDN_Dead_Zone     ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "K-РДН         ", &_r.RDN_Kp            , 0               , (sw)0xA000u      , 0x0100*(_Skor_Nom/_Id_Nom) ,(w*)&_ind_Nom,40, 0xff, "од" , _form(1,2,2,2) },
    { "dN#-РДН-макс  ", &_r.RDN_Max           ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Tфільтр-РДН   ", &_r.RDN_Tfiltr        , 0               , 999              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мceк",_form(1,3,0,2) },
#endif
#ifdef _RRS
    { "T-мех         ", &_r.T_meh             ,_Id_nom( 0.0 )   , _Id_nom( 30.0 )  ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "Т-ф-стат.струм", &_r.T_flt_Stat        ,_fSec( 0.0)      , _fSec( 10 )      ,_fSec(1)      ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек", _form(1,2,2,2) },
    { "Кртн.стат.стр ", &_r.puls_Istat        , 0               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) },
    { "N#-захопл.1   ", &_r.Sk_zahv1          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "N#-захопл.2   ", &_r.Sk_zahv2          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Iстат-захопл. ", &_r.Porog_Istat       ,_Id_nom( 0.0 )   , _Id_nom( 3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "T-захопл.     ", &_r.T_zahv            ,_fSec( 0.0 )     , _fSec(2.0 )      ,_fSec(1.0)    ,(w*)&_ind_Nom,  _fSec(0.01)   , 0xff, "сек", _form(1,2,2,2) },
    { "T-лижі        ", &_r.T_liga            ,_fSec( 0.0 )     , _fSec(2.0 )      ,_fSec(1.0)    ,(w*)&_ind_Nom,  _fSec(0.01)   , 0xff, "сек", _form(1,2,2,2) },
    { "K-лижі        ", &_r.K_liga            , 0               , 1*256            , 256          ,(w*)&_ind_Nom,  3             , 0xff, "од" , _form(1,3,2,2) },
#endif
#ifdef _BUKSOVKA
    { "Букс-Id-визн. ", &_r.Id_RDN_off        ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "Букс-Id-відп. ", &_r.Id_RDN_on         ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "Букс-N-визн.  ", &_r.N_RDN_off         ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Букс-N-відп.  ", &_r.N_RDN_on          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "T-визн.букс.  ", &_r.Time_Buksov       ,_fSec( 0.0 )     ,_fSec( 12.0 )     ,_fSec(1.0)    ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек", _form(1,3,2,2) },
    { "Лічильн.букс. ", &_r.count_Buk_f       , 0               , 15               , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) },
#endif
#ifdef _RVId
    { "Поріг-РВ      ", &_r.RVId_Dead_Zone    ,_Id_nom( 0.0 )   ,_Id_nom( 2.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "Kп-PВ         ", &_r.RVId_Kp           , 0               , 0x13FE           , 0x0100*(_Iv_Nom/_Id_Nom)   ,(w*)&_ind_Nom, 5, 0xff, "од" , _form(1,2,2,2) },
    { "РВId-макс     ", &_r.RVId_Max          ,_Iv_nom( +0.0 )  ,_Iv_nom( +2.0 )   ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#endif
  //{ "Id#-макс      ", &_r.IZMAX             ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", 2 },
    { "Id#-макс1P    ", &_r.OuRSMaxMost1      ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "Id#-макс1M    ", &_r.OuRSMaxMost2      ,_Id_nom(-3.5 )   ,_Id_nom( 0.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
  //{ "Id#-макс2P    ", &_r.OuRSMax2Most1     ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
  //{ "Id#-макс2M    ", &_r.OuRSMax2Most2     ,_Id_nom(-3.5 )   ,_Id_nom( 0.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
  //{ "Id-гр-непp    ", &_r.INN0              ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "Id-ІУ-гр-бесп ", &_or.Id_IU            ,_Id_nom( 0.0 )   ,_Id_nom( 0.2 )    ,_Id_nom(0.01) ,(w*)&_ind_Nom,  2             , 0xff, "%"  , _form(1,2,2,2) },
    { "Лічильн.Id-гр.", &_or.i_count          , 1               , 12               , 1            ,(w*)&_ind_Nom,  1             , 0xff, "од" , _form(1,2,0,2) },
#ifdef  _SIFU2_
    { "Id-гр-безп-дв ", &_or.INN0_dvig        ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom,  1*_K_diskr    , 0xff, "ном", _form(1,2,3,2) },
    { "Коэфф-INN     ", &_or.KINN             , 0x0050          , 0x0125           , 0x0100       ,(w*)&_ind_Nom,  1             , 0xff, "од" , _form(1,2,3,2) },
#endif
    { "ТемпЗІ-РС'+'  ", &_r.Temp_RT_P         ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "ном " , _form(1,4,1,2) },
    { "ТемпЗІ-РС'-'  ", &_r.Temp_RT_M         ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "ном " , _form(1,4,1,2) },
    { "ТемпЗІ-РС'+'пр", &_or.Temp_RT_P        ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "ном " , _form(1,4,1,2) },
    { "ТемпЗІ-РС'-'пр", &_or.Temp_RT_M        ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "ном " , _form(1,4,1,2) },
  //{ "'Kп-РТ        ", &_r_KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "ед" , _form(1,3,2,2) },
  //{ "'Kп-РТ-AH     ", &an_KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "ед" , _form(1,3,2,2) },
    { "Kп-РС         ", &_r.KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  4             , 0xff, "од" , _form(1,3,2,2) },
  //{ "'Ти-РТпреp    ", &_r_KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
  //{ "'Ти-РТпреp-AH ", &an_KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ті-РСпер      ", &_r.KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  1             , 0xff, "мceк",_form(1,3,2,2) },
  //{ "'Ти-РТнепp    ", &_r_KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
  //{ "'Ти-РТнепp-AH ", &an_KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ті-РСбеспер   ", &_r.KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "мceк",_form(1,3,2,2) },
    { "Kі-РС-пер     ", &_or.KRTP             , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  4             , 0xff, "од" , _form(1,3,2,2) },
    { "Ті-РСпер-пр   ", &_or.KRTPRI           , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  1             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ті-РСбеспе-пр ", &_or.KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "мceк",_form(1,3,2,2) },
    { "K-РС-дін      ", &_r.KRTDI             , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "од" , _form(1,3,0,2) },
#ifdef  _SIFU2_
    { "Id-гр-безп-РС2", &_or.INN0_2_          ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "'Kп-РС2       ", &_or_KRTP_2_          , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "од" , _form(1,3,2,2) },
    { "'Kп-РС2-AH    ", &an_KRTP_2_           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "од" , _form(1,3,2,2) },
    { "Kп-РС2-уст    ", &_or.KRTP_2_          , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  4             , 0xff, "од" , _form(1,3,2,2) },
    { "'Ті-РС2пер    ", &_or_KRTPRI_2_        , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "'Ті-РС2пер-AH ", &an_KRTPRI_2_         , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ті-РС2пеp-уст ", &_or.KRTPRI_2_        , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  1             , 0xff, "мceк",_form(1,3,2,2) },
    { "'Ті-РС2безп   ", &_or_KRTNI_2_         , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "'Ті-РС2безп-AH", &an_KRTNI_2_          , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ті-РС2безп-уст", &_or.KRTNI_2_         , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "мceк",_form(1,3,2,2) },
#endif
    { "РС-вих-макс   ", &_r.RTMAX             ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "РС-вих-мін    ", &_r.RTMIN             ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-макс       ", &_r.S_Alfa_Max        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-мін        ", &_r.S_Alfa_Min        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-початкове  ", &_r.S_Alfa_Start      ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "ТемпЗІ-L#     ", &_r.S_DeltaAlfa_Max   ,_Grad( 0.0 )     ,_Grad(  25.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L-вимірюв.Id  ", &_r.S_Alfa_IzmId      ,_Grad( 11.5 )    ,_Grad(  20.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.1 )   , 0xff, "грд", _form(1,3,2,2) },
    { "L-вимірюв.Ud  ", &_r.S_Alfa_IzmDoImp   ,_Grad( 1.0 )     ,_Grad(  3.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.1 )   , 0xff, "грд", _form(1,3,2,2) },
#ifndef  _SIFU2_
    { "'Фазув.інвер:N", &_r.S_FazirovVS       , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ТПK", _form(1,2,0,1) },
    { "'Фазув.інвер:F", &_r.S_FazirovUgol     ,_Grad( 0.0 )     ,_Grad( 60.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom,  0             , 0xff," грд", _form(1,3,0,2) },
#else
    { "'Фазув.пров:N ", &_r.S_FazirovVS       , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ТПK", _form(1,2,0,1) },
    { "'Фазув.пров:F ", &_r.S_FazirovUgol     ,_Grad( 0.0 )     ,_Grad( 60.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom,  0             , 0xff," грд", _form(1,3,0,2) },
    { "'Фазув.веден:N", &_r.S2.FazirovVS      , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ТПK", _form(1,2,0,1) },
    { "Kп-РЗС-веден. ", &_r.S2.Kp_rvt         , 0               , 3000             , 64           ,(w*)&_ind_Nom,  1             , 0xff, "од" , _form(1,3,2,2) },
    { "Kи-РЗС-веден. ", &_r.S2.Ki_rvt         , 0               , 3000             , 64           ,(w*)&_ind_Nom,  1             , 0xff, "од" , _form(1,3,2,2) },
    { "РВС-вих-макс  ", &_r.S2.RVTmax         , 0               , 5*64             , 64           ,(w*)&_ind_Nom,  16            , 0xff, "грд", _form(1,2,2,2) },
    { "РВС-вих-Id-гр ", &_or.RVT_INN0         ,_Grad( -5.0 )    ,_Grad( 5.0 )      ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.05 )  , 0xff, "грд", _form(0,1,3,2) },
#endif
    { "U0-реверс     ", &_r.RevU0             ,_Grad( 000.0 )   ,_Grad( 180.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,0,2) },
    { "Id-реверс     ", &_r.RIDRR             ,_Id_nom( 0.0 )   ,_Id_nom( 0.50 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "dt-реверс     ", &_r.dt_revers         , 0               ,_pSec( 10.0 )     ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "мceк",_form(1,3,1,2) },
  /*{ "K-Kомп-Ud     ", &_r.K_Kompen_Ud       , 0               , 100              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,2) },
    { "K-ЭДС-Р       ", &_r.KEDS_R            , 0               , 255              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,1) },
    { "K-ЭДС-П       ", &_r.KEDS_P            , 0               , 255              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,1) },
    { "K-ЭДС-Т       ", &_r.KEDS_T            , 0               , 255              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,1) },
    { "E#рсч-2й-зоны ", &_r.Z_EDS             ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom( 0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Nрсч-2й-зоны  ", &_r.Skor2Z            ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "E#-2й-зоны    ", &_r.Z_II_EDS          ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom( 0.01), 0xff, "ном", _form(1,2,2,2) },
    { "'N-2й-зоны    ", &Skor_II_Z            ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom,  0             , 0xff, "ном", _form(1,2,2,2) },
    { "Kп-РегЭДС     ", &_r.Kp_REDS           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  3             , 0xff, "ед" , _form(1,4,2,2) },
    { "Tи-РегЭДС     ", &_r.Ki_REDS           , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "мceк",_form(1,3,0,2) },
    { "Kп-РегЭДС-2з. ", &_r.DT_ZISk           , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  3             , 0xff, "ед" , _form(1,4,2,2) },
    { "Tи-РегЭДС-2з. ", &_r.Ki_REDS_II_Z      , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "мceк",_form(1,3,0,2) },
    { "Kп-РC-2з.     ", &_r.KRSP_II_Z         , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "ед" , _form(1,3,2,2) },
    { "Tи-РC-2з.     ", &_r.KRSI_II_Z         , 0               , 999              , 1            ,(w*)&_ind_Nom,  2             , 0xff, "мceк",_form(1,3,0,2) },
  //{ "Kпип-РC-2з.   ", &_r.KRSPIP_II_Z       , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "ед" , _form(1,3,2,2) },
    { "If#-макс      ", &_r.Iv_zad_Max        ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(1,3,2,2) },
    { "If#-мин/эконом", &_r.Iv_zad_Min        ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(1,3,2,2) },
    { "If#-1-зонных  ", &_r.Iv_zad            ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(1,3,2,2) },
    { "If#-гашение   ", &_r.Iv_gashen         ,_Iv_nom( -0.1 )  ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(0,3,2,2) },
    { "T-эконом.поля ", &_r.T_econom          ,_Sec( 0.0 )      ,_Sec( 600.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.5)      , 0xff, "сек", _form(1,3,2,2) },
    { "T-гашен.поля  ", &_r.T_gashenie        ,_Sec( 0.0 )      ,_Sec( 600.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.5)      , 0xff, "сек", _form(1,3,2,2) },
#ifdef _Rev_Pola
    { "If-минРевПоля ", &_r.Iv_porg_Min       ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(1,3,2,2) },
#endif
#ifdef _Vozb_KTE
    { "If-удерж.     ", &_r.Iv_null           ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(1,3,2,2) },
    { "Kп-РТВ        ", &_r.V_Kp_rt           , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,4,0,2) },
    { "Kи-РTВ        ", &_r.V_Ki_rt           , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,4,0,2) },
    { "'Фазир.возб.:N", &_r.V_FazirovVS       , 1               , 6                , 1            ,(w*)&_ind_Nom,  0             , 0xff," ТЕK", _form(1,2,0,1) },
    { "'Фазир.возб.:F", &_r.V_FazirovUgol     ,_Grad( 0.0 )     ,_Grad( 60.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom,  0             , 0xff," грд", _form(1,3,0,2) },
    { "T-отк.имп.воз.", &_r.V_Time_do_OtklImp ,_Sec( 0.1 )      ,_Sec( 6.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.1)      , 0xff, "сек", _form(1,2,2,1) },
    { "Lf#-мин       ", &_r.V_Alfa_Min        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,0,2) },
    { "Lf#-макс      ", &_r.V_Alfa_Max        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,0,2) },
    { "Lf#-текущее   ", &V.Alfa               ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,2,2) },
#endif
    { "If#-текущее   ", &V.Iv_zad             ,_Iv_nom( 0.0 )   ,_Iv_nom( 1.3 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom( 0.01 ), 0xff, "ном", _form(0,3,2,2) },*/
    { "N#-поточне    ", &Z_Skor               ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "Id#-поточне   ", &OuRegS_dop_kod       ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "L#-поточне    ", &S.Alfa               ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,2,2) }
  };

_x_far const struct STB       peregr[ ] =
  {
    { "Id_I1     "    , &_r.I2Tr.I[0]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T1     "    , &_r.I2Tr.T[0]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  100           , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I2     "    , &_r.I2Tr.I[1]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T2     "    , &_r.I2Tr.T[1]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  10            , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I3     "    , &_r.I2Tr.I[2]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T3     "    , &_r.I2Tr.T[2]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I4     "    , &_r.I2Tr.I[3]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T4     "    , &_r.I2Tr.T[3]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I5     "    , &_r.I2Tr.I[4]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T5     "    , &_r.I2Tr.T[4]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,5,0,2) },
    { "Id-інтегр."    , &Id_TeploIntegr       ,_Id_nom( 0.99 )  ,_Id_nom( 1.00 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_To     "    , &_r.I2Tr.Tohl         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  10            , 0xff, "сек", _form(1,5,0,2) }
  };

_x_far const struct STB       stb_masht[ ] =
  {
  //{ "Id-масштаб    ", &_r.Mashtab_Id        , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "ед" , 2 },
    { "Id-ном-АТК    ", &_sr.NOM.Id.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A" , _form(1,5,0,2) },
    { "Id-ном-ДС     ", &_sr.Dat.Id           , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A" , _form(1,5,0,2) },
    { "'Id-макс-ДС   ", &Mashtab.Id_max       , 0               , _Id_nom( 7.0 )   , _Id_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "ном", _form(1,2,2,2) },
    { "'Id-масштаб   ", &Mashtab.Id           , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "од" , _form(1,3,2,2) },
  //{ "Ud-масштаб    ", &_r.Mashtab_Ud        , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "ед" , 2 },
    { "Ud-ном-АТК    ", &_sr.NOM.Ud.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B" , _form(1,5,0,2) },
    { "Ud-ном-ДН     ", &_sr.Dat.Ud           , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B" , _form(1,5,0,2) },
    { "'Ud-макс-ДН   ", &Mashtab.Ud_max       , 0               , _Ud_nom( 7.0 )   , _Ud_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "ном", _form(1,2,2,2) },
    { "'Ud-масштаб   ", &Mashtab.Ud           , (sw)0xF700      , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "од" , _form(1,3,2,2) },
  //{ "If-масштаб    ", &_r.Mashtab_Iv        , 0               , 0x0EFF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "ед" , 2 },
//  { "If-ном-Двиг.  ", &_sr.NOM.Iv.fe        , 0               , 0x7fff           , 10           ,(w*)&_ind_Nom, 1              , 0xff, " A" , _form(1,5,1,2) },
//  { "If-ном-ДТ     ", &_sr.Dat.Iv           , 0               , 0x7fff           , 10           ,(w*)&_ind_Nom, 1              , 0xff, " A" , _form(1,5,1,2) },
//  { "'If-макс-ДТ   ", &Mashtab.Iv_max       , 0               , _Iv_nom( 7.0 )   , _Iv_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "ном", _form(1,2,2,2) },
//  { "'If-масштаб   ", &Mashtab.Iv           , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "ед" , _form(1,3,2,2) },
//  { "ТГ-масштаб    ", &_r.Mashtab_OS_TG     , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },
    { "Uмер-ном      ", &_or.Uset_nom         , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B" , _form(1,5,0,2) },
    { "Uрот-ном      ", &_or.Urot_nom         , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B" , _form(1,5,0,2) },
#ifdef  TGx_ach
    { "ТГx8-масштаб  ", &_r.Mashtab_OS_TGx    , (sw)0xF600      , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) },
#endif
#ifdef  EDS_ach
    { "Eапар-масштаб", &_r.Mashtab_EDS       , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
#ifdef   Itt_ach
    { "Idtt-масштаб ", &_r.Mashtab_Idtt      , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
    { "Is-масштаб    ", &_r.Mashtab_Idtt      , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
#ifdef   Id_sum_ach
    { "Id-сум-масшт. ", &_or.Mashtab_Id_sum   , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
#ifdef   It_ach
    { "It-масштаб    ", &_r.Mashtab_It        , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
  //{ "N#-масштаб    ", &_r.Mashtab_ZSkA      , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },
  //{ "N(Eап)-масштаб", &_or.Mashtab_N_po_EDS , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },
  //{ "N(Eпр)-масштаб", &_or.Mashtab_Npr_po_EDS,0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },
#ifdef Id_2v_ach  // Измерение канала Id-2вал :
    { "Id-2d-масшт.  ", &_r.Mashtab_Id_2v     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
#ifdef N_2v_ach  // Измерение канала N-2вал :
    { "N-2d-масшт.   ", &_r.Mashtab_N_2v      , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,3,2) },
#endif
  //{ "K-перегруз    ", &_r.Koef_Id_teplo     , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "ед" , _form(1,3,2,2) },
    { "ПДФ0-імп/об.  ", &_r.PDF[0].imp        , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 2              , 0xff, "од" , _form(1,5,0,2) },
  //{ "ПДФ-нуль      ", &_r.PDF[0].null       ,_Grad(-179.0 )   ,_Grad(+179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(0,3,1,2) },
  //{ "ПДФ0-масштаб  ", &_r.PDF[0].masht      , (sw)0xF000      , 0x3000           ,_PDF_delitel  ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,1,3,2) },
  //{ "ПДФ0-масштаб  ", &_r.PDF[0].masht      , 0               , (sw)0xFFFFu      ,_PDF_delitel  ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,2,3,2) },
    { "N-ном-Двиг.   ", &_or.N_nom            , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " Об/хвл", _form(1,5,0,2) },
    { "'N-сінхр-Двиг.", &N_ob_minSynhr        , 0               , 3000             , 1            ,(w*)&_ind_Nom, 0              , 0xff, " Об/хвл", _form(1,5,0,3) },
    { "N-ном-Редукт. ", &_sr.NOM.N.fe         , 0               , (sw)0xffff-100   , 10           ,(w*)&_ind_Nom, 1              , 0xff, " Об/хвл", _form(1,5,1,2) },
    { "'Z-пари полюс.", &Pary_AD              , 1               , 16               , 1            ,(w*)&_ind_Nom, 0              , 0xff, " пар", _form(1,2,0,2) },
#ifdef _Sels_shift0
    { "Сельс0g-K-філ.", &_or.Sels_shift0      , 0               , 7                , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) },
#endif
  //{ "Сельс0g-нуль  ", &_r.Selsin[0].null    ,_Grad(-179.0 )   ,_Grad(+179.0)     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.25 )  , 0xff, "грд", _form(0,3,1,2) },
#ifdef _Sels_mashtP0
    { "Сельс0m-мсш`+`", &_or.Sels_mashtP0     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "од" , _form(1,3,2,2) },
#endif
#ifdef _Sels_mashtM0
    { "Сельс0m-мсш`-`", &_or.Sels_mashtM0     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "од" , _form(1,3,2,2) },
#endif
  //{ "Сельс0m-масшт.", &_r.Selsin[0].masht   , (sw)0xF000      , 0x0F00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,1,3,2) },
#ifdef _Sels_shift1
    { "Сельс1g-K-фил.", &_or.Sels_shift1      , 0               , 7                , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) },
#endif
  //{ "Сельс1g-нуль  ", &_r.Selsin[1].null    ,_Grad(-179.0 )   ,_Grad(+179.0)     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 0.25 )  , 0xff, "грд", _form(0,3,1,2) },
#ifdef _Sels_mashtP1
    { "Сельс1m-мсш`+`", &_or.Sels_mashtP1     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "од" , _form(1,3,2,2) },
#endif
#ifdef _Sels_mashtM1
    { "Сельс1m-мсш`-`", &_or.Sels_mashtM1     , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "од" , _form(1,3,2,2) },
#endif
  //{ "Сельс1m-масшт.", &_r.Selsin[1].masht   , (sw)0xF000      , 0x0F00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,1,3,2) },
#ifdef _Rev_Pola
    { "Id#/F#-масшт. ", &_r.Mashtab_Idz_Ivz   , (sw)0xF000      , 0x7fff           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,1,3,2) },
#endif
#ifdef  Ttrans_ach
    { "Кф-парам.     ", &_or.Filtr_Param      , 1               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од", _form(1,4,1,2) },
    { "Ttr-попер.    ", &_or.Ttr_predupr      , 0               ,  300*10          , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,0,2) },
    { "Ttr-4мА       ", &_or.Ttr_4mA          , -50.*10         ,  300*10          , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,0,2) },
    { "Ttr-20мА      ", &_or.Ttr_20mA         , 0               ,  300*10          , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,0,2) }
#endif
#ifdef  Nzad_4_20_ach
    { "Кф-парам-N#.  ", &_or.Filtr_Param_Nzad , 1               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од", _form(1,4,1,2) },
    { "N#-4мА        ", &_or.Nzad_4mA         ,_Skor_nom( +0.00),_Skor_nom( +2.00 ), _Skor_nom( +0.01 ) ,(w*)&_ind_Nom, 8        , 0xff, "%"  , _form(1,2,2,2) },
    { "N#-20мА       ", &_or.Nzad_20mA        ,_Skor_nom( +0.00),_Skor_nom( +2.00 ), _Skor_nom( +0.01 ) ,(w*)&_ind_Nom, 8        , 0xff, "%"  , _form(1,2,2,2) },
#endif
    { "DAC0-масшт.   ", &_or.dac_numb[0].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) },
 #ifdef _DAC_OFFSET
    { "'DAC0-зміщ.0  ", &_or.dac_numb[0].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) },
 #endif
    { "DAC1-масшт.   ", &_or.dac_numb[1].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC1-зміщ.0  ", &_or.dac_numb[1].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#ifdef  _PPG_for_DAC2
   ,{ "DAC2-масшт.   ", &_or.dac_numb[2].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC2-зміщ.0  ", &_or.dac_numb[2].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC3
   ,{ "DAC3-масшт.   ", &_or.dac_numb[3].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC3-зміщ.0  ", &_or.dac_numb[3].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC4
   ,{ "DAC4-масшт.   ", &_or.dac_numb[4].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC4-смещ.0  ", &_or.dac_numb[4].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC5
   ,{ "DAC5-масшт.   ", &_or.dac_numb[5].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC5-смещ.0  ", &_or.dac_numb[5].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC6
   ,{ "DAC6-масшт.   ", &_or.dac_numb[6].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC6-смещ.0  ", &_or.dac_numb[6].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC7
   ,{ "DAC7-масшт.   ", &_or.dac_numb[7].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC7-смещ.0  ", &_or.dac_numb[7].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
  };

_x_far const struct STB       stb_serv[ ] =
  {
    { "След-крат.    ", &sled.kratn           , 0               , 31               , 1000         ,(w*)&sled.dt_scan, 1          , 0xff, "мсек", _form(1,3,2,2) },
#ifdef _JOURNAL
    { "Журнал-крат.  ", &TabJrn.dt_scan       , _fSec(0)        , _fSec(5.0)       , _fSec(1.0)   ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек" , _form(1,1,2,2) },
#endif
#ifdef _WatchDog
    { "Час WatchDog  ", &_r.WD_time           , 0               ,1100              , 1            ,(w*)&_ind_Nom, 50             , 0xff, "мсeк", _form(1,4,0,2) },
#endif
  //{ "След-скан.    ", &sled.dt_scan         , 0               ,_MkSec(50u*1000u) ,_MkSec(1000)  ,(w*)&_ind_Nom, _MkSec(100)    , 0xff, "мсек", _form(1,2,2,2) },
  /*{ "cS#           ", &canr.S_zad           ,_Grad( 0.0 )     ,_Grad( 359.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(0,4,0,2) },
    { "cN#           ", &canr.N_zad           ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "cId#          ", &canr.Id_zad          ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "ном", _form(0,2,2,2) },
    { "cdId#         ", &canr.dId_zad         ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "ном", _form(0,2,2,2) },
    { "cId#P         ", &canr.Idz_MaxP        ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "ном", _form(0,2,2,2) },
    { "cId#M         ", &canr.Idz_MaxM        ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "ном", _form(0,2,2,2) },
    { "cL#           ", &canr.L_zad           ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,0,2) },
    { "cL#min        ", &canr.L_min           ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,0,2) },
    { "cF#           ", &canr.F_zad           ,_Fv_nom( -1.3 )  ,_Fv_nom( 1.3 )    ,_Fv_Nom       ,(w*)&_ind_Nom, _Fv_nom( 0.01 ), 0xff, "ном", _form(0,3,2,2) },*/
#ifndef _F16e
  /*{ "CS:cAi0       ", &_or.Ai_CS[0]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
    { "CS:cAi1       ", &_or.Ai_CS[1]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
    { "CS:cAi2       ", &_or.Ai_CS[2]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
    { "CS:cAi3       ", &_or.Ai_CS[3]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
    { "CS:cAi4       ", &_or.Ai_CS[4]         ,-1               , 14               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },*/
#ifdef _AsPo0_
    { "CS:AsPo0      ", &_or.AS_CSo[0]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo1_
    { "CS:AsPo1      ", &_or.AS_CSo[1]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo2_
    { "CS:AsPo2      ", &_or.AS_CSo[2]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo3_
    { "CS:AsPo3      ", &_or.AS_CSo[3]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo4_
    { "CS:AsPo4      ", &_or.AS_CSo[4]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo5_
    { "CS:AsPo5      ", &_or.AS_CSo[5]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo6_
    { "CS:AsPo6      ", &_or.AS_CSo[6]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPo7_
    { "CS:AsPo7      ", &_or.AS_CSo[7]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi0_
    { "CS:AsPi0      ", &_or.AS_CSi[0]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi1_
    { "CS:AsPi1      ", &_or.AS_CSi[1]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi2_
    { "CS:AsPi2      ", &_or.AS_CSi[2]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi3_
    { "CS:AsPi3      ", &_or.AS_CSi[3]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi4_
    { "CS:AsPi4      ", &_or.AS_CSi[4]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi5_
    { "CS:AsPi5      ", &_or.AS_CSi[5]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi6_
    { "CS:AsPi6      ", &_or.AS_CSi[6]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi7_
    { "CS:AsPi7      ", &_or.AS_CSi[7]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi8_
    { "CS:AsPi8      ", &_or.AS_CSi[8]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi9_
    { "CS:AsPi9      ", &_or.AS_CSi[9]        ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi10_
    { "CS:AsPi10     ", &_or.AS_CSi[10]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi11_
    { "CS:AsPi11     ", &_or.AS_CSi[11]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi12_
    { "CS:AsPi12     ", &_or.AS_CSi[12]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi13_
    { "CS:AsPi13     ", &_or.AS_CSi[13]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi14_
    { "CS:AsPi14     ", &_or.AS_CSi[14]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#ifdef _AsPi15_
    { "CS:AsPi15     ", &_or.AS_CSi[15]       ,-1               , 10               , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(0,2,0,1) },
#endif
#endif //_F16e
    { "T-connectCfg  ", &_r.T_Connect_cfg     ,_Sec( 0.0 )      ,_Sec( 5.0 )       ,_Sec( 1.0 )   ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,2,2,2) },
    { "T-connectSts  ", &_r.T_Connect_sts     ,_Sec( 0.0 )      ,_Sec( 5.0 )       ,_Sec( 1.0 )   ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,2,2,2) },
    { "Tаймаут CAN0  ", &_r.can[0].connect    , 0               , 100              , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек", _form(1,3,0,1) },
    { "CAN0-адреcа 1 ", &can_setting( _CAN0_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" ,  _form(1,3,0,1) },
    { "CAN0-адреcа 2 ", &can_setting( _CAN0_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" ,  _form(1,3,0,1) },
    { "CAN0-сіткa    ", &can_setting( _CAN0_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" ,  _form(1,3,0,1) },
    { "Tаймаут CAN1  ", &_r.can[1].connect                         , 0    , 100    , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек", _form(1,3,0,1) },
    { "CAN1-адреcа 1 ", &can_setting( _CAN1_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" ,  _form(1,3,0,1) },
    { "CAN1-адреcа 2 ", &can_setting( _CAN1_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" ,  _form(1,3,0,1) },
    { "CAN1-сіткa    ", &can_setting( _CAN1_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" ,  _form(1,3,0,1) }
#ifdef _CAN2_Port
   ,{ "Tаймаут CAN2  ", &_r.can[2].connect                         , 0    , 100    , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек", _form(1,3,0,1) },
    { "CAN2-адреcа 1 ", &can_setting( _CAN2_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) },
    { "CAN2-адреcа 2 ", &can_setting( _CAN2_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) },
    { "CAN2-сіткa    ", &can_setting( _CAN2_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) }
#endif
#ifdef _CAN_MASTER
    #ifdef _A7_CAN_MASTER_Ust
          ,_A7_CAN_MASTER_Ust,
    #endif
    { "T-MconnectCfg ", &_r.T_mConnect_cfg    ,_Sec( 0.0 )      ,_Sec( 5.0 )       , _Sec(1.0)    ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,2,2,2) },
    { "T-MconnectSts ", &_r.T_mConnect_sts    ,_Sec( 0.0 )      ,_Sec( 5.0 )       , _Sec(1.0)    ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,2,2,2) },
    { "CAN-такт      ", &_r.time_scan         ,_fSec( 0.0 )     ,_fSec( 1.0 )      , _fSec( 1.0)  ,(w*)&_ind_Nom,_fSec(0.001)    , 0xff, "cек", _form(1,1,3,2) }
#endif
#ifdef _CM3_
   ,{ "Modbus-адреcа ", &_r.rs485.addr        , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(1,3,0,1) }
#endif
  };

#ifdef _CM3_
const _x_far struct STB       stb_ADC_masht[ ] =
  {
    { "Масшт.n0 ", &_ar.ADC_Scale[0]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n1 ", &_ar.ADC_Scale[1]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n2 ", &_ar.ADC_Scale[2]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n3 ", &_ar.ADC_Scale[3]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n4 ", &_ar.ADC_Scale[4]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n5 ", &_ar.ADC_Scale[5]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n6 ", &_ar.ADC_Scale[6]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n7 ", &_ar.ADC_Scale[7]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n8 ", &_ar.ADC_Scale[8]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n9 ", &_ar.ADC_Scale[9]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n10", &_ar.ADC_Scale[10] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n11", &_ar.ADC_Scale[11] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n12", &_ar.ADC_Scale[12] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n13", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n14", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) },
    { "Масшт.n15", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "од " , _form(1,1,4,2) }
 };
#endif
/*
_x_far const struct STB       stb_shtat[ ] =
  {
    { "ИЗУ'>'-макс   ", &_r.ZSkBM_MaxB        ,_Skor_nom(  0.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "ИЗУ'<'-мин    ", &_r.ZSkBM_MaxM        ,_Skor_nom( -2.00),_Skor_nom(  0.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "Темп-ИЗУ      ", &_r.Temp_ZSkBM        ,                0,_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom,               8, 0xff, "ном", _form(1,2,3,2) },
    { "N#-Рабоч.скор.", &_r.Z_SkRab           ,_Skor_nom( -2.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "N#-ТлВп       ", &_r.ZSk_TB            ,_Skor_nom( -2.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "N#-ТлНз       ", &_r.ZSk_TH            ,_Skor_nom( -2.00),_Skor_nom( +2.00 ), _Skor_Nom    ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "N#-порог      ", &_r.Z_SkMin           ,_Skor_nom( +0.00),_Skor_nom( +0.50 ), _Skor_nom( +0.01 ) ,(w*)&_ind_Nom, 8        , 0xff, "%"  , _form(1,2,2,2) }
  };*/

#ifdef _A7_Obj_Ust
_x_far const struct STB       stb_obj[ ] =
  {
      _A7_Obj_Ust
  };
#endif

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

#ifdef   _AVTONASTR
_x_far const struct STB       stb_anastr[ ] =
  {
    { "Tпп РС-беспер ", &_r.Tpp_AN_nepr       , 3               , 2000             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек",_form(1,3,0,2) },
    { "Tпп РС-пер    ", &_r.Tpp_AN_pr         , 3               , 2000             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек",_form(1,3,0,2) },
    { "Коэф.Демпф.РС ", &_r.KoefDempfirRT     , (w)(0.25*256.)  , 2 * 256          , 256          ,(w*)&_ind_Nom, 1              , 0xff, "од" , _form(0,2,3,2) },
    { "Id-гр-бесп-90g", &_r.INN_def_AN        , 0               , 1                , 1            ,(w*)&_ind_Nom, 1              , 0xff, " "  , _form(1,1,0,2) },
    { "Te            ", &_r.Te_AN             , 0               , 120 * 64         , 64           ,(w*)&_ind_Nom, 64             , 0xff, "мсек",_form(1,3,0,2) },
    { "'Ктп/Ra_беспер", &_r.KtpRa_AN_nepr     , 0               , 120 * 64         , 64           ,(w*)&_ind_Nom, 0              , 0xff, "од",  _form(1,3,2,2) },
    { "'Ктп/Ra_пер.  ", &_r.KtpRa_AN_pr       , 0               , 120 * 64         , 64           ,(w*)&_ind_Nom, 0              , 0xff, "од",  _form(1,3,2,2) }
  //{ "Tm            ", &_r.Tm_AN             , 0               , 1000             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек",_form(1,3,0,2) },
  //{ "TопрМакс-Tm   ", &_r.T_AN_ust          , _fSec( 0.0 )    , _fSec( 16.0 )    , _fSec(1)     ,(w*)&_ind_Nom, _fSec(1)       , 0xff, "сек", _form(1,2,1,2) },
  //{ "L0 (Tm АН)    ", &_r.Alfa0_forTm_AN    , _Grad(60)       , _Grad(85)        , _Grad(1)     ,(w*)&_ind_Nom, _Grad(5)       , 0xff, "грд", _form(1,2,0,2) },
  //{ "Множ-ль L#-Tm ", &_r.Kratn_5_AN        , 5               , 10               , 1            ,(w*)&_ind_Nom, 5              , 0xff, "ед" , _form(1,2,0,2) },
  };
#endif

const struct UstUzm   Ustav[] =
  {
    {"Регулюв    " ,sizeof(stb_reg   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_reg   [0] },
    {"Захисти    " ,sizeof(stb_avar  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_avar  [0] },
    {"Перевантаж." ,sizeof(peregr    )/sizeof(struct STB) ,(_x_far const struct STB*)&peregr    [0] },
    {"Масштаби   " ,sizeof(stb_masht )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_masht [0] },
#ifdef _CM3_
    {"Масшт. АЦП " ,sizeof(stb_ADC_masht)/sizeof(struct STB) ,&stb_ADC_masht[0] },
#endif
  //{"Штатн.упр. " ,sizeof(stb_shtat )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_shtat [0] },
#ifdef _A7_Obj_Ust
    {"Об'єкт.упр." ,sizeof(stb_obj   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_obj   [0] },
#endif
#ifdef _AVTONASTR
    {"Автоналашт " ,sizeof(stb_anastr)/sizeof(struct STB) ,(_x_far const struct STB*)&stb_anastr[0] },
#endif
//  {"F#->If#    " ,sizeof(stb_Ivz   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_Ivz   [0] },
    {"Службові   " ,sizeof(stb_serv  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_serv  [0] }
#ifdef  _INTERPRETER
   ,{"Об'єкт.прг " ,sizeof(Ust_Obj_Prg)/sizeof(struct Obj_STB) ,(_x_far const struct STB*)&Ust_Obj_Prg[0] }
#endif
  }; /* Количество уставок в таблице */
const word _MaxNumUstav = sizeof(Ustav)/sizeof(const struct UstUzm) ;


//------------- А6 - Таблица индикации -------------------

_x_far const struct Ind  ind_reg[] =
  {
#ifndef  _SIFU2_
         { "L    , Idсі   ", { &S.Alfa_Old     , &Id_dop_kod    },{_Grad( 1 )     ,_Id_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L    , Ud     ", { &S.Alfa_Old     , &UdSr          },{_Grad( 1 )     ,_Ud_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
       //{ "L    , Мост   ", { &S.Alfa_Old     , &S.NumMost     },{_Grad( 1 )     ,  1             },{ "гp, ", "" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,1,0,1)} },
         { "Idсі , Ud     ", { &Id_dop_kod     , &UdSr          },{_Id_Nom        ,_Ud_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "Idсі , Idрв   ", { &Id_dop_kod     , &Irot          },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "Idсі , Iстат  ", { &Id_dop_kod     , &Ist_SA        },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "Idсі , Id-ІУ  ", { &Id_dop_kod     , &Id_IU         },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
 #ifdef  Id_sr_ach
         { "|Id| , Id-ср  ", { &IDV            , &Id_sr         },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
 #endif
#else
         { "L    , Id1    ", { &S.Alfa_Old     , &Id_dop_kod    },{_Grad( 1 )     ,_Id_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L2   , Id2    ", { &S2.Alfa_Old    , &Id2_dop_kod   },{_Grad( 1 )     ,_Id_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L    , Idsum  ", { &S.Alfa_Old     , &Id_sum        },{_Grad( 1 )     ,_Id_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L2   , Idsum  ", { &S2.Alfa_Old    , &Id_sum        },{_Grad( 1 )     ,_Id_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L    , Ud     ", { &S.Alfa_Old     , &UdSr          },{_Grad( 1 )     ,_Ud_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L2   , Ud     ", { &S2.Alfa_Old    , &UdSr          },{_Grad( 1 )     ,_Ud_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "L    , Мост   ", { &S.Alfa_Old     , &S.NumMost     },{_Grad( 1 )     ,  1             },{ "гp, ", "" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,1,0,1)} },
         { "L2   , Мост   ", { &S2.Alfa_Old    , &S.NumMost     },{_Grad( 1 )     ,  1             },{ "гp, ", "" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,1,0,1)} },
         { "Idsum, Ud     ", { &Id_sum         , &UdSr          },{_Id_Nom        ,_Ud_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "Id1  , Id2    ", { &Id_dop_kod     , &Id2_dop_kod   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
       //{ "|Id1|, |Id2|  ", { &IDV            , &IDV2          },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "Id1s , Id2s   ", { &Id_sr          , &Id2_sr        },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "|Id1|, Id1s   ", { &IDV            , &Id_sr         },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "|Id2|, Id2s   ", { &IDV2           , &Id2_sr        },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
#endif
#ifdef _REG_POL
         { "S#   , S      ", { &ZUgol          , &Ugol          },{_Grad( 1 )     ,_Grad( 1 )      },{ "г, " ,"г" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "S#   , RPout  ", { &ZUgol          , &OuRP          },{_Grad( 1 )     ,_Skor_nom(1)    },{ "г, " ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
#endif
#ifdef  Nzad_4_20_ach
         { "N# (4-20),N#нп", { &Nzad_4_20      , &Nzad          },{_1mA_Nom       ,_Skor_nom(1)    }, {"мА," ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,2,1,2),_form(0,3,0,2)} },
#endif
         { "N#   , N#R    ", { &Z_Skor         , &ZISkor        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N#R  , N      ", { &ZISkor         , &Skor          },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
       //{ "N    , E      ", { &Skor           , &EDS_dop_kod   },{_Skor_nom(1)   ,_EDS_nom(1)     },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "Nw   , Nпдф   ", { &N_rot          , &SkorPDF       },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
       //{ "N    , Nx     ", { &Skor           , &Skor_r        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Nnf  , Nf     ", { &Skor_ind       , &Skor_f        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#ifdef   TGx_ach
         { "Nx1  , Nx8    ", { &TGx1           , &TGx8          },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%,"  , "%"}, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,2,2),_form(0,2,2,2)} },
#endif
         { "Sрот , N      ", { &Srot           , &Skor          },{_Ud_Nom        ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
       //{ "dN   , РСпип-p", { &Delta_Sk       , &OuIchRS_k     },{_Skor_nom(1)   ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#ifndef  _SIFU2_
         { "Id#  , Idсі   ", { &OuRegS_dop_kod , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Idсі , M      ", { &Id_dop_kod     , &Moment        },{_Id_Nom        ,_Mom_Nom        },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#else
         { "Id#  , Id1    ", { &OuRegS_dop_kod , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Id#  , Id2    ", { &OuRegS_dop_kod , &Id2_dop_kod   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Idsum, M      ", { &Id_sum         , &Moment        },{_Id_Nom        ,_Mom_Nom        },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef _RDN
         { "Id   , Id2d   ", { &Id_dop_kod     , &Id_2v        }, {_Id_Nom     , _Id_Nom      }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "dId  , RDNout ", { &dId            , &RDN_Out      }, {_Id_Nom     , _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "N#   , RDNout ", { &Z_Skor         , &RDN_Out      }, {_Skor_nom(1), _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef _BUKSOVKA
         { "N    , N2d    ", { &Skor           , &N_2v         }, {_Skor_nom(1), _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "N    , dN     ", { &Skor           , &dN           }, {_Skor_nom(1), _Skor_nom(1) }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef _RRS
         { "Id   , IdSt   ", { &Id_dop_kod     , &Id_Stat_flt.out},{_Id_Nom    , _Id_Nom      }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
         { "IdSt , IdSt2d ", { &Id_Stat_flt.out, &Id_stat_2v     },{_Id_Nom    , _Id_Nom      }, {"%, " , "%"  }, {(w*)&_ind_100,(w*)&_ind_100}, {_form(0,3,0,2),_form(0,3,0,2)} },
#endif
#ifdef  _RVId
         { "Id1  , Id2    ", { &Id1            , &Id2           },{_Id_Nom        ,_Id_Nom         },{ "%,  ","%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If   , If2    ", { &V.Iv           , &V2.Iv         },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "If#  , If#2   ", { &V.Iv_zad       , &V2.Iv_zad     },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "dId  , dIf    ", { &dRVId          , &dIv           },{_Id_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
       //{ "E#   , E      ", { &Zad_EDS        , &EDS_dop_kod   },{_EDS_nom(1)    ,_EDS_nom(1)     },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(0,3,1,2)} },
#ifdef   EDS_ach
         { "Eапар, Eпрогp ", { &iEDS           , &prEDS         },{_EDS_nom(1)>>_Skor_Shift ,_EDS_nom(1)>>_Skor_Shift },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
       //{ "F#   , If#    ", { &V.Fv_zad       , &V.Iv_zad      },{_Fv_nom(1)     ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
       //{ "If#  , If     ", { &V.Iv_zad       , &V.Iv          },{_Iv_Nom        ,_Iv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
       //{ "If   , F      ", { &V.Iv           , &V.Fv          },{_Iv_Nom        ,_Fv_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#ifdef  _Vozb_KTE
         { "Lf   , If     ", { &V.Alfa_Old     , &V.Iv          },{_Grad( 1 )     ,_Iv_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
         { "РСВі-р,If     ", { &V.Integr_rt    , &V.Iv          },{_Grad( 1 )     ,_Iv_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
#endif
       //{ "Id  ,Id-перегp", { &Id_dop_kod     , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(1,3,0,2)} },
         { "Idрв,Id-перев ", { &Irot           , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(1,3,0,2)} },
         { "Id-інт,Id-пер.", { &Id_TeploIntegr , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,2,2),_form(1,3,0,2)} },
       //{ "KompUd,Ud-komp", { &Kompen_Ud      , &UdSr_Komp     },{ 1             ,_Ud_Nom         },{ "d,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
#ifndef _SIFU2_
         { "|Id#R|, |Id|  ", { &ZIDN           , &IDV           },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(1,3,0,2)} },
         { "РСі-p, Id-p   ", { &OIRT           , &IDN           },{_Grad( 1 )     ,_Id_Nom         },{ "г,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
#else
         { "INN  , INN-дв ", { &INN            , &INN_dvig      },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
         { "RVTout, dL2   ", { &S2.Out_rvt     , &S2.Alfa_RVT   },{_Grad(1)       ,_Grad(1)        },{ "г,"  ,"г" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,2,1,2),_form(0,2,1,2)} },
         { "|Id1#R|,|Id1| ", { &ZIDN           , &IDV           },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(1,3,0,2)} },
         { "|Id2#R|,|Id2| ", { &ZIDN_2_        , &IDV2          },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,4,0,2),_form(1,3,0,2)} },
         { "РС1і-p,Id1-p  ", { &OIRT           , &IDN           },{_Grad( 1 )     ,_Id_Nom         },{ "г,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
         { "РС2і-p,Id2-p  ", { &OIRT_2_        , &IDN_2_        },{_Grad( 1 )     ,_Id_Nom         },{ "г,"  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,1,2),_form(1,3,1,2)} },
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
       //{ "Ud-oe         ", { &UdSr                            },{ 1                                     },{ "ед"       }, {(w*)&_ind_Nom              },{_form(0,4,0,2)               } },
         { "Ud   , Uізол  ", { &UdSr           , &Uinsul        },{_Ud_Nom        , (w)(1.0*(_AD_MAX/5.0))},{ "%,"  ,"B" }, {(w*)&_ind_100,(w*)&_ind_Nom},{_form(0,3,1,2),_form(0,1,2,2)} },
         { "Uізол,Uіз.макc", { &Uinsul         , &Uinsul_max    },{(w)(1.0*(_AD_MAX/5.0)), (w)(1.0*(_AD_MAX/5.0))},{ "В,"  ,"B" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,1,2,2),_form(0,1,2,2)} },
#ifdef Insul_D_ach
         { "Uf   ,  Uізвд ", { &Uf             , &UinsulD      }, {_Ud_Nom     ,(w)(1.0*(_AD_MAX/5.0))    }, {"%,","B"}, {(w*)&_ind_100,(w*)&_ind_Nom}, {_form(0,3,1,2),_form(0,1,2,2)} },
         { "Uізвд,Uіз.макc", { &UinsulD        , &UinsulD_max  }, {(w)(1.0*(_AD_MAX/5.0)), (w)(1.0*(_AD_MAX/5.0))},{"В, ","B"}, {(w*)&_ind_Nom,(w*)&_ind_Nom}, {_form(0,1,2,2),_form(0,1,2,2)} },
#endif
#ifdef  _T_PDF
         { "ПДФ0_T, ПДФ0_F", { &PDF[0].N_Tpdf  , &PDF[0].N_Fpdf},{ _Skor_Nom     ,_Skor_Nom       },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
#endif
/*#ifdef _CM3_
         { "ПДФ0:об/мин, %", { &PDF[0].out_ob  , &PDF[0].out_m  },{ 10            ,_Skor_Nom       },{ ", "  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,4,1,2),_form(0,3,0,2)} },
#else
         { "ПДФ0:об/мин, %", { &PDF[0].out_ob  , &PDF[0].out_m  },{ 1             ,_Skor_Nom       },{ ", "  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,4,1,2),_form(0,3,0,2)} },
#endif
*/
#ifdef TG_ach
         { "ТГ   , E      ", { &TG             , &EDS_dop_kod   },{_Skor_nom(1)   ,_EDS_nom(1)     },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
#endif
       //{ "Сельс0:град, %", { &Sels[0].out_g  , &Sels[0].out_m}, {_Grad( 1 )  ,_Skor_Nom     }, {", " , ""    }, {(w*)&_ind_Nom,(w*)&_ind_100}, {_form(0,3,1,2),_form(0,3,1,2)} },
       //{ "Сельс1:град, %", { &Sels[1].out_g  , &Sels[1].out_m}, {_Grad( 1 )  ,_Skor_Nom     }, {", " , ""    }, {(w*)&_ind_Nom,(w*)&_ind_100}, {_form(0,3,1,2),_form(0,3,1,2)} },
#ifdef  Ttrans_ach
         { "Ttr(4-20),Ttr ", { &Ttrans_4_20    , &Ttrans        },{_1mA_Nom    , 10           }, {"мА,","гp"   }, {(w*)&_ind_Nom,(w*)&_ind_Nom}, {_form(0,2,1,2),_form(0,3,0,2)} },
#endif
#ifndef  _SIFU2_
         { "  Idсі (%, А) ", { &Id_dop_kod     , &Id_dop_kod   }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Id.fe},{_form(0,3,1,2),_form(0,5,0,2)} },
#else
         { "  Id1 (%, А)  ", { &Id_dop_kod     , &Id_dop_kod   }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&Id_divBy2_abs},{_form(0,3,1,2),_form(0,5,0,2)} },
         { "  Id2 (%, А)  ", { &Id2_dop_kod    , &Id2_dop_kod  }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&Id_divBy2_abs},{_form(0,3,1,2),_form(0,5,0,2)} },
         { "  Idsum (%, А)", { &Id_sum         , &Id_sum       }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Id.fe},{_form(0,3,1,2),_form(0,5,0,2)} },
#endif
         { "  Ud (%, В)   ", { &UdSr           , &UdSr         }, { _Ud_Nom , _Ud_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Ud.fe},{_form(0,3,1,2),_form(0,5,0,2)} }
#ifdef  _RVId
         { "  If2(%, А)   ", { &V2.Iv          , &V2.Iv        }, { _Iv_Nom , _Iv_Nom*10 },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Iv.fe},{_form(0,3,0,2),_form(0,2,1,2)} },
#endif
 ,
         { "1T1   ,  1T2  ", { &Temper[0], &Temper[1] },{10, 10           },{ "Гp,","Гр"},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "1T3   ,  1T4  ", { &Temper[2], &Temper[3] },{10, 10           },{ "Гр,","Гр"},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "1T5   ,  1T6  ", { &Temper[4], &Temper[5] },{10, 10           },{ "Гp,","Гр"},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "2T1   ,  2T2  ", { &Temper[6], &Temper[7] },{10, 10           },{ "Гр,","Гр"},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "2T3   ,  2T4  ", { &Temper[8], &Temper[9] },{10, 10           },{ "Гр,","Гр"},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "2T5   ,  2T6  ", { &Temper[10],&Temper[11]},{10, 10           },{ "Гр,","Гр"},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Vout1,Vout2   ", { &Volt[0]  , &Volt[1]   },{1000  , 1000     },{ "В,","В"   }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,1,2,3),_form(1,1,2,3)} },
         { "1KP1          ", { &Amper[0]              },{1                },{ " B"       }, {(w*)&_ind_Nom              },{_form(1,3,2,3)               } },
         { "2KP1          ", { &Amper[1]              },{1                },{ " B"       }, {(w*)&_ind_Nom              },{_form(1,3,2,3)               } }
         //{ "  If (%, А)   ", { &V.Iv           , &V.Iv         }, { _Iv_Nom , _Iv_Nom*10 },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Iv.fe},{_form(0,3,0,2),_form(0,2,1,2)} }
  };

_x_far const struct Ind  ind_serv[] =
  {
    // 12-ти пульсная схема , по два ШС в каждом мосту - индикация первой секции :
#if   defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
         { "IA1   , IB1   ", { &IA1            , &IB1             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC1   , IA2   ", { &IC1            , &IA2             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IB2   , IC2   ", { &IB2            , &IC2             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
    // 12-ти пульсная схема , по одному ШС в каждом мосту :
#elif defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && !defined( IA2_ach ) && !defined( IB2_ach ) && !defined( IC2_ach ) && \
      defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach )
         { "IA1   , IB1   ", { &IA1            , &IB1             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC1   , IA2   ", { &IC1            , &IA3             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IB2   , IC2   ", { &IB3            , &IC3             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
    // 6-ти пульсная схема :
#elif defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
         { "IA1   , IB1   ", { &IA1            , &IB1             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC1           ", { &IC1                               },{_Id_Nom                         },{ "%  "      }, {(w*)&_ind_100              },{_form(1,3,0,2)               } },
#endif
    // 12-ти пульсная схема , по два ШС в каждом мосту - индикация второй секции :
#if   defined( IA3_ach ) && defined( IB3_ach ) && defined( IC3_ach ) && defined( IA4_ach ) && defined( IB4_ach ) && defined( IC4_ach )
         { "IA3   , IB3   ", { &IA3            , &IB3             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IC3   , IA4   ", { &IC3            , &IA4             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IB4   , IC4   ", { &IB4            , &IC4             },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
#endif
#ifdef _Dat_Temp_Max
       _A6_ADC_multiplex_temp,
#endif
         { "ATKflg, flgO  ", { &ATK_flg.all    , &flgO.all        },{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },
         { "cCfgR,  cStsR ", { &canr.CfgReg.all, &canr.StatReg.all},{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },
         { "cN#           ", {                   &canr.N_zad      },{                _Skor_Nom       },{        "%" }, {              (w*)&_ind_100},{               _form(0,3,0,2)} },
       /*  { "cId# ,  cdId# ", { &canr.Id_zad    , &canr.dId_zad    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cId#P,  cId#M ", { &canr.Idz_MaxP  , &canr.Idz_MaxM   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cL#  ,  cF#   ", { &canr.L_zad     , &canr.F_zad      },{_Grad( 1 )     ,_Fv_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
         { "cAo0 ,  cAo1  ", { &canr.Ao[0]     , &canr.Ao[1]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi0 ,  cAi1  ", { &canr.Ai[0]     , &canr.Ai[1]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi2 ,  cAi3  ", { &canr.Ai[2]     , &canr.Ai[3]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi4          ", { &canr.Ai[4]                        },{ 1                              },{ " "        }, {(w*)&_ind_Nom              },{_form(0,5,0,2)               } },*/
         { "CAN0Err:Bus   ", { &can_dd[_CAN0_Port].Avar           },{ 1                                },{"од "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN0Err:Rec,Tx", { &can_dd[_CAN0_Port].Error_receive,&can_dd[_CAN0_Port].Error_send},{1,1},{"од, ","од "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CAN1Err:Bus   ", { &can_dd[_CAN1_Port].Avar                                        },{1  },{"од "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN1Err:Rec,Tx", { &can_dd[_CAN1_Port].Error_receive,&can_dd[_CAN1_Port].Error_send},{1,1},{"од, ","од "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
#ifdef _CAN2_Port
         { "CAN2Err:Bus   ", { &can_dd[_CAN2_Port].Avar                                        },{1  },{"од "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN2Err:Rec,Tx", { &can_dd[_CAN2_Port].Error_receive,&can_dd[_CAN2_Port].Error_send},{1,1},{"од, ","од "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
#endif
#ifdef _CAN_MASTER
    #ifdef _A6_CAN_MASTER_Ind
           _A6_CAN_MASTER_Ind,
    #endif
#endif
#ifdef _NARABOTKA
         { "Напрацюв-г,х  ", { &NARAB.hou     , &NARAB.min  },{ 1             , 1              },{ "г, " ,"m"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,2,0,1)} },
         { "Напрацюв-х,c  ", { &NARAB.min     , &NARAB.sec  },{ 1             , 1              },{ "m, " ,"c"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)} },
         { "Напрацюв-г,п  ", { &NARAB.hou     , &NARAB.ovr  },{ 1             , 1              },{ "г, " ,"од" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,3,0,1)} },
#endif
         { "T1   ,  V1    ", { &TIzm[0].Out,       &TIzm[0].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T2   ,  V2    ", { &TIzm[1].Out,       &TIzm[1].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T3   ,  V3    ", { &TIzm[2].Out,       &TIzm[2].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T4   ,  V4    ", { &TIzm[3].Out,       &TIzm[3].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T5   ,  V5    ", { &TIzm[4].Out,       &TIzm[4].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T6   ,  V6    ", { &TIzm[5].Out,       &TIzm[5].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T7   ,  V7    ", { &TIzm[0].Out,       &TIzm[0].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T8   ,  V8    ", { &TIzm[1].Out,       &TIzm[1].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T9   ,  V9    ", { &TIzm[2].Out,       &TIzm[2].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T10  ,  V10   ", { &TIzm[3].Out,       &TIzm[3].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T11  ,  V11   ", { &TIzm[4].Out,       &TIzm[4].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T12  ,  V12   ", { &TIzm[5].Out,       &TIzm[5].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T13  ,  V13   ", { &TIzm[4].Out,       &TIzm[4].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "T14  ,  V14   ", { &TIzm[5].Out,       &TIzm[5].V_Out },{1,1000                      },{ "Гp,","B"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,1,3,3)} },
         { "Tckl  , StopP ", { &Tckl, &stop_point       }, { _MkSec(1000), 1          },{ "ms, ",""  }, {(w*)&_ind_Nom, (w*)&_ind_Nom } ,{_form(1,2,1,2),_form(1,3,0,1)} }
       //{ "StpS  , StpS2 ", { &stop_pointS, &stop_pointV }, { 1         , 1          },{ ", "  ,""  }, {(w*)&_ind_Nom, (w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} },
       //{ "StpPDF, StpDP ", { &stop_pointP, &stop_pointD }, { 1         , 1          },{ ", "  ,""  }, {(w*)&_ind_Nom, (w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} }
  };

#ifdef _A6_Obj_Ind
_x_far const struct Ind  ind_obj[] =
  {
        _A6_Obj_Ind
  };
#endif

//--------------------------------------------------------

const struct IndUzm Indicat[]=
{
    { "Регулювання   " ,sizeof(ind_reg )/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_reg [0] },
#ifdef _A6_Obj_Ind
    { "Об'ект. управ." ,sizeof(ind_obj )/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_obj [0] },
#endif
#if defined( _RDN ) || defined( _RRS ) || defined( _BUKSOVKA )
    { "Прокат        " ,sizeof(ind_Procat)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_Procat[0] },
#endif
#ifdef _RVId
    { "PB-Id         " ,sizeof(ind_RVId)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_RVId[0] },
#endif
    { "Службові      " ,sizeof(ind_serv)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_serv[0] }
#ifdef  _INTERPRETER
   ,{ "Об'ект. прогр." ,sizeof(Ind_Obj_Prg)/sizeof(struct Ind_obj ) ,(_x_far const struct Ind*)(&Ind_Obj_Prg[0]) }
#endif
};

const word _NumInd = sizeof( Indicat )/sizeof(struct IndUzm) ;

//--------------------------------------------------------

#ifdef _CombRedact
/*
Что бы добавить новую строчку в таблицу: Копируем строку из таблицы уставок и выкидуем из неё маску (0xff обычно), которая отвечает за видимость.
Копируем строку с индикацией и оставляем в ней только те данные что касаются нужной индикации.
*/
_x_far const struct COMB_MENU comb_menu[] =
{
#ifdef _OBJ_COMB_REDACT
     _OBJ_COMB_REDACT,
#endif
    { "N#-масштаб - N#a", &_r.Mashtab_ZSkA,  0, 0x1400, 0x0100, (w*)&_ind_Nom, 1, "од", _form(1,3,3,2),
                  /*ind*/ &ZSkA, _Skor_Nom , "%",               (w*)&_ind_100,          _form(0,3,0,2)},
    { "ТГ-масштаб - ТГ ", &_r.Mashtab_OS_TG, 0, 0x1400, 0x0100, (w*)&_ind_Nom, 1, "од", _form(1,3,3,2),
                  /*ind*/ &TG,   _Skor_Nom , "%",               (w*)&_ind_100,          _form(0,3,0,2)},
    { "Сельс0: масш.-% ", &_r.Selsin[0].masht, (sw)0xF000, 0x0F00, 0x0100, (w*)&_ind_Nom, 1, "од", _form(0,1,3,2),
                  /*ind*/ &Sels[0].out_m, _Skor_Nom,  "%",      (w*)&_ind_100,          _form(0,3,0,2)},
    { "If#-1-зонных - N", &_r.Iv_zad, _Iv_nom(0.0), _Iv_nom(1.3), _Iv_Nom, (w*)&_ind_Nom, _Iv_nom(0.01), "ном ", _form(1,1,2,2),
                  /*ind*/ &Skor, _Skor_nom(1), "%",             (w*)&_ind_100,          _form(0,3,1,2)}
};

_x_far const word len_comb_menu = sizeof(comb_menu) / sizeof(const struct COMB_MENU); //определение глубины структуры комбинированого меню
#endif

//--------------------------------------------------------

//-------- Таблица параметров для вывода на ЦАПы ---------
//---- в СМ3 ЦАП 10-разрядный , а АЦП - 12-разрядный -----

_x_far const struct DAC_output_tab2 DAC_tab2  [ ] =
  {
    { "N         ",  &Skor         , (w)(0.12 * 256.)          },
    { "N#        ",  &Z_Skor       , (w)(0.12 * 256.)          },
    { "N#R       ",  &ZISkor       , (w)(0.12 * 256.)          },
    { "Id#       ",  &OuRegS_dop_kod,(w)(  1.00 * 256./_K_diskr ) },
    { "|Id#R|    ",  &ZIDN         , (w)(  1.00 * 256./_K_diskr ) },
    { "Idсі      ",  &Id_dop_kod   , (w)(  1.00 * 256./_K_diskr ) },
    { "Idрв      ",  &Irot         , (w)(  1.00 * 256./_K_diskr ) },
    { "M         ",  &Moment       , (w)(  1.00 * 256./_K_diskr ) },
    { "Ud        ",  &UdSr         , (w)(  1.00 * 256./_K_diskr ) },
    { "L         ",  &S.Alfa_Old   , (w)(0.12 * 256.)          },
//    { "PDF0m     ",  &PDF[0].out_m , (w)(0.12 * 256.)          },
//    { "PDF0g     ",  &PDF[0].out_g , (w)(0.12 * 256.)          },
    { "Sels0g    ",  &Sels[0].out_g, (w)(0.12 * 256.)          },
    { "Sels1g    ",  &Sels[1].out_g, (w)(0.12 * 256.)          },
    { "Sels0m    ",  &Sels[0].out_m, (w)(0.12 * 256.)          },
    { "Sels1m    ",  &Sels[1].out_m, (w)(0.12 * 256.)          },
    { "cAo0      ",  &canr.Ao[0]   , (w)(  1.00 * 256./_K_diskr ) },
    { "cAo1      ",  &canr.Ao[1]   , (w)(  1.00 * 256./_K_diskr ) },
    { "cAi0      ",  &canr.Ai[0]   , (w)(  1.00 * 256./_K_diskr ) },
    { "cAi1      ",  &canr.Ai[1]   , (w)(  1.00 * 256./_K_diskr ) },
    { "cAi2      ",  &canr.Ai[2]   , (w)(  1.00 * 256./_K_diskr ) },
    { "cAi3      ",  &canr.Ai[3]   , (w)(  1.00 * 256./_K_diskr ) },
    { "cAi4      ",  &canr.Ai[4]   , (w)(  1.00 * 256./_K_diskr ) },
    { "I#Fan     ",  &Id_fan       , (w)(  1.00 * 512 /_K_diskr ) },
    { "Istator   ",  &Ist_SA       , (w)(  1.00 * 256./_K_diskr ) },
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
       //  переменную "Тест" следует держать всегда в конце списка,
       // т.к. она используется для теста ЦАПов и не должна выводиться.
    { "Test      ",  &T_DAC       , (w)(  1.0*256     ) }
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
#ifdef _ATK_SET
   { "РШ         \r", _Skor_nom(0.0) , _Skor_nom(+1.1), _Skor_Nom  , _Skor_nom(0.01) },
#else
   { "РШ         \r", _Skor_nom(-1.1), _Skor_nom(+1.1), _Skor_Nom  , _Skor_nom(0.01) },
#endif
   { "РС         \r", _Id_nom( -2.0) , _Id_nom(+2.0)  , _Id_Nom    , _Id_nom(0.01)   },
#ifdef _Rev_Pola
   { "РСВ-двиг.  \r", _Iv_nom(-2.0)  , _Iv_nom(2.0)   , _Iv_Nom    , _Iv_nom(0.01)   },
#else
 //{ "РТВ-двиг.  \r", _Iv_nom(0.0)   , _Iv_nom(2.0)   , _Iv_Nom    , _Iv_nom(0.01)   },
#endif
 //{ "СИФУВ      \r", _Grad(0.0)     , _Grad(179.0)   , _Grad(1.0) , _Grad(0.05)     },
// 09.06.2020 15:35 см.изм. в "F2_drv.c", "Upravl.c", "Reg_eds.c", "Cikl.h".
// { "РЭДС       \r", _EDS_nom(0.0)  , _EDS_nom(+1.0) , _EDS_Nom   , _EDS_nom(0.01)  },
   { "СІФУ       \r", _Grad(0.0)     , _Grad(179.0)   , _Grad(1.0) , _Grad(0.05)     }
 //{ "РП         \r", _Grad(-179.0)  , _Grad(179.0)   , _Grad(1.0) , _Grad(0.05)     }
#ifdef _SIFU2_
  ,{ "РС1        \r", _Id_nom( -2.0) , _Id_nom(+2.0)  , _Id_Nom    , _Id_nom(0.01)   },
   { "РС2        \r", _Id_nom( -2.0) , _Id_nom(+2.0)  , _Id_Nom    , _Id_nom(0.01)   }
#endif
  } ;
const word _Nck  = sizeof(Nckl)/sizeof(const struct Ck) ;

//-------------------------------------------------

#ifdef _AVTONASTR
// Для Автонастройки РТ
_x_far const struct Vybor AN_RT [] =
  {
   { "\rВизнач. коеф.РT", 0 }
 //{ "\rОпред-е Тм     ", 1 }
  } ;
const word _Nanastr  = sizeof(AN_RT)/sizeof(const struct Vybor) ;
#endif

//-------------------------------------------------

_x_far const struct Vybor Vyb [] = { // Порядок и кол-во меток в F2_DRV.C :
                                 { "\rСІФУ-Рез-М1    ",  3 },//k10 },
                               //{ "\rСИФУ-Рез-М2    ",  4 },//k11 },

                                 { "\rРС-Рез-М1      ",  5 },//k12 },
                               //{ "\rРТ-Рез-М2      ",  6 },//k13 },
#ifdef _SIFU2_
                                 { "\rРС1-Рез-М1     ", 44 },//k80 },
                                 { "\rРС1-Рез-М2     ", 45 },//k85 },
                                 { "\rРС2-Рез-М1     ", 46 },//k90 },
                                 { "\rРС2-Рез-М2     ", 47 },//k95 },
#endif

                              // { "\rРНг-Рез        ",  8 },//k15 },
#ifdef _Vozb_KTE
                                 { "\rСІФУЗ-Рез      ",  9 },//k16 },
#endif
#ifdef   _AVTONASTR
                                 { "\rАвтоналаштуван ",  25},//k60a},
#endif
#ifdef   _NARABOTKA
                                 { "\rОбнул.напрацюв ",  33},//k67 },
#endif
#ifdef _SELS_NULL
                                 { "\rВст.нуля сельс.", 37 },//k71 },
#endif
                               //{ "\rФункц.'F#->If#'",  7 },//k14 },
                                 { "\rЦикли Завдання ", 11 },//k30 },

                                 { "\rШтатний режим  ", 10 },//k17 }
                                 { "\rФазіровка Моста", 48 } //k96 для фазировки моста в "Наладке" 18.05.2020
                               } ;
const word _Nvyb =  sizeof(Vyb)/sizeof(const struct Vybor) ;
//----------------------------------------

_x_far const struct NCx NC [] = {
                                   { "A1-Повідомлен ", _Case ( 'A' , '1' ) },
                                   { "A7-Ред.Устав. ", _Case ( 'A' , '7' ) },
                                   { "A8-Ред.БітУст.", _Case ( 'A' , '8' ) },
                                   { "AE-Збер.Устав.", _Case ( 'A' , 'E' ) },
                                   { "A6-Індикація. ", _Case ( 'A' , '6' ) },
#ifdef _CombRedact
                                   { "F1-Комб.Редак.", _Case ( 'F' , '1' ) },
#endif
                                   { "F2-Налагоджен ", _Case ( 'F' , '2' ) },
                                 //{ "A5-Фазир.Мостa", _Case ( 'A' , '5' ) }, // 18.05.2020
                                   { "FA-Останов.   ", _Case ( 'F' , 'A' ) },
                                   { "A4-Тест АЦП.  ", _Case ( 'A' , '4' ) },
                                   { "A9-Тест ЦАП.  ", _Case ( 'A' , '9' ) },
                                   { "AA-Тест Двх.  ", _Case ( 'A' , 'A' ) },
                                   { "AB-Тест Двих. ", _Case ( 'A' , 'B' ) },
                                   { "F-Монітор.    ", _Case ( 'F' ,  0  ), 9 },
                                   { "F0-НалагРеєстр", _Case ( 'F' , '0' ) },
#ifdef _Sld_cond
                                   { "FC-Умов.Реєстр", _Case ( 'F' , 'C')  },
#endif
                                 //{ "F1-След.      ", _Case ( 'F' , '1' ) },
#ifdef _JOURNAL
                                   { "AC-Налаг.Журн.", _Case ( 'A' , 'C' ) },
                                   { "FB-Журнал.    ", _Case ( 'F' , 'B' ) },
#endif
#ifdef  _TEST_RAM_INCLUDE
                                   { "F3-Тест ОЗП.  ", _Case ( 'F' , '3' ) },
#endif
                                   { "F4-Тест ЭОЗП. ", _Case ( 'F' , '4' ), 9 },// для невидимости.
                                   { "F5-Віднов.Авар", _Case ( 'F' , '5' ) },
                                   { "F6-Годинник   ", _Case ( 'F' , '6')  },
                                   { "F7-Налаг.Годин", _Case ( 'F' , '7')  },
                                   { "AD-Вывед ЦАП. ", _Case ( 'A' , 'D' ) },
                                   { "F8-Про систему", _Case ( 'F' , '8' ) },
                                   { "F9-Відн.Устав ", _Case ( 'F' , '9' ) },
                                   { "Link          ", _Case ( 'I' ,  0  ), 9 },// для невидимости.
#ifndef _CM3_
                                   { "J-RW_I2C      ", _Case ( 'J' ,  0  ), 9 },// для невидимости.
#endif
                                   { "AF-Пароль     ", _Case ( 'A' , 'F' ) },
#ifdef _NET_IRQ
//09.06.2020 13:17                 { "FD-Тест DP.   ", _Case ( 'F' , 'D' ) },
                                   { "B6-Мер:Індик. ", _Case ( 'B' , '6' ) },
                                   { "B7-Мер:Устав. ", _Case ( 'B' , '7' ) },
                                   { "B8-Мер:БітУс. ", _Case ( 'B' , '8' ) },
#endif
                                   { "FE-Швид.пульту", _Case ( 'F' , 'E' ) }
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
