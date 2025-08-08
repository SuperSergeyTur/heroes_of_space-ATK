void comb_redact(void)
{
  word ax, bx, cx, ex; //� ��������
  register lword lax, lbx;
  byte all_sig;
  static byte fl_smena_zagolovka = 0;    //���� ��� ����� ���������
  static word timer_heading = 0;         //��� ����� ��������� � ������ ��������������
  static word fl_first_call = 1;         //���� ������� ������
  static word label = 0;                 //������ �����
  static word m_index = 0;               //������ � ����
  static byte type_ust = 0;              //��� �������
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
          // ����������� ��������������� �������� �������.
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
    // ���������� � <double> ����.
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
      m_dax = dax - (d)lax; //��������� ������� �����.
      lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ust._.celoe; //������� ������ �������� ����������
      if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {
        bx = lax / lbx;
        lax %= lbx;
        // ���� ���� ������ ���� - �� ������� ��:
        if (bx == 0 && cx == 0)
        { //   ���������� ������ ������� �������,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // ������ ���� �����������.
          output_c((b)bx + 0x30);
        }
      }

      if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
        output_c(all_sig);
      // ������������� ��������� �����.
      output_c((b)(w)lax + 0x30);
      label = indication_1;
      return;

    case indication_1: // ���������� ������� �����  ��� double
      ex = comb_menu[m_index].code_ust._.drob;
      if (ex != 0)
      {
        output_c('.');
        for (; ex != 0; ex--)
        {
          m_dax *= 10;
          ax = (w)m_dax; //��������� ����� ����� �����
          output_c((b)(w)ax + 0x30);
          m_dax -= (d)ax; //����� �����
        }
      }
    }
    else // ���������� � <lword, word � byte> ����.
    {
      bx = comb_menu[m_index].nom_ust;
      cx = *(w *)comb_menu[m_index].abs_nom_ust;
      if (comb_menu[m_index].code_ust._.off_sign == 0)
      { // ���� ���������� �� ������ - �������� ���� � ������.
        if ((slw)lbx >= 0)
          all_sig = '+';
        else
          lbx = ~lbx + 1, all_sig = '-';
      }

      // �������� ���������� ������ � ��� ���������.
      /* ��� ����������� ������� ���� '1/x' */
      if (comb_menu[m_index].code_ust._.invert == 1)
      { // ������ ������� ax � bx ��� ���������� �������.
        ex = ax, ax = bx, bx = ex;
      }

      if (ax != 4) // ��� word byte: �������������� �������������
      {
        lax = (lw)lbx * (lw)cx;
        m_time = lax % bx; //��������� �������.
        *(w *)&m_buff[0] = bx;
        lax /= bx;
        if (lax > 0xffffu)
          lax = 0xffff;
      }
      else // ��� lword: �������������� double ����� �������� ������������ ��� ������ ���������
      {
        dax = (d)lbx * (d)cx;

        dbx = dax / (d)bx; //   �������� ������������.
        if (dbx > (d)(lw)0xffffffff)
          dbx = (lw)0xffffffff, dax = (d)bx * dbx;

        lax = dbx;
        m_time = dax - (d)lax * (d)bx; //��������� �������.
        *(w *)&m_buff[0] = bx;
      }
      // ���������� ����� ����� - �������� 5 ��� 10 ��������.
      //  ��� 2-� � 4-� ������� �������� � ������ ���������, ����� ��������� ��������.
      if (ax != 4)
        lbx = 10000ul, ax = 5;
      else
        lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ust._.celoe; //������� ������ �������� ����������
      if (ex == ax)
        ex = 2; // ��� ������������� - ���� ������ ���� ���� �� ��������� ������ "3.2".
      else if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {
        bx = lax / lbx;
        lax %= lbx;
        // ���� ���� ������ ���� - �� ������� ��:
        if (bx == 0 && cx == 0)
        { // � ���������� ������ ������� �������,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // ������ ���� �����������.
          output_c((b)bx + 0x30);
        }
      } // ������������� ��������� �����.
      if ((cx == 0) && (comb_menu[m_index].code_ust._.off_sign == 0))
        output_c(all_sig);
      // ������������� ��������� �����.
      output_c((b)(w)lax + 0x30);
      label = indication_2;
      break;

    case indication_2: // ���������� ������� �����
      if (comb_menu[m_index].code_ust._.celoe == 0)
        ex = 2; // �� ���������.
      else
        ex = comb_menu[m_index].code_ust._.drob;
      if (ex != 0)
      {
        output_c('.');
        bx = *(w *)&m_buff[0];
        lax = m_time; // ��������������� �������.
        for (; ex != 0; ex--)
        {
          lbx = lax * 10;
          lax = lbx % bx;
          ax = lbx / bx;
          output_c((b)(w)ax + 0x30);
        }
      }
      label = indication_3; //��������� � ������  ���������
break;
    }

  case indication_3: //������� �� ��� � ���������
  {
    output_s("  "); //��� ������� ����� �������� � ����������, ����� ��������� �� ���� �������/����� ��� ��������
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
    // ���������� � <double> ����.
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
        dax = (d)(0xffffffffL); // � ������� �� ��������� ��� ������������� ����������
      lax = (lw)dax;           //  ����� ��������� �� �������, � ��� ������� `double`-������� �����.
      m_dax = dax - (d)lax;   //��������� �����.

      // ���������� ����� ����� - �������� 5 ��� 10 ��������.
      //  ��� 2-� � 4-� ������� �������� � ������ ���������, ����� ��������� ��������.
      lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ind._.celoe; //������� ������ �������� ����������
      if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {

        bx = lax / lbx;
        lax %= lbx;
        // ���� ���� ������ ���� - �� ������� ��:
        if (bx == 0 && cx == 0)
        { //   ���������� ������ ������� �������,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // ������ ���� �����������.
          output_c((b)bx + 0x30);
        }
      }

      if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
        output_c(all_sig);
      // ������������� ��������� �����.
      output_c((b)(w)lax + 0x30);
      label = indication_4;
      return;

    case indication_4:
      // ���������� ������� �����
      ex = comb_menu[m_index].code_ind._.drob;
      if (ex != 0)
      {
        output_c('.');
        for (; ex != 0; ex--)
        {
          m_dax *= 10;
          ax = (w)m_dax; //��������� ����� ����� �����
          output_c((b)(w)ax + 0x30);
          m_dax -= (d)ax; //����� �����
        }
      }
    }
    // ���������� � 10-������ ����.
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
      /* ��� ����������� ������� ���� '1/x' */
      if (comb_menu[m_index].code_ind._.invert == 1)
      {                                  // ������ ������� ax � bx ��� ���������� �������.
        ex = lbx, lbx = (lw)bx, bx = ex; //  ��� 4-� ������� �� �������������
      }

      if (ax != 4) // ��� word byte: �������������� �������������
      {
        lax = (lw)lbx * (lw)cx;
        *(w *)&m_buff[3] = lax % bx; //��������� �������.
        *(w *)&m_buff[0] = bx;
        lax /= bx;
      }
      else // ��� lword: �������������� double ����� �������� ������������ ��� ������ ���������
      {
        dax = (d)lbx * (d)cx;

        m_dax = dax / (d)bx; //   �������� ������������.
        if (m_dax > (d)(lw)0xffffffff)
          m_dax = (lw)0xffffffff, dax = (d)bx * m_dax;

        lax = (lw)m_dax;
        *(w *)&m_buff[3] = dax - (d)lax * (d)bx; // � ������� �� ��������� ��� double-����������
        *(w *)&m_buff[0] = bx;                   //  ����� ��������� �� `double`-������� �����, � �������.
      }
      // ���������� ����� ����� - �������� 5 ��� 10 ��������.
      //  ��� 2-� � 4-� ������� �������� � ������ ���������, ����� ��������� ��������.
      if (ax != 4)
        lbx = 10000ul, ax = 5;
      else
        lbx = 1000000000ul, ax = 10;
      ex = ax - comb_menu[m_index].code_ind._.celoe; //������� ������ �������� ����������
      if (ex == ax)
        ex = 2; // ��� ������������� - ���� ������ ���� ���� �� ��������� ������ "3.2".
      else if ((sw)ex < 0)
        ex = 0;

      for (cx = 0; lbx != 1; lbx /= 10)
      {
        bx = lax / lbx;
        lax %= lbx;
        // ���� ���� ������ ���� - �� ������� ��:
        if (bx == 0 && cx == 0)
        { //   ���������� ������ ������� �������,
          if (ex != 0)
            ex--;
        }
        else
        {
          if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
            output_c(all_sig);
          cx = 1; // ������ ���� �����������.
          output_c((b)bx + 0x30);
        }
      }

      if ((cx == 0) && (comb_menu[m_index].code_ind._.off_sign == 0))
        output_c(all_sig);
      // ������������� ��������� �����.
      output_c((b)(w)lax + 0x30);
      
      if (comb_menu[m_index].code_ind._.drob == 0)
          output_s(" "); // OEA ��� ���������� ��������� ���� � ����� ����� �����

      label = indication_5;
      return;

    case indication_5:
      // ���������� ������� �����
      if (comb_menu[m_index].code_ind._.celoe == 0)
        ex = 2;
      else
        ex = comb_menu[m_index].code_ind._.drob;
      if (ex != 0)
      {
        output_c('.');
        bx = *(w *)&m_buff[0];
        lax = *(w *)&m_buff[3]; // ��������������� �������.
        for (; ex != 0; ex--)
        {
          lbx = lax * 10;
          lax = lbx % bx;
          ax = lbx / bx;
          output_c((b)(w)ax + 0x30);
        }
      }
    } // ���������� � 16-������ ����.
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
        { // ���������/������� �����.
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
  } //���� ���������
  break;

  case editing: //�������������� �������
    if (TestCompleted_Output())
    {
      if (fl_smena_zagolovka == 0) //�������� �����
      {
        if ( (u)((w)(Timer1_Ovr - timer_heading)) >= _Sec(1.3) )
        { //� ����� � ��������� ����� �� �������, DAN ��������� ������������ �������� �������� ���������� �� �� ��. ���������. // OEA
          fl_smena_zagolovka = ~fl_smena_zagolovka, timer_heading = Timer1_Ovr;
          output_c('\r');
          output_s(comb_menu[m_index].txt);
          output_c('\n');
          label = indication;
          break;
        }
      }
      else //�������� ������� ���������
      {
        if ( (u)((w)(Timer1_Ovr - timer_heading)) >= _Sec(3.3) )
        {
          fl_smena_zagolovka = ~fl_smena_zagolovka, timer_heading = Timer1_Ovr;
          output_c('\r');
          output_s("                "); //����� ������� �����
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
      { // ���������� ������� ��� �� ������������ ���������.
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
        else if (m_ch == Enter) // �������� ����� ������� � ������ � �������.
        {
          output_s("\r");
          label = heading_menu1; // ��������� � �������� �������.
          fl_smena_zagolovka = 0;
          timer_heading = 0;
          break;
        }
        else if ((comb_menu[m_index].code_ust._.zapr == 0) || (_Ne_Rabota == 1))
        {
          if (m_ch == Up && Mon.Password_Ok == 1) /* ��������� ����� ����� �������.*/
          {
            dax += comb_menu[m_index].dX;
            dbx = comb_menu[m_index].max;
            if (ax == 1 || ax == 2) //  � ���� ����/��� ���� double ����� ��-������� ������� ���������
            {                       //  ������������ (w), � ��� ������������� ����� ������� ���� ����������� ������, ����� ��� ���������:
              bx = (w)dbx;          //  ������� �� ������� ������� ����� � double.
                                    //  ���������� � double � ��������� ��������� ����.
              if (comb_menu[m_index].code_ust._.off_sign == 0)
                dbx = (sw)bx;
              else
                dbx = (w)bx;
            }

            if (dax > dbx)
              dax = dbx;
            label = indication;
          }
          else if (m_ch == Down && Mon.Password_Ok == 1) /* ��������� ����� ����� �������.*/
          {
            dax -= comb_menu[m_index].dX;
            dbx = comb_menu[m_index].min;
            if (ax == 1 || ax == 2)
            {
              bx = (w)dbx; //  ������� �� ������� ������� ����� � double.
                           //  ���������� � double � ��������� ��������� ����.
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

        // ������ � ������� �� ����������� ��� ������������� ��������.
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
} //������� �������