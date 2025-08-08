#ifndef _prt_pt63_h
#define _prt_pt63_h

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;


/*    Макросы для работы с ...  */

     // разрешение ИУ ('0').
#define   mIU_Enable()   PDR1_P11 = 0
     // запрет ИУ ('1').
#define   mIU_Disable()  PDR1_P11 = 1

#define   mSET_Q1()    PDR1_P13 = 0
#define   mCLR_Q1()    PDR1_P13 = 1
#define   mTST_Q1()  (~PDR1_P13)

#define   mPort_Imp( data )  PDR8 = data
#define   Port_imp_copy      PDR8
#define   mClr_ImpVozb()    mPort_Imp( 0x3F )

#define   mUSEL_set()  PDR3  |=  0x08, Po0_c.all |=  0x08
#define   mUSEL_clr()  PDR3  &= ~0x08, Po0_c.all &= ~0x08
#define   mUSEL_not()  PDR3  ^=  0x08, Po0_c.all ^=  0x08
#define    USEL        PDR3_P33

#define   mTst_autostart()   1

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

/*-----  Создание шаблона порта логическиех сигналов. -- */
/* Создание объединения для возможности обращения сразу ко всем разрядам. */

  union Prt16   {
        word all ;
        struct {  word  n0  : 1 ;
                  word  n1  : 1 ;
                  word  n2  : 1 ;
                  word  n3  : 1 ;
                  word  n4  : 1 ;
                  word  n5  : 1 ;
                  word  n6  : 1 ;
                  word  n7  : 1 ;
                  word  n8  : 1 ;
                  word  n9  : 1 ;
                  word  n10 : 1 ;
                  word  n11 : 1 ;
                  word  n12 : 1 ;
                  word  n13 : 1 ;
                  word  n14 : 1 ;
                  word  n15 : 1 ; }  _ ;
              } ;

/*------------------------------------------------*/
#ifdef   _MAIN_INCLUDE
/*------------------------------------------------*/

/*-----  Ячейки соответствующие портам выходных внешних сигналов. -- */

_register union Prt  Po0_c ;  /* копия выводимого в выходной порт. */
//#pragma locate    ( Po0_c = 0x0E1 )

/*--- Ячейки соответствующие портам внешних входных сигналов. */

//   PORT '0'

         union Prt  Pi0_c ;  /*  необработанное состояние порта. */
         union Prt  Pi0_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi0_f ;  /* отфильтрованное состояние порта. */
         union Prt  Pi0_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P0_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P0. */

//   PORT '1'

         union Prt  Pi1_c ;  /*  необработанное состояние порта. */
         union Prt  Pi1_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi1_f ;  /* отфильтрованное состояние порта. */
         union Prt  Pi1_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P1_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P0. */

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern _register     union Prt    Po0_c ;

/*------------------------------------------------*/

extern              union Prt     Pi0_c ,  Pi0_nm ;
extern _register    union Prt     Pi0_f ;
extern   union Prt  Pi0_cf ; /* ненормированое отфильтрованное состояние порта. */
extern     word  P0_t [ 8 ] ;

extern              union Prt     Pi1_c ,  Pi1_nm ;
extern _register    union Prt     Pi1_f ;
extern   union Prt  Pi1_cf ; /* ненормированое отфильтрованное состояние порта. */
extern     word  P1_t [ 8 ] ;

/*------------------------------------------------*/
#endif
#endif
