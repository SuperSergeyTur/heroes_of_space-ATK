

//      ПРОГРАММА ОТРАБОТКИ АВАРИЙНОГО ОТКЛЮЧЕНИЯ .
//----------------------------------------------------------------

void  Init_posle_DistSbr ( void )
  {
      Reg_AvarMsgFirst = 0 ;
      Reg_AvarMsg      = 0 ;
      Reg_PreduprMsg   = 0 ;
      Reg_ServiceMsg   = 0 ;
      //mask_predupr     = 0 ; чтобы по CAN-команде "ОСТАНОВ" не разбиралась
                              // Готовность.
      Reg_AvarMsgFirst2 = 0 ;
      Reg_AvarMsg2      = 0 ;
      Reg_PreduprMsg2   = 0 ;
      Reg_ServiceMsg2   = 0 ;
      //mask_predupr2     = 0 ;

#ifdef _TRETIY_REG
      Reg_AvarMsgFirst3 = 0 ;
      Reg_AvarMsg3      = 0 ;
      Reg_PreduprMsg3   = 0 ;
      Reg_ServiceMsg3   = 0 ;
      //mask_predupr3     = 0 ;
#endif

#ifdef _INTERPRETER
      Reg_AvarMsgFirst_obj = 0 ;
      Reg_AvarMsg_obj      = 0 ;
      Reg_PreduprMsg_obj   = 0 ;
      Reg_ServiceMsg_obj   = 0 ;
      //mask_predupr3     = 0 ;
#endif

      bo_Avar  = 0 ;
#ifdef bo_Avar_Yach
      bo_Avar_Yach = 0 ;
#endif
      //bo_canAvar = 0 ; // 20.09.06 16:34 находится в CAN_OBJ.C .
      //bo_canPredupr = 0 ;
      bo_Predupr = 0 ;
      // bo_Gotov = 0 ; // 25.05.06 16:09 для опер.откл. по CAN .
#ifdef _POWER
      bo_MB1_Razr = 0 ;
      bo_MB1_Otkl = 0 ;
#endif

      Prg.all = _Prg_Gotovn ;
      DWelcome = "\r\nDg>" ,  MWelcome = "\r\nMg>", AWelcome = _GWell_txt;  ;
      av_label = 0 ;
      time_VR1 = Timer1_Ovr ;//для отсчета откл.ЛК по 1VR.

      Av.all = 0 , Av2.all = 0 ;
#ifdef _ATK_SET // Переделываем сброс по переднему фронту и уровню только для АТК .
      Av._.DistSbros = 1 ;  // признак поддерживаем 1.5 сек для уверенного сброса ( дискретного или сетевого ).
#endif
        mClr_Q1() ;  //   При каждой очистке Av.all нужно сбрасывать Q1,Q2,
        mClr_Q2() ;  // иначе он залипнет если сброс попал на время импульса.
#ifndef _ALARM_FZ
  #ifdef  _Union_FR
      Alarm_on();
  #endif
#endif
      Isp._.Oprobov = 0 ;  // обнуляем для штатного опробования ГД.

      // V.flg.all = 0 ;        // 18.10.05 08:16 Не нужно обнулять все ,
      V.flg._.otkl_func = 0 ;  // достаточно обнулить отключение функционала
      V.Fv_zad = _Fv_nom( 1.00 ) ;
      V.flg._.Otkl_Imp  = 0 ;
      V.flg._.Sdvig_imp = 0 ;
      V.flg._.Iv_max    = 0 ;
          // если был задан F2:СИФУВ-Рез, то взводим его, иначе по сбросу
         // защит он отключится, т.к. откл. Блок.Упр.
      //if ( Isp._.SIFUV_Res == 0 ) V.flg._.RT = 1 ;

    /* Если cамонастройка была прервана - восстановление уставок */
      if( Isp._.Samonastr == 1 && zeds != 0 )
       {
         _r.Z_EDS = zeds , _r.T_ZISkorP_Razg = tzisk , _r.Z_SkMax_P = zskmax ;
         zeds = 0 ;
       }
//------------------------------------------------------
    /* Если автонастройка была прервана - восстановление уставок */
#ifdef   _AVTONASTR
       Avtonastroyka_RT ( 3 ) ;
#endif
//------------------------------------------------------

#ifdef  bo_DS_MT       // Для дистанционногои сброса платы МТ .
        bo_DS_MT = 1 ; // Взводим , через 300 мс он сбросится в Common_avar() .
#endif
//------------------------------------------------------

      Init_Regs () ; // переинициализация регуляторов.

/*------------ Для CAN- и объектной программы. ----------*/

      can_ConfigReg ( _CAN_DS1_Init ) ;
      ObjPrg ( _Obj_c_DS1_Init )  ;
      Control_otkr_tir ( _ConOtkr_DS1_Init ) ;
      //bo_Vkl_Vent = 0;
      Trg_Pusk = 0;
      return;
  }
     //-------------------------------------------
    // Частичная переинициализация при CAN-останове.
void  Init_Regs ( void )
  {
      mOtkl_Imp( _VR1_imp ) ;
      mVkl_Imp( _All_imp ^ _VR1_imp ) ;

      S.NumMost = 1 ;

#ifdef _REG_POL
      ZUgol = 0 ;
      ZIUgol = 0 ;
      Integr_RP = 0 , OuRP = 0 ;
      RP_in_sqr = 0 ;
#endif

      Set_ZI ( &zi_rs , 0 ) ;
      Z_Skor = 0, ZISkor = 0, OuIchRS = 0, OuRegS_dop_kod = 0 ;
      Delta_Sk = 0 , OuIchRS_k = 0 ;
      S.Alfa = _r.S_Alfa_Start ;
      fr2 = 0xffff;

      Set_ZIRT ( &zi_rt , 0 ) ;
      OIRT_drob = 0 ;
#ifndef _KTE_GD
      ZIDN  = ZIDN1 = 0 ;  /* выход ЗИ-РТ. */
   #ifdef _ATK_SET
      OuRegS_ogr = 0 ; // Ограниченное задание на ток от Ведущего к Ведомому .
      //---
      OIRT  = _r.S_Alfa_Start ; // В Сетевом Инверторе начальный угол - Альфа Максимум .
      OIRT1 = _r.S_Alfa_Start ;
   #else
      OIRT  = _r.RevU0  ;  /* интегратор регулятора тока */
      OIRT1 = _r.RevU0  ;  /* интегратор регулятора тока */
   #endif
   #ifdef _SIFU2_
      OIRT_drob_2_ = 0 ;
      ZIDN_2_  = ZIDN1_2_ = 0 ;  /* выход ЗИ-РТ. */
      OIRT_2_  = _r.RevU0  ;  /* интегратор регулятора тока */
      OIRT1_2_ = _r.RevU0  ;  /* интегратор регулятора тока */
   #endif
#else
      ORT = 0, OIRT  = 0 ;  /* интегратор регулятора тока */
      Integr_rn = 0 ;
      Integr_rn_drob = 0 ;
      Ug_zx = 0 , Out_rn = 0 ;
#endif

      RegFlg.all = 0 ;
      Z_sk.out = 0  ;
      //S.flg._.SPI = 0 ;

      // Сбрасываем флаги аварийного отключения , которые сработали при работе программы тестирования
      // "Контроль Пробоя Тиристоров" , после этого повторно производится тестирование тиристоров ,
      // если оно включено ...
      flg_RaTe._.tyr_tst_av = 0 ;

    return ;
  }

/*--------------------------------------------------*/

#ifdef _ATK_SET // Переделываем сброс по переднему фронту и уровню только для АТК .
void   DistSbros ( void )
{
  static  word  time_DS ;

           //   Централизованная обработка дистанционного сброса.
    //---
    // Команду сброса подали ( собственную или сетевую из соседнего АТК либо из платы АР2 ) :
  /*if ( bi_DS1 == 1 || ATK2_DS1 == 1 || KTE2_DS1 )
    {       // формируем признак для других программ
      Av._.DistSbros = 1 ;
      time_DS = Timer1_Ovr ;
    }
    // Команду сброса сняли , держим сброс 1.5 сек :
    else if ( Av._.DistSbros == 1 )
    {       // формируем признак для других программ
      if ( (u)(w)(Timer1_Ovr-time_DS) > _Sec( 1.5 ) )  Av._.DistSbros = 0 ;
    }*/

    //---
    // Команду сброса подали ( собственную или сетевую из соседнего АТК либо из платы АР2 ) .
    // Держим сброс 1.5 сек :
    if ( bi_DS1 == 1 || ATK2_DS1 == 1 || KTE2_DS1 )
    {       // формируем признак для других программ
      if ( (u)(w)(Timer1_Ovr-time_DS) < _Sec( 1.5 ) )  Av._.DistSbros = 1 ;
      else                                             Av._.DistSbros = 0 ;
    }
    // Команду сброса сняли и если признак еще не продержался 1.5 сек , то держим его :
    else if ( Av._.DistSbros == 1 )
    {
      if ( (u)(w)(Timer1_Ovr-time_DS) > _Sec( 1.5 ) )  Av._.DistSbros = 0 ;
    }
    else time_DS = Timer1_Ovr ;

  return ;
}
#endif

/*--------------------------------------------------*/

  // При необходимости объектного использования USEL необходимо в OBJ_DEF.H
  // определить имя _USEL_obj и в OBJ.C написать свою программу USEL_Work () .
