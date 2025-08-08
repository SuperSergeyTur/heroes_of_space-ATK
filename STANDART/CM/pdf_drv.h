#ifndef  pdf_drv_h
#define  pdf_drv_h

#include "lpc177x_8x_qei.h"

#ifndef    _PDF_Num
  #define  _PDF_Num       1
#endif

#define   _PDF_Kmul       4

#define   _PDF_PRIORITY   18


void pdf_drv_init( word num ) ;
word pdf_drv_read( word num ) ;

// ��������� ���������� ��� ����������� ����� ��� : 1 - ������ , 0 - ������ .
#define  pdf_interrupt( _PDF_Num )  ICS23_ICE3

/*   ���� ������ ��� ���   */

struct PDF_drv_data
  {
    word  Tpdf_time ; // ����� ����������� ������� ��������� ������ �������� F00 ( �� EPA ) .
    lword  Tpdf ;      // ����� �������� ��������� ���
    lword  Scht_T ;    // ������� �������� ��������� ���
    byte  sign ;      // ���� ����������� ��������: ����� - ������, ����� - �����.
  }  ;

#define  pdf_drv_sign( num )   pdf_drv_data[num].sign

#define   pdf_epa_time   IPCP3

//------------------------------
#ifdef  _MAIN_INCLUDE
//------------------------------
struct  PDF_drv_data  pdf_drv_data[_PDF_Num] ;
word  F00_Oborot, Vel, Position;
word PDF_Oborot_Time;
//------------------------------
#else
//------------------------------
extern struct  PDF_drv_data  pdf_drv_data[_PDF_Num] ;
extern word  F00_Oborot, Vel, Position;
extern word PDF_Oborot_Time;
//------------------------------
#endif
//------------------------------
#endif
