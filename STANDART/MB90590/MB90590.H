/*  FFMC-16 IO-MAP HEADER FILE      */
/*  ==========================      */
/* SOFTUNE WORKBENCH FORMAT         */
/* C-DEFINITIONS FOR IO-SYMBOLS     */
/* CREATED BY IO-WIZARD V2.0   */
/* DATE: 15/07/99 TIME: 11:30:20 */
/* *********************************************************** */
/*               FUJITSU MIKROELEKTRONIK GMBH                  */
/*               Am Siebenstein 6-10, 63303 Dreieich           */
/*               Tel.:++49/6103/690-0,Fax - 122                */
/*                                                             */
/* The following software is for demonstration purposes only.  */
/* It is not fully tested, nor validated in order to fullfill  */
/* its task under all circumstances. Therefore, this software  */
/* or any part of it must only be used in an evaluation        */
/* laboratory environment.                                     */
/* This software is subject to the rules of our standard       */
/* DISCLAIMER, that is delivered with our SW-tools (on the CD  */
/* "Micros Documentation & Software V3.0" see "\START.HTM" or  */
/* see our Internet Page -                                     */
/* http://www.fujitsu-ede.com/products/micro/disclaimer.html   */
/* *********************************************************** */
/* History:                                                      */
/* Date      Version     Author      Description                 */
/* 01.02.99 1.0     T.Kaprolat  created                          */
/*                                                               */
/* 18.02.99 1.2     H.Loesche                                    */
/*  - ICR now included (icr.h)                                   */
/*  - IO-Wizard 1.7 uses IO_EXTENDED now                         */
/*  - WTBR now included (wtbr.h)                                 */
/* 09.04.99 1.3     H.Loesche                                    */
/*  - '_' removed from "!I"-symbols, now done by IO-Wizard       */
/* 14.04.99 1.4     J.Rohn                                       */
/*      - generation of header and c file with IO-Wizard V 1.9   */
/* 22.04.99 1.5 V.Satanovskiy                                    */
/*  - Bitdefinitions for parallelports are changed to Pxx, Dxx   */
/* 06.05.99 1.6 H. Loesche                                       */
/*  - disclaimer added                                           */
/*  - unspecified registers removed                              */
/* 15.07.99 1.7 V.Satanovskiy */
/*  - PADRx 3 are renamed to PADRx_L 1, PADRx_H 1, PADRx_H 1 */


#ifndef   __MB90XXX_H
#  define __MB90XXX_H
/*
- Please define __IO_NEAR in LARGE and COMPACT memory model, if the default
  data bank (DTB) is 00. This will result in better performance in these
  models.
- Please define __IO_FAR in SMALL and MEDIUM memory model, if the default
  data bank (DTB) is other than 00. This might be the case in systems with
  external RAM, which are not using internal RAM as default data area.
- Please define neither __IO_NEAR nor __IO_FAR in all other cases. This
  will work with almost all configurations.
*/

#  ifdef  __IO_NEAR
#    ifdef  __IO_FAR
#      error __IO_NEAR and __IO_FAR must not be defined at the same time
#    else
#      define ___IOWIDTH __near
#    endif
#  else
#    ifdef __IO_FAR
#      define ___IOWIDTH __far
#    else                               /* specified by memory model */
#      define ___IOWIDTH
#    endif
#  endif
#  ifdef  __IO_DEFINE
#    define __IO_EXTERN
#    define __IO_EXTENDED volatile ___IOWIDTH
#  else
#    define __IO_EXTERN   extern      /* for data, which can have __io */
#    define __IO_EXTENDED extern volatile ___IOWIDTH
#  endif

typedef unsigned char		IO_BYTE;
typedef unsigned short		IO_WORD;
typedef unsigned long		IO_LWORD;
typedef const unsigned short	IO_WORD_READ;

/* REGISTER BIT STRUCTURES */

typedef union{   /*  PORT DATA */
    IO_BYTE	byte;
    struct{
    IO_BYTE P00 :1;
    IO_BYTE P01 :1;
    IO_BYTE P02 :1;
    IO_BYTE P03 :1;
    IO_BYTE P04 :1;
    IO_BYTE P05 :1;
    IO_BYTE P06 :1;
    IO_BYTE P07 :1;
  }bit;
 }PDR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P10 :1;
    IO_BYTE P11 :1;
    IO_BYTE P12 :1;
    IO_BYTE P13 :1;
    IO_BYTE P14 :1;
    IO_BYTE P15 :1;
    IO_BYTE P16 :1;
    IO_BYTE P17 :1;
  }bit;
 }PDR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P20 :1;
    IO_BYTE P21 :1;
    IO_BYTE P22 :1;
    IO_BYTE P23 :1;
    IO_BYTE P24 :1;
    IO_BYTE P25 :1;
    IO_BYTE P26 :1;
    IO_BYTE P27 :1;
  }bit;
 }PDR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P30 :1;
    IO_BYTE P31 :1;
    IO_BYTE P32 :1;
    IO_BYTE P33 :1;
    IO_BYTE P34 :1;
    IO_BYTE P35 :1;
    IO_BYTE P36 :1;
    IO_BYTE P37 :1;
  }bit;
 }PDR3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P40 :1;
    IO_BYTE P41 :1;
    IO_BYTE P42 :1;
    IO_BYTE P43 :1;
    IO_BYTE P44 :1;
    IO_BYTE P45 :1;
    IO_BYTE P46 :1;
    IO_BYTE P47 :1;
  }bit;
 }PDR4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P50 :1;
    IO_BYTE P51 :1;
    IO_BYTE P52 :1;
    IO_BYTE P53 :1;
    IO_BYTE P54 :1;
    IO_BYTE P55 :1;
    IO_BYTE P56 :1;
    IO_BYTE P57 :1;
  }bit;
 }PDR5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P60 :1;
    IO_BYTE P61 :1;
    IO_BYTE P62 :1;
    IO_BYTE P63 :1;
    IO_BYTE P64 :1;
    IO_BYTE P65 :1;
    IO_BYTE P66 :1;
    IO_BYTE P67 :1;
  }bit;
 }PDR6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P70 :1;
    IO_BYTE P71 :1;
    IO_BYTE P72 :1;
    IO_BYTE P73 :1;
    IO_BYTE P74 :1;
    IO_BYTE P75 :1;
    IO_BYTE P76 :1;
    IO_BYTE P77 :1;
  }bit;
 }PDR7STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P80 :1;
    IO_BYTE P81 :1;
    IO_BYTE P82 :1;
    IO_BYTE P83 :1;
    IO_BYTE P84 :1;
    IO_BYTE P85 :1;
    IO_BYTE P86 :1;
    IO_BYTE P87 :1;
  }bit;
 }PDR8STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE P90 :1;
    IO_BYTE P91 :1;
    IO_BYTE P92 :1;
    IO_BYTE P93 :1;
    IO_BYTE P94 :1;
    IO_BYTE P95 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PDR9STR;
typedef union{   /*  PORT DIRECTION */
    IO_BYTE	byte;
    struct{
    IO_BYTE D00 :1;
    IO_BYTE D01 :1;
    IO_BYTE D02 :1;
    IO_BYTE D03 :1;
    IO_BYTE D04 :1;
    IO_BYTE D05 :1;
    IO_BYTE D06 :1;
    IO_BYTE D07 :1;
  }bit;
 }DDR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D10 :1;
    IO_BYTE D11 :1;
    IO_BYTE D12 :1;
    IO_BYTE D13 :1;
    IO_BYTE D14 :1;
    IO_BYTE D15 :1;
    IO_BYTE D16 :1;
    IO_BYTE D17 :1;
  }bit;
 }DDR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D20 :1;
    IO_BYTE D21 :1;
    IO_BYTE D22 :1;
    IO_BYTE D23 :1;
    IO_BYTE D24 :1;
    IO_BYTE D25 :1;
    IO_BYTE D26 :1;
    IO_BYTE D27 :1;
  }bit;
 }DDR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D30 :1;
    IO_BYTE D31 :1;
    IO_BYTE D32 :1;
    IO_BYTE D33 :1;
    IO_BYTE D34 :1;
    IO_BYTE D35 :1;
    IO_BYTE D36 :1;
    IO_BYTE D37 :1;
  }bit;
 }DDR3STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D40 :1;
    IO_BYTE D41 :1;
    IO_BYTE D42 :1;
    IO_BYTE D43 :1;
    IO_BYTE D44 :1;
    IO_BYTE D45 :1;
    IO_BYTE D46 :1;
    IO_BYTE D47 :1;
  }bit;
 }DDR4STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D50 :1;
    IO_BYTE D51 :1;
    IO_BYTE D52 :1;
    IO_BYTE D53 :1;
    IO_BYTE D54 :1;
    IO_BYTE D55 :1;
    IO_BYTE D56 :1;
    IO_BYTE D57 :1;
  }bit;
 }DDR5STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D60 :1;
    IO_BYTE D61 :1;
    IO_BYTE D62 :1;
    IO_BYTE D63 :1;
    IO_BYTE D64 :1;
    IO_BYTE D65 :1;
    IO_BYTE D66 :1;
    IO_BYTE D67 :1;
  }bit;
 }DDR6STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D70 :1;
    IO_BYTE D71 :1;
    IO_BYTE D72 :1;
    IO_BYTE D73 :1;
    IO_BYTE D74 :1;
    IO_BYTE D75 :1;
    IO_BYTE D76 :1;
    IO_BYTE D77 :1;
  }bit;
 }DDR7STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D80 :1;
    IO_BYTE D81 :1;
    IO_BYTE D82 :1;
    IO_BYTE D83 :1;
    IO_BYTE D84 :1;
    IO_BYTE D85 :1;
    IO_BYTE D86 :1;
    IO_BYTE D87 :1;
  }bit;
 }DDR8STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D90 :1;
    IO_BYTE D91 :1;
    IO_BYTE D92 :1;
    IO_BYTE D93 :1;
    IO_BYTE D94 :1;
    IO_BYTE D95 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }DDR9STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ADE0 :1;
    IO_BYTE ADE1 :1;
    IO_BYTE ADE2 :1;
    IO_BYTE ADE3 :1;
    IO_BYTE ADE4 :1;
    IO_BYTE ADE5 :1;
    IO_BYTE ADE6 :1;
    IO_BYTE ADE7 :1;
  }bit;
 }ADERSTR;
typedef union{   /*  UART0 */
    IO_BYTE	byte;
    struct{
    IO_BYTE SOE :1;
    IO_BYTE SCKE :1;
    IO_BYTE RFC :1;
    IO_BYTE SMDE :1;
    IO_BYTE MC0 :1;
    IO_BYTE MC1 :1;
    IO_BYTE SBL :1;
    IO_BYTE PEN :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE MC :2;
  }bitc;
 }UMC0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE TBF :1;
    IO_BYTE RBF :1;
    IO_BYTE TIE :1;
    IO_BYTE RIE :1;
    IO_BYTE TDRE :1;
    IO_BYTE PE :1;
    IO_BYTE ORFE :1;
    IO_BYTE RDRF :1;
  }bit;
 }USR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }UIDR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }UODR0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D8 :1;
    IO_BYTE P :1;
    IO_BYTE BCH0 :1;
    IO_BYTE RC0 :1;
    IO_BYTE RC1 :1;
    IO_BYTE RC2 :1;
    IO_BYTE RC3 :1;
    IO_BYTE BCH :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE RC :4;
  }bitc;
 }URD0STR;
typedef union{   /*  UART1 */
    IO_BYTE	byte;
    struct{
    IO_BYTE SOE :1;
    IO_BYTE SCKE :1;
    IO_BYTE RFC :1;
    IO_BYTE SMDE :1;
    IO_BYTE MC0 :1;
    IO_BYTE MC1 :1;
    IO_BYTE SBL :1;
    IO_BYTE PEN :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE MC :2;
  }bitc;
 }UMC1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE TBF :1;
    IO_BYTE RBF :1;
    IO_BYTE TIE :1;
    IO_BYTE RIE :1;
    IO_BYTE TDRE :1;
    IO_BYTE PE :1;
    IO_BYTE ORFE :1;
    IO_BYTE RDRF :1;
  }bit;
 }USR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }UIDR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }UODR1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D8 :1;
    IO_BYTE P :1;
    IO_BYTE BCH0 :1;
    IO_BYTE RC0 :1;
    IO_BYTE RC1 :1;
    IO_BYTE RC2 :1;
    IO_BYTE RC3 :1;
    IO_BYTE BCH :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE RC :4;
  }bitc;
 }URD1STR;
typedef union{   /*  UART2 */
    IO_BYTE	byte;
    struct{
    IO_BYTE SOE :1;
    IO_BYTE SCKE :1;
    IO_BYTE RFC :1;
    IO_BYTE SMDE :1;
    IO_BYTE MC0 :1;
    IO_BYTE MC1 :1;
    IO_BYTE SBL :1;
    IO_BYTE PEN :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE MC :2;
  }bitc;
 }UMC2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE TBF :1;
    IO_BYTE RBF :1;
    IO_BYTE TIE :1;
    IO_BYTE RIE :1;
    IO_BYTE TDRE :1;
    IO_BYTE PE :1;
    IO_BYTE ORFE :1;
    IO_BYTE RDRF :1;
  }bit;
 }USR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }UIDR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }UODR2STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D8 :1;
    IO_BYTE P :1;
    IO_BYTE BCH0 :1;
    IO_BYTE RC0 :1;
    IO_BYTE RC1 :1;
    IO_BYTE RC2 :1;
    IO_BYTE RC3 :1;
    IO_BYTE BCH :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE RC :4;
  }bitc;
 }URD2STR;
typedef union{   /*  SIO with clock selection */
    IO_WORD	word;
    struct{
    IO_WORD SCOE :1;
    IO_WORD SOE :1;
    IO_WORD BDS :1;
    IO_WORD MODE :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD STRT :1;
    IO_WORD STOP :1;
    IO_WORD BUSY :1;
    IO_WORD SIR :1;
    IO_WORD SIE :1;
    IO_WORD SMD0 :1;
    IO_WORD SMD1 :1;
    IO_WORD SMD2 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD SMD :3;
  }bitc;
 }SMCSSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE NEG :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }SESSTR;
typedef union{   /*  DTP, External Interrupts */
    IO_BYTE	byte;
    struct{
    IO_BYTE EN0 :1;
    IO_BYTE EN1 :1;
    IO_BYTE EN2 :1;
    IO_BYTE EN3 :1;
    IO_BYTE EN4 :1;
    IO_BYTE EN5 :1;
    IO_BYTE EN6 :1;
    IO_BYTE EN7 :1;
  }bit;
 }ENIRSTR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE ER0 :1;
    IO_BYTE ER1 :1;
    IO_BYTE ER2 :1;
    IO_BYTE ER3 :1;
    IO_BYTE ER4 :1;
    IO_BYTE ER5 :1;
    IO_BYTE ER6 :1;
    IO_BYTE ER7 :1;
  }bit;
 }EIRRSTR;
typedef union{   /*  AD Converter  */
    IO_BYTE	byte;
    struct{
    IO_BYTE ANE0 :1;
    IO_BYTE ANE1 :1;
    IO_BYTE ANE2 :1;
    IO_BYTE ANS0 :1;
    IO_BYTE ANS1 :1;
    IO_BYTE ANS2 :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
  }bit;
  struct{
    IO_BYTE ANE :3;
    IO_BYTE ANS :3;
    IO_BYTE MD :2;
  }bitc;
 }ADCS0STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE DA :1;
    IO_BYTE STRT :1;
    IO_BYTE STS0 :1;
    IO_BYTE STS1 :1;
    IO_BYTE PAUS :1;
    IO_BYTE INTE :1;
    IO_BYTE INT :1;
    IO_BYTE BUSY :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE STS :2;
  }bitc;
 }ADCS1STR;
typedef union{
    IO_BYTE	byte;
    struct{
    IO_BYTE D0 :1;
    IO_BYTE D1 :1;
    IO_BYTE D2 :1;
    IO_BYTE D3 :1;
    IO_BYTE D4 :1;
    IO_BYTE D5 :1;
    IO_BYTE D6 :1;
    IO_BYTE D7 :1;
  }bit;
 }ADCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE D8 :1;
    IO_BYTE D9 :1;
    IO_BYTE  :1;
    IO_BYTE CT0 :1;
    IO_BYTE CT1 :1;
    IO_BYTE ST0 :1;
    IO_BYTE ST1 :1;
    IO_BYTE S10 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE CT :2;
    IO_BYTE ST :2;
  }bitc;
 }ADCR1STR;
typedef union{  
    IO_WORD	word;
    struct{
    IO_WORD D0 :1;
    IO_WORD D1 :1;
    IO_WORD D2 :1;
    IO_WORD D3 :1;
    IO_WORD D4 :1;
    IO_WORD D5 :1;
    IO_WORD D6 :1;
    IO_WORD D7 :1;
    IO_WORD D8 :1;
    IO_WORD D9 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }ADCRSTR;
typedef union{   /*  PPG control */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PUF0 :1;
    IO_BYTE PIE0 :1;
    IO_BYTE PE00 :1;
    IO_BYTE  :1;
    IO_BYTE PEN0 :1;
  }bit;
 }PPGC0STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
    IO_BYTE PUF1 :1;
    IO_BYTE PIE1 :1;
    IO_BYTE PE10 :1;
    IO_BYTE  :1;
    IO_BYTE PEN1 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE MD :2;
  }bitc;
 }PPGC1STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PCM0 :1;
    IO_BYTE PCM1 :1;
    IO_BYTE PCM2 :1;
    IO_BYTE PCS0 :1;
    IO_BYTE PCS1 :1;
    IO_BYTE PCS2 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE PCM :3;
    IO_BYTE PCS :3;
  }bitc;
 }PPG01STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PUF2 :1;
    IO_BYTE PIE2 :1;
    IO_BYTE PE20 :1;
    IO_BYTE  :1;
    IO_BYTE PEN2 :1;
  }bit;
 }PPGC2STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
    IO_BYTE PUF3 :1;
    IO_BYTE PIE3 :1;
    IO_BYTE PE30 :1;
    IO_BYTE  :1;
    IO_BYTE PEN3 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE MD :2;
  }bitc;
 }PPGC3STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PCM0 :1;
    IO_BYTE PCM1 :1;
    IO_BYTE PCM2 :1;
    IO_BYTE PCS0 :1;
    IO_BYTE PCS1 :1;
    IO_BYTE PCS2 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE PCM :3;
    IO_BYTE PCS :3;
  }bitc;
 }PPG23STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PUF4 :1;
    IO_BYTE PIE4 :1;
    IO_BYTE PE40 :1;
    IO_BYTE  :1;
    IO_BYTE PEN4 :1;
  }bit;
 }PPGC4STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
    IO_BYTE PUF5 :1;
    IO_BYTE PIE5 :1;
    IO_BYTE PE50 :1;
    IO_BYTE  :1;
    IO_BYTE PEN5 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE MD :2;
  }bitc;
 }PPGC5STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PCM0 :1;
    IO_BYTE PCM1 :1;
    IO_BYTE PCM2 :1;
    IO_BYTE PCS0 :1;
    IO_BYTE PCS1 :1;
    IO_BYTE PCS2 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE PCM :3;
    IO_BYTE PCS :3;
  }bitc;
 }PPG45STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PUF6 :1;
    IO_BYTE PIE6 :1;
    IO_BYTE PE60 :1;
    IO_BYTE  :1;
    IO_BYTE PEN6 :1;
  }bit;
 }PPGC6STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
    IO_BYTE PUF7 :1;
    IO_BYTE PIE7 :1;
    IO_BYTE PE70 :1;
    IO_BYTE  :1;
    IO_BYTE PEN7 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE MD :2;
  }bitc;
 }PPGC7STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PCM0 :1;
    IO_BYTE PCM1 :1;
    IO_BYTE PCM2 :1;
    IO_BYTE PCS0 :1;
    IO_BYTE PCS1 :1;
    IO_BYTE PCS2 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE PCM :3;
    IO_BYTE PCS :3;
  }bitc;
 }PPG67STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PUF8 :1;
    IO_BYTE PIE8 :1;
    IO_BYTE PE80 :1;
    IO_BYTE  :1;
    IO_BYTE PEN8 :1;
  }bit;
 }PPGC8STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
    IO_BYTE PUF9 :1;
    IO_BYTE PIE9 :1;
    IO_BYTE PE90 :1;
    IO_BYTE  :1;
    IO_BYTE PEN9 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE MD :2;
  }bitc;
 }PPGC9STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PCM0 :1;
    IO_BYTE PCM1 :1;
    IO_BYTE PCM2 :1;
    IO_BYTE PCS0 :1;
    IO_BYTE PCS1 :1;
    IO_BYTE PCS2 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE PCM :3;
    IO_BYTE PCS :3;
  }bitc;
 }PPG89STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PUFA :1;
    IO_BYTE PIEA :1;
    IO_BYTE PEA0 :1;
    IO_BYTE  :1;
    IO_BYTE PENA :1;
  }bit;
 }PPGCASTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE MD0 :1;
    IO_BYTE MD1 :1;
    IO_BYTE PUFB :1;
    IO_BYTE PIEB :1;
    IO_BYTE PEB0 :1;
    IO_BYTE  :1;
    IO_BYTE PENB :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE MD :2;
  }bitc;
 }PPGCBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE PCM0 :1;
    IO_BYTE PCM1 :1;
    IO_BYTE PCM2 :1;
    IO_BYTE PCS0 :1;
    IO_BYTE PCS1 :1;
    IO_BYTE PCS2 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE PCM :3;
    IO_BYTE PCS :3;
  }bitc;
 }PPGABSTR;
typedef union{   /*  Reload Timer */
    IO_WORD	word;
    struct{
    IO_WORD TRG :1;
    IO_WORD CNTE :1;
    IO_WORD UF :1;
    IO_WORD INTE :1;
    IO_WORD RELD :1;
    IO_WORD OUTL :1;
    IO_WORD OUTE :1;
    IO_WORD MOD0 :1;
    IO_WORD MOD1 :1;
    IO_WORD MOD2 :1;
    IO_WORD CSL0 :1;
    IO_WORD CSL1 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD MOD :3;
    IO_WORD CSL :2;
  }bitc;
 }TMCSR0STR;
typedef union{  
    IO_WORD	word;
    struct{
    IO_WORD TRG :1;
    IO_WORD CNTE :1;
    IO_WORD UF :1;
    IO_WORD INTE :1;
    IO_WORD RELD :1;
    IO_WORD OUTL :1;
    IO_WORD OUTE :1;
    IO_WORD MOD0 :1;
    IO_WORD MOD1 :1;
    IO_WORD MOD2 :1;
    IO_WORD CSL0 :1;
    IO_WORD CSL1 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD MOD :3;
    IO_WORD CSL :2;
  }bitc;
 }TMCSR1STR;
