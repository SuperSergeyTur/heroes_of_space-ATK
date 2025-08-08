
#ifndef _extrn
#define _extrn
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

//Переменые для определения размера областей уставок
// в "obj.h" #define  _kol_obl    ( 1 ) // Количество областей уставок

#define  _v_ar       ( sizeof( struct ABlok_Ustavok )) //размер области аналоговых уставок

#define  _v_r        ( sizeof( struct Blok_Ustavok  )) // Размер области основных уставок
#define  _v_or       ( sizeof( struct oBlok_Ustavok )) //размер области объектных уставок
#define  _v_TablSled ( sizeof( struct SLED          )) //размер области уставок табл. следа
#define  _v_Func     ( sizeof( struct tab_Ivz       )) //размер области уставок Ivz
#define  _v_Stat     ( sizeof( struct SBlok_Ustavok )) //размер области статичных уставок( уставки
                               //не переписываются при восстановлении типовых)
#ifdef _JOURNAL
  #define  _v_TablJrn  ( sizeof( struct TAB_JRN       )) //размер области уставок табл. журнала
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

// DAN перенесено из SIFU.H 04.05.2016 9:30 .
#undef    _synch2_epa_con
#undef    _synch2_epa_time
#define   _synch2_epa_con    _selsin1_epa_con
#define   _synch2_epa_time   _selsin1_epa_time
//---------------

          //  Время команды откл.Q1.
#define  _Time_otkl_Q1     _MkSec( 40u*1000u )
#define  _Time_otkl_Q2     _MkSec( 40u*1000u )
          //  Выдержка на повторное отключение Q1.
#define  _TimeOut_otkl_Q1  _Sec( 1.5 )
#define  _TimeOut_otkl_Q2  _Sec( 1.5 )

//---------------
#if defined (_Union_FR) || defined (_CM3_)
//---------------
// Сигналы ДЗВ контролируются по уровню - есть напряжение , тиристоры заперты , разрешающий уровень для
// реверсирования . Соответственно , - нет напряжения , тиристоры открыты , запрещающий уровень .
//---
// Для удобства , уставка инвертирования во входном порте совпадает с разрешающем реверсирование уровнем
// сигнала . Если разрешающий уровень "1" , то уставка инвертирования во входном порте должна стоять "1" .
#undef     _DZVA_Ok_level
  #define  _DZVA_Ok_level ((_r.Pi1_Normal >> 2) & 0x01)
#undef     _DZVK_Ok_level
  #define  _DZVK_Ok_level ((_r.Pi1_Normal >> 3) & 0x01)

#undef     _DZVA2_Ok_level
  #define  _DZVA2_Ok_level ((_r.Pi1_Normal >> 4) & 0x01)
#undef     _DZVK2_Ok_level
  #define  _DZVK2_Ok_level ((_r.Pi1_Normal >> 5) & 0x01)
//----------------------
        /*   Привязка СИФУ к ЕПА.  */

#define   _sifu_epa_con  _OCS0
#ifdef    _CM3_
 #define  _sifu2_epa_con _OCS4 // DAN 20.05.2016 - На одном таймере с реверсом СИФУ2 сбивается .
#else
 #define  _sifu2_epa_con _OCS2
#endif

#define   _sifu_epa_time( data )  OCCP0 = data
#ifdef    _CM3_
 #define  _sifu2_epa_time( data ) OCCP4 = (w)(data&0xffff) // DAN 20.05.2016 - На одном таймере с реверсом СИФУ2 сбивается .
#else
 #define  _sifu2_epa_time( data ) OCCP2 = (w)(data&0xffff)
#endif

#define   _Sifu_int  OCS01_ICP0
#define   _Sifu2_int OCS23_ICP2

#undef    _OCS23_PRIORITY   // изменяем приоритет EPA.
#define   _OCS23_PRIORITY   20
//----------------------
        /*   Привязка Реверса к ЕПА.  */

#define   _revers_epa_con   _OCS1

#define   _revers_epa_time( data )  OCCP1 = (w)(data&0xffff)
#define   _Revers_int  OCS01_ICP1

#undef    _OCS01_PRIORITY   // изменяем приоритет EPA.
#define   _OCS01_PRIORITY   20

//---------
#ifdef _Vozb_KTE
//---------

        /*   Привязка СИФУВ к ЕПА.  */

#ifdef  _CM3_
    #define   _sifuv_epa_con   _OCS4
    #define   _sifuv_epa_time( data )  OCCP4 = (w)(data&0xffff)
