
#ifndef _var_mtab_h
#define _var_mtab_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

#define _MaxAbonTabSize  3

        //  таблица-перечень абонентов.
struct Abonent_tab_form
{
  byte size_tab ;    //  количество заполненных элементов таблицы.
  struct Abonent_form  *tab [_MaxAbonTabSize] ;
} ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _FLASH_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev1[] =
 {
  // _READ_WRITE_access ( таблица , которую ему пишет Master )
  { "cCfgR",  &canr.StatReg.all },//2, _SHORT_type, 0, _READ_WRITE_access },
  { "cN#",     &ZISkor   }//,   // 2
 } ;
  //{ "cId#",    (w*)&timer1   }   // 2
  //{ "M_Nv_2",  &S.Most_Tir    } //,     1,_CHAR_type,    0,  _READ_access },

#define Nt_abDev1 sizeof( c_t_abDev1 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev1[Nt_abDev1] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev1 =
  {
    "Dev1",
    _CAN0_Port, //  номер порта абонента.
    2,  //  адрес абонента в сети.
    { _AbCfg_Master },  //  тип абонента мастер/slave, _AbCfg_Master.
    Nt_abDev1,   //  кол-во переменных в списке абонента.
    t_abDev1   //  список переменных абонента.
  } ;
struct Abonent_form  abDev1 ;
//*****************************************

 // Для второго абонента
// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev2[] =
 {
  // _READ_WRITE_access ( таблица , которую ему пишет Master )
  { "cCfgR",  &canr.StatReg.all },//2, _SHORT_type, 0, _READ_WRITE_access },
  { "cN#",     &ZISkor   }//,   // 2
 } ;
  //{ "cId#",    (w*)&timer1   }   // 2
  //{ "M_Nv_2",  &S.Most_Tir    } //,     1,_CHAR_type,    0,  _READ_access },

#define Nt_abDev2 sizeof( c_t_abDev2 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev2[Nt_abDev2] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev2 =
  {
    "Dev2",
    _CAN0_Port, //  номер порта абонента.
    3,  //  адрес абонента в сети.
    { _AbCfg_Master },  //  тип абонента мастер/slave, _AbCfg_Master.
    Nt_abDev2,   //  кол-во переменных в списке абонента.
    t_abDev2   //  список переменных абонента.
  } ;
struct Abonent_form  abDev2 ;
//*****************************************

 // Для третьего абонента
// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev3[] =
 {
  // _READ_WRITE_access ( таблица , которую ему пишет Master )
  { "cCfgR",  &canr.StatReg.all },//2, _SHORT_type, 0, _READ_WRITE_access },
  { "cN#",     &ZISkor   }//,   // 2
 } ;
  //{ "cId#",    (w*)&timer1   }   // 2
  //{ "M_Nv_2",  &S.Most_Tir    } //,     1,_CHAR_type,    0,  _READ_access },

#define Nt_abDev3 sizeof( c_t_abDev3 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev3[Nt_abDev3] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev3 =
  {
    "Dev3",
    _CAN0_Port, //  номер порта абонента.
    4,  //  адрес абонента в сети.
    { _AbCfg_Master },  //  тип абонента мастер/slave, _AbCfg_Master.
    Nt_abDev3,   //  кол-во переменных в списке абонента.
    t_abDev3   //  список переменных абонента.
  } ;
struct Abonent_form  abDev3 ;
//*****************************************


/****************************************************
 Список всех абонентов
****************************************************/

        //  таблица-перечень абонентов.
struct Abonent_tab_form ab_tab =
{
      //  количество заполненных элементов таблицы.
  3,
      //  таблица-перечень.
  { &abDev1, &abDev2, &abDev3 }
} ;


//   Список всех открытых таблиц абонентов для их
//   систематизированной инициализации.

const struct  Abon_Init  tab_ab[] =
{
  { &abDev1,  &c_abDev1,  &c_t_abDev1[0] },
  { &abDev2,  &c_abDev2,  &c_t_abDev2[0] },
  { &abDev3,  &c_abDev3,  &c_t_abDev3[0] }
};

const byte size_tab_ab =  sizeof(tab_ab) / sizeof(struct  Abon_Init) ;

//****************************************************

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else

extern const struct namevar c_t_abDev1[];
extern struct namevar t_abDev1[] ;
extern struct Abonent_form  c_abDev1;
extern struct Abonent_form  abDev1;

extern const struct namevar c_t_abDev2[];
extern struct namevar t_abDev2[] ;
extern struct Abonent_form  c_abDev2;
extern struct Abonent_form  abDev2;

extern const struct namevar c_t_abDev3[];
extern struct namevar t_abDev3[] ;
extern struct Abonent_form  c_abDev3;
extern struct Abonent_form  abDev3;

extern struct Abonent_tab_form ab_tab;
extern const struct  Abon_Init  tab_ab[];
extern const byte size_tab_ab;

#endif
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
