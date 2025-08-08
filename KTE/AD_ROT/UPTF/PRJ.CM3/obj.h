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
 #define T1_MR1_Int() SkorAD_Interrupt () //Revers_Interrupt ()
 #define T1_MR2_Int()
 #define T1_MR3_Int()

 #define T1_CR0_Int()
 #define T1_CR1_Int()

 #define T2_MR0_Int()
 #define T2_MR1_Int()
 #define T2_MR2_Int() //S_Interrupt ()
 #define T2_MR3_Int()

 #define T2_CR0_Int()
 #define T2_CR1_Int()

 #define T3_MR0_Int()
 #define T3_MR1_Int() //S2_Interrupt ()
 #define T3_MR2_Int()
 #define T3_MR3_Int()

 #define T3_CR0_Int()
 #define T3_CR1_Int()
//------------------------

//Количество дискретных портов на синхронном порту

#define    _SInp_max       4
#define    _SOut_max       2

//Количество ЦАПов ( по умолчанию их 3 шт. )
#undef  _DAC_numb_max
#define _DAC_numb_max         2
//------------------------------
// Номер PPG , используемого как DAC2 :
//#define    _PPG_for_DAC2    4
//------------------------------
// Задать номера PPG , используемых как ЦАП . Необходимо еще перезадать выше количество ЦАПов .
// PPG0, PPG1 используются для суммы ИУ мостов Вперед и Назад .
// PPG2, PPG3 используются для суммы ИУ мостов Вперед и Назад 12-ти пульсного СИФУ ( при его наличии ) .
// PPG5 используется для суммы ИУ встроенного возбудителя ( при его наличии ) .
//#define  _PPG_for_DAC3    6
//#define  _PPG_for_DAC4    7
//------------------------------

// Выходные каскады для УПТФ и АТК :
#undef     _FzapolnShort_Low
#define    _FzapolnShort_Low      _MkSec( 80 )  // длительность нулевого импульса в мкс
#undef     _FzapolnShort_High
#define    _FzapolnShort_High     _MkSec( 25 )  // длительность единичного импульса в мкс

#undef     _AD_Delta
#define    _AD_Delta         1    // Для точной установки нуля на 12-разрядном АЦП .

//------------------------------------------

// Убираем Регуляторы из Рабочей Структуры :
//#define _Prg_Rabota  ( _ZadSkor | _RegSk | _RegTok | _Sled | _RN | _RP )
#undef    _Prg_Rabota
#define   _Prg_Rabota  ( _ZadSkor | _Sled )

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

#define    bo_Avar               Po0_c._.n0 // K1
#define    bo_Predupr            Po0_c._.n1 // K3
#define    bo_Gotov              Po0_c._.n2 // K2
#define    bo_Zatyan_Pusk        Po0_c._.n3 // K4
#define    bo_Vkl_Kontaktora_KZ  Po0_c._.n4 // K5
#define    bo_VklVent            Po0_c._.n5 // K6
//#define  bo_                   Po0_c._.n6
//#define  bo_                   Po0_c._.n7

//#define  bo_Otkl_Kontaktora_KZ PoS_c[0]._.n0 // K7
//#define  bo_                   PoS_c[0]._.n1
//#define  bo_                   PoS_c[0]._.n2
//#define  bo_                   PoS_c[0]._.n3
//#define  bo_                   PoS_c[0]._.n4
//#define  bo_                   PoS_c[0]._.n5
//#define  bo_                   PoS_c[0]._.n6
//#define  bo_                   PoS_c[0]._.n7

// Порт для выходов , которые никуда не выводятся :
#define    bo_Insulat            Prt_NULL._.n0
#define    bo_Vkl_QK1            Prt_NULL._.n1
#define    bo_MT                 Prt_NULL._.n2
#define    bo_GotovZak           Prt_NULL._.n3  // Готовность Заказчика - пропадает при пуске .
//#define  bo_                   Prt_NULL._.n4
//#define  bo_                   Prt_NULL._.n5
//#define  bo_                   Prt_NULL._.n6
//#define  bo_                   Prt_NULL._.n7

            /*  Дискретные входы   */

