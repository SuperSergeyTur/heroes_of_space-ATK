
// ЗАГОЛОВОЧНЫЙ ФАЙЛ: СОДЕРЖИТ ОПИМАНИЕ СТРУКТУРЫ БЛОКА УСТАВОК.
//-------------------------------------------------

#ifndef _ustav_h
#define _ustav_h



       struct  Blok_Ustavok
  {

      word     Begin_Code ;   //  Слово контроля наличия уставок в Flash.

      union Config  Cfg ;

      union Config2  Cfg2 ;

      word     TMIN;

      word     TMAX;

      byte     K_synchr ;

      byte     Kf_synch   ;

      word     dTsyn_max  ;

      byte     AD_pause ;     /* Время выдержки от момента переключения мультиплексора до пуска АЦП. */

      byte     S_FazirovVS ;

      word     S_FazirovUgol ;

      word     S_Alfa_Start ;

      word     S_Alfa_Max ;

      word     S_Alfa_Min ;

      word     S_DeltaAlfa_Max ;

      word     S_ImpLong ;

      word     S_Alfa_IzmId ;

      word     S_Alfa_IzmDoImp ;
//--------
#ifdef _SIFU2_
//--------
      struct _r_SIFU2   S2 ;
   /*   {                               */
   /*   byte     FazirovVS ;            */
   /*   word     Kp_rvt ;               */
   /*   word     Ki_rvt ;               */
   /*   word     RVTmax ;               */
   /*   } ;                             */

      word     _1P_2P_min ;
      word     _1P_2P_max ;
//---------
#endif
//--------------------  Для тока возбуждения ---------

      word     Iv_zad ;

      word     Iv_zad_Max  ; // Ограничение задания на минимум

      word     Iv_zad_Min  ; // Ограничение задания на минимум

      word     Iv_gashen ;

      word     Iv_avar_Min ;

      word     Iv_econom ;

      word     T_econom ; // Выдержка на гашение/эконом режим Iv
//---------
#ifdef _Vozb_KTE
//---------
      byte     V_Time_do_OtklImp ;

      byte     V_FazirovVS ;

      word     V_FazirovUgol ;

      word     V_Alfa_Max ;

      word     V_Alfa_Min ;

      word     Iv_avar_Max ;

      word     Iv_null ;

      word     V_Kp_rt ;

      word     V_Ki_rt ;
//---------
#endif
//---------/*---------  Для регулятора ЭДС ---------*/

      word     Z_EDS  ;    // Задание на ЭДС

      word     Ki_REDS  ;

      word     Kp_REDS  ;

      word     Skor2Z ;    // Скорость второй зоны

      word     T_ZISkorP_Razg  ;

      word     T_ZISkorP_Torm  ;

      word     T_ZISkorM_Razg  ;

      word     T_ZISkorM_Torm  ;

      word     T_ZISkor_Parab  ;











/*------------  Для Модуля Задания на Скорость  -------------------*/

      union  ZadSkor_u  ZSk_str ;

      union     Skor_u   Sk_str ;

      word     Temp_ZSkBM ;

      word     ZSkBM_MaxB ;

      word     ZSkBM_MaxM ;

      word     ZSk_TB     ;

      word     ZSk_TH     ;

      word     Mashtab_ZSkA ;

      struct SELSIN_ust  Selsin[_Sels_Num] ;

      struct PDF_ust  PDF[_PDF_Num] ;

      word     Mashtab_OS_TG ;

   /*---- Для Регулятора Скорости ----*/

      word     Mashtab_EDS ;

      word     Z_SkMax_P ;

      word     Z_SkMax_M ;

      word     Z_SkMin ;

      word     Z_II_EDS ;

      word     T_Circuit ;

      word     DT_ZISk ;

      word     KRSP ;

      word     KRSI  ;

      word     KRSPIP ;

  /*----  Для Регулятора Тока  ----*/

      word     OuRSMaxMost1 ;

      word     OuRSMaxMost2 ;

      word     OuRSMax2Most1 ;

      word     OuRSMax2Most2 ;

      word     INN0;
#ifndef _KTE_GD
      word     IZMAX;   // Us_zad_max
#endif
      word     Temp_RT_P;

      word     Temp_RT_M;

      word     RTMIN;

      word     RTMAX;
#ifndef _KTE_GD
      word     KRTDI;   //  Kp_rn

      word     KRTPRI ; //  Ki_rn
#endif
      word     KRTNI  ;

      word     KRTP   ;

      word     RevU0  ;

      byte     time_Iv_max ;

      byte     time_Iv_min ;

      byte     Po0_Normal ;

      byte     KKEDS ;

      byte     KEDS_R     ;

      byte     KEDS_P     ;

      byte     KEDS_T     ;

      byte     time_Id_max ;

      word     K_Kompen_Ud   ;

      word     Porog_FE  ;

      word     K_FE  ;

      byte     KeI    ;

      byte     KeV    ;

      word     RIDRR   ;

      word     dt_revers ;

//---------------  Для Защит -------------------

      word     Uinsul_max  ;

      word     Tok_Otkl_Kontaktor ;

      word     Id_Otkl_MT ;

      word     Time_MT ;

      word     Time_MT_Err ;


      word     Time_otkl_BV1 ;          //   Выдержка времени в минутах на отключение при отсутствии охлаждения.






      word     Time_do_OtklImp ;        //  Время от задвигания импульсов при отключении до их снятия.

      word     Ostanov_skor ;           // Уровень скорости для определения режима останова ( в номиналах ).

      word     Ostanov_time ;           // Время выдержки для определения режима останова ( в секундах ).

      word     Stoyanka_Tok ;           // Уровень тока для определения режима стоянки под током ( в номиналах ).

      word     Stoyanka_Eds  ;          // Уровень скорости для определения режима стоянки  под током( в номиналах ).

      word     Stoyanka_Time ;          // Макс. доп. время режима стоянки под током ( в секундах ).

      word     Time_otkl_VentDvig ;

      word     Time_MasloSmazka ;

      word     Time_Smazka_Podsh ;

      word     Ki_REDS_II_Z ;

      word     E_Max ;

      word     N_Max ;

      word     Id_Max ;

      word     Id_teplo_predupr ;

      word     P24_max ;

      word     P24_min ;

      word     P12_max ;

      word     P12_min ;

      word     N12_max ;

      word     N12_min ;

      word     Mashtab_Id  ;      //  Коэфф.приведения тока ротора к пропорции <Inom = 200дискрет>.

      word     Mashtab_Ud  ;      //  Коэфф.приведения напряжения ротора к пропорции <Unom = 200дискрет>.

      word     Mashtab_Iv  ;              //  Коэфф.приведения тока обратной связи возбудителя к пропорции <Inom ч 200дискрет>.

      word     Koef_Id_teplo  ;   //  Коефф. масшт. тока ротора для проверки тепловой защиты.

  /*----  Для Обработки Дискретных Входов -----*/

      byte     Pi0_Normal ;             /*   "Normal" - уставка-маска для нормализации уровней сигналов данного порта,      */
                                        /* т.е. приведения реальных активных уровней сигналов к общепринятому               */
      byte     Pi1_Normal ;             /* уровню активного сигнала, путем инвертирования через исключающее ИЛИ.            */
#ifdef _Pi2_                             /*   Для инвертирования сигнала следует установить в уставке в единицу разряд       */
      byte     Pi2_Normal ;             /* соответствующий (по номеру от младшего) данному сигналу в шаблоне данного порта. */
#endif                                  /*   Для инвертирования сигнала следует установить в уставке в единицу разряд       */
#ifdef _Pi3_
      byte     Pi3_Normal ;
#endif
#ifdef _Pi4_
      byte     Pi4_Normal ;
#endif
      word     Id_Min ;

      word     T_gashenie ;

      word     K_fil_sk ;

      word     porog_fil ;

   //*******  Уставки для CAN.  ********

      struct CAN_SETTING  can[_Num_CAN_Ports] ;  // закладываем сразу под кол-во портов.
   /*  {                            */
   /*    byte   addr ;              */
   /*    byte   master_addr_size ;  */
   /*    union  CAN_CONFIG config ; */
   /*    byte   btime0  ;           */
   /*    byte   btime1  ;           */
   /*    /-------                   */
   /*    word   timeout ;           */
   /*    byte   connect ;           */
   /*    byte   addr_p ;            */
   /*    word   rezerv  ;           */
   /*  } ;                          */






      word   WD_time ;

      word   time_scan ;

      word   T_Connect_cfg ;

      word   T_Connect_sts ;

      word   dN_Max ;

      word   Id_short_imp ;
//#ifdef _CAN_MASTER
      word   T_mConnect_cfg ;

      word   T_mConnect_sts ;

      byte   AddrDevice1 ;

      byte   AddrDevice2 ;

      word   rezervMas[ 9] ;
//#endif
#ifdef _CM3_
      TUART_RS  rs485 ;
/*    {
        union config;
        byte      addr;
      } */
#endif
#ifdef _RDN
      word   Mashtab_Id_2v ;

      word   RDN_Dead_Zone ;

      word   RDN_Kp ;

      word   RDN_Max ;

      word   Mashtab_N_2v ;

      word   RDN_Tfiltr ;

      word   rezervRDN[ 1 ] ;
#endif
#ifdef _BUKSOVKA
      word   Id_RDN_off ;

      word   Id_RDN_on ;

      word   N_RDN_off ;

      word   N_RDN_on ;

      word   Time_Buksov ;

      byte   count_Buk_f ;

      byte   rezervBUK1 ;

      word   rezervBUK[ 3] ;
#endif
#ifndef _KTEV
      word   T_meh ;

      word   T_flt_Stat ;

      word   Porog_Istat ;

      byte   puls_Istat ;

      byte   rezervDST ;
#endif
#ifdef _RRS
      word   Sk_zahv1 ;

      word   Sk_zahv2 ;

      word   T_zahv ;

      word   T_liga ;

      word   K_liga ;

      word   rezervRRS ;
#endif
#ifdef _RVId
      word   RVId_Dead_Zone ;

      word   RVId_Kp ;

      word   RVId_Ti ;

      word   RVId_Max ;

      word   Iv_zad_GL1;

      word   Iv_zad_GL2;

      union ConfigRVId CfgRVId ;

#endif
#ifdef _KTE_GD
      word     Mashtab_Ig  ;      //  Коэфф.приведения тока генер.ГД

      word     Mashtab_Ug  ;      //  Коэфф.приведения напряжения ГД

      word     Mashtab_Ugx ;      //  Коэфф.приведения умноженного напряжения ГД

      word     Ugx8_porog ;

      word     Ig_Max      ;

      word     Ug_Max      ;

      word     Ug_zad_max ;

      word     Kp_rn ;

      word     Ki_rn ;

      word     Ug_Min ;

      byte     UgOstat ;

      byte     rezerved ;

      word     Ig_forUgz_DZ ;

      word     Ig_forUgz_Kp ;

      word     Ig_forUgzR_DZ ;

      word     Ig_forUgzR_Kp ;

      word     rezervGD[ 3 ] ;
#else
      word   PUM_max ;

      word   PUM_min ;
#endif

      word   Password ;

      word   T_ZISkorP_Fors ;



      word   KRSP_for_P ;

      word   Adapt_temp ;

      word   Mashtab_OS_TGx ;

      word   TGx8_porog ;

#ifdef _Rev_Pola   // если включен алгоритм реверса поля.
      word   Mashtab_Idz_Ivz ;

      word   Iv_porg_Min  ;
#endif
#ifdef _REG_POL
      word   Kp_RP ;

      word   Ki_RP ;

      word   DeltaDeadZone ;

      word   T_ZIP_Razg ;

      word   T_ZIP_Torm ;

      word   Kp_dP ;

      word   rezervRP[ 2 ] ;
#endif
#ifdef   _AVTONASTR
      word     KoefDempfirRT ;

      word     T_AN_ust ;

      word     RezervedAN ;

      word     Te_AN ;

      word     Tm_AN ;

      word     Tpp_AN_nepr ;

      word     INN_def_AN ;

      word     Tpp_AN_pr ;

      word     Alfa0_forTm_AN;

      word     Kratn_5_AN;

      word     KtpRa_AN_nepr ;

      word     KtpRa_AN_pr ;

      word   rezervAN[  8 ] ;
#else
      word   rezervAN[ 20 ] ;
#endif
      word   Z_SkRab ;
        // Для теплового расчета ротора.
      struct TEPLO_UST_r
      {
        word   I[5] ;
        word   T[5] ;
        word   Tohl ;
      } I2Tr;

      word   Mashtab_It ;

      word   Mashtab_Idtt ;

#ifdef  _NET_IRQ
      byte   DP_addr ;

      byte   RTU_addr ;
                          //--- word - 1
      byte   IP1_addr ;

      byte   IP2_addr ;
                          //--- word - 2
      byte   IP3_addr ;

      byte   IP4_addr ;
                          //--- word - 3
      byte   IPM1_addr ;

      byte   IPM2_addr ;
                          //--- word - 4
      byte   IPM3_addr ;

      byte   IPM4_addr ;
                          //--- word - 5
      byte   DIP1_addr ;

      byte   DIP2_addr ;
                          //--- word - 6
      byte   DIP3_addr ;

      byte   DIP4_addr ;
                          //--- word - 7
      byte   EMAC1_addr ;

      byte   EMAC2_addr ;
                          //--- word - 8
      byte   EMAC3_addr ;

      byte   EMAC4_addr ;
                          //--- word - 9
      byte   EMAC5_addr ;

      byte   EMAC6_addr ;
                          //--- word - 10
      union  net_set  net_setting ;

      union  net_speed  net_spd ;
                          //--- word - 11
      byte   Net_LT ;

      byte   Num_RS485_In ;
                          //--- word - 12
      byte   Num_RS485_Out ;

      byte   net_reserv    ;
                          //--- word - 13
      word   rezerv1[ 3] ;
#else                     // Должно быть одинаковое количество слов , чтобы можно было перезашить программу с сетевым адаптером .
      word   rezerv1[ 16] ;
#endif
      word   KRSP_II_Z ;

      word   KRSI_II_Z  ;

      word   KRSPIP_II_Z ;

      word   Id_tst_proboy ;

      word   Stoyanka_Time_Predupr ;

      word   T_ZISkor_Parab_delta ;
      
      word Vip_Alfa_Max;
      
      word Vip_Alfa_Min;

      word   Rezerved[ 10 ] ;

//#ifdef _Sld_cond
      word FiltrTime_Start;

      word DelayTime_Start;

      struct sled_cond Start_cond;
 /*   {
        word numb ;
        word mean ;
        union
        {
            word all;
            struct
            {

            word bit    :4;
            word cond   :2;
            word enable :1;
            word type   :1;

            }_;
        } bits;
      }; */

      word FiltrTime_Stop;

      word DelayTime_Stop;

      struct sled_cond Stop_cond ;
 /*   {
        word numb ;
        word mean ;
        union
        {
            word all;
            struct
            {

            word bit    :4;
            word cond   :2;
            word enable :1;
            word type   :1;

            }_;
        }bits;
      }; */
//#endif
#ifdef _CM3_
      word   SetWinTime;
#endif
      word   Ctrl_Code ;

  } ;

        /*---------  Номера каналов мультиплексора ---------*/

  struct  ABlok_Ustavok
  {
      word     Begin_Code ;   //  Слово контроля наличия уставок в Flash.

      struct Channel_AD  n00_ach  ;

      struct Channel_AD  n01_ach  ;

      struct Channel_AD  n02_ach  ;

      struct Channel_AD  n03_ach  ;

      struct Channel_AD  n04_ach  ;

      struct Channel_AD  n05_ach  ;

      struct Channel_AD  n06_ach  ;

      struct Channel_AD  n07_ach  ;

#if defined( _Union_FR) || defined ( _CM3_ )
      struct Channel_AD  n08_ach  ;

      struct Channel_AD  n09_ach  ;

      struct Channel_AD  n10_ach  ;

      struct Channel_AD  n11_ach  ;

      struct Channel_AD  n12_ach  ;

      struct Channel_AD  n13_ach  ;
    #ifdef _Ch13_Mux
      struct Channel_AD  n131_ach  ;

      struct Channel_AD  n132_ach  ;

      struct Channel_AD  n133_ach  ;

      struct Channel_AD  n134_ach  ;

      struct Channel_AD  n135_ach  ;

      struct Channel_AD  n136_ach  ;

      struct Channel_AD  n137_ach  ;

      struct Channel_AD  n138_ach  ;

      struct Channel_AD  n139_ach  ;

      struct Channel_AD  n13a_ach  ;

      struct Channel_AD  n13b_ach  ;

      struct Channel_AD  n13c_ach  ;

      struct Channel_AD  n13d_ach  ;

      struct Channel_AD  n13e_ach  ;

      struct Channel_AD  n13f_ach  ;
    #endif
      struct Channel_AD  n14_ach  ;
    #ifdef _Ch14_Mux
      struct Channel_AD  n141_ach  ;

      struct Channel_AD  n142_ach  ;

      struct Channel_AD  n143_ach  ;

      struct Channel_AD  n144_ach  ;

      struct Channel_AD  n145_ach  ;

      struct Channel_AD  n146_ach  ;

      struct Channel_AD  n147_ach  ;

      struct Channel_AD  n148_ach  ;

      struct Channel_AD  n149_ach  ;

      struct Channel_AD  n14a_ach  ;

      struct Channel_AD  n14b_ach  ;

      struct Channel_AD  n14c_ach  ;

      struct Channel_AD  n14d_ach  ;

      struct Channel_AD  n14e_ach  ;

      struct Channel_AD  n14f_ach  ;
    #endif
      struct Channel_AD  n15_ach  ;
    #ifdef _Ch15_Mux
      struct Channel_AD  n151_ach  ;

      struct Channel_AD  n152_ach  ;

      struct Channel_AD  n153_ach  ;

      struct Channel_AD  n154_ach  ;

      struct Channel_AD  n155_ach  ;

      struct Channel_AD  n156_ach  ;

      struct Channel_AD  n157_ach  ;

      struct Channel_AD  n158_ach  ;

      struct Channel_AD  n159_ach  ;

      struct Channel_AD  n15a_ach  ;

      struct Channel_AD  n15b_ach  ;

      struct Channel_AD  n15c_ach  ;

      struct Channel_AD  n15d_ach  ;

      struct Channel_AD  n15e_ach  ;

      struct Channel_AD  n15f_ach  ;
    #endif
  #ifdef _CM3_
      struct Channel_AD  n16_ach  ;

      struct Channel_AD  n17_ach  ;

      struct Channel_AD  n18_ach  ;

       word  ADC_Scale[19];

  #endif
#else
      struct Channel_AD  nX1_ach  ;

      struct Channel_AD  nX2_ach  ;

      struct Channel_AD  nX3_ach  ;

      struct Channel_AD  nX4_ach  ;

      struct Channel_AD  nX5_ach  ;

      struct Channel_AD  nX6_ach  ;

      struct Channel_AD  nX7_ach  ;
#endif

      byte  Contrl_sum ;
  } ;
