#ifndef _filtr
#define _filtr
//Шаблон структуры для фильтрации аналоговых сигналов
struct fil {
             word *in ;    // вход
             word out ;    // выход
             double d_out ; // выход c дробной частью
             word *tau ;   // заданная постоянная времени фильтра 0.0005...12.0сек ( _fSec(...) )
             word time ;   // текущее время
             byte first ;  // для определения первого запуска
           } ;

void  FiltrLowFreq ( struct fil *ft );

#endif
