#include "array.h"

void ArrayInit( TArray* array )
{
  byte i;

  array->count = 0;
  for ( i = 0; i < ( MAX_NUM_ARRAY - 1); i++ )
  {
  	 array->data[i] = 0;
  }
}


void ArrayPush( TArray* array, lword data )
{
  byte i;

   for ( i = array->count; i > 0; i-- )
   {
   	  array->data[i] = array->data[i-1];
   }
   array->count++;
   array->data[0] = data;

}

byte ArrayPop( TArray* array, lword *data )
{
   byte i;

   if ( array->count == 0 ) return 0;
   *data = array->data[0];
   for ( i = 0; i < array->count; i++ )
   {
   	  array->data[i] = array->data[i+1];
   }
   array->count--;
   return 1;

}


lword ArrayFindNum( TArray* array, lword data )
{
   byte i;

   if ( array->count == 0 ) return 0;
   for ( i = 0; i < array->count; i++ )
   {
   	  if ( array->data[i] == data ) return i+1;
   }
   return 0;
}

lword ArrayFindNumMask( TArray* array, lword data,  lword mask )
{
   byte i;

   if ( array->count == 0 ) return 0;
   for ( i = 0; i < array->count; i++ )
   {
   	  if ( (array->data[i] & mask) == data ) return i+1;
   }
   return 0;

}


byte ArrayReadValue( TArray* array, lword num, lword *data )
{
   if ( ( array->count == 0 ) || ( array->count < num ) ) return 0;
   *data = array->data[num-1];
   return 1;
}

byte ArrayWriteValue( TArray* array, lword num, lword data )
{
   if ( num > MAX_NUM_ARRAY)  return 0;
   if ( num > array->count ) array->count = num;
   array->data[num-1] = data;
   return 1;
}


