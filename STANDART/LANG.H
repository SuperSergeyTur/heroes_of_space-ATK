#ifndef  _LANG_H
#define  _LANG_H

  //-----
  #ifndef _LANG_RU_
  //-----
#define  _Monitor_prompt       "\r\n Монiтор. "
#define  _Dispet_prompt        "\r\n Диспетчер. "
#define  _Disp_ComNotServed    "\r\nКоманда не \r\nобслуговується."
#define  _Ostanov_prompt       "\r\n ОСТАНОВ.\r\n"
#define  _Setab_prompt         "\r\n Уставки: "
#define  _SetabBit_prompt      "\r\nУставки бiтовi:"
#define  _Norton_prompt        "\r\n Меню: \r\n"
#define  _Indicatr_prompt      "\r\n Iндикацiя: "
#define  _Clock_prompt         "\r\nГодинник:"
#define  _Clock1_prompt        "\r\nНалаштув.годин.:"
#define  _AvWell_txt           "A>"
#define  _avWell_txt           "a>"
#define  _PrWell_txt           "W>"
#define  _prWell_txt           "w>"
#define  _RWell_txt            "R>"
#define  _rWell_txt            "r>"
#define  _GWell_txt            "G>"
#define  _gWell_txt            "g>"
#define  _OWell_txt            "O>"
#define  _CWell_txt            "C>"
#define  _cWell_txt            "c>"
#define  _SWell_txt            "S>"
#define  _sWell_txt            "s>"
#define  _Message_prompt       "\r\n Повiдомлення:"
#define  _Msg_notSupport_txt   "Повiд.рег.2 N"
#define  _FirstAvMsg_txt       "Перша аварiя:\r\n"
#define  _AvMsg_txt            "Аварiї:\r\n"
#define  _PrMsg_txt            "Попередження:\r\n"
#define  _Srv1Msg_txt          "\r\nДив.служб.повiд"
#define  _Srv2Msg_txt          "Служб.повiд.:\r\n"
#define  _NoMsg_txt            "Повiдомл. немa"
#define  _ADC_Tst_txt          "\r\n Тест АЦП:"
#define  _ADC_chnl             "\r "
#define  _DAC_Tst              "\r\n Тест ЦАП:"
#define  _Input_Tst            "\r\nДискрет.входи:"
#define  _Input_Tst_c          'c'
#define  _Input_Tst_m          'm'
#define  _Output_Tst           "\r\nДискрет.виходи:"
#define  _Output_Tst_c         'c'
#define  _Output_Tst_m         'm'
#define  _Output_Tst_Q1        "Q1V=_П_"
#define  _Output_Tst_q1        "Q1V=_п_"
#define  _Output_Tst_Q2        "Q2V=_П_"
#define  _Output_Tst_q2        "Q2V=_п_"
#define  _Test_EOZU_txt        "\r\nТест ЕОЗП:"
#define  _Test_i2c_txt         "\rТест пам'ятi i2c"
#define  _Test_clock_txt       "\rТестПам'ятi год."
//#define  _TypeUst_prompt       "\r\nТиповые уставки\r\n восстановлены."
//KVV_backup
//#define  _TypeUst_txt          "\r\n Ок    "
#define  _ReLoadAvar_txt       "\r\nВiдновлен.авар.:"
#define  _ReLoad_prm           "\r Nавар="
#define  _Avar_Not_txt         "\r\nАварiй нема."
#define  _Error_i2c_txt        "\r\nНесправн. ЕОЗП."
#define  _NoConnect_i2c_txt    "\r\nНемає вiдп.ЕОЗП"
#define  _Test_RAM_txt         "\r\nТест ОЗП:"
#define  _Error_RAM_txt        "\r\nНесправн. ОЗП."
#define  _Waiting_txt          "\r\n Чекайте."
#define  _Test_DP_txt          "\r\nТест DP:"
#define  _Error_DP_txt         "\r\nНесправн. DP."
#define  _Test_Yes_txt         "\rТест?-так."
#define  _Test_No_txt          "\rТест?-нi. "
#define  _DAC_tabl_txt         "\r\n Вивед.НаПрилад"
#define  _Fazir_Is_txt         "\r\nФазуван.струмiв:"
#define  _Fazir_Is_txt_Ia_Ir   "\r\n F,Isa%,Isr%,Cos"
#define  _Fazir_Us_txt         "\r\nФазування напруг:"
//---- для двухмостовых возбудителей.
//#define  _Fazir_2Mosta
#define  _Fazir_vozb_txt       "\r\nФазування мосту:"
#define  _Fazir_Yes_txt        "\rПочати?-так."
#define  _Fazir_No_txt         "\rПочати?-нi."
#define  _Fazir_Most           "\rМiст="
#define  _Fazir_sdvig_txt      "\r\nЗсув IУ забло-\r\nковано захистом."
#define  _Fazir_auto_txt       "\r\nЗаблоковано\r\nавтофазуванням."
#define  _Fazir_txt_Q1         "\r\n Недоступно при\r\nзiбр.силов.кола."
#define  _Fazir_txt_avt220     "\r\nНедоступно з \r\nвимк.'=220В'."
#define  _Offset_normal_txt    "\r\nЗмiщення в нормi."
#define  _Offset_anormal_txt   "\r\nЗмiщення не в нормi."
#define  _F2_prompt_txt        "\r\nНалагодження:"
#define  _Not_Selected_DS_txt  "\r\nНе вибраний \r\n давач швидк."
#define  _Cikl_Reg_txt         "\rРег.="
#define  _Sled_prompt          "\r\n Слiд:\n\r"
#define  _Sled_txt0            "\n\r Змiннi:\n\r"
#define  _Sled_txt1            "\n\r Рядкiв:\n"
#define  _SetSled_prompt       "\n\r Налаш.регiстр.:\n"
#define  _SetSled_txt0         "\n\r Кiлькiсть:\n\r"
#define  _SetSled_txt1         "\n\r Перелiк:\n"
#define  _SetSled_txt2         "\n\r Вибiр:\n"
#define  _SetSled_txt3         "\n\r Адреса:\n"
#define  _SetSled_txt4         "\n\r Тип:\n"
#define  _SetSled_txt5         "\n\r Кратнiсть:\n"
#define  _SetSled_txt6         " Вихiд?       "
#define  _SetSled_txt7         "\n\r Автостарт:\n"
#define  _Page_txt             "\r\n\r\nСторiнка-"
#define  _SaveUst_prompt       "\r\nЗбереж. уставок:"
#define  _SaveNo_txt           "\rСкасування.    " // "\rСохранить?-нет."
#define  _SaveYes_txt          "\rЗберегти Робочi " // "\rСохранить?-да. "
//#define  _Saved_txt            "\r\n Записано. "
//KVV_backup
//  #define  _SaveNo_txt       "\rВыход         "
//  #define  _SaveYes_txt      "\rЗапись        "
  #define  _SaveBackUp_txt     "\rЗберегтиРезервнi" // "\rРезервировать?"
  #define  _Saved_txt          "\r\n Ок         "

