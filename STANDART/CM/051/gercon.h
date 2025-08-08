#ifndef _gercon_h
#define _gercon_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

               //-----Для геркона----

void  Init_Gercon ( void ) ;
void GerconAC_Interrupt (void);

#define  Gercon_Msk   ( 1<<11 )

#define   mTest_Gercon()    (  (LPC_GPIO2->PIN & Gercon_Msk) == 0 )

#define   Gercon_Int_Enable()  NVIC_EnableIRQ(EINT1_IRQn)
#define   Gercon_Int_Enable1() //NVIC_EnableIRQ(EINT1_IRQn);

#define   Gercon_PRIORITY  IntPriority(1, 0)

#define   Set_Gercon_Priority()  NVIC_SetPriority(EINT1_IRQn, (Gercon_PRIORITY))

/*
static __INLINE  void Set_Gercon_Level( byte data )
{
   switch ( data )
   {
   	case Low :
        LPC_SC->EXTMODE  &= (0x0E | EXTINT_LEVEL);
		LPC_SC->EXTPOLAR &= (0x0E | EXTINT_LOW) ;
		break;
   	case High :
		LPC_SC->EXTMODE  &= (0x0E | EXTINT_LEVEL) ;
		LPC_SC->EXTPOLAR &= (0x0E | EXTINT_HIGH) ;
		break;
   	case Rising :
		LPC_SC->EXTMODE  &= (0x0E | EXTINT_EDGE) ;
		LPC_SC->EXTPOLAR &= (0x0E | EXTINT_LOW) ;
		break;
   	case Falling :
		LPC_SC->EXTMODE  &= (0x0E | EXTINT_EDGE) ;
		LPC_SC->EXTPOLAR &= (0x0E | EXTINT_HIGH) ;
		break;
   }
}

static __INLINE  void Set_Gercon_Level1( byte data )
{
   switch ( data )
   {
   	case Low :
		LPC_SC->EXTMODE  &= (0x0D | (EXTINT_LEVEL << 1)) ;
		LPC_SC->EXTPOLAR &= (0x0D | EXTINT_LOW << 1 ) ;
		break;
   	case High :
		LPC_SC->EXTMODE  &= (0x0D | EXTINT_LEVEL << 1 ) ;
		LPC_SC->EXTPOLAR &= (0x0D | EXTINT_HIGH << 1 ) ;
		break;
   	case Rising :
		LPC_SC->EXTMODE  &= (0x0D | EXTINT_EDGE << 1 ) ;
		LPC_SC->EXTPOLAR &= (0x0D | EXTINT_LOW << 1 ) ;
		break;
   	case Falling :
		LPC_SC->EXTMODE  &= (0x0E | EXTINT_EDGE << 1 ) ;
		LPC_SC->EXTPOLAR &= (0x0E | EXTINT_HIGH << 1 ) ;
		break;
   }
}
*/
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/
#endif
