#include "mco_emcy.h"

//extern TMCO_ust	_mr;

byte EMCY_Send( lword code )
{
   if ( (mco_ust.EmcyID.all & 0x8000) == 0 ) // Если EMCY-ID создан
   {

   }
   // Если EMCY-ID не создан - ничего не отправляем
   return code;
}
