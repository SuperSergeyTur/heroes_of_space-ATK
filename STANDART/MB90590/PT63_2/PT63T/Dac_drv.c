
//         ��������� ������ �� ���� ��������� �� �����.
//------------------------------------------------------------------

/*--------------------------------------------------*/

    /*
     *    ������ �� ��� ����� PPG (���),
     *
     *    ����� ������ ��������� �� ��� �������� ����� ���������������
     *  �������. ��������� ������ ������ ���� � �������������� ����.
     *  ��� ������������, ������� ��� ������ ����������� ����� ��������
     *  ������� ������� �����. �������� ��������� ������
     *  �������������� ����������� �������������� �������.
     *
     *    ��������� ���� �������� ������ ���� (L) � ������ ������� (H).
     *    L = 0..._DAC_setka_max, H = 0..._DAC_setka_max.
     *       ������� ������������ ����� ���� � ���������� ���� :
     *    �����������������������������������������������������
     *       ���������� �       ���          �   ��������
     *                  �       ����         �  ����������
     *      �� ������   ���������������������������������������
     *       ����, �    �     hex: H/L       �    dec
     *    �����������������������������������������������������
     *        +10/ +5   � _DAC_setka_max / 0 � +_DAC_setka_max
     *         .        �                    �
     *         .        �                    �
     *        +0 /+2.5  � (_DAC_setka_max/2)/�  0
     *         .        � (_DAC_setka_max/2) �
     *         .        �                    �
     *        -10/ 0    � 0 / _DAC_setka_max � -_DAC_setka_max
     *                  �                    �
     */


     //  ������ ������ � ��� ����� ����������.

void  DAC0_output ( word num )
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( 4, 0, 0 ) ;
              PPG_set( 4, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( 4, 0 ) ;
      break;

    case 1 :
           /*    ������ �� ��� ����� ����������.   */
        if (_or.dac_numb[0].var_num>=_DAC_Ntab2  ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num].addr ;
                 // M��������������.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ����� ��� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( 4, axl, axh ) ;
      break;
  }

  return   ;
}
//--------------

void  DAC1_output ( word num )
{
  num = num ;
  return   ;
}
//---------------------

void  DAC2_output ( word num )
{
  num = num ;
  return   ;
}
//---------------------

void DAC_start ( void )
{
  DAC0_output ( 0 ) ;
  DAC1_output ( 0 ) ;
  DAC2_output ( 0 ) ;
 return ;
}

void DAC_Output ( void )
{
  DAC0_output ( 1 ) ;
  DAC1_output ( 1 ) ;
  DAC2_output ( 1 ) ;
 return ;
}

