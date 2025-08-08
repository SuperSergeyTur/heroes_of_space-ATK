
#ifndef _var_mtab_h
#define _var_mtab_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

#define _MaxAbonTabSize  2

        //  таблица-перечень абонентов.
struct Abonent_tab_form
{
  byte size_tab ;    //  количество заполненных элементов таблицы.
  struct Abonent_form  *tab [_MaxAbonTabSize] ;
} ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _FLASH_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

//*****************   CAN1   *************************************************************************************
// Первый абонент - плата управления сетевым выпрямителем


// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev1[] =
 {
  // _READ_WRITE_access ( таблица , которую ему пишет Master )
  { "cStsRV",  &canr.StatReg.all },
  { "N_Rot",   &Skor_Pusk  }
 } ;

#define Nt_abDev1 sizeof( c_t_abDev1 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev1[Nt_abDev1] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev1 =
  {
    "Dev1",
    _CAN1_Port, //  номер порта абонента.
    2,  //  адрес абонента в сети.
    { _AbCfg_Master },  //  тип абонента мастер/slave, _AbCfg_Master.
    Nt_abDev1,   //  кол-во переменных в списке абонента.
    t_abDev1   //  список переменных абонента.
  } ;
struct Abonent_form  abDev1 ;
//*****************************************
//*****************   CAN0   *************************************************************************************
//Первый абонент - плата сетевого инвертора другого ШУ АТК .
// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev21[] =
 {
   { "ePos"  , &EncoderGray      }
   //{ "T05"  , &EncoderGray      }//,
   //vmz 09122014 Все равно не используется
   //{ "cStsR" , &canr.StatReg.all },
   //{ "cCfgR" , &canr.CfgReg2     }  // canr.CfgReg.all
 } ;

#define Nt_abDev21 sizeof( c_t_abDev21 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev21[Nt_abDev21] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev21 =
  {
    "Atk1",
    _CAN0_Port, //  номер порта абонента.
    2,  //  адрес абонента в сети.
    { 0 },  //  тип абонента мастер/slave, _AbCfg_Master.
    Nt_abDev21,   //  кол-во переменных в списке абонента.
    t_abDev21   //  список переменных абонента.
  } ;
struct Abonent_form  abDev21 ;

/****************************************************
 Список всех абонентов
****************************************************/

        //  таблица-перечень абонентов.
struct Abonent_tab_form ab_tab =
{
      //  количество заполненных элементов таблицы.
  2,
      //  таблица-перечень.
  { &abDev1, &abDev21 }
} ;




//   Список всех открытых таблиц абонентов для их
//   систематизированной инициализации.

const struct  Abon_Init  tab_ab[] =
{
  { &abDev1,  &c_abDev1,  &c_t_abDev1[0] },
  { &abDev21, &c_abDev21, &c_t_abDev21[0] }
};

const byte size_tab_ab =  sizeof(tab_ab) / sizeof(struct  Abon_Init) ;

//****************************************************

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else

extern const struct namevar c_t_abDev1[];
extern struct namevar t_abDev1[] ;
extern struct Abonent_form  c_abDev1;
extern struct Abonent_form  abDev1;

extern struct Abonent_tab_form ab_tab;
extern const struct  Abon_Init  tab_ab[];
extern const byte size_tab_ab;

#endif
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
