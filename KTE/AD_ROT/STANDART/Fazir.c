

//    ���������  ���������  ��������  ����  �  ������  �������  �
//  �������������  �����������  ������  ����  ���������� .

/*------------------------------------------------------------------*/
/*   ��������� ����� ���� ������� ������ � ���� ������ ���������� ���
 * ���������� ������� "����������".
 *   ����� ��������� �������������� �� ������ ��������� ��������.
 *   ����� ����� � ��������� �������� ��������� (���� ���� ������).
 *   ����� �����, �� ������� �������������� ����������� ���������, ��������
 * ����������� ��������� ������:
 * - '0' - ������ ��������� ;
 * - '1' - ������ ���� ;
 * - '2' - ������ ���� .
 * ����� ����� ������ ����� �������� �������� �� �������� ����
 * � ����� ���������� '0' ��������.
 *   ����� ��������� ���������� �� ������ �������
 * �������� �� ���� ��������� - ���� ���������� �� �� �������� ����� ���� ��
 * "-" � "+" �������� ���������� "Uac".
 *   ��������� ���� ��������� "�����" � ������������� 60-�������� ��������-
 * ������ � ��������� "0...300"-�������� ����������� ������� 'Enter'.
 *   ��������� ���� ��������� "�����" � ������������� 1-������ ��������������
 * � ��������� "0...+60" �������� ����������� ��������� ������:
 * - � ������� ���������� - ������� '+' ������ ;
 * - � ������� ���������� - ������� '-' ������.
 *
 *   � �������� ������� ���� ��������� ��������� ����������� ��� �
 * ����������� ��� ���� ���, ������� �� ���� ��� ������������:
 * - ����� ���������, ��� �������� �������� ������� �� ��:
 *                                          �
 *                                          � x = 0, ��  _r.FazirovVS = 1 ;
 * x = ����� ����� �� ( � / 60���. ), ���� <
 *                                          � x > 0, ��  _r.FazirovVS = 7 - x ;
 *                                          �
 * - ���� ���������� ��� ������� ��������� �� ��:
 *        _r.FazirovUgol = ������� ����� �� ( � / 60���. ) .
 *
 *   ����� �� ��������� �������������� �������� ������� 'Esc', ��� ����
 * �������� ���� ��������� �������� ������ ���������� ������������.
 */
//-------------------

#ifndef  _Fazir_txt
  #define _Fazir_txt   _Fazir_vozb_txt
#endif

#ifdef  _SIFU2_
  #define _max_num_most  4
  const char* num_txt[_max_num_most] =
  {
    "1(3)",
    "2(4)",
    "3(1)",
    "4(2)"
  };
#else
  #define _max_num_most  2
  const char* num_txt[_max_num_most] =
  {
    "1",
    "2"
  };
#endif

//-------------------