typedef union{   /*  Input Capture */
    IO_BYTE	byte;
    struct{
    IO_BYTE EG00 :1;
    IO_BYTE EG01 :1;
    IO_BYTE EG10 :1;
    IO_BYTE EG11 :1;
    IO_BYTE ICE0 :1;
    IO_BYTE ICE1 :1;
    IO_BYTE ICP0 :1;
    IO_BYTE ICP1 :1;
  }bit;
  struct{
    IO_BYTE EG0 :2;
    IO_BYTE EG1 :2;
  }bitc;
 }ICS01STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE EG20 :1;
    IO_BYTE EG21 :1;
    IO_BYTE EG30 :1;
    IO_BYTE EG31 :1;
    IO_BYTE ICE2 :1;
    IO_BYTE ICE3 :1;
    IO_BYTE ICP2 :1;
    IO_BYTE ICP3 :1;
  }bit;
  struct{
    IO_BYTE EG2 :2;
    IO_BYTE EG3 :2;
  }bitc;
 }ICS23STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE EG40 :1;
    IO_BYTE EG41 :1;
    IO_BYTE EG50 :1;
    IO_BYTE EG51 :1;
    IO_BYTE ICE4 :1;
    IO_BYTE ICE5 :1;
    IO_BYTE ICP4 :1;
    IO_BYTE ICP5 :1;
  }bit;
  struct{
    IO_BYTE EG4 :2;
    IO_BYTE EG5 :2;
  }bitc;
 }ICS45STR;
typedef union{   /*  Output compare */
    IO_WORD	word;
    struct{
    IO_WORD CST0 :1;
    IO_WORD CST1 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD ICE0 :1;
    IO_WORD ICE1 :1;
    IO_WORD ICP0 :1;
    IO_WORD ICP1 :1;
    IO_WORD OTD0 :1;
    IO_WORD OTD1 :1;
    IO_WORD OTE0 :1;
    IO_WORD OTE1 :1;
    IO_WORD CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD CST :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD ICE :2;
    IO_WORD ICP :2;
    IO_WORD OTD :2;
    IO_WORD OTE :2;
  }bitc;
 }OCS01STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE CST0 :1;
    IO_BYTE CST1 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE ICE0 :1;
    IO_BYTE ICE1 :1;
    IO_BYTE ICP0 :1;
    IO_BYTE ICP1 :1;
  }bit;
  struct{
    IO_BYTE CST :2;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE ICE :2;
    IO_BYTE ICP :2;
  }bitc;
 }OCS0STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE OTD0 :1;
    IO_BYTE OTD1 :1;
    IO_BYTE OTE0 :1;
    IO_BYTE OTE1 :1;
    IO_BYTE CMOD :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE OTD :2;
    IO_BYTE OTE :2;
  }bitc;
 }OCS1STR;
typedef union{  
    IO_WORD	word;
    struct{
    IO_WORD CST2 :1;
    IO_WORD CST3 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD ICE2 :1;
    IO_WORD ICE3 :1;
    IO_WORD ICP2 :1;
    IO_WORD ICP3 :1;
    IO_WORD OTD2 :1;
    IO_WORD OTD3 :1;
    IO_WORD OTE2 :1;
    IO_WORD OTE3 :1;
    IO_WORD CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD CST :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD ICE :2;
    IO_WORD ICP :2;
    IO_WORD OTD :2;
    IO_WORD OTE :2;
  }bitc;
 }OCS23STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE CST2 :1;
    IO_BYTE CST3 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE ICE2 :1;
    IO_BYTE ICE3 :1;
    IO_BYTE ICP2 :1;
    IO_BYTE ICP3 :1;
  }bit;
  struct{
    IO_BYTE CST :2;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE ICE :2;
    IO_BYTE ICP :2;
  }bitc;
 }OCS2STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE OTD2 :1;
    IO_BYTE OTD3 :1;
    IO_BYTE OTE2 :1;
    IO_BYTE OTE3 :1;
    IO_BYTE CMOD :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE OTD :2;
    IO_BYTE OTE :2;
  }bitc;
 }OCS3STR;
typedef union{  
    IO_WORD	word;
    struct{
    IO_WORD CST4 :1;
    IO_WORD CST5 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD ICE4 :1;
    IO_WORD ICE5 :1;
    IO_WORD ICP4 :1;
    IO_WORD ICP5 :1;
    IO_WORD OTD4 :1;
    IO_WORD OTD5 :1;
    IO_WORD OTE4 :1;
    IO_WORD OTE5 :1;
    IO_WORD CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD CST :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD ICE :2;
    IO_WORD ICP :2;
    IO_WORD OTD :2;
    IO_WORD OTE :2;
  }bitc;
 }OCS45STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE CST4 :1;
    IO_BYTE CST5 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE ICE4 :1;
    IO_BYTE ICE5 :1;
    IO_BYTE ICP4 :1;
    IO_BYTE ICP5 :1;
  }bit;
  struct{
    IO_BYTE CST :2;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE ICE :2;
    IO_BYTE ICP :2;
  }bitc;
 }OCS4STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE OTD4 :1;
    IO_BYTE OTD5 :1;
    IO_BYTE OTE4 :1;
    IO_BYTE OTE5 :1;
    IO_BYTE CMOD :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE OTD :2;
    IO_BYTE OTE :2;
  }bitc;
 }OCS5STR;
typedef union{   /* Sound control */
    IO_WORD	word;
    struct{
    IO_WORD ST :1;
    IO_WORD INT :1;
    IO_WORD INTE :1;
    IO_WORD OE1 :1;
    IO_WORD OE2 :1;
    IO_WORD TONE :1;
    IO_WORD S0 :1;
    IO_WORD S1 :1;
    IO_WORD DEC :1;
    IO_WORD BUSY :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD TST :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD S :2;
  }bitc;
 }SGCRSTR;
typedef union{   /*  Watch Timer */
    IO_WORD	word;
    struct{
    IO_WORD INT0 :1;
    IO_WORD INTE0 :1;
    IO_WORD INT1 :1;
    IO_WORD INTE1 :1;
    IO_WORD INT2 :1;
    IO_WORD INTE2 :1;
    IO_WORD INT3 :1;
    IO_WORD INTE3 :1;
    IO_WORD ST :1;
    IO_WORD OE :1;
    IO_WORD UPDT :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD TST0 :1;
    IO_WORD TST1 :1;
    IO_WORD TST2 :1;
  }bit;
 }WTCRSTR;
typedef union{   /* PWM0 */
    IO_BYTE	byte;
    struct{
    IO_BYTE TST :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CE :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE OE1 :1;
    IO_BYTE OE2 :1;
  }bit;
 }PWC0STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE TST :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CE :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE OE1 :1;
    IO_BYTE OE2 :1;
  }bit;
 }PWC1STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE TST :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CE :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE OE1 :1;
    IO_BYTE OE2 :1;
  }bit;
 }PWC2STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE TST :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE CE :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE OE1 :1;
    IO_BYTE OE2 :1;
  }bit;
 }PWC3STR;
typedef union{   /* Serial IO Prescaler */
    IO_BYTE	byte;
    struct{
    IO_BYTE DIV0 :1;
    IO_BYTE DIV1 :1;
    IO_BYTE DIV2 :1;
    IO_BYTE DIV3 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE DIV :4;
  }bitc;
 }CDCRSTR;
typedef union{   /* IO timer */
    IO_BYTE	byte;
    struct{
    IO_BYTE CLK0 :1;
    IO_BYTE CLK1 :1;
    IO_BYTE CLR :1;
    IO_BYTE MODE :1;
    IO_BYTE STOP :1;
    IO_BYTE IVFE :1;
    IO_BYTE IVF :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE CLK :2;
  }bitc;
 }TCCSSTR;
typedef union{   /*  ROM Mirror */
    IO_BYTE	byte;
    struct{
    IO_BYTE MI :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }ROMMSTR;
typedef union{   /*  ROM Correction */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE AD0E :1;
    IO_BYTE  :1;
    IO_BYTE AD1E :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PACSRSTR;
typedef union{   /*  Delay interrupt enable */
    IO_BYTE	byte;
    struct{
    IO_BYTE R0 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }DIRRSTR;
typedef union{   /*  Low power mode control */
    IO_BYTE	byte;
    struct{
    IO_BYTE  :1;
    IO_BYTE CG0 :1;
    IO_BYTE CG1 :1;
    IO_BYTE  :1;
    IO_BYTE RST :1;
    IO_BYTE SPL :1;
    IO_BYTE SLP :1;
    IO_BYTE STP :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE CG :2;
  }bitc;
 }LPMCRSTR;
typedef union{   /*  Clock selection */
    IO_BYTE	byte;
    struct{
    IO_BYTE CS0 :1;
    IO_BYTE CS1 :1;
    IO_BYTE MCS :1;
    IO_BYTE  :1;
    IO_BYTE WS0 :1;
    IO_BYTE WS1 :1;
    IO_BYTE MCM :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE CS :2;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE WS :2;
  }bitc;
 }CKSCRSTR;
typedef union{   /* Watchdog Control */
    IO_WORD	word;
    struct{
    IO_WORD WT0 :1;
    IO_WORD WT1 :1;
    IO_WORD WTE :1;
    IO_WORD SRST :1;
    IO_WORD ERST :1;
    IO_WORD WRST :1;
    IO_WORD STBR :1;
    IO_WORD PONR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD WT :2;
  }bitc;
 }WDTCSTR;
typedef union{   /*  Time Base timer */
    IO_BYTE	byte;
    struct{
    IO_BYTE TBC0 :1;
    IO_BYTE TBC1 :1;
    IO_BYTE TBR :1;
    IO_BYTE TBOF :1;
    IO_BYTE TBIE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE TBC :2;
  }bitc;
 }TBTCSTR;
typedef union{   /* Flash Control Register */
    IO_BYTE	byte;
    struct{
    IO_BYTE LPM0 :1;
    IO_BYTE  :1;
    IO_BYTE LPM1 :1;
    IO_BYTE  :1;
    IO_BYTE RDY :1;
    IO_BYTE WE :1;
    IO_BYTE RDYINT :1;
    IO_BYTE INTE :1;
  }bit;
 }FMCSSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE S0 :1;
    IO_BYTE S1 :1;
    IO_BYTE S2 :1;
    IO_BYTE S3 :1;
    IO_BYTE S4 :1;
    IO_BYTE S5 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }WTSRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE M3 :1;
    IO_BYTE M4 :1;
    IO_BYTE M5 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }WTMRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE H0 :1;
    IO_BYTE H1 :1;
    IO_BYTE H2 :1;
    IO_BYTE H3 :1;
    IO_BYTE H4 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }WTHRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS10STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE BS :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS20STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS11STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE BS :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS21STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS12STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE BS :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS22STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS13STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    IO_BYTE M0 :1;
    IO_BYTE M1 :1;
    IO_BYTE M2 :1;
    IO_BYTE P0 :1;
    IO_BYTE P1 :1;
    IO_BYTE P2 :1;
    IO_BYTE BS :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE M :3;
    IO_BYTE P :3;
  }bitc;
 }PWS23STR;

/* C-DECLARATIONS */

__IO_EXTERN __io PDR0STR _pdr0;   /*  PORT DATA */
#define PDR0 _pdr0.byte
#define PDR0_P00 _pdr0.bit.P00
#define PDR0_P01 _pdr0.bit.P01
#define PDR0_P02 _pdr0.bit.P02
#define PDR0_P03 _pdr0.bit.P03
#define PDR0_P04 _pdr0.bit.P04
#define PDR0_P05 _pdr0.bit.P05
#define PDR0_P06 _pdr0.bit.P06
#define PDR0_P07 _pdr0.bit.P07
__IO_EXTERN __io PDR1STR _pdr1;  
#define PDR1 _pdr1.byte
#define PDR1_P10 _pdr1.bit.P10
#define PDR1_P11 _pdr1.bit.P11
#define PDR1_P12 _pdr1.bit.P12
#define PDR1_P13 _pdr1.bit.P13
#define PDR1_P14 _pdr1.bit.P14
#define PDR1_P15 _pdr1.bit.P15
#define PDR1_P16 _pdr1.bit.P16
#define PDR1_P17 _pdr1.bit.P17
__IO_EXTERN __io PDR2STR _pdr2;  
#define PDR2 _pdr2.byte
#define PDR2_P20 _pdr2.bit.P20
#define PDR2_P21 _pdr2.bit.P21
#define PDR2_P22 _pdr2.bit.P22
#define PDR2_P23 _pdr2.bit.P23
#define PDR2_P24 _pdr2.bit.P24
#define PDR2_P25 _pdr2.bit.P25
#define PDR2_P26 _pdr2.bit.P26
#define PDR2_P27 _pdr2.bit.P27
__IO_EXTERN __io PDR3STR _pdr3;  
#define PDR3 _pdr3.byte
#define PDR3_P30 _pdr3.bit.P30
#define PDR3_P31 _pdr3.bit.P31
#define PDR3_P32 _pdr3.bit.P32
#define PDR3_P33 _pdr3.bit.P33
#define PDR3_P34 _pdr3.bit.P34
#define PDR3_P35 _pdr3.bit.P35
#define PDR3_P36 _pdr3.bit.P36
#define PDR3_P37 _pdr3.bit.P37
__IO_EXTERN __io PDR4STR _pdr4;  
#define PDR4 _pdr4.byte
#define PDR4_P40 _pdr4.bit.P40
#define PDR4_P41 _pdr4.bit.P41
#define PDR4_P42 _pdr4.bit.P42
#define PDR4_P43 _pdr4.bit.P43
#define PDR4_P44 _pdr4.bit.P44
#define PDR4_P45 _pdr4.bit.P45
#define PDR4_P46 _pdr4.bit.P46
#define PDR4_P47 _pdr4.bit.P47
__IO_EXTERN __io PDR5STR _pdr5;  
#define PDR5 _pdr5.byte
#define PDR5_P50 _pdr5.bit.P50
#define PDR5_P51 _pdr5.bit.P51
#define PDR5_P52 _pdr5.bit.P52
#define PDR5_P53 _pdr5.bit.P53
#define PDR5_P54 _pdr5.bit.P54
#define PDR5_P55 _pdr5.bit.P55
#define PDR5_P56 _pdr5.bit.P56
#define PDR5_P57 _pdr5.bit.P57
__IO_EXTERN __io PDR6STR _pdr6;  
#define PDR6 _pdr6.byte
#define PDR6_P60 _pdr6.bit.P60
#define PDR6_P61 _pdr6.bit.P61
#define PDR6_P62 _pdr6.bit.P62
#define PDR6_P63 _pdr6.bit.P63
#define PDR6_P64 _pdr6.bit.P64
#define PDR6_P65 _pdr6.bit.P65
#define PDR6_P66 _pdr6.bit.P66
#define PDR6_P67 _pdr6.bit.P67
__IO_EXTERN __io PDR7STR _pdr7;  
#define PDR7 _pdr7.byte
#define PDR7_P70 _pdr7.bit.P70
#define PDR7_P71 _pdr7.bit.P71
#define PDR7_P72 _pdr7.bit.P72
#define PDR7_P73 _pdr7.bit.P73
#define PDR7_P74 _pdr7.bit.P74
#define PDR7_P75 _pdr7.bit.P75
#define PDR7_P76 _pdr7.bit.P76
#define PDR7_P77 _pdr7.bit.P77
__IO_EXTERN __io PDR8STR _pdr8;  
#define PDR8 _pdr8.byte
#define PDR8_P80 _pdr8.bit.P80
#define PDR8_P81 _pdr8.bit.P81
#define PDR8_P82 _pdr8.bit.P82
#define PDR8_P83 _pdr8.bit.P83
#define PDR8_P84 _pdr8.bit.P84
#define PDR8_P85 _pdr8.bit.P85
#define PDR8_P86 _pdr8.bit.P86
#define PDR8_P87 _pdr8.bit.P87
__IO_EXTERN __io PDR9STR _pdr9;  
#define PDR9 _pdr9.byte
#define PDR9_P90 _pdr9.bit.P90
#define PDR9_P91 _pdr9.bit.P91
#define PDR9_P92 _pdr9.bit.P92
#define PDR9_P93 _pdr9.bit.P93
#define PDR9_P94 _pdr9.bit.P94
#define PDR9_P95 _pdr9.bit.P95
__IO_EXTERN __io DDR0STR _ddr0;   /*  PORT DIRECTION */
#define DDR0 _ddr0.byte
#define DDR0_D00 _ddr0.bit.D00
#define DDR0_D01 _ddr0.bit.D01
#define DDR0_D02 _ddr0.bit.D02
#define DDR0_D03 _ddr0.bit.D03
#define DDR0_D04 _ddr0.bit.D04
#define DDR0_D05 _ddr0.bit.D05
#define DDR0_D06 _ddr0.bit.D06
#define DDR0_D07 _ddr0.bit.D07
__IO_EXTERN __io DDR1STR _ddr1;  
#define DDR1 _ddr1.byte
#define DDR1_D10 _ddr1.bit.D10
#define DDR1_D11 _ddr1.bit.D11
#define DDR1_D12 _ddr1.bit.D12
#define DDR1_D13 _ddr1.bit.D13
#define DDR1_D14 _ddr1.bit.D14
#define DDR1_D15 _ddr1.bit.D15
#define DDR1_D16 _ddr1.bit.D16
#define DDR1_D17 _ddr1.bit.D17
__IO_EXTERN __io DDR2STR _ddr2;  
#define DDR2 _ddr2.byte
#define DDR2_D20 _ddr2.bit.D20
#define DDR2_D21 _ddr2.bit.D21
#define DDR2_D22 _ddr2.bit.D22
#define DDR2_D23 _ddr2.bit.D23
#define DDR2_D24 _ddr2.bit.D24
#define DDR2_D25 _ddr2.bit.D25
#define DDR2_D26 _ddr2.bit.D26
#define DDR2_D27 _ddr2.bit.D27
__IO_EXTERN __io DDR3STR _ddr3;  
#define DDR3 _ddr3.byte
#define DDR3_D30 _ddr3.bit.D30
#define DDR3_D31 _ddr3.bit.D31
#define DDR3_D32 _ddr3.bit.D32
#define DDR3_D33 _ddr3.bit.D33
#define DDR3_D34 _ddr3.bit.D34
#define DDR3_D35 _ddr3.bit.D35
#define DDR3_D36 _ddr3.bit.D36
#define DDR3_D37 _ddr3.bit.D37
__IO_EXTERN __io DDR4STR _ddr4;  
#define DDR4 _ddr4.byte
#define DDR4_D40 _ddr4.bit.D40
#define DDR4_D41 _ddr4.bit.D41
#define DDR4_D42 _ddr4.bit.D42
#define DDR4_D43 _ddr4.bit.D43
#define DDR4_D44 _ddr4.bit.D44
#define DDR4_D45 _ddr4.bit.D45
#define DDR4_D46 _ddr4.bit.D46
#define DDR4_D47 _ddr4.bit.D47
__IO_EXTERN __io DDR5STR _ddr5;  
#define DDR5 _ddr5.byte
#define DDR5_D50 _ddr5.bit.D50
#define DDR5_D51 _ddr5.bit.D51
#define DDR5_D52 _ddr5.bit.D52
#define DDR5_D53 _ddr5.bit.D53
#define DDR5_D54 _ddr5.bit.D54
#define DDR5_D55 _ddr5.bit.D55
#define DDR5_D56 _ddr5.bit.D56
#define DDR5_D57 _ddr5.bit.D57
__IO_EXTERN __io DDR6STR _ddr6;  
#define DDR6 _ddr6.byte
#define DDR6_D60 _ddr6.bit.D60
#define DDR6_D61 _ddr6.bit.D61
#define DDR6_D62 _ddr6.bit.D62
#define DDR6_D63 _ddr6.bit.D63
#define DDR6_D64 _ddr6.bit.D64
#define DDR6_D65 _ddr6.bit.D65
#define DDR6_D66 _ddr6.bit.D66
#define DDR6_D67 _ddr6.bit.D67
__IO_EXTERN __io DDR7STR _ddr7;  
#define DDR7 _ddr7.byte
#define DDR7_D70 _ddr7.bit.D70
#define DDR7_D71 _ddr7.bit.D71
#define DDR7_D72 _ddr7.bit.D72
#define DDR7_D73 _ddr7.bit.D73
#define DDR7_D74 _ddr7.bit.D74
#define DDR7_D75 _ddr7.bit.D75
#define DDR7_D76 _ddr7.bit.D76
#define DDR7_D77 _ddr7.bit.D77
__IO_EXTERN __io DDR8STR _ddr8;  
#define DDR8 _ddr8.byte
#define DDR8_D80 _ddr8.bit.D80
#define DDR8_D81 _ddr8.bit.D81
#define DDR8_D82 _ddr8.bit.D82
#define DDR8_D83 _ddr8.bit.D83
#define DDR8_D84 _ddr8.bit.D84
#define DDR8_D85 _ddr8.bit.D85
#define DDR8_D86 _ddr8.bit.D86
#define DDR8_D87 _ddr8.bit.D87
__IO_EXTERN __io DDR9STR _ddr9;  
#define DDR9 _ddr9.byte
#define DDR9_D90 _ddr9.bit.D90
#define DDR9_D91 _ddr9.bit.D91
#define DDR9_D92 _ddr9.bit.D92
#define DDR9_D93 _ddr9.bit.D93
#define DDR9_D94 _ddr9.bit.D94
#define DDR9_D95 _ddr9.bit.D95
__IO_EXTERN __io IO_BYTE _res_1;
#define res_1 _res_1   
__IO_EXTERN __io ADERSTR _ader;  
#define ADER _ader.byte
#define ADER_ADE0 _ader.bit.ADE0
#define ADER_ADE1 _ader.bit.ADE1
#define ADER_ADE2 _ader.bit.ADE2
#define ADER_ADE3 _ader.bit.ADE3
#define ADER_ADE4 _ader.bit.ADE4
#define ADER_ADE5 _ader.bit.ADE5
#define ADER_ADE6 _ader.bit.ADE6
#define ADER_ADE7 _ader.bit.ADE7
__IO_EXTERN __io UMC0STR _umc0;   /*  UART0 */
#define UMC0 _umc0.byte
#define UMC0_SOE _umc0.bit.SOE
#define UMC0_SCKE _umc0.bit.SCKE
#define UMC0_RFC _umc0.bit.RFC
#define UMC0_SMDE _umc0.bit.SMDE
#define UMC0_MC0 _umc0.bit.MC0
#define UMC0_MC1 _umc0.bit.MC1
#define UMC0_SBL _umc0.bit.SBL
#define UMC0_PEN _umc0.bit.PEN
#define UMC0_MC _umc0.bitc.MC
__IO_EXTERN __io USR0STR _usr0;  
#define USR0 _usr0.byte
#define USR0_TBF _usr0.bit.TBF
#define USR0_RBF _usr0.bit.RBF
#define USR0_TIE _usr0.bit.TIE
#define USR0_RIE _usr0.bit.RIE
#define USR0_TDRE _usr0.bit.TDRE
#define USR0_PE _usr0.bit.PE
#define USR0_ORFE _usr0.bit.ORFE
#define USR0_RDRF _usr0.bit.RDRF
__IO_EXTERN __io UIDR0STR _uidr0;  
#define UIDR0 _uidr0.byte
#define UIDR0_D0 _uidr0.bit.D0
#define UIDR0_D1 _uidr0.bit.D1
#define UIDR0_D2 _uidr0.bit.D2
#define UIDR0_D3 _uidr0.bit.D3
#define UIDR0_D4 _uidr0.bit.D4
#define UIDR0_D5 _uidr0.bit.D5
#define UIDR0_D6 _uidr0.bit.D6
#define UIDR0_D7 _uidr0.bit.D7
__IO_EXTERN __io UODR0STR _uodr0;  
#define UODR0 _uodr0.byte
#define UODR0_D0 _uodr0.bit.D0
#define UODR0_D1 _uodr0.bit.D1
#define UODR0_D2 _uodr0.bit.D2
#define UODR0_D3 _uodr0.bit.D3
#define UODR0_D4 _uodr0.bit.D4
#define UODR0_D5 _uodr0.bit.D5
#define UODR0_D6 _uodr0.bit.D6
#define UODR0_D7 _uodr0.bit.D7
__IO_EXTERN __io URD0STR _urd0;  
#define URD0 _urd0.byte
#define URD0_D8 _urd0.bit.D8
#define URD0_P _urd0.bit.P
#define URD0_BCH0 _urd0.bit.BCH0
#define URD0_RC0 _urd0.bit.RC0
#define URD0_RC1 _urd0.bit.RC1
#define URD0_RC2 _urd0.bit.RC2
#define URD0_RC3 _urd0.bit.RC3
#define URD0_BCH _urd0.bit.BCH
#define URD0_RC _urd0.bitc.RC
__IO_EXTERN __io UMC1STR _umc1;   /*  UART1 */
#define UMC1 _umc1.byte
#define UMC1_SOE _umc1.bit.SOE
#define UMC1_SCKE _umc1.bit.SCKE
#define UMC1_RFC _umc1.bit.RFC
#define UMC1_SMDE _umc1.bit.SMDE
#define UMC1_MC0 _umc1.bit.MC0
#define UMC1_MC1 _umc1.bit.MC1
#define UMC1_SBL _umc1.bit.SBL
#define UMC1_PEN _umc1.bit.PEN
#define UMC1_MC _umc1.bitc.MC
__IO_EXTERN __io USR1STR _usr1;  
#define USR1 _usr1.byte
#define USR1_TBF _usr1.bit.TBF
#define USR1_RBF _usr1.bit.RBF
#define USR1_TIE _usr1.bit.TIE
#define USR1_RIE _usr1.bit.RIE
#define USR1_TDRE _usr1.bit.TDRE
#define USR1_PE _usr1.bit.PE
#define USR1_ORFE _usr1.bit.ORFE
#define USR1_RDRF _usr1.bit.RDRF
__IO_EXTERN __io UIDR1STR _uidr1;  
#define UIDR1 _uidr1.byte
#define UIDR1_D0 _uidr1.bit.D0
#define UIDR1_D1 _uidr1.bit.D1
#define UIDR1_D2 _uidr1.bit.D2
#define UIDR1_D3 _uidr1.bit.D3
#define UIDR1_D4 _uidr1.bit.D4
#define UIDR1_D5 _uidr1.bit.D5
#define UIDR1_D6 _uidr1.bit.D6
#define UIDR1_D7 _uidr1.bit.D7
__IO_EXTERN __io UODR1STR _uodr1;  
#define UODR1 _uodr1.byte
#define UODR1_D0 _uodr1.bit.D0
#define UODR1_D1 _uodr1.bit.D1
#define UODR1_D2 _uodr1.bit.D2
#define UODR1_D3 _uodr1.bit.D3
#define UODR1_D4 _uodr1.bit.D4
#define UODR1_D5 _uodr1.bit.D5
#define UODR1_D6 _uodr1.bit.D6
#define UODR1_D7 _uodr1.bit.D7
__IO_EXTERN __io URD1STR _urd1;  
#define URD1 _urd1.byte
#define URD1_D8 _urd1.bit.D8
#define URD1_P _urd1.bit.P
#define URD1_BCH0 _urd1.bit.BCH0
#define URD1_RC0 _urd1.bit.RC0
#define URD1_RC1 _urd1.bit.RC1
#define URD1_RC2 _urd1.bit.RC2
#define URD1_RC3 _urd1.bit.RC3
#define URD1_BCH _urd1.bit.BCH
#define URD1_RC _urd1.bitc.RC
__IO_EXTERN __io UMC2STR _umc2;   /*  UART2 */
#define UMC2 _umc2.byte
#define UMC2_SOE _umc2.bit.SOE
#define UMC2_SCKE _umc2.bit.SCKE
#define UMC2_RFC _umc2.bit.RFC
#define UMC2_SMDE _umc2.bit.SMDE
#define UMC2_MC0 _umc2.bit.MC0
#define UMC2_MC1 _umc2.bit.MC1
#define UMC2_SBL _umc2.bit.SBL
#define UMC2_PEN _umc2.bit.PEN
#define UMC2_MC _umc2.bitc.MC
__IO_EXTERN __io USR2STR _usr2;  
#define USR2 _usr2.byte
#define USR2_TBF _usr2.bit.TBF
#define USR2_RBF _usr2.bit.RBF
#define USR2_TIE _usr2.bit.TIE
#define USR2_RIE _usr2.bit.RIE
#define USR2_TDRE _usr2.bit.TDRE
#define USR2_PE _usr2.bit.PE
#define USR2_ORFE _usr2.bit.ORFE
#define USR2_RDRF _usr2.bit.RDRF
__IO_EXTERN __io UIDR2STR _uidr2;  
#define UIDR2 _uidr2.byte
#define UIDR2_D0 _uidr2.bit.D0
#define UIDR2_D1 _uidr2.bit.D1
#define UIDR2_D2 _uidr2.bit.D2
#define UIDR2_D3 _uidr2.bit.D3
#define UIDR2_D4 _uidr2.bit.D4
#define UIDR2_D5 _uidr2.bit.D5
#define UIDR2_D6 _uidr2.bit.D6
#define UIDR2_D7 _uidr2.bit.D7
__IO_EXTERN __io UODR2STR _uodr2;  
#define UODR2 _uodr2.byte
#define UODR2_D0 _uodr2.bit.D0
#define UODR2_D1 _uodr2.bit.D1
#define UODR2_D2 _uodr2.bit.D2
#define UODR2_D3 _uodr2.bit.D3
#define UODR2_D4 _uodr2.bit.D4
#define UODR2_D5 _uodr2.bit.D5
#define UODR2_D6 _uodr2.bit.D6
#define UODR2_D7 _uodr2.bit.D7
__IO_EXTERN __io URD2STR _urd2;  
#define URD2 _urd2.byte
#define URD2_D8 _urd2.bit.D8
#define URD2_P _urd2.bit.P
#define URD2_BCH0 _urd2.bit.BCH0
#define URD2_RC0 _urd2.bit.RC0
#define URD2_RC1 _urd2.bit.RC1
#define URD2_RC2 _urd2.bit.RC2
#define URD2_RC3 _urd2.bit.RC3
#define URD2_BCH _urd2.bit.BCH
#define URD2_RC _urd2.bitc.RC
__IO_EXTERN __io SMCSSTR _smcs;   /*  SIO with clock selection */
#define SMCS _smcs.word
#define SMCS_STRT _smcs.bit.STRT
#define SMCS_STOP _smcs.bit.STOP
#define SMCS_BUSY _smcs.bit.BUSY
#define SMCS_SIR _smcs.bit.SIR
#define SMCS_SIE _smcs.bit.SIE
#define SMCS_SMD0 _smcs.bit.SMD0
#define SMCS_SMD1 _smcs.bit.SMD1
#define SMCS_SMD2 _smcs.bit.SMD2
#define SMCS_SCOE _smcs.bit.SCOE
#define SMCS_SOE _smcs.bit.SOE
#define SMCS_BDS _smcs.bit.BDS
#define SMCS_MODE _smcs.bit.MODE
#define SMCS_SMD _smcs.bitc.SMD
__IO_EXTERN __io IO_BYTE _sdr;
#define SDR _sdr   
__IO_EXTERN __io SESSTR _ses;  
#define SES _ses.byte
#define SES_NEG _ses.bit.NEG
__IO_EXTERN __io ENIRSTR _enir;   /*  DTP, External Interrupts */
#define ENIR _enir.byte
#define ENIR_EN0 _enir.bit.EN0
#define ENIR_EN1 _enir.bit.EN1
#define ENIR_EN2 _enir.bit.EN2
#define ENIR_EN3 _enir.bit.EN3
#define ENIR_EN4 _enir.bit.EN4
#define ENIR_EN5 _enir.bit.EN5
#define ENIR_EN6 _enir.bit.EN6
#define ENIR_EN7 _enir.bit.EN7
__IO_EXTERN __io EIRRSTR _eirr;  
#define EIRR _eirr.byte
#define EIRR_ER0 _eirr.bit.ER0
#define EIRR_ER1 _eirr.bit.ER1
#define EIRR_ER2 _eirr.bit.ER2
#define EIRR_ER3 _eirr.bit.ER3
#define EIRR_ER4 _eirr.bit.ER4
#define EIRR_ER5 _eirr.bit.ER5
#define EIRR_ER6 _eirr.bit.ER6
#define EIRR_ER7 _eirr.bit.ER7
/*-------------------------------------------------------------------**
**  External Interrupt Input Level register                          **
**                                                                   **
**  This declaration is intended to be included in IO-Wizard source  **
**  files.                                                           **
**  V0.1 still missing prefix '_'                                    **
**  V1.0 symbol prefix '_' added                                     **
**  V1.2 "extern" changed to pre-defined macro of IO-Wizrad, re-     **
**       quires IO-Wizard 1.7 or later                               **
**-------------------------------------------------------------------*/

