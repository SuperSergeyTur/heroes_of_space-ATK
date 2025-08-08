//#ifndef _BTE
#include "lpc177x_8x_exti.h"
extern "C" {
#if !(defined(_BTE) || defined(_CCT))

void  EINT0_IRQHandler( void )
{
   GerconAC_Interrupt ();
   LPC_SC->EXTINT |= 0x01;
}


void  EINT1_IRQHandler( void )
{
   GerconDC_Interrupt ();
   LPC_SC->EXTINT |= 0x02;
}

#else  // _CCT

void  EINT0_IRQHandler( void )
{
      EXTINT_Interrupt () ;
   LPC_SC->EXTINT |= 0x01;
}


void  EINT1_IRQHandler( void )
{
      EXTINT_Interrupt () ;
   LPC_SC->EXTINT |= 0x02;
}

#endif

#ifdef   _GERCON_INT3_
void  EINT3_IRQHandler( void )
{
   EXTINT_Interrupt () ;
   LPC_SC->EXTINT |= EXTI_EINT3_BIT_MARK;

}
#endif

}//extern "C" 

void  Init_Gercon ( void )
{
    EXTI_InitTypeDef EXTICfg;
//------------------внешние прерывания-------
//Сброс регистров в 0
    EXTI_Init();
//Настройка прерываний 1 и 2
    EXTICfg.EXTI_Line = EXTI_EINT0;
    EXTICfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
    EXTICfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE ;

    EXTI_Config(&EXTICfg);

    EXTICfg.EXTI_Line = EXTI_EINT1;

    EXTI_Config(&EXTICfg);
#ifdef   _GERCON_INT3_
    //EXTICfg.EXTI_polarity = EXTI_POLARITY_HIGH_ACTIVE_OR_RISING_EDGE ;

    EXTICfg.EXTI_Line = EXTI_EINT3;

    EXTI_Config(&EXTICfg);
#endif    
}
