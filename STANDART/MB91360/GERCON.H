#ifndef _gercon_h
#define _gercon_h
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

               //-----Äëÿ ãåğêîíà----

extern void EXTINT_Interrupt (void) ;

      #define   mTest_Gercon()    (  PDRK_PDK6  == 0 )
      #define   mTest_GerconDC()  (  PDRK_PDK7  == 0 )
      #define   Ext_Int_Rec      EIRR_ER6
      #define   Ext_Int_Rec1     EIRR_ER7
      #define   Gercon_Int_Enable()  Ext_Int_Rec = 0, ENIR_EN6 = 1
      #define   Gercon_Int_Enable1() Ext_Int_Rec1= 0, ENIR_EN7 = 1
      #define   Gercon_ICR       ICR06
      #define   Gercon_ICR1      ICR07
      #define   Set_Gercon_Level( data ) ELVR_LAB6 = data
      #define   Set_Gercon_Level1( data ) ELVR_LAB7 = data
      #define   Gercon_PRIORITY  17 // 28
      #define   Set_Gercon_Priority()  Gercon_ICR = Gercon_PRIORITY;Gercon_ICR1 = Gercon_PRIORITY
      #define   Low       0
      #define   High      1
      #define   Rising    2
      #define   Falling   3


/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#endif