// 22.05.2020 14:47 Перенесено из #ust_i2c.c
#define  _TypeUst_Prompt       "\r\nТиповi уставки:"
#define  _RestoreNo_txt        "\rСкасування.     " // "\rВосстанов.?-Нет."
#define  _RestoreYes_txt       "\rВiднов.Типовi.  "
#define  _RestoreWork_txt      "\rВiднов.Робочi.  "
#define  _RestoreBackUp_txt    "\rВiднов.Резервнi."

#define  _Ostanov_Prompt       "\r\nРежим 'Останов':"
#define  _OstanovYes_txt       "\rВстановити?-так."
#define  _OstanovNo_txt        "\rВстановити?-нi ."
#define  _Agregat_txt          "\r\n Об'єкт:\r\n"
#define  _AgregatOut_txt       "\rВiдсутнiй."
#define  _About_Prompt         "\r\nПро систему:"
#define  _Type_Agregat_txt     "Тип агрегату "
#define  _DateTime_txt         "Дата/Час ПЗ"
#define  _Type_Program_txt     "Версiя ПЗ    "
#define  _Size_i2c_txt         "Об'єм ЕОЗП   "
#define  _Size_i2c_8kb_txt     " 8 кб        "
#define  _Size_i2c_32kb_txt    " 32 кб       "
#define  _Size_i2c_64kb_txt    " 64 кб       "
#define  _Size_i2c_512kb_txt   " 512 кб      "
#define  _Size_i2c_No_txt      " Вiдсутнє    "
#define  _MinSize_i2c_txt      "\r\nВстановлена ЕОЗП\r\nменше 32кб\r\n"
#define  _ObjectOblUst         "Об'єкт "
#define  _Decimal_txt          "Познач. схеми "
#define  _ErrRAM_txt           "\r\nОЗП несправно"
#define  _Reset_Counter_txt    "\n\rОбнул. лiчил.?"
#define  heading_comb_menu     "\n\rКомб.Редак.: "

#ifndef   _SaveUst_prompt
  #define  _SaveUst_prompt   "\r\nЗапис уставок:"
  #define  _Agregat_txt      "\r\n Об'єкт:\r\n"
  #define  _SaveYes_txt      "\rЗаписати?-так."
  #define  _SaveNo_txt       "\rЗаписати?-ні. "
  #define  _Saved_txt        "\r\n Записано. "
#endif

#if defined _CM3_
   #define  _Autostart_txt        "\r\nАвтостарт \r\nвiдключен.(S6.1)\r\n"
#elif defined _F16e
   #define  _Autostart_txt        "\r\nАвтостарт \r\nвiдключен.(PIN12)\r\n"
#elif defined _J1
   #define  _Autostart_txt        "\r\nАвтостарт \r\nвiдключен.(J1)\r\n"
#else
   #define  _Autostart_txt        "\r\nАвтостарт \r\nвiдключен.(PIN1)\r\n"
#endif

    //  Тексты характерные для отдельных групп агрегатов.
#define  _PWM_test             "\r\nТест каналiвPWM:"
#define  _UPrg_prompt          "\r\nВибiр програми:"
#define  _INP_prompt           "\r\nВхiднi сигнали:"
#define  _DAC_Shift_Null       "Змiщення нуля "
#define  _DAC_Test             "Тест дiапазону"

    //  Программа ввода и контроля пароля.
           //  Формулировки заменены на сокращенные т.к. в ВТЕ не хватает памяти на константы.
#define  _PasswordSize           ( 3 )
#define  _NoPassword_txt         "\r\n Заблок.паролем!"
#define  _MenuPassword_txt       "\r\nВибiр дiї: \r\n"
#define  _EnterPassword_txt      "\r1.Введен.пароля "
#define  _RecovPassword_txt      "\r2.Вiднов.пароля "
#define  _SetPassword_txt        "\r\nВведiть пароль: "
#define  _RecoveCodePassword_txt "\r\nКод Вiдн.Пароля:"
#define  _WrongPassword_txt      "\rПароль невiрний!"
#define  _ChangePassword_txt     "\r1.Змiн.пароль  "
#define  _ActivatePassword_txt   "\r2.Актив.пароль  "
#define  _ActivatedPassword_txt  _RightPassword_txt
#define  _OkNewPassword_txt      _RightPassword_txt
#define  _ProbelPassword_txt     "\r    -------    \r"
#define  _Time_Password_txt      _Sec( 3.0 )


#ifdef  _RES_I2C
  #define  _RES_Tst              "\r\n Налаг.Рез.:"
  #define  _RES_NASTR_DIAP       "Налаг. Дiапаз."
  #define  _RES_COUNT_NASTR      "Лiчильн.вимiр."
  #define  _RES_PAST_NASTR       "Поперед.налаш."
    // колич. подменю - _RES_NASTR_DIAP, _RES_COUNT_NASTR, _RES_PAST_NASTR
  #define  _RES_Ntab2             3