#ifndef  _USEL_obj
void  USEL_Work ( void )
{
  static word T_USEL ;
   // USEL используется как Индикатор Состояния Системы :
   // 1."Загрузка"           -    горит ;
   // 2."Сб.Гот. "           - не горит ;
   // 3."Работа  "           -    горит ;
   // 4."Работа с предупр. " - мигает 1.00 с;
   // 5."Авария  "           - мигает 0.15 с;

    // Сборка Готовности :
  if ( Prg._.Gotovn == 1 )  mUSEL_set() , T_USEL = Timer1_fSec ;
    // Работа  с предупреждением или аварией :
  else if ( bo_Predupr == 1 || bo_Avar == 1 )
   {
     if ( bo_Avar == 1 )
      {
        if ( USEL == 1 && (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(0.15) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
        else if ( (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(0.15) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
      }
     else
      {
        if ( USEL == 1 && (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(1.00) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
        else if ( (u)((w)(Timer1_fSec - T_USEL)) >= _fSec(1.00) )
          {
            mUSEL_not() , T_USEL = Timer1_fSec ;
          }
      }
   }
    // Работа :
  else      mUSEL_clr() , T_USEL = Timer1_fSec ;

 return ;
}
#endif

/*--------------------------------------------------*/

//   Программа измерения мгновенного тока Id

#ifndef _Obj_Id_izm

void IdIzm (void)
  {
      Id_full = _AD_BUSY;
      mAD_Izm (  Id_mg_ach  , &Id_full ) ; // ИЗМЕРЕНИЕ  "Id_Full"

#ifdef  Irot_ach
      Irot_full = _AD_BUSY;
      mAD_Izm (  Irot_ach  , &Irot_full ) ; // ИЗМЕРЕНИЕ  "Irot_Full"
#endif

#ifdef   _SIFU2_  // Измерение суммарного тока :
    // 07.09.07 11:00 - Если аналоговый канал не определён , то знаковый суммарный
    // ток Id_sum находится в SIFU2.C как алгебраическая сумма двух мгновенных .
    // 14.09.2017 12:40 - Если аналоговый определён , то по знаковому суммарному
    // току Id_sum отрабатываем аварию в обоих СИФУ (Сказал Соломаха для Слябинга 12500) :
  #ifdef  Id_sum_ach
      Id_sum_full = _AD_BUSY;
      mAD_Izm (  Id_sum_ach  , &Id_sum_full ) ;
  #endif
#endif

      // Измерение токов по фазам :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
      IdIzm_3faz () ;
#endif

#ifndef _KTE_GD
   #ifdef _RVId
      RVId.Id1_full = _AD_BUSY;
      mAD_Izm (  Id1_ach  , &RVId.Id1_full ) ; // ИЗМЕРЕНИЕ  "Id1"

      RVId.Id2_full = _AD_BUSY;
      mAD_Izm (  Id2_ach  , &RVId.Id2_full ) ; // ИЗМЕРЕНИЕ  "Id2"
   #endif
#endif

#ifdef  Itt_ach
      Itt_full = _AD_BUSY;
      mAD_Izm (  Itt_ach    , &Itt_full ) ; // ИЗМЕРЕНИЕ  "Itt_Full"
#endif

#ifdef   _SIFU2_
  #ifdef  Itt1_ach // Для 12-ти пульсных систем канал трансформаторов тока ШС1 .
      Itt1_full = _AD_BUSY;
      mAD_Izm (  Itt1_ach    , &Itt1_full ) ; // ИЗМЕРЕНИЕ  "Itt1_Full"
  #endif
#endif

    return ;
  }

#endif

/*--------------------------------------------------*/

//   Программа преобразования измеренного тока Id из формата АЦП в
// нужный формат.
//   Включает также:
// - усреднение тока для тепловой защиты.

#ifndef _Obj_Id_conv

void IdConv (void)
  {
    word ix ;

    while ( Id_full == _AD_BUSY ); // 04.11.2008 15:02 Перенесено из СИФУ .

    //mIzmData_Conversion ( Id_nn , ix ,  Id_mg_ach   ) ;
        //   Масштабирование тока, как знакового.
    //Id_Detect =  (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;

    mIzmData_Conversion ( Id_full , ix ,  Id_mg_ach   ) ;
      ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
    //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
  #ifdef  _SIFU_1Faza
        // usrednyaem tok.
    ix = (Id_off + ix) / 3, Id_off = 0 ;
  #endif
        //   беззнаковый ток.
    IDV = ix ;
        //   знаковый ток по номеру моста.
    if ( S.NumMost != 2 ) Id_dop_kod =  ix ;
    else                  Id_dop_kod = ~ix + 1 ;
   //---
        // Усреднение тока для тепловой защиты.

#ifndef _KTE_GD
 #ifdef _SIFU2_
  if ( S.Disable == 1 ) // DAN 23.05.2017 14:46 - При работе только ШС2 :
  {
    Id_teplo = ( Id_teplo + IDV2 ) / 2  ;
  }
  else
 #endif
  {
   #ifndef _ATK_SET
    Id_teplo = ( Id_teplo + IDV ) / 2  ;
   #else // В режиме КЗ ротора сетевые ИУ сняты и ток через согласующий не течет .
    Id_teplo = ( Id_teplo + Irot ) / 2  ;  // В режиме КЗ ток течет только в роторной цепи , Id = 0 .
   #endif
  }
#else
    Id_teplo = IDV_g ;
#endif

#ifdef  Irot_ach
    while ( Irot_full == _AD_BUSY );

    mIzmData_Conversion ( Irot_full , ix ,  Irot_ach   ) ;
      ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
    //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
        //   беззнаковый ток.
    Irot = ix ;
#endif

#ifdef   _SIFU2_  // Измерение суммарного тока :
    // 07.09.07 11:00 - Если аналоговый канал не определён , то знаковый суммарный
    // ток Id_sum находится в SIFU2.C как алгебраическая сумма двух мгновенных .
    // 14.09.2017 12:40 - Если аналоговый определён , то по знаковому суммарному
    // току Id_sum отрабатываем аварию в обоих СИФУ (Сказал Соломаха для Слябинга 12500) :
  #ifdef  Id_sum_ach
    while ( Id_sum_full == _AD_BUSY );
    mIzmData_Conversion ( Id_sum_full , ix ,  Id_sum_ach   ) ;
    //   знаковый суммарный ток :
    Id_sum = (slw)(sw)ix * (slw)(sw)_or.Mashtab_Id_sum / 256 ;
  #endif
#endif

#ifdef  Id_sr_ach
    while ( Id_sr_full == _AD_BUSY );
        //  Преобразование измеренного среднего тока.
    mIzmData_Conversion ( Id_sr_full , ix ,  Id_sr_ach ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Id_sr = ix ;
#endif

#ifndef _KTE_GD
  #ifdef _RVId
    while ( RVId.Id1_full == _AD_BUSY );
        //  Преобразование измеренного среднего тока.
    mIzmData_Conversion ( RVId.Id1_full , ix ,  Id1_ach ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    //   Знаковый ток по номеру моста определять нельзя , тк
    // один из двух двигателей может быть в генераторном режиме .
    RVId.Id1 = ix ;  // знаковый ток .
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    RVId.IDV1 = ix ; // беззнаковый ток .

    while ( RVId.Id2_full == _AD_BUSY );
        //  Преобразование измеренного среднего тока.
    mIzmData_Conversion ( RVId.Id2_full , ix ,  Id2_ach ) ;
    ix = (slw)(sw)ix * (slw)(sw)Mashtab.Id / 256 ;
  //ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Id >> 8 ) ;
    //   Знаковый ток по номеру моста определять нельзя , тк
    // один из двух двигателей может быть в генераторном режиме .
    RVId.Id2 = ix ;  // знаковый ток .
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    RVId.IDV2 = ix ; // беззнаковый ток .
  #endif
#endif

      // Преобразование токов по фазам :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )
    IdConv_3faz () ;
#endif

   //---
  #ifdef  Itt_ach
    while ( Itt_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( Itt_full , ix ,  Itt_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Idtt = ix ;
  #endif
   //---

//--------------
#ifdef   _SIFU2_
//--------------
  #ifdef  Itt1_ach // Для 12-ти пульсных систем канал трансформаторов тока ШС1 .
    while ( Itt1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( Itt1_full , ix ,  Itt1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    Idtt1 = ix ;
  #endif
//--------------
#endif //_SIFU2_
//--------------

    return;
  }

#endif

/*--------------------------------------------------*/

#ifndef _Obj_Id_Max

// 08.04.2008 11:31 - Для добавления выдержки времени на аварию Id-max убран вызов в фоне
// контроля Id_Max , т.к. все равно измерение и преобразование тока выполняются в СИФУ .
// Для КТЭВ и КТЭВ-ГД добавлена выдержка времени на аварию Id-max для фильтрации помех .
// В КТЭ эта выдержка равна нулю .
void Control_Id_Max (void)
  {
// Контроль пробития тиристора работает только если определён сигнал с трансформаторов тока
// или ОС для РТ и есть Itt :
#if defined (Itt_ach) || defined (Itt1_ach) || defined (_Id_on_Itt_for_ProboyTir) //|| defined (Itt2_ach)
    static lword lax ;
  //static word xOtkl_Imp , xS_Alfa_Max , xS_Alfa ;  20.07.2017 9:45 - переменные для запоминания текущего
  //static byte xS_NumMost ;                                           состояния не нужны ...
  //static  byte n , nn , i ;
  #ifdef   _SIFU2_
  //static  byte n2 , nn2 ;
  //static word xS2_Alfa ;
  #endif
#endif
       //  Двойная проверка на случай затирания одного из двух битов
       // при наложении прерывания на операции с этими ячейками.
       // 08.04.2008 11:31 - Эта двойная проверка - пережиток прошлого ,
       // когда флаг выставлялся в СИФУ , а авария - в фоне .
    static byte Idmax, Idmax2;
    static word time_Id_max2;
    word ax;

    if ( (IDV >= _r.Id_Max /*||  Av._.Id_max == 1*/
#ifndef _KTE_GD
    #ifdef _RVId
         || RVId.IDV1 >= _r.Id_Max || RVId.IDV2 >= _r.Id_Max
    #endif
#endif
         ) && S.flg._.VneshZp == 0 ) // 16.10.2008 16:27 - ИУ моста отключены извне.
    {
      if ( ((u)((b)(Puls_counter - time_Id_max)) >= _r.time_Id_max) || Idmax == 1 ) // проверка длительности превышения.
      {
        Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
#ifndef _KTE_GD
  #ifndef _ATK_SET
        mOtkl_Q2 () ;
  #else
        mOtkl_Q1 () ;
  #endif
#else
        // DAN 08.11.2016 - В соответствии с гениальным техническим решением Соломахи и
        // Шестакова , отключаем автомат по защите "Id-Max" уже после того , как всё выгорит ,
        // для того , чтобы сберечь автомат ...
        //mOtkl_Q1 () ; 08.11.2016 15:18
#endif
#ifdef _RVId
    #ifndef _KTE_GD
        if ( IDV  >= _r.Id_Max ) mSet_AvarMsg  ( _Av_IdMax ) ;
        if ( RVId.IDV1 >= _r.Id_Max ) mSet_AvarMsg2 ( _Av2_Id1Max ) ;
        if ( RVId.IDV2 >= _r.Id_Max ) mSet_AvarMsg2 ( _Av2_Id2Max ) ;
    #endif
#else
        mSet_AvarMsg ( _Av_IdMax ) ;
#endif
        Idmax = 1 ; // когда счетчик Puls_counter обнулится , останется взведенным флаг ...
        Av._.Id_max = 1 ; // Только для регистрации в аварийном битовом поле .
      }
    }
    else time_Id_max = Puls_counter , Idmax = 0 ;

#ifdef   _SIFU2_  // Защита по суммарному току :
    // 14.09.2017 12:40 - Если аналоговый определён , то по знаковому суммарному
    // току Id_sum отрабатываем аварию в обоих СИФУ (Сказал Соломаха для Слябинга 12500) :
  #ifdef  Id_sum_ach
    if ( (sw)Id_sum > (sw)_or.Id_sum_max || (sw)Id_sum < (sw)(~_or.Id_sum_max +1) )
    {
        Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
        // Пока что без выдержки времени :
        mOtkl_Q2 () ;
        mSet_AvarMsg ( _Av_Id_sum_Max ) ;
        Av2._.Id_sum_max = 1 ; // Только для регистрации в аварийном битовом поле .
    }
  #endif
#endif

      // Распределение токов по фазам двух секций ШС :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
    TokRaspr_3faz () ;
#endif

    //---------------------------------------------------------------------------------------------------------------

    // Алгоритм определения Пробитого Тиристора .
// Контроль пробития тиристора работает только если определён сигнал с трансформаторов тока
// или ОС для РТ и есть Itt :
#if defined (Itt_ach) || defined (Itt1_ach) || defined (_Id_on_Itt_for_ProboyTir) //|| defined (Itt2_ach)
    //---
    // АЛГОРИТМ :     Если подавать одиночные импульсы и контролировать ток по переменке , то на месте
    //            пробитого тиристора будет ток по переменке , а по постоянке не будет . Но не  нужно
    //            забывать и о том , что в случае , если нагрузка подсоединена , то в одном плече с
    //            пробитым тиристором потечет ток и в постоянке , и в переменке .
    //                Угол должен быть подобран так , чтобы при невозможности тестирования без нагрузки
    //            ток , потребляемый в нагрузке , не принимался за ток пробитого тиристора ...
    //---
    // 12.07.2017 13:00 - DAN : Длительность теста : 20 мс идут ИУ с одним углом , затем уголд уменьшается на 1грд .
    //                    ( 180 - 150 грд ) * 20мс = 600мс .
    //---
    // По номеру тиристора , работающего в данный момент , определяем , какой тиристор пробит .
    // Вот только определить , в каком мосту ( Вперёд или Назад ) пробит тиристор - не получится .
    //---
    // Если оринтироваться по мосту "Вперёд" , получаем следующую таблицу , где :
    //   S.N - номер тиристора , на который подан тестовый одиночный ИУ ;
    //   n   - номер пробитого тиристора , через который потечёт ток фазного КЗ ;
    //   nn  - номер тиристора , находящегося в одном плече с пробитым , через который потечёт ток нагрузки ;
    //
    //                              |------------------------------|
    //                              |  ИУ  | Пробой | Ток нагрузки |
    //                              |------|--------|--------------|
    //                              |  S.N |    n   |     nn       |
    //                              |------|--------|--------------|
    //                              |   1  |    5   |      2       |
    //                              |   2  |    6   |      3       |
    //                              |   3  |    1   |      4       |
    //                              |   4  |    2   |      5       |
    //                              |   5  |    3   |      6       |
    //                              |   6  |    4   |      1       |
    //                              |------------------------------|
    //
    n  = S.N - 2 ; // Номер пробитого тиристора , через который течёт ток фазного КЗ .
    nn = S.N + 1 ; // Номер тиристора , находящегося в одном плече с пробитым , через который течёт ток нагрузки .
    if ( (sb)n  <= 0 ) n += 6 ;
    if ( (sb)nn >  6 ) nn = 1 ;
    //---
#ifdef   _SIFU2_
  #ifdef  Itt1_ach
    Iproboy1 = Idtt1 ;   // Ток трансформаторов тока ШС1 .
  #else
   #ifdef  _Id_on_Itt_for_ProboyTir
    Iproboy1 = IDV ;     // ОС для РТ - это и есть ток с Трансформаторов Тока .
   #else
    Iproboy1 = Idtt*2 ;  // Общий ток - это половина тока ШС1 .
   #endif
  #endif
#else
   #ifdef  _Id_on_Itt_for_ProboyTir
    Iproboy1 = IDV ;     // ОС для РТ - это и есть ток с Трансформаторов Тока .
   #else
    Iproboy1 = Idtt ;    // Ток трансформаторов тока .
   #endif
#endif

    // Проверка происходит в сборке готовности , при отсуствии Аварий и Предупреждений ( допускаем , что
    // Силовое Напряжение есть ) и отключенном ЛК .
    // Самое главное - флаги окончания теста не выставлены ( т.е. первый заход в тест ) .
    //---
       // Проверяем Av._.DistSbros != 1 , т.к. после выхода из аварии путём нажатия [Fn+Stop] выполняется
       // инициализация по дистанционному сбросу и вход в Сборку Готовности . А в OBJ.H эта комбинация
       // клавиш прописана как дискретный вход , и поэтому в Сборке Готовности выполняется повторный вход
       // в инициализацию по дистанционному сбросу ( уже во время Теста на Пробитие Тиристора ) , снимаются
       // ИУ и Альфа устанавливается в 120 грд ...
    if ( _r.Cfg2._.ProboyTir == 1 && Prg._.Gotovn == 1 && bo_Avar == 0 && bo_Predupr == 0 &&
#ifdef _KONTAKTOR_for_ProboyTir
         bi_QK1 == 1 && // Последний коммутационный аппарат - 3х фазный контактор , без включения которого нет силы на тиристорах
#endif
        flg_RaTe._.tyr_tst_ok == 0 && flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0 &&
        Av._.DistSbros != 1 && Klav_Buff != _Reset )
    {
        // Сюда будет несколько входов , для того , чтобы ИУ по ЗИ стали в 179 грд :
        if ( Otkl_Imp != 0 )
        {
            S.Alfa  = _Grad( 179 ) ;        //_or.AlfaTst ;   // Задаём угол для теста .
          //19.07.2017 14:52 - Нет смысла задавать выход ЗИ угла , т.к. в СИФУ всё равно будет рассчитываться ЗИ ...
          //S.Alfa_Old  = _Grad( 179 ) ;    //_or.AlfaTst ;   // Задаём угол для теста - чтобы не идти по ЗИ угла .
  #ifdef   _SIFU2_
            S2.Alfa  = _Grad( 179 ) ;       //_or.AlfaTst ;   // Задаём угол для теста .
          //19.07.2017 14:52 - Нет смысла задавать выход ЗИ угла , т.к. в СИФУ всё равно будет рассчитываться ЗИ ...
          //S2.Alfa_Old  = _Grad( 179 ) ;   //_or.AlfaTst ;   // Задаём угол для теста - чтобы не идти по ЗИ угла .
  #endif
            S.NumMost  = 1 ;                // Задаём мост "Вперёд" для теста .
            Prg.all |= _Sled ;              // Т.к. этот режим выполняется в Сборке Готовности , то включаем След .
            //---
            flg_RaTe._.tyr_tst_go = 1 ;     // Включаем режим "Контроль Пробоя Тиристоров" .
            //---
            // Ждём пока ИУ станут в 179 грд по ЗИ Угла .
            if ( S.Alfa_Old  >= _Grad( 179 )
  #ifdef   _SIFU2_
              && S2.Alfa_Old >= _Grad( 179 )
  #endif
                                             )
            {
               // Сюда должен быть однократный вход :
               Otkl_Imp  = 0x0 ;            // Включаем ИУ для теста .
            }
        }
    }
    //---
    // Включен режим контроля , контроль запущен и флаги окончания теста не выставлены :
    if (  _r.Cfg2._.ProboyTir == 1 && flg_RaTe._.tyr_tst_go == 1 &&
        flg_RaTe._.tyr_tst_ok == 0 && flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0 )
    {
       // Измеряем токи по модулю - ток с трансформаторов тока должен превышать Уставку и при этом , в случае ,
       // если собрана цепь нагрузки , то тока в нагрузке не должно быть :
       // 12.07.2017 13:00 - DAN : При контроле тока выше 30% , не хватало тока для определения пробоя тиристора .
       //                          Уменьшение уставки тока до 20 % для определения пробоя , согласовано с Шестаковым .
       // 30.08.2017 13:45 - DAN : Шестаков заказал уставку для контроля пробоя тиристоров , т.к. при испытаниях наша
       //                          маломощная сеть не даёт даже 20 % тока на 150 грд...
       if ( Iproboy1 > _r.Id_tst_proboy // 17.09.2021 - 0.05, т.к. при 0.20 "пик" тока затягивается на следующий тиристор .
   #ifndef  _Id_on_Itt_for_ProboyTir // Ток в нагрузке проверяем если ОС РТ - это НЕ ток с Трансформаторов Тока :
                                        && IDV < _Id_nom(0.05)
   #else
     #ifdef  Id_sum_ach              // Если суммарный шунт есть , но РТ замкнут не по нему :
                                        && (sw)Id_sum < (sw)_Id_nom(0.10) && (sw)Id_sum > (sw)_Id_nom(-0.10)
     #endif
   #endif
            )
       {
        // Определение пробоя в каждом из двух ШС в каждом мосту :
        #if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )
          if      ( (sb)n == 1 || (sb)n == 4 )
          {
            if        ( IA1 > _r.Id_tst_proboy )   lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
            else /*if ( IA2 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM2_VT11_24 << (n-1) ;
          }
          else if ( (sb)n == 2 || (sb)n == 5 )
          {
            if        ( IC1 > _r.Id_tst_proboy )   lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
            else /*if ( IC2 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM2_VT11_24 << (n-1) ;
          }
          else //if ( (sb)n == 3 || (sb)n == 6 )
          {
            if        ( IB1 > _r.Id_tst_proboy )   lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
            else /*if ( IB2 > _r.Id_tst_proboy )*/ lax = _Pr2_ProbM2_VT11_24 << (n-1) ;
          }
        #else
        // Если в каждом мосту по одному ШС , то рассчитываем пробитый тиристор , даже если есть все три фазных тока одного ШС :
          lax = _Pr2_ProbM1_VT11_24 << (n-1) ;
        #endif
          mSet_PreduprMsg2( lax ) ;             // Предупредительное сообщение о пробитом .
          flg_RaTe._.tyr_tst_pr = 1 ;           // Выставляем флаг окончания теста - тиристор пробит .
       }
       //---
       i++ ; // количество проходов теста .
       //---
       // После каждого из 6 проходов ( 1 период , 20 мс ) уменьшаем угол на 1 эл.грд. :
       if ( i % 6 == 0 )
       {
         S.Alfa -= _Grad( 1 ) ;        // Уменьшаем угол управления .
  #ifdef   _SIFU2_
         S2.Alfa -= _Grad( 1 ) ;       // Уменьшаем угол управления .
  #endif
         //---
         // 12.07.2017 13:00 - DAN : При уменьшении угла до 160 грд не хватало тока для определения пробоя тиристора .
         //                          Уменьшение угла согласовано с Шестаковым .
         // Тест "дощёлкал" до конца :
         if ( S.Alfa < _Grad( 150 ) )  // Подразумеваем , что и S2.Alfa < _Grad( 160 ) ...
         {
           flg_RaTe._.tyr_tst_ok = 1 ; // Выставляем флаг окончания теста - тиристоры в порядке .
         }
       }
       //---
       // ВОЗМОЖНО здесь стоит проверять все аварии и предупреждения , возникшие во время теста ...
       // Если Импульсы не снялись , или не сдвинулись по Геркону , или просто не сработали Герконы , Id-max
       // или РДШ - выставляем флаг успешного окончания теста для входа в работу :
       if ( /*Otkl_Imp != 0x0  ||*/ Av._.Sdvig_imp != 0  || bo_Avar != 0         ||
            Av._.Gercon != 0     || Av._.GerconDC != 0   || Av2._.RV1 != 0       ||
            Av2._.GerconAC2 != 0 || Av2._.GerconAC3 != 0 || Av2._.GerconAC4 != 0 ||
            Av._.Id_max != 0     || Av._.Id2_max == 1 )
       {
           flg_RaTe._.tyr_tst_av = 1 ;           // Выставляем флаг окончания теста - сработала токовая защита .
       }
    }
    else i= 0 ; // обнуляем счётчик проходов теста .
    //----------------

    // Возвращаем все значения назад по окончании Теста в следующих случаях :
    // 1. Кто-то отключил программу тестирования "Контроль Пробоя Тиристоров" прямо при её работе .
    // 2. Программа завершилась , при этом ИУ снялись по Геркону , Id-max , РДШ и т.п. ...
    // 3. Программа завершилась , пробоя не обнаружено .
    // 4. Программа завершилась , пробой обнаружен .
    //---
    // Возможно , здесь еще нужно проверить второе СИФУ для 12-ти пульсных КТЭ .
    //---
    // Сюда должен быть однократный вход !
    if ( flg_RaTe._.tyr_tst_go == 1 && ( _r.Cfg2._.ProboyTir == 0 || flg_RaTe._.tyr_tst_av == 1 ||
                                       flg_RaTe._.tyr_tst_ok == 1 || flg_RaTe._.tyr_tst_pr == 1 ) )
    {
        mOtkl_Imp( _VR1_imp ) ;          // Отключаем ИУ .
        S.Alfa = _r.S_Alfa_Start ;       // Инициализируем Альфа .
      //S.Alfa_Old = _r.S_Alfa_Start ;   // 10.12.2019 - НЕЛЬЗЯ Инициализировать выход ЗИ Альфа - чтобы не сбить контроль перепривязки синхронизации .
  #ifdef   _SIFU2_
        S2.Alfa = _r.S_Alfa_Start ;      // Возвращаем сохранённое значение Альфа .
      //S2.Alfa_Old = _r.S_Alfa_Start ;  // 10.12.2019 - НЕЛЬЗЯ Инициализировать выход ЗИ Альфа - чтобы не сбить контроль перепривязки синхронизации .
  #endif
        Prg.all &= ~_Sled ;              // Отключаем След для сохранения картинки Теста на пробитие , однако
                                         // он автоматически включится через 5 минут .
        //---
        flg_RaTe._.tyr_tst_go = 0 ;      // При отключении тестирования снимаем флаг "тестирование в процессе" .
    }
    //---
    // При отключении программы тестирования "Контроль Пробоя Тиристоров" сбрасываем все флаги :
    if ( _r.Cfg2._.ProboyTir == 0 )
    {
      flg_RaTe._.tyr_tst_ok = 0 ;
      flg_RaTe._.tyr_tst_pr = 0 ;
      flg_RaTe._.tyr_tst_av = 0 ;
    }
    //---
    // Флаги аварийного отключения , которые сработали при работе программы тестирования "Контроль Пробоя Тиристоров"
    // сбрасываются по Дистанционному Сбросу , после этого повторно производится тестирование тиристоров ,
    // если оно включено ...
    //---
    // Был вход в Работу после удачного теста на пробитие . Сбрасываем флаги удачного теста , тем самым
    // готовимся к следующему тесту при следующем вхождении в Работу :
    if ( Prg._.Gotovn == 0 && flg_RaTe._.tyr_tst_ok == 1 )
    {
      flg_RaTe._.tyr_tst_ok = 0 ;
    }
#endif

    //---------------------------------------------------------------------------------------------------------------

    // 21.12.2013 12:56
    // Защита на случай зависания фона (например, как в Березниках), когда теряется синхронизация (выполняется в фоне)
    // и,как следствие, "плывут" импульсы, а всё, что делается чуть выше (сдвиг, отключение Q2 (Q1),
    // которого физически может и не быть, установка аварийных сообщений из-за зависшего фона не
    // переводит систему в аварию) не отключает агрегат.
    if( Av._.Id_max == 0 )
    {
        Idmax2 = 0;
        time_Id_max2 = Puls_counter;
    }
    else
    {
            // Ожидаем снятие импульсов фоновой программой, и если этого не происходит,
            // снимаем импульсы, готовность и включаем аварию.
            // Переводим уставку из Timer1_Ovr в Puls_counter.
        ax = _r.Time_do_OtklImp * (_pSec( 1.0 ) / _Sec( 1.0 )) + _pSec( 0.2 );
        if( ( ( (u)((w)(Puls_counter - time_Id_max2)) > ax ) && ( Otkl_Imp != _Avar_imp ) ) )  Idmax2 = 1; // для защёлки

            //----------

        if( IDV >= _r.Id_Max
#ifndef _KTE_GD
    #ifdef _RVId
          || RVId.IDV1 >= _r.Id_Max || RVId.IDV2 >= _r.Id_Max
    #endif
#endif
          )
        {        // Если ток не падает, значит сдвиг импульсов не помогает и дальше ждать нечего
            if ( (u)((w)(Puls_counter - time_Id_max2)) > _pSec( 0.05 ) )    Idmax2 = 1; // для защёлки
        }

            //----------

        if ( Idmax2 == 1 )
        {
                mOtkl_Imp( _Avar_imp ) ;
                bo_Avar = 1 ;
                bo_Gotov = 0 ;
                bo_canAvar = 1 ;
                bo_canGotov = 0 ;
        #ifdef _ATK_SET
                bo_SA_canGotov = 0 ; //DAN 12.04.2025
                bo_SA_canAvar = 1 //DAN 12.04.2025
                bo_atkAvar = 1 ;
                bo_atkGotov = 0 ;
                bo_AvarATK = 1 ;
                bo_GotovATK = 0 ;
         #ifdef bo_Avar_Yach
                bo_Avar_Yach = 1 ;
                bo_AvarYacheykaATK = 1 ;
         #endif
        #endif
        #ifdef _POWER
                bo_MB1_Razr = 0 ;
        #endif

          #ifdef _KTE_GD
                bo_Vkl_LK = 0 ;
          #else
                bo_Vkl_QK1 = 0 ;
        #endif

#ifndef  _Adc_Extend_Po0 // Если Порт 0 не используется для управления внешним мультиплексором АЦП :
                Port_output (); // Централизованная выдача внешних сигналов.
#else
                // Номер выборки и номер порта , в котором находятся Авария , Готовность , Предупреждение :
                S400_output ( _or.AS_CSo[_AsPo_Av_Pr_Got_] , _AsPo_Av_Pr_Got_);
#endif
        }
    }

    return;
  }

#endif
//----------------------------------------------

void Control_E_Max (void)
  {
    if ( ( EDS & 0x7fff ) > _r.E_Max )  //  Контроль максимальной ЭДС.
      {
        if ( Av._.Emax == 1 ) // проверка повторности превышения.
          {
            mSet_AvarMsg( _Av_Emax ) ; // превышение было дважды подряд.
          }
        else  Av._.Emax = 1  ; // регистрация первого превышения.
      }
    else  Av._.Emax = 0  ; // превышение было одиночное.

    return;
  }
//----------------------------------------------

void Control_N_Max (void)
  {
    if ( (sw)Skor > (sw)_r.N_Max || (sw)Skor < (sw)( ~_r.N_Max + 1 ))
          {
            if ( Av._.Nmax == 1 ) // проверка повторности превышения.
              {
                mSet_AvarMsg( _Av_Nmax ) ; // превышение было дважды подряд.
              }
            else  Av._.Nmax = 1  ; // регистрация первого превышения.
          }
        else  Av._.Nmax = 0  ; // превышение было одиночное.
    return;
  }
//----------------------------------------------
#ifdef _KTE_GD
//------
void Control_Ig_Ug_Max (void)
  {
  if ( IDV_g > _r.Ig_Max )   mSet_AvarMsg( _Av_Ig_max ) ;
#ifdef _RVId
  if ( IDV1  > _r.Ig_Max ) mSet_AvarMsg2 ( _Av2_Id1Max ) ;
  if ( IDV2  > _r.Ig_Max ) mSet_AvarMsg2 ( _Av2_Id2Max ) ;
#endif

  //    компилятор заменял на следующее:
  //1.ax = Ugen ;                    =>  ax = Ugen
  //2.if ( (sw)ax < 0 ) ax = ~ax+1 ; =>  if ( (sw)Ugen < 0 ) ax = ~ax+1 ;
  //    при этом если прерывание влазило между 1. и 2. и Ugen изменялось с
  // +1 на -1, то +1 в ax инвертировалось в 0xFFFF и ложно срабатывала защита.
  //3.if ( ax > _r.Ug_Max )
  //     Чтобы компилятор делал все как надо, нужно добавить 'volatile'.
  //1.ax = (volatile)Ugen ;

  if ( (sw)Ugen > (sw)_r.Ug_Max || (sw)Ugen < (sw)( ~_r.Ug_Max + 1))
  {
    mSet_AvarMsg ( _Av_Ug_max )  ;
  }
    return;
  }
//----------------------------------------------

void Control_Ug_Min (void)
  {
    static word time ;
        //  chtoby mozshno bylo blokir. zaschitu po polyrnosty.
    if ( IDV >= _Id_nom( 0.25 ) && _r.Ug_Min != 0 )
    {
      // Если при токе возбуждения генератора ( по модулю ) большем чем 25% :
      // 1. Напряжение генератора меньше минимального в течении 500мс -> Авария .
      // 2. Ток возбуждения и напряжение генератора разных знаков     -> Авария .
      if ( (sw)Ugen < (sw)_r.Ug_Min && (sw)Ugen > (sw)( ~_r.Ug_Min + 1))
      {
        if ((u)((w)(Timer1_Ovr - time)) > _Sec(0.5)) mSet_AvarMsg( _Av_Ug_min );
      }
      else
      {       // proverka polyarnosty Ug: если ток и напряжение разных знаков...
        if ( ( (sw)Id_dop_kod > 0 && (sw)Ugen < 0 )
                                  ||
             ( (sw)Id_dop_kod < 0 && (sw)Ugen > 0 )) mSet_AvarMsg2 ( _Av2_Ug_polyarn )  ;
        else time = Timer1_Ovr ;
      }
    }
    else time = Timer1_Ovr ;
    return;
  }
//----------------------------------------------

void Control_Id_Min (void)
  {
    static word time ;

    if ( S.Alfa_Old <= _r.S_Alfa_Min && IDV < _r.Id_short_imp )
    {
      if ( (u)((w)(Timer1_Ovr - time)) > _Sec(1.0) ) mSet_AvarMsg( _Av_Id_min );
    }
    else time = Timer1_Ovr ;
    return;
  }
//----------------------------------------------

  // Контроль остаточного намагничивания генератора .
  // Введено в цепь формирования разрешения включения ЛК в якорной цепи во
  // избежание включения ЛК , если РН еще не задавил остаточное напряжение .
word Control_UgOstat ( void )
{
  word ah ;
  ah = 0 ;
 // chtoby mozshno bylo blokir. zaschitu .
 if ( _r.UgOstat != 0 )
 {
  if ( (sw)Ugen > (sw)(  (w)_r.UgOstat ) ||
       (sw)Ugen < (sw)( ~(w)_r.UgOstat + 1 ) )
    {
      mSet_PreduprMsg( _Pr_UgOstat ) ;
      ah = 1 ;
    }
  else mClr_PreduprMsg( _Pr_UgOstat ) ; // Самоочистка, чтобы не осталось
 }                                      // старое предупреждение в "Работе" .
 return ah ;
}

//------
#endif
//----------------------------------------------

void Control_Power_Circuit (void)
  {
     // Защита , контролирующая целостность силовой цепи и наличие напряжения .
    //----
     // При включенном РТ , модуле тока меньшем "Id-мин" и  модуле выхода РС ,
     // большем ("Id-мин"+10%Idном) , срабатывает через выдержку времени 1.0с .
    //----
     //   В RT.C переменная "ZIDN" ЗИРТ , в которую записывается ограниченный
     //   токовой отсечкой модуль выхода РС , при отсутствии тока в цепи
     //   ограничивается уставкой гранично-непрерывного тока , а посему вместо
     //   этой переменной лучше использовать модуль выхода РС .
    static word time ;
           word ax ;

     // защита блокируется уменьшением "Id-мин" до нуля .
    ax = (volatile word)OuRegS ;  // в ГД 'OuRegS' - знаковый.
    if ( (sw)ax < 0 ) ax = ~ax+1 ; // (volatile) чтобы компилятор не оптимизировал.

    if ( Prg._.RegTok == 1 &&
#ifndef _KTE_GD
     ( ( S.Disable == 0 && IDV   < _r.Id_Min && ax > (w)(_r.Id_Min + _Id_nom( 0.1 )) )
 #ifdef _SIFU2_
    // DAN 23.05.2017 14:46 - При работе только ШС2 :
    || ( S.Disable == 1 && IDV2  < _r.Id_Min && ax > (w)(_r.Id_Min + _Id_nom( 0.1 )) )
 #endif
                                                                                       ) )
#else
       IDV_g < _r.Id_Min && ax > (w)(_r.Id_Min + _Ig_nom( 0.1 )) )
#endif
     {
       if ( (u)((w)(Timer1_fSec-time)) > _r.T_Circuit )
        {
          mSet_AvarMsg( _Av_DC_Circuit ) ;
        }
     }
    else time = Timer1_fSec ;

    return;
  }
//----------------------------------------------

 // Контроль датчика скорости ( ТГ или ПДФ ) по рассчетной скорости .
 // Рассчетная скорость Izm_Skor_EDS () находится :
 //    - для  I-зонной структуры по ЭДС ;
 //    - для II-зонной структуры по классической формуле E=CeФn => n=E/CeФ .
 // Авария "Неисправность ДС" отрабатывается в случае , если отклонение
 // рассчетной скорости от фактической превышает допустимое в течении
 // выдержки времени .
void Control_DatSkor ( void )
{
  static word time ;
  register word ax, bx ;

#ifndef _ATK_SET
  // Если нет ДС или РС отключён , выходим не проверяя защиту :
  if ( (_r.Sk_str._.TG == 0 && _r.Sk_str._.PDF == 0) || Prg._.RegSk == 0 ) return ;

  //---// Находим модули ЭДС и скорости :
  ax = Skor_r ;
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "|Nрасч|" - модуль рассчетной скорости .
  bx = Skor ;
  if ( (sw)bx < 0 ) bx = ~bx + 1 ; // "|N|" - модуль скорости .

  //---  Проверяем исправность ДС :
  ax -= bx ; // Отклонение рассчетной скорости от фактической .
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "| |Nр|-|N| |" - модуль отклонения .
  if ( ax > _r.dN_Max )
   {
     if ( (u)((w)(Timer1_Ovr-time)) > _Sec(0.15) )
     {
#ifndef _Perecl_DS
       mSet_AvarMsg( _Av_dN_Max ) ;       // При неисправности ДС - аварийное отключение .
#else
       mSet_PreduprMsg( _Pr_Perecl_DS ) ; // При неисправности ДС - переключение на ЭДС .
       _r.Sk_str._.TG = 0 , _r.Sk_str._.PDF = 0 ; // Отключение ТГ и ПДФ .
       _r.Sk_str._.EDS = 1 ;                      // Включение ЭДС .
#endif
     }
   }
  else time = Timer1_Ovr ;

#else // Для АТК :

  // Если нет ПДФ , или РС отключён , или Пуска нет , или ротор зашунтирован - выходим не проверяя защиту :
  // 29.06.2022 - Убрал выход из проверки защиты при включенном шунтировании ротора , т.к. в этом
  //              режиме скорость что по энкодеру , что по ШИМ-измерениям должна быть номинальной :
  if ( _r.Sk_str._.PDF == 0 || Prg._.RegSk == 0 || ATK_flg._.trig_Pusk == 0 /*|| flgO._.Shunt_Rot == 1*/ )
  {
     time = Timer1_Ovr ;
     return ;
  }

  //---// Находим модули ЭДС и скорости :
  ax = N_rot ;
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "|N_rot|" - модуль рассчетной скорости по ШИМ .
  bx = Skor ;
  if ( (sw)bx < 0 ) bx = ~bx + 1 ; // "|N|" - модуль скорости по ПДФ .

  //---  Проверяем исправность ДС :
  ax -= bx ; // Отклонение рассчетной скорости от фактической .
  if ( (sw)ax < 0 ) ax = ~ax + 1 ; // "| |Nр|-|N| |" - модуль отклонения .
  if ( ax > _r.dN_Max )
   {
     // 30.05.2021 - увеличил время выдержки для аварии по неисправности ДС , т.к. при выдержке _Sec(0.15) ,
     // при включении с выбитой ячейкой реверсора ( без силового напряжения на роторе N по шим = 100% ) ,
     // определяется Неисправность ДС до того , как ШУ ШПМ по отсутствию тока определит отсутствие напряжения
     // на статоре ( то есть не включенный реверсор ) .
     if ( (u)((w)(Timer1_Ovr-time)) > _or.T_dN_Max ) //_Sec(1.5) ) // _Sec(0.15) )
     {
#ifndef _Perecl_DS
       mSet_AvarMsg( _Av_dN_Max ) ;       // При неисправности ДС - аварийное отключение .
#else
       mSet_PreduprMsg( _Pr_Perecl_DS ) ; // При неисправности ДС - переключение на ЭДС .
       _r.Sk_str._.PDF = 0 ;              // Отключение ПДФ .
       _r.Sk_str._.EDS = 1 ;              // Включение скорости по ШИМ .
#endif
     }
   }
  else time = Timer1_Ovr ;

#endif

  return;
}
//----------------------------------------------
//
//    Программа контроля стоянки под током .

void  Control_Stoyanka ( void )
  {
    // Контроль , чтобы время Предупреждения не было больше , чем время Аварии :
    if ( (sw)_r.Stoyanka_Time_Predupr > (sw)_r.Stoyanka_Time ) _r.Stoyanka_Time_Predupr = (sw)_r.Stoyanka_Time ;
    //---
    if ( Prg._.Gotovn == 0 )
      {
   #ifndef _ATK_SET
        if ( ( EDS  & 0x7fff ) <= _r.Stoyanka_Eds  &&
#ifndef _KTE_GD
      ( (S.Disable == 0 && IDV >= _r.Stoyanka_Tok)
 #ifdef _SIFU2_                                    // DAN 23.05.2017 14:46 - При работе только ШС2 :
                                                   || (S.Disable == 1 && IDV2 >= _r.Stoyanka_Tok)
 #endif
                                                                                                  ) )
#else
                           IDV_g >= _r.Stoyanka_Tok  )
#endif
   #else
      //if ( ( Skor & 0x7fff ) <= _r.Stoyanka_Eds && Id_flt.out >= _r.Stoyanka_Tok  ) // 17.06.2021 - решил не фильтровать ток .
        if ( ( Skor & 0x7fff ) <= _r.Stoyanka_Eds && IDV >= _r.Stoyanka_Tok  )
   #endif
          {   //  Задержка на фильтрацию кратковременных "стоянок"
              // при старте или набросе нагрузки - временной порог входа
              // в режим стоянки.
            if ( (u)Stoyanka_Timer <= _r.Stoyanka_Time_Predupr ) goto b1 ; // 05.04.2011 -  По многочисленным жалобам увеличено ... _Sec(1.0) _Sec(0.2)
              // Порог входа в стоянку перейден - отсчет задержки стоянки .
            if ( (u)Stoyanka_Timer >= _r.Stoyanka_Time )
              {
                mSet_AvarMsg( _Av_Stoyanka ) ;
                mClr_PreduprMsg( _Pr_Stoyanka ) ;
              }
            else
              {
                mSet_PreduprMsg( _Pr_Stoyanka ) ;
           b1:  Stoyanka_Timer += Timer1_Ovr - Stoyanka_Time ;
              }
          }
        else if ( (u)Stoyanka_Timer <= _r.Stoyanka_Time_Predupr ) // 05.04.2011 -  По многочисленным жалобам увеличено ... _Sec(1.0) _Sec(0.2)
                  Stoyanka_Timer = 0 ; // Стоянка прекратилась так и
                                      // не перейдя свой временной порог.
             else  goto a1 ; //  Для того чтобы после выхода из режима стоянки
      }                     // дать остыть агрегату, и не дать включить его
    else                   //  на новую, полную N-минутную выдержку.
      {
  a1:   Stoyanka_Timer -= Timer1_Ovr - Stoyanka_Time ;
        if ( (sw)Stoyanka_Timer <= 0 ) Stoyanka_Timer = 0 ;
      }

    Stoyanka_Time = Timer1_Ovr ;

    return  ;
  }
//----------------------------------------------

  void  Control_Predohr ( void ) // Контроль предохранителей .
       {
         //Контроль предохранителя Выходных Каскадов :
      #ifdef  bi_KF_VKask
         //DAN 10.07.2017 10:44 - Предохранитель на плате Выходных Каскадов стоит таким образом , что при перегорании
         //                       форсировка продолжает идти . Форсировки достаточно , чтобы открыть тиристор ...
         //                       Однако сида тока через управляющий переход в таком случае очень мала и это сокращает
         //                       срок жизни тиристора . Выход - Авария вместо Предупреждения . Согласовано с Шестаковым ...
         if ( bi_KF_VKask == 0 )  mSet_AvarMsg2 ( _Av2_KF_VKask ) ;
       //if ( bi_KF_VKask == 0 )  mSet_PreduprMsg( _Pr_KF_VKask ) ; DAN 10.07.2017 10:44
      #endif

      // Для ШС2 в 12-пульсном СИФУ :
      #ifdef  bi_KF_VKask2
         // Контроль предохранителя Выходных Каскадов платы Ведомого Моста :
         //DAN 10.07.2017 10:44 - Предохранитель на плате Выходных Каскадов стоит таким образом , что при перегорании
         //                       форсировка продолжает идти . Форсировки достаточно , чтобы открыть тиристор ...
         //                       Однако сида тока через управляющий переход в таком случае очень мала и это сокращает
         //                       срок жизни тиристора . Выход - Авария вместо Предупреждения . Согласовано с Шестаковым ...
         if ( bi_KF_VKask2 == 0 )  mSet_AvarMsg2 ( _Av2_KF_VKask2 ) ;
       //if ( bi_KF_VKask2 == 0 )  mSet_PreduprMsg2( _Pr2_KF_VKask2 ) ; DAN 10.07.2017 10:44
      #endif

      // Для ШС3 в 12-пульсном СИФУ :
      #ifdef  bi_KF_VKask3
         if ( bi_KF_VKask3 == 0 )  mSet_AvarMsg3 ( _Av3_KF_VKask3 ) ;
      #endif

      // Для ШС4 в 12-пульсном СИФУ :
      #ifdef  bi_KF_VKask4
         if ( bi_KF_VKask4 == 0 )  mSet_AvarMsg3 ( _Av3_KF_VKask4 ) ;
      #endif

          // Контроль предохранителя Выходных Каскадов Возбудителя
      #ifdef  _Vozb_KTE
         //DAN 10.07.2017 10:44 - Предохранитель на плате Выходных Каскадов стоит таким образом , что при перегорании
         //                       форсировка продолжает идти . Форсировки достаточно , чтобы открыть тиристор ...
         //                       Однако сида тока через управляющий переход в таком случае очень мала и это сокращает
         //                       срок жизни тиристора . Выход - Авария вместо Предупреждения . Согласовано с Шестаковым ...
         // На плате 407 есть форсировка . Нет форсировки только на В16 , плата 338 ...
         if ( bi_KFV_VKask == 0 )  mSet_AvarMsg2 ( _Av2_KFV_VKask ) ;
       //if ( bi_KFV_VKask == 0 )  mSet_PreduprMsg( _Pr_KFV_VKask ) ; DAN 10.07.2017 10:44
      #endif

          // Контроль питания Усилителей Импульсов Выходных Каскадов осуществляется только при поданных импульсах :
      #ifdef  bi_KP
         // 12.12.2013 9:00 - В связи с так и не понятыми срабатываниями этой аварии на Запорожстали , Шестаков
         // порекомендовал не контролировать этот сигнал во время реверса , хотя я не думаю , что дело в этом .
         // 23.03.2016 15:19 - Контролируем также и нахождение в Работе , т.к. есть режимы с ИУ не в работе ,
         // например "Контроль Пробития Тиристоров" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0
#if !(defined(_SIFU2_) && defined(bi_KP2))                                // 06.05.2019 - Если в 6-пульсном КТЭ стоят 2 платы выходных
                                                      && S.NumMost == 1   //              каскадов : Вперед и Назад . Контролируем
#endif                                                                    //              только одну плату - рабочую в данный момент .
                                                                        ) // Если появились ИУ ,
         {
           if ( bi_KP == 0 ) // Сработал контроль питания :
           {
             // и прошла выдержка :
             if ((u)((w)(Timer1_Ovr - Time_KP)) > _Sec(0.5))  mSet_AvarMsg2 ( _Av2_KP ) ;
           }
           else Time_KP = Timer1_Ovr ;
         }
         else   Time_KP = Timer1_Ovr ;
      #endif

         // Для ШС2 в 12-пульсном СИФУ :
         // Контроль питания Усилителей Импульсов Выходных Каскадов осуществляется только при поданных импульсах :
      #ifdef  bi_KP2
         // 12.12.2013 9:00 - В связи с так и не понятыми срабатываниями этой аварии на Запорожстали , Шестаков
         // порекомендовал не контролировать этот сигнал во время реверса , хотя я не думаю , что дело в этом .
         // 23.03.2016 15:19 - Контролируем также и нахождение в Работе , т.к. есть режимы с ИУ не в работе ,
         // например "Контроль Пробития Тиристоров" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0
         // 06.05.2019 - В случае , если КТЭ нереверсивный и 2 платы выходных каскадов стоят в двух
         //              силовых шкафах Моста Вперед , необходимо еще доработать этот алгоритм ...
#if !(defined(_SIFU2_) && defined(bi_KP))                                 // 06.05.2019 - Если в 6-пульсном КТЭ стоят 2 платы выходных
                                                      && S.NumMost == 2   //              каскадов : Вперед и Назад . Контролируем
#endif                                                                    //              только одну плату - рабочую в данный момент .
                                                                        ) // Если появились ИУ ,
         {
           if ( bi_KP2 == 0 ) // Сработал контроль питания :
           {
             // и прошла выдержка :
             if ((u)((w)(Timer1_Ovr - Time_KP2)) > _Sec(0.5)) mSet_AvarMsg2 ( _Av2_KP2 ) ;
           }
           else Time_KP2 = Timer1_Ovr ;
         }
         else   Time_KP2 = Timer1_Ovr ;
      #endif

         // Для ШС3 в 12-пульсном СИФУ :
         // Контроль питания Усилителей Импульсов Выходных Каскадов осуществляется только при поданных импульсах :
      #ifdef  bi_KP3
         // 12.12.2013 9:00 - В связи с так и не понятыми срабатываниями этой аварии на Запорожстали , Шестаков
         // порекомендовал не контролировать этот сигнал во время реверса , хотя я не думаю , что дело в этом .
         // 23.03.2016 15:19 - Контролируем также и нахождение в Работе , т.к. есть режимы с ИУ не в работе ,
         // например "Контроль Пробития Тиристоров" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0 ) // Если появились ИУ ,
         {
           if ( bi_KP3 == 0 ) // Сработал контроль питания :
           {
             // и прошла выдержка :
             if ((u)((w)(Timer1_Ovr - Time_KP3)) > _Sec(0.5)) mSet_AvarMsg3 ( _Av3_KP3 ) ;
           }
           else Time_KP3 = Timer1_Ovr ;
         }
         else   Time_KP3 = Timer1_Ovr ;
      #endif

         // Для ШС4 в 12-пульсном СИФУ :
         // Контроль питания Усилителей Импульсов Выходных Каскадов осуществляется только при поданных импульсах :
      #ifdef  bi_KP4
         // 12.12.2013 9:00 - В связи с так и не понятыми срабатываниями этой аварии на Запорожстали , Шестаков
         // порекомендовал не контролировать этот сигнал во время реверса , хотя я не думаю , что дело в этом .
         // 23.03.2016 15:19 - Контролируем также и нахождение в Работе , т.к. есть режимы с ИУ не в работе ,
         // например "Контроль Пробития Тиристоров" .
         if ( Prg._.Gotovn == 0 && Otkl_Imp == 0 && S.flg._.Revers == 0 ) // Если появились ИУ ,
         {
           if ( bi_KP4 == 0 ) // Сработал контроль питания :
           {
             // и прошла выдержка :
             if ((u)((w)(Timer1_Ovr - Time_KP4)) > _Sec(0.5)) mSet_AvarMsg3 ( _Av3_KP4 ) ;
           }
           else Time_KP4 = Timer1_Ovr ;
         }
         else   Time_KP4 = Timer1_Ovr ;
      #endif

        return ;
       }
//----------------------------------------------

#ifdef bi_PT
  void  Control_PT ( void ) // Контроль перегрева тиристоров .
       {
          //---
            //  "Предупреждение - перегрев."
          if ( bi_PT == 0 )
            {
              mSet_PreduprMsg2( _Pr2_PT ) ;
  //-------
  //-------------------- Если охлаждение включается автоматически по перегреву --------------------
  #ifdef bo_Vkl_Vent
              bo_Vkl_Vent = 1 ;  // включение вентиляторов .
              Time_t_tir = Timer1_Ovr ;
            }
          else if ( bo_Vkl_Vent == 1 ) // Если перегрева уже нет , но вентиляторы уже включены ,
            { // держим их включенными еще 10 мин , или пока кто-то не сбросит их "дист.сбросом" :
              if ( (u)((w)(Timer1_Ovr - Time_t_tir)) > _r.Time_otkl_BV1 || Av._.DistSbros == 1 )
                {    // через выдержку
                  bo_Vkl_Vent = 0 ; // отключение вентиляторов
                  mClr_PreduprMsg2( _Pr2_PT ) ;
                }
  #endif
  //-----------------------------------------------------------------------------------------------
            }
        return ;
       }
#endif

// Для ШС2 в 12-пульсном СИФУ :
#ifdef bi_PT2
  void  Control_PT2 ( void ) // Контроль перегрева тиристоров .
       {
          //---
            //  "Предупреждение - перегрев."
          if ( bi_PT2 == 0 )
            {
              mSet_PreduprMsg2( _Pr2_PT2 ) ;
  //-------
  //-------------------- Если охлаждение включается автоматически по перегреву --------------------
  #ifdef bo_Vkl_Vent2
              bo_Vkl_Vent2 = 1 ;  // включение вентиляторов .
              Time_t_tir2 = Timer1_Ovr ;
            }
          else if ( bo_Vkl_Vent2 == 1 ) // Если перегрева уже нет , но вентиляторы уже включены ,
            { // держим их включенными еще 10 мин , или пока кто-то не сбросит их "дист.сбросом" :
              if ( (u)((w)(Timer1_Ovr - Time_t_tir2)) > _r.Time_otkl_BV1 || Av._.DistSbros == 1 )
                {    // через выдержку
                  bo_Vkl_Vent2 = 0 ; // отключение вентиляторов
                  mClr_PreduprMsg2( _Pr2_PT2 ) ;
                }
  #endif
  //-----------------------------------------------------------------------------------------------
            }
        return ;
       }
#endif

//-------------------------------------------------------------------------------------------------
//
//      Измерение температуры тр-ра.
//
//    Весь диапазон датчика - 250 грдС . Поэтому типовые уставки 4мА =-50грдС , 20мА =+200грдС .
//                                                           Или 4мА = 0грдС  , 20мА =+250грдС .
//
//    При обрыве датчика ( 0мА ) индицируется температура , соответствующая 4мА , т.е. не падает
// ниже уставки . Но зато при обрыве срабатывает сообщение о превышении температуры . Сообщение
// в целях экономии - одно .
//
//    Настройка этой платы :
//  |------|---------|-----------------|
//  |  мА  |  В, АЦП | грд, -50...+200 |
//  |------|---------|-----------------|
//  |   0  |    0    |      -50        |
//  |   4  |   0.77  |      -50        |
//  |  12  |   2.33  |      +75        |
//  |  20  |   3.89  |      +200       |
//  ------------------------------------
//
void  Contr_Ttrans_4_20 ( word num )
{
//---
#ifndef  Ttrans_ach
//---
  num = num,  Ttrans = 0, Ttrans_4_20 = 0 ;
//---
#else
//---
  static word Ttrans_full, time_Ttr, Ttrans_4_20_drob, time_scan ;

  register word ax ;
  register lword lax ;

  switch ( num )
  {      //  Стартовая инициализация.
    case 0 :  Ttrans = 0, Ttrans_4_20 = 0, time_Ttr = Timer1_Ovr, Ttrans_4_20_drob = 0 ;

     start: Ttrans_full = _AD_BUSY ;  //  запуск первого измерения изоляции
            AD_Izm ( Ttrans_ach, &Ttrans_full ) ;
      break;
         //  Рабочая программа.
    case 1 :
          if ( (w)(u)(timer1-time_scan) >= _MkSec(10*1000) )
          {
            time_scan = timer1 ;
            //---

            if ( Ttrans_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Ttrans_full, ax, Ttrans_ach ) ;

                 //---   Фильтруем, т.к. на Белой Церкви на 4-20мА были пульсации 200Гц с амплитудой до 15%.
                     //  Лобода ВД предполагал, что это пульсации ШИМ-регулятора в источнике блока формирующего 4-20.
               lax  = (lw)Ttrans_4_20 << 16,    lax += (lw)(w)Ttrans_4_20_drob ;
                 lax += (slw)( ((lw)ax << 16) - lax ) / (sw)(_or.Filtr_Param * 2)  ;  // *2 - т.к. слишком глубокие пульсаци сигнала.
               Ttrans_4_20 = (w)( lax >> 16 ),   Ttrans_4_20_drob = (w)lax ;
                 //---

               ax = Ttrans_4_20 ;

               //                              Ttr_20mA(грд)-Ttr_4mA(грд)
               //     Ttrans = Ttr_4mA(грд) + ----------------------------  * (I-4mA)
               //                                         16mA

               ax -= _1mA_nom( 4 ) ;
               if ( (sw)ax <= 0 )  ax = 0 ;

               Ttrans = _or.Ttr_4mA + (w)( (lw)(w)(_or.Ttr_20mA - _or.Ttr_4mA ) * (lw)(sw)ax / _1mA_nom( 16 ) ) ;

            //--------------------

               goto start; //  запуск очередного измерения.
             }
          }
      break;

    case 2 :                                          // Защита от обрыва 4-20мА.
               if ( (sw)Ttrans >= (sw)_or.Ttr_predupr || (sw)Ttrans_4_20 <= (sw)_1mA_nom( 3 ) )
               {
                 if ( (u)(w)(Timer1_Ovr-time_Ttr) > _Sec( 1.0 ) )  mSet_PreduprMsg2( _Pr2_Ttr_predupr ) ;
               }
               else  time_Ttr = Timer1_Ovr ;

      break;
  }
//---
#endif
//---
  return ;
}

// Программа измерения температуры , за раз измеряется температура от одного датчика .
void T_Izm_Dat(  word num )
{
//---
 #ifndef _Dat_Temp_Max
//---
  num = num ;
//---
#else
//---
  double ax;//float ax;
  word i;
  //---
  switch ( num )
  {
    default :
    break ;

         //  Стартовая инициализация.
    case 0 :
               Counter_Izm_T = 0;  // Инициализация счетчика .

             // Для 2х силовых шкафов :
               Izm_Temp[0].ach =  &T0_ach;
               Izm_Temp[1].ach =  &T1_ach;
               Izm_Temp[2].ach =  &T2_ach;
               Izm_Temp[3].ach =  &T3_ach;
               Izm_Temp[4].ach =  &T4_ach;
               Izm_Temp[5].ach =  &T5_ach;
               Izm_Temp[6].ach =  &T6_ach;
               Izm_Temp[7].ach =  &T7_ach;
               Izm_Temp[8].ach =  &T8_ach;
               Izm_Temp[9].ach =  &T9_ach;
               Izm_Temp[10].ach = &T10_ach;
               Izm_Temp[11].ach = &T11_ach;

             // Для 4х силовых шкафов :
#if defined _Dat_Temp_Max == 24
               Izm_Temp[12].ach = &T12_ach;
               Izm_Temp[13].ach = &T13_ach;
               Izm_Temp[14].ach = &T14_ach;
               Izm_Temp[15].ach = &T15_ach;
               Izm_Temp[16].ach = &T16_ach;
               Izm_Temp[17].ach = &T17_ach;
               Izm_Temp[18].ach = &T18_ach;
               Izm_Temp[19].ach = &T19_ach;
               Izm_Temp[20].ach = &T20_ach;
               Izm_Temp[21].ach = &T21_ach;
               Izm_Temp[22].ach = &T22_ach;
               Izm_Temp[23].ach = &T23_ach;
#endif
               for (i = 0; i < _Dat_Temp_Max; i++)
               {
                  Izm_Temp[i].full = _AD_BUSY ;  // Инициализация для измерений каналов .
               }

               // Для выдачи наружу - температура и номер самого горячего охладителя .
               Hotest.Temperat = -2730 ; // Записываем нуль по Кельвину , чтобы правильно определять отрицательную температуру .
               Hotest.BKnumb   = 0 ;

               // Временная структура для определения температуры и номера самого горячего охладителя .
               Vrem.Temperat = -2730 ; // Записываем нуль по Кельвину , чтобы правильно определять отрицательную температуру .
               Vrem.BKnumb   = 0 ;

      break;

         //  Рабочая программа.
    case 1 :
     // Фон очень короткий , и для того , чтобы не преобразовать несколько раз одно и то же измерение , проверяем :
     if ( Izm_Temp[Counter_Izm_T].full != _AD_BUSY ) // Исли измерение в прерывании уже произошло :
     {
       if ( Counter_Izm_T == 0 )
       {
         // Самый горячий охладитель - перезапись из временной структуры  после проверки всей текущей серии измерений :
         Hotest.Temperat = Vrem.Temperat ; // Самая высокая температура .
         Hotest.BKnumb   = Vrem.BKnumb   ; // Номер охладителя .
         //---
         // Записываем во временную структуру первый охладитель , чтобы было с чего начать :
         Vrem.Temperat = Temper[Counter_Izm_T] ;
         Vrem.BKnumb   = Counter_Izm_T+1 ;       // Номер охладителя , с учетом нумерации с нуля .
       }
       //---
       pru = &Izm_Temp[Counter_Izm_T] ;
       mIzmData_Conversion( Izm_Temp[Counter_Izm_T].full , ax , *pru->ach ) ;

       Izm_Temp[Counter_Izm_T].full = _AD_BUSY ; // подготовка к следующему измерению этого канала .

       ax = (double)ax/(double)_AD_VOLT_DVUPOL;//(float)ax/(float)_AD_VOLT_DVUPOL;
       // ДТ выдаёт 1 В при 100 грд Кельвина .
       ax -= 2.73; // Перевод в грд Цельсисия ( 0 грд С = 273 грд К )
       //1000 - потому что 1 В = 100 грд , а формат 1 грд - 10 дискрет .
       ax = ax*1000*_or.T_Scale[Counter_Izm_T];

       Temper[Counter_Izm_T] = (sw)ax ; // А6 индикация у нас целочисленная , поэтому переводим плавающую точку в целые ...
     }

     // Если нет отдельно работающих силовых шкафов , то Name_Agr = 1 и выведутся все сообщения :
     // Вывод сообщений о перегреве только в работающих ШС :
     if ( ( Name_Agr == 2 && Counter_Izm_T <  (_Dat_Temp_Max/2) /*<= 11*/ ) || // только ведущий мост , 6-ти пульсная схема ,
          ( Name_Agr == 3 && Counter_Izm_T >= (_Dat_Temp_Max/2) /*>= 12*/ ) || // только ведомый мост , 6-ти пульсная схема ,
            Name_Agr == 1 )                                                    // оба моста, 12-ти пульсная схема :
     {
       // Проверка уровня температуры :
       if (Temper[Counter_Izm_T] >= _or.T_Av)
       {
         mSet_AvarMsg2 (_Av2_Izm_T ) ;
         mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
       }
       else if (Temper[Counter_Izm_T] >= _or.T_Pr )
       {
         mSet_PreduprMsg (_Pr_Izm_T ) ;
         mSet_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
       }
       else
       {
         mClr_ServiceMsg3 ((_Srv3_BK1<< Counter_Izm_T)) ;
       }

       // Определение самого Горячего Охладителя :
       if ( (sw)Temper[Counter_Izm_T] > (sw)Vrem.Temperat )
       {
         // Запись во временную структуру :
         Vrem.Temperat = Temper[Counter_Izm_T] ; // Самая высокая температура , из измеренных за текущую серию .
         Vrem.BKnumb   = Counter_Izm_T+1 ;       // Номер охладителя , с учетом нумерации с нуля .
       }
     }
      break;

         //  Зарядка измерения .
    case 2 :
        // Вставка в прерывание ...
        //---
        if ( Izm_Temp[Counter_Izm_T].full == _AD_BUSY ) // Предыдущее измерение обработано , и значит ,
        {                                               // заряжаем следующее измерение :
          // Каждый пульс измеряем один датчик температуры из 24-х :
          if (++Counter_Izm_T >= _Dat_Temp_Max)
          {
            Counter_Izm_T = 0;
          }
          // _AD_BUSY заряжен в фоне после обработки предыдущего измерения...
          pru = &Izm_Temp[Counter_Izm_T] ;
          // Заряжаем измерение , обработку делаем уже спокойно в фоне :
          mAD_Izm( *pru->ach, &Izm_Temp[Counter_Izm_T].full ) ;
        }
      break;
  }
//---
#endif
//---
  return ;
}

//---------------------------------------------
//    Контроль защит с выдержкой времени : предупреждение -> dt -> авария ,
//  если dt задать равной нулю, то авар.откл. блокируется .

void  Control_dt_Avar ( word code )
{
  static word time ;
  register word ax ;

  switch ( code )
  {
    case 0 :
//---
#ifdef bi_BV1 // Если определено автоматическое вкл/выкл вентиляторов , эту выдержку используем
       Timer_BV1          = 0 ; // в функции их включения/выключения Control_PT () .
#endif
//---
#ifdef bi_BV_2 // Для ШС2 в 12-пульсном СИФУ :
       Timer_BV2          = 0 ;
#endif
//---
#ifdef bi_Vent_Dvig
       Timer_Vent_Dvig    = 0 ;
#endif
//---
#ifdef bi_MasloSmazka
       Timer_MasloSmazka  = 0 ;
#endif
//---
#ifdef bi_Smazka_Podsh
       Timer_Smazka_Podsh = 0 ;
#endif
//---
       time               = Timer1_Ovr ;
//---
    break;
        //--------
    case 1 :
      ax = Timer1_Ovr - time ,  time = Timer1_Ovr ;

//------------
#ifdef bi_BV1
 #ifndef bo_Vkl_Vent // Если определено автоматическое вкл/выкл вентиляторов , выдержка не нужна .
 if ( bi_BV1 == 0 )
  {
    mSet_PreduprMsg( _Pr_BV1 ) ;
    if ( _r.Time_otkl_BV1 != 0 ) // Переходит ли предупреждение в аварию ?
     {
       if ( Prg._.Gotovn == 0 )  // в работе :
        {
          if ( (u)Timer_BV1 >= _r.Time_otkl_BV1 ) mSet_AvarMsg( _Av_BV1 ) ;
          else    Timer_BV1 += ax ;
        }
        // в Сборке Готовности , для того чтобы после отключения дать остыть
        // агрегату и не дать включить его на новую N-минутную выдержку .
       else goto c1 ;
     }
  }
 else
  {
c1: Timer_BV1 -= ax ;
    if ( (sw)Timer_BV1 <= 0 ) Timer_BV1 = 0 ;
  }
 #else // При автоматическом вкл/выкл вентиляторов предупреждение "Неисправность вентиляторов" :
 if ( bi_BV1 == 0 && bo_Vkl_Vent == 1 ) mSet_PreduprMsg( _Pr_BV1 ) ; // Для ШС1 .
 else                                   mClr_PreduprMsg( _Pr_BV1 ) ;
 //---
  #ifdef bi_BV2
   if ( bi_BV2 == 0 && bo_Vkl_Vent == 1 ) mSet_PreduprMsg2( _Pr2_BV2 ) ; // Для ШС2 .
   else                                   mClr_PreduprMsg2( _Pr2_BV2 ) ;
  #endif
 #endif
#endif
//------------
#ifdef bi_BV_2
 if ( bi_BV_2 == 0 ) // Для ШС2 в 12-пульсном СИФУ :
  {
    mSet_PreduprMsg2( _Pr2_BV2 ) ;
    if ( _r.Time_otkl_BV1 != 0 ) // Переходит ли предупреждение в аварию ?
     {
       if ( Prg._.Gotovn == 0 )  // в работе :
        {
          if ( (u)Timer_BV2 >= _r.Time_otkl_BV1 ) mSet_AvarMsg2( _Av2_BV2 ) ;
          else    Timer_BV2 += ax ;
        }
        // в Сборке Готовности , для того чтобы после отключения дать остыть
        // агрегату и не дать включить его на новую N-минутную выдержку .
       else goto c11 ;
     }
  }
 else
  {
c11:Timer_BV2 -= ax ;
    if ( (sw)Timer_BV2 <= 0 ) Timer_BV2 = 0 ;
  }
#endif
//------------
#ifdef bi_Vent_Dvig
 if ( bi_Vent_Dvig == 0 )
  {
    mSet_PreduprMsg( _Pr_Vent_Dvig ) ;
    if ( _r.Time_otkl_VentDvig != 0 ) // Переходит ли предупреждение в аварию ?
     {
       if ( Prg._.Gotovn == 0 )  // в работе :
        {
          if ( (u)Timer_Vent_Dvig >= _r.Time_otkl_VentDvig ) mSet_AvarMsg( _Av_Vent_Dvig ) ;
          else    Timer_Vent_Dvig += ax ;
        }
        // в Сборке Готовности , для того чтобы после отключения дать остыть
        // агрегату и не дать включить его на новую N-минутную выдержку .
       else goto c2 ;
     }
  }
 else
  {
c2: Timer_Vent_Dvig -= ax ;
    if ( (sw)Timer_Vent_Dvig <= 0 ) Timer_Vent_Dvig = 0 ;
  }
#endif
//------------
#ifdef bi_MasloSmazka
 if ( bi_MasloSmazka == 0 )
  {
    mSet_PreduprMsg( _Pr_MasloSmazka ) ;
    if ( _r.Time_MasloSmazka != 0 ) // Переходит ли предупреждение в аварию ?
     {
       if ( Prg._.Gotovn == 0 )  // в работе :
        {
          if ( (u)Timer_MasloSmazka >= _r.Time_MasloSmazka ) mSet_AvarMsg( _Av_MasloSmazka ) ;
          else    Timer_MasloSmazka += ax ;
        }
        // в Сборке Готовности , для того чтобы после отключения дать остыть
        // агрегату и не дать включить его на новую N-минутную выдержку .
       else goto c3 ;
     }
  }
 else
  {
c3: Timer_MasloSmazka -= ax ;
    if ( (sw)Timer_MasloSmazka <= 0 ) Timer_MasloSmazka = 0 ;
  }
#endif
//------------
#ifdef bi_Smazka_Podsh
 if ( bi_Smazka_Podsh == 0 )
  {
    mSet_PreduprMsg( _Pr_Smazka_Podsh ) ;
    if ( _r.Time_Smazka_Podsh != 0 ) // Переходит ли предупреждение в аварию ?
     {
       if ( Prg._.Gotovn == 0 )  // в работе :
        {
          if ( (u)Timer_Smazka_Podsh >= _r.Time_Smazka_Podsh ) mSet_AvarMsg( _Av_Smazka_Podsh ) ;
          else    Timer_Smazka_Podsh += ax ;
        }
        // в Сборке Готовности , для того чтобы после отключения дать остыть
        // агрегату и не дать включить его на новую N-минутную выдержку .
       else goto c4 ;
     }
  }
 else
  {
c4: Timer_Smazka_Podsh -= ax ;
    if ( (sw)Timer_Smazka_Podsh <= 0 ) Timer_Smazka_Podsh = 0 ;
  }
#endif
//------------
    break;
  }
  return  ;
}

//-----------------------------

  // Проверка присутствия вращения двигателя.
word Control_Skor ( void )
{
  word ah ;
  ah = 0 ;
 // chtoby mozshno bylo blokir. zaschitu .
 if ( _r.Ostanov_skor != 0 )
 {
  if ( (sw)Skor > (sw)_r.Ostanov_skor  ||
       (sw)Skor < (sw)( ~_r.Ostanov_skor + 1 ) )
    {
      mSet_PreduprMsg( _Pr_Skor_NoNull  ) ;
      ah = 1 ;
    }
  else mClr_PreduprMsg( _Pr_Skor_NoNull  ) ;
 }
 return ah ;
}

//-----------------------------

word  Control_Power ( void )  //  "Контроль" питания ИУ.
{
#ifdef  PUM_ach
 static word time ;
#endif
 //---
 switch ( N_Ucc2 )
 {
   default:
   case 0 :
  //---
#ifdef  PUM_ach
     N_Ucc2 = 1 ; // заряжаем измерение :
     PUM_Ucc = _AD_BUSY ;
     AD_Izm ( PUM_ach, &PUM_Ucc ) ;
   break ;
  //---
   case 1 : // Измерение Питания Усилителей Мощности Выходных Каскадов :
     if ( PUM_Ucc != _AD_BUSY )
      {
        mIzmData_Conversion ( PUM_Ucc , PUM_Ucc , PUM_ach ) ;
        if ( (sw)PUM_Ucc < (sw)_r.PUM_min || (sw)PUM_Ucc > (sw)_r.PUM_max )
         {
           // проверка повторности превышения :
           if ( Av2._.PUM == 1 ) // 09.03.2016 - Питание уже нестабилизированное , выдержка времени .
           {           // Выдержка времени - 7 мсек ( + второе превышение , + вход на зарядку ... ) :
             if ( (u)((w)(timer1 - time)) > _MkSec(7u * 1000u) ) mSet_AvarMsg( _Av_PUM ) ;
           }
           else Av2._.PUM = 1 ;
         }
        else
        {
                time = timer1 ;
                Av2._.PUM = 0 ; // превышение было одиночное .
        }
      }
#endif
//--------------
#ifdef   _SIFU2_
//--------------
#ifdef  _1P_ach
     N_Ucc2 = 2 ; // заряжаем измерение :
     _1P_Ucc = _AD_BUSY ;
     AD_Izm ( _1P_ach, &_1P_Ucc ) ;
   break ;
  //---
   case 2 : // Измерение питания формирователей ИУ :
     if ( _1P_Ucc != _AD_BUSY )
      {
        mIzmData_Conversion ( _1P_Ucc , _1P_Ucc , _1P_ach ) ;
        if ( (sw)_1P_Ucc < (sw)_r._1P_2P_min || (sw)_1P_Ucc > (sw)_r._1P_2P_max )
         {
           // проверка повторности превышения.
           if ( Av2._._1P == 1 )  mSet_AvarMsg2( _Av2_1P ) ;
           else                   Av2._._1P = 1 ;
         }
        else    Av2._._1P = 0 ; // превышение было одиночное .
      }
#endif
#ifdef  _2P_ach
     N_Ucc2 = 3 ; // заряжаем измерение :
     _2P_Ucc = _AD_BUSY ;
     AD_Izm ( _2P_ach, &_2P_Ucc ) ;
   break ;
  //---
   case 3 : // Измерение питания формирователей ИУ :
     if ( _2P_Ucc != _AD_BUSY )
      {
        mIzmData_Conversion ( _2P_Ucc , _2P_Ucc , _2P_ach ) ;
        if ( (sw)_2P_Ucc < (sw)_r._1P_2P_min || (sw)_2P_Ucc > (sw)_r._1P_2P_max )
         {
           // проверка повторности превышения :
           if ( Av2._._2P == 1 )  mSet_AvarMsg2( _Av2_2P ) ;
           else                   Av2._._2P = 1 ;
         }
        else    Av2._._2P = 0 ; // превышение было одиночное .
      }
#endif
//--------------
#endif //_SIFU2_
//--------------
     N_Ucc2 = 0 ; // переход на зарядку измерения :
   break ;
 }
return 0 ;
}

/*-------------------------------------------------*/
//      Однопороговый контроль изоляции ВОЗБУЖДЕНИЯ ГЕНЕРАТОРА по датчику
//  напряжения с делителя ус-ва контр.изоляции.
//
#ifdef Insul_G_ach
word  Contr_Insulat_G ( word num )
{
  static word Uinsul_full , Insul_time, Insul_timer ;
  static word Ud_insul ;
  static byte Ud_insul_drob ;
#ifdef  _Av2_InsulatG
  static word Insul_timer_av;
#endif

  register lword lax ;
  register word ax, bx ;

  switch ( num )
  {      //  Стартовая инициализация.
    case 0 :  UinsulG = 0, Insul_time = Timer1_Ovr, Insul_timer = 0 ;
              Ud_insul = 0 , Ud_insul_drob = 0 ;
         #ifdef  _Av2_InsulatG
              Insul_timer_av = 0 ;
         #endif
     start: Uinsul_full = _AD_BUSY ;  //  запуск первого измерения изоляции
            AD_Izm ( Insul_G_ach,    &Uinsul_full ) ;
      break;
         //  Рабочая программа.
    case 1 :
            if ( Uinsul_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Uinsul_full, ax, Insul_G_ach ) ;
                 if ( (sw)ax < 0 ) ax = ~ax+1 ;

                    //  Фильтрация.
                    // склеиваем целое и дробь.
               lax  = (slw)(sw)UinsulG << 8 ;
               lax += (lw)(w)UinsulG_drob ;   // DROB IS NOT SIGNED !

               if ( ax > UinsulG ) lax += _Insul_koef ;
               else                lax -= _Insul_koef ;

               UinsulG_drob = lax ;           // return drob.
               ax          = (slw)lax >> 8;
               if ( (sw)ax < 0 )  ax = 0 ;
               UinsulG = ax ;

               bx = _UoutG ;   //  выделяем модуль Uout.
               if ( (sw)bx < 0 ) bx = ~bx+1 ;
                    //  Фильтрация опорного напряжения, чтобы оно изменялось с той же
                    //      постоянной что и напряжение изоляции.
                    // склеиваем целое и дробь.
               lax  = (slw)(sw)Ud_insul << 8 ;
               lax += (lw)(w)Ud_insul_drob ;

               if ( bx > Ud_insul ) lax += _Insul_koef ;
               else                 lax -= _Insul_koef ;

               Ud_insul_drob = lax ;           // return drob.
               bx            = (slw)lax >> 8;
               if ( (sw)bx < 0 )  bx = 0 ;
               Ud_insul = bx ;

                  //  Не коррект. порог при низком напряжении, т.к.порог
                  // стремится к нулю и срабатывает в Сб.Гот.
               if( bx < _UoutG_nom( 0.25 ))  bx = _UoutG_nom( 0.25 ) ;
                   //  Коррекция порога срабатывания пропорционально Uout:
                   //            porog = porog * Uout / UoutG_nom.
               lax = (lw)bx * (lw)_r.Uinsul_max ;
               UinsulG_max  = lax / _UoutG_nom( 1.0 ) ;

               ax = Timer1_Ovr-Insul_time ;
               Insul_time = Timer1_Ovr ;
                   //  Контроль порога изоляции с выдержкой времени.
               if ( UinsulG > UinsulG_max  && bi_Otkl_Insul == 0 )
               {     // задержка накопительного типа 15.05.06 17:01
                 if ( (sw)Insul_timer > (sw)_Sec( 5 ) )  // 9 ) )
                 {
                   mSet_PreduprMsg2( _Pr2_InsulatG ) ;
                 }
                 else Insul_timer += ax ;
               }   //  вычитаем пока не переступили через нуль, и так и оставляем...
               else if ( (sw)Insul_timer > 0 ) Insul_timer -= ax ;

                     //  Предупреждение и выходной сигнал очищаются
                    // только через Дист.Сброс.
               if ( (Reg_PreduprMsg2 & _Pr2_InsulatG) != (lw)r0 )
                                                      bo_InsulatG = 1 ;
               else                                   bo_InsulatG = 0 ;
            //--------------------

          #ifdef  _Av2_InsulatG
               lax = (lw)bx * (lw)_or.Uinsul_max_av ;
               bx = lax / _UoutG_nom( 1.0 ) ;

                   //  Контроль порога изоляции с выдержкой времени.
               if ( UinsulG > bx && bi_Otkl_Insul == 0 )
               {      //  Второй порог либо аварийный либо предупредительный.
                 if ( (sw)_or.Tinsul != 0 )  // задержка накопительного типа 15.05.06 17:01
                 {
                   if ( (sw)Insul_timer_av > (sw)_or.Tinsul )  // 9
                   {
                     mSet_AvarMsg2( _Av2_InsulatG ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
                 else
                 {
                   if ( (sw)Insul_timer_av > (sw)_Sec( 5 ) )
                   {
                     mSet_PreduprMsg2( _Pr2_InsulatG2 ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
               }   //  вычитаем пока не переступили через нуль, и так и оставляем...
               else if ( (sw)Insul_timer_av > 0 ) Insul_timer_av -= ax ;
          #endif

               //-----
               goto start; //  запуск очередного измерения.
             }
      break;
  }
  return 0 ;
}
#endif
/*-------------------------------------------------*/
//      Однопороговый контроль изоляции ВОЗБУЖДЕНИЯ ДВИГАТЕЛЯ по датчику
//  напряжения с делителя ус-ва контр.изоляции.
//
#ifdef Insul_D_ach
word  Contr_Insulat_D ( word num )
{
  static word Uinsul_full , Insul_time, Insul_timer ;
  static word Ud_insul ;
  static byte Ud_insul_drob ;
#ifdef  _Av2_InsulatD
  static word Insul_timer_av;
#endif

  register lword lax ;
  register word ax, bx ;

  switch ( num )
  {      //  Стартовая инициализация.
    case 0 :  UinsulD = 0, Insul_time = Timer1_Ovr, Insul_timer = 0 ;
              Ud_insul = 0 , Ud_insul_drob = 0 ;
         #ifdef  _Av2_InsulatD
              Insul_timer_av = 0 ;
         #endif
     start: Uinsul_full = _AD_BUSY ;  //  запуск первого измерения изоляции
            AD_Izm ( Insul_D_ach,    &Uinsul_full ) ;
      break;
         //  Рабочая программа.
    case 1 :
            if ( Uinsul_full != _AD_BUSY )
             {
               mIzmData_Conversion ( Uinsul_full, ax, Insul_D_ach ) ;
                 if ( (sw)ax < 0 ) ax = ~ax+1 ;

                    //  Фильтрация.
                    // склеиваем целое и дробь.
               lax  = (slw)(sw)UinsulD << 8 ;
               lax += (lw)(w)UinsulD_drob ;   // DROB IS NOT SIGNED !

               if ( ax > UinsulD ) lax += _Insul_koef ;
               else                lax -= _Insul_koef ;

               UinsulD_drob = lax ;           // return drob.
               ax          = (slw)lax >> 8;
               if ( (sw)ax < 0 )  ax = 0 ;
               UinsulD = ax ;

      #ifndef  Uf_ach  // Если напряжение возбуждения не измеряется :
                // Для напряжения в эконом. поле :
         #ifndef _KTE_GD                                //  выделяем модуль Uout.
               if ( _r.Cfg._.Iv_Econom == 1 && bi_QK1 == 0 ) bx = _or.Uf_econom ;
         #else
               if ( _r.Cfg._.Iv_Econom == 1 && bi_LK  == 0 ) bx = _or.Uf_econom ;
         #endif
               // Когда поле номинальное , ориентируемся на номинал :
               else bx = _UoutD_nom( 1.00 ) ;
               Uf = bx ;
      #else
               bx = _UoutD ;   //  выделяем модуль Uout.
               if ( (sw)bx < 0 ) bx = ~bx+1 ;
      #endif
                    //  Фильтрация опорного напряжения, чтобы оно изменялось с той же
                    //      постоянной что и напряжение изоляции.
                    // склеиваем целое и дробь.
               lax  = (slw)(sw)Ud_insul << 8 ;
               lax += (lw)(w)Ud_insul_drob ;

               if ( bx > Ud_insul ) lax += _Insul_koef ;
               else                 lax -= _Insul_koef ;

               Ud_insul_drob = lax ;           // return drob.
               bx            = (slw)lax >> 8;
               if ( (sw)bx < 0 )  bx = 0 ;
               Ud_insul = bx ;

                  //  Не коррект. порог при низком напряжении, т.к.порог
                  // стремится к нулю и срабатывает в Сб.Гот.
               if( bx < _UoutD_nom( 0.25 ))  bx = _UoutD_nom( 0.25 ) ;
                   //  Коррекция порога срабатывания пропорционально Uout:
                   //            porog = porog * Uout / UoutD_nom.
               lax = (lw)bx * (lw)_r.Uinsul_max ;
               UinsulD_max  = lax / _UoutD_nom( 1.0 ) ;

               ax = Timer1_Ovr-Insul_time ;
               Insul_time = Timer1_Ovr ;
                   //  Контроль порога изоляции с выдержкой времени.
               if ( UinsulD > UinsulD_max  && bi_Otkl_Insul == 0 )
               {     // задержка накопительного типа 15.05.06 17:01
                 if ( (sw)Insul_timer > (sw)_Sec( 5 ) )  // 9 ) )
                 {
                   mSet_PreduprMsg2( _Pr2_InsulatD ) ;
                 }
                 else Insul_timer += ax ;
               }   //  вычитаем пока не переступили через нуль, и так и оставляем...
               else if ( (sw)Insul_timer > 0 ) Insul_timer -= ax ;

                     //  Предупреждение и выходной сигнал очищаются
                    // только через Дист.Сброс.
               if ( (Reg_PreduprMsg2 & _Pr2_InsulatD) != (lw)r0 )
                                                      bo_InsulatD = 1 ;
               else                                   bo_InsulatD = 0 ;
            //--------------------

          #ifdef  _Av2_InsulatD
               lax = (lw)bx * (lw)_or.Uinsul_max_av ;
               bx = lax / _UoutD_nom( 1.0 ) ;

                   //  Контроль порога изоляции с выдержкой времени.
               if ( UinsulD > bx && bi_Otkl_Insul == 0 )
               {      //  Второй порог либо аварийный либо предупредительный.
                 if ( (sw)_or.Tinsul != 0 )  // задержка накопительного типа 15.05.06 17:01
                 {
                   if ( (sw)Insul_timer_av > (sw)_or.Tinsul )  // 9
                   {
                     mSet_AvarMsg2( _Av2_InsulatD ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
                 else
                 {
                   if ( (sw)Insul_timer_av > (sw)_Sec( 5 ) )
                   {
                     mSet_PreduprMsg2( _Pr2_InsulatD2 ) ;
                   }
                   else Insul_timer_av += ax ;
                 }
               }   //  вычитаем пока не переступили через нуль, и так и оставляем...
               else if ( (sw)Insul_timer_av > 0 ) Insul_timer_av -= ax ;
          #endif

               //-----
               goto start; //  запуск очередного измерения.
             }
      break;
  }
  return 0 ;
}
#endif
//-----------------------------

// "КОНТРОЛЬ КОНТАКТОРА ДИНАМИЧЕСКОГО ТОРМОЖЕНИЯ"
#ifdef  bi_QKDT
void Control_QKDT ( void )
{
  static word time ;

  if ( bi_QKDT == 1 ) // Если контактор ДТ включен ,
  {
     mSet_ServiceMsg( _Srv_QKDT ) ;
     if ( bi_QK1 == 0 ) time = Timer1_fSec ;
     else if ( (u)((w)(Timer1_fSec-time)) > _fSec( 3.0 ) ) // ЛК вкл. > 3 сек.
     {
        mSet_AvarMsg2 ( _Av2_QKDT ) ;
     }
  }
  else
  {
    time = Timer1_fSec ;
    mClr_ServiceMsg( _Srv_QKDT ) ;
  }
return ;
}
#endif
//-----------------------------

// "УПРАВЛЕНИЕ КОНТАКТОРОМ ДИНАМИЧЕСКОГО ТОРМОЖЕНИЯ"
#ifdef  bo_QKDT
void Upr_QKDT ( void )
{
  //если линейник и ВАТ включены - включаем контактор дин.торможения,
  //т.е. отключаем резисторы ДТ
  #ifndef _KTE_GD
      if ( bi_QK1 == 1 && bi_AK1 == 1 )
  #else
      if ( bi_LK == 1 )
  #endif
           bo_QKDT = 1 ;
      else bo_QKDT = 0 ;

return ;
}
#endif
//-----------------------------

word MechTorm_upr ( word num )
{
  static word time2 , time3 ;
  static byte trigg , trigg2 ;
  static word time_MT ;
  static word time2_MT ;
  register word ax ;
#ifdef bi_MT
  static word time_MT_Err ;
  static byte trigg_MT_Err ;
#endif

  switch ( num )
  {
    case _MT_Init :
          trigg = 1 , trigg2 = 0 ;
          time2 = Timer1_Ovr ;
          time3 = Timer1_Ovr ;
          time_MT = Timer1_Ovr ;
          time2_MT = Timer1_Ovr ;
#ifdef bi_MT
          time_MT_Err = Timer1_Ovr ;
          trigg_MT_Err = 0 ;
#endif
    break;

      //------**************************************************---------
    case _MT_Upr :
        // Наложение/снятие механического тормоза.
      if ( _r.Cfg._.MT == 1 )
      {
  //******
 #ifndef  _MT_Podyom
  //******
        if ( bi_QK1 == 1 && bo_Avar == 0 && Prg._.Gotovn == 0 )
        {
          bo_MT = 1 ; // Снимаем МТ .
          time_MT = Timer1_Ovr ;
        }
        else if ( bo_MT == 1 ) // Если МТ не наложен , накладываем :
        {
            // Проверка присутствия вращения двигателя.
          if (((sw)Skor > (sw)_r.Ostanov_skor
                        ||
               (sw)Skor < (sw)( ~_r.Ostanov_skor + 1 ))) bo_MT = 1 ;
          else bo_MT = 0 ;

           // При необходимости МТ-стояночный превращается в МТ-аварийный :
          if ( _r.Time_MT != 0 ) // если уставка времени задана ,
           { // МТ накладывается по выдержке на вращающийся двигатель :
             if ( (u)((w)(Timer1_Ovr-time_MT)) > _r.Time_MT ) bo_MT = 0 ;
           } // используем ту же уставку , что и на ограничение тока _MT_Podyom.
        }

  //******
 #else
  //******
            // если из-вне кто-то наложил тормоз приводим триг.в соотв.
        if ( bo_MT == 0 && trigg2 == 1 )
        {
          time_MT = Timer1_Ovr ;
          trigg2 = 0 ;
        }

            // Проверка Рабочего режима и порога тока отпускания МТ.
        if ( bo_Avar == 0 && bi_QK1 == 1 && Prg._.Gotovn == 0 )
        {     // растормаживаемся по току, затормаживаемся по ЗИ скорости.
      #ifndef _KTE_GD
          if ( IDV   >= _r.Id_Otkl_MT )
      #else
          if ( IDV_g >= _r.Id_Otkl_MT )
      #endif
          {                         //'+1'-чтобы искл.гонку с наложением
            if ( (u)((w)(Timer1_Ovr-time_MT)) > (_r.Time_MT+1) )  trigg2 = 1 ;
          }
          else time_MT = Timer1_Ovr ;
        }
        else
        {
          time_MT = Timer1_Ovr ;
          trigg2 = 0 ;
        }
        //----
        //if ( bo_MT == 1 && trigg2 == 0 ) {...} приводить в соотв. по единице не надо

        if( (sw)ZISkor < (sw)_r.Ostanov_skor && (sw)ZISkor > (sw)( ~_r.Ostanov_skor + 1 )
             && Z_Skor == 0 ) // DAN 02.12.2010 15:15 - При медленном ЗИС МТ успевает наложиться при
            //             || // реверсе скорости . Проверено на ДМК РГП - 9 .
          //(sw)Skor < (sw)_r.Ostanov_skor && (sw)Skor > (sw)( ~_r.Ostanov_skor + 1 ))
        {
          if ( (u)((w)(Timer1_Ovr-time2_MT)) > _r.Time_MT )
          {
            time_MT = Timer1_Ovr ;
            trigg2 = 0 ;
          }
        }
        else time2_MT = Timer1_Ovr ;
        //---
        if ( trigg2 == 1 ) bo_MT = 1 ;
        else               bo_MT = 0 ;
  //******
 #endif
  //******
      }
      else
      {   // Управляем мех.торм. по CAN если отключено его упр. от КТЭ.
        can_ConfigReg ( _CAN_MT ) ;
      }
          // Управляем мех.торм. объектно.
        obj_ConfigReg ( _Obj_MT ) ;

    #ifdef bi_MT           // 02.05.2020 18:47 По просьбе Проценко О.А. контроль исправности тормоза.
        if ( bo_MT == 0 )  // Проявилось на кране 35-36 ДМКД. Там из релейки этот контроль выкинули,
        {                  // а в ТЗ на КТЭ не добавили.
          time_MT_Err = Timer1_Ovr ;
          trigg_MT_Err = 0 ;
        }
        else
        {
          if ( _r.Time_MT_Err != 0 )
          {
            if ( (u)((w)(Timer1_Ovr - time_MT_Err)) > _r.Time_MT_Err )
            {
              trigg_MT_Err = 1 ;
            }
          }
        }
        if ( bi_MT == 0 && trigg_MT_Err == 1 ) mSet_AvarMsg2( _Av2_MT_Err ) ;
    #endif

    break;

      //------**************************************************---------
    case _MT_Id_Zad_Ogr: // Только для подъемных механизмов :
            // держим ограничение тока якоря пока наложен тормоз
            // и некоторое время после снятия наложения, чтобы дать время
            // разжаться колодкам тормоза.
 #ifdef  _MT_Podyom
      if ( _r.Cfg._.MT == 1 )
      {
        if ( bo_MT == 0 ) // Получена команда наложить МТ :
        {
          time2 = Timer1_Ovr ;
           // ограничивать ток торможения сразу нельзя , МТ должен наложиться :
          if ( (u)((w)(Timer1_Ovr - time3)) > _r.Time_MT ) trigg = 1 ;
        }
        else // Получена команда снять МТ :
        {
          time3 = Timer1_Ovr ;
           // после команды выдержка на снятие МТ с ограничением тока :
          if ( (u)((w)(Timer1_Ovr - time2)) > _r.Time_MT ) trigg = 0 ;
        }
        // Ограничение задания на ток :
        if ( trigg == 1 && ( (sw)ZISkor > (sw)_r.Ostanov_skor
                                        ||
                             (sw)ZISkor < (sw)( ~_r.Ostanov_skor + 1 ) ) )
        {
          ax = _r.Id_Otkl_MT + _Id_nom( 0.1 ) ;
          if ( (sw)OuRegS >= 0 )
          {
            if ((sw)OuRegS > (sw)ax ) OuRegS = ax , Prz._.int_p = 1 ;
          }
          else
          {
            ax = ~ax+1 ;
            if ((sw)OuRegS < (sw)ax ) OuRegS = ax , Prz._.int_m = 1 ;
          }
        }
      }
 #else
      ax = 0 ; // заглушка для компилятора о неиспользовании ах .
 #endif
    break;
  }
  return 0 ;
}

//-----------------------

#ifdef _ATK_SET
void Otkl_Q1_ATK ( void ) // Отключаем автомат Q1 при пропадании силы от Согласующего Трансформатора .
{
  if ( Prg._.Gotovn == 0 )
  {
       //02.08.2017 8:00 - Отключаем автомат Q1 по разному для Ведущего и Ведомого :
       if ( (bi_Pusk == 1 && flgO._.Vedushiy == 1) || (ATK2_Pusk == 1 && flgO._.Vedushiy == 0) )
       {
         mOtkl_Q1 () ; // DAN 07.06.2017 17:13 - Грыгорыч в работе отключает Q1 .
#ifdef   bo_atkOtkl_Q1
         bo_atkOtkl_Q1 = 1 ; // Выставляем флаг отключения Q1 для принятия во втором АТК .
#endif
       }
  }
  return ;
}
#endif

//----------- Заглушки для неиспользуемых аварий/предупреждений --------------
//----------------- ( для стандартных масок в AVAR.H ) -----------------------
#ifndef    _Av_Iv_Max
  #define  _Av_Iv_Max        0
#endif
#ifndef    _Av2_Id1Max
  #define  _Av2_Id1Max       0
#endif
#ifndef    _Av2_Id2Max
  #define  _Av2_Id2Max       0
#endif
#ifndef    _Av2_Id2_Max
  #define  _Av2_Id2_Max      0
#endif
#ifndef    _Av_Id_sum_Max
  #define  _Av_Id_sum_Max    0
#endif
#ifndef    _Av_Gercon3
  #define  _Av_Gercon3       0      // Для агрегатов с 4-мя ШС .
#endif
#ifndef    _Av_Gercon4
  #define  _Av_Gercon4       0      // Для агрегатов с 4-мя ШС .
#endif
#ifndef    _Av_PUM
  #define  _Av_PUM           0
#endif
#ifndef    _Av2_1P
  #define  _Av2_1P           0
#endif
#ifndef    _Av2_2P
  #define  _Av2_2P           0
#endif
#ifndef    _Pr_AF1P
  #define  _Pr_AF1P          0
#endif
#ifndef    _Pr_WDT
  #define  _Pr_WDT           0
#endif
#ifndef    _Av2_AF2
  #define  _Av2_AF2          0
#endif
#ifndef    _Pr2_AF2P
  #define  _Pr2_AF2P         0
#endif
#ifndef    _Pr3_BK1A
  #define  _Pr3_BK1A         0
#endif
#ifndef    _Pr3_BK1B
  #define  _Pr3_BK1B         0
#endif
#ifndef    _Pr3_BK1C
  #define  _Pr3_BK1C         0
#endif
#ifndef    _Pr3_BK2A
  #define  _Pr3_BK2A         0
#endif
#ifndef    _Pr3_BK2B
  #define  _Pr3_BK2B         0
#endif
#ifndef    _Pr3_BK2C
  #define  _Pr3_BK2C         0
#endif
#ifndef    _Pr_Perecl_DS
  #define  _Pr_Perecl_DS     0
#endif
#ifndef    _Pr2_ProbM1_VT11_24
  #define  _Pr2_ProbM1_VT11_24  0
#endif
#ifndef    _Pr2_ProbM1_VT12_25
  #define  _Pr2_ProbM1_VT12_25  0
#endif
#ifndef    _Pr2_ProbM1_VT13_26
  #define  _Pr2_ProbM1_VT13_26  0
#endif
#ifndef    _Pr2_ProbM1_VT14_21
  #define  _Pr2_ProbM1_VT14_21  0
#endif
#ifndef    _Pr2_ProbM1_VT15_22
  #define  _Pr2_ProbM1_VT15_22  0
#endif
#ifndef    _Pr2_ProbM1_VT16_23
  #define  _Pr2_ProbM1_VT16_23  0
#endif
#ifndef    _Pr2_ProbM2_VT11_24
  #define  _Pr2_ProbM2_VT11_24  0
#endif
#ifndef    _Pr2_ProbM2_VT12_25
  #define  _Pr2_ProbM2_VT12_25  0
#endif
#ifndef    _Pr2_ProbM2_VT13_26
  #define  _Pr2_ProbM2_VT13_26  0
#endif
#ifndef    _Pr2_ProbM2_VT14_21
  #define  _Pr2_ProbM2_VT14_21  0
#endif
#ifndef    _Pr2_ProbM2_VT15_22
  #define  _Pr2_ProbM2_VT15_22  0
#endif
#ifndef    _Pr2_ProbM2_VT16_23
  #define  _Pr2_ProbM2_VT16_23  0
#endif
#ifndef    _Pr2_ProbM3_VT11_24
  #define  _Pr2_ProbM3_VT11_24  0   // Для агрегатов с 4-мя ШС .
#endif
#ifndef    _Pr2_ProbM3_VT12_25
  #define  _Pr2_ProbM3_VT12_25  0
#endif
#ifndef    _Pr2_ProbM3_VT13_26
  #define  _Pr2_ProbM3_VT13_26  0
#endif
#ifndef    _Pr2_ProbM3_VT14_21
  #define  _Pr2_ProbM3_VT14_21  0
#endif
#ifndef    _Pr2_ProbM3_VT15_22
  #define  _Pr2_ProbM3_VT15_22  0
#endif
#ifndef    _Pr2_ProbM3_VT16_23
  #define  _Pr2_ProbM3_VT16_23  0
#endif
#ifndef    _Pr2_ProbM4_VT11_24
  #define  _Pr2_ProbM4_VT11_24  0   // Для агрегатов с 4-мя ШС .
#endif
#ifndef    _Pr2_ProbM4_VT12_25
  #define  _Pr2_ProbM4_VT12_25  0
#endif
#ifndef    _Pr2_ProbM4_VT13_26
  #define  _Pr2_ProbM4_VT13_26  0
#endif
#ifndef    _Pr2_ProbM4_VT14_21
  #define  _Pr2_ProbM4_VT14_21  0
#endif
#ifndef    _Pr2_ProbM4_VT15_22
  #define  _Pr2_ProbM4_VT15_22  0
#endif
#ifndef    _Pr2_ProbM4_VT16_23
  #define  _Pr2_ProbM4_VT16_23  0
#endif
#ifndef    _Srv_NoCAN_QK
  #define  _Srv_NoCAN_QK     0
#endif
#ifndef    _Srv_Not_Nul_Id
  #define  _Srv_Not_Nul_Id   0
#endif
#ifndef    _Srv_Not_Iv
  #define  _Srv_Not_Iv       0
#endif
#ifndef    _Srv_AN_Av
  #define  _Srv_AN_Av        0
#endif
#ifndef    _Srv_AN_Ra_Te
  #define  _Srv_AN_Ra_Te     0
#endif
#ifndef    _Srv_AN_Tm
  #define  _Srv_AN_Tm        0
#endif
#ifndef    _Srv_AN_Err
  #define  _Srv_AN_Err       0
#endif
#ifndef    _Srv_AN_Kreg
  #define  _Srv_AN_Kreg      0
#endif
#ifndef    _Srv_AN_Iv_min
  #define  _Srv_AN_Iv_min    0
#endif
#ifndef    _Srv_No_EDS_Nom
  #define  _Srv_No_EDS_Nom   0
#endif
//---------------------------------------------
//-----------------------------

 word Common_avar ( void )
 {
#ifdef   Iv_ach
    static byte Ivmin ;
#endif
#ifdef   bo_DS_MT
    static word time_ds ;
#endif

      // Вызов объектной программы перед всеми защитами , например ,
    ObjPrg ( _Obj_c_Common_avar ) ; // для зарядки измерений .

    Contr_Ttrans_4_20 ( 1 ) ; // Зарядка измерения датчика температуры трансформатора .
    Zad_Skor_4_20 ( 1 ) ; // Зарядка измерения Задания токовой петлёй 4-20 мА .
    Mashtab_Dat () ;
    Control_Power_Circuit () ;
  //08.04.2008 11:31 - Для добавления выдержки времени на аварию Id-max убран вызов в фоне
  //контроля Id_Max , т.к. все равно измерение и преобразование тока выполняются в СИФУ .
  //Control_Id_Max () ;
#ifndef _ATK_SET // Для АД не нужно ( АТК или УПТФ ) .
    Control_E_Max  () ;
    Control_N_Max  () ;
#endif
    Control_DatSkor () ; // Для АТК используем .
#ifdef _KTE_GD
    Control_Ig_Ug_Max () ;
    Control_Ug_Min () ;
    Control_Id_Min () ;
#endif
    Contr_Insulat( 1 ) ;
  #ifdef Insul_G_ach
    Contr_Insulat_G( 1 ) ; // Контроль Изоляции Возбуждения Генератора .
  #endif
  #ifdef Insul_D_ach
    Contr_Insulat_D( 1 ) ; // Контроль Изоляции Возбуждения Двигателя .
  #endif

    can_ConfigReg ( _CAN_Avar ) ;  // CAN-команда Аварийного отключения.

#ifndef _ALARM_FZ
  #ifdef  _Union_FR
    if ( Av._.P24 == 1 )
    {
      mSet_PreduprMsg( _Pr_P24) ;
      //Включение компаратора напряжения 1Р24
      Av._.P24 = 0;
      Alarm_on();
    }
  #endif
#endif

    Control_Ucc () ;        //  Контроль питающих напряжений.
    Control_Power () ;      //  Контроль питания ИУ.
    Control_Predohr () ;    //  Контроль предохранителей (Вых.каск.).
    Control_Stoyanka () ;   //  Контроль стоянки по током.
    Control_Gercon () ;     //  Контроль сигналов Герконов.
    Contr_Ttrans_4_20 ( 2 ) ; // Обработка и выдача предупреждения датчика температуры трансформатора .
    Zad_Skor_4_20 ( 2 ) ;     // Обработка и выдача предупреждения обрыва задания .
    T_Izm_Dat ( 1 ) ;         // Обработка аналоговых измерениq температуры каждого охладителя в каждом силовом шкафу и выдача сообщений .

   //  Usrednitel( &Iv_usr, 2); // перенесено в REG_EDS.C
   //  V.Iv = (sw)( (slw)(sw)V.Iv_full * (slw)(sw)_r.Mashtab_Iv >> 8 ) ;


//-------------------------- Включения Вентиляторов --------------------------
//------------------------- по токам силовых мостов --------------------------
#ifdef bo_VklVent
//---
   // Включаем вентиляторы по перегреву ( если есть датчики температуры ) или в работе по беззнаковому току
   if ( (Prg._.Gotovn == 0 && bo_Avar == 0 && (IDV >= _or.Id_Vkl_Vent
  #if defined(_SIFU2_) && !defined(bo_VklVent2) // Если вентиляторы включаются в 12-ти пульсной одновременно :
                                                                     || IDV2 >= _or.Id_Vkl_Vent
  #endif
                                                                                                ) )
  #ifdef _Dat_Temp_Max
              || Hotest.Temperat >= _or.T_Pr
  #endif
                                             )
   {
      bo_VklVent = 1 ; // Включаем вентиляторы .
      //---
      timerVent = Timer1_Ovr ;
   }
   else if ( bo_VklVent == 1 ) // Если тока уже нет , но вентиляторы включены ,
   { // держим их включенными еще некоторое время , или пока кто-то не сбросит их "дист.сбросом" :
        if ( (u)((w)(Timer1_Ovr - timerVent)) > _or.T_Otkl_Vent || Av._.DistSbros == 1 )
          {    // через выдержку
            bo_VklVent = 0 ;  // отключение вентиляторов .
          }
   }
#endif
//----------------------------------------------------------------------------
#if defined(_SIFU2_) && defined(bo_VklVent2) // Если вентиляторы включаются в 12-ти пульсной НЕ одновременно :
   // Включаем вентиляторы по перегреву ( если есть датчики температуры ) или в работе по беззнаковому току
   if ( (Prg._.Gotovn == 0 && bo_Avar == 0 && IDV2 >= _or.Id_Vkl_Vent )
  #ifdef _Dat_Temp_Max
                                                                        || Hotest.Temperat >= _or.T_Pr
  #endif
                                                                                                       )
   {
      bo_VklVent2 = 1 ; // Включаем вентиляторы .
      //---
      timerVent2 = Timer1_Ovr ;
   }
   else if ( bo_VklVent2 == 1 ) // Если тока уже нет , но вентиляторы включены ,
   { // держим их включенными еще некоторое время , или пока кто-то не сбросит их "дист.сбросом" :
        if ( (u)((w)(Timer1_Ovr - timerVent2)) > _or.T_Otkl_Vent || Av._.DistSbros == 1 )
          {    // через выдержку
            bo_VklVent2 = 0 ;  // отключение вентиляторов .
          }
   }
#endif
//----------------------------------------------------------------------------


#ifdef   It_ach  // Для агрегатов с измерением тока тормоза :
    Usrednitel( &It_usr, 2);
    It = (sw)( (slw)(sw)It_full * (slw)(sw)_r.Mashtab_It >> 8 ) ;
#endif

#ifdef   bo_DS_MT // Для дистанционногои сброса платы МТ :
        // Начинаем отсчитывать выдержку ( через  300 мс произойдёт сброс возбудителя ) :
    if ( bo_DS_MT == 0 ) time_ds = Timer1_Ovr ;
    else if ( (u)((w)(Timer1_Ovr-time_ds)) > _Sec( 0.3 ) ) bo_DS_MT = 0 ;
#endif

#ifdef   Iv_ach
 #ifdef   _AVTONASTR
  if ( Isp._.AvtoNastr == 1 && AnastrRT == 0 ) ; // блокировка на время автонастр.
  else
 #endif
   {    //  "Минимальный ток Возбудителя".
    if ( V.Iv < _r.Iv_avar_Min
   #ifdef _RVId
      || V2.Iv < _r.Iv_avar_Min
   #endif
       )
     {
        if ( ((b)(Puls_counter - time_Iv_min) > _r.time_Iv_min) || Ivmin == 1 )
         {
   #ifdef _RVId
           if ( V.Iv < _r.Iv_avar_Min ) mSet_AvarMsg( _Av_Iv_Min ) ;
           if ( V2.Iv < _r.Iv_avar_Min ) mSet_AvarMsg2( _Av2_Iv2_Min ) ;
   #else
           mSet_AvarMsg( _Av_Iv_Min ) ;
   #endif
           Ivmin = 1 ; // когда счетчик Puls_counter обнулится , останется взведенным флаг ...
         }
     }
    else time_Iv_min = Puls_counter , Ivmin = 0 ;
   }
#endif
      //   Проверка активности сервисных программ, при которых
      // запрещен режим "Работа" :
    if ( Isp._.Predupr == 1 )   mSet_PreduprMsg( _Pr_ServiceProg   ) ;


//--- При синхр. якорного СИФУ от Силы моста, а возб.от СН380.
#ifdef  _SIFU_Syn2    // ЕСТЬ ЛИ ОТДЕЛЬНАЯ СИНХРОНИЗАЦИЯ ОТ МОСТА ДЛЯ СИФУ.
  if ( _r.Cfg2._.SIFU_Syn2 == 1 )
  {
#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn2.T1_ovr)) >= 3 )
#else   // На синхронной скорости 1000 об/мин ПДФ на стенде выдаёт 166 кГц и фон "раздувается"
      if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn2.T1_ovr)) >= 9 ) ||
          ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn2.T1_ovr)) >= 3 ) )
#endif
      {
        mSet_AvarMsg ( _Av_NoSynch2 ) ;
#ifdef _ATK_SET
        Otkl_Q1_ATK () ; // Отключаем автомат Q1 при пропадании силы от Согласующего Трансформатора .
        flgO._.Usil_ok = 0 ;
      }
      else flgO._.Usil_ok = 1 ;
#else
  }
#endif
  // При отключении второй синхронизации оставалось значение последнего периода - проявилось
  // на КТЕ5-50 ДМКД 14.09.2018 .
  // 28.05.2020 DAN - Нельзя ориентироваться на бит Syn2.b_SIauto , т.к. после выбора
  // рабочей синхронизации он обнуляется ...
  // При отключении второй синхронизации , чтобы не срабатывала здесь авария , значение её периода
  // инициализируется при выборе рабочей синхронизации .
  /* Проверка периода на минимальное значение */
  if      ( (u)Tsyn2 < _r.TMIN )
  {
    mSet_AvarMsg2 ( _Av2_Tmin2 ) ;
#ifdef _ATK_SET
    Otkl_Q1_ATK () ; // Отключаем автомат Q1 при пропадании силы от Согласующего Трансформатора .
    flgO._.UsilTMIN_ok = 0 ;
#endif
  }
  /* Проверка периода на максимальное значение */
  else if ( (u)Tsyn2 > _r.TMAX )
  {
    mSet_AvarMsg2 ( _Av2_Tmax2 ) ;
#ifdef _ATK_SET
    Otkl_Q1_ATK () ; // Отключаем автомат Q1 при пропадании силы от Согласующего Трансформатора .
    flgO._.UsilTMAX_ok = 0 ;
  }
  else // Период в порядке :
  {
    flgO._.UsilTMIN_ok = 1 ;
    flgO._.UsilTMAX_ok = 1 ;
  }
  
  //Основную синхронизацию контроллируем при отсутстствии синхронизации от силы
  if (!flgO._.Usil_ok || !flgO._.UsilTMIN_ok || !flgO._.UsilTMAX_ok) 
  {
#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 )  mSet_AvarMsg ( _Av_NoSynch ) ;
#else   // На синхронной скорости 1000 об/мин ПДФ на стенде выдаёт 166 кГц и фон "раздувается"
    if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 9 ) ||
        ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 ) )  mSet_AvarMsg ( _Av_NoSynch ) ;
#endif
    /* Проверка периода на минимальное значение */
    if      ( (u)Tsyn < _r.TMIN )   mSet_AvarMsg ( _Av_Tmin ) ;
    /* Проверка периода на максимальное значение */
    else if ( (u)Tsyn > _r.TMAX )   mSet_AvarMsg ( _Av_Tmax ) ;
  }
  
 }
  else   // Отключена вторая синхронизация - снимаем все флаги :
  {
    flgO._.Usil_ok = 0 ;
    flgO._.UsilTMIN_ok = 0 ;
    flgO._.UsilTMAX_ok = 0 ;

#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 )  mSet_AvarMsg ( _Av_NoSynch ) ;
#else   // На синхронной скорости 1000 об/мин ПДФ на стенде выдаёт 166 кГц и фон "раздувается"
    if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 9 ) ||
        ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 ) )  mSet_AvarMsg ( _Av_NoSynch ) ;
#endif
    /* Проверка периода на минимальное значение */
    if      ( (u)Tsyn < _r.TMIN )   mSet_AvarMsg ( _Av_Tmin ) ;
    /* Проверка периода на максимальное значение */
    else if ( (u)Tsyn > _r.TMAX )   mSet_AvarMsg ( _Av_Tmax ) ;
    
    
  }
#else
      }
    }
  }
