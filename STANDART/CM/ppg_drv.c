
//
//     Инициализация PPG в 16-ти разрядный режим с заданием его
//   номера, делителя базовой частоты и исходного выходного уровня.
//     PPG остается в отключенном состоянии.
//
//  clk:  3 -  4 мкс
//        2 -  1.00 мкс  (16МГц/16)
//        1 -  0.25мкс
//        0 -  0.063мкс

void  PPG_total_init( LPC_PWM_TypeDef*Chnl,  byte clk, word Per)
{
    if (Chnl == LPC_PWM0)
    {
      LPC_SC->PCONP |= CLKPWR_PCONP_PCPWM0;
      MCPWM_Init(LPC_MCPWM);
      LPC_MCPWM->CON_CLR = 0xffffffff;
    }
    else LPC_SC->PCONP |= CLKPWR_PCONP_PCPWM1;

    Chnl->IR   = 0xFF & PWM_IR_BITMASK;
    Chnl->TCR  = 0x00;
    Chnl->CTCR = 0x00;
    Chnl->MCR  = 0x00;
    Chnl->CCR  = 0x00;
    Chnl->PCR  = 0x00;
    Chnl->LER  = 0x00;
    Chnl->TCR  = 0x02; //reset counters
    switch ( clk )
    {
        case 0 :
            Chnl->PR   = ((lword)((d)PeripheralClock * _T_PWM_63ns ) / 1000000) - 1;
            break;
        case 1 :
            Chnl->PR   = ((lword)((d)PeripheralClock * _T_PWM_250ns ) / 1000000) - 1;
            break;
        case 2 :
            Chnl->PR   = ((lword)((d)PeripheralClock * _T_PWM_1us ) / 1000000) - 1;
            break;
        case 3 :
            Chnl->PR   = ((lword)((d)PeripheralClock * _T_PWM_4us ) / 1000000) - 1;
            break;
    }
    Chnl->MR0 = Per;
    Chnl->MCR  = 0x02; //reset couners if match MR0
    if (Chnl == LPC_PWM0)
    {
        Chnl->PCR  |= 0x6c6c; //double edge, outputs 2,3,5,6 enable - SUM
        Chnl->TCR  = 0x01; //count enable
    }
    else
    {
        Chnl->PCR  |= 0x7e00; //single edge, outputs 1-6 enable - DAC
        Chnl->TCR  = 0x09; //count enable
        Chnl->LER  = 0x01;
    }

}

void  PPG_init( byte n, byte clk,  byte lev)
{

  switch ( n )
  {
        case 0 :
            _PPG0_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPG0_IOPORT->SET |= _PPG0_Msk;
            else            _PPG0_IOPORT->CLR |= _PPG0_Msk;
            break;
              //------------
        case 1 :
            _PPG1_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPG1_IOPORT->SET |= _PPG1_Msk;
            else            _PPG1_IOPORT->CLR |= _PPG1_Msk;
            break;
              //------------
        case 2 :
          //MC_1A Ч Motor control PWM channel 1, output A.(P1.25)
          //МСPWM DC mode
           channelsetup[1].channelType = MCPWM_CHANNEL_EDGE_MODE;
           channelsetup[1].channelDeadtimeEnable = DISABLE;
           channelsetup[1].channelDeadtimeValue = 0;
           channelsetup[1].channelUpdateEnable = ENABLE;
           channelsetup[1].channelTimercounterValue = 0;
           channelsetup[1].channelPulsewidthValue = 0;
           channelsetup[1].channelPeriodValue = 0;//Per*channelsetup[1].channelClkValue;
           switch ( clk )
           {
               case 0 :
                   channelsetup[1].channelClkValue   = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_63ns);
                   break;
               case 1 :
                   channelsetup[1].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_250ns);
                   break;
               case 2 :
                   channelsetup[1].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_1us);
                   break;
               case 3 :
                   channelsetup[1].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_4us);
                   break;
           }
           if (lev == 1)
           {
            channelsetup[1].channelPolarity = MCPWM_CHANNEL_PASSIVE_HI;
            _PPG2_IOPORT->SET = _PPG2_Msk;
           }
           else
           {
            channelsetup[1].channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
            _PPG2_IOPORT->CLR = _PPG2_Msk;
           }
           MCPWM_ConfigChannel(LPC_MCPWM, MCPWM_CHANNEL_1, &channelsetup[1]);
           break;
      case 3 :
          // MC_2A Ч Motor control PWM channel 2, output A.(P1.28)
          channelsetup[2].channelType = MCPWM_CHANNEL_EDGE_MODE;
          channelsetup[2].channelDeadtimeEnable = DISABLE;
          channelsetup[2].channelDeadtimeValue = 0;
          channelsetup[2].channelUpdateEnable = ENABLE;
          channelsetup[2].channelTimercounterValue = 0;
          channelsetup[2].channelPulsewidthValue = 0;
          channelsetup[2].channelPeriodValue = 0;//Per*channelsetup[2].channelClkValue;
          switch ( clk )
           {
               case 0 :
                   channelsetup[2].channelClkValue   = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_63ns);
                   break;
               case 1 :
                   channelsetup[2].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_250ns);
                   break;
               case 2 :
                   channelsetup[2].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_1us);
                   break;
               case 3 :
                   channelsetup[2].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_4us);
                   break;
           }
          if (lev == 1)
          {
            channelsetup[2].channelPolarity = MCPWM_CHANNEL_PASSIVE_HI;
            _PPG3_IOPORT->SET = _PPG3_Msk;
          }
          else
          {
            channelsetup[2].channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
            _PPG3_IOPORT->CLR = _PPG3_Msk;
          }
          MCPWM_ConfigChannel(LPC_MCPWM, MCPWM_CHANNEL_2, &channelsetup[2]);
          break;
              //------------
        case 4 :
            _PPG4_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPG4_IOPORT->SET = _PPG4_Msk;
            else            _PPG4_IOPORT->CLR = _PPG4_Msk;
            break;
              //------------
        case 5 :
