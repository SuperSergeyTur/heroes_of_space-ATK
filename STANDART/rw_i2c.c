#if !defined( _CM3_) || defined (_EEPROM)

void ReadWrite_i2c ( word flash_begin, word flash_end, byte flash_address )
{
  static byte count ;     //�������
  static byte crs   ; //����������� �����
  static byte size ;  //������ ����� ������

  /*register*/ word ax ;
  /*register*/ byte bh ;

  if ( M_FirstCall == 1 )
  {         //������� �����
    m_ext = Pult_Prog_Addr ;// ��������� ��� ������� ����� ��� �� �������
      if ( Mon.Pult == 1 ) Speed_Pult () ; //  "Speed_Pult () "
    Pult_Prog_Addr = m_ext ;
    //------
    M_FirstCall = 0 ;
    output_s ( "$" ) ;//������ �������� ��� ���������� ������� ������ �����/������
    //��� ������ ����� ��������� ������ �.�. ����� 8 (�.�. �������� ������ 56 ����)
#ifdef _Adr_Clock_i2c
    if ( flash_address == _Adr_Clock_i2c ) size = 8;
    else                                   
#endif      
    size = sizeof ( m_buff );
    output_c ( size ) ;
    output_c ( Hb ( flash_end - flash_begin ) ) ;
    output_c ( Lb ( flash_end - flash_begin ) ) ;
    Label = 0 ;
    count = 0 ;
    crs = 0 ;
    m_addr = flash_begin ;
    m_time = Timer1_Ovr ; //������ �����
    i2c_label = 0 ;
    return ;
  }

  switch ( Label )
  {
    //�������� ���������
    default: Label = 0 ;
    case 0:
             //���� �� 0.5� ������ �� ��������� � ������� �����
             if ( (u)((w)( Timer1_Ovr - m_time )) > _Sec ( 0.5 ) ) goto end ;
             //������� ������ �� ������ ����� �� ��� �����������
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( bh ) ;
               m_time = Timer1_Ovr ; //������ �����
               if ( bh == Return )  //����� �� ����� ������
               {
end:
                 Pult_Prog_Addr = _MainPultProg ;
                 M_FirstCall = 1 ;
                 return ;
               }
               else if ( bh == 'W' ) //������ i2c
               {
                 output_s ( "W" ) ;
                 Label++ ;
               }
               else if ( bh == 'R' ) //������ i2c
               {
                 output_s ( "R" ) ;
                 Label = 10 ;
               }
               else goto end ;
             }
             break ;
    //������ i2c
    case 1:
             //���� �� 0.5� ������ �� ��������� � ������� �����
             if ( (u)((w)( Timer1_Ovr - m_time )) > _Sec ( 0.5 ) ) goto end ;
             //������� ������ �� ������ ����� �� ��� �����������
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( bh ) ;
               m_time = Timer1_Ovr ; //������ �����
               if ( count < size )//��������� ��������� �����
               {
                 m_buff [ count ] = bh ;
                 crs += bh ;
                 count++ ;
               }
               else
               {
                 if ( bh == crs ) //�������� ����������� ����� �����
                 {
                   output_c ( crs ) ;
                   Label++ ;
                 }
                 else
                 {
                   output_c ( ~crs ) ;
                   goto end ;
                 }
               }
             }
             break ;
    case 2:
             if ( Mon.i2c_busy == 1 ) break ; //����, ���� ����������� ����
             Mon.i2c_busy = 1 ;  //������������� �������, ��� ������ ���� ������
             Label++ ;
    case 3:
             ax = xSave_into_i2c ( size , (b*)&m_buff , m_addr , flash_address ) ;
             if ( ax == 4 ) break ;  //���� = 4 - ������������ ������
             if ( ax == 1 )
             {
               mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
               Mon.i2c_busy = 0 ;  //������������� �������, ��� ������ ���� ��������.
               output_c ( ~crs ) ;
               goto end ;
             }
             else
             {
               Mon.i2c_busy = 0 ;  //������������� �������, ��� ������ ���� ��������.
               output_c ( crs ) ;
               m_addr += size ;
               if ( m_addr < flash_end ) //��� �� ����� ��������?
               {
                 m_time = Timer1_Ovr ; //������ �����
                 Label = 1 ;
                 count = 0 ;
               }
               else goto end ;
             }
             break ;
    //������ i2c
    case 10:
