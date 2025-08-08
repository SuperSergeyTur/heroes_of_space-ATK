#ifndef _gercon_h
#define _gercon_h
/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/

               //-----Äëÿ ãåğêîíà----

extern void EXTINT_Interrupt (void) ;

#define   mTest_Gercon()    (  PDR9_P92  == 1 )
#define   mTest_GerconDC()  (  PDR9_P92  == 1 )
#define   Ext_Int_Rec     EIRR_ER0
#define   Ext_Int_Rec1    EIRR_ER0
#define   Gercon_Int_Enable()  Ext_Int_Rec = 0, ENIR_EN0 = 1
#define   Gercon_Int_Enable1() Ext_Int_Rec1= 0, ENIR_EN0 = 1
#define   Gercon_ICR       ICR00
#define   Set_Gercon_Level( data ) ELVR_LALB0 = data
#define   Set_Gercon_Level1( data ) ELVR_LALB0 = data
#define   Gercon_PRIORITY  5
#define   Set_Gercon_Priority()  Gercon_ICR = Gercon_PRIORITY
#define   Low       0
#define   High      1
#define   Rising    2
#define   Falling   3

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ*/
#endif