//----------------------
/*----- Таблица номиналов в отн.единицах (дискретах) и в физ. единицах -----*/

  struct  Nominals
  {
    struct  {  word code ;
               word rezerv2 ;
            } x;
      //  таблица 4-х структур номиналов:
    struct  {  word  oe , fe ;  } Id ;
    struct  {  word  oe , fe ;  } Ud ;
    struct  {  word  oe , fe ;  } Iv ;
    struct  {  word  oe , fe ;  } N  ;
#ifdef _KTE_GD
    struct  {  word  oe , fe ;  } Ig ;
    struct  {  word  oe , fe ;  } Ug ;
#endif
  } ;

  struct  Nominals_Dat
  {
      //  таблица номиналов датчиков:
    word   Id  ;
    word   Ud  ;
    word   Iv  ;
    word   N   ;
#ifdef _KTE_GD
    word   Ig ;
    word   Ug ;
#endif
  } ;

//    Блок уставок не восстанавливаемый по команде "F9-Типовые уставки":
//  для возможности задание номиналов датчиков и т.д.
  struct SBlok_Ustavok
  {
      //  Уставки номиналов: 1дискрета = 1А, 1В.
    struct  Nominals  NOM ;

    struct  Nominals_Dat Dat ;

    word Contrl_sum;
  };

 struct  Mashtab_const
  {
      word     Mashtab_Id  ;

      word     Mashtab_Ud  ;

      word     Mashtab_Iv  ;

      word     Mashtab_N   ;
#ifdef _KTE_GD
      word     Mashtab_Ig  ;

      word     Mashtab_Ug  ;
#endif
  };

