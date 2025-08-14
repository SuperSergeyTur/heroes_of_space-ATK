#ifndef _obj_h
#define _obj_h

//Переменые для определения размера областей уставок
#define  _kol_obl    ( 1 ) // Количество областей уставок
extern   word  read_rezerv( void ) ;

             // отключаемся от CAN при перезагрузке уставок.
#define can_obj_stop()  can_stop( _CAN0_Port ) = 1
             // подключается к CAN после перезагрузки уставок.
#define can_obj_start()  can_stop( _CAN0_Port ) = 0

//-------Температура силового шкафа--------
typedef union {
  word all;
  struct{
    word  BK1   :1;
    word  BK2   :1;
    word  BK3   :1;
    word  BK4   :1;

    word  BK5   :1;
    word  BK6   :1;
    word  BK7   :1;
    word  BK8   :1;

    word  BK9   :1;
    word  BK10  :1;
    word  BK11  :1;
    word  BK12  :1;

    word  BK13  :1;
    word  BK14  :1;
    word  BK15  :1;
    word  BK16  :1;
  }_;
} Av_DT;

typedef struct
{
  float  Freq;       //!< Частота в кГц
  float  V_Out;      //!< Измеренное напряжение
  float  Out;        //!< Температура в градусах
  sword  I_Out;      //!< Температура в градусах в целочисленном формате 1 гр - 10 дискрет
} IzmTemp_Data;

#define   Set_CS_Temp(num)     LPC_GPIO3->SET = ((lw)num<<24)
#define   CLR_CS_Temp()      LPC_GPIO3->CLR = (0xfUL<<24)
//Номера каналов измерения для задания последовательности
#define   _Ch_Ishs1        0
#define   _Ch_BK1_S1       1
#define   _Ch_BK2_S1       2
#define   _Ch_BK3_S1       3
#define   _Ch_BK4_S1       4
#define   _Ch_BK5_S1       5
#define   _Ch_BK6_S1       6
#define   _Ch_Ishs2        7
#define   _Ch_BK1_S2       8
#define   _Ch_BK2_S2       9
#define   _Ch_BK3_S2       10
#define   _Ch_BK4_S2       11
#define   _Ch_BK5_S2       12
#define   _Ch_BK6_S2       13
//Адреса каналов, соответствующие номеру в последовательности
#define   _Ch_Addr_Ishs1        0
#define   _Ch_Addr_BK1_S1       1
#define   _Ch_Addr_BK2_S1       2
#define   _Ch_Addr_BK3_S1       3
#define   _Ch_Addr_BK4_S1       4
#define   _Ch_Addr_BK5_S1       5
#define   _Ch_Addr_BK6_S1       6
#define   _Ch_Addr_Ishs2        8
#define   _Ch_Addr_BK1_S2       9
#define   _Ch_Addr_BK2_S2       10
#define   _Ch_Addr_BK3_S2       11
#define   _Ch_Addr_BK4_S2       12
#define   _Ch_Addr_BK5_S2       13
#define   _Ch_Addr_BK6_S2       14

#define   _Ch_Ishs1msk        0x2000 //8000
#define   _Ch_BK1_S1msk       0x1000 //4000
#define   _Ch_BK2_S1msk       0x0800 //2000
#define   _Ch_BK3_S1msk       0x0400 //1000
#define   _Ch_BK4_S1msk       0x0200 //0800
#define   _Ch_BK5_S1msk       0x0100 //0400
#define   _Ch_BK6_S1msk       0x0080 //0200
#define   _Ch_Ishs2msk        0x0040 //0100
#define   _Ch_BK1_S2msk       0x0020 //0080
#define   _Ch_BK2_S2msk       0x0010 //0040
#define   _Ch_BK3_S2msk       0x0008 //0020
#define   _Ch_BK4_S2msk       0x0004 //0010
#define   _Ch_BK5_S2msk       0x0002 //0008
#define   _Ch_BK6_S2msk       0x0001 //0004


#define _Msk_Temp_Msg     (_Pr2_Tizm1 | _Pr2_Tizm2 | _Pr2_Tizm3 | _Pr2_Tizm4 | _Pr2_Tizm5 | _Pr2_Tizm6 | _Pr2_Tizm7 | _Pr2_Tizm8 | _Pr2_Tizm9 | _Pr2_Tizm10 | _Pr2_Tizm11 | _Pr2_Tizm12 | _Pr2_Tizm13 | _Pr2_Tizm14 )
const word Izm_seq[] =
{
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK1_S1,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK2_S1,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK3_S1,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK4_S1,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK5_S1,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK6_S1,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK1_S2,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK2_S2,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK3_S2,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK4_S2,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK5_S2,
  _Ch_Ishs1,_Ch_Ishs2,
  _Ch_BK6_S2
};
const word Izm_Seq_max = sizeof(Izm_seq)/sizeof(word);

#define _Dat_Temp_All 12         // 12 каналов для темпертуры
#define _MaxChannel 14            // Всего каналов в плате - для буффера.
#define _SrvDT_Mask   0xfff      //0xffff    // ?????????

const word DT_Chanells[][ _Dat_Temp_All/2] =
{
  {
    _Ch_BK1_S1,
    _Ch_BK2_S1,
    _Ch_BK3_S1,
    _Ch_BK4_S1,
    _Ch_BK5_S1,
    _Ch_BK6_S1
  },
  {
    _Ch_BK1_S2,
    _Ch_BK2_S2,
    _Ch_BK3_S2,
    _Ch_BK4_S2,
    _Ch_BK5_S2,
    _Ch_BK6_S2
  }
};
const word Addr_izmChanell[] =
{
  _Ch_Addr_Ishs1 ,
  _Ch_Addr_BK1_S1,
  _Ch_Addr_BK2_S1,
  _Ch_Addr_BK3_S1,
  _Ch_Addr_BK4_S1,
  _Ch_Addr_BK5_S1,
  _Ch_Addr_BK6_S1,
  _Ch_Addr_Ishs2 ,
  _Ch_Addr_BK1_S2,
  _Ch_Addr_BK2_S2,
  _Ch_Addr_BK3_S2,
  _Ch_Addr_BK4_S2,
  _Ch_Addr_BK5_S2,
  _Ch_Addr_BK6_S2
 };
#ifdef  _OBJ_INCLUDE
         byte   Num_obl ;
         //Из-за того, что при записи (или перезагрузке)
         //уставок "Num_obl" обнуляется (как оказалось),
         //для многорезервных агрегатов вводится переменная "Name_Agr",
         //на которую должна опираться объектная часть при исполнении кода
         //многорезервных агрегатов. Значение "Name_Agr" соответствует
         //номеру строки (начиная с 1) в таблице "Tabl_name_ust".
         byte   Name_Agr ;
#else
extern   byte   Num_obl ;
extern   byte   Name_Agr ;
#endif
//--------

word        ObjPrg ( word num )   ;
void        Obj_Interrupt (void );
void        Control_Nzad (void);
void        bo_ATK (void) ;
void        controlFan     ( word ) ; // управление приводом охлаждения (вентиляторов)
void        T_Izm_Dat      ( void ) ; // считывание данных с платы датчиков температуры

//--------

 #define T1_MR0_Int()
 #define T1_MR1_Int() Revers_Interrupt ()
 #define T1_MR2_Int()
#ifdef  _Vozb_KTE
 #define T1_MR3_Int() //Vozb_Interrupt ()
#else
 #define T1_MR3_Int()
#endif

 #define T1_CR0_Int()
 #define T1_CR1_Int()

 #define T2_MR0_Int()
 #define T2_MR1_Int()
#ifdef  _SIFU2_
 #define T2_MR2_Int() S2_Interrupt ()
#else
 #ifdef  _Vozb_KTE
  #define T2_MR2_Int() Vozb_Interrupt ()
 #else
  #define T2_MR2_Int()
 #endif
#endif
 #define T2_MR3_Int()

 #define T2_CR0_Int()
 #define T2_CR1_Int()

 #define T3_MR0_Int()
 #define T3_MR1_Int() S_Interrupt ()
 #define T3_MR2_Int()
 #define T3_MR3_Int()

 #define T3_CR0_Int()
 #define T3_CR1_Int()
//------------------------

// PPG1 - Сигнал форсировки ИУ сетевого инвертора :
  #ifndef _LABOR_STEND
#define  mPPG1_forsir_set( data )    if ( data ) { LPC_GPIO1->SET = (1<<5);} else { PPG_stop( 1, 0 ) ;}
  #else // на стенде АТК на выходных каскадах форсировка ИУ наоборот :
#define  mPPG1_forsir_set( data )    if ( data ) { PPG_stop( 1, 0 ) ;} else { LPC_GPIO1->SET = (1<<5);}
  #endif

//------------------------

//Количество дискретных портов на синхронном порту

#define    _SInp_max       6
#define    _SOut_max       3

//Количество ЦАПов ( по умолчанию их 3 шт. )
#undef  _DAC_numb_max
#define _DAC_numb_max       7
//------------------------------
// Номер PPG , используемого как DAC2 :
#define    _PPG_for_DAC2    2
//------------------------------
// Задать номера PPG , используемых как ЦАП . Необходимо еще перезадать выше количество ЦАПов .
// PPG0, PPG1 используются для суммы ИУ мостов Вперед и Назад .
// PPG2, PPG3 используются для суммы ИУ мостов Вперед и Назад 12-ти пульсного СИФУ ( при его наличии ) .
// PPG5 используется для суммы ИУ встроенного возбудителя ( при его наличии ) .
#define  _PPG_for_DAC3      3
#define  _PPG_for_DAC4      4
#define  _PPG_for_DAC5      6
#define  _PPG_for_DAC6      7
//------------------------------