#ifndef __ELVR_H
#define __ELVR_H

typedef union{  
    IO_WORD word;
    struct{
      IO_WORD LA0 :1;
      IO_WORD LB0 :1;
      IO_WORD LA1 :1;
      IO_WORD LB1 :1;
      IO_WORD LA2 :1;
      IO_WORD LB2 :1;
      IO_WORD LA3 :1;
      IO_WORD LB3 :1;
      IO_WORD LA4 :1;
      IO_WORD LB4 :1;
      IO_WORD LA5 :1;
      IO_WORD LB5 :1;
      IO_WORD LA6 :1;
      IO_WORD LB6 :1;
      IO_WORD LA7 :1;
      IO_WORD LB7 :1;
    }bit;
    struct{
      IO_WORD LALB0 :2;
      IO_WORD LALB1 :2;
      IO_WORD LALB2 :2;
      IO_WORD LALB3 :2;
      IO_WORD LALB4 :2;
      IO_WORD LALB5 :2;
      IO_WORD LALB6 :2;
      IO_WORD LALB7 :2;
    } bitc;
} ELVRSTR;

__IO_EXTERN __io ELVRSTR _elvr;  
#define ELVR        _elvr.word
#define ELVR_LA0    _elvr.bit.LA0
#define ELVR_LB0    _elvr.bit.LB0
#define ELVR_LA1    _elvr.bit.LA1
#define ELVR_LB1    _elvr.bit.LB1
#define ELVR_LA2    _elvr.bit.LA2
#define ELVR_LB2    _elvr.bit.LB2
#define ELVR_LA3    _elvr.bit.LA3
#define ELVR_LB3    _elvr.bit.LB3
#define ELVR_LA4    _elvr.bit.LA4
#define ELVR_LB4    _elvr.bit.LB4
#define ELVR_LA5    _elvr.bit.LA5
#define ELVR_LB5    _elvr.bit.LB5
#define ELVR_LA6    _elvr.bit.LA6
#define ELVR_LB6    _elvr.bit.LB6
#define ELVR_LA7    _elvr.bit.LA7
#define ELVR_LB7    _elvr.bit.LB7
#define ELVR_LALB0  _elvr.bitc.LALB0
#define ELVR_LALB1  _elvr.bitc.LALB1
#define ELVR_LALB2  _elvr.bitc.LALB2
#define ELVR_LALB3  _elvr.bitc.LALB3
#define ELVR_LALB4  _elvr.bitc.LALB4
#define ELVR_LALB5  _elvr.bitc.LALB5
#define ELVR_LALB6  _elvr.bitc.LALB6
#define ELVR_LALB7  _elvr.bitc.LALB7

