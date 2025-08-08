#ifndef _zi_h
#define _zi_h

struct ZI {
            word in, out ;  /* Вход / Выход   ЗИ.  */
            word drob  ;    /* Дробная часть выхода ЗИ.  */
            word *temp_p ;  /* Адрес уставки тепма, размерность которой: "дискреты в секунду".  */
            word *temp_m ;  /* Адрес уставки тепма, размерность которой: "дискреты в секунду".  */
            word time  ;    /* Время последней отработки ЗИ.  */
          } ;

void Zad_Intens ( struct ZI *zip ) ;

void Set_ZI ( struct ZI *zip , word ) ;

#endif
