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

  // Принцип определения входов выходов как и для S400 по значению в _or.AS_CSo[ax]
  void  Set_cs_sio (byte cs_n)
  {
    register word ax;

    ax = (w)((cs_n + 1) % 3);

      // Признак выхода
    if ( ax == 0 )
     {
      ax = (w)((cs_n + 1) / 3) ;
        // Если запросили порт не входящий в сетку _SOut_max
      if ( ax > _SOut_max  )
       {
        Clr_num_port() ;
        return ;
       }
        // в ВТЕ однопл. выходные порты подключаются установкой кодировки на вход дешифратора 3 и 4.
        // Соответственно для AS_CSo[_SOut_max] = 2 должны установить код = 3, для AS_CSo[_SOut_max] = 5 должны установить код = 4
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
      // Иначе вход
    else
     {
      ax = (w)((cs_n + 2) / 2) ;    // входной порт может быть ( Pi(x), Pi(x+1) ), где x приним. знач. от x=0, и далее x +=2
        // Если запросили порт не входящий в сетку _SInp_max
      if ( ax >= _SInp_max  )
       {
        Clr_num_port() ;
        return ;
       }

        // в ВТЕ однопл. входные порты подключаются установкой кодировки на вход дешифратора 0 ... 3.
        // Соответственно для AS_CSi[_SInp_max] = 0 должны установить код = 0
        //                для AS_CSi[_SInp_max] = 1 должны установить код = 1
        //                для AS_CSi[_SInp_max] = 3 должны установить код = 2
      ax = (w)(( (cs_n % 3) + ((cs_n / 3) * 2)) % 3) ; //  ( ... ) % 3 защита от выдачи кода выборки выходов do (если _SInp_max > 3)

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
  // выборка на S500 осуществляется следующим образом:
  // 1. первые две ноги CS_IO[0], CS_IO[1]  - выбор входного/выходного порта, знач.= 0 и 1 это признак входного пота, 2 ризнак выходного порта
  // 2. остальные ноги CS_IO[2], CS_IO[3], CS_IO[4] это выбор номера плат
  // 3. очистка CS_IO[0], CS_IO[1] нулем
  // 4. очистка CS_IO[2], CS_IO[3], CS_IO[4] еденицей

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


