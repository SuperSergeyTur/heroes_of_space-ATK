//ДДДДДДДДДДДДДДДДДДДДДДДДДДДДДДД

//     Программа расчета нагрева обмотки и расчета ограничения тока
//                    соответствующего нагреву.

/*   ptr - указатель на рабочую структуру данных;
     dat - указатель на 'const' структуру исходных данных (уставок).
 */

void Teplo_Uni ( struct Teplo_un *ptr , struct Teplo_Data *dat )
  {
    register byte i ;
    register word ax , Ix ;
    register lword lax  ;
    register lword rIntegr  ;

		        /* Считывание полного времени таймеров. */
    do { ax = Timer1_Ovr , Ix = timer1 ; } while ( ax != Timer1_Ovr ) ;
          //  Из четырехбайтного полного значения времени
          // для работы берутся средние два байта прини-
          // мающие значения в диапазоне 0.25мсек-12.0сек.
    ax = ( ax << 8 ) | ( Ix >> 8 ) ;

    Ix = dat->TimeCikl_Teplo * _fSec(0.001) ;
    if ((u)((w)(ax - ptr->TimeCikl)) < Ix ) return ;
    ptr->TimeCikl += Ix  ;

      /*   Для повышения быстродействия внешняя переменная
       * переписывается в регистровую память. */
    rIntegr = ptr->Integr  ;

		    /* Масштабирование тока. */
    ax = *(ptr->Koef_I)  ;
    Ix = ptr->I  ;
    Ix = (w)( (lw)Ix * (lw)ax >> 8 ) ;

    if ( Ix >= (w)( rIntegr >> 16 ) )
      {
                   /*  Н А Г Р Е В  */
          /* нахождение нужного диапазона тока */
        for ( i = 0 ; ( i < dat->NumTeploPoint   ) && ( Ix >= dat->Tok[i] ) ; i++ )  ;

          /* нахождение коэффициента за крайними точками */
        if       ( i == 0 )                 ax = dat->Kq [0]                 ;
        else  if ( i == dat->NumTeploPoint   )  ax = dat->Kq [dat->NumTeploPoint-1]  ;
          /* нахождение коэффициента между точками (линейная аппроксимация) */
              else
                {
                  lax = dat->Kq[i] - dat->Kq[i-1]  ;
                  ax  =  Ix - dat->Tok[i-1]  ;
                  lax = (slw)(sw)lax * (sw)ax ;
                  ax = dat->Tok[i] - dat->Tok[i-1] ;
                  ax = (slw)lax / (sw)ax ; /* проверка на переполнение в этом случае не нужна */
                  ax += dat->Kq[i-1] ;
                }
                /* Расчет нагрева */
        rIntegr += (lw)( Ix - (w)( rIntegr >> 16 )) * (lw)ax >> 8   ;

        rIntegr += 0 - ((lw)((w)rIntegr) * (lw)ax >> 16 >> 8) ;
      }
                     /*  О Х Л А Ж Д Е Н И Е  */
    else
      {
        ax = dat->Kq_Ohlad ;     /* для охлаждения - свой коэфф. расчета */
                /* Расчет охлаждения */
        rIntegr -= (lw)((w)( rIntegr >> 16 ) - Ix ) * (lw)ax >> 8  ;

        rIntegr -= (lw)((w)rIntegr) * (lw)ax >> 16 >> 8  ;
      }
           /*   Ограничение верхней границы теплового интегратора на
            * уровне "TeploMax", иначе, если дать ему перегреться, то
            * это загонит токовое ограничение до нуля и ниже. */
    if ( rIntegr > ( (lw)(dat->TeploMax)   << 16 ) )
                            rIntegr = (lw)(dat->TeploMax)   << 16 ;

         /*   Ограничение нижней границы теплового интегратора на
          * уровне "TeploNom", иначе, если дать ему остыть, то
          * выдержки времени возрастут выше табличных. */
    else  if ( rIntegr < ( (lw)(dat->TeploNom)   << 16 ) )
                                  rIntegr = (lw)(dat->TeploNom) << 16 ;

        /*   Определение макс.доп. тока на последующую секунду исходя из
         * расчитанного текущего нагрева.   */
    ax = dat->Kq_Obratn ;

    lax = (lw)( dat->TeploMax    - (w)(rIntegr >> 16) ) * (lw)ax ;

    lax -= (lw)((w)rIntegr) * (lw)ax >> 16  ;

    lax += (lw)((w)(rIntegr >> 16))  ;

         /* ограничение выхода за положительную 16-разр. сетку.   */
    if ( lax > 0x7ffful ) lax = 0x7fffu ;

		    /* Обратное масштабирование для токового ограничения.*/
		lax <<= 8 ;
      ax = *(ptr->Koef_I)  ;
    lax /= ax ;
       // control of over... не вылез ли результат деления за 2 байта.
    if ( lax > 0x7ffful )  lax = 0x7fff ;

    ptr->I_max = lax ;

    ptr->Integr  = rIntegr  ;

    return   ;
  }

