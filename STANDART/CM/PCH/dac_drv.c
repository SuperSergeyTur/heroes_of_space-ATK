//#include "common_include.h"
//#include "lpc177x_8x_dac.h"
//#include "dac_drv.h"
//#include "monitor.h"
//#include "obj.h"
//#include "msg.h"
//#include "ppg_drv.h"
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
                                 // Äëÿ FR50 , ò.ê. íà ïëàòå åñòü îïåðàöèîííèê:
void  DAC0_output ( word num )   //   DA0   -   Äâóõïîëÿðíûé ÖÀÏ
{                                //  +12V   -   +511d
  _register word ax ;            //    0V   -      0d
                                 //  -12V   -   -511d
  switch ( num )                 // Äëÿ RCP -   Îäíîïîëÿðíûé ÖÀÏ
  {
    case 0 :
      DAC_Init(0);
      break;

    case 1 :
            //    Âûäà÷à íà 0-é ÖÀÏ ïëàòû ââîäà/âûâîäà.
        if (_or.dac_numb[0].var_num >=_DAC_Ntab2 ) _or.dac_numb[0].var_num = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[0].var_num ].addr ;
#ifndef  _DAC_INVERT //  Íà ïëàòå FR50 ñòîèò èíâåðòèðóþùèé ÎÓ.
              ax = ~ax + 1 ; // Èíâåðñèÿ ñèãíàëà - êîìïåíñàöèÿ èíâåòèðóþùåãî ÎÓ.
#endif
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[0].mashtab >> 8 ) ;
                 // ââîäèì ñðåäíþþ òî÷êó äëÿ ñìåùåíèÿ íóëÿ :
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
      //Êîíôèãóðèðóåì PWM0 äëÿ DAC
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
            //    Âûäà÷à íà 1-é ÖÀÏ ïëàòû ââîäà/âûâîäà.
        if (_or.dac_numb[1].var_num >=_DAC_Ntab2  ) _or.dac_numb[1].var_num  = _DAC_Ntab2-1;
        ax = *DAC_tab2[_or.dac_numb[1].var_num ].addr ;
              ax = (sw)( (slw)(sw)ax * (slw)(sw)_or.dac_numb[1].mashtab >> 8 ) ;

                //  Â îäíîïëàòíîì ÂÒÅ DAC1 àïïàðàòíî ïîäâÿçàí íà ñõåìó âûäà÷è Cos áåç ïîäñòðîå÷íûõ ðåçèñòîðîâ "0"
                //  ïîýòîìó ïðèøëîñü îïÿòü âåðíóòü ñìåùåíèå DAC1

              if ( (sw)ax      > (sw)_DAC_setka_max ) ax = _DAC_setka_max ;
              else if ( (sw)ax < (sw)_DAC_setka_min ) ax = _DAC_setka_min ;

                //  Ïåðåâîäèì â êîä ØÈÌà ñîãëàñíî òàáëèöû âûøå.
              ax = _DAC_setka_max + ax ;
              axl = ax / 2 ;
                //    "- (ax & 0x01)"- ÷òîáû ïðè êîìïåíñèðîâàòü ïîòåðþ äèñêðåòû
                //  íà îêðóãëåíèå ïðè "/" ïðè ÷åòíûõ "ax" è íå ñíèæàòü
                //  äèñêðåòíîñòü ÖÀÏà ñ 1000 äî 500.
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
