//#include "timer.h"

/*-----------------15.08.2012 11:06-----------------
 * Инициализация таймеров
 * --------------------------------------------------*/
//void SysTimer_Init( void )
void Init_timer( void )
{
  word i;
  LPC_TIM_TypeDef       *Timer_def[4]= {
                                         LPC_TIM0,
                                         LPC_TIM1,
                                         LPC_TIM2,
                                         LPC_TIM3
                                        };

  LPC_SC->PCONP |= CLKPWR_PCONP_PCTIM0|CLKPWR_PCONP_PCTIM1|CLKPWR_PCONP_PCTIM2|CLKPWR_PCONP_PCTIM3;
  LPC_SC->PCONP |= CLKPWR_PCONP_PCTIM0;
  //Включаем пины как функциональные
#ifndef P_CH
  PINSEL_ConfigPin (1, 10, 3);
  PINSEL_ConfigPin (1, 18, 3);
  PINSEL_ConfigPin (1, 19, 3);
  PINSEL_ConfigPin (1, 26, 3);
#endif
//  LPC_IOCON->P1_10 = D_RESERV | D_HYS_EN | 0x3;
//  LPC_IOCON->P1_18 = D_RESERV | D_HYS_EN | 0x3;
//  LPC_IOCON->P1_19 = D_RESERV | D_HYS_EN | 0x3;
//  LPC_IOCON->P1_26 = D_RESERV | D_HYS_EN | 0x3;

  for (i= 0; i<=3;++i)
  {
    Timer_def[i]->CTCR = 0;
    Timer_def[i]->TC =0;
    Timer_def[i]->PC =0;
    Timer_def[i]->PR =0;
    Timer_def[i]->CCR = 0;
    //Сброс таймера
    Timer_def[i]->TCR |= 0x2;
    Timer_def[i]->TCR &= ~0x2;

    //Дискрета - 1 мкс: частота PCLK/60
    Timer_def[i]->PR = 59;
  }
  //Настройка общего таймера timer1

  //С чем сраниваться будет значение таймера?
  LPC_TIM0->MR0 = 0xffff;
  LPC_TIM1->MR0 = 0xffff;
  LPC_TIM2->MR0 = 0xffff;
  LPC_TIM3->MR0 = 0xffff;
  //Регистр обнуляется и выдает прерывание
  //делаем все таймеры 16-ти разрядными
  LPC_TIM0->MCR = 3;
  LPC_TIM1->MCR = 2;
  LPC_TIM2->MCR = 2;
  LPC_TIM3->MCR = 0;

  LPC_TIM0->EMR = 0;
  LPC_TIM1->EMR = 0;
  LPC_TIM2->EMR = 0;
  LPC_TIM3->EMR = 0;
//Очищаем запросы прерываний
  LPC_TIM0->IR = 0xffffffff;
  LPC_TIM1->IR = 0xffffffff;
  LPC_TIM2->IR = 0xffffffff;
  LPC_TIM3->IR = 0xffffffff;

  NVIC_SetPriority(TIMER0_IRQn, _TIMER0_IRQ_PRIORITY );
  NVIC_EnableIRQ(TIMER0_IRQn);
  //Включаем таймеры
  LPC_TIM0->TCR |= 0x1;
  LPC_TIM1->TCR |= 0x1;
  LPC_TIM2->TCR |= 0x1;
  LPC_TIM3->TCR |= 0x1;


   Timer1_Ovr = 0;
   Count_SymbolPauza = _SymbolPauza ;
}

/*-----------------15.08.2012 11:21-----------------
 * Прерывание системного таймера
 * --------------------------------------------------*/
