#ifndef _izm_h
#define _izm_h



/*---------------  Для АЦП  ---------------------*/

 struct Izm_analog  // Для измерения аналоговых сигналов
{
  word  out ;
  struct Channel_AD *ach ;
  word  drob ;
  //byte  time ;
  byte  shift ;
  byte  porog ;
} ;
word  Izm_NullOffset ( struct Channel_AD *ptr ) ;
/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

//--------------
#ifdef  _Open_AD_BUFFERs
//--------------
         //  Ячейки работы с буферами измерений

byte   InAdBuffCount        ;

byte   OutAdBuffCount  ;

        // Буфер для управляющих слов АЦП и мультиплексора
          word   AdBuff_Command [AdBuffSize+1]  ;

        // Буфер для адресов результатов измерений
          word  *AdBuff_AddrResult [AdBuffSize+1]  ;
//--------------
#endif
//--------------

//const struct Channel_AD  AN0  = { 0x00, 0x00 };

struct Izm_analog  *pr ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

//--------------
#ifdef  _Open_AD_BUFFERs
//--------------
         //  Ячейки работы с буферами измерений
  extern byte   InAdBuffCount        ;

  extern byte   OutAdBuffCount  ;

        // Буфер для управляющих слов АЦП и мультиплексора
  extern            word   AdBuff_Command []  ;

        // Буфер для адресов результатов измерений
  extern            word  *AdBuff_AddrResult []  ;
//--------------
#endif
//--------------

  extern   struct Izm_analog  *pr ;

/*------------------------------------------------*/
#endif
#endif


