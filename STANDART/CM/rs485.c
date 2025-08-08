//#include "lpc177x_8x_uart.h"
#include "uart_drv.h"
#include "rs485.h"

/*-----------------04.02.2015 9:07------------------
 * Инициализация RS485
 * --------------------------------------------------*/
void RS485_Init( void )
{

    UART_Init( _RS485_ );

	LPC_UART2->TER = 0;
	LPC_UART2->IER = 0;
	LPC_UART2->FCR = 0;
    LPC_UART2->RS485CTRL = 0;
// Настройка FIFO
  	LPC_UART2->FCR =(UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0 | UART_FCR_TX_RS | UART_FCR_RX_RS
#ifdef _DMA_RS485_
                                        | UART_FCR_DMAMODE_SEL
#endif                       
                       ) & UART_FCR_BITMASK;        
        
// Настройка Auto Direction
	LPC_UART2->RS485CTRL |= UART_RS485CTRL_DCTRL_EN;
	LPC_UART2->RS485CTRL |= UART_RS485CTRL_OINV_1 ;

	LPC_UART2->RS485DLY = 50;

// Прерывания по UART2
	LPC_UART2->IER = UART_IER_RBRINT_EN | UART_IER_RLSINT_EN;
	NVIC_EnableIRQ( UART2_IRQn );

	state_rs = _RS_BUSOFF;
	if ( _r.rs485.config._.vkl == 1 )
	{
	    state_rs = _RS_BUSWORK;
	   	LPC_UART2->TER |= UART_TER_TXEN;
	}
#ifdef _DMA_RS485_
        RS485_DMA_Init ( NULL, 0 );
#endif        

}

void RS485_deInit( void )
{
    LPC_SC->PCONP &= ~CLKPWR_PCONP_PCUART2;
	state_rs = _RS_BUSOFF;
}

/*-----------------25.12.2012 14:39-----------------
 *  Прием сообщений по RS485 в фоне при работе с включенным прерыванием
 * -------------------------------------------------*/
lword RS485_Receive( byte *rxbuf, byte buflen )
{
 	lword bToRecv, bRecv;


	bToRecv = buflen;

	bRecv = 0;
		while (bToRecv)
		{
			if (!( LPC_UART2->LSR & UART_LSR_RDR))
			{
				break;
			}
			else
			{
				(*rxbuf++) = LPC_UART2->RBR & UART_RBR_MASKBIT;

				bRecv++;

				bToRecv--;
			}
		}

	return bRecv;
}
/*-----------------30.07.2014 16:26-----------------
 *  Прием сообщений по RS485 в прерывании
 * --------------------------------------------------*/
void RS485_IntReceive(void)
{
	byte tmpc;
	lword rLen;

	while ( 1 )
	{

//		rLen = UART_Receive( LPC_UART2, &tmpc, 1, NONE_BLOCKING );
		rLen = RS485_Receive( &tmpc, 1 );

		// Если есть данные
		if ( rLen )
		{
			// Проверяем буфер на наличие места
			if (!__BUF_IS_FULL(RSBuf.rx_head,RSBuf.rx_tail))
			{
				RSBuf.rx[RSBuf.rx_head] = tmpc;
				__BUF_INCR( RSBuf.rx_head );
			}
		}
		else
		{
			break;
		}
	}
               RS485_ResetBuffer();

}


/*-----------------30.07.2014 16:21-----------------
 * отправка фрейма
 * --------------------------------------------------*/
lword RS485_Send( byte *pData, lword size )
{
	lword bToSend, bSent, timeOut=0, fifo_cnt=0;

	bToSend = size;

	// blocking mode
		bSent = 0;
		LPC_UART2->RS485CTRL |= UART_RS485CTRL_RX_DIS;

#ifdef _DMA_RS485_
                timeOut = timeOut, fifo_cnt = fifo_cnt;
                  // ложим указатель и размер массива в DMA
                RS485_DMA_ReInit ( pData, size );
                RS485_DMA_Enable ();
#else
                
		while ( bToSend )
		{
			timeOut = UART_BLOCKING_TIMEOUT;
			// Wait for THR empty with timeout
			while ( !( LPC_UART2->LSR & UART_LSR_THRE ) )
			{
				if ( timeOut == 0 )
                {
                   break;
                }
				timeOut--;
			}
			// Time out!
			if ( timeOut == 0 )
                {
                   break;
                }
			fifo_cnt = UART_TX_FIFO_SIZE;
			while ( fifo_cnt && bToSend )
			{
				LPC_UART2->THR = (*pData++) & 0xFF;
				while ( !( LPC_UART2->LSR & UART_LSR_THRE ) );
				fifo_cnt--;
				bToSend--;
				bSent++;
			}
		}

		while (!(LPC_UART2->LSR & UART_LSR_TEMT));
		LPC_UART2->RS485CTRL &= ~(UART_RS485CTRL_RX_DIS) ;
                
#endif
	return bSent;
}

void RS485_ResetBuffer( void )
{
  LPC_UART2->FCR |= (UART_FCR_TX_RS | UART_FCR_RX_RS);
}

/*-----------------31.07.2014 11:25-----------------
 *
 * --------------------------------------------------*/
void RS485_IntErr( byte bLSErrType )
{
// Parity error
	if (bLSErrType & UART_LSR_PE)
	{
	}

// Frame error
	if (bLSErrType & UART_LSR_FE)
	{
	}

// Overrun error
	if (bLSErrType & UART_LSR_OE)
	{
	}

// Break Interrupt
	if (bLSErrType & UART_LSR_BI)
	{
	}

// RX FIFO error
	if (bLSErrType & UART_LSR_RXFE)
	{
	}
}

