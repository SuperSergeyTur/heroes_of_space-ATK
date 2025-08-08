
#include "lpc177x_8x_gpdma.c"


// Terminal Counter flag for Channel
 __IO uint32_t Channel0_TC;
 __IO uint32_t Channel1_TC;
 __IO uint32_t Channel2_TC;

// Error Counter flag for Channel
 __IO uint32_t Channel0_Err;
 __IO uint32_t Channel1_Err;
 __IO uint32_t Channel2_Err;

/************************** PRIVATE FUNCTIONS *************************/


/*----------------- INTERRUPT SERVICE ROUTINES --------------------------*/
/*********************************************************************//**
 * @brief		GPDMA interrupt handler sub-routine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
extern "C" {
void DMA_IRQHandler (void)
{
	uint32_t tmp;
		// Scan interrupt pending
	for (tmp = 0; tmp <= 7; tmp++)
        {
		if (GPDMA_IntGetStatus(GPDMA_STAT_INT, tmp))
                {
			// Check counter terminal status
			if(GPDMA_IntGetStatus(GPDMA_STAT_INTTC, tmp))
                        {
				// Clear terminate counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTTC, tmp);

				switch (tmp)
                                {
					case 0:
						Channel0_TC++;
						GPDMA_ChannelCmd(0, DISABLE);
						break;
					case 1:
						Channel1_TC++;
						GPDMA_ChannelCmd(1, DISABLE);
						break;
					case 2:
						Channel2_TC++;
						GPDMA_ChannelCmd(2, DISABLE);
						break;
					case 3:
						GPDMA_ChannelCmd(3, DISABLE);
						break;
					case 4:
						GPDMA_ChannelCmd(4, DISABLE);
						break;
					case 5:
						GPDMA_ChannelCmd(5, DISABLE);
						break;
					case 6:
						GPDMA_ChannelCmd(6, DISABLE);
						break;
					case 7:
						GPDMA_ChannelCmd(7, DISABLE);
						break;
					default:
						break;
				}

			}
				// Check error terminal status
			if (GPDMA_IntGetStatus(GPDMA_STAT_INTERR, tmp))
                        {
				// Clear error counter Interrupt pending
				GPDMA_ClearIntPending (GPDMA_STATCLR_INTERR, tmp);
				switch (tmp)
                                {
					case 0:
						Channel0_Err++;
						GPDMA_ChannelCmd(0, DISABLE);
						break;
					case 1:
						Channel1_Err++;
						GPDMA_ChannelCmd(1, DISABLE);
						break;
					case 2:
						Channel2_Err++;
						GPDMA_ChannelCmd(2, DISABLE);
						break;
					case 3:
						GPDMA_ChannelCmd(3, DISABLE);
						break;
					case 4:
						GPDMA_ChannelCmd(4, DISABLE);
						break;
					case 5:
						GPDMA_ChannelCmd(5, DISABLE);
						break;
					case 6:
						GPDMA_ChannelCmd(6, DISABLE);
						break;
					case 7:
						GPDMA_ChannelCmd(7, DISABLE);
						break;

					default:
						break;
				}
			}
		}
	}
}
}//extern "C"


void GPDMA_Init_Start (void)
  {
          /* Initialize GPDMA controller */
	GPDMA_Init();

	/* Setting GPDMA interrupt */
          // Disable interrupt for DMA
        NVIC_DisableIRQ (DMA_IRQn);
        /* preemption = 1, sub-priority = 1 */
        NVIC_SetPriority(DMA_IRQn, IntPriority(3, 6));
  }


