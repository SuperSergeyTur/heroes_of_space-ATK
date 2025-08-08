void NetPult_Drive ( void )
{

      if ( M_FirstCall == 1 )  /*  Идентификация первого входа для задания  */
        {                      /* начального условия ...                    */
          M_FirstCall = 0 ;
          output_s ( _NetSetab_prompt ) ;
          output_c ( '\r' ) ;
          output_c ( '\n' ) ;

          m_index = 1;
          output_s( AWelcome );
          output_s ( _Net_Cfg_prompt ) ;
          output_c ( '\r' ) ;
          Label = 0 ;

        }

      switch ( Label )
      {
        default:
                while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      output_c ( '\n' ) ;
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( ++m_index > _NumNetInd ) m_index = 1 ;
                      Label = 11 ;
                    }    /* переход к следующей настройке */
                  else if ( m_ch == Up ) /* Изменить номер индицируемой переменной.*/
                    {
                      if ( m_index-- == 1 ) m_index = _NumNetInd ;
                      Label = 11 ;
                    }
                  else if ( m_ch == Enter )
                    {
                      output_c ( '\n' ) ;
                      Label = m_index ;
                    }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                }
            break;
        case 11 :
              if (  TestCompleted_Output() )
                {
                  output_c( '\r');
                  output_s( AWelcome );
                  switch ( m_index )
                  {
                    case 1 :
                        output_s( _Net_Cfg_prompt );
                        break;
                    case 2 :
                        output_s( _Net_Ust_prompt );
                        break;
                    case 3 :
                        output_s( _Net_Ind_prompt );
                        break;
                  }

                  Label = 0 ;
                  break ;
                }

            break;
        case 1 :
//            Label = NetSetab_Bit_Drive();

            break;
        case 2 :
            Label = NetSetab_Drive();

            break;
        case 3 :
//            Label = NetIndicator_Drive();

            break;

      }

 Restart_Output ()  ;

}