// Выходные каскады для УПТФ и АТК :
#undef   _FzapolnLong_Low
#define  _FzapolnLong_Low       _MkSec( 80 )  // длительность нулевого импульса в мкс
#undef   _FzapolnLong_High
#define  _FzapolnLong_High      _MkSec( 25 )  // длительность единичного импульса в мкс

#undef   _FzapolnShort_Low
#define  _FzapolnShort_Low      _MkSec( 25 )  // длительность нулевого импульса в мкс
#undef   _FzapolnShort_High
#define  _FzapolnShort_High     _MkSec( 25 )  // длительность единичного импульса в мкс

#undef     _AD_Delta
#define    _AD_Delta         1    // Для точной установки нуля на 12-разрядном АЦП .

//------------------------------------------

// Маска для выдачи Аварии в Сборке Готовности , кроме Герконов , включает в себя
// ещё и Концевые выключатели дверей :
//#define  _Mask_Avar       ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )

// Если у каждого АТК нет собственного ШК и у комплекта АТК всего один ШК ,
// б/к одного и того же ШК приходят в каждый АТК , то нет смысла
// говорить о дверях ШК , полученных по сети от второго АТК ...
  #ifdef _ShK_own
#define    _Mask_Avar       ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | _Av_SQ1 | _Av_SQ2 | \
                              _Av_SQ1_ATK1 | _Av_SQ1_ATK2 | _Av_SQ1_ATKR | _Av_SQ2_ATK1 | _Av_SQ2_ATK2 | _Av_SQ2_ATKR )
  #else
#define    _Mask_Avar       ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | _Av_SQ1 | _Av_SQ2 | \
                              _Av_SQ1_ATK1 | _Av_SQ1_ATK2 | _Av_SQ1_ATKR )
  #endif
//------------------------------------------

// Чтобы легче сбрасывать защиту в 2-х шкафах на 4-х платах ...
//#define  _Mask_DistSbr    ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
#define    _Mask_DistSbr    ( 0 )

//------------------------------------------

// Выдаём Готовность при ОТСУТСТВИИ СИЛЫ ( по этой Готовности и включаем силу , то есть согласующий трансформатор
// кнопкой на ПУ "Вкл" , "ВВ Ротора" ) :
// Маска для маскируемых Аварий для выдачи Предупреждения в Сборке Готовности ,
// кроме Герконов и дверей SQ1 и SQ2 , включает в себя отсутствие силового напряжения :
//#define  _Mask_AvarPreduprGotovn  ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )

// Если у каждого АТК нет собственного ШК и у комплекта АТК всего один ШК ,
// б/к одного и того же ШК приходят в каждый АТК , то нет смысла
// говорить о дверях ШК , полученных по сети от второго АТК ...
  #ifdef _ShK_own
#define    _Mask_AvarPreduprGotovn  ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | _Av_NoSynch2 | _Av_SQ1 | _Av_SQ2 | \
                                      _Av_SQ1_ATK1 | _Av_SQ1_ATK2 | _Av_SQ1_ATKR | _Av_SQ2_ATK1 | _Av_SQ2_ATK2 | _Av_SQ2_ATKR )
  #else
#define    _Mask_AvarPreduprGotovn  ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | _Av_NoSynch2 | _Av_SQ1 | _Av_SQ2 | \
                                      _Av_SQ1_ATK1 | _Av_SQ1_ATK2 | _Av_SQ1_ATKR )
  #endif

//------------------------------------------

 //   Маска для несбрасываемых в "Сборке Готовности" аварий :
//#define  _Mask_AvarSbr      ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | \
//                              _Av_PUM | _Av_IdMax | _Av_Id_sum_Max | _Av_Iv_Max )

// Если у каждого АТК нет собственного ШК и у комплекта АТК всего один ШК ,
// б/к одного и того же ШК приходят в каждый АТК , то нет смысла
// говорить о дверях ШК , полученных по сети от второго АТК ...
  #ifdef _ShK_own
#define  _Mask_AvarSbr        ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | \
                                _Av_PUM | _Av_IdMax | _Av_Id_sum_Max | _Av_Iv_Max | _Av_SQ1 | _Av_SQ2 | \
                                _Av_SQ1_ATK1 | _Av_SQ1_ATK2 | _Av_SQ1_ATKR | _Av_SQ2_ATK1 | _Av_SQ2_ATK2 | _Av_SQ2_ATKR )
  #else
#define  _Mask_AvarSbr        ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | \
                                _Av_PUM | _Av_IdMax | _Av_Id_sum_Max | _Av_Iv_Max | _Av_SQ1 | _Av_SQ2 | \
                                _Av_SQ1_ATK1 | _Av_SQ1_ATK2 | _Av_SQ1_ATKR )
  #endif

//------------------------------------------

// Убираем Регуляторы из Рабочей Структуры :
//#define _Prg_Rabota  ( _ZadSkor | _RegSk | _RegTok | _Sled | _RN | _RP )
#undef    _Prg_Rabota
#define   _Prg_Rabota  ( /*_ZadSkor | _RegSk | _RegTok |*/ _Sled /*| _RN | _RP*/ )

//------------------------------

#define _sqr2_3mask   0.8164965809   // корень из 2/3 .
#define _PI           3.1415926535   // число пи .
#define _RadS_ObMin   9.549296585    // Коэффициент для перевода радиан в секунду в обороты в минуту .
                                     //
                                     // 1 рад       60
                                     // ------ = --------
                                     // 1 сек     2 * _PI
                                     //
/*------------------------------------------------*/

//------- Фильтрация , порог и разнополярное масштабирование сельсина :
//  Для того , чтобы иметь уставку , раскоментировать соответствующее . Уставка сразу будет видна
// в А7 , Масштабы . При наличии уставки _or.Sels_mashtP0 или _or.Sels_mashtP1 в А6 , Регулир.
// будет индикация немасштабированного и масштабированного сельсина в градусах .
//-------
//#define     _Sels_shift0
//#define     _Sels_shift1
//---
//#define     _Sels_mashtP0
//#define     _Sels_mashtP1
//---
//#define     _Sels_mashtM0
//#define     _Sels_mashtM1

//----------
#undef   _r_S_ImpLong
#define  _r_S_ImpLong    S_ImpLong

/*ДДД Привязка программных имен к аппаратным входам/выходам ДД-*/

            /*  Дискретные выходы  */

#define    bo_VV3_trans          Po0_c._.n0 // K8 - состояние ВВ3 - вакуусного выключачателя трансформатора . // DAN 12.04.2025
#define    bo_Vkl_Vent            Po0_c._.n1 // KG10
#define    bo_SN_On              Po0_c._.n2 // KG11
//#define  bo_                   Po0_c._.n3
//#define  bo_                   Po0_c._.n4
//#define  bo_                   Po0_c._.n5
#define    bo_Vkl_QK1            Po0_c._.n6 // Аппаратно не существует .
//#define  bo_                   Po0_c._.n7 // Аппаратно не существует .

#define    bo_AvarATK            PoS_c[0]._.n0  // K1
#define    bo_GotovATK           PoS_c[0]._.n1  // K2
#define    bo_PreduprATK         PoS_c[0]._.n2  // K3
#define    bo_RabotaATK          PoS_c[0]._.n3  // K4
#define    bo_N_490              PoS_c[0]._.n4  // К5
#define    bo_ReleMalSkor        PoS_c[0]._.n5  // К6 - Используется для снятия Пуска ( т.е. Задвига ИУ ) при нулевом задании .
//#define  bo_                   PoS_c[0]._.n6
#define    bo_Rezerv             PoS_c[0]._.n7  // K7

#define    bo_Reversor1          PoS_c[1]._.n0
#define    bo_Reversor2          PoS_c[1]._.n1
//#define  bo_                   PoS_c[1]._.n2
//#define  bo_                   PoS_c[1]._.n3
//#define  bo_                   PoS_c[1]._.n4
//#define  bo_                   PoS_c[1]._.n5
//#define  bo_                   PoS_c[1]._.n6
//#define  bo_                   PoS_c[1]._.n7

//#define  bo_                   PoS_c[2]._.n0
//#define  bo_                   PoS_c[2]._.n1
//#define  bo_                   PoS_c[2]._.n2
//#define  bo_                   PoS_c[2]._.n3
//#define  bo_                   PoS_c[2]._.n4
//#define  bo_                   PoS_c[2]._.n5
//#define  bo_                   PoS_c[2]._.n6
//#define  bo_                   PoS_c[2]._.n7


// Порт для выходов , которые никуда не выводятся :
#define    bo_Avar               Prt_NULL._.n0
#define    bo_Predupr            Prt_NULL._.n1
#define    bo_Gotov              Prt_NULL._.n2
#define    bo_MT                 Prt_NULL._.n3
#define    bo_Insulat            Prt_NULL._.n4
#define    bo_Avar_Yach          Prt_NULL._.n5 // Используется для Аварии , которая отключает ячейку Согласующего .
#define    bo_KontrVkl           Prt_NULL._.n6
#define    bo_VklVent_1_2_3      Prt_NULL._.n7

