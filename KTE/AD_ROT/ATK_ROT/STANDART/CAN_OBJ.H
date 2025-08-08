#ifndef _can_obj_h
#define _can_obj_h

word  can_obj ( word ) ;
word  can_ConfigReg ( word code ) ;

           //  временно для экспериментов используем одну структуру для
           // настройки обоих портов.
//#undef   can_setting
//#define  can_setting(port) (_r.can[0])

//#define   _TimeOut_Connect   _Sec( 0.5 )

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/

//       Для  'Status_KTE'
#define  _stat_Ready          0
#define  _stat_NotReady       1
#define  _stat_Work           2
#define  _stat_Work_Predupr   3
#define  _stat_Avar           4
#define  _stat_Reserve        5
//--------------------------------------------
// Свой статус АР2 - Роторного Выпрямителя :
#define  bo_canGotov      canr.StatReg._.n0
#define  bo_canPredupr    canr.StatReg._.n1
#define  bo_canAvar       canr.StatReg._.n2
#define  bo_canKTE_Rezerv canr.StatReg._.n3

#define  bo_canRTmin      canr.StatReg._.n45
//#define  bo_canRezerv   canr.StatReg._.n5  
#define  bo_canPrinud_com canr.StatReg._.n6  // режим Принудительной Коммутации .
#define  bo_canConnect    canr.StatReg._.n7

#define  bo_canRabota     canr.StatReg._.n8
#define  bo_canShunt_Rot  canr.StatReg._.n9
#define  bo_canMT         canr.StatReg._.n10
#define  bo_canNum_M      canr.StatReg._.n11

#define  bo_canSn_Imp     canr.StatReg._.n12
#define  bo_canStateQK    canr.StatReg._.n13
#define  bo_canGotovQK    canr.StatReg._.n14 // Готовность ко входу в Работу .
#define  bo_canDS1        canr.StatReg._.n15

//--------------------------------------------

#define  bi_canN_zad      canr.CfgReg._.n0
#define  bi_canId_zad     canr.CfgReg._.n1
#define  bi_canUg_zad     canr.CfgReg._.n2
#define  bi_canL_zad      canr.CfgReg._.n3
#define  bi_canMost       canr.CfgReg._.n4
#define  bi_canQK         canr.CfgReg._.n5
#define  bi_canF_zad      canr.CfgReg._.n6
#define  bi_canMT         canr.CfgReg._.n7

#define  bi_canStart      canr.CfgReg._.n8
#define  bi_canPredupr    canr.CfgReg._.n9
#define  bi_canAvar       canr.CfgReg._.n10
#define  bi_canDistSbros  canr.CfgReg._.n11
#define  bi_canS_zad      canr.CfgReg._.n12
#define  bi_canobject     canr.CfgReg._.n13x2
#define  bi_canConnect    canr.CfgReg._.n15

//--------------------------------------------

// Статус АР1 - Сетевого Инвертора :
#define   KTE2_Z_Sk_ZISk      canr.StatReg2._.n0    // Задание Скорости сравнялось с ЗИ скорости . KTE2_Gotov - не используется .
#define   KTE2_Predupr        canr.StatReg2._.n1
#define   KTE2_Avar           canr.StatReg2._.n2    // sts_KTE2._.Avar      // КТЭ2 в "Аварии"
#define   KTE2_OuRS           canr.StatReg2._.n3

#define   KTE2_RT_ON          canr.StatReg2._.n4
#define   KTE2_VV1_stator     canr.StatReg2._.n5
#define   KTE2_dt_Otkl_KZ     canr.StatReg2._.n6    // Команда отключить КЗ от ШУ ШМП  // было KTE2_AvarStop
//#define KTE2_Connect        canr.StatReg2._.n7

#define   KTE2_Rabota         canr.StatReg2._.n8    // sts_KTE2._.Rabota    // КТЭ2 в "Работе"
#define   KTE2_Shunt_End      canr.StatReg2._.n9    //Выход из режима шунтировки
#define   KTE2_Nazad          canr.StatReg2._.n10
#define   KTE2_Zatormogen     canr.StatReg2._.n11   //Задание скорости равно нулю ( для режима Останов - Снятие ИУ )

#define   KTE2_Sn_Imp         canr.StatReg2._.n12   // sts_KTE2._.SniatImp  // в КТЭ2 сняты "ИУ"
#define   KTE2_Pusk           canr.StatReg2._.n13
#define   KTE2_F2_Isp         canr.StatReg2._.n14   // Угол в уставку для исп.режимов АР1 - "СИФУ-рез" или "Циклы РТ"
#define   KTE2_DS1            canr.StatReg2._.n15   //KTE2_Blokir_ATK


    //Количество входных аналоговых каналов доступных по CAN.
#define    _Ai_max         5

    //Количество выходных аналоговых каналов доступных по CAN.
