#ifndef _avar_h
#define _avar_h
/* 08.12.2020 8:32 "Usred.h" подключается в "Include.h"
#ifdef   It_ach // Для агрегатов , у которых есть ток тормоза .
    #include "usred.h"
#endif
*/
    void        Control_QKDT ( void ) ;
    void        Control_Ucc ( void ) ;        // Контроль питающих напряжений.
    void        Init_posle_DistSbr ( void ) ;
    void        Init_Regs ( void ) ;
    void        USEL_Work ( void ) ;

    void        Control_Id_Max ( void ) ;
    void        Control_E_Max  ( void ) ;
    void        Control_N_Max  ( void ) ;
    void        Control_Stoyanka ( void ) ;
    void        Control_Ig_Ug_Max (void);
    void        Control_DatSkor ( void ) ;
    word        Control_UgOstat ( void ) ;
    word        Control_Skor ( void ) ;
    void        Rabota ( void ) ;
    void        Sborka_Gotovn ( void ) ;
    word        Short_ImpLong ( void ) ;
    word        Short_ImpLongQubler ( word code ) ;
    void        Otkl_Q1 ( void ) ;
    void        Clr_Q1 ( void ) ;
    void        Clr_Q1_Q2 ( void ) ;
    void        GerconAC_Interrupt (void);
    void        GerconDC_Interrupt (void);
    void        Control_Gercon ( void ) ;
    void        Control_dt_Avar ( word code ) ;
    word        Contr_Insulat_G ( word num ) ;
    word        Contr_Insulat_D ( word num ) ;
//----
    word        MechTorm_upr ( word num ) ;
    void        Mashtab_Dat ( void ) ;
    void        Control_otkr_tir ( word num ) ;

    void        Contr_Ttrans_4_20 ( word num ) ;
    void        T_Izm_Dat (  word num ) ;
    void        T_Izm_Dat1(void);

    void        Control_Pusk ( void ) ;
    extern      void  SkorAD_epa_init ( void ) ;
    extern      void  SkorAD_Interrupt ( void ) ;
    void        sifu_rot ( void ) ;

    void        FP_L ( void ) ;

 #define _MT_Init        0
 #define _MT_Upr         1
 #define _MT_Id_Zad_Ogr  2
//----
 #define   _ConOtkr_Init              0
 #define   _ConOtkr_DS1_Init          1
 #define   _ConOtkr_Sborka_Gotovn     2
 #define   _ConOtkr_Rabota            3
 #define   _ConOtkr_Avar_Otkl         4
//----

union  AvarBits
    {
        word all ;
        struct {
#ifndef _Union_FR
                 word DistSbros : 1 ;
                 word Emax      : 1 ;
                 word Sdvig_imp : 1 ;
                 word Nmax      : 1 ;

                 word P24       : 1 ;
                 word P12       : 1 ;
                 word N12       : 1 ;
                 word OneQ1     : 1 ;

                 word OneQ2     : 1 ;
                 word Ostanov   : 1 ;
                 word Id2_max   : 1 ;
                 word GerconDC  : 1 ;

                 word OtklQ2    : 1 ;  //  Признак подачи команды на откл. Q1.
                 word OtklQ1    : 1 ;  //  Признак подачи команды на откл. Q1.
                 word Gercon    : 1 ;  //  Признак срабатывания "Геркона".
                 word Id_max    : 1 ;  //  Признак срабатывания защиты.
#else     // для однообразной регистрации в следе.
                 word Id_max    : 1 ;
                 word Gercon    : 1 ;
                 word OtklQ1    : 1 ;
                 word OtklQ2    : 1 ;

                 word GerconDC  : 1 ;
                 word Id2_max   : 1 ;
                 word Ostanov   : 1 ;
                 word OneQ2     : 1 ;

                 word OneQ1     : 1 ;
                 word N12       : 1 ;
                 word P12       : 1 ;
                 word P24       : 1 ;

                 word Nmax      : 1 ;
                 word Sdvig_imp : 1 ;
                 word Emax      : 1 ;
                 word DistSbros : 1 ;
#endif
               } _ ;
    }  ;