#define    Trg_Pusk              Prt_NULL._.n8 
#define    Pusk_old              Prt_NULL._.n9
#define    Trg_IzmTemp           Prt_NULL._.n10 
#define    Trg_BegTemp           Prt_NULL._.n11





#define    bo_EndIzm             Prt_NULL2._.n0
#define    bo_Vedushiy           Prt_NULL2._.n1
#define    bo_Otkl_Imp           Prt_NULL2._.n2
#define    bo_AvarYacheykaATK    Prt_NULL2._.n3  // Общая авария комплекта АТК для отключения ячейки ( Герконы и двери ) .                   Prt_NULL2._.n3
//#define  bo_                   Prt_NULL2._.n4
//#define  bo_                   Prt_NULL2._.n5
//#define  bo_                   Prt_NULL2._.n6
//#define  bo_                   Prt_NULL2._.n7
//  ---  контактор вентилятора ---
#define    bo_vent_vkl      (bo_Vkl_Vent = 1)//0x01 << 1; // P1_1 - Q1V ,P1_4 - Q2V
#define    bo_vent_otkl     (bo_Vkl_Vent = 0)//0x01 << 1;

            /*  Дискретные входы   */

#define    bi_2P24               Pi0_f._.n0
//#define  bi_                   Pi0_f._.n1
#define    bi_AF1P               Pi0_f._.n2
#define    bi_Fsil_set           Pi0_f._.n3
#define    bi_SQ1                Pi0_f._.n4
//#define  bi_                   Pi0_f._.n5
//#define  bi_                   Pi0_f._.n6
#define    bi_DS1              ( Pi0_f._.n7 == 1 || Klav_Buff == _Reset ) //|| ATK2_DS1 == 1 ) 12.03.2021 - сброс переделан .

//--------------------------------------------------------------------------
 // Не перепутать ! Номер INT и номер в Порту 1 - НЕ совпадают :

//#define  bi_                   Pi1_f._.n0  //     - INT7
//#define  bi_                   Pi1_f._.n1  // сетевой наездник
//#define  bi_                   Pi1_f._.n2  // KF1 - INT5
//#define  bi_                   Pi1_f._.n3  // KР1 - INT6
//#define  bi_PPG4_AP2           Pi1_f._.n4  // PPG4- INT4
//#define  bi_                   Pi1_f._.n5  //     - INT3
#define    bi_Gercon             Pi1_nm._.n6 // 1B  - INT0
#define    bi_GerconAC2          Pi1_nm._.n7 // 2B  - INT1
//--------------------------------------------------------------------------
#define    mAP2_Id_zad_null()    (((b)(LPC_GPIO2->PIN >> 15) & 0x01) == 0) // bi_PPG4_AP2 - Pi1_f._.n4
//--------------------------------------------------------------------------

//#define  bi_                   PiS_f[0]._.n1
#define    bi_Vnesh_Avar          PiS_f[0]._.n1
#define    bi_Q1_1               PiS_f[0]._.n2
#define    bi_Q1_2               PiS_f[0]._.n3
#define    bi_SF2                PiS_f[0]._.n4
#define    bi_SFV1               PiS_f[0]._.n5
#define    bi_KV1                PiS_f[0]._.n6
#define    bi_Dist_Upr           PiS_f[0]._.n7

#define    bi_BV1                PiS_f[1]._.n0
#define    bi_BV2                PiS_f[1]._.n1
//#define  bi_                   PiS_f[1]._.n2
//#define  bi_                   PiS_f[1]._.n3
//#define  bi_                   PiS_f[1]._.n4
//#define  bi_                   PiS_f[1]._.n5
//#define  bi_                   PiS_f[1]._.n6
//#define  bi_                   PiS_f[1]._.n7

#define    bi_xKZ_bk             PiS_f[2]._.n0
#define    bi_xVV1_stator        PiS_f[2]._.n1
#define    bi_xVV3_trans         PiS_f[2]._.n2
#define    bi_xPusk              PiS_f[2]._.n3
#define    bi_xStop              PiS_f[2]._.n4
#define    bi_AvarUKAV           PiS_f[2]._.n5
#define    bi_Revers_Strumenya   PiS_f[2]._.n6
#define    bi_V1_V3              PiS_f[2]._.n7

//#define  bi_                   PiS_f[3]._.n0
//#define  bi_                   PiS_f[3]._.n1
//#define  bi_                   PiS_f[3]._.n2
//#define  bi_                   PiS_f[3]._.n3
//#define  bi_                   PiS_f[3]._.n4
//#define  bi_                   PiS_f[3]._.n5
//#define  bi_                   PiS_f[3]._.n6
//#define  bi_                   PiS_f[3]._.n7

#define    bi_VV1_stator      ( (bi_Dist_Upr == 0 && bi_xVV1_stator == 1) || (bi_Dist_Upr == 1 && bi_SA_B1   == 1) )
#define    bi_VV3_trans       ( (bi_Dist_Upr == 0 && bi_xVV3_trans  == 1) || (bi_Dist_Upr == 1 && bi_SA_B3   == 1) )
#define    bi_KZ_bk           ( (bi_Dist_Upr == 0 && bi_xKZ_bk      == 1) || (bi_Dist_Upr == 1 && bi_SA_QF1  == 1) )
#define    bi_Pusk_1          ( (bi_Dist_Upr == 0 && bi_xPusk       == 1) || (bi_Dist_Upr == 1 && bi_SA_Pusk == 1) )
#define    bi_Stop_1          ( (bi_Dist_Upr == 0 && bi_xStop       == 1) || (bi_Dist_Upr == 1 && bi_SA_Stop == 1) )

#define    bi_Pusk             Trg_Pusk  

//#define  bi_KTE_rezerv1        0
//#define  bi_GerconDC           0

#define    bi_dt_Otkl_KZ         0

#define    bi_Reversor1          1
#define    bi_Reversor2          0


// Входить в Работу без ИУ можно по наличию силы от Согласующего трансформатора
// но при условии , что выбрана синхронизация от силового напряжения :
#define    bi_xQK1             ( (flgO._.Usil_ok == 1 && flgO._.UsilTMIN_ok == 1 && flgO._.UsilTMAX_ok == 1 && \
                                  _r.Cfg2._.SIFU_Syn2 == 1) || _r.Cfg2._.SIFU_Syn2 == 0 )
// Однако , для оперативного отключения с задвигом и последующим снятием ИУ по наложению ТП ,
// следует входить в Работу без ИУ по наличию силы и сигналу ТП :
//#define    bi_QK1              ( bi_xQK1 == 1 && bi_TP == 1 )

#define    bi_QK1              ( bi_xQK1 == 1 && bo_Gotov == 1 )
#define    bi_VR1              ( bi_Stop_1 )

// После включения ячейки статора на ПУ кнопкой "Вкл" , "ВВ Статора" 6кВ на статор не подаётся , пока не вклячатся Реверсоры .
// В 2-ух двигательном режиме контролируются оба Реверсора .
// В 1-но двигательном режиме контролируется один Реверсор :
// 1. "Реверсор1" в АТК1 или АТКR .
// 2. "Реверсор2" в АТК2 или АТКR .
// Включение выбранных Реверсоров происходит от Ручки КЗС - это Пуск и подача ИУ :
#define    bi_Reversor        ( (flgO._.Reg1dvig == 0 && bi_Reversor1 == 1 && bi_Reversor2 == 1 && flgO._.dvig_N1 == 1 && flgO._.dvig_N2 == 1) || \
                                (flgO._.Reg1dvig == 1 && bi_Reversor1 == 1 && bi_Reversor2 == 0 && flgO._.dvig_N1 == 1 && flgO._.dvig_N2 == 0 && (_or.CfgO._.ATK1 == 1 || _or.CfgO._.ATKR == 1)) || \
                                (flgO._.Reg1dvig == 1 && bi_Reversor1 == 0 && bi_Reversor2 == 1 && flgO._.dvig_N1 == 0 && flgO._.dvig_N2 == 1 && (_or.CfgO._.ATK2 == 1 || _or.CfgO._.ATKR == 1)) )

// Контролируем оба тормоза - и ТП и рабочий :
//#define    bi_Barab_Rastormogen  ( bi_TP == 1 && bi_RT_snyat == 1 )

// Дискретная команда Пуск - это по сути б/к Реверсоров , т.к. они включаются от Ручки КЗС .
// Для снятия Пуска при затормаживании Барабана и до отключения Реверсоров следует контролировать еще два условия :
// "КЗС не в Нуле" и "Тормоз не наложен" .
// Если Ручку КЗС поставили в нуль - замедляемся по ЗИРС и ждём пока сработает КРМ ( т.е. наложится тормоз и заклинит
// Барабан ) . Еще контролируем фактическую скорость барабана , т.к. дискретный сигнал bi_RT_snyat может остаться в
// заторможенном состоянии , если концевик не отрегулирован . Только затем , во избежание провала неуправляемой клети ,
// снимаем Пуск для Задвига ИУ . После задвига ИУ запускаем выдержку на снятие ИУ .
// После снятия ИУ включится реле "V нулевая" ( на самом деле реле "Снятие ИУ" , просто на первом ШПМ оно так называлось ) ,
// по которому от Пульта отключатся Реверсоры .
// Т.о., Реверсоры должны отключиться только после затормаживания Барабана .
//--
//#define    bi_xPusk           ( (bi_Null == 0 || bi_Barab_Rastormogen == 1 || bo_ReleMalSkor == 0) && bi_Reversor == 1 )