void Fazirovka ( void )
{
  register byte bh ;
 // word  ax ;
  word  bx ;


              //  �������� ������: ������ ������ �����.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


      if ( M_FirstCallFazir == 1 )  /*  ������������� ������� ����� ��� �������  */
        {                      /* ���������� ������� ...                    */
         output_s ( _Fazir_txt ) ;

         Isp._.Predupr = 1  ;// ����� �� ������ ������� "����������".
      /*    if ( Pex_c._.Gotov == 1 )  //  "���������� ������� ����"
            {
              Pult_Prog_Addr = 0  ;
              output_s ("\r\n ���������� ��� '����������'.") ;
            }
          else
            {
              M_FirstCallFazir = 0 ;
              LabelFazir = 0 ;
            }
          return ;
       */
          M_FirstCallFazir = 0 ;
          LabelFazir = 0 ;
          m_index = 0;
          return ;
        }

          /*   �������� ����, ��� �������� ������������� ���������� � ����,
           * � �� ������������� ��������, �������� "Id_max".
           */
  {
//#ifndef _AD_ROT
    if ( LabelFazir != 25 )
//#else
//    if ( LabelFazir < 25 )  // ��� ��������� �������� ���� ��� �� � �������� ��� �� ����� ������������� ����� �� � ���� .
//#endif
    {
      if ( LabelFazir >= 10 && S.Alfa_Old != 0 )
        {
//#ifdef _AD_ROT
//          if ((u)((w)(Timer1_Ovr - Time_TestFaz))> _Sec(1.5))
//          {
//#endif          
          output_s ( _Fazir_sdvig_txt ) ;
          goto  end1 ;
//#ifdef _AD_ROT
//          }
//#endif          
        }
       // 21.05.2009 DAN - ��� ������� �������� ��������� .
      if ( LabelFazir > 17 && Otkl_Imp != 0 )
        {
          output_s ( _Fazir_sdvig_txt ) ;
          goto  end1 ;
        }
    }
  }
    switch ( LabelFazir )
     {
      default:
      case 0: output_s ( "\n" ) ;
              LabelFazir = 1 ;
      case 1:
          if ( TestCompleted_Output() )
            {
              if ( m_index == 0 ) output_s ( _Fazir_Jakor ) ;
              else                output_s ( _Fazir_Vozb  ) ;
              LabelFazir = 2 ;
              break ;
            }

      case 2:
          if ( TestData_for_Input() )
            {
              mInput_c ( bh ) ;
                  if ( bh == Return )  /* ����� �� ����� ������ */
                    {
                      Label = 0, M_FirstCallFazir = 1 ;  //Pult_Prog_Addr = _MainPultProg , M_FirstCall = 1 ; //  // 20.05.2020
                      Isp._.Predupr = 0  ;
                      m_index = F2regim;//0; // 27.05.2020 ��� ������ �� ��������� ����������� ������ "���������"
                      return ;   // �������� ��� �����-�� ����.
                    }
                  else if ( bh == Up || bh == Down ) /* �������� �����. */
                    {
                      m_index = ~m_index,  LabelFazir = 1 ;
                    }
                  else if ( bh == Enter )
                    {
                      if ( m_index == 0 ) LabelFazir = 3  ;
                      else
                       {
                         LabelFazir = 30 ;
                       }
                    }
                  else    Klav_Buff = bh;
            }
          break ;
      case 3:
          output_s ( _Fazir_rot_txt ) ; // ����� "�����.������:"
                      Time_TestFaz = Timer1_Ovr;
                      
       //   mVkl_Imp( _All_imp ) ; // ������������� ������� �� ��������.
          S.NumMost = 0 ;        // ������ � ����� �� ������� ����������.
          //m_index = 1 ;
          m_ext = _r.S_Alfa_Min  ;   // ���������� �������.
          _r.S_Alfa_Min = 0 ;           // ����� ��������� � ����.
          S.Alfa = 0 ;
#ifdef _SIFU2_
          S2.Alfa = 0;
#endif
          m_time = Timer1_Ovr ;
#ifdef _AD_ROT
          LabelFazir = 4 ;
          break ;

      case 4:
          if ( (u)((w)(Timer1_Ovr - m_time)) > _or.T_zaderg_pusk/2 )
          {
             // ���� �������� ���� �� ������ , �� ���� ����� ������� ����� � �������� ����� ����� 2 �������� .
             // ������������ ���� ����� ����� �������� �������� ����� ������� �� .
             // ������� ������� �������� �� ������ ����� �������� ������ .
             //----
             // ���������� ���� ���������� ����� ����� , �.�. ����� ����������� ��������/����������
             // ������ ������� � ������ �������� �������� ������ ������� .
             if ( (sw)SkorRot > _Skor_nom( 1.5 ) ) flgO._.NeFaznRot = 1 ;
             else                                  flgO._.NeFaznRot = 0 ; 
             
             //----
             LabelFazir = 5 ;
          }
          break ;

      case 5:  /* ��������, ����� �������� ������ ���������� � ����. */
          if ( (u)((w)(Timer1_Ovr - m_time)) < _or.T_zaderg_pusk  )
          {
             mVkl_Imp( _All_imp ) ; // ������������� ������� �� ��������.
            
             S.NumMost = 1 ;
             LabelFazir = 17 ; // ���� ������ ���� , ����� ������ ����� .
             output_c ( '\n' ) ;
             break ;
          }
#else
          LabelFazir = 5 ;
          break ;

      case 5:  /* ��������, ����� �������� ������ ���������� � ����. */
          if ( (u)((w)(Timer1_Ovr - m_time)) < (w)_Sec( 0.2 ) ) break ;

          output_c ( '\n' ) ;
          LabelFazir = 10 ;
          break ;

      case 10:
          if ( TestCompleted_Output() )
            {       //   ����������� ��������.
              output_s ( _Fazir_Most )  ;
              output_s ( num_txt[m_index-1] )  ;
              LabelFazir = 15 ;
              break ;
            }
#endif
      case 15: /* ��������� �������� �� ������ �����, ��� 'while
                * �� �����������' (�.�. ��� ������ ����� ����� �� ����) */
          if ( TestData_for_Input() )
            {
              mInput_c ( m_ch ) ;
                  if ( m_ch == Return )  /* ����� �� ����� ������ */
                    {
                   end: Label = 0, M_FirstCallFazir = 1 ;//end: Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1 ; // // 20.05.2020
                      _r.S_Alfa_Min = m_ext ; // �������������� �������.
                      
                        Isp._.Predupr = 0  ;
                        //m_index = 0; // 27.05.2020 ��� ������ �� ��������� ����������� ������ "���������"
                        Init_posle_DistSbr () ;
                      return ;   // �������� ��� �����-�� ����.
                    }
                  else if ( m_ch == Up ) /* �������� �����. */
                    {
                      m_index++ ;
                      if ( m_index > _max_num_most ) m_index = 1  ;
                      LabelFazir = 10 ;
                      break ;
                    }
                  else if ( m_ch == Down ) /* �������� �����. */
                    {
                      m_index-- ;
                      if ( m_index == 0 ) m_index = _max_num_most  ;
                      LabelFazir = 10 ;
                      break ;
                    }
                  else if ( m_ch == Enter )
                    {
                      mVkl_Imp( _All_imp ) ; // ������������� ������� �� ��������.
                      if ( m_index <= 2 ) S.NumMost = m_index ;
                      else                S.NumMost = m_index-2 ;
                      LabelFazir = 17 ;
                      output_c ( '\n' ) ;
            }       }
          break ;

      case 17:   //   ����������� �������� ���� ���������.
          if ( TestCompleted_Output() )
            {
              if ( m_index <= 2 )
              {
                output_s ("\r���� =")  ;
                 float fax = (float)(sw) _r.Selsin[0].null/_wgLd(1) ;
                 if (!isnormal(fax))
                 {
                   fax = 0;
                 }
                if (fax < 0)
                {
                   output_c ( '-' ) ;
                }
                else
                {
                  output_c ( '+' ) ;
                }
                fax = fabsf(fax);
                bx = (b)(fax / 100) ;
                fax = fmodf(fax, 100.0);
                output_c ( (b)bx + 0x30 ) ;                
                bx = (b)(fax / 10) ;
                output_c ( (b)bx + 0x30 ) ;
                bx = (b)((w)fax % 10) ;
                output_c ( (b)bx + 0x30 ) ;
                output_s (" ���");
              }
              LabelFazir = 20 ;
              break ;
            }

      case 20: /* ��������� �������� �� ������ �����, ��� 'while
                * �� �����������' (�.�. ��� ������ ����� ����� �� ����) */
      if ( TestData_for_Input() )
        {
          mInput_c ( m_ch ) ;
              if ( m_ch == Return || m_ch == Enter)  /* ����� �� ����� ������ */
                {
                  output_c ( '\n' ) ;
                  mOtkl_Imp( _VR1_imp ) ;
                  LabelFazir = 10 ;
                  //m_index = 0; // 27.05.2020 ��� ������ �� ��������� ����������� ������ "���������"
                }
              else if ( m_ch == Up ) //��������� �� ������ � ��������� "1" ���.
                {
                    LabelFazir = 17 ;
                  if ( m_index <= 2 )
                  {
                    _r.Selsin[0].null += _wgL(1);
                    if (  (sw)_r.Selsin[0].null > (sw)_wgL180 )  _r.Selsin[0].null = (sw)_wgL180;
                  }
                }
              else if ( m_ch == Down ) /* ��������� �� ������ � ��������� "1" ���.*/
                {
                  LabelFazir = 17 ;
                  if ( m_index <= 2 )
                  {
                    _r.Selsin[0].null-= _wgL(1);
                    if ( (sw)_r.Selsin[0].null < (sw)(~_wgL180+1))  _r.Selsin[0].null = (sw)(~_wgL180+1) ;
                  }
                }
        }
            break ;
          //----------
        end1:
               mOtkl_Imp( _VR1_imp ) ;
               m_time = Timer1_Ovr,  LabelFazir = 25 ;
            break ;

#ifdef _SIFU_Syn2    // ���� �� ��������� ������������� �� ����� ��� ����.
      case 21:
          if ( TestCompleted_Output() )
            {
              if ( TestData_for_Input() ) // ����� � �����
                {                         // �� ����������� ������� ,
                  mInput_c ( m_ch ) ;
                }
              if ( (u)((w)(Timer1_Ovr - m_time)) >= (w)_Sec( 1.5 ) )
                {
                  LabelFazir = 22 ;
                }
            }
            break ;

      case 22:
              if ( TestCompleted_Output() )
                {       //   ����������� �������� ����� .
                  output_c ( '\n' ) ;
                  output_s ( _Fazir_Most )  ;
                  output_s ( num_txt[m_index-1] )  ;
                  output_c ( '\n' ) ;
                  LabelFazir = 17 ;
                  break ;
                }
#endif

      case 25:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) )  goto end;
            break ;

