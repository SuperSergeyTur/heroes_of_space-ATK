#ifndef _prt_pt63_h
#define _prt_pt63_h

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;


/*    Макросы для работы с ...  */

     // разрешение ИУ ('0'). - ушло
#define   mIU_Enable()
     // запрет ИУ ('1').     - ушло
#define   mIU_Disable()
//---------------

#define   mSET_Q1()    PDR1_P11 = 0
#define   mCLR_Q1()    PDR1_P11 = 1
#define   mTST_Q1()  ( ~PDR1_P11 )
//#define   mSET_Q1()    PDR1_P13 = 1  // проинвертировался выход т.к. из цепи
//#define   mCLR_Q1()    PDR1_P13 = 0  // Q1V были выкинуты оптрон и транзистор.
//#define   mTST_Q1()  ( PDR1_P13 )
//-------------

            //  Выборки к синхронному порту расширения ввода/вывода.
#define   mSSIO_CS0( data )  PDR4_P40 = data
#define   mSSIO_CS1( data )  PDR4_P41 = data
#define   mSSIO_CS2( data )  PDR4_P42 = data
#define   mSSIO_CS3( data )  PDR4_P43 = data
#define   mSSIO_CS4( data )  PDR4_P44 = data

//-------------
            //  Переключение внешнего мультиплексора АЦП и
            // выдержка времени на его переключение.
#define   mSet_MUX( num )  PDR9 = ( PDR9 & 0xC7 ) | ( (b)(num) << 3 ) ; \
         for( t_mux = timer1; (w)(timer1 - t_mux) < (w)_r.AD_pause; )

//-------------

#define   mPort_Imp( data )  PDR8 = data
#define   Port_imp_copy      PDR8
#define   mClr_ImpVozb()    mPort_Imp( 0x3F )

#define   mPort_ImpTorm( data )  PDR2 = data
#define   tPort_imp_copy         PDR2
#define   mClr_ImpTorm()    mPort_ImpTorm( 0x0F )

#define   mUSEL_set()  PDR1  |=  0x40
#define   mUSEL_clr()  PDR1  &= ~0x40
#define   mUSEL_not()  PDR1  ^=  0x40
#define    USEL        PDR1_P16

#define   mTst_autostart()   (( PDR1  &  0x80 ) != 0 )

#define   mSet_autostart()
#define   mClr_autostart()
#define   mNot_autostart()


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
        struct {  byte  n0  : 1 ;
                  byte  n1  : 1 ;
                  byte  n2  : 1 ;
                  byte  n3  : 1 ;
                  byte  n4  : 1 ;
                  byte  n5  : 1 ;
                  byte  n6  : 1 ;
                  byte  n7  : 1 ; }  _ ;
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
          union Prt  Po0_nm ;/* отнормированное состояние порта, выводимое в выходной порт. */

_register union Prt  Po1_c ;  /* копия выводимого в выходной порт. */
          union Prt  Po1_nm ;/* отнормированное состояние порта, выводимое в выходной порт. */

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
extern               union Prt    Po0_nm ;
/*------------------------------------------------*/
extern _register     union Prt    Po1_c ;
extern               union Prt    Po1_nm ;
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