struct RES_output_tab  {
         char const *txt ;
         struct Res_Memory *p ;
 //        word setka ;
       } ;

#endif

  // Автоустановка АЦП
#define  _AutoSetADC_txt          "АвтоУст.Змiщ. "
#define  _SetNo_txt               "\rВстанов.? Нi  "
#define  _SetYes_txt              "\rВстанов.? Так "
#define  _PresentInpSign_txt      "\rПрисут.ВхiдСигн."
#define  _ContinueNo_txt          "\rПродовжити? Нi "
#define  _ContinueYes_txt         "\rПродовжити? Так"
#define  _SetOk_txt               "\rВстанов.виконанa"
#define  _SetBad_txt              "\rЧастковоВстанов."
#define  _CheckByHand_txt         "\rПеревiр. вручну "
#define  _ProgInhibit_txt         "\rПрогрЗаборВстан."
#define  _SetByHand_txt           "\rВстанов. вручну "

//---------------------
#define  _SetJrn_prompt        "\n\r Налашт.Журналу:\n"
#define  _Jrn_Message_prompt   "\r\n Повiд. журналу:"
#define  _JrnMsg               "Змiн.Повiдомл."
#define  _TimeStartProg        "Старт системи."
#define  _Jrn_no_Wrt           "\n\rЗапису немає.\n"

//---------------------
#define  _jrnMultiplicity         "1.Кратнiсть "
#define  _jrnQuantity             "2.Кiлькiсть "
#define  _jrnList                 "3.Перелiк   "

#define  _jrnNewChannel           "3.1.НовийКанал"
#define  _jrnCondition            "3.2.Умова     "
#define  _jrnLevel                "3.3.Рiвень    "

//---------------------
#define  _sldMultiplicity         "Кратнiсть "
#define  _sldAutoStart            "Автостарт "
#define  _sldQuantity             "Кiлькiсть "
#define  _sldList                 "Перелiк   "

#define  _sldStop                 "1.Зупинкa"
#define  _sldStart                "2.Пуск   "

#define  _sldParameter            "-1.Параметр   "
#define  _sldType                 "-2.Тип        "
#define  _sldBitNumber            "-3.Номер бiта "
#define  _sldCondition            "-4.Умова      "
#define  _sldValue                "-5.Значення   "
#define  _sldDelay                "-6.Затримка   "
#define  _sldFilterTime           "-7.ЧасФiльтра "
#define  _sldOnCondition          "-8.Увiм.умови "

#define  _sldAnal                 "-2.1.Аналогов."
#define  _sldBit                  "-2.2.Бiтовий  "

#define  _sldOff                  "-8.1.Вимкнено "
#define  _sldOn                   "-8.2.Увiмкнено"

#define  _sldEquals               "-4.1.Дорiвнює "
#define  _sldLess                 "-4.2.Менше    "
#define  _sldMore                 "-4.3.Бiльше   "

//---------------------
#define   _Net_ModbusTCPIP_         "\r\nМереж:ModbusTCP\n"
#define   _Net_ModbusRTU_           "\r\nМереж:ModbusRTU\n"
#define   _Net_ProfibusDP_          "\r\nМереж:ProfibusDP\n"
#define   _Net_CANopen_             "\r\nМереж:CANopen\n"
#define   _Net_RS485FD_             "\r\nМереж:RS485FD\n"
#define   _Net_NotDefine_           "\r\nМереж:--------\n"

#define   _NetSetabBit_prompt           "\r\nМереж:БитУст "
#define   _NetSetab_prompt              "\r\nМереж:Уставк."
#define   _NetIndicatr_prompt           "\r\nМереж:Индик. "

//---------------------
#ifndef    _KTE_GD
 #ifndef   _AD_ROT           // КТЕ :
  #define  _Fazir_Jakor      "\r1.Якоря?      "
  #define  _Fazir_Vozb       "\r2.Збудника?   "
 #else                       // АД - АТК или УПТФ :
   #define _Fazir_Jakor      "\r1.Ротора?      "
   #define _Fazir_rot_txt    "\r\nФазув.ротора:   "
  #ifdef   _UPTF                // УПТФ :
   #define _Fazir_Vozb       "\r2.Ступенів?    "
   #define _Fazir_stup_txt   "\r\nФазув.ступенів: "
   #define _Stup_txt         "\rСтупінь="
  #else                         // АТК :
   #define _Fazir_Vozb       "\r2.Короткозамик?"
   #define _Fazir_stup_txt   "\r\nФазув.КЗ:       "
   #define _KZ_off           "\rКЗ вимкнено. "
   #define _KZ_on            "\rКЗ увімкнено."
  #endif
 #endif
#else                        // КТЕ-ГД :
  #define  _Fazir_Jakor      "\r1.Збуд.генер.?"
  #define  _Fazir_Vozb       "\r2.Збуд.двиг.? "
#endif

  #define _Fazir_sdvig       "\r N_зсув = "
  #define _Power_On          "\r Увімкнути Uсил"

#ifndef  _Fazir_sdvig_isp_txt
  #define _Fazir_sdvig_isp_txt  "\r\nЗсув ИУ забло-\r\nковано викон.реж."
#endif

//--------- Для чтения уставок -----------------------------------
#define _Agr_        "Тип агрегату: "
#define _Obj_        "Об'єкт:       "
#define _Prog_       "Версія ПЗ:    "
#define _DT_         "Дата/Час ПЗ:  "
#define _Size_i2c_   "Об'єм ЕОЗП:   "
#define _Size_8kb_   "8 кб  "
#define _Size_32kb_  "32 кб "
#define _Size_64kb_  "64 кб "
#define _Size_512kb_ "512 кб "

//#ifndef _Size_No_
  #define _Size_No_    "Відсутній "
//#endif

