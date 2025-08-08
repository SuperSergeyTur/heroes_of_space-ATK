#ifndef _selsin_h
#define _selsin_h


word Selsin ( word code , word num ) ;
void Selsin_init ( void ) ;
void Selsin_input( void ) ;

/*   Блок данных для Задания Скорости через Сельсин   */

struct SELSIN
  {
    word   out_g ;  // выход в градусах
    word   out_m ;  // выход отмасштабированный в дискретах _Skor_nom .
    word   epa_time ;
    word*  epa_addr ;
    word   NS2_time ;
    word   drob ;
  }  ;

struct SELSIN_ust
  {
    word   null ;  // выход
    word   masht ;
  }  ;

struct SELSIN_dop_ust
  {
    word*  mashtP ;
    word*  mashtM ;
    byte*  shift  ;
    byte*  rezerv ;
//  word*  porog  ;
  }  ;

#define  _Sels_Num     2

union SELSIN_trig
{
     byte all ;
     struct
     {
         byte  null0    : 1 ;
         byte  null1    : 1 ;
         byte  rezerv   : 6 ;
     } _ ;
} ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

union SELSIN_trig Sels_tr ;
word  timerNull ;

const byte  _Sels_shift  = 1 ;
const word  _Sels_mashtP = (w)( 1.00 * 256.) ;
const word  _Sels_mashtM = (w)( 1.00 * 256.) ;

struct  SELSIN Sels[_Sels_Num] ;
struct  SELSIN_dop_ust SelsDU[_Sels_Num] ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern union SELSIN_trig Sels_tr ;
extern word  timerNull ;

extern const byte  _Sels_shift  ;
extern const word  _Sels_mashtP ;
extern const word  _Sels_mashtM ;

extern struct  SELSIN Sels[_Sels_Num] ;
extern struct  SELSIN_dop_ust SelsDU[_Sels_Num] ;

/*------------------------------------------------*/
#endif
#endif
