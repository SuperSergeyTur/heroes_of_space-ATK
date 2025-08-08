
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
  register word axh, axl ;

  switch ( num )
  {
    case 0 :  PPG_init( 0, 0, 0 ) ;
              PPG_set( 0, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( 0 ) ;
      break;

    case 1 :
           /*    Âûäà÷à íà ÖÀÏ ïëàòû ïðîöåññîðà.   */
        if (_or.dac_numb[0].var_num>=_DAC_Ntab2  ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num].addr ;
                 // Màñøòàáèðîâàíèå.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
             // ax += _or.dac_numb[0].offset;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Ïåðåâîäèì â êîä ØÈÌà ñîãëàñíî òàáëèöû âûøå.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ÷òîáû ïðè êîìïåíñèðîâàòü ïîòåðþ äèñêðåòû
                //  íà îêðóãëåíèå ïðè "/" ïðè ÷åòíûõ "ax" è íå ñíèæàòü
                //  äèñêðåòíîñòü ÖÀÏà ñ 1000 äî 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( 0, axl, axh ) ;
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
  {                    //  ÷àñòîòà ØÈÌà = 16ÌÃö/1/1000 = 16êÃö.
    case 0 :  PPG_init( 1, 0, 0 ) ;
              PPG_set( 1, _DAC_setka_max/2, _DAC_setka_max/2 ) ;
              PPG_start( 1 ) ;
      break;

    case 1 :
           //    Âûäà÷à íà ÖÀÏ ïëàòû ïðîöåññîðà.
        if (_or.dac_numb[1].var_num >= _DAC_Ntab2  ) _or.dac_numb[1].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num].addr ;
                 // Màñøòàáèðîâàíèå.
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;
             // ax += _or.dac_numb[1].offset;
              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Ïåðåâîäèì â êîä ØÈÌà ñîãëàñíî òàáëèöû âûøå.
              ax = _DAC_setka_max + ax ;
              axh = ax / 2 ;
                //    "- (ax & 0x01)"- ÷òîáû êîìïåíñèðîâàòü ïîòåðþ äèñêðåòû
                //  íà îêðóãëåíèå ïðè "/" ïðè ÷åòíûõ "ax" è íå ñíèæàòü
                //  äèñêðåòíîñòü ÖÀÏà ñ 1000 äî 500.
              axl = _DAC_setka_max - axh - (ax & 0x01) ;
              PPG_set( 1, axl, axh ) ;
      break;
  }

  return   ;
}
//---------------------


