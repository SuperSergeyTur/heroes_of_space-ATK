#ifndef  _RS485_H
  #define  _RS485_H


#define _RS_BUSWORK		1
#define _RS_BUSOFF		0

typedef struct
{
  union
  {
	byte all;
	struct
  	{
    	byte	vkl      : 1;
    	byte	master   : 1;
		byte	b19200	 : 1;
		byte	b38400	 : 1;
		byte	b57600	 : 1;
    	byte	parityon : 1;
    	byte	parity   : 1;
    	byte	stopbit  : 1;
	}_;
  } config;
  byte      addr;
} TUART_RS;

#define  _cfg_rs_vkl   		0x01
#define  _cfg_rs_master		0x02
#define  _cfg_rs_b19200		0x04
#define  _cfg_rs_b38400		0x08
#define  _cfg_rs_b57600		0x10
#define  _cfg_rs_parityon	0x20
#define  _cfg_rs_parity		0x40
#define  _cfg_rs_stopbit	0x80


//-----------   RING BUFFER   ------------------------------
// buffer size definition
#define _RING_BUFSIZE 		256

// Buf mask
#define __BUF_MASK 						( _RING_BUFSIZE-1 )
// Check buf is full or not
#define __BUF_IS_FULL(head, tail) 		( (tail & __BUF_MASK) == ( (head+1) & __BUF_MASK) )
// Check buf will be full in next receiving or not
#define __BUF_WILL_FULL(head, tail) 	( (tail & __BUF_MASK) == ( (head+2) & __BUF_MASK) )
// Check buf is empty
#define __BUF_IS_EMPTY(head, tail) 		( (head & __BUF_MASK) == ( tail & __BUF_MASK) )
// Reset buf
#define __BUF_RESET( bufidx )			( bufidx = 0 )
#define __BUF_INCR( bufidx )			( bufidx = (bufidx+1) & __BUF_MASK )

// Ring buffer structure
typedef struct
{
    byte tx_head;                // Tx ring buffer head index
    byte tx_tail;                // Tx ring buffer tail index
    byte rx_head;                // Rx ring buffer head index
    byte rx_tail;                // Rx ring buffer tail index
    byte  tx[_RING_BUFSIZE];  // Tx data ring buffer
    byte  rx[_RING_BUFSIZE];  // Rx data ring buffer
} TRingBuffer;

//-----------------------------------------------------------

TRingBuffer RSBuf;

word state_rs;
int flag_rs485;
int flag_busy;        // SAP Флаг для отправки запроса и приема ответа мастера
word Timer_rs;        // Время прерываний UART
word TimeWait;        // SAP Время ожидания ответа после запроса SAP
word Time_rs_frame;   // Скорость/время
word newFrame, newbyte;
word FrameCount;      // SAP Номер фрейма мастера

void RS485_Init( void );
void RS485_deInit( void );
void RS485_ResetBuffer( void );




////-------------------//// ФАА 05.18 DMA, чтоб убрать побайтовую передачу(Tx) из фона ////-------------------////

#ifdef _DMA_RS485_

#include "DMA_CM_drv.h"

void RS485_DMA_Init ( byte *pData, lword size );
void RS485_DMA_ReInit ( byte *ptrData, lword size );

void RS485_DMA_Disable (void);
void RS485_DMA_Enable (void);

#define _LPC_UART			UART_2
#define _GPDMA_CONN_UART_Tx		GPDMA_CONN_UART2_Tx
#define _GPDMA_CONN_UART_Rx		GPDMA_CONN_UART2_Rx

#define _GPDMA_CHANNEL_UART2            2
#define RS485_DMA_CH_TC                 Channel2_TC
#define RS485_DMA_CH_ERR                Channel2_Err
//byte     *ptrData

  #endif  //_DMA_RS485_

////-------------------//// ////-------------------//// End DMA ////-------------------//// ////-------------------////


#endif  // _RS485_H
