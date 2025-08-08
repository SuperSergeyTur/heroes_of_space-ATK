/*-----------------15.08.2012 9:27------------------
 * ��������� ��������� ���������� ��� �������
 * --------------------------------------------------*/

#include "system_LPC177x.h"
//---------------   Clock's   -----------------------------------------------
#define SCS_Val               0x00000025
#define CLKSRCSEL_Val         0x00000001
#define PLL0CFG_Val           0x00000009
#define PLL1CFG_Val           0x00000023
#define CCLKSEL_Val           (0x00000001|(1<<8))
#define USBCLKSEL_Val         (0x00000001|(0x02<<8))
#define EMCCLKSEL_Val         0x00000001
#define PCLKSEL_Val           0x00000002
#define PCONP_Val             (CLKPWR_PCONP_PCRTC | CLKPWR_PCONP_PCGPIO) //0x042887DE
#define CLKOUTCFG_Val         0x00000100
#define FLASHCFG_Val          0x00005000

#ifdef CORE_M4
#define	LPC_CPACR	        0xE000ED88

#define SCB_MVFR0           0xE000EF40
#define SCB_MVFR0_RESET     0x10110021

#define SCB_MVFR1           0xE000EF44
#define SCB_MVFR1_RESET     0x11000011
#endif
//----------------------------------------------------------------------------

/*----------------------------------------------------------------------------
 *  DEFINES
 *----------------------------------------------------------------------------*/
// pll_out_clk = F_cco / (2 x P)
//  F_cco = pll_in_clk x M x 2 x P
#define __M                   ((PLL0CFG_Val & 0x1F) + 1)
#define __PLL0_CLK(__F_IN)    (__F_IN * __M)
#define __CCLK_DIV            (CCLKSEL_Val & 0x1F)
#define __PCLK_DIV			  (PCLKSEL_Val & 0x1F)
#define __ECLK_DIV			  ((EMCCLKSEL_Val & 0x01) + 1)


#if ((CCLKSEL_Val & 0x100) == 0)      // cclk = sysclk
    #if ((CLKSRCSEL_Val & 0x01) == 0)   // sysclk = irc_clk
        #define __CORE_CLK (IRC_OSC / __CCLK_DIV)
		#define __PER_CLK  (IRC_OSC/  __PCLK_DIV)
        #define __EMC_CLK  (IRC_OSC/  __ECLK_DIV)
    #else                               // sysclk = osc_clk
        #define __CORE_CLK (OSC_CLK / __CCLK_DIV)
        #define __PER_CLK  (OSC_CLK/  __PCLK_DIV)
        #define __EMC_CLK  (OSC_CLK/  __ECLK_DIV)
    #endif
#else                                 // cclk = pll_clk
    #if ((CLKSRCSEL_Val & 0x01) == 0)   // sysclk = irc_clk
        #define __CORE_CLK (__PLL0_CLK(IRC_OSC) / __CCLK_DIV)
        #define __PER_CLK  (__PLL0_CLK(IRC_OSC) / __PCLK_DIV)
        #define __EMC_CLK  (__PLL0_CLK(IRC_OSC) / __ECLK_DIV)
    #else                               // ��� ������: sysclk = osc_clk
        #define __CORE_CLK (__PLL0_CLK(OSC_CLK) / __CCLK_DIV)
        #define __PER_CLK  (__PLL0_CLK(OSC_CLK) / __PCLK_DIV)
		#define __EMC_CLK  (__PLL0_CLK(OSC_CLK) / __ECLK_DIV)
    #endif
#endif

/*----------------------------------------------------------------------------
 * Clock Variable definitions
 *----------------------------------------------------------------------------*/
lword SystemCoreClock 	= 	__CORE_CLK;		// System Clock Frequency (Core Clock) 120000000
lword PeripheralClock 	= 	__PER_CLK; 		// Peripheral Clock Frequency (Pclk) 60000000
lword EMCClock		  	= 	__EMC_CLK; 		// EMC Clock Frequency       60000000 
lword USBClock 		  	= 	(48000000UL);   // USB Clock Frequency - this value will be updated after call
											// SystemCoreClockUpdate, should be 48MHz

