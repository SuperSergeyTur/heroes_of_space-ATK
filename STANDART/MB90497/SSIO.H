#ifndef ssio
#define ssio

    void        sio_start(void);
    byte        sio_input(void);
    void        sio_out(byte out);

//Для согласования программ
#define  sio_in(inp)   inp = sio_input()

#endif                 