/*-----------------30.07.2014 16:20-----------------
 * Прерывание по UART2
 * --------------------------------------------------*/
extern "C" {
void UART2_IRQHandler(void)
{
	lword intsrc, tmp, tmp1;

	// Determine the interrupt source
	intsrc = LPC_UART2->IIR & 0x03CF;

	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS)
	{
		// Check line status
		tmp1 = LPC_UART2->LSR & UART_LSR_BITMASK;

		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI | UART_LSR_RXFE);

		// If any error exist
		if (tmp1)
		{
			RS485_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI))
	{
          Timer_rs = timer1; 
	  newbyte = 1;

	  RS485_IntReceive();
	  if ( _r.rs485.config._.master == 0 ) // Slave
	  {
            if (( RSBuf.rx[RSBuf.rx_tail] == _r.rs485.addr ) && (newFrame == 1)) //Ждем пока закончится прерывание по приему с правильным адрессом
            {
              flag_rs485 = 1;        // Флаг разрешения считывания буффера по приему и обработка информации
            }
            else  RSBuf.rx_tail = RSBuf.rx_head;
	  } 
          else                                 // Master
          {
#ifdef _ModbusMaster               
            if ( flag_busy == 1 ){ // Пока флаг 0 идет запрос.
              if (( RSBuf.rx[RSBuf.rx_tail] == _r.rs485.addr ) && (newFrame == 1)) //Ждем пока закончится прерывание по приему с правильным адрессом
              {
                flag_rs485 = 1;        // Флаг разрешения считывания буффера по приему и обработка информации
              }
              else  RSBuf.rx_tail = RSBuf.rx_head;
            }
#endif               
          }
	}

     }
}//extern "C" {









////-------------------//// ФАА 05.18 DMA, чтоб убрать побайтовую передачу(Tx) из фона ////-------------------////
#ifdef _DMA_RS485_

// Функция инициализации DMA для Modbus
//   *ptrData - указатель на массив данных 
//   size     - размер данных для отправки                                          

void RS485_DMA_Init ( byte *ptrData, lword size )
  {

	GPDMA_Channel_CFG_Type GPDMACfg;

    	/* GPDMA Interrupt configuration section ------------------------------------------------- */

	// Setup GPDMA channel --------------------------------
	// channel N
	GPDMACfg.ChannelNum = _GPDMA_CHANNEL_UART2;
	// Source memory
	GPDMACfg.SrcMemAddr = (uint32_t) ptrData;
	// Destination memory - don't care
	GPDMACfg.DstMemAddr = 0;
	// Transfer size
	GPDMACfg.TransferSize = (uint32_t)size;
	// Transfer width - don't care
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	// Source connection - don't care
	GPDMACfg.SrcConn = 0;
	// Destination connection
	GPDMACfg.DstConn = _GPDMA_CONN_UART_Tx;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);

	/* Reset terminal counter */
	RS485_DMA_CH_TC = 0;
	/* Reset Error counter */
	RS485_DMA_CH_ERR = 0;

          // Enable interrupt for DMA
        NVIC_EnableIRQ (DMA_IRQn);

	// Enable GPDMA channel 0
	//??? должно быть в функции передачи данных
        //GPDMA_ChannelCmd(_GPDMA_CHANNEL_UART2, ENABLE);              
        
  }                                                

 

// Формирование новой посылки Modbus
//   *ptrData - указатель на массив данных 
//   size     - размер данных для отправки

 void RS485_DMA_ReInit ( byte *ptrData, lword size )
  {
	GPDMA_Channel_CFG_Type GPDMACfg;
    
        //   Для отправки текущей посылки можно сделать так:
// адрес данных         LPC_GPDMACH0->CSrcAddr =   (uint32_t) ptrData  ;     
// размер данных        LPC_GPDMACH0->CControl =  (((size & 0xFFF)<<0) | GPDMA_DMACCxControl_SI | GPDMA_DMACCxControl_I ) ;
        //   Но полная переинициализация выглядит информативней
        
    	/* GPDMA Interrupt configuration section ------------------------------------------------- */

	// Setup GPDMA channel --------------------------------
	// channel N
	GPDMACfg.ChannelNum = _GPDMA_CHANNEL_UART2;
	// Source memory
	GPDMACfg.SrcMemAddr = (uint32_t) ptrData;
	// Destination memory - don't care
	GPDMACfg.DstMemAddr = 0;
	// Transfer size
	GPDMACfg.TransferSize = (uint32_t)size;
	// Transfer width - don't care
	GPDMACfg.TransferWidth = 0;
	// Transfer type
	GPDMACfg.TransferType = GPDMA_TRANSFERTYPE_M2P;
	// Source connection - don't care
	GPDMACfg.SrcConn = 0;
	// Destination connection
	GPDMACfg.DstConn = _GPDMA_CONN_UART_Tx;
	// Linker List Item - unused
	GPDMACfg.DMALLI = 0;
	// Setup channel with given parameter
	GPDMA_Setup(&GPDMACfg);

	/* Reset terminal counter */
	RS485_DMA_CH_TC = 0;
	/* Reset Error counter */
	RS485_DMA_CH_ERR = 0;

  }                                                



 // Запрет прерывания DMA Modbus
void RS485_DMA_Disable (void)
  {
	// Enable GPDMA channel
	GPDMA_ChannelCmd(_GPDMA_CHANNEL_UART2, DISABLE);
  }

// Разрешение прерывания по DMA Modbus
void RS485_DMA_Enable (void)
  {
	// Enable GPDMA channel
	GPDMA_ChannelCmd(_GPDMA_CHANNEL_UART2, ENABLE);
  }
 
 


#endif  //_DMA_RS485_
////-------------------//// ////-------------------//// End DMA ////-------------------//// ////-------------------////



