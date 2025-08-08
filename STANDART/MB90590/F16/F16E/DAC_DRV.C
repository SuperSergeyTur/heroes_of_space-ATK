
//         ÏÐÎÃÐÀÌÌÛ ÂÛÄÀ×È ÍÀ ÖÀÏû ÈÌÅÞÙÈÅÑß ÍÀ ÏËÀÒÅ.
//------------------------------------------------------------------

/*--------------------------------------------------*/

    /*
     *    Âûäà÷à íà ÖÀÏ ÷åðåç PPG (ØÈÌ),
     *
     *    Àäðåñ ÿ÷åéêè âûâîäèìîé íà ÖÀÏ çàäàåòñÿ ÷åðåç ñîîòâåòñòâóþùóþ
     *  óñòàâêó. Âûâîäèìàÿ ÿ÷åéêà äîëæíà áûòü â äîïîëíèòåëüíîì êîäå.
     *  ÖÀÏ îäíîïîëÿðíûé, ïîýòîìó äëÿ âûâîäà äâóïîëÿðíûõ ÷èñåë ââîäèòñÿ
     *  ñðåäíÿÿ íóëåâàÿ òî÷êà. Çíà÷åíèå âûâîäèìîé ÿ÷åéêè
     *  ìàñøòàáèðóåòñÿ ïîñðåäñòâîì ñîîòâåòñâóþùåé óñòàâêè.
     *
     *    Ïàðàìåòðû ØÈÌà çàäàþòñÿ äëèíîé íóëÿ (L) è äëèíîé åäèíèöû (H).
     *    L = 0..._DAC_setka_max, H = 0..._DAC_setka_max.
     *       Òàáëèöà ñîîòâåòñòâèÿ êîäîâ ØÈÌà è íàïðÿæåíèé ÖÀÏà :
     *    ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
     *       Íàïðÿæåíèå ³       Êîä          ³   Çíà÷åíèå
     *                  ³       ØÈÌà         ³  ïåðåìåííîé
     *      íà âûõîäå   ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
     *       Öàïà, Â    ³     hex: H/L       ³    dec
     *    ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
     *        +10/ +5   ³ _DAC_setka_max / 0 ³ +_DAC_setka_max
     *         .        ³                    ³
     *         .        ³                    ³
     *        +0 /+2.5  ³ (_DAC_setka_max/2)/³  0
     *         .        ³ (_DAC_setka_max/2) ³
     *         .        ³                    ³
     *        -10/ 0    ³ 0 / _DAC_setka_max ³ -_DAC_setka_max
     *                  ³                    ³
     */


     //  Âûäà÷à äàííûõ â ÖÀÏ ïëàòû ïðîöåññîðà.

void  DAC0_output ( word num )
{
  register word ax ;

  switch ( num )
  {
    case 0 :
             mLDAC_clr();

             sio_out(0);
             sio_out(0);

             mLDAC_set();

        break;

    case 1 :
           /*    Âûäà÷à íà ÖÀÏ ïëàòû ïðîöåññîðà.   */
        if (_or.dac_numb[0].var_num>=_DAC_Ntab2  ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num].addr ;
                 // Màñøòàáèðîâàíèå.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Ïåðåâîäèì â êîä ØÈÌà ñîãëàñíî òàáëèöû âûøå.
              ax = _DAC_setka_max + ax ;
              //Âûâîä íà DAC

              mLDAC_clr();

              sio_out(ax>>8);

              sio_out(ax);

              mLDAC_set();

      break;
  }

  return   ;
}
//--------------

void  DAC1_output ( word num )
{
  register word ax ;

  switch ( num )
  {
    case 0 :

        Port55_B = 0x05 ;
        mWR_clr() ;

            sio_out(0);
            sio_out(0);

        mWR_set() ;

        break;

    case 1 :
           /*    Âûäà÷à íà ÖÀÏ ïëàòû ïðîöåññîðà.   */
        if (_or.dac_numb[1].var_num >= _DAC_Ntab2  ) _or.dac_numb[1].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num].addr ;
                 // Màñøòàáèðîâàíèå.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Ïåðåâîäèì â êîä ØÈÌà ñîãëàñíî òàáëèöû âûøå.
              ax = _DAC_setka_max + ax ;

        Port55_B = 0x05 ;
        mWR_clr() ;

              sio_out(ax>>8);

              sio_out(ax);

        mWR_set() ;
      break;
  }

  return   ;
}
//---------------------

void  DAC2_output ( word num )
{
  register word ax ;

  switch ( num )
  {                    //  ÷àñòîòà ØÈÌà = 16ÌÃö/1/1000 = 16êÃö.
    case 0 :

        Port55_B = 0x06;
        mWR_clr() ;

            sio_out(0);
            sio_out(0);

        mWR_set() ;
        break;

    case 1 :
           /*    Âûäà÷à íà ÖÀÏ ïëàòû ïðîöåññîðà.   */
        if (_or.dac_numb[2].var_num >= _DAC_Ntab2  ) _or.dac_numb[2].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[2].var_num].addr ;
                 // Màñøòàáèðîâàíèå.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[2].mashtab >> 8 ) ;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Ïåðåâîäèì â êîä ØÈÌà ñîãëàñíî òàáëèöû âûøå.
              ax = _DAC_setka_max + ax ;

        Port55_B = 0x06;
        mWR_clr() ;

            sio_out(ax >> 8);
            sio_out(ax);

        mWR_set() ;
      break;
  }

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

