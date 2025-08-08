#ifndef  pdf_drv_h
#define  pdf_drv_h

#ifndef    _PDF_Num
  #define  _PDF_Num       1
#endif

#define   _PDF_Kmul       4   // коэфф. умножения частоты ПДФ

#define   _PDF_PRIORITY   3 //4  // Приоритет ПДФ дб равен приоритету Реверса ,
                              // тк они находятся в одном регистре ICR07 .

void pdf_drv_init( word num ) ;
word pdf_drv_read( word num ) ;
void pdf_ei( word num ) ; // разрешение прерывания для определения знака ПДФ .
void pdf_di( word num ) ; // запрет     прерывания для определения знака ПДФ .
void pdf_fz_init ( word num ) ;
void pdf_fz ( word num ) ;
__interrupt void pdf0_Interrupt (void);

// Состояние прерывания для определения знака ПДФ : 1 - разреш , 0 - запреш .
#define  pdf_interrupt( _PDF_Num )  ICS01_ICE0

/*   Блок данных для ПДФ   */

struct PDF_drv_data
  {
    word  Tpdf_time ; // время предыдущего прихода переднего фронта импульса F00 ( из EPA ) .
    word  Tpdf ;      // сумма периодов импульсов ПДФ
    word  Scht_T ;    // счетчик периодов импульсов ПДФ
    byte  sign ;      // знак направления вращения: Полож - вперед, Отриц - назад.
  }  ;

#define  pdf_drv_sign( num )   pdf_drv_data[num].sign

#define   pdf_epa_time   IPCP0

//------------------------------
#ifdef  _MAIN_INCLUDE
//------------------------------
struct  PDF_drv_data  pdf_drv_data[_PDF_Num] ;
//------------------------------
#else
//------------------------------
extern struct  PDF_drv_data  pdf_drv_data[_PDF_Num] ;
//------------------------------
#endif
//------------------------------
#endif