//-----------------------------------------------------------------------------
//    ���������  ���������  ����  �����������  ��  �������  �����  ���������� :
#ifdef _Vozb_KTE
      case 30:
              output_s ( _Fazir_txt ) ;
              // ������ � ����� �� ������� ����������.
              // ����������� ������ �������� � "������ ����������" , �������
              V.flg._.Otkl_Imp |= _V_VR1_otkl_imp ;// ������� �������� .
              m_index = 1 ;
              m_ext = _r.V_Alfa_Min  ;   // ���������� �������.
              _r.V_Alfa_Min = 0 ;        // ����� ��������� � ����.
              V.Alfa = 0 ;
              m_time = Timer1_Ovr ;
              LabelFazir = 50 ;
            break ;

      case 50:  /* ��������, ����� �������� ������ ���������� � ����. */
          if ( (u)((w)(Timer1_Ovr - m_time)) < (w)_Sec( 0.2 ) ) break ;

          output_c ( '\n' ) ;
          V.flg._.Otkl_Imp = 0 ; // ��������� ��������� .
          LabelFazir = 170 ;
          break ;

      case 100:
//-----
          V.flg._.Otkl_Imp |= _V_VR1_otkl_imp ;// ������� �������� .
//----- // ��������� ��� ������ �� "Esc".
                    {
                end4: Label = 0, M_FirstCallFazir = 1 ; //Pult_Prog_Addr = _MainPultProg ,  M_FirstCall = 1 ;//21.05.2020
                      //m_index = 0; // 27.05.2020 ��� ������ �� ��������� ����������� ������ "���������"
                      _r.V_Alfa_Min  =  m_ext ;  // �������������� �������
                        V.flg._.fazir = 0 ; // ������� ��������� ����������� ��� ��������� ��� .
                        Isp._.Predupr = 0  ;
                        Init_posle_DistSbr () ;
                        V.Alfa = _r.V_Alfa_Max ;   // �� ������ ������.
                      return ;   // �������� ��� �����-�� ����.
                    }