#else
    #define   _sifuv_epa_con   _OCS3
    #define   _sifuv_epa_time( data )  OCCP3 = (w)(data&0xffff)
#endif
#define   _Sifuv_int  OCS23_ICP3
              //  Разные приоритеты для СИФУв, чтобы его ИУ мог перебивать
             // СИФУя, а регуляторы нет.
#ifdef  _CM3_
  #define   _SIFUV_PRIORITY_high   IntPriority(2, 1)
  #define   _SIFUV_PRIORITY_low    IntPriority(3, 4)
  #define   _set_sifuv_priority( data )  NVIC_SetPriority( TIMER2_IRQn, (w)(data&0xffff))
#else
  #define   _SIFUV_PRIORITY_high   19
  #define   _SIFUV_PRIORITY_low    21
  #define   _set_sifuv_priority( data )  ICR29 = data
#endif

  #undef    _OCS23_PRIORITY   // изменяем приоритет EPA.
#define   _OCS23_PRIORITY   _SIFUV_PRIORITY_low

//---------
#endif  //#ifdef _Vozb_KTE
//---------

//---------------
#else   //#if defined (_Union_FR) || defined (_CM3_)
//---------------
#undef     _DZVA_Ok_level
  #define  _DZVA_Ok_level ((_r.Pi1_Normal >> 4) & 0x01)
#undef     _DZVK_Ok_level
  #define  _DZVK_Ok_level ((_r.Pi1_Normal >> 5) & 0x01)
//----------------------

        /*   Привязка синхронизации к ЕПА в "epa_drv.h".  */

//----------------------
        /*   Привязка СИФУ к ЕПА.  */

#define   _sifu_epa_con   _OCS3
#define   _sifu_epa_time( data )  OCCP3 = (w)(data&0xffff)
//#define   _Sifu_int0  OCS23_ICP2
#define   _Sifu_int  OCS23_ICP3

#undef    _OCS23_PRIORITY   // изменяем приоритет EPA.
#define   _OCS23_PRIORITY   4
//----------------------
        /*   Привязка Реверса к ЕПА.  */

#define   _revers_epa_con   _OCS2 //_OCS0
#define   _revers_epa_time( data )  OCCP2 = (w)(data&0xffff)//OCCP0 = data
//#define   _Revers_int0  OCS01_ICP0     06.07.05 10:45
//#define   _Revers_int1  OCS01_ICP1     06.07.05 10:45

#undef    _OCS01_PRIORITY   // изменяем приоритет EPA.
#define   _OCS01_PRIORITY   3 //4

//----------------------
        /*   Привязка СИФУВ к ЕПА.  */

#define   _sifuv_epa_con   _OCS4
#define   _sifuv_epa_time( data )  OCCP4 = (w)(data&0xffff)
//#define   _Sifuv_int0  OCS45_ICP4
//#define   _Sifuv_int1  OCS45_ICP5
              //  Разные приоритеты для СИФУв, чтобы его ИУ мог перебивать
             // СИФУя, а регуляторы нет.
#define   _SIFUV_PRIORITY_high   3
#define   _SIFUV_PRIORITY_low    5
#define   _set_sifuv_priority( data )  ICR09 = data

  #undef    _OCS45_PRIORITY   // изменяем приоритет EPA.
#define   _OCS45_PRIORITY   _SIFUV_PRIORITY_low

//---------------
#endif  //#if defined (_Union_FR) || defined (_CM3_)
//---------------

         /*  Частота заполнения сигнала ИУ.  */
             // для коротких ИУ
#define  _FzapolnShort_Low      _MkSec( 10 )  // длительность нулевого импульса в мкс
#define  _FzapolnShort_High     _MkSec( 10 )  // длительность единичного импульса в мкс
             // для длинных ИУ
#define  _FzapolnLong_Low      _MkSec( 70 )  // длительность нулевого импульса в мкс
#define  _FzapolnLong_High     _MkSec( 10 )  // длительность единичного импульса в мкс

  #ifdef  _IU_60_Qubler // Переменная скважность ИУ
             // для коротких ИУ ( первая часть ИУ , 6грд )
#undef   _FzapolnShort_Low
#define  _FzapolnShort_Low      _MkSec( 30 )  // длительность нулевого импульса в мкс
#undef   _FzapolnShort_High
#define  _FzapolnShort_High     _MkSec( 30 )  // длительность единичного импульса в мкс
             // для длинных ИУ ( вторая часть ИУ , от 6грд до 60грд )
