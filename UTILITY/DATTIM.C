//Программа формирования h - файла с текущими датой и временем.

# include  <stdio.h>
# include  <dos.h>
# include  <stdlib.h>
# include  <process.h>
# include  <math.h>

int main ( int argc, char *argv[] )
{

 struct  time t;
 struct date d;
 FILE  *fp ;

 if ( argc < 2 )
  {
   printf ( "\nПЁюуЁрььр фюЁьшЁютрэшя h - фрщыр ё тхъущшьш фртющ ш тЁхьхэхь.\n" ) ;
   printf ( "ПЁшьхЁ тычютр яЁюуЁрььы:\n%s name_file.h\n", (const char*)argv[0] ) ;
   return 1 ;
  }

 fp = fopen ( (const char*)argv[1] , "w" ) ;
 if ( fp == NULL )
  {
   fclose ( fp ) ;
   printf ( "\nНхтючьюцэю ютъЁыть шёхюфэыщ фрщы < (const char*)argv[1] > !\n" ) ;
   printf ( "Ррсютр яЁюуЁрььы < dattim.exe > яЁхЁтрэр !\n" ) ;
   return 1 ;
  }
 else
  {
   gettime ( &t ) ;
   getdate ( &d ) ;

   fprintf ( fp, "\n#ifndef _datetime_" ) ;
   fprintf ( fp, "\n#define _datetime_" ) ;
   fprintf ( fp , "\n\n#define __DATETIME__ \"%d ", d.da_day ) ;

   if ( d.da_mon == 1 )    fprintf ( fp, " января " ) ;
   if ( d.da_mon == 2 )    fprintf ( fp, "февраля " ) ;
   if ( d.da_mon == 3 )    fprintf ( fp, " марта  " ) ;
   if ( d.da_mon == 4 )    fprintf ( fp, " апреля " ) ;
   if ( d.da_mon == 5 )    fprintf ( fp, "  мая   " ) ;
   if ( d.da_mon == 6 )    fprintf ( fp, "  июня  " ) ;
   if ( d.da_mon == 7 )    fprintf ( fp, "  июля  " ) ;
   if ( d.da_mon == 8 )    fprintf ( fp, "августа " ) ;
   if ( d.da_mon == 9 )    fprintf ( fp, "сентября" ) ;
   if ( d.da_mon == 10 )   fprintf ( fp, "октября " ) ;
   if ( d.da_mon == 11 )   fprintf ( fp, " ноября " ) ;
   if ( d.da_mon == 12 )   fprintf ( fp, "декабря " ) ;

   fprintf ( fp, " %d\\r\\n   - %d:" , d.da_year , t.ti_hour ) ;

   if ( t.ti_min == 0 )   fprintf ( fp, "00 -   \"" ) ;
   if ( t.ti_min == 1 )   fprintf ( fp, "01 -   \"" ) ;
   if ( t.ti_min == 2 )   fprintf ( fp, "02 -   \"" ) ;
   if ( t.ti_min == 3 )   fprintf ( fp, "03 -   \"" ) ;
   if ( t.ti_min == 4 )   fprintf ( fp, "04 -   \"" ) ;
   if ( t.ti_min == 5 )   fprintf ( fp, "05 -   \"" ) ;
   if ( t.ti_min == 6 )   fprintf ( fp, "06 -   \"" ) ;
   if ( t.ti_min == 7 )   fprintf ( fp, "07 -   \"" ) ;
   if ( t.ti_min == 8 )   fprintf ( fp, "08 -   \"" ) ;
   if ( t.ti_min == 9 )   fprintf ( fp, "09 -   \"" ) ;
   if ( t.ti_min >= 10 )  fprintf ( fp, "%d -   \"",t.ti_min ) ;

   fprintf ( fp, "\n\n#endif\n" ) ;

  }
 fclose ( fp ) ;
 printf ( "Фрщы %s уёяхшэю ёфюЁьшЁютрэ.\n", (const char*)argv[1] ) ;
 return 0 ;
}
