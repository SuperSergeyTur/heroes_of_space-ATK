#ifndef  pdf_h
#define  pdf_h

#include <pdf_drv.h>

//����� ������ ���������� ���������
#define _ReloadValue_us  5000
#define _StrobTempPin    ((LPC_GPIO1->PIN&(1<<24)) != 0) 
//��������� ������������ ������: dU = 1 � - dF = 11,4 ���: 0,0877 �/��� (8.77 �/��� ��� 10 ��/�)

#define _Kvf    88// ��/���
//     
/*!
 * @struct PDF_data
 * @brief  ���� ������ ��� ���(� ������ ������ ��� ��������� �����������) 
 */

typedef struct 
  {
    word   Fpdf  ;     //!< ������� ��������� ���.
    union {
      word all;
      struct {
        word  Strob     :1; //!< ������� ������, ��������������� � ����������
        word  Count_Beg :1; //!< ������� �� ������ �����, ������ 1 �������� � ������ ������� �����������, �� ��������� ������� ���������� ��������������� � 0
      }_;
    } Bits; 
    word   *TimeStrob; //!< ����� ������� ������
    float  *T0Volt;    //!< �������, ������������ ����������� ��� 0 ����� �� ������ �������
    float  *Temp;      //!< ���� ��������� ���������� � �/��
    float  Freq;       //!< ������� � ���
    float  V_Out;      //!< ���������� ���������� 
    float  Out;        //!< ����������� � ��������
    sword  I_Out;      //!< ����������� � �������� � ������������� ������� 1 �� - 10 �������
  } PDF_data ;

struct PDF_ust
  {
    word   imp  ;  //!< ����� ��������� �� ������ ��� ���������� ���� ��������.
    word   null ;  //!< ������� ��������� ��� ���������� ���� ��������.
    word   masht ; //!< ������� ��� ���������� ��������.
  }  ;

  // �������� ���-�� ���. ���������� �� ������ ���������� � ���-�� ���. �� 10����.
#ifndef    _PDF_base_time

  #define  _PDF_PERIOD     1000

  #define  _PDF_base_time   _MkSec( _PDF_PERIOD )
#endif

#define  _PDF_delitel   ( 1 << 10 )   // ��������� ��� ����.���������������

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
