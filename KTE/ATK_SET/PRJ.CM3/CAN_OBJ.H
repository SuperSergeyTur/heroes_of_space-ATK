#ifndef _can_obj_h
#define _can_obj_h

word  can_obj ( word ) ;
word  can_ConfigReg ( word code ) ;

           // Задаем рабочий CAN-порт.
#define   _WorkSlaveCANPort  0
#define   _SecondCANPort     1
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

// Слово Конфигурации из ША :
#define  bi_SA_B1          canr.CfgReg._.n0
#define  bi_SA_B3          canr.CfgReg._.n1
#define  bi_SA_Pusk        canr.CfgReg._.n2
#define  bi_SA_QF1         canr.CfgReg._.n3

#define  bi_SA_Stop        canr.CfgReg._.n4
//#define  bi_             canr.CfgRegSA._.n5
//#define  bi_             canr.CfgRegSA._.n6
//#define  bi_             canr.CfgRegSA._.n7

//#define  bi_             canr.CfgRegSA._.n8
//#define  bi_             canr.CfgRegSA._.n9
//#define  bi_             canr.CfgRegSA._.n10
#define  bi_canDistSbros   canr.CfgReg._.n11

//#define  bi_             canr.CfgRegSA._.n12
//#define  bi_             canr.CfgRegSA._.n13x2
#define  bi_canConnect    canr.CfgReg._.n15

#define  bi_canStart       bi_SA_Pusk
//--------------------------------------------

// Состояние АТК для передачи в ША :
#define  bo_SA_canGotov      canr.StatReg._.n0
#define  bo_SA_canPredupr    canr.StatReg._.n1
#define  bo_SA_canAvar       canr.StatReg._.n2
#define  bo_SA_canN_min      canr.StatReg._.n3
#define  bo_SA_canN_490      canr.StatReg._.n4
#define  bo_SA_canrezerv5    canr.StatReg._.n5
#define  bo_SA_canrezerv6    canr.StatReg._.n6
#define  bo_SA_canConnect    canr.StatReg._.n7
                                         
#define  bo_SA_canrezerv8    canr.StatReg._.n8
#define  bo_SA_canrezerv9    canr.StatReg._.n9
#define  bo_SA_canrezerv10   canr.StatReg._.n10
#define  bo_SA_canrezerv11   canr.StatReg._.n11
#define  bo_SA_canrezerv12   canr.StatReg._.n12
#define  bo_SA_canrezerv13   canr.StatReg._.n13
#define  bo_SA_canrezerv14   canr.StatReg._.n14
#define  bo_SA_canrezerv15   canr.StatReg._.n15

//--------------------------------------------

// Статус АР1 - Сетевого Инвертора для передачи в Роторный выпрямитель :
#define  bo_canZ_Sk_ZISk   canr.StatReg1._.n0  // bo_canGotov - перенес в структуру для неиспользуемых статусов
#define  bo_canPredupr     canr.StatReg1._.n1
#define  bo_canAvar        canr.StatReg1._.n2
#define  bo_canOuRS        canr.StatReg1._.n3

//#define  bo_canrezerv4   canr.StatReg1._.n4
#define  bo_canVV1_stator  canr.StatReg1._.n5  // ВВ1 - вакуумный выключаьтель статора // DAN 12.04.2025
#define  bo_candt_Otkl_KZ  canr.StatReg1._.n6  // Команда отключить КЗ от ШУ ШМП
//#define  bo_canConnect     canr.StatReg1._.n7

#define  bo_canRabota      canr.StatReg1._.n8
#define  bo_canShunt_End   canr.StatReg1._.n9  //Выход из режима шунтировки
#define  bo_canNazad       canr.StatReg1._.n10
#define  bo_canZatormogen  canr.StatReg1._.n11 //Задание скорости равно нулю ( для режима Останов - Снятие ИУ )

#define  bo_canSn_Imp      canr.StatReg1._.n12
#define  bo_canPusk        canr.StatReg1._.n13
#define  bo_canF2_Isp      canr.StatReg1._.n14  //bo_canGotovQK
#define  bo_canDS1         canr.StatReg1._.n15

