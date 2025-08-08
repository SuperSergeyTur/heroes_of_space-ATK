
// ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ РАЗЛИЧНЫЕ ТАБЛИЦЫ .
//------------------------------------------------------------------------------

#ifndef msg_tabl_h
#define msg_tabl_h

// В MSG.H _Device_Name_ можно переименовать :
#define _Device_Name_ "    -УПТФ5-     "

//----------- А8 - Таблицы битовых уставок ---------------

#define _KTE_A8_Cfg1 \
    { "Kонфиг.1    " , (w*)&_r.Cfg.all, 4 ,                                    \
                               { "Штатное упр.",                               \
                                 "Объектн.упр.",                               \
                                 "АСУТП-упр.  ",                               \
                                 "Частотн.ИУ  " },                             \
      { _cfg_Shtat_reg  , _cfg_Obj_prg , _cfg_CAN_reg  ,  _cfg_Fzapoln },      \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Prg \
    { "Структура   " , (w*)&Prg.all,  5 ,                                      \
                               { "Сборка гот. ",                               \
                                 "РС          ",                               \
                                 "Циклы Задан.",                               \
                                 "Блок Управл.",                               \
                                 "След        " },                             \
      { _Gotovn, _RegSk, _Cikl, _Blok_upr, _Sled },                            \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Sk \
    { "Датчик скор." , (w*)&_r.Sk_str.all,  1 ,                                \
                               { "N:фильтр    "},                              \
      { _sk_filtr },                                                           \
       (w*)&_Msk ,2                                                            \
    }

//-----
#define _KTE_A8_Pi1 \
      { "Pi1-инверт  " , &_r.Pi1_Normal,  8 ,     /* CM3 */                    \
                               {                                               \
                                 "резерв0/INT7",                               \
                                 "net    /INT2",                               \
                                 "резерв2/INT5",                               \
                                 "резерв3/INT6",                               \
                                 "резерв4/INT4",                               \
                                 "резерв5/INT3",                               \
                                 "резерв6/INT0",                               \
                                 "1В/Ittm/INT1"                                \
                               },                                              \
        { 0x01, 0x02, 0x04, 0x08, 0x10 , 0x20 , 0x40 , 0x80 },                 \
         (w*)&_Msk ,1                                                          \
      }

//-----
#define _KTE_A8_cCfgR \
    { "АСУТП:cCfgR " , &canr.CfgReg.all  , 16 ,                                \
                               { "rezerved0   ",                               \
                                 "Predupr     ",                               \
                                 "Avar        ",                               \
                                 "rezerved3   ",                               \
                                 "rezerved4   ",                               \
                                 "rezerved5   ",                               \
                                 "rezerved6   ",                               \
                                 "Connect     ",                                \
                                                                               \
                                 "Start       ",                               \
                                 "reserved9   ",                               \
                                 "reserved10  ",                               \
                                 "reserved11  ",                               \
                                 "Пуск 0, 1   ",                               \
                                 "Пуск 1, 0   ",                               \
                                 "reserved14  ",                               \
                                 "reserved15  "                                \
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
                                 "rezerv6     ",                               \
                                 "Connect     ",                               \
                                                                               \
                                 "реж. Работа ",                               \
                                 "rezerv9     ",                               \
                                 "rezerv10    ",                               \
                                 "rezerv11    ",                               \
                                 "Пуск 0, 1   ",                               \
                                 "Пуск 1, 0   ",                               \
                                 "rezerv14    ",                               \
                                 "rezerv15    "                                \
                                 },                                            \
      { _A8_sreg_mask },                                                       \
       (w*)&_Msk ,2                                                            \
    }

//---------------------------------------- Порт CAN 0 ----------------------------------------
// При отсутствии выбора скорости CAN (все скорости == 0) скорость принимается равной 100 кГц .
#ifdef _CANOPEN                            // CAN0-open :
#define _KTE_A8_CAN0cfg \
    { "CAN0-config   " , &can_setting( _CAN0_Port ).config.all, 5 ,                          \
                               {                                                             \
                                 "Вкл.CAN     " ,                                            \
                                 "Вкл.CANopen " ,                                            \
                                 "125кГц-500м " ,                                            \
                                 "250кГц-250м " ,                                            \
                                 "1МГц  - 25м " },                                           \
      { _can_cfg_vkl,_can_cfg_mcovkl, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M },  \
       (w*)&_Msk ,1                                                                          \
    }
#else
#define _KTE_A8_CAN0cfg \
    { "CAN0-config   " , &can_setting( _CAN0_Port ).config.all, 5 ,                          \
                               { "Вкл.CAN     " ,                                            \
                                 "CAN-мастер  " ,                                            \
                                 "125кГц-500м " ,                                            \
                                 "250кГц-250м " ,                                            \
                                 "1МГц  - 25м " },                                           \
      { _can_cfg_vkl, _can_cfg_master, _can_cfg_bt_125k, _can_cfg_bt_250k, _can_cfg_bt_1M }, \
       (w*)&_Msk ,1                                                                          \
    }
#endif

//---------------------------------------- Порт CAN 1 ----------------------------------------
// При отсутствии выбора скорости CAN (все скорости == 0) скорость принимается равной 100 кГц .
#define _KTE_A8_CAN1cfg \
    { "CAN1-config   " , &can_setting( _CAN1_Port ).config.all, 5 ,                          \
                               { "Вкл.CAN     " ,                                            \
                                 "CAN-мастер  " ,                                            \
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
                               { "Вкл.CAN     " ,                                            \
                                 "CAN-мастер  " ,                                            \
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
                               { "Вкл.Modbus  " ,                                            \
                                 "19200 Бит/с " ,                                            \
                                 "38400 Бит/с " ,                                            \
                                 "57600 Бит/с " ,                                            \
                                 "Вкл.четн.   " ,                                            \
                                 "Четность    " ,                                            \
                                 "1 стоп-бит  " },                                           \
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
  //{ "dN-дат.скор.  ", &_r.dN_Max            ,_Skor_nom( +0.0 ),_Skor_nom( +2.5 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
  //{ "E-макс        ", &_r.E_Max             ,_EDS_nom( +0.0 ) ,_EDS_nom( +2.5 )  ,_EDS_Nom      ,(w*)&_ind_Nom, _EDS_nom(0.01) , 0xff, "ном", _form(1,2,2,2) },
  //{ "T-обр.сил.цепи", &_r.T_Circuit         ,_fSec( 0.0 )     ,_fSec( 12.0 )     ,_fSec(1.0)    ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек", _form(1,3,2,2) },
  //{ "Id-мин        ", &_r.Id_Min            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "Id-макс       ", &_r.Id_Max            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#ifdef   Id_sum_ach
    { "Id-сум-макс   ", &_or.Id_sum_max       ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#endif
    { "dt-Id-макс    ", &_r.time_Id_max       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "мceк",_form(1,3,1,1) }, // !!! Это не "word" , а "byte" , до 255 пульсов .
  //{ "Id-тст-пробой ", &_r.Id_tst_proboy     ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
#ifdef _Vozb_KTE
    { "If-макс       ", &_r.Iv_avar_Max       ,_Iv_nom( 0.0 )   ,_Iv_nom( 3.0 )    ,_Iv_Nom       ,(w*)&_ind_Nom, _Iv_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "dt-If-макс    ", &_r.time_Iv_max       , 0               ,_pSec( 0.8 )      ,_pSec(1.0)    ,(w*)&_ind_1000, 1             , 0xff, "мceк",_form(1,3,1,1) },
#endif
#ifdef bi_BV1
  #ifndef  _STOLB_1TIR
   #ifdef bi_PT
    { "T-откл.вент.  ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(3000.0 )     ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "мин", _form(1,2,2,2) },
   #else
    { "T-охлажд      ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(600.0 )      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "мин", _form(1,2,2,2) },
   #endif
  #else
    { "T-охлажд      ", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(3.0 )        ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },
  #endif
#endif
#ifdef Vent_Vkl_Id // для алгоритма включения вентиляторов по току якоря :
    { "T-охлажд-авар.", &_r.Time_otkl_BV1     ,_Sec( 0.0 )      ,_Sec(600.0 )      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "мин", _form(1,2,2,2) },
    { "Id-вкл-вент.  ", &_or.Id_Vkl_Vent      ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,2,2,2) },
    { "T-откл-вент.  ", &_or.T_Otkl_Vent      ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "мин", _form(1,3,1,2) },
#endif
    { "t-перегрев-тиp", &_or.T_Pr             , 0.*10           , 300*10           , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,1,2) },
  //{ "T-перегрев-ав.", &_or.T_Av             , 0.*10           , 300*10           , 10           ,(w*)&_ind_Nom, 10             , 0xff, "грд", _form(0,3,1,2) },
    { "T-откл-вент.  ", &_or.T_Otkl_Vent      ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "мин", _form(1,3,1,2) },
    { "T-откл.имп.   ", &_r.Time_do_OtklImp   ,_Sec( 0.0 )      ,_Sec( 9.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.1)      , 0xff, "сек", _form(1,2,2,2) },
#ifdef bi_Vent_Dvig
    { "T-вент.двиг.  ", &_r.Time_otkl_VentDvig,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "мин", _form(1,3,1,2) },
#endif
#ifdef bi_MasloSmazka
    { "T-смаз.двиг.  ", &_r.Time_MasloSmazka  ,_Sec( 0.0 )      , (sw)0xFFFFu      ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "мин", _form(1,3,1,2) },
#endif
#ifdef bi_Smazka_Podsh
    { "T-смаз.подш.  ", &_r.Time_Smazka_Podsh ,_Sec( 0.0 )      , (sw)0xFFFF       ,_Sec(60.0)    ,(w*)&_ind_Nom, _Sec(10.0)     , 0xff, "мин", _form(1,3,1,2) },
#endif
    { "N-стоянка     ", &_r.Stoyanka_Eds      ,_Skor_nom( +0.0 ),_Skor_nom( +5.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Id-стоянкa    ", &_r.Stoyanka_Tok      ,_Id_nom( 0.0 )   ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.10 ) , 0xff, "ном", _form(1,2,1,2) },
    { "T-ав.стоянка  ", &_r.Stoyanka_Time     ,_Sec( 0.0 )      ,_Sec( 120.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "сек", _form(1,2,0,2) },
    { "T-пр.стоянка  ", &_r.Stoyanka_Time_Predupr ,_Sec( 0.0 )  ,_Sec( 120.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(1.0)      , 0xff, "сек", _form(1,2,0,2) },
  //{ "Id-конт-макс  ", &_r.Tok_Otkl_Kontaktor,_Id_nom( 0.0 )   ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.10 ), 0xff, "ном", _form(1,2,2,2) },
  //{ "Id-откл.МТ    ", &_r.Id_Otkl_MT        ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
  //{ "T-отпуск.МТ   ", &_r.Time_MT           ,_Sec( 0.0 )      ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },
  //{ "Uизол-макс    ", &_r.Uinsul_max        , 0               , (w)(9.9*(_AD_MAX/5.0))  ,(w)(1.0*(_AD_MAX/5.0)),(w*)&_ind_Nom,(w)(0.01*(_AD_MAX/5.0)),0xff," B"  , _form(1,2,2,2) },
#ifdef Insul_D_ach
  #ifndef  Uf_ach
    { "Uf-эконом.    ", &_or.Uf_econom        ,_Uf_nom( 0.00 )  ,_Uf_nom( +2.00 )  , _Uf_Nom      ,(w*)&_ind_Nom, _Uf_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
  #endif
#endif
//------------
 #ifndef _CM3_
//------------
#ifdef _SIFU2_
  #if   defined( _1P_ach ) || defined( _2P_ach )
    { "1Р_2P-макс    ", &_r._1P_2P_max        ,(sw)(-9.9*(_AD_MAX/5.0)), 9.9*(_AD_MAX/5.0)  ,1.0*(_AD_MAX/5.0),(w*)&_ind_Nom, 0.1*(_AD_MAX/5.0),0xff," B"  , _form(0,2,2,2) },
    { "1Р_2P-мин     ", &_r._1P_2P_min        ,(sw)(-9.9*(_AD_MAX/5.0)), 9.9*(_AD_MAX/5.0)  ,1.0*(_AD_MAX/5.0),(w*)&_ind_Nom, 0.1*(_AD_MAX/5.0),0xff," B"  , _form(0,2,2,2) },
  #endif
#endif
#ifdef PUM_ach
    { "ПитУМ-макс    ", &_r.PUM_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "ПитУМ-мин     ", &_r.PUM_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef P12_ach
    { "P12-макс      ", &_r.P12_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "P12-мин       ", &_r.P12_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef N12_ach
    { "N12-макс      ", &_r.N12_max           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
    { "N12-мин       ", &_r.N12_min           ,(sw)(-102*9.99)  , (w)(102*9.99)    , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) },
#endif
    { "1P24-макс     ", &_r.P24_max           ,-102*9.99        , 102*9.99         , 102          ,(w*)&_ind_Nom,  1              ,0xff, " B" , _form(0,2,2,2) },
    { "1P24-мин      ", &_r.P24_min           ,-102*9.99        , 102*9.99         , 102          ,(w*)&_ind_Nom,  1             , 0xff, " B" , _form(0,2,2,2) }
//------------
 #else
//------------
#ifdef _SIFU2_
  #if   defined( _1P_ach ) || defined( _2P_ach )
    { "1Р_2P-макс    ", &_r._1P_2P_max,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4           , 0xff, " B" , _form(0,2,2,2) },
    { "1Р_2P-мин     ", &_r._1P_2P_min,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4           , 0xff, " B" , _form(0,2,2,2) },
  #endif
#endif
#ifdef PUM_ach
    { "ПитУМ-макс    ", &_r.PUM_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "ПитУМ-мин     ", &_r.PUM_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef P12_ach
    { "P12-макс      ", &_r.P12_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "P12-мин       ", &_r.P12_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
#ifdef N12_ach
    { "N12-макс      ", &_r.N12_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "N12-мин       ", &_r.N12_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
#endif
    { "1P24-макс     ", &_r.P24_max ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) },
    { "1P24-мин      ", &_r.P24_min ,(sw)(-9.99*_AD_VOLT/2) , (w)(9.99*_AD_VOLT/2) , _AD_VOLT/2   ,(w*)&_ind_Nom,  4             , 0xff, " B" , _form(0,2,2,2) }
//------------
 #endif
//------------
  };

_x_far const struct STB       stb_reg[ ] =
  {
    { "N#-макс       ", &_r.Z_SkMax_P         ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "N#-мин        ", &_r.Z_SkMax_M         ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
    { "N-останов     ", &_r.Ostanov_skor      ,_Skor_nom( +0.0 ),_Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1<<_Skor_Shift , 0xff, "%"  , _form(1,3,2,2) },
    { "T-останов     ", &_r.Ostanov_time      ,_Sec( 0.1 )      ,_Sec( 9.0 )       ,_Sec(1.0)     ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,1,2,2) },
#ifndef  _ZI_30min
  #ifdef _ZI_4TEMPA
    { "ТемпЗИ-РСВп'+'", &_r.T_ZISkorP_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗИ-РСВп'-'", &_r.T_ZISkorP_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗИ-РСНз'+'", &_r.T_ZISkorM_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗИ-РСНз'-'", &_r.T_ZISkorM_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #ifdef bi_Reviz
    { "ТемпЗИ-РС'рвз'", &_or.T_ZISkor_Reviz   ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #endif
   #ifdef bi_Fors_Temp
    { "ТемпЗИ-РС'фрс'", &_r.T_ZISkorP_Fors    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #endif
  #else
    { "ТемпЗИ-РСВп'+'", &_r.T_ZISkorP_Razg    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
    { "ТемпЗИ-РСВп'-'", &_r.T_ZISkorP_Torm    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },
   #ifdef bi_Reviz
    { "ТемпЗИ-РС'рвз'", &_or.T_ZISkor_Reviz   ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
   #endif
   #ifdef bi_Fors_Temp
  //{ "ТемпЗИ-РС'фрс'", &_r.T_ZISkorP_Fors    ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
   #endif
  #endif
#else
    { "ТемпЗИ-РС'+'  ", &_r.T_ZISkorP_Razg    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "мин", _form(1,2,1,2) },
    { "ТемпЗИ-РС'-'  ", &_r.T_ZISkorP_Torm    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "мин", _form(1,2,1,2) },
 #ifdef bi_Fors_Temp
    { "ТемпЗИ-РС'фрс'", &_r.T_ZISkorP_Fors    , 0               , 300              , 10           ,(w*)&_ind_Nom,  1             , 0xff, "мин", _form(1,2,1,2) },
 #endif
#endif
    { "ТeмпЗИ-РС's'  ", &_r.T_ZISkor_Parab,       _Sec( 0.0 ),       _Sec( 20.0 ),     _Sec( 1.0 ),(w*)&_ind_Nom, _Sec( 0.1 )    , 0xff, "сек", _form(1,3,2,2) },
    { "ТeмпЗИ-РС-dN  ", &_r.T_ZISkor_Parab_delta, _Skor_nom( 0.0 ),  _Skor_nom( 1.0 ), _Skor_Nom  ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
    { "Порог-ФС      ", &_r.porog_fil         ,_Skor_nom( +0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,3,2,2) },
    { "K-ФС          ", &_r.K_fil_sk          , 2               , 1000             , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,2) },
    { "Kп-РC         ", &_r.KRSP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "ед" , _form(1,3,2,2) },
    { "Tи-РC         ", &_r.KRSI              , 0               , 2000             , 1            ,(w*)&_ind_Nom,  2             , 0xff, "мceк",_form(1,3,0,2) },
  /*{ "Kпип-РC       ", &_r.KRSPIP            , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  32            , 0xff, "ед" , _form(1,3,2,2) },
  //{ "Id#-макс      ", &_r.IZMAX             ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", 2 },
    { "Id#-макс1P    ", &_r.OuRSMaxMost1      ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "Id#-макс1M    ", &_r.OuRSMaxMost2      ,_Id_nom(-3.5 )   ,_Id_nom( 0.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "Id#-макс2P    ", &_r.OuRSMax2Most1     ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "Id#-макс2M    ", &_r.OuRSMax2Most2     ,_Id_nom(-3.5 )   ,_Id_nom( 0.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "Id-гр-непp    ", &_r.INN0              ,_Id_nom( 0.0 )   ,_Id_nom( 2.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(1,2,2,2) },
    { "ТемпЗИ-РТ'+'  ", &_r.Temp_RT_P         ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "ном " , _form(1,4,1,2) },
    { "ТемпЗИ-РТ'-'  ", &_r.Temp_RT_M         ,_Id_nom200( 0.0 ),_Id_nom200( 320.0), _Id_Nom200   ,(w*)&_ind_Nom,_Id_nom200(0.20), 0xff, "ном " , _form(1,4,1,2) },
    { "'Kп-РТ        ", &_r_KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "ед" , _form(1,3,2,2) },
    { "'Kп-РТ-AH     ", &an_KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  0             , 0xff, "ед" , _form(1,3,2,2) },
    { "Kп-РТ-уст     ", &_r.KRTP              , 0               , 127*256          , 256          ,(w*)&_ind_Nom,  4             , 0xff, "ед" , _form(1,3,2,2) },
    { "'Ти-РТпреp    ", &_r_KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "'Ти-РТпреp-AH ", &an_KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ти-РТпреp-уст ", &_r.KRTPRI            , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  1             , 0xff, "мceк",_form(1,3,2,2) },
    { "'Ти-РТнепp    ", &_r_KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "'Ти-РТнепp-AH ", &an_KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  0             , 0xff, "мceк",_form(1,3,2,2) },
    { "Ти-РТнепp-уст ", &_r.KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "мceк",_form(1,3,2,2) },
    { "K-РТ-дин      ", &_r.KRTDI             , 0               , 999              , 1            ,(w*)&_ind_Nom,  1             , 0xff, "ед" , _form(1,3,0,2) },
  */{ "РС-вых-макс   ", &_r.RTMAX             ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "РС-вых-мин    ", &_r.RTMIN             ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-макс       ", &_r.S_Alfa_Max        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-мин        ", &_r.S_Alfa_Min        ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-начальное  ", &_r.S_Alfa_Start      ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "ТемпЗИ-L#     ", &_r.S_DeltaAlfa_Max   ,_Grad( 0.0 )     ,_Grad(  25.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "T-задерж-Пуск ", &_or.T_zaderg_pusk    , 3               ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },
    { "T-затян.пуск  ", &_or.Time_Zatyan_Pusk ,_Sec( 0.0 )      ,_Sec( 240.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,3,2,2) },
    { "T-мин.пуск    ", &_or.T_min_Pusk       ,_Sec( 0.0 )      ,_Sec( 240.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.1)      , 0xff, "сек", _form(1,3,2,2) },
    { "T-откл.КЗ     ", &_or.T_otkl_KZ        ,_Sec( 0.0 )      ,_Sec( 240.0 )     ,_Sec(1.0)     ,(w*)&_ind_Nom, _Sec(0.25)     , 0xff, "сек", _form(1,3,2,2) },
  //{ "T-сплошн.ИУ   ", &_or.Time_Sploshnyak  ,_Sec( 0.0 )      ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },
    { "T-включения-К3", &_or.T_vkl_KZ         ,_Sec( 0.0 )      ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  _Sec(0.5)     , 0xff, "сек", _form(1,2,2,2) },
    { "T-снятия ИУ-К3", &_or.Time_snyatIU_KZ  ,_Sec( 0.0 )      ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  _Sec(0.5)     , 0xff, "сек", _form(1,2,2,2) },
    { "N#-начальное  ", &_or.ZIS_Nachal       ,_Skor_nom(  0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "N#-0,1        ", &_or.Pusk_0_1         ,_Skor_nom(  0.0 ),_Skor_nom( +2.00) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "N#-1,0        ", &_or.Pusk_1_0         ,_Skor_nom(  0.0 ),_Skor_nom( +2.00) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Nпорог-вкл-V21", &_or.N_min[0]         ,_Skor_nom(  0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Nпорог-вкл-V22", &_or.N_min[1]         ,_Skor_nom(  0.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Nпорог-вкл-V23", &_or.N_min[2]         ,_Skor_nom(  0.0 ),_Skor_nom( +2.00) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "Nпорог-вкл-KЗ.", &_or.N_min[3]         ,_Skor_nom(  0.0 ),_Skor_nom( +2.00) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },
    { "L-мин-шунтир. ", &_or.Alfa_Min_Shunt   ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "T-L-мин-шунтиp", &_or.Alfa_min_time    ,_fSec( 0.0 )     ,_fSec(1)          ,_fSec(0.001)  ,(w*)&_ind_Nom, _fSec(0.002)   , 0xff, "мс ", _form(1,3,0,2) },
    { "L#-ступени1   ", &_or.Alfa_Shunt       ,_Grad( 0.0 )     ,_Grad(179.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-ступени2   ", &_or.Alfa_Shunt2      ,_Grad( 0.0 )     ,_Grad(179.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "L#-ступени3   ", &_or.Alfa_Shunt3      ,_Grad( 0.0 )     ,_Grad(179.0 )     ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,3,0,2) },
    { "I-ограничения ", &_or.I_Ogr            ,_Id_nom( 0.0 )   ,_Id_nom( 3.5 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "Т-фильтра Id  ", &_or.T_Id_flt         ,_fSec( 0.0)      , _fSec( 3 )       ,_fSec(1)      ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек", _form(1,2,2,2) },
    { "Ти-РТ         ", &_r.KRTNI             , 0               , (sw)0xFFFFu      , 64           ,(w*)&_ind_Nom,  16            , 0xff, "мceк",_form(1,3,0,2) },
    { "Tф-апер.звена ", &_or.Tf_aper          , 0.01            , 0.1              , 1            ,(w*)&_ind_Nom, 0.001          , 0xff, "сек", _form(1,1,3,3) },
    { "Т-фил-скольж. ", &_or.Tfil             , 0.01            , 0.5              , 1            ,(w*)&_ind_Nom, 0.001          , 0xff, "сек", _form(1,1,3,3) },
    { "N#-текущее    ", &Z_Skor               ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
  //{ "Id#-текущее   ", &OuRegS_dop_kod       ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01 ), 0xff, "ном", _form(0,2,2,2) },
    { "L#-текущее    ", &S.Alfa               ,_Grad( 0.0 )     ,_Grad( 179.0 )    ,_Grad(1.0)    ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(1,4,2,2) }
  };

_x_far const struct STB       peregr[ ] =
  {
    { "Id_I1 "        , &_r.I2Tr.I[0]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T1 "        , &_r.I2Tr.T[0]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  100           , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I2 "        , &_r.I2Tr.I[1]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T2 "        , &_r.I2Tr.T[1]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  10            , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I3 "        , &_r.I2Tr.I[2]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T3 "        , &_r.I2Tr.T[2]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I4 "        , &_r.I2Tr.I[3]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T4 "        , &_r.I2Tr.T[3]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,5,0,2) },
    { "Id_I5 "        , &_r.I2Tr.I[4]         ,_Id_nom( 1.02 )  ,_Id_nom( 3.0 )    ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_T5 "        , &_r.I2Tr.T[4]         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,5,0,2) },
    { "Id-интегр."    , &Id_TeploIntegr       ,_Id_nom( 0.99 )  ,_Id_nom( 1.00 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom(0.01)  , 0xff, "ном", _form(1,3,2,2) },
    { "Id_To "        , &_r.I2Tr.Tohl         , 0               , 3600*3           , 1            ,(w*)&_ind_Nom,  10            , 0xff, "сек", _form(1,5,0,2) }
  };

_x_far const struct STB       stb_masht[ ] =
  {
  //{ "Id-масштаб    ", &_r.Mashtab_Id        , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "ед"  , 2 },
    { "Id-ном-УПТФ   ", &_sr.NOM.Id.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A"  , _form(1,5,0,2) },
    { "Id-ном-ДТ     ", &_sr.Dat.Id           , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A"  , _form(1,5,0,2) },
    { "'Id-макс-ДТ   ", &Mashtab.Id_max       , 0               , _Id_nom( 7.0 )   , _Id_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "ном" , _form(1,2,3,2) },
    { "'Id-масштаб   ", &Mashtab.Id           , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,3,3,2) },
#ifdef   Itt_ach
    { "Idtt-масштаб  ", &_r.Mashtab_Idtt      , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },
#endif
    { "t-TV-масштаб  ", &_or.T_Scale          , 0               , 100              , 1            ,(w*)&_ind_Nom, 0.001          , 0xff, "ед ", _form(1,3,3,0) },
    { "DAC0-масшт.   ", &_or.dac_numb[0].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) },
 #ifdef _DAC_OFFSET
    { "'DAC0-смещ.0  ", &_or.dac_numb[0].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) },
 #endif
    { "DAC1-масшт.   ", &_or.dac_numb[1].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC1-смещ.0  ", &_or.dac_numb[1].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#ifdef  _PPG_for_DAC2
   ,{ "DAC2-масшт.   ", &_or.dac_numb[2].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC2-смещ.0  ", &_or.dac_numb[2].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC3
   ,{ "DAC3-масшт.   ", &_or.dac_numb[3].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC3-смещ.0  ", &_or.dac_numb[3].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC4
   ,{ "DAC4-масшт.   ", &_or.dac_numb[4].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC4-смещ.0  ", &_or.dac_numb[4].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC5
   ,{ "DAC5-масшт.   ", &_or.dac_numb[5].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC5-смещ.0  ", &_or.dac_numb[5].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC6
   ,{ "DAC6-масшт.   ", &_or.dac_numb[6].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC6-смещ.0  ", &_or.dac_numb[6].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
#ifdef  _PPG_for_DAC7
   ,{ "DAC7-масшт.   ", &_or.dac_numb[7].mashtab, (w)0xF700     , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(0,3,3,2) }
 #ifdef _DAC_OFFSET
   ,{ "'DAC7-смещ.0  ", &_or.dac_numb[7].offset,_DAC_setka_min,_DAC_setka_max,_DAC_setka_max      ,(w*)&_ind_100, 0              , 0xff, "%  ", _form(0,3,1,2) }
 #endif
#endif
  };

_x_far const struct STB       stb_shtat[ ] =
  {
    { "Iрот-ном-Двиг.", &_or.I_rot_nom        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " A"  , _form(1,5,0,2) },
    { "'Iрот-масштаб ", &Mashtab.Irot         , 0               , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,3,2) },
  //{ "Ud-масштаб    ", &_r.Mashtab_Ud        , 0               , 0x09FF           , 0x0100       ,(w*)&_ind_Nom, 3              , 0xff, "ед"  , 2 },
    { "Uрот-ном-Двиг.", &_sr.NOM.Ud.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B"  , _form(1,5,0,2) },
    { "Uрот-ном-ДН   ", &_sr.Dat.Ud           , 0               , 0x7fff           , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B"  , _form(1,5,0,2) },
    { "'Uрот-макс-ДН ", &Mashtab.Ud_max       , 0               , _Ud_nom( 7.0 )   , _Ud_Nom      ,(w*)&_ind_Nom, 0              , 0xff, "ном" , _form(1,2,3,2) },
    { "'Uрот-масштаб ", &Mashtab.Ud           , (sw)0xF700      , 0x0A00           , 0x0100       ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,3,3,2) },
    { "Uстат-ном-Двиг", &_sr.NOM.Iv.fe        , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " B"  , _form(1,5,0,2) },
    { "Iстат-ном-Двиг", &_or.Istat            , 0               , (sw)0xffff-100   , 10           ,(w*)&_ind_Nom, 1              , 0xff, " A"  , _form(1,5,1,2) },
    { "N-ном-Двиг.   ", &_sr.NOM.N.fe         , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " Об/мин", _form(1,5,0,2) },
    { "P-ном-Двиг.   ", &_or.Pnom             , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 1              , 0xff, " кBт", _form(1,5,0,2) },
    { "`Z-пары полюс.", &Pary_AD              , 1               , 16               , 1            ,(w*)&_ind_Nom, 0              , 0xff, " пар", _form(1,2,0,2) },
    { "Km            ", &_or.Km               , 1               , 3.0              , 1            ,(w*)&_ind_Nom, 0.1            , 0xff, "ед"  , _form(1,1,1,3) },
    { "'Kт           ", &Kt                   , 0               , 2                , 1            ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,1,4,3) },
    { "'M-ном-Двиг.  ", &Mnom                 , 0               , (sw)0xffff-100   , 1            ,(w*)&_ind_Nom, 0              , 0xff, " Н*м", _form(1,6,0,2) },
    { "'S-ном-Двиг.  ", &SlipNom              , 0               , 1                , 1            ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,1,4,3) },
  //{ "'w-ном        ", &OmegaNom             , 0               , 400              , 1            ,(w*)&_ind_Nom, 0              , 0xff, " рад/с" , _form(1,3,4,3) },
  //{ "'w-0          ", &OmegaNullSynhr       , 0               , 400              , 1            ,(w*)&_ind_Nom, 0              , 0xff, " рад/с" , _form(1,3,4,3) },
    { "'r1-статора   ", &r1                   , 0               , 10               , 1            ,(w*)&_ind_Nom, 0              , 0xff, " Ом" , _form(1,1,4,3) },
    { "'r2-ротора    ", &r2                   , 0               , 10               , 1            ,(w*)&_ind_Nom, 0              , 0xff, " Ом" , _form(1,1,4,3) },
  //{ "'R-oe-рассчет ", &Rsigma_raschet       , 0               , 1                , 1            ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,1,3,3) },
  //{ "'X-oe-рассчет ", &Xsigma_raschet       , 0               , 1                , 1            ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,1,3,3) },
  //{ "R-oe-уст      ", &_or.Rsigma           , 0               , 1                , 1            ,(w*)&_ind_Nom, 0.0050         , 0xff, "ед"  , _form(1,1,3,3) },
  //{ "X-oe-уст      ", &_or.Xsigma           , 0               , 1                , 1            ,(w*)&_ind_Nom, 0.0050         , 0xff, "ед"  , _form(1,1,3,3) },
  //{ "'Rсигма-oe-раб", &Rsigma               , 0               , 1                , 1            ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,1,3,3) },
  //{ "'Xсигма-oe-раб", &Xsigma               , 0               , 1                , 1            ,(w*)&_ind_Nom, 0              , 0xff, "ед"  , _form(1,1,3,3) },
    { "R-сигма-oe    ", &Rsigma_korr          , 0               , 1                , 1            ,(w*)&_ind_Nom, 0.0010         , 0xff, "ед"  , _form(1,1,3,3) },
    { "X-сигма-oe    ", &Xsigma_korr          , 0               , 1                , 1            ,(w*)&_ind_Nom, 0.0010         , 0xff, "ед"  , _form(1,1,3,3) }
  };

_x_far const struct STB       stb_serv[ ] =
  {
    { "След-крат.    ", &sled.kratn           , 0               , 31               , 1000         ,(w*)&sled.dt_scan, 1          , 0xff, "мсек", _form(1,3,2,2) },
#ifdef _JOURNAL
    { "Журнал-крат.  ", &TabJrn.dt_scan       , _fSec(0)        , _fSec(5.0)       , _fSec(1.0)   ,(w*)&_ind_Nom, _fSec(0.01)    , 0xff, "сек" , _form(1,1,2,2) },
#endif
#ifdef _WatchDog
    { "Время WatchDog", &_r.WD_time           , 0               ,300               , 1            ,(w*)&_ind_Nom, 50             , 0xff, "мсeк", _form(1,4,0,2) },
#endif
  //{ "След-скан.    ", &sled.dt_scan         , 0               ,_MkSec(50u*1000u) ,_MkSec(1000)  ,(w*)&_ind_Nom, _MkSec(100)    , 0xff, "мсек", _form(1,2,2,2) },
  //{ "cS#           ", &canr.S_zad           ,_Grad( 0.0 )     ,_Grad( 359.0 )    ,_Grad( 1.0)   ,(w*)&_ind_Nom, _Grad( 1.0 )   , 0xff, "грд", _form(0,4,0,2) },
    { "cN#           ", &canr.N_zad           ,_Skor_nom( -2.0 ),_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(0,2,2,2) },
  /*{ "cId#          ", &canr.Id_zad          ,_Id_nom( -3.0 )  ,_Id_nom( +3.0 )   ,_Id_Nom       ,(w*)&_ind_Nom, _Id_nom( 0.01) , 0xff, "ном", _form(0,2,2,2) },
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
    { "CAN0-адреc 1  ", &can_setting( _CAN0_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" ,  _form(1,3,0,1) },
    { "CAN0-адреc 2  ", &can_setting( _CAN0_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" ,  _form(1,3,0,1) },
    { "CAN0-сеткa    ", &can_setting( _CAN0_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" ,  _form(1,3,0,1) },
    { "Tаймаут CAN1  ", &_r.can[1].connect                         , 0    , 100    , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек", _form(1,3,0,1) },
    { "CAN1-адреc 1  ", &can_setting( _CAN1_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" ,  _form(1,3,0,1) },
    { "CAN1-адреc 2  ", &can_setting( _CAN1_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" ,  _form(1,3,0,1) },
    { "CAN1-сеткa    ", &can_setting( _CAN1_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" ,  _form(1,3,0,1) }
#ifdef _CAN2_Port
   ,{ "Tаймаут CAN2  ", &_r.can[2].connect                         , 0    , 100    , 1            ,(w*)&_ind_Nom, 1              , 0xff, "мсек", _form(1,3,0,1) },
    { "CAN2-адреc 1  ", &can_setting( _CAN2_Port).addr             , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,0,1) },
    { "CAN2-адреc 2  ", &can_setting( _CAN2_Port).addr_p           , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,0,1) },
    { "CAN2-сеткa    ", &can_setting( _CAN2_Port).master_addr_size , 0    , 0x7f   , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,0,1) }
#endif
#ifdef _CAN_MASTER
   ,{ "Адрес абон.1  ", &_r.AddrDevice1       , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
  #ifdef _ADDR_DEVICE2
    { "Адрес абон.2  ", &_r.AddrDevice2       , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
  #endif
  #ifdef _ADDR_DEVICE3
    { "Адрес абон.3  ", &_r.AddrDevice3       , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
  #endif
  #ifdef _ADDR_DEVICE4
    { "Адрес абон.4  ", &_r.AddrDevice4       , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
  #endif
  #ifdef _ADDR_DEVICE5
    { "Адрес абон.5  ", &_r.AddrDevice5       , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед"  , _form(1,3,0,1) },
  #endif
    { "T-MconnectCfg ", &_r.T_mConnect_cfg    ,_Sec( 0.0 )      ,_Sec( 5.0 )       , _Sec(1.0)    ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,2,2,2) },
    { "T-MconnectSts ", &_r.T_mConnect_sts    ,_Sec( 0.0 )      ,_Sec( 5.0 )       , _Sec(1.0)    ,(w*)&_ind_Nom, 1              , 0xff, "сек", _form(1,2,2,2) },
    { "CAN-такт      ", &_r.time_scan         ,_fSec( 0.0 )     ,_fSec( 1.0 )      , _fSec( 1.0)  ,(w*)&_ind_Nom,_fSec(0.001)    , 0xff, "cек", _form(1,1,3,2) }
#endif
#ifdef _CM3_
   ,{ "Modbus-адреc  ", &_r.rs485.addr        , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,0,1) }
#endif
  };

#ifdef _CM3_
const _x_far struct STB       stb_ADC_masht[ ] =
  {
    { "Масшт.n0 ", &_ar.ADC_Scale[0]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n1 ", &_ar.ADC_Scale[1]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n2 ", &_ar.ADC_Scale[2]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n3 ", &_ar.ADC_Scale[3]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n4 ", &_ar.ADC_Scale[4]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n5 ", &_ar.ADC_Scale[5]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n6 ", &_ar.ADC_Scale[6]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n7 ", &_ar.ADC_Scale[7]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n8 ", &_ar.ADC_Scale[8]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n9 ", &_ar.ADC_Scale[9]  , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n10", &_ar.ADC_Scale[10] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n11", &_ar.ADC_Scale[11] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n12", &_ar.ADC_Scale[12] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n13", &_ar.ADC_Scale[13] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n14", &_ar.ADC_Scale[14] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
    { "Масшт.n15", &_ar.ADC_Scale[15] , ach_scale_min , ach_scale_max , def_ach_scale        ,(w*)&_ind_Nom, 1              , 0xff, "ед " , _form(1,1,4,2) },
 };
#endif


#ifdef _A7_Obj_Ust
_x_far const struct STB       stb_obj[ ] =
  {
      _A7_Obj_Ust
  };
#endif

const struct UstUzm   Ustav[] =
  {
    {"Регулир.   " ,sizeof(stb_reg   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_reg   [0] },
    {"Защиты     " ,sizeof(stb_avar  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_avar  [0] },
    {"Перегрузки " ,sizeof(peregr    )/sizeof(struct STB) ,(_x_far const struct STB*)&peregr    [0] },
    {"Парам.двиг." ,sizeof(stb_shtat )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_shtat [0] },
    {"Масштабы   " ,sizeof(stb_masht )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_masht [0] },
#ifdef _CM3_
    {"Масшт. АЦП " ,sizeof(stb_ADC_masht)/sizeof(struct STB) ,&stb_ADC_masht[0] },
#endif
#ifdef _A7_Obj_Ust
    {"Объект.упр." ,sizeof(stb_obj   )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_obj   [0] },
#endif
    {"Служебныe  " ,sizeof(stb_serv  )/sizeof(struct STB) ,(_x_far const struct STB*)&stb_serv  [0] }
#ifdef  _INTERPRETER
   ,{"Объект.прг " ,sizeof(Ust_Obj_Prg)/sizeof(struct Obj_STB) ,(_x_far const struct STB*)&Ust_Obj_Prg[0] }
#endif
  }; /* Количество уставок в таблице */
const word _MaxNumUstav = sizeof(Ustav)/sizeof(const struct UstUzm) ;


//------------- А6 - Таблица индикации -------------------

_x_far const struct Ind  ind_reg[] =
  {
         { "N    , Tпуск  ", { &Skor           , &Timer_Pusk    },{_Skor_nom(1)   ,_Sec(1)         },{ "%, ","сеk"}, {(w*)&_ind_100,(w*)&_ind_Nom},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "L    , Id     ", { &S.Alfa_Old     , &Id_dop_kod    },{_Grad( 1 )     ,_Id_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "L    , N      ", { &S.Alfa_Old     , &Skor          },{_Grad( 1 )     ,_Skor_nom(1)    },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,1,2)} },
         { "Fr   , N      ", { &Frot           , &Skor          },{ 360           ,_Skor_nom(1)    },{ "Гц " ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,2,0,2),_form(0,3,1,2)} },
         { "Id   , N      ", { &Id_dop_kod     , &Skor          },{_Id_Nom        ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N#   , N#R    ", { &Z_Skor         , &ZISkor        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N#R  , N      ", { &ZISkor         , &Skor          },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,1,2)} },
         { "N    , Ступ.  ", { &Skor           , &SP_stup       },{_Skor_nom(1)   , 1              },{ "%, " ,""  }, {(w*)&_ind_100,(w*)&_ind_Nom},{_form(0,3,1,2),_form(0,1,0,2)} },
         { "Nnf  , Nf     ", { &Skor_ind       , &Skor_f        },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Id   , Id-фил.", { &Id_dop_kod     , &Id_flt.out    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "Id-фил,Iогран.", { &Id_flt.out     , &ZIDN          },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "N#R  , RTout  ", { &ZISkor         , &OIRT          },{_Skor_nom(1)   ,_Skor_nom(1)    },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,0,2),_form(1,3,0,2)} },
         { "IA   , IB     ", { &IA             , &IB            },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "IC            ", { &IC                              },{_Id_Nom                         },{ "%  "      }, {(w*)&_ind_100              },{_form(0,3,0,2)               } },
         { "Uac  , Uba    ", { &Uac            , &Uba           },{_Ud_Nom        ,_Ud_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
       /*{ "Ix   , Iy     ", { &Ix             , &Iy            },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,3),_form(0,3,0,3)} },
         { "Ux   , Uy     ", { &Ux             , &Uy            },{_Ud_Nom        ,_Ud_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,3),_form(0,3,0,3)} },
         { "Psimx, Psimy  ", { &Psi_m_X[1]     , &Psi_m_Y[1]    },{ 1             , 1              },{ ", "  ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,3,0,3)} },
         { "Slip , SlipF  ", { &Slip           , &Slip_f[1]     },{ 1             , 1              },{ ", "  ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,3,0,3),_form(0,3,0,3)} },
         { "Lr (грд , рад)", { &Lrot           , &Phi_e[1]      },{_Grad( 1 )     , 1              },{ "гp, ",""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,2),_form(0,3,0,3)} },
         { "w-rot, N-rot  ", { &OmegaRot       , &SkorRot       },{ 1             ,_Skor_nom(1)    },{ "r, " ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,1,1,3),_form(0,3,0,2)} },*/
         { "Id  ,Id-перегp", { &Id_dop_kod     , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(1,3,0,2)} },
         { "Id-инт,Id-пер.", { &Id_TeploIntegr , &Id_teplo_max  },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(1,3,2,2),_form(1,3,0,2)} },
#ifdef Itt_ach
         { "Idtt , Id     ", { &Idtt           , &Id_dop_kod    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} }
#endif
       //{ "Ud   , Uизол  ", { &UdSr           , &Uinsul        },{_Ud_Nom        , (w)(1.0*(_AD_MAX/5.0))},{ "%,"  ,"B" }, {(w*)&_ind_100,(w*)&_ind_Nom},{_form(0,3,1,2),_form(0,1,2,2)} },
       //{ "Uизол,Uиз.макc", { &Uinsul         , &Uinsul_max    },{(w)(1.0*(_AD_MAX/5.0)), (w)(1.0*(_AD_MAX/5.0))},{ "В,"  ,"B" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,1,2,2),_form(0,1,2,2)} },
         { " N: об/мин, % ", { &N_ob_min       , &Skor          },{ 1             ,_Skor_Nom       },{ ", "  ,"%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(0,4,0,3),_form(0,3,1,2)} },
         { "  Id (%, А)   ", { &Id_dop_kod     , &Id_dop_kod   }, { _Id_Nom , _Id_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Id.fe},{_form(0,3,1,2),_form(0,5,0,2)} }
       //{ "  Ud (%, В)   ", { &UdSr           , &UdSr         }, { _Ud_Nom , _Ud_Nom },{","," "}, {(w*)&_ind_100,(w*)&_sr.NOM.Ud.fe},{_form(0,3,1,2),_form(0,5,0,2)} }
  };

_x_far const struct Ind  ind_serv[] =
  {
       //{ "T-рег, T-int  ", { &time_Integr    , &TimeAD_Skor     },{_MkSec(1000)   ,_MkSec(1)       },{ "ms,","mks"}, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,2,1,2),_form(1,4,0,2)} },
       //{ "Tzar,Tmth: mks", { &time_zar       , &time_math       },{_MkSec(1)      ,_MkSec(1)       },{ ", " ,""   }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,4,0,2),_form(1,4,0,2)} },
         { "t-TV          ", { &T_izm                             },{10                              },{ "гр"       }, {(w*)&_ind_Nom              },{_form(0,3,1,2)               } },
         { "Tint,Tizm: mks", { &TimeAD_Skor    , &time_izm        },{_MkSec(1)      ,_MkSec(1)       },{ ", " ,""   }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,4,0,2),_form(1,4,0,2)} },
         { "flgO ,  cN#   ", { &flgO.all       , &canr.N_zad      },{ 1             ,_Skor_Nom       },{ "h, ","%"  }, {(w*)&_ind_Nom,(w*)&_ind_100},{_formh(1,2   ),_form(0,3,0,2)} },
         { "cCfgR,  cStsR ", { &canr.CfgReg.all, &canr.StatReg.all},{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },
       /*{ "cN#           ", { &canr.N_zad                        },{_Skor_Nom                       },{ "%"        }, {(w*)&_ind_100              },{_form(0,3,0,2)               } },
         { "cId# ,  cdId# ", { &canr.Id_zad    , &canr.dId_zad    },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cId#P,  cId#M ", { &canr.Idz_MaxP  , &canr.Idz_MaxM   },{_Id_Nom        ,_Id_Nom         },{ "%, " ,"%" }, {(w*)&_ind_100,(w*)&_ind_100},{_form(0,3,0,2),_form(0,3,0,2)} },
         { "cL#  ,  cF#   ", { &canr.L_zad     , &canr.F_zad      },{_Grad( 1 )     ,_Fv_Nom         },{ "гp, ","%" }, {(w*)&_ind_Nom,(w*)&_ind_100},{_form(1,3,0,2),_form(0,3,0,2)} },
         { "cAo0 ,  cAo1  ", { &canr.Ao[0]     , &canr.Ao[1]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi0 ,  cAi1  ", { &canr.Ai[0]     , &canr.Ai[1]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi2 ,  cAi3  ", { &canr.Ai[2]     , &canr.Ai[3]      },{ 1             , 1              },{ ","   ,""  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(0,5,0,2),_form(0,5,0,2)} },
         { "cAi4          ", { &canr.Ai[4]                        },{ 1                              },{ " "        }, {(w*)&_ind_Nom              },{_form(0,5,0,2)               } },*/
         { "CAN0Err:Bus   ", { &can_dd[_CAN0_Port].Avar           },{ 1                                },{"ед "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN0Err:Rec,Tx", { &can_dd[_CAN0_Port].Error_receive,&can_dd[_CAN0_Port].Error_send},{1,1},{"ед, ","ед "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
         { "CAN1Err:Bus   ", { &can_dd[_CAN1_Port].Avar                                        },{1  },{"ед "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN1Err:Rec,Tx", { &can_dd[_CAN1_Port].Error_receive,&can_dd[_CAN1_Port].Error_send},{1,1},{"ед, ","ед "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
#ifdef _CAN2_Port
         { "CAN2Err:Bus   ", { &can_dd[_CAN2_Port].Avar                                        },{1  },{"ед "       },{(w*)&_ind_Nom              },{_form(1,3,0,1)               }},
         { "CAN2Err:Rec,Tx", { &can_dd[_CAN2_Port].Error_receive,&can_dd[_CAN2_Port].Error_send},{1,1},{"ед, ","ед "},{(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)}},
#endif
#ifdef _CAN_MASTER
         { "CAN:time      ", { &Opros_time              }, { _fSec(1)         },{"cek "   },{(w*)&_ind_Nom } ,{_form(1,1,3,2)               } },
       //{ "cCfgM1,cStsM1 ", { &CfgM.all       , &StsM.all           },{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },
         { "Dev1:  rd, wr ", { &Tst_Read_Dev1  , &Tst_Write_Dev1     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },
         { "Dev1: SendRec ", { &abDev1.err.send, &abDev1.err.receive }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} },
#endif
#ifdef _ADDR_DEVICE2
         { "Dev2:  rd, wr ", { &Tst_Read_Dev2  , &Tst_Write_Dev2     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },
         { "Dev2: SendRec ", { &abDev2.err.send, &abDev2.err.receive }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} },
#endif
#ifdef _ADDR_DEVICE3
         { "Dev3:  rd, wr ", { &Tst_Read_Dev3  , &Tst_Write_Dev3     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },
         { "Dev3: SendRec ", { &abDev3.err.send, &abDev3.err.receive }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} },
#endif
#ifdef _NARABOTKA
         { "Наработка-ч,м ", { &NARAB.hou     , &NARAB.min  },{ 1             , 1              },{ "ч, " ,"m"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,2,0,1)} },
         { "Наработка-м,c ", { &NARAB.min     , &NARAB.sec  },{ 1             , 1              },{ "m, " ,"c"  }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,3,0,1),_form(1,3,0,1)} },
         { "Наработка-ч,п ", { &NARAB.hou     , &NARAB.ovr  },{ 1             , 1              },{ "ч, " ,"ед" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_form(1,5,0,2),_form(1,3,0,1)} },
#endif
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

//---
const struct IndUzm Indicat[]=
{
    {"Регулир.   " ,sizeof(ind_reg )/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_reg [0] },
#ifdef _A6_Obj_Ind
    {"Объект.упр." ,sizeof(ind_obj )/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_obj [0] },
#endif
    {"Служебныe  " ,sizeof(ind_serv)/sizeof(struct Ind) ,(_x_far const struct Ind*)&ind_serv[0] }
#ifdef  _INTERPRETER
   ,{"Объект.прг " ,sizeof(Ind_Obj_Prg)/sizeof(struct Ind_obj ) ,(_x_far const struct Ind*)(&Ind_Obj_Prg[0]) }
#endif
};

const word _NumInd = sizeof( Indicat )/sizeof(struct IndUzm) ;

//-------- Таблица параметров для вывода на ЦАПы ---------

_x_far const struct DAC_output_tab2 DAC_tab2  [ ] =                //
  {                                                                //
    { "L         ",  &S.Alfa_Old   , (w)(0.027* 256.)          },  // 0
    { "N#        ",  &Z_Skor       , (w)(0.12 * 256.)          },  // 1
    { "N#R       ",  &ZISkor       , (w)(0.12 * 256.)          },  // 2
    { "N         ",  &Skor         , (w)(0.12 * 256.)          },  // 3
    { "I-ogran   ",  &ZIDN         , (  1.00 * 256./_K_diskr ) },  // 4
    { "Id        ",  &Id_dop_kod   , (  1.00 * 256./_K_diskr ) },  // 5
    { "Id-flt    ",  &Id_flt.out   , (  1.00 * 256./_K_diskr ) },  // 6
    { "cAo0      ",  &canr.Ao[0]   , (  1.00 * 256. )          },  // 7
    { "cAo1      ",  &canr.Ao[1]   , (  1.00 * 256. )          },  // 8
    { "cAi0      ",  &canr.Ai[0]   , (  1.00 * 256. )          },  // 9
    { "cAi1      ",  &canr.Ai[1]   , (  1.00 * 256. )          },  //10
    { "cAi2      ",  &canr.Ai[2]   , (  1.00 * 256. )          },  //11
    { "cAi3      ",  &canr.Ai[3]   , (  1.00 * 256. )          },  //12
    { "cAi4      ",  &canr.Ai[4]   , (  1.00 * 256. )          },  //13
    #ifdef _AD_Obj_DAC
      _AD_Obj_DAC ,
    #endif
       //  переменную "Тест" следует держать всегда в конце списка,
       // т.к. она используется для теста ЦАПов и не должна выводиться.
    { "Test      ",  &T_DAC       , (  1.0*256     ) }
  } ;
const word  _DAC_Ntab2 = sizeof(DAC_tab2) / sizeof(struct DAC_output_tab2) ;

//-------------------------------------------------

const struct Stout Nstout [] = {
                                 #ifdef  _Po0_
                                   { "Po0   ", &Po0_c.all   ,  20 }
                                 #endif
                                 #ifdef  _AsPo0_
                                  ,{ "AsPo0 ", &PoS_c[0].all,  20 }
                                 #endif
                                 #ifdef  _AsPo1_
                                  ,{ "AsPo1 ", &PoS_c[1].all,  20 }
                                 #endif
                                 #ifdef  _AsPo2_
                                  ,{ "AsPo2 ", &PoS_c[2].all,  20 }
                                 #endif
                                 #ifdef  _AsPo3_
                                  ,{ "AsPo3 ", &PoS_c[3].all,  20 }
                                 #endif
                                 #ifdef  _AsPo4_
                                  ,{ "AsPo4 ", &PoS_c[4].all,  20 }
                                 #endif
                                 #ifdef  _AsPo5_
                                  ,{ "AsPo5 ", &PoS_c[5].all,  20 }
                                 #endif
                                 #ifdef  _AsPo6_
                                  ,{ "AsPo6 ", &PoS_c[6].all,  20 }
                                 #endif
                                 #ifdef  _AsPo7_
                                  ,{ "AsPo7 ", &PoS_c[7].all,  20 }
                                 #endif
                                 #ifdef  _Q1V_
                                  ,{ "Q1V   ", (b*)0        ,  40 }
                                 #endif
                                 #ifdef  _Q2V_
                                  ,{ "Q2V   ", (b*)0        ,  60 }
                                 #endif
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
   { "СИФУ       \r", _Grad(0.0)     , _Grad(179.0)   , _Grad(1.0) , _Grad(1.00)     }, //_Grad(0.05)     }
   { "РC         \r", _Skor_nom(-1.1), _Skor_nom(+1.1), _Skor_Nom  , _Skor_nom(0.01) }
  } ;
const word _Nck  = sizeof(Nckl)/sizeof(const struct Ck) ;

//-------------------------------------------------

_x_far const struct Vybor Vyb [] = { // Порядок и кол-во меток в F2_DRV.C :
                                 { "\rСИФУ-Рез-М1    ",  3 },//k10 },
                               //{ "\rСИФУ-Рез-М2    ",  4 },//k11 },

                               //{ "\rРТ-Рез-М1      ",  5 },//k12 },
                               //{ "\rРТ-Рез-М2      ",  6 },//k13 },
#ifdef   _NARABOTKA
                                 { "\rОбнул.наработки",  33},//k67 },
#endif
                                 { "\rЦиклы Задания  ", 11 },//k30 },

                                 { "\rШтатный режим  ", 10 },//k17 }
                                 { "\rФазировка Моста", 48 } //k96 для фазировки моста в "Наладке" 18.05.2020
                               } ;
const word _Nvyb =  sizeof(Vyb)/sizeof(const struct Vybor) ;
//----------------------------------------

_x_far const struct NCx NC [] = {
                                   { "A0-Сообщ/Индиk", _Case ( 'A' , '0' ) },
                                   { "A1-Сообщения. ", _Case ( 'A' , '1' ) },
                                   { "A7-Ред.Устав. ", _Case ( 'A' , '7' ) },
                                   { "A8-Ред.БитУст.", _Case ( 'A' , '8' ) },
                                   { "AE-Сохр.Устав.", _Case ( 'A' , 'E' ) },
                                   { "A6-Индикация. ", _Case ( 'A' , '6' ) },
#ifdef _CombRedact
                                   { "F1-Комб.Редак.", _Case ( 'F' , '1' ) },
#endif
                                   { "F2-Наладка.   ", _Case ( 'F' , '2' ) },
                                 //{ "A5-Фазир.Мостa", _Case ( 'A' , '5' ) }, // 18.05.2020
                                   { "FA-Останов.   ", _Case ( 'F' , 'A' ) },
                                   { "A4-Тест АЦП.  ", _Case ( 'A' , '4' ) },
                                   { "A9-Тест ЦАП.  ", _Case ( 'A' , '9' ) },
                                   { "AA-Тест Двх.  ", _Case ( 'A' , 'A' ) },
                                   { "AB-Тест Двых. ", _Case ( 'A' , 'B' ) },
                                   { "F-Монитор.    ", _Case ( 'F' ,  0  ), 9 },
                                   { "F0-НастРегистp", _Case ( 'F' , '0' ) },
#ifdef _Sld_cond
                                   { "FC-Усл.Регистp", _Case ( 'F' , 'C')  },
#endif
                                 //{ "F1-След.      ", _Case ( 'F' , '1' ) },
#ifdef _JOURNAL
                                   { "AC-Настр.Журн.", _Case ( 'A' , 'C' ) },
                                   { "FB-Журнал     ", _Case ( 'F' , 'B' ) },
#endif
#ifdef  _TEST_RAM_INCLUDE
                                   { "F3-Тест ОЗУ.  ", _Case ( 'F' , '3' ) },
#endif
                                   { "F4-Тест ЭОЗУ. ", _Case ( 'F' , '4' ), 9 },// для невидимости.
                                   { "F5-Восст.Авар.", _Case ( 'F' , '5' ) },
                                   { "F6-Часы.      ", _Case ( 'F' , '6')  },
                                   { "F7-Наст.Часов.", _Case ( 'F' , '7')  },
                                   { "AD-Вывод ЦАП. ", _Case ( 'A' , 'D' ) },
                                   { "F8-О системе. ", _Case ( 'F' , '8' ) },
                                   { "F9-Восст.Устав", _Case ( 'F' , '9' ) },
                                   { "Link          ", _Case ( 'I' ,  0  ), 9 },// для невидимости.
#ifndef _CM3_
                                   { "J-RW_I2C      ", _Case ( 'J' ,  0  ), 9 },// для невидимости.
#endif
                                   { "AF-Пароль     ", _Case ( 'A' , 'F' ) },
#ifdef _NET_IRQ
//09.06.2020 13:17                 { "FD-Тест DP.   ", _Case ( 'F' , 'D' ) },
                                   { "B6-Сеть:Индик.", _Case ( 'B' , '6' ) },
                                   { "B7-Сеть:Устав.", _Case ( 'B' , '7' ) },
                                   { "B8-Сеть:БитУс.", _Case ( 'B' , '8' ) },
#endif
                                   { "FE-Скор.пультa", _Case ( 'F' , 'E' ) }
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
