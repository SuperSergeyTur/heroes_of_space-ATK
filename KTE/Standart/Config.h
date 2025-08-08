#ifndef _config_h
#define _config_h

/*----------- Конфиг1 --------------*/

     //  Конфигурирование наличия внешних и внутрених устройств и режимов.
 union Config {
  word all ;
  struct  {
#ifndef _Union_FR
      word Control_ZSk : 1 ;  // Наличие контроля Отсутствия Задания
      word MT          : 1 ;  // Наличие в схеме "Механического Тормоза"
      word RT_Anastr   : 1 ;  // Коэффициенты РТ вычисляются посредством АН
      word Ostanov     : 1 ;  // Наличие режима "Останов" (снятие импульсов
                              // для устранения ползучки при малых заданиях на скорость).
      word Kontaktor   : 1 ;  // Наличие в схеме "Контактора".
      word Dve_Zony    : 1 ;  // Включение Рег. ЭДС для Двухзонного регу-ия
      word Iv_Econom   : 1 ;  // Включает программу "стояночного" эконом-тока возбуждения.
      word Obj_prg     : 1 ;  // Включает объектную программу.
     //--------
      word Ne_Revers   : 1 ;  // Нереверсивный агрегат ( на главном СИФУ нет Моста Назад )
      word CAN_QK      : 1 ;  // Включение ЛК по сетевому интерфейсу
      word Vrasch_Dvig : 1 ;  // Включение на вращающийся двигатель .
      word Fzapoln     : 1 ;  // Частотное заполнение ИУ главного СИФУ .

      word CAN_reg     : 1 ;  // Включает CAN-управл.
      word Shtat_reg   : 1 ;  // Штатное управл.
      word DZV         : 1 ;  // Реверс по ДЗВ.
      word RN          : 1 ;  // Включает регулятор напряжения возбуждения.
#else
      word RN          : 1 ;
      word DZV         : 1 ;
      word Shtat_reg   : 1 ;
      word CAN_reg     : 1 ;

      word Fzapoln     : 1 ;
      word Vrasch_Dvig : 1 ;
      word CAN_QK      : 1 ;
      word Ne_Revers   : 1 ;
     //--------
      word Obj_prg     : 1 ;
      word Iv_Econom   : 1 ;
      word Dve_Zony    : 1 ;
      word Kontaktor   : 1 ;

      word Ostanov     : 1 ;
      word RT_Anastr   : 1 ;
      word MT          : 1 ;
      word Control_ZSk : 1 ;
#endif
    } _ ;
} ;

#define   _cfg_Control_ZSk  ((w) 0x0001 )
#define   _cfg_MT           ((w) 0x0002 )
#define   _cfg_RT_Anastr    ((w) 0x0004 )
#define   _cfg_Ostanov      ((w) 0x0008 )

#define   _cfg_Kontaktor    ((w) 0x0010 )
#define   _cfg_Dve_Zony     ((w) 0x0020 )
#define   _cfg_Iv_Econom    ((w) 0x0040 )
#define   _cfg_Obj_prg      ((w) 0x0080 )

#define   _cfg_Ne_Revers    ((w) 0x0100 )
#define   _cfg_CAN_QK       ((w) 0x0200 )
#define   _cfg_Vrasch_Dvig  ((w) 0x0400 )
#define   _cfg_Fzapoln      ((w) 0x0800 )

#define   _cfg_CAN_reg      ((w) 0x1000 )
#define   _cfg_Shtat_reg    ((w) 0x2000 )
#define   _cfg_DZV          ((w) 0x4000 )
#define   _cfg_RN           ((w) 0x8000 )

/*----------- Конфиг2 --------------*/

     //  Конфигурирование наличия внешних и внутрених устройств и режимов.
 union Config2 {
  word all ;
  struct  {
//-----
#ifndef _Union_FR
//-----
      word RRS           : 1 ;  // Регулятор рассогласования скорости "ЛЫЖА"
      word RDN           : 1 ;  // Вкл. Регулятор Деления Нагрузки Id 2-х якорей
      word Iv_Econom2    : 1 ;  // KTE5-AC/MC - включает эконом режим при отсутствии задания .
      word Rev_Pola      : 1 ;  // Вкл. алгоритма реверса поля вместо реверса якоря .

      word FreezeIntRTg  : 1 ;  // ГД : Перед реверсом , если Мост и Out_rn разных знаков , не даем нарастать интегратору .
      word Revers_Ugz    : 1 ;  // ГД : Реверс по Ug# .
      word One_RNg       : 1 ;  // ГД : Структура регулирования : РНг -> СИФУ .
      word MT_Podyom     : 1 ;  // Агоритм управления МТ для подъёмных механизмов

      word RDN_Decrease  : 1 ;  // Вкл. Регулятора Деления Нагрузки Id 2-х якорей только НА УМЕНЬШЕНИЕ .
      word DZV_Predupr   : 1 ;  // вывод предупреждений по отсуствию одного из двух сигналов ДЗВ при реверсе .
      word FzapolnV      : 1 ;  // Частотное заполнение ИУ второго СИФУ (возб-ля) .
      word SIFU_Syn2     : 1 ;  // Наличие Автофазировки Моста от Силового напряжения .

      word WatchdogEn    : 1 ;  // Включение Watchdog
      word rezerv13      : 1 ;
      word ProboyTir     : 1 ;  // Контроль пробоя тиристора .
      word VR1           : 1 ;  // Наличие/отсутствие (1/0) сигнала 1VR
//-----
#else
//-----
      word VR1           : 1 ;
      word ProboyTir     : 1 ;
      word rezerv13      : 1 ;
      word WatchdogEn    : 1 ;

      word SIFU_Syn2     : 1 ;
      word FzapolnV      : 1 ;
      word DZV_Predupr   : 1 ;
      word RDN_Decrease  : 1 ;

      word MT_Podyom     : 1 ;
      word One_RNg       : 1 ;
      word Revers_Ugz    : 1 ;
      word FreezeIntRTg  : 1 ;

      word Rev_Pola      : 1 ;
      word Iv_Econom2    : 1 ;
      word RDN           : 1 ;
      word RRS           : 1 ;
//-----
#endif
//-----
    } _ ;
} ;

