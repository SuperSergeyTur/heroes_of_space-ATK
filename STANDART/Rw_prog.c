void RW_Prog( word flash_begin, word flash_end, byte flash_address )
{
  #define _WAIT    _fSec ( 1.0 ) // ����� �������� ������

  static byte count;  // �������
  static byte crs;    // ����������� �����
  static byte size;   // ������ ����� ������
  union unSizeFile
  {
    word all;
    byte b[ 2 ];
  };
  static union unSizeFile SizeFile;
  static word CountByte;

  _register word ax;
  _register byte bh;

  enum{ m0 = 0, m1, m2,
        wr0,    wr1, wr2, wr3, wr4, wr5,
        rd0,    rd1, rd2, rd3, rd4, rd5, rd6, rd7, rd8, rd9, rd10,
        cl0,    cl1, cl2, cl3
      };

  if( M_FirstCall == 1 )
  {
      // ������� � ����� �������� ������
      m_ext = Pult_Prog_Addr; // ��������� ��� ������� ����� ��� �� �������
      if( Mon.Pult == 1 ) Speed_Pult( ); //  "Speed_Pult()"
      Pult_Prog_Addr = m_ext;
      crs = 0;
      M_FirstCall = 0;
      output_c( '@' );
      Label = m0;
      return;
  }

  switch( Label )
  {
      // �������� ���������
      default: Label = m0;
      case m0:
             if( TestCompleted_Output( ) != 0 )
             {
                 size = sizeof( m_buff ); // ������ ������
                 output_c( size );
                 crs -= size;
                 bh = Hb( flash_begin ); // ������� ���� ���������� ������
                 output_c( bh );
                 crs -= bh;
                 bh = Lb( flash_begin ); // ������� ���� ���������� ������
                 output_c( bh );
                 crs -= bh;
                 bh = Hb( flash_end ); // ������� ���� �������� ������
                 output_c( bh );
                 crs -= bh;
                 bh = Lb( flash_end ); // ������� ���� �������� ������
                 output_c( bh );
                 crs -= bh;
                 output_c( crs ); // ����������� �����
                 Label++;
                 m_time = Timer1_fSec; //������ �����
             }
             break;
      case m1:
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 if( bh == crs )
                 {
                     m_time = Timer1_fSec; // ������ �����
                     Label++;
                 }
                 else
                 {
                     output_c( ~crs );
                     goto end;
                 }
             }
             break;
      case m2:
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 if( bh == Return )  // ����� �� ����� ������
                 {
end:
                     Pult_Prog_Addr = _MainPultProg;
                     M_FirstCall = 1;
                     return;
                 }
                 else if( bh == 'W' ) // ������ i2c
                 {
                     output_c( 'W' );
                     count = 0;
                     Label = wr0;
                 }
                 else if( bh == 'R' ) // ������ i2c
                 {
                     output_c( 'R' );
                     m_addr = flash_begin;
                     crs = 0;
                     Label = rd0;
                 }
                 else if( bh == 'C' ) // �������� i2c
                 {
                     output_c( 'C' );
                     for( CountByte = 0; CountByte < sizeof( m_buff ); CountByte++ ) m_buff[ CountByte ] = 0;
                     m_addr = flash_begin;
                     CountByte = 0;
                     crs = 0;
                     Label = cl0;
                 }
                 else goto end;
             }
             break;

      // ������ ����� � i2c
      case wr0:
             // ���� �� 0.5� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // ������ �����
                 if( count < 2 ) // ��������� 2-� ���� ������� �����
                 {
                     SizeFile.b[ count ] = bh;
                     crs -= bh;
                     count++;
                 }
                 else
                 {
                     if( bh == crs ) // �������� ����������� ����� �����
                     {
                         output_c( crs );
                         m_time = Timer1_fSec; // ������ �����
                         Label++;
                     }
                     else
                     {
                         output_c( ~crs );
                         goto end;
                     }
                 }
             }
             break;
      case wr1:
             if( Mon.i2c_busy == 1 ) break; // ����, ���� ����������� ����
             Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������
             m_addr = flash_begin;
             Label++;
      case wr2:
             ax = xSave_into_i2c( 2, (b*)&SizeFile.all, m_addr, flash_address ); // ������ 2-� ���� ������� �����
             if( ax == 4 ) break;  // ���� = 4 - ������������ ������
             Mon.i2c_busy = 0;  // ������������� �������, ��� ������ ���� ��������.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoWrite_i2c );
                 output_c( ~crs );
                 goto end;
             }
             else
             {
                 m_addr += 2;
                 Label++;
                 CountByte = 0;
                 count = 0;
                 m_time = Timer1_fSec; // ������ �����
                 output_c( crs );
             }
             break;
      case wr3:
             //���� �� 0.5� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input ( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // ������ �����
                 if( count < size && CountByte < SizeFile.all ) // ��������� ��������� �����
                 {
                     m_buff[ count ] = bh;
                     crs -= bh;
                     count++;
                     CountByte++;
                 }
                 else
                 {
                     if( bh == crs ) // �������� ����������� ����� �����
                     {
                         output_c( crs );
                         Label++;
                     }
                     else
                     {
                         output_c( ~crs );
                         goto end;
                     }
                 }
             }
             break;
      case wr4:
             if( Mon.i2c_busy == 1 ) break; // ����, ���� ����������� ����
             Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������
             Label++;
      case wr5:
             ax = xSave_into_i2c( count, (b*)&m_buff, m_addr, flash_address );
             if( ax == 4 ) break;  // ���� = 4 - ������������ ������
             Mon.i2c_busy = 0;  // ������������� �������, ��� ������ ���� ��������.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoWrite_i2c );
                 output_c( ~crs );
                 goto end;
             }
             else
             {
                 output_c( crs );
                 m_addr += count;
                 if( CountByte < SizeFile.all ) // ��� �� ����� ��������?
                 {
                     m_time = Timer1_fSec; // ������ �����
                     Label -= 2;
                     count = 0;
                 }
                 else goto end;
             }
             break;

      // ������ ����� �� i2c
      case rd0:
             if( Mon.i2c_busy == 1 ) break; // ����, ���� ����������� ����
             Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������
             Label++;
      case rd1:
             ax = xLoad_from_i2c( 2, m_addr, (b*)&SizeFile.all, flash_address ); // ��������� ������ �����
             if( ax == 4 ) break;  // ���� = 4 - ������������ ������
             Mon.i2c_busy = 0;  // ������������� �������, ��� ������ ���� ��������.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoRead_i2c );
                 SizeFile.all = 0;
             }
             bh = Hb( SizeFile.all ); // ������� ���� ������� �����
             output_c( bh );
             crs -= bh;
             bh = Lb( SizeFile.all ); // ������� ���� ������� �����
             output_c( bh );
             crs -= bh;
             if( (w)SizeFile.all > (w)( flash_end - flash_begin ) || SizeFile.all == 0 ) // ������ ����� ������������ ��� ������ ������
             {
                 output_c( ~crs );
                 goto end;
             }
             output_c( crs );
             m_addr += 2;
             Label++;
             break;
      case rd2:
             // ���� �� 0.5� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // ������ �����
                 if( bh == crs ) // �������� ����������� ����� �����
                 {
                     CountByte = 0;
                     Label++;
                 }
                 else
                 {
                     output_c( ~crs );
                     goto end;
                 }
             }
             break;
      case rd3:
             if( Mon.i2c_busy == 1 ) break; // ����, ���� ����������� ����
             Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������
             Label++;
      case rd4:
             ax = xLoad_from_i2c( size, m_addr, (b*)&m_buff, flash_address ); // ��������� ����������� ���
             if( ax == 4 ) break;  // ���� = 4 - ������������ ������
             Mon.i2c_busy = 0;  // ������������� �������, ��� ������ ���� ��������.
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoRead_i2c );
             }
             else
             {
                 for( count = 0; count < size && CountByte < SizeFile.all; count++, CountByte++ )
                 {
                     if( CountByte < 8 && m_buff[ count ] != CtrlCode[ count ] ) // �������� ������������ ����
                     {
                         ax = 1;
                     }
                     output_c( m_buff[ count ] );
                     crs -= m_buff[ count ];
                 }
                 if( ax == 1 )
                 {
                     output_c( ~crs );
                     goto end;
                 }
                 else output_c( crs );
                 m_addr += size;
                 Label++;
             }
             break;
      case rd5:
             // ���� �� 0.5� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 m_time = Timer1_fSec; // ������ �����
                 if( bh == crs ) // �������� ����������� ����� �����
                 {
                     if( CountByte < SizeFile.all ) Label -= 2;
                     else goto end;
                 }
                 else
                 {
                     output_c( ~crs );
                     goto end;
                 }
             }
             break;

      // �������
      case cl0:
             SizeFile.all = flash_end - m_addr + 1;  // ��������� ������� ���� �������� �� ��������� ������
             if( SizeFile.all > size ) count = size;
             else                      count = (b)SizeFile.all;
             Label++;
      case cl1:
             if( Mon.i2c_busy == 1 ) break; // ����, ���� ����������� ����
             Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������
             Label++;
      case cl2:
             ax = xSave_into_i2c( count, (b*)&m_buff, m_addr, flash_address );
             if( ax == 4 ) break;  // ���� = 4 - ������������ ������
             Mon.i2c_busy = 0;  // ������������� �������, ��� ������ ���� ��������.
             CountByte += count;
             m_addr += count;
             bh = Hb( CountByte ); // ������� ���� �������� ������� ����
             output_c( bh );
             crs -= bh;
             bh = Lb( CountByte ); // ������� ���� �������� ������� ����
             output_c( bh );
             crs -= bh;
             if( ax == 1 )
             {
                 mSet_ServiceMsg( _Srv_NoWrite_i2c );
                 output_c( ~crs );
                 goto end;
             }
             else
             {
                 output_c( crs );
                 m_time = Timer1_fSec; // ������ �����
                 Label++;
             }
             break;
      case cl3:
             //���� �� 0.5� ������ �� ��������� � ������� �����
             if( (u)((w)( Timer1_fSec - m_time )) > _WAIT ) goto end;
             if( TestData_for_Input( ) != 0 )
             {
                 mInput_c( bh );
                 if( bh == crs ) // �������� ����������� �����
                 {
                     // ��� �� ����� �������?
                     if( m_addr < flash_end )
                     {
                         Label -= 3;
                     }
                     else goto end;
                 }
                 else goto end;
             }
             break;
  }
  Restart_Output( );
  return;
}
