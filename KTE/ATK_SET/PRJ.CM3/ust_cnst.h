
// ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ ИНИЦИАЛИЗАЦИЮ БЛОКА УСТАВОК КОНСТАНТАМИ.
//-------------------------------------------------

#ifndef _ust_cnst_h
#define _ust_cnst_h

#ifdef  _FLASH_INCLUDE

_x_far const  struct  Blok_Ustavok   _c  =
  {

   /* word     Begin_Code ;             */   0xABCD ,

   /* union Config  Cfg ; */             { _cfg_Kontaktor | _cfg_MT /*| _cfg_DZV*/ | _cfg_Fzapoln | _cfg_Obj_prg
                                       /*| _cfg_Shtat_reg*/ | _cfg_Control_ZSk | _cfg_Iv_Econom } ,//| _cfg_Ostanov | _cfg_Dve_Zony | _cfg_CAN_reg
   /* union Config2  Cfg2 ;             */  { _cfg2_SIFU_Syn2 | _cfg2_WatchdogEn|_cfg2_ContrTShI|_cfg2_ContrTShV} ,

  /* word     TMIN;                    */  _MkSec( 1. / 55.0 * 1000000.) ,

   /* word     TMAX;                    */  _MkSec( 1. / 45.0 * 1000000.) ,

   /* byte     K_synchr ;               */   2 ,

   /* byte     Kf_synch   ;             */   1 ,

   /* word     dTsyn_max  ;             */  _MkSec( 20 * 55 ),

   /* byte     AD_pause ;               */   (b)_MkSec( 9 ) ,

   /* byte     S_FazirovVS ;         ы  */   5 ,

   /* word     S_FazirovUgol ;       ы  */   _Grad( 37.0 ) ,

   /* word     S_Alfa_Start ;           */   _Grad( 150 ) , //_Grad( 120 ) , 07.06.2021 - Инвертор должен начинать с Альфа-Макс .

   /* word     S_Alfa_Max ;             */   _Grad( 150 ) ,

   /* word     S_Alfa_Min ;             */   _Grad(  20 ) , //_Grad(  90 ) , 12.06.2020 - Инвертор может стать Выпрямителем .

   /* word     S_DeltaAlfa_Max ;        */   _Grad(  20 ) ,

   /* word     S_ImpLong ;              */   _Grad(   6 ) , //_Grad( 120 ) , 29.07.2020 - при переверсе переход на короткие ИУ .

   /* word     S_Alfa_IzmId ;           */   _Grad(  13 ) , //_Grad(  14.5 ) , 23.02.2018 - Вычислил Таран с Шестаковым .

   /* word     S_Alfa_IzmDoImp ;        */   _Grad(  2 ) ,
//--------
#ifdef _SIFU2_
//--------
   /* struct _r_SIFU2   S2 ;            */
   /*   {                               */
   /*   byte     FazirovVS ;            */   6 , //1 ,  29.12.2016 9:30 - В СМ3 ток 800д, уменьшаем в 4 раза коэффициенты :
   /*   word     Kp_rvt ;               */   (w)( 0.20 * 64.) ,//(w)( 0.79 * 64.) ,//0x0020 ,
   /*   word     Ki_rvt ;               */   (w)( 0.03 * 64.) ,//(w)( 0.10 * 64.) ,//0x0014 ,
   /*   word     RVTmax ;               */   (w)( 3.0  * 64.) ,
   /*   } ;                             */

   /* word     _1P_2P_min ;             */  _AD_offset( 3.00 ) , //(w)(3.0 *(512/5.0)),
   /* word     _1P_2P_max ;             */  _AD_offset( 4.50 ) , //(w)(4.5 *(512/5.0)),
//--------
#endif
           /*---------  Для тока возбуждения ---------*/

   /* word     Iv_zad ;                 */  _Iv_nom( 1.00 ) ,           //19

   /* word     Iv_zad_Max  ;            */  _Iv_nom( 1.00 ) ,  // 440u//20

   /* word     Iv_zad_Min  ;            */  _Iv_nom( 0.50 ) ,          //21

   /* word     Iv_gashen ;              */  _Iv_nom( -0.10 ),           //19

   /* word     Iv_avar_Min ;            */  _Iv_nom( 0.20 ) ,         //22

   /* word     Iv_econom ;              */  _Iv_nom( 0.50 ) ,

   /* word     T_econom ;               */  _Sec( 5.0 ) ,
//---------
#ifdef _Vozb_KTE
//---------
   /* byte     V_Time_do_OtklImp ;      */  _Sec( 2.0 ) ,

   /* byte     V_FazirovVS ;            */   5 ,

   /* word     V_FazirovUgol ;          */   _Grad( 37.0 ) ,

   /* word     V_Alfa_Max ;             */   _Grad( 150 ) ,

   /* word     V_Alfa_Min ;             */   _Grad(  10 ) ,

   /* word     Iv_avar_Max ;            */   _Iv_nom( 1.2 ) ,

   /* word     Iv_null ;                */   _Iv_nom( 0.1 ) ,

   /* word     V_Kp_rt ;                */   100 ,

   /* word     V_Ki_rt ;                */     7 ,
//---------
#endif
//--------------------  Для регулятора ЭДС ---------*/

   /* word     Z_EDS  ;                 */  _EDS_nom ( 1.00 ) ,

   /* word     Ki_REDS  ;               */   200 , //"мсек"

   /* word     Kp_REDS  ;               */   (w)( 1.50 * 256) ,

   /* word     Skor2Z ;                 */  _Skor_nom( 1.00 ) ,
#ifndef _ZI_30min
   /* word     T_ZISkorP_Razg  ;        */  _Skor_nom( 0.05 ) ,

   /* word     T_ZISkorP_Torm  ;        */  _Skor_nom( 0.05 ) ,

   /* word     T_ZISkorM_Razg  ;        */  _Skor_nom( 0.05 ) ,

   /* word     T_ZISkorM_Torm  ;        */  _Skor_nom( 0.05 ) ,

   /* word     T_ZISkor_Parab  ;        */  0 , //_Skor_nom( 3.0 ) ,
#else
   /* word     T_ZISkorP_Razg  ;        */  50 , // Номинал за 5 мин

   /* word     T_ZISkorP_Torm  ;        */  50 , // Номинал за 5 мин

   /* word     T_ZISkorM_Razg  ;        */  50 , // Номинал за 5 мин

   /* word     T_ZISkorM_Torm  ;        */  50 , // Номинал за 5 мин

   /* word     T_ZISkor_Parab  ;        */  0 , //_Skor_nom( 3.0 ) ,
#endif
/*------------  Для Модуля Задания на Скорость  -------------------*/

   /* union  ZadSkor_u  ZSk_str ;       */  { _zs_BolsheMenshe } ,

   /* union     Skor_u   Sk_str ;       */  { _sk_PDF | _sk_FiltrEds } ,

   /* word     Temp_ZSkBM ;             */  _Skor_nom( 0.03 )  ,            //32

   /* word     ZSkBM_MaxB ;             */  _Skor_nom( 1.00 )  ,            //30

   /* word     ZSkBM_MaxM ;             */  _Skor_nom( -1.00 ) ,            //31

   /* word     ZSk_TB     ;             */  _Skor_nom( 0.30 )  ,            //33

   /* word     ZSk_TH     ;             */  _Skor_nom( -0.30 ) ,            //34

   /* word     Mashtab_ZSkA ;           */  (w)( 0.375 * 256.) ,             //35

   /* struct SELSIN_ust  Selsin[_Sels_Num] */ {{ _Grad( 0 ), 0x0000 },
                                               { _Grad( 0 ), 0x0000 }},
  #ifndef  _LABOR_STEND
   /* struct PDF_ust  PDF[_PDF_Num]     */ {{ 25000, _Grad( 0 ), _PDF_delitel }},
  #else // На синхронной скорости 1000 об/мин ПДФ 1000 имп/об на стенде выдаёт 166 кГц .
   /* struct PDF_ust  PDF[_PDF_Num]     */ {{ 10000, _Grad( 0 ), _PDF_delitel }},
  #endif
   /* word     Mashtab_OS_TG ;          */  (w)( 1.00 * 256.) ,             //38

   /*---- Для Регулятора Скорости ----*/

   /* word     Mashtab_EDS ;            */  (w)( 1.14 * 256.) ,

   /* word     Z_SkMax_P ;              */  _Skor_nom( 0.90 )  ,            //42

   /* word     Z_SkMax_M ;              */  0 , //_Skor_nom(-1.10 ) ,             //43

   /* word     Z_SkMin ;                */  _Skor_nom ( 0.00 ) ,                //44

   /* word     Z_II_EDS ;               */  _EDS_nom ( 1.00 ) ,

   /* word     T_Circuit ;              */  _fSec( 1.5 ) ,

   /* word     DT_ZISk ;                */  (w)( 0.50 * 256.) , // Кп-РЭДС во второй зоне .
                                                          // Перевод без оснований "64" и "65535" :
   /* word     KRSP ;                   */  (w)( 5.00 * 256.), // Kпс = Kпн*2/32 = Kпн*0.0625
                                                               // Кпн = Кпс/0.0625 = 1/0.0625=16
   /* word     KRSI  ;                  */  0 , // "мсек"   // Киc = 2/32*3.3 / Т
                                                            // Кис = 0.206 / T => T=0.206/Кис=..мс
   /* word     KRSPIP ;                 */  (w)( 0.00 * 256.) , // Kпипс = Kпипн*2/32 = Kпипн*0.0625
                                                                // Кпипн = Кпипс/0.0625
  /*----  Для Регулятора Тока  ----*/

   /* word     OuRSMaxMost1 ;           */  _Id_Nom  ,               // 2

   /* word     OuRSMaxMost2 ;           */ (w)(int)(-1.00 * _Id_Nom)  ,     // 3

   /* word     OuRSMax2Most1 ;          */  _Id_nom(0.1) ,               // 4

   /* word     OuRSMax2Most2 ;          */ (w)(int)(-0.10 * _Id_Nom) ,     // 5

   /* word     INN0;                    */  _Id_nom(3.5) , // распускаем , АТК использует для порога задания .
#ifndef _KTE_GD
   /* word     IZMAX;                   */  _Id_Nom ,                // 1
#endif
   /* word     Temp_RT_P;               */  10 * _Id_Nom200 ,                //10

   /* word     Temp_RT_M;               */  10 * _Id_Nom200 ,                //11

   /* word     RTMIN;                   */  0x0300         , //_Grad(  90 ) , 12.06.2020 - Инвертор может стать Выпрямителем .

   /* word     RTMAX;                   */  0x3A55         ,
#ifndef _KTE_GD
   /* word     KRTDI;                   */  112u,
                                                    // Перевод без основания "65535" :
   /* word     KRTPRI ;                 */  15*64 , // "мсек" // Киc = 91/2*3.3 / Т
#endif                                              //        // Кис = 150 / T => T=150/10=15мс
   /* word     KRTNI  ;                 */  150*64, // "мсек" // Киc = 91/2*3.3 / Т
                                                            // Кис = 150 / T => T=150/1 =150мс
   /* word     KRTP   ;                 */  (w)( 0.21 * 256.) , // Kпс = Kпн*91/2 = Kпн*45
                                                                // Кпн = Кпс/45 = 10/45=0.21
   /* word     RevU0  ;                 */  _Grad( 120.0)  ,

   /* byte     time_Iv_max ;            */  _pSec( 0.02 )  ,

   /* byte     time_Iv_min ;            */  _pSec( 0.02 )  ,

   /* byte     Po0_Normal ;             */  0x01           ,

   /* byte     KKEDS ;                  */  0x3c           ,

   /* byte     KEDS_R     ;             */  10u  ,                           //48

   /* byte     KEDS_P     ;             */  1u   ,                           //49

   /* byte     KEDS_T     ;             */  1u   ,                           //50

   /* byte     time_Id_max ;            */  _pSec( 0.0 )   ,

   /* word     K_Kompen_Ud   ;          */  0x01 ,                          //47

   /* word     Porog_FE  ;              */  0x0064 , //0x0005 для 100%=400diskr => 0x0014 для 100%=1600diskr
                                                     //0x0064 для СМ3 25.06.2020 - сказал Шестаков .
   /* word     K_FE  ;                  */  0x0006 ,

   /* byte     KeI    ;                 */  0x53u          ,

   /* byte     KeV    ;                 */  0x48u          ,

   /* word     RIDRR   ;                */  _Id_nom(0.02) ,                //56

   /* word     dt_revers ;              */  _pSec( 0.0 ) ,

//---------------  Для Защит -------------------

   /* word     Uinsul_max  ;            */ (w)(4.00 *(_AD_MAX/5.0)),

   /* word     Tok_Otkl_Kontaktor ;     */  _Id_nom  ( 0.70 ) ,            //67

   /* word     Id_Otkl_MT ;             */  _Id_nom  ( 0.20 ) ,

   /* word     Time_MT ;                */  0 , //_Sec( 0.5 ) ,

   /* word     Time_MT_Err ;            */ _Sec( 0.5 ) ,
#ifndef  _STOLB_1TIR

   /* word     Time_otkl_BV1 ;       ы  */  _Sec( 3.0 * 60.0 ) ,            //59



#else
   /* word     Time_otkl_BV1 ;       ы  */  _Sec( 0.5 ) ,                   //59
#endif
   /* word     Time_do_OtklImp ;        */  _Sec( 0.1 ) ,                   //60

   /* word     Ostanov_skor ;           */  _Skor_nom ( 0.015 ) ,           //62

   /* word     Ostanov_time ;           */  _Sec( 0.2 ) ,                   //63

   /* word     Stoyanka_Tok ;           */  _Id_nom  ( 0.70 ) , //_Id_nom  ( 2.00 ) , //65

   /* word     Stoyanka_Eds  ;          */  _EDS_nom ( 0.01 ) , //_EDS_nom ( 0.07 ) , //64

   /* word     Stoyanka_Time ;       ы  */  _Sec( 30.0 ) ,                  //66

   /* word     Time_otkl_VentDvig ;     */  _Sec( 3.0 * 60.0 ) ,            //61

   /* word     Time_MasloSmazka ;       */  _Sec( 3.0 * 60.0 ) ,            //61

   /* word     Time_Smazka_Podsh ;      */  _Sec( 3.0 * 60.0 ) ,

   /* word     Ki_REDS_II_Z ;           */  400 , //"мсек"

   /* word     E_Max ;               ы  */  _EDS_nom  ( 1.2 ) ,             //17

   /* word     N_Max ;                  */  _Skor_nom ( 1.23 ) ,            //16

   /* word     Id_Max ;              ы  */  _Id_nom  ( 2.65 ) ,            // 6

   /* word     Id_teplo_predupr ;       */  _Id_nom ( 3.00 ) ,

   /* word     P24_max ;                */  _AD_offset( 3.34 ) ,   // 1.3 * 2.57 V = 3.34 V
                                                   // нормальное значение - 2.57 V
   /* word     P24_min ;                */  _AD_offset( 1.80 ) ,   // 0.7 * 2.57 V = 1.80 V

   /* word     P12_max ;                */  _AD_offset( 3.54 ) ,   // 1.3 * 2.72 V = 3.54 V
                                                   // нормальное значение - 2.72 V
   /* word     P12_min ;                */  _AD_offset( 1.90 ) ,   // 0.7 * 2.72 V = 1.90 V

   /* word     N12_max ;                */  _AD_offset( 3.28 ) ,   // 1.3 * 2.52 V = 3.28 V
                                                   // нормальное значение - 2.52 V
   /* word     N12_min ;                */  _AD_offset( 1.76 ) ,   // 0.7 * 2.52 V = 1.76 V

   /* word     Mashtab_Id  ;            */  (w)( 1.17 * 256.) ,//0x012d , //0x00C8 ,

   /* word     Mashtab_Ud  ;            */  (w)( 1.14 * 256.) ,

   /* word     Mashtab_Iv  ;            */  (w)( 1.00 * 256.) ,             //29

   /* word     Koef_Id_teplo  ;         */  0x0100 ,

  /*----  Для Обработки Дискретных Входов -----*/

   /* byte     Pi0_Normal ;          ы  */  0xF6,//0xD6, //0xB6, //0xA6, //0xFE ,
                                            // Есть KF, KFV - 0xB3, Нет KFV - 0xB7, нет KF - 0xF7.
   /* byte     Pi1_Normal ;             */  0xC3, //0xEB, /*0xB7,*/ //0x83, //0x8F, //0xBF ,
#ifdef _Pi2_
   /* byte     Pi2_Normal ;             */  0x00,
#endif
   /* word     Id_Min ;                 */  _Id_nom  ( 0.1 ) ,

   /* word     T_gashenie ;             */  _Sec( 3.0 ) ,

   /* word     K_fil_sk ;               */    2 ,

   /* word     porog_fil ;              */  _Skor_nom ( 0.02 ) ,

   //*******  Уставки для CAN.  ********

   /* struct CAN_SETTING  can[2] :  */ //_Num_CAN_Ports
   /*  {                            */  {  // для нулевого порта:
   /*    byte   addr ;              */    {   0x01 ,
   /*    byte   master_addr_size ;  */        0x04 ,
   /*    union  CAN_CONFIG config ; */        _can_cfg_bt_250k | _can_cfg_vkl,
   /*    byte   btime0  ;           */        _bt0_100k ,
   /*    byte   btime1  ;           */        _bt1_100k ,
   /*    /-------                   */
   /*    word   timeout ;           */        0x0  ,
   /*    byte   connect ;           */         10  ,// СРЕДНЕЕ ВРЕМЯ ОБМЕНА МИКРОМАСТЕРА
   /*    byte   addr_p ;            */         60  ,// СОСТАВЛЯЕТ 4-7МСЕК.
   /*    word   rezerv  ;           */        0x0  },  // для первого порта:
   /*  } ;                          */
#ifdef _CAN_MASTER
     { 0x02, 0x04, _can_cfg_bt_1M | _can_cfg_master | _can_cfg_vkl, _bt0_100k, _bt1_100k, 0x00, 10,  60, 0 }
#else
     { 0x01, 0x04, _can_cfg_bt_1M /*| _can_cfg_vkl*/, _bt0_100k, _bt1_100k, 0x00, 10 ,  60, 0 }
#endif
                                        },
   /* word   WD_time ;                  */  1000 ,

   /* word   time_scan ;                */  _fSec(0.01),

   /* word   T_Connect_cfg ;            */  _Sec ( 0.80 ) ,

   /* word   T_Connect_sts ;            */  _Sec ( 0.15 ) ,

   /* word   dN_Max ;                   */  _Skor_nom ( 0.35 ) ,            //16

   /* word   Id_short_imp ;             */  _Id_nom  ( 3.5 ) ,
//#ifdef _CAN_MASTER
   /* word   T_mConnect_cfg ;           */  _Sec ( 0.15 ) ,

   /* word   T_mConnect_sts ;           */  _Sec ( 0.80 ) ,

   /* byte   AddrDevice1 ;              */  0x01 ,

   /* byte   AddrDevice2 ;              */  0x02 ,

   /* word   rezervMas[ 9] ;            */  { 0 },
//#endif
#ifdef _CM3_
/*	  TUART_RS	rs485 ;                 */  {
/*    {                                 */
/*      union config;                  */  { _cfg_rs_b19200 | _cfg_rs_parityon | _cfg_rs_parity | _cfg_rs_stopbit },//| _cfg_rs_vkl },
/*      byte      addr;                 */   1
/*    }                                 */  },
#endif
#ifdef _RDN
   /* word   Mashtab_Id_2v ;            */  (w)( 1.15 * 256.) ,

   /* word   RDN_Dead_Zone ;            */  _Id_nom  ( 0.30 ) ,

   /* word   RDN_Kp ;                   */  (w)( _Skor_Nom/_Id_Nom * 1.00 * 256.) ,

   /* word   RDN_Max ;                  */  _Skor_nom ( 0.30 ) ,

   /* word   Mashtab_N_2v ;             */  (w)( 1.00 * 256.) ,

   /* word   RDN_Tfiltr ;               */  50 ,  // 1дискр = 1мсек

   /* word   rezervRDN[ 1 ] ;           */  { 0 },
#endif
#ifdef _BUKSOVKA
   /* word   Id_RDN_off ;               */  _Id_nom ( 0.50 ) ,

   /* word   Id_RDN_on ;                */  _Id_nom ( 0.20 ) ,

   /* word   N_RDN_off ;                */  _Skor_nom ( 0.50 ) ,

   /* word   N_RDN_on ;                 */  _Skor_nom ( 0.20 ) ,

   /* word   Time_Buksov ;              */  _fSec( 0.05 ) ,

   /* byte   count_Buk_f ;              */  3,

   /* byte   rezervBUK1 ;               */  0,

   /* word   rezervBUK[ 3] ;            */  { 0 },
#endif
#ifndef _KTEV
   /* word   T_meh ;                    */  _Id_nom ( 0.15 ) ,

   /* word   T_flt_Stat ;               */  _fSec(0.5) ,

   /* word   Porog_Istat ;              */  _Id_nom ( 0.5 ) ,

   /* byte   puls_Istat ;               */   3 ,

   /* byte   rezervDST ;                */   0 ,
#endif
#ifdef _RRS
   /* word   Sk_zahv1 ;                 */  _Skor_nom ( 0.40 ) ,

   /* word   Sk_zahv2 ;                 */  _Skor_nom ( 0.50 ) ,

   /* word   T_zahv ;                   */  _fSec( 0.0 ) ,

   /* word   T_liga ;                   */  _fSec( 0.2 ) ,

   /* word   K_liga ;                   */   1 * 256 ,

   /* word   rezervRRS ;                */   0 ,
#endif
#ifdef _RVId
   /* word   RVId_Dead_Zone ;           */  _Id_nom  ( 0.00 ) ,

   /* word   RVId_Kp ;                  */  (w)( 0.00 * 256.) ,//по умолчанию 0

   /* word   RVId_Ki ;                  */  1000, // в милисекундах

   /* word   RVId_Max ;                 */  _Iv_nom ( 0.10 ) ,

   /* word   Iv_zad_GL1;                */  _Iv_nom ( 1.00 ) ,

   /* word   Iv_zad_GL2;                */  _Iv_nom ( 1.00 ) ,

   /* union ConfigRVId CfgRVId ;        */ { _cfgRVId_Vkl | _cfgRVId_GL2 },
#endif
#ifdef _KTE_GD
   /* word     Mashtab_Ig  ;            */  (w)( 1.15 * 256.) ,

   /* word     Mashtab_Ug  ;            */  (w)( 1.15 * 256.) ,

   /* word     Mashtab_Ugx ;            */  (w)(int)( -0.78 * 256. / _K_diskr) , // 3200д/(400*_K_diskr*10)

   /* word     Ugx8_porog ;             */  _Ug_nom(  0.00 ) ,

   /* word     Ig_Max      ;            */  _Ig_nom( 2.25 ) ,

   /* word     Ug_Max      ;         ы  */  _Ug_nom  ( 1.2 ) ,             //17

   /* word     Ug_zad_max ;             */  _Ug_nom  ( 1.1 ) ,
                                                                // Перевод без основания "65535" :
   /* word     Kp_rn ;                  */   (w)(26.00 * 256.), // Kпс = Kпн*91/32 = Kпн*2.84
                                                                // Кпн = Кпс/2.84 = 75/2.84=26
   /* word     Ki_rn ;                  */    9 , // "мсек".    // Киc = 91/32*3.3 / Т
                                                                // Кис = 9.38 / T => T=9.38/1=9мс
   /* word     Ug_Min ;              ы  */  _Ug_nom  ( 0.1 ) ,             //17

   /* byte     UgOstat ;                */  _Ug_nom  ( 0.01 ) ,

   /* byte     rezerved ;               */    0 ,

   /* word     Ig_forUgz_DZ ;           */  _Ig_nom( 1.50 ) ,

   /* word     Ig_forUgz_Kp ;           */  (w)( 1.00 * _Skor_Nom/_Ig_Nom * 256.) ,

   /* word     Ig_forUgzR_DZ ;          */  _Ig_nom( 1.90 ) ,

   /* word     Ig_forUgzR_Kp ;          */  (w)( 0.50 * _Ug_Nom/_Ig_Nom * 256.) ,

   /* word     rezervGD[ 3 ] ;          */  { 0 },
#else                                                          /*30V*/ /*25V*/ // Если 1 тиристор в параллели - то 25В .
   /* word   PUM_max ;                  */ _AD_offset( 4.27 ) ,//436 ,/* 373 ,*/ // нормальное знач:
                                                                                 // 3.88V - 396д(30V)
   /* word   PUM_min ;                  */ _AD_offset( 3.30 ) ,//337 ,/* 293 ,*/ // 3.24V - 333д(25V)
#endif

   /* word   Password ;                 */  0 ,
#ifndef _ZI_30min
   /* word   T_ZISkorP_Fors ;           */  _Skor_nom( 0.05 ) ,
#else
   /* word   T_ZISkorP_Fors ;           */  20, // Номинал за 2 мин
#endif
   /* word   KRSP_for_P ;               */ (w)( 16.00 * 256.) ,

   /* word   Adapt_temp ;               */  _Id_nom ( 1.50 ) ,

   /* word   Mashtab_OS_TGx ;           */  (w)(int)( -0.78 * 256. / _K_diskr) , // 3200д/(400*_K_diskr*10)

   /* word   TGx8_porog ;               */  _Skor_nom ( 0.00 ) ,

#ifdef _Rev_Pola   // если включен алгоритм реверса поля.
   /* word   Mashtab_Idz_Ivz ;          */  (w)( 0.20 * 256.) ,

   /* word   Iv_porg_Min  ;             */  _Iv_nom( 0.05 ) ,
#endif
#ifdef _REG_POL    // регулятор положения.
   /* word   Kp_RP ;                    */  (w)( 1.00 * 256.) ,

   /* word   Ki_RP ;                    */  0 , // "мсек".

   /* word   DeltaDeadZone ;            */  _Grad( 5.00 ),

   /* word   T_ZIP_Razg ;               */ _Grad( 650.00 ) ,

   /* word   T_ZIP_Torm ;               */ _Grad( 650.00 ) ,

   /* word   Kp_dP ;                    */  (w)( 1.00 * 256.) ,

   /* word   rezervRP[ 2 ] ;            */  { 0 },
#endif
#ifdef   _AVTONASTR
   /* word     KoefDempfirRT ;          */   (w)( 1.00 * 256.) ,

   /* word     T_AN_ust ;               */   _fSec(16),

   /* word     RezervedAN ;             */   0,

   /* word     Te_AN ;       [мс]       */   20 * 64 ,

   /* word     Tm_AN ;       [мс]       */   50,

   /* word     Tpp_AN_nepr ;            */   30 ,

   /* word     INN_def_AN ;             */   0, // Определять INN: 1 - в 90грд, 0 - по умному

   /* word     Tpp_AN_pr ;              */   10 ,

   /* word     Alfa0_forTm_AN;          */   _Grad(85),

   /* word     Kratn_5_AN;              */   5,

   /* word     KtpRa_AN_nepr ;          */   0 * 64,

   /* word     KtpRa_AN_pr ;            */   0 * 64,

   /* word   rezervAN[  8 ] ;           */  { 0 },
#else
   /* word   rezervAN[ 20 ] ;           */  { 0 },
#endif
   /* word   Z_SkRab ;                  */  _Skor_nom ( 0.00 ) ,
        // Для теплового расчета ротора.
   /* struct TEPLO_UST_r             */
   /* {                              */ {
   /*   word   I[5] ;                */   {_Id_nom(1.06),_Id_nom(1.1),_Id_nom(1.5),_Id_nom(1.75),_Id_nom(2.0)},
   /*   word   T[5] ;  в секундах    */   { 3600        , 600        , 40         , 20          , 15         },
   /*   word   Tohl ;  в секундах    */   420
   /* } I2Tr;                        */ },

   /* word   Mashtab_It ;               */  (w)( 0.978 * 256.) ,

   /* word   Mashtab_Idtt ;             */  (w)( 1.151 * 256.) ,

#ifdef  _NET_IRQ
   /* byte   DP_addr ;                 */  5,

   /* byte   RTU_addr ;                 */  1,

   /* byte   IP1_addr ;                 */  192,

   /* byte   IP2_addr ;                 */  168,

   /* byte   IP3_addr ;                 */  1,

   /* byte   IP4_addr ;                 */  202,

   /* byte   IPM1_addr ;                */  255,

   /* byte   IPM2_addr ;                */  255,

   /* byte   IPM3_addr ;                */  255,

   /* byte   IPM4_addr ;                */  0,

   /* byte   DIP1_addr ;                */  192,

   /* byte   DIP2_addr ;                */  168,

   /* byte   DIP3_addr ;                */  1,

   /* byte   DIP4_addr ;                */  29,

   /* byte   EMAC1_addr ;               */  0x00,

   /* byte   EMAC2_addr ;               */  0xBD,

   /* byte   EMAC3_addr ;               */  0x3B,

   /* byte   EMAC4_addr ;               */  0x33,

   /* byte   EMAC5_addr ;               */  0x06,

   /* byte   EMAC6_addr ;               */  0x66,

   /* union  net_set  net_setting       */  { 0 /*| _net_cfg_vkl */ },

   /* union  net_speed  net_spd ;       */  { 0 /*| _net_cfg_vkl */ },

   /* byte   Net_LT ;                   */  20,

   /* byte   Num_RS485_In ;             */  1,

   /* byte   Num_RS485_Out ;            */  2,

   /* byte   net_reserv    ;            */  0,

   /* word   rezerv1[ 3] ;              */  { 0 },
#else
   /* word   rezerv1[ 16] ;             */  { 0 },
#endif
   /* word   KRSP_II_Z ;                */  (w)( 9.00 * 256.),

   /* word   KRSI_II_Z  ;               */  0 ,

   /* word   KRSPIP_II_Z ;              */  (w)( 0.00 * 256.) ,

   /* word   Id_tst_proboy ;            */  _Id_nom ( 0.05 ) , // 17.09.2021 - при 0.20 "пик" тока затягивается на следующий тиристор

   /* word   Stoyanka_Time_Predupr ;    */  _Sec( 7.0 ) ,

   /* word   T_ZISkor_Parab_delta ;     */  _Skor_nom( 0.05 ),

   /* word Vip_Alfa_Max;                */  _Grad(150),
      
   /* word Vip_Alfa_Min;                */  _Grad(10),

   /* word   Rezerved[ 12 ] ;           */  { 0 },

//#ifdef _Sld_cond
   /* word FiltrTime_Start;             */    0,

   /* word DelayTime_Start;             */    0,

   /* struct sled_cond Start_cond;
      {
        word numb ;                     */  { 0,
   /*   word mean ;                     */    0,
   /*   union
        {
            word all;                   */    0 },
   /*       struct
            {

            word bit    :4;
            word cond   :2;
            word enable :1;
            word type   :1;

            }_;
        } bits;
      }; */

   /* word FiltrTime_Stop;              */    0,

   /* word DelayTime_Stop;              */    0,

   /* struct sled_cond Stop_cond ;
      {
        word numb ;                     */  { 0,
   /*   word mean ;                     */    0,
   /*   union
        {
            word all;                   */    0 },
   /*       struct
            {

            word bit    :4;
            word cond   :2;
            word enable :1;
            word type   :1;

            }_;
        }bits;
      }; */
//#endif

   /* word   SetWinTime;                */  0x0001,

   /* word   Ctrl_Code ;                */  0x4321

  } ;

        /*---------  Номера каналов мультиплексора ---------*/