#define   _cfg2_RRS          ((w) 0x0001 )
#define   _cfg2_RDN          ((w) 0x0002 )
#define   _cfg2_Iv_Econom2   ((w) 0x0004 )
#define   _cfg2_Rev_Pola     ((w) 0x0008 )

#define   _cfg2_FreezeIntRTg ((w) 0x0010 )
#define   _cfg2_Revers_Ugz   ((w) 0x0020 )
#define   _cfg2_One_RNg      ((w) 0x0040 )
#define   _cfg2_MT_Podyom    ((w) 0x0080 )

#define   _cfg2_RDN_Decrease ((w) 0x0100 )
#define   _cfg2_DZV_Predupr  ((w) 0x0200 )
#define   _cfg2_FzapolnV     ((w) 0x0400 )
#define   _cfg2_SIFU_Syn2    ((w) 0x0800 )

#define   _cfg2_WatchdogEn   ((w) 0x1000 )
//#define _cfg2_             ((w) 0x2000 )
#define   _cfg2_ProboyTir    ((w) 0x4000 )
#define   _cfg2_1VR          ((w) 0x8000 )
// Конфигурация RVId
union ConfigRVId
{
    word all;
    struct
    {
        word RVId_Vkl : 1;  // подключение выхода RVId
        word GL1_RVId : 1;  // подключение задания на GL1 к RVId
        word GL2_RVId : 1;  // подключение задания на GL2 к RVId
        word rezerv   : 13;
    } _ ;
};

#define   _cfgRVId_Vkl       ((w) 0x0001 )
#define   _cfgRVId_GL1       ((w) 0x0002 )
#define   _cfgRVId_GL2       ((w) 0x0004 )

/*-----------   Структура программы --------------*/

 union Prog {
              word all ;
              struct {
#ifndef  _Union_FR
                  word  ZadSkor    : 1; // Вкл. модуль Формирования Задания на Скорость.
                  word  RegSk      : 1; // Вкл. Регулятор Скорости.
                  word  RegTok     : 1; // Вкл. Регулятор Тока.
                  word  Cikl       : 1; // Вкл. Циклы Задания.

                  word  Blok_upr   : 1;
                  word  Sled       : 1; // Вкл. След.
                  word  Gotovn     : 1; // Перекл. режим "Сборка Готовности"/"Работа".
                  word  RN         : 1; // Вкл. Регулятора Напряжения

                  word  RP         : 1; // Вкл. Регулятора Положения
#else
                  word             : 7;
                  word  RP         : 1; // Вкл. Регулятора Положения

                  word  RN         : 1; // Вкл. Регулятора Напряжения
                  word  Gotovn     : 1; // Перекл. режим "Сборка Готовности"/"Работа".
                  word  Sled       : 1; // Вкл. След.
                  word  Blok_upr   : 1;

                  word  Cikl       : 1; // Вкл. Циклы Задания.
                  word  RegTok     : 1; // Вкл. Регулятор Тока.
                  word  RegSk      : 1; // Вкл. Регулятор Скорости.
                  word  ZadSkor    : 1; // Вкл. модуль Формирования Задания на Скорость.
#endif
                } _ ;
            } ;


#define   _ZadSkor      ((w) 0x0001 )
#define   _RegSk        ((w) 0x0002 )
#define   _RegTok       ((w) 0x0004 )
#define   _Cikl         ((w) 0x0008 )

#define   _Blok_upr     ((w) 0x0010 )
#define   _Sled         ((w) 0x0020 )
#define   _Gotovn       ((w) 0x0040 )
#define   _RN           ((w) 0x0080 )

#define   _RP           ((w) 0x0100 )
//#define _             ((w) 0x0200 )
//#define _             ((w) 0x0400 )
//#define _             ((w) 0x0800 )

//#define _             ((w) 0x1000 )
//#define _             ((w) 0x2000 )
//#define _             ((w) 0x4000 )
//#define _             ((w) 0x8000 )

#define   _Prg_Gotovn  ( _ZadSkor /*21.02.06 15:51| _Sled*/ | _Gotovn )
          // 26.03.2010 - Включать РН не в ГД нельзя , тк тогда в режиме "РС-Останов" в SIFU.C вызывается РТ .
          // 23.03.2011 - В СИФУ исправлено , и по включенному РН в КТЭ входа в РТ не будет...
#define   _Prg_Rabota  ( _ZadSkor | _RegSk | _RegTok | _Sled | _RN | _RP )

/*------------ Флаги для п/п прерываний ----------*/

 struct InterruptSifu_Flags{

          word      NoAdBuffInfo: 1 ; // НЕ ЗАБЫТЬ ЕГО ВВЕСТИ!

          //word      BegImpSys  : 1 ; // Номер прерывания для п/п прерывания по якорным УИ.
        }   ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

 _register union Prog   Prg ;   //  Структура программы.

 _register struct InterruptSifu_Flags     Flg;

  word  Tckl, Tckl_time ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern _register union Prog   Prg;

extern _register struct InterruptSifu_Flags     Flg;

extern  word  Tckl, Tckl_time ;

/*------------------------------------------------*/
#endif
#endif

