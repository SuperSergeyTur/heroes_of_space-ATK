#ifndef  pdf_h
#define  pdf_h

#include <pdf_drv.h>

//Время замера количества импульсов
#define _ReloadValue_us  5000
#define _StrobTempPin    ((LPC_GPIO1->PIN&(1<<24)) != 0) 
//Примерные эмпирические данные: dU = 1 В - dF = 11,4 кГц: 0,0877 В/кГц (8.77 Г/кГц при 10 мв/Г)

#define _Kvf    88// мВ/кГц
//     
/*!
 * @struct PDF_data
 * @brief  Блок данных для ПДФ(в данном случае для измерения температуры) 
 */

typedef struct 
  {
    word   Fpdf  ;     //!< частота импульсов ПДФ.
    union {
      word all;
      struct {
        word  Strob     :1; //!< Наличие строба, устанавливается в прерывании
        word  Count_Beg :1; //!< Команда на начало счета, запись 1 приводит к началу расчета температуры, по окончанию расчета переменная устанавливается в 0
      }_;
    } Bits; 
    word   *TimeStrob; //!< Время прихода строба
    float  *T0Volt;    //!< Уставка, определяющая температуру при 0 Вольт на выходе датчика
    float  *Temp;      //!< Темп изменения температуы в Г/мВ
    float  Freq;       //!< Частота в кГц
    float  V_Out;      //!< Измеренное напряжение 
    float  Out;        //!< Температура в градусах
    sword  I_Out;      //!< Температура в градусах в целочисленном формате 1 гр - 10 дискрет
  } PDF_data ;

struct PDF_ust
  {
    word   imp  ;  //!< число импульсов на оборот для вычисления угла поворота.
    word   null ;  //!< нулевое положение для вычисления угла поворота.
    word   masht ; //!< масштаб для вычисления скорости.
  }  ;

  // Приводим кол-во имп. измеренное за данный промежуток к кол-ву имп. за 10мсек.
#ifndef    _PDF_base_time

  #define  _PDF_PERIOD     1000

  #define  _PDF_base_time   _MkSec( _PDF_PERIOD )
#endif

#define  _PDF_delitel   ( 1 << 10 )   // основание для коэф.масштабирования

word pdf ( word code , word num , PDF_data *ptr ) ;
void pdf_init ( void ) ;
void pdf_input( void ) ;
void PDF_Interrupt( void );
//------------------------------
#ifdef  _MAIN_INCLUDE
//------------------------------
PDF_data PDF[ _PDF_Num ] ;
float Statistic_Data[3];
word Time_Delta;
word Time_IzmTemp;
//---
#else
//---
extern float Statistic_Data[3];
extern PDF_data PDF[ _PDF_Num ] ;
//---
#endif
#endif
