#ifndef _epa_drv_h
#define _epa_drv_h
//---------------

//  ��� Input CAPTURE

        // ��������� i-���� ������ EPA ��� ������ �������������.
word init_syn_epa( word channel )  ;

      //   ����������� ��������� ����������� compare-EPA.
/*
#define  mSet_sifu_epa_priority( channel, priority )  NVIC_SetPriority( TIMER1_IRQn, priority);\
                                                      priorityIRQ[TIMER1_IRQn] = priority
*/
#define  mSet_sifu_epa_priority( channel, priority )                                                                    \
{                                                                                                                       \
  if      ( channel == _OCS0  )                                            NVIC_SetPriority( TIMER3_IRQn, priority);    \
  else if ( channel == _OCS1 || channel == _OCS2  ||  channel == _OCS3 )   NVIC_SetPriority( TIMER1_IRQn, priority);    \
  else if ( channel == _OCS4 || channel == _OCS5 )                         NVIC_SetPriority( TIMER2_IRQn, priority);    \
}


        //   �������� ������������� � ���.
// BTE
// ������������� �� ���� (��� ����) - capture (�� ����� - CAP0)
#define   _synch_epa_con     _ICS0  // ������������� �� �������� ������� �� .
#define   _synch_epa_time    LPC_TIM3->CR0
//#define   _synch3_epa_con    _ICS1  // ������������� �� �������� ������� �� (���� ������ ��� �������� �����������).
//#define   _synch3_epa_time   LPC_TIM0->CR0

//#define   _synch2_epa_con    _ICS1  // ������������� �� ����� ������� .
//#define   _synch2_epa_time   LPC_TIM0->CR0
//#define   _synch3_epa_con    _ICS2  // ������������� �� ����� ������� .
//#define   _synch3_epa_time   LPC_TIM1->CR0

/* Pin   - Datash  - Shems - function        */
/* P1.10 - T3_CAP0 - CAP0  - Synh Most       */
/* P1.26 - T0_CAP0 - CAP1  - Cntrl Cheredov  */
/* P1.18 - T1_CAP0 - CAP2  - CUc             */
/* P1.19 - T1_CAP1 - CAP3  - Us              */

/* SVTG
#define   GUa_epa_con    _ICS1
#define   GUa_epa_time   LPC_TIM0->CR0   // Us

#define   CUa_epa_con    _ICS2
#define   CUa_epa_time   LPC_TIM1->CR0   // CUc
*/
// BTE
// Us - capture (�� ����� - CAP3)
#define   GUa_epa_con    _ICS3
#define   GUa_epa_time   LPC_TIM1->CR1   
// CUc - capture (�� ����� - CAP2)
#define   CUa_epa_con    _ICS2
#define   CUa_epa_time   LPC_TIM1->CR0   

        //   �������� ��������� � ���.
//#define   _selsin0_epa_con     _ICS1
//#define   _selsin0_epa_time    LPC_TIM0->CR0

//#define   _selsin1_epa_con     _ICS2 // � SIFU.H �������� � �����. �� ���� .
//#define   _selsin1_epa_time    LPC_TIM1->CR0

//#define   _selsin1_epa_con     _ICS1 // � SIFU.H �������� � �����. �� ���� .
//#define   _selsin1_epa_time    LPC_TIM0->CR0

    //  �������� ������� ������� EPA.
#define _ICS0 ( 0x0 )
#define _ICS1 ( 0x1 )
#define _ICS2 ( 0x2 )
#define _ICS3 ( 0x3 )
#define _ICS4 ( 0x4 )

// �� ������� ������
#define _CAP0_NEG_EDGE ( 0x02 )
#define _CAP1_NEG_EDGE ( 0x02 )
#define _CAP2_NEG_EDGE ( 0x02 )
#define _CAP3_NEG_EDGE ( 0x10 )
#define _CAP4_NEG_EDGE ( 0x02 )

// �� ��������� ������
#define _CAP0_POS_EDGE ( 0x01 )
#define _CAP1_POS_EDGE ( 0x01 )
#define _CAP2_POS_EDGE ( 0x01 )
#define _CAP3_POS_EDGE ( 0x08 )
#define _CAP4_POS_EDGE ( 0x01 )

// �� ����� �������
#define _CAP0_BOTH_EDGE ( 0x03 )
#define _CAP1_BOTH_EDGE ( 0x03 )
#define _CAP2_BOTH_EDGE ( 0x03 )
#define _CAP3_BOTH_EDGE ( 0x18 )
#define _CAP4_BOTH_EDGE ( 0x03 )

      //   ���������� ���������� �� ���.
void ei_syn_epa( word channel ) ;
           // ����� ������� ����������.
void Syn_int_drv( word channel ) ; //, word code ) ;

        // ��������� ��� - ����������� ���������.
#define _ICS0_PRIORITY   IntPriority(2, 1)  //����.����� - �apture
#define _ICS1_PRIORITY   IntPriority(2, 1)  //�� ���. (�� ����� CAP1)
#define _ICS23_PRIORITY  IntPriority(2, 1)  //Us + CUc - capture

//---------------
//  ��� Output COMPARE

      //   ��������� ��������� ������ compare-EPA ��� C���.
word init_sifu_epa( word channel ) ;
           // ����� ������� ����������.
void Sifu_int_drv( word channel ) ; //, word code ) ;

    //  �������� �������� ������� EPA.
#define _OCS0 ( 0x0 )  //LPC_TIM3->MR1   // _suiu_epa_con
#define _OCS1 ( 0x1 )  //LPC_TIM1->MR1   // _suii_epa_con
#define _OCS2 ( 0x2 )  //LPC_TIM1->MR2
#define _OCS3 ( 0x3 )  //LPC_TIM1->MR3   // _sifu_epa_con
#define _OCS4 ( 0x4 )  //LPC_TIM2->MR2
#define _OCS5 ( 0x5 )  //LPC_TIM2->MR3

        // ��������� ��� - ����������� ���������.
#define _OCS1_PRIORITY   IntPriority(2, 1) //    (2, 1) ��� ����, ���� ��������� ���� ����� ���� ������� ���� ����
#define _OCS2_PRIORITY   IntPriority(2, 1) // Us + CUc - match registers. (� extern.h -> #define   _sifu_high_priority  IntPriority(2, 0))

//�������� ��������� ���  ������������ � ����������� �� Fujitsu

#define   OCCP0   LPC_TIM3->MR1
#define   OCCP1   LPC_TIM1->MR1
#define   OCCP2   LPC_TIM1->MR2
#define   OCCP3   LPC_TIM1->MR3
#define   OCCP4   LPC_TIM2->MR2
#define   OCCP5   LPC_TIM2->MR3
//#define   Sifu_IRQn   TIMER3_IRQn
//#define   Revers_IRQn TIMER1_IRQn
//#define   Sifuv_IRQn  TIMER1_IRQn
//---------------
#endif
