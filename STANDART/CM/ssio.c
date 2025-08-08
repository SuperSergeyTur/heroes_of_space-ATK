
/*********************************************************************
 * @brief 		Setup clock rate for SSP device
 * @param[in] 	SSPx	SSP peripheral definition, should be:
 * 						- LPC_SSP0: SSP0 peripheral
 * 						- LPC_SSP1: SSP1 peripheral
 * @param[in]	target_clock : clock of SSP (Hz)
 * @return 		None
 ***********************************************************************/
static void setSSPclock (LPC_SSP_TypeDef *SSPx, uint32_t target_clock)
{
    uint32_t prescale, cr0_div, cmp_clk, ssp_clk;
    ssp_clk = PeripheralClock;

	/* Find closest divider to get at or under the target frequency.
	   Use smallest prescale possible and rely on the divider to get
	   the closest target frequency */
	cr0_div = 0;
	cmp_clk = 0xFFFFFFFF;
	prescale = 2;
	while (cmp_clk > target_clock)
	{
		cmp_clk = ssp_clk / ((cr0_div + 1) * prescale);
		if (cmp_clk > target_clock)
		{
			cr0_div++;
			if (cr0_div > 0xFF)
			{
				cr0_div = 0;
				prescale += 2;
			}
		}
	}

    // Write computed prescaler and divider back to register
    SSPx->CR0 &= (~SSP_CR0_SCR(0xFF)) & SSP_CR0_BITMASK;
    SSPx->CR0 |= (SSP_CR0_SCR(cr0_div)) & SSP_CR0_BITMASK;
    SSPx->CPSR = prescale & SSP_CPSR_BITMASK;
}




void sio_start(void)
{
//  #ifdef _MAX_SPI
 #ifdef _SPI0 //_MAX_SPI > 0

    LPC_SC->PCONP |= CLKPWR_PCONP_PCSSP0;

    LPC_SSP0->CR0 = _CR0_SPI0 ;

    LPC_SSP0->CR1 = 0 ;

    setSSPclock ( LPC_SSP0, _Hz_SPI0 ) ;

    LPC_SSP0->CR1 |= SSP_CR1_SSP_EN ;
    
    LPC_IOCON->P0_15  = D_RESERV | D_HYS_EN |0x2;      // SCK
    LPC_IOCON->P0_17  = D_RESERV | D_HYS_EN |0x2;      // MISO
    LPC_IOCON->P0_18  = D_RESERV | D_HYS_EN |0x2;      // MOSI
 #endif  
 
 #ifdef _SPI1 // _MAX_SPI > 1
    LPC_SC->PCONP |= CLKPWR_PCONP_PCSSP1;

    LPC_SSP1->CR0 = _CR0_SPI1 ;

    LPC_SSP1->CR1 = 0 ;

    setSSPclock ( LPC_SSP1, _Hz_SPI1 ) ;
    LPC_SSP1->CR1 |= SSP_CR1_SSP_EN ;
 #endif  
 
 #ifdef _SPI2 // _MAX_SPI > 2
    LPC_SC->PCONP |= CLKPWR_PCONP_PCSSP2;

    LPC_SSP2->CR0 = _CR0_SPI2 ;

    LPC_SSP2->CR1 = 0 ;

    setSSPclock ( LPC_SSP2, _Hz_SPI2 ) ;
    LPC_SSP2->CR1 |= SSP_CR1_SSP_EN ;
 #endif
 
//  #endif
  return ;
}

word read_ssio(LPC_SSP_TypeDef *SSPx)
{
  return read_write_ssio(SSPx, 0xffff);
}

void write_ssio(LPC_SSP_TypeDef *SSPx, word in)
{
  read_write_ssio(SSPx, in);
}

word read_write_ssio(LPC_SSP_TypeDef *SSPx, word in)
{
  word tmp;
 //__disable_interrupt();   
    SSPx->DR = in;

    while ( SSPx->SR & SSP_SR_BSY );
    tmp =  SSPx->DR;
 //__enable_interrupt();
    return tmp;
}