#undef   _FzapolnLong_Low
#define  _FzapolnLong_Low      _MkSec( 80 )  // длительность нулевого импульса в мкс
#undef   _FzapolnLong_High
#define  _FzapolnLong_High     _MkSec( 15 )  // длительность единичного импульса в мкс
  #endif

             // для коротких ИУ встроенного возбудителя
#define  _V_FzapolnShort_Low   _MkSec( 10 )  // длительность нулевого импульса в мкс
#define  _V_FzapolnShort_High  _MkSec( 10 )  // длительность единичного импульса в мкс
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

                            //  для однократности отключения.
#define   mOtkl_Q1()    if ( Av._.OneQ1 == 0 ) \
                        {                      \
                          Av._.OneQ1 = 1 ;     \
                          mSET_Q1(), TimeOtklQ1 = timer1, Av._.OtklQ1 = 1 ; \
                        }
#define   mClr_Q1()    mCLR_Q1(), Av._.OtklQ1 = 0
#define   mTst_Q1()    mTST_Q1()

                            //  для однократности отключения.
#define   mOtkl_Q2()    if ( Av._.OneQ2 == 0 ) \
                        {                      \
                          Av._.OneQ2 = 1 ;     \
                          mSET_Q2(), TimeOtklQ2 = timer1, Av._.OtklQ2 = 1 ; \
                        }
#define   mClr_Q2()    mCLR_Q2(), Av._.OtklQ2 = 0

#define   mYes_Otkl_Q1()    (( ( Reg_AvarMsg | Reg_AvarMsgFirst ) & ~_r.Otkl_Q1_Mask ) != (lw)r0 )

/*------------------------------------------------*/

         // Сдвиг импульсов в АльфаМаксимум.
#define   mSdvig_Imp()     Av._.Sdvig_imp = 1 , S.flg._.Revers = 0

#define   mOtkl_Imp( ax )       Otkl_Imp |= ( ax )

#define   mVkl_Imp( ax )        Otkl_Imp &= ~( ax )

#define   _Start_imp            ( 0x8000u )
#define   _VR1_imp              ( 0x4000u )
#define   _Avar_imp             ( 0x2000u )
#define   _Ostanov_imp          ( 0x1000u )
#define   _Rev_imp              ( 0x0800u )
            // чтобы можно было сбросить сразу все запреты на импульсы
#define   _All_imp              ( 0xFFFFu )

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

// Период выполнения РС : раз в пульс или раз в 3 пульса
#ifdef    _RS_10ms_
  #define _RS_T       10
#else
  #define _RS_T       3.3 // Компилятор правильно понимает дробь , проверено DAN 25.12.2008 10:31 .
#endif

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
          // Объектное управление.
#define   _Obj_c_Init              0
#define   _Obj_c_DS1_Init          1
#define   _Obj_c_Sborka_Gotovn     2
#define   _Obj_c_Rabota            3
#define   _Obj_c_Avar_Otkl         4
#define   _Obj_c_Common_avar       5
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
          // Объектное регулирование.
#define   _Obj_N_Zad               0
#define   _Obj_Id_Zad              1
#define   _Obj_Id_Zad_Ogr          2
#define   _Obj_Iv_Zad              3
#define   _Obj_Ostanov             4
#define   _Obj_MT                  5
#define   _Obj_Alfa_Zad            6
#define   _Obj_Ug_Zad              7
#define   _Obj_N_Zad_R             8
#define   _Obj_Init                9
#define   _Obj_Revers             10
#define   _Obj_S_Zad              11
#define   _Obj_Ug_Zad_R           12
#define   _Obj_N_OS               13
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
          // Штатное регулирование.
#define   _Shtat_Init              0
#define   _Shtat_Reg               1
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

    void        Init_Prog ( void ) ;
    void        Izm_Analog ( void ) ;
    void        Blok_upr ( void ) ;
    word        ZI_Init_Skor ( word num ) ;
    void        RN_null ( void ) ;

    void        RegTok ( void ) ;
    void        Cikl ( void )  ;

    word        sqrt_xy ( word ) ;

    void        IdConv (void);
    void        IdConv_3faz (void);
    void        IdIzm  (void);
    void        IdIzm_3faz (void);
    void        TokRaspr_3faz (void);

    void        Linear (void);

#endif

