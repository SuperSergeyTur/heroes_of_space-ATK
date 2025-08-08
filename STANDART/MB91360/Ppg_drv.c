
//
//     Инициализация PPG в 16-ти разрядный режим с заданием его
//   номера, делителя базовой частоты и исходного выходного уровня.
//     PPG остается в отключенном состоянии.
//
//  clk:  3 -  4 мкс
//        2 -  1.00 мкс  (16МГц/16)
//        1 -  0.25мкс
//        0 -  0.063мкс

void  PPG_init( byte n, byte clk, byte lev)
{
  word ax;
  GCN10 =  0x3210;
  GCN11 =  0x3210;
  ax = (clk<<2)|0x10;
      switch ( n )
      {
        case 0 :
                PCNH0_CNTE = 0; // disable PWM0
                PFRO_PFO0 = 0;
                if ( lev == 1 ) PDRO_PDO0 = 1;
                else PDRO_PDO0 = 0;


                PCNH0 = ax;//0x10;
                //PCNH0 |= ax;
                //PCNL0 = 0x45 ;
                PCNL0 = 0x44 ;
                PCNH0_CNTE = 1; // enable PWM0
               GCN20 &= 0xfe;
               GCN20 |= 0x01;

               break;
              //------------
        case 1 :
                PCNH1_CNTE = 0; // disable PWM0

                PFRO_PFO1 = 0;
                if ( lev == 1 ) PDRO_PDO1 = 1;
                else PDRO_PDO1 = 0;


                PCNH1 = ax;//0x10;
                //PCNH1 |= ax;
                PCNL1 = 0x44 ;

                PCNH1_CNTE = 1; // enable PWM0
               GCN20 &= 0xfd;
               GCN20 |= 0x02;

               break;
              //------------
        case 2 :
                PCNH2_CNTE = 0; // disable PWM0

                PFRO_PFO2 = 0;
                if ( lev == 1 ) PDRO_PDO2 = 1;
                else PDRO_PDO2 = 0;


                PCNH2 = ax;//0x10;
                //PCNH2 |= ax;
                PCNL2 = 0x44 ;

                PCNH2_CNTE = 1; // enable PWM0
               GCN20 &= 0xfb;
               GCN20 |= 0x04;
               break;
              //------------
        case 3 :
                PCNH3_CNTE = 0; // disable PWM0

                PFRO_PFO3 = 0;
                if ( lev == 1 ) PDRO_PDO3 = 1;
                else PDRO_PDO3 = 0;


                PCNH3 = ax;//0x10;
                //PCNH3 |= ax;
                PCNL3 = 0x44 ;

                PCNH3_CNTE = 1; // enable PWM0

               GCN20 &= 0xf7;
               GCN20 |= 0x08;
               break;
              //------------
        case 4 :
                PCNH4_CNTE = 0; // disable PWM0

                PFRO_PFO4 = 0;
                if ( lev == 1 ) PDRO_PDO4 = 1;
                else PDRO_PDO4 = 0;


                PCNH4 = ax;//0x10;
                //PCNH4 |= ax;
                PCNL4 = 0x44 ;

                PCNH4_CNTE = 1; // enable PWM0
               GCN21 &= 0xfe;
               GCN21 |= 0x1;
               break;
              //------------
        case 5 :
                PCNH5_CNTE = 0; // disable PWM0

                PFRO_PFO5 = 0;
                if ( lev == 1 ) PDRO_PDO5 = 1;
                else PDRO_PDO5 = 0;


                PCNH5 = ax;//0x10;
                //PCNH5 |= ax;
                PCNL5 = 0x44 ;

                PCNH5_CNTE = 1; // enable PWM0

               GCN21 &= 0xfd;
               GCN21 |= 0x02;
               break;
              //------------
        case 6 :
                PCNH6_CNTE = 0; // disable PWM0

                PFRO_PFO6 = 0;
                if ( lev == 1 ) PDRO_PDO6 = 1;
                else PDRO_PDO6 = 0;


                PCNH6 = ax;//0x10;
                //PCNH6 |= ax;
                PCNL6 = 0x44 ;

                PCNH6_CNTE = 1; // enable PWM0
               GCN21 &= 0xfb;
               GCN21 |= 0x04;
               break;
              //------------
        case 7 :
                PCNH7_CNTE = 0; // disable PWM0

                PFRO_PFO7 = 0;
                if ( lev == 1 ) PDRO_PDO7 = 1;
                else PDRO_PDO7 = 0;


                PCNH7 = ax;//0x10;
                //PCNH7 |= ax;
                PCNL7 = 0x44 ;

                PCNH7_CNTE = 1; // enable PWM0

               GCN21 &= 0xf7;
               GCN21 |= 0x08;
               break;
              //------------
      }

  return ;
}

