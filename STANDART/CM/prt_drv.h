#ifndef _PRT_DRV_H
#define _PRT_DRV_H

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;


//  ФАЙЛ ОПРЕДЕЛЕНИЙ ДЛЯ ОБРАБОТКИ ВНЕШНИХ ДИСКРЕТНЫХ СИГНАЛОВ.

#define   _Sync_mask   (0x01)

#define  _Gotov_mask   (0x80)

#define  _Q1_Msk		0x00000002  // Порт P1.1
#define  _Q2_Msk		0x00000010  // Порт P1.4

#define   mSET_Q1()    LPC_GPIO1->CLR = _Q1_Msk
#define   mCLR_Q1()    LPC_GPIO1->SET = _Q1_Msk

#define   mSET_Q2()    LPC_GPIO1->CLR = _Q2_Msk
#define   mCLR_Q2()    LPC_GPIO1->SET = _Q2_Msk

#define   set_strob_usredn()   LPC_GPIO0->CLR |= _ADC_USR_Msk
#define   clr_strob_usredn()   LPC_GPIO0->SET |= _ADC_USR_Msk

//#define  _ADC_MUX_Msk			(7UL<<27)
//#define  _ADC_MUX_SET(n)		((n & 0x07)<<27)


#define  _ADC_USR_Msk			(3UL<<29)

#define  _ADC_SELL_Msk                  (1UL<<31)


//---------------------------

     // разрешение ИУ ('0'). - ушло
#define   mIU_Enable()
     // запрет ИУ ('1').     - ушло
#define   mIU_Disable()

 #ifndef   _SIFU2_
#define   mPort_Imp( data )  LPC_GPIO3->PIN =(LPC_GPIO3->PIN&0xff00ffff)|( (data & 0x3F) << 16 )
 #else
// 01.04.2016 - В 12-пульсных КТЭ , при отключении Ведущего моста и самостоятельной работе Ведомого моста
//              всё равно работает СИФУ1 , подающее ИУ на Ведомый мост .
// Если Ведущий мост не отключен , кладём ИУ Ведущего , а если отключен - кладём ИУ Ведомого :
#define   mPort_Imp( data )  if ( S.flg._.VneshZp == 0 )  LPC_GPIO3->PIN =(LPC_GPIO3->PIN&0xff00ffff)|( (data & 0x3F) << 16 );\
                             else                         LPC_GPIO3->PIN =(LPC_GPIO3->PIN&0x00ffffff)|( (data & 0x3F) << 24 )
 #endif

#define   Port_imp_copy      LPC_GPIO3->PIN

#define   mPort_Imp2( data )  LPC_GPIO3->PIN = (LPC_GPIO3->PIN&0x00ffffff)|( (data & 0x3F) << 24 )
#define   Port_imp2_copy      LPC_GPIO3->PIN
#define   mClr_ImpVozb()    mPort_Imp( 0x3F ), mPort_Imp2( 0x3F )

//#define   mPort_ImpV( data )  PDRS = data
#define   mPort_ImpV( data )  LPC_GPIO3->PIN = (LPC_GPIO3->PIN&0x00ffffff)|( (data & 0x3F) << 24 )

#define  USEL_Msk		(lword)0x00000010 // Порт 5.4
#define  PINSTOP_Msk	(lword)0x00000001 // Порт 5.0

#define   mUSEL_set()  LPC_GPIO5->CLR = USEL_Msk
#define   mUSEL_clr()  LPC_GPIO5->SET = USEL_Msk
static __INLINE void mUSEL_not()
{
  if ( (LPC_GPIO5->PIN & USEL_Msk) == 0 )
  {
	 mUSEL_clr();
  }
  else
  {
	 mUSEL_set();
  }
}

#define    USEL     ((LPC_GPIO5->PIN &= USEL_Msk) != 0)

#define   mTst_autostart()   (  LPC_GPIO5->PIN & PINSTOP_Msk )



//#define   mSet_MUX( num )  LPC_GPIO0->PIN = ( LPC_GPIO0->PIN & ~(_ADC_MUX_Msk) ) | ( _ADC_MUX_SET(num)  ) ; \
//         for( t_mux = timer1; (w)(timer1 - t_mux) < (w)_r.AD_pause; )


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
        struct {  word  n0 : 1 ;
                  word  n1 : 1 ;
                  word  n2 : 1 ;
                  word  n3 : 1 ;
                  word  n4 : 1 ;
                  word  n5 : 1 ;
                  word  n6 : 1 ;
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
