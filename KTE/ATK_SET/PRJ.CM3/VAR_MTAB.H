
#ifndef _var_mtab_h
#define _var_mtab_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

//vmz 122014
//#define _MaxAbonTabSize  1
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
// Первый абонент - плата управления роторным выпрямителем


// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev1[] =
{
  { "cStsR",  &canr.StatReg2.all              },  //0
  { "MsgA"  , &Ap2_Msg.avar                   },  //1
  { "MsgP"  , &Ap2_Msg.predupr                },  //2
  { "MsgS"  , &Ap2_Msg.service                },  //3
  { "MsgA2" , &Ap2_Msg.avar2                  },  //4
  { "MsgP2" , &Ap2_Msg.predupr2               },  //5
  { "MsgS2" , &Ap2_Msg.service2               },  //6
  { "N_Rot",  &Nrot_CAN                       },  //7
  { "cStsRI", &canr.StatReg1.all              },  //8
  { "cCfgR",  &canr.CfgRegAp2.all             },  //9
  { "cId#"  , &OuRegS_dop_kod                 },  //a 
  { "N_PDF",  &SkorPDF                        }   //b &PDF[0].out_m } 27.05.2021 - Задание на входе РС всегда положительное , и скорость
} ;                                               //вкл/выкл КЗ также положительная , т.о. передаём в АР2 сигнал ПДФ с учетом направления
                                                  //реверсора , так , чтобы видеть противоходы ( а не просто чистый модуль ) .
#define Nt_abDev1 sizeof( c_t_abDev1 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev1[Nt_abDev1] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev1 =
  {
    "Dev1",
    _CAN1_Port, //  номер порта абонента.
    2,  //  адрес абонента в сети.
    { 0 },  //  тип абонента мастер/slave, _AbCfg_Master.
    Nt_abDev1,   //  кол-во переменных в списке абонента.
    t_abDev1   //  список переменных абонента.
  } ;
struct Abonent_form  abDev1 ;
//*****************************************

//*****************   CAN0   *************************************************************************************
//Первый абонент - плата сетевого инвертора другого ШУ АТК .
// 1. Константная табл. переменных для инициализации.
//const struct namevar c_t_abDev21[] =
// {
//   { "cSts2"  , &canr.StatReg4.all  },
//   { "Idatk"  , &OuRegS_ogr         }
// } ;

//*****************   CAN0   *************************************************************************************
//Первый абонент - ША .
// 1. Константная табл. переменных для инициализации.
const struct namevar c_t_abDev21[] =
 {
    { "cStsSA", &canr.StatReg.all    }, //(w) 0 статус ШУ АР1
    { "Id",     &Irot                }, //(w) 1  ток ротора
    { "N",      &Skor                }, //(w) 2  скорость
    { "Ud",     &UdSr                }, //(w) 3  напряжение ротора
    { "E",      &EDS_dop_kod         }, //(w) 4  ЭДС
    { "AsPi0",  &PiS_f[0].all        }, //(b) 5
    { "AsPi1",  &PiS_f[1].all        }, //(b) 6
    { "AsPi2",  &PiS_f[2].all        }  //(b) 7
 } ;


#define Nt_abDev21 sizeof( c_t_abDev21 )/sizeof( struct namevar)

// 2. Рабочая табл. переменных в ОЗУ для данного абонента.
struct namevar t_abDev21[Nt_abDev21] ;

//  3. Структура описывающая одного абонента.
struct Abonent_form  c_abDev21 =
  {
    "SA",
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

//vmz 122014
extern const struct namevar c_t_abDev21[];
extern struct namevar t_abDev21[] ;
extern struct Abonent_form  c_abDev21;
extern struct Abonent_form  abDev21;

extern struct Abonent_tab_form ab_tab;
extern const struct  Abon_Init  tab_ab[];
extern const byte size_tab_ab;

#endif
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