//-----
      case 170:   //   ����������� �������� ���� ���������.
          if ( TestCompleted_Output() )
            {
                output_s ("\r N = ")  ;
                m_ch = _r.V_FazirovVS + 0x30 ;
                output_c ( m_ch ) ;
                output_s (", F = ")  ;

                ax = _r.V_FazirovUgol / (w)_Grad( 1.0 ) ;
                bx = ax / 10 ;
                output_c ( (b)bx + 0x30 ) ;
                ax = ax % 10 ;
                output_c ( (b)ax + 0x30 ) ;
              LabelFazir = 200 ;
              break ;
            }

      case 200: /* ��������� �������� �� ������ �����, ��� 'while
                * �� �����������' (�.�. ��� ������ ����� ����� �� ����) */
      if ( TestData_for_Input() )
        {
          mInput_c ( m_ch ) ;
              if ( m_ch == Return )  /* ����� �� ����� ������ */
                {
                  output_c ( '\n' ) ;
                  LabelFazir = 100 ;

                }
     #ifdef _SIFUV_Syn2    // ���� �� ��������� ������������� �� ����� ��� �����.
              else if ( m_ch == Up || m_ch == Down || m_ch == Enter )
                {
                  output_s ( _Fazir_auto_txt ) ; // ��������� ���������� .
                  m_time = Timer1_Ovr ; // ��������� �������� .
                  LabelFazir = 210 ;
                  break ;
                }
     #else
              else if ( m_ch == Up ) /* ��������� �� ������ � ��������� "1" ���.*/
                {
                  _r.V_FazirovUgol += _Grad( 1.0 );
                  if ( _r.V_FazirovUgol > _Grad( 60.0 ) ) _r.V_FazirovUgol = _Grad( 60.0 );
                  LabelFazir = 170 ;
                }
              else if ( m_ch == Down ) /* ��������� �� ������ � ��������� "1" ���.*/
                {
                  _r.V_FazirovUgol -= _Grad( 1.0 );
                  if ( (sw)_r.V_FazirovUgol < 0 )  _r.V_FazirovUgol = 0 ;
                  LabelFazir = 170 ;
                }
              else if ( m_ch == Enter ) /* �������� ����� ��.*/
                {
                  _r.V_FazirovVS --;             // ���������� ���������� � ������� ����������.
                  if ( _r.V_FazirovVS  == 0 )  _r.V_FazirovVS  = 6;
                  LabelFazir = 170 ;
                }
     #endif
        }
            break ;
          //----------
        end3:
               V.flg._.Otkl_Imp |= _V_VR1_otkl_imp ;// ������� �������� .
               m_time = Timer1_Ovr,  LabelFazir = 250 ;
            break ;