#define _Ust_        "Уставки:"
#define _BitUst_     "Бітові уставки:"
#define _TstADC_     "Тест АЦП:"
#define _VivDAC_     "Вивед. на ЦАП:"
#define _Smech_      "Зм = "
#define _Up_         "U = +"
#define _Um_         "U = -"
#define _Pusto_      "   "
#define _SmDAC_      "Зміщення ЦАП:"
#define _VarSled_    "Змінні сліду:"
#define _VarJrn_     "Змінні журналу:"
#define _Bit_        "Біт "
#define _DecNum_     "Позначення схеми: "

#ifdef _RES_I2C  //_BTE_NEW
 #define _NAST_RES_     "Налаштування резисторів:"
 #define _R_ZAD_        "Rуст.= "
 #define _R_ZAD_PRED_   "(Ом)    Rпред.= "
 #define _N_IZM_R_      "(Ом)    Nизм.= "
 #define _IZM_RAZ_      "(раз.)"

#endif

#ifdef _NET_IRQ

#define _NetUst_        "Мережа: Уставк."
#define _NetBitUst_     "Мережа: БітУст "
#define   _NetModbusTCPIP_         "Мережа:ModbusTCP/IP"
#define   _NetModbusRTU_           "Мережа:ModbusRTU"
#define   _NetProfibusDP_          "Мережа:ProfibusDP"
#define   _NetCANopen_             "Мережа:CANopen"
#define   _NetRS485FD_             "Мережа:RS485FD"
#define   _NetNotDefine_           "Мережа:--------"

#endif

//----------------------------------------------------------------
 #ifdef _Po0_
#define _Po0_invert_    "Po0-інверт. "
 #endif
 #ifdef _AsPo0_
#define _AsPo0_invert_  "AsPo0-інв.  "
 #endif
 #ifdef _AsPo1_
#define _AsPo1_invert_  "AsPo1-інв.  "
 #endif
 #ifdef _AsPo2_
#define _AsPo2_invert_  "AsPo2-інв.  "
 #endif
 #ifdef _AsPo3_
#define _AsPo3_invert_  "AsPo3-інв.  "
 #endif
 #ifdef _AsPo4_
#define _AsPo4_invert_  "AsPo4-інв.  "
 #endif
 #ifdef _AsPo5_
#define _AsPo5_invert_  "AsPo5-інв.  "
 #endif
 #ifdef _AsPo6_
#define _AsPo6_invert_  "AsPo6-інв.  "
 #endif
 #ifdef _AsPo7_
#define _AsPo7_invert_  "AsPo7-інв.  "
 #endif
//---
#define _Pi0_invert_    "Pi0-інверт. "
 #ifdef _Pi1_
#define _Pi1_invert_    "Pi1-інверт. "
 #endif
 #ifdef _Pi2_
#define _Pi2_invert_    "Pi2-інверт. "
 #endif
 #ifdef _AsPi0_
#define _AsPi0_invert_  "AsPi0-інв.  "
 #endif
 #ifdef _AsPi1_
#define _AsPi1_invert_  "AsPi1-інв.  "
 #endif
 #ifdef _AsPi2_
#define _AsPi2_invert_  "AsPi2-інв.  "
 #endif
 #ifdef _AsPi3_
#define _AsPi3_invert_  "AsPi3-інв.  "
 #endif
 #ifdef _AsPi4_
#define _AsPi4_invert_  "AsPi4-інв.  "
 #endif
 #ifdef _AsPi5_
#define _AsPi5_invert_  "AsPi5-інв.  "
 #endif
 #ifdef _AsPi6_
#define _AsPi6_invert_  "AsPi6-інв.  "
 #endif
 #ifdef _AsPi7_
#define _AsPi7_invert_  "AsPi7-інв.  "
 #endif
 #ifdef _AsPi8_
#define _AsPi8_invert_  "AsPi8-інв.  "
 #endif
 #ifdef _AsPi9_
#define _AsPi9_invert_  "AsPi9-інв.  "
 #endif
 #ifdef _AsPi10_
#define _AsPi10_invert_ "AsPi10-інв. "
 #endif
 #ifdef _AsPi11_
#define _AsPi11_invert_ "AsPi11-інв. "
 #endif
 #ifdef _AsPi12_
#define _AsPi12_invert_ "AsPi12-інв. "
 #endif
 #ifdef _AsPi13_
#define _AsPi13_invert_ "AsPi13-інв. "
 #endif
 #ifdef _AsPi14_
#define _AsPi14_invert_ "AsPi14-інв. "
 #endif
 #ifdef _AsPi15_
#define _AsPi15_invert_ "AsPi15-інв. "
 #endif

  //-----
  #else //ifndef _LANG_RU_
  //-----