extern "C" {
void TIMER0_IRQHandler (void)
{
  //mUSEL_clr();
  
  Timer1_Ovr++;
  LPC_TIM0->IR = 0xffffffff;
  
  if ( Mon.UartCAN_Connect == 0 )
  {
    if ( Mon.Pult == 1 )
    {
      if ( --Count_SymbolPauza == 0 )  // отсчет паузы между символами
      {
        Count_SymbolPauza = _SymbolPauza ;
        if ( ((OutTxBuffCount + 1) & TxBuffSize) != InTxBuffCount )
        {
          OutTxBuffCount = ( OutTxBuffCount + 1 ) & TxBuffSize ;
          LPC_UART0->THR = TxBuff[(w)OutTxBuffCount] ;
        }
      }
    }
    
  } 
  //На случай когда прерывание пришло, а таймер еще не обнулился(может влиять на Timer1_fSec)
  while (timer1 > 0xfffe);  
  
}

void TIMER1_IRQHandler(void )
{
  //word ax = LPC_TIM1->IR&0x3f;
  //  перенесено снизу 27.05.2019 14:27   KVV:
  //  затираются запросы прерывания возникшие в регистре пока будут обработаны все подпрограммы
  //LPC_TIM1->IR = 0xffffffff;
  if ((LPC_TIM1->IR&0x1) != 0)
  {
     T1_MR0_Int();
  }
  if ((LPC_TIM1->IR&0x2) != 0)
  {
     T1_MR1_Int();

  }
  if ((LPC_TIM1->IR&0x4) != 0)
  {
     T1_MR2_Int();

  }
  if ((LPC_TIM1->IR&0x8) != 0)
  {
     T1_MR3_Int();

  }
  if ((LPC_TIM1->IR&0x10) != 0)
  {
     T1_CR0_Int();

  }
  if ((LPC_TIM1->IR&0x20) != 0)
  {
     T1_CR1_Int();
  }
  //LPC_TIM1->IR = 0xffffffff;
  return ;
}

void TIMER2_IRQHandler(void )
{

  //asm_di(TIMER2_IRQn);
//  asm_di();
//   word ax = LPC_TIM2->IR&0x3f;
    //  перенесено снизу 27.05.2019 14:27   KVV  снимались ИУ возб - подозрение на потерю запросов прерываний
    //  помогло
    //LPC_TIM2->IR = 0xffffffff;
 // asm_ei();

  if ((LPC_TIM2->IR&0x8) != 0)
  {
     T2_MR3_Int();

  }
  if ((LPC_TIM2->IR&0x1) != 0)
  {
     T2_MR0_Int();
  }
  if ((LPC_TIM2->IR&0x2) != 0)
  {
     T2_MR1_Int();

  }
  if ((LPC_TIM2->IR&0x4) != 0)
  {
     T2_MR2_Int();

  }
  if ((LPC_TIM2->IR&0x10) != 0)
  {
     T2_CR0_Int();

  }
  if ((LPC_TIM2->IR&0x20) != 0)
  {
     T2_CR1_Int();
  }
  //  27.05.2019 14:27   KVV  снимались ИУ возб - подозрение на потерю запросов прерываний LPC_TIM2->IR = 0xffffffff;
  //asm_ei(TIMER2_IRQn);
  //asm_ei();
  return ;

}

void TIMER3_IRQHandler(void )
{
 // word ax = LPC_TIM3->IR&0x3f;
  //  перенесено снизу 27.05.2019 14:27   KVV:
  //  затираются запросы прерывания возникшие в регистре пока будут обработаны все подпрограммы
 // LPC_TIM3->IR = 0xffffffff;

  if ((LPC_TIM3->IR&0x1) != 0)
  {
     T3_MR0_Int();
  }
  if ((LPC_TIM3->IR&0x2) != 0)
  {
     T3_MR1_Int();

  }
  if ((LPC_TIM3->IR&0x4) != 0)
  {
     T3_MR2_Int();

  }
  if ((LPC_TIM3->IR&0x8) != 0)
  {
     T3_MR3_Int();

  }
  if ((LPC_TIM3->IR&0x10) != 0)
  {
     T3_CR0_Int();

  }
  if ((LPC_TIM3->IR&0x20) != 0)
  {
     T3_CR1_Int();
  }
  //LPC_TIM3->IR = 0xffffffff;
  return ;
}
}//extern "C"