union  AvarBits2
    {
        word all ;
        struct {
#ifndef _Union_FR
                 word GerconAC2   : 1 ;  //  Признак срабатывания "Геркона".
                 word APV_Gercon  : 1 ;
                 word _1P         : 1 ;
                 word _2P         : 1 ;

                 word PUM         : 1 ;
                 word RV1         : 1 ;
                 word GerconAC3   : 1 ;  //  Признак срабатывания "Геркона" в ШС3 .
                 word GerconAC4   : 1 ;  //  Признак срабатывания "Геркона" в ШС4 .

                 word Id_sum_max  : 1 ;
                 word rezerv      : 7 ;
#else     // для однообразной регистрации в следе.
                 word rezerv      : 7 ;
                 word Id_sum_max  : 1 ;

                 word GerconAC4   : 1 ;  //  Признак срабатывания "Геркона" в ШС4 .
                 word GerconAC3   : 1 ;  //  Признак срабатывания "Геркона" в ШС3 .
                 word RV1         : 1 ;
                 word PUM         : 1 ;

                 word _2P         : 1 ;
                 word _1P         : 1 ;
                 word APV_Gercon  : 1 ;
                 word GerconAC2   : 1 ;
#endif
               } _ ;
    }  ;

#ifdef Insul_G_ach
   //  Настраиваем контроль изол.возб.ген. на выход Ud.
  #define  _UoutG              UdSr
  #define  _UoutG_nom( data )  _Ud_nom( data )
#endif

#ifdef Insul_D_ach
   //  Настраиваем контроль изол.возб.дв. на номинал напряжения возб. двиг.
  #define  _UoutD              Uf
  #define  _UoutD_nom( data )  _Uf_nom( data )
#endif

//---------------- Все маски можно переопределить в OBJ.H -------------------------

 // Исключающее ИЛИ : единицы , нуль на месте _Av_IdMax :
#ifndef    _Otkl_Q2_Mask
  // 1. Максимальный выпрямленный ток .
  // 2. Максимальный выпрямленный ток , измеренный общим шунтом в 12-типульсной схеме .
  #define  _Otkl_Q2_Mask    ( _Av_All ^ ( _Av_IdMax | _Av_Id_sum_Max ) )
#endif

#ifndef    _Otkl_Q2_Mask2
  // 1. Максимальный выпрямленный ток Ведомого моста в 12-типульсной схеме .
  // 2. Максимальный выпрямленный ток Якоря 1 при параллельном соединении якорей ( для РВId 2х якорей через возбуждение ) .
  // 3. Максимальный выпрямленный ток Якоря 2 при параллельном соединении якорей ( для РВId 2х якорей через возбуждение ) .
  #define  _Otkl_Q2_Mask2   ( _Av_All ^ ( _Av2_Id2_Max | _Av2_Id1Max | _Av2_Id2Max ) )
#endif

#ifndef    _Mask_DistSbr    // Для агрегатов с 4-мя ШС все варианты сообщений Герконов .
  #define  _Mask_DistSbr    ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
#endif

#ifndef    _Mask_DistSbr2
  #define  _Mask_DistSbr2   ( 0 ) // пока не требуется
#endif

#ifndef    _Mask_Avar       // Для агрегатов с 4-мя ШС все варианты сообщений Герконов .
  #define  _Mask_Avar       ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
#endif

#ifndef    _Mask_Avar2
  #define  _Mask_Avar2      ( 0 ) // пока не требуется
#endif

 //   Маска для аварий, при которых не выдается предупреждение в "Сборке Готовности" ,
 // а значит и выдается Готовность :
#ifndef    _Mask_AvarPreduprGotovn  // Для агрегатов с 4-мя ШС все варианты сообщений Герконов .
  #define  _Mask_AvarPreduprGotovn  ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 )
#endif

 //   Маска для несбрасываемых в "Сборке Готовности" аварий :
 //  _Av_AF1 - 17.02.2009 8:05 DAN Убрано , согласовано с АП .
#ifndef    _Mask_AvarSbr    // 1-4. Для агрегатов с 4-мя ШС все варианты сообщений Герконов .
                            //   5. Питание усилителей ИУ .
                            //   6. Максимальный выпрямленный ток .
                            //   7. Максимальный выпрямленный ток , измеренный общим шунтом в 12-типульсной схеме .
                            //   8. Максимальный ток возбужления ( для систем с двумя СИФУ - Якоря и Возбудителя ) .
  #define  _Mask_AvarSbr    ( _Av_Gercon | _Av_GerconDC | _Av_Gercon3 | _Av_Gercon4 | \
                              _Av_PUM | _Av_IdMax | _Av_Id_sum_Max | _Av_Iv_Max )