//#ifdef    _CAN_Pusk // Ведомый Инвертор получает Пуск по сети от Ведущего :
// #define   bi_Pusk            ( (bi_xPusk == 1 && flgO._.Vedushiy == 1) || (ATK2_Pusk == 1 && flgO._.Vedushiy == 0) )
//#else               // Каждый АТК получает свою дискретную команду Пуск :
// #define   bi_Pusk              (bi_xPusk == 1 )
//#endif

#define    bi_Technol_Ostanov    KTE2_Shunt_Rot // Ротор Зашунтирован - Инвертор кидаем в Альфа Макс .

// Ревизия или не выбран никакой режим ( Люди , Груз или Негабарит ) :
//#define    bi_Reviz            0

#define    bi_KTE_rezerv         0
#define    bi_Razresh_Vkl        bi_Pusk

#define    bi_AK2                1 // Если нет блок-контакта Q2 - для функционирования нового алгоритма Q2V .
#define    bi_AF1                0 // Аварийный сигнал только при предохранителях .
#define    bi_AR1                0
#define    bi_AK1                1
#define    bi_AK2                1 // Если нет блок-контакта Q2 - для функционирования нового алгоритма Q2V .
#define    bi_Bolshe             0
#define    bi_Menshe             0
#define    bi_Rab_Tolch          1 // Прием задания в режиме Работа .
#define    bi_TB                 0
#define    bi_TH                 0
#define    bi_Zapret             0
#define    bi_Fors_Temp          0 // Для форсированного торможения

#define    _V_REZERVE            0
#define    _ATK1                 1
#define    _ATK2                 2

//-------------------
#define  _ACh0_txt      "n0 -Id      "
#define  _ACh1_txt      "n1 -резерв  "
#define  _ACh2_txt      "n2 -резерв  "
#define  _ACh3_txt      "n3 -резерв  "
#define  _ACh4_txt      "n4 -резерв  "
#define  _ACh5_txt      "n5 -Ud      "
#define  _ACh6_txt      "n6 -резерв  "
#define  _ACh7_txt      "n7 -резерв  "
#define  _ACh8_txt      "n8 -резерв  "
#define  _ACh9_txt      "n9 -резерв  "
#define  _ACh10_txt     "n10-резерв  "
#define  _ACh11_txt     "n11-Irot    "
#define  _ACh12_txt     "n12-Ізол.   "
#define  _ACh13_txt     "n13-резерв  "
#define  _ACh14_txt     "n14-резерв  "
#define  _ACh15_txt     "n15-Резист. "
#define  _ACh16_txt     "AN-P24      "
#define  _ACh17_txt     "AN-N12      "
#define  _ACh18_txt     "AN-P12      "

            /*  Аналоговые входы  */

#define    Id_mg_ach            _ar.n00_ach
//#define  _ach                 _ar.n01_ach
//#define  _ach                 _ar.n02_ach
//#define  _ach                 _ar.n03_ach
//#define  _ach                 _ar.n04_ach
#define    Ud_ach               _ar.n05_ach
//#define  _ach                 _ar.n06_ach
//#define  _ach                 _ar.n07_ach
//#define  _ach                 _ar.n08_ach
//#define  _ach                 _ar.n09_ach
//#define  _ach                 _ar.n10_ach
#define    Irot_ach             _ar.n11_ach
#define    Insulation_ach       _ar.n12_ach
//#define  _ach                 _ar.n13_ach
//#define  _ach                 _ar.n14_ach
#define    Zad_res_ach          _ar.n15_ach
#define    Z_sk_ach             Zad_res_ach

#define    P24_ach              _ar.n16_ach
#define    P12_ach              _ar.n18_ach
#define    N12_ach              _ar.n17_ach
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//----------- A8 -  Битовые объектные уставки ------------

  #define _KTE_A8_ConfigObj
//--------------------------------------------------------

     //  Объектное Конфигурирование
 union ConfigO {
  word all ;
  struct  {
      word ATK1          : 1 ;
      word ATK2          : 1 ;
      word ATKR          : 1 ;
      word rezerv3       : 1 ;

      word rezerv4       : 1 ;
      word rezerv5       : 1 ;
      word rezerv6       : 1 ;
      word rezerv7       : 1 ;
     //----
      word rezerv8       : 1 ;
      word rezerv9       : 1 ;
      word rezerv10      : 1 ;
      word rezerv11      : 1 ;

      word rezerv12      : 1 ;
      word rezerv13      : 1 ;
      word rezerv14      : 1 ;
      word rezerv15      : 1 ;
    } _ ;
} ;

#define   _cfgO_ATK1           ((w) 0x0001 )
#define   _cfgO_ATK2           ((w) 0x0002 )
#define   _cfgO_ATKR           ((w) 0x0004 )
//#define _cfgO_rezerv         ((w) 0x0008 )

//#define _cfgO_rezerv         ((w) 0x0010 )
//#define _cfgO_rezerv         ((w) 0x0020 )
//#define _cfgO_rezerv6        ((w) 0x0040 )
//#define _cfgO_rezerv7        ((w) 0x0080 )

//#define _cfgO_rezerv8        ((w) 0x0100 )
//#define _cfgO_rezerv9        ((w) 0x0200 )
//#define _cfgO_rezerv10       ((w) 0x0400 )
//#define _cfgO_rezerv11       ((w) 0x0800 )

//#define _cfgO_rezerv12       ((w) 0x1000 )
//#define _cfgO_rezerv13       ((w) 0x2000 )
//#define _cfgO_rezerv14       ((w) 0x4000 )
//#define _cfgO_rezerv15       ((w) 0x8000 )

union ATKflag {
  word all ;
  struct  {
      word trig_Pusk   : 1 ;
      word trig_Reg    : 1 ;
      word rezerv2     : 1 ;
      word rezerv3     : 1 ;

      word rezerv4     : 1 ;
      word rezerv5     : 1 ;
      word rezerv6     : 1 ;
      word rezerv7     : 1 ;
     //----
      word rezerv8     : 1 ;
      word rezerv9     : 1 ;
      word rezerv10    : 1 ;
      word rezerv11    : 1 ;

      word rezerv12    : 1 ;
      word rezerv13    : 1 ;
      word rezerv14    : 1 ;
      word rezerv15    : 1 ;
    } _ ;
} ;

union flagO {
  word all ;
  struct  {
      word Vedushiy    : 1 ;
      word abonATK     : 2 ;
      word V_rezerve   : 1 ;

      word Usil_ok     : 1 ;
      word UsilTMIN_ok : 1 ;
      word UsilTMAX_ok : 1 ;
      word Reg1dvig    : 1 ;
     //----
      word Shunt_Rot   : 1 ;
      word dvig_N1     : 1 ;
      word Id_neprer1  : 1 ;
      word Id_neprer   : 1 ;