#endif
__IO_EXTERN __io ADCS0STR _adcs0;   /*  AD Converter  */
#define ADCS0 _adcs0.byte
#define ADCS0_ANE0 _adcs0.bit.ANE0
#define ADCS0_ANE1 _adcs0.bit.ANE1
#define ADCS0_ANE2 _adcs0.bit.ANE2
#define ADCS0_ANS0 _adcs0.bit.ANS0
#define ADCS0_ANS1 _adcs0.bit.ANS1
#define ADCS0_ANS2 _adcs0.bit.ANS2
#define ADCS0_MD0 _adcs0.bit.MD0
#define ADCS0_MD1 _adcs0.bit.MD1
#define ADCS0_ANE _adcs0.bitc.ANE
#define ADCS0_ANS _adcs0.bitc.ANS
#define ADCS0_MD _adcs0.bitc.MD
__IO_EXTERN __io ADCS1STR _adcs1;  
#define ADCS1 _adcs1.byte
#define ADCS1_DA _adcs1.bit.DA
#define ADCS1_STRT _adcs1.bit.STRT
#define ADCS1_STS0 _adcs1.bit.STS0
#define ADCS1_STS1 _adcs1.bit.STS1
#define ADCS1_PAUS _adcs1.bit.PAUS
#define ADCS1_INTE _adcs1.bit.INTE
#define ADCS1_INT _adcs1.bit.INT
#define ADCS1_BUSY _adcs1.bit.BUSY
#define ADCS1_STS _adcs1.bitc.STS
__IO_EXTERN __io ADCR0STR _adcr0;  
#define ADCR0 _adcr0.byte
#define ADCR0_D0 _adcr0.bit.D0
#define ADCR0_D1 _adcr0.bit.D1
#define ADCR0_D2 _adcr0.bit.D2
#define ADCR0_D3 _adcr0.bit.D3
#define ADCR0_D4 _adcr0.bit.D4
#define ADCR0_D5 _adcr0.bit.D5
#define ADCR0_D6 _adcr0.bit.D6
#define ADCR0_D7 _adcr0.bit.D7
__IO_EXTERN __io ADCR1STR _adcr1;  
#define ADCR1 _adcr1.byte
#define ADCR1_D8 _adcr1.bit.D8
#define ADCR1_D9 _adcr1.bit.D9
#define ADCR1_CT0 _adcr1.bit.CT0
#define ADCR1_CT1 _adcr1.bit.CT1
#define ADCR1_ST0 _adcr1.bit.ST0
#define ADCR1_ST1 _adcr1.bit.ST1
#define ADCR1_S10 _adcr1.bit.S10
#define ADCR1_CT _adcr1.bitc.CT
#define ADCR1_ST _adcr1.bitc.ST
__IO_EXTERN __io ADCRSTR _adcr;  
#define ADCR _adcr.word
#define ADCR_D0 _adcr.bit.D0
#define ADCR_D1 _adcr.bit.D1
#define ADCR_D2 _adcr.bit.D2
#define ADCR_D3 _adcr.bit.D3
#define ADCR_D4 _adcr.bit.D4
#define ADCR_D5 _adcr.bit.D5
#define ADCR_D6 _adcr.bit.D6
#define ADCR_D7 _adcr.bit.D7
#define ADCR_D8 _adcr.bit.D8
#define ADCR_D9 _adcr.bit.D9
__IO_EXTERN __io PPGC0STR _ppgc0;   /*  PPG control */
#define PPGC0 _ppgc0.byte
#define PPGC0_PUF0 _ppgc0.bit.PUF0
#define PPGC0_PIE0 _ppgc0.bit.PIE0
#define PPGC0_PE00 _ppgc0.bit.PE00
#define PPGC0_PEN0 _ppgc0.bit.PEN0
__IO_EXTERN __io PPGC1STR _ppgc1;  
#define PPGC1 _ppgc1.byte
#define PPGC1_MD0 _ppgc1.bit.MD0
#define PPGC1_MD1 _ppgc1.bit.MD1
#define PPGC1_PUF1 _ppgc1.bit.PUF1
#define PPGC1_PIE1 _ppgc1.bit.PIE1
#define PPGC1_PE10 _ppgc1.bit.PE10
#define PPGC1_PEN1 _ppgc1.bit.PEN1
#define PPGC1_MD _ppgc1.bitc.MD
__IO_EXTERN __io PPG01STR _ppg01;  
#define PPG01 _ppg01.byte
#define PPG01_PCM0 _ppg01.bit.PCM0
#define PPG01_PCM1 _ppg01.bit.PCM1
#define PPG01_PCM2 _ppg01.bit.PCM2
#define PPG01_PCS0 _ppg01.bit.PCS0
#define PPG01_PCS1 _ppg01.bit.PCS1
#define PPG01_PCS2 _ppg01.bit.PCS2
#define PPG01_PCM _ppg01.bitc.PCM
#define PPG01_PCS _ppg01.bitc.PCS
__IO_EXTERN __io PPGC2STR _ppgc2;  
#define PPGC2 _ppgc2.byte
#define PPGC2_PUF2 _ppgc2.bit.PUF2
#define PPGC2_PIE2 _ppgc2.bit.PIE2
#define PPGC2_PE20 _ppgc2.bit.PE20
#define PPGC2_PEN2 _ppgc2.bit.PEN2
__IO_EXTERN __io PPGC3STR _ppgc3;  
#define PPGC3 _ppgc3.byte
#define PPGC3_MD0 _ppgc3.bit.MD0
#define PPGC3_MD1 _ppgc3.bit.MD1
#define PPGC3_PUF3 _ppgc3.bit.PUF3
#define PPGC3_PIE3 _ppgc3.bit.PIE3
#define PPGC3_PE30 _ppgc3.bit.PE30
#define PPGC3_PEN3 _ppgc3.bit.PEN3
#define PPGC3_MD _ppgc3.bitc.MD
__IO_EXTERN __io PPG23STR _ppg23;  
#define PPG23 _ppg23.byte
#define PPG23_PCM0 _ppg23.bit.PCM0
#define PPG23_PCM1 _ppg23.bit.PCM1
#define PPG23_PCM2 _ppg23.bit.PCM2
#define PPG23_PCS0 _ppg23.bit.PCS0
#define PPG23_PCS1 _ppg23.bit.PCS1
#define PPG23_PCS2 _ppg23.bit.PCS2
#define PPG23_PCM _ppg23.bitc.PCM
#define PPG23_PCS _ppg23.bitc.PCS
__IO_EXTERN __io PPGC4STR _ppgc4;  
#define PPGC4 _ppgc4.byte
#define PPGC4_PUF4 _ppgc4.bit.PUF4
#define PPGC4_PIE4 _ppgc4.bit.PIE4
#define PPGC4_PE40 _ppgc4.bit.PE40
#define PPGC4_PEN4 _ppgc4.bit.PEN4
__IO_EXTERN __io PPGC5STR _ppgc5;  
#define PPGC5 _ppgc5.byte
#define PPGC5_MD0 _ppgc5.bit.MD0
#define PPGC5_MD1 _ppgc5.bit.MD1
#define PPGC5_PUF5 _ppgc5.bit.PUF5
#define PPGC5_PIE5 _ppgc5.bit.PIE5
#define PPGC5_PE50 _ppgc5.bit.PE50
#define PPGC5_PEN5 _ppgc5.bit.PEN5
#define PPGC5_MD _ppgc5.bitc.MD
__IO_EXTERN __io PPG45STR _ppg45;  
#define PPG45 _ppg45.byte
#define PPG45_PCM0 _ppg45.bit.PCM0
#define PPG45_PCM1 _ppg45.bit.PCM1
#define PPG45_PCM2 _ppg45.bit.PCM2
#define PPG45_PCS0 _ppg45.bit.PCS0
#define PPG45_PCS1 _ppg45.bit.PCS1
#define PPG45_PCS2 _ppg45.bit.PCS2
#define PPG45_PCM _ppg45.bitc.PCM
#define PPG45_PCS _ppg45.bitc.PCS
__IO_EXTERN __io PPGC6STR _ppgc6;  
#define PPGC6 _ppgc6.byte
#define PPGC6_PUF6 _ppgc6.bit.PUF6
#define PPGC6_PIE6 _ppgc6.bit.PIE6
#define PPGC6_PE60 _ppgc6.bit.PE60
#define PPGC6_PEN6 _ppgc6.bit.PEN6
__IO_EXTERN __io PPGC7STR _ppgc7;  
#define PPGC7 _ppgc7.byte
#define PPGC7_MD0 _ppgc7.bit.MD0
#define PPGC7_MD1 _ppgc7.bit.MD1
#define PPGC7_PUF7 _ppgc7.bit.PUF7
#define PPGC7_PIE7 _ppgc7.bit.PIE7
#define PPGC7_PE70 _ppgc7.bit.PE70
#define PPGC7_PEN7 _ppgc7.bit.PEN7
#define PPGC7_MD _ppgc7.bitc.MD
__IO_EXTERN __io PPG67STR _ppg67;  
#define PPG67 _ppg67.byte
#define PPG67_PCM0 _ppg67.bit.PCM0
#define PPG67_PCM1 _ppg67.bit.PCM1
#define PPG67_PCM2 _ppg67.bit.PCM2
#define PPG67_PCS0 _ppg67.bit.PCS0
#define PPG67_PCS1 _ppg67.bit.PCS1
#define PPG67_PCS2 _ppg67.bit.PCS2
#define PPG67_PCM _ppg67.bitc.PCM
#define PPG67_PCS _ppg67.bitc.PCS
__IO_EXTERN __io PPGC8STR _ppgc8;  
#define PPGC8 _ppgc8.byte
#define PPGC8_PUF8 _ppgc8.bit.PUF8
#define PPGC8_PIE8 _ppgc8.bit.PIE8
#define PPGC8_PE80 _ppgc8.bit.PE80
#define PPGC8_PEN8 _ppgc8.bit.PEN8
__IO_EXTERN __io PPGC9STR _ppgc9;  
#define PPGC9 _ppgc9.byte
#define PPGC9_MD0 _ppgc9.bit.MD0
#define PPGC9_MD1 _ppgc9.bit.MD1
#define PPGC9_PUF9 _ppgc9.bit.PUF9
#define PPGC9_PIE9 _ppgc9.bit.PIE9
#define PPGC9_PE90 _ppgc9.bit.PE90
#define PPGC9_PEN9 _ppgc9.bit.PEN9
#define PPGC9_MD _ppgc9.bitc.MD
__IO_EXTERN __io PPG89STR _ppg89;  
#define PPG89 _ppg89.byte
#define PPG89_PCM0 _ppg89.bit.PCM0
#define PPG89_PCM1 _ppg89.bit.PCM1
#define PPG89_PCM2 _ppg89.bit.PCM2
#define PPG89_PCS0 _ppg89.bit.PCS0
#define PPG89_PCS1 _ppg89.bit.PCS1
#define PPG89_PCS2 _ppg89.bit.PCS2
#define PPG89_PCM _ppg89.bitc.PCM
#define PPG89_PCS _ppg89.bitc.PCS
__IO_EXTERN __io PPGCASTR _ppgca;  
#define PPGCA _ppgca.byte
#define PPGCA_PUFA _ppgca.bit.PUFA
#define PPGCA_PIEA _ppgca.bit.PIEA
#define PPGCA_PEA0 _ppgca.bit.PEA0
#define PPGCA_PENA _ppgca.bit.PENA
__IO_EXTERN __io PPGCBSTR _ppgcb;  
#define PPGCB _ppgcb.byte
#define PPGCB_MD0 _ppgcb.bit.MD0
#define PPGCB_MD1 _ppgcb.bit.MD1
#define PPGCB_PUFB _ppgcb.bit.PUFB
#define PPGCB_PIEB _ppgcb.bit.PIEB
#define PPGCB_PEB0 _ppgcb.bit.PEB0
#define PPGCB_PENB _ppgcb.bit.PENB
#define PPGCB_MD _ppgcb.bitc.MD
__IO_EXTERN __io PPGABSTR _ppgab;  
#define PPGAB _ppgab.byte
#define PPGAB_PCM0 _ppgab.bit.PCM0
#define PPGAB_PCM1 _ppgab.bit.PCM1
#define PPGAB_PCM2 _ppgab.bit.PCM2
#define PPGAB_PCS0 _ppgab.bit.PCS0
#define PPGAB_PCS1 _ppgab.bit.PCS1
#define PPGAB_PCS2 _ppgab.bit.PCS2
#define PPGAB_PCM _ppgab.bitc.PCM
#define PPGAB_PCS _ppgab.bitc.PCS
__IO_EXTERN __io TMCSR0STR _tmcsr0;   /*  Reload Timer */
#define TMCSR0 _tmcsr0.word
#define TMCSR0_TRG _tmcsr0.bit.TRG
#define TMCSR0_CNTE _tmcsr0.bit.CNTE
#define TMCSR0_UF _tmcsr0.bit.UF
#define TMCSR0_INTE _tmcsr0.bit.INTE
#define TMCSR0_RELD _tmcsr0.bit.RELD
#define TMCSR0_OUTL _tmcsr0.bit.OUTL
#define TMCSR0_OUTE _tmcsr0.bit.OUTE
#define TMCSR0_MOD0 _tmcsr0.bit.MOD0
#define TMCSR0_MOD1 _tmcsr0.bit.MOD1
#define TMCSR0_MOD2 _tmcsr0.bit.MOD2
#define TMCSR0_CSL0 _tmcsr0.bit.CSL0
#define TMCSR0_CSL1 _tmcsr0.bit.CSL1
#define TMCSR0_MOD _tmcsr0.bitc.MOD
#define TMCSR0_CSL _tmcsr0.bitc.CSL
__IO_EXTERN __io TMCSR1STR _tmcsr1;  
#define TMCSR1 _tmcsr1.word
#define TMCSR1_TRG _tmcsr1.bit.TRG
#define TMCSR1_CNTE _tmcsr1.bit.CNTE
#define TMCSR1_UF _tmcsr1.bit.UF
#define TMCSR1_INTE _tmcsr1.bit.INTE
#define TMCSR1_RELD _tmcsr1.bit.RELD
#define TMCSR1_OUTL _tmcsr1.bit.OUTL
#define TMCSR1_OUTE _tmcsr1.bit.OUTE
#define TMCSR1_MOD0 _tmcsr1.bit.MOD0
#define TMCSR1_MOD1 _tmcsr1.bit.MOD1
#define TMCSR1_MOD2 _tmcsr1.bit.MOD2
#define TMCSR1_CSL0 _tmcsr1.bit.CSL0
#define TMCSR1_CSL1 _tmcsr1.bit.CSL1
#define TMCSR1_MOD _tmcsr1.bitc.MOD
#define TMCSR1_CSL _tmcsr1.bitc.CSL
__IO_EXTERN __io ICS01STR _ics01;   /*  Input Capture */
#define ICS01 _ics01.byte
#define ICS01_EG00 _ics01.bit.EG00
#define ICS01_EG01 _ics01.bit.EG01
#define ICS01_EG10 _ics01.bit.EG10
#define ICS01_EG11 _ics01.bit.EG11
#define ICS01_ICE0 _ics01.bit.ICE0
#define ICS01_ICE1 _ics01.bit.ICE1
#define ICS01_ICP0 _ics01.bit.ICP0
#define ICS01_ICP1 _ics01.bit.ICP1
#define ICS01_EG0 _ics01.bitc.EG0
#define ICS01_EG1 _ics01.bitc.EG1
__IO_EXTERN __io ICS23STR _ics23;  
#define ICS23 _ics23.byte
#define ICS23_EG20 _ics23.bit.EG20
#define ICS23_EG21 _ics23.bit.EG21
#define ICS23_EG30 _ics23.bit.EG30
#define ICS23_EG31 _ics23.bit.EG31
#define ICS23_ICE2 _ics23.bit.ICE2
#define ICS23_ICE3 _ics23.bit.ICE3
#define ICS23_ICP2 _ics23.bit.ICP2
#define ICS23_ICP3 _ics23.bit.ICP3
#define ICS23_EG2 _ics23.bitc.EG2
#define ICS23_EG3 _ics23.bitc.EG3
__IO_EXTERN __io ICS45STR _ics45;  
#define ICS45 _ics45.byte
#define ICS45_EG40 _ics45.bit.EG40
#define ICS45_EG41 _ics45.bit.EG41
#define ICS45_EG50 _ics45.bit.EG50
#define ICS45_EG51 _ics45.bit.EG51
#define ICS45_ICE4 _ics45.bit.ICE4
#define ICS45_ICE5 _ics45.bit.ICE5
#define ICS45_ICP4 _ics45.bit.ICP4
#define ICS45_ICP5 _ics45.bit.ICP5
#define ICS45_EG4 _ics45.bitc.EG4
#define ICS45_EG5 _ics45.bitc.EG5
__IO_EXTERN __io OCS01STR _ocs01;   /*  Output compare */
#define OCS01 _ocs01.word
#define OCS01_CST0 _ocs01.bit.CST0
#define OCS01_CST1 _ocs01.bit.CST1
#define OCS01_ICE0 _ocs01.bit.ICE0
#define OCS01_ICE1 _ocs01.bit.ICE1
#define OCS01_ICP0 _ocs01.bit.ICP0
#define OCS01_ICP1 _ocs01.bit.ICP1
#define OCS01_OTD0 _ocs01.bit.OTD0
#define OCS01_OTD1 _ocs01.bit.OTD1
#define OCS01_OTE0 _ocs01.bit.OTE0
#define OCS01_OTE1 _ocs01.bit.OTE1
#define OCS01_CMOD _ocs01.bit.CMOD
#define OCS01_CST _ocs01.bitc.CST
#define OCS01_ICE _ocs01.bitc.ICE
#define OCS01_ICP _ocs01.bitc.ICP
#define OCS01_OTD _ocs01.bitc.OTD
#define OCS01_OTE _ocs01.bitc.OTE
__IO_EXTERN __io OCS0STR _ocs0;  
#define OCS0 _ocs0.byte
#define OCS0_CST0 _ocs0.bit.CST0
#define OCS0_CST1 _ocs0.bit.CST1
#define OCS0_ICE0 _ocs0.bit.ICE0
#define OCS0_ICE1 _ocs0.bit.ICE1
#define OCS0_ICP0 _ocs0.bit.ICP0
#define OCS0_ICP1 _ocs0.bit.ICP1
#define OCS0_CST _ocs0.bitc.CST
#define OCS0_ICE _ocs0.bitc.ICE
#define OCS0_ICP _ocs0.bitc.ICP
__IO_EXTERN __io OCS1STR _ocs1;  
#define OCS1 _ocs1.byte
#define OCS1_OTD0 _ocs1.bit.OTD0
#define OCS1_OTD1 _ocs1.bit.OTD1
#define OCS1_OTE0 _ocs1.bit.OTE0
#define OCS1_OTE1 _ocs1.bit.OTE1
#define OCS1_CMOD _ocs1.bit.CMOD
#define OCS1_OTD _ocs1.bitc.OTD
#define OCS1_OTE _ocs1.bitc.OTE
__IO_EXTERN __io OCS23STR _ocs23;  
#define OCS23 _ocs23.word
#define OCS23_CST2 _ocs23.bit.CST2
#define OCS23_CST3 _ocs23.bit.CST3
#define OCS23_ICE2 _ocs23.bit.ICE2
#define OCS23_ICE3 _ocs23.bit.ICE3
#define OCS23_ICP2 _ocs23.bit.ICP2
#define OCS23_ICP3 _ocs23.bit.ICP3
#define OCS23_OTD2 _ocs23.bit.OTD2
#define OCS23_OTD3 _ocs23.bit.OTD3
#define OCS23_OTE2 _ocs23.bit.OTE2
#define OCS23_OTE3 _ocs23.bit.OTE3
#define OCS23_CMOD _ocs23.bit.CMOD
#define OCS23_CST _ocs23.bitc.CST
#define OCS23_ICE _ocs23.bitc.ICE
#define OCS23_ICP _ocs23.bitc.ICP
#define OCS23_OTD _ocs23.bitc.OTD
#define OCS23_OTE _ocs23.bitc.OTE
__IO_EXTERN __io OCS2STR _ocs2;  
#define OCS2 _ocs2.byte
#define OCS2_CST2 _ocs2.bit.CST2
#define OCS2_CST3 _ocs2.bit.CST3
#define OCS2_ICE2 _ocs2.bit.ICE2
#define OCS2_ICE3 _ocs2.bit.ICE3
#define OCS2_ICP2 _ocs2.bit.ICP2
#define OCS2_ICP3 _ocs2.bit.ICP3
#define OCS2_CST _ocs2.bitc.CST
#define OCS2_ICE _ocs2.bitc.ICE
#define OCS2_ICP _ocs2.bitc.ICP
__IO_EXTERN __io OCS3STR _ocs3;  
#define OCS3 _ocs3.byte
#define OCS3_OTD2 _ocs3.bit.OTD2
#define OCS3_OTD3 _ocs3.bit.OTD3
#define OCS3_OTE2 _ocs3.bit.OTE2
#define OCS3_OTE3 _ocs3.bit.OTE3
#define OCS3_CMOD _ocs3.bit.CMOD
#define OCS3_OTD _ocs3.bitc.OTD
#define OCS3_OTE _ocs3.bitc.OTE
__IO_EXTERN __io OCS45STR _ocs45;  
#define OCS45 _ocs45.word
#define OCS45_CST4 _ocs45.bit.CST4
#define OCS45_CST5 _ocs45.bit.CST5
#define OCS45_ICE4 _ocs45.bit.ICE4
#define OCS45_ICE5 _ocs45.bit.ICE5
#define OCS45_ICP4 _ocs45.bit.ICP4
#define OCS45_ICP5 _ocs45.bit.ICP5
#define OCS45_OTD4 _ocs45.bit.OTD4
#define OCS45_OTD5 _ocs45.bit.OTD5
#define OCS45_OTE4 _ocs45.bit.OTE4
#define OCS45_OTE5 _ocs45.bit.OTE5
#define OCS45_CMOD _ocs45.bit.CMOD
#define OCS45_CST _ocs45.bitc.CST
#define OCS45_ICE _ocs45.bitc.ICE
#define OCS45_ICP _ocs45.bitc.ICP
#define OCS45_OTD _ocs45.bitc.OTD
#define OCS45_OTE _ocs45.bitc.OTE
__IO_EXTERN __io OCS4STR _ocs4;  
#define OCS4 _ocs4.byte
#define OCS4_CST4 _ocs4.bit.CST4
#define OCS4_CST5 _ocs4.bit.CST5
#define OCS4_ICE4 _ocs4.bit.ICE4
#define OCS4_ICE5 _ocs4.bit.ICE5
#define OCS4_ICP4 _ocs4.bit.ICP4
#define OCS4_ICP5 _ocs4.bit.ICP5
#define OCS4_CST _ocs4.bitc.CST
#define OCS4_ICE _ocs4.bitc.ICE
#define OCS4_ICP _ocs4.bitc.ICP
__IO_EXTERN __io OCS5STR _ocs5;  
#define OCS5 _ocs5.byte
#define OCS5_OTD4 _ocs5.bit.OTD4
#define OCS5_OTD5 _ocs5.bit.OTD5
#define OCS5_OTE4 _ocs5.bit.OTE4
#define OCS5_OTE5 _ocs5.bit.OTE5
#define OCS5_CMOD _ocs5.bit.CMOD
#define OCS5_OTD _ocs5.bitc.OTD
#define OCS5_OTE _ocs5.bitc.OTE
__IO_EXTERN __io SGCRSTR _sgcr;   /* Sound control */
#define SGCR _sgcr.word
#define SGCR_ST _sgcr.bit.ST
#define SGCR_INT _sgcr.bit.INT
#define SGCR_INTE _sgcr.bit.INTE
#define SGCR_OE1 _sgcr.bit.OE1
#define SGCR_OE2 _sgcr.bit.OE2
#define SGCR_TONE _sgcr.bit.TONE
#define SGCR_S0 _sgcr.bit.S0
#define SGCR_S1 _sgcr.bit.S1
#define SGCR_DEC _sgcr.bit.DEC
#define SGCR_BUSY _sgcr.bit.BUSY
#define SGCR_TST _sgcr.bit.TST
#define SGCR_S _sgcr.bitc.S
__IO_EXTERN __io WTCRSTR _wtcr;   /*  Watch Timer */
#define WTCR _wtcr.word
#define WTCR_INT0 _wtcr.bit.INT0
#define WTCR_INTE0 _wtcr.bit.INTE0
#define WTCR_INT1 _wtcr.bit.INT1
#define WTCR_INTE1 _wtcr.bit.INTE1
#define WTCR_INT2 _wtcr.bit.INT2
#define WTCR_INTE2 _wtcr.bit.INTE2
#define WTCR_INT3 _wtcr.bit.INT3
#define WTCR_INTE3 _wtcr.bit.INTE3
#define WTCR_ST _wtcr.bit.ST
#define WTCR_OE _wtcr.bit.OE
#define WTCR_UPDT _wtcr.bit.UPDT
#define WTCR_TST0 _wtcr.bit.TST0
#define WTCR_TST1 _wtcr.bit.TST1
#define WTCR_TST2 _wtcr.bit.TST2
__IO_EXTERN __io PWC0STR _pwc0;   /* PWM0 */
#define PWC0 _pwc0.byte
#define PWC0_TST _pwc0.bit.TST
#define PWC0_CE _pwc0.bit.CE
#define PWC0_P0 _pwc0.bit.P0
#define PWC0_P1 _pwc0.bit.P1
#define PWC0_OE1 _pwc0.bit.OE1
#define PWC0_OE2 _pwc0.bit.OE2
__IO_EXTERN __io PWC1STR _pwc1;  
#define PWC1 _pwc1.byte
#define PWC1_TST _pwc1.bit.TST
#define PWC1_CE _pwc1.bit.CE
#define PWC1_P0 _pwc1.bit.P0
#define PWC1_P1 _pwc1.bit.P1
#define PWC1_OE1 _pwc1.bit.OE1
#define PWC1_OE2 _pwc1.bit.OE2
__IO_EXTERN __io PWC2STR _pwc2;  
#define PWC2 _pwc2.byte
#define PWC2_TST _pwc2.bit.TST
#define PWC2_CE _pwc2.bit.CE
#define PWC2_P0 _pwc2.bit.P0
#define PWC2_P1 _pwc2.bit.P1
#define PWC2_OE1 _pwc2.bit.OE1
#define PWC2_OE2 _pwc2.bit.OE2
__IO_EXTERN __io PWC3STR _pwc3;  
#define PWC3 _pwc3.byte
#define PWC3_TST _pwc3.bit.TST
#define PWC3_CE _pwc3.bit.CE
#define PWC3_P0 _pwc3.bit.P0
#define PWC3_P1 _pwc3.bit.P1
#define PWC3_OE1 _pwc3.bit.OE1
#define PWC3_OE2 _pwc3.bit.OE2
__IO_EXTERN __io CDCRSTR _cdcr;   /* Serial IO Prescaler */
#define CDCR _cdcr.byte
#define CDCR_DIV0 _cdcr.bit.DIV0
#define CDCR_DIV1 _cdcr.bit.DIV1
#define CDCR_DIV2 _cdcr.bit.DIV2
#define CDCR_DIV3 _cdcr.bit.DIV3
#define CDCR_DIV _cdcr.bitc.DIV
__IO_EXTERN __io TCCSSTR _tccs;   /* IO timer */
#define TCCS _tccs.byte
#define TCCS_CLK0 _tccs.bit.CLK0
#define TCCS_CLK1 _tccs.bit.CLK1
#define TCCS_CLR _tccs.bit.CLR
#define TCCS_MODE _tccs.bit.MODE
#define TCCS_STOP _tccs.bit.STOP
#define TCCS_IVFE _tccs.bit.IVFE
#define TCCS_IVF _tccs.bit.IVF
#define TCCS_CLK _tccs.bitc.CLK
__IO_EXTERN __io ROMMSTR _romm;   /*  ROM Mirror */
#define ROMM _romm.byte
#define ROMM_MI _romm.bit.MI
__IO_EXTERN __io PACSRSTR _pacsr;   /*  ROM Correction */
#define PACSR _pacsr.byte
#define PACSR_AD0E _pacsr.bit.AD0E
#define PACSR_AD1E _pacsr.bit.AD1E
__IO_EXTERN __io DIRRSTR _dirr;   /*  Delay interrupt enable */
#define DIRR _dirr.byte
#define DIRR_R0 _dirr.bit.R0
__IO_EXTERN __io LPMCRSTR _lpmcr;   /*  Low power mode control */
#define LPMCR _lpmcr.byte
#define LPMCR_CG0 _lpmcr.bit.CG0
#define LPMCR_CG1 _lpmcr.bit.CG1
#define LPMCR_RST _lpmcr.bit.RST
#define LPMCR_SPL _lpmcr.bit.SPL
#define LPMCR_SLP _lpmcr.bit.SLP
#define LPMCR_STP _lpmcr.bit.STP
#define LPMCR_CG _lpmcr.bitc.CG
__IO_EXTERN __io CKSCRSTR _ckscr;   /*  Clock selection */
#define CKSCR _ckscr.byte
#define CKSCR_CS0 _ckscr.bit.CS0
#define CKSCR_CS1 _ckscr.bit.CS1
#define CKSCR_MCS _ckscr.bit.MCS
#define CKSCR_WS0 _ckscr.bit.WS0
#define CKSCR_WS1 _ckscr.bit.WS1
#define CKSCR_MCM _ckscr.bit.MCM
#define CKSCR_CS _ckscr.bitc.CS
#define CKSCR_WS _ckscr.bitc.WS
__IO_EXTERN __io WDTCSTR _wdtc;   /* Watchdog Control */
#define WDTC _wdtc.word
#define WDTC_WT0 _wdtc.bit.WT0
#define WDTC_WT1 _wdtc.bit.WT1
#define WDTC_WTE _wdtc.bit.WTE
#define WDTC_SRST _wdtc.bit.SRST
#define WDTC_ERST _wdtc.bit.ERST
#define WDTC_WRST _wdtc.bit.WRST
#define WDTC_STBR _wdtc.bit.STBR
#define WDTC_PONR _wdtc.bit.PONR
#define WDTC_WT _wdtc.bitc.WT
__IO_EXTERN __io TBTCSTR _tbtc;   /*  Time Base timer */
#define TBTC _tbtc.byte
#define TBTC_TBC0 _tbtc.bit.TBC0
#define TBTC_TBC1 _tbtc.bit.TBC1
#define TBTC_TBR _tbtc.bit.TBR
#define TBTC_TBOF _tbtc.bit.TBOF
#define TBTC_TBIE _tbtc.bit.TBIE
#define TBTC_TBC _tbtc.bitc.TBC
__IO_EXTERN __io FMCSSTR _fmcs;   /* Flash Control Register */
#define FMCS _fmcs.byte
#define FMCS_LPM0 _fmcs.bit.LPM0
#define FMCS_LPM1 _fmcs.bit.LPM1
#define FMCS_RDY _fmcs.bit.RDY
#define FMCS_WE _fmcs.bit.WE
#define FMCS_RDYINT _fmcs.bit.RDYINT
#define FMCS_INTE _fmcs.bit.INTE
/*******************************************************************
 *
 *    DESCRIPTION:  Interrupt Control Register Declaration
 *
 *    AUTHOR:       Fujitsu Mikroelektronik GmbH
 *
 *    HISTORY:    
 * Version 1.0      26.01.99: 
 *      - original version
 * Version 1.2      11.02.99
 *      - "extern" changed to pre-defined macro of IO-Wizard 
 *        (__IO_EXTERN), requires IO-Wizard 1.7 or later
 *
 *******************************************************************/

#ifndef __ICR_H
#define __ICR_H

typedef union{  
    unsigned char    byte;
    struct{
      unsigned char IL0      :1;
      unsigned char IL1      :1;
      unsigned char IL2      :1;
      unsigned char ISE      :1;
      unsigned char ICS0     :1;
      unsigned char ICS1     :1;
      unsigned char ICS2     :1;
      unsigned char ICS3     :1;
    }bit;
    struct{
            unsigned char    :4;
      const unsigned char S0 :1;
      const unsigned char S1 :1;
    }bitrd;
    struct{
      unsigned char IL       :3;
      unsigned char :1;
      unsigned char ICS      :4;
    }bitc;
    struct{
            unsigned char    :4;
      const unsigned char S  :2;
    }bitcrd;
 }ICRSTR;

