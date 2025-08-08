
void  Start_RXD_TXD ( void )
{
  Reg_ServiceMsg   = 0 ;

  Label          = 0x0u    ;

  M_FirstCall    = 1 ;
  Pult_Prog_Addr = 0 ;
  Klav_Buff = 0 ;
  m_old = 0 ;


  Mon.UartCAN_Connect = 0 ;
//  Mon.FirstCall       = 0 ;
  Mon.i2c_busy        = 0;

  Mon.NewCiklMsg      = 0 ;
 // Mon.EnableSrvMsg    = 0 ;
  Mon.RX_Data_ok      = 0 ;
  Mon.Password_Ok    = 0 ;
  Mon.RXBuffOverflow = 0 ;
  Count_SymbolPauza = _SymbolPauza ;

    Mon.Pult  = 1  ;
//    Mon.Parolle = 0  ;
    Mon.EnableSrvMsg = 1 ;
//    Mon.Otkl_InOut = 0 ;

//    Mon.i2c_busy = 0 ;
//    Mon.RXBuffOverflow = 0 ;

  OutTxBuffCount = 0x0u   ;
  InTxBuffCount  = 0x01u  ;
  OutRxBuffCount = 0x0u   ;
  InRxBuffCount  = 0x01u  ;

  UART_Init( _PULT_ );
  NVIC_EnableIRQ(UART0_IRQn);

}




void   mRestart_Output( void )
{        // если порт свободен и есть данные на вывод ...
//    if ( ( SODR0_FREE == 1  ) && (  ((OutTxBuffCount + 1) & TxBuffSize) != InTxBuffCount )  )
    if (  (LPC_UART0->LSR & UART_LSR_TEMT) && (  ((OutTxBuffCount + 1) & TxBuffSize) != InTxBuffCount )  )
    {     //  и пульт не в режиме медленного вывода то запускаем прерывания:
         //разрешаем прерыв., а т.к. TDRE всегда взведен, то прерыв. сразу сработает.
      if ( Mon.Pult == 0 && Mon.UartCAN_Connect == 0 )
	  {
					OutTxBuffCount = ( OutTxBuffCount + 1 ) & TxBuffSize ;
					LPC_UART0->THR = TxBuff[(w)OutTxBuffCount] ;
	  }
    }
  return ;
}



/*
static __INLINE void output_c( byte symbol )
{
	TxBuff[(word)InTxBuffCount] = (byte)(symbol);
	InTxBuffCount = ( InTxBuffCount + 1 ) & TxBuffSize;
}

static __INLINE void output_s( const char *ptr )
{

  while( ( ((InTxBuffCount + 1) & TxBuffSize) != OutTxBuffCount ) && (*ptr != 0) )
  {
      output_c ( *(ptr++) ) ;
  }
  Restart_Output ()  ;

}


static  word TestCompleted_Output( void )
{
   return (!( ((OutTxBuffCount + 1) & TxBuffSize) != InTxBuffCount ));
}

static  word  TestData_for_Input ( void )
{
   return   ( ((OutRxBuffCount + 1) & RxBuffSize) != InRxBuffCount ) ;
}


static __INLINE void mInput_c( char *symbol )
{
	OutRxBuffCount = ( OutRxBuffCount + 1 ) & RxBuffSize;
	*symbol = RxBuff[(w)OutRxBuffCount];
}
*/


//----------------------------------------------------------------------------------------------------------------------------

