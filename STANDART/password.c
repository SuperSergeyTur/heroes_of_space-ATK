/*------------------------------------------------------------------*/
/*   ��������� ����� � �������� ������:
 * - ������ ������������� �� ���� �:
                                   { "AE-���.�����. ", _Case ( 'A' , 'E' ) },
                                   { "F2-�������.   ", _Case ( 'F' , '2' ) },
                                   { "A2-�����.Us   ", _Case ( 'A' , '3' ) },
                                   { "A5-�����.����a", _Case ( 'A' , '5' ) },
                                   //{ "FA-�������.   ", _Case ( 'F' , 'A' ) },
                                   { "A9-���� ���.  ", _Case ( 'A' , '9' ) },
                                   { "AB-���� ����. ", _Case ( 'A' , 'B' ) },
                                   { "AD-����� ���. ", _Case ( 'A' , 'D' ) },
                                   { "F-�������.    ", _Case ( 'F' ,  0  ), 9 },
                                   { "F1-����.      ", _Case ( 'F' , '1' ) },
                                   { "F3-���� ���.  ", _Case ( 'F' , '3' ) },
                                   { "F4-���� ����  ", _Case ( 'F' , '4' ) },
                                   { "F7-����.�����.", _Case ( 'F' , '7')  },
                                   { "FD-���� DP.   ", _Case ( 'F' , 'D' ) },
                                   { "F9-���.�����. ", _Case ( 'F' , '9' ) },
                                   { "F0-����.����. ", _Case ( 'F' , '0' ) },
                                   { "FC-�����.����.", _Case ( 'F' , 'C')  },
                                   { "F1-����.      ", _Case ( 'F' , '1' ) },
                                   { "AC-�����.����.", _Case ( 'A' , 'C' ) },
 * - ������ ������������� �� ��������� ������� �: -- ��� ��� ��������, �������, ��������, ����� ������������
 *                                                                       ��� ��������� ������� � ��������� �� ��������.
                                   { "A7-���.�����. ", _Case ( 'A' , '7' ) },
                                   { "A8-���.������.", _Case ( 'A' , '8' ) },
                                   { "A3-�����.Is   ", _Case ( 'A' , '3' ) },
                                   { "A4-���� ���.  ", _Case ( 'A' , '4' ) },
 * - � ������ �� �������� �������� ����������� ����� �������� "������ ������";
 * - ��� �������� � "system.c"�� ����� ������������� �� ���������:
 *       - ���� ����� ������� ������ ������ ������ �� ������������ � �������� �������
 *         "������ ������";
 *       - ����� ���������� ������� "������ ������";
 * - ��� ������ � ���������� ��������� �� ���������:
 *       - ���� ������ �� ������ ����� - ���������� ������   ��� ������������ ������;
 *       - ���� ������    ������ ����� - ���������� �������� ��� ������������ ������;
 * - ��� ����� ������:
 *       - ������ ������ "word";
 *       - ��� ���������� ������ "_r.Password";
 *       - ������ ������� �� 3-� ����;
 *       - ������ ������� word �������� ���� �����, ��������� ������� ��������;
 *       - �� �������� ��������� ��� ���� � ������ ��������������� �� ������� ����� ����;
 *       - ����� �������� �����������/����������� ��������� ����/���� � ��������� "0...9", �� �� ������ ��
 *         ������������ - ����� ������� ������� ���� ���������� �� ������� "*".
 *         ������������� ����, ������ ���� ��������� ����� ����� �� ����.
 *         ��� ������ ������� ������ �����/���� �� ���� �������� ��������� ����� "-" ��� �������� ����,
 *         ��� ������� ��������.
 *       - ���������� ����� ������ ����� � ������� � ��������� �������������� ����� "Enter";
 *       - ������� � ���������� ����� �������������� ����� "Esc", ��� ���� ������� ����� ����������;
 *       - �� ���������� ����� ���� ���� �������� ������ ������������ � �������� ������ � ���� �����������, ���� �����������
 *         � �������������� ����������;
 *       - �� ������������ � ���� ����������;
 * - ��� �������������� ������:
 *       - ������ � ���� �������������� ������;
 *       - �� ����� ��������� ������, ��������������� �� �������: "Xi=9-Ni",
 *         ��� ���� 1-� ����� ������ ����������� �� 3-� �������, 2-� - �� 1-� � 3-� - �� 2-�;
 *       - ������� ������ ����������� �� �������: "Ni=9-Xi",
 *         ��� ���� ������� ���������, ��� 1-� ����� ��������� ���������� ������������� 2-� ����� ������,
 *         2-� - 3-� � 3-� - 1-�;
 * - ��� ��������� ������ ����������� �� ��, ��� � ��� ����� ������, �� � ������� ��������� ���� � �� ���������� �����
 *   �������� ������ ��������� � ������� � ��������������� ����������;
 * - ��� ���������� ������ ������, ������ ���������� �� �������.
 */


