#ifndef  pdf_drv_h
#define  pdf_drv_h

#ifndef    _PDF_Num
  #define  _PDF_Num       2
#endif

#define   _PDF_Kmul       4   // коэфф. умножения частоты ПДФ

#define   _PDF_PRIORITY   5


void pdf_drv_init( word num ) ;
word pdf_drv_read( word num ) ;
void pdf_ei( word num ) ; // разрешение прерывания для определения знака ПДФ .
void pdf_di( word num ) ; // запрет     прерывания для определения знака ПДФ .
__interrupt void pdf0_Interrupt (void);
__interrupt void pdf1_Interrupt (void);

/*   Блок данных для ПДФ   */

struct PDF_drv_data
  {
    word  time ;  // время предыдущего прихода переднего фронта импульса F00 .
    byte  sign ;  // знак направления вращения: Полож - вперед, Отриц - назад.
  }  ;

#define  pdf_drv_sign( num )   pdf_drv_data[num].sign

//------------------------------
#ifdef  _MAIN_INCLUDE
//------------------------------

struct  PDF_drv_data  pdf_drv_data[_PDF_Num] ;

#else

extern struct  PDF_drv_data  pdf_drv_data[_PDF_Num] ;

#endif

#endif