_x_far const  struct  ABlok_Ustavok   _ac  =
  {
   /* word     Begin_Code ; */          0x5678 ,  //  Слово контроля наличия уставок в Flash.

   /* struct Channel_AD  n00_ach  ;     */ { _Ch0_Numb , _AD_offset( 4.98 ) ,  0 },

   /* struct Channel_AD  n01_ach  ;     */ { _Ch1_Numb , _AD_offset( 4.98 ) ,  1 },

   /* struct Channel_AD  n02_ach  ;     */ { _Ch2_Numb , _AD_offset( 4.98 ) ,  2 },

   /* struct Channel_AD  n03_ach  ;     */ { _Ch3_Numb , _AD_offset( 4.98 ) ,  3 },

   /* struct Channel_AD  n04_ach  ;     */ { _Ch4_Numb , _AD_offset( 4.98 ) ,  4 },

   /* struct Channel_AD  n05_ach  ;     */ { _Ch5_Numb , _AD_offset( 4.98 ) ,  5 },

   /* struct Channel_AD  n06_ach  ;     */ { _Ch6_Numb , _AD_offset( 4.98 ) ,  6 },

   /* struct Channel_AD  n07_ach  ;     */ { _Ch7_Numb , _AD_offset( 4.98 ) ,  7 },


   /* struct Channel_AD  n08_ach  ;     */ { _Ch8_Numb , _AD_offset( 4.98 ) ,  8 },

   /* struct Channel_AD  n09_ach  ;     */ { _Ch9_Numb , _AD_offset( 4.98 ) ,  9 },

   /* struct Channel_AD  n10_ach  ;     */ { _Ch10_Numb, _AD_offset( 4.98 ) , 10 },

   /* struct Channel_AD  n11_ach  ;     */ { _Ch11_Numb, _AD_offset( 4.98 ) , 11 },

   /* struct Channel_AD  n12_ach  ;     */ { _Ch12_Numb, _AD_offset( 4.98 ) , 12 },

   /* struct Channel_AD  n13_ach  ;     */ { _Ch13_Numb, _AD_offset( 4.98 ) , 13 },
    #ifdef _Ch13_Mux
   /* struct Channel_AD  n131_ach  ;   */  { _Ch131_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n132_ach  ;   */  { _Ch132_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n133_ach  ;   */  { _Ch133_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n134_ach  ;   */  { _Ch134_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n135_ach  ;   */  { _Ch135_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n136_ach  ;   */  { _Ch136_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n137_ach  ;   */  { _Ch137_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n138_ach  ;   */  { _Ch138_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n139_ach  ;   */  { _Ch139_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n13a_ach  ;   */  { _Ch13a_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n13b_ach  ;   */  { _Ch13b_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n13c_ach  ;   */  { _Ch13c_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n13d_ach  ;   */  { _Ch13d_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n13e_ach  ;   */  { _Ch13e_Numb, _AD_offset( 4.98 ), 13 },

   /* struct Channel_AD  n13f_ach  ;   */  { _Ch13f_Numb, _AD_offset( 4.98 ), 13 },
    #endif
   /* struct Channel_AD  n14_ach  ;     */ { _Ch14_Numb, _AD_offset( 4.98 ) , 14 },
    #ifdef _Ch14_Mux
   /* struct Channel_AD  n141_ach  ;   */  { _Ch141_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n142_ach  ;   */  { _Ch142_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n143_ach  ;   */  { _Ch143_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n144_ach  ;   */  { _Ch144_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n145_ach  ;   */  { _Ch145_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n146_ach  ;   */  { _Ch146_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n147_ach  ;   */  { _Ch147_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n148_ach  ;   */  { _Ch148_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n149_ach  ;   */  { _Ch149_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n14a_ach  ;   */  { _Ch14a_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n14b_ach  ;   */  { _Ch14b_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n14c_ach  ;   */  { _Ch14c_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n14d_ach  ;   */  { _Ch14d_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n14e_ach  ;   */  { _Ch14e_Numb, _AD_offset( 4.98 ), 14 },

   /* struct Channel_AD  n14f_ach  ;   */  { _Ch14f_Numb, _AD_offset( 4.98 ), 14 },
    #endif
   /* struct Channel_AD  n15_ach  ;    */  { _Ch15_Numb, _AD_offset( 4.98 ) , 15 },
    #ifdef _Ch15_Mux
   /* struct Channel_AD  n151_ach  ;   */  { _Ch151_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n152_ach  ;   */  { _Ch152_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n153_ach  ;   */  { _Ch153_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n154_ach  ;   */  { _Ch154_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n155_ach  ;   */  { _Ch155_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n156_ach  ;   */  { _Ch156_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n157_ach  ;   */  { _Ch157_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n158_ach  ;   */  { _Ch158_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n159_ach  ;   */  { _Ch159_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n15a_ach  ;   */  { _Ch15a_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n15b_ach  ;   */  { _Ch15b_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n15c_ach  ;   */  { _Ch15c_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n15d_ach  ;   */  { _Ch15d_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n15e_ach  ;   */  { _Ch15e_Numb, _AD_offset( 4.98 ), 15 },

   /* struct Channel_AD  n15f_ach  ;   */  { _Ch15f_Numb, _AD_offset( 4.98 ), 15 },
    #endif
  #ifdef _CM3_
   /* struct Channel_AD  n16_ach  ;    */  { _Ch16_Numb, _AD_offset( 0.00 ) , 16 },

   /* struct Channel_AD  n17_ach  ;    */  { _Ch17_Numb, _AD_offset( 0.00 ) , 17 },

   /* struct Channel_AD  n18_ach  ;    */  { _Ch18_Numb, _AD_offset( 0.00 ) , 18 },

                                            {
   /* word  ADC_Scale[0];             */      def_ach_scale,
   /* word  ADC_Scale[1];             */      def_ach_scale,
   /* word  ADC_Scale[2];             */      def_ach_scale,
   /* word  ADC_Scale[3];             */      def_ach_scale,
   /* word  ADC_Scale[4];             */      def_ach_scale,
   /* word  ADC_Scale[5];             */      def_ach_scale,
   /* word  ADC_Scale[6];             */      def_ach_scale,
   /* word  ADC_Scale[7];             */      def_ach_scale,
   /* word  ADC_Scale[8];             */      def_ach_scale,
   /* word  ADC_Scale[9];             */      def_ach_scale,
   /* word  ADC_Scale[10];             */     def_ach_scale,
   /* word  ADC_Scale[11];             */     def_ach_scale,
   /* word  ADC_Scale[12];             */     def_ach_scale,
   /* word  ADC_Scale[13];             */     def_ach_scale, //10410, типовый масштаб для плат аналогового мультиплексора
   /* word  ADC_Scale[14];             */     def_ach_scale, //10410,
   /* word  ADC_Scale[15];             */     def_ach_scale, //10410,
   /* word  ADC_Scale[16];             */     def_ach_scale,
   /* word  ADC_Scale[17];             */     def_ach_scale,
   /* word  ADC_Scale[18];             */     def_ach_scale
                                            },
  #endif
   /* byte  Contrl_sum ;                */  0
   } ;

//----------------------
_x_far const  struct tab_Ivz  c_Ivz =
{
  // Функционал - кривая намагничивания :
  _Iv_nom( 0.00  ), _Iv_nom( 0.025 ), _Iv_nom( 0.05  ), _Iv_nom( 0.075 ),
  _Iv_nom( 0.10  ), _Iv_nom( 0.125 ), _Iv_nom( 0.15  ), _Iv_nom( 0.18  ),
  _Iv_nom( 0.225 ), _Iv_nom( 0.27  ), _Iv_nom( 0.305 ), _Iv_nom( 0.34  ),
  _Iv_nom( 0.375 ), _Iv_nom( 0.415 ), _Iv_nom( 0.45  ), _Iv_nom( 0.495 ),
  _Iv_nom( 0.55  ), _Iv_nom( 0.61  ), _Iv_nom( 0.685 ), _Iv_nom( 0.775 ),
  _Iv_nom( 1.00  ),
  0

  // Прямой фукционал - для реверса поля :
  /*
  _Iv_nom( 0.00  ), _Iv_nom( 0.05  ), _Iv_nom( 0.10  ), _Iv_nom( 0.15  ),
  _Iv_nom( 0.20  ), _Iv_nom( 0.25  ), _Iv_nom( 0.30  ), _Iv_nom( 0.35  ),
  _Iv_nom( 0.40  ), _Iv_nom( 0.45  ), _Iv_nom( 0.50  ), _Iv_nom( 0.55  ),
  _Iv_nom( 0.60  ), _Iv_nom( 0.65  ), _Iv_nom( 0.70  ), _Iv_nom( 0.75  ),
  _Iv_nom( 0.80  ), _Iv_nom( 0.85  ), _Iv_nom( 0.90  ), _Iv_nom( 0.95  ),
  _Iv_nom( 1.00  ),
  0
  */
}  ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

 extern  _x_far const struct  Blok_Ustavok    _c  ;
 extern  _x_far const struct  ABlok_Ustavok   _ac  ;
 extern  _x_far const struct  tab_Ivz          c_Ivz  ;

/*------------------------------------------------*/
#endif
#endif

