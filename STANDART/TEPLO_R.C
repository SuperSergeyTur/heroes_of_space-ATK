//ƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒƒ

                /* ƒл€ “епла ротора */

//     ѕрограмма расчета нагрева обмотки и расчета ограничени€ тока
//                    соответствующего нагреву.


void Teplo_Programm ( word num )
  {
    word ax, bx ;

    switch ( num )
    {
      case 0 :

        tpl.I_max = _It_Nom_r * 9.99 ;//_Id_nom( 9.99 )  ;   // чтобы, при пуске не выдавало предупр. о перегрузке.

        tpl.Integr   = (lw)((tpl_r.TeploMax + tpl_r.TeploNom)/2) << 16 ;

        tpl.I = 0 ;
        tpl.Koef_I = &_r.Koef_Id_teplo;

        do { ax = Timer1_Ovr , bx = timer1 ; } while ( ax != Timer1_Ovr ) ;
           // —клеиваем два средних байта из 4 байт полного времени в
          // одно слово.
        ax = ( ax << 8 ) | ( bx >> 8 ) ;
        tpl.TimeCikl = ax ;
      break;
      /*-----------------------------*/

      case 1 :
        Teplo_Uni ( &tpl , (struct Teplo_Data *)&tpl_r ) ;
            // „тобы, не занимать в индикации более 3-х знакомест.
        if ( tpl.I_max > (_It_Nom_r * 9.99) )
        {
          tpl.I_max = _It_Nom_r * 9.99  ;
        }

      break;
      /*-----------------------------*/
    }

    return   ;
  }

