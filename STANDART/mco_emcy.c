#include "mco_emcy.h"

//extern TMCO_ust	_mr;

byte EMCY_Send( lword code )
{
   if ( (mco_ust.EmcyID.all & 0x8000) == 0 ) // ���� EMCY-ID ������
   {

   }
   // ���� EMCY-ID �� ������ - ������ �� ����������
   return code;
}