#define  _Monitor_prompt       "\r\n Монитор. "
#define  _Dispet_prompt        "\r\n Диспетчер. "
#define  _Disp_ComNotServed    "\r\nКоманда не \r\n обслуживается."
#define  _Ostanov_prompt       "\r\n ОСТАНОВ.\r\n"
#define  _Setab_prompt         "\r\n Уставки: "
#define  _SetabBit_prompt      "\r\nУставки битовые:"
#define  _Norton_prompt        "\r\n Меню: \r\n"
#define  _Indicatr_prompt      "\r\n Индикация: "
#define  _Clock_prompt         "\r\nЧасы: "
#define  _Clock1_prompt        "\r\nНастройка часов: "
#define  _AvWell_txt           "A>"
#define  _avWell_txt           "a>"
#define  _PrWell_txt           "W>"
#define  _prWell_txt           "w>"
#define  _RWell_txt            "R>"
#define  _rWell_txt            "r>"
#define  _GWell_txt            "G>"
#define  _gWell_txt            "g>"
#define  _OWell_txt            "O>"
#define  _CWell_txt            "C>"
#define  _cWell_txt            "c>"
#define  _SWell_txt            "S>"
#define  _sWell_txt            "s>"
#define  _Message_prompt       "\r\n Сообщения: "
#define  _Msg_notSupport_txt   "Сооб.рег.2 N"
#define  _FirstAvMsg_txt       "Первая авария:\r\n"
#define  _AvMsg_txt            "Аварии:\r\n"
#define  _PrMsg_txt            "Предупр.:\r\n"
#define  _Srv1Msg_txt          "\r\nСм.служеб.сооб."
#define  _Srv2Msg_txt          "Служеб.сооб.:\r\n"
#define  _NoMsg_txt            "Сообщений нет."
#define  _ADC_Tst_txt          "\r\n Тест АЦП:"
#define  _ADC_chnl             "\r "
#define  _DAC_Tst              "\r\n Тест ЦАП:"
#define  _Input_Tst            "\r\nДискрет.входы:"
#define  _Input_Tst_c          'c'
#define  _Input_Tst_m          'm'
#define  _Output_Tst           "\r\nДискрет.выходы:"
#define  _Output_Tst_c         'c'
#define  _Output_Tst_m         'm'
#define  _Output_Tst_Q1        "Q1V=_П_"
#define  _Output_Tst_q1        "Q1V=_п_"
#define  _Output_Tst_Q2        "Q2V=_П_"
#define  _Output_Tst_q2        "Q2V=_п_"
#define  _Test_EOZU_txt        "\r\nТест ЭОЗУ:"
#define  _Test_i2c_txt         "\rТест памяти i2c"
#define  _Test_clock_txt       "\rТест памяти час."
//#define  _TypeUst_prompt       "\r\nТиповые уставки\r\n восстановлены."
//KVV_backup
//#define  _TypeUst_txt          "\r\n Ок    "
#define  _ReLoadAvar_txt       "\r\nВосстанов.авар.:"
#define  _ReLoad_prm           "\r Nавар="
#define  _Avar_Not_txt         "\r\nАварий нет."
#define  _Error_i2c_txt        "\r\nНеисправн. ЭОЗУ."
#define  _NoConnect_i2c_txt    "\r\nНет ответа ЭОЗУ."
#define  _Test_RAM_txt         "\r\nТест ОЗУ:"
#define  _Error_RAM_txt        "\r\nНеисправн. ОЗУ."
#define  _Waiting_txt          "\r\n Ожидайте."
#define  _Test_DP_txt          "\r\nТест DP:"
#define  _Error_DP_txt         "\r\nНеисправн. DP."
#define  _Test_Yes_txt         "\rТест?-да ."
#define  _Test_No_txt          "\rТест?-нет."
#define  _DAC_tabl_txt         "\r\n Вывод на прибоp"
#define  _Fazir_Is_txt         "\r\nФазировка токов:"
#define  _Fazir_Is_txt_Ia_Ir   "\r\n F,Isa%,Isr%,Cos"
#define  _Fazir_Us_txt         "\r\nФазировка напряжений:"
//---- для двухмостовых возбудителей.
//#define  _Fazir_2Mosta
#define  _Fazir_vozb_txt       "\r\nФазировка моста:"
#define  _Fazir_Yes_txt        "\rНачать?-да ."
#define  _Fazir_No_txt         "\rНачать?-нет."
#define  _Fazir_Most           "\rМост="
#define  _Fazir_sdvig_txt      "\r\nСдвиг ИУ забло-\r\nкирован защитой."
#define  _Fazir_auto_txt       "\r\nЗаблокировано\r\nавтофазировкой."
#define  _Fazir_txt_Q1         "\r\n Недоступно при\r\nсобр.силов.цепи."
#define  _Fazir_txt_avt220     "\r\nНедоступно с \r\nоткл.'=220В'."
#define  _Offset_normal_txt    "\r\nСмещения в норме."
#define  _Offset_anormal_txt   "\r\nСмещения не в норме."
#define  _F2_prompt_txt        "\r\nНаладка:"
#define  _Not_Selected_DS_txt  "\r\nНе выбран \r\n датчик скор."
#define  _Cikl_Reg_txt         "\rРег.="
#define  _Sled_prompt          "\r\n След:\n\r"
#define  _Sled_txt0            "\n\r Переменные:\n\r"
#define  _Sled_txt1            "\n\r Строк:\n"
#define  _SetSled_prompt       "\n\r Настр.регистр.:\n"
#define  _SetSled_txt0         "\n\r Количество:\n\r"
#define  _SetSled_txt1         "\n\r Список:\n"
#define  _SetSled_txt2         "\n\r Выбор:\n"
#define  _SetSled_txt3         "\n\r Адрес:\n"
#define  _SetSled_txt4         "\n\r Тип:\n"
#define  _SetSled_txt5         "\n\r Кратность:\n"
#define  _SetSled_txt6         " Выход?       "
#define  _SetSled_txt7         "\n\r Автостарт:\n"
#define  _Page_txt             "\r\n\r\nСтраница-"
#define  _SaveUst_prompt       "\r\nСохран.уставок:"
#define  _SaveNo_txt           "\rОтмена.        " // "\rСохранить?-нет."
#define  _SaveYes_txt          "\rСохр.Рабочие.  " // "\rСохранить?-да. "
//#define  _Saved_txt            "\r\n Записано. "
//KVV_backup
//  #define  _SaveNo_txt       "\rВыход         "
//  #define  _SaveYes_txt      "\rЗапись        "
  #define  _SaveBackUp_txt     "\rСохр.Резервныe" // "\rРезервировать?"
  #define  _Saved_txt          "\r\n Ок         "

// 22.05.2020 14:47 Перенесено из #ust_i2c.c
#define  _TypeUst_Prompt       "\r\nТиповые уставки:"
#define  _RestoreNo_txt        "\rОтмена.         " // "\rВосстанов.?-Нет."
#define  _RestoreYes_txt       "\rВосст.Типовые.  "
#define  _RestoreWork_txt      "\rВосст.Рабочие.  "
#define  _RestoreBackUp_txt    "\rВосст.Резервныe."

