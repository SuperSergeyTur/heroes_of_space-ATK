#ifndef _PRT_DRV_H
#define _PRT_DRV_H

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;


//  ФАЙЛ ОПРЕДЕЛЕНИЙ ДЛЯ ОБРАБОТКИ ВНЕШНИХ ДИСКРЕТНЫХ СИГНАЛОВ.

#define  USEL_Msk       (lword)0x00000001 // Порт 1.0

#define   mSET_Q1()
#define   mCLR_Q1()

#define   mSET_Q2()
#define   mCLR_Q2()

#define   mUSEL_set()  LPC_GPIO1->CLR = USEL_Msk
#define   mUSEL_clr()  LPC_GPIO1->SET = USEL_Msk
static __INLINE void mUSEL_not()
{
  if ( (LPC_GPIO1->PIN & USEL_Msk) == 0 )
  {
	 mUSEL_clr();
  }
  else
  {
	 mUSEL_set();
  }
}

#define    USEL     ((LPC_GPIO1->PIN &= USEL_Msk) != 0)

#define   mTst_autostart()   1


   //   Константные макросы для перевода заданной постояной времени
   // фильтрации/антидребезга, из милисекунд в дискреты таймера,
   //     допустимый диапазон "0.5 мсек"..."12.0 сек" ;
#define  _Drb_msec( ax )  _MkSec( (d)ax * 1000. / 256. )

//-----  Создание шаблона порта сигналов. --
// Создание объединения для возможности обращения сразу ко всем разрядам.

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

//-----  Ячейки соответствующие портам выходных внешних сигналов. --

_register union Prt  Po0_c, Po0_nm ;  // копия выводимого в выходной порт.

//--- Ячейки соответствующие портам внешних входных сигналов.

         union Prt  Pi0_c ;  //  необработанное состояние порта.
         union Prt  Pi0_nm ;// отнормированное состояние порта.
_register union Prt  Pi0_f ;  // отфильтрованное состояние порта.
         union Prt  Pi0_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P0_t [ 8 ] ; //  Матрица ячеек для счета времени при фильтрации
                   // сигналов порта P0.

//   PORT '1'

         union Prt  Pi1_c ;  /*  необработанное состояние порта. */
         union Prt  Pi1_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi1_f ;  /* отфильтрованное состояние порта. */
         union Prt  Pi1_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P1_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P1. */

#ifdef   _Pi2_
//   PORT '2'

         union Prt  Pi2_c ;  /*  необработанное состояние порта. */
         union Prt  Pi2_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi2_f ;  /* отфильтрованное состояние порта. */
         union Prt  Pi2_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P2_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P2. */
#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern _register     union Prt    Po0_c, Po0_nm ;

/*------------------------------------------------*/

extern              union Prt     Pi0_c ,  Pi0_nm ;
extern _register    union Prt     Pi0_f ;
extern   union Prt  Pi0_cf ; /* ненормированое отфильтрованное состояние порта. */
extern     word  P0_t [ 8 ] ;

extern              union Prt     Pi1_c ,  Pi1_nm ;
extern _register    union Prt     Pi1_f ;
extern   union Prt  Pi1_cf ; /* ненормированое отфильтрованное состояние порта. */
extern     word  P1_t [ 8 ] ;

#ifdef   _Pi2_
  extern   union Prt  Pi2_c ;
  extern   union Prt  Pi2_nm ;
  extern   _register union Prt  Pi2_f ;
  extern   union Prt  Pi2_cf ;
  extern   word  P2_t [ 8 ] ;
#endif

/*------------------------------------------------*/
#endif
#endif
