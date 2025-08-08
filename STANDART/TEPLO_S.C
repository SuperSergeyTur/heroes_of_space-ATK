//ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ

                /* ƒл€ “епла статора */

//     ѕрограмма расчета нагрева обмотки и расчета ограничени€ тока
//                    соответствующего нагреву.


void Teplo_s_Programm ( word num )
  {
    word ax, bx ;

    switch ( num )
    {
      case 0 :

        tpls.I_max = _It_Nom_s * 9.99 ; //_Is_nom( 9.99 )  ; // чтобы, при пуске не выдавало предупр. о перегрузке.

        tpls.Integr   = (lw)((tpl_s.TeploMax + tpl_s.TeploNom)/2) << 16 ;

        tpls.I = 0 ;
        tpls.Koef_I = &_r.Koef_Is_teplo;

        do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
           // —клеиваем два средних байта из 4 байт полного времени в
          // одно слово.
        ax = ( ax << 8 ) | ( bx >> 8 ) ;
        tpls.TimeCikl = ax ;
      break;
      /*-----------------------------*/

      case 1 :
        Teplo_Uni ( &tpls , (struct Teplo_Data*)&tpl_s ) ;
            // „тобы, не занимать в индикации более 3-х знакомест.
        if ( tpls.I_max > (_It_Nom_s * 9.99))
        {
          tpls.I_max = _It_Nom_s * 9.99 ;
        }
      break;
      /*-----------------------------*/
    }

    return   ;
  }

