//  ������� ����������� ����� ����� ��� �������� 'n' ������� � ������
// 'from'.
//  ����������� ����� ������������ � ��������� ���� ��������� ����� -
// ���� ���� ������ ���� �������������� ��� ���������� �����.

word Chek_sum ( word n , byte *from )
{
  _register lword ax , bx ;

  word cx ;

  ax = (lw)from, bx = 0 , cx = 0 ;
  while ( ax < ( (lw)from + n - 1 ) )
    {
      bx -= *(b*)ax ;  // ������� ����������� ����� ��
      ax++;           // ���� ������� ����� ���������� �����.
    }
  if ( *(b*)ax != (b)bx )  cx = 1 ;

  *(b*)ax = bx ;  // ������ � ��������� ���� ������� �������

   return cx ;
}


void init_i2c(void)
{
  // Config Pin for I2C_SDA and I2C_SCL of I2C0

  PINSEL_ConfigPin (0, 27, 1);
  PINSEL_ConfigPin (0, 28, 1);

  I2C_Init(_I2c_dev, 100000);

  /* Enable I2C1 operation */
  I2C_Cmd(_I2c_dev, ENABLE);
  //  i2cData.sl_addr7bit =  _Adr_AT24C16 >> 1;
  //  i2cData.tx_data = &i2c_tx_buff;
  //  i2cData.tx_length = 1;
  //  i2cData.rx_data = &i2c_rx_buff;
  //  i2cData.rx_length = 1;
  //  i2cData.retransmissions_max = 3;

  return;

}

//������ ����������� ������� ������-������, �� ������� EEPROM
word  xSave_into_i2c ( word n ,byte *from ,  word into , byte c_addr)
{
  register word dx, ax, cx ;
  byte buff[10];
  static I2C_M_SETUP_Type  i2cData;

  enum { i0, i1, i2, i3,i4 } ;
  dx = 4;
  switch ( i2c_label )
  {
  default: i2c_label = 0 ;

  case i0 :
    from_i2c = from , into_i2c = into ;

    ax = (into_i2c+ _Page_i2c);
    cx = ax%_Page_i2c;
    i2c_Pi = ax - cx;
    ax_i2c = 0;
    i2cData.sl_addr7bit = c_addr >> 1;
    i2cData.tx_data = buff;
    i2cData.rx_data = NULL;
    i2cData.rx_length = 0;
    // 01.08.2024. ���� 0 ��������. �� ������ ������ �� �������� � "xLoad_from_i2c", ���� ��� ������ ���� ������� �� ����.
    i2cData.retransmissions_max = 3;
    i2c_label = i1 ;
  case i1 :
#ifdef _Adr_Clock_i2c
    if ( c_addr == _Adr_M41T56 )
    {
      buff[0] = (b)into_i2c;
      cx = 1;
      i2cData.tx_length = 1;
    }
    else
#endif
    {
      buff[0] = (b)(into_i2c>>8);
      buff[1] = (b)into_i2c;
      cx = 2;
      i2cData.tx_length = 2;
    }

    for (ax = cx; ax < (8+cx); ++ax)
    {
      buff[ax] = (b)*from_i2c;
      ++from_i2c;
      if ( ++ax_i2c == n )
      {
        ++ax;
        break;
      }
      else if ( ++into_i2c == i2c_Pi )
      {
        i2c_Pi += _Page_i2c ;
        ++ax;
        break;
      }

    }

      i2cData.tx_length = ax;
      if (I2C_MasterTransferData(_I2c_dev, &i2cData, I2C_TRANSFER_POLLING) != SUCCESS)
      {
        dx = 1;
      }
      i2c_label = i2 ;
      time_i2c = timer1;

    break;
    case i2:
      if ((u)((w)(timer1 -time_i2c )) >= _MkSec(4000))
      {
        if ( ax_i2c == n )
        {
          dx = 0;
          break;
        }
        i2c_label = i1 ;
      }
      break;


  }

  if ( dx != 4 )
  {
    i2c_label = 0 ;
  }

  return dx ;   //  ��� ����������� ������.
}



word  xLoad_from_i2c ( word n , word from , byte *into , byte c_addr)
{
  register word  dx, cx ;
  word ax;
  word __into_i2c;
  byte buff[8];
  static I2C_M_SETUP_Type  i2cData;
  dx = 4;

  enum { i0, i1, i2, i3, i4, i5, i6,i7} ;

  switch ( i2c_label )
  {
  default: i2c_label = 0 ;
  case i0 :
    ax_i2c = 0 ;
    from_i2c = into ;
    into_i2c = from ;
    __into_i2c = from ;
    i2cData.sl_addr7bit = c_addr >> 1;
    i2cData.tx_data = buff;
    i2cData.rx_data = buff;
    i2cData.rx_length = 0;
    // 01.08.2024. ���� 0 ��������. ��� ����� i2c � ���� ������ �� ������ .050 (����� - 2 �� 10) � .051 (���� - 1 �� 11)
    // ���������� ��������� "���� �i��.����.", � ����� ���������� ����� ��� ������ ���� ���������� "CodeReadWriter".
    // ������ ���������� � ������� "I2C_MasterTransferData" � ���� ��������� ��������� �����-������� "Second Start condition (Repeat Start)".
    // ���������� ���������� ���������� �������� ".retransmissions_max".
    i2cData.retransmissions_max = 3;
    i2c_label = i1 ;

  case i1 :
    if (ax_i2c  >= n)
    {
      dx = 0;
    }
    else
    {
#ifdef _Adr_Clock_i2c
      if ( c_addr == _Adr_M41T56 )
      {
        buff[0] = (b)into_i2c;
        //������� ������
        i2cData.tx_length = 1;
      }
      else
#endif
      {
        buff[0] = (b)(into_i2c>>8);
        buff[1] = (b)into_i2c;
        //������� ������
        i2cData.tx_length = 2;
      }
        ax = n - ax_i2c;
        if (ax < 8)
        {
          cx = ax;
        }
        else
        {
          cx = 8;
        }

        i2cData.rx_length = cx;
      if (I2C_MasterTransferData(_I2c_dev, &i2cData, I2C_TRANSFER_POLLING) != SUCCESS)
      {
          dx = 1;
      }
      else
      {
        //����� ������
//        i2cData.tx_length = 0;
//        if (I2C_MasterTransferData(_I2c_dev, &i2cData, I2C_TRANSFER_POLLING) != SUCCESS)
//        {
//          dx = 1;
//        }
//        else
//        {
          for (ax = 0; ax < cx; ++ax)
          {
            *from_i2c = buff[ax];
            ++from_i2c;
            ++ax_i2c;
            ++into_i2c;
          }
       // }
      }


    }
    break;
  }


  if ( dx != 4 )
  {
    i2c_label = 0 ;
  }

  return dx ;   //  ��� ����������� ������.


}

//    �������-���������� ��� ������������� xSave_into_i2c �
//  Save_into_i2c ��� ����� ���������� ��������.

word  Save_into_i2c ( word n , byte *from , word into, byte c_addr )
{
  register word ax ;

  i2c_label = 0 ;
  do
  {
    ax = xSave_into_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );

  return ax ;
}


//    �������-���������� ��� ������������� xLoad_from_i2c �
//  Load_from_i2c ��� ����� ���������� ��������.

word  Load_from_i2c ( word n , word from , byte *into, byte c_addr )
{
  register word ax ;

  i2c_label = 0 ;
  do
  {
    ax = xLoad_from_i2c ( n , from , into, c_addr ) ;
    if ( ax == 1 )   break;
  } while ( ax == 4 );

  return ax ;
}
