#ifndef _vozb_h
#define _vozb_h


word SIFU_Start ( void );
word SIFU1_Start ( void );
void S_Interrupt ( void );
void S1_Interrupt ( void );

word Synch2_Start ( void ) ;
//#undef    _synch2_epa_con                       DAN перенесено в EXTRN.H 04.05.2016 9:30 .
//#undef    _synch2_epa_time
//#define   _synch2_epa_con    _selsin1_epa_con
//#define   _synch2_epa_time   _selsin1_epa_time
void Correct_Fazir ( word ) ;


  struct SIFU
    {
      word  Alfa       ;
      word  Alfa_Old   ;
    //word  Alfa_Old2  ; // для программы контроля открытия тиристоров .
      word  TZ         ;
      word  Disable    ;

      byte  N          ;
      byte  NumInt     ;
      byte  NIP        ;
      byte  Most_Tir  ;
      byte  NumMost    ;
      byte  DZV        ;

      union
      {
        word   all ;
        struct
        {
          word  Fmax   : 1 ;
          word  Fmin   : 1 ;
          word  Fdmax  : 1 ;
          word  Fdmin  : 1 ;

          word   Invertor: 1;  // Признак режима Инвертора.
          word   Revers  : 1;  // Признак необходимости Реверсирования.
          word   VneshZp : 1;  // Внешний запрет импульсов . //SPI     : 1;  // Перекл. режим УИ "Одиночные/Сдвоенные".
          word   BegImp  : 1;  // Признак сформированности УИ .

          word  ZapretImp : 1; // Запрет имп. по готовности реверса.
          word  TZ_Ok     : 1; // Новое TZ расчитано.
          word  SnImpVM   : 1; //
          word  SnImpVM2  : 1; //

          word  ImpSet1   : 1; //
          word  ImpSet2   : 1; //
          word  longImp   : 1; //
          word  DZV_OK    : 1; // Пришел сигнал ДЗВ, после этого выдержку на безток.паузу не обнуляем.
        } _ ;
      } flg ;
    }   ;

      // Для возможности задать извне переменную длину ИУ.
#ifndef    _r_S_ImpLong
  #define  _r_S_ImpLong   _r.S_ImpLong
#endif

 // флаги дополнительных измерений тока для Автонастройки и Контроля открытия тиристоров :
 union flg_dop_Izm
    {
      word all ;
      struct
      {
          word  Id_anastr   :  1 ;
          word  tyr_tst_ok  :  1 ; // проверка пробития тиристоров окончена , тиристоры СИФУ1 , СИФУ2 в порядке .
          word  tyr_tst_av  :  1 ; // проверка пробития тиристоров окончена , сработали защиты СИФУ1 или СИФУ2 .
          word  tyr_tst_pr  :  1 ; // проверка пробития тиристоров окончена , тиристоры СИФУ1 или СИФУ2 пробиты .

          word  tyr_tst_go  :  1 ; // проверка пробития тиристоров СИФУ1 и СИФУ2 пущена .
          word  rezerved    : 11 ;
      } _ ;
    }   ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

_register struct SIFU     S ;

//---
#ifdef  _SIFU_Syn2    // ЕСТЬ ЛИ ОТДЕЛЬНАЯ СИНХРОНИЗАЦИЯ ОТ МОСТА ДЛЯ СИФУ.
 struct Synchr Syn2 ;// При синхр. якорного СИФУ от Силы моста, а возб.от СН380.
 struct Synchr *pSyn ;// Адрес синхр., к которой привязано СИФУ.
#else
 #define pSyn (&Syn)
#endif
//---

_register   word  s_ax, s_bx ;
_register   word  s_cx ;
_register  lword  s_lax , s_lbx  ;

word    sf_time  ;
word    s_num  ;
word    s_num2  ;
word    s_num3  ;

word   Time_dL   ;

volatile word    Puls_counter ;

         word    Otkl_Imp  ;
