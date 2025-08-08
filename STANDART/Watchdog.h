#ifndef _watchdog_h
#define _watchdog_h

void watchdog_init( word wd_time );
word watchdog_reset_test( void ) ;
void watchdog_reset( void );

#endif
