#ifndef _types_h
#define _types_h

/*   Çàäàåì èñòî÷íèê ââîäà/âûâîäà äëÿ ïóëüòîâûõ ïğîãğàìì.
 *  ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
 */       /*  Ğîäíîé ïîñëåäîâ.ïîğò 196-é  */
#define   _Terminal_196xRS232

/*ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  */

    /*     Fuj íå ïîíèìàåò register äëÿ  static è äëÿ âíåøíèõ ïåğåìåííûõ
         ïî-ıòîìó çàìåíÿåì åãî íà ' '.
     */
#define   _register

typedef   unsigned char       byte  ;
typedef   unsigned short      word  ;
typedef   unsigned long      lword  ;

typedef     signed char      sbyte  ;
typedef     signed short     sword  ;
typedef     signed long     slword  ;

typedef   const               c  ;
typedef   double              d  ;
typedef   unsigned char       b  ;
typedef   unsigned short      w  ;
typedef   unsigned long      lw  ;

typedef     signed char      sb  ;
typedef     signed short     sw  ;
typedef     signed long      slw  ;

#define   _x_far

#define int8   signed char
#define int16  signed short
#define int32  signed int
#define int64  signed long long

#define uint8  unsigned char
#define uint16  unsigned short
#define uint32  unsigned int
#define uint64  unsigned long long

/*-----------------------------------------------  */

typedef   unsigned     u;
typedef    signed      s;

#ifdef _24_BITS_
/*----------------------  */
/*typedef   __far unsigned char       fbyte  ;
typedef   __far unsigned int        fword  ;
typedef   __far unsigned long int  flword  ;

typedef   __far   signed char      fsbyte  ;
typedef   __far   signed int       fsword  ;
typedef   __far   signed long int fslword  ;

typedef   __far double              fd  ;
typedef   __far unsigned char       fb  ;
typedef   __far unsigned int        fw  ;
typedef   __far unsigned long int  flw  ;

typedef   __far   signed char      fsb  ;
typedef   __far   signed int       fsw  ;
typedef   __far   signed long int fslw  ;
/*----------------------  */
//#else
/*----------------------  */
typedef   unsigned char       fbyte  ;
typedef   unsigned short      fword  ;
typedef   unsigned long      flword  ;

typedef     signed char      fsbyte  ;
typedef     signed short     fsword  ;
typedef     signed long     fslword  ;

typedef   double              fd  ;
typedef   unsigned char       fb  ;
typedef   unsigned short      fw  ;
typedef   unsigned long      flw  ;

typedef     signed char      fsb  ;
typedef     signed short     fsw  ;
typedef     signed long     fslw  ;
/*----------------------  */
#endif
/*-----------------------------------------------  */


/*------------------------------------------------*/
#endif