__IO_EXTERN __io ICRSTR _icr[16];

#define ICR(i)        _icr[i].byte
#define ICR_IL0(i)    _icr[i].bit.IL0
#define ICR_IL1(i)    _icr[i].bit.IL1
#define ICR_IL2(i)    _icr[i].bit.IL2
#define ICR_ISE(i)    _icr[i].bit.ISE
#define ICR_ICS0(i)   _icr[i].bit.ICS0
#define ICR_ICS1(i)   _icr[i].bit.ICS1
#define ICR_ICS2(i)   _icr[i].bit.ICS2
#define ICR_ICS3(i)   _icr[i].bit.ICS3
#define ICR_IL(i)     _icr[i].bitc.IL
#define ICR_ICS(i)    _icr[i].bitc.ICS
#define ICR_S0(i)     _icr[i].bitrd.S0
#define ICR_S1(i)     _icr[i].bitrd.S1
#define ICR_S(i)      _icr[i].bitcrd.S

#define ICR00       _icr[0].byte
#define ICR00_IL0   _icr[0].bit.IL0
#define ICR00_IL1   _icr[0].bit.IL1
#define ICR00_IL2   _icr[0].bit.IL2
#define ICR00_ISE   _icr[0].bit.ISE
#define ICR00_ICS0  _icr[0].bit.ICS0
#define ICR00_ICS1  _icr[0].bit.ICS1
#define ICR00_ICS2  _icr[0].bit.ICS2
#define ICR00_ICS3  _icr[0].bit.ICS3
#define ICR00_IL    _icr[0].bitc.IL
#define ICR00_ICS   _icr[0].bitc.ICS
#define ICR00_S0    _icr[0].bitrd.S0
#define ICR00_S1    _icr[0].bitrd.S1
#define ICR00_S     _icr[0].bitcrd.S

#define ICR01       _icr[1].byte
#define ICR01_IL0   _icr[1].bit.IL0
#define ICR01_IL1   _icr[1].bit.IL1
#define ICR01_IL2   _icr[1].bit.IL2
#define ICR01_ISE   _icr[1].bit.ISE
#define ICR01_ICS0  _icr[1].bit.ICS0
#define ICR01_ICS1  _icr[1].bit.ICS1
#define ICR01_ICS2  _icr[1].bit.ICS2
#define ICR01_ICS3  _icr[1].bit.ICS3
#define ICR01_IL    _icr[1].bitc.IL
#define ICR01_ICS   _icr[1].bitc.ICS
#define ICR01_S0    _icr[1].bitrd.S0
#define ICR01_S1    _icr[1].bitrd.S1
#define ICR01_S     _icr[1].bitcrd.S

#define ICR02       _icr[2].byte
#define ICR02_IL0   _icr[2].bit.IL0
#define ICR02_IL1   _icr[2].bit.IL1
#define ICR02_IL2   _icr[2].bit.IL2
#define ICR02_ISE   _icr[2].bit.ISE
#define ICR02_ICS0  _icr[2].bit.ICS0
#define ICR02_ICS1  _icr[2].bit.ICS1
#define ICR02_ICS2  _icr[2].bit.ICS2
#define ICR02_ICS3  _icr[2].bit.ICS3
#define ICR02_IL    _icr[2].bitc.IL
#define ICR02_ICS   _icr[2].bitc.ICS
#define ICR02_S0    _icr[2].bitrd.S0
#define ICR02_S1    _icr[2].bitrd.S1
#define ICR02_S     _icr[2].bitcrd.S

#define ICR03       _icr[3].byte
#define ICR03_IL0   _icr[3].bit.IL0
#define ICR03_IL1   _icr[3].bit.IL1
#define ICR03_IL2   _icr[3].bit.IL2
#define ICR03_ISE   _icr[3].bit.ISE
#define ICR03_ICS0  _icr[3].bit.ICS0
#define ICR03_ICS1  _icr[3].bit.ICS1
#define ICR03_ICS2  _icr[3].bit.ICS2
#define ICR03_ICS3  _icr[3].bit.ICS3
#define ICR03_IL    _icr[3].bitc.IL
#define ICR03_ICS   _icr[3].bitc.ICS
#define ICR03_S0    _icr[3].bitrd.S0
#define ICR03_S1    _icr[3].bitrd.S1
#define ICR03_S     _icr[3].bitcrd.S

#define ICR04       _icr[4].byte
#define ICR04_IL4   _icr[4].bit.IL0
#define ICR04_IL1   _icr[4].bit.IL1
#define ICR04_IL2   _icr[4].bit.IL2
#define ICR04_ISE   _icr[4].bit.ISE
#define ICR04_ICS4  _icr[4].bit.ICS0
#define ICR04_ICS1  _icr[4].bit.ICS1
#define ICR04_ICS2  _icr[4].bit.ICS2
#define ICR04_ICS3  _icr[4].bit.ICS3
#define ICR04_IL    _icr[4].bitc.IL
#define ICR04_ICS   _icr[4].bitc.ICS
#define ICR04_S4    _icr[4].bitrd.S0
#define ICR04_S1    _icr[4].bitrd.S1
#define ICR04_S     _icr[4].bitcrd.S

#define ICR05       _icr[5].byte
#define ICR05_IL0   _icr[5].bit.IL0
#define ICR05_IL1   _icr[5].bit.IL1
#define ICR05_IL2   _icr[5].bit.IL2
#define ICR05_ISE   _icr[5].bit.ISE
#define ICR05_ICS0  _icr[5].bit.ICS0
#define ICR05_ICS1  _icr[5].bit.ICS1
#define ICR05_ICS2  _icr[5].bit.ICS2
#define ICR05_ICS3  _icr[5].bit.ICS3
#define ICR05_IL    _icr[5].bitc.IL
#define ICR05_ICS   _icr[5].bitc.ICS
#define ICR05_S0    _icr[5].bitrd.S0
#define ICR05_S1    _icr[5].bitrd.S1
#define ICR05_S     _icr[5].bitcrd.S

#define ICR06       _icr[6].byte
#define ICR06_IL0   _icr[6].bit.IL0
#define ICR06_IL1   _icr[6].bit.IL1
#define ICR06_IL2   _icr[6].bit.IL2
#define ICR06_ISE   _icr[6].bit.ISE
#define ICR06_ICS0  _icr[6].bit.ICS0
#define ICR06_ICS1  _icr[6].bit.ICS1
#define ICR06_ICS2  _icr[6].bit.ICS2
#define ICR06_ICS3  _icr[6].bit.ICS3
#define ICR06_IL    _icr[6].bitc.IL
#define ICR06_ICS   _icr[6].bitc.ICS
#define ICR06_S0    _icr[6].bitrd.S0
#define ICR06_S1    _icr[6].bitrd.S1
#define ICR06_S     _icr[6].bitcrd.S

#define ICR07       _icr[7].byte
#define ICR07_IL0   _icr[7].bit.IL0
#define ICR07_IL1   _icr[7].bit.IL1
#define ICR07_IL2   _icr[7].bit.IL2
#define ICR07_ISE   _icr[7].bit.ISE
#define ICR07_ICS0  _icr[7].bit.ICS0
#define ICR07_ICS1  _icr[7].bit.ICS1
#define ICR07_ICS2  _icr[7].bit.ICS2
#define ICR07_ICS3  _icr[7].bit.ICS3
#define ICR07_IL    _icr[7].bitc.IL
#define ICR07_ICS   _icr[7].bitc.ICS
#define ICR07_S0    _icr[7].bitrd.S0
#define ICR07_S1    _icr[7].bitrd.S1
#define ICR07_S     _icr[7].bitcrd.S

#define ICR08       _icr[8].byte
#define ICR08_IL0   _icr[8].bit.IL0
#define ICR08_IL1   _icr[8].bit.IL1
#define ICR08_IL2   _icr[8].bit.IL2
#define ICR08_ISE   _icr[8].bit.ISE
#define ICR08_ICS0  _icr[8].bit.ICS0
#define ICR08_ICS1  _icr[8].bit.ICS1
#define ICR08_ICS2  _icr[8].bit.ICS2
#define ICR08_ICS3  _icr[8].bit.ICS3
#define ICR08_IL    _icr[8].bitc.IL
#define ICR08_ICS   _icr[8].bitc.ICS
#define ICR08_S0    _icr[8].bitrd.S0
#define ICR08_S1    _icr[8].bitrd.S1
#define ICR08_S     _icr[8].bitcrd.S

#define ICR09       _icr[9].byte
#define ICR09_IL0   _icr[9].bit.IL0
#define ICR09_IL1   _icr[9].bit.IL1
#define ICR09_IL2   _icr[9].bit.IL2
#define ICR09_ISE   _icr[9].bit.ISE
#define ICR09_ICS0  _icr[9].bit.ICS0
#define ICR09_ICS1  _icr[9].bit.ICS1
#define ICR09_ICS2  _icr[9].bit.ICS2
#define ICR09_ICS3  _icr[9].bit.ICS3
#define ICR09_IL    _icr[9].bitc.IL
#define ICR09_ICS   _icr[9].bitc.ICS
#define ICR09_S0    _icr[9].bitrd.S0
#define ICR09_S1    _icr[9].bitrd.S1
#define ICR09_S     _icr[9].bitcrd.S

#define ICR10       _icr[10].byte
#define ICR10_IL0   _icr[10].bit.IL0
#define ICR10_IL1   _icr[10].bit.IL1
#define ICR10_IL2   _icr[10].bit.IL2
#define ICR10_ISE   _icr[10].bit.ISE
#define ICR10_ICS0  _icr[10].bit.ICS0
#define ICR10_ICS1  _icr[10].bit.ICS1
#define ICR10_ICS2  _icr[10].bit.ICS2
#define ICR10_ICS3  _icr[10].bit.ICS3
#define ICR10_IL    _icr[10].bitc.IL
#define ICR10_ICS   _icr[10].bitc.ICS
#define ICR10_S0    _icr[10].bitrd.S0
#define ICR10_S1    _icr[10].bitrd.S1
#define ICR10_S     _icr[10].bitcrd.S

#define ICR11       _icr[11].byte
#define ICR11_IL0   _icr[11].bit.IL0
#define ICR11_IL1   _icr[11].bit.IL1
#define ICR11_IL2   _icr[11].bit.IL2
#define ICR11_ISE   _icr[11].bit.ISE
#define ICR11_ICS0  _icr[11].bit.ICS0
#define ICR11_ICS1  _icr[11].bit.ICS1
#define ICR11_ICS2  _icr[11].bit.ICS2
#define ICR11_ICS3  _icr[11].bit.ICS3
#define ICR11_IL    _icr[11].bitc.IL
#define ICR11_ICS   _icr[11].bitc.ICS
#define ICR11_S0    _icr[11].bitrd.S0
#define ICR11_S1    _icr[11].bitrd.S1
#define ICR11_S     _icr[11].bitcrd.S

#define ICR12       _icr[12].byte
#define ICR12_IL0   _icr[12].bit.IL0
#define ICR12_IL1   _icr[12].bit.IL1
#define ICR12_IL2   _icr[12].bit.IL2
#define ICR12_ISE   _icr[12].bit.ISE
#define ICR12_ICS0  _icr[12].bit.ICS0
#define ICR12_ICS1  _icr[12].bit.ICS1
#define ICR12_ICS2  _icr[12].bit.ICS2
#define ICR12_ICS3  _icr[12].bit.ICS3
#define ICR12_IL    _icr[12].bitc.IL
#define ICR12_ICS   _icr[12].bitc.ICS
#define ICR12_S0    _icr[12].bitrd.S0
#define ICR12_S1    _icr[12].bitrd.S1
#define ICR12_S     _icr[12].bitcrd.S

#define ICR13       _icr[13].byte
#define ICR13_IL0   _icr[13].bit.IL0
#define ICR13_IL1   _icr[13].bit.IL1
#define ICR13_IL2   _icr[13].bit.IL2
#define ICR13_ISE   _icr[13].bit.ISE
#define ICR13_ICS0  _icr[13].bit.ICS0
#define ICR13_ICS1  _icr[13].bit.ICS1
#define ICR13_ICS2  _icr[13].bit.ICS2
#define ICR13_ICS3  _icr[13].bit.ICS3
#define ICR13_IL    _icr[13].bitc.IL
#define ICR13_ICS   _icr[13].bitc.ICS
#define ICR13_S0    _icr[13].bitrd.S0
#define ICR13_S1    _icr[13].bitrd.S1
#define ICR13_S     _icr[13].bitcrd.S

#define ICR14       _icr[14].byte
#define ICR14_IL0   _icr[14].bit.IL0
#define ICR14_IL1   _icr[14].bit.IL1
#define ICR14_IL2   _icr[14].bit.IL2
#define ICR14_ISE   _icr[14].bit.ISE
#define ICR14_ICS0  _icr[14].bit.ICS0
#define ICR14_ICS1  _icr[14].bit.ICS1
#define ICR14_ICS2  _icr[14].bit.ICS2
#define ICR14_ICS3  _icr[14].bit.ICS3
#define ICR14_IL    _icr[14].bitc.IL
#define ICR14_ICS   _icr[14].bitc.ICS
#define ICR14_S0    _icr[14].bitrd.S0
#define ICR14_S1    _icr[14].bitrd.S1
#define ICR14_S     _icr[14].bitcrd.S

#define ICR15       _icr[15].byte
#define ICR15_IL0   _icr[15].bit.IL0
#define ICR15_IL1   _icr[15].bit.IL1
#define ICR15_IL2   _icr[15].bit.IL2
#define ICR15_ISE   _icr[15].bit.ISE
#define ICR15_ICS0  _icr[15].bit.ICS0
#define ICR15_ICS1  _icr[15].bit.ICS1
#define ICR15_ICS2  _icr[15].bit.ICS2
#define ICR15_ICS3  _icr[15].bit.ICS3
#define ICR15_IL    _icr[15].bitc.IL
#define ICR15_ICS   _icr[15].bitc.ICS
#define ICR15_S0    _icr[15].bitrd.S0
#define ICR15_S1    _icr[15].bitrd.S1
#define ICR15_S     _icr[15].bitcrd.S


#endif /*  __ICR_H */
__IO_EXTENDED IO_BYTE _prll0;
#define PRLL0 _prll0    /*  PPG data */
__IO_EXTENDED IO_BYTE _prlh0;
#define PRLH0 _prlh0   
__IO_EXTENDED IO_BYTE _prll1;
#define PRLL1 _prll1   
__IO_EXTENDED IO_BYTE _prlh1;
#define PRLH1 _prlh1   
__IO_EXTENDED IO_BYTE _prll2;
#define PRLL2 _prll2   
__IO_EXTENDED IO_BYTE _prlh2;
#define PRLH2 _prlh2   
__IO_EXTENDED IO_BYTE _prll3;
#define PRLL3 _prll3   
__IO_EXTENDED IO_BYTE _prlh3;
#define PRLH3 _prlh3   
__IO_EXTENDED IO_BYTE _prll4;
#define PRLL4 _prll4   
__IO_EXTENDED IO_BYTE _prlh4;
#define PRLH4 _prlh4   
__IO_EXTENDED IO_BYTE _prll5;
#define PRLL5 _prll5   
__IO_EXTENDED IO_BYTE _prlh5;
#define PRLH5 _prlh5   
__IO_EXTENDED IO_BYTE _prll6;
#define PRLL6 _prll6   
__IO_EXTENDED IO_BYTE _prlh6;
#define PRLH6 _prlh6   
__IO_EXTENDED IO_BYTE _prll7;
#define PRLL7 _prll7   
__IO_EXTENDED IO_BYTE _prlh7;
#define PRLH7 _prlh7   
__IO_EXTENDED IO_BYTE _prll8;
#define PRLL8 _prll8   
__IO_EXTENDED IO_BYTE _prlh8;
#define PRLH8 _prlh8   
__IO_EXTENDED IO_BYTE _prll9;
#define PRLL9 _prll9   
__IO_EXTENDED IO_BYTE _prlh9;
#define PRLH9 _prlh9   
__IO_EXTENDED IO_BYTE _prlla;
#define PRLLA _prlla   
__IO_EXTENDED IO_BYTE _prlha;
#define PRLHA _prlha   
__IO_EXTENDED IO_BYTE _prllb;
#define PRLLB _prllb   
__IO_EXTENDED IO_BYTE _prlhb;
#define PRLHB _prlhb   
__IO_EXTENDED IO_WORD _ipcp0;
#define IPCP0 _ipcp0   
__IO_EXTENDED IO_WORD _ipcp1;
#define IPCP1 _ipcp1   
__IO_EXTENDED IO_WORD _ipcp2;
#define IPCP2 _ipcp2   
__IO_EXTENDED IO_WORD _ipcp3;
#define IPCP3 _ipcp3   
__IO_EXTENDED IO_WORD _ipcp4;
#define IPCP4 _ipcp4   
__IO_EXTENDED IO_WORD _ipcp5;
#define IPCP5 _ipcp5   
__IO_EXTENDED IO_WORD _occp0;
#define OCCP0 _occp0   
__IO_EXTENDED IO_WORD _occp1;
#define OCCP1 _occp1   
__IO_EXTENDED IO_WORD _occp2;
#define OCCP2 _occp2   
__IO_EXTENDED IO_WORD _occp3;
#define OCCP3 _occp3   
__IO_EXTENDED IO_WORD _occp4;
#define OCCP4 _occp4   
__IO_EXTENDED IO_WORD _occp5;
#define OCCP5 _occp5   
__IO_EXTENDED IO_WORD _tmr0;
#define TMR0 _tmr0    /* Timer Reload Register */
__IO_EXTENDED IO_WORD _tmrlr0;
#define TMRLR0 _tmrlr0   
__IO_EXTENDED IO_WORD _tmr1;
#define TMR1 _tmr1   
__IO_EXTENDED IO_WORD _tmrlr1;
#define TMRLR1 _tmrlr1   
__IO_EXTENDED IO_WORD _tcdt;
#define TCDT _tcdt    /* IO Timer Data */
__IO_EXTENDED IO_BYTE _sgfr;
#define SGFR _sgfr    /* Sound Generator */
__IO_EXTENDED IO_BYTE _sgar;
#define SGAR _sgar   
__IO_EXTENDED IO_BYTE _sgdr;
#define SGDR _sgdr   
__IO_EXTENDED IO_BYTE _sgtr;
#define SGTR _sgtr   
/*
 *
 *    DESCRIPTION:  Watch clock sub-second register
 *
 *    AUTHOR:       HL, Fujitsu Mikroelektronik GmbH
 *
 *    HISTORY:    
 * Version 1.0      18.02.99: 
 *      - original version
 * Version 1.1      09.04.99: 
 *      - '_' symbol prefix added
 *
 */

#ifndef __WTBR_H
#define __WTBR_H

typedef struct{  
    IO_BYTE  wtbr0;
    IO_BYTE  wtbr1;
    IO_BYTE  wtbr2;
}WTBRSTR;

__IO_EXTENDED WTBRSTR _wtbr;

#define WTBR_WTBR0 _wtbr.wtbr0
#define WTBR_WTBR1 _wtbr.wtbr1
#define WTBR_WTBR2 _wtbr.wtbr2


