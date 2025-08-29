#ifndef _rt_h
#define _rt_h

#define   UdSr  Ud  // DAN 10.11.2016 9:44 - Переменной объявлена Ud , а в программах используется UdSr .
//#define IDV   Id  // DAN 10.11.2016 9:44 - Пережиток прошлого , в КТЭ никогда не использовалось ...

    void        ZadSkor_Analog ( void ) ;
    void        ZadSkor_BolsheMenshe ( void ) ;
    void        Izm_TG ( word num )  ;      //150-200mcs
    void        Izm_Skor_EDS ( void ) ;
    void        ZadSkor_Tolchki ( void ) ;
    void        Pult_Tolchki ( void ) ;
    void        Zad_Skor_4_20 ( word num ) ;
    word        Shtat_ConfigReg ( word code ) ;
    word        obj_ConfigReg ( word code ) ;
    word        Filtr_Sk ( word num ) ;
    word        Econom_polja ( void ) ;

  //---
    void        DatEDS_Ud ( void ) ;
    void        RegSk ( void ) ;
    void        Ugol_Pol ( void ) ;
    void        RegPol ( void ) ;
    void        Revers ( void ) ;
    void        Zadan_RT(void);
    void        RegTok ( void ) ;
    void        RTg ( void ) ;
    void        RNg ( void ) ;
    void        Linear ( void ) ;
    void        Izm_GD ( void ) ;
    void        Fors_Temp_RTg ( void ) ;
    void        UgZad ( void ) ;
    void        ZIUg_Ogr ( void ) ;
    void        Ig_izm_conv ( void ) ;
    void        ZISkor_Ogr ( void ) ;
    void        Fors_Temp ( void ) ;
    void        RDN ( void ) ;
    void        Stat_Tok ( void ) ;
    void        RRS ( void ) ;
    void        Control_Buksovka ( void ) ;
    void        RVId_Reg ( void ) ;
    void        RVId_Izm_Conv ( void ) ;

    void        RegTok2 (void) ;
    void        Linear2 (void) ;
//----------------------------------------------

 union RegFlags {
      word all ;
      struct
      {
          word  ZdSkor  : 1;
          word  Skor    : 1;
          word  ZISk    : 1;
          word  OuRS    : 1;

          word  IchRS   : 1;
          //word  Igen    : 1;
          word  rtg_int_p : 1 ;
          word  rtg_int_m : 1 ;

          word  rng_int_p : 1 ;
          word  rng_int_m : 1 ;

          word  rp_int_p : 1 ;
          word  rp_int_m : 1 ;
      } _ ;
    }   ;

// ЗИ для РТ :
struct ZIRT {
#if _K_diskr == 1 // 10-ти разрядный АЦП - 200d .
            word in, out ;  /* Вход / Выход   ЗИ.  */
#else // 12-ти разрядный АЦП - 800d .
            float in, out ; /* Вход / Выход   ЗИ.  */
#endif
            word drob  ;    /* Дробная часть выхода ЗИ.  */
            word *temp_p ;  /* Адрес уставки тепма, размерность которой: "дискреты в секунду".  */
            word *temp_m ;  /* Адрес уставки тепма, размерность которой: "дискреты в секунду".  */
            word time  ;    /* Время последней отработки ЗИ.  */
          } ;

//----------------------------------------------
    void        Zad_IntensRT ( struct ZIRT *zip ) ;
    void        Set_ZIRT ( struct ZIRT *zip , word ) ;
//----------------------------------------------
 union Pr  {
              byte all ;
              struct {
                  word  Revers2    : 1;
                  word  Gashen     : 1;
                  word  int_p      : 1;
                  word  int_m      : 1;
                  word  torm_zi_p  : 1;
                  word  torm_zi_m  : 1;
                  word  VR1        : 1;
                  word  Revers1    : 1;
                } _ ;
            } ;

  union Pr_liga {
                  word all ;
                  struct
                  {
                     word zahv_ok   : 1 ;
                     word liga_ok   : 1 ;
                     word zahv2_ok  : 1 ;
                     word liga2_ok  : 1 ;

                     word buks      : 1 ;
                     word did       : 1 ;
                     word dn        : 1 ;
                     word b_trig    : 1 ;

                     word buk_count : 4 ;

                     word rezerved  : 4 ;
                  }  _ ;
                } ;