#define  _Ostanov_Prompt       "\r\nРежим 'Останов':"
#define  _OstanovYes_txt       "\rУстановить?-да. "
#define  _OstanovNo_txt        "\rУстановить?-нет."
#define  _Agregat_txt          "\r\n Объект:\r\n"
#define  _AgregatOut_txt       "\rОтсутствует."
#define  _About_Prompt         "\r\nО системе:"
#define  _Type_Agregat_txt     "Тип агрегатa "
#define  _DateTime_txt         "Дата/Время ПО"
#define  _Type_Program_txt     "Версия ПO    "
#define  _Size_i2c_txt         "Объем ЭОЗУ   "
#define  _Size_i2c_8kb_txt     " 8 кб        "
#define  _Size_i2c_32kb_txt    " 32 кб       "
#define  _Size_i2c_64kb_txt    " 64 кб       "
#define  _Size_i2c_512kb_txt   " 512 кб      "
#define  _Size_i2c_No_txt      " Отсутствует "
#define  _MinSize_i2c_txt      "\r\nУстановлена ЭОЗУ\r\nменее 32кб\r\n"
#define  _ObjectOblUst         "Объект "
#define  _Decimal_txt          "Обознач.схемы "
#define  _ErrRAM_txt           "\r\nОЗУ неисправно"
#define  _Reset_Counter_txt    "\n\rОбнул. счетчик?"
#define  heading_comb_menu     "\n\rКомб.Редак.: "

#ifndef   _SaveUst_prompt
  #define  _SaveUst_prompt   "\r\nЗапись уставок:"
  #define  _Agregat_txt      "\r\n Объект:\r\n"
  #define  _SaveYes_txt      "\rЗаписать?-да ."
  #define  _SaveNo_txt       "\rЗаписать?-нет."
  #define  _Saved_txt        "\r\n Записано. "
#endif

#if defined _CM3_
   #define  _Autostart_txt        "\r\nАвтостарт \r\nотключен.(S6.1)\r\n"
#elif defined _F16e
   #define  _Autostart_txt        "\r\nАвтостарт \r\nотключен.(PIN12)\r\n"
#elif defined _J1
   #define  _Autostart_txt        "\r\nАвтостарт \r\nотключен.(J1)\r\n"
#else
   #define  _Autostart_txt        "\r\nАвтостарт \r\nотключен.(PIN1)\r\n"
#endif

    //  Тексты характерные для отдельных групп агрегатов.
#define  _PWM_test             "\r\nТест каналовPWM:"
#define  _UPrg_prompt          "\r\nВыбор программы:"
#define  _INP_prompt           "\r\nВходные сигналы:"
#define  _DAC_Shift_Null       "Смещение нуля "
#define  _DAC_Test             "Тест диапазона"

    //  Программа ввода и контроля пароля.
           //  Формулировки заменены на сокращенные т.к. в ВТЕ не хватает памяти на константы.
#define  _PasswordSize           ( 3 )
#define  _NoPassword_txt         "\r\n Заблок.паролем!"
#define  _MenuPassword_txt       "\r\nВыбор действия: \r\n"
#define  _EnterPassword_txt      "\r1.Ввод пароля   "
#define  _RecovPassword_txt      "\r2.Восст. пароля "
#define  _SetPassword_txt        "\r\nВведите пароль: "
#define  _RecoveCodePassword_txt "\r\nКод ВосстПароля:"
#define  _WrongPassword_txt      "\r Пароль неверен!"
#define  _ChangePassword_txt     "\r1.Измен.пароля  "
#define  _ActivatePassword_txt   "\r2.Актив.пароля  "
#define  _ActivatedPassword_txt  _RightPassword_txt
#define  _OkNewPassword_txt      _RightPassword_txt
#define  _ProbelPassword_txt     "\r    -------    \r"
#define  _Time_Password_txt      _Sec( 3.0 )


#ifdef  _RES_I2C
  #define  _RES_Tst              "\r\n Настр.Рез.:"
  #define  _RES_NASTR_DIAP       "Настр. Диапаз."
  #define  _RES_COUNT_NASTR      "Счетчик изм.  "
  #define  _RES_PAST_NASTR       "Предыд. настр."
    // колич. подменю - _RES_NASTR_DIAP, _RES_COUNT_NASTR, _RES_PAST_NASTR
  #define  _RES_Ntab2             3

struct RES_output_tab  {
         char const *txt ;
         struct Res_Memory *p ;
 //        word setka ;
       } ;

#endif

  // Автоустановка АЦП
#define  _AutoSetADC_txt          "АвтоУст.Смещ. "
#define  _SetNo_txt               "\rУстанов.? Нет"
#define  _SetYes_txt              "\rУстанов.? Да "
#define  _PresentInpSign_txt      "\rПрисут.ВходСигн."
#define  _ContinueNo_txt          "\rПродолжить? Нет"
#define  _ContinueYes_txt         "\rПродолжить? Да "
#define  _SetOk_txt               "\rУстанов.выполн. "
#define  _SetBad_txt              "\rЧастичн.установ."
#define  _CheckByHand_txt         "\rПровер. вручную "
#define  _ProgInhibit_txt         "\rПрогрЗапр.Устан."
#define  _SetByHand_txt           "\rУстанов.вручную "

//---------------------
#define  _SetJrn_prompt        "\n\r Настр. журнала:\n"
#define  _Jrn_Message_prompt   "\r\n Сообщ. журнала:"
#define  _JrnMsg               "Изм.Сообщений."
#define  _TimeStartProg        "Старт системы."
#define  _Jrn_no_Wrt           "\n\r Записи нет.\n"

//---------------------
#define  _jrnMultiplicity         "1.Кратность "
#define  _jrnQuantity             "2.Количествo"
#define  _jrnList                 "3.Список    "

#define  _jrnNewChannel           "3.1.НовыйКанал"
#define  _jrnCondition            "3.2.Условие   "
#define  _jrnLevel                "3.3.Уровень   "