#define    _Ao_max         2

     // Блок данных для управления регулированием по CAN.

  struct  CAN_Reg
  {
    union CAN_ConfigReg
    {
      word all ;
      struct
      {
#ifndef _Union_FR
        word  n0    : 1 ;  // N_zad
        word  n1    : 1 ;  // Id_zad
        word  n2    : 1 ;  // Ug_zad
        word  n3    : 1 ;  // L_zad
        word  n4    : 1 ;  // Most  // направление вращения: 0-вперед, 1-назад.
        word  n5    : 1 ;  // QK
        word  n6    : 1 ;  // F_zad
        word  n7    : 1 ;  // MT

        word  n8    : 1 ;  // Start
        word  n9    : 1 ;  // Predupr
        word  n10   : 1 ;  // Avar
        word  n11   : 1 ;  // DistSbros
        word  n12   : 1 ;  // S_zad
        word  n13x2 : 2 ;  // object
        word  n15   : 1 ;  // Connect   // для теста наличия связи.
#else
        word  n15   : 1 ;  // Connect   // для теста наличия связи.
        word  n13x2 : 2 ;  // object
        word  n12   : 1 ;  // S_zad
        word  n11   : 1 ;  // DistSbros
        word  n10   : 1 ;  // Avar
        word  n9    : 1 ;  // Predupr
        word  n8    : 1 ;  // Start

        word  n7    : 1 ;  // MT
        word  n6    : 1 ;  // F_zad
        word  n5    : 1 ;  // QK
        word  n4    : 1 ;  // Most  // направление вращения: 0-вперед, 1-назад.
        word  n3    : 1 ;  // L_zad
        word  n2    : 1 ;  // Ug_zad
        word  n1    : 1 ;  // Id_zad
        word  n0    : 1 ;  // N_zad
#endif
      } _ ;
    }  CfgReg ;

    union CAN_StatusReg
    {
      word all ;
      struct
      {
#ifndef _Union_FR
        word  n0    : 1 ;  // Gotovn    // готовность к принятию задания .
        word  n1    : 1 ;  // Predupr
        word  n2    : 1 ;  // Avar
        word  n3    : 1 ;  // KTE_Rezerv
        word  n45   : 2 ;  //
        word  n6    : 1 ;  // Most
        word  n7    : 1 ;  // Connect   // для теста наличия связи.

        word  n8    : 1 ;  // Rabota
        word  n9    : 1 ;  // Shunt_Rot
        word  n10   : 1 ;  // MT
        word  n11   : 1 ;  // Num_M
        word  n12   : 1 ;  // Sn_Imp
        word  n13   : 1 ;  // StateQK
        word  n14   : 1 ;  // GotovQK   // готовность к включению линейника .
        word  n15   : 1 ;  // rezerv15
#else
        word  n15   : 1 ;  // rezerv15
        word  n14   : 1 ;  // StateQK
        word  n13   : 1 ;  // GotovQK   // готовность к включению линейника .
        word  n12   : 1 ;  // Sn_Imp
        word  n11   : 1 ;  // Num_M
        word  n10   : 1 ;  // MT
        word  n9    : 1 ;  // Shunt_Rot
        word  n8    : 1 ;  // Rabota

        word  n7    : 1 ;  // Connect   // для теста наличия связи.
        word  n6    : 1 ;  // Most
        word  n45   : 2 ;  //
        word  n3    : 1 ;  // KTE_Rezerv
        word  n2    : 1 ;  // Avar
        word  n1    : 1 ;  // Predupr
        word  n0    : 1 ;  // Gotovn    // готовность к принятию задания .
#endif
      } _ ;
    }  StatReg ;
    //union CAN_StatusReg StatReg2 ;   //статус "чужого" КТЭ   // DAN 12.04.2025 - перенесено в новую структуру

    // DAN 12.04.2025 психанул и определил слово статуса еще раз , чтобы не переделывать два бита - n45 : 2
    union CAN_StatusRegN
    {
      word all ;
      struct
      {
#ifndef _Union_FR
        word  n0    : 1 ;  // Gotovn    // готовность к принятию задания .
        word  n1    : 1 ;  // Predupr
        word  n2    : 1 ;  // Avar
        word  n3    : 1 ;  // KTE_Rezerv
        word  n4    : 1 ;  //
        word  n5    : 1 ;  //
        word  n6    : 1 ;  // rezerv6
        word  n7    : 1 ;  // Connect   // для теста наличия связи.

        word  n8    : 1 ;  // rezerv8
        word  n9    : 1 ;  // rezerv9
        word  n10   : 1 ;  // rezerv10
        word  n11   : 1 ;  // rezerv11
        word  n12   : 1 ;  // rezerv12
        word  n13   : 1 ;  // StateQK
        word  n14   : 1 ;  // GotovQK   // готовность к включению линейника .
        word  n15   : 1 ;  // rezerv15
#else
        word  n15   : 1 ;  // rezerv15
        word  n14   : 1 ;  // StateQK
        word  n13   : 1 ;  // GotovQK   // готовность к включению линейника .
        word  n12   : 1 ;  // rezerv12
        word  n11   : 1 ;  // rezerv11
        word  n10   : 1 ;  // rezerv10
        word  n9    : 1 ;  // rezerv9
        word  n8    : 1 ;  // rezerv8

        word  n7    : 1 ;  // Connect   // для теста наличия связи.
        word  n6    : 1 ;  // rezerv6
        word  n5    : 1 ;  //
        word  n4    : 1 ;  //
        word  n3    : 1 ;  // KTE_Rezerv
        word  n2    : 1 ;  // Avar
        word  n1    : 1 ;  // Predupr
        word  n0    : 1 ;  // Gotovn    // готовность к принятию задания .
#endif
      } _ ;
    }  ;
    union CAN_StatusRegN StatReg2 ;   //статус "чужого" КТЭ

    union
    {
      word all ;
      struct
      {
#ifndef _Union_FR
        word Connect      : 1 ;  // для теста наличия связи.
        word ClrMsg       : 1 ;  // флаг сброса сообщения .
        word rezerved     : 14;
#else
        word rezerved     : 14;
        word ClrMsg       : 1 ;  // флаг сброса сообщения .
        word Connect      : 1 ;  // для теста наличия связи.
#endif
      } _ ;
    }  Data ;

    word N_zad , S_zad ;

    word dId_zad, Id_zad, Idz_MaxP, Idz_MaxM ;

    word Ug_zad , F_zad ;

    word L_zad,  L_min ;

    word Ai[ _Ai_max ] ;

    word Ao[ _Ao_max ] ;

    byte  Temp_Zad;

    byte Most_Tir ;
  };