/*-----------------15.08.2012 9:32------------------
 * ���������� ��������� clock'��
 * --------------------------------------------------*/
void SystemCoreClockUpdate (void)            // Get Core Clock Frequency
{
  // Determine clock frequency according to clock register values
  if ((LPC_SC->CCLKSEL &0x100) == 0) {            // cclk = sysclk
    if ((LPC_SC->CLKSRCSEL & 0x01) == 0) {    // sysclk = irc_clk
          SystemCoreClock = (IRC_OSC / (LPC_SC->CCLKSEL & 0x1F));
          PeripheralClock = (IRC_OSC / (LPC_SC->PCLKSEL & 0x1F));
          EMCClock        = (IRC_OSC / ((LPC_SC->EMCCLKSEL & 0x01)+1));
    }
    else {                                        // sysclk = osc_clk
      if ((LPC_SC->SCS & 0x40) == 0) {
          SystemCoreClock = 0;                      // this should never happen!
          PeripheralClock = 0;
          EMCClock        = 0;
      }
      else {
          SystemCoreClock = (OSC_CLK / (LPC_SC->CCLKSEL & 0x1F));
          PeripheralClock = (OSC_CLK / (LPC_SC->PCLKSEL & 0x1F));
          EMCClock        = (OSC_CLK / ((LPC_SC->EMCCLKSEL & 0x01)+1));
      }
    }
  }
  else {                                          // cclk = pll_clk
    if ((LPC_SC->PLL0STAT & 0x100) == 0) {        // PLL0 not enabled
          SystemCoreClock = 0;                      // this should never happen!
          PeripheralClock = 0;
          EMCClock 		  = 0;
    }
    else {
      if ((LPC_SC->CLKSRCSEL & 0x01) == 0) {    // sysclk = irc_clk
          SystemCoreClock = (IRC_OSC * ((LPC_SC->PLL0STAT & 0x1F) + 1) / (LPC_SC->CCLKSEL & 0x1F));
          PeripheralClock = (IRC_OSC * ((LPC_SC->PLL0STAT & 0x1F) + 1) / (LPC_SC->PCLKSEL & 0x1F));
          EMCClock        = (IRC_OSC * ((LPC_SC->PLL0STAT & 0x1F) + 1) / ((LPC_SC->EMCCLKSEL & 0x01)+1));
      }
      else {                                        // sysclk = osc_clk
        if ((LPC_SC->SCS & 0x40) == 0) {
          SystemCoreClock = 0;                      // this should never happen!
          PeripheralClock = 0;
          EMCClock 		  = 0;
        }
        else {
          SystemCoreClock = (OSC_CLK * ((LPC_SC->PLL0STAT & 0x1F) + 1) / (LPC_SC->CCLKSEL & 0x1F));
          PeripheralClock = (OSC_CLK * ((LPC_SC->PLL0STAT & 0x1F) + 1) / (LPC_SC->PCLKSEL & 0x1F));
          EMCClock        = (OSC_CLK * ((LPC_SC->PLL0STAT & 0x1F) + 1) / ((LPC_SC->EMCCLKSEL & 0x01)+1));
        }
      }
    }
  }
  // ---update USBClock------------------
  if(LPC_SC->USBCLKSEL & (0x01<<8)) //Use PLL0 as the input to the USB clock divider
  {
	  switch (LPC_SC->USBCLKSEL & 0x1F)
	  {
	  case 0:
		  USBClock = 0; //no clock will be provided to the USB subsystem
		  break;
	  case 4:
	  case 6:
		  if(LPC_SC->CLKSRCSEL & 0x01)	//pll_clk_in = main_osc
			  USBClock = (OSC_CLK * ((LPC_SC->PLL0STAT & 0x1F) + 1) / (LPC_SC->USBCLKSEL & 0x1F));
		  else //pll_clk_in = irc_clk
			  USBClock = (IRC_OSC * ((LPC_SC->PLL0STAT & 0x1F) + 1) / (LPC_SC->USBCLKSEL & 0x1F));
		  break;
	  default:
		  USBClock = 0;  // this should never happen!
	  }
  }
  else if(LPC_SC->USBCLKSEL & (0x02<<8)) //usb_input_clk = alt_pll (pll1)
  {
	  if(LPC_SC->CLKSRCSEL & 0x01)	//pll1_clk_in = main_osc
	  		USBClock = (OSC_CLK * ((LPC_SC->PLL1STAT & 0x1F) + 1));
	  else //pll1_clk_in = irc_clk
	  		USBClock = (IRC_OSC * ((LPC_SC->PLL0STAT & 0x1F) + 1));
  }
  else
	  USBClock = 0; // this should never happen!
}

