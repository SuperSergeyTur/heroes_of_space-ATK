#ifndef ssio
#define ssio

    void        sio_start(void);

#define  sio_out(out)  SDR0 = out;\
                       SMCS0_STRT = 1;\
                       while ( SMCS0_BUSY == 1 )

#define  sio_in(inp)   SMCS0_STRT = 1;\
                       while ( SMCS0_BUSY == 1 );\
                       inp = SDR0
#endif                 
