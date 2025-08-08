#ifndef _prt_pt63_h
#define _prt_pt63_h

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;


/*    Макросы для работы с ...  */

     // разрешение ИУ ('0').
/*#define   mIU_Enable()   PDR1_P11 = 0
     // запрет ИУ ('1').
#define   mIU_Disable()  PDR1_P11 = 1

#define   mSet_Q1()    PDR1_P13 = 0
#define   mClr_Q1()    PDR1_P13 = 1*/

#define   mPort_Imp( data )  PDR0 = data
#define   Port_imp_copy      PDR0
#define   mClr_ImpVozb()    mPort_Imp( 0xFC )

//#define   bo_1GL_Ok    PDR6_P63

#define   mUSEL_set()  PDR1  |=  0x40 , Po0_c._.n6 = 1
#define   mUSEL_clr()  PDR1  &= ~0x40 , Po0_c._.n6 = 0
#define   mUSEL_not()  PDR1  ^=  0x40 , Po0_c._.n6 = ~Po0_c._.n6
#define    USEL        PDR1_P16

#define   mTst_autostart()   PDR1_P17 == 1

//Аварию РОТ делаем как Q1V
#define   mSET_Q1()    PDR1_P15 = 0
#define   mCLR_Q1()    PDR1_P15 = 1

#define   mSet_autostart()   ;
#define   mClr_autostart()   ;
#define   mNot_autostart()   ;


/*  ФАЙЛ ОПРЕДЕЛЕНИЙ ДЛЯ ОБРАБОТКИ ВНЕШНИХ ДИСКРЕТНЫХ СИГНАЛОВ. */

   /*   Константные макросы для перевода заданной постояной времени */
   /* фильтрации/антидребезга, из милисекунд в дискреты таймера, */
   /*     допустимый диапазон "0.5 мсек"..."12.0 сек" ; */
#define  _Drb_msec( ax )  _MkSec( (d)ax * 1000. / 256. )


/*--------------------------- */

/*-----  Создание шаблона порта сигналов. -- */
/* Создание объединения для возможности обращения сразу ко всем разрядам. */

  union Prt   {
        byte all ;
        struct {  word  n0  : 1 ;
                  word  n1  : 1 ;
                  word  n2  : 1 ;
                  word  n3  : 1 ;
                  word  n4  : 1 ;
                  word  n5  : 1 ;
                  word  n6  : 1 ;
                  word  n7  : 1 ; }  _ ;
              } ;

/*------------------------------------------------*/
#ifdef   _MAIN_INCLUDE
/*------------------------------------------------*/

/*--- Ячейки соответствующие портам внешних входных сигналов. */

          union Prt  Pi0_c ;  /* необработанное состояние порта. */

          union Prt  Pi0_nm ; /* отнормированное состояние порта. */

          union Prt  Pi0_cf ; /* ненормированое отфильтрованное состояние порта. */

_register union Prt  Pi0_f ;  /* отфильтрованное состояние порта. */

word  P0_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P0. */

_register     union Prt    Po0_c ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern _register     union Prt    Po0_c ;

/*------------------------------------------------*/

extern              union Prt     Pi0_c ,  Pi0_nm ;
extern _register    union Prt     Pi0_f ;
extern              union Prt     Pi0_cf ; /* ненормированое отфильтрованное
                                              состояние порта. */
extern     word  P0_t [ 8 ] ;

/*------------------------------------------------*/
#endif
#endif