#ifdef CORE_M4

void fpu_init(void)
{
 // from arm trm manual:
//                ; CPACR is located at address 0xE000ED88
//                LDR.W R0, =0xE000ED88
//                ; Read CPACR
//                LDR R1, [R0]
//                ; Set bits 20-23 to enable CP10 and CP11 coprocessors
//                ORR R1, R1, #(0xF << 20)
//                ; Write back the modified value to the CPACR
//                STR R1, [R0]


    volatile uint32_t* regCpacr = (uint32_t*) LPC_CPACR;
    volatile uint32_t* regMvfr0 = (uint32_t*) SCB_MVFR0;
    volatile uint32_t* regMvfr1 = (uint32_t*) SCB_MVFR1;
    volatile uint32_t Cpacr;
    volatile uint32_t Mvfr0;
    volatile uint32_t Mvfr1;
    char vfpPresent = 0;

    Mvfr0 = *regMvfr0;
    Mvfr1 = *regMvfr1;

    vfpPresent = ((SCB_MVFR0_RESET == Mvfr0) && (SCB_MVFR1_RESET == Mvfr1));

    if(vfpPresent)
    {
        Cpacr = *regCpacr;
        Cpacr |= (0xF << 20);
        *regCpacr = Cpacr;   // enable CP10 and CP11 for full access
    }

}
#endif

/*-----------------15.08.2012 9:36------------------
 * ������������� ��������� ��������� ������ ��������� CLK
 * --------------------------------------------------*/
void SystemInit (void)
{
  #ifdef CORE_M4
  fpu_init();
  #endif

  LPC_SC->SCS       = SCS_Val;
  if (SCS_Val & (1 << 5)) {             // If Main Oscillator is enabled
    while ((LPC_SC->SCS & (1<<6)) == 0);// Wait for Oscillator to be ready
  }

  LPC_SC->CLKSRCSEL = CLKSRCSEL_Val;    // Select Clock Source for sysclk/PLL0

// PLL0 setup
  LPC_SC->PLL0CFG   = PLL0CFG_Val;
  LPC_SC->PLL0CON   = 0x01;             // PLL0 Enable
  LPC_SC->PLL0FEED  = 0xAA;
  LPC_SC->PLL0FEED  = 0x55;
  while (!(LPC_SC->PLL0STAT & (1<<10)));// Wait for PLOCK0

// PLL1 setup
  LPC_SC->PLL1CFG   = PLL1CFG_Val;
  LPC_SC->PLL1CON   = 0x01;             // PLL1 Enable
  LPC_SC->PLL1FEED  = 0xAA;
  LPC_SC->PLL1FEED  = 0x55;
  while (!(LPC_SC->PLL1STAT & (1<<10)));// Wait for PLOCK1

// Clock's setup
  LPC_SC->CCLKSEL   = CCLKSEL_Val;      // Setup Clock Divider
  LPC_SC->USBCLKSEL = USBCLKSEL_Val;    // Setup USB Clock Divider
  LPC_SC->EMCCLKSEL = EMCCLKSEL_Val;    // EMC Clock Selection
  LPC_SC->PCLKSEL   = PCLKSEL_Val;      // Peripheral Clock Selection
  LPC_SC->PCONP     = PCONP_Val;        // Power Control for Peripherals
  LPC_SC->CLKOUTCFG = CLKOUTCFG_Val;    // Clock Output Configuration

// Flash Accelerator Setup
  LPC_SC->FLASHCFG  = FLASHCFG_Val|0x03A;

  SCB->VTOR  = 0x00000000 & 0x3FFFFF80;
}