rw1:         if ( Mon.i2c_busy == 1 ) break ; //����, ���� ����������� ����
             Mon.i2c_busy = 1 ;  //������������� �������, ��� ������ ���� ������
             Label++ ;
    case 11:
             ax = xLoad_from_i2c ( size , m_addr , (b*)&m_buff , flash_address ) ;
             if ( ax == 4 ) break ;  //���� = 4 - ������������ ������
             if ( ax == 1 )
             {
               mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
               Mon.i2c_busy = 0 ;  //������������� �������, ��� ������ ���� ��������.
               output_c ( ~crs ) ;
               goto end ;
             }
             else
             {
               Mon.i2c_busy = 0 ;  //������������� �������, ��� ������ ���� ��������.
               count = 0 ;
               Label++ ;
             }
             //break ;
    case 12:
             if ( TestCompleted_Output ( ) != 0 )
             {
               if ( count < size )//�������� ��������� �����
               {
                 output_c ( m_buff [ count ] ) ;
                 crs += m_buff [ count ] ;
                 count++ ;
               }
               else
               {
                 output_c ( crs ) ; //�������� ����������� �����
                 m_time = Timer1_Ovr ; //������ �����
                 Label++ ;
               }
             }
             break ; //����� ��� ����, ����� ���������� ��������
    case 13:
             //���� �� 0.5� ������ �� ��������� � ������� �����
             if ( (u)((w)( Timer1_Ovr - m_time )) > _Sec ( 2.0 ) ) goto end ;
             //������� ������ �� ������ ����� �� ��� �����������
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( bh ) ;
               if ( bh == crs ) //�������� ����������� �����
               {
                 m_addr += size ;
                 if ( m_addr < flash_end ) //��� �� ����� ����������?
                 {
                   m_time = Timer1_Ovr ; //������ �����
                   Label = 10 ;
                   count = 0 ;
                   goto rw1;
                 }
                 else goto end ;
               }
               else
               {
                 output_c ( ~crs ) ;
                 goto end ;
               }
             }
             //break ;
  }
  Restart_Output ( ) ;
  return ;
}

#else  //_CM3_

