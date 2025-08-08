#ifndef _zad_skor_h
#define _zad_skor_h

#define   _Porog_ss     (w)_MkSec( 55.0 )

  // Структура для конфигурирования модуля формирования задания на скорость
           // Создание объединения для возможности обращения сразу ко всем разрядам.
  union ZadSkor_u  {
        word     all ;
        struct {
           #ifndef _Union_FR
                 word BolsheMenshe : 1 ;  //  Вкл. режим "больше-меньше" - как дополн. к базовому заданию.
                 word Analog       : 1 ;  //  Вкл. режим базового "аналогового" задания.
                 word Selsin       : 1 ;  //  Вкл. режим базового "сельсинового" задания.
                 word CAN_Z        : 1 ;
           #else
                 word rezerv       : 12;

                 word CAN_Z        : 1 ;
                 word Selsin       : 1 ;  //  Вкл. режим базового "сельсинового" задания.
                 word Analog       : 1 ;  //  Вкл. режим базового "аналогового" задания.
                 word BolsheMenshe : 1 ;  //  Вкл. режим "больше-меньше" - как дополн. к базовому заданию.
           #endif
               } _ ;
            } ;

#define   _zs_BolsheMenshe   ((w) 0x0001 )
#define   _zs_Analog         ((w) 0x0002 )
#define   _zs_Selsin         ((w) 0x0004 )
#define   _zs_CAN_Z          ((w) 0x0008 )

  // Структура для конфигурирования обратной связи по скорости
           // Создание объединения для возможности обращения сразу ко всем разрядам.
  union    Skor_u  {
        word     all ;
        struct {
           #ifndef _Union_FR
                 word EDS        : 1 ;
                 word TG         : 1 ;
                 word PDF        : 1 ;
                 word EDS_Appar  : 1 ;

                 word DatEDS     : 1 ; // Откл./Вкл. программный Датчик ЭДС .
                 word FiltrEds   : 1 ;
                 word Sk_filtr   : 1 ; //  Вкл. режим фильтрации скорости.
                 word EdsIIzona  : 1 ;

                 word KompUd_12p : 1 ;
                 word EncodInv   : 1 ;
           #else
                 word rezerv     : 7 ;
                 word KompUd_12p : 1 ;

                 word EdsIIzona  : 1 ;
                 word Sk_filtr   : 1 ;
                 word FiltrEds   : 1 ;
                 word DatEDS     : 1 ;

                 word EDS_Appar  : 1 ;
                 word PDF        : 1 ;
                 word TG         : 1 ;
                 word EDS        : 1 ;
           #endif
               } _ ;
            } ;

#define   _sk_EDS        ((w) 0x0001 )
#define   _sk_TG         ((w) 0x0002 )
#define   _sk_PDF        ((w) 0x0004 )
#define   _sk_EDS_Appar  ((w) 0x0008 )

#define   _sk_DatEDS     ((w) 0x0010 )
#define   _sk_FiltrEds   ((w) 0x0020 )
#define   _sk_filtr      ((w) 0x0040 )
#define   _sk_EdsIIzona  ((w) 0x0080 )

#define   _sk_KompUd_12p ((w) 0x0100 )
#define   _sk_EncodInv   ((w) 0x0200 )

/*-----------   Управляющие биты для программ испытаний. --------------*/

 union Ispytan {
              word all ;
              struct {
           #ifndef _Union_FR
                        word  SIFU_Res   : 1;
                        word  Samonastr  : 1;
                        word  RT_Res     : 1;
                        word  RN_Res     : 1;

                        word  Cikl       : 1;
                        word  Predupr    : 1;
                        word  NumMost    : 1;
                        word  Oprobov    : 1;

                        word  SIFUV_Res  : 1;
                        word  AvtoNastr  : 1;
                        word  ZIRT_shunt : 1;
                        word  ZIRS_shunt : 1;

                        word  RT1_Res    : 1;
                        word  RT2_Res    : 1;
           #else
                        word  rezerv     : 2;
                        word  RT2_Res    : 1;
                        word  RT1_Res    : 1;

                        word  ZIRS_shunt : 1;
                        word  ZIRT_shunt : 1;
                        word  AvtoNastr  : 1;
                        word  SIFUV_Res  : 1;

                        word  Oprobov    : 1;
                        word  NumMost    : 1;
                        word  Predupr    : 1;
                        word  Cikl       : 1;

                        word  RN_Res     : 1;
                        word  RT_Res     : 1;
                        word  Samonastr  : 1;
                        word  SIFU_Res   : 1;
           #endif
                      } _ ;
            } ;

#define   _ZI_shunt   ((w) 0x0C00 ) // Маска для шунтирования ЗИ - РТ+РС .

 //-------------------------------------------

 union Trigger {
              byte all ;
              struct {
                        word  TB         : 1 ;
                        word  TH         : 1 ;
                        byte  rezerv     : 6 ;
                      } _ ;
            } ;

/*------------------------------------------------*/
#ifdef   _MAIN_INCLUDE
/*------------------------------------------------*/

union  Ispytan     Isp ;
union  Trigger     trig ;
struct Izm_analog  Z_sk ;

        word      ZSkA ;          // Аналоговое задание на скорость - '+/-' в дополнительном коде
        word      ZSkBM ;         // Добавка к базовому заданию от сигналов "больше - меньше"   - '+/-' в дополнительном коде
        word      ZSkT ;          // Задание в режиме "Толчки"  - '+/-' в дополнительном коде
        word      ZSk_Shtat ;
        word      Nzad , Nzad_4_20 ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union  Ispytan     Isp ;
extern union  Trigger     trig ;
extern struct Izm_analog  Z_sk ;

extern  word      ZSkA ;
extern  word      ZSkBM ;
extern  word      ZSkT ;
extern  word      ZSk_Shtat ;
extern  word      Nzad , Nzad_4_20 ;

/*------------------------------------------------*/
#endif
#endif