#if !defined(_Vozb_KTE) && defined(_CH5_PWM)
            _PPG5_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPG5_IOPORT->SET = _PPG5_Msk;
            else            _PPG5_IOPORT->CLR = _PPG5_Msk;
#else
        //MC_0B Ч Motor control PWM channel 0, output B.(P1.22)
          channelsetup[0].channelType = MCPWM_CHANNEL_EDGE_MODE;
          channelsetup[0].channelDeadtimeEnable = DISABLE;
          channelsetup[0].channelDeadtimeValue = 0;
          channelsetup[0].channelUpdateEnable = ENABLE;
          channelsetup[0].channelTimercounterValue = 0;
          channelsetup[0].channelPulsewidthValue = 0;
          channelsetup[0].channelPeriodValue = 0;//Per*channelsetup[0].channelClkValue;
          switch ( clk )
           {
               case 0 :
                   channelsetup[0].channelClkValue   = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_63ns);
                   break;
               case 1 :
                   channelsetup[0].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_250ns);
                   break;
               case 2 :
                   channelsetup[0].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_1us);
                   break;
               case 3 :
                   channelsetup[0].channelClkValue  = (lword)((d)_MCPWM_Timer_Tiks * _T_PWM_4us);
                   break;
           }
          if (lev == 1)
          {
            channelsetup[0].channelPolarity = MCPWM_CHANNEL_PASSIVE_HI;
            _PPG5_IOPORT->SET = _PPG5_Msk;
          }
          else
          {
            channelsetup[0].channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;
            _PPG5_IOPORT->CLR = _PPG5_Msk;
          }
          MCPWM_ConfigChannel(LPC_MCPWM, MCPWM_CHANNEL_0, &channelsetup[0]);
          //PINSEL_ConfigPin (1, 22, 4);
