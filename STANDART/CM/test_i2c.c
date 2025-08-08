
//const char *c_Programm[2] = { "\r�����i��� ���   ", "\r�����i��� ������"};

/*   ��������� ������������ ������ i2c.
   ������������ ������������ � ������ _i2c_beg �� ������ _i2c_end.
   ��� ������������ ���������� ������� ���������� ������. ��-�����
   ������������ ������������ � �������� � ����� ������������ �������
   �������� ������� ��� ���������� � ��� � i2c.
     ��� ������������ � ������ ������������ ��������������� �����
   1...256,1...256, � �.�., � ����� ��������������� ����������� �
   �����������.
     ����� ������������ �������� ��������������� ����������� ���������.
 */

void Test_i2c ( void )
{
   byte bh , bl ;
 //register word ax ;
   static slword ret;
 //lword bx ;

 //char *ptr ;

      //   ������� �������, ����� ������ ����� ����� � ����� ���
      //  ��������������� �� ������������.
  enum { i0, i1, i11, i12, i2 , i21 , i22 , i23 , i24 , i3 };


              //  �������� ������: ������ ������ �����.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCall == 1 )  //  ������������� ������� ����� ��� ������
        {                      // ���������� ������� ...
          output_s ( _Test_EOZU_txt "\r\n") ;
          M_FirstCall = 0 ;
          Label = 0 , m_index = 0 ;
          return ;
        }

    switch ( Label )
    {
      default: Label = i0;
      case i0:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _Test_No_txt  ) ;
              else                output_s ( _Test_Yes_txt ) ;
              Label = i12 ;
              break ;
            }

      case i12: // ��������� �������� �� ������ �����, ��� 'while
               // �� �����������' (�.�. ��� ������ ����� ����� �� ����)
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* ����� �� ����� ������ */
                {
             end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                  //Last_Av = 0;
                }
              else if ( bh == Up || bh == Down ) /* �������� �����. */
                {
                  m_index = ~m_index,  Label = i0 ;
                }
              else if ( bh == Enter )
                {
                  if ( m_index == 0 ) goto end ;
                  output_s ("\r\n");
                  m_index = 0;
                  Label = i2 ;
        }       }
          break ;
    //-----------------

      case i2:
          if ( TestCompleted_Output() )
            {
              if (m_index == 0)
              {
                output_s ( c_Programm[0] ) ;
              }
              else
              {
                output_s ( c_Programm[1] ) ;
              }
              Label = i21 ;
              break ;
            }
    case i21:

      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return )  /* ����� �� ����� ������ */
                {
                  goto end;
                }
              else if ( bh == Up || bh == Down ) /* �������� �����. */
                {
                  m_index = ~m_index,  Label = i2 ;
                }
              else if ( bh == Enter )
                {
                  output_s ( _Waiting_txt "\n\r") ;
                    Label = i22 ;
                }
        }
          break ;
    case i22:
             // 29.11.2012 13:43 ����� ������� �� ����� �����, ������������, �� ����� �������
             if( Mon.i2c_busy == 1 ) break; // ����, ���� ����������� ����

            //  ������� ���������� �������� ������ ������ �.�. ��� ������ ����������.
                 m_buff[5] = 'h', m_buff[6] = '\r', m_buff[7] = 0 ;//NULL ;
/*          //  ������ � ������ ��������������� ����� 1...256,1...256, � �.�.
          for ( bx = 0 ; bx < (_flash_end - _flash_beg); bx = bx + 8192 )
           {
                // �������������� ������ � ���������� ��� � �����
             for ( bl = 4 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[4-bl] = bh ; //output_c ( bh ) ;
               }
             if ( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------
             bh = bx ;
             ax = Save_into_i2c(8192,buff,bx,(b)m_addr) ;
             if ( ax != 0 )
             {
               goto end1;
             }
             //Flash_Store();
           }
*/
          if (m_index == 0)
          {
            ret = EMC_Check( _EMC_CS1,1 );
          }
          else
          {
            ret = EMC_Check( _EMC_CS1,0 );
          }
          m_time = Timer1_Ovr ;
          Label = i23 ;
          break ;

    case i23:
          if ( (u)((w)(Timer1_Ovr-m_time)) < _Sec(0.7) ) break;
          if ( ret == -1 )
          {
            output_s ( " Ok." ) ;
            m_time = Timer1_Ovr ;
            Label = i24 ;
            break ;
          }
          else  // ����� ������ , �� ������� ��������� ������ :
          {
                // �������������� ������ � ���������� ��� � �����
             for ( bl = 4 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( ret >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[4-bl] = bh ; //output_c ( bh ) ;
               }
             //---
             if( TestCompleted_Output() )  output_s ( _Error_i2c_txt "\n\r") ;
             output_s ( m_buff ) ;
             Label = i3 ;
          }
          break ;
    case i24:
          if ( (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0) ) break;
          goto end;
    //-----------------
      case i3:
      //---
      if ( TestData_for_Input() )
        {
          mInput_c ( bh ) ;
              if ( bh == Return || bh == Enter )  /* ����� �� ����� ������ */
              {
                goto end;
              }
        }
/*
            // ���������� ��������������� �� ������ ����� ���������� ������.
          for ( bx = 0; bx < (_flash_end - _flash_beg) ; bx++ )
           {
                // �������������� ������ � ���������� ��� � �����
             for ( bl = 4 ; (signed char) bl  >= 0 ; bl -- )
               {
                 bh = (b)( bx >> 4u*bl ) & 0x0fu ;
                 bh +=  ( bh <= 0x9 )  ?  0x30u  :  0x37u ;
                 m_buff[4-bl] = bh ; //output_c ( bh ) ;
               }
             if( TestCompleted_Output() )  output_s ( m_buff ) ;
             //----------

             ax = Load_from_i2c(1,bx,&bh,(b)m_addr) ;
             if ( ax != 0 )
               {
           end1: ptr = _NoConnect_i2c_txt ;
                 goto end2;
               }
               //   �������� ����� ������� ���������� �� ������������ �����
               // ���������� ������.
             if ( bh != (b)bx )
               {
                 ptr = _Error_i2c_txt ;
           end2: output_s ( m_buff ) ; // ����� ��������� ������ ���������.
                 for ( m_time = Timer1_Ovr ; (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0); ) ;
                 goto end3;
               }
           }
         ptr = "  Ok. "  ;
   end3:
         output_s ( ptr ) ; // ����� (��)�����������.
         for ( m_time = Timer1_Ovr ; (u)((w)(Timer1_Ovr-m_time)) < _Sec(3.0); ) ;
         goto end; */
    }

  return ;
}


