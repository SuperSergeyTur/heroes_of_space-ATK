#ifndef _S500

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

#else //#ifndef _S500
//------------------------------------------------------------------------------------------------

void  Set_cs_sio (byte numb)
{
  byte bh;
  word ax;
 /* _Clr_CS(CS_IO[0]);
  _Clr_CS(CS_IO[1]);
  _Set_CS(CS_IO[2]);
  _Set_CS(CS_IO[3]);
  _Set_CS(CS_IO[4]);
*/
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