//---- Для инициализации PPG как СУММЫ ИМПУЛЬСОВ УПРАВЛЕНИЯ .
//
//     Инициализация частоты PPG с заданием его номера, уровня нуля и
//   единицы. PPG остается в отключенном состоянии.
//
/*
void  PPG_set( byte n, word low, word high )
{
  word ax,bx ;
      switch ( n )
      {
        case 0 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR0 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT0 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 1 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR1 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT1 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 2 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR2 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT2 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 3 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR3 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT3 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 4 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR4 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT4 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 5 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR5 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT5 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 6 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR6 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT6 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
        case 7 :
                //Частота импульсов
                bx = high+low;
                ax =( F_Mh*bx) - 1; //Требуемое число вычисляется по формуле m = (Fpb*tcikl) -1
                PCSR7 = ax;          //где Fpb - частота таймера, определяемая СKS0,1 в PCNH(MГц)
                                     //    tcikl - период в мкс.
                //Длительность импульса
                ax = F_Mh*low - 1;
                PDUT7 = ax;          // Требуемое число вычисляется по формуле n = Fpb*t -1
                                    // где Fpb - частота таймера, определяемая СKS0,1 в PCNH(МГц)
                                    // t - требуемая длительность импульса (мкс)
                                    // для четных каналов из t вычитается мертвое время
               break;
              //------------
      }

  return ;
}
*/
//---- Для инициализации PPG как ЦАП :
//
//     Инициализация частоты PPG с заданием его номера, уровня нуля и
//   единицы. PPG остается в отключенном состоянии.
//
void  PPG_set( byte n, word low, word high )
{
  register word ax,bx ;
      switch ( n )
      {
        case 0 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR0 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT0 = ax;
        asm_di();
                ppg_dut[0][0] = bx;
                ppg_dut[0][1] = ax;
        asm_ei();

               break;
              //------------
        case 1 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR1 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT1 = ax;
        asm_di();
                ppg_dut[1][0] = bx;
                ppg_dut[1][1] = ax;
        asm_ei();
               break;
              //------------
        case 2 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR2 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT2 = ax;
        asm_di();
                ppg_dut[2][0] = bx;
                ppg_dut[2][1] = ax;
        asm_ei();
               break;
              //------------
        case 3 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR3 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT3 = ax;
        asm_di();
                ppg_dut[3][0] = bx;
                ppg_dut[3][1] = ax;
        asm_ei();
               break;
              //------------
        case 4 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR4 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT4 = ax;
        asm_di();
                ppg_dut[4][0] = bx;
                ppg_dut[4][1] = ax;
        asm_ei();
               break;
              //------------
        case 5 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR5 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT5 = ax;
        asm_di();
                ppg_dut[5][0] = bx;
                ppg_dut[5][1] = ax;
        asm_ei();
               break;
              //------------
        case 6 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR6 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT6 = ax;
        asm_di();
                ppg_dut[6][0] = bx;
                ppg_dut[6][1] = ax;
        asm_ei();
               break;
              //------------
        case 7 :
                //Частота импульсов
                bx = high+low;
                ax = high;
                if ( bx != 0) --bx;
                PCSR7 = bx;
                if ( ax != 0)  --ax;
                else ax = 0;
                PDUT7 = ax;
        asm_di();
                ppg_dut[7][0] = bx;
                ppg_dut[7][1] = ax;
        asm_ei();
               break;
              //------------
      }

  return ;
}


