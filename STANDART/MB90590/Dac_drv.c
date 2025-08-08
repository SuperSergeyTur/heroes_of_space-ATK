
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
  register word ax ;
  register word axl, axh ;

  switch ( num )
  {                    //  ������� ���� = 16���/1/1000 = 16���.
    case 0 :  PPG_init( 0, 0, 0 ) ;
              PPG_set( 0, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( 0, 0 ) ;
      break;

    case 1 :
           /*    ������ �� ��� ����� ����������.   */
        if (_or.dac_numb[1].var_num >= _DAC_Ntab2  ) _or.dac_numb[1].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num].addr ;
                 // M��������������.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ����� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( 0, axl, axh ) ;
      break;
  }

  return   ;
}
//---------------------

void  DAC2_output ( word num )
{
  register word ax ;
  register word axl, axh ;

  switch ( num )
  {                    //  ������� ���� = 16���/1/1000 = 16���.
    case 0 :  PPG_init( 5, 0, 0 ) ;
              PPG_set( 5, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( 5, 0 ) ;
      break;

    case 1 :
           /*    ������ �� ��� ����� ����������.   */
        if (_or.dac_numb[2].var_num >= _DAC_Ntab2  ) _or.dac_numb[2].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[2].var_num].addr ;
                 // M��������������.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[2].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ����� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( 5, axl, axh ) ;
      break;
  }

  return   ;
}
//---------------------

#ifdef _PPG_for_DAC3
void  DAC3_output ( word num )
{
  register word ax ;
  register word axl, axh ;

  switch ( num )
  {                    //  ������� ���� = 16���/1/1000 = 16���.
    case 0 :  PPG_init( _PPG_for_DAC3, 0, 0 ) ;
              PPG_set( _PPG_for_DAC3, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC3, 0 ) ;
      break;

    case 1 :
           /*    ������ �� ��� ����� ����������.   */
        if (_or.dac_numb[3].var_num >= _DAC_Ntab2  ) _or.dac_numb[3].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[3].var_num].addr ;
                 // M��������������.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[3].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ����� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC3, axl, axh ) ;
      break;
  }

  return   ;
}
#endif
//---------------------

#ifdef _PPG_for_DAC4
void  DAC4_output ( word num )
{
  register word ax ;
  register word axl, axh ;

  switch ( num )
  {                    //  ������� ���� = 16���/1/1000 = 16���.
    case 0 :  PPG_init( _PPG_for_DAC4, 0, 0 ) ;
              PPG_set( _PPG_for_DAC4, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC4, 0 ) ;
      break;

    case 1 :
           /*    ������ �� ��� ����� ����������.   */
        if (_or.dac_numb[4].var_num >= _DAC_Ntab2  ) _or.dac_numb[4].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[4].var_num].addr ;
                 // M��������������.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[4].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ����� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC4, axl, axh ) ;
      break;
  }

  return   ;
}

#endif
//---------------------

#ifdef _PPG_for_DAC5
void  DAC5_output ( word num )
{
  register word ax ;
  register word axl, axh ;

  switch ( num )
  {                    //  ������� ���� = 16���/1/1000 = 16���.
    case 0 :  PPG_init( _PPG_for_DAC5, 0, 0 ) ;
              PPG_set( _PPG_for_DAC5, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC5, 0 ) ;
      break;

    case 1 :
           /*    ������ �� ��� ����� ����������.   */
        if (_or.dac_numb[5].var_num >= _DAC_Ntab2  ) _or.dac_numb[5].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[5].var_num].addr ;
                 // M��������������.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[5].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  ��������� � ��� ���� �������� ������� ����.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ����� �������������� ������ ��������
                //  �� ���������� ��� "/" ��� ������ "ax" � �� �������
                //  ������������ ���� � 1000 �� 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC5, axl, axh ) ;
      break;
  }

  return   ;
}

#endif
//---------------------

void DAC_start ( void )
{
  DAC0_output ( 0 ) ;
  DAC1_output ( 0 ) ;
  DAC2_output ( 0 ) ;
#ifdef _PPG_for_DAC3
  DAC3_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC4
  DAC4_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC5
  DAC5_output ( 0 ) ;
#endif
 return ;
}

void DAC_Output ( void )
{
  DAC0_output ( 1 ) ;
  DAC1_output ( 1 ) ;
  DAC2_output ( 1 ) ;
#ifdef _PPG_for_DAC3
  DAC3_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC4
  DAC4_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC5
  DAC5_output ( 1 ) ;
#endif
 return ;
}

