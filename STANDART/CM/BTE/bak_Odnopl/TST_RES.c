// ��������� ���������� ������������ ��������� � ������ ������� � ������������� ����������� ������ ��� ����������
// ��������� ����:
//   1. �����.���. (��������� ���������)
//      1.1 RES0-(1-�� �� 2-�� ������. ����������) , ��� 1-�� �������� �������� �������������� ���������� (�������� Ud) 
//      1.2 RES0-(2-�� �� 2-�� ������. ����������) , ��� 2-�� �������� �������� �������������� ���������� (�������� Id)
//      1.3 RES1-(1-�� �� 2-�� ������. ����������) , ��� 1-�� �������� �������� �������������� ���������� (�������� Is)
//      ...
//      1.n
//           1.1.1  �����. ������. (��������� ��������� ���������) 
//                  �� ������� "Enter" � ������� ������� ������������ 2-� ��������� ( ��  ,  ������������� ����������(%)  )
//                                     � ������ ��������, ������� ������������� ��������� � ������� ������ 

//              1.1.1.1 ������� "+" ��������� ����� �������� ��������� 
//              1.1.1.2 ������� "-" ��������� ����� �������� ���������
//              1.1.1.3 ������� "Esc" ���������� � RAM �� ��� ��������� ��� ������ �����
//              1.1.1.4 ������� "Enter" ��������� ������� (������� ���������� ������ ��� �� ���������� ��� ���������� ���� ��������):

//                  1.1.1.4.1 ��������� � RAM �������� ��������
//                  1.1.1.4.2 ������� � ROM ������� �������� � �������� ��� � EEPROM � ����� "���������� ���������" ��������� ��� ��������
//                  1.1.1.4.3 �������� � ROM ������������ �������� � RAM
//                  1.1.1.4.4 ������������� ��� �������� � RAM � ROM ����������
//                  1.1.1.4.5 ������� �������� �� �������� ���� ��� >= 0xff ���������� � ���� 0x01 ����� ������ ���������
//                  1.1.1.4.6 ������� � ������, ��� �������� � �������� � ���, ��� ������ ��������

//���������� �  1.1.1:  ��� ������������� ������ ��������� ��������� �� 4-� ��� ( "�����/���.���." )
//                      ��� ���������� ������ ������ �� ���������

//           1.1.2  ������� ���. (������� ���������� ��������� ��������� ����������� ���� "�����. ������." � � ������� �� "Enter") 
//              1.1.2.1 �� ������� "+" ��� "-"  ���������� ��������� ������ ������ ������ ��������� (��� �������� I2C)
//              1.1.2.2 �� ������� "Esc" ��� "Enter"  ���������� ����� �� ������� �������
//���������� �  1.1.2:  ��� ������������� ������ ��������� ��������� �� 4-� ��� ( "��������� ���." )
//                      ��� ���������� ������ ������ �� ���������

//           1.1.3  ����. �����. (���������� �������� ��������� ��������� � ��, ������� ������������� �������� (������� ���. - 1) �.�. ������������� ���������) 
//              1.1.3.1 �� ������� "+" ��� "-"  ���������� ��������� ������ ������ ������ ��������� (��� �������� I2C)
//              1.1.3.2 �� ������� "Esc" ��� "Enter"  ���������� ����� �� ������� �������
//���������� �  1.1.3:  ��� ������������� ������ ��������� ��������� �� 4-� ��� ( "��������� ���." )
//                      ��� ���������� ������ ������ �� ���������





