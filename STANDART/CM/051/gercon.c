//#ifndef _BTE
#include "lpc177x_8x_exti.h"
extern "C" {
void  EINT1_IRQHandler( void )
{
   GerconAC_Interrupt ();
   LPC_SC->EXTINT |= 0x02;
}
}//extern "C"

void  Init_Gercon ( void )
{
    EXTI_InitTypeDef EXTICfg;
//------------------внешние прерывания-------
//Сброс регистров в 0
    EXTI_Init();
//Настройка прерываний 1 и 2
    EXTICfg.EXTI_Line = EXTI_EINT1;
    EXTICfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
    EXTICfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE ;

    EXTI_Config(&EXTICfg);
}