#endif

 //   Маска для несбрасываемых в "Сборке Готовности" аварий :
 //  _Av2_AF2 - 17.02.2009 8:05 DAN Убрано , согласовано с АП .
#ifndef    _Mask_AvarSbr2
  // 1. Максимальный выпрямленный ток Ведомого моста в 12-типульсной схеме .
  // 2. Питание усилителей ИУ в Ведущем мосту в 12-типульсной схеме .
  // 3. Питание усилителей ИУ в Ведомом мосту в 12-типульсной схеме .
  // 4. Максимальный выпрямленный ток Якоря 1 при параллельном соединении якорей ( для РВId 2х якорей через возбуждение ) .
  // 5. Максимальный выпрямленный ток Якоря 2 при параллельном соединении якорей ( для РВId 2х якорей через возбуждение ) .
  #define  _Mask_AvarSbr2   ( _Av2_Id2_Max | _Av2_1P | _Av2_2P | \
                              _Av2_Id1Max | _Av2_Id2Max )
#endif

 //   Маска для несбрасываемых в "Сборке Готовности" предупреждений :
 //  _Pr_AF1P - 17.02.2009 8:05 DAN Убрано , согласовано с АП .
 //  _Pr_OffsetAch - 22.04.2020 08:31 убрал
#ifndef    _Mask_PreduprSbr
        #define  _Mask_PreduprSbr ( _Pr_P24 | _Pr_P12 | _Pr_N12 | _Pr_Perecl_DS | \
                                    _Pr_Rezerv_Zam | _Pr_TipUst | _Pr_WDT )
#endif

 //   Маска для несбрасываемых в "Сборке Готовности" предупреждений :
 //  _Pr2_AF2P - 17.02.2009 8:05 DAN Убрано , согласовано с АП .
#ifndef    _Mask_PreduprSbr2
  #define  _Mask_PreduprSbr2 ( _Pr2_ProbM1_VT11_24 | _Pr2_ProbM1_VT12_25 | _Pr2_ProbM1_VT13_26 | \
                               _Pr2_ProbM1_VT14_21 | _Pr2_ProbM1_VT15_22 | _Pr2_ProbM1_VT16_23 | \
                               _Pr2_ProbM2_VT11_24 | _Pr2_ProbM2_VT12_25 | _Pr2_ProbM2_VT13_26 | \
                               _Pr2_ProbM2_VT14_21 | _Pr2_ProbM2_VT15_22 | _Pr2_ProbM2_VT16_23 | \
                               _Pr2_ProbM3_VT11_24 | _Pr2_ProbM3_VT12_25 | _Pr2_ProbM3_VT13_26 | \
                               _Pr2_ProbM3_VT14_21 | _Pr2_ProbM3_VT15_22 | _Pr2_ProbM3_VT16_23 | \
                               _Pr2_ProbM4_VT11_24 | _Pr2_ProbM4_VT12_25 | _Pr2_ProbM4_VT13_26 | \
                               _Pr2_ProbM4_VT14_21 | _Pr2_ProbM4_VT15_22 | _Pr2_ProbM4_VT16_23 )
#endif

 //   Маска для сбрасываемых в "Сборке Готовности" сервисных сообщений :
#ifndef    _Mask_ServiceSbr
  #define  _Mask_ServiceSbr ( _Srv_Not_Nul_Id | _Srv_Not_Iv | _Srv_NoCAN_QK )
#endif

 //   Маска для сбрасываемых в "Сборке Готовности" сервисных сообщений :
#ifndef    _Mask_ServiceSbr2
  #define  _Mask_ServiceSbr2 ( 0 ) // пока не требуется
#endif

 //   Маска для сбрасываемых в "Сборке Готовности" сервисных сообщений :
#ifndef    _Mask_ServiceSbr3
  #define  _Mask_ServiceSbr3 ( 0 ) // пока не требуется
#endif
//-----------------------------------------------------------------------------

//------------------------------

