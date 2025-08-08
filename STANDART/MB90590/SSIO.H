#ifndef ssio
#define ssio

    void        sio_start(void);

#define  sio_out(out)  SDR = out;\
                       SMCS_STRT = 1;\
                       while ( SMCS_BUSY == 1 )

#define  sio_in(inp)   SMCS_STRT = 1;\
                       while ( SMCS_BUSY == 1 );\
                       inp = SDR
#endif                 