struct MASHTAB {
                 word  Id,  Id_max ;
                 word  Ud,  Ud_max ;
                 word  Iv,  Iv_max ;
                 word  N ,  N_max  ;
#ifdef _KTE_GD
                 word  Ig,  Ig_max ;
                 word  Ug,  Ug_max ;
#endif
                 word  N_nom_Barabana;
               } ;

/*------------------------------------------------*/
#ifdef  _FLASH_INCLUDE
/*------------------------------------------------*/

         struct  Blok_Ustavok   _r  ;

         struct  ABlok_Ustavok  _ar ;

         struct  SBlok_Ustavok  _sr ;

         struct MASHTAB Mashtab ;

 //-----------------------------------------------------------
 // 11.09.2014 - Точный пересчёт масштабных коэффициентов :

 // 511 дискр  <=> 5     В     1.957 В
 // 200 дискр  <=> 1.957 В    --------- = 1.151 - Масштаб Id
 //                            1.7   В
 //-----------------------------------------------------------
 // 511 дискр  <=> 5     В     3.914 В
 // 400 дискр  <=> 3.914 В    --------- = 0.978 - Масштаб Id
 //                            4.0   В
 //-----------------------------------------------------------
 // 511 дискр  <=> 5     В     3.914 В
 // 400 дискр  <=> 3.914 В    --------- = 1.151 - Масштаб Ud
 //                            3.4   В
 //-----------------------------------------------------------
 // 511 дискр  <=> 5     В     3.914 В
 // 400 дискр  <=> 3.914 В    --------- = 0.978 - Масштаб Iv
 //                            4.0   В
 //-----------------------------------------------------------
 // 511 дискр  <=> 5     В     3.914 В
 // 400 дискр  <=> 3.914 В    --------- = 0.978 - Масштаб N
 //                            4.0   В
 //-----------------------------------------------------------
 // 511 дискр  <=> 5     В     1.957 В
 // 200 дискр  <=> 1.957 В    --------- = 1.151 - Масштаб Ig
 //                            1.7   В
 //-----------------------------------------------------------
 // 511 дискр  <=> 5     В     3.914 В
 // 400 дискр  <=> 3.914 В    --------- = 1.151 - Масштаб Ug
 //                            3.4   В
 //-----------------------------------------------------------
