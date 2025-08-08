
/*--------------------------------------------------*/

    /*
     *  Âûäà÷à íà ÖÀÏ 10-òè ðàçðÿäíîãî êîäà, êîòîðûé ïîìåùàåòñÿ â ìëàäøèå
     *  10 ðàçðÿäîâ ñëîâà. Ñòàðøèå ðàçðÿäû íå èìåþò çíà÷åíèÿ.
     *
     *    Àäðåñ ÿ÷åéêè âûâîäèìîé íà ÖÀÏ çàäàåòñÿ ÷åðåç ñîîòâåòñòâóþùóþ
     *  óñòàâêó. Âûâîäèìàÿ ÿ÷åéêà äîëæíà áûòü â äîïîëíèòåëüíîì êîäå.
     *  ÖÀÏ îäíîïîëÿðíûé, ïîýòîìó äëÿ âûâîäà äâóïîëÿðíûõ ÷èñåë ââîäèòñÿ
     *  ñðåäíÿÿ íóëåâàÿ òî÷êà '+2047'. Çíà÷åíèå âûâîäèìîé ÿ÷åéêè
     *  ìàñøòàáèðóåòñÿ ïîñðåäñòâîì ñîîòâåòñâóþùåé óñòàâêè.
     *
     *       Òàáëèöà ñîîòâåòñòâèÿ êîäîâ è íàïðÿæåíèé ÖÀÏà :
     *    ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
     *       Íàïðÿæåíèå ³ Êîä çàïèñàííûé â ÖÀÏ  ³ Êîä ïåðåäàâàåìûé ìàêðîñó
     *      íà âûõîäå   ÃÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄ
     *       Öàïà, Â    ³    hex    ³    dec    ³    hex    ³    dec
     *    ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄ
     *        +5        ³   03.FF   ³  +1'023   ³   01.FF   ³  +0'511
     *         .        ³           ³           ³           ³
     *         .        ³           ³           ³           ³
     *         .        ³           ³           ³           ³
     *        +0        ³   02.00   ³  +0'512   ³   00.00   ³  +0'000
     *    ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄ
     *        -0        ³   01.FF   ³  +0'511   ³   FF.FF   ³  -0'001
     *         .        ³           ³           ³           ³
     *         .        ³           ³           ³           ³
     *         .        ³           ³           ³           ³
     *        -5        ³   00.00   ³  +0'000   ³   FE.00   ³  -0'512
     *                  ³           ³           ³           ³
     */


     //  Âûäà÷à äàííûõ â ÖÀÏû

void  DAC0_output ( word num )
{
  _register word ax ;

  switch ( num )
  {
    case 0 :
        DACR |= 0x01; // DAC0 - enable, 10 - bit
        DADR0 = 0x1ff;  // 3ff/2
      break;

    case 1 :
            //    Âûäà÷à íà 0-é ÖÀÏ ïëàòû ââîäà/âûâîäà.
        if (_or.dac_numb[0].var_num >=_DAC_Ntab2  ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num ].addr ;
        ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
        ax += _DAC_setka_max-(sw)_or.dac_numb[0].offset ; // ââîäèì ñðåäíþþ òî÷êó äëÿ âîçìîæí. îòîáðàæ. çíàêîâûõ ÷èñåë.
        if ( (sw)ax >= _DAC_setka_max*2 )  ax = _DAC_setka_max*2 ;
        else if ( (sw)ax <= 0 )  ax = 0 ;
        DADR0 = ax;
      break;
  }

  return   ;
}
//------------------
void  DAC1_output ( word num )
{
  _register word ax ;

  switch ( num )
  {
    case 0 :
        DACR |= 0x02; // DAC0 - enable, DAC1- enable, 10 - bit
        DADR1 = 0x1ff;
      break;

    case 1 :
     //    Âûäà÷à íà 2-é ÖÀÏ ïëàòû ââîäà/âûâîäà.
        if (_or.dac_numb[1].var_num >=_DAC_Ntab2  ) _or.dac_numb[1].var_num  = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num ].addr ;
        ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;
        ax += _DAC_setka_max-(sw)_or.dac_numb[1].offset ; // ââîäèì ñðåäíþþ òî÷êó äëÿ âîçìîæí. îòîáðàæ. çíàêîâûõ ÷èñåë.
        if ( (sw)ax >= _DAC_setka_max*2 )  ax = _DAC_setka_max*2 ;
        else if ( (sw)ax <= 0 )  ax = 0 ;
        DADR1 = ax;
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