static byte UART_SetDivisors(LPC_UART_TypeDef *UARTx, uint32_t baudrate)
{
	byte 	errorStatus = FAIL;

	uint32_t uClk;
	uint32_t d, m, bestd, bestm, tmp;
	uint64_t best_divisor, divisor;
	uint32_t current_error, best_error;
	uint32_t recalcbaud;

	// get UART block clock
	uClk = PeripheralClock;

//	 In the Uart IP block, baud rate is calculated using FDR and DLL-DLM registers
//	 The formula is :
//	 BaudRate= uClk * (mulFracDiv/(mulFracDiv+dividerAddFracDiv) / (16 * (DLL)
//	 It involves floating point calculations. That's the reason the formulae are adjusted with
//	 Multiply and divide method.

//	 The value of mulFracDiv and dividerAddFracDiv should comply to the following expressions:
//	 0 < mulFracDiv <= 15, 0 <= dividerAddFracDiv <= 15
	best_error = 0xFFFFFFFF; /* Worst case */
	bestd = 0;
	bestm = 0;
	best_divisor = 0;

	for (m = 1 ; m <= 15 ;m++)
	{
		for (d = 0 ; d < m ; d++)
		{
			divisor = ((unsigned long long)uClk << 28)*m / (baudrate*(m+d));
			current_error = divisor & 0xFFFFFFFF;

			tmp = divisor>>32;

			/* Adjust error */
			if(current_error > ((lword)1<<31))
			{
				current_error = -current_error;
				tmp++;
			}

			/* Out of range */
			if(tmp < 1 || tmp > 65536)
				continue;

			if( current_error < best_error)
			{
				best_error = current_error;
				best_divisor = tmp;
				bestd = d;
				bestm = m;

				if(best_error == 0)
					break;
			}
		} /* end of inner for loop */

		if (best_error == 0)
			break;
	} /* end of outer for loop  */

	/* can not find best match */
	if(best_divisor == 0)
		return FAIL;

	recalcbaud = (uClk >> 4) * bestm / (best_divisor * (bestm + bestd));

	/* reuse best_error to evaluate baud error*/
	if(baudrate > recalcbaud)
		best_error = baudrate - recalcbaud;
	else
		best_error = recalcbaud -baudrate;

	best_error = best_error * 100 / baudrate;

	if (best_error < UART_ACCEPTED_BAUDRATE_ERROR)
	{
			UARTx->LCR |= UART_LCR_DLAB_EN;

			UARTx->DLM = UART_LOAD_DLM(best_divisor);

			UARTx->DLL = UART_LOAD_DLL(best_divisor);

			/* Then reset DLAB bit */
			UARTx->LCR &= (~UART_LCR_DLAB_EN) & UART_LCR_BITMASK;

			UARTx->FDR = (UART_FDR_MULVAL(bestm) | UART_FDR_DIVADDVAL(bestd)) & UART_FDR_BITMASK;
		errorStatus = PASS;
	}

	return errorStatus;
}

extern "C" {

void UART0_IRQHandler( void )
{
	lword intsrc, tmp, tmp1;
	char al;

	// Определение источника прерывани
	intsrc = LPC_UART0->IIR & 0x03CF;
	tmp = intsrc & UART_IIR_INTID_MASK;

	// Receive Line Status
	if ( tmp == UART_IIR_INTID_RLS )
	{
		// Check line status
		tmp1 = LPC_UART0->LSR & UART_LSR_BITMASK;
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE | UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if ( tmp1 )
		{
			//SysError._.Pult = 1;
		}
	}


	if ( tmp == UART_IIR_INTID_CTI )
	{
	    al = (char)(LPC_UART0->RBR & UART_RBR_MASKBIT) ; /* чтобы сбросить лишний запрос */

	}


	// Receive Data Available or Character time-out
	if (  tmp == UART_IIR_INTID_RDA )
	{
	   RxBuff[(w)InRxBuffCount] = (byte)(LPC_UART0->RBR & UART_RBR_MASKBIT);
	   InRxBuffCount = ( InRxBuffCount + 1 ) & RxBuffSize;
       Mon.RX_Data_ok = 1 ;
	}

	// Transmit Holding Empty
        if (Mon.Pult  == 0)
        {
	    if ( tmp == UART_IIR_INTID_THRE )
	    {
	      LPC_UART0->IER &= ~( UART_IER_THREINT_EN );
              if ( (((OutTxBuffCount + 1) & TxBuffSize) != InTxBuffCount) && Mon.UartCAN_Connect == 0 )
              {
                  OutTxBuffCount = ( OutTxBuffCount + 1 ) & TxBuffSize ;
	          LPC_UART0->THR = TxBuff[(w)OutTxBuffCount] ;
	      }
              LPC_UART0->IER |=  UART_IER_THREINT_EN ;
	    }
       }
}
}//extern "C"