#endif /*  __WTBR_H */
__IO_EXTENDED WTSRSTR _wtsr;  
#define WTSR _wtsr.byte
#define WTSR_S0 _wtsr.bit.S0
#define WTSR_S1 _wtsr.bit.S1
#define WTSR_S2 _wtsr.bit.S2
#define WTSR_S3 _wtsr.bit.S3
#define WTSR_S4 _wtsr.bit.S4
#define WTSR_S5 _wtsr.bit.S5
__IO_EXTENDED WTMRSTR _wtmr;  
#define WTMR _wtmr.byte
#define WTMR_M0 _wtmr.bit.M0
#define WTMR_M1 _wtmr.bit.M1
#define WTMR_M2 _wtmr.bit.M2
#define WTMR_M3 _wtmr.bit.M3
#define WTMR_M4 _wtmr.bit.M4
#define WTMR_M5 _wtmr.bit.M5
__IO_EXTENDED WTHRSTR _wthr;  
#define WTHR _wthr.byte
#define WTHR_H0 _wthr.bit.H0
#define WTHR_H1 _wthr.bit.H1
#define WTHR_H2 _wthr.bit.H2
#define WTHR_H3 _wthr.bit.H3
#define WTHR_H4 _wthr.bit.H4
__IO_EXTENDED IO_BYTE _pwc10;
#define PWC10 _pwc10    /*  Stepping motor controller 0 */
__IO_EXTENDED IO_BYTE _pwc20;
#define PWC20 _pwc20   
__IO_EXTENDED PWS10STR _pws10;  
#define PWS10 _pws10.byte
#define PWS10_M0 _pws10.bit.M0
#define PWS10_M1 _pws10.bit.M1
#define PWS10_M2 _pws10.bit.M2
#define PWS10_P0 _pws10.bit.P0
#define PWS10_P1 _pws10.bit.P1
#define PWS10_P2 _pws10.bit.P2
#define PWS10_M _pws10.bitc.M
#define PWS10_P _pws10.bitc.P
__IO_EXTENDED PWS20STR _pws20;  
#define PWS20 _pws20.byte
#define PWS20_M0 _pws20.bit.M0
#define PWS20_M1 _pws20.bit.M1
#define PWS20_M2 _pws20.bit.M2
#define PWS20_P0 _pws20.bit.P0
#define PWS20_P1 _pws20.bit.P1
#define PWS20_P2 _pws20.bit.P2
#define PWS20_BS _pws20.bit.BS
#define PWS20_M _pws20.bitc.M
#define PWS20_P _pws20.bitc.P
__IO_EXTENDED IO_BYTE _pwc11;
#define PWC11 _pwc11    /*  Stepping motor controller 1 */
__IO_EXTENDED IO_BYTE _pwc21;
#define PWC21 _pwc21   
__IO_EXTENDED PWS11STR _pws11;  
#define PWS11 _pws11.byte
#define PWS11_M0 _pws11.bit.M0
#define PWS11_M1 _pws11.bit.M1
#define PWS11_M2 _pws11.bit.M2
#define PWS11_P0 _pws11.bit.P0
#define PWS11_P1 _pws11.bit.P1
#define PWS11_P2 _pws11.bit.P2
#define PWS11_M _pws11.bitc.M
#define PWS11_P _pws11.bitc.P
__IO_EXTENDED PWS21STR _pws21;  
#define PWS21 _pws21.byte
#define PWS21_M0 _pws21.bit.M0
#define PWS21_M1 _pws21.bit.M1
#define PWS21_M2 _pws21.bit.M2
#define PWS21_P0 _pws21.bit.P0
#define PWS21_P1 _pws21.bit.P1
#define PWS21_P2 _pws21.bit.P2
#define PWS21_BS _pws21.bit.BS
#define PWS21_M _pws21.bitc.M
#define PWS21_P _pws21.bitc.P
__IO_EXTENDED IO_BYTE _pwc12;
#define PWC12 _pwc12    /*  Stepping motor controller 2 */
__IO_EXTENDED IO_BYTE _pwc22;
#define PWC22 _pwc22   
__IO_EXTENDED PWS12STR _pws12;  
#define PWS12 _pws12.byte
#define PWS12_M0 _pws12.bit.M0
#define PWS12_M1 _pws12.bit.M1
#define PWS12_M2 _pws12.bit.M2
#define PWS12_P0 _pws12.bit.P0
#define PWS12_P1 _pws12.bit.P1
#define PWS12_P2 _pws12.bit.P2
#define PWS12_M _pws12.bitc.M
#define PWS12_P _pws12.bitc.P
__IO_EXTENDED PWS22STR _pws22;  
#define PWS22 _pws22.byte
#define PWS22_M0 _pws22.bit.M0
#define PWS22_M1 _pws22.bit.M1
#define PWS22_M2 _pws22.bit.M2
#define PWS22_P0 _pws22.bit.P0
#define PWS22_P1 _pws22.bit.P1
#define PWS22_P2 _pws22.bit.P2
#define PWS22_BS _pws22.bit.BS
#define PWS22_M _pws22.bitc.M
#define PWS22_P _pws22.bitc.P
__IO_EXTENDED IO_BYTE _pwc13;
#define PWC13 _pwc13    /*  Stepping motor controller 3 */
__IO_EXTENDED IO_BYTE _pwc23;
#define PWC23 _pwc23   
__IO_EXTENDED PWS13STR _pws13;  
#define PWS13 _pws13.byte
#define PWS13_M0 _pws13.bit.M0
#define PWS13_M1 _pws13.bit.M1
#define PWS13_M2 _pws13.bit.M2
#define PWS13_P0 _pws13.bit.P0
#define PWS13_P1 _pws13.bit.P1
#define PWS13_P2 _pws13.bit.P2
#define PWS13_M _pws13.bitc.M
#define PWS13_P _pws13.bitc.P
__IO_EXTENDED PWS23STR _pws23;  
#define PWS23 _pws23.byte
#define PWS23_M0 _pws23.bit.M0
#define PWS23_M1 _pws23.bit.M1
#define PWS23_M2 _pws23.bit.M2
#define PWS23_P0 _pws23.bit.P0
#define PWS23_P1 _pws23.bit.P1
#define PWS23_P2 _pws23.bit.P2
#define PWS23_BS _pws23.bit.BS
#define PWS23_M _pws23.bitc.M
#define PWS23_P _pws23.bitc.P
__IO_EXTENDED IO_BYTE _padr0_m;
#define PADR0_M _padr0_m   
__IO_EXTENDED IO_BYTE _padr0_h;
#define PADR0_H _padr0_h   
__IO_EXTENDED IO_BYTE _padr1_m;
#define PADR1_M _padr1_m   
__IO_EXTENDED IO_BYTE _padr1_h;
#define PADR1_H _padr1_h   
/*
 * CANIO: control structures of CAN for LX-controllers
 *
 * Version: 1.0            23.01.99     HL
 *      - original version
 * Version: 2.0            26.02.99     HL
 *      - unsigned int replace by IO_WORD (FR/LX have diff int)
 *      - unsigned char replace by IO_BYTE
 */

#ifndef __CANSTR
#define __CANSTR

typedef struct
{
  union{   
    IO_WORD word;
    struct{
      IO_WORD BVAL0 :1;
      IO_WORD BVAL1 :1;
      IO_WORD BVAL2 :1;
      IO_WORD BVAL3 :1;
      IO_WORD BVAL4 :1;
      IO_WORD BVAL5 :1;
      IO_WORD BVAL6 :1;
      IO_WORD BVAL7 :1;
      IO_WORD BVAL8 :1;
      IO_WORD BVAL9 :1;
      IO_WORD BVAL10 :1;
      IO_WORD BVAL11 :1;
      IO_WORD BVAL12 :1;
      IO_WORD BVAL13 :1;
      IO_WORD BVAL14 :1;
      IO_WORD BVAL15 :1;
    } bit;
  } bvalr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD TREQ0 :1;
      IO_WORD TREQ1 :1;
      IO_WORD TREQ2 :1;
      IO_WORD TREQ3 :1;
      IO_WORD TREQ4 :1;
      IO_WORD TREQ5 :1;
      IO_WORD TREQ6 :1;
      IO_WORD TREQ7 :1;
      IO_WORD TREQ8 :1;
      IO_WORD TREQ9 :1;
      IO_WORD TREQ10 :1;
      IO_WORD TREQ11 :1;
      IO_WORD TREQ12 :1;
      IO_WORD TREQ13 :1;
      IO_WORD TREQ14 :1;
      IO_WORD TREQ15 :1;
    } bit;
  } treqr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD TCAN0 :1;
      IO_WORD TCAN1 :1;
      IO_WORD TCAN2 :1;
      IO_WORD TCAN3 :1;
      IO_WORD TCAN4 :1;
      IO_WORD TCAN5 :1;
      IO_WORD TCAN6 :1;
      IO_WORD TCAN7 :1;
      IO_WORD TCAN8 :1;
      IO_WORD TCAN9 :1;
      IO_WORD TCAN10 :1;
      IO_WORD TCAN11 :1;
      IO_WORD TCAN12 :1;
      IO_WORD TCAN13 :1;
      IO_WORD TCAN14 :1;
      IO_WORD TCAN15 :1;
    } bit;
  } tcanr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD TC0 :1;
      IO_WORD TC1 :1;
      IO_WORD TC2 :1;
      IO_WORD TC3 :1;
      IO_WORD TC4 :1;
      IO_WORD TC5 :1;
      IO_WORD TC6 :1;
      IO_WORD TC7 :1;
      IO_WORD TC8 :1;
      IO_WORD TC9 :1;
      IO_WORD TC10 :1;
      IO_WORD TC11 :1;
      IO_WORD TC12 :1;
      IO_WORD TC13 :1;
      IO_WORD TC14 :1;
      IO_WORD TC15 :1;
    } bit;
 } tcr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD RC0 :1;
      IO_WORD RC1 :1;
      IO_WORD RC2 :1;
      IO_WORD RC3 :1;
      IO_WORD RC4 :1;
      IO_WORD RC5 :1;
      IO_WORD RC6 :1;
      IO_WORD RC7 :1;
      IO_WORD RC8 :1;
      IO_WORD RC9 :1;
      IO_WORD RC10 :1;
      IO_WORD RC11 :1;
      IO_WORD RC12 :1;
      IO_WORD RC13 :1;
      IO_WORD RC14 :1;
      IO_WORD RC15 :1;
    } bit;
  } rcr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD RRTR0 :1;
      IO_WORD RRTR1 :1;
      IO_WORD RRTR2 :1;
      IO_WORD RRTR3 :1;
      IO_WORD RRTR4 :1;
      IO_WORD RRTR5 :1;
      IO_WORD RRTR6 :1;
      IO_WORD RRTR7 :1;
      IO_WORD RRTR8 :1;
      IO_WORD RRTR9 :1;
      IO_WORD RRTR10 :1;
      IO_WORD RRTR11 :1;
      IO_WORD RRTR12 :1;
      IO_WORD RRTR13 :1;
      IO_WORD RRTR14 :1;
      IO_WORD RRTR15 :1;
    } bit;
  } rrtrr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD ROVR0 :1;
      IO_WORD ROVR1 :1;
      IO_WORD ROVR2 :1;
      IO_WORD ROVR3 :1;
      IO_WORD ROVR4 :1;
      IO_WORD ROVR5 :1;
      IO_WORD ROVR6 :1;
      IO_WORD ROVR7 :1;
      IO_WORD ROVR8 :1;
      IO_WORD ROVR9 :1;
      IO_WORD ROVR10 :1;
      IO_WORD ROVR11 :1;
      IO_WORD ROVR12 :1;
      IO_WORD ROVR13 :1;
      IO_WORD ROVR14 :1;
      IO_WORD ROVR15 :1;
    } bit;
  } rovrr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD RIE0 :1;
      IO_WORD RIE1 :1;
      IO_WORD RIE2 :1;
      IO_WORD RIE3 :1;
      IO_WORD RIE4 :1;
      IO_WORD RIE5 :1;
      IO_WORD RIE6 :1;
      IO_WORD RIE7 :1;
      IO_WORD RIE8 :1;
      IO_WORD RIE9 :1;
      IO_WORD RIE10 :1;
      IO_WORD RIE11 :1;
      IO_WORD RIE12 :1;
      IO_WORD RIE13 :1;
      IO_WORD RIE14 :1;
      IO_WORD RIE15 :1;
    } bit;
  } rier;
} CANLSTR;

typedef struct
{
  union{  
    IO_WORD word;
      struct{
      IO_WORD HALT :1;
      IO_WORD      :1;
      IO_WORD NIE  :1;
      IO_WORD      :1;
      IO_WORD      :1;
      IO_WORD      :1;
      IO_WORD  	:1;
      IO_WORD TOE 	:1;
      IO_WORD NS0 	:1;
      IO_WORD NS1 	:1;
      IO_WORD NT 	:1;
      IO_WORD  	:1;
      IO_WORD  	:1;
      IO_WORD  	:1;
      IO_WORD RS 	:1;
      IO_WORD TS 	:1;
    }bit;
    struct{
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD 		:1;
      IO_WORD NS 	:2;
    }bitc;
  }csr;
  union{  
    IO_WORD word;
    IO_WORD byte;
    struct{
      IO_WORD MBP0 :1;
      IO_WORD MBP1 :1;
      IO_WORD MBP2 :1;
      IO_WORD MBP3 :1;
      IO_WORD      :1;
      IO_WORD RCE  :1;
      IO_WORD TCE  :1;
      IO_WORD NTE  :1;
    } bit;
    struct{
      IO_WORD MBP  :4;
    } bitc;
  } leir;
  union{  
    IO_WORD word;
    struct{
      IO_WORD REC0 :1;
      IO_WORD REC1 :1;
      IO_WORD REC2 :1;
      IO_WORD REC3 :1;
      IO_WORD REC4 :1;
      IO_WORD REC5 :1;
      IO_WORD REC6 :1;
      IO_WORD REC7 :1;
      IO_WORD TEC0 :1;
      IO_WORD TEC1 :1;
      IO_WORD TEC2 :1;
      IO_WORD TEC3 :1;
      IO_WORD TEC4 :1;
      IO_WORD TEC5 :1;
      IO_WORD TEC6 :1;
      IO_WORD TEC7 :1;
    }bit;
    struct{
      IO_WORD REC :8;
      IO_WORD TEC :8;
    }bitc;
  }rtec;
  union{  
    IO_WORD word;
    struct{
      IO_WORD PSC0 :1;
      IO_WORD PSC1 :1;
      IO_WORD PSC2 :1;
      IO_WORD PSC3 :1;
      IO_WORD PSC4 :1;
      IO_WORD PSC5 :1;
      IO_WORD RSJ0 :1;
      IO_WORD RSJ1 :1;
      IO_WORD TS10 :1;
      IO_WORD TS11 :1;
      IO_WORD TS12 :1;
      IO_WORD TS13 :1;
      IO_WORD TS20 :1;
      IO_WORD TS21 :1;
      IO_WORD TS22 :1;
      IO_WORD      :1;
    } bit;
    struct{
      IO_WORD PSC :6;
      IO_WORD RSJ :2;
      IO_WORD TS1 :4;
      IO_WORD TS2 :3;
    } bitc;
  } btr;
  union{  
    IO_WORD word;
      struct{
      IO_WORD IDE0 :1;
      IO_WORD IDE1 :1;
      IO_WORD IDE2 :1;
      IO_WORD IDE3 :1;
      IO_WORD IDE4 :1;
      IO_WORD IDE5 :1;
      IO_WORD IDE6 :1;
      IO_WORD IDE7 :1;
      IO_WORD IDE8 :1;
      IO_WORD IDE9 :1;
      IO_WORD IDE10 :1;
      IO_WORD IDE11 :1;
      IO_WORD IDE12 :1;
      IO_WORD IDE13 :1;
      IO_WORD IDE14 :1;
      IO_WORD IDE15 :1;
    } bit;
  } ider;
  union{  
    IO_WORD word;
    struct{
      IO_WORD TRTR0 :1;
      IO_WORD TRTR1 :1;
      IO_WORD TRTR2 :1;
      IO_WORD TRTR3 :1;
      IO_WORD TRTR4 :1;
      IO_WORD TRTR5 :1;
      IO_WORD TRTR6 :1;
      IO_WORD TRTR7 :1;
      IO_WORD TRTR8 :1;
      IO_WORD TRTR9 :1;
      IO_WORD TRTR10 :1;
      IO_WORD TRTR11 :1;
      IO_WORD TRTR12 :1;
      IO_WORD TRTR13 :1;
      IO_WORD TRTR14 :1;
      IO_WORD TRTR15 :1;
    } bit;
  } trtrr;
  union{  
    IO_WORD word;
    struct{
      IO_WORD RFWT0 :1;
      IO_WORD RFWT1 :1;
      IO_WORD RFWT2 :1;
      IO_WORD RFWT3 :1;
      IO_WORD RFWT4 :1;
      IO_WORD RFWT5 :1;
      IO_WORD RFWT6 :1;
      IO_WORD RFWT7 :1;
      IO_WORD RFWT8 :1;
      IO_WORD RFWT9 :1;
      IO_WORD RFWT10 :1;
      IO_WORD RFWT11 :1;
      IO_WORD RFWT12 :1;
      IO_WORD RFWT13 :1;
      IO_WORD RFWT14 :1;
      IO_WORD RFWT15 :1;
    } bit;
  } rfwtr;
  union{  
    IO_WORD word;
    struct{
    IO_WORD TIE0 :1;
    IO_WORD TIE1 :1;
    IO_WORD TIE2 :1;
    IO_WORD TIE3 :1;
    IO_WORD TIE4 :1;
    IO_WORD TIE5 :1;
    IO_WORD TIE6 :1;
    IO_WORD TIE7 :1;
    IO_WORD TIE8 :1;
    IO_WORD TIE9 :1;
    IO_WORD TIE10 :1;
    IO_WORD TIE11 :1;
    IO_WORD TIE12 :1;
    IO_WORD TIE13 :1;
    IO_WORD TIE14 :1;
    IO_WORD TIE15 :1;
  } bit;
 } tier;
  union{
    unsigned long     dword;
    struct{
      IO_WORD    AMS00:1;
      IO_WORD    AMS01:1;
      IO_WORD    AMS10:1;
      IO_WORD    AMS11:1;
      IO_WORD    AMS20:1;
      IO_WORD    AMS21:1;
      IO_WORD    AMS30:1;
      IO_WORD    AMS31:1;
      IO_WORD    AMS40:1;
      IO_WORD    AMS41:1;
      IO_WORD    AMS50:1;
      IO_WORD    AMS51:1;
      IO_WORD    AMS60:1;
      IO_WORD    AMS61:1;
      IO_WORD    AMS70:1;
      IO_WORD    AMS71:1;
      IO_WORD    AMS80:1;
      IO_WORD    AMS81:1;
      IO_WORD    AMS90:1;
      IO_WORD    AMS91:1;
      IO_WORD    AMS100:1;
      IO_WORD    AMS101:1;
      IO_WORD    AMS110:1;
      IO_WORD    AMS111:1;
      IO_WORD    AMS120:1;
      IO_WORD    AMS121:1;
      IO_WORD    AMS130:1;
      IO_WORD    AMS131:1;
      IO_WORD    AMS140:1;
      IO_WORD    AMS141:1;
      IO_WORD    AMS150:1;
      IO_WORD    AMS151:1;
    }bit;
    struct{
      IO_WORD    AMS0:2;
      IO_WORD    AMS1:2;
      IO_WORD    AMS2:2;
      IO_WORD    AMS3:2;
      IO_WORD    AMS4:2;
      IO_WORD    AMS5:2;
      IO_WORD    AMS6:2;
      IO_WORD    AMS7:2;
      IO_WORD    AMS8:2;
      IO_WORD    AMS9:2;
      IO_WORD    AMS10:2;
      IO_WORD    AMS11:2;
      IO_WORD    AMS12:2;
      IO_WORD    AMS13:2;
      IO_WORD    AMS14:2;
      IO_WORD    AMS15:2;
    } bitc;
  } amsr;
  union {
    unsigned long   dword;
    unsigned short  word;
    struct {
        IO_WORD AM21 :1;
        IO_WORD AM22 :1;
        IO_WORD AM23 :1;
        IO_WORD AM24 :1;
        IO_WORD AM25 :1;
        IO_WORD AM26 :1;
        IO_WORD AM27 :1;
        IO_WORD AM28 :1;

        IO_WORD AM13 :1;
        IO_WORD AM14 :1;
        IO_WORD AM15 :1;
        IO_WORD AM16 :1;
        IO_WORD AM17 :1;
        IO_WORD AM18 :1;
        IO_WORD AM19 :1;
        IO_WORD AM20 :1;

        IO_WORD AM5 :1;
        IO_WORD AM6 :1;
        IO_WORD AM7 :1;
        IO_WORD AM8 :1;
        IO_WORD AM9 :1;
        IO_WORD AM10 :1;
        IO_WORD AM11 :1;
        IO_WORD AM12 :1;

        IO_WORD      :3;
        IO_WORD AM0 :1;
        IO_WORD AM1 :1;
        IO_WORD AM2 :1;
        IO_WORD AM3 :1;
        IO_WORD AM4 :1;
    } bit_ext;
    struct {
        IO_WORD AM3 :1;
        IO_WORD AM4 :1;
        IO_WORD AM5 :1;
        IO_WORD AM6 :1;
        IO_WORD AM7 :1;
        IO_WORD AM8 :1;
        IO_WORD AM9 :1;
        IO_WORD AM10 :1;

        IO_WORD     :5;
        IO_WORD AM0 :1;
        IO_WORD AM1 :1;
        IO_WORD AM2 :1;
    } bit_std;
    struct {
        IO_WORD AM21_28    : 8;
        IO_WORD AM13_20    : 8;
        IO_WORD AM5_12     : 8;
        IO_WORD unused     : 3;            /* unused bits */
        IO_WORD AM0_4      : 5;
    } bitc_ext;
    struct {
        IO_WORD AM3_10 : 8;
        IO_WORD unused : 5;                /* unused bits   */
        IO_WORD AM0_2  : 3;
        /*IO_WORD upper    :16;                /* unused bits */
    } bitc_std;
  } amr[2];
} CANHSTR;

typedef struct
{
    IO_WORD ram[16];
    union {
    unsigned long   dword;
    unsigned short  word;
    struct {
        const IO_WORD ID21 :1;
        const IO_WORD ID22 :1;
        const IO_WORD ID23 :1;
        const IO_WORD ID24 :1;
        const IO_WORD ID25 :1;
        const IO_WORD ID26 :1;
        const IO_WORD ID27 :1;
        const IO_WORD ID28 :1;

        const IO_WORD ID13 :1;
        const IO_WORD ID14 :1;
        const IO_WORD ID15 :1;
        const IO_WORD ID16 :1;
        const IO_WORD ID17 :1;
        const IO_WORD ID18 :1;
        const IO_WORD ID19 :1;
        const IO_WORD ID20 :1;

        const IO_WORD ID5 :1;
        const IO_WORD ID6 :1;
        const IO_WORD ID7 :1;
        const IO_WORD ID8 :1;
        const IO_WORD ID9 :1;
        const IO_WORD ID10 :1;
        const IO_WORD ID11 :1;
        const IO_WORD ID12 :1;

        const IO_WORD     :3;
        const IO_WORD ID0 :1;
        const IO_WORD ID1 :1;
        const IO_WORD ID2 :1;
        const IO_WORD ID3 :1;
        const IO_WORD ID4 :1;
    } bit_ext;
    struct {
        const IO_WORD ID3 :1;
        const IO_WORD ID4 :1;
        const IO_WORD ID5 :1;
        const IO_WORD ID6 :1;
        const IO_WORD ID7 :1;
        const IO_WORD ID8 :1;
        const IO_WORD ID9 :1;
        const IO_WORD ID10:1;

        const IO_WORD ID  :5;
        const IO_WORD ID0 :1;
        const IO_WORD ID1 :1;
        const IO_WORD ID2 :1;
    } bit_std;
    struct {
        const IO_WORD ID21_28 : 8;
        const IO_WORD ID13_20 : 8;
        const IO_WORD ID5_12  : 8;
        const IO_WORD unused  : 3;         /* unused bits */
        const IO_WORD ID0_4   : 5;
    } bitc_ext;
    struct {
        const IO_WORD ID3_10  : 8;
        const IO_WORD unused  : 5;             /* unused bits   */
        const IO_WORD ID0_2   : 3;
    } bitc_std;
  } idr[16];
  union{
    IO_WORD         word;
    IO_BYTE         byte;
    struct {
        IO_WORD     DLC0:1;
        IO_WORD     DLC1:1;
        IO_WORD     DLC2:1;
        IO_WORD     DLC3:1;
    } bit;
    struct {
        IO_WORD     DLC:4;
    } bitc;
  } dlcr[16];
  union{
          unsigned long dwords [2];
          long          longs  [2];
          IO_WORD  words  [4];
          int           ints   [4];
    const IO_BYTE bytes  [8]; /* because of word access*/
    const char          chars  [8]; /* because of word access*/
          float         floats [2];
          double        adouble;
  }dtr[16];
} CANMSTR;

#endif	/* CANSTR */
/*
 * CANIO: control structures of double CAN for LX-controllers
 *
 * Version: 1.0            23.01.99     FMG, HL
 *      - original version
 * Version: 1.1            27.01.99     FMG, tka 
 *      - idrx0 changed to IDRX0
 * Version: 1.2            11.02.99     FMG, HL
 *      - "extern" declaration changed to predefined macros of
 *        IO-Wizard, requires IO-Wizard 1.7 or later
 *      - DRT1_LWPTR changed to DTR1_DWPTR macro
 */

#ifndef __CANMAC
#define __CANMAC

__IO_EXTERN __io CANLSTR _canl0;
__IO_EXTERN __io CANLSTR _canl1;

