
void Journal ( byte num )
{
  register byte ax, bx, cx, dx;
  register word PlusGist, MinusGist;
  _x_far const struct VAR_JRN register *ptr;
  static byte index;

  // �������������
  if ( num == 0 )
  {
    for ( ax = 0; ax < _MaxNumVarJrn; ax++ ) JrnData.flag[ ax ] = 0;
    JrnData.time = Timer1_fSec;
    JrnData.label = 0; // ����� ��� ��������� TestJrnTab()
    InJrnPtr = 1; // ��������� �� ������ ������
    OutJrnPtr = 0;
    BitJrn.all = 0;
    JrnData.Stop = 0;
    JrnData.activ = 0;
    i2c_jrn_label = 0;
    index = 0;

    // �������� ����� �������
    for ( ax = 0; ax < _MaxJrnCount; ax++ )
    {
       //MsgJrn[ ax ].number = 0;
       for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ ax ].name[ bx ] = 0;
       MsgJrn[ ax ].uslovie = 0;
       MsgJrn[ ax ].value = 0;
       MsgJrn[ ax ].time_msg._.avar_first.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.avar.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.predupr.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.service.lw_reg = 0;
#ifndef _ONE_REG
       MsgJrn[ ax ].time_msg._.avar_first2.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.avar2.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.predupr2.lw_reg = 0;
       MsgJrn[ ax ].time_msg._.service2.lw_reg = 0;
#endif
       for ( bx = 0; bx < 8; bx++ ) MsgJrn[ ax ].time_msg.time.b[ bx ] = 0;
    }

      // ������� ������������ ������ �� ������� ������� ����
      // � const-������� � ��������� �� ������ ����� (�����),
      // ��������� ��� ����������� ����� (�����) ���������� ��� ����������
      // ��-��������� � ���������� ������� (�������) ������ ����������, ���������� � i2c.
    while ( TestJrnTab ( 0 ) != 0 );

    //��������� ����� ������� ���������
    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = _TimeStartProg[ bx ];
    MsgJrn[ InJrnPtr ].uslovie = -2; // ������������� �������, ��� ������ � ������� ����������� �� ������� ���������
    MsgJrn[ InJrnPtr ].value = 0;
    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode; // ������ ������������ ����
    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;

    // ��� ���������� ���������� ������������� ���� � ����������� �� ��������� �����.�����,
    // ����� ��� ����� � ������� ���� ����� �� ��������� ���������� �����������.
    for ( ax = 0; ax < TabJrn.n_kanal; ax++ )  // ���������� ��� �������� ����������
    {
      // ��� ���������� ������������ ������� ���������� ���������� ��������� ����� ���������� � �������
      ptr = &FullJrnTab[ JrnData.tab[ ax ] ];

      if ( ptr->code._.ad == 1 ) // ���������� ����������
      {
        switch ( ptr->code._.type )
        {
          default:
                    break;
          case 1:   // �����������
                    // ���� �������� ��� � ����� ����� 0
                    if ( ( *(b*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ ax ].etalon ) ) == 0 ) JrnData.flag[ ax ] = 1;
                    break;

          case 2:   // �����������
                    // ���� �������� ��� � ����� ����� 0
                    if ( ( *(w*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ ax ].etalon ) ) == 0 ) JrnData.flag[ ax ] = 1;
                    break;
        }
      }
    }

    return;
  }

  // ��������� ������� ������ �������.
  // ��� 16-�� ���������� FR - 0.2...0.5ms
  //                      590 - 0.6...1.4ms
  Tckl_jrn = timer1 ;

  // �������� �� ������ �������, ���� �� �� �����������, ��� ��� ��� �������� ������� ��� ������� ��� �������������,
  // ������� � ���������� �������������.
  if ( BitJrn._.first == 0 )
  {
    if ( (u)( (w)( Timer1_fSec - JrnData.time ) ) <= _fSec( 3.0 ) ) return;
    JrnData.time = Timer1_fSec;
    BitJrn._.first = 1;
  }

  // ���� ������ ������� - ��������� ����� ������� � i2c
  if ( JrnData.activ == 1 ) Save_jrn ();

  // ���� ������� �� ��������� �������
  if ( bi_JrnStop == 1 )
  {
    if ( JrnData.activ == 1 )
    {
      // �������� - ���� �� ��� ���-�� � ������ ��� ������ � i2c?
      // ���� �� ������ �� ������� - ������������� ������ � i2c.
      if ( ( ( OutJrnPtr + 1 ) & _MaxJrnCount ) == InJrnPtr  ) JrnData.activ = 0;
    }
    Tjrn = 0;
    return; // ���� ������� �� ��������� ������� - �������, ����� � ������ �� ������������� ����� ������.
  }
  else JrnData.activ = 1;

  // ���� �� � ������ ����� ��� ����� ������
  if ( ( ( InJrnPtr + 1 ) & _MaxJrnCount ) == OutJrnPtr ) return; // ����� ��������, ������ � i2c �� ��������
                                                                  // �� ������ �������

  // �������� ��������� ��������� ������ ����
  if ( BitJrn._.tst_new_msg == 1 ) // �������� �������� ��������� ���������� ���������
  {
    BitJrn._.tst_new_msg = 0; // ����� ��������
    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = _JrnMsg[ bx ];  // ���������� ��� ���������� �� ����� �������
    MsgJrn[ InJrnPtr ].uslovie = -1; // ������������� �������, ��� ������ � ������� ����������� �� ��������� ���������� ���������
    MsgJrn[ InJrnPtr ].value = 0;
    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode; // ������ ������������ ����
    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;
  }

  // ������� ���� ������� �������������� ��� � "TabJrn.dt_scan" ���.
  if ( (u)( (w)( Timer1_fSec - JrnData.time ) ) < TabJrn.dt_scan ) return; // ����� ��� �� �����
  JrnData.time = Timer1_fSec; // ����� �������� �����


  //---------------- ������� ���� ------------------------------------------

  // �� 1 ������ ������������� ������� ����������, ������� ����� ����������� � ������
  dx = _MaxJrnCount;
  if( (sb)dx > (sb)TabJrn.n_kanal ) dx = TabJrn.n_kanal;

  for ( ax = dx; ax != 0; ax-- )  // ���������� ��� �������� ����������
  {
    // ���� �� � ������ ����� ��� ����� ������
    if ( ( ( InJrnPtr + 1 ) & _MaxJrnCount ) == OutJrnPtr ) return; // ����� ��������, ������ � i2c �� ��������
                                                                    // �� ������ �������

    if( TabJrn.TabVar[ index ].name[ 0 ] == '?' ) goto next; // ����� ���������� � ����� ������� ���

    // ��� ���������� ������������ ������� ���������� ���������� ��������� ����� ���������� � �������
    ptr = &FullJrnTab[ JrnData.tab[ index ] ];

    if ( ptr->code._.ad == 1 ) // ���������� ����������
    {
      // ��� ���������� ���������� ����� ��� ��������� �������� ����� � ��������� � �����
      switch ( ptr->code._.type )
      {
        default:
                  break;
        case 1:   // �����������
                  // ���� �������� ��� � ����� ���� ������ 0
                  if ( ( *(b*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) == 0 && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1; // ��������� �����
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx ] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _RVN;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // ���������� ����� ����
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  // ���� �������� ��� � ����� ���� ������ 1
                  else if ( ( *(b*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) != 0 && JrnData.flag[ index ] != 0 )
                  {
                    JrnData.flag[ index ] = 0; // ����� �����
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _NRV;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // ���������� ����� ����
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  break;

        case 2:   // �����������
                  // ���� �������� ��� � ����� ���� ������ 0
                  if ( ( *(w*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) == 0 && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1; // ��������� �����
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _RVN;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // ���������� ����� ����
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  // ���� �������� ��� � ����� ���� ������ 1
                  else if ( ( *(w*)ptr->addr & ( 1 << (b)TabJrn.TabVar[ index ].etalon ) ) != 0 && JrnData.flag[ index ] != 0 )
                  {
                    JrnData.flag[ index ] = 0; // ����� �����
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _NRV;
                    MsgJrn[ InJrnPtr ].value = TabJrn.TabVar[ index ].etalon; // ���������� ����� ����
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  break;
      }
    }
    else if ( ptr->code._.ad == 0 ) // ���������� ����������
    {
      // ����� ��������� ������ � ������ �����������
      PlusGist  = TabJrn.TabVar[ index ].etalon + ptr->nom * _Gisterezis / 100;
      MinusGist = TabJrn.TabVar[ index ].etalon - ptr->nom * _Gisterezis / 100;

      switch ( TabJrn.TabVar[ index ].uslovie )
      {
        default:
                  break;
        case _RVN: // ==
                  if ( ptr->code._.off_sign == 0 ) // ���������� �����������
                  {
                    if ( *(sw*)ptr->addr == (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _RVN;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    // ����� �� ����� ����������? - ����� �����������, ����� ����� �������� ���� ������� ����� �������
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist || *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // ���������� ������������
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //���� ���������� ������������ - �� ������������� ����� �� ����� ������
                    if ( *(w*)ptr->addr == (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _RVN;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(w*)ptr->addr >= (w)PlusGist || *(w*)ptr->addr <= (w)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _NRV: // !=
                  if ( ptr->code._.off_sign == 0 ) // ���������� �����������
                  {
                    if ( *(sw*)ptr->addr != (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _NRV;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist || *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // ���������� ������������
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //���� ���������� ������������ - �� ������������� ����� �� ����� ������
                    if ( *(w*)ptr->addr != (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _NRV;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist || *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _BRV: // >=
                  if ( ptr->code._.off_sign == 0 ) // ���������� �����������
                  {
                    if ( *(sw*)ptr->addr >= (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BRV;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // ���������� ������������
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //���� ���������� ������������ - �� ������������� ����� �� ����� ������
                    if ( *(w*)ptr->addr >= (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BRV;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(w*)ptr->addr <= (w)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _BOL: // >
                  if ( ptr->code._.off_sign == 0 ) // ���������� �����������
                  {
                    if ( *(sw*)ptr->addr > (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BOL;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(sw*)ptr->addr <= (sw)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // ���������� ������������
                  {
                    if ( (sw)MinusGist < 0 ) MinusGist = 0; //���� ���������� ������������ - �� ������������� ����� �� ����� ������
                    if ( *(w*)ptr->addr > (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _BOL;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(w*)ptr->addr <= (w)MinusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _MRV: // <=
                  if ( ptr->code._.off_sign == 0 ) // ���������� �����������
                  {
                    if ( *(sw*)ptr->addr <= (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MRV;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // ���������� ������������
                  {
                    if ( *(w*)ptr->addr <= (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MRV;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(w*)ptr->addr >= (w)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;

        case _MEN: // <
                  if ( ptr->code._.off_sign == 0 ) // ���������� �����������
                  {
                    if ( *(sw*)ptr->addr < (sw)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MEN;
                      MsgJrn[ InJrnPtr ].value = *(sw*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(sw*)ptr->addr >= (sw)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  else // ���������� ������������
                  {
                    if ( *(w*)ptr->addr < (w)TabJrn.TabVar[ index ].etalon && JrnData.flag[ index ] == 0 )
                    {
                      JrnData.flag[ index ] = 1;
                      // ���������� ��� ���������� �� ����� �������
                      for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                      MsgJrn[ InJrnPtr ].uslovie = _MEN;
                      MsgJrn[ InJrnPtr ].value = *(w*)ptr->addr;
                      MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                      // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                      *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                      MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                      InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                    }
                    else if ( *(w*)ptr->addr >= (w)PlusGist ) JrnData.flag[ index ] = 0;
                  }
                  break;
      }
    }
    else if ( ptr->code._.ad == 2 ) // ���������� ����������, �������������� �������� ������
    {
      if ( ptr->code._.type == 1 ) bx =  7; // ����
      else                         bx = 15; // �����

      for ( cx = 0; cx <= bx; cx++) //����� ������ �������� ������� � �����, ��������� � cx
         if ( ( ptr->nom >> cx ) & 1 != 0 ) break;

      MinusGist = TabJrn.TabVar[ index ].etalon << cx; // ������ �������� � �����

      // ����
      if ( ptr->code._.type == 1 ) PlusGist = (w)( *(b*)ptr->addr & ptr->nom ) & 0x00FF;
      // �����
      else PlusGist = *(w*)ptr->addr & ptr->nom;

      switch ( TabJrn.TabVar[ index ].uslovie )
      {
        default:
                  break;

        case _RVN: // ==
                  if ( PlusGist == MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _RVN;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  else if ( PlusGist != MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _NRV: // !=
                  if ( PlusGist != MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _NRV;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  else if ( PlusGist == MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _BRV: // >=
                  if ( PlusGist >= MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _BRV;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  else if ( PlusGist < MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _BOL: // >
                  if ( PlusGist > MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _BOL;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  else if ( PlusGist <= MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _MRV: // <=
                  if ( PlusGist <= MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _MRV;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  else if ( PlusGist > MinusGist ) JrnData.flag[ index ] = 0;
                  break;

        case _MEN: // <
                  if ( PlusGist < MinusGist && JrnData.flag[ index ] == 0 )
                  {
                    JrnData.flag[ index ] = 1;
                    // ���������� ��� ���������� �� ����� �������
                    for ( bx = 0; bx < _VarNameSize; bx++ ) MsgJrn[ InJrnPtr ].name[ bx] = ptr->name[ bx ];
                    MsgJrn[ InJrnPtr ].uslovie = _MEN;
                    MsgJrn[ InJrnPtr ].value = PlusGist >> cx;
                    MsgJrn[ InJrnPtr ].time_msg.time = c_time;          // �������� ����� �������
                    // �.�. ��� � 'Control Byte' �� ������������ - ����� ���� ����������� ���
                    *(w*)&MsgJrn[ InJrnPtr ].time_msg.time.b[ 6 ] = _CntrCode;
                    MsgJrn[ InJrnPtr ].time_msg._ = msg_reg._;    // ����� ��� �������� ���������
                    InJrnPtr = ( InJrnPtr + 1 ) & _MaxJrnCount;  // ����������� ���������
                  }
                  else if ( PlusGist >= MinusGist ) JrnData.flag[ index ] = 0;
                  break;
      }
    }
next:
    if( ++index >= TabJrn.n_kanal ) index = 0; // ����������� ��� ���������� - �������� � ������
  }
  //------------------------------------------------------------------------
  Tjrn = timer1 - Tckl_jrn; // � Tjrn ����� ������ �������

  return;
}

// m_index - ����� "����1"
// m_time  - ���������� ����� ����������
// m_ext   - ����� "����2"
// m_addr  - ����� ����� ����������

// ��������� �������
void SetJrnTab ( void )
{

  register word ax, bx, cx, ex;
  byte  sig_old;
  register lword lax;


              //  �������� ������: ������ ������ �����.

      if ( Password_control ( 2 ) == 0 )  return   ;
              //---


  if ( M_FirstCall == 1 )  // ������������� ������� ����� ��� �������
  {                        // ���������� ������� ...
    M_FirstCall = 0;
    Label = 0;
    m_index = 0;
    m_ext = 0;
    m_addr = 0;
    JrnData.Stop = 1; // ��������� �������
  }

  //--------------------

  switch ( Label )
  {
    default:
    case 0:
          output_s ( _SetJrn_prompt ); // "\n\r�����. �������: \n" �� ������� ������
          Label = 1;

    case 1:
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu1[ m_index ].txt ); //���������, ����������, ������
            Label = 2;
          }
          break ;

          //�������� � "����1": ���������, ����� ����������, ������ ����������
    case 2:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // ����� �� ����� ������
            {
              JrnData.Stop = 0; //������ �������
              Pult_Prog_Addr = _MainPultProg,  M_FirstCall = 1;
              return;   // �������� ��� �����-�� ����.
            }
            else if ( m_ch == Down ) //��������� ����� "����1"
            {
              m_index++;
              if ( m_index >= Menu1_size ) m_index = 0;
              Label = 1;
            }
            else if ( m_ch == Up )  //��������� ����� "����1"
            {
              m_index--;
              if ( (sw)m_index < 0 ) m_index = Menu1_size - 1;
              Label = 1;
            }
            else if ( m_ch == Enter ) Label = 3;
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 1;
          }
          break;

    case 3:
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" ); //������� �� ������� ������ ����� "����1"
            output_s ( Menu1[ m_index ].txt );
            output_c ( '\n' );
            Label = Menu1[ m_index ].label;
          }
          break;

    //-------------------------------------------------------------------------------
    case 10: //"���������"
          m_time = TabJrn.dt_scan; //��������� ������� ���������
          Label = 11;
    case 11: //����� ��������� �������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );

            ax = TabJrn.dt_scan;
            m_ch  = ax / _fSec(10);
            ax = ax % _fSec(10) ; // ������� �� ������� ��������� �� ��������

            if ( m_ch != 0 )  m_ch += 0x30;
            else              m_ch = ' ';

            output_c ( m_ch ); //�������

            m_ch = ax / _fSec(1);
            ax %= _fSec(1) ;

            output_c ( m_ch+0x30 ); //�������
            output_c ( '.' );

            ax *= 10;
            m_ch = ax / _fSec(1);
            ax %= _fSec(1);
            output_c ( m_ch + 0x30 ); //�������

            ax *= 10;
            m_ch = ax / _fSec(1);
            ax %= _fSec(1);
            output_c ( m_ch + 0x30 ); //�����

            ax *= 10;
            m_ch = ax / _fSec(1);
            output_c ( m_ch + 0x30 ); //��������
            output_s ( " ��� " );
            Label = 12;
          }
          break ;

    case 12: //����� ��������� ��������� �������
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // ����� �� ����� ������
            {
              TabJrn.dt_scan = m_time; // ��������������� ������� ���������
              Label = 0;
            }
            else if ( m_ch == Up )   // ��������� ���������
            {
              TabJrn.dt_scan += _fSec(0.01) ; // ����������� ���������
              if ( TabJrn.dt_scan >= _fSec(5.0) ) TabJrn.dt_scan = _fSec(5.0);
              Label = 11; // ������� �� ����� ���������
            }
            else if ( m_ch == Down ) // ��������� ���������
            {
              TabJrn.dt_scan -= _fSec(0.01); // ��������� ���������
              if ( (sw)TabJrn.dt_scan <= 0 ) TabJrn.dt_scan = _fSec(0.00);
              Label = 11; // ������� �� ����� ���������
            }
            else if ( m_ch == Enter ) Label = 0; // ��������� �������
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 11;
          }
          break;

    //-------------------------------------------------------------------------------
    case 20:  //"���������x"
          m_time = (w)TabJrn.n_kanal; //��������� ������� ���-�� ����������
          Label = 21;
    case 21:  //����� ���������� ����������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( "N = " );

            ax = (w)TabJrn.n_kanal;
            output_c ( ax / 10 + 0x30 ); //�������
            output_c ( ax % 10 + 0x30 ); //�������
            Label = 22;
          }
          break;

    case 22: //����� ��������� ���������� ����������
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )
            {
              TabJrn.n_kanal = (b)m_time; //��������������� ������� ���-�� ����������
              Label = 0;
            }
            else if ( m_ch == Up ) //��������� ���-�� ����������
            {
              TabJrn.n_kanal++;
              if ( TabJrn.n_kanal > _MaxNumVarJrn ) TabJrn.n_kanal = _MaxNumVarJrn; //25.06.2012 10:10 1;
              Label = 21;
            }
            else if ( m_ch == Down ) //��������� ���-�� ����������
            {
              TabJrn.n_kanal--;
              if ( (sb)TabJrn.n_kanal < 0/*1*/ ) TabJrn.n_kanal = 0; //25.06.2012 10:10 _MaxNumVarJrn; ��� ����������� ������
              Label = 21;                         // 0 ���������� � �������� ������ �� ���������� ���������� ���������
            }
            else if ( m_ch == Enter ) Label = 0; //������� ����� ����������
            else  Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 21;
          }
          break;

    //-------------------------------------------------------------------------------
    case 29:
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" ); //������� �� ������� ������ ����� "����1"
            output_s ( Menu1[ m_index ].txt );
            output_c ( '\n' );
            Label = 31;
          }
          break;
    case 30:  //"������    "
          if( TabJrn.n_kanal == 0 )
          {
            m_index = 1;
            output_s ( "\r" ); //������� �� ������� ������ ����� "����1"
            output_s ( Menu1[ m_index ].txt );
            output_c ( '\n' );
            Label = Menu1[ m_index ].label;
            break;
          }
          m_time = 0;
          Label = 31;
    case 31:  //�������� ��� �������� ����������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_c ( 'n' );
            //���������� ������ ����������
            ax = m_time + 1;
            output_c ( ax / 10 + 0x30 ); //�������
            output_c ( ax % 10 + 0x30 ); //�������
            output_c ( '-' );

            //���������� ������������ ����������
            output_s ( TabJrn.TabVar[ m_time ].name );
            Label = 32;
          }
          break;

    case 32:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = 0;
            else if ( m_ch == Down ) //��������� ����� ����������
            {
              m_time++;
              if ( m_time >= TabJrn.n_kanal ) m_time = 0;
              Label = 31;
            }
            else if ( m_ch == Up ) //��������� ����� ����������
            {
              m_time--;
              if ( (sw)m_time < 0 ) m_time = TabJrn.n_kanal - 1;
              Label = 31;
            }
            else if ( m_ch == Enter ) //������� � ����� ������ ����� ����������,
            {                         //������� � ������� �������
              Label = 33;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 31;
          }
          break;

    case 33:  //������� �� ������� ������ ��� ������� ����������
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            output_c ( 'n' );
            //���������� ������ ����������
            ax = m_time + 1;
            output_c ( ax / 10 + 0x30 ); //�������
            output_c ( ax % 10 + 0x30 ); //�������
            output_c ( '-' );
            //���������� ������������ ����������
            output_s ( TabJrn.TabVar[ m_time ].name );
            output_c ( '\n' );
            Label = 34;
          }
          break;

    case 34: //�������� � "����2" - ����� ����������, �������, ������/����� ����
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu2[ m_ext ].txt );
            Label = 35;
          }
          break;

    case 35:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = 29;
            else if ( m_ch == Down ) //��������� ����� ����2
            {
              m_ext++;
              //���� ������� ���������� ����������, �� ���� "�������" ����������
              if ( FullJrnTab[ JrnData.tab[ m_time ] ].code._.ad == 1 && Menu2[ m_ext ].label == 50 ) m_ext++;
              if ( m_ext >= Menu2_size ) m_ext = 0;
              Label = 34;
            }
            else if ( m_ch == Up ) //��������� ����� ����2
            {
              m_ext--;
              if ( (sw)m_ext < 0 ) m_ext = Menu2_size - 1;
              //���� ������� ���������� ����������, �� ���� "�������" ����������
              if ( FullJrnTab[ JrnData.tab[ m_time ] ].code._.ad == 1 && Menu2[ m_ext ].label == 50 )
              {
                m_ext--;
                if ( (sw)m_ext < 0 ) m_ext = Menu2_size - 1;
              }
              Label = 34;
            }
            else if ( m_ch == Enter ) Label = 36;
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 34;
          }
          break;

    case 36: //����� �� ������� ������ ���������� ������ "����2"
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            output_s ( Menu2[ m_ext ].txt );
            output_c ( '\n' );
            Label = Menu2[ m_ext ].label;
            m_addr = 0;
          }
          break;

    //-------------------------------------------------------------------------------
    case 40:  // "����� �������."
          m_addr = 0;
          Label = 41;
    case 41:  //  ����� ����� ���������� � ������ �������� ����������.
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_c ( '#' );
            //���������� ������ ����������
            ax = m_addr + 1;
            output_c ( ax / 10  + 0x30 ); //�������
            output_c ( ax % 10  + 0x30 ); //�������
            output_c ( '-' );
            //���������� ������������ ����������
            //output_s ( FullJrnTab[ m_addr ].name );
            //����� �����������, �.�. output_s �� ��������� far.
            for ( ax = 0; ax < _VarNameSize; ax++ )
                output_c ( FullJrnTab[ m_addr ].name[ ax ] );
            Label = 42;
          }
          break;

    case 42:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = 33;
            else if ( m_ch == Down ) //��������� ����� ����� ����������
            {
              m_addr++;
              if ( m_addr >= FullJrnTab_size ) m_addr = 0;
              Label = 41;
            }
            else if ( m_ch == Up ) //�������� ����� ����� ����������
            {
              m_addr--;
              if ( (sw)m_addr < 0 ) m_addr = FullJrnTab_size - 1;
              Label = 41;
            }
            else if ( m_ch == Enter ) //������� ����� ����������
            {
              if ( JrnData.tab[ m_time ] != m_addr ) //���� ������������� ����� ����������
              {
                //���������� ����� ����� ����������
                JrnData.tab[ m_time ] = m_addr;
                //���� ����� ����� ���������� �� ��������� �� ������ �������,
                //�� �������� ���� � ��� ���������� ���������� ������, �.�. ����� ��������� ������ ��������.
                //��� ���������� ���������� ������ (����� ����) ����� �������������� �� const-�������.
                //����� ��������� ���������� ���������� ���� ������ ����� ������.
                JrnData.flag[ m_time ] = 0;
                if ( FullJrnTab[ JrnData.tab[ m_time ] ].code._.ad == 1 )
                     TabJrn.TabVar[ m_time ].etalon = FullJrnTab[ JrnData.tab[ m_time ] ].nom;
                else TabJrn.TabVar[ m_time ].etalon = 0;
                // �������������� ��� ���������� � ������� �������
                for ( ax = 0; ax < _VarNameSize; ax++ ) TabJrn.TabVar[ m_time ].name[ ax ] = FullJrnTab[ m_addr ].name[ ax ];
              }
              Label = 33;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 41;
          }
          break;

    //-------------------------------------------------------------------------------
    case 50: //"�������       "
          //���������� ������� �������
          m_buff[ 2 ] = TabJrn.TabVar[ m_time ].uslovie;
          //����� �������� � �������� �������
          m_addr = TabJrn.TabVar[ m_time ].uslovie;
          Label = 51;
    case 51: //����� ������� - �������� � "����3"
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( Menu3[ m_addr ].txt );
            Label = 52;
          }
          break;

    case 52:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )
            {
              TabJrn.TabVar[ m_time ].uslovie = m_buff[ 2 ]; //��������������� �������
              Label = 33;
            }
            else if ( m_ch == Down )
            {
              m_addr++;
              if ( m_addr >= Menu3_size ) m_addr = 0;
              Label = 51;
            }
            else if ( m_ch == Up )
            {
              m_addr--;
              if ( (sw)m_addr < 0 ) m_addr = Menu3_size - 1;
              Label = 51;
            }
            else if ( m_ch == Enter )
            {
              //���������� ����� ������� � ���������� ����
              TabJrn.TabVar[ m_time ].uslovie = Menu3[ m_addr ].label;
              JrnData.flag[ m_time ] = 0;
              Label = 33;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 51;
          }
          break;

    //-------------------------------------------------------------------------------
    case 60:  //"������/���    "
          *(w*)&m_buff[ 0 ] = TabJrn.TabVar[ m_time ].etalon; //���������� �������� �������
          //��� ���������� ������������ ������� ���������� ���������� ��������� ����� ���������� � �������
          dptr = &FullJrnTab[ JrnData.tab[ m_time ] ];
          Label = 61;
    case 61: //����� �������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );

            ax = TabJrn.TabVar[ m_time ].etalon;

            // ���������� � 10-������ ����

            // ���������� ����������, �������������� �������� ������ ��� ��������� ����������
            if ( dptr->code._.ad == 2 || dptr->code._.ad == 1 ) bx = 1;
            else bx = dptr->nom;
            cx = *(w*)dptr->abs_nom;
            if ( dptr->code._.off_sign == 0 )
            {    //���� ���������� �� ������ - �������� ���� � ������
              if ( (sw)ax >= 0 )   sig_old = '+';
              else   ax = ~ax + 1, sig_old = '-';
            }

            //�������� ���������� ������ � ��� ���������
            lax = (lw)ax * (lw)cx;
            m_addr = lax % bx;
            lax /= bx;
            if ( lax > 0xffffu) lax = 0xffff;

            //���������� ����� ����� - �������� 5 ��������
            ex = 5 - dptr->code._.celoe; //������� ������ �������� ����������
            if ( ex == 5 ) ex = 2; //��� ������������� - ���� ������ ���� ���� �� ��������� ������ "3.2".
            else if ( (sw)ex < 0 ) ex = 0;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;
              //���� ���� ������ ���� - �� ������� ��:
              if ( bx == 0 && cx == 0 )
              {     //� ���������� ������ ������� �������,
                if ( ex != 0 ) ex--;
                //��� �������� ���������
                else output_c (' ');
              }
              else
              {
                if ( cx == 0 )
                {
                  if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
                  cx = 1;
                }
                //������ ���� �����������
                output_c ( (b)bx + 0x30 );
              }
            }   //������������� ��������� �����
            if ( cx == 0 )
            {
              if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
            }
            output_c ( (b)(w)lax + 0x30 );
            Label = 62;
          }
          break;

    case 62:    //���������� ������� �����
          if ( TestCompleted_Output() )
          {
            if ( dptr->code._.celoe == 0 ) ex = 2;// �� ���������.
            else ex = dptr->code._.drob;
            if ( ex != 0 )
            {
              output_c ( '.' );
              bx = dptr->nom;
              lax = m_addr; //��������������� �������
              for ( ; ex != 0 ; ex-- )
              {
                lax *= 10;
                ax = lax / bx;
                lax %= bx;
                output_c ( (b)ax + 0x30 );
              }
            }
            output_s ( dptr->ch );
            Label = 63; // ��� ������ ��������� �������
          }
          break;

    case 63: //��������� �������
          if ( TestData_for_Input() )
          {
            ax = TabJrn.TabVar[ m_time ].etalon; //���������� ������
            cx = ax; // ��������� ���������� ��������
            mInput_c ( m_ch );
            if ( m_ch == Return )
            {
              TabJrn.TabVar[ m_time ].etalon = *(w*)&m_buff[ 0 ]; //��������������� �������� �������
              Label = 33;
              break;
            }
            else if ( m_ch == Up ) //��������� ������
            {
              ax += dptr->dX;
              bx  = dptr->max;
              //  ���� ���������� ��� ����� �� ����� �������������
              //  ��� ����������� � ��������� 0...65535.
              if ( dptr->code._.off_sign == 0 ) //�� ������
              {
                //  ������ �� ������ ������������� ����� max, ����
                // max ����� 0xFFFF (��� �����������) ��� 0x7FFF
                // (��� ��������), �.�. � ���� ������� �����������
                // �� �������� ��������� �� ����� ��������.
                if ( (sw)ax < (sw)cx ) ax = bx; // ���� ����� �������� �����
                // ����� ������ ��� ��, ������ ��������� �������������.
                if ( (sw)ax > (sw)bx ) ax = bx;
              }
              else //��� �����
              {
                if ( (w)ax < (w)cx ) ax = bx; // ���� ����� �������� �����
                // ����� ������ ��� ��, ������ ��������� �������������.
                if ( (w)ax > (w)bx ) ax = bx;
              }
              Label = 61;
            }
            else if ( m_ch == Down ) //��������� ������
            {
              ax -= dptr->dX;
              bx = dptr->min;
              if ( dptr->code._.off_sign == 0 ) //�� ������
              {
                //  ������ �� ������ ������������� ����� min, ����
                // min ����� 0x0000 (��� �����������) ��� 0x8000
                // (��� ��������), �.�. � ���� ������� �����������
                // �� �������� ��������� �� ����� ��������.
                if ( (sw)ax > (sw)cx ) ax = bx; // ���� ����� ��������� �����
                // ����� ������ ��� ��, ������ ��������� �������������.
                if ( (sw)ax < (sw)bx ) ax = bx;
              }
              else //��� �����
              {
                if ( (w)ax > (w)cx ) ax = bx; // ���� ����� ��������� �����
                // ����� ������ ��� ��, ������ ��������� �������������.
                if ( (w)ax < (w)bx ) ax = bx;
              }
              Label = 61;
            }
            else if ( m_ch == Enter ) //���������� ����� ������
            {
              Label = 33;
            }
            else  Klav_Buff = m_ch;
            TabJrn.TabVar[ m_time ].etalon = ax; //���������� ������
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = 61;
          }
          break;
  }
  Restart_Output ( );
  return;
}

  //   ������� ������������ ���� ������ �� ������� ������� ����
  // � const-������� � ��������� �� ������ ��������� (�����),
  // ��������� ��� ����������� ����� ���������� ��� ����������
  // ��-��������� � ���������� ������� ������ ���������� ���������� � i2c.

word TestJrnTab ( byte num )
{
  enum { k0, k10 };

  static byte index1; //  ������ ������ ������ ������� �������.
  static byte index2; //  ������ ������ ������ const-�������.
  char *ptr1;
  _x_far const char *ptr2;
  byte ah, bh;

  if ( num == 0 )
  {
    switch ( JrnData.label )
    {
      default:;     // ������ ������.
      case k0 : index1 = 0, index2 = 0 ;
                JrnData.label = k10 ;
         break;
          //-----------------
      case k10:      // ���������� �������� �� ����� 3-� ����������.
                for ( ah = 3 ; ah != 0 ; ah-- )
                {     //  ���� ����� ������ �����, �� ����������.
                  //if ( JrnData.tab[index1].name[0] == '@' ) goto next ;

                  ptr1 = &TabJrn.TabVar[ index1 ].name[ 0 ];
                  ptr2 = &FullJrnTab[ index2 ].name[ 0 ];
                       //  ���������� �����.
                  for ( bh = 0 ; ; bh++ )
                  {
                        // ��� �� �����.
                    if ( ptr1[bh] != ptr2[bh] )  break ;

                        // ��� �����������?... ������ ��� �������.
                    if ( ptr1[bh] == 0 || ptr1[bh] == ' ' )  // NULL Vit-07.12.07 14:13
                    {      // ������ ��������������� ����� ��������� ��
                          //     ���������� � ������� �������.
                      JrnData.tab[index1] = index2 ;

                 next:  // �������� ����� ��������� ����������.
                      if ( ++index1 >= _MaxNumVarJrn )
                      {     // ��� ������� ���������.
                        JrnData.label = k0 ; // ������� ����� �� ������.
                        return 0 ;
                      }
                      index2 = -1 ; // ���������� ���������.
                      break ;
                    }
                  }
                      // ��������� � ��������� ���������� � ����������� �������.
                  if ( ++index2 >= FullJrnTab_size ) // ���������� � ������ �����������.
                  {    // ��� �� �������:
                    ptr1[0] = '?' ; // �������� ��� '?' � ����������.
                    goto next ;
                  }
                }
         break;
          //-----------------
    }
  }
  else
  {
    // ���� ���� ������ ������ ��������� ��� �� ��������� ���������� ��������� - �� ���������� ����� ���������� �� �����
    if ( (sb)MsgJrnPrint.uslovie < 0 && *(w*)&MsgJrnPrint.time_msg.time.b[ 6 ] == _CntrCode ) return 0;

    switch ( JrnData.label )
    {
      default:;     // ������ ������.
      case k0 : index1 = 0, index2 = 0 ;
                JrnData.label = k10 ;
         break;
          //-----------------
      case k10:      // ���������� �������� �� ����� 3-� ����������.
                for ( ah = 3 ; ah != 0 ; ah-- )
                {     //  ���� ����� ������ �����, �� ����������.
                  //if ( JrnData.tab[index1].name[0] == '@' ) goto next ;

                  ptr1 = &MsgJrnPrint.name[ 0 ];
                  ptr2 = &FullJrnTab[ index2 ].name[ 0 ];
                       //  ���������� �����.
                  for ( bh = 0 ; ; bh++ )
                  {
                        // ��� �� �����.
                    if ( ptr1[bh] != ptr2[bh] )  break ;

                        // ��� �����������?... ������ ��� �������.
                    if ( ptr1[bh] == 0 || ptr1[bh] == ' ' )  // NULL Vit-07.12.07 14:13
                    {      // ������ ��������������� ����� ��������� ��
                          //     ���������� � ������� �������.
                      JrnData.number = index2 ;
                      JrnData.label = k0 ; // ������� ����� �� ������.
                      return 0 ;
                    }
                  }
                      // ��������� � ��������� ���������� � ����������� �������.
                  if ( ++index2 >= FullJrnTab_size ) // ���������� � ������ �����������.
                  {    // ��� �� �������:
                    MsgJrnPrint.time_msg.time.b[ 7 ] = 0;
                    JrnData.label = k0 ; // ������� ����� �� ������.
                    return 0;
                  }
                }
         break;
          //-----------------
    }
  }
  return 4 ;  // �������� ������������.
}


//---------------------------------------------------

//����� ������� �� �������
void JrnPrint ( void )
{
  register word ax, bx, cx, ex;
  register lword lax;
#ifdef _CM3_

  lword lbx;
  static lword size_i2c ;
#else

  static word size_i2c ;

#endif
  byte  sig_old;
  register byte ab, bb, cb;

  enum { k0, k1, k310, k311, k312, k313, k314, k315, k316, k317,
         k2, k3, k4, k7, k8, k9, k10, k11, k12, k20, k21 };

  if ( M_FirstCall == 1 )  //  ������������� ������� ����� ��� �������
  {                        // ���������� ������� ...
    M_FirstCall = 0;
    Label = k0;
    m_index = 1;
#ifndef _CM3_

    // ��������� ���������� ������� � �������
    m_addr = (w)(_i2c_jrn_end - _i2c_jrn_beg + 1 - _AdrSize);
    m_ext = _i2c_jrn_page;
    if ( m_ext > m_addr ) m_addr = 1; // ������ �� �������� ������ �������� � i2c.
    else m_addr /= m_ext;
#else

    j_ext = (_i2c_jrn_end - _i2c_jrn_beg + 1 - _AdrSize);

    if ( j_ext < _i2c_jrn_page ) m_addr = 1; // ������ �� �������� ������ �������� � i2c.
    else m_addr = j_ext /_i2c_jrn_page;

#endif
    output_s ( _Waiting_txt ) ;
  }

  if ( BitJrn._.tst_msg_jrn != 0 ) //������� ����� ��������� �������
  {
    //����������� ��������� "M_FirstCall" ��� "print_message"
    if ( BitJrn._.tst_msg_jrn == 1 ) BitJrn._.tst_msg_jrn = 2, M_FirstCall = 1;
    print_message ( &MsgJrnPrint.time_msg ); //����� ��������� �� �������
    return;
  }

  //--------------------

  switch ( Label )
  {
    default:
    case k0:

          JrnData.Stop = 1; // ������������� ������
          if ( JrnData.activ == 0 ) Label++;  // ������� ��������� ������� �� ������, ���� ��� ������ ������� ���������
          break;                              // � i2c ������������� ������ ��������� ������ �������

    case k1:
          if ( Mon.i2c_busy == 1 ) break; //  ���� ���� ����������� ����.
          Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������.
#ifndef _CM3_
          jrn_adr_data = (b*)&m_ext;    // ������ ���������� ��������� ������ ����� ������
#else
          jrn_adr_data = (b*)&j_ext;    // ������ ���������� ��������� ������ ����� ������
#endif
          i2c_jrn_addr = _i2c_jrn_beg;  // ��������� ���������������
          i2c_label = 0;                // � i2c ������.
          size_i2c = _AdrSize; // 2;
          Label = k310;
          break;

    case k310:
          goto load;  // �������� ����������.

    case k311:
#ifndef _CM3_
          // �������� ���������: �� ���� �� ��� ������-�� ������.
          if ( m_ext < _i2c_jrn_beg + _AdrSize || m_ext > _i2c_jrn_end ) m_ext = _i2c_jrn_beg + _AdrSize;

          // ��������� �� ����� ��������� ������ ��
          // �������� ���������� ������� � ������ �������� �
          // ������� ������.

          ax = _i2c_jrn_page * m_index;
          bx = m_ext - ( _i2c_jrn_beg + _AdrSize );

          // ��������� �������� ���������, ��� ����� �� ������
          // ������� ������� � ������������ �� �� �����.
          if ( ax > bx )  i2c_jrn_addr = ( (w)_i2c_jrn_end + 1 ) - ( ax - bx );  // (w) - ���������, ����� �� ����
                                                                                 // �������������� ��� i2c �� 32�
          // ��������� �������� ���������, ��� �� ����� �� ������ ������� �������.
          else            i2c_jrn_addr = m_ext - ax;

          // ������ ���������� ����������� �� i2c ������
          jrn_adr_data = (b*)&MsgJrnPrint;
          // ��������� ������� �������� �� ����� i2c.
          bx = _i2c_jrn_end - i2c_jrn_addr + 1;
          size_i2c = sizeof( struct MSG_JRN );
          i2c_label = 0;
          Label = k314;
          // ������� ����� ������� ������� i2c.
          if ( size_i2c > bx )
          {   // ��������� ������ ����� �� ��� �����.
            size_i2c = bx;

#else   //_CM3_
          if ( j_ext < _i2c_jrn_beg + _AdrSize || j_ext > _i2c_jrn_end ) j_ext = _i2c_jrn_beg + _AdrSize;

          // ��������� �� ����� ��������� ������ ��
          // �������� ���������� ������� � ������ �������� �
          // ������� ������.

          lax = _i2c_jrn_page * m_index;
          lbx = j_ext - ( _i2c_jrn_beg + _AdrSize );

          // ��������� �������� ���������, ��� ����� �� ������
          // ������� ������� � ������������ �� �� �����.
          if ( lax > lbx )  i2c_jrn_addr = ( _i2c_jrn_end + 1 ) - ( lax - lbx );  // (w) - ���������, ����� �� ����
                                                                                 // �������������� ��� i2c �� 32�
          // ��������� �������� ���������, ��� �� ����� �� ������ ������� �������.
          else            i2c_jrn_addr = j_ext - lax;

          // ������ ���������� ����������� �� i2c ������
          jrn_adr_data = (b*)&MsgJrnPrint;
          // ��������� ������� �������� �� ����� i2c.
          lbx = _i2c_jrn_end - i2c_jrn_addr + 1;
          size_i2c = sizeof( struct MSG_JRN );
          i2c_label = 0;
          Label = k314;
          // ������� ����� ������� ������� i2c.
          if ( size_i2c > lbx )
          {   // ��������� ������ ����� �� ��� �����.
            size_i2c = lbx;

#endif //_CM3_
            Label = k312;
            // ��������� ���� ����� �����:
    case k312:
            goto load;

    case k313:
            // ��������� ������ ����� �����:
            i2c_jrn_addr += size_i2c; // ��������� ��������� i2c.
            if ( i2c_jrn_addr > _i2c_jrn_end ) i2c_jrn_addr = _i2c_jrn_beg + _AdrSize;
            // �������������� ��������� ��������� � i2c
            jrn_adr_data += size_i2c;   // ������ ��������� �� ���.
            size_i2c = sizeof( struct MSG_JRN ) - size_i2c;
            i2c_label = 0;
            Label = k314;
          }

    case k314:
          goto load;

    case k315:
          Mon.i2c_busy = 0 ;  // ������������� �������, ��� ������ ���� ��������.
          Label++;

    case k316:
          // ������� ������������ ����� �� "MsgJrnPrint.name" � ������ � const-�������.
          // ���� ����� ���������� �� �������, �� � "MsgJrnPrint.time_msg.time.b[ 7 ]" ����� 0.
          if ( TestJrnTab ( 1 ) == 0 )
                Label++;
          break;

    case k317:
          if ( *(w*)&MsgJrnPrint.time_msg.time.b[ 6 ] == _CntrCode ) //������ ����������.
          {
            output_s ( "  Ok." ) ;
            Label = k2;
          }
          else
          {
            output_s ( _Jrn_no_Wrt ) ;
            Label = k20;
          }
          break;

    case k2: // ������� �� ������� ������
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            bb = MsgJrnPrint.time_msg.time.b[ 4 ];  // ����
            cb = bb >> 4;
            cb += 0x30;
            output_c ( cb );
            cb = ( bb & 0x0F ) + 0x30;
            output_c ( cb );
            output_c ( '.' );

            bb = MsgJrnPrint.time_msg.time.b[ 5 ];  // �����
            cb = bb >> 4;
            cb += 0x30;
            output_c ( cb );
            cb = ( bb & 0x0F ) + 0x30;
            output_c ( cb );

            output_s ( DayJrn[ ( MsgJrnPrint.time_msg.time.b[ 3 ] ) - 1 ] ); // ���� ������

            for ( ab = 2; (sw)ab >= 1; --ab  )  // ����, ������
            {
              bb = MsgJrnPrint.time_msg.time.b[ ab ];
              cb = bb >> 4;
              cb += 0x30;
              output_c ( cb );
              cb = ( bb & 0x0F ) + 0x30;
              output_c ( cb );
              output_c ( ':' );
            }
            bb = MsgJrnPrint.time_msg.time.b[ 0 ];  // �������

            cb = bb >> 4;
            cb += 0x30;
            output_c ( cb );
            cb = ( bb & 0x0F ) + 0x30;
            output_c ( cb );

            output_c ( '\n' );

            Label++;
          }
          break;

    case k3: //����� �� ������ ������ ����� ����������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            for ( ab = 0; ab < _VarNameSize; ab++ ) output_c ( MsgJrnPrint.name[ ab ] );
            Label++;
          }
          break;

    case k4:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return )  // ����� �� ����� ������
            {
end:          Pult_Prog_Addr = _MainPultProg, M_FirstCall = 1;
              JrnData.Stop = 0;   // ������ �������
              return;   // �������� ��� �����-�� ����.
            }
            else if ( m_ch == Up ) //��������� ����� ������
            {
              if ( --m_index == 0 ) m_index = m_addr;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else if ( m_ch == Down ) //��������� ����� ������
            {
              if ( ++m_index > m_addr ) m_index = 1;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else if ( m_ch == Enter )
            {
              //� ��������� ������ ������� ������������� ��������� �����-�� ����������
              if ( (sb)MsgJrnPrint.uslovie >= 0 ) Label = k7;
              //� ��������� ������ ������� ������������� ��������� ���������� ��������� -
              //������� ��������� ����� �� ����� ���������
              else if ( (sb)MsgJrnPrint.uslovie == -1 )
              {
                BitJrn._.tst_msg_jrn = 1; //��������� ���������� ���������
                m_ext = (w)k2; //��������� ����� ����� ��� �������� � ��������� ����� ������ ������ ���������
              }
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = k3;
          }
          break;

    case k7: //����� �� ������� ������ ����� ����������
          if ( TestCompleted_Output() )
          {
            output_s ( "\n\r" );
            output_c ( ' ' );
            for ( ab = 0; ab < _VarNameSize; ab++ ) output_c ( MsgJrnPrint.name[ ab ] );
            output_c ( '\n' );
            dptr = &FullJrnTab[ JrnData.number ];
            Label++;
          }
          break;

    case k8: //�� ������ ������ - ������� � ��������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            // ���������� ���������� ��� ������������ �������� ������
            if ( dptr->code._.ad == 0 || dptr->code._.ad == 2 ) Label = k9;  //���������� ����������
            else Label = k11; //���������� ����������
          }
          break;

    case k9: //�������� ���������� ����������
          if ( TestCompleted_Output() )
          {
            for ( ax = 0; ax < Menu3_size; ax++) //����� ������ �������
            {
              if ( MsgJrnPrint.uslovie == Menu3[ ax ].label )
              {
                output_s ( Menu3[ ax ].txt ); //���������� �������
                break;
              }
            }

            ax = MsgJrnPrint.value; //����� �������� ����������

            // ���������� � 10-������ ����

            // ���������� ����������, �������������� �������� ������ ��� ��������� ����������
            if ( dptr->code._.ad == 2 || dptr->code._.ad == 1 ) bx = 1;
            else bx = dptr->nom;
            cx = *(w*)dptr->abs_nom;
            if ( dptr->code._.off_sign == 0 )
            {    //���� ���������� �� ������ - �������� ���� � ������
              if ( (sw)ax >= 0 )   sig_old = '+';
              else   ax = ~ax + 1, sig_old = '-';
            }

            //�������� ���������� ������ � ��� ���������
            lax = (lw)ax * (lw)cx;
            m_ext = lax % bx;
            lax /= bx;
            if ( lax > 0xffffu) lax = 0xffff;

            //���������� ����� ����� - �������� 5 ��������
            ex = 5 - dptr->code._.celoe; //������� ������ �������� ����������
            if ( ex == 5 ) ex = 2; //��� ������������� - ���� ������ ���� ���� �� ��������� ������ "3.2".
            else if ( (sw)ex < 0 ) ex = 0;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;
              //���� ���� ������ ���� - �� ������� ��:
              if ( bx == 0 && cx == 0 )
              {     //� ���������� ������ ������� �������,
                if ( ex != 0 ) ex--;
                //��� �������� ���������
                else output_c (' ');
              }
              else
              {
                if ( cx == 0 )
                {
                  if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
                  cx = 1;
                }
                //������ ���� �����������
                output_c ( (b)bx + 0x30 );
              }
            }   //������������� ��������� �����
            if ( cx == 0 )
            {
              if ( dptr->code._.off_sign == 0 ) output_c ( sig_old );
            }
            output_c ( (b)(w)lax + 0x30 );
            Label = k10;
          }
          break;

    case k10:    //���������� ������� �����
          if ( TestCompleted_Output() )
          {
            if ( dptr->code._.celoe == 0 ) ex = 2;// �� ���������.
            else ex = dptr->code._.drob;
            if ( ex != 0 )
            {
              output_c ( '.' );
              bx = dptr->nom;
              lax = m_ext; //��������������� �������
              for ( ; ex != 0 ; ex-- )
              {
                lax *= 10;
                ax = lax / bx;
                lax %= bx;
                output_c ( (b)ax + 0x30 );
              }
            }
            output_s ( dptr->ch );
            Label = k12;
          }
          break;

    case k11: //�������� ���������� ����������
          if ( TestCompleted_Output() )
          {
            ab = MsgJrnPrint.value; //����� ����

            output_s ( "n." );
            output_c ( ab / 10  + 0x30 );
            output_c ( ab % 10  + 0x30 );
            for ( ax = 0; ax < Menu3_size; ax++ ) //����� ������ �������
            {
              if ( MsgJrnPrint.uslovie == Menu3[ ax ].label )
              {
                output_s ( Menu3[ ax ].txt ); //���������� �������
                break;
              }
            }
            output_c ( '0' );
            Label = k12;
          }
          break;

    case k12:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) Label = k2;
            else if ( m_ch == Enter )
            {
              BitJrn._.tst_msg_jrn = 1; //��������� ���������� ���������
              m_ext = (w)k2; //��������� ����� ����� ��� �������� � ��������� ����� ������ ������ ���������
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = k8;
          }
          break;

          //---------------------------------------------

          load:   //   �������� ������
               ax = xLoad_from_i2c ( size_i2c , i2c_jrn_addr, jrn_adr_data, _Adr_Flash_i2c ) ;
               if ( ax == 4 );   // ���� = 4 - ������ �� ���������.
               else if ( ax == 1 )
               { // ������� �������� ����� �� i2c.
                 output_s ( _NoConnect_i2c_txt );
                 Mon.i2c_busy = 0;  // ������������� �������, ��� ������ ���� ��������.
                 goto end;
               }
               else  Label++;
               break;

    case k20: // ����� ������ ������
          if ( TestCompleted_Output() )
          {
            output_c ( '\r' );
            output_s ( AWelcome );
            output_s ( "N = " );

            lax = (lw)m_index;
            for ( ax = 10000, cx = 0; ax != 1; ax /= 10 )
            {
              bx = lax / ax;
              lax %= ax;

              if ( bx == 0 && cx == 0 ) output_c (' '); //���� ���� ������ ���� - �� ������� ��
              else
              {
                cx = 1;
                output_c ( (b)bx + 0x30 );
              }
            }
            output_c ( (b)(w)lax + 0x30 ); //������������� ��������� �����
            Label = k21;
          }
          break ;

    case k21:
          if ( TestData_for_Input() )
          {
            mInput_c ( m_ch );
            if ( m_ch == Return ) goto end; // ����� �� ����� ������
            else if ( m_ch == Up ) //��������� ����� ������
            {
              if ( --m_index == 0 ) m_index = m_addr;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else if ( m_ch == Down ) //��������� ����� ������
            {
              if ( ++m_index > m_addr ) m_index = 1;
              output_s ( _Waiting_txt ) ;
              Label = k1;
            }
            else Klav_Buff = m_ch;
          }
          if ( AWelcome != AWell_old )
          {
            AWell_old = AWelcome;
            Label = k20;
          }
          break;

  }

  Restart_Output ( );

  return;
}


//������ ������ ������� � i2c
word Save_jrn ( void )
{
   register word    ax;
#ifndef _CM3_
   register word   bx;
   static word size_i2c ;
#else
   lword lbx;
   static lword size_i2c ;

#endif

      //   ������� �������, ����� ������ ����� ����� � ����� ���
      //  ��������������� �� ������������.
  enum { i0, i00, i1, i2, i2_1, i2_2, i2_3, i2_4, i3, i7 };


    switch ( i2c_jrn_label )
     {
      default: i2c_jrn_label = i0;
      case i0:
               if ( ( ( OutJrnPtr + 1 ) & _MaxJrnCount ) != InJrnPtr ) i2c_jrn_label++; // � ������ ���� ����� ������
               break;

      case i00:
               if ( Mon.i2c_busy == 1 ) break; //  ���� ���� ����������� ����.
               Mon.i2c_busy = 1;  // ������������� �������, ��� ������ ���� ������.
                  //  ������� ����� ������� � �������� ���������
                 // ��������� ����� ��� ������� xLoad_from_i2c.
               i2c_label = 0, i2c_jrn_label++;
      case i1:
                 //   ���������� ��������� ������ ����� ������ ���������
                // ��������������� � i2c ������.
               ax = xLoad_from_i2c ( _AdrSize , _i2c_jrn_beg , (b*)&i2c_jrn_addr, _Adr_Flash_i2c ) ;
               goto read;
               //-----------------
      case i2 :   //  �������� ���������: �� ���� �� ��� ������-�� ������.
               if ( i2c_jrn_addr < _i2c_jrn_beg+_AdrSize  ||
                    i2c_jrn_addr > _i2c_jrn_end) i2c_jrn_addr = _i2c_jrn_beg+_AdrSize ;
               //-----------------
                 // ���� ����� ��������� ������ �� ������
               jrn_adr_data = (b*)&MsgJrn[ ( OutJrnPtr + 1 ) & _MaxJrnCount ];
#ifndef _CM3_
                 // ��������� ������� �������� �� ����� i2c.
               bx = _i2c_jrn_end - i2c_jrn_addr + 1 ;
               size_i2c = sizeof(struct MSG_JRN) ;
               i2c_label = 0 , i2c_jrn_label = i2_3 ;
                      // ������� ����� ������� ������� i2c.
                 if ( size_i2c > bx )
                 {   // ��������� ������ ����� �� ��� �����.
                   size_i2c = bx ;
#else  //_CM3_
                 // ��������� ������� �������� �� ����� i2c.
               lbx = _i2c_jrn_end - i2c_jrn_addr + 1 ;
               size_i2c = sizeof(struct MSG_JRN) ;
               i2c_label = 0 , i2c_jrn_label = i2_3 ;
                      // ������� ����� ������� ������� i2c.
                 if ( size_i2c > lbx )
                 {   // ��������� ������ ����� �� ��� �����.
                   size_i2c = lbx ;
#endif        //_CM3_
                   i2c_jrn_label = i2_1 ;
                    // ���������� ���� ����� �����:
    case i2_1 :    goto save ;
    case i2_2 :      // ���������� ������ ����� �����:
                   i2c_jrn_addr += size_i2c ; // ��������� ��������� i2c.
                   if ( i2c_jrn_addr > _i2c_jrn_end ) i2c_jrn_addr = _i2c_jrn_beg+_AdrSize ;
                      // �������������� ��������� ��������� � i2c
                   jrn_adr_data += size_i2c ;   // ������ ��������� �� ���.
                   size_i2c = sizeof(struct MSG_JRN) - size_i2c ;
                   i2c_label = 0 , i2c_jrn_label = i2_3 ;
                 }
    case i2_3 :  goto save ;
    case i2_4 :
                i2c_jrn_addr += size_i2c ;    // ��������� ��������� i2c.
                if ( i2c_jrn_addr > _i2c_jrn_end ) i2c_jrn_addr = _i2c_jrn_beg+_AdrSize ;
                i2c_jrn_label = i3 ;
                break;

               //-----------------
      case i3 :  //   ������ ��������� ������ ����� ������ ���������
                // ��������������� � i2c ������.
               ax = xSave_into_i2c ( _AdrSize , (b*) &i2c_jrn_addr , _i2c_jrn_beg, _Adr_Flash_i2c ) ;
               goto read;
      case i7 :
               Mon.i2c_busy = 0 ;  // ������������� �������, ��� ������ ���� ��������.
               OutJrnPtr = ( OutJrnPtr + 1 ) & _MaxJrnCount; //����������� ��������� ������������ ������
               i2c_jrn_label = i0;
               return 0;
               //-----------------

      //---------------------------------------------

          read:   //  �������� ���� ������������� �/� xLoad_from_i2c.
               if ( ax == 4 ) ;  // ���� = 4 - ���������� ������.
               else if ( ax == 1 )
                 {
                   mSet_ServiceMsg( _Srv_NoRead_i2c ) ;
                   Mon.i2c_busy = 0 ;  // ������������� �������, ��� ������ ���� ��������.
                   i2c_jrn_label = i0;
                   return 1;
                 }
               else  i2c_jrn_label++ ;
               break;

          save:   //   �������� ������.
               ax = xSave_into_i2c ( size_i2c , jrn_adr_data , i2c_jrn_addr, _Adr_Flash_i2c ) ;
               if ( ax == 4 ) ;   // ���� = 4 - ������ �� ���������.
               else if ( ax == 1 )
               {
                   // ������� �������� ����� �� i2c.
                   mSet_ServiceMsg( _Srv_NoWrite_i2c ) ;
                   Mon.i2c_busy = 0 ;  // ������������� �������, ��� ������ ���� ��������.
                   i2c_jrn_label = i0;
                   return 1;
               }
               else  i2c_jrn_label++ ;
               break;
    }
  return 4;
}