#define    bi_2P24               Pi0_f._.n0
#define    bi_SF2                Pi0_f._.n1
#define    bi_KF1                Pi0_f._.n2
#define    bi_KF2                Pi0_f._.n3
#define    bi_TR                 Pi0_f._.n4
#define    bi_AF1P               Pi0_f._.n5
#define    bi_Kontaktor_KZ       Pi0_f._.n6    // К11 - интерфейсное реле .
#define    bi_DS1              ( Pi0_f._.n7 == 1 || Klav_Buff == _Reset )

//--------------------------------------------------------------------------
 // Не перепутать ! Номер INT и номер в Порту 1 - НЕ совпадают :

//#define  bi_KF_VKask           Pi1_f._.n4  // KF  - INT4
//#define  bi_KFV_VKask          Pi1_f._.n5  // KFT - INT3
//#define  bi_Gercon             Pi1_nm._.n6 // 1B  - INT0
//#define  bi_GerconAC2          Pi1_nm._.n7 // 2B  - INT1

// 03.05.2018 13:00 - В связи с тем , что плата Геркона S421 по включению питания выдаёт нуль на 2мс и более ,
//                    процессор успевает вскочить в режим программирования , привязан на INT0 .
//                    Аппаратчики не смогли побороть начальные глюки S421 , поэтому геркон привязали на 2В ,
//                    благо Q1V не нужен для УПТФ .
#define    bi_Gercon             Pi1_nm._.n7 // 1B  - INT1
//--------------------------------------------------------------------------

//#define  bi_                   PiS_f[0]._.n0
#define    bi_Pusk_0_1          (PiS_f[0]._.n1== 1 || can_ConfigReg ( _CAN_P01 )== 1)   // K8  - интерфейсное реле .
#define    bi_Pusk_1_0          (PiS_f[0]._.n2== 1 || can_ConfigReg ( _CAN_P10 )== 1)   // К9  - интерфейсное реле .
#define    bi_QK1                PiS_f[0]._.n3  // Питание статора .                    // К10 - интерфейсное реле .
//#define  bi_                   PiS_f[0]._.n4
//#define  bi_                   PiS_f[0]._.n5
//#define  bi_                   PiS_f[0]._.n6
//#define  bi_                   PiS_f[0]._.n7


//#define  bi_KTE_rezerv1        0
//#define  bi_GerconDC           0
//#define  bi_KP                 0 // Контроль питания усилителей мощности Выходных Каскадов .
#define    bi_Fors_Temp          0
#define    bi_KF_VKask           1
#define    bi_KTE_rezerv         0
#define    bi_Razresh_Vkl        1
#define    bi_Vnesh_Avar         0
#define    bi_VR1              ( bi_QK1 == 0 )
#define    bi_AK2                1 // Если нет блок-контакта Q2 - для функционирования нового алгоритма Q2V .
#define    bi_AK1                1
#define    bi_AR1                0
#define    bi_AF1                0 // Аварийный сигнал только при предохранителях .

//-------------------
#define  _ACh0_txt      "n0 -Id      "
#define  _ACh1_txt      "n1 -резерв  " //"n1 -Id-sr   "
#define  _ACh2_txt      "n2 -TV      "
#define  _ACh3_txt      "n3 -Uac     "
#define  _ACh4_txt      "n4 -Uba     "
#define  _ACh5_txt      "n5 -резерв  "
#define  _ACh6_txt      "n6 -резерв  "
#define  _ACh7_txt      "n7 -резерв  "
#define  _ACh8_txt      "n8 -резерв  "
#define  _ACh9_txt      "n9 -резерв  "
#define  _ACh10_txt     "n10-резерв  "
#define  _ACh11_txt     "n11-IA      "
#define  _ACh12_txt     "n12-IB      "
#define  _ACh13_txt     "n13-IC      "
#define  _ACh14_txt     "n14-резерв  "
#define  _ACh15_txt     "n15-Резист. "
#define  _ACh16_txt     "AN-P24      "
#define  _ACh17_txt     "AN-N12      "
#define  _ACh18_txt     "AN-P12      "

            /*  Аналоговые входы  */

