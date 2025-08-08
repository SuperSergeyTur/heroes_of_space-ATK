word ADE_Read24v16 (byte RegNo)
{

    register byte  al ;
    register word  ax , bx , cx ;


    //Устанавливаем выборку
  ssio_busy = 1;                      // Признак того, что последовательный порт занят для прерываний.
  Set_cs_sio (12);

    sio_out(RegNo);
//---------
    //Выдержка времени на срабатывание сигнала выборки
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    cx = (w)al * 256 ;//<< 8 ;
//---------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    cx += (w)al ;
//---------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);

  ssio_busy = 0;                      // Снимаем признак
  Clr_cs_sio (0);

  return  cx;

}



lword ADE_Read24 (byte RegNo)
{
    register byte  al ;
    register word  ax , bx ;
    register lword  lax ;


    //Устанавливаем выборку
  ssio_busy = 1;                      // Признак того, что последовательный порт занят для прерываний.
  Set_cs_sio (12);

    sio_out(RegNo);
//---------
    //Выдержка времени на срабатывание сигнала выборки
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    lax = (lw)al * 65536. ;//<< 16 ;
//---------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    lax += (lw)al * 256. ;//<< 8 ;
//---------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    lax += (lw)al ;


  ssio_busy = 0;                      // Снимаем признак
  Clr_cs_sio (0);

  return lax ;

}

word ADE_Read16 (byte RegNo)
{
    register byte  al ;
    register word  ax , bx , cx ;


    //Устанавливаем выборку
  ssio_busy = 1;                      // Признак того, что последовательный порт занят для прерываний.
  Set_cs_sio (12);

    sio_out(RegNo);
//---------
    //Выдержка времени на срабатывание сигнала выборки
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    cx = (w)al * 256 ;//<< 8 ;
//---------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    cx += (w)al ;


  ssio_busy = 0;                      // Снимаем признак
  Clr_cs_sio (0);

  return  cx;

}

byte ADE_Read8 (byte RegNo)
{
    register byte  al, cx ;
    register word  ax , bx ;


    //Устанавливаем выборку
  ssio_busy = 1;                      // Признак того, что последовательный порт занят для прерываний.
  Set_cs_sio (12);

    sio_out(RegNo);

    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_in(al);
    cx = al ;

  ssio_busy = 0;                      // Снимаем признак
  Clr_cs_sio (0);

  return cx;

}

void ADE_Write8 (byte RegNo, byte RegData)
{
    register word  ax , bx ;


    //Устанавливаем выборку
  ssio_busy = 1;                      // Признак того, что последовательный порт занят для прерываний.
  Set_cs_sio (12);

    RegNo += 0x80 ;
    sio_out(RegNo);

    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_out(RegData);

  ssio_busy = 0;                      // Снимаем признак
  Clr_cs_sio (0);

  return ;

}

void ADE_Write16 (byte RegNo, word RegData)
{
    register word  ax , bx ;


    //Устанавливаем выборку
  ssio_busy = 1;                      // Признак того, что последовательный порт занят для прерываний.
  Set_cs_sio (12);

    RegNo += 0x80 ;
    sio_out(RegNo);
//-------------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_out(RegData/256);
//-------------
    ax = timer1;
    do  bx = timer1 - ax;
    while ((u)bx < _MkSec(2) );
    //Считываем сигнал из SIO
    sio_out(RegData);

  ssio_busy = 0;                      // Снимаем признак
  Clr_cs_sio (0);

  return ;

}
