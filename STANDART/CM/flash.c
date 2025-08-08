//  Подсчет контрольной суммы блока ОЗУ размером 'n' начиная с адреса
// 'from'.
//  Контрольная сумма записывается в последний байт заданного блока -
// этот байт должен быть зарезервирован под конрольную сумму.

word Chek_sum ( word n , byte *from )
{
  _register lword ax , bx ;
  word cx ;

  ax = (lw)from, bx = 0 , cx = 0 ;
  while ( ax < ( (lw)from + n - 1 ) )
    {
      bx -= *(b*)ax ;  // Подсчет контрольной суммы дл
      ax++;           // всей таблицы кроме последнего байта.
    }
  if ( *(b*)ax != (b)bx )  cx = 1 ;

  *(b*)ax = bx ;  // Запись в последний байт таблицы уставок

   return cx ;
}


//аналог стандартной функции save
word Save_into_i2c(word n,byte *from, lword into, word c_addr)
{
   word ax = 4;
   while ( ax == 4)
   {
      ax = Byte_Relock(n , into, from , 1) ;
   };
   return ax;
}

//замена стандартных функций чтения-записи
word  Byte_Relock ( word n , lword addr_flash ,  byte* adrr_mem , word Save_m)
{
    word bh, ax;
    lword lax;
    byte *source, *destiny;

    ax = 4;
    lax = addr_flash;//+_flash_beg;
    if ( ((lax-1+n) > _Flash_size))
    {
      ax =1;
    }
    else
    {
        switch (i2c_label )
        {
            case 0 :
                    if ( Save_m&0x01 == 1)
                    {
                        source = adrr_mem;
                        destiny = &Flash_Space[lax];
                       /* if (Save_m == 1)
                        {
                          ++i2c_label;
                        }
                        else
                        {*/

                       // }
                    }
                    else
                    {
                        source = &Flash_Space[lax];
                        destiny = adrr_mem;
                    }
                     ax = 0;

                    for ( bh= 0; bh < n;++source, ++destiny, ++bh)
                    {
                      if ((lw)destiny <= (lw)_flash_end)
                        *destiny = *source;
                    }
                    break;
        }

    }

  return ax;
}