#define    Id_mg_ach            _ar.n00_ach
//#define  Id_sr_ach            _ar.n01_ach
#define    Izm_T_ach            _ar.n02_ach  // TV
#define    Uac_ach              _ar.n03_ach
#define    Uba_ach              _ar.n04_ach
//#define  _ach                 _ar.n05_ach
//#define  _ach                 _ar.n06_ach
//#define  _ach                 _ar.n07_ach
//#define  _ach                 _ar.n08_ach
//#define  _ach                 _ar.n09_ach
//#define  _ach                 _ar.n10_ach
#define    IA_ach               _ar.n11_ach
#define    IB_ach               _ar.n12_ach
#define    IC_ach               _ar.n13_ach
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
      word sld_PWM          : 1 ;
      word Avar_After_KZ    : 1 ;
      word rezerv2          : 1 ;
      word rezerv3          : 1 ;

      word rezerv4          : 1 ;
      word rezerv5          : 1 ;
      word rezerv6          : 1 ;
      word rezerv7          : 1 ;
     //----
      word rezerv8          : 1 ;
      word rezerv9          : 1 ;
      word rezerv10         : 1 ;
      word rezerv11         : 1 ;

      word rezerv12         : 1 ;
      word rezerv13         : 1 ;
      word rezerv14         : 1 ;
      word rezerv15         : 1 ;
    } _ ;
} ;

#define   _cfgO_sld_PWM          ((w) 0x0001 )
#define   _cfgO_Avar_After_KZ    ((w) 0x0002 )
//#define _cfgO_rezerv2          ((w) 0x0004 )
//#define _cfgO_rezerv3          ((w) 0x0008 )


//#define _cfgO_rezerv4          ((w) 0x0010 )
//#define _cfgO_rezerv5          ((w) 0x0020 )
//#define _cfgO_rezerv6          ((w) 0x0040 )
//#define _cfgO_rezerv7          ((w) 0x0080 )

union flagO {
  word all ;
  struct  {
      word NeFaznRot   : 1 ;
      word trig_Pusk   : 1 ;
      word new_tyr     : 1 ;
      word Pusk_OK     : 1 ; // Для УПТФ .

      word VShunt1     : 1 ; // Для УПТФ .
      word VShunt2     : 1 ; // Для УПТФ .
      word VShunt3     : 1 ; // Для УПТФ .
      word KZ          : 1 ;
     //----
      word V_trig      : 1 ;
      word Sploshnyak  : 1 ; // Для АТК .
      word rezerv10    : 1 ;
      word rezerv11    : 1 ;

      word KZ_command  : 1 ; // Для УПТФ .
      word KZ_trig     : 1 ; // Для УПТФ .
      word rezerv14    : 1 ;
      word rezerv15    : 1 ;
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

    word   Filtr_Param ;
    word   Ttr_predupr ;
    word   Ttr_4mA ;
    word   Ttr_20mA ;

    double T_Scale ;
    word  T_Pr ;
    word  T_Av ;

    word   T_zaderg_pusk ;
    word   Time_Sploshnyak ;
    word   Time_Zatyan_Pusk ;
    word   Time_snyatIU_KZ ;
    word   Pusk_0_1 ;
    word   Pusk_1_0 ;
    word   N_min[4] ;
    word   Alfa_min_time ;
    word   Alfa_Min_Shunt ;
    word   Alfa_Shunt ;
    word   I_Ogr ;
    word   Udnom ;
    word   rezerved[ 4 ] ;
    float  Rsigma ;
    float  Xsigma ;
    float  Tf_aper ;
    float  Tfil ;
    word   Pary_AD ;
    word   T_Id_flt ;
    word   T_Otkl_Vent ;
    word   T_min_Pusk ;
    word   ZIS_Nachal ;
    word   T_vkl_KZ ;
    word   Alfa_Shunt2 ;
    word   Alfa_Shunt3 ;

    float  Km ;
    word   Pnom ;
    word   Istat ;

    word   I_rot_nom ;
    word   T_otkl_KZ ;