#define _sqr3_mask    1.732050808    // корень из 3 .
#define _sqr2_mask    1.414213562    // корень из 2 .
#define _sqr2_3mask   0.8164965809   // корень из 2/3 .
#define _PI           3.1415926535   // число пи .
#define _Ts           0.000250       // период дискретизации - 1 / 4кГц = 250 мкс .
#define _RadS_ObMin   9.549296585    // Коэффициент для перевода радиан в секунду в обороты в минуту .
                                     //
                                     // 1 рад       60
                                     // ------ = --------
                                     // 1 сек     2 * _PI
                                     //

#define _ADf_Nom     _Ud_Nom         // Для рассчетов Грыгорыча приводим номинал
#define _Kmasht      _Ud_Nom/_Id_Nom // к одним единицам .

/*------------------------------------------------*/

#ifdef  _AVAR_INCLUDE  //_MAIN_INCLUDE - 25.03.2015 Исправлено , чтоб были переменные в этом инклюде .
/*------------------------------------------------*/

/*--------------- Для Регулятора Скорости -------------*/
        word     Z_Skor ;

        word     ZISkor ;

        word     Skor ;

        word     TG ;
#ifdef  TGx_ach
        word     TGx1 , TGx8 ;
#endif
        word     OuRegS_dop_kod ;

        word     OuIchRS  ;
        word     OuIchRS_k  ;
        word     Delta_Sk ;

#ifdef bi_RS_P
        word     _r_KRSP ;
#endif

        word Delt_n , Kf_Sk , Skor_f , drob_FSk , Skor_ind ;
        byte dfgg ;

 //union  RegFlags   RegFlg ; DAN - 11.12.2017 16:27 перенёс в RT.H .
/*-----------------------------------------------------*/

 word   Zapas_Pointer ;
 word   Skor_r ;
 byte   time_VR1 ;

 _register union  AvarBits   Av ;
 _register union  AvarBits2  Av2 ;

#ifdef bi_BV1
word  Timer_BV1 ;
#endif
//---
#ifdef bi_BV_2 // Для ШС2 в 12-пульсном СИФУ :
word  Timer_BV2 ;
#endif
//---
#ifdef bi_Vent_Dvig
word  Timer_Vent_Dvig ;
#endif
//---
#ifdef bi_MasloSmazka
word  Timer_MasloSmazka ;
#endif
//---
#ifdef bi_Smazka_Podsh
word  Timer_Smazka_Podsh ;
#endif
//---
#ifdef bi_Gashenie
 word  time_gash_polja ;
#endif

 word   Ttrans  , Ttrans_4_20  ;

 word upr_label , upr_ax , upr_bx , upr_time ;

 byte   F2regim , c_index ;
 word   av_label  ;
 byte   N_Ucc , N_Ucc2 ;
 word   P24_Ucc , P12_Ucc , N12_Ucc ;

#ifdef PUM_ach
 word PUM_Ucc ;
#endif
#ifdef _1P_ach
 word _1P_Ucc ;
#endif
#ifdef _2P_ach
 word _2P_Ucc ;
#endif

#ifdef  bi_KP
 word   Time_KP ;
#endif
#ifdef  bi_KP2
 word   Time_KP2 ;
#endif
#ifdef  bi_KP3
 word   Time_KP3 ;
#endif
#ifdef  bi_KP4
 word   Time_KP4 ;
#endif
#ifdef  bi_KP_KZ
 word   Time_KP_KZ ;
#endif

 word   Stoyanka_Time , Stoyanka_Timer ;

 word   time_Id_max   ;
 word   time_Iv_min   ;
 word   Time_do_OtklImp   ;
 //word   Time_do_OtklSleda ;
 word   TimeOtklQ1  ;
 word   TimeOtklQ2  ;
lword   mask_predupr ;
lword   mask_predupr2 ;

#ifdef _TRETIY_REG
lword   mask_predupr3 ;
#endif

#ifdef _INTERPRETER
lword   mask_predupr_obj;
lword   mask_service_obj;
#endif

word    S_ImpLong ;
byte    RT_trigg  ; // признак отпускания герк. для контр. его повторн. срабат.
word    gercon_time ;

 word Time_econom ;

#ifdef _KTEV
 word Time_econom_KTEV ;
