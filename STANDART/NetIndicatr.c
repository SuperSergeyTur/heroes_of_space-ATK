
//         ПРОГРАММЫ ИНДИКАЦИИ СОДЕРЖИМОГО ВЫБРАННОЙ ИЗ СПИСКА ЯЧЕЙКИ.
//------------------------------------------------------------------

/*   Режим доступен и из "Готовности" и из "Работы".
 *   Программа осуществляет индикацию содержимого выбранного из таблицы
 * параметра в его номиналах в десятичной форме со знаком.
 *   Функции:
 * - выбор, из таблицы путем перебора , индицируемого параметра;
 * - индикация выбранного параметра в его номиналах в десятичной форме со
 *   знаком.
 *   Клавиши:
 * - "+" в режиме выбора параметра - выбор параметра ;
 * - "Enter" в режиме выбора - переход к индикации ;
 * - "Esc" в режиме индикации - переход к режиму выбора ;
 * - "Esc" в режиме выбора - возврат в диспетчер.
 */
//   Тип параметров задаваемых в таблице интерпретирутся программой при их
// отображении в символьном виде, как знаковый двухбайтный в дополнительном
// коде.  Поэтому задаваемый параметр должен иметь формат типа "sword", либо
// формат типа "word" но при этом не выходить за диапазон "0...+32767" .