// Для регулятора выравнивания якорных токов _RVId
struct RegVId
{
    word dId;      // рассогласование якорных токов
    word dIf;      // рассогласование токов возбуждения
    word Integr;   // интегратор
    word Drob;     // дробь интегратора
    word Out;      // выход регулятора
    word dIfz;     //
    word Time;     // время последнего вызова регулятора
    word Iv1_z;
    word Iv1_zad;
    word Iv1_dlt;
    word Iv1_korr;
    word Iv2_z;
    word Iv2_zad;
    word Iv2_dlt;
    word Iv2_korr;
    word Id1_full; // для измерения якорного тока 1-го двигателя
    word Id2_full; // для измерения якорного тока 2-го двигателя
    word Id1;      // якорный ток 1-го двигателя
    word Id2;      // якорный ток 2-го двигателя
    word IDV1;     // модуль якорного тока 1-го двигателя
    word IDV2;     // модуль якорного тока 2-го двигателя
    union
    {
        word all;
        struct
        {
            word int_p    : 1;
            word int_m    : 1;
            word Iv1_max  : 1;
            word Iv2_max  : 1;

            word Work     : 1;
            word rezerv5  : 1;
            word rezerv6  : 1;
            word rezerv7  : 1;
            //----
            word rezerv8  : 1;
            word rezerv9  : 1;
            word rezerv10 : 1;
            word rezerv11 : 1;

            word rezerv12 : 1;
            word rezerv13 : 1;
            word rezerv14 : 1;
            word rezerv15 : 1;
        } _ ;
    } flg ;
};

/*------------------------------------------------*/
#ifdef _FLASH_INCLUDE
/*------------------------------------------------*/

union  RegFlags   RegFlg ;

/*--------------- Для резистора -------------*/

struct Izm_analog  zad_res ;

/*--------------- Для Регулятора Тока -------------*/

#ifdef   _KTE_GD
        word     IDV_g, IDN_g, IDN_g1, Ig_full, Igen ;
        word     Ug_full, Ugen, Ugx_full, Ugenx1, Ugenx8 ;
        word     Ug_zx, Integr_rn, Out_rn, Integr_rn_drob ;
        struct ZI   zi_oprob ;
        word     Ig_forUgz_Out , Ig_forUgzR_Out ;
#else
        word     ZIDN1 ;
        word     OIRT1;
        word     INN;
        word     INN_dvig ;
        word     IDN;
        word     IDN1;
      //byte     DRINN;
        byte     ED1;
#endif
        word     ZIDN;

        word     IDV;
#ifdef  _SIFU2_
        word     IDV2;
        word     ZIDN_2_ , ZIDN1_2_ , IDN_2_ , IDN1_2_ , INN_2_ , OIRT_2_ , OIRT1_2_ , OIRT_drob_2_ , KRTI_2_ , ORT_2_ ;
        word     ust_rINN0 , ust_rKRTP , ust_rKRTPRI , ust_rKRTNI ;
#endif
        word     _r_KRTP   , an_KRTP   ;
        word     _r_KRTPRI , an_KRTPRI ;
        word     _r_KRTNI  , an_KRTNI  ;
        word     _or_KRTP_2_   , an_KRTP_2_   ;
        word     _or_KRTPRI_2_ , an_KRTPRI_2_ ;
        word     _or_KRTNI_2_  , an_KRTNI_2_  ;

        word   OuRegS;

        word   KRSI_ind , KRSP_ind ;
        word   Ki_REDS_ind , Kp_REDS_ind ;

        word     OIRT , OIRT_drob ;

        word     ORT;                   /*выход регулятора тока  */

        word     KRTI ;

        word     EDS;

        word     EDS_dop_kod , EDS_dop_kod_nf ;

        word     EDS_shest_kod , EDS_shest_kod_nf ;

        word     EDS1;

        byte     ZNEDS;

        byte     ZNEDS1;

        word     prEDS ;

        byte     ZnUdSr     ;

        byte     ZnEDS_P    ;

        word     EDS_P      ;

        word     Kompen_Ud , UdSr_Komp ;

        word     Ud, Ud_full, Ud_off, Id_off ;

#ifdef  Udv_ach
        word     Udv_full ;
#endif

#ifdef  _KTE_GD
        word     Udv ;
#endif

        //word     Udposl     ;

        word     KFE       ;

        byte     pFE   ;
        byte     Shtat_temp ; // флаг для замены темпов ЗИС .
        byte     Fors_temp ;  // флаг для замены темпов ЗИС .
        byte     Reviz_temp ; // флаг для замены темпов ЗИС .

