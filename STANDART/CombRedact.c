void comb_redact(void)
{
  word ax, bx, cx, ex; //к уставкам
  register lword lax, lbx;
  byte all_sig;
  static byte fl_smena_zagolovka = 0;    //флаг для смены хоголовка
  static word timer_heading = 0;         //для смены заголовка в режиме редактирования
  static word fl_first_call = 1;         //флаг первого вызова
  static word label = 0;                 //индекс кейса
  static word m_index = 0;               //индекс в меню
  static byte type_ust = 0;              //тип уставки
  static word ind_time = 0;
  double dax, dbx;//float dax, dbx;  VSEV 03.07.2020

  enum
  {
    password1,
    password2,
    heading_menu1,
    menu1,
    indication,
    indication_1,
    indication_2,
    indication_3,
    indication_4,
    indication_5,
    editing,
    out
  };

  if (fl_first_call == 1)
  {
    fl_first_call = 0;
    if (Mon.Password_Ok == 0)
      label = password1;
    else
      label = heading_menu1;
    return;
  }

  switch (label)
  {
  case password1:
    output_s(_NoPassword_txt);
    m_time = Timer1_Ovr;
    label = password2;
    break;

  case password2:
    if ( (u)((w)(Timer1_Ovr - m_time)) > _Time_Password_txt )
      label = out;
    break;

  case out:
    label = 0;
    fl_first_call = 1;
    output_s("\r");
    Pult_Prog_Addr = _MainPultProg;
    break;

  case heading_menu1:
    if (TestCompleted_Output())
    {
      output_s(heading_comb_menu);
      output_s("\n\r");
      output_s(comb_menu[m_index].txt);
      label = menu1;
    }
    break;

  case menu1:
    if (TestCompleted_Output())
    {
      if (TestData_for_Input())
      {
        mInput_c(m_ch);
        if (m_ch == Down)
        {
          if (++m_index >= len_comb_menu)
            m_index = 0;
          output_s("\r");
          output_s(comb_menu[m_index].txt);
        }
        else if (m_ch == Up)
        {
          if (m_index-- == 0)
            m_index = len_comb_menu - 1;
          output_s("\r");
          output_s(comb_menu[m_index].txt);
        }
        else if (m_ch == Enter)
        {
          // Запоминание первоначального значения уставки.
          ax = comb_menu[m_index].code_ust._.type;
          if (comb_menu[m_index].code_ust._.off_sign == 0 || ax == 0)
          {
            if (ax == 1)
              m_dbx = (d) * (sb *)comb_menu[m_index].addr;
            else if (ax == 2)
              m_dbx = (d) * (sw *)comb_menu[m_index].addr;
            else if ( ax == 3 ) 
              m_dbx = (d)*(  f*)comb_menu[m_index].addr;
            else if (ax == 4)
              m_dbx = (d) * (slw *)comb_menu[m_index].addr;
            else if (ax == 0)
              m_dbx = *(d *)comb_menu[m_index].addr;
          }
          else
          {
            if (ax == 1)
              m_dbx = (d) * (b *)comb_menu[m_index].addr;
            else if (ax == 2)
              m_dbx = (d) * (w *)comb_menu[m_index].addr;
            else if ( ax == 3 ) 
              m_dbx = (d)*(  f*)comb_menu[m_index].addr;
            else if (ax == 4)
              m_dbx = (d) * (lw *)comb_menu[m_index].addr;
            else if ( ax == 0 ) 
              m_dbx = *(  d*)comb_menu[m_index].addr;
          }
          label = indication;
        }
        else if (m_ch == Return)
        {
          label = out;
        }
        else
        {
          Klav_Buff = m_ch;
        }
      }
    }
    break;

  case indication:
  {
    output_c('\r');
    output_s(AWelcome);
    ind_time = Timer1_Ovr;
    type_ust = comb_menu[m_index].code_ust._.type;
    if (comb_menu[m_index].code_ust._.off_sign == 0 || type_ust == 0)
    {
      if (type_ust == 1)
        lbx = (slw)(sw) * (sb *)comb_menu[m_index].addr;
      else if (type_ust == 2)
        lbx = (slw) * (sw *)comb_menu[m_index].addr;
      else if ( type_ust == 3 ) 
        dax = ( d)*(  f*)comb_menu[m_index].addr;
      else if (type_ust == 4)
        lbx = *(slw *)comb_menu[m_index].addr;
      else if (type_ust == 0)
        dax = *(d *)comb_menu[m_index].addr;
    }
    else
    {
      if (type_ust == 1)
        lbx = (lw)(w) * (b *)comb_menu[m_index].addr;
      else if (type_ust == 2)
        lbx = (lw) * (w *)comb_menu[m_index].addr;
      else if ( type_ust == 3 ) 
        dax = ( d)*(  f*)comb_menu[m_index].addr;
      else if (type_ust == 4)
        lbx = *(lw *)comb_menu[m_index].addr;
      else if ( type_ust == 0 ) 
        dax = *(  d*)comb_menu[m_index].addr;
    }
    // распечатка в <double> виде.
    if (type_ust == 0 || type_ust == 3)
    {
      bx = comb_menu[m_index].nom_ust;
      cx = *(w *)comb_menu[m_index].abs_nom_ust;
      {
        if (dax >= 0)
          all_sig = '+';
        else
          dax *= -1., all_sig = '-';
      }
      dbx = dax * (d)cx;
      dax = dbx / (d)bx;
      if (dax > (d)(lw)0xffffffff)
        dax = (lw)0xffffffff;
      lax = (lw)dax;
      m_dax = dax - (d)lax; //сохраняем дробную часть.
      lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ust._.celoe; //сколько первых символов пропустить
      if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {
        bx = lax / lbx;
        lax %= lbx;
        // пока идут первые нули - не выводим их:
        if (bx == 0 && cx == 0)
        { //   пропускаем лишние нулевые символы,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // первые нули закончились.
          output_c((b)bx + 0x30);
        }
      }

      if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
        output_c(all_sig);
      // распечатываем последнюю цифру.
      output_c((b)(w)lax + 0x30);
      label = indication_1;
      return;

    case indication_1: // распечатка дробной части  для double
      ex = comb_menu[m_index].code_ust._.drob;
      if (ex != 0)
      {
        output_c('.');
        for (; ex != 0; ex--)
        {
          m_dax *= 10;
          ax = (w)m_dax; //выделение целой части дроби
          output_c((b)(w)ax + 0x30);
          m_dax -= (d)ax; //сдвиг дроби
        }
      }
    }
    else // распечатка в <lword, word и byte> виде.
    {
      bx = comb_menu[m_index].nom_ust;
      cx = *(w *)comb_menu[m_index].abs_nom_ust;
      if (comb_menu[m_index].code_ust._.off_sign == 0)
      { // Если распечатка со знаком - выделяем знак и модуль.
        if ((slw)lbx >= 0)
          all_sig = '+';
        else
          lbx = ~lbx + 1, all_sig = '-';
      }

      // приводим содержимое ячейки к его номиналам.
      /* для отображения уставок типа '1/x' */
      if (comb_menu[m_index].code_ust._.invert == 1)
      { // меняем местами ax и bx для инверсного деления.
        ex = ax, ax = bx, bx = ex;
      }

      if (ax != 4) // для word byte: преобразование целочисленное
      {
        lax = (lw)lbx * (lw)cx;
        m_time = lax % bx; //сохраняем остаток.
        *(w *)&m_buff[0] = bx;
        lax /= bx;
        if (lax > 0xffffu)
          lax = 0xffff;
      }
      else // для lword: преобразование double чтобы избежать переполнения при первом умножении
      {
        dax = (d)lbx * (d)cx;

        dbx = dax / (d)bx; //   Контроль переполнения.
        if (dbx > (d)(lw)0xffffffff)
          dbx = (lw)0xffffffff, dax = (d)bx * dbx;

        lax = dbx;
        m_time = dax - (d)lax * (d)bx; //сохраняем остаток.
        *(w *)&m_buff[0] = bx;
      }
      // распечатка целой части - максимум 5 или 10 символов.
      //  для 2-х и 4-х байтных начинаем с разных делителей, чтобы сократить итерации.
      if (ax != 4)
        lbx = 10000ul, ax = 5;
      else
        lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ust._.celoe; //сколько первых символов пропустить
      if (ex == ax)
        ex = 2; // для совместимости - если заданы были нули то принимаем формат "3.2".
      else if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {
        bx = lax / lbx;
        lax %= lbx;
        // пока идут первые нули - не выводим их:
        if (bx == 0 && cx == 0)
        { // а пропускаем лишние нулевые символы,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // первые нули закончились.
          output_c((b)bx + 0x30);
        }
      } // распечатываем последнюю цифру.
      if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
        output_c(all_sig);
      // распечатываем последнюю цифру.
      output_c((b)(w)lax + 0x30);
      label = indication_2;
      break;

    case indication_2: // распечатка дробной части
      if (comb_menu[m_index].code_ust._.celoe == 0)
        ex = 2; // по умолчанию.
      else
        ex = comb_menu[m_index].code_ust._.drob;
      if (ex != 0)
      {
        output_c('.');
        bx = *(w *)&m_buff[0];
        lax = m_time; // восстанавливаем остаток.
        for (; ex != 0; ex--)
        {
          lbx = lax * 10;
          lax = lbx % bx;
          ax = lbx / bx;
          output_c((b)(w)ax + 0x30);
        }
      }
      label = indication_3; //переходим к выводу  индикации
break;
    }

  case indication_3: //выводим то что в индикации
  {
    output_s("  "); //два пробела между уставкой и индикацией, можно уменьшить до одно пробела/знака при нехватке
    ax = comb_menu[m_index].code_ind._.type;
    if (comb_menu[m_index].code_ind._.off_sign == 0 || ax == 0)
    {
      if (ax == 1)
        lbx = (slw)(sw) * (sb *)comb_menu[m_index].adr;
      else if (ax == 2)
        lbx = (slw) * (sw *)comb_menu[m_index].adr;
      else if ( ax == 3 ) 
        dax = ( d)*(  f*)comb_menu[m_index].adr;
      else if (ax == 4)
        lbx = *(slw *)comb_menu[m_index].adr;
      else if (ax == 0)
        dax = *(d *)comb_menu[m_index].adr;
    }
    else
    {
      if (ax == 1)
        lbx = (lw)(w) * (b *)comb_menu[m_index].adr;
      else if (ax == 2)
        lbx = (lw) * (w *)comb_menu[m_index].adr;
      else if ( ax == 3 ) 
        dax = ( d)*(  f*)comb_menu[m_index].adr;
      else if (ax == 4)
        lbx = *(lw *)comb_menu[m_index].adr;
      else if ( ax == 0 ) 
        dax = *(  d*)comb_menu[m_index].adr;
    }
    // распечатка в <double> виде.
    if (ax == 0 || ax == 3)
    {
      bx = comb_menu[m_index].nom_ind;
      cx = *comb_menu[m_index].abs_nom_ind;
      {
        if (dax >= 0)
          all_sig = '+';
        else
          dax *= -1.0, all_sig = '-';
      }
      dax = dax * (d)cx;
      dax = dax / (d)bx;
      if (dax > (d)(0xffffffffL))
        dax = (d)(0xffffffffL); // ‚ отличие от алгоритма для целочисленных переменных
      lax = (lw)dax;           //  здесь сохраняем не остаток, а уже готовую `double`-дробную часть.
      m_dax = dax - (d)lax;   //сохраняем дробь.

      // распечатка целой части - максимум 5 или 10 символов.
      //  для 2-х и 4-х байтных начинаем с разных делителей, чтобы сократить итерации.
      lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ind._.celoe; //сколько первых символов пропустить
      if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {

        bx = lax / lbx;
        lax %= lbx;
        // пока идут первые нули - не выводим их:
        if (bx == 0 && cx == 0)
        { //   пропускаем лишние нулевые символы,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // первые нули закончились.
          output_c((b)bx + 0x30);
        }
      }

      if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
        output_c(all_sig);
      // распечатываем последнюю цифру.
      output_c((b)(w)lax + 0x30);
      label = indication_4;
      return;

    case indication_4:
      // распечатка дробной части
      ex = comb_menu[m_index].code_ind._.drob;
      if (ex != 0)
      {
        output_c('.');
        for (; ex != 0; ex--)
        {
          m_dax *= 10;
          ax = (w)m_dax; //выделение целой части дроби
          output_c((b)(w)ax + 0x30);
          m_dax -= (d)ax; //сдвиг дроби
        }
      }
    }
    // распечатка в 10-тичном виде.
    else if (comb_menu[m_index].code_ind._.print_type == 0)
    {
      bx = comb_menu[m_index].nom_ind;
      cx = *comb_menu[m_index].abs_nom_ind;
      if (comb_menu[m_index].code_ind._.off_sign == 0)
      {
        if ((slw)lbx >= 0)
          all_sig = '+';
        else
          lbx = ~lbx + 1, all_sig = '-';
      }
      /* для отображения уставок типа '1/x' */
      if (comb_menu[m_index].code_ind._.invert == 1)
      {                                  // меняем местами ax и bx для инверсного деления.
        ex = lbx, lbx = (lw)bx, bx = ex; //  Для 4-х байтных не продумывалось
      }

      if (ax != 4) // для word byte: преобразование целочисленное
      {
        lax = (lw)lbx * (lw)cx;
        *(w *)&m_buff[3] = lax % bx; //сохраняем остаток.
        *(w *)&m_buff[0] = bx;
        lax /= bx;
      }
      else // для lword: преобразование double чтобы избежать переполнения при первом умножении
      {
        dax = (d)lbx * (d)cx;

        m_dax = dax / (d)bx; //   Контроль переполнения.
        if (m_dax > (d)(lw)0xffffffff)
          m_dax = (lw)0xffffffff, dax = (d)bx * m_dax;

        lax = (lw)m_dax;
        *(w *)&m_buff[3] = dax - (d)lax * (d)bx; // ‚ отличие от алгоритма для double-переменных
        *(w *)&m_buff[0] = bx;                   //  здесь сохраняем не `double`-дробную часть, а остаток.
      }
      // распечатка целой части - максимум 5 или 10 символов.
      //  для 2-х и 4-х байтных начинаем с разных делителей, чтобы сократить итерации.
      if (ax != 4)
        lbx = 10000ul, ax = 5;
      else
        lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ind._.celoe; //сколько первых символов пропустить
      if (ex == ax)
        ex = 2; // для совместимости - если заданы были нули то принимаем формат "3.2".
      else if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {
        bx = lax / lbx;
        lax %= lbx;
        // пока идут первые нули - не выводим их:
        if (bx == 0 && cx == 0)
        { //   пропускаем лишние нулевые символы,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // первые нули закончились.
          output_c((b)bx + 0x30);
        }
      }

      if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
        output_c(all_sig);
      // распечатываем последнюю цифру.
      output_c((b)(w)lax + 0x30);
      
      if (comb_menu[m_index].code_ind._.drob == 0)
          output_s(" "); // OEA для исключения залипания нуля в конце целых чисел

      label = indication_5;
      return;

    case indication_5:
      // распечатка дробной части
      if (comb_menu[m_index].code_ind._.celoe == 0)
        ex = 2;
      else
        ex = comb_menu[m_index].code_ind._.drob;
      if (ex != 0)
      {
        output_c('.');
        bx = *(w *)&m_buff[0];
        lax = *(w *)&m_buff[3]; // восстанавливаем остаток.
        for (; ex != 0; ex--)
        {
          lbx = lax * 10;
          lax = lbx % bx;
          ax = lbx / bx;
          output_c((b)(w)ax + 0x30);
        }
      }
    } // распечатка в 16-ричном виде.
    else
    {
      ax = comb_menu[m_index].code_ind._.type;
      if (ax == 1)
        cx = 1;
      else if (ax == 2)
        cx = 3;
      else if (ax == 4)
        cx = 7;

      for (; (signed char)cx >= 0; cx--)
      {
        bx = (b)(lbx >> 4u * cx) & 0x0fu;
        if (bx <= 0x9)
          bx += 0x30;
        else
        { // маленькие/большие буквы.
          if (comb_menu[m_index].code_ind._.off_sign == 0)
            bx += 0x57u;
          else
            bx += 0x37u;
        }
        output_c(bx);
      }
    }
    label = editing;
    return;
  }
  } //кейс индикация
  break;

  case editing: //редактирование уставки
    if (TestCompleted_Output())
    {
      if (fl_smena_zagolovka == 0) //выводить имена
      {
        if ( (u)((w)(Timer1_Ovr - timer_heading)) >= _Sec(1.3) )
        { //в связи с нехваткой места на дисплее, DAN предложил периодически изменять название параметров на их ед. измерения. // OEA
          fl_smena_zagolovka = ~fl_smena_zagolovka, timer_heading = Timer1_Ovr;
          output_c('\r');
          output_s(comb_menu[m_index].txt);
          output_c('\n');
          label = indication;
          break;
        }
      }
      else //выводить единицы измерения
      {
        if ( (u)((w)(Timer1_Ovr - timer_heading)) >= _Sec(3.3) )
        {
          fl_smena_zagolovka = ~fl_smena_zagolovka, timer_heading = Timer1_Ovr;
          output_c('\r');
          output_s("                "); //нужно очищать экран
          output_c('\r');
          output_s("("), output_s(comb_menu[m_index].ch), output_s(")");
          output_s("     ");
          output_s("("), output_s(comb_menu[m_index].txt2), output_s(")");
          output_c('\r');
          output_c('\n');
          label = indication;
          break;
        }
      }
      if (TestData_for_Input())
      { // Считывание уставки для ее последующего изменения.
        ax = comb_menu[m_index].code_ust._.type;
        if (comb_menu[m_index].code_ust._.off_sign == 0 || ax == 0)
        {
          if (ax == 1)
            dax = (d)(sw) * (sb *)comb_menu[m_index].addr;
          else if (ax == 2)
            dax = (d) * (sw *)comb_menu[m_index].addr;
          else if ( ax == 3 ) 
            dax =  (d)*(  f*)comb_menu[m_index].addr;
          else if (ax == 4)
            dax = (d) * (slw *)comb_menu[m_index].addr;
          else if (ax == 0)
            dax = (d) * (d *)comb_menu[m_index].addr;
        }
        else
        {
          if (ax == 1)
            dax = (d)(w) * (b *)comb_menu[m_index].addr;
          else if (ax == 2)
            dax = (d) * (w *)comb_menu[m_index].addr;
          else if ( ax == 3 ) 
            dax = (d)*(  f*)comb_menu[m_index].addr;
          else if (ax == 4)
            dax = (d) * (lw *)comb_menu[m_index].addr;
          else if ( ax == 0 ) 
            dax = *(  d*)comb_menu[m_index].addr;
        }

        mInput_c(m_ch);
        if (m_ch == Return)
        {
          dax = m_dbx;
          fl_smena_zagolovka = 0;
          timer_heading = 0;
          output_s("\r");
          label = heading_menu1;
          if (comb_menu[m_index].code_ust._.off_sign == 0 || ax == 0)
          {
            if (ax == 1)
              *(sb *)comb_menu[m_index].addr = (sb)dax;
            else if (ax == 2)
              *(sw *)comb_menu[m_index].addr = (sw)dax;
            else if ( ax == 3 )  
              *(  f*)comb_menu[m_index].addr = (f)dax ;
            else if (ax == 4)
              *(slw *)comb_menu[m_index].addr = (slw)dax;
            else if (ax == 0)
              *(d *)comb_menu[m_index].addr = dax;
          }
          else
          {
            if (ax == 1)
              *(b *)comb_menu[m_index].addr = (b)dax;
            else if (ax == 2)
              *(w *)comb_menu[m_index].addr = (w)dax;
            else if ( ax == 3 )   
              *(  f*)comb_menu[m_index].addr = (f)dax ;
            else if (ax == 4)
              *(lw *)comb_menu[m_index].addr = (lw)dax;
            else if ( ax == 0 )   
              *(  d*)comb_menu[m_index].addr = dax ;
          }
          break;
        }
        else if (m_ch == Enter) // Записать копию уставки в память в уставку.
        {
          output_s("\r");
          label = heading_menu1; // Вернуться к перебору уставок.
          fl_smena_zagolovka = 0;
          timer_heading = 0;
          break;
        }
        else if ((comb_menu[m_index].code_ust._.zapr == 0) || (_Ne_Rabota == 1))
        {
          if (m_ch == Up && Mon.Password_Ok == 1) /* “величить грубо копию уставки.*/
          {
            dax += comb_menu[m_index].dX;
            dbx = comb_menu[m_index].max;
            if (ax == 1 || ax == 2) //  В поле макс/мин типа double число по-старому ложится макросами
            {                       //  размерностью (w), и для отрицательных чисел старшие биты заполняются нулями, чтобы это исправить:
              bx = (w)dbx;          //  очищаем от старших нулевых битов в double.
                                    //  возвращаем в double с растяжкой знакового бита.
              if (comb_menu[m_index].code_ust._.off_sign == 0)
                dbx = (sw)bx;
              else
                dbx = (w)bx;
            }

            if (dax > dbx)
              dax = dbx;
            label = indication;
          }
          else if (m_ch == Down && Mon.Password_Ok == 1) /* Уменьшить грубо копию уставки.*/
          {
            dax -= comb_menu[m_index].dX;
            dbx = comb_menu[m_index].min;
            if (ax == 1 || ax == 2)
            {
              bx = (w)dbx; //  очищаем от старших нулевых битов в double.
                           //  возвращаем в double с растяжкой знакового бита.
              if (comb_menu[m_index].code_ust._.off_sign == 0)
                dbx = (sw)bx;
              else
                dbx = (w)bx;
            }
            if (dax < dbx)
              dax = dbx;
            label = indication;
          }
          else
            Klav_Buff = m_ch;
        }
        else
          Klav_Buff = m_ch;

        // Выдача в уставку ее измененного или неизмененного значения.
        if (comb_menu[m_index].code_ust._.off_sign == 0 || ax == 0)
        {
          if (ax == 1)
            *(sb *)comb_menu[m_index].addr = (sb)dax;
          else if (ax == 2)
            *(sw *)comb_menu[m_index].addr = (sw)dax;
          else if ( ax == 3 )  
            *(  f*)comb_menu[m_index].addr = (f)dax ;
          else if (ax == 4)
            *(slw *)comb_menu[m_index].addr = (slw)dax;
          else if (ax == 0)
            *(d *)comb_menu[m_index].addr = dax;
        }
        else
        {
          if (ax == 1)
            *(b *)comb_menu[m_index].addr = (b)dax;
          else if (ax == 2)
            *(w *)comb_menu[m_index].addr = (w)dax;
          else if ( ax == 3 )   
            *(  f*)comb_menu[m_index].addr = (f)dax ;
          else if (ax == 4)
            *(lw *)comb_menu[m_index].addr = (lw)dax;
          else if ( ax == 0 )   
            *(  d*)comb_menu[m_index].addr = dax ;
        }
      }
      if (AWelcome != AWell_old)
        AWell_old = AWelcome;
      if ((TestCompleted_Output()) && ((u)((w)(Timer1_Ovr - ind_time)) > _Sec(0.15)))
        label = indication;
    }
    break;
  } //switch
  Restart_Output ()  ;
  return;
} //функция редактр