      word CAN0_init   : 1 ;
      word dvig_N2     : 1 ;
      word CAN0_ok     : 1 ;
      word CAN1_ok     : 1 ;
    } _ ;
} ;

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

 struct  oBlok_Ustavok
  {        //  номера переменных, которые следует выводить на i-тый ЦАП.
    struct DAC_data dac_numb[ _DAC_numb_max ] ;
    word   Rezerv_DAC [ 12 ] ;

    byte  Ai_CS[_Ai_max];

    byte  AS_CSo[_SOut_max];

    byte  AS_CSi[_SInp_max];

    byte  PiS_Normal[_SInp_max];    //Маска последовательного порта S400.
    /*    PiS_Normal[0]*/
    /*    PiS_Normal[1]*/
    /*    PiS_Normal[2]*/
    /*    PiS_Normal[3]*/

    byte  PoS_Normal[_SOut_max];
    /*    PoS_Normal[0]*/
    /*    PoS_Normal[1]*/

    union ConfigO  CfgO ;

#ifdef    _Sels_mashtP0
    word   Sels_mashtP0 ;
#endif
#ifdef    _Sels_mashtM0
    word   Sels_mashtM0 ;
#endif
#ifdef    _Sels_shift0
    byte   Sels_shift0 ;
    byte   rezerv0 ;
#endif

#ifdef    _Sels_mashtP1
    word   Sels_mashtP1 ;
#endif
#ifdef    _Sels_mashtM1
    word   Sels_mashtM1 ;
#endif
#ifdef    _Sels_shift1
    byte   Sels_shift1 ;
    byte   rezerv1 ;
#endif

    word   T_Pr;
    word   T_Av;
    word   Filtr_Param ;
    word   Ttr_predupr ;
    word   Ttr_4mA ;
    word   Ttr_20mA ;

    word   Filtr_Param_Nzad ;
    word   Nzad_4mA ;
    word   Nzad_20mA ;

    word   Id_Vkl_Vent ;
    word   T_Otkl_Vent ;

    word   N_nom ;
    word   RTMAX  ;
    word   T_zaderg_pusk ;
    word   Z_SkorNull ;
    word   Skor_Vkl_KZ ;
    word   Skor_Otkl_KZ ;

    word   Uset_nom ;
    word   Urot_nom ;

    word   Id_IU ;
    word   i_count ;

    word   Mashtab_ZSkA;
    word   Mashtab_ZSkA_Vper_Gr;
    word   Mashtab_ZSkA_Naz_Gr;
    word   Mashtab_ZSkA_Vper_NG;
    word   Mashtab_ZSkA_Naz_NG;

    word   M_Zsk_Vper_Promeg;
    word   M_Zsk_Naz_Promeg;
    word   M_Zsk_Vper_Promeg_Gr;
    word   M_Zsk_Naz_Promeg_Gr;
    word   M_Zsk_Vper_Promeg_NG;
    word   M_Zsk_Naz_Promeg_NG;

    word   M_Zsk_Vper_Dotiag;
    word   M_Zsk_Naz_Dotiag;
    word   M_Zsk_Vper_Dotiag_Gr;
    word   M_Zsk_Naz_Dotiag_Gr;

    word   M_Zsk_Vper_Posad;
    word   M_Zsk_Naz_Posad;
    word   M_Zsk_Vper_Posad_Gr;
    word   M_Zsk_Naz_Posad_Gr;

    word   Mashtab_Reviz;

    word   T_ZISkor_Reviz;

    word   Id_Rastorm_max ;
    word   Mashtab_Id_Rastorm ;

    word   NzMaxPromeg ;
    word   NzMaxPromeg_Gr ;
    word   NzMaxPromeg_NG ;
    word   NzMaxDotiag ;
    word   NzMaxDotiag_Gr ;
    word   NzMaxPosad ;
    word   NzMaxPosad_Gr ;
    word   NzMaxRevizia ;

    word   KRSP ;
    word   KRSI  ;
    word   KRSPIP ;

    word   T_ZadZ_Vp ;
    word   T_ZadZ_Nz ;

    word   Skor_TP_Avar ;
    word   ReleMalSkor ;
    word   GistReleMalSkor ;
    word   NzadSmeshMax ;
    word   Z_SkMin ;

    word   KRSP_Ludi ;
    word   KRSI_Ludi  ;
    word   KRSPIP_Ludi ;
    word   KRSP_Gruz ;
    word   KRSI_Gruz  ;
    word   KRSPIP_Gruz ;
    word   KRSP_Negabarit ;
    word   KRSI_Negabarit  ;
    word   KRSPIP_Negabarit ;
    word   T_ZISkorP_LudiR ;
    word   T_ZISkorP_LudiT ;
    word   T_ZISkorM_LudiR ;
    word   T_ZISkorM_LudiT ;
    word   T_ZISkorP_GruzR ;
    word   T_ZISkorP_GruzT ;
    word   T_ZISkorM_GruzR ;
    word   T_ZISkorM_GruzT ;
    word   T_ZISkorP_NgbrR ;
    word   T_ZISkorP_NgbrT ;
    word   T_ZISkorM_NgbrR ;
    word   T_ZISkorM_NgbrT ;
    word   T_dN_Max ;

    word   Temp_RT_P ;
    word   Temp_RT_M ;
    word   KRTPRI ;
    word   KRTNI ;
    word   KRTP ;

    word   Z_SkMax_bezKZ ;
    word   Id_Vkl_VentShs1;
    word   TimeAvarNoVent;
    word   Id_min_vent;
    word   Id_max_vent;
    word   Time_otkl_BV1 ;
    word   Id_zad_fors;

    float  T0Volt;          //float  T_20degr;
    float  TempT;
    byte   Time_opros;
    float  Pimp_max[2] ;
    float  Pimp_min[2] ;
    float  mV_A ;

    float dt_Av;

    word   N_490 ;
    word   Z_Sk_mestnoe ;
    
    word   Time_ComtrolPIU;

    word   rezerv[  94 ] ;

#ifdef _INTERPRETER
    struct SetpointData MemData;
#endif

    byte  Contrl_sum ;
  } ;
const word AvTemp[] =
{
  _Ch_Ishs1msk,  
  _Ch_BK1_S1msk,
  _Ch_BK2_S1msk,
  _Ch_BK3_S1msk,
  _Ch_BK4_S1msk,
  _Ch_BK5_S1msk,
  _Ch_BK6_S1msk,
  _Ch_Ishs2msk,  
  _Ch_BK1_S2msk,
  _Ch_BK2_S2msk,
  _Ch_BK3_S2msk , 
  _Ch_BK4_S2msk , 
  _Ch_BK5_S2msk , 
  _Ch_BK6_S2msk  
};

//-------------- А7 - Объектные уставки ------------------
  //{ "N#плн-Вп-Л-мсш", &_r.Mashtab_ZSkA          , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#плн-Нз-Л-мсш", &_or.Mashtab_ZSkA         , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#плн-Вп-Г-мсш", &_or.Mashtab_ZSkA_Vper_Gr , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#плн-Нз-Г-мсш", &_or.Mashtab_ZSkA_Naz_Gr  , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#плн-Вп-Н-мсш", &_or.Mashtab_ZSkA_Vper_NG , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#плн-Нз-Н-мсш", &_or.Mashtab_ZSkA_Naz_NG  , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#прм-Вп-Л-мсш", &_or.M_Zsk_Vper_Promeg    , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#прм-Нз-Л-мсш", &_or.M_Zsk_Naz_Promeg     , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#прм-Вп-Г-мсш", &_or.M_Zsk_Vper_Promeg_Gr , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#прм-Нз-Г-мсш", &_or.M_Zsk_Naz_Promeg_Gr  , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#прм-Вп-Н-мсш", &_or.M_Zsk_Vper_Promeg_NG , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#прм-Нз-Н-мсш", &_or.M_Zsk_Naz_Promeg_NG  , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#дтж-Вп-Л-мсш", &_or.M_Zsk_Vper_Dotiag    , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#дтж-Нз-Л-мсш", &_or.M_Zsk_Naz_Dotiag     , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#дтж-Вп-Г-мсш", &_or.M_Zsk_Vper_Dotiag_Gr , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#дтж-Нз-Г-мсш", &_or.M_Zsk_Naz_Dotiag_Gr  , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#псд-Вп-Л-мсш", &_or.M_Zsk_Vper_Posad     , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#псд-Нз-Л-мсш", &_or.M_Zsk_Naz_Posad      , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#псд-Вп-Г-мсш", &_or.M_Zsk_Vper_Posad_Gr  , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#псд-Нз-Г-мсш", &_or.M_Zsk_Naz_Posad_Gr   , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#ревизия-мсш.", &_or.Mashtab_Reviz        , 0               , 0x1400           , 0x0100       ,(w*)&_ind_Nom, 1              , 0xff, "ед" , _form(1,3,3,2) },\
  //{ "N#-макс-прм-Л.", &_or.NzMaxPromeg          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-прм-Г.", &_or.NzMaxPromeg_Gr       ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-прм-Н.", &_or.NzMaxPromeg_NG       ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-дтж-Л.", &_or.NzMaxDotiag          ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-дтж-Г.", &_or.NzMaxDotiag_Gr       ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-псд-Л.", &_or.NzMaxPosad           ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-псд-Г.", &_or.NzMaxPosad_Gr        ,_Skor_nom( +0.0 ), _Skor_nom( +2.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-макс-ревиз.", &_or.NzMaxRevizia         ,_Skor_nom( +0.0 ), _Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "Kп-РC-Люди    ", &_or.KRSP_Ludi            , 0               , 127*256          , 256           ,(w*)&_ind_Nom, 32            , 0xff, "ед" , _form(1,3,2,2) },\
  //{ "Tи-РC-Люди    ", &_or.KRSI_Ludi            , 0               , 2000             , 1             ,(w*)&_ind_Nom, 2             , 0xff, "мceк",_form(1,4,0,2) },\
  //{ "Kпип-РC-Люди  ", &_or.KRSPIP_Ludi          , 0               , 127*256          , 256           ,(w*)&_ind_Nom, 32            , 0xff, "ед" , _form(1,3,2,2) },\
  //{ "Kп-РC-Груз    ", &_or.KRSP_Gruz            , 0               , 127*256          , 256           ,(w*)&_ind_Nom, 32            , 0xff, "ед" , _form(1,3,2,2) },\
  //{ "Tи-РC-Груз    ", &_or.KRSI_Gruz            , 0               , 2000             , 1             ,(w*)&_ind_Nom, 2             , 0xff, "мceк",_form(1,4,0,2) },\
  //{ "Kпип-РC-Груз  ", &_or.KRSPIP_Gruz          , 0               , 127*256          , 256           ,(w*)&_ind_Nom, 32            , 0xff, "ед" , _form(1,3,2,2) },\
  //{ "Kп-РC-Нгбр    ", &_or.KRSP_Negabarit       , 0               , 127*256          , 256           ,(w*)&_ind_Nom, 32            , 0xff, "ед" , _form(1,3,2,2) },\
  //{ "Tи-РC-Нгбр    ", &_or.KRSI_Negabarit       , 0               , 2000             , 1             ,(w*)&_ind_Nom, 2             , 0xff, "мceк",_form(1,4,0,2) },\
  //{ "Kпип-РC-Нгбр  ", &_or.KRSPIP_Negabarit     , 0               , 127*256          , 256           ,(w*)&_ind_Nom, 32            , 0xff, "ед" , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСВп'+'Л", &_or.T_ZISkorP_LudiR      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСВп'-'Л", &_or.T_ZISkorP_LudiT      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСНз'+'Л", &_or.T_ZISkorM_LudiR      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСНз'-'Л", &_or.T_ZISkorM_LudiT      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСВп'+'Г", &_or.T_ZISkorP_GruzR      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСВп'-'Г", &_or.T_ZISkorP_GruzT      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСНз'+'Г", &_or.T_ZISkorM_GruzR      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСНз'-'Г", &_or.T_ZISkorM_GruzT      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСВп'+'Н", &_or.T_ZISkorP_NgbrR      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСВп'-'Н", &_or.T_ZISkorP_NgbrT      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСНз'+'Н", &_or.T_ZISkorM_NgbrR      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "ТмпЗИ-РСНз'-'Н", &_or.T_ZISkorM_NgbrT      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N-авар.откл-ТП", &_or.Skor_TP_Avar         ,_Skor_nom( 0.0 ) , _Skor_nom( +1.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
  //{ "N#-порогВп    ", &_r.Z_SkMin               ,_Skor_nom( +0.00), _Skor_nom( +0.5 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,2,2,2) },\
  //{ "N#-порогНз    ", &_or.Z_SkMin              ,_Skor_nom( +0.00), _Skor_nom( +0.5 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,2,2,2) },\
  //{ "N#-смещ-Макc  ", &_or.NzadSmeshMax         ,_Skor_nom( +0.00), _Skor_nom( +0.5 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,2,2,2) },\
  //{ "T-задерж-N#Вп ", &_or.T_ZadZ_Vp            , 0               ,_Sec( 9.0 )       ,_Sec(1.0)      ,(w*)&_ind_Nom, 1             , 0xff, "сек", _form(1,1,2,2) },\
  //{ "T-задерж-N#Нз ", &_or.T_ZadZ_Nz            , 0               ,_Sec( 9.0 )       ,_Sec(1.0)      ,(w*)&_ind_Nom, 1             , 0xff, "сек", _form(1,1,2,2) },\

    #define _A7_Obj_Ust \
    { "N#-місцеве    ", &_or.Z_Sk_mestnoe         ,_Skor_nom( 0.0 ) ,_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },\
    { "Пер.тест живл.", &_or.Time_ComtrolPIU      ,_Sec( 60.0 )     ,_Sec( 3600.0 ) ,_Sec(60)     ,(w*)&_ind_Nom, _Sec(1), 0xff, "хвл", _form(1,2,2,2) },\
    { "T-затрим-Пуск ", &_or.T_zaderg_pusk        , 3               ,_Sec( 30.0 )      ,_Sec(1.0)     ,(w*)&_ind_Nom,  1             , 0xff, "сек", _form(1,2,2,2) },\
    { "N=490         ", &_or.N_490                ,_Skor_nom( 0.0 ) ,_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },\
    { "N-мал.швид.   ", &_or.ReleMalSkor          ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
    { "Гіст.-мал.швид", &_or.GistReleMalSkor      ,_Skor_nom( +0.0 ),_Skor_nom( +10.0 ),_Skor_nom(0.01),(w*)&_ind_Nom, 1             , 0xff, "%"  , _form(1,3,2,2) },\
    { "N#-відк-КЗ-рот", &_or.Skor_Otkl_KZ         ,_Skor_nom( 0.0 ) ,_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) },\
    { "N#-макс без КЗ", &_or.Z_SkMax_bezKZ        ,_Skor_nom( 0.0 ) ,_Skor_nom( +2.0 ) ,_Skor_Nom     ,(w*)&_ind_Nom, _Skor_nom(0.01), 0xff, "ном", _form(1,2,2,2) }