#ifndef _WM591
_x_far const byte  TABLINN [ ] =
            {     0xff,0xff,0xfe,0xfe,0xfd,0xfd,0xfc,0xfc,0xfb,0xfb,0xfa,0xfa,
                  0xf9,0xf9,0xf8,0xf8,0xf7,0xf7,0xf6,0xf5,0xf5,0xf4,0xf3,0xf3,
                  0xf2,0xf1,0xf0,0xef,0xee,0xed,0xec,0xeb,0xea,0xe9,0xe8,0xe7,
                  0xe6,0xe5,0xe4,0xe3,0xe2,0xe1,0xe0,0xdf,0xde,0xdd,0xdc,0xdb,
                  0xda,0xd9,0xd8,0xd7,0xd6,0xd5,0xd4,0xd3,0xd2,0xd1,0xcf,0xce,
                  0xcc,0xcb,0xc9,0xc8,0xc6,0xc4,0xc2,0xc0,0xbe,0xbc,0xba,0xb8,
                  0xb6,0xb4,0xb2,0xb0,0xae,0xac,0xaa,0xa8,0xa6,0xa4,0xa2,0xa0,
                  0x9e,0x9c,0x9a,0x98,0x95,0x93,0x90,0x8e,0x8b,0x89,0x86,0x84,
                  0x81,0x7f,0x7c,0x7a,0x77,0x74,0x71,0x6e,0x6b,0x68,0x65,0x62,
                  0x5f,0x5c,0x59,0x55,0x52,0x4e,0x4b,0x48,0x45,0x41,0x3d,0x39,
                  0x35,0x30,0x2a,0x25,0x01f,0x19,0x13,0x13
             };
#endif

//NEW_ZI struct ZI   zi_rs ;
CNotLinearFourTempZI zi_rs;// = CNotLinearFourTempZI::CNotLinearFourTempZI();  //NEW_ZI
CNotLinearJoystick notlinear_joystick;
struct ZIRT zi_rt ;
 #ifdef  _SIFU2_
struct ZIRT zi_rt2 ;
 #endif


#ifdef   _KTE_GD
struct ZI   zi_rtg ;
#endif

   /*---------  Ячейки результатов измерений (копии "AD_RESULT")  ---------*/

   /* измерение Id в 12 градусах после импульса */
        word     Id_full ;

#ifdef  Itt_ach
        word     Itt_full , Idtt ;
#endif

#ifdef  Itt1_ach
        word     Itt1_full , Idtt1 ;
#endif
#ifdef  Itt2_ach
        word     Itt2_full , Idtt2 ;
#endif

        word Iproboy1 ; // для программы контроля пробоя тиристоров .
        byte n , nn , i ;
#ifdef  _SIFU2_
        word Iproboy2 ;
        byte n2 , nn2 ;
#endif

      //word     IDV_old ; // для программы контроля открытия тиристоров .

#ifdef  _SIFU2_
        word     Id2_full, Id_sum_full, Id_sum, Id2_dop_kod ;
        word     Id_divBy2_abs ;
#endif

#ifdef  IA1_ach
        word    IA1_full , IA1 ;
#endif
#ifdef  IB1_ach
        word    IB1_full , IB1 ;
#endif
#ifdef  IC1_ach
        word    IC1_full , IC1 ;
#endif

#ifdef  IA2_ach
        word    IA2_full , IA2 ;
#endif
#ifdef  IB2_ach
        word    IB2_full , IB2 ;
#endif
#ifdef  IC2_ach
        word    IC2_full , IC2 ;
#endif

#ifdef  IA3_ach
        word    IA3_full , IA3 ;
#endif
#ifdef  IB3_ach
        word    IB3_full , IB3 ;
#endif
#ifdef  IC3_ach
        word    IC3_full , IC3 ;
#endif

#ifdef  IA4_ach
        word    IA4_full , IA4 ;
#endif
#ifdef  IB4_ach
        word    IB4_full , IB4 ;
#endif
#ifdef  IC4_ach
        word    IC4_full , IC4 ;
#endif

#ifdef  Id_sr_ach
        word     Id_sr, Id_sr_full ;
#endif

#ifdef  Id2_sr_ach
        word     Id2_sr, Id2_sr_full ;
#endif

