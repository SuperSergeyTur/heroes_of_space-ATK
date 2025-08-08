#ifndef _prt_pt63_h
#define _prt_pt63_h

extern void  Port_input ( word code ) ;
extern void  Port_output ( void ) ;
extern void  Port_output_clr ( void ) ;
extern void  Port_DI8 ( word code ) ;
extern void  Port2_Filtr ( word code ) ;


/*    Макросы для работы с ...  */

     // разрешение ИУ ('0').
#define   mIU_Enable()   TRIS = 0
     // запрет ИУ ('1').     - ушло
#define   mIU_Disable()
//---------------

#define   mSET_Q1()    PDR1_P13 = 0
#define   mCLR_Q1()    PDR1_P13 = 1
#define   mTST_Q1()  (~PDR1_P13)
#define   mSET_Q2()    PDR1_P11 = 0
#define   mCLR_Q2()    PDR1_P11 = 1
#define   mTST_Q2()  (~PDR1_P11)

#define   set_strob_usredn()   PDR1_P10 = 0
#define   clr_strob_usredn()   PDR1_P10 = 1

//-------------
//    Макросы для работы с регистрами Ячейки Ввода/Вывода.
// Регистр выборки
#define   Port55_B  PDR2
// Регистр данных
#define   Port55_A  PDR7

#define   Port55_C  (PDR4 & 0xf)
// Регистр, определяющий направление передачи данных.
#define   DDR_IO    DDR7

#define   mWR_clr()  PDR5_P54 = 0
#define   mWR_set()  PDR5_P54 = 1
#define   mWR()     mWR_clr() , mWR_set()

#define   mRD_clr()  PDR5_P55 = 0
#define   mRD_set()  PDR5_P55 = 1
// Установка порта на прием данных
#define   IO_in_set()   DDR_IO = 0
// Установка порта на выдачу
#define   IO_out_set()  DDR_IO = 0xff

#define   mRD2_clr() mWR_clr()
#define   mRD2_set() mWR_set()
#define   mWR2_clr() mRD_clr()
#define   mWR2_set() mRD_set()
#define   mWR2()     mWR2_clr() , mWR2_set()

#define   mLDAC_set()  PDR1_P12 = 1
#define   mLDAC_clr()  PDR1_P12 = 0


              //  Считывание из порта входных сигналов "Защит".
#define   mDD3_Read( al )   IO_in_set();\
                            Port55_B = 0x00 ; \
                            mRD_clr() ;          \
                            al = Port55_A   ; \
                            mRD_set()


#define   mDD5_Read( al )   IO_in_set();\
                            Port55_B = 0x01 ; \
                            mRD_clr() ;          \
                            for(al=0;al <= 35; ++al);\
                            al = Port55_A   ; \
                            mRD_set()

#define   mDD6_Read( al )   IO_in_set();\
                            Port55_B = 0x02 ; \
                            mRD_clr() ;          \
                            for(al=0;al <= 35; ++al);\
                            al = Port55_A   ; \
                            mRD_set()

              //  Запись в порт выходных сигналов.
#define   mDD2_Write( al )  IO_out_set();\
                            Port55_A = (b)(~al) ; \
                            Port55_B = 0x04 ; \
                            mWR()

//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД
//       Для второй платы ввода вывода.

              //  Считывание из порта входных сигналов.
#define   mXCS6_Read( al )  IO_in_set();\
                            Port55_B = 0x0B ; \
                            mRD2_clr() ;          \
                            al = Port55_A   ; \
                            mRD2_set()

#define   mXCS7_Read( al )  IO_in_set();\
                            Port55_B = 0x13 ; \
                            mRD2_clr() ;          \
                            al = Port55_A   ; \
                            mRD2_set()

#define   mXCS8_Read( al )  IO_in_set();\
                            Port55_B = 0x1B ; \
                            mRD2_clr() ;          \
                            al = Port55_A   ; \
                            mRD2_set()

              //  Запись в порт выходных сигналов.
#define   mXCS9_Write( al ) IO_out_set();\
                            Port55_A = (b)(~al) ; \
                            Port55_B = 0x2B ; \
                            mWR2()

/*ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД-*/
//       Для  платы ввода DI8
//=====================================================

#define   mAI1_DD1_Read( al )   IO_in_set();\
                                Port55_B = 0xF3 ;  \
                                mRD_clr() ;        \
                                al = Port55_A   ;  \
                                mRD_set() ;        \
//-------------
            //  Переключение внешнего мультиплексора АЦП и
            // выдержка времени на его переключение.
#define   mSet_MUX( num )  PDR3 = ( ( PDR3 & 0xf8 ) | num ) ; \
         for( t_mux = timer1; (w)(timer1 - t_mux) < (w)_r.AD_pause; )

