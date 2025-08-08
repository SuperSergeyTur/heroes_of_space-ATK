//#include "common_include.h"
//#include "lpc177x_8x_dac.h"
//#include "dac_drv.h"
//#include "monitor.h"
//#include "obj.h"
//#include "msg.h"
//#include "ppg_drv.h"
/*--------------------------------------------------*/

    /*
     *  ������ �� ��� 10-�� ���������� ����, ������� ���������� � �������
     *  10 �������� �����. ������� ������� �� ����� ��������.
     *
     *    ����� ������ ��������� �� ��� �������� ����� ���������������
     *  �������. ��������� ������ ������ ���� � �������������� ����.
     *  ��� ������������, ������� ��� ������ ����������� ����� ��������
     *  ������� ������� ����� '+2047'. �������� ��������� ������
     *  �������������� ����������� �������������� �������.
     *
     *       ������� ������������ ����� � ���������� ���� :
     *    ���������������������������������������������������������������
     *       ���������� � ��� ���������� � ���  � ��� ������������ �������
     *      �� ������   �������������������������������������������������
     *       ����, �    �    hex    �    dec    �    hex    �    dec
     *    ���������������������������������������������������������������
     *        +5        �   03.FF   �  +1'023   �   01.FF   �  +0'511
     *         .        �           �           �           �
     *         .        �           �           �           �
     *         .        �           �           �           �
     *        +0        �   02.00   �  +0'512   �   00.00   �  +0'000
     *    ���������������������������������������������������������������
     *        -0        �   01.FF   �  +0'511   �   FF.FF   �  -0'001
     *         .        �           �           �           �
     *         .        �           �           �           �
     *         .        �           �           �           �
     *        -5        �   00.00   �  +0'000   �   FE.00   �  -0'512
     *                  �           �           �           �
     */


     //  ������ ������ � ����
                                 // ��� FR50 , �.�. �� ����� ���� ������������:
void  DAC0_output ( word num )   //   DA0   -   ������������ ���
{                                //  +12V   -   +511d
  _register word ax ;            //    0V   -      0d
                                 //  -12V   -   -511d
  switch ( num )                 // ��� RCP -   ������������ ���
  {
    case 0 :
      DAC_Init(0);
      break;

    case 1 :
            //    ������ �� 0-� ��� ����� �����/������.
        if (_or.dac_numb[0].var_num >=_DAC_Ntab2 ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num ].addr ;
#ifndef  _DAC_INVERT //  �� ����� FR50 ����� ������������� ��.
              ax = ~ax + 1 ; // �������� ������� - ����������� ������������� ��.
#endif
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
                 // ������ ������� ����� ��� �������� ���� :
                 // ax += _or.dac_numb[0].offset ;
              ax += _DAC_setka_max-(sw)_or.dac_numb[0].offset ;
              if ( (sw)ax > _DAC_setka_max*2 )  ax = _DAC_setka_max*2 ;
              else if ( (sw)ax < 0 )  ax = 0 ;
            // ax <<=6;
        DAC_UpdateValue (0,ax);
      break;
  }

  return   ;
}

//------------------
void  DAC1_output ( word num )
{
  _register sword ax ;
  _register word axh, axl ;
  switch ( num )
  {
    case 0 :
      //������������� PWM0 ��� DAC
        LPC_SC->PCONP |= CLKPWR_PCONP_PCPWM1;
        LPC_PWM1->IR   = 0xFF & PWM_IR_BITMASK;
        LPC_PWM1->TCR  = 0x00;
        LPC_PWM1->CTCR = 0x00;
        LPC_PWM1->MCR  = 0x00;
        LPC_PWM1->CCR  = 0x00;
        LPC_PWM1->PCR  = 0x00;
        LPC_PWM1->LER  = 0x00;
        LPC_PWM1->TCR  = 0x02; //reset counters
        LPC_PWM1->PR   = ((lword)((d)PeripheralClock * _T_PWM_63ns ) / 1000000) - 1;
        LPC_PWM1->MR0 = _DAC_setka_max;
        LPC_PWM1->MCR  = 0x02; //reset couners if match MR0    
        LPC_PWM1->PCR  |= 0x2020; //double edge, output 5 enable 
        LPC_PWM1->TCR  = 0x01; //count enable
        LPC_PWM1->LER  = 0x01;

        PPG_init( _PPG_DAC1,0, 0 ) ;
        PPG_set( _PPG_DAC1, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
        PPG_start( _PPG_DAC1,0 ) ;
      break;

    case 1 :
            //    ������ �� 1-� ��� ����� �����/������.
        if (_or.dac_numb[1].var_num >=_DAC_Ntab2  ) _or.dac_numb[1].var_num  = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num ].addr ;
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;

                //  � ����������� ��� DAC1 ��������� �������� �� ����� ������ Cos ��� ������������ ���������� "0"
                //  ������� �������� ����� ������� �������� DAC1

              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axl = ax / 2 ;
                //    "- (ax & 0x01)"- ����� ��� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axh = _DAC_setka_max - axl - (ax & 0x01) ;
              PPG_set( _PPG_DAC1, axl, axh ) ;
      break;
  }

  return   ;
}


void DAC_start (void)
{
  DAC0_output ( 0 ) ;
  DAC1_output ( 0 ) ;
  return   ;
}

void  DAC_Output ( void )
{
  DAC0_output ( 1 ) ;
  DAC1_output ( 1 ) ;
  return   ;
}