#ifdef  EDS_ach
        word     iEDS_full,  iEDS ;
#endif
//---
#ifdef _RDN
        word     Id_2v , dId , RDN_Out ;
        word     N_2v  , dN  ;
  #ifdef Id_2v_ach
        word     Id_2v_full ;
  #endif
  #ifdef N_2v_ach
        word     N_2v_full ;
  #endif
#endif
//---
#ifdef _BUKSOVKA
        word     Time_buks ;
#endif
//---
#ifdef _DST
        word     Sk1 , dSkor , Time_stat , Id_Din , Id_Stat ;
        struct   fil  Id_Stat_flt ;
        byte     puls_Istat ;
#endif
#ifdef _RRS
        word     Time_Ist ;
        word     Time_Ist2 ;
        word     Id_stat_2v ;
   #ifdef Id_stat_2v_ach
        word     Id_stat_2v_full ;
   #endif
        union    Pr_liga  liga ;
#endif
//---
#ifdef _RVId
   struct RegVId RVId;
#endif
//---
union Pr  Prz ;

word Id_dop_kod ;
word Ogr_zi_rev ;

/*----------- Для Регулятора Положения -----------*/

#ifdef _REG_POL
word  Ugol , ZUgol ;
word  Integr_RP , OuRP ;
word  ZIUgol ;
word  RP_in_sqr ;
//struct ZI   zi_rp ;
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union  RegFlags   RegFlg ;

extern struct Izm_analog  zad_res ;

#ifdef   _KTE_GD
extern  word     IDV_g, IDN_g, IDN_g1, Ig_full, Igen ;
extern  word     Ug_full, Ugen, Ugx_full, Ugenx1, Ugenx8 ;
extern  word     Ug_zx, Integr_rn, Out_rn, Integr_rn_drob ;
extern  struct ZI   zi_oprob ;
extern  word     Ig_forUgz_Out , Ig_forUgzR_Out ;
#else

extern  word     ZIDN1 ;
extern  word     OIRT1;
extern  word     INN;
extern  word     INN_dvig ;
extern  word     IDN;
extern  word     IDN1;
extern  byte     DRINN;
extern  byte     ED1;

#endif

extern  word     ZIDN;

extern  word     IDV;
 #ifdef  _SIFU2_
extern  word     IDV2 ;
extern  word     ZIDN_2_ , ZIDN1_2_ , IDN_2_ , IDN1_2_ , INN_2_ , OIRT_2_ , OIRT1_2_ , OIRT_drob_2_ , KRTI_2_ , ORT_2_ ;
extern  word     ust_rINN0 , ust_rKRTP , ust_rKRTPRI , ust_rKRTNI ;
 #endif
extern  word     _r_KRTP   , an_KRTP   ;
extern  word     _r_KRTPRI , an_KRTPRI ;
extern  word     _r_KRTNI  , an_KRTNI  ;
extern  word     _or_KRTP_2_   , an_KRTP_2_   ;
extern  word     _or_KRTPRI_2_ , an_KRTPRI_2_ ;
extern  word     _or_KRTNI_2_  , an_KRTNI_2_  ;

extern  word   OuRegS;

extern  word   KRSI_ind , KRSP_ind ;
extern  word   Ki_REDS_ind , Kp_REDS_ind ;

extern  word     OIRT , OIRT_drob ;

extern  word     ORT;

extern  word     KRTI  ;

/*-------------------- ЭДС -----------------------------*/

extern  word     EDS;

extern  word     EDS_dop_kod , EDS_dop_kod_nf ;

extern  word     EDS_shest_kod , EDS_shest_kod_nf ;

extern  word     EDS1;

extern  byte     ZNEDS;

extern  byte     ZNEDS1;

extern  word     prEDS ;

extern  byte     ZnUdSr     ;

extern  byte     ZnEDS_P    ;

extern  word     EDS_P      ;

extern  word     Kompen_Ud , UdSr_Komp ;

extern  word     Ud , Ud_full, Ud_off , Id_off ;

#ifdef  Udv_ach
extern  word     Udv_full ;
#endif

#ifdef  _KTE_GD
extern  word     Udv ;
#endif

//extern  word     Udposl     ;


extern _x_far const byte  TABLINN [] ;

//NEW_ZI extern  struct ZI   zi_rs ;
extern  CNotLinearFourTempZI zi_rs;  //NEW_ZI
extern  CNotLinearJoystick notlinear_joystick;  //NEW_ZI
extern  struct ZIRT zi_rt ;
 #ifdef  _SIFU2_