word  Password_control ( word code )
{
    register word  ax  ;
    register byte  bh  ;

      //   ������� �������, ����� ������ ����� ����� � ����� ���
      //  ��������������� �� ������������.
enum { i0, i10, i20, i30, i40, i50, i60, i70, i160 };


            //  �������������.
    if ( code == 0 )
    {
      if ( _r.Password == 0 )  Mon.Password_Ok = 1 ;
      else                     Mon.Password_Ok = 0 ;

      return  0 ;
    }
    else if ( code == 2 )  //  ������� ��� ��������� ��������: �������� ������ - ������ ������ �����.
    {
        if ( Mon.Password_Ok == 0 )
        {
          if ( M_FirstCall == 1 )  /*  ������������� ������� ����� ��� �������  */
          {
            output_s ( _NoPassword_txt ) ;
            m_time = Timer1_Ovr ;
            M_FirstCall = 0 ;
          }
          else    //---
          {
            if ( (u)(w)(Timer1_Ovr - m_time) > _Time_Password_txt )
            {
              Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
            }
          }
          return  0 ;
        }
        else  return  1 ;
    }
          //----------------------
     //------------------------



      if ( M_FirstCall == 1 )  //  ������������� ������� ����� ��� �������
        {                      // ���������� ������� ...
          M_FirstCall = 0 ;
             //-------------
          m_time = Timer1_Ovr ;
          Label = i0 ;
          m_index = 0 ;
          return  0 ;
        }


     switch ( Label )
     {
      default:
      case i0:    output_s ( _MenuPassword_txt ) ;
                  m_index = 0 ;
                  Label = i10 ;
      case i10:
            if ( TestCompleted_Output() )
            {
              if ( Mon.Password_Ok == 0 )
              {
                if ( m_index == 0 ) output_s ( _EnterPassword_txt ) ;  // �����������
                else                output_s ( _RecovPassword_txt ) ;  // ��������� ����
              }                                                        // � �����������
              else                                                     // �� ���������
              {                                                        // ������
                if ( m_index == 0 ) output_s ( _ChangePassword_txt ) ;
                else                output_s ( _ActivatePassword_txt ) ;
              }
              Label = i20 ;
              break ;
            }

      case  i20:
          if ( TestData_for_Input() )
           {
              mInput_c ( bh ) ;
              if ( bh == Return )  // ����� �� ����� ������
                {
             end: Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ;
                  return  0 ;
                }                                 // ��� ���������� ��������� ��� ���������� ������
              else if (( bh == Up  ||  bh == Down ) && _r.Password != 0 ) // �������� �����.
                {
                  //aa = m_index ;
                  m_index = ~m_index ;
                  Label = i10 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 )                Label = i30 ;
                  else  if ( Mon.Password_Ok == 0 )  Label = i60 ;
                  else
                  {
                    Mon.Password_Ok = 0 ;                  // ��������� ������
                    output_s ( _ActivatedPassword_txt ) ;
                    m_time = Timer1_Ovr ;
                    Label = i160 ;
                  }
                }
              else    Klav_Buff = bh;
           }
          break ;

      case i30:   output_s ( "\n" ) ;
                  m_index = 0 ;
                  m_buff[0] = 0, m_buff[1] = 0, m_buff[2] = 0 ;
                  //output_s ( "\n\r     0 0 0  \b\b\b\b\b" ) ;
                  Label = i40 ;

      case i40:
                if ( (u)(w)(Timer1_Ovr - m_time) > _Sec( 0.15 ) )
                {
                  if ( TestCompleted_Output() )            // ����� ���� ����� ������
                  {
                      output_s ( "\r    -" ) ;
                    if ( Mon.Password_Ok == 1 )   output_c ( m_buff[0]+0x30 ) ;
                    else
                    {
                      if ( m_buff[0] == 0 )  output_c ( '0' ) ;    // ���� �������� ������ �� 0 -
                      else                   output_c ( '*' ) ;    // ������ ��� �� '*'
                    }
                      output_s ( "-" ) ;
                    if ( Mon.Password_Ok == 1 )   output_c ( m_buff[1]+0x30 ) ;
                    else
                    {
                      if ( m_buff[1] == 0 )  output_c ( '0' ) ;
                      else                   output_c ( '*' ) ;
                    }
                      output_s ( "-" ) ;
                    if ( Mon.Password_Ok == 1 )   output_c ( m_buff[2]+0x30 ) ;
                    else
                    {
                      if ( m_buff[2] == 0 )  output_c ( '0' ) ;
                      else                   output_c ( '*' ) ;
                    }
                      output_s ( "-" ) ;
                     // ���������� ����������������� ������� � ����������� �� ��������� �������
                    for ( ax = 0 ; ax < (( _PasswordSize-1 - m_index ) * 2 + 2 ) ; ax++ )
                    {
                      output_s ( "\b" ) ;
                    }

                    Label = i50 ;
                    break ;
                } }

      case i50:   if ( TestData_for_Input() )                        // ���� ������
                  {
                    mInput_c ( bh ) ;
                        if ( bh == Return )         // �� ������� Esc - ��������� ������� �������
                        {                           // ���� ��� 0 - ������� �� ����������
                          Label = i40 ;
                          if ( m_buff[m_index] != 0 )  m_buff[m_index] = 0 ;
                          else
                          {
                            if ( m_index != 0 )  m_index-- ;
                            else                 Label = i0 ;
                          }
                        }
                        else if ( bh == Up )
                        {
                          if ( m_buff[m_index] < 9 )  m_buff[m_index]++ ;
                          else m_buff[m_index] = 0 ;
                         //---  ��� ��������� ������� - ��������������� ����� ���� �� ���� ��������
                          if ( Mon.Password_Ok == 0 )   output_s ( _ProbelPassword_txt ) ;
                          m_time = Timer1_Ovr ;
                            //---
                          Label = i40 ;
                        }
                        else if ( bh == Down )
                        {
                          if ( m_buff[m_index] > 0 )  m_buff[m_index]-- ;
                          else m_buff[m_index] = 9 ;
                            //---
                          if ( Mon.Password_Ok == 0 )   output_s ( _ProbelPassword_txt ) ;
                          m_time = Timer1_Ovr ;
                            //---
                          Label = i40 ;
                        }
                        else if ( bh == Enter )   // �� ������� Enter - �������
                        {                         // �� ��������� �������
                          if ( m_index < 2 )
                          {
                            m_index++ ;
                            Label = i40 ;
                          }
                          else
                          {
                            if ( Mon.Password_Ok == 1 )           // ���� ������ ��� ��������������
                            {                                     // ������ - �����������
                              _r.Password =  (w)m_buff[0] +       // ���������� ������
                                            ((w)m_buff[1] << 4) +
                                            ((w)m_buff[2] << 8) ;
                              output_s ( _OkNewPassword_txt ) ;
                            }
                            else
                            {
                              ax = _r.Password ;
                              if ( m_buff[0] == (ax & 0x000F))           // �������� ������������
                              {                                          // ��������� ������
                                if ( m_buff[1] == ((ax >> 4) & 0x000F))
                                 {
                                   if ( m_buff[2] == ((ax >> 8) & 0x000F))
                                    {
                                      output_s ( _RightPassword_txt ) ;
                                      Mon.Password_Ok = 1 ;
                                    }
                                   else goto end1 ;
                                 }
                                else goto end1 ;
                              }
                              else
                              {
                        end1:   output_s ( _WrongPassword_txt ) ;
                              }
                            }
                            m_time = Timer1_Ovr ;
                            m_index = 0 ;
                            Label = i160 ;
                          }
                        }
                        else    Klav_Buff = bh;
                  }

                  break;


      case i60:   ax = _r.Password ;                      // ����� ���� �������������� ������
                  m_buff[2] = 9 - ( ax       & 0x000F) ;
                  m_buff[0] = 9 - ((ax >> 4) & 0x000F) ;
                  m_buff[1] = 9 - ((ax >> 8) & 0x000F) ;

                  output_s ( _RecoveCodePassword_txt ) ;
                  output_s ( "\r\n    -" ) ;
                  output_c ( m_buff[0]+0x30 ) ;
                  output_s ( "-" ) ;
                  output_c ( m_buff[1]+0x30 ) ;
                  output_s ( "-" ) ;
                  output_c ( m_buff[2]+0x30 ) ;
                  output_s ( "-" ) ;
                  Label = i70 ;

      case i70:   if ( TestData_for_Input() )
                  {
                    mInput_c ( bh ) ;
                        if ( bh == Return || bh == Enter )  // ����� �� ����� ������
                        {
                          goto end ;
                        }
                        else    Klav_Buff = bh;
                  }
                  break ;

      case i160 :
                  if ( (u)(w)(Timer1_Ovr - m_time) > _Time_Password_txt ) goto end ;
          break ;

    }

  return  0 ;
}

