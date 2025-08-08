
//         ��������� ��������� ����������� ��������� �� ������ ������.
//------------------------------------------------------------------

/*   ����� �������� � �� "����������" � �� "������".
 *   ��������� ������������ ��������� ����������� ���������� �� �������
 * ��������� � ��� ��������� � ���������� ����� �� ������.
 *   �������:
 * - �����, �� ������� ����� �������� , ������������� ���������;
 * - ��������� ���������� ��������� � ��� ��������� � ���������� ����� ��
 *   ������.
 *   �������:
 * - "+" � ������ ������ ��������� - ����� ��������� ;
 * - "Enter" � ������ ������ - ������� � ��������� ;
 * - "Esc" � ������ ��������� - ������� � ������ ������ ;
 * - "Esc" � ������ ������ - ������� � ���������.
 */
//   ��� ���������� ���������� � ������� ��������������� ���������� ��� ��
// ����������� � ���������� ����, ��� �������� ����������� � ��������������
// ����.  ������� ���������� �������� ������ ����� ������ ���� "sword", ����
// ������ ���� "word" �� ��� ���� �� �������� �� �������� "0...+32767" .


void NetIndicator_Drive ( void )
{
   register word    ax , bx , cx, ex ;
   byte    all_sig;
   register lword  lax;

      if ( M_FirstCall == 1 )  /*  ������������� ������� ����� ��� �������  */
        {                      /* ���������� ������� ...                    */
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
                      return ;   // �������� ��� �����-�� ����.
                    }
                  else if ( m_ch == Down ) /* �������� ����� ������������ ����������.*/
                    {
                      if ( ++m_index >= NetNumInd ) m_index = 0 ;
                      Label = 103 ;
                    }    /* ������� � ��������� ��������� */
                  else if ( m_ch == Up ) /* �������� ����� ������������ ����������.*/
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
                 // ������� ������, ���� �� �������� ���������� �����.
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
                  else if ( m_ch == Down ) /* �������� ����� ������������ ����������.*/
                    {
                      if ( ++m_addr >=  NetIndicat[m_index].kol_vo ) m_addr = 0 ;
                      Label = 200 ;
                    }    /* ������� � ��������� ��������� */
                  else if ( m_ch == Up ) /* �������� ����� ������������ ����������.*/
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
                 // �������� ���������� ����������� ������ + ������������,
              if  ( (  TestCompleted_Output() )    // ����� �� ����������.
                    && ( (u)((w)(Timer1_Ovr - m_time)) > _Sec(0.15) ) )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  for ( m_ext = 0 ; m_ext < 2 ; m_ext++ )
                  {
                    if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.type == 1 )  ax = *(b*)NetIndicat[m_index].adr_Gruop[m_addr].adr[m_ext] ;
                    else        ax = *(w*)NetIndicat[m_index].adr_Gruop[m_addr].adr[m_ext];
                         // ���������� � 10-������ ����.
                    if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.print_type == 0 )
                    {
                      bx = NetIndicat[m_index].adr_Gruop[m_addr].nom[m_ext]  ;
                      cx = *NetIndicat[m_index].adr_Gruop[m_addr].abs_nom[m_ext]  ;
                      if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )
                      {
                        if ( (sw)ax >= 0 )    all_sig = '+' ;
                        else   ax = ~ax + 1 , all_sig = '-' ;
                      }
                        // �������� ���������� ������ � ��� ���������.
                      //���� �������� � ���������� ��������, �� ��������� �� ���������
                      // abs_nom*ax/diskr_nom
                       /* ��� ����������� ������� ���� '1/x' */
                       if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.invert == 1 )
                       {  // ������ ������� ax � bx ��� ���������� �������.
                         ex = ax , ax = bx, bx = ex ;
                       }
                       lax = (lw)ax * (lw)cx ;
                       *(w*)&m_buff[3] = lax%bx  ;    //��������� �������.
                       *(w*)&m_buff[0] = bx;
                       lax /= bx;

                       if ( lax > 0xffff ) lax = 0xffff;

                      //lax &= 0xffff; // ������� �������.

                                  // ���������� ����� ����� - �������� 5 ��������.
                      ex = 5 - NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe ; //������� ������ �������� ����������
                      if ( ex == 5 ) ex = 2 ; // ��� ������������� - ���� ������ ���� ���� �� ��������� ������ "3.2".
                      else if ( (sw)ex < 0 ) ex = 0 ;
                      for ( ax = 10000, cx = 0 ; ax != 1 ; ax /= 10 )
                          {
                            bx =  lax/ax  ;
                            lax %=ax ;
                                // ���� ���� ������ ���� - �� ������� ��:
                            if ( bx == 0 && cx == 0 )
                            {     // � ���������� ������ ������� �������,
                              if ( ex != 0 ) ex-- ;
                                  // ��� �������� ���������.
                              else  output_c (' ') ;
                            }
                            else
                            {
                              if ((cx == 0) && ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                              cx = 1 ; // ������ ���� �����������.
                              output_c ( (b)bx + 0x30 ) ;
                            }
                          }

                          if ((cx == 0) && ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 )  ) output_c ( all_sig ) ;
                          // ������������� ��������� �����.
                          output_c ( (b)(w)lax + 0x30 ) ;
                          Label = 15 ;
                          return;

                case 15:
                          // ���������� ������� �����
                            if  (NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.celoe == 0)
                            {
                             ex = 2 ;
                            }
                            else ex = NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.drob ;
                            if ( ex != 0 )
                            {
                              output_c ( '.' ) ;
                              bx = *(w*)&m_buff[0] ;
                              lax =*(w*)&m_buff[3]  ; // ��������������� �������.
                              for ( ; ex != 0 ; ex-- )
                              {
                                 ax = lax*10  ;
                                   lax = ax % bx         ;
                                   ax /= bx;
                                output_c ( (b)(w)ax + 0x30 ) ;
                              }
                            }
                    }    // ���������� � 16-������ ����.
                    else //if ( Nind[m_index].code[m_ext]._.print_type == 1 )
                    {
                      if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.type == 1 ) cx = 1 ;
                      else                                         cx = 3 ;
                      for ( ; (signed char) cx >= 0 ; cx -- )
                      {
                        bx = (b)( ax >> 4u*cx ) & 0x0fu ;
                        if ( bx <= 0x9 ) bx += 0x30 ;
                        else
                        {       // ���������/������� �����.
                          if ( NetIndicat[m_index].adr_Gruop[m_addr].code[m_ext]._.off_sign == 0 ) bx += 0x57u ;
                          else                                             bx += 0x37u ;
                        }
                        output_c ( bx ) ;
                      }
                    }
                    output_s ( NetIndicat[m_index].adr_Gruop[m_addr].txt2[m_ext] ) ;
                    if  (NetIndicat[m_index].adr_Gruop[m_addr].txt2[1]==0)  m_ext++;
                    Label = 16 ;// ����� ����� ������� ��������� ����������.
                    return ;
                  case 16:; // ���������� ����.
                  }
                  Label = 23 ;// ������������ � ������� �����.
                  m_time = Timer1_Ovr ;
                }
              while (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;

                  // ���� �������� �� Return ������������ ��� ��� �� ����� �
                  // ���������, ���� �� ���������� - �� � ������� ����������,
                  // � ���� �� ������������ - �� � ���������

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