#define   _dreg_Connect      0x0001
#define   _dreg_ClrMsg       0x0002


#define   _sreg_Gotovn       0x0001
#define   _sreg_Predupr      0x0002
#define   _sreg_Avar         0x0004
#define   _sreg_KTE_Rezerv   0x0008
#define   _sreg_StateQK      0x0010
#define   _sreg_GotovQK      0x0020
#define   _sreg_MT           0x0040
#define   _sreg_Connect      0x0080

#define   _sreg_rezerv8      0x0100
#define   _sreg_rezerv9      0x0200
#define   _sreg_rezerv10     0x0400
#define   _sreg_rezerv11     0x0800
#define   _sreg_rezerv12     0x1000
#define   _sreg_rezerv13     0x2000
#define   _sreg_rezerv14     0x4000
#define   _sreg_rezerv15     0x8000

#define    _A8_sreg_mask \
_sreg_Gotovn   ,_sreg_Predupr  ,_sreg_Avar     ,_sreg_KTE_Rezerv ,\
_sreg_StateQK  ,_sreg_GotovQK  ,_sreg_MT       ,_sreg_Connect    ,\
_sreg_rezerv8  ,_sreg_rezerv9  ,_sreg_rezerv10 ,_sreg_rezerv11   ,\
_sreg_rezerv12 ,_sreg_rezerv13 ,_sreg_rezerv14 ,_sreg_rezerv15

//--------------------------------------------

#define   _creg_N_zad        0x0001
#define   _creg_Id_zad       0x0002
#define   _creg_Ug_zad       0x0004
#define   _creg_L_zad        0x0008
#define   _creg_Most         0x0010
#define   _creg_QK           0x0020
#define   _creg_F_zad        0x0040
#define   _creg_MT           0x0080

#define   _creg_Start        0x0100
#define   _creg_Predupr      0x0200
#define   _creg_Avar         0x0400
#define   _creg_DistSbros    0x0800
#define   _creg_S_zad        0x1000
#define   _creg_rezerv13     0x2000
#define   _creg_rezerv14     0x4000
#define   _creg_Connect      0x8000

#define    _A8_creg_mask \
_creg_N_zad   ,_creg_Id_zad   ,_creg_Ug_zad  ,_creg_L_zad     ,\
_creg_Most    ,_creg_QK       ,_creg_F_zad   ,_creg_MT        ,\
_creg_Start   ,_creg_Predupr  ,_creg_Avar    ,_creg_DistSbros ,\
_creg_S_zad   ,_creg_rezerv13 ,_creg_rezerv14,_creg_Connect

//--------------------------------------------

#define   _CAN_N_Zad               0
#define   _CAN_Id_Zad              1
#define   _CAN_Id_Zad_Ogr          2
#define   _CAN_Iv_Zad              3
#define   _CAN_Ostanov             4
#define   _CAN_MT                  5
#define   _CAN_Avar                6
#define   _CAN_Obmen               7
#define   _CAN_Alfa_Min            8
#define   _CAN_Alfa_Zad            9
#define   _CAN_Ug_Zad             10
#define   _CAN_DistSbros          11
#define   _CAN_N_Zad_R            12
#define   _CAN_Init               13
#define   _CAN_DS1_Init           14
#define   _CAN_QK                 15
#define   _CAN_Revers             16
#define   _CAN_S_Zad              17

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
#ifdef  _MAIN_INCLUDE
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

byte  Status_KTE ;

struct  CAN_Reg   canr ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#else
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

extern byte  Status_KTE ;

extern struct  CAN_Reg   canr ;

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
#endif
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
