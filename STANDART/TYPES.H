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
typedef   unsigned int        word  ;
typedef   unsigned long int  lword  ;

typedef     signed char      sbyte  ;
typedef     signed int       sword  ;
typedef     signed long int slword  ;

typedef     signed            s  ;
typedef   unsigned            u  ;
typedef   const               c  ;
typedef   float               f  ;
typedef   double              d  ;
typedef   unsigned char       b  ;
typedef   unsigned int        w  ;
typedef   unsigned long int  lw  ;

typedef     signed char      sb  ;
typedef     signed int       sw  ;
typedef     signed long int slw  ;

#define   _x_far           __far

/*-----------------------------------------------  */

#ifdef _24_BITS_
/*----------------------  */
typedef   _x_far unsigned char       fbyte  ;
typedef   _x_far unsigned int        fword  ;
typedef   _x_far unsigned long int  flword  ;

typedef   _x_far   signed char      fsbyte  ;
typedef   _x_far   signed int       fsword  ;
typedef   _x_far   signed long int fslword  ;

typedef   _x_far double              fd  ;
typedef   _x_far unsigned char       fb  ;
typedef   _x_far unsigned int        fw  ;
typedef   _x_far unsigned long int  flw  ;

typedef   _x_far   signed char      fsb  ;
typedef   _x_far   signed int       fsw  ;
typedef   _x_far   signed long int fslw  ;
/*----------------------  */
#else
/*----------------------  */
typedef   unsigned char       fbyte  ;
typedef   unsigned int        fword  ;
typedef   unsigned long int  flword  ;

typedef     signed char      fsbyte  ;
typedef     signed int       fsword  ;
typedef     signed long int fslword  ;

typedef   double              fd  ;
typedef   unsigned char       fb  ;
typedef   unsigned int        fw  ;
typedef   unsigned long int  flw  ;

typedef     signed char      fsb  ;
typedef     signed int       fsw  ;
typedef     signed long int fslw  ;
/*----------------------  */
#endif
/*-----------------------------------------------  */


/*------------------------------------------------*/
#endif
