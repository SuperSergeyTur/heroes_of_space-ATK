#ifndef _uart_drv_h
#define _uart_drv_h
//---------------

/*  Для UART1  */

__interrupt void RXD_Interrupt (void);
__interrupt void TXD_Interrupt (void);
void Set_Uart_Speed (word baud);


#define  mSymbol_in_TXD_port(data)  SODR0 = data
//#define _SCR1_REC      ( 0x04 )

#ifdef _MAIN_INCLUDE
    char   SODR0_FREE  ;  /* Признак того, что буфер вывода опустел, прерывания
                         прекратились и без затравки не возобновятся.  */
#else
    extern char   SODR0_FREE  ;
#endif

//---------------
#endif
