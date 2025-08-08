/*------------------------------------------------------------------------
  VECTORS.C
  - Interrupt level (priority) setting
  - Interrupt vector definition

------------------------------------------------------------------------*/

//#include "mb90590.h"

/*------------------------------------------------------------------------
   InitIrqLevels()

   This function  pre-sets all interrupt control registers. It can be used
   to set all interrupt priorities in static applications. If this file
   contains assignments to dedicated resources, verify  that the
   appropriate controller is used.

   NOTE: value 7 disables the interrupt and value 0 sets highest priority.
   NOTE: Two resource interrupts always share one ICR register.
*/
/*------------------------------------------------------------------------
   Prototypes

   Add your own prototypes here. Each vector definition needs is proto-
   type. Either do it here or include a header file containing them.

*/
__interrupt void DefaultIRQHandler (void);
__interrupt  void SIFU_Interrupt ( void );

/*------------------------------------------------------------------------
   Vector definiton

   Use following statements to define vectors. All resource related
   vectors are predefined. Remaining software interrupts can be added here
   as well.
   NOTE: If software interrupts 0 to 7 are defined here, this might
   conflict with the reset vector in the start-up file.
*/

#pragma intvect DefaultIRQHandler  9    /* software interrupt 9         */
#pragma intvect DefaultIRQHandler 10    /* exeception handler           */
#pragma intvect DefaultIRQHandler 11    /* Time-base timer              */
#pragma intvect EXT_Interrupt     12    /* External interrupt(INT0-INT7)*/
#pragma intvect CAN0_RX_Interrupt 13    /* CAN 0 RX                     */
#pragma intvect DefaultIRQHandler 14    /* CAN 0 TX/NX                  */
#pragma intvect CAN1_RX_Interrupt 15    /* CAN 1 RX                     */
#pragma intvect DefaultIRQHandler 16    /* CAN 1 TX/NX                  */
#pragma intvect DefaultIRQHandler 17    /* PPG 0/1                      */
#pragma intvect DefaultIRQHandler 18    /* PPG 2/3                      */
#pragma intvect DefaultIRQHandler 19    /* PPG 4/5                      */
#pragma intvect DefaultIRQHandler 20    /* PPG 6/7                      */
#pragma intvect DefaultIRQHandler 21    /* PPG 8/9                      */
#pragma intvect DefaultIRQHandler 22    /* PPG A/B                      */
#pragma intvect DefaultIRQHandler 23    /* 16-bit Reload Timer 0        */
#pragma intvect DefaultIRQHandler 24    /* 16-bit Reload Timer 1        */
#pragma intvect pdf0_Interrupt    25    /* Input Capture 0/1            */
//#pragma intvect REVERS_Interrupt  26    /* Output Capture 0/1           */
#pragma intvect DefaultIRQHandler 27    /* Input Capture 2/3            */
#pragma intvect SIFU_Interrupt    28    /* Output Capture 2/3           */
#pragma intvect DefaultIRQHandler 29    /* Input Capture 4/5            */
#pragma intvect SIFUV_Interrupt   30    /* Output Capture 4/5           */
#pragma intvect AD_Interrupt      31    /* A/D Converter                */
#pragma intvect Timer_Interrupt   32    /* I/O Timer / Watch Timer      */
#pragma intvect DefaultIRQHandler 33    /* Serial I/O                   */
#pragma intvect DefaultIRQHandler 34    /* Sound Generator              */
#pragma intvect RXD_Interrupt     35    /* UART 0 RX                    */
#pragma intvect TXD_Interrupt     36    /* UART 0 TX                    */
#pragma intvect DefaultIRQHandler 37    /* UART 1 RX                    */
#pragma intvect DefaultIRQHandler 38    /* UART 1 TX                    */
#pragma intvect DefaultIRQHandler 39    /* UART 2 RX                    */
#pragma intvect DefaultIRQHandler 40    /* UART 2 TX                    */
#pragma intvect DefaultIRQHandler 41    /* Flash Memory                 */
#pragma intvect DefaultIRQHandler 42    /* Delayed interrupt            */

/*------------------------------------------------------------------------
   DefaultIRQHandler()

   This function is a placeholder for all vector definitions. Either use
   your own placeholder or add necessary code here.
*/
__interrupt
void DefaultIRQHandler (void)
{
  return ;
    //__DI();                              /* disable interrupts */
    //while(1)
      //  __wait_nop();                    /* halt system */
}


//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
     //  Т.к. на 2 ЕПА приходится одно прерывание,
    // то уже в нем различаем запрос.
__interrupt  void SIFU_Interrupt ( void )
{
 // if     ( _Sifu_int1 == 1 ) S_Interrupt() ;
//  else    Sifu_int_drv(_gashenie_epa_con) ;  // сброс запроса прерывания.
  //S_Interrupt() ;
    if ( _Sifu_int )
    {
      S_Interrupt ();
    }
    else
    {
      Revers_Interrupt ();
    }
  return ;
}
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
     //  Т.к. на 2 ЕПА приходится одно прерывание,
    // то уже в нем различаем запрос.
__interrupt  void SIFUV_Interrupt ( void )
{
#ifdef _Vozb_KTE
  Vozb_Interrupt() ;
#endif
  return ;
}
//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
     //  Т.к. на 2 ЕПА приходится одно прерывание,
    // то уже в нем различаем запрос.
//__interrupt  void REVERS_Interrupt ( void )
//{
//  Revers_Interrupt () ;
//  return ;
//}

__interrupt  void EXT_Interrupt ( void )
{
    if ( EIRR_ER0 )
    {
      GerconAC_Interrupt () ;
      Ext_Int_Rec = 0;
    }
    else if ( EIRR_ER1 )
    {
      GerconDC_Interrupt () ;
      Ext_Int_Rec1 = 0;
    }
  return ;
}

