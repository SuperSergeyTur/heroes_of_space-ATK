#ifndef  _SYSTIMER_H
  #define  _SYSTIMER_H

#define  _FreqMHz_			((d)SystemCoreClock / 1000000.0 ) // ���������� ������ � ���

#define  SYSTICK_PERIOD		(lword)( _FreqMHz_ * 0x010000 - 1 ) // T = 65535 ���
#define  timer1        		LPC_TIM0->TC //(word)LPC_TIM0->TC
#define _TimerDiscreta       (d)1.0    // � FR �������� ������� 1 ���
#define  _TIMER0_IRQ_PRIORITY 		IntPriority(0, 0)
/*
// ������� ������ � ��������� ��������
#define  _Tick              (float)(1000.0) / ((float)SystemCoreClock / 1000000.0) // 8,33 ��
#define  _uS_				(float)SystemCoreClock / 1000000.0   // ���������� ����� ������� �� �����
#define  _mS_				(float)SystemCoreClock / 1000.0      // ���������� ����� ������� �� ����
#define  _MkSec(x)           (word)(x * _uS_)                   // �� 0.0 ����� �� 100000 �����
#define  _mSec(x)           (word)(x * _mS_)                   // �� 0.0 ���� �� 100 ����


lword  SysTimerTick;        // ������� ������������ ���������� �������
#define  _1mS_				(word)(Timer/_mS_)   // �������� ���������� ������� � ��
#define  Timer1_Ovr         (word)(SysTimerTick*100  + _1mS_)  	// 32-��������� ������

// ������� ������ � ������� ��������
#define  _mSecOvr(x)		(TTimer)(x)							// �� 1 ���� �� 4 294 967 295 ����
#define  _SecOvr(x)			(TTimer)(x / 1000.0)                // �� 0.001 ��� �� 4 294 967 ���
#define  _MinOvr(x)			(TTimer)(_SecOvr(x) / 60.0)         // �� 0.1 ��� �� 71 582 ���
#define  _HourOvr(x)		(TTimer)(_MinOvr(x) / 60.0)			// �� 0.1 � �� 1193 � (~ 49 ����)
  */
//void SysTimer_Init( void );
void Init_timer( void );
extern "C" {

void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);
void TIMER2_IRQHandler (void);
void TIMER3_IRQHandler (void);
}//extern "C" 

#endif


