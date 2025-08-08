
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


void Indicator_Drive ( void )
{
   register word    ax , bx , cx, ex ;
   byte    all_sig ;
   register lword  lax, lbx ;
   double   dax ;
   word t_ax, indic_ax;

   if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
   {                      /* начального условия ...                    */
     M_FirstCall = 0 ;
     Label = 100 ;
     m_index = 0 ;
     m_addr  = 0 ;
#ifdef _Cursor_Off
     SendEasyCommandToPult(_Cursor_Off);
#endif
     
     ListIndic = 0;
     if (S_break == 0  ) S_break = 200;
     // Отображение индикации в меню А0 согл. номер группы в А6 (Indicat[]),
     // где _A6_group_obj - номер группы в A6,  _A6_param_obj - номер параметры в массиве _A6_group_obj
#ifdef _A6_group_obj
     if (S_break == 107)
     {
       m_index = _A6_group_obj ;
       m_addr  = _A6_param_obj ;
     }
#endif
     return ;
   }
   
   switch ( Label )
    {
      default:
      case 100:
              output_s ( _Indicatr_prompt ) ;
              output_c ( '\n' ) ;
              if (_NumInd <= 1 )  goto asd1;
               else goto asd;
              //Label = 103 ;
      case 103:
              if (  TestCompleted_Output() )
                {
             asd: output_c( '\r');
                  output_s( AWelcome );
                  output_s ( Indicat[m_index].gruppa ) ;
                  Label = 105 ;
                  break ;
                }

      case 105:
                if ( S_break == 107 ) goto enter ;
                  //----
   #ifdef _INTERPRETER
                if    ( Str_quant.VarInd ==0) t_ax=_NumInd-1 ;
                else                          t_ax=_NumInd ;
   #else
                t_ax = _NumInd;
   #endif
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
//#ifdef _INTERPRETER
//             if    ( Str_quant.VarInd ==0) t_ax=_NumInd-2 ;
//             else                          t_ax=_NumInd-1 ;
//#endif
                      if ( ++m_index >= t_ax ) m_index = 0;
                      Label = 103 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( m_index-- == 0 ) m_index = t_ax-1; //_NumInd - 1 ;
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
                  output_s (Indicat[m_index].adr_Gruop[m_addr].text ) ;
                  Label = 205 ;
                  //break ;  КВВ: перенес ниже 6-12-13
                }
              else if (ListIndic == 1)
                {
                  output_c( '\r');
                  output_s( AWelcome );
                  output_s (Indicat[m_index].adr_Gruop[m_addr].text ) ;
                  Label = 205 ;
                }
                
            if (ListIndic == 0)
              break ;  // КВВ: перенес с выше, т.к. при поочередном выводе в "А0-Сообщ." пропускался иногда вывод наименования параметров

      case 205 :
               if ( S_break == 107 ) goto enter1;

#ifdef _INTERPRETER
                if ( m_index==_NumInd-1) { /* Indicat.kol_vo*/ t_ax = Str_quant.VarInd;      }
                else   t_ax = Indicat[m_index].kol_vo;
#else
                t_ax = Indicat[m_index].kol_vo;
#endif

                while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                        m_addr = 0;
                        if (_NumInd <= 1 ) Label = 107;
                        else Label = 100;

                        break;
                    }
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_addr >=  /*Indicat[m_index].kol_vo*/ t_ax ) m_addr = 0 ;
                      Label = 200 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( m_addr-- == 0 ) m_addr = t_ax-1;  /*Indicat[m_index].kol_vo - 1 ;*/
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
                  if (_NumInd <= 1 )  Label = 100;
                  else Label = 200;

                /*  ФАА 13.06.16
                 * если выходить на Label = 103 после смены символа AWelcome , тогода m_addr остается прежним и при выборе
                 * другого подменю "m_index" с меньшим колич. парам. мы обращаемся к несуществующему массиву и контроллер виснет
                 *
                  if (_NumInd <= 1 )  Label = 100;
                  else Label = 103;
                */
                }

            if (ListIndic == 1)
              {
                Label = 23;
              }
            if (ListIndic == 0)
              break ;

      case 23:

                if (ListIndic == 1){
                  if(TestCompleted_Output())
                   { output_c ( '\n' ) ;
                    ListIndic = 0;}
                }
            
                 // Ожидание завершения предыдущего вывода + тактирование,
              if  ( (  TestCompleted_Output() )    // чтобы не мельтешило.
                    && (( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) || ListIndic == 1) )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  for ( m_ext = 0 ; m_ext < 2 ; m_ext++ )
                  {
                  ax = Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.type ;
                  if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 || ax == 0 )
                  {
                    if      ( ax == 1 ) lbx = (slw)(sw)*( sb*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 2 ) lbx = (slw)    *( sw*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 3 ) dax =      ( d)*(  f*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 4 ) lbx =          *(slw*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 0 ) dax =          *(  d*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                  }
                  else
                  {
                    if      ( ax == 1 ) lbx = ( lw)( w)*(  b*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 2 ) lbx = ( lw)    *(  w*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 3 ) dax =      ( d)*(  f*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else if ( ax == 4 ) lbx =          *( lw*)Indicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;                    
                  }
                         // распечатка в <double> виде.
                    if (( ax == 0 )||(ax == 3))
                    {
                      bx = Indicat[m_index].adr_Gruop[m_addr].nom[m_ext]  ;
                      cx = *Indicat[m_index].adr_Gruop[m_addr].abs_nom[m_ext]  ;
                     // if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )
                      {
                        if (  dax >= 0 )  all_sig = '+' ;
                        else  dax *= -1.0, all_sig = '-' ;
                      }
                        // приводим содержимое ячейки к его номиналам.
                      //Если величина в абсолютных единицах, то вычисляем по пропорции
                      // abs_nom*ax/diskr_nom
                       /* для отображения уставок типа '1/x' */
                       //if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.invert == 1 )
                       //{  // меняем местами ax и bx для инверсного деления.
                         //ex = lbx , lbx = (lw)bx, bx = ex ;                     //  Для 4-х байтных не продумывалось
                       //}

                       dax = dax * (d)cx ;
                       dax = dax / (d)bx ;
                       if (dax > (d)(0xffffffffL) ) dax = (d)(0xffffffffL) ;    // В отличие от алгоритма для целочисленных переменных
#ifdef _CM3_
                       if ((dax != INFINITY)&&(dax != NAN))
#endif                       
                       {
                          lax = (lw)dax ;                                    //  здесь сохраняем не остаток, а уже готовую `double`-дробную часть.
                          m_dax = dax - (d)lax ;    //сохраняем дробь.
                         
                                     // распечатка целой части - максимум 5 или 10 символов.
                               //  для 2-х и 4-х байтных начинаем с разных делителей, чтобы сократить итерации.
                         lbx = 1000000000ul, ax = 10 ;
                         ex = ax - Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe ; //сколько первых символов пропустить
                         if ( (sw)ex < 0 ) ex = 0 ;

                         for ( cx = 0 ; lbx != 1 ; lbx /= 10 )
                          {

                            bx   = lax/lbx  ;
                            lax %= lbx ;
                                // пока идут первые нули - не выводим их:
                            if ( bx == 0 && cx == 0 )
                            {     //   пропускаем лишние нулевые символы,
                              if ( ex != 0 ) ex-- ;
                                  // или заменяем пробелами.
                              else  output_c (' ') ;
                            }
                            else
                            {
                              if ((cx == 0) && ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                              cx = 1 ; // первые нули закончились.
                              output_c ( (b)bx + 0x30 ) ;
                            }
                          }

                          if ((cx == 0) && ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                          // распечатываем последнюю цифру.
                          output_c ( (b)(w)lax + 0x30 ) ;
                          Label = 151 ;
                          return;

                case 151:
                          // распечатка дробной части
                           ex = Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.drob ;
                          if ( ex != 0 )
                            {         output_c ( '.' ) ;

                              for ( ; ex != 0 ; ex-- )
                              {
                                m_dax *= 10 ;
                                ax = (w)m_dax  ;     //выделение целой части дроби
                                output_c ( (b)(w)ax + 0x30 ) ;
                                m_dax -= (d)ax ;    //сдвиг дроби

                              }
                             }
                       }
#ifdef _CM3_
                       else
                       {
                         //Число INFINITY или NAN
                         if (dax == INFINITY)
                         {
                           output_s ( "INF " ) ;
                         }
                         else
                         {
                           output_s ( "NAN " ) ;
                         }
                       }
#endif                       
                    }
                                 // распечатка в 10-тичном виде.
                    else if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.print_type == 0 )
                    {
                      bx = Indicat[m_index].adr_Gruop[m_addr].nom[m_ext]  ;
                      cx = *Indicat[m_index].adr_Gruop[m_addr].abs_nom[m_ext]  ;
                      if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )
                      {
                        if ( (slw)lbx >= 0 )    all_sig = '+' ;
                        else   lbx = ~lbx + 1 , all_sig = '-' ;
                      }
                        // приводим содержимое ячейки к его номиналам.
                      //Если величина в абсолютных единицах, то вычисляем по пропорции
                      // abs_nom*ax/diskr_nom
                       /* для отображения уставок типа '1/x' */
                       if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.invert == 1 )
                       {  // меняем местами ax и bx для инверсного деления.
                         ex = lbx , lbx = (lw)bx, bx = ex ;                     //  Для 4-х байтных не продумывалось
                       }

                     if ( ax != 4 )  // для word byte: преобразование целочисленное
                     {
                       lax = (lw)lbx * (lw)cx ;
                       *(w*)&m_buff[3] = lax%bx ;    //сохраняем остаток.
                       *(w*)&m_buff[0] = bx ;
                       lax /= bx;
                     }
                     else   // для lword: преобразование double чтобы избежать переполнения при первом умножении
                     {
                       dax = (d)lbx * (d)cx ;

                       m_dax = dax / (d)bx ;     //   Контроль переполнения.
                       if ( m_dax > (d)(lw)0xffffffff )  m_dax = (lw)0xffffffff,  dax = (d)bx * m_dax ;

                       lax = (lw)m_dax ;
                       *(w*)&m_buff[3] = dax - (d)lax * (d)bx ;     // В отличие от алгоритма для double-переменных
                       *(w*)&m_buff[0] = bx ;                      //  здесь сохраняем не `double`-дробную часть, а остаток.
                     }
                      //Vit 4-11-11  if ( lax > 0xffff ) lax = 0xffff;

                      //lax &= 0xffff; // очищаем остаток.

                                  // распечатка целой части - максимум 5 или 10 символов.
                            //  для 2-х и 4-х байтных начинаем с разных делителей, чтобы сократить итерации.
                      if ( ax != 4 )  lbx =      10000ul, ax =  5 ;
                      else            lbx = 1000000000ul, ax = 10 ;
                      ex = ax - Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe ; //сколько первых символов пропустить
                      if ( ex == ax ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                      else if ( (sw)ex < 0 ) ex = 0 ;

                      for ( cx = 0 ; lbx != 1 ; lbx /= 10 )
                          {
                            bx   = lax/lbx  ;
                            lax %= lbx ;
                                // пока идут первые нули - не выводим их:
                            if ( bx == 0 && cx == 0 )
                            {     //   пропускаем лишние нулевые символы,
                              if ( ex != 0 ) ex-- ;
                                  // или заменяем пробелами.
                              else  output_c (' ') ;
                            }
                            else
                            {
                              if ((cx == 0) && ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                              cx = 1 ; // первые нули закончились.
                              output_c ( (b)bx + 0x30 ) ;
                            }
                          }

                          if ((cx == 0) && ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                          // распечатываем последнюю цифру.
                          output_c ( (b)(w)lax + 0x30 ) ;
                          Label = 15 ;
                          return;

                case 15:
                          // распечатка дробной части
                            if  (Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe == 0)
                            {
                             ex = 2 ;
                            }
                            else ex = Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.drob ;
                            if ( ex != 0 )
                            {
                              output_c ( '.' ) ;
                              bx = *(w*)&m_buff[0] ;
                              lax =*(w*)&m_buff[3] ; // восстанавливаем остаток.
                              for ( ; ex != 0 ; ex-- )
                              {
                                 lbx = lax*10  ;
                                   lax = lbx % bx ;
                                   ax  = lbx / bx ;
                                output_c ( (b)(w)ax + 0x30 ) ;
                              }
                            }
                    }    // распечатка в 16-ричном виде.
                    else //if ( Nind[m_index].code[m_ext]._.print_type == 1 )
                    {
                      ax = Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.type ;
                      if      ( ax == 1 )  cx = 1 ;
                      else if ( ax == 2 )  cx = 3 ;
                      else if ( ax == 4 )  cx = 7 ;

                      for ( ; (signed char) cx >= 0 ; cx -- )
                      {
                        bx = (b)( lbx >> 4u*cx ) & 0x0fu ;
                        if ( bx <= 0x9 ) bx += 0x30 ;
                        else
                        {       // маленькие/большие буквы.
                          if ( Indicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 ) bx += 0x57u ;
                          else                                                                  bx += 0x37u ;
                        }
                        output_c ( bx ) ;
                      }
                    }
                    output_s ( Indicat[m_index].adr_Gruop[m_addr].txt2[m_ext] ) ;
                    if  (Indicat[m_index].adr_Gruop[m_addr].txt2[1]==0)  m_ext++;
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
                      // ФАА 13.06.16 В данном месте в t_ax хлам
                    //if (/*_NumInd*/t_ax <= 1 )
                    if (_NumInd <= 1 )
                    {
                     output_s ( _Indicatr_prompt ) ;
                     output_c ( '\n' ) ;
                    }
                    else
                    {
                     output_s ( Indicat[m_index].gruppa ) ;
                     output_c ( '\n' ) ;
                    }
                    Label = S_break ;
                  }
                  else if (m_ch == Up){
                    if (Indicat[m_index].kol_vo > 1)
                    {
                      indic_ax = Indicat[m_index].kol_vo;
                      if ( m_addr-- == 0 ) m_addr = indic_ax-1;
                      Label = 200 ;// возвращаемся к прежней метке.
                      ListIndic = 1;
                      output_c ( '\n' ) ;
                    }
                  }
                  else if (m_ch == Down){
                    if (Indicat[m_index].kol_vo > 1)
                    {
                      indic_ax = Indicat[m_index].kol_vo;
                      if ( ++m_addr >=  /*Indicat[m_index].kol_vo*/ indic_ax ) m_addr = 0 ;
                      Label = 200 ;// возвращаемся к прежней метке.
                      ListIndic = 1;
                      output_c ( '\n' ) ;
                    }
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

