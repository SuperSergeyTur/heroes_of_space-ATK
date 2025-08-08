#ifndef _prt_pt63_h
#define _prt_pt63_h

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;

#define   mUSEL_set()  PDR6  |=  0x04
#define   mUSEL_clr()  PDR6  &= ~0x04
#define   mUSEL_not()  PDR6  ^=  0x04
#define    USEL        PDR6_P62

#define   mCAN_set()  PDR4  |=  0x02
#define   mCAN_clr()  PDR4  &= ~0x02
#define   mCAN_not()  PDR4  ^=  0x02

#define   mERR_set()  PDR6  |=  0x02
#define   mERR_clr()  PDR6  &= ~0x02
#define   mERR_not()  PDR6  ^=  0x02

#define   mTst_autostart()   ( PDR3_P34 == 1 )

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

/*-----  Ячейки соответствующие портам выходных внешних сигналов. -- */

_register union Prt  Po0_c ;  /* копия выводимого в выходной порт. */

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