#endif

#else //_SIFU_Syn2

#ifndef _LABOR_STEND
    if ( (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 )  mSet_AvarMsg ( _Av_NoSynch ) ;
#else   // На синхронной скорости 1000 об/мин ПДФ на стенде выдаёт 166 кГц и фон "раздувается"
    if ( ( bi_Technol_Ostanov == 1 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 9 ) ||
        ( bi_Technol_Ostanov == 0 && (u)((w)(Timer1_Ovr - Syn.T1_ovr))  >= 3 ) )  mSet_AvarMsg ( _Av_NoSynch ) ;
#endif
    /* Проверка периода на минимальное значение */
    if      ( (u)Tsyn < _r.TMIN )   mSet_AvarMsg ( _Av_Tmin ) ;
    /* Проверка периода на максимальное значение */
    else if ( (u)Tsyn > _r.TMAX )   mSet_AvarMsg ( _Av_Tmax ) ;


#endif

#ifdef _ATK_SET
  #ifdef   bo_atkOtkl_Q1
    //02.08.2017 8:00 - Грыгорыч решил , что отключать Q1 надо у обоих , если сила пропала на одном из АТК :
    if ( ATK2_Otkl_Q1 == 1 ) mOtkl_Q1 () ;
  #endif
#endif

        /* Проверка табличных тепловых ограничений. */
    if ( Id_teplo_max <= _r.Id_teplo_predupr )   mSet_PreduprMsg ( _Pr_Teplo ) ;

#ifndef _KTE_GD
 #ifdef _SIFU2_
  if ( S.Disable == 1 ) // DAN 23.05.2017 14:46 - При работе только ШС2 :
  {
    if ( IDV2 >= Id_teplo_max )   mSet_AvarMsg ( _Av_Teplo ) ;
  }
  else
 #endif
  {
   #ifndef _ATK_SET
    if ( IDV >= Id_teplo_max )   mSet_AvarMsg ( _Av_Teplo ) ;
   #else // В режиме КЗ ротора сетевые ИУ сняты и ток через согласующий не течет .
    if ( Irot >= Id_teplo_max )  mSet_AvarMsg ( _Av_Teplo ) ; // В режиме КЗ ток течет только в роторной цепи , Id = 0 .
   #endif
  }
#else
    if ( IDV_g >= Id_teplo_max )   mSet_AvarMsg ( _Av_Teplo ) ;
#endif

#ifdef _ATK_SET // В АР1 Сетевом Инверторе , для вычисления частоты ротора :
      //----------------------------------------------- Скрипт Грыгорыча ------------------------------------------------------

      //------------------------------------------- Число пар полюсов -----------------------------------------
      // Число пар полюсов находим как целочисленное частное Максимальной Синхронной скорости ( 3000 об/ мин )
      // для двигателя с 1 парой полюсов к Номинальной скорости двигателя .                  // Например :
                                                                                             // 3000 ->  Z = 1
      //---                                                                                  // 1500 ->  Z = 2
      Pary_AD = (w)3000 / _or.N_nom ;                                                        // 1000 ->  Z = 3

      //-----------------------------
      // Круговая частота сети w0 , рад/с :
      //
      //   wном = 2 * _PI * f
      //
      OmegaNom = (float)2 * _PI * 50 ; //Syn.Fsyn/360 - измерять частоту сети нет смысла ...

      //-----------------------------
      // Синхронная скорость , рад/с :
      //
      //         wном
      //   w0 = ------
      //          Z
      //
      OmegaNullSynhr = (float)OmegaNom / (float)(w)Pary_AD ;

      //------------------------------
      // Синхронная скорость ротора в Об/мин :
      N_ob_minSynhr = _RadS_ObMin * OmegaNullSynhr ;

      // Для правильного подсчета ПДФ номинальная скорость - это синхронная скорость :
      //if ( _sr.NOM.N.fe != N_ob_minSynhr ) _sr.NOM.N.fe = N_ob_minSynhr ; // Пишем уставку один раз .
      // 21.12.2020 - ПДФ стоит на понижающем валу редуктора :
      // Для правильного подсчета ПДФ номинальная скорость - это номинальная скорость редуктора .
      // Считаем от синхронной скорости 300/11.52 = 26.04 об/мин . Т.е. _sr.NOM.N.fe = 26 об/мин .
      //------------------------------

      // 15.10.2020 - Новая идея Грыгорыча для реверса АТК .
      //              Не нужно дожидаться сброса тока , нужно просто уравнять Напряжение Инвертора с Напряжением Ротора .
      //
      // Udинв  = Uсетном * 1.35 * Cos Bинв ;
      //
      // Udвыпр = Urotном * S * 1.35 * Cos Lrot ;
      //
      // Udинв  = Udвыпр ;
      //
      // Uсетном * 1.35 * Cos Bинв = Urotном * S * 1.35 * Cos Lrot ;
      //
      // Uсетном * Cos Bинв = Urotном * S * Cos Lrot ;
      //
      //             Urotном * S * Cos Lrot
      // Cos Bинв = ------------------------ ;
      //                   Uсетном
      //
      //                  Urotном * S * Cos Lrot
      // Bинв = arccos ( ------------------------ ) ;
      //                        Uсетном
      //
      // Lинв = 180 грд - Bинв ;

      // Определяем , переход в Инвертор или наоборот :
      // Подставляется в интегратор только рассчёт для 6 грд АР2 ( переход АР1 из Выпрямителя в Инвертор ) :
      if ( S.flg._.Invertor == 1 ) CosLrot = cosf( (float)(2 *_PI * (float)(w)_Grad( 120 ) ) / (float)(w)_Grad( 360 ) ) ; // эл.грд. -> Рад
      else                         CosLrot = cosf( (float)(2 *_PI * (float)(w)_Grad(   6 ) ) / (float)(w)_Grad( 360 ) ) ;

      Beta = acosf( (float)(w)_or.Urot_nom * (float)(w)Srot * CosLrot / (float)(w)_Ud_Nom / (float)(w)_or.Uset_nom ) ;

      OIRT_for_revers = (sw)(float)( (_PI - Beta) * (float)(w)_Grad( 360 ) / (2 *_PI) ) ; // Рад -> эл.грд.

      //---------------------------------------- Момент двигателя -------------------------------------------------------------

      // Момент двигателя :
      // М = Kform * Irot * CosLrot_istin ,
      // где Кform - коэффициент формы .
      //---
      // CosLrot из определения интегратора для реверса брать нельзя , т.к. в том случае рассчитывается CosLrot
      // для перехода в другой режим . Поэтому здесь рассчитываем истинный CosLrot_istin :
      if ( S.flg._.Invertor == 1 ) CosLrot_istin = cosf( (float)(2 *_PI * (float)(w)_Grad(   6 ) ) / (float)(w)_Grad( 360 ) ) ; // эл.грд. -> Рад
      else                         CosLrot_istin = cosf( (float)(2 *_PI * (float)(w)_Grad( 120 ) ) / (float)(w)_Grad( 360 ) ) ;
      //---
      // Допущения :
      // 1. Пересчёт для режима КЗ , в котором сплошгые ИУ , т.е. угол управления 0 грд ( диодный режим ) не дедаем , т.к.
      //    разница между Cos 6 грд и Cos 0 грд несущественна .
      // 2. Для принудительной коммутации 170 грд тоже не делаем отдельного рассчёта .

      // Номинальный момент двигателя - произведение номинального действующего тока на Kform :

      Mom_nom = Kform * (float)(w)_sr.NOM.Id.fe * (float)_sqr2_3mask ; //0.816 ;
      Mom     = Kform * (float)(w)Irot * CosLrot_istin ;
      Moment = (sw)(float)( Mom / Mom_nom * (float)(w)_Mom_Nom ) ;

      //-----------------------------------------------------------------------------------------------------------------------
#endif

      //  Контроль внешних аварийных и предупредительных сигналов.
     if ( bi_2P24 != 1 )   //  "КОНТРОЛЬ 2P24"
        {
              //  "ГОТОВНОСТЬ СИЛОВОЙ ЦЕПИ"
          if ( bi_AK1 == 0 )   mSet_AvarMsg( _Av_AK1 ) ;

     #ifdef bi_AK2
              //  "ГОТОВНОСТЬ СИЛОВОЙ ЦЕПИ":
              //   1. Q2 .
              //   2. Для Мощных Агрегатов Q1 во втором силовом шкафу ШС2 .
          if ( bi_AK2 == 0 )   mSet_AvarMsg2( _Av2_AK2 ) ;
     #endif

              //  "ПЕРЕГОРАНИЕ ПЗП - 1AF"
          if ( bi_AF1 == 1 )
            {
              mSet_AvarMsg( _Av_AF1 ) ;
     #ifdef _AF_Otkl_Q1 // 20.05.2009 - Решили отключать в мощных и то по особой договоренности .
              mOtkl_Q1 () ; // 29.02.2008 13:18 - Ковтуненко и Замула решили Q1 отключать .
     #endif
            }

     #ifdef bi_AF2 // Для Мощных Агрегатов :
              //  "ПЕРЕГОРАНИЕ ПЗП - 1AF во втором силовом шкафу ШС2"
          if ( bi_AF2 == 1 )
            {
              mSet_AvarMsg2( _Av2_AF2 ) ;
     #ifdef _AF_Otkl_Q1 // 20.05.2009 - Решили отключать в мощных и то по особой договоренности .
              mOtkl_Q1 () ; // 29.02.2008 13:18 - Ковтуненко и Замула решили Q1 отключать .
     #endif
            }
     #endif

     #ifdef bi_AF1P
              //  "ПЕРЕГОРАНИЕ ПЗП - 1AF"
          if ( bi_AF1P == 1 )   mSet_PreduprMsg( _Pr_AF1P ) ;
     #endif

     #ifdef bi_AF2P // Для Мощных Агрегатов :
              //  "ПЕРЕГОРАНИЕ ПЗП - 1AF"
          if ( bi_AF2P == 1 )   mSet_PreduprMsg2( _Pr2_AF2P ) ;
     #endif

     #ifdef   bi_GL1
      #ifdef   _AVTONASTR
       if ( Isp._.AvtoNastr == 1 && AnastrRT == 0 ) ; // блокировка на время автонастр.
       else
      #endif       //  "НЕИСПРАВНОСТЬ ВОЗБУДИТЕЛЯ"
          {
            if ( bi_GL1 == 1 )   mSet_AvarMsg( _Av_GL1 ) ;
          #ifdef _RVId
            if ( bi_GL2 == 1 )   mSet_AvarMsg2( _Av2_GL2 ) ;
          #endif
          }
     #endif

     #ifdef bi_MT // bi_GY1
              //  "НЕИСПРАВНОСТЬ МЕXАНИЧЕСКОГО ТОРМОЗА"
          //if ( bi_GY1 == 0 )   mSet_AvarMsg2( _Av2_GY1 ) ;

              //  "ТЕXНОЛОГИЧЕСКИЙ СИГНАЛ МЕXАНИЧЕСКОГО ТОРМОЗА"
          if ( bi_MT  == 0 )   mSet_ServiceMsg( _Srv_MT ) ;
          else                 mClr_ServiceMsg( _Srv_MT ) ;
     #endif

     #ifdef bi_SF3
              //  "АВТОМАТ ВСПОМОГАТЕЛЬНЫX УСТРОЙСТВ - Возбудитель, МТ , ТГ и тд"
          if ( bi_SF3 == 0 )   mSet_AvarMsg2( _Av2_SF3 ) ;
     #endif

     #ifdef bi_SFV1
              //  "АВТОМАТ ВЕНТИЛЯТОРА ШС1"
         if ( bi_SFV1 == 0 ) mSet_PreduprMsg2( _Pr2_SFV1 ) ;
     #endif

     #ifdef bi_SFV2
              //  "АВТОМАТ ВЕНТИЛЯТОРА ШС2"
         if ( bi_SFV2 == 0 ) mSet_PreduprMsg2( _Pr2_SFV2 ) ;
     #endif

     #ifdef bi_SFV3
              //  "АВТОМАТ ВЕНТИЛЯТОРА ШС3"
         if ( bi_SFV3 == 0 ) mSet_PreduprMsg2( _Pr2_SFV3 ) ;
     #endif

     #ifdef bi_SFV4
              //  "АВТОМАТ ВЕНТИЛЯТОРА ШС4"
         if ( bi_SFV4 == 0 ) mSet_PreduprMsg2( _Pr2_SFV4 ) ;
     #endif

              //  "КОНТРОЛЬ ИЗОЛЯЦИИ"
          if ( bi_AR1 == 1 )   mSet_PreduprMsg( _Pr_Insulat ) ;  // _Pr_AR1

     #ifdef bi_PR1
          // Перегорание ОДНОГО силового предохранителя в ОДНОМ тиристорном плече .
          // Могут перегореть по одному предохранителю в каждом плече , все равно
          // при этом сработает только "bi_PR1"
          if ( bi_PR1 == 0 ) //  "Силовой предохранитель 1"
            {
              mSet_PreduprMsg( _Pr_PR1 ) ;
          #ifdef bi_BV1
              if ( bi_BV1 == 0 ) mSet_AvarMsg( _Av_PR1 ) ;
          #else
//          #ifdef bi_TK1 20.05.2020 09:48
//            if ( bi_TK1 == 0 ) mSet_AvarMsg( _Av_PR1 ) ;
//          #endif
          #endif
         //---
            }
     #endif

     #ifdef bi_PR2
          // Перегорание ДВУX силовых предохранителей в ОДНОМ тиристорном плече .
          // Могут перегореть по одному предохранителю в каждом плече , все равно
          // при этом сработает только "bi_PR1"
          if ( bi_PR2 == 0 ) //  "Силовой предохранитель 2"
            {
              mSet_AvarMsg( _Av_PR2 ) ;
            }
     #endif

     //------------ Для ШС2 ------------
     #ifdef bi_2PR1
          // Перегорание ОДНОГО силового предохранителя в ОДНОМ тиристорном плече ШС2 .
          // Могут перегореть по одному предохранителю в каждом плече ШС2 , все равно
          // при этом сработает только "bi_2PR1"
          if ( bi_2PR1 == 0 ) //  "Силовой предохранитель 1"
            {
              mSet_PreduprMsg2( _Pr2_2PR1 ) ;
          #ifdef bi_BV1
              if ( bi_BV1 == 0 ) mSet_AvarMsg2( _Av2_2PR1 ) ;
          #else
//          #ifdef bi_TK1 20.05.2020 09:48
//            if ( bi_TK1 == 0 ) mSet_AvarMsg2( _Av2_2PR1 ) ;
//          #endif
          #endif
         //---
            }
     #endif
     #ifdef bi_2PR2
          // Перегорание ДВУX силовых предохранителей в ОДНОМ тиристорном плече ШС2 .
          // Могут перегореть по одному предохранителю в каждом плече ШС2 , все равно
          // при этом сработает только "bi_PR1"
          if ( bi_2PR2 == 0 ) //  "Силовой предохранитель 2"
            {
              mSet_AvarMsg2( _Av2_2PR2 ) ;
            }
     #endif
     //---------------------------------

     #ifdef _KTE_GD
              //  "КОНТРОЛЬ ЛИНЕЙНОГО КОНТАКТОРА в цепи Г-Д"
          if ( bi_LK == 0 )    mSet_ServiceMsg( _Srv_LK ) ;
          else                 mClr_ServiceMsg( _Srv_LK ) ;
     #endif

     #ifdef bi_QKDT
          Control_QKDT () ; //  "КОНТРОЛЬ КОНТАКТОРА ДИНАМИЧЕСКОГО ТОРМОЖЕНИЯ"
     #endif

     #ifdef bo_QKDT
          Upr_QKDT () ; //  "УПРАВЛЕНИЕ КОНТАКТОРОМ ДИНАМИЧЕСКОГО ТОРМОЖЕНИЯ"
     #endif

     #ifdef bi_MB1
              //  "КОНТРОЛЬ Б/К МАСЛЕННИКА"
          if ( bi_MB1 == 0 )   mSet_AvarMsg2( _Av2_MB1 ) ;
     #endif

     #ifdef bi_AM1
              //  "КОНТРОЛЬ СИЛОВОГО НАПРЯЖЕНИЯ"
          if ( bi_AM1 == 0 )   mSet_AvarMsg2( _Av2_AM1 ) ;
     #endif

     #ifdef bi_AM2
              //  "КОНТРОЛЬ СИЛОВОГО НАПРЯЖЕНИЯ - 2"
          if ( bi_AM2 == 0 )   mSet_AvarMsg2( _Av2_AM2 ) ;
     #endif

     #ifdef bi_VAT
              //  "КОНТРОЛЬ ВКЛЮЧЁННОГО ВАТа . Для случая , когда ВАТ - это не последний коммутационный аппапрат"
          if ( bi_VAT   == 0 ) mSet_AvarMsg2( _Av2_VAT ) ;
     #endif

     //#ifdef bi_RV1 - 14.10.2008 11:40 - Пересено в прерывание по Геркону 2В .
     //         //  "Срабатывание РДШ"
     //     if ( bi_RV1 == 1 )   mSet_AvarMsg2( _Av2_RV1 ) ;
     //#endif

     #ifdef bi_RV1_VAT
                // Б/к срабатывания расцепителя ВАТ . Смысла спешить уже нет , т.к. ВАТ уже расцеплен .
          if ( bi_RV1_VAT == 1 ) mSet_AvarMsg3( _Av3_RV1_VAT ) ;
     #endif

     #ifdef bi_SQ1
              //  "ДВЕРНАЯ БЛОКИРОВКА"
          if ( bi_SQ1 == 0 )
            {
        #ifndef _ATK_SET
              mSet_AvarMsg2( _Av2_SQ1 ) ;
          #ifdef _POWER
              bo_MB1_Otkl = 1 ; // отключение Масляного Выключателя
          #else
              mOtkl_Q1 () ; // 29.02.2008 13:18 - Замула решил, если не масленик ,
          #endif            //                    то хотя бы Q1 отключать .
            }
        #else
              mSet_AvarMsg( _Av_SQ1 ) ;
              // Отключать Q1 нет смысла , поэтому нужно выдавать аварию с Ведущего АТК ,
              // даже если она произошла на Ведомом :
              bo_atkSQ1 = 1 ; // Выставляем для соседнего АТК флаг .
              // Кроме того , сообщение занесено в маску выдачи Аварии в Сборке Готовности .
            }
          else bo_atkSQ1 = 0 ; // Сбрасываем для соседнего АТК флаг .

          // Выдаём аварию Ведомого , если АТК - Ведущий :
          if ( ATK2_SQ1 == 1 && flgO._.Vedushiy == 1 && av_label == 0 )
            {
              if      ( ATK2_NmbrATK == 1 ) mSet_AvarMsg( _Av_SQ1_ATK1 ) ;
              else if ( ATK2_NmbrATK == 2 ) mSet_AvarMsg( _Av_SQ1_ATK2 ) ;
              else                          mSet_AvarMsg( _Av_SQ1_ATKR ) ;
            }
        #endif
     #endif

     #ifdef bi_SQ2
          if ( bi_SQ2 == 0 ) //  "ДВЕРНАЯ БЛОКИРОВКА ШК"
            {
              // Отключать Q1 нет смысла , поэтому нужно выдавать аварию с Ведущего АТК ,
              // даже если она произошла на Ведомом :
              mSet_AvarMsg( _Av_SQ2 ) ; // это сообщение занесено в маску выдачи Аварии в Сборке Готовности .
              //---
              // Если у каждого АТК нет собственного ШК и у комплекта АТК всего один ШК ,
              // б/к одного и того же ШК приходят в каждый АТК , то нет смысла
              // говорить о дверях ШК , полученных по сети от второго АТК ...
       #ifndef _ShK_own
            }
       #else
              bo_atkSQ2 = 1 ; // Выставляем для соседнего АТК флаг .
            }
          else bo_atkSQ2 = 0 ; // Сбрасываем для соседнего АТК флаг .

          // Выдаём аварию Ведомого , если АТК - Ведущий :
          if ( ATK2_SQ2 == 1 && flgO._.Vedushiy == 1 && av_label == 0 )
            {
              if      ( ATK2_NmbrATK == 1 ) mSet_AvarMsg( _Av_SQ2_ATK1 ) ;
              else if ( ATK2_NmbrATK == 2 ) mSet_AvarMsg( _Av_SQ2_ATK2 ) ;
              else                          mSet_AvarMsg( _Av_SQ2_ATKR ) ;
            }
       #endif
     #endif

     #ifdef _POWER
              //  "РАЗРЕШЕНИЕ ВКЛЮЧЕНИЯ МАСЛЕНИКА"
              //  ( Двери заперты , Изоляция в норме , QK1 отключен , Нет Несброшенных Аварий ) :
          if ( bi_SQ1 == 1 && bi_AR1 == 0
#ifdef bo_Insulat
                       && bo_Insulat == 0
#endif
                       && bi_QK1 == 0 && bo_Avar == 0 )    bo_MB1_Razr = 1 ;
          else                                             bo_MB1_Razr = 0 ;
     #endif

               // КОНТРОЛЬ ( если есть #define bi_XXX в OBJ.H ) :
               // 1 - Охлаждения ;
               // 2 - Вентиляции ;
               // 3 - Маслосмазки двигателя ;
               // 4 - Смазки подшипников .
          Control_dt_Avar ( 1 ) ;

          if ( bi_Vnesh_Avar == 1 )    mSet_AvarMsg( _Av_Vnesh_Avar ) ;