/* CAN0 macros */
#define BVALR0           _canl0.bvalr.word
#define BVALR0_BVAL0     _canl0.bvalr.bit.BVAL0
#define BVALR0_BVAL1     _canl0.bvalr.bit.BVAL1
#define BVALR0_BVAL2     _canl0.bvalr.bit.BVAL2
#define BVALR0_BVAL3     _canl0.bvalr.bit.BVAL3
#define BVALR0_BVAL4     _canl0.bvalr.bit.BVAL4
#define BVALR0_BVAL5     _canl0.bvalr.bit.BVAL5
#define BVALR0_BVAL6     _canl0.bvalr.bit.BVAL6
#define BVALR0_BVAL7     _canl0.bvalr.bit.BVAL7
#define BVALR0_BVAL8     _canl0.bvalr.bit.BVAL8
#define BVALR0_BVAL9     _canl0.bvalr.bit.BVAL9
#define BVALR0_BVAL10    _canl0.bvalr.bit.BVAL10
#define BVALR0_BVAL11    _canl0.bvalr.bit.BVAL11
#define BVALR0_BVAL12    _canl0.bvalr.bit.BVAL12
#define BVALR0_BVAL13    _canl0.bvalr.bit.BVAL13
#define BVALR0_BVAL14    _canl0.bvalr.bit.BVAL14
#define BVALR0_BVAL15    _canl0.bvalr.bit.BVAL15

#define TREQR0           _canl0.treqr.word
#define TREQR0_TREQ0     _canl0.treqr.bit.TREQ0
#define TREQR0_TREQ1     _canl0.treqr.bit.TREQ1
#define TREQR0_TREQ2     _canl0.treqr.bit.TREQ2
#define TREQR0_TREQ3     _canl0.treqr.bit.TREQ3
#define TREQR0_TREQ4     _canl0.treqr.bit.TREQ4
#define TREQR0_TREQ5     _canl0.treqr.bit.TREQ5
#define TREQR0_TREQ6     _canl0.treqr.bit.TREQ6
#define TREQR0_TREQ7     _canl0.treqr.bit.TREQ7
#define TREQR0_TREQ8     _canl0.treqr.bit.TREQ8
#define TREQR0_TREQ9     _canl0.treqr.bit.TREQ9
#define TREQR0_TREQ10    _canl0.treqr.bit.TREQ10
#define TREQR0_TREQ11    _canl0.treqr.bit.TREQ11
#define TREQR0_TREQ12    _canl0.treqr.bit.TREQ12
#define TREQR0_TREQ13    _canl0.treqr.bit.TREQ13
#define TREQR0_TREQ14    _canl0.treqr.bit.TREQ14
#define TREQR0_TREQ15    _canl0.treqr.bit.TREQ15

#define TCANR0           _canl0.tcanr.word
#define TCANR0_TCAN0     _canl0.tcanr.bit.TCAN0
#define TCANR0_TCAN1     _canl0.tcanr.bit.TCAN1
#define TCANR0_TCAN2     _canl0.tcanr.bit.TCAN2
#define TCANR0_TCAN3     _canl0.tcanr.bit.TCAN3
#define TCANR0_TCAN4     _canl0.tcanr.bit.TCAN4
#define TCANR0_TCAN5     _canl0.tcanr.bit.TCAN5
#define TCANR0_TCAN6     _canl0.tcanr.bit.TCAN6
#define TCANR0_TCAN7     _canl0.tcanr.bit.TCAN7
#define TCANR0_TCAN8     _canl0.tcanr.bit.TCAN8
#define TCANR0_TCAN9     _canl0.tcanr.bit.TCAN9
#define TCANR0_TCAN10    _canl0.tcanr.bit.TCAN10
#define TCANR0_TCAN11    _canl0.tcanr.bit.TCAN11
#define TCANR0_TCAN12    _canl0.tcanr.bit.TCAN12
#define TCANR0_TCAN13    _canl0.tcanr.bit.TCAN13
#define TCANR0_TCAN14    _canl0.tcanr.bit.TCAN14
#define TCANR0_TCAN15    _canl0.tcanr.bit.TCAN15

#define TCR0             _canl0.tcr.word
#define TCR0_TC0         _canl0.tcr.bit.TC0
#define TCR0_TC1         _canl0.tcr.bit.TC1
#define TCR0_TC2         _canl0.tcr.bit.TC2
#define TCR0_TC3         _canl0.tcr.bit.TC3
#define TCR0_TC4         _canl0.tcr.bit.TC4
#define TCR0_TC5         _canl0.tcr.bit.TC5
#define TCR0_TC6         _canl0.tcr.bit.TC6
#define TCR0_TC7         _canl0.tcr.bit.TC7
#define TCR0_TC8         _canl0.tcr.bit.TC8
#define TCR0_TC9         _canl0.tcr.bit.TC9
#define TCR0_TC10        _canl0.tcr.bit.TC10
#define TCR0_TC11        _canl0.tcr.bit.TC11
#define TCR0_TC12        _canl0.tcr.bit.TC12
#define TCR0_TC13        _canl0.tcr.bit.TC13
#define TCR0_TC14        _canl0.tcr.bit.TC14
#define TCR0_TC15        _canl0.tcr.bit.TC15

#define RCR0             _canl0.rcr.word
#define RCR0_RC0         _canl0.rcr.bit.RC0
#define RCR0_RC1         _canl0.rcr.bit.RC1
#define RCR0_RC2         _canl0.rcr.bit.RC2
#define RCR0_RC3         _canl0.rcr.bit.RC3
#define RCR0_RC4         _canl0.rcr.bit.RC4
#define RCR0_RC5         _canl0.rcr.bit.RC5
#define RCR0_RC6         _canl0.rcr.bit.RC6
#define RCR0_RC7         _canl0.rcr.bit.RC7
#define RCR0_RC8         _canl0.rcr.bit.RC8
#define RCR0_RC9         _canl0.rcr.bit.RC9
#define RCR0_RC10        _canl0.rcr.bit.RC10
#define RCR0_RC11        _canl0.rcr.bit.RC11
#define RCR0_RC12        _canl0.rcr.bit.RC12
#define RCR0_RC13        _canl0.rcr.bit.RC13
#define RCR0_RC14        _canl0.rcr.bit.RC14
#define RCR0_RC15        _canl0.rcr.bit.RC15

#define RRTRR0           _canl0.rrtrr.word
#define RRTRR0_RRTR0     _canl0.rrtrr.bit.RRTR0
#define RRTRR0_RRTR1     _canl0.rrtrr.bit.RRTR1
#define RRTRR0_RRTR2     _canl0.rrtrr.bit.RRTR2
#define RRTRR0_RRTR3     _canl0.rrtrr.bit.RRTR3
#define RRTRR0_RRTR4     _canl0.rrtrr.bit.RRTR4
#define RRTRR0_RRTR5     _canl0.rrtrr.bit.RRTR5
#define RRTRR0_RRTR6     _canl0.rrtrr.bit.RRTR6
#define RRTRR0_RRTR7     _canl0.rrtrr.bit.RRTR7
#define RRTRR0_RRTR8     _canl0.rrtrr.bit.RRTR8
#define RRTRR0_RRTR9     _canl0.rrtrr.bit.RRTR9
#define RRTRR0_RRTR10    _canl0.rrtrr.bit.RRTR10
#define RRTRR0_RRTR11    _canl0.rrtrr.bit.RRTR11
#define RRTRR0_RRTR12    _canl0.rrtrr.bit.RRTR12
#define RRTRR0_RRTR13    _canl0.rrtrr.bit.RRTR13
#define RRTRR0_RRTR14    _canl0.rrtrr.bit.RRTR14
#define RRTRR0_RRTR15    _canl0.rrtrr.bit.RRTR15

#define ROVRR0           _canl0.rovrr.word
#define ROVRR0_ROVR0     _canl0.rovrr.bit.ROVR0
#define ROVRR0_ROVR1     _canl0.rovrr.bit.ROVR1
#define ROVRR0_ROVR2     _canl0.rovrr.bit.ROVR2
#define ROVRR0_ROVR3     _canl0.rovrr.bit.ROVR3
#define ROVRR0_ROVR4     _canl0.rovrr.bit.ROVR4
#define ROVRR0_ROVR5     _canl0.rovrr.bit.ROVR5
#define ROVRR0_ROVR6     _canl0.rovrr.bit.ROVR6
#define ROVRR0_ROVR7     _canl0.rovrr.bit.ROVR7
#define ROVRR0_ROVR8     _canl0.rovrr.bit.ROVR8
#define ROVRR0_ROVR9     _canl0.rovrr.bit.ROVR9
#define ROVRR0_ROVR10    _canl0.rovrr.bit.ROVR10
#define ROVRR0_ROVR11    _canl0.rovrr.bit.ROVR11
#define ROVRR0_ROVR12    _canl0.rovrr.bit.ROVR12
#define ROVRR0_ROVR13    _canl0.rovrr.bit.ROVR13
#define ROVRR0_ROVR14    _canl0.rovrr.bit.ROVR14
#define ROVRR0_ROVR15    _canl0.rovrr.bit.ROVR15

#define RIER0            _canl0.rier.word
#define RIER0_RIE0       _canl0.rier.bit.RIE0
#define RIER0_RIE1       _canl0.rier.bit.RIE1
#define RIER0_RIE2       _canl0.rier.bit.RIE2
#define RIER0_RIE3       _canl0.rier.bit.RIE3
#define RIER0_RIE4       _canl0.rier.bit.RIE4
#define RIER0_RIE5       _canl0.rier.bit.RIE5
#define RIER0_RIE6       _canl0.rier.bit.RIE6
#define RIER0_RIE7       _canl0.rier.bit.RIE7
#define RIER0_RIE8       _canl0.rier.bit.RIE8
#define RIER0_RIE9       _canl0.rier.bit.RIE9
#define RIER0_RIE10      _canl0.rier.bit.RIE10
#define RIER0_RIE11      _canl0.rier.bit.RIE11
#define RIER0_RIE12      _canl0.rier.bit.RIE12
#define RIER0_RIE13      _canl0.rier.bit.RIE13
#define RIER0_RIE14      _canl0.rier.bit.RIE14
#define RIER0_RIE15      _canl0.rier.bit.RIE15

/* CAN1 macros */
#define BVALR1           _canl1.bvalr.word
#define BVALR1_BVAL0     _canl1.bvalr.bit.BVAL0
#define BVALR1_BVAL1     _canl1.bvalr.bit.BVAL1
#define BVALR1_BVAL2     _canl1.bvalr.bit.BVAL2
#define BVALR1_BVAL3     _canl1.bvalr.bit.BVAL3
#define BVALR1_BVAL4     _canl1.bvalr.bit.BVAL4
#define BVALR1_BVAL5     _canl1.bvalr.bit.BVAL5
#define BVALR1_BVAL6     _canl1.bvalr.bit.BVAL6
#define BVALR1_BVAL7     _canl1.bvalr.bit.BVAL7
#define BVALR1_BVAL8     _canl1.bvalr.bit.BVAL8
#define BVALR1_BVAL9     _canl1.bvalr.bit.BVAL9
#define BVALR1_BVAL10    _canl1.bvalr.bit.BVAL10
#define BVALR1_BVAL11    _canl1.bvalr.bit.BVAL11
#define BVALR1_BVAL12    _canl1.bvalr.bit.BVAL12
#define BVALR1_BVAL13    _canl1.bvalr.bit.BVAL13
#define BVALR1_BVAL14    _canl1.bvalr.bit.BVAL14
#define BVALR1_BVAL15    _canl1.bvalr.bit.BVAL15

#define TREQR1           _canl1.treqr.word
#define TREQR1_TREQ0     _canl1.treqr.bit.TREQ0
#define TREQR1_TREQ1     _canl1.treqr.bit.TREQ1
#define TREQR1_TREQ2     _canl1.treqr.bit.TREQ2
#define TREQR1_TREQ3     _canl1.treqr.bit.TREQ3
#define TREQR1_TREQ4     _canl1.treqr.bit.TREQ4
#define TREQR1_TREQ5     _canl1.treqr.bit.TREQ5
#define TREQR1_TREQ6     _canl1.treqr.bit.TREQ6
#define TREQR1_TREQ7     _canl1.treqr.bit.TREQ7
#define TREQR1_TREQ8     _canl1.treqr.bit.TREQ8
#define TREQR1_TREQ9     _canl1.treqr.bit.TREQ9
#define TREQR1_TREQ10    _canl1.treqr.bit.TREQ10
#define TREQR1_TREQ11    _canl1.treqr.bit.TREQ11
#define TREQR1_TREQ12    _canl1.treqr.bit.TREQ12
#define TREQR1_TREQ13    _canl1.treqr.bit.TREQ13
#define TREQR1_TREQ14    _canl1.treqr.bit.TREQ14
#define TREQR1_TREQ15    _canl1.treqr.bit.TREQ15

#define TCANR1           _canl1.tcanr.word
#define TCANR1_TCAN0     _canl1.tcanr.bit.TCAN0
#define TCANR1_TCAN1     _canl1.tcanr.bit.TCAN1
#define TCANR1_TCAN2     _canl1.tcanr.bit.TCAN2
#define TCANR1_TCAN3     _canl1.tcanr.bit.TCAN3
#define TCANR1_TCAN4     _canl1.tcanr.bit.TCAN4
#define TCANR1_TCAN5     _canl1.tcanr.bit.TCAN5
#define TCANR1_TCAN6     _canl1.tcanr.bit.TCAN6
#define TCANR1_TCAN7     _canl1.tcanr.bit.TCAN7
#define TCANR1_TCAN8     _canl1.tcanr.bit.TCAN8
#define TCANR1_TCAN9     _canl1.tcanr.bit.TCAN9
#define TCANR1_TCAN10    _canl1.tcanr.bit.TCAN10
#define TCANR1_TCAN11    _canl1.tcanr.bit.TCAN11
#define TCANR1_TCAN12    _canl1.tcanr.bit.TCAN12
#define TCANR1_TCAN13    _canl1.tcanr.bit.TCAN13
#define TCANR1_TCAN14    _canl1.tcanr.bit.TCAN14
#define TCANR1_TCAN15    _canl1.tcanr.bit.TCAN15

#define TCR1             _canl1.tcr.word
#define TCR1_TC0         _canl1.tcr.bit.TC0
#define TCR1_TC1         _canl1.tcr.bit.TC1
#define TCR1_TC2         _canl1.tcr.bit.TC2
#define TCR1_TC3         _canl1.tcr.bit.TC3
#define TCR1_TC4         _canl1.tcr.bit.TC4
#define TCR1_TC5         _canl1.tcr.bit.TC5
#define TCR1_TC6         _canl1.tcr.bit.TC6
#define TCR1_TC7         _canl1.tcr.bit.TC7
#define TCR1_TC8         _canl1.tcr.bit.TC8
#define TCR1_TC9         _canl1.tcr.bit.TC9
#define TCR1_TC10        _canl1.tcr.bit.TC10
#define TCR1_TC11        _canl1.tcr.bit.TC11
#define TCR1_TC12        _canl1.tcr.bit.TC12
#define TCR1_TC13        _canl1.tcr.bit.TC13
#define TCR1_TC14        _canl1.tcr.bit.TC14
#define TCR1_TC15        _canl1.tcr.bit.TC15

#define RCR1             _canl1.rcr.word
#define RCR1_RC0         _canl1.rcr.bit.RC0
#define RCR1_RC1         _canl1.rcr.bit.RC1
#define RCR1_RC2         _canl1.rcr.bit.RC2
#define RCR1_RC3         _canl1.rcr.bit.RC3
#define RCR1_RC4         _canl1.rcr.bit.RC4
#define RCR1_RC5         _canl1.rcr.bit.RC5
#define RCR1_RC6         _canl1.rcr.bit.RC6
#define RCR1_RC7         _canl1.rcr.bit.RC7
#define RCR1_RC8         _canl1.rcr.bit.RC8
#define RCR1_RC9         _canl1.rcr.bit.RC9
#define RCR1_RC10        _canl1.rcr.bit.RC10
#define RCR1_RC11        _canl1.rcr.bit.RC11
#define RCR1_RC12        _canl1.rcr.bit.RC12
#define RCR1_RC13        _canl1.rcr.bit.RC13
#define RCR1_RC14        _canl1.rcr.bit.RC14
#define RCR1_RC15        _canl1.rcr.bit.RC15

#define RRTRR1           _canl1.rrtrr.word
#define RRTRR1_RRTR0     _canl1.rrtrr.bit.RRTR0
#define RRTRR1_RRTR1     _canl1.rrtrr.bit.RRTR1
#define RRTRR1_RRTR2     _canl1.rrtrr.bit.RRTR2
#define RRTRR1_RRTR3     _canl1.rrtrr.bit.RRTR3
#define RRTRR1_RRTR4     _canl1.rrtrr.bit.RRTR4
#define RRTRR1_RRTR5     _canl1.rrtrr.bit.RRTR5
#define RRTRR1_RRTR6     _canl1.rrtrr.bit.RRTR6
#define RRTRR1_RRTR7     _canl1.rrtrr.bit.RRTR7
#define RRTRR1_RRTR8     _canl1.rrtrr.bit.RRTR8
#define RRTRR1_RRTR9     _canl1.rrtrr.bit.RRTR9
#define RRTRR1_RRTR10    _canl1.rrtrr.bit.RRTR10
#define RRTRR1_RRTR11    _canl1.rrtrr.bit.RRTR11
#define RRTRR1_RRTR12    _canl1.rrtrr.bit.RRTR12
#define RRTRR1_RRTR13    _canl1.rrtrr.bit.RRTR13
#define RRTRR1_RRTR14    _canl1.rrtrr.bit.RRTR14
#define RRTRR1_RRTR15    _canl1.rrtrr.bit.RRTR15

#define ROVRR1           _canl1.rovrr.word
#define ROVRR1_ROVR0     _canl1.rovrr.bit.ROVR0
#define ROVRR1_ROVR1     _canl1.rovrr.bit.ROVR1
#define ROVRR1_ROVR2     _canl1.rovrr.bit.ROVR2
#define ROVRR1_ROVR3     _canl1.rovrr.bit.ROVR3
#define ROVRR1_ROVR4     _canl1.rovrr.bit.ROVR4
#define ROVRR1_ROVR5     _canl1.rovrr.bit.ROVR5
#define ROVRR1_ROVR6     _canl1.rovrr.bit.ROVR6
#define ROVRR1_ROVR7     _canl1.rovrr.bit.ROVR7
#define ROVRR1_ROVR8     _canl1.rovrr.bit.ROVR8
#define ROVRR1_ROVR9     _canl1.rovrr.bit.ROVR9
#define ROVRR1_ROVR10    _canl1.rovrr.bit.ROVR10
#define ROVRR1_ROVR11    _canl1.rovrr.bit.ROVR11
#define ROVRR1_ROVR12    _canl1.rovrr.bit.ROVR12
#define ROVRR1_ROVR13    _canl1.rovrr.bit.ROVR13
#define ROVRR1_ROVR14    _canl1.rovrr.bit.ROVR14
#define ROVRR1_ROVR15    _canl1.rovrr.bit.ROVR15

#define RIER1            _canl1.rier.word
#define RIER1_RIE0       _canl1.rier.bit.RIE0
#define RIER1_RIE1       _canl1.rier.bit.RIE1
#define RIER1_RIE2       _canl1.rier.bit.RIE2
#define RIER1_RIE3       _canl1.rier.bit.RIE3
#define RIER1_RIE4       _canl1.rier.bit.RIE4
#define RIER1_RIE5       _canl1.rier.bit.RIE5
#define RIER1_RIE6       _canl1.rier.bit.RIE6
#define RIER1_RIE7       _canl1.rier.bit.RIE7
#define RIER1_RIE8       _canl1.rier.bit.RIE8
#define RIER1_RIE9       _canl1.rier.bit.RIE9
#define RIER1_RIE10      _canl1.rier.bit.RIE10
#define RIER1_RIE11      _canl1.rier.bit.RIE11
#define RIER1_RIE12      _canl1.rier.bit.RIE12
#define RIER1_RIE13      _canl1.rier.bit.RIE13
#define RIER1_RIE14      _canl1.rier.bit.RIE14
#define RIER1_RIE15      _canl1.rier.bit.RIE15

__IO_EXTENDED CANHSTR _canh0;
__IO_EXTENDED CANHSTR _canh1;

/* CAN0 macros */
#define CSR0             _canh0.csr.word
#define CSR0_HALT        _canh0.csr.bit.HALT
#define CSR0_NIE         _canh0.csr.bit.NIE
#define CSR0_TOE         _canh0.csr.bit.TOE
#define CSR0_NS0         _canh0.csr.bit.NS0
#define CSR0_NS1         _canh0.csr.bit.NS1
#define CSR0_NT          _canh0.csr.bit.NT
#define CSR0_RS          _canh0.csr.bit.RS
#define CSR0_TS          _canh0.csr.bit.TS
#define CSR0_NS          _canh0.csr.bitc.NS

#define LEIR0            _canh0.leir.byte
#define LEIR0_MBP0       _canh0.leir.bit.MBP0
#define LEIR0_MBP1       _canh0.leir.bit.MBP1
#define LEIR0_MBP2       _canh0.leir.bit.MBP2
#define LEIR0_MBP3       _canh0.leir.bit.MBP3
#define LEIR0_RCE        _canh0.leir.bit.RCE
#define LEIR0_TCE        _canh0.leir.bit.TCE
#define LEIR0_NTE        _canh0.leir.bit.NTE
#define LEIR0_MBP        _canh0.leir.bitc.MBP

#define RTEC0            _canh0.rtec.word
#define RTEC0_REC0       _canh0.rtec.bit.REC0
#define RTEC0_REC1       _canh0.rtec.bit.REC1
#define RTEC0_REC2       _canh0.rtec.bit.REC2
#define RTEC0_REC3       _canh0.rtec.bit.REC3
#define RTEC0_REC4       _canh0.rtec.bit.REC4
#define RTEC0_REC5       _canh0.rtec.bit.REC5
#define RTEC0_REC6       _canh0.rtec.bit.REC6
#define RTEC0_REC7       _canh0.rtec.bit.REC7
#define RTEC0_TEC0       _canh0.rtec.bit.TEC0
#define RTEC0_TEC1       _canh0.rtec.bit.TEC1
#define RTEC0_TEC2       _canh0.rtec.bit.TEC2
#define RTEC0_TEC3       _canh0.rtec.bit.TEC3
#define RTEC0_TEC4       _canh0.rtec.bit.TEC4
#define RTEC0_TEC5       _canh0.rtec.bit.TEC5
#define RTEC0_TEC6       _canh0.rtec.bit.TEC6
#define RTEC0_TEC7       _canh0.rtec.bit.TEC7
#define RTEC0_REC        _canh0.rtec.bitc.REC
#define RTEC0_TEC        _canh0.rtec.bitc.TEC