    word   rezerv[ 130 ] ;

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

//--------------------------------------------------------

/*------------------------------------------------*/
#ifdef  _OBJ_INCLUDE
/*------------------------------------------------*/

struct  oBlok_Ustavok  _or  ;

_x_far const  struct  oBlok_Ustavok  _oc   =
  {
 /*   word  dac_numb[0] ;   sys  N */ { {  3 , (w)(0.12 * 256.) , 0   },   //DA0
 /*   word  dac_numb[1] ;        L */   {  0 , (w)(0.020* 256.) , 0   } }, //PPG8
 /*   word  Rezerv_DAC [ 12 ] ;    */ { 0 },

 /*   byte  Ai_CS[_Ai_max];        */ { 2, 5, 9, 10, 4 }, // 0xff - нет канала.

 /*   byte  AS_CSo[_SOut_max];     */ { 2, 5 },

 /*   byte  AS_CSi[_SInp_max];     */ { 0, 1, 3, 4 },

 /*   byte  PiS_Normal[_SInp_max]; */
                                      {
 /*         PiS_Normal[0]          */   0xff,
 /*         PiS_Normal[1]          */   0xff,
 /*         PiS_Normal[2]          */   0xff,
 /*         PiS_Normal[3]          */   0xff
                                      },
 /*   byte  PoS_Normal[_SOut_max]; */
                                      {
 /*         PoS_Normal[0]          */   0x00,
 /*         PoS_Normal[1]          */   0x00
                                      },
 /*   union ConfigO  CfgO ;        */ { 0 } ,

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

 /*  word   Filtr_Param ;          */ 20 ,//0xDA85 ,
 /*  word   Ttr_predupr ;          */ 140 * 10 ,
 /*  word   Ttr_4mA ;              */ (w)(int)(-50.* 10) ,  //0.* 10 ,
 /*  word   Ttr_20mA ;             */ 200 * 10 ,            //250 * 10 ,

 /*  double T_Scale ;              */ 1.00 ,
 /*  word   T_Pr ;                 */ 50*10, //гр. Цельсия
 /*  word   T_Av ;                 */ 85*10, //гр. Цельсия

 /*   word   T_zaderg_pusk ;       */  _Sec( 1.87 ) ,
 /*   word   Time_Sploshnyak ;     */  _Sec( 3 ) ,
 /*   word   Time_Zatyan_Pusk ;    */  _Sec( 60 ) ,
 /*   word   Time_snyatIU_KZ ;     */  _Sec( 2 ) ,
 /*   word   Pusk_0_1 ;            */  _Skor_nom( 0.1 ) ,
 /*   word   Pusk_1_0 ;            */  _Skor_nom( 1.0 ) ,
 /*   word   N_min;                */{ _Skor_nom(0.3), _Skor_nom(0.6), _Skor_nom(0.7), _Skor_nom(0.91) },
 /*   word   Alfa_min_time ;       */  _fSec( 0.06 ),
 /*   word   Alfa_Min_Shunt ;      */  _Grad( 6 ) ,
 /*   word   Alfa_Shunt ;          */  _Grad( 60 ) ,
 /*   word   I_Ogr ;               */  _Id_nom( 2.0 ) ,
 /*   word   Udnom ;               */  _Skor_nom( 1.0 ) ,
 /*   word   rezerved[ 4 ] ;       */ { 0 },
 /*   float  Rsigma ;              */  0      , // ед   //0.068 , - для стенда .
 /*   float  Xsigma ;              */  0      , // ед   //0.119 , - для стенда .
 /*   float  Tf_aper ;             */  0.0424 , // Постоянная времени апер.звена 1 порядка - для преобразований ( Tf= 1/(2*_PI*Sном*fном)
 /*   float  Tfil ;                */  0.0110 , // постоянная времени фильтрации опытным путем определена как 0.011 сек ( по рассчетам Грыгорыча - 0.2...0.5 сек )
 /*   word   Pary_AD ;             */  3 ,     // число пар полюсов
 /*   word   T_Id_flt ;            */  _fSec(0.1) , // фильтр тока ротора для РТ .
 /*   word   T_Otkl_Vent ;         */  _Sec(1*60) ,
 /*   word   T_min_Pusk ;          */  _Sec(30) ,
 /*   word   ZIS_Nachal ;          */  _Skor_nom( 0.00 ) ,
 /*   word   T_vkl_KZ ;            */  _Sec(5) ,
 /*   word   Alfa_Shunt2 ;         */  _Grad( 60 ) ,
 /*   word   Alfa_Shunt3 ;         */  _Grad( 60 ) ,

 /*   float  Km ;                  */  2.00 ,      //2.70 ,    - для стенда .       Км = Mмакс/Mном , ое
 /*   word   Pnom ;           кВт  */  320 ,       //5 ,       - для стенда .       Рном , кВт
 /*   word   Istat ;               */  58.5*10 ,   //14.7*10 , - для стенда .       Is , А
                                   // уставка действующего тока ротора , если ток двигателя не совпадает с током датчика :
 /*   word   I_rot_nom ;        A  */  355 ,       // 16       - для стенда .
 /*   word   T_otkl_KZ ;           */  _Sec(60) ,

 /*   word  rezerv[ 130 ] ;        */ { 0 },

#ifdef _INTERPRETER
 /*   struct SetpointData MemData; */ { 0 },
#endif

 /*   byte  Contrl_sum ;           */   0
  } ;

//----------------------------------------------------------------------
//
// Табличка Грыгорыча для номинальных токов для настройки датчика УПТФ :
//----------------------------------------------------------------------|
//   Ближайший в сторону увеличения      |  Выпрямленный ток УПТФ Id ,  |
//   номинальный ток УПТФ , на который   |  разделенный на 0.816        |
//   нужно настроить датчик тока         |                              |
//---------------------------------------|------------------------------|
//               320                     |             390              |
//               400                     |             490              |
//               515                     |             630              |
//               542                     |             664              |
//               550                     |             670              |
//               555                     |             680              |
//               580                     |             710              |
//               590                     |             720              |
//               850                     |            1040              |
//---------------------------------------|------------------------------|
//
// Ток двигателя - 355 А -> Id-двиг = 355/0.816 = 435 А .
// Ток датчика   - 400 А -> Id-ДТ   = 400/0.816 = 490 А .

//    Блок уставок не восстанавливаемый по команде "F9-Типовые уставки":
//  для возможности задание номиналов датчиков и т.д.
_x_far const struct SBlok_Ustavok _sc =
  {
      //  Уставки номиналов: 1дискрета = 1А, 1В.
                                       {   {  0, 0 },
 /* struct  {  word  oe , fe ;  } Id ; */     { _Id_nom( 1.0 ),   490 },    //16/0.816=20 //Iрот/0.816 , А
 /* struct  {  word  oe , fe ;  } Ud ; */     { _Ud_nom( 1.0 ),   560 },    //216         //Uрот , В
 /* struct  {  word  oe , fe ;  } Us ; */     { _Iv_nom( 1.0 ),  6000 },    //380         //Us   , В
 /* struct  {  word  oe , fe ;  } N  ; */     { _Skor_nom( 1.0 ), 985 } },  //925         //N    , об/мин
      //  таблица номиналов датчиков:
 /* word   Id  ;                       */     {   490,   //16/0.816=20                    //Iрот , А
 /* word   Ud  ;                       */         560,   //216                            //Uрот , В
 /* word   Us  ;                       */        6000,   //380                            //Us   , В
 /* word   N   ;                       */         985 }, //925                            //N    , об/мин

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
                                       {_Drb_msec( 50 ), _Drb_msec(250 ),
                                        _Drb_msec(250 ), _Drb_msec( 50 ),
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
word  Izm_T_full , T_izm ;
//Usrednit_Str Id_usr;
//word  Id_usr_full , Id_Usr ;
struct  fil  Id_flt ;

word  timerKZ_on  ;
word  timerKZ_off ;

//рабочие переменные :
union flagO flgO ;
word  Alfa_min_time ;
word  Time_shunt_end , Time_shunt , Time_Zatyan_Pusk , Time_Pusk ; //, timeSploshnyak ;
word  time_Reg , time_Integr , time_Puls ;
word  SP_stup , Block_Upravl ;
word  Timer_Pusk , Skor_Pusk ;
word  time_T_izm ;
word  T_zad_vedomiy ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union Prt Prt_NULL;
extern word  Izm_T_full , T_izm ;
//extern Usrednit_Str Id_usr;
//extern word  Id_usr_full , Id_Usr ;
extern struct  fil  Id_flt ;

extern word  timerKZ_on  ;
extern word  timerKZ_off ;

extern union flagO flgO ;
extern word  Alfa_min_time ;
extern word  Time_shunt_end , Time_shunt , Time_Zatyan_Pusk , Time_Pusk ; //, timeSploshnyak ;
extern word  time_Reg , time_Integr , time_Puls ;
extern word  SP_stup , Block_Upravl ;
extern word  Timer_Pusk , Skor_Pusk ;
extern word  time_T_izm ;
extern word  T_zad_vedomiy ;

/*------------------------------------------------*/

extern  struct        oBlok_Ustavok   _or ;
extern  _x_far const struct  oBlok_Ustavok   _oc ;
extern  _x_far const struct  SBlok_Ustavok   _sc ;

extern _x_far const word  P0_tu [ 8 ] ;
extern _x_far const word  P1_tu [ 8 ] ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