//--------------------------------------------------------

    #define _A7_CAN_MASTER_Ust \
    { "Адр.Абон.CAN0 ", &_r.AddrDevice2     , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од"  , _form(1,3,0,1) },\
    { "Адр.Абон.CAN1 ", &_r.AddrDevice1     , 0               , 0x7f             , 1            ,(w*)&_ind_Nom, 1              , 0xff, "од"  , _form(1,3,0,1) }

//------------ А6 - Объектная индикация ------------------

    //#define _A6_Obj_Ind \

  //{ "N#нп, N#-смщ  ", { &Nzad           , &NzadSmesh            }, {_Skor_nom(1),_Skor_nom(1)},{"%, "  ,"%" }, {(w*)&_ind_100,(w*)&_ind_100} ,{_form(0,3,0,2),_form(0,2,1,2)} },\
  //{ "N#  , N#-смщ  ", { &Z_Skor         , &NzadSmesh            }, {_Skor_nom(1),_Skor_nom(1)},{"%, "  ,"%" }, {(w*)&_ind_100,(w*)&_ind_100} ,{_form(0,3,0,2),_form(0,2,1,2)} },\

//--------------------------------------------------------

  //{ "CAN:time      ", { &Opros_time              }, { _fSec(1)         },{"cek "   },{(w*)&_ind_Nom } ,{_form(1,1,3,2)               } },
  //{ "cCfgM1,cStsM1 ", { &CfgM.all       , &StsM.all           },{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },

    #define _A6_CAN_MASTER_Ind \
    { "AP2:cCfg,cSts ", { &canr.CfgRegAp2.all, &canr.StatReg2.all},{ 1             , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },\
    { "stsAP1, stsAP2", { &canr.StatReg1.all, &canr.StatReg2.all},{ 1           , 1              },{ "h, " ,"h" }, {(w*)&_ind_Nom,(w*)&_ind_Nom},{_formh(1,2   ),_formh(1,2   )} },\
    { "AP2 :  rd1,rd2", { &Tst_Read_Dev[0]  , &Tst_Read_Dev[1]     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },\
    { "AP2 :  rd3,rd4", { &Tst_Read_Dev[2]  , &Tst_Read_Dev[3]     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },\
    { "AP2 :  rd5,rd6", { &Tst_Read_Dev[4]  , &Tst_Read_Dev[5]     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },\
    { "AP2 :  rd7,wr1", { &Tst_Read_Dev[6]  , &Tst_Write_Dev[0]     }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom  } ,{_form(1,5,0,2),_form(1,5,0,2)} },\
    { "AP2 :  wr2    ", { &Tst_Write_Dev[1]                        }, {   1  },{  ""},{(w*)&_ind_Nom  } ,{_form(1,5,0,2)} },\
    { "AP2 : SendRec ", { &abDev1.err.send, &abDev1.err.receive }, { 1,   1  },{", ",  ""},{(w*)&_ind_Nom ,(w*)&_ind_Nom } ,{_form(1,3,0,1),_form(1,3,0,1)} }

//--------- F1 - Объектные переменные для следа ----------

    #define _Sld_cnst_Obj \
    {"flgO_all ", &flgO.all         , _sl_form(2,1,1,0,0), 1          ,(w*)&_ind1_sld  , "h " },\
    {"ATKflg   ", &ATK_flg.all      , _sl_form(2,1,1,0,0), 1          ,(w*)&_ind1_sld  , "h " },\
    {"StsAP2   ", &canr.StatReg2.all, _sl_form(2,1,1,0,0), 1          ,(w*)&_ind1_sld  , "h " },\
    {"StsShU2  ", &canr.StatReg3.all, _sl_form(2,1,1,0,0), 1          ,(w*)&_ind1_sld  , "h " },\
    {"ownStsAP1", &canr.StatReg.all , _sl_form(2,1,1,0,0), 1          ,(w*)&_ind1_sld  , "h " },\
    {"ownStsShU", &canr.StatReg4.all, _sl_form(2,1,1,0,0), 1          ,(w*)&_ind1_sld  , "h " },\
    {"N_pdf    ", &SkorPDF          , _sl_form(2,0,2,3,1), _Skor_Nom  ,(w*)&_ind100_sld, "% " },\
    {"N_rot    ", &N_rot            , _sl_form(2,0,2,3,1), _Skor_Nom  ,(w*)&_ind100_sld, "% " },\
    {"Idrv     ", &Irot             , _sl_form(2,0,2,3,1), _Id_Nom    ,(w*)&_ind100_sld, "% " },\
    {"Istat    ", &Ist_SA           , _sl_form(2,0,2,3,1), _Id_Nom    ,(w*)&_ind100_sld, "% " },\
    {"dN#      ", &dZ_Sk            , _sl_form(2,0,2,3,1), _Skor_Nom  ,(w*)&_ind100_sld, "% " }

//------------ AD - Объектный вывод на ЦАП ---------------

    //#define _AD_Obj_DAC \

//------- FB - Объектные переменные для журнала ----------

    //#define _Jrn_cnst_Obj\

//--------------------------------------------------------

/*------------------------------------------------*/
#ifdef  _OBJ_INCLUDE
/*------------------------------------------------*/

struct  oBlok_Ustavok  _or  ;

_x_far const  struct  oBlok_Ustavok  _oc   =
  {
 /*   word  dac_numb[0] ;   sys N  */ { {  0 ,  (w)(0.12 * 256)     , 0   },   //DA0
 /*   word  dac_numb[1] ;          */   {  0 ,  (w)(0.12 * 256)     , 0   },   //DA1->PPG8
 /*   word  dac_numb[2] ;   Ist_SA */   {  22,  (w)(0.12 * 256/_K_diskr) , 0   },   //PPG2
 /*   word  dac_numb[3] ;   Id_fan */   {  21,  (w)(1.00 * 512/_K_diskr) , -500   },   //PPG3
 /*   word  dac_numb[4] ;   Id_fan */   {  21,  (w)(1.00 * 512/_K_diskr) , -500   },   //PPG4
 /*   word  dac_numb[5] ; Id_dop_kod */ {  5 ,  (w)(1.00 * 256/_K_diskr) , 0   },   //PPG6
 /*   word  dac_numb[6] ;   PDF0m  */   {  10,  (w)(0.12 * 256/_K_diskr) , 0   } }, //PPG7
 /*   word  Rezerv_DAC [ 12 ] ;    */ { 0 },

 /*   byte  Ai_CS[_Ai_max];        */ { 2, 5, 9, 10, 4 }, // 0xff - нет канала.

 /*   byte  AS_CSo[_SOut_max];     */ { 2, 5, 8 },

 /*   byte  AS_CSi[_SInp_max];     */ { 0, 1, 3, 4, 6, 7 },

 /*   byte  PiS_Normal[_SInp_max]; */
                                      {
 /*         PiS_Normal[0]          */   0xfe,
 /*         PiS_Normal[1]          */   0xff,
 /*         PiS_Normal[2]          */   0xff,
 /*         PiS_Normal[3]          */   0xff,
 /*         PiS_Normal[4]          */   0xff,
 /*         PiS_Normal[5]          */   0xff
                                      },
 /*   byte  PoS_Normal[_SOut_max]; */
                                      {
 /*         PoS_Normal[0]          */   0x02,
 /*         PoS_Normal[1]          */   0x00,
 /*         PoS_Normal[2]          */   0x00
                                      },
 /*   union ConfigO  CfgO ;        */ { 0 },

#ifdef    _Sels_mashtP0
 /*   word   Sels_mashtP0 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_mashtM0
 /*   word   Sels_mashtM0 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_shift0
 /*   byte   Sels_shift0 ;         */ 1 ,
 /*   byte   rezerv0 ;             */ 0 ,
#endif

#ifdef    _Sels_mashtP1
 /*   word   Sels_mashtP1 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_mashtM1
 /*   word   Sels_mashtM1 ;        */ (w)( 1.00 * 256.) ,
#endif
#ifdef    _Sels_shift1
 /*   byte   Sels_shift1 ;         */ 1 ,
 /*   byte   rezerv1 ;             */ 0 ,
#endif

 /*   word  T_Pr;                  */     55*10, //гр. Цельсия
 /*   word  T_Av;                  */     85*10, //гр. Цельсия
 /*  word   Filtr_Param ;          */ 20 ,//0xDA85 ,
 /*  word   Ttr_predupr ;          */ 140 * 10 ,
 /*  word   Ttr_4mA ;              */ (w)(int)(-50.* 10) ,  //0.* 10 ,
 /*  word   Ttr_20mA ;             */ 200 * 10 ,            //250 * 10 ,

 /*  word   Filtr_Param_Nzad ;     */ 20 ,//0xDA85 ,
 /*  word   Nzad_4mA ;             */ _Skor_nom( 0 ) ,
 /*  word   Nzad_20mA ;            */ _Skor_nom( 1.00 ) ,

 /*  word   Id_Vkl_Vent ;          */  _Id_nom(0.10) ,
 /*  word   T_Otkl_Vent ;          */  _Sec( 2.0 * 60.0 ) ,

 /*   word   N_nom ;               */   740 , // 925 - для стенда .
 /*   word   RTMAX  ;              */  _Grad( 90 ) ,
 /*   word   T_zaderg_pusk ;       */  _Sec( 0.55 ) ,
 /*   word   Z_SkorNull ;          */ _Skor_nom( 0.0025 ) ,
 /*   word   Skor_Vkl_KZ ;         */ _Skor_nom( 1.0 ) ,
 /*   word   Skor_Otkl_KZ ;        */ _Skor_nom( 0.85 ) ,

 /*   word   Uset_nom ;         В  */  1390 , // 380 - для стенда .
 /*   word   Urot_nom ;         В  */  1200 , // 216 - для стенда .

 /*   word   Id_IU ;               */  _Id_nom(0.025) ,
 /*   word   i_count ;             */   6 ,

 /*   word   Mashtab_ZSkA;         */ (w)( 0.375 * 256.) ,
 /*   word   Mashtab_ZSkA_Vper_Gr; */ (w)( 0.901 * 256.) ,
 /*   word   Mashtab_ZSkA_Naz_Gr;  */ (w)( 0.901 * 256.) ,
 /*   word   Mashtab_ZSkA_Vper_NG; */ (w)( 0.210 * 256.) ,
 /*   word   Mashtab_ZSkA_Naz_NG;  */ (w)( 0.210 * 256.) ,

 /*   word   M_Zsk_Vper_Promeg;    */ (w)( 0.250 * 256.) ,
 /*   word   M_Zsk_Naz_Promeg;     */ (w)( 0.250 * 256.) ,
 /*   word   M_Zsk_Vper_Promeg_Gr; */ (w)( 0.250 * 256.) ,
 /*   word   M_Zsk_Naz_Promeg_Gr;  */ (w)( 0.250 * 256.) ,
 /*   word   M_Zsk_Vper_Promeg_NG; */ (w)( 0.210 * 256.) ,
 /*   word   M_Zsk_Naz_Promeg_NG;  */ (w)( 0.210 * 256.) ,

 /*   word   M_Zsk_Vper_Dotiag;    */ (w)( 0.065 * 256.) ,
 /*   word   M_Zsk_Naz_Dotiag;     */ (w)( 0.065 * 256.) ,
 /*   word   M_Zsk_Vper_Dotiag_Gr; */ (w)( 0.065 * 256.) ,
 /*   word   M_Zsk_Naz_Dotiag_Gr;  */ (w)( 0.065 * 256.) ,

 /*   word   M_Zsk_Vper_Posad;     */ (w)( 0.030 * 256.) ,
 /*   word   M_Zsk_Naz_Posad;      */ (w)( 0.030 * 256.) ,
 /*   word   M_Zsk_Vper_Posad_Gr;  */ (w)( 0.035 * 256.) ,
 /*   word   M_Zsk_Naz_Posad_Gr;   */ (w)( 0.035 * 256.) ,

 /*   word   Mashtab_Reviz;        */ (w)( 0.100 * 256.) ,

 /*   word   T_ZISkor_Reviz;       */ _Skor_nom( 0.015 ) ,

 /*   word   Id_Rastorm_max ;      */ _Id_nom ( 0.00 ) ,
 /*   word   Mashtab_Id_Rastorm ;  */ (w)( 0.00 * 256.) ,

 /*   word   NzMaxPromeg ;         */ _Skor_nom( 0.25 ),
 /*   word   NzMaxPromeg_Gr ;      */ _Skor_nom( 0.25 ),
 /*   word   NzMaxPromeg_NG ;      */ _Skor_nom( 0.20 ),
 /*   word   NzMaxDotiag ;         */ _Skor_nom( 0.06 ),
 /*   word   NzMaxDotiag_Gr ;      */ _Skor_nom( 0.06 ),
 /*   word   NzMaxPosad ;          */ _Skor_nom( 0.03 ),
 /*   word   NzMaxPosad_Gr ;       */ _Skor_nom( 0.03 ),
 /*   word   NzMaxRevizia ;        */ _Skor_nom( 0.15 ),

 /*   word   KRSP ;                */ (w)( 5.00 * 256.),
 /*   word   KRSI  ;               */  0 ,
 /*   word   KRSPIP ;              */ (w)( 0.00 * 256.) ,

 /*   word   T_ZadZ_Vp ;           */  _Sec( 0.0 ),
 /*   word   T_ZadZ_Nz ;           */  _Sec( 0.0 ),

 /*   word   Skor_TP_Avar ;        */ _Skor_nom( 0.20 ),
 /*   word   ReleMalSkor ;         */ _Skor_nom( 0.0100 ),
 /*   word   GistReleMalSkor ;     */ _Skor_nom( 0.0025 ),
 /*   word   NzadSmeshMax ;        */ _Skor_nom( 0.00 ),
 /*   word   Z_SkMin ;             */ _Skor_nom( 0.00 ),

 /*   word   KRSP_Ludi ;           */ (w)( 5.00 * 256.),
 /*   word   KRSI_Ludi  ;          */  0 ,
 /*   word   KRSPIP_Ludi ;         */ (w)( 0.00 * 256.) ,
 /*   word   KRSP_Gruz ;           */ (w)( 5.00 * 256.),
 /*   word   KRSI_Gruz  ;          */  0 ,
 /*   word   KRSPIP_Gruz ;         */ (w)( 0.00 * 256.) ,
 /*   word   KRSP_Negabarit ;      */ (w)( 5.00 * 256.),
 /*   word   KRSI_Negabarit  ;     */  0 ,
 /*   word   KRSPIP_Negabarit ;    */ (w)( 0.00 * 256.) ,
 /*   word   T_ZISkorP_LudiR ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorP_LudiT ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorM_LudiR ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorM_LudiT ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorP_GruzR ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorP_GruzT ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorM_GruzR ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorM_GruzT ;     */ _Skor_nom( 0.07 ) ,
 /*   word   T_ZISkorP_NgbrR ;     */ _Skor_nom( 0.05 ) ,
 /*   word   T_ZISkorP_NgbrT ;     */ _Skor_nom( 0.05 ) ,
 /*   word   T_ZISkorM_NgbrR ;     */ _Skor_nom( 0.05 ) ,
 /*   word   T_ZISkorM_NgbrT ;     */ _Skor_nom( 0.05 ) ,
 /*   word   T_dN_Max ;            */  _Sec( 1.5 ),

 /*   word   Temp_RT_P ;           */  100 * _Id_Nom200 ,
 /*   word   Temp_RT_M ;           */  100 * _Id_Nom200 ,
 /*   word   KRTPRI ;              */  10*64 ,
 /*   word   KRTNI ;               */  20*64 ,
 /*   word   KRTP ;                */  (w)( 0.50 * 256.) ,

 /*   word   Z_SkMax_bezKZ ;       */ _Skor_nom( 0.90 ) ,
 /*   word   Id_Vkl_VentShs1;      */ _Id_nom(0.10) ,
 /*   word   TimeAvarNoVent        */ _Sec( 10.0 ),     // SAP 3 sek
 /*   word   Id_min_vent;          */ _Id_nom(0.10),
 /*   word   Id_max_vent;          */ _Id_nom(0.50),
 /*   word   Time_otkl_BV1 ;       */ _Sec( 0.5 * 60.0 ) ,            //59
 /*  word   Id_zad_fors;           */ _Id_nom(0.60) ,   // SAP 1.10
 /*    float  T0Volt               */-50,
 /*    float  TempT;               */10,
 /*    byte   Time_o               */_Sec( 1.0 ) ,
 /*    float  Pimp_max             */{12.0, 12.0} ,   // 70A      ; 1.3 * 2.57 V = 3.34 V
                                                       // нормальное значение - 2.57 V
/*    float  Pimp_min              */ {6.6, 7.0} ,   // 10A      ; 0.7 * 2.57 V = 1.80 V
 /*    float  mV_A ;               */   9.3,    // mV/kГц    1А = 58 мВ/кГц   SAP 9.1,

 /*    float dt_Av;                */ 10.0,

 /*   word   N_490 ;               */ _Skor_nom( 0.98 ) ,
 /*   word   Z_Sk_mestnoe ;        */ _Skor_nom( 0.00 ) ,
 
 /*   word   Time_ComtrolPIU;      */  _Sec(1800), //30 мин

 /*   word  rezerv[  95 ] ;        */ { 0 },

#ifdef _INTERPRETER
 /*   struct SetpointData MemData; */ { 0 },
#endif

 /*   byte  Contrl_sum ;           */   0
  } ;

//----------------------
//    Блок уставок не восстанавливаемый по команде "F9-Типовые уставки":
//  для возможности задание номиналов датчиков и т.д.
_x_far const struct SBlok_Ustavok _sc =
  {
      //  Уставки номиналов: 1дискрета = 1А, 1В.                           // У АД Iф.действ. = 650 А , соответственно
                                       {   {  0, 0 },                      // Id = 650/0.816 = 800 А , но настраиваем Id = 600 A .
 /* struct  {  word  oe , fe ;  } Id ; */     { _Id_nom( 1.0 ), 600 },     // Uрот.действ. = 1200 В , соответственно
 /* struct  {  word  oe , fe ;  } Ud ; */     { _Ud_nom( 1.0 ), 1620 },    // Ud = 1.35*1200 = 1620 В .
 /* struct  {  word  oe , fe ;  } Iv ; */     { _Iv_nom( 1.0 ),  10*10 },  // Ud считать в привязке к Uрот , а не U2тр-ра , т.к. оно никак не станет больше роторного .
 /* struct  {  word  oe , fe ;  } N  ; */     { _Skor_nom( 1.0 ), 71*10}},
      //  таблица номиналов датчиков:
 /* word   Id  ;                       */     {  600,
 /* word   Ud  ;                       */        1620,
 /* word   Iv  ;                       */         10*10,
 /* word   N   ;                       */         71*10 },  // Передаточное число редуктора 10.426 . Т.е. N редукт = 740.25/10.426 = 71 об/мин .

 /* word Contrl_sum;                   */    0
  };

        /*   Матрица контант задающих постоянные времени для сигналов
         * порта P0.
         *   Каждому сигналу порта задается своя постоянная времени.
         * Самый младший элемент матрицы соответтвует самому младшему
         * разряду порта, самый старший - самому старшему.
         */
_x_far const word  P0_tu [ 8 ] = { _Drb_msec( 25 ), _Drb_msec( 200),
                            _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ) } ;

_x_far const word  P1_tu [ 8 ] = { _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 50 ), _Drb_msec( 50 ),
                            _Drb_msec( 20 ), _Drb_msec( 20 ),
                            _Drb_msec(  0 ), _Drb_msec(  0 ) } ;

_x_far const word  PS_tu [_SInp_max][ 8 ] = {
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       },
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       },
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       },
                                       {_Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 ),
                                        _Drb_msec( 50 ), _Drb_msec( 50 )
                                       }
                                      };