#define BTR0             _canh0.btr.word
#define BTR0_PSC0        _canh0.btr.bit.PSC0
#define BTR0_PSC1        _canh0.btr.bit.PSC1
#define BTR0_PSC2        _canh0.btr.bit.PSC2
#define BTR0_PSC3        _canh0.btr.bit.PSC3
#define BTR0_PSC4        _canh0.btr.bit.PSC4
#define BTR0_PSC5        _canh0.btr.bit.PSC5
#define BTR0_RSJ0        _canh0.btr.bit.RSJ0
#define BTR0_RSJ1        _canh0.btr.bit.RSJ1
#define BTR0_TS10        _canh0.btr.bit.TS10
#define BTR0_TS11        _canh0.btr.bit.TS11
#define BTR0_TS12        _canh0.btr.bit.TS12
#define BTR0_TS13        _canh0.btr.bit.TS13
#define BTR0_TS20        _canh0.btr.bit.TS20
#define BTR0_TS21        _canh0.btr.bit.TS21
#define BTR0_TS22        _canh0.btr.bit.TS22
#define BTR0_PSC         _canh0.btr.bitc.PSC
#define BTR0_RSJ         _canh0.btr.bitc.RSJ
#define BTR0_TS1         _canh0.btr.bitc.TS1
#define BTR0_TS2         _canh0.btr.bitc.TS2

#define IDER0            _canh0.ider.word
#define IDER0_IDE0       _canh0.ider.bit.IDE0
#define IDER0_IDE1       _canh0.ider.bit.IDE1
#define IDER0_IDE2       _canh0.ider.bit.IDE2
#define IDER0_IDE3       _canh0.ider.bit.IDE3
#define IDER0_IDE4       _canh0.ider.bit.IDE4
#define IDER0_IDE5       _canh0.ider.bit.IDE5
#define IDER0_IDE6       _canh0.ider.bit.IDE6
#define IDER0_IDE7       _canh0.ider.bit.IDE7
#define IDER0_IDE8       _canh0.ider.bit.IDE8
#define IDER0_IDE9       _canh0.ider.bit.IDE9
#define IDER0_IDE10      _canh0.ider.bit.IDE10
#define IDER0_IDE11      _canh0.ider.bit.IDE11
#define IDER0_IDE12      _canh0.ider.bit.IDE12
#define IDER0_IDE13      _canh0.ider.bit.IDE13
#define IDER0_IDE14      _canh0.ider.bit.IDE14
#define IDER0_IDE15      _canh0.ider.bit.IDE15

#define TRTRR0           _canh0.trtrr.word
#define TRTRR0_TRTR0     _canh0.trtrr.bit.TRTR0
#define TRTRR0_TRTR1     _canh0.trtrr.bit.TRTR1
#define TRTRR0_TRTR2     _canh0.trtrr.bit.TRTR2
#define TRTRR0_TRTR3     _canh0.trtrr.bit.TRTR3
#define TRTRR0_TRTR4     _canh0.trtrr.bit.TRTR4
#define TRTRR0_TRTR5     _canh0.trtrr.bit.TRTR5
#define TRTRR0_TRTR6     _canh0.trtrr.bit.TRTR6
#define TRTRR0_TRTR7     _canh0.trtrr.bit.TRTR7
#define TRTRR0_TRTR8     _canh0.trtrr.bit.TRTR8
#define TRTRR0_TRTR9     _canh0.trtrr.bit.TRTR9
#define TRTRR0_TRTR10    _canh0.trtrr.bit.TRTR10
#define TRTRR0_TRTR11    _canh0.trtrr.bit.TRTR11
#define TRTRR0_TRTR12    _canh0.trtrr.bit.TRTR12
#define TRTRR0_TRTR13    _canh0.trtrr.bit.TRTR13
#define TRTRR0_TRTR14    _canh0.trtrr.bit.TRTR14
#define TRTRR0_TRTR15    _canh0.trtrr.bit.TRTR15

#define RFWTR0           _canh0.rfwtr.word
#define RFWTR0_RFWT0     _canh0.rfwtr.bit.RFWT0
#define RFWTR0_RFWT1     _canh0.rfwtr.bit.RFWT1
#define RFWTR0_RFWT2     _canh0.rfwtr.bit.RFWT2
#define RFWTR0_RFWT3     _canh0.rfwtr.bit.RFWT3
#define RFWTR0_RFWT4     _canh0.rfwtr.bit.RFWT4
#define RFWTR0_RFWT5     _canh0.rfwtr.bit.RFWT5
#define RFWTR0_RFWT6     _canh0.rfwtr.bit.RFWT6
#define RFWTR0_RFWT7     _canh0.rfwtr.bit.RFWT7
#define RFWTR0_RFWT8     _canh0.rfwtr.bit.RFWT8
#define RFWTR0_RFWT9     _canh0.rfwtr.bit.RFWT9
#define RFWTR0_RFWT10    _canh0.rfwtr.bit.RFWT10
#define RFWTR0_RFWT11    _canh0.rfwtr.bit.RFWT11
#define RFWTR0_RFWT12    _canh0.rfwtr.bit.RFWT12
#define RFWTR0_RFWT13    _canh0.rfwtr.bit.RFWT13
#define RFWTR0_RFWT14    _canh0.rfwtr.bit.RFWT14
#define RFWTR0_RFWT15    _canh0.rfwtr.bit.RFWT15

#define TIER0            _canh0.tier.word
#define TIER0_TIE0       _canh0.tier.bit.TIE0
#define TIER0_TIE1       _canh0.tier.bit.TIE1
#define TIER0_TIE2       _canh0.tier.bit.TIE2
#define TIER0_TIE3       _canh0.tier.bit.TIE3
#define TIER0_TIE4       _canh0.tier.bit.TIE4
#define TIER0_TIE5       _canh0.tier.bit.TIE5
#define TIER0_TIE6       _canh0.tier.bit.TIE6
#define TIER0_TIE7       _canh0.tier.bit.TIE7
#define TIER0_TIE8       _canh0.tier.bit.TIE8
#define TIER0_TIE9       _canh0.tier.bit.TIE9
#define TIER0_TIE10      _canh0.tier.bit.TIE10
#define TIER0_TIE11      _canh0.tier.bit.TIE11
#define TIER0_TIE12      _canh0.tier.bit.TIE12
#define TIER0_TIE13      _canh0.tier.bit.TIE13
#define TIER0_TIE14      _canh0.tier.bit.TIE14
#define TIER0_TIE15      _canh0.tier.bit.TIE15

#define AMSR0            _canh0.amsr.dword
#define AMSR0_AMS0       _canh0.amsr.bitc.AMS0
#define AMSR0_AMS1       _canh0.amsr.bitc.AMS1
#define AMSR0_AMS2       _canh0.amsr.bitc.AMS2
#define AMSR0_AMS3       _canh0.amsr.bitc.AMS3
#define AMSR0_AMS4       _canh0.amsr.bitc.AMS4
#define AMSR0_AMS5       _canh0.amsr.bitc.AMS5
#define AMSR0_AMS6       _canh0.amsr.bitc.AMS6
#define AMSR0_AMS7       _canh0.amsr.bitc.AMS7
#define AMSR0_AMS8       _canh0.amsr.bitc.AMS8
#define AMSR0_AMS9       _canh0.amsr.bitc.AMS9
#define AMSR0_AMS10      _canh0.amsr.bitc.AMS10
#define AMSR0_AMS11      _canh0.amsr.bitc.AMS11
#define AMSR0_AMS12      _canh0.amsr.bitc.AMS12
#define AMSR0_AMS13      _canh0.amsr.bitc.AMS13
#define AMSR0_AMS14      _canh0.amsr.bitc.AMS14
#define AMSR0_AMS15      _canh0.amsr.bitc.AMS15
                     
#define AMR00            _canh0.amr[0].word  /* AMR0 for CAN0 (std ID bits) */
#define AMR10            _canh0.amr[1].word  /* AMR1 for CAN0 (std ID bits) */
#define AMRX00           _canh0.amr[0].dword /* AMR0 for CAN0 (ext ID bits) */
#define AMRX10           _canh0.amr[1].dword /* AMR1 for CAN0 (ext ID bits) */

/* CAN1 macros */
#define CSR1             _canh1.csr.word
#define CSR1_HALT        _canh1.csr.bit.HALT
#define CSR1_NIE         _canh1.csr.bit.NIE
#define CSR1_TOE         _canh1.csr.bit.TOE
#define CSR1_NS0         _canh1.csr.bit.NS0
#define CSR1_NS1         _canh1.csr.bit.NS1
#define CSR1_NT          _canh1.csr.bit.NT
#define CSR1_RS          _canh1.csr.bit.RS
#define CSR1_TS          _canh1.csr.bit.TS
#define CSR1_NS          _canh1.csr.bitc.NS

#define LEIR1            _canh1.leir.byte
#define LEIR1_MBP0       _canh1.leir.bit.MBP0
#define LEIR1_MBP1       _canh1.leir.bit.MBP1
#define LEIR1_MBP2       _canh1.leir.bit.MBP2
#define LEIR1_MBP3       _canh1.leir.bit.MBP3
#define LEIR1_RCE        _canh1.leir.bit.RCE
#define LEIR1_TCE        _canh1.leir.bit.TCE
#define LEIR1_NTE        _canh1.leir.bit.NTE
#define LEIR1_MBP        _canh1.leir.bitc.MBP

#define RTEC1            _canh1.rtec.word
#define RTEC1_REC0       _canh1.rtec.bit.REC0
#define RTEC1_REC1       _canh1.rtec.bit.REC1
#define RTEC1_REC2       _canh1.rtec.bit.REC2
#define RTEC1_REC3       _canh1.rtec.bit.REC3
#define RTEC1_REC4       _canh1.rtec.bit.REC4
#define RTEC1_REC5       _canh1.rtec.bit.REC5
#define RTEC1_REC6       _canh1.rtec.bit.REC6
#define RTEC1_REC7       _canh1.rtec.bit.REC7
#define RTEC1_TEC0       _canh1.rtec.bit.TEC0
#define RTEC1_TEC1       _canh1.rtec.bit.TEC1
#define RTEC1_TEC2       _canh1.rtec.bit.TEC2
#define RTEC1_TEC3       _canh1.rtec.bit.TEC3
#define RTEC1_TEC4       _canh1.rtec.bit.TEC4
#define RTEC1_TEC5       _canh1.rtec.bit.TEC5
#define RTEC1_TEC6       _canh1.rtec.bit.TEC6
#define RTEC1_TEC7       _canh1.rtec.bit.TEC7
#define RTEC1_REC        _canh1.rtec.bitc.REC
#define RTEC1_TEC        _canh1.rtec.bitc.TEC

#define BTR1             _canh1.btr.word
#define BTR1_PSC0        _canh1.btr.bit.PSC0
#define BTR1_PSC1        _canh1.btr.bit.PSC1
#define BTR1_PSC2        _canh1.btr.bit.PSC2
#define BTR1_PSC3        _canh1.btr.bit.PSC3
#define BTR1_PSC4        _canh1.btr.bit.PSC4
#define BTR1_PSC5        _canh1.btr.bit.PSC5
#define BTR1_RSJ0        _canh1.btr.bit.RSJ0
#define BTR1_RSJ1        _canh1.btr.bit.RSJ1
#define BTR1_TS10        _canh1.btr.bit.TS10
#define BTR1_TS11        _canh1.btr.bit.TS11
#define BTR1_TS12        _canh1.btr.bit.TS12
#define BTR1_TS13        _canh1.btr.bit.TS13
#define BTR1_TS20        _canh1.btr.bit.TS20
#define BTR1_TS21        _canh1.btr.bit.TS21
#define BTR1_TS22        _canh1.btr.bit.TS22
#define BTR1_PSC         _canh1.btr.bitc.PSC
#define BTR1_RSJ         _canh1.btr.bitc.RSJ
#define BTR1_TS1         _canh1.btr.bitc.TS1
#define BTR1_TS2         _canh1.btr.bitc.TS2

#define IDER1            _canh1.ider.word
#define IDER1_IDE0       _canh1.ider.bit.IDE0
#define IDER1_IDE1       _canh1.ider.bit.IDE1
#define IDER1_IDE2       _canh1.ider.bit.IDE2
#define IDER1_IDE3       _canh1.ider.bit.IDE3
#define IDER1_IDE4       _canh1.ider.bit.IDE4
#define IDER1_IDE5       _canh1.ider.bit.IDE5
#define IDER1_IDE6       _canh1.ider.bit.IDE6
#define IDER1_IDE7       _canh1.ider.bit.IDE7
#define IDER1_IDE8       _canh1.ider.bit.IDE8
#define IDER1_IDE9       _canh1.ider.bit.IDE9
#define IDER1_IDE10      _canh1.ider.bit.IDE10
#define IDER1_IDE11      _canh1.ider.bit.IDE11
#define IDER1_IDE12      _canh1.ider.bit.IDE12
#define IDER1_IDE13      _canh1.ider.bit.IDE13
#define IDER1_IDE14      _canh1.ider.bit.IDE14
#define IDER1_IDE15      _canh1.ider.bit.IDE15

#define TRTRR1           _canh1.trtrr.word
#define TRTRR1_TRTR0     _canh1.trtrr.bit.TRTR0
#define TRTRR1_TRTR1     _canh1.trtrr.bit.TRTR1
#define TRTRR1_TRTR2     _canh1.trtrr.bit.TRTR2
#define TRTRR1_TRTR3     _canh1.trtrr.bit.TRTR3
#define TRTRR1_TRTR4     _canh1.trtrr.bit.TRTR4
#define TRTRR1_TRTR5     _canh1.trtrr.bit.TRTR5
#define TRTRR1_TRTR6     _canh1.trtrr.bit.TRTR6
#define TRTRR1_TRTR7     _canh1.trtrr.bit.TRTR7
#define TRTRR1_TRTR8     _canh1.trtrr.bit.TRTR8
#define TRTRR1_TRTR9     _canh1.trtrr.bit.TRTR9
#define TRTRR1_TRTR10    _canh1.trtrr.bit.TRTR10
#define TRTRR1_TRTR11    _canh1.trtrr.bit.TRTR11
#define TRTRR1_TRTR12    _canh1.trtrr.bit.TRTR12
#define TRTRR1_TRTR13    _canh1.trtrr.bit.TRTR13
#define TRTRR1_TRTR14    _canh1.trtrr.bit.TRTR14
#define TRTRR1_TRTR15    _canh1.trtrr.bit.TRTR15

#define RFWTR1           _canh1.rfwtr.word
#define RFWTR1_RFWT0     _canh1.rfwtr.bit.RFWT0
#define RFWTR1_RFWT1     _canh1.rfwtr.bit.RFWT1
#define RFWTR1_RFWT2     _canh1.rfwtr.bit.RFWT2
#define RFWTR1_RFWT3     _canh1.rfwtr.bit.RFWT3
#define RFWTR1_RFWT4     _canh1.rfwtr.bit.RFWT4
#define RFWTR1_RFWT5     _canh1.rfwtr.bit.RFWT5
#define RFWTR1_RFWT6     _canh1.rfwtr.bit.RFWT6
#define RFWTR1_RFWT7     _canh1.rfwtr.bit.RFWT7
#define RFWTR1_RFWT8     _canh1.rfwtr.bit.RFWT8
#define RFWTR1_RFWT9     _canh1.rfwtr.bit.RFWT9
#define RFWTR1_RFWT10    _canh1.rfwtr.bit.RFWT10
#define RFWTR1_RFWT11    _canh1.rfwtr.bit.RFWT11
#define RFWTR1_RFWT12    _canh1.rfwtr.bit.RFWT12
#define RFWTR1_RFWT13    _canh1.rfwtr.bit.RFWT13
#define RFWTR1_RFWT14    _canh1.rfwtr.bit.RFWT14
#define RFWTR1_RFWT15    _canh1.rfwtr.bit.RFWT15

#define TIER1            _canh1.tier.word
#define TIER1_TIE0       _canh1.tier.bit.TIE0
#define TIER1_TIE1       _canh1.tier.bit.TIE1
#define TIER1_TIE2       _canh1.tier.bit.TIE2
#define TIER1_TIE3       _canh1.tier.bit.TIE3
#define TIER1_TIE4       _canh1.tier.bit.TIE4
#define TIER1_TIE5       _canh1.tier.bit.TIE5
#define TIER1_TIE6       _canh1.tier.bit.TIE6
#define TIER1_TIE7       _canh1.tier.bit.TIE7
#define TIER1_TIE8       _canh1.tier.bit.TIE8
#define TIER1_TIE9       _canh1.tier.bit.TIE9
#define TIER1_TIE10      _canh1.tier.bit.TIE10
#define TIER1_TIE11      _canh1.tier.bit.TIE11
#define TIER1_TIE12      _canh1.tier.bit.TIE12
#define TIER1_TIE13      _canh1.tier.bit.TIE13
#define TIER1_TIE14      _canh1.tier.bit.TIE14
#define TIER1_TIE15      _canh1.tier.bit.TIE15

#define AMSR1            _canh1.amsr.dword
#define AMSR1_AMS0       _canh1.amsr.bitc.AMS0
#define AMSR1_AMS1       _canh1.amsr.bitc.AMS1
#define AMSR1_AMS2       _canh1.amsr.bitc.AMS2
#define AMSR1_AMS3       _canh1.amsr.bitc.AMS3
#define AMSR1_AMS4       _canh1.amsr.bitc.AMS4
#define AMSR1_AMS5       _canh1.amsr.bitc.AMS5
#define AMSR1_AMS6       _canh1.amsr.bitc.AMS6
#define AMSR1_AMS7       _canh1.amsr.bitc.AMS7
#define AMSR1_AMS8       _canh1.amsr.bitc.AMS8
#define AMSR1_AMS9       _canh1.amsr.bitc.AMS9
#define AMSR1_AMS10      _canh1.amsr.bitc.AMS10
#define AMSR1_AMS11      _canh1.amsr.bitc.AMS11
#define AMSR1_AMS12      _canh1.amsr.bitc.AMS12
#define AMSR1_AMS13      _canh1.amsr.bitc.AMS13
#define AMSR1_AMS14      _canh1.amsr.bitc.AMS14
#define AMSR1_AMS15      _canh1.amsr.bitc.AMS15
                     
#define AMR01            _canh1.amr[0].word  /* AMR0 for CAN1 (std ID bits) */
#define AMR11            _canh1.amr[1].word  /* AMR1 for CAN1 (std ID bits) */
#define AMRX01           _canh1.amr[0].dword /* AMR0 for CAN1 (ext ID bits) */
#define AMRX11           _canh1.amr[1].dword /* AMR1 for CAN1 (ext ID bits) */

__IO_EXTENDED CANMSTR _canm0;
__IO_EXTENDED CANMSTR _canm1;

/* CAN0 macros */
#define IDR0(buf)            (_canm0.idr[buf].word)
#define IDRX0(buf)           (_canm0.idr[buf].dword)

#define DLCR0(buf)           (_canm0.dlcr[buf].byte)
#define DLCR0_DLC0(buf)      (_canm0.dlcr[buf].bit.DLC0)
#define DLCR0_DLC1(buf)      (_canm0.dlcr[buf].bit.DLC1)
#define DLCR0_DLC2(buf)      (_canm0.dlcr[buf].bit.DLC2)
#define DLCR0_DLC3(buf)      (_canm0.dlcr[buf].bit.DLC3)

#define DTR0_BPTR(  buf)     (_canm0.dtr[buf].bytes )
#define DTR0_WPTR(  buf)     (_canm0.dtr[buf].words )
#define DTR0_LWPTR( buf)     (_canm0.dtr[buf].dwords)
#define DTR0_CPTR(  buf)     (_canm0.dtr[buf].chars )
#define DTR0_IPTR(  buf)     (_canm0.dtr[buf].ints  )
#define DTR0_LPTR(  buf)     (_canm0.dtr[buf].longs )

#define DTR0_BYTE(  buf,i)   (_canm0.dtr[buf].bytes  [i])
#define DTR0_WORD(  buf,i)   (_canm0.dtr[buf].words  [i])
#define DTR0_DWORD( buf,i)   (_canm0.dtr[buf].dwords [i])
#define DTR0_CHAR(  buf,i)   (_canm0.dtr[buf].chars  [i])
#define DTR0_INT(   buf,i)   (_canm0.dtr[buf].ints   [i])
#define DTR0_LONGS( buf,i)   (_canm0.dtr[buf].longs  [i])
#define DTR0_FLOATS(buf,i)   (_canm0.dtr[buf].floats [i])
#define DTR0_DOUBLE(buf  )   (_canm0.dtr[buf].adouble   )

/* CAN1 macros */
#define IDR1(buf)            (_canm1.idr[buf].word)
#define IDRX1(buf)           (_canm1.idr[buf].dword)

#define DLCR1(buf)           (_canm1.dlcr[buf].byte)
#define DLCR1_DLC0(buf)      (_canm1.dlcr[buf].bit.DLC0)
#define DLCR1_DLC1(buf)      (_canm1.dlcr[buf].bit.DLC1)
#define DLCR1_DLC2(buf)      (_canm1.dlcr[buf].bit.DLC2)
#define DLCR1_DLC3(buf)      (_canm1.dlcr[buf].bit.DLC3)

#define DTR1_BPTR(  buf)     (_canm1.dtr[buf].bytes )
#define DTR1_WPTR(  buf)     (_canm1.dtr[buf].words )
#define DTR1_DWPTR( buf)     (_canm1.dtr[buf].dwords)
#define DTR1_CPTR(  buf)     (_canm1.dtr[buf].chars )
#define DTR1_IPTR(  buf)     (_canm1.dtr[buf].ints  )
#define DTR1_LPTR(  buf)     (_canm1.dtr[buf].longs )

#define DTR1_BYTE(  buf,i)   (_canm1.dtr[buf].bytes  [i])
#define DTR1_WORD(  buf,i)   (_canm1.dtr[buf].words  [i])
#define DTR1_DWORD( buf,i)   (_canm1.dtr[buf].dwords [i])
#define DTR1_CHAR(  buf,i)   (_canm1.dtr[buf].chars  [i])
#define DTR1_INT(   buf,i)   (_canm1.dtr[buf].ints   [i])
#define DTR1_LONGS( buf,i)   (_canm1.dtr[buf].longs  [i])
#define DTR1_FLOATS(buf,i)   (_canm1.dtr[buf].floats [i])
#define DTR1_DOUBLE(buf  )   (_canm1.dtr[buf].adouble   )

#endif /* CANMAC */
#  undef ___IOWIDTH
#endif                   /* __MB90XXX_H */
