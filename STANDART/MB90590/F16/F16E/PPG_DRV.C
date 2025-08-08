
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
        case 1 :
                 if ( lev == 1 ) PDR5_P51 = 1;
                 else            PDR5_P51 = 0;
                 DDR5_D51 = 1;

                 //PPG23_PCS = clk;   // Частота счета
                 PPG23_PCM = clk;   // Частота счета
                     // enable PPG operation без подключения к выходу.
                    //для 16-разрядного реж.  запись нужно производить словом.
                 *(w*)&PPGC2 = 0x0707;
                 //PPGC3 = 0x87;               // enable PPG operation
               break;
              //------------
      }

  return ;
}


//
//     Инициализация частоты PPG с заданием его номера, уровня нуля и
//   единицы. PPG остается в отключенном состоянии.
//
void  PPG_set( byte n, word low, word high )
{
   if ( low  != 0 )   low-- ;  //  корректировка, т.к. PPG
   if ( high != 0 )  high-- ;  // автоматически добавляет одну дискрету.

      switch ( n )
      {
        case 1 :
                 PRLL2 = low  ;
                 PRLH2 = high ;
                 *(w*)&PRLL3 = (low >> 8) | (high & 0xff00) ;
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
      byte bh1,bh2;
      switch ( n )
      {
        case 1 :
                 //Синхронизация комманды старт - чтобы стартовало
                 //с единицы
                 bh1 = PRLL2;
                 bh2 = PRLL3;
                 PRLL2 = s;
                 PRLL3 = 0;
                *(w*)&PPGC2 |= 0xA080;
                 PRLL2 = bh1;
                 PRLL3 = bh2;
                 //PPGC2 |= 0x20;
                 //PPGC3 |= 0x20;      // подключаем PPG к выходу.
               break;
              //------------
      }
  return ;
}


//
//     Остановка PPG с заданием его номера и исходного выходного
//   уровня.
//
void  PPG_stop( byte n, byte lev )
{
      switch ( n )
      {
        case 1 :
                 //PPGC2 &= ~0x20;
                 //PPGC3 &= ~0x20;   // отключаем PPG от выхода.
                 *(w*)&PPGC2 &= ~0xa080;
                 PDR5_P51 = lev ;  // задаем предварительно требуемый уровень выхода.
               break;
              //------------
      }

  return ;
}