void UART_Init( byte port )
{
  LPC_UART_TypeDef *pUARTx;
  TUART_Config	UartConfig;
  lword tmp;
  IRQn_Type _UART_IRQ;

  if ( port == _PULT_ ) // Пультовый терминал
  {
    LPC_SC->PCONP |= CLKPWR_PCONP_PCUART0;

    pUARTx = LPC_UART0;
	_UART_IRQ = UART0_IRQn ;

	UartConfig.baudrate = 19200;
	UartConfig.data = UART_DATABIT_8;
	UartConfig.parity = UART_PARITY_NONE;
	UartConfig.stop = UART_STOPBIT_1;
	UartConfig.RS485.on = UART_RS485_DIS;
  }
#ifndef P_CH

  else
  {                     // _RS485_
    LPC_SC->PCONP |= CLKPWR_PCONP_PCUART2;
	LPC_IOCON->P2_6  = D_RESERV | 0x4; 					// RS485.RTS (UART2.OE)
	LPC_IOCON->P2_8  = D_RESERV | 0x2; 					// RS485.TX
	LPC_IOCON->P2_9  = D_RESERV | 0x2; 					// RS485.RX

	pUARTx = LPC_UART2;
	_UART_IRQ = UART2_IRQn ;

// Устанавливаем скорость
	if ( _r.rs485.config._.b19200 == 1 )
	{
	  UartConfig.baudrate = 19200;
      Time_rs_frame = _MkSec(1800);
	}
	else
	  if ( _r.rs485.config._.b38400 == 1 )
	  {
	    UartConfig.baudrate = 38400;
        Time_rs_frame = _MkSec(900);
	  }
	  else
		if ( _r.rs485.config._.b57600 == 1 )
  		{
          UartConfig.baudrate = 57600;
          Time_rs_frame = _MkSec(600);
  		}
  		else
  	    {
          UartConfig.baudrate = 9600;
          Time_rs_frame = _MkSec(3600);
		}


	UartConfig.data = UART_DATABIT_8;
// Устанавливаем четность
	if ( _r.rs485.config._.parityon == 1 )
	{
	   if ( _r.rs485.config._.parity == 1 )
	   {
	     UartConfig.parity = UART_PARITY_EVEN;
	   }
	   else
	   {
	     UartConfig.parity = UART_PARITY_ODD;
	   }
	}
	else
	{
	     UartConfig.parity = UART_PARITY_NONE;
	}
// Устанавливаем стоп-бит
	if ( _r.rs485.config._.stopbit == 1 )
	{
	   UartConfig.stop = UART_STOPBIT_1;
	}
	else
	{
	   UartConfig.stop = UART_STOPBIT_2;
	}

	//UartConfig.RS485.on = UART_RS485_EN;


  }
#endif
	// FIFOs are empty
	pUARTx->FCR = ( UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS);
	// Disable FIFO
	pUARTx->FCR = 0;
	// Dummy reading
	while (pUARTx->LSR & UART_LSR_RDR)
	{
		tmp = pUARTx->RBR;
	}

	pUARTx->TER = UART_TER_TXEN;
	// Wait for current transmit complete
	while (!(pUARTx->LSR & UART_LSR_THRE));

	// Disable Tx
	pUARTx->TER = 0;
	// Disable interrupt
	pUARTx->IER = 0;
	// Set LCR to default state
	pUARTx->LCR = 0;
	// Set ACR to default state
	pUARTx->ACR = 0;
	// Set RS485 control to default state
	pUARTx->RS485CTRL = 0;
	// Set RS485 delay timer to default state
	pUARTx->RS485DLY = 0;
	// Set RS485 addr match to default state
	pUARTx->ADRMATCH = 0;
	// Dummy reading
	tmp = pUARTx->LSR;
	// Set IrDA to default state for all UART other than UART1
	pUARTx->ICR = 0;

	// Set Line Control register ----------------------------
	UART_SetDivisors(pUARTx, (UartConfig.baudrate));

	tmp = (pUARTx->LCR & (UART_LCR_DLAB_EN | UART_LCR_BREAK_EN)) & UART_LCR_BITMASK;

	switch (UartConfig.data)
	{
		case UART_DATABIT_5:
			tmp |= UART_LCR_WLEN5;
			break;
		case UART_DATABIT_6:
			tmp |= UART_LCR_WLEN6;
			break;
		case UART_DATABIT_7:
			tmp |= UART_LCR_WLEN7;
			break;
		case UART_DATABIT_8:
		default:
			tmp |= UART_LCR_WLEN8;
			break;
	}

	if (UartConfig.parity != UART_PARITY_NONE)
	{
		tmp |= UART_LCR_PARITY_EN;
		switch (UartConfig.parity)
		{
			case UART_PARITY_ODD:
				tmp |= UART_LCR_PARITY_ODD;
				break;
			case UART_PARITY_EVEN:
				tmp |= UART_LCR_PARITY_EVEN;
				break;
			case UART_PARITY_SP_1:
				tmp |= UART_LCR_PARITY_F_1;
				break;
			case UART_PARITY_SP_0:
				tmp |= UART_LCR_PARITY_F_0;
				break;
			default:
				break;
		}
	}

	switch (UartConfig.stop)
	{
		case UART_STOPBIT_2:
			tmp |= UART_LCR_STOPBIT_SEL;
			break;
		case UART_STOPBIT_1:
		default:
			break;
	}

	// Write back to LCR, configure FIFO and Disable Tx
	pUARTx->LCR = (byte)(tmp & UART_LCR_BITMASK);


// Конфигурируем FIFO

  if ( port == _PULT_ ) // Пультовый терминал
  {
	pUARTx->FCR = (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0 | UART_FCR_TX_RS | UART_FCR_RX_RS ) & UART_FCR_BITMASK;
  }
  else
  {
  	pUARTx->FCR = (UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0 | UART_FCR_TX_RS | UART_FCR_RX_RS
#ifdef _DMA_RS485_
                                        | UART_FCR_DMAMODE_SEL
#endif
                       ) & UART_FCR_BITMASK;
  }


    pUARTx->TER |= UART_TER_TXEN;

// Устанавливаем прерывани
	pUARTx->IER |= (UART_IER_RBRINT_EN | UART_IER_RLSINT_EN | UART_IER_THREINT_EN);
    // preemption = 1, sub-priority = 1
    NVIC_SetPriority(_UART_IRQ, IntPriority(3, 6));
	// Enable Interrupt for UART2 channel
    //NVIC_EnableIRQ(_UART_IRQ);

#ifdef _DMA_RS485_
  if ( port != _PULT_ ) // Пультовый терминал
  {  // инициализация DMA с привязкой к UART для Modbus
    RS485_DMA_Init ( NULL, 0 );
  }
#endif
}


void Speed_Pult (void )
{
  if (Mon.Pult  == 1)
   {

     //NVIC_EnableIRQ(UART0_IRQn);
     Mon.Pult  = 0;
   }
   else
   {
     Mon.Pult  = 1;
     //NVIC_DisableIRQ(UART0_IRQn);
   }
   Pult_Prog_Addr = _MainPultProg ;
}

void Set_Uart_Speed(word baudrate)
{
  UART_SetDivisors(LPC_UART0, baudrate);

}

