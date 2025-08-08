
/*--------------------------------------------------*/

    /*
     *  Выдача на ЦАП 10-ти разрядного кода, который помещается в младшие
     *  10 разрядов слова. Старшие разряды не имеют значения.
     *
     *    Адрес ячейки выводимой на ЦАП задается через соответствующую
     *  уставку. Выводимая ячейка должна быть в дополнительном коде.
     *  ЦАП однополярный, поэтому для вывода двуполярных чисел вводится
     *  средняя нулевая точка '+2047'. Значение выводимой ячейки
     *  масштабируется посредством соответсвующей уставки.
     *
     *       Таблица соответствия кодов и напряжений ЦАПа :
     *    ДДДДДДДДДДДДДДВДДДДДДДДДДДДДДДДДДДДДДДВДДДДДДДДДДДДДДДДДДДДДДДД
     *       Напряжение і Код записанный в ЦАП  і Код передаваемый макросу
     *      на выходе   ГДДДДДДДДДДДВДДДДДДДДДДДЕДДДДДДДДДДДВДДДДДДДДДДДД
     *       Цапа, В    і    hex    і    dec    і    hex    і    dec
     *    ДДДДДДДДДДДДДДЕДДДДДДДДДДДЕДДДДДДДДДДДЕДДДДДДДДДДДЕДДДДДДДДДДДД
     *        +5        і   03.FF   і  +1'023   і   01.FF   і  +0'511
     *         .        і           і           і           і
     *         .        і           і           і           і
     *         .        і           і           і           і
     *        +0        і   02.00   і  +0'512   і   00.00   і  +0'000
     *    ДДДДДДДДДДДДДДЕДДДДДДДДДДДЕДДДДДДДДДДДЕДДДДДДДДДДДЕДДДДДДДДДДДД
     *        -0        і   01.FF   і  +0'511   і   FF.FF   і  -0'001
     *         .        і           і           і           і
     *         .        і           і           і           і
     *         .        і           і           і           і
     *        -5        і   00.00   і  +0'000   і   FE.00   і  -0'512
     *                  і           і           і           і
     */


     //  Выдача данных в ЦАПы
                                 // Для FR50 , т.к. на плате есть операционник:
void  DAC0_output ( word num )   //   DA0   -   Двухполярный ЦАП
{                                //  +12V   -   +511d
  _register word ax ;            //    0V   -      0d
                                 //  -12V   -   -511d
  switch ( num )                 // Для RCP -   Однополярный ЦАП
  {
    case 0 :
        DACR |= 0x01; // DAC0 - enable, 10 - bit
        DADR0 = 0x1ff;  // 3ff/2
      break;

    case 1 :
            //    Выдача на 0-й ЦАП платы ввода/вывода.
        if (_or.dac_numb[0].var_num >=_DAC_Ntab2 ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num ].addr ;
#ifndef  _DAC_INVERT //  На плате FR50 стоит инвертирующий ОУ.
              ax = ~ax + 1 ; // Инверсия сигнала - компенсация инветирующего ОУ.
#endif
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
                 // вводим среднюю точку для смещения нуля :
                 // ax += _or.dac_numb[0].offset ;
              ax += _DAC_setka_max-(sw)_or.dac_numb[0].offset ;
              if ( (sw)ax > _DAC_setka_max*2 )  ax = _DAC_setka_max*2 ;
              else if ( (sw)ax < 0 )  ax = 0 ;

        DADR0 = ax;
      break;
  }

  return   ;
}

//------------------
void  DAC1_output ( word num )   //    DA1   -   Однополярный ЦАП
{                                //    +5V   -   +511d
  _register word ax ;            //  +2.5V   -      0d
                                 //     0V   -   -511d
  switch ( num )
  {
    case 0 :
        DACR |= 0x02; // DAC0 - enable, DAC1- enable, 10 - bit
        DADR1 = 0x1ff;
      break;

    case 1 :
            //    Выдача на 1-й ЦАП платы ввода/вывода.
        if (_or.dac_numb[1].var_num >=_DAC_Ntab2  ) _or.dac_numb[1].var_num  = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num ].addr ;
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;
                 // вводим среднюю точку для смещения нуля :
                 // ax += _or.dac_numb[1].offset ;
              ax += _DAC_setka_max-(sw)_or.dac_numb[1].offset ;
              if ( (sw)ax > _DAC_setka_max*2 )  ax = _DAC_setka_max*2 ;
              else if ( (sw)ax < 0 )  ax = 0 ;

        DADR1 = ax;
      break;
  }

  return   ;
}
#ifdef  _PPG_for_DAC2
//------------------
void  DAC2_output ( word num )   // PPGX ,  где Х - номер используемого PPG .
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( _PPG_for_DAC2, 0, 0 ) ;
              PPG_set( _PPG_for_DAC2, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC2,0 ) ;
      break;

    case 1 :
           /*    Выдача на ЦАП платы процессора.   */
        if (_or.dac_numb[2].var_num>=_DAC_Ntab2  ) _or.dac_numb[2].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[2].var_num].addr ;
                 // Mасштабирование.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[2].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Переводим в код ШИМа согласно таблицы выше.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- чтобы при компенсировать потерю дискреты
                //  на округление при "/" при четных "ax" и не снижать
                //  дискретность ЦАПа с 1000 до 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC2, axl, axh ) ;
      break;
  }

  return   ;
}
#endif
//------------------
#ifdef _PPG_for_DAC3
void  DAC3_output ( word num )   // PPGX ,  где Х - номер используемого PPG .
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( _PPG_for_DAC3, 0, 0 ) ;
              PPG_set( _PPG_for_DAC3, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC3,0 ) ;
      break;

    case 1 :
           /*    Выдача на ЦАП платы процессора.   */
        if (_or.dac_numb[3].var_num>=_DAC_Ntab2  ) _or.dac_numb[3].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[3].var_num].addr ;
                 // Mасштабирование.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[3].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Переводим в код ШИМа согласно таблицы выше.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- чтобы при компенсировать потерю дискреты
                //  на округление при "/" при четных "ax" и не снижать
                //  дискретность ЦАПа с 1000 до 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC3, axl, axh ) ;
      break;
  }

  return   ;
}
#endif

