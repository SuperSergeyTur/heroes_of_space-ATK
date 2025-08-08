
      //   ���� ���� ��������� capture-EPA ��� �����-�� ������������.
      //  �� ������� �������� � ���� ���� ����� ������� �� ����� ������ �
      //  ���������������� �����������.

//� IR �������, ��� ������ �������, �������� ���������� ���������� ����� =, � �� ����� |=
// ������ 1 � ��������������� ��� �������� � ������ ���������������� ����������,
//������ 0 �� � ���� �� ��������, ����� ���������� ���������� ����� |= �� ������� ���������
//�������� �� ����� ������������� � ��� ������������, � ���� ���������, ��, ��� ���� ��������
//(� � �������� ���� ��� � ��� 1) � ���������� ��� �������� � 1 �� ���� �������� ����� � �������.
//��� �������� � ������ ���� �������������� �������� �� ����������.

      //   ��������� ��������� ������ capture-EPA ��� �����
      //  �������������.
word init_syn_epa( word channel )
{
  if      ( channel == _ICS0 )  //timer3 , CAP0 (cap0 �� �����)
  {
	 LPC_TIM3->CCR &= 0xF8 ;
   //LPC_TIM3->CR0  = 0;
	 LPC_TIM3->CCR |= _CAP0_NEG_EDGE;
  }
  else if ( channel == _ICS1 )  //timer0 , CAP0 (cap1 �� �����)
  {
     LPC_TIM0->CCR &= 0xF8 ;
   //LPC_TIM0->CR0  = 0;
     LPC_TIM0->CCR |= _CAP1_NEG_EDGE;
  }
  else if ( channel == _ICS2 )  //timer1 , CAP0 (cap2 �� �����)
  {
     LPC_TIM1->CCR &= 0xF8 ;
   //LPC_TIM1->CR0  = 0;
     LPC_TIM1->CCR |= _CAP2_NEG_EDGE;
  }
  else if ( channel == _ICS3 )  //timer1 , CAP1 (cap3 �� �����)
  {
     LPC_TIM1->CCR &= 0x07 ;
   //LPC_TIM1->CR1  = 0;
     LPC_TIM1->CCR |= _CAP3_NEG_EDGE;
  }
  else if ( channel == _ICS4 )  //timer2 , CAP0 ( ������������� � �� �� ����� )
  {
     LPC_TIM2->CCR &= 0xf8 ;

     LPC_TIM2->CCR |= _CAP4_NEG_EDGE;
  }
  return 0 ;
}

      //   ���������� ���������� �� ���.
void ei_syn_epa( word channel )
{
  if( channel == _ICS0 )  // timer3 , CAP0 (cap0 �� �����)
  {   // ���������� ������ �� ���
     LPC_TIM3->IR = 0x10 ;
      // ��������� ���������� ���.
     LPC_TIM3->CCR |= 0x04 ;

     NVIC_SetPriority( TIMER3_IRQn, _ICS0_PRIORITY);
     NVIC_EnableIRQ( TIMER3_IRQn );

  }
  else if( channel == _ICS1 )   //timer0, CAP0 (cap1 �� �����)
  {   // ���������� ������ �� ���
     LPC_TIM0->IR = 0x10 ;
      // ��������� ���������� ���.
     LPC_TIM0->CCR |= 0x04 ;

     NVIC_SetPriority( TIMER0_IRQn, _ICS1_PRIORITY);
     NVIC_EnableIRQ( TIMER0_IRQn );
  }
  else if( channel == _ICS2 )   // timer1 , CAP0   (cap2 �� �����)
  {   // ���������� ������ �� ���
     LPC_TIM1->IR = 0x10 ;
      // ��������� ���������� ���.
     LPC_TIM1->CCR |= 0x04 ;
     NVIC_SetPriority( TIMER1_IRQn, _ICS23_PRIORITY);
     NVIC_EnableIRQ( TIMER1_IRQn );
  }
  else if( channel == _ICS3 )  // timer1 , CAP1 (cap3 �� �����)
  {   // ���������� ������ �� ���
     LPC_TIM1->IR = 0x20 ;
      // ��������� ���������� ���.
     LPC_TIM1->CCR |= 0x20 ;

     NVIC_SetPriority( TIMER1_IRQn, _ICS23_PRIORITY);
     NVIC_EnableIRQ( TIMER1_IRQn );
  }
  else if( channel == _ICS4 )  // timer2 , CAP0 (������������� ��)
  {   // ���������� ������ �� ���
     LPC_TIM2->IR = 0x10 ;
      // ��������� ���������� ���.
     LPC_TIM2->CCR |= 0x04 ;

     NVIC_SetPriority( TIMER2_IRQn, _ICS23_PRIORITY);
     NVIC_EnableIRQ( TIMER2_IRQn );
  }
  //asm_ei();

  return ;
}
            // ����� ������� ����������.
void Syn_int_drv( word channel )//, word code )
{
      // ���������� ������ �� ���
  if     ( channel == _ICS0 )  LPC_TIM3->IR = 0x10 ;
  else if( channel == _ICS1 )  LPC_TIM0->IR = 0x10 ;
  else if( channel == _ICS2 )  LPC_TIM1->IR = 0x10 ;
  else if( channel == _ICS3 )  LPC_TIM1->IR = 0x20 ;
  else if( channel == _ICS4 )  LPC_TIM2->IR = 0x10 ;
  return ;
}


      //   ��������� ��������� ������ compare-EPA ��� C���.
