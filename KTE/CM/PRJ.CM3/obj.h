#ifndef _obj_h
#define _obj_h

//Переменые для определения размера областей уставок
#define  _kol_obl    ( 1 ) // Количество областей уставок
extern   word  read_rezerv( void ) ;

             // отключаемся от CAN при перезагрузке уставок.
#define can_obj_stop()  can_stop( _CAN0_Port ) = 1
             // подключается к CAN после перезагрузки уставок.
#define can_obj_start()  can_stop( _CAN0_Port ) = 0


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

//Количество дискретных портов на синхронном порту

#define    _SInp_max       4
#define    _SOut_max       2

//Количество ЦАПов ( по умолчанию их 3 шт. )
//#undef  _DAC_numb_max
//#define _DAC_numb_max
//------------------------------
// Номер PPG , используемого как DAC2 :
#define    _PPG_for_DAC2    4
//------------------------------
// Задать номера PPG , используемых как ЦАП . Необходимо еще перезадать выше количество ЦАПов .
// PPG0, PPG1 используются для суммы ИУ мостов Вперед и Назад .
// PPG2, PPG3 используются для суммы ИУ мостов Вперед и Назад 12-ти пульсного СИФУ ( при его наличии ) .
// PPG5 используется для суммы ИУ встроенного возбудителя ( при его наличии ) .
//#define  _PPG_for_DAC3    6
//#define  _PPG_for_DAC4    7
//------------------------------

// Как правило , у мощных агрегатов специфические выходные каскады :
//#undef   _FzapolnShort_Low
//#define  _FzapolnShort_Low      _MkSec( 25 )  // длительность нулевого импульса в мкс
//#undef   _FzapolnShort_High
//#define  _FzapolnShort_High     _MkSec( 25 )  // длительность единичного импульса в мкс

#undef     _AD_Delta
#define    _AD_Delta         1    // Для точной установки нуля на 12-разрядном АЦП .

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

/*ДДД Привязка программных имен к аппаратным входам/выходам ДД-*/

            /*  Дискретные выходы  */

#define    bo_Avar               Po0_c._.n0
#define    bo_Predupr            Po0_c._.n1
#define    bo_Gotov              Po0_c._.n2
#define    bo_MT                 Po0_c._.n3
//#define  bo_                   Po0_c._.n4
//#define  bo_                   Po0_c._.n5
#define    bo_Vkl_QK1            Po0_c._.n6 // Аппаратно не существует .
//#define  bo_                   Po0_c._.n7 // Аппаратно не существует .

//#define  bo_                   PoS_c[0]._.n0
//#define  bo_                   PoS_c[0]._.n1
//#define  bo_                   PoS_c[0]._.n2
//#define  bo_                   PoS_c[0]._.n3
//#define  bo_                   PoS_c[0]._.n4
//#define  bo_                   PoS_c[0]._.n5
//#define  bo_                   PoS_c[0]._.n6
//#define  bo_                   PoS_c[0]._.n7

// Порт для выходов , которые никуда не выводятся :
#define    bo_Insulat            Prt_NULL._.n0
//#define  bo_                   Prt_NULL._.n1
//#define  bo_                   Prt_NULL._.n2
//#define  bo_                   Prt_NULL._.n3
//#define  bo_                   Prt_NULL._.n4
//#define  bo_                   Prt_NULL._.n5
//#define  bo_                   Prt_NULL._.n6
//#define  bo_                   Prt_NULL._.n7

            /*  Дискретные входы   */

#define    bi_2P24               Pi0_f._.n0
#define    bi_QK1                Pi0_f._.n1
#define    bi_AK1                Pi0_f._.n2
#define    bi_AR1                Pi0_f._.n3
//#define  bi_                   Pi0_f._.n4
#define    bi_AF1P               Pi0_f._.n5
#define    bi_GL1                Pi0_f._.n6
#define    bi_DS1              ( Pi0_f._.n7 == 1 || Klav_Buff == _Reset )

//--------------------------------------------------------------------------
 // Не перепутать ! Номер INT и номер в Порту 1 - НЕ совпадают :

#define    bi_KF_VKask           Pi1_f._.n4  // KF  - INT4
#define    bi_KFV_VKask          Pi1_f._.n5  // KFT - INT3
#define    bi_Gercon             Pi1_nm._.n6 // 1B  - INT0
//#define  bi_GerconAC2          Pi1_nm._.n7 // 2B  - INT1
//--------------------------------------------------------------------------