//------------------
#ifdef _PPG_for_DAC4
void  DAC4_output ( word num )   // PPGX ,  где Х - номер используемого PPG .
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( _PPG_for_DAC4, 0, 0 ) ;
              PPG_set( _PPG_for_DAC4, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC4,0 ) ;
      break;

    case 1 :
           /*    Выдача на ЦАП платы процессора.   */
        if (_or.dac_numb[4].var_num>=_DAC_Ntab2  ) _or.dac_numb[4].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[4].var_num].addr ;
                 // Mасштабирование.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[4].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Переводим в код ШИМа согласно таблицы выше.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- чтобы при компенсировать потерю дискреты
                //  на округление при "/" при четных "ax" и не снижать
                //  дискретность ЦАПа с 1000 до 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC4, axl, axh ) ;
      break;
  }

  return   ;
}
#endif

//------------------
#ifdef _PPG_for_DAC5
void  DAC5_output ( word num )   // PPGX ,  где Х - номер используемого PPG .
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( _PPG_for_DAC5, 0, 0 ) ;
              PPG_set( _PPG_for_DAC5, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC5,0 ) ;
      break;

    case 1 :
           /*    Выдача на ЦАП платы процессора.   */
        if (_or.dac_numb[5].var_num>=_DAC_Ntab2  ) _or.dac_numb[5].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[5].var_num].addr ;
                 // Mасштабирование.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[5].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Переводим в код ШИМа согласно таблицы выше.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- чтобы при компенсировать потерю дискреты
                //  на округление при "/" при четных "ax" и не снижать
                //  дискретность ЦАПа с 1000 до 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC5, axl, axh ) ;
      break;
  }

  return   ;
}
#endif

//------------------
#ifdef _PPG_for_DAC6
void  DAC6_output ( word num )   // PPGX ,  где Х - номер используемого PPG .
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( _PPG_for_DAC6, 0, 0 ) ;
              PPG_set( _PPG_for_DAC6, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC6,0 ) ;
      break;

    case 1 :
           /*    Выдача на ЦАП платы процессора.   */
        if (_or.dac_numb[6].var_num>=_DAC_Ntab2  ) _or.dac_numb[6].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[6].var_num].addr ;
                 // Mасштабирование.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[6].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Переводим в код ШИМа согласно таблицы выше.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- чтобы при компенсировать потерю дискреты
                //  на округление при "/" при четных "ax" и не снижать
                //  дискретность ЦАПа с 1000 до 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC6, axl, axh ) ;
      break;
  }

  return   ;
}
#endif
//--------------

#ifdef _PPG_for_DAC7
void  DAC7_output ( word num )   // PPGX ,  где Х - номер используемого PPG .
{
  register word ax ;
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( _PPG_for_DAC7, 0, 0 ) ;
              PPG_set( _PPG_for_DAC7, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( _PPG_for_DAC7,0 ) ;
      break;

    case 1 :
           /*    Выдача на ЦАП платы процессора.   */
        if (_or.dac_numb[7].var_num>=_DAC_Ntab2  ) _or.dac_numb[7].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[7].var_num].addr ;
                 // Mасштабирование.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[7].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Переводим в код ШИМа согласно таблицы выше.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- чтобы при компенсировать потерю дискреты
                //  на округление при "/" при четных "ax" и не снижать
                //  дискретность ЦАПа с 1000 до 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( _PPG_for_DAC7, axl, axh ) ;
      break;
  }

  return   ;
}
#endif
//--------------


void DAC_start (void)
{
  DAC0_output ( 0 ) ;
  DAC1_output ( 0 ) ;
#ifdef _PPG_for_DAC2
  DAC2_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC3
  DAC3_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC4
  DAC4_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC5
  DAC5_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC6
  DAC6_output ( 0 ) ;
#endif
#ifdef _PPG_for_DAC7
  DAC7_output ( 0 ) ;
#endif
  return   ;
}

void  DAC_Output ( void )
{
  DAC0_output ( 1 ) ;
  DAC1_output ( 1 ) ;
#ifdef _PPG_for_DAC2
  DAC2_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC3
  DAC3_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC4
  DAC4_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC5
  DAC5_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC6
  DAC6_output ( 1 ) ;
#endif
#ifdef _PPG_for_DAC7
  DAC7_output ( 1 ) ;
#endif
  return   ;
}
