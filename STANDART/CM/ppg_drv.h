#ifndef ppg_FR
#define ppg_FR

void PWM_interrupt (void);

#define _PPG0_Msk       (1<<3)
#define _PPG1_Msk       (1<<5)
#define _PPG2_Msk       (1<<25)
#define _PPG3_Msk       (1<<28)
#define _PPG4_Msk	(1<<0)
#if !defined(_Vozb_KTE) && defined(_CH5_PWM)   
#define _PPG5_Msk       (1<<2)
#else
#define _PPG5_Msk       (1<<22)
#endif
#define _PPG6_Msk       (1<<1)
#define _PPG7_Msk	(1<<3)
#define _PPGD_Msk       (1<<4)

#define _PPG0_IOCON     LPC_IOCON->P1_3
#define _PPG1_IOCON     LPC_IOCON->P1_5
#define _PPG2_IOCON     LPC_IOCON->P1_25
#define _PPG3_IOCON     LPC_IOCON->P1_28
#define _PPG4_IOCON     LPC_IOCON->P2_0
#if !defined(_Vozb_KTE) && defined(_CH5_PWM)   

#define _PPG5_IOCON     LPC_IOCON->P2_2

#else
#define _PPG5_IOCON     LPC_IOCON->P1_22
#endif
#define _PPG6_IOCON     LPC_IOCON->P2_1
#define _PPG7_IOCON     LPC_IOCON->P2_3
#define _DAC_PPG_IOCON  LPC_IOCON->P2_4

#define _PPG0_PIN_EN      D_RESERV | 3
#define _PPG1_PIN_EN      D_RESERV | 3
#define _PPG2_PIN_EN      D_RESERV | 4
#define _PPG3_PIN_EN      D_RESERV | 4
#define _PPG4_PIN_EN      D_RESERV | 1

#if !defined(_Vozb_KTE) && defined(_CH5_PWM)
    #define _PPG5_PIN_EN      D_RESERV | 1
#else
    #define _PPG5_PIN_EN      D_RESERV | 4    
#endif

#define _PPG6_PIN_EN      D_RESERV | 1
#define _PPG7_PIN_EN      D_RESERV | 1
#define _PPGD_PIN_EN      D_RESERV | 1

#define _PPG0_IOPORT      LPC_GPIO1
#define _PPG1_IOPORT      LPC_GPIO1
#define _PPG2_IOPORT      LPC_GPIO1
#define _PPG3_IOPORT      LPC_GPIO1
#define _PPG4_IOPORT      LPC_GPIO2
#if !defined(_Vozb_KTE) && defined(_CH5_PWM)   
#define _PPG5_IOPORT      LPC_GPIO2
#else
#define _PPG5_IOPORT      LPC_GPIO1
#endif 
#define _PPG6_IOPORT      LPC_GPIO2
#define _PPG7_IOPORT      LPC_GPIO2
#define _PPGD_IOPORT      LPC_GPIO2

#define PWM_IR_BITMASK          ((lword)(0x0000073F))

#define _T_PWM_63ns        (d)(0.063)  // 0.063 ìêñ
#define _T_PWM_250ns       (d)(0.25)   // 0.25 ìêñ
#define _T_PWM_1us         (d)(1.0)    // 1 ìêñ
#define _T_PWM_4us         (d)(4.0)    // 4 ìêñ
#define _MCPWM_MkS         (PeripheralClock/1000000)
#define _MCPWM_Timer_Tiks   (_MCPWM_MkS/_MkSec(1))
void  PPG_total_init( LPC_PWM_TypeDef*Chnl,  byte clk, word Per);
void  PPG_init( byte n, byte clk,  byte lev) ;

void  PPG_set( byte n, word low, word high ) ;
void  PPG_start( byte n, byte s ) ;
void  PPG_stop( byte n, byte lev ) ;

//--------------
#ifdef _MAIN_INCLUDE

word ppg_dut[9];
MCPWM_CHANNEL_CFG_Type channelsetup[3];
#else

extern word ppg_dut[];
extern MCPWM_CHANNEL_CFG_Type channelsetup[];
#endif
#endif