//
//     Запуск PPG с заданием его номера.
//
void  PPG_start( byte n, byte s )  //  s - задает длительность "0"-уровня перед "1"-уровнем.
{
      switch ( n )
      {
        case 0 :

              //PFRO_PFO0 = 1;  нельзя подключать выход PPG к ножке, пока его не перезапустили "PCNH0_STGR=1",
              //          т.к. он продолжает генерировать старый меандр и на выход прорывается на несколько мкс "1".

                //PCSR и PDUT  - регистры только для записи, читать их нельзя
                PCSR0 = ppg_dut[0][1]+s;    // длительность периода (сумма нуля и единицы)
                PDUT0 = ppg_dut[0][1];      // длительность единицы

                PCNH0_STGR = 1;         //  перезапуск PPG - генерация PPG начинается с генерации "0"-уровня.
                PFRO_PFO0 = 1;          //  подключение PPG к ножке процессора.

                PCSR0 = ppg_dut[0][0];
                PDUT0 = ppg_dut[0][1];
               break;
              //------------
        case 1 :
              //PFRO_PFO1 = 1;
                PCSR1 = ppg_dut[1][1]+s;
                PDUT1 = ppg_dut[1][1];
                PCNH1_STGR = 1;
                PFRO_PFO1 = 1;
                PCSR1 = ppg_dut[1][0];
                PDUT1 = ppg_dut[1][1];

               break;
              //------------
        case 2 :
              //PFRO_PFO2 = 1;
                PCSR2 = ppg_dut[2][1]+s;
                PDUT2 = ppg_dut[2][1];
                PCNH2_STGR = 1;
                PFRO_PFO2 = 1;
                PCSR2 = ppg_dut[2][0];
                PDUT2 = ppg_dut[2][1];
              //  PCNH2_STGR = 1;

               break;
              //------------
        case 3 :
              //PFRO_PFO3 = 1;
                PCSR3 = ppg_dut[3][1]+s;
                PDUT3 = ppg_dut[3][1];
                PCNH3_STGR = 1;
                PFRO_PFO3 = 1;
                PCSR3 = ppg_dut[3][0];
                PDUT3 = ppg_dut[3][1];
              // PCNH3_STGR = 1;

               break;
              //------------
        case 4 :
              //PFRO_PFO4 = 1;
                PCSR4 = ppg_dut[4][1]+s;
                PDUT4 = ppg_dut[4][1];
                PCNH4_STGR = 1;
                PFRO_PFO4 = 1;
                PCSR4 = ppg_dut[4][0];
                PDUT4 = ppg_dut[4][1];
              //  PCNH4_STGR = 1;

               break;
              //------------
        case 5 :
              //PFRO_PFO5 = 1;
                PCSR5 = ppg_dut[5][1]+s;
                PDUT5 = ppg_dut[5][1];
                PCNH5_STGR = 1;
                PFRO_PFO5 = 1;
                PCSR5 = ppg_dut[5][0];
                PDUT5 = ppg_dut[5][1];
               // PCNH5_STGR = 1;

               break;
              //------------
        case 6 :
              //PFRO_PFO6 = 1;
                PCSR6 = ppg_dut[6][1]+s;
                PDUT6 = ppg_dut[6][1];
                PCNH6_STGR = 1;
                PFRO_PFO6 = 1;
                PCSR6 = ppg_dut[6][0];
                PDUT6 = ppg_dut[6][1];
               // PCNH6_STGR = 1;

               break;
              //------------
        case 7 :
              //PFRO_PFO7 = 1;
                PCSR7 = ppg_dut[7][1]+s;
                PDUT7 = ppg_dut[7][1];
                PCNH7_STGR = 1;
                PFRO_PFO7 = 1;
                PCSR7 = ppg_dut[7][0];
                PDUT7 = ppg_dut[7][1];
               // PCNH7_STGR = 1;

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
        case 0 :
                PFRO_PFO0 = 0;
                if ( lev == 1 ) PDRO_PDO0 = 1;
                else PDRO_PDO0 = 0;

               break;
              //------------
        case 1 :
                PFRO_PFO1 = 0;
                if ( lev == 1 ) PDRO_PDO1 = 1;
                else PDRO_PDO1 = 0;
               break;
              //------------
        case 2 :
                PFRO_PFO2 = 0;
                if ( lev == 1 ) PDRO_PDO2 = 1;
                else PDRO_PDO2 = 0;
               break;
              //------------
        case 3 :
                PFRO_PFO3 = 0;
                if ( lev == 1 ) PDRO_PDO3 = 1;
                else PDRO_PDO3 = 0;
               break;
              //------------
        case 4 :
                PFRO_PFO4 = 0;
                if ( lev == 1 ) PDRO_PDO4 = 1;
                else PDRO_PDO4 = 0;
               break;
              //------------
        case 5 :
                PFRO_PFO5 = 0;
                if ( lev == 1 ) PDRO_PDO5 = 1;
                else PDRO_PDO5 = 0;
               break;
              //------------
        case 6 :
                PFRO_PFO6 = 0;
                if ( lev == 1 ) PDRO_PDO6 = 1;
                else PDRO_PDO6 = 0;
               break;
              //------------
        case 7 :
                PFRO_PFO7 = 0;
                if ( lev == 1 ) PDRO_PDO7 = 1;
                else PDRO_PDO7 = 0;
               break;
              //------------
      }

  return ;
}

