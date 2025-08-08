
//------- ���� �� ����� #DEFINE-������� ( ����� ����������� � INCLUDE.H ) :

//#define  _INTERPRETER    // ���������� ���� ���������������� .

// ���������� ��� ����� ��� ��������������� ����������� ���������� ������� :
//#define  _CM3_ - ���������� � ��������� ������� .

#ifdef  _CM3_
  //#define _MAX_SPI   2
  #define _SPI0 // ���� ��� S400, S500
  #define _SPI1 // ���� ��� �������� ���
  //#define _SPI2 // ���� ���� �� ������������
  //��������� ������� � ���� ��� ���������� ��� ����� ����������
  #define _free_Space_Reg 200
  #define _Hz_SPI0   500000
  #define _Hz_SPI1   20000000
  #define _ADC_SPI   LPC_SSP1
  #define _ADC_CS    LPC_GPIO3
  #define _CR0_SPI0  SSP_CR0_DSS(8) | SSP_CR0_FRF_SPI | SSP_CR0_CPOL_HI | SSP_CR0_CPHA_SECOND
  #define _CR0_SPI1  SSP_CR0_DSS(16) | SSP_CR0_FRF_SPI | SSP_CR0_CPOL_HI
  #define _SPP_S500  LPC_SSP0
  #define _ADC_12_         // 12-�� ��������� ���
  #define _PDF_FiltrNumb     0x100
  #define _PDF_FiltrNumbINX  0x100

//#define _Adc_Extend      // �������������� ������� ������������� ��� .
//#define _Adc_Extend_Inv  // �������������� ������� ��� �������� �������������� (��������, ���� ���������� �� Po0) .
//#define _Adc_Extend_Po0  // �������������� ������� ������������� ��� �� ����� ��������� ����� 0 .
//#define  Mux_Port LPC_GPIO2
//#define  Mux_Pins(data) (data&0x3f)<<24
//#define _Num_Mux     3   // ���������� ���� �������������������� ������� ��� .
//#define _Ch13_Mux        // �������������������� ����� ��� .
//#define _Ch14_Mux        // �������������������� ����� ��� .
//#define _Ch15_Mux        // �������������������� ����� ��� .
//#define _Dat_Temp_Max 24 // ��� ��������� ����������� ��������� ����������� ������� ���������� � ������ ������� ����� .
  #define _MaxSaveSled   _SizeSledPole-1 // ������ ���� �� ������ , ��� _SizeSledPole � INCLUDE.H .
  #define _SizeAddr_i2c_ 4
#else
  #define _SizeAddr_i2c_ 2
#endif

#define    _Monitor_start_page 0x8000  // ��������� �������� ������ ��� �������� .
//---
#define    _SIFU2_         // 12-�������� ����� ����������� .
//#define  _Gercon_APV     // ��� ������� ����� �� ����������� �� ���.�������.
#define    _POWER          // ������� �������� ��������� .
//---
//#define  _SIFU_Syn2      // ���� �� ��������� ������������� �� ����� ��� ����.
//#define  _KTE_5          // ���������� ����������� �� �� (������ ����� ����������� ����, � �� ��) .
//#define  _KONTAKTOR_for_ProboyTir // ��������� �������������� ������� - 3� ������ ��������� , ��� ��������� �������� ��� ���� �� ����������
//#define  _Id_on_Itt_for_ProboyTir // �� ��� �� �� ��������������� ���� , ����� ��� ����� ��������� ������� ���� ������ ����������
//#define  _Synch_3f       // ��������� ������������� .
//---
#define    _AVTONASTR      // ������������� ��
#define    _JOURNAL        // ������� "�������"
#define    _CombRedact     // ������� ������ � ���� "����.������".
#define    _WatchDog       // ������� �������-�������
//---
// ��� PPG5 �� ����� P1.22 . ������� #4 ������ ���� 2-3 .
//---
//#define  _CH5_PWM        // ���� ������� #4:1-2 , �� PPG5 ��� ��� �� ����� P2.2 . ������ ����������� ���� ���� �� ����� .
//---
#define    _S500           // ������� ����� ����� S500 (��� S250) ������ S400 (��� S200)
//---
//#define  _STOLB_1TIR     // ������� �� ������ ���������� - �� 3 ��� .
//---
//#define  _SELS_NULL      // ��������� ���� �������� � "F2-�������."
//#define  _NARABOTKA      // ������� ��������� �������� � ����� .

