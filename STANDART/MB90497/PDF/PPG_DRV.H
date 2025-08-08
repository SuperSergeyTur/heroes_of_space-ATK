#ifndef ppg_590
#define ppg_590

extern void  PPG_init( byte n, byte clk, byte lev ) ;
extern void  PPG_set( byte n, word low, word high ) ;
extern void  PPG_start( byte n ) ;
extern void  PPG_stop( byte n, byte lev ) ;

//--------------
#endif
