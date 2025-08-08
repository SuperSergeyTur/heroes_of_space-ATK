//��������� ��� ������ �����(������, ��� �������) �� ������ � i2c. �������� � �������� �����
//�������� � ���������� � ������� ���������� Write_dat_i2c. ���� ��� �� ����� 0 - ��������� ��������

void RW_i2c_data (word code)
{
    register byte    bh;

      //   ������� �������, ����� ������ ����� ����� � ����� ���
      //  ��������������� �� ������������.
enum { i0, i2, i3 };
      //-----------
        //��� ��������� �������������.
    if ( code == 0 )
    {
      Write_dat_i2c = 0;
      label_dat = 0;
      return ;
    }
      //-----------

    if ((Write_dat_i2c & ~_Error_Wr_ust) == 0 ) return ;// ������� �� ������ ���.
      //-----------

    switch (  label_dat )
    {
      case i0:        //  ������� ������������� ������ ������� �� ��������� ������������ �������.
                  if ( Mon.i2c_busy == 1 ) break; //  ���� ���� ����������� ����.
                  asm_di() ; //�� ������ ������, ���� ����� ������ � i2c � �����������

                  Mon.i2c_busy = 1 ;  // ������������� �������, ��� ������ ���� ������.

                  asm_ei() ;

                  i2c_label = 0;
                  if (i2c_str->code == 1) label_dat = i2 ;
                  else  label_dat = i3 ;
                  break;
      case i2:
                  bh = xSave_into_i2c ( i2c_str->size , i2c_str->addr_mem,i2c_str->addr_i2c,i2c_str->chip_addr ) ;
        read:
                  if ( bh == 4 ) break;  // ���� = 4 - ���������� ������.
                  if ( bh == 1 )
                  {
                    Write_dat_i2c |= _Error_Wr_ust ;
                  }
                  else Write_dat_i2c = 0 ; // ���������� ������������ ������� �� ������.

                  Mon.i2c_busy = 0 ;  // ������������� �������, ��� ������ ���� ��������.
                  label_dat = 0 ;

                  break ;
      case i3:
               bh = xLoad_from_i2c ( i2c_str->size  , i2c_str->addr_i2c , i2c_str->addr_mem ,i2c_str->chip_addr) ;
               goto read;
    }

  return ;
}