union Prt16 Prt_NULL , Prt_NULL2 ;
//bool Trg_Pusk, Pusk_old, Trg_IzmTemp;
word TimeDelay_Temper;
// Обязательно во внутреней памяти, т.к. внешняя шина еще не проинициализарована
// и параметры в конструкторе не будут установлены.
#pragma location = "RAM_region"
TemperatureSensorMonitor DTMonitor(_Dat_Temp_All/2, &_or.dt_Av);
IzmTemp_Data TIzm[_MaxChannel];
word Time_Pr_Dat_temp[_Dat_Temp_All], Time_Av_Dat_temp[_Dat_Temp_All];
word IzmTempLabel;
word Time_tst_sp, dTime_tst_sp;
word Av_Dat, Avv_Dat, Bit_PrAvar;
word FanSpeedMax;
word Time_RMS_On, Time_RMS_Off;
word Nrot_CAN;
Av_DT Av_DT_Str, Pr_DT_Str;
word t_fan;           // максимальная температура за измерение
word Id_fan ;          // задание на вентилятор
word timerVentAvar;   // выдержка времнеи при неисправности вентилятора
word Time_bo_SN_On;
Prt16  DT_Cond[2];
// измер. темпер.
word Time_tst, Time_tst_PIU;
word channelTemp, Channel_Max_izm;
float Volt[2];
float Amper[2];
float Time_Cikl;
word Time_Cikl1;
word VoltMax;
word TimeDelay;
word TimeBlockIzm;
word Id_IU ;
word i_prer , i_nepr ;
word  Temper[_Dat_Temp_All];
float fTemper[2][_Dat_Temp_All/2];
word  Counter_Izm_T;
word T_CAN0 ;
byte Agregat ;
union flagO flgO ;
union ATKflag ATK_flg ;

