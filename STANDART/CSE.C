#ifndef _S500

void  Set_cs_sio (byte numb)
{
  switch ( numb )
  {
    case 0:
            _CS0 = 0;
            break;
    case 1:
            _CS1 = 0;
            break;
    case 2:
            _CS2 = 0;
            break;
    case 3:
            _CS3 = 0;
            break;
    case 4:
            _CS4 = 0;
            break;
#ifdef  _CS5
    case 5:
            _CS5 = 0;
            break;
#endif
#ifdef  _CS6
    case 6:
            _CS6 = 0;
            break;
#endif
#ifdef  _CS7
    case 7:
            _CS7 = 0;
            break;
#endif
#ifdef  _CS8
    case 8:
            _CS8 = 0;
            break;
#endif
#ifdef  _CS9
    case 9:
            _CS9 = 0;
            break;
#endif
    default:
            break;
  }
  return ;
}

void  Clr_cs_sio (byte numb)
{
  switch ( numb )
  {
    case 0:
            _CS0 = 1;
            break;
    case 1:
            _CS1 = 1;
            break;
    case 2:
            _CS2 = 1;
            break;
    case 3:
            _CS3 = 1;
            break;
    case 4:
            _CS4 = 1;
            break;
#ifdef  _CS5
    case 5:
            _CS5 = 1;
            break;
#endif
#ifdef  _CS6
    case 6:
            _CS6 = 1;
            break;
#endif
#ifdef  _CS7
    case 7:
            _CS7 = 1;
            break;
#endif
#ifdef  _CS8
    case 8:
            _CS8 = 1;
            break;
#endif
#ifdef  _CS9
    case 9:
            _CS9 = 1;
            break;
#endif
    default:
            break;
  }
  return ;
}

#else //#ifndef _S500
//------------------------------------------------------------------------------------------------

void  Set_cs_sio (byte numb)
{
  byte bh;
 // _CS0 = 0; ---\ эти выборки и так остаются в "0" после последнего сброса в "Clr_cs_sio"
 // _CS1 = 0; ---/
 // _CS2 = 1; --\
 // _CS3 = 1; ---> закомментировано, чтобы не дергать лишний раз выборку платы
 // _CS4 = 1; --/

  bh = numb/3;


  switch ( bh )
  {
    default:
    case 0:
            _CS2 = 1;
            _CS3 = 1;
            _CS4 = 1;
            break;
    case 1:
            _CS2 = 0;
            _CS3 = 1;
            _CS4 = 1;
            break;
    case 2:
            _CS2 = 1;
            _CS3 = 0;
            _CS4 = 1;
            break;
    case 3:
            _CS2 = 0;
            _CS3 = 0;
            _CS4 = 1;
            break;
    case 4:
            _CS2 = 1;
            _CS3 = 1;
            _CS4 = 0;
            break;
    case 5:
            _CS2 = 0;
            _CS3 = 1;
            _CS4 = 0;
            break;
    case 6:
            _CS2 = 1;
            _CS3 = 0;
            _CS4 = 0;
            break;
    case 7:
            _CS2 = 0;
            _CS3 = 0;
            _CS4 = 0;
            break;
  }
  bh = (numb%3)+1;
  Set_num_port(bh);
  return ;
}

void  Clr_cs_sio (byte numb)
{
  numb = 0;

  //_CS0 = 0;     // _CS0 и _CS1 надо обнулять одновременно,  чтобы не было ложной выборки
  //_CS1 = 0;     // порта AsPi1 после обращения к порту AsPo0 из-за задержки обнуления _CS1
  Clr_num_port(); // в 0.5 мкс после обнуления _CS0, что на длинной ленте способствует помехам
  _CS2 = 1;       // при считывании входных портов (проявилось 12.2013г. на пульте управления печью ферросплавный)
  _CS3 = 1;
  _CS4 = 1;
  return ;
}

#endif //#ifndef _S500