void NetIndicator_Drive ( void )
{
   register word    ax , bx , cx, ex ;
   byte    all_sig;
   register lword  lax;

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
              Label = 100 ;
              m_index = 0 ;
              m_addr  = 0 ;
          if (S_break == 0  ) S_break = 200;

          return ;
        }

  switch ( Label )
    {
      default:
      case 100:
              output_s ( _NetIndicatr_prompt ) ;
              output_c ( '\n' ) ;
              if (NetNumInd <= 1 )  goto asd1;
               else goto asd;
              //Label = 103 ;
      case 103:
              if (  TestCompleted_Output() )
                {
             asd: output_c( '\r');
                  output_s( AWelcome );
                  output_s ( NetIndicat[m_index].gruppa ) ;
                  Label = 105 ;
                  break ;
                }

      case 105:
                if ( S_break == 107 ) goto enter ;
                  //----
                while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
      case 107:       output_c ( '\n' ) ;
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      S_break = 0;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_index >= NetNumInd ) m_index = 0 ;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( m_index-- == 0 ) m_index = NetNumInd - 1 ;
                      Label = 103 ;
                    }
                  else if ( m_ch == Enter )
                    {
             enter:   output_c ( '\n' ) ;
                      Label = 200 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }

                if ( (AWelcome != AWell_old) && (S_break != 107) )
                {
                  AWell_old = AWelcome;
                  Label = 103;
                }
              break ;
            //-------------------
      case 200:
                 // Пропуск вывода, если не завершен предыдущий вывод.
              if (  TestCompleted_Output() )
                {
         asd1:    output_c( '\r');
                  output_s( AWelcome );
                  output_s (NetIndicat[m_index].adr_Gruop[m_addr].text ) ;
                  Label = 205 ;
                  break ;
                }
      case 205 :
               if ( S_break == 107 ) goto enter1;

               while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                        m_addr = 0;
                        if (NetNumInd <= 1 ) Label = 107;
                        else Label = 100;

                        break;
                    }
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_addr >=  NetIndicat[m_index].kol_vo ) m_addr = 0 ;
                      Label = 200 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( m_addr-- == 0 ) m_addr =  NetIndicat[m_index].kol_vo - 1 ;
                      Label = 200 ;
                    }
                  else if ( m_ch == Enter )
                    {
             enter1:   output_c ( '\n' ) ;
                      Label = 23 ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }

                if ( (AWelcome != AWell_old) && (S_break != 107) )
                {
                  AWell_old = AWelcome;
                  if (NetNumInd <= 1 )  Label = 100;
                  else Label = 103;
                }
              break ;

      case 23:
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  for ( m_ext = 0 ; m_ext < 2 ; m_ext++ )
                  {
                    if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.type == 1 )  ax = *(b*)NetIndicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else        ax = *(w*)NetIndicat[m_index].adr_Gruop[m_addr].adr[m_ext];
                         // распечетка в 10-тичном виде.
                    if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.print_type == 0 )
                    {
                      bx = NetIndicat[m_index].adr_Gruop[m_addr].nom[m_ext]  ;
                      cx = *NetIndicat[m_index].adr_Gruop[m_addr].abs_nom[m_ext]  ;
                      if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )
                      {
                        if ( (sw)ax >= 0 )    all_sig = '+' ;
                        else   ax = ~ax + 1 , all_sig = '-' ;
                      }
                        // приводим содержимое ячейки к его номиналам.
                      //Если величина в абсолютных единицах, то вычисляем по пропорции
                      // abs_nom*ax/diskr_nom
                       /* для отображения уставок типа '1/x' */
                       if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.invert == 1 )
                       {  // меняем местами ax и bx для инверсного деления.
                         ex = ax , ax = bx, bx = ex ;
                       }
                       lax = (lw)ax * (lw)cx ;
                       *(w*)&m_buff[3] = lax%bx  ;    //сохраняем остаток.
                       *(w*)&m_buff[0] = bx;
                       lax /= bx;

                       if ( lax > 0xffff ) lax = 0xffff;

                      //lax &= 0xffff; // очищаем остаток.

                                  // распечатка целой части - максимум 5 символов.
                      ex = 5 - NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe ; //сколько первых символов пропустить
                      if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                      else if ( (sw)ex < 0 ) ex = 0 ;
                      for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                          {
                            bx =  lax/ax  ;
                            lax %=ax ;
                                // пока идут первые нули - не выводим их:
                            if ( bx == 0 && cx == 0 )
                            {     // а пропускаем лишние нулевые символы,
                              if ( ex != 0 ) ex-- ;
                                  // или заменяем пробелами.
                              else  output_c (' ') ;
                            }
                            else
                            {
                              if ((cx == 0) && ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                              cx = 1 ; // первые нули закончились.
                              output_c ( (b)bx + 0x30 ) ;
                            }
                          }

                          if ((cx == 0) && ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                          // распечатываем последнюю цифру.
                          output_c ( (b)(w)lax + 0x30 ) ;
                          Label = 15 ;
                          return;

                case 15:
                          // распечатка дробной части
                            if  (NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe == 0)
                            {
                             ex = 2 ;
                            }
                            else ex = NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.drob ;
                            if ( ex != 0 )
                            {
                              output_c ( '.' ) ;
                              bx = *(w*)&m_buff[0] ;
                              lax =*(w*)&m_buff[3]  ; // восстанавливаем остаток.
                              for ( ; ex != 0 ; ex-- )
                              {
                                 ax = lax*10  ;
                                   lax = ax % bx         ;
                                   ax /= bx;
                                output_c ( (b)(w)ax + 0x30 ) ;
                              }
                            }
                    }    // распечетка в 16-ричном виде.
                    else //if ( Nind[m_index].code[m_ext]._.print_type == 1 )
                    {
                      if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.type == 1 ) cx = 1 ;
                      else                                         cx = 3 ;
                      for ( ; (signed char) cx >= 0 ; cx -- )
                      {
                        bx = (b)( ax >> 4u*cx ) & 0x0fu ;
                        if ( bx <= 0x9 ) bx += 0x30 ;
                        else
                        {       // маленькие/большие буквы.
                          if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 ) bx += 0x57u ;
                          else                                             bx += 0x37u ;
                        }
                        output_c ( bx ) ;
                      }
                    }
                    output_s ( NetIndicat[m_index].adr_Gruop[m_addr].txt2[m_ext] ) ;
                    if  (NetIndicat[m_index].adr_Gruop[m_addr].txt2[1]==0)  m_ext++;
                    Label = 16 ;// выход перед выводом следующей переменной.
                    return ;
                  case 16:; // продолжаем цикл.
                  }
                  Label = 23 ;// возвращаемся к прежней метке.
                  m_time = Timer1_Ovr ;
                }
              while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;

                  // Куда перейдем по Return определяется тем как мы вошли в
                  // программу, если из диспетчера - то в перебор параметров,
                  // а если из скринсейвера - то в диспетчер

                  if ( m_ch == Return )
                  {
                    output_s ( "\n\r" ) ;
                    if (NetNumInd <= 1 )
                    {
                     output_s ( _NetIndicatr_prompt ) ;
                     output_c ( '\n' ) ;
                    }
                    else
                    {
                     output_s ( NetIndicat[m_index].gruppa ) ;
                     output_c ( '\n' ) ;
                    }
                    Label = S_break ;
                  }
                  else
                    {
                      Klav_Buff = m_ch;
                    }

                }
              break ;
            //-------------------
      }

  Restart_Output ()  ;

  return ;
}