//---------------------
#define  _sldMultiplicity         "Кратность "
#define  _sldAutoStart            "Автостарт "
#define  _sldQuantity             "Количествo"
#define  _sldList                 "Список    "

#define  _sldStop                 "1.Остановка"
#define  _sldStart                "2.Пуск     "

#define  _sldParameter            "-1.Параметр   "
#define  _sldType                 "-2.Тип        "
#define  _sldBitNumber            "-3.Номер бита "
#define  _sldCondition            "-4.Условие    "
#define  _sldValue                "-5.Значение   "
#define  _sldDelay                "-6.Задержка   "
#define  _sldFilterTime           "-7.Вр.Фильтра "
#define  _sldOnCondition          "-8.Вкл.уcловиe"

#define  _sldAnal                 "-2.1.Аналогов."
#define  _sldBit                  "-2.2.Битовый  "

#define  _sldOff                  "-8.1.Выключенo"
#define  _sldOn                   "-8.2.Включено "

#define  _sldEquals               "-4.1.Равно    "
#define  _sldLess                 "-4.2.Меньше   "
#define  _sldMore                 "-4.3.Больше   "

//---------------------
#define   _Net_ModbusTCPIP_         "\r\nСеть: ModbusTCP\n"
#define   _Net_ModbusRTU_           "\r\nСеть: ModbusRTU\n"
#define   _Net_ProfibusDP_          "\r\nСеть: ProfibusDP\n"
#define   _Net_CANopen_             "\r\nСеть: CANopen\n"
#define   _Net_RS485FD_             "\r\nСеть: RS485FD\n"
#define   _Net_NotDefine_           "\r\nСеть: --------\n"

#define   _NetSetabBit_prompt           "\r\nСеть: БитУст  "
#define   _NetSetab_prompt              "\r\nСеть: Уставки "
#define   _NetIndicatr_prompt           "\r\nСеть: Индик.  "

//---------------------
#ifndef    _KTE_GD
 #ifndef   _AD_ROT           // КТЕ :
  #define  _Fazir_Jakor      "\r1.Якоря?      "
  #define  _Fazir_Vozb       "\r2.Возбудителя?"
 #else                       // АД - АТК или УПТФ :
   #define _Fazir_Jakor      "\r1.Ротора?      "
   #define _Fazir_rot_txt    "\r\nФазир.ротора:   "
  #ifdef   _UPTF                // УПТФ :
   #define _Fazir_Vozb       "\r2.Ступеней?    "
   #define _Fazir_stup_txt   "\r\nФазир.ступеней: "
   #define _Stup_txt         "\rСтупень="
  #else                         // АТК :
   #define _Fazir_Vozb       "\r2.Короткозамык?"
   #define _Fazir_stup_txt   "\r\nФазир.КЗ:       "
   #define _KZ_off           "\rКЗ отключен."
   #define _KZ_on            "\rКЗ включен. "
  #endif
 #endif
#else                        // КТЕ-ГД :
  #define  _Fazir_Jakor      "\r1.Возб.генер.?"
  #define  _Fazir_Vozb       "\r2.Возб.двиг.? "
#endif

  #define _Fazir_sdvig       "\r N_сдвиг = "
  #define _Power_On          "\r Включить С.Н."

#ifndef  _Fazir_sdvig_isp_txt
  #define _Fazir_sdvig_isp_txt  "\r\nСдвиг ИУ забло-\r\nкирован исп.реж."
#endif

//--------- Для чтения уставок -----------------------------------
#define _Agr_        "Тип агрегата: "
#define _Obj_        "Объект:       "
#define _Prog_       "Версия ПО:    "
#define _DT_         "Дата/Время ПО:"
#define _Size_i2c_   "Объем ЭОЗУ:   "
#define _Size_8kb_   "8 кб  "
#define _Size_32kb_  "32 кб "
#define _Size_64kb_  "64 кб "
#define _Size_512kb_ "512 кб "

//#ifndef _Size_No_
  #define _Size_No_    "Отсутствует "
//#endif

#define _Ust_        "Уставки:"
#define _BitUst_     "Битовые уставки:"
#define _TstADC_     "Тест АЦП:"
#define _VivDAC_     "Вывод на ЦАП:"
#define _Smech_      "См = "
#define _Up_         "U = +"
#define _Um_         "U = -"
#define _Pusto_      "   "
#define _SmDAC_      "Смещение ЦАП:"
#define _VarSled_    "Переменные следа:"
#define _VarJrn_     "Переменные журнала:"
#define _Bit_        "Бит "
#define _DecNum_     "Обозначение схемы:"

#ifdef _RES_I2C  //_BTE_NEW
 #define _NAST_RES_     "Настройка резисторов:"
 #define _R_ZAD_        "Rуст.= "
 #define _R_ZAD_PRED_   "(Ом)    Rпред.= "
 #define _N_IZM_R_      "(Ом)    Nизм.= "
 #define _IZM_RAZ_      "(раз.)"

#endif

#ifdef _NET_IRQ

#define _NetUst_        "Сеть: Уставки "
#define _NetBitUst_     "Сеть: БитУст  "
#define   _NetModbusTCPIP_         "Сеть: ModbusTCP/IP"
#define   _NetModbusRTU_           "Сеть: ModbusRTU"
#define   _NetProfibusDP_          "Сеть: ProfibusDP"
#define   _NetCANopen_             "Сеть: CANopen"
#define   _NetRS485FD_             "Сеть: RS485FD"
#define   _NetNotDefine_           "Сеть: --------"

#endif

//----------------------------------------------------------------
 #ifdef _Po0_
#define _Po0_invert_    "Po0-инверт. "
 #endif
 #ifdef _AsPo0_
#define _AsPo0_invert_  "AsPo0-инв.  "
 #endif
 #ifdef _AsPo1_
#define _AsPo1_invert_  "AsPo1-инв.  "
 #endif
 #ifdef _AsPo2_
#define _AsPo2_invert_  "AsPo2-инв.  "
 #endif
 #ifdef _AsPo3_
