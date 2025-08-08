#ifndef ppg_FR
#define ppg_FR

extern void  PPG_init( byte n, byte clk, byte lev ) ;
extern void  PPG_set( byte n, word low, word high ) ;
extern void  PPG_start( byte n, byte s ) ;
extern void  PPG_stop( byte n, byte lev ) ;

#define F_pb           16000000
#define F_Mh           16

//--------------
#ifdef _MAIN_INCLUDE

word ppg_dut[8][2];

#else

extern word ppg_dut[8][2];

#endif
#endif