#define    bi_VR1                PiS_f[0]._.n0
#define    bi_Vnesh_Avar       ( PiS_f[0]._.n1 /*|| Klav_Buff == _Stop*/ ) // пр.127
#define    bi_Razresh_Vkl        PiS_f[0]._.n2
#define    bi_Vent_Dvig          PiS_f[0]._.n3
//#define  bi_                   PiS_f[0]._.n4
//#define  bi_                   PiS_f[0]._.n5
#define    bi_Iv_TG              PiS_f[0]._.n6  // пр.114
//#define  bi_                   PiS_f[0]._.n7

#define    bi_Bolshe             PiS_f[1]._.n0
#define    bi_Menshe             PiS_f[1]._.n1
#define    bi_Rab_Tolch          PiS_f[1]._.n2
//#define  bi_                   PiS_f[1]._.n3
#define    bi_TB                 PiS_f[1]._.n4
#define    bi_TH                 PiS_f[1]._.n5
#define    bi_Zapret             PiS_f[1]._.n6
#define    bi_Gashenie           PiS_f[1]._.n7

//#define  bi_MT                 PiS_f[X]._.nX // б.к. механического тормоза

//#define  bi_KTE_rezerv1        0
//#define  bi_GerconDC           0
//#define  bi_KP                 0 // Контроль питания усилителей мощности Выходных Каскадов .
#define    bi_KTE_rezerv         0
#define    bi_AK2                1 // Если нет блок-контакта Q2 - для функционирования нового алгоритма Q2V .
#define    bi_AF1                0 // Аварийный сигнал только при предохранителях .
#define    bi_Fors_Temp          0 // Для форсированного торможения

//-------------------
#define  _ACh0_txt      "n0 -Id      "
#define  _ACh1_txt      "n1 -резерв  "
#define  _ACh2_txt      "n2 -резерв  "
#define  _ACh3_txt      "n3 -Тахоген."
#define  _ACh4_txt      "n4 -N#      "
#define  _ACh5_txt      "n5 -Ud      "
#define  _ACh6_txt      "n6 -резерв  "
#define  _ACh7_txt      "n7 -резерв  "
#define  _ACh8_txt      "n8 -резерв  "
#define  _ACh9_txt      "n9 -резерв  "
#define  _ACh10_txt     "n10-резерв  "
#define  _ACh11_txt     "n11-резерв  "
#define  _ACh12_txt     "n12-резерв  "
#define  _ACh13_txt     "n13-резерв  "
#define  _ACh14_txt     "n14-If      "
#define  _ACh15_txt     "n15-Резистор"
#define  _ACh16_txt     "AN-P24      "
#define  _ACh17_txt     "AN-N12      "
#define  _ACh18_txt     "AN-P12      "

            /*  Аналоговые входы  */

#define    Id_mg_ach            _ar.n00_ach
//#define  _ach                 _ar.n01_ach
//#define  _ach                 _ar.n02_ach
#define    TG_ach               _ar.n03_ach
#define    Z_sk_ach             _ar.n04_ach
#define    Ud_ach               _ar.n05_ach
//#define  _ach                 _ar.n06_ach
//#define  _ach                 _ar.n07_ach
//#define  _ach                 _ar.n08_ach
//#define  _ach                 _ar.n09_ach
//#define  _ach                 _ar.n10_ach
//#define  _ach                 _ar.n11_ach
//#define  _ach                 _ar.n12_ach
//#define  _ach                 _ar.n13_ach
#define    Iv_ach               _ar.n14_ach
#define    Zad_res_ach          _ar.n15_ach
//#define  Z_sk_ach             Zad_res_ach

#define    P24_ach              _ar.n16_ach
#define    P12_ach              _ar.n18_ach
#define    N12_ach              _ar.n17_ach
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//----------- A8 -  Битовые объектные уставки ------------

  //#define _KTE_A8_ConfigObj
