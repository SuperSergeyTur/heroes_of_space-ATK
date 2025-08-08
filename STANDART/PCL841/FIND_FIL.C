word  find_in_file ( FILE *fp, char *ptr )
{
  byte data, label = 0 , index ;

     //   Устанавливаем указатель на начало файла, чтобы
     // для каждой новой переменной просмотр вести с начала файла.
  fseek(fp, 0L, SEEK_SET);

  while (1)
    {
      data=getc(fp)  ;

      if ( data == (b)EOF) // проверяем на конец файла.
        {
          return 0 ;
        }
      switch ( label )
      {
        case 0 : // ищем строку начинающуюся с '#' и содержащую имя параметра.
          if ( data == '#') label = 1 ;
          break;

        case 1 : // отсеиваем в строке все пробелы.
          if ( data == ' ') break;
          index = 0, label = 2 ;

        case 2 : // ищем в строке заданную последовательность символов.
          if ( data == ptr[index] )
            {
              if ( ptr[++index] == NULL ) label = 3 ;
            }
          else label = 0 ;
          break;

        case 3 :  //  проверяем, что имя параметра закончилось пробелом или
                  // возвратом каретки.
          if ( data != ' ' )
          {
            if ( data == '\n' ) return 1 ;
            label = 0 ;
          }
          label = 4 ;
          break;

        case 4 :  // ищем конец строки.
          if ( data == '\n' ) return 1 ;
          break;
      }
    }

}