#ifdef _SIFUV_Syn2    // ���� �� ��������� ������������� �� ����� ��� �����.
      case 210:
          if ( TestCompleted_Output() )
            {
              if ( TestData_for_Input() ) // ����� � �����
                {                         // �� ����������� ������� ,
                  mInput_c ( m_ch ) ;
                }
              if ( (u)((w)(Timer1_Ovr - m_time)) >= (w)_Sec( 1.5 ) )
                {
                  LabelFazir = 220 ;
                }
            }
            break ;

      case 220:
              if ( TestCompleted_Output() )
                {       //   ����������� �������� "��������� �����:" .
                //output_c ( '\n' ) ;
                  output_s ( _Fazir_txt ) ;
                  output_c ( '\n' ) ;
                  LabelFazir = 170 ;
                  break ;
                }
#endif

      case 250:
              if ( (u)((w)(Timer1_Ovr-m_time)) > _Sec( 2.0 ) )  goto end4;
            break ;

#endif

//-----------------------------------------------------------------------------
//    ���������  ��������� ���������� �������� ���� ��� ����������������� ��������� ��� :
#ifdef _AD_ROT
      case 30:
              output_s ( _Fazir_stup_txt ) ; // ����� "�����.��������:" ��� "�����.��:"
              output_c ( '\n' ) ;
              // ������ � ����� �� ������� ����������.
              m_index = 1 ;
              m_ext = 0 ; // ������� ������� .
              m_time = Timer1_Ovr ;
              LabelFazir = 170 ;
            break ;

      case 100:
//-----
           mFzapoln5_stop() ; // ������� ��
           mPort_ImpV( 0x3f ) ;
           flgO._.V_trig = 0  ;// ������� �������� .
//----- // ��������� ��� ������ �� "Esc".
                    {
                      Label = 0, M_FirstCallFazir = 1 ; //Pult_Prog_Addr = _MainPultProg ,  M_FirstCall = 1 ;//21.05.2020
                      //m_index = 0; // 27.05.2020 ��� ������ �� ��������� ����������� ������ "���������"
                        Isp._.Predupr = 0  ;
                        Init_posle_DistSbr () ;    // �� ������ ������.
                      return ;   // �������� ��� �����-�� ����.
                    }
//-----
      case 170:
          if ( TestCompleted_Output() )
            {
#ifdef _UPTF
                output_s ("\r�������=")  ;
                m_ch = m_ext + 0x30 ;
                output_c ( m_ch ) ;
#else
                if ( m_ext == 0 ) output_s ("\r�� �����    ") ;
                else              output_s ("\r�� �����.  ") ;
#endif
              LabelFazir = 200 ;
              break ;
            }

      case 200: /* ��������� �������� �� ������ �����, ��� 'while
                * �� �����������' (�.�. ��� ������ ����� ����� �� ����) */
      if ( TestData_for_Input() )
        {
          mInput_c ( m_ch ) ;
              if ( m_ch == Return )  /* ����� �� ����� ������ */
                {
                  output_c ( '\n' ) ;
                  LabelFazir = 100 ;

                }
              else if ( m_ch == Up ) // ��������� ������� �� "1" .
                {
                  m_ext += 1 ;
#ifdef _UPTF
                  if ( m_ext > 3 ) m_ext = 0 ;
#else
                  if ( m_ext > 1 ) m_ext = 0 ;
#endif
                  LabelFazir = 170 ;
                }
              else if ( m_ch == Down ) // ��������� ������� �� "1" .
                {
                  m_ext -= 1 ;
#ifdef _UPTF
                  if ( (sw)m_ext < 0 ) m_ext = 0 ;
#else
                  if ( (sw)m_ext < 0 ) m_ext = 1 ;
#endif
                  LabelFazir = 170 ;
                }
              //----
              switch ( m_ext )
              {
                    default:
                    case 0:
                        mFzapoln5_stop() ; // ������� ��
                        flgO._.V_trig = 0 ;
                        mPort_ImpV( 0x3f ) ;
                    break ;

                    case 1:
                        if ( flgO._.V_trig == 0 )
                        {
                            mFzapoln5_stop() ;  // �������
                            mFzapoln5_start() ; // ������ �� �� ����������� ��������
                            flgO._.V_trig = 1 ;
                        }
#ifdef _UPTF
                        mPort_ImpV( 0x37 ) ; //ax = 0x37 ; // 11 0111 - VT4
#else
                        // �������� ��� ��� ����������� ��������� ������������ :
                        mPort_ImpV( 0x30 ) ; //ax = 0x30 ; // 11 0000 - V41 (�����������) , V31 , V24 , V12 ( ��������� V29 , V28 , V27 �������������� )
#endif
                    break ;

                    case 2:
                        if ( flgO._.V_trig == 0 )
                        {
                            mFzapoln5_stop() ;  // �������
                            mFzapoln5_start() ; // ������ �� �� ����������� ��������
                            flgO._.V_trig = 1 ;
                        }
                        mPort_ImpV( 0x27 ) ; //ax = 0x27 ; // 10 0111 - VT4 , VT5
                    break ;

                    case 3:
                        if ( flgO._.V_trig == 0 )
                        {
                            mFzapoln5_stop() ;  // �������
                            mFzapoln5_start() ; // ������ �� �� ����������� ��������
                            flgO._.V_trig = 1 ;
                        }
                        mPort_ImpV( 0x07 ) ; //ax = 0x07 ; // 00 0111 - VT4 , VT5 , VT6
                    break ;
              }

        }
            break ;
          //----------

#endif
     }

 Restart_Output ()  ;

  return ;
}
