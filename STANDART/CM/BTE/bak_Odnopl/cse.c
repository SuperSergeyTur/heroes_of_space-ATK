#ifndef _S500

 #ifndef _BTE_NEW

  void  Set_cs_sio (byte numb)
  {
    _Clr_CS(CS_IO[numb]);
    return ;
  }

  void  Clr_cs_sio (byte numb)
  {
    _Set_CS(CS_IO[numb]);
    return ;
  }
 #else   //#ifndef _BTE_NEW

  // ������� ����������� ������ ������� ��� � ��� S400 �� �������� � _or.AS_CSo[ax]
  void  Set_cs_sio (byte cs_n)
  {
    register word ax;

    ax = (w)((cs_n + 1) % 3);

      // ������� ������
    if ( ax == 0 )
     {
      ax = (w)((cs_n + 1) / 3) ;
        // ���� ��������� ���� �� �������� � ����� _SOut_max
      if ( ax > _SOut_max  )
       {
        Clr_num_port() ;
        return ;
       }
        // � ��� ������. �������� ����� ������������ ���������� ��������� �� ���� ����������� 3 � 4.
        // �������������� ��� AS_CSo[_SOut_max] = 2 ������ ���������� ��� = 3, ��� AS_CSo[_SOut_max] = 5 ������ ���������� ��� = 4
      switch ( ax )
       {
          default:
          case 0 :
              break;

          case 1 :
              Set_num_port( 0x03 ) ;
              break;

          case 2 :
              Set_num_port( 0x04 ) ;
              break;
       }
     }
      // ����� ����
    else
     {
      ax = (w)((cs_n + 2) / 2) ;    // ������� ���� ����� ���� ( Pi(x), Pi(x+1) ), ��� x ������. ����. �� x=0, � ����� x +=2
        // ���� ��������� ���� �� �������� � ����� _SInp_max
      if ( ax >= _SInp_max  )
       {
        Clr_num_port() ;
        return ;
       }

        // � ��� ������. ������� ����� ������������ ���������� ��������� �� ���� ����������� 0 ... 3.
        // �������������� ��� AS_CSi[_SInp_max] = 0 ������ ���������� ��� = 0
        //                ��� AS_CSi[_SInp_max] = 1 ������ ���������� ��� = 1
        //                ��� AS_CSi[_SInp_max] = 3 ������ ���������� ��� = 2
      ax = (w)(( (cs_n % 3) + ((cs_n / 3) * 2)) % 3) ; //  ( ... ) % 3 ������ �� ������ ���� ������� ������� do (���� _SInp_max > 3)

      Set_num_port( ax ) ;
     }

    return ;
  }


  void  Clr_cs_sio (byte numb)
  {
    numb = 0;
    Clr_num_port();
    return ;
  }





 #endif //#ifndef _BTE_NEW

  //------------------------------------------------------------------------------------------------
  // ������� �� S500 �������������� ��������� �������:
  // 1. ������ ��� ���� CS_IO[0], CS_IO[1]  - ����� ��������/��������� �����, ����.= 0 � 1 ��� ������� �������� ����, 2 ������ ��������� �����
  // 2. ��������� ���� CS_IO[2], CS_IO[3], CS_IO[4] ��� ����� ������ ����
  // 3. ������� CS_IO[0], CS_IO[1] �����
  // 4. ������� CS_IO[2], CS_IO[3], CS_IO[4] ��������

#else //#ifndef _S500
  //------------------------------------------------------------------------------------------------

  void  Set_cs_sio (byte numb)
  {
    byte bh;
    word ax;


    bh = numb/3;


    switch ( bh )
    {
      default:
      case 0:
              break;
      case 1:
              _Clr_CS(CS_IO[2]);
              _Set_CS(CS_IO[3]);
              _Set_CS(CS_IO[4]);
              break;
      case 2:
              _Set_CS(CS_IO[2]);
              _Clr_CS(CS_IO[3]);
              _Set_CS(CS_IO[4]);
              break;
      case 3:
              _Clr_CS(CS_IO[2]);
              _Clr_CS(CS_IO[3]);
              _Set_CS(CS_IO[4]);
              break;
      case 4:
              _Set_CS(CS_IO[2]);
              _Set_CS(CS_IO[3]);
              _Clr_CS(CS_IO[4]);
              break;
      case 5:
              _Clr_CS(CS_IO[2]);
              _Set_CS(CS_IO[3]);
              _Clr_CS(CS_IO[4]);
              break;
      case 6:
              _Set_CS(CS_IO[2]);
              _Clr_CS(CS_IO[3]);
              _Clr_CS(CS_IO[4]);
              break;
      case 7:
              _Clr_CS(CS_IO[2]);
              _Clr_CS(CS_IO[3]);
              _Clr_CS(CS_IO[4]);
              break;
    }
    ax = timer1;
    word bx = 0;
    while (bx < _MkSec(2))
    {
      bx = timer1 -ax;
    }


    bh = (numb%3)+1;
    Set_num_port(bh);
    return ;
  }

  void  Clr_cs_sio (byte numb)
  {
    numb = 0;
    Clr_num_port();
    _Set_CS(CS_IO[2]);
    _Set_CS(CS_IO[3]);
    _Set_CS(CS_IO[4]);
    return ;
  }

#endif //#ifndef _S500