_x_far  const  struct  Mashtab_const  _mc  =
  {
#ifdef _KTE
   /* word     Mashtab_Id  ;            */  (w)( +1.151 * 256.0 ) , //( +1.17 * 256.0 ) ,
#else  // для Г-Д и КТЭВ :
   /* word     Mashtab_Id  ;            */  (w)( +0.978 * 256.0 ) , //( +1.00 * 256.0 ) ,
#endif
   /* word     Mashtab_Ud  ;            */  (w)( +1.151 * 256.0 ) , //( +1.14 * 256.0 ) ,
#if defined(_KTEV) && defined(_RVId) // 09.12.2020 15:52 исп. как масштаб якорных токов с номиналом 1.7В
   /* word     Mashtab_Iv  ;            */  (w)( +1.151 * 256.0 ) , //( +1.17 * 256.0 ) ,
#else
   /* word     Mashtab_Iv  ;            */  (w)( +0.978 * 256.0 ) , //( +1.0  * 256.0 ) ,
#endif
   /* word     Mashtab_N   ;            */  (w)( +0.978 * 256.0 ) , //( +1.0  * 256.0 ) ,
#ifdef _KTE_GD
   /* word     Mashtab_Ig  ;            */  (w)( +1.151 * 256.0 ) , //( +1.15 * 256.0 ) ,

   /* word     Mashtab_Ug  ;            */  (w)( +1.151 * 256.0 ) , //( +1.15 * 256.0 ) ,
#endif
  };

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

 extern  struct  Blok_Ustavok   _r  ;

 extern  struct  ABlok_Ustavok  _ar ;

 extern  struct  SBlok_Ustavok  _sr ;

 extern  struct  MASHTAB Mashtab ;

 extern _x_far  const  struct  Mashtab_const  _mc ;

/*------------------------------------------------*/
#endif
/*------------------------------------------------*/

#endif