word init_sifu_epa( word channel )
{
 // LPC_TIM0->TCR = 0;
    if ( channel == _OCS0 )
        {                   //  Timer3 , MR1 .
            LPC_TIM3->MCR &= 0x0FC7;
            LPC_TIM3->MCR |= 0x0008;
            LPC_TIM3->IR  = 0x02;
            NVIC_SetPriority( TIMER3_IRQn, _OCS2_PRIORITY);
            NVIC_EnableIRQ( TIMER3_IRQn );
        }
    else if ( channel == _OCS1 )
        {                   //  Timer1 , MR1 .
            LPC_TIM1->MCR &= 0x0FC7;
            LPC_TIM1->MCR |= 0x0008;
            LPC_TIM1->IR  = 0x02;
            NVIC_SetPriority( TIMER1_IRQn, _OCS1_PRIORITY);
            NVIC_EnableIRQ( TIMER1_IRQn );
        }
    else if ( channel == _OCS2 )
        {                   //  Timer1 , MR2 .
            LPC_TIM1->MCR &= 0x0E3F;
            LPC_TIM1->MCR |= 0x0040;
            LPC_TIM1->IR  = 0x04;
            NVIC_SetPriority( TIMER1_IRQn, _OCS1_PRIORITY);
            NVIC_EnableIRQ( TIMER1_IRQn );
        }
    else if( channel == _OCS3 )
        {                   //  Timer1 , MR3 .
            LPC_TIM1->MCR &= 0x01FF;
            LPC_TIM1->MCR |= 0x0200;
            LPC_TIM1->IR  = 0x08;
            NVIC_SetPriority( TIMER1_IRQn, _OCS1_PRIORITY);
            NVIC_EnableIRQ( TIMER1_IRQn );
        }
    else if ( channel == _OCS4 )
        {                   //  Timer2 , MR2 .
            LPC_TIM2->MCR &= 0x0E3F;
            LPC_TIM2->MCR |= 0x0040;
            LPC_TIM2->IR  = 0x04;
            NVIC_SetPriority( TIMER2_IRQn, _OCS2_PRIORITY);
            NVIC_EnableIRQ( TIMER2_IRQn );
        }
    else if( channel == _OCS5 )
        {                   //  Timer2 , MR3 .
            LPC_TIM2->MCR &= 0x01FF;
            LPC_TIM2->MCR |= 0x0200;
            LPC_TIM2->IR  = 0x08;
            NVIC_SetPriority( TIMER2_IRQn, _OCS2_PRIORITY);
            NVIC_EnableIRQ( TIMER2_IRQn );
        }
  return 0 ;
}

// ���������� ���������� , ���� ��� ���� ������������������� .
word off_sifu_epa( word channel )
{
    if ( channel == _OCS0 )
        {                   //  Timer3 , MR1 .
            LPC_TIM3->MCR &= 0x0FC7;
            LPC_TIM3->IR  = 0x02;
        }
    else if ( channel == _OCS1 )
        {                   //  Timer1 , MR1 .
            LPC_TIM1->MCR &= 0x0FC7;
            LPC_TIM1->IR  = 0x02;
        }
    else if ( channel == _OCS2 )
        {                   //  Timer1 , MR2 .
            LPC_TIM1->MCR &= 0x0E3F;
            LPC_TIM1->IR  = 0x04;
        }
    else if( channel == _OCS3 )
        {                   //  Timer1 , MR3 .
            LPC_TIM1->MCR &= 0x01FF;
            LPC_TIM1->IR  = 0x08;
        }
    else if ( channel == _OCS4 )
        {                   //  Timer2 , MR2 .
            LPC_TIM2->MCR &= 0x0E3F;
            LPC_TIM2->IR  = 0x04;
        }
    else if( channel == _OCS5 )
        {                   //  Timer2 , MR3 .
            LPC_TIM2->MCR &= 0x01FF;
            LPC_TIM2->IR  = 0x08;
        }
  return 0 ;
}

// ��������� ���������� , ���� ��� ���� ��������� .
word on_sifu_epa( word channel )
{
    if ( channel == _OCS0 )
        {                   //  Timer3 , MR1 .
            LPC_TIM3->MCR |= 0x0008;
            LPC_TIM3->IR  = 0x02;
        }
    else if ( channel == _OCS1 )
        {                   //  Timer1 , MR1 .
            LPC_TIM1->MCR |= 0x0008;
            LPC_TIM1->IR  = 0x02;
        }
    else if ( channel == _OCS2 )
        {                   //  Timer1 , MR2 .
            LPC_TIM1->MCR |= 0x0040;
            LPC_TIM1->IR  = 0x04;
        }
    else if( channel == _OCS3 )
        {                   //  Timer1 , MR3 .
            LPC_TIM1->MCR |= 0x0200;
            LPC_TIM1->IR  = 0x08;
        }
    else if ( channel == _OCS4 )
        {                   //  Timer2 , MR2 .
            LPC_TIM2->MCR |= 0x0040;
            LPC_TIM2->IR  = 0x04;
        }
    else if( channel == _OCS5 )
        {                   //  Timer2 , MR3 .
            LPC_TIM2->MCR |= 0x0200;
            LPC_TIM2->IR  = 0x08;
        }
  return 0 ;
}

            // ����� ������� ����������.
void Sifu_int_drv( word channel )
{
      // ���������� ������ �� ���
  if     ( channel == _OCS0 )  LPC_TIM3->IR  = 0x02;
  else if( channel == _OCS1 )  LPC_TIM1->IR  = 0x02;
  else if( channel == _OCS2 )  LPC_TIM1->IR  = 0x04;
  else if( channel == _OCS3 )  LPC_TIM1->IR  = 0x08;
  else if( channel == _OCS4 )  LPC_TIM2->IR  = 0x04;
  else if( channel == _OCS5 )  LPC_TIM2->IR  = 0x08;
  return ;
}
