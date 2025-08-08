#ifndef _timerdrv_h
#define _timerdrv_h
//---------------

/*  Программа инициализации послед.порта, его прерывания и буферов для прерывания.  */
extern void  Init_timer ( void ) ;
extern __interrupt void Timer_Interrupt (void);
//void RelTimer_init( void);

            // Для совместимости с именем таймера MCS196.
#define  timer1   TCDT

#define  DIVIDE_BY_16         16
#define  DIVIDE_BY_STANDART   DIVIDE_BY_16  /* ВЫБОР ДЕЛИТЕЛЯ  */


    /*         Величина дискреты таймера в микросекундах.  */

#define  _TimerDiscreta   ((const d)( (d)1000000ul / ( (d)F_Quarz / (d)DIVIDE_BY_STANDART ) ))

//#define  timer2    TMRLR0

//---------------
#endif
