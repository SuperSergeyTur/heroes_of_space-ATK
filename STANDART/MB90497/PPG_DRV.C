
//************     8-ми РАЗРЯДНЫЕ "PPG"       *************

 void PPG_stop(byte n,byte lev)
 {
     switch ( n )
     {
      case 0:
              PPGC0 &= 0x5f;
              PDR1_P14 = lev;
              break;
      case 1:
              PPGC1 &= 0x5f;
              PDR1_P15 = lev;
              break;
      case 2:
              PPGC2 &= 0x5f;
              PDR1_P16 = lev;
              break;
      case 3:
              PPGC3 &= 0x5f;
              PDR1_P17 = lev;
              break;
     }
  return ;
 }

//     Инициализация частоты PPG с заданием его номера, уровня нуля и
//   единицы. PPG остается в отключенном состоянии.
//
void  PPG_set( byte n, word low, word high )
{
   if ( low  != 0 )   low-- ;  //  корректировка, т.к. PPG
   if ( high != 0 )  high-- ;  // автоматически добавляет одну дискрету.

      switch ( n )
      {
        case 0 :
                 PRLL0 = low  ;       //  младший байт для "0".
                 PRLH0 = high ;       //  старший байт для "0".
               break;
              //------------
        case 1 :
                 PRLL1 = low  ;       //  младший байт для "1".
                 PRLH1 = high ;       //  старший байт для "1".
               break;
              //------------
        case 2 :
                 PRLL2 = low  ;       //  младший байт для "2".
                 PRLH2 = high ;       //  старший байт для "2".
               break;
              //------------
        case 3 :
                 PRLL3 = low  ;       //  младший байт для "3".
                 PRLH3 = high ;       //  старший байт для "3".
               break;
              //------------
      }

  return ;
}


//
//     Инициализация PPG в 16-ти разрядный режим с заданием его
//   номера, делителя базовой частоты и исходного выходного уровня.
//     PPG остается в отключенном состоянии.
//
//  clk:  4 -  1.00 мкс  (16МГц/16)
//        3 -  0.50 мкс
//        2 -  0.25 мкс
//        1 -  0.125мкс
//        0 -  0.063мкс

void  PPG_init( byte n, byte clk, byte lev)
{
      switch ( n )
      {
        case 0 :
                 if ( lev == 1 ) PDR1_P14 = 1;
                 else            PDR1_P14 = 0;
                 DDR1_D14 = 1;

                 PPG01_PCM = clk;   // Частота счета
                     // enable PPG operation без подключения к выходу.
                    //  для 16-разрядного реж. запись нужно производить словом,
                    // иначе по подаче питания PPG глючит и начинает работать
                    // только после перезапуска при поданном питании.
                 PPGC0 = 0xa1;    // enable PPG operation
               break;
              //------------
        case 1 :
                 if ( lev == 1 ) PDR1_P15 = 1;
                 else            PDR1_P15 = 0;
                 DDR1_D15 = 1;

                 PPG01_PCS = clk;   // Частота счета
                     // enable PPG operation без подключения к выходу.
                    //  для 16-разрядного реж. запись нужно производить словом,
                    // иначе по подаче питания PPG глючит и начинает работать
                    // только после перезапуска при поданном питании.
                 PPGC1 = 0xa1;    // enable PPG operation
               break;
              //------------
        case 2 :
                 if ( lev == 1 ) PDR1_P16 = 1;
                 else            PDR1_P16 = 0;
                 DDR1_D16 = 1;

                 PPG23_PCM = clk;   // Частота счета
                     // enable PPG operation без подключения к выходу.
                    //  для 16-разрядного реж. запись нужно производить словом,
                    // иначе по подаче питания PPG глючит и начинает работать
                    // только после перезапуска при поданном питании.
                 PPGC2 = 0xa1;    // enable PPG operation
               break;
              //------------
        case 3 :
                 if ( lev == 1 ) PDR1_P17 = 1;
                 else            PDR1_P17 = 0;
                 DDR1_D17 = 1;

                 PPG23_PCS = clk;   // Частота счета
                     // enable PPG operation без подключения к выходу.
                    //  для 16-разрядного реж. запись нужно производить словом,
                    // иначе по подаче питания PPG глючит и начинает работать
                    // только после перезапуска при поданном питании.
                 PPGC3 = 0xa1;    // enable PPG operation
               break;
              //------------
      }

  return ;
}

//
//     Запуск PPG с заданием его номера.
//
void  PPG_start( byte n, byte s )
{
  byte bh, bh1;
      switch ( n )
      {
        case 0 :
                 bh = PRLH0;
                 bh1 = PRLL0;
                 PRLH0 = s;
                 PRLL0 = 0;
                 PPGC0 |= 0xA0;
                 PRLH0 = bh;
                 PRLL0 = bh1;
               break;

              //------------
        case 1 :
                 bh = PRLH1;
                 bh1 = PRLL1;
                 PRLH1 = s;
                 PRLL1 = 0;
                 PPGC1 |= 0xA0;
                 PRLH1 = bh;
                 PRLL1 = bh1;
               break;

              //------------
        case 2 :
                 bh = PRLH2;
                 bh1 = PRLL2;
                 PRLH2 = s;
                 PRLL2 = 0;
                 PPGC2 |= 0xA0;
                 PRLH2 = bh;
                 PRLL2 = bh1;
               break;

              //------------
        case 3 :
                 bh = PRLH3;
                 bh1 = PRLL3;
                 PRLH3 = s;
                 PRLL3 = 0;
                 PPGC3 |= 0xA0;
                 PRLH3 = bh;
                 PRLL3 = bh1;

               break;
      }
  return ;
}

