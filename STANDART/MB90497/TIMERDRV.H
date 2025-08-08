#ifndef _timerdrv_h
#define _timerdrv_h
//---------------

/*  Программа инициализации послед.порта, его прерывания и буферов для прерывания.  */
extern void  Init_timer ( void ) ;

            // Для совместимости с именем таймера MCS196.
#define  timer1   TCDT

#define  DIVIDE_BY_16         16
#define  DIVIDE_BY_8          32
#define  DIVIDE_BY_STANDART   DIVIDE_BY_8  /* ВЫБОР ДЕЛИТЕЛЯ  */
#define  _R_timer1_enable   TMCSR1_TRG = 1;
#define  _R_timer0_enable   TMCSR0_TRG = 1;

    /*         Величина дискреты таймера в микросекундах.  */

#define  _TimerDiscreta   ((const d)( (d)1000000ul / ( (d)F_Quarz / (d)DIVIDE_BY_STANDART ) ))
//---------------
        // приоритеты Измерения тока и СИФУ
#define  _RelTimer0_PRIORITY   6 // приоритет.
#define  _RelTimer1_PRIORITY   5 // приоритет.
//---------------

#endif
