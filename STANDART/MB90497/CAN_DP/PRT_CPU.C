
void Init_CPU_Ports() {

  __set_il(7);       // маска запросов прерываний - все разрешены

    //   В "DDRx": 1 - выход, 0 - вход.
    //   В "PDRx": начальное значение выходного сигнала - 1 или 0.

// ***** CLOCK *****
  //CKSCR = 0xBB;
/*  CKSCR = 1011 1011 (1111 1100)
 0 bit(CS0) -
 1 bit(CS1) - multiplication rate
              CS1  CS0
               0    0   1xHCLK (4MHz)
               0    1   2xHCLK (8MHz)
               1    0   3xHCLK (12MHz)
               1    1   4xHCLK (16MHz)
 2 bit(MCS) - PLL clock
              0 - PLL clock selected
              1 - main clock selected
 3 bit(SCS) - subclock
              0 - subclock selected
              1 - main clock selected
 4 bit(WS0) -
 5 bit(WS1) - oscillation wait time
              WS1  WS0
               0    0   256 us
               0    1   2.05 ms
               1    0   8.19 ms
               1    1   32.77 ms/65.54 ms
 6 bit(MCM) - PLL clock flag
              0 - operating on the PLL clock
              1 - operating on the main clock
 7 bit(SCM) - subclock flag
              0 - operating on the subclock
              1 - operating on the main or PLL clock
*/

// *****************


// ***** PORT2 - GPIO *****
  HACR = 0xFF; // all PORT - GPIO
/*  HACR = 1111 1111 (0000 0000)
    0 - address output A16-A23
    1 - GPIO P20-P27
*/
  DDR2 = 0x04; // 0000 0100
//DDR: 0 - input; 1 - output
  PDR2 = 0x04; // 0000 0100
// ************************

// ***** PORT3 - GPIO *****
  DDR3 = 0x89; // 1100 1101
//DDR: 0 - input; 1 - output
  PDR3 = 0xFF; // 1111 1111
// ************************

// ***** PORT4 - UART1 *****
//  uart_config(port);
// *************************

// ***** PORT4 - CAN *****
   DDR4 = 0x08; // 0000 1000
   PDR4 = 0x18; // 0001 1000
//  can_config(port);
// ***********************

// ***** PORT4 - GPIO *****
  DDR4 = 0x02; // 0000 0010
  PDR4 = 0x02; // 0000 0010
// ************************

// ***** PORT5 - do not used *****
  ADER = 0; // analog input disable
  DDR5 = 0x00; // 0000 0000
// *******************************

// ***** PORT6 - interrupt *****
//  EIRR = 0; // Interrupt flags clear
//  ENIR = 0x01; // INT0 enable
/*  ENIR = 0000 0001
  bit 0-7(EN0-EN7) - interrupt request enable bits
                     0 - disable
                     1 - enable
*/
//  ELVR_LALB0 = _Interrupt_level;

// *****************************

// ***** PORT6 - GPIO *****
  DDR6 = 0x06; // 0000 0110
  PDR6 = 0x06; // 0000 0110
// ************************

}
