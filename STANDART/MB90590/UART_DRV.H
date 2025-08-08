#ifndef _uart_drv_h
#define _uart_drv_h
//---------------

/*  Для UART0  */

__interrupt void RXD_Interrupt (void);
__interrupt void TXD_Interrupt (void);

#define  mSymbol_in_TXD_port(data)  UODR0 = data
//#define _SCR1_REC      ( 0x04 )

#ifdef _MAIN_INCLUDE
    char   TXD_FREE  ;  /* Признак того, что буфер вывода опустел, прерывания
                         прекратились и без затравки не возобновятся.  */
#else
    extern char   TXD_FREE  ;
#endif

//---------------
#endif