#endif

 word zeds , tzisk , zskmax  ; // применяются в самонастройке функционала.

 word Time_t_tir ;
 word timerVent ;
 word timerVent2 ;

 // Для контроля изоляции.
 word UinsulG , UinsulG_max  ;
 byte UinsulG_drob ;
 word UinsulD , UinsulD_max  ;
 byte UinsulD_drob ;
 word Uf ;
 byte     Schet_p[6] ;
 word  IDV_sr , IDV_1 ;

#ifdef _FP_N_to_L
 word    L_after_FP ;
 word   *fp_L ;
#endif

#ifdef _AD_ROT
//переменные ШИМ измерений :
word  IA_full , IB_full , IC_full ;
word  Uac_full, Uba_full;
word  IA , IB , IC ;
word  Uac, Uba;
//------------- Изначально было во float , по распоряжению КВВ переведено в double --------------
//---------- Затем , 30.09.2021 перевел во float , т.к. рассчеты критичны ко времени ------------
float Ux , Uy , Ix , Iy ;
float Psi_X[2] , Psi_Y[2] ;
float Psi_m_X[3] , Psi_m_Y[3] ;
float SlipNom , Slip , Slip_f[2] ;
float OmegaNom , OmegaRot , OmegaNullSynhr , N_ob_min ;
float Phi_e[2] ;
float drad0 , drad ;
float r1 , r2 , Rsigma , Xsigma , Rsigma_raschet , Xsigma_raschet , Rsigma_korr , Xsigma_korr ;
float Kt ;
//-----------------------------------------------------------------------------------------------
word  trig_first_raschet ;
word  Lrot ;
word  SkorRot ;
float  nFrot;
float Frot;
word  errPhi_e ;
word  TimeAD_Skor , time_izm , time_math , time_zar ;
word  Pary_AD , Mnom ;
word  time_Prinud ;

//переменные СИФУ в ШИМ :
byte  VT , VTn ;
word  L[6] , L_IU[6] , L_iu ;

//Импульсы с подтверждающими
//                         0    1    2    3    4    5    6
//byte const FOR0 [7] = { 0x3f,0x5e,0x7c,0x79,0x73,0x67,0x4f };

//Импульсы с подтверждающими для нефазности ротора :
//                         0    2    1    6    5    4    3
  byte const FOR2 [7] = { 0x3f,0x7c,0x5e,0x4f,0x67,0x73,0x79 };

//Импульсы только подтверждающие , без первых :
//                         0    6    1    2    3    4    5
  byte const FOR01 [7] = { 0x3f,0x5f,0x7e,0x7d,0x7b,0x77,0x6f };

//Т.к. при нефазности ИУ идут в другую сторону , справа налево , то берём первые без подтверждающих .
//Импульсы только первые , без подтверждающих , для нефазности ротора :
//                         0    2    1    6    5    4    3
  byte const FOR21 [7] = { 0x3f,0x7d,0x7e,0x5f,0x6f,0x77,0x7b };

#endif

#ifdef   It_ach // Для агрегатов , у которых есть ток тормоза .
 word   It , It_full ;
 Usrednit_Str   It_usr ;
#endif

/*------------------------------------------------*/
/*------------------------------------------------*/
#else
/*------------------------------------------------*/
extern  byte   time_VR1 ;
/*--------------- Для Регулятора Скорости -------------*/
extern  word     Z_Skor ;

extern  word     ZISkor ;

extern  word     Skor ;

extern  word     TG ;

#ifdef  TGx_ach
extern  word     TGx1 , TGx8 ;
#endif

extern  word     OuRegS_dop_kod ;

extern  word     OuIchRS  ;
extern  word     OuIchRS_k  ;
extern  word     Delta_Sk ;

#ifdef bi_RS_P
  extern  word     _r_KRSP ;
#endif

extern  word Delt_n , Kf_Sk , Skor_f , drob_FSk , Skor_ind ;
extern  byte new_izm_pdf , dfgg ;

//extern  union  RegFlags   RegFlg ; DAN - 11.12.2017 16:27 перенёс в RT.H .
/*-----------------------------------------------------*/

extern word   Zapas_Pointer ;
extern word  Skor_r ;

extern _register union   AvarBits  Av ;
extern _register union   AvarBits2 Av2 ;