extern  struct ZIRT zi_rt2 ;
 #endif

#ifdef   _KTE_GD
extern  struct ZI   zi_rtg ;
#endif

extern  word     KFE       ;

extern  byte     pFE   ;
extern  byte     Shtat_temp ; // флаг для замены темпов ЗИС .
extern  byte     Fors_temp ;  // флаг для замены темпов ЗИС .
extern  byte     Reviz_temp ; // флаг для замены темпов ЗИС .


   /*---------  Ячейки результатов измерений (копии "AD_RESULT")  ---------*/

   /* измерение Id в 12 градусах после импульса */
extern  word     Id_full ;

#ifdef  Itt_ach
extern  word     Itt_full , Idtt ;
#endif

#ifdef  Itt1_ach
extern  word     Itt1_full , Idtt1 ;
#endif
#ifdef  Itt2_ach
extern  word     Itt2_full , Idtt2 ;
#endif

extern  word Iproboy1 ; // для программы контроля пробоя тиристоров .
extern  byte n , nn , i ;
#ifdef  _SIFU2_
extern  word Iproboy2 ;
extern  byte n2 , nn2 ;
#endif

//extern  word     IDV_old ; // для программы контроля открытия тиристоров .

#ifdef  _SIFU2_
extern  word     Id2_full, Id_sum_full, Id_sum, Id2_dop_kod ;
extern  word     Id_divBy2_abs ;
#endif

#ifdef  IA1_ach
extern  word    IA1_full , IA1 ;
#endif
#ifdef  IB1_ach
extern  word    IB1_full , IB1 ;
#endif
#ifdef  IC1_ach
extern  word    IC1_full , IC1 ;
#endif

#ifdef  IA2_ach
extern  word    IA2_full , IA2 ;
#endif
#ifdef  IB2_ach
extern  word    IB2_full , IB2 ;
#endif
#ifdef  IC2_ach
extern  word    IC2_full , IC2 ;
#endif

#ifdef  IA3_ach
extern  word    IA3_full , IA3 ;
#endif
#ifdef  IB3_ach
extern  word    IB3_full , IB3 ;
#endif
#ifdef  IC3_ach
extern  word    IC3_full , IC3 ;
#endif

#ifdef  IA4_ach
extern  word    IA4_full , IA4 ;
#endif
#ifdef  IB4_ach
extern  word    IB4_full , IB4 ;
#endif
#ifdef  IC4_ach
extern  word    IC4_full , IC4 ;
#endif

#ifdef  Id_sr_ach
extern  word     Id_sr, Id_sr_full ;
#endif

#ifdef  Id2_sr_ach
extern  word     Id2_sr, Id2_sr_full ;
#endif

#ifdef  EDS_ach
extern  word     iEDS_full,  iEDS ;
#endif
//---
#ifdef _RDN
extern  word     Id_2v , dId , RDN_Out ;
extern  word     N_2v  , dN  ;
  #ifdef Id_2v_ach
extern  word     Id_2v_full ;
  #endif
  #ifdef N_2v_ach
extern  word     N_2v_full ;
  #endif
#endif
//---
#ifdef _BUKSOVKA
extern  word     Time_buks ;
#endif
//---
#ifdef _DST
extern  word     Sk1 , dSkor , Time_stat , Id_Din , Id_Stat ;
extern  struct   fil  Id_Stat_flt ;
extern  byte     puls_Istat ;
#endif
#ifdef _RRS
extern  word     Time_Ist ;
extern  word     Time_Ist2 ;
extern  word     Id_stat_2v ;
   #ifdef Id_stat_2v_ach
extern  word     Id_stat_2v_full ;
   #endif
extern  union    Pr_liga  liga ;
#endif
//---
#ifdef _RVId
extern struct RegVId RVId;
#endif
//---
  extern  union Pr  Prz ;

  extern word Id_dop_kod ;

/*----------- Для Регулятора Положения -----------*/

#ifdef _REG_POL
extern  word  Ugol , ZUgol ;
extern  word  Integr_RP , OuRP ;
extern  word  ZIUgol ;
extern  word  RP_in_sqr ;
//extern  struct ZI   zi_rp ;
#endif

extern  word Ogr_zi_rev ;

/*------------------------------------------------*/
#endif
#endif