//   #ifdef  bi_TK1 20.05.2020 09:48
//        if ( bi_TK1 == 0 )           mSet_AvarMsg( _Av_BV1 ) ;
//   #endif
     #ifdef  bi_CentroBegnik
          if ( bi_CentroBegnik == 1 )  mSet_AvarMsg( _Av_CentroBegnik ) ;
     #endif
     #ifdef  bi_Iv_TG
          if ( bi_Iv_TG == 0 )
             #ifndef _Perecl_DS // При неисправности ДС - аварийное отключение ;
                                       mSet_AvarMsg( _Av_Iv_TG ) ;
             #else
             {
               mSet_PreduprMsg( _Pr_Perecl_DS ) ; // При неисправности ДС - переключение на ЭДС .
               _r.Sk_str._.TG = 0 , _r.Sk_str._.PDF = 0 ; // Отключение ТГ и ПДФ .
               _r.Sk_str._.EDS = 1 ;                      // Включение ЭДС .
             }
             #endif
     #endif
     #ifdef  bi_1P
          if ( bi_1P == 0 )            mSet_AvarMsg2( _Av2_1P ) ;
     #endif
     #ifdef  bi_2P
          if ( bi_2P == 0 )            mSet_AvarMsg2( _Av2_2P ) ;
     #endif
     #ifdef  bi_PUM
          if ( bi_PUM == 0 )           mSet_AvarMsg( _Av_PUM ) ;
     #endif
     #ifdef bi_PT // Контроль перегрева тиристоров .
          Control_PT () ;
     #endif
     #ifdef bi_AT
             //  "Авария - перегрев тиристоров."
         if ( bi_AT == 0 )             mSet_AvarMsg2( _Av2_AT ) ;
     #endif
     #ifdef bi_PT2 // Контроль перегрева тиристоров ШС2 .
          Control_PT2 () ;
     #endif
     #ifdef bi_AT2
             //  "Авария - перегрев тиристоров ШС2."
         if ( bi_AT2 == 0 )            mSet_AvarMsg2( _Av2_AT2 ) ;
     #endif

     // Произвол конструкторов Лисиенко :
     // 1й вариант - Общие для всего силового блока б/к перегрева :
     #ifdef bi_BK1
             //  "Предупреждение - перегрев."
         if ( bi_BK1 == 0 )   mSet_PreduprMsg( _Pr_BK1 ) ;
     #endif
     #ifdef bi_BK2
             //  "Авария - перегрев."
         if ( bi_BK2 == 0 )   mSet_AvarMsg2( _Av2_BK2 ) ;
     #endif

     // 2й вариант - предупреждения по б/к перегрева в разных фазах :
     #ifdef  bi_prBK1A
        if ( bi_prBK1A == 0 ) mSet_PreduprMsg3( _Pr3_BK1A ) ;
     #endif
     #ifdef  bi_prBK1B
        if ( bi_prBK1B == 0 ) mSet_PreduprMsg3( _Pr3_BK1B ) ;
     #endif
     #ifdef  bi_prBK1C
        if ( bi_prBK1C == 0 ) mSet_PreduprMsg3( _Pr3_BK1C ) ;
     #endif
     #ifdef  bi_prBK2A
        if ( bi_prBK2A == 0 ) mSet_PreduprMsg3( _Pr3_BK2A ) ;
     #endif
     #ifdef  bi_prBK2B
        if ( bi_prBK2B == 0 ) mSet_PreduprMsg3( _Pr3_BK2B ) ;
     #endif
     #ifdef  bi_prBK2C
        if ( bi_prBK2C == 0 ) mSet_PreduprMsg3( _Pr3_BK2C ) ;
     #endif

     // 3й вариант - аварии по б/к перегрева в разных фазах :
     #ifdef  bi_avBK1A
        if ( bi_avBK1A == 0 ) mSet_AvarMsg3( _Av3_BK1A ) ;
     #endif
     #ifdef  bi_avBK1B
        if ( bi_avBK1B == 0 ) mSet_AvarMsg3( _Av3_BK1B ) ;
     #endif
     #ifdef  bi_avBK1C
        if ( bi_avBK1C == 0 ) mSet_AvarMsg3( _Av3_BK1C ) ;
     #endif
     #ifdef  bi_avBK2A
        if ( bi_avBK2A == 0 ) mSet_AvarMsg3( _Av3_BK2A ) ;
     #endif
     #ifdef  bi_avBK2B
        if ( bi_avBK2B == 0 ) mSet_AvarMsg3( _Av3_BK2B ) ;
     #endif
     #ifdef  bi_avBK2C
        if ( bi_avBK2C == 0 ) mSet_AvarMsg3( _Av3_BK2C ) ;
     #endif

     // 4й вариант - предупреждения с авариями по выдержке по б/к перегрева в разных фазах
     // ( пока не прописано ) .

     #ifdef bi_t_Trans
             //  "Авария - перегрев трансформатора."
         if ( bi_t_Trans == 0 )        mSet_AvarMsg2( _Av2_t_Trans ) ;
     #endif
     #ifdef bi_tw_Trans
             //  "Предупреждение - перегрев трансформатора."
         if ( bi_tw_Trans == 0 )       mSet_PreduprMsg( _Pr_t_Trans ) ;
     #endif
     #ifdef bi_ROP
             //  "Авария - реле обрыва поля."
         if ( bi_ROP == 0 )        mSet_AvarMsg2( _Av2_ROP ) ;
     #endif

     #ifdef  bi_Technol_Ostanov
      if ( bi_Technol_Ostanov == 1 )   mSet_ServiceMsg2( _Srv2_Technol_Ostanov ) ;
      else                             mClr_ServiceMsg2( _Srv2_Technol_Ostanov ) ;
     #endif

     // Для раздельной работы 12-пульсной схемы :
     #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
          if ( Prg._.Gotovn == 1 ) // Отключать/Включать мосты можно только в Сборке Готовности :
          {
             if ( Name_Agr == 2 ) // только ведущий мост , 6-ти пульсная схема :
             {
               S.Disable = 0, S2.Disable = 1; // Отключаем ИУ СИФУ2 .
               mSet_ServiceMsg2( _Srv2_VedomOtkl ), mClr_ServiceMsg2( _Srv2_VeduschOtkl ) ;
             }
             else if ( Name_Agr == 3 ) // только ведомый мост , 6-ти пульсная схема :
             {
               S.Disable = 1, S2.Disable = 0; // Отключаем ИУ СИФУ1 .
               mClr_ServiceMsg2( _Srv2_VedomOtkl ), mSet_ServiceMsg2( _Srv2_VeduschOtkl ) ;
             }
             else if ( Name_Agr == 1 ) // Включены оба моста, 12-ти пульсная схема :
             {
               S.Disable = 0, S2.Disable = 0;
               mClr_ServiceMsg2( _Srv2_VeduschOtkl ) ; // На всякий случай .
               mClr_ServiceMsg2( _Srv2_VedomOtkl ) ;   // На всякий случай .
             }
             else // if ( Name_Agr == 0 ) // Объект не выбран :
             {
               S.Disable = 1, S2.Disable = 1;
               mSet_ServiceMsg2( _Srv2_VedomOtkl ), mSet_ServiceMsg2( _Srv2_VeduschOtkl ) ;
             }
          }
          else // В работе нельзя выполнять переключения мостов :
          {
             //---
             // if ( Name_Agr == 1 ) - включены оба моста, 12-ти пульсная схема
             // if ( Name_Agr == 2 ) - включен только ведущий мост, 6-ти пульсная схема
             // if ( Name_Agr == 3 ) - включен только ведомый мост, 6-ти пульсная схема
             //---
             if      ( Name_Agr == 1 && ( bi_Vedom == 1 || bi_Vedusch == 1 || bi_Both == 0 ) ) mSet_PreduprMsg2( _Pr2_No_PereclMost ) ;
             else if ( Name_Agr == 2 && ( bi_Vedom == 1 || bi_Vedusch == 0 || bi_Both == 1 ) ) mSet_PreduprMsg2( _Pr2_No_PereclMost ) ;
             else if ( Name_Agr == 3 && ( bi_Vedom == 0 || bi_Vedusch == 1 || bi_Both == 1 ) ) mSet_PreduprMsg2( _Pr2_No_PereclMost ) ;
             else      mClr_PreduprMsg2( _Pr2_No_PereclMost ) ; // Очищаем старое предупреждение .
          }

          // Контроль исправности переключателя Мостов :
          if    ( ( bi_Vedusch == 1 && bi_Vedom == 1 ) ||
                  ( bi_Vedusch == 1 && bi_Both  == 1 ) ||
                  ( bi_Vedom   == 1 && bi_Both  == 1 ) ||
                  ( bi_Vedusch == 0 && bi_Vedom == 0 && bi_Both == 0 ) )
          {
               mSet_ServiceMsg3( _Srv3_NeisprPerekl ) ;
          }
          else mClr_ServiceMsg3( _Srv3_NeisprPerekl ) ; // Очистка старых сообщений .
          //----
     #endif

        }
     else   mSet_AvarMsg( _Av_2P24 ) ;