#ifdef bi_BV1
extern word  Timer_BV1 ;
#endif
#ifdef bi_BV_2
extern word  Timer_BV2 ;
#endif
#ifdef bi_Vent_Dvig
extern word  Timer_Vent_Dvig    ;
#endif
#ifdef bi_MasloSmazka
extern word  Timer_MasloSmazka  ;
#endif
#ifdef bi_Smazka_Podsh
extern word  Timer_Smazka_Podsh ;
#endif
#ifdef bi_Gashenie
extern word time_gash_polja ;
#endif

extern word   Ttrans  , Ttrans_4_20  ;

extern  word upr_label , upr_ax , upr_bx , upr_time ;

extern byte   F2regim , c_index ;
extern word   av_label  ;
extern byte   N_Ucc , N_Ucc2 ;
extern word   P24_Ucc , P12_Ucc , N12_Ucc ;

#ifdef PUM_ach
 extern word PUM_Ucc ;
#endif
#ifdef _1P_ach
 extern word _1P_Ucc ;
#endif
#ifdef _2P_ach
 extern word _2P_Ucc ;
#endif

#ifdef  bi_KP
 extern word  Time_KP ;
#endif
#ifdef  bi_KP2
 extern word  Time_KP2 ;
#endif
#ifdef  bi_KP3
 extern word  Time_KP3 ;
#endif
#ifdef  bi_KP4
 extern word  Time_KP4 ;
#endif
#ifdef  bi_KP_KZ
 extern word   Time_KP_KZ ;
#endif

extern word   Stoyanka_Time , Stoyanka_Timer ;

extern word   time_Id_max   ;
extern word   time_Iv_min   ;
extern word   Time_do_OtklImp  ;
//extern word   Time_do_OtklSleda ;
extern word   TimeOtklQ1  ;
extern word   TimeOtklQ2  ;
extern lword  mask_predupr ;
extern lword  mask_predupr2 ;

#ifdef _TRETIY_REG
extern lword   mask_predupr3 ;
#endif

#ifdef _INTERPRETER
extern lword   mask_predupr_obj;
extern lword   mask_service_obj;
#endif

extern word    S_ImpLong ;

extern byte    RT_trigg  ; // признак отпускания герк. для контр. его повторн. срабат.
extern word    gercon_time ;

extern  word Time_econom ;

#ifdef _KTEV
extern  word Time_econom_KTEV ;
#endif

extern  word zeds , tzisk , zskmax  ;

extern  word Time_t_tir ;
extern  word timerVent ;
extern  word timerVent2 ;

 // Для контроля изоляции.
extern  word UinsulG , UinsulG_max  ;
extern  byte UinsulG_drob ;
extern  word UinsulD , UinsulD_max  ;
extern  byte UinsulD_drob ;
extern  word Uf ;
extern  byte  Schet_p[6] ;
extern  word  IDV_sr , IDV_1 ;

#ifdef _FP_N_to_L
extern  word    L_after_FP ;
extern  word   *fp_L ;
#endif

#ifdef _AD_ROT
extern word  IA_full , IB_full , IC_full ;
extern word  Uac_full, Uba_full;
extern word  IA , IB , IC ;
extern word  Uac, Uba;
extern float Ux , Uy , Ix , Iy ;
extern float Psi_X[] , Psi_Y[] ;
extern float Psi_m_X[] , Psi_m_Y[] ;
extern float SlipNom , Slip , Slip_f[] ;
extern float OmegaNom , OmegaRot , OmegaNullSynhr , N_ob_min ;
extern float Phi_e[] ;
extern float drad0 , drad ;
extern float r1 , r2 , Rsigma , Xsigma , Rsigma_raschet , Xsigma_raschet , Rsigma_korr , Xsigma_korr ;
extern float Kt ;
extern word  trig_first_raschet ;
extern word  Lrot ;
extern word  SkorRot ;
extern word  nFrot , Frot ;
extern word  errPhi_e ;
extern word  TimeAD_Skor , time_izm , time_math , time_zar ;
extern word  Pary_AD , Mnom ;
extern word  time_Prinud ;

extern byte  VT , VTn ;
extern word  L[] , L_IU[] , L_iu ;

extern byte const FOR2[];
#endif

 //---
#ifdef   It_ach // Для агрегатов , у которых есть ток тормоза .
 extern word   It , It_full ;
 extern Usrednit_Str   It_usr ;
#endif
/*------------------------------------------------*/
#endif
#endif

