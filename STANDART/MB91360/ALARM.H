#ifndef _alrm_h
#define _alrm_h

void Alarm_start(void) ;
__interrupt void Alarm_interrupt(void);

#define Alarm_on()  ACSR_PD = 0
#define Alarm_off() ACSR_PD = 1

#endif