//--------------------------------------------------------

     //  Объектное Конфигурирование
 union ConfigO {
  word all ;
  struct  {
      word rezerv0     : 1 ;
      word rezerv1     : 1 ;
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

/*union flagO {
  word all ;
  struct  {
      word rezerv0     : 1 ;
      word rezerv1     : 1 ;
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
} ;*/

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

#ifdef _Dat_Temp_Max
    double  T_Scale[_Dat_Temp_Max];  //float  T_Scale[_Dat_Temp_Max];

    word   T_Pr;
    word   T_Av;
#endif

    word   Filtr_Param ;
    word   Ttr_predupr ;
    word   Ttr_4mA ;
    word   Ttr_20mA ;

    word   Filtr_Param_Nzad ;
    word   Nzad_4mA ;
    word   Nzad_20mA ;

    word   Id_Vkl_Vent ;
    word   T_Otkl_Vent ;

    word   rezerv[ 32 ] ;

#ifdef _INTERPRETER
    struct SetpointData MemData;
#endif

    byte  Contrl_sum ;
  } ;

//-------------- А7 - Объектные уставки ------------------

    //#define _A7_Obj_Ust \

//------------ А6 - Объектная индикация ------------------

    //#define _A6_Obj_Ind \

//--------- F1 - Объектные переменные для следа ----------

    //#define _Sld_cnst_Obj \

//------------ AD - Объектный вывод на ЦАП ---------------

    //#define _AD_Obj_DAC \

//------- FB - Объектные переменные для журнала ----------

    //#define _Jrn_cnst_Obj\

//------ K6 - Объектные переменные в комб.редакт ---------

    //#define _OBJ_COMB_REDACT \


//--------------------------------------------------------

/*------------------------------------------------*/
#ifdef  _OBJ_INCLUDE
/*------------------------------------------------*/

struct  oBlok_Ustavok  _or  ;

_x_far const  struct  oBlok_Ustavok  _oc   =
  {
 /*   word  dac_numb[0] ;   sys    */ { {  0 ,  (w)(0.12 * 256)     , 0   },   //DA0
 /*   word  dac_numb[1] ;   Iv#    */   {  3 ,  1.00 * 256/_K_diskr , 0   },   //DA1->PPG8
 /*   word  dac_numb[2] ;          */   {  0 ,  (w)(0.12 * 256)     , 0   } }, //PPG4
 /*   word  Rezerv_DAC [ 12 ] ;    */ { 0 },

 /*   byte  Ai_CS[_Ai_max];        */ { 2, 5, 9, 10, 4 }, // 0xff - нет канала.

 /*   byte  AS_CSo[_SOut_max];     */ { 2, 5 },

 /*   byte  AS_CSi[_SInp_max];     */ { 0, 1, 3, 4 },

 /*   byte  PiS_Normal[_SInp_max]; */
                                      {
 /*         PiS_Normal[0]          */   0xfc,
 /*         PiS_Normal[1]          */   0xff,
 /*         PiS_Normal[2]          */   0xff,
 /*         PiS_Normal[3]          */   0xff
                                      },
 /*   byte  PoS_Normal[_SOut_max]; */
                                      {
 /*         PoS_Normal[0]          */   0x00,
 /*         PoS_Normal[1]          */   0x00
                                      },
 /*   union ConfigO  CfgO ;        */   0,

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

#ifdef _Dat_Temp_Max
 /*  double T_Scale[_Dat_Temp_Max];  */  { 1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,
                                          1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00,1.00 },
 /*   word  T_Pr;                  */     55*10, //гр. Цельсия
 /*   word  T_Av;                  */     85*10, //гр. Цельсия
#endif

 /*  word   Filtr_Param ;          */ 20 ,//0xDA85 ,
 /*  word   Ttr_predupr ;          */ 140 * 10 ,
 /*  word   Ttr_4mA ;              */ (w)(int)(-50.* 10) ,  //0.* 10 ,
 /*  word   Ttr_20mA ;             */ 200 * 10 ,            //250 * 10 ,

 /*  word   Filtr_Param_Nzad ;     */ 20 ,//0xDA85 ,
 /*  word   Nzad_4mA ;             */ _Skor_nom( 0 ) ,
 /*  word   Nzad_20mA ;            */ _Skor_nom( 1.00 ) ,

 /*  word   Id_Vkl_Vent ;          */  _Id_nom(0.10) ,
 /*  word   T_Otkl_Vent ;          */  _Sec( 2.0 * 60.0 ) ,

 /*   word  rezerv[ 32 ] ;          */ { 0 },

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
      //  Уставки номиналов: 1дискрета = 1А, 1В.
                                       {   {  0, 0 },
 /* struct  {  word  oe , fe ;  } Id ; */     { _Id_nom( 1.0 ), 500 },
 /* struct  {  word  oe , fe ;  } Ud ; */     { _Ud_nom( 1.0 ), 440 },
 /* struct  {  word  oe , fe ;  } Iv ; */     { _Iv_nom( 1.0 ),  10*10 },
 /* struct  {  word  oe , fe ;  } N  ; */     { _Skor_nom( 1.0 ), 500 } },
      //  таблица номиналов датчиков:
 /* word   Id  ;                       */     {  500,
 /* word   Ud  ;                       */        440,
 /* word   Iv  ;                       */         10*10,
 /* word   N   ;                       */        500 },

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

union Prt Prt_NULL;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union Prt Prt_NULL;

extern  struct        oBlok_Ustavok   _or ;
extern  _x_far const struct  oBlok_Ustavok   _oc ;
extern  _x_far const struct  SBlok_Ustavok   _sc ;

extern _x_far const word  P0_tu [ 8 ] ;
extern _x_far const word  P1_tu [ 8 ] ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