//struct  fil  Id_flt ;
word  Irot_full , Irot , dIrot ;
word  Istat; //Ток статора для отображения на приборе
struct MSG_regs Ap2_Msg; //регистры сообщений из АР2
word  N_rot ;
word  canId_zad ;
word  Time_Pusk ;
word  Time_do_OtklImpPusk ;
word  Id_deystv ;
word  Time_Reg ;
word  OuRegS_ogr ;

word  OIRT_for_revers ;
float Beta , CosLrot , CosLrot_istin ;

float OmegaNom , OmegaNullSynhr , N_ob_minSynhr , N_ob_min ;
float Kform , Mom , Mom_nom ;
word  Srot ;
word  Pary_AD ;

word  Time_Reversor ;

//word  T_ZadZ ;
//word  NzadSmesh , Z_Skor_ind ;
word  dZ_Sk ;
word  SkorPDF ;

word Ist_SA ; // DAN 12.04.2025 14:15
word fr1,fr2;
//byte  Ludi_temp ;
//byte  Gruz_temp ;
//byte  Negabarit_temp ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union Prt Prt_NULL , Prt_NULL2 ;

extern word Id_IU ;
extern word i_prer , i_nepr ;

extern word T_CAN0 ;
extern byte Agregat ;
extern union flagO flgO ;
extern union ATKflag ATK_flg ;

//extern struct  fil  Id_flt ;
extern word  Irot_full , Irot , dIrot ;
extern word  N_rot ;
extern word  canId_zad ;
extern word  Time_Pusk ;
extern word  Time_do_OtklImpPusk ;
extern word  Id_deystv ;
extern word  Time_Reg ;
extern word  OuRegS_ogr ;

extern word  OIRT_for_revers ;
extern float Beta , CosLrot , CosLrot_istin ;

extern float OmegaNom , OmegaNullSynhr , N_ob_minSynhr , N_ob_min ;
extern float Kform , Mom , Mom_nom ;
extern word  Srot ;
extern word  Pary_AD ;

extern word  Time_Reversor ;

//extern word  T_ZadZ ;
//extern word  NzadSmesh , Z_Skor_ind ;
extern word  dZ_Sk ;
extern word  SkorPDF ;

extern word Ist_SA ; // DAN 12.04.2025 14:15

//extern byte  Ludi_temp ;
//extern byte  Gruz_temp ;
//extern byte  Negabarit_temp ;

extern  struct        oBlok_Ustavok   _or ;
extern  _x_far const struct  oBlok_Ustavok   _oc ;
extern  _x_far const struct  SBlok_Ustavok   _sc ;

extern _x_far const word  P0_tu [ 8 ] ;
extern _x_far const word  P1_tu [ 8 ] ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