//-------------

#define   mPort_Imp( data )  CSI0 = 0;  \
                             PDR8 = data;\
                             CSI0 = 1

#define   Port_imp_copy      PDR8
#define   mClr_ImpVozb()    mPort_Imp( 0x3F )

#define   mPort_ImpV( data ) CSI1 = 0;\
                             PDR8 = data;\
                             CSI1 = 1


#define   mPort_ImpTorm( data )
#define   tPort_imp_copy
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

#define  TRIS     PDR4_P44
#define  CSI0     PDR3_P35
#define  CSI1     PDR3_P37

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
                   /* сигналов порта P1. */

//   PORT '2'

          union Prt  Pi2_c ;  /*  необработанное состояние порта. */
          union Prt  Pi2_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi2_f ;  /* отфильтрованное состояние порта. */
          union Prt  Pi2_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P2_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P2. */

//   PORT '3'

         union Prt  Pi3_c ;  /*  необработанное состояние порта. */
         union Prt  Pi3_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi3_f ;  /* отфильтрованное состояние порта. */
         union Prt  Pi3_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P3_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P3. */

#ifdef _DI8
//   PORT '4'

          union Prt  Pi4_c ;  /*  необработанное состояние порта. */
          union Prt  Pi4_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi4_f ;  /* отфильтрованное состояние порта. */
          union Prt  Pi4_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P4_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P4. */

#endif

#ifdef _PORTE2_

//   PORT '4'

          union Prt  Pi4_c ;  /*  необработанное состояние порта. */
          union Prt  Pi4_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi4_f ;  /* отфильтрованное состояние порта. */
          union Prt  Pi4_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P4_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P4. */

//   PORT '5'

         union Prt  Pi5_c ;  /*  необработанное состояние порта. */
         union Prt  Pi5_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi5_f ;  /* отфильтрованное состояние порта. */
         union Prt  Pi5_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P5_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P5. */

//   PORT '6'

          union Prt  Pi6_c ;  /*  необработанное состояние порта. */
          union Prt  Pi6_nm ;/* отнормированное состояние порта. */
_register union Prt  Pi6_f ;  /* отфильтрованное состояние порта. */
          union Prt  Pi6_cf ; /* ненормированое отфильтрованное состояние порта. */

word  P6_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P6. */


#endif

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern _register     union Prt    Po0_c ;
extern               union Prt    Po0_nm ;

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

extern              union Prt     Pi2_c ,  Pi2_nm ;
extern _register    union Prt     Pi2_f ;
extern   union Prt  Pi2_cf ; /* ненормированое отфильтрованное состояние порта. */
extern     word  P2_t [ 8 ] ;

extern              union Prt     Pi3_c ,  Pi3_nm ;
extern _register    union Prt     Pi3_f ;
extern   union Prt  Pi1_cf ; /* ненормированое отфильтрованное состояние порта. */
extern     word  P3_t [ 8 ] ;

#ifdef _DI8
extern    union Prt  Pi4_c ;  /*  необработанное состояние порта. */
extern    union Prt  Pi4_nm ;/* отнормированное состояние порта. */
extern _register union Prt  Pi4_f ;  /* отфильтрованное состояние порта. */
extern    union Prt  Pi4_cf ; /* ненормированое отфильтрованное состояние порта. */

extern word  P4_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P4. */
#endif

#ifdef _PORTE2_

extern    union Prt  Pi4_c ;  /*  необработанное состояние порта. */
extern    union Prt  Pi4_nm ;/* отнормированное состояние порта. */
extern _register union Prt  Pi4_f ;  /* отфильтрованное состояние порта. */
extern    union Prt  Pi4_cf ; /* ненормированое отфильтрованное состояние порта. */

extern word  P4_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P4. */

extern   union Prt  Pi5_c ;  /*  необработанное состояние порта. */
extern   union Prt  Pi5_nm ;/* отнормированное состояние порта. */
extern _register union Prt  Pi5_f ;  /* отфильтрованное состояние порта. */
extern   union Prt  Pi5_cf ; /* ненормированое отфильтрованное состояние порта. */

extern  word  P5_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P5. */
extern    union Prt  Pi6_c ;  /*  необработанное состояние порта. */
extern    union Prt  Pi6_nm ;/* отнормированное состояние порта. */
extern _register union Prt  Pi6_f ;  /* отфильтрованное состояние порта. */
extern    union Prt  Pi6_cf ; /* ненормированое отфильтрованное состояние порта. */

extern word  P6_t [ 8 ] ; /*  Матрица ячеек для счета времени при фильтрации */
                   /* сигналов порта P6. */

#endif
/*------------------------------------------------*/
#endif
#endif
