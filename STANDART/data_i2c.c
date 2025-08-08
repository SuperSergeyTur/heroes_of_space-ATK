//Программа для записи числа(одного, или массива) по адресу в i2c. Работает с основном цикле
//програмы и правляется с помощью переменной Write_dat_i2c. если она не равна 0 - программа работает

void RW_i2c_data (word code)
{
    register byte    bh;

      //   Следует следить, чтобы номера меток здесь и далее шли
      //  последовательно по возрастающей.
enum { i0, i2, i3 };
      //-----------
        //для стартовой инициализации.
    if ( code == 0 )
    {
      Write_dat_i2c = 0;
      label_dat = 0;
      return ;
    }
      //-----------

    if ((Write_dat_i2c & ~_Error_Wr_ust) == 0 ) return ;// команды на запись нет.
      //-----------

    switch (  label_dat )
    {
      case i0:        //  Ожидаем разблокировки записи уставок от программы перезагрузки уставок.
                  if ( Mon.i2c_busy == 1 ) break; //  Ждем пока освободится шина.
                  asm_di() ; //на всякий случай, если будем писать в i2c в прерываниях

                  Mon.i2c_busy = 1 ;  // Устанавливаем признак, что теперь шина занята.

                  asm_ei() ;

                  i2c_label = 0;
                  if (i2c_str->code == 1) label_dat = i2 ;
                  else  label_dat = i3 ;
                  break;
      case i2:
                  bh = xSave_into_i2c ( i2c_str->size , i2c_str->addr_mem,i2c_str->addr_i2c,i2c_str->chip_addr ) ;
        read:
                  if ( bh == 4 ) break;  // пока = 4 - продолжаем чтение.
                  if ( bh == 1 )
                  {
                    Write_dat_i2c |= _Error_Wr_ust ;
                  }
                  else Write_dat_i2c = 0 ; // сбрасываем отработанные запросы на запись.

                  Mon.i2c_busy = 0 ;  // Устанавливаем признак, что теперь шина свободна.
                  label_dat = 0 ;

                  break ;
      case i3:
               bh = xLoad_from_i2c ( i2c_str->size  , i2c_str->addr_i2c , i2c_str->addr_mem ,i2c_str->chip_addr) ;
               goto read;
    }

  return ;
}