#define _AsPo3_invert_  "AsPo3-инв.  "
 #endif
 #ifdef _AsPo4_
#define _AsPo4_invert_  "AsPo4-инв.  "
 #endif
 #ifdef _AsPo5_
#define _AsPo5_invert_  "AsPo5-инв.  "
 #endif
 #ifdef _AsPo6_
#define _AsPo6_invert_  "AsPo6-инв.  "
 #endif
 #ifdef _AsPo7_
#define _AsPo7_invert_  "AsPo7-инв.  "
 #endif
//---
#define _Pi0_invert_    "Pi0-инверт. "
 #ifdef _Pi1_
#define _Pi1_invert_    "Pi1-инверт. "
 #endif
 #ifdef _Pi2_
#define _Pi2_invert_    "Pi2-инверт. "
 #endif
 #ifdef _AsPi0_
#define _AsPi0_invert_  "AsPi0-инв.  "
 #endif
 #ifdef _AsPi1_
#define _AsPi1_invert_  "AsPi1-инв.  "
 #endif
 #ifdef _AsPi2_
#define _AsPi2_invert_  "AsPi2-инв.  "
 #endif
 #ifdef _AsPi3_
#define _AsPi3_invert_  "AsPi3-инв.  "
 #endif
 #ifdef _AsPi4_
#define _AsPi4_invert_  "AsPi4-инв.  "
 #endif
 #ifdef _AsPi5_
#define _AsPi5_invert_  "AsPi5-инв.  "
 #endif
 #ifdef _AsPi6_
#define _AsPi6_invert_  "AsPi6-инв.  "
 #endif
 #ifdef _AsPi7_
#define _AsPi7_invert_  "AsPi7-инв.  "
 #endif
 #ifdef _AsPi8_
#define _AsPi8_invert_  "AsPi8-инв.  "
 #endif
 #ifdef _AsPi9_
#define _AsPi9_invert_  "AsPi9-инв.  "
 #endif
 #ifdef _AsPi10_
#define _AsPi10_invert_ "AsPi10-инв. "
 #endif
 #ifdef _AsPi11_
#define _AsPi11_invert_ "AsPi11-инв. "
 #endif
 #ifdef _AsPi12_
#define _AsPi12_invert_ "AsPi12-инв. "
 #endif
 #ifdef _AsPi13_
#define _AsPi13_invert_ "AsPi13-инв. "
 #endif
 #ifdef _AsPi14_
#define _AsPi14_invert_ "AsPi14-инв. "
 #endif
 #ifdef _AsPi15_
#define _AsPi15_invert_ "AsPi15-инв. "
 #endif

  //-----
  #endif //ifndef _LANG_RU_
  //-----

/*------------------------------------------------*/
#ifdef _MSG_INCLUDE
/*------------------------------------------------*/

  //-----
  #ifndef _LANG_RU_
  //-----
     const char *const  c_Clock[] =  { "Час        ","Дата:д.м.р."};
     const char *const  u_Clock[] =  { "Хвилини     ",
                                       "Години      ",
                                       "День тижня  ",
                                       "День мiсяця ",
                                       "Мiсяць      ",
                                       "Рiк         ",
                                       "Калiбрування",
                                       "Перев.годин."
                                      };
     const char *const Day[8] = { " Пн."," Вт."," Ср."," Чт."," Пт."," Сб."," Нд.","Err" };

#define  _Summer_txt    "Лiтнє     "
#define  _Winter_txt    "Зимове    "
#define  _On_txt        "Увiмкнено "
#define  _Off_txt       "Вiдключено"
#define  _Calibr_txt    " c/доба "

            //  Вынесено для экономии памяти.
const char  _PasswordLtd_txt[]   = "\r\nОбмеженоПаролем!" ;
const char  _RightPassword_txt[] = "\r       Ok!      "   ;

const char  _Dostup_Gotovn_txt[] = "\r\nДоступно \r\n з 'Зб.Готовн.'" ;
const char  _Dostup_Rabota_txt[] = "\r\nДоступно \r\nз робочего реж." ;
const char  _Dostup_Ostanov_txt[]= "\r\nДоступно \r\n з 'ОСТАНОВу'"   ;
const char *c_Programm[2] = { "\rПеревiрка ОЗП   ", "\rПеревiрка запису"};
  //-----
  #else //ifndef _LANG_RU_
  //-----
     const char *const  c_Clock[] =  { "Время      ","Дата:д.м.г."};
     const char *const  u_Clock[] =  { "Минуты      ",
                                       "Часы        ",
                                       "День недели ",
                                       "День месяца ",
                                       "Месяц       ",
                                       "Год         ",
                                       "Калибровкa  ",
                                       "Перевод час."
                                      };
     const char *const Day[8] = { " Пн."," Вт."," Ср."," Чт."," Пт."," Сб."," Вс.","Err" };

#define  _Summer_txt    "Летнее    "
#define  _Winter_txt    "Зимнее    "
#define  _On_txt        "Включено  "
#define  _Off_txt       "Отключено "
#define  _Calibr_txt    " c/сут  "

            //  Вынесено для экономии памяти.
const char  _PasswordLtd_txt[]   = "\r\nОгранич.паролем!" ;
const char  _RightPassword_txt[] = "\r       Ok!      "   ;

const char  _Dostup_Gotovn_txt[] = "\r\nДоступно \r\n из 'Сб.Готовн.'" ;
const char  _Dostup_Rabota_txt[] = "\r\nДоступно \r\nиз рабочего реж." ;
const char  _Dostup_Ostanov_txt[]= "\r\nДоступно \r\n из 'ОСТАНОВа'"   ;
const char *c_Programm[2] = { "\rПроверка ОЗУ    ", "\rПроверка записи "};
  //-----
  #endif //ifndef _LANG_RU_
  //-----

/*------------------------------------------------*/
#endif //_MSG_INCLUDE
/*------------------------------------------------*/

#endif