#endif
            break;
              //------------
        case 6 :
            _PPG6_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPG6_IOPORT->SET = _PPG6_Msk;
            else            _PPG6_IOPORT->CLR = _PPG6_Msk;
            break;
              //------------
        case 7 :
            _PPG7_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPG7_IOPORT->SET = _PPG7_Msk;
            else            _PPG7_IOPORT->CLR = _PPG7_Msk;
            break;
              //------------
        case 8 :
            _DAC_PPG_IOCON  = D_RESERV | 0;
            if ( lev == 1 ) _PPGD_IOPORT->SET = _PPGD_Msk;
            else            _PPGD_IOPORT->CLR = _PPGD_Msk;
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
      word ax, bx;
      switch ( n )
      {
        case 0 :
                bx = LPC_PWM0->TC+1;
                if ( bx > LPC_PWM0->MR0) bx = 0;
                ax = bx+ppg_dut[0];
                if ( ax > LPC_PWM0->MR0) ax -= LPC_PWM0->MR0;
                LPC_PWM0->MR1 = bx;
                LPC_PWM0->MR2 = ax;
                _PPG0_IOCON = _PPG0_PIN_EN;       // SUM0
                break;
              //------------
        case 1 :
                bx = LPC_PWM0->TC+1;
                if ( bx > LPC_PWM0->MR0) bx = 0;
                ax = bx+ppg_dut[1];
                if ( ax > LPC_PWM0->MR0) ax -= LPC_PWM0->MR0;
                LPC_PWM0->MR2 = bx;
                LPC_PWM0->MR3 = ax;
                _PPG1_IOCON = _PPG1_PIN_EN;       // SUM1
                break;
              //------------
        case 2 :
          //MC_1A Ч Motor control PWM channel 1, output A.(P1.25)
          MCPWM_Stop(LPC_MCPWM, DISABLE, ENABLE , DISABLE);
          ax =channelsetup[1].channelPulsewidthValue - s*channelsetup[1].channelClkValue;
          if ((sw)ax < 0)
          {
             ax = 0;
          }
          LPC_MCPWM->TC1 = ax;
          MCPWM_Start(LPC_MCPWM, DISABLE, ENABLE,DISABLE  );
          _PPG2_IOCON = _PPG2_PIN_EN;
          break;
        case 3 :
          // MC_2A Ч Motor control PWM channel 2, output A.(P1.28)
          MCPWM_Stop(LPC_MCPWM, DISABLE, DISABLE, ENABLE);
          ax =channelsetup[2].channelPulsewidthValue - s*channelsetup[2].channelClkValue;
          if ((sw)ax < 0)
          {
            ax = 0;
          }
          LPC_MCPWM->TC2 = ax;
          //LPC_MCPWM->CP |= MCPWM_PATENT_A2;
          MCPWM_Start(LPC_MCPWM, DISABLE, DISABLE, ENABLE);
          _PPG3_IOCON = _PPG3_PIN_EN;
          break;
          //------------
        case 4 :
                _PPG4_IOCON = _PPG4_PIN_EN;       // DAC
                break;
              //------------
        case 5 :
#if defined(_Vozb_KTE) || !defined(_CH5_PWM)
        //MC_0B Ч Motor control PWM channel 0, output B.(P1.22)

               MCPWM_Stop(LPC_MCPWM, ENABLE, DISABLE,DISABLE );
               ax =channelsetup[0].channelPulsewidthValue - s*channelsetup[0].channelClkValue;
               if ((sw)ax < 0)
               {
                 ax = 0;
               }
               LPC_MCPWM->TC0= ax;
               MCPWM_Start(LPC_MCPWM, ENABLE, DISABLE,DISABLE );
#endif
                 _PPG5_IOCON = _PPG5_PIN_EN;
                break;
              //------------
        case 6 :
                _PPG6_IOCON = _PPG6_PIN_EN;       // DAC
                break;
              //------------
        case 7 :
                _PPG7_IOCON = _PPG7_PIN_EN;       // DAC
                break;
              //------------
        case 8 :
                _DAC_PPG_IOCON = _PPGD_PIN_EN;       // DAC
                break;
              //------------
      }

  return ;
}

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
                LPC_PWM0->MR0 = high+low;
                bx = LPC_PWM0->TC;
                if ( bx > LPC_PWM0->MR0) bx = 0, LPC_PWM0->TC = 0;
                ax = bx+high;
                if ( ax > LPC_PWM0->MR0) ax -= LPC_PWM0->MR0;
                LPC_PWM0->MR1 = bx;
                LPC_PWM0->MR2 = ax;
                ppg_dut[0] = high;
               break;
              //------------
        case 1 :
                LPC_PWM0->MR0 = high+low;
                bx = LPC_PWM0->TC;
                if ( bx > LPC_PWM0->MR0) bx = 0, LPC_PWM0->TC = 0;
                ax = bx+high;
                if ( ax > LPC_PWM0->MR0) ax -= LPC_PWM0->MR0;
                LPC_PWM0->MR2 = bx;
                LPC_PWM0->MR3 = ax;
                ppg_dut[1] = high;
               break;
              //------------
        case 2 :
          //MC_1A Ч Motor control PWM channel 1, output A.(P1.25)
          //В канале А от 0 до МАTH идет passive, а потом до LIM  идет active
          //В канале В наоборот, по этому в значение channelPulsewidthValue 
          //записываем low для канала А, а high - для канала В
          channelsetup[1].channelPeriodValue = (high+low)*channelsetup[1].channelClkValue;
          if (channelsetup[1].channelPolarity == MCPWM_CHANNEL_PASSIVE_LO)
          {
            channelsetup[1].channelPulsewidthValue = high*channelsetup[1].channelClkValue;
          }
          else
          {
            channelsetup[1].channelPulsewidthValue = low*channelsetup[1].channelClkValue;
          }
          MCPWM_WriteToShadow(LPC_MCPWM, MCPWM_CHANNEL_1, &channelsetup[1]);
               break;
              //------------
        case 3 :
          // MC_2A Ч Motor control PWM channel 2, output A.(P1.28)
          //В канале А от 0 до МАTH идет passive, а потом до LIM  идет active
          //В канале В наоборот, по этому в значение channelPulsewidthValue 
          //записываем low для канала А, а high - для канала В
          channelsetup[2].channelPeriodValue = (high+low)*channelsetup[2].channelClkValue;
          if (channelsetup[2].channelPolarity == MCPWM_CHANNEL_PASSIVE_LO)
          {
            channelsetup[2].channelPulsewidthValue = high*channelsetup[2].channelClkValue;
          }
          else
          {
            channelsetup[2].channelPulsewidthValue = low*channelsetup[2].channelClkValue;
          }
          MCPWM_WriteToShadow(LPC_MCPWM, MCPWM_CHANNEL_2, &channelsetup[2]);
              break;
              //------------
        case 4 :
                LPC_PWM1->MR0 = high+low;
                LPC_PWM1->MR1 = low;
                LPC_PWM1->LER  = 0x03;
               break;
              //------------
        case 5 :
