#ifndef _revers_h
#define _revers_h

#include <dzv_drv.h>

extern  void  Revers_epa_init ( void ) ;
extern  void  Revers_start ( void ) ;
extern  void  Revers_Interrupt ( void ) ;

/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

  //   массив ячеек для помещения результатов серии измерений тока при
  // контроле спада тока для разрешения реверса.

        word     Tok_for_Revers[ 3 ] ;

        word     dt_revers ;
        byte     dn_revers ;

        word     TimePuls_of_Revers ;

//   счетчик серий измерений с удовлетворительным результатом.
// определеное значение его содержимого является разрешением реверсирования.

        byte     Revers_Label ;

/*------------------------------------------------*/
#else
/*------------------------------------------------*/

extern  word     Tok_for_Revers[ 3 ] ;

extern  word     dt_revers ;
extern  byte     dn_revers ;

extern  word     TimePuls_of_Revers ;

extern  byte     Revers_Label ;

/*------------------------------------------------*/
#endif
#endif