#ifdef _F16e

byte const FOR0 [3][7] = {{ 0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f },
   // первый мост ->
                          { 0x3f,0x5e,0x7c,0x79,0x73,0x67,0x4f },
   // второй мост ->
                          { 0x3f,0x9e,0xbc,0xb9,0xb3,0xa7,0x8f }};

byte const FOR1 [3][7] = {{ 0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f },
   // первый мост ->
                          { 0x3f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f },
   // второй мост ->
                          { 0x3f,0xbe,0xbd,0xbb,0xb7,0xaf,0x9f }};
#else

//byte const FOR0 [3][7] = {{ 0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f },
   // первый мост ->    { 0x3f,0x5e,0x7c,0x79,0x73,0x67,0x4f },
   // второй мост ->    { 0x3f,0x9e,0xbc,0xb9,0xb3,0xa7,0x8f }};

//byte const FOR1 [3][7] = {{ 0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f },
   // первый мост ->    { 0x3f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f },
   // второй мост ->    { 0x3f,0xbe,0xbd,0xbb,0xb7,0xaf,0x9f }};

#ifndef  _SIFU_1Faza
              //Импульсы с подтверждающими
  byte const FOR0 [7] = { 0x3f,0x5e,0x7c,0x79,0x73,0x67,0x4f };
              //Импульсы без подтверждающих
  byte const FOR1 [7] = { 0x3f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f };
#else  // тир-ры двоятся чтобы можно было реализовать 120-грд ИУ для 1-фазн.КТЭВ
      // рабочие тиристоры:    1/2, 1/2  откл.3/4, 3/4  откл.
  byte const FOR0 [7] = { 0x3f,0x7c,0x7c,0x3f,0x73,0x73,0x3f };
              //Импульсы без подтверждающих
      // рабочие тиристоры:     1,  откл.откл. 3   откл.откл.
  byte const FOR1 [7] = { 0x3f,0x7e,0x3f,0x3f,0x7b,0x3f,0x3f };
#endif

#endif //_F16e
   word  const  LIN[35]=               /*массив линеаризации пилы  */
	   {
       0x0000,0x0320,0x0570,0x0734,0x08a7,0x0a0a,
	     0x0b43,0x0c69,0x0d7c,0x0e7b,0x0f6f,0x105b,
	     0x113c,0x121d,0x12f5,0x13c3,0x1491,0x1576,
	     0x163b,0x16fb,0x17c8,0x187d,0x1932,0x19e6,
	     0x1a96,0x1b46,0x1bf6,0x1ca4,0x1d50,0x1dfc,
	     0x1ea8,0x1f54,0x1fff
	   };

   union flg_dop_Izm  flg_RaTe ;

  sword  Id_AN_imp;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

  extern _register  struct SIFU     S              ;

//---
#ifdef  _SIFU_Syn2    // ЕСТЬ ЛИ ОТДЕЛЬНАЯ СИНХРОНИЗАЦИЯ ОТ МОСТА ДЛЯ СИФУ.
 extern struct Synchr Syn2 ;
 extern struct Synchr *pSyn ;
#else
 #define pSyn (&Syn)
#endif
//---

  extern  word    s_time  ;
  extern  word    s_num  ;
  extern  word    s_num2  ;
  extern  word    s_num3  ;
  extern  word   Time_dL   ;

  extern _register   word  s_ax ;
  extern _register   word  s_cx    ;
  extern _register  lword  s_lax, s_lbx  ;

  extern word    Otkl_Imp  ;

  extern volatile word    Puls_counter ;
#ifdef _F16e

  extern         byte const FOR0[3][7];
  extern         byte const FOR1[3][7];

#else

  extern         byte const FOR0[];
  extern         byte const FOR1[];

#endif
  extern         word const  LIN[]  ;

  extern union flg_dop_Izm  flg_RaTe ;

  extern        sword Id_AN_imp;
/*------------------------------------------------*/
#endif
#endif
