#ifndef _s400
#define _s400

    void       S400_input ( byte cs_n, byte Port, byte code);
    void       S400_output ( byte cs_n, byte Port);

#ifndef  _SInp_max

#define  _SInp_max   2

#endif

#ifndef  _SOut_max

#define  _SOut_max   1

#endif
    // вынесено вверх, из-за inc2.c в КТЭ из-за замены d obj.h _MAIN_INCLUDE на _OBJ_INCLUDE
extern _x_far  const word  PS_tu [_SInp_max][ 8 ] ; /*  Матрица уставок времени фильтрации сигналов. */

                /* имитация выходного порта. */
#ifdef  _MAIN_INCLUDE

         union Prt  PoS_c[_SOut_max] ;  //копия выводимого в выходной порт.
         union Prt  PiS_c[_SInp_max] ;  // необработанное состояние порта.
         union Prt  PiS_nm[_SInp_max] ;// отнормированное состояние порта.
         union Prt  PiS_f[_SInp_max] ;  // отфильтрованное состояние порта.
         union Prt  PiS_cf[_SInp_max] ; // ненормированое отфильтрованное состояние порта.

         word  PS_t [ _SInp_max ][ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                                         /* сигналов порта P0. */
         byte  ssio_busy;
#else

  extern union Prt  PoS_c[_SOut_max] ;

  extern union Prt  PiS_c[_SInp_max] ;  /*  необработанное состояние порта. */
  extern union Prt  PiS_nm[_SInp_max] ;/* отнормированное состояние порта. */
  extern union Prt  PiS_f[_SInp_max] ;  /* отфильтрованное состояние порта. */
  extern union Prt  PiS_cf[_SInp_max] ; /* ненормированое отфильтрованное состояние порта. */

  extern word  PS_t [ _SInp_max ][ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                                         /* сигналов порта P0. */
  extern byte  ssio_busy;

#endif

#endif