//--------------------------------------------
//Свой статус АР1 для передачи в другой ШУ: ШУ1-ШУ2
#define  bo_atkGotov       canr.StatReg4._.n0
#define  bo_atkPredupr     canr.StatReg4._.n1
#define  bo_atkAvar        canr.StatReg4._.n2
#define  bo_atkOuRS        canr.StatReg4._.n3

#define  bo_atkNmbrATK     canr.StatReg3._.n4
#define  bo_atkNmbrATK1    canr.StatReg3._.n5
#define  bo_atkAvarStop    canr.StatReg4._.n6
#define  bo_atkConnect     canr.StatReg4._.n7

#define  bo_atkRabota      canr.StatReg4._.n8
#define  bo_atkShunt_End   canr.StatReg4._.n9
#define  bo_atkAvar_Yach   canr.StatReg4._.n10 //bo_atkSQ2 //bo_atkOtkl_Q1
#define  bo_atkZatormogen  canr.StatReg4._.n11 //Задание скорости равно нулю ( для режима Останов - Снятие ИУ )

#define  bo_atkSQ1         canr.StatReg4._.n12 //bo_atkSn_Imp
#define  bo_atkPusk        canr.StatReg4._.n13
#define  bo_atkGotovQK     canr.StatReg4._.n14
#define  bo_atkDS1         canr.StatReg4._.n15

//--------------------------------------------

// Статус другого АТК , точнее его АР1 - Сетевого Инвертора :
#define  ATK2_Gotov        canr.StatReg3._.n0
#define  ATK2_Predupr      canr.StatReg3._.n1
#define  ATK2_Avar         canr.StatReg3._.n2
#define  ATK2_OuRS         canr.StatReg3._.n3

#define  ATK2_NmbrATK      ((b)canr.StatReg3._.n4|((b)canr.StatReg3._.n5<<1))
#define  ATK2_AvarStop     canr.StatReg3._.n6
#define  ATK2_Connect      canr.StatReg3._.n7

#define  ATK2_Rabota       canr.StatReg3._.n8
#define  ATK2_Shunt_End    canr.StatReg3._.n9
#define  ATK2_Avar_Yach    canr.StatReg3._.n10 //ATK2_SQ2 //ATK2_Otkl_Q1
#define  ATK2_Zatormogen   canr.StatReg3._.n11 //Задание скорости равно нулю ( для режима Останов - Снятие ИУ )

#define  ATK2_SQ1          canr.StatReg3._.n12 //ATK2_Sn_Imp
#define  ATK2_Pusk         canr.StatReg3._.n13
#define  ATK2_GotovQK      canr.StatReg3._.n14
#define  ATK2_DS1          canr.StatReg3._.n15

//--------------------------------------------

// Структура для неиспользуемых статусов
#define  bo_canGotov       canr.StatRegx._.n0
#define  bi_canMT          canr.StatRegx._.n1
//#define  bo_             canr.StatRegx._.n2
//#define  bo_             canr.StatRegx._.n3

//#define  bo_             canr.StatRegx._.n45
//#define  bo_             canr.StatRegx._.n6
//#define  bo_             canr.StatRegx._.n7

//#define  bo_             canr.StatRegx._.n8
//#define  bo_             canr.StatRegx._.n9
//#define  bo_             canr.StatRegx._.n10
//#define  bo_             canr.StatRegx._.n11

//#define  bo_             canr.StatRegx._.n12
//#define  bo_             canr.StatRegx._.n13
//#define  bo_             canr.StatRegx._.n14
//#define  bo_             canr.StatRegx._.n15

//--------------------------------------------

//#define  bi_canN_zad      canr.CfgReg._.n0
//#define  bi_canId_zad     canr.CfgReg._.n1
//#define  bi_canUg_zad     canr.CfgReg._.n2
//#define  bi_canL_zad      canr.CfgReg._.n3
//#define  bi_canMost       canr.CfgReg._.n4
//#define  bi_canQK         canr.CfgReg._.n5
//#define  bi_canF_zad      canr.CfgReg._.n6
//#define  bi_canMT         canr.CfgReg._.n7

