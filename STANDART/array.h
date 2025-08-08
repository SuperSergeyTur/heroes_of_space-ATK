#ifndef  _ARRAY_H
  #define  _ARRAY_H

#define MAX_NUM_ARRAY	10

typedef struct
{
   byte 	count;
   lword 	data[MAX_NUM_ARRAY];
}
TArray;

#ifdef  _CANOPEN_INCLUDE

void ArrayInit( TArray* array );
void ArrayPush( TArray* array, lword data );
byte ArrayPop( TArray* array, lword *data );
lword ArrayFindNum( TArray* array, lword data );
lword ArrayFindNumMask( TArray* array, lword data,  lword mask );
byte ArrayRead( TArray* array, lword num, lword *data );
byte ArrayWrite( TArray* array, lword num, lword data  );

#else

extern void ArrayInit( TArray* array );
extern void ArrayPush( TArray* array, lword data );
extern byte ArrayPop( TArray* array, lword *data );
extern lword ArrayFindNum( TArray* array, lword data );
extern lword ArrayFindNumMask( TArray* array, lword data,  lword mask );
extern byte ArrayReadValue( TArray* array, lword num, lword *data );
extern byte ArrayWriteValue( TArray* array, lword num, lword data );

#endif


#endif