void TstRES_Drive ( void )
{
   register word  ax ;
           lword  lax ;   
   static   word  time, time_Ind ;
   static   word  count_con, count_Fault_Comp ;
   static   word  Res_RAM_copy ;
   static   word  ResFirst_con ;

           //  �������� ������: ������ ������ �����.
   if ( Password_control ( 2 ) == 0 )  return   ;

              

   if ( M_FirstCall == 1 )  /*  ������������� ������� ����� ��� �������  */
     {                      /* ���������� ������� ...                    */
       M_FirstCall = 0 ;
       m_index = 0 , Label = 0 ;
       m_ext = 0 ;
       count_con = 0 ;

   //    if ( Mon.Password_Ok == 0 )  Label = 200 ;  // ���� � ��������������� � ������.
   //    else                         Label = 210 ;  // ������� ����.

       return ;
     }

  switch ( Label )
    {
      default: Label = 0 ;
      case 0:
                  output_s ( _RES_Tst ) ;
                  output_c ( '\n' ) ;
                  Label = 4;
      case 4:
             // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( RES_com_tab[m_index].RES_tab.txt ) ;
                  Label = 1 ;
                  break ;
                }
      case 1:  if (  TestData_for_Input() )
                {
                  mInput_c ( m_ch ) ;
                  if ( m_ch == Return )
                    {
                      Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ;
                      return ;   // �������� ��� �����-�� ����.
                    }
                  else if ( m_ch == Down )
                    {
                      if ( ++m_index >= _RES_Ntab ) m_index = 0 ;
                      Label = 4 ;
                    }
                  else if ( m_ch == Up )
                    {
                      if ( m_index == 0 ) m_index = _RES_Ntab ;
                      m_index-- ;
                      Label = 4 ;
                    }    // ������� � ��������� ��������� 
                  else if ( m_ch == Enter )
                    {
                      Label = 20 ;
                        // �������� � ������� ��������� ���������
                      m_ext = 0;

                      output_s ( "\n\r  " ) ;
                      output_s ( RES_com_tab[m_index].RES_tab.txt ) ;
                      output_s ( ":\n" ) ;
                    }
                  else
                  {
                    Klav_Buff = m_ch;
                  }
                }
               if (AWelcome != AWell_old )
                {
                  AWell_old = AWelcome;
                  Label = 4;
                }

              break ;
            //-------------------

      case 20:  // �������� ���������� ����������� ������.
                if ( TestCompleted_Output() )
                 {
                   output_c ( '\r' ) ;
                   output_s( AWelcome );
                   if      ( m_ext == 0 )    output_s ( _RES_NASTR_DIAP ) ;
                   else if ( m_ext == 1 )    output_s ( _RES_COUNT_NASTR ) ;
                   else                      output_s ( _RES_PAST_NASTR ) ;
                   Label = 21 ;
                   break ;
                 }

      case 21:  // ����� ������ : 
                if ( TestData_for_Input() )
                  {
                    mInput_c ( m_ch ) ;
                    if ( m_ch == Return )  // ����� �� ����� �������
                      {
                        output_c ( '\n' ) ;
                        Label = 0 ;
                      }
                    else if ( m_ch == Down )
                      {
                        if ( ++m_ext >= _RES_Ntab2 ) m_ext = 0 ;
                        Label = 20 ;
                      }
                    else if ( m_ch == Up )
                      {
                        if ( m_ext == 0 ) m_ext = _RES_Ntab2 ;
                        m_ext-- ;
                        Label = 20 ;
                      }
                    else if ( m_ch == Enter )
                      {
                          // ������� ������� ���������� ��������� � ���������
                        count_con = 0 ;
                          // ������� ������ ������ ��������� �������� RAM ��� �������� ���� ��� ������ �� Esc
                        ResFirst_con = 0 ;

                          // ������� � ����� "��������� ���������":
                        if      ( m_ext == 0 )
                         {

                           Label = 22, time = timer1 ;
                           output_s ( "\n\r  " ) ;
                             // �� �����. ������ �����. �� � �����. ��������., ������� �������. ���������
                           output_s ( RES_com_tab[m_index].RES_DataAch.txt ) ;
                           output_s ( ":\n" ) ;



                         }
                          // ������� � ����� ��������� "������� ���������":
                        else if ( m_ext == 1 )  Label = 40, time = timer1 ;
                          // ������� � ����� ��������� "���������� ���������":
                        else if ( m_ext == 2 )  Label = 50, time = timer1  ;

                      }
                    else
                      {
                        Klav_Buff = m_ch;
                      }
                  }
                if (AWelcome != AWell_old )
                  {
                    AWell_old = AWelcome;
                    Label = 20 ;
                  }

              break ;

 //--------------------------------------------------------------------------------------------------------------------//
        
              
              
      case 22:     //  ����� "��������� ���������":
                   //  ���� ���� ������� ��������� �������


                  // ������� ������� �������� ��������� � �������� ��� � ����� ��� �������� �� Esc
               if ( TestCompleted_Output() )
                 {

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM ) ;

                   if ( ax == MCP4661_RETFUNC_FAILED )
                    {
                         // ���� ��� ������ �������� �������� � ������� ������ ���������
                         // ��������� ������������ �������� �� ��������� �����
                      if ( ++count_con > 3 )
                       {
                        count_con = 0 ;
                        Label = 38 ;
                        break ;
                       }

                    }
                   else
                    {
                       // ��� ������ ������ ������ �� ��������
                       
                       // ��� ������� ��������� ��� ����������, ��� ��� ��������� ������ "+", "-" ( ��������� ������������� ) �������� ���������
                       // ������������������� ��������. (�� 100 ��� ����� ������� 2-� ����)
                       // ������� ���� ����������� �� ��������� � �������� ��������� ���� ������ ��� ���
                     if ( ResFirst_con != 0 )          
                      { 
                        if ( ResCommon[ m_index ].Res_data_write != ResCommon[ m_index ].ResMemory.Res_RAM )
                         {
                          if ( ++count_Fault_Comp > 3 ) Label = 38 ;  
                          else                          Label = 24 ;
                          break ;
                         } 
                        
                      } 
                     
                       // ���� ����� � ������� ������ ��� ��������� �������� �������� �������������
                       // � �������� ��� ��� ������ �� "Esc" :
                     if ( ResFirst_con == 0 )
                      {
                         Res_RAM_copy = ResCommon[ m_index ].ResMemory.Res_RAM ;
                         ResFirst_con = 1;
                      }
                     Label = 26 ;
                    }

                   break ;
                 }
                 // ���  TestCompleted_Output   break �� ������ ���� ����� ���� ������ Esc


                 // ������� ����� ��������
      case 24:
                if (  TestCompleted_Output() )
                 {
                   ax = SetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM );

                   if ( ax == MCP4661_RETFUNC_FAILED )
                    {
                         // ���� ��� ������  �������� �������� � ������� ������ ���������
                         // ��������� �������� �� �� ��������� �����
                      if ( ++count_con > 3 )
                       {
                        count_con = 0 ;
                        Label = 38 ;
                        break ;
                       }

                    }
                   else
                    {
                      count_con = 0 ;
                        // �� ��������� ������� ������� ��� ��� ��������
                      Label = 22 ;
                      break ;
                    }
                 }
              
                break ;


      case 25:




      case 26:

                    // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                     // ����� ������������� � �� 
                     
                  // ���� ���� ������� �������� ��������� ����� ���� (�������� �������� ���. � ������� ����������� ���. �� ��� ������� �� 
                  //   � ���� �� �����, � � ����� �� ����)
               #ifdef _RES_IND_INVERT 
                  lax = ResCommon[ m_index ].ResConst.mashtab - 
                        (lw)(( (lw)ResCommon[ m_index ].ResMemory.Res_RAM * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
               #else
                  lax = (lw)(( (lw)ResCommon[ m_index ].ResMemory.Res_RAM * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;                  
               #endif


                  //output_s ( " R = " ) ;

                  m_ch = lax / 100000 + 0x30  ;
                  lax %= 100000 ;
                  output_c ( m_ch ) ;                  
                  
                  m_ch = lax / 10000 + 0x30  ;
                  lax %= 10000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 1000 + 0x30  ;
                  lax %= 1000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 100 + 0x30  ;
                  lax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 10 + 0x30  ;
                  lax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( lax + 0x30 ) ;

                  //output_s ( " �� " ) ;
                  output_s ( ", " ) ;

                     //  ����� ���������� ������
                    // ���� ������� == 0  (��� ����������, ������� ������������ �� ��� ���������� ���������� ����� ��� Id_max, ...)
                  if ( RES_com_tab[m_index].RES_DataAch.nom == 0 )
                    {
                     ax = 0 ;  
                     output_s ( "�����." ) ;                      
                    }
                  else
                    {
                       // ����� ����� ���������� ����������
                     ax = *(  w*)RES_com_tab[m_index].RES_DataAch.adr ;
                     
                     if ( (sw)ax >= 0 )  output_c ( '+' );
                     else
                       {
                         output_c ( '-' ); ;
                         ax = ~ax + 1 ;
                       }                     
                      
                     ax =  (w)( (slw) ax * (slw)100 * (slw)100 / (slw)RES_com_tab[m_index].RES_DataAch.nom ) ;

                  
                     
                     m_ch = ax / 10000 + 0x30  ;
                     ax %= 10000 ;
                     output_c ( m_ch ) ;

                     m_ch = ax / 1000 + 0x30  ;
                     ax %= 1000 ;
                     output_c ( m_ch ) ;

                     m_ch = ax / 100 + 0x30  ;
                     ax %= 100 ;
                     output_c ( m_ch ) ;

                     output_c ( '.' ) ;  // ����� ������� ����� .


                     m_ch = ax / 10 + 0x30  ;
                     ax %= 10 ;
                     output_c ( m_ch ) ;


           //        m_ch = ax / 1 + 0x30  ;  17-��� ������
           //        output_c ( m_ch ) ;
                    }
           //       output_s ( "% " ) ;

                  Label = 30 ;

                  time_Ind = Timer1_Ovr ;

                  break ;

                }



      case 30:


                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  // ����� �� ����� ������
                     {
                       Label = 32 ;
                     }
               #ifndef _RES_IND_INVERT 
                   else if ( m_ch == Up )
                     {
                         // �������� �� ����� �� ����� ��� ������� ��������� � max
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM < ResCommon[ m_index ].ResConst.Wiper_Data_max )
                        {
                           // ���������� ������ ��� ������
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM + 1 ;
                         count_Fault_Comp = 0;
                         Label = 24 ;
                        }
                     }
                   else if ( m_ch == Down ) // �������� ��������
                     {
                         // �������� �� ����. ������ 0
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM > 0  )
                        {
                           // ���������� ������ ��� ������
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM - 1 ;
                         count_Fault_Comp = 0 ;
                         Label = 24 ;
                        }
                     }
               #else
                   else if ( m_ch == Down  )
                     {
                         // �������� �� ����� �� ����� ��� ������� ��������� � max
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM < ResCommon[ m_index ].ResConst.Wiper_Data_max )
                        {
                           // ���������� ������ ��� ������
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM + 1 ;
                         count_Fault_Comp = 0 ;
                         Label = 24 ;
                        }
                     }
                   else if ( m_ch == Up ) // �������� ��������
                     {
                         // �������� �� ����. ������ 0
                       if ( ResCommon[ m_index ].ResMemory.Res_RAM > 0  )
                        {
                           // ���������� ������ ��� ������
                         ResCommon[ m_index ].Res_data_write = ResCommon[ m_index ].ResMemory.Res_RAM - 1 ;
                         count_Fault_Comp = 0 ;                         
                         Label = 24 ;
                        }
                     }                   
               #endif
                   
                   else if ( m_ch == Enter ) Label = 35 ; // �������� ������� .
                   else
                     {
                       Klav_Buff = m_ch;
                     }
                 }
                if (AWelcome != AWell_old )
                 {
                   AWell_old = AWelcome;
                   Label = 26 ;
                 }
                
                  // ���� ������ �� ������ ��� ����� �������� � ������� ������������ ���������
              if ( (u)(w)( Timer1_Ovr - time_Ind ) >= _Sec(0.20) && Label == 30 )  Label = 26 ;

              break ;


               // ������ Esc
        case 32:

              if (  TestCompleted_Output() )
                {
                    // ���� ������� �������� �� ����� ������ �������� � �������� �����
                  if ( ResCommon[ m_index ].ResMemory.Res_RAM != Res_RAM_copy )
                   {
                      // ���������� ������ ��� ������
                    ResCommon[ m_index ].Res_data_write = Res_RAM_copy ;
                    ax = SetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM );

                    if ( ax == MCP4661_RETFUNC_FAILED )
                     {
                          // ���� ��� ������  �������� �������� � ������� ������ ���������.
                          // ��������� �������� �� �� ��������� �����
                       if ( ++count_con > 3 )
                        {
                         count_con = 0 ;
                         Label = 38 ;
                         break ;
                        }

                     }
                    else
                     {
                       count_con = 0 ;
                         // �� ��������� ������� ������� ��������� �� �������� ���� ��������
                       Label = 33 ;
                       break ;
                     }
                   }

                }

        case 33:



                  // ������� ������� �������� ���������
               if ( TestCompleted_Output() )
                 {

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_RAM ) ;

                   if ( ax == MCP4661_RETFUNC_FAILED )
                    {
                         // ���� ��� ������ �������� �������� � ������� ������ ���������
                         // ��������� ������������ �������� �� ��������� �����
                      if ( ++count_con > 3 )
                       {
                        count_con = 0 ;
                        Label = 38 ;
                        break ;
                       }

                    }
                   else
                    {
                       // ��� ������ ������ ������ �� �������� �������� ��� �������� �������� ������������� �����������
                     if ( ResCommon[ m_index ].ResMemory.Res_RAM == Res_RAM_copy )
                      {
                        // ������ ��������� ��������� �������� � ���� ������� ����
                       Label = 20 ;
                      }
                     else
                      {
                        // ������ ����� ������ �������� ������ ��������� ����������� ������ �� ���� � ����������
                       Label = 38 ;
                      }

                    }

                   break ;
                 }

 //---------------------------------------------------------------------//
                 // ����� �� Enter
        case 35:
              if (  TestCompleted_Output() )
                {
                 ResCommon[ m_index ].Res_Err_Ret = SetResVal_Enter( &ResCommon[ m_index ] ) ;
                 ax = (w)ResCommon[ m_index ].Res_Err_Ret ;

                   // ������ ������ � �������� (������ ������ �� ���������)
                 if        ( ax == MCP4661_RET_RECORD_NO_FINISH || ax == MCP4661_RET_EEPROM_BUSY ) break ;
                   // ������ ���������� ���������
                 else if   ( ax == MCP4661_RET_DATA_OK )                 Label = 20 ;
                   // ������ ��� ������ ������
                 else if ( ( ax == MCP4661_RETFUNC_FAILED  )      ||
                           ( ax == MCP4661_RET_CONNECT_OVERFLOW ) ||
                           ( ax == MCP4661_RET_DATA_FAILED )
                         )                                               Label = 38 ;

                 break ;
                }


        case 38:

              if (  TestCompleted_Output() )
                {

                 time = Timer1_Ovr ;
                 Label = 39 ;
                 break ;
                }


        case 39:

                    // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( "�����/���.���." ) ;  //( "�����/���.���." ) ;
                    // ������� ��������� �� ����� ���� ��� ������/������ ���������
                  if ( (u)(w)(Timer1_Ovr - time) > _Sec( 4.0 ) )  Label = 20 ;
                  break ;
                }
                  break ;




 //--------------------------------------------------------------------------------------------------------------------//
                 //  ����� ��������� "������� ���������":

      case 40:



               if ( TestCompleted_Output() )
                 {

                      // �� �������� ����� ������ ���������� � EEPROM ����������� ����� 5 �� (�� ����� ������� ������ � ������ �� ����� ������)
                      // ��������� ����������� ������ ���� ��������� � ������ ������ �� ��������
                   if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) ) break ;

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_EEP_COUNT_SAVE ) ;

                   if ( ( ax == MCP4661_RET_EEPROM_BUSY ) || ( ax == MCP4661_RETFUNC_FAILED ) )
                    {
                         // ���� ��� ������ �������� �������� � ������� ������ ���������
                         // ��������� ������������ �������� �� ��������� �����
                      time = timer1 ;
                         // ������� ������� ���������� ��������� � ���������
                      if ( ++count_con > 3 ) count_con = 0, Label = 44 ;
                    }
                   else  Label = 42 ;

                   break ;
                 }

      case 42:

                    // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );

                    // ��������� ��������� ���� ��������
                  ax = ResCommon[ m_index ].ResMemory.Count_Save ;
                  output_s ( " ���= " ) ;  //( " ���= " ) ;

                    /*  ����� ���������� ��������� �������������. */

                  m_ch = ax / 100 + 0x30  ;
                  ax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = ax / 10 + 0x30  ;
                  ax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( ax + 0x30 ) ;

                  output_s ( " ���." ) ;  //( " ���." ) ;

                  Label = 46 ;

                  break ;
                }


      case 44:

                    // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( "��������� ���." ) ;  //( "��������� ���." ) ;

                  Label = 46 ;
                  break ;
                }

      case 46:

                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  // ����� �� ����� ������
                     {
                         // ������� � ������ ������
                       Label = 20 ;
                     }
                   else if ( m_ch == Up )
                     {
                         // ����������� ������ ������ ��������� ��� �������� "���������� ���������"
                         // ��������� �������� ��� �������� I2C ������� � ������� ���������
                       Label = 40 ;
                     }
                   else if ( m_ch == Down ) // �������� ��������
                     {
                         // ����������� ������ ������ ��������� ��� �������� "���������� ���������"
                         // ��������� �������� ��� �������� I2C ������� � ������� ���������
                       Label = 40 ;
                     }
                   else if ( m_ch == Enter ) Label = 20 ; // �������� ������� .
                   else
                     {
                       Klav_Buff = m_ch;
                     }
                 }
                if (AWelcome != AWell_old )
                 {
                   AWell_old = AWelcome;
                   Label = 42 ;
                 }

              break ;
            //-------------------


 //--------------------------------------------------------------------------------------------------------------------//
                 //  ����� ��������� "���������� ���������":

      case 50:

                if ( TestCompleted_Output() )
                 {

                      // �� �������� ����� ������ ���������� � EEPROM ����������� ����� 5 �� (�� ����� ������� ������ � ������ �� ����� ������)
                      // ��������� ����������� ������ ���� ��������� � ������ ������ �� ��������
                   if ( (u)(w)( timer1 - time ) <= _MkSec( 7*1000 ) ) break ;

                   ax = GetResistorValue( &ResCommon[ m_index ], RES_WIPER_EEP_PAST_SAVE ) ;

                   if ( ( ax == MCP4661_RET_EEPROM_BUSY ) || ( ax == MCP4661_RETFUNC_FAILED ) )
                    {
                         // ���� ��� ������ �������� �������� � ������� ������ ���������
                         // ��������� ������������ �������� �� ��������� �����
                      time = timer1 ;
                         // ������� ������� ���������� ��������� � ���������
                      if ( ++count_con > 3 ) count_con = 0, Label = 54 ;
                    }
                   else  Label = 52 ;

                   break ;
                 }

      case 52:

                    // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                 
                     // ��������� ��������� ���� ��������
                     // ����� ������������� � �� 
                     
                  // ���� ���� ������� �������� ��������� ����� ���� (�������� �������� ���. � ������� ����������� ���. �� ��� ������� �� 
                  //   � ���� �� �����, � � ����� �� ����)
               #ifdef _RES_IND_INVERT 
                  lax = ResCommon[ m_index ].ResConst.mashtab - 
                        (lw)(( (lw)ResCommon[ m_index ].ResMemory.Past_Save * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;
               #else
                  lax = (lw)(( (lw)ResCommon[ m_index ].ResMemory.Past_Save * ResCommon[ m_index ].ResConst.mashtab ) >> 8) ;                  
               #endif
                  
                  output_s ( " R = " ) ;
                  m_ch = lax / 100000 + 0x30  ;
                  lax %= 100000 ;
                  output_c ( m_ch ) ;                  
                  
                  m_ch = lax / 10000 + 0x30  ;
                  lax %= 10000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 1000 + 0x30  ;
                  lax %= 1000 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 100 + 0x30  ;
                  lax %= 100 ;
                  output_c ( m_ch ) ;

                  m_ch = lax / 10 + 0x30  ;
                  lax %= 10 ;
                  output_c ( m_ch ) ;

                  output_c ( lax + 0x30 ) ;
                  
                  output_s ( " �� " ) ;  //( " �� " ) ;

                  Label = 56 ;

                  break ;

                }



      case 54:

                    // �������� ���������� ����������� ������.
              if (  TestCompleted_Output() )
                {
                  output_c ( '\r' ) ;
                  output_s( AWelcome );
                  output_s ( "��������� ���." ) ;  //( "��������� ���." ) ;

                  Label = 56 ;
                  break ;
                }


      case 56:

                if ( TestData_for_Input() )
                 {
                   mInput_c ( m_ch ) ;
                   if ( m_ch == Return )  // ����� �� ����� ������
                     {
                         // ������� � ������ ������
                       Label = 20 ;
                     }
                   else if ( m_ch == Up )
                     {
                         // ����������� ������ ������ ��������� ��� �������� "���������� ���������"
                         // ��������� �������� ��� �������� I2C ������� � ������� ���������
                       Label = 50 ;
                     }
                   else if ( m_ch == Down ) // �������� ��������
                     {
                         // ����������� ������ ������ ��������� ��� �������� "���������� ���������"
                         // ��������� �������� ��� �������� I2C ������� � ������� ���������
                       Label = 50 ;
                     }
                   else if ( m_ch == Enter ) Label = 20 ; // �������� ������� .
                   else
                     {
                       Klav_Buff = m_ch;
                     }
                 }
                if (AWelcome != AWell_old )
                 {
                   AWell_old = AWelcome;
                   Label = 52 ;
                 }

              break ;

 //--------------------------------------------------------------------------------------------------------------------//


    }

 Restart_Output ()  ;

  return ;
}

