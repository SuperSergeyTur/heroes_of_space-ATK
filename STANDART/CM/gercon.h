#ifndef _gercon_h
#define _gercon_h
/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД*/

               //-----Для геркона----

void  Init_Gercon ( void ) ;

#define  Gercon1_Msk   ( 1<<10 )
#define  Gercon2_Msk   ( 1<<11 )

#ifdef   _GERCON_INT3_  // 22.10.19 ФАА для БСВ уровень PINa геркона AC(1B) =5В.
 #ifndef _VOZB_SHIM_
  #undef Gercon1_Msk
  #define Gercon1_Msk (1<<_GERCON_INT3_)
 #else
  #undef Gercon2_Msk    // 13.07.2023 10:46 - DAN для КТЕ геркон ШИМ возбудителя заводится на 2В .
  #define Gercon2_Msk (1<<_GERCON_INT3_)
 #endif
#endif

      #define   mTest_Gercon()    (  (LPC_GPIO2->PIN & Gercon1_Msk) == 0 )
      #define   mTest_GerconDC()  (  (LPC_GPIO2->PIN & Gercon2_Msk)  == 0 )

#ifndef   _GERCON_INT3_
      #define   Gercon_Int_Enable()  NVIC_EnableIRQ(EINT0_IRQn)
#else
      #define   Gercon_Int_Enable()  NVIC_EnableIRQ(EINT3_IRQn)
#endif

      #define   Gercon_Int_Enable1() NVIC_EnableIRQ(EINT1_IRQn);

      #define   Gercon_PRIORITY  IntPriority(1, 0)

#ifndef   _GERCON_INT3_
      #define   Set_Gercon_Priority()  NVIC_SetPriority(EINT0_IRQn, (Gercon_PRIORITY));\
                                       NVIC_SetPriority(EINT1_IRQn, (Gercon_PRIORITY))
#else
      #define   Set_Gercon_Priority()  NVIC_SetPriority(EINT3_IRQn, (Gercon_PRIORITY));\
                                       NVIC_SetPriority(EINT1_IRQn, (Gercon_PRIORITY))
#endif
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