//#define  _AF_Otkl_Q1     // ���������� Q1 � ������ ��������� � �� �� ������ �������������� .
//---
//#define  _CANOPEN
//#define  _CAN_MASTER     // �� ������� ���� ���� ���� CAN ������������� �� ������ ��� ������
//#define  _CAN_MASTER_PORT  _CAN0_Port // ����������� CAN0-����� ��� �������
//#define  _CAN_MASTER_PORT  _CAN1_Port // ����������� CAN1-����� ��� �������
//---
#define    _NET_IRQ        // ia????N ?N?No�? �?a?? ?aN?n??�a
#define    _DMA_RS485_     // ��������� ��� �� RS485 ��� ���������� ������� ���� ��� ��������
//---
//#define  _AZIMUT         // ������� �� 0 �� 360��� .
//---
//#define  _REG_POL        // ��������� ���������
//#define  _RP_OS_S0_      // �������� ����� ��� �� �� �������� 0
//#define  _RP_OS_S1_      // �������� ����� ��� �� �� �������� 1
//#define  _RP_OS_PDF_     // �������� ����� ��� �� �� ���
//#define  _RP_ZIS         // ����������� ������ �� �� ���� ���
//---
//#define  _ONE_REG        // ���� ������� ���������
//#define  _TRETIY_REG     // ������ ������� ���������
#define    _Sld_cond       // ��������� ����� �� �������
//---
//#define  _Rev_Pola       // ������ ����.
//#define  _RS_10ms_       // ������ ���������� �� ��� � 3 ������.
//---
#define    _Po0_INVERT     // ������� ����������� �������� �������� �������� .
//#define  _AsPo_INVERT    // ������� ����������� �������� �������� �������� ������ ����� S400/S500 ��� S200/S250 .
//---
#define    _DST            // ��������� ������� ������������ ���� .
//#define  _RDN            // ��������� ���������� ������� �������� .
//#define  _RRS            // ��������� ���� : ���������� ��������������� �������� .
//#define  _BUKSOVKA       // �������� �������� ( ����� ���� ) .
//#define  _RVId           // ��������� ���������� ������������ ����� �����
//---
//#define  _Obj_Id_izm     // ��������� ��������� ����������� ���� Id .
//#define  _Obj_Id_conv    // ��������� �������������� ����������� ���� Id .
//#define  _Obj_Id_Max     // ��������� ���������� ������ �� ���� Id .
//---
//#define  _Obj_Id2_izm    // ��������� ��������� � �������������� ����������� ���� Id2 .
//---
//#define  _ZI_4TEMPA      // ��� � 4-�� ������� : �� ������ � ���������� ������ ������� .
//#define  _ZI_30min       // �� �� 30 ����� .
//---
//#define  _Perecl_DS      // ��� ������������� �� ������������� �� ��� ��� ������ .
#define     bi_xQ1  ( bi_AK1 == 1 || bi_AK2 == 1 ) // ���������� Q1 , ����� ��� �/� ������� .
#define     bi_xQ2  1 //( bi_VAT == 1 ) //( bi_Vkl_Q2 == 1 && bi_Otkl_Q2 == 0 ) // ���������� Q2 , ����� ��� �/� ������� .
//---
//#define  _T_PDF          // ��������� �� �� �� ������� ��� ��������� ���������
//#define  _USEL_obj       // ��������� ���������� USEL . ����� �� ���������� ������, ����������, ������ .
//---
//--- ������� � �������� ����� :
//----------------
#define    _Po0_
//----------------
//#define  _AsPo0_
//#define  _AsPo1_
//#define  _AsPo2_
//#define  _AsPo3_
//#define  _AsPo4_
//#define  _AsPo5_
//#define  _AsPo6_
//#define  _AsPo7_
//----------------
#define    _Pi1_
//----------------
#define    _AsPi0_
#define    _AsPi1_
//#define  _AsPi2_
//#define  _AsPi3_
//#define  _AsPi4_
//#define  _AsPi5_
//#define  _AsPi6_
//#define  _AsPi7_
//#define  _AsPi8_
//#define  _AsPi9_
//#define  _AsPi10_
//#define  _AsPi11_
//#define  _AsPi12_
//#define  _AsPi13_
//#define  _AsPi14_
//#define  _AsPi15_
//----------------
#ifdef     _Adc_Extend_Po0      // �������������� ������� ������������� ��� �� ����� ��������� ����� 0 .
#define    _AsPo_Av_Pr_Got_  1  // ����� ����� , � ������� ��������� ������ , ���������� , �������������� .
#endif