byte NetSetab_Drive( void )
{
  static byte Label1 = 0 ;
  register  word    ax , bx , cx , ex ;
  byte  sig_old;
  register  lword  lax ;


   switch ( Label1 )
   {
    default:
    case 5 :
            //   Если вывод не поспевает за нажатиями клавиш
            // "больше/меньше", то производится обработка нескольких
            // нажатий за время одного вывода.
            //  Пропуск вывода, если не завершен предыдущий вывод, и
            // переход к обработке нажатий клавиш.
          if (  TestCompleted_Output() )
            {    /*  Вывод заданной строки меню. */
              if ( Label != 205 )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( NetVar.NetUst[m_addr].text ) ;
/* */                  Label1 = 10 ;
        output_c( '0' ) ;
        while ( !TestCompleted_Output() )  ;
                }
              else
                {
                  // Вывод значения ячейки соответствующей данной строке меню.
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
        output_c( '5' ) ;
        while ( !TestCompleted_Output() )  ;

                        // для 'word' все равно: со знаком или без.
                  if ( NetVar.NetUst[m_addr].code._.type == 2 )  ax = *(w*)NetVar.NetUst[m_addr].addr ;
                  else
                  {     // для 'byte' не все равно: со знаком или без.
                    ax = *(sb*)NetVar.NetUst[m_addr].addr ;
                    if ( NetVar.NetUst[m_addr].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение.
                  }
                  cx = *(w*)NetVar.NetUst[m_addr].abs_nom;
                  bx = NetVar.NetUst[m_addr].nom ;
                  if ( NetVar.NetUst[m_addr].code._.off_sign == 0 )
                  {    // Если распечатка со знаком - выделяем знак и модуль.
                    if ( (sw)ax >= 0 )    sig_old = '+' ;
                    else   ax = ~ax + 1 , sig_old = '-' ;
                  }
                  /*if ( Ustav[m_index].adr_Gruop[m_addr].code._.type == 2 )  ax = *(w*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  else                          ax = *(b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  cx = *(w*)Ustav[m_index].adr_Gruop[m_addr].abs_nom;
                  bx = Ustav[m_index].adr_Gruop[m_addr].nom ;
                  if ( (sw)ax >= 0 )    sig_old = '+' ;
                  else   ax = ~ax + 1 , sig_old = '-' ;*/

                    // приводим содержимое ячейки к его номиналам.
                       /* для отображения уставок типа '1/x' */
                   if (NetVar.NetUst[m_addr].code._.invert == 1 )
                   {  // меняем местами ax и bx для инверсного деления.
                     ex = ax , ax = bx, bx = ex ;
                   }
                   lax =  (lw)ax*(lw)cx;
                   m_time = lax%bx;
                   *(w*)&m_buff[0] = bx;
                   lax /=bx;
                   if(lax > 0xffffu) lax = 0xffff;
                   //lax &= 0xffff ;   // очищаем остаток.

                             // распечатка целой части - максимум 5 символов.
                      ex = 5 - NetVar.NetUst[m_addr].code._.celoe ; //сколько первых символов пропустить
                      if ( ex == 5 ) ex = 2 ; // для совместимости - если заданы были нули то принимаем формат "3.2".
                      else if ( (sw)ex < 0 ) ex = 0 ;
                      for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                      {
                        bx = lax / ax ;
                        lax %= ax;
                            // пока идут первые нули - не выводим их:
                        if ( bx == 0 && cx == 0 )
                        {     // а пропускаем лишние нулевые символы,
                          if ( ex != 0 ) ex-- ;
                             // или заменяем пробелами.
                          else  output_c (' ') ;
                        }
                        else
                        {
                          if(cx == 0)
                          {
                            if ((NetVar.NetUst[m_addr].code._.zapr == 1)&& (_Ne_Rabota == 0) ) output_c ( '#' ) ;
                            if ( (NetVar.NetUst[m_addr].code._.off_sign == 0) ) output_c ( sig_old ) ;
                            cx = 1 ;
                          }
                           // первые нули закончились.
                          output_c ( (b)bx + 0x30 ) ;
                        }
                      }   // распечатываем последнюю цифру.
                      if(cx == 0)
                      {
                        if ((NetVar.NetUst[m_addr].code._.zapr == 1)&& (_Ne_Rabota == 0) ) output_c ( '#' ) ;
                        if ( (NetVar.NetUst[m_addr].code._.off_sign == 0) ) output_c ( sig_old ) ;
                      }
                      //if ( (Ustav[m_index].adr_Gruop[m_addr].code._.off_sign == 0) && (cx == 0) ) output_c ( sig_old ) ;
                      output_c ( (b)(w)lax + 0x30 ) ;
/* */                     Label1 = 15 ;
                     break;
            case 15:    // распечатка дробной части
                      if ( NetVar.NetUst[m_addr].code._.celoe == 0 ) ex = 2 ;// по умолчанию.
                      else ex = NetVar.NetUst[m_addr].code._.drob ;
                      if ( ex != 0 )
                      {
                        output_c ( '.' ) ;
                        bx = *(w*)&m_buff[0] ;
                        lax = m_time ; // восстанавливаем остаток.
                        for ( ; ex != 0 ; ex-- )
                        {
                          lax*=10  ;
                          ax = lax/bx ;
                          lax %= bx;
                            output_c ( (b)ax + 0x30 ) ;
                        }
                      }
                      output_s ( NetVar.NetUst[m_addr].ch ) ;
                      if ((NetVar.NetUst[m_addr].code._.zapr == 1) && (_Ne_Rabota == 0) ) output_c ( '#' ) ;

/* */                  Label1 = 20 ;// для режима изменения выбранной уставки
                }
              break ;
            }
          if ( Label1 != 5 ) // Режим выбора уставок.
            {
     case 10: while (  TestData_for_Input() )
                {
        output_c( '1' ) ;
        while ( !TestCompleted_Output() )  ;
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
//                      M_FirstCall = 1 ;
                      return 0 ;   // добавить еще какую-то иниц.
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
/* */                Label1 = 0;
              }

              break ;
            //-------------------

     case 16: //output_c ( '\n' ) ;
        output_c( '7' ) ;
        while ( !TestCompleted_Output() )  ;
              output_c ( '\r' ) ;
              output_s( AWelcome );
              output_s ( NetVar.NetUst[m_addr].text ) ;
/* */              Label1 = 17 ;
              break;
     case 17:while (  TestData_for_Input() )
                {
        output_c( '2' ) ;
        while ( !TestCompleted_Output() )  ;
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
      case 18:        //if ( (kol == 1) || (_MaxNumUstav == 1) ) goto out;
                      output_s ( _Net_Ust_prompt ) ;
                      output_c ( '\n' ) ;
/* */                      Label1 = 0;
                      m_addr = 0;
                      break ;   // добавить еще какую-то иниц.
                    }
                  else if ( m_ch == Down ) /* Перейти к другому пункту меню.*/
                    {
                      do
                      {
                        if ( ++m_addr >= NetNumUst ) m_addr = 0 ;
                      }
                      while ((NetVar.NetUst[m_addr].mask & _N_prog) == 0 );
/* */                      Label1 = 16 ;
                    }
                  else if ( m_ch == Up ) /* Перейти к другому пункту меню.*/
                    {
                      do
                      {
                        if ( m_addr-- == 0 ) m_addr = NetNumUst - 1 ;
                      }
                      while ((NetVar.NetUst[m_addr].mask & _N_prog) == 0 );
/* */                      Label1 = 16 ;
                    }
                  else if ( m_ch == Enter ) // перейти в режим изменения уставки
                    {
        output_c( '3' ) ;
        while ( !TestCompleted_Output() )  ;
                      // Запоминание первоначального значения уставки.
                  if ( NetVar.NetUst[m_addr].code._.type == 2 )  m_ext = *(w*)NetVar.NetUst[m_addr].addr ;
                      else                          m_ext = *(b*)NetVar.NetUst[m_addr].addr ;
                      output_c ( '\n' ) ;
/* */                      Label1 = 5 ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
/* */                Label1 = 16;
              }

              break ;
          }
        else   // Режим изменения выбранной уставки.
          {
     case 20: while (  TestData_for_Input() )
                {     // Считывание уставки для ее последующего изменения.
                        // для 'word' все равно: со знаком или без.
                  if ( NetVar.NetUst[m_addr].code._.type == 2 )  ax = *(w*)NetVar.NetUst[m_addr].addr ;
                  else                        //  ax = *(b*)Ustav[m_index].adr_Gruop[m_addr].addr ;
                  {     // для 'byte' не все равно: со знаком или без.
                    ax = *(sb*)NetVar.NetUst[m_addr].addr ;
                    if ( NetVar.NetUst[m_addr].code._.off_sign == 1 ) ax &= 0x00FF ; // срезаем знаковое расширение.
                  }
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      ax = m_ext ;  // Восстановление прежнего значения уставки.
                      output_s ( "\n\r" ) ;
/*??? */                     output_s ( _Net_Ust_prompt ) ;
                      output_c ( '\n' ) ;
                      if ( NetNumUst == 1 )
                      {
/* */                        Label1  = 18;
                      }
/* */                      else Label1 = 16 ;

                    }
                  else if ( m_ch == Enter ) // Записать копию уставки в память в уставку.
                    {
        output_c( '4' ) ;
        while ( !TestCompleted_Output() )  ;
                      output_s ( "\n\r" ) ;
/*???*/                     output_s ( _Net_Ust_prompt ) ;
                      output_c ( '\n' ) ;
                      if ( NetNumUst == 1 )
                      {
/* */                        Label1  = 18;
                      }
/* */                      else Label1 = 16 ;       // Вернуться к перебору уставок.
                    }
                  else if ((NetVar.NetUst[m_addr].code._.zapr == 0)|| (_Ne_Rabota == 1) )
                  {
                    if ( m_ch == Up )   /* Увеличить грубо копию уставки.*/
                    {
                      if (NetVar.NetUst[m_addr].code._.invert == 1 ) goto down ;
                 up:  cx = ax ; // сохраняем предыдущее значение.
                      ax += NetVar.NetUst[m_addr].dX ;
                      bx  = NetVar.NetUst[m_addr].max ;
                       //  Если распечатка без знака то число рассматриваем
                      //  как беззнаковое в диапазоне 0...65535.
                      if ( NetVar.NetUst[m_addr].code._.off_sign == 0 )
                      {    //  со знаком.
                           //  Защита на случай переваливания через max, если
                           // max задан 0xFFFF (для беззнаковых) или 0x7FFF
                           // (для знаковых), т.к. в этих случаях ограничение
                           // по обычному алгоритму не может работать.
                        if ( (sw)ax < (sw)cx ) ax = bx ; // если после сложения число
                           // стало меньше чем до, значит произошло переваливание.
                        if ( (sw)ax > (sw)bx ) ax = bx ;
                      }
                      else
                      {    // без знака.
                        if ( (w)ax < (w)cx ) ax = bx ; // если после сложения число
                           // стало меньше чем до, значит произошло переваливание.
                        if ( (w)ax > (w)bx ) ax = bx ;
                      }
/* */                      Label1 = 5 ;
                    }
                    else if ( m_ch == Down ) /* Уменьшить грубо копию уставки.*/
                    {
                      if (NetVar.NetUst[m_addr].code._.invert == 1 ) goto up ;
                 down:cx = ax ; // сохраняем предыдущее значение.
                      ax -= NetVar.NetUst[m_addr].dX ;
                      bx  = NetVar.NetUst[m_addr].min ;
                      //if ( (sw)(ax -= Ustav[m_index].adr_Gruop[m_addr].dX ) < (sw)Ustav[m_index].adr_Gruop[m_addr].min ) ax = Ustav[m_index].adr_Gruop[m_addr].min ;
                      if ( NetVar.NetUst[m_addr].code._.off_sign == 0 )
                      {    //  со знаком.
                           //  Защита на случай переваливания через min, если
                           // min задан 0x0000 (для беззнаковых) или 0x8000
                           // (для знаковых), т.к. в этих случаях ограничение
                           // по обычному алгоритму не может работать.
                        if ( (sw)ax > (sw)cx ) ax = bx ; // если после вычитания число
                           // стало больше чем до, значит произошло переваливание.
                        if ( (sw)ax < (sw)bx ) ax = bx ;
                      }
                      else
                      {    // без знака.
                        if ( (w)ax > (w)cx ) ax = bx ; // если после вычитания число
                           // стало больше чем до, значит произошло переваливание.
                        if ( (w)ax < (w)bx ) ax = bx ;
                      }
/* */                      Label1 = 5 ;
                    }
                    else
                    {
                      Klav_Buff = m_ch;
                    }

                  }
                  else
                    {
                      Klav_Buff = m_ch;
                    }
                    // Выдача в уставку ее измененного или неизмененного значения.
                  if ( NetVar.NetUst[m_addr].code._.type == 2 )  *(w*)NetVar.NetUst[m_addr].addr = ax ;
                  else                          *(b*)NetVar.NetUst[m_addr].addr = ax ;
                }
              if (AWelcome != AWell_old )
              {
                AWell_old = AWelcome;
/* */                Label1 = 5;
              }

              break ;
            //-------------------
          }
   }

  return 2 ;

}

