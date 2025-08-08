#ifndef _s400
#define _s400

#ifdef _BTE_NEW


  // ВЫXОДЫ:
  // 1. задали несуществующий адрес (в нашем случае _Clr_CS = 0x07 )
  // 2. перевели GPIO в выход
  // 3. установили данные
  // 4. установили адресс _Set_CS
  // 5. подождали
  // 6. защелкнули данные посредством смены адреса ( в нашем случае очисткой _Clr_CS )
  // 7. если есть еще выходные порты повторили операции с пункта 3
  // 8. после выдачи данных во все порты перевели порт во вход

  // ВXОДЫ:
  // 1. задали несуществующий адрес (в нашем случае _Clr_CS = 0x07 )
  // 2. перевели GPIO во вход
  // 3. установили адресс _Set_CS
  // 4. подождали
  // 5. считали данные
  // 6. задали несуществующий адрес (в нашем случае _Clr_CS = 0x07 )
  // 7. если есть еще входные порты повторили операции с пункта 3

    byte BuffIO_in ( void ) ;
    void BuffIO_out ( byte cs_n,  byte  port_out ) ;

    #define PORT_BUFF           LPC_GPIO2
    #define PIN_PORT_BUFF       0x00ff0000

    #define SET_GPIO_PiS()      PORT_BUFF->DIR &=   (~PIN_PORT_BUFF) ;               \
                                LPC_IOCON->P2_16  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_17  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_18  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_19  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_20  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_21  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_22  = D_RESERV | D_MODE_PULLUP | 0;    \
                                LPC_IOCON->P2_23  = D_RESERV | D_MODE_PULLUP | 0

    #define SET_GPIO_PoS()      PORT_BUFF->DIR |=   PIN_PORT_BUFF ;


    #define Pinp_al(al)         al= ((b)(LPC_GPIO2->PIN >> 16) & 0xff)

    #define Pout_al(port_out)     PORT_BUFF->PIN = ( PORT_BUFF->PIN & (~PIN_PORT_BUFF)) | (((lw)port_out<<16) & PIN_PORT_BUFF )
                               // Port_CS->PIN = ( Port_CS->PIN & (~PinPort_CS)) | (((lw)num<<26) & PinPort_CS )
                               // PORT_BUFF->PIN = ((lw)(port_out & 0xFF)) << 16

#endif

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