//---
#ifndef _KTE_GD
  #define  _Srv_Oprobovanie  0
#endif
//---     // Выводим сообщ.о налад.режиме, если задан какой-либо из них
          // кроме опробования, т.к. для опробования есть свое сообщение.
      mClr_ServiceMsg( _Srv_F2_regim | _Srv_Oprobovanie ) ;
      if ( Isp.all != 0 )
      {
         if ( Isp._.Oprobov == 1 ) mSet_ServiceMsg( _Srv_Oprobovanie ) ;
         else                      mSet_ServiceMsg( _Srv_F2_regim ) ;
      }

      //---
      // В наладочных режимах встроенного возбудителя не нужно заходить в работу .
      // Взводим само сообщение , а не бит Isp._.Predupr , т.к. его еще придется
      // правильно сбросить , чтобы он не исчез в режиме Фазировки :
      if ( Isp._.SIFUV_Res == 1 || Ckl._.RTV == 1 || Ckl._.SIFUV == 1 ) mSet_PreduprMsg( _Pr_ServiceProg ) ;

#ifdef _KTE_GD
          // Если выбрано опробование , но не подана команда разблокировки :
      if ( bi_Oprobov == 1 && bi_Blokir == 0 ) mSet_ServiceMsg( _Srv_Blokir ) ;
      else                                     mClr_ServiceMsg( _Srv_Blokir ) ;
