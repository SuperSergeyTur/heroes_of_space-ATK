//---------------------------------------------

/*-- Регенерация уставок по месту работы в зависимости от кода места работы.--*/
//
//   Perekl_rezerv ( 0, 0 ) ;  в main() - вызов для стартовой инициализации.
//
//   Perekl_rezerv( 1, read_rezerv()) ; в Sborka_Gotovn() -  рабочий вызов.
//
//   read_rezerv() - в obj.c передает код резерва: 0 - все отключено
//                                                 1,2,3... - номер резерва.
//
word  Perekl_rezerv ( word code, word code_rezerv )
{
  static byte label_code_rezerv;//, copy_code_rezerv; 04.04.2014 9:46 перенесен в "Monitor.h" для правильного
  word ax;                      // отображения текущей области уставок в "About" и при чтении уставок в "CodeReadWriter".
  word bx;
  static word count;
  enum  { k0, k1, k10, k20, k25,
#ifdef _JOURNAL
        k26,
#endif
        k30, k35 }  ;
  ax = 4;
            // инициализация.
        if ( code == 0 )
        {
          Num_obl = 1;
          Name_Agr = Num_obl ;   //12.11.08 13:06
          label_code_rezerv = k0, copy_code_rezerv = 0xff ;
          Wr_label = 0 ;
          count = 0;
          return 0 ;
        }

            // Для объектов без резервов.
        if ( _kol_obl <= 1 ) return 0;

        switch ( label_code_rezerv )
        {
          default: label_code_rezerv = k0 ;
                  //----------------
          case k0 :
          case k1 :
                 //  Вывод наименования объекта по дист. сбросу.
              if ( bi_DS1 == 1 )  label_code_rezerv = k1 ; // ловим перепад
              else  if ( label_code_rezerv == k1 )
              {
                label_code_rezerv = k30 ;
                break;
              }

             if ( copy_code_rezerv != code_rezerv )//Сравнивание с предыдущей копией.
              {    //Если код изменился из-за исчезнувшего сигнала
                copy_code_rezerv = code_rezerv ; //vvv

                can_obj_stop() ; // отключаемся от CAN
                if ( code_rezerv != 0 ) label_code_rezerv = k10 ;
                else                    label_code_rezerv = k30 ;
              }
              else if ( code == 2 ) label_code_rezerv = k30 ;
              else ax = 0;
           break ;
             //-----------------------
          case k10 :
                  // Предупр. чтобы опрератор подошел к угрегату и посмотрел.
                //code = 2 в функции Init_Prog (при загрузке сообщение не устанавливается)
                if ( code != 2 )mSet_PreduprMsg( _Pr_Rezerv_Zam ) ;
                if ( Num_obl == 0 ) break; // ожидаем разблокировки от "АЕ-Зап.Устав"
                Num_obl = 0 ; // "0"-блокирует запись уставок по "АЕ-Зап.Устав"
                Wr_label = 0 ;// на время перезагрузки уставок.
                label_code_rezerv = k20 ;
                count = 0;
           break ;
             //-----------------------

          case k20 :
                // Происходит перезапись уставок из i2c в ОЗУ,
                // во время которой нельзя входить в "Работу"
              if ( code != 2 ) mSet_PreduprMsg( _Pr_Rezerv_Zam ) ;
              bx = Rd_wr_ust( copy_code_rezerv );  // 08.02.2019 10:16. Уссурийск 5к. Проблемы с перезагрузкой областей
              if( bx == 4 );                       // уставок (проявилось на номиналах).Причина не установлена.
              else if( bx == 0 || count >= 3 )     // Виталик сказал - делаем повторы.
              //if ( Rd_wr_ust( copy_code_rezerv ) != 4 )
              {   // Переинициализацию CAN производим после перезаписи уставок.
                can_obj_start() ; // подключаемся к CAN
                Num_obl = copy_code_rezerv ; // переключаем рабочую область уставок.
                label_code_rezerv = k25 ;
              }
              else
              {
                count++;
                Wr_label = 0;
              }
             break ;
              //-----------------------
          case k25 :
                // Происходит перезапись уставок из i2c в ОЗУ,
                // во время которой нельзя входить в "Работу"
               if ( code != 2 ) mSet_PreduprMsg( _Pr_Rezerv_Zam ) ;
                   //   Находим соответствие именам из рабочей таблицы имен
                   // в const-таблице.
              if ( TestSledTab () != 4 )
              {
#ifdef _JOURNAL
                label_code_rezerv = k26 ;
#else
                label_code_rezerv = k30 ;
                //перезапись в одном месте после отработки всех
                //перезагрузок при изменении резерва
                Name_Agr = Num_obl ; //12.11.08 13:06
#endif
              }
             break ;
              //-----------------------

#ifdef _JOURNAL
          case k26 :
                // Происходит перезапись уставок из i2c в ОЗУ,
                // во время которой нельзя входить в "Работу"
               if ( code != 2 ) mSet_PreduprMsg( _Pr_Rezerv_Zam ) ;
                   //   Находим соответствие именам из рабочей таблицы имен
                   // в const-таблице.
              if ( TestJrnTab ( 0 ) != 4 )
              {
                label_code_rezerv = k30 ;
                //перезапись в одном месте после отработки всех
                //перезагрузок при изменении резерва
                Name_Agr = Num_obl ; //12.11.08 13:06
              }
             break ;
              //-----------------------
#endif

          case k30 :
                  /* Ожидание окончания вывода имеющихся в буфере сообщений */
              if ( TestCompleted_Output() )
              {     //  Вывод наименования объекта по дист. сбросу.
                //label_code_rezerv = k0 ;
                output_s( _Agregat_txt ) ;
                if ( copy_code_rezerv == 0 ) output_s( _AgregatOut_txt ) ;
                else       output_s(Tabl_name_ust[copy_code_rezerv - 1]) ;
                ax = 0;
                //если сообщение до сих пор не сброшено - будем ждать на метке
                //k35 дист. сброса
                if ( (Reg_PreduprMsg & _Pr_Rezerv_Zam) != 0 ) label_code_rezerv = k35 ;
                //если дист.сброс нажат - можем щупать переключение резерва
                else label_code_rezerv = k0 ;
              }
             break ;
              //-----------------------
          case k35 :
              //ждем, пока не будет дист.сброса - резерв не переключаем
              if ( (Reg_PreduprMsg & _Pr_Rezerv_Zam) == 0 ) label_code_rezerv = k0 ;
             break ;
        }

    return ax;
}
