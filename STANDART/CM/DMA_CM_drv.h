#ifndef  _DMA_H
  #define  _DMA_H


#include "lpc177x_8x_gpdma.h"

// Terminal Counter flag for Channel 
extern __IO uint32_t Channel0_TC;
extern __IO uint32_t Channel1_TC;
extern __IO uint32_t Channel2_TC;

// Error Counter flag for Channel 
extern __IO uint32_t Channel0_Err;
extern __IO uint32_t Channel1_Err;
extern __IO uint32_t Channel2_Err;

/************************** PRIVATE FUNCTIONS *************************/
extern "C" {
void DMA_IRQHandler (void);
}//extern "C"

void GPDMA_Init_Start (void);

#endif //_DMA_H