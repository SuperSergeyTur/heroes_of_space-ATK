#ifndef  _SYSTIMER_H
  #define  _SYSTIMER_H

#define  _FreqMHz_			((d)SystemCoreClock / 1000000.0 ) // количество тактов в мкс

#define  SYSTICK_PERIOD		(lword)( _FreqMHz_ * 0x010000 - 1 ) // T = 65535 мкс
#define  timer1        		LPC_TIM0->TC //(word)LPC_TIM0->TC
#define _TimerDiscreta       (d)1.0    // в FR дискрета таймера 1 мкс
#define  _TIMER0_IRQ_PRIORITY 		IntPriority(0, 0)
/*
// Макросы работы с системным таймером
#define  _Tick              (float)(1000.0) / ((float)SystemCoreClock / 1000000.0) // 8,33 нс
#define  _uS_				(float)SystemCoreClock / 1000000.0   // количество тиков таймера за мксек
#define  _mS_				(float)SystemCoreClock / 1000.0      // количество тиков таймера за мсек
#define  _MkSec(x)           (word)(x * _uS_)                   // от 0.0 мксек до 100000 мксек
#define  _mSec(x)           (word)(x * _mS_)                   // от 0.0 мсек до 100 мсек


lword  SysTimerTick;        // счетчик переполнения системного таймера
#define  _1mS_				(word)(Timer/_mS_)   // значения системного таймера в мс
#define  Timer1_Ovr         (word)(SysTimerTick*100  + _1mS_)  	// 32-разрядный таймер

// Макросы работы с большим таймером
#define  _mSecOvr(x)		(TTimer)(x)							// от 1 мсек до 4 294 967 295 мсек
#define  _SecOvr(x)			(TTimer)(x / 1000.0)                // от 0.001 сек до 4 294 967 сек
#define  _MinOvr(x)			(TTimer)(_SecOvr(x) / 60.0)         // от 0.1 мин до 71 582 мин
#define  _HourOvr(x)		(TTimer)(_MinOvr(x) / 60.0)			// от 0.1 ч до 1193 ч (~ 49 дней)
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


