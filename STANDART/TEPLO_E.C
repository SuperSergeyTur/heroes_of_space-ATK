
//     Программа расчета нагрева обмотки и расчета ограничения тока
//                    соответствующего нагреву.

/*   ptr - указатель на рабочую структуру данных;
     dat - указатель на 'const' структуру исходных данных (уставок).
 */


#include <math.h>

word Teplo_exp ( word code, struct TEPLO_Data *ptr, const struct TEPLO_cData *cptr )
{
  register byte i ;
  register word ax, Ix, Imax ;
  register word bx ;
  register lword lax  ;
  register lword rIntegr ;

	  // Инициализация.
    if ( code == 0 )
    {     // защита от неправильно заданной табл.
      bx = cptr->TeploNom / 100 ;//вычисл.1%.
      ax = 0 ;                                    // и еще один % для Imax.
      if ( cptr->Tok[0] <= (cptr->TeploNom+bx)) cptr->Tok[0] = cptr->TeploNom+2*bx, ax = 1 ;
      for ( i = 0 ; i <= cptr->NumTeploPoint-2 ; i++ )
      {      // таблица токов должна идти по возрастающей.
        if ( cptr->Tok[i+1]  <= cptr->Tok[i] ) cptr->Tok[i+1]  = cptr->Tok[i]+bx,ax = 1 ;
             // таблица времени должна идти по убывающей.
        if ( cptr->Time[i+1] >= cptr->Time[i]) cptr->Time[i+1] = cptr->Time[i]-1,ax = 1 ;
      }
      ptr->label = 0 ;
      *(cptr->Iptr) = 0 ;
      ptr->I_max = cptr->TeploNom * 10 ; // чтобы, при пуске не выдавало предупр. о перегрузке.
      ptr->Integr_w = (lw)((cptr->Tok[0] + cptr->TeploNom)/2) ; //<< 16 ;
      ptr->Integr_drob = 0 ; //<< 16 ;
      ptr->Isum = 0 ;
      ptr->n_izm = 0 ;
      ptr->TimeCikl = Timer1_fSec ;

      return ax ;
    }
  //---
     // определение среднего значения тока.
  ax = ptr->Isum,  bx = ax ; // копия для контроля переполнения.
  Ix = *(cptr->Iptr) ;
  if ( (sw)Ix < 0 ) Ix = ~Ix+1 ;
  ax += Ix ;  // накапливаем сумматор тока
        // контроль переполнения.
  if ( ax >= bx ) ptr->Isum = ax, ptr->n_izm++ ;
  else            ; //ptr->Isum = 0xffff ; //ptr->n_izm++ ;  не неращиваем счетчик.

    /*   Для повышения быстродействия внешняя переменная
      * переписывается в регистровую память. */
  rIntegr  = (lw)(w)ptr->Integr_w << 16 ;
  rIntegr += (lw)(w)ptr->Integr_drob ;

  Ix = ptr->Ix,  Imax = cptr->Tok[0]-1 ;


  switch ( ptr->label )
  {
    case 0 :
                                                         // в расчете таймаут.
    if ((u)((w)(Timer1_fSec - ptr->TimeCikl)) < _fSec(_Teplo_cikl) ) return 0 ;
	  ptr->TimeCikl += _fSec(_Teplo_cikl) ;
    //------- Вычисляем средний за такт расчета ток и
        // схватываем текущий ток, чтобы на последующих шагах работать с
                                  //  округление
//   21.06.16 FAA переполнение в одноплатном ВТЕ с током <33% (Id_Nom=800 u) (и как результат перегрузка по току ротора)  (цикл программы 0,1-0,3 ms)
//  Ix = ((w)ptr->Isum+(w)(b)ptr->n_izm/2)/(w)(b)ptr->n_izm, ptr->Ix = Ix ;  //  одним и тем же значением.

    Ix = (w)(((lw)(w)ptr->Isum + (lw)(w)ptr->n_izm / 2) / (lw)(w)ptr->n_izm), ptr->Ix = Ix ;  //  одним и тем же значением.
    ptr->Isum = 0, ptr->n_izm = 0 ;

            if ( Ix >= (w)( rIntegr >> 16 ) )
            {
                /*  Н А Г Р Е В  */
                /* нахождение нужного диапазона тока */
              for ( i = 0 ; ( i < cptr->NumTeploPoint   ) && ( Ix >= cptr->Tok[i] ) ; i++ )  ;

                /* нахождение коэффициента за крайними точками */
              bx = cptr->NumTeploPoint ;
              if       ( i == 0 )
              {
                ax = cptr->Time[0], bx = cptr->Tok[0] ;
              }
              else  if ( i == bx   )
              {
                ax = cptr->Time[bx-1], bx = cptr->Tok[bx-1]  ;
              }
              else  /* нахождение коэффициента между точками (линейная аппроксимация) */
              {
                bx = Ix ;
                lax = cptr->Time[i] - cptr->Time[i-1]  ;
                ax  =  Ix - cptr->Tok[i-1]  ;
                lax = (slw)(sw)lax * (sw)ax ;
                ax = cptr->Tok[i] - cptr->Tok[i-1] ;
                ax = (slw)lax / (sw)ax ; /* проверка на переполнение в этом случае не нужна */
                ax += cptr->Time[i-1] ;
              }
              ptr->buff = (d)(bx-Imax) / (d)(bx-cptr->TeploNom)   ;
              ptr->ax = ax ;
              //---
              ptr->label = 1 ;
        break;
              //---
    case 1 :
              ptr->buff = log( ptr->buff )  ;
              ptr->label = 2 ;
        break;
              //---
    case 2 :
              ptr->buff = -(d)ptr->ax / ptr->buff ;
              ptr->buff = 1-exp(-_Teplo_cikl/ptr->buff)  ;
              ptr->label = 3 ;
          break;
                //---
    case 3 :
              lax  = (lw)(ptr->buff*256.*256.*256.) + 1u  ;  /* "+1" - для округления в большую сторону */

              if ( lax >= 0x00fffful )  ax = 0xffff ;
              else                      ax = lax ;

                      /* Расчет нагрева */
              rIntegr += (lw)( Ix - (w)( rIntegr >> 16 )) * (lw)ax >> 8   ;

              rIntegr += 0 - ((lw)((w)rIntegr) * (lw)ax >> 16 >> 8 ) ;
            }
          else           /*  О Х Л А Ж Д Е Н И Е  */
            {
              ptr->buff = (d)(cptr->Tok[0]-Imax) / (d)(cptr->Tok[0]-cptr->TeploNom)   ;
              //---
              ptr->label = 4 ;
        break;
              //---
    case 4 :
              ptr->buff = log( ptr->buff )  ;
              ptr->label = 5 ;
        break;
              //---
    case 5:
              ptr->buff = -(d)*(cptr->Time_ohlad) / ptr->buff ;
              ptr->buff = 1-exp(-_Teplo_cikl/ptr->buff)  ;
              ptr->label = 6 ;
          break;
                //---
    case 6 :
              lax  = (lw)(ptr->buff*256.*256.*256.) ;  /* "+1" - для округления в большую сторону */
              if ( lax >= 0x00fffful )  ax = 0xffff ;
              else                      ax = lax ;

                      /* Расчет охлаждения */
              rIntegr -= (lw)((w)( rIntegr >> 16 ) - Ix ) * (lw)ax >> 8  ;

              rIntegr -= (lw)((w)rIntegr) * (lw)ax >> 16 >> 8  ;
            }
                 /*   Ограничение верхней границы теплового интегратора на
                  * уровне "TeploMax", иначе, если дать ему перегреться, то
                  * это загонит токовое ограничение до нуля и ниже. */
          if ( rIntegr > ( (lw)Imax << 16 ) )
                                  rIntegr = (lw)Imax << 16 ;

               /*   Ограничение нижней границы теплового интегратора на
                * уровне "TeploNom", иначе, если дать ему остыть, то
                * выдержки времени возрастут выше табличных. */
          else  if ( rIntegr < ( (lw)(cptr->TeploNom)   << 16 ) )
                                        rIntegr = (lw)(cptr->TeploNom) << 16 ;

              /*   Определение макс.доп. тока до последующего такта расчета исходя из
               * расчитанного текущего нагрева.   */

    /*   Коэффициент расчета допустимого тока как функции вычисленного нагрева.
     *  Следовало бы иметь таблицу коэфф. расположенных соответственно токам,
     *  но в этом случае отсутствует плавность наложения ограничения на ток (при
     *  монотонном(!) нагреве или охлаждении) из-за перехода от одного коэффициента
     *  к другому (в зависимости от диапазона тока).
     *    Поэтому выбран один обратный коэфф. соответствующий наибольшему коэфф. из
     *  таблицы '_Kq[]', что обеспечивает наибольшую плавность наростания или снижения
     *  ограничения и его несколько более раннее наложение.
     *  Если выбрать обратный коэфф. соответствующий наименьшему коэфф. из таблицы
     *  '_Kq[]', то при этом будет наблюдаться резкое наростание или снижение
     *  ограничения при его несколько более позднем наложении.
     */
              ax = cptr->Tok[cptr->NumTeploPoint-1] ;
              ptr->buff = (d)(ax-Imax) / (d)(ax-cptr->TeploNom)   ;
              //---
              ptr->label = 7 ;
        break;
              //---
    case 7 :
              ptr->buff = log( ptr->buff )  ;
              ptr->label = 8 ;
        break;
              //---
    case 8 :
              ptr->buff = -(d)cptr->Time[cptr->NumTeploPoint-1] / ptr->buff ;
              ptr->buff = 1.-exp(-_Teplo_cikl/ptr->buff)  ;

                   // Вычисляем обратный коэфф.
              ax  = (w)(1./ptr->buff) ;

          lax = (lw)( Imax - (w)(rIntegr >> 16) ) * (lw)ax ;

          lax -= (lw)((w)rIntegr) * (lw)ax >> 16  ;

          lax += (lw)((w)(rIntegr >> 16))  ;

              // ограничение выхода, чтобы не занимать в индикации более 3-х симв.
          ax = cptr->TeploNom * 10 - 1 ;
          if ( lax > ax ) lax = ax ;

          //---  Filtraciya.
       // lax  = (lax - (lw)ptr->I_max) << ( 8 ) ; //-4) ;   //  Фильтрация превращает выдержку 20сек в 23сек.

       // lax += (slw)(sw)ptr->I_max << 8 ;
       // lax += (lw)(w)ptr->I_max_drob ;   // DROB ISN'T SIGNED !

          ptr->I_max = (slw)lax ; //>> 8 ;
       // ptr->I_max_drob = lax ;

          //---
          ptr->label = 0 ;
    break;//-------------
  }
        // Возвращаем обработанное значение интегратора.
  ptr->Integr_w    = (w)(rIntegr >> 16)  ;  // Для индикации.
  ptr->Integr_drob = (w) rIntegr ;


  if ( ptr->label == 0 )  return 1 ; // расчет только что завершен.
  else                    return 2 ; // расчет незавершен.

}

