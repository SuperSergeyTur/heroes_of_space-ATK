#ifndef _zi_h
#define _zi_h

struct ZI
 {
   word in , in_2  ;               // Вход ЗИ / Вход 2-го интегратора ЗИ .
   word out_lin , out_2 , out ;    // Выход линейного ЗИ / выход 2-го интегратора / выход параболического ЗИ .
   word drob_lin , drob_2 , drob ; // Дробная часть линейного выхода ЗИ / Дробная часть выхода 2-го интегратора / Дробная часть выхода ЗИ .             // Дробная часть выхода ЗИ.
   word *temp_p_razg ;    // Адрес уставки тепма разгона в "+" , размерность которой: "дискреты в секунду" .
   word *temp_p_torm ;    // Адрес уставки тепма торможения в "+", размерность которой: "дискреты в секунду" .
   word *temp_m_razg ;    // Адрес уставки тепма разгона в "-", размерность которой: "дискреты в секунду" .
   word *temp_m_torm ;    // Адрес уставки тепма торможения в "-", размерность которой: "дискреты в секунду".
   word *temp_parabola ;  // Адрес уставки темпа параболической части ЗИ, размерность которой: "дискреты в секунду" .
   word in2_copy  ;
   word out2_copy ;
   word outl_copy ;
   word start_m   ;
   word start_p   ;

      union
      {
        byte  all ;
        struct
        {
          //word   plus         : 1 ;
          //word   minus        : 1 ;
          word   trg_pl       : 1 ;
          word   trg_min      : 1 ;
          word   trg_lin      : 1 ;
          word   trg_pl_end   : 1 ;
          word   trg_min_end  : 1 ;
        } _ ;
      } prz ;


   word time_s ;
   word time  ;           // Время последней отработки ЗИ .
 } ;

void Zad_Intens ( struct ZI *zip ) ;

void Set_ZI ( struct ZI *zip , word ) ;


#endif
