#ifndef _timerdrv_h
#define _timerdrv_h
//---------------


            // Для совместимости с именем таймера MCS196.
#define  timer1   TCDT0
#define  timer2   TCDT1

#define  R_BUS_CLOK         16000000
#define  DIVIDER            16              /* ВЫБОР ДЕЛИТЕЛЯ  */


    /*         Величина дискреты таймера в микросекундах.  */

#define  _TimerDiscreta   ((const d)( (d)1000000ul / ( (d)R_BUS_CLOK / (d)DIVIDER ) ))

//---------------
#endif
