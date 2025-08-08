#ifndef  pdf_h
#define  pdf_h

#include <pdf_drv.h>

word pdf ( word code , word num ) ;
void pdf_init ( void ) ;
void pdf_input( void ) ;

/*   Блок данных для ПДФ   */

struct PDF_data
  {
    word   out_ob;  // выход: скорость в оборотах.
    word   out_m ;  // выход: масштабированное кол-во имп. за интервал измерения.
    word   out_g ;  // угол поворота в градусах.
    word   time  ;  // время последнего считывания.
    word   count ;  // последнее значение счетчика.
    word   Fpdf  ;  // частота импульсов ПДФ.
    word   N_Fpdf;  // скорость в оборотах по частоте импульсов ПДФ.
    word   N_Tpdf;  // скорость в оборотах по периоду импульсов ПДФ.
    word   fz    ;  // подсчет оборотов .
    union
    {
      byte    all ;
      struct
      {
        byte  t_ogr_pdf    : 1 ; // флаг ограничения периода импульсов по максимому .
        byte  pdf_zona_T   : 1 ; // флаг переключения с частоты на период .
        byte  new_izm_pdf  : 1 ; // флаг готового измерения ПДФ ( раз в 3 пульса ) .
        byte  rezerv       : 5 ;
      } _ ;
    } flg ;
  }  ;

struct PDF_ust
  {
    word   imp  ;  // число импульсов на оборот для вычисления угла поворота.
    word   null ;  // нулевое положение для вычисления угла поворота.
    word   masht ; // масштаб для вычисления скорости.
  }  ;

  // Приводим кол-во имп. измеренное за данный промежуток к кол-ву имп. за 10мсек.
#ifndef    _PDF_base_time

  #define  _PDF_PERIOD     10000

  #define  _PDF_base_time   _MkSec( _PDF_PERIOD )
#endif

#define  _PDF_delitel   ( 1 << 10 )   // основание для коэф.масштабирования

//------------------------------
#ifdef  _MAIN_INCLUDE
//------------------------------
struct  PDF_data PDF[ _PDF_Num ] ;
//---
#else
//---
extern struct  PDF_data PDF[ _PDF_Num ] ;
//---
#endif
#endif