#if !defined(_Vozb_KTE) && defined(_CH5_PWM)
                LPC_PWM1->MR0 = high+low;
                LPC_PWM1->MR3 = low;
                LPC_PWM1->LER  = 0x09;
#else
        //MC_0B Ч Motor control PWM channel 0, output B.(P1.22)
          //В канале А от 0 до МАTH идет passive, а потом до LIM  идет active
          //В канале В наоборот, по этому в значение channelPulsewidthValue 
          //записываем low для канала А, а high - для канала В
          channelsetup[0].channelPeriodValue = (high+low)*channelsetup[0].channelClkValue;
          if (channelsetup[0].channelPolarity == MCPWM_CHANNEL_PASSIVE_LO)
          {
            channelsetup[0].channelPulsewidthValue = high*channelsetup[0].channelClkValue;
          }
          else
          {
            channelsetup[0].channelPulsewidthValue = low*channelsetup[0].channelClkValue;
          }
          MCPWM_WriteToShadow(LPC_MCPWM, MCPWM_CHANNEL_0, &channelsetup[0]);

#endif
               break;
              //------------
        case 6 :
                LPC_PWM1->MR0 = high+low;
                LPC_PWM1->MR2 = low;
                LPC_PWM1->LER  = 0x05;
               break;
              //------------
        case 7 :
                LPC_PWM1->MR0 = high+low;
                LPC_PWM1->MR4 = low;
                LPC_PWM1->LER  = 0x11;
               break;
              //------------
        case 8 :
                LPC_PWM1->MR0 = high+low;
                LPC_PWM1->MR5 = low;
                LPC_PWM1->LER  = 0x21;
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
  //lword lax;
      switch ( n )
      {
        case 0 :
                _PPG0_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG0_IOPORT->SET = _PPG0_Msk;
                else            _PPG0_IOPORT->CLR = _PPG0_Msk;
                break;
              //------------
        case 1 :
                _PPG1_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG1_IOPORT->SET = _PPG1_Msk;
                else            _PPG1_IOPORT->CLR = _PPG1_Msk;
                break;
              //------------
        case 2 :
                //MC_1A Ч Motor control PWM channel 1, output A.(P1.25)
                MCPWM_Stop(LPC_MCPWM, DISABLE,ENABLE,DISABLE);
                _PPG2_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG2_IOPORT->SET = _PPG2_Msk;
                else            _PPG2_IOPORT->CLR = _PPG2_Msk;
                break;
              //------------
        case 3 :
                // MC_2A Ч Motor control PWM channel 2, output A.(P1.28)
                MCPWM_Stop(LPC_MCPWM, DISABLE,DISABLE,ENABLE);
                _PPG3_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG3_IOPORT->SET = _PPG3_Msk;
                else            _PPG3_IOPORT->CLR = _PPG3_Msk;
                break;
              //------------
        case 4 :
                _PPG4_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG4_IOPORT->SET = _PPG4_Msk;
                else            _PPG4_IOPORT->CLR = _PPG4_Msk;
                break;
              //------------
        case 5 :
#if defined(_Vozb_KTE) || !defined(_CH5_PWM)
               //MC_0B Ч Motor control PWM channel 0, output B.(P1.22)
                MCPWM_Stop(LPC_MCPWM, ENABLE,DISABLE,DISABLE);
#endif
                _PPG5_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG5_IOPORT->SET = _PPG5_Msk;
                else            _PPG5_IOPORT->CLR = _PPG5_Msk;
                break;
              //------------
        case 6 :
                _PPG6_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG6_IOPORT->SET = _PPG6_Msk;
                else            _PPG6_IOPORT->CLR = _PPG6_Msk;
                break;
              //------------
        case 7 :
                _PPG7_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPG7_IOPORT->SET = _PPG7_Msk;
                else            _PPG7_IOPORT->CLR = _PPG7_Msk;
                break;
              //------------
        case 8 :
                _DAC_PPG_IOCON = D_RESERV ;
                if ( lev == 1 ) _PPGD_IOPORT->SET = _PPGD_Msk;
                else            _PPGD_IOPORT->CLR = _PPGD_Msk;
                break;
              //------------
      }

  return ;
}

