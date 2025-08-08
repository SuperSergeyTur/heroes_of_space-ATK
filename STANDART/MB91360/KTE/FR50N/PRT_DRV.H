#ifndef _port_h
#define _port_h

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;


//  ФАЙЛ ОПРЕДЕЛЕНИЙ ДЛЯ ОБРАБОТКИ ВНЕШНИХ ДИСКРЕТНЫХ СИГНАЛОВ.

#define   _Sync_mask   (0x01)

#define  _Gotov_mask   (0x80)

#define   mSET_Q1()    PDRL_PDL4 = 0
#define   mCLR_Q1()    PDRL_PDL4 = 1

#define   mSET_Q2()    PDRL_PDL5 = 0
#define   mCLR_Q2()    PDRL_PDL5 = 1

#define   set_strob_usredn()   PDR0_PD04 = 0
#define   clr_strob_usredn()   PDR0_PD04 = 1

#define   mSetProfiRes()   PDR0_PD05 = 1
#define   mClrProfiRes()   PDR0_PD05 = 0

              //  Для ВВ-УМП.
#define   mSetSbrosTriggProboy( data )  PDR0_PD04 = data

//---------------------------

     // разрешение ИУ ('0'). - ушло
#define   mIU_Enable()
     // запрет ИУ ('1').     - ушло
#define   mIU_Disable()

 #ifndef   _SIFU2_
#define   mPort_Imp( data )  PDRR = data
 #else
// 01.04.2016 - В 12-пульсных КТЭ , при отключении Ведущего моста и самостоятельной работе Ведомого моста
//              всё равно работает СИФУ1 , подающее ИУ на Ведомый мост .
// Если Ведущий мост не отключен , кладём ИУ Ведущего , а если отключен - кладём ИУ Ведомого :
#define   mPort_Imp( data )  if ( S.flg._.VneshZp == 0 )  PDRR = data;  else  PDRS = data
 #endif

#define   Port_imp_copy      PDRR

#define   mPort_Imp2( data )  PDRS = data
#define   Port_imp2_copy      PDRS
#define   mClr_ImpVozb()    mPort_Imp( 0x3F ), mPort_Imp2( 0x3F )

//#define   mPort_ImpV( data )  PDRS = data
#define   mPort_ImpV( data )  PDRS = ( (PDRS & 0xC0) | (data & 0x3F) )

#define   mUSEL_set()  PDRB_PDB2 = 1            //PDRB  |=  0x04
#define   mUSEL_clr()  PDRB_PDB2 = 0            //PDRB  &= ~0x04
#define   mUSEL_not()  PDRB_PDB2 = ~PDRB_PDB2   //PDRB  ^=  0x04
#define    USEL        PDRB_PDB2

#define   mTst_autostart()   ( PDRI_PDI3 == 1 )

   //   Константные макросы для перевода заданной постояной времени
   // фильтрации/антидребезга, из милисекунд в дискреты таймера,
   //     допустимый диапазон "0.5 мсек"..."12.0 сек" ;
#define  _Drb_msec( ax )  _MkSec( (d)ax * 1000. / 256. )

//-----  Создание шаблона порта сигналов. --
// Создание объединения для возможности обращения сразу ко всем разрядам.

  union Prt   {
        byte all ;
        struct {  word  n7  : 1 ;
                  word  n6  : 1 ;
                  word  n5  : 1 ;
                  word  n4  : 1 ;
                  word  n3  : 1 ;
                  word  n2  : 1 ;
                  word  n1  : 1 ;
                  word  n0  : 1 ; }  _ ;
              } ;

/*-----  Создание шаблона порта логическиех сигналов. -- */
/* Создание объединения для возможности обращения сразу ко всем разрядам. */

  union Prt16   {
        word all ;
        struct {  word  n15 : 1 ;
                  word  n14 : 1 ;
                  word  n13 : 1 ;
                  word  n12 : 1 ;
                  word  n11 : 1 ;
                  word  n10 : 1 ;
                  word  n9  : 1 ;
                  word  n8  : 1 ;
                  word  n7  : 1 ;
                  word  n6  : 1 ;
                  word  n5  : 1 ;
                  word  n4  : 1 ;
                  word  n3  : 1 ;
                  word  n2  : 1 ;
                  word  n1  : 1 ;
                  word  n0  : 1 ; }  _ ;
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