#endif

     // Для раздельной работы 12-пульсной схемы :
     #if defined(bi_Vedusch) && defined(bi_Vedom) && defined(bi_Both)
          // После вывода всех сообщений , затираем ненужные , в зависимости от области уставок :
          if ( Name_Agr == 3 ) // только ведомый мост , 6-ти пульсная схема :
           {
              // На ВСЕ (кроме геркона и Id-Max) Предупреждения и Аварии Ведущего моста не реагируем :
              //----- для 12-ти пульсной схемы с одним ШС в каждом мосту :
              if ( ( Reg_AvarMsg     & _Av_AK1        ) != (lw)r0 ) mClr_AvarMsg(  _Av_AK1  ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AM1       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AM1 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AT        ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AT   ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_PT        ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_PT) ;
              if ( ( Reg_AvarMsg     & _Av_AF1        ) != (lw)r0 ) mClr_AvarMsg( _Av_AF1) ;
              if ( ( Reg_PreduprMsg  & _Pr_AF1P       ) != (lw)r0 ) mClr_PreduprMsg( _Pr_AF1P) ;
              if ( ( Reg_PreduprMsg  & _Pr_BV1        ) != (lw)r0 ) mClr_PreduprMsg( _Pr_BV1 ) ;
              if ( ( Reg_AvarMsg     & _Av_BV1        ) != (lw)r0 ) mClr_AvarMsg( _Av_BV1 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KP        ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KF_VKask  ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask  ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_SFV1      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV1 ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK1A      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK1A ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK1B      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK1B ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK1C      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK1C ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK1A      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK1A ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK1B      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK1B ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK1C      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK1C ) ;

              //----- для 12-ти пульсной схемы с двумя ШС в каждом мосту :
              //----- ( сделать на будущее условную компиляцию - количество ШС в мосту )
            //if ( ( Reg_AvarMsg2    & _Av2_KP2       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP2 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KF_VKask2 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask2 ) ;
            //if ( ( Reg_PreduprMsg2 & _Pr2_SFV2      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV2 ) ;
           }
         //---
          if ( Name_Agr == 2 ) // только ведущий мост , 6-ти пульсная схема :
           {
              // На ВСЕ (кроме геркона и Id-Max) Предупреждения и Аварии Ведомого моста не реагируем :
              //----- для 12-ти пульсной схемы с одним ШС в каждом мосту :
              if ( ( Reg_AvarMsg2    & _Av2_AK2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AK2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AM2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AM2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_AT2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AT2   ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_PT2       ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_PT2) ;
              if ( ( Reg_AvarMsg2    & _Av2_AF2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_AF2) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_AF2P      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_AF2P ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_BV2       ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_BV2  ) ;
              if ( ( Reg_AvarMsg2    & _Av2_BV2       ) != (lw)r0 ) mClr_AvarMsg2( _Av2_BV2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KP2       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP2 ) ;
              if ( ( Reg_AvarMsg2    & _Av2_KF_VKask2 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask2 ) ;
              if ( ( Reg_PreduprMsg2 & _Pr2_SFV2      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV2 ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK2A      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK2A ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK2B      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK2B ) ;
              if ( ( Reg_PreduprMsg3 & _Pr3_BK2C      ) != (lw)r0 ) mClr_PreduprMsg3( _Pr3_BK2C ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK2A      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK2A ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK2B      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK2B ) ;
              if ( ( Reg_AvarMsg3    & _Av3_BK2C      ) != (lw)r0 ) mClr_AvarMsg3( _Av3_BK2C ) ;

              //----- для 12-ти пульсной схемы с двумя ШС в каждом мосту :
              //----- ( сделать на будущее условную компиляцию - количество ШС в мосту )
            //if ( ( Reg_AvarMsg2    & _Av2_KP3       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP3 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KP4       ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KP4 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KF_VKask3 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask3 ) ;
            //if ( ( Reg_AvarMsg2    & _Av2_KF_VKask4 ) != (lw)r0 ) mClr_AvarMsg2 ( _Av2_KF_VKask4 ) ;
            //if ( ( Reg_PreduprMsg2 & _Pr2_SFV3      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV3 ) ;
            //if ( ( Reg_PreduprMsg2 & _Pr2_SFV4      ) != (lw)r0 ) mClr_PreduprMsg2( _Pr2_SFV4 ) ;
           }
     #endif

      // Программа тестирования "Контроль Пробоя Тиристоров" обнаружила пробитые тиристоры .
      if ( flg_RaTe._.tyr_tst_pr == 1 ) mSet_ServiceMsg2( _Srv2_Proboy_Tyr ) ;
      else                              mClr_ServiceMsg2( _Srv2_Proboy_Tyr ) ;

       // При работе программы тестирования "Контроль Пробоя Тиристоров" сработали токовые защиты .
      if ( flg_RaTe._.tyr_tst_av == 1 ) mSet_ServiceMsg2( _Srv2_ZashProboy_Tyr ) ;
      else                              mClr_ServiceMsg2( _Srv2_ZashProboy_Tyr ) ;

#ifdef _INTERPRETER
    if (ObjSrv_bit._.Avar)    mSet_PreduprMsg2( _Pr2_NoObjPrg ) ;
#endif

   return 0 ;
 }

//-----------------------------

void  Sborka_Gotovn ( void )
{
   #ifndef _KTE_GD
    static   word time_QK ;
    register lword lax ;
   #endif
    register word ax ;

      //   Сброс всех аварийных сообщений (в т.ч. и первого)
      // кроме сообщений об герконах и предохранителях (перечисленых в маске) :
    mClr_AvarMsg ( _Av_All & ~_Mask_AvarSbr  ) ;
    mClr_AvarMsg2( _Av_All & ~_Mask_AvarSbr2 ) ;
#ifdef _TRETIY_REG
    mClr_AvarMsg3( _Av_All ) ;
#endif
#ifdef _INTERPRETER
    mClr_AvarMsg_obj( _Av_All ) ;
#endif

      //   Сброс всех предупредительных сообщений , кроме перечисленых в маске :
    mClr_PreduprMsg  ( _Pr_All & ~_Mask_PreduprSbr  ) ;
    mClr_PreduprMsg2 ( _Pr_All & ~_Mask_PreduprSbr2 ) ;
#ifdef _TRETIY_REG
    mClr_PreduprMsg3( _Pr_All ) ;
#endif
#ifdef _INTERPRETER
    mClr_PreduprMsg_obj( _Pr_All ) ;
#endif

      //   Сброс (выборочный) сервисных сообщений , перечисленых в маске :
    mClr_ServiceMsg ( _Mask_ServiceSbr  ) ;
    mClr_ServiceMsg2( _Mask_ServiceSbr2 ) ;
#ifdef _TRETIY_REG
    mClr_ServiceMsg3( _Srv_All & ~_Mask_ServiceSbr3 ) ;
#endif
#ifdef _INTERPRETER
    mClr_ServiceMsg_obj( _Srv_All ) ;
#endif


              //  "ДИСТАНЦИОННЫЙ СБРОС"
#ifndef _ATK_SET
    if ( can_ConfigReg ( _CAN_DistSbros ) == 1 )   goto sbr ;
    if ( bi_DS1 == 1 )   Av._.DistSbros = 1 ;
    else  if ( Av._.DistSbros == 1 )
    {
  sbr:Init_posle_DistSbr () ;
    }
#else // Переделываем сброс по переднему фронту и уровню только для АТК .
    DistSbros () ;  //  Центариз.обработка дист.сброса.
        //---
    if ( Av._.DistSbros == 1 )   Init_posle_DistSbr () ;
#endif

    Perekl_rezerv( 1, read_rezerv()) ;// Перезагрузка уставок рабочего резерва.

    MechTorm_upr ( _MT_Upr ) ;

    Common_avar() ;

    can_ConfigReg ( _CAN_Ostanov ) ;// для контроля наличия связи по CAN.

      // Если ОЗУ испорчено установить сообщение .
    //if ( Sch_Byte |= 0 )   mSet_ServiceMsg( _Srv_OZU_Isporch ) ;

      //  Контроль внешних аварийных и предупредительных сигналов.
     if ( bi_2P24 != 1 )   //  "КОНТРОЛЬ 2P24"
        {
    #ifdef _KTE_GD    //  "ПОСЛЕДНИЙ КОММУТАЦИОННЫЙ АППАРАТ"
          if ( bi_QK1 == 0 )  mSet_PreduprMsg( _Pr_Q1 ) ;
              // если нет разрешения вкл. КТЭВ-ГД  в готовности
          if ( bi_Razresh_Vkl == 0 )  mSet_PreduprMsg( _Pr_RazreshVkl_KTE ) ;
        }
    #else
       if( _r.Cfg2._.VR1 == 1 )
       {
       //#ifndef _1VR_GOTOVN // Если выдача Готовности при наличии VR1 - то сообщение "Оперативное отключение" не выводим .
          //  "КОМАНДА ОПЕРАТИВНОГО ОТКЛЮЧЕНИЯ"
          if ( bi_VR1 == 1 || Prz._.VR1 == 1 )    mSet_ServiceMsg( _Srv_VR1 ) ;
       //#else
       }
       else
       {
          // Главное - НЕ ПОТЕРЯТЬ сообщение 1VR , в противном случае , если вход bi_VR1 есть , то сообщений не будет ,
          // Готовность будет , а вот в Работу агрегат не войдёт , пока вход bi_VR1 не пропадёт ...
          if ( Prz._.VR1 == 1 )    mSet_ServiceMsg( _Srv_VR1 ) ;
       //#endif
       }
              //   Откл. QK при выходе из работы по 1VR: держим 2сек признак
          if ( Prz._.VR1 == 1 )// Prz._.VR1, который разбирает bo_Gotov, чтобы
          {                   // успел отпасть контактор.
            if ( bi_QK1 == 0 )  Prz._.VR1 = 0 ;
            else if ( (u)((b)(Timer1_Ovr-time_VR1)) > _Sec(2.0)) 
            {
              Prz._.VR1 = 0 ;
              mClr_ServiceMsg( _Srv_VR1 ) ;
            }
          }
        }
        // 26.01.07 18:28 - Возможность включить КТЭ на ВРАЩАЮЩИЙСЯ ДВИГАТЕЛЬ :
     // Проверка вращения двигателя ( а для ГД в работе ) :
     if ( _r.Cfg._.Vrasch_Dvig == 0 ) Control_Skor () ;
    #endif
            // Проверка присутствия задания на скорость.
          if ( _r.Cfg._.Control_ZSk == 1 )
            {
              ax = Z_Skor ;
              if ( (sw)ax < 0 )  ax = ~ax + 1 ;

              if ( ax > _r.Ostanov_skor )
                {
                  mSet_PreduprMsg( _Pr_Podano_ZSk   ) ;
            }   }
                                                    //0 DAN 20.05.2016 - Дал маленький допуск на сбитый АЦП .
    if ( Isp._.SIFU_Res == 1 && (sw)zad_res.out > (sw)5 )  mSet_PreduprMsg( _Pr_Podano_ZSk ) ;
    if ( Isp._.RT_Res   == 1 && (sw)zad_res.out > (sw)5 )  mSet_PreduprMsg( _Pr_Podano_ZSk ) ;

      // Вызов объектной программы после проверки всех защит
    ObjPrg ( _Obj_c_Sborka_Gotovn ) ; // чтобы была полная картина.

      //   Проверка наличия Аварийных и Предупредительных сигналов  и
      // их выдача в порт.
          // Только при аварии по геркону отрабатывает выходной бит Авария :
    if ( ((Reg_AvarMsg | Reg_AvarMsgFirst) & (_Mask_Avar) )
                                        != (lw)r0 )  bo_Avar = 1 ;
#ifdef bo_Avar_Yach
          // 13.06.2021 - Выдаём Аварию для отключения ячейки Согласующего Трансформатора .
          // Только при аварии по геркону и дверях отрабатывает выходной бит Авария
          // для отключения ячейки Согласующего трансформатора :
    if ( ((Reg_AvarMsg | Reg_AvarMsgFirst) & (_Mask_Avar) )
                                        != (lw)r0 )  bo_Avar_Yach = 1 ;
#endif
          // маскируем герконы в Предупреждении , т.к. они отработали в Аварии :
#ifndef _KTE_GD
    if( _r.Cfg2._.VR1 == 1 ) lax = _Mask_AvarPreduprGotovn;
    else                     lax = _Mask_AvarPreduprGotovn | _Av_VR1;
    if ( ( ((Reg_AvarMsgFirst | Reg_AvarMsg) & ~lax )
#else
    if ( ( ((Reg_AvarMsgFirst | Reg_AvarMsg) & ~( _Mask_AvarPreduprGotovn ))
#endif
       | (Reg_PreduprMsg & ~(mask_predupr
          #ifdef _KTE_GD // маскируем предупреждение об отсуствии Разреш.вкл-я :
              | _Pr_RazreshVkl_KTE
          #endif
                            ))
       | (Reg_AvarMsgFirst2 | Reg_AvarMsg2)|(Reg_PreduprMsg2 & ~(mask_predupr2))
#ifdef _TRETIY_REG
       | (Reg_AvarMsgFirst3 | Reg_AvarMsg3)|(Reg_PreduprMsg3 & ~(mask_predupr3))
#endif
#ifdef _INTERPRETER
       | (Reg_AvarMsgFirst_obj | Reg_AvarMsg_obj)|(Reg_PreduprMsg_obj & ~(mask_predupr_obj))
#endif
                              ) != (lw)r0 )  bo_Predupr = 1 ;
    else                                     bo_Predupr = 0 ;

      //  Завершающая проверка готовности КТЭ .
  //bo_Gotov = 0 ; 03.02.2011 11:07 Перенесено вниз , чтобы в CAN-переменной "Po0" не сбрасывалась Готовность ,
                  // т.к. Po0_c.all ( который берётся в VAR_TAB.H ), изменяется в любой части программы .
    bo_canGotov = 0 ;     // чтобы не разваливался ЛК при переходе в Сб.Г. по CAN
 #ifdef _ATK_SET
    bo_SA_canGotov = 0 ; //DAN 12.04.2025
    bo_atkGotov = 0 ;
    bo_ATK () ; // Формирование дискретных выходов АТК в конце , чтобы была полная картина .
 #endif
 #ifdef _KTE_GD
    bo_Vkl_LK = 0 ;
      //---
         // Если опробование в сочетании с блокировкой.
    Isp._.Oprobov = 0 ;
    if ( bi_Oprobov == 1 && bi_Blokir == 0 ) Isp.all = 0 , Isp._.Oprobov = 1 ;
 #endif
    //---

    // Нет аварий , нет предупреждений :
    if ( bo_Avar == 0 && bo_Predupr == 0 )
    {
      // 05.03.2018 13:15 DAN - Готовность включаем до проверки проверки пробоя тиристоров , чтобы у агрегатов ,
      //                        последним коммутационным агрегатом которых является 3х фазный контактор ,
      //                        он включился по готовности и тест пробоя прошел при наличии силового напряжения .
      //
      //                        Для этого еще требуется в OBJ_DEF.H задать строку _KONTAKTOR_for_ProboyTir ...
      bo_Gotov = 1 ;
      bo_canGotov = 1 ;  
      bo_SA_canGotov = 1 ; //DAN 12.04.2025
      bo_atkGotov = 1 ;
 
      
      //---
#if defined (Itt_ach) || defined (Itt1_ach) || defined (_Id_on_Itt_for_ProboyTir) //|| defined (Itt2_ach)
    // Нет аварий , нет предупреждений и тест на пробой тиристора окончен ( или тестирование отключено ) :
      if ( (_r.Cfg2._.ProboyTir == 1 && flg_RaTe._.tyr_tst_ok == 1 &&
            flg_RaTe._.tyr_tst_pr == 0 && flg_RaTe._.tyr_tst_av == 0) || _r.Cfg2._.ProboyTir == 0 )
#endif
      {
             //  "Опробование"
    #ifdef _KTE_GD
             //  Переходим в работу по опробов. если задан налад.режим.
        if ( bi_Oprobov == 1 && Isp.all != 0 ) goto  xx ; // в обход разрешения

        if ( bi_Razresh_Vkl == 1 )  // Разрешениe вкл. КТЭ - старт.
        {
    #else   // При кратковременном нажатии Пуск, держим команду на вкл. ЛК не
        if ( bo_Vkl_QK1 == 1 ) // менее 4сек. и если ЛК не включился, то снимаем ее.
        {
          if ((u)((w)(Timer1_Ovr-time_QK)) > _Sec( 4.0 )) bo_Vkl_QK1 = 0 ;
        }
        else  time_QK = Timer1_Ovr ;
        
        if ( bi_Razresh_Vkl == 0 )  mSet_PreduprMsg( _Pr_RazreshVkl_KTE ) ;
        else  mClr_PreduprMsg( _Pr_RazreshVkl_KTE ) ;

          //----
    //  #ifdef _KTE_5
        // В "F2-Наладке" и при откл."CAN-упр.ЛК" - Разрешениe вкл. КТЭ - старт.
        if ( (can_ConfigReg ( _CAN_QK ) == 0 && (bi_Razresh_Vkl == 1 || bo_Vkl_QK1 == 1))
                                             || // или при вкл."CAN-упр.ЛК" при
              can_ConfigReg ( _CAN_QK ) == 1 )  // приходе соотв. СAN-команды .
     // #endif
        {
          bo_Vkl_QK1 = 1 ; // пока есть ком. Пуск держим ком.на вкл.ЛК.
          // 15.03.2021 DAN - добавил контроль признака Оперативного отключения .
          if ( bi_QK1 == 1 && ( (_r.Cfg2._.VR1 == 1 && bi_VR1 == 0) || _r.Cfg2._.VR1 == 0 ) && Prz._.VR1 == 0 ) // "ПОСЛЕДНИЙ КОММУТАЦИОННЫЙ АППАРАТ"
    #endif // 14.08.2012 - контроль bi_VR1 добавлен для агрегатов с выдачей Готовности при наличии 1VR .
          {   //mVkl_Imp( _VR1_imp | _Start_imp ) ;
              goto xx ; // заглушка, чтобы не возмущался компил. на пустую 'xx:'.
          xx: Prg.all = _Sled | _Blok_upr ;
              DWelcome = "\r\nDr>" ,  MWelcome = "\r\nMr>", AWelcome = _RWell_txt;  ;
              //bo_Vkl_Vent = 1;
              upr_label = 0 ;
          }
        }
      }
    }
    else // Если "Готовности" нет ( есть "Предупреждения" и "Аварии" ) :
    {
        bo_Gotov = 0 ; // 03.02.2011 11:07 Перенесено сверху , чтобы обнулялось в одном месте .
 #ifndef _KTE_GD
        bo_Vkl_QK1 = 0 ;
 #endif
    }
      //    Фиксация времени изменения количества сообщений для
      //  распечатки его по "Enter" в режиме "A1".
    //check_msg_time ()  ; //это уже есть в system.c  24.02.09 15:50
    // закомментировано "check_msg_time()" 11.04.2014 11:49 т.к. за цикл он должен вызываться 1 раз в "System_prg()"
  return ;
}
//------------------------------------------------


void  Rabota ( void )
{
      //   04.10.05 10:46
      //   Сброс предупредительных сообщений .
  //  mClr_PreduprMsg  ( _Pr_All & ~( _Pr_P24 | _Pr_P12 | _Pr_N12 | _Pr_DZVA | _Pr_DZVK) ) ;
  //  mClr_PreduprMsg2 ( _Pr_All & ~( _Pr2_ | _Pr2_ )
//-------

#ifdef _ATK_SET // Переделываем сброс по переднему фронту и уровню только для АТК .
    DistSbros () ;  //  Центариз.обработка дист.сброса.

          //  "ДИСТАНЦИОННЫЙ СБРОС" ПРЕДУПРЕЖДЕНИЙ ПО ХОДУ РАБОТЫ.
    if ( Av._.DistSbros == 1 ) // Переделываем сброс по переднему фронту и уровню только для АТК .
      {
        Reg_PreduprMsg  = 0 , Reg_ServiceMsg  = 0 , mask_predupr  = 0 ;
        Reg_PreduprMsg2 = 0 , Reg_ServiceMsg2 = 0 , mask_predupr2 = 0 ;
#ifdef _TRETIY_REG
        Reg_PreduprMsg3 = 0 , Reg_ServiceMsg3 = 0 , mask_predupr3 = 0 ;
#endif
#ifdef _INTERPRETER
        Reg_PreduprMsg_obj = 0 , Reg_ServiceMsg_obj = 0 , mask_predupr_obj = 0 ;
#endif
#ifdef  bo_DS_MT       // Для дистанционногои сброса платы МТ .
        bo_DS_MT = 1 ; // Взводим , через 300 мс он сбросится в Common_avar() .
#endif
      }
#endif

    MechTorm_upr ( _MT_Upr ) ;

    Common_avar() ;

//-------

    if ( bi_2P24 != 1 )   //  "КОНТРОЛЬ 2P24"
      {
    //-------   Проверка отключенности "ПОСЛЕДНЕГО КОММУТАЦИОННОГО АППАРАТА" .

    //---
    #ifdef _KTE_GD   // Для ГД в наладочных режимах блокируем контроль линейника,
    //---
          if ( bi_QK1 == 0 )
          {
            mSet_PreduprMsg( _Pr_Q1 ) ;
            mSet_AvarMsg( _Av_VR1 ) ;
          }

          // блокируем на время опробования : разреш.вкл.ЛК , контроль
          // вращения двигателя и остаточного намагничивания генератора :

          // Завершение опробования только когда отключен тумблер опробования . А когда отпущена кнопка блокировки
          // мы только обнуляем задание на опробование в UPRAVL.C :
          if ( Isp._.Oprobov == 1 && (/*bi_Blokir == 1 ||*/ bi_Oprobov == 0)) mSet_AvarMsg( _Av_VR1 ) ;

        //if ( bi_Razresh_Vkl == 0 && bi_Oprobov == 0 )  // если нет разрешения вкл. КТЭ
        //20.03.2009 11:32 - DAN . Нужно ориентироваться на режим опробования , а не на вход :
          if ( bi_Razresh_Vkl == 0 && Isp._.Oprobov == 0 )  // если нет разрешения вкл. КТЭ
          {
            mSet_PreduprMsg( _Pr_RazreshVkl_KTE ) ; // установить предупредительное сообщение
            mSet_AvarMsg( _Av_VR1 ) ;
          }
            //---
          //if ( bi_LK == 0 && bo_Gotov == 1 ) // если ЛК еще не включен ,
          if ( bi_LK == 0 && bo_Avar == 0 ) // если ЛК еще не включен , i net avarii :
          {
            // Проверка вращения двигателя и остаточного намагничивания ген. :
            if ( Control_Skor() == 0 && Control_UgOstat() == 0 ) bo_Vkl_LK = 1 ; // разрешение включения ЛК .
            else                                                 bo_Vkl_LK = 0 ;
          }
    //---
    #else    // Для КТЭ.
    //---
        if ( bi_QK1 == 0 )   //  Если пропал блок-контакт ЛК :
          {
            if ( bo_Avar == 0 && // Не было ни аварии , ни местного или сетевого оперативного отключения =>
                 ( ( can_ConfigReg ( _CAN_QK ) == 0 && ( _r.Cfg2._.VR1 == 1 && bi_VR1 == 0 ) ) ||
                     can_ConfigReg ( _CAN_QK ) == 1 ) )
              { //Отключаем когда исчезнет ток нагрузки ( 2% добавляем на случай, если _r.Id_Min=0 и нуль АЦП сбит ) :
                if ( ( S.Disable == 0 && IDV <= (_r.Id_Min + _Id_nom (0.02)) )
            #ifdef _SIFU2_ // DAN 23.05.2017 14:46 - При работе только ШС2 :
                  || ( S.Disable == 1 && IDV2 <= (_r.Id_Min + _Id_nom (0.02)) )
            #endif
                                                                                )
                {
                     mSet_AvarMsg( _Av_QK1_SamoOtkl ) ; // самоотключение.
                }
                else mSet_ServiceMsg2(_Srv2_NeisprQK1_bk ) ; // если есть ток .
          }   }

          //  "КОМАНДА ОПЕРАТИВНОГО ОТКЛЮЧЕНИЯ" - Местная или Сетевая:
        if ( ( can_ConfigReg ( _CAN_QK ) == 0 && (( _r.Cfg2._.VR1 == 1 && bi_VR1 == 1 ) || ( _r.Cfg2._.VR1 == 0 && bi_QK1 == 0 ))) ||
               can_ConfigReg ( _CAN_QK ) == 2 )
          {
            mSet_AvarMsg( _Av_VR1 ) ;
            Prz._.VR1 = 1 ;
          }
    //---
    #endif
    //---
      }

      // Вызов объектной программы после проверки всех защит
    ObjPrg ( _Obj_c_Rabota ) ; // чтобы была полная картина.

//------- Проверка наличия Предупредительных сигналов и выдача их в порт.

    if ( ( (Reg_PreduprMsg  & ~mask_predupr ) |
           (Reg_PreduprMsg2 & ~mask_predupr2)
#ifdef _TRETIY_REG
         | (Reg_PreduprMsg3 & ~mask_predupr3)
#endif
#ifdef _INTERPRETER
         | (Reg_PreduprMsg_obj & ~mask_predupr_obj)
#endif
                                              ) != (lw)r0 ) bo_Predupr = 1 ;
    else                                                    bo_Predupr = 0 ;

 #ifdef _ATK_SET
    bo_ATK () ; // Формирование дискретных выходов АТК в конце , чтобы была полная картина .
 #endif

//------- Проверка наличия Аварийных сигналов и выдача их в порт.

switch( av_label )
{
  default :
  case 0  :

    ObjPrg ( _Obj_c_Avar_Otkl )  ; // защита отключаемая после срабатывания защиты.

#ifndef _ATK_SET
          //  "ДИСТАНЦИОННЫЙ СБРОС" ПРЕДУПРЕЖДЕНИЙ ПО ХОДУ РАБОТЫ.
    if ( can_ConfigReg ( _CAN_DistSbros ) == 1 )   goto sbr1 ;
    if ( bi_DS1 == 1 )    Av._.DistSbros = 1 ;
    else  if ( Av._.DistSbros == 1 )
      {
  sbr1: Av._.DistSbros = 0 ;
        Reg_PreduprMsg  = 0 , Reg_ServiceMsg  = 0 , mask_predupr  = 0 ;
        Reg_PreduprMsg2 = 0 , Reg_ServiceMsg2 = 0 , mask_predupr2 = 0 ;
#ifdef _TRETIY_REG
        Reg_PreduprMsg3 = 0 , Reg_ServiceMsg3 = 0 , mask_predupr3 = 0 ;
#endif
#ifdef _INTERPRETER
        Reg_PreduprMsg_obj = 0 , Reg_ServiceMsg_obj = 0 , mask_predupr_obj = 0 ;
#endif
#ifdef  bo_DS_MT       // Для дистанционногои сброса платы МТ .
        bo_DS_MT = 1 ; // Взводим , через 300 мс он сбросится в Common_avar() .
#endif
      }
#endif
//------- Регистрация первых аварий. -------------------

    // 04.11.2011 9:25 - Перенесено сюда сверху для того , чтобы правильно регистрировать
    // первую аварию при входе в объектную программу по ветке _Obj_c_Avar_Otkl .
    // Если авария фиксировалась при этом входе , то она не заносилась в регистр
    // первых аварий и происходило не аварийное отключение агрегата , а оперативное .

    //mSetF_AvarMsg  ( Reg_AvarMsg  ) ; // Будет зафиксирована первая авария
    //mSetF_AvarMsg2 ( Reg_AvarMsg2 ) ; // только из одного регистра из двух.
    // 26.07.2013 10:45 - Будут зафиксированы первые аварии из ВСЕX доступных регистров ,
    // но при условии , что они ВСЕ возникли на ЭТОМ такте :
    SetF_AvarMsg () ;

    if ( ( Reg_AvarMsgFirst | Reg_AvarMsgFirst2
#ifdef _TRETIY_REG
                            | Reg_AvarMsgFirst3
#endif
#ifdef _INTERPRETER
                            | Reg_AvarMsgFirst_obj
#endif
                                                  ) != (lw)r0 ) // Тест всех аварий.
      {
        mSdvig_Imp()  ;   // Команда на задвигание УИ в АльфаМакс.
        Prg.all = 0 ;//21.02.06 15:50 _Sled ;
        SCHCIKL = 0, YKST = 0 ; // 21.01.2021 Чтобы ступени Циклов начинать с начала.
        // Если в системе верхнего уровня из-за этого все развалится ,
        // переставить bo_canGotov = 0 в отключение по аварии ниже ...
        bo_canGotov = 0 ; // для блокировки регуляторов во внешней системе.
     #ifdef _ATK_SET
        bo_SA_canGotov = 0 ; //DAN 12.04.2025
        bo_atkGotov = 0 ;
     #endif
     #ifdef _KTE_GD
        bo_Gotov = 0 ;  // моргнуть Готовностью для ГД чтобы откл. контактор двиг. при штатном откл.
        bo_Vkl_LK = 0 ;
     #else
        bo_Vkl_QK1 = 0 ;
     #endif
      #ifdef bo_Avar_Yach
          // 13.06.2021 - Выдаём Аварию для отключения ячейки Согласующего Трансформатора .
          // Только при аварии по геркону и дверях отрабатывает выходной бит Авария
          // для отключения ячейки Согласующего трансформатора :
        if ( ((Reg_AvarMsg | Reg_AvarMsgFirst) & (_Mask_Avar) )
                                        != (lw)r0 )  bo_Avar_Yach = 1 ;
      #endif
          // Проверка первопричины - "ОПЕРАТИВНОГО ОТКЛ.":
          // если кроме опер.откл. есть и другие аварии то отрабатыв. аварию.
      #ifdef _ATK_SET  // Отключение силы - тоже оперативное отключение :
        if ( ((Reg_AvarMsgFirst & ~(_Av_VR1 | _Av_NoSynch2) ) | Reg_AvarMsgFirst2
      #else
        if ( ((Reg_AvarMsgFirst & ~_Av_VR1 ) | Reg_AvarMsgFirst2
      #endif
#ifdef _TRETIY_REG
                                             | Reg_AvarMsgFirst3
#endif
#ifdef _INTERPRETER
                                             | Reg_AvarMsgFirst_obj
#endif
                                                                    ) != (lw)r0 )
          {    // Отключение по аварии.
            DWelcome = "\r\nDa>" ,  MWelcome = "\r\nMa>", AWelcome = _AvWell_txt;
            bo_Avar = 1 ;
            //bo_canAvar = 1 ; // 20.09.06 16:34 находится в CAN_OBJ.C .
            bo_Gotov = 0 ;
          #ifdef _POWER
            bo_MB1_Razr = 0 ;
          #endif
        #ifndef _ATK_SET
            if ( _r.Cfg._.Kontaktor == 1 )
              {  // Условие истинно только при аварии _Av_IdMax ( в маске ) :
                if ((( Reg_AvarMsg | Reg_AvarMsgFirst ) & ~_Otkl_Q2_Mask ) != (lw)r0 ) goto q ;
                if ((( Reg_AvarMsg2 | Reg_AvarMsgFirst2 ) & ~_Otkl_Q2_Mask2 ) != (lw)r0 ) goto q ;
                // Если понадобиться , продумать маски для отключения Q2 для третьего и прекрасного регистров :
                //#ifdef _TRETIY_REG
                //#endif
                //#ifdef _INTERPRETER
                //#endif
             #ifdef _SIFU2_
               if ( S.Disable == 1 ) // DAN 23.05.2017 14:46 - При работе только ШС2 :
               {
                if ( IDV2 > _r.Tok_Otkl_Kontaktor ) goto q ;
               }
               else
             #endif
               {
                if ( IDV > _r.Tok_Otkl_Kontaktor ) goto q ;
               }
              }
            else
              {
          q:    mOtkl_Q2 () ;
              }
        #else
                if ((( Reg_AvarMsg | Reg_AvarMsgFirst ) & ~_Otkl_Q2_Mask ) != (lw)r0 )    mOtkl_Q1 ()  ;
                if ((( Reg_AvarMsg2 | Reg_AvarMsgFirst2 ) & ~_Otkl_Q2_Mask2 ) != (lw)r0 ) mOtkl_Q1 ()  ;
        #endif
                // Фиксация текущего момента времени для последующих отсчетов.
            Time_do_OtklImp  = Timer1_Ovr ;
            av_label = 10 ;
            bo_SledActiv = 1 ;
            break;// сделаем один выход наружу чтобы, даже при остановленном
                 // до аварии следе сработала фиксация текущих сообщений и времени.
             //---------------
  case 10 :   // - ожидание остановки следа, после команды остановки.
            //21.02.06 15:50 Prg._.Sled = 0 ;
            if ( bo_SledActiv == 0 )
              {
                av_label = 15 ;
              }
  case 15 :   // - отсчет времени до отключения импульсов.
            if ( (u)((w)(Timer1_Ovr - Time_do_OtklImp)) >= _r.Time_do_OtklImp )
              {
                mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
     #ifdef _KTE_GD
                // DAN 08.11.2016 - В соответствии с гениальным техническим решением Соломахи и
                // Шестакова , отключаем автомат по защите "Id-Max" уже после того , как всё выгорит ,
                // для того , чтобы сберечь автомат ...
                if ( ( (Reg_AvarMsg | Reg_AvarMsgFirst) & _Av_IdMax ) != (lw)r0 ) mOtkl_Q1 () ;
     #endif
                //---
                   //  если истекли обе задержки переходим к следующему шагу.
                  // (задержки могут быть разных размеров.)
                if ( av_label == 15 )
                {
                  av_label = 18 ;
                  i2c_av_label = 0 ;
                }
              }
        break; //--------------------
  case 18 :
            if ( Save_avar() != 4 )   av_label = 20 ;

        break; //--------------------
  case 20 :
               //  острочиваем автозапуск следа.
            sl_d.time_out = Timer1_Ovr ;
              //  "ДИСТАНЦИОННЫЙ СБРОС"
#ifndef _ATK_SET
                // чтобы можно было сбросить с пульта Геркон и Id_Max
            if ( can_ConfigReg ( _CAN_DistSbros ) == 1 )  goto sbr ;
            if ( Klav_Buff == _Reset )        goto sbr ;
            if ( bi_DS1 == 1 )   Av._.DistSbros = 1 ;
            else  if ( Av._.DistSbros == 1 )
              {      // Разрешен ли дистанционный сброс при данных авариях?
                if ( ( (Reg_AvarMsg | Reg_AvarMsgFirst)
                                      & _Mask_DistSbr ) != 0 )  break ;
           sbr: Init_posle_DistSbr () ;
          }   }
#else // Переделываем сброс по переднему фронту и уровню только для АТК .
            if ( Av._.DistSbros == 1 )
            {
               Init_posle_DistSbr () ;
          } }
#endif
        else  // Отключение по команде 1VR - "ОПЕРАТИВНОЕ ОТКЛЮЧЕНИЕ".
          {
            Time_do_OtklImp  = Timer1_Ovr ;
            av_label = 30 ;
  case 30 :
            if ( (u)((w)(Timer1_Ovr - Time_do_OtklImp)) >= _r.Time_do_OtklImp )
              {
                Init_posle_DistSbr () ;
              }
          }
      }
}
      //    Фиксация времени изменения количества сообщений для
      //  распечатки его по "Enter" в режиме "A1".
    //check_msg_time ()  ; //это уже есть в system.c  24.02.09 15:50
    // закомментировано "check_msg_time()" 11.04.2014 11:49 т.к. за цикл он должен вызываться 1 раз в "System_prg()"
  return ;
}
//---------------------

void Clr_Q1_Q2 ( void )
{
  static word timeout_Q1, timeout_Q2  ;

  // Сигнал на отключение автоматов длится _Time_otkl_QX . Во время отключения взводится
  // флаг однократности отключения автомата Av._.OneQX . Пока этот флаг не снят ,
  // дальнейшего отключения автоматов не происходит . Флаг однократности снимается по
  // выдержке времени , при условии , что блок контакт автомата включен .

         /* Снятие, после выдержки, сигнала на отключение "Q1". */
      if ( Av._.OtklQ1 == 1 )
      {
        if ( (u)((w)(timer1 - TimeOtklQ1)) >= _Time_otkl_Q1 )
        {
          mClr_Q1() ;
          timeout_Q1 = Timer1_Ovr ;
        }
      }
      else if ( Av._.OneQ1 == 1 ) // Пока флаг однократности отключения Q1 взведён , отключения Q1 не происходит .
        { // Снятие однократности отключения автомата после выдержки времени , если его снова включили .
          if ( (u)((w)(Timer1_Ovr-timeout_Q1)) >= _TimeOut_otkl_Q1)
            {                                         // Снимаем однократность , только если автомат Q1 включен ,
              if ( bi_xQ1 == 1 || Av._.Ostanov == 1 ) Av._.OneQ1 = 0 ; // или в режиме Останов .
            }
        }

         /* Снятие, после выдержки, сигнала на отключение "Q2". */
      if ( Av._.OtklQ2 == 1 )
      {
        if ( (u)((w)(timer1 - TimeOtklQ2)) >= _Time_otkl_Q2 )
        {
          mClr_Q2() ;
          timeout_Q2 = Timer1_Ovr ;
        }
      }
      else if ( Av._.OneQ2 == 1 ) // Пока флаг однократности отключения Q2 взведён , отключения Q2 не происходит .
        { // Снятие однократности отключения автомата после выдержки времени , если его снова включили .
          if ( (u)((w)(Timer1_Ovr-timeout_Q2)) >= _TimeOut_otkl_Q2)
            {                                         // Снимаем однократность , только если автомат Q1 включен ,
              if ( bi_xQ2 == 1 || Av._.Ostanov == 1 ) Av._.OneQ2 = 0 ; // или в режиме Останов .
            }
        }

return ;
}
//-------------

void GerconAC_Interrupt (void)
  {
      if ( mTest_Gercon() )
      {
     #ifdef  _Gercon_APV  // идет тайм-аут на повторное вкл.
        if ( Av2._.APV_Gercon != 0 )
     #endif
        {
          mOtkl_Q1 () ;
      #ifdef _POWER
          bo_MB1_Otkl = 1 ;
      #endif
          // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
          //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
          // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
          //            АЭС , что после Геркона в КТЭ :
          //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
          //            не задвигая их в Альфа-макс .
          //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
          //             выдержку времени перед их снятием , чтобы загасить ток .
          //              3. Для ГД импульсы мгновенно не снимать .
      #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 В АТК не снимаем ИУ без выдержки , чтобы не запутаться Инв/Выпр .
          if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
      #endif
        }
        Av._.Sdvig_imp = 1 ;
        Av._.Gercon = 1 ;
      #ifdef bi_2B1 // Герконы в ШВ1 и в ШВ2 приходят на вход 1В .
        if ( mTest_Gercon2B1() ) Av2._.GerconAC2 = 1 ;
      #endif
      #ifdef bi_3B1 // Герконы в ШВ1 , ШВ2 и ШВ3 приходят на вход 1В .
             if ( mTest_Gercon3B1() ) Av2._.GerconAC3 = 1 ;
      #endif
      #ifdef bi_4B1 // Герконы в ШВ1 , ШВ2 , ШВ3 и ШВ4 приходят на вход 1В .
             if ( mTest_Gercon4B1() ) Av2._.GerconAC4 = 1 ;
      #endif
      }
    return   ;
  }

//-------------

void GerconDC_Interrupt (void)
  {
      if ( mTest_GerconDC() )
      {
      //-------------------
    #ifdef bi_GerconDC
        mOtkl_Q2 () ;
          // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
          //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
          // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
          //            АЭС , что после Геркона в КТЭ :
          //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
          //            не задвигая их в Альфа-макс .
          //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
          //             выдержку времени перед их снятием , чтобы загасить ток .
          //              3. Для ГД импульсы мгновенно не снимать .
      #ifndef _KTE_GD
          if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
      #endif
        Av._.Sdvig_imp = 1 ;
        Av._.GerconDC = 1 ;
    #else  // 14.10.2008 11:40
     #ifdef bi_RV1
              //  "Срабатывание РДШ"
        Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
        Av2._.RV1 = 1 ;
     #endif
    #endif
      //-------------------
    #ifdef bi_GerconAC2
      #ifdef  _Gercon_APV  // идет тайм-аут на повторное вкл.
        if ( Av2._.APV_Gercon != 0 )
      #endif
        {
          mOtkl_Q1 () ;
          // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
          //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
          // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
          //            АЭС , что после Геркона в КТЭ :
          //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
          //            не задвигая их в Альфа-макс .
          //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
          //             выдержку времени перед их снятием , чтобы загасить ток .
          //              3. Для ГД импульсы мгновенно не снимать .
      #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 В АТК не снимаем ИУ без выдержки , чтобы не запутаться Инв/Выпр .
          if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
      #endif
        }
        Av._.Sdvig_imp = 1 ;
        Av2._.GerconAC2 = 1 ;
    #endif
      //-------------------
      }
    return   ;
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
          /* Проверка сигнала Герконов.  */
void Control_Gercon ( void )
{
        /* Проверка сигнала Геркона Постоянного Тока.  */
  #ifdef bi_GerconDC
    if ( bi_GerconDC == 1 )  Av._.GerconDC = 1 ;
    if ( Av._.GerconDC == 1 )
     {
        mSet_AvarMsg ( _Av_GerconDC ) ;
        mOtkl_Q2 () ;
     }
  #else // 14.10.2008 11:40
     #ifdef bi_RV1
              //  "Срабатывание РДШ"
       if ( bi_RV1 == 1 ) Av2._.RV1 = 1 ;
       if ( Av2._.RV1 == 1 )
        {
          Av._.Sdvig_imp = 1 ;   // Команда на задвигание УИ в АльфаМакс.
          mSet_AvarMsg2( _Av2_RV1 ) ;
        }
     #endif
  #endif
     //-------
    if ( bi_Gercon == 1 )  Av._.Gercon = 1 ;
  #ifdef bi_GerconAC2
    if ( bi_GerconAC2 == 1 ) Av2._.GerconAC2 = 1 ;
  #endif
     //-------

//---***************************************
#ifndef  _Gercon_APV
//---***************************************
    if ( Av._.Gercon == 1 ) // <- признак выставляется в  прерывании по геркону.
      {
        mSet_AvarMsg ( _Av_Gercon ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
        //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
        // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
        //            АЭС , что после Геркона в КТЭ :
        //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
        //            не задвигая их в Альфа-макс .
        //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
        //             выдержку времени перед их снятием , чтобы загасить ток .
        //              3. Для ГД импульсы мгновенно не снимать .
    #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 В АТК не снимаем ИУ без выдержки , чтобы не запутаться Инв/Выпр .
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
      }
      //----
    if ( Av2._.GerconAC2 == 1 )
     {
      #ifdef bi_2B1 // Герконы в ШВ1 и в ШВ2 приходят на вход 1В .
        if ( Av._.Gercon == 1 ) // Если сработали герконы и в ШВ1 и в ШВ2 ,
         {                      // считаем , что сработал только в ШВ2 ,
           if ( (Reg_AvarMsgFirst & _Av_Gercon) != (lw)r0 ) // если ШВ1 был в первой аврии ,
            {                            // заносим в первую аварию ШВ2 .
              mSet_AvarMsg ( _Av_GerconDC ) ;
            }
           mClr_AvarMsg ( _Av_Gercon ) ; // Стираем сообщение о герконе в ШВ1 .
         }
      #endif
        mSet_AvarMsg ( _Av_GerconDC ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
        //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
        // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
        //            АЭС , что после Геркона в КТЭ :
        //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
        //            не задвигая их в Альфа-макс .
        //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
        //             выдержку времени перед их снятием , чтобы загасить ток .
        //              3. Для ГД импульсы мгновенно не снимать .
    #if !defined(_KTE_GD) && !defined(_ATK_SET) // 08.12.2020 В АТК не снимаем ИУ без выдержки , чтобы не запутаться Инв/Выпр .
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
     }
      //----
  #ifdef bi_3B1 // Герконы в ШВ1 , ШВ2 и ШВ3 приходят на вход 1В .
    if ( Av2._.GerconAC3 == 1 )
     {
        if ( Av._.Gercon == 1 ) // Если сработали герконы и в ШВ1 и в ШВ3 ,
         {                      // считаем , что сработал только в ШВ3 ,
           if ( (Reg_AvarMsgFirst & _Av_Gercon) != (lw)r0 ) // если ШВ1 был в первой аврии ,
            {                            // заносим в первую аварию ШВ3 .
              mSet_AvarMsg ( _Av_Gercon3 ) ;
            }
           mClr_AvarMsg ( _Av_Gercon ) ; // Стираем сообщение о герконе в ШВ1 .
         }
        mSet_AvarMsg ( _Av_Gercon3 ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
        //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
        // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
        //            АЭС , что после Геркона в КТЭ :
        //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
        //            не задвигая их в Альфа-макс .
        //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
        //             выдержку времени перед их снятием , чтобы загасить ток .
        //              3. Для ГД импульсы мгновенно не снимать .
    #ifndef _KTE_GD
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
     }
  #endif
  #ifdef bi_4B1 // Герконы в ШВ1 , ШВ2 , ШВ3 и ШВ4 приходят на вход 1В .
    if ( Av2._.GerconAC4 == 1 )
     {
        if ( Av._.Gercon == 1 ) // Если сработали герконы и в ШВ1 и в ШВ4 ,
         {                      // считаем , что сработал только в ШВ4 ,
           if ( (Reg_AvarMsgFirst & _Av_Gercon) != (lw)r0 ) // если ШВ1 был в первой аврии ,
            {                            // заносим в первую аварию ШВ4 .
              mSet_AvarMsg ( _Av_Gercon4 ) ;
            }
           mClr_AvarMsg ( _Av_Gercon ) ; // Стираем сообщение о герконе в ШВ1 .
         }
        mSet_AvarMsg ( _Av_Gercon4 ) ;
        mOtkl_Q1 () ;
        // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
        //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
        // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
        //            АЭС , что после Геркона в КТЭ :
        //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
        //            не задвигая их в Альфа-макс .
        //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
        //             выдержку времени перед их снятием , чтобы загасить ток .
        //              3. Для ГД импульсы мгновенно не снимать .
    #ifndef _KTE_GD
        if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
    #endif
      #ifdef _POWER
        bo_MB1_Otkl = 1 ;
      #endif
     }
  #endif
//---***************************************
#else
//---***************************************
    if ( Av._.Gercon == 1 || Av2._.GerconAC2 == 1 )
    {
      Av._.Sdvig_imp = 1 ;
          //  геркон сработал повторно после отпускания между 10 и 30 мсек.
      if ( Av2._.APV_Gercon != 0 )  goto Avar  ;
      else      // геркон сработал впервые за 30 мсек.
      {
         if ( RT_trigg == 0 )// запоминаем, был ли включен при
         {                  // срабатывании геркона РТ.
           if ( Prg._.RegTok == 1 ) RT_trigg  = 0x81 ;
           else                     RT_trigg  = 0x80 ;
         }
         Prg._.RegTok = 0 ; // отключение Рег. Тока.
         if ( (u)((w)(timer1 - gercon_time)) > _MkSec( 10u * 1000u ) )   // если прошло 10 ms .
         {
           if (   mTest_Gercon()
                #ifdef bi_GerconAC2
                       || mTest_GerconDC()
                #endif
              )
           {       // геркон переменного тока ШС1
         Avar: if ( Av._.Gercon   == 1 )  mSet_AvarMsg ( _Av_Gercon ) ;
                   // геркон переменного тока ШС2
               if ( Av2._.GerconAC2 == 1 )mSet_AvarMsg ( _Av_GerconDC ) ;
               mOtkl_Q1 () ;
               // 05.12.07 - По замечаниям из Запорожстали , по Герконам сразу снимаем
               //            импульсы без выдержки , чтобы не успели сгореть тиристоры :
               // 28.09.15 - Шестаков и Игнатов решили , после наладки КТЭВа на Xмельницкой
               //            АЭС , что после Геркона в КТЭ :
               //              1. В Режиме Выпрямителя можно снимать ИУ мгновенно ,
               //            не задвигая их в Альфа-макс .
               //              2. В Режиме Инвертора следует держать ИУ в Альфа-макс
               //             выдержку времени перед их снятием , чтобы загасить ток .
               //              3. Для ГД импульсы мгновенно не снимать .
           #ifndef _KTE_GD
               if ( S.flg._.Invertor == 0 ) mOtkl_Imp( _Avar_imp ) ;  /* отключение импульсов якоря */
           #endif
          #ifdef _POWER
              bo_MB1_Otkl = 1 ;
          #endif
           }
           else  // если геркон разомкнулся через 10 ms
           {
              if ( bo_Avar == 0  ) // прверка, чтобы не снять сдвиг ИУ.
              {
                Av._.Sdvig_imp = 0 ;
                if ( RT_trigg == 0x81 )  Prg._.RegTok = 1 ;
              }
              RT_trigg = 0  ;
              Av._.Gercon = 0 ;
              Av2._.GerconAC2 = 0 ;
              Av2._.APV_Gercon = 1 ; // признак отпускания герк. для контр. его повторн. срабат.
           }
         }
      }
    }
    else
    {
      RT_trigg = 0  ;
      if ( Av2._.APV_Gercon != 0 )
      {     //  Если в течении 30 ms после первого ВКЗ геркон повторно не
            // сработал  -  tst_ сбрасывается.
        if ( (u)((w)(timer1 - gercon_time)) > _MkSec( 30u * 1000u ) )  Av2._.APV_Gercon = 0 ;
      }
      else gercon_time = timer1 ;
    }
//---***************************************
#endif
//---***************************************
  return ;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Измерение токов по фазам :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach )

 void IdIzm_3faz (void)
 {
   // 100мкс - все 6 измерений фазных токов мультиплексированными каналами .
   // Поэтому измеряем по 4 рабочих тока каждый пульс :
   //---
   // Определение фаз , по которым сейчас должен течь ток .
     // В режиме определения пробитого тиристора :          // В рабочем режиме :
     // Tir1 - фазные токи Iс ( Ia - необязательно )        // Tir1 - фазные токи Ia и Ib
     // Tir2 - фазные токи Ib ( Ic - необязательно )        // Tir2 - фазные токи Ia и Iс
     // Tir3 - фазные токи Ia ( Ib - необязательно )        // Tir3 - фазные токи Ib и Ic
     // Tir4 - фазные токи Ic ( Ia - необязательно )        // Tir4 - фазные токи Ib и Ia
     // Tir5 - фазные токи Ib ( Ic - необязательно )        // Tir5 - фазные токи Ic и Ia
     // Tir6 - фазные токи Ia ( Ib - необязательно )        // Tir6 - фазные токи Ic и Ib
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 2 && S.N != 5 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S.N != 3 && S.N != 6 ) )
    {
      IA1_full = _AD_BUSY; // ШС1
      mAD_Izm (  IA1_ach    , &IA1_full ) ; // ИЗМЕРЕНИЕ  "IA1_Full"
      //---
 #ifdef IA2_ach
      IA2_full = _AD_BUSY; // ШС2
      mAD_Izm (  IA2_ach    , &IA2_full ) ; // ИЗМЕРЕНИЕ  "IA2_Full"
 #endif
    }
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 1 && S.N != 4 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S.N != 2 && S.N != 5 ) )
    {
      IB1_full = _AD_BUSY; // ШС1
      mAD_Izm (  IB1_ach    , &IB1_full ) ; // ИЗМЕРЕНИЕ  "IB1_Full"
      //---
 #ifdef IB2_ach
      IB2_full = _AD_BUSY; // ШС2
      mAD_Izm (  IB2_ach    , &IB2_full ) ; // ИЗМЕРЕНИЕ  "IB2_Full"
 #endif
    }
    if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 3 && S.N != 6 ) ||
         ( flg_RaTe._.tyr_tst_go == 0 && S.N != 1 && S.N != 4 ) )
    {
      IC1_full = _AD_BUSY; // ШС1
      mAD_Izm (  IC1_ach    , &IC1_full ) ; // ИЗМЕРЕНИЕ  "IC1_Full"
      //---
 #ifdef IC2_ach
      IC2_full = _AD_BUSY; // ШС2
      mAD_Izm (  IC2_ach    , &IC2_full ) ; // ИЗМЕРЕНИЕ  "IC2_Full"
 #endif
    }

  return ;
 }

//   Программа преобразования измеренных токов по фазам :
 void IdConv_3faz (void)
 {
    register word ix ;
    //---
   // Определение фаз , по которым сейчас должен течь ток .
     // В режиме определения пробитого тиристора :          // В рабочем режиме :
     // Tir1 - фазные токи Iс ( Ia - необязательно )        // Tir1 - фазные токи Ia и Ib
     // Tir2 - фазные токи Ib ( Ic - необязательно )        // Tir2 - фазные токи Ia и Iс
     // Tir3 - фазные токи Ia ( Ib - необязательно )        // Tir3 - фазные токи Ib и Ic
     // Tir4 - фазные токи Ic ( Ia - необязательно )        // Tir4 - фазные токи Ib и Ia
     // Tir5 - фазные токи Ib ( Ic - необязательно )        // Tir5 - фазные токи Ic и Ia
     // Tir6 - фазные токи Ia ( Ib - необязательно )        // Tir6 - фазные токи Ic и Ib
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 2 && S.N != 5 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S.N != 3 && S.N != 6 ) )
  {
    while ( IA1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IA1_full , ix ,  IA1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IA1 = ix ;
      //---
 #ifdef IA2_ach
    while ( IA2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IA2_full , ix ,  IA2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IA2 = ix ;
 #endif
  }
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 1 && S.N != 4 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S.N != 2 && S.N != 5 ) )
  {
    while ( IB1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IB1_full , ix ,  IB1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IB1 = ix ;
      //---
 #ifdef IB2_ach
    while ( IB2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IB2_full , ix ,  IB2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IB2 = ix ;
 #endif
  }
  if ( ( flg_RaTe._.tyr_tst_go == 1 && S.N != 3 && S.N != 6 ) ||
       ( flg_RaTe._.tyr_tst_go == 0 && S.N != 1 && S.N != 4 ) )
  {
    while ( IC1_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IC1_full , ix ,  IC1_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IC1 = ix ;
      //---
 #ifdef IC2_ach
    while ( IC2_full == _AD_BUSY );
   //---
    mIzmData_Conversion ( IC2_full , ix ,  IC2_ach   ) ;
    ix = (sw)( (slw)(sw)ix * (slw)(sw)_r.Mashtab_Idtt >> 8 ) ;
    if ( (sw)ix < 0 ) ix = ~ix + 1 ;
    IC2 = ix ;
 #endif
  }

  return ;
 }

#endif

//---------------------------------------------------------------------------------------------------------------

      // Распределение токов по фазам двух секций ШС :
#if defined( IA1_ach ) && defined( IB1_ach ) && defined( IC1_ach ) && defined( IA2_ach ) && defined( IB2_ach ) && defined( IC2_ach )

 void TokRaspr_3faz (void)
 {
    word ax ;
    //---
    // Определение фаз , по которым сейчас должен течь ток :
    // Tir1 - фазные токи Ia и Ib
    // Tir2 - фазные токи Ia и Iс
    // Tir3 - фазные токи Ib и Ic
    // Tir4 - фазные токи Ib и Ia
    // Tir5 - фазные токи Ic и Ia
    // Tir6 - фазные токи Ic и Ib

    if ( Prg._.Gotovn == 0 ) // Контроль только в работе :
    {
      if ( S.N == 1 ) // Tir1 - фазные токи Ia и Ib .
      {
         //--- Фаза A шкафов ШС1 и ШС2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
         //---
         //--- Фаза B шкафов ШС1 и ШС2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
      }
      else if ( S.N == 2 ) // Tir2 - фазные токи Ia и Iс .
      {
         //--- Фаза A шкафов ШС1 и ШС2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
         //---
         //--- Фаза C шкафов ШС1 и ШС2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
      }
      else if ( S.N == 3 ) // Tir3 - фазные токи Ib и Ic .
      {
         //--- Фаза B шкафов ШС1 и ШС2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
         //---
         //--- Фаза C шкафов ШС1 и ШС2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
      }
      else if ( S.N == 4 ) // Tir4 - фазные токи Ib и Ia .
      {
         //--- Фаза B шкафов ШС1 и ШС2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
         //---
         //--- Фаза A шкафов ШС1 и ШС2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
      }
      else if ( S.N == 5 ) // Tir5 - фазные токи Ic и Ia .
      {
         //--- Фаза C шкафов ШС1 и ШС2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
         //---
         //--- Фаза A шкафов ШС1 и ШС2 :
         ax = IA1 - IA2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IA1 + IA2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_A ) ;
           }
         }
      }
      else // Tir6 - фазные токи Ic и Ib .
      {
         //--- Фаза C шкафов ШС1 и ШС2 :
         ax = IC1 - IC2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IC1 + IC2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_C ) ;
           }
         }
         //---
         //--- Фаза B шкафов ШС1 и ШС2 :
         ax = IB1 - IB2 ;
         if ( (sw)ax < 0 ) ax = ~ax + 1 ;
         //---
         if ( ((IB1 + IB2)/2) > _or.dIs_ControlBegin )
         {
           if ( ax > _or.Is_tokoraspred ) // Токи в одноимённых фазах сильно отличаются :
           {
            mSet_PreduprMsg3 ( _Pr3_TokRaspr1S_B ) ;
           }
         }
      }
    }

  return ;
 }

#endif