void ReadWrite_i2c ( lword flash_begin, lword flash_end, byte flash_address )
{
  static byte count, count_povtor ;     //�������
  static byte crs, crs_old   ; //����������� �����
  static byte size ;  //������ ����� ������
  static lword m_addr2;
  static byte m_buff2[ TxBuffSize + 1 ];
  union {
          lword all;
          byte raz[ 4 ];
        }Siz;
  /*register*/ word ax ;
  /*register*/ byte bh ;

  if ( M_FirstCall == 1 )
  {         //������� �����
    m_ext = Pult_Prog_Addr ;// ��������� ��� ������� ����� ��� �� �������
      if ( Mon.Pult == 1 ) Speed_Pult () ; //  "Speed_Pult () "
    Pult_Prog_Addr = m_ext ;
    //------
    M_FirstCall = 0 ;

    Siz.all = flash_end - flash_begin;
    output_s ( "#" ) ;//������ �������� ��� ���������� ������� ������ �����/������
    size = sizeof ( m_buff2 );
    output_c ( size ) ;
    output_c ( Siz.raz[ 3 ] ) ;
    output_c ( Siz.raz[ 2 ] ) ;
    output_c ( Siz.raz[ 1 ] ) ;
    output_c ( Siz.raz[ 0 ] ) ;
    Label = 0 ;
    count = count_povtor = 0 ;
    crs = crs_old = 0 ;
    m_addr2 = flash_begin ;
    m_time = Timer1_Ovr ; //������ �����
    i2c_label = 0 ;
    return ;
  }

  switch ( Label )
  {
    //�������� ���������
    default: Label = 0 ;
    case 0:
             //���� �� 0.5� ������ �� ��������� � ������� �����
             if ( (u)((w)( Timer1_Ovr - m_time )) > _Sec ( 0.5 ) ) goto end ;
             //������� ������ �� ������ ����� �� ��� �����������
             if ( TestData_for_Input ( ) != 0 )
             {
               mInput_c ( bh ) ;
               m_time = Timer1_Ovr ; //������ �����
               if ( bh == Return )  //����� �� ����� ������
               {
end:
                 Pult_Prog_Addr = _MainPultProg ;
                 M_FirstCall = 1 ;
                 return ;
               }
               else if ( bh == 'W' ) //������ i2c
               {
                 output_s ( "W" ) ;
                 Label++ ;
               }
               else if ( bh == 'R' ) //������ i2c
               {
                 output_s ( "R" ) ;
                 Label = 10 ;
               }
               else goto end ;
             }
             break ;
    //������ i2c
    case 1:
             //���� �� 2.0� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_Ovr - m_time )) > _Sec( 2.0 ) ) goto end;
             if( TestData_for_Input() != 0 )
             {
               m_time = Timer1_Ovr; //������ �����
               mInput_c( bh );
               if( count < size ) //��������� ��������� �����
               {
                 m_buff2[ count ] = bh;
                 count++;
                 crs += bh;
               }
               else
               {
                 if( bh == crs ) //�������� ����������� ����� �����
                 {
                   output_c( crs );
                   count_povtor = 0;
                   crs_old = crs;
                   Label++;
                 }
                 else if( count_povtor < 5 )
                 {
                   output_c( 0xff );
                   count_povtor++;
                   crs = crs_old;
                   count = 0;
                 }
                 else
                 {
                   output_c( ~crs );
                   goto end;
                 }
               }
             }
             break;
    case 2:
             if( Mon.i2c_busy == 1 ) break; //����, ���� ����������� ����
             Mon.i2c_busy = 1; //������������� �������, ��� ������ ���� ������
             Label++;
    case 3:  //��� ��������� �������� ������ ���������� Byte_Relock ��� ������ ������
             //����� ������ Flash_store
             ax = Byte_Relock( size, (lw)m_addr2, (b*)&m_buff2, 3 );//xSave_into_i2c ( size , (b*)&m_buff2 , m_addr2 , flash_address ) ;
             if( ax == 4 ) break; //���� = 4 - ������������ ������
             if( ax == 1 )
             {
               mSet_ServiceMsg( _Srv_NoWrite_i2c );
               Mon.i2c_busy = 0;  //������������� �������, ��� ������ ���� ��������.
               output_c( ~crs );
               goto end;
             }
             else
             {
               Mon.i2c_busy = 0;  //������������� �������, ��� ������ ���� ��������.
               output_c( crs );
               m_addr2 += size;
               if( m_addr2 < flash_end ) //��� �� ����� ��������?
               {
                 m_time = Timer1_Ovr; //������ �����
                 Label = 1;
                 count = 0;
               }
               else
               {
                 Label++;
               }
             }
             break;
    case 4:
             ax = Flash_Store( 1 );
             if( ax == 0 ) goto end;
             break;

    //������ i2c
    case 10:
             if( Mon.i2c_busy == 1 ) break; //����, ���� ����������� ����
             Mon.i2c_busy = 1;  //������������� �������, ��� ������ ���� ������
             Label++;
    case 11:

             ax = xLoad_from_i2c( size , m_addr2 , (b*)&m_buff2 , flash_address );
             if( ax == 4 ) break;  //���� = 4 - ������������ ������
             if( ax == 1 )
             {
               mSet_ServiceMsg( _Srv_NoRead_i2c );
               Mon.i2c_busy = 0;  //������������� �������, ��� ������ ���� ��������.
               output_c( ~crs );
               goto end;
             }
             else
             {
               Mon.i2c_busy = 0;  //������������� �������, ��� ������ ���� ��������.
               count = 0;
               Label++;
             }
    case 12:
             if( TestCompleted_Output() != 0 ) //�������� ��������� �����
             {
               if( count < size )
               {

                  output_c( m_buff2[ count ] );
                  crs += m_buff2[ count ];
                  count++;
               }
               else
               {
                 output_c( crs ); //�������� ����������� �����
                 Label++;
                 m_time = Timer1_Ovr; //������ �����
               }
             }
             break; //����� ��� ����, ����� ���������� ��������
    case 13:
             //���� �� 2.0� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_Ovr - m_time )) > _Sec ( 2.0 ) ) goto end;
               //������� ������ �� ������ ����� �� ��� �����������
             if( TestData_for_Input() != 0 )
             {
               mInput_c( bh );
               if( bh == crs ) //�������� ����������� �����
               {
                 crs_old = crs;
                 count_povtor = 0;
                 m_addr2 += size;
                 if( m_addr2 < flash_end ) //��� �� ����� ����������?
                 {
                   m_time = Timer1_Ovr; //������ �����
                   Label = 10;
                   count = 0;
                 }
                 else goto end;
               }
               else if( bh == 0xff )
               {
                 if( count_povtor < 5 )
                 {
                    count_povtor++;
                    crs = crs_old;
                    Label = 12;
                    count = 0;
                 }
                 else
                 {
                   output_c( ~crs );
                   goto end;
                 }
               }
               else
               {
                 output_c( ~crs );
                 goto end;
               }
             }
  }
  Restart_Output();
  return;
}

#endif