//#define  bi_canStart      canr.CfgReg._.n8
//#define  bi_canPredupr    canr.CfgReg._.n9
//#define  bi_canAvar       canr.CfgReg._.n10
//#define  bi_canDistSbros  canr.CfgReg._.n11
//#define  bi_canS_zad      canr.CfgReg._.n12
//#define  bi_canobject     canr.CfgReg._.n13x2


#define  bi_canN_zad       0
#define  bi_canId_zad      0
#define  bi_canUg_zad      0
#define  bi_canL_zad       0
#define  bi_canMost        0
#define  bi_canQK          0
#define  bi_canF_zad       0
#define  bi_canPredupr     0  
#define  bi_canAvar        0

#define  bo_canStart      canr.CfgRegAp2._.n8
#define  bo_canConnect    canr.CfgRegAp2._.n15
//--------------------------------------------
// Статус АР2 - Роторного Выпрямителя :
//#define  KTE2_Gotov          canr.StatReg2._.n0    // не используем в алгоритмах инвертора .
#define    KTE2_Predupr        canr.StatReg2._.n1
#define    KTE2_Avar           canr.StatReg2._.n2    // sts_KTE2._.Avar      // КТЭ2 в "Аварии"
//#define  KTE2_KTE_Rezerv     canr.StatReg2._.n3    // не используем в алгоритмах инвертора .

#define    KTE2_RTmin          canr.StatReg2._.n4
#define    KTE2_Prinud_com     canr.StatReg2._.n6    // режим Принудительной Коммутации .
//#define  KTE2_Connect        canr.StatReg2._.n7    // не используем в алгоритмах инвертора .

#define    KTE2_Rabota         canr.StatReg2._.n8    // sts_KTE2._.Rabota    // КТЭ2 в "Работе"
#define    KTE2_Shunt_Rot      canr.StatReg2._.n9
//#define  KTE2_MT             canr.StatReg2._.n10   // не используем в алгоритмах инвертора .
//#define  KTE2_Num_Most       canr.StatReg2._.n11   // не используем в алгоритмах инвертора .

#define    KTE2_Sn_Imp         canr.StatReg2._.n12   // sts_KTE2._.SniatImp  // в КТЭ2 сняты "ИУ"
//#define  KTE2_StateQK        canr.StatReg2._.n13   // не используем в алгоритмах инвертора .
#define    KTE2_GotovQK        canr.StatReg2._.n14   // Готовность к включению в Работу .
#define    KTE2_DS1            canr.StatReg2._.n15   // KTE2_canEndLocRot

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
    }  CfgReg ;                        // структура конфиг от ША // DAN 12.04.2025
    union CAN_ConfigReg CfgRegAp2 ;    //Cтруктура конфиг в АР2

    union Prt16  StatReg1 ; //статус "чужого" КТЭ : АР1-АР2
    union Prt16  StatReg2 ; //статус "чужого" КТЭ : АР1-АР2
    union Prt16  StatReg3 ; //статус "чужого" КТЭ : ШУ1-ШУ2
    union Prt16  StatReg4 ; //Свой статус АР1 для передачи в другой ШУ: ШУ1-ШУ2
    union Prt16  StatRegx ; //Структура для неиспользуемых статусов    
    union Prt16  StatReg ;    //Статус АР1 - Сетевого Инвертора для передачи в АР2 // DAN 12.04.2025


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
#define   _sreg_rezerv6      0x0040
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
_sreg_StateQK  ,_sreg_GotovQK  ,_sreg_rezerv6  ,_sreg_Connect    ,\
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
#define   _creg_rezerv3      0x2000
#define   _creg_rezerv4      0x4000
#define   _creg_Connect      0x8000

#define    _A8_creg_mask \
_creg_N_zad   ,_creg_Id_zad   ,_creg_Ug_zad  ,_creg_L_zad     ,\
_creg_Most    ,_creg_QK       ,_creg_F_zad   ,_creg_MT        ,\
_creg_Start   ,_creg_Predupr  ,_creg_Avar    ,_creg_DistSbros ,\
_creg_S_zad   ,_creg_rezerv3  ,_creg_rezerv4 ,_creg_Connect

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
