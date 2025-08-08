#ifndef _unireg_h
#define _unireg_h


typedef struct {
            word *zad_max ;// Адрес уставки макс. огр. задания в "+".
            word *zad_min ;// Адрес уставки макс. огр. задания в "-".
            word *kp      ;// Адрес уставки пропорционального коэфф.
            word *ki      ;// Адрес уставки интегрального коэфф.
            word *zad     ;// Вход задания
            word *oc      ;//обрат.связь
            word  out ;   //  выход .
            word  dout ,din; //величина dout, которой достигает интегральная часть за время, определенное ki, при ошибке din
            word  add_zi;   //добавка ко входной величине, если надо влиять на него, минуя ЗИ.
            word  time;
            word  dt;
            word  lim_min;
            word  lim_max;
            word  integr  ;    // Интегратор,
            byte  integr_drob ;  // дробная часть интегратора.
            union    //  Байт конфигурации
            {       //  регулятора.
              byte all ;
              struct
              {
                word  positiv_oc : 1 ; // задает положительную о.с.
                word  pos_out    : 1 ; // Выход только положительный
                word  enable     : 1 ; //включение регулятора
                word  positiv_in : 1 ;  // задание только положительное
              } _ ;
            } cfg ;
            union   //  Байт временных флагов для
            {       // регулятора.
              byte all ;
              struct
              {
                word  ltd_int_p : 1 ;
                word  ltd_int_m : 1 ;
                word  ltd_z_max : 1 ;
                word  ltd_z_min : 1 ;
                word  ltd_zi_max : 1 ;
                word  ltd_zi_min : 1 ;
                word  rezerv1    : 1 ;
              } _ ;
            } b ;
            struct
            {
                word Zad_reg;
                word Def;
                word dIntegr;

            } Ind;
            struct ZI zi ;
          } Reg_Str;

/*------------------------------------------------*/
#endif
